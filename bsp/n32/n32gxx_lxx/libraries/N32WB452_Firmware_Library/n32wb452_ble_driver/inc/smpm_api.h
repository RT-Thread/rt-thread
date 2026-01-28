/**
 ****************************************************************************************
 *
 * @file smpm_api.h
 *
 * @brief Header file - SMPM API
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef SMPM_API_H_
#define SMPM_API_H_

/**
 ****************************************************************************************
 * @addtogroup SMPM_API Security Manager Protocol Manager API
 * @ingroup SMPM
 * @brief Provide an API to GAPM task
 *
 * The SMPM is responsible for all security related functions not related to a
 * specific connection with a peer.
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */


#include "rwip_config.h"
#if (BLE_SMPM)
#include "gap.h"                // GAP Definitions

/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * STRUCTURES
 ****************************************************************************************
*/

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Generate a random address
 *
 * @param[in] addr_type    Provided address type
 *
 * @return If request has been processed or not
 ****************************************************************************************
 */
uint8_t smpm_gen_rand_addr(uint8_t addr_type);

/**
 ****************************************************************************************
 * @brief Resolve a random address
 * Note: address should be resolvable
 *
 * @param[in] addr    Device address
 * @param[in] irk     IRK used for address resolution
 *
 ****************************************************************************************
 */
void smpm_resolv_addr(bd_addr_t* addr, struct gap_sec_key *irk);


/**
 ****************************************************************************************
 * @brief Use the encryption block
 *
 * @param[in] operand_1 First operand as encryption block input (16 bytes)
 * @param[in] operand_2 Second operand as encryption block input (16 bytes)
 *
 ****************************************************************************************
 */
void smpm_use_enc_block(uint8_t *operand_1, uint8_t *operand_2);

/**
 ****************************************************************************************
 * @brief Generate a random number
 ****************************************************************************************
 */
void smpm_gen_rand_nb(void);



/**
 ****************************************************************************************
 * @brief Send an encryption request to the HCI.
 ****************************************************************************************
 */
void smpm_send_encrypt_req(uint8_t *operand_1, uint8_t *operand_2);

#if (SECURE_CONNECTIONS)
/**
 ****************************************************************************************
 * @brief Send a generate DH Key request to the HCI.
 ****************************************************************************************
 */
void smpm_send_generate_dh_key(uint8_t *operand_1, uint8_t *operand_2);
#endif // (SECURE_CONNECTIONS)

#endif // (BLE_SMPM)
#endif // (SMPM_API_H_)

/// @} SMPM_API
