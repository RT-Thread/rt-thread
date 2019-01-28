/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2014 ARM Limited. All rights reserved.    
*    
* $Date:        19. March 2015
* $Revision: 	V.1.4.5
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_sin_f32.c    
*    
* Description:	Fast sine calculation for floating-point values.   
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
#include "arm_common_tables.h"

/**    
 * @ingroup groupFastMath    
 */

/**    
 * @defgroup sin Sine    
 *    
 * Computes the trigonometric sine function using a combination of table lookup   
 * and cubic interpolation.  There are separate functions for   
 * Q15, Q31, and floating-point data types.   
 * The input to the floating-point version is in radians while the   
 * fixed-point Q15 and Q31 have a scaled input with the range   
 * [0 +0.9999] mapping to [0 2*pi).  The fixed-point range is chosen so that a
 * value of 2*pi wraps around to 0.
 *   
 * The implementation is based on table lookup using 256 values together with cubic interpolation.   
 * The steps used are:   
 *  -# Calculation of the nearest integer table index   
 *  -# Fetch the four table values a, b, c, and d     
 *  -# Compute the fractional portion (fract) of the table index.   
 *  -# Calculation of wa, wb, wc, wd    
 *  -# The final result equals <code>a*wa + b*wb + c*wc + d*wd</code>   
 *   
 * where   
 * <pre>    
 *    a=Table[index-1];    
 *    b=Table[index+0];    
 *    c=Table[index+1];    
 *    d=Table[index+2];    
 * </pre>   
 * and   
 * <pre>    
 *    wa=-(1/6)*fract.^3 + (1/2)*fract.^2 - (1/3)*fract;    
 *    wb=(1/2)*fract.^3 - fract.^2 - (1/2)*fract + 1;    
 *    wc=-(1/2)*fract.^3+(1/2)*fract.^2+fract;    
 *    wd=(1/6)*fract.^3 - (1/6)*fract;    
 * </pre>    
 */

/**    
 * @addtogroup sin    
 * @{    
 */

/**   
 * @brief  Fast approximation to the trigonometric sine function for floating-point data.   
 * @param[in] x input value in radians.   
 * @return  sin(x).   
 */

float32_t arm_sin_f32(
  float32_t x)
{
  float32_t sinVal, fract, in;                           /* Temporary variables for input, output */
  uint16_t index;                                        /* Index variable */
  float32_t a, b;                                        /* Two nearest output values */
  int32_t n;
  float32_t findex;

  /* input x is in radians */
  /* Scale the input to [0 1] range from [0 2*PI] , divide input by 2*pi */
  in = x * 0.159154943092f;

  /* Calculation of floor value of input */
  n = (int32_t) in;

  /* Make negative values towards -infinity */
  if(x < 0.0f)
  {
    n--;
  }

  /* Map input value to [0 1] */
  in = in - (float32_t) n;

  /* Calculation of index of the table */
  findex = (float32_t) FAST_MATH_TABLE_SIZE * in;
  index = ((uint16_t)findex) & 0x1ff;

  /* fractional value calculation */
  fract = findex - (float32_t) index;

  /* Read two nearest values of input value from the sin table */
  a = sinTable_f32[index];
  b = sinTable_f32[index+1];

  /* Linear interpolation process */
  sinVal = (1.0f-fract)*a + fract*b;

  /* Return the output value */
  return (sinVal);
}

/**    
 * @} end of sin group    
 */
