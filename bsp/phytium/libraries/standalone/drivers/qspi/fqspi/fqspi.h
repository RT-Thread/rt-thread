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
 * FilePath: fqspi.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:00:55
 * Description:  This files is for the qspi functions related definitions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/3/29  first release
 * 1.1   wangxiaodong  2022/9/9   improve functions
 * 1.2   zhangyan      2022/12/7  improve functions
 */

#ifndef BSP_DRIVERS_FQSPI_H
#define BSP_DRIVERS_FQSPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "fkernel.h"
#include "ftypes.h"
#include "ferror_code.h"
#include "fdebug.h"
#include "fparameters.h"

#define FQSPI_SUCCESS      FT_SUCCESS
#define FQSPI_INVAL_PARAM  FT_MAKE_ERRCODE(ErrModBsp, ErrBspQSpi, 1)
#define FQSPI_NOT_READY    FT_MAKE_ERRCODE(ErrModBsp, ErrBspQSpi, 2)
#define FQSPI_NOT_ALLIGN   FT_MAKE_ERRCODE(ErrModBsp, ErrBspQSpi, 3)
#define FQSPI_NOT_SUPPORT  FT_MAKE_ERRCODE(ErrModBsp, ErrBspQSpi, 4)
#define FQSPI_TIMEOUT      FT_MAKE_ERRCODE(ErrModBsp, ErrBspQSpi, 5)

/* FQSPI Transfer mode, command-addr-data protocols */
typedef enum
{
    FQSPI_TRANSFER_1_1_1 = 0x0,
    FQSPI_TRANSFER_1_1_2 = 0x1,
    FQSPI_TRANSFER_1_1_4 = 0x2,
    FQSPI_TRANSFER_1_2_2 = 0x3,
    FQSPI_TRANSFER_1_4_4 = 0x4,
    FQSPI_TRANSFER_2_2_2 = 0x5,
    FQSPI_TRANSFER_4_4_4 = 0x6
} FQspiTransferMode;

/* FQSPI Flash Capcity type */
typedef enum
{
    FQSPI_FLASH_CAP_4MB = 0b000,
    FQSPI_FLASH_CAP_8MB = 0b001,
    FQSPI_FLASH_CAP_16MB = 0b010,
    FQSPI_FLASH_CAP_32MB = 0b011,
    FQSPI_FLASH_CAP_64MB = 0b100,
    FQSPI_FLASH_CAP_128MB = 0b101,
    FQSPI_FLASH_CAP_256MB = 0b110,
} FQspiFlashCapcityType;

/* FQSPI pclk divider type */
typedef enum
{
    FQSPI_SCK_DIV_128 = 0x0,
    FQSPI_SCK_DIV_2 = 0x1,
    FQSPI_SCK_DIV_4 = 0x2,
    FQSPI_SCK_DIV_8 = 0x3,
    FQSPI_SCK_DIV_16 = 0x4,
    FQSPI_SCK_DIV_32 = 0x5,
    FQSPI_SCK_DIV_64 = 0x6
} FQspiSckDivType;

/* FQSPI Address type */
typedef enum
{
    FQSPI_ADDR_SEL_3 = 0x0,
    FQSPI_ADDR_SEL_4 = 0x1
} FQspiAddrType;

/* Specifies if the Instruction need transfer address */
typedef enum
{
    FQSPI_CMD_ADDR_DISABLE = 0x0,
    FQSPI_CMD_ADDR_ENABLE = 0x1
} FQspiCmdAddrType;

/* Specifies if the Instruction have latency */
typedef enum
{
    FQSPI_CMD_LATENCY_DISABLE = 0x0,
    FQSPI_CMD_LATENCY_ENABLE = 0x1
} FQspiCmdLatencyType;

/* Specifies if the Instruction need transfer data */
typedef enum
{
    FQSPI_CMD_DATA_DISABLE = 0x0,
    FQSPI_CMD_DATA_ENABLE = 0x1
} FQspiCmdDataType;

/* Specifies if the Instruction use buffer */
typedef enum
{
    FQSPI_USE_BUFFER_DISABLE = 0x0,
    FQSPI_USE_BUFFER_ENABLE = 0x1
} FQspiUseBufferType;

/* Specifies if the Instruction need some execution time */
typedef enum
{
    FQSPI_WAIT_DISABLE = 0x0,
    FQSPI_WAIT_ENABLE = 0x1
} FQspiWaitType;


typedef enum
{
    FQSPI_XIP_EXIT = 0x0,
    FQSPI_XIP_ENTER = 0x1
} FQspiXIPState;

typedef struct
{
    u32 instance_id;  /* Id of device */
    uintptr base_addr; /* Base address of qspi */
    uintptr mem_start; /* Start address of qspi memory */
    u32 capacity;    /* Flash capacity */
    u32 dev_num;      /* Qspi device number */
    u32 channel;     /* channel number, cs number */
} FQspiConfig;

/* rd_cfg register */
typedef struct
{
    u8 rd_cmd : 8;  /* Specifies the Instruction to be sent */
    u8 rd_through : 1;
    u8 rd_transfer : 3;/* Specifies the Instruction tranfer Mode 1-1-1~4-4-4*/
    u8 rd_addr_sel : 1;/* Specifies the Instruction addr mode 3 byte addr or 4 byte addr*/
    u8 rd_latency : 1;    /* Specifies if the Instruction need read latency*/
    u8 mode_byte : 1;   /* Specifies if the Instruction need modifier*/
    u8 cmd_sign : 8;    /* Specifies the Instruction modifier*/
    u8 dummy : 5;        /* Specifies the Number of Dummy Cycles.*/
    u8 d_buffer : 1;    /* Specifies if the Instruction use buffer to read data*/
    u8 rd_sck_sel : 3;     /* Specifies the pclk division .*/
} FQspiRdCfgDef;

/* wr_cfg register */
typedef struct
{
    u8 wr_cmd : 8;  /* Specifies the Instruction to be sent */
    u16 reserved : 14;
    u8 wr_wait : 1;
    u8 wr_through : 1;
    u8 wr_transfer : 3;/* Specifies the Instruction tranfer Mode 1-1-1~4-4-4*/
    u8 wr_addr_sel : 1;/* Specifies the Instruction addr mode 3 byte addr or 4 byte addr*/
    u8 wr_mode : 1;   /* Specifies if the Instruction need modifier*/
    u8 wr_sck_sel : 3; /* Specifies the pclk division .*/
} FQspiWrCfgDef;

/* cmd_port register */
typedef struct
{
    u8 cmd : 8;  /* Specifies the Instruction to be sent */
    u8 reserved : 1;
    u8 wait : 1;
    u8 through : 1;
    u8 cs : 2;
    u8 transfer : 3;/* Specifies the Instruction tranfer Mode 1-1-1~4-4-4*/
    u8 cmd_addr : 1;    /* Specifies if the Instruction need transfer address*/
    u8 latency : 1;    /* Specifies if the Instruction need read latency*/
    u8 data_transfer : 1;    /* Specifies if the Instruction need tranfer data*/
    u8 addr_sel : 1;    /* Specifies the Instruction addr mode 3 byte addr or 4 byte addr*/
    u8 dummy : 5;        /* Specifies the Number of Dummy Cycles.*/
    u8 p_buffer : 1;    /* Specifies if the Instruction use buffer to read data*/
    u8 rw_num : 3;        /* Specifies the read or write bytes number.*/
    u8 sck_sel : 3;        /* Specifies the pclk division .*/
} FQspiCommandPortDef;

typedef struct
{
    u8 cs_hold;  /* Specifies the cs valid hold time */
    u8 cs_setup;   /* Specifies the cs valid setup time */
    u16 cs_delay; /* Specifies the cs delay time */
} FQspiCsTimingCfgDef;

typedef struct
{
    FQspiConfig config;
    FQspiRdCfgDef rd_cfg;
    FQspiWrCfgDef wr_cfg;
    FQspiCommandPortDef cmd_def;
    FQspiCsTimingCfgDef cs_timing_cfg;
    u32 is_ready;    /**< Device is initialized and ready */
    u32 flash_size;  /* size of QSPI flash */
    u8 mf_id;   /* manufacturer information */
} FQspiCtrl;

/* lookup FQSPI default Configuration parameters */
const FQspiConfig *FQspiLookupConfig(u32 instance_id);

/* set capacity and number of flash connect to qspi */
void FQspiSetCapacityAndNum(FQspiCtrl *pctrl);

/* qspi instance initialization */
FError FQspiCfgInitialize(FQspiCtrl *pctrl, const FQspiConfig *input_config_p);

/* qspi instance de-initialization */
void FQspiDeInitialize(FQspiCtrl *pctrl);

/* command port register config */
FError FQspiCommandPortConfig(FQspiCtrl *pctrl);

/* read register config */
FError FQspiRdCfgConfig(FQspiCtrl *pctrl);

/* write register config */
FError FQspiWrCfgConfig(FQspiCtrl *pctrl);

/* qspi cs number set */
void FQspiChannelSet(FQspiCtrl *pctrl, u32 channel);

/* qspi cs timing set */
void FQspiCsTimingSet(FQspiCtrl *pctrl, FQspiCsTimingCfgDef *cs_timing_cfg);

#ifdef __cplusplus
}
#endif

#endif
