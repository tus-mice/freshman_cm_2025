/*
 * PL_lcd.h
 *
 *  Created on: May 16, 2025
 *      Author: KanataWatanabe
 */

#ifndef INC_PL_LCD_H_
#define INC_PL_LCD_H_

void lcd_cmd(uint8_t);
void lcd_data(uint8_t);
void pl_lcd_puts(const char*);
void pl_lcd_init(void);
void pl_lcd_move(uint8_t);
void pl_lcd_pos(uint8_t, uint8_t);
void pl_lcd_clear(void);

#endif /* INC_PL_LCD_H_ */
