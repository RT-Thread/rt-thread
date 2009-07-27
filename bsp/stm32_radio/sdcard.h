																	/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : sdcard.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      SD Card driver firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SDCARD_H
#define __SDCARD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  /* SDIO specific error defines */
  SD_CMD_CRC_FAIL                    = (1), /* Command response received (but CRC check failed) */
  SD_DATA_CRC_FAIL                   = (2), /* Data bock sent/received (CRC check Failed) */
  SD_CMD_RSP_TIMEOUT                 = (3), /* Command response timeout */
  SD_DATA_TIMEOUT                    = (4), /* Data time out */
  SD_TX_UNDERRUN                     = (5), /* Transmit FIFO under-run */
  SD_RX_OVERRUN                      = (6), /* Receive FIFO over-run */
  SD_START_BIT_ERR                   = (7), /* Start bit not detected on all data signals in widE bus mode */
  SD_CMD_OUT_OF_RANGE                = (8), /* CMD's argument was out of range.*/
  SD_ADDR_MISALIGNED                 = (9), /* Misaligned address */
  SD_BLOCK_LEN_ERR                   = (10), /* Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
  SD_ERASE_SEQ_ERR                   = (11), /* An error in the sequence of erase command occurs.*/
  SD_BAD_ERASE_PARAM                 = (12), /* An Invalid selection for erase groups */
  SD_WRITE_PROT_VIOLATION            = (13), /* Attempt to program a write protect block */
  SD_LOCK_UNLOCK_FAILED              = (14), /* Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
  SD_COM_CRC_FAILED                  = (15), /* CRC check of the previous command failed */
  SD_ILLEGAL_CMD                     = (16), /* Command is not legal for the card state */
  SD_CARD_ECC_FAILED                 = (17), /* Card internal ECC was applied but failed to correct the data */
  SD_CC_ERROR                        = (18), /* Internal card controller error */
  SD_GENERAL_UNKNOWN_ERROR           = (19), /* General or Unknown error */
  SD_STREAM_READ_UNDERRUN            = (20), /* The card could not sustain data transfer in stream read operation. */
  SD_STREAM_WRITE_OVERRUN            = (21), /* The card could not sustain data programming in stream mode */
  SD_CID_CSD_OVERWRITE               = (22), /* CID/CSD overwrite error */
  SD_WP_ERASE_SKIP                   = (23), /* only partial address space was erased */
  SD_CARD_ECC_DISABLED               = (24), /* Command has been executed without using internal ECC */
  SD_ERASE_RESET                     = (25), /* Erase sequence was cleared before executing because an out of erase sequence command was received */
  SD_AKE_SEQ_ERROR                   = (26), /* Error in sequence of authentication. */
  SD_INVALID_VOLTRANGE               = (27),
  SD_ADDR_OUT_OF_RANGE               = (28),
  SD_SWITCH_ERROR                    = (29),
  SD_SDIO_DISABLED                   = (30),
  SD_SDIO_FUNCTION_BUSY              = (31),
  SD_SDIO_FUNCTION_FAILED            = (32),
  SD_SDIO_UNKNOWN_FUNCTION           = (33),

  /* Standard error defines */
  SD_INTERNAL_ERROR, 
  SD_NOT_CONFIGURED,
  SD_REQUEST_PENDING, 
  SD_REQUEST_NOT_APPLICABLE, 
  SD_INVALID_PARAMETER,  
  SD_UNSUPPORTED_FEATURE,  
  SD_UNSUPPORTED_HW,  
  SD_ERROR,  
  SD_OK,  
} SD_Error;

/* SDIO Commands  Index */
#define SDIO_GO_IDLE_STATE                       ((u8)0)
#define SDIO_SEND_OP_COND                        ((u8)1)
#define SDIO_ALL_SEND_CID                        ((u8)2)
#define SDIO_SET_REL_ADDR                        ((u8)3) /* SDIO_SEND_REL_ADDR for SD Card */
#define SDIO_SET_DSR                             ((u8)4)
#define SDIO_SDIO_SEN_OP_COND                    ((u8)5)
#define SDIO_HS_SWITCH                           ((u8)6)
#define SDIO_SEL_DESEL_CARD                      ((u8)7)
#define SDIO_HS_SEND_EXT_CSD                     ((u8)8)
#define SDIO_SEND_CSD                            ((u8)9)
#define SDIO_SEND_CID                            ((u8)10)
#define SDIO_READ_DAT_UNTIL_STOP                 ((u8)11) /* SD Card doesn't support it */
#define SDIO_STOP_TRANSMISSION                   ((u8)12)
#define SDIO_SEND_STATUS                         ((u8)13)
#define SDIO_HS_BUSTEST_READ                     ((u8)14)
#define SDIO_GO_INACTIVE_STATE                   ((u8)15)
#define SDIO_SET_BLOCKLEN                        ((u8)16)
#define SDIO_READ_SINGLE_BLOCK                   ((u8)17)
#define SDIO_READ_MULT_BLOCK                     ((u8)18)
#define SDIO_HS_BUSTEST_WRITE                    ((u8)19)
#define SDIO_WRITE_DAT_UNTIL_STOP                ((u8)20) /* SD Card doesn't support it */
#define SDIO_SET_BLOCK_COUNT                     ((u8)23) /* SD Card doesn't support it */
#define SDIO_WRITE_SINGLE_BLOCK                  ((u8)24)
#define SDIO_WRITE_MULT_BLOCK                    ((u8)25)
#define SDIO_PROG_CID                            ((u8)26) /* reserved for manufacturers */
#define SDIO_PROG_CSD                            ((u8)27)
#define SDIO_SET_WRITE_PROT                      ((u8)28)
#define SDIO_CLR_WRITE_PROT                      ((u8)29)
#define SDIO_SEND_WRITE_PROT                     ((u8)30)
#define SDIO_SD_ERASE_GRP_START                  ((u8)32) /* To set the address of the first write
                                                             block to be erased. (For SD card only) */
#define SDIO_SD_ERASE_GRP_END                    ((u8)33) /* To set the address of the last write block of the
                                                             continuous range to be erased. (For SD card only) */
#define SDIO_ERASE_GRP_START                     ((u8)35) /* To set the address of the first write block to be erased.
                                                             (For MMC card only spec 3.31) */

#define SDIO_ERASE_GRP_END                       ((u8)36) /* To set the address of the last write block of the
                                                             continuous range to be erased. (For MMC card only spec 3.31) */

#define SDIO_ERASE                               ((u8)38)
#define SDIO_FAST_IO                             ((u8)39) /* SD Card doesn't support it */
#define SDIO_GO_IRQ_STATE                        ((u8)40) /* SD Card doesn't support it */
#define SDIO_LOCK_UNLOCK                         ((u8)42)
#define SDIO_APP_CMD                             ((u8)55)
#define SDIO_GEN_CMD                             ((u8)56)
#define SDIO_NO_CMD                              ((u8)64)

/* Following commands are SD Card Specific commands.
   SDIO_APP_CMD should be sent before sending these
   commands. */
#define SDIO_APP_SD_SET_BUSWIDTH                 ((u8)6)  /* For SD Card only */
#define SDIO_SD_APP_STAUS                        ((u8)13) /* For SD Card only */
#define SDIO_SD_APP_SEND_NUM_WRITE_BLOCKS        ((u8)22) /* For SD Card only */
#define SDIO_SD_APP_OP_COND                      ((u8)41) /* For SD Card only */
#define SDIO_SD_APP_SET_CLR_CARD_DETECT          ((u8)42) /* For SD Card only */
#define SDIO_SD_APP_SEND_SCR                     ((u8)51) /* For SD Card only */
#define SDIO_SDIO_RW_DIRECT                      ((u8)52) /* For SD I/O Card only */
#define SDIO_SDIO_RW_EXTENDED                    ((u8)53) /* For SD I/O Card only */

/* Following commands are SD Card Specific security commands.
   SDIO_APP_CMD should be sent before sending these commands. */
#define SDIO_SD_APP_GET_MKB                      ((u8)43) /* For SD Card only */
#define SDIO_SD_APP_GET_MID                      ((u8)44) /* For SD Card only */
#define SDIO_SD_APP_SET_CER_RN1                  ((u8)45) /* For SD Card only */
#define SDIO_SD_APP_GET_CER_RN2                  ((u8)46) /* For SD Card only */
#define SDIO_SD_APP_SET_CER_RES2                 ((u8)47) /* For SD Card only */
#define SDIO_SD_APP_GET_CER_RES1                 ((u8)48) /* For SD Card only */
#define SDIO_SD_APP_SECURE_READ_MULTIPLE_BLOCK   ((u8)18) /* For SD Card only */
#define SDIO_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK  ((u8)25) /* For SD Card only */
#define SDIO_SD_APP_SECURE_ERASE                 ((u8)38) /* For SD Card only */
#define SDIO_SD_APP_CHANGE_SECURE_AREA           ((u8)49) /* For SD Card only */
#define SDIO_SD_APP_SECURE_WRITE_MKB             ((u8)48) /* For SD Card only */

typedef enum
{
  SD_NO_TRANSFER  = 0,
  SD_TRANSFER_IN_PROGRESS
} SDTransferState;

typedef struct
{
  u16 TransferredBytes;
  SD_Error TransferError;
  u8  padding;
} SDLastTransferInfo;

typedef struct       /* Card Specific Data */
{
  vu8  CSDStruct;            /* CSD structure */
  vu8  SysSpecVersion;       /* System specification version */
  vu8  Reserved1;            /* Reserved */
  vu8  TAAC;                 /* Data read access-time 1 */
  vu8  NSAC;                 /* Data read access-time 2 in CLK cycles */
  vu8  MaxBusClkFrec;        /* Max. bus clock frequency */
  vu16 CardComdClasses;      /* Card command classes */
  vu8  RdBlockLen;           /* Max. read data block length */
  vu8  PartBlockRead;        /* Partial blocks for read allowed */
  vu8  WrBlockMisalign;      /* Write block misalignment */
  vu8  RdBlockMisalign;      /* Read block misalignment */
  vu8  DSRImpl;              /* DSR implemented */
  vu8  Reserved2;            /* Reserved */
  vu32 DeviceSize;           /* Device Size */
  vu8  MaxRdCurrentVDDMin;   /* Max. read current @ VDD min */
  vu8  MaxRdCurrentVDDMax;   /* Max. read current @ VDD max */
  vu8  MaxWrCurrentVDDMin;   /* Max. write current @ VDD min */
  vu8  MaxWrCurrentVDDMax;   /* Max. write current @ VDD max */
  vu8  DeviceSizeMul;        /* Device size multiplier */
  vu8  EraseGrSize;          /* Erase group size */
  vu8  EraseGrMul;           /* Erase group size multiplier */
  vu8  WrProtectGrSize;      /* Write protect group size */
  vu8  WrProtectGrEnable;    /* Write protect group enable */
  vu8  ManDeflECC;           /* Manufacturer default ECC */
  vu8  WrSpeedFact;          /* Write speed factor */
  vu8  MaxWrBlockLen;        /* Max. write data block length */
  vu8  WriteBlockPaPartial;  /* Partial blocks for write allowed */
  vu8  Reserved3;            /* Reserded */
  vu8  ContentProtectAppli;  /* Content protection application */
  vu8  FileFormatGrouop;     /* File format group */
  vu8  CopyFlag;             /* Copy flag (OTP) */
  vu8  PermWrProtect;        /* Permanent write protection */
  vu8  TempWrProtect;        /* Temporary write protection */
  vu8  FileFormat;           /* File Format */
  vu8  ECC;                  /* ECC code */
  vu8  CSD_CRC;              /* CSD CRC */
  vu8  Reserved4;            /* always 1*/
} SD_CSD;

typedef struct      /*Card Identification Data*/
{
  vu8  ManufacturerID;       /* ManufacturerID */
  vu16 OEM_AppliID;          /* OEM/Application ID */
  vu32 ProdName1;            /* Product Name part1 */
  vu8  ProdName2;            /* Product Name part2*/
  vu8  ProdRev;              /* Product Revision */
  vu32 ProdSN;               /* Product Serial Number */
  vu8  Reserved1;            /* Reserved1 */
  vu16 ManufactDate;         /* Manufacturing Date */
  vu8  CID_CRC;              /* CID CRC */
  vu8  Reserved2;            /* always 1 */
} SD_CID;

typedef struct
{
  SD_CSD SD_csd;
  SD_CID SD_cid;
  u32 CardCapacity; /* Card Capacity */
  u32 CardBlockSize; /* Card Block Size */
  u16 RCA;
  u8 CardType;
} SD_CardInfo;

/* Exported constants --------------------------------------------------------*/
#define SD_DMA_MODE                     ((u32)0x00000000)
#define SD_INTERRUPT_MODE               ((u32)0x00000001)
#define SD_POLLING_MODE                 ((u32)0x00000002)

/* Supported Memory Cards */
#define SDIO_STD_CAPACITY_SD_CARD_V1_1     ((u32)0x0)
#define SDIO_STD_CAPACITY_SD_CARD_V2_0     ((u32)0x1)
#define SDIO_HIGH_CAPACITY_SD_CARD         ((u32)0x2)
#define SDIO_MULTIMEDIA_CARD               ((u32)0x3)
#define SDIO_SECURE_DIGITAL_IO_CARD        ((u32)0x4)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD    ((u32)0x5)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD  ((u32)0x6)
#define SDIO_HIGH_CAPACITY_MMC_CARD        ((u32)0x7)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
SD_Error SD_Init(void);
SD_Error SD_PowerON(void);
SD_Error SD_PowerOFF(void);
SD_Error SD_InitializeCards(void);
SD_Error SD_GetCardInfo(SD_CardInfo *cardinfo);
SD_Error SD_EnableWideBusOperation(u32 WideMode);
SD_Error SD_SetDeviceMode(u32 Mode);
SD_Error SD_SelectDeselect(u32 addr);
SD_Error SD_ReadBlock(u32 addr, u32 *readbuff, u16 BlockSize);
SD_Error SD_ReadMultiBlocks(u32 addr, u32 *readbuff, u16 BlockSize, u32 NumberOfBlocks);
SD_Error SD_WriteBlock(u32 addr, u32 *writebuff, u16 BlockSize);
SD_Error SD_WriteMultiBlocks(u32 addr, u32 *writebuff, u16 BlockSize, u32 NumberOfBlocks);
SDTransferState SD_GetTransferState(void);
SD_Error SD_StopTransfer(void);
SD_Error SD_Erase(u32 startaddr, u32 endaddr);
SD_Error SD_SendStatus(u32 *pcardstatus);
SD_Error SD_SendSDStatus(u32 *psdstatus);
SD_Error SD_ProcessIRQSrc(void);

#endif /* __SDCARD_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
