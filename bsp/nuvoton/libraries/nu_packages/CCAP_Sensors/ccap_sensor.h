/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-8-16       Wayne        First version
*
******************************************************************************/

#ifndef __CCAP_SENSOR_H__
#define __CCAP_SENSOR_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>
#include "NuMicro.h"

typedef enum
{
    evCCAPSNR_HM1055,
    evCCAPSNR_ADV728X,
    evCCAPSNR_CNT
} ccap_sensor_id;

typedef enum
{
    CCAP_SENSOR_CMD_RESET,
    CCAP_SENSOR_CMD_SET_POWER,
    CCAP_SENSOR_CMD_SET_MODE,
    CCAP_SENSOR_CMD_GET_SUIT_MODE,
} ccap_sensor_cmd;

typedef struct
{
    uint32_t u32Width;     // Horizontal total pixel
    uint32_t u32Height;    // Vertical total pixel
    uint8_t *pu8FarmAddr;
    uint32_t u32PixFmt;
} ccap_view_info;
typedef ccap_view_info *ccap_view_info_t;

typedef struct
{
    rt_uint16_t  u16Addr;
    rt_uint16_t  u16Val;
} sensor_reg_val;
typedef sensor_reg_val *sensor_reg_val_t;

typedef struct
{
    ccap_view_info        sViewInfo;
    const sensor_reg_val *psRegArr;
    rt_uint32_t           u32RegArrSize;
    rt_uint32_t           u32SenClk;
    rt_uint32_t           u32Polarity;
} sensor_mode_info;
typedef sensor_mode_info *sensor_mode_info_t;

typedef rt_err_t (*ccap_sensor_set_mode)(struct rt_i2c_bus_device *i2cdev, void *pvPriv, sensor_mode_info *psInfo);
typedef struct
{
    ccap_sensor_id     eId;
    sensor_mode_info_t psModeInfo;
    uint32_t           ModeInfoSize;
    rt_uint16_t        u16AddrBL;  // Address byte length
    rt_uint16_t        u16ValBL;   // Address byte length
    rt_uint16_t        u16DevAddr;

    rt_bool_t          RstActLow;
    rt_uint32_t        RstHoldTimeInMs;
    rt_bool_t          PwrDwnActLow;

    ccap_sensor_set_mode pfnSetMode;
} sensor_priv;
typedef sensor_priv *sensor_priv_t;

typedef struct
{
    rt_base_t     RstPin;
    rt_base_t     PwrDwnPin;
    const char   *I2cName;
} ccap_sensor_io;
typedef ccap_sensor_io *ccap_sensor_io_t;

typedef struct
{
    struct rt_device  device;
    ccap_sensor_io   *psIo;
} ccap_sensor_dev;
typedef ccap_sensor_dev *ccap_sensor_dev_t;

rt_err_t ccap_sensor_i2c_write(struct rt_i2c_bus_device *i2cdev, rt_uint16_t addr, rt_uint8_t *puBuf, int i32BufLen);
rt_err_t ccap_sensor_i2c_read(struct rt_i2c_bus_device *i2cdev, rt_uint16_t addr, rt_uint8_t *puWBuf, int i32WBufLen, rt_uint8_t *puRBuf, int i32RBufLen);
rt_err_t ccap_sensor_register(struct rt_device *device, const char *name, void *user_data);
rt_err_t nu_ccap_sensor_create(ccap_sensor_io *psIo, ccap_sensor_id evSensorId, const char *szName);
ccap_sensor_dev_t nu_create_hm1055(ccap_sensor_io *psIo, const char *szName);
ccap_sensor_dev_t nu_create_adv728x(ccap_sensor_io *psIo, const char *szName);

#endif /* __CCAP_SENSOR_H__ */
