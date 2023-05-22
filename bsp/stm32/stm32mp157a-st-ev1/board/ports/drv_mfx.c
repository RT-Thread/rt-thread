/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-08     thread-liu   first version
 */

#include "board.h"

#include "mfxstm32l152.h"
#define DRV_DEBUG
#define LOG_TAG             "drv.mfx"
#include <drv_log.h>

#define CHIP_ADDRESS    0x42     /* mfx address */
#define I2C_NAME       "i2c2"

struct st_mfx
{
    struct rt_device dev;
    struct rt_i2c_bus_device *i2c_bus;
    rt_uint8_t id;
    rt_uint16_t type;
};
static struct st_mfx rt_mfx = {0};
static IO_DrvTypeDef *IoDrv = NULL;

static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint16_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msg[2] = {0, 0};

    RT_ASSERT(bus != RT_NULL);

    msg[0].addr  = CHIP_ADDRESS;
    msg[0].flags = RT_I2C_WR;
    msg[0].buf   = &reg;
    msg[0].len   = 1;

    msg[1].addr  = CHIP_ADDRESS;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = len;
    msg[1].buf   = buf;

    if (rt_i2c_transfer(bus, msg, 2) == 2)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

/* i2c write reg */
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2];
    struct rt_i2c_msg msgs;

    RT_ASSERT(bus != RT_NULL);
    buf[0] = reg;
    buf[1] = data;

    msgs.addr  = CHIP_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = buf;
    msgs.len   = sizeof(buf);

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

void MFX_IO_Init(void)
{
    rt_mfx.i2c_bus = rt_i2c_bus_device_find(I2C_NAME);
    if (rt_mfx.i2c_bus == RT_NULL)
    {
        LOG_E("can't find %c deivce", I2C_NAME);
    }
}

void MFX_IO_DeInit(void)
{
}

void MFX_IO_ITConfig(void)
{
    static rt_uint8_t mfx_io_it_enabled = 0;
    GPIO_InitTypeDef  gpio_init_structure;

    if(mfx_io_it_enabled == 0)
    {
        mfx_io_it_enabled = 1;
        /* Enable the GPIO EXTI clock */
        __HAL_RCC_GPIOI_CLK_ENABLE();

        gpio_init_structure.Pin   = GPIO_PIN_8;
        gpio_init_structure.Pull  = GPIO_NOPULL;
        gpio_init_structure.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_init_structure.Mode  = GPIO_MODE_IT_RISING;
        HAL_GPIO_Init(GPIOI, &gpio_init_structure);

        /* Enable and set GPIO EXTI Interrupt to the lowest priority */
        HAL_NVIC_SetPriority((IRQn_Type)(EXTI8_IRQn), 0x04, 0x00);
        HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI8_IRQn));
    }
}

void MFX_IO_Write(rt_uint16_t Addr, rt_uint8_t Reg, rt_uint8_t Value)
{
    write_reg(rt_mfx.i2c_bus, Reg, Value);
}

rt_uint8_t MFX_IO_Read(rt_uint16_t Addr, rt_uint8_t Reg)
{
    rt_uint8_t value = 0;
    read_reg(rt_mfx.i2c_bus, Reg, 1, &value);

    return value;
}

rt_uint16_t MFX_IO_ReadMultiple(rt_uint16_t Addr, rt_uint8_t Reg, rt_uint8_t *Buffer, rt_uint16_t Length)
{
    return read_reg(rt_mfx.i2c_bus, Reg, Length, Buffer);
}

rt_weak void MFX_IO_Delay(rt_uint32_t Delay)
{
    rt_thread_delay(Delay);
}

rt_weak void MFX_IO_Wakeup(void)
{
}

rt_weak void MFX_IO_EnableWakeupPin(void)
{
}

rt_uint8_t BSP_IO_DeInit(void)
{
    IoDrv = NULL;
    return RT_EOK;
}

rt_uint32_t BSP_IO_ITGetStatus(rt_uint32_t IoPin)
{
    /* Return the IO Pin IT status */
    return (IoDrv->ITStatus(0, IoPin));
}

/**
  * @brief  Clears all the IO IT pending bits.
  * @retval None
  */
void BSP_IO_ITClear(void)
{
    /* Clear all IO IT pending bits */
    IoDrv->ClearIT(0, MFXSTM32L152_GPIO_PINS_ALL);
}

void BSP_IO_ITClearPin(rt_uint32_t IO_Pins_To_Clear)
{
    /* Clear only the selected list of IO IT pending bits */
    IoDrv->ClearIT(0, IO_Pins_To_Clear);
}

/**
  * @brief  Configures the IO pin(s) according to IO mode structure value.
  * @param  IoPin: IO pin(s) to be configured.
  *          This parameter can be one of the following values:
  *            @arg  MFXSTM32L152_GPIO_PIN_x: where x can be from 0 to 23.
  * @param  IoMode: IO pin mode to configure
  *          This parameter can be one of the following values:
  *            @arg  IO_MODE_INPUT
  *            @arg  IO_MODE_OUTPUT
  *            @arg  IO_MODE_IT_RISING_EDGE
  *            @arg  IO_MODE_IT_FALLING_EDGE
  *            @arg  IO_MODE_IT_LOW_LEVEL
  *            @arg  IO_MODE_IT_HIGH_LEVEL
  *            @arg  IO_MODE_ANALOG
  *            @arg  IO_MODE_OFF
  *            @arg  IO_MODE_INPUT_PU,
  *            @arg  IO_MODE_INPUT_PD,
  *            @arg  IO_MODE_OUTPUT_OD,
  *            @arg  IO_MODE_OUTPUT_OD_PU,
  *            @arg  IO_MODE_OUTPUT_OD_PD,
  *            @arg  IO_MODE_OUTPUT_PP,
  *            @arg  IO_MODE_OUTPUT_PP_PU,
  *            @arg  IO_MODE_OUTPUT_PP_PD,
  *            @arg  IO_MODE_IT_RISING_EDGE_PU
  *            @arg  IO_MODE_IT_FALLING_EDGE_PU
  *            @arg  IO_MODE_IT_LOW_LEVEL_PU
  *            @arg  IO_MODE_IT_HIGH_LEVEL_PU
  *            @arg  IO_MODE_IT_RISING_EDGE_PD
  *            @arg  IO_MODE_IT_FALLING_EDGE_PD
  *            @arg  IO_MODE_IT_LOW_LEVEL_PD
  *            @arg  IO_MODE_IT_HIGH_LEVEL_PD
  * @retval RT_EOK if all initializations are OK. Other value if error.
  */
rt_uint8_t rt_mfx_pin_mode(rt_uint32_t IoPin, IO_ModeTypedef IoMode)
{
    /* Configure the selected IO pin(s) mode */
    IoDrv->Config(0, IoPin, IoMode);

    return RT_EOK;
}

/**
  * @brief  Sets the IRQ_OUT pin polarity and type
  * @param  IoIrqOutPinPolarity: High/Low
  * @param  IoIrqOutPinType:     OpenDrain/PushPull
  * @retval OK
  */
rt_uint8_t rt_mfx_config_irq(rt_uint8_t IoIrqOutPinPolarity, rt_uint8_t IoIrqOutPinType)
{
    if((rt_mfx.id == MFXSTM32L152_ID_1) || (rt_mfx.id == MFXSTM32L152_ID_2))
    {
        /* Initialize the IO driver structure */
        mfxstm32l152_SetIrqOutPinPolarity(0, IoIrqOutPinPolarity);
        mfxstm32l152_SetIrqOutPinType(0, IoIrqOutPinType);
    }

    return RT_EOK;
}

/**
  * @brief  Sets the selected pins state.
  * @param  IoPin: Selected pins to write.
  *          This parameter can be any combination of the IO pins.
  * @param  PinState: New pins state to write
  * @retval None
  */
void rt_mfx_pin_write(rt_uint32_t IoPin, rt_base_t PinState)
{
    /* Set the Pin state */
    IoDrv->WritePin(0, IoPin, PinState);
}

/**
  * @brief  Gets the selected pins current state.
  * @param  IoPin: Selected pins to read.
  *          This parameter can be any combination of the IO pins.
  * @retval The current pins state
  */
rt_uint32_t rt_mfx_pin_read(rt_uint32_t IoPin)
{
    return(IoDrv->ReadPin(0, IoPin));
}

/**
  * @brief  Toggles the selected pins state.
  * @param  IoPin: Selected pins to toggle.
  *          This parameter can be any combination of the IO pins.
  * @note   This function is only used to toggle one pin in the same time
  * @retval None
  */
void rt_mfx_pin_toggle(rt_uint32_t IoPin)
{
    /* Toggle the current pin state */
    if(IoDrv->ReadPin(0, IoPin) != 0)
    {
        IoDrv->WritePin(0, IoPin, 0); /* Reset */
    }
    else
    {
        IoDrv->WritePin(0, IoPin, 1); /* Set */
    }
}

int rt_mfx_init(void)
{
    /* Read ID and verify the MFX is ready */
    rt_mfx.id = mfxstm32l152_io_drv.ReadID(0);
    if((rt_mfx.id == MFXSTM32L152_ID_1) || (rt_mfx.id == MFXSTM32L152_ID_2))
    {
        /* Initialize the IO driver structure */
        IoDrv = &mfxstm32l152_io_drv;

        /* Initialize MFX */
        IoDrv->Init(0);
        IoDrv->Start(0, IO_PIN_ALL);

        LOG_I("mfx init success, id: 0x%x", rt_mfx.id);

        return RT_EOK;
    }
    LOG_I("mfx init error, id: 0x%x", rt_mfx.id);

    return -RT_ERROR;
}
INIT_DEVICE_EXPORT(rt_mfx_init);
