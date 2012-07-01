/**
 ******************************************************************************
 * @file    stm32f2xx_it.c
 * @author  Alexei Troussov
 * @version V1.0
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "stm32f2xx_it.h"

#include "stm32_buttons.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

extern void xPortSysTickHandler( void );

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler( void )
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler( void )
{	/* Go to infinite loop when Hard Fault exception occurs */
	while ( 1 ) {}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler( void )
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while ( 1 ) {}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler( void )
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while ( 1 ) {}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler( void )
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while ( 1 ) {}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler( void )
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler( void )
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler( void )
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler( void )
{
	xPortSysTickHandler();
}

/******************************************************************************/
/*                 STM32F2xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f2xx.S).                                               */
/******************************************************************************/

uint8_t PB_Touch_flag;

void EXTI0_IRQHandler( void )
{
}

/**
 * @brief  This function handles External line 10 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI15_10_IRQHandler( void )
{
	if ( EXTI_GetITStatus( WAKEUP_BUTTON_EXTI_LINE ) != RESET )		// PC10
	{
		PB_Touch_flag |= 0x1;
		/* Clear the interrupt flags */
		EXTI_ClearITPendingBit( WAKEUP_BUTTON_EXTI_LINE );
	}
	if ( EXTI_GetITStatus( RIGHT_BUTTON_EXTI_LINE ) != RESET )		// PD13
	{
		PB_Touch_flag |= (0x1 << 3);
		/* Clear the interrupt flags */
		EXTI_ClearITPendingBit( RIGHT_BUTTON_EXTI_LINE );
	}
}

void EXTI3_IRQHandler( void )
{
	if ( EXTI_GetITStatus( TAMPER_BUTTON_EXTI_LINE ) != RESET )		// PD3
	{
		PB_Touch_flag |= (0x1 << 1);
		/* Clear the interrupt flags */
		EXTI_ClearITPendingBit( TAMPER_BUTTON_EXTI_LINE );
	}
}

void EXTI9_5_IRQHandler( void )
{
	if ( EXTI_GetITStatus( KEY_BUTTON_EXTI_LINE ) != RESET )		// PD6
	{
		PB_Touch_flag |= (0x1 << 2);
		/* Clear the interrupt flags */
		EXTI_ClearITPendingBit( KEY_BUTTON_EXTI_LINE );
	}
#ifdef USE_TOUCHSCREEN
	if ( EXTI_GetITStatus( TOUCH_PEN_EXTI_LINE ) != RESET )			// Touch screen
	{
		PB_Touch_flag |= (0x1 << 4);
		/* Clear the interrupt flags */
		EXTI_ClearITPendingBit( TOUCH_PEN_EXTI_LINE );
	}
#endif /* USE_TOUCHSCREEN */
}

///**
// * @brief  This function handles PPP interrupt request.
// * @param  None
// * @retval None
// */
//void PPP_IRQHandler(void)
//{
//}

/**
 * @brief  This function handles ethernet DMA interrupt request.
 * @param  None
 * @retval None
 */
void ETH_IRQHandler( void )
{
}
