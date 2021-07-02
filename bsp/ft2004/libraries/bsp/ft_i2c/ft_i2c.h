/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 13:32:20
 * @Description:  This files is for i2c user interface
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_BSP_I2C_H
#define FT_BSP_I2C_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_debug.h"
#include "ft_assert.h"
#include "ft_error_code.h"
#include "ft_i2c_hw.h"

    /* I2C Ctrl instance */
    typedef enum
    {
        I2C_CTRL_ID_0 = 0,
        I2C_CTRL_ID_1,
        I2C_CTRL_ID_2,
        I2C_CTRL_ID_3,

        MAX_I2C_CTRL_ID,
    } FI2C_Instance_t;

    static const u32 g_FI2cIrqNum[MAX_I2C_CTRL_ID] = {
        44, 45, 46, 47};

    static const u32 g_FI2cRegBaseAddr[MAX_I2C_CTRL_ID] = {
        I2C0_BASE_ADDRESS, I2C1_BASE_ADDRESS,
        I2C2_BASE_ADDRESS, I2C3_BASE_ADDRESS};

#define I2C_DEFAULT_IRQ_PRIORITY 0

    /* Type of I2C device */
    typedef enum
    {
        I2C_MASTER_DEV = 0,
        I2C_SLAVE_DEV,

        MAX_I2C_DEV
    } FI2C_DevType_t;

    /* I2C work mode type */
    typedef enum
    {
        I2C_POLLING_MODE = 0,
        I2C_IRQ_MODE,

        MAX_I2C_WORKMODE
    } FI2C_WorkMode_t;

    /* Type of I2C bus speed */
    typedef enum
    {
        I2C_STANDARD_SPEED = 0,
        I2C_FAST_SPEED,
        I2C_HIGH_SPEED,

        MAX_I2C_SPEED,
    } FI2C_SpeedType_t;

    /* I2C error code Submodule */
    typedef enum
    {
        I2C_ERR_MODE_DEF = 0,

        MAX_I2C_ERR_MODE,
    } FI2C_Submodule_t;

    /* I2C irq type */
    typedef enum
    {
        I2C_IRQ_TYPE_NONE = 0,
        I2C_IRQ_TYPE_TX_COMPLETE,
        I2C_IRQ_TYPE_RX_COMPLETE,

        MAX_I2C_IRQ_TYPE
    } FI2C_IrqType_t;

    /* I2C config info */
    typedef struct
    {
        FI2C_Instance_t InstanceId; /* Id of I2C ctrl instance */
        u32 BaseAddress;            /* base address of I2C register */
        FI2C_DevType_t WorkMode;    /* work as master or slave */
        FI2C_SpeedType_t BusSpeed;  /* bus speed setting */
        u32 SclLcnt;
        u32 SclHcnt;
        u32 RxThres;
        u32 TxThres;
        bool_t Is7BitAddr; /* TRUE: use 7 bit addr, FALSE: use 10 bit addr */
        bool_t IsPolling;  /* is polling */
        u32 IrqNum;        /* irq num of I2C in system */
        u32 IrqPriority;   /* irq priority */
        u32 BlockSize;     /* block size, for eeprom */
        bool_t WRByFifo;
    } FI2C_Config_t;

    /* I2C RX/TX buffer */
    typedef struct
    {
        u8 *BytePtr;
        u32 TotalBytes;
        u32 DataLength;
        u32 CurIndex;
    } FI2C_Buffer_t;

    typedef void (*FI2C_IrqCallBackHandler_t)(FT_IN u32 IrqType,
                                              FT_INOUT void *pDev,
                                              FT_INOUT void *pArg);
    typedef void (*FI2C_IrqWaitHandler_t)(FT_IN u32 IrqType,
                                          FT_INOUT void *pDev);
    typedef int32_t (*FI2C_DelayHandler_t)(FT_IN u32);

    /* I2C device info */
    typedef struct
    {
        FI2C_Config_t Config; /* Configuration data structure  */

        void *pRxEvent;
        void *pTxEvent;
        FI2C_IrqCallBackHandler_t pIrqCallBack;
        FI2C_IrqWaitHandler_t pWaitCallBack;
        u32 LastIrqErr;
        FI2C_Buffer_t RxBuf;
        FI2C_Buffer_t TxBuf;

        FI2C_DelayHandler_t DelayHandle;
        bool_t IsReady; /* Device is ininitialized and ready*/
        u16 SlaveAddr;  /* address of I2C slave device for master */
    } FI2C_t;

    void FI2C_initMaster(FT_IN FI2C_Instance_t id,
                         FT_IN FI2C_WorkMode_t mode,
                         FT_IN u32 SlaveAddr,
                         FT_IN bool_t UseWRFifo,
                         FT_IN u32 PageSize,
                         FT_INOUT FI2C_t *pDev);
    u32 FI2C_writeByByte(FT_IN u32 len, FT_IN u8 *pI2cBuf, FT_IN u8 PageAddr,
                         FT_INOUT FI2C_t *pDev);
    u32 FI2C_readByByte(FT_IN u32 len, FT_OUT u8 *pI2cBuf, FT_IN u8 PageAddr,
                        FT_INOUT FI2C_t *pDev);
    u32 FI2C_setIrqHandler(FT_IN FI2C_IrqType_t IrqType, FT_IN FI2C_DelayHandler_t pHandler, FT_IN void *pArgs,
                           FT_INOUT FI2C_t *pDev);
    void FI2C_irqHandler(void *pArgs);
    void FI2C_irqHandler4Fifo(void *pArgs);
    u32 FI2C_getIrqMask(FT_IN FI2C_t *pDev);
    void FI2C_setIrqMask(FT_IN FI2C_t *pDev, FT_IN u32 mask);
    void FI2C_setIrq(FT_IN FI2C_t *pDev, FT_IN u32 maskBit, FT_IN bool_t enable);
    bool_t FI2C_checkIfIntr(FT_IN FI2C_t *pDev);
    u32 FI2C_writeByFifo(FT_IN u8 PageAddr, FT_INOUT FI2C_t *pDev);
    u32 FI2C_readByFifo(FT_IN u8 PageAddr, FT_INOUT FI2C_t *pDev);
    void FI2C_deInitMaster(FT_INOUT FI2C_t *pDev);

#define FT_I2C_DEBUG_TAG "FT_I2C"
//#define FT_I2C_ENABLE_DEBUG
#define FT_I2C_ERROR(format, ...) FT_DEBUG_PRINT_E(FT_I2C_DEBUG_TAG, format, ##__VA_ARGS__)
#ifdef FT_I2C_ENABLE_DEBUG
#define FT_I2C_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_I2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_I2C_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_I2C_DEBUG_TAG, format, ##__VA_ARGS__)
#else
#define FT_I2C_DEBUG_I(format, ...)
#define FT_I2C_DEBUG_W(format, ...)
#endif

#define ERR_I2C_OK ERR_SUCCESS
#define ERR_I2C_NOT_READY FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 1)
#define ERR_I2C_WRITE_TIMEOUT FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 2)
#define ERR_I2C_READ_TIMEOUT FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 3)
#define ERR_I2C_SIZE_TOO_LARGE FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 4)
#define ERR_I2C_NOT_SUPPORT FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 5)
#define ERR_I2C_INVALID_PARAM FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 6)
#define ERR_I2C_INVALID_HANDLER FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 7)
#define ERR_I2C_INVALID_NO_MEM FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 8)
#define ERR_I2C_BUS_NOT_ENABLED FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 9)
#define ERR_I2C_EVT_TIMEOUT FT_CODE_ERR(errModeI2c, I2C_ERR_MODE_DEF, 0xA)

#ifdef __cplusplus
}
#endif

#endif
