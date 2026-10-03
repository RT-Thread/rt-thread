#ifndef RENESAS_MACL
#define RENESAS_MACL

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include <stdint.h>
#include "bsp_api.h"

#if BSP_FEATURE_MACL_SUPPORTED
 #if __has_include("arm_math_types.h")

/* Ignore certain math warnings in ARM CMSIS DSP headers */
  #if defined(__ARMCC_VERSION)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wsign-conversion"
   #pragma clang diagnostic ignored "-Wimplicit-int-conversion"
   #pragma clang diagnostic ignored "-Wimplicit-int-float-conversion"
  #elif defined(__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wconversion"
   #pragma GCC diagnostic ignored "-Wsign-conversion"
   #pragma GCC diagnostic ignored "-Wfloat-conversion"
  #endif
  #if defined(__IAR_SYSTEMS_ICC__)
   #pragma diag_suppress=Pe223
  #endif

  #include "arm_math_types.h"
  #include "dsp/basic_math_functions.h"
  #include "dsp/matrix_functions.h"
  #include "dsp/filtering_functions.h"
  #include "dsp/support_functions.h"
  #include "dsp/fast_math_functions.h"

  #if defined(__IAR_SYSTEMS_ICC__)
   #pragma diag_default=Pe223
  #endif
  #if defined(__ARMCC_VERSION)
   #pragma clang diagnostic pop
  #elif defined(__GNUC__)
   #pragma GCC diagnostic pop
  #endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MACL
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Common macro used by MACL */
  #define BSP_MACL_FIXED_POINT_MODE_DISABLE    (0x0)
  #define BSP_MACL_FIXED_POINT_MODE_ENABLE     (0x10)

  #define BSP_MACL_SHIFT_SIGN                  (0x80)
  #define BSP_MACL_SHIFT_1_BIT                 (1U)
  #define BSP_MACL_SHIFT_30_BIT                (30U)
  #define BSP_MACL_SHIFT_31_BIT                (31U)
  #define BSP_MACL_SHIFT_32_BIT                (32U)

  #define BSP_MACL_32_BIT                      (32U)

  #define BSP_MACL_Q31_MAX_VALUE               (0x7FFFFFFF) // Max value is 0.999999999534
  #define BSP_MACL_Q31_MIN_VALUE               (0x80000000) // Min value is -1.0

  #define BSP_MACL_OVERFLOW_VALUE              (0x1)        // 0b01
  #define BSP_MACL_UNDERFLOW_VALUE             (0x2)        // 0b10

  #define BSP_MACL_CLEAR_MULR_REG              (0x0U)

  #define BSP_MACL_POSITIVE_NUM                (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

void R_BSP_MaclMulQ31(const q31_t * p_src_a, const q31_t * p_src_b, q31_t * p_dst, uint32_t block_size);
void R_BSP_MaclScaleQ31(const q31_t * p_src, q31_t scale_fract, int8_t shift, q31_t * p_dst, uint32_t block_size);
void R_BSP_MaclMatMulQ31(const arm_matrix_instance_q31 * p_src_a,
                         const arm_matrix_instance_q31 * p_src_b,
                         arm_matrix_instance_q31       * p_dst);
void R_BSP_MaclMatVecMulQ31(const arm_matrix_instance_q31 * p_src_mat, const q31_t * p_vec, q31_t * p_dst);
void R_BSP_MaclMatScaleQ31(const arm_matrix_instance_q31 * p_src,
                           q31_t                           scale_fract,
                           int32_t                         shift,
                           arm_matrix_instance_q31       * p_dst);
void R_BSP_MaclBiquadCsdDf1Q31(const arm_biquad_casd_df1_inst_q31 * p_biquad_csd_df1_inst,
                               const q31_t                        * p_src,
                               q31_t                              * p_dst,
                               uint32_t                             block_size);
void R_BSP_MaclConvQ31(const q31_t * p_src_a,
                       uint32_t      src_a_len,
                       const q31_t * p_src_b,
                       uint32_t      src_b_len,
                       q31_t       * p_dst);
arm_status R_BSP_MaclConvPartialQ31(const q31_t * p_src_a,
                                    uint32_t      src_a_len,
                                    const q31_t * p_src_b,
                                    uint32_t      src_b_len,
                                    q31_t       * p_dst,
                                    uint32_t      first_idx,
                                    uint32_t      num_points);

void R_BSP_MaclFirDecimateQ31(const arm_fir_decimate_instance_q31 * p_fir_decimate_ins_q31,
                              const q31_t                         * p_src,
                              q31_t                               * p_dst,
                              uint32_t                              block_size);

void R_BSP_MaclFirInterpolateQ31(const arm_fir_interpolate_instance_q31 * p_fir_interpolate_ins_q31,
                                 const q31_t                            * p_src,
                                 q31_t                                  * p_dst,
                                 uint32_t                                 block_size);

void R_BSP_MaclCorrelateQ31(const q31_t * p_src_a,
                            uint32_t      src_a_len,
                            const q31_t * p_src_b,
                            uint32_t      src_b_len,
                            q31_t       * p_dst);

void R_BSP_MaclFirSparseQ31(arm_fir_sparse_instance_q31 * p_fir_sparse_ins_q31,
                            const q31_t                 * p_src,
                            q31_t                       * p_dst,
                            q31_t                       * p_scratch_in,
                            uint32_t                      block_size);

void R_BSP_MaclLmsNormQ31(arm_lms_norm_instance_q31 * p_lms_norm_ins_q31,
                          const q31_t               * p_src,
                          q31_t                     * p_ref,
                          q31_t                     * p_out,
                          q31_t                     * p_err,
                          uint32_t                    block_size);

void R_BSP_MaclLmsQ31(const arm_lms_instance_q31 * p_lms_ins_q31,
                      const q31_t                * p_src,
                      q31_t                      * p_ref,
                      q31_t                      * p_out,
                      q31_t                      * p_err,
                      uint32_t                     block_size);

void R_BSP_MaclFirQ31(const arm_fir_instance_q31 * p_fir_inst, const q31_t * p_src, q31_t * p_dst, uint32_t block_size);

/******************************************************************************************************************//**
 * @} (end addtogroup BSP_MACL)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

 #endif
#endif
#endif
