/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "sdcard.h"
#include "string.h"
/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
extern SD_CardInfo SDCardInfo;
#define BlockSize            512 /* Block Size in Bytes [�o�̪�block�t�q�O�u���ϡv�ASD�d���C�Ӯ��Ϭ�512�r�`]*/
#define BufferWordsSize      (BlockSize >> 2)	//128�A�t�q�Ѧ�MAIN���������A�O128��32�쪺�w�İϡA�s��512�Ӧr�`

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive [�Ө�ƬO�ݭn��g��]                                                   */
/* �`�N�G�q��ƪ��N�X�W�ӬݡA�ҿת�drv�o�ӰѼơA�O�Τ@�ӼƦr�ӥN����w�������A�q��switch�y�y��
   drv = ATA = 0�G��ܬOIDE�w�L���@�ر��f
   drv = MMC = 1: ��ܪ��OMMC�d�����f�A�]�N�OSD�d
   drv = USB = 2: ��ܪ��OUSB�s�x�]�ƪ����f
   �q�o�̬ݨӡA�ڭ����ӭn��ܪ��OMMC���f,��J�Ѽƥ�����1*/
DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{	
  SD_Error Status;
  Status = SD_Init();
  if (Status == SD_OK)
  {
    /*----------------- Read CSD/CID MSD registers ------------------*/
    Status = SD_GetCardInfo(&SDCardInfo);
  }

  if (Status == SD_OK)
  {
    /*----------------- Select Card --------------------------------*/
    Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));
  }

  if (Status == SD_OK)
  {
    Status = SD_EnableWideBusOperation(SDIO_BusWide_1b);
  }

  /* Set Device Transfer Mode to DMA [�]�m�ǿ�Ҧ���DMA�覡]*/
  if (Status == SD_OK)
  {  
    Status = SD_SetDeviceMode(SD_INTERRUPT_MODE);
  }
  if(Status == SD_OK)return 0;
  else return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status  [�Ө�ƻݭn��g]                                                  */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s) [�Ө�ƻݭn��g]                                       */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
  //memset(buff2, 0, sizeof(buff2));
	if(count==1)
        {
          SD_ReadBlock(sector << 9 ,(u32 *)(&buff[0]),BlockSize);
          //memcpy(buff,buff2,SECTOR_SIZE);
	}
	else
        {
          SD_ReadMultiBlocks(sector << 9 ,(u32 *)(&buff[0]),BlockSize,count);
          //memcpy(buff,buff2,SECTOR_SIZE * count);
	}
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s) [�Ө�ƻݭn��g]                                                      */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
  //memset(buff2, 0, sizeof(buff2));
	if(count==1)
        {
          //memcpy(buff2,buff,SECTOR_SIZE);
          SD_WriteBlock(sector << 9 ,(u32 *)(&buff[0]),BlockSize);
	}
	else
        {
          //memcpy(buff2,buff,SECTOR_SIZE * count);
          SD_WriteMultiBlocks(sector << 9 ,(u32 *)(&buff[0]),BlockSize,count);
	}
        
  return RES_OK;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions [�Ө�ƻݭn��g]                                              */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}

