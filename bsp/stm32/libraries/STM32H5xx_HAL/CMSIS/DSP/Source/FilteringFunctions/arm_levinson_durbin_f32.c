/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_levinson_durbin_f32.c
 * Description:  f32 version of Levinson Durbin algorithm
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
#pragma GCC warning "Scalar version of arm_levinson_durbin_f32 built. Helium version has build issues with gcc."
#endif 

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) &&  !defined(__CMSIS_GCC_H)

#include "arm_helium_utils.h"

#define LANE23_MASK 0xFF00

void arm_levinson_durbin_f32(const float32_t *phi,
  float32_t *a, 
  float32_t *err,
  int nbCoefs)
{
   float32_t e;
   static const uint32_t revOffsetArray[4] = {3,2,1,0};

   a[0] = phi[1] / phi[0];

   e = phi[0] - phi[1] * a[0];
   for(int p=1; p < nbCoefs; p++)
   {
      float32_t suma = 0.0f;
      float32_t sumb = 0.0f;
      f32x4_t vecA,vecRevPhi,vecPhi,vecSumA, vecSumB;
      float32_t k;
      uint32_t blkCnt; 
      const float32_t *pPhi,*pRevPhi,*pA;
      uint32x4_t revOffset;

      int nb,j,i;

      revOffset = vld1q(revOffsetArray);
      vecSumA = vdupq_n_f32(0.0f);
      vecSumB = vdupq_n_f32(0.0f);

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

         vecRevPhi = vldrwq_gather_shifted_offset_f32(pRevPhi,revOffset);
         pRevPhi -= 4;

         vecSumA = vfmaq(vecSumA,vecA,vecRevPhi);
         vecSumB = vfmaq(vecSumB,vecA,vecPhi);

         i += 4;
         blkCnt--;

      }

      suma = vecAddAcrossF32Mve(vecSumA);
      sumb = vecAddAcrossF32Mve(vecSumB);

      blkCnt = p & 3;
      while(blkCnt > 0)
      {
         suma += a[i] * phi[p - i];
         sumb += a[i] * phi[i + 1];

         i++;
         blkCnt--;
      }

      k = (phi[p+1] - suma)/(phi[0] - sumb);

      f32x4_t vecRevA,tmp;
      static int32_t orgOffsetArray[4]={0,1,-1,-2};
      static const int32_t offsetIncArray[4]={2,2,-2,-2};

      uint32x4_t offset,offsetInc,vecTmp;


      offset = vld1q_u32((uint32_t*)orgOffsetArray);
      vecTmp = vdupq_n_u32(p);

      offset = vaddq_m_u32(offset,offset,vecTmp,LANE23_MASK);
      offsetInc = vld1q_u32((uint32_t*)offsetIncArray);

      nb = p >> 2;
      j=0;
      for(int i = 0; i < nb ; i++)
      {
          
          /*
            x0=a[j] - k * a[p-1-j];
            x1=a[j+1] - k * a[p-2-j];
            x3=a[p-1-j] - k * a[j];
            x4=a[p-2-j] - k * a[j+1];

            a[j] = x0;
            a[j+1] = x1;
            a[p-1-j] = x2;
            a[p-2-j] = x3;
          */

          uint64_t tmpa,tmpb;
          vecA = vldrwq_gather_shifted_offset_f32(a,offset);

          
          tmpa = vgetq_lane_u64((uint64x2_t)vecA,0);
          tmpb = vgetq_lane_u64((uint64x2_t)vecA,1);
          vecRevA = (f32x4_t) vsetq_lane_u64(tmpb,(uint64x2_t)vecRevA,0);
          vecRevA = (f32x4_t) vsetq_lane_u64(tmpa,(uint64x2_t)vecRevA,1);
          

          tmp = vsubq(vecA,vmulq_n_f32(vecRevA,k));
          vstrwq_scatter_shifted_offset_f32(a, offset, tmp);

          offset = vaddq(offset,offsetInc);
 
          j+=2;

      }

      switch(p & 3)
      {
         case 3:
         {
            float32_t x,y;
            x = a[j] - k * a[p-1-j];
            y = a[p-1-j] - k * a[j];

            a[j] = x;
            a[p-1-j] = y;

            a[j+1] = a[j+1] - k * a[p-1-(j+1)];
         }
         break;

         case 2:
         {
            float32_t x,y;
            x = a[j] - k * a[p-1-j];
            y = a[p-1-j] - k * a[j];

            a[j] = x;
            a[p-1-j] = y;
         }
         break;

         case 1:
            a[j] = a[j]- k * a[p-1-j];
         break;
      }

      a[p] = k;
      e = e * (1.0f - k*k);


   }
   *err = e;
}

#else
void arm_levinson_durbin_f32(const float32_t *phi,
  float32_t *a, 
  float32_t *err,
  int nbCoefs)
{
   float32_t e;
   int p;

   a[0] = phi[1] / phi[0];

   e = phi[0] - phi[1] * a[0];
   for(p=1; p < nbCoefs; p++)
   {
      float32_t suma=0.0f;
      float32_t sumb=0.0f;
      float32_t k;
      int nb,j,i;

      for(i=0; i < p; i++)
      {
         suma += a[i] * phi[p - i];
         sumb += a[i] * phi[i + 1];
      }

      k = (phi[p+1]-suma)/(phi[0] - sumb);


      nb = p >> 1;
      j=0;
      for(i =0; i < nb ; i++)
      {
          float32_t x,y;

          x=a[j] - k * a[p-1-j];
          y=a[p-1-j] - k * a[j];

          a[j] = x;
          a[p-1-j] = y;

          j++;
      }

      nb = p & 1;
      if (nb)
      {
            a[j]=a[j]- k * a[p-1-j];
      }

      a[p] = k;
      e = e * (1.0f - k*k);


   }
   *err = e;
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of LD group
 */
