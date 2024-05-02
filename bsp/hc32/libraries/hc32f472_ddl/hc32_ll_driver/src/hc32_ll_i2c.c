/**
 *******************************************************************************
 * @file  hc32_ll_i2c.c
 * @brief This file provides firmware functions to manage the Inter-Integrated
 *        Circuit(I2C).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Fix bug for I2C_FastAckCmd()
                                    Move macro define I2C_SRC_CLK to head file
   2023-12-15       CDT             Remove API I2C_FIFO_ClearRequestStatus() & I2C_FIFO_GetStatus
                                    Modify I2C_Restart()
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_i2c.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_I2C I2C
 * @brief I2C Driver Library
 * @{
 */

#if (LL_I2C_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup I2C_Local_Macros I2C Local Macros
 * @{
 */
#define I2C_BAUDRATE_MAX                (1000000UL)
#define I2C_BAUDRATE_400K               (400000UL)

#define I2C_SCL_HIGHT_LOW_LVL_SUM_MAX   ((float32_t)0x1FE)
#define I2C_7BIT_MAX                    (0x7FUL)
#define I2C_10BIT_MAX                   (0x3FFUL)

/**
 * @defgroup I2C_Check_Parameters_Validity I2C Check Parameters Validity
 * @{
 */

#define IS_I2C_UNIT(x)                                                         \
(   ((x) == CM_I2C1)                        ||                                 \
    ((x) == CM_I2C2)                        ||                                 \
    ((x) == CM_I2C3))

#define IS_I2C_DIG_FILTER_CLK(x)        ((x) <= I2C_DIG_FILTER_CLK_DIV4)

#define IS_I2C_7BIT_ADDR(x)             ((x) <= I2C_7BIT_MAX)
#define IS_I2C_10BIT_ADDR(x)            ((x) <= I2C_10BIT_MAX)

#define IS_I2C_SPEED(x)                                                        \
(   ((x) != 0U)                                     &&                         \
    ((x) <= I2C_BAUDRATE_MAX))

#define IS_I2C_FLAG(x)                                                         \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_FLAG_ALL) == I2C_FLAG_ALL))

#define IS_I2C_CLR_FLAG(x)                                                     \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_FLAG_CLR_ALL) == I2C_FLAG_CLR_ALL))

#define IS_I2C_INT(x)                                                          \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_INT_ALL) == I2C_INT_ALL))

#define IS_I2C_SMBUS_CONFIG(x)                                                 \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_SMBUS_MATCH_ALL) == I2C_SMBUS_MATCH_ALL))

#define IS_I2C_ADDR(mode, addr)                                                \
(   ((I2C_ADDR_7BIT == (mode)) && ((addr) <= 0x7FU))        ||                 \
    ((I2C_ADDR_10BIT == (mode)) && ((addr) <= 0x3FFU))      ||                 \
    (I2C_ADDR_DISABLE == (mode)))

#define IS_I2C_ADDR_NUM(x)                                                     \
(   ((x) == I2C_ADDR0)                              ||                         \
    ((x) == I2C_ADDR1))

#define IS_I2C_CLK_DIV(x)                                                      \
(   (x) <= I2C_CLK_DIV128)

#define IS_I2C_TRANS_DIR(x)                                                    \
(   ((x) == I2C_DIR_TX)                             ||                         \
    ((x) == I2C_DIR_RX))

#define IS_I2C_ACK_CONFIG(x)                                                   \
(   ((x) == I2C_ACK)                                ||                         \
    ((x) == I2C_NACK))

#define IS_I2C_FLAG_STD(x)                                                     \
(   ((x) == RESET)                                  ||                         \
    ((x) == SET))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup I2C_Global_Functions I2C Global Functions
 * @{
 */

/**
 * @brief Try to wait a status of specified flags
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *        @arg CM_I2C or CM_I2Cx:   I2C instance register base.
 * @param [in] u32Flag              Specify the flags to check, This parameter can be any combination of the member from
 *                                  @ref I2C_Flag values:
 * @param [in] enStatus             Expected status @ref en_flag_status_t
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 */
int32_t I2C_WaitStatus(const CM_I2C_TypeDef *I2Cx, uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_TIMEOUT;
    uint32_t u32RegStatusBit;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_FLAG(u32Flag));
    DDL_ASSERT(IS_I2C_FLAG_STD(enStatus));

    for (;;) {
        u32RegStatusBit = (READ_REG32_BIT(I2Cx->SR, u32Flag));
        if (((enStatus == SET) && (u32Flag == u32RegStatusBit)) || ((enStatus == RESET) && (0UL == u32RegStatusBit))) {
            i32Ret = LL_OK;
        }

        if ((LL_OK == i32Ret) || (0UL == u32Timeout)) {
            break;
        } else {
            u32Timeout--;
        }
    }
    return i32Ret;
}

/**
 * @brief I2C generate start condition
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *        @arg CM_I2C or CM_I2Cx:   I2C instance register base.
 * @retval None
 */
void I2C_GenerateStart(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_START);
}

/**
 * @brief I2C generate restart condition
 * @param [in]  I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg CM_I2C or CM_I2Cx:        I2C instance register base.
 * @retval None
 */
void I2C_GenerateRestart(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_RESTART);
}

/**
 * @brief I2C generate stop condition
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval None
 */
void I2C_GenerateStop(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_STOP);
}

/**
 * @brief Set the baudrate for I2C peripheral.
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] pstcI2cInit          Pointer to I2C config structure  @ref stc_i2c_init_t
 *         @arg pstcI2cInit->u32ClockDiv: Division of i2c source clock, reference as:
 *              step1: calculate div = (I2cSrcClk/Baudrate/(Imme+2*Dnfsum+SclTime)
 *                     I2cSrcClk -- I2c source clock
 *                     Baudrate -- baudrate of i2c
 *                     SclTime  -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                 according to i2c bus hardware parameter.
 *                     Dnfsum   -- 0 if digital filter off;
 *                                 Filter capacity if digital filter on(1 ~ 4)
 *                     Imme     -- An Immediate data, 516
 *              step2: chose a division item which is similar and bigger than div from @ref I2C_Clock_Division.
 *         @arg pstcI2cInit->u32Baudrate : Baudrate configuration
 *         @arg pstcI2cInit->u32SclTime : Indicate SCL pin rising and falling
 *              time, should be number of T(i2c clock period time)
 * @param [out] pf32Error           Baudrate error
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t I2C_BaudrateConfig(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t *pstcI2cInit, float32_t *pf32Error)
{
    int32_t i32Ret = LL_OK;
    uint32_t I2cSrcClk;
    uint32_t I2cDivClk;
    uint32_t SclCnt;
    uint32_t Baudrate;
    uint32_t Dnfsum = 0UL;
    uint32_t Divsum = 2UL;
    uint32_t TheoryBaudrate;
    float32_t WidthTotal;
    float32_t SumTotal;
    float32_t WidthHL;
    float32_t fErr = 0.0F;

    if ((NULL == pstcI2cInit) || (NULL == pf32Error)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_I2C_UNIT(I2Cx));
        DDL_ASSERT(IS_I2C_SPEED(pstcI2cInit->u32Baudrate));
        DDL_ASSERT(IS_I2C_CLK_DIV(pstcI2cInit->u32ClockDiv));

        /* Get configuration for i2c */
        I2cSrcClk = I2C_SRC_CLK;
        I2cDivClk = 1UL << pstcI2cInit->u32ClockDiv;
        SclCnt = pstcI2cInit->u32SclTime;
        Baudrate = pstcI2cInit->u32Baudrate;

        /* Judge digital filter status */
        if (0U != READ_REG32_BIT(I2Cx->FLTR, I2C_FLTR_DNFEN)) {
            Dnfsum = (READ_REG32_BIT(I2Cx->FLTR, I2C_FLTR_DNF) >> I2C_FLTR_DNF_POS) + 1U;
        }

        /* Judge if clock divider on*/
        if (I2C_CLK_DIV1 == pstcI2cInit->u32ClockDiv) {
            Divsum = 3UL;
        }

        if (I2cDivClk != 0UL) { /* Judge for misra */
            WidthTotal = (float32_t)I2cSrcClk / (float32_t)Baudrate / (float32_t)I2cDivClk;
            SumTotal = (2.0F * (float32_t)Divsum) + (2.0F * (float32_t)Dnfsum) + (float32_t)SclCnt;
            WidthHL = WidthTotal - SumTotal;

            /* Integer for WidthTotal, rounding off */
            if ((WidthTotal - (float32_t)((uint32_t)WidthTotal)) >= 0.5F) {
                WidthTotal = (float32_t)((uint32_t)WidthTotal) + 1.0F;
            } else {
                WidthTotal = (float32_t)((uint32_t)WidthTotal);
            }

            if (WidthTotal <= SumTotal) {
                /* Err, Should set a smaller division value for pstcI2cInit->u32ClockDiv */
                i32Ret = LL_ERR_INVD_PARAM;
            } else {
                if (WidthHL > I2C_SCL_HIGHT_LOW_LVL_SUM_MAX) {
                    /* Err, Should set a bigger division value for pstcI2cInit->u32ClockDiv */
                    i32Ret = LL_ERR_INVD_PARAM;
                } else {
                    TheoryBaudrate = I2cSrcClk / (uint32_t)WidthTotal / I2cDivClk;
                    fErr = ((float32_t)Baudrate - (float32_t)TheoryBaudrate) / (float32_t)TheoryBaudrate;
                    WRITE_REG32(I2Cx->CCR,                                              \
                                (pstcI2cInit->u32ClockDiv << I2C_CCR_FREQ_POS) |       \
                                (((uint32_t)WidthHL / 2U) << I2C_CCR_SLOWW_POS) |       \
                                (((uint32_t)WidthHL - (((uint32_t)WidthHL) / 2U)) << I2C_CCR_SHIGHW_POS));
                    if (Baudrate > I2C_BAUDRATE_400K) {
                        SET_REG32_BIT(I2Cx->CCR, I2C_CCR_FMPLUSEN);
                    }
                }
            }
        } else {
            i32Ret = LL_ERR_INVD_PARAM;
        }
    }

    if ((NULL != pf32Error) && (LL_OK == i32Ret)) {
        *pf32Error = fErr;
    }

    return i32Ret;
}

/**
 * @brief De-initialize I2C unit
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 */
int32_t I2C_DeInit(CM_I2C_TypeDef *I2Cx)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    /* RESET peripheral register and internal status*/
    CLR_REG32_BIT(I2Cx->CR1, I2C_CR1_PE);
    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_SWRST);

    return LL_OK;
}

/**
 * @brief Initialize I2C peripheral according to the structure
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] pstcI2cInit          Pointer to I2C config structure  @ref stc_i2c_init_t
 *         @arg pstcI2cInit->u32ClockDiv: Division of i2c source clock, reference as:
 *              step1: calculate div = (I2cSrcClk/Baudrate/(Imme+2*Dnfsum+SclTime)
 *                     I2cSrcClk -- I2c source clock
 *                     Baudrate -- baudrate of i2c
 *                     SclTime  -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                 according to i2c bus hardware parameter.
 *                     Dnfsum   -- 0 if digital filter off;
 *                                 Filter capacity if digital filter on(1 ~ 4)
 *                     Imme     -- An Immediate data, 516
 *              step2: chose a division item which is similar and bigger than div
 *                     from @ref I2C_Clock_Division.
 *         @arg pstcI2cInit->u32Baudrate : Baudrate configuration
 *         @arg pstcI2cInit->u32SclTime : Indicate SCL pin rising and falling
 *              time, should be number of T(i2c clock period time)
 * @param [out] pf32Error           Baudrate error
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t I2C_Init(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t *pstcI2cInit, float32_t *pf32Error)
{
    int32_t i32Ret;

    if (NULL == pstcI2cInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_I2C_UNIT(I2Cx));
        DDL_ASSERT(IS_I2C_SPEED(pstcI2cInit->u32Baudrate));
        DDL_ASSERT(IS_I2C_CLK_DIV(pstcI2cInit->u32ClockDiv));

        /* Register and internal status reset */
        CLR_REG32_BIT(I2Cx->CR1, I2C_CR1_PE);
        SET_REG32_BIT(I2Cx->CR1, I2C_CR1_SWRST);
        SET_REG32_BIT(I2Cx->CR1, I2C_CR1_PE);

        /* I2C baudrate config */
        i32Ret = I2C_BaudrateConfig(I2Cx, pstcI2cInit, pf32Error);

        /* Disable global broadcast address function */
        CLR_REG32_BIT(I2Cx->CR1, I2C_CR1_ENGC);
        /* Release software reset */
        CLR_REG32_BIT(I2Cx->CR1, I2C_CR1_SWRST);
        /* Disable I2C peripheral */
        CLR_REG32_BIT(I2Cx->CR1, I2C_CR1_PE);
        /* Disable slave address function */
        CLR_REG32_BIT(I2Cx->SLR0, I2C_SLR0_SLADDR0EN);
    }
    return i32Ret;
}

/**
 * @brief I2C slave address config
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32AddrNum           I2C address 0 or address 1 @ref I2C_Address_Num
 * @param [in] u32AddrMode          Address mode configuration @ref I2C_Addr_Config
 * @param [in] u32Addr              The slave address
 * @retval None
 */
void I2C_SlaveAddrConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32Addr)
{
    __IO uint32_t *const pu32SLRx = (__IO uint32_t *)((uint32_t)&I2Cx->SLR0 + (u32AddrNum * 4UL));

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_ADDR_NUM(u32AddrNum));
    DDL_ASSERT(IS_I2C_ADDR(u32AddrMode, u32Addr));

    if (I2C_ADDR_DISABLE == u32AddrMode) {
        CLR_REG32_BIT(*pu32SLRx, I2C_SLR0_SLADDR0EN);
    } else {
        if (I2C_ADDR_10BIT == u32AddrMode) {
            MODIFY_REG32(*pu32SLRx, I2C_SLR0_SLADDR0EN | I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0,
                         u32AddrMode | u32Addr);
        } else {
            MODIFY_REG32(*pu32SLRx, I2C_SLR0_SLADDR0EN | I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0,
                         u32AddrMode | (u32Addr << 1U));
        }
    }
}

/**
 * @brief I2C slave address config
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32AddrNum           I2C address 0 or address 1 @ref I2C_Address_Num
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SlaveAddrCmd(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, en_functional_state_t enNewState)
{
    __IO uint32_t *const pu32SLRx = (__IO uint32_t *)((uint32_t)&I2Cx->SLR0 + (u32AddrNum * 4UL));
    /* Check parameters */
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_ADDR_NUM(u32AddrNum));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(*pu32SLRx, I2C_SLR0_SLADDR0EN, (uint32_t)enNewState << I2C_SLR0_SLADDR0EN_POS);
}

/**
 * @brief I2C slave address mask function config
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32AddrNum           I2C address 0 or address 1 @ref I2C_Address_Num
 * @param [in] u32AddrMode          Address mode configuration @ref I2C_Addr_Config
 * @param [in] u32MaskAddr          The slave mask address
 * @retval None
 */
void I2C_SlaveMaskAddrConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32MaskAddr)
{
    __IO uint32_t *const pu32SLRx = (__IO uint32_t *)((uint32_t)&I2Cx->SLR0 + (u32AddrNum * 4UL));

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_ADDR_NUM(u32AddrNum));
    DDL_ASSERT(IS_I2C_ADDR(u32AddrMode, u32MaskAddr));

    if (I2C_ADDR_10BIT == u32AddrMode) {
        MODIFY_REG32(*pu32SLRx, I2C_SLR0_ADDRMOD0 | I2C_SLR0_MSLADDR0,
                     u32AddrMode | (u32MaskAddr << I2C_SLR0_MSLADDR0_POS));
    } else {
        MODIFY_REG32(*pu32SLRx, I2C_SLR0_ADDRMOD0 | I2C_SLR0_MSLADDR0,
                     u32AddrMode | (u32MaskAddr << (I2C_SLR0_MSLADDR0_POS + 1U)));
    }
}

/**
 * @brief I2C mask slave address function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32AddrNum           I2C address 0 or address 1 @ref I2C_Address_Num
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SlaveMaskAddrCmd(CM_I2C_TypeDef *I2Cx, uint32_t u32AddrNum, en_functional_state_t enNewState)
{
    __IO uint32_t *const pu32SLRx = (__IO uint32_t *)((uint32_t)&I2Cx->SLR0 + (u32AddrNum * 4UL));
    /* Check parameters */
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_ADDR_NUM(u32AddrNum));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(*pu32SLRx, I2C_SLR0_MASKEN0, (uint32_t)enNewState << I2C_SLR0_MASKEN0_POS);
}

/**
 * @brief I2C function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_Cmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_PE, (uint32_t)enNewState << I2C_CR1_PE_POS);
}

/**
 * @brief I2C fast ACK config
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_FastAckCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (ENABLE == enNewState) {
        CLR_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);
    } else {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);
    }
}

/**
 * @brief I2C bus wait function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_BusWaitCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(I2Cx->CR4, I2C_CR4_BUSWAIT);
    } else {
        CLR_REG32_BIT(I2Cx->CR4, I2C_CR4_BUSWAIT);
    }
}

/**
 * @brief I2C SMBUS function configuration
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32SmbusConfig       Indicate the SMBUS address match function configuration. @ref I2C_Smbus_Match_Config
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SmbusConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32SmbusConfig, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_SMBUS_CONFIG(u32SmbusConfig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(I2Cx->CR1, u32SmbusConfig);
    } else {
        CLR_REG32_BIT(I2Cx->CR1, u32SmbusConfig);
    }
}

/**
 * @brief I2C SMBUS function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SmbusCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_SMBUS, (uint32_t)enNewState << I2C_CR1_SMBUS_POS);
}

/**
 * @brief I2C digital filter function configuration
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32FilterClock       Chose the digital filter clock, @ref I2C_Digital_Filter_Clock
 * @retval None
 */
void I2C_DigitalFilterConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32FilterClock)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_DIG_FILTER_CLK(u32FilterClock));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_DNF, u32FilterClock);
}

/**
 * @brief I2C digital filter command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_DigitalFilterCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_DNFEN, (uint32_t)enNewState << I2C_FLTR_DNFEN_POS);
}

/**
 * @brief I2C analog filter function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_AnalogFilterCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_ANFEN, (uint32_t)enNewState << I2C_FLTR_ANFEN_POS);
}

/**
 * @brief I2C general call command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_GeneralCallCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    MODIFY_REG32(I2Cx->CR1, I2C_CR1_ENGC, (uint32_t)enNewState << I2C_CR1_ENGC_POS);
}

/**
 * @brief I2C flags status get
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32Flag              Specify the flags to check, This parameter can be any combination of the member from
 *                                  @ref I2C_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t I2C_GetStatus(const CM_I2C_TypeDef *I2Cx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_FLAG(u32Flag));

    return ((0UL != READ_REG32_BIT(I2Cx->SR, u32Flag)) ? SET : RESET);
}

/**
 * @brief Clear I2C flags
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32Flag              Specifies the flag to clear, This parameter can be any combination of the member from
 *                                  @ref I2C_Flag_Clear
 * @retval None
 */
void I2C_ClearStatus(CM_I2C_TypeDef *I2Cx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_CLR_FLAG(u32Flag));

    WRITE_REG32(I2Cx->CLR, u32Flag);
}

/**
 * @brief I2C FIFO function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_FIFO_Cmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    MODIFY_REG32(I2Cx->FSTR, I2C_FSTR_FEN, (uint32_t)enNewState << I2C_FSTR_FEN_POS);
}

/**
 * @brief I2C Get Transfer FIFO data number
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval uint32_t                 The transfer FIFO data number
 */
uint32_t I2C_FIFO_GetTxDataNum(const CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    return ((READ_REG32_BIT(I2Cx->SR, I2C_SR_TFST) >> I2C_SR_TFST_POS));
}

/**
 * @brief I2C get receive FIFO data status
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval uint32_t                 The FIFO data status @ref I2C_FIFO_Data_Status
 */
uint32_t I2C_FIFO_GetRxDataStatus(const CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    return ((READ_REG32_BIT(I2Cx->FSTR, I2C_FSTR_RFST) >> I2C_FSTR_RFST_POS));
}

/**
 * @brief I2C get transfer FIFO data status
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval uint32_t                 The FIFO data status @ref I2C_FIFO_Data_Status
 */
uint32_t I2C_FIFO_GetTxDataStatus(const CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    return ((READ_REG32_BIT(I2Cx->FSTR, I2C_FSTR_TFST) >> I2C_FSTR_TFST_POS));
}

/**
 * @brief I2C FIFO NACK reset transfer FIFO function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_FIFO_NackResetFIFOCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    MODIFY_REG32(I2Cx->FSTR, I2C_FSTR_NACKTFFLUSH, (uint32_t)enNewState << I2C_FSTR_NACKTFFLUSH_POS);
}

/**
 * @brief I2C flush transfer FIFO
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval None
 */
void I2C_FIFO_TxFlush(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->FSTR, I2C_FSTR_TFFLUSH);
    CLR_REG32_BIT(I2Cx->FSTR, I2C_FSTR_TFFLUSH);
}

/**
 * @brief I2C flush receive FIFO
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval None
 */
void I2C_FIFO_RxFlush(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->FSTR, I2C_FSTR_RFFLUSH);
    CLR_REG32_BIT(I2Cx->FSTR, I2C_FSTR_RFFLUSH);
}

/**
 * @brief I2C Bus free clear function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_BusFreeClearCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    MODIFY_REG32(I2Cx->CR4, I2C_CR4_BUSFREECLREN, (uint32_t)enNewState << I2C_CR4_BUSFREECLREN_POS);
}

/**
 * @brief I2C software reset function command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SWResetCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_SWRST, (uint32_t)enNewState << I2C_CR1_SWRST_POS);
}

/**
 * @brief I2C interrupt command
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32IntType           Specifies the I2C interrupts @ref I2C_Int_Flag
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_IntCmd(CM_I2C_TypeDef *I2Cx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(I2Cx->CR2, u32IntType);
    } else {
        CLR_REG32_BIT(I2Cx->CR2, u32IntType);
    }
}

/**
 * @brief I2C send data
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u8Data               The data to be send
 * @retval None
 */
void I2C_WriteData(CM_I2C_TypeDef *I2Cx, uint8_t u8Data)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    WRITE_REG8(I2Cx->DTR, u8Data);
}

/**
 * @brief I2C read data from register
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @retval uint8_t                  The value of the received data
 */
uint8_t I2C_ReadData(const CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    return READ_REG8(I2Cx->DRR);
}

/**
 * @brief I2C ACK status configuration
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32AckConfig         I2C ACK configure. @ref I2C_Ack_Config
 * @retval None
 */
void I2C_AckConfig(CM_I2C_TypeDef *I2Cx, uint32_t u32AckConfig)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_ACK_CONFIG(u32AckConfig));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_ACK, u32AckConfig);
}

/**
 * @brief I2C SCL high level timeout configuration
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u16TimeoutH          Clock timeout period for high level
 * @retval None
 */
void I2C_SCLHighTimeoutConfig(CM_I2C_TypeDef *I2Cx, uint16_t u16TimeoutH)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    MODIFY_REG32(I2Cx->SLTR, I2C_SLTR_TOUTHIGH, (uint32_t)u16TimeoutH << I2C_SLTR_TOUTHIGH_POS);
}

/**
 * @brief I2C SCL low level timeout configuration
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u16TimeoutL          Clock timeout period for low level
 * @retval None
 */
void I2C_SCLLowTimeoutConfig(CM_I2C_TypeDef *I2Cx, uint16_t u16TimeoutL)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    MODIFY_REG32(I2Cx->SLTR, I2C_SLTR_TOUTLOW, u16TimeoutL);
}

/**
 * @brief Enable or disable I2C SCL high level timeout function
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SCLHighTimeoutCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_HTMOUT);
    } else {
        CLR_REG32_BIT(I2Cx->CR3, I2C_CR3_HTMOUT);
    }
}

/**
 * @brief Enable or disable I2C SCL low level timeout function
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SCLLowTimeoutCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_LTMOUT);
    } else {
        CLR_REG32_BIT(I2Cx->CR3, I2C_CR3_LTMOUT);
    }
}

/**
 * @brief Enable or disable I2C SCL timeout function
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void I2C_SCLTimeoutCmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_TMOUTEN);
    } else {
        CLR_REG32_BIT(I2Cx->CR3, I2C_CR3_TMOUTEN);
    }
}

/**
 * @brief I2Cx start
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 */
int32_t I2C_Start(CM_I2C_TypeDef *I2Cx, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_BUSY, RESET, u32Timeout);

    if (LL_OK == i32Ret) {
        /* generate start signal */
        I2C_GenerateStart(I2Cx);
        /* Judge if start success*/
        i32Ret = I2C_WaitStatus(I2Cx, (I2C_FLAG_BUSY | I2C_FLAG_START), SET, u32Timeout);
    }

    return i32Ret;
}

/**
 * @brief I2Cx restart
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 */
int32_t I2C_Restart(CM_I2C_TypeDef *I2Cx, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_BUSY, SET, u32Timeout);

    if (LL_OK == i32Ret) {
        /* Clear start status flag */
        I2C_ClearStatus(I2Cx, I2C_FLAG_CLR_START);
        /* Send restart condition */
        I2C_GenerateRestart(I2Cx);
        /* Judge if start success*/
        i32Ret = I2C_WaitStatus(I2Cx, (I2C_FLAG_BUSY | I2C_FLAG_START), SET, u32Timeout);
    }

    return i32Ret;
}

/**
 * @brief I2Cx send address
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u16Addr              The address to be sent
 * @param [in] u8Dir                Transfer direction, @ref I2C_Trans_Dir
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR:                NACK received
 */
int32_t I2C_TransAddr(CM_I2C_TypeDef *I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_TRANS_DIR(u8Dir));
    DDL_ASSERT(IS_I2C_7BIT_ADDR(u16Addr));

    i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_EMPTY, SET, u32Timeout);

    if (LL_OK == i32Ret) {
        /* Send I2C address */
        I2C_WriteData(I2Cx, (uint8_t)(u16Addr << 1U) | u8Dir);

        if (I2C_DIR_TX == u8Dir) {
            /* If in master transfer process, Need wait transfer end */
            i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_CPLT, SET, u32Timeout);
        } else {
            /* If in master receive process, wait I2C_FLAG_TRA changed to receive */
            i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TRA, RESET, u32Timeout);
        }

        if (i32Ret == LL_OK) {
            if (I2C_GetStatus(I2Cx, I2C_FLAG_NACKF) == SET) {
                i32Ret = LL_ERR;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief I2Cx send 10 bit address
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u16Addr              The address to be sent
 * @param [in] u8Dir                Transfer direction @ref I2C_Trans_Dir
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR:                NACK received
 */
int32_t I2C_Trans10BitAddr(CM_I2C_TypeDef *I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_TRANS_DIR(u8Dir));
    DDL_ASSERT(IS_I2C_10BIT_ADDR(u16Addr));

    i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_EMPTY, SET, u32Timeout);

    if (LL_OK == i32Ret) {
        /* Write 11110 + SLA(bit9:8) + W#(1bit) */
        I2C_WriteData(I2Cx, (uint8_t)((u16Addr >> 7U) & 0x06U) | 0xF0U | I2C_DIR_TX);
        i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_CPLT, SET, u32Timeout);

        if (LL_OK == i32Ret) {
            /* If receive ACK */
            if (I2C_GetStatus(I2Cx, I2C_FLAG_NACKF) == RESET) {
                /* Write SLA(bit7:0)*/
                I2C_WriteData(I2Cx, (uint8_t)(u16Addr & 0xFFU));
                i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_CPLT, SET, u32Timeout);

                if (LL_OK == i32Ret) {
                    if (I2C_GetStatus(I2Cx, I2C_FLAG_NACKF) == SET) {
                        i32Ret = LL_ERR;
                    }
                }
            } else {
                i32Ret = LL_ERR;
            }
        }
    }

    if ((u8Dir == I2C_DIR_RX) && (LL_OK == i32Ret)) {
        /* Restart */
        I2C_ClearStatus(I2Cx, I2C_FLAG_CLR_START);
        I2C_GenerateRestart(I2Cx);
        i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_START, SET, u32Timeout);

        if (LL_OK == i32Ret) {
            /* Write 11110 + SLA(bit9:8) + R(1bit) */
            I2C_WriteData(I2Cx, (uint8_t)((u16Addr >> 7U) & 0x06U) | 0xF0U | I2C_DIR_RX);
            /* If in master receive process, Need wait TRA flag */
            i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TRA, RESET, u32Timeout);

            if (LL_OK == i32Ret) {
                /* If receive NACK */
                if (I2C_GetStatus(I2Cx, I2C_FLAG_NACKF) == SET) {
                    i32Ret = LL_ERR;
                }
            }
        }
    }

    return i32Ret;
}

/**
 * @brief I2Cx send data
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] au8TxData            The data array to be sent
 * @param [in] u32Size              Number of data in array pau8TxData
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t I2C_TransData(CM_I2C_TypeDef *I2Cx, uint8_t const au8TxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32Count = 0UL;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    if (au8TxData != NULL) {
        while ((u32Count != u32Size) && (i32Ret == LL_OK)) {
            /* Wait tx buffer empty */
            i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_EMPTY, SET, u32Timeout);

            if (i32Ret == LL_OK) {
                /* Send one byte data */
                I2C_WriteData(I2Cx, au8TxData[u32Count]);

                /* Wait transfer end */
                i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_CPLT, SET, u32Timeout);

                /* If receive NACK */
                if (I2C_GetStatus(I2Cx, I2C_FLAG_NACKF) == SET) {
                    break;
                }
                u32Count++;
            }
        }
    } else {
        i32Ret = LL_ERR_INVD_PARAM;
    }

    return i32Ret;
}

/**
 * @brief I2Cx receive data
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [out] au8RxData           Array to hold the received data
 * @param [in] u32Size              Number of data to be received
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t I2C_ReceiveData(CM_I2C_TypeDef *I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_OK;
    uint32_t i;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    if (au8RxData != NULL) {
        uint32_t u32FastAckDis = READ_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);
        for (i = 0UL; i < u32Size; i++) {
            i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_RX_FULL, SET, u32Timeout);

            if (0UL == u32FastAckDis) {
                if ((u32Size >= 2UL) && (i == (u32Size - 2UL))) {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            } else {
                if (i != (u32Size - 1UL)) {
                    I2C_AckConfig(I2Cx, I2C_ACK);
                } else {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            }

            if (i32Ret == LL_OK) {
                /* read data from register */
                au8RxData[i] = I2C_ReadData(I2Cx);
            } else {
                break;
            }
        }
        I2C_AckConfig(I2Cx, I2C_ACK);
    } else {
        i32Ret = LL_ERR_INVD_PARAM;
    }

    return i32Ret;
}

/**
 * @brief I2Cx receive data and stop(for master)
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *        @arg CM_I2C or CM_I2Cx:   I2C instance register base.
 * @param [out] au8RxData           Array to hold the received data
 * @param [in] u32Size              Number of data to be received
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t I2C_MasterReceiveDataAndStop(CM_I2C_TypeDef *I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_OK;
    uint32_t i;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    if (au8RxData != NULL) {
        uint32_t u32FastAckDis = READ_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);

        for (i = 0UL; i < u32Size; i++) {
            i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_RX_FULL, SET, u32Timeout);

            if (0UL == u32FastAckDis) {
                if ((u32Size >= 2UL) && (i == (u32Size - 2UL))) {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            } else {
                if (i != (u32Size - 1UL)) {
                    I2C_AckConfig(I2Cx, I2C_ACK);
                } else {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            }

            if (i32Ret == LL_OK) {
                /* Stop before read last data */
                if (i == (u32Size - 1UL)) {
                    I2C_ClearStatus(I2Cx, I2C_FLAG_CLR_STOP);
                    I2C_GenerateStop(I2Cx);
                }
                /* read data from register */
                au8RxData[i] = I2C_ReadData(I2Cx);

                if (i == (u32Size - 1UL)) {
                    /* Wait stop flag after DRR read */
                    i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_STOP, SET, u32Timeout);
                }
            } else {
                break;
            }
        }
        I2C_AckConfig(I2Cx, I2C_ACK);
    } else {
        i32Ret = LL_ERR_INVD_PARAM;
    }

    return i32Ret;
}

/**
 * @brief I2Cx stop
 * @param [in] I2Cx                 Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C or CM_I2Cx:  I2C instance register base.
 * @param [in] u32Timeout           Maximum count of trying to get a status of a flag in status register
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 */
int32_t I2C_Stop(CM_I2C_TypeDef *I2Cx, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    /* Clear stop flag */
    while ((SET == I2C_GetStatus(I2Cx, I2C_FLAG_STOP)) && (u32Timeout > 0UL)) {
        I2C_ClearStatus(I2Cx, I2C_FLAG_CLR_STOP);
        u32Timeout--;
    }
    I2C_GenerateStop(I2Cx);
    /* Wait stop flag */
    i32Ret = I2C_WaitStatus(I2Cx, I2C_FLAG_STOP, SET, u32Timeout);

    return i32Ret;
}

/**
 * @brief Initialize structure stc_i2c_init_t variable with default value.
 * @param [out] pstcI2cInit             Pointer to a stc_i2c_init_t structure variable which will be initialized.
 *                                      @ref stc_i2c_init_t.
 * @retval int32_t
 *         - LL_OK:                     Success
 *         - LL_ERR_INVD_PARAM:         Parameter error
 */
int32_t I2C_StructInit(stc_i2c_init_t *pstcI2cInit)
{
    int32_t i32Ret = LL_OK;
    if (pstcI2cInit == NULL) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcI2cInit->u32Baudrate = 50000UL;
        pstcI2cInit->u32SclTime = 0UL;
        pstcI2cInit->u32ClockDiv = I2C_CLK_DIV1;
    }

    return i32Ret;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
