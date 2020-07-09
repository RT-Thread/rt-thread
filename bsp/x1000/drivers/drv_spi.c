/*
 * File      : board_spi_master.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

/*********************************************************************************************************
**   Include Files
*********************************************************************************************************/
#include <rthw.h>
#include <rtthread.h>

#include <rtdevice.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_gpio.h"
#include "drv_spi.h"

#define SSI_BASE    SSI0_BASE

#define DEBUG   0
#if DEBUG
#define PRINT(...)     rt_kprintf(__VA_ARGS__)
#else
#define PRINT(...)
#endif


#define JZ_SPI_RX_BUF(type)                     \
uint32_t jz_spi_rx_buf_##type(struct jz_spi *hw)     \
{                                                \
    uint32_t data  = spi_readl(hw, SSI_DR);           \
    type * rx = (type *)hw->rx_buf;                  \
    *rx++ = (type)(data);                        \
    hw->rx_buf = (uint8_t *)rx;                          \
    return (uint32_t)data;                           \
}

#define JZ_SPI_TX_BUF(type)                     \
uint32_t jz_spi_tx_buf_##type(struct jz_spi *hw)     \
{                                               \
    uint32_t data;                                   \
    const type * tx = (type *)hw->tx_buf;           \
    data = *tx++;                               \
    hw->tx_buf = (uint8_t *)tx;                          \
    spi_send_data(hw, data);                    \
    return (uint32_t)data;                           \
}

JZ_SPI_RX_BUF(u8)
JZ_SPI_TX_BUF(u8)

JZ_SPI_RX_BUF(u16)
JZ_SPI_TX_BUF(u16)

JZ_SPI_RX_BUF(u32)
JZ_SPI_TX_BUF(u32)



static rt_err_t     jz_spi_configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t  jz_spi_xfer(struct rt_spi_device* device, struct rt_spi_message* message);



static const struct rt_spi_ops jz_spi_ops =
{
    jz_spi_configure,
    jz_spi_xfer
};

static struct jz_spi jz_spi0 =
{
     .base = SSI0_BASE,
};

static void jz_spi_set_cs(struct jz_spi_cs *cs,int value)
{
//    gpio_set_value(cs->port,cs->pin,!!value);
	if(value != 0)
		gpio_set_func(cs->port,cs->pin,GPIO_OUTPUT1);
	else
		gpio_set_func(cs->port,cs->pin,GPIO_OUTPUT0);
}

/*************************************************************
 * jz_spi_set_clk: set the SPI_CLK.
 * The min clock is 23438Hz, and the max clock is defined
 * by max_clk or max_speed_hz(it is 54MHz for JZ4780, and
 * the test max clock is 30MHz).
 ************************************************************* */
static int _spi_set_clk(struct jz_spi *spi_bus, uint32_t hz)
{
    uint16_t cgv;
    uint32_t cpm_rate;

    cpm_rate = clk_get_rate(spi_bus->clk);

    if (hz >= 10000000)
        clk_set_rate(spi_bus->clk,2 * hz);
    else
        clk_set_rate(spi_bus->clk, 24000000);

    cpm_rate =  clk_get_rate(spi_bus->clk);

    cgv = cpm_rate / (2 * hz);
    if (cgv > 0)
        cgv -= 1;

    spi_writel(spi_bus, SSI_GR, cgv);

    return 0;
}

static uint32_t _spi_get_clk(struct jz_spi *spi_bus)
{
    uint16_t cgv;

    cgv = spi_readl(spi_bus, SSI_GR);

    return clk_get_rate(spi_bus->clk) / (2 * (cgv + 1));
}

static uint32_t _spi_do_write_fifo(struct jz_spi* spi_bus,uint32_t sendEntries)
{
    uint32_t    cnt = 0;

    if((spi_bus->tx_buf != RT_NULL) && (spi_bus->tx_func != RT_NULL))
    {
        while (cnt++ < sendEntries)
        {
            spi_bus->tx_func(spi_bus);

            spi_bus->sendCount += spi_bus->xfer_unit_size;
        }
    }
    else
    {
        while (cnt++ < sendEntries)
        {
            spi_send_data(spi_bus,0xFF);

            spi_bus->sendCount += spi_bus->xfer_unit_size;
        }
    }

//    PRINT("sendCount = %d\n",spi_bus->sendCount);

    return 0;
}


static uint32_t _spi_do_read_fifo(struct jz_spi* spi_bus)
{
    uint32_t cnt = 0;
    uint32_t    dummy;

    if((spi_bus->rx_buf != RT_NULL) && (spi_bus->rx_func != RT_NULL))
    {
        while(!spi_is_rxfifo_empty(spi_bus))
        {
        	spi_bus->rx_func(spi_bus);
            spi_bus->recvCount += spi_bus->xfer_unit_size;
            cnt ++;
        }
    }
    else
    {
        while(!spi_is_rxfifo_empty(spi_bus))
        {
            dummy = spi_readl(spi_bus, SSI_DR);
            cnt ++;
        }
    }

    PRINT("recvCnt = %d\n",cnt);
    return cnt;
}


static uint32_t _spi_do_xfer(struct jz_spi* spi_bus)
{
    uint32_t    leaveEntries;
    uint32_t    sendEntries;
    uint32_t    trigger;
    uint8_t     intFlag = 0, lastFlag = 0;

    leaveEntries = (spi_bus->totalCount - spi_bus->sendCount) / spi_bus->xfer_unit_size;

    if(spi_bus->is_first == 1)
    {
        /* CPU Mode should reset SSI triggers at first */
        spi_bus->tx_trigger = SSI_TX_FIFO_THRESHOLD * 8;
        spi_bus->rx_trigger = (SSI_RX_FIFO_THRESHOLD - SSI_SAFE_THRESHOLD) * 8;

        spi_set_tx_trigger(spi_bus, spi_bus->tx_trigger);
        spi_set_rx_trigger(spi_bus, spi_bus->rx_trigger);

        if(leaveEntries <= JZ_SSI_MAX_FIFO_ENTRIES)
        {
            sendEntries = leaveEntries;
        }
        else
        {
            sendEntries = JZ_SSI_MAX_FIFO_ENTRIES;

            intFlag = 1;
        }

        spi_start_transmit(spi_bus);
        spi_bus->is_first = 0;
    }
    else
    {
        trigger = JZ_SSI_MAX_FIFO_ENTRIES - spi_bus->tx_trigger;

        if (leaveEntries <= trigger)
        {
            sendEntries = leaveEntries;

            lastFlag = 1;
        }
        else
        {
            sendEntries = CPU_ONCE_BLOCK_ENTRIES;
            intFlag = 1;
        }
    }

    _spi_do_write_fifo(spi_bus,sendEntries);

    spi_enable_tx_error_intr(spi_bus);
    spi_enable_rx_error_intr(spi_bus);

    if(intFlag)
    {
        spi_enable_txfifo_half_empty_intr(spi_bus);
        spi_enable_rxfifo_half_full_intr(spi_bus);
    }
    else
    {
        spi_disable_txfifo_half_empty_intr(spi_bus);
        spi_disable_rxfifo_half_full_intr(spi_bus);
    }

    if(lastFlag)
        spi_enable_rxfifo_half_full_intr(spi_bus);

    return 0;
}


static void _spi_irq_handler(int vector, void *param)
{
    struct jz_spi* spi_bus = (struct jz_spi *) param;
    uint32_t    leftCount = spi_bus->totalCount - spi_bus->sendCount;
    uint32_t    status;
    uint8_t     flag = 0;

    PRINT("INT\n");

    if ( spi_get_underrun(spi_bus) && spi_get_tx_error_intr(spi_bus))
    {
        PRINT("UNDR\n");
        spi_disable_tx_error_intr(spi_bus);

        if(leftCount == 0)
        {
            _spi_do_read_fifo(spi_bus);

            spi_disable_tx_intr(spi_bus);
            spi_disable_rx_intr(spi_bus);

            rt_completion_done(&spi_bus->completion);
        }
        else
        {
            spi_clear_errors(spi_bus);
            spi_enable_tx_error_intr(spi_bus);
        }

        flag++;
    }

    if ( spi_get_overrun(spi_bus) && spi_get_rx_error_intr(spi_bus) )
    {
        PRINT("OVER\n");
        _spi_do_read_fifo(spi_bus);

        flag++;
    }

    if ( spi_get_rxfifo_half_full(spi_bus) && spi_get_rxfifo_half_full_intr(spi_bus))
    {
        PRINT("RFHF\n");
        _spi_do_read_fifo(spi_bus);

        flag++;
    }

    if ( spi_get_txfifo_half_empty(spi_bus) && spi_get_txfifo_half_empty_intr(spi_bus))
    {
        PRINT("THFE\n");
        _spi_do_xfer(spi_bus);

        flag++;
    }

//    if (!flag)
//    {
//        rt_completion_done(&spi_bus->completion);
//    }

    spi_clear_errors(spi_bus);
}


static rt_uint32_t  jz_spi_xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    rt_base_t   level;
    int i;

    struct jz_spi* spi_bus = (struct jz_spi *)device->bus;
    struct jz_spi_cs* _spi_cs = (struct jz_spi_cs*)device->parent.user_data;

    /* take CS */
    if (message->cs_take)
    {
        jz_spi_set_cs(_spi_cs,0);
    }

    spi_disable_tx_intr(spi_bus);
    spi_disable_rx_intr(spi_bus);
    spi_start_transmit(spi_bus);
    spi_flush_fifo(spi_bus);
    spi_enable_receive(spi_bus);
    spi_clear_errors(spi_bus);

#ifdef SSI_DEGUG
    dump_spi_reg(hw);
#endif

    spi_bus->is_first   = 1;
    spi_bus->totalCount = message->length;
    spi_bus->sendCount  = 0;
    spi_bus->recvCount  = 0;

    spi_bus->rx_buf = (rt_uint8_t *)message->recv_buf;
    spi_bus->tx_buf = (rt_uint8_t *)message->send_buf;

    _spi_do_xfer(spi_bus);

    rt_completion_wait(&spi_bus->completion,RT_WAITING_FOREVER);

    spi_finish_transmit(spi_bus);
    spi_clear_errors(spi_bus);

    /* release CS */
    if (message->cs_release)
    {
        jz_spi_set_cs(_spi_cs,1);
        spi_finish_transmit(spi_bus);
    }

    return message->length;
}


static rt_err_t jz_spi_configure(struct rt_spi_device* device,
                                    struct rt_spi_configuration* configuration)
{
    struct jz_spi * spi_bus = (struct jz_spi *)device->bus;

    /* Disable SSIE */
    spi_disable(spi_bus);

    _spi_set_clk(spi_bus,configuration->max_hz);
    configuration->max_hz = _spi_get_clk(spi_bus);
    PRINT("spi clk = %d\n",configuration->max_hz);

    if(configuration->data_width <= 8)
    {
        spi_set_frame_length(spi_bus, FIFO_W8);

        spi_bus->xfer_unit_size = SPI_8BITS;
        spi_bus->rx_func = jz_spi_rx_buf_u8;
        spi_bus->tx_func = jz_spi_tx_buf_u8;
    }
    else if(configuration->data_width <= 16)
    {
        spi_set_frame_length(spi_bus, FIFO_W16);

        spi_bus->xfer_unit_size = SPI_16BITS;
        spi_bus->rx_func = jz_spi_rx_buf_u16;
        spi_bus->tx_func = jz_spi_tx_buf_u16;
    }
    else if(configuration->data_width <= 32)
    {
        spi_set_frame_length(spi_bus, FIFO_W32);

        spi_bus->xfer_unit_size = SPI_32BITS;
        spi_bus->rx_func = jz_spi_rx_buf_u32;
        spi_bus->tx_func = jz_spi_tx_buf_u32;
    }
    else
    {
        return RT_EIO;
    }
//    spi_set_frame_length(spi_bus,spi_bus->xfer_unit_size);

    /* CPOL */
    if (configuration->mode & RT_SPI_CPHA)
        spi_set_clock_phase(spi_bus, 1);
    else
        spi_set_clock_phase(spi_bus, 0);
    /* CPHA */
    if (configuration->mode & RT_SPI_CPOL)
        spi_set_clock_polarity(spi_bus, 1);
    else
        spi_set_clock_polarity(spi_bus, 0);

    /* MSB or LSB */
    if (configuration->mode & RT_SPI_MSB)
    {
        spi_set_tx_msb(spi_bus);
        spi_set_rx_msb(spi_bus);
    }
    else
    {
        spi_set_tx_lsb(spi_bus);
        spi_set_rx_lsb(spi_bus);
    }
    /* Enable SSIE */
    spi_enable(spi_bus);

    return RT_EOK;
};



int rt_hw_spi_master_init(void)
{
    PRINT("init spi bus spi0\n");

#ifdef RT_USING_SPI0
#	ifdef RT_SPI0_USE_PA
    /* GPIO Initialize (SSI FUNC2) */
//    gpio_set_func(GPIO_PORT_A,GPIO_Pin_25,GPIO_FUNC_2);	//CE0
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_26,GPIO_FUNC_2);		//CLK
//    gpio_set_func(GPIO_PORT_A,GPIO_Pin_27,GPIO_FUNC_2);	//CE0
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_28,GPIO_FUNC_2);		//DR
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_29,GPIO_FUNC_2);		//DT

    /* Release HOLD WP */
    gpio_set_func(GPIO_PORT_A, GPIO_Pin_30, GPIO_OUTPUT1);	//CE1->WP
    gpio_set_func(GPIO_PORT_A, GPIO_Pin_31, GPIO_OUTPUT1);	//GPC->HOLD
#	else
    /* GPIO Initialize (SSI FUNC2) */
//    gpio_set_func(GPIO_PORT_D,GPIO_Pin_1,GPIO_FUNC_0);	//CE0
    gpio_set_func(GPIO_PORT_D,GPIO_Pin_0,GPIO_FUNC_0);		//CLK
    gpio_set_func(GPIO_PORT_D,GPIO_Pin_3,GPIO_FUNC_0);		//DR
    gpio_set_func(GPIO_PORT_D,GPIO_Pin_2,GPIO_FUNC_0);		//DT
#	endif
#endif

    /* Init config param */
    jz_spi0.base = SSI_BASE;

    jz_spi0.clk     = clk_get("cgu_ssi");
    clk_enable(jz_spi0.clk);
    jz_spi0.clk_gate = clk_get("ssi0");
    clk_enable(jz_spi0.clk_gate);


    rt_completion_init(&jz_spi0.completion);


    /* disable the SSI controller */
    spi_disable(&jz_spi0);

    /* set default half_intr trigger */
    jz_spi0.tx_trigger = SSI_TX_FIFO_THRESHOLD * 8;
    jz_spi0.rx_trigger = SSI_RX_FIFO_THRESHOLD * 8;
    spi_set_tx_trigger(&jz_spi0, jz_spi0.tx_trigger);
    spi_set_rx_trigger(&jz_spi0, jz_spi0.rx_trigger);

    /* First,mask the interrupt, while verify the status ? */
    spi_disable_tx_intr(&jz_spi0);
    spi_disable_rx_intr(&jz_spi0);

    spi_disable_receive(&jz_spi0);

    spi_set_clock_phase(&jz_spi0, 0);
    spi_set_clock_polarity(&jz_spi0, 0);
    spi_set_tx_msb(&jz_spi0);
    spi_set_rx_msb(&jz_spi0);

    spi_set_format(&jz_spi0);
    spi_set_frame_length(&jz_spi0, 8);
    spi_disable_loopback(&jz_spi0);
    spi_flush_fifo(&jz_spi0);

    spi_underrun_auto_clear(&jz_spi0);
    spi_clear_errors(&jz_spi0);

    spi_select_ce0(&jz_spi0);
    /* enable the SSI controller */
    spi_enable(&jz_spi0);

    rt_spi_bus_register(&jz_spi0.parent,"spi0", &jz_spi_ops);
    PRINT("init spi bus spi0 done\n");

    rt_hw_interrupt_install(IRQ_SSI0,_spi_irq_handler,&jz_spi0,"SSI0");
    rt_hw_interrupt_umask(IRQ_SSI0);

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_spi_master_init);
