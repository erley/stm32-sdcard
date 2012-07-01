/**
 ******************************************************************************
 * @file    main.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains various global settings for the project
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Enable LCD display */
#define USE_LCD

/* Enable touch screen interaction */
//#define USE_TOUCHSCREEN

/* Enable SD Card slot */
#define USE_SDCARD

#if !defined(USE_LCD) && defined(USE_TOUCHSCREEN)
#error USE_TOUCHSCREEN can be defined only if USE_CLD is defined too!
#endif /* !USE_LCD &&  USE_TOUCHSCREEN */

/* Enable DHCP, if disabled static address is used */
//#define USE_DHCP

/* Uncomment SERIAL_DEBUG to retarget of printf() to COM port for debugging */
#define SERIAL_DEBUG

/* Use HW cryptographic processor: AES, TDES, RNG, SHA-1 and MD5.
   !!! This line should be left uncommented !!! */
#define USE_STM32F2XX_HW_CRYPTO

/* MAC ADDRESS */
#define MAC_ADDR0   0
#define MAC_ADDR1   0
#define MAC_ADDR2   0
#define MAC_ADDR3   0
#define MAC_ADDR4   0
#define MAC_ADDR5   1

/* Static IP ADDRESS */
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   20
   
/* NETMASK */
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/* Gateway Address */
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1

/* MII and RMII mode selection, for STM322xG-EVAL Board(MB786) RevB ***********/
//#define RMII_MODE  // User have to provide the 50 MHz clock by soldering a 50 MHz
                     // oscillator (ref SM7745HEV-50.0M or equivalent) on the U3
                     // footprint located under CN3 and also removing jumper on JP5. 
                     // This oscillator is not provided with the board. 
                     // For more details, please refer to STM3220G-EVAL evaluation
                     // board User manual (UM1057).

                                     
#define MII_MODE

/* Uncomment the define below to clock the PHY from external 25MHz crystal (only for MII mode) */
#ifdef 	MII_MODE
//#define PHY_CLOCK_MCO
#endif

/* STM322xG-EVAL jumpers setting
    +==========================================================================================+
    +  Jumper |       MII mode configuration            |      RMII mode configuration         +
    +==========================================================================================+
    +  JP5    | 2-3 provide 25MHz clock by MCO(PA8)     |  Not fitted                          +
    +         | 1-2 provide 25MHz clock by ext. Crystal |                                      +
    + -----------------------------------------------------------------------------------------+
    +  JP6    |          2-3                            |  1-2                                 +
    + -----------------------------------------------------------------------------------------+
    +  JP8    |          Open                           |  Close                               +
    +==========================================================================================+
*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Exported function prototypes ----------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */
