/*
 * File      : drv_i2s.c
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

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/audio.h>

#include "dma.h"


#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "board.h"
#include "drv_clock.h"
#include "drv_dma.h"
#include "drv_gpio.h"
#include "drv_aic.h"
#include "drv_aic_i2s.h"

#define AIC_DEBUG   0
#if AIC_DEBUG
#define AIC_DBG(...)     rt_kprintf("[AIC]"),rt_kprintf(__VA_ARGS__)
#else
#define AIC_DBG(...)
#endif

static struct jz_aic _g_jz_aic;

int aic_set_rate(struct jz_aic *aic, uint32_t freq)
{
    int ret;
//    clk_disable(aic->clk);

    if (aic->clk_rate != freq)
    {
        ret = clk_set_rate(aic->clk, freq);
        if (!ret)
            aic->clk_rate = clk_get_rate(aic->clk);

    }

//    clk_enable(aic->clk);

    AIC_DBG("aic clock = %d\n",clk_get_rate(aic->clk));
    return aic->clk_rate;
}

static void aic_irq_handler(int vector, void *param)
{
    struct jz_aic *aic = (struct jz_aic *)param;

    aic->mask = __aic_get_irq_enmask(aic);

    if (aic->mask && (aic->mask & __aic_get_irq_flag(aic)))
    {
        /*Disable all aic interrupt*/
        __aic_set_irq_enmask(aic, 0);

        if ((aic->mask & 0x8) && __aic_test_ror(aic))
        {
            aic->ror++;
            AIC_DBG("recieve fifo [overrun] interrupt time [%d]\n",
                            aic->ror);
        }

        if ((aic->mask & 0x4) && __aic_test_tur(aic))
        {
            aic->tur++;
            AIC_DBG("transmit fifo [underrun] interrupt time [%d]\n",
                            aic->tur);
        }

        if ((aic->mask & 0x2) && __aic_test_rfs(aic))
        {
            AIC_DBG("[recieve] fifo at or above threshold interrupt time\n");
        }

        if ((aic->mask & 0x1) && __aic_test_tfs(aic))
        {
            AIC_DBG("[transmit] fifo at or blow threshold interrupt time\n");
        }

        /*sleep, avoid frequently interrupt*/
        __aic_clear_all_irq_flag(aic);
        __aic_set_irq_enmask(aic, aic->mask);
    }
}

struct jz_aic* _aic_init(void)
{
    struct jz_aic       *aic = &_g_jz_aic;
    struct rt_device    *device;


    aic->base = AIC_BASE;

    aic->clk_gate   = clk_get("aic");
    aic->clk        = clk_get("cgu_i2s");
    if((aic->clk_gate == RT_NULL) || (aic->clk == RT_NULL))
    {
        AIC_DBG("aic or i2s clk error\n");

        goto aic_init_error;
    }
    /* set system clock */
    clk_set_rate(aic->clk, 24000000);
    aic->clk_rate = 24000000;

    clk_enable(aic->clk_gate);
    clk_enable(aic->clk);
    aic->irqno      = IRQ_AIC0;
    aic->irqflags   =  0;

    rt_hw_interrupt_install(IRQ_AIC0,aic_irq_handler,aic,"irq_aic");
    rt_hw_interrupt_umask(IRQ_AIC0);

    return aic;

aic_init_error:
    clk_put(aic->clk);
    clk_put(aic->clk_gate);
    return RT_NULL;
}

#define I2S_DEBUG   0
#if I2S_DEBUG
#define I2S_DBG(...)     rt_kprintf("[I2S]"),rt_kprintf(__VA_ARGS__)
#else
#define I2S_DBG(...)
#endif

#define I2S_TFIFO_DEPTH     64
#define I2S_RFIFO_DEPTH     32

#define I2S_OSS_FMT         16
#define I2S_ISS_FMT         16

#define I2S_PALY_CHANEL     2

struct jz_i2s   _g_jz_i2s =
{
    .aic        = 0,
    .i2s_init   = 0,
    .i2s_mode   = 0,
    .tx_dr_base = ((AIC_BASE + AICDR) & 0x1FFFFFFF),
	.channels	= 2,
	.fmt_width	= 16,
    .tx_dmac    = RT_NULL,
    .rx_dmac    = RT_NULL,
};

#define I2S_DMA_TX_CHAN     2
#define I2S_DMA_RX_CHAN     3

static void aic_i2s_trans_complete(struct rt_dma_channel *dmac, struct dma_message *msg);

static void dump_registers(struct jz_aic *aic)
{
    rt_kprintf("AIC_FR     0x%08x : 0x%08x\n",     (aic->base+AICFR),  jz_aic_read_reg(aic, AICFR));
    rt_kprintf("AIC_CR     0x%08x : 0x%08x\n",     (aic->base+AICCR),  jz_aic_read_reg(aic, AICCR));
    rt_kprintf("AIC_I2SCR  0x%08x : 0x%08x\n",     (aic->base+I2SCR),  jz_aic_read_reg(aic, I2SCR));
    rt_kprintf("AIC_SR     0x%08x : 0x%08x\n",     (aic->base+AICSR),  jz_aic_read_reg(aic, AICSR));
    rt_kprintf("AIC_I2SSR  0x%08x : 0x%08x\n",     (aic->base+I2SSR),  jz_aic_read_reg(aic, I2SSR));
    rt_kprintf("AIC_I2SDIV 0x%08x : 0x%08x\n",     (aic->base+I2SDIV), jz_aic_read_reg(aic, I2SDIV));
    rt_kprintf("AIC_DR     0x%08x : 0x%08x\n",     (aic->base+AICDR),  jz_aic_read_reg(aic, AICDR));

    rt_kprintf("AIC_I2SCDR\t 0x%08x\n",*(volatile unsigned int*)0xb0000060);
    rt_kprintf("AIC_I2SCDR1\t 0x%08x\n",*(volatile unsigned int*)0xb0000070);
    rt_kprintf("AICSR\t 0x%08x\n",*(volatile unsigned int*)0xb0020014);
    return;
}

int dump_aic_i2s(void)
{
	dump_registers(_g_jz_i2s.aic);

	return 0;
}
MSH_CMD_EXPORT(dump_aic_i2s,dump i2s registers...);

#if 0
int i2scdr_extclk(void)
{
	rt_uint32_t regValue;

	regValue = readl(0xb0000060);
	regValue &= ~(0x01 << 30);
	writel(regValue,0xb0000060);

    rt_kprintf("AIC_I2SCDR\t 0x%08x\n",*(volatile unsigned int*)0xb0000060);
}
MSH_CMD_EXPORT(i2scdr_extclk,set i2s cdr ext clk...);

int i2scdr_pllclk(void)
{
	rt_uint32_t regValue;

	regValue = readl(0xb0000060);
	regValue |= (0x01 << 30);
	writel(regValue,0xb0000060);

    rt_kprintf("AIC_I2SCDR\t 0x%08x\n",*(volatile unsigned int*)0xb0000060);
}
MSH_CMD_EXPORT(i2scdr_pllclk,set i2s cdr pll clk...);
#endif

static void aic_i2s_start_substream(struct jz_i2s *i2s,int stream)
{
	struct jz_aic *aic = i2s->aic;

	if(stream == AUDIO_STREAM_REPLAY)
	{
		int i = 4;
		I2S_DBG("codec fifo level0 %x\n", jz_aic_read_reg(aic, AICSR));
		for (i= 0; i < I2S_TFIFO_DEPTH ; i++)
		{
			__aic_write_txfifo(aic, 0x0);
			__aic_write_txfifo(aic, 0x0);
		}

		__aic_clear_tur(aic);
		I2S_DBG("codec fifo level1 %x\n", jz_aic_read_reg(aic, AICSR));
		__i2s_enable_replay(aic);

		while (!__aic_test_tur(aic)) ;
		__i2s_enable_transmit_dma(aic);
		__aic_clear_tur(aic);
#if I2S_DEBUG
		__aic_en_tur_int(aic);
#endif
	}
	else
	{
		__aic_flush_rxfifo(aic);
		rt_thread_delay(1);
		__i2s_enable_record(aic);
		__i2s_enable_receive_dma(aic);

#if I2S_DEBUG
		__aic_en_ror_int(aic);
#endif
	}

	I2S_DBG("strtup sub stream ok!\n");
}

static void aic_i2s_stop_substream(struct jz_i2s *i2s,int stream)
{
	struct jz_aic *aic = i2s->aic;

	if(stream == AUDIO_STREAM_REPLAY)
	{
#if I2S_DEBUG
		__aic_dis_tur_int(aic);
#endif
		if (__i2s_transmit_dma_is_enable(aic))
		{
			//wait all dma queue is complete
			while(i2s->tx_dmac->get_index != i2s->tx_dmac->put_index)
				rt_thread_delay(1);

			__i2s_disable_transmit_dma(aic);
			__aic_clear_tur(aic);
			/*hrtime mode: stop will be happen in any where, make sure there is
			 *	no data transfer on ahb bus before stop dma
			 */
			while(!__aic_test_tur(aic));
		}
		__i2s_disable_replay(aic);
		__aic_clear_tur(aic);
	}
	else
	{
//		if (jz_i2s_debug) __aic_dis_ror_int(aic);

		if (__i2s_receive_dma_is_enable(aic))
		{
			__i2s_disable_receive_dma(aic);
			__aic_clear_ror(aic);
			while(!__aic_test_ror(aic));
		}
		__i2s_disable_record(aic);
		__aic_clear_ror(aic);
	}
}

int aic_i2s_set_clkdiv(struct jz_i2s *i2s,int div_id, int div)
{
    struct jz_aic *aic = i2s->aic;

    I2S_DBG("enter %s div_id %d div %d\n", __func__, div_id , div);

    /*BIT CLK fix 64FS*/
    /*SYS_CLK is 256, 384, 512, 768*/
    if (div != 256 && div != 384 && div != 512 && div != 768)
        return -RT_EIO;

	__i2s_set_dv(aic, (div/64) - 1);
	__i2s_set_idv(aic, (div/64) - 1);

    return RT_EOK;
}


/*
 * stream = CODEC_STREAM_PLAYBACK or CODEC_STREAM_CAPTURE
 */
int aic_i2s_startup(struct jz_i2s *i2s,int stream)
{
	struct jz_aic   *aic = i2s->aic;

	if(!i2s->i2s_mode)
	{
		I2S_DBG("start set AIC register....\n");
	    __aic_disable(aic);

		__aic_select_i2s(aic);
		__i2s_select_i2s_fmt(aic);

#ifndef CODEC_AS_MASTER
		__i2s_bclk_output(aic);
		__i2s_sync_output(aic);
#else
		__i2s_bclk_input(aic);
		__i2s_sync_input(aic);
#endif

		aic_i2s_set_sysclk(i2s,CODEC_DEF_RATE);

		__i2s_play_lastsample(aic);
		__i2s_set_transmit_trigger(aic, I2S_TFIFO_DEPTH/4);
		__i2s_set_receive_trigger(aic, (I2S_RFIFO_DEPTH/4 - 1));
		__aic_enable(aic);

	}

	/* Set playback or record mode */
	if(stream == AUDIO_STREAM_REPLAY)
	{
		__i2s_send_rfirst(aic);
		__i2s_disable_transmit_dma(aic);
		__i2s_disable_replay(aic);
		__aic_clear_tur(aic);
		i2s->i2s_mode |= I2S_WRITE;
	}
	else
	{
		__i2s_disable_receive_dma(aic);
		__i2s_disable_record(aic);
		__aic_clear_ror(aic);
		i2s->i2s_mode |= I2S_READ;
	}

	return 0;
}

int aic_i2s_trigger(struct jz_i2s* i2s,int cmd,int stream)
{
	switch (cmd)
	{
		case I2S_TRIGGER_START:
		case I2S_TRIGGER_RESUME:
		case I2S_TRIGGER_PAUSE_RELEASE:
			aic_i2s_start_substream(i2s,stream);
			break;
		case I2S_TRIGGER_STOP:
		case I2S_TRIGGER_SUSPEND:
		case I2S_TRIGGER_PAUSE_PUSH:
		default:
			aic_i2s_stop_substream(i2s,stream);
			break;
	}

	return 0;
}

int aic_i2s_hw_params(struct jz_i2s* i2s,int stream)
{
	struct jz_aic   *aic = i2s->aic;
    struct dma_config       config;

    int trigger;
	int bus_width;

	I2S_DBG("upgrade hw params...\n");

	if(stream == AUDIO_STREAM_REPLAY)
	{
		/* channel */
		__i2s_channel(aic, i2s->channels);

		/* format */
		if(i2s->fmt_width == 8)
			bus_width = RT_DMA_BUSWIDTH_1_BYTE;
		else if(i2s->fmt_width == 16)
			bus_width = RT_DMA_BUSWIDTH_2_BYTES;
		else
			bus_width = RT_DMA_BUSWIDTH_4_BYTES;

        i2s->tx_dmac = rt_dma_get_channel(I2S_DMA_TX_CHAN);
        RT_ASSERT(i2s->tx_dmac != RT_NULL);
        if(i2s->tx_dmac != RT_NULL)
        {
            config.direction        = RT_DMA_MEM_TO_DEV;
            config.src_addr_width   = bus_width;
            config.src_maxburst     = (64 * 1024);
            config.dst_addr_width   = bus_width;
            config.dst_maxburst     = (I2S_TFIFO_DEPTH * bus_width)/2;
            rt_dma_configture(i2s->tx_dmac,&config);

            i2s->tx_dmac->start = RT_NULL;
            i2s->tx_dmac->complete = aic_i2s_trans_complete;
        }

		__i2s_set_oss(aic, i2s->fmt_width);
		__i2s_set_transmit_trigger(aic, (I2S_TFIFO_DEPTH / 4));

		I2S_DBG("TX_DMAC config ok!\n");
	}
	else
	{
		/* format */
		if(i2s->fmt_width == 8)
			bus_width = RT_DMA_BUSWIDTH_1_BYTE;
		else if(i2s->fmt_width == 16)
			bus_width = RT_DMA_BUSWIDTH_2_BYTES;
		else
			bus_width = RT_DMA_BUSWIDTH_4_BYTES;

        i2s->rx_dmac = rt_dma_get_channel(I2S_DMA_RX_CHAN);
        if(i2s->rx_dmac != RT_NULL)
        {
            config.direction        = RT_DMA_DEV_TO_MEM;
            config.src_addr_width   = bus_width;
            config.src_maxburst     =  (I2S_RFIFO_DEPTH * bus_width)/2;
            config.dst_addr_width   = bus_width;
            config.dst_maxburst     = (64 * 1024);
            rt_dma_configture(i2s->rx_dmac,&config);

            i2s->rx_dmac->start = RT_NULL;
            i2s->rx_dmac->complete = aic_i2s_trans_complete;

            I2S_DBG("RX DMA config ok \n");
        }

		__i2s_set_iss(aic, i2s->fmt_width);
		__i2s_set_receive_trigger(aic, (I2S_RFIFO_DEPTH/4 - 1));

	}

	return 0;
}

void aic_i2s_shutdown(struct jz_i2s *i2s,int stream)
{
	struct jz_aic   *aic = i2s->aic;

	aic_i2s_stop_substream(i2s,stream);

	if(stream == AUDIO_STREAM_REPLAY)
		i2s->i2s_mode &= ~I2S_WRITE;
	else
		i2s->i2s_mode &= ~I2S_READ;

	if(!i2s->i2s_mode)
		__aic_disable(aic);
}

int aic_i2s_set_sysclk(struct jz_i2s *i2s,uint32_t freq)
{
	struct jz_aic *aic = i2s->aic;


#ifdef RT_USING_ICODEC
	__aic_select_internal_codec(aic);
#else
	__aic_select_external_codec(aic);
#endif

	__i2s_stop_bitclk(aic);

	aic_set_rate(aic, freq);

	__i2s_start_bitclk(aic);

#ifdef CFG_AIC_SOC_CLKOUT
	/* Master clk output */
	__i2s_select_sysclk_output(aic);

	__i2s_enable_sysclk_output(aic);
#else
	/* Master clk input */
	__i2s_select_sysclk_input(aic);
	__i2s_disable_sysclk_output(aic);
#endif

    return 0;
}


static void aic_i2s_trans_complete(struct rt_dma_channel *dmac, struct dma_message *msg)
{
	I2S_DBG("TAG,%d,%s\n",__LINE__,__func__);
	if(msg->complete_cb)
	{
		if(msg->t_mode == JZDMA_REQ_I2S0_TX)
			msg->complete_cb(msg->complete_arg,msg->src_addr);
		else
			msg->complete_cb(msg->complete_arg,msg->dst_addr);
	}
}

rt_size_t aic_i2s_send(struct jz_i2s *i2s, const void* buffer, rt_size_t size,void (*tx_callback)(void *,void *), void *tx_arg)
{
    struct dma_message         message;

	I2S_DBG("TAG,%d,%s\n",__LINE__,__func__);

    message.src_addr    = (uint8_t *) (buffer);
    message.src_option  = RT_DMA_ADDR_INC;

    message.dst_addr    = (uint8_t *) (AIC_BASE + AICDR);
    message.dst_option  = RT_DMA_ADDR_FIX;

    message.t_size      = size;
    message.t_mode      = JZDMA_REQ_I2S0_TX;

    message.complete_cb	= (void *)tx_callback;
    message.complete_arg= tx_arg;

    I2S_DBG("i2s trans  length = %d\n",size);

	if (rt_dma_trans_message(i2s->tx_dmac, &message) == RT_EOK)
		return size;

    return 0;
}

rt_size_t aic_i2s_recv(struct jz_i2s *i2s, void* buffer, rt_size_t size,void (*rx_callback)(void *,void *), void *rx_arg)
{
    struct dma_message         message;

    message.src_addr    = (uint8_t *) (AIC_BASE + AICDR);
    message.src_option  = RT_DMA_ADDR_FIX;

    message.dst_addr    = (uint8_t *) (buffer);
    message.dst_option  = RT_DMA_ADDR_INC;

    message.t_size      = size;
    message.t_mode      = JZDMA_REQ_I2S0_RX;

    message.complete_cb	= (void *)rx_callback;
    message.complete_arg= rx_arg;

	if(rt_dma_trans_message(i2s->rx_dmac,&message) == RT_EOK)
		return size;

    return 0;
}



struct jz_i2s *rt_hw_aic_i2s_init(void)
{
    struct jz_aic *aic;
    struct jz_i2s *i2s = &_g_jz_i2s;

#ifndef RT_USING_ICODEC
#ifdef CFG_AIC_SOC_CLKOUT
	gpio_set_func(GPIO_PORT_B, GPIO_Pin_0, GPIO_FUNC_1); // I2S_MCLK
#endif
	gpio_set_func(GPIO_PORT_B, GPIO_Pin_1, GPIO_FUNC_1); // I2S_BCLK
	gpio_set_func(GPIO_PORT_B, GPIO_Pin_2, GPIO_FUNC_1); // I2S_LRCLK
	gpio_set_func(GPIO_PORT_B, GPIO_Pin_3, GPIO_FUNC_1); // I2S_DI
	gpio_set_func(GPIO_PORT_B, GPIO_Pin_4, GPIO_FUNC_1); // I2S_DO
#endif

	I2S_DBG("TAG,%d,%s\n",__LINE__,__func__);
    aic = _aic_init();
    if(aic == RT_NULL)
        return RT_NULL;
    i2s->aic = aic;

    i2s->i2s_mode = 0;

	I2S_DBG("TAG,%d,%s\n",__LINE__,__func__);

	/* now ,we just support I2S playback */
	aic_i2s_startup(i2s,AUDIO_STREAM_REPLAY);

	aic_i2s_hw_params(i2s,AUDIO_STREAM_REPLAY);

    return i2s;
}

