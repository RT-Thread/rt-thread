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
* \brief This file implements the platform abstraction layer APIs for timer.
*
* \addtogroup  grPAL
* @{
*/

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "pal_os_timer.h"
#include "nrf_delay.h"
#include "nrf_rtc.h"
#include "nrf_drv_rtc.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
 
/// @cond hidden 
/*********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/
// Defined in pal_os_event.c
extern volatile uint32_t g_tick_count;

/**********************************************************************************************************************
 * LOCAL ROUTINES
 *********************************************************************************************************************/
/// @endcond

/**********************************************************************************************************************
 * API IMPLEMENTATION
 *********************************************************************************************************************/
/**
* Get the current time in milliseconds<br>
*
*
* \retval  uint32_t time in milliseconds
*/
uint32_t pal_os_timer_get_time_in_milliseconds(void)
{
    return (g_tick_count);
}

/**
* Function to wait or delay until the given milliseconds time
* 
* \param[in] milliseconds Delay value in milliseconds
*
*/
void pal_os_timer_delay_in_milliseconds(uint16_t milliseconds)
{
    nrf_delay_ms(milliseconds);
}

/**
* @}
*/

