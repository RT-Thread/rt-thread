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

#include <sunxi_hal_geth.h>

void random_ether_addr(uint8_t *addr)
{
    uint32_t sid3;

    /*
    * F133 chipid the start address is located at 0x03006200.
    * SID total of 128bits，the offset 0x0c is variable.
    */
    sid3 = hal_readl(0x03006200 + 0xc);

    /*
    * DC-44-6D from ieee official licensed to Allwinner.
    * on here, for testing purposes only.
    */
    addr[0] = 0xDC;
    addr[1] = 0x44;
    addr[2] = 0x6D;
    addr[3] = sid3 & 0xFFu;
    addr[4] = (sid3 >> 8) & 0xFFu;
    addr[5] = (sid3 >> 16) & 0xFFu;
}

void geth_set_link_mode(unsigned long iobase, int duplex, int speed)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_BASIC_CTL0);
    if (!duplex)
        value &= ~CTL0_DM;
    else
        value |= CTL0_DM;

    switch (speed) {
    case 1000:
        value &= ~0x0C;
        break;
    case 100:
    case 10:
    default:
        value |= 0x08;
        if (speed == 100)
            value |= 0x04;
        else
            value &= ~0x04;
        break;
    }

    hal_writel(value, iobase + GETH_BASIC_CTL0);
}

void geth_mac_loopback(unsigned long iobase, int enable)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_BASIC_CTL0);
    if (enable)
        value |= 0x02;
    else
        value &= ~0x02;

    hal_writel(value, iobase + GETH_BASIC_CTL0);
}

void geth_start_tx(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_TX_CTL1);
    value |= (1 << 30);
    hal_writel(value, iobase + GETH_TX_CTL1);
}

void geth_stop_tx(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_TX_CTL1);
    value &= ~(1 << 30);
    hal_writel(value, iobase + GETH_TX_CTL1);
}

void geth_start_rx(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_RX_CTL1);
    value |= (1 << 30);
    hal_writel(value, iobase + GETH_RX_CTL1);
}

void geth_stop_rx(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_RX_CTL1);
    value &= ~(1 << 30);
    hal_writel(value, iobase + GETH_RX_CTL1);
}

void geth_loopback_enable(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_BASIC_CTL0);
    value |= (1 << 0);
    hal_writel(value, iobase + GETH_BASIC_CTL0);
}

void geth_loopback_disable(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_BASIC_CTL0);
    value &= ~(1 << 0);
    hal_writel(value, iobase + GETH_BASIC_CTL0);
}

uint32_t geth_mac_reset(unsigned long iobase)
{
    uint32_t value;

    /* Soft reset all registers and logic */
    value = hal_readl(iobase + GETH_BASIC_CTL1);
    value |= SOFT_RST;
    hal_writel(value, iobase + GETH_BASIC_CTL1);

    while(value)
    {
        rt_thread_delay(10);
        value = (hal_readl(iobase + GETH_BASIC_CTL1) & SOFT_RST);
    }
    return !!value;
}

void geth_mac_init(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_TX_CTL1);
    /* Transmit COE type 2 cannot be done in cut-through mode. */
    value |= TX_MD;
    hal_writel(value, iobase + GETH_TX_CTL1);

    value = hal_readl(iobase + GETH_RX_CTL0);
    hal_writel((0x3 << 20), iobase + GETH_MDIO_ADDR); /* MDC_DIV_RATIO */

    value = hal_readl(iobase + GETH_RX_CTL1);
    value |= RX_MD;
    /* Forward frames with error and undersized good frame. */
    value |= (RX_ERR_FRM | RX_RUNT_FRM );
    hal_writel(value, iobase + GETH_RX_CTL1);
}

void geth_set_filter(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_RX_FRM_FLT);
    value |= 0x1;
    hal_writel(value, iobase + GETH_RX_FRM_FLT);
}

void geth_set_mac_addr(unsigned long iobase, unsigned char *addr, int index)
{
    uint32_t value;

    value = (addr[5] << 8) | addr[4];
    hal_writel(value, iobase + GETH_ADDR_HI(index));

    value = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
    hal_writel(value, iobase + GETH_ADDR_LO(index));
}

void geth_mac_enable(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_TX_CTL0);
    value |= (1 << 31);
    hal_writel(value, iobase + GETH_TX_CTL0);

    value = hal_readl(iobase + GETH_RX_CTL0);
    value |= (1 << 31);
    hal_writel(value, iobase + GETH_RX_CTL0);
}

void geth_mac_disable(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_TX_CTL0);
    value &= ~(1 << 31);
    hal_writel(value, iobase + GETH_TX_CTL0);

    value = hal_readl(iobase + GETH_RX_CTL0);
    value &= ~(1 << 31);
    hal_writel(value, iobase + GETH_RX_CTL0);
}

void geth_tx_poll(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_TX_CTL1);
    value |= (1 << 31);
    hal_writel(value, iobase + GETH_TX_CTL1);
}

void geth_rx_poll(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_RX_CTL1);
    value |= (1 << 31);
    hal_writel(value, iobase + GETH_RX_CTL1);
}

void geth_flush_tx(unsigned long iobase)
{
    uint32_t value;

    value = hal_readl(iobase + GETH_TX_CTL1);
    value |= 0x1;
    hal_writel(value, iobase + GETH_TX_CTL1);
}


void geth_rx_int_enable(unsigned long iobase)
{
    uint32_t value = 0;
    value |= RX_INT;
    hal_writel(value , iobase + GETH_INT_EN);
}

void geth_tx_int_enable(unsigned long iobase)
{
    uint32_t value = 0;
    value |= (TX_INT | TX_STOP_INT | TX_UA_INT | TX_TOUT_INT | TX_UNF_INT);
    hal_writel(value, iobase + GETH_INT_EN);
}

void geth_rx_int_disable(unsigned long iobase)
{
    uint32_t value = 0;
    value = hal_readl(iobase + GETH_INT_EN);
    value &= ~RX_INT;
    hal_writel(value , iobase + GETH_INT_EN);}

void geth_tx_int_disable(unsigned long iobase)
{
    uint32_t value = 0;
    value = hal_readl(iobase + GETH_INT_EN);
    value &= ~TX_INT;
    hal_writel(value, iobase + GETH_INT_EN);
}

void geth_all_int_disable(unsigned long iobase)
{
    hal_writel(0, iobase + GETH_INT_EN);
}

void geth_clk_enable(uint32_t used_type,uint32_t phy_interface,uint32_t tx_delay,uint32_t rx_delay)
{
    uint32_t value;
    uint32_t reg_val;

    /* Enalbe clk for gmac */
    value = hal_readl(CCMU_BASE + CCMU_GETH_CLK_REG);
    value |= (1 << CCMU_GETH_RST_BIT);
    value |= (1 << CCMU_GETH_GATING_BIT);
    hal_writel(value, CCMU_BASE + CCMU_GETH_CLK_REG);

    /* Enable clk for ephy */
#ifdef USE_EPHY25M
    value = hal_readl(CCMU_BASE + CCMU_EPHY_CLK_REG);
    value |= (1 << CCMU_EPHY_PLL_PERI0_GATING_BIT);
    value |= (1 << CCMU_EPHY_SCLK_GATING_BIT);
    hal_writel(value, CCMU_BASE + CCMU_EPHY_CLK_REG);
#endif

    /* Set phy clock */
    value = hal_readl(PHY_CLK_REG);

    if (used_type == INT_PHY){
        reg_val = hal_readl(CCMU_BASE + 0x0070);
        reg_val |= (1 << 0);
        hal_writel(reg_val, CCMU_BASE + 0x0070);

        reg_val = hal_readl(CCMU_BASE + 0x02c8);
        reg_val |= (1 << 2);
        hal_writel(reg_val, CCMU_BASE + 0x02c8);

        value |= (1 << 15);
        value &= ~(1 << 16);
        value |= (3 << 17);
    } else {
        value &= ~(1 << 15);
        value |= (1 << 16);
    }

    if (phy_interface == PHY_INTERFACE_MODE_RGMII) {
        value |= 0x00000004;
    } else {
        value &= ~0x00000004;
    }

    value &= ~0x00002003;
    if (phy_interface == PHY_INTERFACE_MODE_RGMII
            || phy_interface == PHY_INTERFACE_MODE_GMII) {
        value |= 0x00000002;
    } else if (phy_interface == PHY_INTERFACE_MODE_RMII) {
        value |= 0x00002001;
    }
    /* Adjust Tx/Rx clock delay */
    value &= ~(0x07 << 10);
    value |= ((tx_delay & 0x07) << 10);
    value &= ~(0x1f << 5);
    value |= ((rx_delay & 0x1f) << 5);

    hal_writel(value, PHY_CLK_REG);

}

void geth_clk_disable(void)
{
    uint32_t value;

    /* Disalbe clk for gmac */
    value = hal_readl(CCMU_BASE + CCMU_GETH_CLK_REG);
    value &= ~(1 << CCMU_GETH_RST_BIT);
    value &= ~(1 << CCMU_GETH_GATING_BIT);
    hal_writel(value, CCMU_BASE + CCMU_GETH_CLK_REG);

    /* Disable clk for ephy */
#ifdef USE_EPHY25M
    value = hal_readl(CCMU_BASE + CCMU_EPHY_CLK_REG);
    value &= ~(1 << CCMU_EPHY_PLL_PERI0_GATING_BIT);
    value &= ~(1 << CCMU_EPHY_SCLK_GATING_BIT);
    hal_writel(value, CCMU_BASE + CCMU_EPHY_CLK_REG);
#endif
}

uint32_t geth_mdio_read(unsigned long iobase, int phy_addr, u8 reg)
{
    uint32_t value = 0;

    value |= (0x06 << 20);
    value |= (((phy_addr << 12) & (0x0001F000)) |
                    ((reg << 4) & (0x000007F0)) |
                    MII_BUSY);

    hal_writel(value, iobase + GETH_MDIO_ADDR);
    while (hal_readl(iobase + GETH_MDIO_ADDR) & MII_BUSY)
        ;

    return  (uint32_t)hal_readl(iobase + GETH_MDIO_DATA);
}

uint32_t geth_mdio_write(unsigned long iobase, int phy_addr, u8 reg, u16 data)
{
    uint32_t value = 0;

    value |= (0x06 << 20);
    value |= (((phy_addr << 12) & (0x0001F000)) |
                    ((reg << 4) & (0x000007F0)) |
                    MII_WRITE | MII_BUSY);

    /* Set the MII address register to write */
    hal_writel(data, iobase + GETH_MDIO_DATA);
    hal_writel(value, iobase + GETH_MDIO_ADDR);

    /* Wait until any existing MII operation is complete */
    while (hal_readl(iobase + GETH_MDIO_ADDR) & MII_BUSY)
        ;

    return 0;
}
