#include <stdio.h>
#include <stdlib.h>

#include "azure_iot_lite.h"

#pragma region certs
const char certificates[] =
/* DigiCert Baltimore Root */
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\r\n"
"RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\r\n"
"VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\r\n"
"DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\r\n"
"ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\r\n"
"VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\r\n"
"mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\r\n"
"IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\r\n"
"mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\r\n"
"XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\r\n"
"dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\r\n"
"jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\r\n"
"BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\r\n"
"DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\r\n"
"9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\r\n"
"jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\r\n"
"Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\r\n"
"ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\r\n"
"R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\r\n"
"-----END CERTIFICATE-----\r\n"
/*DigiCert Global Root CA*/
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\r\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\r\n"
"QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\r\n"
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\r\n"
"b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\r\n"
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\r\n"
"CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\r\n"
"nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\r\n"
"43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\r\n"
"T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\r\n"
"gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\r\n"
"BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\r\n"
"TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\r\n"
"DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\r\n"
"hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\r\n"
"06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\r\n"
"PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\r\n"
"YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\r\n"
"CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\r\n"
"-----END CERTIFICATE-----\r\n"
/*D-TRUST Root Class 3 CA 2 2009*/
"-----BEGIN CERTIFICATE-----\r\n"
"MIIEMzCCAxugAwIBAgIDCYPzMA0GCSqGSIb3DQEBCwUAME0xCzAJBgNVBAYTAkRF\r\n"
"MRUwEwYDVQQKDAxELVRydXN0IEdtYkgxJzAlBgNVBAMMHkQtVFJVU1QgUm9vdCBD\r\n"
"bGFzcyAzIENBIDIgMjAwOTAeFw0wOTExMDUwODM1NThaFw0yOTExMDUwODM1NTha\r\n"
"ME0xCzAJBgNVBAYTAkRFMRUwEwYDVQQKDAxELVRydXN0IEdtYkgxJzAlBgNVBAMM\r\n"
"HkQtVFJVU1QgUm9vdCBDbGFzcyAzIENBIDIgMjAwOTCCASIwDQYJKoZIhvcNAQEB\r\n"
"BQADggEPADCCAQoCggEBANOySs96R+91myP6Oi/WUEWJNTrGa9v+2wBoqOADER03\r\n"
"UAifTUpolDWzU9GUY6cgVq/eUXjsKj3zSEhQPgrfRlWLJ23DEE0NkVJD2IfgXU42\r\n"
"tSHKXzlABF9bfsyjxiupQB7ZNoTWSPOSHjRGICTBpFGOShrvUD9pXRl/RcPHAY9R\r\n"
"ySPocq60vFYJfxLLHLGvKZAKyVXMD9O0Gu1HNVpK7ZxzBCHQqr0ME7UAyiZsxGsM\r\n"
"lFqVlNpQmvH/pStmMaTJOKDfHR+4CS7zp+hnUquVH+BGPtikw8paxTGA6Eian5Rp\r\n"
"/hnd2HN8gcqW3o7tszIFZYQ05ub9VxC1X3a/L7AQDcUCAwEAAaOCARowggEWMA8G\r\n"
"A1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFP3aFMSfMN4hvR5COfyrYyNJ4PGEMA4G\r\n"
"A1UdDwEB/wQEAwIBBjCB0wYDVR0fBIHLMIHIMIGAoH6gfIZ6bGRhcDovL2RpcmVj\r\n"
"dG9yeS5kLXRydXN0Lm5ldC9DTj1ELVRSVVNUJTIwUm9vdCUyMENsYXNzJTIwMyUy\r\n"
"MENBJTIwMiUyMDIwMDksTz1ELVRydXN0JTIwR21iSCxDPURFP2NlcnRpZmljYXRl\r\n"
"cmV2b2NhdGlvbmxpc3QwQ6BBoD+GPWh0dHA6Ly93d3cuZC10cnVzdC5uZXQvY3Js\r\n"
"L2QtdHJ1c3Rfcm9vdF9jbGFzc18zX2NhXzJfMjAwOS5jcmwwDQYJKoZIhvcNAQEL\r\n"
"BQADggEBAH+X2zDI36ScfSF6gHDOFBJpiBSVYEQBrLLpME+bUMJm2H6NMLVwMeni\r\n"
"acfzcNsgFYbQDfC+rAF1hM5+n02/t2A7nPPKHeJeaNijnZflQGDSNiH+0LS4F9p0\r\n"
"o3/U37CYAqxva2ssJSRyoWXuJVrl5jLn8t+rSfrzkGkj2wTZ51xY/GXUl77M/C4K\r\n"
"zCUqNQT4YJEVdT1B/yMfGchs64JTBKbkTCJNjYy6zltz7GRUUG3RnFX7acM2w4y8\r\n"
"PIWmawomDeCTmGCufsYkl4phX5GOZpIJhzbNi5stPvZR1FDUWSi9g/LMKHtThm3Y\r\n"
"Johw1+qRzT65ysCQblrGXnRl11z+o+I=\r\n"
"-----END CERTIFICATE-----\r\n"
/*WoSign*/
"-----BEGIN CERTIFICATE-----\r\n"
"MIIFdjCCA16gAwIBAgIQXmjWEXGUY1BWAGjzPsnFkTANBgkqhkiG9w0BAQUFADBV\r\n"
"MQswCQYDVQQGEwJDTjEaMBgGA1UEChMRV29TaWduIENBIExpbWl0ZWQxKjAoBgNV\r\n"
"BAMTIUNlcnRpZmljYXRpb24gQXV0aG9yaXR5IG9mIFdvU2lnbjAeFw0wOTA4MDgw\r\n"
"MTAwMDFaFw0zOTA4MDgwMTAwMDFaMFUxCzAJBgNVBAYTAkNOMRowGAYDVQQKExFX\r\n"
"b1NpZ24gQ0EgTGltaXRlZDEqMCgGA1UEAxMhQ2VydGlmaWNhdGlvbiBBdXRob3Jp\r\n"
"dHkgb2YgV29TaWduMIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAvcqN\r\n"
"rLiRFVaXe2tcesLea9mhsMMQI/qnobLMMfo+2aYpbxY94Gv4uEBf2zmoAHqLoE1U\r\n"
"fcIiePyOCbiohdfMlZdLdNiefvAA5A6JrkkoRBoQmTIPJYhTpA2zDxIIFgsDcScc\r\n"
"f+Hb0v1naMQFXQoOXXDX2JegvFNBmpGN9J42Znp+VsGQX+axaCA2pIwkLCxHC1l2\r\n"
"ZjC1vt7tj/id07sBMOby8w7gLJKA84X5KIq0VC6a7fd2/BVoFutKbOsuEo/Uz/4M\r\n"
"x1wdC34FMr5esAkqQtXJTpCzWQ27en7N1QhatH/YHGkR+ScPewavVIMYe+HdVHpR\r\n"
"aG53/Ma/UkpmRqGyZxq7o093oL5d//xWC0Nyd5DKnvnyOfUNqfTq1+ezEC8wQjch\r\n"
"zDBwyYaYD8xYTYO7feUapTeNtqwylwA6Y3EkHp43xP901DfA4v6IRmAR3Qg/UDar\r\n"
"uHqklWJqbrDKaiFaafPz+x1wOZXzp26mgYmhiMU7ccqjUu6Du/2gd/Tkb+dC221K\r\n"
"mYo0SLwX3OSACCK28jHAPwQ+658geda4BmRkAjHXqc1S+4RFaQkAKtxVi8QGRkvA\r\n"
"Sh0JWzko/amrzgD5LkhLJuYwTKVYyrREgk/nkR4zw7CT/xH8gdLKH3Ep3XZPkiWv\r\n"
"HYG3Dy+MwwbMLyejSuQOmbp8HkUff6oZRZb9/D0CAwEAAaNCMEAwDgYDVR0PAQH/\r\n"
"BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFOFmzw7R8bNLtwYgFP6H\r\n"
"EtX2/vs+MA0GCSqGSIb3DQEBBQUAA4ICAQCoy3JAsnbBfnv8rWTjMnvMPLZdRtP1\r\n"
"LOJwXcgu2AZ9mNELIaCJWSQBnfmvCX0KI4I01fx8cpm5o9dU9OpScA7F9dY74ToJ\r\n"
"MuYhOZO9sxXqT2r09Ys/L3yNWC7F4TmgPsc9SnOeQHrAK2GpZ8nzJLmzbVUsWh2e\r\n"
"JXLOC62qx1ViC777Y7NhRCOjy+EaDveaBk3e1CNOIZZbOVtXHS9dCF4Jef98l7VN\r\n"
"g64N1uajeeAz0JmWAjCnPv/So0M/BVoG6kQC2nz4SNAzqfkHx5Xh9T71XXG68pWp\r\n"
"dIhhWeO/yloTunK0jF02h+mmxTwTv97QRCbut+wucPrXnbes5cVAWubXbHssw1ab\r\n"
"R80LzvobtCHXt2a49CUwi1wNuepnsvRtrtWhnk/Yn+knArAdBtaP4/tIEp9/EaEQ\r\n"
"PkxROpaw0RPxx9gmrjrKkcRpnd8BKWRRb2jaFOwIQZeQjdCygPLPwj2/kWjFgGce\r\n"
"xGATVdVhmVd8upUPYUk6ynW8yQqTP2cOEvIo4jEbwFcW3wh8GcF+Dx+FHgo2fFt+\r\n"
"J7x6v+Db9NpSvd4MVHAxkUOVyLzwPt0JfjBkUO1/AaQzZ01oT74V77D2AhGiGxMl\r\n"
"OtzCWfHjXEa7ZywCRuoeSKbmW9m1vFGikpbbqsY3Iqb+zCB0oy2pLmvLwIIRIbWT\r\n"
"ee5Ehr7XHuQe+w==\r\n"
"-----END CERTIFICATE-----\r\n"

;

#pragma endregion

#pragma region helpers

int g_platform_init = false;
static LOCK_HANDLE g_platform_init_lock = NULL;

int get_send_timeout(struct device* device)
{
	const char* timeout;
	bool res;
	if (device && device->system_properties)
		if (Map_ContainsKey(device->system_properties, SEND_TIMEOUT, &res) == MAP_OK && res)
		{
			timeout = Map_GetValueFromKey(device->system_properties, SEND_TIMEOUT);
			if (timeout)
				return atoi(timeout);
		}
	return DEFAULT_SEND_TIMEOUT;
}
void log_error(char * log)
{
	printf(log);
}

char* new_uid()
{
	char* unique_container_id = NULL;
	if ((unique_container_id = (char*)malloc(sizeof(char) * DEFAULT_UNIQUE_ID_LENGTH + 1)) == NULL)
	{
		log_error("Failed allocating Uid");
		return 0;
	}
	else
	{
		memset(unique_container_id, 0, sizeof(char) * DEFAULT_UNIQUE_ID_LENGTH + 1);
		if (UniqueId_Generate(unique_container_id, DEFAULT_UNIQUE_ID_LENGTH) != 0)
		{
			log_error("Failed creating Uid");
			return 0;
		}
	}

	return unique_container_id;
}

const IOTHUB_CLIENT_TRANSPORT_PROVIDER default_Protocol(void)
{
	//hardcoded to amqp for now
	return AMQP_Protocol;
}
#pragma endregion

#pragma region message_type
const tMessage Message = {
	.create = message_type_create,
	.destroy = message_type_destroy,
	.cpy = message_type_copy,
};

void* message_type_copy(struct message *src, struct message **dst) {

	*dst = Message.create(src->message_Id, src->correlation_Id);
	(*dst)->content_type = src->content_type;

	if (src->content_type == IOTHUBMESSAGE_BYTEARRAY)
	{
		(*dst)->data_len = src->data_len;
		(*dst)->data.binary = malloc(src->data_len * sizeof(unsigned char));
		memcpy((*dst)->data.binary, src->data.binary, src->data_len);
	}
	else
	{
		mallocAndStrcpy_s(&((*dst)->data.text), (char *)src->data.text);
	}
	return 0;
}
struct message *message_type_create(const char* messageId, const char* correlationId) {

	struct message *msg = (struct message*) malloc(sizeof(struct message));
	memset(msg, 0, sizeof(*msg));

	if (messageId)
		mallocAndStrcpy_s(&(msg->message_Id), (char *)messageId);

	if (correlationId)
		mallocAndStrcpy_s(&(msg->correlation_Id), (char *)correlationId);

	return msg;
}

void *message_type_destroy(struct message *msg) {

	if (msg)
	{
		if (msg->correlation_Id)
		{
			free(msg->correlation_Id);
			msg->correlation_Id = NULL;
		}
		if (msg->message_Id) {
			free(msg->message_Id);
			msg->message_Id = NULL;
		}
		if (msg->data.text)
		{
			free(msg->data.text);
			msg->data.text = NULL;
		}
	}
	return 0;
}
#pragma endregion

#pragma region device_type
const tDevice Device = {
	.create = device_type_create,
	.destroy = device_type_destroy,
};

struct device *device_type_create(const char *connectionString) {

	//todo: make this static 
	if (g_platform_init_lock == NULL)
		g_platform_init_lock = Lock_Init();
	if (!g_platform_init)
	{
		Lock(g_platform_init_lock);
		if (!g_platform_init)
		{
			if (platform_init() != 0)
			{
				log_error("Failed to initialize the platform.\n");
				//todo: handle this error
				return 0;
			}
			g_platform_init++;
		}
		Unlock(g_platform_init_lock);
	}

	/*create an IoTHub client*/
	IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, default_Protocol());
	if (iotHubClientHandle == NULL)
	{
		log_error("Failure creating IoTHubClient handle");
		//todo: handle this error
		return 0;
	}

	IoTHubClient_LL_SetOption(iotHubClientHandle, OPTION_TRUSTED_CERT, certificates);

	//set the default system values 
	MAP_HANDLE message_pending_acks = Map_Create(NULL);

	//set the default system values 
	MAP_HANDLE system_properties = Map_Create(NULL);
	Map_Add(system_properties, CONTENT_TYPE, DEFAULT_CONTENT_TYPE);
	Map_Add(system_properties, CONTENT_ENCODING, DEFAULT_CONTENT_ENCODING);

	//set the default message values 
	MAP_HANDLE message_properties = Map_Create(NULL);
	LOCK_HANDLE receive_lock_handle = Lock_Init();

	struct device *result = (struct device*)malloc(sizeof(struct device));
	memset(result, 0, sizeof(*result));

	result->iothub_ll_handle = iotHubClientHandle;
	result->system_properties = system_properties;
	result->message_properties = message_properties;

	result->post_message = device_post_message;
	result->send_message = device_send_message;

	result->receive_message = device_receive_message;
	result->set_receive_handler = device_set_receive_handler;

	result->set_message_property = device_set_message_property;
	result->set_system_property = device_set_system_property;
	result->message_pending_acks = message_pending_acks;

	result->wait_for_message_ack = device_wait_for_message_ack;
	result->wait_for_all_acks = device_wait_for_all_acks;

	result->receive_handler = device_receive_handler;

	result->receive_lock_handle = receive_lock_handle;


	if (IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, result->receive_handler, result) != IOTHUB_CLIENT_OK)
	{
		(void)printf("ERROR: IoTHubClient_LL_SetMessageCallback..........FAILED!\r\n");
	}

	result->on_ack = device_on_ack;

	result->flush = device_flush;

	return result;
}

void *device_type_destroy(struct device * device) {

	// Clean up the iothub sdk handle
	IoTHubClient_LL_Destroy(device->iothub_ll_handle);

	Map_Destroy(device->message_properties);
	Map_Destroy(device->system_properties);
	Map_Destroy(device->message_pending_acks);

	Lock_Deinit(device->receive_lock_handle);

	free(device);
	return 0;
}
#pragma endregion

void message_ack(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
	struct ack* ack = (struct ack*)userContextCallback;

	ack->device->on_ack(ack->device, result == IOTHUB_CLIENT_CONFIRMATION_OK, ack->message_Id);

	free(ack->message_Id);
	free(ack);
}


IOTHUBMESSAGE_DISPOSITION_RESULT device_receive_handler(IOTHUB_MESSAGE_HANDLE message, void* user_context) {

	if (user_context == NULL)
	{
		log_error("failed reading ContentType.");
		return IOTHUBMESSAGE_ABANDONED;
	}
	struct device* device = user_context;

	const char* messageId;
	const char* correlationId;

	// Message properties
	messageId = IoTHubMessage_GetMessageId(message);
	correlationId = IoTHubMessage_GetCorrelationId(message);

	struct message* msg = Message.create(messageId, correlationId);

	msg->content_type = IoTHubMessage_GetContentType(message);
	if (msg->content_type == IOTHUBMESSAGE_BYTEARRAY)
	{
		const unsigned char* buff_msg;
		size_t data_len;

		if (IoTHubMessage_GetByteArray(message, &buff_msg, &data_len) != IOTHUB_MESSAGE_OK)
		{
			(void)printf("Failure retrieving byte array message\r\n");
			Message.destroy(msg);
			return IOTHUBMESSAGE_ABANDONED;
		}
		else
		{
			msg->data.binary = malloc(data_len * sizeof(unsigned char));
			memcpy(msg->data.binary, buff_msg, data_len);
			msg->data_len = data_len;
		}
	}
	else
	{
		//if not byte array, it's string
		const char* string_msg = IoTHubMessage_GetString(message);
		if (string_msg == NULL)
		{
			(void)printf("Failure retrieving byte array message\r\n");
			Message.destroy(msg);
			return IOTHUBMESSAGE_ABANDONED;
		}
		else
		{
			mallocAndStrcpy_s(&(msg->data.text), (char *)string_msg);
		}
	}

	Lock(device->receive_lock_handle);
	if (device->last_inbound_message)
		Message.destroy(device->last_inbound_message);

	device->last_inbound_message = msg;

	if (device->receive_user_handle)
		device->receive_user_handle(device->last_inbound_message, device->user_context);

	Unlock(device->receive_lock_handle);

	return IOTHUBMESSAGE_ACCEPTED;
}

IOTHUB_MESSAGE_RESULT device_post_message(struct device *self, const char *message, char **message_id) {

	bool res = true;

	IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(message);

	if (Map_ContainsKey(self->system_properties, CONTENT_TYPE, &res) != MAP_OK || !res
		|| IoTHubMessage_SetContentTypeSystemProperty(message_handle, Map_GetValueFromKey(self->system_properties, CONTENT_TYPE)) != IOTHUB_MESSAGE_OK)
	{
		log_error("failed reading ContentType.");
		return IOTHUB_MESSAGE_ERROR;
	}

	if (Map_ContainsKey(self->system_properties, CONTENT_ENCODING, &res) != MAP_OK || !res
		|| IoTHubMessage_SetContentEncodingSystemProperty(message_handle, Map_GetValueFromKey(self->system_properties, CONTENT_ENCODING)) != IOTHUB_MESSAGE_OK)
	{
		log_error("failed reading ContentEncoding.");
		return IOTHUB_MESSAGE_ERROR;
	}

	//setting the value to NULL will skip this propoerties
	bool has_key = false;
	if (Map_ContainsKey(self->message_properties, MESSAGE_ID, &has_key) == MAP_OK && !has_key)
	{
		char *msg_id = new_uid();
		if (IoTHubMessage_SetMessageId(message_handle, msg_id) != IOTHUB_MESSAGE_OK)
		{
			log_error("failed setting the MESSAGE_ID.");
			return IOTHUB_MESSAGE_ERROR;
		}
		free(msg_id);
	}

	if (Map_ContainsKey(self->message_properties, CORRELATION_ID, &has_key) == MAP_OK && !has_key)
	{
		char *correlation_id = new_uid();
		if (IoTHubMessage_SetCorrelationId(message_handle, correlation_id) != IOTHUB_MESSAGE_OK)
		{
			log_error("failed setting the CORRELATION_ID.");
			return IOTHUB_MESSAGE_ERROR;
		}
		free(correlation_id);
	}

	const char* const* propertyKeys;
	const char* const* propertyValues;
	size_t propertyCount;

	if (Map_GetInternals(self->message_properties, &propertyKeys, &propertyValues, &propertyCount) != MAP_OK)
	{
		log_error("failed getting message properties details.");
		return IOTHUB_MESSAGE_ERROR;
	}

	MAP_HANDLE propMap = IoTHubMessage_Properties(message_handle);

	for (size_t i = 0; i < propertyCount; i++)
	{
		if (strcmp(propertyKeys[i], MESSAGE_ID))
		{
			if (IoTHubMessage_SetMessageId(message_handle, propertyValues[i]) != IOTHUB_MESSAGE_OK)
			{
				log_error("failed setting the MESSAGE_ID.");
				return IOTHUB_MESSAGE_ERROR;
			}
		}
		if (strcmp(propertyKeys[i], CORRELATION_ID))
		{
			if (IoTHubMessage_SetCorrelationId(message_handle, propertyValues[i]) != IOTHUB_MESSAGE_OK)
			{
				log_error("failed setting the CORRELATION_ID.");
				return IOTHUB_MESSAGE_ERROR;
			}
		}
		else
			if (Map_AddOrUpdate(propMap, propertyKeys[i], propertyValues[i]) != MAP_OK)
			{
				log_error("failed getting message properties details.");
				return IOTHUB_MESSAGE_ERROR;
			}
	}

	char strTime[50];
	time_t rawtime;

	const char *message_Id = IoTHubMessage_GetMessageId(message_handle);

	time(&rawtime);
	sprintf(strTime, "%d", (int)rawtime);

	Map_AddOrUpdate(self->message_pending_acks, message_Id, strTime);

	struct ack* ack = (struct ack*) malloc(sizeof(struct ack));
	ack->device = self;
	mallocAndStrcpy_s(&(ack->message_Id), (char *)message_Id);

	if (message_id)
		*message_id = ack->message_Id;

	IoTHubClient_LL_SendEventAsync(self->iothub_ll_handle, message_handle, message_ack, (void *)ack);

	IoTHubMessage_Destroy(message_handle);

	return IOTHUB_MESSAGE_OK;
}

IOTHUB_MESSAGE_RESULT device_send_message(struct device *self, const char *message)
{
	char* message_id;
	IOTHUB_MESSAGE_RESULT result = self->post_message(self, message, &message_id);
	if (result != IOTHUB_MESSAGE_OK)
	{
		log_error("Failed to post message");
		return result;
	}

	while (self->wait_for_message_ack(self, message_id)) {

		//flush the upstream/downstream network buffers
		self->flush(self);

		//wait for the server to ack
		ThreadAPI_Sleep(1);
	}
	return result;
}

IOTHUB_MESSAGE_RESULT device_receive_message(struct device *self, struct message** msg)
{
	while (Lock(self->receive_lock_handle) == LOCK_OK) {

		if (self->last_inbound_message == NULL)
			Unlock(self->receive_lock_handle);
		else
		{
			Message.cpy(self->last_inbound_message, msg);

			Message.destroy(self->last_inbound_message);
			self->last_inbound_message = NULL;

			Unlock(self->receive_lock_handle);
			return IOTHUB_MESSAGE_OK;
		}

		//flush the upstream/downstream network buffers
		self->flush(self);

		//wait for the server to ack
		ThreadAPI_Sleep(1);
	}

	return IOTHUB_MESSAGE_ERROR;
}

void device_on_ack(struct device* self, bool success, const char* message_id)
{
	if (success && self->on_message_sent)
		self->on_message_sent(message_id);

	else if (!success && self->on_message_failed)
		self->on_message_failed(message_id);

	bool key_exists = false;
	if (message_id && Map_ContainsKey(self->message_pending_acks, message_id, &key_exists) != MAP_OK || key_exists)
		if (Map_Delete(self->message_pending_acks, message_id) != MAP_OK)
			log_error("Could not remove a message from the pending ack list");

}

bool device_wait_for_all_acks(struct device* self)
{
	const char* const* propertyKeys;
	const char* const* propertyValues;
	size_t propertyCount;

	if (Map_GetInternals(self->message_pending_acks, &propertyKeys, &propertyValues, &propertyCount) != MAP_OK)
	{
		log_error("failed getting message properties details.");
		return IOTHUB_MESSAGE_ERROR;
	}

	time_t now;
	time(&now);

	for (size_t i = 0; i < propertyCount; i++)
	{
		time_t message_sent = (time_t)atoi(propertyValues[i]);
		if (now - message_sent < get_send_timeout(self))
			return true;
	}
	return false;
}

bool device_wait_for_message_ack(struct device* self, const char* message_id)
{
	bool key_exists = false;

	if (message_id && Map_ContainsKey(self->message_pending_acks, message_id, &key_exists) != MAP_OK || key_exists)
	{
		time_t now;
		time(&now);

		const char* value = Map_GetValueFromKey(self->message_pending_acks, message_id);
		time_t message_sent = (time_t)atoi(value);
		if (now - message_sent < get_send_timeout(self))
			return true;

	}
	return false;
}

IOTHUB_MESSAGE_RESULT device_set_message_property(struct device* self, const char *key, const char *value) {
	if (Map_AddOrUpdate(self->message_properties, key, value) != MAP_OK)
	{
		log_error("failed setting message property.");
		return IOTHUB_MESSAGE_ERROR;
	}
	return IOTHUB_MESSAGE_OK;
}

IOTHUB_MESSAGE_RESULT device_set_system_property(struct device* self, const char *key, const char *value) {
	if (Map_AddOrUpdate(self->system_properties, key, value) != MAP_OK)
	{
		log_error("failed setting system property.");
		return IOTHUB_MESSAGE_ERROR;
	}
	return IOTHUB_MESSAGE_OK;
}

IOTHUB_MESSAGE_RESULT device_set_receive_handler(struct device* self, receive_message_handler callback, void* user_context)
{
	Lock(self->receive_lock_handle);

	self->receive_user_handle = callback;
	self->user_context = user_context;

	Unlock(self->receive_lock_handle);
	return IOTHUB_MESSAGE_OK;
}

void device_flush(struct device* self) {

	IoTHubClient_LL_DoWork(self->iothub_ll_handle);
}
