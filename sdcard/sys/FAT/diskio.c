/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"

#include "ffconf.h"
#include "stm32_sd_spi.h"

/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
	BYTE drv				/* Physical drive number (0..) */
)
{
	if ( drv )
		return STA_NOINIT;

	if ( SD_Detect() == SD_NOT_PRESENT )
		return STA_NODISK;

	if ( SD_Init() != SD_RESPONSE_NO_ERROR )
		return STA_NOINIT;

	return 0;
}

/*-----------------------------------------------------------------------*/
/* Return Drive Status                                                   */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
	BYTE drv		/* Physical drive number (0..) */
)
{
	if ( drv )
		return STA_NOINIT;
	return 0;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE drv,		/* Physical drive number (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	DRESULT res;
	if ( drv || !count )
		return RES_PARERR;

	if ( count == 1 )
		res = (DRESULT)SD_SectorRead( sector, buff );
	else
		res = (DRESULT)SD_SectorsRead( sector, buff, count );

	if ( res == 0x00 )
		return RES_OK;
	return RES_ERROR;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive number (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	DRESULT res;
	if ( drv || !count )
		return RES_PARERR;

	if ( count == 1 )
		res = (DRESULT)SD_SectorWrite( sector, buff );
	else
		res = (DRESULT)SD_SectorsWrite( sector, buff, count );

	if ( res == 0 )
		return RES_OK;
	return RES_ERROR;
}
#endif /* _READONLY */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive number (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	SD_CardInfo cardinfo;
	DRESULT res;
	if ( drv )
		return RES_PARERR;

	switch( ctrl )
	{
	case CTRL_SYNC:
//		res = ( SD_WaitReady() == SD_RESPONSE_NO_ERROR ) ? RES_OK : RES_ERROR
		res = RES_OK;
		break;
	case GET_BLOCK_SIZE:
		*(WORD*)buff = _MAX_SS;
		res = RES_OK;
		break;
	case GET_SECTOR_COUNT:
		if ( SD_GetCardInfo( &cardinfo ) != SD_RESPONSE_NO_ERROR )
			res = RES_ERROR;
		else
		{
			*(DWORD*)buff = cardinfo.CardCapacity;
			res = ( *(DWORD*)buff > 0 ) ? RES_OK : RES_PARERR;
		}
		break;
	case CTRL_ERASE_SECTOR:
		res = ( SD_SectorsErase( ((DWORD*)buff)[ 0 ], ((DWORD*)buff)[ 1 ] ) == SD_RESPONSE_NO_ERROR )
			? RES_OK : RES_PARERR;
		break;
	default:
		res = RES_PARERR;
		break;
	}

	return res;
}

#if !_FS_READONLY
/**
 * Real time clock (used in ff.c)
 * +-----------------------------------------------------------------------------------------------+
 * |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00| 
 * +--------------------|-----------|--------------|--------------|-----------------|--------------+
 * |Year(0-127 org.1980)|Month(1-12)|   Day(1-31)  |  Hour(0-23)  |   Minute(0-59)  | Second(0-59) |
 * +-----------------------------------------------------------------------------------------------+
 */
DWORD get_fattime( void )
{
	return 0;
}
#endif /* _FS_READONLY */
