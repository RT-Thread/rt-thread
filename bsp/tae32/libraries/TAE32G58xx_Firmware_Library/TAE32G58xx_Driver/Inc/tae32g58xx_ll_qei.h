/**
  ******************************************************************************
  * @file    tae32g58xx_ll_qei.h
  * @author  MCD Application Team
  * @brief   Header file for QEI LL module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_QEI_H_
#define _TAE32G58XX_LL_QEI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup QEI_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup QEI_LL_Exported_Macros QEI LL Exported Macros
  * @brief    QEI LL Exported Macros
  * @{
  */

/**
  * @brief  Position Counter Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  cnt Position Counter
  * @return None
  */
#define __LL_QEI_PosCnt_Set(__QEI__, cnt)               WRITE_REG((__QEI__)->POSCNT, cnt)

/**
  * @brief  Position Counter Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Position Counter
  */
#define __LL_QEI_PosCnt_Get(__QEI__)                    READ_REG((__QEI__)->POSCNT)


/**
  * @brief  Position Counter Initial Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  init Position Counter Initial
  * @return None
  */
#define __LL_QEI_PosCntInit_Set(__QEI__, init)          WRITE_REG((__QEI__)->POSINIT, init)

/**
  * @brief  Position Counter Initial Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Position Counter Initial
  */
#define __LL_QEI_PosCntInit_Get(__QEI__)                READ_REG((__QEI__)->POSINIT)


/**
  * @brief  Position Counter Max Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  max Position Counter Max
  * @return None
  */
#define __LL_QEI_PosCntMax_Set(__QEI__, max)            WRITE_REG((__QEI__)->POSMAX, max)

/**
  * @brief  Position Counter Max Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Position Counter Max
  */
#define __LL_QEI_PosCntMax_Get(__QEI__)                 READ_REG((__QEI__)->POSMAX)


/**
  * @brief  Position Counter Compare Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  cmp Position Counter Compare
  * @return None
  */
#define __LL_QEI_PosCntCmp_Set(__QEI__, cmp)            WRITE_REG((__QEI__)->POSCMP, cmp)

/**
  * @brief  Position Counter Compare Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Position Counter Compare
  */
#define __LL_QEI_PosCntCmp_Get(__QEI__)                 READ_REG((__QEI__)->POSCMP)


/**
  * @brief  Position Counter Index Latch Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Position Counter Index Latch
  */
#define __LL_QEI_PosCntIdxLatch_Get(__QEI__)            READ_REG((__QEI__)->POSILAT)


/**
  * @brief  Position Counter Timer Latch Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Position Counter Timer Latch
  */
#define __LL_QEI_PosCntTmrLatch_Get(__QEI__)            READ_REG((__QEI__)->POSLAT)


/**
  * @brief  Timer Counter Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  cnt Timer Counter
  * @return None
  */
#define __LL_QEI_TmrCnt_Set(__QEI__, cnt)               WRITE_REG((__QEI__)->UTMR, cnt)

/**
  * @brief  Timer Counter Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Timer Counter
  */
#define __LL_QEI_TmrCnt_Get(__QEI__)                    READ_REG((__QEI__)->UTMR)


/**
  * @brief  Timer Counter Period Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  period Timer Counter Period
  * @return None
  */
#define __LL_QEI_TmrCntPeriod_Set(__QEI__, period)      WRITE_REG((__QEI__)->UPRD, period)

/**
  * @brief  Timer Counter Period Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Timer Counter Period
  */
#define __LL_QEI_TmrCntPeriod_Get(__QEI__)              READ_REG((__QEI__)->UPRD)


/**
  * @brief  Direction Counter Mode Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  mode Direction Counter Mode @ref QEI_DirCntModeETypeDef
  * @return None
  */
#define __LL_QEI_DirCntMode_Set(__QEI__, mode)          \
        MODIFY_REG((__QEI__)->DECCTL, QEI0_DECCTL_DCM_Msk, (((mode) & 0x1UL) << QEI0_DECCTL_DCM_Pos))

/**
  * @brief  Position Counter Work Mode Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  mode Position Counter Work Mode @ref QEI_PosCntWorkModeETypeDef
  * @return None
  */
#define __LL_QEI_PosCntWorkMode_Set(__QEI__, mode)      \
        MODIFY_REG((__QEI__)->DECCTL, QEI0_DECCTL_QSRC_Msk, (((mode) & 0x3UL) << QEI0_DECCTL_QSRC_Pos))

/**
  * @brief  Position Counter Clock Rate Mode Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  mode Position Counter Clock Rate Mode @ref QEI_ClkRateModeETypeDef
  * @return None
  */
#define __LL_QEI_ClkRateMode_Set(__QEI__, mode)         \
        MODIFY_REG((__QEI__)->DECCTL, QEI0_DECCTL_XCR_Msk, (((mode) & 0x1UL) << QEI0_DECCTL_XCR_Pos))

/**
  * @brief  Index Reset Position Counter Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_IdxRstPosCnt_En(__QEI__)               CLEAR_BIT((__QEI__)->DECCTL, QEI0_DECCTL_IGATE_Msk)

/**
  * @brief  Index Reset Position Counter Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_IdxRstPosCnt_Dis(__QEI__)              SET_BIT((__QEI__)->DECCTL, QEI0_DECCTL_IGATE_Msk)

/**
  * @brief  QEA/QEB Swap Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_QEA_B_Swap_En(__QEI__)                 SET_BIT((__QEI__)->DECCTL, QEI0_DECCTL_SWAP_Msk)

/**
  * @brief  QEA/QEB Swap Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_QEA_B_Swap_Dis(__QEI__)                CLEAR_BIT((__QEI__)->DECCTL, QEI0_DECCTL_SWAP_Msk)

/**
  * @brief  QEB Input Polarity Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  pol QEB Input Polarity
  * @return None
  */
#define __LL_QEI_QEBInputPol_Set(__QEI__, pol)          \
        MODIFY_REG((__QEI__)->DECCTL, QEI0_DECCTL_QBP_Msk, (((pol) & 0x1U) << QEI0_DECCTL_QBP_Pos))

/**
  * @brief  QEA Input Polarity Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  pol QEA Input Polarity
  * @return None
  */
#define __LL_QEI_QEAInputPol_Set(__QEI__, pol)          \
        MODIFY_REG((__QEI__)->DECCTL, QEI0_DECCTL_QAP_Msk, (((pol) & 0x1U) << QEI0_DECCTL_QAP_Pos))

/**
  * @brief  Index Input Polarity Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  pol Index Input Polarity
  * @return None
  */
#define __LL_QEI_IdxInputPol_Set(__QEI__, pol)          \
        MODIFY_REG((__QEI__)->DECCTL, QEI0_DECCTL_QIP_Msk, (((pol) & 0x1U) << QEI0_DECCTL_QIP_Pos))


/**
  * @brief  Position Counter Reset Mode Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  mode Position Counter Reset Mode @ref QEI_PosCntRstModeETypeDef
  * @return None
  */
#define __LL_QEI_PosCntRstMode_Set(__QEI__, mode)       \
        MODIFY_REG((__QEI__)->QEPCTL, QEI0_QEPCTL_PCRM_Msk, (((mode) & 0x3UL) << QEI0_QEPCTL_PCRM_Pos))

/**
  * @brief  Position Counter Software Initial Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntSwInit_En(__QEI__)               SET_BIT((__QEI__)->QEPCTL, QEI0_QEPCTL_SWI_Msk)

/**
  * @brief  Position Counter Index Initial Edge Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  edge Position Counter Index Initial Edge @ref QEI_PosCntIdxInitEdgeETypeDef
  * @return None
  */
#define __LL_QEI_PosCntIdxInitEdge_Set(__QEI__, edge)   \
        MODIFY_REG((__QEI__)->QEPCTL, QEI0_QEPCTL_IEI_Msk, (((edge) & 0x3UL) << QEI0_QEPCTL_IEI_Pos))

/**
  * @brief  Position Counter Index Latch Edge Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  edge Position Counter Index Latch Edge @ref QEI_PosCntIdxLatchEdgeETypeDef
  * @return None
  */
#define __LL_QEI_PosCntIdxLatchEdge_Set(__QEI__, edge)  \
        MODIFY_REG((__QEI__)->QEPCTL, QEI0_QEPCTL_IEL_Msk, (((edge) & 0x3UL) << QEI0_QEPCTL_IEL_Pos))

/**
  * @brief  QEI Timer Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_Tmr_En(__QEI__)                        SET_BIT((__QEI__)->QEPCTL, QEI0_QEPCTL_UTE_Msk)

/**
  * @brief  QEI Timer Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_Tmr_Dis(__QEI__)                       CLEAR_BIT((__QEI__)->QEPCTL, QEI0_QEPCTL_UTE_Msk)

/**
  * @brief  QEI Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_En(__QEI__)                            SET_BIT((__QEI__)->QEPCTL, QEI0_QEPCTL_QPE_Msk)

/**
  * @brief  QEI Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_Dis(__QEI__)                           CLEAR_BIT((__QEI__)->QEPCTL, QEI0_QEPCTL_QPE_Msk)


/**
  * @brief  Position Counter Compare Shadow Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntCmpShadow_En(__QEI__)            SET_BIT((__QEI__)->POSCTL, QEI0_POSCTL_PSE_Msk)

/**
  * @brief  Position Counter Compare Shadow Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntCmpShadow_Dis(__QEI__)           CLEAR_BIT((__QEI__)->POSCTL, QEI0_POSCTL_PSE_Msk)

/**
  * @brief  Position Counter Compare Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntCmp_En(__QEI__)                  SET_BIT((__QEI__)->POSCTL, QEI0_POSCTL_CCE_Msk)

/**
  * @brief  Position Counter Compare Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntCmp_Dis(__QEI__)                 CLEAR_BIT((__QEI__)->POSCTL, QEI0_POSCTL_CCE_Msk)


/**
  * @brief  Capture Event Division Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  div Capture Event Division @ref QEI_CapEvtDivETypeDef
  * @return None
  */
#define __LL_QEI_CapEvtDiv_Set(__QEI__, div)            \
        MODIFY_REG((__QEI__)->CAPCTL, QEI0_CAPCTL_UPPS_Msk, (((div) & 0xfUL) << QEI0_CAPCTL_UPPS_Pos))

/**
  * @brief  Capture Timer Clock Division Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  div Capture Timer Clock Division @ref QEI_CapTmrClkDivETypeDef
  * @return None
  */
#define __LL_QEI_CapTmrClkDiv_Set(__QEI__, div)         \
        MODIFY_REG((__QEI__)->CAPCTL, QEI0_CAPCTL_CCPS_Msk, (((div) & 0x7UL) << QEI0_CAPCTL_CCPS_Pos))

/**
  * @brief  Capture Latch Mode Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  mode Capture Latch Mode @ref QEI_CapLatchModeETypeDef
  * @return None
  */
#define __LL_QEI_CapLatchMode_Set(__QEI__, mode)        \
        MODIFY_REG((__QEI__)->CAPCTL, QEI0_CAPCTL_CMD_Msk, (((mode) & 0x1UL) << QEI0_CAPCTL_CMD_Pos))

/**
  * @brief  QEI Capture Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_Cap_En(__QEI__)                        SET_BIT((__QEI__)->CAPCTL, QEI0_CAPCTL_CEN_Msk)

/**
  * @brief  QEI Capture Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_Cap_Dis(__QEI__)                       CLEAR_BIT((__QEI__)->CAPCTL, QEI0_CAPCTL_CEN_Msk)


/**
  * @brief  Capture Counter Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  cnt Capture Counter
  * @return None
  */
#define __LL_QEI_CapCnt_Set(__QEI__, cnt)               WRITE_REG((__QEI__)->QCTMR, cnt)

/**
  * @brief  Capture Counter Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Capture Counter
  */
#define __LL_QEI_CapCnt_Get(__QEI__)                    READ_REG((__QEI__)->QCTMR)


/**
  * @brief  Capture Period Set
  * @param  __QEI__ Specifies QEI peripheral
  * @param  period Capture Period
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_QEI_CapPeriod_Set(__QEI__, period)         \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (WRITE_REG((__QEI__)->QCPRD, period)) : 0)

/**
  * @brief  Capture Period Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Capture Period
  */
#define __LL_QEI_CapPeriod_Get(__QEI__)                 READ_REG((__QEI__)->QCPRD)


/**
  * @brief  Capture Counter Latch Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Capture Counter Latch
  */
#define __LL_QEI_CapCntLatch_Get(__QEI__)               READ_REG((__QEI__)->CTMRLAT)


/**
  * @brief  Capture Period Latch Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return Capture Period Latch
  */
#define __LL_QEI_CapPeriodLatch_Get(__QEI__)            READ_REG((__QEI__)->CPRDLAT)


/**
  * @brief  Capture Done Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_CapDone_INT_En(__QEI__)                SET_BIT((__QEI__)->IENR, QEI0_IENR_CDE_Msk)

/**
  * @brief  Capture Done Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_CapDone_INT_Dis(__QEI__)               CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_CDE_Msk)

/**
  * @brief  Position Counter Reset Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntRst_INT_En(__QEI__)              SET_BIT((__QEI__)->IENR, QEI0_IENR_PRE_Msk)

/**
  * @brief  Position Counter Reset Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntRst_INT_Dis(__QEI__)             CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_PRE_Msk)

/**
  * @brief  Position Counter Initial Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntInit_INT_En(__QEI__)             SET_BIT((__QEI__)->IENR, QEI0_IENR_PIE_Msk)

/**
  * @brief  Position Counter Initial Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntInit_INT_Dis(__QEI__)            CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_PIE_Msk)

/**
  * @brief  Timer Overflow Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_TmrOverflow_INT_En(__QEI__)            SET_BIT((__QEI__)->IENR, QEI0_IENR_UTO_Msk)

/**
  * @brief  Timer Overflow Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_TmrOverflow_INT_Dis(__QEI__)           CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_UTO_Msk)

/**
  * @brief  Position Counter Latch Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntLatch_INT_En(__QEI__)            SET_BIT((__QEI__)->IENR, QEI0_IENR_IEL_Msk)

/**
  * @brief  Position Counter Latch Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntLatch_INT_Dis(__QEI__)           CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_IEL_Msk)

/**
  * @brief  Position Counter Compare Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntCmp_INT_En(__QEI__)              SET_BIT((__QEI__)->IENR, QEI0_IENR_PCM_Msk)

/**
  * @brief  Position Counter Compare Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntCmp_INT_Dis(__QEI__)             CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_PCM_Msk)

/**
  * @brief  Position Counter Overflow Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntOverflow_INT_En(__QEI__)         SET_BIT((__QEI__)->IENR, QEI0_IENR_PCO_Msk)

/**
  * @brief  Position Counter Overflow Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntOverflow_INT_Dis(__QEI__)        CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_PCO_Msk)

/**
  * @brief  Position Counter Underflow Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntUnderflow_INT_En(__QEI__)        SET_BIT((__QEI__)->IENR, QEI0_IENR_PCU_Msk)

/**
  * @brief  Position Counter Underflow Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntUnderflow_INT_Dis(__QEI__)       CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_PCU_Msk)

/**
  * @brief  Directiont Change Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_DirChange_INT_En(__QEI__)              SET_BIT((__QEI__)->IENR, QEI0_IENR_QDC_Msk)

/**
  * @brief  Directiont Change Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_DirChange_INT_Dis(__QEI__)             CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_QDC_Msk)

/**
  * @brief  Phase Error Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PhaseErr_INT_En(__QEI__)               SET_BIT((__QEI__)->IENR, QEI0_IENR_QPE_Msk)

/**
  * @brief  Phase Error Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PhaseErr_INT_Dis(__QEI__)              CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_QPE_Msk)

/**
  * @brief  Position Counter Error Interrupt Enable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntErr_INT_En(__QEI__)              SET_BIT((__QEI__)->IENR, QEI0_IENR_PCE_Msk)

/**
  * @brief  Position Counter Error Interrupt Disable
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntErr_INT_Dis(__QEI__)             CLEAR_BIT((__QEI__)->IENR, QEI0_IENR_PCE_Msk)

/**
  * @brief  All Interrupt Enable Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return All Interrupt Enable
  */
#define __LL_QEI_AllIntEn_Get(__QEI__)                  READ_REG((__QEI__)->IENR)


/**
  * @brief  First Index Direct Status Get
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 reverse rotation
  * @retval 1 forward rotation
  */
#define __LL_QEI_FirstIdxDirSta_Get(__QEI__)            READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_QDF_Msk, QEI0_STSR_QDF_Pos)

/**
  * @brief  Index Direct Status Get
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 reverse rotation
  * @retval 1 forward rotation
  */
#define __LL_IdxDirSta_Get(__QEI__)                     READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_QDI_Msk, QEI0_STSR_QDI_Pos)

/**
  * @brief  Real Timer Direct Status Get
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 reverse rotation
  * @retval 1 forward rotation
  */
#define __LL_QEI_RealTimeDirSta_Get(__QEI__)            READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_QDS_Msk, QEI0_STSR_QDS_Pos)

/**
  * @brief  Judge is Capture Overflow Error Status or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Capture Overflow Error Status
  * @retval 1 is Capture Overflow Error Status
  */
#define __LL_QEI_IsCapOverflowErrSta(__QEI__)           READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_COE_Msk, QEI0_STSR_COE_Pos)

/**
  * @brief  Capture Overflow Error Status Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_CapOverflowErrSta_Clr(__QEI__)         WRITE_REG((__QEI__)->STSR, QEI0_STSR_COE_Msk)

/**
  * @brief  Judge is Capture Direction Error Status or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Capture Direction Error Status
  * @retval 1 is Capture Direction Error Status
  */
#define __LL_QEI_IsCapDirErrSta(__QEI__)                READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_CDE_Msk, QEI0_STSR_CDE_Pos)

/**
  * @brief  Capture Direction Error Status Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_CapDirErrSta_Clr(__QEI__)              WRITE_REG((__QEI__)->STSR, QEI0_STSR_CDE_Msk)

/**
  * @brief  Judge is First Index Status or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't First Index Status
  * @retval 1 is First Index Status
  */
#define __LL_QEI_IsFirstIdxSta(__QEI__)                 READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_FIS_Msk, QEI0_STSR_FIS_Pos)

/**
  * @brief  First Index Status Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_FirstIdxSta_Clr(__QEI__)               WRITE_REG((__QEI__)->STSR, QEI0_STSR_FIS_Msk)

/**
  * @brief  Judge is Capture Done Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Capture Done Interrupt Pending
  * @retval 1 is Capture Done Interrupt Pending
  */
#define __LL_QEI_IsCapDoneIntPnd(__QEI__)               READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_CDS_Msk, QEI0_STSR_CDS_Pos)

/**
  * @brief  Capture Done Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_CapDoneIntPnd_Clr(__QEI__)             WRITE_REG((__QEI__)->STSR, QEI0_STSR_CDS_Msk)

/**
  * @brief  Judge is Positon Counter Reset Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Reset Interrupt Pending
  * @retval 1 is Positon Counter Reset Interrupt Pending
  */
#define __LL_QEI_IsPosCntRstIntPnd(__QEI__)             READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_PRS_Msk, QEI0_STSR_PRS_Pos)

/**
  * @brief  Positon Counter Reset Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntRstIntPnd_Clr(__QEI__)           WRITE_REG((__QEI__)->STSR, QEI0_STSR_PRS_Msk)

/**
  * @brief  Judge is Positon Counter Initial Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Initial Interrupt Pending
  * @retval 1 is Positon Counter Initial Interrupt Pending
  */
#define __LL_QEI_IsPosCntInitIntPnd(__QEI__)            READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_PIS_Msk, QEI0_STSR_PIS_Pos)

/**
  * @brief  Positon Counter Initial Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntInitIntPnd_Clr(__QEI__)          WRITE_REG((__QEI__)->STSR, QEI0_STSR_PIS_Msk)

/**
  * @brief  Judge is Timer Overflow Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Timer Overflow Interrupt Pending
  * @retval 1 is Timer Overflow Interrupt Pending
  */
#define __LL_QEI_IsTmrOverflowIntPnd(__QEI__)           READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_UTO_Msk, QEI0_STSR_UTO_Pos)

/**
  * @brief  Timer Overflow Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_TmrOverflowIntPnd_Clr(__QEI__)         WRITE_REG((__QEI__)->STSR, QEI0_STSR_UTO_Msk)

/**
  * @brief  Judge is Positon Counter Latch Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Latch Interrupt Pending
  * @retval 1 is Positon Counter Latch Interrupt Pending
  */
#define __LL_QEI_IsPosCntLatchIntPnd(__QEI__)           READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_IEL_Msk, QEI0_STSR_IEL_Pos)

/**
  * @brief  Positon Counter Latch Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntLatchIntPnd_Clr(__QEI__)         WRITE_REG((__QEI__)->STSR, QEI0_STSR_IEL_Msk)

/**
  * @brief  Judge is Positon Counter Compare Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Compare Interrupt Pending
  * @retval 1 is Positon Counter Compare Interrupt Pending
  */
#define __LL_QEI_IsPosCntCmpIntPnd(__QEI__)             READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_PCM_Msk, QEI0_STSR_PCM_Pos)

/**
  * @brief  Positon Counter Compare Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntCmpIntPnd_Clr(__QEI__)           WRITE_REG((__QEI__)->STSR, QEI0_STSR_PCM_Msk)

/**
  * @brief  Judge is Positon Counter Overflow Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Overflow Interrupt Pending
  * @retval 1 is Positon Counter Overflow Interrupt Pending
  */
#define __LL_QEI_IsPosCntOverflowIntPnd(__QEI__)        READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_PCO_Msk, QEI0_STSR_PCO_Pos)

/**
  * @brief  Positon Counter Overflow Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntOverflowIntPnd_Clr(__QEI__)      WRITE_REG((__QEI__)->STSR, QEI0_STSR_PCO_Msk)

/**
  * @brief  Judge is Positon Counter Underflow Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Positon Counter Underflow Interrupt Pending
  * @retval 1 is Positon Counter Underflow Interrupt Pending
  */
#define __LL_QEI_IsPosCntUnderflowIntPnd(__QEI__)       READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_PCU_Msk, QEI0_STSR_PCU_Pos)

/**
  * @brief  Positon Counter Underflow Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntUnderflowIntPnd_Clr(__QEI__)     WRITE_REG((__QEI__)->STSR, QEI0_STSR_PCU_Msk)

/**
  * @brief  Judge is Direction Change Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Direction Change Interrupt Pending
  * @retval 1 is Direction Change Interrupt Pending
  */
#define __LL_QEI_IsDirChangeIntPnd(__QEI__)             READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_QDC_Msk, QEI0_STSR_QDC_Pos)

/**
  * @brief  Direction Change Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_DirChangeIntPnd_Clr(__QEI__)           WRITE_REG((__QEI__)->STSR, QEI0_STSR_QDC_Msk)

/**
  * @brief  Judge is Phase Error Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Phase Error Interrupt Pending
  * @retval 1 is Phase Error Interrupt Pending
  */
#define __LL_QEI_IsPhaseErrIntPnd(__QEI__)              READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_PHE_Msk, QEI0_STSR_PHE_Pos)

/**
  * @brief  Phase Error Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PhaseErrIntPnd_Clr(__QEI__)            WRITE_REG((__QEI__)->STSR, QEI0_STSR_PHE_Msk)

/**
  * @brief  Judge is Position Counter Error Interrupt Pending or not
  * @param  __QEI__ Specifies QEI peripheral
  * @retval 0 isn't Position Counter Error Interrupt Pending
  * @retval 1 is Position Counter Error Interrupt Pending
  */
#define __LL_QEI_IsPosCntErrIntPnd(__QEI__)             READ_BIT_SHIFT((__QEI__)->STSR, QEI0_STSR_PCE_Msk, QEI0_STSR_PCE_Pos)

/**
  * @brief  Position Counter Error Interrupt Pending Clear
  * @param  __QEI__ Specifies QEI peripheral
  * @return None
  */
#define __LL_QEI_PosCntErrIntPnd_Clr(__QEI__)           WRITE_REG((__QEI__)->STSR, QEI0_STSR_PCE_Msk)

/**
  * @brief  All Interrupt Pending Get
  * @param  __QEI__ Specifies QEI peripheral
  * @return All Interrupt Pending
  */
#define __LL_QEI_AllIntPnd_Get(__QEI__)                 READ_REG((__QEI__)->STSR)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup QEI_LL_Exported_Types QEI LL Exported Types
  * @brief    QEI LL Exported Types
  * @{
  */

/**
  * @brief QEI Direction Counter Mode Definition
  */
typedef enum {
    QEI_DIR_CNT_MODE0 = 0,              /*!< QEI Direction Counter Mode 0 */
    QEI_DIR_CNT_MODE1,                  /*!< QEI Direction Counter Mode 1 */
} QEI_DirCntModeETypeDef;

/**
  * @brief QEI Position Counter Work Mode Definition
  */
typedef enum {
    QEI_POS_CNT_WORK_MODE_QUAD = 0,     /*!< QEI Position Counter Work Mode Quadrature  */
    QEI_POS_CNT_WORK_MODE_DIR,          /*!< QEI Position Counter Work Mode Direction   */
    QEI_POS_CNT_WORK_MODE_UP,           /*!< QEI Position Counter Work Mode Up          */
    QEI_POS_CNT_WORK_MODE_DOWN,         /*!< QEI Position Counter Work Mode Down        */
} QEI_PosCntWorkModeETypeDef;

/**
  * @brief QEI Position Counter Clock Rate Mode Definition
  */
typedef enum {
    QEI_CLK_RATE_MODE_X1 = 0,           /*!< QEI Position Counter Clock Rate Mode X1 */
    QEI_CLK_RATE_MODE_X2,               /*!< QEI Position Counter Clock Rate Mode X2 */
} QEI_ClkRateModeETypeDef;

/**
  * @brief QEI QEA/QEB/Index Input Polarity Definition
  */
typedef enum {
    QEI_INPUT_POL_ACT_HIGH = 0,         /*!< QEI QEA/QEB/Index Input Polarity Active High   */
    QEI_INPUT_POL_ACT_LOW,              /*!< QEI QEA/QEB/Index Input Polarity Active Low    */
} QEI_InputPolETypeDef;

/**
  * @brief QEI Position Counter Reset Mode Definition
  * @note  Up and Down Overflow Reset are included in every mode
  */
typedef enum {
    QEI_POS_CNT_RST_MODE_EVERY_IDX = 0, /*!< QEI Position Counter Reset Mode Every Index    */
    QEI_POS_CNT_RST_MODE_MAX,           /*!< QEI Position Counter Reset Mode MAX            */
    QEI_POS_CNT_RST_MODE_FIRDT_IDX,     /*!< QEI Position Counter Reset Mode First Index    */
    QEI_POS_CNT_RST_MODE_TMR_EVT,       /*!< QEI Position Counter Reset Mode Timer Event    */
} QEI_PosCntRstModeETypeDef;

/**
  * @brief QEI Position Counter Index Initial Edge Definition
  */
typedef enum {
    QEI_POS_CNT_INIT_IDX_EDGE_DIS = 1,  /*!< QEI Position Counter Index Initial Edge Disable    */
    QEI_POS_CNT_INIT_IDX_EDGE_RISING,   /*!< QEI Position Counter Index Initial Edge Rising     */
    QEI_POS_CNT_INIT_IDX_EDGE_FALLING,  /*!< QEI Position Counter Index Initial Edge Falling    */
} QEI_PosCntIdxInitEdgeETypeDef;

/**
  * @brief QEI Position Counter Index Latch Edge Definition
  */
typedef enum {
    QEI_POS_CNT_LATCH_IDX_EDGE_DIS = 0, /*!< QEI Position Counter Index Latch Edge Disable      */
    QEI_POS_CNT_LATCH_IDX_EDGE_RISING,  /*!< QEI Position Counter Index Latch Edge Rising       */
    QEI_POS_CNT_LATCH_IDX_EDGE_FALLING, /*!< QEI Position Counter Index Latch Edge Falling      */
    QEI_POS_CNT_LATCH_IDX_EDGE_FIRST,   /*!< QEI Position Counter Index Latch Edge First Quad   */
} QEI_PosCntIdxLatchEdgeETypeDef;

/**
  * @brief QEI Capture Event Division Definition
  */
typedef enum {
    QEI_CAP_EVT_DIV_1 = 0,              /*!< QEI Capture Event Division 1       */
    QEI_CAP_EVT_DIV_2,                  /*!< QEI Capture Event Division 2       */
    QEI_CAP_EVT_DIV_4,                  /*!< QEI Capture Event Division 4       */
    QEI_CAP_EVT_DIV_8,                  /*!< QEI Capture Event Division 8       */
    QEI_CAP_EVT_DIV_16,                 /*!< QEI Capture Event Division 16      */
    QEI_CAP_EVT_DIV_32,                 /*!< QEI Capture Event Division 32      */
    QEI_CAP_EVT_DIV_64,                 /*!< QEI Capture Event Division 64      */
    QEI_CAP_EVT_DIV_128,                /*!< QEI Capture Event Division 128     */
    QEI_CAP_EVT_DIV_256,                /*!< QEI Capture Event Division 256     */
    QEI_CAP_EVT_DIV_512,                /*!< QEI Capture Event Division 512     */
    QEI_CAP_EVT_DIV_1024,               /*!< QEI Capture Event Division 1024    */
    QEI_CAP_EVT_DIV_2048,               /*!< QEI Capture Event Division 2048    */
} QEI_CapEvtDivETypeDef;

/**
  * @brief QEI Capture Timer Clock Division Definition
  */
typedef enum {
    QEI_CAP_TMR_CLK_DIV_1 = 0,          /*!< QEI Capture Timer Clock Division 1     */
    QEI_CAP_TMR_CLK_DIV_2,              /*!< QEI Capture Timer Clock Division 2     */
    QEI_CAP_TMR_CLK_DIV_4,              /*!< QEI Capture Timer Clock Division 4     */
    QEI_CAP_TMR_CLK_DIV_8,              /*!< QEI Capture Timer Clock Division 8     */
    QEI_CAP_TMR_CLK_DIV_16,             /*!< QEI Capture Timer Clock Division 16    */
    QEI_CAP_TMR_CLK_DIV_32,             /*!< QEI Capture Timer Clock Division 32    */
    QEI_CAP_TMR_CLK_DIV_64,             /*!< QEI Capture Timer Clock Division 64    */
    QEI_CAP_TMR_CLK_DIV_128,            /*!< QEI Capture Timer Clock Division 128   */
} QEI_CapTmrClkDivETypeDef;

/**
  * @brief QEI Capture Latch Mode Definition
  */
typedef enum {
    QEI_CAP_LATCH_MODE_CPU_READ = 0,    /*!< QEI Capture Latch Mode CPU Read        */
    QEI_CAP_LATCH_MODE_TMR_TO,          /*!< QEI Capture Latch Mode Timer Timeout   */
} QEI_CapLatchModeETypeDef;


/**
  * @brief QEI Position Counter initialization related configuration Definition
  */
typedef struct __QEI_PosCnt_InitTypeDef {
    uint32_t init_val;                              /*!< Position Counter Initial Value             */
    uint32_t max_val;                               /*!< Position Counter Max Value                 */

    bool idx_rst_en;                                /*!< Index Reset Position Counter Enable        */
    bool swap_en;                                   /*!< QEA/B Swap Enable                          */
    QEI_InputPolETypeDef idx_pol;                   /*!< Index Input Polarity                       */
    QEI_InputPolETypeDef qea_pol;                   /*!< QEA Input Polarity                         */
    QEI_InputPolETypeDef qeb_pol;                   /*!< QEB Input Polarity                         */

    QEI_PosCntWorkModeETypeDef work_mode;           /*!< Position Counter Work Mode                 */
    QEI_DirCntModeETypeDef     dir_cnt_mode;        /*!< Position Counter Direction Counter Mode    */
    QEI_ClkRateModeETypeDef    clk_rate_mode;       /*!< Position Counter Clock Rate                */
    QEI_PosCntRstModeETypeDef  rst_mode;            /*!< Position Counter Reset Mode                */
    QEI_PosCntIdxInitEdgeETypeDef  idx_init_edge;   /*!< Position Counter Index Init Edge           */
    QEI_PosCntIdxLatchEdgeETypeDef idx_latch_edge;  /*!< Position Counter Index Latch Edge          */
} QEI_PosCnt_InitTypeDef;

/**
  * @brief QEI Timer initialization related configuration Definition
  */
typedef struct __QEI_Tmr_InitTypeDef {
    bool     enable;                        /*!< Timer Enable       */
    uint32_t start_val;                     /*!< Timer Start Value  */
    uint32_t period_val;                    /*!< Timer Period Value */
} QEI_Tmr_InitTypeDef;

/**
  * @brief QEI Compare initialization related configuration Definition
  */
typedef struct __QEI_Cmp_InitTypeDef {
    bool enable;                            /*!< Compare Enable         */
    bool shadow_en;                         /*!< Compare Shadow Enable  */
    uint32_t cmp_val;                       /*!< Compare Value          */
} QEI_Cmp_InitTypeDef;

/**
  * @brief QEI Capture initialization related configuration Definition
  */
typedef struct __QEI_Cap_InitTypeDef {
    bool enable;                            /*!< Capture Enable                 */
    QEI_CapEvtDivETypeDef    evt_div;       /*!< Capture Event Division         */
    QEI_CapTmrClkDivETypeDef tmr_clk_div;   /*!< Capture Timer Clock Division   */
    QEI_CapLatchModeETypeDef latch_mode;    /*!< Capture Latch Mode             */
} QEI_Cap_InitTypeDef;


/**
  * @brief QEI initialization related configuration Definition
  */
typedef struct __QEI_InitTypeDef {
    QEI_PosCnt_InitTypeDef pos_cnt_init;    /*!< Position Counter Init  */
    QEI_Tmr_InitTypeDef    tmr_init;        /*!< Timer Init             */
    QEI_Cmp_InitTypeDef    cmp_init;        /*!< Compare Init           */
    QEI_Cap_InitTypeDef    cap_init;        /*!< Capture Init           */
} QEI_InitTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup QEI_LL_Exported_Functions
  * @{
  */

/** @addtogroup QEI_LL_Exported_Functions_Groupp1
  * @{
  */
LL_StatusETypeDef LL_QEI_Init(QEI_TypeDef *Instance, QEI_InitTypeDef *init);
LL_StatusETypeDef LL_QEI_DeInit(QEI_TypeDef *Instance);
void LL_QEI_MspInit(QEI_TypeDef *Instance);
void LL_QEI_MspDeInit(QEI_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup QEI_LL_Exported_Functions_Groupp2
  * @{
  */
LL_StatusETypeDef LL_QEI_En(QEI_TypeDef *Instance);
LL_StatusETypeDef LL_QEI_Dis(QEI_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup QEI_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_QEI_IRQHandler(QEI_TypeDef *Instance);

void LL_QEI_CapDoneCallback(QEI_TypeDef *Instance);
void LL_QEI_PosCntRstCallback(QEI_TypeDef *Instance);
void LL_QEI_PosCntInitCallback(QEI_TypeDef *Instance);
void LL_QEI_TmrOverflowCallback(QEI_TypeDef *Instance);
void LL_QEI_PosCntLatchCallback(QEI_TypeDef *Instance);
void LL_QEI_PosCntCmpCallback(QEI_TypeDef *Instance);
void LL_QEI_PosCntOverflowCallback(QEI_TypeDef *Instance);
void LL_QEI_PosCntUnderflowCallback(QEI_TypeDef *Instance);
void LL_QEI_DirChangeCallback(QEI_TypeDef *Instance);
void LL_QEI_PhaseErrCallback(QEI_TypeDef *Instance);
void LL_QEI_PosCntErrCallback(QEI_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_QEI_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

