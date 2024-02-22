/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#ifdef BSP_USING_TCA9539

#include "tca9539.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Define for TCA9539 */
#define BSP_TCA9539_I2C_BUS_NAME        "i2c1"
#define BSP_TCA9539_DEV_ADDR            (0x74U)

#define TCA9539_RST_PIN                 (32)    /* PB15 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  BSP TCA9539 write data.
 * @param  [in] bus:                    Pointer to the i2c bus device.
 * @param  [in] reg:                    Register to be written.
 * @param  [in] data:                   The pointer to the buffer contains the data to be written.
 * @param  [in] len:                    Buffer size in byte.
 * @retval rt_err_t:
 *           - RT_EOK
 *           - -RT_ERROR
 */
static rt_err_t BSP_TCA9539_I2C_Write(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data, rt_uint16_t len)
{
    struct rt_i2c_msg msgs;
    rt_uint8_t buf[6];

    buf[0] = reg;
    if (len > 0)
    {
        if (len < 6)
        {
            rt_memcpy(buf + 1, data, len);
        }
        else
        {
            return -RT_ERROR;
        }
    }
    msgs.addr   = BSP_TCA9539_DEV_ADDR;
    msgs.flags  = RT_I2C_WR;
    msgs.buf    = buf;
    msgs.len    = len + 1;
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

/**
 * @brief  BSP TCA9539 Read data.
 * @param  [in] bus:                    Pointer to the i2c bus device.
 * @param  [in] reg:                    Register to be read.
 * @param  [out] data:                  The pointer to the buffer contains the data to be read.
 * @param  [in] len:                    Buffer size in byte.
 * @retval rt_err_t:
 *           - RT_EOK
 *           - -RT_ERROR
 */
static rt_err_t BSP_TCA9539_I2C_Read(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data, rt_uint16_t len)
{
    struct rt_i2c_msg msgs;

    if (RT_EOK != BSP_TCA9539_I2C_Write(bus, reg, RT_NULL, 0))
    {
        return -RT_ERROR;
    }
    msgs.addr   = BSP_TCA9539_DEV_ADDR;
    msgs.flags  = RT_I2C_RD;
    msgs.buf    = data;
    msgs.len    = len;
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}


/**
 * @brief  Reset TCA9539.
 * @param  [in] None
 * @retval None
 */
static void TCA9539_Reset(void)
{
    rt_pin_mode(TCA9539_RST_PIN, PIN_MODE_OUTPUT);
    /* Reset the device */
    rt_pin_write(TCA9539_RST_PIN, PIN_LOW);
    rt_thread_mdelay(3U);
    rt_pin_write(TCA9539_RST_PIN, PIN_HIGH);
}

/**
 * @brief  Write TCA9539 pin output value.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg @ref TCA9539_Port_Definition
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref TCA9539_Pin_Definition
 * @param  [in] u8PinState              Pin state to be written.
 *         This parameter can be one of the following values:
 *           @arg @ref TCA9539_Pin_State_Definition
 * @retval rt_err_t:
 *           - RT_ERROR
 *           - RT_EOK
 */
rt_err_t TCA9539_WritePin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState)
{
    uint8_t u8TempData[2];

    u8TempData[0] = u8Port + TCA9539_REG_OUTPUT_PORT0;
    if (RT_EOK != BSP_TCA9539_I2C_Read(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }
    if (0U == u8PinState)
    {
        u8TempData[1] &= (uint8_t)(~u8Pin);
    }
    else
    {
        u8TempData[1] |= u8Pin;
    }
    if (RT_EOK != BSP_TCA9539_I2C_Write(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief  Read TCA9539 pin input value.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg @ref TCA9539_Port_Definition
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref TCA9539_Pin_Definition
 * @param  [in] u8PinState              Pin state to be written.
 *         This parameter can be one of the following values:
 *           @arg @ref TCA9539_Pin_State_Definition
 * @retval rt_err_t:
 *           - RT_ERROR
 *           - RT_EOK
 */
rt_err_t TCA9539_ReadPin(uint8_t u8Port, uint8_t u8Pin, uint8_t *pu8PinState)
{
    uint8_t u8TempData[2];

    u8TempData[0] = u8Port + TCA9539_REG_INPUT_PORT0;
    if (RT_EOK != BSP_TCA9539_I2C_Read(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }
    if (0U != (u8TempData[1] & u8Pin))
    {
        *pu8PinState = TCA9539_PIN_SET;
    }
    else
    {
        *pu8PinState = TCA9539_PIN_RESET;
    }

    return RT_EOK;
}

/**
 * @brief  Toggle TCA9539 pin output value.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg @ref TCA9539_Port_Definition
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref TCA9539_Pin_Definition
 * @retval rt_err_t:
 *           - -RT_ERROR
 *           - RT_EOK
 */
rt_err_t TCA9539_TogglePin(uint8_t u8Port, uint8_t u8Pin)
{
    uint8_t u8TempData[2];

    u8TempData[0] = u8Port + TCA9539_REG_OUTPUT_PORT0;
    if (RT_EOK != BSP_TCA9539_I2C_Read(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }
    u8TempData[1] ^= u8Pin;
    if (RT_EOK != BSP_TCA9539_I2C_Write(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief  Configuration TCA9539 pin.
 * @param  [in] u8Port                  Port number.
 *         This parameter can be one of the following values:
 *           @arg @ref TCA9539_Port_Definition
 * @param  [in] u8Pin                   Pin number.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref TCA9539_Pin_Definition
 * @param  [in] u8Dir                   Pin output direction.
 *         This parameter can be one of the following values:
 *           @arg @ref TCA9539_Direction_Definition
 * @retval rt_err_t:
 *           - -RT_ERROR
 *           - RT_EOK
 */
rt_err_t TCA9539_ConfigPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir)
{
    uint8_t u8TempData[2];

    u8TempData[0] = u8Port + TCA9539_REG_CONFIG_PORT0;
    if (RT_EOK != BSP_TCA9539_I2C_Read(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }
    if (TCA9539_DIR_OUT == u8Dir)
    {
        u8TempData[1] &= (uint8_t)(~u8Pin);
    }
    else
    {
        u8TempData[1] |= u8Pin;
    }
    if (RT_EOK != BSP_TCA9539_I2C_Write(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief  Initialize TCA9539.
 * @param  [in] None
 * @retval rt_err_t:
 *           - -RT_ERROR
 *           - RT_EOK
 */
int TCA9539_Init(void)
{
    char name[RT_NAME_MAX];
    uint8_t u8TempData[2];

    TCA9539_Reset();
    rt_strncpy(name, BSP_TCA9539_I2C_BUS_NAME, RT_NAME_MAX);
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);
    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", BSP_TCA9539_I2C_BUS_NAME);
        return -RT_ERROR;
    }
    /* All Pins are input as default */
    u8TempData[0] = TCA9539_REG_CONFIG_PORT0;
    u8TempData[1] = 0xFFU;
    if (RT_EOK != BSP_TCA9539_I2C_Write(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }
    u8TempData[0] = TCA9539_REG_CONFIG_PORT1;
    if (RT_EOK != BSP_TCA9539_I2C_Write(i2c_bus, u8TempData[0], &u8TempData[1], 1U))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_PREV_EXPORT(TCA9539_Init);

#endif /* BSP_USING_TCA9539 */
