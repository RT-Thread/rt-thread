/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include "bcm283x.h"

rt_uint32_t bcm283x_peri_read(volatile rt_ubase_t addr)
{
    rt_uint32_t ret;
    __sync_synchronize();
    ret = HWREG32(addr);
    __sync_synchronize();
    return ret;
}

rt_uint32_t bcm283x_peri_read_nb(volatile rt_ubase_t addr)
{
    return HWREG32(addr);
}

void bcm283x_peri_write(volatile rt_ubase_t addr, rt_uint32_t value)
{
    __sync_synchronize();
    HWREG32(addr) = value;
    __sync_synchronize();
}

void bcm283x_peri_write_nb(volatile rt_ubase_t addr, rt_uint32_t value)
{
    HWREG32(addr) = value;
}

void bcm283x_peri_set_bits(volatile rt_ubase_t addr, rt_uint32_t value, rt_uint32_t mask)
{
    rt_uint32_t v = bcm283x_peri_read(addr);
    v = (v & ~mask) | (value & mask);
    bcm283x_peri_write(addr, v);
}

void bcm283x_gpio_fsel(rt_uint8_t pin, rt_uint8_t mode)
{
    volatile rt_ubase_t addr = (BCM283X_GPIO_BASE + BCM283X_GPIO_GPFSEL0 + (pin / 10) * 4);
    rt_uint8_t   shift = (pin % 10) * 3;
    rt_uint32_t  mask = BCM283X_GPIO_FSEL_MASK << shift;
    rt_uint32_t  value = mode << shift;

    bcm283x_peri_set_bits(addr, value, mask);
}

void bcm283x_gpio_set(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPSET0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    bcm283x_peri_write(addr, 1 << shift);
}

void bcm283x_gpio_clr(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPCLR0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    bcm283x_peri_write(addr, 1 << shift);
}

rt_uint8_t bcm283x_gpio_lev(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM2835_GPIO_GPLEV0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = bcm283x_peri_read(addr);
    return (value & (1 << shift)) ? HIGH : LOW;
}

rt_uint8_t bcm283x_gpio_eds(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPEDS0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = bcm283x_peri_read(addr);
    return (value & (1 << shift)) ? HIGH : LOW;
}

/* Write a 1 to clear the bit in EDS */
void bcm283x_gpio_set_eds(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPEDS0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_write(addr, value);
}

/* Rising edge detect enable */
void bcm283x_gpio_ren(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPREN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, value, value);
}

void bcm283x_gpio_clr_ren(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPREN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, 0, value);
}

/* Falling edge detect enable */
void bcm283x_gpio_fen(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPFEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, value, value);
}
void bcm283x_gpio_clr_fen(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPFEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, 0, value);
}

/* High detect enable */
void bcm283x_gpio_hen(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPHEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, value, value);
}

void bcm283x_gpio_clr_hen(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPHEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, 0, value);
}

/* Low detect enable */
void bcm283x_gpio_len(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPLEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, value, value);
}

void bcm283x_gpio_clr_len(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPLEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, 0, value);
}

/* Async rising edge detect enable */
void bcm283x_gpio_aren(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPAREN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, value, value);
}
void bcm283x_gpio_clr_aren(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPAREN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, 0, value);
}

/* Async falling edge detect enable */
void bcm283x_gpio_afen(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPAFEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, value, value);
}
void bcm283x_gpio_clr_afen(rt_uint8_t pin)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPAFEN0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    rt_uint32_t value = 1 << shift;
    bcm283x_peri_set_bits(addr, 0, value);
}

/* Set pullup/down */
void bcm283x_gpio_pud(rt_uint8_t pud)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPPUD;
    bcm283x_peri_write(addr, pud);
}

/* Pullup/down clock
// Clocks the value of pud into the GPIO pin
*/
void bcm283x_gpio_pudclk(rt_uint8_t pin, rt_uint8_t on)
{
    volatile rt_ubase_t addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPPUDCLK0 + (pin / 32) * 4;
    rt_uint8_t shift = pin % 32;
    bcm283x_peri_write(addr, (on? 1 : 0) << shift);
}

void bcm283x_gpio_set_pud(rt_uint8_t pin, rt_uint8_t pud)
{
    bcm283x_gpio_pud(pud);
    bcm283x_clo_delayMicros(10);

    bcm283x_gpio_pudclk(pin, 1);
    bcm283x_clo_delayMicros(10);

    bcm283x_gpio_pud(BCM283X_GPIO_PUD_OFF);
    bcm283x_gpio_pudclk(pin, 0);
}


void bcm283x_gpio_write(rt_uint8_t pin, rt_uint8_t val)
{
    if (val)
        bcm283x_gpio_set(pin);
    else
        bcm283x_gpio_clr(pin);
}

rt_uint64_t bcm283x_st_read(void)
{
    volatile rt_ubase_t addr;
    rt_uint32_t hi, lo;
    rt_uint64_t st;

    addr = BCM283X_ST_BASE + BCM283X_ST_CHI;
    hi = bcm283x_peri_read(addr);

    addr = BCM283X_ST_BASE + BCM283X_ST_CLO;
    lo = bcm283x_peri_read(addr);

    addr = BCM283X_ST_BASE + BCM283X_ST_CHI;
    st = bcm283x_peri_read(addr);

    /* Test for overflow */
    if (st == hi)
    {
        rt_kprintf(">> 1crash???\n");
        st <<= 32;
        st += lo;
        rt_kprintf(">> 2crash!!!\n");
    }
    else
    {
        st <<= 32;
        addr = BCM283X_ST_BASE + BCM283X_ST_CLO;
        st += bcm283x_peri_read(addr);
    }
    return st;
}

/* microseconds */
void bcm283x_delayMicroseconds(rt_uint64_t micros)
{
    rt_uint64_t start;

    start =  bcm283x_st_read();
    rt_kprintf("bcm283x_st_read result: %d\n", start);

    /* Not allowed to access timer registers (result is not as precise)*/
    if (start==0)
        return;

    bcm283x_st_delay(start, micros);
}

void bcm283x_clo_delayMicros(rt_uint32_t micros)
{
    volatile rt_uint32_t addr;
    rt_uint32_t compare;

    addr = BCM283X_ST_BASE + BCM283X_ST_CLO;
    compare = bcm283x_peri_read(addr) + micros;
    while(bcm283x_peri_read(addr) < compare);
}

void bcm283x_st_delay(rt_uint64_t offset_micros, rt_uint64_t micros)
{
    rt_uint64_t compare = offset_micros + micros;
    while(bcm283x_st_read() < compare);
}


/* Read an number of bytes from I2C */
rt_uint8_t bcm283x_i2c_read(rt_uint32_t base, rt_uint8_t* buf, rt_uint32_t len)
{
    volatile rt_uint32_t  dlen    = base + BCM283X_BSC_DLEN;
    volatile rt_uint32_t  fifo    = base + BCM283X_BSC_FIFO;
    volatile rt_uint32_t  status  = base + BCM283X_BSC_S;
    volatile rt_uint32_t  control = base + BCM283X_BSC_C;

    rt_uint32_t remaining = len;
    rt_uint32_t i = 0;
    rt_uint8_t reason = BCM283X_I2C_REASON_OK;

    /* Clear FIFO */
    bcm283x_peri_set_bits(control, BCM283X_BSC_C_CLEAR_1, BCM283X_BSC_C_CLEAR_1);
    /* Clear Status */
    bcm283x_peri_write_nb(status, BCM283X_BSC_S_CLKT | BCM283X_BSC_S_ERR | BCM283X_BSC_S_DONE);
    /* Set Data Length */
    bcm283x_peri_write_nb(dlen, len);
    /* Start read */
    bcm283x_peri_write_nb(control, BCM283X_BSC_C_I2CEN | BCM283X_BSC_C_ST | BCM283X_BSC_C_READ);

    /* wait for transfer to complete */
    while (!(bcm283x_peri_read_nb(status) & BCM283X_BSC_S_DONE))
    {
        /* we must empty the FIFO as it is populated and not use any delay */
        while (remaining && bcm283x_peri_read_nb(status) & BCM283X_BSC_S_RXD)
        {
            /* Read from FIFO, no barrier */
            buf[i] = bcm283x_peri_read_nb(fifo);
            i++;
            remaining--;
        }
    }

    /* transfer has finished - grab any remaining stuff in FIFO */
    while (remaining && (bcm283x_peri_read_nb(status) & BCM283X_BSC_S_RXD))
    {
        /* Read from FIFO, no barrier */
        buf[i] = bcm283x_peri_read_nb(fifo);
        i++;
        remaining--;
    }

    /* Received a NACK */
    if (bcm283x_peri_read(status) & BCM283X_BSC_S_ERR)
    {
        reason = BCM283X_I2C_REASON_ERROR_NACK;
    }

    /* Received Clock Stretch Timeout */
    else if (bcm283x_peri_read(status) & BCM283X_BSC_S_CLKT)
    {
        reason = BCM283X_I2C_REASON_ERROR_CLKT;
    }

    /* Not all data is received */
    else if (remaining)
    {
        reason = BCM283X_I2C_REASON_ERROR_DATA;
    }

    bcm283x_peri_set_bits(control, BCM283X_BSC_S_DONE, BCM283X_BSC_S_DONE);

    return reason;
}

int bcm283x_i2c_begin(int no)
{
    if (0 == no)
    {
        bcm283x_gpio_fsel(BCM_GPIO_PIN_0, BCM283X_GPIO_FSEL_ALT0); /* SDA */
        bcm283x_gpio_fsel(BCM_GPIO_PIN_1, BCM283X_GPIO_FSEL_ALT0); /* SCL */
    }
    else
    {
        bcm283x_gpio_fsel(BCM_GPIO_PIN_2, BCM283X_GPIO_FSEL_ALT0); /* SDA */
        bcm283x_gpio_fsel(BCM_GPIO_PIN_3, BCM283X_GPIO_FSEL_ALT0); /* SCL */
    }
    return 0;
}

void bcm283x_i2c_end(int no)
{
    if (0 == no)
    {
        bcm283x_gpio_fsel(BCM_GPIO_PIN_0, BCM283X_GPIO_FSEL_INPT); /* SDA */
        bcm283x_gpio_fsel(BCM_GPIO_PIN_1, BCM283X_GPIO_FSEL_INPT); /* SCL */
    }
    else
    {
        bcm283x_gpio_fsel(BCM_GPIO_PIN_2, BCM283X_GPIO_FSEL_INPT); /* SDA */
        bcm283x_gpio_fsel(BCM_GPIO_PIN_3, BCM283X_GPIO_FSEL_INPT); /* SCL */
    }
}

void bcm283x_i2c_setSlaveAddress(int no, rt_uint8_t saddr)
{
    volatile rt_uint32_t addr;
    if (0 == no)
        addr = PER_BASE + BCM283X_BSC0_BASE + BCM283X_BSC_A;
    else
        addr = PER_BASE + BCM283X_BSC1_BASE + BCM283X_BSC_A;

    bcm283x_peri_write(addr, saddr);
}

void bcm283x_i2c_setClockDivider(int no, rt_uint16_t divider)
{
    volatile rt_uint32_t addr;
    if (0 == no)
        addr = PER_BASE + BCM283X_BSC0_BASE + BCM283X_BSC_DIV;
    else
        addr = PER_BASE + BCM283X_BSC0_BASE + BCM283X_BSC_DIV;
    bcm283x_peri_write(addr, divider);
}

void bcm283x_i2c_set_baudrate(int no, rt_uint32_t baudrate)
{
    rt_uint32_t divider;
    divider = (BCM283X_CORE_CLK_HZ / baudrate) & 0xFFFE;
    bcm283x_i2c_setClockDivider(no, (rt_uint16_t)divider);
}

/* Writes an number of bytes to I2C */
rt_uint8_t bcm283x_i2c_write(rt_uint32_t base, const rt_uint8_t * buf, rt_uint32_t len)
{
    volatile rt_uint32_t dlen    = base + BCM283X_BSC_DLEN;
    volatile rt_uint32_t fifo    = base + BCM283X_BSC_FIFO;
    volatile rt_uint32_t status  = base + BCM283X_BSC_S;
    volatile rt_uint32_t control = base + BCM283X_BSC_C;

    rt_uint32_t remaining = len;
    rt_uint32_t i = 0;
    rt_uint8_t reason = BCM283X_I2C_REASON_OK;

    /* Clear FIFO */
    bcm283x_peri_set_bits(control, BCM283X_BSC_C_CLEAR_1, BCM283X_BSC_C_CLEAR_1);
    /* Clear Status */
    bcm283x_peri_write(status, BCM283X_BSC_S_CLKT | BCM283X_BSC_S_ERR | BCM283X_BSC_S_DONE);
    /* Set Data Length */
    bcm283x_peri_write(dlen, len);
    /* pre populate FIFO with max buffer */
    while(remaining && (i < BCM283X_BSC_FIFO_SIZE))
    {
        bcm283x_peri_write_nb(fifo, buf[i]);
        i++;
        remaining--;
    }

    /* Enable device and start transfer */
    bcm283x_peri_write(control, BCM283X_BSC_C_I2CEN | BCM283X_BSC_C_ST);

    /* Transfer is over when BCM2835_BSC_S_DONE */
    while(!(bcm283x_peri_read(status) & BCM283X_BSC_S_DONE))
    {
        while (remaining && (bcm283x_peri_read(status) & BCM283X_BSC_S_TXD))
        {
        /* Write to FIFO */
            bcm283x_peri_write(fifo, buf[i]);
            i++;
            remaining--;
        }
    }

    /* Received a NACK */
    if (bcm283x_peri_read(status) & BCM283X_BSC_S_ERR)
    {
        reason = BCM283X_I2C_REASON_ERROR_NACK;
    }

    /* Received Clock Stretch Timeout */
    else if (bcm283x_peri_read(status) & BCM283X_BSC_S_CLKT)
    {
        reason = BCM283X_I2C_REASON_ERROR_CLKT;
    }

    /* Not all data is sent */
    else if (remaining)
    {
        reason = BCM283X_I2C_REASON_ERROR_DATA;
    }

    bcm283x_peri_set_bits(control, BCM283X_BSC_S_DONE, BCM283X_BSC_S_DONE);

    return reason;
}

rt_uint8_t bcm283x_i2c_write_read_rs(char* cmds, rt_uint32_t cmds_len, char* buf, rt_uint32_t buf_len)
{
    volatile rt_uint32_t dlen    = PER_BASE + BCM283X_BSC0_BASE + BCM283X_BSC_DLEN;
    volatile rt_uint32_t fifo    = PER_BASE + BCM283X_BSC0_BASE + BCM283X_BSC_FIFO;
    volatile rt_uint32_t status  = PER_BASE + BCM283X_BSC0_BASE + BCM283X_BSC_S;
    volatile rt_uint32_t control = PER_BASE + BCM283X_BSC0_BASE + BCM283X_BSC_C;

    rt_uint32_t remaining = cmds_len;
    rt_uint32_t i = 0;
    rt_uint8_t reason = BCM283X_I2C_REASON_OK;

    /* Clear FIFO */
    bcm283x_peri_set_bits(control, BCM283X_BSC_C_CLEAR_1, BCM283X_BSC_C_CLEAR_1);

    /* Clear Status */
    bcm283x_peri_write(status, BCM283X_BSC_S_CLKT | BCM283X_BSC_S_ERR | BCM283X_BSC_S_DONE);

    /* Set Data Length */
    bcm283x_peri_write(dlen, cmds_len);

    /* pre populate FIFO with max buffer */
    while(remaining && (i < BCM283X_BSC_FIFO_SIZE))
    {
        bcm283x_peri_write_nb(fifo, cmds[i]);
        i++;
        remaining--;
    }

    /* Enable device and start transfer */
    bcm283x_peri_write(control, BCM283X_BSC_C_I2CEN | BCM283X_BSC_C_ST);

    /* poll for transfer has started (way to do repeated start, from BCM2835 datasheet) */
    while (!(bcm283x_peri_read(status) & BCM283X_BSC_S_TA))
    {
        /* Linux may cause us to miss entire transfer stage */
        if (bcm283x_peri_read_nb(status) & BCM283X_BSC_S_DONE)
            break;
    }

    remaining = buf_len;
    i = 0;

    /* Send a repeated start with read bit set in address */
    bcm283x_peri_write(dlen, buf_len);
    bcm283x_peri_write(control, BCM283X_BSC_C_I2CEN | BCM283X_BSC_C_ST  | BCM283X_BSC_C_READ);

    /* Wait for write to complete and first byte back. */
    bcm283x_clo_delayMicros(100);

    /* wait for transfer to complete */
    while (!(bcm283x_peri_read_nb(status) & BCM283X_BSC_S_DONE))
    {
        /* we must empty the FIFO as it is populated and not use any delay */
        while (remaining && bcm283x_peri_read(status) & BCM283X_BSC_S_RXD)
        {
            /* Read from FIFO, no barrier */
            buf[i] = bcm283x_peri_read_nb(fifo);
            i++;
            remaining--;
        }
    }

    /* transfer has finished - grab any remaining stuff in FIFO */
    while (remaining && (bcm283x_peri_read(status) & BCM283X_BSC_S_RXD))
    {
        /* Read from FIFO */
        buf[i] = bcm283x_peri_read(fifo);
        i++;
        remaining--;
    }

    /* Received a NACK */
    if (bcm283x_peri_read(status) & BCM283X_BSC_S_ERR)
    {
        reason = BCM283X_I2C_REASON_ERROR_NACK;
    }

    /* Received Clock Stretch Timeout */
    else if (bcm283x_peri_read(status) & BCM283X_BSC_S_CLKT)
    {
        reason = BCM283X_I2C_REASON_ERROR_CLKT;
    }

    /* Not all data is sent */
    else if (remaining)
    {
        reason = BCM283X_I2C_REASON_ERROR_DATA;
    }

    bcm283x_peri_set_bits(control, BCM283X_BSC_S_DONE, BCM283X_BSC_S_DONE);

    return reason;
}
