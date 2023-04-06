/**
  ******************************************************************************
  * @file    stm32u5xx_ll_spi.h
  * @author  MCD Application Team
  * @brief   Header file of SPI LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_LL_SPI_H
#define STM32U5xx_LL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(SPI1) || defined(SPI2) || defined(SPI3)

/** @defgroup SPI_LL SPI
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/** @defgroup SPI_LL_Private_Macros SPI Private Macros
  * @{
  */
#define IS_LL_SPI_GRP1_INSTANCE(__INSTANCE__)   (((__INSTANCE__) == SPI1) ||\
                                                 ((__INSTANCE__) == SPI2)

#define IS_LL_SPI_GRP2_INSTANCE(__INSTANCE__)    ((__INSTANCE__) == SPI3)
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup SPI_LL_Exported_Types SPI Exported Types
  * @{
  */

/**
  * @brief  SPI Init structures definition
  */
typedef struct
{
  uint32_t TransferDirection;       /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_LL_EC_TRANSFER_MODE.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetTransferDirection().*/

  uint32_t Mode;                    /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref SPI_LL_EC_MODE.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetMode().*/

  uint32_t DataWidth;               /*!< Specifies the SPI data width.
                                         This parameter can be a value of @ref SPI_LL_EC_DATAWIDTH.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetDataWidth().*/

  uint32_t ClockPolarity;           /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_LL_EC_POLARITY.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetClockPolarity().*/

  uint32_t ClockPhase;              /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_LL_EC_PHASE.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetClockPhase().*/

  uint32_t NSS;                     /*!< Specifies whether the NSS signal is managed by hardware (NSS pin)
                                         or by software using the SSI bit.

                                         This parameter can be a value of @ref SPI_LL_EC_NSS_MODE.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetNSSMode().*/

  uint32_t BaudRate;                /*!< Specifies the BaudRate prescaler value which will be used to configure
                                         the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_LL_EC_BAUDRATEPRESCALER.
                                         @note The communication clock is derived from the master clock.
                                         The slave clock does not need to be set.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetBaudRatePrescaler().*/

  uint32_t BitOrder;                /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_LL_EC_BIT_ORDER.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetTransferBitOrder().*/

  uint32_t CRCCalculation;          /*!< Specifies if the CRC calculation is enabled or not.
                                         This parameter can be a value of @ref SPI_LL_EC_CRC_CALCULATION.

                                         This feature can be modified afterwards using unitary functions
                                         @ref LL_SPI_EnableCRC() and @ref LL_SPI_DisableCRC().*/

  uint32_t CRCPoly;                 /*!< Specifies the polynomial used for the CRC calculation.
                                         This parameter must be a number between Min_Data = 0x00
                                         and Max_Data = 0xFFFFFFFF.

                                         This feature can be modified afterwards using unitary function
                                         @ref LL_SPI_SetCRCPolynomial().*/

} LL_SPI_InitTypeDef;

/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Constants SPI Exported Constants
  * @{
  */

/** @defgroup SPI_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_SPI_ReadReg function
  * @{
  */
#define LL_SPI_SR_RXP                              (SPI_SR_RXP)
#define LL_SPI_SR_TXP                              (SPI_SR_TXP)
#define LL_SPI_SR_DXP                              (SPI_SR_DXP)
#define LL_SPI_SR_EOT                              (SPI_SR_EOT)
#define LL_SPI_SR_TXTF                             (SPI_SR_TXTF)
#define LL_SPI_SR_UDR                              (SPI_SR_UDR)
#define LL_SPI_SR_CRCE                             (SPI_SR_CRCE)
#define LL_SPI_SR_MODF                             (SPI_SR_MODF)
#define LL_SPI_SR_OVR                              (SPI_SR_OVR)
#define LL_SPI_SR_TIFRE                            (SPI_SR_TIFRE)
#define LL_SPI_SR_SUSP                             (SPI_SR_SUSP)
#define LL_SPI_SR_TXC                              (SPI_SR_TXC)
#define LL_SPI_SR_RXWNE                            (SPI_SR_RXWNE)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_SPI_ReadReg and  LL_SPI_WriteReg functions
  * @{
  */
#define LL_SPI_IER_RXPIE                           (SPI_IER_RXPIE)
#define LL_SPI_IER_TXPIE                           (SPI_IER_TXPIE)
#define LL_SPI_IER_DXPIE                           (SPI_IER_DXPIE)
#define LL_SPI_IER_EOTIE                           (SPI_IER_EOTIE)
#define LL_SPI_IER_TXTFIE                          (SPI_IER_TXTFIE)
#define LL_SPI_IER_UDRIE                           (SPI_IER_UDRIE)
#define LL_SPI_IER_OVRIE                           (SPI_IER_OVRIE)
#define LL_SPI_IER_CRCEIE                          (SPI_IER_CRCEIE)
#define LL_SPI_IER_TIFREIE                         (SPI_IER_TIFREIE)
#define LL_SPI_IER_MODFIE                          (SPI_IER_MODFIE)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_MODE Mode
  * @{
  */
#define LL_SPI_MODE_MASTER                         (SPI_CFG2_MASTER)
#define LL_SPI_MODE_SLAVE                          (0x00000000UL)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_SS_LEVEL SS Level
  * @{
  */
#define LL_SPI_SS_LEVEL_HIGH                       (SPI_CR1_SSI)
#define LL_SPI_SS_LEVEL_LOW                        (0x00000000UL)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_SS_IDLENESS SS Idleness
  * @{
  */
#define LL_SPI_SS_IDLENESS_00CYCLE                 (0x00000000UL)
#define LL_SPI_SS_IDLENESS_01CYCLE                 (SPI_CFG2_MSSI_0)
#define LL_SPI_SS_IDLENESS_02CYCLE                 (SPI_CFG2_MSSI_1)
#define LL_SPI_SS_IDLENESS_03CYCLE                 (SPI_CFG2_MSSI_0 | SPI_CFG2_MSSI_1)
#define LL_SPI_SS_IDLENESS_04CYCLE                 (SPI_CFG2_MSSI_2)
#define LL_SPI_SS_IDLENESS_05CYCLE                 (SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_0)
#define LL_SPI_SS_IDLENESS_06CYCLE                 (SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1)
#define LL_SPI_SS_IDLENESS_07CYCLE                 (SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1 | SPI_CFG2_MSSI_0)
#define LL_SPI_SS_IDLENESS_08CYCLE                 (SPI_CFG2_MSSI_3)
#define LL_SPI_SS_IDLENESS_09CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_0)
#define LL_SPI_SS_IDLENESS_10CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_1)
#define LL_SPI_SS_IDLENESS_11CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_1 | SPI_CFG2_MSSI_0)
#define LL_SPI_SS_IDLENESS_12CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_2)
#define LL_SPI_SS_IDLENESS_13CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_0)
#define LL_SPI_SS_IDLENESS_14CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1)
#define LL_SPI_SS_IDLENESS_15CYCLE                 (SPI_CFG2_MSSI_3\
                                                    | SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1 | SPI_CFG2_MSSI_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_ID_IDLENESS Master Inter-Data Idleness
  * @{
  */
#define LL_SPI_ID_IDLENESS_00CYCLE                 (0x00000000UL)
#define LL_SPI_ID_IDLENESS_01CYCLE                 (SPI_CFG2_MIDI_0)
#define LL_SPI_ID_IDLENESS_02CYCLE                 (SPI_CFG2_MIDI_1)
#define LL_SPI_ID_IDLENESS_03CYCLE                 (SPI_CFG2_MIDI_0 | SPI_CFG2_MIDI_1)
#define LL_SPI_ID_IDLENESS_04CYCLE                 (SPI_CFG2_MIDI_2)
#define LL_SPI_ID_IDLENESS_05CYCLE                 (SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_0)
#define LL_SPI_ID_IDLENESS_06CYCLE                 (SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1)
#define LL_SPI_ID_IDLENESS_07CYCLE                 (SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1 | SPI_CFG2_MIDI_0)
#define LL_SPI_ID_IDLENESS_08CYCLE                 (SPI_CFG2_MIDI_3)
#define LL_SPI_ID_IDLENESS_09CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_0)
#define LL_SPI_ID_IDLENESS_10CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_1)
#define LL_SPI_ID_IDLENESS_11CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_1 | SPI_CFG2_MIDI_0)
#define LL_SPI_ID_IDLENESS_12CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_2)
#define LL_SPI_ID_IDLENESS_13CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_0)
#define LL_SPI_ID_IDLENESS_14CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1)
#define LL_SPI_ID_IDLENESS_15CYCLE                 (SPI_CFG2_MIDI_3\
                                                    | SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1 | SPI_CFG2_MIDI_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_TXCRCINIT_ALL TXCRC Init All
  * @{
  */
#define LL_SPI_TXCRCINIT_ALL_ZERO_PATTERN          (0x00000000UL)
#define LL_SPI_TXCRCINIT_ALL_ONES_PATTERN          (SPI_CR1_TCRCINI)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_RXCRCINIT_ALL RXCRC Init All
  * @{
  */
#define LL_SPI_RXCRCINIT_ALL_ZERO_PATTERN          (0x00000000UL)
#define LL_SPI_RXCRCINIT_ALL_ONES_PATTERN          (SPI_CR1_RCRCINI)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_UDR_CONFIG_REGISTER UDR Config Register
  * @{
  */
#define LL_SPI_UDR_CONFIG_REGISTER_PATTERN         (0x00000000UL)
#define LL_SPI_UNDERRUN_BEHAV_LAST_RECEIVED        (SPI_CFG1_UDRCFG)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_PROTOCOL Protocol
  * @{
  */
#define LL_SPI_PROTOCOL_MOTOROLA                   (0x00000000UL)
#define LL_SPI_PROTOCOL_TI                         (SPI_CFG2_SP_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_PHASE Phase
  * @{
  */
#define LL_SPI_PHASE_1EDGE                         (0x00000000UL)
#define LL_SPI_PHASE_2EDGE                         (SPI_CFG2_CPHA)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_POLARITY Polarity
  * @{
  */
#define LL_SPI_POLARITY_LOW                        (0x00000000UL)
#define LL_SPI_POLARITY_HIGH                       (SPI_CFG2_CPOL)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_NSS_POLARITY NSS Polarity
  * @{
  */
#define LL_SPI_NSS_POLARITY_LOW                    (0x00000000UL)
#define LL_SPI_NSS_POLARITY_HIGH                   (SPI_CFG2_SSIOP)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_BAUDRATEPRESCALER Baud Rate Prescaler
  * @{
  */
#define LL_SPI_BAUDRATEPRESCALER_BYPASS            (SPI_CFG1_BPASS)
#define LL_SPI_BAUDRATEPRESCALER_DIV2              (0x00000000UL)
#define LL_SPI_BAUDRATEPRESCALER_DIV4              (SPI_CFG1_MBR_0)
#define LL_SPI_BAUDRATEPRESCALER_DIV8              (SPI_CFG1_MBR_1)
#define LL_SPI_BAUDRATEPRESCALER_DIV16             (SPI_CFG1_MBR_1 | SPI_CFG1_MBR_0)
#define LL_SPI_BAUDRATEPRESCALER_DIV32             (SPI_CFG1_MBR_2)
#define LL_SPI_BAUDRATEPRESCALER_DIV64             (SPI_CFG1_MBR_2 | SPI_CFG1_MBR_0)
#define LL_SPI_BAUDRATEPRESCALER_DIV128            (SPI_CFG1_MBR_2 | SPI_CFG1_MBR_1)
#define LL_SPI_BAUDRATEPRESCALER_DIV256            (SPI_CFG1_MBR_2 | SPI_CFG1_MBR_1 | SPI_CFG1_MBR_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_BIT_ORDER Bit Order
  * @{
  */
#define LL_SPI_LSB_FIRST                           (SPI_CFG2_LSBFRST)
#define LL_SPI_MSB_FIRST                           (0x00000000UL)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_TRANSFER_MODE Transfer Mode
  * @{
  */
#define LL_SPI_FULL_DUPLEX                         (0x00000000UL)
#define LL_SPI_SIMPLEX_TX                          (SPI_CFG2_COMM_0)
#define LL_SPI_SIMPLEX_RX                          (SPI_CFG2_COMM_1)
#define LL_SPI_HALF_DUPLEX_RX                      (SPI_CFG2_COMM_0|SPI_CFG2_COMM_1)
#define LL_SPI_HALF_DUPLEX_TX                      (SPI_CFG2_COMM_0|SPI_CFG2_COMM_1|SPI_CR1_HDDIR)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_DATAWIDTH Data Width
  * @{
  */
#define LL_SPI_DATAWIDTH_4BIT                      (SPI_CFG1_DSIZE_0 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_5BIT                      (SPI_CFG1_DSIZE_2)
#define LL_SPI_DATAWIDTH_6BIT                      (SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_7BIT                      (SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_8BIT                      (SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_9BIT                      (SPI_CFG1_DSIZE_3)
#define LL_SPI_DATAWIDTH_10BIT                     (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_11BIT                     (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_12BIT                     (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_13BIT                     (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2)
#define LL_SPI_DATAWIDTH_14BIT                     (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_15BIT                     (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_16BIT                     (SPI_CFG1_DSIZE_3\
                                                    | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_17BIT                     (SPI_CFG1_DSIZE_4)
#define LL_SPI_DATAWIDTH_18BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_19BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_20BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_0 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_21BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_2)
#define LL_SPI_DATAWIDTH_22BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_23BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_24BIT                     (SPI_CFG1_DSIZE_4\
                                                    | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_25BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3)
#define LL_SPI_DATAWIDTH_26BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_27BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_28BIT                     (SPI_CFG1_DSIZE_4\
                                                    | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_29BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2)
#define LL_SPI_DATAWIDTH_30BIT                     (SPI_CFG1_DSIZE_4\
                                                    | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATAWIDTH_31BIT                     (SPI_CFG1_DSIZE_4\
                                                    | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATAWIDTH_32BIT                     (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3\
                                                    | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_FIFO_TH FIFO Threshold
  * @{
  */
#define LL_SPI_FIFO_TH_01DATA                      (0x00000000UL)
#define LL_SPI_FIFO_TH_02DATA                      (SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_TH_03DATA                      (SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_TH_04DATA                      (SPI_CFG1_FTHLV_0 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_TH_05DATA                      (SPI_CFG1_FTHLV_2)
#define LL_SPI_FIFO_TH_06DATA                      (SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_TH_07DATA                      (SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_TH_08DATA                      (SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_TH_09DATA                      (SPI_CFG1_FTHLV_3)
#define LL_SPI_FIFO_TH_10DATA                      (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_TH_11DATA                      (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_TH_12DATA                      (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_1 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_TH_13DATA                      (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_2)
#define LL_SPI_FIFO_TH_14DATA                      (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_TH_15DATA                      (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_TH_16DATA                      (SPI_CFG1_FTHLV_3\
                                                    | SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1 | SPI_CFG1_FTHLV_0)
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)

/** @defgroup SPI_LL_EC_CRC_CALCULATION CRC Calculation
  * @{
  */
#define LL_SPI_CRCCALCULATION_DISABLE              (0x00000000UL)            /*!< CRC calculation disabled */
#define LL_SPI_CRCCALCULATION_ENABLE               (SPI_CFG1_CRCEN)          /*!< CRC calculation enabled  */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup SPI_LL_EC_CRC CRC
  * @{
  */
#define LL_SPI_CRC_4BIT                            (SPI_CFG1_CRCSIZE_0 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_5BIT                            (SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_6BIT                            (SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_7BIT                            (SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_8BIT                            (SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_9BIT                            (SPI_CFG1_CRCSIZE_3)
#define LL_SPI_CRC_10BIT                           (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_11BIT                           (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_12BIT                           (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_13BIT                           (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_14BIT                           (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_15BIT                           (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_16BIT                           (SPI_CFG1_CRCSIZE_3\
                                                    | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_17BIT                           (SPI_CFG1_CRCSIZE_4)
#define LL_SPI_CRC_18BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_19BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_20BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_0 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_21BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_22BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_23BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_24BIT                           (SPI_CFG1_CRCSIZE_4\
                                                    | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_25BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3)
#define LL_SPI_CRC_26BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_27BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_28BIT                           (SPI_CFG1_CRCSIZE_4\
                                                    | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_29BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_30BIT                           (SPI_CFG1_CRCSIZE_4\
                                                    | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_31BIT                           (SPI_CFG1_CRCSIZE_4\
                                                    | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_32BIT                           (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3\
                                                    | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_NSS_MODE NSS Mode
  * @{
  */
#define LL_SPI_NSS_SOFT                            (SPI_CFG2_SSM)
#define LL_SPI_NSS_HARD_INPUT                      (0x00000000UL)
#define LL_SPI_NSS_HARD_OUTPUT                     (SPI_CFG2_SSOE)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_RX_FIFO RxFIFO Packing LeVel
  * @{
  */
#define LL_SPI_RX_FIFO_0PACKET               (0x00000000UL)    /* 0 or multiple of 4 packet available is the RxFIFO */
#define LL_SPI_RX_FIFO_1PACKET               (SPI_SR_RXPLVL_0)
#define LL_SPI_RX_FIFO_2PACKET               (SPI_SR_RXPLVL_1)
#define LL_SPI_RX_FIFO_3PACKET               (SPI_SR_RXPLVL_1 | SPI_SR_RXPLVL_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_AUTOCR_TRIGSEL  Autonomous Trigger selection
  * @brief    SPI Autonomous Trigger selection
  * @{
  */
#define LL_SPI_TRIG_GRP1                   (0x10000000U)                    /*!< Trigger Group for SPI1 and SPI2 */
#define LL_SPI_TRIG_GRP2                   (0x20000000U)                    /*!< Trigger Group for SPI3 */

/*!< HW Trigger signal is GPDMA_CH0_TRG     */
#define LL_SPI_GRP1_GPDMA_CH0_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP1 | (0x00000000U))
/*!< HW Trigger signal is GPDMA_CH1_TRG     */
#define LL_SPI_GRP1_GPDMA_CH1_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP1 | (0x1U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is GPDMA_CH2_TRG     */
#define LL_SPI_GRP1_GPDMA_CH2_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP1 | (0x2U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is GPDMA_CH3_TRG     */
#define LL_SPI_GRP1_GPDMA_CH3_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP1 | (0x3U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI4_TRG         */
#define LL_SPI_GRP1_EXTI4_TRG              (uint32_t)(LL_SPI_TRIG_GRP1 | (0x4U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI9_TRG         */
#define LL_SPI_GRP1_EXTI9_TRG              (uint32_t)(LL_SPI_TRIG_GRP1 | (0x5U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM1_CH1_TRG    */
#define LL_SPI_GRP1_LPTIM1_CH1_TRG         (uint32_t)(LL_SPI_TRIG_GRP1 | (0x6U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM2_CH1_TRG    */
#define LL_SPI_GRP1_LPTIM2_CH1_TRG         (uint32_t)(LL_SPI_TRIG_GRP1 | (0x7U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP1_TRG         */
#define LL_SPI_GRP1_COMP1_TRG              (uint32_t)(LL_SPI_TRIG_GRP1 | (0x8U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP2_TRG         */
#define LL_SPI_GRP1_COMP2_TRG              (uint32_t)(LL_SPI_TRIG_GRP1 | (0x9U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_ALRA_TRG      */
#define LL_SPI_GRP1_RTC_ALRA_TRG           (uint32_t)(LL_SPI_TRIG_GRP1 | (0xAU << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_WUT_TRG       */
#define LL_SPI_GRP1_RTC_WUT_TRG            (uint32_t)(LL_SPI_TRIG_GRP1 | (0xBU << SPI_AUTOCR_TRIGSEL_Pos))

/*!< HW Trigger signal is LPDMA_CH0_TRG     */
#define LL_SPI_GRP2_LPDMA_CH0_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP2 | (0x00000000U))
/*!< HW Trigger signal is LPDMA_CH1_TRG     */
#define LL_SPI_GRP2_LPDMA_CH1_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP2 | (0x1U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPDMA_CH2_TRG     */
#define LL_SPI_GRP2_LPDMA_CH2_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP2 | (0x2U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPDMA_CH3_TRG     */
#define LL_SPI_GRP2_LPDMA_CH3_TCF_TRG      (uint32_t)(LL_SPI_TRIG_GRP2 | (0x3U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI4_TRG         */
#define LL_SPI_GRP2_EXTI4_TRG              (uint32_t)(LL_SPI_TRIG_GRP2 | (0x4U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI8_TRG         */
#define LL_SPI_GRP2_EXTI8_TRG              (uint32_t)(LL_SPI_TRIG_GRP2 | (0x5U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM1_CH1_TRG    */
#define LL_SPI_GRP2_LPTIM1_CH1_TRG         (uint32_t)(LL_SPI_TRIG_GRP2 | (0x6U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM3_CH1_TRG    */
#define LL_SPI_GRP2_LPTIM3_CH1_TRG         (uint32_t)(LL_SPI_TRIG_GRP2 | (0x7U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP1_TRG         */
#define LL_SPI_GRP2_COMP1_TRG              (uint32_t)(LL_SPI_TRIG_GRP2 | (0x8U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP2_TRG         */
#define LL_SPI_GRP2_COMP2_TRG              (uint32_t)(LL_SPI_TRIG_GRP2 | (0x9U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_ALRA_TRG      */
#define LL_SPI_GRP2_RTC_ALRA_TRG           (uint32_t)(LL_SPI_TRIG_GRP2 | (0xAU << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_WUT_TRG       */
#define LL_SPI_GRP2_RTC_WUT_TRG            (uint32_t)(LL_SPI_TRIG_GRP2 | (0xBU << SPI_AUTOCR_TRIGSEL_Pos))

/**
  * @}
  */

/** @defgroup SPI_LL_EC_AUTOCR_TRIGPOL  Autonomous Trigger Polarity
  * @brief    SPI Autonomous Trigger Polarity
  * @{
  */
#define LL_SPI_TRIG_POLARITY_RISING         0x00000000U           /*!< SPI triggered on rising edge  */
#define LL_SPI_TRIG_POLARITY_FALLING        SPI_AUTOCR_TRIGPOL    /*!< SPI triggered on falling edge */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Macros SPI Exported Macros
  * @{
  */

/** @defgroup SPI_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SPI register
  * @param  __INSTANCE__ SPI Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_SPI_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in SPI register
  * @param  __INSTANCE__ SPI Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_SPI_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup SPI_LL_Exported_Functions SPI Exported Functions
  * @{
  */

/** @defgroup SPI_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable SPI peripheral
  * @rmtoll CR1          SPE           LL_SPI_Enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_Enable(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Disable SPI peripheral
  * @note   When disabling the SPI, follow the procedure described in the Reference Manual.
  * @rmtoll CR1          SPE           LL_SPI_Disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_Disable(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Check if SPI peripheral is enabled
  * @rmtoll CR1          SPE           LL_SPI_IsEnabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabled(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_SPE) == (SPI_CR1_SPE)) ? 1UL : 0UL);
}

/**
  * @brief  Swap the MOSI and MISO pin
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG2         IOSWP         LL_SPI_EnableIOSwap
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIOSwap(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CFG2, SPI_CFG2_IOSWP);
}

/**
  * @brief  Restore default function for MOSI and MISO pin
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG2         IOSWP         LL_SPI_DisableIOSwap
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIOSwap(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CFG2, SPI_CFG2_IOSWP);
}

/**
  * @brief  Check if MOSI and MISO pin are swapped
  * @rmtoll CFG2         IOSWP         LL_SPI_IsEnabledIOSwap
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIOSwap(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CFG2, SPI_CFG2_IOSWP) == (SPI_CFG2_IOSWP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO control
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG2         AFCNTR        LL_SPI_EnableGPIOControl
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableGPIOControl(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CFG2, SPI_CFG2_AFCNTR);
}

/**
  * @brief  Disable GPIO control
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG2         AFCNTR        LL_SPI_DisableGPIOControl
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableGPIOControl(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CFG2, SPI_CFG2_AFCNTR);
}

/**
  * @brief  Check if GPIO control is active
  * @rmtoll CFG2         AFCNTR        LL_SPI_IsEnabledGPIOControl
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledGPIOControl(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CFG2, SPI_CFG2_AFCNTR) == (SPI_CFG2_AFCNTR)) ? 1UL : 0UL);
}

/**
  * @brief  Set SPI Mode to Master or Slave
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG2         MASTER        LL_SPI_SetMode
  * @param  SPIx SPI Instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_SPI_MODE_MASTER
  *         @arg @ref LL_SPI_MODE_SLAVE
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetMode(SPI_TypeDef *SPIx, uint32_t Mode)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_MASTER, Mode);
}

/**
  * @brief  Get SPI Mode (Master or Slave)
  * @rmtoll CFG2         MASTER        LL_SPI_GetMode
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_MODE_MASTER
  *         @arg @ref LL_SPI_MODE_SLAVE
  */
__STATIC_INLINE uint32_t LL_SPI_GetMode(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_MASTER));
}

/**
  * @brief  Configure the Idleness applied by master between active edge of SS and first send data
  * @rmtoll CFG2         MSSI          LL_SPI_SetMasterSSIdleness
  * @param  SPIx SPI Instance
  * @param  MasterSSIdleness This parameter can be one of the following values:
  *         @arg @ref LL_SPI_SS_IDLENESS_00CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_01CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_02CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_03CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_04CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_05CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_06CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_07CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_08CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_09CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_10CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_11CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_12CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_13CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_14CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_15CYCLE
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetMasterSSIdleness(SPI_TypeDef *SPIx, uint32_t MasterSSIdleness)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_MSSI, MasterSSIdleness);
}

/**
  * @brief  Get the configured Idleness applied by master
  * @rmtoll CFG2         MSSI          LL_SPI_GetMasterSSIdleness
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_SS_IDLENESS_00CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_01CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_02CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_03CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_04CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_05CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_06CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_07CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_08CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_09CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_10CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_11CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_12CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_13CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_14CYCLE
  *         @arg @ref LL_SPI_SS_IDLENESS_15CYCLE
  */
__STATIC_INLINE uint32_t LL_SPI_GetMasterSSIdleness(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_MSSI));
}

/**
  * @brief  Configure the idleness applied by master between data frame
  * @rmtoll CFG2         MIDI          LL_SPI_SetInterDataIdleness
  * @param  SPIx SPI Instance
  * @param  MasterInterDataIdleness This parameter can be one of the following values:
  *         @arg @ref LL_SPI_ID_IDLENESS_00CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_01CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_02CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_03CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_04CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_05CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_06CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_07CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_08CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_09CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_10CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_11CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_12CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_13CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_14CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_15CYCLE
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetInterDataIdleness(SPI_TypeDef *SPIx, uint32_t MasterInterDataIdleness)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_MIDI, MasterInterDataIdleness);
}

/**
  * @brief  Get the configured inter data idleness
  * @rmtoll CFG2         MIDI          LL_SPI_SetInterDataIdleness
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_ID_IDLENESS_00CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_01CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_02CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_03CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_04CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_05CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_06CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_07CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_08CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_09CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_10CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_11CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_12CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_13CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_14CYCLE
  *         @arg @ref LL_SPI_ID_IDLENESS_15CYCLE
  */
__STATIC_INLINE uint32_t LL_SPI_GetInterDataIdleness(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_MIDI));
}

/**
  * @brief  Set transfer size
  * @note    Count is the number of frame to be transferred
  * @rmtoll CR2          TSIZE         LL_SPI_SetTransferSize
  * @param  SPIx SPI Instance
  * @param  Count 0..0xFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetTransferSize(SPI_TypeDef *SPIx, uint32_t Count)
{
  MODIFY_REG(SPIx->CR2, SPI_CR2_TSIZE, Count);
}

/**
  * @brief  Get transfer size
  * @note    Count is the number of frame to be transferred
  * @rmtoll CR2          TSIZE         LL_SPI_GetTransferSize
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferSize(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_TSIZE));
}

/**
  * @brief  Lock the AF configuration of associated IOs
  * @note   Once this bit is set, the AF configuration remains locked until a hardware reset occurs.
  *         the reset of the IOLock bit is done by hardware. for that, LL_SPI_DisableIOLock can not exist.
  * @rmtoll CR1          IOLOCK        LL_SPI_EnableIOLock
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIOLock(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_IOLOCK);
}

/**
  * @brief  Check if the AF configuration is locked.
  * @rmtoll CR1          IOLOCK        LL_SPI_IsEnabledIOLock
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIOLock(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_IOLOCK) == (SPI_CR1_IOLOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Set Tx CRC Initialization Pattern
  * @rmtoll CR1          TCRCINI         LL_SPI_SetTxCRCInitPattern
  * @param  SPIx SPI Instance
  * @param  TXCRCInitAll This parameter can be one of the following values:
  *         @arg @ref LL_SPI_TXCRCINIT_ALL_ZERO_PATTERN
  *         @arg @ref LL_SPI_TXCRCINIT_ALL_ONES_PATTERN
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetTxCRCInitPattern(SPI_TypeDef *SPIx, uint32_t TXCRCInitAll)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_RCRCINI, TXCRCInitAll);
}

/**
  * @brief  Get Tx CRC Initialization Pattern
  * @rmtoll CR1          TCRCINI         LL_SPI_GetTxCRCInitPattern
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_TXCRCINIT_ALL_ZERO_PATTERN
  *         @arg @ref LL_SPI_TXCRCINIT_ALL_ONES_PATTERN
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxCRCInitPattern(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_TCRCINI));
}

/**
  * @brief  Set Rx CRC Initialization Pattern
  * @rmtoll CR1          RCRCINI         LL_SPI_SetRxCRCInitPattern
  * @param  SPIx SPI Instance
  * @param  RXCRCInitAll This parameter can be one of the following values:
  *         @arg @ref LL_SPI_RXCRCINIT_ALL_ZERO_PATTERN
  *         @arg @ref LL_SPI_RXCRCINIT_ALL_ONES_PATTERN
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetRxCRCInitPattern(SPI_TypeDef *SPIx, uint32_t RXCRCInitAll)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_RCRCINI, RXCRCInitAll);
}

/**
  * @brief  Get Rx CRC Initialization Pattern
  * @rmtoll CR1          RCRCINI         LL_SPI_GetRxCRCInitPattern
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_RXCRCINIT_ALL_ZERO_PATTERN
  *         @arg @ref LL_SPI_RXCRCINIT_ALL_ONES_PATTERN
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxCRCInitPattern(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_RCRCINI));
}

/**
  * @brief  Set internal SS input level ignoring what comes from PIN.
  * @note   This configuration has effect only with config LL_SPI_NSS_SOFT
  * @rmtoll CR1          SSI           LL_SPI_SetInternalSSLevel
  * @param  SPIx SPI Instance
  * @param  SSLevel This parameter can be one of the following values:
  *         @arg @ref LL_SPI_SS_LEVEL_HIGH
  *         @arg @ref LL_SPI_SS_LEVEL_LOW
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetInternalSSLevel(SPI_TypeDef *SPIx, uint32_t SSLevel)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_SSI, SSLevel);
}

/**
  * @brief  Get internal SS input level
  * @rmtoll CR1          SSI           LL_SPI_GetInternalSSLevel
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_SS_LEVEL_HIGH
  *         @arg @ref LL_SPI_SS_LEVEL_LOW
  */
__STATIC_INLINE uint32_t LL_SPI_GetInternalSSLevel(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_SSI));
}

/**
  * @brief  Enable CRC computation on 33/17 bits
  * @rmtoll CR1          CRC33_17      LL_SPI_EnableFullSizeCRC
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableFullSizeCRC(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_CRC33_17);
}

/**
  * @brief  Disable CRC computation on 33/17 bits
  * @rmtoll CR1          CRC33_17      LL_SPI_DisableFullSizeCRC
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableFullSizeCRC(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_CRC33_17);
}

/**
  * @brief  Check if Enable CRC computation on 33/17 bits is enabled
  * @rmtoll CR1          CRC33_17      LL_SPI_IsEnabledFullSizeCRC
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledFullSizeCRC(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_CRC33_17) == (SPI_CR1_CRC33_17)) ? 1UL : 0UL);
}

/**
  * @brief  Suspend an ongoing transfer for Master configuration
  * @rmtoll CR1          CSUSP         LL_SPI_SuspendMasterTransfer
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SuspendMasterTransfer(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_CSUSP);
}

/**
  * @brief  Start effective transfer on wire for Master configuration
  * @rmtoll CR1          CSTART        LL_SPI_StartMasterTransfer
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_StartMasterTransfer(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_CSTART);
}

/**
  * @brief  Check if there is an unfinished master transfer
  * @rmtoll CR1          CSTART        LL_SPI_IsActiveMasterTransfer
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveMasterTransfer(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_CSTART) == (SPI_CR1_CSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Master Rx auto suspend in case of overrun
  * @rmtoll CR1          MASRX         LL_SPI_EnableMasterRxAutoSuspend
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableMasterRxAutoSuspend(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_MASRX);
}

/**
  * @brief  Disable Master Rx auto suspend in case of overrun
  * @rmtoll CR1          MASRX         LL_SPI_DisableMasterRxAutoSuspend
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableMasterRxAutoSuspend(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_MASRX);
}

/**
  * @brief  Check if Master Rx auto suspend is activated
  * @rmtoll CR1          MASRX         LL_SPI_IsEnabledMasterRxAutoSuspend
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledMasterRxAutoSuspend(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_MASRX) == (SPI_CR1_MASRX)) ? 1UL : 0UL);
}

/**
  * @brief  Set Underrun behavior
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG1         UDRCFG        LL_SPI_SetUDRConfiguration
  * @param  SPIx SPI Instance
  * @param  UDRConfig This parameter can be one of the following values:
  *         @arg @ref LL_SPI_UDR_CONFIG_REGISTER_PATTERN
  *         @arg @ref LL_SPI_UNDERRUN_BEHAV_LAST_RECEIVED
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetUDRConfiguration(SPI_TypeDef *SPIx, uint32_t UDRConfig)
{
  MODIFY_REG(SPIx->CFG1, SPI_CFG1_UDRCFG, UDRConfig);
}

/**
  * @brief  Get Underrun behavior
  * @rmtoll CFG1         UDRCFG        LL_SPI_GetUDRConfiguration
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_UDR_CONFIG_REGISTER_PATTERN
  *         @arg @ref LL_SPI_UNDERRUN_BEHAV_LAST_RECEIVED
  */
__STATIC_INLINE uint32_t LL_SPI_GetUDRConfiguration(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG1, SPI_CFG1_UDRCFG));
}


/**
  * @brief  Set Serial protocol used
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG2         SP            LL_SPI_SetStandard
  * @param  SPIx SPI Instance
  * @param  Standard This parameter can be one of the following values:
  *         @arg @ref LL_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref LL_SPI_PROTOCOL_TI
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetStandard(SPI_TypeDef *SPIx, uint32_t Standard)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_SP, Standard);
}

/**
  * @brief  Get Serial protocol used
  * @rmtoll CFG2         SP            LL_SPI_GetStandard
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref LL_SPI_PROTOCOL_TI
  */
__STATIC_INLINE uint32_t LL_SPI_GetStandard(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_SP));
}

/**
  * @brief  Set Clock phase
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CFG2         CPHA          LL_SPI_SetClockPhase
  * @param  SPIx SPI Instance
  * @param  ClockPhase This parameter can be one of the following values:
  *         @arg @ref LL_SPI_PHASE_1EDGE
  *         @arg @ref LL_SPI_PHASE_2EDGE
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t ClockPhase)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_CPHA, ClockPhase);
}

/**
  * @brief  Get Clock phase
  * @rmtoll CFG2         CPHA          LL_SPI_GetClockPhase
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_PHASE_1EDGE
  *         @arg @ref LL_SPI_PHASE_2EDGE
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPhase(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_CPHA));
}

/**
  * @brief  Set Clock polarity
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CFG2         CPOL          LL_SPI_SetClockPolarity
  * @param  SPIx SPI Instance
  * @param  ClockPolarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_POLARITY_LOW
  *         @arg @ref LL_SPI_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t ClockPolarity)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_CPOL, ClockPolarity);
}

/**
  * @brief  Get Clock polarity
  * @rmtoll CFG2         CPOL          LL_SPI_GetClockPolarity
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_POLARITY_LOW
  *         @arg @ref LL_SPI_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPolarity(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_CPOL));
}

/**
  * @brief  Set NSS polarity
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CFG2         SSIOP          LL_SPI_SetNSSPolarity
  * @param  SPIx SPI Instance
  * @param  NSSPolarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_NSS_POLARITY_LOW
  *         @arg @ref LL_SPI_NSS_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetNSSPolarity(SPI_TypeDef *SPIx, uint32_t NSSPolarity)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_SSIOP, NSSPolarity);
}

/**
  * @brief  Get NSS polarity
  * @rmtoll CFG2         SSIOP          LL_SPI_GetNSSPolarity
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_NSS_POLARITY_LOW
  *         @arg @ref LL_SPI_NSS_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_SPI_GetNSSPolarity(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_SSIOP));
}

/**
  * @brief  Set Baudrate Prescaler
  * @note   This configuration can not be changed when SPI is enabled.
  *         SPI BaudRate = fPCLK/Pescaler.
  * @rmtoll CFG1         MBR BPASS    LL_SPI_SetBaudRatePrescaler
  * @param  SPIx SPI Instance
  * @param  Baudrate This parameter can be one of the following values:
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_BYPASS
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV256
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetBaudRatePrescaler(SPI_TypeDef *SPIx, uint32_t Baudrate)
{
  MODIFY_REG(SPIx->CFG1, (SPI_CFG1_MBR | SPI_CFG1_BPASS), Baudrate);
}

/**
  * @brief  Get Baudrate Prescaler
  * @rmtoll CFG1         MBR BPASS    LL_SPI_GetBaudRatePrescaler
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_BYPASS
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV256
  */
__STATIC_INLINE uint32_t LL_SPI_GetBaudRatePrescaler(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG1, (SPI_CFG1_MBR | SPI_CFG1_BPASS)));
}

/**
  * @brief  Set Transfer Bit Order
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CFG2         LSBFRST       LL_SPI_SetTransferBitOrder
  * @param  SPIx SPI Instance
  * @param  BitOrder This parameter can be one of the following values:
  *         @arg @ref LL_SPI_LSB_FIRST
  *         @arg @ref LL_SPI_MSB_FIRST
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t BitOrder)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_LSBFRST, BitOrder);
}

/**
  * @brief  Get Transfer Bit Order
  * @rmtoll CFG2         LSBFRST       LL_SPI_GetTransferBitOrder
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_LSB_FIRST
  *         @arg @ref LL_SPI_MSB_FIRST
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferBitOrder(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_LSBFRST));
}

/**
  * @brief  Set Transfer Mode
  * @note   This configuration can not be changed when SPI is enabled except for half duplex direction
  *         using LL_SPI_SetHalfDuplexDirection.
  * @rmtoll CR1          HDDIR         LL_SPI_SetTransferDirection\n
  *         CFG2         COMM          LL_SPI_SetTransferDirection
  * @param  SPIx SPI Instance
  * @param  TransferDirection This parameter can be one of the following values:
  *         @arg @ref LL_SPI_FULL_DUPLEX
  *         @arg @ref LL_SPI_SIMPLEX_TX
  *         @arg @ref LL_SPI_SIMPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_TX
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t TransferDirection)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_HDDIR,  TransferDirection & SPI_CR1_HDDIR);
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_COMM, TransferDirection & SPI_CFG2_COMM);
}

/**
  * @brief  Get Transfer Mode
  * @rmtoll CR1          HDDIR         LL_SPI_GetTransferDirection\n
  *         CFG2         COMM          LL_SPI_GetTransferDirection
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_FULL_DUPLEX
  *         @arg @ref LL_SPI_SIMPLEX_TX
  *         @arg @ref LL_SPI_SIMPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_TX
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferDirection(SPI_TypeDef *SPIx)
{
  uint32_t Hddir = READ_BIT(SPIx->CR1, SPI_CR1_HDDIR);
  uint32_t Comm = READ_BIT(SPIx->CFG2, SPI_CFG2_COMM);
  return (Hddir | Comm);
}

/**
  * @brief  Set direction for Half-Duplex Mode
  * @note   In master mode the MOSI pin is used and in slave mode the MISO pin is used for Half-Duplex.
  * @rmtoll CR1          HDDIR         LL_SPI_SetHalfDuplexDirection
  * @param  SPIx SPI Instance
  * @param  HalfDuplexDirection This parameter can be one of the following values:
  *         @arg @ref LL_SPI_HALF_DUPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_TX
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetHalfDuplexDirection(SPI_TypeDef *SPIx, uint32_t HalfDuplexDirection)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_HDDIR, HalfDuplexDirection & SPI_CR1_HDDIR);
}

/**
  * @brief  Get direction for Half-Duplex Mode
  * @note   In master mode the MOSI pin is used and in slave mode the MISO pin is used for Half-Duplex.
  * @rmtoll CR1          HDDIR         LL_SPI_GetHalfDuplexDirection
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_HALF_DUPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_TX
  */
__STATIC_INLINE uint32_t LL_SPI_GetHalfDuplexDirection(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_HDDIR) | SPI_CFG2_COMM);
}

/**
  * @brief  Set Frame Data Size
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG1         DSIZE         LL_SPI_SetDataWidth
  * @param  SPIx SPI Instance
  * @param  DataWidth This parameter can be one of the following values:
  *         @arg @ref LL_SPI_DATAWIDTH_4BIT
  *         @arg @ref LL_SPI_DATAWIDTH_5BIT
  *         @arg @ref LL_SPI_DATAWIDTH_6BIT
  *         @arg @ref LL_SPI_DATAWIDTH_7BIT
  *         @arg @ref LL_SPI_DATAWIDTH_8BIT
  *         @arg @ref LL_SPI_DATAWIDTH_9BIT
  *         @arg @ref LL_SPI_DATAWIDTH_10BIT
  *         @arg @ref LL_SPI_DATAWIDTH_11BIT
  *         @arg @ref LL_SPI_DATAWIDTH_12BIT
  *         @arg @ref LL_SPI_DATAWIDTH_13BIT
  *         @arg @ref LL_SPI_DATAWIDTH_14BIT
  *         @arg @ref LL_SPI_DATAWIDTH_15BIT
  *         @arg @ref LL_SPI_DATAWIDTH_16BIT
  *         @arg @ref LL_SPI_DATAWIDTH_17BIT
  *         @arg @ref LL_SPI_DATAWIDTH_18BIT
  *         @arg @ref LL_SPI_DATAWIDTH_19BIT
  *         @arg @ref LL_SPI_DATAWIDTH_20BIT
  *         @arg @ref LL_SPI_DATAWIDTH_21BIT
  *         @arg @ref LL_SPI_DATAWIDTH_22BIT
  *         @arg @ref LL_SPI_DATAWIDTH_23BIT
  *         @arg @ref LL_SPI_DATAWIDTH_24BIT
  *         @arg @ref LL_SPI_DATAWIDTH_25BIT
  *         @arg @ref LL_SPI_DATAWIDTH_26BIT
  *         @arg @ref LL_SPI_DATAWIDTH_27BIT
  *         @arg @ref LL_SPI_DATAWIDTH_28BIT
  *         @arg @ref LL_SPI_DATAWIDTH_29BIT
  *         @arg @ref LL_SPI_DATAWIDTH_30BIT
  *         @arg @ref LL_SPI_DATAWIDTH_31BIT
  *         @arg @ref LL_SPI_DATAWIDTH_32BIT
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t DataWidth)
{
  MODIFY_REG(SPIx->CFG1, SPI_CFG1_DSIZE, DataWidth);
}

/**
  * @brief  Get Frame Data Size
  * @rmtoll CFG1         DSIZE         LL_SPI_GetDataWidth
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_DATAWIDTH_4BIT
  *         @arg @ref LL_SPI_DATAWIDTH_5BIT
  *         @arg @ref LL_SPI_DATAWIDTH_6BIT
  *         @arg @ref LL_SPI_DATAWIDTH_7BIT
  *         @arg @ref LL_SPI_DATAWIDTH_8BIT
  *         @arg @ref LL_SPI_DATAWIDTH_9BIT
  *         @arg @ref LL_SPI_DATAWIDTH_10BIT
  *         @arg @ref LL_SPI_DATAWIDTH_11BIT
  *         @arg @ref LL_SPI_DATAWIDTH_12BIT
  *         @arg @ref LL_SPI_DATAWIDTH_13BIT
  *         @arg @ref LL_SPI_DATAWIDTH_14BIT
  *         @arg @ref LL_SPI_DATAWIDTH_15BIT
  *         @arg @ref LL_SPI_DATAWIDTH_16BIT
  *         @arg @ref LL_SPI_DATAWIDTH_17BIT
  *         @arg @ref LL_SPI_DATAWIDTH_18BIT
  *         @arg @ref LL_SPI_DATAWIDTH_19BIT
  *         @arg @ref LL_SPI_DATAWIDTH_20BIT
  *         @arg @ref LL_SPI_DATAWIDTH_21BIT
  *         @arg @ref LL_SPI_DATAWIDTH_22BIT
  *         @arg @ref LL_SPI_DATAWIDTH_23BIT
  *         @arg @ref LL_SPI_DATAWIDTH_24BIT
  *         @arg @ref LL_SPI_DATAWIDTH_25BIT
  *         @arg @ref LL_SPI_DATAWIDTH_26BIT
  *         @arg @ref LL_SPI_DATAWIDTH_27BIT
  *         @arg @ref LL_SPI_DATAWIDTH_28BIT
  *         @arg @ref LL_SPI_DATAWIDTH_29BIT
  *         @arg @ref LL_SPI_DATAWIDTH_30BIT
  *         @arg @ref LL_SPI_DATAWIDTH_31BIT
  *         @arg @ref LL_SPI_DATAWIDTH_32BIT
  */
__STATIC_INLINE uint32_t LL_SPI_GetDataWidth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG1, SPI_CFG1_DSIZE));
}

/**
  * @brief  Set threshold of FIFO that triggers a transfer event
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG1         FTHLV         LL_SPI_SetFIFOThreshold
  * @param  SPIx SPI Instance
  * @param  Threshold This parameter can be one of the following values:
  *         @arg @ref LL_SPI_FIFO_TH_01DATA
  *         @arg @ref LL_SPI_FIFO_TH_02DATA
  *         @arg @ref LL_SPI_FIFO_TH_03DATA
  *         @arg @ref LL_SPI_FIFO_TH_04DATA
  *         @arg @ref LL_SPI_FIFO_TH_05DATA
  *         @arg @ref LL_SPI_FIFO_TH_06DATA
  *         @arg @ref LL_SPI_FIFO_TH_07DATA
  *         @arg @ref LL_SPI_FIFO_TH_08DATA
  *         @arg @ref LL_SPI_FIFO_TH_09DATA
  *         @arg @ref LL_SPI_FIFO_TH_10DATA
  *         @arg @ref LL_SPI_FIFO_TH_11DATA
  *         @arg @ref LL_SPI_FIFO_TH_12DATA
  *         @arg @ref LL_SPI_FIFO_TH_13DATA
  *         @arg @ref LL_SPI_FIFO_TH_14DATA
  *         @arg @ref LL_SPI_FIFO_TH_15DATA
  *         @arg @ref LL_SPI_FIFO_TH_16DATA
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetFIFOThreshold(SPI_TypeDef *SPIx, uint32_t Threshold)
{
  MODIFY_REG(SPIx->CFG1, SPI_CFG1_FTHLV, Threshold);
}

/**
  * @brief  Get threshold of FIFO that triggers a transfer event
  * @rmtoll CFG1         FTHLV         LL_SPI_GetFIFOThreshold
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_FIFO_TH_01DATA
  *         @arg @ref LL_SPI_FIFO_TH_02DATA
  *         @arg @ref LL_SPI_FIFO_TH_03DATA
  *         @arg @ref LL_SPI_FIFO_TH_04DATA
  *         @arg @ref LL_SPI_FIFO_TH_05DATA
  *         @arg @ref LL_SPI_FIFO_TH_06DATA
  *         @arg @ref LL_SPI_FIFO_TH_07DATA
  *         @arg @ref LL_SPI_FIFO_TH_08DATA
  *         @arg @ref LL_SPI_FIFO_TH_09DATA
  *         @arg @ref LL_SPI_FIFO_TH_10DATA
  *         @arg @ref LL_SPI_FIFO_TH_11DATA
  *         @arg @ref LL_SPI_FIFO_TH_12DATA
  *         @arg @ref LL_SPI_FIFO_TH_13DATA
  *         @arg @ref LL_SPI_FIFO_TH_14DATA
  *         @arg @ref LL_SPI_FIFO_TH_15DATA
  *         @arg @ref LL_SPI_FIFO_TH_16DATA
  */
__STATIC_INLINE uint32_t LL_SPI_GetFIFOThreshold(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG1, SPI_CFG1_FTHLV));
}

/**
  * @brief  Enable CRC
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG1         CRCEN         LL_SPI_EnableCRC
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableCRC(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CFG1, SPI_CFG1_CRCEN);
}

/**
  * @brief  Disable CRC
  * @rmtoll CFG1         CRCEN         LL_SPI_DisableCRC
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableCRC(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CFG1, SPI_CFG1_CRCEN);
}

/**
  * @brief  Check if CRC is enabled
  * @rmtoll CFG1         CRCEN         LL_SPI_IsEnabledCRC
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledCRC(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CFG1, SPI_CFG1_CRCEN) == SPI_CFG1_CRCEN) ? 1UL : 0UL);
}

/**
  * @brief  Set CRC Length
  * @note   This configuration can not be changed when SPI is enabled.
  * @rmtoll CFG1         CRCSIZE       LL_SPI_SetCRCWidth
  * @param  SPIx SPI Instance
  * @param  CRCLength This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CRC_4BIT
  *         @arg @ref LL_SPI_CRC_5BIT
  *         @arg @ref LL_SPI_CRC_6BIT
  *         @arg @ref LL_SPI_CRC_7BIT
  *         @arg @ref LL_SPI_CRC_8BIT
  *         @arg @ref LL_SPI_CRC_9BIT
  *         @arg @ref LL_SPI_CRC_10BIT
  *         @arg @ref LL_SPI_CRC_11BIT
  *         @arg @ref LL_SPI_CRC_12BIT
  *         @arg @ref LL_SPI_CRC_13BIT
  *         @arg @ref LL_SPI_CRC_14BIT
  *         @arg @ref LL_SPI_CRC_15BIT
  *         @arg @ref LL_SPI_CRC_16BIT
  *         @arg @ref LL_SPI_CRC_17BIT
  *         @arg @ref LL_SPI_CRC_18BIT
  *         @arg @ref LL_SPI_CRC_19BIT
  *         @arg @ref LL_SPI_CRC_20BIT
  *         @arg @ref LL_SPI_CRC_21BIT
  *         @arg @ref LL_SPI_CRC_22BIT
  *         @arg @ref LL_SPI_CRC_23BIT
  *         @arg @ref LL_SPI_CRC_24BIT
  *         @arg @ref LL_SPI_CRC_25BIT
  *         @arg @ref LL_SPI_CRC_26BIT
  *         @arg @ref LL_SPI_CRC_27BIT
  *         @arg @ref LL_SPI_CRC_28BIT
  *         @arg @ref LL_SPI_CRC_29BIT
  *         @arg @ref LL_SPI_CRC_30BIT
  *         @arg @ref LL_SPI_CRC_31BIT
  *         @arg @ref LL_SPI_CRC_32BIT
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetCRCWidth(SPI_TypeDef *SPIx, uint32_t CRCLength)
{
  MODIFY_REG(SPIx->CFG1, SPI_CFG1_CRCSIZE, CRCLength);
}

/**
  * @brief  Get CRC Length
  * @rmtoll CFG1          CRCSIZE       LL_SPI_GetCRCWidth
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_CRC_4BIT
  *         @arg @ref LL_SPI_CRC_5BIT
  *         @arg @ref LL_SPI_CRC_6BIT
  *         @arg @ref LL_SPI_CRC_7BIT
  *         @arg @ref LL_SPI_CRC_8BIT
  *         @arg @ref LL_SPI_CRC_9BIT
  *         @arg @ref LL_SPI_CRC_10BIT
  *         @arg @ref LL_SPI_CRC_11BIT
  *         @arg @ref LL_SPI_CRC_12BIT
  *         @arg @ref LL_SPI_CRC_13BIT
  *         @arg @ref LL_SPI_CRC_14BIT
  *         @arg @ref LL_SPI_CRC_15BIT
  *         @arg @ref LL_SPI_CRC_16BIT
  *         @arg @ref LL_SPI_CRC_17BIT
  *         @arg @ref LL_SPI_CRC_18BIT
  *         @arg @ref LL_SPI_CRC_19BIT
  *         @arg @ref LL_SPI_CRC_20BIT
  *         @arg @ref LL_SPI_CRC_21BIT
  *         @arg @ref LL_SPI_CRC_22BIT
  *         @arg @ref LL_SPI_CRC_23BIT
  *         @arg @ref LL_SPI_CRC_24BIT
  *         @arg @ref LL_SPI_CRC_25BIT
  *         @arg @ref LL_SPI_CRC_26BIT
  *         @arg @ref LL_SPI_CRC_27BIT
  *         @arg @ref LL_SPI_CRC_28BIT
  *         @arg @ref LL_SPI_CRC_29BIT
  *         @arg @ref LL_SPI_CRC_30BIT
  *         @arg @ref LL_SPI_CRC_31BIT
  *         @arg @ref LL_SPI_CRC_32BIT
  */
__STATIC_INLINE uint32_t LL_SPI_GetCRCWidth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG1, SPI_CFG1_CRCSIZE));
}

/**
  * @brief  Set NSS Mode
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CFG2         SSM           LL_SPI_SetNSSMode\n
  *         CFG2         SSOE          LL_SPI_SetNSSMode
  * @param  SPIx SPI Instance
  * @param  NSS This parameter can be one of the following values:
  *         @arg @ref LL_SPI_NSS_SOFT
  *         @arg @ref LL_SPI_NSS_HARD_INPUT
  *         @arg @ref LL_SPI_NSS_HARD_OUTPUT
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetNSSMode(SPI_TypeDef *SPIx, uint32_t NSS)
{
  MODIFY_REG(SPIx->CFG2, SPI_CFG2_SSM | SPI_CFG2_SSOE, NSS);
}

/**
  * @brief  Set NSS Mode
  * @rmtoll CFG2         SSM           LL_SPI_GetNSSMode\n
  *         CFG2         SSOE          LL_SPI_GetNSSMode
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_NSS_SOFT
  *         @arg @ref LL_SPI_NSS_HARD_INPUT
  *         @arg @ref LL_SPI_NSS_HARD_OUTPUT
  */
__STATIC_INLINE uint32_t LL_SPI_GetNSSMode(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CFG2, SPI_CFG2_SSM | SPI_CFG2_SSOE));
}

/**
  * @brief  Enable NSS pulse mgt
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CFG2         SSOM          LL_SPI_EnableNSSPulseMgt
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableNSSPulseMgt(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CFG2, SPI_CFG2_SSOM);
}

/**
  * @brief  Disable NSS pulse mgt
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CFG2         SSOM          LL_SPI_DisableNSSPulseMgt
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableNSSPulseMgt(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CFG2, SPI_CFG2_SSOM);
}

/**
  * @brief  Check if NSS pulse is enabled
  * @rmtoll CFG2         SSOM          LL_SPI_IsEnabledNSSPulse
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledNSSPulse(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CFG2, SPI_CFG2_SSOM) == SPI_CFG2_SSOM) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check if there is enough data in FIFO to read a full packet
  * @rmtoll SR           RXP           LL_SPI_IsActiveFlag_RXP
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXP(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_RXP) == (SPI_SR_RXP)) ? 1UL : 0UL);
}

/**
  * @brief  Check if there is enough space in FIFO to hold a full packet
  * @rmtoll SR           TXP           LL_SPI_IsActiveFlag_TXP
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXP(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_TXP) == (SPI_SR_TXP)) ? 1UL : 0UL);
}

/**
  * @brief  Check if there enough space in FIFO to hold a full packet, AND enough data to read a full packet
  * @rmtoll SR           DXP           LL_SPI_IsActiveFlag_DXP
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_DXP(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_DXP) == (SPI_SR_DXP)) ? 1UL : 0UL);
}

/**
  * @brief  Check that end of transfer event occurred
  * @rmtoll SR           EOT           LL_SPI_IsActiveFlag_EOT
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_EOT(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_EOT) == (SPI_SR_EOT)) ? 1UL : 0UL);
}

/**
  * @brief  Check that all required data has been filled in the fifo according to transfer size
  * @rmtoll SR           TXTF          LL_SPI_IsActiveFlag_TXTF
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXTF(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_TXTF) == (SPI_SR_TXTF)) ? 1UL : 0UL);
}

/**
  * @brief  Get Underrun error flag
  * @rmtoll SR           UDR           LL_SPI_IsActiveFlag_UDR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_UDR(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_UDR) == (SPI_SR_UDR)) ? 1UL : 0UL);
}

/**
  * @brief  Get CRC error flag
  * @rmtoll SR           CRCE        LL_SPI_IsActiveFlag_CRCERR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_CRCERR(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_CRCE) == (SPI_SR_CRCE)) ? 1UL : 0UL);
}

/**
  * @brief  Get  Mode fault error flag
  * @rmtoll SR           MODF          LL_SPI_IsActiveFlag_MODF
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_MODF(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_MODF) == (SPI_SR_MODF)) ? 1UL : 0UL);
}

/**
  * @brief  Get Overrun error flag
  * @rmtoll SR           OVR           LL_SPI_IsActiveFlag_OVR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_OVR(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_OVR) == (SPI_SR_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get TI Frame format error flag
  * @rmtoll SR           TIFRE         LL_SPI_IsActiveFlag_FRE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_FRE(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_TIFRE) == (SPI_SR_TIFRE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if a suspend operation is done
  * @rmtoll SR           SUSP          LL_SPI_IsActiveFlag_SUSP
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_SUSP(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_SUSP) == (SPI_SR_SUSP)) ? 1UL : 0UL);
}

/**
  * @brief  Check if last TxFIFO or CRC frame transmission is completed
  * @rmtoll SR           TXC           LL_SPI_IsActiveFlag_TXC
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXC(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_TXC) == (SPI_SR_TXC)) ? 1UL : 0UL);
}

/**
  * @brief  Check if at least one 32-bit data is available in RxFIFO
  * @rmtoll SR           RXWNE         LL_SPI_IsActiveFlag_RXWNE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXWNE(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_RXWNE) == (SPI_SR_RXWNE)) ? 1UL : 0UL);
}

/**
  * @brief  Get number of data framed remaining in current TSIZE
  * @rmtoll SR           CTSIZE           LL_SPI_GetRemainingDataFrames
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetRemainingDataFrames(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->SR, SPI_SR_CTSIZE) >> SPI_SR_CTSIZE_Pos);
}

/**
  * @brief  Get RxFIFO packing Level
  * @rmtoll SR           RXPLVL        LL_SPI_GetRxFIFOPackingLevel
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_RX_FIFO_0PACKET
  *         @arg @ref LL_SPI_RX_FIFO_1PACKET
  *         @arg @ref LL_SPI_RX_FIFO_2PACKET
  *         @arg @ref LL_SPI_RX_FIFO_3PACKET
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxFIFOPackingLevel(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->SR, SPI_SR_RXPLVL));
}

/**
  * @brief  Clear End Of Transfer flag
  * @rmtoll IFCR         EOTC          LL_SPI_ClearFlag_EOT
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_EOT(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_EOTC);
}

/**
  * @brief  Clear TXTF flag
  * @rmtoll IFCR         TXTFC         LL_SPI_ClearFlag_TXTF
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_TXTF(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_TXTFC);
}

/**
  * @brief  Clear Underrun error flag
  * @rmtoll IFCR         UDRC          LL_SPI_ClearFlag_UDR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_UDR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_UDRC);
}

/**
  * @brief  Clear Overrun error flag
  * @rmtoll IFCR         OVRC          LL_SPI_ClearFlag_OVR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_OVR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_OVRC);
}

/**
  * @brief  Clear CRC error flag
  * @rmtoll IFCR         CRCEC        LL_SPI_ClearFlag_CRCERR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_CRCERR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_CRCEC);
}

/**
  * @brief  Clear  Mode fault error flag
  * @rmtoll IFCR         MODFC         LL_SPI_ClearFlag_MODF
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_MODF(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_MODFC);
}

/**
  * @brief  Clear Frame format error flag
  * @rmtoll IFCR         TIFREC        LL_SPI_ClearFlag_FRE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_FRE(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_TIFREC);
}

/**
  * @brief  Clear SUSP flag
  * @rmtoll IFCR         SUSPC         LL_SPI_ClearFlag_SUSP
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_SUSP(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_SUSPC);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable Rx Packet available IT
  * @rmtoll IER          RXPIE         LL_SPI_EnableIT_RXP
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXP(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_RXPIE);
}

/**
  * @brief  Enable Tx Packet space available IT
  * @rmtoll IER          TXPIE         LL_SPI_EnableIT_TXP
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXP(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_TXPIE);
}

/**
  * @brief  Enable Duplex Packet available IT
  * @rmtoll IER          DXPIE         LL_SPI_EnableIT_DXP
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_DXP(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_DXPIE);
}

/**
  * @brief  Enable End Of Transfer IT
  * @rmtoll IER          EOTIE         LL_SPI_EnableIT_EOT
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_EOT(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_EOTIE);
}

/**
  * @brief  Enable TXTF IT
  * @rmtoll IER          TXTFIE        LL_SPI_EnableIT_TXTF
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXTF(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_TXTFIE);
}

/**
  * @brief  Enable Underrun IT
  * @rmtoll IER          UDRIE         LL_SPI_EnableIT_UDR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_UDR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_UDRIE);
}

/**
  * @brief  Enable Overrun IT
  * @rmtoll IER          OVRIE         LL_SPI_EnableIT_OVR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_OVR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_OVRIE);
}

/**
  * @brief  Enable CRC Error IT
  * @rmtoll IER          CRCEIE        LL_SPI_EnableIT_CRCERR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_CRCERR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_CRCEIE);
}

/**
  * @brief  Enable TI Frame Format Error IT
  * @rmtoll IER          TIFREIE       LL_SPI_EnableIT_FRE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_FRE(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_TIFREIE);
}

/**
  * @brief  Enable MODF IT
  * @rmtoll IER          MODFIE        LL_SPI_EnableIT_MODF
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_MODF(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->IER, SPI_IER_MODFIE);
}

/**
  * @brief  Disable Rx Packet available IT
  * @rmtoll IER          RXPIE         LL_SPI_DisableIT_RXP
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXP(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_RXPIE);
}

/**
  * @brief  Disable Tx Packet space available IT
  * @rmtoll IER          TXPIE         LL_SPI_DisableIT_TXP
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXP(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_TXPIE);
}

/**
  * @brief  Disable Duplex Packet available IT
  * @rmtoll IER          DXPIE         LL_SPI_DisableIT_DXP
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_DXP(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_DXPIE);
}

/**
  * @brief  Disable End Of Transfer IT
  * @rmtoll IER          EOTIE         LL_SPI_DisableIT_EOT
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_EOT(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_EOTIE);
}

/**
  * @brief  Disable TXTF IT
  * @rmtoll IER          TXTFIE        LL_SPI_DisableIT_TXTF
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXTF(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_TXTFIE);
}

/**
  * @brief  Disable Underrun IT
  * @rmtoll IER          UDRIE         LL_SPI_DisableIT_UDR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_UDR(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_UDRIE);
}

/**
  * @brief  Disable Overrun IT
  * @rmtoll IER          OVRIE         LL_SPI_DisableIT_OVR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_OVR(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_OVRIE);
}

/**
  * @brief  Disable CRC Error IT
  * @rmtoll IER          CRCEIE        LL_SPI_DisableIT_CRCERR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_CRCERR(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_CRCEIE);
}

/**
  * @brief  Disable TI Frame Format Error IT
  * @rmtoll IER          TIFREIE       LL_SPI_DisableIT_FRE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_FRE(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_TIFREIE);
}

/**
  * @brief  Disable MODF IT
  * @rmtoll IER          MODFIE        LL_SPI_DisableIT_MODF
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_MODF(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->IER, SPI_IER_MODFIE);
}

/**
  * @brief  Check if Rx Packet available IT is enabled
  * @rmtoll IER          RXPIE         LL_SPI_IsEnabledIT_RXP
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXP(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_RXPIE) == (SPI_IER_RXPIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx Packet space available IT is enabled
  * @rmtoll IER          TXPIE         LL_SPI_IsEnabledIT_TXP
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXP(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_TXPIE) == (SPI_IER_TXPIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Duplex Packet available IT is enabled
  * @rmtoll IER          DXPIE         LL_SPI_IsEnabledIT_DXP
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_DXP(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_DXPIE) == (SPI_IER_DXPIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if End Of Transfer IT is enabled
  * @rmtoll IER          EOTIE         LL_SPI_IsEnabledIT_EOT
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_EOT(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_EOTIE) == (SPI_IER_EOTIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if TXTF IT is enabled
  * @rmtoll IER          TXTFIE        LL_SPI_IsEnabledIT_TXTF
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXTF(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_TXTFIE) == (SPI_IER_TXTFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Underrun IT is enabled
  * @rmtoll IER          UDRIE         LL_SPI_IsEnabledIT_UDR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_UDR(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_UDRIE) == (SPI_IER_UDRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Overrun IT is enabled
  * @rmtoll IER          OVRIE         LL_SPI_IsEnabledIT_OVR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_OVR(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_OVRIE) == (SPI_IER_OVRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if CRC Error IT is enabled
  * @rmtoll IER          CRCEIE        LL_SPI_IsEnabledIT_CRCERR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_CRCERR(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_CRCEIE) == (SPI_IER_CRCEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if TI Frame Format Error IT is enabled
  * @rmtoll IER          TIFREIE       LL_SPI_IsEnabledIT_FRE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_FRE(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_TIFREIE) == (SPI_IER_TIFREIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if MODF IT is enabled
  * @rmtoll IER          MODFIE        LL_SPI_IsEnabledIT_MODF
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_MODF(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->IER, SPI_IER_MODFIE) == (SPI_IER_MODFIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_DMA_Management DMA Management
  * @{
  */

/**
  * @brief  Enable DMA Rx
  * @rmtoll CFG1         RXDMAEN       LL_SPI_EnableDMAReq_RX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_RX(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CFG1, SPI_CFG1_RXDMAEN);
}

/**
  * @brief  Disable DMA Rx
  * @rmtoll CFG1         RXDMAEN       LL_SPI_DisableDMAReq_RX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_RX(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CFG1, SPI_CFG1_RXDMAEN);
}

/**
  * @brief  Check if DMA Rx is enabled
  * @rmtoll CFG1         RXDMAEN       LL_SPI_IsEnabledDMAReq_RX
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_RX(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CFG1, SPI_CFG1_RXDMAEN) == (SPI_CFG1_RXDMAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable DMA Tx
  * @rmtoll CFG1         TXDMAEN       LL_SPI_EnableDMAReq_TX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_TX(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CFG1, SPI_CFG1_TXDMAEN);
}

/**
  * @brief  Disable DMA Tx
  * @rmtoll CFG1         TXDMAEN       LL_SPI_DisableDMAReq_TX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_TX(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CFG1, SPI_CFG1_TXDMAEN);
}

/**
  * @brief  Check if DMA Tx is enabled
  * @rmtoll CFG1         TXDMAEN       LL_SPI_IsEnabledDMAReq_TX
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_TX(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CFG1, SPI_CFG1_TXDMAEN) == (SPI_CFG1_TXDMAEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_DATA_Management DATA_Management
  * @{
  */

/**
  * @brief  Read Data Register
  * @rmtoll RXDR         .       LL_SPI_ReceiveData8
  * @param  SPIx SPI Instance
  * @retval 0..0xFF
  */
__STATIC_INLINE uint8_t LL_SPI_ReceiveData8(SPI_TypeDef *SPIx)
{
  return (*((__IO uint8_t *)&SPIx->RXDR));
}

/**
  * @brief  Read Data Register
  * @rmtoll RXDR         .       LL_SPI_ReceiveData16
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint16_t LL_SPI_ReceiveData16(SPI_TypeDef *SPIx)
{
  return (uint16_t)(READ_REG(SPIx->RXDR));
}

/**
  * @brief  Read Data Register
  * @rmtoll RXDR         .       LL_SPI_ReceiveData32
  * @param  SPIx SPI Instance
  * @retval  0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_ReceiveData32(SPI_TypeDef *SPIx)
{
  return (*((__IO uint32_t *)&SPIx->RXDR));
}

/**
  * @brief  Write Data Register
  * @rmtoll TXDR         .       LL_SPI_TransmitData8
  * @param  SPIx SPI Instance
  * @param  TxData 0..0xFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_TransmitData8(SPI_TypeDef *SPIx, uint8_t TxData)
{
  *((__IO uint8_t *)&SPIx->TXDR) = TxData;
}

/**
  * @brief  Write Data Register
  * @rmtoll TXDR         .       LL_SPI_TransmitData16
  * @param  SPIx SPI Instance
  * @param  TxData 0..0xFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_TransmitData16(SPI_TypeDef *SPIx, uint16_t TxData)
{
#if defined (__GNUC__)
  __IO uint16_t *spitxdr = ((__IO uint16_t *)&SPIx->TXDR);
  *spitxdr = TxData;
#else
  SPIx->TXDR = TxData;
#endif /* __GNUC__ */
}

/**
  * @brief  Write Data Register
  * @rmtoll TXDR         .       LL_SPI_TransmitData32
  * @param  SPIx SPI Instance
  * @param  TxData 0..0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_TransmitData32(SPI_TypeDef *SPIx, uint32_t TxData)
{
  *((__IO uint32_t *)&SPIx->TXDR) = TxData;
}

/**
  * @brief  Set polynomial for CRC calcul
  * @rmtoll CRCPOLY      CRCPOLY       LL_SPI_SetCRCPolynomial
  * @param  SPIx SPI Instance
  * @param  CRCPoly 0..0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetCRCPolynomial(SPI_TypeDef *SPIx, uint32_t CRCPoly)
{
  WRITE_REG(SPIx->CRCPOLY, CRCPoly);
}

/**
  * @brief  Get polynomial for CRC calcul
  * @rmtoll CRCPOLY      CRCPOLY       LL_SPI_GetCRCPolynomial
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetCRCPolynomial(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->CRCPOLY));
}

/**
  * @brief  Set the underrun pattern
  * @rmtoll UDRDR        UDRDR         LL_SPI_SetUDRPattern
  * @param  SPIx SPI Instance
  * @param  Pattern 0..0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetUDRPattern(SPI_TypeDef *SPIx, uint32_t Pattern)
{
  WRITE_REG(SPIx->UDRDR, Pattern);
}

/**
  * @brief  Get the underrun pattern
  * @rmtoll UDRDR        UDRDR         LL_SPI_GetUDRPattern
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetUDRPattern(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->UDRDR));
}

/**
  * @brief  Get Rx CRC
  * @rmtoll RXCRCR       RXCRC         LL_SPI_GetRxCRC
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxCRC(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->RXCRC));
}

/**
  * @brief  Get Tx CRC
  * @rmtoll TXCRCR       TXCRC         LL_SPI_GetTxCRC
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxCRC(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->TXCRC));
}

/**
  * @}
  */

/** @defgroup SPI_LL_AutonomousMode Configuration functions related to Autonomous mode feature
  * @{
  */

/**
  * @brief  Enable Selected Trigger
  * @rmtoll AUTOCR          TRIGEN          LL_SPI_Enable_SelectedTrigger
  * @param  SPIx SPI Instance.
  * @retval None
  */
__STATIC_INLINE void LL_SPI_Enable_SelectedTrigger(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->AUTOCR, SPI_AUTOCR_TRIGEN);
}

/**
  * @brief  Disable Selected Trigger
  * @rmtoll AUTOCR          TRIGEN          LL_SPI_Disable_SelectedTrigger
  * @param  SPIx SPI Instance.
  * @retval None
  */
__STATIC_INLINE void LL_SPI_Disable_SelectedTrigger(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->AUTOCR, SPI_AUTOCR_TRIGEN);
}

/**
  * @brief  Indicate if selected Trigger is disabled or enabled
  * @rmtoll AUTOCR          TRIGEN          LL_SPI_IsEnabled_SelectedTrigger
  * @param  SPIx SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabled_SelectedTrigger(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->AUTOCR, SPI_AUTOCR_TRIGEN) == (SPI_AUTOCR_TRIGEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the trigger polarity
  * @rmtoll AUTOCR        TRIGPOL     LL_SPI_SetTriggerPolarity
  * @param  SPIx SPI Instance.
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_TRIG_POLARITY_RISING
  *         @arg @ref LL_SPI_TRIG_POLARITY_FALLING
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetTriggerPolarity(SPI_TypeDef *SPIx, uint32_t Polarity)
{
  MODIFY_REG(SPIx->AUTOCR, SPI_AUTOCR_TRIGPOL, Polarity);
}

/**
  * @brief  Get the trigger polarity
  * @rmtoll AUTOCR        TRIGPOL     LL_SPI_GetTriggerPolarity
  * @param  SPIx SPI Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_TRIG_POLARITY_RISING
  *         @arg @ref LL_SPI_TRIG_POLARITY_FALLING
  */
__STATIC_INLINE uint32_t LL_SPI_GetTriggerPolarity(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->AUTOCR, SPI_AUTOCR_TRIGPOL));
}

/**
  * @brief  Set the selected trigger
  * @rmtoll AUTOCR        TRIGSEL     LL_SPI_SetSelectedTrigger
  * @param  SPIx SPI Instance.
  * @param  Trigger This parameter can be one of the following values:
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH0_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH1_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH2_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH3_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_EXTI4_TRG
  *         @arg @ref  LL_SPI_GRP1_EXTI9_TRG
  *         @arg @ref  LL_SPI_GRP1_LPTIM1_CH1_TRG
  *         @arg @ref  LL_SPI_GRP1_LPTIM2_CH1_TRG
  *         @arg @ref  LL_SPI_GRP1_COMP1_TRG
  *         @arg @ref  LL_SPI_GRP1_COMP2_TRG
  *         @arg @ref  LL_SPI_GRP1_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_GRP1_RTC_WUT_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH0_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH1_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH2_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH3_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_EXTI4_TRG
  *         @arg @ref  LL_SPI_GRP2_EXTI8_TRG
  *         @arg @ref  LL_SPI_GRP2_LPTIM1_CH1_TRG
  *         @arg @ref  LL_SPI_GRP2_LPTIM3_CH1_TRG
  *         @arg @ref  LL_SPI_GRP2_COMP1_TRG
  *         @arg @ref  LL_SPI_GRP2_COMP2_TRG
  *         @arg @ref  LL_SPI_GRP2_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_GRP2_RTC_WUT_TRG
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetSelectedTrigger(SPI_TypeDef *SPIx, uint32_t Trigger)
{
  MODIFY_REG(SPIx->AUTOCR, SPI_AUTOCR_TRIGSEL, (Trigger & SPI_AUTOCR_TRIGSEL_Msk));
}

/**
  * @brief  Get the selected trigger
  * @rmtoll AUTOCR        TRIGSEL     LL_SPI_GetSelectedTrigger
  * @param  SPIx SPI Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH0_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH1_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH2_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_GPDMA_CH3_TCF_TRG
  *         @arg @ref  LL_SPI_GRP1_EXTI4_TRG
  *         @arg @ref  LL_SPI_GRP1_EXTI9_TRG
  *         @arg @ref  LL_SPI_GRP1_LPTIM1_CH1_TRG
  *         @arg @ref  LL_SPI_GRP1_LPTIM2_CH1_TRG
  *         @arg @ref  LL_SPI_GRP1_COMP1_TRG
  *         @arg @ref  LL_SPI_GRP1_COMP2_TRG
  *         @arg @ref  LL_SPI_GRP1_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_GRP1_RTC_WUT_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH0_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH1_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH2_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_LPDMA_CH3_TCF_TRG
  *         @arg @ref  LL_SPI_GRP2_EXTI4_TRG
  *         @arg @ref  LL_SPI_GRP2_EXTI8_TRG
  *         @arg @ref  LL_SPI_GRP2_LPTIM1_CH1_TRG
  *         @arg @ref  LL_SPI_GRP2_LPTIM3_CH1_TRG
  *         @arg @ref  LL_SPI_GRP2_COMP1_TRG
  *         @arg @ref  LL_SPI_GRP2_COMP2_TRG
  *         @arg @ref  LL_SPI_GRP2_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_GRP2_RTC_WUT_TRG
  */
__STATIC_INLINE uint32_t LL_SPI_GetSelectedTrigger(SPI_TypeDef *SPIx)
{
  if (IS_LL_SPI_GRP2_INSTANCE(SPIx))
  {
    return (uint32_t)((READ_BIT(SPIx->AUTOCR, SPI_AUTOCR_TRIGSEL) | LL_SPI_TRIG_GRP2));
  }
  else
  {
    return (uint32_t)((READ_BIT(SPIx->AUTOCR, SPI_AUTOCR_TRIGSEL) | LL_SPI_TRIG_GRP1));
  }
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup SPI_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_SPI_DeInit(SPI_TypeDef *SPIx);
ErrorStatus LL_SPI_Init(SPI_TypeDef *SPIx, LL_SPI_InitTypeDef *SPI_InitStruct);
void        LL_SPI_StructInit(LL_SPI_InitTypeDef *SPI_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */
/**
  * @}
  */


#endif /* defined(SPI1) || defined(SPI2) || defined(SPI3) */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_SPI_H */
