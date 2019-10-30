/***************************************************************************//**
* \file cy_ble_clk.h
* \version 2.30
*
* \brief
*  Contains the function prototypes and constants for the BLE clock.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_BLE_CLK_H
#define CY_BLE_CLK_H

#include "cy_device_headers.h"
#include <stddef.h>
#include "cy_ble_config.h"
#include "syslib/cy_syslib.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/******************************************************************************
 *      Macro definitions                                         
 ******************************************************************************/

 #define CY_BLE_CLK_ID                                   (0x05ul << 18u)


/*******************************************************************************
*       Data Types
*******************************************************************************/

/**
 * \addtogroup group_ble_clock_api_data_types
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
    
} cy_en_ble_bless_eco_freq_t;

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
    
} cy_en_ble_bless_sys_eco_clk_div_t;

/** BLE ECO Clock return value */
typedef enum
{
    /** ECO started successfully */
    CY_BLE_ECO_SUCCESS         = 0x00UL,

    /** Invalid input parameters values */
    CY_BLE_ECO_BAD_PARAM       = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0001UL,

    /** RCB is not available for Firmware control to restart ECO */
    CY_BLE_ECO_RCB_CONTROL_LL  = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0002UL,

    /** ECO already started */
    CY_BLE_ECO_ALREADY_STARTED = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0003UL,
    
    /** Hardware error */
    CY_BLE_ECO_HARDWARE_ERROR  = CY_PDL_STATUS_ERROR | CY_BLE_CLK_ID | 0x0004UL,
    
} cy_en_ble_eco_status_t;

/** BLE ECO configuration parameters */
typedef struct
{
    /** ECO crystal start-up time in multiple of 31.25us (startup_time_from_user min - 31.25us)
     * ecoXtalStartUpTime = startup_time_from_user/31.25 */
    uint8_t                           ecoXtalStartUpTime;

    /** ECO crystal load capacitance - In multiple of 0.075pF (pF_from_user min - 7.5pF, pF_from_user max - 26.625pF)
     * loadcap = ((pF_from_user - 7.5)/0.075) */
    uint8_t                           loadCap;

    /** ECO Frequency. */
    cy_en_ble_bless_eco_freq_t        ecoFreq;

    /** System divider for ECO clock */
    cy_en_ble_bless_sys_eco_clk_div_t ecoSysDiv;
    
} cy_stc_ble_bless_eco_cfg_params_t;
/** \} */


/******************************************************************************
 *       Function Prototypes                                        
 ******************************************************************************/

/**
 * \addtogroup group_ble_clock_api
 * \{
 */
cy_en_ble_eco_status_t Cy_BLE_EcoStart(const cy_stc_ble_bless_eco_cfg_params_t *ecoConfig);
void Cy_BLE_EcoStop(void);
/** \} */


/******************************************************************************
 *       Private Function Prototypes                                     
 ******************************************************************************/

void Cy_BLE_HAL_Init(void);
uint8_t Cy_BLE_HAL_IsEcoCpuClockSrc(void);
uint8_t Cy_BLE_HAL_IsWcoLfclkSrc(void);
uint32_t Cy_BLE_HAL_EcoGetFrequency(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CY_BLE_CLK_H */


/* [] END OF FILE */
