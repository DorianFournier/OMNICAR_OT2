/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_3
#define BUZZER_GPIO_Port GPIOE
#define SW_BUZZER_Pin GPIO_PIN_6
#define SW_BUZZER_GPIO_Port GPIOE
#define ADC_BAT_Pin GPIO_PIN_4
#define ADC_BAT_GPIO_Port GPIOA
#define SW_JOY_Pin GPIO_PIN_7
#define SW_JOY_GPIO_Port GPIOA
#define VRX_Pin GPIO_PIN_5
#define VRX_GPIO_Port GPIOC
#define VRY_Pin GPIO_PIN_0
#define VRY_GPIO_Port GPIOB
#define ROTA_RIGHT_Pin GPIO_PIN_10
#define ROTA_RIGHT_GPIO_Port GPIOE
#define PWR_UP_Pin GPIO_PIN_11
#define PWR_UP_GPIO_Port GPIOE
#define PWR_DOWN_Pin GPIO_PIN_12
#define PWR_DOWN_GPIO_Port GPIOE
#define ROTA_LEFT_Pin GPIO_PIN_13
#define ROTA_LEFT_GPIO_Port GPIOE
#define IRQ_Pin GPIO_PIN_15
#define IRQ_GPIO_Port GPIOA
#define CE_Pin GPIO_PIN_6
#define CE_GPIO_Port GPIOB
#define CSN_Pin GPIO_PIN_7
#define CSN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
