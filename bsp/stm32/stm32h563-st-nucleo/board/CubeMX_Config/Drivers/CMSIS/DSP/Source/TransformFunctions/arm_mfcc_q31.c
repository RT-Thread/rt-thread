/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mfcc_q31.c
 * Description:  MFCC function for the q31 version
 *
 * $Date:        07 September 2021
 * $Revision:    V1.10.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include "dsp/transform_functions.h"
#include "dsp/statistics_functions.h"
#include "dsp/basic_math_functions.h"
#include "dsp/complex_math_functions.h"
#include "dsp/fast_math_functions.h"
#include "dsp/matrix_functions.h"

/* Constants for Q31 implementation */
#define LOG2TOLOG_Q31 0x02C5C860
#define MICRO_Q31 0x08637BD0
#define SHIFT_MELFILTER_SATURATION_Q31 10
/**
  @ingroup groupTransforms
 */


/**
  @defgroup MFCC MFCC

  MFCC Transform

  There are separate functions for floating-point, Q31, and Q31 data types.
 */



/**
  @addtogroup MFCC
  @{
 */

/**
  @brief         MFCC Q31
  @param[in]    S       points to the mfcc instance structure
  @param[in]     pSrc points to the input samples in Q31
  @param[out]     pDst  points to the output MFCC values in q8.23 format
  @param[inout]     pTmp  points to a temporary buffer of complex

  @return        none

  @par           Description
                   The number of input samples is the FFT length used
                   when initializing the instance data structure.

                   The temporary buffer has a 2*fft length.

                   The source buffer is modified by this function.

                   The function may saturate. If the FFT length is too
                   big and the number of MEL filters too small then the fixed
                   point computations may saturate.

 */


arm_status arm_mfcc_q31(
  const arm_mfcc_instance_q31 * S,
  q31_t *pSrc,
  q31_t *pDst,
  q31_t *pTmp
  )
{
    q31_t m;
    uint32_t index;
    uint32_t fftShift=0;
    q31_t logExponent;
    q63_t result;
    arm_matrix_instance_q31 pDctMat;
    uint32_t i;
    uint32_t coefsPos;
    uint32_t filterLimit;
    q31_t *pTmp2=(q31_t*)pTmp;

    arm_status status = ARM_MATH_SUCCESS;
    
    // q31
    arm_absmax_q31(pSrc,S->fftLen,&m,&index);

    if (m !=0)
    {
       q31_t quotient;
       int16_t shift;

       status = arm_divide_q31(0x7FFFFFFF,m,&quotient,&shift);
       if (status != ARM_MATH_SUCCESS)
       {
          return(status);
       }
 
       arm_scale_q31(pSrc,quotient,shift,pSrc,S->fftLen);
    }


    // q31
    arm_mult_q31(pSrc,S->windowCoefs, pSrc, S->fftLen);


    /* Compute spectrum magnitude 
    */
    fftShift = 31 - __CLZ(S->fftLen);
#if defined(ARM_MFCC_CFFT_BASED)
    /* some HW accelerator for CMSIS-DSP used in some boards
       are only providing acceleration for CFFT.
       With ARM_MFCC_CFFT_BASED enabled, CFFT is used and the MFCC
       will be accelerated on those boards.
 
       The default is to use RFFT
    */
    /* Convert from real to complex */
    for(i=0; i < S->fftLen ; i++)
    {
      pTmp2[2*i] = pSrc[i];
      pTmp2[2*i+1] = 0;
    }
    arm_cfft_q31(&(S->cfft),pTmp2,0,1);
#else
    /* Default RFFT based implementation */
    arm_rfft_q31(&(S->rfft),pSrc,pTmp2);
#endif
    filterLimit = 1 + (S->fftLen >> 1);


    // q31 - fftShift
    arm_cmplx_mag_q31(pTmp2,pSrc,filterLimit);
    // q30 - fftShift


    /* Apply MEL filters */
    coefsPos = 0;
    for(i=0; i<S->nbMelFilters; i++)
    {
      arm_dot_prod_q31(pSrc+S->filterPos[i],
        &(S->filterCoefs[coefsPos]),
        S->filterLengths[i],
        &result);

      coefsPos += S->filterLengths[i];

      // q16.48 - fftShift
      result += MICRO_Q31;
      result >>= (SHIFT_MELFILTER_SATURATION_Q31 + 18);
      // q16.29 - fftShift - satShift
      pTmp[i] = __SSAT(result,31) ;

    }


    // q16.29 - fftShift - satShift
    /* Compute the log */
    arm_vlog_q31(pTmp,pTmp,S->nbMelFilters);


    // q5.26
   
    logExponent = fftShift + 2 + SHIFT_MELFILTER_SATURATION_Q31;
    logExponent = logExponent * LOG2TOLOG_Q31;


    // q5.26
    arm_offset_q31(pTmp,logExponent,pTmp,S->nbMelFilters);
    arm_shift_q31(pTmp,-3,pTmp,S->nbMelFilters);

    
    // q8.23

    pDctMat.numRows=S->nbDctOutputs;
    pDctMat.numCols=S->nbMelFilters;
    pDctMat.pData=(q31_t*)S->dctCoefs;

    arm_mat_vec_mult_q31(&pDctMat, pTmp, pDst);

    return(status);
}

/**
  @} end of MFCC group
 */
