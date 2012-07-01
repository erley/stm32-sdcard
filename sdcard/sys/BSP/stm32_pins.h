/**
 ******************************************************************************
 * @file    stm32_pins.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   This file contains definitions for development board hardware resources.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_PINS_H
#define STM32_PINS_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Utilities
 * @{
 */

/** @defgroup STM32_Exported_Types
 * @{
 */
/**
 * @}
 *//* STM32_Exported_Types */

/** @defgroup STM32_Exported_Constants
 * @{
 */

/** @addtogroup STM32_LED
 * @{
 */

#define LEDn                             4
#define LED_GPIO_CLK_INIT                RCC_AHB1PeriphClockCmd

#define LED1_PIN                         GPIO_Pin_6
#define LED1_GPIO_PORT                   GPIOG
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOG

#define LED2_PIN                         GPIO_Pin_10
#define LED2_GPIO_PORT                   GPIOG
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOG

#define LED3_PIN                         GPIO_Pin_12
#define LED3_GPIO_PORT                   GPIOG
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOG

#define LED4_PIN                         GPIO_Pin_15
#define LED4_GPIO_PORT                   GPIOG
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOG

/**
 * @}
 *//* STM32_LED */

/** @addtogroup STM32_COM
 * @{
 */

#define COMn                             1
#define COM_GPIO_CLK_INIT                RCC_AHB1PeriphClockCmd
#define COM_RxTx_GPIO_CLK_INIT           RCC_APB1PeriphClockCmd

/**
 * @brief Definition for COM port 1, connected to UART5
 */
#define EVAL_COM1                        UART5
#define EVAL_COM1_CLK                    RCC_APB1Periph_UART5
#define EVAL_COM1_TX_PIN                 GPIO_Pin_12
#define EVAL_COM1_TX_GPIO_PORT           GPIOC
#define EVAL_COM1_TX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define EVAL_COM1_TX_SOURCE              GPIO_PinSource12
#define EVAL_COM1_TX_AF                  GPIO_AF_UART5
#define EVAL_COM1_RX_PIN                 GPIO_Pin_2
#define EVAL_COM1_RX_GPIO_PORT           GPIOD
#define EVAL_COM1_RX_GPIO_CLK            RCC_AHB1Periph_GPIOD
#define EVAL_COM1_RX_SOURCE              GPIO_PinSource2
#define EVAL_COM1_RX_AF                  GPIO_AF_UART5
#define EVAL_COM1_IRQn                   UART5_IRQn

/**
 * @}
 *//* STM32_COM */

/** @addtogroup STM32_BUTTON
 * @{
 */

#define BUTTONn                          4
#define BUTTON_GPIO_CLK_INIT             RCC_AHB1PeriphClockCmd

/**
 * @brief Wakeup push-button (BTN1)
 */
#define WAKEUP_BUTTON_PIN                GPIO_Pin_10				// PC10
#define WAKEUP_BUTTON_GPIO_PORT          GPIOC
#define WAKEUP_BUTTON_GPIO_CLK           RCC_AHB1Periph_GPIOC
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line10
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOC
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource10
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI15_10_IRQn
#define WAKEUP_BUTTON_PRESSED_STATE      1

/**
 * @brief Tamper push-button (BTN2)
 */
#define TAMPER_BUTTON_PIN                GPIO_Pin_3					// PD3
#define TAMPER_BUTTON_GPIO_PORT          GPIOD
#define TAMPER_BUTTON_GPIO_CLK           RCC_AHB1Periph_GPIOD
#define TAMPER_BUTTON_EXTI_LINE          EXTI_Line3
#define TAMPER_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOD
#define TAMPER_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource3
#define TAMPER_BUTTON_EXTI_IRQn          EXTI3_IRQn
#define TAMPER_BUTTON_PRESSED_STATE      0

/**
 * @brief Key push-button (BTN3)
 */
#define KEY_BUTTON_PIN                   GPIO_Pin_6					// PD6
#define KEY_BUTTON_GPIO_PORT             GPIOD
#define KEY_BUTTON_GPIO_CLK              RCC_AHB1Periph_GPIOD
#define KEY_BUTTON_EXTI_LINE             EXTI_Line6
#define KEY_BUTTON_EXTI_PORT_SOURCE      EXTI_PortSourceGPIOD
#define KEY_BUTTON_EXTI_PIN_SOURCE       EXTI_PinSource6
#define KEY_BUTTON_EXTI_IRQn             EXTI9_5_IRQn
#define KEY_BUTTON_PRESSED_STATE         0

/**
 * @brief Right push-button (BTN4)
 */
#define RIGHT_BUTTON_PIN                 GPIO_Pin_13				// PD13
#define RIGHT_BUTTON_GPIO_PORT           GPIOD
#define RIGHT_BUTTON_GPIO_CLK            RCC_AHB1Periph_GPIOD
#define RIGHT_BUTTON_EXTI_LINE           EXTI_Line13
#define RIGHT_BUTTON_EXTI_PORT_SOURCE    EXTI_PortSourceGPIOD
#define RIGHT_BUTTON_EXTI_PIN_SOURCE     EXTI_PinSource13
#define RIGHT_BUTTON_EXTI_IRQn           EXTI15_10_IRQn
#define RIGHT_BUTTON_PRESSED_STATE       0

/**
 * @}
 *//* STM32_BUTTON */

/** @addtogroup STM32_LCD_TOUCHSCREEN
 * @{
 */

/**
 * @brief Touch screen PEN
 */
#define TOUCH_PEN_PIN                    GPIO_Pin_8
#define TOUCH_PEN_GPIO_PORT              GPIOA
#define TOUCH_PEN_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define TOUCH_PEN_GPIO_CLK_INIT          RCC_AHB1PeriphClockCmd
#define TOUCH_PEN_EXTI_LINE              EXTI_Line8
#define TOUCH_PEN_EXTI_PORT_SOURCE       EXTI_PortSourceGPIOA
#define TOUCH_PEN_EXTI_PIN_SOURCE        EXTI_PinSource8
#define TOUCH_PEN_EXTI_IRQn              EXTI9_5_IRQn

/**
 * @brief Touch screen Chip Select
 */
#define TOUCH_CS_PIN                     GPIO_Pin_7
#define TOUCH_CS_GPIO_PORT               GPIOG
#define TOUCH_CS_GPIO_CLK                RCC_AHB1Periph_GPIOG
#define TOUCH_CS_GPIO_CLK_INIT           RCC_AHB1PeriphClockCmd

/**
 * @}
 *//* STM32_LCD_TOUCHSCREEN */

/** @addtogroup STM32_SDCard
 * @{
 */

/**
 * @brief SD Card Chip Select pin
 */
#define SD_CS_GPIO_PORT                 GPIOB
#define SD_CS_PIN                       GPIO_Pin_11
#define SD_CS_GPIO_CLK                  RCC_AHB1Periph_GPIOB
#define SD_CS_GPIO_CLK_INIT             RCC_AHB1PeriphClockCmd

/**
 * @brief  SD Card presence detection pin
 */
#define SD_DETECT_GPIO_PORT             GPIOB
#define SD_DETECT_PIN                   GPIO_Pin_12
#define SD_DETECT_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define SD_DETECT_GPIO_CLK_INIT         RCC_AHB1PeriphClockCmd

/**
 * @}
 *//* STM32_SDCard */

/** @addtogroup STM32_SPI
 * @{
 */

/**
 * @brief SPI interface
 */
#define SPIx_SPI                        SPI2
#define SPIx_SPI_CLK                    RCC_APB1Periph_SPI2
#define SPIx_SPI_CLK_INIT               RCC_APB1PeriphClockCmd
//#define SPIx_SPI_IRQn                   SPI2_IRQn
//#define SPIx_SPI_IRQHANDLER             SPI2_IRQHandler

#define SPIx_SPI_SCLK_PIN                GPIO_Pin_13
#define SPIx_SPI_SCLK_GPIO_PORT          GPIOB
#define SPIx_SPI_SCLK_GPIO_CLK           RCC_AHB1Periph_GPIOB
#define SPIx_SPI_SCLK_GPIO_CLK_INIT      RCC_AHB1PeriphClockCmd
#define SPIx_SPI_SCLK_SOURCE             GPIO_PinSource13
#define SPIx_SPI_SCLK_AF                 GPIO_AF_SPI2

#define SPIx_SPI_MISO_PIN               GPIO_Pin_14
#define SPIx_SPI_MISO_GPIO_PORT         GPIOB
//#define SPIx_SPI_MISO_GPIO_CLK          RCC_AHB1Periph_GPIOB
//#define SPIx_SPI_MISO_GPIO_CLK_INIT     RCC_AHB1PeriphClockCmd
#define SPIx_SPI_MISO_SOURCE            GPIO_PinSource14
#define SPIx_SPI_MISO_AF                GPIO_AF_SPI2

#define SPIx_SPI_MOSI_PIN               GPIO_Pin_15
#define SPIx_SPI_MOSI_GPIO_PORT         GPIOB
//#define SPIx_SPI_MOSI_GPIO_CLK          RCC_AHB1Periph_GPIOB
//#define SPIx_SPI_MOSI_GPIO_CLK_INIT     RCC_AHB1PeriphClockCmd
#define SPIx_SPI_MOSI_SOURCE            GPIO_PinSource15
#define SPIx_SPI_MOSI_AF                GPIO_AF_SPI2

/**
 * @}
 *//* STM32_SPI */

///** @addtogroup STM32_SD_FLASH
// * @{
// */
//
//#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40012C80)
///**
// * @brief  SDIO Initialization Frequency (400KHz max)
// */
//#define SDIO_INIT_CLK_DIV                0x76
///**
// * @brief  SDIO Data Transfer Frequency (25MHz max)
// */
//#define SDIO_TRANSFER_CLK_DIV            0x00
//
//#define SD_SDIO_DMA                   DMA2
//#define SD_SDIO_DMA_CLK               RCC_AHB1Periph_DMA2
//
//#define SD_SDIO_DMA_STREAM3	          3
////#define SD_SDIO_DMA_STREAM6           6
//
//#ifdef SD_SDIO_DMA_STREAM3
// #define SD_SDIO_DMA_STREAM            DMA2_Stream3
// #define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
// #define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF3
// #define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF3
// #define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF3
// #define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF3
// #define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF3
// #define SD_SDIO_DMA_IRQn              DMA2_Stream3_IRQn
// #define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream3_IRQHandler
//#elif defined SD_SDIO_DMA_STREAM6
// #define SD_SDIO_DMA_STREAM            DMA2_Stream6
// #define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
// #define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF6
// #define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF6
// #define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF6
// #define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF6
// #define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF6
// #define SD_SDIO_DMA_IRQn              DMA2_Stream6_IRQn
// #define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream6_IRQHandler
//#endif /* SD_SDIO_DMA_STREAM3 */
//
///**
// * @}
// *//* STM32_SD_FLASH */

/** @addtogroup STM32_I2C_EE
 * @{
 */

/**
 * @brief  I2C EEPROM Interface pins
 */
#define sEE_I2C                          I2C1
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C1
#define sEE_I2C_SCL_PIN                  GPIO_Pin_6                  /* PB6 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource6
#define sEE_I2C_SCL_AF                   GPIO_AF_I2C1
#define sEE_I2C_SDA_PIN                  GPIO_Pin_9                  /* PB9 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource9
#define sEE_I2C_SDA_AF                   GPIO_AF_I2C1
#define sEE_M24C64_32

#define sEE_I2C_DMA                      DMA1
#define sEE_I2C_DMA_CHANNEL              DMA_Channel_1
#define sEE_I2C_DMA_STREAM_TX            DMA1_Stream6
#define sEE_I2C_DMA_STREAM_RX            DMA1_Stream0
#define sEE_I2C_DMA_CLK                  RCC_AHB1Periph_DMA1
#define sEE_I2C_DR_Address               0x40005410
#define sEE_USE_DMA

#define sEE_I2C_DMA_TX_IRQn              DMA1_Stream6_IRQn
#define sEE_I2C_DMA_RX_IRQn              DMA1_Stream0_IRQn
#define sEE_I2C_DMA_TX_IRQHandler        DMA1_Stream6_IRQHandler
#define sEE_I2C_DMA_RX_IRQHandler        DMA1_Stream0_IRQHandler
#define sEE_I2C_DMA_PREPRIO              0
#define sEE_I2C_DMA_SUBPRIO              0

#define sEE_TX_DMA_FLAG_FEIF             DMA_FLAG_FEIF6
#define sEE_TX_DMA_FLAG_DMEIF            DMA_FLAG_DMEIF6
#define sEE_TX_DMA_FLAG_TEIF             DMA_FLAG_TEIF6
#define sEE_TX_DMA_FLAG_HTIF             DMA_FLAG_HTIF6
#define sEE_TX_DMA_FLAG_TCIF             DMA_FLAG_TCIF6
#define sEE_RX_DMA_FLAG_FEIF             DMA_FLAG_FEIF0
#define sEE_RX_DMA_FLAG_DMEIF            DMA_FLAG_DMEIF0
#define sEE_RX_DMA_FLAG_TEIF             DMA_FLAG_TEIF0
#define sEE_RX_DMA_FLAG_HTIF             DMA_FLAG_HTIF0
#define sEE_RX_DMA_FLAG_TCIF             DMA_FLAG_TCIF0

/* Time constant for the delay caclulation allowing to have a millisecond
   incrementing counter. This value should be equal to (System Clock / 1000).
   ie. if system clock = 120MHz then sEE_TIME_CONST should be 120. */
#define sEE_TIME_CONST                   120

/**
 * @}
 *//* STM32_I2C_EE */

/** @addtogroup STM32_ETH
 * @{
 */

#define DP83848_PHY_ADDRESS			0x01 /* Relative to STM322xG-EVAL Board */

/**
 * @brief  GPIO ports used by Ethernet interface
 */
#define ETH_GPIO_PORTS				RCC_AHB1Periph_GPIOA | \
									RCC_AHB1Periph_GPIOB | \
									RCC_AHB1Periph_GPIOC | \
									RCC_AHB1Periph_GPIOE | \
									RCC_AHB1Periph_GPIOG
#define ETH_GPIO_PORTS_INIT			RCC_AHB1PeriphClockCmd

/**
 * @brief  Specific defines for EXTI line, used to manage Ethernet link status
 */
#define ETH_LINK_EXTI_LINE			EXTI_Line0
#define ETH_LINK_EXTI_PORT_SOURCE	EXTI_PortSourceGPIOC
#define ETH_LINK_EXTI_PIN_SOURCE	EXTI_PinSource0
#define ETH_LINK_EXTI_IRQn			EXTI0_IRQn

/**
 * @brief  ETH link pin
 */
#define ETH_LINK_PIN				GPIO_Pin_0
#define ETH_LINK_GPIO_PORT			GPIOC
#define ETH_LINK_GPIO_CLK			RCC_AHB1Periph_GPIOC
#define ETH_LINK_GPIO_INIT			RCC_AHB1PeriphClockCmd

/**
 * @brief  PHY registers
 */
#define PHY_MICR					0x11				/* MII Interrupt Control Register */
#define PHY_MICR_INT_EN				((uint16_t)0x0002)	/* PHY Enable interrupts */
#define PHY_MICR_INT_OE				((uint16_t)0x0001)	/* PHY Enable output interrupt events */
#define PHY_MISR					0x12				/* MII Interrupt Status and Misc. Control Register */
#define PHY_MISR_LINK_INT_EN		((uint16_t)0x0020)	/* Enable Interrupt on change of link status */
#define PHY_LINK_STATUS				((uint16_t)0x2000)	/* PHY link status interrupt mask */

/**
 * @}
 *//* STM32_ETH */

/** @addtogroup STM32_FSMC_SRAM
 * @{
 */

/**
 * @brief  GPIO ports used by FSMC SRAM
 */
#define SRAM_GPIO_PORTS			RCC_AHB1Periph_GPIOD | \
								RCC_AHB1Periph_GPIOE | \
								RCC_AHB1Periph_GPIOF | \
								RCC_AHB1Periph_GPIOG
#define SRAM_GPIO_PORTS_INIT	RCC_AHB1PeriphClockCmd

/**
 * @brief  FSMC Bank 1 NOR/SRAM
 */
#define Bank1_SRAM1_ADDR		0x60000000
#define Bank1_SRAM2_ADDR		0x64000000
#define Bank1_SRAM3_ADDR		0x68000000
#define Bank1_SRAM4_ADDR		0x6C000000
//#define Bank2_NAND_ADDR			0x70000000
//#define Bank3_NAND_ADDR			0x80000000
#define FSMC_SRAM_ADDR			Bank1_SRAM1_ADDR
#define FSMC_Bank1_NORSRAM		FSMC_Bank1_NORSRAM2	//FSMC_Bank1_NORSRAM1

/**
 * @}
 *//* STM32_FSMC_SRAM */

/** @defgroup STM32_LCD
 * @{
 */

/**
 * @brief LCD backlight pin
 */
#define LCD_LDK_PIN                      GPIO_Pin_5
#define LCD_LDK_GPIO_PORT                GPIOA
#define LCD_LDK_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define LCD_LDK_GPIO_CLK_INIT            RCC_AHB1PeriphClockCmd

/**
 * @brief  LCD Size (Width and Height)
 */
#define LCD_PIXEL_WIDTH          0x0140
#define LCD_PIXEL_HEIGHT         0x00F0

/**
 * @}
 *//* STM32_LCD */

/**
 * @}
 *//* STM32_Exported_Constants */

/** @defgroup STM32_Exported_Functions
 * @{
 */

void ETH_config_pins( void );

void SRAM_config_pins( void );
void SRAM_unconfig_pins( void );

/**
 * @}
 *//* STM32_Exported_Functions */

/**
 * @}
 *//* Utilities */

#ifdef __cplusplus
}
#endif

#endif /* STM32_PINS_H */
