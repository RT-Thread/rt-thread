#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_gpio.h"


#define I2C_DEBUG   0

#if I2C_DEBUG
#define I2C_DBG(...)     rt_kprintf("[I2C]"),rt_kprintf(__VA_ARGS__)
#else
#define I2C_DBG(...)
#endif

#define I2C_CTRL        (0x00)
#define I2C_TAR         (0x04)
#define I2C_SAR         (0x08)
#define I2C_DC          (0x10)
#define I2C_SHCNT       (0x14)
#define I2C_SLCNT       (0x18)
#define I2C_FHCNT       (0x1C)
#define I2C_FLCNT       (0x20)
#define I2C_INTST       (0x2C)
#define I2C_INTM        (0x30)
#define I2C_RXTL        (0x38)
#define I2C_TXTL        (0x3c)
#define I2C_CINTR       (0x40)
#define I2C_CRXUF       (0x44)
#define I2C_CRXOF       (0x48)
#define I2C_CTXOF       (0x4C)
#define I2C_CRXREQ      (0x50)
#define I2C_CTXABRT     (0x54)
#define I2C_CRXDONE     (0x58)
#define I2C_CACT        (0x5C)
#define I2C_CSTP        (0x60)
#define I2C_CSTT        (0x64)
#define I2C_CGC         (0x68)
#define I2C_ENB         (0x6C)
#define I2C_STA         (0x70)
#define I2C_TXFLR       (0x74)
#define I2C_RXFLR       (0x78)
#define I2C_SDAHD       (0x7C)
#define I2C_TXABRT      (0x80)
#define I2C_DMACR       (0x88)
#define I2C_DMATDLR     (0x8c)
#define I2C_DMARDLR     (0x90)
#define I2C_SDASU       (0x94)
#define I2C_ACKGC       (0x98)
#define I2C_ENSTA       (0x9C)
#define I2C_FLT         (0xA0)

/* I2C Control Register (I2C_CTRL) */
#define I2C_CTRL_SLVDIS (1 << 6)    /* after reset slave is disabled */
#define I2C_CTRL_REST   (1 << 5)
#define I2C_CTRL_MATP   (1 << 4)    /* 1: 10bit address 0: 7bit addressing */
#define I2C_CTRL_SATP   (1 << 3)    /* 1: 10bit address 0: 7bit address */
#define I2C_CTRL_SPDF   (2 << 1)    /* fast mode 400kbps */
#define I2C_CTRL_SPDS   (1 << 1)    /* standard mode 100kbps */
#define I2C_CTRL_MD     (1 << 0)    /* master enabled */

/* I2C Status Register (I2C_STA) */
#define I2C_STA_SLVACT  (1 << 6)    /* Slave FSM is not in IDLE state */
#define I2C_STA_MSTACT  (1 << 5)    /* Master FSM is not in IDLE state */
#define I2C_STA_RFF     (1 << 4)    /* RFIFO if full */
#define I2C_STA_RFNE    (1 << 3)    /* RFIFO is not empty */
#define I2C_STA_TFE     (1 << 2)    /* TFIFO is empty */
#define I2C_STA_TFNF    (1 << 1)    /* TFIFO is not full  */
#define I2C_STA_ACT     (1 << 0)    /* I2C Activity Status */

/* i2c interrupt status (I2C_INTST) */
#define I2C_INTST_IGC       (1 << 11)
#define I2C_INTST_ISTT      (1 << 10)
#define I2C_INTST_ISTP      (1 << 9)
#define I2C_INTST_IACT      (1 << 8)
#define I2C_INTST_RXDN      (1 << 7)
#define I2C_INTST_TXABT     (1 << 6)
#define I2C_INTST_RDREQ     (1 << 5)
#define I2C_INTST_TXEMP     (1 << 4)
#define I2C_INTST_TXOF      (1 << 3)
#define I2C_INTST_RXFL      (1 << 2)
#define I2C_INTST_RXOF      (1 << 1)
#define I2C_INTST_RXUF      (1 << 0)

/* i2c interrupt mask status (I2C_INTM) */
#define I2C_INTM_MIGC       (1 << 11)
#define I2C_INTM_MISTT      (1 << 10)
#define I2C_INTM_MISTP      (1 << 9)
#define I2C_INTM_MIACT      (1 << 8)
#define I2C_INTM_MRXDN      (1 << 7)
#define I2C_INTM_MTXABT     (1 << 6)
#define I2C_INTM_MRDREQ     (1 << 5)
#define I2C_INTM_MTXEMP     (1 << 4)
#define I2C_INTM_MTXOF      (1 << 3)
#define I2C_INTM_MRXFL      (1 << 2)
#define I2C_INTM_MRXOF      (1 << 1)
#define I2C_INTM_MRXUF      (1 << 0)

#define I2C_DC_REST         (1 << 10)
#define I2C_DC_STP          (1 << 9)
#define I2C_DC_READ         (1 << 8)

#define I2C_ENB_I2CENB      (1 << 0)    /* Enable the i2c */

#define CONFIG_I2C_FIFO_LEN	64
#define I2C_FIFO_LEN		(CONFIG_I2C_FIFO_LEN)
#define TX_LEVEL			(I2C_FIFO_LEN / 2)
#define RX_LEVEL			(I2C_FIFO_LEN / 2 - 1)

#define TIMEOUT				0xff

/*
 *  msg_end_type: The bus control which need to be send at end of transfer.
 *  @MSG_END_STOP: Send stop pulse at end of transfer.
 *  @MSG_END_REPEAT_START: Send repeat start at end of transfer.
 */
enum msg_end_type
{
	MSG_END_STOP,
	MSG_END_CONTINUE,
	MSG_END_REPEAT_START,
};

/* I2C standard mode high count register(I2CSHCNT) */
#define I2CSHCNT_ADJUST(n)      (((n) - 8) < 6 ? 6 : ((n) - 8))
/* I2C standard mode low count register(I2CSLCNT) */
#define I2CSLCNT_ADJUST(n)      (((n) - 1) < 8 ? 8 : ((n) - 1))
/* I2C fast mode high count register(I2CFHCNT) */
#define I2CFHCNT_ADJUST(n)      (((n) - 8) < 6 ? 6 : ((n) - 8))
/* I2C fast mode low count register(I2CFLCNT) */
#define I2CFLCNT_ADJUST(n)      (((n) - 1) < 8 ? 8 : ((n) - 1))

/* I2C Transmit Abort Status Register (I2C_TXABRT) */
static const char *abrt_src[] =
{
	"I2C_TXABRT_ABRT_7B_ADDR_NOACK",
	"I2C_TXABRT_ABRT_10ADDR1_NOACK",
	"I2C_TXABRT_ABRT_10ADDR2_NOACK",
	"I2C_TXABRT_ABRT_XDATA_NOACK",
	"I2C_TXABRT_ABRT_GCALL_NOACK",
	"I2C_TXABRT_ABRT_GCALL_READ",
	"I2C_TXABRT_ABRT_HS_ACKD",
	"I2C_TXABRT_SBYTE_ACKDET",
	"I2C_TXABRT_ABRT_HS_NORSTRT",
	"I2C_TXABRT_SBYTE_NORSTRT",
	"I2C_TXABRT_ABRT_10B_RD_NORSTRT",
	"I2C_TXABRT_ABRT_MASTER_DIS",
	"I2C_TXABRT_ARB_LOST",
	"I2C_TXABRT_SLVFLUSH_TXFIFO",
	"I2C_TXABRT_SLV_ARBLOST",
	"I2C_TXABRT_SLVRD_INTX",
};

struct ingenic_i2c_bus
{
    struct rt_i2c_bus_device parent;

    rt_uint32_t hwaddr;
    rt_uint32_t irqno;

    struct clk *clk;

	enum msg_end_type w_end_type;
	enum msg_end_type r_end_type;

	unsigned char *rbuf;
	unsigned char *wbuf;
	unsigned int rd_len;

	int len;
	unsigned int rate;

	struct rt_completion completion;
};

#ifdef RT_USING_I2C0
static struct ingenic_i2c_bus ingenic_i2c0;
#endif

#ifdef RT_USING_I2C1
static struct ingenic_i2c_bus ingenic_i2c1;
#endif

#ifdef RT_USING_I2C2
static struct ingenic_i2c_bus ingenic_i2c2;
#endif

static inline unsigned short i2c_readl(struct ingenic_i2c_bus *i2c,
        unsigned short offset)
{
    return readl(i2c->hwaddr + offset);
}

static inline void i2c_writel(struct ingenic_i2c_bus *i2c, unsigned short offset,
        unsigned short value)
{
    writel(value, i2c->hwaddr + offset);
}

static int ingenic_i2c_disable(struct ingenic_i2c_bus *i2c)
{
	int timeout = TIMEOUT;

	i2c_writel(i2c, I2C_ENB, 0);

	while ((i2c_readl(i2c, I2C_ENSTA) & I2C_ENB_I2CENB) && (--timeout > 0))
		rt_thread_delay(1);

	if (timeout) return 0;

	I2C_DBG("disable i2c failed!\n");
	return -RT_ETIMEOUT;
}

static int ingenic_i2c_enable(struct ingenic_i2c_bus *i2c)
{
	int timeout = TIMEOUT;

	i2c_writel(i2c, I2C_ENB, 1);

	while (!(i2c_readl(i2c, I2C_ENSTA) & I2C_ENB_I2CENB) && (--timeout > 0))
		rt_thread_delay(1);

	if (timeout) return 0;

	I2C_DBG("enable i2c failed\n");
	return -RT_ETIMEOUT;
}

static void ingenic_i2c_reset(struct ingenic_i2c_bus *i2c)
{
	i2c_readl(i2c, I2C_CTXABRT);
	i2c_readl(i2c, I2C_INTST);

	ingenic_i2c_disable(i2c);
	rt_thread_delay(1);
	ingenic_i2c_enable(i2c);
}


static int ingenic_i2c_set_speed(struct ingenic_i2c_bus *i2c, int rate)
{
	/*ns */
	long dev_clk = clk_get_rate(i2c->clk);
	long cnt_high = 0;	/* HIGH period count of the SCL clock */
	long cnt_low = 0;	/* LOW period count of the SCL clock */
	long setup_time = 0;
	long hold_time = 0;
	unsigned short tmp;

	i2c->rate = rate;

	if (ingenic_i2c_disable(i2c))I2C_DBG("i2c not disable\n");

	if (rate <= 100000)
	{
		tmp = 0x43 | (1 << 5);	/* standard speed mode */
		i2c_writel(i2c, I2C_CTRL, tmp);
	}
	else
	{
		tmp = 0x45 | (1 << 5);	/* fast speed mode */
		i2c_writel(i2c, I2C_CTRL, tmp);
	}

	/*         high
	 *         ____     ____      ____      ____
	 *  clk __|  | |___|    |____|    |____|    |___
	 *           | | |
	 *           | | |
	 *           |_|_|     _________      ____
	 * data    __/ | |\___/         \____/    \____
	 *    setup->| |<|
	 *           ->| |<-hold
	 */

	//setup_time = (10 000 000/(rate*4)) + 1;
	setup_time = (dev_clk / (rate * 4));
	if (setup_time > 1) setup_time -= 1;

	//hold_time =  (10000000/(rate*4)) - 1;
	hold_time = (dev_clk / (rate * 4));

	/*         high
	 *         ____     ____
	 *  clk __|    |___|    |____
	 *              low
	 *        |<--period--->|
	 *
	 */
	cnt_high = dev_clk / (rate * 2);
	cnt_low = dev_clk / (rate * 2);

	if (setup_time > 255) setup_time = 255;
	if (setup_time <= 0) setup_time = 1;
	if (hold_time > 0xFFFF) hold_time = 0xFFFF;

	if (rate <= 100000)
	{
		i2c_writel(i2c, I2C_SHCNT, I2CSHCNT_ADJUST(cnt_high));
		i2c_writel(i2c, I2C_SLCNT, I2CSLCNT_ADJUST(cnt_low));
	}
	else
	{
		i2c_writel(i2c, I2C_FHCNT, I2CFHCNT_ADJUST(cnt_high));
		i2c_writel(i2c, I2C_FLCNT, I2CFLCNT_ADJUST(cnt_low));
	}

	i2c_writel(i2c, I2C_SDASU, setup_time & 0xff);
	i2c_writel(i2c, I2C_SDAHD, hold_time);

	return 0;
}

/* function: send read command
 * return:	0, successful
 *		1, txfifo valid entry is more than receive fifo, before send read command,
 *			must be read.
 *		2, txfifo count is 0 or rxfifo count is 0.
 * */
static inline unsigned int i2c_send_rcmd(struct ingenic_i2c_bus *i2c)
{
	unsigned int tx_count, rx_count, count, tx_valid, rx_valid;

	tx_valid = i2c_readl(i2c, I2C_TXFLR);
	rx_valid = i2c_readl(i2c, I2C_RXFLR);
	tx_count = I2C_FIFO_LEN - tx_valid;
	rx_count = I2C_FIFO_LEN - rx_valid;

	if (tx_valid > rx_count)
    {
		I2C_DBG("###Warning: I2C transfer fifo valid entry is more receive fifo, "
				"before send read cmd, please read data from "
				"the read fifo.\n");
		return 1;
	}

	if (!tx_count || !rx_count)
    {
		I2C_DBG("###Warning: I2C receive fifo or transfer fifo is full, "
				"before send read cmd, please read data from "
				"the read fifo or wait some time.\n\n");
		return 2;
	}

	count = (i2c->rd_len < tx_count)? i2c->rd_len : tx_count;
	count = (count < rx_count)? count : rx_count;

	i2c->rd_len -= count;

	if (!i2c->rd_len)
    {
		while (count > 1)
        {
			i2c_writel(i2c, I2C_DC, I2C_DC_READ);
			count--;
		}

		if (i2c->r_end_type == MSG_END_STOP)
        {
			i2c_writel(i2c, I2C_DC, I2C_DC_READ | I2C_DC_STP);
		}
        else
        {
			i2c_writel(i2c, I2C_DC, I2C_DC_READ);
		}
	}
    else
    {
		while (count > 0)
        {
			i2c_writel(i2c, I2C_DC, I2C_DC_READ);
			count--;
		}
	}

	return 0;
}

static void txabrt(struct ingenic_i2c_bus *i2c, int src)
{
	int i;

	I2C_DBG("--I2C txabrt:\n");
	for (i = 0; i < 16; i++)
    {
		if (src & (0x1 << i))
			I2C_DBG("--I2C TXABRT[%d]=%s\n", i, abrt_src[i]);
	}
}

static int i2c_disable_clk(struct ingenic_i2c_bus *i2c)
{
	int timeout = 10;
	int tmp = i2c_readl(i2c, I2C_STA);

	while ((tmp & I2C_STA_MSTACT) && (--timeout > 0))
	{
		rt_thread_delay(2);
		tmp = i2c_readl(i2c, I2C_STA);
	}

	if (timeout > 0)
	{
		clk_disable(i2c->clk);
		return 0;
	}
	else
	{
		I2C_DBG("--I2C disable clk timeout, I2C_STA = 0x%x\n", tmp);
		ingenic_i2c_reset(i2c);
		clk_disable(i2c->clk);

		return -RT_ETIMEOUT;
	}
}

static inline int xfer_read(struct ingenic_i2c_bus *i2c, unsigned char *buf, int len, enum msg_end_type end_type)
{
	int ret = 0;
	long timeout;
	unsigned short tmp;

	rt_memset(buf, 0, len);

	i2c->rd_len = len;
	i2c->len = len;
	i2c->rbuf = buf;
	i2c->r_end_type = end_type;

	i2c_readl(i2c, I2C_CSTP);		/* clear STP bit */
	i2c_readl(i2c, I2C_CTXOF);		/* clear TXOF bit */
	i2c_readl(i2c, I2C_CTXABRT);	/* clear TXABRT bit */

    I2C_DBG("i2c: read %d len data\n", len);

	if (len <= I2C_FIFO_LEN)
    {
		i2c_writel(i2c, I2C_RXTL, len - 1);
	}
    else
    {
		i2c_writel(i2c, I2C_RXTL, RX_LEVEL);
	}
//	I2C_DBG("RXTL: %x\n", i2c_readl(i2c, I2C_RXTL));

	I2C_DBG("read len: %d\n", i2c_readl(i2c, I2C_RXFLR));

	while (i2c_readl(i2c, I2C_STA) & I2C_STA_RFNE)
    {
		i2c_readl(i2c, I2C_DC);
	}

    if (i2c_send_rcmd(i2c))
    {
    	I2C_DBG("i2c: send read command failed!\n");
    }
    else
    {
    	I2C_DBG("i2c: send read command OK!\n");
    }

	tmp = I2C_INTM_MRXFL | I2C_INTM_MTXABT;
	if (end_type == MSG_END_STOP) tmp |= I2C_INTM_MISTP;
	i2c_writel(i2c, I2C_INTM, tmp);

    /* wait for finish */
	while(rt_completion_wait(&(i2c->completion), RT_TICK_PER_SECOND) == -RT_ETIMEOUT)
		I2C_DBG("fifo len: %d\n", i2c_readl(i2c, I2C_RXFLR));

	tmp = i2c_readl(i2c, I2C_TXABRT);
	if (tmp)
    {
		txabrt(i2c, tmp);
		if (tmp > 0x1 && tmp < 0x10)
			ret = -RT_EIO;
		else
			ret = -RT_EIO;

        /* abort read */
		if (tmp & (1 << 5)) {
			ret = -RT_ERROR;
		}
		i2c_readl(i2c, I2C_CTXABRT);
	}

    if (ret < 0) ingenic_i2c_reset(i2c);

	return ret;
}

static inline int xfer_write(struct ingenic_i2c_bus *i2c, unsigned char *buf, int len, enum msg_end_type end_type)
{
	int ret = 0;
	long timeout = TIMEOUT;
	unsigned short reg_tmp;

	i2c->wbuf = buf;
	i2c->len = len;

	i2c_writel(i2c, I2C_TXTL, TX_LEVEL);

    i2c_readl(i2c, I2C_CSTP);       /* clear STP bit */
    i2c_readl(i2c, I2C_CTXOF);      /* clear TXOF bit */
    i2c_readl(i2c, I2C_CTXABRT);    /* clear TXABRT bit */

    I2C_DBG("i2c: write %d len data\n", len);

	i2c->w_end_type = end_type;

	while ((i2c_readl(i2c, I2C_STA) & I2C_STA_TFNF) && (i2c->len > 0))
    {
		reg_tmp = *i2c->wbuf++;
		if (i2c->len == 1)
        {
			if (end_type == MSG_END_STOP)
            {
				reg_tmp |= I2C_DC_STP;
			}
		}
		i2c_writel(i2c, I2C_DC, reg_tmp);

		i2c->len -= 1;
	}

	if (i2c->len == 0)
    {
		i2c_writel(i2c, I2C_TXTL, 0);
	}

	reg_tmp = I2C_INTM_MTXEMP | I2C_INTM_MTXABT | I2C_INTM_MTXOF;
	if (end_type == MSG_END_STOP) reg_tmp |= I2C_INTM_MISTP;
	i2c_writel(i2c, I2C_INTM, reg_tmp);

    /* wait for finish */
	rt_completion_wait(&(i2c->completion), rt_tick_from_millisecond(2000));

	reg_tmp = i2c_readl(i2c, I2C_TXABRT);
	if (reg_tmp)
    {
		txabrt(i2c, reg_tmp);
		if (reg_tmp > 0x1 && reg_tmp < 0x10)
			ret = -RT_EIO;
		else
			ret = -RT_EIO;

        //after I2C_TXABRT_ABRT_XDATA_NOACK error,this required core to resend
		if (reg_tmp & 8)
        {
			ret = -RT_ERROR;
		}
		i2c_readl(i2c, I2C_CTXABRT);
	}

	if (ret < 0) ingenic_i2c_reset(i2c);

	return ret;
}

static rt_size_t ingenic_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
	int i;
    int ret = RT_EOK;
    struct ingenic_i2c_bus *i2c;

    i2c = (struct ingenic_i2c_bus*)bus;

	clk_enable(i2c->clk);
	i2c_writel(i2c, I2C_TAR, msgs[0].addr);

	for (i = 0; i < num; i++)
    {
		enum msg_end_type end_type = MSG_END_STOP;

		if (i < (num - 1))
        {
			if (msgs[i + 1].flags & RT_I2C_NO_START)
            {
				end_type = MSG_END_CONTINUE;	    /* have no STOP and START */
			}
            else
            {
				end_type = MSG_END_REPEAT_START;	/* have no STOP but have RESTART */
			}
		}

		/* initialize completion */
		rt_completion_init(&(i2c->completion));

		if (msgs[i].flags & RT_I2C_RD)
        {
			ret = xfer_read(i2c, msgs[i].buf, msgs[i].len, end_type);
		}
        else
        {
			ret = xfer_write(i2c, msgs[i].buf, msgs[i].len, end_type);
		}

        if (ret < 0)
        {
			clk_disable(i2c->clk);
			goto _ERR;
		}
	}

	ret = i2c_disable_clk(i2c);

_ERR:
    return ret < 0? ret : i;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    ingenic_i2c_xfer,
    RT_NULL,
    RT_NULL
};

static void i2c_irq_handler(int irqno, void *param)
{
	unsigned short tmp, intst, intmsk;
	struct ingenic_i2c_bus *i2c;

	i2c = (struct ingenic_i2c_bus*)param;

	intst = i2c_readl(i2c, I2C_INTST);
	intmsk = i2c_readl(i2c, I2C_INTM);

	I2C_DBG("i2c irq!!\n");

	if ((intst & I2C_INTST_TXABT) && (intmsk & I2C_INTM_MTXABT))
	{
		I2C_DBG("%s %d, I2C transfer error, ABORT interrupt\n", __func__, __LINE__);
		goto END_TRSF_IRQ_HND;
	}

	if ((intst & I2C_INTST_ISTP) && (intmsk & I2C_INTM_MISTP))
	{
		i2c_readl(i2c, I2C_CSTP);	/* clear STP bit */

		if (i2c->len == 0)
			goto END_TRSF_IRQ_HND;
	}

	if ((intmsk & I2C_INTM_MTXEMP) && (intst & I2C_INTST_TXEMP))
	{
		if (!i2c->len)
		{
			if (i2c->w_end_type == MSG_END_REPEAT_START)
			{
				goto END_TRSF_IRQ_HND;
			}
			else
			{
				tmp = i2c_readl(i2c, I2C_INTM);
				tmp &= ~I2C_INTM_MTXEMP;
				i2c_writel(i2c, I2C_INTM, tmp);
			}
		}
		else
		{
			while ((i2c->len > 0) && (i2c_readl(i2c, I2C_STA) & I2C_STA_TFNF))
			{
				tmp = *i2c->wbuf++;
				if (i2c->len == 1)
				{
					if (i2c->w_end_type == MSG_END_STOP)
						tmp |= I2C_DC_STP;
				}

				i2c_writel(i2c, I2C_DC, tmp);
				i2c->len -= 1;
			}

			if (i2c->len == 0)
			{
				i2c_writel(i2c, I2C_TXTL, 0);
			}
		}
	}

	if ((intst & I2C_INTST_RXFL) && (intmsk & I2C_INTM_MRXFL))
	{
		I2C_DBG("I2C RXFL\n");
		while ((i2c_readl(i2c, I2C_STA) & I2C_STA_RFNE) && (i2c->len > 0))
		{
			tmp = i2c_readl(i2c, I2C_DC) & 0xff;
			*i2c->rbuf++ = tmp;
			i2c->len--;
		}

		if (i2c->len == 0)
		{
			goto END_RECE_IRQ_HND;
		}

		if (i2c->len <= I2C_FIFO_LEN)
		{
			i2c_writel(i2c, I2C_RXTL, i2c->len - 1);
		}

		if (i2c_send_rcmd(i2c))
		{
			I2C_DBG("%s %d, I2C controller has BUG, RXFLR or TXFLR can not clear\n", __func__, __LINE__);
		}
	}

	if ((intst & I2C_INTST_RXOF) && (intmsk & I2C_INTM_MRXOF))
	{
		I2C_DBG("%s %d, I2C transfer error, RXFIFO over full\n", __func__, __LINE__);
		i2c_readl(i2c, I2C_CRXOF);	/* clear RXOF bit */
	}

	if ((intst & I2C_INTST_TXOF) && (intmsk & I2C_INTM_MTXOF))
	{
		I2C_DBG("%s %d, I2C transfer error, TXFIFO over full\n", __func__, __LINE__);
		i2c_readl(i2c, I2C_CTXOF);	/* clear TXOF bit */
		goto END_TRSF_IRQ_HND;
	}

	return ;

END_RECE_IRQ_HND:
END_TRSF_IRQ_HND:
	i2c_writel(i2c, I2C_INTM, 0);
	rt_completion_done(&i2c->completion);
}

int rt_hw_i2c_init(void)
{
	struct ingenic_i2c_bus *i2c;
    struct rt_i2c_bus_device *i2c_bus;

#ifdef RT_USING_I2C0
    {
		i2c = &ingenic_i2c0;
		rt_memset((void *)i2c, 0, sizeof(struct ingenic_i2c_bus));

		i2c->hwaddr = I2C0_BASE;
		i2c->irqno = IRQ_I2C0;

		/* Set PB23 PB24 in func0 (I2C0) */
		gpio_set_func(GPIO_PORT_B, GPIO_Pin_24, GPIO_FUNC_0);
		gpio_set_func(GPIO_PORT_B, GPIO_Pin_23, GPIO_FUNC_0);

		/* enable clock */
		i2c->clk = clk_get("i2c0");
		clk_enable(i2c->clk);

		i2c_bus = &i2c->parent;
		i2c_bus->ops = &i2c_ops;
		rt_i2c_bus_device_register(i2c_bus, "i2c0");

		ingenic_i2c_set_speed(i2c, 400 * 1000);

		/* reset I2C */
		i2c_writel(i2c, I2C_CTRL, i2c_readl(i2c, I2C_CTRL) | I2C_CTRL_REST);
		i2c_writel(i2c, I2C_INTM, 0x0);

		ingenic_i2c_enable(i2c);
		clk_disable(i2c->clk);

		/* install interrupt */
		rt_hw_interrupt_install(i2c->irqno, i2c_irq_handler, i2c, "i2c0");
		rt_hw_interrupt_umask(i2c->irqno);
    }
#endif

#ifdef RT_USING_I2C1
    {
		i2c = &ingenic_i2c1;
		rt_memset((void *)i2c, 0, sizeof(struct ingenic_i2c_bus));

		i2c->hwaddr = I2C1_BASE;
		i2c->irqno = IRQ_I2C1;

		/* Set PC26 PC27 in func0 (I2C1) */
		gpio_set_func(GPIO_PORT_C, GPIO_Pin_26, GPIO_FUNC_0);
		gpio_set_func(GPIO_PORT_C, GPIO_Pin_27, GPIO_FUNC_0);

		/* enable clock */
		i2c->clk = clk_get("i2c1");
		clk_enable(i2c->clk);

		i2c_bus = &i2c->parent;
		i2c_bus->ops = &i2c_ops;
		rt_i2c_bus_device_register(i2c_bus, "i2c1");

		ingenic_i2c_set_speed(i2c, 400 * 1000);

		/* reset I2C */
		i2c_writel(i2c, I2C_CTRL, i2c_readl(i2c, I2C_CTRL) | I2C_CTRL_REST);
		i2c_writel(i2c, I2C_INTM, 0x0);

		ingenic_i2c_enable(i2c);
		clk_disable(i2c->clk);

		/* install interrupt */
		rt_hw_interrupt_install(i2c->irqno, i2c_irq_handler, i2c, "i2c1");
		rt_hw_interrupt_umask(i2c->irqno);
    }
#endif

#ifdef RT_USING_I2C2
    {
        i2c = &ingenic_i2c2;
        rt_memset((void *)i2c, 0, sizeof(struct ingenic_i2c_bus));

        i2c->hwaddr = I2C2_BASE;
        i2c->irqno = IRQ_I2C2;

        /* Set PC26 PC27 in func0 (I2C1) */
        gpio_set_func(GPIO_PORT_D, GPIO_Pin_0, GPIO_FUNC_1);
        gpio_set_func(GPIO_PORT_D, GPIO_Pin_1, GPIO_FUNC_1);

        /* enable clock */
        i2c->clk = clk_get("i2c2");
        clk_enable(i2c->clk);

        i2c_bus = &i2c->parent;
        i2c_bus->ops = &i2c_ops;
        rt_i2c_bus_device_register(i2c_bus, "i2c2");

        ingenic_i2c_set_speed(i2c, 400 * 1000);

        /* reset I2C */
        i2c_writel(i2c, I2C_CTRL, i2c_readl(i2c, I2C_CTRL) | I2C_CTRL_REST);
        i2c_writel(i2c, I2C_INTM, 0x0);

        ingenic_i2c_enable(i2c);
        clk_disable(i2c->clk);

        /* install interrupt */
        rt_hw_interrupt_install(i2c->irqno, i2c_irq_handler, i2c, "i2c2");
        rt_hw_interrupt_umask(i2c->irqno);
    }
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);
