/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

// TIN-TODO: The definitions were moved here from Tin's bsp_common.h. Consider removing them from here
// and adding them to another header file.

#ifndef BSP_RTM_RA6W1_H
#define BSP_RTM_RA6W1_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RTM_TIME_PTR    ((time_in_rtm_t *) dg_configAPPSUPP_RTM_ADDR)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Temporary global time rtm structure located in parallel to ‘_dpm_flag_in_rtm’ structure,
 * till dpm rtm mapping re-order (moving it to a common place) will be done. */
typedef struct _time_in_rtm
{
    long               __timezone;     /* timezone */
    unsigned long long systime_offset; /* msec */
    unsigned long long rtc_oldtime;    /* msec */
} time_in_rtm_t;

/* Support 64bit time */
typedef unsigned long long __time64_t;
typedef __time64_t         ra6w1_time_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
