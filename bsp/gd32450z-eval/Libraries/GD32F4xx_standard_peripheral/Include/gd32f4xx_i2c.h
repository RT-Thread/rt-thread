/*!
    \file  gd32f4xx_i2c.h
    \brief definitions for the I2C
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef GD32F4XX_I2C_H
#define GD32F4XX_I2C_H

#include "gd32f4xx.h"

/* I2Cx(x=0,1,2) definitions */
#define I2C0                          I2C_BASE
#define I2C1                          (I2C_BASE+0x400U)
#define I2C2                          (I2C_BASE+0x800U)

/* registers definitions */
#define I2C_CTL0(i2cx)                REG32((i2cx) + 0x00U)      /*!< I2C control register 0 */
#define I2C_CTL1(i2cx)                REG32((i2cx) + 0x04U)      /*!< I2C control register 1 */
#define I2C_SADDR0(i2cx)              REG32((i2cx) + 0x08U)      /*!< I2C slave address register 0*/
#define I2C_SADDR1(i2cx)              REG32((i2cx) + 0x0CU)      /*!< I2C slave address register */
#define I2C_DATA(i2cx)                REG32((i2cx) + 0x10U)      /*!< I2C transfer buffer register */
#define I2C_STAT0(i2cx)               REG32((i2cx) + 0x14U)      /*!< I2C transfer status register 0 */
#define I2C_STAT1(i2cx)               REG32((i2cx) + 0x18U)      /*!< I2C transfer status register */
#define I2C_CKCFG(i2cx)               REG32((i2cx) + 0x1CU)      /*!< I2C clock configure register */
#define I2C_RT(i2cx)                  REG32((i2cx) + 0x20U)      /*!< I2C rise time register */
#define I2C_FCTL(i2cx)                REG32((i2cx) + 0x24U)      /*!< I2C filter control register */
#define I2C_SAMCS(i2cx)               REG32((i2cx) + 0x80U)      /*!< I2C SAM control and status register */


/* bits definitions */
/* I2Cx_CTL0 */
#define I2C_CTL0_I2CEN                BIT(0)        /*!< peripheral enable */
#define I2C_CTL0_SMBEN                BIT(1)        /*!< SMBus mode */
#define I2C_CTL0_SMBSEL               BIT(3)        /*!< SMBus type */
#define I2C_CTL0_ARPEN                BIT(4)        /*!< ARP enable */
#define I2C_CTL0_PECEN                BIT(5)        /*!< PEC enable */
#define I2C_CTL0_GCEN                 BIT(6)        /*!< general call enable */
#define I2C_CTL0_DISSTRC              BIT(7)        /*!< clock stretching disable (slave mode) */
#define I2C_CTL0_START                BIT(8)        /*!< start generation */
#define I2C_CTL0_STOP                 BIT(9)        /*!< stop generation */
#define I2C_CTL0_ACKEN                BIT(10)       /*!< acknowledge enable */
#define I2C_CTL0_POAP                 BIT(11)       /*!< acknowledge/PEC position (for data reception) */
#define I2C_CTL0_PECTRANS             BIT(12)       /*!< packet error checking */
#define I2C_CTL0_SALT                 BIT(13)       /*!< SMBus alert */
#define I2C_CTL0_SRESET               BIT(15)       /*!< software reset */

/* I2Cx_CTL1 */
#define I2C_CTL1_I2CCLK               BITS(0,5)     /*!< I2CCLK[5:0] bits (peripheral clock frequency) */
#define I2C_CTL1_ERRIE                BIT(8)        /*!< error interrupt inable */
#define I2C_CTL1_EVIE                 BIT(9)        /*!< event interrupt enable */
#define I2C_CTL1_BUFIE                BIT(10)       /*!< buffer interrupt enable */
#define I2C_CTL1_DMAON                BIT(11)       /*!< DMA requests enable */
#define I2C_CTL1_DMALST               BIT(12)       /*!< DMA last transfer */

/* I2Cx_SADDR0 */
#define I2C_SADDR0_ADDRESS0           BIT(0)        /*!< bit 0 of a 10-bit address */
#define I2C_SADDR0_ADDRESS            BITS(1,7)     /*!< 7-bit address or bits 7:1 of a 10-bit address */
#define I2C_SADDR0_ADDRESS_H          BITS(8,9)     /*!< highest two bits of a 10-bit address */
#define I2C_SADDR0_ADDFORMAT          BIT(15)       /*!< address mode for the I2C slave */

/* I2Cx_SADDR1 */
#define I2C_SADDR1_DUADEN             BIT(0)        /*!< aual-address mode switch */
#define I2C_SADDR1_ADDRESS2           BITS(1,7)     /*!< second I2C address for the slave in dual-address mode */

/* I2Cx_DATA */
#define I2C_DATA_TRB                  BITS(0,7)     /*!< 8-bit data register */

/* I2Cx_STAT0 */
#define I2C_STAT0_SBSEND              BIT(0)        /*!< start bit (master mode) */
#define I2C_STAT0_ADDSEND             BIT(1)        /*!< address sent (master mode)/matched (slave mode) */
#define I2C_STAT0_BTC                 BIT(2)        /*!< byte transfer finished */
#define I2C_STAT0_ADD10SEND           BIT(3)        /*!< 10-bit header sent (master mode) */
#define I2C_STAT0_STPDET              BIT(4)        /*!< stop detection (slave mode) */
#define I2C_STAT0_RBNE                BIT(6)        /*!< data register not empty (receivers) */
#define I2C_STAT0_TBE                 BIT(7)        /*!< data register empty (transmitters) */
#define I2C_STAT0_BERR                BIT(8)        /*!< bus error */
#define I2C_STAT0_LOSTARB             BIT(9)        /*!< arbitration lost (master mode) */
#define I2C_STAT0_AERR                BIT(10)       /*!< acknowledge failure */
#define I2C_STAT0_OUERR               BIT(11)       /*!< overrun/underrun */
#define I2C_STAT0_PECERR              BIT(12)       /*!< PEC error in reception */
#define I2C_STAT0_SMBTO               BIT(14)       /*!< timeout signal in SMBus mode */
#define I2C_STAT0_SMBALT              BIT(15)       /*!< SMBus alert status */

/* I2Cx_STAT1 */
#define I2C_STAT1_MASTER              BIT(0)        /*!< master/slave */
#define I2C_STAT1_I2CBSY              BIT(1)        /*!< bus busy */
#define I2C_STAT1_TRS                 BIT(2)        /*!< transmitter/receiver */
#define I2C_STAT1_RXGC                BIT(4)        /*!< general call address (slave mode) */
#define I2C_STAT1_DEFSMB              BIT(5)        /*!< SMBus device default address (slave mode) */
#define I2C_STAT1_HSTSMB              BIT(6)        /*!< SMBus host header (slave mode) */
#define I2C_STAT1_DUMODF              BIT(7)        /*!< dual flag (slave mode) */
#define I2C_STAT1_ECV                 BITS(8,15)    /*!< packet error checking register */

/* I2Cx_CKCFG */
#define I2C_CKCFG_CLKC                BITS(0,11)    /*!< clock control register in fast/standard mode (master mode) */
#define I2C_CKCFG_DTCY                BIT(14)       /*!< fast mode duty cycle */
#define I2C_CKCFG_FAST                BIT(15)       /*!< I2C speed selection in master mode */

/* I2Cx_RT */
#define I2C_RT_RISETIME               BITS(0,5)     /*!< maximum rise time in fast/standard mode (Master mode) */

/* I2Cx_FCTL */
#define I2C_FCTL_DF                   BITS(0,3)     /*!< digital noise filter */
#define I2C_FCTL_AFD                  BIT(4)        /*!< analog noise filter disable */

/* I2Cx_SAMCS */
#define I2C_SAMCS_SAMEN               BIT(0)        /*!< SAM_V interface enable */
#define I2C_SAMCS_STOEN               BIT(1)        /*!< SAM_V interface timeout detect enable */
#define I2C_SAMCS_TFFIE               BIT(4)        /*!< txframe fall interrupt enable */
#define I2C_SAMCS_TFRIE               BIT(5)        /*!< txframe rise interrupt enable */
#define I2C_SAMCS_RFFIE               BIT(6)        /*!< rxframe fall interrupt enable */
#define I2C_SAMCS_RFRIE               BIT(7)        /*!< rxframe rise interrupt enable */
#define I2C_SAMCS_TXF                 BIT(8)        /*!< level of txframe signal */
#define I2C_SAMCS_RXF                 BIT(9)        /*!< level of rxframe signal */
#define I2C_SAMCS_TFF                 BIT(12)       /*!< txframe fall flag, cleared by software write 0 */
#define I2C_SAMCS_TFR                 BIT(13)       /*!< txframe rise flag, cleared by software write 0 */
#define I2C_SAMCS_RFF                 BIT(14)       /*!< rxframe fall flag, cleared by software write 0 */
#define I2C_SAMCS_RFR                 BIT(15)       /*!< rxframe rise flag, cleared by software write 0 */


/* constants definitions */

/* the digital noise filter can filter spikes's length */
typedef enum {
    I2C_DF_DISABLE,                                     /*!< disable digital noise filter */
    I2C_DF_1PCLK,                                       /*!< enable digital noise filter and the maximum filtered spiker's length 1 PCLK1 */
    I2C_DF_2PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 2 PCLK1 */
    I2C_DF_3PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 3 PCLK1 */
    I2C_DF_4PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 4 PCLK1 */
    I2C_DF_5PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 5 PCLK1 */
    I2C_DF_6PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 6 PCLK1 */
    I2C_DF_7PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 7 PCLK1 */
    I2C_DF_8PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 8 PCLK1 */
    I2C_DF_9PCLKS,                                      /*!< enable digital noise filter and the maximum filtered spiker's length 9 PCLK1 */
    I2C_DF_10PCLKS,                                     /*!< enable digital noise filter and the maximum filtered spiker's length 10 PCLK1 */
    I2C_DF_11PCLKS,                                     /*!< enable digital noise filter and the maximum filtered spiker's length 11 PCLK1 */
    I2C_DF_12PCLKS,                                     /*!< enable digital noise filter and the maximum filtered spiker's length 12 PCLK1 */
    I2C_DF_13PCLKS,                                     /*!< enable digital noise filter and the maximum filtered spiker's length 13 PCLK1 */
    I2C_DF_14PCLKS,                                     /*!< enable digital noise filter and the maximum filtered spiker's length 14 PCLK1 */
    I2C_DF_15PCLKS                                      /*!< enable digital noise filter and the maximum filtered spiker's length 15 PCLK1 */
}i2c_digital_filter_enum;

/* SMBus/I2C mode switch and SMBus type selection */
#define I2C_I2CMODE_ENABLE            ((uint32_t)0x00000000U)                  /*!< I2C mode */
#define I2C_SMBUSMODE_ENABLE          I2C_CTL0_SMBEN                           /*!< SMBus mode */

/* SMBus/I2C mode switch and SMBus type selection */
#define I2C_SMBUS_DEVICE              ((uint32_t)0x00000000U)                  /*!< SMBus mode device type */
#define I2C_SMBUS_HOST                I2C_CTL0_SMBSEL                          /*!< SMBus mode host type */
/* I2C transfer direction */
#define I2C_TRANSMITTER               (~BIT(0))                                /*!< transmitter */
#define I2C_RECEIVER                  BIT(0)                                   /*!< receiver */

/* whether or not to send an ACK */
#define I2C_ACK_ENABLE                ((uint8_t)0x01U)                         /*!< ACK will be sent */
#define I2C_ACK_DISABLE               ((uint8_t)0x00U)                         /*!< ACK will be not sent */

/* I2C POAP position*/
#define I2C_ACKPOS_CURRENT            ((uint8_t)0x01U)                         /*!< ACKEN bit decides whether to send ACK or not for the current */
#define I2C_ACKPOS_NEXT               ((uint8_t)0x00U)                         /*!< ACKEN bit decides whether to send ACK or not for the next byte */

/* I2C dual-address mode switch */
#define I2C_DUADEN_DISABLE            ((uint8_t)0x00U)                         /*!< dual-address mode disabled */
#define I2C_DUADEN_ENABLE             ((uint8_t)0x01U)                         /*!< dual-address mode enabled */

/* whether or not to stretch SCL low */
#define I2C_SCLSTRETCH_ENABLE         ((uint32_t)0x00000000U)                  /*!< SCL stretching is enabled */
#define I2C_SCLSTRETCH_DISABLE        I2C_CTL0_DISSTRC                         /*!< SCL stretching is disabled */

/* whether or not to response to a General Call */
#define I2C_GCEN_ENABLE               I2C_CTL0_GCEN                            /*!< slave will response to a general call */
#define I2C_GCEN_DISABLE              ((uint32_t)0x00000000U)                  /*!< slave will not response to a general call */

/* software reset I2C */
#define I2C_SRESET_SET                I2C_CTL0_SRESET                          /*!< I2C is under reset */
#define I2C_SRESET_RESET              ((uint32_t)0x00000000U)                  /*!< I2C is not under reset */

/* I2C DMA mode configure */
/* DMA mode switch */
#define I2C_DMA_ON                    I2C_CTL1_DMAON                           /*!< DMA mode enabled */
#define I2C_DMA_OFF                   ((uint32_t)0x00000000U)                  /*!< DMA mode disabled */
/* flag indicating DMA last transfer */
#define I2C_DMALST_ON                 I2C_CTL1_DMALST                          /*!< next DMA EOT is the last transfer */
#define I2C_DMALST_OFF                ((uint32_t)0x00000000U)                  /*!< next DMA EOT is not the last transfer */


/* I2C PEC configure */
/* PEC enable */
#define I2C_PEC_ENABLE                I2C_CTL0_PECEN                           /*!< PEC calculation on */
#define I2C_PEC_DISABLE              ((uint32_t)0x00000000U)                   /*!< PEC calculation off */

/* PEC transfer */
#define I2C_PECTRANS_ENABLE           I2C_CTL0_PECTRANS                        /*!< transfer PEC */
#define I2C_PECTRANS_DISABLE          ((uint32_t)0x00000000U)                  /*!< not transfer PEC value */

/* I2C SMBus configure */
/* issue or not alert through SMBA pin */
#define I2C_SALTSEND_ENABLE           I2C_CTL0_SALT                            /*!< issue alert through SMBA pin */
#define I2C_SALTSEND_DISABLE          ((uint32_t)0x00000000U)                  /*!< not issue alert through SMBA */
/* ARP protocol in SMBus switch */
#define I2C_ARP_ENABLE                I2C_CTL0_ARPEN                           /*!< ARP is enabled */
#define I2C_ARP_DISABLE               ((uint32_t)0x00000000U)                  /*!< ARP is disabled */

/* I2C state */
/* I2C bit state */
#define I2C_SBSEND                    BIT(0)                                   /*!< start condition sent out in master mode */
#define I2C_ADDSEND                   BIT(1)                                   /*!< address is sent in master mode or received and matches in slave mode */
#define I2C_BTC                       BIT(2)                                   /*!< byte transmission finishes */
#define I2C_ADD10SEND                 BIT(3)                                   /*!< header of 10-bit address is sent in master mode */
#define I2C_STPDET                    BIT(4)                                   /*!< etop condition detected in slave mode */
#define I2C_RBNE                      BIT(6)                                   /*!< I2C_DATA is not Empty during receiving */
#define I2C_TBE                       BIT(7)                                   /*!< I2C_DATA is empty during transmitting */
#define I2C_BERR                      BIT(8)                                   /*!< a bus error occurs indication a unexpected start or stop condition on I2C bus */
#define I2C_LOSTARB                   BIT(9)                                   /*!< arbitration lost in master mode */
#define I2C_AERR                      BIT(10)                                  /*!< acknowledge error */
#define I2C_OUERR                     BIT(11)                                  /*!< over-run or under-run situation occurs in slave mode */
#define I2C_PECERR                    BIT(12)                                  /*!< PEC error when receiving data */
#define I2C_SMBTO                     BIT(14)                                  /*!< timeout signal in SMBus mode */
#define I2C_SMBALT                    BIT(15)                                  /*!< SMBus alert status */
#define I2C_MASTER                    (BIT(0)|BIT(31))                         /*!< a flag indicating whether I2C block is in master or slave mode */
#define I2C_I2CBSY                    (BIT(1)|BIT(31))                         /*!< busy flag */
#define I2C_TRS                       (BIT(2)|BIT(31))                         /*!< whether the I2C is a transmitter or a receiver */
#define I2C_RXGC                      (BIT(4)|BIT(31))                         /*!< general call address (00h) received */
#define I2C_DEFSMB                    (BIT(5)|BIT(31))                         /*!< default address of SMBus device */
#define I2C_HSTSMB                    (BIT(6)|BIT(31))                         /*!< SMBus host header detected in slave mode */
#define I2C_DUMODF                    (BIT(7)|BIT(31))                         /*!< dual flag in slave mode indicating which address is matched in dual-address mode */

/* I2C duty cycle in fast mode */
#define CKCFG_DTCY(regval)            (BIT(14) & ((uint32_t)(regval) << 14))
#define I2C_DTCY_2                    CKCFG_DTCY(0)                            /*!< I2C fast mode Tlow/Thigh = 2 */
#define I2C_DTCY_16_9                 CKCFG_DTCY(1)                            /*!< I2C fast mode Tlow/Thigh = 16/9 */

/* address mode for the I2C slave */
#define SADDR0_ADDFORMAT(regval)      (BIT(15) & ((regval) << 15))
#define I2C_ADDFORMAT_7BITS           SADDR0_ADDFORMAT(0)                      /*!< address:7 bits */
#define I2C_ADDFORMAT_10BITS          SADDR0_ADDFORMAT(1)                      /*!< address:10 bits */

/* function declarations */
/* reset I2C */
void i2c_deinit(uint32_t i2c_periph);
/* I2C clock configure */
void i2c_clock_config(uint32_t i2c_periph,uint32_t clkspeed,uint32_t dutycyc);
/* I2C address configure */
void i2c_mode_addr_config(uint32_t i2c_periph,uint32_t i2cmod,uint32_t addformat,uint32_t addr);
/* SMBus type selection */
void i2c_smbus_type_config(uint32_t i2c_periph,uint32_t type);
/* whether or not to send an ACK */
void i2c_ack_config(uint32_t i2c_periph,uint8_t ack);
/* I2C POAP position configure */
void i2c_ackpos_config(uint32_t i2c_periph,uint8_t pos);
/* master send slave address */
void i2c_master_addressing(uint32_t i2c_periph,uint8_t addr,uint32_t trandirection);
/* dual-address mode switch */
void i2c_dualaddr_enable(uint32_t i2c_periph, uint8_t dualaddr);

/* enable i2c */
void i2c_enable(uint32_t i2c_periph);
/* disable i2c */
void i2c_disable(uint32_t i2c_periph);
/* generate a START condition on I2C bus */
void i2c_start_on_bus(uint32_t i2c_periph);
/* generate a STOP condition on I2C bus */
void i2c_stop_on_bus(uint32_t i2c_periph);
/* i2c transmit data function */
void i2c_transmit_data(uint32_t i2c_periph,uint8_t data);
/* i2c receive data function */
uint8_t i2c_receive_data(uint32_t i2c_periph);
/* I2C DMA mode enable */
void i2c_dma_enable(uint32_t i2c_periph,uint32_t dmastste);
/* flag indicating DMA last transfer */
void i2c_dma_last_transfer_enable(uint32_t i2c_periph,uint32_t dmalast);
/* whether to stretch SCL low when data is not ready in slave mode  */
void i2c_stretch_scl_low_config(uint32_t i2c_periph,uint32_t stretchpara );
/* whether or not to response to a general call  */
void i2c_slave_response_to_gcall_config(uint32_t i2c_periph,uint32_t gcallpara);
/* software reset I2C  */
void i2c_software_reset_config(uint32_t i2c_periph, uint32_t sreset);

/* check i2c state */
FlagStatus i2c_flag_get(uint32_t i2c_periph,uint32_t state);
/* clear i2c state */
void i2c_flag_clear(uint32_t i2c_periph,uint32_t state);
/* enable i2c interrupt */
void i2c_interrupt_enable(uint32_t i2c_periph,uint32_t inttype);
/* disable i2c interrupt */
void i2c_interrupt_disable(uint32_t i2c_periph,uint32_t inttype);

/* I2C PEC calculation on or off */
void i2c_pec_enable(uint32_t i2c_periph,uint32_t pecstate);
/* I2C whether to transfer PEC value */
void i2c_pec_transfer_enable(uint32_t i2c_periph,uint32_t pecpara);
/* packet error checking value  */
uint8_t i2c_pec_value(uint32_t i2c_periph);

/* I2C issue alert through SMBA pin */
void i2c_smbus_alert_issue(uint32_t i2c_periph,uint32_t smbuspara);
/* I2C ARP protocol in SMBus switch  */
void i2c_smbus_arp_enable(uint32_t i2c_periph,uint32_t arpstate);

/* I2C analog noise filter disable */
void i2c_analog_noise_filter_disable(uint32_t i2c_periph);
/* I2C analog noise filter enable */
void i2c_analog_noise_filter_enable(uint32_t i2c_periph);
/* digital noise filter */
void i2c_digital_noise_filter_config(uint32_t i2c_periph,i2c_digital_filter_enum dfilterpara);

/* enable SAM_V interface */
void i2c_sam_enable(uint32_t i2c_periph);
/* disable SAM_V interface */
void i2c_sam_disable(uint32_t i2c_periph);
/* enable SAM_V interface timeout detect */
void i2c_sam_timeout_enable(uint32_t i2c_periph);
/* disable SAM_V interface timeout detect */
void i2c_sam_timeout_disable(uint32_t i2c_periph);
/* enable the specified I2C SAM interrupt */
void i2c_sam_interrupt_enable(uint32_t i2c_periph,uint32_t inttype);
/* disable the specified I2C SAM interrupt */
void i2c_sam_interrupt_disable(uint32_t i2c_periph,uint32_t inttype);
/* check i2c SAM state */
FlagStatus i2c_sam_flag_get(uint32_t i2c_periph,uint32_t samstate);
/* clear i2c SAM state */
void i2c_sam_flag_clear(uint32_t i2c_periph,uint32_t samstate);


#endif /* GD32F4XX_I2C_H */
