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

#include <assert.h>
#include "fsl_i2c_hal.h"
#include "fsl_i2c_shared_function.h"
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_I2C_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for I2C instances. */
extern I2C_Type * const g_i2cBase[I2C_INSTANCE_COUNT];

/* External for the I2C master driver interrupt handler.*/
extern void I2C_DRV_MasterIRQHandler(uint32_t instance);

/* External for the I2C slave driver interrupt handler.*/
extern void I2C_DRV_SlaveIRQHandler(uint32_t instance);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Pass IRQ control to either the master or slave driver.
 *
 * The address of the IRQ handlers are checked to make sure they are non-zero before
 * they are called. If the IRQ handler's address is zero, it means that driver was
 * not present in the link (because the IRQ handlers are marked as weak). This would
 * actually be a program error, because it means the master/slave config for the IRQ
 * was set incorrectly.
 *
 * @param instance   Instance number of the I2C module.
 */
void I2C_DRV_IRQHandler(uint32_t instance)
{
    assert(instance < I2C_INSTANCE_COUNT);
    I2C_Type * base = g_i2cBase[instance];
    if(I2C_HAL_GetStatusFlag(base, kI2CArbitrationLost))
    {
        /* Master mode.*/
        I2C_DRV_MasterIRQHandler(instance);
    }
	else
	{
	    if (I2C_HAL_IsMaster(base))
	    {
	        /* Master mode.*/
	        I2C_DRV_MasterIRQHandler(instance);
	    }
	    else
	    {
	        /* Slave mode.*/
	        I2C_DRV_SlaveIRQHandler(instance);
	    }
	}
}

#endif /* FSL_FEATURE_SOC_I2C_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

