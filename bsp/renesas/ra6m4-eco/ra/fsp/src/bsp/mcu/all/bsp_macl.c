/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_macl.h"

#if BSP_FEATURE_MACL_SUPPORTED
 #if __has_include("arm_math_types.h")

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

  #ifndef INDEX_MASK

/* This used to be defined in CMSIS DSP. But they have added an undef of the macro in utils.h and therefore it is no longer
 * in scope for the uses of this file.  */
   #define INDEX_MASK    0x0000003F
  #endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static inline void r_macl_wait_operation(void);

static void r_macl_mul_q31(const q31_t * p_src_a, const q31_t * p_src_b, q31_t * p_dst, uint32_t block_size);

static void r_macl_scale_q31(const q31_t * p_src, q31_t scale_fract, int8_t shift, q31_t * p_dst, uint32_t block_size);

static void r_macl_mat_mul_q31(const arm_matrix_instance_q31 * p_src_a,
                               const arm_matrix_instance_q31 * p_src_b,
                               arm_matrix_instance_q31       * p_dst);

static void r_macl_mat_mul_acc_q31(const q31_t * p_in_a,
                                   const q31_t * p_in_b,
                                   q31_t       * p_out,
                                   uint16_t      num_cols_a,
                                   uint16_t      num_cols_b);

static void r_macl_mat_scale_q31(const arm_matrix_instance_q31 * p_src,
                                 q31_t                           scale_fract,
                                 int32_t                         shift,
                                 arm_matrix_instance_q31       * p_dst);
static void r_macl_conv_q31(const q31_t * p_src_a, const q31_t * p_src_b, q31_t * p_dst, uint8_t block_size);

static uint32_t r_macl_recip_q31(q31_t in, q31_t * dst, const q31_t * p_recip_table);

/*******************************************************************************************************************//**
 * @addtogroup BSP_MACL
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Perform multiplication via MACL module.
 *
 * @param[in]   p_src_a       Pointer which point to data A.
 * @param[in]   p_src_b       Pointer which point to data B.
 * @param[out]  p_dst         Pointer to buffer which will hold the calculation result.
 * @param[in]   block_size    Numbers of elements to be calculated.
 **********************************************************************************************************************/
void R_BSP_MaclMulQ31 (const q31_t * p_src_a, const q31_t * p_src_b, q31_t * p_dst, uint32_t block_size)
{
    /* Enable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_ENABLE;

    r_macl_mul_q31(p_src_a, p_src_b, p_dst, block_size);

    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;
}

/*******************************************************************************************************************//**
 * Perform scaling a vector by multiplying scalar via MACL module.
 *
 * @param[in]   p_src        Pointer which point to a vector.
 * @param[in]   scale_fract  Pointer to the scalar number.
 * @param[in]   shift        Number of bits to shift the result by
 * @param[out]  p_dst        Pointer to buffer which will hold the calculation result.
 * @param[in]   block_size   Numbers of elements to be calculated.
 **********************************************************************************************************************/
void R_BSP_MaclScaleQ31 (const q31_t * p_src, q31_t scale_fract, int8_t shift, q31_t * p_dst, uint32_t block_size)
{
    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    r_macl_scale_q31(p_src, scale_fract, shift, p_dst, block_size);
}

/*******************************************************************************************************************//**
 * Perform Q31 matrix multiplication via MACL module.
 *
 * @param[in]   p_src_a       Points to the first input matrix structure A.
 * @param[in]   p_src_b       Points to the second input matrix structure B.
 * @param[out]  p_dst         Points to the buffer which hold output matrix structure.
 **********************************************************************************************************************/
void R_BSP_MaclMatMulQ31 (const arm_matrix_instance_q31 * p_src_a,
                          const arm_matrix_instance_q31 * p_src_b,
                          arm_matrix_instance_q31       * p_dst)
{
    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    r_macl_mat_mul_q31(p_src_a, p_src_b, p_dst);
}

/*******************************************************************************************************************//**
 * Perform Q31 matrix and vector multiplication via MACL module.
 *
 * @param[in]   p_src_mat     Points to the first input matrix structure.
 * @param[in]   p_vec         Points to the input vector.
 * @param[out]  p_dst         Points to the buffer which hold the output vector.
 **********************************************************************************************************************/
void R_BSP_MaclMatVecMulQ31 (const arm_matrix_instance_q31 * p_src_mat, const q31_t * p_vec, q31_t * p_dst)
{
    uint16_t      num_rows     = p_src_mat->numRows; // Number of rows of input matrix
    uint16_t      num_cols     = p_src_mat->numCols; // Number of columns of input matrix
    const q31_t * p_src        = p_src_mat->pData;   // Input data matrix
    const q31_t * p_in_vec     = p_vec;              // Input data vector
    q31_t       * p_out        = p_dst;              // Output data vector
    uint16_t      row          = num_rows;           // Loop counters
    uint16_t      num_cols_vec = 1;

    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    /* Row loop of the matrix */
    do
    {
        /* Perform the multiply-accumulates a row in p_src with the input vector */
        r_macl_mat_mul_acc_q31(p_src, p_in_vec, p_out, num_cols, num_cols_vec);

        p_out++;
        row--;
        p_src += num_cols;
    } while (row > 0U);
}

/*******************************************************************************************************************//**
 * Perform scaling a matrix by multiplying scalar via MACL module.
 *
 * @param[in]   p_src        Points to the vector.
 * @param[in]   scale_fract  Points to the scalar number.
 * @param[in]   shift        Number of bits to shift the result by
 * @param[out]  p_dst        Points to the buffer which will hold the calculation result.
 **********************************************************************************************************************/
void R_BSP_MaclMatScaleQ31 (const arm_matrix_instance_q31 * p_src,
                            q31_t                           scale_fract,
                            int32_t                         shift,
                            arm_matrix_instance_q31       * p_dst)
{
    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    r_macl_mat_scale_q31(p_src, scale_fract, shift, p_dst);
}

/*******************************************************************************************************************//**
 * Perform the biquad cascade direct form I filter in Q31 via MACL module
 *
 * @param[in]   p_biquad_csd_df1_inst   Point to instance of the Q31 Biquad cascade structure
 * @param[in]   p_src                   Point to input sample to be filtered.
 * @param[out]  p_dst                   Point to buffer for storing filtered sample.
 * @param[in]   block_size              Numbers of input sample.
 **********************************************************************************************************************/
void R_BSP_MaclBiquadCsdDf1Q31 (const arm_biquad_casd_df1_inst_q31 * p_biquad_csd_df1_inst,
                                const q31_t                        * p_src,
                                q31_t                              * p_dst,
                                uint32_t                             block_size)
{
    const q31_t       * p_coeffs    = p_biquad_csd_df1_inst->pCoeffs;                         // Coefficient pointer
    q31_t             * p_state     = p_biquad_csd_df1_inst->pState;                          // State pointer
    const q31_t       * p_src_local = p_src;                                                  // Local pointer for p_src
    q31_t             * p_dst_local = p_dst;                                                  // Local pointer for p_dst
    uint32_t            stage       = p_biquad_csd_df1_inst->numStages;                       // Loop counter
    uint32_t            sample;                                                               // Loop counter
    uint32_t            state_update_element;                                                 // Update state buffer
    uint32_t            src_ctrl;                                                             // Control the value of source
    uint32_t            sample_ctrl;                                                          // Control the value of sample
    uint32_t            coeffs_ctrl;                                                          // Control the value of coefficient
    uint32_t            shift           = ((uint32_t) p_biquad_csd_df1_inst->postShift + 1U); // Shift to be applied to the output
    uint32_t            r_shift         = BSP_MACL_32_BIT - shift;                            // Shift to be applied to the output
    volatile uint64_t * p_result_in_q62 = (uint64_t *) &(R_MACL->MULR0.MULRL);                // Assign to address of MULR0

    state_update_element = 0U;
    coeffs_ctrl          = 0U;

    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    while (stage > 0U)
    {
        sample      = block_size;
        src_ctrl    = 0U;
        sample_ctrl = 0U;

        /**
         * y[n] = b0 * x[n] + b1 * x[n - 1] + b2 * x[n -2] + a1 * y[n - 1] + a2 * y[n - 2]
         */
        while (sample > 0U)
        {
            /* Clean result reg */
            R_MACL->MULRCLR = 0U;

            /* Calculate b0.x[n] */
            R_MACL->MAC32S = (uint32_t) p_src_local[src_ctrl];
            R_MACL->MULB0  = (uint32_t) p_coeffs[coeffs_ctrl];
            r_macl_wait_operation();

            /* Calculate for b1.x[n-1] and a1.y[n-1] */
            if (sample_ctrl >= 1U)
            {
                /* b1 * x[n - 1] */
                R_MACL->MAC32S = (uint32_t) p_state[state_update_element];
                R_MACL->MULB0  = (uint32_t) p_coeffs[coeffs_ctrl + 1U];
                r_macl_wait_operation();

                /* a1 * y[n - 1] */
                R_MACL->MAC32S = (uint32_t) p_state[state_update_element + 2U];
                R_MACL->MULB0  = (uint32_t) p_coeffs[coeffs_ctrl + 3U];
                r_macl_wait_operation();
            }

            /* Calculate for b2 * x[n - 2] and a2 * y[n - 2]*/
            if (sample_ctrl >= 2U)
            {
                /* b2 * x[n - 2] */
                R_MACL->MAC32S = (uint32_t) p_state[state_update_element + 1U];
                R_MACL->MULB0  = (uint32_t) p_coeffs[coeffs_ctrl + 2U];
                r_macl_wait_operation();

                /* a2 * y[n - 2] */
                R_MACL->MAC32S = (uint32_t) p_state[state_update_element + 3U];
                R_MACL->MULB0  = (uint32_t) p_coeffs[coeffs_ctrl + 4U];
                r_macl_wait_operation();
            }

            /* Update state buffer */
            p_state[state_update_element + 1U] = p_state[state_update_element]; // x[n - 2] = x[n - 1]
            p_state[state_update_element]      = p_src_local[src_ctrl];         // x[n - 1] = x[n]

            /* Shift and write result to buffer */
            *p_dst_local = (q31_t) (*p_result_in_q62 >> r_shift);

            /* Update state buffer */
            p_state[state_update_element + 3U] = p_state[state_update_element + 2U]; // y[n - 2] = y[n - 1]
            p_state[state_update_element + 2U] = *p_dst_local;                       // Update value of y[n-1]

            sample--;
            src_ctrl++;
            sample_ctrl++;

            /* Check before update addr of p_dst to prevent segmentation fault */
            if (sample != 0U)
            {
                p_dst_local++;
            }
        }

        p_src_local           = p_dst;
        p_dst_local           = p_dst;
        state_update_element += 4U;
        coeffs_ctrl          += 5U;
        stage--;
    }
}

/*******************************************************************************************************************//**
 * Perform the convolution in Q31 via MACL module.
 *
 * @param[in]   p_src_a     Point to input source A
 * @param[in]   src_a_len   Length of source A
 * @param[in]   p_src_b     Point to input source B
 * @param[in]   src_b_len   Length of source B
 * @param[out]  p_dst       Point to result buffer
 **********************************************************************************************************************/
void R_BSP_MaclConvQ31 (const q31_t * p_src_a,
                        uint32_t      src_a_len,
                        const q31_t * p_src_b,
                        uint32_t      src_b_len,
                        q31_t       * p_dst)
{
    uint8_t       src_a_ctrl;          // Control the value of source A
    uint8_t       src_b_ctrl;          // Control the value of source B
    uint8_t       element_ctrl;        // Control the value of element
    uint32_t      src_a_len_local;     // Local length of source A
    uint32_t      src_b_len_local;     // Local length of source B
    const q31_t * p_data_a;            // Input source A pointer
    const q31_t * p_data_b;            // Input source B pointer
    q31_t       * p_dst_local = p_dst; // Output pointer

    src_a_ctrl   = 1U;
    src_b_ctrl   = 1U;
    element_ctrl = 1U;

    /* Enable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_ENABLE;

    /* The algorithm implementation is based on the lengths of the inputs. src B is always made to slide across src A.
     * Therefore, length of B is always considered as shorter or equal to length of A */
    if (src_a_len >= src_b_len)
    {
        p_data_a        = p_src_a;
        p_data_b        = p_src_b;
        src_a_len_local = src_a_len;
        src_b_len_local = src_b_len;
    }
    else
    {
        p_data_a        = p_src_b;
        p_data_b        = p_src_a;
        src_a_len_local = src_b_len;
        src_b_len_local = src_a_len;
    }

    /* Stage 1 */

    /* sum = x[0] * y[0]
     * sum = x[0] * y[1] + x[1] * y[0]
     * ....
     * sum = x[0] * y[srcBlen - 1] + x[1] * y[srcBlen - 2] +...+ x[srcBLen - 1] * y[0]
     */
    while (src_b_ctrl < src_b_len_local)
    {
        /* Perform multiply-accumulate via MACL for convolution operation */
        r_macl_conv_q31(p_data_a, p_data_b, p_dst_local, element_ctrl);

        p_data_b++;
        p_dst_local++;
        element_ctrl++;
        src_b_ctrl++;
        src_a_ctrl++;
    }

    /* Stage 2 */

    /* sum = x[0] * y[srcBLen-1] + x[1] * y[srcBLen-2] +...+ x[srcBLen-1] * y[0]
     * sum = x[1] * y[srcBLen-1] + x[2] * y[srcBLen-2] +...+ x[srcBLen]   * y[0]
     * ....
     * sum = x[srcALen-srcBLen-2] * y[srcBLen-1] + x[srcALen] * y[srcBLen-2] +...+ x[srcALen-1] * y[0]
     */
    while (src_a_ctrl <= src_a_len_local)
    {
        /* Perform multiply-accumulate via MACL for convolution operation */
        r_macl_conv_q31(p_data_a, p_data_b, p_dst_local, element_ctrl);

        p_data_a++;
        p_dst_local++;
        src_a_ctrl++;
    }

    element_ctrl--;

    /* Stage 3 */

    /* sum += x[srcALen-srcBLen+1] * y[srcBLen-1] + x[srcALen-srcBLen+2] * y[srcBLen-2] +...+ x[srcALen-1] * y[1]
     * sum += x[srcALen-srcBLen+2] * y[srcBLen-1] + x[srcALen-srcBLen+3] * y[srcBLen-2] +...+ x[srcALen-1] * y[2]
     * ....
     * sum +=  x[srcALen-2] * y[srcBLen-1] + x[srcALen-1] * y[srcBLen-2]
     * sum +=  x[srcALen-1] * y[srcBLen-1]
     */
    while (element_ctrl > 0U)
    {
        /* Perform multiply-accumulate via MACL for convolution operation */
        r_macl_conv_q31(p_data_a, p_data_b, p_dst_local, element_ctrl);

        p_data_a++;
        element_ctrl--;
        p_dst_local++;
    }

    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;
}

/*******************************************************************************************************************//**
 * Perform the partial convolution in Q31 via MACL module.
 *
 * @param[in]   p_src_a                     Point to input source A
 * @param[in]   src_a_len                   Length of source A
 * @param[in]   p_src_b                     Point to input source B
 * @param[in]   src_b_len                   Length of source B
 * @param[out]  p_dst                       Point to result buffer
 * @param[in]   first_idx                   The first output sample to start with
 * @param[in]   num_points                  The number of output points to be computed
 *
 * @retval      ARM_MATH_SUCCESS            Operation successful
 * @retval      ARM_MATH_ARGUMENT_ERROR     Requested compute points is bigger than result size
 **********************************************************************************************************************/
arm_status R_BSP_MaclConvPartialQ31 (const q31_t * p_src_a,
                                     uint32_t      src_a_len,
                                     const q31_t * p_src_b,
                                     uint32_t      src_b_len,
                                     q31_t       * p_dst,
                                     uint32_t      first_idx,
                                     uint32_t      num_points)
{
    /* Status of Partial convolution */
    arm_status status;

    /* Enable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_ENABLE;

    /* Check for range of output samples to be calculated */
    if ((first_idx + num_points) > (src_a_len + (src_b_len - 1U)))
    {
        /* Set status as ARM_MATH_ARGUMENT_ERROR */
        status = ARM_MATH_ARGUMENT_ERROR;
    }
    else
    {
        /* Loop to calculate convolution for output length number of values */
        for (uint32_t i = first_idx; i <= (first_idx + num_points - 1U); i++)
        {
            /* Clear the Result registers. */
            R_MACL->MULRCLR = 0U;

            /* Loop to perform MAC operations according to convolution equation */
            for (uint32_t j = 0U; j <= i; j++)
            {
                /* Check the array limitations */
                if (((i - j) < src_b_len) && (j < src_a_len))
                {
                    /* z[i] += x[i-j] * y[j] */
                    R_MACL->MAC32S = (uint32_t) (p_src_a[j]);
                    R_MACL->MULB0  = (uint32_t) (p_src_b[i - j]);
                    r_macl_wait_operation();
                }
            }

            /* Store the output in the destination buffer */
            p_dst[i] = (q31_t) R_MACL->MULR0.MULRH;
        }

        /* Set status as ARM_MATH_SUCCESS */
        status = ARM_MATH_SUCCESS;
    }

    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    return status;
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR Decimate Q31 via MACL module.
 *
 * @param[in]   p_fir_decimate_ins_q31   Pointer which point to an instance of the Q31 FIR Decimate structure.
 * @param[in]   p_src                    Pointer which point to the input vector.
 * @param[out]  p_dst                    Pointer to buffer which hold the output vector.
 * @param[in]   block_size               Numbers of samples to be calculated.
 **********************************************************************************************************************/
void R_BSP_MaclFirDecimateQ31 (const arm_fir_decimate_instance_q31 * p_fir_decimate_ins_q31,
                               const q31_t                         * p_src,
                               q31_t                               * p_dst,
                               uint32_t                              block_size)
{
    q31_t       * p_state  = p_fir_decimate_ins_q31->pState;  // State pointer
    const q31_t * p_coeffs = p_fir_decimate_ins_q31->pCoeffs; // Coefficient pointer
    q31_t       * p_state_cur;                                // Points to the current sample of the state
    q31_t       * p_state_buffer;                             // Temporary pointer for state buffer
    const q31_t * p_coeff_buffer;                             // Temporary pointer for coefficient buffer
    uint32_t      num_taps = p_fir_decimate_ins_q31->numTaps; // Number of filter coefficients in the filter
    uint32_t      num_of_decimate_factor;                     // Number of decimation factor
    uint32_t      tap_cnt;                                    // Loop counters
    uint32_t      blk_cnt;                                    // Loop counters

    /* Enable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_ENABLE;

    /* p_fir_decimate_ins_q31->pState buffer contains previous frame (num_taps - 1) samples */
    /* p_state_cur points to the location where the new input data should be written */
    p_state_cur = p_fir_decimate_ins_q31->pState + (num_taps - 1U);

    /* Initialize blk_cnt with number of samples */
    blk_cnt = block_size / p_fir_decimate_ins_q31->M;

    while (blk_cnt > 0U)
    {
        /* Copy decimation factor number of new input samples into the state buffer */
        num_of_decimate_factor = p_fir_decimate_ins_q31->M;

        do
        {
            *p_state_cur++ = *p_src++;
            --num_of_decimate_factor;
        } while (num_of_decimate_factor > 0);

        /* Set accumulator to zero */
        R_MACL->MULRCLR = BSP_MACL_CLEAR_MULR_REG;

        /* Initialize state pointer */
        p_state_buffer = p_state;

        /* Initialize coeff pointer */
        p_coeff_buffer = p_coeffs;

        /* Initialize tap_cnt with number of taps */
        tap_cnt = num_taps;

        while (tap_cnt > 0U)
        {
            /* Perform the multiply-accumulate */
            /* Write state variable to register A */
            R_MACL->MAC32S = (uint32_t) *p_state_buffer++;

            /* Write coeficients to register B*/
            R_MACL->MULB0 = (uint32_t) *p_coeff_buffer++;
            r_macl_wait_operation();

            /* Decrement loop counter */
            tap_cnt--;
        }

        /* Advance the state pointer by the decimation factor
         * to process the next group of decimation factor number samples */
        p_state = p_state + p_fir_decimate_ins_q31->M;

        /* The result is in the accumulator, store in the destination buffer. */
        *p_dst++ = (q31_t) (R_MACL->MULR0.MULRH);

        /* Decrement loop counter */
        blk_cnt--;
    }

    /* Processing is complete.
     * Now copy the last num_taps - 1 samples to the satrt of the state buffer.
     * This prepares the state buffer for the next function call. */

    /* Points to the start of the state buffer */
    p_state_cur = p_fir_decimate_ins_q31->pState;

    /* Initialize tap_cnt with number of taps */
    tap_cnt = (num_taps - 1U);

    /* Copy data */
    while (tap_cnt > 0U)
    {
        *p_state_cur++ = *p_state++;

        /* Decrement loop counter */
        tap_cnt--;
    }

    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR interpolator via MACL module.
 *
 * @param[in]   p_fir_interpolate_ins_q31     Pointer which point to an instance of the Q31 FIR interpolator structure.
 * @param[in]   p_src                         Pointer which point to the input vector.
 * @param[out]  p_dst                         Pointer to buffer which hold the output vector.
 * @param[in]   block_size                    Numbers of samples to be calculated.
 **********************************************************************************************************************/
void R_BSP_MaclFirInterpolateQ31 (const arm_fir_interpolate_instance_q31 * p_fir_interpolate_ins_q31,
                                  const q31_t                            * p_src,
                                  q31_t                                  * p_dst,
                                  uint32_t                                 block_size)
{
    /* Disable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    q31_t             * p_state  = p_fir_interpolate_ins_q31->pState;         // State pointer
    const q31_t       * p_coeffs = p_fir_interpolate_ins_q31->pCoeffs;        // Coefficient pointer
    q31_t             * p_state_cur;                                          // Points to the current sample of the state
    q31_t             * p_state_tmp;                                          // Temporary pointer for state buffer
    const q31_t       * p_coef_tmp;                                           // Temporary pointer for coefficient buffer
    uint32_t            coef_idx;                                             // Index of coefficient
    uint32_t            factor_cnt;                                           // Loop counters
    uint32_t            blk_cnt;                                              // Loop counters
    uint32_t            tap_cnt;                                              // Loop counters
    uint32_t            phase_len   = p_fir_interpolate_ins_q31->phaseLength; // Length of each polyphase filter component
    volatile uint64_t * p_result_r0 = (uint64_t *) &(R_MACL->MULR0.MULRL);    // Assign to address of MULR0

    /* p_state_cur points to the location where the new input data should be written */
    p_state_cur = p_fir_interpolate_ins_q31->pState + (phase_len - 1U);

    /* Initialize blk_cnt with number of samples */
    blk_cnt = block_size;

    while (blk_cnt > 0U)
    {
        /* Copy new input sample into the state buffer */
        *p_state_cur++ = *p_src++;

        /* Address modifier index of coefficient buffer */
        coef_idx = 1U;

        /* Loop over the Interpolation factor. */
        factor_cnt = p_fir_interpolate_ins_q31->L;

        while (factor_cnt > 0U)
        {
            /* Clear registers */
            R_MACL->MULRCLR = BSP_MACL_CLEAR_MULR_REG;

            /* Initialize state pointer */
            p_state_tmp = p_state;

            /* Initialize coefficient pointer */
            p_coef_tmp = p_coeffs + (p_fir_interpolate_ins_q31->L - coef_idx);

            /* Initialize tap_cnt with number of samples */
            tap_cnt = phase_len;

            while (tap_cnt > 0U)
            {
                R_MACL->MAC32S = (uint32_t) (*p_state_tmp);
                R_MACL->MULB0  = (uint32_t) (*p_coef_tmp);

                /* Wait for the calculation. */
                r_macl_wait_operation();

                tap_cnt--;
                p_state_tmp++;
                p_coef_tmp += p_fir_interpolate_ins_q31->L;
            }

            /* The result is in the accumulator, store in the destination buffer. */
            *p_dst++ = (q31_t) (*p_result_r0 >> BSP_MACL_SHIFT_31_BIT);

            /* Increment the address modifier index of coefficient buffer */
            coef_idx++;

            /* Decrement the loop counter */
            factor_cnt--;
        }

        /* Advance the state pointer by 1 to process the next group of interpolation factor number samples */
        p_state = p_state + 1;

        /* Decrement the loop counter */
        blk_cnt--;
    }

    /* Points to the start of the state buffer */
    p_state_cur = p_fir_interpolate_ins_q31->pState;

    /* Initialize tap_cnt with number of samples */
    tap_cnt = (phase_len - 1U);

    /* Copy data */
    while (tap_cnt > 0U)
    {
        *p_state_cur++ = *p_state++;

        /* Decrement loop counter */
        tap_cnt--;
    }
}

/*******************************************************************************************************************//**
 * Perform the Q31 Correlate via MACL module.
 *
 * @param[in]   p_src_a          Point to the first input sequence.
 * @param[in]   src_a_len        Length of the first input sequence.
 * @param[in]   p_src_b          Point to the second input sequence.
 * @param[in]   src_b_len        Length of the second input sequence.
 * @param[out]  p_dst            Points to the location where the output result is written.
 *                               Length 2 * max(src_a_len, src_b_len) - 1.
 **********************************************************************************************************************/
void R_BSP_MaclCorrelateQ31 (const q31_t * p_src_a,
                             uint32_t      src_a_len,
                             const q31_t * p_src_b,
                             uint32_t      src_b_len,
                             q31_t       * p_dst)
{
    const q31_t * p_in1;               // InputA pointer
    const q31_t * p_in2;               // InputB pointer
    q31_t       * p_out = p_dst;       // Output pointer
    const q31_t * p_in_a_buf;          // Intermediate inputA pointer
    const q31_t * p_in_b_buf;          // Intermediate inputB pointer
    const q31_t * p_src1;              // Intermediate pointers
    uint32_t      block_size1;         // Loop counters
    uint32_t      block_size2;         // Loop counters
    uint32_t      block_size3;         // Loop counters
    uint32_t      len_diff_cnt;        // Number of output samples
    uint32_t      cal_cnt;             // Loop counters
    uint32_t      count;               // Loop counters
    int32_t       inc = 1;             // Destination address modifier

    /* Enable Fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_ENABLE;

    /* If src_a_len > src_b_len,
     * (src_a_len - src_b_len) zeroes has to included in the starting of the output buffer */

    /* If src_a_len < src_b_len,
     * (src_b_len - src_a_len) zeroes has to included in the ending of the output buffer */
    if (src_a_len >= src_b_len)
    {
        /* Initialization of inputA pointer */
        p_in1 = p_src_a;

        /* Initialization of inputB pointer */
        p_in2 = p_src_b;

        /* When src_a_len > src_b_len, zero padding is done to srcB
         * to make their lengths equal.
         * Instead, (src_a_len - src_b_len)
         * number of output samples are made zero */
        len_diff_cnt = src_a_len - src_b_len;

        /* Updating the pointer position to non zero value */
        p_out += len_diff_cnt;
    }
    else
    {
        /* Initialization of inputA pointer */
        p_in1 = p_src_b;

        /* Initialization of inputB pointer */
        p_in2 = p_src_a;

        /* src_b_len is always considered as shorter or equal to src_a_len */
        len_diff_cnt = src_b_len;
        src_b_len    = src_a_len;
        src_a_len    = len_diff_cnt;

        /* CORR(x, y) = Reverse order(CORR(y, x)) */
        /* Hence set the destination pointer to point to the last output sample */
        p_out = p_dst + ((src_a_len + src_b_len) - 2U);

        /* Destination address modifier is set to -1 */
        inc = -1;
    }

    /* The function is internally
     * divided into three stages according to the number of multiplications that has to be
     * taken place between inputA samples and inputB samples. In the first stage of the
     * algorithm, the multiplications increase by one for every iteration.
     * In the second stage of the algorithm, src_b_len number of multiplications are done.
     * In the third stage of the algorithm, the multiplications decrease by one
     * for every iteration.
     * The algorithm is implemented in three stages.
     * The loop counters of each stage is initiated here. */
    block_size1 = src_b_len - 1U;
    block_size2 = src_a_len - (src_b_len - 1U);
    block_size3 = block_size1;

    /* --------------------------
     * Initializations of stage1
     * -------------------------*/

    /* sum = x[0] * y[src_b_len - 1]
     * sum = x[0] * y[src_b_len - 2] + x[1] * y[src_b_len - 1]
     * ....
     * sum = x[0] * y[0] + x[1] * y[1] +...+ x[src_b_len - 1] * y[src_b_len - 1]
     *//* In this stage the MAC operations are increased by 1 for every iteration.
     * The count variable holds the number of MAC operations performed */
    count = 1U;

    /* Working pointer of inputA */
    p_in_a_buf = p_in1;

    /* Working pointer of inputB */
    p_src1     = p_in2 + (src_b_len - 1U);
    p_in_b_buf = p_src1;

    /* ------------------------
     * Stage1 process
     * ----------------------*/

    /* The first stage starts here */
    while (block_size1 > 0U)
    {
        /* Accumulator is made zero for every iteration */
        R_MACL->MULRCLR = BSP_MACL_CLEAR_MULR_REG;

        /* Initialize cal_cnt with number of samples */
        cal_cnt = count;

        while (cal_cnt > 0U)
        {
            /* Perform the multiply-accumulate */
            /* x[0] * y[src_b_len - 1] */
            R_MACL->MAC32S = (uint32_t) *p_in_a_buf++;
            R_MACL->MULB0  = (uint32_t) *p_in_b_buf++;
            r_macl_wait_operation();

            /* Decrement loop counter */
            cal_cnt--;
        }

        /* Store the result in the accumulator in the destination buffer. */
        *p_out = (q31_t) (R_MACL->MULR0.MULRH);

        /* Destination pointer is updated according to the address modifier, inc */
        p_out += inc;

        /* Update the inputA and inputB pointers for next MAC calculation */
        p_in_b_buf = p_src1 - count;
        p_in_a_buf = p_in1;

        /* Increment MAC count */
        count++;

        /* Decrement loop counter */
        block_size1--;
    }

    /* --------------------------
     * Initializations of stage2
     * ------------------------*/

    /* sum = x[0] * y[0] + x[1] * y[1] +...+ x[src_b_len-1] * y[src_b_len-1]
     * sum = x[1] * y[0] + x[2] * y[1] +...+ x[src_b_len] * y[src_b_len-1]
     * ....
     * sum = x[src_a_len-src_b_len-2] * y[0] + x[src_a_len-src_b_len-1] * y[1] +...+ x[src_a_len-1] * y[src_b_len-1]
     *//* Working pointer of inputA */
    p_in_a_buf = p_in1;

    /* Working pointer of inputB */
    p_in_b_buf = p_in2;

    /* count is index by which the pointer p_in1 to be incremented */
    count = 0U;

    /* -------------------
     * Stage2 process
     * ------------------*/

    /* Stage2 depends on src_b_len as in this stage src_b_len number of MACS are performed. */

    while (block_size2 > 0U)
    {
        /* Accumulator is made zero for every iteration */
        R_MACL->MULRCLR = BSP_MACL_CLEAR_MULR_REG;

        /* Initialize cal_cnt with number of samples */
        cal_cnt = src_b_len;

        while (cal_cnt > 0U)
        {
            /* Perform the multiply-accumulate */
            R_MACL->MAC32S = (uint32_t) *p_in_a_buf++;
            R_MACL->MULB0  = (uint32_t) *p_in_b_buf++;
            r_macl_wait_operation();

            /* Decrement the loop counter */
            cal_cnt--;
        }

        /* Store the result in the accumulator in the destination buffer. */
        *p_out = (q31_t) (R_MACL->MULR0.MULRH);

        /* Destination pointer is updated according to the address modifier, inc */
        p_out += inc;

        /* Increment MAC count */
        count++;

        /* Update the inputA and inputB pointers for next MAC calculation */
        p_in_a_buf = p_in1 + count;
        p_in_b_buf = p_in2;

        /* Decrement loop counter */
        block_size2--;
    }

    /* --------------------------
     * Initializations of stage3
     * -------------------------*/

    /* sum += x[src_a_len-src_b_len+1] * y[0] + x[src_a_len-src_b_len+2] * y[1] +...+ x[src_a_len-1] * y[src_b_len-1]
     * sum += x[src_a_len-src_b_len+2] * y[0] + x[src_a_len-src_b_len+3] * y[1] +...+ x[src_a_len-1] * y[src_b_len-1]
     * ....
     * sum +=  x[src_a_len-2] * y[0] + x[src_a_len-1] * y[1]
     * sum +=  x[src_a_len-1] * y[0]
     *//* In this stage the MAC operations are decreased by 1 for every iteration.
     * The count variable holds the number of MAC operations performed */
    count = src_b_len - 1U;

    /* Working pointer of inputA */
    p_src1     = p_in1 + (src_a_len - (src_b_len - 1U));
    p_in_a_buf = p_src1;

    /* Working pointer of inputB */
    p_in_b_buf = p_in2;

    /* -------------------
     * Stage3 process
     * ------------------*/

    while (block_size3 > 0U)
    {
        /* Accumulator is made zero for every iteration */
        R_MACL->MULRCLR = BSP_MACL_CLEAR_MULR_REG;

        /* Initialize cal_cnt with number of samples */
        cal_cnt = count;

        while (cal_cnt > 0U)
        {
            /* Perform the multiply-accumulate */
            R_MACL->MAC32S = (uint32_t) *p_in_a_buf++;
            R_MACL->MULB0  = (uint32_t) *p_in_b_buf++;
            r_macl_wait_operation();

            /* Decrement loop counter */
            cal_cnt--;
        }

        /* Store the result in the accumulator in the destination buffer. */
        *p_out = (q31_t) (R_MACL->MULR0.MULRH);

        /* Destination pointer is updated according to the address modifier, inc */
        p_out += inc;

        /* Update the inputA and inputB pointers for next MAC calculation */
        p_in_a_buf = ++p_src1;
        p_in_b_buf = p_in2;

        /* Decrement MAC count */
        count--;

        /* Decrement loop counter */
        block_size3--;
    }

    /* Disable fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR Sparse filter via MACL module.
 *
 * @note The number of p_fir_sparse_ins_q31->numTaps must be greater than or equal to 2
 *
 * @param[in]     p_fir_sparse_ins_q31  points to an instance of the Q31 sparse FIR structure
 * @param[in]     p_src                 points to the block of input data
 * @param[out]    p_dst                 points to the block of output data
 * @param[in]     p_scratch_in          points to a temporary buffer of size blockSize
 * @param[in]     block_size            number of input samples to process
 **********************************************************************************************************************/
void R_BSP_MaclFirSparseQ31 (arm_fir_sparse_instance_q31 * p_fir_sparse_ins_q31,
                             const q31_t                 * p_src,
                             q31_t                       * p_dst,
                             q31_t                       * p_scratch_in,
                             uint32_t                      block_size)
{
    q31_t       * p_state  = p_fir_sparse_ins_q31->pState;
    const q31_t * p_coeffs = p_fir_sparse_ins_q31->pCoeffs;
    q31_t       * p_scratch_tmp;
    q31_t       * p_state_tmp      = p_state;
    q31_t       * p_scratch_in_tmp = p_scratch_in;
    q31_t       * p_out;
    int32_t     * p_tap_delay = p_fir_sparse_ins_q31->pTapDelay;
    uint32_t      delay_size  = p_fir_sparse_ins_q31->maxDelay + block_size;
    uint16_t      num_taps    = p_fir_sparse_ins_q31->numTaps;
    int32_t       read_index;
    uint32_t      tap_cnt;
    uint32_t      blk_cnt;
    q31_t         coeff = *p_coeffs++;
    q31_t         in;

    /* Disable fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    /* block_size of Input samples are copied into the state buffer */
    /* StateIndex points to the starting position to write in the state buffer */
    arm_circularWrite_f32((int32_t *) p_state_tmp, (int32_t) delay_size, &p_fir_sparse_ins_q31->stateIndex, 1,
                          (int32_t *) p_src, 1, block_size);

    /* Read Index, from where the state buffer should be read, is calculated. */
    read_index = (int32_t) (p_fir_sparse_ins_q31->stateIndex - block_size) - *p_tap_delay++;

    /* Wraparound of read_index */
    if (read_index < 0)
    {
        read_index += (int32_t) delay_size;
    }

    /* Working pointer for state buffer is updated */
    p_state_tmp = p_state;

    /* block_size samples are read from the state buffer */
    arm_circularRead_f32((int32_t *) p_state_tmp, (int32_t) delay_size, &read_index, 1, (int32_t *) p_scratch_in_tmp,
                         (int32_t *) p_scratch_in_tmp, (int32_t) block_size, 1, block_size);

    /* Working pointer for the scratch buffer of state values */
    p_scratch_tmp = p_scratch_in_tmp;

    /* Working pointer for scratch buffer of output values */
    p_out = p_dst;

    /* Initialize blk_cnt with number of samples */
    blk_cnt = block_size;

    while (blk_cnt > 0U)
    {
        /* Perform Multiplication and store in destination buffer */
        R_MACL->MUL32S = (uint32_t) *p_scratch_tmp++;
        R_MACL->MULB0  = (uint32_t) coeff;
        r_macl_wait_operation();
        *p_out++ = (q31_t) R_MACL->MULR0.MULRH;

        /* Decrement loop counter */
        blk_cnt--;
    }

    /* Load the coefficient value and
     * increment the coefficient buffer for the next set of state values */
    coeff = *p_coeffs++;

    /* Read Index, from where the state buffer should be read, is calculated. */
    read_index = (int32_t) (p_fir_sparse_ins_q31->stateIndex - block_size) - *p_tap_delay++;

    /* Wraparound of read_index */
    if (read_index < 0)
    {
        read_index += (int32_t) delay_size;
    }

    /* Loop over the number of taps. */
    tap_cnt = (uint32_t) num_taps - 2U;

    while (tap_cnt > 0U)
    {
        /* Working pointer for state buffer is updated */
        p_state_tmp = p_state;

        /* block_size samples are read from the state buffer */
        arm_circularRead_f32((int32_t *) p_state_tmp,
                             (int32_t) delay_size,
                             &read_index,
                             1,
                             (int32_t *) p_scratch_in_tmp,
                             (int32_t *) p_scratch_in_tmp,
                             (int32_t) block_size,
                             1,
                             block_size);

        /* Working pointer for the scratch buffer of state values */
        p_scratch_tmp = p_scratch_in_tmp;

        /* Working pointer for scratch buffer of output values */
        p_out = p_dst;

        /* Initialize blk_cnt with number of samples */
        blk_cnt = block_size;

        while (blk_cnt > 0U)
        {
            /* Perform Multiply-Accumulate */
            /* Initialize out value*/
            R_MACL->MULR0.MULRH = (uint32_t) *p_out;
            R_MACL->MULR0.MULRL = 0x0;

            /* Assign p_scratch_tmp value to register*/
            R_MACL->MAC32S = (uint32_t) *p_scratch_tmp++;

            /* Assign coeff value to register. */
            R_MACL->MULB0 = (uint32_t) coeff;
            r_macl_wait_operation();

            /* Read the result in Q31*/
            *p_out++ = (q31_t) R_MACL->MULR0.MULRH;

            /* Decrement loop counter */
            blk_cnt--;
        }

        /* Load the coefficient value and
         * increment the coefficient buffer for the next set of state values */
        coeff = *p_coeffs++;

        /* Read Index, from where the state buffer should be read, is calculated. */
        read_index = (int32_t) (p_fir_sparse_ins_q31->stateIndex - block_size) - *p_tap_delay++;

        /* Wraparound of read_index */
        if (read_index < 0)
        {
            read_index += (int32_t) delay_size;
        }

        /* Decrement tap loop counter */
        tap_cnt--;
    }

    /* Compute last tap without the final read of p_tap_delay */

    /* Working pointer for state buffer is updated */
    p_state_tmp = p_state;

    /* block_size samples are read from the state buffer */
    arm_circularRead_f32((int32_t *) p_state_tmp, (int32_t) delay_size, &read_index, 1, (int32_t *) p_scratch_in_tmp,
                         (int32_t *) p_scratch_in_tmp, (int32_t) block_size, 1, block_size);

    /* Working pointer for the scratch buffer of state values */
    p_scratch_tmp = p_scratch_in_tmp;

    /* Working pointer for scratch buffer of output values */
    p_out = p_dst;

    /* Initialize blk_cnt with number of samples */
    blk_cnt = block_size;

    while (blk_cnt > 0U)
    {
        /* Perform Multiply-Accumulate */
        /* Initialize out value*/
        R_MACL->MULR0.MULRH = (uint32_t) *p_out;
        R_MACL->MULR0.MULRL = 0x0;

        /* Assign p_scratch_tmp value to register*/
        R_MACL->MAC32S = (uint32_t) *p_scratch_tmp++;

        /* Assign coeff value to register. */
        R_MACL->MULB0 = (uint32_t) coeff;
        r_macl_wait_operation();

        /* Read the result in Q31*/
        *p_out++ = (q31_t) R_MACL->MULR0.MULRH;

        /* Decrement loop counter */
        blk_cnt--;
    }

    /* Working output pointer is updated */
    p_out = p_dst;

    /* Output is converted into 1.31 format. */
    /* Initialize blk_cnt with number of samples */
    blk_cnt = block_size;

    while (blk_cnt > 0U)
    {
        in       = *p_out << BSP_MACL_SHIFT_1_BIT;
        *p_out++ = in;

        /* Decrement loop counter */
        blk_cnt--;
    }
}

/*******************************************************************************************************************//**
 * Perform the Q31 normalized LMS filter via MACL module.
 * @param[in]     p_lms_norm_ins_q31          points to an instance of the Q31 normalized LMS filter structure
 * @param[in]     p_src      points to the block of input data
 * @param[in]     p_ref      points to the block of reference data
 * @param[out]    p_out      points to the block of output data
 * @param[out]    p_err      points to the block of error data
 * @param[in]     block_size number of samples to process
 **********************************************************************************************************************/
void R_BSP_MaclLmsNormQ31 (arm_lms_norm_instance_q31 * p_lms_norm_ins_q31,
                           const q31_t               * p_src,
                           q31_t                     * p_ref,
                           q31_t                     * p_out,
                           q31_t                     * p_err,
                           uint32_t                    block_size)
{
    q31_t             * p_state  = p_lms_norm_ins_q31->pState;             // State pointer
    q31_t             * p_coeffs = p_lms_norm_ins_q31->pCoeffs;            // Coefficient pointer
    q31_t             * p_state_curnt;                                     // Points to the current sample of the state
    q31_t             * p_state_buf;                                       // Temporary pointers for state
    q31_t             * p_coeffs_buf;                                      // Coefficient buffers
    q31_t               mu       = p_lms_norm_ins_q31->mu;                 // Adaptive factor
    uint32_t            num_taps = p_lms_norm_ins_q31->numTaps;            // Number of filter coefficients in the filter
    uint32_t            tap_cnt;                                           // Loop counters
    uint32_t            blk_cnt;                                           // Loop counters
    q31_t               acc;                                               // Accumulator
    q63_t               energy;                                            // Energy of the input
    q31_t               err_data;                                          // Error data sample
    q31_t               weight_factor;                                     // Weight factor and state
    q31_t               data_in;
    q31_t               x0;                                                // Temporary variable to hold input sample
    q31_t               error_x_mu;                                        // Temporary variable to store error
    q31_t               one_by_energy;                                     // Temporary variables to store mu product and reciprocal of energy
    q31_t               post_shift;                                        // Post shift to be applied to weight after reciprocal calculation
    q31_t               acc_l;                                             // Low accumulator
    q31_t               acc_h;                                             // High accumulator
    uint32_t            u_shift = ((uint32_t) p_lms_norm_ins_q31->postShift + 1U);
    uint32_t            l_shift = BSP_MACL_32_BIT - u_shift;               // Shift to be applied to the output
    q63_t               result_temp;                                       // Temporary variable to read result register
    volatile uint64_t * p_result_r4 = (uint64_t *) &(R_MACL->MULR4.MULRL); // Assign to address of MULR4
    uint32_t            tmp_check;                                         // Check overflow/underflow value
    q63_t               mul_tmp = 0;
    energy = p_lms_norm_ins_q31->energy;                                   // Frame energy
    x0     = p_lms_norm_ins_q31->x0;                                       // Input sample

    /* p_lms_norm_ins_q31->pState points to buffer which contains previous frame (num_taps - 1) samples */
    /* p_state_curnt points to the location where the new input data should be written */
    p_state_curnt = &(p_lms_norm_ins_q31->pState[(num_taps - 1U)]);

    /* Initialise loop count */
    blk_cnt = block_size;

    /* Clear the Result registers. */
    R_MACL->MULRCLR = BSP_MACL_CLEAR_MULR_REG;

    /* Disable fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    while (blk_cnt > 0U)
    {
        /* Copy the new input sample into the state buffer */
        *p_state_curnt++ = *p_src;

        /* Initialize p_state pointer */
        p_state_buf = p_state;

        /* Initialize coefficient pointer */
        p_coeffs_buf = p_coeffs;

        /* Read the sample from input buffer */
        data_in = *p_src++;

        /* Update the energy calculation */
        R_MACL->MUL32S = (uint32_t) x0;
        R_MACL->MULB1  = (uint32_t) x0;
        r_macl_wait_operation();
        mul_tmp        = (q63_t) R_MACL->MULR1.MULRH << BSP_MACL_SHIFT_32_BIT;
        mul_tmp       |= R_MACL->MULR1.MULRL;
        energy         = (energy << BSP_MACL_SHIFT_32_BIT) - (mul_tmp << 1);
        R_MACL->MUL32S = (uint32_t) data_in;
        R_MACL->MULB1  = (uint32_t) data_in;
        r_macl_wait_operation();
        mul_tmp  = (q63_t) R_MACL->MULR1.MULRH << BSP_MACL_SHIFT_32_BIT;
        mul_tmp |= R_MACL->MULR1.MULRL;

        energy = (energy + (mul_tmp << 1)) >> BSP_MACL_SHIFT_32_BIT;

        /* Set the accumulator to zero */
        R_MACL->MULR0.MULRH = BSP_MACL_CLEAR_MULR_REG;
        R_MACL->MULR0.MULRL = BSP_MACL_CLEAR_MULR_REG;

        /* Initialize tap_cnt with number of samples */
        tap_cnt = num_taps;

        while (tap_cnt > 0U)
        {
            /* Perform the multiply-accumulate */
            R_MACL->MAC32S = (uint32_t) *p_state_buf++;
            R_MACL->MULB0  = (uint32_t) *p_coeffs_buf++;
            r_macl_wait_operation();

            /* Decrement the loop counter */
            tap_cnt--;
        }

        /* Converting the result to 1.31 format */
        /* Calc lower part of acc */
        acc_l = (q31_t) (R_MACL->MULR0.MULRL >> l_shift);

        /* Calc upper part of acc */
        acc_h = (q31_t) R_MACL->MULR0.MULRH << u_shift;

        acc = acc_l | acc_h;

        /* Store the result from accumulator into the destination buffer. */
        *p_out++ = acc;

        /* Compute and store error */
        err_data = *p_ref++ - acc;
        *p_err++ = err_data;

        /* Calculates the reciprocal of energy */
        post_shift = (q31_t) r_macl_recip_q31((q31_t) energy + DELTA_Q31,
                                              &one_by_energy,
                                              &p_lms_norm_ins_q31->recipTable[0]);

        /* Calculation of product of (e * mu) */
        /* Enable Fixed Point Mode. */
        R_MACL->MULC   = BSP_MACL_FIXED_POINT_MODE_ENABLE;
        R_MACL->MUL32S = (uint32_t) err_data;
        R_MACL->MULB4  = (uint32_t) mu;
        r_macl_wait_operation();
        error_x_mu = (q31_t) R_MACL->MULR4.MULRH;

        /* Disable fixed point mode. */
        R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

        /* Weighting factor for the normalized version */
        R_MACL->MUL32S = (uint32_t) error_x_mu;
        R_MACL->MULB4  = (uint32_t) one_by_energy;
        r_macl_wait_operation();
        result_temp   = (q63_t) *p_result_r4;
        weight_factor = clip_q63_to_q31(result_temp >> (31 - post_shift));

        /* Initialize p_state pointer */
        p_state_buf = p_state;

        /* Initialize coefficient pointer */
        p_coeffs_buf = p_coeffs;

        /* Initialize tap_cnt with number of samples */
        tap_cnt = num_taps;

        while (tap_cnt > 0U)
        {
            /* Perform the multiply-accumulate */
            R_MACL->MULR5.MULRH = (uint32_t) (*p_coeffs_buf >> BSP_MACL_SHIFT_1_BIT);
            R_MACL->MULR5.MULRL = (uint32_t) *p_coeffs_buf << BSP_MACL_SHIFT_31_BIT;
            R_MACL->MAC32S      = (uint32_t) weight_factor;
            R_MACL->MULB5       = (uint32_t) *p_state_buf++;
            r_macl_wait_operation();

            tmp_check = (R_MACL->MULR5.MULRH >> BSP_MACL_SHIFT_30_BIT);

            /* Check overflow/underflow coefficient value */
            if (BSP_MACL_OVERFLOW_VALUE == tmp_check)
            {
                *p_coeffs_buf = (q31_t) BSP_MACL_Q31_MAX_VALUE;
            }
            else if (BSP_MACL_UNDERFLOW_VALUE == tmp_check)
            {
                *p_coeffs_buf = (q31_t) BSP_MACL_Q31_MIN_VALUE;
            }
            else
            {
                /* Enable fixed point mode. */
                R_MACL->MULC |= (uint8_t) R_MACL_MULC_MULFRAC_Msk;

                *p_coeffs_buf = (q31_t) R_MACL->MULR5.MULRH;

                /* Disable fixed point mode. */
                R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;
            }

            /* Increment the coefficient buffer */
            p_coeffs_buf++;

            /* Decrement loop counter */
            tap_cnt--;
        }

        /* Read the sample from state buffer */
        x0 = *p_state;

        /* Advance state pointer by 1 for the next sample */
        p_state = p_state + 1;

        /* Decrement loop counter */
        blk_cnt--;
    }

    /* Save energy and x0 values for the next frame */
    p_lms_norm_ins_q31->energy = (q31_t) energy;
    p_lms_norm_ins_q31->x0     = x0;

    /* Processing is complete.
     * Now copy the last num_taps - 1 samples to the start of the state buffer.
     * This prepares the state buffer for the next function call. */

    /* Points to the start of the p_state buffer */
    p_state_curnt = p_lms_norm_ins_q31->pState;

    /* Initialize tap_cnt with number of samples */
    tap_cnt = (num_taps - 1U);

    while (tap_cnt > 0U)
    {
        *p_state_curnt++ = *p_state++;

        /* Decrement loop counter */
        tap_cnt--;
    }
}

/*******************************************************************************************************************//**
 * Perform the Q31 LMS filter via MACL module.
 * @param[in]     p_lms_ins_q31          points to an instance of the Q31 normalized LMS filter structure
 * @param[in]     p_src      points to the block of input data
 * @param[in]     p_ref      points to the block of reference data
 * @param[out]    p_out      points to the block of output data
 * @param[out]    p_err      points to the block of error data
 * @param[in]     block_size number of samples to process
 **********************************************************************************************************************/
void R_BSP_MaclLmsQ31 (const arm_lms_instance_q31 * p_lms_ins_q31,
                       const q31_t                * p_src,
                       q31_t                      * p_ref,
                       q31_t                      * p_out,
                       q31_t                      * p_err,
                       uint32_t                     block_size)
{
    q31_t  * p_state  = p_lms_ins_q31->pState;    // State pointer
    q31_t  * p_coeffs = p_lms_ins_q31->pCoeffs;   // Coefficient pointer
    q31_t  * p_state_curnt;                       // Points to the current sample of the state
    q31_t  * p_state_buf;                         // Temporary pointers for state
    q31_t  * p_coeffs_buf;                        // Coefficient buffers
    q31_t    mu       = p_lms_ins_q31->mu;        // Adaptive factor
    uint32_t num_taps = p_lms_ins_q31->numTaps;   // Number of filter coefficients in the filter
    uint32_t tap_cnt;                             // Loop counters
    uint32_t blk_cnt;                             // Loop counters
    q63_t    acc;                                 // Accumulator
    q31_t    err_data = 0;                        // Error data sample
    q31_t    alpha;                               // Intermediate constant for taps update
    q31_t    acc_l;                               // Low accumulator
    q31_t    acc_h;                               // High accumulator
    uint32_t u_shift = (p_lms_ins_q31->postShift + 1);
    uint32_t l_shift = BSP_MACL_32_BIT - u_shift; // Shift to be applied to the output
    uint32_t tmp_check;                           // Check overflow/underflow value

    /* Disable fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    /* p_lms_ins_q31->pState points to buffer which contains previous frame (numTaps - 1) samples */
    /* pStateCurnt points to the location where the new input data should be written */
    p_state_curnt = &(p_lms_ins_q31->pState[(num_taps - 1U)]);

    /* initialise loop count */
    blk_cnt = block_size;

    while (blk_cnt > 0U)
    {
        /* Copy the new input sample into the state buffer */
        *p_state_curnt++ = *p_src++;

        /* Initialize pState pointer */
        p_state_buf = p_state;

        /* Initialize coefficient pointer */
        p_coeffs_buf = p_coeffs;

        /* Set the accumulator to zero */
        R_MACL->MULRCLR = BSP_MACL_CLEAR_MULR_REG;

        /* Initialize tapCnt with number of samples */
        tap_cnt = num_taps;

        while (tap_cnt > 0U)
        {
            /* Perform the multiply-accumulate */

            R_MACL->MAC32S = (uint32_t) *p_state_buf++;
            R_MACL->MULB0  = (uint32_t) *p_coeffs_buf++;
            r_macl_wait_operation();

            /* Decrement the loop counter */
            tap_cnt--;
        }

        /* Converting the result to 1.31 format */
        /* Calc lower part of acc */
        acc_l = (q31_t) (R_MACL->MULR0.MULRL >> l_shift);

        /* Calc upper part of acc */
        acc_h = (q31_t) R_MACL->MULR0.MULRH << u_shift;

        acc = acc_l | acc_h;

        /* Store the result from accumulator into the destination buffer. */
        *p_out++ = (q31_t) acc;

        /* Compute and store error */
        err_data = *p_ref++ - (q31_t) acc;
        *p_err++ = err_data;

        /* Compute alpha i.e. intermediate constant for taps update */
        /* Enable Fixed Point Mode. */
        R_MACL->MULC   = BSP_MACL_FIXED_POINT_MODE_ENABLE;
        R_MACL->MUL32S = (uint32_t) err_data;
        R_MACL->MULB4  = (uint32_t) mu;
        r_macl_wait_operation();
        alpha = (q31_t) R_MACL->MULR4.MULRH;

        /* Initialize pState pointer */
        /* Advance state pointer by 1 for the next sample */
        p_state_buf = p_state++;

        /* Initialize coefficient pointer */
        p_coeffs_buf = p_coeffs;

        /* Initialize tapCnt with number of samples */
        tap_cnt = num_taps;

        /* Disable fixed point mode. */
        R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

        while (tap_cnt > 0U)
        {
            /* Perform the multiply-accumulate */

            /* coef = (q31_t) (((q63_t) alpha * (*px++)) >> (32));
             * pb = clip_q63_to_q31((q63_t) * pb + (coef << 1U)); */
            R_MACL->MULR5.MULRH = (uint32_t) (*p_coeffs_buf >> BSP_MACL_SHIFT_1_BIT);
            R_MACL->MULR5.MULRL = (uint32_t) *p_coeffs_buf << BSP_MACL_SHIFT_31_BIT;

            R_MACL->MAC32S = (uint32_t) alpha;
            R_MACL->MULB5  = (uint32_t) *p_state_buf++;
            r_macl_wait_operation();

            tmp_check = (R_MACL->MULR5.MULRH >> BSP_MACL_SHIFT_30_BIT);

            /* Check overflow/underflow coefficient value */
            if (BSP_MACL_OVERFLOW_VALUE == tmp_check)
            {
                *p_coeffs_buf = (q31_t) BSP_MACL_Q31_MAX_VALUE;
            }
            else if (BSP_MACL_UNDERFLOW_VALUE == tmp_check)
            {
                *p_coeffs_buf = (q31_t) BSP_MACL_Q31_MIN_VALUE;
            }
            else
            {
                /* Enable fixed point mode. */
                R_MACL->MULC |= (uint8_t) R_MACL_MULC_MULFRAC_Msk;

                *p_coeffs_buf = (q31_t) R_MACL->MULR5.MULRH;

                /* Disable fixed point mode. */
                R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;
            }

            /* Increment the coefficient buffer */
            p_coeffs_buf++;

            /* Decrement loop counter */
            tap_cnt--;
        }

        /* Decrement loop counter */
        blk_cnt--;
    }

    /* Processing is complete.
     * Now copy the last numTaps - 1 samples to the start of the state buffer.
     * This prepares the state buffer for the next function call. */

    /* Points to the start of the pState buffer */
    p_state_curnt = p_lms_ins_q31->pState;

    /* copy data */
    /* Initialize tapCnt with number of samples */
    tap_cnt = (num_taps - 1U);

    while (tap_cnt > 0U)
    {
        *p_state_curnt++ = *p_state++;

        /* Decrement loop counter */
        tap_cnt--;
    }
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR filter via MACL module.
 *
 * @param[in]     p_fir_inst    Points to an instance of the Q31 FIR filter structure
 * @param[in]     p_src         Points to the block of input data
 * @param[in]     p_ref         Points to the block of reference data
 * @param[out]    p_out         Points to the block of output data
 * @param[out]    p_err         Points to the block of error data
 * @param[in]     block_size    Number of samples to process
 **********************************************************************************************************************/
void R_BSP_MaclFirQ31 (const arm_fir_instance_q31 * p_fir_inst, const q31_t * p_src, q31_t * p_dst, uint32_t block_size)
{
    q31_t       * p_state;             // Pointer to state buffer which will be used to hold calculated sample
    q31_t       * p_state_curnt;       // Intermediate pointer used to write sample into state buffer
    q31_t       * p_state_tmp;         // Intermediate pointer to write sample value into register MAC32S
    const q31_t * p_coeff_tmp;         // Intermediate pointer to write coefficient into register MULB0
    const q31_t * p_coeffs;            // Local pointer for p_Coeff of instance p_fir_inst
    uint16_t      num_taps;            // Numbers of coefficient
    uint32_t      tap_cnt;             // Loop count
    uint32_t      blk_cnt;             // Loop count

    p_state  = p_fir_inst->pState;
    p_coeffs = p_fir_inst->pCoeffs;

    num_taps = p_fir_inst->numTaps;
    blk_cnt  = block_size;

    /* p_fir_inst->pState points to state array which contains previous frame (num_taps - 1) samples */
    /* p_state_curnt points to the location where the new input data should be written */
    p_state_curnt = &(p_fir_inst->pState[(num_taps - 1U)]);

    /* Enable fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_ENABLE;

    while (blk_cnt > 0U)
    {
        /* Copy one sample at a time into state buffer */
        *p_state_curnt++ = *p_src++;

        /* Initialize state pointer */
        p_state_tmp = p_state;

        /* Initialize Coefficient pointer */
        p_coeff_tmp = p_coeffs;

        tap_cnt = num_taps;

        /* Clean result reg */
        R_MACL->MULRCLR = 0U;

        /* Perform the multiply-accumulates */
        do
        {
            /* y[n] =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0] */
            R_MACL->MAC32S = (uint32_t) (*p_state_tmp++);
            R_MACL->MULB0  = (uint32_t) (*p_coeff_tmp++);

            r_macl_wait_operation();

            tap_cnt--;
        } while (tap_cnt > 0U);

        /* Store result into destination buffer. */
        *p_dst++ = (q31_t) R_MACL->MULR0.MULRH;

        /* Advance state pointer by 1 for the next sample */
        p_state++;

        /* Decrement loop counter */
        blk_cnt--;
    }

    /* Disable fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    /* Processing is complete. Now copy the last num_taps - 1 samples to the start of the state buffer. This prepares
     * the state buffer for the next function call. */

    /* Points to the start of the state buffer */
    p_state_curnt = p_fir_inst->pState;

    /* Initialize tapCnt with number of taps */
    tap_cnt = (num_taps - 1U);

    /* Copy remaining data */
    while (tap_cnt > 0U)
    {
        *p_state_curnt++ = *p_state++;

        /* Decrement loop counter */
        tap_cnt--;
    }
}

/*******************************************************************************************************************//**
 * Waiting for MACL module finish 5 cycles of processing.
 *
 **********************************************************************************************************************/
static inline void r_macl_wait_operation ()
{
    /* Wait for 5 cycles */
    __asm volatile (
        "nop \n"
        "nop \n"
        "nop \n"
        "nop \n"
        "nop \n"
        );
}

/*******************************************************************************************************************//**
 * Multiplication operation of MACL module.
 *
 * @param[in]   p_src_a       Pointer to multiplied number.
 * @param[in]   p_src_b       Pointer to multiplicand number.
 * @param[out]  p_dst         Pointer to buffer which will hold the calculation result.
 * @param[in]   block_size    Numbers of elements to be calculated.
 **********************************************************************************************************************/
static void r_macl_mul_q31 (const q31_t * p_src_a, const q31_t * p_src_b, q31_t * p_dst, uint32_t block_size)
{
    const q31_t * p_src_a_local;
    const q31_t * p_src_b_local;
    q31_t       * p_dst_local;
    uint32_t      block_size_cnt;

    block_size_cnt = block_size;

    p_src_a_local = p_src_a;
    p_src_b_local = p_src_b;
    p_dst_local   = p_dst;

    /* Clean result register before perform the calculation */
    R_MACL->MULRCLR = 0U;

    while (block_size_cnt > 0U)
    {
        if ((*p_src_a_local == (q31_t) BSP_MACL_Q31_MIN_VALUE) && (*p_src_b_local == (q31_t) BSP_MACL_Q31_MIN_VALUE))
        {
            /* Overflow case */
            *p_dst_local = (q31_t) BSP_MACL_Q31_MAX_VALUE;
        }
        else
        {
            /* Write value to perform the multiply operation */
            R_MACL->MUL32S = (uint32_t) (*p_src_a_local);
            R_MACL->MULB0  = (uint32_t) (*p_src_b_local);

            /* Wait for the calculation. */
            r_macl_wait_operation();

            *p_dst_local = (q31_t) R_MACL->MULR0.MULRH;
        }

        block_size_cnt--;
        p_src_a_local++;
        p_src_b_local++;
        p_dst_local++;
    }
}

/*******************************************************************************************************************//**
 * Perform scaling a vector by multiplying scalar via MACL module.
 *
 * @param[in]   p_src        Pointer which point to a vector.
 * @param[in]   scale_fract  Pointer to the scalar number.
 * @param[in]   shift        Number of bits to shift the result by
 * @param[out]  p_dst        Pointer to buffer which will hold the calculation result.
 * @param[in]   block_size   Numbers of elements to be calculated.
 **********************************************************************************************************************/
static void r_macl_scale_q31 (const q31_t * p_src, q31_t scale_fract, int8_t shift, q31_t * p_dst, uint32_t block_size)
{
    const q31_t * p_src_local;
    q31_t       * p_dst_local;
    q31_t         out;
    uint32_t      block_size_cnt;
    bool          shift_signed;
    int32_t       scale_shift;         /* Shift to apply after scaling */

    volatile uint32_t * p_result = &(R_MACL->MULR0.MULRH);

    block_size_cnt = block_size;
    shift_signed   = (bool) (shift & BSP_MACL_SHIFT_SIGN);
    scale_shift    = shift + 1;

    p_src_local = p_src;
    p_dst_local = p_dst;

    /* Clean result register before perform the calculation */
    R_MACL->MULRCLR = 0U;

    /* Write data to register MUL32S. */
    R_MACL->MUL32S = (uint32_t) scale_fract;

    while (block_size_cnt > 0U)
    {
        /* Write data to register B */
        R_MACL->MULB0 = (uint32_t) (*p_src_local);

        /* Wait for the calculation. */
        r_macl_wait_operation();

        if (shift_signed == BSP_MACL_POSITIVE_NUM)
        {
            /* Read data to register MULRLn.MULRH */
            out = (q31_t) (*p_result) << scale_shift;

            if (*p_result != (uint32_t) (out >> scale_shift))
            {
                /* Overflow/underflow check for shifting result */
                if (BSP_MACL_POSITIVE_NUM == (*p_result >> BSP_MACL_SHIFT_31_BIT))
                {
                    out = (q31_t) (BSP_MACL_Q31_MAX_VALUE);
                }
                else
                {
                    out = (q31_t) (BSP_MACL_Q31_MIN_VALUE);
                }
            }

            /* Write out the result */
            *p_dst_local = out;
        }
        else
        {
            /* Read data to register MULRLn.MULRH. */
            out = (q31_t) (*p_result) >> -scale_shift;

            /* Write out the result */
            *p_dst_local = out;
        }

        block_size_cnt--;
        p_src_local++;
        p_dst_local++;
    }
}

/*******************************************************************************************************************//**
 * Perform Q31 matrix multiplication via MACL module.
 *
 * @param[in]   p_src_a       Points to the first input matrix structure A.
 * @param[in]   p_src_b       Points to the second input matrix structure B.
 * @param[out]  p_dst         Points to the buffer which hold output matrix structure.
 **********************************************************************************************************************/
static void r_macl_mat_mul_q31 (const arm_matrix_instance_q31 * p_src_a,
                                const arm_matrix_instance_q31 * p_src_b,
                                arm_matrix_instance_q31       * p_dst)
{
    const q31_t * p_in_a = p_src_a->pData;       // Input data matrix pointer A
    const q31_t * p_in_b;                        // Input data matrix pointer B
    q31_t       * p_out      = p_dst->pData;     // Output data matrix pointer
    uint16_t      num_rows_a = p_src_a->numRows; // Number of rows of input matrix A
    uint16_t      num_cols_b = p_src_b->numCols; // Number of columns of input matrix B
    uint16_t      num_cols_a = p_src_a->numCols; // Number of columns of input matrix A
    uint16_t      col;                           // Column loop counters
    uint16_t      row = num_rows_a;              // Row loop counters

    /* Row loop */
    do
    {
        /* For every row wise process, column loop counter is to be initiated */
        col = num_cols_b;

        /* For every row wise process, p_in_b pointer is set to starting address of p_src_b data */
        p_in_b = p_src_b->pData;

        /* Column loop */
        do
        {
            /* Perform the multiply-accumulates a row in p_src_a with a column in p_src_b */
            r_macl_mat_mul_acc_q31(p_in_a, p_in_b, p_out, num_cols_a, num_cols_b);

            p_in_b++;
            p_out++;
            col--;
        } while (col > 0U);

        row--;
        p_in_a += num_cols_a;
    } while (row > 0U);
}

/*******************************************************************************************************************//**
 * Perform the multiply-accumulates a row with a column.
 *
 * @param[in]   p_in_a        Points to the input data matrix pointer A.
 * @param[in]   p_in_b        Points to the input data matrix pointer B.
 * @param[out]  p_out         Points to the output data matrix pointer.
 * @param[in]   num_cols_a    Number of columns of input matrix A.
 * @param[in]   num_cols_b    Number of columns of input matrix B.
 **********************************************************************************************************************/
static void r_macl_mat_mul_acc_q31 (const q31_t * p_in_a,
                                    const q31_t * p_in_b,
                                    q31_t       * p_out,
                                    uint16_t      num_cols_a,
                                    uint16_t      num_cols_b)
{
    uint16_t      cnt     = num_cols_a;
    const q31_t * p_tmp_a = p_in_a;
    const q31_t * p_tmp_b = p_in_b;
    q31_t         out_h;
    q31_t         out_l;

    R_MACL->MULRCLR = 0U;

    while (cnt > 0U)
    {
        R_MACL->MAC32S = (uint32_t) (*p_tmp_a);
        R_MACL->MULB0  = (uint32_t) (*p_tmp_b);

        /* Wait for the calculation. */
        r_macl_wait_operation();
        cnt--;
        p_tmp_a++;
        p_tmp_b += num_cols_b;
    }

    /* Read data to register MULR0. */
    out_h  = (q31_t) (R_MACL->MULR0.MULRH << BSP_MACL_SHIFT_1_BIT);
    out_l  = (q31_t) (R_MACL->MULR0.MULRL >> BSP_MACL_SHIFT_31_BIT);
    *p_out = (out_h | out_l);
}

/*******************************************************************************************************************//**
 * Perform scaling a matrix by multiplying scalar via MACL module.
 *
 * @param[in]   p_src        Points to the input matrix.
 * @param[in]   scale_fract  Fractional portion of the scale factor.
 * @param[in]   shift        Number of bits to shift the result by
 * @param[out]  p_dst        Points to the output matrix structure which will hold the calculation result.
 **********************************************************************************************************************/
static void r_macl_mat_scale_q31 (const arm_matrix_instance_q31 * p_src,
                                  q31_t                           scale_fract,
                                  int32_t                         shift,
                                  arm_matrix_instance_q31       * p_dst)
{
    q31_t             * p_in  = p_src->pData; // Input data matrix pointer
    q31_t             * p_out = p_dst->pData; // Output data matrix pointer
    uint32_t            block_size;           // Loop counter
    q31_t               out;                  // Temporary output data
    int32_t             scale_shift;          // Shift to apply after scaling
    volatile uint32_t * p_result = &(R_MACL->MULR0.MULRH);

    scale_shift = shift + 1;

    /* Total number of samples in input matrix */
    block_size = (uint32_t) (p_src->numRows * p_src->numCols);

    /* Clean result register before perform the calculation */
    R_MACL->MULRCLR = 0U;

    /* Write data to register MUL32S. */
    R_MACL->MUL32S = (uint32_t) scale_fract;

    while (block_size > 0U)
    {
        /* Write data to register B. */
        R_MACL->MULB0 = (uint32_t) (*p_in);

        /* Wait for the calculation. */
        r_macl_wait_operation();

        /* Read data to register MULRL.MULRH. */
        out = (q31_t) (*p_result) << scale_shift;

        if (*p_result != (uint32_t) (out >> scale_shift))
        {
            /* Overflow/underflow check for shifting result */
            if (BSP_MACL_POSITIVE_NUM == (*p_result >> BSP_MACL_SHIFT_31_BIT))
            {
                out = (q31_t) (BSP_MACL_Q31_MAX_VALUE);
            }
            else
            {
                out = (q31_t) (BSP_MACL_Q31_MIN_VALUE);
            }
        }

        /* Write out the result. */
        *p_out = out;

        block_size--;
        p_in++;
        p_out++;
    }
}

/*******************************************************************************************************************//**
 * Perform multiply-accumulate via MACL for convolution operation.
 *
 * @param[in]   check_value     Value which got from result register MULRH.
 * @param[out]  p_dst            Pointer to destination buffer.
 **********************************************************************************************************************/
void r_macl_conv_q31 (const q31_t * p_src_a, const q31_t * p_src_b, q31_t * p_dst, uint8_t block_size)
{
    uint8_t       cnt;
    const q31_t * p_src_a_local;
    const q31_t * p_src_b_local;
    q31_t       * p_dst_local;

    p_src_a_local = p_src_a;
    p_src_b_local = p_src_b;
    p_dst_local   = p_dst;

    cnt = block_size;

    /* Clean register result */
    R_MACL->MULRCLR = 0U;

    /* Perform multiply-accumulate */
    while (cnt > 0)
    {
        R_MACL->MAC32S = (uint32_t) (*p_src_a_local);
        R_MACL->MULB0  = (uint32_t) (*p_src_b_local);

        /* Wait for the calculation. */
        r_macl_wait_operation();

        p_src_a_local++;
        p_src_b_local--;
        cnt--;
    }

    /* Store result into desire buffer */
    *p_dst_local = (q31_t) R_MACL->MULR0.MULRH;
}

/*******************************************************************************************************************//**
 * Function to Calculates 1/in (reciprocal) value of Q31 Data type.
 *
 * @param[in]   in                   Input data.
 * @param[out]  dst                  Point to output data.
 * @param[in]   p_recip_table        Points to the reciprocal initial value table.
 **********************************************************************************************************************/

uint32_t r_macl_recip_q31 (q31_t in, q31_t * dst, const q31_t * p_recip_table)
{
    q31_t               out;
    uint32_t            temp_val;
    uint32_t            index;
    uint32_t            sign_bits;
    uint64_t            reg_val;
    volatile uint64_t * p_result_r3 = (uint64_t *) &(R_MACL->MULR3.MULRL);

    /* Enable fixed point mode. */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_ENABLE;
    if (in > 0)
    {
        sign_bits = ((uint32_t) (__CLZ((uint32_t) in) - 1));
    }
    else
    {
        sign_bits = ((uint32_t) (__CLZ((uint32_t) (-in)) - 1));
    }

    /* Convert input sample to 1.31 format */
    in = (in << sign_bits);

    /* calculation of index for initial approximated Val */
    index = (uint32_t) (in >> 24);
    index = (index & INDEX_MASK);

    /* 1.31 with exp 1 */
    out = p_recip_table[index];

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (uint32_t i = 0U; i < 2U; i++)
    {
        R_MACL->MUL32S = (uint32_t) in;
        R_MACL->MULB3  = (uint32_t) out;
        r_macl_wait_operation();
        temp_val = R_MACL->MULR3.MULRH;

        /* Disable fixed point mode. */
        R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;
        temp_val     = BSP_MACL_Q31_MAX_VALUE - temp_val;

        /*      1.31 with exp 1 */
        /* out = (q31_t) (((q63_t) out * temp_val) >> 30); */
        R_MACL->MUL32S = (uint32_t) out;
        R_MACL->MULB3  = temp_val;
        r_macl_wait_operation();
        reg_val = *p_result_r3;
        out     = clip_q63_to_q31(((q63_t) reg_val) >> 30);
    }

    /* write output */
    *dst = out;

    /* return num of sign_bits of out = 1/in value */
    return sign_bits + 1U;
}

 #endif
#endif

/******************************************************************************************************************//**
 * @} (end addtogroup BSP_MACL)
 **********************************************************************************************************************/
