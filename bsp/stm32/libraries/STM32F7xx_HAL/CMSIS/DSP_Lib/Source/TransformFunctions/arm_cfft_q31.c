/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2014 ARM Limited. All rights reserved.    
*    
* $Date:        19. March 2015 
* $Revision: 	V.1.4.5  
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_cfft_q31.c   
*    
* Description:	Combined Radix Decimation in Frequency CFFT fixed point processing function
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

extern void arm_radix4_butterfly_q31(
    q31_t * pSrc,
    uint32_t fftLen,
    q31_t * pCoef,
    uint32_t twidCoefModifier);

extern void arm_radix4_butterfly_inverse_q31(
    q31_t * pSrc,
    uint32_t fftLen,
    q31_t * pCoef,
    uint32_t twidCoefModifier);

extern void arm_bitreversal_32(
    uint32_t * pSrc,
    const uint16_t bitRevLen,
    const uint16_t * pBitRevTable);
    
void arm_cfft_radix4by2_q31(
    q31_t * pSrc,
    uint32_t fftLen,
    const q31_t * pCoef);
    
void arm_cfft_radix4by2_inverse_q31(
    q31_t * pSrc,
    uint32_t fftLen,
    const q31_t * pCoef);

/**   
* @ingroup groupTransforms   
*/

/**
* @addtogroup ComplexFFT   
* @{   
*/

/**   
* @details   
* @brief       Processing function for the fixed-point complex FFT in Q31 format.
* @param[in]      *S    points to an instance of the fixed-point CFFT structure.  
* @param[in, out] *p1   points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.  
* @param[in]     ifftFlag       flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform.  
* @param[in]     bitReverseFlag flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output.  
* @return none.  
*/

void arm_cfft_q31( 
    const arm_cfft_instance_q31 * S, 
    q31_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag)
{
    uint32_t L = S->fftLen;

    if(ifftFlag == 1u)
    {
        switch (L) 
        {
        case 16: 
        case 64:
        case 256:
        case 1024:
        case 4096:
            arm_radix4_butterfly_inverse_q31  ( p1, L, (q31_t*)S->pTwiddle, 1 );
            break;
            
        case 32:
        case 128:
        case 512:
        case 2048:
            arm_cfft_radix4by2_inverse_q31  ( p1, L, S->pTwiddle );
            break;
        }  
    }
    else
    {
        switch (L) 
        {
        case 16: 
        case 64:
        case 256:
        case 1024:
        case 4096:
            arm_radix4_butterfly_q31  ( p1, L, (q31_t*)S->pTwiddle, 1 );
            break;
            
        case 32:
        case 128:
        case 512:
        case 2048:
            arm_cfft_radix4by2_q31  ( p1, L, S->pTwiddle );
            break;
        }  
    }
    
    if( bitReverseFlag )
        arm_bitreversal_32((uint32_t*)p1,S->bitRevLength,S->pBitRevTable);    
}

/**    
* @} end of ComplexFFT group    
*/

void arm_cfft_radix4by2_q31(
    q31_t * pSrc,
    uint32_t fftLen,
    const q31_t * pCoef) 
{    
    uint32_t i, l;
    uint32_t n2, ia;
    q31_t xt, yt, cosVal, sinVal;
    q31_t p0, p1;
    
    n2 = fftLen >> 1;    
    ia = 0;
    for (i = 0; i < n2; i++)
    {
        cosVal = pCoef[2*ia];
        sinVal = pCoef[2*ia + 1];
        ia++;
        
        l = i + n2;
        xt = (pSrc[2 * i] >> 2) - (pSrc[2 * l] >> 2);
        pSrc[2 * i] = (pSrc[2 * i] >> 2) + (pSrc[2 * l] >> 2);
        
        yt = (pSrc[2 * i + 1] >> 2) - (pSrc[2 * l + 1] >> 2);
        pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2) + (pSrc[2 * i + 1] >> 2);
        
        mult_32x32_keep32_R(p0, xt, cosVal);
        mult_32x32_keep32_R(p1, yt, cosVal);
        multAcc_32x32_keep32_R(p0, yt, sinVal); 
        multSub_32x32_keep32_R(p1, xt, sinVal);
        
        pSrc[2u * l] = p0 << 1;
        pSrc[2u * l + 1u] = p1 << 1;
    
    }

    // first col
    arm_radix4_butterfly_q31( pSrc, n2, (q31_t*)pCoef, 2u);
    // second col
    arm_radix4_butterfly_q31( pSrc + fftLen, n2, (q31_t*)pCoef, 2u);
			
    for (i = 0; i < fftLen >> 1; i++)
    {
        p0 = pSrc[4*i+0];
        p1 = pSrc[4*i+1];
        xt = pSrc[4*i+2];
        yt = pSrc[4*i+3];
        
        p0 <<= 1;
        p1 <<= 1;
        xt <<= 1;
        yt <<= 1;
        
        pSrc[4*i+0] = p0;
        pSrc[4*i+1] = p1;
        pSrc[4*i+2] = xt;
        pSrc[4*i+3] = yt;
    }

}

void arm_cfft_radix4by2_inverse_q31(
    q31_t * pSrc,
    uint32_t fftLen,
    const q31_t * pCoef) 
{    
    uint32_t i, l;
    uint32_t n2, ia;
    q31_t xt, yt, cosVal, sinVal;
    q31_t p0, p1;
    
    n2 = fftLen >> 1;    
    ia = 0;
    for (i = 0; i < n2; i++)
    {
        cosVal = pCoef[2*ia];
        sinVal = pCoef[2*ia + 1];
        ia++;
        
        l = i + n2;
        xt = (pSrc[2 * i] >> 2) - (pSrc[2 * l] >> 2);
        pSrc[2 * i] = (pSrc[2 * i] >> 2) + (pSrc[2 * l] >> 2);
        
        yt = (pSrc[2 * i + 1] >> 2) - (pSrc[2 * l + 1] >> 2);
        pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2) + (pSrc[2 * i + 1] >> 2);
        
        mult_32x32_keep32_R(p0, xt, cosVal);
        mult_32x32_keep32_R(p1, yt, cosVal);
        multSub_32x32_keep32_R(p0, yt, sinVal); 
        multAcc_32x32_keep32_R(p1, xt, sinVal);
        
        pSrc[2u * l] = p0 << 1;
        pSrc[2u * l + 1u] = p1 << 1;
    
    }

    // first col
    arm_radix4_butterfly_inverse_q31( pSrc, n2, (q31_t*)pCoef, 2u);
    // second col
    arm_radix4_butterfly_inverse_q31( pSrc + fftLen, n2, (q31_t*)pCoef, 2u);
			
    for (i = 0; i < fftLen >> 1; i++)
    {
        p0 = pSrc[4*i+0];
        p1 = pSrc[4*i+1];
        xt = pSrc[4*i+2];
        yt = pSrc[4*i+3];
        
        p0 <<= 1;
        p1 <<= 1;
        xt <<= 1;
        yt <<= 1;
        
        pSrc[4*i+0] = p0;
        pSrc[4*i+1] = p1;
        pSrc[4*i+2] = xt;
        pSrc[4*i+3] = yt;
    }
}

