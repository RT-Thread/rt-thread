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

#ifndef __FSL_LTC_HAL_H__
#define __FSL_LTC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_LTC_COUNT

/*!
 * @addtogroup ltc_hal
 * @{
 */
 
 typedef enum _ltc_status_err_shift_t {
     kStatus_LTC_ErrShift = 4, /*!< Number of left shift bits for ltc_status_t General Error OR'ed with LTC Error Status Register ERRID1 value */
 } ltc_status_err_shift_t;

/*! @brief Error codes for LTC HAL and PD. */
typedef enum _ltc_status_t {
    kStatus_LTC_Success                 = 0U,
    kStatus_LTC_InvalidInput            = 0x00000001U,
    kStatus_LTC_InvalidKeyLength        = 0x00000002U,
    kStatus_LTC_InvalidDataLength       = 0x00000003U,
    kStatus_LTC_InvalidICVLength        = 0x00000004U,
    kStatus_LTC_Error                   = 0x00000005U, /*!< General Error. */
    kStatus_LTC_ModeError               = 0x00000015U, /*!< Error Status Register: Mode Error. */
    kStatus_LTC_DataSizeError           = 0x00000025U, /*!< Error Status Register: Data Size Error, including PKHA N Register Size Error */
    kStatus_LTC_KeySizeError            = 0x00000035U, /*!< Error Status Register: Key Size Error, including PKHA E Register Size Error */
    kStatus_LTC_PKHA_RegASzError        = 0x00000045U, /*!< Error Status Register: PKHA A Register Size Error */
    kStatus_LTC_PKHA_RegBSzError        = 0x00000055U, /*!< Error Status Register: PKHA B Register Size Error */
    kStatus_LTC_DataOutOfSeqError       = 0x00000065U, /*!< Error Status Register: Data Arrived Out of Sequence Error */
    kStatus_LTC_PKHA_DivByZeroError     = 0x00000075U, /*!< Error Status Register: PKHA Divide By Zero Error */
    kStatus_LTC_PKHA_ModulusEvenError   = 0x00000085U, /*!< Error Status Register: PKHA Modulus Even Error */
    kStatus_LTC_DES_KeyParityError      = 0x00000095U, /*!< Error Status Register: DES Key Parity Error */
    kStatus_LTC_ICV_CheckFailed         = 0x000000A5U, /*!< Error Status Register: ICV Check Failed (Received MAC compare failed) */
    kStatus_LTC_InternalHwFailure       = 0x000000B5U, /*!< Error Status Register: Internal Hardware Failure */
    kStatus_LTC_CCM_AadSzError          = 0x000000C5U, /*!< Error Status Register: CCM AAD Size Error */
    kStatus_LTC_CCM_InvalidCryptoSel    = 0x000000F5U, /*!< Error Status Register: Invalid Crypto Engine Selected */
    kStatus_LTC_OSAError                = 0x00000006U, /*!< OSA initialisation failed. */
} ltc_status_t;

/*! Full word representing the actual bit values for the LTC mode register. */
typedef uint32_t ltc_hal_mode_t;

/*! @brief LTC algorithm mode. */
typedef enum _ltc_hal_algorithm_t {
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCAlgorithm_PKHA       = LTC_MDPK_ALG_PKHA << LTC_MDPK_ALG_SHIFT,
    #endif /* FSL_FEATURE_LTC_HAS_PKHA */
    kLTCAlgorithm_AES        = LTC_MD_ALG_AES << LTC_MD_ALG_SHIFT,
    #if FSL_FEATURE_LTC_HAS_DES
    kLTCAlgorithm_DES        = LTC_MD_ALG_DES << LTC_MD_ALG_SHIFT,
    kLTCAlgorithm_3DES       = LTC_MD_ALG_TRIPLE_DES << LTC_MD_ALG_SHIFT
    #endif /* FSL_FEATURE_LTC_HAS_DES */
} ltc_hal_algorithm_t;

/*! @brief Register areas for PKHA clear memory operations. */
typedef enum _ltc_hal_pkha_reg_area {
    kLTC_PKHA_REG_A     = 8U,
    kLTC_PKHA_REG_B     = 4U,
    kLTC_PKHA_REG_E     = 2U,
    kLTC_PKHA_REG_N     = 1U,
    kLTC_PKHA_REG_All = kLTC_PKHA_REG_A | kLTC_PKHA_REG_B | kLTC_PKHA_REG_E | kLTC_PKHA_REG_N,
} ltc_hal_pkha_reg_area_t;

/*! @brief Quadrant areas for 2048-bit registers for PKHA clear memory
 * operations. */
typedef enum _ltc_hal_pkha_clr_quad_area_t {
    kLTC_PKHA_CLR_QUAD_0    = 1U,
    kLTC_PKHA_CLR_QUAD_1    = 2U,
    kLTC_PKHA_CLR_QUAD_2    = 4U,
    kLTC_PKHA_CLR_QUAD_3    = 8U,
    kLTC_PKHA_CLR_QUAD_0_1_3  = kLTC_PKHA_CLR_QUAD_0 | kLTC_PKHA_CLR_QUAD_1 | kLTC_PKHA_CLR_QUAD_3,
    kLTC_PKHA_CLR_QUAD_0_1_2  = kLTC_PKHA_CLR_QUAD_0 | kLTC_PKHA_CLR_QUAD_1 | kLTC_PKHA_CLR_QUAD_2,
    kLTC_PKHA_CLR_QUAD_All  = kLTC_PKHA_CLR_QUAD_0_1_2 | kLTC_PKHA_CLR_QUAD_3,
} ltc_hal_pkha_clr_quad_area_t;

/*! @brief Quadrant areas for 2048-bit registers for PKHA copy memory
 * operations. */
typedef enum _ltc_hal_pkha_quad_area_t {
    kLTC_PKHA_QUAD_0    = 0U,
    kLTC_PKHA_QUAD_1    = 1U,
    kLTC_PKHA_QUAD_2    = 2U,
    kLTC_PKHA_QUAD_3    = 3U,
} ltc_hal_pkha_quad_area_t;

/*! @brief Montgomery or normal PKHA input format. */
typedef enum _ltc_hal_pkha_montgomery_form_t {
    kLTC_PKHA_NormalValue         = 0U,
    kLTC_PKHA_MontgomeryFormat    = 1U
} ltc_hal_pkha_montgomery_form_t;

/*! @brief Integer vs binary polynomial arithmetic selection. */
typedef enum _ltc_hal_pkha_f2m_t {
    kLTC_PKHA_Integer_Arith       = 0U,     /*!< Use integer arithmetic */
    kLTC_PKHA_F2M_Arith           = 1U      /*!< Use binary polynomial arithmetic */
} ltc_hal_pkha_f2m_t;

/*! @brief User-supplied (R^2 mod N) input or LTC should calculate. */
typedef enum _ltc_hal_pkha_r2_t {
    kLTC_PKHA_R2_Calc            = 0U,      /*!< Calculate (R^2 mod N) */
    kLTC_PKHA_R2_Input           = 1U       /*!< (R^2 mod N) supplied as input */
} ltc_hal_pkha_r2_t;

/*! @brief Use of timing equalized version of a PKHA function. */
typedef enum _ltc_hal_pkha_timing_t {
    kLTC_PKHA_NoTimingEqualized  = 0U,
    kLTC_PKHA_TimingEqualized    = 1U
} ltc_hal_pkha_timing_t;

/*! @brief Select PKHA output destination register. */
typedef enum _ltc_hal_pkha_output_reg_t {
    kLTC_PKHA_Output_B           = 0U,
    kLTC_PKHA_Output_A           = 1U
} ltc_hal_pkha_output_reg_t;

/*! @brief PKHA functions - arithmetic, copy/clear memory. */
typedef enum _ltc_hal_pkha_func_t {
    kLTC_PKHA_ClearMem                 = 1U,
    kLTC_PKHA_Arith_ModAdd             = 2U,    /*!< (A + B) mod N */
    kLTC_PKHA_Arith_ModSub1            = 3U,    /*!< (A - B) mod N */
    kLTC_PKHA_Arith_ModSub2            = 4U,    /*!< (B - A) mod N */
    kLTC_PKHA_Arith_ModMul             = 5U,    /*!< (A x B) mod N */
    kLTC_PKHA_Arith_ModExp             = 6U,    /*!< (A^E) mod N */
    kLTC_PKHA_Arith_ModRed             = 7U,    /*!< (A) mod N */
    kLTC_PKHA_Arith_ModInv             = 8U,    /*!< (A^-1) mod N */
    kLTC_PKHA_Arith_ECCAdd             = 9U,    /*!< (P1 + P2) */
    kLTC_PKHA_Arith_ECCDouble          = 10U,   /*!< (P2 + P2) */
    kLTC_PKHA_Arith_ECCMul             = 11U,   /*!< (E x P1) */
    kLTC_PKHA_Arith_ModR2              = 12U,   /*!< (R^2 mod N) */
    kLTC_PKHA_Arith_GCD                = 14U,   /*!< GCD (A, N) */
    kLTC_PKHA_Arith_PrimalityTest      = 15U,   /*!< Miller-Rabin */
    kLTC_PKHA_CopyMem_N_Size           = 16U,
    kLTC_PKHA_CopyMem_SRC_Size         = 17U
} ltc_hal_pkha_func_t;

/*! @brief LTC encrypt/decrypt mode for symmetric key operations. */
typedef enum _ltc_hal_mode_encrypt_t {
    kLTCMode_Decrypt   = LTC_MD_ENC_DECRYPT << LTC_MD_ENC_SHIFT,
    kLTCMode_Encrypt   = LTC_MD_ENC_ENCRYPT << LTC_MD_ENC_SHIFT
} ltc_hal_mode_encrypt_t;

/*! @brief LTC ICV check enable/disable. */
typedef enum _ltc_hal_mode_icv_check_t {
    kLTCMode_ICV_NoCompare   = 0U << LTC_MD_ICV_TEST_SHIFT,
    kLTCMode_ICV_Compare     = 1U << LTC_MD_ICV_TEST_SHIFT
} ltc_hal_mode_icv_check_t;

/*! @brief LTC algorithm state. */
typedef enum _ltc_hal_mode_algorithm_state_t {
    kLTCMode_AS_Update       = LTC_MD_AS_UPDATE << LTC_MD_AS_SHIFT,
    kLTCMode_AS_Init         = LTC_MD_AS_INITIALIZE << LTC_MD_AS_SHIFT,
    kLTCMode_AS_Finalize     = LTC_MD_AS_FINALIZE << LTC_MD_AS_SHIFT,
    /* TODO: incorrect name in reg definitions. */
    kLTCMode_AS_InitFinal    = 3U << LTC_MD_AS_SHIFT   
} ltc_hal_mode_algorithm_state_t;

/*! @brief LTC symmetric key encryption/decryption operating mode. */
typedef enum _ltc_hal_mode_symmetric_alg_t {
    kLTCMode_CTR       = 0x00U << LTC_MD_AAI_SHIFT,
    kLTCMode_CBC       = 0x10U << LTC_MD_AAI_SHIFT,
    kLTCMode_ECB       = 0x20U << LTC_MD_AAI_SHIFT,
    kLTCMode_CFB       = 0x30U << LTC_MD_AAI_SHIFT,
    kLTCMode_OFB       = 0x40U << LTC_MD_AAI_SHIFT,
    kLTCMode_CMAC      = 0x60U << LTC_MD_AAI_SHIFT,
    kLTCMode_XCBC_MAC  = 0x70U << LTC_MD_AAI_SHIFT,
    kLTCMode_CCM       = 0x80U << LTC_MD_AAI_SHIFT,
    kLTCMode_GCM       = 0x90U << LTC_MD_AAI_SHIFT,
    kLTCMode_CBC_MAC   = 0xA0U << LTC_MD_AAI_SHIFT,
    kLTCMode_CTR_MAC   = 0xB0U << LTC_MD_AAI_SHIFT
} ltc_hal_mode_symmetric_alg_t;

/*! @brief LTC ModeR Register AAI field DK bit */
typedef enum _ltc_hal_mode_decrypt_key_t {
    kLTCMode_DK = 0x100U,
} ltc_hal_mode_decrypt_key_t;

/*! @brief LTC reset command. */
typedef enum _ltc_hal_cmd_t {
    kLTCCmd_ResetAll   = 1U << LTC_COM_ALL_SHIFT,   /*!< Reset all internal logic */
    kLTCCmd_ResetAES   = 1U << LTC_COM_AES_SHIFT,   /*!< Reset AES core */
    #if FSL_FEATURE_LTC_HAS_DES
    kLTCCmd_ResetDES   = 1U << LTC_COM_DES_SHIFT,   /*!< Reset DES core */
    #endif /* FSL_FEATURE_LTC_HAS_DES */
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCCmd_ResetPKHA  = 1U << LTC_COM_PK_SHIFT     /*!< Reset PKHA core */
    #endif /* FSL_FEATURE_LTC_HAS_PKHA */
} ltc_hal_cmd_t;

/*! @brief LTC key register read access */
typedef enum _ltc_hal_key_lock_t {
    kLTCCtrl_KeyRegisterReadable = 0U,      /*!< Key register readable */
    kLTCCtrl_KeyRegisterNotReadable = 1U    /*!< Key register not readable */
} ltc_hal_key_lock_t;

/*! @brief LTC byte swap */
typedef enum _ltc_hal_byte_swap_t {
    kLTCCtrl_ByteNoSwap = 0U,               /*!< Don't swap bytes on read/write */
    kLTCCtrl_ByteSwap= 1U                   /*!< Swap bytes on read/write */
} ltc_hal_byte_swap_t;

/*! @brief LTC FIFO DMA request size */
typedef enum _ltc_hal_fifo_dma_size_t {
    kLTCCtrl_DMASize_1byte = 0U,            /*!< DMA request FIFO 1 entry */
    kLTCCtrl_DMASize_4byte = 1U             /*!< DMA request FIFO 4 entries */
} ltc_hal_fifo_dma_size_t;

/*! @brief LTC DMA module enable */
typedef enum _ltc_hal_dma_enable_t {
    kLTCCtrl_DMA_Disabled = 0U,             /*!< DMA disable */
    kLTCCtrl_DMA_Enabled = 1U               /*!< DMA enabled */
} ltc_hal_dma_enable_t;

/*! @brief LTC Interrupt mask */
typedef enum _ltc_hal_isr_mask_t {
    kLTCCtrl_ISR_Not_Masked = 0U,           /*!< Interrupt not masked */
    kLTCCtrl_ISR_Masked = 1U                /*!< Interrupt masked */
} ltc_hal_isr_mask_t;

/*! @brief LTC clear register */
typedef enum _ltc_hal_clear_written_t {
    kLTCClear_Mode          = 1U << LTC_CW_CM_SHIFT,
    kLTCClear_DataSize      = 1U << LTC_CW_CDS_SHIFT,
    kLTCClear_ICVSize       = 1U << LTC_CW_CICV_SHIFT,
    kLTCClear_Context       = 1U << LTC_CW_CCR_SHIFT,
    kLTCClear_Key           = 1U << LTC_CW_CKR_SHIFT,
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCClear_PKHA_Size_A   = 1U << LTC_CW_CPKA_SHIFT,
    kLTCClear_PKHA_Size_B   = 1U << LTC_CW_CPKB_SHIFT,
    kLTCClear_PKHA_Size_N   = 1U << LTC_CW_CPKN_SHIFT,
    kLTCCLear_PKHA_Size_E   = 1U << LTC_CW_CPKE_SHIFT,
    kLTCClear_All_Size      = (int) kLTCClear_PKHA_Size_A |
                                    kLTCClear_PKHA_Size_B |
                                    kLTCClear_PKHA_Size_N |
                                    kLTCCLear_PKHA_Size_E,
    #endif /* FSL_FEATURE_LTC_HAS_PKHA */
    kLTCClear_OutputFIFO    = 1U << LTC_CW_COF_SHIFT,
    kLTCClear_InputFIFO     = (int)(1U << LTC_CW_CIF_SHIFT),
    kLTCClear_All           = (int)(LTC_CW_CM_MASK |
                              LTC_CW_CDS_MASK |
                              LTC_CW_CICV_MASK |
                              LTC_CW_CCR_MASK |
                              LTC_CW_CKR_MASK |
                              #if FSL_FEATURE_LTC_HAS_PKHA
                              LTC_CW_CPKA_MASK |
                              LTC_CW_CPKB_MASK |
                              LTC_CW_CPKN_MASK |
                              LTC_CW_CPKE_MASK |
                              #endif /* FSL_FEATURE_LTC_HAS_PKHA */
                              LTC_CW_COF_MASK |
                              LTC_CW_CIF_MASK)
} ltc_hal_clear_written_t;

/*! @brief LTC status flags */
typedef enum _ltc_hal_status_flag_t {
    kLTCStatus_AES_Busy             = 1U << LTC_STA_AB_SHIFT,
    #if FSL_FEATURE_LTC_HAS_DES
    kLTCStatus_DES_Busy             = 1U << LTC_STA_DB_SHIFT,
    #endif /* FSL_FEATURE_LTC_HAS_DES */
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCStatus_PKHA_Busy            = 1U << LTC_STA_PB_SHIFT,
    #endif /* FSL_FEATURE_LTC_HAS_PKHA */
    kLTCStatus_Done_ISR             = 1U << LTC_STA_DI_SHIFT,
    kLTCStatus_Error_ISR            = 1U << LTC_STA_EI_SHIFT,
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCStatus_PublicKeyPrime       = 1U << LTC_STA_PKP_SHIFT,
    kLTCStatus_PublicKeyOpOne       = 1U << LTC_STA_PKO_SHIFT,
    kLTCStatus_PublicKeyOpZero      = 1U << LTC_STA_PKZ_SHIFT,
    #endif
    kLTCStatus_All                  = LTC_STA_AB_MASK |
                                      #if FSL_FEATURE_LTC_HAS_DES
                                      LTC_STA_DB_MASK |
                                      #endif /* #if FSL_FEATURE_LTC_HAS_DES */                                      
                                      LTC_STA_DI_MASK |
                                      LTC_STA_EI_MASK 
                                      #if FSL_FEATURE_LTC_HAS_PKHA
                                      | LTC_STA_PB_MASK |
                                      LTC_STA_PKP_MASK |
                                      LTC_STA_PKO_MASK |
                                      LTC_STA_PKZ_MASK
                                      #endif /* FSL_FEATURE_LTC_HAS_PKHA */
} ltc_hal_status_flag_t;

/*! @brief LTC error status flags */
typedef enum _ltc_hal_error_status_flag_t {
    kLTCErrorStatus_Mode            = LTC_ESTA_ERRID1_MODE_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kLTCErrorStatus_DataSize        = LTC_ESTA_ERRID1_DATA_SIZE_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kLTCErrorStatus_KeySize         = LTC_ESTA_ERRID1_KEY_SIZE_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCErrorStatus_PKHA_A_Size     = LTC_ESTA_ERRID1_PKHA_A_SIZE_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kLTCErrorStatus_PKHA_B_Size     = LTC_ESTA_ERRID1_PKHA_B_SIZE_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    #endif
    kLTCErrorStatus_DataSequence    = LTC_ESTA_ERRID1_DATA_OUT_OF_SEQ_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCErrorStatus_PKHA_Div_Zero   = LTC_ESTA_ERRID1_PKHA_DIV_BY_0_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kLTCErrorStatus_PKHA_Mod_Even   = LTC_ESTA_ERRID1_PKHA_MOD_EVEN_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    #endif
    #if FSL_FEATURE_LTC_HAS_DES
    kLTCErrorStatus_DES_Key_Parity  = LTC_ESTA_ERRID1_DES_KEY_PARITY_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    #endif /* FSL_FEATURE_LTC_HAS_DES */
    kLTCErrorStatus_ICV_Check_Fail  = LTC_ESTA_ERRID1_ICV_CHECK_FAIL <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kLTCErrorStatus_Internal_Fail   = LTC_ESTA_ERRID1_INTERNAL_HARD_FAIL <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kLTCErrorStatus_AAD_Size        = LTC_ESTA_ERRID1_CCM_AAD_SIZE_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kTLCErrorStatus_Invalid_Engine  = LTC_ESTA_ERRID1_INVALID_ENGINE_SEL_ERROR <<
                                        LTC_ESTA_ERRID1_SHIFT,
    kLTCErrorStatus_General         = LTC_ESTA_CL1_GEN_ERROR << LTC_ESTA_CL1_SHIFT,
    kLTCErrorStatus_AES             = LTC_ESTA_CL1_AES_ERROR << LTC_ESTA_CL1_SHIFT,
    #if FSL_FEATURE_LTC_HAS_DES
    kLTCErrorStatus_DES             = LTC_ESTA_CL1_DES_ERROR << LTC_ESTA_CL1_SHIFT,
    #endif /* FSL_FEATURE_LTC_HAS_DES */
    #if FSL_FEATURE_LTC_HAS_PKHA
    kLTCErrorStatus_PKHA            = LTC_ESTA_CL1_PKHA_ERROR << LTC_ESTA_CL1_SHIFT,
    #endif /* FSL_FEATURE_LTC_HAS_PKHA */
    kLTCErrorStatus_ErrId           = LTC_ESTA_ERRID1_MASK,
    kLTCErrorStatus_All             = LTC_ESTA_ERRID1_MASK |
                                      LTC_ESTA_CL1_MASK
} ltc_hal_error_status_flag_t;

/*! @brief LTC FIFO status */
typedef enum _ltc_hal_fifo_status_t
{
    kLTCFIFO_OutputFifoFull = 0x80000000U,  /*!< Output FIFO Full bit mask */
    kLTCFIFO_OutputFifoLevel = 0x007F0000U, /*!< Output FIFO Level bit mask */
    kLTCFIFO_InputFifoFull = 0x00008000U,   /*!< Input FIFO Full bit mask */
    kLTCFIFO_InputFifoLevel = 0x0000007FU,  /*!< Input FIFO Level bit mask */
} ltc_hal_fifo_status_t;

/*! @brief LTC PKHA parameters */
typedef struct _ltc_hal_pkha_mode_params_t
{
    ltc_hal_pkha_func_t func;
    ltc_hal_pkha_f2m_t arithType;
    ltc_hal_pkha_montgomery_form_t montFormIn;
    ltc_hal_pkha_montgomery_form_t montFormOut;
    ltc_hal_pkha_reg_area_t srcReg;
    ltc_hal_pkha_quad_area_t srcQuad;
    ltc_hal_pkha_reg_area_t dstReg;
    ltc_hal_pkha_quad_area_t dstQuad;
    ltc_hal_pkha_timing_t equalTime;
    ltc_hal_pkha_r2_t R2modN;
}ltc_hal_pkha_mode_params_t;

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Reads an unaligned word.
 *
 * This function creates a 32-bit word from an input array of four bytes. 
 *
 * @param src Input array of four bytes. The array can start at any address in memory.
 * @return 32-bit unsigned int created from the input byte array.
 */
static inline uint32_t LTC_HAL_GetWordFromUnaligned(const uint8_t * src)
{
    /* __CORTEX_M is defined in CMSIS header file */
#if __CORTEX_M > 0
    /* Cortex M4 does support misaligned loads */
    return *(const uint32_t*)src;
#else
    /* Cortex M0 does not support misaligned loads */
    union _align_bytes_t
    {
        uint32_t word;
        uint8_t  byte[sizeof(uint32_t)];
    } my_bytes;
    
    my_bytes.byte[0] = *src;
    my_bytes.byte[1] = *(src+1);
    my_bytes.byte[2] = *(src+2);
    my_bytes.byte[3] = *(src+3);
    return my_bytes.word;
#endif
}

/*!
 * @brief Converts a 32-bit word into a byte array.
 *
 * This function creates an output array of four bytes from an input 32-bit word.
 *
 * @param srcWord Input 32-bit unsigned integer. 
 * @param dst Output array of four bytes. The array can start at any address in memory.
 */
static inline void LTC_HAL_SetUnalignedFromWord(uint32_t srcWord, uint8_t * dst)
{
    /* __CORTEX_M is defined in CMSIS header file */
#if __CORTEX_M > 0
    /* Cortex M4 does support misaligned stores */
    *(uint32_t*)dst = srcWord;
#else
    /* Cortex M0 does not support misaligned stores */
    *dst++ = (srcWord & 0x000000FFU);
    *dst++ = (srcWord & 0x0000FF00U) >> 8;
    *dst++ = (srcWord & 0x00FF0000U) >> 16;
    *dst++ = (srcWord & 0xFF000000U) >> 24;
#endif
}

/*!
 * @brief Initializes the LTC HAL.
 *
 * Initializes the LTC module to a known working state.
 *
 * @param base LTC module base pointer.
 */
void LTC_HAL_Init(LTC_Type *base);

/*!
 * @brief Sets the LTC operating algorithm.
 *
 * This function sets the mode algorithm to use to switch between the major
 * operating modes of PKHA, AES, DES, and 3DES.  The value of this determines
 * which way the mode register is interpreted, and should be set first
 * before setting other mode settings.
 *
 * @param outMode Output mode word
 * @param alg Algorithm to select
 */
static inline void LTC_HAL_ModeSetAlgorithm(ltc_hal_mode_t *outMode,
                                            ltc_hal_algorithm_t alg)
{    
    *outMode |= (uint32_t) alg;
}

/*!
 * @brief Sets the encrypt/decrypt mode.
 *
 * Sets the operating mode to encrypt or decrypt symmetric key
 * algorithms.
 *
 * @param outMode Output mode word
 * @param encrypt Encrypt/decrypt mode selector
 */
static inline void LTC_HAL_ModeSetEncrypt(ltc_hal_mode_t *outMode,
                                          ltc_hal_mode_encrypt_t encrypt)
{
    *outMode |= encrypt;
}

/*!
 * @brief Gets the encrypt/decrypt mode.
 *
 * Gets the operating mode to encrypt or decrypt the symmetric key
 * algorithms.
 *
 * @param outMode Output mode word
 * @return Encrypt/decrypt mode selector
 */
static inline ltc_hal_mode_encrypt_t LTC_HAL_ModeGetEncrypt(ltc_hal_mode_t *outMode)
{
    return (ltc_hal_mode_encrypt_t)((uint32_t)*outMode & LTC_MD_ENC_MASK);
}

/*!
 * @brief Sets the ICV test selection.
 *
 * Sets the algorithm to perform or not perform ICV checking for all
 * algorithms other than AES ECB.
 *
 * @param outMode Output mode word
 * @param check Compare / Don't compare selector
 */
static inline void LTC_HAL_ModeSetICVTest(ltc_hal_mode_t *outMode,
                                          ltc_hal_mode_icv_check_t check)
{
    *outMode |= check;
}

/*!
 * @brief Sets the algorithm state.
 *
 * Sets the state of the algorithm to be executed.
 *
 * @param outMode Output mode word
 * @param as Algorithm state to select
 */
static inline void LTC_HAL_ModeSetAlgorithmState(ltc_hal_mode_t *outMode,
                                                 ltc_hal_mode_algorithm_state_t as)
{
    *outMode &= ~LTC_MD_AS_MASK;
    *outMode |= as;
}

/*!
 * @brief Gets the algorithm state.
 *
 * Gets the state of the algorithm.
 *
 * @return Algorithm state
 */
static inline ltc_hal_mode_algorithm_state_t LTC_HAL_ModeGetAlgorithmState(ltc_hal_mode_t *outMode)
{
    return (ltc_hal_mode_algorithm_state_t) ((uint32_t)(*outMode) & LTC_MD_AS_MASK);
}

/*!
 * @brief Sets the symmetric algorithm.
 *
 * Sets the symmetric encryption/decryption operating mode.
 *
 * @param outMode Output mode word
 * @param alg Operation mode to use
 */
static inline void LTC_HAL_ModeSetSymmetricAlg(ltc_hal_mode_t *outMode,
                                               ltc_hal_mode_symmetric_alg_t alg)
{
    *outMode |= (uint32_t) alg;
}

/*!
 * @brief Sets the mode DK bit.
 *
 * Sets the LTC AES Mode DK bit to mark the key as decrypt key.
 * 
 */
static inline void LTC_HAL_ModeSetDecryptKey(LTC_Type *base)
{
    uint32_t temp = (kLTCMode_DK | LTC_BRD_MD_AAI(base));
    LTC_BWR_MD_AAI(base, temp);
}

/*!
 * @brief Sets the PKHA function.
 *
 * Sets the mathematics or memory function for the PKHA mode operation.
 *
 * @param outMode Output mode word
 * @param func Function to use
 */
static inline void LTC_HAL_PKHA_ModeSetFunc(ltc_hal_mode_t *outMode,
                                            ltc_hal_pkha_func_t func)
{
    /* This value is part of PKHA_MODE_LS but it always represents bits 0-5. */
    *outMode |= (uint32_t) func;
}

/*!
 * @brief Sets PKHA montgomery inputs.
 *
 * Sets the LTC PKHA mode to use regular or montgomery-form inputs.
 *
 * @param outMode Output mode word
 * @param form Form to use
 */
static inline void LTC_HAL_PKHA_ModeSetMontgomeryInput(
                                            ltc_hal_mode_t *outMode,
                                            ltc_hal_pkha_montgomery_form_t form)
{
    *outMode |= ((uint32_t) form << 19);
}

/*!
 * @brief Sets PKHA montgomery outputs.
 *
 * Sets the LTC PKHA mode to use regular or montgomery-form outputs.
 *
 * @param outMode Output mode word
 * @param form Form to use
 */
static inline void LTC_HAL_PKHA_ModeSetMontgomeryOutput(
                                            ltc_hal_mode_t *outMode,
                                            ltc_hal_pkha_montgomery_form_t form)
{
    *outMode |= ((uint32_t) form << 18);
}

/*!
 * @brief Sets the PKHA arithmetic type (f2m or integer).
 *
 * Sets the LTC PKHA mode to perform integer or f2m binary polynomial
 * operations.
 *
 * @param outMode Output mode word
 * @param form Form to use
 */
static inline void LTC_HAL_PKHA_ModeSetF2M(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_f2m_t form)
{
    *outMode |= ((uint32_t) form << 17);
}

/*!
 * @brief Sets the PKHA use of R2 mod N.
 *
 * Sets the LTC PKHA mode to calculate or use the supplied R2 mod N inputs.
 *
 * @param outMode Output mode word
 * @param form Form to use
 */
static inline void LTC_HAL_PKHA_ModeSetR2(ltc_hal_mode_t *outMode,
                                          ltc_hal_pkha_r2_t form)
{
    *outMode |= ((uint32_t) form << 16);
}

/*!
 * @brief Sets the PKHA timing equalization.
 *
 * Sets the LTC PKHA mode to use timing equalized version of functions or not.
 *
 * @param outMode Output mode word
 * @param form Form to use
 */
static inline void LTC_HAL_PKHA_ModeSetTimingEqual(ltc_hal_mode_t *outMode,
                                                   ltc_hal_pkha_timing_t form)
{
    *outMode |= ((uint32_t) form << 10);
}

/*!
 * @brief Sets the PKHA output selection.
 *
 * Sets the LTC PKHA mode to output results in a particular destination
 * register.
 *
 * @param outMode Output mode word
 * @param form Form to use
 */
static inline void LTC_HAL_PKHA_ModeSetOutput(ltc_hal_mode_t *outMode,
                                              ltc_hal_pkha_output_reg_t form)
{
    *outMode |= ((uint32_t) form << 8);
}

/*!
 * @brief Sets the PKHA RAM area selection.
 *
 * Sets the LTC PKHA mode to clear a particular RAM area.
 *
 * @param outMode Output mode word
 * @param area Ram area to clear.
 */
static inline void LTC_HAL_PKHA_ModeSetRamArea(ltc_hal_mode_t *outMode,
                                               ltc_hal_pkha_reg_area_t area)
{
    *outMode |= ((uint32_t) area << 16);
}

/*!
 * @brief Sets the PKHA Quad area selection.
 *
 * Sets the LTC PKHA mode to clear a particular Quadrant area.
 *
 * @param outMode Output mode word
 * @param quad Quad area to clear.
 */
static inline void LTC_HAL_PKHA_ModeSetQuadArea(ltc_hal_mode_t *outMode,
                                                ltc_hal_pkha_clr_quad_area_t quad)
{
    *outMode |= ((uint32_t) quad << 6);
}

/*!
 * @brief LTC write mode register.
 *
 * The mode register can only be written all at once.  Use the other
 * LTC_HAL_ModeSet* utility functions to construct the mode and then use this
 * to write it to the hardware.
 *
 * @param base LTC module base pointer
 * @param mode Mode to set
 */
static inline void LTC_HAL_WriteMode(LTC_Type *base, ltc_hal_mode_t mode)
{
    LTC_WR_MD(base, mode);
}

/*!
 * @brief LTC read mode register.
 * 
 *
 * @param base LTC module base pointer
 */
static inline ltc_hal_mode_t LTC_HAL_ReadMode(LTC_Type *base)
{
    return LTC_RD_MD(base);
    
}

/*!
 * @brief Gets the LTC key size.
 *
 * Returns the size in bytes of the key used for AES/DES operations.
 * 
 * @param base LTC module base pointer
 * @return Size of key in bytes
 */
static inline uint8_t LTC_HAL_GetKeySize(LTC_Type *base)
{
    return (uint8_t) LTC_RD_KS(base);
}

/*!
 * @brief Sets the LTC key size.
 *
 * Sets the size in bytes of the key being used for AES/DES operations.
 * 
 * @note This should be called after the key itself is written because a write
 * to this prevents writing the key.
 *
 * @param base LTC module base pointer
 * @param keySize Size in bytes of the key to write
 * @return LTC status
 */
ltc_status_t LTC_HAL_SetKeySize(LTC_Type *base, uint8_t keySize);

/*!
 * @brief Gets the LTC data size.
 *
 * Returns the size in bytes of the data being used for AES/DES operations.
 * 
 * @param base LTC module base pointer
 * @return Size of key in bytes
 */
static inline uint16_t LTC_HAL_GetDataSize(LTC_Type *base)
{
    return (uint16_t) LTC_RD_DS(base);
}

/*!
 * @brief Sets the LTC data size.
 *
 * Sets the size in bytes of the data being used for AES/DES operations.
 * 
 * @param base LTC module base pointer
 * @param dataSize Size in bytes of the data that will be written to the input FIFO
 * @return LTC status
 */
ltc_status_t LTC_HAL_SetDataSize(LTC_Type *base, uint16_t dataSize);

/*!
 * @brief Gets the LTC ICV size.
 *
 * Returns the size in bytes of data in the last block of ICV (integrity check
 * value) is valid when performing AES integrity checks.
 *
 * @param base LTC module base pointer
 * @return Size of valid ICV data in bytes
 */
static inline uint8_t LTC_HAL_GetICVSize(LTC_Type *base)
{
    return (uint8_t) LTC_RD_ICVS(base);
}

/*!
 * @brief Sets the LTC ICV size.
 *
 * Sets the size in bytes of data that is valid in the last block ICV
 * (integrity check value).
 * 
 * @param base LTC module base pointer
 * @param dataSize Size in bytes of the valid ICV data
 * @return LTC status
 */
ltc_status_t LTC_HAL_SetICVSize(LTC_Type *base, uint8_t dataSize);

/*!
 * @brief Issues LTC commands.
 *
 * Issues LTC commands to reset the module or submodules.
 * 
 * @param base LTC module base pointer
 * @param cmd Command to issue. 
 *              
 */
static inline void LTC_HAL_Command(LTC_Type *base, ltc_hal_cmd_t cmd)
{
    LTC_WR_COM(base, (uint32_t) cmd);
}

/*!
 * @brief Sets LTC Interrupt Masked.
 *
 * @note After this bit is set, it can only be cleared by hard reset.
 *
 * @param base LTC module base pointer
 * @param mask ISR mask/no mask setting
 */
static inline void LTC_HAL_SetInterruptMask(LTC_Type *base,
                                            ltc_hal_isr_mask_t mask)
{
    LTC_WR_CTL_IM(base, mask);
}

#if FSL_FEATURE_LTC_HAS_PKHA
/*!
 * @brief Sets LTC DMA enable for PKHA.
 *
 * Enables/disables DMA request and done signals for PKHA.
 *
 * @param base LTC module base pointer
 * @param enable Enable/disable DMA
 */
static inline void LTC_HAL_SetPKHAEnableDMA(LTC_Type *base,
                                            ltc_hal_dma_enable_t enable)
{
    LTC_WR_CTL_PDE(base, enable);
}
#endif /* FSL_FEATURE_LTC_HAS_PKHA */

/*!
 * @brief Sets LTC DMA enable for input FIFO.
 *
 * Enables/disables the DMA request and done signals for input FIFO.
 *
 * @param base LTC module base pointer
 * @param enable Enable/disable DMA
 */
static inline void LTC_HAL_SetInputFIFOEnableDMA(LTC_Type *base,
                                                 ltc_hal_dma_enable_t enable)
{
    LTC_WR_CTL_IFE(base, enable);
}

/*!
 * @brief Sets the LTC DMA input FIFO request size.
 *
 * Input FIFO only requests data if the input FIFO has enough space for
 * the request size.
 *
 * @param base LTC module base pointer
 * @param size Input FIFO DMA request size of 1 or 4 bytes
 */
static inline void LTC_HAL_SetInputFIFORequestSizeDMA(LTC_Type *base,
                                                      ltc_hal_fifo_dma_size_t size)
{
    LTC_WR_CTL_IFR(base, size);
}

/*!
 * @brief Sets the LTC DMA enable for output FIFO.
 *
 * Enables/disables the DMA request and done signals for output FIFO.
 *
 * @param base LTC module base pointer
 * @param enable Enable/disable DMA
 */
static inline void LTC_HAL_SetOutputFIFOEnableDMA(LTC_Type *base,
                                                  ltc_hal_dma_enable_t enable)
{
    LTC_WR_CTL_OFE(base, enable);
}

/*!
 * @brief Sets the LTC DMA output FIFO request size.
 *
 * Input FIFO only requests data if the output FIFO has enough space for
 * the request size.
 *
 * @param base LTC module base pointer
 * @param size Output FIFO DMA request size of 1 or 4 bytes
 */
static inline void LTC_HAL_SetOutputFIFORequestSizeDMA(LTC_Type *base,
                                                       ltc_hal_fifo_dma_size_t size)
{
    LTC_WR_CTL_OFR(base, size);
}

/*!
 * @brief Sets the LTC input FIFO byte swap.
 *
 * Sets whether the input FIFO should byte swap all data written to.
 *
 * @param base LTC module base pointer
 * @param swap Input FIFO byte swap value
 */
static inline void LTC_HAL_SetInputFIFOByteSwap(LTC_Type *base,
                                                ltc_hal_byte_swap_t swap)
{
    LTC_WR_CTL_IFS(base, swap);
}

/*!
 * @brief Sets the LTC output FIFO byte swap.
 *
 * Sets whether the output FIFO should byte swap all data read from.
 *
 * @param base LTC module base pointer
 * @param swap Output FIFO byte swap value
 */
static inline void LTC_HAL_SetOutputFIFOByteSwap(LTC_Type *base,
                                                 ltc_hal_byte_swap_t swap)
{
    LTC_WR_CTL_OFS(base, swap);
}

/*!
 * @brief Sets the LTC input key register byte swap.
 *
 * Sets whether the key register should byte swap all data written to.  Data is
 * byte-swapped only within a single word.
 *
 * @param base LTC module base pointer
 * @param swap Input key register byte swap value
 */
static inline void LTC_HAL_SetKeyRegInputByteSwap(LTC_Type *base,
                                                  ltc_hal_byte_swap_t swap)
{
    LTC_WR_CTL_KIS(base, swap);
}

/*!
 * @brief Sets the LTC output key register byte swap.
 *
 * Sets whether the key register should byte swap all data read from.  Data is
 * byte-swapped only within a single word.
 *
 * @param base LTC module base pointer
 * @param swap Output key register byte swap value
 */
static inline void LTC_HAL_SetKeyRegOutputByteSwap(LTC_Type *base,
                                                  ltc_hal_byte_swap_t swap)
{
    LTC_WR_CTL_KOS(base, swap);
}

/*!
 * @brief Sets the LTC input context register byte swap.
 *
 * Sets whether the context register should byte swap all data written to.  Data is
 * byte-swapped only within a single word.
 *
 * @param base LTC module base pointer
 * @param swap Input context register byte swap value
 */
static inline void LTC_HAL_SetCtxRegInputByteSwap(LTC_Type *base,
                                                  ltc_hal_byte_swap_t swap)
{
    LTC_WR_CTL_CIS(base, swap);
}

/*!
 * @brief Sets the LTC output context register byte swap.
 *
 * Sets whether the context register should byte swap all data read from.  Data is
 * byte-swapped only within a single word.
 *
 * @param base LTC module base pointer
 * @param swap Output context register byte swap value
 */
static inline void LTC_HAL_SetCtxRegOutputByteSwap(LTC_Type *base,
                                                   ltc_hal_byte_swap_t swap)
{
    LTC_WR_CTL_COS(base, swap);
}

/*!
 * @brief Sets the LTC key register access lock.
 *
 * Sets read access to the LTC key register.
 *
 * @param base LTC module base pointer
 * @param swap lock Key register read access value
 */
static inline void LTC_HAL_SetKeyRegAccessLock(LTC_Type *base, 
                                               ltc_hal_key_lock_t lock)
{
    LTC_WR_CTL_KAL(base, lock);
}

/*!
 * @brief Clears  LTC internal registers.
 *
 * This function clears various internal registers of the LTC to
 * reset components to a known state.
 *
 * @param base LTC module base pointer
 * @param clear Submodule to be cleared
 */
static inline void LTC_HAL_ClearWritten(LTC_Type *base,
                                        ltc_hal_clear_written_t clear)
{
    LTC_WR_CW(base, clear);
}

/*!
 * @brief Gets LTC status flags.
 *
 * Returns the status of a single or multiple status flags. The return value is
 * only true if at least one of the selected flags are true.
 *
 * @param base LTC module base pointer
 * @param flag Status flag to check
 * @return bool Status flag true/false
 */
static inline bool LTC_HAL_GetStatusFlag(LTC_Type *base,
                                         ltc_hal_status_flag_t flag)
{
    return (bool) ((uint32_t) flag & LTC_RD_STA(base));
}

/*!
 * @brief Clears the status done interrupt.
 *
 * This function clears the interrupt flag that signals an operation has completed, so
 * it can be reasserted on a subsequent operation.
 *
 * @param base LTC module base pointer
 */
static inline void LTC_HAL_ClearDoneInterruptStatus(LTC_Type *base)
{
    LTC_BWR_STA_DI(base, 1);
}

/*!
 * @brief Gets LTC masked status flags.
 *
 * Returns the status of each individual flag requested.
 *
 * @param base LTC module base pointer
 * @param in Status flags to check
 * @param out Output status flags set
 */
void LTC_HAL_GetStatusFlagMasked(LTC_Type *base,
                                 ltc_hal_status_flag_t in,
                                 ltc_hal_status_flag_t *out);

/*!
 * @brief Gets LTC error status flags.
 *
 * Returns the status of a single or multiple error status flags. The return
 * value is only true if all selected flags are true.
 *
 * @param base LTC module base pointer
 * @param flag Error status flag to check
 * @return bool Error status flag true/false
 */
static inline bool LTC_HAL_GetErrorStatusFlag(LTC_Type *base,
                                              ltc_hal_error_status_flag_t flag)
{
    return (bool) ((uint32_t) flag & LTC_RD_ESTA(base));
}

/*!
 * @brief Gets LTC masked error status flags.
 *
 * Returns the error status of each individual flag requested.
 *
 * @param base LTC module base pointer
 * @param flag Error status flag to check
 * @param in Error status flags to check
 * @param out Output error status flags set
 */
void LTC_HAL_GetErrorStatusFlagMasked(LTC_Type *base,
                                      ltc_hal_error_status_flag_t in,
                                      ltc_hal_error_status_flag_t *out);

/*!
 * @brief Gets the LTC AAD size.
 *
 * Returns the size in bytes (mod 16) of how much of the last block of AAD is
 * valid.
 * 
 * @param base LTC module base pointer
 * @param authOnly Output parameter to store whether or not only AAD data is
 *                 to be written to the FIFO, meaning only authentication is
 *                 being performed.
 * @return Size of the AAD, mod 16
 */
uint8_t LTC_HAL_GetAADSize(LTC_Type *base, bool *authOnly);

/*!
 * @brief Sets the LTC AAD size.
 *
 * Sets the size of the AAD to be written.  This data is added to the data size
 * register, which is the AAD size rounded up to the next 16-byte boundary.
 * If the 'authOnly' flag is set, it tells the engine that *only*
 * authentication is performed which means only AAD data is written
 * into the input FIFO.
 * 
 * @param base LTC module base pointer
 * @param Size Size in bytes of the AAD data
 * @param authOnly Whether or not only AAD data is to be written to the FIFO,
 *                 meaning only authentication is being performed.
 */
void LTC_HAL_SetAADSize(LTC_Type *base, uint16_t size, bool authOnly);

#if FSL_FEATURE_LTC_HAS_GCM
/*!
 * @brief Gets the LTC IV size.
 *
 * Returns the size in bytes (mod 16) of how much of the last block of IV is
 * valid.
 * 
 * @param base LTC module base pointer
 * @param onlyIV Output parameter to store whether or not only IV data is
 *               to be written to the FIFO.
 * @return Size of the IV, mod 16
 */
uint8_t LTC_HAL_GetIVSize(LTC_Type *base, bool *onlyIV);

/*!
 * @brief Sets the LTC IV size.
 *
 * Sets the size of the IV to be written.  This data is added to the data size
 * register, which is the IV size rounded up to the next 16-byte boundary.
 * 
 * @param base LTC module base pointer
 * @param Size Size in bytes (mod 16) of the IV data
 * @param onlyIV Whether or not only IV data is to be written to the FIFO
 * @return LTC status
 */
void LTC_HAL_SetIVSize(LTC_Type *base, uint16_t size, bool onlyIV);
#endif /* FSL_FEATURE_LTC_HAS_GCM */

#if FSL_FEATURE_LTC_HAS_DPAMS
/*!
 * @brief Sets the DPA mask seed value.
 *
 * The differential power analysis (DPA) needs a seed mask to introduce noise
 * into the power consumed by the AES module.  This should be seeded at least
 * at POR but preferably every 100 k AES blocks processed to provide DPA
 * protection.
 *
 * @param base LTC module base pointer
 * @param mask Random DPA mask seed value
 */
static inline void LTC_HAL_SetDPAMaskSeed(LTC_Type *base, uint32_t mask)
{
    LTC_WR_DPAMS(base, mask);
}
#endif /* FSL_FEATURE_LTC_HAS_DPAMS */

#if FSL_FEATURE_LTC_HAS_PKHA
/*!
 * @brief Sets the PKHA A size.
 *
 * Sets the size in bytes of data contained in the PKHA A register.
 *
 * @param base LTC module base pointer
 * @param size Size in bytes (maximum 256)
 */
ltc_status_t LTC_HAL_PKHA_SetASize(LTC_Type *base, uint16_t size);

/*!
 * @brief Gets the PKHA A size.
 *
 * Returns the size in bytes of data contained in the PKHA A register.
 *
 * @param base LTC module base pointer
 * @return Size in bytes
 */
static inline uint16_t LTC_HAL_PKHA_GetASize(LTC_Type *base)
{
    return (uint16_t) LTC_RD_PKASZ_PKASZ(base);
}

/*!
 * @brief Sets the PKHA B size.
 *
 * Sets the size in bytes of data contained in the PKHA B register.
 *
 * @param base LTC module base pointer
 * @param size Size in bytes (maximum 256)
 */
ltc_status_t LTC_HAL_PKHA_SetBSize(LTC_Type *base, uint16_t size);

/*!
 * @brief Gets the PKHA B size.
 *
 * Returns the size in bytes of data contained in the PKHA B register.
 *
 * @param base LTC module base pointer
 * @return Size in bytes
 */
static inline uint16_t LTC_HAL_PKHA_GetBSize(LTC_Type *base)
{
    return (uint16_t) LTC_RD_PKBSZ_PKBSZ(base);
}

/*!
 * @brief Sets the PKHA N size.
 *
 * Sets the size in bytes of data contained in the PKHA N register.
 *
 * @param base LTC module base pointer
 * @param size Size in bytes (maximum 256)
 */
ltc_status_t LTC_HAL_PKHA_SetNSize(LTC_Type *base, uint16_t size);

/*!
 * @brief Gets the PKHA N size.
 *
 * Returns the size in bytes of data contained in the PKHA N register.
 *
 * @param base LTC module base pointer
 * @return Size in bytes
 */
static inline uint16_t LTC_HAL_PKHA_GetNSize(LTC_Type *base)
{
    return (uint16_t) LTC_RD_PKNSZ_PKNSZ(base);
}

/*!
 * @brief Sets the PKHA E size.
 *
 * Sets the size in bytes of data contained in the PKHA E register.
 *
 * @param base LTC module base pointer
 * @param size Size in bytes (maximum 256)
 */
ltc_status_t LTC_HAL_PKHA_SetESize(LTC_Type *base, uint16_t size);

/*!
 * @brief Gets the PKHA E size.
 *
 * Returns the size in bytes of data contained in the PKHA E register.
 *
 * @param base LTC module base pointer
 * @return Size in bytes
 */
static inline uint16_t LTC_HAL_PKHA_GetESize(LTC_Type *base)
{
    return (uint16_t) LTC_RD_PKESZ_PKESZ(base);
}
#endif /* FSL_FEATURE_LTC_HAS_PKHA */

/*!
 * @brief Writes the LTC context register;
 *
 * The LTC context register is a 512 bit (64 byte) register that holds
 * internal context for the crypto engine.  The meaning varies based on the
 * algorithm and operating state being used.  This register is written by the
 * driver/application to load state such as IV, counter, and so on. Then, it is
 * updated by the internal crypto engine as needed.
 *
 * @param base LTC module base pointer
 * @param data Data to write
 * @param dataSize Size of data to write in bytes
 * @param startIndex Starting word (4-byte) index into the 16-word register.
 * @return Status of write
 */
ltc_status_t LTC_HAL_SetContext(LTC_Type *base,
                                const uint8_t *data,
                                uint8_t dataSize,
                                uint8_t startIndex);

/*!
 * @brief Reads the LTC context register.
 *
 * The LTC context register is a 512 bit (64 byte) register that holds
 * internal context for the crypto engine.  The meaning varies based on the
 * algorithm and operating state being used.  This register is written by the
 * driver/application to load state such as IV, counter, and so on. Then, it is
 * updated by the internal crypto engine as needed.
 *
 * @param base LTC module base pointer
 * @param data Destination of read data
 * @param dataSize Size of data to read in bytes
 * @param startIndex Starting word (4-byte) index into the 16-word register.
 * @return Status of read
 */                                
ltc_status_t LTC_HAL_GetContext(LTC_Type *base,
                                uint8_t *dest,
                                uint8_t dataSize,
                                uint8_t startIndex);

/*!
 * @brief Sets the LTC keys.
 *
 * This function writes the LTC keys into the key register.  The keys should
 * be written before the key size.
 *
 * @param base LTC module base pointer
 * @param key Array of key words
 * @param keySize Number of bytes for all keys to be loaded (maximum 32, must be a
 *                multiple of 4).
 * @returns Key set status
 */
ltc_status_t LTC_HAL_SetKey(LTC_Type *base, const uint8_t *key, uint8_t keySize);

/*!
 * @brief Gets the LTC keys.
 *
 * This function retrieves the LTC keys from the key register.
 *
 * @param base LTC module base pointer
 * @param key Array of data to store keys
 * @param keySize Number of bytes of keys to retrieve
 * @returns Key set status
 */
ltc_status_t LTC_HAL_GetKey(LTC_Type *base, uint8_t *key, uint8_t keySize);

/*!
 * @brief Gets the input FIFO level.
 *
 * Returns the number of entries currently in the input FIFO.
 *
 * @param base LTC module base pointer
 * @returns Input FIFO entries
 */
static inline uint8_t LTC_HAL_InputFIFOGetLevel(LTC_Type *base)
{
    return (uint8_t) LTC_RD_FIFOSTA_IFL(base);
}

/*!
 * @brief Gets the input FIFO level.
 *
 * Returns the number of entries currently in the input FIFO.
 *
 * @param base LTC module base pointer
 * @returns Input FIFO entries
 */
static inline bool LTC_HAL_InputFIFOFull(LTC_Type *base)
{
    return (bool) LTC_RD_FIFOSTA_IFF(base);
}

/*!
 * @brief Gets the output FIFO level.
 *
 * Returns the number of entries currently in the output FIFO.
 *
 * @param base LTC module base pointer
 * @returns Output FIFO entries
 */
static inline uint8_t LTC_HAL_OutputFIFOGetLevel(LTC_Type *base)
{
    //return (uint8_t) LTC_RD_FIFOSTA_OFL(base);
    return (bool) LTC_RD_FIFOSTA_OFL(base);
}

/*!
 * @brief Gets the output FIFO level.
 *
 * Returns the number of entries currently in the output FIFO.
 *
 * @param base LTC module base pointer
 * @returns Output FIFO entries
 */
static inline bool LTC_HAL_OutputFIFOFull(LTC_Type *base)
{
    return (bool) LTC_RD_FIFOSTA_OFF(base);
}

/*!
 * @brief Writes data to input FIFO.
 *
 * Writes a word of data to the input FIFO for algorithm processing.
 *
 * @param base LTC module base pointer
 * @param data Data to write
 */
static inline void LTC_HAL_WriteInputFIFO(LTC_Type *base, uint32_t data)
{
    LTC_WR_IFIFO(base, data);
}

/*!
 * @brief Reads data from the output FIFO.
 *
 * Reads a word of data from the output FIFO after algorithm processing.
 *
 * @param base LTC module base pointer
 * @returns Data read
 */
static inline uint32_t LTC_HAL_ReadOutputFIFO(LTC_Type *base)
{
    return (uint32_t) LTC_RD_OFIFO(base);
}

/*!
 * @brief Reads data from the LTC FIFO Status register.
 *
 * Reads LTC FIFO Status register actual value.
 *
 * @param base LTC module base pointer
 * @returns Data read
 */
static inline uint32_t LTC_HAL_GetStatusFIFO(LTC_Type *base)
{
    return LTC_FIFOSTA_REG(base);
}

#if FSL_FEATURE_LTC_HAS_PKHA
/*!
 * @brief Writes data to the PKHA A register.
 *
 * Writes data in byte-sized chunks to the PKHA A register, which is 2048 bits in
 * size.  This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes return zero.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes
 * @return Status
 */
ltc_status_t LTC_HAL_WritePKA(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Writes data and its size to the PKHA A register.
 *
 * Writes data in byte-sized chunks to the PKHA A register, which is 2048 bits in
 * size. This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes return zero. Also write
 * data size to PKASZ register.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes and stored in PKASZ reg.
 * @return Status
 */
ltc_status_t LTC_HAL_WriteSizedPKA(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Reads data from the PKHA A register.
 *
 * Reads data in byte-sized chunks from PKHA A register, which is 2048 bits in
 * size.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be read into.  This must be large enough to
 *             store 'dataSize' bytes.
 * @param dataSize Size of data to be read, in bytes
 */
void LTC_HAL_ReadPKA(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize);

/*!
 * @brief Writes data to the PKHA B register.
 *
 * Writes data in byte-sized chunks to PKHA B register, which is 2048 bits in
 * size.  This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes return zero.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes
 * @return Status
 */
ltc_status_t LTC_HAL_WritePKB(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Writes data and its size to the PKHA B register.
 *
 * Writes data in byte-sized chunks to PKHA B register, which is 2048 bits in
 * size. This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes return zero. Also write
 * data size to PKBSZ register.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes and stored in PKBSZ reg.
 * @return Status
 */
ltc_status_t LTC_HAL_WriteSizedPKB(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Reads data from the PKHA B register.
 *
 * Reads data in byte-sized chunks from PKHA B register, which is 2048 bits in
 * size.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be read into.  This must be large enough to
 *             store 'dataSize' bytes.
 * @param dataSize Size of data to be read, in bytes
 */
void LTC_HAL_ReadPKB(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize);

/*!
 * @brief Writes data to the PKHA N register.
 *
 * Writes data in byte-sized chunks to PKHA N register, which is 2048 bits in
 * size.  This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes return zero.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes
 * @return Status
 */
ltc_status_t LTC_HAL_WritePKN(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Writes data and its size to the PKHA N register.
 *
 * Writes data in byte-sized chunks to the PKHA N register, which is 2048 bits in
 * size. This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes return zero. Also write
 * data size to PKNSZ register.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes and stored in PKNSZ reg.
 * @return Status
 */
ltc_status_t LTC_HAL_WriteSizedPKN(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Reads data from the PKHA N register.
 *
 * Reads data in byte-sized chunks from PKHA N register, which is 2048 bits in
 * size.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be read into.  This must be large enough to
 *             store 'dataSize' bytes.
 * @param dataSize Size of data to be read, in bytes
 */
void LTC_HAL_ReadPKN(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize);

/*!
 * @brief Writes data to the PKHA E register.
 *
 * Writes data in byte-sized chunks to PKHA E register, which is 2048 bits in
 * size.  This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes return zero.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes
 * @return Status
 */
ltc_status_t LTC_HAL_WritePKE(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Writes data and its size to the PKHA E register.
 *
 * Writes data in byte-sized chunks to PKHA E register, which is 2048 bits in
 * size. This register can only be written when the mode register is not set
 * for PKHA operation. Otherwise, reads and writes  return zero. Also write
 * data size to PKESZ register.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be written
 * @param dataSize Size of data to be written in bytes and stored in PKESZ reg.
 * @return Status
 */
ltc_status_t LTC_HAL_WriteSizedPKE(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize);

/*!
 * @brief Reads data from the PKHA E register.
 *
 * Reads data in byte-sized chunks from PKHA E register, which is 2048 bits in
 * size.
 *
 * @param base LTC module base pointer
 * @param quad Quadrant in register (0 - 3) to refer to the sub-registers.
 * @param data Array of bytes to be read into.  This must be large enough to
 *             store 'dataSize' bytes.
 * @param dataSize Size of data to be read, in bytes
 */
void LTC_HAL_ReadPKE(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize);

/*!
 * @brief Sets the PKHA copy source register.
 *
 * Sets the LTC PKHA source register to perform register copy.
 *
 * @param outMode Output mode word
 * @param reg Register to use
 */
void LTC_HAL_PKHA_ModeSetSrcRegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_reg_area_t reg);

/*!
 * @brief Sets the PKHA copy destination register.
 *
 * Sets the LTC PKHA destination register to perform register copy.
 *
 * @param outMode Output mode word
 * @param reg Register to use
 */
void LTC_HAL_PKHA_ModeSetDstRegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_reg_area_t reg);

/*!
 * @brief Sets the PKHA copy source segment.
 *
 * Sets the LTC PKHA source segment to perform register copy.
 *
 * @param outMode Output mode word
 * @param reg Register to use
 */
void LTC_HAL_PKHA_ModeSetSrcSegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_quad_area_t quad);
/*!
 * @brief Sets the PKHA copy destination segment.
 *
 * Sets the LTC PKHA destination segment to perform register copy.
 *
 * @param outMode Output mode word
 * @param reg Register to use
 */
void LTC_HAL_PKHA_ModeSetDstSegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_quad_area_t quad);
#endif /* FSL_FEATURE_LTC_HAS_PKHA */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */

#endif /* FSL_FEATURE_SOC_LTC_COUNT */
#endif /* __FSL_LTC_HAL_H__ */

