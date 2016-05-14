/*
 * File      : drv_mmc.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013 - 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-09     aozima       the first version
 * 2013-03-29     aozima       support Jz4770.
 * 2013-04-01     aozima       add interrupt support for Jz4770.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/mmcsd_core.h>
#include <drivers/sdio.h>

#include "board.h"
#include "drv_gpio.h"
#include "drv_clock.h"
#include "drv_mmc.h"

#define RT_USING_MSC0
#define RT_USING_MSC1

// #define JZ47XX_SDIO_DBG

#ifdef JZ47XX_SDIO_DBG
#define sdio_dbg(fmt, ...)  rt_kprintf("[SDIO]");rt_kprintf(fmt, ##__VA_ARGS__)
#else
#define sdio_dbg(fmt, ...)
#endif

static void msc_handler(int irqno, void* param)
{
    struct jz47xx_sdio * jz_sdio = (struct jz47xx_sdio *)param;

    /* disable interrupt */
    rt_hw_interrupt_mask(jz_sdio->irqno);

    rt_completion_done(&jz_sdio->completion);
}

rt_inline void jz_mmc_clk_autoctrl(struct jz47xx_sdio *host, unsigned int on)
{
    if(on)
    {
        if(!clk_is_enabled(host->clock))
            clk_enable(host->clock);
        if(!clk_is_enabled(host->clock_gate))
            clk_enable(host->clock_gate);
    }
    else
    {
        if(clk_is_enabled(host->clock_gate))
            clk_disable(host->clock_gate);
        if(clk_is_enabled(host->clock))
            clk_disable(host->clock);
    }
}

/* Stop the MMC clock and wait while it happens */
rt_inline rt_err_t jz_mmc_stop_clock(uint32_t hw_base)
{
    uint16_t value;
    int timeout = 10000;

    value = readw(hw_base + MSC_CTRL_OFFSET);
    value |= MSC_CTRL_CLOCK_STOP;
    writew(value, hw_base + MSC_CTRL_OFFSET);

    while (timeout && (readl(hw_base + MSC_STAT_OFFSET) & MSC_STAT_CLK_EN))
    {
        timeout--;
        if (timeout == 0)
        {
            return -RT_ETIMEOUT;
        }
        rt_thread_delay(1);
    }

    return RT_EOK;
}

/* Start the MMC clock and operation */
rt_inline void jz_mmc_start_clock(uint32_t hw_base)
{
    uint16_t value;
    value = readw(hw_base + MSC_CTRL_OFFSET);
    value |= (MSC_CTRL_CLOCK_START | MSC_CTRL_START_OP);
    writew(value, hw_base + MSC_CTRL_OFFSET);
}

static int jz_mmc_hardware_init(struct jz47xx_sdio * jz_sdio)
{
    uint32_t hw_base = jz_sdio->hw_base;
    uint32_t value;

    /* reset mmc/sd controller */
    value = readl(hw_base + MSC_CTRL_OFFSET);
    value |= MSC_CTRL_RESET;
    writel(value, hw_base + MSC_CTRL_OFFSET);
    rt_thread_delay(1);
    value &= ~MSC_CTRL_RESET;
    writel(value, hw_base + MSC_CTRL_OFFSET);

    while(readl(hw_base + MSC_STAT_OFFSET) & MSC_STAT_IS_RESETTING);

    /* mask all IRQs */
    writel(0xffffffff, hw_base + MSC_IMASK_OFFSET);
    writel(0xffffffff, hw_base + MSC_IREG_OFFSET);

    /* set timeout */
    writel(0x100, hw_base + MSC_RESTO_OFFSET);
    writel(0x1ffffff, hw_base + MSC_RDTO_OFFSET);

    /* stop MMC/SD clock */
    jz_mmc_stop_clock(hw_base);
}

/* Set the MMC clock frequency */
void jz_mmc_set_clock(struct jz47xx_sdio * jz_sdio, unsigned int clock)
{
    unsigned int msc_clock = jz_sdio->msc_clock;

    /* calc and set MSC_CLKRT. */
    {
        unsigned int div = 0;
        while (clock < msc_clock)
        {
            div++;
            msc_clock >>= 1;
        }
        if(div > 7) div = 7;

        sdio_dbg("msc_clock: %u, SDIO_CLK: %u, MSC_CLKRT: %u\r\n", jz_sdio->msc_clock, clock, div);
        writew(div, jz_sdio->hw_base + MSC_CLKRT_OFFSET);
    }
}

/* RT-Thread SDIO interface */
static void jz47xx_sdio_request(struct rt_mmcsd_host *host,
                                struct rt_mmcsd_req *req)
{
    struct jz47xx_sdio *sdio = host->private_data;
    unsigned int cmdat = 0;
    unsigned int stat;
    uint32_t hw_base, value;

    hw_base = sdio->hw_base;
    jz_mmc_stop_clock(hw_base);

    sdio_dbg("CMD: %d ARG: %08X\n", req->cmd->cmd_code, req->cmd->arg);

    if(sdio->flag & MSC_CMDAT_BUS_WIDTH_4BIT)
    {
        cmdat |= MSC_CMDAT_BUS_WIDTH_4BIT;
    }

    /* auto send stop */
    if (req->stop)
    {
        sdio_dbg("CMD STOP: %d ARG: %08X\n", req->stop->cmd_code,
                 req->stop->arg);
        cmdat |= MSC_CMDAT_SEND_AS_STOP;
    }

    if(req->cmd->cmd_code == GO_IDLE_STATE)
    {
        cmdat |= MSC_CMDAT_INIT;
    }

    /* clear status */
    writew(0xFFFF, hw_base + MSC_IREG_OFFSET);

    /* open interrupt */
    value = readl(hw_base + MSC_IMASK_OFFSET);
    value &= ~(MSC_DATA_TRAN_DONE | MSC_PRG_DONE | MSC_END_CMD_RES);
    writel(value, hw_base + MSC_IMASK_OFFSET);

    if(req->data)
    {
        writew(req->data->blksize, hw_base + MSC_BLKLEN_OFFSET);
        writew(req->data->blks, hw_base + MSC_NOB_OFFSET);

        cmdat |= MSC_CMDAT_DATA_EN;
        if (req->data->flags & DATA_DIR_WRITE)
        {
            cmdat |= MSC_CMDAT_WRITE;
        }
        else if (req->data->flags & DATA_DIR_READ)
        {
            cmdat |= MSC_CMDAT_READ;
        }
    }
    else
    {
        writew(0, hw_base + MSC_BLKLEN_OFFSET);
        writew(0, hw_base + MSC_NOB_OFFSET);
    }

    /* set command */
    writeb(req->cmd->cmd_code, hw_base + MSC_CMD_OFFSET);

    /* set argument */
    writel(req->cmd->arg, hw_base + MSC_ARG_OFFSET);

    /* Set response type */
#ifdef JZ47XX_SDIO_DBG
    {
        int res_type = req->cmd->flags & RESP_MASK;
        sdio_dbg("resp type:%u\r\n", res_type);
    }
#endif

    cmdat &= ~(MSC_CMDAT_RESP_FORMAT_MASK);
    switch (req->cmd->flags & RESP_MASK)
    {
    case RESP_NONE:
        break;

    case RESP_R1B:
        cmdat |= MSC_CMDAT_BUSY;
        /*FALLTHRU*/
    case RESP_R1:
        cmdat |= MSC_CMDAT_RESPONSE_R1;
        break;
    case RESP_R2:
        cmdat |= MSC_CMDAT_RESPONSE_R2;
        break;
    case RESP_R3:
        cmdat |= MSC_CMDAT_RESPONSE_R3;
        break;
    case RESP_R4:
        cmdat |= MSC_CMDAT_RESPONSE_R4;
        break;
    case RESP_R5:
        cmdat |= MSC_CMDAT_RESPONSE_R5;
        break;
    case RESP_R6:
        cmdat |= MSC_CMDAT_RESPONSE_R6;
    case RESP_R7:
        cmdat |= MSC_CMDAT_RESPONSE_R7;
        break;
    default:
        break;
    }

    /* Set command */
    sdio_dbg("cmdat: %08X\r\n", cmdat);
    writel(cmdat, sdio->hw_base + MSC_CMDAT_OFFSET);
    writel(MSC_CTRL_START_OP, sdio->hw_base + MSC_CTRL_OFFSET);

    writel(0xFF, sdio->hw_base + MSC_RESTO_OFFSET);
    writel(0xFFFFFFFF, sdio->hw_base + MSC_RDTO_OFFSET);

    jz_mmc_start_clock(sdio->hw_base);
    req->cmd->err = RT_EOK;

    if(!(readl(sdio->hw_base + MSC_IREG_OFFSET) & MSC_END_CMD_RES))
    {
        rt_err_t ret;

        rt_completion_init(&sdio->completion);
        rt_hw_interrupt_umask(sdio->irqno);
        ret = rt_completion_wait(&sdio->completion, RT_TICK_PER_SECOND);
        if(ret == RT_EOK)
        {
            sdio_dbg("wait END_CMD_RES OK!\r\n");
        }
        else
        {
            uint32_t value;

            value = readl(hw_base + MSC_STAT_OFFSET);
            sdio_dbg("stat=0x%08x\n", value);
            value = readl(hw_base + MSC_IREG_OFFSET);
            sdio_dbg("iflag=0x%08x\n", value);

            req->cmd->err = ret;
            sdio_dbg("wait END_CMD_RES timeout[uncompletion]\r\n");
        }
    }
    else
    {
        sdio_dbg("no need wait MSC_END_CMD_RES!\r\n");
    }

    stat = readl(hw_base + MSC_STAT_OFFSET);
    writew(MSC_END_CMD_RES, hw_base + MSC_IREG_OFFSET);

    /* get response. */
    {
        uint8_t buf[16];
        uint32_t data;

        if(req->cmd->err == RT_EOK)
        {
            if(stat & MSC_STAT_TIME_OUT_RES)
            {
                sdio_dbg("ERR: MSC_STAT_TIME_OUT_RES\r\n");
                req->cmd->err = -RT_ETIMEOUT;
            }
            else if(stat & MSC_STAT_CRC_READ_ERR)
            {
                sdio_dbg("ERR: MSC_STAT_CRC_READ_ERR\r\n");
                req->cmd->err = -1;
            }
        }

        switch (req->cmd->flags & RESP_MASK)
        {
        case RESP_R1:
        case RESP_R1B:
        case RESP_R6:
        case RESP_R3:
        case RESP_R4:
        case RESP_R5:
        case RESP_R7:
            data = readw(sdio->hw_base + MSC_RES_OFFSET);
            buf[1] = data & 0xFF;

            data = readw(sdio->hw_base + MSC_RES_OFFSET);
            buf[2] = (data >> 8) & 0xFF;
            buf[3] = data & 0xFF;

            data = readw(sdio->hw_base + MSC_RES_OFFSET);
            buf[4] = data & 0xFF;

            req->cmd->resp[0] = buf[1] << 24 | buf[2] << 16
                                | buf[3] << 8 | buf[4];
            break;
        case RESP_R2:
        {
            uint32_t i, v, w1, w2;

            data = readw(sdio->hw_base + MSC_RES_OFFSET);
            v = data & 0xFFFF;

            for(i=0; i<4; i++)
            {
                data = readw(sdio->hw_base + MSC_RES_OFFSET);
                w1 = data & 0xFFFF;

                data = readw(sdio->hw_base + MSC_RES_OFFSET);
                w2 = data & 0xFFFF;

                req->cmd->resp[i] = v << 24 | w1 << 8 | w2 >> 8;
                v = w2;
            }
        }
        break;
        default:
            break;
        }

        sdio_dbg("error:%d cmd->resp [%08X, %08X, %08X, %08X]\r\n\r\n",
                 req->cmd->err,
                 req->cmd->resp[0],
                 req->cmd->resp[1],
                 req->cmd->resp[2],
                 req->cmd->resp[3]
                );
    }

    if(req->data)
    {
        unsigned int waligned;
        uint32_t len = req->data->blksize * req->data->blks;

        /* word aligned ? */
        waligned = (((unsigned int)req->data->buf & 0x3) == 0);

        if (req->data->flags & DATA_DIR_WRITE)
        {
            if(waligned)
            {
                uint32_t i;
                uint32_t *src = (uint32_t *)req->data->buf;

                for(i=0; i<len; i+=4)
                {
                    while (readl(sdio->hw_base +  MSC_STAT_OFFSET) & MSC_STAT_DATA_FIFO_FULL);

                    writel(*src++, hw_base + MSC_TXFIFO_OFFSET);
                }
            }
            else
            {
                uint32_t i, data;
                uint8_t * src = (uint8_t *)req->data->buf;

                for(i=0; i<len; i+=4)
                {
                    while (readl(sdio->hw_base +  MSC_STAT_OFFSET) & MSC_STAT_DATA_FIFO_FULL);

                    data  = (*src++ << 0);
                    data |= (*src++ << 8);
                    data |= (*src++ << 16);
                    data |= (*src++ << 24);

                    writel(data, hw_base + MSC_TXFIFO_OFFSET);
                }
            }

            writel(IFLG_PRG_DONE, hw_base + MSC_IREG_OFFSET);
        }
        else if (req->data->flags & DATA_DIR_READ)
        {
            if(waligned)
            {
                uint32_t i;
                uint32_t * dst = (uint32_t *)req->data->buf;

                for(i=0; i<len; i+=4)
                {
                    while (readl(sdio->hw_base +  MSC_STAT_OFFSET) & MSC_STAT_DATA_FIFO_EMPTY);

                    *dst ++ = readl(sdio->hw_base +  MSC_RXFIFO_OFFSET);
                }
            }
            else
            {
                uint32_t data, i;
                uint8_t * dst = (uint8_t *)req->data->buf;

                for(i=0; i<len; i+=4)
                {
                    while (readl(sdio->hw_base +  MSC_STAT_OFFSET) & MSC_STAT_DATA_FIFO_EMPTY);

                    data = readl(sdio->hw_base +  MSC_RXFIFO_OFFSET);
                    *dst++ = (uint8_t)(data >> 0);
                    *dst++ = (uint8_t)(data >> 8);
                    *dst++ = (uint8_t)(data >> 16);
                    *dst++ = (uint8_t)(data >> 24);
                }
            }

            writel(IFLG_DATA_TRAN_DONE, hw_base + MSC_IREG_OFFSET);
        }

#if 0
        value = readl(hw_base + MSC_IMASK_OFFSET);
        value &= ~MSC_DATA_TRAN_DONE;
        writel(value, hw_base + MSC_IMASK_OFFSET);

        if(!(readl(sdio->hw_base + MSC_IREG_OFFSET) & MSC_DATA_TRAN_DONE))
        {
            rt_err_t ret;

            rt_completion_init(&sdio->completion);
            sdio_dbg("TRAN_DONE umask\r\n");
            rt_hw_interrupt_umask(sdio->irqno);

            ret = rt_completion_wait(&sdio->completion, RT_TICK_PER_SECOND);
            if(ret == RT_EOK)
            {
                sdio_dbg("wait END_CMD_RES OK!\r\n");
            }
            else
            {
            	rt_kprintf("SD DATA: int status 0x%08x\n", readl(sdio->hw_base + MSC_IREG_OFFSET));
                sdio_dbg("wait END_CMD_RES timeout!\r\n");
            }
        }
        else
        {
            sdio_dbg("no need wait MSC_DATA_TRAN_DONE!\r\n");
        }
#endif

        /* clear status */
        writew(MSC_DATA_TRAN_DONE, hw_base + MSC_IREG_OFFSET);
    } /* if req->data */

    mmcsd_req_complete(host);
}


static void jz47xx_sdio_set_iocfg(struct rt_mmcsd_host *host,
                                  struct rt_mmcsd_io_cfg *io_cfg)
{
    struct jz47xx_sdio * jz_sdio = host->private_data;
    rt_uint32_t clkdiv;

    sdio_dbg("set_iocfg clock: %d\n", io_cfg->clock);

    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        sdio_dbg("MMC: Setting controller bus width to 4\n");
        jz_sdio->flag |= MSC_CMDAT_BUS_WIDTH_4BIT;
    }
    else
    {
        jz_sdio->flag &= ~(MSC_CMDAT_BUS_WIDTH_4BIT);
        sdio_dbg("MMC: Setting controller bus width to 1\n");
    }

    if (io_cfg->clock)
    {
        unsigned int clk_set = 0, clkrt = 0;
        unsigned int clk_want = io_cfg->clock;
        unsigned int lpm = 0;

        if (io_cfg->clock > 1 * 1000 * 1000)
        {
            io_cfg->clock = 1000 * 1000;
        }

        jz_mmc_clk_autoctrl(jz_sdio, 1);
        if (clk_want > 3000000)
        {
            clk_set_rate(jz_sdio->clock, io_cfg->clock);
        }
        else
        {
            clk_set_rate(jz_sdio->clock, 24000000);
        }
        clk_set = clk_get_rate(jz_sdio->clock);

        while (clk_want < clk_set)
        {
            clkrt++;
            clk_set >>= 1;
        }

        if (clkrt > 7)
        {
            sdio_dbg("invalid value of CLKRT: "
                "ios->clock=%d clk_want=%d "
                "clk_set=%d clkrt=%X,\n",
                io_cfg->clock, clk_want, clk_set, clkrt);
            return;
        }

        if (!clkrt)
        {
            sdio_dbg("clk_want: %u, clk_set: %luHz\n", io_cfg->clock, clk_get_rate(jz_sdio->clock));
        }

        writel(clkrt, jz_sdio->hw_base + MSC_CLKRT_OFFSET);

        if (clk_set > 25000000)
        {
            lpm = (0x2 << LPM_DRV_SEL_SHF) | LPM_SMP_SEL;
        }

        if(jz_sdio->sdio_clk)
        {
            writel(lpm, jz_sdio->hw_base + MSC_LPM_OFFSET);
            writel(MSC_CTRL_CLOCK_START, jz_sdio->hw_base + MSC_CTRL_OFFSET);
        }
        else
        {
            lpm |= LPM_LPM;
            writel(lpm, jz_sdio->hw_base + MSC_LPM_OFFSET);
        }
    }
    else
    {
        jz_mmc_clk_autoctrl(jz_sdio, 0);
    }

    /* maybe switch power to the card */
    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        sdio_dbg("MMCSD_POWER_OFF\r\n");
        break;
    case MMCSD_POWER_UP:
        sdio_dbg("MMCSD_POWER_UP\r\n");
        break;
    case MMCSD_POWER_ON:
        sdio_dbg("MMCSD_POWER_ON\r\n");
        jz_mmc_hardware_init(jz_sdio);
        // jz_mmc_set_clock(jz_sdio, io_cfg->clock);
        break;
    default:
        sdio_dbg("unknown power_mode %d\n", io_cfg->power_mode);
        break;
    }
}

static rt_int32_t jz47xx_SD_Detect(struct rt_mmcsd_host *host)
{
    sdio_dbg("jz47xx_SD_Detect\n");
}

static void jz47xx_sdio_enable_sdio_irq(struct rt_mmcsd_host *host,
                                        rt_int32_t enable)
{
    sdio_dbg("jz47xx_sdio_enable_sdio_irq, enable:%d\n", enable);
}

static const struct rt_mmcsd_host_ops ops =
{
    jz47xx_sdio_request,
    jz47xx_sdio_set_iocfg,
    jz47xx_SD_Detect,
    jz47xx_sdio_enable_sdio_irq,
};

int jz47xx_sdio_init(void)
{
    struct rt_mmcsd_host *host = RT_NULL;
    struct jz47xx_sdio * jz_sdio = RT_NULL;

#ifdef  RT_USING_MSC0
    host = mmcsd_alloc_host();
    jz_sdio = rt_malloc(sizeof(struct jz47xx_sdio));
    if(!(host && jz_sdio))
    {
        goto err;
    }

    rt_memset(jz_sdio, 0, sizeof(struct jz47xx_sdio));
    /* set hardware base firstly */
    jz_sdio->hw_base = MSC0_BASE;
    jz_sdio->clock = clk_get("cgu_msc0");
    jz_sdio->clock_gate = clk_get("msc0");

    /* init GPIO (msc0 boot)
     *        name      pin  fun
     * X1000  MSC0_D0:  PA23  1
     * X1000  MSC0_D1:  PA22  1
     * X1000  MSC0_D2:  PA21  1
     * X1000  MSC0_D3:  PA20  1
     * X1000  MSC0_CMD: PA25  1
     * X1000  MSC0_CLK: PA24  1
     */
    {
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_20, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_21, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_22, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_23, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_24, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_A, GPIO_Pin_25, GPIO_FUNC_1);
    }

    /* enable MSC0 clock gate. */
    clk_enable(jz_sdio->clock_gate);

    jz_sdio->msc_clock = 24UL * 1000 * 1000;    /* 50Mhz */
    host->freq_min = 400 * 1000;                /* min 400Khz. */
    host->freq_max = 24 * 1000 * 1000;          /* max 50Mhz.  */

    /* set clock */
    clk_set_rate(jz_sdio->clock, BOARD_EXTAL_CLK);

    host->ops = &ops;
    host->valid_ocr = VDD_27_28 | VDD_28_29 | VDD_29_30 | VDD_30_31 | VDD_31_32 |
        VDD_32_33 | VDD_33_34 | VDD_34_35 | VDD_35_36;
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED;
    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;
    host->private_data = jz_sdio;

    jz_sdio->host = host;
    jz_sdio->irqno = IRQ_MSC0;

    rt_hw_interrupt_install(jz_sdio->irqno, msc_handler, jz_sdio, "msc0");
    rt_hw_interrupt_mask(jz_sdio->irqno);

    mmcsd_change(host);
#endif // RT_USING_MSC0

#ifdef  RT_USING_MSC1
    host = mmcsd_alloc_host();
    jz_sdio = rt_malloc(sizeof(struct jz47xx_sdio));
    if(!(host && jz_sdio))
    {
        goto err;
    }

    rt_memset(jz_sdio, 0, sizeof(struct jz47xx_sdio));
    jz_sdio->hw_base = MSC1_BASE;
    jz_sdio->clock = clk_get("cgu_msc1");
    jz_sdio->clock_gate = clk_get("msc1");

    /* init GPIO (paladin msc1 SDIO wifi)
     *        name      pin  fun
     * X1000  MSC1_D0:  PC02  0
     * X1000  MSC1_D1:  PC03  0
     * X1000  MSC1_D2:  PC04  0
     * X1000  MSC1_D3:  PC05  0
     * X1000  MSC1_CMD: PC01  0
     * X1000  MSC1_CLK: PC00  0
     *
     */
    {
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_0, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_1, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_2, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_3, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_4, GPIO_FUNC_0);
        gpio_set_func(GPIO_PORT_C, GPIO_Pin_5, GPIO_FUNC_0);
    }

    /* enable MSC1 clock gate. */
    clk_enable(jz_sdio->clock_gate);

    jz_sdio->msc_clock = 50UL * 1000 * 1000;    /* 50Mhz */
    host->freq_min = 400 * 1000;                /* min 400Khz. */
    host->freq_max = 50 * 1000 * 1000;          /* max 50Mhz.  */

    /* set clock */
    clk_set_rate(jz_sdio->clock, BOARD_EXTAL_CLK);

    host->ops = &ops;
    host->valid_ocr = VDD_27_28 | VDD_28_29 | VDD_29_30 | VDD_30_31 | VDD_31_32 |
        VDD_32_33 | VDD_33_34 | VDD_34_35 | VDD_35_36;
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE;
    host->max_seg_size = 65535;
    host->max_dma_segs = 2;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;
    host->private_data = jz_sdio;

    jz_sdio->host = host;
    jz_sdio->irqno = IRQ_MSC1;

    rt_hw_interrupt_install(jz_sdio->irqno, msc_handler, jz_sdio, "msc1");
    rt_hw_interrupt_mask(jz_sdio->irqno);

    mmcsd_change(host);
#endif // RT_USING_MSC1

    return RT_EOK;

err:
    if(host)
    {
        mmcsd_free_host(host);
    }
    if(jz_sdio)
    {
        rt_free(host);
    }

    return -RT_ENOMEM;
}

