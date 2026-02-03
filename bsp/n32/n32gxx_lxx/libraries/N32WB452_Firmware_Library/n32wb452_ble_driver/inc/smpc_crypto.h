/**
 ****************************************************************************************
 *
 * @file smpc_crypto.h
 *
 * @brief Header file for SMP Secure Connection Cryptographic Functions
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef SMPC_CRYPTO_H_
#define SMPC_CRYPTO_H_

#include "rwip_config.h"
#if (SECURE_CONNECTIONS)
#include "smp_common.h"

/**
 ****************************************************************************************
 * @brief Initiates the F4 crypto function
 *
 * @param[in] conidx   connection identifier
 * @param[in] U        pointer to array of bytes (see spec)
 * @param[in] V        pointer to array of bytes (see spec)
 * @param[in] X        pointer to array of bytes (see spec)
 * @param[in] Z        single byte value (see spec)
 * @return none.
 ****************************************************************************************
 */
void smpc_f4_Init(uint8_t conidx,uint8_t* U,uint8_t* V,uint8_t* X,uint8_t Z);


/**
 ****************************************************************************************
 * @brief Cleans up after the F4 crypto function, freeing any memory which had been allocated
 *
 * @param[in] conidx   connection identifier
 * @return none.
 ****************************************************************************************
 */
void smpc_f4_complete(uint8_t conidx);


/**
 ****************************************************************************************
 * @brief  Initiates the G2 crypto function
 *
 * @param[in] conidx   connection identifier
 * @param[in] U        pointer to array of bytes (see spec)
 * @param[in] V        pointer to array of bytes (see spec)
 * @param[in] X        pointer to array of bytes (see spec)
 * @param[in] Y        pointer to array of bytes (see spec)
 * @return none.
 ****************************************************************************************
 */
void smpc_g2_init(uint8_t conidx, uint8_t* U, uint8_t* V, uint8_t* X, uint8_t* Y);

/**
 ****************************************************************************************
 * @brief Cleans up after the G2 crypto function, freeing any memory which had been allocated
 *
 * @param[in] conidx   connection identifier
 * @return none.
 ****************************************************************************************
 */
void smpc_g2_complete(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief  Initiates the F5 crypto function
 *
 * @param[in] conidx   connection identifier
 * @param[in] W        pointer to the DH Key
 * @param[in] N1       pointer to 16 byte random number
 * @param[in] N2       pointer to 16 byte random number
 * @param[in] A1       pointer to array representing address of device
 * @param[in] A2       pointer to array representing address of device
 * @return none.
 ****************************************************************************************
 */
void smpc_f5_init(uint8_t conidx, uint8_t* W,uint8_t* N1,uint8_t* N2,uint8_t* A1,uint8_t* A2);

/**
 ****************************************************************************************
 * @brief Cleans up after the F5 crypto function, freeing any memory which had been allocated
 *
 * @param[in] conidx   connection identifier
 * @return none.
 ****************************************************************************************
 */
void smpc_f5_complete(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief  Initiates the F6 crypto function
 *
 * @param[in] conidx   connection identifier
 * @param[in] W        pointer to Mac Key
 * @param[in] N1       pointer to 16 byte random number
 * @param[in] N2       pointer to 16 byte random number
 * @param[in] R        pointer to array of bytes (see spec)
 * @param[in] IoCap    pointer to array representing IO capabilities of device
 * @param[in] A1       pointer to array representing address of device
 * @param[in] A2       pointer to array representing address of device
 * @return none.
 ****************************************************************************************
 */
void smpc_f6_init(uint8_t conidx,uint8_t* W, uint8_t* N1, uint8_t* N2, uint8_t* R, uint8_t* IOcap, uint8_t* A1, uint8_t* A2);

/**
 ****************************************************************************************
 * @brief Cleans up after the F6 crypto function, freeing any memory which had been allocated
 *
 * @param[in] conidx   connection identifier
 * @return none.
 ****************************************************************************************
 */
void smpc_f6_complete(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Initiates the AES CMAC crypto function. Allocate memory for the CMAC and
 *        begins the subkey generation
 *
 * @param[in] conidx   connection identifier
 * @param[in] K        pointer to the Key to be used
 * @param[in] M        pointer to the block of data the data on which the CMAC is performed
 * @param[in] M_len    length (in bytes) of the block of data M
 * @return none.
 ****************************************************************************************
 */
void smpc_aes_cmac_init(uint8_t conidx,uint8_t* K,uint8_t* M,uint8_t M_len);

/**
 ****************************************************************************************
 * @brief Continues subsequent stages of the AES CMAC crypto function
 *
 * @param[in] conidx   connection identifier
 * @param[in] aes_res  point to the result of the previous stage of the AES CMAC
 *
 * @return none.
 ****************************************************************************************
 */
void smpc_aes_cmac_continue(uint8_t conIdx,uint8_t* aes_res);

/**
 ****************************************************************************************
 * @brief The final stage of the AES CMAC crypto function
 *
 * @param[in] conidx   connection identifier
 * @param[in] aes_res  point to the result of the previous stage of the AES CMAC
 *
 * @return none.
 ****************************************************************************************
 */
void smpc_aes_cmac_complete(uint8_t conIdx,uint8_t* aes_res);

/**
 ****************************************************************************************
 * @brief Process the next stage of the AES CMAC (wrapping smpc_aes_cmac_continue(..) and
 *        smpc_aes_cmac_complete(..)
 *
 * @param[in] conidx   connection identifier
 * @param[in] aes_res  point to the result of the previous stage of the AES CMAC
 *
 * @returns boolean    Indicate if the AES CMAC is complete
 ****************************************************************************************
 */

bool smpc_process_aes_cmac(uint8_t idx,uint8_t* aes_res);
#endif // (SECURE_CONNECTIONS)


#endif /* SMPC_CRYPTO_H_ */
