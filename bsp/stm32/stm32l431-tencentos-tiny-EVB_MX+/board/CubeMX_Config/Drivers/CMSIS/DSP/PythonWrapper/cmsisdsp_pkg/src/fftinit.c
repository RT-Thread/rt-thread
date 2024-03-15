/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Python Wrapper
 * Title:        fftinit.c
 * Description:  FFT init functions for the Python wrapper
 *
 * $Date:        25. March 2019
 * $Revision:    V0.0.1
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
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
#include "arm_math.h"
#include "arm_common_tables.h"
#include "arm_const_structs.h"

#define FFTINIT(SIZE)                                           \
  S->bitRevLength = arm_cfft_sR_f32_len##SIZE.bitRevLength;        \
  S->pBitRevTable = arm_cfft_sR_f32_len##SIZE.pBitRevTable;         \
  S->pTwiddle = arm_cfft_sR_f32_len##SIZE.pTwiddle;

#define FFTFXTINIT(EXT,SIZE)                                           \
  S->bitRevLength = arm_cfft_sR_##EXT##_len##SIZE.bitRevLength;        \
  S->pBitRevTable = arm_cfft_sR_##EXT##_len##SIZE.pBitRevTable;         \
  S->pTwiddle = arm_cfft_sR_##EXT##_len##SIZE.pTwiddle;

arm_status arm_cfft_init_f32(
  arm_cfft_instance_f32 * S,
  uint16_t fftLen)
{
        /*  Initialise the default arm status */                                
        arm_status status = ARM_MATH_SUCCESS;                                   
                                                                                
        /*  Initialise the FFT length */                                        
        S->fftLen = fftLen;          
                                                                                
        /*  Initialise the Twiddle coefficient pointer */                       
        S->pTwiddle = (float32_t *)twiddleCoef_4096;                         
                                                                                
                                                                                
        /*  Initializations of Instance structure depending on the FFT length */
        switch (S->fftLen) {                                                    
            /*  Initializations of structure parameters for 4096 point FFT */   
        case 4096U:                                                             
            /*  Initialise the bit reversal table modifier */                   
            FFTINIT(4096);      
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 2048 point FFT */   
        case 2048U:                                                             
            /*  Initialise the bit reversal table modifier */                   
            FFTINIT(2048);                 
                                                                            
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 1024 point FFT */   
        case 1024U:                                                             
            /*  Initialise the bit reversal table modifier */                   
            FFTINIT(1024);                 
                                                                         
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 512 point FFT */    
        case 512U:                                                              
            /*  Initialise the bit reversal table modifier */                   
            FFTINIT(512);                                                                                   
            break;                                                              
                                                                                
        case 256U:                                                              
            FFTINIT(256);                                                                                  
            break;                                                              
                                                                                
        case 128U:                                                              
            FFTINIT(128);                                                                                  
            break;                                                              
                                                                                
        case 64U:                                                               
            FFTINIT(64);                                                                               
            break;                                                              
                                                                                
        case 32U:                                                               
            FFTINIT(32);                                                                                
            break;                                                              
                                                                                
        case 16U:                                                               
            /*  Initializations of structure parameters for 16 point FFT */     
            FFTINIT(16);   
            break;                                                              
                                                                                
                                                                                
        default:                                                                
            /*  Reporting argument error if fftSize is not valid value */       
            status = ARM_MATH_ARGUMENT_ERROR;                                   
            break;                                                              
        }                                                                       
                                                                                
                                                                                
        return (status);    
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
        S->pTwiddle = (float32_t *)twiddleCoef_4096;                         
                                                                                
                                                                                
        /*  Initializations of Instance structure depending on the FFT length */
        switch (S->fftLen) {                                                    
            /*  Initializations of structure parameters for 4096 point FFT */   
        case 4096U:                                                             
            /*  Initialise the bit reversal table modifier */                   
            FFTFXTINIT(q31,4096);      
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 2048 point FFT */   
        case 2048U:                                                             
            /*  Initialise the bit reversal table modifier */                   
             FFTFXTINIT(q31,2048);                 
                                                                            
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 1024 point FFT */   
        case 1024U:                                                             
            /*  Initialise the bit reversal table modifier */                   
             FFTFXTINIT(q31,1024);                 
                                                                         
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 512 point FFT */    
        case 512U:                                                              
            /*  Initialise the bit reversal table modifier */                   
             FFTFXTINIT(q31,512);                                                                                   
            break;                                                              
                                                                                
        case 256U:                                                              
             FFTFXTINIT(q31,256);                                                                                  
            break;                                                              
                                                                                
        case 128U:                                                              
             FFTFXTINIT(q31,128);                                                                                  
            break;                                                              
                                                                                
        case 64U:                                                               
             FFTFXTINIT(q31,64);                                                                               
            break;                                                              
                                                                                
        case 32U:                                                               
             FFTFXTINIT(q31,32);                                                                                
            break;                                                              
                                                                                
        case 16U:                                                               
            /*  Initializations of structure parameters for 16 point FFT */     
             FFTFXTINIT(q31,16);   
            break;                                                              
                                                                                
                                                                                
        default:                                                                
            /*  Reporting argument error if fftSize is not valid value */       
            status = ARM_MATH_ARGUMENT_ERROR;                                   
            break;                                                              
        }                                                                       
                                                                                
                                                                                
        return (status);    
}

arm_status arm_cfft_init_q15(
  arm_cfft_instance_q15 * S,
  uint16_t fftLen)
{
        /*  Initialise the default arm status */                                
        arm_status status = ARM_MATH_SUCCESS;                                   
                                                                                
        /*  Initialise the FFT length */                                        
        S->fftLen = fftLen;          
                                                                                
        /*  Initialise the Twiddle coefficient pointer */                       
        S->pTwiddle = (float32_t *)twiddleCoef_4096;                         
                                                                                
                                                                                
        /*  Initializations of Instance structure depending on the FFT length */
        switch (S->fftLen) {                                                    
            /*  Initializations of structure parameters for 4096 point FFT */   
        case 4096U:                                                             
            /*  Initialise the bit reversal table modifier */                   
            FFTFXTINIT(q15,4096);      
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 2048 point FFT */   
        case 2048U:                                                             
            /*  Initialise the bit reversal table modifier */                   
             FFTFXTINIT(q15,2048);                 
                                                                            
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 1024 point FFT */   
        case 1024U:                                                             
            /*  Initialise the bit reversal table modifier */                   
             FFTFXTINIT(q15,1024);                 
                                                                         
            break;                                                              
                                                                                
            /*  Initializations of structure parameters for 512 point FFT */    
        case 512U:                                                              
            /*  Initialise the bit reversal table modifier */                   
            FFTFXTINIT(q15,512);                                                                                   
            break;                                                              
                                                                                
        case 256U:                                                              
            FFTFXTINIT(q15,256);                                                                                  
            break;                                                              
                                                                                
        case 128U:                                                              
            FFTFXTINIT(q15,128);                                                                                  
            break;                                                              
                                                                                
        case 64U:                                                               
            FFTFXTINIT(q15,64);                                                                               
            break;                                                              
                                                                                
        case 32U:                                                               
            FFTFXTINIT(q15,32);                                                                                
            break;                                                              
                                                                                
        case 16U:                                                               
            /*  Initializations of structure parameters for 16 point FFT */     
            FFTFXTINIT(q15,16);   
            break;                                                              
                                                                                
                                                                                
        default:                                                                
            /*  Reporting argument error if fftSize is not valid value */       
            status = ARM_MATH_ARGUMENT_ERROR;                                   
            break;                                                              
        }                                                                       
                                                                                
                                                                                
        return (status);    
}