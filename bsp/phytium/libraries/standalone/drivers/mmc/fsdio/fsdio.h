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
 * FilePath: fsdio.h
 * Date: 2022-05-26 16:20:52
 * LastEditTime: 2022-05-26 16:20:53
 * Description:  This file is for sdio user interface definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 1.2   zhugengyu  2022/7/15    adopt to e2000
 * 1.3   zhugengyu  2022/11/23   fix multi-block rw issues
 */

#ifndef  FSDIO_H
#define  FSDIO_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif
/************************** Constant Definitions *****************************/

/* SDIO driver error code */
#define FSDIO_SUCCESS               FT_SUCCESS
#define FSDIO_ERR_TIMEOUT           FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 1)
#define FSDIO_ERR_NOT_INIT          FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 2)
#define FSDIO_ERR_SHORT_BUF         FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 3)
#define FSDIO_ERR_NOT_SUPPORT       FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 4)
#define FSDIO_ERR_INVALID_STATE     FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 5)
#define FSDIO_ERR_TRANS_TIMEOUT     FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 6)
#define FSDIO_ERR_CMD_TIMEOUT       FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 7)
#define FSDIO_ERR_NO_CARD           FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 8)
#define FSDIO_ERR_BUSY              FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 9)
#define FSDIO_ERR_DMA_BUF_UNALIGN   FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 10)

typedef enum
{
    FSDIO_IDMA_TRANS_MODE, /* DMA trans mode */
    FSDIO_PIO_TRANS_MODE, /* NO-DMA trans by read/write Fifo */
} FSdioTransMode; /* SDIO trans mode */

typedef enum
{
    FSDIO_GENERAL_INTR, /* interrupt status belongs to controller */
    FSDIO_IDMA_INTR,    /* interrupt status belongs to DMA */
} FSdioIntrType; /* SDIO interrupt status type */

typedef enum
{
    FSDIO_SD_3_3V_VOLTAGE = 0, /* 3.3v */
    FSDIO_SD_1_8V_VOLTAGE /* 1.8v */
} FSdioVoltageType; /* SDIO card voltage type */

typedef enum
{
    FSDIO_EVT_CARD_DETECTED = 0, /* card detected event */
    FSDIO_EVT_CMD_DONE, /* cmd transfer finish event */
    FSDIO_EVT_DATA_DONE, /* cmd with data transfer finish event */
    FSDIO_EVT_ERR_OCCURE, /* error occurred in transfer */

    FSDIO_NUM_OF_EVT
} FSdioEvtType; /* SDIO event type */

#define FSDIO_SD_400KHZ                 400000U
#define FSDIO_SD_25_MHZ                 25000000U
#define FSDIO_SD_50_MHZ                 50000000U
/**************************** Type Definitions *******************************/
typedef struct _FSdio FSdio;

typedef void (*FSdioRelaxHandler)(void);
typedef void (*FSdioEvtHandler)(FSdio *const instance_p, void *args, u32 status, u32 dmac_status);

typedef struct
{
    u32 attribute; /* ds0 */
#define FSDIO_IDMAC_DES0_DIC    BIT(1)/* 内部描述表不触发TI/RI中断 */
#define FSDIO_IDMAC_DES0_LD     BIT(2)/* 数据的最后一个描述符 */
#define FSDIO_IDMAC_DES0_FD     BIT(3)/* 数据的第一个描述符 */
#define FSDIO_IDMAC_DES0_CH     BIT(4)/* 链接下一个描述符地址 */
#define FSDIO_IDMAC_DES0_ER     BIT(5)/* 链表已经到达最后一个链表 */
#define FSDIO_IDMAC_DES0_CES    BIT(30)/* RINTSTS寄存器错误汇总 */
#define FSDIO_IDMAC_DES0_OWN    BIT(31)/* 描述符关联DMA，完成传输后该位置置0 */
    u32 non1; /* ds1 --> unused */
    u32 len; /* ds2 bit[25:13] buffer2 size，bit[12:0] buffer1 size*/
#define FSDIO_IDMAC_DES2_BUF1_MASK      GENMASK(12, 0)
#define FSDIO_IDMAC_DES2_BUF1_SIZE(x)  (FSDIO_IDMAC_DES2_BUF1_MASK & (x))
#define FSDIO_IDMAC_DES2_BUF2_MASK      GENMASK(25, 13)
#define FSDIO_IDMAC_DES2_BUF2_SIZE(x)  (FSDIO_IDMAC_DES2_BUF2_MASK & (x << 13))
    u32 non2; /* ds3 --> unused */
    u32 addr_lo; /* ds4 Lower 32-bits of Buffer Address Pointer 1 --> buffer 1 */
    u32 addr_hi; /* ds5 Upper 32-bits of Buffer Address Pointer 1 */
    u32 desc_lo; /* ds6 Lower 32-bits of Next Descriptor Address --> buffer 2 */
    u32 desc_hi; /* ds7 Upper 32-bits of Next Descriptor Address */
} __attribute__((packed)) __attribute((aligned(4))) FSdioIDmaDesc;  /* SDIO DMA descriptr */

typedef struct
{
    volatile FSdioIDmaDesc *first_desc; /* first descriptor in the list */
    u32 desc_num; /* num of descriptors in the list */
} FSdioIDmaDescList; /* SDIO DMA descriptors list */

typedef struct
{
    u8 *buf; /* trans buffer */
    u32 blksz; /* card block size */
    u32 blkcnt; /* num of block in trans */
    u32 datalen; /* bytes in trans */
} FSdioData; /* SDIO trans data */

typedef struct
{
    u32 cmdidx; /* command index */
    u32 cmdarg; /* command argument */
    u32 response[4]; /* command response buffer */
    u32 flag; /* command flags */
#define FSDIO_CMD_FLAG_NEED_INIT         BIT(1) /* need initialization */
#define FSDIO_CMD_FLAG_EXP_RESP          BIT(2) /* need reply */
#define FSDIO_CMD_FLAG_EXP_LONG_RESP     BIT(3) /* need 136 bits long reply */
#define FSDIO_CMD_FLAG_NEED_RESP_CRC     BIT(4) /* need CRC */
#define FSDIO_CMD_FLAG_EXP_DATA          BIT(5) /* need trans data */
#define FSDIO_CMD_FLAG_WRITE_DATA        BIT(6) /* need trans data to write card */
#define FSDIO_CMD_FLAG_READ_DATA         BIT(7) /* need trans data to read card */
#define FSDIO_CMD_FLAG_NEED_AUTO_STOP    BIT(8) /* need auto stop after command */
#define FSDIO_CMD_FLAG_ADTC              BIT(9) /* need ADTC */
#define FSDIO_CMD_FLAG_SWITCH_VOLTAGE    BIT(10) /* need switch voltage */
    FSdioData *data_p; /* SDIO trans data */
    volatile boolean success; /* TRUE: comand and data transfer success */
} FSdioCmdData; /* SDIO trans command and data */

typedef struct
{
    u32            instance_id; /* Device instance id */
    uintptr        base_addr;   /* Device base address */
    u32            irq_num;     /* Interrupt num */
    FSdioTransMode trans_mode;  /* Trans mode, PIO/DMA */
    FSdioVoltageType voltage;   /* Card voltage type */
    boolean        non_removable; /* No removeable media, e.g eMMC */
    boolean        filp_resp_byte_order; /* Some SD protocol implmentation may not do byte-order filp */
} FSdioConfig; /* SDIO intance configuration */

typedef struct _FSdio
{
    FSdioConfig         config;      /* Current active configs */
    u32                 is_ready;    /* Device is initialized and ready */
    FSdioIDmaDescList   desc_list;   /* DMA descriptor list, valid in DMA trans mode */
    FSdioEvtHandler     evt_handlers[FSDIO_NUM_OF_EVT]; /* call-backs for interrupt event */
    void                *evt_args[FSDIO_NUM_OF_EVT]; /* arguments for event call-backs */
    FSdioRelaxHandler   relax_handler;
    u32                 prev_cmd; /* record previous command code */
} FSdio; /* SDIO intance */
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* Get the device instance default configure  */
const FSdioConfig *FSdioLookupConfig(u32 instance_id);

/* initialization SDIO controller instance */
FError FSdioCfgInitialize(FSdio *const instance_p, const FSdioConfig *cofig_p);

/* deinitialization SDIO controller instance */
void FSdioDeInitialize(FSdio *const instance_p);

/* Setup DMA descriptor for SDIO controller instance */
FError FSdioSetIDMAList(FSdio *const instance_p, volatile FSdioIDmaDesc *desc, u32 desc_num);

/* Set the Card clock freqency */
FError FSdioSetClkFreq(FSdio *const instance_p, u32 input_clk_hz);

/* Get the real Card clock freqency */
u32 FSdioGetClkFreq(FSdio *const instance_p);

/* Start command and data transfer in DMA mode */
FError FSdioDMATransfer(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);

/* Wait DMA transfer finished by poll */
FError FSdioPollWaitDMAEnd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);

/* Start command and data transfer in PIO mode */
FError FSdioPIOTransfer(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);

/* Wait PIO transfer finished by poll */
FError FSdioPollWaitPIOEnd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);

/* Get cmd response and received data after wait poll status or interrupt signal */
FError FSdioGetCmdResponse(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);

/* Get SDIO controller interrupt mask */
u32 FSdioGetInterruptMask(FSdio *const instance_p, FSdioIntrType intr_type);

/* Enable/Disable SDIO controller interrupt */
void FSdioSetInterruptMask(FSdio *const instance_p, FSdioIntrType type, u32 set_mask, boolean enable);

/* Interrupt handler for SDIO instance */
void FSdioInterruptHandler(s32 vector, void *param);

/* Reset controller from error state */
FError FSdioRestart(FSdio *const instance_p);

/* Register event call-back function as handler for interrupt events */
void FSdioRegisterEvtHandler(FSdio *const instance_p, FSdioEvtType evt, FSdioEvtHandler handler, void *handler_arg);

/* Register sleep call-back function */
void FSdioRegisterRelaxHandler(FSdio *const instance_p, FSdioRelaxHandler relax_handler);

/* Dump all register value of SDIO instance */
void FSdioDumpRegister(uintptr base_addr);

/* Dump command and data info */
void FSdioDumpCmdInfo(FSdioCmdData *const cmd_data);

#ifdef __cplusplus
}
#endif


#endif