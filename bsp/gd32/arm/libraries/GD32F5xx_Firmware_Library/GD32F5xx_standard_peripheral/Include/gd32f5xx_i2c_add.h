/*!
    \file    gd32f5xx_i2c.h
    \brief   definitions for the I2C3-5

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
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

#ifndef GD32F5XX_I2C_ADD_H
#define GD32F5XX_I2C_ADD_H

#include "gd32f5xx.h"

/* I2Cx(x=3,4,5) definitions */
#define I2C0                                    I2C_BASE                          /*!< I2C0 base address */

#define I2C3                                    (I2C_BASE + 0x00002C00U)          /*!< I2C3 base address */
#define I2C4                                    (I2C_BASE + 0x00003000U)          /*!< I2C4 base address */
#define I2C5                                    (I2C_BASE + 0x00003400U)          /*!< I2C5 base address */

/* registers definitions */
/* registers of I2Cx(x=3,4,5) */
#define I2C_ADD_CTL0(i2cx)                  REG32((i2cx) + 0x00000000U)     /*!< I2C control register 0 */
#define I2C_ADD_CTL1(i2cx)                  REG32((i2cx) + 0x00000004U)     /*!< I2C control register 1 */
#define I2C_ADD_SADDR0(i2cx)                REG32((i2cx) + 0x00000008U)     /*!< I2C slave address register 0*/
#define I2C_ADD_SADDR1(i2cx)                REG32((i2cx) + 0x0000000CU)     /*!< I2C slave address register 1*/
#define I2C_ADD_TIMING(i2cx)                REG32((i2cx) + 0x00000010U)     /*!< I2C timing register */
#define I2C_ADD_TIMEOUT(i2cx)               REG32((i2cx) + 0x00000014U)     /*!< I2C timeout register */
#define I2C_ADD_STAT(i2cx)                  REG32((i2cx) + 0x00000018U)     /*!< I2C status register */
#define I2C_ADD_STATC(i2cx)                 REG32((i2cx) + 0x0000001CU)     /*!< I2C status clear register */
#define I2C_ADD_PEC(i2cx)                   REG32((i2cx) + 0x00000020U)     /*!< I2C PEC register */
#define I2C_ADD_RDATA(i2cx)                 REG32((i2cx) + 0x00000024U)     /*!< I2C receive data register */
#define I2C_ADD_TDATA(i2cx)                 REG32((i2cx) + 0x00000028U)     /*!< I2C transmit data register */
#define I2C_ADD_CTL2(i2cx)                  REG32((i2cx) + 0x00000090U)     /*!< I2C control register 2 */

/* bits definitions */
/* I2Cx_CTL0 */
#define I2C_ADD_CTL0_I2CEN                  BIT(0)                          /*!< I2C peripheral enable */
#define I2C_ADD_CTL0_TIE                    BIT(1)                          /*!< transmit interrupt enable */
#define I2C_ADD_CTL0_RBNEIE                 BIT(2)                          /*!< receive interrupt enable */
#define I2C_ADD_CTL0_ADDMIE                 BIT(3)                          /*!< address match interrupt enable in slave mode */
#define I2C_ADD_CTL0_NACKIE                 BIT(4)                          /*!< not acknowledge received interrupt enable */
#define I2C_ADD_CTL0_STPDETIE               BIT(5)                          /*!< stop detection interrupt enable */
#define I2C_ADD_CTL0_TCIE                   BIT(6)                          /*!< transfer complete interrupt enable */
#define I2C_ADD_CTL0_ERRIE                  BIT(7)                          /*!< error interrupt enable */
#define I2C_ADD_CTL0_DNF                    BITS(8,11)                      /*!< digital noise filter */
#define I2C_ADD_CTL0_ANOFF                  BIT(12)                         /*!< analog noise filter */
#define I2C_ADD_CTL0_DENT                   BIT(14)                         /*!< DMA enable for transmission */
#define I2C_ADD_CTL0_DENR                   BIT(15)                         /*!< DMA enable for reception */
#define I2C_ADD_CTL0_SBCTL                  BIT(16)                         /*!< slave byte control */
#define I2C_ADD_CTL0_SS                     BIT(17)                         /*!< whether to stretch SCL low when data is not ready in slave mode */
#define I2C_ADD_CTL0_WUEN                   BIT(18)                         /*!< wakeup from deep-sleep mode enable */
#define I2C_ADD_CTL0_GCEN                   BIT(19)                         /*!< whether or not to response to a general call (0x00) */
#define I2C_ADD_CTL0_SMBHAEN                BIT(20)                         /*!< SMBus host address enable */
#define I2C_ADD_CTL0_SMBDAEN                BIT(21)                         /*!< SMBus device default address enable */
#define I2C_ADD_CTL0_SMBALTEN               BIT(22)                         /*!< SMBus alert enable */
#define I2C_ADD_CTL0_PECEN                  BIT(23)                         /*!< PEC calculation switch */

/* I2Cx_CTL1 */
#define I2C_ADD_CTL1_SADDRESS               BITS(0,9)                       /*!< received slave address */
#define I2C_ADD_CTL1_TRDIR                  BIT(10)                         /*!< transfer direction in master mode */
#define I2C_ADD_CTL1_ADD10EN                BIT(11)                         /*!< 10-bit addressing mode enable in master mode */
#define I2C_ADD_CTL1_HEAD10R                BIT(12)                         /*!< 10-bit address header executes read direction only in master receive mode */
#define I2C_ADD_CTL1_START                  BIT(13)                         /*!< generate a START condition on I2C bus */
#define I2C_ADD_CTL1_STOP                   BIT(14)                         /*!< generate a STOP condition on I2C bus */
#define I2C_ADD_CTL1_NACKEN                 BIT(15)                         /*!< generate NACK in slave mode */
#define I2C_ADD_CTL1_BYTENUM                BITS(16,23)                     /*!< number of bytes to be transferred */
#define I2C_ADD_CTL1_RELOAD                 BIT(24)                         /*!< reload mode enable */
#define I2C_ADD_CTL1_AUTOEND                BIT(25)                         /*!< automatic end mode in master mode */
#define I2C_ADD_CTL1_PECTRANS               BIT(26)                         /*!< PEC transfer */

/* I2Cx_SADDR0 */
#define I2C_ADD_SADDR0_ADDRESS0             BIT(0)                          /*!< bit 0 of a 10-bit address */
#define I2C_ADD_SADDR0_ADDRESS              BITS(1,7)                       /*!< 7-bit address or bits 7:1 of a 10-bit address */
#define I2C_ADD_SADDR0_ADDRESS_H            BITS(8,9)                       /*!< highest two bits of a 10-bit address */
#define I2C_ADD_SADDR0_ADDFORMAT            BIT(10)                         /*!< address mode for the I2C slave */
#define I2C_ADD_SADDR0_ADDRESSEN            BIT(15)                         /*!< I2C address enable */

/* I2Cx_SADDR1 */
#define I2C_ADD_SADDR1_ADDRESS2             BITS(1,7)                       /*!< second I2C address for the slave */
#define I2C_ADD_SADDR1_ADDMSK2              BITS(8,10)                      /*!< ADDRESS2[7:1] mask */
#define I2C_ADD_SADDR1_ADDRESS2EN           BIT(15)                         /*!< second I2C address enable */

/* I2Cx_TIMING */
#define I2C_ADD_TIMING_SCLL                 BITS(0,7)                       /*!< SCL low period */
#define I2C_ADD_TIMING_SCLH                 BITS(8,15)                      /*!< SCL high period */
#define I2C_ADD_TIMING_SDADELY              BITS(16,19)                     /*!< data hold time */
#define I2C_ADD_TIMING_SCLDELY              BITS(20,23)                     /*!< data setup time */
#define I2C_ADD_TIMING_PSC                  BITS(28,31)                     /*!< timing prescaler */

/* I2Cx_TIMEOUT */
#define I2C_ADD_TIMEOUT_BUSTOA              BITS(0,11)                      /*!< bus timeout A */
#define I2C_ADD_TIMEOUT_TOIDLE              BIT(12)                         /*!< idle clock timeout detection */
#define I2C_ADD_TIMEOUT_TOEN                BIT(15)                         /*!< clock timeout detection enable */
#define I2C_ADD_TIMEOUT_BUSTOB              BITS(16,27)                     /*!< bus timeout B */
#define I2C_ADD_TIMEOUT_EXTOEN              BIT(31)                         /*!< extended clock timeout detection enable */

/* I2Cx_STAT */
#define I2C_ADD_STAT_TBE                    BIT(0)                          /*!< I2C_ADD_TDATA is empty during transmitting */
#define I2C_ADD_STAT_TI                     BIT(1)                          /*!< transmit interrupt */
#define I2C_ADD_STAT_RBNE                   BIT(2)                          /*!< I2C_ADD_RDATA is not empty during receiving */
#define I2C_ADD_STAT_ADDSEND                BIT(3)                          /*!< address received matches in slave mode */
#define I2C_ADD_STAT_NACK                   BIT(4)                          /*!< not acknowledge flag */
#define I2C_ADD_STAT_STPDET                 BIT(5)                          /*!< STOP condition detected in slave mode */
#define I2C_ADD_STAT_TC                     BIT(6)                          /*!< transfer complete in master mode */
#define I2C_ADD_STAT_TCR                    BIT(7)                          /*!< transfer complete reload */
#define I2C_ADD_STAT_BERR                   BIT(8)                          /*!< bus error */
#define I2C_ADD_STAT_LOSTARB                BIT(9)                          /*!< arbitration lost */
#define I2C_ADD_STAT_OUERR                  BIT(10)                         /*!< overrun/underrun error in slave mode */
#define I2C_ADD_STAT_PECERR                 BIT(11)                         /*!< PEC error */
#define I2C_ADD_STAT_TIMEOUT                BIT(12)                         /*!< timeout flag */
#define I2C_ADD_STAT_SMBALT                 BIT(13)                         /*!< SMBus Alert */
#define I2C_ADD_STAT_I2CBSY                 BIT(15)                         /*!< busy flag */
#define I2C_ADD_STAT_TR                     BIT(16)                         /*!< whether the I2C is a transmitter or a receiver in slave mode */
#define I2C_ADD_STAT_READDR                 BITS(17,23)                     /*!< received match address in slave mode */

/* I2Cx_STATC */
#define I2C_ADD_STATC_ADDSENDC              BIT(3)                          /*!< ADDSEND flag clear */
#define I2C_ADD_STATC_NACKC                 BIT(4)                          /*!< not acknowledge flag clear */
#define I2C_ADD_STATC_STPDETC               BIT(5)                          /*!< STPDET flag clear */
#define I2C_ADD_STATC_BERRC                 BIT(8)                          /*!< bus error flag clear */
#define I2C_ADD_STATC_LOSTARBC              BIT(9)                          /*!< arbitration Lost flag clear */
#define I2C_ADD_STATC_OUERRC                BIT(10)                         /*!< overrun/underrun flag clear */
#define I2C_ADD_STATC_PECERRC               BIT(11)                         /*!< PEC error flag clear */
#define I2C_ADD_STATC_TIMEOUTC              BIT(12)                         /*!< TIMEOUT flag clear */
#define I2C_ADD_STATC_SMBALTC               BIT(13)                         /*!< SMBus Alert flag clear */

/* I2Cx_PEC */
#define I2C_ADD_PEC_PECV                    BITS(0,7)                       /*!< Packet Error Checking Value that calculated by hardware when PEC is enabled */

/* I2Cx_RDATA */
#define I2C_ADD_RDATA_RDATA                 BITS(0,7)                       /*!< receive data value */

/* I2Cx_TDATA */
#define I2C_ADD_TDATA_TDATA                 BITS(0,7)                       /*!< transmit data value */

/* I2Cx_CTL2 */
#define I2C_ADD_CTL2_ADDM                   BITS(9,15)                      /*!< address bits compare select */

/* constants definitions */
/* define the I2C bit position and its register index offset */
#define I2C_ADD_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define I2C_ADD_REG_VAL(i2cx, offset)       (REG32((i2cx) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define I2C_ADD_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)
#define I2C_ADD_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
        | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define I2C_ADD_REG_VAL2(i2cx, offset)      (REG32((i2cx) + ((uint32_t)(offset) >> 22)))
#define I2C_ADD_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define I2C_ADD_CTL0_REG_OFFSET             ((uint32_t)0x00000000U)         /*!< CTL0 register offset */
#define I2C_ADD_STAT_REG_OFFSET             ((uint32_t)0x00000018U)         /*!< STAT register offset */

/* I2C interrupt flags */
typedef enum {
    I2C_ADD_INT_FLAG_TI = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 1U, I2C_ADD_STAT_REG_OFFSET, 1U),            /*!< transmit interrupt flag */
    I2C_ADD_INT_FLAG_RBNE = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 2U, I2C_ADD_STAT_REG_OFFSET, 2U),          /*!< I2C_ADD_RDATA is not empty during receiving interrupt flag */
    I2C_ADD_INT_FLAG_ADDSEND = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 3U, I2C_ADD_STAT_REG_OFFSET, 3U),       /*!< address received matches in slave mode interrupt flag */
    I2C_ADD_INT_FLAG_NACK = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 4U, I2C_ADD_STAT_REG_OFFSET, 4U),          /*!< not acknowledge interrupt flag */
    I2C_ADD_INT_FLAG_STPDET = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 5U, I2C_ADD_STAT_REG_OFFSET, 5U),        /*!< stop condition detected in slave mode interrupt flag */
    I2C_ADD_INT_FLAG_TC = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 6U, I2C_ADD_STAT_REG_OFFSET, 6U),            /*!< transfer complete in master mode interrupt flag */
    I2C_ADD_INT_FLAG_TCR = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 6U, I2C_ADD_STAT_REG_OFFSET, 7U),           /*!< transfer complete reload interrupt flag */
    I2C_ADD_INT_FLAG_BERR = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 7U, I2C_ADD_STAT_REG_OFFSET, 8U),          /*!< bus error interrupt flag */
    I2C_ADD_INT_FLAG_LOSTARB = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 7U, I2C_ADD_STAT_REG_OFFSET, 9U),       /*!< arbitration lost interrupt flag */
    I2C_ADD_INT_FLAG_OUERR = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 7U, I2C_ADD_STAT_REG_OFFSET, 10U),        /*!< overrun/underrun error in slave mode interrupt flag */
    I2C_ADD_INT_FLAG_PECERR = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 7U, I2C_ADD_STAT_REG_OFFSET, 11U),       /*!< PEC error interrupt flag */
    I2C_ADD_INT_FLAG_TIMEOUT = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 7U, I2C_ADD_STAT_REG_OFFSET, 12U),      /*!< timeout interrupt flag */
    I2C_ADD_INT_FLAG_SMBALT = I2C_ADD_REGIDX_BIT2(I2C_ADD_CTL0_REG_OFFSET, 7U, I2C_ADD_STAT_REG_OFFSET, 13U)        /*!< SMBus Alert interrupt flag */
} i2c_add_interrupt_flag_enum;

/* I2C DMA constants definitions */
#define I2C_ADD_DMA_TRANSMIT                ((uint32_t)0x00000000U)         /*!< I2C transmit data use DMA */
#define I2C_ADD_DMA_RECEIVE                 ((uint32_t)0x00000001U)         /*!< I2C receive data use DMA */

/* I2C interrupt enable or disable */
#define I2C_ADD_INT_ERR                     I2C_ADD_CTL0_ERRIE          /*!< error interrupt enable */
#define I2C_ADD_INT_TC                      I2C_ADD_CTL0_TCIE           /*!< transfer complete interrupt enable */
#define I2C_ADD_INT_STPDET                  I2C_ADD_CTL0_STPDETIE       /*!< stop detection interrupt enable */
#define I2C_ADD_INT_NACK                    I2C_ADD_CTL0_NACKIE         /*!< not acknowledge received interrupt enable */
#define I2C_ADD_INT_ADDM                    I2C_ADD_CTL0_ADDMIE         /*!< address match interrupt enable */
#define I2C_ADD_INT_RBNE                    I2C_ADD_CTL0_RBNEIE         /*!< receive interrupt enable */
#define I2C_ADD_INT_TI                      I2C_ADD_CTL0_TIE            /*!< transmit interrupt enable */

/* I2C transfer direction in master mode */
#define I2C_ADD_MASTER_TRANSMIT             ((uint32_t)0x00000000U)         /*!< I2C master transmit */
#define I2C_ADD_MASTER_RECEIVE              I2C_ADD_CTL1_TRDIR          /*!< I2C master receive */

/* address mode for the I2C slave */
#define I2C_ADD_ADDFORMAT_7BITS             ((uint32_t)0x00000000U)         /*!< address:7 bits */
#define I2C_ADD_ADDFORMAT_10BITS            I2C_ADD_SADDR0_ADDFORMAT    /*!< address:10 bits */

/* the length of filter spikes */
#define FILTER_DISABLE                  ((uint32_t)0x00000000U)         /*!< digital filter is disabled */
#define FILTER_LENGTH_1                 ((uint32_t)0x00000001U)         /*!< digital filter is enabled and filter spikes with a length of up to 1 tI2CCLK */
#define FILTER_LENGTH_2                 ((uint32_t)0x00000002U)         /*!< digital filter is enabled and filter spikes with a length of up to 2 tI2CCLK */
#define FILTER_LENGTH_3                 ((uint32_t)0x00000003U)         /*!< digital filter is enabled and filter spikes with a length of up to 3 tI2CCLK */
#define FILTER_LENGTH_4                 ((uint32_t)0x00000004U)         /*!< digital filter is enabled and filter spikes with a length of up to 4 tI2CCLK */
#define FILTER_LENGTH_5                 ((uint32_t)0x00000005U)         /*!< digital filter is enabled and filter spikes with a length of up to 5 tI2CCLK */
#define FILTER_LENGTH_6                 ((uint32_t)0x00000006U)         /*!< digital filter is enabled and filter spikes with a length of up to 6 tI2CCLK */
#define FILTER_LENGTH_7                 ((uint32_t)0x00000007U)         /*!< digital filter is enabled and filter spikes with a length of up to 7 tI2CCLK */
#define FILTER_LENGTH_8                 ((uint32_t)0x00000008U)         /*!< digital filter is enabled and filter spikes with a length of up to 8 tI2CCLK */
#define FILTER_LENGTH_9                 ((uint32_t)0x00000009U)         /*!< digital filter is enabled and filter spikes with a length of up to 9 tI2CCLK */
#define FILTER_LENGTH_10                ((uint32_t)0x0000000AU)         /*!< digital filter is enabled and filter spikes with a length of up to 10 tI2CCLK */
#define FILTER_LENGTH_11                ((uint32_t)0x0000000BU)         /*!< digital filter is enabled and filter spikes with a length of up to 11 tI2CCLK */
#define FILTER_LENGTH_12                ((uint32_t)0x0000000CU)         /*!< digital filter is enabled and filter spikes with a length of up to 12 tI2CCLK */
#define FILTER_LENGTH_13                ((uint32_t)0x0000000DU)         /*!< digital filter is enabled and filter spikes with a length of up to 13 tI2CCLK */
#define FILTER_LENGTH_14                ((uint32_t)0x0000000EU)         /*!< digital filter is enabled and filter spikes with a length of up to 14 tI2CCLK */
#define FILTER_LENGTH_15                ((uint32_t)0x0000000FU)         /*!< digital filter is enabled and filter spikes with a length of up to 15 tI2CCLK */

/* defines which bits of register ADDRESS[7:1] are compared with an incoming address byte */
#define ADDRESS_BIT1_COMPARE            ((uint32_t)0x00000200U)         /*!< address bit1 needs compare */
#define ADDRESS_BIT2_COMPARE            ((uint32_t)0x00000400U)         /*!< address bit2 needs compare */
#define ADDRESS_BIT3_COMPARE            ((uint32_t)0x00000800U)         /*!< address bit3 needs compare */
#define ADDRESS_BIT4_COMPARE            ((uint32_t)0x00001000U)         /*!< address bit4 needs compare */
#define ADDRESS_BIT5_COMPARE            ((uint32_t)0x00002000U)         /*!< address bit5 needs compare */
#define ADDRESS_BIT6_COMPARE            ((uint32_t)0x00004000U)         /*!< address bit6 needs compare */
#define ADDRESS_BIT7_COMPARE            ((uint32_t)0x00008000U)         /*!< address bit7 needs compare */

/* defines which bits of ADDRESS2[7:1] are compared with an incoming address byte, and which bits are masked (don??t care) */
#define ADDRESS2_NO_MASK                ((uint32_t)0x00000000U)         /*!< no mask, all the bits must be compared */
#define ADDRESS2_MASK_BIT1              ((uint32_t)0x00000001U)         /*!< ADDRESS2[1] is masked, only ADDRESS2[7:2] are compared */
#define ADDRESS2_MASK_BIT1_2            ((uint32_t)0x00000002U)         /*!< ADDRESS2[2:1] is masked, only ADDRESS2[7:3] are compared */
#define ADDRESS2_MASK_BIT1_3            ((uint32_t)0x00000003U)         /*!< ADDRESS2[3:1] is masked, only ADDRESS2[7:4] are compared */
#define ADDRESS2_MASK_BIT1_4            ((uint32_t)0x00000004U)         /*!< ADDRESS2[4:1] is masked, only ADDRESS2[7:5] are compared */
#define ADDRESS2_MASK_BIT1_5            ((uint32_t)0x00000005U)         /*!< ADDRESS2[5:1] is masked, only ADDRESS2[7:6] are compared */
#define ADDRESS2_MASK_BIT1_6            ((uint32_t)0x00000006U)         /*!< ADDRESS2[6:1] is masked, only ADDRESS2[7] are compared */
#define ADDRESS2_MASK_ALL               ((uint32_t)0x00000007U)         /*!< all the ADDRESS2[7:1] bits are masked */

/* idle clock timeout detection */
#define BUSTOA_DETECT_SCL_LOW           ((uint32_t)0x00000000U)         /*!< BUSTOA is used to detect SCL low timeout */
#define BUSTOA_DETECT_IDLE              I2C_ADD_TIMEOUT_TOIDLE      /*!< BUSTOA is used to detect both SCL and SDA high timeout when the bus is idle */

/* I2C flag definitions */
#define I2C_ADD_FLAG_TBE                    I2C_ADD_STAT_TBE                    /*!< I2C_ADD_TDATA is empty during transmitting */
#define I2C_ADD_FLAG_TI                     I2C_ADD_STAT_TI                     /*!< transmit interrupt */
#define I2C_ADD_FLAG_RBNE                   I2C_ADD_STAT_RBNE                   /*!< I2C_ADD_RDATA is not empty during receiving */
#define I2C_ADD_FLAG_ADDSEND                I2C_ADD_STAT_ADDSEND                /*!< address received matches in slave mode */
#define I2C_ADD_FLAG_NACK                   I2C_ADD_STAT_NACK                   /*!< not acknowledge flag */
#define I2C_ADD_FLAG_STPDET                 I2C_ADD_STAT_STPDET                 /*!< STOP condition detected in slave mode */
#define I2C_ADD_FLAG_TC                     I2C_ADD_STAT_TC                     /*!< transfer complete in master mode */
#define I2C_ADD_FLAG_TCR                    I2C_ADD_STAT_TCR                    /*!< transfer complete reload */
#define I2C_ADD_FLAG_BERR                   I2C_ADD_STAT_BERR                   /*!< bus error */
#define I2C_ADD_FLAG_LOSTARB                I2C_ADD_STAT_LOSTARB                /*!< arbitration lost */
#define I2C_ADD_FLAG_OUERR                  I2C_ADD_STAT_OUERR                  /*!< overrun/underrun error in slave mode */
#define I2C_ADD_FLAG_PECERR                 I2C_ADD_STAT_PECERR                 /*!< PEC error */
#define I2C_ADD_FLAG_TIMEOUT                I2C_ADD_STAT_TIMEOUT                /*!< timeout flag */
#define I2C_ADD_FLAG_SMBALT                 I2C_ADD_STAT_SMBALT                 /*!< SMBus Alert */
#define I2C_ADD_FLAG_I2CBSY                 I2C_ADD_STAT_I2CBSY                 /*!< busy flag */
#define I2C_ADD_FLAG_TR                     I2C_ADD_STAT_TR                     /*!< whether the I2C is a transmitter or a receiver in slave mode */

/* function declarations */
/* initialization functions */
/* reset I2C */
void i2c_add_deinit(uint32_t i2c_add_periph);
/* configure the timing parameters */
void i2c_add_timing_config(uint32_t i2c_add_periph, uint32_t psc, uint32_t scl_dely, uint32_t sda_dely);
/* configure digital noise filter */
void i2c_add_digital_noise_filter_config(uint32_t i2c_add_periph, uint32_t filter_length);
/* enable analog noise filter */
void i2c_add_analog_noise_filter_enable(uint32_t i2c_add_periph);
/* disable analog noise filter */
void i2c_add_analog_noise_filter_disable(uint32_t i2c_add_periph);
/* configure the SCL high and low period of clock in master mode */
void i2c_add_master_clock_config(uint32_t i2c_add_periph, uint32_t sclh, uint32_t scll);
/* configure i2c slave address and transfer direction in master mode */
void i2c_add_master_addressing(uint32_t i2c_add_periph, uint32_t address, uint32_t trans_direction);

/* application function declarations */
/* 10-bit address header executes read direction only in master receive mode */
void i2c_add_address10_header_enable(uint32_t i2c_add_periph);
/* 10-bit address header executes complete sequence in master receive mode */
void i2c_add_address10_header_disable(uint32_t i2c_add_periph);
/* enable 10-bit addressing mode in master mode */
void i2c_add_address10_enable(uint32_t i2c_add_periph);
/* disable 10-bit addressing mode in master mode */
void i2c_add_address10_disable(uint32_t i2c_add_periph);
/* enable I2C automatic end mode in master mode */
void i2c_add_automatic_end_enable(uint32_t i2c_add_periph);
/* disable I2C automatic end mode in master mode */
void i2c_add_automatic_end_disable(uint32_t i2c_add_periph);
/* enable the response to a general call */
void i2c_add_slave_response_to_gcall_enable(uint32_t i2c_add_periph);
/* disable the response to a general call */
void i2c_add_slave_response_to_gcall_disable(uint32_t i2c_add_periph);
/* enable to stretch SCL low when data is not ready in slave mode */
void i2c_add_stretch_scl_low_enable(uint32_t i2c_add_periph);
/* disable to stretch SCL low when data is not ready in slave mode */
void i2c_add_stretch_scl_low_disable(uint32_t i2c_add_periph);
/* configure i2c slave address */
void i2c_add_address_config(uint32_t i2c_add_periph, uint32_t address, uint32_t addr_format);
/* define which bits of ADDRESS[7:1] need to compare with the incoming address byte */
void i2c_add_address_bit_compare_config(uint32_t i2c_add_periph, uint32_t compare_bits);
/* disable i2c address in slave mode */
void i2c_add_address_disable(uint32_t i2c_add_periph);
/* configure i2c second slave address */
void i2c_add_second_address_config(uint32_t i2c_add_periph, uint32_t address, uint32_t addr_mask);
/* disable i2c second address in slave mode */
void i2c_add_second_address_disable(uint32_t i2c_add_periph);
/* get received match address in slave mode */
uint32_t i2c_add_recevied_address_get(uint32_t i2c_add_periph);
/* enable slave byte control */
void i2c_add_slave_byte_control_enable(uint32_t i2c_add_periph);
/* disable slave byte control */
void i2c_add_slave_byte_control_disable(uint32_t i2c_add_periph);
/* generate a NACK in slave mode */
void i2c_add_nack_enable(uint32_t i2c_add_periph);
/* generate an ACK in slave mode */
void i2c_add_nack_disable(uint32_t i2c_add_periph);
/* enable wakeup from deep-sleep mode */
void i2c_add_wakeup_from_deepsleep_enable(uint32_t i2c_add_periph);
/* disable wakeup from deep-sleep mode */
void i2c_add_wakeup_from_deepsleep_disable(uint32_t i2c_add_periph);
/* enable I2C */
void i2c_add_enable(uint32_t i2c_add_periph);
/* disable I2C */
void i2c_add_disable(uint32_t i2c_add_periph);
/* generate a START condition on I2C bus */
void i2c_add_start_on_bus(uint32_t i2c_add_periph);
/* generate a STOP condition on I2C bus */
void i2c_add_stop_on_bus(uint32_t i2c_add_periph);
/* I2C transmit data */
void i2c_add_data_transmit(uint32_t i2c_add_periph, uint32_t data);
/* I2C receive data */
uint32_t i2c_add_data_receive(uint32_t i2c_add_periph);
/* enable I2C reload mode */
void i2c_add_reload_enable(uint32_t i2c_add_periph);
/* disable I2C reload mode */
void i2c_add_reload_disable(uint32_t i2c_add_periph);
/* configure number of bytes to be transferred */
void i2c_add_transfer_byte_number_config(uint32_t i2c_add_periph, uint32_t byte_number);
/* enable I2C DMA for transmission or reception */
void i2c_add_dma_enable(uint32_t i2c_add_periph, uint8_t dma);
/* disable I2C DMA for transmission or reception */
void i2c_add_dma_disable(uint32_t i2c_add_periph, uint8_t dma);
/* I2C transfers PEC value */
void i2c_add_pec_transfer(uint32_t i2c_add_periph);
/* enable I2C PEC calculation */
void i2c_add_pec_enable(uint32_t i2c_add_periph);
/* disable I2C PEC calculation */
void i2c_add_pec_disable(uint32_t i2c_add_periph);
/* get packet error checking value */
uint32_t i2c_add_pec_value_get(uint32_t i2c_add_periph);
/* enable SMBus alert */
void i2c_add_smbus_alert_enable(uint32_t i2c_add_periph);
/* disable SMBus alert */
void i2c_add_smbus_alert_disable(uint32_t i2c_add_periph);
/* enable SMBus device default address */
void i2c_add_smbus_default_addr_enable(uint32_t i2c_add_periph);
/* disable SMBus device default address */
void i2c_add_smbus_default_addr_disable(uint32_t i2c_add_periph);
/* enable SMBus host address */
void i2c_add_smbus_host_addr_enable(uint32_t i2c_add_periph);
/* disable SMBus host address */
void i2c_add_smbus_host_addr_disable(uint32_t i2c_add_periph);
/* enable extended clock timeout detection */
void i2c_add_extented_clock_timeout_enable(uint32_t i2c_add_periph);
/* disable extended clock timeout detection */
void i2c_add_extented_clock_timeout_disable(uint32_t i2c_add_periph);
/* enable clock timeout detection */
void i2c_add_clock_timeout_enable(uint32_t i2c_add_periph);
/* disable clock timeout detection */
void i2c_add_clock_timeout_disable(uint32_t i2c_add_periph);
/* configure bus timeout B */
void i2c_add_bus_timeout_b_config(uint32_t i2c_add_periph, uint32_t timeout);
/* configure bus timeout A */
void i2c_add_bus_timeout_a_config(uint32_t i2c_add_periph, uint32_t timeout);
/* configure idle clock timeout detection */
void i2c_add_idle_clock_timeout_config(uint32_t i2c_add_periph, uint32_t timeout);

/* interrupt & flag functions */
/* get I2C flag status */
FlagStatus i2c_add_flag_get(uint32_t i2c_add_periph, uint32_t flag);
/* clear I2C flag status */
void i2c_add_flag_clear(uint32_t i2c_add_periph, uint32_t flag);
/* enable I2C interrupt */
void i2c_add_interrupt_enable(uint32_t i2c_add_periph, uint32_t interrupt);
/* disable I2C interrupt */
void i2c_add_interrupt_disable(uint32_t i2c_add_periph, uint32_t interrupt);
/* get I2C interrupt flag status */
FlagStatus i2c_add_interrupt_flag_get(uint32_t i2c_add_periph, i2c_add_interrupt_flag_enum int_flag);
/* clear I2C interrupt flag status */
void i2c_add_interrupt_flag_clear(uint32_t i2c_add_periph, i2c_add_interrupt_flag_enum int_flag);

#endif /* GD32F5XX_I2C_ADD_H */
