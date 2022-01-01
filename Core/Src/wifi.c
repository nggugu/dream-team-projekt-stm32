#include "wifi.h"


void WIFI_Init(char *ssid, char *pwd) {
	USART1_ClearBuffer();

	// reset
	USART1_SendString("AT+RST\r\n", (uint16_t) strlen("AT+RST\r\n"));
	HAL_Delay(7000);
	USART1_ClearBuffer();

	// iskljuci echo (radi lakseg debugginga)
	USART1_SendString("ATE0\r\n", (uint16_t) strlen("ATE0\r\n"));
	while(!USART1_RxBufferContains("OK\r\n")) ;
	USART1_ClearBuffer();

	// postavi Station mod
	USART1_SendString("AT+CWMODE=1\r\n", (uint16_t) strlen("AT+CWMODE=1\r\n"));
	while(!USART1_RxBufferContains("OK\r\n")) ;
	USART1_ClearBuffer();

	// spoji se na mrezu
	char cwjap_cmd[strlen(ssid) + strlen(pwd) + 17];
	sprintf(cwjap_cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pwd);
	USART1_SendString(cwjap_cmd, (uint16_t) strlen(cwjap_cmd));
	while(!USART1_RxBufferContains("OK\r\n")) ;
	USART1_ClearBuffer();

}

void WIFI_SendHttpGetRequest(char *hostname, char *path, char *response) {
	USART1_ClearBuffer();

	char cipstart_cmd[strlen(hostname) + 26];
	sprintf(cipstart_cmd, "AT+CIPSTART=\"TCP\",\"%s\",80\r\n", hostname);

	USART1_SendString(cipstart_cmd, (uint16_t) strlen(cipstart_cmd));
	while(!USART1_RxBufferContains("OK\r\n")) ;
	USART1_ClearBuffer();

	char req[strlen(hostname) + strlen(path) + 26];
	sprintf(req, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path, hostname);

	char send_cmd[17];
	sprintf(send_cmd, "AT+CIPSEND=%d\r\n", strlen(req));

	USART1_SendString(send_cmd, strlen(send_cmd));
	while(!USART1_RxBufferContains("OK\r\n")) ;
	USART1_ClearBuffer();

	USART1_SendString(req, strlen(req));
	while(!USART1_RxBufferContains("OK\r\n")) ;
	USART1_ClearBuffer();

	// znak } oznacava kraj odgovora jer ocekujemo da cemo dobiti JSON u tijelu
	while(!USART1_RxBufferContains("}\n")) ;

	USART1_GetBufferContent(response);
}


