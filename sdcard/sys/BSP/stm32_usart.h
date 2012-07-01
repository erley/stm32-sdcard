/**
 ******************************************************************************
 * @file    stm32_usart.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains definitions and routines to handle COM ports
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_USART_H
#define STM32_USART_H

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

typedef enum _COM_TypeDef
{
  COM1 = 0
// ,COM2 = 1
} COM_TypeDef;

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

void STM_EVAL_COMInit( COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct );

/**
 * @}
 *//* STM32_Exported_Functions */

/**
 * @}
 *//* Utilities */

#ifdef __cplusplus
}
#endif

#endif /* STM32_USART_H */
