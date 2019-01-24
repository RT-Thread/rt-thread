/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2014 ARM Limited. All rights reserved.    
*    
* $Date:        19. March 2015
* $Revision: 	V.1.4.5  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_std_q31.c    
*    
* Description:	Standard deviation of an array of Q31 type.    
*    
* Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
*  
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the 
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.    
* -------------------------------------------------------------------- */

#include "arm_math.h"

/**    
 * @ingroup groupStats    
 */

/**    
 * @addtogroup STD    
 * @{    
 */


/**    
 * @brief Standard deviation of the elements of a Q31 vector.    
 * @param[in]       *pSrc points to the input vector    
 * @param[in]       blockSize length of the input vector    
 * @param[out]      *pResult standard deviation value returned here    
 * @return none.    
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 *    
 *\par    
 * The function is implemented using an internal 64-bit accumulator.        
 * The input is represented in 1.31 format, which is then downshifted by 8 bits
 * which yields 1.23, and intermediate multiplication yields a 2.46 format.        
 * The accumulator maintains full precision of the intermediate multiplication results,         
 * but provides only a 16 guard bits.        
 * There is no saturation on intermediate additions.        
 * If the accumulator overflows it wraps around and distorts the result.        
 * In order to avoid overflows completely the input signal must be scaled down by         
 * log2(blockSize)-8 bits, as a total of blockSize additions are performed internally.  
 * After division, internal variables should be Q18.46 
 * Finally, the 18.46 accumulator is right shifted by 15 bits to yield a 1.31 format value. 
 *    
 */


void arm_std_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult)
{
  q63_t sum = 0;                                 /* Accumulator */
  q63_t meanOfSquares, squareOfMean;             /* square of mean and mean of square */
  q31_t in;                                      /* input value */
  uint32_t blkCnt;                               /* loop counter */
  q63_t sumOfSquares = 0;                        /* Accumulator */

	if(blockSize == 1)
	{
		*pResult = 0;
		return;
	}
   
#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1])  */
    /* Compute Sum of squares of the input samples    
     * and then store the result in a temporary variable, sum. */
    in = *pSrc++ >> 8;
    sum += in;
    sumOfSquares += ((q63_t) (in) * (in));
    in = *pSrc++ >> 8;
    sum += in;
    sumOfSquares += ((q63_t) (in) * (in));
    in = *pSrc++ >> 8;
    sum += in;
    sumOfSquares += ((q63_t) (in) * (in));
    in = *pSrc++ >> 8;
    sum += in;
    sumOfSquares += ((q63_t) (in) * (in));

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
    /* Compute Sum of squares of the input samples    
     * and then store the result in a temporary variable, sum. */
    in = *pSrc++ >> 8;
    sum += in;
    sumOfSquares += ((q63_t) (in) * (in));

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Compute Mean of squares of the input samples    
   * and then store the result in a temporary variable, meanOfSquares. */
  meanOfSquares = sumOfSquares / (q63_t)(blockSize - 1);

#else

  /* Run the below code for Cortex-M0 */

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
    /* Compute Sum of squares of the input samples     
     * and then store the result in a temporary variable, sumOfSquares. */
    in = *pSrc++ >> 8;
    sumOfSquares += ((q63_t) (in) * (in));

    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    /* Compute sum of all input values and then store the result in a temporary variable, sum. */
    sum += in;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Compute Mean of squares of the input samples     
   * and then store the result in a temporary variable, meanOfSquares. */
  meanOfSquares = sumOfSquares / (q63_t)(blockSize - 1);

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  /* Compute square of mean */
  squareOfMean = sum * sum / (q63_t)(blockSize * (blockSize - 1u));

  /* Compute standard deviation and then store the result to the destination */
  arm_sqrt_q31((meanOfSquares - squareOfMean) >> 15, pResult);

}

/**    
 * @} end of STD group    
 */
