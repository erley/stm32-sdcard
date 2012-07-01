/**
 ******************************************************************************
 * @file    stm32_buttons.c
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains definitions and routines to handle push buttons
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "stm32_buttons.h"

/** @addtogroup Utilities
 * @{
 */

/** @defgroup STM32_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 *//* STM32_Private_TypesDefinitions */


/** @defgroup STM32_Private_Defines
 * @{
 */
/**
 * @}
 *//* STM32_Private_Defines */


/** @defgroup STM32_Private_Macros
 * @{
 */
/**
 * @}
 *//* STM32_Private_Macros */


/** @defgroup STM32_Private_Constants
 * @{
 */

/** @addtogroup STM32_BUTTON
 * @{
 */

/*const, but GPIO_Init() takes non-const parameter */
GPIO_TypeDef* BUTTON_PORT[ BUTTONn ] =
{
	WAKEUP_BUTTON_GPIO_PORT,
	TAMPER_BUTTON_GPIO_PORT,
	KEY_BUTTON_GPIO_PORT,
	RIGHT_BUTTON_GPIO_PORT
};
const uint16_t BUTTON_PIN[ BUTTONn ] =
{
	WAKEUP_BUTTON_PIN,
	TAMPER_BUTTON_PIN,
	KEY_BUTTON_PIN,
	RIGHT_BUTTON_PIN
};
const uint32_t BUTTON_CLK[ BUTTONn ] =
{
	WAKEUP_BUTTON_GPIO_CLK,
	TAMPER_BUTTON_GPIO_CLK,
	KEY_BUTTON_GPIO_CLK,
	RIGHT_BUTTON_GPIO_CLK
};
const uint16_t BUTTON_EXTI_LINE[ BUTTONn ] =
{
	WAKEUP_BUTTON_EXTI_LINE,
	TAMPER_BUTTON_EXTI_LINE,
	KEY_BUTTON_EXTI_LINE,
	RIGHT_BUTTON_EXTI_LINE
};
const uint8_t BUTTON_PORT_SOURCE[ BUTTONn ] =
{
	WAKEUP_BUTTON_EXTI_PORT_SOURCE,
	TAMPER_BUTTON_EXTI_PORT_SOURCE,
	KEY_BUTTON_EXTI_PORT_SOURCE,
	RIGHT_BUTTON_EXTI_PORT_SOURCE
};
const uint8_t BUTTON_PIN_SOURCE[ BUTTONn ] =
{
	WAKEUP_BUTTON_EXTI_PIN_SOURCE,
	TAMPER_BUTTON_EXTI_PIN_SOURCE,
	KEY_BUTTON_EXTI_PIN_SOURCE,
	RIGHT_BUTTON_EXTI_PIN_SOURCE
};
const uint8_t BUTTON_IRQn[ BUTTONn ] =
{
	WAKEUP_BUTTON_EXTI_IRQn,
	TAMPER_BUTTON_EXTI_IRQn,
	KEY_BUTTON_EXTI_IRQn,
	RIGHT_BUTTON_EXTI_IRQn
};
const uint8_t BUTTON_PRESSED_STATE[ BUTTONn ] =
{
	WAKEUP_BUTTON_PRESSED_STATE,
	TAMPER_BUTTON_PRESSED_STATE,
	KEY_BUTTON_PRESSED_STATE,
	RIGHT_BUTTON_PRESSED_STATE
};

/**
 * @}
 *//* STM32_BUTTON */

/**
 * @}
 *//* STM32_Private_Constants */


/** @defgroup STM32_Private_Variables
 * @{
 */
/**
 * @}
 *//* STM32_Private_Variables */


/** @defgroup STM32_Private_FunctionPrototypes
 * @{
 */
/**
 * @}
 *//* STM32_Private_FunctionPrototypes */


/** @defgroup STM32_Public_Functions
 * @{
 */

/**
 * @brief  Configures Button GPIO and EXTI Line.
 * @param  Button: Specifies the Button to be configured.
 *   This parameter can be one of following parameters:
 *     @arg BUTTON_WAKEUP: Wakeup Push Button
 *     @arg BUTTON_TAMPER: Tamper Push Button
 *     @arg BUTTON_KEY: Key Push Button
 *     @arg BUTTON_RIGHT: Joystick Right Push Button
 *     @arg BUTTON_LEFT: Joystick Left Push Button
 *     @arg BUTTON_UP: Joystick Up Push Button
 *     @arg BUTTON_DOWN: Joystick Down Push Button
 *     @arg BUTTON_SEL: Joystick Sel Push Button
 * @param  Button_Mode: Specifies Button mode.
 *   This parameter can be one of following parameters:
 *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO
 *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
 *                     generation capability
 * @retval None
 */
void STM_EVAL_PBInit( Button_TypeDef Button, ButtonMode_TypeDef Button_Mode )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the BUTTON Clock */
	BUTTON_GPIO_CLK_INIT( BUTTON_CLK[ Button ], ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE );

	/* Configure Button pin as input */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[ Button ];
	GPIO_Init( BUTTON_PORT[ Button ], &GPIO_InitStructure );

	if ( Button_Mode == BUTTON_MODE_EXTI )
	{
		/* Connect Button EXTI Line to Button GPIO Pin */
		SYSCFG_EXTILineConfig( BUTTON_PORT_SOURCE[ Button ], BUTTON_PIN_SOURCE[ Button ] );

		/* Configure Button EXTI line */
		EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[ Button ];
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = ( Button != BUTTON_WAKEUP ) ?
			EXTI_Trigger_Falling : EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init( &EXTI_InitStructure );

		/* Enable and set Button EXTI Interrupt to the lowest priority */
		NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[ Button ];
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init( &NVIC_InitStructure );
	}
}

/**
 * @brief  Returns the selected Button state.
 * @param  Button: Specifies the Button to be checked.
 *   This parameter can be one of following parameters:
 *     @arg BUTTON_WAKEUP: Wakeup Push Button
 *     @arg BUTTON_TAMPER: Tamper Push Button
 *     @arg BUTTON_KEY: Key Push Button
 *     @arg BUTTON_RIGHT: Joystick Right Push Button
 *     @arg BUTTON_LEFT: Joystick Left Push Button
 *     @arg BUTTON_UP: Joystick Up Push Button
 *     @arg BUTTON_DOWN: Joystick Down Push Button
 *     @arg BUTTON_SEL: Joystick Sel Push Button
 * @retval The Button GPIO pin value.
 */
uint32_t STM_EVAL_PBGetState( Button_TypeDef Button )
{
	uint8_t bitstatus =
		GPIO_ReadInputDataBit( BUTTON_PORT[ Button ], BUTTON_PIN[ Button ] );
	if ( BUTTON_PRESSED_STATE[ Button ] == 0 )
		return ( bitstatus == (uint8_t)Bit_SET ) ? Bit_RESET : Bit_SET;
	return bitstatus;
}

/**
 * @}
 *//* STM32_Public_Functions */


/**
 * @}
 *//* Utilities */
