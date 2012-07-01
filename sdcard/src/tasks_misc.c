/**
 ******************************************************************************
 * @file    tasks_misc.c
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains all the functions for RTOS tasks
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "tasks_misc.h"

#include "stm32_buttons.h"
#include "stm32_sd_spi.h"

/* Scheduler */
#include "FreeRTOS.h"
#include "task.h"

#include "FAT/ff.h"

/* Standard includes */
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static const TCHAR filename[ 12 + 1 ] = { 'T', 'E', 'S', 'T', '_', 'S', 'D', 'C', '.', 'T', 'X', 'T', '\0' };
static const TCHAR filecontext[ 15 ] = { 'U', 'C', 'A', 'N', '-', 'S', 'T', 'M', '3', '2', 'F', '2', '1', '7', '\0' };
static FATFS fs;
static FIL f;

static uint8_t buff[ 512 ];
static uint8_t buff1[ 512 ];

static void SDCard_Run( void )
{
	UINT nb;
	FRESULT rs;

	if ( SD_Detect() == SD_NOT_PRESENT )
	{
		printf( "SDCard isn't detected\n" );
		return;
	}

	printf( "f_mount() ... " );
	rs = f_mount( 0, &fs );
	if ( rs != FR_OK )
	{
		printf( "failed with code %d\n", rs );
		return;
	}
	printf( "OK\n" );

	printf( "f_open() ... " );
	rs = f_open( &f, filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE );
	if ( rs != FR_OK )
	{
		printf( "failed with code %d\n", rs );
		return;
	}
	printf( "OK\n" );

	printf( "f_write() ... " );
	rs = f_write( &f, filecontext, sizeof(filecontext), &nb );
	if ( rs != FR_OK || nb != sizeof(filecontext) )
	{
		printf( "failed with code %d\n", rs );
		return;
	}
	printf( "OK\n" );

	printf( "f_close() ... " );
	rs = f_close( &f );
	if ( rs != FR_OK )
	{
		printf( "failed with code %d\n", rs );
		return;
	}
	printf( " OK\n" );
}

static void SDCard_Dump( void )
{
	SD_Error res;
	SD_CardInfo cardinfo;
	uint8_t i, j;

	if ( SD_Detect() == SD_NOT_PRESENT )
	{
		printf( "SDCard isn't detected\n" );
	}
	else
	{
		printf( "SDCard detected\n" );
		memset( &cardinfo, 0, sizeof(cardinfo) );

		// initialize SD Card...
		res = SD_Init();
		if ( res == SD_RESPONSE_NO_ERROR )
		{
			res = SD_GetCardInfo( &cardinfo );
			if ( res == SD_RESPONSE_NO_ERROR )
			{
				SD_DumpCardInfo( &cardinfo );
			}
			else
			{
				printf( "SDCard information retrieval failed with code %d\n", res );
			}
			res = SD_SectorRead( 0, buff );
			if ( res == SD_RESPONSE_NO_ERROR )
			{
				printf( "Sector 0:\n" );
				for ( i=0; i<32; ++i )
				{
					for ( j=0; j<16; ++j )
						printf( " %02X", buff[ 16*i + j ] );
					printf("\n");
				}
			}
			else
			{
				printf( "SDCard read sector 0 failed\n" );
			}
		}
		else
		{
			printf( "SDCard initialization failed with code %d\n", res );
		}
	}
}

static void SDCard_Erase( void )
{
	SD_Error res;

	if ( SD_Detect() == SD_NOT_PRESENT )
	{
		printf( "SDCard isn't detected\n" );
	}
	else
	{
		printf( "SDCard detected\n" );

		// initialize SD Card...
		res = SD_Init();
		if ( res == SD_RESPONSE_NO_ERROR )
		{
			uint32_t ReadAddr = 123;
			uint8_t i, j;

			res = SD_SectorRead( ReadAddr, buff );
			if ( res == SD_RESPONSE_NO_ERROR )
			{
				printf( "Sector %lu:\n", ReadAddr );
				for ( i=0; i<32; ++i )
				{
					for ( j=0; j<16; ++j )
						printf( " %02X", buff[ 16*i + j ] );
					printf("\n");
				}
			}
			else
				printf( "SDCard read sector %lu failed\n", ReadAddr );

			res = SD_SectorErase( ReadAddr );
			if ( res == SD_RESPONSE_NO_ERROR )
				printf( "Sector erase succeeded\n" );
			else
				printf( "Sector erase failed\n" );

			res = SD_SectorRead( ReadAddr, buff1 );
			if ( res == SD_RESPONSE_NO_ERROR )
			{
				printf( "Sector %lu:\n", ReadAddr );
				for ( i=0; i<32; ++i )
				{
					for ( j=0; j<16; ++j )
						printf( " %02X", buff[ 16*i + j ] );
					printf("\n");
				}
			}
			else
				printf( "SDCard read sector %lu failed\n", ReadAddr );

//			memset( buff, 0x00, sizeof(buff) );

			res = SD_SectorWrite( ReadAddr, buff );
			if ( res == SD_RESPONSE_NO_ERROR )
				printf( "Sector write succeeded\n" );
			else
				printf( "Sector write failed\n" );

			res = SD_SectorRead( ReadAddr, buff1 );
			if ( res == SD_RESPONSE_NO_ERROR )
			{
				printf( "Sector %lu:\n", ReadAddr );
				for ( i=0; i<32; ++i )
				{
					for ( j=0; j<16; ++j )
						printf( " %02X", buff[ 16*i + j ] );
					printf("\n");
				}
			}
			else
				printf( "SDCard read sector %lu failed\n", ReadAddr );
		}
		else
			printf( "SDCard initialization failed with code %d\n", res );
	}
}

static void SDCard_Status( void )
{
	SD_Error res;
	SD_Status SD_status;

	if ( SD_Detect() == SD_NOT_PRESENT )
	{
		printf( "SDCard isn't detected\n" );
	}
	else
	{
		printf( "SDCard detected\n" );

		// initialize SD Card...
		res = SD_Init();
		if ( res == SD_RESPONSE_NO_ERROR )
		{
			res = SD_GetStatus( &SD_status );
			if ( res == SD_RESPONSE_NO_ERROR )
			{
				SD_DumpStatus( &SD_status );
			}
			else
				printf( "SDCard status retrieval failed with code %d\n", res );
		}
		else
			printf( "SDCard initialization failed with code %d\n", res );
	}
}

static void OnBTN1( void )
{
	printf("BTN1 was pressed\n");
#ifdef USE_SDCARD
	printf( "Get SDCard status info\n" );
	SDCard_Status();
#endif /* USE_SDCARD */
}

static void OnBTN2( void )
{
	printf("BTN2 was pressed\n");
#ifdef USE_SDCARD
	printf( "Erase sectors on SDCard\n" );
	SDCard_Erase();
#endif /* USE_SDCARD */
}

static void OnBTN3( void )
{
	printf("BTN3 was pressed\n");
#ifdef USE_SDCARD
	printf( "Dump SDCard information\n" );
	/* Initialize SD Card and dump its information */
	SDCard_Dump();
#endif /* USE_SDCARD */
}

static void OnBTN4( void )
{
	printf( "BTN4 was pressed\n" );
#ifdef USE_SDCARD
	printf( "Write test text file on SDCard FAT\n" );
	/* Initialize SD Card and write file on it */
	SDCard_Run();
#endif /* USE_SDCARD */
}

#ifdef USE_TOUCHSCREEN
static void OnTOUCH( int16_t x, int16_t y )
{
	printf( "TOUCH( %d, %d )\n", x, y );
}
#endif /* USE_TOUCHSCREEN */

/* Private task functions ----------------------------------------------------*/

/**
 * @brief  Show message every time button is pressed
 * @param  pvParameters not used
 * @retval None
 */
extern uint8_t PB_Touch_flag;
void HandleButtons_task( void* pvParameters )
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 20;

	// we set a flag because writing on LCD from interrupt handler would break
	while(1)
	{
		uint8_t mask = 0x1;
		if ( PB_Touch_flag & mask )
		{
			xLastWakeTime = xTaskGetTickCount();
			vTaskDelayUntil( &xLastWakeTime, xFrequency );
			if ( STM_EVAL_PBGetState(BUTTON_WAKEUP) == Bit_SET )
			{
				OnBTN1();
			}
			PB_Touch_flag &= ~mask;
		}
		mask <<= 1;
		if ( PB_Touch_flag & mask )
		{
			xLastWakeTime = xTaskGetTickCount();
			vTaskDelayUntil( &xLastWakeTime, xFrequency );
			if ( STM_EVAL_PBGetState(BUTTON_TAMPER) == Bit_SET )
			{
				OnBTN2();
			}
			PB_Touch_flag &= ~mask;
		}
		mask <<= 1;
		if ( PB_Touch_flag & mask )
		{
			xLastWakeTime = xTaskGetTickCount();
			vTaskDelayUntil( &xLastWakeTime, xFrequency );
			if ( STM_EVAL_PBGetState(BUTTON_KEY) == Bit_SET )
			{
				OnBTN3();
			}
			PB_Touch_flag &= ~mask;
		}
		mask <<= 1;
		if ( PB_Touch_flag & mask )
		{
			xLastWakeTime = xTaskGetTickCount();
			vTaskDelayUntil( &xLastWakeTime, xFrequency );
			if ( STM_EVAL_PBGetState(BUTTON_RIGHT) == Bit_SET )
			{
				OnBTN4();
			}
			PB_Touch_flag &= ~mask;
		}
#ifdef USE_TOUCHSCREEN
		mask <<= 1;
		if ( PB_Touch_flag & mask )
		{
			xLastWakeTime = xTaskGetTickCount();
			vTaskDelayUntil( &xLastWakeTime, xFrequency );
			if (STM_EVAL_TouchScreen_GetState() == Bit_SET)
			{
				Point p_touched;
				if ( LCD_TouchScreen_Read(&p_touched) == 1 )
				{
					OnTOUCH( p_touched.X, p_touched.Y );
				}
			}
			PB_Touch_flag &= ~mask;
		}
#endif /* USE_TOUCHSCREEN */
	}
}
