/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-21 09:29:48
 * @LastEditTime: 2021-04-23 09:24:59
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_FREERTOS_I2C_H
#define FT_FREERTOS_I2C_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_i2c.h"

/* RX event */
#define FOS_I2C_RX_OVER_EVT       (0x01 << 0)

/* TX event */
#define FOS_I2C_TX_OVER_EVT       (0x01 << 0)

typedef struct 
{
    FI2C_Instance_t Id;
    FI2C_DevType_t DevType;
    FI2C_WorkMode_t WorkMode;
    u32 SlaveAddr;
    u32 PageAddr;
    u32 PageSize;
    u8 *pTxBuf;
    u32 TxBufSize;
    u8 *pRxBuf;
    u32 RxBufSize;
    bool_t UseWRFIFO;
}FOS_I2cConfig_t;

u32 FOS_initI2cCtrl(FOS_I2cConfig_t *config);
void FOS_deInitI2cCtrl(FI2C_Instance_t Id);
u32 FOS_i2cRead(FOS_I2cConfig_t *config);
u32 FOS_i2cWrite(FOS_I2cConfig_t *config);

#ifdef __cplusplus
}
#endif

#endif