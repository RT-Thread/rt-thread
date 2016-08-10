
/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_trng_hal.h"
#if FSL_FEATURE_SOC_TRNG_COUNT

/* Most of TRNG HAL is defined in fsl_trng_hal.h */


/*!
 * @brief Initializes the TRNG module.
 *
 * This function initializes the TRNG to a default state.
 */
void TRNG_HAL_Init(TRNG_Type * base)
{
    /* Must be in program mode.*/
    TRNG_HAL_SetWorkingMode(base, kTRNGWorkModeProgram);

    /* Reset Defaults.*/
    TRNG_BWR_MCTL_RST_DEF(base, 1);
}

/*!
 * @brief Enables the TRNG module.
 *
 * This function enables the TRNG random data generation and loading.
 */
void TRNG_HAL_Enable(TRNG_Type * base)
{
    /* Set to Run mode.*/
    TRNG_HAL_SetWorkingMode(base, kTRNGWorkModeRun);
    
    /* Enable TRNG Access Mode. To generate an Entropy
     * value that can be read via the true0-true15 registers.*/
    TRNG_BWR_MCTL_TRNG_ACC(base, 1);
}

/*!
 * @brief Sets statistical check limits.
 *
 * This function is used to set minimum and maximum limits of statistical checks.
 *
 */
trng_status_t  TRNG_HAL_SetStatisticalCheckLimit(TRNG_Type * base, trng_statistical_check_t statistical_check, const trng_statistical_check_limit_t *limit )
{
    uint32_t        range;
    trng_status_t   status = kStatus_TRNG_Success;

    if(limit && (limit->maximum > limit->minimum))
    {
        range = limit->maximum - limit->minimum; /* Registers use range instead of minimum value.*/

        switch(statistical_check)
        {
            case kTRNGStatisticalCheckMonobit:/* Allowable maximum and minimum number of ones/zero detected during entropy generation. */
                if((range <= 0xffff) && (limit->maximum <= 0xffff))
                {
                    TRNG_BWR_SCML_MONO_MAX(base, limit->maximum);
                    TRNG_BWR_SCML_MONO_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckRunBit1:/* Allowable maximum and minimum number of runs of length 1 detected during entropy generation. */
                if((range <= 0x7fff) && (limit->maximum <= 0x7fff))
                {
                    TRNG_BWR_SCR1L_RUN1_MAX(base, limit->maximum);
                    TRNG_BWR_SCR1L_RUN1_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckRunBit2:/* Allowable maximum and minimum number of runs of length 2 detected during entropy generation. */
                if((range <= 0x3fff) && (limit->maximum <= 0x3fff))
                {        
                    TRNG_BWR_SCR2L_RUN2_MAX(base, limit->maximum);
                    TRNG_BWR_SCR2L_RUN2_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckRunBit3:/* Allowable maximum and minimum number of runs of length 3 detected during entropy generation. */
                if((range <= 0x1fff) && (limit->maximum <= 0x1fff))
                {
                    TRNG_BWR_SCR3L_RUN3_MAX(base, limit->maximum);
                    TRNG_BWR_SCR3L_RUN3_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckRunBit4:/* Allowable maximum and minimum number of runs of length 4 detected during entropy generation. */
                if((range <= 0xfff) && (limit->maximum <= 0xfff))
                {
                    TRNG_BWR_SCR4L_RUN4_MAX(base, limit->maximum);
                    TRNG_BWR_SCR4L_RUN4_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckRunBit5:/* Allowable maximum and minimum number of runs of length 5 detected during entropy generation. */
                if((range <= 0x7ff) && (limit->maximum <= 0x7ff))
                {
                    TRNG_BWR_SCR5L_RUN5_MAX(base, limit->maximum);
                    TRNG_BWR_SCR5L_RUN5_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckRunBit6Plus:/* Allowable maximum and minimum number of length 6 or more detected during entropy generation */
                if((range <= 0x7ff) && (limit->maximum <= 0x7ff))
                {
                    TRNG_BWR_SCR6PL_RUN6P_MAX(base, limit->maximum);
                    TRNG_BWR_SCR6PL_RUN6P_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckPoker:/* Allowable maximum and minimum limit of "Poker Test" detected during entropy generation . */
                if((range <= 0xffff) && (limit->maximum <= 0xffffff))
                {
                    TRNG_BWR_PKRMAX_PKR_MAX(base, limit->maximum);
                    TRNG_BWR_PKRRNG_PKR_RNG(base, range);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            case kTRNGStatisticalCheckFrequencyCount: /* Allowable maximum and minimum limit of entropy sample frquency count during entropy generation . */
                if((limit->minimum <= 0x3fffff) && (limit->maximum <= 0x3fffff))
                {
                    TRNG_BWR_FRQMAX_FRQ_MAX(base, limit->maximum);
                    TRNG_BWR_FRQMIN_FRQ_MIN(base, limit->minimum);
                }
                else
                {
                    status = kStatus_TRNG_InvalidArgument;
                }
                break;
            default:
                status = kStatus_TRNG_InvalidArgument;
                break;
        }
    }

    return status;
}

/*!
 * @brief Gets statistical check limits.
 *
 * This function is used to get current setting of minimum and maximum limits of statistical checks.
 *
 */
void TRNG_HAL_GetStatisticalCheckLimit(TRNG_Type * base, trng_statistical_check_t statistical_check, trng_statistical_check_limit_t *limit )
{
    uint32_t range;
    uint32_t max;

    if(limit)
    {
        switch(statistical_check)
        {
            case kTRNGStatisticalCheckMonobit:/* Allowable maximum and minimum number of ones/zero detected during entropy generation. */
                max = TRNG_BRD_SCML_MONO_MAX(base);
                range = TRNG_BRD_SCML_MONO_RNG(base);
                break;
            case kTRNGStatisticalCheckRunBit1:/* Allowable maximum and minimum number of runs of length 1 detected during entropy generation. */
                max = TRNG_BRD_SCR1L_RUN1_MAX(base);
                range = TRNG_BRD_SCR1L_RUN1_RNG(base);
                break;
            case kTRNGStatisticalCheckRunBit2:/* Allowable maximum and minimum number of runs of length 2 detected during entropy generation. */
                max = TRNG_BRD_SCR2L_RUN2_MAX(base);
                range = TRNG_BRD_SCR2L_RUN2_RNG(base);
                break;
            case kTRNGStatisticalCheckRunBit3:/* Allowable maximum and minimum number of runs of length 3 detected during entropy generation. */
                max = TRNG_BRD_SCR3L_RUN3_MAX(base);
                range = TRNG_BRD_SCR3L_RUN3_RNG(base);
                break;
            case kTRNGStatisticalCheckRunBit4:/* Allowable maximum and minimum number of runs of length 4 detected during entropy generation. */
                max = TRNG_BRD_SCR4L_RUN4_MAX(base);
                range = TRNG_BRD_SCR4L_RUN4_RNG(base);
                break;
            case kTRNGStatisticalCheckRunBit5:/* Allowable maximum and minimum number of runs of length 5 detected during entropy generation. */
                max = TRNG_BRD_SCR5L_RUN5_MAX(base);
                range = TRNG_BRD_SCR5L_RUN5_RNG(base);
                break;
            case kTRNGStatisticalCheckRunBit6Plus:/* Allowable maximum and minimum number of length 6 or more detected during entropy generation */
                max = TRNG_BRD_SCR6PL_RUN6P_MAX(base);
                range = TRNG_BRD_SCR6PL_RUN6P_RNG(base);
                break;
            case kTRNGStatisticalCheckPoker:/* Allowable maximum and minimum limit of "Poker Test" detected during entropy generation . */
                max = TRNG_BRD_PKRMAX_PKR_MAX(base);
                range = TRNG_BRD_PKRRNG_PKR_RNG(base);
                break;
            case kTRNGStatisticalCheckFrequencyCount: /* Allowable maximum and minimum limit of entropy sample frquency count during entropy generation . */
                max = TRNG_BRD_FRQMAX_FRQ_MAX(base);
                range = max - TRNG_BRD_FRQMIN_FRQ_MIN(base);
                break;
            default:
                return;
        }
    
        /* Return values. */
        limit->maximum = max;
        limit->minimum = max - range;
    }
}

/*!
 * @brief Enables or disables the related TRNG interrupt
 * 
 * This function enables or disables interrupts that are generated by the TRNG.
*/
void TRNG_HAL_SetIntMode(TRNG_Type * base, trng_interrupt_t interrupt, bool enable)
{
    if (enable)
    {
        TRNG_SET_INT_MASK(base, (uint32_t)interrupt);   /* Enable interrupt */
    }
    else
    {
        TRNG_CLR_INT_MASK(base, (uint32_t)interrupt);   /* Disable interrupt*/
    }
}

/*!
 * @brief Gets a entry data from the TRNG. 
 *
 * This function gets an entropy data from TRNG.
 * Entropy data is spread over TRNG_ENT_COUNT registers. 
 * Read register number is defined by index parameter.
 * Entropy data is valid only if TRNG_HAL_GetEntropyValidCmd() returns 1.
*/
uint32_t TRNG_HAL_ReadEntropy(TRNG_Type * base, uint32_t index)
{
    uint32_t data;

    index = index % TRNG_ENT_COUNT; /* This way we can use incremental index without limit control from application.*/

    data = TRNG_RD_ENT(base, index);
    
    if(index == (TRNG_ENT_COUNT-1) )
    {
        /* Dummy read. Defect workaround.
         * TRNG could not clear ENT_VAL  flag automatically, application 
         * had to do a dummy reading operation for anyone TRNG register 
         * to clear it firstly, then to read the RTENT0 to RTENT15 again */
        index = TRNG_RD_ENT(base, 0);
    }

    return data;
}

/*!
 * @brief Gets the TRNG status. 
 *
 * This function gets current status after TRNG entropy generation.
*/
trng_status_t TRNG_HAL_GetStatus(TRNG_Type * base)
{
    trng_status_t status = kStatus_TRNG_Success;

    /* Check HW error.*/
    if(TRNG_HAL_GetErrorCmd(base))
    {
        status = (trng_status_t)((unsigned)status | kStatus_TRNG_Error);            /* TRNG module error occurred */

        if(TRNG_BRD_STATUS_TF1BR0(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit1Sampling0);
        }
        if(TRNG_BRD_STATUS_TF1BR1(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit1Sampling1);
        }
        if(TRNG_BRD_STATUS_TF2BR0(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit2Sampling0);
        }
        if(TRNG_BRD_STATUS_TF2BR1(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit2Sampling1);
        }
        if(TRNG_BRD_STATUS_TF3BR0(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit3Sampling0);
        }
        if(TRNG_BRD_STATUS_TF3BR1(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit3Sampling1);
        }
        if(TRNG_BRD_STATUS_TF4BR0(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit4Sampling0);
        }
        if(TRNG_BRD_STATUS_TF4BR1(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit4Sampling1);
        }
        if(TRNG_BRD_STATUS_TF5BR0(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit5Sampling0);
        }
        if(TRNG_BRD_STATUS_TF5BR1(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit5Sampling1);
        }
        if(TRNG_BRD_STATUS_TF6PBR0(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit6PlusSampling0);
        }
        if(TRNG_BRD_STATUS_TF6PBR1(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailRunBit6PlusSampling1);
        }
        if(TRNG_BRD_STATUS_TFSB(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailSparseBit);
        }
        if(TRNG_BRD_STATUS_TFLR(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailLongRun);
        }
        if(TRNG_BRD_STATUS_TFP(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailPoker);
        }
        if(TRNG_BRD_STATUS_TFMB(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailMonoBit);
        }
        if(TRNG_BRD_MCTL_FCT_FAIL(base))
        {
            status = (trng_status_t)((unsigned)status | kStatus_TRNG_TestFailFrequencyCount);
        }
    }

    return status;
}

/*!
 * @brief Sets the TRNG retry count.
 * 
 * This function sets the retry counter which defines the number of times a 
 * statistical check may fails during the TRNG Entropy Generation before
 * generating an error.
*/
trng_status_t TRNG_HAL_SetRetryCount(TRNG_Type * base, uint8_t retry_count)
{
    trng_status_t   status;

    if((retry_count>=1) && (retry_count <=15))
    {
        /* Set retry count.*/
        TRNG_BWR_SCMISC_RTY_CT(base, retry_count);
        status = kStatus_TRNG_Success;
    }
    else
    {
        status = kStatus_TRNG_InvalidArgument;
    }
    return status;
}


#endif
/*******************************************************************************
 * EOF
 *******************************************************************************/
