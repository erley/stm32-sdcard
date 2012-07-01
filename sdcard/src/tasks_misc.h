/**
 ******************************************************************************
 * @file    tasks_misc.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains all the functions for RTOS tasks
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TASKS_MISC_H
#define TASKS_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void HandleButtons_task( void* pvParameters );

#ifdef __cplusplus
}
#endif

#endif /* TASKS_MISC_H */
