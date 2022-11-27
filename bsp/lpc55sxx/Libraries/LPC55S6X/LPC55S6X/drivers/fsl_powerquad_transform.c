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
#define FSL_COMPONENT_ID "platform.drivers.powerquad_transform"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void PQ_TransformCFFT(POWERQUAD_Type *base, uint32_t length, void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pData;
    base->LENGTH  = length;
    base->CONTROL = (CP_FFT << 4U) | PQ_TRANS_CFFT;
}

void PQ_TransformRFFT(POWERQUAD_Type *base, uint32_t length, void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);

    /* Set 0's for imaginary inputs as not be reading them in by the machine */
    base->GPREG[1]  = 0U;
    base->GPREG[3]  = 0U;
    base->GPREG[5]  = 0U;
    base->GPREG[7]  = 0U;
    base->GPREG[9]  = 0U;
    base->GPREG[11] = 0U;
    base->GPREG[13] = 0U;
    base->GPREG[15] = 0U;
    base->OUTBASE   = (uint32_t)(uint32_t *)pResult;
    base->INABASE   = (uint32_t)(uint32_t *)pData;
    base->LENGTH    = length;
    base->CONTROL   = (CP_FFT << 4U) | PQ_TRANS_RFFT;
}

void PQ_TransformIFFT(POWERQUAD_Type *base, uint32_t length, void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pData;
    base->LENGTH  = length;
    base->CONTROL = (CP_FFT << 4U) | PQ_TRANS_IFFT;
}

void PQ_TransformCDCT(POWERQUAD_Type *base, uint32_t length, void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pData;
    base->LENGTH  = length;
    base->CONTROL = (CP_FFT << 4U) | PQ_TRANS_CDCT;
}

void PQ_TransformRDCT(POWERQUAD_Type *base, uint32_t length, void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);

    base->GPREG[1]  = 0U;
    base->GPREG[3]  = 0U;
    base->GPREG[5]  = 0U;
    base->GPREG[7]  = 0U;
    base->GPREG[9]  = 0U;
    base->GPREG[11] = 0U;
    base->GPREG[13] = 0U;
    base->GPREG[15] = 0U;
    base->OUTBASE   = (uint32_t)(uint32_t *)pResult;
    base->INABASE   = (uint32_t)(uint32_t *)pData;
    base->LENGTH    = length;
    base->CONTROL   = (CP_FFT << 4U) | PQ_TRANS_RDCT;
}

void PQ_TransformIDCT(POWERQUAD_Type *base, uint32_t length, void *pData, void *pResult)
{
    assert(NULL != pData);
    assert(NULL != pResult);

    base->OUTBASE = (uint32_t)(uint32_t *)pResult;
    base->INABASE = (uint32_t)(uint32_t *)pData;
    base->LENGTH  = length;
    base->CONTROL = (CP_FFT << 4U) | PQ_TRANS_IDCT;
}
