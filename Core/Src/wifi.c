#include "wifi.h"


int8_t WIFI_Init(char *ssid, char *pwd) {
	USART1_ClearBuffer();

	// reset ESP modula - uglavnom nije potreban, ali ako bude potrebe,
	// otkomentiraj sljedece linije:

	// USART1_SendString("AT+RST\r\n", (uint16_t) strlen("AT+RST\r\n"));
	// HAL_Delay(7000);
	// USART1_ClearBuffer();

	// iskljuci echo (radi lakseg debugginga)
	USART1_SendString("ATE0\r\n", (uint16_t) strlen("ATE0\r\n"));

	if (USART1_WaitFor("OK\r\n", "ERROR\r\n", 5000) == -1) {
		USART1_ClearBuffer();
		return -1;
	}
	USART1_ClearBuffer();

	// postavi Station mod
	USART1_SendString("AT+CWMODE=1\r\n", (uint16_t) strlen("AT+CWMODE=1\r\n"));

	if (USART1_WaitFor("OK\r\n", "ERROR\r\n", 1000) == -1) {
		USART1_ClearBuffer();
		return -1;
	}
	USART1_ClearBuffer();

	// spoji se na mrezu
	char cwjap_cmd[strlen(ssid) + strlen(pwd) + 17];
	sprintf(cwjap_cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pwd);
	USART1_SendString(cwjap_cmd, (uint16_t) strlen(cwjap_cmd));

	if (USART1_WaitFor("OK\r\n", "FAIL\r\n", 10000) == -1) {
		USART1_ClearBuffer();
		return -1;
	}
	USART1_ClearBuffer();

	return 0;

}

int8_t WIFI_SendRequestWithParams(char *hostname, char *path, double temp, double moisture, double humidity, double waterLevel) {
	USART1_ClearBuffer();

	char cipstart_cmd[strlen(hostname) + 26];
	sprintf(cipstart_cmd, "AT+CIPSTART=\"TCP\",\"%s\",80\r\n", hostname);

	USART1_SendString(cipstart_cmd, (uint16_t) strlen(cipstart_cmd));

	if (USART1_WaitFor("OK\r\n", "ERROR\r\n", 1000) == -1) {
		USART1_ClearBuffer();
		return -1;
	}
	USART1_ClearBuffer();

	char req[strlen(path) + strlen(hostname) + 4 * 5 + strlen("GET ?instant_temperature=&instant_moisture=&instant_humidity=&instant_water= HTTP/1.1\r\nHost: \r\n\r\n")];
	sprintf(req, "GET %s?instant_temperature=%.0lf&instant_moisture=%.0lf&instant_humidity=%.0lf&instant_water=%.0lf HTTP/1.1\r\nHost: %s\r\n\r\n", \
			path, temp, moisture, humidity, waterLevel, hostname);

	char send_cmd[17];
	sprintf(send_cmd, "AT+CIPSEND=%d\r\n", strlen(req));

	USART1_SendString(send_cmd, strlen(send_cmd));

	if (USART1_WaitFor("OK\r\n", "ERROR\r\n", 1000) == -1) {
		USART1_ClearBuffer();
		return -1;
	}
	USART1_ClearBuffer();

	USART1_SendString(req, strlen(req));

	if (USART1_WaitFor("OK\r\n", "ERROR\r\n", 1000) == -1) {
		USART1_ClearBuffer();
		return -1;
	}
	USART1_ClearBuffer();

	int8_t ret = USART1_WaitForTrueOrFalse("ERROR\r\n", 10000);

	USART1_ClearBuffer();

	return ret;
}
