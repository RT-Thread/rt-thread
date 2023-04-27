/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fqspi_flash.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-07-12 16:20:55
 * Description:  
 * This file is for S25FS256, GD25Q256, GD25Q64 norflash program, includes reading and writing registers and data,
 * Users can refer to this file to adapt chips from other manufacturers.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2021/11/12  first release
 * 1.1   wangxiaodong  2022/3/29   improve functions
 * 1.2   wangxiaodong  2022/7/5    adapt to e2000
 * 1.3   wangxiaodong  2022/9/9    improve functions
 * 1.4   zhangyan      2022/12/7   improve functions
 */

#ifndef FQSPI_FLASH_H
#define FQSPI_FLASH_H

#include "fkernel.h"
#include "ftypes.h"
#include "ferror_code.h"
#include "fqspi.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* qspi flash support manufacturer JEDEC ID */
#define FQSPI_FLASH_MF_ID_CYPRESS            0x01
#define FQSPI_FLASH_MF_ID_GIGADEVICE         0xC8
#define FQSPI_FLASH_MF_ID_BOYA               0x68

/* qspi flash supported information table */
#define FQSPI_FLASH_INFO_TABLE                                                                  \
    {                                                                                           \
        {"S25FS256S", FQSPI_FLASH_MF_ID_CYPRESS, 0x02, 0x19, FQSPI_FLASH_CAP_32MB},             \
        {"GD25Q32C", FQSPI_FLASH_MF_ID_GIGADEVICE, 0x40, 0x16, FQSPI_FLASH_CAP_4MB},            \
        {"GD25Q32E", FQSPI_FLASH_MF_ID_GIGADEVICE, 0x60, 0x16, FQSPI_FLASH_CAP_4MB},            \
        {"GD25Q64B", FQSPI_FLASH_MF_ID_GIGADEVICE, 0x40, 0x17, FQSPI_FLASH_CAP_8MB},            \
        {"GD25LQ128E", FQSPI_FLASH_MF_ID_GIGADEVICE, 0x40, 0x18, FQSPI_FLASH_CAP_16MB},         \
    	{"GD25LQ128E", FQSPI_FLASH_MF_ID_GIGADEVICE, 0x60, 0x18, FQSPI_FLASH_CAP_16MB},         \
        {"GD25QL256D", FQSPI_FLASH_MF_ID_GIGADEVICE, 0x60, 0x19, FQSPI_FLASH_CAP_32MB},         \
        {"BY25Q64BS", FQSPI_FLASH_MF_ID_BOYA, 0x40, 0x17, FQSPI_FLASH_CAP_8MB},                 \
        {"BY25Q128BS", FQSPI_FLASH_MF_ID_BOYA, 0x40, 0x18, FQSPI_FLASH_CAP_16MB},               \
        {"BY25Q32BS", FQSPI_FLASH_MF_ID_BOYA, 0x40, 0x16, FQSPI_FLASH_CAP_4MB}                  \
    }

#define FQSPI_FLASH_CMD_WRR 0x01        /* Write status register */
#define FQSPI_FLASH_CMD_PP 0x02         /* Page program */
#define FQSPI_FLASH_CMD_READ 0x03       /* Normal read data bytes */
#define FQSPI_FLASH_CMD_WRDI 0x04       /* Write disable */
#define FQSPI_FLASH_CMD_RDSR1 0x05      /* Read status register */
#define FQSPI_FLASH_CMD_WREN 0x06       /* Write enable */
#define FQSPI_FLASH_CMD_RDSR2 0x07      /* Read status register */
#define FQSPI_FLASH_CMD_FAST_READ 0x0B  /* Fast read data bytes */
#define FQSPI_FLASH_CMD_4FAST_READ 0x0C /* Fast read data bytes */
#define FQSPI_FLASH_CMD_DUAL_READ 0xBB  /* Dual read data bytes */
#define FQSPI_FLASH_CMD_4PP 0x12        /* Page program */
#define FQSPI_FLASH_CMD_4READ 0x13      /* Normal read data bytes */
#define FQSPI_FLASH_CMD_P4E 0x20        /* Erase 4kb sector */
#define FQSPI_FLASH_CMD_4P4E 0x21       /* Erase 4kb sector */
#define FQSPI_FLASH_CMD_QPP 0x32        /* Quad Page program */
#define FQSPI_FLASH_CMD_4QPP 0x34       /* Quad Page program */
#define FQSPI_FLASH_CMD_RDCR 0x35       /* Read config register */
#define FQSPI_FLASH_CMD_BE 0x60         /* Bulk erase */
#define FQSPI_FLASH_CMD_RDAR 0x65       /* Read Any Register  */
#define FQSPI_FLASH_CMD_DOR 0x3B        /* Dual read data bytes*/
#define FQSPI_FLASH_CMD_QOR 0x6B        /* Quad read data bytes */
#define FQSPI_FLASH_CMD_QWFR 0xE7       /* Quad word fast read data bytes */
#define FQSPI_FLASH_CMD_4QOR 0x6C       /* Quad read data bytes */
#define FQSPI_FLASH_CMD_WRAR 0x71       /* Write Any Register  */
#define FQSPI_FLASH_CMD_RDID 0x9F       /* Read JEDEC ID */
#define FQSPI_FLASH_CMD_4BAM 0xB7       /* Enter 4 Bytes Mode */
#define FQSPI_FLASH_CMD_4BE 0xC7        /* Bulk erase */
#define FQSPI_FLASH_CMD_SE 0xD8         /* Sector erase */
#define FQSPI_FLASH_CMD_4SE 0xDC        /* Sector erase */
#define FQSPI_FLASH_CMD_4BEX 0xE9       /* Exit 4 Bytes Mode */
#define FQSPI_FLASH_CMD_QIOR 0xEB       /* Quad read data bytes */
#define FQSPI_FLASH_CMD_4QIOR 0xEC      /* Quad read data bytes */
#define FQSPI_FLASH_CMD_SFDP 0x5A       /* Read JEDEC Serial Manu ID */
#define FQSPI_CMD_ENABLE_RESET 0x66     /* Software Reset Enable */
#define FQSPI_CMD_RESET 0x99            /* Software Reset */
#define FQSPI_FLASH_CMD_RDSR3 0x15      /* Read status register 3 */

/* boya flash */
#define FQSPI_FLASH_CMD_WRITE_SR2 0x31  /* Write status register 2 */
#define FQSPI_FLASH_CMD_WRITE_SR3 0x11  /* Write status register 3 */

#define FQSPI_BUSY_TIMEOUT_US           1000000
#define FQSPI_NOR_FLASH_STATE_BUSY      BIT(0)

#define FQSPI_FLASH_WP_ENABLE 0x7c      /* Write status register 2 */
#define FQSPI_FLASH_WP_DISABLE 0x00     /* Write status register 2 */
/* Read some flash information */
FError FQspiFlashSpecialInstruction(FQspiCtrl *pctrl, u8 cmd, u8 *buf, size_t len);

/* read flash sfdp-Serial Flash Discoverable Parameter */
FError FQspiFlashReadSfdp(FQspiCtrl *pctrl, u32 offset, u8 *buf, size_t len);

/* read flash register */
FError FQspiFlashReadReg(FQspiCtrl *pctrl, u32 offset, u8 *buf, size_t len);

/* write flash register */
FError FQspiFlashWriteReg(FQspiCtrl *pctrl, u8 command, const u8 *buf, size_t len);

/* read flash data config */
FError FQspiFlashReadDataConfig(FQspiCtrl *pctrl, u8 command);

/* read flash data */
size_t FQspiFlashReadData(FQspiCtrl *pctrl, u32 chip_addr, u8 *buf, size_t len);

/* write flash data */
FError FQspiFlashWriteData(FQspiCtrl *pctrl, u8 command, u32 chip_addr, const u8 *buf, size_t len);

/* flash erase */
FError FQspiFlashErase(FQspiCtrl *pctrl, u8 command, u32 offset);

/* flash write enable */
FError FQspiFlashEnableWrite(FQspiCtrl *pctrl);

/* flash write disable */
FError FQspiFlashDisableWrite(FQspiCtrl *pctrl);

/* wait flash command execution complete */
FError FQspiFlashWaitForCmd(FQspiCtrl *pctrl);

/* read flash data use register port */
FError FQspiFlashPortReadData(FQspiCtrl *pctrl, u8 cmd, u32 chip_addr, u8 *buf, size_t len);

/* write flash data use register port */
FError FQspiFlashPortWriteData(FQspiCtrl *pctrl, u8 cmd, u32 chip_addr, u8 *buf, size_t len);

/* detect flash information */
FError FQspiFlashDetect(FQspiCtrl *pctrl);

/* qspi write protect set */
FError FQspiFlashWProtectSet(FQspiCtrl *pctrl, boolean wprotect, u8 channel);

#ifdef __cplusplus
}
#endif

#endif
