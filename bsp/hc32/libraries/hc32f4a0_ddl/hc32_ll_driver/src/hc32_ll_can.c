/**
 *******************************************************************************
 * @file  hc32_ll_can.c
 * @brief This file provides firmware functions to manage the CAN.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Deleted redundant comments
                                    API fixed: CAN_FillTxFrame(), CAN_GetStatus(), CAN_ClearStatus()
   2023-06-30       CDT             Added 3 APIs for local-reset.Refine local function CAN_ReadRxBuf(), CAN_WriteTxBuf()
                                    Modify typo
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
#include "hc32_ll_can.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_CAN CAN
 * @brief CAN Driver Library
 * @{
 */

#if (LL_CAN_ENABLE == DDL_ON)

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
 * @defgroup CAN_Check_Parameters_Validity CAN Check Parameters Validity
 * @{
 */
#define IS_CAN_BIT_MASK(x, mask)    (((x) != 0U) && (((x) | (mask)) == (mask)))

#define IS_CAN_FUNC_EN(x, en)       (((x) == 0U) || ((x) == (en)))

#define IS_CAN_UNIT(x)              (((x) == CM_CAN1) || ((x) == CM_CAN2))
#define IS_CAN_FD_UNIT(x)           ((x) == CM_CAN2)

#define IS_CAN_BIT_TIME_PRESC(x)    (((x) >= 1U) && ((x) <= 256U))

#define IS_CAN_WORK_MD(x)           ((x) <= CAN_WORK_MD_ELB_SILENT)

#define IS_CAN_TX_BUF_TYPE(x)       (((x) == CAN_TX_BUF_PTB) || ((x) == CAN_TX_BUF_STB))

#define IS_CAN_PTB_SINGLESHOT_TX(x) IS_CAN_FUNC_EN(x, CAN_PTB_SINGLESHOT_TX_ENABLE)

#define IS_CAN_STB_SINGLESHOT_TX(x) IS_CAN_FUNC_EN(x, CAN_STB_SINGLESHOT_TX_ENABLE)

#define IS_CAN_STB_PRIO_MD(x)       IS_CAN_FUNC_EN(x, CAN_STB_PRIO_MD_ENABLE)

#define IS_CAN_TX_REQ(x)            IS_CAN_BIT_MASK(x, CAN_TX_REQ_STB_ONE|CAN_TX_REQ_STB_ALL|CAN_TX_REQ_PTB)

#define IS_CAN_RX_ALL_FRAME(x)      IS_CAN_FUNC_EN(x, CAN_RX_ALL_FRAME_ENABLE)

#define IS_CAN_RX_OVF_MD(x)         (((x) == CAN_RX_OVF_SAVE_NEW) || ((x) == CAN_RX_OVF_DISCARD_NEW))

#define IS_CAN_SELF_ACK(x)          IS_CAN_FUNC_EN(x, CAN_SELF_ACK_ENABLE)

#define IS_CAN_INT(x)               IS_CAN_BIT_MASK(x, CAN_INT_ALL)

#define IS_CAN_FLAG(x)              IS_CAN_BIT_MASK(x, CAN_FLAG_ALL)

#define IS_CAN_ID(ide, x)                                                      \
(   (((ide) == 1U) && (((x) | 0x1FFFFFFFUL) == 0x1FFFFFFFUL))   ||             \
    (((ide) == 0U) && (((x) | 0x7FFUL) == 0x7FFUL)))

#define IS_CAN_ID_MASK(x)           (((x) | 0x1FFFFFFFUL) == 0x1FFFFFFFUL)

#define IS_CAN_IDE(x)               (((x) == 0U) || ((x) == 1U))

#define IS_CAN_FILTER(x)            IS_CAN_BIT_MASK(x, CAN_FILTER_ALL)

#define IS_CAN_RX_WARN(x)           (((x) >= CAN_RX_WARN_MIN) && ((x) <= CAN_RX_WARN_MAX))

#define IS_CAN_ERR_WARN(x)          ((x) < 16U)

#define IS_CAN_FD_MD(x)             (((x) == CAN_FD_MD_BOSCH) || ((x) == CAN_FD_MD_ISO))

#define IS_CAN_FD_TDC(x)            IS_CAN_FUNC_EN(x, CAN_FD_TDC_ENABLE)

#define IS_CAN_FD_SSP(x)            ((x) < 128U)

#define IS_TTCAN_TX_BUF_MD(x)       (((x) == CAN_TTC_TX_BUF_MD_CAN) || ((x) == CAN_TTC_TX_BUF_MD_TTCAN))

#define IS_TTCAN_TX_BUF_SEL(x)      ((x) <= CAN_TTC_TX_BUF_STB3)

#define IS_TTCAN_INT(x)             IS_CAN_BIT_MASK(x, CAN_TTC_INT_ALL)

#define IS_TTCAN_FLAG(x)            IS_CAN_BIT_MASK(x, CAN_TTC_FLAG_ALL)

#define IS_TTCAN_TX_EN_WINDOW(x)    (((x) > 0U) && ((x) <= 16U))

#define IS_TTCAN_NTU_PRESCALER(x)                                              \
(   ((x) == CAN_TTC_NTU_PRESCALER1)             ||                             \
    ((x) == CAN_TTC_NTU_PRESCALER2)             ||                             \
    ((x) == CAN_TTC_NTU_PRESCALER4)             ||                             \
    ((x) == CAN_TTC_NTU_PRESCALER8))

#define IS_TTCAN_TRIG_TYPE(x)                                                  \
(   ((x) == CAN_TTC_TRIG_IMMED_TRIG)            ||                             \
    ((x) == CAN_TTC_TRIG_TIME_TRIG)             ||                             \
    ((x) == CAN_TTC_TRIG_SINGLESHOT_TX_TRIG)    ||                             \
    ((x) == CAN_TTC_TRIG_TX_START_TRIG)         ||                             \
    ((x) == CAN_TTC_TRIG_TX_STOP_TRIG))

#define IS_CAN_ID_TYPE(x)                                                      \
(   ((x) == CAN_ID_STD_EXT)                     ||                             \
    ((x) == CAN_ID_STD)                         ||                             \
    ((x) == CAN_ID_EXT))

#define IS_CAN_SBT(seg1, seg2, sjw)                                            \
(   (((seg1) >= 2U) && ((seg1) <= 65U))         &&                             \
    (((seg2) >= 1U) && ((seg2) <= 8U))          &&                             \
    (((sjw) >= 1U) && ((sjw) <= 16U))           &&                             \
    ((seg1) >= ((seg2) + 1U))                   &&                             \
    ((seg2) >= (sjw)))

#define IS_CAN_FD_SBT(seg1, seg2, sjw)                                         \
(   (((seg1) >= 2U) && ((seg1) <= 65U))         &&                             \
    (((seg2) >= 1U) && ((seg2) <= 32U))         &&                             \
    (((sjw) >= 1U) && ((sjw) <= 16U))           &&                             \
    ((seg1) >= ((seg2) + 1U))                   &&                             \
    ((seg2) >= (sjw)))

#define IS_CAN_FD_FBT(seg1, seg2, sjw)                                         \
(   (((seg1) >= 2U) && ((seg1) <= 17U))         &&                             \
    (((seg2) >= 1U) && ((seg2) <= 8U))          &&                             \
    (((sjw) >= 1U) && ((sjw) <= 8U))            &&                             \
    ((seg1) >= ((seg2) + 1U))                   &&                             \
    ((seg2) >= (sjw)))

/* FDF bit check */
#define IS_CAN20_FDF(x)                     ((x) == 0U)

/**
 * @}
 */

/**
 * @defgroup CAN_Miscellaneous_Macros CAN Miscellaneous Macros
 * @{
 */
#define CAN_RX_BUF_NUM                      (8U)

#define CAN_RX_WARN_MIN                     (1U)
#define CAN_RX_WARN_MAX                     (CAN_RX_BUF_NUM)

#define CAN_ERRINT_FLAG_MASK                (CAN_ERRINT_BEIF | CAN_ERRINT_ALIF | CAN_ERRINT_EPIF)

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

/**
 * @defgroup CAN_Local_Variables CAN Local Variables
 * @{
 */
const static uint8_t m_au8DLC2WordSize[16U] = {
    0U, 1U, 1U, 1U, 1U, 2U, 2U, 2U, 2U, 3U, 4U, 5U, 6U, 8U, 12U, 16U
};

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CAN_Local_Functions CAN Local Functions
 * @{
 */

#if defined __DEBUG
/**
 * @brief  Initialization parameter check.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  pstcCanInit            Pointer to a stc_can_init_t structure value that
 *                                      contains the configuration information for the CAN.
 * @retval None
 */
static void CAN_InitParameterCheck(CM_CAN_TypeDef *CANx, const stc_can_init_t *pstcCanInit)
{
    stc_canfd_config_t *pstcCanFd = pstcCanInit->pstcCanFd;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_WORK_MD(pstcCanInit->u8WorkMode));
    DDL_ASSERT(IS_CAN_PTB_SINGLESHOT_TX(pstcCanInit->u8PTBSingleShotTx));
    DDL_ASSERT(IS_CAN_STB_SINGLESHOT_TX(pstcCanInit->u8STBSingleShotTx));
    DDL_ASSERT(IS_CAN_STB_PRIO_MD(pstcCanInit->u8STBPrioMode));
    DDL_ASSERT(IS_CAN_RX_WARN(pstcCanInit->u8RxWarnLimit));
    DDL_ASSERT(IS_CAN_ERR_WARN(pstcCanInit->u8ErrorWarnLimit));
    DDL_ASSERT(IS_CAN_FILTER(pstcCanInit->u16FilterSelect));
    DDL_ASSERT(IS_CAN_RX_ALL_FRAME(pstcCanInit->u8RxAllFrame));
    DDL_ASSERT(IS_CAN_RX_OVF_MD(pstcCanInit->u8RxOvfMode));
    DDL_ASSERT(IS_CAN_SELF_ACK(pstcCanInit->u8SelfAck));

    if (pstcCanFd != NULL) {
        DDL_ASSERT(IS_CAN_FD_UNIT(CANx));
        DDL_ASSERT(IS_CAN_BIT_TIME_PRESC(pstcCanInit->stcBitCfg.u32Prescaler));
        DDL_ASSERT(IS_CAN_FD_SBT(pstcCanInit->stcBitCfg.u32TimeSeg1,
                                 pstcCanInit->stcBitCfg.u32TimeSeg2,
                                 pstcCanInit->stcBitCfg.u32SJW));

        DDL_ASSERT(IS_CAN_BIT_TIME_PRESC(pstcCanFd->stcBitCfg.u32Prescaler));
        DDL_ASSERT(IS_CAN_FD_FBT(pstcCanFd->stcBitCfg.u32TimeSeg1,
                                 pstcCanFd->stcBitCfg.u32TimeSeg2,
                                 pstcCanFd->stcBitCfg.u32SJW));

        DDL_ASSERT(IS_CAN_FD_MD(pstcCanFd->u8Mode));
        DDL_ASSERT(IS_CAN_FD_TDC(pstcCanFd->u8TDC));
        DDL_ASSERT(IS_CAN_FD_SSP(pstcCanFd->u8SSPOffset));
    } else {
        DDL_ASSERT(IS_CAN_BIT_TIME_PRESC(pstcCanInit->stcBitCfg.u32Prescaler));
        DDL_ASSERT(IS_CAN_SBT(pstcCanInit->stcBitCfg.u32TimeSeg1,
                              pstcCanInit->stcBitCfg.u32TimeSeg2,
                              pstcCanInit->stcBitCfg.u32SJW));
    }
}
#endif

/**
 * @brief  Specifies work mode for the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8WorkMode             Work mode of CAN.
 *                                      This parameter can be a value of @ref CAN_Work_Mode
 *   @arg  CAN_WORK_MD_NORMAL:          Normal work mode.
 *   @arg  CAN_WORK_MD_SILENT:          Silent work mode. Prohibit data transmission.
 *   @arg  CAN_WORK_MD_ILB:             Internal loop back mode, just for self-test while developing.
 *   @arg  CAN_WORK_MD_ELB:             External loop back mode, just for self-test while developing.
 *   @arg  CAN_WORK_MD_ELB_SILENT:      External loop back silent mode, just for self-test while developing.
 *                                      It is forbidden to respond to received frames and error frames,
 *                                      but data can be transmitted.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
static void CAN_SetWorkMode(CM_CAN_TypeDef *CANx, uint8_t u8WorkMode)
{
    uint8_t u8CFGSTAT = 0U;
    uint8_t u8TCMD    = 0U;

    switch (u8WorkMode) {
        case CAN_WORK_MD_SILENT:
            u8TCMD    = CAN_TCMD_LOM;
            break;
        case CAN_WORK_MD_ILB:
            u8CFGSTAT = CAN_CFG_STAT_LBMI;
            break;
        case CAN_WORK_MD_ELB:
            u8CFGSTAT = CAN_CFG_STAT_LBME;
            break;
        case CAN_WORK_MD_ELB_SILENT:
            u8TCMD    = CAN_TCMD_LOM;
            u8CFGSTAT = CAN_CFG_STAT_LBME;
            break;
        case CAN_WORK_MD_NORMAL:
        default:
            break;
    }

    MODIFY_REG8(CANx->CFG_STAT, CAN_CFG_STAT_LBMI | CAN_CFG_STAT_LBME, u8CFGSTAT);
    MODIFY_REG8(CANx->TCMD, CAN_TCMD_LOM, u8TCMD);
}

/**
 * @brief  Configures acceptance filter. Set ID and ID mask for the specified acceptance filters.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u16FilterSelect        Acceptance filters selection.
 *                                      This parameter can be values of @ref CAN_Acceptance_Filter
 * @param  [in]  pstcFilter             Pointer to a stc_can_filter_config_t structure type array which contains ID and ID mask
 *                                      values for the acceptance filters specified by parameter u16FilterSelect.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       If one the following cases matches:
 *                                      - u16FilterSelect == 0U.
 *                                      - pstcFilter == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
static int32_t CAN_FilterConfig(CM_CAN_TypeDef *CANx, uint16_t u16FilterSelect,
                                const stc_can_filter_config_t *pstcFilter)
{
    uint8_t u8FilterAddr = 0U;
    uint8_t i = 0U;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    if ((u16FilterSelect != 0U) && (pstcFilter != NULL)) {
        while (u16FilterSelect != 0U) {
            if ((u16FilterSelect & 0x1U) != 0U) {
                DDL_ASSERT(IS_CAN_ID_TYPE(pstcFilter[i].u32IDType));
                DDL_ASSERT(IS_CAN_ID_MASK(pstcFilter[i].u32IDMask));
                WRITE_REG8(CANx->ACFCTRL, u8FilterAddr);
                WRITE_REG32(CANx->ACF, pstcFilter[i].u32ID);
                SET_REG8_BIT(CANx->ACFCTRL, CAN_ACFCTRL_SELMASK);
                WRITE_REG32(CANx->ACF, pstcFilter[i].u32IDMask | pstcFilter[i].u32IDType);
                i++;
            }
            u16FilterSelect >>= 1U;
            u8FilterAddr++;
        }

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Configures the specified CAN FD according to the specified parameters
 *         in a @ref stc_canfd_config_t structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  pstcCanFd              Pointer to a @ref stc_canfd_config_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcCanFd == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
static int32_t CAN_FD_Config(CM_CAN_TypeDef *CANx, const stc_canfd_config_t *pstcCanFd)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcCanFd != NULL) {
        /* Specifies CAN FD ISO mode. */
        MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_FD_ISO, pstcCanFd->u8Mode);
        /**
         * Configures fast bit time.
         * Restrictions: u32TimeSeg1 >= u32TimeSeg2 + 1, u32TimeSeg2 >= u32SJW.
         * TQ = u32Prescaler / CANClock.
         * Fast bit time = (u32TimeSeg1 + u32TimeSeg2) * TQ.
         */
        WRITE_REG32(CANx->FBT, ((pstcCanFd->stcBitCfg.u32TimeSeg1 - 2U) | \
                                ((pstcCanFd->stcBitCfg.u32TimeSeg2 - 1U) << CAN_FBT_F_SEG_2_POS) | \
                                ((pstcCanFd->stcBitCfg.u32SJW - 1U) << CAN_FBT_F_SJW_POS) | \
                                ((pstcCanFd->stcBitCfg.u32Prescaler - 1U) << CAN_FBT_F_PRESC_POS)));

        /* Specifies the secondary sample point. Number of TQ.
           Enable or disable TDC. */
        WRITE_REG8(CANx->TDC, pstcCanFd->u8TDC | pstcCanFd->u8SSPOffset);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Write TX buffer register in bytes.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  pstcTx                 Pointer to a @ref stc_can_tx_frame_t structure.
 * @retval None
 */
static void CAN_WriteTxBuf(CM_CAN_TypeDef *CANx, const stc_can_tx_frame_t *pstcTx)
{
    uint8_t i;
    uint8_t u8WordLen;
    __IO uint32_t *reg32TBUF;
    uint32_t *pu32TxData = (uint32_t *)((uint32_t)(&pstcTx->au8Data[0U]));

    reg32TBUF = (__IO uint32_t *)((uint32_t)&CANx->TBUF);
    reg32TBUF[0U] = pstcTx->u32ID;
    reg32TBUF[1U] = pstcTx->u32Ctrl;

    u8WordLen = m_au8DLC2WordSize[pstcTx->DLC];
    if ((pstcTx->FDF == 0U) && (u8WordLen > 2U)) {
        /* Maximum size of data payload is 8 bytes(2words) for classical CAN frame. */
        u8WordLen = 2U;
    }

    for (i = 0U; i < u8WordLen; i++) {
        reg32TBUF[2U + i] = pu32TxData[i];
    }
}

/**
 * @brief  Read RX buffer register in bytes.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  pstcRx                 Pointer to a @ref stc_can_rx_frame_t structure.
 * @retval None
 */
static void CAN_ReadRxBuf(const CM_CAN_TypeDef *CANx, stc_can_rx_frame_t *pstcRx)
{
    __I uint32_t *reg32RBUF;
    uint8_t i;
    uint8_t u8WordLen;
    uint32_t *pu32RxData = (uint32_t *)((uint32_t)(&pstcRx->au8Data[0U]));

    reg32RBUF = (__I uint32_t *)((uint32_t)&CANx->RBUF);
    pstcRx->u32ID   = reg32RBUF[0U];
    pstcRx->u32Ctrl = reg32RBUF[1U];

    if (pstcRx->IDE == 0U) {
        pstcRx->u32ID &= 0x7FFUL;
    } else {
        pstcRx->u32ID &= 0x1FFFFFFFUL;
    }

    u8WordLen = m_au8DLC2WordSize[pstcRx->DLC];
    if ((pstcRx->FDF == 0U) && (u8WordLen > 2U)) {
        /* Maximum size of data payload is 8 bytes(2words) for classical CAN frame. */
        u8WordLen = 2U;
    }

    for (i = 0U; i < u8WordLen; i++) {
        pu32RxData[i] = reg32RBUF[2U + i];
    }
}

/**
 * @}
 */

/**
 * @defgroup CAN_Global_Functions CAN Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified CAN peripheral according to the specified parameters
 *         in the structure pstcCanInit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  pstcCanInit            Pointer to a @ref stc_can_init_t structure value that
 *                                      contains the configuration information for the CAN.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcCanInit == NULL
 */
int32_t CAN_Init(CM_CAN_TypeDef *CANx, const stc_can_init_t *pstcCanInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcCanInit != NULL) {
#if defined __DEBUG
        CAN_InitParameterCheck(CANx, pstcCanInit);
#endif
        /* Local reset. */
        SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
        /* Configures nominal bit time. */
        WRITE_REG32(CANx->SBT, ((pstcCanInit->stcBitCfg.u32TimeSeg1 - 2U) | \
                                ((pstcCanInit->stcBitCfg.u32TimeSeg2 - 1U) << CAN_SBT_S_SEG_2_POS) | \
                                ((pstcCanInit->stcBitCfg.u32SJW - 1U) << CAN_SBT_S_SJW_POS) | \
                                ((pstcCanInit->stcBitCfg.u32Prescaler - 1U) << CAN_SBT_S_PRESC_POS)));
        /* Enable or disable STB priority mode. */
        MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_TSMODE, pstcCanInit->u8STBPrioMode);
        /* Configures acceptance filters. */
        (void)CAN_FilterConfig(CANx, pstcCanInit->u16FilterSelect, pstcCanInit->pstcFilter);

        /* Configures CAN-FD if needed. */
        if (pstcCanInit->pstcCanFd != NULL) {
            (void)CAN_FD_Config(CANx, pstcCanInit->pstcCanFd);
        }

        /* CAN enters normal communication mode. */
        CLR_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
        /* Specifies CAN work mode. */
        CAN_SetWorkMode(CANx, pstcCanInit->u8WorkMode);
        /* Enable or disable single shot transmission mode of PTB and STB. */
        MODIFY_REG8(CANx->CFG_STAT, \
                    (CAN_CFG_STAT_TPSS | CAN_CFG_STAT_TSSS), \
                    (pstcCanInit->u8PTBSingleShotTx | pstcCanInit->u8STBSingleShotTx));
        /* Specifies receive buffer almost full warning limit. Specifies error warning limit. */
        WRITE_REG8(CANx->LIMIT, ((pstcCanInit->u8RxWarnLimit << CAN_LIMIT_AFWL_POS) | pstcCanInit->u8ErrorWarnLimit));

        /* Enable or disable RX all frames(include frames with error).
           Specifies receive overflow mode. In case of a full rx buffer when a new message is received.
           Enable or disable self-acknowledge. */
        WRITE_REG8(CANx->RCTRL, pstcCanInit->u8RxAllFrame | \
                   pstcCanInit->u8RxOvfMode  | \
                   pstcCanInit->u8SelfAck);
        /* Enable acceptance filters that configured before. */
        WRITE_REG16(CANx->ACFEN, pstcCanInit->u16FilterSelect);
        /* Configures TTCAN if needed. */
        if (pstcCanInit->pstcCanTtc != NULL) {
            (void)CAN_TTC_Config(CANx, pstcCanInit->pstcCanTtc);
        }

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set each @ref stc_can_init_t field to a default value.
 *         Classical CAN bit time configuration:
 *         Based on 40MHz CAN clock, TQ clock is CAN clock divided by 4.
 *         Bit rate 500Kbps, 1 bit time is 20TQs, sample point is 80%.
 *         CAN-FD bit time configuration:
 *         Based on 40MHz CAN clock, TQ clock is CAN clock divided by 1.
 *         Bit rate 2Mbps, 1 bit time is 20TQs, primary sample point is 80%,
 *         secondary sample point is 80%.
 * @param  [in]  pstcCanInit            Pointer to a @ref stc_can_init_t structure
 *                                      whose fields will be set to default values.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcCanInit == NULL.
 */
int32_t CAN_StructInit(stc_can_init_t *pstcCanInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcCanInit != NULL) {
        /**
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
        pstcCanInit->stcBitCfg.u32Prescaler = 4U;
        pstcCanInit->stcBitCfg.u32TimeSeg1  = 16U;
        pstcCanInit->stcBitCfg.u32TimeSeg2  = 4U;
        pstcCanInit->stcBitCfg.u32SJW       = 2U;
        pstcCanInit->pstcFilter        = NULL;
        pstcCanInit->u16FilterSelect   = 0U;
        pstcCanInit->u8WorkMode        = CAN_WORK_MD_NORMAL;
        pstcCanInit->u8PTBSingleShotTx = CAN_PTB_SINGLESHOT_TX_DISABLE;
        pstcCanInit->u8STBSingleShotTx = CAN_STB_SINGLESHOT_TX_DISABLE;
        pstcCanInit->u8STBPrioMode     = CAN_STB_PRIO_MD_DISABLE;
        pstcCanInit->u8RxWarnLimit     = CAN_RX_WARN_MAX;
        pstcCanInit->u8ErrorWarnLimit  = 7U;
        pstcCanInit->u8RxAllFrame      = CAN_RX_ALL_FRAME_DISABLE;
        pstcCanInit->u8RxOvfMode       = CAN_RX_OVF_DISCARD_NEW;
        pstcCanInit->u8SelfAck         = CAN_SELF_ACK_DISABLE;
        pstcCanInit->pstcCanTtc        = NULL;
        pstcCanInit->pstcCanFd = NULL;

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Deinitialize the specified CAN peripheral registers to their default reset values.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval None
 */
void CAN_DeInit(CM_CAN_TypeDef *CANx)
{
    uint8_t i;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    CLR_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
    for (i = 0U; i < 2U; i++) {
        WRITE_REG8(CANx->CFG_STAT, 0x80U);
        WRITE_REG8(CANx->TCMD, 0x00U);
        WRITE_REG8(CANx->TCTRL, 0x90U);
        WRITE_REG8(CANx->RCTRL, 0x10U);
        WRITE_REG8(CANx->RTIE, 0xFEU);
        WRITE_REG8(CANx->RTIF, 0xFFU);
        WRITE_REG8(CANx->ERRINT, 0xD5U);
        WRITE_REG8(CANx->LIMIT, 0x1BU);
        WRITE_REG32(CANx->SBT, 0x01020203UL);
        WRITE_REG8(CANx->RECNT, 0x00U);
        WRITE_REG8(CANx->TECNT, 0x00U);
        WRITE_REG8(CANx->ACFCTRL, 0x00U);
        WRITE_REG8(CANx->TBSLOT, 0x00U);
        WRITE_REG8(CANx->TTCFG, 0xD8U);
        WRITE_REG16(CANx->TRG_CFG, 0x00U);
        WRITE_REG16(CANx->TT_TRIG, 0x00U);
        WRITE_REG16(CANx->TT_WTRIG, 0x00U);
        WRITE_REG16(CANx->ACFEN, 0x01U);
        WRITE_REG32(CANx->FBT, 0x01020203UL);
        WRITE_REG8(CANx->TDC, 0x00U);

        SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
    }
}

/**
 * @brief  Enable or disable specified interrupts.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u32IntType             Interrupt of CAN.
 *                                      This parameter can be values of @ref CAN_Interrupt_Type
 *   @arg  CAN_INT_ERR_INT:             Register bit RTIE.EIE. Error interrupt.
 *   @arg  CAN_INT_STB_TX:              Register bit RTIE.TSIE. STB was transmitted successfully.
 *   @arg  CAN_INT_PTB_TX:              Register bit RTIE.TPIE. PTB was transmitted successfully.
 *   @arg  CAN_INT_RX_BUF_WARN:         Register bit RTIE.RAFIE. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_INT_RX_BUF_FULL:         Register bit RTIE.RFIE. The FIFO of receive buffer is full.
 *   @arg  CAN_INT_RX_OVERRUN:          Register bit RTIE.ROIE. Receive buffers are full and there is a further message to be stored.
 *   @arg  CAN_INT_RX:                  Register bit RTIE.RIE. Received a valid data frame or remote frame.
 *   @arg  CAN_INT_BUS_ERR:             Register bit ERRINT.BEIE. Arbitration lost caused bus error
 *   @arg  CAN_INT_ARBITR_LOST:         Register bit ERRINT.ALIE. Arbitration lost.
 *   @arg  CAN_INT_ERR_PASSIVE:         Register bit ERRINT.EPIE. A change from error-passive to error-active or error-active to error-passive has occurred.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CAN_IntCmd(CM_CAN_TypeDef *CANx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint8_t u8RTIE;
    uint8_t u8ERRINT;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8RTIE   = (uint8_t)u32IntType;
    u8ERRINT = (uint8_t)(u32IntType >> 8U);

    if (enNewState == ENABLE) {
        SET_REG8_BIT(CANx->RTIE, u8RTIE);
        SET_REG8_BIT(CANx->ERRINT, u8ERRINT);
    } else {
        CLR_REG8_BIT(CANx->RTIE, u8RTIE);
        CLR_REG8_BIT(CANx->ERRINT, u8ERRINT);
    }
}

/**
 * @brief  Fills transmit frame.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8TxBufType            CAN transmit buffer type.
 *                                      This parameter can be a value of @ref CAN_Tx_Buf_Type
 * @param  [in]  pstcTx                 Pointer to a @ref stc_can_tx_frame_t structure.
 *   @arg  CAN_TX_BUF_PTB:              Primary transmit buffer.
 *   @arg  CAN_TX_BUF_STB:              Secondary transmit buffer.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTx == NULL.
 *           - LL_ERR_BUF_FULL:         The specified transmit buffer is full.
 *           - LL_ERR_BUSY:             The specified transmit buffer is being transmitted.
 */
int32_t CAN_FillTxFrame(CM_CAN_TypeDef *CANx, uint8_t u8TxBufType, const stc_can_tx_frame_t *pstcTx)
{
    uint8_t u8RTIE;
    uint8_t u8TCTRL;
    uint32_t u32RegAddr;
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TX_BUF_TYPE(u8TxBufType));

    if (pstcTx != NULL) {
        if (CANx == CM_CAN1) {
            DDL_ASSERT(IS_CAN20_FDF(pstcTx->FDF));
        }
        if (u8TxBufType == CAN_TX_BUF_PTB) {
            if (READ_REG8_BIT(CANx->TCMD, CAN_TCMD_TPE) != 0U) {
                /* PTB is being transmitted. */
                i32Ret = LL_ERR_BUSY;
            }
        } else {
            if (READ_REG8_BIT(CANx->TCMD, (CAN_TCMD_TSONE | CAN_TCMD_TSALL)) != 0U) {
                /* STB is being transmitted. */
                i32Ret = LL_ERR_BUSY;
            } else {
                u8RTIE  = READ_REG8(CANx->RTIE);
                u8TCTRL = READ_REG8(CANx->TCTRL);
                if (((u8RTIE & CAN_RTIE_TSFF) == CAN_RTIE_TSFF) || \
                    ((u8TCTRL & CAN_TCTRL_TSSTAT) == CAN_TCTRL_TSSTAT)) {
                    /* All STBs are filled. */
                    i32Ret = LL_ERR_BUF_FULL;
                }
            }
        }

        if (i32Ret == LL_OK) {
            /* Assert ID */
            DDL_ASSERT(IS_CAN_ID(pstcTx->IDE, pstcTx->u32ID));

            /* Specifies the transmit buffer, PTB or STB. */
            u32RegAddr = (uint32_t)&CANx->TCMD;
            WRITE_REG32(PERIPH_BIT_BAND(u32RegAddr, CAN_TCMD_TBSEL_POS), u8TxBufType);

            CAN_WriteTxBuf(CANx, pstcTx);

            if (u8TxBufType == CAN_TX_BUF_STB) {
                /* After writes the data in transmit buffer(TB), sets the TSNEXT bit to indicate that the current
                   STB slot has been filled, so that the hardware will point TB to the next STB slot. */
                SET_REG8_BIT(CANx->TCTRL, CAN_TCTRL_TSNEXT);
            }
        }
    } else {
        i32Ret = LL_ERR_INVD_PARAM;
    }

    return i32Ret;
}

/**
 * @brief  Starts transmission.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8TxRequest            The transmit buffer to be transmitted.
 *                                      This parameter can be values of @ref CAN_Tx_Request
 *   @arg  CAN_TX_REQ_STB_ONE:          Transmit one STB frame.
 *   @arg  CAN_TX_REQ_STB_ALL:          Transmit all STB frames.
 *   @arg  CAN_TX_REQ_PTB:              Transmit PTB frame.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_StartTx(CM_CAN_TypeDef *CANx, uint8_t u8TxRequest)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TX_REQ(u8TxRequest));
    SET_REG8_BIT(CANx->TCMD, u8TxRequest);
}

/**
 * @brief  Abort the transmission of the specified transmit buffer.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8TxBufType            The transmit buffer to be aborted.
 *                                      This parameter can be a value of @ref CAN_Tx_Buf_Type
 *   @arg  CAN_TX_BUF_PTB:              Abort PTB transmission.
 *   @arg  CAN_TX_BUF_STB:              Abort STB transmission.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_AbortTx(CM_CAN_TypeDef *CANx, uint8_t u8TxBufType)
{
    uint8_t au8Abort[] = {CAN_TCMD_TPA, CAN_TCMD_TSA};

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_TX_BUF_TYPE(u8TxBufType));
    SET_REG8_BIT(CANx->TCMD, au8Abort[u8TxBufType]);
}

/**
 * @brief  Get one received frame.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [out] pstcRx                 Pointer to a @ref stc_can_rx_frame_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Get one received frame successfully.
 *           - LL_ERR_BUF_EMPTY:        Receive buffer is empty, and no frame has been read.
 *           - LL_ERR_INVD_PARAM:       pstcRx == NULL.
 */
int32_t CAN_GetRxFrame(CM_CAN_TypeDef *CANx, stc_can_rx_frame_t *pstcRx)
{
    int32_t i32Ret = LL_ERR_BUF_EMPTY;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    if (pstcRx == NULL) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        if (READ_REG8_BIT(CANx->RCTRL, CAN_RCTRL_RSTAT) != CAN_RX_BUF_EMPTY) {
            CAN_ReadRxBuf(CANx, pstcRx);
            /* Set RB to point to the next RB slot. */
            SET_REG8_BIT(CANx->RCTRL, CAN_RCTRL_RREL);

            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/** Request a local-reset. The some register (e.g for node configuration) can only be modified if RESET=1.
 *  Bit RESET forces several components to a reset state, see the reference manual for details.
 * @brief
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval None
 */
void CAN_EnterLocalReset(CM_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
}

/** Exit the local-reset state. A CAN node will participate in CAN communication after RESET is switched to 0 after 11 CAN bit times.
 * @brief
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval None
 */
void CAN_ExitLocalReset(CM_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    CLR_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
}

/** Check whether CAN is in the local-reset state.
 * @brief
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t CAN_GetLocalResetStatus(CM_CAN_TypeDef *CANx)
{
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    if (READ_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET) != 0U) {
        /* The CAN is in local-reset state */
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Get the status of specified flag.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u32Flag                CAN status flag.
 *                                      This parameter can be a value of @ref CAN_Status_Flag
 *   @arg  CAN_FLAG_BUS_OFF:            Register bit CFG_STAT.BUSOFF. CAN bus off.
 *   @arg  CAN_FLAG_TX_GOING:           Register bit CFG_STAT.TACTIVE. CAN bus is transmitting.
 *   @arg  CAN_FLAG_RX_GOING:           Register bit CFG_STAT.RACTIVE. CAN bus is receiving.
 *   @arg  CAN_FLAG_RX_BUF_OVF:         Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost.
 *   @arg  CAN_FLAG_TX_BUF_FULL:        Register bit RTIE.TSFF. Transmit buffers are all full:
 *                                      TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled.
 *                                      TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.
 *   @arg  CAN_FLAG_TX_ABORTED:         Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *   @arg  CAN_FLAG_ERR_INT:            Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter and the
 *                                      set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *   @arg  CAN_FLAG_STB_TX:             Register bit RTIF.TSIF. STB was transmitted successfully.
 *   @arg  CAN_FLAG_PTB_TX:             Register bit RTIF.TPIF. PTB was transmitted successfully.
 *   @arg  CAN_FLAG_RX_BUF_WARN:        Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_FLAG_RX_BUF_FULL:        Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *   @arg  CAN_FLAG_RX_OVERRUN:         Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *   @arg  CAN_FLAG_RX:                 Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *   @arg  CAN_FLAG_BUS_ERR:            Register bit ERRINT.BEIF. In case of an error, KOER and the error counters get updated. BEIF gets set if BEIE is enabled
 *                                      and the other error interrupt flags will act accordingly.
 *   @arg  CAN_FLAG_ARBITR_LOST:        Register bit ERRINT.ALIF. Arbitration lost.
 *   @arg  CAN_FLAG_ERR_PASSIVE:        Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *   @arg  CAN_FLAG_ERR_PASSIVE_NODE:   Register bit ERRINT.EPASS. The node is an error-passive node.
 *   @arg  CAN_FLAG_TEC_REC_WARN:       Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t CAN_GetStatus(const CM_CAN_TypeDef *CANx, uint32_t u32Flag)
{
    uint8_t u8CFGSTAT;
    uint8_t u8RCTRL;
    uint8_t u8RTIE;
    uint8_t u8RTIF;
    uint8_t u8ERRINT;
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_FLAG(u32Flag));

    u8CFGSTAT = (uint8_t)(u32Flag & 0x7UL);
    u8RCTRL   = (uint8_t)(u32Flag & CAN_FLAG_RX_BUF_OVF);
    u8RTIE    = (uint8_t)(u32Flag >> 8U);
    u8RTIF    = (uint8_t)(u32Flag >> 16U);
    u8ERRINT  = (uint8_t)(u32Flag >> 24U);

    u8CFGSTAT = READ_REG8_BIT(CANx->CFG_STAT, u8CFGSTAT);
    u8RCTRL   = READ_REG8_BIT(CANx->RCTRL, u8RCTRL);
    u8RTIE    = READ_REG8_BIT(CANx->RTIE, u8RTIE);
    u8RTIF    = READ_REG8_BIT(CANx->RTIF, u8RTIF);
    u8ERRINT  = READ_REG8_BIT(CANx->ERRINT, u8ERRINT);

    if ((u8CFGSTAT != 0U) || (u8RCTRL != 0U) || \
        (u8RTIE != 0U) || (u8RTIF != 0U) || (u8ERRINT != 0U)) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of specified flags.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u32Flag                CAN status flag.
 *                                      This parameter can be values of @ref CAN_Status_Flag
 *   @arg  CAN_FLAG_TX_ABORTED:         Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *   @arg  CAN_FLAG_ERR_INT:            Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter
 *                                      and the set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *   @arg  CAN_FLAG_STB_TX:             Register bit RTIF.TSIF. STB was transmitted successfully.
 *   @arg  CAN_FLAG_PTB_TX:             Register bit RTIF.TPIF. PTB was transmitted successfully.
 *   @arg  CAN_FLAG_RX_BUF_WARN:        Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_FLAG_RX_BUF_FULL:        Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *   @arg  CAN_FLAG_RX_OVERRUN:         Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *   @arg  CAN_FLAG_RX:                 Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *   @arg  CAN_FLAG_BUS_ERR:            Register bit ERRINT.BEIF. In case of an error, KOER and the error counters get updated. BEIF gets set if BEIE is enabled
 *                                      and the other error interrupt flags will act accordingly.
 *   @arg  CAN_FLAG_ARBITR_LOST:        Register bit ERRINT.ALIF. Arbitration lost.
 *   @arg  CAN_FLAG_ERR_PASSIVE:        Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *   @arg  CAN_FLAG_ERR_PASSIVE_NODE:   Register bit ERRINT.EPASS. The node is an error-passive node.
 *   @arg  CAN_FLAG_TEC_REC_WARN:       Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 * @retval None
 */
void CAN_ClearStatus(CM_CAN_TypeDef *CANx, uint32_t u32Flag)
{
    uint8_t u8RTIF;
    uint8_t u8ERRINT;
    uint8_t u8Reg;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_FLAG(u32Flag));

    u32Flag &= CAN_FLAG_CLR_ALL;
    u8RTIF   = (uint8_t)(u32Flag >> 16U);
    u8ERRINT = (uint8_t)(u32Flag >> 24U);

    WRITE_REG8(CANx->RTIF, u8RTIF);

    u8Reg  = READ_REG8(CANx->ERRINT);
    u8Reg &= (uint8_t)(~CAN_ERRINT_FLAG_MASK);
    u8Reg |= u8ERRINT;
    WRITE_REG8(CANx->ERRINT, u8Reg);
}

/**
 * @brief  Get the value of CAN status.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval An uint32_t type value that includes the flowing status flags.
 *         - CAN_FLAG_BUS_OFF:          Register bit CFG_STAT.BUSOFF. CAN bus off.
 *         - CAN_FLAG_TX_GOING:         Register bit CFG_STAT.TACTIVE. CAN bus is transmitting.
 *         - CAN_FLAG_RX_GOING:         Register bit CFG_STAT.RACTIVE. CAN bus is receiving.
 *         - CAN_FLAG_RX_BUF_OVF:       Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost.
 *         - CAN_FLAG_TX_BUF_FULL:      Register bit RTIE.TSFF. Transmit buffers are all full:
 *                                      TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled.
 *                                      TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.
 *         - CAN_FLAG_TX_ABORTED:       Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *         - CAN_FLAG_ERR_INT:          Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter and the
 *                                      set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *         - CAN_FLAG_STB_TX:           Register bit RTIF.TSIF. STB was transmitted successfully.
 *         - CAN_FLAG_PTB_TX:           Register bit RTIF.TPIF. PTB was transmitted successfully.
 *         - CAN_FLAG_RX_BUF_WARN:      Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *         - CAN_FLAG_RX_BUF_FULL:      Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *         - CAN_FLAG_RX_OVERRUN:       Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *         - CAN_FLAG_RX:               Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *         - CAN_FLAG_BUS_ERR:          Register bit ERRINT.BEIF. In case of an error, KOER and the error counters get updated. BEIF gets set if BEIE is enabled
 *                                      and the other error interrupt flags will act accordingly.
 *         - CAN_FLAG_ARBITR_LOST:      Register bit ERRINT.ALIF. Arbitration lost.
 *         - CAN_FLAG_ERR_PASSIVE:      Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *         - CAN_FLAG_ERR_PASSIVE_NODE: Register bit ERRINT.EPASS. The node is an error-passive node.
 *         - CAN_FLAG_TEC_REC_WARN:     Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 */
uint32_t CAN_GetStatusValue(const CM_CAN_TypeDef *CANx)
{
    uint32_t u32RCTRL;
    uint32_t u32RTIE;
    uint32_t u32RTIF;
    uint32_t u32ERRINT;
    uint32_t u32RetVal;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    u32RetVal  = CANx->CFG_STAT;
    u32RCTRL   = CANx->RCTRL;
    u32RCTRL  &= CAN_FLAG_RX_BUF_OVF;
    u32RTIE    = CANx->RTIE;
    u32RTIF    = CANx->RTIF;
    u32ERRINT  = CANx->ERRINT;

    u32RetVal |= (u32RCTRL | (u32RTIE << 8U) | (u32RTIF << 16U) | (u32ERRINT << 24U));
    u32RetVal &= CAN_FLAG_ALL;

    return u32RetVal;
}

/**
 * @brief  Get the information of CAN errors.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [out] pstcErr                Pointer to a @ref stc_can_error_info_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcErr == NULL.
 */
int32_t CAN_GetErrorInfo(const CM_CAN_TypeDef *CANx, stc_can_error_info_t *pstcErr)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    if (pstcErr != NULL) {
        pstcErr->u8ArbitrLostPos = READ_REG8_BIT(CANx->EALCAP, CAN_EALCAP_ALC);
        pstcErr->u8ErrorType     = READ_REG8_BIT(CANx->EALCAP, CAN_EALCAP_KOER) >> CAN_EALCAP_KOER_POS;
        pstcErr->u8RxErrorCount  = READ_REG8(CANx->RECNT);
        pstcErr->u8TxErrorCount  = READ_REG8(CANx->TECNT);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Get status(full or empty) of transmit buffer.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval An uint8_t type value of status of transmit buffer. It can be a value of @ref CAN_Tx_Buf_Status
 *     - CAN_TX_BUF_EMPTY:              TTCAN is disabled(TTEN == 0): STB is empty.
 *                                      TTCAN is disabled(TTEN == 1) and transmit buffer is specified by TBPTR and TTPTR(TTTBM == 1):
 *                                      PTB and STB are both empty.
 *     - CAN_TX_BUF_NOT_MORE_THAN_HALF: TTEN == 0: STB is not less than half full;
 *                                      TTEN == 1 && TTTBM == 1: PTB and STB are neither empty.
 *     - CAN_TX_BUF_MORE_THAN_HALF:     TTEN == 0: STB is more than half full;
 *                                      TTEN == 1 && TTTBM == 1: reserved value.
 *     - CAN_TX_BUF_FULL:               TTEN == 0: STB is full;
 *                                      TTEN == 1 && TTTBM == 1: PTB and STB are both full.
 */
uint8_t CAN_GetTxBufStatus(const CM_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (READ_REG8_BIT(CANx->TCTRL, CAN_TCTRL_TSSTAT));
}

/**
 * @brief  Get status(full or empty) of receive buffer.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval An uint8_t type value of status of receive buffer. It can be a value of @ref CAN_Rx_Buf_Status
 *          - CAN_RX_BUF_EMPTY:         Receive buffer is empty.
 *          - CAN_RX_BUF_NOT_WARN:      Receive buffer is not empty, but is less than almost full warning limit.
 *          - CAN_RX_BUF_WARN:          Receive buffer is not full, but is more than or equal to almost full warning limit.
 *          - CAN_RX_BUF_FULL:          Receive buffer is full.
 */
uint8_t CAN_GetRxBufStatus(const CM_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return (READ_REG8_BIT(CANx->RCTRL, CAN_RCTRL_RSTAT));
}

/**
 * @brief  Enable or disable the specified acceptance filters.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u16FilterSelect        Acceptance filters selection.
 *                                      This parameter can be values of @ref CAN_Acceptance_Filter
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CAN_FilterCmd(CM_CAN_TypeDef *CANx, uint16_t u16FilterSelect, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_FILTER(u16FilterSelect));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(CANx->ACFEN, u16FilterSelect);
    } else {
        CLR_REG16_BIT(CANx->ACFEN, u16FilterSelect);
    }
}

/**
 * @brief  Set receive buffer full warning limit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in] u8RxWarnLimit:          Receive buffer full warning limit.
 *                                      When the number of received frames reaches the value specified by
 *                                      parameter 'u8RxWarnLimit', register bit RTIF.RAFIF set and the
 *                                      interrupt occurred if it was enabled.
 * @retval None
 */
void CAN_SetRxWarnLimit(CM_CAN_TypeDef *CANx, uint8_t u8RxWarnLimit)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_RX_WARN(u8RxWarnLimit));
    MODIFY_REG8(CANx->LIMIT, CAN_LIMIT_AFWL, u8RxWarnLimit << CAN_LIMIT_AFWL_POS);
}

/**
 * @brief  Set error warning limit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8ErrorWarnLimit       Programmable error warning limit. Range is [0, 15].
 *                                      Error warning limit = (u8ErrorWarnLimit + 1) * 8.
 * @retval None
 */
void CAN_SetErrorWarnLimit(CM_CAN_TypeDef *CANx, uint8_t u8ErrorWarnLimit)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_CAN_ERR_WARN(u8ErrorWarnLimit));
    MODIFY_REG8(CANx->LIMIT, CAN_LIMIT_EWL, u8ErrorWarnLimit);
}

/**
 * @brief  Set each @ref stc_canfd_config_t field to a default value.
 *         Based on 40MHz CAN clock, TQ clock is CAN clock divided by 1.
 *         Bit rate 2Mbps, 1 bit time is 20TQs, primary sample point is 80%,
 *         secondary sample point is 80%.
 * @param  [in]  pstcCanFd              Pointer to a @ref stc_canfd_config_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcCanFd == NULL.
 * @note 1. CAN-FD is only available on these part numbers: HC32F4A0TIHB, HC32F4A0SITB, HC32F4A0SGTB.
 * @note 2. CAN2 supports CAN-FD.
 */
int32_t CAN_FD_StructInit(stc_canfd_config_t *pstcCanFd)
{
    /**
     * u8TDC: Enable(CAN_FD_TDC_ENABLE) or disable(CAN_FD_TDC_DISABLE) transmitter delay compensation.
     * u8SSPOffset: The position(TQs) of secondary sample point.
     *
     * Primary sample point: u32TimeSeg1 / (u32TimeSeg1 + u32TimeSeg2) = 80%
     * Secondary sample point: u8SSPOffset / (u32TimeSeg1 + u32TimeSeg2) = 80%
     *
     * u32TimeSeg1: TQs of segment 1. Contains synchronization segment,
     *              propagation time segment and phase buffer segment 1.
     * u32TimeSeg2: TQs of segment 2(Phase buffer segment 2).
     * u32SJW: TQs of synchronization jump width.
     * u32Prescaler: Range [1, 256].
     */

    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcCanFd != NULL) {
        pstcCanFd->stcBitCfg.u32Prescaler = 1U;
        pstcCanFd->stcBitCfg.u32TimeSeg1  = 16U;
        pstcCanFd->stcBitCfg.u32TimeSeg2  = 4U;
        pstcCanFd->stcBitCfg.u32SJW       = 4U;
        pstcCanFd->u8Mode                 = CAN_FD_MD_ISO;
        pstcCanFd->u8TDC                  = CAN_FD_TDC_ENABLE;
        pstcCanFd->u8SSPOffset            = 16U;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set each @ref stc_can_ttc_config_t field to a default value.
 * @param  [in]  pstcCanTtc             Pointer to a @ref stc_can_ttc_config_t structure value that
 *                                      contains the configuration information for TTCAN.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcCanTtc == NULL.
 */
int32_t CAN_TTC_StructInit(stc_can_ttc_config_t *pstcCanTtc)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcCanTtc != NULL) {
        pstcCanTtc->u8NTUPrescaler      = CAN_TTC_NTU_PRESCALER1;
        pstcCanTtc->u32RefMsgID         = 0x0UL;
        pstcCanTtc->u32RefMsgIDE        = 0U;
        pstcCanTtc->u8TxBufMode         = CAN_TTC_TX_BUF_MD_TTCAN;
        pstcCanTtc->u16TriggerType      = CAN_TTC_TRIG_SINGLESHOT_TX_TRIG;
        pstcCanTtc->u16TxEnableWindow   = 16U;
        pstcCanTtc->u16TxTriggerTime    = 0xFFFFU;
        pstcCanTtc->u16WatchTriggerTime = 0xFFFFU;

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Configures the specified TTCAN according to the specified parameters
 *         in @ref stc_can_ttc_config_t type structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  pstcCanTtc             Pointer to a @ref stc_can_ttc_config_t structure value that
 *                                      contains the configuration information for TTCAN.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcCanTtc == NULL.
 */
int32_t CAN_TTC_Config(CM_CAN_TypeDef *CANx, const stc_can_ttc_config_t *pstcCanTtc)
{
    uint32_t u32RefMsgID;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_CAN_UNIT(CANx));

    if (pstcCanTtc != NULL) {
        DDL_ASSERT(IS_TTCAN_TX_BUF_MD(pstcCanTtc->u8TxBufMode));
        DDL_ASSERT(IS_TTCAN_NTU_PRESCALER(pstcCanTtc->u8NTUPrescaler));
        DDL_ASSERT(IS_CAN_ID(pstcCanTtc->u32RefMsgIDE, pstcCanTtc->u32RefMsgID));
        DDL_ASSERT(IS_TTCAN_TRIG_TYPE(pstcCanTtc->u16TriggerType));
        DDL_ASSERT(IS_TTCAN_TX_EN_WINDOW(pstcCanTtc->u16TxEnableWindow));

        u32RefMsgID = pstcCanTtc->u32RefMsgID & ((uint32_t)(~CAN_REF_MSG_REF_IDE));
        /* Specifies transmission buffer mode. */
        MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_TTTBM, pstcCanTtc->u8TxBufMode);
        /* Specifies Tx_Enable window and trigger type. */
        WRITE_REG16(CANx->TRG_CFG, pstcCanTtc->u16TriggerType |
                    ((pstcCanTtc->u16TxEnableWindow - 1U) << CAN_TRG_CFG_TEW_POS));
        /* Specifies ID of reference message and its extension bit. */
        WRITE_REG32(CANx->REF_MSG, (((pstcCanTtc->u32RefMsgIDE << CAN_REF_MSG_REF_IDE_POS) | u32RefMsgID)));
        /* Specifies transmission trigger time. */
        WRITE_REG16(CANx->TT_TRIG, pstcCanTtc->u16TxTriggerTime);
        /* Specifies watch trigger time. */
        WRITE_REG16(CANx->TT_WTRIG, pstcCanTtc->u16WatchTriggerTime);
        /* Specifies NTU prescaler. */
        MODIFY_REG8(CANx->TTCFG, CAN_TTCFG_T_PRESC, pstcCanTtc->u8NTUPrescaler);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable the specified interrupts of TTCAN.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8IntType              Interrupt of TTCAN.
 *                                      This parameter can be values of @ref TTCAN_Interrupt_Type
 *   @arg  CAN_TTC_INT_TIME_TRIG:       Time trigger interrupt.
 *   @arg  CAN_TTC_INT_WATCH_TRIG:      Watch trigger interrupt.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CAN_TTC_IntCmd(CM_CAN_TypeDef *CANx, uint8_t u8IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_TTCAN_INT(u8IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG8_BIT(CANx->TTCFG, u8IntType);
    } else {
        CLR_REG8_BIT(CANx->TTCFG, u8IntType);
    }
}

/**
 * @brief  Enable or disable TTCAN of the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note Call this function when CFG_STAT.RESET is 0.
 */
void CAN_TTC_Cmd(CM_CAN_TypeDef *CANx, en_functional_state_t enNewState)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&CANx->TTCFG;
    WRITE_REG32(PERIPH_BIT_BAND(u32Addr, CAN_TTCFG_TTEN_POS), enNewState);
}

/**
 * @brief  Get status of the specified TTCAN flag.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8Flag                 Status flag of TTCAN.
 *                                      This parameter can be values of @ref TTCAN_Status_Flag
 *   @arg  CAN_TTC_FLAG_TIME_TRIG:      Time trigger interrupt flag.
 *   @arg  CAN_TTC_FLAG_TRIG_ERR:       Trigger error interrupt flag.
 *   @arg  CAN_TTC_FLAG_WATCH_TRIG:     Watch trigger interrupt flag.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t CAN_TTC_GetStatus(const CM_CAN_TypeDef *CANx, uint8_t u8Flag)
{
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_TTCAN_FLAG(u8Flag));

    if (READ_REG8_BIT(CANx->TTCFG, (u8Flag & CAN_TTC_FLAG_ALL)) != 0U) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of TTCAN flags.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8Flag                 Status flag of TTCAN.
 *                                      This parameter can be a value of @ref TTCAN_Status_Flag except CAN_TTC_FLAG_TRIG_ERR.
 *   @arg  CAN_TTC_FLAG_TIME_TRIG:      Time trigger interrupt flag.
 *   @arg  CAN_TTC_FLAG_WATCH_TRIG:     Watch trigger interrupt flag.
 * @retval None
 */
void CAN_TTC_ClearStatus(CM_CAN_TypeDef *CANx, uint8_t u8Flag)
{
    uint8_t u8Reg;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_TTCAN_FLAG(u8Flag));

    u8Reg   = READ_REG8(CANx->TTCFG);
    u8Reg  &= (uint8_t)(~CAN_TTC_FLAG_ALL);
    u8Reg  |= u8Flag;
    WRITE_REG8(CANx->TTCFG, u8Reg);
}

/**
 * @brief  Get the status value of TTCAN.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @retval An uint8_t type value that includes the flowing status flags.
 *         - CAN_TTC_FLAG_TIME_TRIG:    Time trigger interrupt flag.
 *         - CAN_TTC_FLAG_TRIG_ERR:     Trigger error interrupt flag.
 *         - CAN_TTC_FLAG_WATCH_TRIG:   Watch trigger interrupt flag.
 */
uint8_t CAN_TTC_GetStatusValue(const CM_CAN_TypeDef *CANx)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    return READ_REG8_BIT(CANx->TTCFG, CAN_TTC_FLAG_ALL);
}

/**
 * @brief  Specifies trigger type of TTCAN.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u16TriggerType         TTCAN trigger type.
 *                                      This parameter can be a value of @ref TTCAN_Trigger_Type
 *   @arg  CAN_TTC_TRIG_IMMED_TRIG:     Immediate trigger for immediate transmission.
 *   @arg  CAN_TTC_TRIG_TIME_TRIG:      Time trigger for receive triggers.
 *   @arg  CAN_TTC_TRIG_SINGLESHOT_TX_TRIG: Single shot transmit trigger for exclusive time windows.
 *   @arg  CAN_TTC_TRIG_TX_START_TRIG:  Transmit start trigger for merged arbitrating time windows.
 *   @arg  CAN_TTC_TRIG_TX_STOP_TRIG:   Transmit stop trigger for merged arbitrating time windows.
 * @retval None
 */
void CAN_TTC_SetTriggerType(CM_CAN_TypeDef *CANx, uint16_t u16TriggerType)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_TTCAN_TRIG_TYPE(u16TriggerType));
    MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TTYPE, u16TriggerType);
}

/**
 * @brief  Specifies transmit enable window time of TTCAN.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u16TxEnableWindow      Number of NTU. Time period within which the transmit of a message may be started.
 * @retval None
 */
void CAN_TTC_SetTxEnableWindow(CM_CAN_TypeDef *CANx, uint16_t u16TxEnableWindow)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_TTCAN_TX_EN_WINDOW(u16TxEnableWindow));
    MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TEW, (u16TxEnableWindow - 1U) << CAN_TRG_CFG_TEW_POS);
}

/**
 * @brief  Specifies transmit trigger time of TTCAN.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u16TxTriggerTime       Transmit trigger time(number of NTU).
 * @retval None
 */
void CAN_TTC_SetTxTriggerTime(CM_CAN_TypeDef *CANx, uint16_t u16TxTriggerTime)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    WRITE_REG16(CANx->TT_TRIG, u16TxTriggerTime);
}

/**
 * @brief  TTCAN specifies watch-trigger time.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u16WatchTriggerTime    Watch trigger time(number of NTU).
 * @retval None
 */
void CAN_TTC_SetWatchTriggerTime(CM_CAN_TypeDef *CANx, uint16_t u16WatchTriggerTime)
{
    DDL_ASSERT(IS_CAN_UNIT(CANx));
    WRITE_REG16(CANx->TT_WTRIG, u16WatchTriggerTime);
}

/**
 * @brief  TTCAN fill transmit frame.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [in]  u8CANTTCTxBuf          TTCAN transmit buffer selection.
 *                                      This parameter can be a value of @ref TTCAN_Tx_Buf_Sel
 * @param  [in]  pstcTx                 Pointer to a @ref stc_can_tx_frame_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTx == NULL.
 *           - LL_ERR_BUF_FULL:         The target transmit buffer is full.
 */
int32_t CAN_TTC_FillTxFrame(CM_CAN_TypeDef *CANx, uint8_t u8CANTTCTxBuf, const stc_can_tx_frame_t *pstcTx)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_CAN_UNIT(CANx));
    DDL_ASSERT(IS_TTCAN_TX_BUF_SEL(u8CANTTCTxBuf));

    if (pstcTx != NULL) {
        DDL_ASSERT(IS_CAN20_FDF(pstcTx->FDF));

        if (READ_REG8_BIT(CANx->TCTRL, CAN_TX_BUF_FULL) == CAN_TX_BUF_FULL) {
            i32Ret = LL_ERR_BUF_FULL;
        } else {
            WRITE_REG8(CANx->TBSLOT, u8CANTTCTxBuf);
            MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TTPTR, u8CANTTCTxBuf);
            CAN_WriteTxBuf(CANx, pstcTx);

            /* Set buffer as filled. */
            SET_REG8_BIT(CANx->TBSLOT, CAN_TBSLOT_TBF);

            /* Write MSB of TT_TRIG to transmit. */
            WRITE_REG16(CANx->TT_TRIG, CANx->TT_TRIG);

            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Get the configuration of TTCAN.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_CAN or CM_CANx:           CAN instance register base.
 * @param  [out] pstcCanTtc             Pointer to a @ref stc_can_ttc_config_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcCanTtc == NULL.
 */
int32_t CAN_TTC_GetConfig(const CM_CAN_TypeDef *CANx, stc_can_ttc_config_t *pstcCanTtc)
{
    uint32_t u32Tmp;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcCanTtc != NULL) {
        u32Tmp = READ_REG32(CANx->REF_MSG);
        pstcCanTtc->u8TxBufMode         = READ_REG8_BIT(CANx->TCTRL, CAN_TCTRL_TTTBM);
        pstcCanTtc->u8NTUPrescaler      = READ_REG8_BIT(CANx->TTCFG, CAN_TTCFG_T_PRESC);
        pstcCanTtc->u32RefMsgIDE        = (u32Tmp >> CAN_REF_MSG_REF_IDE_POS) & 0x1UL;
        pstcCanTtc->u32RefMsgID         = u32Tmp & 0x7FFFFFFFUL;
        pstcCanTtc->u16TriggerType      = READ_REG16_BIT(CANx->TRG_CFG, CAN_TRG_CFG_TTYPE);
        pstcCanTtc->u16TxEnableWindow   = (READ_REG16_BIT(CANx->TRG_CFG, CAN_TRG_CFG_TEW) >> CAN_TRG_CFG_TEW_POS) + 1U;
        pstcCanTtc->u16TxTriggerTime    = READ_REG16(CANx->TT_TRIG);
        pstcCanTtc->u16WatchTriggerTime = READ_REG16(CANx->TT_WTRIG);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_CAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
