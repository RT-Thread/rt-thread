/*!
    \file    gd32h7xx_mdio.h
    \brief   definitions for the MDIO

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_MDIO_H
#define GD32H7XX_MDIO_H

#include "gd32h7xx.h"

/* MDIO definitions */
#define MDIO                          MDIO_BASE                      /*!< MDIO base address */

/* registers definitions */
#define MDIO_CTL                      REG32((MDIO) + 0x00000000U)    /*!< MDIO control register */
#define MDIO_RFRM                     REG32((MDIO) + 0x00000004U)    /*!< MDIO received frame information register */
#define MDIO_RDATA                    REG32((MDIO) + 0x00000008U)    /*!< MDIO received data register */
#define MDIO_RADDR                    REG32((MDIO) + 0x0000000CU)    /*!< MDIO received address register */
#define MDIO_TDATA                    REG32((MDIO) + 0x00000010U)    /*!< MDIO transfer data register */
#define MDIO_CFG                      REG32((MDIO) + 0x00000014U)    /*!< MDIO configuration register */
#define MDIO_STAT                     REG32((MDIO) + 0x00000018U)    /*!< MDIO status register */
#define MDIO_INTEN                    REG32((MDIO) + 0x0000001CU)    /*!< MDIO interrupt enable register */
#define MDIO_PIN                      REG32((MDIO) + 0x00000020U)    /*!< MDIO pin value register */
#define MDIO_TO                       REG32((MDIO) + 0x00000024U)    /*!< MDIO timeout register */

/* bits definitions */
/* MDIO_CTL */
#define MDIO_CTL_SWRST                BIT(0)                         /*!< reset MDIO block */
#define MDIO_CTL_PHYB                 BIT(1)                         /*!< MDIO PHY bit length */

/* MDIO_RFRM */
#define MDIO_RFRM_ROP                 BITS(0,1)                      /*!< received frame field OP */
#define MDIO_RFRM_RPHY                BITS(2,6)                      /*!< received frame field PHYADR */
#define MDIO_RFRM_RDEV                BITS(7,11)                     /*!< received frame field DEVADD */
#define MDIO_RFRM_RTA                 BITS(12,13)                    /*!< received frame field TA */

/* MDIO_RDATA */
#define MDIO_RDATA_RDATA              BITS(0,15)                     /*!< received frame field DATA */

/* MDIO_RADDR */
#define MDIO_RADDR_RADDR              BITS(0,15)                     /*!< received frame field ADDRESS */

/* MDIO_TDATA */
#define MDIO_TDATA_TDATA              BITS(0,15)                     /*!< data that is transmitted */

/* MDIO_CFG */
#define MDIO_CFG_PHYSW                BITS(0,4)                      /*!< software provided PHYADR */
#define MDIO_CFG_EPHYSEL              BITS(5,9)                      /*!< selects expected PHYADR */
#define MDIO_CFG_EDEVADD              BITS(10,14)                    /*!< expected DEVADD */

/* MDIO_STAT */
#define MDIO_STAT_WRFRM               BIT(0)                         /*!< set at end bit of a write data frame if DEVADD and PHYADR both match */
#define MDIO_STAT_ADDRFRM             BIT(1)                         /*!< set at end bit of an address frame if DEVADD and PHYADR both match */
#define MDIO_STAT_RDINCFRM            BIT(2)                         /*!< set at end bit of a post read increment address frame if DEVADD and PHYADR both match */
#define MDIO_STAT_RDFRM               BIT(3)                         /*!< set at end bit of a read data frame if DEVADD and PHYADR both match */
#define MDIO_STAT_DEVM                BIT(4)                         /*!< set at end bit of DEVADD if DEVADD matches */
#define MDIO_STAT_DEVNM               BIT(5)                         /*!< set at end bit of DEVADD if DEVADD nonmatches */
#define MDIO_STAT_PHYM                BIT(6)                         /*!< set at end bit of PHYADR if PHYADR matches */
#define MDIO_STAT_PHYNM               BIT(7)                         /*!< set at end bit of PHYADR if PHYADR nonmatches */
#define MDIO_STAT_TANM                BIT(8)                         /*!< set at end bit of TA of a write frame if the received TA nonmatches expected ��10�� */
#define MDIO_STAT_TO                  BIT(9)                         /*!< timeout flag */
#define MDIO_STAT_UDR                 BIT(10)                        /*!< transmit underrun flag */
#define MDIO_STAT_OVR                 BIT(11)                        /*!< receive overrun flag */
#define MDIO_STAT_RBNE                BIT(13)                        /*!< read data buffer not empty flag */

/* MDIO_INTEN */
#define MDIO_INTEN_WRFRMIE            BIT(0)                         /*!< interrupt requested when WRFRM bit becomes active */
#define MDIO_INTEN_ADDRFRMIE          BIT(1)                         /*!< interrupt requested when ADDRFRM bit becomes active */
#define MDIO_INTEN_RDINCFRMIE         BIT(2)                         /*!< interrupt requested when RDINCFRM bit becomes active */
#define MDIO_INTEN_RDFRMIE            BIT(3)                         /*!< interrupt requested when RDFRM bit becomes active */
#define MDIO_INTEN_DEVMIE             BIT(4)                         /*!< interrupt requested when DEVM bit becomes active */
#define MDIO_INTEN_DEVNMIE            BIT(5)                         /*!< interrupt requested when DEVNM bit becomes active */
#define MDIO_INTEN_PHYMIE             BIT(6)                         /*!< interrupt requested when PHYM bit becomes active */
#define MDIO_INTEN_PHYNMIE            BIT(7)                         /*!< interrupt requested when PHYNM bit becomes active */
#define MDIO_INTEN_TANMIE             BIT(8)                         /*!< interrupt requested when TANM bit becomes active */
#define MDIO_INTEN_TOIE               BIT(9)                         /*!< interrupt requested when TO bit becomes active */
#define MDIO_INTEN_UDRIE              BIT(10)                        /*!< interrupt requested when UDR bit becomes active */
#define MDIO_INTEN_OVRIE              BIT(11)                        /*!< interrupt requested when OVR bit becomes active */
#define MDIO_INTEN_RBNEIE             BIT(13)                        /*!< interrupt requested when RBNE bit becomes active */

/* MDIO_PIN */
#define MDIO_PIN_PHYPIN               BITS(0,4)                      /*!< pin value read from hardware PRTADR[4:0] pins */

/* MDIO_TO */
#define MDIO_TO_TOEN                  BIT(0)                         /*!< timeout enable */
#define MDIO_TO_TOCNT                 BITS(1,16)                     /*!< timeout counter */

/* constants definitions */
/* MDIO PHY bit length definitions */
#define MDIO_PHY_BITS_3               MDIO_CTL_PHYB                  /*!< MDIO PHY uses 3 bits */
#define MDIO_PHY_BITS_5               ((uint32_t)0x00000000U)        /*!< MDIO PHY uses 5 bits */

/* software provided PHYADR configuration definitions */
#define CFG_PHYSW(regval)             (BITS(0,4)&((uint32_t)(regval) << 0U))

/* expected PHYADR selection definitions */
#define CFG_EPHYSEL(regval)           (BITS(5,9)&((uint32_t)(regval) << 5U))
#define MDIO_PHYADR_HARDWARE          ((uint32_t)0x00000000U)         /*!< sets expected PHYADR = PHYPIN[4:0] */
#define MDIO_PHYADR_SOFTWARE          ((uint32_t)0x0000001FU)         /*!< sets expected PHYADR = PHYSW[4:0] */
#define MDIO_PHYADR_HW_SW_MIX(regval) (BITS(0,4)&((uint32_t)(regval)))/*!< software PHYADR bit select */

/* expected DEVADD configuration definitions */
#define CFG_EDEVADD(regval)           (BITS(10,14)&((uint32_t)(regval) << 10U))

/* get value of register bit field */
#define GET_RFRM_ROP(regval)          GET_BITS((regval),0,1)         /*!< get value of MDIO_RFRM_ROP bit field */
#define GET_RFRM_RPHY(regval)         GET_BITS((regval),2,6)         /*!< get value of MDIO_RFRM_RPHY bit field */
#define GET_RFRM_RDEV(regval)         GET_BITS((regval),7,11)        /*!< get value of MDIO_RFRM_RDEV bit field */
#define GET_RFRM_RTA(regval)          GET_BITS((regval),12,13)       /*!< get value of MDIO_RFRM_RTA bit field */
#define GET_RDATA_RDATA(regval)       GET_BITS((regval),0,15)        /*!< get value of MDIO_RDATA_RDATA bit field */
#define GET_RADDR_RADDR(regval)       GET_BITS((regval),0,15)        /*!< get value of MDIO_RADDR_RADDR bit field */
#define GET_PIN_PHYPIN(regval)        GET_BITS((regval),0,4)         /*!< get value of MDIO_PIN_PHYPIN bit field */

/* expected timeout configuration definitions */
#define TO_TOCNT(regval)              (BITS(1,16)&((uint32_t)(regval) << 1U))

/* MDIO flag definitions */
#define MDIO_FLAG_WRFRM               MDIO_STAT_WRFRM                /*!< a write data frame flag status */
#define MDIO_FLAG_ADDRFRM             MDIO_STAT_ADDRFRM              /*!< an address frame flag status */
#define MDIO_FLAG_RDINCFRM            MDIO_STAT_RDINCFRM             /*!< a post read increment address frame flag status */
#define MDIO_FLAG_RDFRM               MDIO_STAT_RDFRM                /*!< a read data frame flag status */
#define MDIO_FLAG_DEVM                MDIO_STAT_DEVM                 /*!< a DEVADD match frame flag status */
#define MDIO_FLAG_DEVNM               MDIO_STAT_DEVNM                /*!< a DEVADD nonmatch frame flag status */
#define MDIO_FLAG_PHYM                MDIO_STAT_PHYM                 /*!< a PHYADR match frame flag status */
#define MDIO_FLAG_PHYNM               MDIO_STAT_PHYNM                /*!< a PHYADR nonmatch frame flag status */
#define MDIO_FLAG_TANM                MDIO_STAT_TANM                 /*!< a TA nonmatch frame flag status */
#define MDIO_FLAG_TIMEOUT             MDIO_STAT_TO                   /*!< timeout flag */
#define MDIO_FLAG_TX_UNDERRUN         MDIO_STAT_UDR                  /*!< transmit underrun flag */
#define MDIO_FLAG_RX_OVERRUN          MDIO_STAT_OVR                  /*!< receive overrun flag */
#define MDIO_FLAG_RBNE                MDIO_STAT_RBNE                 /*!< read data buffer not empty flag */

/* MDIO interrupt definitions */
#define MDIO_INT_WRFRM                MDIO_INTEN_WRFRMIE             /*!< a write data frame interrupt */
#define MDIO_INT_ADDRFRM              MDIO_INTEN_ADDRFRMIE           /*!< an address frame interrupt */
#define MDIO_INT_RDINCFRM             MDIO_INTEN_RDINCFRMIE          /*!< a post read increment address frame interrupt */
#define MDIO_INT_RDFRM                MDIO_INTEN_RDFRMIE             /*!< a read data frame interrupt */
#define MDIO_INT_DEVM                 MDIO_INTEN_DEVMIE              /*!< a DEVADD match frame interrupt */
#define MDIO_INT_DEVNM                MDIO_INTEN_DEVNMIE             /*!< a DEVADD nonmatch frame interrupt */
#define MDIO_INT_PHYM                 MDIO_INTEN_PHYMIE              /*!< a PHYADR match frame interrupt */
#define MDIO_INT_PHYNM                MDIO_INTEN_PHYNMIE             /*!< a PHYADR nonmatch frame interrupt */
#define MDIO_INT_TANM                 MDIO_INTEN_TANMIE              /*!< a TA nonmatch frame interrupt */
#define MDIO_INT_TIMEOUT              MDIO_INTEN_TOIE                /*!< a timeout interrupt */
#define MDIO_INT_TX_UNDERRUN          MDIO_INTEN_UDRIE               /*!< a transmit underrun interrupt */
#define MDIO_INT_RX_OVERRUN           MDIO_INTEN_OVRIE               /*!< a receive overrun interrupt */
#define MDIO_INT_RBNE                 MDIO_INTEN_RBNEIE              /*!< a read data buffer not empty interrupt */

/* device type definitions */
#define DEVADD_PMA_PMD                ((uint16_t)0x0001U)            /*!< device type PMA/PMD */
#define DEVADD_WIS                    ((uint16_t)0x0002U)            /*!< device type WIS */
#define DEVADD_PCS                    ((uint16_t)0x0003U)            /*!< device type PCS */
#define DEVADD_PHY_XS                 ((uint16_t)0x0004U)            /*!< device type PHY XS */
#define DEVADD_DTE_XS                 ((uint16_t)0x0005U)            /*!< device type DTE XS */

/* function declarations */
/* reset functions */
/* reset MDIO */
void mdio_deinit(void);
/* reset MDIO block */
void mdio_software_reset(void);

/* fuction configuration */
/* initialize MDIO for communication */
uint32_t mdio_init(uint32_t phy_size, uint32_t phy_softaddr, uint32_t phy_sel, uint16_t devadd);
/* configure MDIO phy bit length */
void mdio_phy_length_config(uint32_t phy_bit);
/* set the software PHYADR value */
void mdio_soft_phyadr_set(uint32_t phy_soft);
/* select the expected frame field PHYADR */
void mdio_framefield_phyadr_config(uint32_t phy_sel);
/* configure the expected frame field DEVADD */
void mdio_framefield_devadd_config(uint16_t type);
/* read the hardware PRTADR[4:0] value */
uint32_t mdio_phy_pin_read(void);
/* configure the expected frame bit timeout */
void mdio_timeout_config(uint16_t timeout);
/* enable MDIO frame bit timeout */
void mdio_timeout_enable(void);
/* disable MDIO frame bit timeout */
void mdio_timeout_disable(void);

/* rx & tx functions */
/* read the received frame field OP */
uint16_t mdio_op_receive(void);
/* read the received frame field PHYADR */
uint16_t mdio_phyadr_receive(void);
/* read the received frame field DEVADD */
uint16_t mdio_devadd_receive(void);
/* read the received frame field TA */
uint16_t mdio_ta_receive(void);
/* read the received frame field DATA  */
uint16_t mdio_data_receive(void);
/* read the received frame field ADDRESS */
uint16_t mdio_address_receive(void);
/* transmit the frame field DATA */
void mdio_data_transmit(uint16_t data);

/* interrupt & flag functions */
/* get the flag status of the frame */
FlagStatus mdio_flag_get(uint32_t flag);
/* clear MDIO flag status */
void mdio_flag_clear(uint32_t flag);
/* enable MDIO interrupt */
void mdio_interrupt_enable(uint32_t interrupt);
/* disable MDIO interrupt */
void mdio_interrupt_disable(uint32_t interrupt);

#endif /* GD32H7XX_MDIO_H */
