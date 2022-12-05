/**
 ****************************************************************************************
 *
 * @file smpc_util.h
 *
 * @brief Header file for SMPC utilities.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef SMPC_UTIL_H_
#define SMPC_UTIL_H_

/**
 ****************************************************************************************
 * @addtogroup SMPC_UTIL Utility
 * @ingroup SMPC
 * @brief Contains utility functions and macros for SMPC.
 *
 * The SMPC Utilities block contains key generating and security related functions
 * that are useful in accomplishing the task of the security manager protocol
 * layer of the Bluetooth Low Energy.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_SMPC)

#include "smp_common.h"
#include <string.h>

#include "l2cc_pdu.h"
#include "smpc_int.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// SMPC command PDU construct function pointer type definition
typedef void (*smpc_construct_pdu_t)(struct l2cc_pdu *pdu, void *value);

/// SMPC command PDU reception functions
typedef void (*smpc_recv_pdu_t)(uint8_t idx, struct l2cc_pdu *pdu);

/*
 * GLOBAL VARIABLES DECLARATION
 ****************************************************************************************
 */

extern const smpc_construct_pdu_t smpc_construct_pdu[L2C_CODE_SECURITY_MAX];
extern const smpc_recv_pdu_t smpc_recv_pdu[L2C_CODE_SECURITY_MAX];

/*
 * FUNCTIONS DECLARATION
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Parameter checking function of SMP PDU packets.
 *
 * @param[in] pdu   Pointer to the data part of the SMP command PDU.
 *
 * @return Value of check parameter status, to be reported to host or back to peer.
 ****************************************************************************************
 */
uint8_t smpc_check_param(struct l2cc_pdu *pdu);

#endif //(BLE_SMPC)
#endif //(SMPC_UTIL_H_)

/// @} SMPC_UTIL
