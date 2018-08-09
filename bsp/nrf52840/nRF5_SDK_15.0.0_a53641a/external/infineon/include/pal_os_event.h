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
* \brief   This file implements the prototype declarations of pal os event
*
* \addtogroup  grPAL
* @{
*/


#ifndef _PAL_OS_EVENT_H_
#define _PAL_OS_EVENT_H_

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
 
#include "Datatypes.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * ENUMS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * PAL extern definitions
 *********************************************************************************************************************/
 
/**
 * @brief typedef for Callback function when timer elapses.
 */
typedef void (*register_callback)(void*);

/**
 * \brief Initializes the OS event PAL.
 */
void pal_os_event_init(void);

/**
 * @brief Callback registration function to trigger once when timer expires.
 */
void pal_os_event_register_callback_oneshot(register_callback callback, void* callback_args, uint32_t time_us);

#endif //_PAL_OS_EVENT_H_

/**
* @}
*/
