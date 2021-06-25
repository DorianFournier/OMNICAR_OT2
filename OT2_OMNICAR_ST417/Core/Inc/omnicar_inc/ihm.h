/*
 * ihm.h
 *
 *  Created on: Jun 10, 2021
 *      Author: TEAM OMNICAR
 */

#ifndef INC_OMNICAR_INC_IHM_H_
#define INC_OMNICAR_INC_IHM_H_

#include "stm32f4xx_hal.h"   				//** Change this according to your STM32 series **//
#include <stdbool.h>

//1. JOYSTICK FUNCTION
void ihm_joystick(ADC_HandleTypeDef *hadc1, ADC_HandleTypeDef *hadc2, uint8_t *tab);

//2. POWER BUTTON FUNCTION
uint8_t ihm_PWR_button(GPIO_TypeDef *PWRPORT, uint16_t PWRUP_Pin, uint16_t PWRDOWN_Pin, uint8_t *tab);

//3. ROTA BUTTON FUNCTION
void ihm_ROTA_button(GPIO_TypeDef *ROTAPORT, uint16_t ROTALEFT_Pin, uint16_t ROTARIGHT_Pin, uint8_t *tab);

//4. BUZZER ON OFF
void ihm_buzzer_ON_OFF(GPIO_TypeDef *SWITCHPORT, uint16_t SWITCH_BUZZER_Pin, uint8_t *tab);

//5. ACTIVE BUZZER
void ihm_active_buzzer(GPIO_TypeDef *BUZZERPORT, uint16_t BUZZER_OT2_Pin, uint8_t *tab);

//6. ADC GET BATTERY LEVEL
uint8_t ihm_getBatteryLevel(ADC_HandleTypeDef *hadc);

#endif /* INC_OMNICAR_INC_IHM_H_ */
