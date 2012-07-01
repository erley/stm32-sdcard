/**
  ******************************************************************************
  * @file    main.c
  * @author  Alexei Troussov
  * @version V1.0
  * @date    01-May-2012
  * @brief   Main program
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "stm32_buttons.h"
#include "stm32_spi.h"

#include "FreeRTOS.h"
#include "task.h"

#include "serial_debug.h"
#include "tasks_misc.h"

#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/*--------------- Tasks Priority -------------*/

#define BTN_TASK_PRIO   ( tskIDLE_PRIORITY + 1 )

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main( void )
{
	/* At this stage the microcontroller clock setting is already configured to
       120 MHz, this is done through SystemInit() function which is called from
       startup file (startup_stm32f2xx.S) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f2xx.c file
     */

	/* USART Configuration */
	DebugComPort_Init();

	/* Initialize buttons */
	STM_EVAL_PBInit( BUTTON_WAKEUP, BUTTON_MODE_EXTI );
	STM_EVAL_PBInit( BUTTON_TAMPER, BUTTON_MODE_EXTI );
	STM_EVAL_PBInit( BUTTON_KEY   , BUTTON_MODE_EXTI );
	STM_EVAL_PBInit( BUTTON_RIGHT , BUTTON_MODE_EXTI );

	/* Initialize SPI */
	STM_EVAL_SPI_Init();

printf("\ntest tracing from embedded code\n");

	/* Handle buttons */
	xTaskCreate( HandleButtons_task, (const signed char* const)"BTN", configMINIMAL_STACK_SIZE, NULL, BTN_TASK_PRIO, NULL );

	/* Start scheduler */
	vTaskStartScheduler();

	/* We should never get here as control is now taken by the scheduler */
	for(;;);
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed( uint8_t* file, uint32_t line )
{
	/* User can add his own implementation to report the file name and line number,
		ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while ( 1 ) {}
}

#endif /* USE_FULL_ASSERT */
