/*!
    \file    gd32h7xx_spi.h
    \brief   definitions for the SPI

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

#ifndef GD32H7XX_SPI_H
#define GD32H7XX_SPI_H

#include "gd32h7xx.h"

/* SPIx(x=0,1,2,3,4,5) definitions */
#define SPI0                            (SPI_BASE + 0x0000F800U)
#define SPI1                            SPI_BASE
#define SPI2                            (SPI_BASE + 0x00000400U)
#define SPI3                            (SPI_BASE + 0x0000FC00U)
#define SPI4                            (SPI_BASE + 0x00011800U)
#define SPI5                            (SPI_BASE + 0x00010000U)

/* SPI registers definitions */
#define SPI_CTL0(spix)                  REG32((spix) + 0x00U)                   /*!< SPI control register 0 */
#define SPI_CTL1(spix)                  REG32((spix) + 0x04U)                   /*!< SPI control register 1*/
#define SPI_CFG0(spix)                  REG32((spix) + 0x08U)                   /*!< SPI configuration register 0 */
#define SPI_CFG1(spix)                  REG32((spix) + 0x0CU)                   /*!< SPI configuration register 1 */
#define SPI_INT(spix)                   REG32((spix) + 0x10U)                   /*!< SPI interrupt register */
#define SPI_STAT(spix)                  REG32((spix) + 0x14U)                   /*!< SPI status register */
#define SPI_STATC(spix)                 REG32((spix) + 0x18U)                   /*!< SPI interrupt/status flags clear register */
#define SPI_TDATA(spix)                 REG32((spix) + 0x20U)                   /*!< SPI data transfer register */
#define SPI_RDATA(spix)                 REG32((spix) + 0x30U)                   /*!< SPI data receive register */
#define SPI_CRCPOLY(spix)               REG32((spix) + 0x40U)                   /*!< SPI CRC polynomial register */
#define SPI_TCRC(spix)                  REG32((spix) + 0x44U)                   /*!< SPI TX CRC register */
#define SPI_RCRC(spix)                  REG32((spix) + 0x48U)                   /*!< SPI RX CRC register */
#define SPI_URDATA(spix)                REG32((spix) + 0x4CU)                   /*!< SPI underrun data register */
#define SPI_I2SCTL(spix)                REG32((spix) + 0x50U)                   /*!< I2S control register */
#define SPI_QCTL(spix)                  REG32((spix) + 0x80U)                   /*!< quad_SPI mode control register(for SPI3/4) */
#define SPI_RXDLYCK(spix)               REG32((spix) + 0xFCU)                   /*!< SPI receive clock delay register */

/* bits definitions */
/* SPI_CTL0 */
#define SPI_CTL0_SPIEN                  BIT(0)                                  /*!< SPI enable */
#define SPI_CTL0_MASP                   BIT(8)                                  /*!< the master is suspended automatically in receive mode */
#define SPI_CTL0_MSTART                 BIT(9)                                  /*!< master start transfer */
#define SPI_CTL0_MSPDR                  BIT(10)                                 /*!< suspend request in SPI master mode */
#define SPI_CTL0_NSSI                   BIT(12)                                 /*!< the input level to internal NSS signal */
#define SPI_CTL0_CRCFS                  BIT(13)                                 /*!< full scale CRC polynomial configuration */
#define SPI_CTL0_RXCRCI                 BIT(14)                                 /*!< the receiver CRC initialization configuration */
#define SPI_CTL0_TXCRCI                 BIT(15)                                 /*!< the transmitter CRC initialization configuration */
#define SPI_CTL0_IOAFEN                 BIT(16)                                 /*!< related IOs AF configuration enable */

/* SPI_CFG0 */
#define SPI_CFG0_DZ                     BITS(0,4)                               /*!< data size */
#define SPI_CFG0_FIFOLVL                BITS(5,8)                               /*!< FIFO threshold level */
#define SPI_CFG0_TXUROP                 BITS(9,10)                              /*!< operation of slave transmitter when underrun detected */
#define SPI_CFG0_TXURDT                 BITS(11,12)                             /*!< detection of underrun error at slave transmitter */
#define SPI_CFG0_DMAREN                 BIT(14)                                 /*!< receive buffer DMA enable */
#define SPI_CFG0_DMATEN                 BIT(15)                                 /*!< transmit buffer DMA enable */
#define SPI_CFG0_CRCSZ                  BITS(16,20)                             /*!< CRC size */
#define SPI_CFG0_CRCEN                  BIT(22)                                 /*!< CRC calculation enable */
#define SPI_CFG0_BYTEN                  BIT(23)                                 /*!< byte access enable */
#define SPI_CFG0_WORDEN                 BIT(24)                                 /*!< word access enable */
#define SPI_CFG0_PSC                    BITS(28,30)                             /*!< master clock prescaler selection */

/* SPI_CFG1 */
#define SPI_CFG1_MSSD                   BITS(0,3)                               /*!< delay between active edge of NSS and start transfer or receive data in SPI master mode */
#define SPI_CFG1_MDFD                   BITS(4,7)                               /*!< delay between the data frames in SPI master mode */
#define SPI_CFG1_SWPMIO                 BIT(15)                                 /*!< MOSI and MISO pin swap */
#define SPI_CFG1_RO                     BIT(16)                                 /*!< receive only */
#define SPI_CFG1_BDOEN                  BIT(17)                                 /*!< bidirectional transmit output enable */
#define SPI_CFG1_BDEN                   BIT(18)                                 /*!< bidirectional enable */
#define SPI_CFG1_TMOD                   BIT(21)                                 /*!< SPI TI mode enable */
#define SPI_CFG1_MSTMOD                 BIT(22)                                 /*!< Master mode enable */
#define SPI_CFG1_LF                     BIT(23)                                 /*!< LSB first mode */
#define SPI_CFG1_CKPH                   BIT(24)                                 /*!< clock phase selection */
#define SPI_CFG1_CKPL                   BIT(25)                                 /*!< clock polarity selection */
#define SPI_CFG1_NSSIM                  BIT(26)                                 /*!< NSS input signal manage mode */
#define SPI_CFG1_NSSIOPL                BIT(28)                                 /*!< NSS pin input/output polarity selection */
#define SPI_CFG1_NSSDRV                 BIT(29)                                 /*!< NSS pin output enable in master mode */
#define SPI_CFG1_NSSCTL                 BIT(30)                                 /*!< NSS pin output control in master mode */
#define SPI_CFG1_AFCTL                  BIT(31)                                 /*!< AF GPIOs control */

/* SPI_INT */
#define SPI_INT_RPIE                    BIT(0)                                  /*!< RP interrupt enable */
#define SPI_INT_TPIE                    BIT(1)                                  /*!< TP interrupt enable */
#define SPI_INT_DPIE                    BIT(2)                                  /*!< DP interrupt enable */
#define SPI_INT_ESTCIE                  BIT(3)                                  /*!< end of transfer or suspend or TXFIFO clear interrupt enable */
#define SPI_INT_TXFIE                   BIT(4)                                  /*!< transmission filled interrupt enable */
#define SPI_INT_TXUREIE                 BIT(5)                                  /*!< underrun error interrupt enable */
#define SPI_INT_RXOREIE                 BIT(6)                                  /*!< overrun error interrupt enable */
#define SPI_INT_CRCERIE                 BIT(7)                                  /*!< CRC error interrupt enable */
#define SPI_INT_FEIE                    BIT(8)                                  /*!< TI frame error interrupt enable */
#define SPI_INT_CONFEIE                 BIT(9)                                  /*!< SPI configuration error interrupt enable */
#define SPI_INT_TXSERFIE                BIT(10)                                 /*!< TXSER reload interrupt enable */

/* SPI_STAT */
#define SPI_STAT_RP                     BIT(0)                                  /*!< RxFIFO packet space available flag */
#define SPI_STAT_TP                     BIT(1)                                  /*!< TxFIFO packet space available flag */
#define SPI_STAT_DP                     BIT(2)                                  /*!< duplex packet */
#define SPI_STAT_ET                     BIT(3)                                  /*!< End of transmission/reception flag */
#define SPI_STAT_TXF                    BIT(4)                                  /*!< TxFIFO transmission has been filled */
#define SPI_STAT_TXURERR                BIT(5)                                  /*!< transmission underrun error */
#define SPI_STAT_RXORERR                BIT(6)                                  /*!< reception overrun error */
#define SPI_STAT_CRCERR                 BIT(7)                                  /*!< SPI CRC error */
#define SPI_STAT_FERR                   BIT(8)                                  /*!< SPI TI format error */
#define SPI_STAT_CONFERR                BIT(9)                                  /*!< SPI configuration error */
#define SPI_STAT_TXSERF                 BIT(10)                                 /*!< The additional SPI data has been reloaded */
#define SPI_STAT_SPD                    BIT(11)                                 /*!< suspend flsg */
#define SPI_STAT_TC                     BIT(12)                                 /*!< TxFIFO transmission complete flag */
#define SPI_STAT_RPLVL                  BITS(13,14)                             /*!< RxFIFO packing level */
#define SPI_STAT_RWNE                   BIT(15)                                 /*!< the word of RXFIFO is not empty */
#define SPI_STAT_CTXSIZE                BITS(16,31)                             /*!< the number of data frames remaining in the TXSIZE session */

/* SPI_STATC */
#define SPI_STATC_ETC                   BIT(3)                                  /*!< Clear the end of transmission/reception flag */
#define SPI_STATC_TXFC                  BIT(4)                                  /*!< Clear the TxFIFO transmission filled flag */
#define SPI_STATC_TXURERRC              BIT(5)                                  /*!< clear the transmission underrun error flag */
#define SPI_STATC_RXORERRC              BIT(6)                                  /*!< clear the reception overrun error flag */
#define SPI_STATC_CRCERRC               BIT(7)                                  /*!< clear the CRC error flag */
#define SPI_STATC_FERRC                 BIT(8)                                  /*!< clear the SPI TI format error flag */
#define SPI_STATC_CONFERRC              BIT(9)                                  /*!< clear the configuration error flag */
#define SPI_STATC_TXSERFC               BIT(10)                                 /*!< clear the TXSERF flag */
#define SPI_STATC_SPDC                  BIT(11)                                 /*!< clear the suspend flag */

/* SPI_TDATA */
#define SPI_TDATA_TDATA                 BITS(0,31)                              /*!< data transfer register */

/* SPI_RDATA */
#define SPI_RDATA_RDATA                 BITS(0,31)                              /*!< data receive register */

/* SPI_CRCPOLY */
#define SPI_CRCPOLY_CRCPOLY             BITS(0,31)                              /*!< CRC polynomial register */

/* SPI_TCRC */
#define SPI_TCRC_TCRC                   BITS(0,31)                              /*!< Tx CRC register */

/* SPI_RCRC */
#define SPI_RCRC_RCRC                   BITS(0,31)                              /*!< Rx CRC register */

/* SPI_URDATA */
#define SPI_URDATA_URDATA               BITS(0,31)                              /*!< transmission underrun data at slave mode */

/* SPI_I2SCTL */
#define SPI_I2SCTL_CHLEN                BIT(0)                                  /*!< channel length */
#define SPI_I2SCTL_DTLEN                BITS(1,2)                               /*!< data length */
#define SPI_I2SCTL_CKPL                 BIT(3)                                  /*!< idle state clock polarity */
#define SPI_I2SCTL_I2SSTD               BITS(4,5)                               /*!< I2S standard selection */
#define SPI_I2SCTL_PCMSMOD              BIT(7)                                  /*!< PCM frame synchronization mode */
#define SPI_I2SCTL_I2SOPMOD             BITS(8,9)                               /*!< I2S operation mode */
#define SPI_I2SCTL_I2SEN                BIT(10)                                 /*!< I2S enable */
#define SPI_I2SCTL_I2SSEL               BIT(11)                                 /*!< I2S mode selection */
#define SPI_I2SCTL_DIV                  BITS(16,23)                             /*!< dividing factor for the prescaler */
#define SPI_I2SCTL_OF                   BIT(24)                                 /*!< odd factor for the prescaler */
#define SPI_I2SCTL_MCKOEN               BIT(25)                                 /*!< I2S_MCK output enable */
#define SPI_I2SCTL_I2SCH                BIT(31)                                 /*!< I2S Channel side */

/* SPI_QCTL(only for SPI3/4) */
#define SPI_QCTL_QMOD                   BIT(0)                                  /*!< quad-SPI mode enable */
#define SPI_QCTL_QRD                    BIT(1)                                  /*!< quad-SPI mode read select */
#define SPI_QCTL_IO23_DRV               BIT(2)                                  /*!< drive SPI_IO2 and SPI_IO3 enable */

/* SPI_RXDLYCK */
#define SPI_RXDLYCK_SRXD                BITS(0,4)                               /*!< slave mode receive clock delay units*/
#define SPI_RXDLYCK_SRXDEN              BIT(5)                                  /*!< slave mode receive clock delay enable*/
#define SPI_RXDLYCK_MRXD                BITS(6,10)                              /*!< master mode receive clock delay units*/
#define SPI_RXDLYCK_MRXDEN              BIT(11)                                 /*!< master mode receive clock delay enable*/

/* constants definitions */
/* SPI and I2S parameter struct definitions */
typedef struct
{
    uint32_t device_mode;                                                       /*!< SPI master or slave */
    uint32_t trans_mode;                                                        /*!< SPI transtype */
    uint32_t data_size;                                                         /*!< SPI data frame size */
    uint32_t nss;                                                               /*!< SPI NSS control by handware or software */
    uint32_t endian;                                                            /*!< SPI big endian or little endian */
    uint32_t clock_polarity_phase;                                              /*!< SPI clock phase and polarity */
    uint32_t prescale;                                                          /*!< SPI prescale factor */
}spi_parameter_struct;

/* SPI suspend in receive mode */
#define SPI_AUTO_SUSPEND                SPI_CTL0_MASP                           /*!< until the overrun condition is reached, the SPI stream is suspended in the full RxFIFO state */
#define SPI_CONTINUOUS                  ((uint32_t)0x00000000U)                 /*!< SPI stream/clock generation is continuous whether or not an overrun occurs */

/* SPI master start transfer */
#define SPI_TRANS_START                 SPI_CTL0_MSTART                         /*!< the master transmission is occurring, or has been temporarily suspended by automatic suspend */
#define SPI_TRANS_IDLE                  ((uint32_t)0x00000000U)                 /*!< the master transfer is idle status */

/* SPI NSS input level */
#define SPI_NSS_LEVEL_HIGH              SPI_CTL0_NSSI                           /*!< NSS pin is pulled high */
#define SPI_NSS_LEVEL_LOW               ((uint32_t)0x00000000U)                 /*!< NSS pin is pulled low */

/* SPI TCRC init pattern */
#define SPI_TCRC_INIT_1                 SPI_CTL0_TXCRCI                         /*!< use all 1 pattern */
#define SPI_TCRC_INIT_0                 ((uint32_t)0x00000000U)                 /*!< use all 0 pattern */

/* SPI RCRC init pattern */
#define SPI_RCRC_INIT_1                 SPI_CTL0_RXCRCI                         /*!< use all 1 pattern */
#define SPI_RCRC_INIT_0                 ((uint32_t)0x00000000U)                 /*!< use all 0 pattern */

/* SPI data frame size */
#define CFG0_DZ(regval)                 (BITS(0,4) & ((uint32_t)(regval) << 0))
#define SPI_DATASIZE_4BIT               CFG0_DZ(3)                              /*!< SPI data frame size is 4-bit */
#define SPI_DATASIZE_5BIT               CFG0_DZ(4)                              /*!< SPI data frame size is 5-bit */
#define SPI_DATASIZE_6BIT               CFG0_DZ(5)                              /*!< SPI data frame size is 6-bit */
#define SPI_DATASIZE_7BIT               CFG0_DZ(6)                              /*!< SPI data frame size is 7-bit */
#define SPI_DATASIZE_8BIT               CFG0_DZ(7)                              /*!< SPI data frame size is 8-bit */
#define SPI_DATASIZE_9BIT               CFG0_DZ(8)                              /*!< SPI data frame size is 9-bit */
#define SPI_DATASIZE_10BIT              CFG0_DZ(9)                              /*!< SPI data frame size is 10-bit */
#define SPI_DATASIZE_11BIT              CFG0_DZ(10)                             /*!< SPI data frame size is 11-bit */
#define SPI_DATASIZE_12BIT              CFG0_DZ(11)                             /*!< SPI data frame size is 12-bit */
#define SPI_DATASIZE_13BIT              CFG0_DZ(12)                             /*!< SPI data frame size is 13-bit */
#define SPI_DATASIZE_14BIT              CFG0_DZ(13)                             /*!< SPI data frame size is 14-bit */
#define SPI_DATASIZE_15BIT              CFG0_DZ(14)                             /*!< SPI data frame size is 15-bit */
#define SPI_DATASIZE_16BIT              CFG0_DZ(15)                             /*!< SPI data frame size is 16-bit */
#define SPI_DATASIZE_17BIT              CFG0_DZ(16)                             /*!< SPI data frame size is 17-bit */
#define SPI_DATASIZE_18BIT              CFG0_DZ(17)                             /*!< SPI data frame size is 18-bit */
#define SPI_DATASIZE_19BIT              CFG0_DZ(18)                             /*!< SPI data frame size is 19-bit */
#define SPI_DATASIZE_20BIT              CFG0_DZ(19)                             /*!< SPI data frame size is 20-bit */
#define SPI_DATASIZE_21BIT              CFG0_DZ(20)                             /*!< SPI data frame size is 21-bit */
#define SPI_DATASIZE_22BIT              CFG0_DZ(21)                             /*!< SPI data frame size is 22-bit */
#define SPI_DATASIZE_23BIT              CFG0_DZ(22)                             /*!< SPI data frame size is 23-bit */
#define SPI_DATASIZE_24BIT              CFG0_DZ(23)                             /*!< SPI data frame size is 24-bit */
#define SPI_DATASIZE_25BIT              CFG0_DZ(24)                             /*!< SPI data frame size is 25-bit */
#define SPI_DATASIZE_26BIT              CFG0_DZ(25)                             /*!< SPI data frame size is 26-bit */
#define SPI_DATASIZE_27BIT              CFG0_DZ(26)                             /*!< SPI data frame size is 27-bit */
#define SPI_DATASIZE_28BIT              CFG0_DZ(27)                             /*!< SPI data frame size is 28-bit */
#define SPI_DATASIZE_29BIT              CFG0_DZ(28)                             /*!< SPI data frame size is 29-bit */
#define SPI_DATASIZE_30BIT              CFG0_DZ(29)                             /*!< SPI data frame size is 30-bit */
#define SPI_DATASIZE_31BIT              CFG0_DZ(30)                             /*!< SPI data frame size is 31-bit */
#define SPI_DATASIZE_32BIT              CFG0_DZ(31)                             /*!< SPI data frame size is 32-bit */

/* SPI FIFO threshold level */
#define CFG0_FIFOLVL(regval)            (BITS(5,8) & ((uint32_t)(regval) << 5))
#define SPI_FIFO_TH_01DATA              CFG0_FIFOLVL(0)                         /*!< set FIFO threshold level = 1-data frame */
#define SPI_FIFO_TH_02DATA              CFG0_FIFOLVL(1)                         /*!< set FIFO threshold level = 2-data frame */
#define SPI_FIFO_TH_03DATA              CFG0_FIFOLVL(2)                         /*!< set FIFO threshold level = 3-data frame */
#define SPI_FIFO_TH_04DATA              CFG0_FIFOLVL(3)                         /*!< set FIFO threshold level = 4-data frame */
#define SPI_FIFO_TH_05DATA              CFG0_FIFOLVL(4)                         /*!< set FIFO threshold level = 5-data frame */
#define SPI_FIFO_TH_06DATA              CFG0_FIFOLVL(5)                         /*!< set FIFO threshold level = 6-data frame */
#define SPI_FIFO_TH_07DATA              CFG0_FIFOLVL(6)                         /*!< set FIFO threshold level = 7-data frame */
#define SPI_FIFO_TH_08DATA              CFG0_FIFOLVL(7)                         /*!< set FIFO threshold level = 8-data frame */
#define SPI_FIFO_TH_09DATA              CFG0_FIFOLVL(8)                         /*!< set FIFO threshold level = 9-data frame */
#define SPI_FIFO_TH_10DATA              CFG0_FIFOLVL(9)                         /*!< set FIFO threshold level = 10-data frame */
#define SPI_FIFO_TH_11DATA              CFG0_FIFOLVL(10)                        /*!< set FIFO threshold level = 11-data frame */
#define SPI_FIFO_TH_12DATA              CFG0_FIFOLVL(11)                        /*!< set FIFO threshold level = 12-data frame */
#define SPI_FIFO_TH_13DATA              CFG0_FIFOLVL(12)                        /*!< set FIFO threshold level = 13-data frame */
#define SPI_FIFO_TH_14DATA              CFG0_FIFOLVL(13)                        /*!< set FIFO threshold level = 14-data frame */
#define SPI_FIFO_TH_15DATA              CFG0_FIFOLVL(14)                        /*!< set FIFO threshold level = 15-data frame */
#define SPI_FIFO_TH_16DATA              CFG0_FIFOLVL(15)                        /*!< set FIFO threshold level = 16-data frame */

/* SPI slave transmitter underrun detected operation */
#define CFG0_TXUROP(regval)             (BITS(9,10) & ((uint32_t)(regval) << 9))
#define SPI_CONFIG_REGISTER_PATTERN     CFG0_TXUROP(0)                          /*!< slave send a constant value defined by the SPI_URDATA register */
#define SPI_CONFIG_LAST_RECEIVED        CFG0_TXUROP(1)                          /*!< slave send the data frame received from master lastly */
#define SPI_CONFIG_LAST_TRANSMITTED     CFG0_TXUROP(2)                          /*!< Slave send the data frame which is lastly transmitted by itself */

/* SPI slave transmitter underrun detected config */
#define CFG0_TXURDT(regval)             (BITS(11,12) & ((uint32_t)(regval) << 11))
#define SPI_DETECT_BEGIN_DATA_FRAME     CFG0_TXURDT(0)                          /*!< underrun detected at start of data frame (no bit 1 protection) */
#define SPI_DETECT_END_DATA_FRAME       CFG0_TXURDT(1)                          /*!< underrun detected at end of last data frame */
#define SPI_DETECT_BEGIN_ACTIVE_NSS     CFG0_TXURDT(2)                          /*!< underrun detected at start of NSS signal */

/* SPI CRC size */
#define CFG0_CRCSZ(regval)              (BITS(16,20) & ((uint32_t)(regval) << 16))
#define SPI_CRCSIZE_4BIT                CFG0_CRCSZ(3)                           /*!< SPI crc size is 4-bit */
#define SPI_CRCSIZE_5BIT                CFG0_CRCSZ(4)                           /*!< SPI crc size is 5-bit */
#define SPI_CRCSIZE_6BIT                CFG0_CRCSZ(5)                           /*!< SPI crc size is 6-bit */
#define SPI_CRCSIZE_7BIT                CFG0_CRCSZ(6)                           /*!< SPI crc size is 7-bit */
#define SPI_CRCSIZE_8BIT                CFG0_CRCSZ(7)                           /*!< SPI crc size is 8-bit */
#define SPI_CRCSIZE_9BIT                CFG0_CRCSZ(8)                           /*!< SPI crc size is 9-bit */
#define SPI_CRCSIZE_10BIT               CFG0_CRCSZ(9)                           /*!< SPI crc size is 10-bit */
#define SPI_CRCSIZE_11BIT               CFG0_CRCSZ(10)                          /*!< SPI crc size is 11-bit */
#define SPI_CRCSIZE_12BIT               CFG0_CRCSZ(11)                          /*!< SPI crc size is 12-bit */
#define SPI_CRCSIZE_13BIT               CFG0_CRCSZ(12)                          /*!< SPI crc size is 13-bit */
#define SPI_CRCSIZE_14BIT               CFG0_CRCSZ(13)                          /*!< SPI crc size is 14-bit */
#define SPI_CRCSIZE_15BIT               CFG0_CRCSZ(14)                          /*!< SPI crc size is 15-bit */
#define SPI_CRCSIZE_16BIT               CFG0_CRCSZ(15)                          /*!< SPI crc size is 16-bit */
#define SPI_CRCSIZE_17BIT               CFG0_CRCSZ(16)                          /*!< SPI crc size is 17-bit */
#define SPI_CRCSIZE_18BIT               CFG0_CRCSZ(17)                          /*!< SPI crc size is 18-bit */
#define SPI_CRCSIZE_19BIT               CFG0_CRCSZ(18)                          /*!< SPI crc size is 19-bit */
#define SPI_CRCSIZE_20BIT               CFG0_CRCSZ(19)                          /*!< SPI crc size is 20-bit */
#define SPI_CRCSIZE_21BIT               CFG0_CRCSZ(20)                          /*!< SPI crc size is 21-bit */
#define SPI_CRCSIZE_22BIT               CFG0_CRCSZ(21)                          /*!< SPI crc size is 22-bit */
#define SPI_CRCSIZE_23BIT               CFG0_CRCSZ(22)                          /*!< SPI crc size is 23-bit */
#define SPI_CRCSIZE_24BIT               CFG0_CRCSZ(23)                          /*!< SPI crc size is 24-bit */
#define SPI_CRCSIZE_25BIT               CFG0_CRCSZ(24)                          /*!< SPI crc size is 25-bit */
#define SPI_CRCSIZE_26BIT               CFG0_CRCSZ(25)                          /*!< SPI crc size is 26-bit */
#define SPI_CRCSIZE_27BIT               CFG0_CRCSZ(26)                          /*!< SPI crc size is 27-bit */
#define SPI_CRCSIZE_28BIT               CFG0_CRCSZ(27)                          /*!< SPI crc size is 28-bit */
#define SPI_CRCSIZE_29BIT               CFG0_CRCSZ(28)                          /*!< SPI crc size is 29-bit */
#define SPI_CRCSIZE_30BIT               CFG0_CRCSZ(29)                          /*!< SPI crc size is 30-bit */
#define SPI_CRCSIZE_31BIT               CFG0_CRCSZ(30)                          /*!< SPI crc size is 31-bit */
#define SPI_CRCSIZE_32BIT               CFG0_CRCSZ(31)                          /*!< SPI crc size is 32-bit */

/* SPI clock prescale factor */
#define CFG0_PSC(regval)                (BITS(28,30) & ((uint32_t)(regval) << 28))
#define SPI_PSC_2                       CFG0_PSC(0)                             /*!< SPI clock prescale factor is 2 */
#define SPI_PSC_4                       CFG0_PSC(1)                             /*!< SPI clock prescale factor is 4 */
#define SPI_PSC_8                       CFG0_PSC(2)                             /*!< SPI clock prescale factor is 8 */
#define SPI_PSC_16                      CFG0_PSC(3)                             /*!< SPI clock prescale factor is 16 */
#define SPI_PSC_32                      CFG0_PSC(4)                             /*!< SPI clock prescale factor is 32 */
#define SPI_PSC_64                      CFG0_PSC(5)                             /*!< SPI clock prescale factor is 64 */
#define SPI_PSC_128                     CFG0_PSC(6)                             /*!< SPI clock prescale factor is 128 */
#define SPI_PSC_256                     CFG0_PSC(7)                             /*!< SPI clock prescale factor is 256 */

/* SPI NSS idleness delay */
#define CFG1_MSSD(regval)               (BITS(0,3) & ((uint32_t)(regval) << 0))
#define SPI_NSS_IDLENESS_00CYCLE        CFG1_MSSD(0)                            /*!< no delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_01CYCLE        CFG1_MSSD(1)                            /*!< 1 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_02CYCLE        CFG1_MSSD(2)                            /*!< 2 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_03CYCLE        CFG1_MSSD(3)                            /*!< 3 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_04CYCLE        CFG1_MSSD(4)                            /*!< 4 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_05CYCLE        CFG1_MSSD(5)                            /*!< 5 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_06CYCLE        CFG1_MSSD(6)                            /*!< 6 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_07CYCLE        CFG1_MSSD(7)                            /*!< 7 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_08CYCLE        CFG1_MSSD(8)                            /*!< 8 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_09CYCLE        CFG1_MSSD(9)                            /*!< 9 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_10CYCLE        CFG1_MSSD(10)                           /*!< 10 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_11CYCLE        CFG1_MSSD(11)                           /*!< 11 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_12CYCLE        CFG1_MSSD(12)                           /*!< 12 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_13CYCLE        CFG1_MSSD(13)                           /*!< 13 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_14CYCLE        CFG1_MSSD(14)                           /*!< 14 clock cycle delay between active edge of NSS and transmittion */
#define SPI_NSS_IDLENESS_15CYCLE        CFG1_MSSD(15)                           /*!< 15 clock cycle delay between active edge of NSS and transmittion */

/* SPI master data frame delay */
#define CFG1_MDFD(regval)               (BITS(4,7) & ((uint32_t)(regval) << 4))
#define SPI_DATA_IDLENESS_00CYCLE       CFG1_MDFD(0)                            /*!< no delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_01CYCLE       CFG1_MDFD(1)                            /*!< 1 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_02CYCLE       CFG1_MDFD(2)                            /*!< 2 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_03CYCLE       CFG1_MDFD(3)                            /*!< 3 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_04CYCLE       CFG1_MDFD(4)                            /*!< 4 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_05CYCLE       CFG1_MDFD(5)                            /*!< 5 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_06CYCLE       CFG1_MDFD(6)                            /*!< 6 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_07CYCLE       CFG1_MDFD(7)                            /*!< 7 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_08CYCLE       CFG1_MDFD(8)                            /*!< 8 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_09CYCLE       CFG1_MDFD(9)                            /*!< 9 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_10CYCLE       CFG1_MDFD(10)                           /*!< 10 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_11CYCLE       CFG1_MDFD(11)                           /*!< 11 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_12CYCLE       CFG1_MDFD(12)                           /*!< 12 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_13CYCLE       CFG1_MDFD(13)                           /*!< 13 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_14CYCLE       CFG1_MDFD(14)                           /*!< 14 clock cycle delay between data frames in SPI master mode */
#define SPI_DATA_IDLENESS_15CYCLE       CFG1_MDFD(15)                           /*!< 15 clock cycle delay between data frames in SPI master mode */

/* SPI IO swap */
#define SPI_IO_SWAP                     SPI_CFG1_SWPMIO                         /*!< SPI MOSI and MISO swap */
#define SPI_IO_NORMAL                   (~SPI_CFG1_SWPMIO)                      /*!< SPI MOSI and MISO no swap */

/* SPI bidirectional transfer direction */
#define SPI_BIDIRECTIONAL_TRANSMIT      SPI_CFG1_BDOEN                          /*!< SPI work in transmit-only mode */
#define SPI_BIDIRECTIONAL_RECEIVE       (~SPI_CFG1_BDOEN)                       /*!< SPI work in receive-only mode */

/* SPI transmit type */
#define SPI_TRANSMODE_FULLDUPLEX        ((uint32_t)0x00000000U)                 /*!< SPI receive and send data at fullduplex communication */
#define SPI_TRANSMODE_RECEIVEONLY       SPI_CFG1_RO                             /*!< SPI only receive data */
#define SPI_TRANSMODE_BDRECEIVE         SPI_CFG1_BDEN                           /*!< bidirectional receive data */
#define SPI_TRANSMODE_BDTRANSMIT        (SPI_CFG1_BDEN | SPI_CFG1_BDOEN)        /*!< bidirectional transmit data*/

/* SPI mode definitions */
#define SPI_MASTER                      SPI_CFG1_MSTMOD                         /*!< SPI as master */
#define SPI_SLAVE                       ((uint32_t)0x00000000U)                 /*!< SPI as slave */

/* SPI transmit way */
#define SPI_ENDIAN_MSB                  ((uint32_t)0x00000000U)                 /*!< SPI transmit way is big endian: transmit MSB first */
#define SPI_ENDIAN_LSB                  SPI_CFG1_LF                             /*!< SPI transmit way is little endian: transmit LSB first */

/* SPI clock phase and polarity */
#define SPI_CK_PL_LOW_PH_1EDGE          ((uint32_t)0x00000000U)                 /*!< SPI clock polarity is low level and phase is first edge */
#define SPI_CK_PL_HIGH_PH_1EDGE         SPI_CFG1_CKPL                           /*!< SPI clock polarity is high level and phase is first edge */
#define SPI_CK_PL_LOW_PH_2EDGE          SPI_CFG1_CKPH                           /*!< SPI clock polarity is low level and phase is second edge */
#define SPI_CK_PL_HIGH_PH_2EDGE         (SPI_CFG1_CKPL | SPI_CFG1_CKPH)         /*!< SPI clock polarity is high level and phase is second edge */

/* SPI NSS control mode */
#define SPI_NSS_SOFT                    SPI_CFG1_NSSIM                          /*!< SPI NSS control by sofrware */
#define SPI_NSS_HARD                    ((uint32_t)0x00000000U)                 /*!< SPI NSS control by hardware */

/* SPI NSS polarity */
#define SPI_NSS_POLARITY_HIGH           SPI_CFG1_NSSIOPL                        /*!< SPI NSS high level is active */
#define SPI_NSS_POLARITY_LOW            ((uint32_t)0x00000000U)                 /*!< SPI NSS low level is active */

/* SPI NSS output control */
#define SPI_NSS_INVALID_PULSE           SPI_CFG1_NSSCTL                         /*!< SPI data frames are interleaved with NSS invalid pulses */
#define SPI_NSS_HOLD_UNTIL_TRANS_END    ((uint32_t)0x00000000U)                 /*!< SPI NSS remains active level until data transfer complete */

/* SPI af gpio control */
#define SPI_GPIO_CONTROL                SPI_CFG1_AFCTL                          /*!< SPI always control all associated GPIO */
#define SPI_GPIO_FREE                   ((uint32_t)0x00000000U)                 /*!< SPI do not control GPIO when disabled */

/* SPI RxFIFO packing level */
#define STAT_RPLVL(regval)              (BITS(13,14) & ((uint32_t)(regval) << 13))
#define SPI_RX_FIFO_0PACKET             STAT_RPLVL(0)                           /*!< no frame or 4 frames stored in RxFIFO */
#define SPI_RX_FIFO_1PACKET             STAT_RPLVL(1)                           /*!< 1 frame stored in RxFIFO */
#define SPI_RX_FIFO_2PACKET             STAT_RPLVL(2)                           /*!< 2 frames stored in RxFIFO */
#define SPI_RX_FIFO_3PACKET             STAT_RPLVL(3)                           /*!< 3 frames stored in RxFIFO */

/* I2S audio sample rate */
#define I2S_AUDIOSAMPLE_8K              ((uint32_t)8000U)                       /*!< I2S audio sample rate is 8KHz */
#define I2S_AUDIOSAMPLE_11K             ((uint32_t)11025U)                      /*!< I2S audio sample rate is 11KHz */
#define I2S_AUDIOSAMPLE_16K             ((uint32_t)16000U)                      /*!< I2S audio sample rate is 16KHz */
#define I2S_AUDIOSAMPLE_22K             ((uint32_t)22050U)                      /*!< I2S audio sample rate is 22KHz */
#define I2S_AUDIOSAMPLE_32K             ((uint32_t)32000U)                      /*!< I2S audio sample rate is 32KHz */
#define I2S_AUDIOSAMPLE_44K             ((uint32_t)44100U)                      /*!< I2S audio sample rate is 44KHz */
#define I2S_AUDIOSAMPLE_48K             ((uint32_t)48000U)                      /*!< I2S audio sample rate is 48KHz */
#define I2S_AUDIOSAMPLE_96K             ((uint32_t)96000U)                      /*!< I2S audio sample rate is 96KHz */
#define I2S_AUDIOSAMPLE_192K            ((uint32_t)192000U)                     /*!< I2S audio sample rate is 192KHz */

/* I2S frame format */
#define I2SCTL_DTLEN(regval)            (BITS(1,2) & ((uint32_t)(regval) << 1))
#define I2S_FRAMEFORMAT_DT16B_CH16B     I2SCTL_DTLEN(0)                         /*!< I2S data length is 16 bit and channel length is 16 bit */
#define I2S_FRAMEFORMAT_DT16B_CH32B     (I2SCTL_DTLEN(0) | SPI_I2SCTL_CHLEN)    /*!< I2S data length is 16 bit and channel length is 32 bit */
#define I2S_FRAMEFORMAT_DT24B_CH32B     (I2SCTL_DTLEN(1) | SPI_I2SCTL_CHLEN)    /*!< I2S data length is 24 bit and channel length is 32 bit */
#define I2S_FRAMEFORMAT_DT32B_CH32B     (I2SCTL_DTLEN(2) | SPI_I2SCTL_CHLEN)    /*!< I2S data length is 32 bit and channel length is 32 bit */

/* I2S master clock output */
#define I2S_MCKOUT_DISABLE              ((uint32_t)0x00000000U)                 /*!< I2S master clock output disable */
#define I2S_MCKOUT_ENABLE               SPI_I2SCTL_MCKOEN                       /*!< I2S master clock output enable */

/* I2S operation mode */
#define I2SCTL_I2SOPMOD(regval)         (BITS(8,9) & ((uint32_t)(regval) << 8))
#define I2S_MODE_SLAVETX                I2SCTL_I2SOPMOD(0)                      /*!< I2S slave transmit mode */
#define I2S_MODE_SLAVERX                I2SCTL_I2SOPMOD(1)                      /*!< I2S slave receive mode */
#define I2S_MODE_MASTERTX               I2SCTL_I2SOPMOD(2)                      /*!< I2S master transmit mode */
#define I2S_MODE_MASTERRX               I2SCTL_I2SOPMOD(3)                      /*!< I2S master receive mode */

/* I2S standard */
#define I2SCTL_I2SSTD(regval)           (BITS(4,5) & ((uint32_t)(regval) << 4))
#define I2S_STD_PHILLIPS                I2SCTL_I2SSTD(0)                        /*!< I2S phillips standard */
#define I2S_STD_MSB                     I2SCTL_I2SSTD(1)                        /*!< I2S MSB standard */
#define I2S_STD_LSB                     I2SCTL_I2SSTD(2)                        /*!< I2S LSB standard */
#define I2S_STD_PCMSHORT                I2SCTL_I2SSTD(3)                        /*!< I2S PCM short standard */
#define I2S_STD_PCMLONG                 (I2SCTL_I2SSTD(3) | SPI_I2SCTL_PCMSMOD) /*!< I2S PCM long standard */

/* I2S clock polarity */
#define I2S_CKPL_LOW                    ((uint32_t)0x00000000U)                 /*!< I2S clock polarity low level */
#define I2S_CKPL_HIGH                   SPI_I2SCTL_CKPL                         /*!< I2S clock polarity high level */

/* SPI DMA constants definitions */
#define SPI_DMA_TRANSMIT                ((uint8_t)0x00U)                        /*!< SPI transmit data use DMA */
#define SPI_DMA_RECEIVE                 ((uint8_t)0x01U)                        /*!< SPI receive data use DMA */

/* SPI CRC constants definitions */
#define SPI_CRC_TX                      ((uint8_t)0x00U)                        /*!< SPI transmit CRC value */
#define SPI_CRC_RX                      ((uint8_t)0x01U)                        /*!< SPI receive CRC value */

/* SPI/I2S interrupt enable/disable constants definitions */
#define SPI_I2S_INT_RP                  ((uint8_t)0x00U)                        /*!< RP interrupt */
#define SPI_I2S_INT_TP                  ((uint8_t)0x01U)                        /*!< TP interrupt */
#define SPI_I2S_INT_DP                  ((uint8_t)0x02U)                        /*!< DP interrupt */
#define SPI_I2S_INT_ESTC                ((uint8_t)0x03U)                        /*!< end of transfer or suspend or TXFIFO clear interrupt */
#define SPI_I2S_INT_TXF                 ((uint8_t)0x04U)                        /*!< transmission filled interrupt */
#define SPI_I2S_INT_TXURE               ((uint8_t)0x05U)                        /*!< underrun error interrupt */
#define SPI_I2S_INT_RXORE               ((uint8_t)0x06U)                        /*!< overrun error interrupt */
#define SPI_I2S_INT_CRCER               ((uint8_t)0x07U)                        /*!< CRC error interrupt */
#define SPI_I2S_INT_FE                  ((uint8_t)0x08U)                        /*!< TI frame error interrupt */
#define SPI_I2S_INT_CONFE               ((uint8_t)0x09U)                        /*!< mode error interrupt */
#define SPI_I2S_INT_TXSERF              ((uint8_t)0x0AU)                        /*!< TXSER reload interrupt */

/* SPI/I2S interrupt flag constants definitions */
#define SPI_I2S_INT_FLAG_RP             ((uint8_t)0x00U)                        /*!< RP interrupt flag */
#define SPI_I2S_INT_FLAG_TP             ((uint8_t)0x01U)                        /*!< TP interrupt flag */
#define SPI_I2S_INT_FLAG_DP             ((uint8_t)0x02U)                        /*!< DP interrupt flag */
#define SPI_I2S_INT_FLAG_ET             ((uint8_t)0x03U)                        /*!< end of transfer or receive interrupt flag */
#define SPI_I2S_INT_FLAG_TXF            ((uint8_t)0x04U)                        /*!< transmission filled interrupt flag */
#define SPI_I2S_INT_FLAG_TXURERR        ((uint8_t)0x05U)                        /*!< underrun error interrupt flag */
#define SPI_I2S_INT_FLAG_RXORERR        ((uint8_t)0x06U)                        /*!< overrun error interrupt flag */
#define SPI_I2S_INT_FLAG_CRCERR         ((uint8_t)0x07U)                        /*!< CRC error interrupt flag */
#define SPI_I2S_INT_FLAG_FERR           ((uint8_t)0x08U)                        /*!< TI frame error interrupt flag */
#define SPI_I2S_INT_FLAG_CONFERR        ((uint8_t)0x09U)                        /*!< mode error interrupt flag */
#define SPI_I2S_INT_FLAG_TXSERF         ((uint8_t)0x0AU)                        /*!< TXSER reload interrupt flag */
#define SPI_I2S_INT_FLAG_SPD            ((uint8_t)0x0BU)                        /*!< suspend interrupt flag */
#define SPI_I2S_INT_FLAG_TC             ((uint8_t)0x0CU)                        /*!< TXFIFO clear interrupt flag */

/* SPI/I2S flag definitions */
#define SPI_FLAG_RP                     SPI_STAT_RP                             /*!< RP flag */
#define SPI_FLAG_TP                     SPI_STAT_TP                             /*!< TP flag */
#define SPI_FLAG_DP                     SPI_STAT_DP                             /*!< DP flag */
#define SPI_FLAG_ET                     SPI_STAT_ET                             /*!< end of transfer or receive flag */
#define SPI_FLAG_TXF                    SPI_STAT_TXF                            /*!< transmission filled flag */
#define SPI_FLAG_TXURERR                SPI_STAT_TXURERR                        /*!< underrun error flag */
#define SPI_FLAG_RXORERR                SPI_STAT_RXORERR                        /*!< overrun error flag */
#define SPI_FLAG_CRCERR                 SPI_STAT_CRCERR                         /*!< CRC error flag */
#define SPI_FLAG_FERR                   SPI_STAT_FERR                           /*!< TI frame error flag */
#define SPI_FLAG_CONFERR                SPI_STAT_CONFERR                        /*!< mode error flag */
#define SPI_FLAG_TXSERF                 SPI_STAT_TXSERF                         /*!< TXSER reload flag */
#define SPI_FLAG_SPD                    SPI_STAT_SPD                            /*!< suspend flag */
#define SPI_FLAG_TC                     SPI_STAT_TC                             /*!< TXFIFO clear flag */
#define SPI_FLAG_RPLVL                  SPI_STAT_RPLVL                          /*!< RxFIFO packing level flag */
#define SPI_FLAG_RWNE                   SPI_STAT_RWNE                           /*!< the word of RXFIFO is not empty flag */
#define SPI_FLAG_CTXSIZE                SPI_STAT_CTXSIZE                        /*!< the number of data frames remaining in the TXSIZE session flag */

#define I2S_FLAG_RP                     SPI_STAT_RP                             /*!< RP flag */
#define I2S_FLAG_TP                     SPI_STAT_TP                             /*!< TP flag */
#define I2S_FLAG_DP                     SPI_STAT_DP                             /*!< DP flag */
#define I2S_FLAG_ET                     SPI_STAT_ET                             /*!< end of transfer or suspend or TXFIFO clear flag */
#define I2S_FLAG_TXF                    SPI_STAT_TXF                            /*!< transmission filled flag */
#define I2S_FLAG_TXURERR                SPI_STAT_TXURERR                        /*!< underrun error flag */
#define I2S_FLAG_RXORERR                SPI_STAT_RXORERR                        /*!< overrun error flag */

/* function declarations */
/* initialization functions */
/* reset SPI and I2S */
void spi_i2s_deinit(uint32_t spi_periph);
/* initialize the parameters of SPI struct with the default values */
void spi_struct_para_init(spi_parameter_struct* spi_struct);
/* initialize SPI parameter */
void spi_init(uint32_t spi_periph, spi_parameter_struct* spi_struct);
/* enable SPI */
void spi_enable(uint32_t spi_periph);
/* disable SPI */
void spi_disable(uint32_t spi_periph);

/* initialize I2S parameter */
void i2s_init(uint32_t spi_periph, uint32_t i2s_mode, uint32_t i2s_standard, uint32_t i2s_ckpl);
/* configure I2S prescaler */
void i2s_psc_config(uint32_t spi_periph, uint32_t i2s_audiosample, uint32_t i2s_frameformat, uint32_t i2s_mckout);
/* enable I2S */
void i2s_enable(uint32_t spi_periph);
/* disable I2S */
void i2s_disable(uint32_t spi_periph);

/* IO swap functions */
/* SPI MOSI and MISO pin swap */
void spi_io_config(uint32_t spi_periph, uint32_t io_cfg);

/* SPI delay config functions */
/* set delay between active edge of NSS and start transfer or receive data in SPI master mode */
void spi_nss_idleness_delay_set(uint32_t spi_periph, uint32_t delay_cycle);
/* set SPI master data frame delay */
void spi_data_frame_delay_set(uint32_t spi_periph, uint32_t delay_cycle);
/* set SPI master mode rx clock delay */
void spi_master_receive_clock_delay_set(uint32_t spi_periph, uint32_t delay_unit);
/* set SPI slave mode rx clock delay */
void spi_slave_receive_clock_delay_set(uint32_t spi_periph, uint32_t delay_unit);
/* clear SPI master mode rx clock delay */
void spi_master_receive_clock_delay_clear(uint32_t spi_periph);
/* clear SPI slave mode rx clock delay */
void spi_slave_receive_clock_delay_clear(uint32_t spi_periph);

/* NSS functions */
/* NSS output control */
void spi_nss_output_control(uint32_t spi_periph, uint32_t nss_ctl);
/* set SPI NSS active polarity */
void spi_nss_polarity_set(uint32_t spi_periph, uint32_t polarity);
/* enable SPI NSS output */
void spi_nss_output_enable(uint32_t spi_periph);
/* disable SPI NSS output */
void spi_nss_output_disable(uint32_t spi_periph);
/* SPI NSS pin high level in software mode */
void spi_nss_internal_high(uint32_t spi_periph);
/* SPI NSS pin low level in software mode */
void spi_nss_internal_low(uint32_t spi_periph);

/* SPI DMA functions */
/* enable SPI DMA */
void spi_dma_enable(uint32_t spi_periph, uint8_t spi_dma);
/* disable SPI DMA */
void spi_dma_disable(uint32_t spi_periph, uint8_t spi_dma);

/* SPI/I2S transfer configure functions */
/* configure SPI/I2S data frame size */
void spi_i2s_data_frame_size_config(uint32_t spi_periph, uint32_t frame_size);
/* SPI/I2S transmit data */
void spi_i2s_data_transmit(uint32_t spi_periph, uint32_t data);
/* SPI/I2S receive data */
uint32_t spi_i2s_data_receive(uint32_t spi_periph);
/* configure SPI bidirectional transfer direction */
void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction);
/* SPI/I2S master start transfer */
void spi_master_transfer_start(uint32_t spi_periph, uint32_t transfer_start);
/* configure SPI current data number */
void spi_current_data_num_config(uint32_t spi_periph, uint32_t current_num);
/* configure SPI reload data number */
void spi_reload_data_num_config(uint32_t spi_periph, uint32_t reload_num);

/* SPI CRC functions */
/* set SPI CRC polynomial */
void spi_crc_polynomial_set(uint32_t spi_periph, uint32_t crc_poly);
/* get SPI CRC polynomial */
uint32_t spi_crc_polynomial_get(uint32_t spi_periph);
/* configure SPI CRC length */
void spi_crc_length_config(uint32_t spi_periph, uint32_t crc_size);
/* turn on SPI CRC function */
void spi_crc_on(uint32_t spi_periph);
/* turn off SPI CRC function */
void spi_crc_off(uint32_t spi_periph);
/* get SPI CRC send value or receive value */
uint32_t spi_crc_get(uint32_t spi_periph, uint8_t crc);
/* enable SPI CRC full size(33 bit or 17 bit) polynomial */
void spi_crc_full_size_enable(uint32_t spi_periph);
/* disable SPI CRC full size(33 bit or 17 bit) polynomial */
void spi_crc_full_size_disable(uint32_t spi_periph);
/* configure SPI TCRC init pattern */
void spi_tcrc_init_pattern(uint32_t spi_periph, uint32_t init_pattern);
/* configure SPI RCRC init pattern */
void spi_rcrc_init_pattern(uint32_t spi_periph, uint32_t init_pattern);

/* SPI TI mode functions */
/* enable SPI TI mode */
void spi_ti_mode_enable(uint32_t spi_periph);
/* disable SPI TI mode */
void spi_ti_mode_disable(uint32_t spi_periph);

/* quad wire SPI functions */
/* enable quad wire SPI */
void spi_quad_enable(uint32_t spi_periph);
/* disable quad wire SPI */
void spi_quad_disable(uint32_t spi_periph);
/* enable quad wire SPI write */
void spi_quad_write_enable(uint32_t spi_periph);
/* enable quad wire SPI read */
void spi_quad_read_enable(uint32_t spi_periph);
/* enable quad wire SPI_IO2 and SPI_IO3 pin output */
void spi_quad_io23_output_enable(uint32_t spi_periph);
/* disable quad wire SPI_IO2 and SPI_IO3 pin output */
void spi_quad_io23_output_disable(uint32_t spi_periph);

/* SPI underrun functions */
/* slave transmitter underrun detected operation */
void spi_underrun_operation(uint32_t spi_periph, uint32_t ur_ope);
/* configure slave transmitter underrun detected */
void spi_underrun_config(uint32_t spi_periph, uint32_t ur_cfg);
/* configure underrun data at slave mode */
void spi_underrun_data_config(uint32_t spi_periph, uint32_t udata);

/* SPI suspend functions */
/* configure SPI suspend in receive mode */
void spi_suspend_mode_config(uint32_t spi_periph, uint32_t sus_mode);
/* SPI master mode suspend request */
void spi_suspend_request(uint32_t spi_periph);

/* SPI Related IOS AF functions */
/* enable SPI related IOs AF */
void spi_related_ios_af_enable(uint32_t spi_periph);
/* disable SPI related IOs AF */
void spi_related_ios_af_disable(uint32_t spi_periph);
/* SPI af gpio control */
void spi_af_gpio_control(uint32_t spi_periph, uint32_t ctl);

/* flag and interrupt functions */
/* enable SPI and I2S interrupt */
void spi_i2s_interrupt_enable(uint32_t spi_periph, uint8_t interrupt);
/* disable SPI and I2S interrupt */
void spi_i2s_interrupt_disable(uint32_t spi_periph, uint8_t interrupt);
/* get SPI and I2S interrupt flag status */
FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, uint8_t interrupt);
/* get SPI and I2S flag status */
FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t flag);
/* clear SPI and I2S flag status */
void spi_i2s_flag_clear(uint32_t spi_periph, uint32_t flag);
/* get SPI and I2S RXFIFO packing level */
uint32_t spi_i2s_rxfifo_plevel_get(uint32_t spi_periph);
/* get SPI and I2S remaining data frames number in the TXSIZE session */
uint32_t spi_i2s_remain_data_num_get(uint32_t spi_periph);

/* SPI FIFO configure */
/* set SPI FIFO threshold level */
void spi_fifo_threshold_level_set(uint32_t spi_periph, uint32_t fifo_thl);
/* enable SPI word access */
void spi_word_access_enable(uint32_t spi_periph);
/* disable SPI word access */
void spi_word_access_disable(uint32_t spi_periph);
/* enable SPI byte access */
void spi_byte_access_enable(uint32_t spi_periph);
/* disable SPI byte access */
void spi_byte_access_disable(uint32_t spi_periph);

#endif /* GD32H7XX_SPI_H */
