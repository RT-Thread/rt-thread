/*
 * Copyright 2018-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_powerquad.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.powerquad_math"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void PQ_VectorLnF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_ln0(val.integerX);
            val.integerX = _pq_readAdd0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_LN, 1, PQ_TRANS);
        PQ_EndVector();
    }
}

void PQ_VectorInvF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_inv0(val.integerX);
            val.integerX = _pq_readMult0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_INV, 0, PQ_TRANS);
        PQ_EndVector();
    }
}

void PQ_VectorSqrtF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_sqrt0(val.integerX);
            val.integerX = _pq_readMult0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_SQRT, 0, PQ_TRANS);
        PQ_EndVector();
    }
}

void PQ_VectorInvSqrtF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_invsqrt0(val.integerX);
            val.integerX = _pq_readMult0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_INVSQRT, 0, PQ_TRANS);
        PQ_EndVector();
    }
}

void PQ_VectorEtoxF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_etox0(val.integerX);
            val.integerX = _pq_readMult0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_ETOX, 0, PQ_TRANS);
        PQ_EndVector();
    }
}

void PQ_VectorEtonxF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_etonx0(val.integerX);
            val.integerX = _pq_readMult0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_ETONX, 0, PQ_TRANS);
        PQ_EndVector();
    }
}

void PQ_VectorSinF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_sin0(val.integerX);
            val.integerX = _pq_readAdd0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_SIN, 1, PQ_TRIG);
        PQ_EndVector();
    }
}

void PQ_VectorCosF32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_cos0(val.integerX);
            val.integerX = _pq_readAdd0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8F32(PQ_COS, 1, PQ_TRIG);
        PQ_EndVector();
    }
}

void PQ_VectorLnFixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_ln_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readAdd0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_LN, 1, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorInvFixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_inv_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_INV, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorSqrtFixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_sqrt_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_SQRT, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorInvSqrtFixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_invsqrt_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_INVSQRT, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorEtoxFixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_etox_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_ETOX, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorEtonxFixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_etonx_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_ETONX, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorSinQ31(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    uint32_t cppre;
#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    pq_float_t magic;
    pq_float_t valFloat;

    magic.integerX = 0x30c90fdbU;
#endif

    cppre            = POWERQUAD->CPPRE;
    POWERQUAD->CPPRE = POWERQUAD_CPPRE_CPPRE_OUT(31);

#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            valFloat.floatX = magic.floatX * (float)(*pSrc++);
            _pq_sin0(valFloat.integerX);
            (void)_pq_readAdd0();
            *pDst++ = (int32_t)_pq_readAdd0_fx();
        }
    }

    while (length > 0)
    {
        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        length -= 8;
    }

#else
    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_sin_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readAdd0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_SIN, 1, PQ_TRIG_FIXED);
        PQ_EndVector();
    }
#endif

    POWERQUAD->CPPRE = cppre;
}

void PQ_VectorCosQ31(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    uint32_t cppre;
#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    pq_float_t magic;
    pq_float_t valFloat;

    magic.integerX = 0x30c90fdb;
#endif

    cppre            = POWERQUAD->CPPRE;
    POWERQUAD->CPPRE = POWERQUAD_CPPRE_CPPRE_OUT(31);

#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            valFloat.floatX = magic.floatX * (float)(*pSrc++);
            _pq_cos0(valFloat.integerX);
            (void)_pq_readAdd0();
            *pDst++ = (int32_t)_pq_readAdd0_fx();
        }
    }

    while (length > 0)
    {
        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        valFloat.floatX = magic.floatX * (float)(*pSrc++);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int32_t)_pq_readAdd0_fx();

        length -= 8;
    }

#else
    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_cos_fx0(*pSrc++);
            *pDst++ = (int32_t)_pq_readAdd0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8Fixed32(PQ_COS, 1, PQ_TRIG_FIXED);
        PQ_EndVector();
    }
#endif

    POWERQUAD->CPPRE = cppre;
}

void PQ_VectorLnFixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_ln_fx0(*pSrc++);
            *pDst++ = (int16_t)_pq_readAdd0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(pSrc, pDst, length);
        PQ_Vector8Fixed16(PQ_LN, 1, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorInvFixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_inv_fx0(*pSrc++);
            *pDst++ = (int16_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(pSrc, pDst, length);
        PQ_Vector8Fixed16(PQ_INV, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorSqrtFixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_sqrt_fx0(*pSrc++);
            *pDst++ = (int16_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(pSrc, pDst, length);
        PQ_Vector8Fixed16(PQ_SQRT, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorInvSqrtFixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_invsqrt_fx0(*pSrc++);
            *pDst++ = (int16_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(pSrc, pDst, length);
        PQ_Vector8Fixed16(PQ_INVSQRT, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorEtoxFixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_etox_fx0(*pSrc++);
            *pDst++ = (int16_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(pSrc, pDst, length);
        PQ_Vector8Fixed16(PQ_ETOX, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorEtonxFixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_etonx_fx0(*pSrc++);
            *pDst++ = (int16_t)_pq_readMult0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(pSrc, pDst, length);
        PQ_Vector8Fixed16(PQ_ETONX, 0, PQ_TRANS_FIXED);
        PQ_EndVector();
    }
}

void PQ_VectorSinQ15(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    uint32_t cppre;
#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    pq_float_t magic;
    pq_float_t valFloat;

    magic.integerX = 0x30c90fdb;
#endif

    cppre            = POWERQUAD->CPPRE;
    POWERQUAD->CPPRE = POWERQUAD_CPPRE_CPPRE_OUT(31);

    int32_t remainderBy8 = length % 8;

#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
            _pq_sin0(valFloat.integerX);
            (void)_pq_readAdd0();
            *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);
        }
    }

    while (length > 0)
    {
        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_sin0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        length -= 8;
    }

#else

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_sin_fx0((uint32_t)(*pSrc++) << 16U);
            *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);
        }
    }

    if (length > 0)
    {
        PQ_StartVectorQ15(pSrc, pDst, length);
        PQ_Vector8Q15(PQ_SIN, 1, PQ_TRIG_FIXED);
        PQ_EndVector();
    }
#endif

    POWERQUAD->CPPRE = cppre;
}

void PQ_VectorCosQ15(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    uint32_t cppre;
#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    pq_float_t magic;
    pq_float_t valFloat;

    magic.integerX = 0x30c90fdbU;
#endif

    cppre            = POWERQUAD->CPPRE;
    POWERQUAD->CPPRE = POWERQUAD_CPPRE_CPPRE_OUT(31);

    int32_t remainderBy8 = length % 8;

#if defined(FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA) && FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA
    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
            _pq_cos0(valFloat.integerX);
            (void)_pq_readAdd0();
            *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);
        }
    }

    while (length > 0)
    {
        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        valFloat.floatX = magic.floatX * (float)(uint32_t)((uint32_t)(*pSrc++) << 16U);
        _pq_cos0(valFloat.integerX);
        (void)_pq_readAdd0();
        *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);

        length -= 8;
    }

#else

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_cos_fx0((uint32_t)(*pSrc++) << 16U);
            *pDst++ = (int16_t)(uint32_t)((_pq_readAdd0_fx()) >> 16U);
        }
    }

    if (length > 0)
    {
        PQ_StartVectorQ15(pSrc, pDst, length);
        PQ_Vector8Q15(PQ_COS, 1, PQ_TRIG_FIXED);
        PQ_EndVector();
    }
#endif

    POWERQUAD->CPPRE = cppre;
}

int32_t PQ_ArctanFixed(POWERQUAD_Type *base, int32_t x, int32_t y, pq_cordic_iter_t iteration)
{
    base->CORDIC_X = (uint32_t)x;
    base->CORDIC_Y = (uint32_t)y;
    base->CORDIC_Z = 0U;
    base->CONTROL  = (CP_CORDIC << 4U) | CORDIC_ARCTAN | CORDIC_ITER(iteration);

    return (int32_t)base->CORDIC_Z;
}

int32_t PQ_ArctanhFixed(POWERQUAD_Type *base, int32_t x, int32_t y, pq_cordic_iter_t iteration)
{
    base->CORDIC_X = (uint32_t)x;
    base->CORDIC_Y = (uint32_t)y;
    base->CORDIC_Z = 0U;
    base->CONTROL  = (CP_CORDIC << 4U) | CORDIC_ARCTANH | CORDIC_ITER(iteration);

    return (int32_t)base->CORDIC_Z;
}

int32_t PQ_Arctan2Fixed(POWERQUAD_Type *base, int32_t x, int32_t y, pq_cordic_iter_t iteration)
{
    int32_t result;

    result = PQ_ArctanFixed(base, x, y, iteration);

    if (x < 0)
    {
        if (y < 0)
        {
            result -= 0x08000000;
        }
        else
        {
            result += 0x08000000;
        }
    }

    return result;
}
