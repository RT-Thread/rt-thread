/**
 ****************************************************************************************
 *
 * @file smpc_int.h
 *
 * @brief Header file - SMPC.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef SMPC_INT_H_
#define SMPC_INT_H_

/**
 ****************************************************************************************
 * @addtogroup SMP_INT Security Manager Protocol Internal
 * @ingroup HOST
 * @brief Security Manager Protocol Internals.
 * @{
 *
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_SMPC)
#include "smpc.h"

#include "smp_common.h"

#include <stdbool.h>
#include <stdint.h>

#include "co_bt.h"
#include "gap.h"

#include "smpc_api.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// Minimum Encryption key size
#define SMPC_MIN_ENC_SIZE_LEN                   (7)
/// Maximum Encryption Key size
#define SMPC_MAX_ENC_SIZE_LEN                   (16)


/// Pairing Request and Pairing Response PDU Length
#define SMPC_CODE_PAIRING_REQ_RESP_LEN          (7)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


///Security Properties for distributed keys(all have the issued STK's properties)
enum
{
    ///No security properties
    SMP_KSEC_NONE = 0x00,
    ///Unauthenticated no MITM
    SMP_KSEC_UNAUTH_NO_MITM,
    ///Authenticated with MITM
    SMP_KSEC_AUTH_MITM,
};

/// Repeated Attempts Attack Detection status
enum smpc_attempts_status
{
    /// No attack has been detected
    SMPC_REP_ATTEMPTS_NO_ERROR          = GAP_ERR_NO_ERROR,           // 0x00
    /// An attack has already been detected, drop the message
    SMPC_REP_ATTEMPTS_ATTACK,
    /// An attack has been detected, an indication has been sent to the HL
    SMPC_REP_ATTEMPS_ATTACK_DETECTED,
    /// Repeated Attempt detected, need to send a Pairing Failed PDU to the peer device
    SMPC_REP_ATTEMPT                    = SMP_ERROR_REPEATED_ATTEMPTS   // 0x09
};


/// STK generation methods
enum smpc_method
{
    ///Just Works Method
    SMPC_METH_JW            = 0x00,
    ///PassKey Entry Method
    SMPC_METH_PK,
    ////OOB Method
    SMPC_METH_OOB,
    ////Numeric Comparison
    SMPC_METH_NC
};

/// Signature Command Types
enum
{
    /// Generate Signature
    SMPC_SIGN_GEN           = 0x00,
    /// Verify Signature
    SMPC_SIGN_VERIF
};

enum
{
    /// Use of STK in start encryption command
    SMPC_USE_STK     = 0x00,
    /// Use of LTK in start encryption command
    SMPC_USE_LTK
};

#if (SECURE_CONNECTIONS)
enum
{
    SMP_AES_CMAC_KEY_GENERATION = 0x00,

    SMP_AES_CMAC_BLOCK
};

/// Keypress Notification types
enum smpc_notification_type
{
    /// Passkey entry started
    SMP_PASSKEY_ENTRY_STARTED = 0x00,
    /// Passkey digit entered
    SMP_PASSKEY_DIGIT_ENTERED,
    /// Passkey digit erased
    SMP_PASSKEY_DIGIT_ERASED,
    /// Passkey cleared
    SMP_PASSKEY_CLEARED,
    /// Passkey entry completed
    SMP_PASSKEY_ENTRY_COMPLETED
};
#endif // (SECURE_CONNECTIONS)
/*
 * STRUCTURES DEFINITION
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLES DEFINITION
 ****************************************************************************************
 */


/*
 * MACROS
 ****************************************************************************************
 */
/// Authentication Request mask
#define SMPC_MASK_AUTH_REQ(req)    (req & 0x07)

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Send a SMPM_USE_ENC_BLOCK_CMD message to the SMPM. Shall be use when the AES_128
 *        encryption block need to be used.
 *
 * @param[in] conidx      Connection Index
 * @param[in] operand_1   First operand
 * @param[in] operand_2   Second operand
 ****************************************************************************************
 */
void smpc_send_use_enc_block_cmd(uint8_t conidx,
                                 uint8_t *operand_1, uint8_t *operand_2);


/**
 ****************************************************************************************
 * @brief Send a SMPM_GEN_DH_KEY_CMD message to the SMPM. Shall be use when we need to
 *        generate a DH KEy
 *
 * @param[in] conidx      Connection Index
 * @param[in] operand_1   X co-ordinate
 * @param[in] operand_2   Y co-ordinate
 ****************************************************************************************
 */

void smpc_send_gen_dh_key_cmd(uint8_t conidx,
                                uint8_t *operand_1, uint8_t *operand_2);

/**
 ****************************************************************************************
 * @brief Send a request to the controller to start the encryption procedure.
 *
 * @param[in] conidx      Connection Index
 * @param[in] operand_1   First operand
 * @param[in] operand_2   Second operand
 ****************************************************************************************
 */
void smpc_send_start_enc_cmd(uint8_t idx, uint8_t key_type, uint8_t *key,
                             uint8_t *randnb, uint16_t ediv);

/**
 ****************************************************************************************
 * @brief Send the LTK provided by the HL to the controller.
 *
 * @param[in] idx         Connection Index
 * @param[in] found       Indicate if the requested LTK has been found by the application
 * @param[in] key         Found LTK, used only if found is set to true
 ****************************************************************************************
 */
void smpc_send_ltk_req_rsp(uint8_t idx, bool found, uint8_t *key);

/**
 ****************************************************************************************
 * @brief Send a SMPC_PAIRING_REQ_IND message to the HL
 *
 * @param[in] conidx      Connection Index
 * @param[in] req_type    Kind of request
 ****************************************************************************************
 */
void smpc_send_pairing_req_ind(uint8_t conidx, uint8_t req_type);

/**
 ****************************************************************************************
 * @brief Send a SMPC_PAIRING_IND message to the HL
 *
 * @param[in] conidx      Connection Index
 * @param[in] ind_type    Kind of indication
 * @param[in] value       Value to indicate (keys, ...)
 ****************************************************************************************
 */
void smpc_send_pairing_ind(uint8_t conidx, uint8_t ind_type, void *value);

/**
 ****************************************************************************************
 * @brief Check if the provided pairing features are within the specified range.
 *
 * @param[in] pair_feat   Pairing Features values to check
 *
 * @param[out] true if features are valid, else false
 ****************************************************************************************
 */
bool smpc_check_pairing_feat(struct gapc_pairing *pair_feat);

/**
 ****************************************************************************************
 * @brief Check if an attack by repeated attempts has been triggered by the peer device
 *
 * @param[in] conidx   Connection Index
 ****************************************************************************************
 */
uint8_t smpc_check_repeated_attempts(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Compute and check the encryption key size to use during the connection.
 *
 * @param[in] conidx   Connection Index
 *
 * @param[out] true if the resultant EKS is within the specified range [7-16 bytes], else false
 ****************************************************************************************
 */
bool smpc_check_max_key_size(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Check if the keys distribution scheme is compliant with the required security
 *        level
 *
 * @param[in] conidx      Connection Index
 * @param[in] sec_level   Security level required by the device.
 ****************************************************************************************
 */
bool smpc_check_key_distrib(uint8_t conidx, uint8_t sec_level);

/**
 ****************************************************************************************
 * @brief Apply the XOR operator to the two provided operands
 *
 * @param[in|out] result      Buffer which will contain the result of the XOR operation
 * @param[in]     operand_1   First operand
 * @param[in]     operand_2   Second operand
 ****************************************************************************************
 */
void smpc_xor(uint8_t *result, uint8_t *operand_1, uint8_t *operand_2);

/**
 ****************************************************************************************
 * @brief Generate the L value during a signature verification/generation procedure.
 *
 * @param[in] conidx   Connection Index
 * @param[in] src      Indicate the source of the CSRK which will be used (LOCAL or PEER)
 ****************************************************************************************
 */
void smpc_generate_l(uint8_t conidx, uint8_t src);

/**
 ****************************************************************************************
 * @brief Generate one of the Ci value during a signature verification/generation procedure.
 *
 * @param[in] conidx   Connection Index
 * @param[in] src      Indicate the source of the CSRK which will be used (LOCAL or PEER)
 * @param[in] ci1      Previous computed Ci value
 * @param[in] mi       16-byte block used to generate the ci value
 ****************************************************************************************
 */
void smpc_generate_ci(uint8_t conidx, uint8_t src, uint8_t *ci1, uint8_t *mi);

/**
 ****************************************************************************************
 * @brief Generate the random value exchanged during the pairing procedure (phase 2)
 *
 * @param[in] conidx   Connection Index
 * @param[in] state    New state of the SMPC task.
 ****************************************************************************************
 */
void smpc_generate_rand(uint8_t conidx, uint8_t state);

/**
 ****************************************************************************************
 * @brief Generate the first value needed in the confirm value generation
 *
 * @param[in] conidx   Connection Index
 * @param[in] role     Current role of the device
 * @param[in] local    true if the confirm value to generate is the confirm value of the
 *                     device, false if it is the remote device's one.
 ****************************************************************************************
 */
void smpc_generate_e1(uint8_t conidx, uint8_t role, bool local);

/**
 ****************************************************************************************
 * @brief Generate the confirm value
 *
 * @param[in] conidx   Connection Index
 * @param[in] role     Current role of the device
 * @param[in] e1       e1 value
 ****************************************************************************************
 */
void smpc_generate_cfm(uint8_t conidx, uint8_t role, uint8_t *e1);

/**
 ****************************************************************************************
 * @brief Generate the STK used to encrypt a link after the pairing procedure
 *
 * @param[in] conidx   Connection Index
 * @param[in] role     Current role of the device
 ****************************************************************************************
 */
void smpc_generate_stk(uint8_t conidx, uint8_t role);

/**
 ****************************************************************************************
 * @brief Calculate one of the subkey used during the signature generation/verification
 *        procedure.
 *
 * @param[in] gen_k2        true if the returned subkeys is k2, false if k1
 * @param[in] l_value       L value obtained from the CSRK.
 * @param[in|out] subkey    Buffer which will contain the generated subkey.
 ****************************************************************************************
 */
void smpc_calc_subkeys(bool gen_k2, uint8_t *l_value, uint8_t *subkey);

/**
 ****************************************************************************************
 * @brief Start to send the keys defined during the pairing features exchange procedure.
 *
 * @param[in] conidx        Connection Index
 * @param[in] role          Current role of the device
 ****************************************************************************************
 */
void smpc_tkdp_send_start(uint8_t conidx, uint8_t role);

/**
 ****************************************************************************************
 * @brief Define the next step of TKDP procedure (sending side).
 *
 * @param[in] conidx        Connection Index
 * @param[in] role          Current role of the device
 ****************************************************************************************
 */
void smpc_tkdp_send_continue(uint8_t conidx, uint8_t role);

/**
 ****************************************************************************************
 * @brief Put the task in a state allowing to receive the keys defined during the pairing
 *        features exchange procedure.
 *
 * @param[in] conidx        Connection Index
 * @param[in] role          Current role of the device
 ****************************************************************************************
 */
void smpc_tkdp_rcp_start(uint8_t conidx, uint8_t role);

/**
 ****************************************************************************************
 * @brief Define the next step of TKDP procedure (reception side).
 *
 * @param[in] conidx        Connection Index
 * @param[in] role          Current role of the device
 ****************************************************************************************
 */
void smpc_tkdp_rcp_continue(uint8_t conidx, uint8_t role);


/**
 ****************************************************************************************
 * @brief Start the timer used to detect a Repeated Attempts attack
 *
 * @param[in] conidx        Connection Index
 ****************************************************************************************
 */
void smpc_launch_rep_att_timer(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Determine the method which will be used to generate the STK during a pairing
 *        procedure
 *
 * @param[in] conidx        Connection Index
 ****************************************************************************************
 */
void smpc_get_key_sec_prop(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Check if the security mode requested by the application or the peer device can
 *        be reached with the exchanged pairing features.
 *
 * @param[in] conidx        Connection Index
 * @param[in] role          Current role of the device
 ****************************************************************************************
 */
bool smpc_is_sec_mode_reached(uint8_t conidx, uint8_t role);

/**
 ****************************************************************************************
 * @brief Define what to do once a start encryption procedure has been successfully finished.
 *
 * @param[in] conidx        Connection Index
 * @param[in] role          Current role of the device
 * @param[in] status        Status
 ****************************************************************************************
 */
void smpc_handle_enc_change_evt(uint8_t conidx, uint8_t role, uint8_t status);


#if (SECURE_CONNECTIONS)
/**
 ****************************************************************************************
 * @brief Initiate DHKey Check algorithm
 *
 * @param[in] conidx        Connection Index
 ****************************************************************************************
 */
void smpc_initiate_dhkey_check(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Initiates the f5 algorithm to calculate the MacKey and LTK for a link
 *
 * @param[in] conidx        Connection Index
 *
 ****************************************************************************************
 */

void smpc_init_mac_key_calculation(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Initiates the f6 algorithm to verify a DH Key Check.
 *
 * @param[in] conidx        Connection Index
 *
 ****************************************************************************************
 */

void smpc_initiate_dhkey_verification(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Determines the next bit of the passkey to be used
 *
 * @param[in] conidx        Connection Index
 *
 ****************************************************************************************
 */
uint8_t smpc_get_next_passkey_bit(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Checks if secure connections are enabled on a link
 *
 * @param[in] conidx        Connection Index
 *
 ****************************************************************************************
 */
bool smpc_secure_connections_enabled(uint8_t idx);

#endif // (SECURE_CONNECTIONS)
#endif //(BLE_SMPC)
#endif //SMPC_INT_H_

/// @} SMPC
