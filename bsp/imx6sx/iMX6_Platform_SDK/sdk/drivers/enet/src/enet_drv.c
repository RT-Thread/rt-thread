/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file enet_drv.c
 * @brief Driver of the i.MX ENET controller.
 *
 * @ingroup diag_enet
 */

#include "sdk.h"
#include "enet/enet.h"
#include "enet_private.h"

/*!
 *Global variable which defines the buffer descriptions for receiving frame
 * 	comment:: it must aligned by 128-bits.
 */
static imx_enet_bd_t imx_enet_rx_bd[ENET_BD_RX_NUM * NUM_OF_ETH_DEVS] __attribute__ ((aligned(32)));

/*!
 *Global variable which defines the buffer descriptions for receiving frame
 * 	comment:: it must aligned by 128-bits.
 */
static imx_enet_bd_t imx_enet_tx_bd[ENET_BD_TX_NUM * NUM_OF_ETH_DEVS] __attribute__ ((aligned(32)));

/*!
 * Global variable which contains the frame buffers ,
 */
static unsigned char imx_enet_rx_buf[ENET_BD_RX_NUM * NUM_OF_ETH_DEVS][2048]
    __attribute__ ((aligned(32)));

/*!
 * Global variable which contains the frame buffers ,
 */
static unsigned char imx_enet_tx_buf[ENET_BD_TX_NUM * NUM_OF_ETH_DEVS][2048]
    __attribute__ ((aligned(32)));

/*!
 * This function gets the value of the PHY registers through the MII interface.
 */
int imx_enet_mii_read(volatile hw_enet_t * enet_reg, unsigned char phy_addr,
                      unsigned char reg_addr, unsigned short int *value)
{
    unsigned long waiting = ENET_MII_TIMEOUT;

    if (enet_reg->EIR.U & ENET_EVENT_MII) {
        enet_reg->EIR.U = ENET_EVENT_MII;
    }

    enet_reg->MMFR.U = ENET_MII_READ(phy_addr, reg_addr);   /*Write CMD */

    while (1) {
        if (enet_reg->EIR.U & ENET_EVENT_MII) {
            enet_reg->EIR.U = ENET_EVENT_MII;
            break;
        }
        if ((--waiting) == 0)
            return -1;

        hal_delay_us(ENET_MII_TICK);
    }

    *value = ENET_MII_GET_DATA(enet_reg->MMFR.U);
    return 0;
}

/*!
 * This function sets the value of the PHY registers through the MII interface.
 */
int imx_enet_mii_write(volatile hw_enet_t * enet_reg, unsigned char phy_addr,
                       unsigned char reg_addr, unsigned short int value)
{
    unsigned long waiting = ENET_MII_TIMEOUT;

    if (enet_reg->EIR.U & ENET_EVENT_MII) {
        enet_reg->EIR.U = ENET_EVENT_MII;
    }

    enet_reg->MMFR.U = ENET_MII_WRITE(phy_addr, reg_addr, value);   /* Write CMD */

    while (1) {
        if (enet_reg->EIR.U & ENET_EVENT_MII) {
            enet_reg->EIR.U = ENET_EVENT_MII;
            break;
        }

        if ((--waiting) == 0)
            return -1;

        hal_delay_us(ENET_MII_TICK);
    }

    return 0;
}

/*!
 * The function initializes the description buffer for receiving or transmitting.
 */
static void imx_enet_bd_init(imx_enet_priv_t * dev, int dev_idx)
{
    int i;
    imx_enet_bd_t *p;
    imx_enet_bd_t *rx_bd_base = imx_enet_rx_bd, *tx_bd_base = imx_enet_tx_bd;

    rx_bd_base += (dev_idx * ENET_BD_RX_NUM);
    tx_bd_base += (dev_idx * ENET_BD_TX_NUM);

    p = dev->rx_bd = (imx_enet_bd_t *) rx_bd_base;

    for (i = 0; i < ENET_BD_RX_NUM; i++, p++) {
        p->status = BD_RX_ST_EMPTY;
        p->length = 0;
        p->data = (unsigned char *)imx_enet_rx_buf[i + dev_idx * ENET_BD_RX_NUM];
        //printf("rx bd %x, buffer is %x\n", (unsigned int)p, (unsigned int)p->data);
    }

    dev->rx_bd[i - 1].status |= BD_RX_ST_WRAP;
    dev->rx_cur = dev->rx_bd;

    p = dev->tx_bd = (imx_enet_bd_t *) tx_bd_base;

    for (i = 0; i < ENET_BD_TX_NUM; i++, p++) {
        p->status = 0;
        p->length = 0;
        p->data = (unsigned char *)imx_enet_tx_buf[i + dev_idx * ENET_BD_TX_NUM];
        //printf("tx bd %x, buffer is %x\n", (unsigned int)p, (unsigned int)p->data);
    }

    dev->tx_bd[i - 1].status |= BD_TX_ST_WRAP;
    dev->tx_cur = dev->tx_bd;

    /*TODO:: add the sync function for items */
}

/*!
 * This function initializes the ENET controller.
 */
static void imx_enet_chip_init(imx_enet_priv_t * dev)
{
    volatile hw_enet_t *enet_reg = (hw_enet_t *) dev->enet_reg;
	unsigned int ipg_clk;

    enet_reg->ECR.U = ENET_RESET;

    while (enet_reg->ECR.U & ENET_RESET) {
        hal_delay_us(ENET_COMMON_TICK);
    }

    enet_reg->EIMR.U = 0x00000000;
    enet_reg->EIR.U = 0xFFFFFFFF;

    /*
     * setup the MII gasket for RMII mode
     */
    enet_reg->RCR.U = (enet_reg->RCR.U & ~(0x0000003F)) | ENET_RCR_RGMII_EN | ENET_RCR_FCE | ENET_RCR_PROM;
    enet_reg->TCR.U |= ENET_TCR_FDEN;
    enet_reg->MIBC.U |= ENET_MIB_DISABLE;

    enet_reg->IAUR.U = 0;
    enet_reg->IALR.U = 0;
    enet_reg->GAUR.U = 0;
    enet_reg->GALR.U = 0;

    /*TODO:: Use MII_SPEED(IPG_CLK) to get the value */
	ipg_clk = get_main_clock(IPG_CLK);
    enet_reg->MSCR.U = (enet_reg->MSCR.U & (~0x7e)) | (((ipg_clk + 499999) / 5000000) << 1); 

    /*Enable ETHER_EN */
    enet_reg->MRBR.U = 2048 - 16;
    enet_reg->RDSR.U = (unsigned long)dev->rx_bd;
    enet_reg->TDSR.U = (unsigned long)dev->tx_bd;

#if 0//defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
	/* Enable Swap to support little-endian device */
	enet_reg->ECR.U |= (0x1 << 8); //BM_ENET_ECR_DBSWP;
	/* set ENET tx at store and forward mode */
	enet_reg->TFWR.U |= BM_ENET_TFWR_STRFWD; //(0x1 << 8);
#endif	
}

void enet_phy_rework_ar8031(imx_enet_priv_t * dev)
{
    unsigned short val = 0;
#if 0
	int i;
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1d, 0x1F); // ?? unknown debug reg
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
    //printf("debug before 0x1F val = 0x%x\n", val);
    val |= 0x4;
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1e, val);
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
    //printf("debug after 0x1F val = 0x%x\n", val);

    // Set CLK_25M Clock Select MDIO register
    // select_clk25m = 3'b110 = 125 MHz from local PLL source
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xd, 0x7); // MMD Access Control; device addr=7
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xe, 0x8016); // MMD Access Address Data; reg=0x8016 (CLK_25M Clock Select)
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xd, 0x4007); // MMD Access Control; func=data, device addr=7
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0xe, &val);
    //printf("debug read from 0x8016 val = 0x%x\n", val);
    val &= 0xffe3;
    val |= 0x18;
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xe, val);
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0xe, &val);
    //printf("debug after read from 0x8016 val = 0x%x\n", val);
    for (i = 0; i < 100000; i++) ;

    //debug register 0x5[8]=1'b1 - suggest add 2ns GTX_CLK delay
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1d, 0x5); // debug reg 0x05 = SerDes Test and System Mode Control
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
    val |= 0x0100; // bit 8 = RGMII_tx_clk_dly
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1e, val);

    // Disable hibernate
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1d, 0xb); // Hib Control and Auto-negotiation Test
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1e, 0x3c40); // disable hibernate

    // Config to external loopback
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1d, 0x11); // External Loopback selection
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
    val |= 0x0001; // enable ext loopback
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1e, val);

	// PHY AR8031 Integrated 10/100/1000 Gigabit
	// Reset & full duplex
	// Use default speed - after Pwer on reset - 1000Mbs
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0, 0x8140);
	imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0, &val);
	while (val == 0x8140)
		imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0, &val);
#else
	/* To enable AR8031 ouput a 125MHz clk from CLK_25M */
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xd, 0x7);
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xe, 0x8016);
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xd, 0x4007);
	imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0xe, &val);

	val &= 0xffe3;
	val |= 0x18;
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0xe, val);

	/* introduce tx clock delay */
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1d, 0x5);
	imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
	val |= 0x0100;
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1e, val);
#endif

}

void enet_phy_rework_ksz9021(imx_enet_priv_t * dev)
{
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x9, 0x1c00);
	
	/* min rx data delay */
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x0b, 0x8105);
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x0c, 0x0000);
	
	/* max rx/tx clock delay, min rx/tx control delay */
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x0b, 0x8104);
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x0c, 0xf0f0);
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x0b, 0x104);
}

/*!
 * This function initializes the PHY connected to the ENET controller.
 */
void imx_enet_phy_init(imx_enet_priv_t * dev)
{
    unsigned short value = 0;
    unsigned long id = 0;
	
	// Read PHY ID registers.
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_IDENTIFY_1, &value);
    id = (value & PHY_ID1_MASK) << PHY_ID1_SHIFT;
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_IDENTIFY_2, &value);
    id |= (value & PHY_ID2_MASK) << PHY_ID2_SHIFT;
    id &= 0xfffffff0; // mask off lower 4 bits
    
    switch (id)
    {
        case 0x00540088: // ?? PHY
            break;
        case PHY_LAN8700_ID:
            printf("ENET LAN8700 PHY: ID=%lx\n", id);
            break;
        case PHY_LAN8720_ID:
            printf("ENET LAN8720 PHY: ID=%lx\n", id);
            break;
        case PHY_AR8031_ID:
            printf("ENET AR8031 PHY: ID=%lx\n", id);
     		enet_phy_rework_ar8031(dev);
            break;
        case PHY_KSZ9021RN_ID:
            printf("ENET KSZ9021RN PHY: ID=%lx\n", id);
            enet_phy_rework_ksz9021(dev);
            break;
        default:
            printf("[Warning] ENET not connect right PHY: ID=%lx\n", id);
    }
    dev->phy_id = id;

    // Reset PHY
	imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, &value);
	value |= PHY_CTRL_RESET;
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, value);
    
    // Wait for reset to complete.
    do {
        imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, &value);
    } while (value & PHY_CTRL_RESET);
    
	/* restart auto-negotiation */
#if 1	
#if 1	
	imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, &value);
	value |= 0x1200;
	imx_enet_mii_write(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, value);
#else
    value = 0x8100;
    imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1f, value);
#endif
#endif
    
    // Read current PHY status.
    imx_enet_get_phy_status(dev);
}

uint32_t imx_enet_get_phy_status(imx_enet_priv_t * dev)
{
    uint16_t value;
    
    // Reset saved status.
    dev->status = 0;
    
    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_STATUS_REG, &value);
    printf("enet phy status %0d: %04x\n", dev->phy_addr, value);    //  0x7809 or 0x782d

    if (value & PHY_STATUS_LINK_ST)
    {
        dev->status |= ENET_STATUS_LINK_ON;
    }
    else
    {
        dev->status &= ~ENET_STATUS_LINK_ON;
    }
    
	if (dev->phy_id == PHY_AR8031_ID)
	{
#if 0
	    imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1b, &value); // Cable Diagnostic Tester (CDT)
	    if (value & (1 << 2))
	        dev->status |= ENET_STATUS_FULL_DPLX;
	    else
	        dev->status &= ~ENET_STATUS_FULL_DPLX;

	    if (value & 0x2)
	        dev->status |= ENET_STATUS_1000M;
	    else if (value & 0x1)
	        dev->status |= ENET_STATUS_100M;
	    else
	        dev->status |= ENET_STATUS_10M;
#else
		imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x11, &value); // PHY-Specific status reg
		printf("AR8031 reg 0x11 = %04x\n", value);
		if(value & (1<<13))
			dev->status |= ENET_STATUS_FULL_DPLX;
		else
			dev->status &= ~ENET_STATUS_FULL_DPLX;
	    if (((value>>14)&0x3) == 0x2)
	        dev->status |= ENET_STATUS_1000M;
	    else if (((value>>14)&0x3) == 0x2)
	        dev->status |= ENET_STATUS_100M;
	    else
	        dev->status |= ENET_STATUS_10M;
#endif
	}
	else if (dev->phy_id == PHY_KSZ9021RN_ID)
	{
		imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1f, &value);
		printf("KSZ9021 reg 0x1f = %04x\n", value);
		if (value & (1 << 3))
			dev->status |= ENET_STATUS_FULL_DPLX;
		else
			dev->status &= ~ENET_STATUS_FULL_DPLX;
		if (value & (1 << 6))
	        dev->status |= ENET_STATUS_1000M;
		else if (value & (1 << 5))
			dev->status |= ENET_STATUS_100M;
		else
			dev->status |= ENET_STATUS_10M;
	}
	else
	{
		if (value & 0xe000)
			dev->status |= ENET_STATUS_100M;
		else
			dev->status |= ENET_STATUS_10M;
		if (value & 0x5000)
			dev->status |= ENET_STATUS_FULL_DPLX;
		else
			dev->status &= ~ENET_STATUS_FULL_DPLX;
	}	
	
//     printf("ENET %0d: [ %s ] [ %s ] [ %s ]:\n", dev->phy_addr,
//            (dev->status & ENET_STATUS_FULL_DPLX) ? "FULL_DUPLEX" : "HALF_DUPLEX",
//            (dev->status & ENET_STATUS_LINK_ON) ? "connected" : "disconnected",
//            (dev->status & ENET_STATUS_1000M) ? "1000M bps" : (dev->status & ENET_STATUS_100M) ?
//            "100M bps" : "10M bps");

    return dev->status;
}

void imx_enet_phy_enable_external_loopback(imx_enet_priv_t * dev)
{
    uint16_t val;
    
    if (dev->phy_id == PHY_AR8031_ID)
    {
        // Disable hibernate
        imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1d, 0xb); // Hib Control and Auto-negotiation Test
        imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
        imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1e, 0x3c40); // disable hibernate

        // Config to external loopback
        imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1d, 0x11); // External Loopback selection
        imx_enet_mii_read(dev->enet_reg, dev->phy_addr, 0x1e, &val);
        val |= 0x0001; // enable ext loopback
        imx_enet_mii_write(dev->enet_reg, dev->phy_addr, 0x1e, val);
    }
}

unsigned long imx_enet_poll(imx_enet_priv_t * dev)
{
    volatile hw_enet_t *enet_reg = dev->enet_reg;
    unsigned int value = 0;

    value = enet_reg->EIR.U;
    enet_reg->EIR.U = value & (~ENET_EVENT_MII);

    if (value & ENET_EVENT_TX_ERR) {
        printf("WARNING[POLL]: There are error(%x) for transmit\n", value & ENET_EVENT_TX_ERR);
        dev->tx_busy = 0;
    } else {
        if (value & ENET_EVENT_TX) {
            dev->tx_busy = 0;
        }
    }

    if (value & ENET_EVENT_RX) {
        //imx_enet_check_rx_bd(sc);
    }

    if (value & ENET_EVENT_HBERR) {
        printf("WARNGING[POLL]: Hearbeat error!\n");
    }

    if (value & ENET_EVENT_EBERR) {
        printf("WARNING[POLL]: Ethernet Bus Error!\n");
    }

    return value;
}

int imx_enet_send(imx_enet_priv_t * dev, unsigned char *buf, int length, unsigned long key)
{
    volatile hw_enet_t *enet_reg = dev->enet_reg;
    imx_enet_bd_t *p = dev->tx_cur;

    memcpy(p->data, buf, length);

    p->length = length;
    p->status &= ~(BD_TX_ST_LAST | BD_TX_ST_RDY | BD_TX_ST_TC | BD_TX_ST_ABC);
    p->status |= BD_TX_ST_LAST | BD_TX_ST_RDY | BD_TX_ST_TC;

    if (p->status & BD_TX_ST_WRAP) {
        p = dev->tx_bd;
    } else
        p++;

    dev->tx_cur = p;
    dev->tx_busy = 1;
    dev->tx_key = key;
    enet_reg->TDAR.U = ENET_RX_TX_ACTIVE;

    return 0;
}

int imx_enet_recv(imx_enet_priv_t * dev, unsigned char *buf, int *length)
{
    imx_enet_bd_t *p = dev->rx_cur;
    volatile hw_enet_t *enet_reg = dev->enet_reg;

    if (p->status & BD_RX_ST_EMPTY) {
        return -1;
    }

    if (!(p->status & BD_RX_ST_LAST)) {
        printf("BUG[RX]: status=%x, length=%x\n", p->status, p->length);
        return -1;
    }

    if ((p->status & BD_RX_ST_ERRS) || (p->length > ENET_FRAME_LEN)) {
        printf("BUG1[RX]: status=%x, length=%x\n", p->status, p->length);
    } else {
        memcpy(buf, p->data, p->length - 4);
        *length = p->length - 4;
    }

    p->status = (p->status & BD_RX_ST_WRAP) | BD_RX_ST_EMPTY;

    if (p->status & BD_RX_ST_WRAP) {
        p = dev->rx_bd;
    } else {
        p++;
    }

    dev->rx_cur = p;
    enet_reg->ECR.U |= ENET_ETHER_EN;
    enet_reg->RDAR.U |= ENET_RX_TX_ACTIVE;

    return 0;
}

int imx_enet_init(imx_enet_priv_t * dev, unsigned long reg_base, int phy_addr)
{
    dev->enet_reg = (hw_enet_t *) reg_base;
    dev->tx_busy = 0;
    dev->status = 0;
    dev->phy_addr = phy_addr;   /* 0 or 1 */

    imx_enet_bd_init(dev, phy_addr);

    imx_enet_chip_init(dev);

    //imx_enet_phy_init(dev);

    return 0;
}

static void imx_enet_set_mac_address(volatile hw_enet_t * enet_reg, unsigned char *enaddr)
{
    unsigned long value;

    value = enaddr[0];
    value = (value << 8) + enaddr[1];
    value = (value << 8) + enaddr[2];
    value = (value << 8) + enaddr[3];
    enet_reg->PALR.U = value;

    value = enaddr[4];
    value = (value << 8) + enaddr[5];
    enet_reg->PAUR.U = (value << 16);
}

void imx_enet_start(imx_enet_priv_t * dev, unsigned char *enaddr)
{
    imx_enet_set_mac_address(dev->enet_reg, enaddr);

    dev->tx_busy = 0;
    dev->enet_reg->ECR.U |= ENET_ETHER_EN | ENET_ETHER_SPEED_1000M | ENET_ETHER_LITTLE_ENDIAN;
    dev->enet_reg->RDAR.U |= ENET_RX_TX_ACTIVE;
}

void imx_enet_stop(imx_enet_priv_t * dev)
{
    dev->enet_reg->ECR.U &= ~ENET_ETHER_EN;
}

int imx_enet_isolate_phy(imx_enet_priv_t * dev)
{
    unsigned short value = 0;

    if (!imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, &value)) {
        value |= (0x01 << 10);
        if (!imx_enet_mii_write(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, value)) {
            return 0;
        }
    }
    return -1;
}

int imx_enet_unisolate_phy(imx_enet_priv_t * dev)
{
    unsigned short value = 0;

    if (!imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, &value)) {
        value &= ~(0x01 << 10);
        if (!imx_enet_mii_write(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, value)) {
            imx_enet_mii_read(dev->enet_reg, dev->phy_addr, PHY_CTRL_REG, &value);
            return 0;
        }
    }
    return -1;
}

int imx_enet_mii_type(imx_enet_priv_t * dev, enum imx_mii_type mii_type)
{
    volatile hw_enet_t *enet_reg = dev->enet_reg;

    switch (mii_type) {
    case MII:
        /*clear RMII and RGMII */
        enet_reg->RCR.U &= ~(ENET_RCR_RMII_MODE | ENET_RCR_RGMII_EN);
        enet_reg->RCR.U |= ENET_RCR_MII_MODE;
        break;
    case RMII:
        enet_reg->RCR.U &= ~(ENET_RCR_RGMII_EN);
        enet_reg->RCR.U |= (ENET_RCR_MII_MODE | ENET_RCR_RMII_MODE);
        break;
    case RGMII:
        enet_reg->RCR.U &= ~(ENET_RCR_RMII_MODE | ENET_RCR_MII_MODE);
        enet_reg->RCR.U |= ENET_RCR_RGMII_EN;
        enet_reg->TFWR.U = 0x3f;    //for mx6dq
        break;
    default:
        printf("BUG:unknow MII type=%x\n", mii_type);
        break;
    }
    return 0;
}
