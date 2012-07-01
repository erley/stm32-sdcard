/**
 ******************************************************************************
 * @file    serial_debug.c
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   Serail port debugging console. Retargets printf() function to USART
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "serial_debug.h"

#include "stm32_usart.h"

#include <stdio.h>

#ifdef SERIAL_DEBUG

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initialize COM1 interface for serial debug
 * @note   COM1 interface is defined in stm3210g_eval.h file (under Utilities\STM32_EVAL\STM322xG_EVAL)
 * @param  None
 * @retval None
 */
void DebugComPort_Init( void )
{
	USART_InitTypeDef USART_InitStructure;

	/* USARTx configured as follow:
	   - BaudRate = 115200 baud
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - No parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM_EVAL_COMInit( COM1, &USART_InitStructure );
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData( EVAL_COM1, (uint8_t)ch );

	/* Loop until the end of transmission */
	while ( USART_GetFlagStatus( EVAL_COM1, USART_FLAG_TC ) == RESET ) {}

	return ch;
}

#endif /* SERIAL_DEBUG */
