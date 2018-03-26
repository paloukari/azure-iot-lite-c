# azure-iot-lite-c
The Azure IoT Lite C is a thin library on top of the official Microsoft Azure C SDK that greatly simplifies Azure IoT development in C

## Quickstart

1. In Visual Studio, create an empty C++ Project
1. Install the **azure-iot-lite-c** library Nuget Package:

	`Install-Package Paloukari.Azure.IoT.Lite.C`
1. Add a new `main.c` file 
1. Include the single required header

	`#include "azure_iot_lite.h"`

1. Add the bellow libraries in the Input of the Library properties of your project

    `rpcrt4.lib;crypt32.lib;advapi32.lib`
1. Define an empty main
    ```
	int main()
	{

	}
	```
1. Pick one of the examples bellow to test out. 
	#### The complete code for sending a telemetry message looks like this:
		
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

   In this example, `send_message` will block execution until the message has been sent and the server acknowledgement has been received.

    ```
    //create the device
	struct device *mxchip = Device.create(CONNECTION_STRING);
	//post the telemetry payload
	mxchip->send_message(mxchip, "Some Telemetry data testing send..");
    //destroy the device
	Device.destroy(mxchip);
    ```

   
1. Posting a D2C message (non blocking call):

   In this example, `post_message` will enqueue a new message in the outbound queue without blocking the thread. When you call `flush`, all messages in the outbound queue will be sent and all incoming network traffic will be processed and put in the inbound queue.
   
   This pattern is more complicated than the `send_message` example, but is more useful for single threaded applications that need to have an 'async' behavior.

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