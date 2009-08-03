/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_spi.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      SPI firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_SPI_H
#define __STM32F10x_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* SPI Init structure definition */
typedef struct
{
  u16 SPI_Direction;
  u16 SPI_Mode;
  u16 SPI_DataSize;
  u16 SPI_CPOL;
  u16 SPI_CPHA;
  u16 SPI_NSS;
  u16 SPI_BaudRatePrescaler;
  u16 SPI_FirstBit;
  u16 SPI_CRCPolynomial;
}SPI_InitTypeDef;

/* I2S Init structure definition */
typedef struct
{
  u16 I2S_Mode;
  u16 I2S_Standard;
  u16 I2S_DataFormat;
  u16 I2S_MCLKOutput;
  u16 I2S_AudioFreq;
  u16 I2S_CPOL;
}I2S_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

#define IS_SPI_ALL_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == SPI1_BASE) || \
                                   ((*(u32*)&(PERIPH)) == SPI2_BASE) || \
                                   ((*(u32*)&(PERIPH)) == SPI3_BASE))

#define IS_SPI_23_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == SPI2_BASE) || \
                                  ((*(u32*)&(PERIPH)) == SPI3_BASE))

/* SPI data direction mode */
#define SPI_Direction_2Lines_FullDuplex ((u16)0x0000)
#define SPI_Direction_2Lines_RxOnly     ((u16)0x0400)
#define SPI_Direction_1Line_Rx          ((u16)0x8000)
#define SPI_Direction_1Line_Tx          ((u16)0xC000)

#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_Rx) || \
                                     ((MODE) == SPI_Direction_1Line_Tx))

/* SPI master/slave mode */
#define SPI_Mode_Master                 ((u16)0x0104)
#define SPI_Mode_Slave                  ((u16)0x0000)

#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))

/* SPI data size */
#define SPI_DataSize_16b                ((u16)0x0800)
#define SPI_DataSize_8b                 ((u16)0x0000)

#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DataSize_16b) || \
                                   ((DATASIZE) == SPI_DataSize_8b))

/* SPI Clock Polarity */
#define SPI_CPOL_Low                    ((u16)0x0000)
#define SPI_CPOL_High                   ((u16)0x0002)

#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))

/* SPI Clock Phase */
#define SPI_CPHA_1Edge                  ((u16)0x0000)
#define SPI_CPHA_2Edge                  ((u16)0x0001)

#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))

/* SPI Slave Select management */
#define SPI_NSS_Soft                    ((u16)0x0200)
#define SPI_NSS_Hard                    ((u16)0x0000)

#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))                         

/* SPI BaudRate Prescaler  */
#define SPI_BaudRatePrescaler_2         ((u16)0x0000)
#define SPI_BaudRatePrescaler_4         ((u16)0x0008)
#define SPI_BaudRatePrescaler_8         ((u16)0x0010)
#define SPI_BaudRatePrescaler_16        ((u16)0x0018)
#define SPI_BaudRatePrescaler_32        ((u16)0x0020)
#define SPI_BaudRatePrescaler_64        ((u16)0x0028)
#define SPI_BaudRatePrescaler_128       ((u16)0x0030)
#define SPI_BaudRatePrescaler_256       ((u16)0x0038)

#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))

/* SPI MSB/LSB transmission */
#define SPI_FirstBit_MSB                ((u16)0x0000)
#define SPI_FirstBit_LSB                ((u16)0x0080)

#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))

/* I2S Mode */
#define I2S_Mode_SlaveTx                ((u16)0x0000)
#define I2S_Mode_SlaveRx                ((u16)0x0100)
#define I2S_Mode_MasterTx               ((u16)0x0200)
#define I2S_Mode_MasterRx               ((u16)0x0300)

#define IS_I2S_MODE(MODE) (((MODE) == I2S_Mode_SlaveTx) || \
                           ((MODE) == I2S_Mode_SlaveRx) || \
                           ((MODE) == I2S_Mode_MasterTx) || \
                           ((MODE) == I2S_Mode_MasterRx) )

/* I2S Standard */
#define I2S_Standard_Phillips           ((u16)0x0000)
#define I2S_Standard_MSB                ((u16)0x0010)
#define I2S_Standard_LSB                ((u16)0x0020)
#define I2S_Standard_PCMShort           ((u16)0x0030)
#define I2S_Standard_PCMLong            ((u16)0x00B0)

#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_Standard_Phillips) || \
                                   ((STANDARD) == I2S_Standard_MSB) || \
                                   ((STANDARD) == I2S_Standard_LSB) || \
                                   ((STANDARD) == I2S_Standard_PCMShort) || \
                                   ((STANDARD) == I2S_Standard_PCMLong))

/* I2S Data Format */
#define I2S_DataFormat_16b              ((u16)0x0000)
#define I2S_DataFormat_16bextended      ((u16)0x0001)
#define I2S_DataFormat_24b              ((u16)0x0003)
#define I2S_DataFormat_32b              ((u16)0x0005)

#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DataFormat_16b) || \
                                    ((FORMAT) == I2S_DataFormat_16bextended) || \
                                    ((FORMAT) == I2S_DataFormat_24b) || \
                                    ((FORMAT) == I2S_DataFormat_32b))

/* I2S MCLK Output */ 
#define I2S_MCLKOutput_Enable           ((u16)0x0200)
#define I2S_MCLKOutput_Disable          ((u16)0x0000)

#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
                                    ((OUTPUT) == I2S_MCLKOutput_Disable))

/* I2S Audio Frequency */
#define I2S_AudioFreq_48k                ((u16)48000)
#define I2S_AudioFreq_44k                ((u16)44100)
#define I2S_AudioFreq_22k                ((u16)22050)
#define I2S_AudioFreq_16k                ((u16)16000)
#define I2S_AudioFreq_8k                 ((u16)8000)
#define I2S_AudioFreq_Default            ((u16)2)

#define IS_I2S_AUDIO_FREQ(FREQ) (((FREQ) == I2S_AudioFreq_48k) || \
                                 ((FREQ) == I2S_AudioFreq_44k) || \
                                 ((FREQ) == I2S_AudioFreq_22k) || \
                                 ((FREQ) == I2S_AudioFreq_16k) || \
                                 ((FREQ) == I2S_AudioFreq_8k)  || \
                                 ((FREQ) == I2S_AudioFreq_Default))

/* I2S Clock Polarity */
#define I2S_CPOL_Low                    ((u16)0x0000)
#define I2S_CPOL_High                   ((u16)0x0008)

#define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
                           ((CPOL) == I2S_CPOL_High))

/* SPI_I2S DMA transfer requests */
#define SPI_I2S_DMAReq_Tx               ((u16)0x0002)
#define SPI_I2S_DMAReq_Rx               ((u16)0x0001)

#define IS_SPI_I2S_DMAREQ(DMAREQ) ((((DMAREQ) & (u16)0xFFFC) == 0x00) && ((DMAREQ) != 0x00))

/* SPI NSS internal software mangement */
#define SPI_NSSInternalSoft_Set         ((u16)0x0100)
#define SPI_NSSInternalSoft_Reset       ((u16)0xFEFF)

#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))

/* SPI CRC Transmit/Receive */
#define SPI_CRC_Tx                      ((u8)0x00)
#define SPI_CRC_Rx                      ((u8)0x01)

#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))

/* SPI direction transmit/receive */
#define SPI_Direction_Rx                ((u16)0xBFFF)
#define SPI_Direction_Tx                ((u16)0x4000)

#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))

/* SPI_I2S interrupts definition */
#define SPI_I2S_IT_TXE                  ((u8)0x71)
#define SPI_I2S_IT_RXNE                 ((u8)0x60)
#define SPI_I2S_IT_ERR                  ((u8)0x50)

#define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
                                 ((IT) == SPI_I2S_IT_RXNE) || \
                                 ((IT) == SPI_I2S_IT_ERR))

#define SPI_I2S_IT_OVR                  ((u8)0x56)
#define SPI_IT_MODF                     ((u8)0x55)
#define SPI_IT_CRCERR                   ((u8)0x54)
#define I2S_IT_UDR                      ((u8)0x53)

#define IS_SPI_I2S_CLEAR_IT(IT) (((IT) == SPI_IT_CRCERR))

#define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE) || ((IT) == SPI_I2S_IT_TXE) || \
                               ((IT) == I2S_IT_UDR) || ((IT) == SPI_IT_CRCERR) || \
                               ((IT) == SPI_IT_MODF) || ((IT) == SPI_I2S_IT_OVR))

/* SPI_I2S flags definition */
#define SPI_I2S_FLAG_RXNE               ((u16)0x0001)
#define SPI_I2S_FLAG_TXE                ((u16)0x0002)
#define I2S_FLAG_CHSIDE                 ((u16)0x0004)
#define I2S_FLAG_UDR                    ((u16)0x0008)
#define SPI_FLAG_CRCERR                 ((u16)0x0010)
#define SPI_FLAG_MODF                   ((u16)0x0020)
#define SPI_I2S_FLAG_OVR                ((u16)0x0040)
#define SPI_I2S_FLAG_BSY                ((u16)0x0080)

#define IS_SPI_I2S_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))

#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == I2S_FLAG_UDR) || ((FLAG) == I2S_FLAG_CHSIDE) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE))

/* SPI CRC polynomial --------------------------------------------------------*/
#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, u8 SPI_I2S_IT, FunctionalState NewState);
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, u16 SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2S_SendData(SPI_TypeDef* SPIx, u16 Data);
u16 SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, u16 SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, u16 SPI_DataSize);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
u16 SPI_GetCRC(SPI_TypeDef* SPIx, u8 SPI_CRC);
u16 SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, u16 SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, u8 SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, u8 SPI_I2S_IT);

#endif /*__STM32F10x_SPI_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
