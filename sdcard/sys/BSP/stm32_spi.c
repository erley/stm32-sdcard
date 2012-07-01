/**
 ******************************************************************************
 * @file    stm32_spi.c
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains definitions and routines to handle SPI bus
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "stm32_spi.h"

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

/**
 * @brief  Initialize SPI
 * @param  None
 * @retval None
 */
void STM_EVAL_SPI_Init( void )
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the SPI clock */
	SPIx_SPI_CLK_INIT( SPIx_SPI_CLK, ENABLE );

	/* Enable GPIO clocks (they are all on GPIOB) */
	SPIx_SPI_SCLK_GPIO_CLK_INIT( SPIx_SPI_SCLK_GPIO_CLK, ENABLE );

	/* Connect SPI pins to AF5 */
	GPIO_PinAFConfig( SPIx_SPI_SCLK_GPIO_PORT, SPIx_SPI_SCLK_SOURCE, SPIx_SPI_SCLK_AF );
	GPIO_PinAFConfig( SPIx_SPI_MISO_GPIO_PORT, SPIx_SPI_MISO_SOURCE, SPIx_SPI_MISO_AF );
	GPIO_PinAFConfig( SPIx_SPI_MOSI_GPIO_PORT, SPIx_SPI_MOSI_SOURCE, SPIx_SPI_MOSI_AF );

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* base clock is set to 50Mhz */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = SPIx_SPI_SCLK_PIN;
	GPIO_Init( SPIx_SPI_SCLK_GPIO_PORT, &GPIO_InitStructure );

	/* SPI  MISO pin configuration */
	GPIO_InitStructure.GPIO_Pin = SPIx_SPI_MISO_PIN;
	GPIO_Init( SPIx_SPI_MISO_GPIO_PORT, &GPIO_InitStructure );

	/* SPI  MOSI pin configuration */
	GPIO_InitStructure.GPIO_Pin =  SPIx_SPI_MOSI_PIN;
	GPIO_Init( SPIx_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure );

	/* SPI configuration -------------------------------------------------------*/
	SPI_I2S_DeInit( SPIx_SPI );

	/* Initializes the SPI communication */
	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler =
#ifdef USE_TOUCHSCREEN
		SPI_BaudRatePrescaler_16;
#else
		SPI_BaudRatePrescaler_2;	/* actual speed of SPI bus is half of base clock */
#endif /* USE_TOUCHSCREEN */
	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial     = 7;
	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
	SPI_Init( SPIx_SPI, &SPI_InitStructure );

	/* The Data transfer is performed in the SPI interrupt routine */
	SPI_Cmd( SPIx_SPI, ENABLE );  /* Enable the SPI peripheral */
}

/**
 * @brief  Sends a byte on SPI bus and receives a byte of response
 * @see SD_WriteByte() and SD_ReadByte() from stm32_eval_spi_sd.c
 * @param  Byte to send
 * @retval Received data
 */
uint16_t STM_EVAL_SPI_Send_Recieve_Data( uint8_t data )
{
	/* Wait until the transmit buffer is empty */
	while ( SPI_I2S_GetFlagStatus( SPIx_SPI, SPI_I2S_FLAG_TXE ) == RESET ) {}
	SPI_I2S_SendData( SPIx_SPI, data );	/* Send byte to SPI bus */
	/* Wait to receive a byte */
	while ( SPI_I2S_GetFlagStatus( SPIx_SPI, SPI_I2S_FLAG_RXNE ) == RESET ) {}
	return SPI_I2S_ReceiveData( SPIx_SPI );	/* Read byte from SPI bus */
}

//void STM_EVAL_SPI_Low_Speed()
//{
//	SPI_InitTypeDef SPI_InitStructure;
//
//	SPI_Cmd( SPIx_SPI, DISABLE );
//	SPI_I2S_DeInit( SPIx_SPI );
//
//	/* Initializes the SPI communication */
//	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;
//	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;
//	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
//	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial     = 7;
//	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
//	SPI_Init( SPIx_SPI, &SPI_InitStructure );
//
//	/* The Data transfer is performed in the SPI interrupt routine */
//	SPI_Cmd( SPIx_SPI, ENABLE );	/* Enable the SPI peripheral */
//}
//
//void STM_EVAL_SPI_High_Speed()
//{
//	SPI_InitTypeDef SPI_InitStructure;
//
//	SPI_Cmd( SPIx_SPI, DISABLE );
//	SPI_I2S_DeInit( SPIx_SPI );
//
//	/* Initializes the SPI communication */
//	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;
//	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;
//	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
//	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial     = 7;
//	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
//	SPI_Init( SPIx_SPI, &SPI_InitStructure );
//
//	/* The Data transfer is performed in the SPI interrupt routine */
//	SPI_Cmd( SPIx_SPI, ENABLE );	/* Enable the SPI peripheral */
//}

/**
 * @}
 *//* STM32_Public_Functions */


/**
 * @}
 *//* Utilities */
