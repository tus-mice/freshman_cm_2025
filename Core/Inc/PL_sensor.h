/*
 * PL_sensor.h
 *
 *  Created on: May 16, 2025
 *      Author: KanataWatanabe
 */

#ifndef INC_PL_SENSOR_H_
#define INC_PL_SENSOR_H_

#include "stm32l4xx_hal.h"

extern uint16_t g_ADCBuffer[5];
extern float g_V_Batt;
extern uint16_t g_sensor[4];
void pl_callback_getSensor();
void pl_interupt_getSensor();

#endif /* INC_PL_SENSOR_H_ */
