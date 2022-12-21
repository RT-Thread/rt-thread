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

#include <rtdevice.h>

#include "ccap_sensor.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "ccap.sensor"
#define DBG_COLOR
#include <rtdbg.h>

rt_err_t ccap_sensor_i2c_write(struct rt_i2c_bus_device *i2cdev, rt_uint16_t addr, rt_uint8_t *puBuf, int i32BufLen)
{
    struct rt_i2c_msg msg;

    msg.addr  = addr;       /* Slave address */
    msg.flags = RT_I2C_WR;  /* Write flag */
    msg.buf   = puBuf;      /* Slave register address */
    msg.len   = i32BufLen;  /* Number of bytes sent */

    if (i2cdev && rt_i2c_transfer(i2cdev, &msg, 1) != 1)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

rt_err_t ccap_sensor_i2c_read(struct rt_i2c_bus_device *i2cdev, rt_uint16_t addr, rt_uint8_t *puWBuf, int i32WBufLen, rt_uint8_t *puRBuf, int i32RBufLen)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = addr;                  /* Slave address */
    msgs[0].flags = RT_I2C_WR;             /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)puWBuf;  /* Slave register address */
    msgs[0].len   = i32WBufLen;            /* Number of bytes sent */

    msgs[1].addr  = addr;                  /* Slave address */
    msgs[1].flags = RT_I2C_RD;             /* Read flag without READ_ACK */
    msgs[1].buf   = (rt_uint8_t *)puRBuf;  /* Read data pointer */
    msgs[1].len   = i32RBufLen;            /* Number of bytes read */

    if (rt_i2c_transfer(i2cdev, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t ccap_sensor_set_mode_general(struct rt_i2c_bus_device *i2cdev, sensor_priv *pdev, sensor_mode_info *psInfo)
{
    uint8_t au8TxData[4];
    int i;

    RT_ASSERT(i2cdev);
    RT_ASSERT(pdev);
    RT_ASSERT(psInfo);

    LOG_I("Selected Sensor ID:%d, Width:%d, Height:%d, FMT:%08x",
          pdev->eId,
          psInfo->sViewInfo.u32Width,
          psInfo->sViewInfo.u32Height,
          psInfo->sViewInfo.u32PixFmt);

    for (i = 0; i < psInfo->u32RegArrSize; i++)
    {
        const sensor_reg_val *psRegVal = &psInfo->psRegArr[i];

        switch (pdev->u16AddrBL)
        {
        case 2:
            au8TxData[0] = (uint8_t)((psRegVal->u16Addr >> 8) & 0x00FF); //addr [15:8]
            au8TxData[1] = (uint8_t)((psRegVal->u16Addr) & 0x00FF); //addr [ 7:0]
            break;

        case 1:
            au8TxData[0] = (uint8_t)((psRegVal->u16Addr) & 0x00FF); //addr [ 7:0]
            break;

        default:
            return -RT_ERROR;
        }

        switch (pdev->u16ValBL)
        {
        case 2:
            au8TxData[pdev->u16AddrBL] = (uint8_t)((psRegVal->u16Val >> 8) & 0x00FF); //data [15:8]
            au8TxData[pdev->u16AddrBL + 1] = (uint8_t)((psRegVal->u16Val) & 0x00FF); //data [ 7:0]
            break;

        case 1:
            au8TxData[pdev->u16AddrBL] = (uint8_t)((psRegVal->u16Val) & 0x00FF);  //data [ 7:0]
            break;

        default:
            return -RT_ERROR;
        }

        //LOG_I("SlaveID=0x%02x, Addr: [0x%02X,0x%02X], Value: [0x%02X,0x%02X], Length: %d", msg.addr, au8TxData[0], au8TxData[1], au8TxData[2], au8TxData[3], msg.len  );
        if (ccap_sensor_i2c_write(i2cdev, pdev->u16DevAddr, (rt_uint8_t *)&au8TxData[0], pdev->u16AddrBL + pdev->u16ValBL) != RT_EOK)
        {
            LOG_E("[Failed] addr=%x, data=%d\n", psRegVal->u16Addr, psRegVal->u16Val);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static rt_err_t ccap_sensor_setpower(ccap_sensor_dev *pdev, rt_bool_t bOn)
{
    ccap_sensor_io_t psIo;
    sensor_priv_t    psSensorPriv;

    if (pdev == RT_NULL)
        return -RT_ERROR;

    psIo = pdev->psIo;
    psSensorPriv = (sensor_priv_t)((rt_device_t)pdev)->user_data;

    LOG_I("sensor power pin: %d, Active low: %s", psIo->PwrDwnPin, bOn ? "TRUE" : "FALSE");

    rt_pin_mode(psIo->PwrDwnPin, PIN_MODE_OUTPUT);

    if (bOn == RT_TRUE)
    {
        (psSensorPriv->PwrDwnActLow == RT_TRUE) ? rt_pin_write(psIo->PwrDwnPin, PIN_HIGH) : rt_pin_write(psIo->PwrDwnPin, PIN_LOW);
    }
    else
    {
        (psSensorPriv->PwrDwnActLow == RT_TRUE) ? rt_pin_write(psIo->PwrDwnPin, PIN_LOW) : rt_pin_write(psIo->PwrDwnPin, PIN_HIGH);
    }

    return RT_EOK;
}

static rt_err_t ccap_sensor_reset(ccap_sensor_dev *pdev)
{
    ccap_sensor_io_t psIo;
    sensor_priv_t    psSensorPriv;

    if (pdev == RT_NULL)
        return -RT_ERROR;

    psIo = pdev->psIo;
    psSensorPriv = (sensor_priv_t)((rt_device_t)pdev)->user_data;

    LOG_I("sensor reset pin: %d, Active low: %s", psIo->RstPin, psSensorPriv->RstActLow ? "TRUE" : "FALSE");

    rt_pin_mode(psIo->RstPin, PIN_MODE_OUTPUT);

    (psSensorPriv->RstActLow == RT_TRUE) ?
    rt_pin_write(psIo->RstPin, PIN_LOW) :
    rt_pin_write(psIo->RstPin, PIN_HIGH);

    rt_thread_mdelay(psSensorPriv->RstHoldTimeInMs);

    (psSensorPriv->RstActLow == RT_TRUE) ?
    rt_pin_write(psIo->RstPin, PIN_HIGH) :
    rt_pin_write(psIo->RstPin, PIN_LOW);

    return RT_EOK;
}

/* common device interface */
static rt_err_t ccap_sensor_open(rt_device_t dev, rt_uint16_t oflag)
{
    ccap_sensor_dev *pdev = (ccap_sensor_dev *)dev;
    rt_err_t ret = -RT_ERROR;

    if (pdev == RT_NULL)
        goto fail_ccap_sensor_open;

    /* Power-on */
    ret = ccap_sensor_setpower(pdev, RT_TRUE);
    if (ret != RT_EOK)
        goto fail_ccap_sensor_open;

    /* Reset */
    ret = ccap_sensor_reset(pdev);

fail_ccap_sensor_open:

    return ret;
}

static rt_err_t ccap_sensor_close(rt_device_t dev)
{
    ccap_sensor_dev *pdev = (ccap_sensor_dev *)dev;

    if (pdev == RT_NULL)
        return -RT_ERROR;

    /* Power-off */
    return ccap_sensor_setpower(pdev, RT_FALSE);
}

static ccap_view_info_t ccap_find_suit_mode(ccap_view_info_t psViewInfo, const sensor_priv_t psSensorPriv)
{
    int i = 0;
    sensor_mode_info_t psSensorModeInfo = RT_NULL;

    for (i = 0; i < psSensorPriv->ModeInfoSize; i++)
    {
        if ((psViewInfo->u32Width <= psSensorPriv->psModeInfo[i].sViewInfo.u32Width) &&
                (psViewInfo->u32Height <= psSensorPriv->psModeInfo[i].sViewInfo.u32Height))
            break;
    }

    if (i != psSensorPriv->ModeInfoSize)
        psSensorModeInfo = &psSensorPriv->psModeInfo[i];
    else
    {
        /* Failed to get suit mode. Here, we gave latest Sensor mode to user. */
        psSensorModeInfo = &psSensorPriv->psModeInfo[i - 1];
    }

    return (ccap_view_info_t)psSensorModeInfo;
}

static rt_err_t ccap_sensor_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    ccap_sensor_dev *pdev = (ccap_sensor_dev *)dev;

    RT_ASSERT(dev);

    switch (cmd)
    {
    case CCAP_SENSOR_CMD_RESET:
        result = ccap_sensor_reset(pdev);
        break;

    case CCAP_SENSOR_CMD_SET_POWER:
    {
        rt_bool_t bOn = (rt_bool_t)args;
        result = ccap_sensor_setpower(pdev, bOn);
    }
    break;

    case CCAP_SENSOR_CMD_SET_MODE:
    {
        ccap_sensor_io *psIo = pdev->psIo;
        struct rt_i2c_bus_device *i2cbus;
        sensor_mode_info *psInfo;
        sensor_priv *psSensorPriv = (sensor_priv *)dev->user_data;

        RT_ASSERT(args);
        RT_ASSERT(psIo);
        RT_ASSERT(psIo->I2cName);

        i2cbus = (struct rt_i2c_bus_device *)rt_device_find(psIo->I2cName);
        RT_ASSERT(i2cbus);

        psInfo = (sensor_mode_info *) args;

        if (psSensorPriv->pfnSetMode != RT_NULL)
            result = psSensorPriv->pfnSetMode(i2cbus, psSensorPriv, psInfo);
        else
            result = ccap_sensor_set_mode_general(i2cbus, psSensorPriv, psInfo);
    }
    break;

    case CCAP_SENSOR_CMD_GET_SUIT_MODE:
    {
        /* Get private data of sensor */
        sensor_priv_t psSensorPriv = (sensor_priv_t)dev->user_data;
        ccap_view_info_t psViewInfo;

        RT_ASSERT(args);
        RT_ASSERT(psSensorPriv);

        psViewInfo = *((ccap_view_info_t *)args);
        RT_ASSERT(psViewInfo);

        psViewInfo = ccap_find_suit_mode(psViewInfo, (sensor_priv_t)psSensorPriv);

        *((ccap_view_info_t *)args) = psViewInfo;
    }
    break;

    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
static struct rt_device_ops ccap_ops =
{
    .init = RT_NULL,
    .open = ccap_sensor_open,
    .close = ccap_sensor_close,
    .read = RT_NULL,
    .write = RT_NULL,
    .control = ccap_sensor_control,
}
#endif

rt_err_t ccap_sensor_register(struct rt_device *device, const char *name, void *user_data)
{
    RT_ASSERT(device);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &ccap_ops;
#else
    device->init        = RT_NULL;
    device->open        = ccap_sensor_open;
    device->close       = ccap_sensor_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = ccap_sensor_control;
#endif
    device->user_data   = user_data;

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_STANDALONE);
}

rt_err_t nu_ccap_sensor_create(ccap_sensor_io *psIo, ccap_sensor_id evSensorId, const char *szName)
{
    static int i32AllocatedSensorId = 0;
    rt_err_t ret = -RT_ERROR;
    ccap_sensor_dev_t pdev = RT_NULL;

    RT_ASSERT(psIo);
    RT_ASSERT((evSensorId >= 0) && (evSensorId < evCCAPSNR_CNT));

    switch (evSensorId)
    {
    case evCCAPSNR_HM1055:
        pdev = nu_create_hm1055(psIo, szName);
        break;

    case evCCAPSNR_ADV728X:
        pdev = nu_create_adv728x(psIo, szName);
        break;

    default:
        break;
    }

    if (pdev != RT_NULL)
    {
        ccap_sensor_setpower(pdev, RT_FALSE);
        i32AllocatedSensorId++;
        ret = RT_EOK;
    }

    return ret;
}
