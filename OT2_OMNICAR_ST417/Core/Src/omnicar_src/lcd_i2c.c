/*
 * lcd_i2c.c
 *
 *  Created on: May 8, 2021
 *      Author: TEAM OMNICAR
 */

#include "omnicar_inc/lcd_i2c.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Library variables */
static I2C_HandleTypeDef lcd_i2cHandle;
static uint8_t LCD_I2C_SLAVE_ADDRESS = 0;				// declaration of static data for the Slave Address

/* SEND COMMAND */
void lcd_i2c_sendCommand(uint8_t command)
{
	uint8_t tab[2] =																	// declaration of a table of 2 cells
	{
		0x00,																			// Control byte (0x00)
		command,																		// Command passed as parameter of the function
	};

	HAL_I2C_Master_Transmit(&lcd_i2cHandle, LCD_I2C_SLAVE_ADDRESS, tab, 2, 200);		// Transmit the table with I2C communication
}

/* SEND DATA */
void lcd_i2c_sendData(uint8_t data)
{
  uint8_t tab[2] =																		// Declaration of a table of 2 cells
  {
		  0x40,																			// Control byte (0x40)
		  data,																			// Command passed as parameter of the function
  };
  HAL_I2C_Master_Transmit(&lcd_i2cHandle, LCD_I2C_SLAVE_ADDRESS, tab, 2, 200);			// Transmit the table with I2C communication
}

/* INIT */
bool lcd_i2c_init(I2C_HandleTypeDef *pI2cHandle)
{
	HAL_Delay(50);																				// Delay of 50ms
	lcd_i2cHandle = *pI2cHandle;																// Store the struct managing the I2C
	if(HAL_I2C_IsDeviceReady(&lcd_i2cHandle, LCD_I2C_SLAVE_ADDRESS_0, 5, 500) != HAL_OK)		// Check if the slave is not ready for communicate
	{
	return false;											// if it is not ready, return false (don't start the communication)
	}
	else
	{
	LCD_I2C_SLAVE_ADDRESS = LCD_I2C_SLAVE_ADDRESS_0;		// Store the value of the macro LCD_I2C_SLAVE_ADDRESS_0 (0x78) into LCD_I2C_SLAVE_ADDRESS
	}

	HAL_Delay(45);											// Delay of 45 ms
	lcd_i2c_sendCommand(LCD_FUNCTIONSET);					// Call function for send LCD_FUNCTIONSET

	HAL_Delay(1);											// Delay of 1 ms
	lcd_i2c_sendCommand(LCD_DISPLAYON);						// Call function for send LCD_DISPLAYON

	HAL_Delay(1);											// Delay of 1 ms
	lcd_i2c_sendCommand(LCD_CLEARDISPLAY);					// Call function for send LCD_CLEARDISPLAY

	HAL_Delay(10);											// Delay of 10 ms
	lcd_i2c_sendCommand(LCD_ENTRYMODESET);					// Call function for send LCD_ENTRYMODESET

	HAL_Delay(1);											// Delay of 1 ms

	return true;											// Return true if the initialization of the LCD has been completed
}

void lcd_i2c_printf(const char* str, ...)
{
  char stringArray[20];										// declaration of a array of 20 elements
  va_list args;												//
  va_start(args, str);										//
  vsprintf(stringArray, str, args);							//
  va_end(args);												//
  for(uint8_t i=0; i<strlen(stringArray) && i<20; i++)		// condition made for "i" from 0 to 5
  {
    lcd_i2c_sendData((uint8_t)stringArray[i]);				//
  }
}


void lcd_i2c_sendCommand_Add(uint8_t add)
{
	uint8_t address = LCD_SETDDRAMADDR | add;												// mask address passed in agurment with LCD_SETDDRAMADDR
	uint8_t tab[2] =																		// Declaration of a table of 2 cells
	{
			0x00,																			// Control byte (0x00)
			address,																		// Command passed as parameter of the function
	};
	HAL_I2C_Master_Transmit(&lcd_i2cHandle, LCD_I2C_SLAVE_ADDRESS, tab, 2, 200);			// Transmit the table with I2C communication
}


/* AFFICHE TEXTE NE BOUGEANT PAS LORS DE L'UTILISATION*/
void lcd_i2c_text_placement()
{
    lcd_i2c_printf("OT1:");												// function call for display 'OT1'
    lcd_i2c_sendCommand_Add(0x08);										// function call for move the cursor into a address passed a parameter (0x08)
    lcd_i2c_sendData(0x25);												// function call for display '%'
    lcd_i2c_sendCommand_Add(0x54);										// function call for move the cursor into a address passed a parameter (0x54)
    lcd_i2c_printf("OT2:");												// function call for display 'OT2'
    lcd_i2c_sendCommand_Add(0x5C);										// function call for move the cursor into a address passed a parameter (0x5C)
    lcd_i2c_sendData(0x25);												// function call for display '%'
    lcd_i2c_sendCommand_Add(0x62);										// function call for move the cursor into a address passed a parameter (0x62)
    lcd_i2c_printf("P:");												// function call for display 'P'
    lcd_i2c_sendCommand_Add(0x66);										// function call for move the cursor into a address passed a parameter (0x66)
    lcd_i2c_printf("/4");												// function call for display '/4'
    lcd_i2c_sendCommand_Add(0x0C);										// function call for move the cursor into a address passed a parameter (0x0C)
    lcd_i2c_printf("V:");												// function call for display 'V'
    lcd_i2c_sendCommand_Add(0x10);										// function call for move the cursor into a address passed a parameter (0x10)
    lcd_i2c_printf("KM/H");												// function call for display 'KM/H'
}

void lcd_i2c_power_state(uint8_t btn_state)
{
	uint8_t address = LCD_SETDDRAMADDR | 0x65;							// mask address 0x65 with LCD_SETDDRAMADDR
	uint8_t tab[4] =													// declaration of a table of 4 cells
	{
			0x80,														// control byte (0x80)
			address,													// command passed as parameter of the function
			0x40,								    					// control byte (0x40)
			btn_state,													// command passed as parameter of the function
	};

	switch(btn_state)
	{
		case 0: 	tab[3] = '0';										// If btn_state equal 0 ->  store 0 into the fourth case of tab
					break;
		case 4: 	tab[3] = '1';										// If btn_state equal 4 ->  store 1 into the fourth case of tab
					break;
		case 8: 	tab[3] = '2';										// If btn_state equal 8 ->  store 2 into the fourth case of tab
					break;
		case 12: 	tab[3] = '3';										// If btn_state equal 12 -> store 3 into the fourth case of tab
					break;
		case 16: 	tab[3] = '4';										// If btn_state equal 16 -> store 4 into the fourth case of tab
					break;
	}
	HAL_I2C_Master_Transmit(&lcd_i2cHandle, LCD_I2C_SLAVE_ADDRESS, tab, 4, 200);		// Transmit the table with I2C communication
}


void lcd_i2c_bat0T1_state(uint8_t *tab_ack)
{
	uint8_t address = LCD_SETDDRAMADDR | 0x05;							// mask address 0x05 with LCD_SETDDRAMADDR
	uint8_t tab[4] =
	{
			0x80,														// control byte (0x80)
			address,													// address masked before
			0x40,														// control byte (0x40)
			(int)tab_ack[0],											// check battery data into tab_ack[0]
	};

	HAL_I2C_Master_Transmit(&lcd_i2cHandle, LCD_I2C_SLAVE_ADDRESS, tab, 4, 200);		// Transmit the table with I2C communication
}

void lcd_i2c_bat0T2_state(uint8_t batOT2)
{
	uint8_t address = LCD_SETDDRAMADDR | 0x59;							// mask address 0x59 with LCD_SETDDRAMADDR
	uint8_t tab[4] =
	{
			0x80,														// control byte (0x80)
			address,													// address masked before
			0x40,														// control byte (0x40)
			(int)batOT2,												// store battery percentage passed in parameters of the function
	};

	HAL_I2C_Master_Transmit(&lcd_i2cHandle, LCD_I2C_SLAVE_ADDRESS, tab, 4, 200);		// Transmit the table with I2C communication
}
