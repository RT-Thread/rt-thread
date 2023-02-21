#include <hal_log.h>
#include <stdlib.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <hal_gpio.h>
#include <sunxi_hal_twi.h>
#include <hal_dma.h>
#include <hal_cache.h>
#include <sunxi_hal_regulator.h>
#include <interrupt.h>

#ifdef CONFIG_RTTKERNEL
#include <hal_cfg.h>
#include <script.h>
#endif

static const uint32_t hal_twi_address[] =
{
    SUNXI_TWI0_PBASE,
    SUNXI_TWI1_PBASE,
    SUNXI_TWI2_PBASE,
    SUNXI_TWI3_PBASE,
#if !(defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1))
    SUNXI_S_TWI0_PBASE,
#endif
};

static const uint32_t hal_twi_irq_num[] =
{
    SUNXI_IRQ_TWI0,
    SUNXI_IRQ_TWI1,
    SUNXI_IRQ_TWI2,
    SUNXI_IRQ_TWI3,
#if !(defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1))
    SUNXI_IRQ_S_TWI0,
#endif
};

#if !(defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1))
static const hal_clk_id_t hal_twi_pclk[] =
{
    HAL_CLK_BUS_APB2,
    HAL_CLK_BUS_APB2,
    HAL_CLK_BUS_APB2,
    HAL_CLK_BUS_APB2,
    HAL_CLK_BUS_APB2,
};

static const hal_clk_id_t hal_twi_mclk[] =
{
    HAL_CLK_PERIPH_TWI0,
    HAL_CLK_PERIPH_TWI1,
    HAL_CLK_PERIPH_TWI2,
    HAL_CLK_PERIPH_TWI3,
    HAL_CLK_PERIPH_TWI4,
};
#endif

static const enum REGULATOR_TYPE_ENUM twi_regulator_type = AXP2101_REGULATOR;
static const enum REGULATOR_ID_ENUM twi_regulator_id[] =
{
    AXP2101_ID_ALDO2,
    AXP2101_ID_ALDO2,
    AXP2101_ID_MAX,
    AXP2101_ID_MAX,
    AXP2101_ID_MAX,
};
static const int twi_vol[] =
{
    3300000,
    3300000,
    -1,
    -1,
    -1,
};


static hal_twi_t hal_twi[TWI_MASTER_MAX];

/* set twi clock
 *
 * clk_n: clock divider factor n
 * clk_m: clock divider factor m
 */
static void twi_clk_write_reg(hal_twi_t *twi, unsigned int reg_clk,
                              unsigned int clk_m, unsigned int clk_n,
                              unsigned int mask_clk_m, unsigned int mask_clk_n)
{
    const unsigned long base_addr = twi->base_addr;
    unsigned int reg_val = readl(base_addr + reg_clk);

    if (reg_clk == TWI_DRIVER_BUSC)
    {
        reg_val &= ~(mask_clk_m | mask_clk_n);
        reg_val |= ((clk_m | (clk_n << 4)) << 8);
        writel(reg_val, base_addr + reg_clk);
    }
    else
    {
        reg_val &= ~(mask_clk_m | mask_clk_n);
        reg_val |= ((clk_m  << 3) | clk_n);
        writel(reg_val, base_addr + reg_clk);
    }
}

/*
* Fin is APB CLOCK INPUT;
* Fsample = F0 = Fin/2^CLK_N;
* F1 = F0/(CLK_M+1);
* Foscl = F1/10 = Fin/(2^CLK_N * (CLK_M+1)*10);
* Foscl is clock SCL;100KHz or 400KHz
*
* clk_in: apb clk clock
* sclk_req: freqence to set in HZ
*/
static int twi_set_clock(hal_twi_t *twi, unsigned int reg_clk,
                         unsigned int clk_in, unsigned int sclk_req,
                         unsigned int mask_clk_m, unsigned int mask_clk_n)
{
    unsigned int clk_m = 0;
    unsigned int clk_n = 0;
    unsigned int _2_pow_clk_n = 1;
    unsigned int src_clk      = clk_in / 10;
    unsigned int divider      = src_clk / sclk_req; /* 400khz or 100khz */
    unsigned int sclk_real    = 0;      /* the real clock frequency */

    if (divider == 0)
    {
        clk_m = 1;
        goto set_clk;
    }

    /*
     * search clk_n and clk_m,from large to small value so
     * that can quickly find suitable m & n.
     */
    while (clk_n < 8)   /* 3bits max value is 8 */
    {
        /* (m+1)*2^n = divider -->m = divider/2^n -1 */
        clk_m = (divider / _2_pow_clk_n) - 1;
        /* clk_m = (divider >> (_2_pow_clk_n>>1))-1 */
        while (clk_m < 16)   /* 4bits max value is 16 */
        {
            /* src_clk/((m+1)*2^n) */
            sclk_real = src_clk / (clk_m + 1) / _2_pow_clk_n;
            if (sclk_real <= sclk_req)
            {
                goto set_clk;
            }
            else
            {
                clk_m++;
            }
        }
        clk_n++;
        _2_pow_clk_n *= 2; /* mutilple by 2 */
    }

set_clk:
    twi_clk_write_reg(twi, reg_clk, clk_m, clk_n, mask_clk_m, mask_clk_n);
    return 0;
}


/*************************************** TWI ENGINE XFER REG CONTROL begin****************************/

/* clear the interrupt flag */
static inline void twi_clear_irq_flag(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);
    /* start and stop bit should be 0 */
    reg_val |= TWI_CTL_INTFLG;
    reg_val &= ~(TWI_CTL_STA | TWI_CTL_STP);
    writel(reg_val, base_addr + TWI_CTL_REG);
    /* read two more times to make sure that */
    /* interrupt flag does really be cleared */
    {
        unsigned int temp;

        temp = readl(base_addr + TWI_CTL_REG);
        temp |= readl(base_addr + TWI_CTL_REG);
    }
}

/* get data first, then clear flag */
static inline void twi_get_byte(const unsigned long base_addr, unsigned char  *buffer)
{
    *buffer = (unsigned char)(TWI_DATA_MASK & readl(base_addr + TWI_DATA_REG));
    twi_clear_irq_flag(base_addr);
}

/* only get data, we will clear the flag when stop */
static inline void twi_get_last_byte(const unsigned long base_addr, unsigned char  *buffer)
{
    *buffer = (unsigned char)(TWI_DATA_MASK &
                              readl(base_addr + TWI_DATA_REG));
}

/* write data and clear irq flag to trigger send flow */
static inline void twi_put_byte(const unsigned long base_addr, const unsigned char *buffer)
{
    writel((unsigned int)*buffer, base_addr + TWI_DATA_REG);
    twi_clear_irq_flag(base_addr);
}

static inline void twi_enable_irq(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    /*
     * 1 when enable irq for next operation, set intflag to 0 to prevent
     * to clear it by a mistake (intflag bit is write-1-to-clear bit)
     * 2 Similarly, mask START bit and STOP bit to prevent to set it
     * twice by a mistake (START bit and STOP bit are self-clear-to-0 bits)
     */
    reg_val |= TWI_CTL_INTEN;
    reg_val &= ~(TWI_CTL_STA | TWI_CTL_STP | TWI_CTL_INTFLG);
    writel(reg_val, base_addr + TWI_CTL_REG);
}

static inline void twi_disable_irq(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    reg_val &= ~TWI_CTL_INTEN;
    reg_val &= ~(TWI_CTL_STA | TWI_CTL_STP | TWI_CTL_INTFLG);
    writel(reg_val, base_addr + TWI_CTL_REG);
}

static inline void twi_disable(const unsigned long base_addr, unsigned int reg, unsigned int mask)
{
    unsigned int reg_val = readl(base_addr + reg);

    reg_val &= ~mask;
    writel(reg_val, base_addr + reg);
    TWI_INFO("offset: 0x%x value: 0x%lx", reg, readl(base_addr + reg));
}

static inline void twi_enable(const unsigned long base_addr, unsigned int reg, unsigned int mask)
{
    unsigned int reg_val = readl(base_addr + reg);

    reg_val |= mask;
    writel(reg_val, base_addr + reg);
    TWI_INFO("offset: 0x%x value: 0x%lx", reg,
             readl(base_addr + reg));
}

/* trigger start signal, the start bit will be cleared automatically */
static inline void twi_set_start(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    reg_val |= TWI_CTL_STA;
    reg_val &= ~TWI_CTL_INTFLG;
    writel(reg_val, base_addr + TWI_CTL_REG);
}

/* get start bit status, poll if start signal is sent */
static inline unsigned int twi_get_start(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    reg_val >>= 5;
    return reg_val & 1;
}

/* trigger stop signal, the stop bit will be cleared automatically */
static inline void twi_set_stop(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    reg_val |= TWI_CTL_STP;
    reg_val &= ~TWI_CTL_INTFLG;
    writel(reg_val, base_addr + TWI_CTL_REG);
}

/* get stop bit status, poll if stop signal is sent */
static inline unsigned int twi_get_stop(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    reg_val >>= 4;
    return reg_val & 1;
}

static inline void twi_disable_ack(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    reg_val &= ~TWI_CTL_ACK;
    reg_val &= ~TWI_CTL_INTFLG;
    writel(reg_val, base_addr + TWI_CTL_REG);
}

/* when sending ack or nack, it will send ack automatically */
static inline void twi_enable_ack(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    reg_val |= TWI_CTL_ACK;
    reg_val &= ~TWI_CTL_INTFLG;
    writel(reg_val, base_addr + TWI_CTL_REG);
}

/* get the interrupt flag */
static inline unsigned int twi_query_irq_flag(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_CTL_REG);

    return (reg_val & TWI_CTL_INTFLG);/* 0x 0000_1000 */
}

/* get interrupt status */
static inline unsigned int twi_query_irq_status(const unsigned long base_addr)
{
    unsigned int reg_val = readl(base_addr + TWI_STAT_REG);

    return (reg_val & TWI_STAT_MASK);
}

/* Enhanced Feature Register */
static inline void twi_set_efr(const unsigned long base_addr, unsigned int efr)
{
    unsigned int reg_val = readl(base_addr + TWI_EFR_REG);

    reg_val &= ~TWI_EFR_MASK;
    efr     &= TWI_EFR_MASK;
    reg_val |= efr;
    writel(reg_val, base_addr + TWI_EFR_REG);
}

/* function  */
static int twi_start(const unsigned long base_addr, int port)
{
    unsigned int timeout = 0xff;

    twi_set_start(base_addr);
    while ((twi_get_start(base_addr) == 1) && (--timeout))
        ;
    if (timeout == 0)
    {
        TWI_ERR("[twi%d] START can't sendout!", port);
        return SUNXI_TWI_FAIL;
    }

    return SUNXI_TWI_OK;
}

static int twi_restart(const unsigned long base_addr, int port)
{
    unsigned int timeout = 0xff;

    twi_set_start(base_addr);
    twi_clear_irq_flag(base_addr);
    while ((twi_get_start(base_addr) == 1) && (--timeout))
        ;
    if (timeout == 0)
    {
        TWI_ERR("[twi%d] Restart can't sendout!", port);
        return SUNXI_TWI_FAIL;
    }

    return SUNXI_TWI_OK;
}

static int twi_stop(const unsigned long base_addr, int port)
{
    unsigned int timeout = 0xff;

    twi_set_stop(base_addr);
    //unsigned int reg_val = readl(base_addr + TWI_CTL_REG);
    twi_clear_irq_flag(base_addr);

    twi_get_stop(base_addr);/* it must delay 1 nop to check stop bit */
    while ((twi_get_stop(base_addr) == 1) && (--timeout))
        ;
    if (timeout == 0)
    {
        TWI_ERR("[twi%d] STOP can't sendout!", port);
        return SUNXI_TWI_TFAIL;
    }

    //twi_clear_irq_flag(base_addr);
    timeout = 0xff;
    while ((readl(base_addr + TWI_STAT_REG) != TWI_STAT_IDLE)
           && (--timeout))
        ;
    if (timeout == 0)
    {
        TWI_ERR("[twi%d] twi state(0x%0lx) isn't idle(0xf8)",
                port, readl(base_addr + TWI_STAT_REG));
        return SUNXI_TWI_TFAIL;
    }

    timeout = 0xff;
    while ((readl(base_addr + TWI_LCR_REG) != TWI_LCR_IDLE_STATUS
            && readl(base_addr + TWI_LCR_REG) != TWI_LCR_NORM_STATUS)
           && (--timeout))
        ;

    if (timeout == 0)
    {
        TWI_ERR("[twi%d] twi lcr(0x%0lx) isn't idle(0x3a)",
                port, readl(base_addr + TWI_LCR_REG));
        return SUNXI_TWI_TFAIL;
    }

    //twi_clear_irq_flag(base_addr);
    TWI_INFO("twi stop end");

    return SUNXI_TWI_OK;
}

/* get SDA state */
static unsigned int twi_get_sda(const unsigned long base_addr)
{
    unsigned int status = 0;

    status = TWI_LCR_SDA_STATE_MASK & readl(base_addr + TWI_LCR_REG);
    status >>= 4;
    return (status & 0x1);
}

/* set SCL level(high/low), only when SCL enable */
static void twi_set_scl(const unsigned long base_addr, unsigned int hi_lo)
{
    unsigned int reg_val = readl(base_addr + TWI_LCR_REG);

    reg_val &= ~TWI_LCR_SCL_CTL;
    hi_lo   &= 0x01;
    reg_val |= (hi_lo << 3);
    writel(reg_val, base_addr + TWI_LCR_REG);
}

/* enable SDA or SCL */
static void twi_enable_lcr(const unsigned long base_addr, unsigned int sda_scl)
{
    unsigned int reg_val = readl(base_addr + TWI_LCR_REG);

    sda_scl &= 0x01;
    if (sda_scl)
    {
        reg_val |= TWI_LCR_SCL_EN;    /* enable scl line control */
    }
    else
    {
        reg_val |= TWI_LCR_SDA_EN;    /* enable sda line control */
    }

    writel(reg_val, base_addr + TWI_LCR_REG);
}

/* disable SDA or SCL */
static void twi_disable_lcr(const unsigned long base_addr, unsigned int sda_scl)
{
    unsigned int reg_val = readl(base_addr + TWI_LCR_REG);

    sda_scl &= 0x01;
    if (sda_scl)
    {
        reg_val &= ~TWI_LCR_SCL_EN;    /* disable scl line control */
    }
    else
    {
        reg_val &= ~TWI_LCR_SDA_EN;    /* disable sda line control */
    }

    writel(reg_val, base_addr + TWI_LCR_REG);
}

/* send 9 clock to release sda */
static int twi_send_clk_9pulse(const unsigned long base_addr, int port)
{
    int twi_scl = 1;
    int low = 0;
    int high = 1;
    int cycle = 0;
    int num = 0;
    unsigned char status;

    /* enable scl control */
    twi_enable_lcr(base_addr, twi_scl);

    while (cycle < 9)
    {
        if (twi_get_sda(base_addr)
            && twi_get_sda(base_addr)
            && twi_get_sda(base_addr))
        {
            break;
        }
        /* twi_scl -> low */
        twi_set_scl(base_addr, low);
        for (num = 1000; num > 0; num--);

        /* twi_scl -> high */
        twi_set_scl(base_addr, high);

        for (num = 1000; num > 0; num--);
        cycle++;
    }

    if (twi_get_sda(base_addr))
    {
        twi_disable_lcr(base_addr, twi_scl);
        status =  SUNXI_TWI_OK;
    }
    else
    {
        TWI_ERR("[twi%d] SDA is still Stuck Low, failed.", port);
        twi_disable_lcr(base_addr, twi_scl);
        status =  SUNXI_TWI_FAIL;
    }

    return status;
}


/*************************************** TWI DRV XFER REG CONTROL begin****************************/

#if 0

/* set twi clock
 *
 * clk_n: clock divider factor n
 * clk_m: clock divider factor m
 */
static void twi_clk_write_reg(const uint32_t base_addr, uint32_t sclk_freq,
                              uint8_t clk_m, uint8_t clk_n)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_BUSC);
#if defined(CONFIG_ARCH_SUN50IW10)
    uint32_t duty;
#endif
    TWI_INFO("reg_clk = 0x%x, clk_m = %u, clk_n = %u,"
             "mask_clk_m = %x, mask_clk_n = %x",
             reg_clk, clk_m, clk_n, mask_clk_m, mask_clk_n);

    reg_val &= ~(TWI_DRV_CLK_M | TWI_DRV_CLK_N);
    reg_val |= ((clk_m | (clk_n << 4)) << 8);
#if defined(CONFIG_ARCH_SUN50IW10)
    duty = TWI_DRV_CLK_DUTY;
    if (sclk_freq > STANDDARD_FREQ)
    {
        reg_val |= duty;
    }
    else
    {
        reg_val &= ~duty;
    }
#endif
    writel(reg_val, base_addr + TWI_DRIVER_BUSC);
}


/*
* Fin is APB CLOCK INPUT;
* Fsample = F0 = Fin/2^CLK_N;
* F1 = F0/(CLK_M+1);
* Foscl = F1/10 = Fin/(2^CLK_N * (CLK_M+1)*10);
* Foscl is clock SCL;100KHz or 400KHz
*
* clk_in: apb clk clock
* sclk_freq: freqence to set in HZ
*/
static int32_t twi_set_clock(twi_port_t twi_port,
                             uint32_t clk_in, uint32_t sclk_freq)
{
    const uint32_t base_addr = g_twi_regbase[twi->port];

    uint8_t clk_m = 0, clk_n = 0, _2_pow_clk_n = 1;
    uint32_t src_clk      = clk_in / 10;
    uint32_t divider      = src_clk / sclk_freq; /* 400khz or 100khz */
    uint32_t sclk_real    = 0;      /* the real clock frequency */

    if (divider == 0)
    {
        clk_m = 1;
        goto set_clk;
    }

    /*
     * search clk_n and clk_m,from large to small value so
     * that can quickly find suitable m & n.
     */
    while (clk_n < 8)   /* 3bits max value is 8 */
    {
        /* (m+1)*2^n = divider -->m = divider/2^n -1 */
        clk_m = (divider / _2_pow_clk_n) - 1;
        /* clk_m = (divider >> (_2_pow_clk_n>>1))-1 */
        while (clk_m < 16)   /* 4bits max value is 16 */
        {
            /* src_clk/((m+1)*2^n) */
            sclk_real = src_clk / (clk_m + 1) / _2_pow_clk_n;
            if (sclk_real <= sclk_freq)
            {
                goto set_clk;
            }
            else
            {
                clk_m++;
            }
        }
        clk_n++;
        _2_pow_clk_n *= 2; /* mutilple by 2 */
    }

set_clk:
    twi_clk_write_reg(base_addr, sclk_freq, clk_m, clk_n);
    return 0;
}
#endif

static uint32_t twi_drv_query_irq_status(const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_INTC);

    return (reg_val & TWI_DRV_STAT_MASK);
}

static void twi_drv_clear_irq_flag(uint32_t pending_bit, const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_INTC);

    pending_bit &= TWI_DRV_STAT_MASK;
    reg_val |= pending_bit;
    writel(reg_val, base_addr + TWI_DRIVER_INTC);
}

static void twi_clear_pending(const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_INTC);

    reg_val |= TWI_DRV_STAT_MASK;
    writel(reg_val, base_addr + TWI_DRIVER_INTC);
}

/* start TWI transfer */
static void twi_start_xfer(const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_CTRL);

    reg_val |= START_TRAN;
    writel(reg_val, base_addr + TWI_DRIVER_CTRL);
}

/*
 * send DMA RX Req when the data byte number in RECV_FIFO reaches RX_TRIG
 * or Read Packet Tansmission completed with RECV_FIFO not empty
 */
static void twi_set_rx_trig_level(uint32_t val, const unsigned long base_addr)
{
    uint32_t mask = TRIG_MASK;
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_DMAC);

    val = (val & mask) << 16;
    reg_val &= ~(mask << 16);
    reg_val |= val;
    writel(reg_val, base_addr + TWI_DRIVER_DMAC);
}

/* bytes be send as slave device reg address */
static void twi_set_packet_addr_byte(uint32_t val, const unsigned long base_addr)
{
    uint32_t mask = ADDR_BYTE;
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_FMT);

    reg_val &= ~mask;
    val = (val << 16) & mask;
    reg_val |= val;
    writel(reg_val, base_addr + TWI_DRIVER_FMT);
}

/* bytes be send/received as data */
static void twi_set_packet_data_byte(uint32_t val, const unsigned long base_addr)
{
    uint32_t mask = DATA_BYTE;
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_FMT);

    reg_val &= ~mask;
    val &= mask;
    reg_val |= val;
    writel(reg_val, base_addr + TWI_DRIVER_FMT);
}

#if 0
/* interval between each packet in 32*Fscl cycles */
static void twi_set_packet_interval(uint32_t val, const uint32_t base_addr)
{
    uint32_t mask = INTERVAL_MASK;
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_CFG);

    reg_val &= ~mask;
    val <<= 16;
    val &= mask;
    reg_val |= val;
    writel(reg_val, base_addr + TWI_DRIVER_CFG);
}
#endif

/* FIFO data be transmitted as PACKET_CNT packets in current format */
static void twi_set_packet_cnt(uint32_t val, const unsigned long base_addr)
{
    uint32_t mask = PACKET_MASK;
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_CFG);

    reg_val &= ~mask;
    val &= mask;
    reg_val |= val;
    writel(reg_val, base_addr + TWI_DRIVER_CFG);
}

/* do not send slave_id +W */
static void twi_enable_read_tran_mode(const unsigned long base_addr)
{
    uint32_t mask = READ_TRAN;
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_CTRL);

    reg_val |= mask;
    writel(reg_val, base_addr + TWI_DRIVER_CTRL);
}

/* send slave_id + W */
static void twi_disable_read_tran_mode(const unsigned long base_addr)
{
    uint32_t mask = READ_TRAN;
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_CTRL);

    reg_val &= ~mask;
    writel(reg_val, base_addr + TWI_DRIVER_CTRL);
}


static inline void twi_soft_reset(const unsigned long base_addr, unsigned int reg, unsigned int mask)
{
    unsigned int reg_val = readl(base_addr + reg);

    reg_val |= mask;
    writel(reg_val, base_addr + reg);
}

static void twi_enable_tran_irq(uint32_t bitmap, const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_INTC);

    reg_val |= bitmap;
    reg_val &= ~TWI_DRV_STAT_MASK;
    writel(reg_val, base_addr + TWI_DRIVER_INTC);
}

static void twi_disable_tran_irq(uint32_t bitmap, const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_INTC);

    reg_val &= ~bitmap;
    reg_val &= ~TWI_DRV_STAT_MASK;
    writel(reg_val, base_addr + TWI_DRIVER_INTC);
}

static void twi_enable_dma_irq(uint32_t bitmap, const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_DMAC);

    bitmap &= TWI_DRQEN_MASK;
    reg_val |= bitmap;
    writel(reg_val, base_addr + TWI_DRIVER_DMAC);
}

static void twi_disable_dma_irq(uint32_t bitmap, const unsigned long base_addr)
{
    uint32_t reg_val = readl(base_addr + TWI_DRIVER_DMAC);

    bitmap &= TWI_DRQEN_MASK;
    reg_val &= ~bitmap;
    writel(reg_val, base_addr + TWI_DRIVER_DMAC);
}

static void twi_slave_addr(const unsigned long base_addr, twi_msg_t *msgs)
{
    uint32_t val = 0, cmd = 0;

    /* read, default value is write */
    if (msgs->flags & TWI_M_RD)
    {
        cmd = SLV_RD_CMD;
    }

    if (msgs->flags & TWI_M_TEN)
    {
        /* SLV_ID | CMD | SLV_ID_X */
        val = ((0x78 | ((msgs->addr >> 8) & 0x03)) << 9) | cmd
              | (msgs->addr & 0xff);
    }
    else
    {
        val = ((msgs->addr & 0x7f) << 9) | cmd;
    }

    writel(val, base_addr + TWI_DRIVER_SLV);
}


/* the number of data in SEND_FIFO */
static int32_t twi_query_txfifo(const unsigned long base_addr)
{
    uint32_t reg_val;

    reg_val = readl(base_addr + TWI_DRIVER_FIFOC) & SEND_FIFO_CONT;

    return reg_val;
}

/* the number of data in RECV_FIFO */
static int32_t twi_query_rxfifo(const unsigned long base_addr)
{
    uint32_t reg_val;

    reg_val = readl(base_addr + TWI_DRIVER_FIFOC) & RECV_FIFO_CONT;
    reg_val >>= 16;

    return reg_val;
}

static void twi_clear_txfifo(const unsigned long base_addr)
{
    uint32_t reg_val;

    reg_val = readl(base_addr + TWI_DRIVER_FIFOC);
    reg_val |= SEND_FIFO_CLEAR;
    writel(reg_val, base_addr + TWI_DRIVER_FIFOC);
}

static void twi_clear_rxfifo(const unsigned long base_addr)
{
    uint32_t reg_val;

    reg_val = readl(base_addr + TWI_DRIVER_FIFOC);
    reg_val |= RECV_FIFO_CLEAR;
    writel(reg_val, base_addr + TWI_DRIVER_FIFOC);
}

static int twi_send_msgs(hal_twi_t *twi, twi_msg_t *msgs)
{
    uint16_t i;
    uint8_t time = 0xff;

    TWI_INFO("twi[%d] msgs->len = %d", twi->port, msgs->len);

    for (i = 0; i < msgs->len; i++)
    {
        while ((twi_query_txfifo(twi->base_addr) >= MAX_FIFO) && time--)
            ;
        if (time)
        {
            hal_writeb(msgs->buf[i], twi->base_addr + TWI_DRIVER_SENDF);
        }
        else
        {
            TWI_ERR("[twi%d] SEND FIFO overflow. timeout", twi->port);
            return SUNXI_TWI_FAIL;
        }
    }

    return SUNXI_TWI_OK;
}

static uint32_t twi_recv_msgs(hal_twi_t *twi, twi_msg_t *msgs)
{
    uint16_t i;
    uint8_t time = 0xff;

    TWI_INFO("twi[%d] msgs->len = %d", twi->port, msgs->len);

    for (i = 0; i < msgs->len; i++)
    {
        while (!twi_query_rxfifo(twi->base_addr) && time--)
            ;
        if (time)
        {
            msgs->buf[i] = hal_readb(twi->base_addr + TWI_DRIVER_RECVF);
        }
        else
        {
            return 0;
        }
    }
    return msgs->len;
}
/************************ TWI DRV XFER REG CONTROL end*************************/
static void twi_dma_callback(void *para)
{
    hal_twi_t *twi = (hal_twi_t *)para;
    int hal_sem_ret;

    hal_sem_ret = hal_sem_post(twi->dma_complete);
    if (hal_sem_ret != 0)
    {
        TWI_ERR("[twi%d] twi dma driver xfer timeout (dev addr:0x%x)\n", twi->port, twi->msgs->addr);
    return;
    }
}

static int twi_dma_xfer(hal_twi_t *twi, char *buf, int len, enum dma_transfer_direction dir)
{
    struct sunxi_dma_chan *dma_chan = twi->dma_chan;
    struct dma_slave_config slave_config;
    int hal_sem_ret;

    hal_dcache_clean((unsigned long)buf, len);
    hal_dma_callback_install(dma_chan, twi_dma_callback, twi);
    if (dir == DMA_MEM_TO_DEV)
    {
        slave_config.direction = DMA_MEM_TO_DEV;
    slave_config.src_addr = (unsigned long)buf;
    slave_config.dst_addr = twi->base_addr + TWI_DRIVER_SENDF;
        slave_config.slave_id = sunxi_slave_id(DRQDST_TWI0_TX + twi->port, DRQSRC_SDRAM);
    }
    else
    {
        slave_config.direction = DMA_DEV_TO_MEM;
    slave_config.src_addr = twi->base_addr + TWI_DRIVER_RECVF;
    slave_config.dst_addr = (unsigned long)buf;
    slave_config.slave_id = sunxi_slave_id(DRQDST_SDRAM, DRQSRC_TWI0_RX + twi->port);
    }
    slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
    slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
    slave_config.src_maxburst = DMA_SLAVE_BURST_16;
    slave_config.dst_maxburst = DMA_SLAVE_BURST_16;
    hal_dma_slave_config(dma_chan, &slave_config);
    if (dir == DMA_MEM_TO_DEV)
    {
        hal_dma_prep_device(dma_chan, slave_config.dst_addr, slave_config.src_addr, len, DMA_MEM_TO_DEV);
    }
    else
    {
        hal_dma_prep_device(dma_chan, slave_config.dst_addr, slave_config.src_addr, len, DMA_DEV_TO_MEM);
    }

    //hal_dma_cyclic_callback_install(dma_chan, twi_dma_callback, twi);
    hal_dma_start(dma_chan);

    hal_sem_ret = hal_sem_timedwait(twi->dma_complete, twi->timeout * 100);
    if (hal_sem_ret != 0)
    {
        TWI_ERR("[twi%d] twi dma driver xfer timeout (dev addr:0x%x)\n", twi->port, twi->msgs->addr);
    return -1;
    }
    TWI_INFO("[twi%d] twi driver dma xfer success.\n", twi->port);
    TWI_ERR("[twi%d] twi driver dma xfer success.\n", twi->port);
    return 0;
}

static int twi_write(hal_twi_t *twi, twi_msg_t *msgs)
{
    twi->msgs = msgs;

    twi_slave_addr(twi->base_addr, msgs);
    if (msgs->len == 1)
    {
        twi_set_packet_addr_byte(0, twi->base_addr);
        twi_set_packet_data_byte(msgs->len, twi->base_addr);
    }
    else
    {
        twi_set_packet_addr_byte(1, twi->base_addr);
        twi_set_packet_data_byte(msgs->len - 1, twi->base_addr);
    }
    twi_set_packet_cnt(1, twi->base_addr);

    twi_clear_pending(twi->base_addr);
    twi_enable_tran_irq(TRAN_COM_INT | TRAN_ERR_INT, twi->base_addr);
    twi_start_xfer(twi->base_addr);

    return twi_send_msgs(twi, msgs);
}

static int32_t twi_dma_write(hal_twi_t *twi, twi_msg_t *msgs)
{
    int32_t ret = 0;
    const uint32_t base_addr = twi->base_addr;
    twi->msgs = msgs;

    twi_slave_addr(base_addr, msgs);
    twi_set_packet_addr_byte(1, base_addr);
    twi_set_packet_data_byte(msgs->len - 1, base_addr);
    twi_set_packet_cnt(1, base_addr);

    twi_clear_pending(base_addr);
    twi_enable_tran_irq(TRAN_COM_INT | TRAN_ERR_INT, base_addr);
    twi_enable_dma_irq(DMA_TX, base_addr);
    twi_start_xfer(base_addr);

    ret = twi_dma_xfer(twi, msgs->buf, msgs->len, DMA_MEM_TO_DEV);

    return ret;
}

static int twi_read(hal_twi_t *twi, twi_msg_t *msgs, int32_t num)
{
    twi_msg_t *wmsgs = NULL, *rmsgs = NULL;

    if (num == 1)
    {
        wmsgs = NULL;
        rmsgs = msgs;
    }
    else if (num == 2)
    {
        wmsgs = msgs;
        rmsgs = msgs + 1;
    }
    else
    {
        TWI_ERR("msg num err");
        return -1;
    }
    TWI_INFO("rmsgs->len : %d", rmsgs->len);

    twi->msgs = rmsgs;

    twi_slave_addr(twi->base_addr, rmsgs);
    twi_set_packet_cnt(1, twi->base_addr);
    twi_set_packet_data_byte(rmsgs->len, twi->base_addr);
    if (rmsgs->len > MAX_FIFO)
    {
        twi_set_rx_trig_level(MAX_FIFO, twi->base_addr);
    }
    else
    {
        twi_set_rx_trig_level(rmsgs->len, twi->base_addr);
    }
    if (twi_query_rxfifo(twi->base_addr))
    {
        twi_clear_rxfifo(twi->base_addr);
    }

    twi_clear_pending(twi->base_addr);
    twi_enable_tran_irq(TRAN_COM_INT | TRAN_ERR_INT, twi->base_addr);
    twi_start_xfer(twi->base_addr);

    if (wmsgs)
    {
        return twi_send_msgs(twi, wmsgs);
    }

    return 0;
}

static int32_t twi_dma_read(hal_twi_t *twi, twi_msg_t *msgs, int32_t num)
{
    int32_t ret = 0;
    twi_msg_t *wmsgs, *rmsgs;
    const uint32_t base_addr = twi->base_addr;

    if (num == 1)
    {
        wmsgs = NULL;
        rmsgs = msgs;
    }
    else if (num == 2)
    {
        wmsgs = msgs;
        rmsgs = msgs + 1;
    }
    twi->msgs = rmsgs;

    twi_slave_addr(base_addr, rmsgs);
    twi_set_packet_data_byte(rmsgs->len, base_addr);
    twi_set_packet_cnt(1, base_addr);
    twi_set_rx_trig_level(MAX_FIFO / 2, base_addr);
    if (twi_query_rxfifo(base_addr))
    {
        twi_clear_rxfifo(base_addr);
    }

    twi_clear_pending(base_addr);
    twi_enable_tran_irq(TRAN_COM_INT | TRAN_ERR_INT, base_addr);
    twi_enable_dma_irq(DMA_RX, base_addr);
    twi_start_xfer(base_addr);
    if (wmsgs)
    {
        twi_send_msgs(twi, wmsgs);
    }

    ret = twi_dma_xfer(twi, rmsgs->buf, rmsgs->len, DMA_DEV_TO_MEM);

    return ret;
}
/*************************************** TWI DRV XFER REG CONTROL end****************************/

static int hal_twi_drv_complete(hal_twi_t *twi)
{
    int hal_sem_ret;

    hal_sem_ret = hal_sem_timedwait(twi->hal_sem, twi->timeout * 100);
    if (hal_sem_ret < 0)
    {
        TWI_ERR("[twi%d] twi driver xfer timeout (dev addr:0x%x)", twi->port, twi->msgs->addr);
        //dump_reg(twi, 0x200, 0x20);
        twi_disable_tran_irq(TRAN_COM_INT | TRAN_ERR_INT
                             | RX_REQ_INT | TX_REQ_INT, twi->base_addr);
        twi_disable_dma_irq(DMA_TX | DMA_RX, twi->base_addr);
        return SUNXI_TWI_FAIL;
    }
    else if (twi->result == RESULT_ERR)
    {
        TWI_ERR("[twi%d]twi drv xfer incomplete xfer"
                "(status: 0x%lx, dev addr: 0x%x)",
                twi->port, twi->msgs_idx, twi->msgs->addr);
        twi_disable_tran_irq(TRAN_COM_INT | TRAN_ERR_INT
                             | RX_REQ_INT | TX_REQ_INT, twi->base_addr);
        twi_disable_dma_irq(DMA_TX | DMA_RX, twi->base_addr);
        return SUNXI_TWI_FAIL;
    }

    TWI_INFO("twi drv xfer complete");

    //  twin_lock_irqsave(&twi->lock, flags);
    twi->result = RESULT_COMPLETE;
    //  twin_unlock_irqrestore(&twi->lock, flags);

    return SUNXI_TWI_OK;
}

static int hal_twi_engine_complete(hal_twi_t *twi, int code)
{
    int ret = SUNXI_TWI_OK;
    int hal_sem_ret;

    twi->msgs     = NULL;
    twi->msgs_num = 0;
    twi->msgs_ptr = 0;
    twi->status  = TWI_XFER_IDLE;

    /* twi->msgs_idx  store the information */
    if (code == SUNXI_TWI_FAIL)
    {
        TWI_ERR("[twi%d] Maybe Logic Error, debug it!", twi->port);
        twi->msgs_idx = code;
        ret = SUNXI_TWI_FAIL;
        twi->result = RESULT_ERR;
    }
    else if (code != SUNXI_TWI_OK)
    {
        twi->msgs_idx = code;
        ret = SUNXI_TWI_FAIL;
        twi->result = RESULT_ERR;
    }

    hal_sem_ret = hal_sem_post(twi->hal_sem);
    if (hal_sem_ret != 0)
    {
        ret = SUNXI_TWI_FAIL;
        TWI_ERR(" evdev give hal_semaphore err");
    }

    TWI_INFO("code=%d, complete", twi->msgs_idx);

    return ret;
}

/*
 ****************************************************************************
 *
 *  FunctionName:           hal_i2c_addr_byte
 *
 *  Description:
 *         7bits addr: 7-1bits addr+0 bit r/w
 *         10bits addr: 1111_11xx_xxxx_xxxx-->1111_0xx_rw,xxxx_xxxx
 *         send the 7 bits addr,or the first part of 10 bits addr
 *  Parameters:
 *
 *
 *  Return value:
 *           ??
 *  Notes:
 *
 ****************************************************************************
 */
static void hal_twi_addr_byte(hal_twi_t *twi)
{
    unsigned char addr = 0;
    unsigned char tmp  = 0;

    if (twi->msgs[twi->msgs_idx].flags & TWI_M_TEN)
    {
        /* 0111_10xx,ten bits address--9:8bits */
        tmp = 0x78 | (((twi->msgs[twi->msgs_idx].addr) >> 8) & 0x03);
        addr = tmp << 1;    /*1111_0xx0*/
        /* how about the second part of ten bits addr? */
        /* Answer: deal at twi_core_process() */
    }
    else
    {
        addr = (twi->msgs[twi->msgs_idx].addr & 0x7f) << 1;
    }/* 7-1bits addr, xxxx_xxx0 */

    /* read, default value is write */
    if (twi->msgs[twi->msgs_idx].flags & TWI_M_RD)
    {
        addr |= 1;
    }

    if (twi->msgs[twi->msgs_idx].flags & TWI_M_TEN)
    {
        TWI_INFO("[twi%d] first part of 10bits = 0x%x",
                 twi->port, addr);
    }
    else
    {
        TWI_INFO("[twi%d] 7bits+r/w = 0x%x", twi->port, addr);
    }

    /* send 7bits+r/w or the first part of 10bits */
    twi_put_byte(twi->base_addr, &addr);
}

static int hal_twi_core_process(hal_twi_t *twi)
{
    const uint32_t base_addr = twi->base_addr;
    int  ret        = SUNXI_TWI_OK;
    int  err_code   = 0;
    unsigned char  state = 0;
    unsigned char  tmp   = 0;

    state = twi_query_irq_status(base_addr);

    //twin_lock_irqsave(&twi->lock, flags);
    TWI_INFO("[twi%d][slave address = (0x%x), state = (0x%x)]",
             twi->port, twi->msgs->addr, state);
    if (twi->msgs == NULL)
    {
        TWI_ERR("[twi%d] twi message is NULL, err_code = 0xfe",
                twi->port);
        err_code = 0xfe;
        goto msg_null;
    }

    switch (state)
    {
        case 0xf8:
            /* On reset or stop the bus is idle, use only at poll method */
            err_code = 0xf8;
            goto err_out;
        case 0x08: /* A START condition has been transmitted */
        case 0x10: /* A repeated start condition has been transmitted */
            hal_twi_addr_byte(twi);/* send slave address */
            break;
        case 0xd8: /* second addr has transmitted, ACK not received!    */
        case 0x20: /* SLA+W has been transmitted; NOT ACK has been received */
            err_code = 0x20;
            goto err_out;
        case 0x18: /* SLA+W has been transmitted; ACK has been received */
            /* if any, send second part of 10 bits addr */
            if (twi->msgs[twi->msgs_idx].flags & TWI_M_TEN)
            {
                /* the remaining 8 bits of address */
                tmp = twi->msgs[twi->msgs_idx].addr & 0xff;
                twi_put_byte(base_addr, &tmp); /* case 0xd0: */
                break;
            }
            goto send_data;
        /* for 7 bit addr, then directly send data byte--case 0xd0:  */
        case 0xd0: /* second addr has transmitted,ACK received!     */
        case 0x28: /* Data byte in DATA REG has been transmitted; */
            /*  ACK has been received */
            /* after send register address then START send write data  */
send_data:
            if (twi->msgs_ptr < twi->msgs[twi->msgs_idx].len)
            {
                twi_put_byte(base_addr,
                             &(twi->msgs[twi->msgs_idx].buf[twi->msgs_ptr]));
                twi->msgs_ptr++;
                break;
            }

            twi->msgs_idx++; /* the other msg */
            twi->msgs_ptr = 0;
            if (twi->msgs_idx == twi->msgs_num)
            {
                err_code = SUNXI_TWI_OK;/* Success,wakeup */
                goto ok_out;
            }
            else if (twi->msgs_idx < twi->msgs_num)
            {
                /* for restart pattern, read spec, two msgs */
                ret = twi_restart(base_addr, twi->port);
                if (ret == SUNXI_TWI_FAIL)
                {
                    TWI_ERR("[twi%d] twi restart fail", twi->port);
                    err_code = SUNXI_TWI_FAIL;
                    goto err_out;/* START can't sendout */
                }
            }
            else
            {
                err_code = SUNXI_TWI_FAIL;
                goto err_out;
            }
            break;
        case 0x30: /* Data byte in TWIDAT has been transmitted; */
            /* NOT ACK has been received */
            err_code = 0x30;    /*err,wakeup the thread*/
            goto err_out;
        case 0x38: /* Arbitration lost during SLA+W, SLA+R or data bytes */
            err_code = 0x38;    /*err,wakeup the thread*/
            goto err_out;
        case 0x40: /* SLA+R has been transmitted; ACK has been received */
            /* with Restart,needn't to send second part of 10 bits addr */
            /* refer-"TWI-SPEC v2.1" */
            /* enable A_ACK need it(receive data len) more than 1. */
            if (twi->msgs[twi->msgs_idx].len > 1)
            {
                /* send register addr complete,then enable the A_ACK */
                /* and get ready for receiving data */
                twi_enable_ack(base_addr);
                twi_clear_irq_flag(base_addr);/* jump to case 0x50 */
            }
            else if (twi->msgs[twi->msgs_idx].len == 1)
            {
                twi_clear_irq_flag(base_addr);/* jump to case 0x58 */
            }
            break;
        case 0x48: /* SLA+R has been transmitted; NOT ACK has been received */
            err_code = 0x48;    /*err,wakeup the thread*/
            goto err_out;
        case 0x50: /* Data bytes has been received; ACK has been transmitted */
            /* receive first data byte */
            if (twi->msgs_ptr < twi->msgs[twi->msgs_idx].len)
            {
                /* more than 2 bytes, the last byte need not to send ACK */
                if ((twi->msgs_ptr + 2) == twi->msgs[twi->msgs_idx].len)
                    /* last byte no ACK */
                {
                    twi_disable_ack(base_addr);
                }

                /* get data then clear flag,then next data coming */
                twi_get_byte(base_addr,
                             &twi->msgs[twi->msgs_idx].buf[twi->msgs_ptr]);
                twi->msgs_ptr++;
                break;
            }
            /* err process, the last byte should be @case 0x58 */
            err_code = SUNXI_TWI_FAIL;/* err, wakeup */
            goto err_out;
        case 0x58:
            /* Data byte has been received; NOT ACK has been transmitted */
            /* received the last byte  */
            if (twi->msgs_ptr == twi->msgs[twi->msgs_idx].len - 1)
            {
                twi_get_last_byte(base_addr,
                                  &twi->msgs[twi->msgs_idx].buf[twi->msgs_ptr]);
                twi->msgs_idx++;
                twi->msgs_ptr = 0;
                if (twi->msgs_idx == twi->msgs_num)
                {
                    /* succeed,wakeup the thread */
                    err_code = SUNXI_TWI_OK;
                    goto ok_out;
                }
                else if (twi->msgs_idx < twi->msgs_num)
                {
                    /* repeat start */
                    ret = twi_restart(base_addr, twi->port);
                    if (ret == SUNXI_TWI_FAIL)  /* START fail */
                    {
                        TWI_ERR("[twi%d] twi restart fail", twi->port);
                        err_code = SUNXI_TWI_FAIL;
                        goto err_out;
                    }
                    break;
                }
            }
            else
            {
                err_code = 0x58;
                goto err_out;
            }
            break;
        case 0x00: /* Bus error during master or slave mode due to illegal level condition */
            err_code = 0xff;
            goto err_out;
        default:
            err_code = state;
            goto err_out;
    }
    //twin_unlock_irqrestore(&twi->lock, flags);
    return ret;

ok_out:
err_out:
    if (twi_stop(base_addr, twi->port) == SUNXI_TWI_FAIL)
    {
        TWI_ERR("[twi%d] STOP failed!", twi->port);
    }

msg_null:
    ret = hal_twi_engine_complete(twi, err_code);/* wake up */
    //twin_unlock_irqrestore(&twi->lock, flags);
    return ret;
}


static int hal_twi_drv_core_process(hal_twi_t *twi)
{
    int ret = SUNXI_TWI_OK;
    uint32_t status, code = 0;
    int hal_sem_ret, taskwoken = 0;

    //  twin_lock_irqsave(&twi->lock, flags);

    status = twi_drv_query_irq_status(twi->base_addr);
    twi_drv_clear_irq_flag(status, twi->base_addr);

    if (status & TRAN_COM_PD)
    {
        TWI_INFO("twi drv complete");
        twi_disable_tran_irq(TRAN_COM_INT, twi->base_addr);
        twi->result = RESULT_COMPLETE;

        if ((status & RX_REQ_PD) && (twi->msgs->len < DMA_THRESHOLD))
        {
            twi_recv_msgs(twi, twi->msgs);
        }
        goto ok_out;
    }

    if (status & TRAN_ERR_PD)
    {
        TWI_ERR("twi drv error");
        twi_disable_tran_irq(TRAN_ERR_INT, twi->base_addr);
        code = readl(twi->base_addr + TWI_DRIVER_CTRL);
        code = (code & TWI_DRV_STA) >> 16;
        TWI_ERR("err code : %0lx", code);
        switch (code)
        {
            case 0x00:
                TWI_ERR("[twi%d] bus error", twi->port);
                break;
            case 0x01:
                TWI_ERR("[twi%d] Timeout when sending 9th SCL clk", twi->port);
                break;
            case 0x20:
                TWI_ERR("[twi%d] Address + Write bit transmitted,"
                        "ACK not received", twi->port);
                break;
            case 0x30:
                TWI_ERR("[twi%d] Data byte transmitted in master mode,"
                        "ACK not received", twi->port);
                break;
            case 0x38:
                TWI_ERR("[twi%d] Arbitration lost in address"
                        "or data byte", twi->port);
                break;
            case 0x48:
                TWI_ERR("[twi%d] Address + Read bit transmitted,"
                        "ACK not received", twi->port);
                break;
            case 0x58:
                TWI_ERR("[twi%d] Data byte received in master mode,"
                        "ACK not received", twi->port);
                break;
            default:
                TWI_ERR("[twi%d] unknown error", twi->port);
                break;
        }
        goto err_out;
    }

err_out:
    twi->msgs_idx = code;
    twi->result = RESULT_ERR;
    TWI_ERR("packet transmission failed , status : 0x%0lx", code);

ok_out:
    //wake up
    hal_sem_ret = hal_sem_post(twi->hal_sem);
    if (hal_sem_ret != 0)
    {
        ret = SUNXI_TWI_FAIL;
        TWI_ERR(" evdev give hal_semaphore err");
    }

    return ret;
    //  twin_unlock_irqrestore(&twi->lock, flags);
}

static irqreturn_t hal_twi_handler(int irq, void *dev)
{
    hal_twi_t *twi = (hal_twi_t *)dev;

    if (twi->twi_drv_used)
    {
        hal_twi_drv_core_process(twi);
    }
    else
    {
        if (!twi_query_irq_flag(twi->base_addr))
        {
            TWI_ERR("unknown interrupt!");
            return 0;
        }

        /* disable irq */
        twi_disable_irq(twi->base_addr);

        /* twi core process */
        hal_twi_core_process(twi);

        /*
         * enable irq only when twi is transferring,
         * otherwise disable irq
         */
        if (twi->status != TWI_XFER_IDLE)
        {
            twi_enable_irq(twi->base_addr);
        }
    }
    return 0;
}

/**
 * twi_do_xfer - twi driver transmission control
 */
static int hal_twi_drv_do_xfer(hal_twi_t *twi, struct twi_msg *msgs, int num)
{
    //  uint64_t flags = 0;
    int ret = -1;

    //  twin_lock_irqsave(&twi->lock, flags);
    //  twi->result = 0;
    //  twin_unlock_irqrestore(&twi->lock, flags);

    twi_clear_pending(twi->base_addr);
    twi_disable_tran_irq(TRAN_COM_INT | TRAN_ERR_INT
                         | RX_REQ_INT | TX_REQ_INT, twi->base_addr);
    twi_disable_dma_irq(DMA_TX | DMA_RX, twi->base_addr);
    if (twi_query_txfifo(twi->base_addr))
    {
        twi_clear_txfifo(twi->base_addr);
    }

    if (num == 1)
    {
        if (msgs->flags & TWI_M_RD)
        {
            TWI_INFO("1 msgs read ");
            /* 1 msgs read */
            twi_enable_read_tran_mode(twi->base_addr);
            twi_set_packet_addr_byte(0, twi->base_addr);
            if (twi->dma_chan && (msgs->len >= DMA_THRESHOLD))
            {
                TWI_INFO("twi[%d] master dma read", twi->port);
                ret =  twi_dma_read(twi, msgs, num);
            }
            else
            {
                TWI_INFO("twi[%d] master cpu read", twi->port);
                ret = twi_read(twi, msgs, num);
            }
        }
        else
        {
            /* 1 msgs write */
            twi_disable_read_tran_mode(twi->base_addr);
            if (twi->dma_chan && (msgs->len >= DMA_THRESHOLD))
            {
                TWI_INFO("twi[%d] master dma write\n", twi->port);
                ret = twi_dma_write(twi, msgs);
            }
            else
            {
                TWI_INFO("twi[%d] master cpu write\n", twi->port);
                ret = twi_write(twi, msgs);
            }
        }
    }
    else if ((num == 2) && ((msgs + 1)->flags & TWI_M_RD))
    {
        /* 2 msgs read */
        TWI_INFO("2 msgs read");
        twi_disable_read_tran_mode(twi->base_addr);
        twi_set_packet_addr_byte(msgs->len, twi->base_addr);
        if (twi->dma_chan && ((msgs + 1)->len >= DMA_THRESHOLD))
        {
            TWI_INFO("twi[%d] master dma read\n", twi->port);
            ret =  twi_dma_read(twi, msgs, num);
        }
        else
        {
            TWI_INFO("twi[%d] master cpu read\n", twi->port);
            ret = twi_read(twi, msgs, num);
        }
    }

    if (ret)
    {
        return ret;
    }

    return hal_twi_drv_complete(twi);
}

static int hal_twi_engine_do_xfer(hal_twi_t *twi, twi_msg_t *msgs, int num)
{
    int ret;

    const uint32_t base_addr = twi->base_addr;
    int hal_sem_ret;

    twi_soft_reset(base_addr, TWI_SRST_REG, TWI_SRST_SRST);
    //udelay(100);

    /* test the bus is free,already protect by the hal_semaphore at DEV layer */
    while (twi_query_irq_status(base_addr) != TWI_STAT_IDLE &&
           twi_query_irq_status(base_addr) != TWI_STAT_BUS_ERR &&
           twi_query_irq_status(base_addr) != TWI_STAT_ARBLOST_SLAR_ACK)
    {
        TWI_ERR("[twi%d] bus is busy, status = %x",
                twi->port, twi_query_irq_status(base_addr));
        if (twi_send_clk_9pulse(base_addr, twi->port) != SUNXI_TWI_OK)
        {
            ret = SUNXI_TWI_RETRY;
            goto out;
        }
        else
        {
            break;
        }
    }

    /* may conflict with xfer_complete */
    //twin_lock_irqsave(&twi->lock, flags);
    twi->msgs    = msgs;
    twi->msgs_num = num;
    twi->msgs_ptr = 0;
    twi->msgs_idx = 0;
    twi_enable_irq(base_addr);  /* enable irq */
    twi_disable_ack(base_addr); /* disabe ACK */
    /* set the special function register,default:0. */
    twi_set_efr(base_addr, 0);
    //twin_unlock_irqrestore(&twi->lock, flags);

    /* START signal, needn't clear int flag */
    twi->status  = TWI_XFER_START;
    ret = twi_start(base_addr, twi->port);
    if (ret == SUNXI_TWI_FAIL)
    {
        TWI_ERR("[twi%d] twi start fail", twi->port);
        twi_soft_reset(base_addr, TWI_SRST_REG, TWI_SRST_SRST);
        twi_disable_irq(base_addr);  /* disable irq */
        ret = SUNXI_TWI_RETRY;
        goto out;
    }

    twi->status  = TWI_XFER_RUNNING;
    /* sleep and wait,do the transfer at interrupt handler,timeout = 5*HZ */
    hal_sem_ret = hal_sem_timedwait(twi->hal_sem, twi->timeout * 100);
    /* return code,if(msgs_idx == num) succeed */
    ret = twi->msgs_idx;
    if (hal_sem_ret != 0)
    {
        TWI_ERR("[twi%d] xfer timeout (dev addr:0x%x)",
                twi->port, msgs->addr);
        //twin_lock_irqsave(&twi->lock, flags);
        twi->msgs = NULL;
        //twin_unlock_irqrestore(&twi->lock, flags);
        ret = SUNXI_TWI_FAIL;
    }
    else if (ret != num)
    {
        TWI_ERR("[twi%d] incomplete xfer (status: 0x%x, dev addr: 0x%x)",
                twi->port, ret, msgs->addr);
        ret = SUNXI_TWI_FAIL;
    }

    TWI_INFO("hal_twi_engine_do_xfer end");
out:
    return ret;
}

twi_status_t hal_twi_xfer(twi_port_t port, twi_msg_t *msgs, int32_t num)
{
    hal_twi_t *twi = &hal_twi[port];
    int ret;

    if ((msgs == NULL) || (num <= 0))
    {
        TWI_ERR("[twi%d] invalid argument", port);
        return TWI_STATUS_INVALID_PARAMETER;
    }

    if (twi->twi_drv_used)
    {
        TWI_INFO("[twi%d] twi driver xfer", twi->port);
        ret = hal_twi_drv_do_xfer(twi, msgs, num);
        if (ret < 0)
        {
            return TWI_STATUS_ERROR;
        }
    }
    else
    {
        TWI_INFO("[twi%d] twi engine xfer", twi->port);
        ret = hal_twi_engine_do_xfer(twi, msgs, num);
        if (ret < 0)
        {
            return TWI_STATUS_ERROR;
        }
    }

    return ret == num ? TWI_STATUS_OK : TWI_STATUS_ERROR;
}

static twi_status_t hal_twi_sys_pinctrl_init(hal_twi_t *twi)
{
#ifdef CONFIG_RTTKERNEL
    user_gpio_set_t gpio_cfg[2] = {0};
    int count, i;
    char twi_name[16];
    int ret = TWI_STATUS_OK;

    sprintf(twi_name, "twi%d", twi->port);
    count = Hal_Cfg_GetGPIOSecKeyCount(twi_name);
    if (!count)
    {
        TWI_ERR("[twi%d] not support in sys_config\n", twi->port);
        return TWI_STATUS_ERROR;
    }
    Hal_Cfg_GetGPIOSecData(twi_name, gpio_cfg, count);

    for (i = 0; i < count; i++) {
        twi->pin[i] = (gpio_cfg[i].port - 1) * 32 + gpio_cfg[i].port_num;
        twi->pinmux = gpio_cfg[i].mul_sel;
        ret = hal_gpio_pinmux_set_function(twi->pin[i], twi->pinmux);
        if (ret){
            TWI_ERR("[twi%d] PIN%u set function failed! return %d\n",
                    twi->port, twi->pin[i], ret);
            return TWI_STATUS_ERROR;
        }

        ret = hal_gpio_set_driving_level(twi->pin[i], gpio_cfg[i].drv_level);
        if (ret) {
            TWI_ERR("[twi%d] PIN%u set driving level failed! return %d\n",
                    twi->port, gpio_cfg[i].drv_level, ret);
            return TWI_STATUS_ERROR;
        }

        if (gpio_cfg[i].pull)
            if (hal_gpio_set_pull(twi->pin[i], gpio_cfg[i].pull))
                return TWI_STATUS_ERROR;
    }

    return TWI_STATUS_OK;
#endif
    TWI_ERR("twi[%d] not support sys_config format \n", twi->port);
    return TWI_STATUS_ERROR;
}

static twi_status_t hal_twi_pinctrl_init(hal_twi_t *twi)
{
    uint8_t i;

    switch (twi->port)
    {
        case TWI_MASTER_0:
            twi->pin[0] = TWI0_SCK;
            twi->pin[1] = TWI0_SDA;
            twi->pinmux = TWI0_PIN_MUXSEL;
            break;
        case TWI_MASTER_1:
            twi->pin[0] = TWI1_SCK;
            twi->pin[1] = TWI1_SDA;
            twi->pinmux = TWI1_PIN_MUXSEL;
            break;
        case TWI_MASTER_2:
            twi->pin[0] = TWI2_SCK;
            twi->pin[1] = TWI2_SDA;
            twi->pinmux = TWI2_PIN_MUXSEL;
            break;
        case TWI_MASTER_3:
            twi->pin[0] = TWI3_SCK;
            twi->pin[1] = TWI3_SDA;
            twi->pinmux = TWI3_PIN_MUXSEL;
            break;
        case S_TWI_MASTER_0:
#if !(defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1))
        twi->pin[0] = S_TWI0_SCK;
        twi->pin[1] = S_TWI0_SDA;
        twi->pinmux = S_TWI0_PIN_MUXSEL;
#endif
        break;
    }

    for (i = 0; i < TWI_PIN_NUM; i++)
    {
        if (hal_gpio_pinmux_set_function(twi->pin[i], twi->pinmux))
        {
            TWI_ERR("[twi%d] PIN set function failed!", twi->port);
            return TWI_STATUS_ERROR;
        }

        if (hal_gpio_set_driving_level(twi->pin[i], TWI_DRIVE_STATE))
        {
            TWI_ERR("[twi%d] PIN set driving failed!", twi->port);
            return TWI_STATUS_ERROR;
        }

        if (hal_gpio_set_pull(twi->pin[i], TWI_PULL_STATE))
        {
            TWI_ERR("[twi%d] PIN set driving failed!", twi->port);
            return TWI_STATUS_ERROR;
        }
    }

    return TWI_STATUS_OK;
}

static twi_status_t hal_twi_pinctrl_exit(hal_twi_t *twi)
{
    uint8_t i;

    for (i = 0; i < TWI_PIN_NUM; i++)
    {
        if (hal_gpio_pinmux_set_function(twi->pin[i], TWI_DISABLE_PIN_MUXSEL))
        {
            TWI_ERR("[twi%d] PIN exit function failed!", twi->port);
            return TWI_STATUS_ERROR;
        }
    }

    return TWI_STATUS_OK;
}

static twi_status_t hal_twi_regulator_init(hal_twi_t *twi)
{
    enum REGULATOR_TYPE_ENUM regulator_type = twi_regulator_type;
    enum REGULATOR_ID_ENUM regulator_id = twi_regulator_id[twi->port];

    int tar_vol = twi_vol[twi->port];
    int ret;
/*
    if (regulator_id == AXP2101_ID_MAX)
    {
        TWI_INFO("[twi%d] needn't to set regulator", twi->port);
        return TWI_STATUS_OK;
    }

    hal_regulator_get(REGULATOR_GET(regulator_type, regulator_id), &twi->regulator);

    ret = hal_regulator_set_voltage(&twi->regulator, tar_vol);
    if (ret)
    {
        TWI_ERR("twi%d set voltage failed", twi->port);
        return TWI_STATUS_ERROR;
    }

    ret = hal_regulator_enable(&twi->regulator);
    if (ret)
    {
        TWI_ERR("twi%d enabled regulator failed", twi->port);
        return TWI_STATUS_ERROR;
    }
*/
    return TWI_STATUS_OK;
}

static twi_status_t hal_twi_regulator_exit(hal_twi_t *twi)
{
    int ret;

    enum REGULATOR_ID_ENUM regulator_id = twi_regulator_id[twi->port];

    if (regulator_id == AXP2101_ID_MAX)
    {
        TWI_INFO("[twi%d] needn't to exit regulator", twi->port);
        return TWI_STATUS_OK;
    }

    ret = hal_regulator_disable(&twi->regulator);

    if (ret)
    {
        TWI_ERR("twi%d disable regulator failed\n", twi->port);
        return TWI_STATUS_ERROR;
    }

    return TWI_STATUS_OK;
}

static twi_status_t hal_twi_clk_init(hal_twi_t *twi)
{
    unsigned long rate;
    /*
        if (hal_clk_set_parent(twi->mclk, twi->pclk)) {
            TWI_ERR("[twi%d] clk set parent failed!",twi->port);
        return TWI_STATUS_ERROR;
        }
    */
#if !(defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1))
    rate = hal_clk_get_rate(twi->pclk);

    if (hal_clock_enable(twi->mclk))
    {
        TWI_ERR("[twi%d] clk enable mclk failed!", twi->port);
        return TWI_STATUS_ERROR;
    }

#else
    rate =24000000;
    hal_clk_type_t  clk_type = HAL_SUNXI_CCU;
    hal_clk_id_t    twi_clk_id;
    hal_clk_t       clk;

    hal_reset_type_t    reset_type = HAL_SUNXI_RESET;
    hal_reset_id_t  twi_reset_id;
    struct reset_control *reset;

    switch (twi->port)
    {
        case 0:
            twi_clk_id = SUNXI_CLK_TWI(0);
            twi_reset_id = SUNXI_CLK_RST_TWI(0);
            break;
        case 1:
            twi_clk_id = SUNXI_CLK_TWI(1);
            twi_reset_id = SUNXI_CLK_RST_TWI(1);
            break;
        case 2:
            twi_clk_id = SUNXI_CLK_TWI(2);
            twi_reset_id = SUNXI_CLK_RST_TWI(2);
            break;
        case 3:
            twi_clk_id = SUNXI_CLK_TWI(3);
            twi_reset_id = SUNXI_CLK_RST_TWI(3);
            break;
        default:
            TWI_ERR("twi%d is invalid\n", twi->port);
            return TWI_STATUS_ERROR;
    }

    reset = hal_reset_control_get(reset_type, twi_reset_id);
    if (!reset)
    {
    TWI_ERR("twi reset control get error");
        return TWI_STATUS_ERROR;
    }
    hal_reset_control_deassert(reset);
    hal_reset_control_put(reset);

    clk = hal_clock_get(clk_type, twi_clk_id);
    if (!clk)
    {
        TWI_ERR("twi clock get error ");
        return TWI_STATUS_ERROR;
    }
    hal_clock_enable(clk);
#endif

    if (twi->twi_drv_used)
    {
        twi_set_clock(twi, TWI_DRIVER_BUSC, 24000000, twi->freq,
                      TWI_DRV_CLK_M, TWI_DRV_CLK_N);
        twi_enable(twi->base_addr, TWI_DRIVER_CTRL, TWI_DRV_EN);
    }
    else
    {
        twi_set_clock(twi, TWI_CLK_REG, rate, twi->freq,
                      TWI_CLK_DIV_M, TWI_CLK_DIV_N);
        twi_enable(twi->base_addr, TWI_CTL_REG, TWI_CTL_BUSEN);
    }

    return TWI_STATUS_OK;
}

static void hal_twi_clk_exit(hal_twi_t *twi)
{
    /* disable twi bus */
    twi_disable(twi->base_addr, TWI_DRIVER_CTRL, TWI_DRV_EN);

    //hal_clock_disable(twi->mclk);
}

twi_status_t hal_twi_init(twi_port_t port)
{
    int ret;
    unsigned long rate;

    hal_twi_t *twi = &hal_twi[port];

    if (twi->already_init) //if twi has been inited, return ok
    {
        return TWI_STATUS_OK;
    }

    twi->port = port;
    twi->base_addr = hal_twi_address[twi->port];
    twi->irqnum = hal_twi_irq_num[twi->port];

#if !(defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1))
    twi->pclk = hal_twi_pclk[port];
    twi->mclk = hal_twi_mclk[port];
#endif

    twi->freq = TWI_FREQUENCY_400K;
#if 1
    twi->twi_drv_used = ENGINE_XFER;
#else
    twi->twi_drv_used = TWI_DRV_XFER;
#endif
    twi->status = TWI_XFER_IDLE;
    twi->timeout = 5;
    twi->flags = 0;

    twi->hal_sem = hal_sem_create(0);
    if (twi->hal_sem == NULL)
    {
        TWI_ERR("[twi%d] creating hal semaphore failed.", port);
        goto errsem;
    }

    if (twi->twi_drv_used)
    {
        twi->dma_complete = hal_sem_create(0);
    if (twi->dma_complete == NULL)
    {
            TWI_ERR("[twi%d] creating dma semaphore failed.\n", port);
        goto errsem_dma;
    }
    }

#if !(defined(CONFIG_ARCH_SUN8IW18P1) || defined(CONFIG_SOC_SUN20IW1))
    if (hal_twi_regulator_init(twi))
    {
        TWI_ERR("[twi%d] regulator init error", port);
        goto errregu;
    }
#endif

    if (hal_twi_clk_init(twi))
    {
        TWI_ERR("[twi%d] clk init error", port);
        goto errclk;
    }

    if (hal_twi_sys_pinctrl_init(twi)) {
        if (hal_twi_pinctrl_init(twi)) {
            TWI_ERR("[twi%d] pinctrl init error", port);
            goto errpin;
        }
    }

    if (request_irq(twi->irqnum, hal_twi_handler, 0, "twi-ctl", twi) < 0)
    {
        TWI_ERR("[twi%d] request irq error", twi->port);
        goto errirq;
    }

    enable_irq(twi->irqnum);

    if (twi->twi_drv_used)
    {
        hal_dma_chan_request(&twi->dma_chan);
    }

    twi->already_init++;

    return TWI_STATUS_OK;

errirq:
    free_irq(twi->irqnum, twi);
errpin:
    hal_twi_pinctrl_exit(twi);
errclk:
    hal_twi_clk_exit(twi);

#if !(defined(CONFIG_ARCH_SUN8IW18P1) || defined(CONFIG_SOC_SUN20IW1))
errregu:
    hal_twi_regulator_exit(twi);
#endif
errsem_dma:
    if (twi->twi_drv_used)
    {
        hal_sem_delete(twi->dma_complete);
    }
errsem:
    hal_sem_delete(twi->hal_sem);

    return TWI_STATUS_ERROR;
}

twi_status_t hal_twi_uninit(twi_port_t port)
{
    hal_twi_t *twi = &hal_twi[port];

    if (twi->already_init > 0)
    {
        twi->already_init--;
        if (twi->already_init == 0)
        {
            disable_irq(twi->irqnum);
            free_irq(twi->irqnum, twi);
            hal_twi_pinctrl_exit(twi);
        if (twi->twi_drv_used)
        {
                hal_dma_chan_free(twi->dma_chan);
        }
            hal_twi_clk_exit(twi);
#if !defined(CONFIG_ARCH_SUN8IW18P1)
            hal_twi_regulator_exit(twi);
#endif
            hal_sem_delete(twi->hal_sem);
        }
    }
    return TWI_STATUS_OK;
}

twi_status_t hal_twi_write(twi_port_t port, unsigned long pos, const void *buf, uint32_t size)
{
    twi_msg_t msg;
    uint8_t num = 1, i = 0;
    uint8_t *msg_buf;
    uint8_t *buf1 = (uint8_t *)buf;
    hal_twi_t *twi = &hal_twi[port];

    msg_buf = (uint8_t *)malloc(sizeof(uint8_t) * (size + 1));
    if (!msg_buf)
    {
        return TWI_STATUS_ERROR;
    }

    memset(msg_buf, 0x00, sizeof(uint8_t) * (size + 1));
    msg_buf[0] = (int8_t)pos;
    for (i = 0; i < size; i++)
    {
        msg_buf[i + 1] = buf1[i];
    }

    msg.addr =  twi->slave_addr;
    msg.flags = twi->flags & TWI_M_TEN;
    msg.flags &= ~(TWI_M_RD);
    msg.len = (size + 1);
    msg.buf = msg_buf;
    return hal_twi_xfer(port, &msg, num);
}

twi_status_t hal_twi_read(twi_port_t port, unsigned long pos, void *buf, uint32_t size)
{
    twi_msg_t msg[2];
    uint8_t num = 2, index = 0;

    hal_twi_t *twi = &hal_twi[port];

    index = (uint8_t)pos;
    msg[0].addr =  twi->slave_addr;
    msg[0].flags = twi->flags & TWI_M_TEN;
    msg[0].flags &= ~(TWI_M_RD);
    msg[0].len = 1;
    msg[0].buf = &index;

    msg[1].addr =  twi->slave_addr;
    msg[1].flags = twi->flags & TWI_M_TEN;
    msg[1].flags |= TWI_M_RD;
    msg[1].len = size;
    msg[1].buf = buf;

    return hal_twi_xfer(port, msg, num);
}

twi_status_t hal_twi_control(twi_port_t port, hal_twi_transfer_cmd_t cmd, void *args)
{
    hal_twi_t *twi = &hal_twi[port];
    twi_msg_t *msg;
    uint16_t *arg;

    switch (cmd)
    {
        case I2C_SLAVE:
        case I2C_SLAVE_FORCE:
            arg = (uint16_t *)args;
            if (*arg > 0x7ff)
            {
                return TWI_STATUS_INVALID_PARAMETER;
            }
            else if (twi->status != TWI_XFER_IDLE)
            {
                return TWI_STATUS_ERROR_BUSY;
            }
            twi->slave_addr = *arg;
            return TWI_STATUS_OK;
        case I2C_TENBIT:
            arg = (uint16_t *)args;
            if (*arg)
            {
                twi->flags |= TWI_M_TEN;
            }
            else
            {
                twi->flags &= ~TWI_M_TEN;
            }
            return TWI_STATUS_OK;
        case I2C_RDWR:
            msg = (twi_msg_t *)args;
            return hal_twi_xfer(port, msg, 1);
        default:
            return TWI_STATUS_INVALID_PARAMETER;
    }
}
