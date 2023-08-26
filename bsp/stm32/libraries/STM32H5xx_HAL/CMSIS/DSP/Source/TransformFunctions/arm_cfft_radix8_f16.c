/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cfft_radix8_f16.c
 * Description:  Radix-8 Decimation in Frequency CFFT & CIFFT Floating point processing function
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

#include "dsp/transform_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)


/* ----------------------------------------------------------------------
 * Internal helper function used by the FFTs
 * -------------------------------------------------------------------- */

/**
  brief         Core function for the floating-point CFFT butterfly process.
  param[in,out] pSrc             points to the in-place buffer of floating-point data type.
  param[in]     fftLen           length of the FFT.
  param[in]     pCoef            points to the twiddle coefficient buffer.
  param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.
  return        none
*/

void arm_radix8_butterfly_f16(
  float16_t * pSrc,
  uint16_t fftLen,
  const float16_t * pCoef,
  uint16_t twidCoefModifier)
{
   uint32_t ia1, ia2, ia3, ia4, ia5, ia6, ia7;
   uint32_t i1, i2, i3, i4, i5, i6, i7, i8;
   uint32_t id;
   uint32_t n1, n2, j;

   float16_t r1, r2, r3, r4, r5, r6, r7, r8;
   float16_t t1, t2;
   float16_t s1, s2, s3, s4, s5, s6, s7, s8;
   float16_t p1, p2, p3, p4;
   float16_t co2, co3, co4, co5, co6, co7, co8;
   float16_t si2, si3, si4, si5, si6, si7, si8;
   const float16_t C81 = 0.70710678118f16;

   n2 = fftLen;

   do
   {
      n1 = n2;
      n2 = n2 >> 3;
      i1 = 0;

      do
      {
         i2 = i1 + n2;
         i3 = i2 + n2;
         i4 = i3 + n2;
         i5 = i4 + n2;
         i6 = i5 + n2;
         i7 = i6 + n2;
         i8 = i7 + n2;
         r1 = (_Float16)pSrc[2 * i1] + (_Float16)pSrc[2 * i5];
         r5 = (_Float16)pSrc[2 * i1] - (_Float16)pSrc[2 * i5];
         r2 = (_Float16)pSrc[2 * i2] + (_Float16)pSrc[2 * i6];
         r6 = (_Float16)pSrc[2 * i2] - (_Float16)pSrc[2 * i6];
         r3 = (_Float16)pSrc[2 * i3] + (_Float16)pSrc[2 * i7];
         r7 = (_Float16)pSrc[2 * i3] - (_Float16)pSrc[2 * i7];
         r4 = (_Float16)pSrc[2 * i4] + (_Float16)pSrc[2 * i8];
         r8 = (_Float16)pSrc[2 * i4] - (_Float16)pSrc[2 * i8];
         t1 = (_Float16)r1 - (_Float16)r3;
         r1 = (_Float16)r1 + (_Float16)r3;
         r3 = (_Float16)r2 - (_Float16)r4;
         r2 = (_Float16)r2 + (_Float16)r4;
         pSrc[2 * i1] = (_Float16)r1 + (_Float16)r2;
         pSrc[2 * i5] = (_Float16)r1 - (_Float16)r2;
         r1 = (_Float16)pSrc[2 * i1 + 1] + (_Float16)pSrc[2 * i5 + 1];
         s5 = (_Float16)pSrc[2 * i1 + 1] - (_Float16)pSrc[2 * i5 + 1];
         r2 = (_Float16)pSrc[2 * i2 + 1] + (_Float16)pSrc[2 * i6 + 1];
         s6 = (_Float16)pSrc[2 * i2 + 1] - (_Float16)pSrc[2 * i6 + 1];
         s3 = (_Float16)pSrc[2 * i3 + 1] + (_Float16)pSrc[2 * i7 + 1];
         s7 = (_Float16)pSrc[2 * i3 + 1] - (_Float16)pSrc[2 * i7 + 1];
         r4 = (_Float16)pSrc[2 * i4 + 1] + (_Float16)pSrc[2 * i8 + 1];
         s8 = (_Float16)pSrc[2 * i4 + 1] - (_Float16)pSrc[2 * i8 + 1];
         t2 = (_Float16)r1 - (_Float16)s3;
         r1 = (_Float16)r1 + (_Float16)s3;
         s3 = (_Float16)r2 - (_Float16)r4;
         r2 = (_Float16)r2 + (_Float16)r4;
         pSrc[2 * i1 + 1] = (_Float16)r1 + (_Float16)r2;
         pSrc[2 * i5 + 1] = (_Float16)r1 - (_Float16)r2;
         pSrc[2 * i3]     = (_Float16)t1 + (_Float16)s3;
         pSrc[2 * i7]     = (_Float16)t1 - (_Float16)s3;
         pSrc[2 * i3 + 1] = (_Float16)t2 - (_Float16)r3;
         pSrc[2 * i7 + 1] = (_Float16)t2 + (_Float16)r3;
         r1 = ((_Float16)r6 - (_Float16)r8) * (_Float16)C81;
         r6 = ((_Float16)r6 + (_Float16)r8) * (_Float16)C81;
         r2 = ((_Float16)s6 - (_Float16)s8) * (_Float16)C81;
         s6 = ((_Float16)s6 + (_Float16)s8) * (_Float16)C81;
         t1 = (_Float16)r5 - (_Float16)r1;
         r5 = (_Float16)r5 + (_Float16)r1;
         r8 = (_Float16)r7 - (_Float16)r6;
         r7 = (_Float16)r7 + (_Float16)r6;
         t2 = (_Float16)s5 - (_Float16)r2;
         s5 = (_Float16)s5 + (_Float16)r2;
         s8 = (_Float16)s7 - (_Float16)s6;
         s7 = (_Float16)s7 + (_Float16)s6;
         pSrc[2 * i2]     = (_Float16)r5 + (_Float16)s7;
         pSrc[2 * i8]     = (_Float16)r5 - (_Float16)s7;
         pSrc[2 * i6]     = (_Float16)t1 + (_Float16)s8;
         pSrc[2 * i4]     = (_Float16)t1 - (_Float16)s8;
         pSrc[2 * i2 + 1] = (_Float16)s5 - (_Float16)r7;
         pSrc[2 * i8 + 1] = (_Float16)s5 + (_Float16)r7;
         pSrc[2 * i6 + 1] = (_Float16)t2 - (_Float16)r8;
         pSrc[2 * i4 + 1] = (_Float16)t2 + (_Float16)r8;

         i1 += n1;
      } while (i1 < fftLen);

      if (n2 < 8)
         break;

      ia1 = 0;
      j = 1;

      do
      {
         /*  index calculation for the coefficients */
         id  = ia1 + twidCoefModifier;
         ia1 = id;
         ia2 = ia1 + id;
         ia3 = ia2 + id;
         ia4 = ia3 + id;
         ia5 = ia4 + id;
         ia6 = ia5 + id;
         ia7 = ia6 + id;

         co2 = pCoef[2 * ia1];
         co3 = pCoef[2 * ia2];
         co4 = pCoef[2 * ia3];
         co5 = pCoef[2 * ia4];
         co6 = pCoef[2 * ia5];
         co7 = pCoef[2 * ia6];
         co8 = pCoef[2 * ia7];
         si2 = pCoef[2 * ia1 + 1];
         si3 = pCoef[2 * ia2 + 1];
         si4 = pCoef[2 * ia3 + 1];
         si5 = pCoef[2 * ia4 + 1];
         si6 = pCoef[2 * ia5 + 1];
         si7 = pCoef[2 * ia6 + 1];
         si8 = pCoef[2 * ia7 + 1];

         i1 = j;

         do
         {
            /*  index calculation for the input */
            i2 = i1 + n2;
            i3 = i2 + n2;
            i4 = i3 + n2;
            i5 = i4 + n2;
            i6 = i5 + n2;
            i7 = i6 + n2;
            i8 = i7 + n2;
            r1 = (_Float16)pSrc[2 * i1] + (_Float16)pSrc[2 * i5];
            r5 = (_Float16)pSrc[2 * i1] - (_Float16)pSrc[2 * i5];
            r2 = (_Float16)pSrc[2 * i2] + (_Float16)pSrc[2 * i6];
            r6 = (_Float16)pSrc[2 * i2] - (_Float16)pSrc[2 * i6];
            r3 = (_Float16)pSrc[2 * i3] + (_Float16)pSrc[2 * i7];
            r7 = (_Float16)pSrc[2 * i3] - (_Float16)pSrc[2 * i7];
            r4 = (_Float16)pSrc[2 * i4] + (_Float16)pSrc[2 * i8];
            r8 = (_Float16)pSrc[2 * i4] - (_Float16)pSrc[2 * i8];
            t1 = (_Float16)r1 - (_Float16)r3;
            r1 = (_Float16)r1 + (_Float16)r3;
            r3 = (_Float16)r2 - (_Float16)r4;
            r2 = (_Float16)r2 + (_Float16)r4;
            pSrc[2 * i1] = (_Float16)r1 + (_Float16)r2;
            r2 = (_Float16)r1 - (_Float16)r2;
            s1 = (_Float16)pSrc[2 * i1 + 1] + (_Float16)pSrc[2 * i5 + 1];
            s5 = (_Float16)pSrc[2 * i1 + 1] - (_Float16)pSrc[2 * i5 + 1];
            s2 = (_Float16)pSrc[2 * i2 + 1] + (_Float16)pSrc[2 * i6 + 1];
            s6 = (_Float16)pSrc[2 * i2 + 1] - (_Float16)pSrc[2 * i6 + 1];
            s3 = (_Float16)pSrc[2 * i3 + 1] + (_Float16)pSrc[2 * i7 + 1];
            s7 = (_Float16)pSrc[2 * i3 + 1] - (_Float16)pSrc[2 * i7 + 1];
            s4 = (_Float16)pSrc[2 * i4 + 1] + (_Float16)pSrc[2 * i8 + 1];
            s8 = (_Float16)pSrc[2 * i4 + 1] - (_Float16)pSrc[2 * i8 + 1];
            t2 = (_Float16)s1 - (_Float16)s3;
            s1 = (_Float16)s1 + (_Float16)s3;
            s3 = (_Float16)s2 - (_Float16)s4;
            s2 = (_Float16)s2 + (_Float16)s4;
            r1 = (_Float16)t1 + (_Float16)s3;
            t1 = (_Float16)t1 - (_Float16)s3;
            pSrc[2 * i1 + 1] = (_Float16)s1 + (_Float16)s2;
            s2 = (_Float16)s1 - (_Float16)s2;
            s1 = (_Float16)t2 - (_Float16)r3;
            t2 = (_Float16)t2 + (_Float16)r3;
            p1 = (_Float16)co5 * (_Float16)r2;
            p2 = (_Float16)si5 * (_Float16)s2;
            p3 = (_Float16)co5 * (_Float16)s2;
            p4 = (_Float16)si5 * (_Float16)r2;
            pSrc[2 * i5]     = (_Float16)p1 + (_Float16)p2;
            pSrc[2 * i5 + 1] = (_Float16)p3 - (_Float16)p4;
            p1 = (_Float16)co3 * (_Float16)r1;
            p2 = (_Float16)si3 * (_Float16)s1;
            p3 = (_Float16)co3 * (_Float16)s1;
            p4 = (_Float16)si3 * (_Float16)r1;
            pSrc[2 * i3]     = (_Float16)p1 + (_Float16)p2;
            pSrc[2 * i3 + 1] = (_Float16)p3 - (_Float16)p4;
            p1 = (_Float16)co7 * (_Float16)t1;
            p2 = (_Float16)si7 * (_Float16)t2;
            p3 = (_Float16)co7 * (_Float16)t2;
            p4 = (_Float16)si7 * (_Float16)t1;
            pSrc[2 * i7]     = (_Float16)p1 + (_Float16)p2;
            pSrc[2 * i7 + 1] = (_Float16)p3 - (_Float16)p4;
            r1 = ((_Float16)r6 - (_Float16)r8) * (_Float16)C81;
            r6 = ((_Float16)r6 + (_Float16)r8) * (_Float16)C81;
            s1 = ((_Float16)s6 - (_Float16)s8) * (_Float16)C81;
            s6 = ((_Float16)s6 + (_Float16)s8) * (_Float16)C81;
            t1 = (_Float16)r5 - (_Float16)r1;
            r5 = (_Float16)r5 + (_Float16)r1;
            r8 = (_Float16)r7 - (_Float16)r6;
            r7 = (_Float16)r7 + (_Float16)r6;
            t2 = (_Float16)s5 - (_Float16)s1;
            s5 = (_Float16)s5 + (_Float16)s1;
            s8 = (_Float16)s7 - (_Float16)s6;
            s7 = (_Float16)s7 + (_Float16)s6;
            r1 = (_Float16)r5 + (_Float16)s7;
            r5 = (_Float16)r5 - (_Float16)s7;
            r6 = (_Float16)t1 + (_Float16)s8;
            t1 = (_Float16)t1 - (_Float16)s8;
            s1 = (_Float16)s5 - (_Float16)r7;
            s5 = (_Float16)s5 + (_Float16)r7;
            s6 = (_Float16)t2 - (_Float16)r8;
            t2 = (_Float16)t2 + (_Float16)r8;
            p1 = (_Float16)co2 * (_Float16)r1;
            p2 = (_Float16)si2 * (_Float16)s1;
            p3 = (_Float16)co2 * (_Float16)s1;
            p4 = (_Float16)si2 * (_Float16)r1;
            pSrc[2 * i2]     = (_Float16)p1 + (_Float16)p2;
            pSrc[2 * i2 + 1] = (_Float16)p3 - (_Float16)p4;
            p1 = (_Float16)co8 * (_Float16)r5;
            p2 = (_Float16)si8 * (_Float16)s5;
            p3 = (_Float16)co8 * (_Float16)s5;
            p4 = (_Float16)si8 * (_Float16)r5;
            pSrc[2 * i8]     = (_Float16)p1 + (_Float16)p2;
            pSrc[2 * i8 + 1] = (_Float16)p3 - (_Float16)p4;
            p1 = (_Float16)co6 * (_Float16)r6;
            p2 = (_Float16)si6 * (_Float16)s6;
            p3 = (_Float16)co6 * (_Float16)s6;
            p4 = (_Float16)si6 * (_Float16)r6;
            pSrc[2 * i6]     = (_Float16)p1 + (_Float16)p2;
            pSrc[2 * i6 + 1] = (_Float16)p3 - (_Float16)p4;
            p1 = (_Float16)co4 * (_Float16)t1;
            p2 = (_Float16)si4 * (_Float16)t2;
            p3 = (_Float16)co4 * (_Float16)t2;
            p4 = (_Float16)si4 * (_Float16)t1;
            pSrc[2 * i4]     = (_Float16)p1 + (_Float16)p2;
            pSrc[2 * i4 + 1] = (_Float16)p3 - (_Float16)p4;

            i1 += n1;
         } while (i1 < fftLen);

         j++;
      } while (j < n2);

      twidCoefModifier <<= 3;
   } while (n2 > 7);
}

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
