/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_i2c.h
 **
 ** A detailed description is available at
 ** @link I2cGroup Inter-Integrated Circuit(I2C) description @endlink
 **
 **   - 2018-10-16  CDT  First version for Device Driver Library of I2C.
 **
 ******************************************************************************/

#ifndef __HC32F460_I2C_H__
#define __HC32F460_I2C_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_I2C_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup I2cGroup Inter-Integrated Circuit (I2C)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief I2c configuration structure
 **
 ******************************************************************************/
typedef struct stc_i2c_init
{
    uint32_t u32ClockDiv;    ///< I2C clock division for i2c source clock
    uint32_t u32Baudrate;    ///< I2C baudrate config
    uint32_t u32SclTime;     ///< The SCL rising and falling time, count of T(i2c source clock after frequency divider)
}stc_i2c_init_t;

/**
 *******************************************************************************
 ** \brief I2c SMBUS configuration structure
 **
 ******************************************************************************/
typedef struct stc_i2c_smbus_init
{
    en_functional_state_t enHostAdrMatchFunc;     ///< SMBUS host address matching function
    en_functional_state_t enDefaultAdrMatchFunc;  ///< SMBUS default address matching function
    en_functional_state_t enAlarmAdrMatchFunc;    ///< SMBUS Alarm address matching function
}stc_i2c_smbus_init_t;

/**
 *******************************************************************************
 ** \brief I2c digital filter mode enumeration
 **
 ******************************************************************************/
typedef enum en_i2c_digital_filter_mode
{
    Filter1BaseCycle = 0u,          ///< I2C digital filter ability 1 base cycle
    Filter2BaseCycle = 1u,          ///< I2C digital filter ability 2 base cycle
    Filter3BaseCycle = 2u,          ///< I2C digital filter ability 3 base cycle
    Filter4BaseCycle = 3u,          ///< I2C digital filter ability 4 base cycle
}en_i2c_digital_filter_mode_t;

/**
 *******************************************************************************
 ** \brief I2c address bit enumeration
 **
 ******************************************************************************/
typedef enum en_address_bit
{
    Adr7bit = 0u,       ///< I2C address length is 7 bits
    Adr10bit = 1u,      ///< I2C address length is 10 bits
}en_address_bit_t;

/**
 *******************************************************************************
 ** \brief I2c transfer direction enumeration
 **
 ******************************************************************************/
typedef enum en_trans_direction
{
    I2CDirTrans = 0u,
    I2CDirReceive = 1u,
}en_trans_direction_t;

/**
 *******************************************************************************
 ** \brief I2c clock timeout switch enumeration
 **
 ******************************************************************************/
typedef enum en_clock_timeout_switch
{
    TimeoutFunOff = 0u,  ///< I2C SCL pin time out function off
    LowTimerOutOn = 3u,  ///< I2C SCL pin high level time out function on
    HighTimeOutOn = 5u,  ///< I2C SCL pin low level time out function on
    BothTimeOutOn = 7u,  ///< I2C SCL pin both(low and high) level time out function on
}en_clock_timeout_switch_t;

/**
 *******************************************************************************
 ** \brief I2c clock timeout initialize structure
 **
 ******************************************************************************/
typedef struct stc_clock_timeout_init
{
    en_clock_timeout_switch_t   enClkTimeOutSwitch;  ///< I2C clock timeout function switch
    uint16_t                    u16TimeOutHigh;      ///< I2C clock timeout period for High level
    uint16_t                    u16TimeOutLow;       ///< I2C clock timeout period for Low level
}stc_clock_timeout_init_t;

/**
 *******************************************************************************
 ** \brief I2c ACK config enumeration
 **
 ******************************************************************************/
typedef enum en_i2c_ack_config
{
    I2c_ACK = 0u,
    I2c_NACK = 1u,
}en_i2c_ack_config_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* define interrupt enable bit for I2C_CR2 register */
#define I2C_CR2_STARTIE         (0x00000001ul)
#define I2C_CR2_SLADDR0EN       (0x00000002ul)
#define I2C_CR2_SLADDR1EN       (0x00000004ul)
#define I2C_CR2_TENDIE          (0x00000008ul)
#define I2C_CR2_STOPIE          (0x00000010ul)
#define I2C_CR2_RFULLIE         (0x00000040ul)
#define I2C_CR2_TEMPTYIE        (0x00000080ul)
#define I2C_CR2_ARLOIE          (0x00000200ul)
#define I2C_CR2_NACKIE          (0x00001000ul)
#define I2C_CR2_TMOURIE         (0x00004000ul)
#define I2C_CR2_GENCALLIE       (0x00100000ul)
#define I2C_CR2_SMBDEFAULTIE    (0x00200000ul)
#define I2C_CR2_SMBHOSTIE       (0x00400000ul)
#define I2C_CR2_SMBALRTIE       (0x00800000ul)

/* define status bit for I2C_SR register */
#define I2C_SR_STARTF           (0x00000001ul)
#define I2C_SR_SLADDR0F         (0x00000002ul)
#define I2C_SR_SLADDR1F         (0x00000004ul)
#define I2C_SR_TENDF            (0x00000008ul)
#define I2C_SR_STOPF            (0x00000010ul)
#define I2C_SR_RFULLF           (0x00000040ul)
#define I2C_SR_TEMPTYF          (0x00000080ul)
#define I2C_SR_ARLOF            (0x00000200ul)
#define I2C_SR_ACKRF            (0x00000400ul)
#define I2C_SR_NACKF            (0x00001000ul)
#define I2C_SR_TMOUTF           (0x00004000ul)
#define I2C_SR_MSL              (0x00010000ul)
#define I2C_SR_BUSY             (0x00020000ul)
#define I2C_SR_TRA              (0x00040000ul)
#define I2C_SR_GENCALLF         (0x00100000ul)
#define I2C_SR_SMBDEFAULTF      (0x00200000ul)
#define I2C_SR_SMBHOSTF         (0x00400000ul)
#define I2C_SR_SMBALRTF         (0x00800000ul)

/* define status clear bit for I2C_CLR register*/
#define I2C_CLR_STARTFCLR       (0x00000001ul)
#define I2C_CLR_SLADDR0FCLR     (0x00000002ul)
#define I2C_CLR_SLADDR1FCLR     (0x00000004ul)
#define I2C_CLR_TENDFCLR        (0x00000008ul)
#define I2C_CLR_STOPFCLR        (0x00000010ul)
#define I2C_CLR_RFULLFCLR       (0x00000040ul)
#define I2C_CLR_TEMPTYFCLR      (0x00000080ul)
#define I2C_CLR_ARLOFCLR        (0x00000200ul)
#define I2C_CLR_NACKFCLR        (0x00001000ul)
#define I2C_CLR_TMOUTFCLR       (0x00004000ul)
#define I2C_CLR_GENCALLFCLR     (0x00100000ul)
#define I2C_CLR_SMBDEFAULTFCLR  (0x00200000ul)
#define I2C_CLR_SMBHOSTFCLR     (0x00400000ul)
#define I2C_CLR_SMBALRTFCLR     (0x00800000ul)
#define I2C_CLR_MASK            (0x00F056DFul)

/* I2C_Clock_Division I2C clock division */
#define I2C_CLK_DIV1            (0ul)  /* I2c source clock/1 */
#define I2C_CLK_DIV2            (1ul)  /* I2c source clock/2 */
#define I2C_CLK_DIV4            (2ul)  /* I2c source clock/4 */
#define I2C_CLK_DIV8            (3ul)  /* I2c source clock/8 */
#define I2C_CLK_DIV16           (4ul)  /* I2c source clock/16 */
#define I2C_CLK_DIV32           (5ul)  /* I2c source clock/32 */
#define I2C_CLK_DIV64           (6ul)  /* I2c source clock/64 */
#define I2C_CLK_DIV128          (7ul)  /* I2c source clock/128 */
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
en_result_t I2C_BaudrateConfig(M4_I2C_TypeDef* pstcI2Cx, const stc_i2c_init_t* pstcI2cInit, float32_t *pf32Error);
en_result_t I2C_DeInit(M4_I2C_TypeDef* pstcI2Cx);
en_result_t I2C_Init(M4_I2C_TypeDef* pstcI2Cx, const stc_i2c_init_t* pstcI2cInit, float32_t *pf32Error);
void I2C_Cmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
en_result_t I2C_SmbusConfig(M4_I2C_TypeDef* pstcI2Cx, const stc_i2c_smbus_init_t* pstcI2C_SmbusInitStruct);
void I2C_SmBusCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_SoftwareResetCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);

////////////////////////////////////////////////////////////////////////////////////////
void I2C_DigitalFilterConfig(M4_I2C_TypeDef* pstcI2Cx, en_i2c_digital_filter_mode_t enDigiFilterMode);
void I2C_DigitalFilterCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_AnalogFilterCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_GeneralCallCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_SlaveAdr0Config(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState, en_address_bit_t enAdrMode, uint32_t u32Adr);
void I2C_SlaveAdr1Config(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState, en_address_bit_t enAdrMode, uint32_t u32Adr);
en_result_t I2C_ClkTimeOutConfig(M4_I2C_TypeDef* pstcI2Cx, const stc_clock_timeout_init_t* pstcTimoutInit);
void I2C_IntCmd(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32IntEn, en_functional_state_t enNewState);
void I2C_FastAckCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_BusWaitCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);

///////////////////////////////////////////////////////////////////////////////////////
void I2C_GenerateStart(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_GenerateReStart(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_GenerateStop(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_WriteData(M4_I2C_TypeDef* pstcI2Cx, uint8_t u8Data);
uint8_t I2C_ReadData(M4_I2C_TypeDef* pstcI2Cx);
void I2C_AckConfig(M4_I2C_TypeDef* pstcI2Cx, en_i2c_ack_config_t u32AckConfig);
en_flag_status_t I2C_GetStatus(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32StatusBit);
void I2C_ClearStatus(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32StatusBit);

/* High level functions for reference ********************************/
en_result_t I2C_Start(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32Timeout);
en_result_t I2C_Restart(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32Timeout);
en_result_t I2C_TransAddr(M4_I2C_TypeDef* pstcI2Cx, uint8_t u8Addr, en_trans_direction_t enDir, uint32_t u32Timeout);
en_result_t I2C_Trans10BitAddr(M4_I2C_TypeDef* pstcI2Cx, uint16_t u16Addr, en_trans_direction_t enDir, uint32_t u32Timeout);
en_result_t I2C_TransData(M4_I2C_TypeDef* pstcI2Cx, uint8_t const au8TxData[], uint32_t u32Size, uint32_t u32Timeout);
en_result_t I2C_ReceiveData(M4_I2C_TypeDef* pstcI2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout);
en_result_t I2C_Stop(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32Timeout);
en_result_t I2C_WaitStatus(const M4_I2C_TypeDef *pstcI2Cx, uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout);
en_result_t I2C_MasterDataReceiveAndStop(M4_I2C_TypeDef* pstcI2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout);

//@} // I2cGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_I2C_ENABLE */

#endif /* __HC32F460_I2C_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
