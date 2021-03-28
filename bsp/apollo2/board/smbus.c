/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"

#ifdef RT_USING_SMBUS

#define SMBUS_GPIO_SDA    5
#define SMBUS_GPIO_SCL    6

#define mSDA_LOW()        am_hal_gpio_out_bit_clear(SMBUS_GPIO_SDA)    /* Clear SDA line */
#define mSDA_HIGH()       am_hal_gpio_out_bit_set(SMBUS_GPIO_SDA)      /* Set SDA line */
#define mSCL_LOW()        am_hal_gpio_out_bit_clear(SMBUS_GPIO_SCL)    /* Clear SCL line */
#define mSCL_HIGH()       am_hal_gpio_out_bit_set(SMBUS_GPIO_SCL)      /* Set SCL line */

#define mSDA_READ()       am_hal_gpio_input_bit_read(SMBUS_GPIO_SDA)   /* Read SDA line */

#define mSDA_IN()         am_hal_gpio_pin_config(SMBUS_GPIO_SDA, AM_HAL_GPIO_INPUT | AM_HAL_GPIO_PULL6K)  /* Set SDA as Input */
#define mSDA_OUT()        am_hal_gpio_pin_config(SMBUS_GPIO_SDA, AM_HAL_GPIO_OUTPUT)                      /* Set SDA as Output */
#define mSCL_OUT()        am_hal_gpio_pin_config(SMBUS_GPIO_SCL, AM_HAL_GPIO_OUTPUT)                      /* Set SCL as Output */

#define ACK       0
#define NACK      1

/* SCL keep time */
static void keep_delay(void)
{
    int i;
    for(i = 0; i < 30; i++)
       __nop();
}

static void few_delay(void)
{
    __nop();
    __nop();
}

static rt_uint8_t am_smbus_send_bit(rt_uint8_t send_bit)
{
    mSDA_OUT();
    few_delay();

    if(send_bit)        /* Send a bit */
        mSDA_HIGH();
    else
        mSDA_LOW();

    mSCL_HIGH();        /* High Level of Clock Pulse */
    keep_delay();

    mSCL_LOW();
    keep_delay();

    return 0;
}

static rt_uint8_t am_smbus_read_bit(void)
{
    rt_uint8_t read_bit;

    mSDA_IN();
    few_delay();

    mSCL_HIGH();             /* High Level of Clock Pulse */
    keep_delay();

    read_bit = mSDA_READ();  /* Read a bit, save it in Read_bit */

    mSCL_LOW();
    keep_delay();

    return read_bit;
}

static void am_smbus_start_bit(void)
{
    mSDA_OUT();
    mSDA_HIGH();     /* Generate bus free time between Stop */
    keep_delay();
    mSCL_HIGH();
    keep_delay();

    mSDA_LOW();      /* Hold time after (Repeated) Start */
    keep_delay();

    mSCL_LOW();
    keep_delay();
}

static void am_smbus_stop_bit(void)
{
    mSDA_OUT();
    mSDA_HIGH();     /* Generate bus free time between Stop */
    keep_delay();
    mSCL_LOW();
    keep_delay();

    mSDA_LOW();      /* Hold time after Stop */
    keep_delay();

    mSCL_HIGH();     /* For sleep mode(SCL needs to be high during Sleep.) */
    keep_delay();
}

static rt_uint8_t am_smbus_tx_byte(rt_uint8_t tx_byte)
{
    int i;
    rt_uint8_t ack_bit;
    rt_uint8_t bit_out;

    for(i = 0; i < 8; i++)
    {
        if(tx_byte&0x80)
            bit_out = 1;             /* If the current bit of Tx_buffer is 1 set bit_out */
        else
            bit_out = 0;             /* else clear bit_out */

        am_smbus_send_bit(bit_out);  /* Send the current bit on SDA */
        tx_byte <<= 1;               /* Get next bit for checking */
    }

    ack_bit = am_smbus_read_bit();   /* Get acknowledgment bit */

    return ack_bit;
}

static rt_uint8_t am_smbus_rx_byte(rt_uint8_t ack_nack)
{
    int i;
    rt_uint8_t rx_byte;

    for(i = 0; i < 8; i++)
    {
        if(am_smbus_read_bit())   /* Get a bit from the SDA line */
        {
            rx_byte <<= 1;        /* If the bit is HIGH save 1  in RX_buffer */
            rx_byte |=0x01;
        }
        else
        {
            rx_byte <<= 1;        /* If the bit is LOW save 0 in RX_buffer */
            rx_byte &=0xfe;
        }
    }
    am_smbus_send_bit(ack_nack);  /* Sends acknowledgment bit */

    return rx_byte;
}

rt_uint8_t am_smbus_tx_then_tx(rt_uint8_t SlaveAddress, rt_uint8_t command, rt_uint8_t* pBuffer, rt_uint16_t bytesNumber)
{
    int i;

    am_smbus_start_bit();                      /* Start condition */

    if(am_smbus_tx_byte(SlaveAddress))         /* Send SlaveAddress and write */
        return 1;

    if(am_smbus_tx_byte(command))              /* Send command */
        return 1;

    for(i = 0; i < bytesNumber; i++)
    {
        am_smbus_tx_byte(pBuffer[i]);          /* Write data, slave must send ACK */
    }

    am_smbus_stop_bit();                       /* Stop condition */

    return 0;
}

rt_uint8_t am_smbus_tx_then_rx(rt_uint8_t SlaveAddress, rt_uint8_t command, rt_uint8_t* pBuffer, rt_uint16_t bytesNumber)
{
    int i;

    am_smbus_start_bit();                      /* Start condition */

    if(am_smbus_tx_byte(SlaveAddress))         /* Send SlaveAddress and write */
        return 1;

    if(am_smbus_tx_byte(command))              /* Send command */
        return 1;

    am_smbus_start_bit();                      /* Repeated Start condition */

    if(am_smbus_tx_byte(SlaveAddress | 0x01))  /* Send SlaveAddress and read */
        return 1;

    for(i = 0; i < bytesNumber; i++)
    {
        pBuffer[i] = am_smbus_rx_byte(ACK);    /* Read data, master must send ACK */
    }

    am_smbus_stop_bit();                       /* Stop condition */

    return 0;
}

void am_smbus_scl_high(void)
{
    mSCL_HIGH();     /* For sleep mode(SCL needs to be high during Sleep.) */
    keep_delay();
}

void am_smbus_scl_low(void)
{
    mSCL_LOW();     /* For sleep mode(SCL needs to be high during Sleep.) */
    keep_delay();
}

int rt_hw_smbus_init(void)
{
    mSDA_OUT();
    mSCL_OUT();
    mSDA_HIGH();   /* bus free */
    mSCL_HIGH();

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(rt_hw_smbus_init);
#endif

#endif

/*@}*/
