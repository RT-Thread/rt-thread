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

#include "fsl_i2c_shared_function.h"
#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

#if defined(KM34Z7_SERIES)

/* Implementation of I2C handler named in startup code. */
void I2C0_I2C1_IRQHandler(void)
{
    for(uint32_t i=0; i < I2C_INSTANCE_COUNT; i++)
    {
        if (CLOCK_SYS_GetI2cGateCmd(i))
        {
            I2C_DRV_IRQHandler(i);
        }
    }
}
#else

#if (I2C_INSTANCE_COUNT > 0U)
/* Implementation of I2C0 handler named in startup code. */
void I2C0_IRQHandler(void)
{
    I2C_DRV_IRQHandler(I2C0_IDX);
}
#endif

#if (I2C_INSTANCE_COUNT > 1U)
/* Implementation of I2C1 handler named in startup code. */
void I2C1_IRQHandler(void)
{
    I2C_DRV_IRQHandler(I2C1_IDX);
}
#endif

#if (I2C_INSTANCE_COUNT > 2U)
/* Implementation of I2C2 handler named in startup code. */
void I2C2_IRQHandler(void)
{
    I2C_DRV_IRQHandler(I2C2_IDX);
}
#endif

#if (I2C_INSTANCE_COUNT > 3U)
/* Implementation of I2C3 handler named in startup code. */
void I2C3_IRQHandler(void)
{
    I2C_DRV_IRQHandler(I2C3_IDX);
}
#endif
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

