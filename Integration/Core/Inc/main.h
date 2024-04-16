/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9488.h"
#include "xpt2046.h"
#include "Screens.h"
#include "ds1307.h"
#include "Pills.h";
#include "xbee.h"

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
#define Actuator1_IN1_Pin GPIO_PIN_3
#define Actuator1_IN1_GPIO_Port GPIOF
#define Actuaor1_IN2_Pin GPIO_PIN_5
#define Actuaor1_IN2_GPIO_Port GPIOF
#define Stepper_Step_Pin GPIO_PIN_0
#define Stepper_Step_GPIO_Port GPIOC
#define Stepper_Dir_Pin GPIO_PIN_1
#define Stepper_Dir_GPIO_Port GPIOC
#define NSS_Pin GPIO_PIN_12
#define NSS_GPIO_Port GPIOB
#define Actuator_1_EN_Pin GPIO_PIN_9
#define Actuator_1_EN_GPIO_Port GPIOC
#define TFT_CS_Pin GPIO_PIN_0
#define TFT_CS_GPIO_Port GPIOD
#define TFT_DC_Pin GPIO_PIN_6
#define TFT_DC_GPIO_Port GPIOD
#define TFT_RST_Pin GPIO_PIN_7
#define TFT_RST_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
