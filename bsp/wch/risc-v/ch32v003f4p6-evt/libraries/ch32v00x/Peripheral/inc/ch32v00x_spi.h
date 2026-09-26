/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v00x_spi.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/06/01
 * Description        : This file contains all the functions prototypes for the
 *                      SPI firmware library.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#ifndef __CH32V00x_SPI_H
#define __CH32V00x_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x.h>

/* SPI Init structure definition */
typedef struct
{
    uint16_t SPI_Direction; /* Specifies the SPI unidirectional or bidirectional data mode.
                               This parameter can be a value of @ref SPI_data_direction */

    uint16_t SPI_Mode; /* Specifies the SPI operating mode.
                          This parameter can be a value of @ref SPI_mode */

    uint16_t SPI_DataSize; /* Specifies the SPI data size.
                              This parameter can be a value of @ref SPI_data_size */

    uint16_t SPI_CPOL; /* Specifies the serial clock steady state.
                          This parameter can be a value of @ref SPI_Clock_Polarity 
                          When using SPI slave mode to send data, the CPOL bit should be set to 1 */

    uint16_t SPI_CPHA; /* Specifies the clock active edge for the bit capture.
                          This parameter can be a value of @ref SPI_Clock_Phase */

    uint16_t SPI_NSS; /* Specifies whether the NSS signal is managed by
                         hardware (NSS pin) or by software using the SSI bit.
                         This parameter can be a value of @ref SPI_Slave_Select_management */

    uint16_t SPI_BaudRatePrescaler; /* Specifies the Baud Rate prescaler value which will be
                                       used to configure the transmit and receive SCK clock.
                                       This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                       @note The communication clock is derived from the master
                                             clock. The slave clock does not need to be set. */

    uint16_t SPI_FirstBit; /* Specifies whether data transfers start from MSB bit. */

    uint16_t SPI_CRCPolynomial; /* Specifies the polynomial used for the CRC calculation. */
} SPI_InitTypeDef;

/* SPI_data_direction */
#define SPI_Direction_2Lines_FullDuplex    ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly        ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx             ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx             ((uint16_t)0xC000)

/* SPI_mode */
#define SPI_Mode_Master                    ((uint16_t)0x0104)
#define SPI_Mode_Slave                     ((uint16_t)0x0000)

/* SPI_data_size */
#define SPI_DataSize_16b                   ((uint16_t)0x0800)
#define SPI_DataSize_8b                    ((uint16_t)0x0000)

/* SPI_Clock_Polarity */
#define SPI_CPOL_Low                       ((uint16_t)0x0000)
#define SPI_CPOL_High                      ((uint16_t)0x0002)//When using SPI slave mode to send data, the CPOL bit should be set to 1. 

/* SPI_Clock_Phase */
#define SPI_CPHA_1Edge                     ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                     ((uint16_t)0x0001)

/* SPI_Slave_Select_management */
#define SPI_NSS_Soft                       ((uint16_t)0x0200)
#define SPI_NSS_Hard                       ((uint16_t)0x0000)

/* SPI_BaudRate_Prescaler */
#define SPI_BaudRatePrescaler_2            ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4            ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8            ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16           ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32           ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64           ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128          ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256          ((uint16_t)0x0038)

/* SPI_MSB_LSB transmission */
#define SPI_FirstBit_MSB                   ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                   ((uint16_t)0x0080)//not support SPI slave mode

/* SPI_I2S_DMA_transfer_requests */
#define SPI_I2S_DMAReq_Tx                  ((uint16_t)0x0002)
#define SPI_I2S_DMAReq_Rx                  ((uint16_t)0x0001)

/* SPI_NSS_internal_software_management */
#define SPI_NSSInternalSoft_Set            ((uint16_t)0x0100)
#define SPI_NSSInternalSoft_Reset          ((uint16_t)0xFEFF)

/* SPI_CRC_Transmit_Receive */
#define SPI_CRC_Tx                         ((uint8_t)0x00)
#define SPI_CRC_Rx                         ((uint8_t)0x01)

/* SPI_direction_transmit_receive */
#define SPI_Direction_Rx                   ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                   ((uint16_t)0x4000)

/* SPI_I2S_interrupts_definition */
#define SPI_I2S_IT_TXE                     ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE                    ((uint8_t)0x60)
#define SPI_I2S_IT_ERR                     ((uint8_t)0x50)
#define SPI_I2S_IT_OVR                     ((uint8_t)0x56)
#define SPI_IT_MODF                        ((uint8_t)0x55)
#define SPI_IT_CRCERR                      ((uint8_t)0x54)
#define I2S_IT_UDR                         ((uint8_t)0x53)

/* SPI_I2S_flags_definition */
#define SPI_I2S_FLAG_RXNE                  ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE                   ((uint16_t)0x0002)
#define I2S_FLAG_CHSIDE                    ((uint16_t)0x0004)
#define I2S_FLAG_UDR                       ((uint16_t)0x0008)
#define SPI_FLAG_CRCERR                    ((uint16_t)0x0010)
#define SPI_FLAG_MODF                      ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR                   ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BSY                   ((uint16_t)0x0080)

void       SPI_I2S_DeInit(SPI_TypeDef *SPIx);
void       SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void       SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);
void       SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void       SPI_I2S_ITConfig(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
void       SPI_I2S_DMACmd(SPI_TypeDef *SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void       SPI_I2S_SendData(SPI_TypeDef *SPIx, uint16_t Data);
uint16_t   SPI_I2S_ReceiveData(SPI_TypeDef *SPIx);
void       SPI_NSSInternalSoftwareConfig(SPI_TypeDef *SPIx, uint16_t SPI_NSSInternalSoft);
void       SPI_SSOutputCmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void       SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint16_t SPI_DataSize);
void       SPI_TransmitCRC(SPI_TypeDef *SPIx);
void       SPI_CalculateCRC(SPI_TypeDef *SPIx, FunctionalState NewState);
uint16_t   SPI_GetCRC(SPI_TypeDef *SPIx, uint8_t SPI_CRC);
uint16_t   SPI_GetCRCPolynomial(SPI_TypeDef *SPIx);
void       SPI_BiDirectionalLineConfig(SPI_TypeDef *SPIx, uint16_t SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG);
void       SPI_I2S_ClearFlag(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG);
ITStatus   SPI_I2S_GetITStatus(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT);
void       SPI_I2S_ClearITPendingBit(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT);

#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_SPI_H */
