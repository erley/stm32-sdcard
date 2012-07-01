/**
 ******************************************************************************
 * @file    stm32_buttons.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains definitions and routines to handle push buttons
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_BUTTONS_H
#define STM32_BUTTONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

#include "stm32_pins.h"

/** @addtogroup Utilities
 * @{
 */

/** @defgroup STM32_Exported_Types
 * @{
 */

typedef enum _Button_TypeDef
{
	BUTTON_WAKEUP = 0,
	BUTTON_TAMPER = 1,
	BUTTON_KEY = 2,
	BUTTON_RIGHT = 3
} Button_TypeDef;

typedef enum _ButtonMode_TypeDef
{
	BUTTON_MODE_GPIO = 0,
	BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

//typedef enum _JOYState_TypeDef
//{
//	JOY_NONE = 0,
//	JOY_SEL = 1,
//	JOY_DOWN = 2,
//	JOY_LEFT = 3,
//	JOY_RIGHT = 4,
//	JOY_UP = 5
//} JOYState_TypeDef;

/**
 * @}
 *//* STM32_Exported_Types */

/** @defgroup STM32_Exported_Constants
 * @{
 */
/**
 * @}
 *//* STM32_Exported_Constants */

/** @defgroup STM32_Exported_Functions
 * @{
 */

void STM_EVAL_PBInit( Button_TypeDef Button, ButtonMode_TypeDef Button_Mode );
uint32_t STM_EVAL_PBGetState( Button_TypeDef Button );

/**
 * @}
 *//* STM32_Exported_Functions */

/**
 * @}
 *//* Utilities */

#ifdef __cplusplus
}
#endif

#endif /* STM32_BUTTONS_H */
