# azure-iot-lite-c
The Azure IoT Lite C is a thin library on top of the official Microsoft Azure C SDK that greatly simplifies Azure IoT development in C

## Quickstart

TODO: add the setup readme here

**Samples:**

1. Sending a D2C message:

    ```
    //create the device
	struct device *mxchip = Device.create(CONNECTION_STRING);
	//post the telemetry payload
	mxchip->send_message(mxchip, "Some Telemetry data testing send..");
    //destroy the device
	Device.destroy(mxchip);
    ```
1. Posting a D2C message (non blocking call):
    ```
    //create the device
	struct device * mxchip = Device.create(CONNECTION_STRING);

	char* message_id;
	//post the telemetry payload
	mxchip->post_message(mxchip, "Some Telemetry data testing post..", &message_id);
	
	while (mxchip->wait_for_ack(mxchip, message_id)) {

		//flush the upstream/downstream network buffers
		mxchip->flush(mxchip);

		//wait for the server to ack
		ThreadAPI_Sleep(1);
	}
    //destroy the device
	Device.destroy(mxchip);
    ```