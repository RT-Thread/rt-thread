/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-04-19 17:04:44
 * @Description:  This files is for implementation of sd ctrl
 *
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FTSDCTRL_H
#define FTSDCTRL_H
#include "ft_types.h"
#include "ft_error_code.h"

/* sd ctrl module debug tag */
#define FT_SD_CTRL_DEBUG_TAG "FT_SD_CTRL"

/* definition of errcode for sd module */
#define FTSDC_SUCCESS FST_SUCCESS                                                            /* 成功 */
#define FTSDC_FAILURE FT_MAKE_ERRCODE(errModeSdCtrl, errBspGeneral, FST_FAILURE)             /* Normal */
#define FTSDC_TIMEOUT FT_MAKE_ERRCODE(errModeSdCtrl, errBspGeneral, FST_TIMEOUT)             /* Timeout */
#define FTSDC_EILSEQ FT_MAKE_ERRCODE(errModeSdCtrl, errBspGeneral, FST_EILSEQ)               /* Illegal byte sequence. */
#define FTSDC_INVALID_PARAM FT_MAKE_ERRCODE(errModeSdCtrl, errBspGeneral, FST_INVALID_PARAM) /* Illegal byte sequence. */

/* type of response to sd cmds */
#define FTSDCTRL_CMD_RES_NONE 0  /* No response */
#define FTSDCTRL_CMD_RES_LONG 1  /* The response length is long, code length is 128 */
#define FTSDCTRL_CMD_RES_SHORT 2 /* The response length is short, code length is 32 */

/* irq enable bits */
#define FTSDCTRL_DATA_WRITE_IRQ_MASK 0x1
#define FTSDCTRL_DATA_READ_IRQ_MASK 0x2
#define FTSDCTRL_CMD_IRQ_MASK 0x4

/* type of irq callback */
typedef enum
{
    FTSDCTRL_DMADATAIRQID = 0x1U, /* Select dma interrupt */
    FTSDCTRL_CMDIRQID = 0x2U,     /* Select cmd interrupt */
    FTSDCTRL_ERRORIRQID = 0x3U,   /* Select error interrupt */
} FSdCtrl_IrqCallbackSelect_t;

/* normal irq enable bits for NORMAL_INT_EN_REG_OFFSET */
typedef enum
{
    NORMAL_IRQ_CC = 1, /*  Command completion interrupt */
    NORMAL_IRQ_CR = 2, /*  Card removal interrupt  */
    NORMAL_IRQ_EI = 4  /* Command error interrupt */
} FSdCtrl_NormalIrqSelect_t;

/* error irq enable bits for ERROR_INT_EN_REG_OFFSET */
typedef enum
{
    ERROR_IRQ_CTE = 1,   /* Command timeout error interrupted */
    ERROR_IRQ_CCRCE = 2, /*  Command CRC error interrupt  */
    ERROR_IRQ_CIR = 4,   /* Command index error interrupt */
    ERROR_IRQ_CNR = 8    /* Command response error interrupted */
} FSdCtrl_ErrorIrqSelect_t;

/* data trans irq bits for BD_ISR_EN_REG_OFFSET */
typedef enum
{
    BD_IRQ_TRS = 1,        /* DMA transmission has been interrupted */
    BD_IRQ_DTE = 2,        /*  Timeout interrupt  */
    BD_IRQ_CMDE = 4,       /* Command response error interrupted */
    BD_IRQ_TRE = 8,        /* Command response error interrupt CRC response error interrupt */
    BD_IRQ_NRCRC = 0x10,   /* No CRC response interruption */
    BD_IRQ_DATFRAX = 0x20, /*  AXI bus forces to release interrupts  */
    BD_IRQ_RESPE = 0x40,   /* Read SD card operation, AXI BR channel complete interrupt */
    BD_IRQ_DAIS = 0x80,    /* DMA error interrupt */
} FSdCtrl_BdIrqSelect;

/* types of irq */
typedef enum
{
    FTSDC_NORMAL_ISR = 0U,
    FTSDC_BD_ISR,
    FTSDC_ERROR_ISR
} FSdCtrl_IsrCallbackSelect_t;

/* voltage supply range type of SD Card follow POWER_CONTROLL_REG
*/
typedef enum
{
    FSDC_HIGH_V = 0, /* SD card operate within the voltage range of 2.7-3.6 V */
    FSDC_DUAL_V,     /* SD card operate within the Low Voltage Range (T.B.D) and 2.7-3.6 V */

    MAX_FSDC_VOLTAGE_TYPE
} FSdCtrl_VRangeType_t;

/* read-write property of SD Card */
typedef enum
{
    FSDC_RW_CARD = 0,
    FSDC_RO_CARD,

    MAX_FSDC_WR_CARD_TYPE
} FSdCtrl_WRType_t;

/* capacity type of SD Card */
typedef enum
{
    FSDC_SD_CARD = 0,
    FSDC_SDHC_CARD,
    FSDC_SDXC_CARD,

    MAX_FSDC_CARD_CAPACITY_TYPE
} FSdCtrl_CapacityType_t;

/* speed class of SD Card */
typedef enum
{
    FSDC_CLASS0 = 0,
    FSDC_CLASS2,
    FSDC_CLASS4,
    FSDC_CLASS6,

    MAX_FSDC_CLASS_TYPE
} FSdCtrl_ClassType_t;

/**
 * This typedef contains configuration information for the sd device.
 */
typedef struct
{
    u32 instanceId;   /* Unique ID  of device */
    u32 baseAddress;  /* Base address of the device */
    u32 inputClockHz; /* Input clock frequency */
    u32 cardDetect;   /* Card Detect */
    u32 writeProtect; /* Write Protect */
    u32 busWidth;     /* Bus Width */
    u32 dmaIrqNum;    /* dma irq number */
    u32 normalIrqNum; /* normal irq number */
    u32 errIrqNum;    /* error irq number  */
    u8 workMode;      /* Work mode for data transfers ,
                        If the mask bit is 0, polling is used ,
                        follow irq enable bits*/
} FSdCtrl_Config_t;

typedef void (*FtsdCtrl_irqCallback_t)(void *args);

/* irq callback and iput args */
typedef struct
{
    FtsdCtrl_irqCallback_t pDmaDataCallback; /* DMA data interrupt function pointer */
    void *pDmaDataArgs;

    FtsdCtrl_irqCallback_t pCmdCallback; /* Commond interrupt function pointer */
    void *pCmdArgs;

    FtsdCtrl_irqCallback_t pErrorCallback; /* Error interrupt function pointer */
    void *pErrorArgs;
} FSdCtrl_IrqConfig_t;

typedef struct FtsdCtrl FtsdCtrl_t;
typedef void (*pFtsdCtrl_delayTimer_t)(ft_base_t delayUs);
typedef ft_error_t (*pFtsdCtrl_irqWaitCallback_t)(FtsdCtrl_t *FtsdCtrl);

/* ctrl instance of sd */
struct FtsdCtrl
{
    FSdCtrl_Config_t config;
    u32 isReady; /* Device is initialized and ready */
    /*************reserved**************/
    FSdCtrl_VRangeType_t voltageType;
    FSdCtrl_WRType_t writeReadType;
    FSdCtrl_CapacityType_t capacityType;
    FSdCtrl_ClassType_t speedClassType;
    /*************reserved**************/
    FSdCtrl_IrqConfig_t irqConfig;
    pFtsdCtrl_irqWaitCallback_t writeWaitCallback; /* function pointer .Used to determine whether the data transmission is complete*/
    pFtsdCtrl_irqWaitCallback_t readWaitCallback;  /* function pointer .Used to determine whether the data received is complete*/
    pFtsdCtrl_irqWaitCallback_t cmdWaitCallback;   /* function pointer . Used to determine whether the command is complete */
};

u32 FSdCtrl_PrepareCmdRaw(FT_IN u32 cmdIndex, FT_IN u32 rspType);
void FSdCtrl_WriteData(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN UINTPTR dataAddr, FT_IN UINTPTR cmdArg, FT_IN u32 blkNum);
void FSdCtrl_ReadData(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                      FT_IN UINTPTR dataAddr,
                      FT_IN UINTPTR cardAddr,
                      FT_IN u32 blkNum);
ft_error_t FSdCtrl_WaitCmdEnd(FT_OUT FtsdCtrl_t *pFtsdCtrl,
                              FT_IN pFtsdCtrl_delayTimer_t pDelayTimer_fun,
                              FT_IN u32 rspType,
                              FT_OUT u32 *cmdRsp);
ft_error_t FSdCtrl_WaitReadDataEnd(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                                   FT_IN pFtsdCtrl_delayTimer_t pDelayTimer_fun,
                                   FT_IN u32 blkNum);
ft_error_t FSdCtrl_WaitWriteDataEnd(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                                    FT_IN pFtsdCtrl_delayTimer_t pDelayTimer_fun,
                                    FT_IN u32 blkNum);

void FSdCtrl_DoCmd(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN u32 cmdIndex, FT_IN u32 rspType, u32 arg);
void FSdCtrl_DoACmd(FT_INOUT FtsdCtrl_t *pFtsdCtrl,
                    FT_IN u32 cmdIndex,
                    FT_IN u32 rspType,
                    u32 arg);
void FSdCtrl_NormalIrq(FT_INOUT FtsdCtrl_t *pFtsdCtrl);
void FSdCtrl_DmaIrq(FT_INOUT FtsdCtrl_t *pFtsdCtrl);
void FSdCtrl_ErrIrq(FT_INOUT FtsdCtrl_t *pFtsdCtrl);
bool_t FSdCtrl_CardDetect(FT_INOUT FtsdCtrl_t *pFtsdCtrl);

FSdCtrl_Config_t *FSdCtrl_LookupConfig(u32 instanceId);
/* This routine performs per device specific initialization of Phytium SDHC.*/
ft_error_t FsdCtrl_Init(FT_INOUT FtsdCtrl_t *pFtsdCtrl);
void FSdCtrl_ClkFreqSetup(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN u32 sdClk);
void FSdCtrl_ResetDma(FT_INOUT FtsdCtrl_t *pFtsdCtrl);
/* reset sd ctrl during init */
void FSdCtrl_Reset(FT_INOUT FtsdCtrl_t *pFtsdCtrl, pFtsdCtrl_delayTimer_t fDelayTimer);

/* set irq call backs */
ft_error_t FSdCtrl_SetHandler(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN FSdCtrl_IrqCallbackSelect_t selectIndex,
                              void *FuncPtr,
                              void *Args);

/* register call-backs to determinate wheather write、read and cmd is complete */
void FSdCtrl_WriteWaitRegister(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_irqWaitCallback_t callBack);
void FSdCtrl_ReadWaitRegister(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_irqWaitCallback_t callBack);
void FSdCtrl_CmdWaitRegister(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_irqWaitCallback_t callBack);
void FSdCtrl_ErrWaitRegister(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN pFtsdCtrl_irqWaitCallback_t callBack);

/* get irq status */
u32 FSdCtrl_GetNormalIrqStatus(FT_INOUT FtsdCtrl_t *pFtsdCtrl);
u32 FSdCtrl_GetDataIrqStatus(FT_INOUT FtsdCtrl_t *pFtsdCtrl);
u32 FSdCtrl_GetErrorIrqStatus(FT_INOUT FtsdCtrl_t *pFtsdCtrl);

/* enable selected normal irq */
void FSdCtrl_NormalIrqSet(FtsdCtrl_t *pFtsdCtrl, FT_IN FSdCtrl_NormalIrqSelect_t flgs);
void FSdCtrl_BdIrqSet(FtsdCtrl_t *pFtsdCtrl, FT_IN FSdCtrl_BdIrqSelect flgs);

#endif //
