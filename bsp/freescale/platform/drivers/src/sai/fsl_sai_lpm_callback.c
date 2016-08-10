/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

// Standard C Included Files
#include <stdio.h>
#include <stdint.h>

// SDK Included Files
#include "fsl_power_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_I2S_COUNT

power_manager_error_code_t sai_pm_callback(power_manager_notify_struct_t * notify,
 power_manager_callback_data_t * dataPtr)
{
    power_manager_error_code_t result = kPowerManagerSuccess;

    switch (notify->notifyType)
    {
        case kPowerManagerNotifyRecover:
        /* TODO */
        /* Add code here. */
        break;

        case kPowerManagerNotifyBefore:
        /* TODO */
        /* Add code here. */
        break;

        case kPowerManagerNotifyAfter:
        /* TODO */
        /* Add code here. */
        break;

        default:
            result = kPowerManagerError;
        break;
    }

    return result;
}

clock_manager_error_code_t sai_cm_callback(clock_notify_struct_t *notify,
 void* dataPtr)
{
    clock_manager_error_code_t result = kClockManagerSuccess;

    switch (notify->notifyType)
    {
        case kClockManagerNotifyBefore:
        /* TODO */
        /* Add code here. */
        break;

        case kClockManagerNotifyRecover:
        /* TODO */
        /* Add code here. */
        break;

        case kClockManagerNotifyAfter:
        /* TODO */
        /* Add code here. */
        break;

        default:
            result = kClockManagerError;
        break;
    }
    return result;
}
#endif

