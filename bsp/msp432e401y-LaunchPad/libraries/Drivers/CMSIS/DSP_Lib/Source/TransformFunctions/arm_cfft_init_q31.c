/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cfft_init_q31.c
 * Description:  Initialization function for cfft q31 instance
 *
 * $Date:        07. January 2020
 * $Revision:    V1.7.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2020 ARM Limited or its affiliates. All rights reserved.
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

#define FFTINIT(EXT,SIZE)                                           \
  S->bitRevLength = arm_cfft_sR_##EXT##_len##SIZE.bitRevLength;        \
  S->pBitRevTable = arm_cfft_sR_##EXT##_len##SIZE.pBitRevTable;         \
  S->pTwiddle = arm_cfft_sR_##EXT##_len##SIZE.pTwiddle;

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Initialization function for the cfft q31 function
  @param[in,out] S              points to an instance of the floating-point CFFT structure
  @param[in]     fftLen         fft length (number of complex samples)
  @return        execution status
                   - \ref ARM_MATH_SUCCESS        : Operation successful
                   - \ref ARM_MATH_ARGUMENT_ERROR : an error is detected

  @par          Use of this function is mandatory only for the MVE version of the FFT.
                Other versions can still initialize directly the data structure using 
                variables declared in arm_const_structs.h
 */

#include "arm_math.h"
#include "arm_common_tables.h"
#include "arm_const_structs.h"

#if defined(ARM_MATH_MVEI) 

#include "arm_vec_fft.h"
#include "arm_mve_tables.h"


arm_status arm_cfft_radix4by2_rearrange_twiddles_q31(arm_cfft_instance_q31 *S, int twidCoefModifier)
{
                                                                  
        switch (S->fftLen >> (twidCoefModifier - 1)) {  

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_4096)
        case 4096U:                                                                                
            S->rearranged_twiddle_tab_stride1_arr = rearranged_twiddle_tab_stride1_arr_4096_q31;
            S->rearranged_twiddle_stride1  =  rearranged_twiddle_stride1_4096_q31;     

            S->rearranged_twiddle_tab_stride2_arr = rearranged_twiddle_tab_stride2_arr_4096_q31;
            S->rearranged_twiddle_stride2  =  rearranged_twiddle_stride2_4096_q31;    

            S->rearranged_twiddle_tab_stride3_arr = rearranged_twiddle_tab_stride3_arr_4096_q31;
            S->rearranged_twiddle_stride3  =  rearranged_twiddle_stride3_4096_q31;                                                     
            break; 
#endif                                  

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_1024) || defined(ARM_TABLE_BITREVIDX_FXT_2048)                                                                                                   
        case 1024U:                                                                                
            S->rearranged_twiddle_tab_stride1_arr = rearranged_twiddle_tab_stride1_arr_1024_q31;
            S->rearranged_twiddle_stride1  =  rearranged_twiddle_stride1_1024_q31;     

            S->rearranged_twiddle_tab_stride2_arr = rearranged_twiddle_tab_stride2_arr_1024_q31;
            S->rearranged_twiddle_stride2  =  rearranged_twiddle_stride2_1024_q31;    

            S->rearranged_twiddle_tab_stride3_arr = rearranged_twiddle_tab_stride3_arr_1024_q31;
            S->rearranged_twiddle_stride3  =  rearranged_twiddle_stride3_1024_q31;                                                                          
            break;                                                                                 
 #endif 

 #if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_256) || defined(ARM_TABLE_BITREVIDX_FXT_512)                                                                                                  
        case 256U:                                                                                 
            S->rearranged_twiddle_tab_stride1_arr = rearranged_twiddle_tab_stride1_arr_256_q31;
            S->rearranged_twiddle_stride1  =  rearranged_twiddle_stride1_256_q31;     

            S->rearranged_twiddle_tab_stride2_arr = rearranged_twiddle_tab_stride2_arr_256_q31;
            S->rearranged_twiddle_stride2  =  rearranged_twiddle_stride2_256_q31;    

            S->rearranged_twiddle_tab_stride3_arr = rearranged_twiddle_tab_stride3_arr_256_q31;
            S->rearranged_twiddle_stride3  =  rearranged_twiddle_stride3_256_q31;    

            break;                     
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_64) || defined(ARM_TABLE_BITREVIDX_FXT_128)
        case 64U:                                                                                  
            S->rearranged_twiddle_tab_stride1_arr = rearranged_twiddle_tab_stride1_arr_64_q31;
            S->rearranged_twiddle_stride1  =  rearranged_twiddle_stride1_64_q31;     

            S->rearranged_twiddle_tab_stride2_arr = rearranged_twiddle_tab_stride2_arr_64_q31;
            S->rearranged_twiddle_stride2  =  rearranged_twiddle_stride2_64_q31;    

            S->rearranged_twiddle_tab_stride3_arr = rearranged_twiddle_tab_stride3_arr_64_q31;
            S->rearranged_twiddle_stride3  =  rearranged_twiddle_stride3_64_q31;                                                                         
            break;  
#endif                                                                               
              
#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_16) || defined(ARM_TABLE_BITREVIDX_FXT_32)                                                                                                                                                                                                                
        case 16U:                                                                                  
            S->rearranged_twiddle_tab_stride1_arr = rearranged_twiddle_tab_stride1_arr_16_q31;
            S->rearranged_twiddle_stride1  =  rearranged_twiddle_stride1_16_q31;     

            S->rearranged_twiddle_tab_stride2_arr = rearranged_twiddle_tab_stride2_arr_16_q31;
            S->rearranged_twiddle_stride2  =  rearranged_twiddle_stride2_16_q31;    

            S->rearranged_twiddle_tab_stride3_arr = rearranged_twiddle_tab_stride3_arr_16_q31;
            S->rearranged_twiddle_stride3  =  rearranged_twiddle_stride3_16_q31;                                                                       
            break;  
#endif                                                                               
                                                                                                   
        default:  
            return(ARM_MATH_ARGUMENT_ERROR);                                                                                 
            break;                                                                                 
            /* invalid sizes already filtered */                                                   
        }                                                                                          

        return(ARM_MATH_SUCCESS);

}



arm_status arm_cfft_init_q31(
  arm_cfft_instance_q31 * S,
  uint16_t fftLen)
{

        /*  Initialise the default arm status */                                
        arm_status status = ARM_MATH_SUCCESS;                                   
                                                                                
        /*  Initialise the FFT length */                                        
        S->fftLen = fftLen;                                                     
                                                                                
        /*  Initialise the Twiddle coefficient pointer */                       
        S->pTwiddle = NULL;                         
                                                                                
                                                                                
        /*  Initializations of Instance structure depending on the FFT length */
        switch (S->fftLen) {                                                    
            /*  Initializations of structure parameters for 4096 point FFT */   
#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_4096)                                                           
        case 4096U:  
            /*  Initialise the bit reversal table modifier */                   
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH;      
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_4096;   
            S->pTwiddle = (q31_t *)twiddleCoef_4096_q31;       
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 1);               
            break;                                                              
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_2048)                                                                                                        
            /*  Initializations of structure parameters for 2048 point FFT */   
        case 2048U:                                                             
            /*  Initialise the bit reversal table modifier */                   
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH;      
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_2048;
            S->pTwiddle = (q31_t *)twiddleCoef_2048_q31;          
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 2);           
            break;     
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_1024)                                                                                                                  
            /*  Initializations of structure parameters for 1024 point FFT */   
        case 1024U:                                                             
            /*  Initialise the bit reversal table modifier */                   
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH;      
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_1024; 
            S->pTwiddle = (q31_t *)twiddleCoef_1024_q31;         
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 1);           
            break;                                                              
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_512)                                                           
            /*  Initializations of structure parameters for 512 point FFT */    
        case 512U:                                                              
            /*  Initialise the bit reversal table modifier */                   
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH;       
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_512;  
            S->pTwiddle = (q31_t *)twiddleCoef_512_q31;         
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 2);           
            break;                                                              
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_256)                                                           
        case 256U:                                                              
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH;       
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_256; 
            S->pTwiddle = (q31_t *)twiddleCoef_256_q31;          
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 1);           
            break;  
#endif                                                            
                 
#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_128)                                                                                                                          
        case 128U:                                                              
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH;       
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_128; 
            S->pTwiddle = (q31_t *)twiddleCoef_128_q31;          
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 2);           
            break;                                                              
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_64)                                                                                                                      
        case 64U:                                                               
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH;        
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_64;  
            S->pTwiddle = (q31_t *)twiddleCoef_64_q31;          
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 1);           
            break;                                                              
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_32)                                                                                                                           
        case 32U:                                                               
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH;        
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_32;  
            S->pTwiddle = (q31_t *)twiddleCoef_32_q31;          
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 2);           
            break;                                                              
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || defined(ARM_TABLE_BITREVIDX_FXT_16)                                                                                                                                
        case 16U:                                                               
            /*  Initializations of structure parameters for 16 point FFT */     
            S->bitRevLength = ARMBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH;        
            S->pBitRevTable = (uint16_t *)armBitRevIndexTable_fixed_16; 
            S->pTwiddle = (q31_t *)twiddleCoef_16_q31;           
            status=arm_cfft_radix4by2_rearrange_twiddles_q31(S, 1);           
            break;                                                              
#endif                                                                             
                                                                         
        default:                                                                
            /*  Reporting argument error if fftSize is not valid value */       
            status = ARM_MATH_ARGUMENT_ERROR;                                   
            break;                                                              
        }                                                                       
                                                                                
                                                                                
        return (status);     
}
#else
arm_status arm_cfft_init_q31(
  arm_cfft_instance_q31 * S,
  uint16_t fftLen)
{
        /*  Initialise the default arm status */
        arm_status status = ARM_MATH_SUCCESS;

        /*  Initialise the FFT length */
        S->fftLen = fftLen;

        /*  Initialise the Twiddle coefficient pointer */
        S->pTwiddle = NULL;


        /*  Initializations of Instance structure depending on the FFT length */
        switch (S->fftLen) {
#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_4096) && defined(ARM_TABLE_BITREVIDX_FLT_4096))
            /*  Initializations of structure parameters for 4096 point FFT */
        case 4096U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,4096);
            break;
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_2048) && defined(ARM_TABLE_BITREVIDX_FLT_2048))
            /*  Initializations of structure parameters for 2048 point FFT */
        case 2048U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,2048);

            break;
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_1024) && defined(ARM_TABLE_BITREVIDX_FLT_1024))
            /*  Initializations of structure parameters for 1024 point FFT */
        case 1024U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,1024);

            break;
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_512) && defined(ARM_TABLE_BITREVIDX_FLT_512))
            /*  Initializations of structure parameters for 512 point FFT */
        case 512U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,512);
            break;
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_256) && defined(ARM_TABLE_BITREVIDX_FLT_256))
        case 256U:
            FFTINIT(q31,256);
            break;
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_128) && defined(ARM_TABLE_BITREVIDX_FLT_128))
        case 128U:
            FFTINIT(q31,128);
            break;
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_64) && defined(ARM_TABLE_BITREVIDX_FLT_64))
        case 64U:
            FFTINIT(q31,64);
            break;
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_32) && defined(ARM_TABLE_BITREVIDX_FLT_32))
        case 32U:
            FFTINIT(q31,32);
            break;
#endif 

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FFT_TABLES) || (defined(ARM_TABLE_TWIDDLECOEF_Q31_16) && defined(ARM_TABLE_BITREVIDX_FLT_16))
        case 16U:
            /*  Initializations of structure parameters for 16 point FFT */
            FFTINIT(q31,16);
            break;
#endif

        default:
            /*  Reporting argument error if fftSize is not valid value */
            status = ARM_MATH_ARGUMENT_ERROR;
            break;
        }


        return (status);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of ComplexFFT group
 */
