/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_fir_decimate_q15.c
 * Description:  Q15 FIR Decimator
 *
 * $Date:        23 April 2021
 * $Revision:    V1.9.0
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

#include "dsp/filtering_functions.h"

/**
  @ingroup groupFilters
 */

/**
  @addtogroup FIR_decimate
  @{
 */

/**
  @brief         Processing function for the Q15 FIR decimator.
  @param[in]     S          points to an instance of the Q15 FIR decimator structure
  @param[in]     pSrc       points to the block of input data
  @param[out]    pDst       points to the block of output data
  @param[in]     blockSize  number of input samples to process per call
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using a 64-bit internal accumulator.
                   Both coefficients and state variables are represented in 1.15 format and multiplications yield a 2.30 result.
                   The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.
                   There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.
                   After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.
                   Lastly, the accumulator is saturated to yield a result in 1.15 format.

 @remark
                   Refer to \ref arm_fir_decimate_fast_q15() for a faster but less precise implementation of this function.
 */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_fir_decimate_q15(
  const arm_fir_decimate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize)
{
    q15_t    *pState = S->pState;   /* State pointer */
    const q15_t    *pCoeffs = S->pCoeffs; /* Coefficient pointer */
    q15_t    *pStateCurnt;      /* Points to the current sample of the state */
    const q15_t    *px, *pb;          /* Temporary pointers for state and coefficient buffers */
    uint32_t  numTaps = S->numTaps; /* Number of filter coefficients in the filter */
    uint32_t  i, tapCnt, blkCnt, outBlockSize = blockSize / S->M;   /* Loop counters */
    uint32_t  blkCntN4;
    const q15_t  *px0, *px1, *px2, *px3;
    q63_t     acc0v, acc1v, acc2v, acc3v;
    q15x8_t x0v, x1v, x2v, x3v;
    q15x8_t c0v;

    /*
     * S->pState buffer contains previous frame (numTaps - 1) samples
     * pStateCurnt points to the location where the new input data should be written
     */
    pStateCurnt = S->pState + (numTaps - 1U);
    /*
     * Total number of output samples to be computed
     */
    blkCnt = outBlockSize / 4;
    blkCntN4 = outBlockSize - (4 * blkCnt);

    while (blkCnt > 0U)
    {
        /*
         * Need extra temp variables as 4 * S->M is not necessarily a multiple of 8
         * and cause final tail predicated post incremented pointers to jump ahead
         */
        const q15_t      *pSrcTmp = pSrc;
        q15_t      *pStateCurntTmp = pStateCurnt;

        /*
         * Copy 4 * decimation factor number of new input samples into the state buffer
         */
        i = (4 * S->M) >> 3;
        while (i > 0U)
        {
            vstrhq_s16(pStateCurntTmp, vldrhq_s16(pSrcTmp));
            pSrcTmp += 8;
            pStateCurntTmp += 8;
            i--;
        }
        i = (4 * S->M) & 7;
        if (i > 0U)
        {
            mve_pred16_t p0 = vctp16q(i);
            vstrhq_p_s16(pStateCurntTmp, vldrhq_s16(pSrcTmp), p0);
        }

        pSrc += (4 * S->M);
        pStateCurnt += (4 * S->M);

        /*
         * Clear all accumulators
         */
        acc0v = 0LL;
        acc1v = 0LL;
        acc2v = 0LL;
        acc3v = 0LL;
        /*
         * Initialize state pointer for all the samples
         */
        px0 = pState;
        px1 = pState + S->M;
        px2 = pState + 2 * S->M;
        px3 = pState + 3 * S->M;
        /*
         * Initialize coeff. pointer
         */
        pb = pCoeffs;

        tapCnt = numTaps >> 3;
        /*
         * Loop over the number of taps.  Unroll by a factor of 4.
         * Repeat until we've computed numTaps-4 coefficients.
         */
        while (tapCnt > 0U)
        {
            /*
             * Read the b[numTaps-1] coefficient
             */
            c0v = vldrhq_s16(pb);
            pb += 8;
            /*
             * Read x[n-numTaps-1] sample for acc0
             */
            x0v = vld1q(px0);
            x1v = vld1q(px1);
            x2v = vld1q(px2);
            x3v = vld1q(px3);
            px0 += 8;
            px1 += 8;
            px2 += 8;
            px3 += 8;

            acc0v = vmlaldavaq(acc0v, x0v, c0v);
            acc1v = vmlaldavaq(acc1v, x1v, c0v);
            acc2v = vmlaldavaq(acc2v, x2v, c0v);
            acc3v = vmlaldavaq(acc3v, x3v, c0v);
            /*
             * Decrement the loop counter
             */
            tapCnt--;
        }

        /*
         * If the filter length is not a multiple of 4, compute the remaining filter taps
         * should be tail predicated
         */
        tapCnt = numTaps & 7;
        if (tapCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(tapCnt);
            /*
             * Read the b[numTaps-1] coefficient
             */
            c0v = vldrhq_z_s16(pb, p0);
            pb += 8;
            /*
             * Read x[n-numTaps-1] sample for acc0
             */
            x0v = vld1q(px0);
            x1v = vld1q(px1);
            x2v = vld1q(px2);
            x3v = vld1q(px3);
            px0 += 8;
            px1 += 8;
            px2 += 8;
            px3 += 8;

            acc0v = vmlaldavaq(acc0v, x0v, c0v);
            acc1v = vmlaldavaq(acc1v, x1v, c0v);
            acc2v = vmlaldavaq(acc2v, x2v, c0v);
            acc3v = vmlaldavaq(acc3v, x3v, c0v);
        }

        acc0v = asrl(acc0v, 15);
        acc1v = asrl(acc1v, 15);
        acc2v = asrl(acc2v, 15);
        acc3v = asrl(acc3v, 15);
        /*
         * store in the destination buffer.
         */
        *pDst++ = (q15_t) __SSAT((q31_t) acc0v, 16);
        *pDst++ = (q15_t) __SSAT((q31_t) acc1v, 16);;
        *pDst++ = (q15_t) __SSAT((q31_t) acc2v, 16);;
        *pDst++ = (q15_t) __SSAT((q31_t) acc3v, 16);;

        /*
         * Advance the state pointer by the decimation factor
         * to process the next group of decimation factor number samples
         */
        pState = pState + 4 * S->M;
        /*
         * Decrement the loop counter
         */
        blkCnt--;
    }

    while (blkCntN4 > 0U)
    {
        /*
         * Copy decimation factor number of new input samples into the state buffer
         */
        i = S->M;
        do
        {
            *pStateCurnt++ = *pSrc++;
        }
        while (--i);
        /*
         * Set accumulator to zero
         */
        acc0v = 0LL;
        /*
         * Initialize state pointer
         */
        px = pState;
        /*
         * Initialize coeff. pointer
         */
        pb = pCoeffs;

        tapCnt = numTaps >> 3;
        while (tapCnt > 0U)
        {
            c0v = vldrhq_s16(pb);
            x0v = vldrhq_s16(px);
            pb += 8;
            px += 8;
            acc0v = vmlaldavaq(acc0v, x0v, c0v);
            /*
             * Decrement the loop counter
             */
            tapCnt--;
        }

        tapCnt = numTaps & 7;
        if (tapCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(tapCnt);
            c0v = vldrhq_z_s16(pb, p0);
            x0v = vldrhq_z_s16(px, p0);
            acc0v = vmlaldavaq_p(acc0v, x0v, c0v, p0);
        }

        acc0v = asrl(acc0v, 15);

        /*
         * Advance the state pointer by the decimation factor
         * to process the next group of decimation factor number samples
         */
        pState = pState + S->M;
        /*
         * The result is in the accumulator, store in the destination buffer.
         */
        *pDst++ = (q15_t) __SSAT((q31_t) acc0v, 16);
        /*
         * Decrement the loop counter
         */
        blkCntN4--;
    }

    /*
     * Processing is complete.
     * Now copy the last numTaps - 1 samples to the start of the state buffer.
     * This prepares the state buffer for the next function call.
     */

    pStateCurnt = S->pState;
    blkCnt = (numTaps - 1) >> 3;
    while (blkCnt > 0U)
    {
        vstrhq_s16(pStateCurnt, vldrhq_s16(pState));
        pState += 8;
        pStateCurnt += 8;
        blkCnt--;
    }
    blkCnt = (numTaps - 1) & 7;
    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp16q(blkCnt);
        vstrhq_p_s16(pStateCurnt, vldrhq_s16(pState), p0);
    }  
}
#else
#if defined (ARM_MATH_DSP)

void arm_fir_decimate_q15(
  const arm_fir_decimate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize)
{
        q15_t *pState = S->pState;                     /* State pointer */
  const q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
        q15_t *pStateCur;                              /* Points to the current sample of the state */
        q15_t *px;                                     /* Temporary pointer for state buffer */
  const q15_t *pb;                                     /* Temporary pointer for coefficient buffer */
        q31_t x0, x1, c0;                              /* Temporary variables to hold state and coefficient values */
        q63_t sum0;                                    /* Accumulators */
        q63_t acc0, acc1;
        q15_t *px0, *px1;
        uint32_t blkCntN3;
        uint32_t numTaps = S->numTaps;                 /* Number of taps */
        uint32_t i, blkCnt, tapCnt, outBlockSize = blockSize / S->M;  /* Loop counters */

#if defined (ARM_MATH_LOOPUNROLL)
        q31_t c1;                                      /* Temporary variables to hold state and coefficient values */
#endif

  /* S->pState buffer contains previous frame (numTaps - 1) samples */
  /* pStateCur points to the location where the new input data should be written */
  pStateCur = S->pState + (numTaps - 1U);

  /* Total number of output samples to be computed */
  blkCnt = outBlockSize / 2;
  blkCntN3 = outBlockSize - (2 * blkCnt);

  while (blkCnt > 0U)
  {
    /* Copy 2 * decimation factor number of new input samples into the state buffer */
    i = S->M * 2;

    do
    {
      *pStateCur++ = *pSrc++;

    } while (--i);

    /* Set accumulator to zero */
    acc0 = 0;
    acc1 = 0;

    /* Initialize state pointer for all the samples */
    px0 = pState;
    px1 = pState + S->M;

    /* Initialize coeff pointer */
    pb = pCoeffs;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time */
    tapCnt = numTaps >> 2U;

    while (tapCnt > 0U)
    {
      /* Read the b[numTaps-1] and b[numTaps-2] coefficients */
      c0 = read_q15x2_ia ((q15_t **) &pb);

      /* Read x[n-numTaps-1] and x[n-numTaps-2]sample */
      x0 = read_q15x2_ia (&px0);
      x1 = read_q15x2_ia (&px1);

      /* Perform the multiply-accumulate */
      acc0 = __SMLALD(x0, c0, acc0);
      acc1 = __SMLALD(x1, c0, acc1);

      /* Read the b[numTaps-3] and b[numTaps-4] coefficient */
      c0 = read_q15x2_ia ((q15_t **) &pb);

      /* Read x[n-numTaps-2] and x[n-numTaps-3] sample */
      x0 = read_q15x2_ia (&px0);
      x1 = read_q15x2_ia (&px1);

      /* Perform the multiply-accumulate */
      acc0 = __SMLALD(x0, c0, acc0);
      acc1 = __SMLALD(x1, c0, acc1);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of taps */
    tapCnt = numTaps;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Read coefficients */
      c0 = *pb++;

      /* Fetch state variables for acc0, acc1 */
      x0 = *px0++;
      x1 = *px1++;

      /* Perform the multiply-accumulate */
      acc0 = __SMLALD(x0, c0, acc0);
      acc1 = __SMLALD(x1, c0, acc1);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Advance the state pointer by the decimation factor
     * to process the next group of decimation factor number samples */
    pState = pState + S->M * 2;

    /* Store filter output, smlad returns the values in 2.14 format */
    /* so downsacle by 15 to get output in 1.15 */
    *pDst++ = (q15_t) (__SSAT((acc0 >> 15), 16));
    *pDst++ = (q15_t) (__SSAT((acc1 >> 15), 16));

    /* Decrement loop counter */
    blkCnt--;
  }

  while (blkCntN3 > 0U)
  {
    /* Copy decimation factor number of new input samples into the state buffer */
    i = S->M;

    do
    {
      *pStateCur++ = *pSrc++;

    } while (--i);

    /* Set accumulator to zero */
    sum0 = 0;

    /* Initialize state pointer */
    px = pState;

    /* Initialize coeff pointer */
    pb = pCoeffs;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time */
    tapCnt = numTaps >> 2U;

    while (tapCnt > 0U)
    {
      /* Read the b[numTaps-1] and b[numTaps-2] coefficients */
      c0 = read_q15x2_ia ((q15_t **) &pb);

      /* Read x[n-numTaps-1] and x[n-numTaps-2] sample */
      x0 = read_q15x2_ia (&px);

      /* Read the b[numTaps-3] and b[numTaps-4] coefficients */
      c1 = read_q15x2_ia ((q15_t **) &pb);

      /* Perform the multiply-accumulate */
      sum0 = __SMLALD(x0, c0, sum0);

      /* Read x[n-numTaps-2] and x[n-numTaps-3] sample */
      x0 = read_q15x2_ia (&px);

      /* Perform the multiply-accumulate */
      sum0 = __SMLALD(x0, c1, sum0);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of taps */
    tapCnt = numTaps;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Read coefficients */
      c0 = *pb++;

      /* Fetch 1 state variable */
      x0 = *px++;

      /* Perform the multiply-accumulate */
      sum0 = __SMLALD(x0, c0, sum0);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Advance the state pointer by the decimation factor
     * to process the next group of decimation factor number samples */
    pState = pState + S->M;

    /* Store filter output, smlad returns the values in 2.14 format */
    /* so downsacle by 15 to get output in 1.15 */
    *pDst++ = (q15_t) (__SSAT((sum0 >> 15), 16));

    /* Decrement loop counter */
    blkCntN3--;
  }

  /* Processing is complete.
     Now copy the last numTaps - 1 samples to the satrt of the state buffer.
     This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCur = S->pState;
  i = (numTaps - 1U) >> 2U;
 
  /* copy data */
  while (i > 0U)
  {
    write_q15x2_ia (&pStateCur, read_q15x2_ia (&pState));
    write_q15x2_ia (&pStateCur, read_q15x2_ia (&pState));

    /* Decrement loop counter */
    i--;
  }

  i = (numTaps - 1U) % 0x04U;

  /* Copy data */
  while (i > 0U)
  {
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    i--;
  }

}

#else /* #if defined (ARM_MATH_DSP) */

void arm_fir_decimate_q15(
  const arm_fir_decimate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize)
{
        q15_t *pState = S->pState;                     /* State pointer */
  const q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
        q15_t *pStateCur;                              /* Points to the current sample of the state */
        q15_t *px;                                     /* Temporary pointer for state buffer */
  const q15_t *pb;                                     /* Temporary pointer for coefficient buffer */
        q15_t x0, x1, c0;                              /* Temporary variables to hold state and coefficient values */
        q63_t sum0;                                    /* Accumulators */
        q63_t acc0, acc1;
        q15_t *px0, *px1;
        uint32_t blkCntN3;
        uint32_t numTaps = S->numTaps;                 /* Number of taps */
        uint32_t i, blkCnt, tapCnt, outBlockSize = blockSize / S->M;  /* Loop counters */


  /* S->pState buffer contains previous frame (numTaps - 1) samples */
  /* pStateCur points to the location where the new input data should be written */
  pStateCur = S->pState + (numTaps - 1U);

  /* Total number of output samples to be computed */
  blkCnt = outBlockSize / 2;
  blkCntN3 = outBlockSize - (2 * blkCnt);

  while (blkCnt > 0U)
  {
    /* Copy 2 * decimation factor number of new input samples into the state buffer */
    i = S->M * 2;

    do
    {
      *pStateCur++ = *pSrc++;

    } while (--i);

    /* Set accumulator to zero */
    acc0 = 0;
    acc1 = 0;

    /* Initialize state pointer */
    px0 = pState;
    px1 = pState + S->M;

    /* Initialize coeff pointer */
    pb = pCoeffs;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time */
    tapCnt = numTaps >> 2U;

    while (tapCnt > 0U)
    {
      /* Read the Read b[numTaps-1] coefficients */
      c0 = *pb++;

      /* Read x[n-numTaps-1] for sample 0 and for sample 1 */
      x0 = *px0++;
      x1 = *px1++;

      /* Perform the multiply-accumulate */
      acc0 += x0 * c0;
      acc1 += x1 * c0;

      /* Read the b[numTaps-2] coefficient */
      c0 = *pb++;

      /* Read x[n-numTaps-2] for sample 0 and sample 1 */
      x0 = *px0++;
      x1 = *px1++;

      /* Perform the multiply-accumulate */
      acc0 += x0 * c0;
      acc1 += x1 * c0;

      /* Read the b[numTaps-3] coefficients */
      c0 = *pb++;

      /* Read x[n-numTaps-3] for sample 0 and sample 1 */
      x0 = *px0++;
      x1 = *px1++;

      /* Perform the multiply-accumulate */
      acc0 += x0 * c0;
      acc1 += x1 * c0;

      /* Read the b[numTaps-4] coefficient */
      c0 = *pb++;

      /* Read x[n-numTaps-4] for sample 0 and sample 1 */
      x0 = *px0++;
      x1 = *px1++;

      /* Perform the multiply-accumulate */
      acc0 += x0 * c0;
      acc1 += x1 * c0;

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of taps */
    tapCnt = numTaps;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Read coefficients */
      c0 = *pb++;

      /* Fetch 1 state variable */
      x0 = *px0++;
      x1 = *px1++;

      /* Perform the multiply-accumulate */
      acc0 += x0 * c0;
      acc1 += x1 * c0;

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Advance the state pointer by the decimation factor
     * to process the next group of decimation factor number samples */
    pState = pState + S->M * 2;

    /* Store filter output, smlad returns the values in 2.14 format */
    /* so downsacle by 15 to get output in 1.15 */

    *pDst++ = (q15_t) (__SSAT((acc0 >> 15), 16));
    *pDst++ = (q15_t) (__SSAT((acc1 >> 15), 16));

    /* Decrement loop counter */
    blkCnt--;
  }

  while (blkCntN3 > 0U)
  {
    /* Copy decimation factor number of new input samples into the state buffer */
    i = S->M;

    do
    {
      *pStateCur++ = *pSrc++;

    } while (--i);

    /* Set accumulator to zero */
    sum0 = 0;

    /* Initialize state pointer */
    px = pState;

    /* Initialize coeff pointer */
    pb = pCoeffs;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time */
    tapCnt = numTaps >> 2U;

    while (tapCnt > 0U)
    {
      /* Read the b[numTaps-1] coefficient */
      c0 = *pb++;

      /* Read x[n-numTaps-1] sample */
      x0 = *px++;

      /* Perform the multiply-accumulate */
      sum0 += x0 * c0;

      /* Read the b[numTaps-2] coefficient */
      c0 = *pb++;

      /* Read x[n-numTaps-2] sample */
      x0 = *px++;

      /* Perform the multiply-accumulate */
      sum0 += x0 * c0;

      /* Read the b[numTaps-3] coefficient */
      c0 = *pb++;

      /* Read x[n-numTaps-3] sample */
      x0 = *px++;

      /* Perform the multiply-accumulate */
      sum0 += x0 * c0;

      /* Read the b[numTaps-4] coefficient */
      c0 = *pb++;

      /* Read x[n-numTaps-4] sample */
      x0 = *px++;

      /* Perform the multiply-accumulate */
      sum0 += x0 * c0;

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of taps */
    tapCnt = numTaps;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Read coefficients */
      c0 = *pb++;

      /* Fetch 1 state variable */
      x0 = *px++;

      /* Perform the multiply-accumulate */
      sum0 += x0 * c0;

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Advance the state pointer by the decimation factor
     * to process the next group of decimation factor number samples */
    pState = pState + S->M;

    /* Store filter output, smlad returns the values in 2.14 format */
    /* so downsacle by 15 to get output in 1.15 */
    *pDst++ = (q15_t) (__SSAT((sum0 >> 15), 16));

    /* Decrement loop counter */
    blkCntN3--;
  }

  /* Processing is complete.
   ** Now copy the last numTaps - 1 samples to the satrt of the state buffer.
   ** This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCur = S->pState;

  i = (numTaps - 1U) >> 2U;

  /* copy data */
  while (i > 0U)
  {
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    i--;
  }

  i = (numTaps - 1U) % 0x04U;

  /* copy data */
  while (i > 0U)
  {
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    i--;
  }
}

#endif /* #if defined (ARM_MATH_DSP) */
#endif /* defined(ARM_MATH_MVEI) */
/**
  @} end of FIR_decimate group
 */
