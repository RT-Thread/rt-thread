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
 * FilePath: fsdif.h
 * Date: 2022-05-26 16:20:52
 * LastEditTime: 2022-05-26 16:20:53
 * Description:  This file is for sdif user interface definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 1.2   zhugengyu  2022/7/15    adopt to e2000
 * 1.3   zhugengyu  2022/11/23   fix multi-block rw issues
 * 2.0   zhugengyu  2023/9/16    rename as sdif, support SD 3.0 and rework clock timing
 * 2.1   zhugengyu  2023/10/23   add sdio interrupt handler
 */

#ifndef  FSDIF_H
#define  FSDIF_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif
/************************** Constant Definitions *****************************/

/* SDIF driver error code */
#define FSDIF_SUCCESS               FT_SUCCESS
#define FSDIF_ERR_TIMEOUT           FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 1)
#define FSDIF_ERR_NOT_INIT          FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 2)
#define FSDIF_ERR_SHORT_BUF         FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 3)
#define FSDIF_ERR_NOT_SUPPORT       FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 4)
#define FSDIF_ERR_INVALID_STATE     FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 5)
#define FSDIF_ERR_TRANS_TIMEOUT     FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 6)
#define FSDIF_ERR_CMD_TIMEOUT       FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 7)
#define FSDIF_ERR_NO_CARD           FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 8)
#define FSDIF_ERR_BUSY              FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 9)
#define FSDIF_ERR_DMA_BUF_UNALIGN   FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 10)
#define FSDIF_ERR_INVALID_TIMING    FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 11)

typedef enum
{
    FSDIF_IDMA_TRANS_MODE, /* DMA trans mode */
    FSDIF_PIO_TRANS_MODE, /* NO-DMA trans by read/write Fifo */
} FSdifTransMode; /* SDIF trans mode */

typedef enum
{
    FSDIF_GENERAL_INTR, /* interrupt status belongs to controller */
    FSDIF_IDMA_INTR,    /* interrupt status belongs to DMA */
} FSdifIntrType; /* SDIF interrupt status type */

typedef enum
{
    FSDIF_EVT_CARD_DETECTED = 0, /* card detected event */
    FSDIF_EVT_CMD_DONE, /* cmd transfer finish event */
    FSDIF_EVT_DATA_DONE, /* cmd with data transfer finish event */
    FSDIF_EVT_SDIO_IRQ, /* sdio card customized event */
    FSDIF_EVT_ERR_OCCURE, /* error occurred in transfer */

    FSDIF_NUM_OF_EVT
} FSdifEvtType; /* SDIF event type */

typedef enum
{
    FSDIF_CLK_SPEED_400KHZ = 400000U,
    FSDIF_CLK_SPEED_25_MHZ = 25000000U,
    FSDIF_CLK_SPEED_26_MHZ = 26000000U, /* mmc */
    FSDIF_CLK_SPEED_50_MHZ = 50000000U,
    FSDIF_CLK_SPEED_52_MHZ = 52000000U, /* mmc */
    FSDIF_CLK_SPEED_100_MHZ = 100000000U,
    FSDIF_CLK_SPEED_200_MHZ = 200000000U,
} FSdifClkSpeed;

/**************************** Type Definitions *******************************/
typedef struct _FSdif FSdif;
typedef struct _FSdifTiming FSdifTiming;

typedef void (*FSdifRelaxHandler)(void);
typedef void (*FSdifEvtHandler)(FSdif *const instance_p, void *args, u32 status, u32 dmac_status);

typedef struct
{
    u32 attribute; /* des0 */
#define FSDIF_IDMAC_DES0_DIC    BIT(1)/* 内部描述表不触发TI/RI中断 */
#define FSDIF_IDMAC_DES0_LD     BIT(2)/* 数据的最后一个描述符 */
#define FSDIF_IDMAC_DES0_FD     BIT(3)/* 数据的第一个描述符 */
#define FSDIF_IDMAC_DES0_CH     BIT(4)/* 链接下一个描述符地址 */
#define FSDIF_IDMAC_DES0_ER     BIT(5)/* 链表已经到达最后一个链表 */
#define FSDIF_IDMAC_DES0_CES    BIT(30)/* RINTSTS寄存器错误汇总 */
#define FSDIF_IDMAC_DES0_OWN    BIT(31)/* 描述符关联DMA，完成传输后该位置置0 */
    u32 non1; /* des1 --> unused */
    u32 len;  /* des2 buffer size*/
    u32 non2; /* des3 --> unused */
    u32 addr_lo; /* des4 Lower 32-bits of Buffer Address Pointer 1 --> buffer 1 */
    u32 addr_hi; /* des5 Upper 32-bits of Buffer Address Pointer 1 */
    /* Each descriptor can transfer up to 4KB of data in chained mode */
#define FSDIF_IDMAC_MAX_BUF_SIZE        0x1000U
    u32 desc_lo; /* des6 Lower 32-bits of Next Descriptor Address --> buffer 2 */
    u32 desc_hi; /* des7 Upper 32-bits of Next Descriptor Address */
} __attribute__((packed)) __attribute((aligned(4))) FSdifIDmaDesc;  /* SDIF DMA descriptr */

typedef struct
{
    volatile FSdifIDmaDesc *first_desc; /* virtual address of first descriptor */
    volatile uintptr first_desc_dma; /* physical address of first descriptor */
    u32 desc_num; /* num of descriptors in the list */
    u32 desc_trans_sz; /* num of bytes transfer by one descriptor */
} FSdifIDmaDescList; /* SDIF DMA descriptors list */

typedef struct
{
    /* buffer address shall aligned with transfer block size */
    void *buf; /* virtual address of buffer for memory access */
    uintptr buf_dma; /* physical address for DMA */
    u32 blksz; /* card block size */
    u32 blkcnt; /* num of block in trans */
    u32 datalen; /* bytes in trans */
} FSdifData; /* SDIF trans data */

typedef struct
{
    u32 cmdidx; /* command index */
#define FSDIF_SWITCH_VOLTAGE             11U
    u32 cmdarg; /* command argument */
    u32 response[4]; /* command response buffer */
    u32 flag; /* command flags */
#define FSDIF_CMD_FLAG_NEED_INIT         BIT(1) /* need initialization */
#define FSDIF_CMD_FLAG_EXP_RESP          BIT(2) /* need reply */
#define FSDIF_CMD_FLAG_EXP_LONG_RESP     BIT(3) /* need 136 bits long reply */
#define FSDIF_CMD_FLAG_NEED_RESP_CRC     BIT(4) /* need CRC */
#define FSDIF_CMD_FLAG_EXP_DATA          BIT(5) /* need trans data */
#define FSDIF_CMD_FLAG_WRITE_DATA        BIT(6) /* need trans data to write card */
#define FSDIF_CMD_FLAG_READ_DATA         BIT(7) /* need trans data to read card */
#define FSDIF_CMD_FLAG_NEED_AUTO_STOP    BIT(8) /* need auto stop after command */
#define FSDIF_CMD_FLAG_ADTC              BIT(9) /* need ADTC */
#define FSDIF_CMD_FLAG_SWITCH_VOLTAGE    BIT(10) /* need switch voltage */
#define FSDIF_CMD_FLAG_ABORT             BIT(11)
    FSdifData *data_p; /* SDIF trans data */
    volatile boolean success; /* TRUE: comand and data transfer success */
} FSdifCmdData; /* SDIF trans command and data */

typedef const FSdifTiming *(*FSdifGetTuning)(FSdifClkSpeed clock_freq, boolean non_removable);

typedef struct _FSdifTiming
{
    boolean   use_hold; /* 1: CMD[29] = 1, equal to add one sampling time delay */
    u32       clk_div;  /* for reg 0x8 */
    u32       clk_src;  /* for reg 0x108 */
    u32       shift;    /* for reg 0x110 */
    void (*pad_delay)(u32 id);      /* method to adjust pad delay */
} FSdifTiming; /* SDIF timing configuration */

typedef struct
{
    u32            instance_id; /* Device instance id */
    uintptr        base_addr;   /* Device base address */
    u32            irq_num;     /* Interrupt num */
    FSdifTransMode trans_mode;  /* Trans mode, PIO/DMA */
    boolean        non_removable; /* No removeable media, e.g eMMC */
    FSdifGetTuning get_tuning; /* Get time-tuning related parameters and method */
} FSdifConfig; /* SDIF intance configuration */

typedef struct _FSdif
{
    FSdifConfig         config;      /* Current active configs */
    u32                 is_ready;    /* Device is initialized and ready */
    FSdifIDmaDescList   desc_list;   /* DMA descriptor list, valid in DMA trans mode */
    FSdifEvtHandler     evt_handlers[FSDIF_NUM_OF_EVT]; /* call-backs for interrupt event */
    void                *evt_args[FSDIF_NUM_OF_EVT]; /* arguments for event call-backs */
    FSdifRelaxHandler   relax_handler;
    u32                 prev_cmd; /* record previous command code */
    FSdifCmdData        *cur_cmd;
    const FSdifTiming   *curr_timing;
} FSdif; /* SDIF intance */
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* Get the device instance default configure  */
const FSdifConfig *FSdifLookupConfig(u32 instance_id);

/* initialization SDIF controller instance */
FError FSdifCfgInitialize(FSdif *const instance_p, const FSdifConfig *cofig_p);

/* deinitialization SDIF controller instance */
void FSdifDeInitialize(FSdif *const instance_p);

/* Setup DMA descriptor for SDIF controller instance */
FError FSdifSetIDMAList(FSdif *const instance_p, volatile FSdifIDmaDesc *desc, uintptr desc_dma,  u32 desc_num);

/* Set the Card clock freqency */
FError FSdifSetClkFreq(FSdif *const instance_p, u32 input_clk_hz);

/* Start command and data transfer in DMA mode */
FError FSdifDMATransfer(FSdif *const instance_p, FSdifCmdData *const cmd_data_p);

/* Wait DMA transfer finished by poll */
FError FSdifPollWaitDMAEnd(FSdif *const instance_p, FSdifCmdData *const cmd_data_p);

/* Start command and data transfer in PIO mode */
FError FSdifPIOTransfer(FSdif *const instance_p, FSdifCmdData *const cmd_data_p);

/* Wait PIO transfer finished by poll */
FError FSdifPollWaitPIOEnd(FSdif *const instance_p, FSdifCmdData *const cmd_data_p);

/* Read PIO data, it works in IRQ mode */
FError FSdifPIOReadData(FSdif *const instance_p, FSdifData *data_p);

/* Get cmd response and received data after wait poll status or interrupt signal */
FError FSdifGetCmdResponse(FSdif *const instance_p, FSdifCmdData *const cmd_data_p);

/* Get SDIF controller interrupt mask */
u32 FSdifGetInterruptMask(FSdif *const instance_p, FSdifIntrType intr_type);

/* Enable/Disable SDIF controller interrupt */
void FSdifSetInterruptMask(FSdif *const instance_p, FSdifIntrType type, u32 set_mask, boolean enable);

/* Interrupt handler for SDIF instance */
void FSdifInterruptHandler(s32 vector, void *param);

/* Reset controller from error state */
FError FSdifRestart(FSdif *const instance_p);

/* Register event call-back function as handler for interrupt events */
void FSdifRegisterEvtHandler(FSdif *const instance_p, FSdifEvtType evt, FSdifEvtHandler handler, void *handler_arg);

/* Register sleep call-back function */
void FSdifRegisterRelaxHandler(FSdif *const instance_p, FSdifRelaxHandler relax_handler);

/* Dump all register value of SDIF instance */
void FSdifDumpRegister(uintptr base_addr);

/* Dump command and data info */
void FSdifDumpCmdInfo(FSdifCmdData *const cmd_data);

#ifdef __cplusplus
}
#endif


#endif
