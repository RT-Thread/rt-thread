/** @file sys_common.h
*   @brief Common Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - General Definitions
*   .
*   which are relevant for all drivers.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __SYS_COMMON_H__
#define __SYS_COMMON_H__

#include "hal_stdtypes.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/************************************************************/
/* Type Definitions                                         */
/************************************************************/

#ifndef _TBOOLEAN_DECLARED
typedef boolean tBoolean;
#define _TBOOLEAN_DECLARED
#endif

/** @enum loopBackType
*   @brief Loopback type definition
*/
/** @typedef loopBackType_t
*   @brief Loopback type Type Definition
*
*   This type is used to select the module Loopback type Digital or Analog loopback.
*/
typedef enum loopBackType 
{
    Digital = 0U, 
    Analog = 1U
}loopBackType_t;

/** @enum config_value_type
*   @brief config type definition
*/
/** @typedef config_value_type_t
*   @brief config type Type Definition
*
*   This type is used to specify the Initial and Current value.
*/
typedef enum config_value_type
{
	InitialValue,
	CurrentValue
}config_value_type_t;

/* USER CODE BEGIN (1) */
/* USER CODE END */

/********************************************************************************/
/* The ASSERT macro, which does the actual assertion checking.  Typically, this */
/* will be for procedure arguments.                                             */
/********************************************************************************/
#ifdef DEBUG
#define ASSERT(expr) {                                      \
                         if(!(expr))                        \
                         {                                  \
                             __error__(__FILE__, __LINE__); \
                         }                                  \
                     }
#else
#define ASSERT(expr)
#endif

/* USER CODE BEGIN (2) */
/* USER CODE END */

#endif
