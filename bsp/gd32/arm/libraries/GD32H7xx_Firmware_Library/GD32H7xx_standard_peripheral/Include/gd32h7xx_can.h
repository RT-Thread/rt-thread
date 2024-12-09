/*!
    \file    gd32h7xx_can.h
    \brief   definitions for the CAN

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

#ifndef GD32H7XX_CAN_H
#define GD32H7XX_CAN_H

#include "gd32h7xx.h"

/* CAN definitions */
#define CAN0                           CAN_BASE                                          /*!< CAN0 base address */
#define CAN1                           (CAN_BASE + 0x00001000U)                          /*!< CAN1 base address */
#define CAN2                           (CAN_BASE + 0x00002000U)                          /*!< CAN2 base address */
#define CAN_RAM(canx)                  ((uint32_t)((canx) + 0x00000080U))                /*!< can ram base address */
#define CAN_PN_RAM(canx)               ((uint32_t)((canx) + 0x00000B40U))                /*!< Pretended Networking ram base address */

/* registers definitions */
#define CAN_CTL0(canx)                 REG32((canx) + 0x00000000U)                       /*!< CAN control register 0 */
#define CAN_CTL1(canx)                 REG32((canx) + 0x00000004U)                       /*!< CAN control register 1 */
#define CAN_TIMER(canx)                REG32((canx) + 0x00000008U)                       /*!< CAN timer register */
#define CAN_RMPUBF(canx)               REG32((canx) + 0x00000010U)                       /*!< CAN receive mailbox public filter register */
#define CAN_ERR0(canx)                 REG32((canx) + 0x0000001CU)                       /*!< CAN error register 0 */
#define CAN_ERR1(canx)                 REG32((canx) + 0x00000020U)                       /*!< CAN error register 1 */
#define CAN_INTEN(canx)                REG32((canx) + 0x00000028U)                       /*!< CAN interrupt enable register */
#define CAN_STAT(canx)                 REG32((canx) + 0x00000030U)                       /*!< CAN status register */
#define CAN_CTL2(canx)                 REG32((canx) + 0x00000034U)                       /*!< CAN control register 2 */
#define CAN_CRCC(canx)                 REG32((canx) + 0x00000044U)                       /*!< CAN crc for classical frame register */
#define CAN_RFIFOPUBF(canx)            REG32((canx) + 0x00000048U)                       /*!< CAN receive fifo public filter register */
#define CAN_RFIFOIFMN(canx)            REG32((canx) + 0x0000004CU)                       /*!< CAN receive fifo identifier filter matching number register */
#define CAN_BT(canx)                   REG32((canx) + 0x00000050U)                       /*!< CAN bit timing register */
#define CAN_RFIFOMPF0(canx)            REG32((canx) + 0x00000880U)                       /*!< CAN receive fifo / mailbox private filter 0 register */
#define CAN_RFIFOMPF1(canx)            REG32((canx) + 0x00000884U)                       /*!< CAN receive fifo / mailbox private filter 1 register */
#define CAN_RFIFOMPF2(canx)            REG32((canx) + 0x00000888U)                       /*!< CAN receive fifo / mailbox private filter 2 register */
#define CAN_RFIFOMPF3(canx)            REG32((canx) + 0x0000088CU)                       /*!< CAN receive fifo / mailbox private filter 3 register */
#define CAN_RFIFOMPF4(canx)            REG32((canx) + 0x00000890U)                       /*!< CAN receive fifo / mailbox private filter 4 register */
#define CAN_RFIFOMPF5(canx)            REG32((canx) + 0x00000894U)                       /*!< CAN receive fifo / mailbox private filter 5 register */
#define CAN_RFIFOMPF6(canx)            REG32((canx) + 0x00000898U)                       /*!< CAN receive fifo / mailbox private filter 6 register */
#define CAN_RFIFOMPF7(canx)            REG32((canx) + 0x0000089CU)                       /*!< CAN receive fifo / mailbox private filter 7 register */
#define CAN_RFIFOMPF8(canx)            REG32((canx) + 0x000008A0U)                       /*!< CAN receive fifo / mailbox private filter 8 register */
#define CAN_RFIFOMPF9(canx)            REG32((canx) + 0x000008A4U)                       /*!< CAN receive fifo / mailbox private filter 9 register */
#define CAN_RFIFOMPF10(canx)           REG32((canx) + 0x000008A8U)                       /*!< CAN receive fifo / mailbox private filter 10 register */
#define CAN_RFIFOMPF11(canx)           REG32((canx) + 0x000008ACU)                       /*!< CAN receive fifo / mailbox private filter 11 register */
#define CAN_RFIFOMPF12(canx)           REG32((canx) + 0x000008B0U)                       /*!< CAN receive fifo / mailbox private filter 12 register */
#define CAN_RFIFOMPF13(canx)           REG32((canx) + 0x000008B4U)                       /*!< CAN receive fifo / mailbox private filter 13 register */
#define CAN_RFIFOMPF14(canx)           REG32((canx) + 0x000008B8U)                       /*!< CAN receive fifo / mailbox private filter 14 register */
#define CAN_RFIFOMPF15(canx)           REG32((canx) + 0x000008BCU)                       /*!< CAN receive fifo / mailbox private filter 15 register */
#define CAN_RFIFOMPF16(canx)           REG32((canx) + 0x000008C0U)                       /*!< CAN receive fifo / mailbox private filter 16 register */
#define CAN_RFIFOMPF17(canx)           REG32((canx) + 0x000008C4U)                       /*!< CAN receive fifo / mailbox private filter 17 register */
#define CAN_RFIFOMPF18(canx)           REG32((canx) + 0x000008C8U)                       /*!< CAN receive fifo / mailbox private filter 18 register */
#define CAN_RFIFOMPF19(canx)           REG32((canx) + 0x000008CCU)                       /*!< CAN receive fifo / mailbox private filter 19 register */
#define CAN_RFIFOMPF20(canx)           REG32((canx) + 0x000008D0U)                       /*!< CAN receive fifo / mailbox private filter 20 register */
#define CAN_RFIFOMPF21(canx)           REG32((canx) + 0x000008D4U)                       /*!< CAN receive fifo / mailbox private filter 21 register */
#define CAN_RFIFOMPF22(canx)           REG32((canx) + 0x000008D8U)                       /*!< CAN receive fifo / mailbox private filter 22 register */
#define CAN_RFIFOMPF23(canx)           REG32((canx) + 0x000008DCU)                       /*!< CAN receive fifo / mailbox private filter 23 register */
#define CAN_RFIFOMPF24(canx)           REG32((canx) + 0x000008E0U)                       /*!< CAN receive fifo / mailbox private filter 24 register */
#define CAN_RFIFOMPF25(canx)           REG32((canx) + 0x000008E4U)                       /*!< CAN receive fifo / mailbox private filter 25 register */
#define CAN_RFIFOMPF26(canx)           REG32((canx) + 0x000008E8U)                       /*!< CAN receive fifo / mailbox private filter 26 register */
#define CAN_RFIFOMPF27(canx)           REG32((canx) + 0x000008ECU)                       /*!< CAN receive fifo / mailbox private filter 27 register */
#define CAN_RFIFOMPF28(canx)           REG32((canx) + 0x000008F0U)                       /*!< CAN receive fifo / mailbox private filter 28 register */
#define CAN_RFIFOMPF29(canx)           REG32((canx) + 0x000008F4U)                       /*!< CAN receive fifo / mailbox private filter 29 register */
#define CAN_RFIFOMPF30(canx)           REG32((canx) + 0x000008F8U)                       /*!< CAN receive fifo / mailbox private filter 30 register */
#define CAN_RFIFOMPF31(canx)           REG32((canx) + 0x000008FCU)                       /*!< CAN receive fifo / mailbox private filter 31 register */
#define CAN_PN_CTL0(canx)              REG32((canx) + 0x00000B00U)                       /*!< Pretended Networking mode control register 0 */
#define CAN_PN_TO(canx)                REG32((canx) + 0x00000B04U)                       /*!< Pretended Networking mode timeout register */
#define CAN_PN_STAT(canx)              REG32((canx) + 0x00000B08U)                       /*!< Pretended Networking mode status register */
#define CAN_PN_EID0(canx)              REG32((canx) + 0x00000B0CU)                       /*!< Pretended Networking mode expected identifier 0 register */
#define CAN_PN_EDLC(canx)              REG32((canx) + 0x00000B10U)                       /*!< Pretended Networking mode expected dlc register */
#define CAN_PN_EDL0(canx)              REG32((canx) + 0x00000B14U)                       /*!< Pretended Networking mode expected data low 0 register */
#define CAN_PN_EDL1(canx)              REG32((canx) + 0x00000B18U)                       /*!< Pretended Networking mode expected data low 1 register */
#define CAN_PN_IFEID1(canx)            REG32((canx) + 0x00000B1CU)                       /*!< Pretended Networking mode identifier filter / expected identifier 1 register */
#define CAN_PN_DF0EDH0(canx)           REG32((canx) + 0x00000B20U)                       /*!< Pretended Networking mode data 0 filter / expected data high 0 register */
#define CAN_PN_DF1EDH1(canx)           REG32((canx) + 0x00000B24U)                       /*!< Pretended Networking mode data 1 filter / expected data high 1 register */
#define CAN_PN_RWM0CS(canx)            REG32((canx) + 0x00000B40U)                       /*!< Pretended Networking mode received wakeup mailbox 0 control status information register */
#define CAN_PN_RWM0I(canx)             REG32((canx) + 0x00000B44U)                       /*!< Pretended Networking mode received wakeup mailbox 0 identifier register */
#define CAN_PN_RWM0D0(canx)            REG32((canx) + 0x00000B48U)                       /*!< Pretended Networking mode received wakeup mailbox 0 data 0 register */
#define CAN_PN_RWM0D1(canx)            REG32((canx) + 0x00000B4CU)                       /*!< Pretended Networking mode received wakeup mailbox 0 data 1 register */
#define CAN_PN_RWM1CS(canx)            REG32((canx) + 0x00000B50U)                       /*!< Pretended Networking mode received wakeup mailbox 1 control status information register */
#define CAN_PN_RWM1I(canx)             REG32((canx) + 0x00000B54U)                       /*!< Pretended Networking mode received wakeup mailbox 1 identifier register */
#define CAN_PN_RWM1D0(canx)            REG32((canx) + 0x00000B58U)                       /*!< Pretended Networking mode received wakeup mailbox 1 data 0 register */
#define CAN_PN_RWM1D1(canx)            REG32((canx) + 0x00000B5CU)                       /*!< Pretended Networking mode received wakeup mailbox 1 data 1 register */
#define CAN_PN_RWM2CS(canx)            REG32((canx) + 0x00000B60U)                       /*!< Pretended Networking mode received wakeup mailbox 2 control status information register */
#define CAN_PN_RWM2I(canx)             REG32((canx) + 0x00000B64U)                       /*!< Pretended Networking mode received wakeup mailbox 2 identifier register */
#define CAN_PN_RWM2D0(canx)            REG32((canx) + 0x00000B68U)                       /*!< Pretended Networking mode received wakeup mailbox 2 data 0 register */
#define CAN_PN_RWM2D1(canx)            REG32((canx) + 0x00000B6CU)                       /*!< Pretended Networking mode received wakeup mailbox 2 data 1 register */
#define CAN_PN_RWM3CS(canx)            REG32((canx) + 0x00000B70U)                       /*!< Pretended Networking mode received wakeup mailbox 3 control status information register */
#define CAN_PN_RWM3I(canx)             REG32((canx) + 0x00000B74U)                       /*!< Pretended Networking mode received wakeup mailbox 3 identifier register */
#define CAN_PN_RWM3D0(canx)            REG32((canx) + 0x00000B78U)                       /*!< Pretended Networking mode received wakeup mailbox 3 data 0 register */
#define CAN_PN_RWM3D1(canx)            REG32((canx) + 0x00000B7CU)                       /*!< Pretended Networking mode received wakeup mailbox 3 data 1 register */
#define CAN_FDCTL(canx)                REG32((canx) + 0x00000C00U)                       /*!< CAN FD control register */
#define CAN_FDBT(canx)                 REG32((canx) + 0x00000C04U)                       /*!< CAN bit timing register */
#define CAN_CRCCFD(canx)               REG32((canx) + 0x00000C08U)                       /*!< CAN CRC for classical and FD frame register */

/* bits definitions */
/* CAN_CTL0 */
#define CAN_CTL0_MSZ                   BITS(0, 4)                                        /*!< memory size */
#define CAN_CTL0_FS                    BITS(8, 9)                                        /*!< format selection */
#define CAN_CTL0_FDEN                  BIT(11)                                           /*!< CAN FD operation enable */
#define CAN_CTL0_MST                   BIT(12)                                           /*!< mailbox stop transmission */
#define CAN_CTL0_LAPRIOEN              BIT(13)                                           /*!< enable local arbitration priority */
#define CAN_CTL0_PNMOD                 BIT(14)                                           /*!< Pretended Networking mode selection */
#define CAN_CTL0_DMAEN                 BIT(15)                                           /*!< enable DMA */
#define CAN_CTL0_RPFQEN                BIT(16)                                           /*!< enable rx private filters enable & rx mailbox queue */
#define CAN_CTL0_SRDIS                 BIT(17)                                           /*!< enable self reception */
#define CAN_CTL0_PNS                   BIT(18)                                           /*!< Pretended Networking state */
#define CAN_CTL0_PNEN                  BIT(19)                                           /*!< enable Pretended Networking mode */
#define CAN_CTL0_LPS                   BIT(20)                                           /*!< low power state */
#define CAN_CTL0_WERREN                BIT(21)                                           /*!< enable error warning */
#define CAN_CTL0_INAS                  BIT(24)                                           /*!< inactive mode state */
#define CAN_CTL0_SWRST                 BIT(25)                                           /*!< software reset */
#define CAN_CTL0_NRDY                  BIT(27)                                           /*!< not ready */
#define CAN_CTL0_HALT                  BIT(28)                                           /*!< halt CAN */
#define CAN_CTL0_RFEN                  BIT(29)                                           /*!< rx fifo enable */
#define CAN_CTL0_INAMOD                BIT(30)                                           /*!< enable inactive mode */
#define CAN_CTL0_CANDIS                BIT(31)                                           /*!< disable CAN */

/* CAN_CTL1 */
#define CAN_CTL1_MMOD                  BIT(3)                                            /*!< monitor mode */
#define CAN_CTL1_MTO                   BIT(4)                                            /*!< mailbox transmission order */
#define CAN_CTL1_TSYNC                 BIT(5)                                            /*!< enable time synchronization */
#define CAN_CTL1_ABORDIS               BIT(6)                                            /*!< not enable automatic bus off recovery */
#define CAN_CTL1_BSPMOD                BIT(7)                                            /*!< bit sampling mode */
#define CAN_CTL1_RWERRIE               BIT(10)                                           /*!< enable rx error warning interrupt */
#define CAN_CTL1_TWERRIE               BIT(11)                                           /*!< enable tx error warning interrupt */
#define CAN_CTL1_LSCMOD                BIT(12)                                           /*!< loopback and silent communication mode */
#define CAN_CTL1_ERRSIE                BIT(14)                                           /*!< enable error summary interrupt */
#define CAN_CTL1_BOIE                  BIT(15)                                           /*!< enable bus off interrupt */

/* CAN_TIMER */
#define CAN_TIMER_CNT                  BITS(0,15)                                        /*!< counter value */

/* CAN_RMPUBF */
#define CAN_RMPUBF_MFD0                BIT(0)                                            /*!< mailbox filter data bit 0 */
#define CAN_RMPUBF_MFD1                BIT(1)                                            /*!< mailbox filter data bit 1 */
#define CAN_RMPUBF_MFD2                BIT(2)                                            /*!< mailbox filter data bit 2 */
#define CAN_RMPUBF_MFD3                BIT(3)                                            /*!< mailbox filter data bit 3 */
#define CAN_RMPUBF_MFD4                BIT(4)                                            /*!< mailbox filter data bit 4 */
#define CAN_RMPUBF_MFD5                BIT(5)                                            /*!< mailbox filter data bit 5 */
#define CAN_RMPUBF_MFD6                BIT(6)                                            /*!< mailbox filter data bit 6 */
#define CAN_RMPUBF_MFD7                BIT(7)                                            /*!< mailbox filter data bit 7 */
#define CAN_RMPUBF_MFD8                BIT(8)                                            /*!< mailbox filter data bit 8 */
#define CAN_RMPUBF_MFD9                BIT(9)                                            /*!< mailbox filter data bit 9 */
#define CAN_RMPUBF_MFD10               BIT(10)                                           /*!< mailbox filter data bit 10 */
#define CAN_RMPUBF_MFD11               BIT(11)                                           /*!< mailbox filter data bit 11 */
#define CAN_RMPUBF_MFD12               BIT(12)                                           /*!< mailbox filter data bit 12 */
#define CAN_RMPUBF_MFD13               BIT(13)                                           /*!< mailbox filter data bit 13 */
#define CAN_RMPUBF_MFD14               BIT(14)                                           /*!< mailbox filter data bit 14 */
#define CAN_RMPUBF_MFD15               BIT(15)                                           /*!< mailbox filter data bit 15 */
#define CAN_RMPUBF_MFD16               BIT(16)                                           /*!< mailbox filter data bit 16 */
#define CAN_RMPUBF_MFD17               BIT(17)                                           /*!< mailbox filter data bit 17 */
#define CAN_RMPUBF_MFD18               BIT(18)                                           /*!< mailbox filter data bit 18 */
#define CAN_RMPUBF_MFD19               BIT(19)                                           /*!< mailbox filter data bit 19 */
#define CAN_RMPUBF_MFD20               BIT(20)                                           /*!< mailbox filter data bit 20 */
#define CAN_RMPUBF_MFD21               BIT(21)                                           /*!< mailbox filter data bit 21 */
#define CAN_RMPUBF_MFD22               BIT(22)                                           /*!< mailbox filter data bit 22 */
#define CAN_RMPUBF_MFD23               BIT(23)                                           /*!< mailbox filter data bit 23 */
#define CAN_RMPUBF_MFD24               BIT(24)                                           /*!< mailbox filter data bit 24 */
#define CAN_RMPUBF_MFD25               BIT(25)                                           /*!< mailbox filter data bit 25 */
#define CAN_RMPUBF_MFD26               BIT(26)                                           /*!< mailbox filter data bit 26 */
#define CAN_RMPUBF_MFD27               BIT(27)                                           /*!< mailbox filter data bit 27 */
#define CAN_RMPUBF_MFD28               BIT(28)                                           /*!< mailbox filter data bit 28 */
#define CAN_RMPUBF_MFD29               BIT(29)                                           /*!< mailbox filter data bit 29 */
#define CAN_RMPUBF_MFD30               BIT(30)                                           /*!< mailbox filter data bit 30 */
#define CAN_RMPUBF_MFD31               BIT(31)                                           /*!< mailbox filter data bit 31 */

/* CAN_ERR0 */
#define CAN_ERR0_TECNT                 BITS(0, 7)                                        /*!< transmit error count defined by the CAN standard */
#define CAN_ERR0_RECNT                 BITS(8, 15)                                       /*!< receive error count defined by the CAN standard */
#define CAN_ERR0_TEFCNT                BITS(16, 23)                                      /*!< transmit error count for the data phase of FD frames with BRS bit set */
#define CAN_ERR0_REFCNT                BITS(24, 31)                                      /*!< receive error count for the data phase of FD frames with BRS bit set */

/* CAN_ERR1 */
#define CAN_ERR1_ERRSF                 BIT(1)                                            /*!< error summary flag */
#define CAN_ERR1_BOF                   BIT(2)                                            /*!< bus off flag */
#define CAN_ERR1_RS                    BIT(3)                                            /*!< receiving state */
#define CAN_ERR1_ERRSI                 BITS(4, 5)                                        /*!< error state indicator */
#define CAN_ERR1_TS                    BIT(6)                                            /*!< transmitting state */
#define CAN_ERR1_IDLEF                 BIT(7)                                            /*!< idle flag */
#define CAN_ERR1_RWERRF                BIT(8)                                            /*!< rx error warning flag */
#define CAN_ERR1_TWERRF                BIT(9)                                            /*!< tx error warning flag */
#define CAN_ERR1_STFERR                BIT(10)                                           /*!< stuff error */
#define CAN_ERR1_FMERR                 BIT(11)                                           /*!< form error */
#define CAN_ERR1_CRCERR                BIT(12)                                           /*!< CRC error */
#define CAN_ERR1_ACKERR                BIT(13)                                           /*!< ACK error */
#define CAN_ERR1_BDERR                 BIT(14)                                           /*!< bit dominant error for all format frames */
#define CAN_ERR1_BRERR                 BIT(15)                                           /*!< bit recessive error for all format frames */
#define CAN_ERR1_RWERRIF               BIT(16)                                           /*!< rx error warning interrupt flag */
#define CAN_ERR1_TWERRIF               BIT(17)                                           /*!< tx error warning interrupt flag */
#define CAN_ERR1_SYN                   BIT(18)                                           /*!< synchronization flag */
#define CAN_ERR1_BORF                  BIT(19)                                           /*!< bus off recovery flag */
#define CAN_ERR1_ERRFSF                BIT(20)                                           /*!< error summary flag for data phase of FD frames with BRS bit set */
#define CAN_ERR1_ERROVR                BIT(21)                                           /*!< error overrun */
#define CAN_ERR1_STFFERR               BIT(26)                                           /*!< stuff error in data phase of FD frames with BRS bit set */
#define CAN_ERR1_FMFERR                BIT(27)                                           /*!< form error in data phase of FD frames with BRS bit set */
#define CAN_ERR1_CRCFERR               BIT(28)                                           /*!< CRC error in data phase of FD frames with BRS bit set */
#define CAN_ERR1_BDFERR                BIT(30)                                           /*!< bit dominant error in data phase of FD frames with BRS bit set */
#define CAN_ERR1_BRFERR                BIT(31)                                           /*!< bit recessive error in data phase of FD frames with BRS bit set */

/* CAN_INTEN */
#define CAN_INTEN_MIE0                 BIT(0)                                            /*!< enable message 0 transmission and reception interrupt */
#define CAN_INTEN_MIE1                 BIT(1)                                            /*!< enable message 1 transmission and reception interrupt */
#define CAN_INTEN_MIE2                 BIT(2)                                            /*!< enable message 2 transmission and reception interrupt */
#define CAN_INTEN_MIE3                 BIT(3)                                            /*!< enable message 3 transmission and reception interrupt */
#define CAN_INTEN_MIE4                 BIT(4)                                            /*!< enable message 4 transmission and reception interrupt */
#define CAN_INTEN_MIE5                 BIT(5)                                            /*!< enable message 5 transmission and reception interrupt */
#define CAN_INTEN_MIE6                 BIT(6)                                            /*!< enable message 6 transmission and reception interrupt */
#define CAN_INTEN_MIE7                 BIT(7)                                            /*!< enable message 7 transmission and reception interrupt */
#define CAN_INTEN_MIE8                 BIT(8)                                            /*!< enable message 8 transmission and reception interrupt */
#define CAN_INTEN_MIE9                 BIT(9)                                            /*!< enable message 9 transmission and reception interrupt */
#define CAN_INTEN_MIE10                BIT(10)                                           /*!< enable message 10 transmission and reception interrupt */
#define CAN_INTEN_MIE11                BIT(11)                                           /*!< enable message 11 transmission and reception interrupt */
#define CAN_INTEN_MIE12                BIT(12)                                           /*!< enable message 12 transmission and reception interrupt */
#define CAN_INTEN_MIE13                BIT(13)                                           /*!< enable message 13 transmission and reception interrupt */
#define CAN_INTEN_MIE14                BIT(14)                                           /*!< enable message 14 transmission and reception interrupt */
#define CAN_INTEN_MIE15                BIT(15)                                           /*!< enable message 15 transmission and reception interrupt */
#define CAN_INTEN_MIE16                BIT(16)                                           /*!< enable message 16 transmission and reception interrupt */
#define CAN_INTEN_MIE17                BIT(17)                                           /*!< enable message 17 transmission and reception interrupt */
#define CAN_INTEN_MIE18                BIT(18)                                           /*!< enable message 18 transmission and reception interrupt */
#define CAN_INTEN_MIE19                BIT(19)                                           /*!< enable message 19 transmission and reception interrupt */
#define CAN_INTEN_MIE20                BIT(20)                                           /*!< enable message 20 transmission and reception interrupt */
#define CAN_INTEN_MIE21                BIT(21)                                           /*!< enable message 21 transmission and reception interrupt */
#define CAN_INTEN_MIE22                BIT(22)                                           /*!< enable message 22 transmission and reception interrupt */
#define CAN_INTEN_MIE23                BIT(23)                                           /*!< enable message 23 transmission and reception interrupt */
#define CAN_INTEN_MIE24                BIT(24)                                           /*!< enable message 24 transmission and reception interrupt */
#define CAN_INTEN_MIE25                BIT(25)                                           /*!< enable message 25 transmission and reception interrupt */
#define CAN_INTEN_MIE26                BIT(26)                                           /*!< enable message 26 transmission and reception interrupt */
#define CAN_INTEN_MIE27                BIT(27)                                           /*!< enable message 27 transmission and reception interrupt */
#define CAN_INTEN_MIE28                BIT(28)                                           /*!< enable message 28 transmission and reception interrupt */
#define CAN_INTEN_MIE29                BIT(29)                                           /*!< enable message 29 transmission and reception interrupt */
#define CAN_INTEN_MIE30                BIT(30)                                           /*!< enable message 30 transmission and reception interrupt */
#define CAN_INTEN_MIE31                BIT(31)                                           /*!< enable message 31 transmission and reception interrupt */

/* CAN_STAT */
#define CAN_STAT_MS0_RFC               BIT(0)                                            /*!< mailbox 0 state / clear rx fifo bit */
#define CAN_STAT_MS1_RES               BIT(1)                                            /*!< mailbox 1 state */
#define CAN_STAT_MS2_RES               BIT(2)                                            /*!< mailbox 2 state */
#define CAN_STAT_MS3_RES               BIT(3)                                            /*!< mailbox 3 state */
#define CAN_STAT_MS4_RES               BIT(4)                                            /*!< mailbox 4 state */
#define CAN_STAT_MS5_RFNE              BIT(5)                                            /*!< mailbox 5 state / rx fifo not empty */
#define CAN_STAT_MS6_RFW               BIT(6)                                            /*!< mailbox 6 state / rx fifo warning */
#define CAN_STAT_MS7_RFO               BIT(7)                                            /*!< mailbox 7 state / rx fifo overflow */
#define CAN_STAT_MS8                   BIT(8)                                            /*!< mailbox 8 state */
#define CAN_STAT_MS9                   BIT(9)                                            /*!< mailbox 9 state */
#define CAN_STAT_MS10                  BIT(10)                                           /*!< mailbox 10 state */
#define CAN_STAT_MS11                  BIT(11)                                           /*!< mailbox 11 state */
#define CAN_STAT_MS12                  BIT(12)                                           /*!< mailbox 12 state */
#define CAN_STAT_MS13                  BIT(13)                                           /*!< mailbox 13 state */
#define CAN_STAT_MS14                  BIT(14)                                           /*!< mailbox 14 state */
#define CAN_STAT_MS15                  BIT(15)                                           /*!< mailbox 15 state */
#define CAN_STAT_MS16                  BIT(16)                                           /*!< mailbox 16 state */
#define CAN_STAT_MS17                  BIT(17)                                           /*!< mailbox 17 state */
#define CAN_STAT_MS18                  BIT(18)                                           /*!< mailbox 18 state */
#define CAN_STAT_MS19                  BIT(19)                                           /*!< mailbox 19 state */
#define CAN_STAT_MS20                  BIT(20)                                           /*!< mailbox 20 state */
#define CAN_STAT_MS21                  BIT(21)                                           /*!< mailbox 21 state */
#define CAN_STAT_MS22                  BIT(22)                                           /*!< mailbox 22 state */
#define CAN_STAT_MS23                  BIT(23)                                           /*!< mailbox 23 state */
#define CAN_STAT_MS24                  BIT(24)                                           /*!< mailbox 24 state */
#define CAN_STAT_MS25                  BIT(25)                                           /*!< mailbox 25 state */
#define CAN_STAT_MS26                  BIT(26)                                           /*!< mailbox 26 state */
#define CAN_STAT_MS27                  BIT(27)                                           /*!< mailbox 27 state */
#define CAN_STAT_MS28                  BIT(28)                                           /*!< mailbox 28 state */
#define CAN_STAT_MS29                  BIT(29)                                           /*!< mailbox 29 state */
#define CAN_STAT_MS30                  BIT(30)                                           /*!< mailbox 30 state */
#define CAN_STAT_MS31                  BIT(31)                                           /*!< mailbox 31 state */

/* CAN_CTL2 */
#define CAN_CTL2_EFDIS                 BIT(11)                                           /*!< disable edge filtering */
#define CAN_CTL2_ISO                   BIT(12)                                           /*!< ISO CAN FD */
#define CAN_CTL2_PREEN                 BIT(14)                                           /*!< protocol exception detection enable by CAN standard */
#define CAN_CTL2_ITSRC                 BIT(15)                                           /*!< internal counter source */
#define CAN_CTL2_IDERTR_RMF            BIT(16)                                           /*!< IDE and RTR field filter type for rx mailbox reception */
#define CAN_CTL2_RRFRMS                BIT(17)                                           /*!< remote request frame is stored */
#define CAN_CTL2_RFO                   BIT(18)                                           /*!< receive filter order */
#define CAN_CTL2_ASD                   BITS(19, 23)                                      /*!< arbitration start delay */
#define CAN_CTL2_RFFN                  BITS(24, 27)                                      /*!< rx fifo filter number */
#define CAN_CTL2_BORIE                 BIT(30)                                           /*!< enable bus off recovery interrupt */
#define CAN_CTL2_ERRFSIE               BIT(31)                                           /*!< error summary interrupt enable bit for data phase of FD frames with BRS bit set */

/* CAN_CRCC */
#define CAN_CRCC_CRCTC                 BITS(0, 14)                                       /*!< transmitted CRC value for classical frames */
#define CAN_CRCC_ANTM                  BITS(16, 20)                                      /*!< associated number of mailbox for transmitting the CRCTC[14:0] value */

/* CAN_RFIFOPUBF */
#define CAN_RFIFOPUBF_FFD0             BIT(0)                                            /*!< rx fifo filter data bit 0 */
#define CAN_RFIFOPUBF_FFD1             BIT(1)                                            /*!< rx fifo filter data bit 1 */
#define CAN_RFIFOPUBF_FFD2             BIT(2)                                            /*!< rx fifo filter data bit 2 */
#define CAN_RFIFOPUBF_FFD3             BIT(3)                                            /*!< rx fifo filter data bit 3 */
#define CAN_RFIFOPUBF_FFD4             BIT(4)                                            /*!< rx fifo filter data bit 4 */
#define CAN_RFIFOPUBF_FFD5             BIT(5)                                            /*!< rx fifo filter data bit 5 */
#define CAN_RFIFOPUBF_FFD6             BIT(6)                                            /*!< rx fifo filter data bit 6 */
#define CAN_RFIFOPUBF_FFD7             BIT(7)                                            /*!< rx fifo filter data bit 7 */
#define CAN_RFIFOPUBF_FFD8             BIT(8)                                            /*!< rx fifo filter data bit 8 */
#define CAN_RFIFOPUBF_FFD9             BIT(9)                                            /*!< rx fifo filter data bit 9 */
#define CAN_RFIFOPUBF_FFD10            BIT(10)                                           /*!< rx fifo filter data bit 10 */
#define CAN_RFIFOPUBF_FFD11            BIT(11)                                           /*!< rx fifo filter data bit 11 */
#define CAN_RFIFOPUBF_FFD12            BIT(12)                                           /*!< rx fifo filter data bit 12 */
#define CAN_RFIFOPUBF_FFD13            BIT(13)                                           /*!< rx fifo filter data bit 13 */
#define CAN_RFIFOPUBF_FFD14            BIT(14)                                           /*!< rx fifo filter data bit 14 */
#define CAN_RFIFOPUBF_FFD15            BIT(15)                                           /*!< rx fifo filter data bit 15 */
#define CAN_RFIFOPUBF_FFD16            BIT(16)                                           /*!< rx fifo filter data bit 16 */
#define CAN_RFIFOPUBF_FFD17            BIT(17)                                           /*!< rx fifo filter data bit 17 */
#define CAN_RFIFOPUBF_FFD18            BIT(18)                                           /*!< rx fifo filter data bit 18 */
#define CAN_RFIFOPUBF_FFD19            BIT(19)                                           /*!< rx fifo filter data bit 19 */
#define CAN_RFIFOPUBF_FFD20            BIT(20)                                           /*!< rx fifo filter data bit 20 */
#define CAN_RFIFOPUBF_FFD21            BIT(21)                                           /*!< rx fifo filter data bit 21 */
#define CAN_RFIFOPUBF_FFD22            BIT(22)                                           /*!< rx fifo filter data bit 22 */
#define CAN_RFIFOPUBF_FFD23            BIT(23)                                           /*!< rx fifo filter data bit 23 */
#define CAN_RFIFOPUBF_FFD24            BIT(24)                                           /*!< rx fifo filter data bit 24 */
#define CAN_RFIFOPUBF_FFD25            BIT(25)                                           /*!< rx fifo filter data bit 25 */
#define CAN_RFIFOPUBF_FFD26            BIT(26)                                           /*!< rx fifo filter data bit 26 */
#define CAN_RFIFOPUBF_FFD27            BIT(27)                                           /*!< rx fifo filter data bit 27 */
#define CAN_RFIFOPUBF_FFD28            BIT(28)                                           /*!< rx fifo filter data bit 28 */
#define CAN_RFIFOPUBF_FFD29            BIT(29)                                           /*!< rx fifo filter data bit 29 */
#define CAN_RFIFOPUBF_FFD30            BIT(30)                                           /*!< rx fifo filter data bit 30 */
#define CAN_RFIFOPUBF_FFD31            BIT(31)                                           /*!< rx fifo filter data bit 31 */

/* CAN_RFIFOIFMN */
#define CAN_RFIFOIFMN_IDFMN            BITS(0, 8)                                        /*!< identifier filter matching number */

/* CAN_BT */
#define CAN_BT_PBS2                    BITS(0, 4)                                        /*!< phase buffer segment 2 */
#define CAN_BT_PBS1                    BITS(5, 9)                                        /*!< phase buffer segment 1 */
#define CAN_BT_PTS                     BITS(10, 15)                                      /*!< propagation time segment */
#define CAN_BT_SJW                     BITS(16, 20)                                      /*!< resynchronization jump width */
#define CAN_BT_BAUDPSC                 BITS(21, 30)                                      /*!< baud rate prescaler */

/* CAN_RFIFOMPFx, x = 0..31 */
#define CAN_RFIFOMPF_FMFD0             BIT(0)                                            /*!< fifo / mailbox filter data bit 0 */
#define CAN_RFIFOMPF_FMFD1             BIT(1)                                            /*!< fifo / mailbox filter data bit 1 */
#define CAN_RFIFOMPF_FMFD2             BIT(2)                                            /*!< fifo / mailbox filter data bit 2 */
#define CAN_RFIFOMPF_FMFD3             BIT(3)                                            /*!< fifo / mailbox filter data bit 3 */
#define CAN_RFIFOMPF_FMFD4             BIT(4)                                            /*!< fifo / mailbox filter data bit 4 */
#define CAN_RFIFOMPF_FMFD5             BIT(5)                                            /*!< fifo / mailbox filter data bit 5 */
#define CAN_RFIFOMPF_FMFD6             BIT(6)                                            /*!< fifo / mailbox filter data bit 6 */
#define CAN_RFIFOMPF_FMFD7             BIT(7)                                            /*!< fifo / mailbox filter data bit 7 */
#define CAN_RFIFOMPF_FMFD8             BIT(8)                                            /*!< fifo / mailbox filter data bit 8 */
#define CAN_RFIFOMPF_FMFD9             BIT(9)                                            /*!< fifo / mailbox filter data bit 9 */
#define CAN_RFIFOMPF_FMFD10            BIT(10)                                           /*!< fifo / mailbox filter data bit 10 */
#define CAN_RFIFOMPF_FMFD11            BIT(11)                                           /*!< fifo / mailbox filter data bit 11 */
#define CAN_RFIFOMPF_FMFD12            BIT(12)                                           /*!< fifo / mailbox filter data bit 12 */
#define CAN_RFIFOMPF_FMFD13            BIT(13)                                           /*!< fifo / mailbox filter data bit 13 */
#define CAN_RFIFOMPF_FMFD14            BIT(14)                                           /*!< fifo / mailbox filter data bit 14 */
#define CAN_RFIFOMPF_FMFD15            BIT(15)                                           /*!< fifo / mailbox filter data bit 15 */
#define CAN_RFIFOMPF_FMFD16            BIT(16)                                           /*!< fifo / mailbox filter data bit 16 */
#define CAN_RFIFOMPF_FMFD17            BIT(17)                                           /*!< fifo / mailbox filter data bit 17 */
#define CAN_RFIFOMPF_FMFD18            BIT(18)                                           /*!< fifo / mailbox filter data bit 18 */
#define CAN_RFIFOMPF_FMFD19            BIT(19)                                           /*!< fifo / mailbox filter data bit 19 */
#define CAN_RFIFOMPF_FMFD20            BIT(20)                                           /*!< fifo / mailbox filter data bit 20 */
#define CAN_RFIFOMPF_FMFD21            BIT(21)                                           /*!< fifo / mailbox filter data bit 21 */
#define CAN_RFIFOMPF_FMFD22            BIT(22)                                           /*!< fifo / mailbox filter data bit 22 */
#define CAN_RFIFOMPF_FMFD23            BIT(23)                                           /*!< fifo / mailbox filter data bit 23 */
#define CAN_RFIFOMPF_FMFD24            BIT(24)                                           /*!< fifo / mailbox filter data bit 24 */
#define CAN_RFIFOMPF_FMFD25            BIT(25)                                           /*!< fifo / mailbox filter data bit 25 */
#define CAN_RFIFOMPF_FMFD26            BIT(26)                                           /*!< fifo / mailbox filter data bit 26 */
#define CAN_RFIFOMPF_FMFD27            BIT(27)                                           /*!< fifo / mailbox filter data bit 27 */
#define CAN_RFIFOMPF_FMFD28            BIT(28)                                           /*!< fifo / mailbox filter data bit 28 */
#define CAN_RFIFOMPF_FMFD29            BIT(29)                                           /*!< fifo / mailbox filter data bit 29 */
#define CAN_RFIFOMPF_FMFD30            BIT(30)                                           /*!< fifo / mailbox filter data bit 30 */
#define CAN_RFIFOMPF_FMFD31            BIT(31)                                           /*!< fifo / mailbox filter data bit 31 */

/* CAN_PN_CTL0 */
#define CAN_PN_CTL0_FFT                BITS(0, 1)                                        /*!< frame filtering type in Pretended Networking mode */
#define CAN_PN_CTL0_IDFT               BITS(2, 3)                                        /*!< ID field filtering type in Pretended Networking mode */
#define CAN_PN_CTL0_DATAFT             BITS(4, 5)                                        /*!< data field filtering type in Pretended Networking mode */
#define CAN_PN_CTL0_NMM                BITS(8, 15)                                       /*!< number of messages matching times */
#define CAN_PN_CTL0_WMIE               BIT(16)                                           /*!< enable wakeup match interrupt */
#define CAN_PN_CTL0_WTOIE              BIT(17)                                           /*!< enable wakeup timeout interrupt */

/* CAN_PN_TO */
#define CAN_PN_TO_WTO                  BITS(0, 15)                                       /*!< wakeup timeout */

/* CAN_PN_STAT */
#define CAN_PN_STAT_MMCNTS             BIT(7)                                            /*!< matching message counter state */
#define CAN_PN_STAT_MMCNT              BITS(8, 15)                                       /*!< matching message counter in Pretended Networking mode */
#define CAN_PN_STAT_WMS                BIT(16)                                           /*!< wakeup match flag status */
#define CAN_PN_STAT_WTOS               BIT(17)                                           /*!< wakeup timeout flag status */

/* CAN_PN_EID0 */
#define CAN_PN_EID0_EID_ELT            BITS(0, 28)                                       /*!< expected ID field / expected ID low threshold in Pretended Networking mode */
#define CAN_PN_EID0_ERTR               BIT(29)                                           /*!< expected RTR in Pretended Networking mode */
#define CAN_PN_EID0_EIDE               BIT(30)                                           /*!< expected IDE in Pretended Networking mode */

/* CAN_PN_EDLC */
#define CAN_PN_EDLC_DLCEHT             BITS(0, 3)                                        /*!< DLC expected high threshold in Pretended Networking mode */
#define CAN_PN_EDLC_DLCELT             BITS(16, 19)                                      /*!< DLC expected low threshold in Pretended Networking mode */

/* CAN_PN_EDL0 */
#define CAN_PN_EDL0_DB3ELT             BITS(0, 7)                                        /*!< data byte 3 expected low threshold in Pretended Networking mode */
#define CAN_PN_EDL0_DB2ELT             BITS(8, 15)                                       /*!< data byte 2 expected low threshold in Pretended Networking mode */
#define CAN_PN_EDL0_DB1ELT             BITS(16, 23)                                      /*!< data byte 1 expected low threshold in Pretended Networking mode */
#define CAN_PN_EDL0_DB0ELT             BITS(24, 31)                                      /*!< data byte 0 expected low threshold in Pretended Networking mode */

/* CAN_PN_EDL1 */
#define CAN_PN_EDL1_DB7ELT             BITS(0, 7)                                        /*!< data byte 7 expected low threshold in Pretended Networking mode */
#define CAN_PN_EDL1_DB6ELT             BITS(8, 15)                                       /*!< data byte 6 expected low threshold in Pretended Networking mode */
#define CAN_PN_EDL1_DB5ELT             BITS(16, 23)                                      /*!< data byte 5 expected low threshold in Pretended Networking mode */
#define CAN_PN_EDL1_DB4ELT             BITS(24, 31)                                      /*!< data byte 4 expected low threshold in Pretended Networking mode */

/* CAN_PN_IFEID1 */
#define CAN_PN_IFEID1_IDFD_EHT         BITS(0, 28)                                       /*!< IDE filter data in Pretended Networking mode */
#define CAN_PN_IFEID1_RTRFD            BIT(29)                                           /*!< RTR filter data in Pretended Networking mode */
#define CAN_PN_IFEID1_IDEFD            BIT(30)                                           /*!< ID filter data / ID expected high threshold in Pretended Networking mode */

/* CAN_PN_DF0EDH0 */
#define CAN_PN_DF0EDH0_DB3FD_EHT       BITS(0, 7)                                        /*!< data byte 3 filter data / data byte 3 expected high threshold in Pretended Networking mode */
#define CAN_PN_DF0EDH0_DB2FD_EHT       BITS(8, 15)                                       /*!< data byte 2 filter data / data byte 2 expected high threshold in Pretended Networking mode */
#define CAN_PN_DF0EDH0_DB1FD_EHT       BITS(16, 23)                                      /*!< data byte 1 filter data / data byte 1 expected high threshold in Pretended Networking mode */
#define CAN_PN_DF0EDH0_DB0FD_EHT       BITS(24, 31)                                      /*!< data byte 0 filter data / data byte 0 expected high threshold in Pretended Networking mode */

/* CAN_PN_DF1EDH1 */
#define CAN_PN_DF1EDH1_DB7FD_EHT       BITS(0, 7)                                        /*!< data byte 7 filter data / data byte 7 expected high threshold in Pretended Networking mode */
#define CAN_PN_DF1EDH1_DB6FD_EHT       BITS(8, 15)                                       /*!< data byte 6 filter data / data byte 6 expected high threshold in Pretended Networking mode */
#define CAN_PN_DF1EDH1_DB5FD_EHT       BITS(16, 23)                                      /*!< data byte 5 filter data / data byte 5 expected high threshold in Pretended Networking mode */
#define CAN_PN_DF1EDH1_DB4FD_EHT       BITS(24, 31)                                      /*!< data byte 4 filter data / data byte 4 expected high threshold in Pretended Networking mode */

/* CAN_PN_RWMxCS, x = 0..3 */
#define CAN_PN_RWMXCS_RDLC             BITS(16, 19)                                      /*!< received DLC bits */
#define CAN_PN_RWMXCS_RRTR             BIT(20)                                           /*!< received RTR bit */
#define CAN_PN_RWMXCS_RIDE             BIT(21)                                           /*!< received IDE bit */
#define CAN_PN_RWMXCS_RSRR             BIT(22)                                           /*!< received SRR bit */

/* CAN_PN_RWMxI, x = 0..3 */
#define CAN_PN_RWMXI_RID               BITS(0, 28)                                       /*!< received ID bits */

/* CAN_PN_RWMxD0, x = 0..3 */
#define CAN_PN_RWMXD0_RDB3             BITS(0, 7)                                        /*!< received data byte 3 */
#define CAN_PN_RWMXD0_RDB2             BITS(8, 15)                                       /*!< received data byte 2 */
#define CAN_PN_RWMXD0_RDB1             BITS(16, 23)                                      /*!< received data byte 1 */
#define CAN_PN_RWMXD0_RDB0             BITS(24, 31)                                      /*!< received data byte 0 */

/* CAN_PN_RWMxD1, x = 0..3 */
#define CAN_PN_RWMXD1_RDB7             BITS(0, 7)                                        /*!< received data byte 7 */
#define CAN_PN_RWMXD1_RDB6             BITS(8, 15)                                       /*!< received data byte 6 */
#define CAN_PN_RWMXD1_RDB5             BITS(16, 23)                                      /*!< received data byte 5 */
#define CAN_PN_RWMXD1_RDB4             BITS(24, 31)                                      /*!< received data byte 4 */

/* CAN_FDCTL */
#define CAN_FDCTL_TDCV                 BITS(0, 5)                                        /*!< transmitter delay compensation value */
#define CAN_FDCTL_TDCO                 BITS(8, 12)                                       /*!< transmitter delay compensation offset */
#define CAN_FDCTL_TDCS                 BIT(14)                                           /*!< transmitter delay compensation status */
#define CAN_FDCTL_TDCEN                BIT(15)                                           /*!< transmitter delay compensation enable */
#define CAN_FDCTL_MDSZ                 BITS(16, 17)                                      /*!< mailbox data size */
#define CAN_FDCTL_BRSEN                BIT(31)                                           /*!< bit rate of data switch enable */

/* CAN_FDBT */
#define CAN_FDBT_DPBS2                 BITS(0, 2)                                        /*!< phase buffer segment 2 for data bit time */
#define CAN_FDBT_DPBS1                 BITS(5, 7)                                        /*!< phase buffer segment 1 for data bit time */
#define CAN_FDBT_DPTS                  BITS(10, 14)                                      /*!< propagation time segment for data bit time */
#define CAN_FDBT_DSJW                  BITS(16, 18)                                      /*!< resynchronization jump width for data bit time */
#define CAN_FDBT_DBAUDPSC              BITS(20, 29)                                      /*!< baud rate prescaler for data bit time */

/* CAN_CRCCFD */
#define CAN_CRCCFD_CRCTCI              BITS(0, 20)                                       /*!< transmitted CRC value for classical and ISO / non-ISO frames */
#define CAN_CRCCFD_ANTM                BITS(24, 28)                                      /*!< associated number of mailbox for transmitting the CRCTCI[20:0] value */

/* CAN_MDES0 */
#define CAN_MDES0_TIMESTAMP            BITS(0, 15)                                       /*!< free-running counter timestamp */
#define CAN_MDES0_DLC                  BITS(16, 19)                                      /*!< data length code in bytes */
#define CAN_MDES0_RTR                  BIT(20)                                           /*!< remote transmission request */
#define CAN_MDES0_IDE                  BIT(21)                                           /*!< ID extended bit */
#define CAN_MDES0_SRR                  BIT(22)                                           /*!< substitute remote request */
#define CAN_MDES0_CODE                 BITS(24, 27)                                      /*!< mailbox code */
#define CAN_MDES0_ESI                  BIT(29)                                           /*!< error state indicator */
#define CAN_MDES0_BRS                  BIT(30)                                           /*!< bit rate switch */
#define CAN_MDES0_FDF                  BIT(31)                                           /*!< FD format indicator */

/* CAN_MDES1 */
#define CAN_MDES1_ID_EXD               BITS(0, 17)                                       /*!< identifier for extended frame */
#define CAN_MDES1_ID_STD               BITS(18, 28)                                      /*!< identifier for standard frame */
#define CAN_MDES1_PRIO                 BITS(29, 31)                                      /*!< local priority */

/* CAN_FDES0 */
#define CAN_FDES0_TIMESTAMP            BITS(0, 15)                                       /*!< free-running counter timestamp */
#define CAN_FDES0_DLC                  BITS(16, 19)                                      /*!< data length code in bytes */
#define CAN_FDES0_RTR                  BIT(20)                                           /*!< remote transmission request */
#define CAN_FDES0_IDE                  BIT(21)                                           /*!< ID extended bit */
#define CAN_FDES0_SRR                  BIT(22)                                           /*!< substitute remote request */
#define CAN_FDES0_IDFMN                BITS(23, 31)                                      /*!< identifier filter matching number */

/* CAN_FDES1 */
#define CAN_FDES1_ID_EXT               BITS(0, 17)                                       /*!< identifier for extended frame */
#define CAN_FDES1_ID_STD               BITS(18, 28)                                      /*!< identifier for standard frame */

/* CAN_FDESX_A */
#define CAN_FDESX_ID_EXD_A             BITS(0, 28)                                       /*!< extended ID in format A */
#define CAN_FDESX_ID_STD_A             BITS(18, 28)                                      /*!< standard ID in format A */
#define CAN_FDESX_IDE_A                BIT(30)                                           /*!< ID extended frame for format A */
#define CAN_FDESX_RTR_A                BIT(31)                                           /*!< remote frame for format A */

/* CAN_FDESX_B */
#define CAN_FDESX_ID_EXD_B_1           BITS(0, 13)                                       /*!< extended ID 1 in format B */
#define CAN_FDESX_ID_STD_B_1           BITS(3, 13)                                       /*!< standard ID 1 in format B */
#define CAN_FDESX_IDE_B1               BIT(14)                                           /*!< ID extended frame 1 for format B */
#define CAN_FDESX_RTR_B1               BIT(15)                                           /*!< remote frame 1 for format B */
#define CAN_FDESX_ID_EXD_B_0           BITS(16, 29)                                      /*!< extended ID 0 in format B */
#define CAN_FDESX_ID_STD_B_0           BITS(19, 29)                                      /*!< standard ID 0 in format B */
#define CAN_FDESX_IDE_B0               BIT(30)                                           /*!< ID extended frame 0 for format B */
#define CAN_FDESX_RTR_B0               BIT(31)                                           /*!< remote frame 0 for format B */

/* CAN_FDESX_C */
#define CAN_FDESX_ID_C_3               BITS(0, 7)                                        /*!< ID for frame 3 for format C */
#define CAN_FDESX_ID_C_2               BITS(8, 15)                                       /*!< ID for frame 2 for format C */
#define CAN_FDESX_ID_C_1               BITS(16, 23)                                      /*!< ID for frame 1 for format C */
#define CAN_FDESX_ID_C_0               BITS(24, 31)                                      /*!< ID for frame 0 for format C */

/* consts definitions */
/* define the CAN bit position and its register index offset */
#define CAN_REGIDX_BIT(regidx, bitpos) (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define CAN_REG_VAL(canx, offset)      (REG32((uint32_t)(canx) + ((uint32_t)(offset) >> 6U)))
#define CAN_BIT_POS(val)               ((uint32_t)(val) & 0x0000001FU)
#define CAN_RFIFOMPF(canx, num)        REG32((canx) + 0x00000880U + (num) * 0x00000004U) /*!< CAN receive fifo / mailbox private filter x register */

/* register offset */
#define CTL0_REG_OFFSET                ((uint32_t)0x00000000U)                           /*!< CTL0 register offset */
#define CTL1_REG_OFFSET                ((uint32_t)0x00000004U)                           /*!< CTL1 register offset */
#define ERR1_REG_OFFSET                ((uint32_t)0x00000020U)                           /*!< ERR1 register offset */
#define INTEN_REG_OFFSET               ((uint32_t)0x00000028U)                           /*!< INTEN register offset */
#define STAT_REG_OFFSET                ((uint32_t)0x00000030U)                           /*!< STAT register offset */
#define CTL2_REG_OFFSET                ((uint32_t)0x00000034U)                           /*!< CTL2 register offset */
#define PN_CTL0_REG_OFFSET             ((uint32_t)0x00000B00U)                           /*!< PN_CTL0 register offset */
#define PN_STAT_REG_OFFSET             ((uint32_t)0x00000B08U)                           /*!< PN_STAT register offset */
#define FDCTL_REG_OFFSET               ((uint32_t)0x00000C00U)                           /*!< FDCTL register offset */

/* CAN interrupt enable or disable */
typedef enum {
    /* interrupt in CLT1 register */
    CAN_INT_RX_WARNING            = CAN_REGIDX_BIT(CTL1_REG_OFFSET, 10U),                /*!< receive warning interrupt */
    CAN_INT_TX_WARNING            = CAN_REGIDX_BIT(CTL1_REG_OFFSET, 11U),                /*!< transmit warning interrupt */
    CAN_INT_ERR_SUMMARY           = CAN_REGIDX_BIT(CTL1_REG_OFFSET, 14U),                /*!< error interrupt */
    CAN_INT_BUSOFF                = CAN_REGIDX_BIT(CTL1_REG_OFFSET, 15U),                /*!< bus off interrupt */
    /* interrupt in CLT2 register */
    CAN_INT_BUSOFF_RECOVERY       = CAN_REGIDX_BIT(CTL2_REG_OFFSET, 30U),                /*!< bus off recovery interrupt */
    CAN_INT_ERR_SUMMARY_FD        = CAN_REGIDX_BIT(CTL2_REG_OFFSET, 31U),                /*!< fd error interrupt */
    /* interrupt in INTEN register */
    CAN_INT_MB0                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 0U),                /*!< mailbox 0 interrupt */
    CAN_INT_MB1                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 1U),                /*!< mailbox 1 interrupt */
    CAN_INT_MB2                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 2U),                /*!< mailbox 2 interrupt */
    CAN_INT_MB3                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 3U),                /*!< mailbox 3 interrupt */
    CAN_INT_MB4                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 4U),                /*!< mailbox 4 interrupt */
    CAN_INT_MB5                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 5U),                /*!< mailbox 5 interrupt */
    CAN_INT_MB6                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 6U),                /*!< mailbox 6 interrupt */
    CAN_INT_MB7                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 7U),                /*!< mailbox 7 interrupt */
    CAN_INT_MB8                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 8U),                /*!< mailbox 8 interrupt */
    CAN_INT_MB9                   = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 9U),                /*!< mailbox 9 interrupt */
    CAN_INT_MB10                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 10U),               /*!< mailbox 10 interrupt */
    CAN_INT_MB11                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 11U),               /*!< mailbox 11 interrupt */
    CAN_INT_MB12                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 12U),               /*!< mailbox 12 interrupt */
    CAN_INT_MB13                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 13U),               /*!< mailbox 13 interrupt */
    CAN_INT_MB14                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 14U),               /*!< mailbox 14 interrupt */
    CAN_INT_MB15                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 15U),               /*!< mailbox 15 interrupt */
    CAN_INT_MB16                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 16U),               /*!< mailbox 16 interrupt */
    CAN_INT_MB17                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 17U),               /*!< mailbox 17 interrupt */
    CAN_INT_MB18                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 18U),               /*!< mailbox 18 interrupt */
    CAN_INT_MB19                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 19U),               /*!< mailbox 19 interrupt */
    CAN_INT_MB20                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 20U),               /*!< mailbox 20 interrupt */
    CAN_INT_MB21                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 21U),               /*!< mailbox 21 interrupt */
    CAN_INT_MB22                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 22U),               /*!< mailbox 22 interrupt */
    CAN_INT_MB23                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 23U),               /*!< mailbox 23 interrupt */
    CAN_INT_MB24                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 24U),               /*!< mailbox 24 interrupt */
    CAN_INT_MB25                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 25U),               /*!< mailbox 25 interrupt */
    CAN_INT_MB26                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 26U),               /*!< mailbox 26 interrupt */
    CAN_INT_MB27                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 27U),               /*!< mailbox 27 interrupt */
    CAN_INT_MB28                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 28U),               /*!< mailbox 28 interrupt */
    CAN_INT_MB29                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 29U),               /*!< mailbox 29 interrupt */
    CAN_INT_MB30                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 30U),               /*!< mailbox 30 interrupt */
    CAN_INT_MB31                  = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 31U),               /*!< mailbox 31 interrupt */
    CAN_INT_FIFO_AVAILABLE        = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 5U),                /*!< fifo available interrupt */
    CAN_INT_FIFO_WARNING          = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 6U),                /*!< fifo warning interrupt */
    CAN_INT_FIFO_OVERFLOW         = CAN_REGIDX_BIT(INTEN_REG_OFFSET, 7U),                /*!< fifo overflow interrupt */
    /* interrupt in PN_CTL0 register */
    CAN_INT_WAKEUP_MATCH          = CAN_REGIDX_BIT(PN_CTL0_REG_OFFSET, 16U),             /*!< Pretended Networking match interrupt */
    CAN_INT_WAKEUP_TIMEOUT        = CAN_REGIDX_BIT(PN_CTL0_REG_OFFSET, 17U)              /*!< Pretended Networking timeout wakeup interrupt */
} can_interrupt_enum;

/* CAN flags */
typedef enum {
    /* flags in CTL0 register */
    CAN_FLAG_CAN_PN            = CAN_REGIDX_BIT(CTL0_REG_OFFSET, 18U),                   /*!< Pretended Networking state flag */
    CAN_FLAG_SOFT_RST             = CAN_REGIDX_BIT(CTL0_REG_OFFSET, 25U),                /*!< software reset flag */
    /* flags in ERR1 register */
    CAN_FLAG_ERR_SUMMARY          = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 1U),                 /*!< error summary flag */
    CAN_FLAG_BUSOFF               = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 2U),                 /*!< bus off flag */
    CAN_FLAG_RECEIVING            = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 3U),                 /*!< receiving state flag */
    CAN_FLAG_TRANSMITTING         = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 6U),                 /*!< transmitting state flag */
    CAN_FLAG_IDLE                 = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 7U),                 /*!< IDLE state flag */
    CAN_FLAG_RX_WARNING           = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 8U),                 /*!< receive warning flag */
    CAN_FLAG_TX_WARNING           = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 9U),                 /*!< transmit warning flag */
    CAN_FLAG_STUFF_ERR            = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 10U),                /*!< stuff error flag */
    CAN_FLAG_FORM_ERR             = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 11U),                /*!< form error flag */
    CAN_FLAG_CRC_ERR              = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 12U),                /*!< CRC error flag */
    CAN_FLAG_ACK_ERR              = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 13U),                /*!< ACK error flag */
    CAN_FLAG_BIT_DOMINANT_ERR     = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 14U),                /*!< bit dominant error flag */
    CAN_FLAG_BIT_RECESSIVE_ERR    = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 15U),                /*!< bit recessive error flag */
    CAN_FLAG_SYNC_ERR             = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 18U),                /*!< synchronization flag */
    CAN_FLAG_BUSOFF_RECOVERY      = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 19U),                /*!< bus off recovery flag */
    CAN_FLAG_ERR_SUMMARY_FD       = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 20U),                /*!< FD error summary flag */
    CAN_FLAG_ERR_OVERRUN          = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 21U),                /*!< error overrun flag */
    CAN_FLAG_STUFF_ERR_FD         = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 26U),                /*!< stuff error in FD data phase flag */
    CAN_FLAG_FORM_ERR_FD          = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 27U),                /*!< form error in FD data phase flag */
    CAN_FLAG_CRC_ERR_FD           = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 28U),                /*!< CRC error in FD data phase flag */
    CAN_FLAG_BIT_DOMINANT_ERR_FD  = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 30U),                /*!< bit dominant error in FD data phase flag */
    CAN_FLAG_BIT_RECESSIVE_ERR_FD = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 31U),                /*!< bit recessive error in FD data phase flag */
    /* flags in STAT register */
    CAN_FLAG_MB0                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 0U),                 /*!< mailbox 0 flag */
    CAN_FLAG_MB1                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 1U),                 /*!< mailbox 1 flag */
    CAN_FLAG_MB2                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 2U),                 /*!< mailbox 2 flag */
    CAN_FLAG_MB3                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 3U),                 /*!< mailbox 3 flag */
    CAN_FLAG_MB4                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 4U),                 /*!< mailbox 4 flag */
    CAN_FLAG_MB5                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 5U),                 /*!< mailbox 5 flag */
    CAN_FLAG_MB6                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 6U),                 /*!< mailbox 6 flag */
    CAN_FLAG_MB7                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 7U),                 /*!< mailbox 7 flag */
    CAN_FLAG_MB8                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 8U),                 /*!< mailbox 8 flag */
    CAN_FLAG_MB9                  = CAN_REGIDX_BIT(STAT_REG_OFFSET, 9U),                 /*!< mailbox 9 flag */
    CAN_FLAG_MB10                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 10U),                /*!< mailbox 10 flag */
    CAN_FLAG_MB11                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 11U),                /*!< mailbox 11 flag */
    CAN_FLAG_MB12                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 12U),                /*!< mailbox 12 flag */
    CAN_FLAG_MB13                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 13U),                /*!< mailbox 13 flag */
    CAN_FLAG_MB14                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 14U),                /*!< mailbox 14 flag */
    CAN_FLAG_MB15                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 15U),                /*!< mailbox 15 flag */
    CAN_FLAG_MB16                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 16U),                /*!< mailbox 16 flag */
    CAN_FLAG_MB17                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 17U),                /*!< mailbox 17 flag */
    CAN_FLAG_MB18                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 18U),                /*!< mailbox 18 flag */
    CAN_FLAG_MB19                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 19U),                /*!< mailbox 19 flag */
    CAN_FLAG_MB20                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 20U),                /*!< mailbox 20 flag */
    CAN_FLAG_MB21                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 21U),                /*!< mailbox 21 flag */
    CAN_FLAG_MB22                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 22U),                /*!< mailbox 22 flag */
    CAN_FLAG_MB23                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 23U),                /*!< mailbox 23 flag */
    CAN_FLAG_MB24                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 24U),                /*!< mailbox 24 flag */
    CAN_FLAG_MB25                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 25U),                /*!< mailbox 25 flag */
    CAN_FLAG_MB26                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 26U),                /*!< mailbox 26 flag */
    CAN_FLAG_MB27                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 27U),                /*!< mailbox 27 flag */
    CAN_FLAG_MB28                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 28U),                /*!< mailbox 28 flag */
    CAN_FLAG_MB29                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 29U),                /*!< mailbox 29 flag */
    CAN_FLAG_MB30                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 30U),                /*!< mailbox 30 flag */
    CAN_FLAG_MB31                 = CAN_REGIDX_BIT(STAT_REG_OFFSET, 31U),                /*!< mailbox 31 flag */
    CAN_FLAG_FIFO_AVAILABLE       = CAN_REGIDX_BIT(STAT_REG_OFFSET, 5U),                 /*!< fifo available flag */
    CAN_FLAG_FIFO_WARNING         = CAN_REGIDX_BIT(STAT_REG_OFFSET, 6U),                 /*!< fifo warning flag */
    CAN_FLAG_FIFO_OVERFLOW        = CAN_REGIDX_BIT(STAT_REG_OFFSET, 7U),                 /*!< fifo overflow flag */
    /* flags in PN_STAT register */
    CAN_FLAG_WAKEUP_MATCH         = CAN_REGIDX_BIT(PN_STAT_REG_OFFSET, 16U),             /*!< Pretended Networking match flag */
    CAN_FLAG_WAKEUP_TIMEOUT       = CAN_REGIDX_BIT(PN_STAT_REG_OFFSET, 17U),             /*!< Pretended Networking timeout wakeup flag */
    /* flags in FDCTL register */
    CAN_FLAG_TDC_OUT_OF_RANGE     = CAN_REGIDX_BIT(FDCTL_REG_OFFSET, 14U),               /*!< transmitter delay is out of compensation range flag */
} can_flag_enum;

/* CAN interrupt flags */
typedef enum {
    /* interrupt flags in ERR1 register */
    CAN_INT_FLAG_ERR_SUMMARY      = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 1U),                 /*!< error summary interrupt flag */
    CAN_INT_FLAG_BUSOFF           = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 2U),                 /*!< bus off interrupt flag */
    CAN_INT_FLAG_RX_WARNING       = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 16U),                /*!< receive warning interrupt flag */
    CAN_INT_FLAG_TX_WARNING       = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 17U),                /*!< transmit warning interrupt flag */
    CAN_INT_FLAG_BUSOFF_RECOVERY  = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 19U),                /*!< bus off recovery interrupt flag */
    CAN_INT_FLAG_ERR_SUMMARY_FD   = CAN_REGIDX_BIT(ERR1_REG_OFFSET, 20U),                /*!< fd error summary interrupt flag */
    /* interrupt flags in STAT register */
    CAN_INT_FLAG_MB0              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 0U),                 /*!< mailbox 0 interrupt flag */
    CAN_INT_FLAG_MB1              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 1U),                 /*!< mailbox 1 interrupt flag */
    CAN_INT_FLAG_MB2              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 2U),                 /*!< mailbox 2 interrupt flag */
    CAN_INT_FLAG_MB3              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 3U),                 /*!< mailbox 3 interrupt flag */
    CAN_INT_FLAG_MB4              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 4U),                 /*!< mailbox 4 interrupt flag */
    CAN_INT_FLAG_MB5              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 5U),                 /*!< mailbox 5 interrupt flag */
    CAN_INT_FLAG_MB6              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 6U),                 /*!< mailbox 6 interrupt flag */
    CAN_INT_FLAG_MB7              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 7U),                 /*!< mailbox 7 interrupt flag */
    CAN_INT_FLAG_MB8              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 8U),                 /*!< mailbox 8 interrupt flag */
    CAN_INT_FLAG_MB9              = CAN_REGIDX_BIT(STAT_REG_OFFSET, 9U),                 /*!< mailbox 9 interrupt flag */
    CAN_INT_FLAG_MB10             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 10U),                /*!< mailbox 10 interrupt flag */
    CAN_INT_FLAG_MB11             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 11U),                /*!< mailbox 11 interrupt flag */
    CAN_INT_FLAG_MB12             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 12U),                /*!< mailbox 12 interrupt flag */
    CAN_INT_FLAG_MB13             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 13U),                /*!< mailbox 13 interrupt flag */
    CAN_INT_FLAG_MB14             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 14U),                /*!< mailbox 14 interrupt flag */
    CAN_INT_FLAG_MB15             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 15U),                /*!< mailbox 15 interrupt flag */
    CAN_INT_FLAG_MB16             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 16U),                /*!< mailbox 16 interrupt flag */
    CAN_INT_FLAG_MB17             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 17U),                /*!< mailbox 17 interrupt flag */
    CAN_INT_FLAG_MB18             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 18U),                /*!< mailbox 18 interrupt flag */
    CAN_INT_FLAG_MB19             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 19U),                /*!< mailbox 19 interrupt flag */
    CAN_INT_FLAG_MB20             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 20U),                /*!< mailbox 20 interrupt flag */
    CAN_INT_FLAG_MB21             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 21U),                /*!< mailbox 21 interrupt flag */
    CAN_INT_FLAG_MB22             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 22U),                /*!< mailbox 22 interrupt flag */
    CAN_INT_FLAG_MB23             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 23U),                /*!< mailbox 23 interrupt flag */
    CAN_INT_FLAG_MB24             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 24U),                /*!< mailbox 24 interrupt flag */
    CAN_INT_FLAG_MB25             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 25U),                /*!< mailbox 25 interrupt flag */
    CAN_INT_FLAG_MB26             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 26U),                /*!< mailbox 26 interrupt flag */
    CAN_INT_FLAG_MB27             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 27U),                /*!< mailbox 27 interrupt flag */
    CAN_INT_FLAG_MB28             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 28U),                /*!< mailbox 28 interrupt flag */
    CAN_INT_FLAG_MB29             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 29U),                /*!< mailbox 29 interrupt flag */
    CAN_INT_FLAG_MB30             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 30U),                /*!< mailbox 30 interrupt flag */
    CAN_INT_FLAG_MB31             = CAN_REGIDX_BIT(STAT_REG_OFFSET, 31U),                /*!< mailbox 31 interrupt flag */
    CAN_INT_FLAG_FIFO_AVAILABLE   = CAN_REGIDX_BIT(STAT_REG_OFFSET, 5U),                 /*!< fifo available interrupt flag */
    CAN_INT_FLAG_FIFO_WARNING     = CAN_REGIDX_BIT(STAT_REG_OFFSET, 6U),                 /*!< fifo warning interrupt flag */
    CAN_INT_FLAG_FIFO_OVERFLOW    = CAN_REGIDX_BIT(STAT_REG_OFFSET, 7U),                 /*!< fifo overflow interrupt flag */
    /* interrupt flags in PN_STAT register */
    CAN_INT_FLAG_WAKEUP_MATCH     = CAN_REGIDX_BIT(PN_STAT_REG_OFFSET, 16U),             /*!< Pretended Networking match interrupt flag */
    CAN_INT_FLAG_WAKEUP_TIMEOUT   = CAN_REGIDX_BIT(PN_STAT_REG_OFFSET, 17U)              /*!< Pretended Networking timeout wakeup interrupt flag */
} can_interrupt_flag_enum;

/* operation modes */
typedef enum {
    CAN_NORMAL_MODE               = 0U,                                                  /*!< normal mode */
    CAN_MONITOR_MODE              = 1U,                                                  /*!< monitor mode */
    CAN_LOOPBACK_SILENT_MODE      = 2U,                                                  /*!< loopback mode */
    CAN_INACTIVE_MODE             = 3U,                                                  /*!< inactive mode */
    CAN_DISABLE_MODE              = 4U,                                                  /*!< disable mode */
    CAN_PN_MODE                   = 5U                                                   /*!< Pretended Networking mode */
} can_operation_modes_enum;

/* initialize parameter type */
typedef enum {
    CAN_INIT_STRUCT               = 0U,                                                  /*!< CAN initialize parameters struct */
    CAN_FD_INIT_STRUCT            = 1U,                                                  /*!< CAN FD parameters struct */
    CAN_FIFO_INIT_STRUCT          = 2U,                                                  /*!< CAN fifo parameters struct */
    CAN_PN_MODE_INIT_STRUCT       = 3U,                                                  /*!< Pretended Networking mode parameter strcut */
    CAN_PN_MODE_FILTER_STRUCT     = 4U,                                                  /*!< Pretended Networking mode filter parameter strcut */
    CAN_MDSC_STRUCT               = 5U,                                                  /*!< mailbox descriptor strcut */
    CAN_FDES_STRUCT               = 6U,                                                  /*!< Rx fifo descriptor strcut */
    CAN_FIFO_ID_FILTER_STRUCT     = 7U,                                                  /*!< Rx fifo id filter strcut */
    CAN_CRC_STRUCT                = 8U,                                                  /*!< CRC strcut */
    CAN_ERRCNT_STRUCT             = 9U,                                                  /*!< error counter strcut */
} can_struct_type_enum;

/* error state indicator */
typedef enum {
    CAN_ERROR_STATE_ACTIVE        = 0U,                                                  /*!< CAN in error active */
    CAN_ERROR_STATE_PASSIVE       = 1U,                                                  /*!< CAN in error passive */
    CAN_ERROR_STATE_BUS_OFF       = 2U                                                   /*!< CAN in bus off */
} can_error_state_enum;

/* error counter structure */
typedef struct {
    uint8_t fd_data_phase_rx_errcnt;                                                     /*!< receive error counter for data phase of FD frames with BRS bit set */
    uint8_t fd_data_phase_tx_errcnt;                                                     /*!< transmit error count for the data phase of FD frames with BRS bit set */
    uint8_t rx_errcnt;                                                                   /*!< receive error count defined by the CAN standard */
    uint8_t tx_errcnt;                                                                   /*!< transmit error count defined by the CAN standard */
} can_error_counter_struct;

/* CAN initialize parameters structure */
typedef struct {
    uint32_t internal_counter_source;                                                    /*!< internal counter source */
    uint32_t mb_tx_order;                                                                /*!< mailbox transmit order */
    uint32_t mb_rx_ide_rtr_type;                                                         /*!< IDE and RTR field filter type  */
    uint32_t mb_remote_frame;                                                            /*!< remote request frame is stored */
    uint8_t self_reception;                                                              /*!< enable or disable self reception */
    uint8_t mb_tx_abort_enable;                                                          /*!< enable or disable transmit abort */
    uint8_t local_priority_enable;                                                       /*!< enable or disable local priority */
    uint8_t rx_private_filter_queue_enable;                                              /*!< private filter and queue enable */
    uint32_t edge_filter_enable;                                                         /*!< edge filter enable*/
    uint32_t protocol_exception_enable;                                                  /*!< protocol exception enable */
    uint32_t rx_filter_order;                                                            /*!< receive filter order */
    uint32_t memory_size;                                                                /*!< memory size */
    uint32_t mb_public_filter;                                                           /*!< mailbox public filter */
    uint32_t prescaler;                                                                  /*!< baud rate prescaler */
    uint8_t resync_jump_width;                                                           /*!< resynchronization jump width */
    uint8_t prop_time_segment;                                                           /*!< propagation time segment */
    uint8_t time_segment_1;                                                              /*!< time segment 1 */
    uint8_t time_segment_2;                                                              /*!< time segment 2 */
} can_parameter_struct;

/* mailbox descriptor struct */
typedef struct {
    uint32_t timestamp : 16;                                                             /*!< free-running counter timestamp */
    uint32_t dlc : 4;                                                                    /*!< data length code in bytes */
    uint32_t rtr : 1;                                                                    /*!< remote transmission request */
    uint32_t ide : 1;                                                                    /*!< ID extended bit */
    uint32_t srr : 1;                                                                    /*!< substitute remote request */
    uint32_t reserve1 : 1;                                                               /*!< reserve bit 1 */
    uint32_t code : 4;                                                                   /*!< mailbox code */
    uint32_t reserve2 : 1;                                                               /*!< reserve bit 2 */
    uint32_t esi : 1;                                                                    /*!< error state indicator */
    uint32_t brs : 1;                                                                    /*!< bit rate switch */
    uint32_t fdf : 1;                                                                    /*!< FD format indicator */
    uint32_t id : 29;                                                                    /*!< identifier for frame */
    uint32_t prio : 3;                                                                   /*!< local priority */
    uint32_t *data;                                                                      /*!< data */
    uint32_t data_bytes;                                                                 /*!< data bytes */
    uint8_t padding;                                                                     /*!< FD mode padding data */
} can_mailbox_descriptor_struct;

/* fifo descriptor struct */
typedef struct {
    uint32_t timestamp : 16;                                                             /*!< free-running counter timestamp */
    uint32_t dlc : 4;                                                                    /*!< data length code in bytes */
    uint32_t rtr : 1;                                                                    /*!< remote transmission request */
    uint32_t ide : 1;                                                                    /*!< ID extended bit */
    uint32_t srr : 1;                                                                    /*!< substitute remote request */
    uint32_t idhit : 9;                                                                  /*!< identifier filter matching number */
    uint32_t id;                                                                         /*!< identifier for frame */
    uint32_t data[2];                                                                    /*!< fifo data */
} can_rx_fifo_struct;

/* FD initialize parameter struct */
typedef struct {
    uint32_t iso_can_fd_enable;                                                          /*!< ISO CAN FD protocol enable */
    uint32_t bitrate_switch_enable;                                                      /*!< data bit rate switch */
    uint32_t mailbox_data_size;                                                          /*!< mailbox data size */
    uint32_t tdc_enable;                                                                 /*!< transmitter delay compensation enable */
    uint32_t tdc_offset;                                                                 /*!< transmitter delay compensation offset */
    uint32_t prescaler;                                                                  /*!< baud rate prescaler */
    uint8_t resync_jump_width;                                                           /*!< resynchronization jump width */
    uint8_t prop_time_segment;                                                           /*!< propagation time segment */
    uint8_t time_segment_1;                                                              /*!< time segment 1 */
    uint8_t time_segment_2;                                                              /*!< time segment 2 */
} can_fd_parameter_struct;

/* FIFO ID filter table struct */
typedef struct {
    uint32_t remote_frame;                                                               /*!< expected remote frame*/
    uint32_t extended_frame;                                                             /*!< expected extended frame */
    uint32_t id;                                                                         /*!< expected id */
} can_rx_fifo_id_filter_struct;

/* FIFO initialize parameter struct */
typedef struct {
    uint8_t dma_enable;                                                                  /*!< DMA enable */
    uint32_t filter_format_and_number;                                                   /*!< FIFO ID filter format and number */
    uint32_t fifo_public_filter;                                                         /*!< FIFO ID public filter */
} can_fifo_parameter_struct;

/* Pretended Networking mode filter parameter struct */
typedef struct {
    uint32_t rtr;                                                                        /*!< remote frame */
    uint32_t ide;                                                                        /*!< extended frame */
    uint32_t id;                                                                         /*!< id */
    uint32_t dlc_high_threshold;                                                         /*!< DLC expected high threshold */
    uint32_t dlc_low_threshold;                                                          /*!< DLC expected low threshold */
    uint32_t payload[2];                                                                 /*!< data */
} can_pn_mode_filter_struct;

/* Pretended Networking mode initialize parameter struct */
typedef struct {
    uint32_t timeout_int;                                                                /*!< enable or disable timeout interrupt */
    uint32_t match_int;                                                                  /*!< enable or disable match interrupt */
    uint32_t num_matches;                                                                /*!< set number of message matching times */
    uint32_t match_timeout;                                                              /*!< set wakeup timeout value */
    uint32_t frame_filter;                                                               /*!< set frame filtering type */
    uint32_t id_filter;                                                                  /*!< set id filtering type */
    uint32_t data_filter;                                                                /*!< set data filtering type */
} can_pn_mode_config_struct;

/* CRC parameter struct */
typedef struct {
    uint32_t classical_frm_mb_number;                                                    /*!< associated number of mailbox for transmitting the CRCTC[14:0] value */
    uint32_t classical_frm_transmitted_crc;                                              /*!< transmitted CRC value for classical frames */
    uint32_t classical_fd_frm_mb_number;                                                 /*!< associated number of mailbox for transmitting the CRCTCI[20:0] value */
    uint32_t classical_fd_frm_transmitted_crc;                                           /*!< transmitted CRC value for classical and ISO / non-ISO FD frames */
} can_crc_struct;

/* CAN_CTL0 register */
#define CTL0_MSZ(regval)                     (CAN_CTL0_MSZ & ((uint32_t)(regval) << 0U)) /*!< write value to CAN_CTL0_MSZ bit field */
#define CAN_MEMSIZE_1_UNIT                   CTL0_MSZ(0U)                                /*!< 1 unit for message transmission and reception */
#define CAN_MEMSIZE_2_UNIT                   CTL0_MSZ(1U)                                /*!< 2 units for message transmission and reception */
#define CAN_MEMSIZE_3_UNIT                   CTL0_MSZ(2U)                                /*!< 3 units for message transmission and reception */
#define CAN_MEMSIZE_4_UNIT                   CTL0_MSZ(3U)                                /*!< 4 units for message transmission and reception */
#define CAN_MEMSIZE_5_UNIT                   CTL0_MSZ(4U)                                /*!< 5 units for message transmission and reception */
#define CAN_MEMSIZE_6_UNIT                   CTL0_MSZ(5U)                                /*!< 6 units for message transmission and reception */
#define CAN_MEMSIZE_7_UNIT                   CTL0_MSZ(6U)                                /*!< 7 units for message transmission and reception */
#define CAN_MEMSIZE_8_UNIT                   CTL0_MSZ(7U)                                /*!< 8 units for message transmission and reception */
#define CAN_MEMSIZE_9_UNIT                   CTL0_MSZ(8U)                                /*!< 9 units for message transmission and reception */
#define CAN_MEMSIZE_10_UNIT                  CTL0_MSZ(9U)                                /*!< 10 units for message transmission and reception */
#define CAN_MEMSIZE_11_UNIT                  CTL0_MSZ(10U)                               /*!< 11 units for message transmission and reception */
#define CAN_MEMSIZE_12_UNIT                  CTL0_MSZ(11U)                               /*!< 12 units for message transmission and reception */
#define CAN_MEMSIZE_13_UNIT                  CTL0_MSZ(12U)                               /*!< 13 units for message transmission and reception */
#define CAN_MEMSIZE_14_UNIT                  CTL0_MSZ(13U)                               /*!< 14 units for message transmission and reception */
#define CAN_MEMSIZE_15_UNIT                  CTL0_MSZ(14U)                               /*!< 15 units for message transmission and reception */
#define CAN_MEMSIZE_16_UNIT                  CTL0_MSZ(15U)                               /*!< 16 units for message transmission and reception */
#define CAN_MEMSIZE_17_UNIT                  CTL0_MSZ(16U)                               /*!< 17 units for message transmission and reception */
#define CAN_MEMSIZE_18_UNIT                  CTL0_MSZ(17U)                               /*!< 18 units for message transmission and reception */
#define CAN_MEMSIZE_19_UNIT                  CTL0_MSZ(18U)                               /*!< 19 units for message transmission and reception */
#define CAN_MEMSIZE_20_UNIT                  CTL0_MSZ(19U)                               /*!< 20 units for message transmission and reception */
#define CAN_MEMSIZE_21_UNIT                  CTL0_MSZ(20U)                               /*!< 21 units for message transmission and reception */
#define CAN_MEMSIZE_22_UNIT                  CTL0_MSZ(21U)                               /*!< 22 units for message transmission and reception */
#define CAN_MEMSIZE_23_UNIT                  CTL0_MSZ(22U)                               /*!< 23 units for message transmission and reception */
#define CAN_MEMSIZE_24_UNIT                  CTL0_MSZ(23U)                               /*!< 24 units for message transmission and reception */
#define CAN_MEMSIZE_25_UNIT                  CTL0_MSZ(24U)                               /*!< 25 units for message transmission and reception */
#define CAN_MEMSIZE_26_UNIT                  CTL0_MSZ(25U)                               /*!< 26 units for message transmission and reception */
#define CAN_MEMSIZE_27_UNIT                  CTL0_MSZ(26U)                               /*!< 27 units for message transmission and reception */
#define CAN_MEMSIZE_28_UNIT                  CTL0_MSZ(27U)                               /*!< 28 units for message transmission and reception */
#define CAN_MEMSIZE_29_UNIT                  CTL0_MSZ(28U)                               /*!< 29 units for message transmission and reception */
#define CAN_MEMSIZE_30_UNIT                  CTL0_MSZ(29U)                               /*!< 30 units for message transmission and reception */
#define CAN_MEMSIZE_31_UNIT                  CTL0_MSZ(30U)                               /*!< 31 units for message transmission and reception */
#define CAN_MEMSIZE_32_UNIT                  CTL0_MSZ(31U)                               /*!< 32 units for message transmission and reception */

#define CTL0_FS(regval)                      (CAN_CTL0_FS & ((uint32_t)(regval) << 8U))  /*!< write value to CAN_CTL0_FS bit field */
#define CAN_FIFO_FILTER_FORMAT_A             CTL0_FS(0U)                                 /*!< FIFO filter format A */
#define CAN_FIFO_FILTER_FORMAT_B             CTL0_FS(1U)                                 /*!< FIFO filter format B */
#define CAN_FIFO_FILTER_FORMAT_C             CTL0_FS(2U)                                 /*!< FIFO filter format C */
#define CAN_FIFO_FILTER_FORMAT_D             CTL0_FS(3U)                                 /*!< FIFO filter format D */

#define GET_CTL0_FS(regval)                  GET_BITS((regval),8,9)                       /*!< get CAN_CTL0_FS bit field */

/* CAN_CTL1 register */
#define CAN_TX_HIGH_PRIORITY_MB_FIRST        ((uint32_t)0x00000000U)                      /*!< highest priority mailbox first */
#define CAN_TX_LOW_NUM_MB_FIRST              CAN_CTL1_MTO                                 /*!< low number mailbox first */

#define CAN_BSP_MODE_ONE_SAMPLE              ((uint32_t)0x00000000U)                      /*!< one sample for the received bit */
#define CAN_BSP_MODE_THREE_SAMPLES           CAN_CTL1_BSPMOD                              /*!< three sample for received bit */

/* CAN_ERR0 register */
#define GET_ERR0_REFCNT(regval)              GET_BITS((regval),24,31)                     /*!< get receive error counter for data phase of FD frames with BRS bit set */
#define GET_ERR0_TEFCNT(regval)              GET_BITS((regval),16,23)                     /*!< get transmit error counter for data phase of FD frames with BRS bit set */
#define GET_ERR0_RECNT(regval)               GET_BITS((regval),8,15)                      /*!< get receive error counter defined by the CAN standard */
#define GET_ERR0_TECNT(regval)               GET_BITS((regval),0,7)                       /*!< get transmit error counter defined by the CAN standard */
#define ERR0_REFCNT(regval)                  (BITS(24,31) & ((uint32_t)(regval) << 24U))  /*!< set receive error counter for data phase of FD frames with BRS bit set */
#define ERR0_TEFCNT(regval)                  (BITS(16,23) & ((uint32_t)(regval) << 16U))  /*!< set transmit error counter for data phase of FD frames with BRS bit set */
#define ERR0_RECNT(regval)                   (BITS(8,15) & ((uint32_t)(regval) << 8U))    /*!< set receive error counter defined by the CAN standard */
#define ERR0_TECNT(regval)                   (BITS(0,7) & ((uint32_t)(regval) << 0U))     /*!< set transmit error counter defined by the CAN standard */

/* CAN_ERR1 register */
#define GET_ERR1_ERRSI(regval)               GET_BITS((regval),4,5)                       /*!< read CAN_ERR1_ERRSI bit field */

/* CAN_STAT register */
#define STAT_MS(regval)                      BIT(regval)                                  /*!< write value to CAN_STAT_MS bit field */

/* CAN_CTL2 register */
#define CAN_TIMER_SOURCE_BIT_CLOCK           ((uint32_t)0x00000000U)                      /*!< internal counter source is CAN bit clock */
#define CAN_TIMER_SOURCE_EXTERNAL_TIME_TICK  CAN_CTL2_ITSRC                               /*!< internal counter source is external time tick */

#define CAN_IDE_RTR_COMPARED                 ((uint32_t)0x00000000U)                      /*!< always compare IDE bit, never compare RTR bit */
#define CAN_IDE_RTR_FILTERED                 CAN_CTL2_IDERTR_RMF                          /*!< filtering IDE and RTR fields */

#define CAN_GEN_REMOTE_RESPONSE_FRAME        ((uint32_t)0x00000000U)                      /* remote response frame is generated when a mailbox with CODE RANSWER is found with the same ID */
#define CAN_STORE_REMOTE_REQUEST_FRAME       CAN_CTL2_RRFRMS                              /* remote request frame is stored as a data frame without automatic remote response frame transmitted */

#define CAN_RX_FILTER_ORDER_FIFO_FIRST       ((uint32_t)0x00000000U)                      /*!< receive search FIFO first */
#define CAN_RX_FILTER_ORDER_MAILBOX_FIRST    CAN_CTL2_RFO                                 /*!< receive search mailbox first */

#define CTL2_ASD(regval)                     (BITS(19,23) & ((uint32_t)(regval) << 19U))  /*!< write value to CAN_CTL2_ASD bit field */

#define CTL2_RFFN(regval)                    (BITS(24,27) & ((uint32_t)(regval) << 24U))  /*!< write value to CAN_CTL2_RFFN bit field */
#define GET_CTL2_RFFN(regval)                GET_BITS((regval),24,27)                     /*!< get CAN_CTL2_RFFN bit field */
#define CAN_RXFIFO_FILTER_A_NUM_8            (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(0U))   /*!< FIFO ID filter format A and 8 filters */
#define CAN_RXFIFO_FILTER_A_NUM_16           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(1U))   /*!< FIFO ID filter format A and 16 filters */
#define CAN_RXFIFO_FILTER_A_NUM_24           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(2U))   /*!< FIFO ID filter format A and 24 filters */
#define CAN_RXFIFO_FILTER_A_NUM_32           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(3U))   /*!< FIFO ID filter format A and 32 filters */
#define CAN_RXFIFO_FILTER_A_NUM_40           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(4U))   /*!< FIFO ID filter format A and 40 filters */
#define CAN_RXFIFO_FILTER_A_NUM_48           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(5U))   /*!< FIFO ID filter format A and 48 filters */
#define CAN_RXFIFO_FILTER_A_NUM_56           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(6U))   /*!< FIFO ID filter format A and 56 filters */
#define CAN_RXFIFO_FILTER_A_NUM_64           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(7U))   /*!< FIFO ID filter format A and 64 filters */
#define CAN_RXFIFO_FILTER_A_NUM_72           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(8U))   /*!< FIFO ID filter format A and 72 filters */
#define CAN_RXFIFO_FILTER_A_NUM_80           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(9U))   /*!< FIFO ID filter format A and 80 filters */
#define CAN_RXFIFO_FILTER_A_NUM_88           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(10U))  /*!< FIFO ID filter format A and 88 filters */
#define CAN_RXFIFO_FILTER_A_NUM_96           (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(11U))  /*!< FIFO ID filter format A and 96 filters */
#define CAN_RXFIFO_FILTER_A_NUM_104          (CAN_FIFO_FILTER_FORMAT_A | CTL2_RFFN(12U))  /*!< FIFO ID filter format A and 104 filters */
#define CAN_RXFIFO_FILTER_B_NUM_16           (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(0U))   /*!< FIFO ID filter format B and 16 filters */
#define CAN_RXFIFO_FILTER_B_NUM_32           (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(1U))   /*!< FIFO ID filter format B and 32 filters */
#define CAN_RXFIFO_FILTER_B_NUM_48           (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(2U))   /*!< FIFO ID filter format B and 48 filters */
#define CAN_RXFIFO_FILTER_B_NUM_64           (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(3U))   /*!< FIFO ID filter format B and 64 filters */
#define CAN_RXFIFO_FILTER_B_NUM_80           (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(4U))   /*!< FIFO ID filter format B and 80 filters */
#define CAN_RXFIFO_FILTER_B_NUM_96           (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(5U))   /*!< FIFO ID filter format B and 96 filters */
#define CAN_RXFIFO_FILTER_B_NUM_112          (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(6U))   /*!< FIFO ID filter format B and 112 filters */
#define CAN_RXFIFO_FILTER_B_NUM_128          (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(7U))   /*!< FIFO ID filter format B and 128 filters */
#define CAN_RXFIFO_FILTER_B_NUM_144          (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(8U))   /*!< FIFO ID filter format B and 144 filters */
#define CAN_RXFIFO_FILTER_B_NUM_160          (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(9U))   /*!< FIFO ID filter format B and 160 filters */
#define CAN_RXFIFO_FILTER_B_NUM_176          (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(10U))  /*!< FIFO ID filter format B and 176 filters */
#define CAN_RXFIFO_FILTER_B_NUM_192          (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(11U))  /*!< FIFO ID filter format B and 192 filters */
#define CAN_RXFIFO_FILTER_B_NUM_208          (CAN_FIFO_FILTER_FORMAT_B | CTL2_RFFN(12U))  /*!< FIFO ID filter format B and 208 filters */
#define CAN_RXFIFO_FILTER_C_NUM_32           (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(0U))   /*!< FIFO ID filter format C and 32 filters */
#define CAN_RXFIFO_FILTER_C_NUM_64           (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(1U))   /*!< FIFO ID filter format C and 64 filters */
#define CAN_RXFIFO_FILTER_C_NUM_96           (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(2U))   /*!< FIFO ID filter format C and 96 filters */
#define CAN_RXFIFO_FILTER_C_NUM_128          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(3U))   /*!< FIFO ID filter format C and 128 filters */
#define CAN_RXFIFO_FILTER_C_NUM_160          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(4U))   /*!< FIFO ID filter format C and 160 filters */
#define CAN_RXFIFO_FILTER_C_NUM_192          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(5U))   /*!< FIFO ID filter format C and 192 filters */
#define CAN_RXFIFO_FILTER_C_NUM_224          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(6U))   /*!< FIFO ID filter format C and 224 filters */
#define CAN_RXFIFO_FILTER_C_NUM_256          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(7U))   /*!< FIFO ID filter format C and 256 filters */
#define CAN_RXFIFO_FILTER_C_NUM_288          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(8U))   /*!< FIFO ID filter format C and 288 filters */
#define CAN_RXFIFO_FILTER_C_NUM_320          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(9U))   /*!< FIFO ID filter format C and 320 filters */
#define CAN_RXFIFO_FILTER_C_NUM_352          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(10U))  /*!< FIFO ID filter format C and 352 filters */
#define CAN_RXFIFO_FILTER_C_NUM_384          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(11U))  /*!< FIFO ID filter format C and 384 filters */
#define CAN_RXFIFO_FILTER_C_NUM_416          (CAN_FIFO_FILTER_FORMAT_C | CTL2_RFFN(12U))  /*!< FIFO ID filter format C and 416 filters */
#define CAN_RXFIFO_FILTER_D                  CAN_FIFO_FILTER_FORMAT_D                     /*!< FIFO ID filter format D */

/* CAN_CRCC register */
#define GET_CRCC_ANTM(regval)                GET_BITS((regval),16,20)                     /*!< get associated number of mailbox for transmitting the CRCTC[14:0] value */
#define GET_CRCC_CRCTC(regval)               GET_BITS((regval),0,14)                      /*!< get transmitted CRC value for classical frames */

/* CAN_RFIFOIFMN register */
#define GET_RFIFOIFMN_IDFMN(regval)          GET_BITS((regval),0,8)                       /*!< get identifier filter matching number */

/* CAN_BT register */
#define BT_PBS2(regval)                      (BITS(0,4) & ((uint32_t)(regval) << 0U))     /*!< write value to CAN_BT_PBS2 bit field */
#define BT_PBS1(regval)                      (BITS(5,9) & ((uint32_t)(regval) << 5U))     /*!< write value to CAN_BT_PBS1 bit field */
#define BT_PTS(regval)                       (BITS(10,15) & ((uint32_t)(regval) << 10U))  /*!< write value to CAN_BT_PTS bit field */
#define BT_SJW(regval)                       (BITS(16,20) & ((uint32_t)(regval) << 16U))  /*!< write value to CAN_BT_SJW bit field */
#define BT_BAUDPSC(regval)                   (BITS(21,30) & ((uint32_t)(regval) << 21U))  /*!< write value to CAN_BT_BAUDPSC bit field */

/* CAN_FDCTL register */
#define GET_FDCTL_MDSZ(regval)               GET_BITS((regval),16,17)                     /*!< get mailbox data size */

/* CAN_PN_CTL0 register */
#define PN_CTL0_FFT(regval)                  (BITS(0,1) & ((uint32_t)(regval) << 0U))     /*!< write value to CAN_PN_CTL0_FFT bit field */
#define CAN_PN_FRAME_FILTERING_ID            PN_CTL0_FFT(0U)                              /*!< all fields except DATA field, DLC field are filtered */
#define CAN_PN_FRAME_FILTERING_ID_DATA       PN_CTL0_FFT(1U)                              /*!< all fields are filtered */
#define CAN_PN_FRAME_FILTERING_ID_NMM        PN_CTL0_FFT(2U)                              /*!< all fields except DATA field, DLC field are filtered with NMM[7:0] matching times */
#define CAN_PN_FRAME_FILTERING_ID_DATA_NMM   PN_CTL0_FFT(3U)                              /*!< all fields are filtered with NMM[7:0] matching times */

#define PN_CTL0_IDFT(regval)                 (BITS(2,3) & ((uint32_t)(regval) << 2U))     /*!< write value to CAN_PN_CTL0_IDFT bit field */
#define CAN_PN_ID_FILTERING_EXACT            PN_CTL0_IDFT(0U)                             /*!< DATA field equal to the expected data field */
#define CAN_PN_ID_FILTERING_GREATER          PN_CTL0_IDFT(1U)                             /*!< DATA field greater than or equal to the expected data */
#define CAN_PN_ID_FILTERING_SMALLER          PN_CTL0_IDFT(2U)                             /*!< DATA field greater than or equal to the expected data */
#define CAN_PN_ID_FILTERING_RANGE            PN_CTL0_IDFT(3U)                             /*!< DATA field is between expected data high threshold and low threshold */

#define PN_CTL0_DATAFT(regval)               (BITS(4,5) & ((uint32_t)(regval) << 4U))     /*!< write value to CAN_PN_CTL0_DATAFT bit field */
#define CAN_PN_DATA_FILTERING_EXACT          PN_CTL0_DATAFT(0U)                           /*!< ID field equal to the expected identifie */
#define CAN_PN_DATA_FILTERING_GREATER        PN_CTL0_DATAFT(1U)                           /*!< ID field greater than or equal to the expected identifier */
#define CAN_PN_DATA_FILTERING_SMALLER        PN_CTL0_DATAFT(2U)                           /*!< ID field smaller than or equal to the expected identifier */
#define CAN_PN_DATA_FILTERING_RANGE          PN_CTL0_DATAFT(3U)                           /*!< ID field is between expected idetifier high threshold and low threshold */

#define PN_CTL0_NMM(regval)                  (BITS(8,15) & ((uint32_t)(regval) << 8U))    /*!< write value to CAN_PN_CTL0_NMM bit field */

#define PN_CTL0_WMIE(regval)                 (BIT(16) & ((uint32_t)(regval) << 16U))      /*!< write value to CAN_PN_CTL0_WMIE bit */

#define PN_CTL0_WTOIE(regval)                (BIT(17) & ((uint32_t)(regval) << 17U))      /*!< write value to CAN_PN_CTL0_WTOIE bit */

/* CAN_PN_TO register */
#define PN_TO_WTO(regval)                    (BITS(0,15) & ((uint32_t)(regval) << 0U))    /*!< write value to CAN_PN_TO_WTO bit field */

/* CAN_PN_STAT register */
#define GET_PN_STAT_MMCNT(regval)            GET_BITS((regval),8,15)                      /*!< get matching message counter in Pretended Networking mode */

/* CAN_PN_EID0 register */
#define PN_EID0_EIDF_ELT_STD(regval)         (BITS(18,28) & ((uint32_t)(regval) << 18U))  /*!< write value to CAN_PN_EID0_EIDF_ELT bit field for standard frames */
#define PN_EID0_EIDF_ELT_EXD(regval)         (BITS(0,28) & ((uint32_t)(regval) << 0U))    /*!< write value to CAN_PN_EID0_EIDF_ELT bit field for extended frames */

/* CAN_PN_EDLC register */
#define PN_EDLC_DLCEHT(regval)               (BITS(0,3) & ((uint32_t)(regval) << 0U))     /*!< write value to CAN_PN_EDLC_DLCEHT bit field */
#define PN_EDLC_DLCELT(regval)               (BITS(16,19) & ((uint32_t)(regval) << 16U))  /*!< write value to CAN_PN_EDLC_DLCELT bit field */

/* CAN_PN_IFEID1 register */
#define PN_IFEID1_IDEFD_STD(regval)          (BITS(18,28) & ((uint32_t)(regval) << 18U))  /*!< write value to CAN_PN_IFEID1_IDEFD bit field for standard frames */
#define PN_IFEID1_IDEFD_EXD(regval)          (BITS(0,28) & ((uint32_t)(regval) << 0U))    /*!< write value to CAN_PN_IFEID1_IDEFD bit field for extended frames */

/* CAN_FDCTL register */
#define GET_FDCTL_TDCV(regval)               GET_BITS((regval),0,5)                       /*!< get transmitter delay compensation value */

#define FDCTL_TDCO(regval)                   (BITS(8,12) & ((uint32_t)(regval) << 8U))    /*!< write value to CAN_FDCTL_TDCO bit field */

#define FDCTL_MDSZ(regval)                   (BITS(16,17) & ((uint32_t)(regval) << 16U))  /*!< write value to CAN_FDCTL_MDSZ bit field */
#define CAN_MAILBOX_DATA_SIZE_8_BYTES        FDCTL_MDSZ(0U)                               /*!< mailbox data size is 8 bytes */
#define CAN_MAILBOX_DATA_SIZE_16_BYTES       FDCTL_MDSZ(1U)                               /*!< mailbox data size is 16 bytes */
#define CAN_MAILBOX_DATA_SIZE_32_BYTES       FDCTL_MDSZ(2U)                               /*!< mailbox data size is 32 bytes */
#define CAN_MAILBOX_DATA_SIZE_64_BYTES       FDCTL_MDSZ(3U)                               /*!< mailbox data size is 64 bytes */

/* CAN_FDBT register */
#define FDBT_DPBS2(regval)                   (BITS(0,2) & ((uint32_t)(regval) << 0U))     /*!< write value to CAN_FDBT_DPBS2 bit field */
#define FDBT_DPBS1(regval)                   (BITS(5,7) & ((uint32_t)(regval) << 5U))     /*!< write value to CAN_FDBT_DPBS1 bit field */
#define FDBT_DPTS(regval)                    (BITS(10,14) & ((uint32_t)(regval) << 10U))  /*!< write value to CAN_FDBT_DPTS bit field */
#define FDBT_DSJW(regval)                    (BITS(16,18) & ((uint32_t)(regval) << 16U))  /*!< write value to CAN_FDBT_DSJW bit field */
#define FDBT_DBAUDPSC(regval)                (BITS(20,29) & ((uint32_t)(regval) << 20U))  /*!< write value to CAN_FDBT_DBAUDPSC bit field */

/* CAN_CRCCFD register */
#define GET_CRCCFD_CRCTCI(regval)            GET_BITS((regval),0,20)                      /*!< get transmitted CRC value for classical and ISO / non-ISO FD frames */
#define GET_CRCCFD_ANTM(regval)              GET_BITS((regval),24,28)                     /*!< get associated number of mailbox for transmitting the CRCTCI[20:0] value */

/* MDES0 descriptor */
#define MDES0_DLC(regval)                    (BITS(16,19) & ((uint32_t)(regval) << 16U))  /*!< write value to MDES0 descriptor DLC bit field */

#define GET_MDES0_DLC(regval)                GET_BITS((regval),16,19)                     /*!< get MDES0 descriptor DLC bit field */

#define MDES0_CODE(regval)                   (((uint32_t)(regval) << 24U) & CAN_MDES0_CODE)
#define CAN_MB_RX_STATUS_INACTIVE            (0U)                                         /*!< mailbox receive status inactive */
#define CAN_MB_RX_STATUS_FULL                (2U)                                         /*!< mailbox receive status full */
#define CAN_MB_RX_STATUS_EMPTY               (4U)                                         /*!< mailbox receive status empty */
#define CAN_MB_RX_STATUS_OVERRUN             (6U)                                         /*!< mailbox receive status overrun */
#define CAN_MB_RX_STATUS_RANSWER             (10U)                                        /*!< mailbox receive status answer */
#define CAN_MB_RX_STATUS_BUSY                (1U)                                         /*!< mailbox receive status busy */
#define CAN_MB_TX_STATUS_INACTIVE            (8U)                                         /*!< mailbox transmit status inactive */
#define CAN_MB_TX_STATUS_ABORT               (9U)                                         /*!< mailbox transmit status abort */
#define CAN_MB_TX_STATUS_DATA                (12U)                                        /*!< mailbox transmit status data */

#define GET_MDES0_CODE(regval)               GET_BITS((regval),24,27)                     /*!< get MDES0 descriptor CODE bit field */

/* MDES1 descriptor */
#define GET_MDES1_ID_EXD(regval)             GET_BITS((regval),0,28)                      /*!< get MDES1 descriptor ID_STD and ID_EXD bit field */
#define MDES1_ID_EXD(regval)                 (BITS(0,28) & ((uint32_t)(regval) << 0U))    /*!< write value to MDES1 descriptor ID_STD and ID_EXD bit field */

#define GET_MDES1_ID_STD(regval)             GET_BITS((regval),18,28)                     /*!< get MDES1 descriptor ID_STD bit field */
#define MDES1_ID_STD(regval)                 (BITS(18,28) & ((uint32_t)(regval) << 18U))  /*!< write value to MDES1 descriptor ID_STD bit field */

#define MDES1_PRIO(regval)                   (BITS(29,31) & ((uint32_t)(regval) << 29U))  /*!< write value to MDES1 descriptor PRIO bit field */

/* FDES1 descriptor */
#define GET_FDES1_ID_EXD(regval)             GET_BITS((regval),0,28)                      /*!< get FDES1 descriptor ID_STD and ID_EXD bit field */
#define FDES1_ID_EXD(regval)                 (BITS(0,28) & ((uint32_t)(regval) << 0U))    /*!< write value to FDES1 descriptor ID_STD and ID_EXD bit field */

#define GET_FDES1_ID_STD(regval)             GET_BITS((regval),18,28)                     /*!< get FDES1 descriptor ID_STD bit field */
#define FDES1_ID_STD(regval)                 (BITS(18,28) & ((uint32_t)(regval) << 18U))  /*!< write value to FDES1 descriptor ID_STD bit field */

/* FDESx descriptor */
#define CAN_DATA_FRAME_ACCEPTED              ((uint32_t)0x00000000U)                      /*!< remote frames are rejected and data frames can be stored */
#define CAN_REMOTE_FRAME_ACCEPTED            ((uint32_t)0x00000001U)                      /*!< remote frames can be stored and data frames are rejected */

#define CAN_STANDARD_FRAME_ACCEPTED          ((uint32_t)0x00000000U)                      /*!< extended frames are rejected and standard frames can be stored */
#define CAN_EXTENDED_FRAME_ACCEPTED          ((uint32_t)0x00000001U)                      /*!< extended frames can be stored and standard frames are rejected */

#define FIFO_FILTER_ID_EXD_A(val)            (((uint32_t)(val) << 0U) & CAN_FDESX_ID_EXD_A) /*!< valid extended ID filter field in format A */
#define FIFO_FILTER_ID_STD_A(val)            (((uint32_t)(val) << 18U) & CAN_FDESX_ID_STD_A)/*!< valid standard ID filter field in format A */
#define FIFO_FILTER_ID_EXD_B0(val)           (GET_BITS((val),15,28) << 16U)                 /*!< valid extended ID filter field in format B */
#define FIFO_FILTER_ID_EXD_B1(val)           (GET_BITS((val),15,28) << 0U)                  /*!< valid extended ID filter field in format B */
#define FIFO_FILTER_ID_STD_B0(val)           (GET_BITS((val),0,10) << 19U)                  /*!< valid standard ID filter field in format B */
#define FIFO_FILTER_ID_STD_B1(val)           (GET_BITS((val),0,10) << 3U)                   /*!< valid standard ID filter field in format B */
#define FIFO_FILTER_ID_EXD_C0(val)           (GET_BITS((val),21,28) << 24U)                 /*!< valid extended ID filter field in format C */
#define FIFO_FILTER_ID_EXD_C1(val)           (GET_BITS((val),21,28) << 16U)                 /*!< valid extended ID filter field in format C */
#define FIFO_FILTER_ID_EXD_C2(val)           (GET_BITS((val),21,28) << 8U)                  /*!< valid extended ID filter field in format C */
#define FIFO_FILTER_ID_EXD_C3(val)           (GET_BITS((val),21,28) << 0U)                  /*!< valid extended ID filter field in format C */
#define FIFO_FILTER_ID_STD_C0(val)           (GET_BITS((val),3,10) << 24U)                  /*!< valid standard ID filter field in format C */
#define FIFO_FILTER_ID_STD_C1(val)           (GET_BITS((val),3,10) << 16U)                  /*!< valid standard ID filter field in format C */
#define FIFO_FILTER_ID_STD_C2(val)           (GET_BITS((val),3,10) << 8U)                   /*!< valid standard ID filter field in format C */
#define FIFO_FILTER_ID_STD_C3(val)           (GET_BITS((val),3,10) << 0U)                   /*!< valid standard ID filter field in format C */

/* timeout definitions */
#define CAN_DELAY                           ((uint32_t)0x01FFFFFFU)                         /*!< state timeout */
#define CAN_MAX_MAILBOX_NUM                  32U                                            /*!< the supported maximum mailbox number */
#define CAN_MAX_RAM_SIZE                    (CAN_MAX_MAILBOX_NUM * 4U)                      /*!< the maximum RAM size used for CAN mailbox */
#define CAN_STANDARD                         BIT(31)                                        /*!< standard frames */
#define CAN_EXTENDED                         ((uint32_t)0x00000000U)                        /*!< extended frames*/

/* function declarations */
/* CAN module initialize */
/* deinitialize CAN */
void can_deinit(uint32_t can_periph);
/* reset CAN internal state machines and CAN registers */
ErrStatus can_software_reset(uint32_t can_periph);
/* CAN module initialization */
ErrStatus can_init(uint32_t can_periph, can_parameter_struct *can_parameter_init);
/* initialize CAN parameter structure with a default value */
void can_struct_para_init(can_struct_type_enum type, void *p_struct);
/* configure receive fifo/mailbox private filter */
void can_private_filter_config(uint32_t can_periph, uint32_t index, uint32_t filter_data);

/* CAN operation modes */
/* enter the corresponding mode */
ErrStatus can_operation_mode_enter(uint32_t can_periph, can_operation_modes_enum mode);
/* get operation mode */
can_operation_modes_enum can_operation_mode_get(uint32_t can_periph);
/* exit inactive mode */
ErrStatus can_inactive_mode_exit(uint32_t can_periph);
/* exit Pretended Networking mode */
ErrStatus can_pn_mode_exit(uint32_t can_periph);

/* CAN FD mode configuration */
/* can FD initialize */
void can_fd_config(uint32_t can_periph, can_fd_parameter_struct *can_fd_para_init);
/* enable bit rate switching */
void can_bitrate_switch_enable(uint32_t can_periph);
/* disable bit rate switching */
void can_bitrate_switch_disable(uint32_t can_periph);
/* get transmitter delay compensation value */
uint32_t can_tdc_get(uint32_t can_periph);
/* enable transmitter delay compensation */
void can_tdc_enable(uint32_t can_periph);
/* disable transmitter delay compensation */
void can_tdc_disable(uint32_t can_periph);

/* CAN FIFO configuration */
/* configure rx FIFO */
void can_rx_fifo_config(uint32_t can_periph, can_fifo_parameter_struct *can_fifo_para_init);
/* configure rx FIFO filter table */
void can_rx_fifo_filter_table_config(uint32_t can_periph, can_rx_fifo_id_filter_struct id_filter_table[]);
/* read rx FIFO data */
void can_rx_fifo_read(uint32_t can_periph, can_rx_fifo_struct *rx_fifo);
/* get rx FIFO filter matching number */
uint32_t can_rx_fifo_filter_matching_number_get(uint32_t can_periph);
/* clear rx FIFO */
void can_rx_fifo_clear(uint32_t can_periph);

/* CAN mailbox operation */
/* get mailbox RAM address */
uint32_t *can_ram_address_get(uint32_t can_periph, uint32_t index);
/* configure mailbox */
void can_mailbox_config(uint32_t can_periph, uint32_t index, can_mailbox_descriptor_struct *mdpara);
/* abort mailbox transmit */
void can_mailbox_transmit_abort(uint32_t can_periph, uint32_t index);
/* inactive transmit mailbox */
void can_mailbox_transmit_inactive(uint32_t can_periph, uint32_t index);
/* read receive mailbox data */
ErrStatus can_mailbox_receive_data_read(uint32_t can_periph, uint32_t index, can_mailbox_descriptor_struct *mdpara);
/* lock the receive mailbox */
void can_mailbox_receive_lock(uint32_t can_periph, uint32_t index);
/* unlock the receive mailbox */
void can_mailbox_receive_unlock(uint32_t can_periph);
/* inactive the receive mailbox */
void can_mailbox_receive_inactive(uint32_t can_periph, uint32_t index);
/* get mailbox code value */
uint32_t can_mailbox_code_get(uint32_t can_periph, uint32_t index);

/* errors & CRC */
/* configure error counter */
void can_error_counter_config(uint32_t can_periph, can_error_counter_struct *errcnt_struct);
/* get error count */
void can_error_counter_get(uint32_t can_periph, can_error_counter_struct *errcnt_struct);
/* get error state indicator */
can_error_state_enum can_error_state_get(uint32_t can_periph);
/* get mailbox CRC value */
void can_crc_get(uint32_t can_periph, can_crc_struct *crc_struct);

/* Pretended Networking mode configuration */
/* configure Pretended Networking mode parameter */
void can_pn_mode_config(uint32_t can_periph, can_pn_mode_config_struct *pnmod_config);
/* configure pn mode filter */
void can_pn_mode_filter_config(uint32_t can_periph, can_pn_mode_filter_struct *expect, can_pn_mode_filter_struct *filter);
/* get matching message counter of Pretended Networking mode */
int32_t can_pn_mode_num_of_match_get(uint32_t can_periph);
/* get matching message */
void can_pn_mode_data_read(uint32_t can_periph, uint32_t index, can_mailbox_descriptor_struct *mdpara);

/* others */
/* enable self reception */
void can_self_reception_enable(uint32_t can_periph);
/* disable self reception */
void can_self_reception_disable(uint32_t can_periph);
/* enable transmit abort */
void can_transmit_abort_enable(uint32_t can_periph);
/* disable transmit abort */
void can_transmit_abort_disable(uint32_t can_periph);
/* enable auto bus off recovery mode */
void can_auto_busoff_recovery_enable(uint32_t can_periph);
/* disable auto bus off recovery mode */
void can_auto_busoff_recovery_disable(uint32_t can_periph);
/* enable time sync mode */
void can_time_sync_enable(uint32_t can_periph);
/* disable time sync mode */
void can_time_sync_disable(uint32_t can_periph);
/* enable edge filter mode */
void can_edge_filter_mode_enable(uint32_t can_periph);
/* disable edge filter mode */
void can_edge_filter_mode_disable(uint32_t can_periph);
/* enable protocol exception detection mode */
void can_ped_mode_enable(uint32_t can_periph);
/* disable protocol exception detection mode */
void can_ped_mode_disable(uint32_t can_periph);
/* configure arbitration delay bits */
void can_arbitration_delay_bits_config(uint32_t can_periph, uint32_t delay_bits);
/* configure bit sampling mode */
void can_bsp_mode_config(uint32_t can_periph, uint32_t sampling_mode);

/* CAN interrupt and flag */
/* get CAN flag */
FlagStatus can_flag_get(uint32_t can_periph, can_flag_enum flag);
/* clear CAN flag */
void can_flag_clear(uint32_t can_periph, can_flag_enum flag);
/* enable CAN interrupt */
ErrStatus can_interrupt_enable(uint32_t can_periph, can_interrupt_enum interrupt);
/* disable CAN interrupt */
ErrStatus can_interrupt_disable(uint32_t can_periph, can_interrupt_enum interrupt);
/* get CAN interrupt flag */
FlagStatus can_interrupt_flag_get(uint32_t can_periph, can_interrupt_flag_enum int_flag);
/* clear CAN interrupt flag */
void can_interrupt_flag_clear(uint32_t can_periph, can_interrupt_flag_enum int_flag);

#endif /* GD32H7XX_CAN_H */
