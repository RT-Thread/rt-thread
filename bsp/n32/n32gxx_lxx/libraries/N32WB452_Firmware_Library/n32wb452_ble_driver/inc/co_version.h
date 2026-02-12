/**
 ****************************************************************************************
 *
 * @file co_version.h
 *
 * @brief Version definitions for BT4.2
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef _CO_VERSION_H_
#define _CO_VERSION_H_
/**
 ****************************************************************************************
 * @defgroup CO_VERSION Version Defines
 * @ingroup COMMON
 *
 * @brief Bluetooth Controller Version definitions.
 *
 * @{
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"        // SW configuration options

#if (BLE_QUALIF)
/// RWBT SW Major Version
#define RWBT_SW_VERSION_MAJOR                   (RW_BT40_VERSION)
#else
/// RWBT SW Major Version
#define RWBT_SW_VERSION_MAJOR                   (RW_BT42_VERSION)
#endif
/// RWBT SW Minor Version
#define RWBT_SW_VERSION_MINOR                   3
/// RWBT SW Build Version
#define RWBT_SW_VERSION_BUILD                   31

/// RWBT SW Major Version
#define RWBT_SW_VERSION_SUB_BUILD               0


/// @} CO_VERSION


#endif // _CO_VERSION_H_
