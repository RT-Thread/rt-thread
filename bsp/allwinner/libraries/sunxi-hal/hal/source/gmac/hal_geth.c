/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <errno.h>
#include <typedef.h>
#include <hal_mem.h>
#include <sunxi_hal_geth.h>
#include <lwip/pbuf.h>
#include <netif/ethernet.h>
#include <sunxi_hal_mii.h>
#include <sunxi_hal_miiphy.h>
#include <rtthread.h>
#include <netif/ethernetif.h>
#ifdef RT_USING_SMART
#include <page.h>
#include <ioremap.h>
#endif
#include <arch.h>

static struct geth_device rt_geth_dev;
static unsigned int rx_clean = 0;

static int gmac_rx_desc_fill(rt_device_t dev)
{
    unsigned int i = 0;
    unsigned int count = 0;
    hal_geth_dma_desc_t *rx_p = NULL;

    for(i=0; i<DMA_DESC_RX_NUM; i++)
    {
        rx_p = rt_geth_dev.get_buffer_config.dma_desc_rx + count;
        rx_p->desc0.rx.own = 1;
        rx_p->desc1.all |= ((1 << 11) - 1);
        count = circ_inc(count, DMA_DESC_RX_NUM);
    }
    count = 0;
    return 0;
}

void desc_buf_set(struct dma_desc *desc, unsigned long paddr, int size)
{
    desc->desc1.all &= (~((1 << 11) - 1));
    desc->desc1.all |= (size & ((1 << 11) - 1));
}

void desc_set_own(struct dma_desc *desc)
{
    desc->desc0.all |= 0x80000000;
}

void desc_tx_close(struct dma_desc *first, struct dma_desc *end, int csum_insert)
{
    struct dma_desc *desc = first;

    first->desc1.tx.first_sg = 1;
    end->desc1.tx.last_seg = 1;
    end->desc1.tx.interrupt = 1;

    if (csum_insert)
    {
        do
        {
            desc->desc1.tx.cic = 3;
            desc++;
        } while (desc <= end);

    }
}

int desc_get_own(struct dma_desc *desc)
{
    return desc->desc0.all & 0x80000000;
}

void desc_tag_clean(struct dma_desc *desc)
{
    desc->resever0 = 0;
}

void desc_add_tag(struct dma_desc *desc)
{
    desc->resever0 = 1;
}

static int geth_phy_read(char *devname, unsigned int phy_addr, unsigned char reg,unsigned short *data)
{
    struct eth_device *dev;
    uint32_t value;

    value = geth_mdio_read(rt_geth_dev.iobase, phy_addr, reg);

    return value;
}

static int geth_phy_write(char *devname, unsigned int phy_addr, unsigned char reg, uint16_t data)
{
    struct eth_device *dev;

    geth_mdio_write(rt_geth_dev.iobase, phy_addr, reg, data);

    return 0;
}

void geth_link_change(struct geth_device *dev,rt_bool_t up)
{
    if(up)
    {
        printf("link up\n");
        eth_device_linkchange(&dev->parent, RT_TRUE);
        dev->phy_link_status = RT_TRUE;
    }
    else
    {
        printf("link down\n");
        eth_device_linkchange(&dev->parent, RT_FALSE);
        dev->phy_link_status = RT_FALSE;
    }
}

int read_data_from_eth(rt_device_t dev,struct pbuf *p,uint16_t *read_length)
{
    unsigned int i = 0;
    int ret = -1;
    hal_geth_dma_desc_t *rx_p = NULL;
    unsigned int delay_count = 0;
    struct pbuf *q = NULL;
    int length = 0;
    int offset = 0;
    rx_p = rt_geth_dev.get_buffer_config.dma_desc_rx + rx_clean;

    awos_arch_mems_flush_dcache_region((unsigned long)rx_p,sizeof(hal_geth_dma_desc_t));
    awos_arch_mems_flush_dcache_region((unsigned long)rx_p->desc2,2048);
    dsb(v);
    if(!rx_p->desc0.rx.own)
    {
        length = rx_p->desc0.rx.frm_len;
        for(q = p;q != RT_NULL;q=q->next)
        {
            if((length - PBUF_MAX_BUFF_SIZE) <= 0)
            {
                rt_memcpy(q->payload,(void *)((unsigned long)rx_p->desc2 + offset),length);
                offset += length;
                break;
            }
            else
            {
                rt_memcpy(q->payload,(void *)((unsigned long)rx_p->desc2 + offset),PBUF_MAX_BUFF_SIZE);
                offset += PBUF_MAX_BUFF_SIZE;
                length -= PBUF_MAX_BUFF_SIZE;
            }
        }

        if(offset != (uint16_t)(rx_p->desc0.rx.frm_len))
        {
            *read_length = 0;
            ret = -1;
            printf("have not enough pbuf for receive data offset %d length %d\n",offset,length);
        }
        else
        {
            *read_length = offset;
            ret = 0;
        }
        rx_p->desc0.all = 0x80000000;

        awos_arch_mems_clean_dcache_region((unsigned long)rx_p,sizeof(hal_geth_dma_desc_t));
        rx_clean = circ_inc(rx_clean, DMA_DESC_RX_NUM);
    }
    else
    {
        read_length = 0;
        return -1;
    }

    return ret;

}
int tx_desc_recycle(rt_device_t dev)
{
    struct dma_desc *desc;
    static int tx_clean = 0;
    desc = rt_geth_dev.get_buffer_config.dma_desc_tx + tx_clean;

    awos_arch_mems_flush_dcache_region((unsigned long)desc,sizeof(hal_geth_dma_desc_t));
    dsb(v);
    while((!desc_get_own(desc))&&(desc->resever0))
    {
        desc_tag_clean(desc);
        dsb(v);
        awos_arch_mems_clean_dcache_region((unsigned long)desc,sizeof(hal_geth_dma_desc_t));

        tx_clean = circ_inc(tx_clean, DMA_DESC_TX_NUM);
        desc = rt_geth_dev.get_buffer_config.dma_desc_tx + tx_clean;
        dsb(v);
        awos_arch_mems_flush_dcache_region((unsigned long)desc,sizeof(hal_geth_dma_desc_t));
        dsb(v);
    }
    return 0;
}

static irqreturn_t geth_irq_handler(int irq, void *dev_id)
{
    int int_sta_value;
    int_sta_value = hal_readl(rt_geth_dev.iobase + GETH_INT_STA);
    int length;
    int ret = 0;

    if(RX_INT & int_sta_value)
    {
        hal_writel(RX_INT,rt_geth_dev.iobase + GETH_INT_STA);
        geth_rx_int_disable(rt_geth_dev.iobase);
        eth_device_ready(&(rt_geth_dev.parent));

    }
    if(TX_INT & int_sta_value)
    {
        hal_writel(RX_INT,rt_geth_dev.iobase + GETH_INT_STA);
    }

    /*clear all interrupt status*/
    hal_writel(int_sta_value,rt_geth_dev.iobase + GETH_INT_STA);

    return 0;
}

int is_enough_desc_available(struct dma_desc *entry)
{
    struct pbuf *q = RT_NULL;
    struct dma_desc *desc;
    desc = entry;
    awos_arch_mems_flush_dcache_region((unsigned long)desc,sizeof(hal_geth_dma_desc_t));
    dsb(v);
    if(desc->desc0.tx.own != 0)
    {
        printf("desc %08x desc0 %08x desc1 %08x\n",desc,desc->desc0,desc->desc1);
        return -RT_ERROR;
    }

    return RT_EOK;
}

int wait_tx_completed(struct dma_desc *entry)
{
    struct pbuf *q = RT_NULL;
    struct dma_desc *desc;
    unsigned int timeout_cnt = 0;
    desc = entry;
    awos_arch_mems_flush_dcache_region((unsigned long)desc,sizeof(hal_geth_dma_desc_t));
    dsb(v);
    while(desc_get_own(desc))
    {
        awos_arch_mems_flush_dcache_region((unsigned long)desc,sizeof(hal_geth_dma_desc_t));
        dsb(v);
        timeout_cnt++;
        if(timeout_cnt > 1000)
        {
            printf("emac send data timeout \n");
            return -RT_ERROR;
        }
    }
    desc_tag_clean(desc);
    dsb(v);
    awos_arch_mems_clean_dcache_region((unsigned long)desc,sizeof(hal_geth_dma_desc_t));

    return RT_EOK;
}

static rt_err_t rt_geth_xmit(rt_device_t dev, struct pbuf *p)
{
    unsigned int entry;
    struct pbuf *q = RT_NULL;
    struct dma_desc *first, *paddr ,*end;
    static int tx_dirty = 0;
    static int tx_clean = 0;
    int desc_value = 0;
    void *dist = NULL;
    int ret = 0;
    unsigned int i = 0;
    unsigned int copy_offset = 0;

    if (!rt_geth_dev.phy_link_status) return -RT_ERROR;

    first = rt_geth_dev.get_buffer_config.dma_desc_tx + tx_dirty;
    ret = is_enough_desc_available(first);
    if(ret < 0)
    {
        return -RT_ERROR;
    }

    copy_offset = 0;
    for(q = p;q != RT_NULL;q=q->next)
    {
        dist = (void *)((unsigned long)first->desc2);
        rt_memcpy(dist+copy_offset,q->payload,q->len);
        copy_offset += q->len;

        if(copy_offset >= ((1 << 11) - 1))
        {
            printf("send data exceed max len copy_offset %d\n",copy_offset);
            return -RT_ERROR;
        }
    }

    desc_buf_set(first, 0, copy_offset);
    desc_add_tag(first);
    tx_dirty = circ_inc(tx_dirty, DMA_DESC_TX_NUM);
    end = first;
    desc_set_own(first);
    desc_tx_close(first, end, 0);

    dsb(v);
    awos_arch_mems_clean_dcache_region((unsigned long)first,sizeof(hal_geth_dma_desc_t));
    awos_arch_mems_clean_dcache_region((unsigned long)first->desc2,copy_offset);
    dsb(v);

    /* Enable transmit and Poll transmit */
    geth_tx_poll(rt_geth_dev.iobase);
    ret = wait_tx_completed(first);

    return ret;
}

static struct pbuf *rt_geth_recv(rt_device_t dev)
{
    static struct pbuf *p_s = RT_NULL;
    struct pbuf *p = RT_NULL;
    int status;
    uint16_t length = 0;
    static int first_flag = 0;

    uint64_t before_get_data_tick;
    uint64_t diff_tick0;
    uint64_t diff_tick1;
    uint64_t diff_tick2;
    if(p_s == RT_NULL)
    {
        p_s = pbuf_alloc(PBUF_RAW, ENET_FRAME_MAX_FRAMELEN, PBUF_POOL);
        if(p_s == RT_NULL)
        {
            return RT_NULL;
        }
    }
    p = p_s;

    status = read_data_from_eth(dev,p,&length);
    if(status == -1)
    {
        geth_rx_int_enable(rt_geth_dev.iobase);
        return NULL;
    }

    pbuf_realloc(p, length);
    p_s = RT_NULL;
    return p;
}

static int rx_status(hal_geth_dma_desc_t *p)
{
    int ret = good_frame;

    if (p->desc0.rx.last_desc == 0)
        ret = discard_frame;

    if (p->desc0.rx.frm_type && (p->desc0.rx.chsum_err
            || p->desc0.rx.ipch_err))
        ret = discard_frame;

    if (p->desc0.rx.err_sum)
        ret = discard_frame;

    if (p->desc0.rx.len_err)
        ret = discard_frame;

    if (p->desc0.rx.mii_err)
        ret = discard_frame;

    return ret;
}

static void geth_set_hwaddr(unsigned char *addr)
{
    geth_set_mac_addr(rt_geth_dev.iobase, addr, 0);
}

static void geth_get_hwaddr(struct eth_device *dev)
{
}

/********************************************************
RGMII       RMI              D1                F133
---------------------------------------------------------
RXD3        /           PE14    PG9         /       PG9
RXD2        /           PE13    PG8         PE13    PG8
RXD1        RXD1        PE2     PG2         PE2     PG2
RXD0        RXD0        PE1     PG1         PE1     PG1
RXCK        /           PE15    PG10        /       PG10
RXCTRL      CRS-DV      PE0     PG0         PE0     PG0
TXD3        /           PE12    PG7         PE12    PG7
TXD2        /           PE11    PG6         PE11    PG6
TXD1        TXD1        PE5     PG5         PE5     PG5
TXD0        TXD0        PE4     PG4         PE4     PG4
TXCK        TXCK        PE3     PG3         PE3     PG3
TXCTL       TXEN        PE6     PG12        PE6     PG12
CLKIN       RXER        PE7     PG13        PE7     PG13
MDC         MDC         PE8     PG14        PE8     PG14
MDIO        MDIO        PE9     PG15        PE9     PG15
EPHY-25M    EPHY-25M    PE10    PG11        PE10    PG11
*/
static void geth_pinctrl_init(void)
{
#ifdef GMAC_USING_GPIOE
    hal_gpio_pinmux_set_function(GPIO_PE0, 8);
    hal_gpio_pinmux_set_function(GPIO_PE1, 8);
    hal_gpio_pinmux_set_function(GPIO_PE2, 8);
    hal_gpio_pinmux_set_function(GPIO_PE3, 8);
    hal_gpio_pinmux_set_function(GPIO_PE4, 8);
    hal_gpio_pinmux_set_function(GPIO_PE5, 8);
    hal_gpio_pinmux_set_function(GPIO_PE6, 8);
    hal_gpio_pinmux_set_function(GPIO_PE7, 8);
    hal_gpio_pinmux_set_function(GPIO_PE8, 8);
    hal_gpio_pinmux_set_function(GPIO_PE9, 8);
    hal_gpio_pinmux_set_function(GPIO_PE10, 8);
#ifdef GMAC_USING_RGMII
    hal_gpio_pinmux_set_function(GPIO_PE11, 8);
    hal_gpio_pinmux_set_function(GPIO_PE12, 8);
    hal_gpio_pinmux_set_function(GPIO_PE13, 8);
#ifdef BOARD_allwinnerd1
    hal_gpio_pinmux_set_function(GPIO_PE14, 8);
    hal_gpio_pinmux_set_function(GPIO_PE15, 8);
#endif /* BOARD_allwinnerd1 */

#ifdef BOARD_allwinnerd1s
    hal_gpio_pinmux_set_function(GPIO_PG9, 4);
    hal_gpio_pinmux_set_function(GPIO_PG10, 4);
#endif /* BOARD_allwinnerd1s */

#endif /* GMAC_USING_RGMII */
#endif /* GMAC_USING_GPIOE */

#ifdef GMAC_USING_GPIOG
    hal_gpio_pinmux_set_function(GPIO_PG0, 4);
    hal_gpio_pinmux_set_function(GPIO_PG1, 4);
    hal_gpio_pinmux_set_function(GPIO_PG2, 4);
    hal_gpio_pinmux_set_function(GPIO_PG3, 4);
    hal_gpio_pinmux_set_function(GPIO_PG4, 4);
    hal_gpio_pinmux_set_function(GPIO_PG5, 4);
#ifdef GMAC_USING_RGMII
    hal_gpio_pinmux_set_function(GPIO_PG6, 4);
    hal_gpio_pinmux_set_function(GPIO_PG7, 4);
    hal_gpio_pinmux_set_function(GPIO_PG8, 4);
    hal_gpio_pinmux_set_function(GPIO_PG9, 4);
    hal_gpio_pinmux_set_function(GPIO_PG10, 4);
#endif /* GMAC_USING_RGMII */
    hal_gpio_pinmux_set_function(GPIO_PG11, 4);
    hal_gpio_pinmux_set_function(GPIO_PG12, 4);
    hal_gpio_pinmux_set_function(GPIO_PG13, 4);
    hal_gpio_pinmux_set_function(GPIO_PE14, 4);
    hal_gpio_pinmux_set_function(GPIO_PE15, 4);
#endif /* GMAC_USING_GPIOG */
}

static int geth_phy_init(struct eth_device *dev)
{
    uint32_t value;
    uint16_t phy_val;
    int i;
    uint32_t phy_addr = 0x1f;
    int duplex;
    int speed;
    uint16_t temp = 0;

    for (i = 0; i < 0x1f; i++) {
        value = (geth_phy_read((char *)dev, i, MII_PHYSID1,NULL)
                            & 0xffff) << 16;
        value |= (geth_phy_read((char *)dev, i, MII_PHYSID2,NULL) & 0xffff);

        if ((value & 0x1fffffff) == 0x1fffffff) {
            rt_thread_delay(RT_TICK_PER_SECOND/100);
            continue;
        }
        phy_addr = i;
        break;
    }

    phy_addr = i;
    if (phy_addr == 0x1f) {
        printf("No PHY device!\n");
        return -1;
    }
    phy_val = geth_phy_read((char *)dev, phy_addr, MII_BMCR,NULL);
    geth_phy_write((char *)dev, phy_addr, MII_BMCR, phy_val | BMCR_RESET);
    while (geth_phy_read((char *)dev, phy_addr, MII_BMCR,NULL) & BMCR_RESET);

    phy_val = geth_phy_read((char *)dev, phy_addr, MII_BMCR,NULL);
    geth_phy_write((char *)dev, phy_addr, MII_BMCR, phy_val | BMCR_FULLDPLX);

    /* Reset phy chip */
    phy_val = geth_phy_read((char *)dev, phy_addr, MII_BMCR,NULL);
    geth_phy_write((char *)dev, phy_addr, MII_BMCR, (phy_val & ~BMCR_PDOWN));
    while (geth_phy_read((char *)dev, phy_addr, MII_BMCR,NULL) & BMCR_PDOWN);

    /* Wait BMSR_ANEGCOMPLETE be set */
    while (!(geth_phy_read((char *)dev, phy_addr, MII_BMSR,NULL) & BMSR_ANEGCOMPLETE)) {
        if (i > 40) {
            printf("Warning: Auto negotiation timeout!\n");
            return -1;
        }
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        i++;
    }

    phy_val = geth_phy_read((char *)dev, phy_addr, MII_RESV2,NULL);
    temp = (phy_val>>4) & 0x3;
    switch(temp)
    {
    case 2:
        speed = 1000;
        break;
    case 1:
        speed = 100;
        break;
    case 0:
        speed = 10;
        break;
    default :
        break;
    }
    temp = phy_val & 0x08;
    duplex = (temp) ? 1 : 0;
    geth_set_link_mode(rt_geth_dev.iobase,duplex,speed);

    return 0;
}

static int geth_dma_desc_init(void)
{
    void *temp = RT_NULL;

#ifdef RT_USING_SMART
    rt_geth_dev.get_buffer_config.rx_buff_addr = rt_pages_alloc(RX_BUFFER_INDEX_NUM);
#else
    rt_geth_dev.get_buffer_config.rx_buff_addr = rt_malloc(DMA_MEM_ALIGN_SIZE * DMA_DESC_RX_NUM);
#endif
    if(!rt_geth_dev.get_buffer_config.rx_buff_addr)
    {
        printf("ERROR: rx buff page alloc failed\n");
        return -1;
    }
    //temp = (void *)rt_ioremap_nocache((void *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.rx_buff_addr), (SYS_PAGE_SIZE<<RX_BUFFER_INDEX_NUM));
    rt_geth_dev.get_buffer_config.phy_rx_buff_addr = (void *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.rx_buff_addr);
#ifdef RT_USING_SMART
    rt_geth_dev.get_buffer_config.tx_buff_addr = rt_pages_alloc(TX_BUFFER_INDEX_NUM);
#else
    rt_geth_dev.get_buffer_config.tx_buff_addr = rt_malloc(DMA_MEM_ALIGN_SIZE * DMA_DESC_TX_NUM);
#endif
    if(!rt_geth_dev.get_buffer_config.tx_buff_addr)
    {
        printf("ERROR: tx buff page alloc failed\n");
        return -1;
    }
    //temp = (void *)rt_ioremap_nocache((void *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.tx_buff_addr), (SYS_PAGE_SIZE<<TX_BUFFER_INDEX_NUM));
    rt_geth_dev.get_buffer_config.phy_tx_buff_addr = (void *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.tx_buff_addr);

#ifdef RT_USING_SMART
    rt_geth_dev.get_buffer_config.dma_desc_rx = (hal_geth_dma_desc_t *)rt_pages_alloc(RX_BD_INDEX_NUM);
#else
    rt_geth_dev.get_buffer_config.dma_desc_rx = (hal_geth_dma_desc_t *)rt_malloc(sizeof(hal_geth_dma_desc_t) * DMA_DESC_RX_NUM);
#endif
    if(!rt_geth_dev.get_buffer_config.dma_desc_rx)
    {
        printf("ERROR: rx bd page alloc failed\n");
        return -1;
    }

    //temp = (void *)rt_ioremap_nocache((void *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_rx), (SYS_PAGE_SIZE<<RX_BD_INDEX_NUM));
    rt_geth_dev.get_buffer_config.phy_dma_desc_rx = (hal_geth_dma_desc_t *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_rx);
#ifdef RT_USING_SMART
    rt_geth_dev.get_buffer_config.dma_desc_tx = (hal_geth_dma_desc_t *)rt_pages_alloc(TX_BD_INDEX_NUM);
#else
    rt_geth_dev.get_buffer_config.dma_desc_tx = (hal_geth_dma_desc_t *)rt_malloc(sizeof(hal_geth_dma_desc_t) * DMA_DESC_TX_NUM);
#endif
    if(!rt_geth_dev.get_buffer_config.dma_desc_tx)
    {
        printf("ERROR: tx bd page alloc failed\n");
        return -1;
    }
    //temp = (void *)rt_ioremap_nocache((void *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_tx), (SYS_PAGE_SIZE<<TX_BD_INDEX_NUM));
    rt_geth_dev.get_buffer_config.phy_dma_desc_tx = (hal_geth_dma_desc_t *)awos_arch_virt_to_phys((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_tx);

    return 0;
}

void desc_init_chain(hal_geth_dma_desc_t *desc, unsigned long addr, unsigned long first_buff_addr,unsigned int size,unsigned int align_size)
{
    /* In chained mode the desc3 points to the next element in the ring.
     * The latest element has to point to the head.
     */
    int i;
    hal_geth_dma_desc_t *p = desc;
    unsigned long dma_desc_phy = addr;
    unsigned long dma_buff_phy = first_buff_addr;

    for (i = 0; i < size; i++) {

        if(i == (size - 1))
        {
            p->desc2 = (u32)dma_buff_phy;
            p->desc3 = (u32)addr;
        }
        else
        {
            dma_desc_phy += sizeof(hal_geth_dma_desc_t);
            p->desc2 = (u32)dma_buff_phy;
            p->desc3 = (u32)dma_desc_phy;
            p++;
        }
        dma_buff_phy += align_size;
    }
}

static rt_err_t rt_geth_init(rt_device_t dev)
{
    uint32_t value;

    /* Enable clock */

    uint32_t used_type = rt_geth_dev.used_type;
    uint32_t tx_delay = rt_geth_dev.tx_delay;
    uint32_t rx_delay = rt_geth_dev.rx_delay;
    uint32_t phy_interface = rt_geth_dev.phy_interface;
    geth_clk_enable(used_type,phy_interface,tx_delay,rx_delay);

    /* Pinctrl init */
    geth_pinctrl_init();
    /* MAC controller soft reset */
    value = geth_mac_reset(rt_geth_dev.iobase);
    if (!value)
    {
        printf("Gmac controller softs reset success\n");
    }
    else
    {
        printf("Gmac controller soft reset failed value %08x\n",value);
    }
    /* MAC controller initialize */
    geth_mac_init(rt_geth_dev.iobase);

    geth_set_hwaddr(rt_geth_dev.dev_addr);
    /* Frame filter */
    geth_set_filter(rt_geth_dev.iobase);
    /* Burst should be 8 */
    value = hal_readl(rt_geth_dev.iobase + GETH_BASIC_CTL1);
    value |= (8 << 24);
    hal_writel(value, rt_geth_dev.iobase + GETH_BASIC_CTL1);

    /* Disable all interrupt of dma */
    geth_all_int_disable(rt_geth_dev.iobase);

    value = geth_dma_desc_init();
    if(value < 0) {
        printf("Gmac dma desc init fail!\n");
        return -1;
    }

    memset((void *)rt_geth_dev.get_buffer_config.dma_desc_tx, 0, sizeof(hal_geth_dma_desc_t)*DMA_DESC_TX_NUM);
    memset((void *)rt_geth_dev.get_buffer_config.dma_desc_rx, 0, sizeof(hal_geth_dma_desc_t)*DMA_DESC_RX_NUM);

    desc_init_chain(rt_geth_dev.get_buffer_config.dma_desc_tx, (unsigned long)rt_geth_dev.get_buffer_config.phy_dma_desc_tx,
                    (unsigned long)rt_geth_dev.get_buffer_config.phy_tx_buff_addr, DMA_DESC_TX_NUM, DMA_MEM_ALIGN_SIZE);
    desc_init_chain(rt_geth_dev.get_buffer_config.dma_desc_rx, (unsigned long)rt_geth_dev.get_buffer_config.phy_dma_desc_rx,
                    (unsigned long)rt_geth_dev.get_buffer_config.phy_rx_buff_addr, DMA_DESC_RX_NUM, DMA_MEM_ALIGN_SIZE);

    gmac_rx_desc_fill(NULL);

    hal_writel((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_tx, rt_geth_dev.iobase + GETH_TX_DESC_LIST);
    hal_writel((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_rx, rt_geth_dev.iobase + GETH_RX_DESC_LIST);

    awos_arch_mems_clean_dcache_region((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_tx, sizeof(hal_geth_dma_desc_t)*DMA_DESC_TX_NUM);
    awos_arch_mems_clean_dcache_region((unsigned long)rt_geth_dev.get_buffer_config.dma_desc_rx, sizeof(hal_geth_dma_desc_t)*DMA_DESC_RX_NUM);
    dsb(v);
    /* start tx & rx */
    geth_start_tx(rt_geth_dev.iobase);
    geth_start_rx(rt_geth_dev.iobase);

    /* Enable transmit & receive */
    geth_mac_enable(rt_geth_dev.iobase);

    if (request_irq(GETH_IRQ_NUM, geth_irq_handler, 0, "geth", (void *)&rt_geth_dev) < 0)
    {
        printf("request irq error\n");
        return -1;
    }

    enable_irq(GETH_IRQ_NUM);
    geth_rx_int_enable(rt_geth_dev.iobase);
    return 0;
}

static void rt_geth_uninitialize(rt_device_t dev)
{
    geth_mac_disable(rt_geth_dev.iobase);
    geth_clk_disable();
}

static rt_err_t rt_geth_open(rt_device_t dev, rt_uint16_t oflag)
{
    printf("gmac open\n");
    return RT_EOK;
}

static rt_err_t rt_geth_close(rt_device_t dev)
{
    printf("gmac close\n");
    return RT_EOK;
}

static rt_ssize_t rt_geth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    printf("gmac read\n");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_geth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    printf("gmac write\n");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_geth_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) {
            rt_memcpy(args, rt_geth_dev.dev_addr, 6);
        } else {
            return -RT_ERROR;
        }
        break;

    default :
        break;
    }

    return RT_EOK;
}
int is_data_availabl()
{

    hal_geth_dma_desc_t *rx_p = NULL;
    rx_p = rt_geth_dev.get_buffer_config.dma_desc_rx + rx_clean;

    awos_arch_mems_flush_dcache_region((unsigned long)rx_p,sizeof(hal_geth_dma_desc_t));
    awos_arch_mems_flush_dcache_region((unsigned long)rx_p->desc2,2048);
    dsb(v);

    if(!rx_p->desc0.rx.own)
    {
        if((rx_p->desc0.rx.last_desc != 1)||(rx_p->desc0.rx.first_desc != 1))
        {
            printf("first %d last %d\n",rx_p->desc0.rx.first_desc,rx_p->desc0.rx.last_desc);
        }
        return 0;
    }
    else
    {
        return -1;
    }

    return 0;
}

static void phy_link_detect(void *param)
{

    uint16_t bmsr = 0;
    uint16_t link_status = 0;
    uint16_t link_status_old = 0;
    uint16_t phy_val;
    int ret = -1;

    while(1)
    {
        bmsr = geth_phy_read(NULL, 0, MII_BMSR,NULL);
        link_status = bmsr & BMSR_LSTATUS;
        if(link_status_old != link_status)
        {
            if(link_status)
            {
                ret = geth_phy_init((struct eth_device *)param);
                if(ret == 0)
                {
                    geth_link_change(&rt_geth_dev,1);
                }
            }
            else
            {
                if(link_status_old != link_status)
                {
                    geth_link_change(&rt_geth_dev,0);
                }
            }

        }
        link_status_old = link_status;
        rt_thread_delay(RT_TICK_PER_SECOND);
    }

}
void rt_geth_driver_init(void)
{
    rt_err_t state = RT_EOK;

    rt_geth_dev.iobase = IOBASE;
    rt_geth_dev.phy_interface = PHY_INTERFACE_MODE_RGMII;
    rt_geth_dev.used_type = EXT_PHY;
    rt_geth_dev.tx_delay = 3;
    rt_geth_dev.rx_delay = 0;

    random_ether_addr(rt_geth_dev.dev_addr);
    rt_geth_dev.parent.parent.init = rt_geth_init;
    rt_geth_dev.parent.parent.open = rt_geth_open;
    rt_geth_dev.parent.parent.close = rt_geth_close;
    rt_geth_dev.parent.parent.read = rt_geth_read;
    rt_geth_dev.parent.parent.write = rt_geth_write;
    rt_geth_dev.parent.parent.control = rt_geth_control;
    rt_geth_dev.parent.parent.user_data = RT_NULL;

    rt_geth_dev.parent.eth_rx = rt_geth_recv;
    rt_geth_dev.parent.eth_tx = rt_geth_xmit;
    /* register eth device */
    state = eth_device_init(&(rt_geth_dev.parent), "e0");
    if (RT_EOK == state) {
        printf("gmac device init success\n");
    } else {
        printf("gmac device init failed: %d\n", state);
    }

    rt_thread_t link_detect;
    link_detect = rt_thread_create("link_detect",
                            phy_link_detect,
                            (void *)&rt_geth_dev,
                            4096,
                            13,
                            2);
    if (link_detect != RT_NULL)
    {
        rt_thread_startup(link_detect);
    }

    return;
}

static int rt_hw_eth_drvier_init(void)
{
    rt_geth_driver_init();

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_eth_drvier_init);
