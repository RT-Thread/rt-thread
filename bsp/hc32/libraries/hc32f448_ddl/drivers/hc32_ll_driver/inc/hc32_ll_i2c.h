/**
 *******************************************************************************
 * @file  hc32_ll_i2c.h
 * @brief This file contains all the functions prototypes of the Inter-Integrated
 *        Circuit(I2C) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-09-30       CDT             Move macro define I2C_SRC_CLK to head file and add marco I2C_WIDTH_MAX_IMME
   2023-12-15       CDT             Rename I2C_FIFO_FLAG_xx as I2C_FLAG_xx_FIFO_xx, I2C_INT_RFREQ as I2C_INT_RX_FIFO_REQ
                                    Adjust I2C_FLAG_ALL & I2C_FLAG_CLR_ALL & I2C_INT_ALL
                                    Add I2C_Flag_Clear def group
                                    Remove API I2C_FIFO_ClearRequestStatus() & I2C_FIFO_GetStatus
                                    Fix I2C_Deinit
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_I2C_H__
#define __HC32_LL_I2C_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_I2C
 * @{
 */

#if (LL_I2C_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup I2C_Global_Types I2C Global Types
 * @{
 */

/**
 * @brief I2c configuration structure
 */
typedef struct {
    uint32_t u32ClockDiv;           /*!< I2C clock division for i2c source clock */
    uint32_t u32Baudrate;           /*!< I2C baudrate config */
    uint32_t u32SclTime;            /*!< The SCL rising and falling time, count of T(i2c source clock after frequency divider) */
} stc_i2c_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup I2C_Global_Macros I2C Global Macros
 * @{
 */

#define I2C_SRC_CLK                   (SystemCoreClock >> ((CM_CMU->SCFGR & CMU_SCFGR_PCLK0S) >> CMU_SCFGR_PCLK0S_POS))

#define I2C_WIDTH_MAX_IMME            (516UL)

/**
 * @defgroup I2C_Trans_Dir I2C Transfer Direction
 * @{
 */
#define I2C_DIR_TX                    (0x0U)
#define I2C_DIR_RX                    (0x1U)
/**
 * @}
 */

/**
 * @defgroup I2C_Addr_Config I2C Address Configure
 * @{
 */
#define I2C_ADDR_DISABLE              (0U)
#define I2C_ADDR_7BIT                 (I2C_SLR0_SLADDR0EN)
#define I2C_ADDR_10BIT                (I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0EN)
/**
 * @}
 */

/**
 * @defgroup I2C_Clock_Division I2C Clock Division
 * @{
 */
#define I2C_CLK_DIV1                  (0UL)         /*!< I2c source clock/1 */
#define I2C_CLK_DIV2                  (1UL)         /*!< I2c source clock/2 */
#define I2C_CLK_DIV4                  (2UL)         /*!< I2c source clock/4 */
#define I2C_CLK_DIV8                  (3UL)         /*!< I2c source clock/8 */
#define I2C_CLK_DIV16                 (4UL)         /*!< I2c source clock/16 */
#define I2C_CLK_DIV32                 (5UL)         /*!< I2c source clock/32 */
#define I2C_CLK_DIV64                 (6UL)         /*!< I2c source clock/64 */
#define I2C_CLK_DIV128                (7UL)         /*!< I2c source clock/128 */
/**
 * @}
 */

/**
 * @defgroup I2C_Address_Num I2C Address Number
 * @{
 */
#define I2C_ADDR0                     (0UL)
#define I2C_ADDR1                     (1UL)
/**
 * @}
 */

/**
 * @defgroup I2C_Ack_Config I2C ACK Configure
 * @{
 */
#define I2C_ACK                       (0UL)         /*!< Send ACK after date receive */
#define I2C_NACK                      (I2C_CR1_ACK) /*!< Send NACK after date received */
/**
 * @}
 */

/**
 * @defgroup I2C_Smbus_Match_Config I2C SMBUS Address Match Configure
 * @{
 */
#define I2C_SMBUS_MATCH_ALARM         (I2C_CR1_SMBALRTEN)
#define I2C_SMBUS_MATCH_DEFAULT       (I2C_CR1_SMBDEFAULTEN)
#define I2C_SMBUS_MATCH_HOST          (I2C_CR1_SMBHOSTEN)
#define I2C_SMBUS_MATCH_ALL           (I2C_CR1_SMBALRTEN | I2C_CR1_SMBDEFAULTEN | I2C_CR1_SMBHOSTEN)
/**
 * @}
 */

/**
 * @defgroup I2C_Digital_Filter_Clock I2C Digital Filter Clock
 * @{
 */
#define I2C_DIG_FILTER_CLK_DIV1       (0UL << I2C_FLTR_DNF_POS) /*!< I2C Clock/1 */
#define I2C_DIG_FILTER_CLK_DIV2       (1UL << I2C_FLTR_DNF_POS) /*!< I2C Clock/2 */
#define I2C_DIG_FILTER_CLK_DIV3       (2UL << I2C_FLTR_DNF_POS) /*!< I2C Clock/3 */
#define I2C_DIG_FILTER_CLK_DIV4       (3UL << I2C_FLTR_DNF_POS) /*!< I2C Clock/4 */
/**
 * @}
 */

/**
 * @defgroup I2C_Flag I2C Flag
 * @{
 */
#define I2C_FLAG_START                (I2C_SR_STARTF)      /*!< Start condition detected */
#define I2C_FLAG_MATCH_ADDR0          (I2C_SR_SLADDR0F)    /*!< Address 0 detected */
#define I2C_FLAG_MATCH_ADDR1          (I2C_SR_SLADDR1F)    /*!< Address 1 detected */
#define I2C_FLAG_TX_CPLT              (I2C_SR_TENDF)       /*!< Transfer end */
#define I2C_FLAG_STOP                 (I2C_SR_STOPF)       /*!< Stop condition detected */
#define I2C_FLAG_RX_FULL              (I2C_SR_RFULLF)      /*!< Receive buffer full */
#define I2C_FLAG_TX_EMPTY             (I2C_SR_TEMPTYF)     /*!< Transfer buffer empty */
#define I2C_FLAG_ARBITRATE_FAIL       (I2C_SR_ARLOF)       /*!< Arbitration fails */
#define I2C_FLAG_ACKR                 (I2C_SR_ACKRF)       /*!< ACK status */
#define I2C_FLAG_NACKF                (I2C_SR_NACKF)       /*!< NACK detected */
#define I2C_FLAG_TMOUTF               (I2C_SR_TMOUTF)      /*!<  Time out detected */
#define I2C_FLAG_MASTER               (I2C_SR_MSL)         /*!< Master mode flag */
#define I2C_FLAG_BUSY                 (I2C_SR_BUSY)        /*!< Bus busy status */
#define I2C_FLAG_TRA                  (I2C_SR_TRA)         /*!< Transfer mode flag */
#define I2C_FLAG_GENERAL_CALL         (I2C_SR_GENCALLF)    /*!< General call detected */
#define I2C_FLAG_SMBUS_DEFAULT_MATCH  (I2C_SR_SMBDEFAULTF) /*!< SMBUS default address detected */
#define I2C_FLAG_SMBUS_HOST_MATCH     (I2C_SR_SMBHOSTF)    /*!< SMBUS host address detected */
#define I2C_FLAG_SMBUS_ALARM_MATCH    (I2C_SR_SMBALRTF)    /*!< SMBUS alarm address detected */
#define I2C_FLAG_RX_FIFO_REQ          (I2C_SR_RFREQ)       /*!< Receive FIFO request */
#define I2C_FLAG_RX_FIFO_FULL         (I2C_SR_RFFULL)      /*!< Receive FIFO full */
#define I2C_FLAG_RX_FIFO_EMPTY        (I2C_SR_RFEMPTY)     /*!< Receive FIFO empty */
#define I2C_FLAG_TX_FIFO_FULL         (I2C_SR_TFFULL)      /*!< Transfer FIFO full */
#define I2C_FLAG_TX_FIFO_EMPTY        (I2C_SR_TFEMPTY)     /*!< Transfer FIFO empty */

#define I2C_FLAG_ALL                  (I2C_FLAG_START          | I2C_FLAG_NACKF               | \
                                       I2C_FLAG_MATCH_ADDR0    | I2C_FLAG_TMOUTF              | \
                                       I2C_FLAG_MATCH_ADDR1    | I2C_FLAG_MASTER              | \
                                       I2C_FLAG_TX_CPLT        | I2C_FLAG_BUSY                | \
                                       I2C_FLAG_STOP           | I2C_FLAG_TRA                 | \
                                       I2C_FLAG_RX_FULL        | I2C_FLAG_GENERAL_CALL        | \
                                       I2C_FLAG_TX_EMPTY       | I2C_FLAG_SMBUS_DEFAULT_MATCH | \
                                       I2C_FLAG_ARBITRATE_FAIL | I2C_FLAG_SMBUS_HOST_MATCH    | \
                                       I2C_FLAG_ACKR           | I2C_FLAG_SMBUS_ALARM_MATCH   | \
                                       I2C_FLAG_RX_FIFO_REQ    | I2C_FLAG_RX_FIFO_FULL        | \
                                       I2C_FLAG_RX_FIFO_EMPTY  | I2C_FLAG_TX_FIFO_FULL        | \
                                       I2C_FLAG_TX_FIFO_EMPTY)
/**
 * @}
 */

/**
 * @defgroup I2C_Flag_Clear I2C Flag to clear
 * @{
 */
#define I2C_FLAG_CLR_START                  (I2C_CLR_STARTFCLR)      /*!< Start condition detected */
#define I2C_FLAG_CLR_MATCH_ADDR0            (I2C_CLR_SLADDR0FCLR)    /*!< Address 0 detected */
#define I2C_FLAG_CLR_MATCH_ADDR1            (I2C_CLR_SLADDR1FCLR)    /*!< Address 1 detected */
#define I2C_FLAG_CLR_TX_CPLT                (I2C_CLR_TENDFCLR)       /*!< Transfer end */
#define I2C_FLAG_CLR_STOP                   (I2C_CLR_STOPFCLR)       /*!< Stop condition detected */
#define I2C_FLAG_CLR_RX_FULL                (I2C_CLR_RFULLFCLR)      /*!< Receive buffer full */
#define I2C_FLAG_CLR_ARBITRATE_FAIL         (I2C_CLR_ARLOFCLR)       /*!< Arbitration fails */
#define I2C_FLAG_CLR_NACK                   (I2C_CLR_NACKFCLR)       /*!< NACK detected */
#define I2C_FLAG_CLR_TMOUTF                 (I2C_CLR_TMOUTFCLR)      /*!< Time out detected */
#define I2C_FLAG_CLR_GENERAL_CALL           (I2C_CLR_GENCALLFCLR)    /*!< General call detected */
#define I2C_FLAG_CLR_SMBUS_DEFAULT_MATCH    (I2C_CLR_SMBDEFAULTFCLR) /*!< SMBUS default address detected */
#define I2C_FLAG_CLR_SMBUS_HOST_MATCH       (I2C_CLR_SMBHOSTFCLR)    /*!< SMBUS host address detected */
#define I2C_FLAG_CLR_SMBUS_ALARM_MATCH      (I2C_CLR_SMBALRTFCLR)    /*!< SMBUS alarm address detected */
#define I2C_FLAG_CLR_RX_FIFO_REQ            (I2C_CLR_RFREQCLR)       /*!< Receive FIFO request */

#define I2C_FLAG_CLR_ALL              (I2C_FLAG_CLR_START       | I2C_FLAG_CLR_ARBITRATE_FAIL      | \
                                       I2C_FLAG_CLR_MATCH_ADDR0 | I2C_FLAG_CLR_NACK                | \
                                       I2C_FLAG_CLR_MATCH_ADDR1 | I2C_FLAG_CLR_TMOUTF              | \
                                       I2C_FLAG_CLR_TX_CPLT     | I2C_FLAG_CLR_GENERAL_CALL        | \
                                       I2C_FLAG_CLR_STOP        | I2C_FLAG_CLR_SMBUS_DEFAULT_MATCH | \
                                       I2C_FLAG_CLR_RX_FULL     | I2C_FLAG_CLR_SMBUS_HOST_MATCH    | \
                                       I2C_FLAG_CLR_SMBUS_ALARM_MATCH   | \
                                       I2C_FLAG_CLR_RX_FIFO_REQ)

/**
 * @}
 */

/**
 * @defgroup I2C_FIFO_Data_Status I2C FIFO status
 * @{
 */
#define I2C_FIFO_EMPTY                 (0U)
#define I2C_FIFO_HALFFULL              (1U)
#define I2C_FIFO_FULL                  (2U)
/**
 * @}
 */

/**
 * @defgroup I2C_Int_Flag I2C Interrupt Flag Bits
 * @{
 */
#define I2C_INT_START                 (I2C_CR2_STARTIE)
#define I2C_INT_MATCH_ADDR0           (I2C_CR2_SLADDR0IE)
#define I2C_INT_MATCH_ADDR1           (I2C_CR2_SLADDR1IE)
#define I2C_INT_TX_CPLT               (I2C_CR2_TENDIE)
#define I2C_INT_STOP                  (I2C_CR2_STOPIE)
#define I2C_INT_RX_FULL               (I2C_CR2_RFULLIE)
#define I2C_INT_TX_EMPTY              (I2C_CR2_TEMPTYIE)
#define I2C_INT_ARBITRATE_FAIL        (I2C_CR2_ARLOIE)
#define I2C_INT_NACK                  (I2C_CR2_NACKIE)
#define I2C_INT_TMOUTIE               (I2C_CR2_TMOUTIE)
#define I2C_INT_GENERAL_CALL          (I2C_CR2_GENCALLIE)
#define I2C_INT_SMBUS_DEFAULT_MATCH   (I2C_CR2_SMBDEFAULTIE)
#define I2C_INT_SMBUS_HOST_MATCH      (I2C_CR2_SMBHOSTIE)
#define I2C_INT_SMBUS_ALARM_MATCH     (I2C_CR2_SMBALRTIE)
#define I2C_INT_RX_FIFO_REQ           (I2C_CR2_RFREQIE)
#define I2C_INT_ALL                   (I2C_INT_START       | I2C_INT_ARBITRATE_FAIL      | \
                                       I2C_INT_MATCH_ADDR0 | I2C_INT_NACK                | \
                                       I2C_INT_MATCH_ADDR1 | I2C_INT_TMOUTIE             | \
                                       I2C_INT_TX_CPLT     | I2C_INT_GENERAL_CALL        | \
                                       I2C_INT_STOP        | I2C_INT_SMBUS_DEFAULT_MATCH | \
                                       I2C_INT_RX_FULL     | I2C_INT_SMBUS_HOST_MATCH    | \
                                       I2C_INT_TX_EMPTY    | I2C_INT_SMBUS_ALARM_MATCH   | \
                                       I2C_INT_RX_FIFO_REQ)
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
 * @addtogroup I2C_Global_Functions
 * @{
 */

/* Initialization and Configuration **********************************/
int32_t I2C_StructInit(stc_i2c_init_t *pstcI2cInit);
int32_t I2C_BaudrateConfig(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t *pstcI2cInit, float32_t *pf32Error);
int32_t I2C_DeInit(CM_I2C_TypeDef *I2Cx);
int32_t I2C_Init(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t *pstcI2cInit, float32_t *pf32Error);
void I2C_SlaveAddrConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32Addr);
void I2C_SlaveAddrCmd(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, en_functional_state_t enNewState);
void I2C_Cmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_FastAckCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_BusWaitCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);

void I2C_SmbusConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32SmbusConfig, en_functional_state_t enNewState);
void I2C_SmbusCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);

void I2C_DigitalFilterConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32FilterClock);
void I2C_DigitalFilterCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);

void I2C_AnalogFilterCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);

void I2C_GeneralCallCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_SWResetCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_IntCmd(CM_I2C_TypeDef *I2Cx, uint32_t u32IntType, en_functional_state_t enNewState);

void I2C_SlaveMaskAddrConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32MaskAddr);
void I2C_SlaveMaskAddrCmd(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, en_functional_state_t enNewState);

void I2C_BusFreeClearCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);

/* Start/Restart/Stop ************************************************/
void I2C_GenerateStart(CM_I2C_TypeDef *I2Cx);
void I2C_GenerateRestart(CM_I2C_TypeDef *I2Cx);
void I2C_GenerateStop(CM_I2C_TypeDef *I2Cx);

/* Status management *************************************************/
en_flag_status_t I2C_GetStatus(const CM_I2C_TypeDef *I2Cx, uint32_t u32Flag);
void I2C_ClearStatus(CM_I2C_TypeDef *I2Cx, uint32_t u32Flag);

/* FIFO *************************************************************/
void I2C_FIFO_Cmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
uint32_t I2C_FIFO_GetTxDataNum(const CM_I2C_TypeDef *I2Cx);
uint32_t I2C_FIFO_GetRxDataStatus(const CM_I2C_TypeDef *I2Cx);
uint32_t I2C_FIFO_GetTxDataStatus(const CM_I2C_TypeDef *I2Cx);
void I2C_FIFO_NackResetFIFOCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_FIFO_TxFlush(CM_I2C_TypeDef *I2Cx);
void I2C_FIFO_RxFlush(CM_I2C_TypeDef *I2Cx);

/* Data transfer *****************************************************/
void I2C_WriteData(CM_I2C_TypeDef *I2Cx, uint8_t u8Data);
uint8_t I2C_ReadData(const CM_I2C_TypeDef *I2Cx);
void I2C_AckConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32AckConfig);

/* Time out function *************************************************/
void I2C_SCLHighTimeoutConfig(CM_I2C_TypeDef *I2Cx, uint16_t u16TimeoutH);
void I2C_SCLLowTimeoutConfig(CM_I2C_TypeDef *I2Cx, uint16_t u16TimeoutL);
void I2C_SCLHighTimeoutCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_SCLLowTimeoutCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_SCLTimeoutCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);

/* High level functions for reference ********************************/
int32_t I2C_Start(CM_I2C_TypeDef *I2Cx, uint32_t u32Timeout);
int32_t I2C_Restart(CM_I2C_TypeDef *I2Cx, uint32_t u32Timeout);
int32_t I2C_TransAddr(CM_I2C_TypeDef *I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout);
int32_t I2C_Trans10BitAddr(CM_I2C_TypeDef *I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout);
int32_t I2C_TransData(CM_I2C_TypeDef *I2Cx, uint8_t const au8TxData[], uint32_t u32Size, uint32_t u32Timeout);
int32_t I2C_ReceiveData(CM_I2C_TypeDef *I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout);
int32_t I2C_MasterReceiveDataAndStop(CM_I2C_TypeDef *I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout);
int32_t I2C_Stop(CM_I2C_TypeDef *I2Cx, uint32_t u32Timeout);
int32_t I2C_WaitStatus(const CM_I2C_TypeDef *I2Cx, uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout);

/**
 * @}
 */

#endif /* LL_I2C_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_I2C_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
