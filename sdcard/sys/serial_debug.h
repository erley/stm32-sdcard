/**
 ******************************************************************************
 * @file    serial_debug.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   Seral debugging console implementation
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SERIAL_DEBUG_H
#define SERIAL_DEBUG_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef SERIAL_DEBUG
void DebugComPort_Init( void );
#endif /* SERIAL_DEBUG */

#endif /* SERIAL_DEBUG_H */
