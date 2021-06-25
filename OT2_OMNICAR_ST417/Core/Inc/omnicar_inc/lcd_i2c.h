/*
 * lcd_i2c.h
 *
 *  Created on: Jun 10, 2021
 *      Author: TEAM OMNICAR
 */

#ifndef INC_OMNICAR_INC_LCD_I2C_H_
#define INC_OMNICAR_INC_LCD_I2C_H_

#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* LCD Commands - USE */
#define LCD_CLEARDISPLAY    0x01
#define LCD_FUNCTIONSET     0x38
#define LCD_DISPLAYON		0x0C// Display ON, Cursor ON, Blink ON
#define LCD_ENTRYMODESET    0x06

#define LCD_RETURNHOME      0x02
#define LCD_DISPLAYCONTROL  0x08
#define LCD_CURSORSHIFT     0x10
#define LCD_SETCGRAMADDR    0x40
#define LCD_SETDDRAMADDR    0x80

/* Commands bitfields */
//1) Entry mode Bitfields
#define LCD_ENTRY_SH      0x01
#define LCD_ENTRY_ID      0x02
//2) Display control
#define LCD_DISPLAY_B     0x01
#define LCD_DISPLAY_C     0x02
#define LCD_DISPLAY_D     0x04
//3) Shift control
#define LCD_SHIFT_RL      0x04
#define LCD_SHIFT_SC      0x08
//4) Function set control
#define LCD_FUNCTION_F    0x04
#define LCD_FUNCTION_N    0x08
#define LCD_FUNCTION_DL   0x10

/* I2C Control bits */
#define LCD_RS        (1 << 0)
#define LCD_RW        (1 << 1)
#define LCD_EN        (1 << 2)
#define LCD_BK_LIGHT  (1 << 3)

/* Library variables */
#define LCD_I2C_SLAVE_ADDRESS_0  0x78

bool lcd_i2c_init(I2C_HandleTypeDef *pI2cHandle);

void lcd_i2c_sendCommand(uint8_t command);

void lcd_i2c_sendCommand_Add(uint8_t add);

void lcd_i2c_sendData(uint8_t data);

void lcd_i2c_printf(const char* str, ...);

void lcd_i2c_text_placement();

void lcd_i2c_bat0T1_state(uint8_t *tab_ack);

void lcd_i2c_bat0T2_state(uint8_t batOT2);

void lcd_i2c_power_state(uint8_t btn_state);

#endif /* INC_OMNICAR_INC_LCD_I2C_H_ */
