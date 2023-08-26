/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_levinson_durbin_f16.c
 * Description:  f16 version of Levinson Durbin algorithm
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

#include "dsp/filtering_functions_f16.h"

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
#pragma GCC warning "Scalar version of arm_levinson_durbin_f16 built. Helium version has build issues with gcc."
#endif 

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) &&  !defined(__CMSIS_GCC_H)

#include "arm_helium_utils.h"

#define LANE4567_MASK 0xFF00

void arm_levinson_durbin_f16(const float16_t *phi,
  float16_t *a, 
  float16_t *err,
  int nbCoefs)
{
   _Float16 e;
   static const uint16_t revOffsetArray[8] = {7,6,5,4,3,2,1,0};

   a[0] = (_Float16)phi[1] / (_Float16)phi[0];

   e = (_Float16)phi[0] - (_Float16)phi[1] * (_Float16)a[0];
   for(int p=1; p < nbCoefs; p++)
   {
      _Float16 suma = 0.0f16;
      _Float16 sumb = 0.0f16;
      f16x8_t vecA,vecRevPhi,vecPhi,vecSumA, vecSumB;
      _Float16 k;
      uint32_t blkCnt; 
      const float16_t *pPhi,*pRevPhi,*pA;
      uint16x8_t revOffset;

      int nb,j,i;

      revOffset = vld1q(revOffsetArray);
      vecSumA = vdupq_n_f16(0.0f16);
      vecSumB = vdupq_n_f16(0.0f16);

      pRevPhi = &phi[p-7];
      pPhi = &phi[1];
      pA = a;

      i = 0;
      blkCnt = p >> 3;
      while(blkCnt > 0)
      {
         vecA = vld1q(pA);
         pA += 8;

         vecPhi = vld1q(pPhi);
         pPhi += 8;

         vecRevPhi = vldrhq_gather_shifted_offset_f16(pRevPhi,revOffset);
         pRevPhi -= 8;

         vecSumA = vfmaq(vecSumA,vecA,vecRevPhi);
         vecSumB = vfmaq(vecSumB,vecA,vecPhi);

         i += 8;
         blkCnt--;

      }

      suma = vecAddAcrossF16Mve(vecSumA);
      sumb = vecAddAcrossF16Mve(vecSumB);

      blkCnt = p & 7;
      while(blkCnt > 0)
      {
         suma += (_Float16)a[i] * (_Float16)phi[p - i];
         sumb += (_Float16)a[i] * (_Float16)phi[i + 1];

         i++;
         blkCnt--;
      }

      k = ((_Float16)phi[p+1] - suma)/((_Float16)phi[0] - sumb);

      f16x8_t vecRevA,tmp;
      static int16_t orgOffsetArray[8]={0,1,2,3,-1,-2,-3,-4};
      static const int16_t offsetIncArray[8]={4,4,4,4,-4,-4,-4,-4};

      uint16x8_t offset,offsetInc,vecTmp;


      offset = vld1q_u16((uint16_t*)orgOffsetArray);
      vecTmp = vdupq_n_u16(p);

      offset = vaddq_m_u16(offset,offset,vecTmp,LANE4567_MASK);
      offsetInc = vld1q_u16((uint16_t*)offsetIncArray);

      nb = p >> 3;
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
          vecA = vldrhq_gather_shifted_offset_f16(a,offset);

          
          tmpa = vgetq_lane_u64((uint64x2_t)vecA,0);
          tmpb = vgetq_lane_u64((uint64x2_t)vecA,1);
          vecRevA = (f16x8_t) vsetq_lane_u64(tmpb,(uint64x2_t)vecRevA,0);
          vecRevA = (f16x8_t) vsetq_lane_u64(tmpa,(uint64x2_t)vecRevA,1);
          

          tmp = vsubq(vecA,vmulq_n_f16(vecRevA,k));
          vstrhq_scatter_shifted_offset_f16(a, offset, tmp);

          offset = vaddq(offset,offsetInc);
 
          j+=4;

      }

      blkCnt = p & 7;

      if (blkCnt)
      {
         nb = blkCnt >> 1;
         for(int i =0;i < nb ; i++)
         {
             _Float16 x,y;
   
             x=(_Float16)a[j] - (_Float16)k * (_Float16)a[p-1-j];
             y=(_Float16)a[p-1-j] - (_Float16)k * (_Float16)a[j];
   
             a[j] = x;
             a[p-1-j] = y;
   
             j++;
         }
   
         nb = blkCnt & 1;
         if (nb)
         {
               a[j]=(_Float16)a[j]- (_Float16)k * (_Float16)a[p-1-j];
         }
      }

     
      a[p] = k;
      e = e * (1.0f16 - k*k);


   }
   *err = e;
}

#else

#if defined(ARM_FLOAT16_SUPPORTED)

void arm_levinson_durbin_f16(const float16_t *phi,
  float16_t *a, 
  float16_t *err,
  int nbCoefs)
{
   _Float16 e;

   a[0] = (_Float16)phi[1] / (_Float16)phi[0];

   e = (_Float16)phi[0] - (_Float16)phi[1] * (_Float16)a[0];
   for(int p=1; p < nbCoefs; p++)
   {
      _Float16 suma=0.0f16;
      _Float16 sumb=0.0f16;
      _Float16 k;
      int nb,j;

      for(int i=0; i < p; i++)
      {
         suma += (_Float16)a[i] * (_Float16)phi[p - i];
         sumb += (_Float16)a[i] * (_Float16)phi[i + 1];
      }

      k = ((_Float16)phi[p+1]-suma)/((_Float16)phi[0] - sumb);


      nb = p >> 1;
      j=0;
      for(int i =0;i < nb ; i++)
      {
          _Float16 x,y;

          x=(_Float16)a[j] - (_Float16)k * (_Float16)a[p-1-j];
          y=(_Float16)a[p-1-j] - (_Float16)k * (_Float16)a[j];

          a[j] = x;
          a[p-1-j] = y;

          j++;
      }

      nb = p & 1;
      if (nb)
      {
            a[j]=(_Float16)a[j]- (_Float16)k * (_Float16)a[p-1-j];
      }

      a[p] = k;
      e = e * (1.0f16 - k*k);


   }
   *err = e;
}
#endif /* defined(ARM_FLOAT16_SUPPORTED */
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of LD group
 */
