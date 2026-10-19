/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include	"MathUtils.h"
#include	"DataTypeDef.h"
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
#define W_CurrentPin_Pin GPIO_PIN_0
#define W_CurrentPin_GPIO_Port GPIOA
#define V_CurrentPin_Pin GPIO_PIN_1
#define V_CurrentPin_GPIO_Port GPIOA
#define U_CurrentPin_Pin GPIO_PIN_2
#define U_CurrentPin_GPIO_Port GPIOA
#define VBUS_AD_Pin GPIO_PIN_4
#define VBUS_AD_GPIO_Port GPIOA
#define OC_FAULT_Pin GPIO_PIN_5
#define OC_FAULT_GPIO_Port GPIOA
#define OC_FAULT_EXTI_IRQn EXTI9_5_IRQn
#define PWM_WL_Pin GPIO_PIN_7
#define PWM_WL_GPIO_Port GPIOA
#define PWM_VL_Pin GPIO_PIN_0
#define PWM_VL_GPIO_Port GPIOB
#define PWM_UL_Pin GPIO_PIN_1
#define PWM_UL_GPIO_Port GPIOB
#define SD_Pin GPIO_PIN_12
#define SD_GPIO_Port GPIOB
#define PWM_WH_Pin GPIO_PIN_8
#define PWM_WH_GPIO_Port GPIOA
#define PWM_VH_Pin GPIO_PIN_9
#define PWM_VH_GPIO_Port GPIOA
#define PWM_UH_Pin GPIO_PIN_10
#define PWM_UH_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_11
#define LED_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
