# azure-iot-lite-c
The Azure IoT Lite C is a thin library on top of the official Microsoft Azure C SDK that greatly simplifies Azure IoT development in C

## Quickstart

1. In Visual Studio, create an empty C++ Project
1. Install the **azure-iot-lite-c** library Nuget Package:

	`Install-Package Paloukari.Azure.IoT.Lite.C`
1. Add a new `main.c` file 
1. Include the single required header

	`#include "azure_iot_lite.h"`
1. Define an empty main
	```
	int main()
	{

	}
	```
1. Pick one of the examples bellow to test out. 
*The complete code for sending a telemetry message looks like this:*
		
	```
	#include "azure_iot_lite.h"

	int main()
	{
		//create the device
		struct device *mxchip = Device.create("your device connection string");
		//post the telemetry payload
		mxchip->send_message(mxchip, "Some Telemetry data testing send..");
		//destroy the device
		Device.destroy(mxchip);
	}
	```
	
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