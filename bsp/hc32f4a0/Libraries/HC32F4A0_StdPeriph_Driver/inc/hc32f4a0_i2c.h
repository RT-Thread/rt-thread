/**
 *******************************************************************************
 * @file  hc32f4a0_i2c.h
 * @brief This file contains all the functions prototypes of the Inter-Integrated
 *        Circuit(I2C).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hexiao          First version
   2020-07-15       Hexiao          Modify I2C_SmBusCmd to I2C_SetMode
   2020-08-31       Hexiao          Remove invalid clock division value
   2020-10-30       Hexiao          Optimize data transfer api,etc.
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
#ifndef __HC32F4A0_I2C_H__
#define __HC32F4A0_I2C_H__

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
 * @addtogroup DDL_I2C
 * @{
 */

#if (DDL_I2C_ENABLE == DDL_ON)

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
typedef struct
{
    uint32_t u32ClkDiv;   /*!< I2C clock division for pclk3*/
    uint32_t u32Baudrate;    /*!< I2C baudrate config*/
    uint32_t u32SclTime;     /*!< The SCL rising and falling time, count of T(pclk3)*/
}stc_i2c_init_t;

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

/** @defgroup I2C_Buadrate_Max I2C baudrate max value
  * @{
  */
#define I2C_BAUDRATE_MAX                    (400000UL)
/**
 * @}
 */

/** @defgroup I2C_Mode Peripheral Mode
  * @{
  */
#define I2C_MODE_I2C                        (0UL)
#define I2C_MODE_SMBUS                      (2UL)
/**
 * @}
 */

/** @defgroup I2C_Transfer_Direction I2C transfer direction
  * @{
  */
#define I2C_DIR_TX                          (0x0U)
#define I2C_DIR_RX                          (0x1U)
/**
 * @}
 */

/** @defgroup I2C_Addr_Config I2C address configuration
  * @{
  */
#define I2C_ADDR_MODE_7BIT                  (0x0U)
#define I2C_ADDR_MODE_10BIT                 (I2C_SLR0_ADDRMOD0)
/**
 * @}
 */

/** @defgroup I2C_Clock_division I2C clock division
  * @{
  */
#define I2C_CLK_DIV1                        (0UL)
#define I2C_CLK_DIV2                        (1UL)
#define I2C_CLK_DIV4                        (2UL)
#define I2C_CLK_DIV8                        (3UL)
#define I2C_CLK_DIV16                       (4UL)
#define I2C_CLK_DIV32                       (5UL)
#define I2C_CLK_DIV64                       (6UL)
#define I2C_CLK_DIV128                      (7UL)
/**
 * @}
 */

/** @defgroup I2C_Address_Num I2C address number
  * @{
  */
#define I2C_ADDR_0                          (0UL)
#define I2C_ADDR_1                          (1UL)
/**
 * @}
 */

/** @defgroup I2C_Ack_Type I2C ack type
  * @{
  */
#define I2C_ACK                             (0UL)
#define I2C_NACK                            (I2C_CR1_ACK)
/**
 * @}
 */

/** @defgroup I2C_Smbus_Match_Cfg I2C smbus address match configuration
  * @{
  */
#define I2C_SMBUS_MATCH_ALRT                (I2C_CR1_SMBALRTEN)
#define I2C_SMBUS_MATCH_DEFAULT             (I2C_CR1_SMBDEFAULTEN)
#define I2C_SMBUS_MATCH_HOST                (I2C_CR1_SMBHOSTEN)
/**
 * @}
 */

/** @defgroup I2C_Smbus_clear_mask I2C smbus clear mask
  * @{
  */
#define I2C_SMBUS_CONFIG_CLEARMASK     (I2C_CR1_SMBALRTEN|I2C_CR1_SMBDEFAULTEN|I2C_CR1_SMBHOSTEN)
/**
 * @}
 */

/** @defgroup I2C_Digital_Filter_mode I2C digital filter mode
  * @{
  */
#define I2C_DIG_FILTMODE_1CYCLE              (0UL << I2C_FLTR_DNF_POS)
#define I2C_DIG_FILTMODE_2CYCLE              (1UL << I2C_FLTR_DNF_POS)
#define I2C_DIG_FILTMODE_3CYCLE              (2UL << I2C_FLTR_DNF_POS)
#define I2C_DIG_FILTMODE_4CYCLE              (3UL << I2C_FLTR_DNF_POS)
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
void I2C_DeInit(M4_I2C_TypeDef* I2Cx);
en_result_t I2C_StructInit(stc_i2c_init_t* pstcI2C_InitStruct);
en_result_t I2C_Init(M4_I2C_TypeDef* I2Cx, const stc_i2c_init_t *pstcI2C_InitStruct, float32_t *pf32Err);
en_result_t I2C_BaudrateConfig(M4_I2C_TypeDef* I2Cx, const stc_i2c_init_t *pstcI2C_InitStruct, float32_t *pf32Err);
void I2C_SlaveAddrCmd(M4_I2C_TypeDef* I2Cx, uint32_t u32AddrNum, en_functional_state_t enNewState);
void I2C_SlaveAddrConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32Addr);
void I2C_SetMode(M4_I2C_TypeDef* I2Cx, uint32_t u32Mode);
void I2C_Cmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_FastAckCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_BusWaitCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_SoftwareResetCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_IntCmd(M4_I2C_TypeDef* I2Cx, uint32_t u32IntEn, en_functional_state_t enNewState);

void I2C_ClkHighTimeoutConfig(M4_I2C_TypeDef* I2Cx, uint16_t u16TimeoutH);
void I2C_ClkLowTimeoutConfig(M4_I2C_TypeDef* I2Cx, uint16_t u16TimeoutL);
void I2C_ClkHighTimeoutCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_ClkLowTimeoutCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_ClkTimeoutCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_SmbusConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32SmbusConfig, en_functional_state_t enNewState);
void I2C_DigitalFilterConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32DigFilterMode);
void I2C_DigitalFilterCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_AnalogFilterCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_GeneralCallCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);

/* Start/Restart/Stop ************************************************/
void I2C_GenerateStart(M4_I2C_TypeDef* I2Cx);
void I2C_GenerateReStart(M4_I2C_TypeDef* I2Cx);
void I2C_GenerateStop(M4_I2C_TypeDef* I2Cx);

/* Status management *************************************************/
en_flag_status_t I2C_GetStatus(const M4_I2C_TypeDef *I2Cx, uint32_t u32StatusBit);
void I2C_ClearStatus(M4_I2C_TypeDef* I2Cx, uint32_t u32StatusBit);

/* Data transfer *****************************************************/
void I2C_WriteDataReg(M4_I2C_TypeDef* I2Cx, uint8_t u8Data);
uint8_t I2C_ReadDataReg(const M4_I2C_TypeDef *I2Cx);
void I2C_AckConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32AckConfig);

/* High level functions for reference ********************************/
en_result_t I2C_Start(M4_I2C_TypeDef* I2Cx, uint32_t u32Timeout);
en_result_t I2C_Restart(M4_I2C_TypeDef* I2Cx, uint32_t u32Timeout);
en_result_t I2C_TransAddr(M4_I2C_TypeDef* I2Cx, uint8_t u8Addr, uint8_t u8Dir, uint32_t u32Timeout);
en_result_t I2C_Trans10BitAddr(M4_I2C_TypeDef* I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout);
en_result_t I2C_TransData(M4_I2C_TypeDef* I2Cx, uint8_t const pau8TxData[], uint32_t u32Size, uint32_t u32Timeout);
en_result_t I2C_Receive(M4_I2C_TypeDef* I2Cx, uint8_t pau8RxData[], uint32_t u32Size, uint32_t u32Timeout);
en_result_t I2C_Stop(M4_I2C_TypeDef* I2Cx, uint32_t u32Timeout);
en_result_t I2C_MasterReceiveAndStop(M4_I2C_TypeDef* I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout);
/**
 * @}
 */

#endif /* DDL_I2C_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_I2C_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
