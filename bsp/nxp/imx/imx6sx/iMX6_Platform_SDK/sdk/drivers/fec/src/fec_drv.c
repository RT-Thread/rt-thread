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
 * @file fec_drv.c
 * @brief Driver of the i.MX FEC controller.
 *
 * @ingroup diag_fec
 */

#include "sdk.h"
#include "fec/fec.h"
#include "fec_private.h"

/*!
 *Global variable which defines the buffer descriptions for receiving frame
 * 	comment:: it must aligned by 128-bits.
 */
static imx_fec_bd_t imx_fec_rx_bd[FEC_BD_RX_NUM * NUM_OF_ETH_DEVS] __attribute__ ((aligned(32)));

/*!
 *Global variable which defines the buffer descriptions for receiving frame
 * 	comment:: it must aligned by 128-bits.
 */
static imx_fec_bd_t imx_fec_tx_bd[FEC_BD_TX_NUM * NUM_OF_ETH_DEVS] __attribute__ ((aligned(32)));

/*!
 * Global variable which contains the frame buffers ,
 */
static unsigned char imx_fec_rx_buf[FEC_BD_RX_NUM * NUM_OF_ETH_DEVS][2048]
    __attribute__ ((aligned(32)));

/*!
 * Global variable which contains the frame buffers ,
 */
static unsigned char imx_fec_tx_buf[FEC_BD_TX_NUM * NUM_OF_ETH_DEVS][2048]
    __attribute__ ((aligned(32)));

/*!
 * This function gets the value of the PHY registers through the MII interface.
 */
int imx_fec_mii_read(volatile hw_fec_t * fec_reg, unsigned char phy_addr,
                      unsigned char reg_addr, unsigned short int *value)
{
    unsigned long waiting = FEC_MII_TIMEOUT;

    if (fec_reg->EIR.U & FEC_EVENT_MII) {
        fec_reg->EIR.U = FEC_EVENT_MII;
    }

    fec_reg->MMFR.U = FEC_MII_READ(phy_addr, reg_addr);   /*Write CMD */

    while (1) {
        if (fec_reg->EIR.U & FEC_EVENT_MII) {
            fec_reg->EIR.U = FEC_EVENT_MII;
            break;
        }
        if ((--waiting) == 0)
            return -1;

        hal_delay_us(FEC_MII_TICK);
    }

    *value = FEC_MII_GET_DATA(fec_reg->MMFR.U);
    return 0;
}

/*!
 * This function sets the value of the PHY registers through the MII interface.
 */
int imx_fec_mii_write(volatile hw_fec_t * fec_reg, unsigned char phy_addr,
                       unsigned char reg_addr, unsigned short int value)
{
    unsigned long waiting = FEC_MII_TIMEOUT;

    if (fec_reg->EIR.U & FEC_EVENT_MII) {
        fec_reg->EIR.U = FEC_EVENT_MII;
    }

    fec_reg->MMFR.U = FEC_MII_WRITE(phy_addr, reg_addr, value);   /* Write CMD */

    while (1) {
        if (fec_reg->EIR.U & FEC_EVENT_MII) {
            fec_reg->EIR.U = FEC_EVENT_MII;
            break;
        }

        if ((--waiting) == 0)
            return -1;

        hal_delay_us(FEC_MII_TICK);
    }

    return 0;
}

/*!
 * The function initializes the description buffer for receiving or transmitting.
 */
static void imx_fec_bd_init(imx_fec_priv_t * dev, int dev_idx)
{
    int i;
    imx_fec_bd_t *p;
    imx_fec_bd_t *rx_bd_base = imx_fec_rx_bd, *tx_bd_base = imx_fec_tx_bd;

    rx_bd_base += (dev_idx * FEC_BD_RX_NUM);
    tx_bd_base += (dev_idx * FEC_BD_TX_NUM);

    p = dev->rx_bd = (imx_fec_bd_t *) rx_bd_base;

    for (i = 0; i < FEC_BD_RX_NUM; i++, p++) {
        p->status = BD_RX_ST_EMPTY;
        p->length = 0;
        p->data = (unsigned char *)imx_fec_rx_buf[i + dev_idx * FEC_BD_RX_NUM];
        //printf("rx bd %x, buffer is %x\n", (unsigned int)p, (unsigned int)p->data);
    }

    dev->rx_bd[i - 1].status |= BD_RX_ST_WRAP;
    dev->rx_cur = dev->rx_bd;

    p = dev->tx_bd = (imx_fec_bd_t *) tx_bd_base;

    for (i = 0; i < FEC_BD_TX_NUM; i++, p++) {
        p->status = 0;
        p->length = 0;
        p->data = (unsigned char *)imx_fec_tx_buf[i + dev_idx * FEC_BD_TX_NUM];
       // printf("tx bd %x, buffer is %x\n", (unsigned int)p, (unsigned int)p->data);
    }

    dev->tx_bd[i - 1].status |= BD_TX_ST_WRAP;
    dev->tx_cur = dev->tx_bd;

    /*TODO:: add the sync function for items */
}

/*!
 * This function initializes the FEC controller.
 */
static void imx_fec_chip_init(imx_fec_priv_t * dev)
{
    volatile hw_fec_t *fec_reg = (hw_fec_t *) dev->fec_reg;
	unsigned int ipg_clk;

    fec_reg->ECR.U = FEC_RESET;

    while (fec_reg->ECR.U & FEC_RESET) {
        hal_delay_us(FEC_COMMON_TICK);
    }

    fec_reg->EIMR.U = 0x00000000;
    fec_reg->EIR.U = 0xFFFFFFFF;

    /*
     * setup the MII gasket for RMII mode
     */
    fec_reg->RCR.U = (fec_reg->RCR.U & ~(0x0000003F)) | FEC_RCR_MII_MODE | FEC_RCR_FCE | FEC_RCR_PROM;
    fec_reg->TCR.U |= FEC_TCR_FDEN;
    fec_reg->MIBC.U |= FEC_MIB_DISABLE;

    fec_reg->IAUR.U = 0;
    fec_reg->IALR.U = 0;
    fec_reg->GAUR.U = 0;
    fec_reg->GALR.U = 0;

    /*TODO:: Use MII_SPEED(IPG_CLK) to get the value */
	ipg_clk = get_main_clock(IPG_CLK);
    fec_reg->MSCR.U = (fec_reg->MSCR.U & (~0x7e)) | (((ipg_clk + 499999) / 5000000) << 1); 

    /*Enable ETHER_EN */
    fec_reg->EMRBR.U = 2048 - 16;
    fec_reg->ERDSR.U = (unsigned long)dev->rx_bd;
    fec_reg->ETDSR.U = (unsigned long)dev->tx_bd;
}

/*!
 * This function initializes the PHY connected to the FEC controller.
 */
void imx_fec_phy_init(imx_fec_priv_t * dev)
{
    unsigned short value = 0;
    unsigned long id = 0;
	
	/* read phy id */
    imx_fec_mii_read(dev->fec_reg, dev->phy_addr, PHY_IDENTIFY_1, &value);
    id = (value & PHY_ID1_MASK) << PHY_ID1_SHIFT;
    imx_fec_mii_read(dev->fec_reg, dev->phy_addr, PHY_IDENTIFY_2, &value);
    id |= (value & PHY_ID2_MASK) << PHY_ID2_SHIFT;
    
    switch (id & 0xfffffff0)
    {
        case 0x00540088:
            break;
        case PHY_LAN8700_ID:
            printf("FEC LAN8700 PHY: ID=%lx\n", id);
            break;
        case PHY_LAN8720_ID:
            printf("FEC LAN8720 PHY: ID=%lx\n", id);
            break;
        default:
            printf("[Warning] FEC not connect right PHY: ID=%lx\n", id);
    }
    dev->phy_id = id;

	/* re-start Auto Neg */
    imx_fec_mii_read(dev->fec_reg, dev->phy_addr, PHY_CTRL_REG, &value);
	value |= 0x1200;
    imx_fec_mii_write(dev->fec_reg, dev->phy_addr, PHY_CTRL_REG, value);
	
	/* read phy status */
	imx_fec_get_phy_status(dev);
}

uint32_t imx_fec_get_phy_status(imx_fec_priv_t * dev)
{
    uint16_t value;
    
    // Reset saved status.
    dev->status = 0;
    
    imx_fec_mii_read(dev->fec_reg, dev->phy_addr, PHY_STATUS_REG, &value);
    printf("fec phy status %0d: %04x\n", dev->phy_addr, value);    //  0x7809 or 0x782d

    if (value & PHY_STATUS_LINK_ST) {
        dev->status |= FEC_STATUS_LINK_ON;
    } else {
        dev->status &= ~FEC_STATUS_LINK_ON;
    }
	if (value & (PHY_STATUS_100TXF | PHY_STATUS_100TXH | PHY_STATUS_100T4))
        dev->status |= FEC_STATUS_100M;
	else
        dev->status |= FEC_STATUS_10M;
	if (value & (PHY_STATUS_100TXF | PHY_STATUS_10TF))
		dev->status |= FEC_STATUS_FULL_DPLX;
	else
		dev->status &= ~FEC_STATUS_FULL_DPLX;

//     printf("FEC %0d: [ %s ] [ %s ] [ %s ]:\n", dev->phy_addr,
//            (dev->status & FEC_STATUS_FULL_DPLX) ? "FULL_DUPLEX" : "HALF_DUPLEX",
//            (dev->status & FEC_STATUS_LINK_ON) ? "connected" : "disconnected",
//            (dev->status & FEC_STATUS_1000M) ? "1000M bps" : (dev->status & FEC_STATUS_100M) ?
//            "100M bps" : "10M bps");
    
    return dev->status;
}

unsigned long imx_fec_poll(imx_fec_priv_t * dev)
{
    volatile hw_fec_t *fec_reg = dev->fec_reg;
    unsigned int value = 0;

    value = fec_reg->EIR.U;
    fec_reg->EIR.U = value & (~FEC_EVENT_MII);

    if (value & FEC_EVENT_TX_ERR) {
        printf("WARNING[POLL]: There are error(%x) for transmit\n", value & FEC_EVENT_TX_ERR);
        dev->tx_busy = 0;
    } else {
        if (value & FEC_EVENT_TX) {
            dev->tx_busy = 0;
        }
    }

    if (value & FEC_EVENT_RX) {
        //imx_fec_check_rx_bd(sc);
    }

    if (value & FEC_EVENT_HBERR) {
        printf("WARNGING[POLL]: Hearbeat error!\n");
    }

    if (value & FEC_EVENT_EBERR) {
        printf("WARNING[POLL]: Ethernet Bus Error!\n");
    }

    return value;
}

int imx_fec_send(imx_fec_priv_t * dev, unsigned char *buf, int length, unsigned long key)
{
    volatile hw_fec_t *fec_reg = dev->fec_reg;
    imx_fec_bd_t *p = dev->tx_cur;

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
    fec_reg->TDAR.U = FEC_RX_TX_ACTIVE;

    return 0;
}

int imx_fec_recv(imx_fec_priv_t * dev, unsigned char *buf, int *length)
{
    imx_fec_bd_t *p = dev->rx_cur;
    volatile hw_fec_t *fec_reg = dev->fec_reg;

    if (p->status & BD_RX_ST_EMPTY) {
        return -1;
    }

    if (!(p->status & BD_RX_ST_LAST)) {
        printf("BUG[RX]: status=%x, length=%x\n", p->status, p->length);
        return -1;
    }

    if ((p->status & BD_RX_ST_ERRS) || (p->length > FEC_FRAME_LEN)) {
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
    fec_reg->ECR.U |= FEC_ETHER_EN;
    fec_reg->RDAR.U |= FEC_RX_TX_ACTIVE;

    return 0;
}

int imx_fec_init(imx_fec_priv_t * dev, unsigned long reg_base, int phy_addr)
{
    dev->fec_reg = (hw_fec_t *) reg_base;
    dev->tx_busy = 0;
    dev->status = 0;
    dev->phy_addr = phy_addr;   /* 0 or 1 */

    imx_fec_bd_init(dev, phy_addr);

    imx_fec_chip_init(dev);

    //imx_fec_phy_init(dev);

    return 0;
}

static void imx_fec_set_mac_address(volatile hw_fec_t * fec_reg, unsigned char *enaddr)
{
    unsigned long value;

    value = enaddr[0];
    value = (value << 8) + enaddr[1];
    value = (value << 8) + enaddr[2];
    value = (value << 8) + enaddr[3];
    fec_reg->PALR.U = value;

    value = enaddr[4];
    value = (value << 8) + enaddr[5];
    fec_reg->PAUR.U = (value << 16);
}

void imx_fec_start(imx_fec_priv_t * dev, unsigned char *enaddr)
{
    imx_fec_set_mac_address(dev->fec_reg, enaddr);

    dev->tx_busy = 0;
    dev->fec_reg->ECR.U |= FEC_ETHER_EN;
    dev->fec_reg->RDAR.U |= FEC_RX_TX_ACTIVE;
}

void imx_fec_stop(imx_fec_priv_t * dev)
{
    dev->fec_reg->ECR.U &= ~FEC_ETHER_EN;
}

int imx_fec_isolate_phy(imx_fec_priv_t * dev)
{
    unsigned short value = 0;

    if (!imx_fec_mii_read(dev->fec_reg, dev->phy_addr, PHY_CTRL_REG, &value)) {
        value |= (0x01 << 10);
        if (!imx_fec_mii_write(dev->fec_reg, dev->phy_addr, PHY_CTRL_REG, value)) {
            return 0;
        }
    }
    return -1;
}

int imx_fec_unisolate_phy(imx_fec_priv_t * dev)
{
    unsigned short value = 0;

    if (!imx_fec_mii_read(dev->fec_reg, dev->phy_addr, PHY_CTRL_REG, &value)) {
        value &= ~(0x01 << 10);
        if (!imx_fec_mii_write(dev->fec_reg, dev->phy_addr, PHY_CTRL_REG, value)) {
            imx_fec_mii_read(dev->fec_reg, dev->phy_addr, PHY_CTRL_REG, &value);
            return 0;
        }
    }
    return -1;
}

int imx_fec_mii_type(imx_fec_priv_t * dev, enum imx_mii_type mii_type)
{
    switch (mii_type) {
    case RMII:
		/*
		 * setup the MII gasket for RMII mode
		 */
		
		/* disable the gasket */
		FEC_MIIGSK_ENR = 0;
		
		/* wait for the gasket to be disabled */
		while (FEC_MIIGSK_ENR & FEC_MIIGSK_ENR_READY)
			hal_delay_us(FEC_MII_TICK);
		
		/* configure gasket for RMII, 50 MHz, no loopback, and no echo */
		FEC_MIIGSK_CFGR = FEC_MIIGSK_CFGR_IF_MODE_RMII;
		
		/* re-enable the gasket */
		FEC_MIIGSK_ENR = FEC_MIIGSK_ENR_EN;
		while(!(FEC_MIIGSK_ENR & FEC_MIIGSK_ENR_READY))
			hal_delay_us(FEC_MII_TICK);
        break;
    default:
        printf("BUG:unknow MII type=%x\n", mii_type);
        break;
    }
    return 0;
}
