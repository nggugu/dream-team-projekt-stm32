#ifndef INC_WIFI_H_
#define INC_WIFI_H_

#include "usart.h"

#include <stdio.h>
#include <string.h>

void WIFI_Init(char *ssid, char *pwd);
void WIFI_SendHttpGetRequest(char *hostname, char *path, char *response);

#endif /* INC_WIFI_H_ */
