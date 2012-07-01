/**
 ******************************************************************************
 * @file    stm32_usart.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains definitions and routines to handle COM ports
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "stm32_usart.h"

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

/** @addtogroup STM32_COM
 * @{
 */

/*const, but USART_Init() takes non-const parameter */
USART_TypeDef* COM_USART[ COMn ] = { EVAL_COM1 };
/*const, but GPIO_PinAFConfig() takes non-const parameter */
GPIO_TypeDef* COM_TX_PORT[ COMn ] = { EVAL_COM1_TX_GPIO_PORT };
/*const, but GPIO_PinAFConfig() takes non-const parameter */
GPIO_TypeDef* COM_RX_PORT[ COMn ] = { EVAL_COM1_RX_GPIO_PORT };
const uint32_t COM_USART_CLK[ COMn ] = { EVAL_COM1_CLK };
const uint32_t COM_TX_PORT_CLK[ COMn ] = { EVAL_COM1_TX_GPIO_CLK };
const uint32_t COM_RX_PORT_CLK[ COMn ] = { EVAL_COM1_RX_GPIO_CLK };
const uint16_t COM_TX_PIN[ COMn ] = { EVAL_COM1_TX_PIN };
const uint16_t COM_RX_PIN[ COMn ] = { EVAL_COM1_RX_PIN };
const uint8_t COM_TX_PIN_SOURCE[ COMn ] = { EVAL_COM1_TX_SOURCE };
const uint8_t COM_RX_PIN_SOURCE[ COMn ] = { EVAL_COM1_RX_SOURCE };
const uint8_t COM_TX_AF[ COMn ] = { EVAL_COM1_TX_AF };
const uint8_t COM_RX_AF[ COMn ] = { EVAL_COM1_RX_AF };

/**
 * @}
 *//* STM32_COM */

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
 * @brief  Configures COM port.
 * @param  COM: Specifies the COM port to be configured.
 *   This parameter can be one of following parameters:
 *     @arg COM1
 *     @arg COM2
 * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
 *   contains the configuration information for the specified USART peripheral.
 * @retval None
 */
void STM_EVAL_COMInit( COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct )
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO clock */
	COM_GPIO_CLK_INIT( COM_TX_PORT_CLK[ COM ] | COM_RX_PORT_CLK[ COM ], ENABLE );

	if ( COM == COM1 ) /* TODO: can be done better here */
		COM_RxTx_GPIO_CLK_INIT( COM_USART_CLK[ COM ], ENABLE );	/* Enable USART clock */

	/* connect GPIO port to USARTx_Tx */
	GPIO_PinAFConfig( COM_TX_PORT[ COM ], COM_TX_PIN_SOURCE[ COM ], COM_TX_AF[ COM ] );

	/* connect GPIO port to USARTx_Rx */
	GPIO_PinAFConfig( COM_RX_PORT[ COM ], COM_RX_PIN_SOURCE[ COM ], COM_RX_AF[ COM ] );

	/* configure USART Tx */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[ COM ];
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( COM_TX_PORT[ COM ], &GPIO_InitStructure );

	/* configure USART Rx */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
	GPIO_Init( COM_RX_PORT[ COM ], &GPIO_InitStructure );

	/* USART configuration */
	USART_Init( COM_USART[ COM ], USART_InitStruct );

	/* enable USART */
	USART_Cmd( COM_USART[ COM ], ENABLE );
}

/**
 * @}
 *//* STM32_Public_Functions */


/**
 * @}
 *//* Utilities */
