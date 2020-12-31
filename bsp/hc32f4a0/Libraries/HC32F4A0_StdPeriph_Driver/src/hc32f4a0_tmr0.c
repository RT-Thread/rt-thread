/**
 *******************************************************************************
 * @file  hc32f4a0_tmr0.c
 * @brief This file provides firmware functions to manage the TMR0
 *        (TMR0).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb          First version
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
#include "hc32f4a0_tmr0.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMR0 TMR0
 * @brief TMR0 Driver Library
 * @{
 */

#if (DDL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Local_Macros TMR0 Local Macros
 * @{
 */
#define TMR0_BCONR_INIT_MSK             (TMR0_BCONR_CAPMDA | TMR0_BCONR_CKDIVA | \
                                         TMR0_BCONR_HICPA  | TMR0_BCONR_HSTAA  | \
                                         TMR0_BCONR_HSTPA  | TMR0_BCONR_HCLEA)

#define TMR0_CHA_CLKSRC_MSK             (TMR0_BCONR_SYNSA   |                  \
                                        TMR0_BCONR_SYNCLKA  |                  \
                                        TMR0_BCONR_ASYNCLKA)
#define TMR0_CHB_CLKSRC_MSK             (TMR0_BCONR_SYNSB   |                  \
                                        TMR0_BCONR_SYNCLKB  |                  \
                                        TMR0_BCONR_ASYNCLKB)

#define TMR0_CHB_POS                    (16U)
#define TMR0_OFFEST(ch)                 ((ch) * TMR0_CHB_POS)
/**
 * @defgroup TMR0_Check_Parameters_Validity TMR0 Check Parameters Validity
 * @{
 */
#define IS_VALID_UNIT(x)                                                       \
(   ((x) == M4_TMR0_1)                             ||                          \
    ((x) == M4_TMR0_2))

#define IS_VALID_CHANNEL(x)                                                    \
(   ((x) == TMR0_CH_A)                             ||                          \
    ((x) == TMR0_CH_B))

#define IS_VALID_CLK_DIVISION(x)                                               \
(   ((x) == TMR0_CLK_DIV1)                         ||                          \
    ((x) == TMR0_CLK_DIV2)                         ||                          \
    ((x) == TMR0_CLK_DIV4)                         ||                          \
    ((x) == TMR0_CLK_DIV8)                         ||                          \
    ((x) == TMR0_CLK_DIV16)                        ||                          \
    ((x) == TMR0_CLK_DIV32)                        ||                          \
    ((x) == TMR0_CLK_DIV64)                        ||                          \
    ((x) == TMR0_CLK_DIV128)                       ||                          \
    ((x) == TMR0_CLK_DIV256)                       ||                          \
    ((x) == TMR0_CLK_DIV512)                       ||                          \
    ((x) == TMR0_CLK_DIV1024))

#define IS_VALID_CLK_SRC(x)                                                    \
(   ((x) == TMR0_CLK_SRC_PCLK1)                    ||                          \
    ((x) == TMR0_CLK_SRC_INTHWTRIG)                ||                          \
    ((x) == TMR0_CLK_SRC_XTAL32)                   ||                          \
    ((x) == TMR0_CLK_SRC_LRC))

#define IS_VALID_HWTRG_FUNC(x)                                                 \
(   ((x) | TMR0_BT_HETRG_FUNC_MASK) == TMR0_BT_HETRG_FUNC_MASK)

#define IS_VALID_TMR0_FUNC(x)                                                  \
(   ((x) == TMR0_FUNC_CMP)                         ||                          \
    ((x) == TMR0_FUNC_CAP))

#define IS_VALID_TMR0_COM_TRIG(x)                                              \
(   ((x) != 0x0UL)                                 &&                          \
    (((x) | TMR0_COM_TRIG_MASk) == TMR0_COM_TRIG_MASk))
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
 * @defgroup TMR0_Global_Functions TMR0 Global Functions
 * @{
 */

/**
 * @brief  Set a default value for TMR0 configuration structure.
 * @param  [in] pstcInitStruct    Tmr0 function structure
 *                                See the structure definition for @ref stc_tmr0_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_StructInit(stc_tmr0_init_t* pstcInitStruct)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInitStruct != NULL)
    {
        pstcInitStruct->u32ClockDivision = TMR0_CLK_DIV1;
        pstcInitStruct->u32ClockSource   = TMR0_CLK_SRC_PCLK1;
        pstcInitStruct->u32Tmr0Func      = TMR0_FUNC_CMP;
        pstcInitStruct->u16CmpValue      = 0xFFFFU;
        pstcInitStruct->u16CntValue      = 0x0000U;
        pstcInitStruct->u32HwTrigFunc    = TMR0_BT_HWTRG_FUNC_NONE;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Tmr0 peripheral function initialize
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] pstcTmr0Init       TMR0 function base parameter structure
 *   @arg  See the structure definition for @ref stc_tmr0_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 * @note   In capture mode, don't need configure member u32HwTrigFunc and u16CmpValue.
 *         In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
en_result_t TMR0_Init(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, \
                        const stc_tmr0_init_t* pstcTmr0Init)
{
    uint32_t u32Temp;
    uint32_t u32CMPRAddr;
    uint32_t u32CNTRAddr;
    en_result_t enRet = ErrorInvalidParameter;
    if (pstcTmr0Init != NULL)
    {
        enRet = Ok;
        DDL_ASSERT(IS_VALID_UNIT(TMR0x));
        DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
        DDL_ASSERT(IS_VALID_CLK_DIVISION(pstcTmr0Init->u32ClockDivision));
        DDL_ASSERT(IS_VALID_CLK_SRC(pstcTmr0Init->u32ClockSource));
        DDL_ASSERT(IS_VALID_TMR0_FUNC(pstcTmr0Init->u32Tmr0Func));
        DDL_ASSERT(IS_VALID_HWTRG_FUNC(pstcTmr0Init->u32HwTrigFunc));

        u32Temp = (uint32_t)u8Channel * 4UL;
        u32CNTRAddr = (uint32_t)(&TMR0x->CNTAR) + u32Temp;
        u32CMPRAddr = (uint32_t)(&TMR0x->CMPAR) + u32Temp;
        RW_MEM32(u32CNTRAddr) = pstcTmr0Init->u16CntValue;
        RW_MEM32(u32CMPRAddr) = pstcTmr0Init->u16CmpValue;

        u32Temp = pstcTmr0Init->u32ClockDivision | \
                  pstcTmr0Init->u32HwTrigFunc    | \
                  pstcTmr0Init->u32Tmr0Func;

        u8Channel *= TMR0_CHB_POS;
        /* Config mode, clock source */
        MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_INIT_MSK << u8Channel), (u32Temp << u8Channel));
        /* Config clock mode */
        MODIFY_REG32(TMR0x->BCONR, (TMR0_CHA_CLKSRC_MSK << u8Channel), (pstcTmr0Init->u32ClockSource << u8Channel));
    }
    return enRet;
}

/**
 * @brief  Set clock source.
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32ClkSrc          Specifies the clock source
 * This parameter can be a value of the following:
 *   @arg  TMR0_CLK_SRC_PCLK1:     Synchronous clock source: PCLK1.
 *   @arg  TMR0_CLK_SRC_INTHWTRIG: Synchronous clock source: Hardware Trigger Event.
 *   @arg  TMR0_CLK_SRC_XTAL32:    Asynchronous clock source: XTAl32
 *   @arg  TMR0_CLK_SRC_LRC:       Asynchronous clock source: LRC
 * @retval None.
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_SetClkSrc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkSrc)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_CLK_SRC(u32ClkSrc));

    u8Channel = TMR0_OFFEST(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_CHA_CLKSRC_MSK << u8Channel), (u32ClkSrc << u8Channel));
}

/**
 * @brief  Set the division of the clock source.
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32ClkDiv          Specifies the clock source division
 * This parameter can be a value of the following:
 *   @arg  TMR0_CLK_DIV1:          Clock source.
 *   @arg  TMR0_CLK_DIV2:          Clock source / 2.
 *   @arg  TMR0_CLK_DIV4:          Clock source / 4.
 *   @arg  TMR0_CLK_DIV8:          Clock source / 8.
 *   @arg  TMR0_CLK_DIV16:         Clock source / 16.
 *   @arg  TMR0_CLK_DIV32:         Clock source / 32.
 *   @arg  TMR0_CLK_DIV64:         Clock source / 64.
 *   @arg  TMR0_CLK_DIV128:        Clock source / 128.
 *   @arg  TMR0_CLK_DIV256:        Clock source / 256.
 *   @arg  TMR0_CLK_DIV512:        Clock source / 512.
 *   @arg  TMR0_CLK_DIV1024:       Clock source / 1024.
 * @retval None.
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_SetClkDiv(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkDiv)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_CLK_DIVISION(u32ClkDiv));

    u8Channel = TMR0_OFFEST(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CKDIVA << u8Channel), (u32ClkDiv << u8Channel));
}

/**
 * @brief  Set Tmr0 HardWare Trigger Function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32HWFunc          Select TMR0 hardware trigger function
 * This parameter can be a value of @ref TMR0_HardwareTrigger_Func_define
 * @param  [in] enNewState         Disable or Enable the function
 * @retval None
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_HWTrigCmd(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, \
                           uint32_t u32HWFunc, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_HWTRG_FUNC(u32HWFunc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8Channel = TMR0_OFFEST(u8Channel);
    if(enNewState == Enable)
    {
        MODIFY_REG32(TMR0x->BCONR, (u32HWFunc << u8Channel), (u32HWFunc << u8Channel));
    }
    else
    {
        CLEAR_REG32_BIT(TMR0x->BCONR, (u32HWFunc << u8Channel));
    }
}

/**
 * @brief  Set Tmr0 Function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32Func            Select TMR0 function
 *   @arg  TMR0_FUNC_CMP:          Select the Compare function for TMR0
 *   @arg  TMR0_FUNC_CAP:          Select the Capture function for TMR0
 * @retval None
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_SetFunc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32Func)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_TMR0_FUNC(u32Func));

    u8Channel = TMR0_OFFEST(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CAPMDA << u8Channel), (u32Func << u8Channel));
}

/**
 * @brief  Get Tmr0 status (STFLR)
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval Set: Flag is set
 *         Reset: Flag is reset
 */
en_flag_status_t TMR0_GetStatus(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    en_flag_status_t enRet = Reset;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u8Channel = TMR0_OFFEST(u8Channel);
    if (READ_REG32_BIT(TMR0x->STFLR, (TMR0_STFLR_CMFA << u8Channel)) != 0U)
    {
        enRet = Set;
    }
    return enRet;
}

/**
 * @brief  Clear Tmr0 status (STFLR)
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval None
 * @note   In asynchronous clock, continuous operation of the STFLR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_ClearStatus(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u8Channel = TMR0_OFFEST(u8Channel);
    /*Clear the Flag*/
    CLEAR_REG32_BIT(TMR0x->STFLR, (TMR0_STFLR_CMFA << u8Channel));
}

/**
 * @brief  Command the tmr0 function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState         Disable or Enable the function
 * @retval None
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_Cmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                        en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8Channel = TMR0_OFFEST(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CSTA <<u8Channel), ((uint32_t)enNewState << TMR0_BCONR_CSTA_POS) << u8Channel);
}

/**
 * @brief  Tmr0 interrupt function command
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState       Disable or Enable the function
 * @retval None
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_IntCmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                        en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8Channel = TMR0_OFFEST(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_INTENA << u8Channel), ((uint32_t)enNewState << TMR0_BCONR_INTENA_POS) << u8Channel);
}

/**
 * @brief  Get Tmr0 counter value
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval In asynchronous clock, Get the value requires stop timer0
 *
 */
uint16_t TMR0_GetCntVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint16_t u16CntVal;
    uint32_t u32CNTRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CNTRAddr = (uint32_t)&TMR0x->CNTAR + (uint32_t)u8Channel * 4UL;
    u16CntVal = (uint16_t)RW_MEM32(u32CNTRAddr);
    return u16CntVal;
}

/**
 * @brief  Set Tmr0 counter value
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u16Value           The data to write to the counter register
 * @retval None
 * @note   Setting the count requires stop timer0
 */
void TMR0_SetCntVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value)
{
    uint32_t u32CNTRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CNTRAddr = (uint32_t)&TMR0x->CNTAR + (uint32_t)u8Channel * 4UL;
    RW_MEM32(u32CNTRAddr) = (uint32_t)u16Value;
}

/**
 * @brief  Get Tmr0 base compare value
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval In asynchronous clock, Get the value requires stop timer0
 */
uint16_t TMR0_GetCmpVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint16_t u16CmpVal;
    uint32_t u32CMPRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CMPRAddr = (uint32_t)&TMR0x->CMPAR + (uint32_t)u8Channel * 4UL;
    u16CmpVal = (uint16_t)RW_MEM32(u32CMPRAddr);
    return u16CmpVal;
}

/**
 * @brief  Set Tmr0 compare value
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u16Value           The data to write to the compare register
 * @retval Setting the count requires stop timer0
 */
void TMR0_SetCmpVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value)
{
    uint32_t u32CMPRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CMPRAddr = (uint32_t)&TMR0x->CMPAR + (uint32_t)u8Channel * 4UL;
    RW_MEM32(u32CMPRAddr) = (uint32_t)u16Value;
}

/**
 * @brief  De-Initialize TMR0 function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be value of the following:
 *   @arg  M4_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2:              TMR0 unit 2 instance register base
 * @retval None
 */
void TMR0_DeInit(M4_TMR0_TypeDef* TMR0x)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));

    WRITE_REG32(TMR0x->CMPAR, 0x0000FFFFUL);
    WRITE_REG32(TMR0x->CMPBR, 0x0000FFFFUL);
    WRITE_REG32(TMR0x->CNTAR, 0UL);
    WRITE_REG32(TMR0x->CNTBR, 0UL);
    WRITE_REG32(TMR0x->STFLR, 0UL);
    WRITE_REG32(TMR0x->BCONR, 0UL);
}

/**
 * @brief  Enable or Disable common trigger source for Tmr0
 * @param  [in] u32ComTrig              Common trigger event enable bit mask.
 *  This parameter can be value of @ref TMR0_Common_Trigger_Sel
 *   @arg  TMR0_COM_TRIG1:              Common trigger source 1.
 *   @arg  TMR0_COM_TRIG2:              Common trigger source 2.
 * @param  [in] enNewState              Disable or Enable the function
 * @retval None
 */
void TMR0_ComTriggerCmd(uint32_t u32ComTrig, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_TMR0_COM_TRIG(u32ComTrig));

    if (enNewState == Enable)
    {
        SET_REG32_BIT(M4_AOS->TMR0_HTSSR, u32ComTrig);
    }
    else
    {
        CLEAR_REG32_BIT(M4_AOS->TMR0_HTSSR, u32ComTrig);
    }
}

/**
 * @brief  Set trigger source for Tmr0
 * @param  [in] enEvent        External event source, @ref en_event_src_t
 * @retval None
 */
void TMR0_SetTriggerSrc(en_event_src_t enEvent)
{
    MODIFY_REG32(M4_AOS->TMR0_HTSSR, AOS_TMR0_HTSSR_TRGSEL, (uint32_t)enEvent);
}

/**
 * @}
*/

#endif /* DDL_TMR0_ENABLE */

/**
 * @}
*/

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
