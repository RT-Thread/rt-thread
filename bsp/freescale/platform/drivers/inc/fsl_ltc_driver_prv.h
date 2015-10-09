/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_LTC_DRIVER_PRV_H__
#define __FSL_LTC_DRIVER_PRV_H__

#include "fsl_ltc_hal.h"
#include "fsl_ltc_driver.h"
#if FSL_FEATURE_LTC_HAS_DES
#include "fsl_ltc_driver_des.h"
#endif
#include "fsl_ltc_driver_aes.h"
#if FSL_FEATURE_LTC_HAS_PKHA
#include "fsl_ltc_driver_pkha.h"
#include "fsl_ltc_driver_rsa.h"
#endif
#include "fsl_clock_manager.h"

/*!
 * @cond INTERNAL
 * 
 */
 
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Type used in GCM and CCM modes. 

    Content of a block is established via individual bytes and moved to LTC 
	IFIFO by moving 32-bit words. 
*/
typedef union _ltc_drv_xcm_block_t
{
    uint8_t   b[16];  /*!< 16 octets block for CCM B0 and CTR0 and for GCM */
    uint32_t  w[4];   /*!< LTC context register is 16 bytes written as four 32-bit words */
} ltc_drv_xcm_block_t;
 
/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*! @brief LTC driver lock mechanism. */
#if (LTC_DRV_RTOS_MULTI_THREAD)
    void ltc_drv_lock(uint32_t instance);
    void ltc_drv_unlock(uint32_t instance);
#else
    #define ltc_drv_lock(instance)         do {}while(0)
    #define ltc_drv_unlock(instance)       do {}while(0)
#endif

/*! @brief LTC driver wait mechanism. */
ltc_status_t ltc_drv_wait(uint32_t instance);

/*!
 * @brief Tests the correct key size.
 *
 * This function tests the correct key size.
 * @param keySize Input key length in bytes.
 * @return True if the key length is supported, false if not.
 */
static inline bool ltc_drv_check_key_size(const uint32_t keySize)
{    
    return ((keySize == 16u)
         #if FSL_FEATURE_LTC_HAS_AES192
         ||((keySize == 24u))
         #endif
         #if FSL_FEATURE_LTC_HAS_AES256
         ||((keySize == 32u))
         #endif
         ); 
}

/*!
 * @brief Tests the correct LTC module instance number.
 *
 * This function tests the LTC module instance number.
 * @param instance Input instance number to be checked.
 * @return True if the instance number is correct.
 * @return False if the instance number is NOT correct.
 */
static inline bool ltc_drv_check_instance(uint32_t instance)
{
    return (instance < FSL_FEATURE_SOC_LTC_COUNT);
}

/*!
 * @brief Checks the LTC Status register for error.
 *
 * @return kStatus_LTC_Error if error status bit is set.
 * @return kStatus_LTC_Success if there is no error in the LTC error status register.
 */
ltc_status_t ltc_drv_return_status(uint32_t instance);

/*!
 * @brief Gets the key from the LTC context.
 *
 * @param instance LTC module instance number.
 * @param key Output buffer for the key. 
 * @param keySize Input size of the key buffer.
 */
ltc_status_t ltc_drv_get_key(uint32_t instance, uint8_t *key, uint8_t keySize);

/*!
 * @brief Initializes the LTC for symmetric encrypt/decrypt operation. 
 * Mode is set to INITIALIZE/FINALIZE.
 *
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 8, 16, 24, or 32.
 * @param alg Symmetric algorithm
 * @param mode Symmetric block mode
 * @param enc Encrypt/decrypt control
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t ltc_drv_symmetric_init_final(uint32_t instance,
                                          const uint8_t *key,
                                          uint8_t keySize,
                                          ltc_hal_algorithm_t alg,
                                          ltc_hal_mode_symmetric_alg_t mode,
                                          ltc_hal_mode_encrypt_t enc);

/*!
 * @brief Initializes the LTC for symmetric encrypt/decrypt operation. Mode is set to INITIALIZE.
 *
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 8, 16, 24, or 32.
 * @param alg Symmetric algorithm
 * @param mode Symmetric block mode
 * @param enc Encrypt/decrypt control
 * @return Status from encrypt/decrypt operation
 */                                   
ltc_status_t ltc_drv_symmetric_init(uint32_t instance,
                                    const uint8_t *key,
                                    uint8_t keySize,
                                    ltc_hal_algorithm_t alg,
                                    ltc_hal_mode_symmetric_alg_t mode,
                                    ltc_hal_mode_encrypt_t enc);

/*!
 * @brief Initializes the LTC for symmetric encrypt/decrypt operation. Mode is set to FINALIZE.
 *
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 8, 16, 24, or 32.
 * @param alg Symmetric algorithm
 * @param mode Symmetric block mode
 * @param enc Encrypt/decrypt control
 * @return Status from encrypt/decrypt operation
 */                                   
ltc_status_t ltc_drv_symmetric_final(uint32_t instance,
                                     const uint8_t *key,
                                     uint8_t keySize,
                                     ltc_hal_algorithm_t alg,
                                     ltc_hal_mode_symmetric_alg_t mode,
                                     ltc_hal_mode_encrypt_t enc);
                                   
/*!
 * @brief Initializes the LTC for symmetric encrypt/decrypt operation. Mode is set to UPDATE.
 *
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 8, 16, 24, or 32.
 * @param alg Symmetric algorithm
 * @param mode Symmetric block mode
 * @param enc Encrypt/decrypt control
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t ltc_drv_symmetric_update(uint32_t instance,
                                      const uint8_t *key,
                                      uint8_t keySize,
                                      ltc_hal_algorithm_t alg,
                                      ltc_hal_mode_symmetric_alg_t mode,
                                      ltc_hal_mode_encrypt_t enc);

/*!
 * @brief Processes symmetric data through LTC AES and DES engines.
 *
 * @param instance LTC module instance number
 * @param inData Input data
 * @param inSize Size of input data, in bytes
 * @param outData Output data
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t ltc_drv_symmetric_process_data(uint32_t instance,
                                            const uint8_t *inData,
                                            uint32_t inSize,
                                            uint8_t *outData);

/*!
 * @brief Processes symmetric data through LTC AES in multiple sessions. 
 *
 * Specific for AES CCM and GCM modes as they need to update mode register.
 *
 * @param instance LTC module instance number
 * @param inData Input data
 * @param inSize Size of input data, in bytes
 * @param outData Output data 
 * @param lastAs The LTC Algorithm state to be set sup for last block during message processing in multiple sessions. 
 *               For CCM it is kLTCMode_AS_Finalize. For GCM it is kLTCMode_AS_InitFinal.
 * @return Status from encrypt/decrypt operation
 */                                          
ltc_status_t ltc_drv_symmetric_process_data_multiple(uint32_t instance,
                                                     const uint8_t *inData,
                                                     uint32_t inSize,
                                                     uint8_t *outData,
                                                     ltc_hal_mode_t mode_reg, 
                                                     ltc_hal_mode_algorithm_state_t lastAs);

/*!
 * @brief Splits the LTC job into sessions. Used for CBC, CTR, CFB, OFB cipher block modes.
 *
 * @param instance LTC module instance number
 * @param inData Input data to process.
 * @param inSize Input size of the input buffer.
 * @param outData Output data buffer.
 */
ltc_status_t ltc_drv_process_message_in_sessions(uint32_t instance,
                                                 const uint8_t *inData, 
                                                 uint32_t inSize, 
                                                 uint8_t *outData);
                                                 
/*!
 * @brief Moves the 16-byte block to LTC Input FIFO.
 *
 * This function takes one block and moves it into the LTC IFIFO in 32-bit word sized stores.
 *
 * @param instance LTC module instance number. 
 * @param blk 16-byte block with num_bytes data ready for LTC IFIFO.
 * @param num_bytes Number of bytes to be moved into the IFIFO. 
 */
void ltc_drv_move_block_to_ltc_ififo(uint32_t instance, 
                                     const ltc_drv_xcm_block_t *blk, 
                                     int num_bytes);

/*!
 * @brief Moves data to LTC Input FIFO.
 *
 * This function takes data of arbitrary size and moves it to LTC IFIFO.
 *
 * @param instance LTC module instance number. 
 * @param data Input data buffer with dataSize data ready for LTC IFIFO.
 * @param dataSize Number of bytes in the input data buffer. 
 */                                     
void ltc_drv_move_to_ififo(uint32_t instance, 
                           const uint8_t *data, 
                           uint32_t dataSize);
                    
/*!
 * @brief Receives MAC compare.
 *
 * This function is a sub-process of CCM and GCM decryption.
 * It compares received MAC with the MAC computed during decryption.
 *
 * @param instance LTC module instance number. 
 * @param tag Received MAC.
 * @param tagSize Number of bytes in the received MAC.
 * @param mode_reg LTC Mode Register current value. It is modified and written to LTC Mode Register.
 */                    
ltc_status_t ltc_drv_aes_received_mac_compare(uint32_t instance, 
                                      const uint8_t *tag, 
                                      uint32_t tagSize, 
                                      ltc_hal_mode_t mode_reg);

/*!
 * @brief Processes tag during AES GCM and CCM.
 *
 * This function is a sub-process of CCM and GCM encryption and decryption.
 * For encryption, it writes computed MAC to the output tag.
 * For decryption, it compares the received MAC with the computed MAC.
 *
 * @param instance LTC module instance number. 
 * @param[in,out] tag Output computed MAC during encryption or Input received MAC during decryption. 
 * @param tagSize Size of MAC buffer in bytes.
 * @param mode_reg LTC Mode Register current value. It is checked to read Enc/Dec bit. 
 *                 It is modified and written to LTC Mode Register during decryption.
 * @param ctx Index to LTC context registers with computed MAC for encryption process.
 */                                      
ltc_status_t  ltc_drv_aes_process_tag(uint32_t instance, 
                             uint8_t *tag, 
                             uint32_t tagSize, 
                             ltc_hal_mode_t mode_reg,
                             uint32_t ctx);
                             
#if FSL_FEATURE_LTC_HAS_PKHA
/*!
 * @brief Starts the PKHA operation.
 *
 * This function starts an operation configured by the params parameter.
 *
 * @param instance LTC peripheral instance number  
 * @param params Configuration structure containing all settings required for PKHA operation. 
 * @param[out] flags Output LTC Status register read value when the function returns kStatus_LTC_Success. NULL to skip the status register reading. 
 */
ltc_status_t ltc_drv_pkha_init_mode(uint32_t instance, 
                                    ltc_hal_pkha_mode_params_t *params);

/*!
 * @brief Clears the PKHA memory function.
 *
 * This function clears the selected PKHA memory area.
 *
 * @param instance LTC peripheral instance number  
 * @param A Boolean value True (if LTC_PKA shall be cleared) or false (LTC_PKA is left untouched). 
 * @param B Boolean value True (LTC_PKB shall be cleared) or False (LTC_PKB is left untouched). 
 * @param N Boolean value True (LTC_PKN shall be cleared) or False (LTC_PKN is left untouched). 
 * @param E Boolean value True (LTC_PKE shall be cleared) or False (LTC_PKE is left untouched). 
 * @return Operation status.
 */
ltc_status_t ltc_drv_pkha_clear_regabne(uint32_t instance,
                                        bool A, 
                                        bool B, 
                                        bool N, 
                                        bool E);

/*!
 * @brief Performs modular multiplication - (A x B) mod N.
 *
 * This function performs modular multiplication with either integer or
 * binary polynomial (F2m) inputs.  It can optionally specify whether inputs
 * and/or outputs is in Montgomery form or not.
 *
 * @param instance LTC peripheral instance number 
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param B second addend (integer or binary polynomial)
 * @param sizeB Size of B in bytes
 * @param N modulus. 
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @param montIn Format of inputs
 * @param montOut Format of output
 * @param equalTime Run the function time equalized or no timing equalization. This argument is ignored for F2m modular multiplication.
 * @return Operation status.
 */
ltc_status_t ltc_drv_pkha_modmul(uint32_t instance,
                                 const uint8_t *A,
                                 uint16_t sizeA,
                                 const uint8_t *B,
                                 uint16_t sizeB,
                                 const uint8_t *N,
                                 uint16_t sizeN,
                                 uint8_t *result,
                                 uint16_t *resultSize,
                                 ltc_hal_pkha_f2m_t arithType,
                                 ltc_hal_pkha_montgomery_form_t montIn,
                                 ltc_hal_pkha_montgomery_form_t montOut,
                                 ltc_hal_pkha_timing_t equalTime);

#endif /* FSL_FEATURE_LTC_HAS_PKHA */

/*!
 * @brief Gets the last status flag.
 
 * @param instance LTC peripheral instance number 
 * @return Operation LTC status flag.
 */
ltc_hal_status_flag_t ltc_drv_get_status_flag(uint32_t instance);

/*!
 * @brief Clears the LTC module.
 * This function can be used to clear all sensitive data from theLTC module, such as private keys. It is called internally by the LTC driver in case of an error or operation complete.
 * @param instance LTC peripheral instance number  
 * @param pkha Include LTC PKHA register clear. If there is no PKHA, the argument is ignored. 
 */
void ltc_drv_clear_all(uint32_t instance, bool pkha);

#if defined(__cplusplus)
}
#endif
/*!
 * @endcond
 * 
 */
#endif /* __FSL_LTC_DRIVER_PRV_H__ */

