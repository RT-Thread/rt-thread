/**
 * \file
 *
 * \brief Instance description for SERCOM1
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
#ifndef _SAML10_SERCOM1_INSTANCE_H_
#define _SAML10_SERCOM1_INSTANCE_H_

/* ========== Register definition for SERCOM1 peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_SERCOM1_I2CM_CTRLA  (0x42000800) /**< (SERCOM1) I2CM Control A */
#define REG_SERCOM1_I2CM_CTRLB  (0x42000804) /**< (SERCOM1) I2CM Control B */
#define REG_SERCOM1_I2CM_BAUD   (0x4200080C) /**< (SERCOM1) I2CM Baud Rate */
#define REG_SERCOM1_I2CM_INTENCLR (0x42000814) /**< (SERCOM1) I2CM Interrupt Enable Clear */
#define REG_SERCOM1_I2CM_INTENSET (0x42000816) /**< (SERCOM1) I2CM Interrupt Enable Set */
#define REG_SERCOM1_I2CM_INTFLAG (0x42000818) /**< (SERCOM1) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CM_STATUS (0x4200081A) /**< (SERCOM1) I2CM Status */
#define REG_SERCOM1_I2CM_SYNCBUSY (0x4200081C) /**< (SERCOM1) I2CM Synchronization Busy */
#define REG_SERCOM1_I2CM_ADDR   (0x42000824) /**< (SERCOM1) I2CM Address */
#define REG_SERCOM1_I2CM_DATA   (0x42000828) /**< (SERCOM1) I2CM Data */
#define REG_SERCOM1_I2CM_DBGCTRL (0x42000830) /**< (SERCOM1) I2CM Debug Control */
#define REG_SERCOM1_I2CS_CTRLA  (0x42000800) /**< (SERCOM1) I2CS Control A */
#define REG_SERCOM1_I2CS_CTRLB  (0x42000804) /**< (SERCOM1) I2CS Control B */
#define REG_SERCOM1_I2CS_INTENCLR (0x42000814) /**< (SERCOM1) I2CS Interrupt Enable Clear */
#define REG_SERCOM1_I2CS_INTENSET (0x42000816) /**< (SERCOM1) I2CS Interrupt Enable Set */
#define REG_SERCOM1_I2CS_INTFLAG (0x42000818) /**< (SERCOM1) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CS_STATUS (0x4200081A) /**< (SERCOM1) I2CS Status */
#define REG_SERCOM1_I2CS_SYNCBUSY (0x4200081C) /**< (SERCOM1) I2CS Synchronization Busy */
#define REG_SERCOM1_I2CS_ADDR   (0x42000824) /**< (SERCOM1) I2CS Address */
#define REG_SERCOM1_I2CS_DATA   (0x42000828) /**< (SERCOM1) I2CS Data */
#define REG_SERCOM1_SPI_CTRLA   (0x42000800) /**< (SERCOM1) SPI Control A */
#define REG_SERCOM1_SPI_CTRLB   (0x42000804) /**< (SERCOM1) SPI Control B */
#define REG_SERCOM1_SPI_BAUD    (0x4200080C) /**< (SERCOM1) SPI Baud Rate */
#define REG_SERCOM1_SPI_INTENCLR (0x42000814) /**< (SERCOM1) SPI Interrupt Enable Clear */
#define REG_SERCOM1_SPI_INTENSET (0x42000816) /**< (SERCOM1) SPI Interrupt Enable Set */
#define REG_SERCOM1_SPI_INTFLAG (0x42000818) /**< (SERCOM1) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM1_SPI_STATUS  (0x4200081A) /**< (SERCOM1) SPI Status */
#define REG_SERCOM1_SPI_SYNCBUSY (0x4200081C) /**< (SERCOM1) SPI Synchronization Busy */
#define REG_SERCOM1_SPI_ADDR    (0x42000824) /**< (SERCOM1) SPI Address */
#define REG_SERCOM1_SPI_DATA    (0x42000828) /**< (SERCOM1) SPI Data */
#define REG_SERCOM1_SPI_DBGCTRL (0x42000830) /**< (SERCOM1) SPI Debug Control */
#define REG_SERCOM1_USART_CTRLA (0x42000800) /**< (SERCOM1) USART Control A */
#define REG_SERCOM1_USART_CTRLB (0x42000804) /**< (SERCOM1) USART Control B */
#define REG_SERCOM1_USART_CTRLC (0x42000808) /**< (SERCOM1) USART Control C */
#define REG_SERCOM1_USART_BAUD  (0x4200080C) /**< (SERCOM1) USART Baud Rate */
#define REG_SERCOM1_USART_RXPL  (0x4200080E) /**< (SERCOM1) USART Receive Pulse Length */
#define REG_SERCOM1_USART_INTENCLR (0x42000814) /**< (SERCOM1) USART Interrupt Enable Clear */
#define REG_SERCOM1_USART_INTENSET (0x42000816) /**< (SERCOM1) USART Interrupt Enable Set */
#define REG_SERCOM1_USART_INTFLAG (0x42000818) /**< (SERCOM1) USART Interrupt Flag Status and Clear */
#define REG_SERCOM1_USART_STATUS (0x4200081A) /**< (SERCOM1) USART Status */
#define REG_SERCOM1_USART_SYNCBUSY (0x4200081C) /**< (SERCOM1) USART Synchronization Busy */
#define REG_SERCOM1_USART_RXERRCNT (0x42000820) /**< (SERCOM1) USART Receive Error Count */
#define REG_SERCOM1_USART_DATA  (0x42000828) /**< (SERCOM1) USART Data */
#define REG_SERCOM1_USART_DBGCTRL (0x42000830) /**< (SERCOM1) USART Debug Control */

#else

#define REG_SERCOM1_I2CM_CTRLA  (*(__IO uint32_t*)0x42000800U) /**< (SERCOM1) I2CM Control A */
#define REG_SERCOM1_I2CM_CTRLB  (*(__IO uint32_t*)0x42000804U) /**< (SERCOM1) I2CM Control B */
#define REG_SERCOM1_I2CM_BAUD   (*(__IO uint32_t*)0x4200080CU) /**< (SERCOM1) I2CM Baud Rate */
#define REG_SERCOM1_I2CM_INTENCLR (*(__IO uint8_t*)0x42000814U) /**< (SERCOM1) I2CM Interrupt Enable Clear */
#define REG_SERCOM1_I2CM_INTENSET (*(__IO uint8_t*)0x42000816U) /**< (SERCOM1) I2CM Interrupt Enable Set */
#define REG_SERCOM1_I2CM_INTFLAG (*(__IO uint8_t*)0x42000818U) /**< (SERCOM1) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CM_STATUS (*(__IO uint16_t*)0x4200081AU) /**< (SERCOM1) I2CM Status */
#define REG_SERCOM1_I2CM_SYNCBUSY (*(__I  uint32_t*)0x4200081CU) /**< (SERCOM1) I2CM Synchronization Busy */
#define REG_SERCOM1_I2CM_ADDR   (*(__IO uint32_t*)0x42000824U) /**< (SERCOM1) I2CM Address */
#define REG_SERCOM1_I2CM_DATA   (*(__IO uint8_t*)0x42000828U) /**< (SERCOM1) I2CM Data */
#define REG_SERCOM1_I2CM_DBGCTRL (*(__IO uint8_t*)0x42000830U) /**< (SERCOM1) I2CM Debug Control */
#define REG_SERCOM1_I2CS_CTRLA  (*(__IO uint32_t*)0x42000800U) /**< (SERCOM1) I2CS Control A */
#define REG_SERCOM1_I2CS_CTRLB  (*(__IO uint32_t*)0x42000804U) /**< (SERCOM1) I2CS Control B */
#define REG_SERCOM1_I2CS_INTENCLR (*(__IO uint8_t*)0x42000814U) /**< (SERCOM1) I2CS Interrupt Enable Clear */
#define REG_SERCOM1_I2CS_INTENSET (*(__IO uint8_t*)0x42000816U) /**< (SERCOM1) I2CS Interrupt Enable Set */
#define REG_SERCOM1_I2CS_INTFLAG (*(__IO uint8_t*)0x42000818U) /**< (SERCOM1) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CS_STATUS (*(__IO uint16_t*)0x4200081AU) /**< (SERCOM1) I2CS Status */
#define REG_SERCOM1_I2CS_SYNCBUSY (*(__I  uint32_t*)0x4200081CU) /**< (SERCOM1) I2CS Synchronization Busy */
#define REG_SERCOM1_I2CS_ADDR   (*(__IO uint32_t*)0x42000824U) /**< (SERCOM1) I2CS Address */
#define REG_SERCOM1_I2CS_DATA   (*(__IO uint8_t*)0x42000828U) /**< (SERCOM1) I2CS Data */
#define REG_SERCOM1_SPI_CTRLA   (*(__IO uint32_t*)0x42000800U) /**< (SERCOM1) SPI Control A */
#define REG_SERCOM1_SPI_CTRLB   (*(__IO uint32_t*)0x42000804U) /**< (SERCOM1) SPI Control B */
#define REG_SERCOM1_SPI_BAUD    (*(__IO uint8_t*)0x4200080CU) /**< (SERCOM1) SPI Baud Rate */
#define REG_SERCOM1_SPI_INTENCLR (*(__IO uint8_t*)0x42000814U) /**< (SERCOM1) SPI Interrupt Enable Clear */
#define REG_SERCOM1_SPI_INTENSET (*(__IO uint8_t*)0x42000816U) /**< (SERCOM1) SPI Interrupt Enable Set */
#define REG_SERCOM1_SPI_INTFLAG (*(__IO uint8_t*)0x42000818U) /**< (SERCOM1) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM1_SPI_STATUS  (*(__IO uint16_t*)0x4200081AU) /**< (SERCOM1) SPI Status */
#define REG_SERCOM1_SPI_SYNCBUSY (*(__I  uint32_t*)0x4200081CU) /**< (SERCOM1) SPI Synchronization Busy */
#define REG_SERCOM1_SPI_ADDR    (*(__IO uint32_t*)0x42000824U) /**< (SERCOM1) SPI Address */
#define REG_SERCOM1_SPI_DATA    (*(__IO uint32_t*)0x42000828U) /**< (SERCOM1) SPI Data */
#define REG_SERCOM1_SPI_DBGCTRL (*(__IO uint8_t*)0x42000830U) /**< (SERCOM1) SPI Debug Control */
#define REG_SERCOM1_USART_CTRLA (*(__IO uint32_t*)0x42000800U) /**< (SERCOM1) USART Control A */
#define REG_SERCOM1_USART_CTRLB (*(__IO uint32_t*)0x42000804U) /**< (SERCOM1) USART Control B */
#define REG_SERCOM1_USART_CTRLC (*(__IO uint32_t*)0x42000808U) /**< (SERCOM1) USART Control C */
#define REG_SERCOM1_USART_BAUD  (*(__IO uint16_t*)0x4200080CU) /**< (SERCOM1) USART Baud Rate */
#define REG_SERCOM1_USART_RXPL  (*(__IO uint8_t*)0x4200080EU) /**< (SERCOM1) USART Receive Pulse Length */
#define REG_SERCOM1_USART_INTENCLR (*(__IO uint8_t*)0x42000814U) /**< (SERCOM1) USART Interrupt Enable Clear */
#define REG_SERCOM1_USART_INTENSET (*(__IO uint8_t*)0x42000816U) /**< (SERCOM1) USART Interrupt Enable Set */
#define REG_SERCOM1_USART_INTFLAG (*(__IO uint8_t*)0x42000818U) /**< (SERCOM1) USART Interrupt Flag Status and Clear */
#define REG_SERCOM1_USART_STATUS (*(__IO uint16_t*)0x4200081AU) /**< (SERCOM1) USART Status */
#define REG_SERCOM1_USART_SYNCBUSY (*(__I  uint32_t*)0x4200081CU) /**< (SERCOM1) USART Synchronization Busy */
#define REG_SERCOM1_USART_RXERRCNT (*(__I  uint8_t*)0x42000820U) /**< (SERCOM1) USART Receive Error Count */
#define REG_SERCOM1_USART_DATA  (*(__IO uint16_t*)0x42000828U) /**< (SERCOM1) USART Data */
#define REG_SERCOM1_USART_DBGCTRL (*(__IO uint8_t*)0x42000830U) /**< (SERCOM1) USART Debug Control */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for SERCOM1 peripheral ========== */
#define SERCOM1_DMAC_ID_RX                       6          /* Index of DMA RX trigger */
#define SERCOM1_DMAC_ID_TX                       7          /* Index of DMA TX trigger */
#define SERCOM1_FIFO_DEPTH_POWER                 2          /* Rx Fifo depth = 2^FIFO_DEPTH_POWER */
#define SERCOM1_GCLK_ID_CORE                     12         
#define SERCOM1_GCLK_ID_SLOW                     10         
#define SERCOM1_INT_MSB                          6          
#define SERCOM1_PMSB                             3          
#define SERCOM1_SPI                              1          /* SPI mode implemented? */
#define SERCOM1_TWIM                             1          /* TWI Master mode implemented? */
#define SERCOM1_TWIS                             1          /* TWI Slave mode implemented? */
#define SERCOM1_TWI_HSMODE                       0          /* TWI HighSpeed mode implemented? */
#define SERCOM1_USART                            1          /* USART mode implemented? */
#define SERCOM1_USART_AUTOBAUD                   0          /* USART AUTOBAUD mode implemented? */
#define SERCOM1_USART_ISO7816                    0          /* USART ISO7816 mode implemented? */
#define SERCOM1_USART_LIN_MASTER                 0          /* USART LIN Master mode implemented? */
#define SERCOM1_USART_RS485                      0          /* USART RS485 mode implemented? */
#define SERCOM1_INSTANCE_ID                      66         

#endif /* _SAML10_SERCOM1_INSTANCE_ */
