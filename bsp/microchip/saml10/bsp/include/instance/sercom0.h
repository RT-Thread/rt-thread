/**
 * \file
 *
 * \brief Instance description for SERCOM0
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

/* file generated from device description version 2019-01-31T14:29:25Z */
#ifndef _SAML10_SERCOM0_INSTANCE_H_
#define _SAML10_SERCOM0_INSTANCE_H_

/* ========== Register definition for SERCOM0 peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_SERCOM0_I2CM_CTRLA  (0x42000400) /**< (SERCOM0) I2CM Control A */
#define REG_SERCOM0_I2CM_CTRLB  (0x42000404) /**< (SERCOM0) I2CM Control B */
#define REG_SERCOM0_I2CM_BAUD   (0x4200040C) /**< (SERCOM0) I2CM Baud Rate */
#define REG_SERCOM0_I2CM_INTENCLR (0x42000414) /**< (SERCOM0) I2CM Interrupt Enable Clear */
#define REG_SERCOM0_I2CM_INTENSET (0x42000416) /**< (SERCOM0) I2CM Interrupt Enable Set */
#define REG_SERCOM0_I2CM_INTFLAG (0x42000418) /**< (SERCOM0) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM0_I2CM_STATUS (0x4200041A) /**< (SERCOM0) I2CM Status */
#define REG_SERCOM0_I2CM_SYNCBUSY (0x4200041C) /**< (SERCOM0) I2CM Synchronization Busy */
#define REG_SERCOM0_I2CM_ADDR   (0x42000424) /**< (SERCOM0) I2CM Address */
#define REG_SERCOM0_I2CM_DATA   (0x42000428) /**< (SERCOM0) I2CM Data */
#define REG_SERCOM0_I2CM_DBGCTRL (0x42000430) /**< (SERCOM0) I2CM Debug Control */
#define REG_SERCOM0_I2CS_CTRLA  (0x42000400) /**< (SERCOM0) I2CS Control A */
#define REG_SERCOM0_I2CS_CTRLB  (0x42000404) /**< (SERCOM0) I2CS Control B */
#define REG_SERCOM0_I2CS_INTENCLR (0x42000414) /**< (SERCOM0) I2CS Interrupt Enable Clear */
#define REG_SERCOM0_I2CS_INTENSET (0x42000416) /**< (SERCOM0) I2CS Interrupt Enable Set */
#define REG_SERCOM0_I2CS_INTFLAG (0x42000418) /**< (SERCOM0) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM0_I2CS_STATUS (0x4200041A) /**< (SERCOM0) I2CS Status */
#define REG_SERCOM0_I2CS_SYNCBUSY (0x4200041C) /**< (SERCOM0) I2CS Synchronization Busy */
#define REG_SERCOM0_I2CS_ADDR   (0x42000424) /**< (SERCOM0) I2CS Address */
#define REG_SERCOM0_I2CS_DATA   (0x42000428) /**< (SERCOM0) I2CS Data */
#define REG_SERCOM0_SPI_CTRLA   (0x42000400) /**< (SERCOM0) SPI Control A */
#define REG_SERCOM0_SPI_CTRLB   (0x42000404) /**< (SERCOM0) SPI Control B */
#define REG_SERCOM0_SPI_BAUD    (0x4200040C) /**< (SERCOM0) SPI Baud Rate */
#define REG_SERCOM0_SPI_INTENCLR (0x42000414) /**< (SERCOM0) SPI Interrupt Enable Clear */
#define REG_SERCOM0_SPI_INTENSET (0x42000416) /**< (SERCOM0) SPI Interrupt Enable Set */
#define REG_SERCOM0_SPI_INTFLAG (0x42000418) /**< (SERCOM0) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM0_SPI_STATUS  (0x4200041A) /**< (SERCOM0) SPI Status */
#define REG_SERCOM0_SPI_SYNCBUSY (0x4200041C) /**< (SERCOM0) SPI Synchronization Busy */
#define REG_SERCOM0_SPI_ADDR    (0x42000424) /**< (SERCOM0) SPI Address */
#define REG_SERCOM0_SPI_DATA    (0x42000428) /**< (SERCOM0) SPI Data */
#define REG_SERCOM0_SPI_DBGCTRL (0x42000430) /**< (SERCOM0) SPI Debug Control */
#define REG_SERCOM0_USART_CTRLA (0x42000400) /**< (SERCOM0) USART Control A */
#define REG_SERCOM0_USART_CTRLB (0x42000404) /**< (SERCOM0) USART Control B */
#define REG_SERCOM0_USART_CTRLC (0x42000408) /**< (SERCOM0) USART Control C */
#define REG_SERCOM0_USART_BAUD  (0x4200040C) /**< (SERCOM0) USART Baud Rate */
#define REG_SERCOM0_USART_RXPL  (0x4200040E) /**< (SERCOM0) USART Receive Pulse Length */
#define REG_SERCOM0_USART_INTENCLR (0x42000414) /**< (SERCOM0) USART Interrupt Enable Clear */
#define REG_SERCOM0_USART_INTENSET (0x42000416) /**< (SERCOM0) USART Interrupt Enable Set */
#define REG_SERCOM0_USART_INTFLAG (0x42000418) /**< (SERCOM0) USART Interrupt Flag Status and Clear */
#define REG_SERCOM0_USART_STATUS (0x4200041A) /**< (SERCOM0) USART Status */
#define REG_SERCOM0_USART_SYNCBUSY (0x4200041C) /**< (SERCOM0) USART Synchronization Busy */
#define REG_SERCOM0_USART_RXERRCNT (0x42000420) /**< (SERCOM0) USART Receive Error Count */
#define REG_SERCOM0_USART_DATA  (0x42000428) /**< (SERCOM0) USART Data */
#define REG_SERCOM0_USART_DBGCTRL (0x42000430) /**< (SERCOM0) USART Debug Control */

#else

#define REG_SERCOM0_I2CM_CTRLA  (*(__IO uint32_t*)0x42000400U) /**< (SERCOM0) I2CM Control A */
#define REG_SERCOM0_I2CM_CTRLB  (*(__IO uint32_t*)0x42000404U) /**< (SERCOM0) I2CM Control B */
#define REG_SERCOM0_I2CM_BAUD   (*(__IO uint32_t*)0x4200040CU) /**< (SERCOM0) I2CM Baud Rate */
#define REG_SERCOM0_I2CM_INTENCLR (*(__IO uint8_t*)0x42000414U) /**< (SERCOM0) I2CM Interrupt Enable Clear */
#define REG_SERCOM0_I2CM_INTENSET (*(__IO uint8_t*)0x42000416U) /**< (SERCOM0) I2CM Interrupt Enable Set */
#define REG_SERCOM0_I2CM_INTFLAG (*(__IO uint8_t*)0x42000418U) /**< (SERCOM0) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM0_I2CM_STATUS (*(__IO uint16_t*)0x4200041AU) /**< (SERCOM0) I2CM Status */
#define REG_SERCOM0_I2CM_SYNCBUSY (*(__I  uint32_t*)0x4200041CU) /**< (SERCOM0) I2CM Synchronization Busy */
#define REG_SERCOM0_I2CM_ADDR   (*(__IO uint32_t*)0x42000424U) /**< (SERCOM0) I2CM Address */
#define REG_SERCOM0_I2CM_DATA   (*(__IO uint8_t*)0x42000428U) /**< (SERCOM0) I2CM Data */
#define REG_SERCOM0_I2CM_DBGCTRL (*(__IO uint8_t*)0x42000430U) /**< (SERCOM0) I2CM Debug Control */
#define REG_SERCOM0_I2CS_CTRLA  (*(__IO uint32_t*)0x42000400U) /**< (SERCOM0) I2CS Control A */
#define REG_SERCOM0_I2CS_CTRLB  (*(__IO uint32_t*)0x42000404U) /**< (SERCOM0) I2CS Control B */
#define REG_SERCOM0_I2CS_INTENCLR (*(__IO uint8_t*)0x42000414U) /**< (SERCOM0) I2CS Interrupt Enable Clear */
#define REG_SERCOM0_I2CS_INTENSET (*(__IO uint8_t*)0x42000416U) /**< (SERCOM0) I2CS Interrupt Enable Set */
#define REG_SERCOM0_I2CS_INTFLAG (*(__IO uint8_t*)0x42000418U) /**< (SERCOM0) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM0_I2CS_STATUS (*(__IO uint16_t*)0x4200041AU) /**< (SERCOM0) I2CS Status */
#define REG_SERCOM0_I2CS_SYNCBUSY (*(__I  uint32_t*)0x4200041CU) /**< (SERCOM0) I2CS Synchronization Busy */
#define REG_SERCOM0_I2CS_ADDR   (*(__IO uint32_t*)0x42000424U) /**< (SERCOM0) I2CS Address */
#define REG_SERCOM0_I2CS_DATA   (*(__IO uint8_t*)0x42000428U) /**< (SERCOM0) I2CS Data */
#define REG_SERCOM0_SPI_CTRLA   (*(__IO uint32_t*)0x42000400U) /**< (SERCOM0) SPI Control A */
#define REG_SERCOM0_SPI_CTRLB   (*(__IO uint32_t*)0x42000404U) /**< (SERCOM0) SPI Control B */
#define REG_SERCOM0_SPI_BAUD    (*(__IO uint8_t*)0x4200040CU) /**< (SERCOM0) SPI Baud Rate */
#define REG_SERCOM0_SPI_INTENCLR (*(__IO uint8_t*)0x42000414U) /**< (SERCOM0) SPI Interrupt Enable Clear */
#define REG_SERCOM0_SPI_INTENSET (*(__IO uint8_t*)0x42000416U) /**< (SERCOM0) SPI Interrupt Enable Set */
#define REG_SERCOM0_SPI_INTFLAG (*(__IO uint8_t*)0x42000418U) /**< (SERCOM0) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM0_SPI_STATUS  (*(__IO uint16_t*)0x4200041AU) /**< (SERCOM0) SPI Status */
#define REG_SERCOM0_SPI_SYNCBUSY (*(__I  uint32_t*)0x4200041CU) /**< (SERCOM0) SPI Synchronization Busy */
#define REG_SERCOM0_SPI_ADDR    (*(__IO uint32_t*)0x42000424U) /**< (SERCOM0) SPI Address */
#define REG_SERCOM0_SPI_DATA    (*(__IO uint32_t*)0x42000428U) /**< (SERCOM0) SPI Data */
#define REG_SERCOM0_SPI_DBGCTRL (*(__IO uint8_t*)0x42000430U) /**< (SERCOM0) SPI Debug Control */
#define REG_SERCOM0_USART_CTRLA (*(__IO uint32_t*)0x42000400U) /**< (SERCOM0) USART Control A */
#define REG_SERCOM0_USART_CTRLB (*(__IO uint32_t*)0x42000404U) /**< (SERCOM0) USART Control B */
#define REG_SERCOM0_USART_CTRLC (*(__IO uint32_t*)0x42000408U) /**< (SERCOM0) USART Control C */
#define REG_SERCOM0_USART_BAUD  (*(__IO uint16_t*)0x4200040CU) /**< (SERCOM0) USART Baud Rate */
#define REG_SERCOM0_USART_RXPL  (*(__IO uint8_t*)0x4200040EU) /**< (SERCOM0) USART Receive Pulse Length */
#define REG_SERCOM0_USART_INTENCLR (*(__IO uint8_t*)0x42000414U) /**< (SERCOM0) USART Interrupt Enable Clear */
#define REG_SERCOM0_USART_INTENSET (*(__IO uint8_t*)0x42000416U) /**< (SERCOM0) USART Interrupt Enable Set */
#define REG_SERCOM0_USART_INTFLAG (*(__IO uint8_t*)0x42000418U) /**< (SERCOM0) USART Interrupt Flag Status and Clear */
#define REG_SERCOM0_USART_STATUS (*(__IO uint16_t*)0x4200041AU) /**< (SERCOM0) USART Status */
#define REG_SERCOM0_USART_SYNCBUSY (*(__I  uint32_t*)0x4200041CU) /**< (SERCOM0) USART Synchronization Busy */
#define REG_SERCOM0_USART_RXERRCNT (*(__I  uint8_t*)0x42000420U) /**< (SERCOM0) USART Receive Error Count */
#define REG_SERCOM0_USART_DATA  (*(__IO uint16_t*)0x42000428U) /**< (SERCOM0) USART Data */
#define REG_SERCOM0_USART_DBGCTRL (*(__IO uint8_t*)0x42000430U) /**< (SERCOM0) USART Debug Control */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for SERCOM0 peripheral ========== */
#define SERCOM0_DMAC_ID_RX                       4          /* Index of DMA RX trigger */
#define SERCOM0_DMAC_ID_TX                       5          /* Index of DMA TX trigger */
#define SERCOM0_FIFO_DEPTH_POWER                 1          /* Rx Fifo depth = 2^FIFO_DEPTH_POWER */
#define SERCOM0_GCLK_ID_CORE                     11         
#define SERCOM0_GCLK_ID_SLOW                     10         
#define SERCOM0_INT_MSB                          6          
#define SERCOM0_PMSB                             3          
#define SERCOM0_SPI                              1          /* SPI mode implemented? */
#define SERCOM0_TWIM                             1          /* TWI Master mode implemented? */
#define SERCOM0_TWIS                             1          /* TWI Slave mode implemented? */
#define SERCOM0_TWI_HSMODE                       1          /* TWI HighSpeed mode implemented? */
#define SERCOM0_USART                            1          /* USART mode implemented? */
#define SERCOM0_USART_AUTOBAUD                   0          /* USART AUTOBAUD mode implemented? */
#define SERCOM0_USART_ISO7816                    0          /* USART ISO7816 mode implemented? */
#define SERCOM0_USART_LIN_MASTER                 0          /* USART LIN Master mode implemented? */
#define SERCOM0_USART_RS485                      0          /* USART RS485 mode implemented? */
#define SERCOM0_INSTANCE_ID                      65         

#endif /* _SAML10_SERCOM0_INSTANCE_ */
