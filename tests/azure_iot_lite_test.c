#include <stdio.h>
#include <stdlib.h>

#include "connection_string.h"

#include "azure_iot_lite.h"

void test_multiple_post_messages();
void test_post_message();
void test_send_message();
void test_receive_message();
void test_receive_message_handler();

int main()
{	
	test_send_message();
	test_post_message();
	test_multiple_post_messages();

	test_receive_message();
	test_receive_message_handler();
}


void test_send_message() {
	//create the device
	struct device *mxchip = Device.create(CONNECTION_STRING);
	//send the telemetry payload
	mxchip->send_message(mxchip, "Some Telemetry data testing send..");

	Device.destroy(mxchip);
}

void test_post_message() {
	//create the device
	struct device * mxchip = Device.create(CONNECTION_STRING);

	char* message_id;
	//post the telemetry payload
	IOTHUB_MESSAGE_RESULT result = mxchip->post_message(mxchip, "Some Telemetry data testing post..", &message_id);
	if (result != IOTHUB_MESSAGE_OK)
	{
		printf("Failed to post message");
		return;
	}

	while (mxchip->wait_for_message_ack(mxchip, message_id)) {

		//flush the upstream/downstream network buffers
		mxchip->flush(mxchip);

		//wait for the server to ack
		ThreadAPI_Sleep(1);
	}

	Device.destroy(mxchip);
}

void test_multiple_post_messages() {
	//create the device
	struct device * mxchip = Device.create(CONNECTION_STRING);

	//post the telemetry payload
	mxchip->post_message(mxchip, "Some Telemetry data..", NULL);
	mxchip->post_message(mxchip, "..some more..", NULL);
	mxchip->post_message(mxchip, "..final packet!", NULL);

	while (mxchip->wait_for_all_acks(mxchip)) {

		//flush the upstream/downstream network buffers
		mxchip->flush(mxchip);

		//wait for the server to ack
		ThreadAPI_Sleep(1);
	}

	Device.destroy(mxchip);
}

void test_receive_message() {
	
	//create the device
	struct device * mxchip = Device.create(CONNECTION_STRING);
	
	//the pointer of the new incoming message
	struct message* msg;

	//receive an inbound message
	mxchip->receive_message(mxchip, &msg);

	//destroy the device
	Device.destroy(mxchip);
}

void *message_handler(struct message* message, void* user_context) {
	(void)message;
	(void)user_context;
	return 0;
}
void test_receive_message_handler() {
	//create the device
	struct device * mxchip = Device.create(CONNECTION_STRING);
	
	mxchip->set_receive_handler(mxchip, message_handler, "context");

	//receive an inbound message
	mxchip->receive_message(mxchip, NULL);

	//destroy the device
	Device.destroy(mxchip);
}