/**
 ******************************************************************************
 * @file    stm32_pins.c
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains definitions for development board hardware resources.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "stm32_pins.h"

#include "stm32f2xx.h"

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

void ETH_config_pins( void )
{
/*                                 STM322xG -> uCos
   ETH_MDIO -------------------------> PA2	-> PA2
   ETH_MDC --------------------------> PC1	-> PC1
   ETH_PPS_OUT ----------------------> PB5	-> not soldered
   ETH_MII_CRS ----------------------> PH2	-> PA0   (CRS  RTL8201 pin 23)
   ETH_MII_COL ----------------------> PH3	-> PA3   (COL  RTL8201 pin 1)
   ETH_MII_RX_ER --------------------> PI10	-> PB10  (RXER RTL8201 pin 24)
   ETH_MII_RXD2 ---------------------> PH6	-> PB0   (RXD2 RTL8201 pin 19)
   ETH_MII_RXD3 ---------------------> PH7	-> PB1   (RXD3 RTL8201 pin 18)
   ETH_MII_TX_CLK -------------------> PC3	-> PC3   (TXC  RTL8201 pin 7)
   ETH_MII_TXD2 ---------------------> PC2	-> PC2   (TXD2 RTL8201 pin 4)
   ETH_MII_TXD3 ---------------------> PB8	-> PE2   (TXD3 RTL8201 pin 3)
   ETH_MII_RX_CLK/ETH_RMII_REF_CLK---> PA1	-> PA1
   ETH_MII_RX_DV/ETH_RMII_CRS_DV ----> PA7	-> PA7
   ETH_MII_RXD0/ETH_RMII_RXD0 -------> PC4	-> PC4
   ETH_MII_RXD1/ETH_RMII_RXD1 -------> PC5	-> PC5
   ETH_MII_TX_EN/ETH_RMII_TX_EN -----> PG11	-> PG11
   ETH_MII_TXD0/ETH_RMII_TXD0 -------> PG13	-> PG13
   ETH_MII_TXD1/ETH_RMII_TXD1 -------> PG14	-> PG14
   ETH_MII_INT ----------------------> PB14 -> PC0
 */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL ;

	/* Configure PA0, PA1, PA2, PA3, PA7 */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_7;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource0, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource1, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource2, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource3, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource7, GPIO_AF_ETH );

	/* Configure PB0, PB1 and PB10 */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10;
	GPIO_Init( GPIOB, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOB, GPIO_PinSource0, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOB, GPIO_PinSource1, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOB, GPIO_PinSource10, GPIO_AF_ETH );

	/* Configure PC1, PC2, PC3, PC4 and PC5 */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init( GPIOC, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOC, GPIO_PinSource1, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOC, GPIO_PinSource2, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOC, GPIO_PinSource3, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOC, GPIO_PinSource4, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOC, GPIO_PinSource5, GPIO_AF_ETH );

	/* Configure PE2 */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_2;
	GPIO_Init( GPIOE, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource2, GPIO_AF_ETH );

	/* Configure PG11, PG14 and PG13 */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Init( GPIOG, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource11, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource13, GPIO_AF_ETH );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource14, GPIO_AF_ETH );
}

void SRAM_config_pins( void )
{
/*
 +-------------------+--------------------+------------------+------------------+
 +                       SRAM pins assignment                                   +
 +-------------------+--------------------+------------------+------------------+
 | PD0  <-> FSMC_D2  | PE0  <-> FSMC_NBL0 | PF0  <-> FSMC_A0 | PG0 <-> FSMC_A10 |
 | PD1  <-> FSMC_D3  | PE1  <-> FSMC_NBL1 | PF1  <-> FSMC_A1 | PG1 <-> FSMC_A11 |
 | PD4  <-> FSMC_NOE | PE7  <-> FSMC_D4   | PF2  <-> FSMC_A2 | PG2 <-> FSMC_A12 |
 | PD5  <-> FSMC_NWE | PE8  <-> FSMC_D5   | PF3  <-> FSMC_A3 | PG3 <-> FSMC_A13 |
 | PD7  <-> FSMC_NE1 | PE9  <-> FSMC_D6   | PF4  <-> FSMC_A4 | PG4 <-> FSMC_A14 |
 | PD8  <-> FSMC_D13 | PE10 <-> FSMC_D7   | PF5  <-> FSMC_A5 | PG5 <-> FSMC_A15 |
 | PD9  <-> FSMC_D14 | PE11 <-> FSMC_D8   | PF12 <-> FSMC_A6 | PG9 <-> FSMC_NE2 |
 | PD10 <-> FSMC_D15 | PE12 <-> FSMC_D9   | PF13 <-> FSMC_A7 |------------------+
 | PD11 <-> FSMC_A16 | PE13 <-> FSMC_D10  | PF14 <-> FSMC_A8 |
 | PD12 <-> FSMC_A17 | PE14 <-> FSMC_D11  | PF15 <-> FSMC_A9 |
 | PD14 <-> FSMC_D0  | PE15 <-> FSMC_D12  |------------------+
 | PD15 <-> FSMC_D1	 |--------------------+
 +-------------------+
*/
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	/* GPIOD configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5  |
		GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
		GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init( GPIOD, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource0 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource1 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource4 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource5 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource7 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource8 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource9 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource10, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource11, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource12, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource14, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource15, GPIO_AF_FSMC );

	/* GPIOE configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_7 |
		GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 |
		GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init( GPIOE, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource0 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource1 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource10, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource11, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource12, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource13, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource14, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource15, GPIO_AF_FSMC );

	/* GPIOF configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3 |
		GPIO_Pin_4  | GPIO_Pin_5  |
		GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init( GPIOF, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource0 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource1 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource2 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource3 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource4 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource5 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource12, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource13, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource14, GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource15, GPIO_AF_FSMC );

	/* GPIOG configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  | GPIO_Pin_3 |
		GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_9;
	GPIO_Init( GPIOG, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource0 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource1 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource2 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource3 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource4 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource5 , GPIO_AF_FSMC );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource9 , GPIO_AF_FSMC );
}

void SRAM_unconfig_pins( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	/* GPIOD configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5  |
		GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
		GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init( GPIOD, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource0 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource1 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource4 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource5 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource7 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource8 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource9 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource10, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource11, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource12, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource14, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource15, GPIO_AF_MCO );

	/* GPIOE configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_7  | GPIO_Pin_8  |
		GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |
		GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init( GPIOE, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource0 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource1 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource7 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource8 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource9 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource10, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource11, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource12, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource13, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource14, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOE, GPIO_PinSource15, GPIO_AF_MCO );

	/* GPIOF configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3 |
		GPIO_Pin_4  | GPIO_Pin_5  |
		GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init( GPIOF, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource0 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource1 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource2 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource3 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource4 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource5 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource12, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource13, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource14, GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOF, GPIO_PinSource15, GPIO_AF_MCO );

	/* GPIOG configuration */
	GPIO_InitStructure.GPIO_Pin =
		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
		GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_9;
	GPIO_Init( GPIOG, &GPIO_InitStructure );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource0 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource1 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource2 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource3 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource4 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource5 , GPIO_AF_MCO );
	GPIO_PinAFConfig( GPIOG, GPIO_PinSource9 , GPIO_AF_MCO );
}

/**
 * @}
 *//* STM32_Public_Functions */


/**
 * @}
 *//* Utilities */
