/**
 ******************************************************************************
 * @file    stm32f2xx_it.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains the headers of the interrupt handlers
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32F2xx_IT_H
#define STM32F2xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
 * Bitmask with flags for buttons pressed and touchscreen
 * Bit 0 - BTN1
 * Bit 1 - BTN2
 * Bit 2 - BTN3
 * Bit 3 - BTN4
 * Bit 4 - Touch screen
 */
extern uint8_t PB_Touch_flag;

void NMI_Handler( void );
void HardFault_Handler( void );
void MemManage_Handler( void );
void BusFault_Handler( void );
void UsageFault_Handler( void );
void SVC_Handler( void );
void DebugMon_Handler( void );
void PendSV_Handler( void );
void SysTick_Handler( void );

#ifdef __cplusplus
}
#endif

#endif /* STM32F2xx_IT_H */
