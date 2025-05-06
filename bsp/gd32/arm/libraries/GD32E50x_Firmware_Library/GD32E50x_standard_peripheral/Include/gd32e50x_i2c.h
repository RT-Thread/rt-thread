/*!
    \file    gd32e50x_i2c.h
    \brief   definitions for the I2C

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef GD32E50X_I2C_H
#define GD32E50X_I2C_H

#include "gd32e50x.h"

/* I2Cx(x=0,1,2) definitions */
#define I2C0                             I2C_BASE                              /*!< I2C0 base address */
#define I2C1                             (I2C_BASE + 0x00000400U)              /*!< I2C1 base address */
#define I2C2                             (I2C_BASE + 0x00006C00U)              /*!< I2C2 base address */

/* registers definitions */
/* registers of I2Cx(x=0,1) */
#define I2C_CTL0(i2cx)                   REG32((i2cx) + 0x00000000U)           /*!< I2C control register 0 */
#define I2C_CTL1(i2cx)                   REG32((i2cx) + 0x00000004U)           /*!< I2C control register 1 */
#define I2C_SADDR0(i2cx)                 REG32((i2cx) + 0x00000008U)           /*!< I2C slave address register 0*/
#define I2C_SADDR1(i2cx)                 REG32((i2cx) + 0x0000000CU)           /*!< I2C slave address register */
#define I2C_DATA(i2cx)                   REG32((i2cx) + 0x00000010U)           /*!< I2C transfer buffer register */
#define I2C_STAT0(i2cx)                  REG32((i2cx) + 0x00000014U)           /*!< I2C transfer status register 0 */
#define I2C_STAT1(i2cx)                  REG32((i2cx) + 0x00000018U)           /*!< I2C transfer status register */
#define I2C_CKCFG(i2cx)                  REG32((i2cx) + 0x0000001CU)           /*!< I2C clock configure register */
#define I2C_RT(i2cx)                     REG32((i2cx) + 0x00000020U)           /*!< I2C rise time register */
#define I2C_SAMCS(i2cx)                  REG32((i2cx) + 0x00000080U)           /*!< I2C SAM control and status register */
#define I2C_CTL2(i2cx)                   REG32((i2cx) + 0x00000090U)           /*!< control register 2 */
#define I2C_CS(i2cx)                     REG32((i2cx) + 0x00000094U)           /*!< control and status register */
#define I2C_STATC(i2cx)                  REG32((i2cx) + 0x00000098U)           /*!< status clear register */

/* registers of I2Cx(x=2) */
#define I2C2_CTL0(i2cx)                  REG32((i2cx) + 0x00000000U)           /*!< I2C control register 0 */
#define I2C2_CTL1(i2cx)                  REG32((i2cx) + 0x00000004U)           /*!< I2C control register 1 */
#define I2C2_SADDR0(i2cx)                REG32((i2cx) + 0x00000008U)           /*!< I2C slave address register 0*/
#define I2C2_SADDR1(i2cx)                REG32((i2cx) + 0x0000000CU)           /*!< I2C slave address register 1*/
#define I2C2_TIMING(i2cx)                REG32((i2cx) + 0x00000010U)           /*!< I2C timing register */
#define I2C2_TIMEOUT(i2cx)               REG32((i2cx) + 0x00000014U)           /*!< I2C timeout register */
#define I2C2_STAT(i2cx)                  REG32((i2cx) + 0x00000018U)           /*!< I2C status register */
#define I2C2_STATC(i2cx)                 REG32((i2cx) + 0x0000001CU)           /*!< I2C status clear register */
#define I2C2_PEC(i2cx)                   REG32((i2cx) + 0x00000020U)           /*!< I2C PEC register */
#define I2C2_RDATA(i2cx)                 REG32((i2cx) + 0x00000024U)           /*!< I2C receive data register */
#define I2C2_TDATA(i2cx)                 REG32((i2cx) + 0x00000028U)           /*!< I2C transmit data register */

/* bits definitions */
/* bits definitions of I2Cx(x=0,1) */
/* I2Cx_CTL0 */
#define I2C_CTL0_I2CEN                   BIT(0)                                /*!< peripheral enable */
#define I2C_CTL0_SMBEN                   BIT(1)                                /*!< SMBus mode */
#define I2C_CTL0_SMBSEL                  BIT(3)                                /*!< SMBus type */
#define I2C_CTL0_ARPEN                   BIT(4)                                /*!< ARP enable */
#define I2C_CTL0_PECEN                   BIT(5)                                /*!< PEC enable */
#define I2C_CTL0_GCEN                    BIT(6)                                /*!< general call enable */
#define I2C_CTL0_SS                      BIT(7)                                /*!< clock stretching disable (slave mode) */
#define I2C_CTL0_START                   BIT(8)                                /*!< start generation */
#define I2C_CTL0_STOP                    BIT(9)                                /*!< stop generation */
#define I2C_CTL0_ACKEN                   BIT(10)                               /*!< acknowledge enable */
#define I2C_CTL0_POAP                    BIT(11)                               /*!< acknowledge/PEC position (for data reception) */
#define I2C_CTL0_PECTRANS                BIT(12)                               /*!< packet error checking */
#define I2C_CTL0_SALT                    BIT(13)                               /*!< SMBus alert */
#define I2C_CTL0_SRESET                  BIT(15)                               /*!< software reset */

/* I2Cx_CTL1 */
#define I2C_CTL1_I2CCLK                  BITS(0,6)                             /*!< I2CCLK[6:0] bits (peripheral clock frequency) */
#define I2C_CTL1_ERRIE                   BIT(8)                                /*!< error interrupt enable */
#define I2C_CTL1_EVIE                    BIT(9)                                /*!< event interrupt enable */
#define I2C_CTL1_BUFIE                   BIT(10)                               /*!< buffer interrupt enable */
#define I2C_CTL1_DMAON                   BIT(11)                               /*!< DMA requests enable */
#define I2C_CTL1_DMALST                  BIT(12)                               /*!< DMA last transfer */

/* I2Cx_SADDR0 */
#define I2C_SADDR0_ADDRESS0              BIT(0)                                /*!< bit 0 of a 10-bit address */
#define I2C_SADDR0_ADDRESS               BITS(1,7)                             /*!< 7-bit address or bits 7:1 of a 10-bit address */
#define I2C_SADDR0_ADDRESS_H             BITS(8,9)                             /*!< highest two bits of a 10-bit address */
#define I2C_SADDR0_ADDFORMAT             BIT(15)                               /*!< address mode for the I2C slave */

/* I2Cx_SADDR1 */
#define I2C_SADDR1_DUADEN                BIT(0)                                /*!< dual-address mode switch */
#define I2C_SADDR1_ADDRESS2              BITS(1,7)                             /*!< second I2C address for the slave in dual-address mode */

/* I2Cx_DATA */
#define I2C_DATA_TRB                     BITS(0,7)                             /*!< 8-bit data register */

/* I2Cx_STAT0 */
#define I2C_STAT0_SBSEND                 BIT(0)                                /*!< start bit (master mode) */
#define I2C_STAT0_ADDSEND                BIT(1)                                /*!< address sent (master mode)/matched (slave mode) */
#define I2C_STAT0_BTC                    BIT(2)                                /*!< byte transfer finished */
#define I2C_STAT0_ADD10SEND              BIT(3)                                /*!< 10-bit header sent (master mode) */
#define I2C_STAT0_STPDET                 BIT(4)                                /*!< stop detection (slave mode) */
#define I2C_STAT0_RBNE                   BIT(6)                                /*!< data register not empty (receivers) */
#define I2C_STAT0_TBE                    BIT(7)                                /*!< data register empty (transmitters) */
#define I2C_STAT0_BERR                   BIT(8)                                /*!< bus error */
#define I2C_STAT0_LOSTARB                BIT(9)                                /*!< arbitration lost (master mode) */
#define I2C_STAT0_AERR                   BIT(10)                               /*!< acknowledge failure */
#define I2C_STAT0_OUERR                  BIT(11)                               /*!< overrun/underrun */
#define I2C_STAT0_PECERR                 BIT(12)                               /*!< PEC error in reception */
#define I2C_STAT0_SMBTO                  BIT(14)                               /*!< timeout signal in SMBus mode */
#define I2C_STAT0_SMBALT                 BIT(15)                               /*!< SMBus alert status */

/* I2Cx_STAT1 */
#define I2C_STAT1_MASTER                 BIT(0)                                /*!< master/slave */
#define I2C_STAT1_I2CBSY                 BIT(1)                                /*!< bus busy */
#define I2C_STAT1_TR                     BIT(2)                                /*!< transmitter/receiver */
#define I2C_STAT1_RXGC                   BIT(4)                                /*!< general call address (slave mode) */
#define I2C_STAT1_DEFSMB                 BIT(5)                                /*!< SMBus device default address (slave mode) */
#define I2C_STAT1_HSTSMB                 BIT(6)                                /*!< SMBus host header (slave mode) */
#define I2C_STAT1_DUMODF                 BIT(7)                                /*!< dual flag (slave mode) */
#define I2C_STAT1_PECV                   BITS(8,15)                            /*!< packet error checking value */

/* I2Cx_CKCFG */
#define I2C_CKCFG_CLKC                   BITS(0,11)                            /*!< clock control register in fast/standard mode or fast mode plus(master mode) */
#define I2C_CKCFG_DTCY                   BIT(14)                               /*!< duty cycle of fast mode or fast mode plus */
#define I2C_CKCFG_FAST                   BIT(15)                               /*!< I2C speed selection in master mode */

/* I2Cx_RT */
#define I2C_RT_RISETIME                  BITS(0,6)                             /*!< maximum rise time in fast/standard mode or fast mode plus(master mode) */

/* I2Cx_SAMCS */
#define I2C_SAMCS_SAMEN                  BIT(0)                                /*!< SAM_V interface enable */
#define I2C_SAMCS_STOEN                  BIT(1)                                /*!< SAM_V interface timeout detect enable */
#define I2C_SAMCS_TFFIE                  BIT(4)                                /*!< txframe fall interrupt enable */
#define I2C_SAMCS_TFRIE                  BIT(5)                                /*!< txframe rise interrupt enable */
#define I2C_SAMCS_RFFIE                  BIT(6)                                /*!< rxframe fall interrupt enable */
#define I2C_SAMCS_RFRIE                  BIT(7)                                /*!< rxframe rise interrupt enable */
#define I2C_SAMCS_TXF                    BIT(8)                                /*!< level of txframe signal */
#define I2C_SAMCS_RXF                    BIT(9)                                /*!< level of rxframe signal */
#define I2C_SAMCS_TFF                    BIT(12)                               /*!< txframe fall flag */
#define I2C_SAMCS_TFR                    BIT(13)                               /*!< txframe rise flag */
#define I2C_SAMCS_RFF                    BIT(14)                               /*!< rxframe fall flag */
#define I2C_SAMCS_RFR                    BIT(15)                               /*!< rxframe rise flag */

/* I2Cx_CTL2 */
#define I2C_CTL2_FMPEN                   BIT(0)                                /*!< fast mode plus enable */
#define I2C_CTL2_SETM                    BIT(1)                                /*!< start early termination mode */
#define I2C_CTL2_TOEN                    BIT(4)                                /*!< timeout calculation disable */
#define I2C_CTL2_RADD                    BIT(8)                                /*!< record received slave address to the transfer buffer register */
#define I2C_CTL2_ADDM                    BITS(9,15)                            /*!< address bit compare select */

/* I2Cx_CS */
#define I2C_CS_STLO                      BIT(0)                                /*!< start lost occurred */
#define I2C_CS_STPSEND                   BIT(1)                                /*!< stop condition sent */
#define I2C_CS_STLOIE                    BIT(8)                                /*!< start lost interrupt enable */
#define I2C_CS_STPSENDIE                 BIT(9)                                /*!< stop condition sent interrupt enable */

/* I2Cx_STATC */
#define I2C_STATC_SBSENDC                BIT(0)                                /*!< clear SBSEND bit */
#define I2C_STATC_ADDSENDC               BIT(1)                                /*!< clear ADDSEND bit */
#define I2C_STATC_BTCC                   BIT(2)                                /*!< clear BTC bit */
#define I2C_STATC_ADD10SENDC             BIT(3)                                /*!< clear ADD10SEND bit */
#define I2C_STATC_STOPFC                 BIT(4)                                /*!< clear STPDET bit */
#define I2C_STATC_SRCEN                  BIT(15)                               /*!< Status register clear enable */

/* bits definitions of I2Cx(x=2) */
/* I2Cx_CTL0 */
#define I2C2_CTL0_I2CEN                  BIT(0)                                /*!< I2C peripheral enable */
#define I2C2_CTL0_TIE                    BIT(1)                                /*!< transmit interrupt enable */
#define I2C2_CTL0_RBNEIE                 BIT(2)                                /*!< receive interrupt enable */
#define I2C2_CTL0_ADDMIE                 BIT(3)                                /*!< address match interrupt enable in slave mode */
#define I2C2_CTL0_NACKIE                 BIT(4)                                /*!< not acknowledge received interrupt enable */
#define I2C2_CTL0_STPDETIE               BIT(5)                                /*!< stop detection interrupt enable */
#define I2C2_CTL0_TCIE                   BIT(6)                                /*!< transfer complete interrupt enable */
#define I2C2_CTL0_ERRIE                  BIT(7)                                /*!< error interrupt enable */
#define I2C2_CTL0_DNF                    BITS(8,11)                            /*!< digital noise filter */
#define I2C2_CTL0_ANOFF                  BIT(12)                               /*!< analog noise filter */
#define I2C2_CTL0_DENT                   BIT(14)                               /*!< DMA enable for transmission */
#define I2C2_CTL0_DENR                   BIT(15)                               /*!< DMA enable for reception */
#define I2C2_CTL0_SBCTL                  BIT(16)                               /*!< slave byte control */
#define I2C2_CTL0_SS                     BIT(17)                               /*!< whether to stretch SCL low when data is not ready in slave mode */
#define I2C2_CTL0_WUEN                   BIT(18)                               /*!< wakeup from Deep-sleep mode enable */
#define I2C2_CTL0_GCEN                   BIT(19)                               /*!< whether or not to response to a General Call (0x00) */
#define I2C2_CTL0_SMBHAEN                BIT(20)                               /*!< SMBus host address enable */
#define I2C2_CTL0_SMBDAEN                BIT(21)                               /*!< SMBus device default address enable */
#define I2C2_CTL0_SMBALTEN               BIT(22)                               /*!< SMBus alert enable */
#define I2C2_CTL0_PECEN                  BIT(23)                               /*!< PEC calculation switch */

/* I2Cx_CTL1 */
#define I2C2_CTL1_SADDRESS               BITS(0,9)                             /*!< received slave address */
#define I2C2_CTL1_TRDIR                  BIT(10)                               /*!< transfer direction in master mode */
#define I2C2_CTL1_ADD10EN                BIT(11)                               /*!< 10-bit addressing mode enable in master mode */
#define I2C2_CTL1_HEAD10R                BIT(12)                               /*!< 10-bit address header executes read direction only in master receive mode */
#define I2C2_CTL1_START                  BIT(13)                               /*!< generate a START condition on I2C bus */
#define I2C2_CTL1_STOP                   BIT(14)                               /*!< generate a STOP condition on I2C bus */
#define I2C2_CTL1_NACKEN                 BIT(15)                               /*!< generate NACK in slave mode */
#define I2C2_CTL1_BYTENUM                BITS(16,23)                           /*!< number of bytes to be transferred */
#define I2C2_CTL1_RELOAD                 BIT(24)                               /*!< reload mode enable */
#define I2C2_CTL1_AUTOEND                BIT(25)                               /*!< automatic end mode in master mode */
#define I2C2_CTL1_PECTRANS               BIT(26)                               /*!< PEC transfer */

/* I2Cx_SADDR0 */
#define I2C2_SADDR0_ADDRESS0             BIT(0)                                /*!< bit 0 of a 10-bit address */
#define I2C2_SADDR0_ADDRESS              BITS(1,7)                             /*!< 7-bit address or bits 7:1 of a 10-bit address */
#define I2C2_SADDR0_ADDRESS_H            BITS(8,9)                             /*!< highest two bits of a 10-bit address */
#define I2C2_SADDR0_ADDFORMAT            BIT(10)                               /*!< address mode for the I2C slave */
#define I2C2_SADDR0_ADDRESSEN            BIT(15)                               /*!< I2C address enable */

/* I2Cx_SADDR1 */
#define I2C2_SADDR1_ADDRESS2             BITS(1,7)                             /*!< second I2C address for the slave */
#define I2C2_SADDR1_ADDMSK2              BITS(8,10)                            /*!< ADDRESS2[7:1] mask */
#define I2C2_SADDR1_ADDRESS2EN           BIT(15)                               /*!< second I2C address enable */

/* I2Cx_TIMING */
#define I2C2_TIMING_SCLL                 BITS(0,7)                             /*!< SCL low period */
#define I2C2_TIMING_SCLH                 BITS(8,15)                            /*!< SCL high period */
#define I2C2_TIMING_SDADELY              BITS(16,19)                           /*!< data hold time */
#define I2C2_TIMING_SCLDELY              BITS(20,23)                           /*!< data setup time */
#define I2C2_TIMING_PSC                  BITS(28,31)                           /*!< timing prescaler */

/* I2Cx_TIMEOUT */
#define I2C2_TIMEOUT_BUSTOA              BITS(0,11)                            /*!< bus timeout A */
#define I2C2_TIMEOUT_TOIDLE              BIT(12)                               /*!< idle clock timeout detection */
#define I2C2_TIMEOUT_TOEN                BIT(15)                               /*!< clock timeout detection enable */
#define I2C2_TIMEOUT_BUSTOB              BITS(16,27)                           /*!< bus timeout B */
#define I2C2_TIMEOUT_EXTOEN              BIT(31)                               /*!< extended clock timeout detection enable */

/* I2Cx_STAT */
#define I2C2_STAT_TBE                    BIT(0)                                /*!< I2C_TDATA is empty during transmitting */
#define I2C2_STAT_TI                     BIT(1)                                /*!< transmit interrupt */
#define I2C2_STAT_RBNE                   BIT(2)                                /*!< I2C_RDATA is not empty during receiving */
#define I2C2_STAT_ADDSEND                BIT(3)                                /*!< address received matches in slave mode */
#define I2C2_STAT_NACK                   BIT(4)                                /*!< not acknowledge flag */
#define I2C2_STAT_STPDET                 BIT(5)                                /*!< STOP condition detected in slave mode */
#define I2C2_STAT_TC                     BIT(6)                                /*!< transfer complete in master mode */
#define I2C2_STAT_TCR                    BIT(7)                                /*!< transfer complete reload */
#define I2C2_STAT_BERR                   BIT(8)                                /*!< bus error */
#define I2C2_STAT_LOSTARB                BIT(9)                                /*!< arbitration lost */
#define I2C2_STAT_OUERR                  BIT(10)                               /*!< overrun/underrun error in slave mode */
#define I2C2_STAT_PECERR                 BIT(11)                               /*!< PEC error */
#define I2C2_STAT_TIMEOUT                BIT(12)                               /*!< timeout flag */
#define I2C2_STAT_SMBALT                 BIT(13)                               /*!< SMBus Alert */
#define I2C2_STAT_I2CBSY                 BIT(15)                               /*!< busy flag */
#define I2C2_STAT_TR                     BIT(16)                               /*!< whether the I2C is a transmitter or a receiver in slave mode */
#define I2C2_STAT_READDR                 BITS(17,23)                           /*!< received match address in slave mode */

/* I2Cx_STATC */
#define I2C2_STATC_ADDSENDC              BIT(3)                                /*!< ADDSEND flag clear */
#define I2C2_STATC_NACKC                 BIT(4)                                /*!< not acknowledge flag clear */
#define I2C2_STATC_STPDETC               BIT(5)                                /*!< STPDET flag clear */
#define I2C2_STATC_BERRC                 BIT(8)                                /*!< bus error flag clear */
#define I2C2_STATC_LOSTARBC              BIT(9)                                /*!< arbitration Lost flag clear */
#define I2C2_STATC_OUERRC                BIT(10)                               /*!< overrun/underrun flag clear */
#define I2C2_STATC_PECERRC               BIT(11)                               /*!< PEC error flag clear */
#define I2C2_STATC_TIMEOUTC              BIT(12)                               /*!< TIMEOUT flag clear */
#define I2C2_STATC_SMBALTC               BIT(13)                               /*!< SMBus Alert flag clear */

/* I2Cx_PEC */
#define I2C2_PEC_PECV                    BITS(0,7)                             /*!< Packet Error Checking Value that calculated by hardware when PEC is enabled */

/* I2Cx_RDATA */
#define I2C2_RDATA_RDATA                 BITS(0,7)                             /*!< receive data value */

/* I2Cx_TDATA */
#define I2C2_TDATA_TDATA                 BITS(0,7)                             /*!< transmit data value */

/* constants definitions */
/* define the I2C bit position and its register index offset */
#define I2C_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define I2C_REG_VAL(i2cx, offset)       (REG32((i2cx) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define I2C_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)
#define I2C_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                              | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define I2C_REG_VAL2(i2cx, offset)      (REG32((i2cx) + ((uint32_t)(offset) >> 22)))
#define I2C_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
/* register offset of I2Cx(x=0,1) */
#define I2C_CTL1_REG_OFFSET              ((uint32_t)0x00000004U)               /*!< CTL1 register offset */
#define I2C_STAT0_REG_OFFSET             ((uint32_t)0x00000014U)               /*!< STAT0 register offset */
#define I2C_STAT1_REG_OFFSET             ((uint32_t)0x00000018U)               /*!< STAT1 register offset */
#define I2C_SAMCS_REG_OFFSET             ((uint32_t)0x00000080U)               /*!< SAMCS register offset */
#define I2C_CTL2_REG_OFFSET              ((uint32_t)0x00000090U)               /*!< CTL2 register offset */
#define I2C_CS_REG_OFFSET                ((uint32_t)0x00000094U)               /*!< control and status register offset */
#define I2C_STATC_REG_OFFSET             ((uint32_t)0x00000098U)               /*!< status clear register offset */
/* register offset of I2Cx(x=2) */
#define I2C2_CTL0_REG_OFFSET             ((uint32_t)0x00000000U)               /*!< CTL0 register offset */
#define I2C2_STAT_REG_OFFSET             ((uint32_t)0x00000018U)               /*!< STAT register offset */

/* I2C flag definitions */
/* I2C flag definitions of I2Cx(x=0,1) */
typedef enum {
    /* flags in STAT0 register */
    I2C_FLAG_SBSEND = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 0U),                /*!< start condition sent out in master mode */
    I2C_FLAG_ADDSEND = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 1U),               /*!< address is sent in master mode or received and matches in slave mode */
    I2C_FLAG_BTC = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 2U),                   /*!< byte transmission finishes */
    I2C_FLAG_ADD10SEND = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 3U),             /*!< header of 10-bit address is sent in master mode */
    I2C_FLAG_STPDET = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 4U),                /*!< stop condition detected in slave mode */
    I2C_FLAG_RBNE = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 6U),                  /*!< I2C_DATA is not Empty during receiving */
    I2C_FLAG_TBE = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 7U),                   /*!< I2C_DATA is empty during transmitting */
    I2C_FLAG_BERR = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 8U),                  /*!< a bus error occurs indication a unexpected start or stop condition on I2C bus */
    I2C_FLAG_LOSTARB = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 9U),               /*!< arbitration lost in master mode */
    I2C_FLAG_AERR = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 10U),                 /*!< acknowledge error */
    I2C_FLAG_OUERR = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 11U),                /*!< over-run or under-run situation occurs in slave mode */
    I2C_FLAG_PECERR = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 12U),               /*!< PEC error when receiving data */
    I2C_FLAG_SMBTO = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 14U),                /*!< timeout signal in SMBus mode */
    I2C_FLAG_SMBALT = I2C_REGIDX_BIT(I2C_STAT0_REG_OFFSET, 15U),               /*!< SMBus alert status */
    /* flags in STAT1 register */
    I2C_FLAG_MASTER = I2C_REGIDX_BIT(I2C_STAT1_REG_OFFSET, 0U),                /*!< a flag indicating whether I2C block is in master or slave mode */
    I2C_FLAG_I2CBSY = I2C_REGIDX_BIT(I2C_STAT1_REG_OFFSET, 1U),                /*!< busy flag */
    I2C_FLAG_TR = I2C_REGIDX_BIT(I2C_STAT1_REG_OFFSET, 2U),                    /*!< whether the I2C is a transmitter or a receiver */
    I2C_FLAG_RXGC = I2C_REGIDX_BIT(I2C_STAT1_REG_OFFSET, 4U),                  /*!< general call address (00h) received */
    I2C_FLAG_DEFSMB = I2C_REGIDX_BIT(I2C_STAT1_REG_OFFSET, 5U),                /*!< default address of SMBus device */
    I2C_FLAG_HSTSMB = I2C_REGIDX_BIT(I2C_STAT1_REG_OFFSET, 6U),                /*!< SMBus host header detected in slave mode */
    I2C_FLAG_DUMOD = I2C_REGIDX_BIT(I2C_STAT1_REG_OFFSET, 7U),                 /*!< dual flag in slave mode indicating which address is matched in dual-address mode */
    /* flags in SAMCS register */
    I2C_FLAG_TFF = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 12U),                  /*!< txframe fall flag */
    I2C_FLAG_TFR = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 13U),                  /*!< txframe rise flag */
    I2C_FLAG_RFF = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 14U),                  /*!< rxframe fall flag */
    I2C_FLAG_RFR = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 15U),                  /*!< rxframe rise flag */
    /* flags in control and status register */
    I2C_FLAG_STLO = I2C_REGIDX_BIT(I2C_CS_REG_OFFSET, 0U),                     /*!< start lost flag */
    I2C_FLAG_STPSEND = I2C_REGIDX_BIT(I2C_CS_REG_OFFSET, 1U)                   /*!< stop condition sent flag */
} i2c_flag_enum;

/* I2C flag definitions of I2Cx(x=2) */
#define I2C2_FLAG_TBE                    I2C2_STAT_TBE                         /*!< I2C_TDATA is empty during transmitting */
#define I2C2_FLAG_TI                     I2C2_STAT_TI                          /*!< transmit interrupt */
#define I2C2_FLAG_RBNE                   I2C2_STAT_RBNE                        /*!< I2C_RDATA is not empty during receiving */
#define I2C2_FLAG_ADDSEND                I2C2_STAT_ADDSEND                     /*!< address received matches in slave mode */
#define I2C2_FLAG_NACK                   I2C2_STAT_NACK                        /*!< not acknowledge flag */
#define I2C2_FLAG_STPDET                 I2C2_STAT_STPDET                      /*!< STOP condition detected in slave mode */
#define I2C2_FLAG_TC                     I2C2_STAT_TC                          /*!< transfer complete in master mode */
#define I2C2_FLAG_TCR                    I2C2_STAT_TCR                         /*!< transfer complete reload */
#define I2C2_FLAG_BERR                   I2C2_STAT_BERR                        /*!< bus error */
#define I2C2_FLAG_LOSTARB                I2C2_STAT_LOSTARB                     /*!< arbitration lost */
#define I2C2_FLAG_OUERR                  I2C2_STAT_OUERR                       /*!< overrun/underrun error in slave mode */
#define I2C2_FLAG_PECERR                 I2C2_STAT_PECERR                      /*!< PEC error */
#define I2C2_FLAG_TIMEOUT                I2C2_STAT_TIMEOUT                     /*!< timeout flag */
#define I2C2_FLAG_SMBALT                 I2C2_STAT_SMBALT                      /*!< SMBus Alert */
#define I2C2_FLAG_I2CBSY                 I2C2_STAT_I2CBSY                      /*!< busy flag */
#define I2C2_FLAG_TR                     I2C2_STAT_TR                          /*!< whether the I2C is a transmitter or a receiver in slave mode */

/* I2C interrupt flags */
/* I2C interrupt flags of I2Cx(x=0,1) */
typedef enum {
    /* interrupt flags in CTL1 register */
    I2C_INT_FLAG_SBSEND = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 9U, I2C_STAT0_REG_OFFSET, 0U),        /*!< start condition sent out in master mode interrupt flag */
    I2C_INT_FLAG_ADDSEND = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 9U, I2C_STAT0_REG_OFFSET, 1U),       /*!< address is sent in master mode or received and matches in slave mode interrupt flag */
    I2C_INT_FLAG_BTC =  I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 9U, I2C_STAT0_REG_OFFSET, 2U),          /*!< byte transmission finishes */
    I2C_INT_FLAG_ADD10SEND =  I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 9U, I2C_STAT0_REG_OFFSET, 3U),    /*!< header of 10-bit address is sent in master mode interrupt flag */
    I2C_INT_FLAG_STPDET = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 9U, I2C_STAT0_REG_OFFSET, 4U),        /*!< stop condition detected in slave mode interrupt flag */
    I2C_INT_FLAG_RBNE = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 9U, I2C_STAT0_REG_OFFSET, 6U),          /*!< I2C_DATA is not Empty during receiving interrupt flag */
    I2C_INT_FLAG_TBE = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 9U, I2C_STAT0_REG_OFFSET, 7U),           /*!< I2C_DATA is empty during transmitting interrupt flag */
    I2C_INT_FLAG_BERR = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 8U, I2C_STAT0_REG_OFFSET, 8U),          /*!< a bus error occurs indication a unexpected start or stop condition on I2C bus interrupt flag */
    I2C_INT_FLAG_LOSTARB = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 8U, I2C_STAT0_REG_OFFSET, 9U),       /*!< arbitration lost in master mode interrupt flag */
    I2C_INT_FLAG_AERR = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 8U, I2C_STAT0_REG_OFFSET, 10U),         /*!< acknowledge error interrupt flag */
    I2C_INT_FLAG_OUERR = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 8U, I2C_STAT0_REG_OFFSET, 11U),        /*!< over-run or under-run situation occurs in slave mode interrupt flag */
    I2C_INT_FLAG_PECERR = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 8U, I2C_STAT0_REG_OFFSET, 12U),       /*!< PEC error when receiving data interrupt flag */
    I2C_INT_FLAG_SMBTO = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 8U, I2C_STAT0_REG_OFFSET, 14U),        /*!< timeout signal in SMBus mode interrupt flag */
    I2C_INT_FLAG_SMBALT = I2C_REGIDX_BIT2(I2C_CTL1_REG_OFFSET, 8U, I2C_STAT0_REG_OFFSET, 15U),       /*!< SMBus Alert status interrupt flag */
    /* interrupt flags in SAMCS register */
    I2C_INT_FLAG_TFF = I2C_REGIDX_BIT2(I2C_SAMCS_REG_OFFSET, 4U, I2C_SAMCS_REG_OFFSET, 12U),         /*!< txframe fall interrupt flag */
    I2C_INT_FLAG_TFR = I2C_REGIDX_BIT2(I2C_SAMCS_REG_OFFSET, 5U, I2C_SAMCS_REG_OFFSET, 13U),         /*!< txframe rise interrupt  flag */
    I2C_INT_FLAG_RFF = I2C_REGIDX_BIT2(I2C_SAMCS_REG_OFFSET, 6U, I2C_SAMCS_REG_OFFSET, 14U),         /*!< rxframe fall interrupt flag */
    I2C_INT_FLAG_RFR = I2C_REGIDX_BIT2(I2C_SAMCS_REG_OFFSET, 7U, I2C_SAMCS_REG_OFFSET, 15U),         /*!< rxframe rise interrupt flag */
    /* interrupt flags in control and status register */
    I2C_INT_FLAG_STLO = I2C_REGIDX_BIT2(I2C_CS_REG_OFFSET, 8U, I2C_CS_REG_OFFSET, 0U),               /*!< start lost interrupt flag */
    I2C_INT_FLAG_STPSEND = I2C_REGIDX_BIT2(I2C_CS_REG_OFFSET, 9U, I2C_CS_REG_OFFSET, 1U)             /*!< stop condition sent interrupt flag */
} i2c_interrupt_flag_enum;

/* I2C interrupt flags of I2Cx(x=2) */
typedef enum {
    I2C2_INT_FLAG_TI = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 1U, I2C2_STAT_REG_OFFSET, 1U),          /*!< transmit interrupt flag */
    I2C2_INT_FLAG_RBNE = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 2U, I2C2_STAT_REG_OFFSET, 2U),        /*!< I2C_RDATA is not empty during receiving interrupt flag */
    I2C2_INT_FLAG_ADDSEND = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 3U, I2C2_STAT_REG_OFFSET, 3U),     /*!< address received matches in slave mode interrupt flag */
    I2C2_INT_FLAG_NACK = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 4U, I2C2_STAT_REG_OFFSET, 4U),        /*!< not acknowledge interrupt flag */
    I2C2_INT_FLAG_STPDET = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 5U, I2C2_STAT_REG_OFFSET, 5U),      /*!< stop condition detected in slave mode interrupt flag */
    I2C2_INT_FLAG_TC = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 6U, I2C2_STAT_REG_OFFSET, 6U),          /*!< transfer complete in master mode interrupt flag */
    I2C2_INT_FLAG_TCR = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 6U, I2C2_STAT_REG_OFFSET, 7U),         /*!< transfer complete reload interrupt flag */
    I2C2_INT_FLAG_BERR = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 7U, I2C2_STAT_REG_OFFSET, 8U),        /*!< bus error interrupt flag */
    I2C2_INT_FLAG_LOSTARB = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 7U, I2C2_STAT_REG_OFFSET, 9U),     /*!< arbitration lost interrupt flag */
    I2C2_INT_FLAG_OUERR = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 7U, I2C2_STAT_REG_OFFSET, 10U),      /*!< overrun/underrun error in slave mode interrupt flag */
    I2C2_INT_FLAG_PECERR = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 7U, I2C2_STAT_REG_OFFSET, 11U),     /*!< PEC error interrupt flag */
    I2C2_INT_FLAG_TIMEOUT = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 7U, I2C2_STAT_REG_OFFSET, 12U),    /*!< timeout interrupt flag */
    I2C2_INT_FLAG_SMBALT = I2C_REGIDX_BIT2(I2C2_CTL0_REG_OFFSET, 7U, I2C2_STAT_REG_OFFSET, 13U)      /*!< SMBus Alert interrupt flag */
} i2c2_interrupt_flag_enum;

/* I2C interrupt of I2Cx(x=0,1) */
typedef enum {
    /* interrupt in CTL1 register */
    I2C_INT_ERR = I2C_REGIDX_BIT(I2C_CTL1_REG_OFFSET, 8U),                     /*!< error interrupt */
    I2C_INT_EV = I2C_REGIDX_BIT(I2C_CTL1_REG_OFFSET, 9U),                      /*!< event interrupt */
    I2C_INT_BUF = I2C_REGIDX_BIT(I2C_CTL1_REG_OFFSET, 10U),                    /*!< buffer interrupt */
    /* interrupt in SAMCS register */
    I2C_INT_TFF = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 4U),                    /*!< txframe fall interrupt  */
    I2C_INT_TFR = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 5U),                    /*!< txframe rise interrupt */
    I2C_INT_RFF = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 6U),                    /*!< rxframe fall interrupt */
    I2C_INT_RFR = I2C_REGIDX_BIT(I2C_SAMCS_REG_OFFSET, 7U),                    /*!< rxframe rise interrupt */
    /* interrupt in control and status register */
    I2C_INT_STLO = I2C_REGIDX_BIT(I2C_CS_REG_OFFSET, 8U),                      /*!< start lost interrupt */
    I2C_INT_STPSEND = I2C_REGIDX_BIT(I2C_CS_REG_OFFSET, 9U)                    /*!< stop condition sent interrupt */
} i2c_interrupt_enum;

/* I2C interrupt of I2Cx(x=2) */
#define I2C2_INT_ERR                     I2C2_CTL0_ERRIE                       /*!< error interrupt */
#define I2C2_INT_TC                      I2C2_CTL0_TCIE                        /*!< transfer complete interrupt */
#define I2C2_INT_STPDET                  I2C2_CTL0_STPDETIE                    /*!< stop detection interrupt */
#define I2C2_INT_NACK                    I2C2_CTL0_NACKIE                      /*!< not acknowledge received interrupt */
#define I2C2_INT_ADDM                    I2C2_CTL0_ADDMIE                      /*!< address match interrupt */
#define I2C2_INT_RBNE                    I2C2_CTL0_RBNEIE                      /*!< receive interrupt */
#define I2C2_INT_TI                      I2C2_CTL0_TIE                         /*!< transmit interrupt */

/* I2C status register bit clear */
#define CLEAR_STPDET                     I2C_STATC_STOPFC                      /*!< clear STPDET bit in I2C_STAT0 */
#define CLEAR_ADD10SEND                  I2C_STATC_ADD10SENDC                  /*!< clear ADD10SEND bit in I2C_STAT0 */
#define CLEAR_BTC                        I2C_STATC_BTCC                        /*!< clear BTC bit in I2C_STAT0 */
#define CLEAR_ADDSEND                    I2C_STATC_ADDSENDC                    /*!< clear ADDSEND bit in I2C_STAT0 */
#define CLEAR_SBSEND                     I2C_STATC_SBSENDC                     /*!< clear SBSEND bit in I2C_STAT0 */

/* I2C start early termination mode */
#define STANDARD_I2C_PROTOCOL_MODE       ((uint32_t)0x00000000U)               /*!< do as the standard i2c protocol */
#define ARBITRATION_LOST_MODE            I2C_CTL2_SETM                         /*!< do the same thing as arbitration lost */

/* SMBus/I2C mode switch and SMBus type selection */
#define I2C_I2CMODE_ENABLE               ((uint32_t)0x00000000U)               /*!< I2C mode */
#define I2C_SMBUSMODE_ENABLE             I2C_CTL0_SMBEN                        /*!< SMBus mode */

/* SMBus/I2C mode switch and SMBus type selection */
#define I2C_SMBUS_DEVICE                 ((uint32_t)0x00000000U)               /*!< SMBus mode device type */
#define I2C_SMBUS_HOST                   I2C_CTL0_SMBSEL                       /*!< SMBus mode host type */

/* I2C transfer direction */
#define I2C_RECEIVER                     ((uint32_t)0x00000001U)               /*!< receiver */
#define I2C_TRANSMITTER                  ((uint32_t)0xFFFFFFFEU)               /*!< transmitter */

/* whether or not to send an ACK */
#define I2C_ACK_DISABLE                  ((uint32_t)0x00000000U)               /*!< ACK will be not sent */
#define I2C_ACK_ENABLE                   I2C_CTL0_ACKEN                        /*!< ACK will be sent */

/* I2C POAP position*/
#define I2C_ACKPOS_CURRENT               ((uint32_t)0x00000000U)               /*!< ACKEN bit decides whether or not to send ACK or not for the current byte */
#define I2C_ACKPOS_NEXT                  I2C_CTL0_POAP                         /*!< ACKEN bit decides whether or not to send ACK for the next byte */

/* software reset I2C */
#define I2C_SRESET_RESET                 ((uint32_t)0x00000000U)               /*!< I2C is not under reset */
#define I2C_SRESET_SET                   I2C_CTL0_SRESET                       /*!< I2C is under reset */

/* I2C DMA mode configure */
/* DMA mode switch */
#define I2C_DMA_OFF                      ((uint32_t)0x00000000U)               /*!< disable DMA mode */
#define I2C_DMA_ON                       I2C_CTL1_DMAON                        /*!< enable DMA mode */

/* flag indicating DMA last transfer */
#define I2C_DMALST_OFF                   ((uint32_t)0x00000000U)               /*!< next DMA EOT is not the last transfer */
#define I2C_DMALST_ON                    I2C_CTL1_DMALST                       /*!< next DMA EOT is the last transfer */

/* I2C PEC configure */
/* PEC enable */
#define I2C_PEC_DISABLE                  ((uint32_t)0x00000000U)               /*!< PEC calculation off */
#define I2C_PEC_ENABLE                   I2C_CTL0_PECEN                        /*!< PEC calculation on */

/* I2C SMBus configure */
/* issue or not alert through SMBA pin */
#define I2C_SALTSEND_DISABLE             ((uint32_t)0x00000000U)               /*!< not issue alert through SMBA */
#define I2C_SALTSEND_ENABLE              I2C_CTL0_SALT                         /*!< issue alert through SMBA pin */

/* ARP protocol in SMBus switch */
#define I2C_ARP_DISABLE                  ((uint32_t)0x00000000U)               /*!< disable ARP */
#define I2C_ARP_ENABLE                   I2C_CTL0_ARPEN                        /*!< enable ARP */

/* fast mode plus enable */
#define I2C_FAST_MODE_PLUS_DISABLE       ((uint32_t)0x00000000U)               /*!< disable fast mode plus */
#define I2C_FAST_MODE_PLUS_ENABLE        I2C_CTL2_FMPEN                        /*!< enable fast mode plus */

/* I2C duty cycle in fast mode or fast mode plus */
#define I2C_DTCY_2                       ((uint32_t)0x00000000U)               /*!< in I2C fast mode or fast mode plus Tlow/Thigh = 2 */
#define I2C_DTCY_16_9                    I2C_CKCFG_DTCY                        /*!< in I2C fast mode or fast mode plus Tlow/Thigh = 16/9 */

/* address mode for the I2C slave */
#define I2C_ADDFORMAT_7BITS              ((uint32_t)0x00000000U)               /*!< address format is 7 bits */
#define I2C_ADDFORMAT_10BITS             I2C_SADDR0_ADDFORMAT                  /*!< address format is 10 bits */

/* I2C DMA constants definitions */
#define I2C2_DMA_TRANSMIT                ((uint32_t)0x00000000U)               /*!< I2C transmit data use DMA */
#define I2C2_DMA_RECEIVE                 ((uint32_t)0x00000001U)               /*!< I2C receive data use DMA */

/* I2C transfer direction in master mode */
#define I2C2_MASTER_TRANSMIT             ((uint32_t)0x00000000U)               /*!< I2C master transmit */
#define I2C2_MASTER_RECEIVE              I2C2_CTL1_TRDIR                       /*!< I2C master receive */

/* address mode for the I2C slave */
#define I2C2_ADDFORMAT_7BITS             ((uint32_t)0x00000000U)               /*!< address:7 bits */
#define I2C2_ADDFORMAT_10BITS            I2C2_SADDR0_ADDFORMAT                 /*!< address:10 bits */

/* defines which bits of register ADDRESS[7:1] are compared with an incoming address byte */
#define ADDRESS_BIT1_COMPARE             ((uint32_t)0x00000200U)               /*!< address bit1 needs compare */
#define ADDRESS_BIT2_COMPARE             ((uint32_t)0x00000400U)               /*!< address bit2 needs compare */
#define ADDRESS_BIT3_COMPARE             ((uint32_t)0x00000800U)               /*!< address bit3 needs compare */
#define ADDRESS_BIT4_COMPARE             ((uint32_t)0x00001000U)               /*!< address bit4 needs compare */
#define ADDRESS_BIT5_COMPARE             ((uint32_t)0x00002000U)               /*!< address bit5 needs compare */
#define ADDRESS_BIT6_COMPARE             ((uint32_t)0x00004000U)               /*!< address bit6 needs compare */
#define ADDRESS_BIT7_COMPARE             ((uint32_t)0x00008000U)               /*!< address bit7 needs compare */

/* the length of filter spikes */
#define FILTER_DISABLE                   ((uint32_t)0x00000000U)               /*!< digital filter is disabled */
#define FILTER_LENGTH_1                  ((uint32_t)0x00000001U)               /*!< digital filter is enabled and filter spikes with a length of up to 1 tI2CCLK */
#define FILTER_LENGTH_2                  ((uint32_t)0x00000002U)               /*!< digital filter is enabled and filter spikes with a length of up to 2 tI2CCLK */
#define FILTER_LENGTH_3                  ((uint32_t)0x00000003U)               /*!< digital filter is enabled and filter spikes with a length of up to 3 tI2CCLK */
#define FILTER_LENGTH_4                  ((uint32_t)0x00000004U)               /*!< digital filter is enabled and filter spikes with a length of up to 4 tI2CCLK */
#define FILTER_LENGTH_5                  ((uint32_t)0x00000005U)               /*!< digital filter is enabled and filter spikes with a length of up to 5 tI2CCLK */
#define FILTER_LENGTH_6                  ((uint32_t)0x00000006U)               /*!< digital filter is enabled and filter spikes with a length of up to 6 tI2CCLK */
#define FILTER_LENGTH_7                  ((uint32_t)0x00000007U)               /*!< digital filter is enabled and filter spikes with a length of up to 7 tI2CCLK */
#define FILTER_LENGTH_8                  ((uint32_t)0x00000008U)               /*!< digital filter is enabled and filter spikes with a length of up to 8 tI2CCLK */
#define FILTER_LENGTH_9                  ((uint32_t)0x00000009U)               /*!< digital filter is enabled and filter spikes with a length of up to 9 tI2CCLK */
#define FILTER_LENGTH_10                 ((uint32_t)0x0000000AU)               /*!< digital filter is enabled and filter spikes with a length of up to 10 tI2CCLK */
#define FILTER_LENGTH_11                 ((uint32_t)0x0000000BU)               /*!< digital filter is enabled and filter spikes with a length of up to 11 tI2CCLK */
#define FILTER_LENGTH_12                 ((uint32_t)0x0000000CU)               /*!< digital filter is enabled and filter spikes with a length of up to 12 tI2CCLK */
#define FILTER_LENGTH_13                 ((uint32_t)0x0000000DU)               /*!< digital filter is enabled and filter spikes with a length of up to 13 tI2CCLK */
#define FILTER_LENGTH_14                 ((uint32_t)0x0000000EU)               /*!< digital filter is enabled and filter spikes with a length of up to 14 tI2CCLK */
#define FILTER_LENGTH_15                 ((uint32_t)0x0000000FU)               /*!< digital filter is enabled and filter spikes with a length of up to 15 tI2CCLK */

/* defines which bits of ADDRESS2[7:1] are compared with an incoming address byte, and which bits are masked (don��t care) */
#define ADDRESS2_NO_MASK                 ((uint32_t)0x00000000U)               /*!< no mask, all the bits must be compared */
#define ADDRESS2_MASK_BIT1               ((uint32_t)0x00000001U)               /*!< ADDRESS2[1] is masked, only ADDRESS2[7:2] are compared */
#define ADDRESS2_MASK_BIT1_2             ((uint32_t)0x00000002U)               /*!< ADDRESS2[2:1] is masked, only ADDRESS2[7:3] are compared */
#define ADDRESS2_MASK_BIT1_3             ((uint32_t)0x00000003U)               /*!< ADDRESS2[3:1] is masked, only ADDRESS2[7:4] are compared */
#define ADDRESS2_MASK_BIT1_4             ((uint32_t)0x00000004U)               /*!< ADDRESS2[4:1] is masked, only ADDRESS2[7:5] are compared */
#define ADDRESS2_MASK_BIT1_5             ((uint32_t)0x00000005U)               /*!< ADDRESS2[5:1] is masked, only ADDRESS2[7:6] are compared */
#define ADDRESS2_MASK_BIT1_6             ((uint32_t)0x00000006U)               /*!< ADDRESS2[6:1] is masked, only ADDRESS2[7] are compared */
#define ADDRESS2_MASK_ALL                ((uint32_t)0x00000007U)               /*!< all the ADDRESS2[7:1] bits are masked */

/* idle clock timeout detection */
#define BUSTOA_DETECT_SCL_LOW            ((uint32_t)0x00000000U)               /*!< BUSTOA is used to detect SCL low timeout */
#define BUSTOA_DETECT_IDLE               I2C2_TIMEOUT_TOIDLE                   /*!< BUSTOA is used to detect both SCL and SDA high timeout when the bus is idle */

/* function declarations */
/* functions of I2C0~2 */
/* reset I2C */
void i2c_deinit(uint32_t i2c_periph);
/* enable I2C */
void i2c_enable(uint32_t i2c_periph);
/* disable I2C */
void i2c_disable(uint32_t i2c_periph);
/* generate a START condition on I2C bus */
void i2c_start_on_bus(uint32_t i2c_periph);
/* generate a STOP condition on I2C bus */
void i2c_stop_on_bus(uint32_t i2c_periph);
/* enable the response to a general call */
void i2c_slave_response_to_gcall_enable(uint32_t i2c_periph);
/* disable the response to a general call */
void i2c_slave_response_to_gcall_disable(uint32_t i2c_periph);
/* enable to stretch SCL low when data is not ready in slave mode */
void i2c_stretch_scl_low_enable(uint32_t i2c_periph);
/* disable to stretch SCL low when data is not ready in slave mode */
void i2c_stretch_scl_low_disable(uint32_t i2c_periph);
/* I2C transmit data function */
void i2c_data_transmit(uint32_t i2c_periph, uint32_t data);
/* I2C receive data function */
uint32_t i2c_data_receive(uint32_t i2c_periph);
/* I2C transfers PEC value */
void i2c_pec_transfer(uint32_t i2c_periph);
/* enable I2C PEC calculation */
void i2c_pec_enable(uint32_t i2c_periph);
/* disable I2C PEC calculation */
void i2c_pec_disable(uint32_t i2c_periph);
/* get packet error checking value */
uint32_t i2c_pec_value_get(uint32_t i2c_periph);

/* functions of I2C0, I2C1 */
/* configure I2C clock */
void i2c_clock_config(uint32_t i2c_periph, uint32_t clkspeed, uint32_t dutycyc);
/* configure I2C address */
void i2c_mode_addr_config(uint32_t i2c_periph, uint32_t mode, uint32_t addformat, uint32_t addr);
/* select SMBus type */
void i2c_smbus_type_config(uint32_t i2c_periph, uint32_t type);
/* whether or not to send an ACK */
void i2c_ack_config(uint32_t i2c_periph, uint32_t ack);
/* configure I2C POAP position */
void i2c_ackpos_config(uint32_t i2c_periph, uint32_t pos);
/* master sends slave address */
void i2c_master_addressing(uint32_t i2c_periph, uint32_t addr, uint32_t trandirection);
/* enable dual-address mode */
void i2c_dualaddr_enable(uint32_t i2c_periph, uint32_t addr);
/* disable dual-address mode */
void i2c_dualaddr_disable(uint32_t i2c_periph);

/* configure I2C DMA mode */
void i2c_dma_config(uint32_t i2c_periph, uint32_t dmastate);
/* configure whether next DMA EOT is DMA last transfer or not */
void i2c_dma_last_transfer_config(uint32_t i2c_periph, uint32_t dmalast);
/* configure software reset I2C */
void i2c_software_reset_config(uint32_t i2c_periph, uint32_t sreset);
/* configure I2C alert through SMBA pin */
void i2c_smbus_alert_config(uint32_t i2c_periph, uint32_t smbuspara);
/* configure I2C ARP protocol in SMBus */
void i2c_smbus_arp_config(uint32_t i2c_periph, uint32_t arpstate);
/* enable SAM_V interface */
void i2c_sam_enable(uint32_t i2c_periph);
/* disable SAM_V interface */
void i2c_sam_disable(uint32_t i2c_periph);
/* enable SAM_V interface timeout detect */
void i2c_sam_timeout_enable(uint32_t i2c_periph);
/* disable SAM_V interface timeout detect */
void i2c_sam_timeout_disable(uint32_t i2c_periph);

/* configure I2C start early termination mode */
void i2c_start_early_termination_mode_config(uint32_t i2c_periph, uint32_t mode);
/* enable I2C timeout calculation */
void i2c_timeout_calculation_enable(uint32_t i2c_periph);
/* disable I2C timeout calculation */
void i2c_timeout_calculation_disable(uint32_t i2c_periph);
/* enable I2C record the received slave address to the transfer buffer register */
void i2c_record_received_slave_address_enable(uint32_t i2c_periph);
/* disable I2C record the received slave address to the transfer buffer register */
void i2c_record_received_slave_address_disable(uint32_t i2c_periph);
/* define which bits of ADDRESS[7:1] need to compare with the incoming address byte */
void i2c_address_bit_compare_config(uint32_t i2c_periph, uint16_t compare_bits);
/* enable I2C status register clear */
void i2c_status_clear_enable(uint32_t i2c_periph);
/* disable I2C status register clear */
void i2c_status_clear_disable(uint32_t i2c_periph);
/* clear I2C status in I2C_STAT0 register */
void i2c_status_bit_clear(uint32_t i2c_periph, uint32_t clear_bit);

/* get I2C flag status */
FlagStatus i2c_flag_get(uint32_t i2c_periph, i2c_flag_enum flag);
/* clear I2C flag status */
void i2c_flag_clear(uint32_t i2c_periph, i2c_flag_enum flag);
/* enable I2C interrupt */
void i2c_interrupt_enable(uint32_t i2c_periph, i2c_interrupt_enum interrupt);
/* disable I2C interrupt */
void i2c_interrupt_disable(uint32_t i2c_periph, i2c_interrupt_enum interrupt);
/* get I2C interrupt flag status */
FlagStatus i2c_interrupt_flag_get(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag);
/* clear I2C interrupt flag status */
void i2c_interrupt_flag_clear(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag);

/* functions of I2C2 */
/* configure the timing parameters */
void i2c_timing_config(uint32_t i2c_periph, uint32_t psc, uint32_t scl_dely, uint32_t sda_dely);
/* configure digital noise filter */
void i2c_digital_noise_filter_config(uint32_t i2c_periph, uint32_t filter_length);
/* enable analog noise filter */
void i2c_analog_noise_filter_enable(uint32_t i2c_periph);
/* disable analog noise filter */
void i2c_analog_noise_filter_disable(uint32_t i2c_periph);
/* enable wakeup from Deep-sleep mode */
void i2c_wakeup_from_deepsleep_enable(uint32_t i2c_periph);
/* disable wakeup from Deep-sleep mode */
void i2c_wakeup_from_deepsleep_disable(uint32_t i2c_periph);

/* configure the SCL high and low period of clock in master mode */
void i2c_master_clock_config(uint32_t i2c_periph, uint32_t sclh, uint32_t scll);
/* configure I2C slave address and transfer direction in master mode */
void i2c2_master_addressing(uint32_t i2c_periph, uint32_t address, uint32_t trans_direction);
/* 10-bit address header executes read direction only in master receive mode */
void i2c_address10_header_enable(uint32_t i2c_periph);
/* 10-bit address header executes complete sequence in master receive mode */
void i2c_address10_header_disable(uint32_t i2c_periph);
/* enable 10-bit addressing mode in master mode */
void i2c_address10_enable(uint32_t i2c_periph);
/* disable 10-bit addressing mode in master mode */
void i2c_address10_disable(uint32_t i2c_periph);
/* enable I2C automatic end mode in master mode */
void i2c_automatic_end_enable(uint32_t i2c_periph);
/* disable I2C automatic end mode in master mode */
void i2c_automatic_end_disable(uint32_t i2c_periph);

/* configure I2C slave address */
void i2c_address_config(uint32_t i2c_periph, uint32_t address, uint32_t addr_format);
/* disable I2C address in slave mode */
void i2c_address_disable(uint32_t i2c_periph);
/* configure I2C second slave address */
void i2c_second_address_config(uint32_t i2c_periph, uint32_t address, uint32_t addr_mask);
/* disable I2C second address in slave mode */
void i2c_second_address_disable(uint32_t i2c_periph);
/* get received match address in slave mode */
uint32_t i2c_recevied_address_get(uint32_t i2c_periph);
/* enable slave byte control */
void i2c_slave_byte_control_enable(uint32_t i2c_periph);
/* disable slave byte control */
void i2c_slave_byte_control_disable(uint32_t i2c_periph);
/* generate a NACK in slave mode */
void i2c_nack_enable(uint32_t i2c_periph);
/* generate an ACK in slave mode */
void i2c_nack_disable(uint32_t i2c_periph);

/* enable I2C reload mode */
void i2c_reload_enable(uint32_t i2c_periph);
/* disable I2C reload mode */
void i2c_reload_disable(uint32_t i2c_periph);
/* configure number of bytes to be transferred */
void i2c_transfer_byte_number_config(uint32_t i2c_periph, uint32_t byte_number);
/* enable I2C DMA for transmission or reception */
void i2c2_dma_enable(uint32_t i2c_periph, uint8_t dma);
/* disable I2C DMA for transmission or reception */
void i2c2_dma_disable(uint32_t i2c_periph, uint8_t dma);

/* enable SMBus alert */
void i2c_smbus_alert_enable(uint32_t i2c_periph);
/* disable SMBus alert */
void i2c_smbus_alert_disable(uint32_t i2c_periph);
/* enable SMBus device default address */
void i2c_smbus_default_addr_enable(uint32_t i2c_periph);
/* disable SMBus device default address */
void i2c_smbus_default_addr_disable(uint32_t i2c_periph);
/* enable SMBus host address */
void i2c_smbus_host_addr_enable(uint32_t i2c_periph);
/* disable SMBus host address */
void i2c_smbus_host_addr_disable(uint32_t i2c_periph);
/* enable extended clock timeout detection */
void i2c_extented_clock_timeout_enable(uint32_t i2c_periph);
/* disable extended clock timeout detection */
void i2c_extented_clock_timeout_disable(uint32_t i2c_periph);
/* enable clock timeout detection */
void i2c_clock_timeout_enable(uint32_t i2c_periph);
/* disable clock timeout detection */
void i2c_clock_timeout_disable(uint32_t i2c_periph);
/* configure bus timeout B */
void i2c_bus_timeout_b_config(uint32_t i2c_periph, uint32_t timeout);
/* configure bus timeout A */
void i2c_bus_timeout_a_config(uint32_t i2c_periph, uint32_t timeout);
/* configure idle clock timeout detection */
void i2c_idle_clock_timeout_config(uint32_t i2c_periph, uint32_t timeout);

/* get I2C flag status */
FlagStatus i2c2_flag_get(uint32_t i2c_periph, uint32_t flag);
/* clear I2C flag status */
void i2c2_flag_clear(uint32_t i2c_periph, uint32_t flag);
/* enable I2C interrupt */
void i2c2_interrupt_enable(uint32_t i2c_periph, uint32_t interrupt);
/* disable I2C interrupt */
void i2c2_interrupt_disable(uint32_t i2c_periph, uint32_t interrupt);
/* get I2C interrupt flag status */
FlagStatus i2c2_interrupt_flag_get(uint32_t i2c_periph, i2c2_interrupt_flag_enum int_flag);
/* clear I2C interrupt flag status */
void i2c2_interrupt_flag_clear(uint32_t i2c_periph, i2c2_interrupt_flag_enum int_flag);

#endif /* GD32E50X_I2C_H */
