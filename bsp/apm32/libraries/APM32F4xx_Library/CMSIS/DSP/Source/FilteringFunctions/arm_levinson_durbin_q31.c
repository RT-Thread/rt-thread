/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_levinson_durbin_q31.c
 * Description:  q31 version of Levinson Durbin algorithm
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

#define ONE_Q31 0x7FFFFFFFL
#define TWO_Q30 0x7FFFFFFFL

#define HALF_Q31 0x00008000L
#define ONE_Q15 0x7FFF
#define HALF_Q15 0x3FFF
#define LOWPART_MASK 0x07FFF

__STATIC_FORCEINLINE q31_t mul32x16(q31_t a, q15_t b)
{
  q31_t r = ((q63_t)a * (q63_t)b) >> 15;

  return(r);

}

__STATIC_FORCEINLINE q31_t mul32x32(q31_t a, q31_t b)
{
  //q31_t r = __SSAT(((q63_t)a * b) >> 31,31);
  q31_t r = ((q63_t)a * b) >> 31;

  return(r);

}

__STATIC_FORCEINLINE q31_t divide(q31_t n, q31_t d)
{
  arm_status status;
  int16_t shift;
  q15_t inverse;
  q31_t r;
  // We are computing:
  // n / d = n / (h + l) where h and l are the high end and low end part.
  // 1 / (h + l) = 1 / h (1 - l / h)
  // Our division algorithm has a shift. So it is returning a scaled value sh.
  // So we need a << shift to convert 1/ sh to 1/h.
  // In below code, we are organizing the computation differently. Instead of computing:
  // 1 / h (1 - l / h)
  // we are computing
  // 1 / h (2 - (l + h) / h)
  // 1 / h (2 - d / h)
  // Also, we are not computing 1/h in Q15 but in Q14.
  // 2 is expressed in Q30.
  // So at the end of all computation we need a << 2

  // Result is in Q14 because of use of HALF_Q15 instead of ONE_Q15.
  status=arm_divide_q15(HALF_Q15,d>>16,&inverse,&shift);
  (void)status;

  // d is used instead of l
  // So we will need to substract to 2 instead of 1.
  r = mul32x16(d,inverse);
  r = TWO_Q30 - (r << shift);
  r = mul32x16(r, inverse);
  r = mul32x32(r,n) ;
  r = r << (shift + 2);

  return(r);

}

/**
  @ingroup groupFilters
 */

/**
  @defgroup LD Levinson Durbin Algorithm

 */

/**
  @addtogroup LD
  @{
 */

/**
  @brief         Levinson Durbin
  @param[in]     phi      autocovariance vector starting with lag 0 (length is nbCoefs + 1)
  @param[out]    a        autoregressive coefficients
  @param[out]    err      prediction error (variance)
  @param[in]     nbCoefs  number of autoregressive coefficients
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) && defined(__CMSIS_GCC_H)
#pragma GCC warning "Scalar version of arm_levinson_durbin_q31 built. Helium version has build issues with gcc."
#endif

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE) &&  !defined(__CMSIS_GCC_H)

#define LANE23_MASK 0xFF00

#include "arm_helium_utils.h"
void arm_levinson_durbin_q31(const q31_t *phi,
  q31_t *a,
  q31_t *err,
  int nbCoefs)
{
    q31_t e;

    static const uint32_t revOffsetArray[4] = {3,2,1,0};

   //a[0] = phi[1] / phi[0];
   a[0] = divide(phi[1], phi[0]);


   //e = phi[0] - phi[1] * a[0];
   e = phi[0] - mul32x32(phi[1],a[0]);

   for(int p=1; p < nbCoefs; p++)
   {
      q63_t suma=0;
      q63_t sumb=0;
      q31x4_t vecA,vecRevPhi,vecPhi;
      q31_t k;
      uint32_t blkCnt;
      const q31_t *pPhi,*pRevPhi,*pA;
      uint32x4_t revOffset;


      int nb,j,i;

      revOffset = vld1q(revOffsetArray);

      pRevPhi = &phi[p-3];
      pPhi = &phi[1];
      pA = a;

      i = 0;
      blkCnt = p >> 2;
      while(blkCnt > 0)
      {
         vecA = vld1q(pA);
         pA += 4;

         vecPhi = vld1q(pPhi);
         pPhi += 4;

         vecRevPhi = vldrwq_gather_shifted_offset_s32(pRevPhi,revOffset);
         pRevPhi -= 4;

         suma = vmlaldavaq(suma,vecA,vecRevPhi);
         sumb = vmlaldavaq(sumb,vecA,vecPhi);

         i += 4;
         blkCnt--;
      }


      blkCnt = p & 3;
      while(blkCnt > 0)
      {
         suma += ((q63_t)a[i] * phi[p - i]);
         sumb += ((q63_t)a[i] * phi[i + 1]);

         i++;
         blkCnt--;
      }

      suma = asrl(suma, 31);
      sumb = asrl(sumb, 31);



      //k = (phi[p+1]-suma)/(phi[0] - sumb);
      k = divide(phi[p+1]-(q31_t)suma,phi[0] - (q31_t)sumb);

      q31x4_t vecRevA,tmp;
      static uint32_t orgOffsetArray[4]={0,1,-1,-2};
      static const uint32_t offsetIncArray[4]={2,2,-2,-2};

      uint32x4_t offset,offsetInc,vecTmp;


      offset = vld1q(orgOffsetArray);
      vecTmp = vdupq_n_u32(p);

      offset = vaddq_m_u32(offset,offset,vecTmp,LANE23_MASK);
      offsetInc = vld1q(offsetIncArray);


      nb = p >> 2;
      j=0;
      for(int i =0;i < nb ; i++)
      {
        /*
          q31_t x0,x1,x2,x3;

          //x = a[j] - k * a[p-1-j];
          x0 = a[j] - mul32x32(k,a[p-1-j]);
          x1 = a[j+1] - mul32x32(k,a[p-2-j]);

          //y = a[p-1-j] - k * a[j];
          x2 = a[p-1-j] - mul32x32(k , a[j]);
          x3 = a[p-2-j] - mul32x32(k , a[j+1]);

          a[j] = x0;
          a[j+1] = x1;
          a[p-1-j] = x2;
          a[p-2-j] = x3;
        */

          uint64_t tmpa,tmpb;
          vecA = vldrwq_gather_shifted_offset_s32(a,offset);


          tmpa = vgetq_lane_u64((uint64x2_t)vecA,0);
          tmpb = vgetq_lane_u64((uint64x2_t)vecA,1);
          vecRevA = (q31x4_t) vsetq_lane_u64(tmpb,(uint64x2_t)vecRevA,0);
          vecRevA = (q31x4_t) vsetq_lane_u64(tmpa,(uint64x2_t)vecRevA,1);


          tmp = vsubq(vecA,vqdmulhq_n_s32(vecRevA,k));
          vstrwq_scatter_shifted_offset_s32(a, offset, tmp);

          offset = vaddq(offset,offsetInc);

          j+=2;
      }

      switch(p & 3)
      {
         case 3:
         {
          q31_t x,y;

          //x = a[j] - k * a[p-1-j];
          x = a[j] - mul32x32(k,a[p-1-j]);

          //y = a[p-1-j] - k * a[j];
          y = a[p-1-j] - mul32x32(k , a[j]);

          a[j] = x;
          a[p-1-j] = y;

          //a[j] = a[j]- k * a[p-1-j];
          a[j+1] = a[j+1] - mul32x32(k,a[p-2-j]);
         }
         break;

         case 2:
         {
          q31_t x,y;

          //x = a[j] - k * a[p-1-j];
          x = a[j] - mul32x32(k,a[p-1-j]);

          //y = a[p-1-j] - k * a[j];
          y = a[p-1-j] - mul32x32(k , a[j]);

          a[j] = x;
          a[p-1-j] = y;
         }
         break;

         case 1:
            //a[j] = a[j]- k * a[p-1-j];
            a[j] = a[j] - mul32x32(k,a[p-1-j]);
         break;
      }

      a[p] = k;

      // e = e * (1 - k*k);
      e = mul32x32(e,ONE_Q31 - mul32x32(k,k));


   }
   *err = e;
}

#else

void arm_levinson_durbin_q31(const q31_t *phi,
  q31_t *a,
  q31_t *err,
  int nbCoefs)
{
   q31_t e;

   //a[0] = phi[1] / phi[0];
   a[0] = divide(phi[1], phi[0]);


   //e = phi[0] - phi[1] * a[0];
   e = phi[0] - mul32x32(phi[1],a[0]);

   for(int p=1; p < nbCoefs; p++)
   {
      q63_t suma=0;
      q63_t sumb=0;
      q31_t k;
      int nb,j;

      for(int i=0; i < p; i++)
      {
         suma += ((q63_t)a[i] * phi[p - i]);
         sumb += ((q63_t)a[i] * phi[i + 1]);
      }

      suma = suma >> 31;
      sumb = sumb >> 31;



      //k = (phi[p+1]-suma)/(phi[0] - sumb);
      k = divide(phi[p+1]-(q31_t)suma,phi[0] - (q31_t)sumb);


      nb = p >> 1;
      j=0;
      for(int i =0;i < nb ; i++)
      {
          q31_t x,y;

          //x = a[j] - k * a[p-1-j];
          x = a[j] - mul32x32(k,a[p-1-j]);

          //y = a[p-1-j] - k * a[j];
          y = a[p-1-j] - mul32x32(k , a[j]);

          a[j] = x;
          a[p-1-j] = y;

          j++;
      }

      nb = p & 1;
      if (nb)
      {
            //a[j] = a[j]- k * a[p-1-j];
            a[j] = a[j] - mul32x32(k,a[p-1-j]);
      }

      a[p] = k;

      // e = e * (1 - k*k);
      e = mul32x32(e,ONE_Q31 - mul32x32(k,k));


   }
   *err = e;
}
#endif /* defined(ARM_MATH_MVEI) */

/**
  @} end of LD group
 */
