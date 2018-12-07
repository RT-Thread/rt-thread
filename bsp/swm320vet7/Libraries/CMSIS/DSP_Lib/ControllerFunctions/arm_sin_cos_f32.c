/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2014 ARM Limited. All rights reserved.    
*    
* $Date:        19. March 2015
* $Revision: 	V.1.4.5
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_sin_cos_f32.c    
*    
* Description:	Sine and Cosine calculation for floating-point values.   
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
 * @ingroup groupController    
 */

/**    
 * @defgroup SinCos Sine Cosine   
 *    
 * Computes the trigonometric sine and cosine values using a combination of table lookup   
 * and linear interpolation.     
 * There are separate functions for Q31 and floating-point data types.   
 * The input to the floating-point version is in degrees while the   
 * fixed-point Q31 have a scaled input with the range   
 * [-1 0.9999] mapping to [-180 +180] degrees.   
 *
 * The floating point function also allows values that are out of the usual range. When this happens, the function will
 * take extra time to adjust the input value to the range of [-180 180].
 *   
 * The implementation is based on table lookup using 360 values together with linear interpolation.   
 * The steps used are:   
 *  -# Calculation of the nearest integer table index.   
 *  -# Compute the fractional portion (fract) of the input.   
 *  -# Fetch the value corresponding to \c index from sine table to \c y0 and also value from \c index+1 to \c y1.      
 *  -# Sine value is computed as <code> *psinVal = y0 + (fract * (y1 - y0))</code>.    
 *  -# Fetch the value corresponding to \c index from cosine table to \c y0 and also value from \c index+1 to \c y1.      
 *  -# Cosine value is computed as <code> *pcosVal = y0 + (fract * (y1 - y0))</code>.    
 */

 /**    
 * @addtogroup SinCos    
 * @{    
 */

/**    
 * @brief  Floating-point sin_cos function.   
 * @param[in]  theta    input value in degrees    
 * @param[out] *pSinVal points to the processed sine output.    
 * @param[out] *pCosVal points to the processed cos output.    
 * @return none.   
 */

void arm_sin_cos_f32(
  float32_t theta,
  float32_t * pSinVal,
  float32_t * pCosVal)
{
  float32_t fract, in;                             /* Temporary variables for input, output */
  uint16_t indexS, indexC;                         /* Index variable */
  float32_t f1, f2, d1, d2;                        /* Two nearest output values */
  int32_t n;
  float32_t findex, Dn, Df, temp;

  /* input x is in degrees */
  /* Scale the input, divide input by 360, for cosine add 0.25 (pi/2) to read sine table */
  in = theta * 0.00277777777778f;

  /* Calculation of floor value of input */
  n = (int32_t) in;

  /* Make negative values towards -infinity */
  if(in < 0.0f)
  {
    n--;
  }
  /* Map input value to [0 1] */
  in = in - (float32_t) n;

  /* Calculation of index of the table */
  findex = (float32_t) FAST_MATH_TABLE_SIZE * in;
  indexS = ((uint16_t)findex) & 0x1ff;
  indexC = (indexS + (FAST_MATH_TABLE_SIZE / 4)) & 0x1ff;

  /* fractional value calculation */
  fract = findex - (float32_t) indexS;

  /* Read two nearest values of input value from the cos & sin tables */
  f1 = sinTable_f32[indexC+0];
  f2 = sinTable_f32[indexC+1];
  d1 = -sinTable_f32[indexS+0];
  d2 = -sinTable_f32[indexS+1];

  Dn = 0.0122718463030f; // delta between the two points (fixed), in this case 2*pi/FAST_MATH_TABLE_SIZE
  Df = f2 - f1; // delta between the values of the functions
  temp = Dn*(d1 + d2) - 2*Df;
  temp = fract*temp + (3*Df - (d2 + 2*d1)*Dn);
  temp = fract*temp + d1*Dn;

  /* Calculation of cosine value */
  *pCosVal = fract*temp + f1;
  
  /* Read two nearest values of input value from the cos & sin tables */
  f1 = sinTable_f32[indexS+0];
  f2 = sinTable_f32[indexS+1];
  d1 = sinTable_f32[indexC+0];
  d2 = sinTable_f32[indexC+1];

  Df = f2 - f1; // delta between the values of the functions
  temp = Dn*(d1 + d2) - 2*Df;
  temp = fract*temp + (3*Df - (d2 + 2*d1)*Dn);
  temp = fract*temp + d1*Dn;
  
  /* Calculation of sine value */
  *pSinVal = fract*temp + f1;
}
/**    
 * @} end of SinCos group    
 */
