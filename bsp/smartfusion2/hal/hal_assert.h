/*******************************************************************************
 * (c) Copyright 2008-2013 Microsemi SoC Products Group. All rights reserved.
 * 
 * SVN $Revision: 7375 $
 * SVN $Date: 2015-05-01 19:27:40 +0530 (Fri, 01 May 2015) $
 */
#ifndef HAL_ASSERT_HEADER
#define HAL_ASSERT_HEADER

#ifdef MSCC_NO_RELATIVE_PATHS
#include "mss_assert.h"
#else
#include "../CMSIS/mss_assert.h"
#endif

#if defined(NDEBUG)
/***************************************************************************//**
 * HAL_ASSERT() is defined out when the NDEBUG symbol is used.
 ******************************************************************************/
#define HAL_ASSERT(CHECK)

#else
/***************************************************************************//**
 * Default behaviour for HAL_ASSERT() macro:
 *------------------------------------------------------------------------------
 * Using the HAL_ASSERT() macro is the same as directly using the SmartFusion2
 * CMSIS ASSERT() macro. The behaviour is toolchain specific and project
 * setting specific.
 ******************************************************************************/
#define HAL_ASSERT(CHECK)     ASSERT(CHECK);

#endif  /* NDEBUG */

#endif  /* HAL_ASSERT_HEADER */
