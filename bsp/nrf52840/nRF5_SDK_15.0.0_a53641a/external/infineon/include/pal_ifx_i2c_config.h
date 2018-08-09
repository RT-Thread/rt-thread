/**
* \copyright
* Copyright (c) 2018, Infineon Technologies AG
* All rights reserved.
*
* This software is provided with terms and conditions as specified in OPTIGA(TM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author   Infineon AG
*
* \file
*
* \brief   This file implements the platform abstraction layer extern declarations for ifx i2c.
*
* \addtogroup  grPAL
* @{
*/

#ifndef _PAL_IFX_I2C_CONFIG_H_
#define _PAL_IFX_I2C_CONFIG_H_

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "pal.h"
#include "pal_i2c.h"
#include "pal_gpio.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * ENUMS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * PAL extern definitions for IFX I2C
 *********************************************************************************************************************/
extern pal_i2c_t optiga_pal_i2c_context_0;
extern pal_gpio_t optiga_vdd_0;
extern pal_gpio_t optiga_reset_0;

#endif /* _PAL_IFX_I2C_CONFIG_H_ */

/**
* @}
*/
