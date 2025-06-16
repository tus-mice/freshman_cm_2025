/*
 * PL_lcd.c
 *
 *  Created on: May 16, 2025
 *      Author: KanataWatanabe
 */

#include "stm32l4xx_hal.h"
#include "i2c.h"

#define LCD_ADDRESS 0x7c

void lcd_cmd(uint8_t x)
{
	uint8_t aTxBuffer[2] = {0x00, x};

	while (HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)LCD_ADDRESS, (uint8_t*)aTxBuffer, 2, 1000) != HAL_OK)
	{
		if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
		{
			Error_Handler();
		}
	}
}

void lcd_data(uint8_t x)
{
	uint8_t aTxBuffer[2] = {0x40, x};

	while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)LCD_ADDRESS, (uint8_t*)aTxBuffer, 2, 1000) != HAL_OK)
	{
		if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
		{
			Error_Handler();
		}
	}
}

void pl_lcd_puts(const char *s)
{
	while (*s)lcd_data(*s++);
}

void pl_lcd_init(void)
{
	lcd_cmd(0x38);
	lcd_cmd(0x39);
	lcd_cmd(0x14);
	lcd_cmd(0x70);
	lcd_cmd(0x56);
	lcd_cmd(0x6c);
	HAL_Delay(300);
	lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
	HAL_Delay(2);
}

void pl_lcd_move(uint8_t pos)
{
	lcd_cmd(0x80 | pos);
}

void pl_lcd_pos(uint8_t row, uint8_t col)
{
	lcd_cmd(0x80 | ((row & 0x01) << 6) | col);
}

void pl_lcd_clear()
{
	lcd_cmd(0x01);
	HAL_Delay(2);
}
