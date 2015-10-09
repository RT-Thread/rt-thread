/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Table of base addresses for instances. */
SIM_Type * const g_simBase[] = SIM_BASE_PTRS;
#if FSL_FEATURE_SOC_MCGLITE_COUNT || FSL_FEATURE_SOC_MCG_COUNT
MCG_Type * const g_mcgBase[] = MCG_BASE_PTRS;
#endif

#if (defined(FSL_FEATURE_SOC_SCG_COUNT) && FSL_FEATURE_SOC_SCG_COUNT)
const uint32_t g_scgBase[] = SCG_BASE_PTRS;
#endif

#if ((!(defined(FSL_FEATURE_SOC_SCG_COUNT) && FSL_FEATURE_SOC_SCG_COUNT)) \
       && FSL_FEATURE_SOC_OSC_COUNT)
OSC_Type * const g_oscBase[] = OSC_BASE_PTRS; 
#endif

#if (defined(FSL_FEATURE_SOC_PCC_COUNT) && FSL_FEATURE_SOC_PCC_COUNT)
PCC_Type * const g_pccBase[] = PCC_BASE_PTRS; 
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

