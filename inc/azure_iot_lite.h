#ifndef AZURE_IOTHUB_LITE_H
#define AZURE_IOTHUB_LITE_H

#include "iothub_client.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "azure_c_shared_utility/uniqueid.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "iothub_client_options.h"

#include "iothubtransportamqp.h"

#define CONTENT_TYPE "ContentType"
#define DEFAULT_CONTENT_TYPE "application%2Fjson"
#define CONTENT_ENCODING "ContentEncoding"
#define DEFAULT_CONTENT_ENCODING "utf-8"
#define MESSAGE_ID "MessageId"
#define CORRELATION_ID "CorrelationId"
#define DEFAULT_UNIQUE_ID_LENGTH 40

#define ACK_TIMEOUT 60 //seconds

#ifdef __cplusplus
extern "C"
{
#endif
	struct device *device_type_create(char * connectionString);
	void *device_type_destroy(struct device * device);
	IOTHUB_MESSAGE_RESULT device_post_message(struct device* self, char *message);
	IOTHUB_MESSAGE_RESULT device_set_message_property(struct device* self, char *key, char *value);
	IOTHUB_MESSAGE_RESULT device_set_system_property(struct device* self, char *key, char *value);
	void device_flush(struct device* self);
	void device_on_ack(struct device* self, bool success, char* message_id);
	bool device_wait_for_ack(struct device* self, char* message_id);
	bool device_wait_for_all_acks(struct device* self);
	

	struct ack {
		struct device* device;
		char* message_Id;
	};

	struct device {
		IOTHUB_CLIENT_LL_HANDLE iothub_ll_handle;

		MAP_HANDLE system_properties;
		MAP_HANDLE message_properties;
		MAP_HANDLE message_pending_acks;
		
		IOTHUB_MESSAGE_RESULT (*post_message)(struct device* self, char *message);
		IOTHUB_MESSAGE_RESULT(*send_message)(struct device* self, char *message);

		void (*on_ack)(struct device* self, bool success, char* message_id);
		void(*flush)(struct device* self);
		bool(*wait_for_ack)(struct device* self, char* message_id);
		bool(*wait_for_all_acks)(struct device* self);
		
		void(*on_message_sent)(char *message_id);
		void(*on_message_failed)(char *message_id);

		IOTHUB_MESSAGE_RESULT (*set_message_property)(struct device* self, char *key, char *value);
		IOTHUB_MESSAGE_RESULT (*set_system_property)(struct device* self, char *key, char *value);
	};

	typedef struct device_type {
		struct device * (*create)(char *connectionString);
		void * (*destroy)(struct device * device);
	}tDevice;

	extern const tDevice Device;
	
#ifdef __cplusplus
}
#endif

#endif //AZURE_IOTHUB_LITE_H