/*
 * sh.c
 *
 *  Created on: Jan 5, 2022
 *      Author: gugu
 */

/*
 * INCLUDES
 */
#include "sh.h"

/*
 * INITIALISATION
 */
void SH_init(SH *dev, ADC_HandleTypeDef *ADC_handle) {
	dev->ADC_handle = ADC_handle;
}

/*
 * DATA ACQUISITION
 */
uint8_t SH_ReadData(SH *dev) {
	uint8_t errNum = 0;
	HAL_StatusTypeDef status;

	status = HAL_ADC_Start(dev->ADC_handle);
	errNum += (status != HAL_OK);

	status = HAL_ADC_PollForConversion(dev->ADC_handle, HAL_MAX_DELAY);
	errNum += (status != HAL_OK);

	dev->ADC_data = HAL_ADC_GetValue(dev->ADC_handle);
	HAL_ADC_Stop(dev->ADC_handle);
	errNum += (status != HAL_OK);

	if (dev->ADC_data >= 3155) {
		dev->soilHumidity = 0.0;
	} else if (dev->ADC_data <= 986) {
		dev->soilHumidity = 100.0;
	} else {
		dev->soilHumidity = (-50.0/1101.0)*(dev->ADC_data - 3155.0);
	}

	return errNum;
}
