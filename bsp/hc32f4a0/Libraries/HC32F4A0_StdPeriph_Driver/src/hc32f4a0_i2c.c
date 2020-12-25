/**
 *******************************************************************************
 * @file  hc32f4a0_i2c.c
 * @brief This file provides firmware functions to manage the Inter-Integrated
 *        Circuit(I2C).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hexiao          First version
   2020-07-15       Hexiao          Modify I2C_SmBusCmd to I2C_SetMode
   2020-08-31       Hexiao          Refine I2C_Init/I2C_SendData/I2C_RcvData
   2020-09-15       Hexiao          Modify I2C_RcvData for manually ack and nack
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_i2c.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_I2C I2C
 * @brief I2C Driver Library
 * @{
 */

#if (DDL_I2C_ENABLE == DDL_ON)

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

#define I2C_CLR_MASK                       (0x00F052DFUL)
#define I2C_INT_MASK                       (0x00F052DFUL)
#define I2C_SCL_HIGHT_LOW_LVL_SUM_MAX      ((float32_t)0x1F*(float32_t)2)


/**
 * @defgroup I2C_Check_Parameters_Validity I2C Check Parameters Validity
 * @{
 */
#define IS_VALID_UNIT(x)                                                       \
(   ((x) == M4_I2C1)                               ||                          \
    ((x) == M4_I2C2)                               ||                          \
    ((x) == M4_I2C3)                               ||                          \
    ((x) == M4_I2C4)                               ||                          \
    ((x) == M4_I2C5)                               ||                          \
    ((x) == M4_I2C6))

#define IS_VALID_MODE(x)                                                       \
(   ((x) == I2C_MODE_I2C)                          ||                          \
    ((x) == I2C_MODE_SMBUS))

#define IS_VALID_CLEARBIT(x)       ((0U != (x)) && (0U == ((x) & (~I2C_CLR_MASK))))

#define IS_VALID_INT(x)            ((0U != (x)) && (0U == ((x) & (~I2C_INT_MASK))))

#define IS_VALID_SPEED(speed)      ((0U != (speed)) && ((speed) <= (I2C_BAUDRATE_MAX)))

#define IS_VALID_DIGITAL_FILTER(x) ((x) <= I2C_DIG_FILTMODE_4CYCLE)

#define IS_VALID_RD_STATUS_BIT(x)                                              \
(   ((x) == I2C_SR_STARTF)                         ||                          \
    ((x) == I2C_SR_SLADDR0F)                       ||                          \
    ((x) == I2C_SR_SLADDR1F)                       ||                          \
    ((x) == I2C_SR_TENDF)                          ||                          \
    ((x) == I2C_SR_STOPF)                          ||                          \
    ((x) == I2C_SR_RFULLF)                         ||                          \
    ((x) == I2C_SR_TEMPTYF)                        ||                          \
    ((x) == I2C_SR_ARLOF)                          ||                          \
    ((x) == I2C_SR_ACKRF)                          ||                          \
    ((x) == I2C_SR_NACKF)                          ||                          \
    ((x) == I2C_SR_TMOUTF)                         ||                          \
    ((x) == I2C_SR_MSL)                            ||                          \
    ((x) == I2C_SR_BUSY)                           ||                          \
    ((x) == I2C_SR_TRA)                            ||                          \
    ((x) == I2C_SR_GENCALLF)                       ||                          \
    ((x) == I2C_SR_SMBDEFAULTF)                    ||                          \
    ((x) == I2C_SR_SMBHOSTF)                       ||                          \
    ((x) == I2C_SR_SMBALRTF))

#define IS_VALID_SMBUS_CONFIG(x)      ((0U != (x)) &&                          \
                                      (0U == ((x) & (~(uint32_t)I2C_SMBUS_CONFIG_CLEARMASK))))

#define IS_VALID_7BIT_ADDR(x)         ((x) <= 0x7FUL)
#define IS_VALID_10BIT_ADDR(x)        ((x) <= 0x3FFUL)


#define IS_VALID_ADDR_NUM(x)                                                   \
(   ((x) == I2C_ADDR_0)                            ||                          \
    ((x) == I2C_ADDR_1))

#define IS_VALID_CLK_DIV(x)                                                    \
(   ((x) == I2C_CLK_DIV1)                          ||                          \
    ((x) == I2C_CLK_DIV2)                          ||                          \
    ((x) == I2C_CLK_DIV4)                          ||                          \
    ((x) == I2C_CLK_DIV8)                          ||                          \
    ((x) == I2C_CLK_DIV16)                         ||                          \
    ((x) == I2C_CLK_DIV32)                         ||                          \
    ((x) == I2C_CLK_DIV64)                         ||                          \
    ((x) == I2C_CLK_DIV128))

#define IS_VALID_DIR(x)                                                        \
(   ((x) == I2C_DIR_TX)                            ||                          \
    ((x) == I2C_DIR_RX))

#define IS_VALID_ACK_CONFIG(x)                                                 \
(   ((x) == I2C_ACK)                               ||                          \
    ((x) == I2C_NACK))
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
static en_result_t I2C_WaitStatus(const M4_I2C_TypeDef *I2Cx, uint32_t u32Flags, en_flag_status_t enStatus, uint32_t u32Timeout);

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
 * @brief  Set the baudrate for I2C peripheral.
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] pstcI2C_InitStruct   Pointer to I2C configuration structure
 *                                   @ref stc_i2c_init_t
 *         @arg pstcI2C_InitStruct->u32ClkDiv: Division of Pclk3, reference as:
 *              step1: calculate div = (Pclk3/Baudrate/(68+2*dnfsum+SclTime)
 *                     Pclk3 -- system clock
 *                     Baudrate -- baudrate of i2c
 *                     SclTime -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                according to i2c bus hardware parameter.
 *                     dnfsum -- 0 if digital filter off;
 *                               Filter capacity if digital filter on(1 ~ 4)
 *              step2: chose a division item which is similar and bigger than div
 *                     from @ref I2C_Clock_division.
 *         @arg pstcI2C_InitStruct->u32Baudrate : Baudrate configuration
 *         @arg pstcI2C_InitStruct->u32SclTime : Indicate SCL pin rising and
 *              falling time, should be number of T(i2c clock period time)
 * @param  [out] pf32Err               Baudrate error
 * @retval en_result_t
 */
en_result_t I2C_BaudrateConfig(M4_I2C_TypeDef* I2Cx, const stc_i2c_init_t *pstcI2C_InitStruct, float32_t *pf32Err)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    en_result_t enRet = Ok;
    uint32_t u32Pclk3;
    uint32_t I2cDivClk;
    uint32_t SclCnt;
    uint32_t Baudrate;
    uint32_t dnfsum = 0UL;
    uint32_t divsum = 2UL;
    float32_t WidthTotal;
    float32_t SumTotal;
    float32_t WidthHL;
    float32_t fErr = 0.0F;

    if ((NULL == pstcI2C_InitStruct) || (NULL == pf32Err))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_SPEED(pstcI2C_InitStruct->u32Baudrate));
        DDL_ASSERT(IS_VALID_CLK_DIV(pstcI2C_InitStruct->u32ClkDiv));

        /* Get configuration for i2c */
        u32Pclk3 = SystemCoreClock >> ((M4_CMU->SCFGR & CMU_SCFGR_PCLK3S) >> CMU_SCFGR_PCLK3S_POS);
        I2cDivClk = 1UL << pstcI2C_InitStruct->u32ClkDiv;
        SclCnt = pstcI2C_InitStruct->u32SclTime;
        Baudrate = pstcI2C_InitStruct->u32Baudrate;

        /* Judge digital filter status*/
        if(0U != READ_REG32_BIT(I2Cx->FLTR, I2C_FLTR_DNFEN))
        {
            dnfsum = (READ_REG32_BIT(I2Cx->FLTR, I2C_FLTR_DNF) >> I2C_FLTR_DNF_POS) + 1U;
        }

        /* Judge if clock divider on*/
        if(I2C_CLK_DIV1 == I2cDivClk)
        {
            divsum = 3UL;
        }

        WidthTotal = (float32_t)u32Pclk3 / (float32_t)Baudrate / (float32_t)I2cDivClk;
        SumTotal = 2.0F*(float32_t)divsum + 2.0F*(float32_t)dnfsum + (float32_t)SclCnt;
        WidthHL = WidthTotal - SumTotal;

        if(WidthTotal <= SumTotal)
        {
            /* Err, Should set a smaller division value for pstcI2C_InitStruct->u32ClkDiv */
            enRet = ErrorInvalidParameter;
        }
        else if(WidthHL > I2C_SCL_HIGHT_LOW_LVL_SUM_MAX)
        {
            /* Err, Should set a bigger division value for pstcI2C_InitStruct->u32ClkDiv */
            enRet = ErrorInvalidParameter;
        }
        else
        {
            fErr =(WidthHL - (float32_t)((uint32_t)WidthHL)) / WidthHL;
            WRITE_REG32(I2Cx->CCR, (pstcI2C_InitStruct->u32ClkDiv << I2C_CCR_FREQ_POS)     \
                           | (((uint32_t)WidthHL/2U) << I2C_CCR_SLOWW_POS)              \
                           | (((uint32_t)WidthHL - (uint32_t)WidthHL/2U) << I2C_CCR_SHIGHW_POS));
        }
    }

    if((NULL != pf32Err)&&(Ok == enRet))
    {
        *pf32Err = fErr;
    }

    return enRet;
}

/**
 * @brief  De-initialize I2C unit
 * @param  [in] I2Cx   Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval None
 */
void I2C_DeInit(M4_I2C_TypeDef* I2Cx)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    /* Reset peripheral register and internal status*/
    CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);
    SET_REG32_BIT(I2Cx->CR1,I2C_CR1_SWRST);
}

/**
 * @brief  Initialize structure stc_i2c_init_t variable with default value.
 * @param  [out] pstcI2C_InitStruct     Pointer to a stc_i2c_init_t structure variable
 *                                      which will be initialized.
 *   @arg  See the struct @ref stc_i2c_init_t.
 * @retval en_result_t
 */
en_result_t I2C_StructInit(stc_i2c_init_t* pstcI2C_InitStruct)
{
    en_result_t enRet = Ok;

    if (pstcI2C_InitStruct == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcI2C_InitStruct->u32Baudrate = 50000UL;
        pstcI2C_InitStruct->u32ClkDiv = I2C_CLK_DIV1;
        pstcI2C_InitStruct->u32SclTime = 0UL;
    }

    return enRet;
}

/**
 * @brief  Initialize I2C peripheral according to the structure
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] pstcI2C_InitStruct   Pointer to I2C configuration structure
 *                                   @ref stc_i2c_init_t
 *         @arg pstcI2C_InitStruct->u32ClkDiv: Division of Pclk3, reference as:
 *              step1: calculate div = (Pclk3/Baudrate/(68+2*dnfsum+SclTime)
 *                     Pclk3 -- system clock
 *                     Baudrate -- baudrate of i2c
 *                     SclTime -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                according to i2c bus hardware parameter.
 *                     dnfsum -- 0 if digital filter off;
 *                               Filter capacity if digital filter on(1 ~ 4)
 *              step2: chose a division item which is similar and bigger than div
 *                     from @ref I2C_Clock_division.
 *         @arg pstcI2C_InitStruct->u32Baudrate : Baudrate configuration
 *         @arg pstcI2C_InitStruct->u32SclTime : Indicate SCL pin rising and
 *              falling time, should be number of T(i2c clock period time)
 * @param  [out] pf32Err               Baudrate error
 * @retval en_result_t
 */
en_result_t I2C_Init(M4_I2C_TypeDef* I2Cx, const stc_i2c_init_t *pstcI2C_InitStruct, float32_t *pf32Err)
{
    en_result_t enRet;
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    if (NULL == pstcI2C_InitStruct )
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_VALID_SPEED(pstcI2C_InitStruct->u32Baudrate));
        DDL_ASSERT(IS_VALID_CLK_DIV(pstcI2C_InitStruct->u32ClkDiv));

        /* Register and internal status reset */
        CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);
        SET_REG32_BIT(I2Cx->CR1,I2C_CR1_SWRST);
        SET_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);

        /* I2C baudrate config */
        enRet = I2C_BaudrateConfig(I2Cx, pstcI2C_InitStruct, pf32Err);

        if(enRet == Ok)
        {
            /* Disable global broadcast address function */
            CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_ENGC);

            /* Release software reset */
            CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_SWRST);
            /* Disable I2C peripheral */
            CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified I2C slave address function
 * @param  [in] I2Cx                Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32AddrNum           I2C address 0 or address 1 @ref I2C_Address_Num
 *                                   This parameter can be one of the following values:
 *                                   @arg I2C_ADDR_0
 *                                   @arg I2C_ADDR_1
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_SlaveAddrCmd(M4_I2C_TypeDef* I2Cx, uint32_t u32AddrNum, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_ADDR_NUM(u32AddrNum));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    __IO uint32_t* pu32SLRx = (__IO uint32_t*)((uint32_t)&I2Cx->SLR0 + u32AddrNum * 4UL);

    if(Enable == enNewState)
    {
        SET_REG32_BIT(*pu32SLRx, I2C_SLR0_SLADDR0EN);
    }
    else
    {
        CLEAR_REG32_BIT(*pu32SLRx, I2C_SLR0_SLADDR0EN);
    }
}

/**
 * @brief  I2C slave address config
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32AddrNum            I2C address 0 or address 1 @ref I2C_Address_Num
 *                                    This parameter can be one of the following values:
 *                                    @arg I2C_ADDR_0
 *                                    @arg I2C_ADDR_1
 * @param  [in] u32AddrMode           Address mode configuration,@ref  I2C_Addr_Config
 *                                    This parameter can be one of the following values:
 *                                    @arg I2C_ADDR_MODE_7BIT
 *                                    @arg I2C_ADDR_MODE_10BIT
 * @param  [in] u32Addr               The slave address
 * @retval None
 */
void I2C_SlaveAddrConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32Addr)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_ADDR_NUM(u32AddrNum));


    __IO uint32_t* pu32SLRx = (__IO uint32_t*)((uint32_t)&I2Cx->SLR0 + u32AddrNum * 4UL);

    if(I2C_ADDR_MODE_10BIT == u32AddrMode)
    {
        DDL_ASSERT(IS_VALID_10BIT_ADDR(u32Addr));
        MODIFY_REG32(*pu32SLRx, I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0, u32AddrMode + u32Addr);
    }
    else
    {
        DDL_ASSERT(IS_VALID_7BIT_ADDR(u32Addr));
        MODIFY_REG32(*pu32SLRx, I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0, u32AddrMode + (u32Addr << 1));
    }
}

/**
 * @brief  Configure peripheral mode
 * @param  [in] I2Cx   Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32Mode This parameter can be one of the following values:
 *         @arg I2C_MODE_I2C
 *         @arg I2C_MODE_SMBUS
 * @retval None
 */
void I2C_SetMode(M4_I2C_TypeDef* I2Cx, uint32_t u32Mode)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_MODE(u32Mode));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_SMBUS, u32Mode);
}

/**
 * @brief  Enable or disable the specified I2C peripheral
 * @param  [in] I2Cx                Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_Cmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_PE, (uint32_t)enNewState << I2C_CR1_PE_POS);
}

/**
 * @brief Enable or disable the I2C fast ack function
 * @param  [in] I2Cx           Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param [in] enNewState      New state of the fast ACK function, can be
 *                             Disable or Enable the function
 * @retval None
 */
void I2C_FastAckCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);
    }
    else
    {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);
    }
}

/**
 * @brief Enable or disable the bus wait function
 * @param  [in] I2Cx           Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param [in] enNewState      New state of the bus wait function, can be
 *                             Disable or Enable the function
 * @retval None
 */
void I2C_BusWaitCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    uint32_t u32CR4_Reg = ((uint32_t)&I2Cx->CR3) + 4UL;
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        *(__IO uint32_t *)u32CR4_Reg |= (1UL << 10UL);
    }
    else
    {
        *(__IO uint32_t *)u32CR4_Reg &= ~(1UL << 10UL);
    }
}

/**
 * @brief  I2C SCL high level timeout configuration
 * @param  [in] I2Cx       Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param [in] u16TimeoutH  clock timeout period for high level
 * @retval None
 */
void I2C_ClkHighTimeoutConfig(M4_I2C_TypeDef* I2Cx, uint16_t u16TimeoutH)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    CLEAR_REG32_BIT(I2Cx->SLTR, I2C_SLTR_TOUTHIGH);
    SET_REG32_BIT(I2Cx->SLTR, ((uint32_t)u16TimeoutH << 16U));
}

/**
 * @brief  I2C SCL low level timeout configuration
 * @param  [in] I2Cx       Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param [in] u16TimeoutL  clock timeout period for low level
 * @retval None
 */
void I2C_ClkLowTimeoutConfig(M4_I2C_TypeDef* I2Cx, uint16_t u16TimeoutL)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    CLEAR_REG32_BIT(I2Cx->SLTR, I2C_SLTR_TOUTLOW);
    SET_REG32_BIT(I2Cx->SLTR, u16TimeoutL);
}

/**
 * @brief  Enable or disable I2C SCL high level timeout function
 * @param  [in] I2Cx       Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param [in] enNewState  New state of the I2C SCL high level timeout function,
 *                         can be Disable or Enable the function
 * @retval None
 */
void I2C_ClkHighTimeoutCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_HTMOUT);
    }
    else
    {
        CLEAR_REG32_BIT(I2Cx->CR3, I2C_CR3_HTMOUT);
    }
}

/**
 * @brief  Enable or disable I2C SCL low level timeout function
 * @param  [in] I2Cx       Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param [in] enNewState  New state of the I2C SCL low level timeout function
 *                         can be Disable or Enable the function
 * @retval None
 */
void I2C_ClkLowTimeoutCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_LTMOUT);
    }
    else
    {
        CLEAR_REG32_BIT(I2Cx->CR3, I2C_CR3_LTMOUT);
    }
}

/**
 * @brief  Enable or disable I2C SCL timeout function
 * @param  [in] I2Cx      Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param [in] enNewState New state of the I2C SCL timeout function, can be
 *                        Disable or Enable the function
 * @retval None
 */
void I2C_ClkTimeoutCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(I2Cx->CR3, I2C_CR3_TMOUTEN);
    }
    else
    {
        CLEAR_REG32_BIT(I2Cx->CR3, I2C_CR3_TMOUTEN);
    }
}

/**
 * @brief  Config I2C SMBUS address match function
 * @param  [in] I2Cx                    Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32SmbusConfig          Indicate the SMBUS address match function configuration.
 *         This parameter can be one or any combination of the following values:
 *         @ref I2C_Smbus_Match_Cfg
 *         @arg I2C_SMBUS_MATCH_ALRT    : Smbus alarm address
 *         @arg I2C_SMBUS_MATCH_DEFAULT : Smbus default address
 *         @arg I2C_SMBUS_MATCH_HOST    : Smbus host address address
 * @param  [in] enNewState              New state of the I2Cx SMBUS match config,
 *                                      @ref en_functional_state_t
 * @retval None
 */
void I2C_SmbusConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32SmbusConfig, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_SMBUS_CONFIG(u32SmbusConfig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(I2Cx->CR1, u32SmbusConfig);
    }
    else
    {
        CLEAR_REG32_BIT(I2Cx->CR1, u32SmbusConfig);
    }
}

/**
 * @brief  Config I2C digital filter mode
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32DigFilterMode     Chose the digital filter mode,
 *         @ref I2C_Digital_Filter_mode
 *         This parameter can be one of the following values:
 *         @arg I2C_DIG_FILTMODE_1CYCLE
 *         @arg I2C_DIG_FILTMODE_2CYCLE
 *         @arg I2C_DIG_FILTMODE_3CYCLE
 *         @arg I2C_DIG_FILTMODE_4CYCLE
 * @retval None
 */
void I2C_DigitalFilterConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32DigFilterMode)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_DIGITAL_FILTER(u32DigFilterMode));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_DNF, u32DigFilterMode);
}

/**
 * @brief  Enable or disable I2C digital filter function
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_DigitalFilterCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_DNFEN, (uint32_t)enNewState << I2C_FLTR_DNFEN_POS);
}

/**
 * @brief  Enable or disable I2C analog filter function
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_AnalogFilterCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_ANFEN, (uint32_t)enNewState << I2C_FLTR_ANFEN_POS);
}

/**
 * @brief  Enable or disable I2C general call function
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_GeneralCallCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_ENGC, (uint32_t)enNewState << I2C_CR1_ENGC_POS);
}

/**
 * @brief  Generate I2Cx communication start condition
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval None
 */
void I2C_GenerateStart(M4_I2C_TypeDef* I2Cx)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_START);
}

/**
 * @brief  Generate I2Cx communication restart condition
 * @param  [in] I2Cx                  Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval None
 */
void I2C_GenerateReStart(M4_I2C_TypeDef* I2Cx)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_RESTART);
}

/**
 * @brief  Generate I2Cx communication stop condition
 * @param  [in] I2Cx                  Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval None
 */
void I2C_GenerateStop(M4_I2C_TypeDef* I2Cx)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_STOP);
}

/**
 * @brief  Check whether the specified I2C flag is set or not
 * @param  [in] I2Cx                  Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32StatusBit         specify the flag to check,
 *         This parameter can be one of the following values:
 *         @arg   I2C_SR_STARTF     : Start condition detected flag
 *         @arg   I2C_SR_SLADDR0F   : Address 0 detected flag
 *         @arg   I2C_SR_SLADDR1F   : Address 1 detected flag
 *         @arg   I2C_SR_TENDF      : Transfer end flag
 *         @arg   I2C_SR_STOPF      : Stop condition detected flag
 *         @arg   I2C_SR_RFULLF     : Receive buffer full flag
 *         @arg   I2C_SR_TEMPTYF    : Transfer buffer empty flag
 *         @arg   I2C_SR_ARLOF      : Arbitration fails flag
 *         @arg   I2C_SR_ACKRF      : ACK detected flag
 *         @arg   I2C_SR_NACKF      : NACK detected flag
 *         @arg   I2C_SR_TMOUTF     : Time out detected flag
 *         @arg   I2C_SR_MSL        : Master mode flag
 *         @arg   I2C_SR_BUSY       : Bus busy status flag
 *         @arg   I2C_SR_TRA        : Transfer mode flag
 *         @arg   I2C_SR_GENCALLF   : General call detected flag
 *         @arg   I2C_SR_SMBDEFAULTF: Smbus default address detected flag
 *         @arg   I2C_SR_SMBHOSTF   : Smbus host address detected flag
 *         @arg   I2C_SR_SMBALRTF   : Smbus alarm address detected flag
 * @retval The status of the I2C status flag, may be Set or Reset.
 */
en_flag_status_t I2C_GetStatus(const M4_I2C_TypeDef *I2Cx, uint32_t u32StatusBit)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_RD_STATUS_BIT(u32StatusBit));

    return ((0UL != READ_REG32_BIT(I2Cx->SR, u32StatusBit)) ? Set : Reset);
}

/**
 * @brief  Clear I2C status flag
 * @param  [in] I2Cx                  Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32StatusBit          Specify the flag to clear,
 *         This parameter can be any combination of the following values:
 *         @arg  I2C_CLR_STARTFCLR     : Start flag clear
 *         @arg  I2C_CLR_SLADDR0FCLR   : Address 0 detected flag clear
 *         @arg  I2C_CLR_SLADDR1FCLR   : Address 1 detected flag clear
 *         @arg  I2C_CLR_TENDFCLR      : Transfer end flag clear
 *         @arg  I2C_CLR_STOPFCLR      : Stop flag clear
 *         @arg  I2C_CLR_RFULLFCLR     : Receive buffer full flag clear
 *         @arg  I2C_CLR_TEMPTYFCLR    : Transfer buffer empty flag clear
 *         @arg  I2C_CLR_ARLOFCLR      : Arbitration fails flag clear
 *         @arg  I2C_CLR_NACKFCLR      : NACK detected flag clear
 *         @arg  I2C_CLR_TMOUTFCLR     : Time out detected flag clear
 *         @arg  I2C_CLR_GENCALLFCLR   : General call address detected flag clear
 *         @arg  I2C_CLR_SMBDEFAULTFCLR: Smbus default address detected flag clear
 *         @arg  I2C_CLR_SMBHOSTFCLR   : Smbus host address detected flag clear
 *         @arg  I2C_CLR_SMBALRTFCLR   : Smbus alarm address detected flag clear
 * @retval None
 */
void I2C_ClearStatus(M4_I2C_TypeDef* I2Cx, uint32_t u32StatusBit)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_CLEARBIT(u32StatusBit));

    WRITE_REG32(I2Cx->CLR,u32StatusBit);
}

/**
 * @brief  I2C software reset function command
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_SoftwareResetCmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_SWRST, (uint32_t)enNewState << I2C_CR1_SWRST_POS);
}

/**
 * @brief  Enable or disable the specified I2C interrupts
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32IntEn   Specify the I2C interrupts sources to be configuration.
 *         This parameter can be any combination of the following values:
 *         @arg    I2C_CR2_STARTIE      : Start flag interrupt
 *         @arg    I2C_CR2_SLADDR0IE    : Address 0 detected interrupt
 *         @arg    I2C_CR2_SLADDR1IE    : Address 1 detected interrupt
 *         @arg    I2C_CR2_TENDIE       : Transfer end interrupt
 *         @arg    I2C_CR2_STOPIE       : Stop flag interrupt
 *         @arg    I2C_CR2_RFULLIE      : Receive buffer full interrupt
 *         @arg    I2C_CR2_TEMPTYIE     : Transfer buffer empty interrupt
 *         @arg    I2C_CR2_ARLOIE       : Arbitration fails interrupt
 *         @arg    I2C_CR2_NACKIE       : NACK flag detected interrupt
 *         @arg    I2C_CR2_TMOUTIE      : Time out detected interrupt
 *         @arg    I2C_CR2_GENCALLIE    : General call address detected interrupt
 *         @arg    I2C_CR2_SMBDEFAULTIE : Smbus default address detected interrupt
 *         @arg    I2C_CR2_SMBHOSTIE    : Smbus host address detected interrupt
 *         @arg    I2C_CR2_SMBALRTIE    : Smbus alarm address detected interrupt
 * @param  [in] enNewState           New state of the I2Cx interrupt function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_IntCmd(M4_I2C_TypeDef* I2Cx, uint32_t u32IntEn, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_INT(u32IntEn));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(I2Cx->CR2, u32IntEn);
    }
    else
    {
        CLEAR_REG32_BIT(I2Cx->CR2, u32IntEn);
    }
}

/**
 * @brief  Send data byte
 * @param  [in] I2Cx                 Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u8Data               The data to be send
 * @retval None
 */
void I2C_WriteDataReg(M4_I2C_TypeDef* I2Cx, uint8_t u8Data)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    WRITE_REG8(I2Cx->DTR, u8Data);
}

/**
 * @brief  Read the most recent received data byte
 * @param  [in] I2Cx   Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval The value of the received data
 */
uint8_t I2C_ReadDataReg(const M4_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    return READ_REG8(I2Cx->DRR);
}

/**
 * @brief  Config I2C ACK status
 * @param  [in] I2Cx                Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32AckConfig        Ack configuration
 *         This parameter can be one of the following values:
 *         @arg I2C_ACK
 *         @arg I2C_NACK
 * @retval None
 */
void I2C_AckConfig(M4_I2C_TypeDef* I2Cx, uint32_t u32AckConfig)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_ACK_CONFIG(u32AckConfig));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_ACK, u32AckConfig);
}

/**
 * @brief  I2Cx Start
 * @param  [in] I2Cx   Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in]  u32Timeout  Maximum count of trying to get a status of a
 *              flag in status register
 * @retval An en_result_t enumeration value:
 *            - Ok: Start successfully
 *            - Error: Start unsuccessfully
 */
en_result_t I2C_Start(M4_I2C_TypeDef* I2Cx, uint32_t u32Timeout)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    en_result_t enRet;

    enRet = I2C_WaitStatus(I2Cx, I2C_SR_BUSY, Reset, u32Timeout);

    if(Ok == enRet)
    {
        /* generate start signal */
        I2C_GenerateStart(I2Cx);
        /* Judge if start success*/
        enRet = I2C_WaitStatus(I2Cx, (I2C_SR_BUSY | I2C_SR_STARTF), Set, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  I2Cx Restart
 * @param  [in] I2Cx         Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32Timeout  Maximum count of trying to get a status of a
 *              flag in status register
 * @retval An en_result_t enumeration value:
 *            - Ok: Restart successfully
 *            - Error: Restart unsuccessfully
 */
en_result_t I2C_Restart(M4_I2C_TypeDef* I2Cx, uint32_t u32Timeout)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    en_result_t enRet;

    /* Clear start status flag */
    I2C_ClearStatus(I2Cx, I2C_CLR_STARTFCLR);
    /* Send restart condition */
    I2C_GenerateReStart(I2Cx);
    /* Judge if start success*/
    enRet = I2C_WaitStatus(I2Cx, (I2C_SR_BUSY | I2C_SR_STARTF), Set, u32Timeout);

    return enRet;
}

/**
 * @brief  Send 7bit address
 * @param  [in] I2Cx         Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u8Addr       The address to be sent
 * @param  [in] u8Dir        Transfer direction,
 *                           This parameter can be one of the following values:
 *                           @arg I2C_DIR_TX
 *                           @arg I2C_DIR_RX
 * @param  [in] u32Timeout   Maximum count of trying to get a status of a
 *              flag in status register
 * @retval An en_result_t enumeration value:
 *            - Ok: Send successfully
 *            - Error: Send unsuccessfully or NACK received
 */
en_result_t I2C_TransAddr(M4_I2C_TypeDef* I2Cx, uint8_t u8Addr, uint8_t u8Dir, uint32_t u32Timeout)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_7BIT_ADDR(u8Addr));
    DDL_ASSERT(IS_VALID_DIR(u8Dir));

    en_result_t enRet;

    enRet = I2C_WaitStatus(I2Cx, I2C_SR_TEMPTYF, Set, u32Timeout);

    if(Ok == enRet)
    {
        /* Send I2C address */
        I2C_WriteDataReg(I2Cx, (uint8_t)(u8Addr << 1U) | u8Dir);

        if(I2C_DIR_TX == u8Dir)
        {
            /* If in master transfer process, wait transfer end */
            enRet = I2C_WaitStatus(I2Cx, I2C_SR_TENDF, Set, u32Timeout);
        }
        else
        {
            /* If in master recevie process, wait I2C_SR_TRA changed to recevie */
            enRet = I2C_WaitStatus(I2Cx, I2C_SR_TRA, Reset, u32Timeout);
        }

         /* If receive NACK*/
        if(enRet == Ok)
        {
            if(I2C_GetStatus(I2Cx, I2C_SR_ACKRF) == Set)
            {
                enRet = Error;
            }
        }
    }

    return enRet;
}


/**
* @brief  Send 10bit Address
* @param  [in] I2Cx          Pointer to the I2C peripheral register
*         This parameter can be one of the following values:
*         @arg M4_I2C1
*         @arg M4_I2C2
*         @arg M4_I2C3
*         @arg M4_I2C4
*         @arg M4_I2C5
*         @arg M4_I2C6
* @param  [in] u16Addr       The address to be sent
* @param  [in] u8Dir         Transfer direction,
*         This parameter can be one of the following values:
*         @arg  I2C_DIR_TX
*         @arg  I2C_DIR_RX
* @param  [in]  u32Timeout   Maximum count of trying to get a status of a
*              flag in status register
* @retval An en_result_t enumeration value:
*            - Ok: Send successfully
*            - Error: Send unsuccessfully or NACK received
*/
en_result_t I2C_Trans10BitAddr(M4_I2C_TypeDef* I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));
    DDL_ASSERT(IS_VALID_10BIT_ADDR(u16Addr));
    DDL_ASSERT(IS_VALID_DIR(u8Dir));

    en_result_t enRet;
    enRet = I2C_WaitStatus(I2Cx, I2C_SR_TEMPTYF, Set, u32Timeout);
    if(Ok == enRet)
    {
        /* Write 11110 + SLA(bit9:8) + W#(1bit) */
        I2C_WriteDataReg(I2Cx, (uint8_t)((u16Addr>>7U) & 0x06U) | 0xF0U | I2C_DIR_TX);
        enRet = I2C_WaitStatus(I2Cx, I2C_SR_TENDF, Set, u32Timeout);

        if(Ok == enRet)
        {
            /* If receive ACK */
            if(I2C_GetStatus(I2Cx, I2C_SR_ACKRF) == Reset)
            {
                /* Write SLA(bit7:0)*/
                I2C_WriteDataReg(I2Cx, (uint8_t)(u16Addr & 0xFFU));
                enRet = I2C_WaitStatus(I2Cx, I2C_SR_TENDF, Set, u32Timeout);

                if(Ok == enRet)
                {
                    if(I2C_GetStatus(I2Cx, I2C_SR_ACKRF) != Reset)
                    {
                        enRet = Error;
                    }
                }
            }
            else
            {
                enRet = Error;
            }
        }
    }

    if((u8Dir == I2C_DIR_RX) && (Ok == enRet))
    {
        /* Restart */
        I2C_ClearStatus(I2Cx, I2C_CLR_STARTFCLR);
        I2C_GenerateReStart(I2Cx);
        enRet = I2C_WaitStatus(I2Cx, I2C_SR_STARTF, Set, u32Timeout);

        if(Ok == enRet)
        {
            /* Write 11110 + SLA(bit9:8) + R(1bit) */
            I2C_WriteDataReg(I2Cx, (uint8_t)((u16Addr>>7U) & 0x06U) | 0xF0U | I2C_DIR_RX);
            /* If in master receive process, Need wait TRA flag */
            enRet = I2C_WaitStatus(I2Cx, I2C_SR_TRA, Reset, u32Timeout);

            if(Ok == enRet)
            {
                /* If receive NACK */
                if(I2C_GetStatus(I2Cx, I2C_SR_ACKRF) != Reset)
                {
                    enRet = Error;
                }
            }
        }
    }

    return enRet;
}

/**
 * @brief  Send data bytes
 * @param  [in] I2Cx           Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] pau8TxData     The data array to be sent
 * @param  [in] u32Size        Number of data in array pau8TxData
 * @param  [in] u32Timeout     Maximum count of trying to get a status of a
 *              flag in status register
 * @retval An en_result_t enumeration value:
 *            - Ok: Send successfully
 *            - Error: Send unsuccessfully or NACK received
 *            - ErrorInvalidParameter: pau8TxData is NULL
 */
en_result_t I2C_TransData(M4_I2C_TypeDef* I2Cx, uint8_t const pau8TxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    en_result_t enRet = Ok;
    uint32_t u32Cnt = 0UL;

    if(pau8TxData != NULL)
    {
        while((u32Cnt != u32Size) &&(enRet == Ok))
        {
            /* Wait tx buffer empty */
            enRet = I2C_WaitStatus(I2Cx, I2C_SR_TEMPTYF, Set, u32Timeout);

            if(enRet == Ok)
            {
                /* Send one byte data */
                I2C_WriteDataReg(I2Cx, pau8TxData[u32Cnt]);
                /* Wait transfer end */
                enRet = I2C_WaitStatus(I2Cx, I2C_SR_TENDF, Set, u32Timeout);

                /* If receive NACK*/
                if(I2C_GetStatus(I2Cx, I2C_SR_ACKRF) == Set)
                {
                    break;
                }
                u32Cnt++;
            }
        }
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}

/**
 * @brief  I2Cx Receive Data
 * @param  [in] I2Cx          Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [out] pau8RxData    Array to hold the received data
 * @param  [in]  u32Size       Number of data to be received
 * @param  [in]  u32Timeout    Maximum count of trying to get a status of a
 *              flag in status register
 * @retval An en_result_t enumeration value:
 *            - Ok: Receive successfully
 *            - Error: Receive unsuccessfully
 *            - ErrorInvalidParameter: pau8RxData is NULL
 */
en_result_t I2C_Receive(M4_I2C_TypeDef* I2Cx, uint8_t pau8RxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    en_result_t enRet = Ok;

    if(pau8RxData != NULL)
    {
        uint32_t u32FastAckEn = READ_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);
        for(uint32_t i=0UL; i<u32Size; i++)
        {
            enRet = I2C_WaitStatus(I2Cx, I2C_SR_RFULLF, Set, u32Timeout);

            if(0UL == u32FastAckEn)
            {
                if((u32Size >= 2UL) && (i == (u32Size - 2UL)))
                {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            }
            else
            {
                if(i != (u32Size - 1UL))
                {
                    I2C_AckConfig(I2Cx, I2C_ACK);
                }
                else
                {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            }

            if(enRet == Ok)
            {
                 /* read data from register */
                pau8RxData[i] = I2C_ReadDataReg(I2Cx);
            }
            else
            {
                break;
            }
        }
        I2C_AckConfig(I2Cx, I2C_ACK);
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}

/**
 * @brief  Master receive data and stop
 * @param  [in] I2Cx           Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] au8RxData      Array to hold the received data
 * @param  [in] u32Size        Number of data to be received
 * @param  [in] u32Timeout     Maximum count of trying to get a status of a
 *              flag in status register
 * @retval An en_result_t enumeration value:
 *            - Ok: Receive successfully
 *            - Error: Receive or Stop unsuccessfully
 *            - ErrorInvalidParameter: au8RxData is NULL
 */
en_result_t I2C_MasterReceiveAndStop(M4_I2C_TypeDef* I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    if(au8RxData != NULL)
    {
        uint32_t u32FastAckEn = READ_REG32_BIT(I2Cx->CR3, I2C_CR3_FACKEN);
        for(uint32_t i=0UL; i<u32Size; i++)
        {
            enRet = I2C_WaitStatus(I2Cx, I2C_SR_RFULLF, Set, u32Timeout);

            if(0UL == u32FastAckEn)
            {
                if((u32Size >= 2UL) && (i == (u32Size - 2UL)))
                {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            }
            else
            {
                if(i != (u32Size - 1UL))
                {
                    I2C_AckConfig(I2Cx, I2C_ACK);
                }
                else
                {
                    I2C_AckConfig(I2Cx, I2C_NACK);
                }
            }

            if(enRet == Ok)
            {
                /* Stop before read last data */
                if(i == (u32Size - 1UL))
                {
                    I2C_ClearStatus(I2Cx, I2C_SR_STOPF);
                    I2C_GenerateStop(I2Cx);
                }

                 /* read data from register */
                au8RxData[i] = I2C_ReadDataReg(I2Cx);

                if(i == (u32Size - 1UL))
                {
                    /* Wait stop flag after DRR read */
                    enRet = I2C_WaitStatus(I2Cx, I2C_SR_STOPF, Set, u32Timeout);
                }
            }
            else
            {
                break;
            }
        }
        I2C_AckConfig(I2Cx, I2C_ACK);
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}


/**
 * @brief  I2Cx Stop
 * @param  [in] I2Cx          Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in]  u32Timeout   Maximum count of trying to get a status of a
 *              flag in status register
 * @retval An en_result_t enumeration value:
 *            - Ok: Stop successfully
 *            - Error: Stop unsuccessfully
 */
en_result_t I2C_Stop(M4_I2C_TypeDef* I2Cx, uint32_t u32Timeout)
{
    en_result_t enRet;

    DDL_ASSERT(IS_VALID_UNIT(I2Cx));

    /* Clear stop flag */
    while((Set == I2C_GetStatus(I2Cx, I2C_SR_STOPF)) && (u32Timeout > 0UL))
    {
        I2C_ClearStatus(I2Cx, I2C_CLR_STOPFCLR);
        u32Timeout--;
    }
    I2C_GenerateStop(I2Cx);
    /* Wait stop flag */
    enRet = I2C_WaitStatus(I2Cx, I2C_SR_STOPF, Set, u32Timeout);

    return enRet;
}
/**
 * @}
 */

/**
* @defgroup I2C_Local_Functions I2C Local Functions
* @{
*/

/**
 * @brief  Try to wait a status of specified flags
 * @param  [in] I2Cx                Pointer to the I2C peripheral register.
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32Flags             specify the flags to check
 * @param  [in] enStatus             expected status,
 *         This parameter can be any combination of the following values:
 *         @arg   I2C_SR_STARTF     : Start condition detected flag
 *         @arg   I2C_SR_SLADDR0F   : Address 0 detected flag
 *         @arg   I2C_SR_SLADDR1F   : Address 1 detected flag
 *         @arg   I2C_SR_TENDF      : Transfer end flag
 *         @arg   I2C_SR_STOPF      : Stop condition detected flag
 *         @arg   I2C_SR_RFULLF     : Receive buffer full flag
 *         @arg   I2C_SR_TEMPTYF    : Transfer buffer empty flag
 *         @arg   I2C_SR_ARLOF      : Arbitration fails flag
 *         @arg   I2C_SR_ACKRF      : ACK detected flag
 *         @arg   I2C_SR_NACKF      : NACK detected flag
 *         @arg   I2C_SR_TMOUTF     : Time out detected flag
 *         @arg   I2C_SR_MSL        : Master mode flag
 *         @arg   I2C_SR_BUSY       : Bus busy status flag
 *         @arg   I2C_SR_TRA        : Transfer mode flag
 *         @arg   I2C_SR_GENCALLF   : General call detected flag
 *         @arg   I2C_SR_SMBDEFAULTF: Smbus default address detected flag
 *         @arg   I2C_SR_SMBHOSTF   : Smbus host address detected flag
 *         @arg   I2C_SR_SMBALRTF   : Smbus alarm address detected flag
 * @param  [in]  u32Timeout  Maximum count of trying to get a status of a
 *              flag in status register
 * @retval  Process result
 *          - Error         Failed to get expected status of specified flags
 *          - Ok            successfully gotten the expected status of the specified flags
 */
static en_result_t I2C_WaitStatus(const M4_I2C_TypeDef *I2Cx, uint32_t u32Flags, en_flag_status_t enStatus, uint32_t u32Timeout)
{
    en_result_t enRet = Error;
    uint32_t u32RegStatusBit;

    for(;;)
    {
        u32RegStatusBit = (READ_REG32_BIT(I2Cx->SR, u32Flags));
        if(((enStatus == Set) && (u32Flags == u32RegStatusBit))
           || ((enStatus == Reset) && (0UL == u32RegStatusBit)))
        {
            enRet = Ok;
        }

        if((Ok == enRet) || (0UL == u32Timeout))
        {
            break;
        }
        else
        {
            u32Timeout--;
        }
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
