/***************************************************************************//**
* \file cy_ble_clk.h
* \version 3.60
*
* The header file of the BLE ECO clock driver.
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
* \addtogroup group_ble_clk
* \{
* This driver provides an API to manage the BLE ECO clock block.
*
* The functions and other declarations used in this driver are in cy_ble_clk.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* The BLE ECO clock is a high-accuracy high-frequency clock that feeds the
* link-layer controller and the radio Phy.
*
* This clock is also an input to the system resources subsystem as an
* alternative high-frequency clock source (ALTHF).
*
* \section group_ble_configuration_considerations Configuration Considerations
* To configure the BLE ECO clock, call Cy_BLE_EcoConfigure().
*
* The following code shows how to configure the BLE ECO clock:
* \snippet bleclk/snippet/main.c BLE ECO clock API: Cy_BLE_EcoConfigure()
*
* \section group_ble_clk_more_information More Information
* See the BLE chapter of the device technical reference manual (TRM).
*
* \section group_ble_clk_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason of Change</th></tr>
*   <tr>
*     <td>3.60</td>
*     <td>MISRA</td>
*     <td>Resolve MISRA 2012 standard defects.</td>
*   </tr>
*   <tr>
*     <td>3.50</td>
*     <td>Updated \ref Cy_BLE_EcoConfigure, \ref Cy_BLE_EcoReset functions
*         for PSoC 64 devices. Now the \ref Cy_BLE_EcoConfigure function can
*         return PRA driver status value for PSoC 64 devices.</td>
*     <td>The BLE ECO clock driver uses the PRA driver to change the frequency
*         value on the protected side. A BLE ECO clock driver function that
*         calls a PRA driver function will return the PRA error status code
*         if the called PRA function returns an error. In these cases,
*         refer to PRA return statuses. Refer to functions description for
*         details.</td>
*   </tr>
*   <tr>
*     <td>3.40.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>3.40</td>
*     <td>A new API function \ref Cy_BLE_EcoIsEnabled() is added.</td>
*     <td>API enhancement.</td>
*   </tr>
*   <tr>
*     <td>3.30</td>
*     <td>Updated the \ref Cy_BLE_EcoConfigure() to reuse the \ref Cy_SysClk_ClkPeriGetFrequency().</td>
*     <td>API enhancement.</td>
*   </tr>
*   <tr>
*     <td>3.20</td>
*     <td>Updated the Cy_BLE_EcoConfigure(): it stores the ECO frequency for possible frequency calculation by the Cy_SysClk_ClkHfGetFrequency().</td>
*     <td>API enhancement.</td>
*   </tr>
*   <tr>
*     <td>3.10</td>
*     <td>Updated the Cy_BLE_EcoConfigure() use case, when the voltageReg parameter is CY_BLE_ECO_VOLTAGE_REG_BLESSLDO
*         and the Buck core regulator is enabled.</td>
*     <td>Defect fixing: Before, when the Cy_BLE_EcoConfigure() function included the BLE LDO regulator option, the function returned CY_BLE_ECO_HARDWARE_ERROR if
*         the Buck core regulator had been enabled.</td>
*   </tr>
*   <tr>
*     <td>3.0</td>
*     <td>The initial version. \n The functionality of the BLE ECO clock is migrated from the BLE Middleware to the separated driver (ble_clk).</td>
*     <td>Independent usage of BLE ECO clock without BLE Middleware.</td>
*   </tr>
* </table>
*
* \defgroup group_ble_clk_functions Functions
* \defgroup group_ble_clk_data_type Enumerated Types
* \defgroup group_ble_clk_macros Macros
*
*/

#if !defined(CY_BLE_CLK_H)
#define CY_BLE_CLK_H

#include "cy_device.h"

#if defined (CY_IP_MXBLESS) && defined (CY_IP_MXS40IOSS)

#include <stddef.h>
#include "cy_syslib.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*******************************************************************************
*       Macro definitions
*******************************************************************************/

/**
 * \addtogroup group_ble_clk_macros
 * \{
 */
/** Driver major version */
#define CY_BLE_CLK_DRV_VERSION_MAJOR    (3)

/** Driver minor version */
#define CY_BLE_CLK_DRV_VERSION_MINOR    (60)

/** Driver ID */
#define CY_BLE_CLK_ID                   (0x05UL << 18U)
/** \} */


/*******************************************************************************
*       Data Types
*******************************************************************************/

/**
 * \addtogroup group_ble_clk_data_type
 * \{
 */
/** BLE Radio ECO clock divider */
typedef enum
{
    CY_BLE_MXD_RADIO_CLK_DIV_1  = 0U,
    CY_BLE_MXD_RADIO_CLK_DIV_2  = 1U,
    CY_BLE_MXD_RADIO_CLK_DIV_4  = 2U,
    CY_BLE_MXD_RADIO_CLK_DIV_8  = 4U,
    CY_BLE_MXD_RADIO_CLK_DIV_16 = 8U
} cy_en_ble_mxd_radio_clk_div_t;

/** Sine wave buffer output capability select */
typedef enum
{
    CY_BLE_MXD_RADIO_CLK_BUF_AMP_16M_SMALL = 0U,
    CY_BLE_MXD_RADIO_CLK_BUF_AMP_16M_LARGE = 1U,
    CY_BLE_MXD_RADIO_CLK_BUF_AMP_32M_SMALL = 2U,
    CY_BLE_MXD_RADIO_CLK_BUF_AMP_32M_LARGE = 3U
} cy_en_ble_mxd_radio_clk_buf_amp_t;

/** BLESS clock divider */
typedef enum
{
    CY_BLE_BLESS_XTAL_CLK_DIV_1 = 0U,
    CY_BLE_BLESS_XTAL_CLK_DIV_2 = 1U,
    CY_BLE_BLESS_XTAL_CLK_DIV_4 = 2U,
    CY_BLE_BLESS_XTAL_CLK_DIV_8 = 3U
}cy_en_ble_bless_xtal_clk_div_config_llclk_div_t;

/** BLE ECO Clock Frequency. */
typedef enum
{
    /** ECO Frequency of 16MHz */
    CY_BLE_BLESS_ECO_FREQ_16MHZ,

    /** ECO Frequency of 32MHz */
    CY_BLE_BLESS_ECO_FREQ_32MHZ
} cy_en_ble_eco_freq_t;

/** BLE ECO System clock divider */
typedef enum
{
    /** Link Layer clock divider = 1 */
    CY_BLE_SYS_ECO_CLK_DIV_1 = 0x00U,

    /** Link Layer clock divider = 2 */
    CY_BLE_SYS_ECO_CLK_DIV_2,

    /** Link Layer clock divider = 4 */
    CY_BLE_SYS_ECO_CLK_DIV_4,

    /** Link Layer clock divider = 8 */
    CY_BLE_SYS_ECO_CLK_DIV_8,

    /** Invalid Link Layer clock divider */
    CY_BLE_SYS_ECO_CLK_DIV_INVALID

} cy_en_ble_eco_sys_clk_div_t;

/** BLE ECO Clock return value */
typedef enum
{
    /** ECO started successfully */
    CY_BLE_ECO_SUCCESS         = 0x00UL,

    /** Invalid input param values */
    CY_BLE_ECO_BAD_PARAM       = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0001UL,

    /** RCB is not available for Firmware control to restart ECO */
    CY_BLE_ECO_RCB_CONTROL_LL  = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0002UL,

    /** ECO already started */
    CY_BLE_ECO_ALREADY_STARTED = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0003UL,

    /** Hardware error */
    CY_BLE_ECO_HARDWARE_ERROR  = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0004UL,

} cy_en_ble_eco_status_t;

/** BLE Voltage regulator */
typedef enum
{
    /** Use SIMO Buck or BLE LDO regulator depend on system usage */
    CY_BLE_ECO_VOLTAGE_REG_AUTO,

    /** Use BLE LDO */
    CY_BLE_ECO_VOLTAGE_REG_BLESSLDO

} cy_en_ble_eco_voltage_reg_t;
/** \} */


/*******************************************************************************
*       Configuration Structures
*******************************************************************************/

/** \cond INTERNAL */
/** BLE ECO configuration structures */
typedef struct
{
    /**
     *  ECO crystal startup time in multiple of 31.25us (startup_time_from_user min - 31.25us)
     *  ecoXtalStartUpTime = startup_time_from_user/31.25
     */
    uint8_t                           ecoXtalStartUpTime;

    /**
     *  ECO crystal load capacitance - In multiple of 0.075pF (pF_from_user min - 7.5pF, pF_from_user max - 26.625pF)
     *  loadcap = ((pF_from_user - 7.5)/0.075)
     */
    uint8_t                           loadCap;

    /** ECO Frequency. */
    cy_en_ble_eco_freq_t              ecoFreq;

    /** System divider for ECO clock. */
    cy_en_ble_eco_sys_clk_div_t       ecoSysDiv;

} cy_stc_ble_eco_config_t;

#if (defined(CY_DEVICE_SECURE))
/** PRA structure for Cy_BLE_EcoConfigure function parameters */
typedef struct
{
    cy_en_ble_eco_freq_t freq;
    cy_en_ble_eco_sys_clk_div_t sysClkDiv;
    uint32_t cLoad;
    uint32_t xtalStartUpTime;
    cy_en_ble_eco_voltage_reg_t voltageReg;
} cy_stc_pra_ble_eco_config_t;
#endif /* (defined(CY_DEVICE_SECURE)) */

/** \endcond */


/*******************************************************************************
*       Function Prototypes
*******************************************************************************/

/**
 * \addtogroup group_ble_clk_functions
 * \{
 */
cy_en_ble_eco_status_t Cy_BLE_EcoConfigure(cy_en_ble_eco_freq_t freq,
                                    cy_en_ble_eco_sys_clk_div_t sysClkDiv,
                                                       uint32_t cLoad,
                                                       uint32_t xtalStartUpTime,
                                    cy_en_ble_eco_voltage_reg_t voltageReg);
void Cy_BLE_EcoReset(void);
__STATIC_INLINE bool Cy_BLE_EcoIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_BLE_EcoIsEnabled
****************************************************************************//**
*
*  Reports the Enabled/Disabled BLE ECO status.
*
*  \return Boolean status of BLE ECO: true - Enabled, false - Disabled.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_BLE_EcoIsEnabled(void)
{
    return (((BLE_BLESS_MT_CFG & BLE_BLESS_MT_CFG_ENABLE_BLERD_Msk) != 0u) &&
            ((BLE_BLESS_MT_STATUS & BLE_BLESS_MT_STATUS_BLESS_STATE_Msk) != 0u));
}
/** \} */

/** \cond INTERNAL */
cy_en_ble_eco_status_t Cy_BLE_EcoStart(const cy_stc_ble_eco_config_t *config);
void Cy_BLE_EcoStop(void);
/** \endcond */


/*******************************************************************************
*       Private Function Prototypes
*******************************************************************************/

/** \cond INTERNAL */
void Cy_BLE_HAL_Init(void);


/*******************************************************************************
*       Backwards compatibility macros
*******************************************************************************/

#define cy_stc_ble_bless_eco_cfg_params_t   cy_stc_ble_eco_config_t
#define cy_en_ble_bless_sys_eco_clk_div_t   cy_en_ble_eco_sys_clk_div_t
#define cy_en_ble_bless_eco_freq_t          cy_en_ble_eco_freq_t
/** \endcond */


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* defined(CY_IP_MXBLESS) */
#endif /* CY_BLE_CLK_H */

/** \} group_ble_clk */

/* [] END OF FILE */
