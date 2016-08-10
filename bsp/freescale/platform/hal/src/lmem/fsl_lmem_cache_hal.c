/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#include "fsl_lmem_cache_hal.h"
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_LMEM_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetCodeCacheInvalidateAllCmd
 * Description   : Enable or disable the Processor Code bus option to invalidate all lines.
 *
 * This function enables or disables the Processor Code bus option to invalidate all
 * lines in both WAYs.
 *
 *END**************************************************************************/
void LMEM_HAL_SetCodeCacheInvalidateAllCmd(LMEM_Type * base, bool enable)
{
    LMEM_BWR_PCCCR_INVW0(base, (enable == true));
    LMEM_BWR_PCCCR_INVW1(base, (enable == true));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetCodeCachePushAllCmd
 * Description   : Enable or disable the Processor Code bus option to push all modified lines.
 *
 * This function enables or disables the Processor Code bus option to push all modified
 * lines to both WAYs.
 *
 *END**************************************************************************/
void LMEM_HAL_SetCodeCachePushAllCmd(LMEM_Type * base, bool enable)
{
    LMEM_BWR_PCCCR_PUSHW0(base, (enable == true));
    LMEM_BWR_PCCCR_PUSHW1(base, (enable == true));
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetCodeCacheClearAllCmd
 * Description   : Enable or disable the Processor Code bus option to push and invalidate all
 *                 modified lines.
 *
 * This function enables or disables the Processor Code bus option to push and invalidate all
 * modified lines.
 *
 *END**************************************************************************/
void LMEM_HAL_SetCodeCacheClearAllCmd(LMEM_Type * base, bool enable)
{
    /* To perform a clear, set both invaldiate and push */
    LMEM_BWR_PCCCR_INVW0(base, (enable == true));
    LMEM_BWR_PCCCR_PUSHW0(base, (enable == true));
    LMEM_BWR_PCCCR_INVW1(base, (enable == true));
    LMEM_BWR_PCCCR_PUSHW1(base, (enable == true));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetCodeCacheRegionMode
 * Description   : Sets the cache mode for a specific region for the Processor
 *                 Code bus.
 *
 * This function sets the cache mode for a specific region for the Processor
 * Code bus. Note that you can only demote the cache mode.
 *
 *END**************************************************************************/
void LMEM_HAL_SetCodeCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region,
                                     lmem_cache_mode_t cacheMode)
{
    switch (region)
    {
    case kCacheRegion0:
        LMEM_BWR_PCCRMR_R0(base, cacheMode);
        break;
    case kCacheRegion1:
        LMEM_BWR_PCCRMR_R1(base, cacheMode);
        break;
    case kCacheRegion2:
        LMEM_BWR_PCCRMR_R2(base, cacheMode);
        break;
    case kCacheRegion3:
        LMEM_BWR_PCCRMR_R3(base, cacheMode);
        break;
    case kCacheRegion4:
        LMEM_BWR_PCCRMR_R4(base, cacheMode);
        break;
    case kCacheRegion5:
        LMEM_BWR_PCCRMR_R5(base, cacheMode);
        break;
    case kCacheRegion6:
        LMEM_BWR_PCCRMR_R6(base, cacheMode);
        break;
    case kCacheRegion7:
        LMEM_BWR_PCCRMR_R7(base, cacheMode);
        break;
    case kCacheRegion8:
        LMEM_BWR_PCCRMR_R8(base, cacheMode);
        break;
    case kCacheRegion9:
        LMEM_BWR_PCCRMR_R9(base, cacheMode);
        break;
    case kCacheRegion10:
        LMEM_BWR_PCCRMR_R10(base, cacheMode);
        break;
    case kCacheRegion11:
        LMEM_BWR_PCCRMR_R11(base, cacheMode);
        break;
    case kCacheRegion12:
        LMEM_BWR_PCCRMR_R12(base, cacheMode);
        break;
    case kCacheRegion13:
        LMEM_BWR_PCCRMR_R13(base, cacheMode);
        break;
    case kCacheRegion14:
        LMEM_BWR_PCCRMR_R14(base, cacheMode);
        break;
    case kCacheRegion15:
        LMEM_BWR_PCCRMR_R15(base, cacheMode);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_GetCodeCacheRegionMode
 * Description   : Gets the current cache mode for a specific region for the Processor
 *                 Code bus.
 *
 * This function gets the current cache mode for a specific region for the Processor
 * Code bus.
 *
 *END**************************************************************************/
uint32_t LMEM_HAL_GetCodeCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region)
{
    uint32_t mode;

    switch (region)
    {
    case kCacheRegion0:
        mode =  LMEM_RD_PCCRMR_R0(base);
        break;
    case kCacheRegion1:
        mode = LMEM_RD_PCCRMR_R1(base);
        break;
    case kCacheRegion2:
        mode = LMEM_RD_PCCRMR_R2(base);
        break;
    case kCacheRegion3:
        mode = LMEM_RD_PCCRMR_R3(base);
        break;
    case kCacheRegion4:
        mode = LMEM_RD_PCCRMR_R4(base);
        break;
    case kCacheRegion5:
        mode = LMEM_RD_PCCRMR_R5(base);
        break;
    case kCacheRegion6:
        mode = LMEM_RD_PCCRMR_R6(base);
        break;
    case kCacheRegion7:
        mode = LMEM_RD_PCCRMR_R7(base);
        break;
    case kCacheRegion8:
        mode = LMEM_RD_PCCRMR_R8(base);
        break;
    case kCacheRegion9:
        mode = LMEM_RD_PCCRMR_R9(base);
        break;
    case kCacheRegion10:
        mode = LMEM_RD_PCCRMR_R10(base);
        break;
    case kCacheRegion11:
        mode = LMEM_RD_PCCRMR_R11(base);
        break;
    case kCacheRegion12:
        mode = LMEM_RD_PCCRMR_R12(base);
        break;
    case kCacheRegion13:
        mode = LMEM_RD_PCCRMR_R13(base);
        break;
    case kCacheRegion14:
        mode = LMEM_RD_PCCRMR_R14(base);
        break;
    case kCacheRegion15:
        mode = LMEM_RD_PCCRMR_R15(base);
        break;
    default:
        mode = 0;
        break;
    }

    return mode;
}

#if FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetSystemCacheInvalidateAllCmd
 * Description   : Enable or disable the Processor System bus option to invalidate all lines.
 *
 * This function enables or disables the Processor System bus option to invalidate all
 * lines in both WAYs.
 *
 *END**************************************************************************/
void LMEM_HAL_SetSystemCacheInvalidateAllCmd(LMEM_Type * base, bool enable)
{
    LMEM_BWR_PSCCR_INVW0(base, (enable == true));
    LMEM_BWR_PSCCR_INVW1(base, (enable == true));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetSystemCachePushAllCmd
 * Description   : Enable or disable the Processor System bus option to push all modified lines.
 *
 * This function enables or disables the Processor System bus option to push all
 * modified lines to both WAYs.
 *
 *END**************************************************************************/
void LMEM_HAL_SetSystemCachePushAllCmd(LMEM_Type * base, bool enable)
{
    LMEM_BWR_PSCCR_PUSHW0(base, (enable == true));
    LMEM_BWR_PSCCR_PUSHW1(base, (enable == true));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetSystemCacheClearAllCmd
 * Description   : Enable or disable the Processor System bus option to push and invalidate all
 *                 modified lines.
 *
 * This function enables or disables the Processor System bus option to push and invalidate all
 * modified lines to both WAYs.
 *
 *END**************************************************************************/
void LMEM_HAL_SetSystemCacheClearAllCmd(LMEM_Type * base, bool enable)
{
    /* To perform a clear, set both invaldiate and push */
    LMEM_BWR_PSCCR_INVW0(base, (enable == true));
    LMEM_BWR_PSCCR_PUSHW0(base, (enable == true));
    LMEM_BWR_PSCCR_INVW1(base, (enable == true));
    LMEM_BWR_PSCCR_PUSHW1(base, (enable == true));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_SetSystemCacheRegionMode
 * Description   : Sets the cache mode for a specific region for the Processor
 *                 System bus.
 *
 * This function sets the cache mode for a specific region for the Processor
 * System bus. Note that you can only demote the cache mode.
 *
 *END**************************************************************************/
void LMEM_HAL_SetSystemCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region,
                                       lmem_cache_mode_t cacheMode)
{
    switch (region)
    {
    case kCacheRegion0:
        LMEM_BWR_PSCRMR_R0(base, cacheMode);
        break;
    case kCacheRegion1:
        LMEM_BWR_PSCRMR_R1(base, cacheMode);
        break;
    case kCacheRegion2:
        LMEM_BWR_PSCRMR_R2(base, cacheMode);
        break;
    case kCacheRegion3:
        LMEM_BWR_PSCRMR_R3(base, cacheMode);
        break;
    case kCacheRegion4:
        LMEM_BWR_PSCRMR_R4(base, cacheMode);
        break;
    case kCacheRegion5:
        LMEM_BWR_PSCRMR_R5(base, cacheMode);
        break;
    case kCacheRegion6:
        LMEM_BWR_PSCRMR_R6(base, cacheMode);
        break;
    case kCacheRegion7:
        LMEM_BWR_PSCRMR_R7(base, cacheMode);
        break;
    case kCacheRegion8:
        LMEM_BWR_PSCRMR_R8(base, cacheMode);
        break;
    case kCacheRegion9:
        LMEM_BWR_PSCRMR_R9(base, cacheMode);
        break;
    case kCacheRegion10:
        LMEM_BWR_PSCRMR_R10(base, cacheMode);
        break;
    case kCacheRegion11:
        LMEM_BWR_PSCRMR_R11(base, cacheMode);
        break;
    case kCacheRegion12:
        LMEM_BWR_PSCRMR_R12(base, cacheMode);
        break;
    case kCacheRegion13:
        LMEM_BWR_PSCRMR_R13(base, cacheMode);
        break;
    case kCacheRegion14:
        LMEM_BWR_PSCRMR_R14(base, cacheMode);
        break;
    case kCacheRegion15:
        LMEM_BWR_PSCRMR_R15(base, cacheMode);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_HAL_GetSystemCacheRegionMode
 * Description   : Gets the current cache mode for a specific region for the Processor
 *                 System bus.
 *
 * This function gets the current cache mode for a specific region for the Processor
 * System bus.
 *
 *END**************************************************************************/
uint32_t LMEM_HAL_GetSystemCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region)
{
    uint32_t val = 0;
    switch (region)
    {
    case kCacheRegion0:
        val = LMEM_RD_PSCRMR_R0(base);
        break;
    case kCacheRegion1:
        val = LMEM_RD_PSCRMR_R1(base);
        break;
    case kCacheRegion2:
        val = LMEM_RD_PSCRMR_R2(base);
        break;
    case kCacheRegion3:
        val = LMEM_RD_PSCRMR_R3(base);
        break;
    case kCacheRegion4:
        val = LMEM_RD_PSCRMR_R4(base);
        break;
    case kCacheRegion5:
        val = LMEM_RD_PSCRMR_R5(base);
        break;
    case kCacheRegion6:
        val = LMEM_RD_PSCRMR_R6(base);
        break;
    case kCacheRegion7:
        val = LMEM_RD_PSCRMR_R7(base);
        break;
    case kCacheRegion8:
        val = LMEM_RD_PSCRMR_R8(base);
        break;
    case kCacheRegion9:
        val = LMEM_RD_PSCRMR_R9(base);
        break;
    case kCacheRegion10:
        val = LMEM_RD_PSCRMR_R10(base);
        break;
    case kCacheRegion11:
        val = LMEM_RD_PSCRMR_R11(base);
        break;
    case kCacheRegion12:
        val = LMEM_RD_PSCRMR_R12(base);
        break;
    case kCacheRegion13:
        val = LMEM_RD_PSCRMR_R13(base);
        break;
    case kCacheRegion14:
        val = LMEM_RD_PSCRMR_R14(base);
        break;
    case kCacheRegion15:
        val = LMEM_RD_PSCRMR_R15(base);
        break;
    default:
        break;
    }
    return val;
}

#endif /* FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE */

#endif /* FSL_FEATURE_SOC_LMEM_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

