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
#define FSL_COMPONENT_ID "platform.drivers.powerquad_matrix"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void PQ_MatrixAddition(POWERQUAD_Type *base, uint32_t length, void *pAData, void *pBData, void *pResult)
{
    assert(NULL != pAData);
    assert(NULL != pBData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pAData;
    base->INBBASE = (uint32_t)(uint32_t *)pBData;
    base->LENGTH  = length;
    base->CONTROL = (CP_MTX << 4U) | PQ_MTX_ADD;
}

void PQ_MatrixSubtraction(POWERQUAD_Type *base, uint32_t length, void *pAData, void *pBData, void *pResult)
{
    assert(NULL != pAData);
    assert(NULL != pBData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pAData;
    base->INBBASE = (uint32_t)(uint32_t *)pBData;
    base->LENGTH  = length;
    base->CONTROL = (CP_MTX << 4U) | PQ_MTX_SUB;
}

void PQ_MatrixMultiplication(POWERQUAD_Type *base, uint32_t length, void *pAData, void *pBData, void *pResult)
{
    assert(NULL != pAData);
    assert(NULL != pBData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pAData;
    base->INBBASE = (uint32_t)(uint32_t *)pBData;
    base->LENGTH  = length;
    base->CONTROL = (CP_MTX << 4U) | PQ_MTX_MULT;
}

void PQ_MatrixProduct(POWERQUAD_Type *base, uint32_t length, void *pAData, void *pBData, void *pResult)
{
    assert(NULL != pAData);
    assert(NULL != pBData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pAData;
    base->INBBASE = (uint32_t)(uint32_t *)pBData;
    base->LENGTH  = length;
    base->CONTROL = (CP_MTX << 4U) | PQ_MTX_PROD;
}

void PQ_VectorDotProduct(POWERQUAD_Type *base, uint32_t length, void *pAData, void *pBData, void *pResult)
{
    assert(NULL != pAData);
    assert(NULL != pBData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pAData;
    base->INBBASE = (uint32_t)(uint32_t *)pBData;
    base->LENGTH  = length;
    base->CONTROL = (CP_MTX << 4U) | PQ_VEC_DOTP;
}

void PQ_MatrixInversion(POWERQUAD_Type *base, uint32_t length, void *pData, void *pTmpData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pTmpData);
    assert(NULL != pResult);

    /* Workaround:
     *
     * Matrix inv depends on the coproc 1/x function, this puts coproc to right state.
     */
    _pq_inv0(1.0f);

    base->INABASE = (uint32_t)(uint32_t *)pData;
    base->TMPBASE = (uint32_t)(uint32_t *)pTmpData;
    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->LENGTH  = length;
    base->CONTROL = (CP_MTX << 4U) | PQ_MTX_INV;
}

void PQ_MatrixTranspose(POWERQUAD_Type *base, uint32_t length, void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pData;
    base->LENGTH  = length;
    base->CONTROL = (CP_MTX << 4U) | PQ_MTX_TRAN;
}

void PQ_MatrixScale(POWERQUAD_Type *base, uint32_t length, float misc, const void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);
    pq_float_t val;

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(const uint32_t *)pData;
    base->LENGTH  = length;

    val.floatX = misc;
    base->MISC = val.integerX;

    base->CONTROL = (CP_MTX << 4U) | PQ_MTX_SCALE;
}
