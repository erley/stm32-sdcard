/**
 ******************************************************************************
 * @file    stm32_sd_spi.h
 * @author  Alexei Troussov
 * @version V1.0
 * @date    21-June-2012
 * @brief   High-level communication layer for read/write SD Card mounted on SPI bus.
 *          SPI and GPIO pins are defined in stm32_pins.h file.
 *          SPI bus is initialized in STM_EVAL_SPI_Init() in stm32_spi.c file.
 *          This driver can be tuned for any development board in stm32_pins.h.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_SD_SPI_H
#define STM32_SD_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

#include "stm32_pins.h"

/** @addtogroup Utilities
 * @{
 */

/** @defgroup STM32_Exported_Types
 * @{
 */

/**
 * @brief  Card Specific Data: CSD Register
 */
typedef struct _SD_CSD
{									/*   v1 v2 bits */
	uint8_t  CSDStruct;				/*!<  2  x (=0) CSD structure */
	uint8_t  SysSpecVersion;		/*!<  4  x (reserved=0) System specification version */
	uint8_t  Reserved1;				/*!<  2  x Reserved */
	uint8_t  TAAC;					/*!<  8  x Data read access-time 1 */
	uint8_t  NSAC;					/*!<  8  x Data read access-time 2 in CLK cycles */
	uint8_t  MaxBusClkFrec;			/*!<  8  x (={32,5A}) Max. bus clock frequency */
	uint16_t CardComdClasses;		/*!< 12  x (=01x110110101) Card command classes */
	uint8_t  RdBlockLen;			/*!<  4  x Max. read data block length */
	uint8_t  PartBlockRead;			/*!<  1  x (=1) Partial blocks for read allowed */
	uint8_t  WrBlockMisalign;		/*!<  1  x Write block misalignment */
	uint8_t  RdBlockMisalign;		/*!<  1  x Read block misalignment */
	uint8_t  DSRImpl;				/*!<  1  x DSR implemented */
	uint8_t  Reserved2;				/*!<  2    (=0) Reserved */

	// {{ these 27 bits are for v1:
	uint32_t DeviceSize;			/*!< 12    Device Size */
	uint8_t  MaxRdCurrentVDDMin;	/*!<  3    Max. read current @ VDD min */
	uint8_t  MaxRdCurrentVDDMax;	/*!<  3    Max. read current @ VDD max */
	uint8_t  MaxWrCurrentVDDMin;	/*!<  3    Max. write current @ VDD min */
	uint8_t  MaxWrCurrentVDDMax;	/*!<  3    Max. write current @ VDD max */
	uint8_t  DeviceSizeMul;			/*!<  3    Device size multiplier */
	// }}

	// {{ these 27 bits are for v2:
	uint8_t  Reserved5;				/*!<     4 (=0) Reserved */
	//uint32_t DeviceSize;			/*!<    22 Device Size */
	uint8_t  Reserved6;				/*!<     1 (=0) Reserved */
	// }}

	uint8_t  EraseBlockEnable;		/*!<  1  x (=1 for v2) Erase single block enable */
	uint8_t  EraseSectorSize;		/*!<  7  x (=7F for v2) Erase sector size */
	uint8_t  WrProtectGrSize;		/*!<  7  x Write protect group size */
	uint8_t  WrProtectGrEnable;		/*!<  1  x Write protect group enable */
	uint8_t  ManDeflECC;			/*!<  2  x (reserved=0) Manufacturer default ECC */
	uint8_t  WrSpeedFact;			/*!<  3  x Write speed factor */
	uint8_t  MaxWrBlockLen;			/*!<  4  x Max. write data block length */
	uint8_t  WriteBlockPaPartial;	/*!<  1  x Partial blocks for write allowed */
	uint8_t  Reserved3;				/*!<  4  x (=0) Reserved */
	uint8_t  ContentProtectAppli;	/*!<  1  x (reserved=0) Content protection application */
	uint8_t  FileFormatGroup;		/*!<  1  x File format group */
	uint8_t  CopyFlag;				/*!<  1  x Copy flag (OTP) */
	uint8_t  PermWrProtect;			/*!<  1  x Permanent write protection */
	uint8_t  TempWrProtect;			/*!<  1  x Temporary write protection */
	uint8_t  FileFormat;			/*!<  2  x File Format */
	uint8_t  ECC;					/*!<  2  x (reserved=0) ECC code */
	uint8_t  CSD_CRC;				/*!<  7  x CSD CRC */
	uint8_t  Reserved4;				/*!<  1  x (=1) not used */
} SD_CSD;

/**
 * @brief  SD Card Configuration Register
 */
typedef struct _SD_SCR
{									/*   bits */
	uint8_t		SCR_Version;		/*!< :4 (=0, else reserved) SCR structure version */
	uint8_t		SpecVersion;		/*!< :4 Physical layer specification version number
										0 - Version 1.0 and 1.01
										1 - Version 1.10
										2 - Version 2.00 or 3.0x
										3-15 - reserved */
	uint8_t		StateAfterErase;	/*!< :1 State of bits after sector erase */
	uint8_t		Security;			/*!< :3 CPRM security version
										0 - no security
										1 - not used
										2 - SDSC security ver 1.01
										3 - SDHC security ver 2.00
										4 - SDXC security ver 3.xx
										5-7 - reserved */
	uint8_t		BusWidth;			/*!< :4 Supported data bus width
										bit 0 - 1 bit
										bit 1 - reserved
										bit 2 - 4 bit
										bit 3 - reserved */
	uint8_t		SpecVersion3;		/*!< :1 Distinguish between SpecVersion 2.00 or 3.0x */
	uint8_t		ExSecurity;			/*!< :4 Extended security (0 if not supported) */
	uint16_t	Reserved1;			/*!< :9 Reserved */
	uint8_t		CmdSupport1;		/*!< :1 Support of CMD23 (set block count) */
	uint8_t		CmdSupport2;		/*!< :1 Support of CMD20 (speed class control) */
	uint32_t	Reserved2;			/*!< :32 Reserved */
} SD_SCR;

/**
 * @brief  Card Identification Data: CID Register
 */
typedef struct _SD_CID
{									/*   bits */
	uint8_t  ManufacturerID;		/*!< : 8 ManufacturerID */
	uint16_t OEM_AppliID;			/*!< :16 OEM/Application ID (2-char string) */
	uint32_t ProdName1;				/*!< :32 Product Name part1 (4-char string) */
	uint8_t  ProdName2;				/*!< : 8 Product Name part2 (1-char string) */
	uint8_t  ProdRev;				/*!< : 8 Product Revision (x.y, where x and y take 4 bits each) */
	uint32_t ProdSN;				/*!< :32 Product Serial Number */
	uint8_t  Reserved1;				/*!< : 4 Reserved */
	uint16_t ManufactDate;			/*!< :12 Manufacturing Date (bits 0-3: month, bits 4-11: year-2000) */
	uint8_t  CID_CRC;				/*!< : 7 CID CRC */
	uint8_t  Reserved2;				/*!< : 1 Not used, always 1 */
} SD_CID;

/**
 * @brief SD Card information
 */
typedef struct _SD_CardInfo
{
	SD_CSD SD_csd;
	SD_CID SD_cid;
	SD_SCR SD_scr;
	uint32_t CardCapacity;			/*!< Card Capacity */
	uint32_t CardBlockSize;			/*!< Card Block Size */
} SD_CardInfo;

/**
 * @brief  SD Card Status structure
 */
typedef struct _SD_Status
{									/*   bits */
	uint8_t		BusWidth;			/*!< :  2 Bus width */
	uint8_t		InSecuredMode;		/*!< :  1 Set if SD card is in secured mode */
	uint16_t	Reserved1;			/*!< : 13 Reserved */
	uint16_t	CardType;			/*!< : 16 Card Type
										0000h - Regular SD card
										0001h - SD ROM card
										0002h - OTP card */
	uint32_t	SizeProtectedArea;	/*!< : 32 Size of protected area */
	uint8_t		SpeedClass;			/*!< :  8 Speed class
										00h - Class 0
										01h - Class 2
										02h - Class 4
										03h - Class 6
										04h - Class 10
										05h-FFh - reserved */
	uint8_t		PerformanceMove;	/*!< :  8 Performance move
										00h - Sequential write
										0xh - x Mb/sec
										FFh - Infinity */
	uint8_t		AU_Size;			/*!< :  4 Allocation Unit size
										0h - not defined
										1h - 16 Kb
										2h - 32 Kb
										3h - 64 Kb
										4h - 128 Kb
										5h - 256 Kb
										6h - 512 Kb
										7h - 1 Mb
										8h - 2 Mb
										9h - 4 Mb
										Ah - 8 Mb
										Bh - 12 Mb
										Ch - 16 Mb
										Dh - 24 Mb
										Eh - 32 Mb
										Fh - 64 Mb */
	uint8_t		Reserved2;			/*!< :  4 Reserved */
	uint16_t	EraseSize;			/*!< : 16 Erase Size in AU blocks */
	uint8_t		EraseTimeout;		/*!< :  6 Erase Timeout in seconds */
	uint8_t		EraseOffset;		/*!< :  2 Erase Offset in seconds */
	uint8_t		UHS_SpeedGrade;		/*!< :  4 Speed Grade for UHS mode (0 - <10 Mb/sec, 1 - > 10 Mb/sec) */
	uint8_t		UHS_AU_Size;		/*!< :  4 Allocation Unit size for UHS mode
										0h - not defined
										1h-6h - not used
										7h - 1 Mb
										8h - 2 Mb
										9h - 4 Mb
										Ah - 8 Mb
										Bh - 12 Mb
										Ch - 16 Mb
										Dh - 24 Mb
										Eh - 32 Mb
										Fh - 64 Mb */
} SD_Status;

/**
 * @brief  SD R1 responses
 */
typedef enum _SD_Error
{
	SD_RESPONSE_NO_ERROR	= 0x00,
	SD_IN_IDLE_STATE		= 0x01,
	SD_ERASE_RESET			= 0x02,
	SD_ILLEGAL_COMMAND		= 0x04,
	SD_COMMAND_CRC_ERROR	= 0x08,
	SD_ERASE_SEQUENCE_ERROR	= 0x10,
	SD_ADDRESS_ERROR		= 0x20,
	SD_PARAMETER_ERROR		= 0x40,
	SD_CHECK_BIT			= 0x80,	/*!< this bit must be set to 0 */
	SD_RESPONSE_FAILURE		= 0xFF
} SD_Error;

/**
 * @}
 *//* STM32_Exported_Types */

/** @defgroup STM32_Exported_Constants
 * @{
 */

/**
 * @brief  Block (1 NAND sector) size
 */
#define SD_BLOCK_SIZE		0x200

/**
 * @brief  SD detection on its memory slot
 */
#define SD_PRESENT			((uint8_t)0x01)
#define SD_NOT_PRESENT		((uint8_t)0x00)

/**
 * @}
 *//* STM32_Exported_Constants */

/** @defgroup STM32_Exported_Functions
 * @{
 */

uint8_t SD_Detect( void );

void SD_DeInit( void );
SD_Error SD_Init( void );

SD_Error SD_GetCardInfo( SD_CardInfo *cardinfo );
void SD_DumpCardInfo( const SD_CardInfo *cardinfo );

SD_Error SD_GetStatus( SD_Status* SD_status );
void SD_DumpStatus( const SD_Status* SD_status );

/**
 * Read/Write/Erase by sectors of SD_BLOCK_SIZE (=512) bytes
 * All addresses are sector numbers
 * All buffers have to be pre-allocated to have 512 bytes
 */
SD_Error SD_SectorRead( uint32_t readAddr, uint8_t* pBuffer );
SD_Error SD_SectorWrite( uint32_t writeAddr, const uint8_t* pBuffer );
SD_Error SD_SectorsRead( uint32_t readAddr, uint8_t* pBuffer, uint32_t nbSectors );
SD_Error SD_SectorsWrite( uint32_t writeAddr, const uint8_t* pBuffer, uint32_t nbSectors );
SD_Error SD_SectorsErase( uint32_t eraseAddrFrom, uint32_t eraseAddrTo );
#define SD_SectorErase( eraseAddr )		SD_SectorsErase( (eraseAddr), (eraseAddr) )

/**
 * @}
 *//* STM32_Exported_Functions */

/**
 * @}
 *//* Utilities */

#ifdef __cplusplus
}
#endif

#endif /* STM32_SD_SPI_H */
