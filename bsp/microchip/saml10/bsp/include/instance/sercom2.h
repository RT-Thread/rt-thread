/**
 * \file
 *
 * \brief Instance description for SERCOM2
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
#ifndef _SAML10_SERCOM2_INSTANCE_H_
#define _SAML10_SERCOM2_INSTANCE_H_

/* ========== Register definition for SERCOM2 peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_SERCOM2_I2CM_CTRLA  (0x42000C00) /**< (SERCOM2) I2CM Control A */
#define REG_SERCOM2_I2CM_CTRLB  (0x42000C04) /**< (SERCOM2) I2CM Control B */
#define REG_SERCOM2_I2CM_BAUD   (0x42000C0C) /**< (SERCOM2) I2CM Baud Rate */
#define REG_SERCOM2_I2CM_INTENCLR (0x42000C14) /**< (SERCOM2) I2CM Interrupt Enable Clear */
#define REG_SERCOM2_I2CM_INTENSET (0x42000C16) /**< (SERCOM2) I2CM Interrupt Enable Set */
#define REG_SERCOM2_I2CM_INTFLAG (0x42000C18) /**< (SERCOM2) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM2_I2CM_STATUS (0x42000C1A) /**< (SERCOM2) I2CM Status */
#define REG_SERCOM2_I2CM_SYNCBUSY (0x42000C1C) /**< (SERCOM2) I2CM Synchronization Busy */
#define REG_SERCOM2_I2CM_ADDR   (0x42000C24) /**< (SERCOM2) I2CM Address */
#define REG_SERCOM2_I2CM_DATA   (0x42000C28) /**< (SERCOM2) I2CM Data */
#define REG_SERCOM2_I2CM_DBGCTRL (0x42000C30) /**< (SERCOM2) I2CM Debug Control */
#define REG_SERCOM2_I2CS_CTRLA  (0x42000C00) /**< (SERCOM2) I2CS Control A */
#define REG_SERCOM2_I2CS_CTRLB  (0x42000C04) /**< (SERCOM2) I2CS Control B */
#define REG_SERCOM2_I2CS_INTENCLR (0x42000C14) /**< (SERCOM2) I2CS Interrupt Enable Clear */
#define REG_SERCOM2_I2CS_INTENSET (0x42000C16) /**< (SERCOM2) I2CS Interrupt Enable Set */
#define REG_SERCOM2_I2CS_INTFLAG (0x42000C18) /**< (SERCOM2) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM2_I2CS_STATUS (0x42000C1A) /**< (SERCOM2) I2CS Status */
#define REG_SERCOM2_I2CS_SYNCBUSY (0x42000C1C) /**< (SERCOM2) I2CS Synchronization Busy */
#define REG_SERCOM2_I2CS_ADDR   (0x42000C24) /**< (SERCOM2) I2CS Address */
#define REG_SERCOM2_I2CS_DATA   (0x42000C28) /**< (SERCOM2) I2CS Data */
#define REG_SERCOM2_SPI_CTRLA   (0x42000C00) /**< (SERCOM2) SPI Control A */
#define REG_SERCOM2_SPI_CTRLB   (0x42000C04) /**< (SERCOM2) SPI Control B */
#define REG_SERCOM2_SPI_BAUD    (0x42000C0C) /**< (SERCOM2) SPI Baud Rate */
#define REG_SERCOM2_SPI_INTENCLR (0x42000C14) /**< (SERCOM2) SPI Interrupt Enable Clear */
#define REG_SERCOM2_SPI_INTENSET (0x42000C16) /**< (SERCOM2) SPI Interrupt Enable Set */
#define REG_SERCOM2_SPI_INTFLAG (0x42000C18) /**< (SERCOM2) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM2_SPI_STATUS  (0x42000C1A) /**< (SERCOM2) SPI Status */
#define REG_SERCOM2_SPI_SYNCBUSY (0x42000C1C) /**< (SERCOM2) SPI Synchronization Busy */
#define REG_SERCOM2_SPI_ADDR    (0x42000C24) /**< (SERCOM2) SPI Address */
#define REG_SERCOM2_SPI_DATA    (0x42000C28) /**< (SERCOM2) SPI Data */
#define REG_SERCOM2_SPI_DBGCTRL (0x42000C30) /**< (SERCOM2) SPI Debug Control */
#define REG_SERCOM2_USART_CTRLA (0x42000C00) /**< (SERCOM2) USART Control A */
#define REG_SERCOM2_USART_CTRLB (0x42000C04) /**< (SERCOM2) USART Control B */
#define REG_SERCOM2_USART_CTRLC (0x42000C08) /**< (SERCOM2) USART Control C */
#define REG_SERCOM2_USART_BAUD  (0x42000C0C) /**< (SERCOM2) USART Baud Rate */
#define REG_SERCOM2_USART_RXPL  (0x42000C0E) /**< (SERCOM2) USART Receive Pulse Length */
#define REG_SERCOM2_USART_INTENCLR (0x42000C14) /**< (SERCOM2) USART Interrupt Enable Clear */
#define REG_SERCOM2_USART_INTENSET (0x42000C16) /**< (SERCOM2) USART Interrupt Enable Set */
#define REG_SERCOM2_USART_INTFLAG (0x42000C18) /**< (SERCOM2) USART Interrupt Flag Status and Clear */
#define REG_SERCOM2_USART_STATUS (0x42000C1A) /**< (SERCOM2) USART Status */
#define REG_SERCOM2_USART_SYNCBUSY (0x42000C1C) /**< (SERCOM2) USART Synchronization Busy */
#define REG_SERCOM2_USART_RXERRCNT (0x42000C20) /**< (SERCOM2) USART Receive Error Count */
#define REG_SERCOM2_USART_DATA  (0x42000C28) /**< (SERCOM2) USART Data */
#define REG_SERCOM2_USART_DBGCTRL (0x42000C30) /**< (SERCOM2) USART Debug Control */

#else

#define REG_SERCOM2_I2CM_CTRLA  (*(__IO uint32_t*)0x42000C00U) /**< (SERCOM2) I2CM Control A */
#define REG_SERCOM2_I2CM_CTRLB  (*(__IO uint32_t*)0x42000C04U) /**< (SERCOM2) I2CM Control B */
#define REG_SERCOM2_I2CM_BAUD   (*(__IO uint32_t*)0x42000C0CU) /**< (SERCOM2) I2CM Baud Rate */
#define REG_SERCOM2_I2CM_INTENCLR (*(__IO uint8_t*)0x42000C14U) /**< (SERCOM2) I2CM Interrupt Enable Clear */
#define REG_SERCOM2_I2CM_INTENSET (*(__IO uint8_t*)0x42000C16U) /**< (SERCOM2) I2CM Interrupt Enable Set */
#define REG_SERCOM2_I2CM_INTFLAG (*(__IO uint8_t*)0x42000C18U) /**< (SERCOM2) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM2_I2CM_STATUS (*(__IO uint16_t*)0x42000C1AU) /**< (SERCOM2) I2CM Status */
#define REG_SERCOM2_I2CM_SYNCBUSY (*(__I  uint32_t*)0x42000C1CU) /**< (SERCOM2) I2CM Synchronization Busy */
#define REG_SERCOM2_I2CM_ADDR   (*(__IO uint32_t*)0x42000C24U) /**< (SERCOM2) I2CM Address */
#define REG_SERCOM2_I2CM_DATA   (*(__IO uint8_t*)0x42000C28U) /**< (SERCOM2) I2CM Data */
#define REG_SERCOM2_I2CM_DBGCTRL (*(__IO uint8_t*)0x42000C30U) /**< (SERCOM2) I2CM Debug Control */
#define REG_SERCOM2_I2CS_CTRLA  (*(__IO uint32_t*)0x42000C00U) /**< (SERCOM2) I2CS Control A */
#define REG_SERCOM2_I2CS_CTRLB  (*(__IO uint32_t*)0x42000C04U) /**< (SERCOM2) I2CS Control B */
#define REG_SERCOM2_I2CS_INTENCLR (*(__IO uint8_t*)0x42000C14U) /**< (SERCOM2) I2CS Interrupt Enable Clear */
#define REG_SERCOM2_I2CS_INTENSET (*(__IO uint8_t*)0x42000C16U) /**< (SERCOM2) I2CS Interrupt Enable Set */
#define REG_SERCOM2_I2CS_INTFLAG (*(__IO uint8_t*)0x42000C18U) /**< (SERCOM2) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM2_I2CS_STATUS (*(__IO uint16_t*)0x42000C1AU) /**< (SERCOM2) I2CS Status */
#define REG_SERCOM2_I2CS_SYNCBUSY (*(__I  uint32_t*)0x42000C1CU) /**< (SERCOM2) I2CS Synchronization Busy */
#define REG_SERCOM2_I2CS_ADDR   (*(__IO uint32_t*)0x42000C24U) /**< (SERCOM2) I2CS Address */
#define REG_SERCOM2_I2CS_DATA   (*(__IO uint8_t*)0x42000C28U) /**< (SERCOM2) I2CS Data */
#define REG_SERCOM2_SPI_CTRLA   (*(__IO uint32_t*)0x42000C00U) /**< (SERCOM2) SPI Control A */
#define REG_SERCOM2_SPI_CTRLB   (*(__IO uint32_t*)0x42000C04U) /**< (SERCOM2) SPI Control B */
#define REG_SERCOM2_SPI_BAUD    (*(__IO uint8_t*)0x42000C0CU) /**< (SERCOM2) SPI Baud Rate */
#define REG_SERCOM2_SPI_INTENCLR (*(__IO uint8_t*)0x42000C14U) /**< (SERCOM2) SPI Interrupt Enable Clear */
#define REG_SERCOM2_SPI_INTENSET (*(__IO uint8_t*)0x42000C16U) /**< (SERCOM2) SPI Interrupt Enable Set */
#define REG_SERCOM2_SPI_INTFLAG (*(__IO uint8_t*)0x42000C18U) /**< (SERCOM2) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM2_SPI_STATUS  (*(__IO uint16_t*)0x42000C1AU) /**< (SERCOM2) SPI Status */
#define REG_SERCOM2_SPI_SYNCBUSY (*(__I  uint32_t*)0x42000C1CU) /**< (SERCOM2) SPI Synchronization Busy */
#define REG_SERCOM2_SPI_ADDR    (*(__IO uint32_t*)0x42000C24U) /**< (SERCOM2) SPI Address */
#define REG_SERCOM2_SPI_DATA    (*(__IO uint32_t*)0x42000C28U) /**< (SERCOM2) SPI Data */
#define REG_SERCOM2_SPI_DBGCTRL (*(__IO uint8_t*)0x42000C30U) /**< (SERCOM2) SPI Debug Control */
#define REG_SERCOM2_USART_CTRLA (*(__IO uint32_t*)0x42000C00U) /**< (SERCOM2) USART Control A */
#define REG_SERCOM2_USART_CTRLB (*(__IO uint32_t*)0x42000C04U) /**< (SERCOM2) USART Control B */
#define REG_SERCOM2_USART_CTRLC (*(__IO uint32_t*)0x42000C08U) /**< (SERCOM2) USART Control C */
#define REG_SERCOM2_USART_BAUD  (*(__IO uint16_t*)0x42000C0CU) /**< (SERCOM2) USART Baud Rate */
#define REG_SERCOM2_USART_RXPL  (*(__IO uint8_t*)0x42000C0EU) /**< (SERCOM2) USART Receive Pulse Length */
#define REG_SERCOM2_USART_INTENCLR (*(__IO uint8_t*)0x42000C14U) /**< (SERCOM2) USART Interrupt Enable Clear */
#define REG_SERCOM2_USART_INTENSET (*(__IO uint8_t*)0x42000C16U) /**< (SERCOM2) USART Interrupt Enable Set */
#define REG_SERCOM2_USART_INTFLAG (*(__IO uint8_t*)0x42000C18U) /**< (SERCOM2) USART Interrupt Flag Status and Clear */
#define REG_SERCOM2_USART_STATUS (*(__IO uint16_t*)0x42000C1AU) /**< (SERCOM2) USART Status */
#define REG_SERCOM2_USART_SYNCBUSY (*(__I  uint32_t*)0x42000C1CU) /**< (SERCOM2) USART Synchronization Busy */
#define REG_SERCOM2_USART_RXERRCNT (*(__I  uint8_t*)0x42000C20U) /**< (SERCOM2) USART Receive Error Count */
#define REG_SERCOM2_USART_DATA  (*(__IO uint16_t*)0x42000C28U) /**< (SERCOM2) USART Data */
#define REG_SERCOM2_USART_DBGCTRL (*(__IO uint8_t*)0x42000C30U) /**< (SERCOM2) USART Debug Control */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for SERCOM2 peripheral ========== */
#define SERCOM2_DMAC_ID_RX                       8          /* Index of DMA RX trigger */
#define SERCOM2_DMAC_ID_TX                       9          /* Index of DMA TX trigger */
#define SERCOM2_FIFO_DEPTH_POWER                 1          /* Rx Fifo depth = 2^FIFO_DEPTH_POWER */
#define SERCOM2_GCLK_ID_CORE                     13         
#define SERCOM2_GCLK_ID_SLOW                     10         
#define SERCOM2_INT_MSB                          6          
#define SERCOM2_PMSB                             3          
#define SERCOM2_SPI                              1          /* SPI mode implemented? */
#define SERCOM2_TWIM                             0          /* TWI Master mode implemented? */
#define SERCOM2_TWIS                             0          /* TWI Slave mode implemented? */
#define SERCOM2_TWI_HSMODE                       0          /* TWI HighSpeed mode implemented? */
#define SERCOM2_USART                            1          /* USART mode implemented? */
#define SERCOM2_USART_AUTOBAUD                   1          /* USART AUTOBAUD mode implemented? */
#define SERCOM2_USART_ISO7816                    1          /* USART ISO7816 mode implemented? */
#define SERCOM2_USART_LIN_MASTER                 0          /* USART LIN Master mode implemented? */
#define SERCOM2_USART_RS485                      1          /* USART RS485 mode implemented? */
#define SERCOM2_INSTANCE_ID                      67         

#endif /* _SAML10_SERCOM2_INSTANCE_ */
