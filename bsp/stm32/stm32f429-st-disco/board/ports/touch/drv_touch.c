/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     xuzhuoyi     first implementation.
 */

#include "drv_touch.h"
#include "drivers/i2c.h"

#ifdef PKG_USING_LITTLEVGL2RTT
#include "littlevgl2rtt.h"
#endif


#define TSC_I2C_ADDR    0x41            /* 7-bit I2C address                  */

static struct rt_i2c_bus_device *stmpe811_i2c_bus;


/**
  \fn          int32_t touch_readRegister (uint8_t reg, uint8_t *val)
  \brief       Read register value from Touchscreen controller
  \param[in]   reg    Register address
  \param[out]  val    Pointer where data will be read from register
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
static int32_t touch_read (uint8_t reg, uint8_t *val)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = TSC_I2C_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &reg;
    msgs[0].len   = 1;

    msgs[1].addr  = TSC_I2C_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = val;
    msgs[1].len   = 1;

    if (rt_i2c_transfer(stmpe811_i2c_bus, msgs, 2) == 2)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }

}

/**
  \fn          int32_t touch_writeData (uint8_t reg, const uint8_t *val)
  \brief       Write value to Touchscreen controller register
  \param[in]   reg    Register address
  \param[in]   val    Pointer with data to write to register
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
static int32_t touch_write(uint8_t reg, uint8_t val)
{
    struct rt_i2c_msg msgs;
    rt_uint8_t buf[2];

    buf[0] = reg;
    buf[1] = val;

    msgs.addr  = TSC_I2C_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = buf;
    msgs.len   = 2;

    if (rt_i2c_transfer(stmpe811_i2c_bus, &msgs, 1) == 1)
    {
    return RT_EOK;
    }
    else
    {
    return -RT_ERROR;
    }

}


/**
  \fn          int32_t Touch_Initialize (void)
  \brief       Initialize touchscreen
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
static rt_err_t stmpe811_touch_init(rt_device_t dev)
{
    stmpe811_i2c_bus = rt_i2c_bus_device_find("i2c3");

    touch_write(STMPE811_SYS_CTRL1,      0x02); /* Reset Touch-screen controller */
    rt_thread_mdelay(10);                              /* Wait 10ms                     */


    touch_write(STMPE811_SYS_CTRL2,      0x0C); /* Enable TSC and ADC            */
    touch_write(STMPE811_ADC_CTRL1,      0x68); /* Set sample time , 12-bit mode */
    rt_thread_mdelay(1);                               /* Wait 1ms                      */

    touch_write(STMPE811_ADC_CTRL2,      0x01); /* ADC frequency 3.25 MHz        */
    touch_write(STMPE811_TSC_CFG,        0xC2); /* Detect delay 10us,
                                                 Settle time 500us             */
    touch_write(STMPE811_FIFO_TH,        0x01); /* Threshold for FIFO            */
    touch_write(STMPE811_FIFO_STA,       0x01); /* FIFO reset                    */
    touch_write(STMPE811_FIFO_STA,       0x00); /* FIFO not reset                */
    touch_write(STMPE811_TSC_FRACTION_Z, 0x07); /* Fraction z                    */
    touch_write(STMPE811_TSC_I_DRIVE,    0x01); /* Drive 50 mA typical           */
    touch_write(STMPE811_GPIO_AF,        0x00); /* Pins are used for touchscreen */
    touch_write(STMPE811_TSC_CTRL,       0x01); /* Enable TSC                    */

    return 0;
}

/**
  \fn          int32_t Touch_Uninitialize (void)
  \brief       De-initialize touchscreen
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t touch_uninitialize (void) {
  touch_write(STMPE811_SYS_CTRL1, 0x02);  /* Reset Touch-screen controller    */
  return 0;
}

/**
  \fn          int32_t Touch_GetState (TOUCH_STATE *pState)
  \brief       Get touchscreen state
  \param[out]  pState  pointer to TOUCH_STATE structure
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t touch_get_state(struct touch_state *state)
{
    uint8_t val;
    uint8_t num;
    uint8_t xyz[4];
    int32_t res;
    struct rt_i2c_msg msgs[2];

    /* Read touch status */
    res = touch_read(STMPE811_TSC_CTRL, &val);
    if (res < 0) return -1;
    state->pressed = (val & (1 << 7)) ? 1 : 0;
  
    if (state->pressed)
    {
        val = STMPE811_TSC_DATA;

        /* If FIFO overflow, discard all samples except the last one */
        res = touch_read(STMPE811_FIFO_SIZE, &num);
        if (res < 0 || num == 0) return -1;

        while (num--)
        {
            msgs[0].addr  = TSC_I2C_ADDR;
            msgs[0].flags = RT_I2C_WR;
            msgs[0].buf   = &val;
            msgs[0].len   = 1;

            //rt_i2c_transfer(stmpe811_i2c_bus, &msgs, 1);
          //ptrI2C->MasterTransmit (TSC_I2C_ADDR, &val, 1, true);
          //while (ptrI2C->GetStatus().busy);
            msgs[1].addr  = TSC_I2C_ADDR;
            msgs[1].flags = RT_I2C_RD;
            msgs[1].buf   = xyz;
            msgs[1].len   = 4;
            rt_i2c_transfer(stmpe811_i2c_bus, msgs, 2);
          //ptrI2C->MasterReceive (TSC_I2C_ADDR, xyz, 4, false);
          //while (ptrI2C->GetStatus().busy);
        }
        state->x =  (int16_t)((xyz[0] << 4) | ((xyz[1] & 0xF0) >> 4));
        state->y =  (int16_t) (xyz[2]       | ((xyz[1] & 0x0F) << 8));
    }
    else
    {
        /* Clear all data in FIFO */
        touch_write(STMPE811_FIFO_STA, 0x1);
        touch_write(STMPE811_FIFO_STA, 0x0);
    }

    return 0;
}

void touch_show_state()
{
    int16_t x;
    int16_t y;
    struct touch_state ts;
    touch_get_state(&ts);
    x = (3706 - ts.x) / 14;
    y = (-461 + ts.y) / 10.5;
    rt_kprintf("[drv_touch] touch_show_state, x: %d, y: %d, pressed: %d, padding: %d\n", ts.x , ts.y, ts.pressed, ts.padding);
    rt_kprintf("[drv_touch] touch_show_state, phy x: %d, phy y: %d\n", x , y);
}
MSH_CMD_EXPORT(touch_show_state, show screen coordinate in touching);

static int rt_hw_touch_init(void)
{
    static struct rt_device touch;

    /* init device structure */
    touch.type = RT_Device_Class_Unknown;
    touch.init = stmpe811_touch_init;
    touch.user_data = RT_NULL;

    /* register touch device to RT-Thread */
    rt_device_register(&touch, "touch", RT_DEVICE_FLAG_RDWR);
    
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_touch_init);
