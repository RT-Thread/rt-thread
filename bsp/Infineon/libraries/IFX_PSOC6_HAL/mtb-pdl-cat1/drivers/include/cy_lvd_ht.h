/***************************************************************************//**
* \file cy_lvd_ht.h
* \version 1.0
*
* The header file of the LVD HT driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_lvd_ht
* \{
* The LVD HT driver provides an API to manage the Low Voltage Detection HT block.
*
* The functions and other declarations used in this driver are in cy_lvd_ht.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* The LVD block provides a status of currently observed VDDD voltage
* and triggers an interrupt or fault when the observed voltage crosses an adjusted
* threshold.
*
* \section group_lvd_ht_configuration_considerations Configuration Considerations
* To set up an LVD, configure the voltage threshold by the
* \ref Cy_LVD_HT_SetThreshold function, ensure that the LVD block itself and LVD
* interrupt are disabled (by the \ref Cy_LVD_HT_Disable and
* \ref Cy_LVD_HT_ClearInterruptMask functions correspondingly) before changing the
* threshold to prevent propagating a false interrupt.
* Then configure interrupts by the \ref Cy_LVD_HT_SetInterruptConfig function, do
* not forget to initialize an interrupt handler (the interrupt source number
* is srss_interrupt_IRQn).
* Then enable LVD by the \ref Cy_LVD_HT_Enable function, then wait for at least 25us
* to get the circuit stabilized and clear the possible false interrupts by the
* \ref Cy_LVD_HT_ClearInterrupt, and finally the LVD interrupt can be enabled by
* the \ref Cy_LVD_HT_SetInterruptMask function.
*
* Note : If an LVD is required in Deep Sleep mode, then \ref Cy_LVD_HT_DeepSleepEnable
* should be used to enable LVD during Deep Sleep.
*
* \section group_lvd_ht_more_information More Information
* See the LVD chapter of the device technical reference manual (TRM).
*
* \section group_lvd_ht_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason of Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial Version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_lvd_ht_macros Macros
* \defgroup group_lvd_ht_functions Functions
*   \{
*       \defgroup group_lvd_ht_functions_syspm_callback  Low Power Callback
*   \}
* \defgroup group_lvd_ht_enums Enumerated Types
*/


#if !defined(CY_LVD_HT_H)
#define CY_LVD_HT_H

#include "cy_device.h"

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))

#include "cy_pra.h"
#include "cy_syspm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup group_lvd_ht_macros
* \{
*/

/** The driver major version */
#define CY_LVD_HT_DRV_VERSION_MAJOR       1

/** The driver minor version */
#define CY_LVD_HT_DRV_VERSION_MINOR       0

/** The LVD driver identifier */
#define CY_LVD_HT_ID                      (CY_PDL_DRV_ID(0x78U))


/** \} group_lvd_ht_macros */


/** \addtogroup group_lvd_ht_enums
* \{
*/

/**
 * LVD Selection.
 */
typedef enum
{
    CY_LVD_HT_SELECT_LVD_1   = 0x1u,  /**<Select HT LVD-1 */
    CY_LVD_HT_SELECT_LVD_2   = 0x2u,  /**<Select HT LVD-2 */
} cy_en_lvd_ht_select_t;

/**
 * LVD reference voltage select.
 */
typedef enum
{
    CY_LVD_HT_THRESHOLD_2_8_V    = 0x0U, /**<Select LVD reference voltage: 2.8V */
    CY_LVD_HT_THRESHOLD_2_9_V    = 0x1U, /**<Select LVD reference voltage: 2.9V */
    CY_LVD_HT_THRESHOLD_3_0_V    = 0x2U, /**<Select LVD reference voltage: 3.0V */
    CY_LVD_HT_THRESHOLD_3_1_V    = 0x3U, /**<Select LVD reference voltage: 3.1V */
    CY_LVD_HT_THRESHOLD_3_2_V    = 0x4U, /**<Select LVD reference voltage: 3.2V */
    CY_LVD_HT_THRESHOLD_3_3_V    = 0x5U, /**<Select LVD reference voltage: 3.3V */
    CY_LVD_HT_THRESHOLD_3_4_V    = 0x6U, /**<Select LVD reference voltage: 3.4V */
    CY_LVD_HT_THRESHOLD_3_5_V    = 0x7U, /**<Select LVD reference voltage: 3.5V */
    CY_LVD_HT_THRESHOLD_3_6_V    = 0x8U, /**<Select LVD reference voltage: 3.6V */
    CY_LVD_HT_THRESHOLD_3_7_V    = 0x9U, /**<Select LVD reference voltage: 3.7V */
    CY_LVD_HT_THRESHOLD_3_8_V    = 0xAU, /**<Select LVD reference voltage: 3.8V */
    CY_LVD_HT_THRESHOLD_3_9_V    = 0xBU, /**<Select LVD reference voltage: 3.9V */
    CY_LVD_HT_THRESHOLD_4_0_V    = 0xCU, /**<Select LVD reference voltage: 4.0V */
    CY_LVD_HT_THRESHOLD_4_1_V    = 0xDU, /**<Select LVD reference voltage: 4.1V */
    CY_LVD_HT_THRESHOLD_4_2_V    = 0xEU, /**<Select LVD reference voltage: 4.2V */
    CY_LVD_HT_THRESHOLD_4_3_V    = 0xFU,  /**<Select LVD reference voltage: 4.3V */
    CY_LVD_HT_THRESHOLD_4_4_V    = 0x10U, /**<Select LVD reference voltage: 4.4V */
    CY_LVD_HT_THRESHOLD_4_5_V    = 0x11U, /**<Select LVD reference voltage: 4.5V */
    CY_LVD_HT_THRESHOLD_4_6_V    = 0x12U, /**<Select LVD reference voltage: 4.6V */
    CY_LVD_HT_THRESHOLD_4_7_V    = 0x13U, /**<Select LVD reference voltage: 4.7V */
    CY_LVD_HT_THRESHOLD_4_8_V    = 0x14U, /**<Select LVD reference voltage: 4.8V */
    CY_LVD_HT_THRESHOLD_4_9_V    = 0x15U, /**<Select LVD reference voltage: 4.9V */
    CY_LVD_HT_THRESHOLD_5_0_V    = 0x16U, /**<Select LVD reference voltage: 5.0V */
    CY_LVD_HT_THRESHOLD_5_1_V    = 0x17U, /**<Select LVD reference voltage: 5.1V */
    CY_LVD_HT_THRESHOLD_5_2_V    = 0x18U, /**<Select LVD reference voltage: 5.2V */
    CY_LVD_HT_THRESHOLD_5_3_V    = 0x19U, /**<Select LVD reference voltage: 5.3V */
} cy_en_lvd_ht_tripsel_t;

/**
 * LVD interrupt configuration select.
 */
typedef enum
{
    CY_LVD_HT_INTR_DISABLE    = 0x0U,  /**<Select LVD interrupt: disabled */
    CY_LVD_HT_INTR_RISING     = 0x1U,  /**<Select LVD interrupt: rising edge */
    CY_LVD_HT_INTR_FALLING    = 0x2U,  /**<Select LVD interrupt: falling edge */
    CY_LVD_HT_INTR_BOTH       = 0x3U,  /**<Select LVD interrupt: both edges */
} cy_en_lvd_ht_intr_config_t;

/**
 * LVD Action
 */
typedef enum
{
    CY_LVD_HT_ACTION_INTERRUPT    = 0x0U,  /**<Select LVD Action : Interrupt */
    CY_LVD_HT_ACTION_FAULT        = 0x1U,  /**<Select LVD Action : Fault */
} cy_en_lvd_ht_action_config_t;

/**
 * LVD output status.
 */
typedef enum
{
    CY_LVD_HT_STATUS_BELOW   = 0x0U,  /**<The voltage is below the threshold */
    CY_LVD_HT_STATUS_ABOVE   = 0x1U,  /**<The voltage is above the threshold */
} cy_en_lvd_ht_status_t;

/** \} group_lvd_ht_enums */

/** \cond internal */
/* Macros for conditions used by CY_ASSERT calls */
#define CY_LVD_HT_CHECK_TRIPSEL(threshold)  (((threshold) == CY_LVD_HT_THRESHOLD_2_8_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_2_9_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_0_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_1_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_2_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_3_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_4_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_5_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_6_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_7_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_8_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_3_9_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_0_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_1_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_2_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_3_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_4_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_5_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_6_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_7_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_8_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_4_9_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_5_0_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_5_1_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_5_2_V) || \
                                          ((threshold) == CY_LVD_HT_THRESHOLD_5_3_V))

#define CY_LVD_HT_CHECK_INTR_CFG(intrCfg)   (((intrCfg) == CY_LVD_HT_INTR_DISABLE) || \
                                          ((intrCfg) == CY_LVD_HT_INTR_RISING) || \
                                          ((intrCfg) == CY_LVD_HT_INTR_FALLING) || \
                                          ((intrCfg) == CY_LVD_HT_INTR_BOTH))

#define CY_LVD_HT_CHECK_ACTION_CFG(actionCfg)   (((actionCfg) == CY_LVD_HT_ACTION_INTERRUPT) || \
                                              ((actionCfg) == CY_LVD_HT_ACTION_FAULT))

#define CY_LVD_HT_CHECK_LVD_SELECT(lvdNum)   (((lvdNum) == CY_LVD_HT_SELECT_LVD_1) || \
                                              ((lvdNum) == CY_LVD_HT_SELECT_LVD_2))

/** \endcond */

/**
* \addtogroup group_lvd_ht_functions
* \{
*/
__STATIC_INLINE void Cy_LVD_HT_Enable(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_Disable(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_SetThreshold(cy_en_lvd_ht_select_t lvdNum, cy_en_lvd_ht_tripsel_t threshold);
__STATIC_INLINE cy_en_lvd_ht_status_t Cy_LVD_HT_GetStatus(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE uint32_t Cy_LVD_HT_GetInterruptStatus(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_ClearInterrupt(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_SetInterrupt(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE uint32_t Cy_LVD_HT_GetInterruptMask(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_SetInterruptMask(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_ClearInterruptMask(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE uint32_t Cy_LVD_HT_GetInterruptStatusMasked(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_SetInterruptConfig(cy_en_lvd_ht_select_t lvdNum, cy_en_lvd_ht_intr_config_t lvdInterruptConfig);
__STATIC_INLINE void Cy_LVD_HT_DeepSleepEnable(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_DeepSleepDisable(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE void Cy_LVD_HT_SetActionConfig(cy_en_lvd_ht_select_t lvdNum, cy_en_lvd_ht_action_config_t lvdActionConfig);
__STATIC_INLINE cy_en_lvd_ht_action_config_t Cy_LVD_HT_GetActionConfig(cy_en_lvd_ht_select_t lvdNum);
__STATIC_INLINE bool Cy_LVD_HT_IsDeepSleepEnabled(cy_en_lvd_ht_select_t lvdNum);

/** \addtogroup group_lvd_ht_functions_syspm_callback
* The driver supports SysPm callback for Deep Sleep transition.
* \{
*/
cy_en_syspm_status_t Cy_LVD_HT_DeepSleepCallback(cy_stc_syspm_callback_params_t * callbackParams, cy_en_syspm_callback_mode_t mode);
/** \} */

/*******************************************************************************
* Function Name: Cy_LVD_HT_Enable
****************************************************************************//**
*
*  Enables the output of the LVD block when the VDDD voltage crosses the
* threshold.
*  See the Configuration Considerations section for details.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_Enable(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_PWR_LVD_CTL |= SRSS_PWR_LVD_CTL_HVLVD1_EN_HT_Msk;
    }
    else
    {
        SRSS_PWR_LVD_CTL2 |= SRSS_PWR_LVD_CTL2_HVLVD2_EN_HT_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_Disable
****************************************************************************//**
*
*  Disables a particular LVD. A low voltage detection interrupt is disabled.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_Disable(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_PWR_LVD_CTL &= (uint32_t) ~SRSS_PWR_LVD_CTL_HVLVD1_EN_HT_Msk;
    }
    else
    {
        SRSS_PWR_LVD_CTL2 &= (uint32_t) ~SRSS_PWR_LVD_CTL2_HVLVD2_EN_HT_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_SetThreshold
****************************************************************************//**
*
*  Sets a threshold for monitoring the VDDD voltage.
*  To prevent propagating a false interrupt, before changing the threshold
*  ensure that the LVD block itself and LVD interrupt are disabled by the
*  \ref Cy_LVD_HT_Disable and \ref Cy_LVD_HT_ClearInterruptMask functions
*  correspondingly.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \param threshold
*  Threshold selection for Low Voltage Detect circuit, \ref cy_en_lvd_ht_tripsel_t.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_SetThreshold(cy_en_lvd_ht_select_t lvdNum, cy_en_lvd_ht_tripsel_t threshold)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));
    CY_ASSERT_L3(CY_LVD_HT_CHECK_TRIPSEL(threshold));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_PWR_LVD_CTL = _CLR_SET_FLD32U(SRSS_PWR_LVD_CTL, SRSS_PWR_LVD_CTL_HVLVD1_TRIPSEL_HT, threshold);
    }
    else
    {
        SRSS_PWR_LVD_CTL2 = _CLR_SET_FLD32U(SRSS_PWR_LVD_CTL2, SRSS_PWR_LVD_CTL2_HVLVD2_TRIPSEL_HT, threshold);
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_GetStatus
****************************************************************************//**
*
*  Returns the status of selected LVD.
*  SRSS LVD Status Register (PWR_LVD_STATUS).
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \return LVD status, \ref cy_en_lvd_ht_status_t.
*
*******************************************************************************/
__STATIC_INLINE cy_en_lvd_ht_status_t Cy_LVD_HT_GetStatus(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','SRSS_PWR_LVD_STATUS_HVLVD1_OUT_Msk extracts only 1 bit value');
        return ((cy_en_lvd_ht_status_t) _FLD2VAL(SRSS_PWR_LVD_STATUS_HVLVD1_OUT, SRSS_PWR_LVD_STATUS));
    }
    else
    {
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','SRSS_PWR_LVD_STATUS2_HVLVD2_OUT_Msk extracts only 1 bit value');
        return ((cy_en_lvd_ht_status_t) _FLD2VAL(SRSS_PWR_LVD_STATUS2_HVLVD2_OUT, SRSS_PWR_LVD_STATUS2));

    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_GetInterruptStatus
****************************************************************************//**
*
*  Returns the status of selected LVD's interrupt.
*  SRSS Interrupt Register (SRSS_INTR).
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \return SRSS Interrupt status
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_LVD_HT_GetInterruptStatus(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        return (SRSS_SRSS_INTR & SRSS_SRSS_INTR_HVLVD1_Msk);
    }
    else
    {
        return (SRSS_SRSS_INTR & SRSS_SRSS_INTR_HVLVD2_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_ClearInterrupt
****************************************************************************//**
*
*  Clears LVD interrupt.
*  SRSS Interrupt Register (SRSS_INTR).
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_ClearInterrupt(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_SRSS_INTR = SRSS_SRSS_INTR_HVLVD1_Msk;
    }
    else
    {
        SRSS_SRSS_INTR = SRSS_SRSS_INTR_HVLVD2_Msk;
    }

    (void) SRSS_SRSS_INTR;
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_SetInterrupt
****************************************************************************//**
*
*  Triggers the device to generate interrupt for LVD.
*  SRSS Interrupt Set Register (SRSS_INTR_SET).
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_SetInterrupt(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_SRSS_INTR_SET |= SRSS_SRSS_INTR_SET_HVLVD1_Msk;
    }
    else
    {
        SRSS_SRSS_INTR_SET |= SRSS_SRSS_INTR_SET_HVLVD2_Msk;
    }
}


/*******************************************************************************
* Function Name:  Cy_LVD_HT_GetInterruptMask
****************************************************************************//**
*
*  Returns the mask value of LVD interrupts.
*  SRSS Interrupt Mask Register (SRSS_INTR_MASK).
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \return SRSS Interrupt Mask value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_LVD_HT_GetInterruptMask(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        return (SRSS_SRSS_INTR_MASK & SRSS_SRSS_INTR_MASK_HVLVD1_Msk);
    }
    else
    {
        return (SRSS_SRSS_INTR_MASK & SRSS_SRSS_INTR_MASK_HVLVD2_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_SetInterruptMask
****************************************************************************//**
*
* Enables LVD interrupts.
* Sets the LVD interrupt mask in the SRSS_INTR_MASK register.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_SetInterruptMask(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_SRSS_INTR_MASK |= SRSS_SRSS_INTR_MASK_HVLVD1_Msk;
    }
    else
    {
        SRSS_SRSS_INTR_MASK |= SRSS_SRSS_INTR_MASK_HVLVD2_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_ClearInterruptMask
****************************************************************************//**
*
* Disables LVD interrupts.
* Clears the LVD interrupt mask in the SRSS_INTR_MASK register.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_ClearInterruptMask(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_SRSS_INTR_MASK &= (uint32_t) ~SRSS_SRSS_INTR_MASK_HVLVD1_Msk;
    }
    else
    {
        SRSS_SRSS_INTR_MASK &= (uint32_t) ~SRSS_SRSS_INTR_MASK_HVLVD2_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_GetInterruptStatusMasked
****************************************************************************//**
*
*  Returns the masked interrupt status which is a bitwise AND between the
*  interrupt status and interrupt mask registers.
*  SRSS Interrupt Masked Register (SRSS_INTR_MASKED).
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \return SRSS Interrupt Masked value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_LVD_HT_GetInterruptStatusMasked(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        return (SRSS_SRSS_INTR_MASKED & SRSS_SRSS_INTR_MASK_HVLVD1_Msk);
    }
    else
    {
        return (SRSS_SRSS_INTR_MASKED & SRSS_SRSS_INTR_MASK_HVLVD2_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_SetInterruptConfig
****************************************************************************//**
*
*  Sets a configuration for specified LVD interrupt.
*  HVLVD Configuration Register (PWR_LVD_CTL or PWR_LVD_CTL2).
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \param lvdInterruptConfig \ref cy_en_lvd_ht_intr_config_t.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_SetInterruptConfig(cy_en_lvd_ht_select_t lvdNum, cy_en_lvd_ht_intr_config_t lvdInterruptConfig)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));
    CY_ASSERT_L3(CY_LVD_HT_CHECK_INTR_CFG(lvdInterruptConfig));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_PWR_LVD_CTL = _CLR_SET_FLD32U(SRSS_PWR_LVD_CTL, SRSS_PWR_LVD_CTL_HVLVD1_EDGE_SEL, lvdInterruptConfig);
    }
    else
    {
        SRSS_PWR_LVD_CTL2 = _CLR_SET_FLD32U(SRSS_PWR_LVD_CTL2, SRSS_PWR_LVD_CTL2_HVLVD2_EDGE_SEL, lvdInterruptConfig);
    }
}

/*******************************************************************************
* Function Name: Cy_LVD_HT_SetActionConfig
****************************************************************************//**
*
*  Sets a action configuration after LVD block reaches threshold.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \param lvdActionConfig \ref cy_en_lvd_ht_action_config_t.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_SetActionConfig(cy_en_lvd_ht_select_t lvdNum, cy_en_lvd_ht_action_config_t lvdActionConfig)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));
    CY_ASSERT_L3(CY_LVD_HT_CHECK_ACTION_CFG(lvdActionConfig));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_PWR_LVD_CTL = _CLR_SET_FLD32U(SRSS_PWR_LVD_CTL, SRSS_PWR_LVD_CTL_HVLVD1_ACTION, lvdActionConfig);
    }
    else
    {
        SRSS_PWR_LVD_CTL2 = _CLR_SET_FLD32U(SRSS_PWR_LVD_CTL2, SRSS_PWR_LVD_CTL2_HVLVD2_ACTION, lvdActionConfig);
    }
}

/*******************************************************************************
* Function Name: Cy_LVD_HT_GetActionConfig
****************************************************************************//**
*
*  Gets the action configured after LVD reaches threshold.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \return \ref cy_en_lvd_ht_action_config_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_lvd_ht_action_config_t Cy_LVD_HT_GetActionConfig(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        return (((SRSS_PWR_LVD_CTL & SRSS_PWR_LVD_CTL_HVLVD1_ACTION_Msk) != 0UL) ? CY_LVD_HT_ACTION_FAULT : CY_LVD_HT_ACTION_INTERRUPT);
    }
    else
    {
        return (((SRSS_PWR_LVD_CTL2 & SRSS_PWR_LVD_CTL2_HVLVD2_ACTION_Msk) != 0UL) ? CY_LVD_HT_ACTION_FAULT : CY_LVD_HT_ACTION_INTERRUPT);
    }
}

/*******************************************************************************
* Function Name: Cy_LVD_HT_DeepSleepEnable
****************************************************************************//**
*
*  Enables selected LVD block during Deep Sleep.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
* \note
* For enabling, call this API before the system enters first DEEPSLEEP entry,
* else if we enable in the second or subsequent DEEPSLEEP entries then it might
* not wake the system from DEEPSLEEP through LVD.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_DeepSleepEnable(cy_en_lvd_ht_select_t lvdNum)
{
    CY_ASSERT_L3(CY_LVD_HT_CHECK_LVD_SELECT(lvdNum));

    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_PWR_LVD_CTL |= SRSS_PWR_LVD_CTL_HVLVD1_DPSLP_EN_HT_Msk;
    }
    else
    {
        SRSS_PWR_LVD_CTL2 |= SRSS_PWR_LVD_CTL2_HVLVD2_DPSLP_EN_HT_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_LVD_HT_DeepSleepDisable
****************************************************************************//**
*
*  Disables selected LVD block during Deep Sleep.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
* \note
* After Cy_LVD_HT_DeepSleepDisable call, you have to reinitialize LVD according
* to recommended LVD Init sequence, else it might not wake the system from
* DEEPSLEEP through LVD after calling Cy_LVD_HT_DeepSleepEnable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LVD_HT_DeepSleepDisable(cy_en_lvd_ht_select_t lvdNum)
{
    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        SRSS_PWR_LVD_CTL &= (uint32_t) ~SRSS_PWR_LVD_CTL_HVLVD1_DPSLP_EN_HT_Msk;
    }
    else
    {
        SRSS_PWR_LVD_CTL2 &= (uint32_t) ~SRSS_PWR_LVD_CTL2_HVLVD2_DPSLP_EN_HT_Msk;
    }
}

/*******************************************************************************
* Function Name: Cy_LVD_HT_IsDeepSleepEnabled
****************************************************************************//**
*
*  Checks if LVD HT is enabled during Deep Sleep or not.
*
*  \param lvdNum
*   Selects the LVD, \ref cy_en_lvd_ht_select_t
*
*  \return - True if LVD HT is enabled during Deep Sleep, otherwise False.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_LVD_HT_IsDeepSleepEnabled(cy_en_lvd_ht_select_t lvdNum)
{
    if(lvdNum == CY_LVD_HT_SELECT_LVD_1)
    {
        return (((SRSS_PWR_LVD_CTL & SRSS_PWR_LVD_CTL_HVLVD1_DPSLP_EN_HT_Msk) != 0UL) ? true : false);
    }
    else
    {
        return (((SRSS_PWR_LVD_CTL2 & SRSS_PWR_LVD_CTL2_HVLVD2_DPSLP_EN_HT_Msk) != 0UL) ? true : false);
    }
}


/** \} group_lvd_ht_functions */

#ifdef __cplusplus
}
#endif

#endif /* CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

#endif /* CY_LVD_HT_H */

/** \} group_lvd_ht */


/* [] END OF FILE */
