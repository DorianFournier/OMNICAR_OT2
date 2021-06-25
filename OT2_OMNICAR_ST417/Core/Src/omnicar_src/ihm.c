/*
 * ihm.c
 *
 *  Created on: May 7, 2021
 *      Author: TEAM OMNICAR
 */
#include "omnicar_inc/ihm.h"					// include header file
#include "stm32f4xx_hal.h"   					// change this according to your STM32 series
#include <stdlib.h>								// include standard library
#include <stdio.h>								// include standard library
#include <stdbool.h>							// include standard library to use boolean
#include <string.h>								// include standard library to use string

//*** IHM variables declaration ***//
/* Tab ACK placement */
/*	[0] : XY-axis & Rotation	-> H, B, G, D, a, b, c, d, N, R, L
 * 	[1] : Speed button			-> 0 : 0% / 5 : 25% / 10 : 50% / 15 : 75% / 20 : 100%
 * 	[2] : Buzzer				-> 1 or 0
 */
static uint16_t VRx;							// data for x-axis joystick
static uint16_t VRy;							// data for y-axis joystick

static GPIO_TypeDef *PWR_PORT;					// declaration of static GPIO_TypeDef to store the GPIO POWER PORT
static uint16_t PWR_UP_PIN;						// declaration of static data for Power Up button
static uint16_t PWR_DOWN_PIN;					// declaration of static data for Power Down button

static GPIO_TypeDef *ROTA_PORT;					// declaration of static GPIO_TypeDef to store the GPIO ROTA PORT
static uint16_t ROTA_LEFT_PIN;					// declaration of static data for Rotation Left button
static uint16_t ROTA_RIGHT_PIN;					// declaration of static data for Rotation Right button

static GPIO_TypeDef *BUZZER_PORT;				// declaration of static GPIO_TypeDef to store the GPIO BUZZER PORT
static uint16_t BUZZER_PIN;						// declaration of static data for buzzer

static GPIO_TypeDef *SWITCH_PORT;				// declaration of static GPIO_TypeDef to store the GPIO SWITCH PORT
static uint16_t SWITCH_PIN;						// declaration of static data for Switch

static uint8_t counter = 0;						// init counter

static bool neutral_areaY = false;				// declaration of static boolean data for neutral_areaY
static bool neutral_areaX = false;				// declaration of static boolean data for neutral_areaX

static bool switch_on = false;					// declaration of static boolean data for the different switch state

#define MAX 1024
#define MIN 853
static uint8_t batValue = 0;					// declaration of static data for Battery Value
static float batPercent = 0.0;					// declaration of static data for Battery Percentage

void ihm_joystick(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2, uint8_t *tab)
{
	HAL_ADC_Start(hadc1);										// function call to start the ADC 1
	HAL_ADC_Start(hadc2);										// function call to start the ADC 1

	if(HAL_ADC_PollForConversion(hadc1, 1) == HAL_OK)			// check if the conversion of ADC 1 is complete
	{
		VRx = HAL_ADC_GetValue(hadc1);							// VRx take the value converted of ADC 1
	}
	if(HAL_ADC_PollForConversion(hadc2, 1) == HAL_OK)			// check if the conversion of ADC 2 is complete
	{
		VRy = HAL_ADC_GetValue(hadc2);							// VRy take the value converted of ADC 2
	}

	if(VRx >= 256 && VRx <= 768)								// check the value of VRx and VRy
	{
		neutral_areaX = true;									// pass neutral_areaX at true
	}

	if(VRy >= 256 && VRy <= 768)								// check the value of VRx and VRy
	{
		neutral_areaY = true;									// pass neutral_areaX at true
	}


	if (VRx < 256 && neutral_areaY)								// check the value of VRx and VRy
	{
		tab[0] = 'B';											// store 'B' into the first case of tab
	}
	else if(VRx < 256 && VRy > 768)								// check the value of VRx and VRy
	{
		tab[0] = 'b';											// store 'b' into the first case of tab
	}
	else if (neutral_areaX && VRy > 768)						// check the value of VRx and VRy
	{
		tab[0] = 'D';											// store 'D' into the first case of tab
	}
	else if (VRx > 768 && VRy > 768)							// check the value of VRx and VRy
	{
		tab[0] = 'a';											// store 'a' into the first case of tab
	}
	else if (VRx > 768 && neutral_areaY)						// check the value of VRx and VRy
	{
		tab[0] = 'H';											// store 'H' into the first case of tab
	}
	else if (neutral_areaX && neutral_areaY)					// check the value of VRx and VRy
	{
		tab[0] = 'N';											// store 'N' into the first case of tab
	}
	else if (VRx > 768 && VRy < 256)							// check the value of VRx and VRy
	{
		tab[0] = 'd';											// store 'd' into the first case of tab
	}
	else if (neutral_areaX && VRy < 256)						// check the value of VRx and VRy
	{
		tab[0] = 'G';											// store 'G' into the first case of tab
	}
	else if (VRx < 256 && VRy < 256)							// check the value of VRx and VRy
	{
		tab[0] = 'c';											// store 'c' into the first case of tab
	}

	neutral_areaX = false;										// pass neutral_areaX at false
	neutral_areaY = false;										// pass neutral_areaY at false
}

//2. POWER UPDATE
uint8_t ihm_PWR_button(GPIO_TypeDef *PWRPORT, uint16_t PWRUP_Pin, uint16_t PWRDOWN_Pin, uint8_t *tab)
{
	//Copy Pins and Port variables
	PWR_PORT = PWRPORT;                                                  // store into PWR_PORT the first argument passed to the function
	PWR_UP_PIN = PWRUP_Pin;                                              // store into PWR_UP_PIN the second argument passed to the function
	PWR_DOWN_PIN = PWRDOWN_Pin;                                          // store into PWR_DOWN_PIN the third argument passed to the function

	//Read State Pin
	if (HAL_GPIO_ReadPin(PWR_PORT, PWR_UP_PIN) == GPIO_PIN_SET)          // check the state of PWR_UP_PIN
	{
		HAL_GPIO_TogglePin(PWR_PORT, PWR_UP_PIN);                        // call function to reverse the state of PWR_UP_PIN
		HAL_Delay(200);                                                  // delay of 200ms

		if(counter == 16)
		{                                               				 // check if the value of counter is equal to 16
			tab[1] = counter;                                            // store the value of the counter into the second case of tab
		}
		else
		{                                                           	 // check the value of counter
			counter += 4;                                                // add 4 to the value of the counter
			tab[1] = counter;                                            // store the value of the counter into the second case of tab
		}
	}
	else if (HAL_GPIO_ReadPin(PWR_PORT, PWR_DOWN_PIN) == GPIO_PIN_SET)   // check the state of PWR_DOWN_PIN
	{
		HAL_GPIO_TogglePin(PWR_PORT, PWR_DOWN_PIN);                      // call function to reverse the state of PWR_DOWN_PIN
		HAL_Delay(200);                                                  // delay of 200ms

		if(counter == 0)
		{                                                				 // check if the value of counter is equal to 0
			tab[1] = counter;                                            // store the value of the counter into the second case of tab
		}
		else
		{                                                           	 // check the value of counter
			counter -= 4;                                                // subtracted 4 to the value of the counter
			tab[1] = counter;                                            // store the value of the counter into the second case of tab
		}
	}
	else
	{
		tab[1] = counter;                                            	  // store the value of the counter into the second case of tab
	}
	return counter;                                              		  // return value of the counter at main.c file
}

//3. ROTA BUTTON FUNCTION
void ihm_ROTA_button(GPIO_TypeDef *ROTAPORT, uint16_t ROTALEFT_Pin, uint16_t ROTARIGHT_Pin, uint8_t *tab)
{
	//Copy Pins and Port variables
	ROTA_PORT = ROTAPORT;														// store into ROTA_PORT the first argument passed to the function
	ROTA_LEFT_PIN = ROTALEFT_Pin;												// store into ROTA_LEFT_PIN the second argument passed to the function
	ROTA_RIGHT_PIN = ROTARIGHT_Pin;												// store into ROTA_RIGHT_PIN the third argument passed to the function

	//Read State Pin
	if(HAL_GPIO_ReadPin(ROTA_PORT, ROTA_RIGHT_PIN) == GPIO_PIN_SET)				// check the state of ROTA_RIGHT_PIN
	{
		tab[0] = 'R';															// store 'R' into the first case of tab
	}
	else if(HAL_GPIO_ReadPin(ROTA_PORT, ROTA_LEFT_PIN) == GPIO_PIN_SET)			// check the state of ROTA_LEFT_PIN
	{
		tab[0] = 'L';															// store 'L' into the first case of tab
	}
}

//4. BUZZER ON OFF (IN OR OUT)
void ihm_buzzer_ON_OFF(GPIO_TypeDef *SWITCHPORT, uint16_t SWITCH_BUZZER_Pin, uint8_t *tab)
{
	SWITCH_PORT = SWITCHPORT;									// store into SWITCH_PORT the first argument passed to the function
	SWITCH_PIN = SWITCH_BUZZER_Pin;								// store into SWITCH_PIN the first argument passed to the function

	tab[2] = HAL_GPIO_ReadPin(SWITCH_PORT, SWITCH_PIN);			// store the state of SWITCH_PORT into the second case of tab

	if(tab[2] == 1)												// check if the third case of tab is equal to 1
	{
		switch_on = true;										// pass switch_on at true
	}
	else
	{
		switch_on = false;										// pass switch_on at false
	}
}

//5. ACTIVE BUZZER (if it is activate with "buzzer_ON_OFF function"
void ihm_active_buzzer(GPIO_TypeDef *BUZZERPORT, uint16_t BUZZER_OT2_Pin, uint8_t *tab)
{
	BUZZER_PORT = BUZZERPORT;											// store into BUZZER_PORT the first argument passed to the function
	BUZZER_PIN = BUZZER_OT2_Pin;										// store into BUZZER_PIN the second argument passed to the function

	if (tab[2] == '1' && switch_on)										// check if the value of the third case of tab is equal at 1 AND if switch_on is true
	{
		HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);		// Transition to the high state of the pin (PIN SET)
	}
	else if (tab[2] == '0' || !switch_on )								// check if the value of the third case of tab is equal at 0 OR switch_on is false
	{
		HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);		// Transition to the low" state of the pin
	}
}

uint8_t ihm_getBatteryLevel(ADC_HandleTypeDef *hadc)
{
	HAL_ADC_Start(hadc);												 // call function to start the ADC
	if(HAL_ADC_PollForConversion(hadc, 1) == HAL_OK)					 // check if the conversion of ADC is complete
	{
		batValue = HAL_ADC_GetValue(hadc);								 // batValue take the converted value of ADC
	}

	//batPercent = 100 - (((MAX - (float)batValue)/ MAX - MIN)*100);	 // store the result of the equation in batPercent
	batPercent = ((MAX - (float)batValue)/ MAX - MIN)*100;				 // subtract the value of batPercent by 100
	batPercent = (uint8_t)batPercent;									 // cast to integer the batPercent variable (float)

	return batPercent;													 // return value of the bat at main.c file
}

// ADC  10 BITS
//	8.4 V ->  3.3	V -> 1024	->	100 %
//	7.0 V ->  2.75  V -> 853	->	  0 %

// MAX = 1024
// MIN = 853
// VMAX = 3.3
// VMIN = 2.75

/* ex : ADC retourne : ADC = 868
		869 * VMAX = 2864
		2864 / 1024 = 2.79 V = 7.1 V

		Calcul pourcentage : [(MAX - ADC)/MAX - MIN] * 100
						AN : [(1024 - 868)/1024-853] * 100 = 91,2
							 100 - 91,2 = 8,8%
*/
/* ex : ADC retourne : ADC = 938
		938 * VMAX = 3095
		3095 / 1024 = 3.02 V = 7.6 V

		Calcul pourcentage : [(MAX - ADC)/MAX - MIN] * 100
						AN : [(1024 - 938)/1024-853] * 100 = 50,29
							 100 - 50,29 = 49,71%
*/

//	16.8 V -> 3.3 	V -> 4096	->	100 %		// (2.75 * 4096) / 3.3 = 3413
//	14.0 V -> 2.75  V -> 3413	->	  0 %

// MAX = 4096
// MIN = 3413
// VMAX = 3.3
// VMIN = 2.75

/* ex : ADC retourne : ADC = 3765
		3765 * VMAX = 12424
		12424 / 4096 = 3.0 V = 15.27 V

		Calcul pourcentage : [(MAX - ADC)/MAX - MIN] * 100
						AN : [(4096 - 3765)/4096-3413] * 100 = 48,46
							 100 - 48,46 = 51%
*/


