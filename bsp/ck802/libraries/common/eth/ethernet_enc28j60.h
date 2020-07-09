/****************************************************************************
 * csky/hardware/bsp/common/ethernet_enc28j60/ethernet_enc28j60.h
 *
 * Copyright (C) 2016 The YunOS Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ****************************************************************************/

#ifndef _ETHERNET_ENC28J60_H__
#define _ETHERNET_ENC28J60_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* ****** ETH ****** */
#define ETH_HEADER_LEN  14
/* values of certain bytes: */
#define ETHTYPE_ARP_H_V 0x08
#define ETHTYPE_ARP_L_V 0x06
#define ETHTYPE_IP_H_V  0x08
#define ETHTYPE_IP_L_V  0x00
/* byte positions in the ethernet frame:
 Ethernet type field (2bytes): */
#define ETH_TYPE_H_P    12
#define ETH_TYPE_L_P    13

#define ETH_DST_MAC     0
#define ETH_SRC_MAC     6


/* ******* ARP ******* */
#define ETH_ARP_OPCODE_REPLY_H_V 0x0
#define ETH_ARP_OPCODE_REPLY_L_V 0x02

#define ETHTYPE_ARP_L_V          0x06
/* arp.dst.ip */
#define ETH_ARP_DST_IP_P         0x26
/* arp.opcode */
#define ETH_ARP_OPCODE_H_P       0x14
#define ETH_ARP_OPCODE_L_P       0x15
/* arp.src.mac */
#define ETH_ARP_SRC_MAC_P        0x16
#define ETH_ARP_SRC_IP_P         0x1c
#define ETH_ARP_DST_MAC_P        0x20
#define ETH_ARP_DST_IP_P         0x26

/* ******* IP ******* */
#define IP_HEADER_LEN       20
/* ip.src */
#define IP_SRC_P            0x1a
#define IP_DST_P            0x1e
#define IP_HEADER_LEN_VER_P 0xe
#define IP_CHECKSUM_P       0x18
#define IP_TTL_P            0x16
#define IP_FLAGS_P          0x14
#define IP_P                0xe
#define IP_TOTLEN_H_P       0x10
#define IP_TOTLEN_L_P       0x11

#define IP_PROTO_P          0x17

#define IP_PROTO_ICMP_V     1
#define IP_PROTO_TCP_V      6
/* 17=0x11 */
#define IP_PROTO_UDP_V      17
/* ******* ICMP ******* */
#define ICMP_TYPE_ECHOREPLY_V   0
#define ICMP_TYPE_ECHOREQUEST_V 8

#define ICMP_TYPE_P             0x22
#define ICMP_CHECKSUM_P         0x24

/* ******* UDP ******* */
#define UDP_HEADER_LEN   8

#define UDP_SRC_PORT_H_P 0x22
#define UDP_SRC_PORT_L_P 0x23
#define UDP_DST_PORT_H_P 0x24
#define UDP_DST_PORT_L_P 0x25

#define UDP_LEN_H_P      0x26
#define UDP_LEN_L_P      0x27
#define UDP_CHECKSUM_H_P 0x28
#define UDP_CHECKSUM_L_P 0x29
#define UDP_DATA_P       0x2a

/* ******* TCP ******* */
#define TCP_SRC_PORT_H_P     0x22
#define TCP_SRC_PORT_L_P     0x23
#define TCP_DST_PORT_H_P     0x24
#define TCP_DST_PORT_L_P     0x25
/* the tcp seq number is 4 bytes 0x26-0x29 */
#define TCP_SEQ_H_P          0x26
#define TCP_SEQACK_H_P       0x2a
/* flags: SYN=2 */
#define TCP_FLAGS_P          0x2f
#define TCP_FLAGS_SYN_V      2
#define TCP_FLAGS_FIN_V      1
#define TCP_FLAGS_PUSH_V     8
#define TCP_FLAGS_SYNACK_V   0x12
#define TCP_FLAGS_ACK_V      0x10
#define TCP_FLAGS_PSHACK_V   0x18
/* plain len without the options: */
#define TCP_HEADER_LEN_PLAIN 20
#define TCP_HEADER_LEN_P     0x2e
#define TCP_CHECKSUM_H_P     0x32
#define TCP_CHECKSUM_L_P     0x33
#define TCP_OPTIONS_P        0x36


/* ENC28J60 Control Registers
 Control register definitions are a combination of address,
 bank number, and Ethernet/MAC/PHY indicator bits.
 - Register address        (bits 0-4)
 - Bank number        (bits 5-6)
 - MAC/PHY indicator        (bit 7) */
#define ADDR_MASK        0x1F
#define BANK_MASK        0x60
#define SPRD_MASK        0x80
/* All-bank registers */
#define EIE              0x1B
#define EIR              0x1C
#define ESTAT            0x1D
#define ECON2            0x1E
#define ECON1            0x1F
/* Bank 0 registers */
#define ERDPTL           (0x00|0x00)
#define ERDPTH           (0x01|0x00)
#define EWRPTL           (0x02|0x00)
#define EWRPTH           (0x03|0x00)
#define ETXSTL           (0x04|0x00)
#define ETXSTH           (0x05|0x00)
#define ETXNDL           (0x06|0x00)
#define ETXNDH           (0x07|0x00)
#define ERXSTL           (0x08|0x00)
#define ERXSTH           (0x09|0x00)
#define ERXNDL           (0x0A|0x00)
#define ERXNDH           (0x0B|0x00)
#define ERXRDPTL         (0x0C|0x00)
#define ERXRDPTH         (0x0D|0x00)
#define ERXWRPTL         (0x0E|0x00)
#define ERXWRPTH         (0x0F|0x00)
#define EDMASTL          (0x10|0x00)
#define EDMASTH          (0x11|0x00)
#define EDMANDL          (0x12|0x00)
#define EDMANDH          (0x13|0x00)
#define EDMADSTL         (0x14|0x00)
#define EDMADSTH         (0x15|0x00)
#define EDMACSL          (0x16|0x00)
#define EDMACSH          (0x17|0x00)
/* Bank 1 registers */
#define EHT0             (0x00|0x20)
#define EHT1             (0x01|0x20)
#define EHT2             (0x02|0x20)
#define EHT3             (0x03|0x20)
#define EHT4             (0x04|0x20)
#define EHT5             (0x05|0x20)
#define EHT6             (0x06|0x20)
#define EHT7             (0x07|0x20)
#define EPMM0            (0x08|0x20)
#define EPMM1            (0x09|0x20)
#define EPMM2            (0x0A|0x20)
#define EPMM3            (0x0B|0x20)
#define EPMM4            (0x0C|0x20)
#define EPMM5            (0x0D|0x20)
#define EPMM6            (0x0E|0x20)
#define EPMM7            (0x0F|0x20)
#define EPMCSL           (0x10|0x20)
#define EPMCSH           (0x11|0x20)
#define EPMOL            (0x14|0x20)
#define EPMOH            (0x15|0x20)
#define EWOLIE           (0x16|0x20)
#define EWOLIR           (0x17|0x20)
#define ERXFCON          (0x18|0x20)
#define EPKTCNT          (0x19|0x20)
/* Bank 2 registers */
#define MACON1           (0x00|0x40|0x80)
#define MACON2           (0x01|0x40|0x80)
#define MACON3           (0x02|0x40|0x80)
#define MACON4           (0x03|0x40|0x80)
#define MABBIPG          (0x04|0x40|0x80)
#define MAIPGL           (0x06|0x40|0x80)
#define MAIPGH           (0x07|0x40|0x80)
#define MACLCON1         (0x08|0x40|0x80)
#define MACLCON2         (0x09|0x40|0x80)
#define MAMXFLL          (0x0A|0x40|0x80)
#define MAMXFLH          (0x0B|0x40|0x80)
#define MAPHSUP          (0x0D|0x40|0x80)
#define MICON            (0x11|0x40|0x80)
#define MICMD            (0x12|0x40|0x80)
#define MIREGADR         (0x14|0x40|0x80)
#define MIWRL            (0x16|0x40|0x80)
#define MIWRH            (0x17|0x40|0x80)
#define MIRDL            (0x18|0x40|0x80)
#define MIRDH            (0x19|0x40|0x80)
/* Bank 3 registers */
#define MAADR1           (0x00|0x60|0x80)
#define MAADR0           (0x01|0x60|0x80)
#define MAADR3           (0x02|0x60|0x80)
#define MAADR2           (0x03|0x60|0x80)
#define MAADR5           (0x04|0x60|0x80)
#define MAADR4           (0x05|0x60|0x80)
#define EBSTSD           (0x06|0x60)
#define EBSTCON          (0x07|0x60)
#define EBSTCSL          (0x08|0x60)
#define EBSTCSH          (0x09|0x60)
#define MISTAT           (0x0A|0x60|0x80)
#define EREVID           (0x12|0x60)
#define ECOCON           (0x15|0x60)
#define EFLOCON          (0x17|0x60)
#define EPAUSL           (0x18|0x60)
#define EPAUSH           (0x19|0x60)
/* PHY registers */
#define PHCON1           0x00
#define PHSTAT1          0x01
#define PHHID1           0x02
#define PHHID2           0x03
#define PHCON2           0x10
#define PHSTAT2          0x11
#define PHIE             0x12
#define PHIR             0x13
#define PHLCON           0x14

/* ENC28J60 ERXFCON Register Bit Definitions */
#define ERXFCON_UCEN     0x80
#define ERXFCON_ANDOR    0x40
#define ERXFCON_CRCEN    0x20
#define ERXFCON_PMEN     0x10
#define ERXFCON_MPEN     0x08
#define ERXFCON_HTEN     0x04
#define ERXFCON_MCEN     0x02
#define ERXFCON_BCEN     0x01
/* ENC28J60 EIE Register Bit Definitions */
#define EIE_INTIE        0x80
#define EIE_PKTIE        0x40
#define EIE_DMAIE        0x20
#define EIE_LINKIE       0x10
#define EIE_TXIE         0x08
#define EIE_WOLIE        0x04
#define EIE_TXERIE       0x02
#define EIE_RXERIE       0x01
#define EIE_ALLCLOSE     0xff

/* ENC28J60 EIR Register Bit Definitions */
#define EIR_PKTIF        0x40
#define EIR_DMAIF        0x20
#define EIR_LINKIF       0x10
#define EIR_TXIF         0x08
#define EIR_WOLIF        0x04
#define EIR_TXERIF       0x02
#define EIR_RXERIF       0x01
#define EIR_ALLINTS      0x7b  /* All interrupts */

/* ENC28J60 ESTAT Register Bit Definitions */
#define ESTAT_INT        0x80
#define ESTAT_LATECOL    0x10
#define ESTAT_RXBUSY     0x04
#define ESTAT_TXABRT     0x02
#define ESTAT_CLKRDY     0x01
/*  ENC28J60 ECON2 Register Bit Definitions */
#define ECON2_AUTOINC    0x80
#define ECON2_PKTDEC     0x40
#define ECON2_PWRSV      0x20
#define ECON2_VRPS       0x08
/*  ENC28J60 ECON1 Register Bit Definitions */
#define ECON1_TXRST      0x80
#define ECON1_RXRST      0x40
#define ECON1_DMAST      0x20
#define ECON1_CSUMEN     0x10
#define ECON1_TXRTS      0x08
#define ECON1_RXEN       0x04
#define ECON1_BSEL1      0x02
#define ECON1_BSEL0      0x01
/*  ENC28J60 MACON1 Register Bit Definitions */
#define MACON1_LOOPBK    0x10
#define MACON1_TXPAUS    0x08
#define MACON1_RXPAUS    0x04
#define MACON1_PASSALL   0x02
#define MACON1_MARXEN    0x01
/*  ENC28J60 MACON2 Register Bit Definitions */
#define MACON2_MARST     0x80
#define MACON2_RNDRST    0x40
#define MACON2_MARXRST   0x08
#define MACON2_RFUNRST   0x04
#define MACON2_MATXRST   0x02
#define MACON2_TFUNRST   0x01
/*  ENC28J60 MACON3 Register Bit Definitions */
#define MACON3_PADCFG2   0x80
#define MACON3_PADCFG1   0x40
#define MACON3_PADCFG0   0x20
#define MACON3_TXCRCEN   0x10
#define MACON3_PHDRLEN   0x08
#define MACON3_HFRMLEN   0x04
#define MACON3_FRMLNEN   0x02
#define MACON3_FULDPX    0x01
/*  ENC28J60 MICMD Register Bit Definitions */
#define MICMD_MIISCAN    0x02
#define MICMD_MIIRD      0x01
/*  ENC28J60 MISTAT Register Bit Definitions */
#define MISTAT_NVALID    0x04
#define MISTAT_SCAN      0x02
#define MISTAT_BUSY      0x01
/*  ENC28J60 PHY PHCON1 Register Bit Definitions */
#define PHCON1_PRST      0x8000
#define PHCON1_PLOOPBK   0x4000
#define PHCON1_PPWRSV    0x0800
#define PHCON1_PDPXMD    0x0100
/*  ENC28J60 PHY PHSTAT1 Register Bit Definitions */
#define PHSTAT1_PFDPX    0x1000
#define PHSTAT1_PHDPX    0x0800
#define PHSTAT1_LLSTAT   0x0004
#define PHSTAT1_JBSTAT   0x0002
/*  ENC28J60 PHY PHCON2 Register Bit Definitions */
#define PHCON2_FRCLINK   0x4000
#define PHCON2_TXDIS     0x2000
#define PHCON2_JABBER    0x0400
#define PHCON2_HDLDIS    0x0100
/*  ENC28J60 PHY PHIE Register Bit Definitions */
#define PHIE_PLNKIE      0x0010
#define PHIE_PGEIE       0x0002

/*  ENC28J60 Packet Control Byte Bit Definitions */
#define PKTCTRL_PHUGEEN  0x08
#define PKTCTRL_PPADEN   0x04
#define PKTCTRL_PCRCEN   0x02
#define PKTCTRL_POVERRIDE 0x01

/*  SPI operation codes */
#define ENC28J60_READ_CTRL_REG  0x00
#define ENC28J60_READ_BUF_MEM   0x3A
#define ENC28J60_WRITE_CTRL_REG 0x40
#define ENC28J60_WRITE_BUF_MEM  0x7A
#define ENC28J60_BIT_FIELD_SET  0x80
#define ENC28J60_BIT_FIELD_CLR  0xA0
#define ENC28J60_SOFT_RESET     0xFF

/*  The RXSTART_INIT should be zero. See Rev. B4 Silicon Errata
 buffer boundaries applied to internal 8K ram
 the entire available packet buffer space is allocated

 start with recbuf at 0/ */
#define RXSTART_INIT   0x0
/*  receive buffer end */
#define RXSTOP_INIT    (0x1FFF-0x0600-1)
/*  start TX buffer at 0x1FFF-0x0600, pace for one full ethernet frame (~1500 bytes) */
#define TXSTART_INIT   (0x1FFF-0x0600)
/*  stp TX buffer at end of mem */
#define TXSTOP_INIT    0x1FFF

/*  max frame length which the conroller will accept: */
#define MAX_FRAMELEN   1518        /*  (note: maximum ethernet frame length would be 1518) */

void enc28j60_spi_cs_status_change(int status);

#if 1//defined CONFIG_PHOBOS_GENERAL
#define PA5_A8         15
#define PA1            12

#define ENC28J60_CSL()  enc28j60_spi_cs_status_change(0);  //yunos_bsp_gpio_set_value(20, GPIO_VALUE_LOW);  /* SPI_CS_LOW */

#define ENC28J60_CSH()  enc28j60_spi_cs_status_change(1);  //yunos_bsp_gpio_set_value(20, GPIO_VALUE_HIGH);   /* SPI_CS_HIGH */

#else
#define PA5_A8         47
#define ENC28J60_CSL() enc28j60_spi_cs_status_change(0);  //yunos_bsp_gpio_set_value(44, GPIO_VALUE_LOW);    /* SPI_CS_LOW */

#define ENC28J60_CSH() enc28j60_spi_cs_status_change(1); //yunos_bsp_gpio_set_value(44, GPIO_VALUE_HIGH);   /* SPI_CS_HIGH */
#endif

typedef struct _spi_net_ops_t {
    int (*init)(const uint8_t *macaddr);
    int (*recv)(uint8_t *, uint16_t);
    int (*send)(uint8_t *, uint16_t);
    int (*reset)(void);
    int (*irq_enable)(int);
    int (*set_macaddr)(const uint8_t *macaddr);
    int (*get_link_status)(void);
} net_ops_t;

enum enc28j60_reset {
    RST_ENC28J60_ALL,
    RST_ENC28J60_TX,
    RST_ENC28J60_RX
};

int yunos_bsp_enc28j60_init(const uint8_t *macaddr);
int yunos_bsp_enc28j60_reset(void);
int yunos_bsp_enc28j60_get_link_status(void);
int yunos_bsp_enc28j60_set_irq_enable(int enable);
int yunos_bsp_enc28j60_get_interrupt_status(void);
int yunos_bsp_enc28j60_set_interrupt_status(int status);
//int yunos_bsp_enc28j60_set_interrupt(gpio_interrupt_t interrupt_cb);
int yunos_bsp_enc28j60_get_pkt_cnt(void);
int yunos_bsp_enc28j60_net_init(void);
int yunos_bsp_enc28j60_set_macaddr(const uint8_t *macaddr);
net_ops_t *yunos_bsp_spi_net_get_ctrl_ops(void);
int yunos_bsp_enc28j60_handle_int_error(int status);

int yunos_bsp_enc28j60_send_start(uint16_t len);
void yunos_bsp_enc28j60_send_data(uint8_t *packet, uint16_t len);
void yunos_bsp_enc28j60_send_end(void);

int yunos_bsp_enc28j60_recv_start(uint16_t maxlen);
int yunos_bsp_enc28j60_recv_data(uint8_t *packet, uint16_t len);
void yunos_bsp_enc28j60_recv_end(void);

void yunos_bsp_enc28j60_hard_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* _ETHERNET_ENC28J60_H__ */
