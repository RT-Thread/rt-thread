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

#include "fsl_flexbus_driver.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_FB_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initializes the FlexBus driver.
 *
 * @param instance The FlexBus peripheral instance number.
 * @param fb_config FlexBus input user configuration
 */
flexbus_status_t FLEXBUS_DRV_Init(uint32_t instance, const flexbus_user_config_t *fb_config)
{
    assert(instance < FB_INSTANCE_COUNT);

    FB_Type* fbbase = g_fbBase[instance];

    if(!fb_config)
    {
        return kStatus_FLEXBUS_InvalidArgument;
    }

    /* clock setting initialization.*/
    CLOCK_SYS_EnableFlexbusClock(instance);

    /* Reset all the register to default state.*/
    FLEXBUS_HAL_Init(fbbase);
    /* Configure all the register to a known state */
    FLEXBUS_HAL_Configure(fbbase, fb_config);

    return kStatus_FLEXBUS_Success;
}

/*!
 * @brief Shuts down the FlexBus driver.
 *
 * @param instance The FlexBus peripheral instance number.
 */
flexbus_status_t FLEXBUS_DRV_Deinit(uint32_t instance)
{
    assert(instance < FB_INSTANCE_COUNT);

    /* disable clock for Flexbus.*/
    CLOCK_SYS_DisableFlexbusClock(instance);

    return kStatus_FLEXBUS_Success;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

