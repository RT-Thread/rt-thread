/*
 * Copyright (C) 2016 YunOS Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#ifndef CONFIG_KERNEL_NONE
#include <csi_kernel.h>
#endif
#include "ethernet_enc28j60.h"

#include "pin.h"
#include "soc.h"
#include "drv_spi.h"
#include "drv_gpio.h"
#include "drv_eth.h"
#include "drv_eth_phy.h"
#include "drv_eth_mac.h"

#include <errno.h>

#define NET_HWADDR_LEN  6
#define THIS_MODULE MODULE_DEV_ETH
#define MAX_SPI_TRANSFER_LEN 512
#define MAX_RECV_ERROR_CNT  50

static uint8_t  Enc28j60Bank;
static uint16_t NextPacketPtr;
gpio_pin_handle_t pin_int = NULL;

typedef int (*gpio_interrupt_t)(int irqno);

static spi_handle_t g_net_spi_hd = NULL;
static gpio_pin_handle_t   pgpio_pin_handle1;
//static k_sem_handle_t g_sem_spi_tx_hd = NULL;
//static k_sem_handle_t g_sem_spi_rx_hd = NULL;

static eth_mac_priv_t s_eth_instance[CONFIG_ETH_NUM];
static eth_phy_priv_t s_phy_instance[CONFIG_ETH_NUM];

static uint8_t g_hw_addr[NET_HWADDR_LEN] = {0};

static uint8_t enc28j60ReadOp(uint8_t op, uint8_t address);
static void enc28j60WriteOp(uint8_t op, uint8_t address, uint8_t data);
static void enc28j60ReadBuffer(const uint16_t len, uint8_t *data);
static void enc28j60WriteBuffer(uint16_t len, uint8_t *data);
static void enc28j60SetBank(uint8_t address);
static uint8_t enc28j60Read(uint8_t address);
static void enc28j60Write(uint8_t address, uint8_t data);
static uint32_t enc28j60PhyWrite(uint8_t phy_addr, uint8_t reg_addr, uint16_t  data);
static uint32_t enc28j60Phyregread(uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);
static void enc28j60Init(const uint8_t *macaddr);
static int enc28j60Reset(int obj);
static uint16_t enc28j60GetRxFreeSpace(void);
static void enc28j60_int_handle(uint32_t event);
static int enc28j60_set_interrupt(pin_t gpio_pin);
extern void mdelay(uint32_t ms);

/**
 * interrupt handle function to post sem for handle
 *
 * @param irqno the irq number of network
 *
 */
static void enc28j60_int_handle(uint32_t event)
{
    eth_mac_priv_t *eth_priv = &s_eth_instance[0];
    uint8_t int_stat, ptkcnt, estat;
    uint16_t freespace;
    uint16_t status_vec_ptr;
    uint8_t  status_vec[7];
    bool reset = 0;

    csi_gpio_pin_irq_set(pin_int, GPIO_IRQ_MODE_LOW_LEVEL, 0);
    //enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIE, EIE_INTIE);

    int_stat = enc28j60Read(EIR); /*  read EIR register data */;

    // error flags to be handled first
    if (int_stat & EIR_RXERIF) {
        ptkcnt = enc28j60Read(EPKTCNT);
        freespace = enc28j60GetRxFreeSpace();
#ifndef CONFIG_TEST_TTCP

        if ((ptkcnt == 0xFF) || (freespace < MAX_FRAMELEN)) {
            /*   do nothing, data in buffer will be read out */
            printf("Rx buffer has %d packets and %d bytes free space\n", ptkcnt, freespace);
        } else {
            printf("something is wrong other than no buffer.\n");
        }

#endif
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIR, EIR_RXERIF);

        if (ptkcnt > MAX_RECV_ERROR_CNT) {
            reset = 1;
        }
    }

    if (int_stat & EIR_TXERIF) {
        estat = enc28j60Read(ESTAT);

        if ((estat & ESTAT_TXABRT) || (estat & ESTAT_LATECOL)) {
            printf("ESTAT=0x%x\n", estat);
            status_vec_ptr = enc28j60Read(ETXNDL);
            status_vec_ptr |= enc28j60Read(ETXNDH) << 8;
            status_vec_ptr++;
            enc28j60Write(ERDPTL, status_vec_ptr);
            enc28j60Write(ERDPTH, status_vec_ptr >> 8);
            enc28j60ReadBuffer(7, status_vec);
            printf("status vector:0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x\n",
                   status_vec[0], status_vec[1], status_vec[2], status_vec[3], status_vec[4], status_vec[5], status_vec[6]);
            reset = 1;
        }

        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIR, EIR_TXERIF);
    }

    if (reset) {
        if (enc28j60Reset(RST_ENC28J60_ALL) == 0) {
            printf("reset OK \n");
            /*  init enc28j60 module */
            uint8_t macaddr[6];

            csi_eth_mac_get_macaddr(NULL, (eth_mac_addr_t *)macaddr);

            enc28j60Init(macaddr);

            printf("enc28j60 init OK \n");
            enc28j60_set_interrupt(PA5_A8);
            enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE);
            return;
        }
    }

    if (int_stat & EIR_PKTIF) {
        ptkcnt = enc28j60Read(EPKTCNT); //just for debugging

        //EIR_PKTIF will be cleared if all data is read out
        eth_priv->cb_event((eth_mac_handle_t)eth_priv, CSI_ETH_MAC_EVENT_RX_FRAME);
    }

    if (int_stat & EIR_TXIF) {
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIR, EIR_TXIF);
        //eth_priv->cb_event((eth_mac_handle_t)eth_priv, CSI_ETH_MAC_EVENT_TX_FRAME);
    }

    if (int_stat & EIR_LINKIF) {
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIR, EIR_LINKIF);
        eth_priv->cb_event((eth_mac_handle_t)eth_priv, CSI_ETH_MAC_EVENT_LINK_CHANGE);
    }

    //clear all interrupt falgs. In fact, EIR_PKTIF can not be cleared
    enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIR, 0xFF & (~(EIR_PKTIF | EIR_LINKIF)));

    // don't enable interrupt if events not handled
    if (!(int_stat & (EIR_PKTIF | EIR_LINKIF))) {
        //enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE);
        csi_gpio_pin_irq_set(pin_int, GPIO_IRQ_MODE_LOW_LEVEL, 1);
    }

}

void enc28j60_spi_transfer_callback(spi_event_e event)
{
    if (event == SPI_EVENT_TRANSFER_COMPLETE) {

    } else if (event == SPI_EVENT_TX_COMPLETE) {
        //csi_kernel_sem_post(g_sem_spi_tx_hd);
    } else if (event == SPI_EVENT_RX_COMPLETE) {
        //csi_kernel_sem_post(g_sem_spi_rx_hd);
    } else if (event == SPI_EVENT_DATA_LOST) {
        printf("TRANSFER_DATA_LOST\n");
    } else {
        printf("TRANSFER_MODE_FAULT\n");
    }
}

void enc28j60_spi_cs_status_change(int status)
{
    csi_gpio_pin_write(pgpio_pin_handle1, status);
}

static int32_t enc28j60_spi_send(spi_handle_t handle, const void *data, uint32_t num)
{
    csi_spi_send(handle, data, num, 1);
    // csi_kernel_sem_wait(g_sem_spi_tx_hd, -1);

    return 0;
}

static int32_t enc28j60_spi_receive(spi_handle_t handle, void *data, uint32_t num)
{
    csi_spi_receive(handle, data, num, 1);
    //csi_kernel_sem_wait(g_sem_spi_rx_hd, -1);

    return 0;
}

/**
 * read ctrl register
 * @param op operation cmd
 * @param register address
 *
 * @return
 *        -register data
 */
static uint8_t enc28j60ReadOp(uint8_t op, uint8_t address)
{
    uint8_t   dat = 0;

    ENC28J60_CSL();

    dat = (op | (address & ADDR_MASK));

    uint8_t rdata[1] = {0};

    enc28j60_spi_send(g_net_spi_hd, &dat, 1);

    enc28j60_spi_receive(g_net_spi_hd, &rdata[0], 1);

    /* do dummy read if needed (for mac and mii, see datasheet page 29) */
    if (address & 0x80) {
        enc28j60_spi_receive(g_net_spi_hd, &rdata[0], 1);
    }

    /* release CS */
    ENC28J60_CSH();
    return rdata[0];

}

/**
 * write ctrl cmd to register
 * @param op operation cmd
 * @param register address
 * @param data the data to be set
 *
 * @return
 *        -NULL
 */
static void enc28j60WriteOp(uint8_t op, uint8_t address, uint8_t data)
{
    char dat = 0;

    ENC28J60_CSL();
    /* issue write command */
    dat = op | (address & ADDR_MASK);

    enc28j60_spi_send(g_net_spi_hd, &dat, 1);

    dat = data;
    enc28j60_spi_send(g_net_spi_hd, &dat, 1);

    ENC28J60_CSH();
}

/**
 * read buffer data
 * @param len the data length waint to read
 * @param data the data buffer
 *
 * @return
 *        -NULL
 */
static void enc28j60ReadBuffer(uint16_t len, uint8_t *data)
{
    char ops_ctr = ENC28J60_READ_BUF_MEM;

    ENC28J60_CSL();
    /* issue read command */

    enc28j60_spi_send(g_net_spi_hd, &ops_ctr, 1);

    enc28j60_spi_receive(g_net_spi_hd, (char *)&data[0], len);

    ENC28J60_CSH();
}

/**
 * write data to buffer
 * @param len the data length waint to write
 * @param data the data buffer pointer
 *
 * @return
 *        -NULL
 */
static void enc28j60WriteBuffer(uint16_t len, uint8_t *data)
{
    char ops_ctr = ENC28J60_WRITE_BUF_MEM;

    ENC28J60_CSL();
    /* issue write command */
    //drv_porting_spi_write(NULL, &ops_ctr, 1);

    enc28j60_spi_send(g_net_spi_hd, &ops_ctr, 1);

    enc28j60_spi_send(g_net_spi_hd, &data[0], len);

    ENC28J60_CSH();
}

/**
 * select the bank to operation
 * @param address the bank address
 *
 * @return
 *        -NULL
 */
static void enc28j60SetBank(uint8_t address)
{
    /* set the bank (if needed) */
    if ((address & BANK_MASK) != Enc28j60Bank) {
        /* set the bank */
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, (ECON1_BSEL1 | ECON1_BSEL0));
        enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK) >> 5);
        Enc28j60Bank = (address & BANK_MASK);
    }
}

/**
 *  read ctrl register data
 * @param address the ctrl register address
 *
 * @return
 *        -ctrl register data
 */
static uint8_t enc28j60Read(uint8_t address)
{
    /* set the bank */
    enc28j60SetBank(address);
    /* do the read */
    return enc28j60ReadOp(ENC28J60_READ_CTRL_REG, address);
}

/**
 *  write data to ctrl register
 * @param address the ctrl register address
 * @param data ctrl register cmd
 *
 * @return
 *        - NULL
 */
static void enc28j60Write(uint8_t address, uint8_t data)
{
    /* set the bank */
    enc28j60SetBank(address);
    /* do the write */
    enc28j60WriteOp(ENC28J60_WRITE_CTRL_REG, address, data);
}

/**
 *  write data to phy register
 * @param address the phy register address
 * @param data phy register cmd
 *
 * @return
 *        - NULL
 */
static uint32_t enc28j60PhyWrite(uint8_t phy_addr, uint8_t reg_addr, uint16_t  data)
{
    int retry = 0;

    /* set the PHY register address */
    enc28j60Write(MIREGADR, phy_addr);
    /* write the PHY data */
    enc28j60Write(MIWRL, data);
    enc28j60Write(MIWRH, data >> 8);

    /* wait until the PHY write completes */
    while (enc28j60Read(MISTAT) & MISTAT_BUSY) {
        retry++;

        if (retry > 0xFFF) {
            printf("write Phyreg_status error \n");
            return -1;
        }
    }

    return 0;
}

/**
 *  read data from phy register
 * @param address the phy register address
 *
 * @return
 *        -the data of phy register
 */
static uint32_t enc28j60Phyregread(uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    uint8_t  temp;
    int      retry = 0;

    temp = enc28j60Read(MICMD);
    /*  set the PHY register address */
    enc28j60Write(MIREGADR, phy_addr);

    enc28j60Write(MICMD, temp | MICMD_MIIRD);

    /*  Loop to wait until the PHY register has been read through the MII */
    while ((enc28j60Read(MISTAT) & MISTAT_BUSY)) {
        if (retry++ > 0xFFF) {
            printf("read Phyreg_status error \n");
            return -1;
        }
    }

    enc28j60Write(MICMD, temp & (~MICMD_MIIRD));   /* clear bit MICMD.MIIRD */

    /*  Obtain results and return */
    *data = enc28j60Read(MIRDL);
    *data |= (enc28j60Read(MIRDH) << 8);

    return *data;
}

/**
 *   init ethernet ctrl register
 * @param address the MAC address
 *
 * @return
 *        - NULL
 */
static void enc28j60Init(const uint8_t *macaddr)
{
    /*  check CLKRDY bit to see if reset is complete */
    /*  The CLKRDY does not work. See Rev. B4 Silicon Errata point. Just wait. */
    NextPacketPtr = RXSTART_INIT;
    /*  Rx start */
    enc28j60Write(ERXSTL, RXSTART_INIT & 0xFF);
    enc28j60Write(ERXSTH, RXSTART_INIT >> 8);
    /*  set receive pointer address */
    enc28j60Write(ERXRDPTL, RXSTART_INIT & 0xFF);
    enc28j60Write(ERXRDPTH, RXSTART_INIT >> 8);
    /*  RX end */
    enc28j60Write(ERXNDL, RXSTOP_INIT & 0xFF);
    enc28j60Write(ERXNDH, RXSTOP_INIT >> 8);
    /*  TX start */
    enc28j60Write(ETXSTL, TXSTART_INIT & 0xFF);
    enc28j60Write(ETXSTH, TXSTART_INIT >> 8);
    /*  TX end */
    enc28j60Write(ETXNDL, TXSTOP_INIT & 0xFF);
    enc28j60Write(ETXNDH, TXSTOP_INIT >> 8);

    /* do bank 1 stuff, packet filter:
     For broadcast packets we allow only ARP packtets
     All other packets should be unicast only for our mac (MAADR) */
#if LWIP_IPV4 && LWIP_IPV6
    enc28j60Write(ERXFCON, ERXFCON_UCEN | ERXFCON_CRCEN | ERXFCON_PMEN | ERXFCON_MCEN);
    enc28j60Write(EPMM0, 0x3f); /* ARP Pattern Match Filter */
    enc28j60Write(EPMM1, 0x30);
    enc28j60Write(EPMCSL, 0xf9);
    enc28j60Write(EPMCSH, 0xf7);
#elif LWIP_IPV6
    enc28j60Write(ERXFCON, ERXFCON_UCEN | ERXFCON_CRCEN | ERXFCON_MCEN);
#else   /* for IPv6 without ARP and BC */
    enc28j60Write(ERXFCON, ERXFCON_UCEN | ERXFCON_CRCEN | ERXFCON_PMEN);
    enc28j60Write(EPMM0, 0x3f); /* ARP Pattern Match Filter */
    enc28j60Write(EPMM1, 0x30);
    enc28j60Write(EPMCSL, 0xf9);
    enc28j60Write(EPMCSH, 0xf7);
#endif
    /* do bank 2 stuff */
    /* enable MAC receive */
    enc28j60Write(MACON1, MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS);
    /*   bring MAC out of reset */
    enc28j60Write(MACON2, 0x00);
    /*   enable automatic padding to 60bytes and CRC operations */
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN | MACON3_FULDPX); /* MACON3_HFRMLEN */
    /*   set inter-frame gap (non-back-to-back) */
    enc28j60Write(MAIPGL, 0x12);
    enc28j60Write(MAIPGH, 0x0C);
    /*   set inter-frame gap (back-to-back) */
    enc28j60Write(MABBIPG, 0x15);
    /*   Set the maximum packet size which the controller will accept */
    /*   Do not send packets longer than MAX_FRAMELEN: */
    enc28j60Write(MAMXFLL, MAX_FRAMELEN & 0xFF);
    enc28j60Write(MAMXFLH, MAX_FRAMELEN >> 8);

    /*   do bank 3 stuff */
    /*   write MAC address */
    /*   NOTE: MAC address in ENC28J60 is byte-backward */
    enc28j60Write(MAADR5, macaddr[0]);
    enc28j60Write(MAADR4, macaddr[1]);
    enc28j60Write(MAADR3, macaddr[2]);
    enc28j60Write(MAADR2, macaddr[3]);
    enc28j60Write(MAADR1, macaddr[4]);
    enc28j60Write(MAADR0, macaddr[5]);
    enc28j60PhyWrite(PHCON1, 0, PHCON1_PDPXMD);

    /*   no loopback of transmitted frames */
    enc28j60PhyWrite(PHCON2, 0, PHCON2_HDLDIS);

    enc28j60PhyWrite(PHIE, 0, PHIE_PLNKIE | PHIE_PGEIE);

    /*   switch to bank 0 */
    enc28j60SetBank(ECON1);
    /*   enable interrutps */
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_PKTIE | EIE_LINKIE | EIE_TXIE | EIE_TXERIE | EIE_RXERIE);
    /*   enable packet reception */
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);

    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE);
}

/**
 *  set mac addr
 * @param macaddr the macaddr for net
 *
 * @return
 *        - NULL
 */
static void enc28j60Setmacaddr(const uint8_t *macaddr)
{
    ENC28J60_CSH();
    /*   enable MAC receive */
    enc28j60Write(MACON1, MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS);
    /*   bring MAC out of reset */
    enc28j60Write(MACON2, 0x00);
    /*   enable automatic padding to 60bytes and CRC operations */
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FULDPX);

    /*   write MAC address */
    /*   NOTE: MAC address in ENC28J60 is byte-backward */
    enc28j60Write(MAADR5, macaddr[0]);
    enc28j60Write(MAADR4, macaddr[1]);
    enc28j60Write(MAADR3, macaddr[2]);
    enc28j60Write(MAADR2, macaddr[3]);
    enc28j60Write(MAADR1, macaddr[4]);
    enc28j60Write(MAADR0, macaddr[5]);

}

/**
 *  Hard reset enc28j60
 * @param void
 *
 */
static void enc28j60hardreset(void)
{
    gpio_pin_handle_t pin = NULL;
    pin = csi_gpio_pin_initialize(PA1);
    csi_gpio_pin_config(pin, GPIO_MODE_PULLNONE, GPIO_DIRECTION_OUTPUT);
    csi_gpio_pin_write(pin, 0);  /* LOW */
    mdelay(3);
    csi_gpio_pin_write(pin, 1);
    mdelay(3);

    printf("NET HARD RESET\n");
}

/**
 *  reset enc28j60
 * @param obj the net work object
 *
 * @return
 *        - status
 */
static int enc28j60Reset(int obj)
{
    int retry = 0;

    ENC28J60_CSH();

    if (obj == RST_ENC28J60_ALL) {
        /* first net hard reset */
        enc28j60hardreset();
        enc28j60WriteOp(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);

        while (!(enc28j60Read(ESTAT) & ESTAT_CLKRDY)) {
            if (retry++ > 0xFFF) {
                return -1;
            }
        }
    } else if (obj == RST_ENC28J60_TX) {
        enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRST);
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRST);
    } else if (obj == RST_ENC28J60_RX) {
        enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXRST);
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_RXRST);
    }

    return 0;
}

/**
 *  get rx free space
 * @param void
 *
 * @return
 *        - status 0
 */
static uint16_t enc28j60GetRxFreeSpace(void)
{
    uint16_t free_space;
    uint16_t erxrdpt;
    uint16_t erxwrpt;

    erxrdpt = enc28j60Read(ERXRDPTL);
    erxrdpt |= enc28j60Read(ERXRDPTH) << 8;

    erxwrpt = enc28j60Read(ERXWRPTL);
    erxwrpt |= enc28j60Read(ERXWRPTH) << 8;

    if (erxwrpt > erxrdpt) {
        free_space = (RXSTOP_INIT - RXSTART_INIT) - (erxwrpt - erxrdpt);
    } else if (erxwrpt == erxrdpt) {
        free_space = (RXSTOP_INIT - RXSTART_INIT);
    } else {
        free_space = erxrdpt - erxwrpt - 1;
    }

    return free_space;
}

/**
 *  enc28j60 interrupt set
 * @param interrupt_cb the interrupt callback function
 *
 * @return
 *        - status 0
 */

static int enc28j60_set_interrupt(pin_t gpio_pin)
{
    uint32_t ret = 0;

    pin_int = csi_gpio_pin_initialize(gpio_pin);

    ret = csi_gpio_pin_config(pin_int, GPIO_MODE_PULLUP, GPIO_DIRECTION_INPUT);

    ret = csi_gpio_pin_irq_set(pin_int, GPIO_IRQ_MODE_LOW_LEVEL, 1);

    return 0;
}

csi_drv_version_t csi_eth_phy_get_version(eth_phy_handle_t handle)
{
    csi_drv_version_t version = {0xff, 0xff};
    uint16_t dev_version, dev_version1;

    if (handle == NULL) {
        return version;
    }

    enc28j60Phyregread(PHHID1, 0, &dev_version);
    enc28j60Phyregread(PHHID2, 0, &dev_version1);

    version.api = CSI_ETH_PHY_API_VERSION;
    version.drv = (dev_version << 16) + dev_version1;

    return version;
}

eth_phy_handle_t csi_eth_phy_initialize(csi_eth_phy_read_t fn_read, csi_eth_phy_write_t fn_write)
{
    eth_phy_priv_t *phy_priv;

    if ((fn_read == NULL) || (fn_write == NULL)) {
        return NULL;
    }

    csi_gpio_port_initialize(0, (gpio_event_cb_t)enc28j60_int_handle);

    phy_priv = &s_phy_instance[0];

    phy_priv->phy_read  = fn_read ;
    phy_priv->phy_write = fn_write;

    return (eth_mac_handle_t)phy_priv;
}

int32_t csi_eth_phy_uninitialize(eth_phy_handle_t handle)
{
    if (handle == NULL) {
        return -1;
    }

    return 0;
}


int32_t csi_eth_phy_deinit(void)
{
    /*   no loopback of transmitted frames */
    enc28j60PhyWrite(PHCON2, 0, PHCON2_HDLDIS);
    /*  LINK AND ALL PHY Interrupt Enable */
    enc28j60PhyWrite(PHIE, 0, PHIE_PLNKIE | PHIE_PGEIE);
    return 0;
}

int32_t csi_eth_phy_power_control(eth_phy_handle_t handle, eth_power_state_t state)
{
    uint16_t power_control;

    if (handle == NULL) {
        return -1;
    }

    enc28j60Phyregread(PHCON1, 0, &power_control);

    if (state == CSI_ETH_POWER_FULL) {
        power_control &= ~(1 << 11);
    } else if (state == CSI_ETH_POWER_OFF) {
        power_control |= (1 << 11);
    } else if (state == CSI_ETH_POWER_LOW) {

    } else {
        return -1;
    }

    enc28j60PhyWrite(PHCON1, 0, power_control);

    return 0;
}

int32_t csi_eth_phy_set_interface(eth_phy_handle_t handle, uint32_t interface)
{
    if (handle == NULL) {
        return -1;
    }

    return 0;
}

eth_link_info_t csi_eth_phy_get_linkinfo(eth_phy_handle_t handle)
{
    eth_link_info_t net_link_info = {0};

    if (handle == NULL) {
        return net_link_info;
    }

    net_link_info.duplex = 1;
    net_link_info.speed = 1;

    return net_link_info;
}

int32_t csi_eth_phy_set_mode(eth_phy_handle_t handle, uint32_t mode)
{
    uint32_t phy_mode = 0;

    if (handle == NULL) {
        return -1;
    }

    eth_phy_priv_t *phy_priv = (eth_phy_priv_t *)handle;

    phy_priv->link_info.speed    = (mode & 0x03);
    phy_priv->link_info.duplex   = (mode & 0x04);
    phy_priv->link_info.Loopback = (mode & 0x05);

    if (phy_priv->link_info.duplex) {
        phy_mode |= PHCON1_PDPXMD;
    } else {
        phy_mode &= ~(PHCON1_PDPXMD);
    }

    if (phy_priv->link_info.Loopback) {
        phy_mode |= PHCON1_PLOOPBK;
    } else {
        phy_mode &= ~(PHCON1_PLOOPBK);
    }

    enc28j60PhyWrite(PHCON1, 0, phy_mode);

    return 0;
}

eth_link_state_t csi_eth_phy_get_linkstate(eth_phy_handle_t handle)
{
    uint16_t phstat1;
    uint16_t phstat2;
    eth_link_state_t state;

    if (handle == NULL) {
        return -1;
    }

    uint8_t status = enc28j60Read(EIR);

    if (status & EIR_LINKIF) {
        /*  as tested, need to read twice */
        enc28j60Phyregread(PHSTAT1, 0, &phstat1);
        enc28j60Phyregread(PHSTAT1, 0, &phstat2);

        phstat1 |= phstat2;

        if (phstat1 & 0x0004) {
            state = ETH_LINK_UP;
        } else {
            state = ETH_LINK_DOWN;
        }

        /*  resets to "0" when read */
        enc28j60Phyregread(PHIR, 0, NULL);

        return state;
    }

    return -1;
}

eth_mac_handle_t csi_eth_mac_initialize(eth_event_cb_t cb)
{
    eth_mac_priv_t *eth_priv;
    static int eth_mac_init = 0;
    int ret = -1;

    if (cb == NULL) {
        printf("cb  == null\n");
        return NULL;
    }

    eth_priv = &s_eth_instance[0];
    eth_priv->cb_event = cb;

    if (eth_mac_init == 0) {
        //init spi get spi_handle
        g_net_spi_hd = csi_spi_initialize(SPI1_TX, SPI1_RX, SPI1_CLK, SPI1_CS, (spi_event_cb_t)enc28j60_spi_transfer_callback, NULL);

        //spi_handle success goto config spi
        if (g_net_spi_hd != NULL) {

            ret = csi_spi_config(g_net_spi_hd, SYSTEM_CLOCK, 2000000, SPI_MODE_MASTER, SPI_FORMAT_CPOL0_CPHA0,
                                 SPI_ORDER_MSB2LSB, SPI_SS_MASTER_SW, 7);

            pgpio_pin_handle1 = csi_gpio_pin_initialize(SPI1_CS);
            csi_gpio_pin_config(pgpio_pin_handle1, GPIO_MODE_PULLNONE, GPIO_DIRECTION_OUTPUT);

        }

        eth_mac_init = 1;
    }

    if ((ret == 0) || (eth_mac_init == 1)) {

        if (enc28j60Reset(RST_ENC28J60_ALL) == 0) {
            printf("reset OK \n");
            /*  init enc28j60 module */
            uint8_t macaddr[6];

            csi_eth_mac_get_macaddr(NULL, (eth_mac_addr_t *)macaddr);

            enc28j60Init(macaddr);

            printf("enc28j60 init OK \n");
            enc28j60_set_interrupt(PA5_A8);

            //g_sem_spi_tx_hd = csi_kernel_sem_new(1, 0);
            //g_sem_spi_rx_hd = csi_kernel_sem_new(1, 0);

            return (eth_mac_handle_t)eth_priv;
        }
    }

    return NULL;
}

int32_t csi_eth_mac_uninitialize(eth_mac_handle_t handle)
{
    if (handle == NULL) {
        return -1;
    }

    return 0;
}

csi_drv_version_t csi_eth_mac_get_version(eth_mac_handle_t handle)
{
    csi_drv_version_t mac_version = {0xff, 0xff};

    if (handle == NULL) {
        return mac_version;
    }

    mac_version.api = CSI_ETH_PHY_API_VERSION;
    mac_version.drv = enc28j60Read(EREVID);

    return mac_version;
}

int32_t csi_eth_mac_power_control(eth_mac_handle_t handle, eth_power_state_t state)
{
    uint8_t pw_control;

    if (handle == NULL) {
        return -1;
    }

    pw_control = enc28j60Read(ECON2);

    if (state == CSI_ETH_POWER_FULL) {
        pw_control &= ~(1 << 11);
    } else if (state == CSI_ETH_POWER_LOW) {
        pw_control |= (1 << 11);
    } else if (state == CSI_ETH_POWER_OFF) {

    } else {
        return -1;
    }

    enc28j60Write(ECON2, pw_control);

    return 0;
}

int32_t csi_eth_mac_get_macaddr(eth_mac_handle_t handle, eth_mac_addr_t *mac)
{
    if ((handle == NULL) || (mac == NULL)) {
        return -1;
    }

    memcpy(mac, g_hw_addr, NET_HWADDR_LEN);
    return 0;
}

int32_t csi_eth_mac_set_macaddr(eth_mac_handle_t handle, const eth_mac_addr_t *mac)
{
    if ((handle == NULL) || (mac == NULL)) {
        return -1;
    }

    memcpy(g_hw_addr, mac, NET_HWADDR_LEN);
    printf("csiMAC: %02x:%02x:%02x:%02x:%02x:%02x\n", g_hw_addr[0], g_hw_addr[1], g_hw_addr[2],
           g_hw_addr[3], g_hw_addr[4], g_hw_addr[5]);

    enc28j60Setmacaddr(g_hw_addr);
    return 0;
}

int32_t csi_eth_mac_set_addrfilter(eth_mac_handle_t handle, const eth_mac_addr_t *addr, uint32_t num_addr)
{
    if ((handle == NULL) || (addr == NULL)) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_get_rx_framesize(eth_mac_handle_t handle)
{
    uint16_t len;
    uint16_t rxstat;

    if (handle == NULL) {
        return -1;
    }

    /*   check if a packet has been received and buffered
    if( !(enc28j60Read(EIR) & EIR_PKTIF) ){
    The above does not work. See Rev. B4 Silicon Errata point 6.  */
    if (enc28j60Read(EPKTCNT) == 0) {
        return (0);
    }

    /*   Set the read pointer to the start of the received packet  */
    enc28j60Write(ERDPTL, (NextPacketPtr));
    enc28j60Write(ERDPTH, (NextPacketPtr) >> 8);

    /*   read the next packet pointer */
    NextPacketPtr  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    NextPacketPtr |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;

    /*   read the packet length (see datasheet page 43) */
    len  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    len |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;
    len -= 4; /*  remove the CRC count */

    /*   limit retrieve length */
    if (len > MAX_FRAMELEN - 1) {
        printf("rx packet length is %d\n", len);
        len = MAX_FRAMELEN - 1;
        return -1;
    }

    /*   read the receive status (see datasheet page 43) */
    rxstat = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    rxstat |= (uint16_t)enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;

    /*   check CRC and symbol errors (see datasheet page 44, table 7-3): */
    /*   The ERXFCON.CRCEN is set by default. Normally we should not */
    /*   need to check this. */
    if ((rxstat & 0x80) == 0) {
        printf("rx status vector is 0x%x\n", rxstat);
        len = 0; // invalid
        return -1;
    }

    return len;
}

int32_t csi_eth_mac_get_rx_frametime(eth_mac_handle_t handle, eth_mac_time_t *time)
{
    if ((handle == NULL)) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_get_tx_frametime(eth_mac_handle_t handle, eth_mac_time_t *time)
{
    if (handle == NULL) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_control(eth_mac_handle_t handle, uint32_t control, uint32_t arg)
{
    if (handle == NULL) {
        return -1;
    }


    if (control == CSI_ETH_MAC_CONTROL_RX) {
        if (arg) {
            //enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE);
            csi_gpio_pin_irq_set(pin_int, GPIO_IRQ_MODE_LOW_LEVEL, 1);

        } else {
            //enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIE, EIE_INTIE);
            csi_gpio_pin_irq_set(pin_int, GPIO_IRQ_MODE_LOW_LEVEL, 0);
        }

        return 0;
    }

    return 0;
}

/**
 *   send a packet data
 * @param address the packet data length
 *
 * @return
 *        - sent data length
 */
int32_t csi_eth_mac_send_frame(eth_mac_handle_t handle, const uint8_t *frame, uint32_t len, uint32_t flags)
{
    int retry = 0;

    if ((handle == NULL) || (frame == NULL)) {
        return -1;
    }

    if (len > MAX_FRAMELEN) {
        printf("TX len %d is too large to send\n", len);
        return 0;
    }

    while (enc28j60Read(ECON1) & ECON1_TXRTS) {
        if (retry++ > 0xFFF) {
            printf("data not be sent out\n");
            return -1;
        }
    }

    /*   Set the write pointer to start of transmit buffer area */
    enc28j60Write(EWRPTL, TXSTART_INIT & 0xFF);
    enc28j60Write(EWRPTH, TXSTART_INIT >> 8);

    /*   Set the TXND pointer to correspond to the packet size given */
    /*   Status vector will be written at ETXND+1. */
    enc28j60Write(ETXNDL, (TXSTART_INIT + len) & 0xFF);
    enc28j60Write(ETXNDH, (TXSTART_INIT + len) >> 8);

    /*   write per-packet control byte (0x00 means use macon3 settings) */
    enc28j60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00);

    /*   copy the packet into the transmit buffer */
    enc28j60WriteBuffer(len, (uint8_t *)frame);

    /*   send the contents of the transmit buffer onto the network */
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);

    /*   Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12. */
    if ((enc28j60Read(EIR) & EIR_TXERIF)) {
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);
    }

    return len;
}

int32_t csi_eth_mac_read_frame(eth_mac_handle_t handle, uint8_t *frame, uint32_t len)
{
    uint32_t rlen;
    uint16_t rxstat;

    if ((handle == NULL) || (frame == NULL)) {
        return -1;
    }

    /*   check if a packet has been received and buffered
    if( !(enc28j60Read(EIR) & EIR_PKTIF) ){
    The above does not work. See Rev. B4 Silicon Errata point 6.  */
    if (enc28j60Read(EPKTCNT) == 0) {
        return (0);
    }

    /*   Set the read pointer to the start of the received packet  */
    enc28j60Write(ERDPTL, (NextPacketPtr));
    enc28j60Write(ERDPTH, (NextPacketPtr) >> 8);

    /*   read the next packet pointer */
    NextPacketPtr  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    NextPacketPtr |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;

    /*   read the packet length (see datasheet page 43) */
    rlen  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    rlen |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;
    rlen -= 4; /*  remove the CRC count */

    /*   limit retrieve length */
    if (rlen > MAX_FRAMELEN - 1) {
        printf("rx packet length is %d\n", rlen);
        rlen = MAX_FRAMELEN - 1;
        return -1;
    }

    /*   read the receive status (see datasheet page 43) */
    rxstat = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    rxstat |= (uint16_t)enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0) << 8;

    /*   check CRC and symbol errors (see datasheet page 44, table 7-3): */
    /*   The ERXFCON.CRCEN is set by default. Normally we should not */
    /*   need to check this. */
    if ((rxstat & 0x80) == 0) {
        printf("rx status vector is 0x%x\n", rxstat);
        rlen = 0; // invalid
        return -1;
    }

    /*   copy the packet from the receive buffer */
    enc28j60ReadBuffer(rlen, frame);

    /*   Move the RX read pointer to the start of the next received packet */
    /*   This frees the memory we just read out */
    enc28j60Write(ERXRDPTL, (NextPacketPtr));
    enc28j60Write(ERXRDPTH, (NextPacketPtr) >> 8);

    /*   decrement the packet counter indicate we are done with this packet */
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_AUTOINC | ECON2_PKTDEC);

    return rlen;

}

eth_capabilities_t csi_eth_mac_get_capabilities(eth_mac_handle_t handle)
{
    eth_capabilities_t  capab = {0};

    if (handle == NULL) {
        return capab;
    }

    eth_mac_priv_t *mac_priv = (eth_mac_priv_t *)handle;

    mac_priv->capabilities.mac_address = 1;

    capab = mac_priv->capabilities;

    return capab;
}

void csi_eth_mac_signal_event(eth_mac_handle_t handle, uint32_t event)
{
    if (handle == NULL) {
        return;
    }

}

int32_t csi_eth_mac_control_time(eth_mac_handle_t handle, uint32_t control, eth_mac_time_t *time)
{
    if (handle == NULL) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_phy_read(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    if ((handle == NULL) || (data == NULL)) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_phy_write(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    if ((handle == NULL)) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_add_framefilter(eth_mac_handle_t handle, const eth_frame_filter_t *filter)
{
    if ((handle == NULL) || (filter == NULL)) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_remove_framefilter(eth_mac_handle_t handle, uint32_t filter_id)
{
    if (handle == NULL) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_en_framefilter(eth_mac_handle_t handle, uint32_t filter_id, bool en)
{
    if (handle == NULL) {
        return -1;
    }

    return 0;
}

int32_t csi_eth_mac_get_framefilter(eth_mac_handle_t handle, eth_frame_filter_list_t *list, uint32_t *count_out, uint32_t max_count)
{
    if ((handle == NULL) || (list == NULL)) {
        return -1;
    }

    return 0;
}

