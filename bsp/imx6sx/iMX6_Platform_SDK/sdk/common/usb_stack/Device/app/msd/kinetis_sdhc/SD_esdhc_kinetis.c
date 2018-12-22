/******************************************************************************
*  (c) copyright Freescale Semiconductor China Ltd. 2008
*  ALL RIGHTS RESERVED
*  File Name: SD.C
*  Description: SD Card Drivers
*  Assembler:  Codewarrior for HC(S)08 V6.0
*  Version: 1.0
*  Author: Jose Ruiz
*  Location: Guadalajuara, Mexico
*
* UPDATED HISTORY:
* REV   YYYY.MM.DD  AUTHOR        DESCRIPTION OF CHANGE
* ---   ----------  ------        ---------------------
* 1.0   2008.01.02  Jose Ruiz      Initial version
******************************************************************************/
/* Freescale  is  not  obligated  to  provide  any  support, upgrades or new */
/* releases  of  the Software. Freescale may make changes to the Software at */
/* any time, without any obligation to notify or provide updated versions of */
/* the  Software  to you. Freescale expressly disclaims any warranty for the */
/* Software.  The  Software is provided as is, without warranty of any kind, */
/* either  express  or  implied,  including, without limitation, the implied */
/* warranties  of  merchantability,  fitness  for  a  particular purpose, or */
/* non-infringement.  You  assume  the entire risk arising out of the use or */
/* performance of the Software, or any systems you design using the software */
/* (if  any).  Nothing  may  be construed as a warranty or representation by */
/* Freescale  that  the  Software  or  any derivative work developed with or */
/* incorporating  the  Software  will  be  free  from  infringement  of  the */
/* intellectual property rights of third parties. In no event will Freescale */
/* be  liable,  whether in contract, tort, or otherwise, for any incidental, */
/* special,  indirect, consequential or punitive damages, including, but not */
/* limited  to,  damages  for  any loss of use, loss of time, inconvenience, */
/* commercial loss, or lost profits, savings, or revenues to the full extent */
/* such  may be disclaimed by law. The Software is not fault tolerant and is */
/* not  designed,  manufactured  or  intended by Freescale for incorporation */
/* into  products intended for use or resale in on-line control equipment in */
/* hazardous, dangerous to life or potentially life-threatening environments */
/* requiring  fail-safe  performance,  such  as  in the operation of nuclear */
/* facilities,  aircraft  navigation  or  communication systems, air traffic */
/* control,  direct  life  support machines or weapons systems, in which the */
/* failure  of  products  could  lead  directly to death, personal injury or */
/* severe  physical  or  environmental  damage  (High  Risk Activities). You */
/* specifically  represent and warrant that you will not use the Software or */
/* any  derivative  work of the Software for High Risk Activities.           */
/* Freescale  and the Freescale logos are registered trademarks of Freescale */
/* Semiconductor Inc.                                                        */
/*****************************************************************************/

/* Includes */
#include "user_config.h"

#if USE_SDHC_PROTOCOL

#include "types.h"
#include "SD_esdhc_kinetis.h"


/* Gobal Variables */
uint_8  vSD_CSD[16];        /* SD card CSD vaule    */
uint_8  vSD_Bnum;           /* Block number         */
uint_32 vSD_LBA;            /* BLock address        */

T32_8 u32MaxBlocks;
T16_8 u16BlockSize;

T32_8 gu8SD_Argument;
uint_8 gu8SD_CID[16];

ESDHC_INFO_STRUCT_PTR    esdhc_info_ptr;
uint_32                  sdhc_addr = 0, num_block = 0;
SDCARD_STRUCT_PTR        sdcard_ptr;

/************************************************/
uint_8 SD_Init(void)
{
   uint_32              i,param, c_size, c_size_mult, read_bl_len, NUM_BLOCKS,time_out = 0;
   ESDHC_COMMAND_STRUCT command;

   esdhc_info_ptr = (ESDHC_INFO_STRUCT_PTR)malloc(sizeof(ESDHC_INFO_STRUCT));
   esdhc_info_ptr->CARD = 0;
   sdcard_ptr = (SDCARD_STRUCT_PTR)malloc(sizeof(SDCARD_STRUCT));
   sdcard_ptr->NUM_BLOCKS = 0;
   sdcard_ptr->ADDRESS = 0;
   sdcard_ptr->SDHC = FALSE;
   sdcard_ptr->VERSION2 = FALSE;


   while(time_out < 1000)
   {
      /* Initialize and detect card */
      if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_INIT, NULL))
      {
         continue;
      }
      /* SDHC check */
      param = 0;
      if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_GET_CARD, &param))
      {
         continue;
      }

      if ((ESDHC_CARD_SD == param) || (ESDHC_CARD_SDHC == param) || (ESDHC_CARD_SDCOMBO == param) || (ESDHC_CARD_SDHCCOMBO == param))
      {
         if ((ESDHC_CARD_SDHC == param) || (ESDHC_CARD_SDHCCOMBO == param))
         {
            sdcard_ptr->SDHC = TRUE;
         }
         break;
      }
      else
      {
         continue;
      }
      time_out++;
   }

   if(time_out >= 1000)
   return 2;

   /* Card identify */
   command.COMMAND = ESDHC_CMD2;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = 0;
   command.READ = FALSE;
   command.BLOCKS = 0;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return FALSE;
   }

   /* Get card address */
   command.COMMAND = ESDHC_CMD3;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = 0;
   command.READ = FALSE;
   command.BLOCKS = 0;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return FALSE;
   }
   sdcard_ptr->ADDRESS = command.RESPONSE[0] & 0xFFFF0000;

   /* Get card parameters */
   command.COMMAND = ESDHC_CMD9;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = sdcard_ptr->ADDRESS;
   command.READ = FALSE;
   command.BLOCKS = 0;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return FALSE;
   }
   if (0 == (command.RESPONSE[3] & 0x00C00000))
   {
      read_bl_len = (command.RESPONSE[2] >> 8) & 0x0F;
      c_size = command.RESPONSE[2] & 0x03;
      c_size = (c_size << 10) | (command.RESPONSE[1] >> 22);
      c_size_mult = (command.RESPONSE[1] >> 7) & 0x07;
      sdcard_ptr->NUM_BLOCKS = (c_size + 1) * (1 << (c_size_mult + 2)) * (1 << (read_bl_len - 9));
   }
   else
   {
      sdcard_ptr->VERSION2 = TRUE;
      c_size = (command.RESPONSE[1] >> 8) & 0x003FFFFF;
      sdcard_ptr->NUM_BLOCKS = (c_size + 1) << 10;
   }
   u16BlockSize.u16 = 512;

   /* Select card */
   command.COMMAND = ESDHC_CMD7;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = sdcard_ptr->ADDRESS;
   command.READ = FALSE;
   command.BLOCKS = 0;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return FALSE;
   }

   /* Set block size */
   command.COMMAND = ESDHC_CMD16;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = IO_SDCARD_BLOCK_SIZE;
   command.READ = FALSE;
   command.BLOCKS = 0;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return FALSE;
   }

   /* *************** Defaut: 4 bit width is used ***************** */
   /* Application specific command */
   command.COMMAND = ESDHC_CMD55;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = sdcard_ptr->ADDRESS;
   command.READ = FALSE;
   command.BLOCKS = 0;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return(FALSE);              /* Command IDLE fail*/
   }

   /* Set bus width == 4 */
   command.COMMAND = ESDHC_ACMD6;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = 2;
   command.READ = FALSE;
   command.BLOCKS = 0;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return(FALSE);              /* Command IDLE fail*/
   }

   param = ESDHC_BUS_WIDTH_4BIT;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SET_BUS_WIDTH, &param))
   {
      return(FALSE);              /* Command IDLE fail*/
   }

   /* Change baudrate to Highspeed*/
   param = 40000000;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SET_BAUDRATE, &param))
   {
      return (FALSE);
   }
   return(TRUE);

}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_sdcard_esdhc_read_block
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*    Reads sector (512 byte) from SD card with given index into given buffer.
*
*END*----------------------------------------------------------------------*/
void SD_Read_Block (PTR_LBA_APP_STRUCT lba_app_ptr)
{
   ESDHC_COMMAND_STRUCT command;
   uint_32 address;

   /* SD card data address adjustment */
   if (sdcard_ptr->SDHC)
   address = (uint_32)(lba_app_ptr->offset/512);
   else
   address = (uint_32)(lba_app_ptr->offset);

   /* Read block command */
   command.COMMAND = ESDHC_CMD17;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = (uint_32)address;
   command.READ = TRUE;
   command.BLOCKS = 1;
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return;
   }
   /* Read data */
   if (IO_SDCARD_BLOCK_SIZE != _esdhc_read(lba_app_ptr->buff_ptr, IO_SDCARD_BLOCK_SIZE))
   {
      return;
   }

}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _io_sdcard_esdhc_write_block
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*    Writes sector (512 byte) with given index to SD card from given buffer.
*
*END*----------------------------------------------------------------------*/
void SD_Write_Block (PTR_LBA_APP_STRUCT lba_app_ptr)
{
   ESDHC_COMMAND_STRUCT command;
   uint_32 param = 0;

   /* SD card data address adjustment */
   if (sdcard_ptr->SDHC)
   param = (uint_32)(lba_app_ptr->offset/512);
   else
   param = (uint_32)(lba_app_ptr->offset);

   /* Write block command */
   command.COMMAND = ESDHC_CMD24;
   command.TYPE = ESDHC_TYPE_NORMAL;
   command.ARGUMENT = (uint_32)param;
   command.READ = FALSE;
   command.BLOCKS = 1;
   if (ESDHC_OK != _esdhc_ioctl(IO_IOCTL_ESDHC_SEND_COMMAND, &command))
   {
      return;
   }

   /* Write data */
   if (IO_SDCARD_BLOCK_SIZE != _esdhc_write(lba_app_ptr->buff_ptr, IO_SDCARD_BLOCK_SIZE))
   {
      return;
   }

   /* Wait for transfer complete */
   if (ESDHC_OK != _esdhc_ioctl (IO_IOCTL_FLUSH_OUTPUT,&param))
   {
      return;
   }

   return;
}

/*********************************************************
* Name: SD_Card_Info
* Desc: Storage information of SD Card
* Parameter: None
* Return: None
**********************************************************/
void SD_Card_Info(uint_32_ptr max_blocks_ptr, uint_32_ptr block_size_ptr)
{
   *max_blocks_ptr = sdcard_ptr->NUM_BLOCKS;
   *block_size_ptr = u16BlockSize.u16;
}
#endif
/* EOF */
