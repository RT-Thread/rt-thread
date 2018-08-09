/**
* \copyright
* Copyright (c) 2018, Infineon Technologies AG
* All rights reserved.
*
* This software is provided with terms and conditions as specified in OPTIGA(TM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author Infineon AG
*
* \file
*
* \brief This file implements the platform abstraction layer APIs for gpio.
*
* \addtogroup  grPAL
* @{
*/


/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "pal_gpio.h"
#include "nrf_gpio.h"
#include "pal_ifx_i2c_config.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL ROUTINES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API IMPLEMENTATION
 *********************************************************************************************************************/

void pal_gpio_init()
{
    // Init power pins
    nrf_gpio_cfg_output(19);
    nrf_gpio_cfg_output(20);

    // Set power pins to enable power
    nrf_gpio_pin_clear(19); // Enable power for the *on-board* Trust X device
    nrf_gpio_pin_set(20);   // Disable power for *external* Trust X device inside the 2GO slot

    // Init reset pin
    nrf_gpio_cfg_output((uint32_t)(optiga_reset_0.p_gpio_hw));
}

/**
* Sets the GPIO pin to high state
* 
* <b>API Details:</b>
*      The API sets the pin high, only if the pin is assigned to a valid gpio context.<br>
*      Otherwise the API returns without any failure status.<br>
*
*\param[in] p_gpio_context Pointer to pal layer gpio context
*
*
*/
void pal_gpio_set_high(const pal_gpio_t* p_gpio_context)
{
    if (p_gpio_context != NULL && p_gpio_context->p_gpio_hw != NULL)
    {
        nrf_gpio_pin_set((uint32_t)(p_gpio_context->p_gpio_hw));
    }
}

/**
* Sets the gpio pin to low state
*
* <b>API Details:</b>
*      The API set the pin low, only if the pin is assigned to a valid gpio context.<br>
*      Otherwise the API returns without any failure status.<br>
* 
*\param[in] p_gpio_context Pointer to pal layer gpio context
*
*/
void pal_gpio_set_low(const pal_gpio_t* p_gpio_context)
{
    if (p_gpio_context != NULL && p_gpio_context->p_gpio_hw != NULL)
    {
        nrf_gpio_pin_clear((uint32_t)(p_gpio_context->p_gpio_hw));
    }
}

/**
* @}
*/

