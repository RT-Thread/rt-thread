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
* \brief This file implements the prototype declarations of pal gpio
*
* \addtogroup  grPAL
* @{
*/

#ifndef _PAL_GPIO_H_
#define _PAL_GPIO_H_

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
 
#include "pal.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * ENUMS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DATA STRUCTURES
 *********************************************************************************************************************/

/**
 * \brief Structure defines the PAL GPIO configuration.
 */
typedef struct pal_gpio
{
    /// Pointer to gpio platform specific context/structure
    void* p_gpio_hw;

} pal_gpio_t;

/**********************************************************************************************************************
 * API Prototypes
 *********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initializes the GPIO PAL.
 */
void pal_gpio_init(void);

/**
 * \brief Sets the gpio pin to high state.
 */
void pal_gpio_set_high(const pal_gpio_t* p_gpio_context);

/**
 * \brief Sets the gpio pin to Low state.
 */
void pal_gpio_set_low(const pal_gpio_t* p_gpio_context);

#ifdef __cplusplus
}
#endif

#endif /* _PAL_GPIO_H_ */

/**
* @}
*/

