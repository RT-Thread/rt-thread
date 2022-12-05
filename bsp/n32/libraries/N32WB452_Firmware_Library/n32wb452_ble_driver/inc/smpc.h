/**
 ****************************************************************************************
 *
 * @file smpc.h
 *
 * @brief Header file - SMPC.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef SMPC_H_
#define SMPC_H_

/**
 ****************************************************************************************
 * @addtogroup SMP Security Manager Protocol
 * @ingroup HOST
 * @brief Security Manager Protocol.
 *
 * The SMP is responsible for the over-all security policies of BLE.
 * It defines methods for pairing and key distribution, handles encryption,
 * data signing and privacy features such as random addressing generation and resolution.
 *
 * Pairing is performed to exchange pairing features and generate a short term
 * key for link encryption.
 * A transport specific key distribution is performed to
 * share the keys that can be used to encrypt the link in the future
 * reconnection process, signed data verification and random address
 * resolution.
 *
 * There exist 3 phases in the complete security procedure:
 * 1. Feature exchange (IO capabilities, OOB flags, Authentication Requirements, Key distributions)
 * 2. Short Term Key generation
 *    Generation method depends on exchanged features:
 *     - Just Works - use Temporary key = 0
 *     - PassKey Entry - use Temporary Key = 6-digit provided by user
 *     - Out of Band (OOB) - use Temporary Key = 16-octet key, available form OOB source
 * 3. Transport Specific Key Distribution (TKDP)(LTK+EDIV+RAND_NB, IRK+ADDR, CSRK)
 *---------------------------------------------------------------------
 * @addtogroup SMPC Security Manager Protocol Controller
 * @ingroup SMP
 * @brief Security Manager Protocol Controller.
 *
 * This block handles control of SM procedures for several possible existing connections,
 * for which the security procedure may be conducted simultaneously.
 *
 * It allows flow control for HCI access to encryption and random number generation, used
 * at different moments in the procedure.
 *
 * It handles PDU creation and sending through L2CAP, also their reception from L2CAP
 * and interpretation.
 *
 * Other small utilities such as maximum key size determination and TKDP organization are
 * implemented in SMPC.
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
#include "co_bt.h"
#include "gap.h"
#include "gapc_task.h"
#include "ke_task.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// MAC length
#define SMPC_SIGN_MAC_LEN                       (8)
/// SignCounter length
#define SMPC_SIGN_COUNTER_LEN                   (4)
/// Signature length
#define SMPC_SIGN_LEN                           (SMPC_SIGN_MAC_LEN + SMPC_SIGN_COUNTER_LEN)

/**
 * Repeated Attempts Timer Configuration
 */
/// Repeated Attempts Timer default value (x10ms)
#define SMPC_REP_ATTEMPTS_TIMER_DEF_VAL         (200)      //2s
/// Repeated Attempts Timer max value (x10ms)
#define SMPC_REP_ATTEMPTS_TIMER_MAX_VAL         (3000)     //30s
/// Repeated Attempts Timer multiplier
#define SMPC_REP_ATTEMPTS_TIMER_MULT            (2)

/**
 * Timeout Timer Configuration
 */
#define SMPC_TIMEOUT_TIMER_DURATION             (1000)     //30s

#define SMPC_PUBLIC_KEY_256_COORD_LEN            0x20
/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/// Information source.
enum smpc_addr_src
{
    /// Local info.
    SMPC_INFO_LOCAL,
    /// Peer info.
    SMPC_INFO_PEER,
    /// Maximum info source.
    SMPC_INFO_MAX
};

/*
 * STRUCTURES DEFINITION
 ****************************************************************************************
 */

/// Master ID Information Structure
struct smpc_mst_id_info
{
    // Encryption Diversifier
    uint16_t ediv;

    // Random Number
    uint8_t randnb[GAP_RAND_NB_LEN];
};

#if (SECURE_CONNECTIONS)
struct smp_aes_cmac
{
    uint8_t* M; // pointer to memory allocated by calling function
    uint8_t  M_len;
    uint8_t  M_last[16];
    uint8_t  X[16];
    uint8_t  Y[16];
    uint8_t*  K; //[16];
    uint8_t  K1[16];
    uint8_t  K2[16];
    uint8_t  next_block;
    uint8_t  num_blocks;
    uint8_t  state;  // Only 3 States - Idle, SubKey Generation, Block AES
};

struct smp_f4
{
    uint8_t M[65];
    uint8_t X[16]; // The Key
};

struct smp_f5
{
    uint8_t M[53];
    uint8_t* W;
    uint8_t T[16];
    uint8_t SALT[16];
};


struct smp_f6
{
    uint8_t W[16];
    uint8_t M[65];
};

struct smp_g2
{
    uint8_t X[16];
    uint8_t M[80];
};

struct gapc_public_key
{
    uint8_t x[GAP_P256_KEY_LEN];
    uint8_t y[GAP_P256_KEY_LEN];
};

#endif // (SECURE_CONNECTIONS)
/// Pairing Information
struct smpc_pair_info
{
    /// TK during Phase 2, LTK or IRK during Phase 3
    struct gap_sec_key key;
    /// Pairing request command
    struct gapc_pairing pair_req_feat;
    /// Pairing response feature
    struct gapc_pairing pair_rsp_feat;
    /// Random number value
    uint8_t rand[RAND_VAL_LEN];
    /// Remote random number value
    uint8_t rem_rand[RAND_VAL_LEN];
    /// Confirm value to check
    uint8_t conf_value[GAP_KEY_LEN];
    /// Pairing Method
    uint8_t pair_method;
    /// Authentication level
    uint8_t auth;
    /// check that LTK exchanged during pairing
    bool ltk_exchanged;
    /// Key to be exchanged (transmitted or to be received)
    uint8_t keys_dist;


    #if (SECURE_CONNECTIONS)
    // AES_CMAC Info
    struct smp_aes_cmac* aes_cmac;
    // Structure for Secure Connections Crypto functions
    struct smp_f4*  f4_info;
    struct smp_f5*  f5_info;
    struct smp_f6*  f6_info;
    struct smp_g2*  g2_info;

    bool dh_key_calculation_complete;

    uint8_t MacKey[GAP_KEY_LEN];
    uint8_t dh_key_check_peer[DHKEY_CHECK_LEN];
    uint8_t dh_key_local[DH_KEY_LEN];

    uint8_t dh_key_check_local[DHKEY_CHECK_LEN];
    bool dh_key_check_received_from_peer;

    public_key_t peer_public_key;

    uint8_t passkey_bit_count;
    uint32_t passkey;

    // Required for OOB
    uint8_t peer_r[GAP_KEY_LEN];
    uint8_t local_r[GAP_KEY_LEN];
    bool peer_rand_received;
    bool peer_confirm_received;
    #endif // (SECURE_CONNECTIONS)
};

/// Signing Information
struct smpc_sign_info
{
    /// Operation requester task id
    ke_task_id_t requester;

    /// Message offset
    uint16_t msg_offset;
    /// Number of block
    uint8_t block_nb;
    /// Cn-1 value -> Need to kept this value to retrieve it after L generation
    uint8_t cn1[GAP_KEY_LEN];
};

/// SMPC environment structure
struct smpc_env
{
    /// SMPC temporary information
    union smpc_info
    {
        /**
         * Pairing Information - This structure is allocated at the beginning of a pairing
         * or procedure. It is freed when a disconnection occurs or at the end of
         * the pairing procedure. If not enough memory can be found, the procedure will fail
         *  with an "Unspecified Reason" error
         */
        struct smpc_pair_info *pair;

        /**
         * Signature Procedure Information - This structure is allocated at the beginning of a
         * signing procedure. It is freed when a disconnection occurs or at the end of
         * the signing procedure. If not enough memory can be found, the procedure will fail
         *  with an "Unspecified Reason" error.
         */
        struct smpc_sign_info *sign;
    } info;

    /// CSRK values (Local and remote)
    struct gap_sec_key csrk[SMPC_INFO_MAX];

    /// signature counter values (Local and remote)
    uint32_t sign_counter[SMPC_INFO_MAX];

    /// Repeated Attempt Timer value
    uint16_t rep_att_timer_val;

    /// Encryption key size
    uint8_t key_size;

    /**
     * Contains the current state of the two timers needed in the SMPC task
     *      Bit 0 - Is Timeout Timer running
     *      Bit 1 - Is Repeated Attempt Timer running
     *      Bit 2 - Has task reached a SMP Timeout
     */
    uint8_t timer_state;

    /// State of the current procedure
    uint8_t state;

    #if (SECURE_CONNECTIONS)
    bool secure_connections_enabled;
    #endif // (SECURE_CONNECTIONS)
};

/*
 * GLOBAL VARIABLES DEFINITION
 ****************************************************************************************
 */


/*
 * MACROS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


#endif //(BLE_SMPC)
#endif //SMPC_H_

/// @} SMPC
