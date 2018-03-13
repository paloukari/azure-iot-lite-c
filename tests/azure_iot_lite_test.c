// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
#include <stdio.h>
#include <stdlib.h>

#include "azure_iot_lite.h"


int main()
{
	//create the device
	struct device * mxchip = Device.create("<<YOUR DEVICE CONNECtION STRING>>");
	
	//post the telemetry payload
	mxchip->post_message(mxchip, "TelemetryData");
	
	while (mxchip->wait_for_all_acks(mxchip)) {

		//flush the upstream/downstream network buffers
		mxchip->flush(mxchip);

		//wait for the server to ack
		ThreadAPI_Sleep(1);
	}
	
	Device.destroy(mxchip);
}