/***************************************************************************//**
* \file cy_ble_config.h
* \version 2.20
*
* \brief
*  The user BLE clock configuration file. Allows redefining default 
*  cy_ble_clk.h defines.
*
********************************************************************************
* \copyright
* Copyright 2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_BLE_CLK_CONF_H
#define CY_BLE_CLK_CONF_H

#include <cy_device_headers.h>
#ifndef CY_IP_MXBLESS
    #error "The BLE middleware is not supported on this device"
#endif


/**
 * Use this file to redefine default #define(s) from cy_ble_clk.h
 * example:
 * #define CY_BLE_DEFAULT_ECO_SET_TRIM_DELAY                (900u)
 *
 */


#endif /* !defined(CY_BLE_CLK_CONF_H)*/

/* [] END OF FILE */
