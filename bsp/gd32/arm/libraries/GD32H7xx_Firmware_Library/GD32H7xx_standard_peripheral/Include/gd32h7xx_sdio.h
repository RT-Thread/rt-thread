/*!
    \file    gd32h7xx_sdio.h
    \brief   definitions for the SDIO

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

#ifndef GD32H7XX_SDIO_H
#define GD32H7XX_SDIO_H

#include "gd32h7xx.h"

/* SDIO definitions */
#define SDIO0                           (SDIO_BASE + 0x09FE4C00U)
#define SDIO1                           (SDIO_BASE)

/* registers definitions */
#define SDIO_PWRCTL(sdiox)              REG32((sdiox) + 0x00000000U)   /*!< SDIO power control register */
#define SDIO_CLKCTL(sdiox)              REG32((sdiox) + 0x00000004U)   /*!< SDIO clock control register */
#define SDIO_CMDAGMT(sdiox)             REG32((sdiox) + 0x00000008U)   /*!< SDIO command argument register */
#define SDIO_CMDCTL(sdiox)              REG32((sdiox) + 0x0000000CU)   /*!< SDIO command control register */
#define SDIO_RSPCMDIDX(sdiox)           REG32((sdiox) + 0x00000010U)   /*!< SDIO command index response register */
#define SDIO_RESP0(sdiox)               REG32((sdiox) + 0x00000014U)   /*!< SDIO response register 0 */
#define SDIO_RESP1(sdiox)               REG32((sdiox) + 0x00000018U)   /*!< SDIO response register 1 */
#define SDIO_RESP2(sdiox)               REG32((sdiox) + 0x0000001CU)   /*!< SDIO response register 2 */
#define SDIO_RESP3(sdiox)               REG32((sdiox) + 0x00000020U)   /*!< SDIO response register 3 */
#define SDIO_DATATO(sdiox)              REG32((sdiox) + 0x00000024U)   /*!< SDIO data timeout register */
#define SDIO_DATALEN(sdiox)             REG32((sdiox) + 0x00000028U)   /*!< SDIO data length register */
#define SDIO_DATACTL(sdiox)             REG32((sdiox) + 0x0000002CU)   /*!< SDIO data control register */
#define SDIO_DATACNT(sdiox)             REG32((sdiox) + 0x00000030U)   /*!< SDIO data counter register */
#define SDIO_STAT(sdiox)                REG32((sdiox) + 0x00000034U)   /*!< SDIO status register */
#define SDIO_INTC(sdiox)                REG32((sdiox) + 0x00000038U)   /*!< SDIO interrupt clear register */
#define SDIO_INTEN(sdiox)               REG32((sdiox) + 0x0000003CU)   /*!< SDIO interrupt enable register */
#define SDIO_ACKTO(sdiox)               REG32((sdiox) + 0x00000040U)   /*!< SDIO FIFO ACK timeout register */
#define SDIO_FIFO(sdiox)                REG32((sdiox) + 0x00000080U)   /*!< SDIO FIFO data register */
#define SDIO_IDMACTL(sdiox)             REG32((sdiox) + 0x00000050U)   /*!< SDIO FIFO internal DMA control register */
#define SDIO_IDMASIZE(sdiox)            REG32((sdiox) + 0x00000054U)   /*!< SDIO FIFO internal DMA buffer size register */
#define SDIO_IDMAADDR0(sdiox)           REG32((sdiox) + 0x00000058U)   /*!< SDIO FIFO internal DMA buffer 0 base address register */
#define SDIO_IDMAADDR1(sdiox)           REG32((sdiox) + 0x0000005CU)   /*!< SDIO FIFO internal DMA buffer 1 base address register */

/* bits definitions */
/* SDIO_PWRCTL */
#define SDIO_PWRCTL_PWRCTL              BITS(0,1)              /*!< SDIO power control bits */
#define SDIO_PWRCTL_VSSTART             BIT(2)                 /*!< voltage switch start bit */
#define SDIO_PWRCTL_VSEN                BIT(3)                 /*!< voltage switch enable bit */
#define SDIO_PWRCTL_DIRPS               BIT(4)                 /*!< data and command direction polarity selection bit */

/* SDIO_CLKCTL */
#define SDIO_CLKCTL_DIV                 BITS(0,9)              /*!< clock division */
#define SDIO_CLKCTL_CLKPWRSAV           BIT(12)                /*!< SDIO_CLK clock dynamic switch on/off for power saving */
#define SDIO_CLKCTL_BUSMODE             BITS(14,15)            /*!< SDIO card bus mode control bit */
#define SDIO_CLKCTL_CLKEDGE             BIT(16)                /*!< command and data SDIO_CLK dephasing selection bit */
#define SDIO_CLKCTL_HWEN                BIT(17)                /*!< hardware flow control enable bit */
#define SDIO_CLKCTL_DRSEL               BIT(18)                /*!< data rate selection bit */
#define SDIO_CLKCTL_BUSSP               BIT(19)                /*!< bus speed mode selection bit */
#define SDIO_CLKCTL_RCLK                BITS(20,21)            /*!< receive clock selection bits */

/* SDIO_CMDAGMT */
#define SDIO_CMDAGMT_CMDAGMT            BITS(0,31)             /*!< SDIO card command argument */

/* SDIO_CMDCTL */
#define SDIO_CMDCTL_CMDIDX              BITS(0,5)              /*!< command index */
#define SDIO_CMDCTL_TREN                BIT(6)                 /*!< data transfer mode enable bit */
#define SDIO_CMDCTL_TRSTOP              BIT(7)                 /*!< data transfer stop bit */
#define SDIO_CMDCTL_CMDRESP             BITS(8,9)              /*!< waits command response type bits */
#define SDIO_CMDCTL_INTWAIT             BIT(10)                /*!< interrupt wait instead of timeout */
#define SDIO_CMDCTL_WAITDEND            BIT(11)                /*!< waits for ends of data transfer */
#define SDIO_CMDCTL_CSMEN               BIT(12)                /*!< command state machine (CSM) enable bit */
#define SDIO_CMDCTL_HOLD                BIT(13)                /*!< hold DSM transmission and reception of new data block */
#define SDIO_CMDCTL_BOOTMOD             BIT(14)                /*!< boot mode selection bit */
#define SDIO_CMDCTL_BOOTMODEN           BIT(15)                /*!< boot mode procedure enable bit */
#define SDIO_CMDCTL_CMDSR               BIT(16)                /*!< suspend or resume command and signals interrupt period start/end bit */

/* SDIO_DATATO */
#define SDIO_DATATO_DATATO              BITS(0,31)             /*!< data timeout period */

/* SDIO_DATALEN */
#define SDIO_DATALEN_DATALEN            BITS(0,24)             /*!< data transfer length */

/* SDIO_DATACTL */
#define SDIO_DATACTL_DATAEN             BIT(0)                 /*!< data transfer enabled bit */
#define SDIO_DATACTL_DATADIR            BIT(1)                 /*!< data transfer direction */
#define SDIO_DATACTL_TRANSMOD           BITS(2,3)              /*!< data transfer mode */
#define SDIO_DATACTL_BLKSZ              BITS(4,7)              /*!< data block size */
#define SDIO_DATACTL_ACKEN              BIT(12)                /*!< boot acknowledgment enable bit */
#define SDIO_DATACTL_FIFOREST           BIT(13)                /*!< FIFO buffer reset, flush all data */

/* SDIO_STAT */
#define SDIO_STAT_CCRCERR               BIT(0)                 /*!< command response received (CRC check failed) */
#define SDIO_STAT_DTCRCERR              BIT(1)                 /*!< data block sent/received (CRC check failed) */
#define SDIO_STAT_CMDTMOUT              BIT(2)                 /*!< command response timeout */
#define SDIO_STAT_DTTMOUT               BIT(3)                 /*!< data timeout */
#define SDIO_STAT_TXURE                 BIT(4)                 /*!< transmit FIFO underrun error occurs */
#define SDIO_STAT_RXORE                 BIT(5)                 /*!< received FIFO overrun error occurs */
#define SDIO_STAT_CMDRECV               BIT(6)                 /*!< command response received (CRC check passed) */
#define SDIO_STAT_CMDSEND               BIT(7)                 /*!< command sent (no response required) */
#define SDIO_STAT_DTEND                 BIT(8)                 /*!< data end (data counter, SDIO_DATACNT is zero) */
#define SDIO_STAT_DATHOLD               BIT(9)                 /*!< data transfer hold */
#define SDIO_STAT_DTBLKEND              BIT(10)                /*!< data block sent/received (CRC check passed) */
#define SDIO_STAT_DATABOR               BIT(11)                /*!< data transfer aborted by CMD12 */
#define SDIO_STAT_CMDSTA                BIT(12)                /*!< command path active state */
#define SDIO_STAT_DATSTA                BIT(13)                /*!< data path active state */
#define SDIO_STAT_TFH                   BIT(14)                /*!< transmit FIFO is half empty */
#define SDIO_STAT_RFH                   BIT(15)                /*!< receive FIFO is half full */
#define SDIO_STAT_TFF                   BIT(16)                /*!< transmit FIFO is full */
#define SDIO_STAT_RFF                   BIT(17)                /*!< receive FIFO is full */
#define SDIO_STAT_TFE                   BIT(18)                /*!< transmit FIFO is empty */
#define SDIO_STAT_RFE                   BIT(19)                /*!< receive FIFO is empty */
#define SDIO_STAT_DAT0BSY               BIT(20)                /*!< DAT0 line signal keep busy */
#define SDIO_STAT_DAT0BSYEND            BIT(21)                /*!< DAT0 line signal changed from busy to ready */
#define SDIO_STAT_SDIOINT               BIT(22)                /*!< SD I/O interrupt received */
#define SDIO_STAT_ACKFAIL               BIT(23)                /*!< boot acknowledgment received and check fail */
#define SDIO_STAT_ACKTO                 BIT(24)                /*!< boot acknowledgment timeout */
#define SDIO_STAT_VSEND                 BIT(25)                /*!< voltage switch critical timing section end */
#define SDIO_STAT_CLKSTOP               BIT(26)                /*!< SDIO_CLK stopped in voltage switch procedure */
#define SDIO_STAT_IDMERR                BIT(27)                /*!< IDMA transfer error */
#define SDIO_STAT_IDMAEND               BIT(28)                /*!< IDMA transfer end */

/* SDIO_INTC */
#define SDIO_INTC_CCRCERRC              BIT(0)                 /*!< CCRCERR flag clear bit */
#define SDIO_INTC_DTCRCERRC             BIT(1)                 /*!< DTCRCERR flag clear bit */
#define SDIO_INTC_CMDTMOUTC             BIT(2)                 /*!< CMDTMOUT flag clear bit */
#define SDIO_INTC_DTTMOUTC              BIT(3)                 /*!< DTTMOUT flag clear bit */
#define SDIO_INTC_TXUREC                BIT(4)                 /*!< TXURE flag clear bit */
#define SDIO_INTC_RXOREC                BIT(5)                 /*!< RXORE flag clear bit */
#define SDIO_INTC_CMDRECVC              BIT(6)                 /*!< CMDRECV flag clear bit */
#define SDIO_INTC_CMDSENDC              BIT(7)                 /*!< CMDSEND flag clear bit */
#define SDIO_INTC_DTENDC                BIT(8)                 /*!< DTEND flag clear bit */
#define SDIO_INTC_DATHOLDC              BIT(9)                 /*!< DATHOLD flag clear bit */
#define SDIO_INTC_DTBLKENDC             BIT(10)                /*!< DTBLKEND flag clear bit */
#define SDIO_INTC_DATABORC              BIT(11)                /*!< DATABOR flag clear bit */
#define SDIO_INTC_DAT0BSYENDC           BIT(21)                /*!< DAT0BSYEND flag clear bit */
#define SDIO_INTC_SDIOINTC              BIT(22)                /*!< SDIOINT flag clear bit */
#define SDIO_INTC_ACKFAILC              BIT(23)                /*!< ACKFAIL flag clear bit */
#define SDIO_INTC_ACKTOC                BIT(24)                /*!< ACKTO flag clear bit */
#define SDIO_INTC_VSENDC                BIT(25)                /*!< VSEND flag clear bit */
#define SDIO_INTC_CLKSTOPC              BIT(26)                /*!< CLKSTOP flag clear bit */
#define SDIO_INTC_IDMERRC               BIT(27)                /*!< IDMERR flag clear bit */
#define SDIO_INTC_IDMAENDC              BIT(28)                /*!< IDMAEND flag clear bit */

/* SDIO_INTEN */
#define SDIO_INTEN_CCRCERRIE            BIT(0)                 /*!< command response CRC fail interrupt enable */
#define SDIO_INTEN_DTCRCERRIE           BIT(1)                 /*!< data CRC fail interrupt enable */
#define SDIO_INTEN_CMDTMOUTIE           BIT(2)                 /*!< command response timeout interrupt enable */
#define SDIO_INTEN_DTTMOUTIE            BIT(3)                 /*!< data timeout interrupt enable */
#define SDIO_INTEN_TXUREIE              BIT(4)                 /*!< transmit FIFO underrun error interrupt enable */
#define SDIO_INTEN_RXOREIE              BIT(5)                 /*!< received FIFO overrun error interrupt enable */
#define SDIO_INTEN_CMDRECVIE            BIT(6)                 /*!< command response received interrupt enable */
#define SDIO_INTEN_CMDSENDIE            BIT(7)                 /*!< command sent interrupt enable */
#define SDIO_INTEN_DTENDIE              BIT(8)                 /*!< data end interrupt enable */
#define SDIO_INTEN_DATHOLDIE            BIT(9)                 /*!< data transfer hold interrupt enable */
#define SDIO_INTEN_DTBLKENDIE           BIT(10)                /*!< data block end interrupt enable */
#define SDIO_INTEN_DATABORIE            BIT(11)                /*!< data transfer abort interrupt enable */
#define SDIO_INTEN_TFHIE                BIT(14)                /*!< transmit FIFO half empty interrupt enable */
#define SDIO_INTEN_RFHIE                BIT(15)                /*!< receive FIFO half full interrupt enable */
#define SDIO_INTEN_RFFIE                BIT(17)                /*!< receive FIFO full interrupt enable */
#define SDIO_INTEN_TFEIE                BIT(18)                /*!< transmit FIFO empty interrupt enable */
#define SDIO_INTEN_DAT0BSYENDIE         BIT(21)                /*!< DAT0 line signal changed from busy to ready interrupt enable */
#define SDIO_INTEN_SDIOINTIE            BIT(22)                /*!< SD I/O interrupt received interrupt enable */
#define SDIO_INTEN_ACKFAILIE            BIT(23)                /*!< boot acknowledgment received and check fail interrupt enable */
#define SDIO_INTEN_ACKTOIE              BIT(24)                /*!< boot acknowledgment timeout enable */
#define SDIO_INTEN_VSENDIE              BIT(25)                /*!< voltage switch critical timing section end interrupt enable */
#define SDIO_INTEN_CLKSTOPIE            BIT(26)                /*!< voltage Switch clock stopped interrupt enable */
#define SDIO_INTEN_IDMAERRIE            BIT(27)                /*!< IDMA transfer error interrupt enable */
#define SDIO_INTEN_IDMAENDIE            BIT(28)                /*!< IDMA transfer end interrupt enable */

/* SDIO_ACKTO */
#define SDIO_ACKTO_ACKTO                BITS(0, 24)            /*!< boot ACK timeout period */

/* SDIO_FIFO */
#define SDIO_FIFO_FIFODT                BITS(0, 31)            /*!< receive FIFO data or transmit FIFO data */

/* SDIO_IDMACTL */
#define SDIO_IDMACTL_IDMAEN             BIT(0)                 /*!< FIFO IDMA enable bit */
#define SDIO_IDMACTL_BUFMOD             BIT(1)                 /*!< double buffer mode enable bit */
#define SDIO_IDMACTL_BUFSEL             BIT(2)                 /*!< IDMA double buffer selection bit */

/* SDIO_IDMASIZE */
#define SDIO_IDMASIZE_IDMASIZE          BITS(5, 12)            /*!< number of bytes per buffer, buffer size = number*32 */

/* SDIO_IDMAADDR0 */
#define SDIO_IDMAADDR0_IDMAADDR0        BITS(0, 31)            /*!< IDMA buffer 0 base address, is a multiple of 8 */

/* SDIO_IDMAADDR1 */
#define SDIO_IDMAADDR1_IDMAADDR1        BITS(0, 31)            /*!< IDMA buffer 1 base address, is a multiple of 8 */

/* constants definitions */
/* SDIO power control */
#define PWRCTL_PWRCTL(regval)           (BITS(0,1) & ((uint32_t)(regval) << 0))
#define SDIO_POWER_OFF                  PWRCTL_PWRCTL(0)       /*!< SDIO power off */
#define SDIO_POWER_CYCLE                PWRCTL_PWRCTL(2)       /*!< SDIO power cycle */
#define SDIO_POWER_ON                   PWRCTL_PWRCTL(3)       /*!< SDIO power on */

/* SDIO receive clock selection */
#define CLKCTL_RECEICECLOCK(regval)     (BITS(20, 21) & ((uint32_t)(regval) << 20))
#define SDIO_RECEIVECLOCK_INCLK         CLKCTL_RECEICECLOCK(0) /*!< select SDIO_IN_CLK clock */
#define SDIO_RECEIVECLOCK_CLKIN         CLKCTL_RECEICECLOCK(1) /*!< select SDIO_CLKIN clock */
#define SDIO_RECEIVECLOCK_FBCLK         CLKCTL_RECEICECLOCK(2) /*!< select SDIO_FB_CLK clock */

/* SDIO card bus speed control */
#define SDIO_BUSSPEED_LOW               (uint32_t)0x00000000U  /*!< DS, HS, SDR12, SDR25 bus speed */
#define SDIO_BUSSPEED_HIGH              SDIO_CLKCTL_BUSSP      /*!< SDR50, SDR104, DDR50 bus speed */

/* SDIO data rate selection */
#define SDIO_DATA_RATE_SDR              (uint32_t)0x00000000U  /*!< SDR selected */
#define SDIO_DATA_RATE_DDR              SDIO_CLKCTL_DRSEL      /*!< DDR selected */

/* SDIO_CLK clock edge selection */
#define SDIO_SDIOCLKEDGE_RISING         (uint32_t)0x00000000U  /*!< select the rising edge of the SDIOCLK to generate SDIO_CLK */
#define SDIO_SDIOCLKEDGE_FALLING        SDIO_CLKCTL_CLKEDGE    /*!< select the falling edge of the SDIOCLK to generate SDIO_CLK */

/* SDIO_CLK clock dynamic switch on/off for power saving */
#define SDIO_CLOCKPWRSAVE_DISABLE       (uint32_t)0x00000000U  /*!< SDIO_CLK clock is always on */
#define SDIO_CLOCKPWRSAVE_ENABLE        SDIO_CLKCTL_CLKPWRSAV  /*!< SDIO_CLK closed when bus is idle */

/* SDIO card bus mode control */
#define CLKCTL_BUSMODE(regval)          (BITS(14, 15) & ((uint32_t)(regval) << 14))
#define SDIO_BUSMODE_1BIT               CLKCTL_BUSMODE(0)      /*!< 1-bit SDIO card bus mode */
#define SDIO_BUSMODE_4BIT               CLKCTL_BUSMODE(1)      /*!< 4-bit SDIO card bus mode */
#define SDIO_BUSMODE_8BIT               CLKCTL_BUSMODE(2)      /*!< 8-bit SDIO card bus mode */

/* SDIO direction polarity of data and command */
#define SDIO_DIRECTION_SIGNAL_LOW       (uint32_t)0x00000000U  /*!< direction signal is low, the voltage transceiver IOs driven as output */
#define SDIO_DIRECTION_SIGNAL_HIGH      SDIO_PWRCTL_DIRPS      /*!< direction signal is high, the voltage transceiver IOs driven as output */

/* SDIO boot mode */
#define SDIO_BOOTMODE_NORMAL            (uint32_t)0x00000000U  /*!< normal boot mode */
#define SDIO_BOOTMODE_ALTERNATIVE       SDIO_CMDCTL_BOOTMOD    /*!< alternative boot mode */

/* SDIO command response type */
#define CMDCTL_CMDRESP(regval)          (BITS(8, 9) & ((uint32_t)(regval) << 8))
#define SDIO_RESPONSETYPE_NO            CMDCTL_CMDRESP(0)      /*!< no response */
#define SDIO_RESPONSETYPE_SHORT         CMDCTL_CMDRESP(1)      /*!< short response */
#define SDIO_RESPONSETYPE_SHORT_NOCRC   CMDCTL_CMDRESP(2)      /*!< short response without CRC */
#define SDIO_RESPONSETYPE_LONG          CMDCTL_CMDRESP(3)      /*!< long response */

/* command state machine wait type */
#define SDIO_WAITTYPE_NO                (uint32_t)0x00000000U  /*!< not wait interrupt */
#define SDIO_WAITTYPE_INTERRUPT         SDIO_CMDCTL_INTWAIT    /*!< wait interrupt */
#define SDIO_WAITTYPE_DATAEND           SDIO_CMDCTL_WAITDEND   /*!< wait the end of data transfer */

/* command type */
#define SDIO_CMDTYPE_NO                 (uint32_t)0x00000000U  /*!< just a command */
#define SDIO_CMDTYPE_TRANSFER           SDIO_CMDCTL_TREN       /*!< command for transfer */
#define SDIO_CMDTYPE_TRANSFERSTOP       SDIO_CMDCTL_TRSTOP     /*!< commang for stopping transfer */
#define SDIO_CMDTYPE_SUSPEND            SDIO_CMDCTL_CMDSR      /*!< suspend command, or resume command */

/* short response and each part of the long response */
#define SDIO_RESPONSE0                  (uint32_t)0x00000000U  /*!< card response[31:0]/card response[127:96] */
#define SDIO_RESPONSE1                  (uint32_t)0x00000001U  /*!< card response[95:64] */
#define SDIO_RESPONSE2                  (uint32_t)0x00000002U  /*!< card response[63:32] */
#define SDIO_RESPONSE3                  (uint32_t)0x00000003U  /*!< card response[31:1], plus bit 0 */

/* SDIO data block size */
#define DATACTL_BLKSZ(regval)           (BITS(4,7) & ((uint32_t)(regval) << 4))
#define SDIO_DATABLOCKSIZE_1BYTE        DATACTL_BLKSZ(0)       /*!< block size = 1 byte */
#define SDIO_DATABLOCKSIZE_2BYTES       DATACTL_BLKSZ(1)       /*!< block size = 2 bytes */
#define SDIO_DATABLOCKSIZE_4BYTES       DATACTL_BLKSZ(2)       /*!< block size = 4 bytes */
#define SDIO_DATABLOCKSIZE_8BYTES       DATACTL_BLKSZ(3)       /*!< block size = 8 bytes */
#define SDIO_DATABLOCKSIZE_16BYTES      DATACTL_BLKSZ(4)       /*!< block size = 16 bytes */
#define SDIO_DATABLOCKSIZE_32BYTES      DATACTL_BLKSZ(5)       /*!< block size = 32 bytes */
#define SDIO_DATABLOCKSIZE_64BYTES      DATACTL_BLKSZ(6)       /*!< block size = 64 bytes */
#define SDIO_DATABLOCKSIZE_128BYTES     DATACTL_BLKSZ(7)       /*!< block size = 128 bytes */
#define SDIO_DATABLOCKSIZE_256BYTES     DATACTL_BLKSZ(8)       /*!< block size = 256 bytes */
#define SDIO_DATABLOCKSIZE_512BYTES     DATACTL_BLKSZ(9)       /*!< block size = 512 bytes */
#define SDIO_DATABLOCKSIZE_1024BYTES    DATACTL_BLKSZ(10)      /*!< block size = 1024 bytes */
#define SDIO_DATABLOCKSIZE_2048BYTES    DATACTL_BLKSZ(11)      /*!< block size = 2048 bytes */
#define SDIO_DATABLOCKSIZE_4096BYTES    DATACTL_BLKSZ(12)      /*!< block size = 4096 bytes */
#define SDIO_DATABLOCKSIZE_8192BYTES    DATACTL_BLKSZ(13)      /*!< block size = 8192 bytes */
#define SDIO_DATABLOCKSIZE_16384BYTES   DATACTL_BLKSZ(14)      /*!< block size = 16384 bytes */

/* SDIO data transfer mode */
#define DATACTL_TRANSMODE(regval)       (BITS(2,3) & ((uint32_t)(regval) << 2))
#define SDIO_TRANSMODE_BLOCKCOUNT       DATACTL_TRANSMODE(0)   /*!< block count data transfer */
#define SDIO_TRANSMODE_MULTIBYTE        DATACTL_TRANSMODE(1)   /*!< multibyte data transfer (only SD/SD I/O) */
#define SDIO_TRANSMODE_STREAM           DATACTL_TRANSMODE(2)   /*!< stream transfer (only eMMC) */
#define SDIO_TRANSMODE_BLOCKCMD12       DATACTL_TRANSMODE(3)   /*!< block data transfer ends with CMD12 */

/* SDIO data transfer direction */
#define SDIO_TRANSDIRECTION_TOCARD      (uint32_t)0x00000000U  /*!< write data to card */
#define SDIO_TRANSDIRECTION_TOSDIO      SDIO_DATACTL_DATADIR   /*!< read data from card */

/* SDIO idma buffer mode */
#define SDIO_IDMA_SINGLE_BUFFER         (uint32_t)0x00000000U  /*!< single buffer mode */
#define SDIO_IDMA_DOUBLE_BUFFER         SDIO_IDMACTL_BUFMOD    /*!< double buffer mode */

/* SDIO idma buffer selection */
#define SDIO_IDMA_BUFFER0               (uint32_t)0x00000000U  /*!< select buffer0 */
#define SDIO_IDMA_BUFFER1               SDIO_IDMACTL_BUFSEL    /*!< select buffer1 */

/* constants definitions */
/* SDIO flags */
#define SDIO_FLAG_CCRCERR               BIT(0)                 /*!< command response received (CRC check failed) flag */
#define SDIO_FLAG_DTCRCERR              BIT(1)                 /*!< data block sent/received (CRC check failed) flag */
#define SDIO_FLAG_CMDTMOUT              BIT(2)                 /*!< command response timeout flag */
#define SDIO_FLAG_DTTMOUT               BIT(3)                 /*!< data timeout flag */
#define SDIO_FLAG_TXURE                 BIT(4)                 /*!< transmit FIFO underrun error occurs flag */
#define SDIO_FLAG_RXORE                 BIT(5)                 /*!< received FIFO overrun error occurs flag */
#define SDIO_FLAG_CMDRECV               BIT(6)                 /*!< command response received (CRC check passed) flag */
#define SDIO_FLAG_CMDSEND               BIT(7)                 /*!< command sent (no response required) flag */
#define SDIO_FLAG_DTEND                 BIT(8)                 /*!< data end (data counter, SDIO_DATACNT is zero) flag */
#define SDIO_FLAG_DTHOLD                BIT(9)                 /*!< data transfer hold flag */
#define SDIO_FLAG_DTBLKEND              BIT(10)                /*!< data block sent/received (CRC check passed) flag */
#define SDIO_FLAG_DTABORT               BIT(11)                /*!< data transfer aborted by CMD12 flag */
#define SDIO_FLAG_CMDSTA                BIT(12)                /*!< command path active state flag */
#define SDIO_FLAG_DATSTA                BIT(13)                /*!< data path active state flag */
#define SDIO_FLAG_TFH                   BIT(14)                /*!< transmit FIFO is half empty flag: at least 8 words can be written into the FIFO */
#define SDIO_FLAG_RFH                   BIT(15)                /*!< receive FIFO is half full flag: at least 8 words can be read in the FIFO */
#define SDIO_FLAG_TFF                   BIT(16)                /*!< transmit FIFO is full flag */
#define SDIO_FLAG_RFF                   BIT(17)                /*!< receive FIFO is full flag */
#define SDIO_FLAG_TFE                   BIT(18)                /*!< transmit FIFO is empty flag */
#define SDIO_FLAG_RFE                   BIT(19)                /*!< receive FIFO is empty flag */
#define SDIO_FLAG_DAT0BSY               BIT(20)                /*!< DAT0 line signal keep busy flag */
#define SDIO_FLAG_DAT0BSYEND            BIT(21)                /*!< DAT0 line signal changed from busy to ready flag */
#define SDIO_FLAG_SDIOINT               BIT(22)                /*!< SD I/O interrupt received flag */
#define SDIO_FLAG_ACKFAIL               BIT(23)                /*!< boot acknowledgment received and check fail flag */
#define SDIO_FLAG_ACKTO                 BIT(24)                /*!< boot acknowledgment timeout flag */
#define SDIO_FLAG_VOLSWEND              BIT(25)                /*!< voltage switch critical timing section end flag */
#define SDIO_FLAG_CLKSTOP               BIT(26)                /*!< SDIO_CLK stopped in voltage switch procedure flag */
#define SDIO_FLAG_IDMAERR               BIT(27)                /*!< IDMA transfer error flag */
#define SDIO_FLAG_IDMAEND               BIT(28)                /*!< IDMA transfer end flag */

/* SDIO interrupt enable or disable */
#define SDIO_INT_CCRCERR                BIT(0)                 /*!< SDIO CCRCERR interrupt */
#define SDIO_INT_DTCRCERR               BIT(1)                 /*!< SDIO DTCRCERR interrupt */
#define SDIO_INT_CMDTMOUT               BIT(2)                 /*!< SDIO CMDTMOUT interrupt */
#define SDIO_INT_DTTMOUT                BIT(3)                 /*!< SDIO DTTMOUT interrupt */
#define SDIO_INT_TXURE                  BIT(4)                 /*!< SDIO TXURE interrupt */
#define SDIO_INT_RXORE                  BIT(5)                 /*!< SDIO RXORE interrupt */
#define SDIO_INT_CMDRECV                BIT(6)                 /*!< SDIO CMDRECV interrupt */
#define SDIO_INT_CMDSEND                BIT(7)                 /*!< SDIO CMDSEND interrupt */
#define SDIO_INT_DTEND                  BIT(8)                 /*!< SDIO DTEND interrupt */
#define SDIO_INT_DTHOLD                 BIT(9)                 /*!< SDIO DTHOLD interrupt */
#define SDIO_INT_DTBLKEND               BIT(10)                /*!< SDIO DTBLKEND interrupt */
#define SDIO_INT_DTABORT                BIT(11)                /*!< SDIO DTABORT interrupt */
#define SDIO_INT_TFH                    BIT(14)                /*!< SDIO TFH interrupt */
#define SDIO_INT_RFH                    BIT(15)                /*!< SDIO RFH interrupt */
#define SDIO_INT_RFF                    BIT(17)                /*!< SDIO RFF interrupt */
#define SDIO_INT_TFE                    BIT(18)                /*!< SDIO TFE interrupt */
#define SDIO_INT_DAT0BSYEND             BIT(21)                /*!< SDIO DAT0BSYEND interrupt */
#define SDIO_INT_SDIOINT                BIT(22)                /*!< SDIO SDIOINT interrupt */
#define SDIO_INT_ACKFAIL                BIT(23)                /*!< SDIO ACKFAIL interrupt */
#define SDIO_INT_ACKTO                  BIT(24)                /*!< SDIO ACKTO interrupt */
#define SDIO_INT_VOLSWEND               BIT(25)                /*!< SDIO VOLSWEND interrupt */
#define SDIO_INT_CLKSTOP                BIT(26)                /*!< SDIO CLKSTOP interrupt */
#define SDIO_INT_IDMAERR                BIT(27)                /*!< SDIO IDMAERR interrupt */
#define SDIO_INT_IDMAEND                BIT(28)                /*!< SDIO IDMAEND interrupt */

/* SDIO interrupt flag: enable or disable */
#define SDIO_INT_FLAG_CCRCERR           BIT(0)                 /*!< SDIO CCRCERR interrupt flag */
#define SDIO_INT_FLAG_DTCRCERR          BIT(1)                 /*!< SDIO DTCRCERR interrupt flag */
#define SDIO_INT_FLAG_CMDTMOUT          BIT(2)                 /*!< SDIO CMDTMOUT interrupt flag */
#define SDIO_INT_FLAG_DTTMOUT           BIT(3)                 /*!< SDIO DTTMOUT interrupt flag */
#define SDIO_INT_FLAG_TXURE             BIT(4)                 /*!< SDIO TXURE interrupt flag */
#define SDIO_INT_FLAG_RXORE             BIT(5)                 /*!< SDIO RXORE interrupt flag */
#define SDIO_INT_FLAG_CMDRECV           BIT(6)                 /*!< SDIO CMDRECV interrupt flag */
#define SDIO_INT_FLAG_CMDSEND           BIT(7)                 /*!< SDIO CMDSEND interrupt flag */
#define SDIO_INT_FLAG_DTEND             BIT(8)                 /*!< SDIO DTEND interrupt flag */
#define SDIO_INT_FLAG_DTHOLD            BIT(9)                 /*!< SDIO DTHOLD interrupt flag */
#define SDIO_INT_FLAG_DTBLKEND          BIT(10)                /*!< SDIO DTBLKEND interrupt flag */
#define SDIO_INT_FLAG_DTABORT           BIT(11)                /*!< SDIO DTABORT interrupt flag */
#define SDIO_INT_FLAG_TFH               BIT(14)                /*!< SDIO TFH interrupt flag */
#define SDIO_INT_FLAG_RFH               BIT(15)                /*!< SDIO RFH interrupt flag */
#define SDIO_INT_FLAG_RFF               BIT(17)                /*!< SDIO RFF interrupt flag */
#define SDIO_INT_FLAG_TFE               BIT(18)                /*!< SDIO TFE interrupt flag */
#define SDIO_INT_FLAG_DAT0BSYEND        BIT(21)                /*!< SDIO DAT0BSYEND interrupt flag */
#define SDIO_INT_FLAG_SDIOINT           BIT(22)                /*!< SDIO SDIOINT interrupt flag */
#define SDIO_INT_FLAG_ACKFAIL           BIT(23)                /*!< SDIO ACKFAIL interrupt flag */
#define SDIO_INT_FLAG_ACKTO             BIT(24)                /*!< SDIO ACKTO interrupt flag */
#define SDIO_INT_FLAG_VOLSWEND          BIT(25)                /*!< SDIO VOLSWEND interrupt flag */
#define SDIO_INT_FLAG_CLKSTOP           BIT(26)                /*!< SDIO CLKSTOP interrupt flag */
#define SDIO_INT_FLAG_IDMAERR           BIT(27)                /*!< SDIO IDMAERR interrupt flag */
#define SDIO_INT_FLAG_IDMAEND           BIT(28)                /*!< SDIO IDMAEND interrupt flag */

/* SDIO read wait type */
#define SDIO_READWAITTYPE_DAT2          (uint32_t)0x00000000U  /*!< read wait control using SDIO_DAT[2] */
#define SDIO_READWAITTYPE_CLK           SDIO_DATACTL_RWTYPE    /*!< read wait control by stopping SDIO_CLK */

/* function declarations */
/* de/initialization functions, hardware clock, bus mode, power_state and SDIO clock configuration */
/* deinitialize the SDIO */
void sdio_deinit(uint32_t sdio_periph);
/* configure the SDIO clock */
void sdio_clock_config(uint32_t sdio_periph, uint32_t clock_edge, uint32_t clock_powersave, uint32_t clock_division);
/* set receive clock */
void sdio_clock_receive_set(uint32_t sdio_periph, uint32_t clock_receive);
/* enable hardware clock control */
void sdio_hardware_clock_enable(uint32_t sdio_periph);
/* disable hardware clock control */
void sdio_hardware_clock_disable(uint32_t sdio_periph);
/* set different SDIO card bus mode */
void sdio_bus_mode_set(uint32_t sdio_periph, uint32_t bus_mode);
/* set SDIO bus speed */
void sdio_bus_speed_set(uint32_t sdio_periph, uint32_t bus_speed);
/* set SDIO data rate */
void sdio_data_rate_set(uint32_t sdio_periph, uint32_t data_rate);
/* set direction polarity of data and command */
void sdio_direction_polarity_set(uint32_t sdio_periph, uint32_t dirpl);
/* set the SDIO power state */
void sdio_power_state_set(uint32_t sdio_periph, uint32_t power_state);
/* get the SDIO power state */
uint32_t sdio_power_state_get(uint32_t sdio_periph);

/* configure the command index, argument, command type, response type, wait type and CSM(command state machine) to send command functions */
/* configure the command and response */
void sdio_command_response_config(uint32_t sdio_periph, uint32_t cmd_index, uint32_t cmd_argument, uint32_t response_type);
/* set the command state machine wait type */
void sdio_wait_type_set(uint32_t sdio_periph, uint32_t wait_type);
/* enable the CSM transfer command mode(treats the command as a data transfer command) */
void sdio_trans_start_enable(uint32_t sdio_periph);
/* disable the CSM transfer command mode(treats the command as a data transfer command) */
void sdio_trans_start_disable(uint32_t sdio_periph);
/* enable the CSM stop command mode(treats the command as a data stop transfer command) */
void sdio_trans_stop_enable(uint32_t sdio_periph);
/* disable the CSM stop command mode(treats the command as a data stop transfer command) */
void sdio_trans_stop_disable(uint32_t sdio_periph);
/* enable the CSM(command state machine) */
void sdio_csm_enable(uint32_t sdio_periph);
/* disable the CSM(command state machine) */
void sdio_csm_disable(uint32_t sdio_periph);
/* get the last response command index */
uint8_t sdio_command_index_get(uint32_t sdio_periph);
/* get the response for the last received command */
uint32_t sdio_response_get(uint32_t sdio_periph, uint32_t sdio_responsex);
/* enable the data hold */
void sdio_hold_enable(uint32_t sdio_periph);
/* disable the data hold */
void sdio_hold_disable(uint32_t sdio_periph);
/* enable the SDIO suspend mode (the CSM treats the command as a Suspend command or Resume command) */
void sdio_suspend_enable(uint32_t sdio_periph);
/* disable the SDIO suspend mode (the CSM treats the command as a Suspend command or Resume command) */
void sdio_suspend_disable(uint32_t sdio_periph);

/* configure the data timeout, length, block size, transfer mode, direction and DSM for data transfer functions */
/* configure the data timeout, data length and data block size */
void sdio_data_config(uint32_t sdio_periph, uint32_t data_timeout, uint32_t data_length, uint32_t data_blocksize);
/* configure the data transfer mode and direction */
void sdio_data_transfer_config(uint32_t sdio_periph, uint32_t transfer_mode, uint32_t transfer_direction);
/* enable the DSM(data state machine) for data transfer */
void sdio_dsm_enable(uint32_t sdio_periph);
/* disable the DSM(data state machine) for data transfer */
void sdio_dsm_disable(uint32_t sdio_periph);
/* write data(one word) to the transmit FIFO */
void sdio_data_write(uint32_t sdio_periph, uint32_t data);
/* read data(one word) from the receive FIFO */
uint32_t sdio_data_read(uint32_t sdio_periph);
/* get the number of remaining data bytes to be transferred to card */
uint32_t sdio_data_counter_get(uint32_t sdio_periph);
/* enable the FIFO buffer reset */
void sdio_fifo_reset_enable(uint32_t sdio_periph);
/* disable the FIFO buffer reset */
void sdio_fifo_reset_disable(uint32_t sdio_periph);

/* configure the IMDA */
/* set IDMA buffer mode and size */
void sdio_idma_set(uint32_t sdio_periph, uint32_t buffer_mode, uint32_t buffer_size);
/* set IDMA buffer0 address */
void sdio_idma_buffer0_address_set(uint32_t sdio_periph, uint32_t buffer_address);
/* set IDMA buffer1 address */
void sdio_idma_buffer1_address_set(uint32_t sdio_periph, uint32_t buffer_address);
/* get the IDMA double buffer address selection bit */
uint32_t sdio_buffer_selection_get(uint32_t sdio_periph);
/* select IDMA buffer */
void sdio_idma_buffer_select(uint32_t sdio_periph, uint32_t buffer_select);
/* enable the IDMA request for SDIO */
void sdio_idma_enable(uint32_t sdio_periph);
/* disable the IDMA request for SDIO */
void sdio_idma_disable(uint32_t sdio_periph);

/* flag and interrupt functions */
/* get the flags state of SDIO */
FlagStatus sdio_flag_get(uint32_t sdio_periph, uint32_t flag);
/* clear the pending flags of SDIO */
void sdio_flag_clear(uint32_t sdio_periph, uint32_t flag);
/* enable the SDIO interrupt */
void sdio_interrupt_enable(uint32_t sdio_periph, uint32_t int_flag);
/* disable the SDIO interrupt */
void sdio_interrupt_disable(uint32_t sdio_periph, uint32_t int_flag);
/* get the interrupt flags state of SDIO */
FlagStatus sdio_interrupt_flag_get(uint32_t sdio_periph, uint32_t int_flag);
/* clear the interrupt pending flags of SDIO */
void sdio_interrupt_flag_clear(uint32_t sdio_periph, uint32_t int_flag);

/* SDIO voltage switch functions */
/* enable voltage switch */
void sdio_voltage_switch_enable(uint32_t sdio_periph);
/* disable voltage switch */
void sdio_voltage_switch_disable(uint32_t sdio_periph);
/* enable voltage switch sequence */
void sdio_voltage_switch_sequence_enable(uint32_t sdio_periph);
/* disable voltage switch sequence */
void sdio_voltage_switch_sequence_disable(uint32_t sdio_periph);

/* SDIO boot function */
/* set boot mode */
void sdio_boot_mode_set(uint32_t sdio_periph, uint32_t boot_mode);
/* enbale DSM(data state machine) boot acknowledgment */
void sdio_boot_ack_enable(uint32_t sdio_periph);
/* disbale DSM(data state machine) boot acknowledgment */
void sdio_boot_ack_disable(uint32_t sdio_periph);
/* set boot ACK timeout period */
void sdio_boot_acktimeout_set(uint32_t sdio_periph, uint32_t timeout);
/* enable boot operation */
void sdio_boot_enable(uint32_t sdio_periph);
/* disable boot operation */
void sdio_boot_disable(uint32_t sdio_periph);
#endif /* GD32H7XX_SDIO_H */
