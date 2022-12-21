/**************************************************************************//**
 * @file     nu_kpi.h
 * @brief    KPI driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_KPI_H__
#define __NU_KPI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup KPI_Driver KPI Driver
  @{
*/

/** @addtogroup KPI_EXPORTED_CONSTANTS KPI Exported Constants
  @{
*/

#define KPI_ROW_SCAN_DELAY4CLK  (0x0 << KPI_KPICONF_SCANROWD_Pos) /*!< Delay cycle when row change */
#define KPI_ROW_SCAN_DELAY8CLK  (0x1 << KPI_KPICONF_SCANROWD_Pos) /*!< Delay cycle when row change */
#define KPI_ROW_SCAN_DELAY16CLK (0x2 << KPI_KPICONF_SCANROWD_Pos) /*!< Delay cycle when row change */
#define KPI_ROW_SCAN_DELAY32CLK (0x3 << KPI_KPICONF_SCANROWD_Pos) /*!< Delay cycle when row change */

#define KPI_KEY00       (KPI_KPIKEST0_KEST00_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY01       (KPI_KPIKEST0_KEST01_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY02       (KPI_KPIKEST0_KEST02_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY03       (KPI_KPIKEST0_KEST03_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY04       (KPI_KPIKEST0_KEST04_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY05       (KPI_KPIKEST0_KEST05_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY06       (KPI_KPIKEST0_KEST06_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY07       (KPI_KPIKEST0_KEST07_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY10       (KPI_KPIKEST0_KEST10_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY11       (KPI_KPIKEST0_KEST11_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY12       (KPI_KPIKEST0_KEST12_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY13       (KPI_KPIKEST0_KEST13_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY14       (KPI_KPIKEST0_KEST14_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY15       (KPI_KPIKEST0_KEST15_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY16       (KPI_KPIKEST0_KEST16_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY17       (KPI_KPIKEST0_KEST17_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY20       (KPI_KPIKEST0_KEST20_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY21       (KPI_KPIKEST0_KEST21_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY22       (KPI_KPIKEST0_KEST22_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY23       (KPI_KPIKEST0_KEST23_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY24       (KPI_KPIKEST0_KEST24_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY25       (KPI_KPIKEST0_KEST25_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY26       (KPI_KPIKEST0_KEST26_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY27       (KPI_KPIKEST0_KEST27_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY30       (KPI_KPIKEST0_KEST30_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY31       (KPI_KPIKEST0_KEST31_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY32       (KPI_KPIKEST0_KEST32_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY33       (KPI_KPIKEST0_KEST33_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY34       (KPI_KPIKEST0_KEST34_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY35       (KPI_KPIKEST0_KEST35_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY36       (KPI_KPIKEST0_KEST36_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY37       (KPI_KPIKEST0_KEST37_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY40       (KPI_KPIKEST0_KEST40_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY41       (KPI_KPIKEST0_KEST41_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY42       (KPI_KPIKEST0_KEST42_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY43       (KPI_KPIKEST0_KEST43_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY44       (KPI_KPIKEST0_KEST44_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY45       (KPI_KPIKEST0_KEST45_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY46       (KPI_KPIKEST0_KEST46_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY47       (KPI_KPIKEST0_KEST47_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY50       (KPI_KPIKEST0_KEST50_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY51       (KPI_KPIKEST0_KEST51_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY52       (KPI_KPIKEST0_KEST52_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY53       (KPI_KPIKEST0_KEST53_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY54       (KPI_KPIKEST0_KEST54_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY55       (KPI_KPIKEST0_KEST55_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY56       (KPI_KPIKEST0_KEST56_Msk)  /*!< Press / Release Key Indicator */
#define KPI_KEY57       (KPI_KPIKEST0_KEST57_Msk)  /*!< Press / Release Key Indicator */

#define KPI_GET_KEY_STA_REG0(kpi)     (kpi->KPIKEST0)  /*!< Get Keypad State Register 0 */
#define KPI_GET_KEY_STA_REG1(kpi)     (kpi->KPIKEST1)  /*!< Get Keypad State Register 1 */
#define KPI_GET_PRESS_KEY_REG0(kpi)   (kpi->KPIKPE0)   /*!< Get Lower 32 Key Press Event Indicator */
#define KPI_GET_PRESS_KEY_REG1(kpi)   (kpi->KPIKPE1)   /*!< Get Upper 32 Key Press Event Indicator */
#define KPI_GET_RELEASE_KEY_REG0(kpi) (kpi->KPIKRE0)   /*!< Get Lower 32 Key Release Event Indicator */
#define KPI_GET_RELEASE_KEY_REG1(kpi) (kpi->KPIKRE1)   /*!< Get Upper 32 Key Release Event Indicator */

#define KPI_EN_WAKEUP(kpi)   (kpi->KPICONF |=  KPI_KPICONF_WAKEUP_Msk)  /*!< Enable Lower Power Wakeup */
#define KPI_DIS_WAKEUP(kpi)  (kpi->KPICONF &= ~KPI_KPICONF_WAKEUP_Msk)  /*!< Disable Lower Power Wakeup */

/**
 *    @brief        Enable KPI specified interrupt
 *
 *    @param[in]    u32InterruptFlag    The specified interrupt of KPI module.
 *                                      - \ref KPI_KPICONF_PKINTEN_Msk    : Press Key Interrupt Enable
 *                                      - \ref KPI_KPICONF_RKINTEN_Msk    : Release Key Interrupt
 *                                      - \ref KPI_KPICONF_INTEN_Msk      : Key Interrupt Enable
 *
 *    @return       None
 *
 *    @details      The function is used to enable KPI specified interrupt.
 *    \hideinitializer
 */
#define KPI_ENABLE_INT(kpi,u32InterruptFlag)   (kpi->KPICONF |=  u32InterruptFlag)

/**
 *    @brief        Disable KPI specified interrupt
 *
 *    @param[in]    u32InterruptFlag    The specified interrupt of KPI module.
 *                                      - \ref KPI_KPICONF_PKINTEN_Msk    : Press Key Interrupt Enable
 *                                      - \ref KPI_KPICONF_RKINTEN_Msk    : Release Key Interrupt
 *                                      - \ref KPI_KPICONF_INTEN_Msk      : Key Interrupt Enable
 *
 *    @return       None
 *
 *    @details      The function is used to enable KPI specified interrupt.
 *    \hideinitializer
 */
#define KPI_DISABLE_INT(kpi,u32InterruptFlag)  (kpi->KPICONF &= ~u32IntSel)

/**
 *    @brief        Disable 3Key Reset
 *
 *    @return       None
 *
 *    @details      The function is used to disable 3key Reset.
 *    \hideinitializer
 */
#define KPI_DISABLE_3KEY_RESET(kpi)  (kpi->KPI3KCONF &= ~KPI_KPI3KCONF_EN3KYRST_Msk)

/**
 *    @brief        Get interrupt flag
 *
 *    @return       \ref KPI_KPISTATUS_PDWAKE_Msk
 *                  \ref KPI_KPISTATUS_RST3KEY_Msk
 *                  \ref KPI_KPISTATUS_KEYINT_Msk
 *                  \ref KPI_KPISTATUS_RKEYINT_Msk
 *                  \ref KPI_KPISTATUS_PKEYINT_Msk
 *
 *    @details      The function is used to disable 3key Reset.
 *    \hideinitializer
 */
#define KPI_GET_INT_FLAG(kpi)    (kpi->KPISTATUS)

void KPI_Open(KPI_T *kpi, uint32_t u32Row, uint32_t u32Col);
void KPI_Close(KPI_T *kpi);
void KPI_ConfigKeyScanTiming(KPI_T *kpi, uint32_t u32PreScale, uint32_t u32Debounce, uint32_t u32ScanDelay);
void KPI_Set3KeyReset(KPI_T *kpi, uint32_t u32Key1, uint32_t u32Key2, uint32_t u32Key3, uint32_t u32RstCnt);


/*@}*/ /* end of group KPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group KPI_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /*__NU_KPI_H__*/






