#ifndef AZURE_IOTHUB_LITE_H
#define AZURE_IOTHUB_LITE_H

#include "iothub.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"

#include "iothubtransportamqp.h"
//#include "iothubtransportmqtt.h"

#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/uniqueid.h"
#include "azure_c_shared_utility/lock.h"

#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/shared_util_options.h"

#define SEMICOLON ;
#define CONTENT_TYPE "ContentType"
#define DEFAULT_SEND_TIMEOUT 60
#define SEND_TIMEOUT "SendTimeout"
#define DEFAULT_CONTENT_TYPE "application%2Fjson"
#define CONTENT_ENCODING "ContentEncoding"
#define DEFAULT_CONTENT_ENCODING "utf-8"
#define MESSAGE_ID "MessageId"
#define CORRELATION_ID "CorrelationId"
#define DEFAULT_UNIQUE_ID_LENGTH 40



#ifdef __cplusplus
extern "C"
{
#endif

	struct message;
	
	typedef void *(*receive_message_handler)(struct message* message, void* user_context);

	struct message *message_type_create(const char* messageId, const char* correlationId);
	void* message_type_copy(struct message *src, struct message **dst);
	void *message_type_destroy(struct message* message);
	
	struct device *device_type_create(const char* connectionString);
	void *device_type_destroy(struct device* device);
	IOTHUB_MESSAGE_RESULT device_post_message(struct device* self, const char *message, char** message_id);
	IOTHUB_MESSAGE_RESULT device_send_message(struct device* self, const char *message);
	IOTHUB_MESSAGE_RESULT device_set_message_property(struct device* self, const char *key, const char *value);
	IOTHUB_MESSAGE_RESULT device_set_system_property(struct device* self, const char *key, const char *value);
	
	IOTHUB_MESSAGE_RESULT device_set_receive_handler(struct device* self, receive_message_handler callback, void* user_context);
	IOTHUBMESSAGE_DISPOSITION_RESULT device_receive_handler(IOTHUB_MESSAGE_HANDLE message, void* user_context);

	IOTHUB_MESSAGE_RESULT device_receive_message(struct device *self, struct message** msg);
	

	void device_flush(struct device* self);
	void device_on_ack(struct device* self, bool success, const char* message_id);
	bool device_wait_for_message_ack(struct device* self, const char* message_id);
	bool device_wait_for_all_acks(struct device* self);

	struct ack {
		struct device* device;
		char* message_Id;
	};

	struct message {		
		char* message_Id;
		char* correlation_Id;

		IOTHUBMESSAGE_CONTENT_TYPE content_type;

		union {
			unsigned char* binary;
			char* text;
		}data;

		size_t data_len;
	};
	typedef struct message_type {
		struct message* (*create)();
		void* (*destroy)(struct message * message);
		void* (*cpy)(struct message * src, struct message ** dst);
		
	}tMessage;

	

	extern const tMessage Message;

	struct device {
		IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;

		MAP_HANDLE system_properties;
		MAP_HANDLE message_properties;
		MAP_HANDLE message_pending_acks;
		void* user_context;

		LOCK_HANDLE receive_lock_handle;

		struct message* last_inbound_message;

		IOTHUBMESSAGE_DISPOSITION_RESULT(*receive_handler)(IOTHUB_MESSAGE_HANDLE message, void* user_context);

		receive_message_handler receive_user_handle;

		IOTHUB_MESSAGE_RESULT(*post_message)(struct device* self, const char* message, char** message_id);
		IOTHUB_MESSAGE_RESULT(*send_message)(struct device* self, const char* message);

		IOTHUB_MESSAGE_RESULT(*receive_message)(struct device* self, struct message** msg);
		IOTHUB_MESSAGE_RESULT(*set_receive_handler)(struct device* self, receive_message_handler callback, void* user_context);

		void(*on_ack)(struct device* self, bool success, char* message_id);
		void(*flush)(struct device* self);
		bool(*wait_for_message_ack)(struct device* self, char* message_id);
		bool(*wait_for_all_acks)(struct device* self);

		void(*on_message_sent)(const char *message_id);
		void(*on_message_failed)(const char *message_id);

		IOTHUB_MESSAGE_RESULT(*set_message_property)(struct device* self, char *key, char *value);
		IOTHUB_MESSAGE_RESULT(*set_system_property)(struct device* self, char *key, char *value);
	};

	typedef struct device_type {
		struct device* (*create)(char *connectionString);
		void* (*destroy)(struct device * device);
	}tDevice;

	extern const tDevice Device;

#ifdef __cplusplus
}
#endif

#endif //AZURE_IOTHUB_LITE_H