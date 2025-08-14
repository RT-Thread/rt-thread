/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "drv_hw_i2c.h"


#ifdef RT_USING_I2C

#define LOG_TAG              "drv.i2c"
#include <rtdbg.h>

static const struct gd32_i2c_config i2c_configs[] =
{
#ifdef BSP_USING_HW_I2C0
     {
        .i2c_periph = I2C0, .device_name = "i2c0", .periph_clk = RCU_I2C0, .i2c_clock_hz = BSP_HW_I2C0_CLOCK_SPEED,
        .scl_clk = RCU_GPIOB, .scl_port = GPIOB, .scl_pin = GPIO_PIN_6, .scl_af = GPIO_AF_1,
        .sda_clk = RCU_GPIOB, .sda_port = GPIOB, .sda_pin = GPIO_PIN_7, .sda_af = GPIO_AF_1,
        .ev_irq_type = I2C0_EV_IRQn, .er_irq_type = I2C0_ER_IRQn,
    },
#endif
#ifdef BSP_USING_HW_I2C1
    {
        .i2c_periph = I2C1, .device_name = "i2c1", .periph_clk = RCU_I2C1, .i2c_clock_hz = BSP_HW_I2C1_CLOCK_SPEED,
        .scl_clk = RCU_GPIOB, .scl_port = GPIOB, .scl_pin = GPIO_PIN_10, .scl_af = GPIO_AF_1,
        .sda_clk = RCU_GPIOB, .sda_port = GPIOB, .sda_pin = GPIO_PIN_11, .sda_af = GPIO_AF_1,
        .ev_irq_type = I2C1_EV_IRQn, .er_irq_type = I2C1_ER_IRQn,
    },
#endif
};

static struct gd32_i2c i2c_objs[sizeof(i2c_configs) / sizeof(i2c_configs[0])];

#define I2C_GD32_ERR_BERR (1U << 0)  /* Bus error */
#define I2C_GD32_ERR_LARB (1U << 1)  /* Arbitration lost */
#define I2C_GD32_ERR_AERR (1U << 2)  /* No ACK received */
#define I2C_GD32_ERR_BUSY (1U << 4)  /* I2C bus busy */
static inline void i2c_enable_interrupts(uint32_t i2c_periph)
{
    i2c_interrupt_enable(i2c_periph, I2C_INT_ERR);
    i2c_interrupt_enable(i2c_periph, I2C_INT_EV);
    i2c_interrupt_enable(i2c_periph, I2C_INT_BUF);
}

static inline void i2c_disable_interrupts(uint32_t i2c_periph)
{
    i2c_interrupt_disable(i2c_periph, I2C_INT_ERR);
    i2c_interrupt_disable(i2c_periph, I2C_INT_EV);
    i2c_interrupt_disable(i2c_periph, I2C_INT_BUF);
}

static inline void i2c_log_error(struct gd32_i2c *i2c_dev)
{
    if (i2c_dev->errs & I2C_GD32_ERR_BERR) LOG_E("[%s] Bus error", i2c_dev->config->device_name);
    if (i2c_dev->errs & I2C_GD32_ERR_LARB) LOG_E("[%s] Arbitration lost", i2c_dev->config->device_name);
    if (i2c_dev->errs & I2C_GD32_ERR_AERR) LOG_E("[%s] No ACK received", i2c_dev->config->device_name);
    if (i2c_dev->errs & I2C_GD32_ERR_BUSY) LOG_E("[%s] I2C bus is busy", i2c_dev->config->device_name);
}

static inline void gd32_i2c_xfer_read(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg = i2c_obj->config;
    rt_uint8_t read_byte;

    i2c_obj->current->len--;
    read_byte = I2C_DATA(cfg->i2c_periph);
    *i2c_obj->current->buf = read_byte;

    LOG_D("[%s] < Read byte: 0x%02X", cfg->device_name, read_byte);

    i2c_obj->current->buf++;

    if ((i2c_obj->xfer_len > 0U) && (i2c_obj->current->len == 0U))
    {
        i2c_obj->current++;
    }
}

static inline void gd32_i2c_xfer_write(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg = i2c_obj->config;

    rt_uint8_t write_byte = *i2c_obj->current->buf;
    LOG_D("[%s] > Write byte: 0x%02X", cfg->device_name, write_byte);

    i2c_obj->current->len--;
    I2C_DATA(cfg->i2c_periph) = *i2c_obj->current->buf;
    i2c_obj->current->buf++;

    if ((i2c_obj->xfer_len > 0U) && (i2c_obj->current->len == 0U))
    {
        i2c_obj->current++;
    }
}

static void gd32_i2c_handle_tbe(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg = i2c_obj->config;
    LOG_D("[%s] TBE event: xfer_len=%d", cfg->device_name, i2c_obj->xfer_len);

    if (i2c_obj->xfer_len > 0U)
    {
        i2c_obj->xfer_len--;
        if (i2c_obj->xfer_len == 0U)
        {
            LOG_D("[%s] Last byte to send, disabling BUFIE, waiting for BTC.", cfg->device_name);
            I2C_CTL1(cfg->i2c_periph) &= ~I2C_CTL1_BUFIE;
        }
        gd32_i2c_xfer_write(i2c_obj);
    }
    else
    {
        LOG_D("[%s] TBE indicates all data sent. Generating STOP.", cfg->device_name);
        I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_STOP;
        rt_completion_done(&i2c_obj->sync_sem);
    }
}

static void gd32_i2c_handle_rbne(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg = i2c_obj->config;
    LOG_D("[%s] RBNE event: xfer_len=%d", cfg->device_name, i2c_obj->xfer_len);

    switch (i2c_obj->xfer_len)
    {
    case 0:
        LOG_W("[%s] Unexpected RBNE, waking thread.", cfg->device_name);
        rt_completion_done(&i2c_obj->sync_sem);
        break;
    case 1:
        i2c_obj->xfer_len--;
        gd32_i2c_xfer_read(i2c_obj);
        LOG_D("[%s] RBNE: Last byte received, waking thread.", cfg->device_name);
        rt_completion_done(&i2c_obj->sync_sem);
        break;
    case 2:
    case 3:
        LOG_D("[%s] RBNE: %d bytes left, disabling BUFIE, waiting for BTC.", cfg->device_name, i2c_obj->xfer_len);
        I2C_CTL1(cfg->i2c_periph) &= ~I2C_CTL1_BUFIE;
        break;
    default:
        i2c_obj->xfer_len--;
        gd32_i2c_xfer_read(i2c_obj);
        break;
    }
}

static void gd32_i2c_handle_btc(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg = i2c_obj->config;
    LOG_D("[%s] BTC event: xfer_len=%d, flags=0x%X", cfg->device_name, i2c_obj->xfer_len, i2c_obj->current->flags);

    if (i2c_obj->current->flags & RT_I2C_RD)
    {
        switch (i2c_obj->xfer_len)
        {
        case 2:
            LOG_D("[%s] BTC: N=2, generating STOP.", cfg->device_name);
            I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_STOP;
            i2c_obj->xfer_len -= 2;
            gd32_i2c_xfer_read(i2c_obj);
            gd32_i2c_xfer_read(i2c_obj);
            rt_completion_done(&i2c_obj->sync_sem);
            break;
        case 3:
            LOG_D("[%s] BTC: N=3, clearing ACKEN for NACK.", cfg->device_name);
            I2C_CTL0(cfg->i2c_periph) &= ~I2C_CTL0_ACKEN;
            i2c_obj->xfer_len--;
            gd32_i2c_xfer_read(i2c_obj);
            break;
        default:
            LOG_W("[%s] Unexpected BTC in read mode, handling as RBNE.", cfg->device_name);
            gd32_i2c_handle_rbne(i2c_obj);
            break;
        }
    }
    else
    {
        LOG_D("[%s] BTC in write mode, means last byte sent.", cfg->device_name);
        gd32_i2c_handle_tbe(i2c_obj);
    }
}

static void gd32_i2c_handle_addsend(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg = i2c_obj->config;
    LOG_D("[%s] ADDSEND event: xfer_len=%d, flags=0x%X, is_restart=%d", cfg->device_name, i2c_obj->xfer_len, i2c_obj->current->flags, i2c_obj->is_restart);

    if ((i2c_obj->current->flags & RT_I2C_RD) && (i2c_obj->xfer_len <= 1U))
    {
        LOG_D("[%s] ADDSEND: N<=1 read, clearing ACKEN.", cfg->device_name);
        I2C_CTL0(cfg->i2c_periph) &= ~I2C_CTL0_ACKEN;
    }

    (void)I2C_STAT0(cfg->i2c_periph);
    (void)I2C_STAT1(cfg->i2c_periph);

    if (i2c_obj->is_restart)
    {
        i2c_obj->is_restart = RT_FALSE;
        i2c_obj->current->flags |= RT_I2C_RD;
        LOG_D("[%s] ADDSEND: 10-bit read restart. Generating RESTART.", cfg->device_name);
        I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_START;
        return;
    }

    if ((i2c_obj->current->flags & RT_I2C_RD) && (i2c_obj->xfer_len == 1U))
    {
        LOG_D("[%s] ADDSEND: N=1 read, generating STOP.", cfg->device_name);
        I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_STOP;
    }
}

static void gd32_i2c_event_handler(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg;
    uint32_t stat0;

    RT_ASSERT(i2c_obj != RT_NULL);
    cfg = i2c_obj->config;

    stat0 = I2C_STAT0(cfg->i2c_periph);
    LOG_D("[%s] EV_IRQ: STAT0=0x%08X", cfg->device_name, stat0);

    if (stat0 & I2C_STAT0_SBSEND)
    {
        uint8_t addr_byte;
        if (i2c_obj->current->flags & RT_I2C_RD)
        {
            addr_byte = (i2c_obj->addr1 << 1) | 1;
        }
        else
        {
            addr_byte = (i2c_obj->addr1 << 1) | 0;
        }
        LOG_D("[%s] SBSEND: Sending address byte 0x%02X", cfg->device_name, addr_byte);
        I2C_DATA(cfg->i2c_periph) = addr_byte;
    }
    else if (stat0 & I2C_STAT0_ADD10SEND)
    {
        LOG_D("[%s] ADD10SEND: Sending 2nd address byte 0x%02X", cfg->device_name, i2c_obj->addr2);
        I2C_DATA(cfg->i2c_periph) = i2c_obj->addr2;
    }
    else if (stat0 & I2C_STAT0_ADDSEND)
    {
        gd32_i2c_handle_addsend(i2c_obj);
    }
    else if (stat0 & I2C_STAT0_BTC)
    {
        gd32_i2c_handle_btc(i2c_obj);
    }
    else if (stat0 & I2C_STAT0_RBNE)
    {
        gd32_i2c_handle_rbne(i2c_obj);
    }
    else if (stat0 & I2C_STAT0_TBE)
    {
        gd32_i2c_handle_tbe(i2c_obj);
    }
}

void gd32_i2c_error_handler(struct gd32_i2c *i2c_obj)
{
    const struct gd32_i2c_config *cfg;
    uint32_t stat0;

    RT_ASSERT(i2c_obj != RT_NULL);
    cfg = i2c_obj->config;

    stat0 = I2C_STAT0(cfg->i2c_periph);
    LOG_E("[%s] ER_IRQ: STAT0=0x%08X", cfg->device_name, stat0);

    if (stat0 & I2C_STAT0_BERR)
    {
        I2C_STAT0(cfg->i2c_periph) &= ~I2C_STAT0_BERR;
        i2c_obj->errs |= I2C_GD32_ERR_BERR;
    }

    if (stat0 & I2C_STAT0_LOSTARB)
    {
        I2C_STAT0(cfg->i2c_periph) &= ~I2C_STAT0_LOSTARB;
        i2c_obj->errs |= I2C_GD32_ERR_LARB;
    }

    if (stat0 & I2C_STAT0_AERR)
    {
        I2C_STAT0(cfg->i2c_periph) &= ~I2C_STAT0_AERR;
        i2c_obj->errs |= I2C_GD32_ERR_AERR;
    }

    if (i2c_obj->errs != 0)
    {
        LOG_D("[%s] Error detected, sending STOP and waking thread.", cfg->device_name);
        I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_STOP;
        rt_completion_done(&i2c_obj->sync_sem);
    }
}

static rt_ssize_t gd32_i2c_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct gd32_i2c *i2c_dev;
    const struct gd32_i2c_config *cfg;
    rt_ssize_t i, itr;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);
    RT_ASSERT(num > 0);

    i2c_dev = rt_container_of(bus, struct gd32_i2c, parent);
    cfg = i2c_dev->config;

    LOG_D("[%s] master_xfer: num_msgs=%d", cfg->device_name, num);

    for (i = 0; i < num; i++)
    {
        if ((i < num - 1) && !(msgs[i].flags & RT_I2C_NO_STOP))
        {
            LOG_E("[%s] Only the last message can have a STOP signal", cfg->device_name);
            return -RT_EINVAL;
        }

        if (msgs[i].len == 0 || msgs[i].buf == RT_NULL)
        {
            LOG_E("[%s] Invalid message buffer or length at index %d", cfg->device_name, i);
            return -RT_EINVAL;
        }
    }

    rt_mutex_take(&i2c_dev->bus_mutex, RT_WAITING_FOREVER);

    I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_I2CEN;

    for (i = 0; i < num; i = itr)
    {
        LOG_D("[%s] Processing msg segment starting at index %d", cfg->device_name, i);
        i2c_dev->current = &msgs[i];
        i2c_dev->xfer_len = msgs[i].len;
        rt_uint16_t current_addr = i2c_dev->current->addr;

        for (itr = i + 1; itr < num; itr++)
        {
            if ((msgs[itr].flags & RT_I2C_RD) != (i2c_dev->current->flags & RT_I2C_RD) ||
                msgs[itr].addr != current_addr)
            {
                break;
            }
            i2c_dev->xfer_len += msgs[itr].len;
        }
        LOG_D("[%s] Merged %d msgs. Total len=%d, addr=0x%X, flags=0x%X",
              cfg->device_name, itr - i, i2c_dev->xfer_len, current_addr, i2c_dev->current->flags);

        LOG_D("[%s] Checking for bus busy...", cfg->device_name);
        if (I2C_STAT1(cfg->i2c_periph) & I2C_STAT1_I2CBSY)
        {
            LOG_E("[%s] Bus is busy!", cfg->device_name);
            i2c_dev->errs = I2C_GD32_ERR_BUSY;
            result = -RT_EBUSY;
            break;
        }

        if (i2c_dev->current->flags & RT_I2C_ADDR_10BIT)
        {
            i2c_dev->addr1 = 0xF0 | ((current_addr >> 8) & 0x03);
            i2c_dev->addr2 = current_addr & 0xFF;
            LOG_D("[%s] 10-bit address: 0x%X -> addr1=0x%X, addr2=0x%X", cfg->device_name, current_addr, i2c_dev->addr1, i2c_dev->addr2);
        }
        else
        {
            i2c_dev->addr1 = current_addr & 0x7F;
        }

        i2c_dev->errs = 0;
        i2c_dev->is_restart = RT_FALSE;
        rt_completion_init(&i2c_dev->sync_sem);

        I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_ACKEN;

        if ((i2c_dev->current->flags & RT_I2C_RD) && (i2c_dev->current->flags & RT_I2C_ADDR_10BIT))
        {
            LOG_D("[%s] Preparing for 10-bit read restart.", cfg->device_name);
            i2c_dev->is_restart = RT_TRUE;
            i2c_dev->current->flags &= ~RT_I2C_RD;
        }

        if ((i2c_dev->current->flags & RT_I2C_RD) && (i2c_dev->xfer_len == 2))
        {
            LOG_D("[%s] N=2 read, setting POAP.", cfg->device_name);
            I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_POAP;
        }

        LOG_D("[%s] Generating START, enabling IRQs, waiting for completion...", cfg->device_name);
        i2c_enable_interrupts(cfg->i2c_periph);
        I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_START;

        result = rt_completion_wait(&i2c_dev->sync_sem, bus->timeout);

        if (i2c_dev->is_restart == RT_TRUE)
        {
            i2c_dev->current->flags |= RT_I2C_RD;
        }

        I2C_CTL0(cfg->i2c_periph) &= ~I2C_CTL0_POAP;
        i2c_disable_interrupts(cfg->i2c_periph);

        if (result != RT_EOK)
        {
            LOG_E("[%s] I2C transaction timeout!", cfg->device_name);
            result = -RT_ETIMEOUT;
            I2C_CTL0(cfg->i2c_periph) |= I2C_CTL0_STOP;
            break;
        }

        if (i2c_dev->errs != 0)
        {
            LOG_E("[%s] Hardware error detected by ISR.", cfg->device_name);
            i2c_log_error(i2c_dev);
            result = -RT_EIO;
            break;
        }
        LOG_D("[%s] Transaction segment completed successfully.", cfg->device_name);
    }

    if (result == RT_EOK)
    {
        if (!(msgs[num - 1].flags & RT_I2C_NO_STOP))
        {
            LOG_D("[%s] Last message, Waiting STOP.", cfg->device_name);
            rt_uint32_t timeout = 1000;
            while (I2C_STAT1(cfg->i2c_periph) & I2C_STAT1_I2CBSY && timeout--)
            {
                rt_hw_us_delay(1);
            }
        }
        else
        {
            LOG_D("[%s] Last message has NO_STOP flag, leaving bus active.", cfg->device_name);
        }
    }

    I2C_CTL0(cfg->i2c_periph) &= ~I2C_CTL0_I2CEN;

    rt_mutex_release(&i2c_dev->bus_mutex);

    LOG_D("[%s] master_xfer exiting with code: %d", cfg->device_name, (result == RT_EOK) ? i : result);
    if (result == RT_EOK)
    {
        return i;
    }
    else
    {
        return result;
    }
}


static struct gd32_i2c *_get_i2c_obj(uint32_t i2c_periph)
{
    for (size_t i = 0; i < sizeof(i2c_objs) / sizeof(i2c_objs[0]); i++)
    {
        if (i2c_objs[i].config->i2c_periph == i2c_periph)
        {
            return &i2c_objs[i];
        }
    }
    /* Should not happen in a correctly configured system. */
    LOG_E("Cannot find i2c_obj for periph: 0x%08X", i2c_periph);
    return RT_NULL;
}

#ifdef BSP_USING_HW_I2C0
void I2C0_EV_IRQHandler(void)
{
    rt_interrupt_enter();

    struct gd32_i2c *i2c_obj = _get_i2c_obj(I2C0);
    if (i2c_obj)
    {
        gd32_i2c_event_handler(i2c_obj);
    }

    rt_interrupt_leave();
}

void I2C0_ER_IRQHandler(void)
{
    rt_interrupt_enter();

    struct gd32_i2c *i2c_obj = _get_i2c_obj(I2C0);
    if (i2c_obj)
    {
        gd32_i2c_error_handler(i2c_obj);
    }

    rt_interrupt_leave();
}
#endif


#ifdef BSP_USING_HW_I2C1
void I2C1_EV_IRQHandler(void)
{
    rt_interrupt_enter();

    struct gd32_i2c *i2c_obj = _get_i2c_obj(I2C1);
    if (i2c_obj)
    {
        gd32_i2c_event_handler(i2c_obj);
    }

    rt_interrupt_leave();
}

void I2C1_ER_IRQHandler(void)
{
    rt_interrupt_enter();

    struct gd32_i2c *i2c_obj = _get_i2c_obj(I2C1);
    if (i2c_obj)
    {
        gd32_i2c_error_handler(i2c_obj);
    }

    rt_interrupt_leave();
}
#endif


static const struct rt_i2c_bus_device_ops gd32_i2c_ops =
{
    .master_xfer = gd32_i2c_master_xfer,
    .slave_xfer  = RT_NULL,
    .i2c_bus_control = RT_NULL,
};

int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_objs) / sizeof(struct gd32_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        const struct gd32_i2c_config *config = &i2c_configs[i];
        struct gd32_i2c *i2c_obj = &i2c_objs[i];

        LOG_D("Initializing %s...", config->device_name);

        i2c_obj->config = config;
        i2c_obj->parent.ops = &gd32_i2c_ops;
        i2c_obj->parent.timeout = RT_TICK_PER_SECOND;

        rcu_periph_clock_enable(config->scl_clk);
        if (config->scl_clk != config->sda_clk)
        {
            rcu_periph_clock_enable(config->sda_clk);
        }
        rcu_periph_clock_enable(config->periph_clk);

        gpio_af_set(config->scl_port, config->scl_af, config->scl_pin);
        gpio_mode_set(config->scl_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config->scl_pin);
        gpio_output_options_set(config->scl_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, config->scl_pin);

        gpio_af_set(config->sda_port, config->sda_af, config->sda_pin);
        gpio_mode_set(config->sda_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config->sda_pin);
        gpio_output_options_set(config->sda_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, config->sda_pin);

        i2c_deinit(config->i2c_periph);
        i2c_clock_config(config->i2c_periph, config->i2c_clock_hz, I2C_DTCY_2);
        i2c_mode_addr_config(config->i2c_periph, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0);
        i2c_enable(config->i2c_periph);
        i2c_ack_config(config->i2c_periph, I2C_ACK_ENABLE);

        nvic_irq_enable(config->ev_irq_type, 2);
        nvic_irq_enable(config->er_irq_type, 1);

        result = rt_i2c_bus_device_register(&i2c_obj->parent, config->device_name);
        if (result != RT_EOK)
        {
            LOG_E("Failed to register i2c bus %s", config->device_name);
            return result;
        }

        rt_mutex_init(&i2c_obj->bus_mutex,
                  config->device_name,
                  RT_IPC_FLAG_FIFO);

        rt_completion_init(&i2c_obj->sync_sem);

        LOG_I("I2C bus %s registered successfully.", config->device_name);
    }
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */

