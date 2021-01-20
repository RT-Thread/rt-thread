/**
 *******************************************************************************
 * @file  hc32f4a0_can.c
 * @brief This file provides firmware functions to manage the CAN.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
   2020-08-10       Wuze            Refined CAN_GetStatusVal()
   2020-12-14       Wuze            1. Fixed a bug of CAN_TTC_TransData(); Refined CAN_SBTConfig()
                                    2. Modified comment of structure stc_can_bt_cfg_t
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
#include "hc32f4a0_can.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CAN CAN
 * @brief CAN Driver Library
 * @{
 */

#if (DDL_CAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CAN_Local_Macros CAN Local Macros
 * @{
 */

/**
 * @defgroup CAN_Configuration_Bit_Mask CAN Configuration Bit Mask
 * @{
 */
#define CAN_LB_MODE_MSK                     (CAN_CFG_STAT_LBMI | CAN_CFG_STAT_LBME)
#define CAN_TRANS_MODE_MSK                  (CAN_CFG_STAT_TPSS | CAN_CFG_STAT_TSSS)
#define CAN_TTC_FLAG_CLR_MSK                (CAN_TTC_FLAG_TTI | CAN_TTC_FLAG_WTI)
/**
 * @}
 */

/**
 * @defgroup CAN_Register_Bit_Band CAN Register Bit Band
 * @{
 */
#define __BIT_BAND_BASE                     (0x42000000UL)
#define __PERIP_BASE                        (0x40000000UL)
#define __REG_OFS(regAddr)                  ((regAddr) - __PERIP_BASE)
#define __BIT_BAND_ADDR(regAddr, pos)       ((__REG_OFS(regAddr) << 5U) + ((uint32_t)(pos) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(regAddr, pos)              (*(__IO uint32_t *)__BIT_BAND_ADDR((regAddr), (pos)))
/**
 * @}
 */

/**
 * @defgroup CAN_Check_Parameters_Validity CAN check parameters validity
 * @{
 */
#define IS_CAN_UNIT(x)                                                         \
(   ((x) == M4_CAN1)                            ||                             \
    ((x) == M4_CAN2))

#define IS_CAN_SBT_SEG1(x)                                                     \
(   ((x) >= 2U)                                 &&                             \
    ((x) <= 65U))

#define IS_CAN_SBT_SEG2(x)                                                     \
(   ((x) >= 1U)                                 &&                             \
    ((x) <= 8U))

#define IS_CAN_FD_SBT_SEG2(x)                                                  \
(   ((x) >= 1U)                                 &&                             \
    ((x) <= 32U))

#define IS_CAN_SBT_SJW(x)                                                      \
(   ((x) >= 1U)                                 &&                             \
    ((x) <= 16U))

#define IS_CAN_SBT_PRESC(x)                                                    \
(   ((x) >= 1U)                                 &&                             \
    ((x) <= 256U))

#define IS_CAN_FBT_SEG1(x)                                                     \
(   ((x) >= 2U)                                 &&                             \
    ((x) <= 17U))

#define IS_CAN_FBT_SEG2(x)                                                     \
(   ((x) >= 1U)                                 &&                             \
    ((x) <= 8U))

#define IS_CAN_FBT_SJW(x)                                                      \
(   ((x) >= 1U)                                 &&                             \
    ((x) <= 8U))

#define IS_CAN_FBT_PRESC(x)                                                    \
(   ((x) >= 1U)                                 &&                             \
    ((x) <= 256U))

#define IS_CAN_SBT_PRIO_MODE(x)                                                \
(   ((x) == CAN_STB_PRIO_FIFO)                  ||                             \
    ((x) == CAN_STB_PRIO_ID))

#define IS_CAN_IDE(x)                                                          \
(   ((x) == 0U)                                 ||                             \
    ((x) == 1U))

#define IS_CAN_SELF_ACK_CMD(x)                                                 \
(   ((x) == CAN_SELF_ACK_DISABLE)               ||                             \
    ((x) == CAN_SELF_ACK_ENABLE))

#define IS_CAN_TB_TYPE(x)                                                      \
(   ((x) == CAN_BUF_PTB)                        ||                             \
    ((x) == CAN_BUF_STB))

#define IS_CAN_STB_TX_CTRL(x)                                                  \
(   ((x) == CAN_STB_TRANS_ALL)                  ||                             \
    ((x) == CAN_STB_TRANS_ONE))

#define IS_CAN_WORK_MODE(x)                                                    \
(   ((x) <= CAN_MODE_ELB_SILENT))

#define IS_CAN_TRANS_MODE(x)                                                   \
(   ((x) == CAN_TRANS_PTB_STB_AUTO_RETX)        ||                             \
    ((x) == CAN_TRANS_PTB_SSHOT)                ||                             \
    ((x) == CAN_TRANS_STB_SSHOT)                ||                             \
    ((x) == CAN_TRANS_PTB_STB_SSHOT))

#define IS_CAN_RB_STORE_SEL(x)                                                 \
(   ((x) == CAN_RB_STORE_CORRECT_DATA)          ||                             \
    ((x) == CAN_RB_STORE_ALL_DATA))

#define IS_CAN_RB_OVF_OP(x)                                                    \
(   ((x) == CAN_RB_OVF_SAVE_NEW)                ||                             \
    ((x) == CAN_RB_OVF_DISCARD_NEW))

#define IS_CAN_RBS_FULL_WARN_LIMIT(x)                                          \
(   ((x) >= CAN_RBS_WARN_LIMIT_MIN)             &&                             \
    ((x) <= CAN_RBS_WARN_LIMIT_MAX))

#define IS_CAN_ERR_WARN_LIMIT(x)                                               \
(   ((x) < 16U))

#define IS_CAN_AF_MSK_TYPE(x)                                                  \
(   ((x) == CAN_AF_MSK_STD_EXT)                 ||                             \
    ((x) == CAN_AF_MSK_STD)                     ||                             \
    ((x) == CAN_AF_MSK_EXT))

#define IS_CAN_1_BIT_MSK(x)                                                    \
(   ((x) != 0U)                                 &&                             \
    (((x) & ((x) - 1U)) == 0U))

#define IS_CAN_BIT_MSK(x, msk)                                                 \
(   ((x) != 0U)                                 &&                             \
    (((x) | (msk)) == (msk)))

#define IS_CAN_FD_MODE(x)                                                      \
(   ((x) == CAN_FD_MODE_BOSCH)                  ||                             \
    ((x) == CAN_FD_MODE_ISO_11898))

#define IS_CAN_FD_SSP(x)                                                       \
(   ((x) < 128U))

#define IS_CAN_TDC_CMD(x)                                                      \
(   ((x) == CAN_FD_TDC_DISABLE)                 ||                             \
    ((x) == CAN_FD_TDC_ENABLE))

#define IS_CAN_TTC_TB_MODE(x)                                                  \
(   ((x) == CAN_TTC_TB_MODE_NORMAL)             ||                             \
    ((x) == CAN_TTC_TB_MODE_PTR))

#define IS_CAN_TTC_TBS(x)                                                      \
(   ((x) <= CAN_TTC_TBS_STB3))

#define IS_CAN_TTC_TRIG_TYPE(x)                                                \
(   ((x) == CAN_TTC_TRIG_IMMED_TRIG)            ||                             \
    ((x) == CAN_TTC_TRIG_TIME_TRIG)             ||                             \
    ((x) == CAN_TTC_TRIG_SSHOT_TRANS_TRIG)      ||                             \
    ((x) == CAN_TTC_TRIG_TRANS_START_TRIG)      ||                             \
    ((x) == CAN_TTC_TRIG_TRANS_STOP_TRIG))

#define IS_CAN_TTC_NTU_PRESC(x)                                                \
(   ((x) == CAN_TTC_NTU_PRESC_1)                ||                             \
    ((x) == CAN_TTC_NTU_PRESC_2)                ||                             \
    ((x) == CAN_TTC_NTU_PRESC_4)                ||                             \
    ((x) == CAN_TTC_NTU_PRESC_8))

#define IS_CAN_TTC_TX_EN_WINDOW(x)                                             \
(   (x) <= 16U)

/**
 * @}
 */

/**
 * @defgroup CAN_Miscellaneous_Macros CAN Miscellaneous Macros
 * @{
 */
#define CAN_RBS_CNT                         (8U)                /*!< Each CAN unit has 8 receive buffer slots. */
#define CAN_RBS_WARN_LIMIT_MIN              (1U)
#define CAN_RBS_WARN_LIMIT_MAX              (CAN_RBS_CNT)
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
 * @defgroup CAN_Global_Functions CAN Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified CAN peripheral according to the specified parameters
 *         in the stc_can_init_t type structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcInit               Pointer to a stc_can_init_t structure value that
 *                                      contains the configuration information for the CAN.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL
 */
en_result_t CAN_Init(M4_CAN_TypeDef *CANx, const stc_can_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
#ifdef __DEBUG
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcInit->enCANFDCmd));
        if (pstcInit->enCANFDCmd == Disable)
        {
            DDL_ASSERT(IS_CAN_SBT_SEG2(pstcInit->stcSBT.u32SEG2));
        }
        else
        {
            DDL_ASSERT(IS_CAN_FD_SBT_SEG2(pstcInit->stcSBT.u32SEG2));
        }
#endif
        /* Software reset. */
        CAN_SWReset(CANx);
        /* Defines slow bit time. */
        (void)CAN_SBTConfig(CANx, &pstcInit->stcSBT);
        /* Specifies STB priority mode. */
        CAN_SetSTBPrioMode(CANx, pstcInit->u8STBPrioMode);
        /* Configures acceptance filters. */
        (void)CAN_AFConfig(CANx, pstcInit->u16AFSel, pstcInit->pstcAFCfg);
        /* Configures CAN-FD if enabled. */
        CAN_FD_Cmd(CANx, Disable);
        if (pstcInit->enCANFDCmd == Enable)
        {
            (void)CAN_FD_Config(CANx, &pstcInit->stcFDCfg);
            CAN_FD_Cmd(CANx, Enable);
        }

        /* CAN bus enters normal communication mode. */
        CAN_EnterNormalComm(CANx);
        /* Specifies work mode. */
        CAN_SetWorkMode(CANx, pstcInit->u8WorkMode);
        /* Specifies transmission mode. */
        CAN_SetTransMode(CANx, pstcInit->u8TransMode);

        CAN_SetRBStoreSel(CANx, pstcInit->u8RBStoreSel);
        CAN_SetRBSWarnLimit(CANx, pstcInit->u8RBSWarnLimit);
        CAN_SetErrWarnLimit(CANx, pstcInit->u8ErrWarnLimit);
        /* Specifies the operation when receiving buffer overflow. */
        CAN_SetRBOvfOp(CANx, pstcInit->u8RBOvfOp);
        /* Enable acceptance filters that configured before. */
        SET_REG16_BIT(CANx->ACFEN, pstcInit->u16AFSel);

        /* Enable or disable self-ACK. */
        DDL_ASSERT(IS_CAN_SELF_ACK_CMD(pstcInit->u8SelfACKCmd));
        MODIFY_REG8(CANx->RCTRL, CAN_RCTRL_SACK, pstcInit->u8SelfACKCmd);

        /* Clear all status flags. */
        CAN_ClrStatus(CANx, CAN_FLAG_ALL);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for CAN initialization structure. \
 *         Slow bit time configuration:
 *         Based on 40MHz CAN clock, TQ clock is CAN clock divided by 4. \
 *         Bit rate 500Kbps, 1 bit time is 20TQs, sample point is 80%.
 *         CAN-FD bit time configuration:
 *         Based on 40MHz CAN clock, TQ clock is CAN clock divided by 1. \
 *         Bit rate 2Mbps, 1 bit time is 20TQs, primary sample point is 80%, \
 *         secondary sample point is 80%.
 * @param  [in]  pstcInit               Pointer to a stc_can_init_t structure value that
 *                                      contains the configuration information for the CAN unit.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t CAN_StructInit(stc_can_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u8WorkMode     = CAN_MODE_NORMAL;
        pstcInit->u8TransMode    = CAN_TRANS_PTB_STB_AUTO_RETX;
        pstcInit->u8STBPrioMode  = CAN_STB_PRIO_FIFO;
        pstcInit->u8RBSWarnLimit = 6U;
        pstcInit->u8ErrWarnLimit = 7U;
        pstcInit->u16AFSel       = CAN_AF1;
        pstcInit->u8RBStoreSel   = CAN_RB_STORE_CORRECT_DATA;
        pstcInit->u8RBOvfOp      = CAN_RB_OVF_DISCARD_NEW;
        pstcInit->u8SelfACKCmd   = CAN_SELF_ACK_DISABLE;
        pstcInit->pstcAFCfg      = NULL;
        /*
         * Synchronization Segment(SS): Fixed as 1TQ
         * Propagation Time Segment(PTS) and Phase Buffer Segment 1(PBS1): 15TQs
         * Phase Buffer Segment 2(PBS2): 4TQs
         *
         * Field 'S_SEG_1' in register CAN_SBT contains SS, PTS and PBS1.
         * Field 'S_SEG_2' in register CAN_SBT only contains PBS2.
         * Sample point = (SS + PTS + PBS1) / (SS + PTS + PBS1 + PBS2)
         *              = (1 + 15) / (1 + 15 + 4)
         *              = 80%.
         */
        pstcInit->stcSBT.u32SEG1 = 1U + 15U;
        pstcInit->stcSBT.u32SEG2 = 4U;
        pstcInit->stcSBT.u32SJW  = 2U;
        pstcInit->stcSBT.u32Prescaler = 4U;

        /*
         * Set enCANFDCmd as Enable if CAN-FD is needed.
         *
         * u8TDCCmd: Enalbe(CAN_FD_TDC_ENABLE) or disable(CAN_FD_TDC_DISABLE) transmitter delay compensation.
         * u8TDCSSP: The position(TQs) of secondary sample point.
         *
         * Primary sample point: u32SEG1 / (u32SEG1 + u32SEG2) = 80%
         * Secondary sample point: u8TDCSSP / (u32SEG1 + u32SEG2) = 80%
         */
        pstcInit->enCANFDCmd = Disable;
        (void)CAN_FD_StructInit(&pstcInit->stcFDCfg);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the CAN peripheral. Reset the registers of the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval None
 */
void CAN_DeInit(M4_CAN_TypeDef *CANx)
{
    uint8_t i;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    CLEAR_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
    for (i=0U; i<2U; i++)
    {
        WRITE_REG8(CANx->CFG_STAT, 0x80U);
        WRITE_REG8(CANx->TCMD, 0x00U);
        WRITE_REG8(CANx->TCTRL, 0x90U);
        WRITE_REG8(CANx->RCTRL, 0x10U);
        WRITE_REG8(CANx->RTIE, 0xFEU);
        WRITE_REG8(CANx->RTIF, 0xFFU);
        WRITE_REG8(CANx->ERRINT, 0xD5U);
        WRITE_REG8(CANx->LIMIT, 0x1BU);
        WRITE_REG32(CANx->SBT, 0x01020203U);
        WRITE_REG32(CANx->FBT, 0x01020203U);
        WRITE_REG8(CANx->EALCAP, 0x00U);
        WRITE_REG8(CANx->TDC, 0x00U);
        WRITE_REG8(CANx->RECNT, 0x00U);
        WRITE_REG8(CANx->TECNT, 0x00U);
        WRITE_REG8(CANx->ACFCTRL, 0x00U);
        WRITE_REG8(CANx->ACFEN, 0x01U);
        WRITE_REG8(CANx->TBSLOT, 0x00U);
        WRITE_REG8(CANx->TTCFG, 0xD8U);
        WRITE_REG16(CANx->TRG_CFG, 0x00U);
        WRITE_REG16(CANx->TT_TRIG, 0x00U);
        WRITE_REG16(CANx->TT_WTRIG, 0x00U);
        SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
    }
}

/**
 * @brief  Software reset the specified CAN unit. \
           Software reset is a partial reset and CANNOT reset all registers. \
           Some registers need software reset before written.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval None
 */
void CAN_SWReset(M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
}

/**
 * @brief  Set the CAN node to enter the normal communication mode.
 *         When this state is set, it takes 11 CAN bit time for this node to participate in communication.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval None
 */
void CAN_EnterNormalComm(M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    CLEAR_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
}

/**
 * @brief  Specifies work mode for the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8WorkMode             Work mode of CAN.
 *                                      This parameter can be a value of @ref CAN_Work_Mode
 *   @arg  CAN_MODE_NORMAL:             Normal work mode.
 *   @arg  CAN_MODE_SILENT:             Silent work mode. Prohibit data transmission.
 *   @arg  CAN_MODE_ILB:                Internal loopback mode, just for self-test while developing.
 *   @arg  CAN_MODE_ELB:                External loopback mode, just for self-test while developing.
 *   @arg  CAN_MODE_ELB_SILENT:         External loppback silent mode, just for self-test while developing. \
 *                                      It is forbidden to respond to received frames and error frames, but data can be transmitted.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_SetWorkMode(M4_CAN_TypeDef *CANx, uint8_t u8WorkMode)
{
    uint8_t u8CFGSTAT = 0U;
    uint8_t u8TCMD    = 0U;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_WORK_MODE(u8WorkMode));

    switch (u8WorkMode)
    {
        case CAN_MODE_SILENT:
            u8TCMD    = CAN_TCMD_LOM;
            break;
        case CAN_MODE_ILB:
            u8CFGSTAT = CAN_CFG_STAT_LBMI;
            break;
        case CAN_MODE_ELB:
            u8CFGSTAT = CAN_CFG_STAT_LBME;
            break;
        case CAN_MODE_ELB_SILENT:
            u8TCMD    = CAN_TCMD_LOM;
            u8CFGSTAT = CAN_CFG_STAT_LBME;
            break;
        case CAN_MODE_NORMAL:
        default:
            break;
    }

    MODIFY_REG8(CANx->CFG_STAT, CAN_LB_MODE_MSK, u8CFGSTAT);
    MODIFY_REG8(CANx->TCMD, CAN_TCMD_LOM, u8TCMD);
}

/**
 * @brief  Specifies transmission mode for the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8TransMode            PTB/STB transmission mode.
 *                                      This parameter can be a value of @ref CAN_Trans_Mode
 *   @arg  CAN_TRANS_PTB_STB_AUTO_RETX: Both PTB and STB automatically retransmit.
 *   @arg  CAN_TRANS_PTB_SSHOT:         PTB single shot transmit.
 *   @arg  CAN_TRANS_STB_SSHOT:         STB single shot transmit.
 *   @arg  CAN_TRANS_PTB_STB_SSHOT:     STB and PTB both single shot transmit.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_SetTransMode(M4_CAN_TypeDef *CANx, uint8_t u8TransMode)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TRANS_MODE(u8TransMode));
    MODIFY_REG8(CANx->CFG_STAT, CAN_TRANS_MODE_MSK, u8TransMode);
}

/**
 * @brief  Specifies STB transmission priority mode for the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8STBPrioMode          STB transmission priority mode.
 *                                      This parameter can be a value of @ref CAN_STB_Priority_Mode
 *   @arg  CAN_STB_PRIO_FIFO:           Data first in first be transmitted.
 *   @arg  CAN_STB_PRIO_ID :            Data with smallest ID first be transmitted.
 * @retval None
 * @note Whatever the priority mode of STB is, PTB always has the highest priority.
 */
void CAN_SetSTBPrioMode(M4_CAN_TypeDef *CANx, uint8_t u8STBPrioMode)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_SBT_PRIO_MODE(u8STBPrioMode));
    MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_TSMODE, u8STBPrioMode);
}

/**
 * @brief  Specifies the receive buffer store selection for specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8RBStoreSel           Receive buffer store selection.
 *                                      This parameter can be a value of @ref CAN_RB_Store_Selection
 *   @arg  CAN_RB_STORE_CORRECT_DATA:   Receive buffer stores correct data frames only.
 *   @arg  CAN_RB_STORE_ALL_DATA:       Receive buffer stores all data frames, includes error data.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_SetRBStoreSel(M4_CAN_TypeDef *CANx, uint8_t u8RBStoreSel)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_RB_STORE_SEL(u8RBStoreSel));
    MODIFY_REG8(CANx->RCTRL, CAN_RCTRL_RBALL, u8RBStoreSel);
}

/**
 * @brief  Specifies the operation when receiving buffer overflow.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8RBOvfOperation       Operation when receive buffer overflow.
 *                                      This parameter can be a value of @ref CAN_RB_Overflow_Operation
 *   @arg  CAN_RB_OVF_SAVE_NEW:         Saves the newly received data and the first received data will be overwritten.
 *   @arg  CAN_RB_OVF_DISCARD_NEW:      Discard the newly received data.
 * @retval None
 */
void CAN_SetRBOvfOp(M4_CAN_TypeDef *CANx, uint8_t u8RBOvfOperation)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_RB_OVF_OP(u8RBOvfOperation));
    MODIFY_REG8(CANx->RCTRL, CAN_RCTRL_ROM, u8RBOvfOperation);
}

/**
 * @brief  Enable or disable the specified interrupts of the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32IntType             Interrupt type of CAN. Set this parameter to 0xFFFFFFFF to select all the interrupts of CAN.
 *                                      This parameter can be values of @ref CAN_Interrupt_Type
 *   @arg  CAN_INT_ERR_INT:             Register bit RTIE.EIE. Error interrupt.
 *   @arg  CAN_INT_STB_TRANS_OK:        Register bit RTIE.TSIE. Secondary transmit buffer was transmitted successfully.
 *   @arg  CAN_INT_PTB_TRANS_OK:        Register bit RTIE.TPIE. Primary transmit buffer was transmitted successfully.
 *   @arg  CAN_INT_RB_ALMOST_FULL:      Register bit RTIE.RAFIE. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_INT_RB_FIFO_FULL:        Register bit RTIE.RFIE. The FIFO of receive buffer is full.
 *   @arg  CAN_INT_RX_OVERRUN:          Register bit RTIE.ROIE. Receive buffers are full and there is a further message to be stored.
 *   @arg  CAN_INT_RX:                  Register bit RTIE.RIE. Received a valid data frame or remote frame.
 *   @arg  CAN_INT_BUS_ERR:             Register bit ERRINT.BEIE. Arbitration lost caused bus error
 *   @arg  CAN_INT_ARB_LOST:            Register bit ERRINT.ALIE. Arbitration lost.
 *   @arg  CAN_INT_ERR_PASSIVE:         Register bit ERRINT.EPIE. A change from error-passive to error-active or error-active to error-passive has occurred.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified interrupts.
 *   @arg  Disable:                     Disable the specified interrupts.
 * @retval None
 */
void CAN_IntCmd(M4_CAN_TypeDef *CANx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint8_t u8RTIE;
    uint8_t u8ERRINT;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32IntType &= CAN_INT_ALL;
    u8RTIE      = (uint8_t)u32IntType;
    u8ERRINT    = (uint8_t)(u32IntType >> 8U);

    if (enNewState == Enable)
    {
        SET_REG8_BIT(CANx->RTIE, u8RTIE);
        SET_REG8_BIT(CANx->ERRINT, u8ERRINT);
    }
    else
    {
        CLEAR_REG8_BIT(CANx->RTIE, u8RTIE);
        CLEAR_REG8_BIT(CANx->ERRINT, u8ERRINT);
    }
}

/**
 * @brief  Configures slow bit timing(SBT).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcCfg                Pointer to a stc_can_bt_cfg_t structure value that
 *                                      contains the configuration information for SBT.
 *   @arg  u32SEG1:                     TQs of segment 1. Contains synchronization segment, \
 *                                      propagation time segment and phase buffer segment 1.
 *   @arg  u32SEG2:                     TQs of segment 2. Phase buffer segment 2.
 *   @arg  u32SJW:                      TQs of synchronization jump width.
 *   @arg  u32Prescaler:                Range [1, 256].
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 * @note 1. Restrictions: u32SEG1 >= u32SEG2 + 1, u32SEG2 >= u32SJW.
 * @note 2. TQ = u32Prescaler / CANClock.
 * @note 3. Slow bit time = (u32SEG1 + u32SEG2) * TQ.
 * @note 4. Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_SBTConfig(M4_CAN_TypeDef *CANx, const stc_can_bt_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;
#ifdef __DEBUG
    uint32_t u32Addr;
    uint32_t u32BitPos = 0U;
#endif
    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_SBT_SEG1(pstcCfg->u32SEG1));
        DDL_ASSERT(IS_CAN_SBT_SJW(pstcCfg->u32SJW));
        DDL_ASSERT(IS_CAN_SBT_PRESC(pstcCfg->u32Prescaler));
#ifdef __DEBUG
        if (CANx == M4_CAN2)
        {
            u32BitPos = 1U;
        }
        /* If CAN-FD enabled. */
        u32Addr = (uint32_t)&M4_PERIC->CAN_SYCTLREG;
        if (BIT_BAND(u32Addr, u32BitPos) == (uint32_t)Disable)
        {
            DDL_ASSERT(IS_CAN_SBT_SEG2(pstcCfg->u32SEG2));
        }
        else
        {
            DDL_ASSERT(IS_CAN_FD_SBT_SEG2(pstcCfg->u32SEG2));
        }
#endif
        WRITE_REG32(CANx->SBT, ((pstcCfg->u32SEG1 - 2U) | \
                                ((pstcCfg->u32SEG2 - 1U) << CAN_SBT_S_SEG_2_POS) | \
                                ((pstcCfg->u32SJW - 1U) << CAN_SBT_S_SJW_POS)    | \
                                ((pstcCfg->u32Prescaler - 1U) << CAN_SBT_S_PRESC_POS)));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get arbitration lost position of a frame.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval A uint8_t type value of arbitration lost position.
 */
uint8_t CAN_GetArbLostPos(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (READ_REG8_BIT(CANx->EALCAP, CAN_EALCAP_ALC));
}

/**
 * @brief  Get error type.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t value of error type. It's can be a value of @ref CAN_Error_Type
 *   @arg  CAN_ERR_NO:                  No error.
 *   @arg  CAN_ERR_BIT:                 Error is bit error.
 *   @arg  CAN_ERR_FORM:                Error is form error.
 *   @arg  CAN_ERR_STUFF:               Error is stuff error.
 *   @arg  CAN_ERR_ACK:                 Error is ACK error.
 *   @arg  CAN_ERR_CRC:                 Error is CRC error.
 *   @arg  CAN_ERR_OTHER:               Error is other error.
 */
uint8_t CAN_GetErrType(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (READ_REG8_BIT(CANx->EALCAP, CAN_EALCAP_KOER));
}

/**
 * @brief  Set receive buffer slots full warning limit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in] u8RBSWarnLimit:         Receive buffer slots full warning limit. Rang is [1, 8].
 *                                      Each CAN unit has 8 receive buffer slots. When the number of received frames \
 *                                      reaches the value specified by parameter 'u8RBSWarnLimit', register bit RTIF.RAFIF is set and \
 *                                      the interrupt occurred if it was enabled.
 * @retval None
 */
void CAN_SetRBSWarnLimit(M4_CAN_TypeDef *CANx, uint8_t u8RBSWarnLimit)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_RBS_FULL_WARN_LIMIT(u8RBSWarnLimit));

    u8RBSWarnLimit <<= CAN_LIMIT_AFWL_POS;
    MODIFY_REG8(CANx->LIMIT, CAN_LIMIT_AFWL, u8RBSWarnLimit);
}

/**
 * @brief  Set error warning limit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8ErrWarnLimit         Programmable error warning limit. Range is [0, 15].
 *                                      Error warning limit = (u8ErrWarnLimit + 1) * 8.
 * @retval None
 */
void CAN_SetErrWarnLimit(M4_CAN_TypeDef *CANx, uint8_t u8ErrWarnLimit)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_ERR_WARN_LIMIT(u8ErrWarnLimit));
    MODIFY_REG8(CANx->LIMIT, CAN_LIMIT_EWL, u8ErrWarnLimit);
}

/**
 * @brief  Get receive error count(REC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of REC.
 */
uint8_t CAN_GetREC(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (CANx->RECNT);
}

/**
 * @brief  Get transmission error count(TEC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of TEC.
 */
uint8_t CAN_GetTEC(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (CANx->TECNT);
}

/**
 * @brief  Clear receive error count(REC) and transmission error count(TEC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval None
 * @note Set CFG_STAT.BUSOFF to 1 to clear REC and TEC. ONLY for TEST mode!
 */
void CAN_ClrErrCount(M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_BUSOFF);
}

/**
 * @brief  Configures acceptance filter. Set ID and ID mask for the specified acceptance filters.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16AFSel               Acceptance filter enable bit.
 *                                      This parameter can be values of @ref CAN_AF
 *   @arg CAN_AF1 ~ CAN_AF16
 * @param  [in]  pstcAFCfg              Points to a stc_can_af_cfg_t structure type array which contains ID and ID mask
 *                                      values for the acceptance filters specified by parameter u16AFSel.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -u16AFSel == 0U.
 *                                     -pstcAFCfg == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_AFConfig(M4_CAN_TypeDef *CANx, uint16_t u16AFSel, const stc_can_af_cfg_t pstcAFCfg[])
{
    uint8_t u8AFAddr = 0U;
    uint8_t i = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if ((u16AFSel != 0U) && (pstcAFCfg != NULL))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));

        while (u16AFSel != 0U)
        {
            if ((u16AFSel & (uint16_t)0x1U) != 0U)
            {
                DDL_ASSERT(IS_CAN_AF_MSK_TYPE(pstcAFCfg[i].u32MskType));

                WRITE_REG8(CANx->ACFCTRL, u8AFAddr);
                WRITE_REG32(CANx->ACF, pstcAFCfg[i].u32ID);
                SET_REG8_BIT(CANx->ACFCTRL, CAN_ACFCTRL_SELMASK);
                WRITE_REG32(CANx->ACF, pstcAFCfg[i].u32IDMsk | pstcAFCfg[i].u32MskType);
                i++;
            }

            u16AFSel >>= 1U;
            u8AFAddr++;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable acceptance filter.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16AFSel               Acceptance filter enable bit.
 *                                      This parameter can be values of @ref CAN_AF
 *   @arg CAN_AF1 ~ CAN_AF16
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the acceptance filters that specified by parameter u16AFSel.
 *   @arg Disable:                      Disable the acceptance filters that specified by parameter u16AFSel.
 * @retval None
 */
void CAN_AFCmd(M4_CAN_TypeDef *CANx, uint16_t u16AFSel, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG16_BIT(CANx->ACFEN, u16AFSel);
    }
    else
    {
        CLEAR_REG16_BIT(CANx->ACFEN, u16AFSel);
    }
}

/**
 * @brief  Get the transmit buffer which is being transmitted.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of transmit buffer type. It can be a value of @ref CAN_Transmit_Buffer_Type
 *   @arg  CAN_BUF_PTB:                 The transmit buffer which is being transmitted is PTB.
 *   @arg  CAN_BUF_STB:                 The transmit buffer which is being transmitted is STB.
 *   @arg  0xFFU:                       No transmit buffer is being transmitted.
 */
uint8_t CAN_GetTBType(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Tmp;
    uint8_t u8Ret;

    u8Tmp = CANx->TCMD;
    if ((u8Tmp & CAN_TCMD_TPE) != 0U)
    {
        u8Ret = CAN_BUF_PTB;
    }
    else if ((u8Tmp & (CAN_TCMD_TSALL | CAN_TCMD_TSONE)) != 0U)
    {
        u8Ret = CAN_BUF_STB;
    }
    else
    {
        u8Ret = 0xFFU;
    }

    return u8Ret;
}

/**
 * @brief  Abort the transmission of the specified transmit buffer that ready but not started.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8TBType               The transmit buffer to be aborted.
 *                                      This parameter can be a value of @ref CAN_Transmit_Buffer_Type
 *   @arg  CAN_BUF_PTB:                 Abort PTB transmission that ready but not started.
 *   @arg  CAN_BUF_STB:                 Abort STB transmission that ready but not started.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_AbortTrans(M4_CAN_TypeDef *CANx, uint8_t u8TBType)
{
    uint8_t au8Abort[] = {CAN_TCMD_TPA, CAN_TCMD_TSA};

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TB_TYPE(u8TBType));
    SET_REG8_BIT(CANx->TCMD, au8Abort[u8TBType]);
}

/**
 * @brief  Get the common flag's status.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32Flag                Status flag.
 *                                      This parameter can be a value of @ref CAN_Common_Status_Flag
 *   @arg  CAN_FLAG_BUS_OFF:            Register bit CFG_STAT.BUSOFF. CAN bus off.
 *   @arg  CAN_FLAG_BUS_TX:             Register bit CFG_STAT.TACTIVE. CAN bus is transmitting.
 *   @arg  CAN_FLAG_BUS_RX:             Register bit CFG_STAT.RACTIVE. CAN bus is receiving.
 *   @arg  CAN_FLAG_RB_OVF:             Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost.
 *   @arg  CAN_FLAG_TB_FULL:            Register bit RTIE.TSFF. Transmit buffers are all full: \
 *                                      TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled. \
 *                                      TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.
 *   @arg  CAN_FLAG_TRANS_ABORTED:      Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *   @arg  CAN_FLAG_ERR_INT:            Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter and the \
 *                                      set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than \
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *   @arg  CAN_FLAG_STB_TRANS_OK:       Register bit RTIF.TSIF. STB was transmitted successfully.
 *   @arg  CAN_FLAG_PTB_TRANS_OK:       Register bit RTIF.TPIF. PTB was transmitted successfully.
 *   @arg  CAN_FLAG_RB_ALMOST_FULL:     Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_FLAG_RB_FIFO_FULL:       Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *   @arg  CAN_FLAG_RX_OVERRUN:         Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *   @arg  CAN_FLAG_RX_OK:              Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *   @arg  CAN_FLAG_BUS_ERR:            Register bit ERRINT.BEIF. Arbitration lost caused bus error.
 *   @arg  CAN_FLAG_ARB_LOST:           Register bit ERRINT.ALIF. Arbitration lost.
 *   @arg  CAN_FLAG_ERR_PASSIVE:        Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *   @arg  CAN_FLAG_ERR_PASSIVE_NODE:   Register bit ERRINT.EPASS. The node is an error-passive node.
 *   @arg  CAN_FLAG_REACH_WARN_LIMIT:   Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         At least one of the specified status flags is set.
 *   @arg  Reset:                       None of the specified status flags is set.
 */
en_flag_status_t CAN_GetStatus(const M4_CAN_TypeDef *CANx, uint32_t u32Flag)
{
    uint8_t u8CFGSTAT;
    uint8_t u8RCTRL;
    uint8_t u8RTIE;
    uint8_t u8RTIF;
    uint8_t u8ERRINT;
    en_flag_status_t enFlag = Reset;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    u32Flag  &= CAN_FLAG_ALL;

    u8CFGSTAT = (uint8_t)(u32Flag);
    u8RCTRL   = (uint8_t)(u32Flag & CAN_FLAG_RB_OVF);
    u8RTIE    = (uint8_t)(u32Flag >> 8U);
    u8RTIF    = (uint8_t)(u32Flag >> 16U);
    u8ERRINT  = (uint8_t)(u32Flag >> 24U);

    u8CFGSTAT = READ_REG8_BIT(CANx->CFG_STAT, u8CFGSTAT);
    u8RCTRL   = READ_REG8_BIT(CANx->RCTRL, u8RCTRL);
    u8RTIE    = READ_REG8_BIT(CANx->RTIE, u8RTIE);
    u8RTIF    = READ_REG8_BIT(CANx->RTIF, u8RTIF);
    u8ERRINT  = READ_REG8_BIT(CANx->ERRINT, u8ERRINT);

    if ((u8CFGSTAT != 0U) || (u8RCTRL != 0U) || \
        (u8RTIE != 0U) || (u8RTIF != 0U) || (u8ERRINT != 0U))
    {
        enFlag = Set;
    }

    return enFlag;
}

/**
 * @brief  Clear the common flag's status.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32Flag                Status flag. Set this parameter to 0xFFFFFFFF to select all sataus flags of CAN.
 *                                      This parameter can be a value of @ref CAN_Common_Status_Flag
 *   @arg  CAN_FLAG_RB_OVF:             Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost.
 *   @arg  CAN_FLAG_TRANS_ABORTED:      Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *   @arg  CAN_FLAG_ERR_INT:            Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter \
 *                                      and the set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than \
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *   @arg  CAN_FLAG_STB_TRANS_OK:       Register bit RTIF.TSIF. STB was transmitted successfully.
 *   @arg  CAN_FLAG_PTB_TRANS_OK:       Register bit RTIF.TPIF. PTB was transmitted successfully.
 *   @arg  CAN_FLAG_RB_ALMOST_FULL:     Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_FLAG_RB_FIFO_FULL:       Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *   @arg  CAN_FLAG_RX_OVERRUN:         Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *   @arg  CAN_FLAG_RX_OK:              Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *   @arg  CAN_FLAG_BUS_ERR:            Register bit ERRINT.BEIF. Arbitration lost caused bus error.
 *   @arg  CAN_FLAG_ARB_LOST:           Register bit ERRINT.ALIF. Arbitration lost.
 *   @arg  CAN_FLAG_ERR_PASSIVE:        Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *   @arg  CAN_FLAG_ERR_PASSIVE_NODE:   Register bit ERRINT.EPASS. The node is an error-passive node.
 *   @arg  CAN_FLAG_REACH_WARN_LIMIT:   Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 * @retval None
 */
void CAN_ClrStatus(M4_CAN_TypeDef *CANx, uint32_t u32Flag)
{
    uint8_t u8RTIF;
    uint8_t u8ERRINT;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    u32Flag &= CAN_FLAG_CLR_MSK;
    u8RTIF   = (uint8_t)(u32Flag >> 16U);
    u8ERRINT = (uint8_t)(u32Flag >> 24U);

    if ((u32Flag & CAN_FLAG_RB_OVF) != 0U)
    {
        SET_REG8_BIT(CANx->RCTRL, CAN_RCTRL_RREL);
    }
    SET_REG8_BIT(CANx->RTIF, u8RTIF);
    SET_REG8_BIT(CANx->ERRINT, u8ERRINT);
}

/**
 * @brief  Get the value of status.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint32_t type value that includes the flowing status flags.
 *   @arg  CAN_FLAG_BUS_OFF:            Register bit CFG_STAT.BUSOFF. CAN bus off.
 *   @arg  CAN_FLAG_BUS_TX:             Register bit CFG_STAT.TACTIVE. CAN bus is transmitting.
 *   @arg  CAN_FLAG_BUS_RX:             Register bit CFG_STAT.RACTIVE. CAN bus is receiving.
 *   @arg  CAN_FLAG_RB_OVF:             Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost.
 *   @arg  CAN_FLAG_TB_FULL:            Register bit RTIE.TSFF. Transmit buffers are all full: \
 *                                      TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled. \
 *                                      TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.
 *   @arg  CAN_FLAG_TRANS_ABORTED:      Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *   @arg  CAN_FLAG_ERR_INT:            Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter and the \
 *                                      set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than \
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *   @arg  CAN_FLAG_STB_TRANS_OK:       Register bit RTIF.TSIF. STB was transmitted successfully.
 *   @arg  CAN_FLAG_PTB_TRANS_OK:       Register bit RTIF.TPIF. PTB was transmitted successfully.
 *   @arg  CAN_FLAG_RB_ALMOST_FULL:     Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_FLAG_RB_FIFO_FULL:       Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *   @arg  CAN_FLAG_RX_OVERRUN:         Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *   @arg  CAN_FLAG_RX_OK:              Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *   @arg  CAN_FLAG_BUS_ERR:            Register bit ERRINT.BEIF. Arbitration lost caused bus error.
 *   @arg  CAN_FLAG_ARB_LOST:           Register bit ERRINT.ALIF. Arbitration lost.
 *   @arg  CAN_FLAG_ERR_PASSIVE:        Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *   @arg  CAN_FLAG_ERR_PASSIVE_NODE:   Register bit ERRINT.EPASS. The node is an error-passive node.
 *   @arg  CAN_FLAG_REACH_WARN_LIMIT:   Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 */
uint32_t CAN_GetStatusVal(const M4_CAN_TypeDef *CANx)
{
    uint32_t u32RCTRL;
    uint32_t u32RTIE;
    uint32_t u32RTIF;
    uint32_t u32ERRINT;
    uint32_t u32RetVal;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    u32RetVal  = CANx->CFG_STAT;
    u32RCTRL   = CANx->RCTRL;
    u32RCTRL  &= CAN_FLAG_RB_OVF;
    u32RTIE    = CANx->RTIE;
    u32RTIF    = CANx->RTIF;
    u32ERRINT  = CANx->ERRINT;

    u32RetVal |= (u32RCTRL | (u32RTIE << 8U) | (u32RTIF << 16U) | (u32ERRINT << 24U));
    u32RetVal &= CAN_FLAG_ALL;

    return u32RetVal;
}

/**
 * @brief  Get status(full or empty) of transmit buffer.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of status of transmit buffer. It's can be a value of @ref CAN_TB_Status
 *   @arg  CAN_TB_STAT_EMPTY:           TTCAN is disabled(TTEN == 0): STB is empty.
 *                                      TTCAN is disabled(TTEN == 1) and transmit buffer is specified by TBPTR and TTPTR(TTTBM == 1):
 *                                      PTB and STB are both empty.
 *   @arg  CAN_TB_STAT_LESS_HALF:       TTEN == 0: STB is not less than half full;
 *                                      TTEN == 1 && TTTBM == 1: PTB and STB are neither empty.
 *   @arg  CAN_TB_STAT_MORE_HALF:       TTEN == 0: STB is more than half full;
 *                                      TTEN == 1 && TTTBM == 1: reserved value.
 *   @arg  CAN_TB_STAT_FULL             TTEN == 0: STB is full;
 *                                      TTEN == 1 && TTTBM == 1: PTB and STB are both full.
 */
uint8_t CAN_GetTBFullStatus(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (READ_REG8_BIT(CANx->TCTRL, CAN_TCTRL_TSSTAT));
}

/**
 * @brief  Get status(full or empty) of receive buffer.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of status of receive buffer. It's can be a value of @ref CAN_RB_Status
 *   @arg  CAN_RB_STAT_EMPTY:           Receive buffer(RB) is empty.
 *   @arg  CAN_RB_STAT_LESS_WARN_LIMIT: RB is not empty, but is less than almost full warning limit.
 *   @arg  CAN_RB_STAT_MORE_WARN_LIMIT: RB is not full, but is more than or equal to almost full warning limit.
 *   @arg  CAN_RB_STAT_FULL:            RB is full.
 */
uint8_t CAN_GetRBFullStatus(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (READ_REG8_BIT(CANx->TCTRL, CAN_RCTRL_RSTAT));
}

/**
 * @brief  Configures the specified CAN FD according to the specified parameters
 *         in the stc_can_fd_cfg_t type structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcCfg                Pointer to a stc_can_fd_cfg_t structure value that
 *                                      contains the configuration information for the CAN FD.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_FD_Config(M4_CAN_TypeDef *CANx, const stc_can_fd_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_FD_MODE(pstcCfg->u8CANFDMode));
        DDL_ASSERT(IS_CAN_TDC_CMD(pstcCfg->u8TDCCmd));
        DDL_ASSERT(IS_CAN_FD_SSP(pstcCfg->u8TDCSSP));

        DDL_ASSERT(IS_CAN_FBT_SEG1(pstcCfg->stcFBT.u32SEG1));
        DDL_ASSERT(IS_CAN_FBT_SEG2(pstcCfg->stcFBT.u32SEG2));
        DDL_ASSERT(IS_CAN_FBT_SJW(pstcCfg->stcFBT.u32SJW));
        DDL_ASSERT(IS_CAN_FBT_PRESC(pstcCfg->stcFBT.u32Prescaler));

        /* Specifies CAN FD ISO mode. */
        MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_FD_ISO, pstcCfg->u8CANFDMode);

        /*
         * Configures fast bit time.
         * Restrictions: u32SEG1 >= u32SEG2 + 1, u32SEG2 >= u32SJW.
         * TQ = u32Prescaler / CANClock.
         * Fast bit time = (u32SEG1 + u32SEG2) * TQ.
         */
        WRITE_REG32(CANx->FBT, ((pstcCfg->stcFBT.u32SEG1 - 2U) | \
                                ((pstcCfg->stcFBT.u32SEG2 - 1U) << CAN_FBT_F_SEG_2_POS) | \
                                ((pstcCfg->stcFBT.u32SJW - 1U) << CAN_FBT_F_SJW_POS)    | \
                                ((pstcCfg->stcFBT.u32Prescaler - 1U) << CAN_FBT_F_PRESC_POS)));

        /* Specifies the secondary sample point. Number of TQ. */
        MODIFY_REG8(CANx->TDC, CAN_TDC_SSPOFF, pstcCfg->u8TDCSSP);

        /* Enable or disable TDC. */
        MODIFY_REG8(CANx->TDC, CAN_TDC_TDCEN, pstcCfg->u8TDCCmd);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the CAN FD configuration structure.
 *         Based on 40MHz CAN clock, TQ clock is CAN clock divided by 1. \
 *         Bit rate 2Mbps, 1 bit time is 20TQs, primary sample point is 80%, \
 *         secondary sample point is 80%.
 * @param  [in]  pstcCfg                Pointer to a stc_can_fd_cfg_t structure value that
 *                                      contains the configuration information for the CAN FD.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t CAN_FD_StructInit(stc_can_fd_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        /*
         * u8TDCCmd: Enalbe(CAN_FD_TDC_ENABLE) or disable(CAN_FD_TDC_DISABLE) transmitter delay compensation.
         * u8TDCSSP: The position(TQs) of secondary sample point.
         *
         * Primary sample point: u32SEG1 / (u32SEG1 + u32SEG2) = 80%
         * Secondary sample point: u8TDCSSP / (u32SEG1 + u32SEG2) = 80%
         *
         * u32SEG1:      TQs of segment 1. Contains synchronization segment, \
         *               propagation time segment and phase buffer segment 1.
         * u32SEG2:      TQs of segment 2. Phase buffer segment 2.
         * u32SJW:       TQs of synchronization jump width.
         * u32Prescaler: Range [1, 256].
         */
        pstcCfg->u8CANFDMode = CAN_FD_MODE_BOSCH;
        pstcCfg->u8TDCCmd    = CAN_FD_TDC_ENABLE;
        pstcCfg->u8TDCSSP    = 16U;
        pstcCfg->stcFBT.u32SEG1 = 1U + 15U;
        pstcCfg->stcFBT.u32SEG2 = 4U;
        pstcCfg->stcFBT.u32SJW  = 4U;
        pstcCfg->stcFBT.u32Prescaler = 1U;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable CAN FD.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable CAN FD.
 *   @arg  Disable:                     Disable CAN FD.
 * @retval None
 */
void CAN_FD_Cmd(const M4_CAN_TypeDef *CANx, en_functional_state_t enNewState)
{
    uint32_t u32Addr;
    uint32_t u32BitPos = 0U;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (CANx == M4_CAN2)
    {
        u32BitPos = 1U;
    }
    u32Addr = (uint32_t)&M4_PERIC->CAN_SYCTLREG;
    BIT_BAND(u32Addr, u32BitPos) = (uint32_t)enNewState;
}

/**
 * @brief  Set a default value for the CAN TTC(time-triggered communication) configuration structure.
 * @param  [in]  pstcCfg                Pointer to a stc_can_ttc_cfg_t structure value that
 *                                      contains the configuration information for the CAN TTC.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t CAN_TTC_StructInit(stc_can_ttc_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u8TransBufMode   = CAN_TTC_TB_MODE_PTR;
        pstcCfg->u8NTUPrescaler   = CAN_TTC_NTU_PRESC_1;
        pstcCfg->u32RefMsgIDE     = 0U;
        pstcCfg->u32RefMsgID      = 0x0U;
        pstcCfg->u16TrigType      = CAN_TTC_TRIG_SSHOT_TRANS_TRIG;
        pstcCfg->u16TxEnWindow    = 16U;
        pstcCfg->u16TxTrigTime    = 0xFFFFU;
        pstcCfg->u16WatchTrigTime = 0xFFFFU;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures the specified CAN TTC(time-triggered communication) according to the specified parameters
 *         in the stc_can_ttc_cfg_t type structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcCfg                Pointer to a stc_can_ttc_cfg_t structure value that
 *                                      contains the configuration information for the CAN TTC.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t CAN_TTC_Config(M4_CAN_TypeDef *CANx, const stc_can_ttc_cfg_t *pstcCfg)
{
    uint32_t u32RefMsgID;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_TTC_TB_MODE(pstcCfg->u8TransBufMode));
        DDL_ASSERT(IS_CAN_TTC_NTU_PRESC(pstcCfg->u8NTUPrescaler));
        DDL_ASSERT(IS_CAN_IDE(pstcCfg->u32RefMsgIDE));
        DDL_ASSERT(IS_CAN_TTC_TRIG_TYPE(pstcCfg->u16TrigType));
        DDL_ASSERT(IS_CAN_TTC_TX_EN_WINDOW(pstcCfg->u16TxEnWindow));

        u32RefMsgID = pstcCfg->u32RefMsgID & ((uint32_t)(~CAN_REF_MSG_REF_IDE));

        /* Specifies transmission buffer mode. */
        MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_TTTBM, pstcCfg->u8TransBufMode);
        /* Specifies Tx_Enable window and trigger type. */
        WRITE_REG16(CANx->TRG_CFG, ((((uint32_t)pstcCfg->u16TxEnWindow-1U) << CAN_TRG_CFG_TEW_POS) | pstcCfg->u16TrigType));
        /* Specifies ID of reference message and its extension bit. */
        WRITE_REG32(CANx->REF_MSG, (((pstcCfg->u32RefMsgIDE << CAN_REF_MSG_REF_IDE_POS) | u32RefMsgID)));
        /* Specifies transmission trigger time. */
        WRITE_REG16(CANx->TT_TRIG, pstcCfg->u16TxTrigTime);
        /* Specifies watch trigger time. */
        WRITE_REG16(CANx->TT_WTRIG, pstcCfg->u16WatchTrigTime);
        /* Specifies NTU prescaler. */
        WRITE_REG8(CANx->TTCFG, pstcCfg->u8NTUPrescaler);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable time-triggered communication(TTC) of the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable TTC.
 *   @arg  Disable:                     Disable TTC.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_TTC_Cmd(M4_CAN_TypeDef *CANx, en_functional_state_t enNewState)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    u32Addr = (uint32_t)&CANx->TTCFG;
    BIT_BAND(u32Addr, CAN_TTCFG_TTEN_POS) = (uint32_t)enNewState;
}

/**
 * @brief  Specifies transmission buffer slot(TBS) which is going to be filled.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8SlotPtr              Transmit-trigger transmit buffer slot.
 *                                      This parameter can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             TBS pointer points to PTB.
 *   @arg  CAN_TTC_TBS_STB1:            TBS pointer points to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB2:            TBS pointer points to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB3:            TBS pointer points to STB slot 3.
 * @retval None
 */
void CAN_TTC_SetTBSToBeFilled(M4_CAN_TypeDef *CANx, uint8_t u8SlotPtr)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TTC_TBS(u8SlotPtr));
    MODIFY_REG8(CANx->TBSLOT, CAN_TBSLOT_TBPTR, u8SlotPtr);
}

/**
 * @brief  Marks the transmission buffer slot(TBS) as filled.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval None
 */
void CAN_TTC_SetTBSFilled(M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    SET_REG8_BIT(CANx->TBSLOT, CAN_TBSLOT_TBF);
}

/**
 * @brief  Specifies time-triggered communication(TTC) timer prescaler.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8NTUPrescaler         Time-triggered communication timer prescaler.
 *                                      This parameter can be a value of @ref CAN_TTC_NTU_Prescaler
 *   @arg  CAN_TTC_NTU_PRESC_1:         NTU is SBT bit time * 1.
 *   @arg  CAN_TTC_NTU_PRESC_2:         NTU is SBT bit time * 2.
 *   @arg  CAN_TTC_NTU_PRESC_4:         NTU is SBT bit time * 4.
 *   @arg  CAN_TTC_NTU_PRESC_8:         NTU is SBT bit time * 8.
 * @retval None
 */
void CAN_TTC_SetNTUPrescaler(M4_CAN_TypeDef *CANx, uint8_t u8NTUPrescaler)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TTC_NTU_PRESC(u8NTUPrescaler));
    MODIFY_REG8(CANx->TTCFG, CAN_TTCFG_T_PRESC, u8NTUPrescaler);
}

/**
 * @brief  Enable or disable the specified interrupts of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8IntType              Interrupt type of TTC.
 *                                      This parameter can be values of @ref CAN_TTC_Interrupt_Type
 *   @arg  CAN_TTC_INT_TTI:             Time trigger interrupt.
 *   @arg  CAN_TTC_INT_WTI:             Watch trigger interrupt.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified interrupts.
 *   @arg  Disable:                     Disable the specified interrupts.
 * @retval None
 */
void CAN_TTC_IntCmd(M4_CAN_TypeDef *CANx, uint8_t u8IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8IntType &= CAN_TTC_INT_ALL;
    if (enNewState == Enable)
    {
        SET_REG8_BIT(CANx->TTCFG, u8IntType);
    }
    else
    {
        CLEAR_REG8_BIT(CANx->TTCFG, u8IntType);
    }
}

/**
 * @brief  Get flag status of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8Flag                 Status flag of TTC.
 *                                      This parameter can be values of @ref CAN_TTC_Status_Flag
 *   @arg  CAN_TTC_FLAG_TTI:            Time trigger interrupt flag.
 *   @arg  CAN_TTC_FLAG_TEI:            Trigger error interrupt flag.
 *   @arg  CAN_TTC_FLAG_WTI:            Watch trigger interrupt flag.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         At least one of the specified flags is set.
 *   @arg  Reset:                       None of the specified flags is reset.
 */
en_flag_status_t CAN_TTC_GetStatus(const M4_CAN_TypeDef *CANx, uint8_t u8Flag)
{
    en_flag_status_t enFlag = Reset;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    if (READ_REG8_BIT(CANx->TTCFG, (u8Flag & (uint8_t)CAN_TTC_FLAG_ALL)) != 0U)
    {
        enFlag = Set;
    }

    return enFlag;
}

/**
 * @brief  Clear flag status of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8Flag                 Status flag of TTC.
 *                                      This parameter can be a value of @ref CAN_TTC_Status_Flag except CAN_TTC_FLAG_TEI.
 *   @arg  CAN_TTC_FLAG_TTI:            Time trigger interrupt flag.
 *   @arg  CAN_TTC_FLAG_WTI:            Watch trigger interrupt flag.
 * @retval None
 */
void CAN_TTC_ClrStatus(M4_CAN_TypeDef *CANx, uint8_t u8Flag)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    SET_REG8_BIT(CANx->TTCFG, (u8Flag & CAN_TTC_FLAG_CLR_MSK));
}

/**
 * @brief  Get the value of status of TTC.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value that includes the flowing status flags.
 *   @arg  CAN_TTC_FLAG_TTI:            Time trigger interrupt flag.
 *   @arg  CAN_TTC_FLAG_TEI:            Trigger error interrupt flag.
 *   @arg  CAN_TTC_FLAG_WTI:            Watch trigger interrupt flag.
 */
uint8_t CAN_TTC_GetStatusVal(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return READ_REG8_BIT(CANx->TTCFG, CAN_TTC_FLAG_ALL);
}

/**
 * @brief  Specifies reference message ID and IDE for time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32ID                  Reference message ID.
 * @retval None
 */
void CAN_TTC_SetRefMsgID(M4_CAN_TypeDef *CANx, uint32_t u32ID)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    u32ID &= (uint32_t)(~CAN_REF_MSG_REF_IDE);
    MODIFY_REG32(CANx->REF_MSG, CAN_REF_MSG_REF_ID, u32ID);
}

/**
 * @brief  Specifiy IDE of TTC(time-triggered communication) reference message.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32IDE                 IDE bit.
 *   @arg  0:                           Standard ID.
 *   @arg  1:                           Extended ID.
 * @retval None
 */
void CAN_TTC_SetRefMsgIDE(M4_CAN_TypeDef *CANx, uint32_t u32IDE)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_IDE(u32IDE));
    u32Addr = (uint32_t)&CANx->REF_MSG;
    BIT_BAND(u32Addr, CAN_REF_MSG_REF_IDE_POS) = u32IDE;
}

/**
 * @brief  Get reference message ID of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint32_t value of reference message ID.
 */
uint32_t CAN_TTC_GetRefMsgID(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (READ_REG32_BIT(CANx->REF_MSG, CAN_REF_MSG_REF_ID));
}

/**
 * @brief  Get reference message ID extension bit of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint32_t value of reference message IDE.
 *   @arg  0:                           Standard ID.
 *   @arg  1:                           Extended ID.
 */
uint32_t CAN_TTC_GetRefMsgIDE(const M4_CAN_TypeDef *CANx)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    u32Addr = (uint32_t)&CANx->REF_MSG;
    return BIT_BAND(u32Addr, CAN_REF_MSG_REF_IDE_POS);
}

/**
 * @brief  Specifies transmit-trigger transmit buffer slot(TBS) for time-triggered communication(TTC) of specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8TBSlotPtr            Transmit-trigger transmit buffer slot.
 *                                      This parameter can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             TBS pointer points to PTB.
 *   @arg  CAN_TTC_TBS_STB_S1:          TBS pointer points to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB_S2:          TBS pointer points to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB_S3:          TBS pointer points to STB slot 3.
 * @retval None
 */
void CAN_TTC_SetTxTrigTBS(M4_CAN_TypeDef *CANx, uint8_t u8TBSlotPtr)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TTC_TBS(u8TBSlotPtr));
    MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TTPTR, u8TBSlotPtr);
}

/**
 * @brief  Get transmit-trigger transmit buffer slot(TBS) of specified CAN unit's time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of transmit buffer slot pointer. It is can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             TBS pointer points to PTB.
 *   @arg  CAN_TTC_TBS_STB1:            TBS pointer points to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB2:            TBS pointer points to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB3:            TBS pointer points to STB slot 3.
 */
uint8_t CAN_TTC_GetTxTrigTBS(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (uint8_t)(READ_REG16_BIT(CANx->TRG_CFG, CAN_TRG_CFG_TTPTR));
}

/**
 * @brief  Specifies trigger type for time-triggered communication(TTC) of specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16TrigType            Time-triggered communication trigger type.
 *                                      This parameter can be a value of @ref CAN_TTC_Trigger_Type
 *   @arg  CAN_TTC_TRIG_IMMED_TRIG:          Immediate trigger for immediate transmission.
 *   @arg  CAN_TTC_TRIG_TIME_TRIG:           Time trigger for receive triggers.
 *   @arg  CAN_TTC_TRIG_SSHOT_TRANS_TRIG:    Single shot transmit trigger for exclusive time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_START_TRIG:    Transmit start trigger for merged arbitrating time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_STOP_TRIG:     Transmit stop trigger for merged arbitrating time windows.
 * @retval None
 */
void CAN_TTC_SetTrigType(M4_CAN_TypeDef *CANx, uint16_t u16TrigType)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TTC_TRIG_TYPE(u16TrigType));
    MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TTYPE, u16TrigType);
}

/**
 * @brief  Get trigger type of specified CAN unit's time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint16_t type value of TTC trigger type.
 *   @arg  CAN_TTC_TRIG_IMMED_TRIG:          Immediate trigger for immediate transmission.
 *   @arg  CAN_TTC_TRIG_TIME_TRIG:           Time trigger for receive triggers.
 *   @arg  CAN_TTC_TRIG_SSHOT_TRANS_TRIG:    Single shot transmit trigger for exclusive time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_START_TRIG:    Transmit start trigger for merged arbitrating time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_STOP_TRIG:     Transmit stop trigger for merged arbitrating time windows.
 */
uint16_t CAN_TTC_GetTrigType(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return READ_REG16_BIT(CANx->TRG_CFG, CAN_TRG_CFG_TTYPE);
}

/**
 * @brief  Specifies transmission enable window for single shot transmit trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16TxEnableWindow      Number of NTU. Time period within which the transmission of a message may be started.
 * @retval None
 */
void CAN_TTC_SetTxEnableWindow(M4_CAN_TypeDef *CANx, uint16_t u16TxEnableWindow)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TTC_TX_EN_WINDOW(u16TxEnableWindow));
    u16TxEnableWindow -= 1U;
    u16TxEnableWindow  = (uint16_t)((uint32_t)u16TxEnableWindow << CAN_TRG_CFG_TEW_POS);
    MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TEW, u16TxEnableWindow);
}

/**
 * @brief  Get transmit enable window of single shot transmit trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint16_t type value of Tx_Enable window.
 */
uint16_t CAN_TTC_GetTxEnableWindow(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return ((CANx->TRG_CFG >> CAN_TRG_CFG_TEW_POS) + 1U);
}

/**
 * @brief  Set transmission trigger time for timer-trigger communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16TxTrigTime          Transmission trigger time. Number of NTU.
 * @retval None
 */
void CAN_TTC_SetTxTrigTime(M4_CAN_TypeDef *CANx, uint16_t u16TxTrigTime)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    WRITE_REG16(CANx->TT_TRIG, u16TxTrigTime);
}

/**
 * @brief  Get watch trigger time of timer-trigger communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint16_t type value of cycle time.
 */
uint16_t CAN_TTC_GetTxTrigTime(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (CANx->TT_TRIG);
}

/**
 * @brief  Set cycle time for timer-trigger communication(TTC) watch-trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16WatchTrigTime       Watch trigger time. Number of NTU.
 * @retval None
 */
void CAN_TTC_SetWatchTrigTime(M4_CAN_TypeDef *CANx, uint16_t u16WatchTrigTime)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    WRITE_REG16(CANx->TT_WTRIG, u16WatchTrigTime);
}

/**
 * @brief  Get cycle time of timer-trigger communication(TTC) watch-trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint16_t type value of cycle time.
 */
uint16_t CAN_TTC_GetWatchTrigTime(const M4_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (CANx->TT_WTRIG);
}

/**
 * @brief  CAN bus transmits data.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcTx                 Points to a stc_can_tx_t structure type data which stores the frames to be transmitted.
 * @param  [in]  u8TxBufType            CAN transmit buffer type.
 *                                      This parameter can be a value of @ref CAN_Transmit_Buffer_Type
 *   @arg  CAN_BUF_PTB:                 Primary transmit buffer.
 *   @arg  CAN_BUF_STB:                 Secondary transmit buffer.
 * @param  [in]  u8STBTxCtrl            STB transmission control. If transmit via PTB, set u8STBTxCtrl to 0.
 *                                      This parameter can be a value of @ref CAN_STB_Trans_Control
 *   @arg  CAN_STB_TRANS_ALL:           Transmit all of STB slots.
 *   @arg  CAN_STB_TRANS_ONE:           Transmit one STB slot.
 * @param  [in]  u32Timeout             Timeout value. Set it as zero for transmit in interrupt-mode.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcTx == NULL.
 *   @arg  ErrorBufferFull:             The target transmit buffer is full.
 *   @arg  ErrorOperationInProgress:    The target transmit buffer is being transmitted.
 *   @arg  ErrorAddressAlignment:       Data address is not 4-byte aligned.
 *   @arg  ErrorTimeout:                Transmit timeout.
 *   @arg  Error:                       CAN bus transmission error.
 */
en_result_t CAN_TransData(M4_CAN_TypeDef *CANx, const stc_can_tx_t *pstcTx,
                          uint8_t u8TxBufType, uint8_t u8STBTxCtrl, uint32_t u32Timeout)
{
    uint32_t i;
    uint8_t u8DataSize;
    uint8_t u8WordLen;
    uint32_t u32Addr;
    uint32_t u32TimeCnt;
    uint32_t u32SrcDataAddr;
    uint32_t u32TBAddr;
    uint8_t au8TxEn[2U][2U] = {{CAN_TCMD_TPE, CAN_TCMD_TPE}, \
                               {CAN_TCMD_TSALL, CAN_TCMD_TSONE}};
    uint8_t au8Check[2U] = {CAN_RTIF_TPIF, CAN_RTIF_TSIF};
    uint8_t au8DLC2Size[2U][16U] =
    {
        {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U},
        {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U},
    };
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcTx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_TB_TYPE(u8TxBufType));
        DDL_ASSERT(IS_CAN_STB_TX_CTRL(u8STBTxCtrl));

        u32SrcDataAddr = (uint32_t)pstcTx->pu8Data;

        if ((READ_REG8_BIT(CANx->TCTRL, CAN_TB_STAT_FULL) == CAN_TB_STAT_FULL) && \
            (u8TxBufType == CAN_BUF_STB))
        {
            /* All STBs are full. */
            enRet = ErrorBufferFull;
        }
        else if ((READ_REG8_BIT(CANx->TCMD, CAN_TCMD_TPE) != 0U) && \
                 (u8TxBufType == CAN_BUF_PTB))
        {
            /* PTB is being transmitted. */
            enRet = ErrorOperationInProgress;
        }
        else if ((u32SrcDataAddr & 0x03UL) != 0U)
        {
            enRet = ErrorAddressAlignment;
        }
        else
        {
            u8DataSize = au8DLC2Size[pstcTx->FDF][pstcTx->DLC];
            u8WordLen  = u8DataSize / 4U;
            if ((u8DataSize % 4U) != 0U)
            {
                u8WordLen += 1U;
            }

            /* Specifies the transmit buffer, PTB or STB. */
            u32Addr = (uint32_t)&CANx->TCMD;
            BIT_BAND(u32Addr, CAN_TCMD_TBSEL_POS) = (uint32_t)u8TxBufType;

            u32TBAddr = (uint32_t)&CANx->TBUF;
            RW_MEM32(u32TBAddr) = pstcTx->u32ID;
            RW_MEM32(u32TBAddr + 4U) = pstcTx->u32Ctrl;

            i = 0U;
            u32TBAddr += 8U;
            while (i < u8WordLen)
            {
                RW_MEM32(u32TBAddr + i * 4U) = *(uint32_t *)u32SrcDataAddr;
                u32SrcDataAddr += 4U;
                i++;
            }

            if (u8TxBufType == CAN_BUF_STB)
            {
                /* After writes the data in transmit buffer(TB), sets the TSNEXT bit to indicate that the current \
                   STB slot has been filled, so that the hardware will point TB to the next STB slot. */
                SET_REG8_BIT(CANx->TCTRL, CAN_TCTRL_TSNEXT);
            }

            /* Enable transmission. */
            SET_REG8_BIT(CANx->TCMD, au8TxEn[u8TxBufType][u8STBTxCtrl]);

            if (u32Timeout == 0U)
            {
                enRet = Ok;
            }
            else
            {
                /* Check transmission. */
                u32TimeCnt = u32Timeout * (HCLK_VALUE / 10U / 1000U);
                enRet = ErrorTimeout;
                while (u32TimeCnt-- != 0U)
                {
                    if ((CAN_GetStatusVal(CANx) & CAN_FLAG_TX_ERR_MSK) != 0U)
                    {
                        enRet = Error;
                    }
                    else if (READ_REG8_BIT(CANx->RTIF, au8Check[u8TxBufType]) != 0U)
                    {
                        /* Clear the transmit-OK status flag. */
                        CANx->RTIF |= au8Check[u8TxBufType];
                        enRet = Ok;
                    }
                    else
                    {
                        /* rsvd */
                    }
                    if (enRet != ErrorTimeout)
                    {
                        break;
                    }
                }
            }
        }
    }

    return enRet;
}

/**
 * @brief  TTCAN transmits data. For single shot transmit trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcTx                 Points to a stc_can_tx_t structure type data which stores the frames to be transmitted.
 * @param  [in]  u8TBSlot               Transmit buffer pointer.
 *                                      This parameter can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             Point to PTB.
 *   @arg  CAN_TTC_TBS_STB1:            Point to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB2:            Point to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB3:            Point to STB slot 3.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcTx == NULL.
 *   @arg  ErrorBufferFull:             The target transmit buffer is full.
 *   @arg  ErrorAddressAlignment:       Data address is not 4-byte aligned.
 */
en_result_t CAN_TTC_TransData(M4_CAN_TypeDef *CANx, const stc_can_tx_t *pstcTx, uint8_t u8TBSlot)
{
    uint32_t i;
    uint8_t u8Tmp;
    uint8_t u8DataSize;
    uint8_t u8WordLen;
    uint32_t u32SrcDataAddr;
    uint32_t u32TBAddr;
    uint8_t au8DLC2Size[2U][16U] =
    {
        {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U},
        {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U},
    };
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcTx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));

        u32SrcDataAddr = (uint32_t)pstcTx->pu8Data;
        u8Tmp = CANx->TBSLOT;
        WRITE_REG8(CANx->TBSLOT, u8TBSlot);
        if (READ_REG8_BIT(CANx->TCTRL, CAN_TB_STAT_FULL) == CAN_TB_STAT_FULL)
        {
            enRet = ErrorBufferFull;
        }
        else if (READ_REG8_BIT(CANx->RTIE, CAN_RTIE_TSFF) != 0U)
        {
            WRITE_REG8(CANx->TBSLOT, CAN_TBSLOT_TBF|u8Tmp);
            WRITE_REG16(CANx->TT_TRIG, CANx->TT_TRIG);
            enRet = ErrorBufferFull;
        }
        else if ((u32SrcDataAddr & 0x03UL) != 0U)
        {
            enRet = ErrorAddressAlignment;
        }
        else
        {
            u8DataSize = au8DLC2Size[pstcTx->FDF][pstcTx->DLC];
            u8WordLen  = u8DataSize / 4U;
            if ((u8DataSize % 4U) != 0U)
            {
                u8WordLen += 1U;
            }

            u32TBAddr = (uint32_t)&CANx->TBUF;
            MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TTPTR, u8TBSlot);

            RW_MEM32(u32TBAddr) = pstcTx->u32ID;
            RW_MEM32(u32TBAddr + 4U) = pstcTx->u32Ctrl;

            i = 0U;
            u32TBAddr += 8U;
            while (i < u8WordLen)
            {
                RW_MEM32(u32TBAddr + i * 4U) = *(uint32_t *)u32SrcDataAddr;
                u32SrcDataAddr += 4U;
                i++;
            }
            /* Set buffer as filled. */
            SET_REG8_BIT(CANx->TBSLOT, CAN_TBSLOT_TBF);

            /* Write MSB of TT_TRIG to transmit. */
            WRITE_REG16(CANx->TT_TRIG, CANx->TT_TRIG);

            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  CAN bus receives data.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [out] pstcRx                 Points to a stc_can_rx_t structure type array which is used to \
 *                                      store the received frames.
 * @param  [out] pu8RxFrameCnt          Address to store the number of frames received.
 *                                      If you do not need it, set it as NULL.\
 * @param  [in] u8RxFrameBufLength      The length of the buffer which is used to store the received frames.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -pstcRx == NULL.
 *                                     -u8RxFrameBufLength == 0U.
 */
en_result_t CAN_ReceiveData(M4_CAN_TypeDef *CANx, stc_can_rx_t pstcRx[], uint8_t *pu8RxFrameCnt, uint8_t u8RxFrameBufLength)
{
    uint32_t i;
    uint8_t u8DataSize;
    uint8_t u8WordLen;
    uint8_t u8RxFrameCnt = 0U;
    uint32_t u32DestDataAddr;
    uint32_t u32RBAddr;
    en_result_t enRet;
    uint8_t au8DLC2Size[2U][16U] =
    {
        {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U},
        {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U},
    };

    if ((pstcRx == NULL) || (u8RxFrameBufLength == 0U))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        enRet = Ok;
        while (READ_REG8_BIT(CANx->RCTRL, CAN_RCTRL_RSTAT) != CAN_RB_STAT_EMPTY)
        {
            u32RBAddr = (uint32_t)&CANx->RBUF;
            pstcRx[u8RxFrameCnt].u32ID   = RW_MEM32(u32RBAddr);
            pstcRx[u8RxFrameCnt].u32Ctrl = RW_MEM32(u32RBAddr + 4U);

            u8DataSize = au8DLC2Size[pstcRx[u8RxFrameCnt].FDF][pstcRx[u8RxFrameCnt].DLC];
            u8WordLen  = u8DataSize / 4U;
            if ((u8DataSize % 4U) != 0U)
            {
                u8WordLen += 1U;
            }

            u32DestDataAddr = (uint32_t)pstcRx[u8RxFrameCnt].pu8Data;
            if (!IS_ADDRESS_ALIGN_WORD(u32DestDataAddr))
            {
                enRet = ErrorAddressAlignment;
                break;
            }
            i = 0U;
            u32RBAddr += 8U;
            while (i < u8WordLen)
            {
                *(uint32_t *)u32DestDataAddr = RW_MEM32(u32RBAddr + i * 4U);
                u32DestDataAddr += 4U;
                i++;
            }

            /* Set RB to point to the next RB slot. */
            SET_REG8_BIT(CANx->RCTRL, CAN_RCTRL_RREL);
            u8RxFrameCnt++;
            if (u8RxFrameCnt >= u8RxFrameBufLength)
            {
                break;
            }
        }

        if (pu8RxFrameCnt != NULL)
        {
            *pu8RxFrameCnt = u8RxFrameCnt;
        }
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_CAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
