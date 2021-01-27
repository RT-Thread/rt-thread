/**
 *******************************************************************************
 * @file  hc32f4a0_spi.h
 * @brief This file contains all the functions prototypes of the SPI driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wangmin         First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_SPI_H__
#define __HC32F4A0_SPI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_SPI
 * @{
 */

#if (DDL_SPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Types SPI Global Types
 * @{
 */

/**
 * @brief Structure definition of SPI initialization.
 */
typedef struct
{
    uint32_t u32WireMode;           /*!< SPI wire mode, 3 wire mode or 4 wire mode.
                                         This parameter can be a value of @ref SPI_Wire_Mode_Define */
    uint32_t u32TransMode;          /*!< SPI transfer mode, send only or full duplex.
                                         This parameter can be a value of @ref SPI_Transfer_Mode_Define */
    uint32_t u32MasterSlave;        /*!< SPI master/slave mode.
                                         This parameter can be a value of @ref SPI_Master_Slave_Mode_Define */
    uint32_t u32SuspMode;           /*!< SPI communication suspend function.
                                         This parameter can be a value of @ref SPI_Communication_Suspend_Function_Define */
    uint32_t u32Modfe;              /*!< SPI mode fault detect command.
                                         This parameter can be a value of @ref SPI_Mode_Fault_Dectet_Command_Define */
    uint32_t u32Parity;             /*!< SPI parity check selection.
                                         This parameter can be a value of @ref SPI_Parity_Check_Define */
    uint32_t u32SpiMode;            /*!< SPI mode.
                                         This parameter can be a value of @ref SPI_Mode_Define */
    uint32_t u32BaudRatePrescaler;  /*!< SPI baud rate prescaler.
                                         This parameter can be a value of @ref SPI_Baud_Rate_Prescaler_Define */
    uint32_t u32DataBits;           /*!< SPI data bits, 4 bits ~ 32 bits.
                                         This parameter can be a value of @ref SPI_Data_Size_Define */
    uint32_t u32FirstBit;           /*!< MSB first or LSB first.
                                         This parameter can be a value of @ref SPI_First_Bit_Define */
    uint32_t u32FrameLevel;         /*!< SPI frame level, SPI_FRAME_1 ~ SPI_FRAME_4.
                                         This parameter can be a value of @ref SPI_Frame_Level_Define */
} stc_spi_init_t;

/**
 * @brief Structure definition of SPI delay time configuration.
 */
typedef struct
{
    uint32_t u32IntervalDelay;      /*!< SPI interval time delay (Next access delay time)
                                         This parameter can be a value of @ref SPI_Interval_Delay_Time_define */
    uint32_t u32ReleaseDelay;       /*!< SPI release time delay (SCK invalid delay time)
                                         This parameter can be a value of @ref SPI_Release_Delay_Time_define */
    uint32_t u32SetupDelay;         /*!< SPI Setup time delay (SCK valid delay time) define
                                         This parameter can be a value of @ref SPI_Setup_Delay_Time_define */
} stc_spi_delay_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Macros SPI Global Macros
 * @{
 */

/**
 * @defgroup SPI_Wire_Mode_Define SPI wire mode define
 * @{
 */
#define SPI_WIRE_4                  (0UL)
#define SPI_WIRE_3                  (SPI_CR1_SPIMDS)
/**
 * @}
 */

/**
 * @defgroup SPI_Transfer_Mode_Define SPI transfer mode define
 * @{
 */
#define SPI_FULL_DUPLEX             (0UL)               /*!< Full duplex. */
#define SPI_SEND_ONLY               (SPI_CR1_TXMDS)     /*!< Send only. */
/**
 * @}
 */

/**
 * @defgroup SPI_Master_Slave_Mode_Define SPI master slave mode define
 * @{
 */
#define SPI_SLAVE                   (0UL)
#define SPI_MASTER                  (SPI_CR1_MSTR)
/**
 * @}
 */

/**
 * @defgroup SPI_Loopback_Selection_Define SPI loopback selection define
 * @note Loopback mode is mainly used for parity self-diagnosis in 4-wire full-duplex mode.
 * @{
 */
#define SPI_SPLPBK_INVALID          (0UL)
#define SPI_SPLPBK_MOSI_INVERT      (SPI_CR1_SPLPBK)    /*!< MISO data is the inverse of the data output by MOSI. */
#define SPI_SPLPBK_MOSI             (SPI_CR1_SPLPBK2)   /*!< MISO data is the data output by MOSI. */
/**
 * @}
 */

/**
 * @defgroup SPI_Communication_Suspend_Function_Define SPI communication suspend function define
 * @{
 */
#define SPI_COM_SUSP_FUNC_OFF       (0UL)
#define SPI_COM_SUSP_FUNC_ON        (SPI_CR1_CSUSPE)
/**
 * @}
 */

/**
 * @defgroup SPI_Interrupt_Type_Define SPI interrupt type define
 * @{
 */
#define SPI_INT_ERROR               (SPI_CR1_EIE)       /*!< Including overload, underload and parity error. */
#define SPI_INT_TX_BUFFER_EMPTY     (SPI_CR1_TXIE)
#define SPI_INT_RX_BUFFER_FULL      (SPI_CR1_RXIE)
#define SPI_INT_IDLE                (SPI_CR1_IDIE)
/**
 * @}
 */

/**
 * @defgroup SPI_Mode_Fault_Dectet_Command_Define SPI mode fault dectect command define
 * @{
 */
#define SPI_MODFE_DISABLE           (0UL)               /*!< Disable mode fault detection. */
#define SPI_MODFE_ENABLE            (SPI_CR1_MODFE)     /*!< Enable mode fault detection. */
/**
 * @}
 */

/**
 * @defgroup SPI_Parity_Check_Error_Self_Diagnosis_Define SPI parity check error self diagnosis define
 * @{
 */
#define SPI_PATE_DISABLE            (0UL)               /*!< Disable self diagnosis of parity check. */
#define SPI_PATE_ENABLE             (SPI_CR1_PATE)      /*!< Enable self diagnosis of parity check. */
/**
 * @}
 */

/**
 * @defgroup SPI_Parity_Check_Define SPI parity check mode define
 * @{
 */
#define SPI_PARITY_INVALID          (0UL)                           /*!< Parity check invalid. */
#define SPI_PARITY_EVEN             (SPI_CR1_PAE)                   /*!< Parity check selection even parity. */
#define SPI_PARITY_ODD              (SPI_CR1_PAE | SPI_CR1_PAOE)    /*!< Parity check selection odd parity. */
/**
 * @}
 */

/**
 * @defgroup SPI_Interval_Delay_Time_define SPI interval time delay (Next access delay time) define
 * @{
 */
#define SPI_INTERVAL_TIME_1SCK_2PCLK1  (0UL)
#define SPI_INTERVAL_TIME_2SCK_2PCLK1  (SPI_CFG1_MIDI_0)
#define SPI_INTERVAL_TIME_3SCK_2PCLK1  (SPI_CFG1_MIDI_1)
#define SPI_INTERVAL_TIME_4SCK_2PCLK1  (SPI_CFG1_MIDI_1 | SPI_CFG1_MIDI_0)
#define SPI_INTERVAL_TIME_5SCK_2PCLK1  (SPI_CFG1_MIDI_2)
#define SPI_INTERVAL_TIME_6SCK_2PCLK1  (SPI_CFG1_MIDI_2 | SPI_CFG1_MIDI_0)
#define SPI_INTERVAL_TIME_7SCK_2PCLK1  (SPI_CFG1_MIDI_2 | SPI_CFG1_MIDI_1)
#define SPI_INTERVAL_TIME_8SCK_2PCLK1  (SPI_CFG1_MIDI_2 | SPI_CFG1_MIDI_1 | SPI_CFG1_MIDI_0)
/**
 * @}
 */

/**
 * @defgroup SPI_Release_Delay_Time_define SPI release time delay (SCK invalid delay time) define
 * @{
 */
#define SPI_RELEASE_TIME_1SCK         (0UL)
#define SPI_RELEASE_TIME_2SCK         (SPI_CFG1_MSSDL_0)
#define SPI_RELEASE_TIME_3SCK         (SPI_CFG1_MSSDL_1)
#define SPI_RELEASE_TIME_4SCK         (SPI_CFG1_MSSDL_1 | SPI_CFG1_MSSDL_0)
#define SPI_RELEASE_TIME_5SCK         (SPI_CFG1_MSSDL_2)
#define SPI_RELEASE_TIME_6SCK         (SPI_CFG1_MSSDL_2 | SPI_CFG1_MSSDL_0)
#define SPI_RELEASE_TIME_7SCK         (SPI_CFG1_MSSDL_2 | SPI_CFG1_MSSDL_1)
#define SPI_RELEASE_TIME_8SCK         (SPI_CFG1_MSSDL_2 | SPI_CFG1_MSSDL_1 | SPI_CFG1_MSSDL_0)
/**
 * @}
 */

/**
 * @defgroup SPI_Setup_Delay_Time_define SPI Setup time delay (SCK valid delay time) define
 * @{
 */
#define SPI_SETUP_TIME_1SCK         (0UL)
#define SPI_SETUP_TIME_2SCK         (SPI_CFG1_MSSI_0)
#define SPI_SETUP_TIME_3SCK         (SPI_CFG1_MSSI_1)
#define SPI_SETUP_TIME_4SCK         (SPI_CFG1_MSSI_1 | SPI_CFG1_MSSI_0)
#define SPI_SETUP_TIME_5SCK         (SPI_CFG1_MSSI_2)
#define SPI_SETUP_TIME_6SCK         (SPI_CFG1_MSSI_2 | SPI_CFG1_MSSI_0)
#define SPI_SETUP_TIME_7SCK         (SPI_CFG1_MSSI_2 | SPI_CFG1_MSSI_1)
#define SPI_SETUP_TIME_8SCK         (SPI_CFG1_MSSI_2 | SPI_CFG1_MSSI_1 | SPI_CFG1_MSSI_0)
/**
 * @}
 */

/**
 * @defgroup SPI_SS_Pin_Define SPI SSx define
 * @{
 */
#define SPI_PIN_SS0                 (SPI_CFG1_SS0PV)
#define SPI_PIN_SS1                 (SPI_CFG1_SS1PV)
#define SPI_PIN_SS2                 (SPI_CFG1_SS2PV)
#define SPI_PIN_SS3                 (SPI_CFG1_SS3PV)
/**
 * @}
 */

/**
 * @defgroup SPI_SS_Active_Level_Define SPI SSx Active Level define
 * @{
 */
#define SPI_SS_ACTIVE_LOW          (0UL)               /*!< SS pin active low. */
#define SPI_SS_ACTIVE_HIGH         (1UL)               /*!< SS pin active high. */
/**
 * @}
 */

/**
 * @defgroup SPI_Read_Target_Buffer_Define SPI read data register target buffer define
 * @{
 */
#define SPI_RD_TARGET_RD_BUF        (0UL)               /*!< Read RX buffer. */
#define SPI_RD_TARGET_WR_BUF        (SPI_CFG1_SPRDTD)   /*!< Read TX buffer. */
/**
 * @}
 */

/**
 * @defgroup SPI_Frame_Level_Define SPI data frame level define, The Data in the
 *                                   SPI_DR register will be send to TX_BUFF after
 *                                   enough data frame write to the SPI_DR
 * @{
 */
#define SPI_FRAME_1     (0UL)                               /*!< Data 1 frame */
#define SPI_FRAME_2     (SPI_CFG1_FTHLV_0)                  /*!< Data 2 frame.*/
#define SPI_FRAME_3     (SPI_CFG1_FTHLV_1)                  /*!< Data 3 frame.*/
#define SPI_FRAME_4     (SPI_CFG1_FTHLV_0 | SPI_CFG1_FTHLV_1) /*!< Data 4 frame.*/
/**
 * @}
 */

/**
 * @defgroup SPI_Mode_Define SPI Mode define
 * @{
 */
/* SCK pin output low in idle state; MOSI/MISO pin data valid in odd edge , MOSI/MISO pin data change in even edge */
#define SPI_MODE_0                  (0UL)
/* SCK pin output low in idle state; MOSI/MISO pin data valid in even edge , MOSI/MISO pin data change in odd edge */
#define SPI_MODE_1                  (SPI_CFG2_CPHA)
/* SCK pin output high in idle state; MOSI/MISO pin data valid in odd edge , MOSI/MISO pin data change in even edge */
#define SPI_MODE_2                  (SPI_CFG2_CPOL)
/* SCK pin output high in idle state; MOSI/MISO pin data valid in even edge , MOSI/MISO pin data change in odd edge */
#define SPI_MODE_3                  (SPI_CFG2_CPOL | SPI_CFG2_CPHA)
/**
 * @}
 */

/**
 * @defgroup SPI_Baud_Rate_Prescaler_Define SPI baudrate prescaler define
 * @{
 */
#define SPI_BR_PCLK1_DIV2            (0UL)                               /*!< SPI baud rate is the pclk1 divided by 2. */
#define SPI_BR_PCLK1_DIV4            (SPI_CFG2_MBR_0)                    /*!< SPI baud rate is the pclk1 clock divided by 4. */
#define SPI_BR_PCLK1_DIV8            (SPI_CFG2_MBR_1)                    /*!< SPI baud rate is the pclk1 clock divided by 8. */
#define SPI_BR_PCLK1_DIV16           (SPI_CFG2_MBR_1 | SPI_CFG2_MBR_0)   /*!< SPI baud rate is the pclk1 clock divided by 16. */
#define SPI_BR_PCLK1_DIV32           (SPI_CFG2_MBR_2)                    /*!< SPI baud rate is the pclk1 clock divided by 32. */
#define SPI_BR_PCLK1_DIV64           (SPI_CFG2_MBR_2 | SPI_CFG2_MBR_0)   /*!< SPI baud rate is the pclk1 clock divided by 64. */
#define SPI_BR_PCLK1_DIV128          (SPI_CFG2_MBR_2 | SPI_CFG2_MBR_1)   /*!< SPI baud rate is the pclk1 clock divided by 128. */
#define SPI_BR_PCLK1_DIV256          (SPI_CFG2_MBR_2 | SPI_CFG2_MBR_1 | SPI_CFG2_MBR_0)  /*!< SPI baud rate is the pclk1 divided by 256. */
/**
 * @}
 */

/**
 * @defgroup SPI_Data_Size_Define SPI data size define
 * @{
 */
#define SPI_DATA_SIZE_4BIT          (0UL)
#define SPI_DATA_SIZE_5BIT          (SPI_CFG2_DSIZE_0)
#define SPI_DATA_SIZE_6BIT          (SPI_CFG2_DSIZE_1)
#define SPI_DATA_SIZE_7BIT          (SPI_CFG2_DSIZE_0 | SPI_CFG2_DSIZE_1)
#define SPI_DATA_SIZE_8BIT          (SPI_CFG2_DSIZE_2)
#define SPI_DATA_SIZE_9BIT          (SPI_CFG2_DSIZE_2 | SPI_CFG2_DSIZE_0)
#define SPI_DATA_SIZE_10BIT         (SPI_CFG2_DSIZE_2 | SPI_CFG2_DSIZE_1)
#define SPI_DATA_SIZE_11BIT         (SPI_CFG2_DSIZE_2 | SPI_CFG2_DSIZE_1 | SPI_CFG2_DSIZE_0)
#define SPI_DATA_SIZE_12BIT         (SPI_CFG2_DSIZE_3)
#define SPI_DATA_SIZE_13BIT         (SPI_CFG2_DSIZE_3 | SPI_CFG2_DSIZE_0)
#define SPI_DATA_SIZE_14BIT         (SPI_CFG2_DSIZE_3 | SPI_CFG2_DSIZE_1)
#define SPI_DATA_SIZE_15BIT         (SPI_CFG2_DSIZE_3 | SPI_CFG2_DSIZE_1 | SPI_CFG2_DSIZE_0)
#define SPI_DATA_SIZE_16BIT         (SPI_CFG2_DSIZE_3 | SPI_CFG2_DSIZE_2)
#define SPI_DATA_SIZE_20BIT         (SPI_CFG2_DSIZE_3 | SPI_CFG2_DSIZE_2 | SPI_CFG2_DSIZE_0)
#define SPI_DATA_SIZE_24BIT         (SPI_CFG2_DSIZE_3 | SPI_CFG2_DSIZE_2 | SPI_CFG2_DSIZE_1)
#define SPI_DATA_SIZE_32BIT         (SPI_CFG2_DSIZE_3 | SPI_CFG2_DSIZE_2 | SPI_CFG2_DSIZE_1 | SPI_CFG2_DSIZE_0)
/**
 * @}
 */

/**
 * @defgroup SPI_First_Bit_Define SPI first bit define
 * @{
 */
#define SPI_FIRST_MSB               (0UL)
#define SPI_FIRST_LSB               (SPI_CFG2_LSBF)
/**
 * @}
 */

/**
 * @defgroup SPI_State_Flag_Define SPI state flag define
 * @{
 */
#define SPI_FLAG_OVERLOAD           (SPI_SR_OVRERF)
#define SPI_FLAG_IDLE               (SPI_SR_IDLNF)
#define SPI_FLAG_MODE_FAULT         (SPI_SR_MODFERF)
#define SPI_FLAG_PARITY_ERROR       (SPI_SR_PERF)
#define SPI_FLAG_UNDERLOAD          (SPI_SR_UDRERF)
#define SPI_FLAG_TX_BUFFER_EMPTY    (SPI_SR_TDEF)       /*!< This flag is set when the data in the data register     \
                                                             is copied into the shift register, but the transmission \
                                                             of the data bit may not have been completed. */
#define SPI_FLAG_RX_BUFFER_FULL     (SPI_SR_RDFF)       /*!< When this flag is set, it indicates that a data was received. */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup SPI_Global_Functions
 * @{
 */
en_result_t SPI_StructInit(stc_spi_init_t *pstcInit);
en_result_t SPI_DelayStructInit(stc_spi_delay_t *pstcDelayCfg);

en_result_t SPI_Init(M4_SPI_TypeDef *SPIx, const stc_spi_init_t *pstcInit);
void SPI_DeInit(M4_SPI_TypeDef *SPIx);

void SPI_IntCmd(M4_SPI_TypeDef *SPIx, uint32_t u32IntType, en_functional_state_t enNewState);
void SPI_FunctionCmd(M4_SPI_TypeDef *SPIx, en_functional_state_t enNewState);

void SPI_WriteDataReg(M4_SPI_TypeDef *SPIx, uint32_t u32Data);
uint32_t SPI_ReadDataReg(const M4_SPI_TypeDef *SPIx);

en_flag_status_t SPI_GetStatus(const M4_SPI_TypeDef *SPIx, uint32_t u32Flag);
void SPI_ClearFlag(M4_SPI_TypeDef *SPIx, uint32_t u32Flag);

void SPI_LoopbackModeCfg(M4_SPI_TypeDef *SPIx, uint32_t u32Mode);
void SPI_PateCmd(M4_SPI_TypeDef *SPIx, en_functional_state_t enNewState);
en_result_t SPI_DelayTimeCfg(M4_SPI_TypeDef *SPIx, const stc_spi_delay_t *pstcDelayCfg);
void SPI_SSValidLevelCfg(M4_SPI_TypeDef *SPIx, uint32_t u32SSPin, en_functional_state_t enNewState);
void SPI_SSPinSel(M4_SPI_TypeDef *SPIx, uint32_t u32SSPin);
void SPI_ReadBufCfg(M4_SPI_TypeDef *SPIx, uint32_t u32ReadBuf);

en_result_t SPI_Transmit(M4_SPI_TypeDef *SPIx, const void *pvTxBuf, uint32_t u32TxLength);
en_result_t SPI_Receive(M4_SPI_TypeDef *SPIx, void *pvRxBuf, uint32_t u32RxLength);
en_result_t SPI_TransmitReceive(M4_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, uint32_t u32Length);

/**
 * @}
 */

#endif /* DDL_SPI_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_SPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
