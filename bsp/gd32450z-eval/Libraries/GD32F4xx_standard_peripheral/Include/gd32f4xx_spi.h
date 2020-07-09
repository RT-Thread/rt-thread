/*!
    \file  gd32f4xx_spi.h
    \brief definitions for the SPI
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef GD32F4XX_SPI_H
#define GD32F4XX_SPI_H

#include "gd32f4xx.h"

/* SPIx(x=0,1,2,3,4,5) definitions */
#define SPI0                            (SPI_BASE + 0x0000F800U)
#define SPI1                            SPI_BASE
#define SPI2                            (SPI_BASE + 0x00000400U)
#define SPI3                            (SPI_BASE + 0x0000FC00U)
#define SPI4                            (SPI_BASE + 0x00011800U)
#define SPI5                            (SPI_BASE + 0x00011C00U)

/* I2Sx_ADD(x=1,2) definitions */
#define I2S1_ADD                        I2S_ADD_BASE
#define I2S2_ADD                        (I2S_ADD_BASE + 0x00000C00U)

/* SPI registers definitions */
#define SPI_CTL0(spix)                  REG32((spix) + 0x00U)                   /*!< SPI control register 0 */
#define SPI_CTL1(spix)                  REG32((spix) + 0x04U)                   /*!< SPI control register 1*/
#define SPI_STAT(spix)                  REG32((spix) + 0x08U)                   /*!< SPI status register */
#define SPI_DATA(spix)                  REG32((spix) + 0x0CU)                   /*!< SPI data register */
#define SPI_CRCPOLY(spix)               REG32((spix) + 0x10U)                   /*!< SPI CRC polynomial register */
#define SPI_RCRC(spix)                  REG32((spix) + 0x14U)                   /*!< SPI receive CRC register */
#define SPI_TCRC(spix)                  REG32((spix) + 0x18U)                   /*!< SPI transmit CRC register */
#define SPI_I2SCTL(spix)                REG32((spix) + 0x1CU)                   /*!< SPI I2S control register */
#define SPI_I2SPSC(spix)                REG32((spix) + 0x20U)                   /*!< SPI I2S clock prescaler register */
#define SPI_QCTL(spix)                  REG32((spix) + 0x80U)                   /*!< SPI quad mode control register */

/* I2S_ADD registers definitions */
#define I2S_ADD_CTL0(i2sx_add)          REG32((i2sx_add) + 0x00U)               /*!< I2S_ADD control register 0 */
#define I2S_ADD_CTL1(i2sx_add)          REG32((i2sx_add) + 0x04U)               /*!< I2S_ADD control register 1*/
#define I2S_ADD_STAT(i2sx_add)          REG32((i2sx_add) + 0x08U)               /*!< I2S_ADD status register */
#define I2S_ADD_DATA(i2sx_add)          REG32((i2sx_add) + 0x0CU)               /*!< I2S_ADD data register */
#define I2S_ADD_CRCPOLY(i2sx_add)       REG32((i2sx_add) + 0x10U)               /*!< I2S_ADD CRC polynomial register */
#define I2S_ADD_RCRC(i2sx_add)          REG32((i2sx_add) + 0x14U)               /*!< I2S_ADD receive CRC register */
#define I2S_ADD_TCRC(i2sx_add)          REG32((i2sx_add) + 0x18U)               /*!< I2S_ADD transmit CRC register */
#define I2S_ADD_I2SCTL(i2sx_add)        REG32((i2sx_add) + 0x1CU)               /*!< I2S_ADD I2S control register */
#define I2S_ADD_I2SPSC(i2sx_add)        REG32((i2sx_add) + 0x20U)               /*!< I2S_ADD I2S clock prescaler register */

/* bits definitions */
/* SPIx_CTL0 */
#define SPI_CTL0_CKPH                   BIT(0)                                  /*!< clock phase selection*/
#define SPI_CTL0_CKPL                   BIT(1)                                  /*!< clock polarity selection */
#define SPI_CTL0_MSTMOD                 BIT(2)                                  /*!< master mode enable */
#define SPI_CTL0_PSC                    BITS(3,5)                               /*!< master clock prescaler selection */
#define SPI_CTL0_SPIEN                  BIT(6)                                  /*!< SPI enable*/
#define SPI_CTL0_LF                     BIT(7)                                  /*!< lsb first mode */
#define SPI_CTL0_SWNSS                  BIT(8)                                  /*!< nss pin selection in nss software mode */
#define SPI_CTL0_SWNSSEN                BIT(9)                                  /*!< nss software mode selection */
#define SPI_CTL0_RO                     BIT(10)                                 /*!< receive only */
#define SPI_CTL0_FF16                   BIT(11)                                 /*!< data frame size */
#define SPI_CTL0_CRCNT                  BIT(12)                                 /*!< CRC next transfer */
#define SPI_CTL0_CRCEN                  BIT(13)                                 /*!< CRC calculation enable */
#define SPI_CTL0_BDOEN                  BIT(14)                                 /*!< bidirectional transmit output enable*/
#define SPI_CTL0_BDEN                   BIT(15)                                 /*!< bidirectional enable */

/* SPIx_CTL1 */
#define SPI_CTL1_DMAREN                 BIT(0)                                  /*!< receive buffer dma enable */
#define SPI_CTL1_DMATEN                 BIT(1)                                  /*!< transmit buffer dma enable */
#define SPI_CTL1_NSSDRV                 BIT(2)                                  /*!< drive nss output */
#define SPI_CTL1_TMOD                   BIT(4)                                  /*!< SPI TI mode enable */
#define SPI_CTL1_ERRIE                  BIT(5)                                  /*!< errors interrupt enable */
#define SPI_CTL1_RBNEIE                 BIT(6)                                  /*!< receive buffer not empty interrupt enable */
#define SPI_CTL1_TBEIE                  BIT(7)                                  /*!< transmit buffer empty interrupt enable */

/* SPIx_STAT */
#define SPI_STAT_RBNE                   BIT(0)                                  /*!< receive buffer not empty */
#define SPI_STAT_TBE                    BIT(1)                                  /*!< transmit buffer empty */
#define SPI_STAT_I2SCH                  BIT(2)                                  /*!< I2S channel side */
#define SPI_STAT_TXURERR                BIT(3)                                  /*!< I2S transmission underrun error bit */
#define SPI_STAT_CRCERR                 BIT(4)                                  /*!< SPI CRC error bit */
#define SPI_STAT_CONFERR                BIT(5)                                  /*!< SPI configuration error */
#define SPI_STAT_RXORERR                BIT(6)                                  /*!< SPI reception overrun error Bit */
#define SPI_STAT_TRANS                  BIT(7)                                  /*!< transmitting on-going Bit */
#define SPI_STAT_FERR                   BIT(8)                                  /*!< format error */

/* SPI_DATA */
#define SPI_DATA_DATA                   BITS(0,15)                              /*!< data transfer register */

/* SPI_CRCPOLY */
#define SPI_CRCPOLY_CPR                 BITS(0,15)                              /*!< CRC polynomial register */

/* SPI_RCRC */
#define SPI_RCRC_RCR                    BITS(0,15)                              /*!< RX CRC register */

/* SPI_TCRC */
#define SPI_TCRC_TCR                    BITS(0,15)                              /*!< RX CRC register */

/* SPIx_I2SCTL */
#define SPI_I2SCTL_CHLEN                BIT(0)                                  /*!< channel length */
#define SPI_I2SCTL_DTLEN                BITS(1,2)                               /*!< data length */
#define SPI_I2SCTL_CKPL                 BIT(3)                                  /*!< idle state clock polarity */
#define SPI_I2SCTL_I2SSTD               BITS(4,5)                               /*!< I2S standard selection */
#define SPI_I2SCTL_PCMSMOD              BIT(7)                                  /*!< PCM frame synchronization mode */
#define SPI_I2SCTL_I2SOPMOD             BITS(8,9)                               /*!< I2S operation mode */
#define SPI_I2SCTL_I2SEN                BIT(10)                                 /*!< I2S enable */
#define SPI_I2SCTL_I2SSEL               BIT(11)                                 /*!< I2S mode selection */

/* SPIx_I2S_PSC */
#define SPI_I2SPSC_DIV                  BITS(0,7)                               /*!< dividing factor for the prescaler */
#define SPI_I2SPSC_OF                   BIT(8)                                  /*!< odd factor for the prescaler */
#define SPI_I2SPSC_MCKOEN               BIT(9)                                  /*!< I2S MCK output enable */

/* SPIx_SPI_QCTL(only SPI5) */
#define SPI_QCTL_QMOD                   BIT(0)                                  /*!< quad-SPI mode enable */
#define SPI_QCTL_QRD                    BIT(1)                                  /*!< quad-SPI mode read select */
#define SPI_QCTL_IO23_DRV               BIT(2)                                  /*!< drive SPI_IO2 and SPI_IO3 enable */

/* constants definitions */
/* SPI and I2S parameter struct definitions */
typedef struct
{   
    uint32_t device_mode;                                                       /*!< SPI master or slave */
    uint32_t trans_mode;                                                        /*!< SPI transtype */
    uint32_t frame_size;                                                        /*!< SPI frame size */
    uint32_t nss;                                                               /*!< SPI nss control by handware or software */
    uint32_t endian;                                                            /*!< SPI big endian or little endian */
    uint32_t clock_polarity_phase;                                              /*!< SPI clock phase and polarity */
    uint32_t prescale;                                                          /*!< SPI prescale factor */
}spi_parameter_struct;

/* SPI struct parameter options */
#define SPI_MASTER                      (SPI_CTL0_MSTMOD | SPI_CTL0_SWNSS)      /*!< SPI as master */
#define SPI_SLAVE                       ((uint32_t)0x00000000U)                 /*!< SPI as slave */

#define SPI_BIDIRECTIONAL_TEANSMIT      SPI_CTL0_BDOEN                          /*!< SPI work in transmit-only mode */
#define SPI_BIDIRECTIONAL_RECEIVE       ~SPI_CTL0_BDOEN                         /*!< SPI work in receive-only mode */

#define SPI_TRANSMODE_FULLDUPLEX        ((uint32_t)0x00000000U)                 /*!< SPI receive and send data at fullduplex communication */
#define SPI_TRANSMODE_RECEIVEONLY       SPI_CTL0_RO                             /*!< SPI only receive data */
#define SPI_TRANSMODE_BDRECEIVE         SPI_CTL0_BDEN                           /*!< bidirectional receive data */
#define SPI_TRANSMODE_BDTRANSMIT        (SPI_CTL0_BDEN | SPI_CTL0_BDOEN)        /*!< bidirectional transmit data*/

#define SPI_FRAMESIZE_16BIT             SPI_CTL0_FF16                           /*!< SPI frame size is 16 bits */
#define SPI_FRAMESIZE_8BIT              ((uint32_t)0x00000000U)                 /*!< SPI frame size is 8 bits */

#define SPI_NSS_SOFT                    SPI_CTL0_SWNSSEN                        /*!< SPI nss control by sofrware */
#define SPI_NSS_HARD                    ((uint32_t)0x00000000U)                 /*!< SPI nss control by hardware */

#define SPI_ENDIAN_MSB                  ((uint32_t)0x00000000U)                 /*!< SPI transmit way is big endian:transmit MSB first */
#define SPI_ENDIAN_LSB                  SPI_CTL0_LF                             /*!< SPI transmit way is little endian:transmit LSB first */

#define SPI_CK_PL_LOW_PH_1EDGE          ((uint32_t)0x00000000U)                 /*!< SPI clock polarity is low level and phase is first edge */
#define SPI_CK_PL_HIGH_PH_1EDGE         SPI_CTL0_CKPL                           /*!< SPI clock polarity is high level and phase is first edge */
#define SPI_CK_PL_LOW_PH_2EDGE          SPI_CTL0_CKPH                           /*!< SPI clock polarity is low level and phase is second edge */
#define SPI_CK_PL_HIGH_PH_2EDGE         (SPI_CTL0_CKPL|SPI_CTL0_CKPH)           /*!< SPI clock polarity is high level and phase is second edge */

#define CTL0_PSC(regval)                (BITS(3,5)&((uint32_t)(regval)<<3))
#define SPI_PSC_2                       CTL0_PSC(0)                             /*!< SPI clock prescale factor is 2 */
#define SPI_PSC_4                       CTL0_PSC(1)                             /*!< SPI clock prescale factor is 4 */
#define SPI_PSC_8                       CTL0_PSC(2)                             /*!< SPI clock prescale factor is 8 */
#define SPI_PSC_16                      CTL0_PSC(3)                             /*!< SPI clock prescale factor is 16 */
#define SPI_PSC_32                      CTL0_PSC(4)                             /*!< SPI clock prescale factor is 32 */
#define SPI_PSC_64                      CTL0_PSC(5)                             /*!< SPI clock prescale factor is 64 */
#define SPI_PSC_128                     CTL0_PSC(6)                             /*!< SPI clock prescale factor is 128 */
#define SPI_PSC_256                     CTL0_PSC(7)                             /*!< SPI clock prescale factor is 256 */

/* I2S parameter options */
#define I2S_AUDIOSAMPLE_8K              ((uint32_t)8000U)                       /*!< I2S audio sample rate is 8khz */
#define I2S_AUDIOSAMPLE_11K             ((uint32_t)11025U)                      /*!< I2S audio sample rate is 11khz */
#define I2S_AUDIOSAMPLE_16K             ((uint32_t)16000U)                      /*!< I2S audio sample rate is 16khz */
#define I2S_AUDIOSAMPLE_22K             ((uint32_t)22050U)                      /*!< I2S audio sample rate is 22khz */
#define I2S_AUDIOSAMPLE_32K             ((uint32_t)32000U)                      /*!< I2S audio sample rate is 32khz */
#define I2S_AUDIOSAMPLE_44K             ((uint32_t)44100U)                      /*!< I2S audio sample rate is 44khz */
#define I2S_AUDIOSAMPLE_48K             ((uint32_t)48000U)                      /*!< I2S audio sample rate is 48khz */
#define I2S_AUDIOSAMPLE_96K             ((uint32_t)96000U)                      /*!< I2S audio sample rate is 96khz */
#define I2S_AUDIOSAMPLE_192K            ((uint32_t)192000U)                     /*!< I2S audio sample rate is 192khz */

#define I2SCTL_DTLEN(regval)            (BITS(1,2)&((uint32_t)(regval)<<1))
#define I2S_FRAMEFORMAT_DT16B_CH16B     I2SCTL_DTLEN(0)                         /*!< I2S data length is 16 bit and channel length is 16 bit */
#define I2S_FRAMEFORMAT_DT16B_CH32B     (I2SCTL_DTLEN(0)|SPI_I2SCTL_CHLEN)      /*!< I2S data length is 16 bit and channel length is 32 bit */
#define I2S_FRAMEFORMAT_DT24B_CH32B     (I2SCTL_DTLEN(1)|SPI_I2SCTL_CHLEN)      /*!< I2S data length is 24 bit and channel length is 32 bit */
#define I2S_FRAMEFORMAT_DT32B_CH32B     (I2SCTL_DTLEN(2)|SPI_I2SCTL_CHLEN)      /*!< I2S data length is 32 bit and channel length is 32 bit */
                                                                               
#define I2S_MCKOUT_DISABLE              ((uint32_t)0x00000000U)                 /*!< I2S master clock output disable */
#define I2S_MCKOUT_ENABLE               SPI_I2SPSC_MCKOEN                       /*!< I2S master clock output enable */
                                                                           
#define I2SCTL_I2SOPMOD(regval)         (BITS(8,9)&((uint32_t)(regval)<<8))
#define I2S_MODE_SLAVETX                I2SCTL_I2SOPMOD(0)                      /*!< I2S slave transmit mode */
#define I2S_MODE_SLAVERX                I2SCTL_I2SOPMOD(1)                      /*!< I2S slave receive mode */
#define I2S_MODE_MASTERTX               I2SCTL_I2SOPMOD(2)                      /*!< I2S master transmit mode */
#define I2S_MODE_MASTERRX               I2SCTL_I2SOPMOD(3)                      /*!< I2S master receive mode */

#define I2SCTL_I2SSTD(regval)           (BITS(4,5)&((uint32_t)(regval)<<4))
#define I2S_STD_PHILLIPS                I2SCTL_I2SSTD(0)                        /*!< I2S phillips standard */
#define I2S_STD_MSB                     I2SCTL_I2SSTD(1)                        /*!< I2S MSB standard */
#define I2S_STD_LSB                     I2SCTL_I2SSTD(2)                        /*!< I2S LSB standard */
#define I2S_STD_PCMSHORT                I2SCTL_I2SSTD(3)                        /*!< I2S PCM short standard */
#define I2S_STD_PCMLONG                 (I2SCTL_I2SSTD(3)|SPI_I2SCTL_PCMSMOD)   /*!< I2S PCM long standard */

#define I2S_CKPL_LOW                    ((uint32_t)0x00000000U)                 /*!< I2S clock polarity low level */
#define I2S_CKPL_HIGH                   SPI_I2SCTL_CKPL                         /*!< I2S clock polarity high level */

/* SPI dma constants definitions */                                    
#define SPI_DMA_TRANSMIT                ((uint8_t)0x00U)                        /*!< SPI transmit data DMA */
#define SPI_DMA_RECEIVE                 ((uint8_t)0x01U)                        /*!< SPI receive data DMA */

/* SPI CRC constants definitions */
#define SPI_CRC_TX                      ((uint8_t)0x00U)                        /*!< SPI transmit CRC value */
#define SPI_CRC_RX                      ((uint8_t)0x01U)                        /*!< SPI receive CRC value */

/* SPI interrupt constants definitions */
#define SPI_I2S_INT_TBE                 ((uint8_t)0x00U)                        /*!< transmit buffer empty interrupt */
#define SPI_I2S_INT_RBNE                ((uint8_t)0x01U)                        /*!< receive buffer not empty interrupt */
#define SPI_I2S_INT_RXORERR             ((uint8_t)0x02U)                        /*!< overrun interrupt */
#define SPI_INT_CONFERR                 ((uint8_t)0x03U)                        /*!< config error interrupt */
#define SPI_INT_CRCERR                  ((uint8_t)0x04U)                        /*!< CRC error interrupt */
#define I2S_INT_TXURERR                 ((uint8_t)0x05U)                        /*!< underrun error interrupt */
#define SPI_I2S_INT_ERR                 ((uint8_t)0x06U)                        /*!< error interrupt */
#define SPI_I2S_INT_FERR                ((uint8_t)0x07U)                        /*!< format error interrupt */

/* SPI flag definitions */                                                  
#define SPI_FLAG_RBNE                   SPI_STAT_RBNE                           /*!< receive buffer not empty flag */
#define SPI_FLAG_TBE                    SPI_STAT_TBE                            /*!< transmit buffer empty flag */
#define SPI_FLAG_CRCERR                 SPI_STAT_CRCERR                         /*!< CRC error flag */
#define SPI_FLAG_CONFERR                SPI_STAT_CONFERR                        /*!< mode config error flag */
#define SPI_FLAG_RXORERR                SPI_STAT_RXORERR                        /*!< receive overrun flag */
#define SPI_FLAG_TRANS                  SPI_STAT_TRANS                          /*!< transmit on-going flag */
#define SPI_FLAG_FERR                   SPI_STAT_FERR                           /*!< format error interrupt flag */
#define I2S_FLAG_RBNE                   SPI_STAT_RBNE                           /*!< receive buffer not empty flag */
#define I2S_FLAG_TBE                    SPI_STAT_TBE                            /*!< transmit buffer empty flag */
#define I2S_FLAG_CH                     SPI_STAT_I2SCH                          /*!< transmit buffer empty interrupt */
#define I2S_FLAG_TXURERR                SPI_STAT_TXURERR                        /*!< underrun error flag */
#define I2S_FLAG_RXORERR                SPI_STAT_RXORERR                        /*!< overrun flag */
#define I2S_FLAG_TRANS                  SPI_STAT_TRANS                          /*!< transmit on-going flag */
#define I2S_FLAG_FERR                   SPI_STAT_FERR                           /*!< format error interrupt flag */

/* function declarations */
/* SPI and I2S reset */
void spi_i2s_deinit(uint32_t spi_periph);
/* SPI parameter initialization */
void spi_init(uint32_t spi_periph,spi_parameter_struct* spi_struct);
/* SPI enable */
void spi_enable(uint32_t spi_periph);
/* SPI disable */
void spi_disable(uint32_t spi_periph);

/* I2S parameter initialization */
void i2s_init(uint32_t spi_periph,uint32_t i2s_mode,uint32_t i2s_standard,uint32_t i2s_ckpl);
/* I2S prescale configuration */
void i2s_psc_config(uint32_t spi_periph,uint32_t i2s_audiosample,uint32_t i2s_frameformat,uint32_t i2s_mckout);
/* I2S enable */
void i2s_enable(uint32_t spi_periph);
/* I2S disable */
void i2s_disable(uint32_t spi_periph);

/* SPI nss output enable */
void spi_nss_output_enable(uint32_t spi_periph);
/* SPI nss output disable */
void spi_nss_output_disable(uint32_t spi_periph);
/* SPI nss pin high level in software mode */
void spi_nss_internal_high(uint32_t spi_periph);
/* SPI nss pin low level in software mode */
void spi_nss_internal_low(uint32_t spi_periph);

/* SPI dma enable */
void spi_dma_enable(uint32_t spi_periph,uint8_t spi_dma);
/* SPI dma disable */
void spi_dma_disable(uint32_t spi_periph,uint8_t spi_dma);

/* configure SPI/I2S data frame format */
void spi_i2s_data_frame_format_config(uint32_t spi_periph,uint16_t frame_format);
/* transmit data */
void spi_i2s_data_transmit(uint32_t spi_periph,uint16_t data);
/* receive data */
uint16_t spi_i2s_data_receive(uint32_t spi_periph);
/* configure SPI bidirectional transfer direction  */
void spi_bidirectional_transfer_config(uint32_t spi_periph,uint32_t transfer_direction);

/* enable SPI interrupt */
void spi_i2s_interrupt_enable(uint32_t spi_periph,uint8_t spi_i2s_int);
/* disable SPI interrupt */
void spi_i2s_interrupt_disable(uint32_t spi_periph,uint8_t spi_i2s_int);
/* get SPI and I2S interrupt status*/
FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph,uint8_t spi_i2s_int);
/* get SPI and I2S flag status */
FlagStatus spi_i2s_flag_get(uint32_t spi_periph,uint32_t spi_i2s_flag);
/* clear SPI CRC error flag status */
void spi_crc_error_clear(uint32_t spi_periph);

/* SPI CRC polynomial set */
void spi_crc_polynomial_set(uint32_t spi_periph,uint16_t crc_poly);
/* SPI CRC polynomial get */
uint16_t spi_crc_polynomial_get(uint32_t spi_periph);
/* SPI CRC function turn on */
void spi_crc_on(uint32_t spi_periph);
/* SPI CRC function turn off */
void spi_crc_off(uint32_t spi_periph);
/* SPI next data is CRC value */
void spi_crc_next(uint32_t spi_periph);
/* get SPI CRC send value or receive value */
uint16_t spi_crc_get(uint32_t spi_periph,uint8_t spi_crc);

/* SPI TI mode enable */
void spi_ti_mode_enable(uint32_t spi_periph);
/* SPI TI mode disable */
void spi_ti_mode_disable(uint32_t spi_periph);

/* configure i2s full duplex mode */
void i2s_full_duplex_mode_config(uint32_t i2s_add_periph,uint32_t i2s_mode,uint32_t i2s_standard,uint32_t i2s_ckpl,uint32_t i2s_frameformat);

/* quad wire SPI enable */
void qspi_enable(uint32_t spi_periph);
/* quad wire SPI disable */
void qspi_disable(uint32_t spi_periph);
/* quad wire SPI write enable */
void qspi_write_enable(uint32_t spi_periph);
/* quad wire SPI read enable */
void qspi_read_enable(uint32_t spi_periph);
/* quad wire SPI_IO2 and SPI_IO3 pin output enable */
void qspi_io23_output_enable(uint32_t spi_periph);
/* quad wire SPI_IO2 and SPI_IO3 pin output disable */
void qspi_io23_output_disable(uint32_t spi_periph);

#endif /* GD32F4XX_SPI_H */
