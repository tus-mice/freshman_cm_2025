/*
 * PL_sensor.c
 *
 *  Created on: May 16, 2025
 *      Author: KanataWatanabe
 */

#include "PL_sensor.h"
#include "adc.h"
#include "stm32l4xx_hal.h"

uint16_t g_ADCBuffer[5];

char AD_step;

uint16_t g_sensor_on[4];
uint16_t g_sensor_off[4];
uint16_t g_sensor[4];

float g_V_Batt;

void pl_callback_getSensor(void)
{
	uint16_t V_battAD;

	int i, j;
	HAL_ADC_Stop_DMA(&hadc1);
	switch (AD_step)
	{
	case 0:
		HAL_GPIO_WritePin(SENSORLED_1_GPIO_Port, SENSORLED_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SENSORLED_2_GPIO_Port, SENSORLED_2_Pin, GPIO_PIN_RESET);

		for (j=0; j <= 500; j ++)
		{
		}
		break;

	case 1:
		g_sensor_on[0] = g_ADCBuffer[1];
		g_sensor_on[1] = g_ADCBuffer[2];
		g_sensor_off[2] = g_ADCBuffer[3];
		g_sensor_off[3] = g_ADCBuffer[4];

		HAL_GPIO_WritePin(SENSORLED_1_GPIO_Port, SENSORLED_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSORLED_2_GPIO_Port, SENSORLED_2_Pin, GPIO_PIN_SET);

		for (j=0; j <= 500; j++)
		{
		}
		break;

	case 2:
		g_sensor_off[0] = g_ADCBuffer[1];
		g_sensor_off[1] = g_ADCBuffer[2];
		g_sensor_on[2] = g_ADCBuffer[3];
		g_sensor_on[3] = g_ADCBuffer[4];

		HAL_GPIO_WritePin(SENSORLED_1_GPIO_Port, SENSORLED_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSORLED_2_GPIO_Port, SENSORLED_2_Pin, GPIO_PIN_RESET);

		for (j=0; j <= 500; j++)
		{
		}
		break;
	}

	V_battAD = g_ADCBuffer[0];
	g_V_Batt = 3.3 * (float)V_battAD / (float)(4056 - 1) * (100.0 + 22.0) / 22.0;
	AD_step ++;

	if (AD_step != 3)
	{
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)g_ADCBuffer, sizeof(g_ADCBuffer) / sizeof(uint16_t));
	}
	else
	{
		AD_step = 0;
		for(i=0;i<4;i++){
			g_sensor[i] = g_sensor_on[i] - g_sensor_off[i];
		}
	}
}

void pl_interupt_getSensor(void){

		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)g_ADCBuffer,
				sizeof(g_ADCBuffer) / sizeof(uint16_t));


}
