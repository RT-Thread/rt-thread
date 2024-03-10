/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
**************************************************************************//*!
*
* @file spi.h
*
* @author
*
* @version
*
* @date May-28-2009
*
* @brief  This file is SPI Driver Header File
*****************************************************************************/
#ifndef __esdhc_kinetis__
#define __esdhc_kinetis__


/* Includes */
#include "usb_devapi.h"
/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** IO_SDCARD STRUCT
**
** The address of this structure is used to maintain SD card specific
** information.
*/
typedef struct io_sdcard_struct
{
   /* The number of blocks for the device */
   uint_32                NUM_BLOCKS;

   /* High capacity = block addressing */
   boolean                SDHC;

   /* Specification 2 or later card = different CSD register */
   boolean                VERSION2;

   /* Card address */
   uint_32                ADDRESS;

} SDCARD_STRUCT, *SDCARD_STRUCT_PTR;

typedef struct esdhc_command_struct
{
   uint_8  COMMAND;
   uint_8  TYPE;
   uint_32 ARGUMENT;
   boolean READ;
   uint_32 BLOCKS;
   uint_32 RESPONSE[4];

} ESDHC_COMMAND_STRUCT, *ESDHC_COMMAND_STRUCT_PTR;

typedef struct esdhc_info_struct
{
   /* The actual card status */
   uint_32                        CARD;

   /* The intermediate buffer */
   uint_32                        BUFFER[128];

} ESDHC_INFO_STRUCT, * ESDHC_INFO_STRUCT_PTR;
typedef const ESDHC_INFO_STRUCT *ESDHC_INFO_STRUCT_CPTR;
/*
** ESDHC_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a esdhc driver is initialized.
*/
typedef struct esdhc_init_struct
{
   /* The device number */
   uint_32 CHANNEL;

   /* The communication baud rate */
   uint_32 BAUD_RATE;

   /* The module input clock */
   uint_32 CLOCK_SPEED;

} ESDHC_INIT_STRUCT, * ESDHC_INIT_STRUCT_PTR;

typedef const ESDHC_INIT_STRUCT *ESDHC_INIT_STRUCT_CPTR;


/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

#define IO_SDCARD_BLOCK_SIZE_POWER   (9)
#define IO_SDCARD_BLOCK_SIZE         (1 << IO_SDCARD_BLOCK_SIZE_POWER)
/*----------------------------------------------------------------------
*
* ----------------------------------------------------------------------*/

#define BSP_ALARM_FREQUENCY                  (100)
#define SD_INVALID_PARAMETER                 -1
#define IO_ERROR_DEVICE_BUSY                 -1
#define IO_ERROR_DEVICE_INVALID              -1
#define IO_ERROR                             -1
#define IO_ERROR_INVALID_IOCTL_CMD           -1
#define IO_IOCTL_DEVICE_IDENTIFY             0x99
#define IO_IOCTL_FLUSH_OUTPUT                0x93

/* Element defines for ID array */
#define IO_IOCTL_ID_PHY_ELEMENT              (0)
#define IO_IOCTL_ID_LOG_ELEMENT              (1)
#define IO_IOCTL_ID_ATTR_ELEMENT             (2)
#define IO_DEV_TYPE_PHYS_ESDHC               (0x001C)
#define IO_DEV_TYPE_LOGICAL_MFS              (0x0004)

#define IO_DEV_ATTR_READ                     (0x0008)
#define IO_DEV_ATTR_REMOVE                   (0x0010)
#define IO_DEV_ATTR_SEEK                     (0x0020)
#define IO_DEV_ATTR_WRITE                    (0x0040)
#define IO_DEV_ATTR_BLOCK_MODE               (0x0200)

#define IO_ESDHC_ATTRIBS (IO_DEV_ATTR_READ | IO_DEV_ATTR_REMOVE | IO_DEV_ATTR_SEEK | IO_DEV_ATTR_WRITE | IO_DEV_ATTR_BLOCK_MODE)

#define ESDHC_XFERTYP_RSPTYP_NO              (0x00)
#define ESDHC_XFERTYP_RSPTYP_136             (0x01)
#define ESDHC_XFERTYP_RSPTYP_48              (0x02)
#define ESDHC_XFERTYP_RSPTYP_48BUSY          (0x03)

#define ESDHC_XFERTYP_CMDTYP_ABORT           (0x03)

#define ESDHC_PROCTL_EMODE_INVARIANT         (0x02)

#define ESDHC_PROCTL_DTW_1BIT                (0x00)
#define ESDHC_PROCTL_DTW_4BIT                (0x01)
#define ESDHC_PROCTL_DTW_8BIT                (0x10)

/* ********************************************************** */

#define IO_TYPE_ESDHC              0x13

/*
** IOCTL calls specific to eSDHC
*/
#define IO_IOCTL_ESDHC_INIT                  0x01
#define IO_IOCTL_ESDHC_SEND_COMMAND          0x02
#define IO_IOCTL_ESDHC_GET_CARD              0x03
#define IO_IOCTL_ESDHC_GET_BAUDRATE          0x04
#define IO_IOCTL_ESDHC_SET_BAUDRATE          0x05
#define IO_IOCTL_ESDHC_GET_BUS_WIDTH         0x06
#define IO_IOCTL_ESDHC_SET_BUS_WIDTH         0x07
#define IO_IOCTL_ESDHC_GET_BLOCK_SIZE        0x08
#define IO_IOCTL_ESDHC_SET_BLOCK_SIZE        0x09

/* ESDHC error codes */
#define ESDHC_OK                             (0x00)
#define DRIVER_ERROR_BASE                    (0xA000)
#define ESDHC_ERROR_BASE                     (DRIVER_ERROR_BASE | 0x0C00)
#define ESDHC_ERROR_INIT_FAILED              (ESDHC_ERROR_BASE | 0x01)
#define ESDHC_ERROR_COMMAND_FAILED           (ESDHC_ERROR_BASE | 0x02)
#define ESDHC_ERROR_COMMAND_TIMEOUT          (ESDHC_ERROR_BASE | 0x03)
#define ESDHC_ERROR_DATA_TRANSFER            (ESDHC_ERROR_BASE | 0x04)
#define ESDHC_ERROR_INVALID_BUS_WIDTH        (ESDHC_ERROR_BASE | 0x05)

/* ESDHC bus widths */
#define ESDHC_BUS_WIDTH_1BIT                 (0x00)
#define ESDHC_BUS_WIDTH_4BIT                 (0x01)
#define ESDHC_BUS_WIDTH_8BIT                 (0x02)

/* ESDHC card types */
#define ESDHC_CARD_NONE                      (0x00)
#define ESDHC_CARD_UNKNOWN                   (0x01)
#define ESDHC_CARD_SD                        (0x02)
#define ESDHC_CARD_SDHC                      (0x03)
#define ESDHC_CARD_SDIO                      (0x04)
#define ESDHC_CARD_SDCOMBO                   (0x05)
#define ESDHC_CARD_SDHCCOMBO                 (0x06)
#define ESDHC_CARD_MMC                       (0x07)
#define ESDHC_CARD_CEATA                     (0x08)

/* ESDHC command types */
#define ESDHC_TYPE_NORMAL                    (0x00)
#define ESDHC_TYPE_SUSPEND                   (0x01)
#define ESDHC_TYPE_RESUME                    (0x02)
#define ESDHC_TYPE_ABORT                     (0x03)
#define ESDHC_TYPE_SWITCH_BUSY               (0x04)


/******************************* SD Card Standard Commands **********************************/
#define ESDHC_CMD0                           (0)
#define ESDHC_CMD1                           (1)
#define ESDHC_CMD2                           (2)
#define ESDHC_CMD3                           (3)
#define ESDHC_CMD4                           (4)
#define ESDHC_CMD5                           (5)
#define ESDHC_CMD6                           (6)
#define ESDHC_CMD7                           (7)
#define ESDHC_CMD8                           (8)
#define ESDHC_CMD9                           (9)
#define ESDHC_CMD10                          (10)
#define ESDHC_CMD11                          (11)
#define ESDHC_CMD12                          (12)
#define ESDHC_CMD13                          (13)
#define ESDHC_CMD15                          (15)
#define ESDHC_CMD16                          (16)
#define ESDHC_CMD17                          (17)
#define ESDHC_CMD18                          (18)
#define ESDHC_CMD20                          (20)
#define ESDHC_CMD24                          (24)
#define ESDHC_CMD25                          (25)
#define ESDHC_CMD26                          (26)
#define ESDHC_CMD27                          (27)
#define ESDHC_CMD28                          (28)
#define ESDHC_CMD29                          (29)
#define ESDHC_CMD30                          (30)
#define ESDHC_CMD32                          (32)
#define ESDHC_CMD33                          (33)
#define ESDHC_CMD34                          (34)
#define ESDHC_CMD35                          (35)
#define ESDHC_CMD36                          (36)
#define ESDHC_CMD37                          (37)
#define ESDHC_CMD38                          (38)
#define ESDHC_CMD39                          (39)
#define ESDHC_CMD40                          (40)
#define ESDHC_CMD42                          (42)
#define ESDHC_CMD52                          (52)
#define ESDHC_CMD53                          (53)
#define ESDHC_CMD55                          (55)
#define ESDHC_CMD56                          (56)
#define ESDHC_CMD60                          (60)
#define ESDHC_CMD61                          (61)
#define ESDHC_ACMD6                          (0x40 + 6)
#define ESDHC_ACMD13                         (0x40 + 13)
#define ESDHC_ACMD22                         (0x40 + 22)
#define ESDHC_ACMD23                         (0x40 + 23)
#define ESDHC_ACMD41                         (0x40 + 41)
#define ESDHC_ACMD42                         (0x40 + 42)
#define ESDHC_ACMD51                         (0x40 + 51)


/*--------------------------------------------------------------------------*/
/*
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

   extern int_32 _esdhc_read ( uint_8_ptr, int_32);
   extern int_32 _esdhc_write ( uint_8_ptr, int_32);
   extern int_32 _esdhc_ioctl ( uint_32, pointer);


#ifdef __cplusplus
}
#endif

#endif /* __esdhc_kinetis__ */
