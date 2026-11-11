/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-12-20     BruceOu           the first version
 * 2026-01-11     ShiHongchao       Fix the I2C master receive mode B software
 *                                  flow and add support for mode A
 */

#include "drv_hard_i2c.h"
#include "i2c_config.h"

#ifdef RT_USING_I2C

#define LOG_TAG              "drv.i2c"
#include <rtdbg.h>

#if !defined(BSP_USING_HARD_I2C0) && !defined(BSP_USING_HARD_I2C1) && !defined(BSP_USING_HARD_I2C2) && !defined(BSP_USING_HARD_I2C3) && !defined(BSP_USING_HARD_I2C4) && !defined(BSP_USING_HARD_I2C5)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
#endif

#if defined(BSP_USING_HARD_I2C0)
struct rt_i2c_bus_device i2c0;
#endif /* BSP_USING_I2C0 */

#if defined(BSP_USING_HARD_I2C1)
struct rt_i2c_bus_device i2c1;
#endif /* BSP_USING_I2C1 */

#if defined(BSP_USING_HARD_I2C2)
struct rt_i2c_bus_device i2c2;
#endif /* BSP_USING_I2C2 */

#if defined(BSP_USING_HARD_I2C3)
struct rt_i2c_bus_device i2c3;
#endif /* BSP_USING_I2C3 */

#if defined(BSP_USING_HARD_I2C4)
struct rt_i2c_bus_device i2c4;
#endif /* BSP_USING_I2C4 */

#if defined(BSP_USING_HARD_I2C5)
struct rt_i2c_bus_device i2c5;
#endif /* BSP_USING_I2C5 */

#if defined (SOC_SERIES_GD32F5xx)
#define i2c_flag_get_gd                      i2c_add_flag_get
#define I2C_FLAG_RBNE_GD                     I2C_ADD_FLAG_RBNE
#define i2c_data_receive_gd                  i2c_add_data_receive
#define I2C_STAT_GD                          I2C_ADD_STAT
#define I2C_STAT_TBE_GD                      I2C_ADD_STAT_TBE
#define i2c_data_transmit_gd                 i2c_add_data_transmit
#define I2C_STAT_TI_GD                       I2C_ADD_STAT_TI
#define i2c_address10_enable_gd              i2c_add_address10_enable
#define i2c_address10_disable_gd             i2c_add_address10_disable
#define i2c_master_addressing_gd             i2c_add_master_addressing
#define I2C_MASTER_RECEIVE_GD                I2C_ADD_MASTER_RECEIVE
#define i2c_transfer_byte_number_config_gd   i2c_add_transfer_byte_number_config
#define i2c_start_on_bus_gd                  i2c_add_start_on_bus
#define i2c_automatic_end_enable_gd          i2c_add_automatic_end_enable
#define i2c_automatic_end_disable_gd         i2c_add_automatic_end_disable
#define I2C_MASTER_TRANSMIT_GD               I2C_ADD_MASTER_TRANSMIT
#define I2C_FLAG_I2CBSY_GD                   I2C_ADD_FLAG_I2CBSY
#define I2C_FLAG_TC_GD                       I2C_ADD_FLAG_TC
#define I2C_FLAG_TI_GD                       I2C_ADD_FLAG_TI
#define I2C_FLAG_TBE_GD                      I2C_ADD_FLAG_TBE
#define I2C_FLAG_NACK_GD                     I2C_ADD_FLAG_NACK
#define i2c_stop_on_bus_gd                   i2c_add_stop_on_bus
#define I2C_FLAG_STPDET_GD                   I2C_ADD_FLAG_STPDET
#define i2c_timing_config_gd                 i2c_add_timing_config
#define i2c_master_clock_config_gd           i2c_add_master_clock_config
#define i2c_enable_gd                        i2c_add_enable
#define i2c_flag_clear_gd                    i2c_add_flag_clear

#else

#define i2c_flag_get_gd                      i2c_flag_get
#define I2C_FLAG_RBNE_GD                     I2C_FLAG_RBNE
#define i2c_data_receive_gd                  i2c_data_receive
#define I2C_STAT_GD                          I2C_STAT
#define I2C_STAT_TBE_GD                      I2C_STAT_TBE
#define i2c_data_transmit_gd                 i2c_data_transmit
#define I2C_STAT_TI_GD                       I2C_STAT_TI
#define i2c_address10_enable_gd              i2c_address10_enable
#define i2c_address10_disable_gd             i2c_address10_disable
#define i2c_master_addressing_gd             i2c_master_addressing
#define I2C_MASTER_RECEIVE_GD                I2C_MASTER_RECEIVE
#define i2c_transfer_byte_number_config_gd   i2c_transfer_byte_number_config
#define i2c_start_on_bus_gd                  i2c_start_on_bus
#define i2c_automatic_end_enable_gd          i2c_automatic_end_enable
#define i2c_automatic_end_disable_gd         i2c_automatic_end_disable
#define I2C_MASTER_TRANSMIT_GD               I2C_MASTER_TRANSMIT
#define I2C_FLAG_I2CBSY_GD                   I2C_FLAG_I2CBSY
#define I2C_FLAG_TC_GD                       I2C_FLAG_TC
#define I2C_FLAG_TI_GD                       I2C_FLAG_TI
#define I2C_FLAG_TBE_GD                      I2C_FLAG_TBE
#define I2C_FLAG_NACK_GD                     I2C_FLAG_NACK
#define i2c_stop_on_bus_gd                   i2c_stop_on_bus
#define I2C_FLAG_STPDET_GD                   I2C_FLAG_STPDET
#define i2c_timing_config_gd                 i2c_timing_config
#define i2c_master_clock_config_gd           i2c_master_clock_config
#define i2c_enable_gd                        i2c_enable
#define i2c_flag_clear_gd                    i2c_flag_clear

#endif

#if defined (SOC_SERIES_GD32F5xx)
#define IS_I2C_LEGACY(periph)  ((periph) == I2C0 || (periph) == I2C1 || (periph) == I2C2)
#elif defined (SOC_SERIES_GD32F4xx)
#define IS_I2C_LEGACY(periph)  (1)
#elif (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
#define IS_I2C_LEGACY(periph)  (0)
#endif

static const struct gd32_i2c_bus gd_i2c_config[] = {
#ifdef BSP_USING_HARD_I2C0
    I2C0_CONFIG,
#endif
#ifdef BSP_USING_HARD_I2C1
    I2C1_CONFIG,
#endif
#ifdef BSP_USING_HARD_I2C2
    I2C2_CONFIG,
#endif
#ifdef BSP_USING_HARD_I2C3
    I2C3_CONFIG,
#endif
#ifdef BSP_USING_HARD_I2C4
    I2C4_CONFIG,
#endif
#ifdef BSP_USING_HARD_I2C5
    I2C5_CONFIG,
#endif
};

/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c
  * @retval None
  */
static void gd32_i2c_gpio_init(const struct gd32_i2c_bus *i2c)
{
    rt_uint32_t scl_port, sda_port;
    rt_uint32_t scl_pin, sda_pin;
    rt_uint32_t pin_af;
    rcu_periph_enum scl_periph, sda_periph;

    if(get_pin_config(i2c->scl_pin_name, &scl_port, &scl_pin, &scl_periph) != RT_EOK)
    {
        return;
    }

    if(get_pin_config(i2c->sda_pin_name, &sda_port, &sda_pin, &sda_periph) != RT_EOK)
    {
        return;
    }

    pin_alternate_config(i2c->alternate, &pin_af);

    /* enable I2C and GPIO clock */
    rcu_periph_clock_enable(scl_periph);
    rcu_periph_clock_enable(sda_periph);
    rcu_periph_clock_enable(i2c->per_clk);

    /* configure I2C pins as alternate function open-drain */
    gpio_af_set(scl_port, pin_af, scl_pin);
    gpio_mode_set(scl_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, scl_pin);
#if (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
    gpio_output_options_set(scl_port, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, scl_pin);
    gpio_af_set(sda_port, pin_af, sda_pin);
    gpio_mode_set(sda_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, sda_pin);
    gpio_output_options_set(sda_port, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, sda_pin);
#else
    gpio_output_options_set(scl_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, scl_pin);
    gpio_af_set(sda_port, pin_af, sda_pin);
    gpio_mode_set(sda_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, sda_pin);
    gpio_output_options_set(sda_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, sda_pin);
#endif
}

#if (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
static void gd32_i2c_clock_source_config(rt_uint32_t i2c_periph)
{
    switch(i2c_periph)
    {
    case I2C0:
        rcu_i2c_clock_config(IDX_I2C0, RCU_I2CSRC_IRC64MDIV);
        break;
    case I2C1:
        rcu_i2c_clock_config(IDX_I2C1, RCU_I2CSRC_IRC64MDIV);
        break;
    case I2C2:
        rcu_i2c_clock_config(IDX_I2C2, RCU_I2CSRC_IRC64MDIV);
        break;
    case I2C3:
        rcu_i2c_clock_config(IDX_I2C3, RCU_I2CSRC_IRC64MDIV);
        break;
    default:
        break;
    }
}
#endif

/**
  * @brief  read data.
  * @param  i2c_periph
  * @param  *p_buffer
  * @param  data_byte
  * @retval None
  */
static uint8_t gd32_i2c_read(rt_uint32_t i2c_periph, rt_uint8_t *p_buffer,
                             rt_uint16_t data_byte, rt_tick_t timeout)
{
#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
    rt_tick_t start_tick;
#else
    RT_UNUSED(timeout);
#endif

    if (data_byte == 0) return 1;

#if defined(BSP_USING_RECEIVING_A) && \
        (defined(SOC_SERIES_GD32F4xx) || defined(SOC_SERIES_GD32F5xx))
    /*
        In single-byte reception, disable ACK because the master needs to send
        NACK after receiving the first byte,indicating no more data will be
        received, then immediately send the stop condition
    */
    if(data_byte == 1)
    {
        /* disable acknowledge */
        i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_periph);
    }
#endif

    /* while there is data to be read */
    while(data_byte)
    {
#if defined (SOC_SERIES_GD32F5xx) || defined (SOC_SERIES_GD32F4xx)
        if(IS_I2C_LEGACY(i2c_periph))
        {
#ifdef BSP_USING_RECEIVING_A
            /*
                After receiving the second-to-last byte, ACK should be disabled
                and STOP should be set, to ensure that NACK is sent after receiving
                the last byte and the stop condition is transmitted
            */
            if(2 == data_byte)
            {
                    /* wait until BTC bit is set */
                    while(!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE));
                    /* disable acknowledge */
                    i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
                    /* send a stop condition to I2C bus */
                    i2c_stop_on_bus(i2c_periph);
            }
#elif defined(BSP_USING_RECEIVING_B)
            /*
                For 3-byte reception: Wait for byte transfer completion, then
                disable ACK so NACK is automatically sent after receiving the
                last byte
                For 2-byte reception: Wait for byte transfer completion, then
                send stop condition to ensure direct stop after receiving the
                last byte instead of sending ACK
            */
            if(3 == data_byte)
            {
                    /* wait until BTC bit is set */
                    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
                    /* disable acknowledge */
                    i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
            }
            else if(2 == data_byte)
            {
                    /* wait until BTC bit is set */
                    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
                    /* send a stop condition to I2C bus */
                    i2c_stop_on_bus(i2c_periph);
            }
#else
#error "Please select the receiving scheme."
#endif
            /* wait until RBNE bit is set */
            if(i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            {
                    /* read a byte from the EEPROM */
                    *p_buffer = i2c_data_receive(i2c_periph);
                    /* point to the next location where the byte read will be saved */
                    p_buffer++;
                    /* decrement the read bytes counter */
                    data_byte--;
            }
        }else
#endif
        {
#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
            /* wait until the RBNE bit is set */
            start_tick = rt_tick_get();
            while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_RBNE_GD))
            {
                if(i2c_flag_get_gd(i2c_periph, I2C_FLAG_NACK_GD))
                {
                    return 1;
                }
                if((rt_tick_get() - start_tick) >= timeout)
                {
                    return 1;
                }
            }

            /* read a byte */
            *p_buffer = i2c_data_receive_gd(i2c_periph);
            /* point to the next location where the byte read will be saved */
            p_buffer++;
            /* decrement the read bytes counter */
            data_byte--;
#endif
        }
    }
    return 0;
}

/**
  * @brief  write data.
  * @param  i2c_periph
  * @param  *p_buffer
  * @param  data_byte
  * @retval None
  */
static uint8_t gd32_i2c_write(rt_uint32_t i2c_periph, uint8_t *p_buffer,
                              uint16_t data_byte, rt_tick_t timeout)
{
#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
    rt_tick_t start_tick;
#else
    RT_UNUSED(timeout);
#endif

    if (data_byte == 0) return 1;

    while(data_byte)
    {
#if defined (SOC_SERIES_GD32F5xx) || defined (SOC_SERIES_GD32F4xx)
        if(IS_I2C_LEGACY(i2c_periph))
        {
            /* data transmission */
            i2c_data_transmit(i2c_periph, *p_buffer);
            /* point to the next byte to be written */
            p_buffer++;
            /* decrement the write bytes counter */
            data_byte--;
            /* wait until the TI bit is set */
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
        }
        else
#endif
        {
#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
            /* wait until the transmit data buffer is empty */
            I2C_STAT_GD(i2c_periph) |= I2C_STAT_TBE_GD;
            start_tick = rt_tick_get();
            while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TBE_GD))
            {
                if(i2c_flag_get_gd(i2c_periph, I2C_FLAG_NACK_GD) ||
                   ((rt_tick_get() - start_tick) >= timeout))
                {
                    return 1;
                }
            }

            while(data_byte)
            {
                /* wait until the TI bit is set */
                start_tick = rt_tick_get();
                while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TI_GD))
                {
                    if(i2c_flag_get_gd(i2c_periph, I2C_FLAG_NACK_GD))
                    {
                        return 1;
                    }
                    if((rt_tick_get() - start_tick) >= timeout)
                    {
                        return 1;
                    }
                }
                /* data transmission */
                i2c_data_transmit_gd(i2c_periph, *p_buffer);
                /* point to the next byte to be written */
                p_buffer++;
                /* decrement the write bytes counter */
                data_byte--;
            }
#endif
        }
    }

    if(data_byte != 0)
    {
        return 1;
    }
    return 0;
}

/**
  * @brief
  * @param
  * @param
  * @param
  * @retval
  */

static rt_ssize_t gd32_i2c_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg = RT_NULL;
    struct gd32_i2c_bus *gd32_i2c;
    rt_uint32_t i;
#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
    rt_tick_t start_tick;
    rt_bool_t address_probe = RT_FALSE;
    rt_bool_t stop_generated = RT_FALSE;
    rt_bool_t bus_started = RT_FALSE;
    struct rt_i2c_msg *phase_msg;
    rt_uint32_t phase_end;
    rt_uint32_t phase_total_byte;
#endif
    rt_err_t ret = -RT_ERROR;

    RT_ASSERT(bus != RT_NULL);

    if(msgs == RT_NULL || num == 0 || (msgs[0].flags & RT_I2C_NO_START))
    {
        return -RT_EINVAL;
    }

    gd32_i2c = (struct gd32_i2c_bus *)bus->priv;

#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
    if(!IS_I2C_LEGACY(gd32_i2c->i2c_periph))
    {
        phase_msg = &msgs[0];
        for(i = 1; i < num; i++)
        {
            if(msgs[i].flags & RT_I2C_NO_START)
            {
                if((msgs[i].addr != phase_msg->addr) ||
                   ((msgs[i].flags & (RT_I2C_RD | RT_I2C_ADDR_10BIT)) !=
                    (phase_msg->flags & (RT_I2C_RD | RT_I2C_ADDR_10BIT))))
                {
                    return -RT_EINVAL;
                }
            }else{
                phase_msg = &msgs[i];
            }
        }
    }
#endif

    for(i = 0; i < num;)
    {
        msg = &msgs[i];
#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
        if(!IS_I2C_LEGACY(gd32_i2c->i2c_periph))
        {
            phase_end = i + 1;
            phase_total_byte = msg->len;
            while((phase_end < num) && (msgs[phase_end].flags & RT_I2C_NO_START))
            {
                phase_total_byte += msgs[phase_end].len;
                phase_end++;
            }

            address_probe = !(msg->flags & (RT_I2C_RD | RT_I2C_NO_START | RT_I2C_NO_STOP)) &&
                    (msg->len == 0) && (phase_end == (i + 1));
            stop_generated = RT_FALSE;

            if(!bus_started)
            {
                start_tick = rt_tick_get();
                while(i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY_GD))
                {
                    if((rt_tick_get() - start_tick) >= bus->timeout)
                    {
                        LOG_E("i2c bus busy timeout");
                        ret = -RT_ETIMEOUT;
                        goto out;
                    }
                }
            }

            {
                rt_uint32_t address = msg->addr;

                if(msg->flags & RT_I2C_ADDR_10BIT)
                {
                    /* enable 10-bit addressing mode in master mode */
                    i2c_address10_enable_gd(gd32_i2c->i2c_periph);
                }else{
                    /* disable 10-bit addressing mode in master mode */
                    i2c_address10_disable_gd(gd32_i2c->i2c_periph);
                    address <<= 1;
                }

                if(msg->flags & RT_I2C_RD)
                {
                    /* configure slave address */
                    i2c_master_addressing_gd(gd32_i2c->i2c_periph, address, I2C_MASTER_RECEIVE_GD);
                }else{
                    /* configure slave address */
                    i2c_master_addressing_gd(gd32_i2c->i2c_periph, address, I2C_MASTER_TRANSMIT_GD);
                    if(address_probe)
                    {
                        i2c_flag_clear_gd(gd32_i2c->i2c_periph,
                                I2C_FLAG_STPDET_GD | I2C_FLAG_NACK_GD);
                        i2c_automatic_end_enable_gd(gd32_i2c->i2c_periph);
                    }
                }

                i2c_transfer_byte_number_config_gd(gd32_i2c->i2c_periph, phase_total_byte);
                /* send a start condition to I2C bus */
                i2c_start_on_bus_gd(gd32_i2c->i2c_periph);
                bus_started = RT_TRUE;
            }

            if(address_probe)
            {
                rt_bool_t address_nack = RT_FALSE;

                start_tick = rt_tick_get();
                while(!i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_STPDET_GD))
                {
                    if(i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_NACK_GD))
                    {
                        address_nack = RT_TRUE;
                    }

                    if((rt_tick_get() - start_tick) >= bus->timeout)
                    {
                        LOG_E("i2c address probe timeout");
                        i2c_automatic_end_disable_gd(gd32_i2c->i2c_periph);
                        ret = -RT_ETIMEOUT;
                        goto out;
                    }
                }

                if(i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_NACK_GD))
                {
                    address_nack = RT_TRUE;
                }
                i2c_automatic_end_disable_gd(gd32_i2c->i2c_periph);
                i2c_flag_clear_gd(gd32_i2c->i2c_periph,
                        I2C_FLAG_STPDET_GD | I2C_FLAG_NACK_GD);
                stop_generated = RT_TRUE;
                msg = &msgs[phase_end - 1];
                i = phase_end;
                if(address_nack)
                {
                    ret = -RT_EIO;
                    goto out;
                }
                continue;
            }

            while(i < phase_end)
            {
                msg = &msgs[i];
                if(msg->flags & RT_I2C_RD)
                {
                    if(gd32_i2c_read(gd32_i2c->i2c_periph, msg->buf, msg->len,
                                     bus->timeout) != 0)
                    {
                        LOG_E("i2c bus read failed,i2c bus stop!");
                        goto out;
                    }
                }else{
                    if(gd32_i2c_write(gd32_i2c->i2c_periph, msg->buf, msg->len,
                                      bus->timeout) != 0)
                    {
                        LOG_E("i2c bus write failed,i2c bus stop!");
                        goto out;
                    }
                }
                i++;
            }

            start_tick = rt_tick_get();
            while(!i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_TC_GD))
            {
                if(i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_NACK_GD))
                {
                    ret = -RT_EIO;
                    goto out;
                }
                if((rt_tick_get() - start_tick) >= bus->timeout)
                {
                    LOG_E("i2c transfer phase timeout");
                    ret = -RT_ETIMEOUT;
                    goto out;
                }
            }
            continue;
        }
#endif
        if (!(msg->flags & RT_I2C_NO_START))
        {
#if defined (SOC_SERIES_GD32F5xx) || defined (SOC_SERIES_GD32F4xx)
            if(IS_I2C_LEGACY(gd32_i2c->i2c_periph))
            {

                if(msg->flags & RT_I2C_RD)
                {
                    if(i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY))
                    {
                            i2c_stop_on_bus(gd32_i2c->i2c_periph);
                    }
                    /* enable acknowledge */
                    i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_ENABLE);
                    /* i2c master sends start signal only when the bus is idle */
                    while(i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY));
#ifdef BSP_USING_RECEIVING_B
                    /*  */
                    if(msg->len == 2)
                    {
                        i2c_ackpos_config(gd32_i2c->i2c_periph, I2C_ACKPOS_NEXT);
                    }
#endif
                    /* send the start signal */
                    i2c_start_on_bus(gd32_i2c->i2c_periph);
                     /* i2c master sends START signal successfully */
                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND));

                    i2c_master_addressing(gd32_i2c->i2c_periph, msg->addr, I2C_RECEIVER);

                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND));
#ifdef BSP_USING_RECEIVING_B
                    if(msg->len <= 2)
                    {
                        i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_DISABLE);
                    }
#endif
                    /* address flag set means i2c slave sends ACK */
                    i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
#ifdef BSP_USING_RECEIVING_B
                    if(msg->len == 1)
                    {
                        i2c_stop_on_bus(gd32_i2c->i2c_periph);
                    }
#endif

               }else {
                    /* configure slave address */
                    while(i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY));
                    /* send a start condition to I2C bus */
                    i2c_start_on_bus(gd32_i2c->i2c_periph);
                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND));

                    i2c_master_addressing(gd32_i2c->i2c_periph, msg->addr, I2C_TRANSMITTER);
                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND));

                    i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
               }
            }
#endif
        }

        if(msg->flags & RT_I2C_RD)
        {
            if(gd32_i2c_read(gd32_i2c->i2c_periph, msg->buf, msg->len,
                             bus->timeout) != 0)
            {
                LOG_E("i2c bus read failed,i2c bus stop!");
                goto out;
            }
        }else {
            if(gd32_i2c_write(gd32_i2c->i2c_periph, msg->buf, msg->len,
                              bus->timeout) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                goto out;
            }
       }
        i++;
    }
    ret = i;

out:
#if defined (SOC_SERIES_GD32F5xx) || defined (SOC_SERIES_GD32F4xx)
    if(IS_I2C_LEGACY(gd32_i2c->i2c_periph))
    {

        if(!(msg->flags & RT_I2C_NO_STOP))
        {
            if(msg->flags & RT_I2C_RD)
            {
                while((I2C_CTL0(gd32_i2c->i2c_periph) & I2C_CTL0_STOP));
            }else{
                /* send a stop condition to I2C bus */
                i2c_stop_on_bus(gd32_i2c->i2c_periph);
                /* wait until stop condition generate */
                while((I2C_CTL0(gd32_i2c->i2c_periph) & I2C_CTL0_STOP));
                /* clear the STPDET bit */
            }
        }
    }else
#endif
    {
#if defined (SOC_SERIES_GD32F5xx) || (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
        if(!(msg->flags & RT_I2C_NO_STOP) && !stop_generated)
        {
            if((ret >= 0) && !address_probe)
            {
                start_tick = rt_tick_get();
                while(!i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_TC_GD))
                {
                    if(i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_NACK_GD))
                    {
                        ret = -RT_EIO;
                        break;
                    }

                    if((rt_tick_get() - start_tick) >= bus->timeout)
                    {
                        LOG_E("i2c transfer complete timeout");
                        ret = -RT_ETIMEOUT;
                        break;
                    }
                }
            }
            /* send a stop condition to I2C bus */
            i2c_stop_on_bus_gd(gd32_i2c->i2c_periph);
            /* wait until stop condition generate */
            start_tick = rt_tick_get();
            while(!i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_STPDET_GD))
            {
                if((rt_tick_get() - start_tick) >= bus->timeout)
                {
                    LOG_E("i2c stop timeout");
                    ret = -RT_ETIMEOUT;
                    break;
                }
            }
            /* clear the STPDET bit */
            i2c_flag_clear_gd(gd32_i2c->i2c_periph,
                    I2C_FLAG_STPDET_GD | I2C_FLAG_NACK_GD);
        }
#endif
    }
    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops = {
    .master_xfer = gd32_i2c_master_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = RT_NULL
};

/**
  * @brief  I2C initialization function
  * @param  None
  * @retval RT_EOK indicates successful initialization.
  */
int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(gd_i2c_config) / sizeof(gd_i2c_config[0]);
//    rt_err_t result;

    for(int i = 0; i < obj_num; i++)
    {
#if (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
        gd32_i2c_clock_source_config(gd_i2c_config[i].i2c_periph);
#endif
        gd32_i2c_gpio_init(&gd_i2c_config[i]);

        /* configure I2C timing. I2C speed clock=400kHz*/
#if defined (SOC_SERIES_GD32F5xx) || defined (SOC_SERIES_GD32F4xx)
        if(IS_I2C_LEGACY(gd_i2c_config[i].i2c_periph))
        {

            i2c_clock_config(gd_i2c_config[i].i2c_periph, 100000, I2C_DTCY_2);
            i2c_mode_addr_config(gd_i2c_config[i].i2c_periph, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0xa0);
            i2c_enable(gd_i2c_config[i].i2c_periph);
            i2c_ack_config(gd_i2c_config[i].i2c_periph, I2C_ACK_ENABLE);
        }else
#endif
        {
#if defined (SOC_SERIES_GD32F5xx)
            i2c_timing_config_gd(gd_i2c_config[i].i2c_periph, 0x1, 0x7, 0);
            i2c_master_clock_config_gd(gd_i2c_config[i].i2c_periph, 0x2D, 0x87);

            /* enable I2C1 */
            i2c_enable_gd(gd_i2c_config[i].i2c_periph);
#elif (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
            /* GD32H7xx vendor timing for a 64 MHz I2C kernel clock at 400 kHz. */
            i2c_timing_config_gd(gd_i2c_config[i].i2c_periph, 0x0, 0x6, 0);
            i2c_master_clock_config_gd(gd_i2c_config[i].i2c_periph, 0x26, 0x73);
            i2c_enable_gd(gd_i2c_config[i].i2c_periph);
#endif
        }

        gd_i2c_config[i].i2c_bus->ops = &i2c_ops;
        gd_i2c_config[i].i2c_bus->priv = (void *)&gd_i2c_config[i];

        rt_i2c_bus_device_register(gd_i2c_config[i].i2c_bus, gd_i2c_config[i].device_name);
    }

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
