/**
* \copyright
* Copyright(c) 2018, Infineon Technologies AG
* All rights reserved.
*
* This software is provided with terms and conditions as specified in OPTIGA(RM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author Infineon AG
*
* \file
*
* \brief This file implements platform abstraction layer configurations for ifx i2c protocol.
*
* \addtogroup  grPAL
* @{
*/

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "pal_gpio.h"
#include "pal_i2c.h"
#include "ifx_i2c_config.h"

/*********************************************************************************************************************
 * pal ifx i2c instance
 *********************************************************************************************************************/
/**
 * \brief PAL I2C configuration for OPTIGA. 
 */
pal_i2c_t optiga_pal_i2c_context_0 =
{
    /// Pointer to I2C master platform specific context
    NULL,
    /// Slave address
    IFX_I2C_BASE_ADDR,
    /// Upper layer context
    NULL,
    /// Callback event handler
    NULL
};

/*********************************************************************************************************************
 * PAL GPIO configurations defined for XMC4500
 *********************************************************************************************************************/
/**
* \brief PAL vdd pin configuration for OPTIGA. 
 */
pal_gpio_t optiga_vdd_0 =
{
    // Platform specific GPIO context for the pin used to toggle Vdd.
    (void*)NULL
};

/**
 * \brief PAL reset pin configuration for OPTIGA.
 */
pal_gpio_t optiga_reset_0 =
{
    // Platform specific GPIO context for the pin used to toggle Reset.
    (void*)18
};


/**
* @}
*/

