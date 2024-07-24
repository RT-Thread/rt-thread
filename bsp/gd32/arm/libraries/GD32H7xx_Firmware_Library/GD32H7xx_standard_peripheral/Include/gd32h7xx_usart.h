/*!
    \file    gd32h7xx_usart.h
    \brief   definitions for the USART

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

#ifndef GD32H7XX_USART_H
#define GD32H7XX_USART_H

#include "gd32h7xx.h"

/* USARTx(x=0,1,2,5), UARTx(x=3,4,6,7) definitions */
#define USART0                        (USART_BASE + 0x0000CC00U)            /*!< USART0 base address */
#define USART1                        USART_BASE                            /*!< USART1 base address */
#define USART2                        (USART_BASE + 0x00000400U)            /*!< USART2 base address */
#define UART3                         (USART_BASE + 0x00000800U)            /*!< UART3 base address */
#define UART4                         (USART_BASE + 0x00000C00U)            /*!< UART4 base address */
#define USART5                        (USART_BASE + 0x0000D000U)            /*!< USART5 base address */
#define UART6                         (USART_BASE + 0x00003400U)            /*!< UART6 base address */
#define UART7                         (USART_BASE + 0x00003800U)            /*!< UART7 base address */

/* registers definitions */
#define USART_CTL0(usartx)            REG32((usartx) + 0x00000000U)         /*!< USART control register 0 */
#define USART_CTL1(usartx)            REG32((usartx) + 0x00000004U)         /*!< USART control register 1 */
#define USART_CTL2(usartx)            REG32((usartx) + 0x00000008U)         /*!< USART control register 2 */
#define USART_BAUD(usartx)            REG32((usartx) + 0x0000000CU)         /*!< USART baud rate generator register */
#define USART_GP(usartx)              REG32((usartx) + 0x00000010U)         /*!< USART prescaler and guard time configuration register */
#define USART_RT(usartx)              REG32((usartx) + 0x00000014U)         /*!< USART receiver timeout register */
#define USART_CMD(usartx)             REG32((usartx) + 0x00000018U)         /*!< USART command register */
#define USART_STAT(usartx)            REG32((usartx) + 0x0000001CU)         /*!< USART status register */
#define USART_INTC(usartx)            REG32((usartx) + 0x00000020U)         /*!< USART interrupt status clear register */
#define USART_RDATA(usartx)           REG32((usartx) + 0x00000024U)         /*!< USART receive data register */
#define USART_TDATA(usartx)           REG32((usartx) + 0x00000028U)         /*!< USART transmit data register */
#define USART_CHC(usartx)             REG32((usartx) + 0x000000C0U)         /*!< USART coherence control register */
#define USART_FCS(usartx)             REG32((usartx) + 0x000000D0U)         /*!< USART FIFO control and status register */

/* bits definitions */
/* USARTx_CTL0 */
#define USART_CTL0_UEN                BIT(0)                                /*!< enable USART */
#define USART_CTL0_UESM               BIT(1)                                /*!< enable USART in deep-sleep mode */
#define USART_CTL0_REN                BIT(2)                                /*!< enable receiver */
#define USART_CTL0_TEN                BIT(3)                                /*!< enable transmitter */
#define USART_CTL0_IDLEIE             BIT(4)                                /*!< enable idle line detected interrupt */
#define USART_CTL0_RBNEIE             BIT(5)                                /*!< enable read data buffer not empty interrupt and overrun error interrupt (when FIFO is disabled) */
#define USART_CTL0_RFNEIE             BIT(5)                                /*!< enable receive FIFO not empty interrupt and overrun error interrupt (when FIFO is enabled) */
#define USART_CTL0_TCIE               BIT(6)                                /*!< enable transmission complete interrupt */
#define USART_CTL0_TBEIE              BIT(7)                                /*!< enable transmitter register empty interrupt (when FIFO is disabled) */
#define USART_CTL0_TFNFIE             BIT(7)                                /*!< enable transmit FIFO not full interrupt (when FIFO is enabled) */
#define USART_CTL0_PERRIE             BIT(8)                                /*!< enable parity error interrupt */
#define USART_CTL0_PM                 BIT(9)                                /*!< parity mode */
#define USART_CTL0_PCEN               BIT(10)                               /*!< enable parity control */
#define USART_CTL0_WM                 BIT(11)                               /*!< wakeup method in mute mode */
#define USART_CTL0_WL0                BIT(12)                               /*!< word length 0 */
#define USART_CTL0_MEN                BIT(13)                               /*!< enable mute mode */
#define USART_CTL0_AMIE0              BIT(14)                               /*!< enable address 0 character match interrupt */
#define USART_CTL0_OVSMOD             BIT(15)                               /*!< oversample mode */
#define USART_CTL0_DED                BITS(16,20)                           /*!< enable driver deassertion time */
#define USART_CTL0_DEA                BITS(21,25)                           /*!< enable driver assertion time */
#define USART_CTL0_RTIE               BIT(26)                               /*!< enable receiver timeout interrupt */
#define USART_CTL0_EBIE               BIT(27)                               /*!< enable end of block interrupt */
#define USART_CTL0_WL1                BIT(28)                               /*!< word length 1 */
#define USART_CTL0_AMIE1              BIT(31)                               /*!< enable address 1 character match interrupt */

/* USARTx_CTL1 */
#define USART_CTL1_AMEN0              BIT(0)                                /*!< enable address 0 match mode */
#define USART_CTL1_ADDM0              BIT(4)                                /*!< address 0 detection mode */
#define USART_CTL1_LBLEN              BIT(5)                                /*!< LIN break frame length */
#define USART_CTL1_LBDIE              BIT(6)                                /*!< enable LIN break detection interrupt */
#define USART_CTL1_CLEN               BIT(8)                                /*!< last bit clock pulse */
#define USART_CTL1_CPH                BIT(9)                                /*!< clock phase */
#define USART_CTL1_CPL                BIT(10)                               /*!< clock polarity */
#define USART_CTL1_CKEN               BIT(11)                               /*!< enable ck pin */
#define USART_CTL1_STB                BITS(12,13)                           /*!< stop bits length */
#define USART_CTL1_LMEN               BIT(14)                               /*!< enable LIN mode */
#define USART_CTL1_STRP               BIT(15)                               /*!< swap TX/RX pins */
#define USART_CTL1_RINV               BIT(16)                               /*!< RX pin level inversion */
#define USART_CTL1_TINV               BIT(17)                               /*!< TX pin level inversion */
#define USART_CTL1_DINV               BIT(18)                               /*!< data bit level inversion */
#define USART_CTL1_MSBF               BIT(19)                               /*!< most significant bit first */
#define USART_CTL1_RTEN               BIT(23)                               /*!< enable receiver timeout */
#define USART_CTL1_ADDR0              BITS(24,31)                           /*!< address 0 of the USART terminal */

/* USARTx_CTL2 */
#define USART_CTL2_ERRIE              BIT(0)                                /*!< enable error interrupt in multibuffer communication */
#define USART_CTL2_IREN               BIT(1)                                /*!< enable IrDA mode */
#define USART_CTL2_IRLP               BIT(2)                                /*!< IrDA low-power */
#define USART_CTL2_HDEN               BIT(3)                                /*!< enable half-duplex */
#define USART_CTL2_NKEN               BIT(4)                                /*!< enable NACK in smartcard mode */
#define USART_CTL2_SCEN               BIT(5)                                /*!< enable smartcard mode */
#define USART_CTL2_DENR               BIT(6)                                /*!< enable DMA for reception */
#define USART_CTL2_DENT               BIT(7)                                /*!< enable DMA for transmission */
#define USART_CTL2_RTSEN              BIT(8)                                /*!< enable RTS */
#define USART_CTL2_CTSEN              BIT(9)                                /*!< enable CTS */
#define USART_CTL2_CTSIE              BIT(10)                               /*!< enable CTS interrupt */
#define USART_CTL2_OSB                BIT(11)                               /*!< one sample bit mode */
#define USART_CTL2_OVRD               BIT(12)                               /*!< disable overrun */
#define USART_CTL2_DDRE               BIT(13)                               /*!< disable DMA on reception error */
#define USART_CTL2_DEM                BIT(14)                               /*!< enable driver mode */
#define USART_CTL2_DEP                BIT(15)                               /*!< enable driver polarity mode */
#define USART_CTL2_AMEN1              BIT(16)                               /*!< enable address 1 match mode */
#define USART_CTL2_SCRTNUM            BITS(17,19)                           /*!< smartcard auto-retry number */
#define USART_CTL2_WUM                BITS(20,21)                           /*!< wakeup mode from deep-sleep mode */
#define USART_CTL2_WUIE               BIT(22)                               /*!< enable wakeup from deep-sleep mode interrupt */
#define USART_CTL2_ADDM1              BIT(23)                               /*!< address 1 detection mode */
#define USART_CTL2_ADDR1              BITS(24,31)                           /*!< address 1 of the USART terminal */

/* USARTx_BAUD */
#define USART_BAUD_FRADIV             BITS(0,3)                             /*!< fraction of baud-rate divider */
#define USART_BAUD_INTDIV             BITS(4,15)                            /*!< integer of baud-rate divider */

/* USARTx_GP */
#define USART_GP_PSC                  BITS(0,7)                             /*!< prescaler value for dividing the system clock */
#define USART_GP_GUAT                 BITS(8,15)                            /*!< guard time value in smartcard mode */

/* USARTx_RT */
#define USART_RT_RT                   BITS(0,23)                            /*!< receiver timeout threshold */
#define USART_RT_BL                   BITS(24,31)                           /*!< block length */

/* USARTx_CMD */
#define USART_CMD_SBKCMD              BIT(1)                                /*!< send break command */
#define USART_CMD_MMCMD               BIT(2)                                /*!< mute mode command */
#define USART_CMD_RXFCMD              BIT(3)                                /*!< receive data flush command */
#define USART_CMD_TXFCMD              BIT(4)                                /*!< transmit data flush request */

/* USARTx_STAT */
#define USART_STAT_PERR               BIT(0)                                /*!< parity error flag */
#define USART_STAT_FERR               BIT(1)                                /*!< frame error flag */
#define USART_STAT_NERR               BIT(2)                                /*!< noise error flag */
#define USART_STAT_ORERR              BIT(3)                                /*!< overrun error */
#define USART_STAT_IDLEF              BIT(4)                                /*!< idle line detected flag */
#define USART_STAT_RBNE               BIT(5)                                /*!< read data buffer not empty(when FIFO is disabled) */
#define USART_STAT_RFNE               BIT(5)                                /*!< receive FIFO not empty(when FIFO is enabled) */
#define USART_STAT_TC                 BIT(6)                                /*!< transmission completed */
#define USART_STAT_TBE                BIT(7)                                /*!< transmit data register empty(when FIFO is disabled) */
#define USART_STAT_TFNF               BIT(7)                                /*!< transmit FIFO not full(when FIFO is enabled) */
#define USART_STAT_LBDF               BIT(8)                                /*!< LIN break detected flag */
#define USART_STAT_CTSF               BIT(9)                                /*!< CTS change flag */
#define USART_STAT_CTS                BIT(10)                               /*!< CTS level */
#define USART_STAT_RTF                BIT(11)                               /*!< receiver timeout flag */
#define USART_STAT_EBF                BIT(12)                               /*!< end of block flag */
#define USART_STAT_AMF1               BIT(13)                               /*!< address 1 character match flag */
#define USART_STAT_BSY                BIT(16)                               /*!< busy flag */
#define USART_STAT_AMF0               BIT(17)                               /*!< address 0 character match flag */
#define USART_STAT_SBF                BIT(18)                               /*!< send break flag */
#define USART_STAT_RWU                BIT(19)                               /*!< receiver wakeup from mute mode */
#define USART_STAT_WUF                BIT(20)                               /*!< wakeup from deep-sleep mode flag */
#define USART_STAT_TEA                BIT(21)                               /*!< transmit enable acknowledge flag */
#define USART_STAT_REA                BIT(22)                               /*!< receive enable acknowledge flag */

/* USARTx_INTC */
#define USART_INTC_PEC                BIT(0)                                /*!< clear parity error */
#define USART_INTC_FEC                BIT(1)                                /*!< clear frame error flag */
#define USART_INTC_NEC                BIT(2)                                /*!< clear noise detected */
#define USART_INTC_OREC               BIT(3)                                /*!< clear overrun error */
#define USART_INTC_IDLEC              BIT(4)                                /*!< clear idle line detected */
#define USART_INTC_TCC                BIT(6)                                /*!< clear transmission complete */
#define USART_INTC_LBDC               BIT(8)                                /*!< clear LIN break detected */
#define USART_INTC_CTSC               BIT(9)                                /*!< clear CTS change */
#define USART_INTC_RTC                BIT(11)                               /*!< clear receiver timeout */
#define USART_INTC_EBC                BIT(12)                               /*!< clear end of timeout */
#define USART_INTC_AMC1               BIT(16)                               /*!< clear address 1 character match */
#define USART_INTC_AMC0               BIT(17)                               /*!< clear address 0 character match */
#define USART_INTC_WUC                BIT(20)                               /*!< clear wakeup from deep-sleep mode */

/* USARTx_RDATA */
#define USART_RDATA_RDATA             BITS(0,9)                             /*!< receive data value */

/* USARTx_TDATA */
#define USART_TDATA_TDATA             BITS(0,9)                             /*!< transmit data value */

/* USARTx_CHC */
#define USART_CHC_HCM                 BIT(0)                                /*!< hardware flow control coherence mode */
#define USART_CHC_EPERR               BIT(8)                                /*!< early parity error flag */

/* USARTx_FCS */
#define USART_FCS_ELNACK              BIT(0)                                 /*!< early NACK when smartcard mode is selected */
#define USART_FCS_RFCNT3_4            BITS(1,2)                              /*!< receive FIFO counter number RFCNT[4:3] */
#define USART_FCS_RFT                 BIT(4)                                 /*!< receive FIFO threshold flag */
#define USART_FCS_TFT                 BIT(5)                                 /*!< transmit FIFO threshold flag */
#define USART_FCS_TFE                 BIT(6)                                 /*!< transmit FIFO empty flag */
#define USART_FCS_TFF                 BIT(7)                                 /*!< transmit FIFO full flag */
#define USART_FCS_FEN                 BIT(8)                                 /*!< enable FIFO */
#define USART_FCS_RFFIE               BIT(9)                                 /*!< enable receive FIFO full interrupt */
#define USART_FCS_RFE                 BIT(10)                                /*!< receive FIFO empty flag */
#define USART_FCS_RFF                 BIT(11)                                /*!< receive FIFO full flag */
#define USART_FCS_RFCNT0_2            BITS(12,14)                            /*!< receive FIFO counter number RFCNT[2:0] */
#define USART_FCS_RFFIF               BIT(15)                                /*!< receive FIFO full interrupt flag */
#define USART_FCS_RFTCFG              BITS(16,18)                            /*!< receive FIFO threshold configuration */
#define USART_FCS_TFTCFG              BITS(19,21)                            /*!< transmit FIFO threshold configuration */
#define USART_FCS_RFTIF               BIT(22)                                /*!< receive FIFO threshold interrupt flag */
#define USART_FCS_TFEIF               BIT(24)                                /*!< transmit FIFO empty interrupt flag */
#define USART_FCS_TFTIF               BIT(25)                                /*!< transmit FIFO threshold interrupt flag */
#define USART_FCS_TFEC                BIT(26)                                /*!< clear transmit FIFO empty flag */
#define USART_FCS_RFTIE               BIT(27)                                /*!< enable receive FIFO threshold interrupt */
#define USART_FCS_TFTIE               BIT(29)                                /*!< enable transmit FIFO threshold interrupt */
#define USART_FCS_TFEIE               BIT(31)                                /*!< enable transmit FIFO empty interrupt */

/* constants definitions */
/* define the USART bit position and its register index offset */
#define USART_REGIDX_BIT(regidx, bitpos)     (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define USART_REG_VAL(usartx, offset)        (REG32((usartx) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define USART_BIT_POS(val)                   ((uint32_t)(val) & 0x0000001FU)
#define USART_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                              | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define USART_REG_VAL2(usartx, offset)       (REG32((usartx) + ((uint32_t)(offset) >> 22)))
#define USART_BIT_POS2(val)                  (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define USART_CTL0_REG_OFFSET                ((uint32_t)0x00000000U)        /*!< CTL0 register offset */
#define USART_CTL1_REG_OFFSET                ((uint32_t)0x00000004U)        /*!< CTL1 register offset */
#define USART_CTL2_REG_OFFSET                ((uint32_t)0x00000008U)        /*!< CTL2 register offset */
#define USART_STAT_REG_OFFSET                ((uint32_t)0x0000001CU)        /*!< STAT register offset */
#define USART_CHC_REG_OFFSET                 ((uint32_t)0x000000C0U)        /*!< CHC register offset */
#define USART_FCS_REG_OFFSET                 ((uint32_t)0x000000D0U)        /*!< FCS register offset */

/* USART flags */
typedef enum{
    /* flags in STAT register */
    USART_FLAG_REA = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 22U),          /*!< receive enable acknowledge flag */
    USART_FLAG_TEA = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 21U),          /*!< transmit enable acknowledge flag */
    USART_FLAG_WU = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 20U),           /*!< wakeup from Deep-sleep mode flag */
    USART_FLAG_RWU = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 19U),          /*!< receiver wakeup from mute mode */
    USART_FLAG_SB = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 18U),           /*!< send break flag */
    USART_FLAG_AM0 = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 17U),          /*!< ADDR0 match flag */
    USART_FLAG_BSY = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 16U),          /*!< busy flag */
    USART_FLAG_AM1 = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 13U),          /*!< ADDR1 match flag */
    USART_FLAG_EB = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 12U),           /*!< end of block flag */
    USART_FLAG_RT = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 11U),           /*!< receiver timeout flag */
    USART_FLAG_CTS = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 10U),          /*!< CTS level */
    USART_FLAG_CTSF = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 9U),          /*!< CTS change flag */
    USART_FLAG_LBD = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 8U),           /*!< LIN break detected flag */
    USART_FLAG_TBE = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 7U),           /*!< transmit data buffer empty(when FIFO is disabled) */
    USART_FLAG_TFNF = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 7U),          /*!< transmit FIFO not full(when FIFO is enabled) */
    USART_FLAG_TC = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 6U),            /*!< transmission complete */
    USART_FLAG_RBNE = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 5U),          /*!< read data buffer not empty(when FIFO is disabled) */
    USART_FLAG_RFNE = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 5U),          /*!< receive FIFO not empty(when FIFO is enabled) */
    USART_FLAG_IDLE = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 4U),          /*!< IDLE line detected flag */
    USART_FLAG_ORERR = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 3U),         /*!< overrun error */
    USART_FLAG_NERR = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 2U),          /*!< noise error flag */
    USART_FLAG_FERR = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 1U),          /*!< frame error flag */
    USART_FLAG_PERR = USART_REGIDX_BIT(USART_STAT_REG_OFFSET, 0U),          /*!< parity error flag */
    /* flags in CHC register */
    USART_FLAG_EPERR = USART_REGIDX_BIT(USART_CHC_REG_OFFSET, 8U),          /*!< early parity error flag */
    /* flags in FCS register */
    USART_FLAG_RFF = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 11U),           /*!< receive FIFO full flag */
    USART_FLAG_RFE = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 10U),           /*!< receive FIFO empty flag */
    USART_FLAG_TFF = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 7U),            /*!< transmit FIFO full flag */
    USART_FLAG_TFE = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 6U),            /*!< transmit FIFO empty flag */
    USART_FLAG_TFT = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 5U),            /*!< transmit FIFO threshold reach flag */
    USART_FLAG_RFT = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 4U)             /*!< receive FIFO threshold reach flag */
}usart_flag_enum;

/* USART interrupt flags */
typedef enum
{
    /* interrupt flags in CTL0 register */
    USART_INT_FLAG_AM1 = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 31U, USART_STAT_REG_OFFSET, 13U),      /*!< address 1 match interrupt and flag */
    USART_INT_FLAG_EB = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 27U, USART_STAT_REG_OFFSET, 12U),       /*!< end of block interrupt and flag */
    USART_INT_FLAG_RT = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 26U, USART_STAT_REG_OFFSET, 11U),       /*!< receiver timeout interrupt and flag */
    USART_INT_FLAG_AM0 = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 14U, USART_STAT_REG_OFFSET, 17U),      /*!< address 0 match interrupt and flag */
    USART_INT_FLAG_PERR = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 8U, USART_STAT_REG_OFFSET, 0U),       /*!< parity error interrupt and flag */
    USART_INT_FLAG_TBE = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 7U, USART_STAT_REG_OFFSET, 7U),        /*!< transmitter buffer empty interrupt and flag(when FIFO is disabled) */
    USART_INT_FLAG_TFNF = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 7U, USART_STAT_REG_OFFSET, 7U),       /*!< transmit FIFO not full interrupt and flag(when FIFO is enabled) */
    USART_INT_FLAG_TC = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 6U, USART_STAT_REG_OFFSET, 6U),         /*!< transmission complete interrupt and flag */
    USART_INT_FLAG_RBNE = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 5U, USART_STAT_REG_OFFSET, 5U),       /*!< read data buffer not empty interrupt and flag(when FIFO is disabled) */
    USART_INT_FLAG_RFNE = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 5U, USART_STAT_REG_OFFSET, 5U),       /*!< receive FIFO not empty interrupt and flag(when FIFO is enabled) */
    USART_INT_FLAG_RBNE_ORERR = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 5U, USART_STAT_REG_OFFSET, 3U), /*!< read data buffer not empty interrupt and overrun error flag(when FIFO is disabled) */
    USART_INT_FLAG_RFNE_ORERR = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 5U, USART_STAT_REG_OFFSET, 3U), /*!< receive FIFO not empty interrupt and overrun error flag(when FIFO is enabled) */
    USART_INT_FLAG_IDLE = USART_REGIDX_BIT2(USART_CTL0_REG_OFFSET, 4U, USART_STAT_REG_OFFSET, 4U),       /*!< IDLE line detected interrupt and flag */
    /* interrupt flags in CTL1 register */
    USART_INT_FLAG_LBD = USART_REGIDX_BIT2(USART_CTL1_REG_OFFSET, 6U, USART_STAT_REG_OFFSET, 8U),        /*!< LIN break detected interrupt and flag */
    /* interrupt flags in CTL2 register */
    USART_INT_FLAG_WU = USART_REGIDX_BIT2(USART_CTL2_REG_OFFSET, 22U, USART_STAT_REG_OFFSET, 20U),       /*!< wakeup from deep-sleep mode interrupt and flag */
    USART_INT_FLAG_CTS = USART_REGIDX_BIT2(USART_CTL2_REG_OFFSET, 10U, USART_STAT_REG_OFFSET, 9U),       /*!< CTS interrupt and flag */
    USART_INT_FLAG_ERR_NERR = USART_REGIDX_BIT2(USART_CTL2_REG_OFFSET, 0U, USART_STAT_REG_OFFSET, 2U),   /*!< error interrupt and noise error flag */
    USART_INT_FLAG_ERR_ORERR = USART_REGIDX_BIT2(USART_CTL2_REG_OFFSET, 0U, USART_STAT_REG_OFFSET, 3U),  /*!< error interrupt and overrun error */
    USART_INT_FLAG_ERR_FERR = USART_REGIDX_BIT2(USART_CTL2_REG_OFFSET, 0U, USART_STAT_REG_OFFSET, 1U),   /*!< error interrupt and frame error flag */
    /* interrupt flags in FCS register */
    USART_INT_FLAG_TFT = USART_REGIDX_BIT2(USART_FCS_REG_OFFSET, 29U, USART_FCS_REG_OFFSET, 25U),        /*!< transmit FIFO threshold reach interrupt and flag */
    USART_INT_FLAG_TFE = USART_REGIDX_BIT2(USART_FCS_REG_OFFSET, 31U, USART_FCS_REG_OFFSET, 24U),        /*!< transmit FIFO empty interrupt and flag */
    USART_INT_FLAG_RFT = USART_REGIDX_BIT2(USART_FCS_REG_OFFSET, 27U, USART_FCS_REG_OFFSET, 22U),        /*!< receive FIFO threshold reach interrupt and flag */
    USART_INT_FLAG_RFF = USART_REGIDX_BIT2(USART_FCS_REG_OFFSET, 9U, USART_FCS_REG_OFFSET, 15U)          /*!< receive FIFO full interrupt and flag */
}usart_interrupt_flag_enum;

/* enable or disable USART interrupt */
typedef enum
{
    /* interrupt in CTL0 register */
    USART_INT_AM1 = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 31U),          /*!< address 1 match interrupt */
    USART_INT_EB = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 27U),           /*!< end of block interrupt */
    USART_INT_RT = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 26U),           /*!< receiver timeout interrupt */
    USART_INT_AM0 = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 14U),          /*!< address 0 match interrupt */
    USART_INT_PERR = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 8U),          /*!< parity error interrupt */
    USART_INT_TBE = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 7U),           /*!< transmitter buffer empty interrupt(when FIFO is disabled) */
    USART_INT_TFNF = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 7U),          /*!< transmit FIFO not full interrupt(when FIFO is enabled) */
    USART_INT_TC = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 6U),            /*!< transmission complete interrupt */
    USART_INT_RBNE = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 5U),          /*!< read data buffer not empty interrupt and overrun error interrupt(when FIFO is disabled) */
    USART_INT_RFNE = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 5U),          /*!< receive FIFO not empty interrupt and overrun error interrupt(when FIFO is enabled) */
    USART_INT_IDLE = USART_REGIDX_BIT(USART_CTL0_REG_OFFSET, 4U),          /*!< IDLE line detected interrupt */
    /* interrupt in CTL1 register */
    USART_INT_LBD = USART_REGIDX_BIT(USART_CTL1_REG_OFFSET, 6U),           /*!< LIN break detected interrupt */
    /* interrupt in CTL2 register */
    USART_INT_WU = USART_REGIDX_BIT(USART_CTL2_REG_OFFSET, 22U),           /*!< wakeup from deep-sleep mode interrupt */
    USART_INT_CTS = USART_REGIDX_BIT(USART_CTL2_REG_OFFSET, 10U),          /*!< CTS interrupt */
    USART_INT_ERR = USART_REGIDX_BIT(USART_CTL2_REG_OFFSET, 0U),           /*!< error interrupt */
    /* interrupt in FCS register */
    USART_INT_TFE = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 31U),           /*!< transmit FIFO empty interrupt */
    USART_INT_TFT = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 29U),           /*!< transmit FIFO threshold interrupt */
    USART_INT_RFT = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 27U),           /*!< receive FIFO threshold interrupt */
    USART_INT_RFF = USART_REGIDX_BIT(USART_FCS_REG_OFFSET, 9U)             /*!< receive FIFO full interrupt */
}usart_interrupt_enum;

/* configure USART invert */
typedef enum {
    /* data bit level inversion */
    USART_DINV_ENABLE,                                                     /*!< data bit level inversion */
    USART_DINV_DISABLE,                                                    /*!< data bit level not inversion */
    /* TX pin level inversion */
    USART_TXPIN_ENABLE,                                                    /*!< TX pin level inversion */
    USART_TXPIN_DISABLE,                                                   /*!< TX pin level not inversion */
    /* RX pin level inversion */
    USART_RXPIN_ENABLE,                                                    /*!< RX pin level inversion */
    USART_RXPIN_DISABLE,                                                   /*!< RX pin level not inversion */
    /* swap TX/RX pins */
    USART_SWAP_ENABLE,                                                     /*!< swap TX/RX pins */
    USART_SWAP_DISABLE                                                     /*!< not swap TX/RX pins */
}usart_invert_enum;

/* configure USART receiver */
#define CTL0_REN(regval)              (BIT(2) & ((uint32_t)(regval) << 2))
#define USART_RECEIVE_ENABLE          CTL0_REN(1)                          /*!< enable receiver */
#define USART_RECEIVE_DISABLE         CTL0_REN(0)                          /*!< disable receiver */

/* configure USART transmitter */
#define CTL0_TEN(regval)              (BIT(3) & ((uint32_t)(regval) << 3))
#define USART_TRANSMIT_ENABLE         CTL0_TEN(1)                          /*!< enable transmitter */
#define USART_TRANSMIT_DISABLE        CTL0_TEN(0)                          /*!< disable transmitter */

/* USART parity bits definitions */
#define CTL0_PM(regval)               (BITS(9,10) & ((uint32_t)(regval) << 9))
#define USART_PM_NONE                 CTL0_PM(0)                           /*!< no parity */
#define USART_PM_EVEN                 CTL0_PM(2)                           /*!< even parity */
#define USART_PM_ODD                  CTL0_PM(3)                           /*!< odd parity */

/* USART wakeup method in mute mode */
#define CTL0_WM(regval)               (BIT(11) & ((uint32_t)(regval) << 11))
#define USART_WM_IDLE                 CTL0_WM(0)                           /*!< idle line */
#define USART_WM_ADDR                 CTL0_WM(1)                           /*!< address match */

/* USART word length definitions */
#define CTL0_WL(regval1, regval2)     ((BIT(28) & ((uint32_t)(regval1) << 28)) | (BIT(12) & ((uint32_t)(regval2) << 12)))
#define USART_WL_8BIT                 CTL0_WL(0, 0)                        /*!< 8 bits */
#define USART_WL_9BIT                 CTL0_WL(0, 1)                        /*!< 9 bits */
#define USART_WL_7BIT                 CTL0_WL(1, 0)                        /*!< 7 bits */
#define USART_WL_10BIT                CTL0_WL(1, 1)                        /*!< 10 bits */

/* USART oversample mode */
#define CTL0_OVSMOD(regval)           (BIT(15) & ((uint32_t)(regval) << 15))
#define USART_OVSMOD_8                CTL0_OVSMOD(1)                       /*!< oversampling by 8 */
#define USART_OVSMOD_16               CTL0_OVSMOD(0)                       /*!< oversampling by 16 */

/* USART LIN break frame length */
#define CTL1_LBLEN(regval)            (BIT(5) & ((uint32_t)(regval) << 5))
#define USART_LBLEN_10B               CTL1_LBLEN(0)                        /*!< 10 bits break detection */
#define USART_LBLEN_11B               CTL1_LBLEN(1)                        /*!< 11 bits break detection */

/* USART last bit clock pulse */
#define CTL1_CLEN(regval)             (BIT(8) & ((uint32_t)(regval) << 8))
#define USART_CLEN_NONE               CTL1_CLEN(0)                         /*!< clock pulse of the last data bit (MSB) is not output to the CK pin */
#define USART_CLEN_EN                 CTL1_CLEN(1)                         /*!< clock pulse of the last data bit (MSB) is output to the CK pin */

/* USART clock phase */
#define CTL1_CPH(regval)              (BIT(9) & ((uint32_t)(regval) << 9))
#define USART_CPH_1CK                 CTL1_CPH(0)                          /*!< first clock transition is the first data capture edge */
#define USART_CPH_2CK                 CTL1_CPH(1)                          /*!< second clock transition is the first data capture edge */

/* USART clock polarity */
#define CTL1_CPL(regval)              (BIT(10) & ((uint32_t)(regval) << 10))
#define USART_CPL_LOW                 CTL1_CPL(0)                          /*!< steady low value on CK pin */
#define USART_CPL_HIGH                CTL1_CPL(1)                          /*!< steady high value on CK pin */

/* USART stop bits definitions */
#define CTL1_STB(regval)              (BITS(12,13) & ((uint32_t)(regval) << 12))
#define USART_STB_1BIT                CTL1_STB(0)                          /*!< 1 bit */
#define USART_STB_0_5BIT              CTL1_STB(1)                          /*!< 0.5 bit */
#define USART_STB_2BIT                CTL1_STB(2)                          /*!< 2 bits */
#define USART_STB_1_5BIT              CTL1_STB(3)                          /*!< 1.5 bits */

/* USART data is transmitted/received with the LSB/MSB first */
#define CTL1_MSBF(regval)             (BIT(19) & ((uint32_t)(regval) << 19))
#define USART_MSBF_LSB                CTL1_MSBF(0)                         /*!< LSB first */
#define USART_MSBF_MSB                CTL1_MSBF(1)                         /*!< MSB first */

/* enable USART IrDA low-power */
#define CTL2_IRLP(regval)             (BIT(2) & ((uint32_t)(regval) << 2))
#define USART_IRLP_LOW                CTL2_IRLP(1)                         /*!< low-power */
#define USART_IRLP_NORMAL             CTL2_IRLP(0)                         /*!< normal */

/* USART DMA request for receive configure */
#define CTL2_DENR(regval)             (BIT(6) & ((uint32_t)(regval) << 6))
#define USART_RECEIVE_DMA_ENABLE      CTL2_DENR(1)                         /*!< DMA request enable for reception */
#define USART_RECEIVE_DMA_DISABLE     CTL2_DENR(0)                         /*!< DMA request disable for reception */

/* USART DMA request for transmission configure */
#define CTL2_DENT(regval)             (BIT(7) & ((uint32_t)(regval) << 7))
#define USART_TRANSMIT_DMA_ENABLE     CTL2_DENT(1)                         /*!< DMA request enable for transmission */
#define USART_TRANSMIT_DMA_DISABLE    CTL2_DENT(0)                         /*!< DMA request disable for transmission */

/* configure USART RTS hardware flow control */
#define CTL2_RTSEN(regval)            (BIT(8) & ((uint32_t)(regval) << 8))
#define USART_RTS_ENABLE              CTL2_RTSEN(1)                        /*!< RTS hardware flow control enabled */
#define USART_RTS_DISABLE             CTL2_RTSEN(0)                        /*!< RTS hardware flow control disabled */

/* configure USART CTS hardware flow control */
#define CTL2_CTSEN(regval)            (BIT(9) & ((uint32_t)(regval) << 9))
#define USART_CTS_ENABLE              CTL2_CTSEN(1)                        /*!< CTS hardware flow control enabled */
#define USART_CTS_DISABLE             CTL2_CTSEN(0)                        /*!< CTS hardware flow control disabled */

/* configure USART one sample bit method */
#define CTL2_OSB(regval)              (BIT(11) & ((uint32_t)(regval) << 11))
#define USART_OSB_1BIT                CTL2_OSB(1)                          /*!< 1 sample bit */
#define USART_OSB_3BIT                CTL2_OSB(0)                          /*!< 3 sample bits */

/* USART driver enable polarity mode */
#define CTL2_DEP(regval)              (BIT(15) & ((uint32_t)(regval) << 15))
#define USART_DEP_HIGH                CTL2_DEP(0)                          /*!< DE signal is active high */
#define USART_DEP_LOW                 CTL2_DEP(1)                          /*!< DE signal is active low */

/* USART wakeup mode from deep-sleep mode */
#define CTL2_WUM(regval)              (BITS(20,21) & ((uint32_t)(regval) << 20))
#define USART_WUM_ADDR                CTL2_WUM(0)                          /*!< WUF active on address match */
#define USART_WUM_STARTB              CTL2_WUM(2)                          /*!< WUF active on start bit */
#define USART_WUM_RBNE                CTL2_WUM(3)                          /*!< WUF active on RBNE */

/* USART address 0 detection mode */
#define CTL1_ADDM0(regval)            (BIT(4) & ((uint32_t)(regval) << 4))
#define USART_ADDM0_4BIT              CTL1_ADDM0(0)                        /*!< 4-bit address detection */
#define USART_ADDM0_FULLBIT           CTL1_ADDM0(1)                        /*!< full-bit address detection */

/* USART address 1 detection mode */
#define CTL2_ADDM1(regval)            (BIT(23) & ((uint32_t)(regval) << 23))
#define USART_ADDM1_4BIT              CTL2_ADDM1(0)                        /*!< 4-bit address detection */
#define USART_ADDM1_FULLBIT           CTL2_ADDM1(1)                        /*!< full-bit address detection */

/* USART hardware flow control coherence mode */
#define CHC_HCM(regval)               (BIT(0) & ((uint32_t)(regval) << 0))
#define USART_HCM_NONE                CHC_HCM(0)                           /*!< nRTS signal equals to the rxne status register */
#define USART_HCM_EN                  CHC_HCM(1)                           /*!< nRTS signal is set when the last data bit has been sampled */

/* configure USART transmit FIFO threshold */
#define FCS_TFTCFG(regval)            (BITS(19,21) & ((uint32_t)(regval) << 19))
#define USART_TFTCFG_THRESHOLD_1_8    FCS_TFTCFG(0)                       /*!< transmit FIFO reaches 1/8 of its depth */
#define USART_TFTCFG_THRESHOLD_1_4    FCS_TFTCFG(1)                       /*!< transmit FIFO reaches 1/4 of its depth */
#define USART_TFTCFG_THRESHOLD_1_2    FCS_TFTCFG(2)                       /*!< transmit FIFO reaches 1/2 of its depth */
#define USART_TFTCFG_THRESHOLD_3_4    FCS_TFTCFG(3)                       /*!< transmit FIFO reaches 3/4 of its depth */
#define USART_TFTCFG_THRESHOLD_7_8    FCS_TFTCFG(4)                       /*!< transmit FIFO reaches 7/8 of its depth */
#define USART_TFTCFG_THRESHOLD_EMPTY  FCS_TFTCFG(5)                       /*!< transmit FIFO becomes empty */

/* configure USART receive FIFO threshold */
#define FCS_RFTCFG(regval)            (BITS(16,18) & ((uint32_t)(regval) << 16))
#define USART_RFTCFG_THRESHOLD_1_8    FCS_RFTCFG(0)                       /*!< receive FIFO reaches 1/8 of its depth */
#define USART_RFTCFG_THRESHOLD_1_4    FCS_RFTCFG(1)                       /*!< receive FIFO reaches 1/4 of its depth */
#define USART_RFTCFG_THRESHOLD_1_2    FCS_RFTCFG(2)                       /*!< receive FIFO reaches 1/2 of its depth */
#define USART_RFTCFG_THRESHOLD_3_4    FCS_RFTCFG(3)                       /*!< receive FIFO reaches 3/4 of its depth */
#define USART_RFTCFG_THRESHOLD_7_8    FCS_RFTCFG(4)                       /*!< receive FIFO reaches 7/8 of its depth */
#define USART_RFTCFG_THRESHOLD_FULL   FCS_RFTCFG(5)                       /*!< receive FIFO becomes full */

/* function declarations */
/* initialization functions */
/* reset USART */
void usart_deinit(uint32_t usart_periph);
/* configure USART baud rate value */
void usart_baudrate_set(uint32_t usart_periph, uint32_t baudval);
/* configure USART parity function */
void usart_parity_config(uint32_t usart_periph, uint32_t paritycfg);
/* configure USART word length */
void usart_word_length_set(uint32_t usart_periph, uint32_t wlen);
/* configure USART stop bit length */
void usart_stop_bit_set(uint32_t usart_periph, uint32_t stblen);
/* enable USART */
void usart_enable(uint32_t usart_periph);
/* disable USART */
void usart_disable(uint32_t usart_periph);
/* configure USART transmitter */
void usart_transmit_config(uint32_t usart_periph, uint32_t txconfig);
/* configure USART receiver */
void usart_receive_config(uint32_t usart_periph, uint32_t rxconfig);

/* USART normal mode communication */
/* data is transmitted/received with the LSB/MSB first */
void usart_data_first_config(uint32_t usart_periph, uint32_t msbf);
/* USART inverted configure */
void usart_invert_config(uint32_t usart_periph, usart_invert_enum invertpara);
/* enable the USART overrun function */
void usart_overrun_enable(uint32_t usart_periph);
/* disable the USART overrun function */
void usart_overrun_disable(uint32_t usart_periph);
/* configure the USART oversample mode */
void usart_oversample_config(uint32_t usart_periph, uint32_t oversamp);
/* configure sample bit method */
void usart_sample_bit_config(uint32_t usart_periph, uint32_t osb);
/* enable receiver timeout */
void usart_receiver_timeout_enable(uint32_t usart_periph);
/* disable receiver timeout */
void usart_receiver_timeout_disable(uint32_t usart_periph);
/* configure receiver timeout threshold */
void usart_receiver_timeout_threshold_config(uint32_t usart_periph, uint32_t rtimeout);
/* USART transmit data function */
void usart_data_transmit(uint32_t usart_periph, uint16_t data);
/* USART receive data function */
uint16_t usart_data_receive(uint32_t usart_periph);
/* enable USART command */
void usart_command_enable(uint32_t usart_periph, uint32_t cmdtype);

/* multi-processor communication */
/* enable address 0 match mode */
void usart_address_0_match_mode_enable(uint32_t usart_periph);
/* disable address 0 match mode */
void usart_address_0_match_mode_disable(uint32_t usart_periph);
/* enable address 1 match mode */
void usart_address_1_match_mode_enable(uint32_t usart_periph);
/* disable address 1 match mode */
void usart_address_1_match_mode_disable(uint32_t usart_periph);
/* configure address 0 of the USART */
void usart_address_0_config(uint32_t usart_periph, uint8_t addr);
/* configure address 1 of the USART */
void usart_address_1_config(uint32_t usart_periph, uint8_t addr);
/* configure address 0 detection mode */
void usart_address_0_detection_mode_config(uint32_t usart_periph, uint32_t addmod);
/* configure address 1 detection mode */
void usart_address_1_detection_mode_config(uint32_t usart_periph, uint32_t addmod);
/* enable mute mode */
void usart_mute_mode_enable(uint32_t usart_periph);
/* disable mute mode */
void usart_mute_mode_disable(uint32_t usart_periph);
/* configure wakeup method in mute mode */
void usart_mute_mode_wakeup_config(uint32_t usart_periph, uint32_t wmethod);

/* LIN mode communication */
/* enable LIN mode */
void usart_lin_mode_enable(uint32_t usart_periph);
/* disable LIN mode */
void usart_lin_mode_disable(uint32_t usart_periph);
/* LIN break detection length */
void usart_lin_break_detection_length_config(uint32_t usart_periph, uint32_t lblen);

/* half-duplex communication */
/* enable half-duplex mode */
void usart_halfduplex_enable(uint32_t usart_periph);
/* disable half-duplex mode */
void usart_halfduplex_disable(uint32_t usart_periph);

/* synchronous communication */
/* enable clock */
void usart_clock_enable(uint32_t usart_periph);
/* disable clock */
void usart_clock_disable(uint32_t usart_periph);
/* configure USART synchronous mode parameters */
void usart_synchronous_clock_config(uint32_t usart_periph, uint32_t clen, uint32_t cph, uint32_t cpl);

/* smartcard communication */
/* configure guard time value in smartcard mode */
void usart_guard_time_config(uint32_t usart_periph, uint32_t guat);
/* enable smartcard mode */
void usart_smartcard_mode_enable(uint32_t usart_periph);
/* disable smartcard mode */
void usart_smartcard_mode_disable(uint32_t usart_periph);
/* enable NACK in smartcard mode */
void usart_smartcard_mode_nack_enable(uint32_t usart_periph);
/* disable NACK in smartcard mode */
void usart_smartcard_mode_nack_disable(uint32_t usart_periph);
/* enable early NACK in smartcard mode */
void usart_smartcard_mode_early_nack_enable(uint32_t usart_periph);
/* disable early NACK in smartcard mode */
void usart_smartcard_mode_early_nack_disable(uint32_t usart_periph);
/* configure smartcard auto-retry number */
void usart_smartcard_autoretry_config(uint32_t usart_periph, uint32_t scrtnum);
/* configure block length */
void usart_block_length_config(uint32_t usart_periph, uint32_t bl);

/* IrDA communication */
/* enable IrDA mode */
void usart_irda_mode_enable(uint32_t usart_periph);
/* disable IrDA mode */
void usart_irda_mode_disable(uint32_t usart_periph);
/* configure the peripheral clock prescaler in USART IrDA low-power or SmartCard mode */
void usart_prescaler_config(uint32_t usart_periph, uint32_t psc);
/* configure IrDA low-power */
void usart_irda_lowpower_config(uint32_t usart_periph, uint32_t irlp);

/* hardware flow communication */
/* configure hardware flow control RTS */
void usart_hardware_flow_rts_config(uint32_t usart_periph, uint32_t rtsconfig);
/* configure hardware flow control CTS */
void usart_hardware_flow_cts_config(uint32_t usart_periph, uint32_t ctsconfig);

/* coherence control */
/* configure hardware flow control coherence mode */
void usart_hardware_flow_coherence_config(uint32_t usart_periph, uint32_t hcm);

/* enable RS485 driver */
void usart_rs485_driver_enable(uint32_t usart_periph);
/* disable RS485 driver */
void usart_rs485_driver_disable(uint32_t usart_periph);
/* configure driver enable assertion time */
void usart_driver_assertime_config(uint32_t usart_periph, uint32_t deatime);
/* configure driver enable de-assertion time */
void usart_driver_deassertime_config(uint32_t usart_periph, uint32_t dedtime);
/* configure driver enable polarity mode */
void usart_depolarity_config(uint32_t usart_periph, uint32_t dep);

/* USART DMA */
/* configure USART DMA reception */
void usart_dma_receive_config(uint32_t usart_periph, uint32_t dmacmd);
/* configure USART DMA transmission */
void usart_dma_transmit_config(uint32_t usart_periph, uint32_t dmacmd);
/* disable DMA on reception error */
void usart_reception_error_dma_disable(uint32_t usart_periph);
/* enable DMA on reception error */
void usart_reception_error_dma_enable(uint32_t usart_periph);

/* enable USART to wakeup the mcu from deep-sleep mode */
void usart_wakeup_enable(uint32_t usart_periph);
/* disable USART to wakeup the mcu from deep-sleep mode */
void usart_wakeup_disable(uint32_t usart_periph);
/* configure the USART wakeup mode from deep-sleep mode */
void usart_wakeup_mode_config(uint32_t usart_periph, uint32_t wum);

/* USART FIFO */
/* enable FIFO */
void usart_fifo_enable(uint32_t usart_periph);
/* disable FIFO */
void usart_fifo_disable(uint32_t usart_periph);
/* configure transmit FIFO threshold */
void usart_transmit_fifo_threshold_config(uint32_t usart_periph, uint32_t txthreshold);
/* configure receive FIFO threshold */
void usart_receive_fifo_threshold_config(uint32_t usart_periph, uint32_t rxthreshold);
/* read receive FIFO counter number */
uint8_t usart_receive_fifo_counter_number(uint32_t usart_periph);

/* flag & interrupt functions */
/* get flag in STAT/FCS register */
FlagStatus usart_flag_get(uint32_t usart_periph, usart_flag_enum flag);
/* clear USART status */
void usart_flag_clear(uint32_t usart_periph, usart_flag_enum flag);
/* enable USART interrupt */
void usart_interrupt_enable(uint32_t usart_periph, usart_interrupt_enum interrupt);
/* disable USART interrupt */
void usart_interrupt_disable(uint32_t usart_periph, usart_interrupt_enum interrupt);
/* get USART interrupt and flag status */
FlagStatus usart_interrupt_flag_get(uint32_t usart_periph, usart_interrupt_flag_enum int_flag);
/* clear USART interrupt flag */
void usart_interrupt_flag_clear(uint32_t usart_periph, usart_interrupt_flag_enum int_flag);

#endif /* GD32H7XX_USART_H */
