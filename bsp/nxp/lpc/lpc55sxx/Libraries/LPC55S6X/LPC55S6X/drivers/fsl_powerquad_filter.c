/*
 * Copyright 2018-2022 NXP
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
#define FSL_COMPONENT_ID "platform.drivers.powerquad_filter"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void PQ_VectorBiqaudDf2F32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            val.floatX = *pSrc++;
            _pq_biquad0(val.integerX);
            val.integerX = _pq_readAdd0();
            *pDst++      = val.floatX;
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8BiquadDf2F32();
        PQ_EndVector();
    }
}

void PQ_VectorBiqaudDf2Fixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_biquad0_fx(*pSrc++);
            *pDst++ = (int32_t)_pq_readAdd0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVector(pSrc, pDst, length);
        PQ_Vector8BiquadDf2Fixed32();
        PQ_EndVector();
    }
}

void PQ_VectorBiqaudDf2Fixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;
        while ((remainderBy8--) > 0)
        {
            _pq_biquad0_fx(*pSrc++);
            *pDst++ = (int16_t)_pq_readAdd0_fx();
        }
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(pSrc, pDst, length);
        PQ_Vector8BiquadDf2Fixed16();
        PQ_EndVector();
    }
}

void PQ_VectorBiqaudCascadeDf2F32(float *pSrc, float *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;
    pq_float_t val;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;

        PQ_Biquad1F32(&pSrc[0], &pDst[0]);

        for (int i = 1; i < remainderBy8; i++)
        {
            val.floatX = pSrc[i - 1];
            _pq_biquad0(val.integerX);

            val.floatX = pSrc[i];
            _pq_biquad1(val.integerX);

            val.integerX = _pq_readAdd0();
            pDst[i - 1]  = val.floatX;

            val.integerX = _pq_readAdd1();
            pDst[i]      = val.floatX;
        }

        PQ_BiquadF32(&pSrc[remainderBy8 - 1], &pDst[remainderBy8 - 1]);
    }

    if (length > 0)
    {
        PQ_StartVector(&pSrc[remainderBy8], &pDst[remainderBy8], length);
        PQ_Vector8BiqaudDf2CascadeF32();
        PQ_EndVector();
    }
}

void PQ_VectorBiqaudCascadeDf2Fixed32(int32_t *pSrc, int32_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;

        _pq_biquad1_fx(pSrc[0]);
        pDst[0] = (int32_t)_pq_readAdd1_fx();

        for (int i = 1; i < remainderBy8; i++)
        {
            _pq_biquad0_fx(pSrc[i - 1]);
            _pq_biquad1_fx(pSrc[i]);
            pDst[i - 1] = (int32_t)_pq_readAdd0_fx();
            pDst[i]     = (int32_t)_pq_readAdd1_fx();
        }

        _pq_biquad0_fx(pSrc[remainderBy8 - 1]);
        pDst[remainderBy8 - 1] = (int32_t)_pq_readAdd0_fx();
    }

    if (length > 0)
    {
        PQ_StartVector(&pSrc[remainderBy8], &pDst[remainderBy8], length);
        PQ_Vector8BiqaudDf2CascadeFixed32();
        PQ_EndVector();
    }
}

void PQ_VectorBiqaudCascadeDf2Fixed16(int16_t *pSrc, int16_t *pDst, int32_t length)
{
    int32_t remainderBy8 = length % 8;

    if (remainderBy8 > 0)
    {
        length -= remainderBy8;

        _pq_biquad1_fx(pSrc[0]);
        pDst[0] = (int16_t)_pq_readAdd1_fx();

        for (int i = 1; i < remainderBy8; i++)
        {
            _pq_biquad0_fx(pSrc[i - 1]);
            _pq_biquad1_fx(pSrc[i]);
            pDst[i - 1] = (int16_t)_pq_readAdd0_fx();
            pDst[i]     = (int16_t)_pq_readAdd1_fx();
        }

        _pq_biquad0_fx(pSrc[remainderBy8 - 1]);
        pDst[remainderBy8 - 1] = (int16_t)_pq_readAdd0_fx();
    }

    if (length > 0)
    {
        PQ_StartVectorFixed16(&pSrc[remainderBy8], &pDst[remainderBy8], length);
        PQ_Vector8BiqaudDf2CascadeFixed16();
        PQ_EndVector();
    }
}

void PQ_BiquadBackUpInternalState(POWERQUAD_Type *base, int32_t biquad_num, pq_biquad_state_t *state)
{
    pq_float_t v_n_1;
    pq_float_t v_n;

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
    if (0 == biquad_num)
    {
        v_n_1.integerX = base->GPREG[0];
        v_n.integerX   = base->GPREG[1];

        state->param.v_n_1 = v_n_1.floatX;
        state->param.v_n   = v_n.floatX;
        state->compreg     = base->COMPREG[1];
    }
    else
    {
        v_n_1.integerX = base->GPREG[8];
        v_n.integerX   = base->GPREG[9];

        state->param.v_n_1 = v_n_1.floatX;
        state->param.v_n   = v_n.floatX;
        state->compreg     = base->COMPREG[3];
    }
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
}

void PQ_BiquadRestoreInternalState(POWERQUAD_Type *base, int32_t biquad_num, pq_biquad_state_t *state)
{
    pq_float_t v_n_1;
    pq_float_t v_n;
    pq_float_t a_1;
    pq_float_t a_2;
    pq_float_t b_0;
    pq_float_t b_1;
    pq_float_t b_2;

    if (0 == biquad_num)
    {
        v_n_1.floatX = state->param.v_n_1;
        v_n.floatX   = state->param.v_n;
        a_1.floatX   = state->param.a_1;
        a_2.floatX   = state->param.a_2;
        b_0.floatX   = state->param.b_0;
        b_1.floatX   = state->param.b_1;
        b_2.floatX   = state->param.b_2;

        base->GPREG[0]   = v_n_1.integerX;
        base->GPREG[1]   = v_n.integerX;
        base->GPREG[2]   = a_1.integerX;
        base->GPREG[3]   = a_2.integerX;
        base->GPREG[4]   = b_0.integerX;
        base->GPREG[5]   = b_1.integerX;
        base->GPREG[6]   = b_2.integerX;
        base->COMPREG[1] = state->compreg;
    }
    else
    {
        v_n_1.floatX = state->param.v_n_1;
        v_n.floatX   = state->param.v_n;
        a_1.floatX   = state->param.a_1;
        a_2.floatX   = state->param.a_2;
        b_0.floatX   = state->param.b_0;
        b_1.floatX   = state->param.b_1;
        b_2.floatX   = state->param.b_2;

        base->GPREG[8]   = v_n_1.integerX;
        base->GPREG[9]   = v_n.integerX;
        base->GPREG[10]  = a_1.integerX;
        base->GPREG[11]  = a_2.integerX;
        base->GPREG[12]  = b_0.integerX;
        base->GPREG[13]  = b_1.integerX;
        base->GPREG[14]  = b_2.integerX;
        base->COMPREG[3] = state->compreg;
    }
}

void PQ_FIR(POWERQUAD_Type *base,
            const void *pAData,
            int32_t ALength,
            const void *pBData,
            int32_t BLength,
            void *pResult,
            uint32_t opType)
{
    assert(NULL != pAData);
    assert(NULL != pBData);
    assert(NULL != pResult);

    base->INABASE = (uint32_t)(const uint32_t *)pAData;
    base->INBBASE = (uint32_t)(const uint32_t *)pBData;
    base->LENGTH  = ((uint32_t)BLength << 16U) + (uint32_t)ALength;
    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->CONTROL = (CP_FIR << 4U) | opType;
}

void PQ_FIRIncrement(POWERQUAD_Type *base, int32_t ALength, int32_t BLength, int32_t xOffset)
{
    base->MISC    = (uint32_t)xOffset;
    base->LENGTH  = ((uint32_t)BLength << 16U) + (uint32_t)ALength;
    base->CONTROL = (CP_FIR << 4U) | PQ_FIR_INCREMENTAL;
}

void PQ_BiquadCascadeDf2Init(pq_biquad_cascade_df2_instance *S, uint8_t numStages, pq_biquad_state_t *pState)
{
    S->numStages = numStages;
    S->pState    = pState;
}

void PQ_BiquadCascadeDf2F32(const pq_biquad_cascade_df2_instance *S, float *pSrc, float *pDst, uint32_t blockSize)
{
    uint32_t stage            = S->numStages;
    pq_biquad_state_t *states = S->pState;

    if (pDst != pSrc)
    {
        (void)memcpy(pDst, pSrc, 4U * blockSize);
    }

    if (stage % 2U != 0U)
    {
        PQ_BiquadRestoreInternalState(POWERQUAD, 0, states);

        PQ_VectorBiqaudDf2F32(pSrc, pDst, (int32_t)blockSize);

        PQ_BiquadBackUpInternalState(POWERQUAD, 0, states);

        states++;
        stage--;
    }

    do
    {
        PQ_BiquadRestoreInternalState(POWERQUAD, 1, states);
        states++;
        PQ_BiquadRestoreInternalState(POWERQUAD, 0, states);

        PQ_VectorBiqaudCascadeDf2F32(pDst, pDst, (int32_t)blockSize);

        states--;
        PQ_BiquadBackUpInternalState(POWERQUAD, 1, states);
        states++;
        PQ_BiquadBackUpInternalState(POWERQUAD, 0, states);

        states++;
        stage -= 2U;

    } while (stage > 0U);
}

void PQ_BiquadCascadeDf2Fixed32(const pq_biquad_cascade_df2_instance *S,
                                int32_t *pSrc,
                                int32_t *pDst,
                                uint32_t blockSize)
{
    uint32_t stage            = S->numStages;
    pq_biquad_state_t *states = S->pState;

    if (pDst != pSrc)
    {
        (void)memcpy(pDst, pSrc, 4U * blockSize);
    }

    if (stage % 2U != 0U)
    {
        PQ_BiquadRestoreInternalState(POWERQUAD, 0, states);

        PQ_VectorBiqaudDf2Fixed32(pSrc, pDst, (int32_t)blockSize);

        PQ_BiquadBackUpInternalState(POWERQUAD, 0, states);

        states++;
        stage--;
    }

    do
    {
        PQ_BiquadRestoreInternalState(POWERQUAD, 0, states);
        states++;
        PQ_BiquadRestoreInternalState(POWERQUAD, 1, states);

        PQ_VectorBiqaudCascadeDf2Fixed32(pDst, pDst, (int32_t)blockSize);

        states--;
        PQ_BiquadBackUpInternalState(POWERQUAD, 0, states);
        states++;
        PQ_BiquadBackUpInternalState(POWERQUAD, 1, states);

        states++;
        stage -= 2U;
    } while (stage > 0U);
}

void PQ_BiquadCascadeDf2Fixed16(const pq_biquad_cascade_df2_instance *S,
                                int16_t *pSrc,
                                int16_t *pDst,
                                uint32_t blockSize)
{
    uint32_t stage            = S->numStages;
    pq_biquad_state_t *states = S->pState;

    if (pDst != pSrc)
    {
        (void)memcpy(pDst, pSrc, 2U * blockSize);
    }

    if (stage % 2U != 0U)
    {
        PQ_BiquadRestoreInternalState(POWERQUAD, 0, states);

        PQ_VectorBiqaudDf2Fixed16(pSrc, pDst, (int32_t)blockSize);

        PQ_BiquadBackUpInternalState(POWERQUAD, 0, states);

        states++;
        stage--;
    }

    do
    {
        PQ_BiquadRestoreInternalState(POWERQUAD, 0, states);
        states++;
        PQ_BiquadRestoreInternalState(POWERQUAD, 1, states);

        PQ_VectorBiqaudCascadeDf2Fixed16(pDst, pDst, (int32_t)blockSize);

        states--;
        PQ_BiquadBackUpInternalState(POWERQUAD, 0, states);
        states++;
        PQ_BiquadBackUpInternalState(POWERQUAD, 1, states);

        states++;
        stage -= 2U;
    } while (stage > 0U);
}
