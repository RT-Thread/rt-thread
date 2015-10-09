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
#include "fsl_spi_dma_shared_function.h"

#if FSL_FEATURE_SOC_SPI_COUNT
/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Extern for the DSPI DMA master driver's interrupt handler.*/
extern void SPI_DRV_DmaMasterIRQHandler(uint32_t instance);

/* Extern for the DSPI DMA slave driver's interrupt handler.*/
extern void SPI_DRV_DmaSlaveIRQHandler(uint32_t instance);

/*! @brief Table of base pointers for SPI instances. */
extern SPI_Type * const g_spiBase[SPI_INSTANCE_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief The function SPI_DRV_DmaIRQHandler passes IRQ control to either the master or
 * slave driver.
 *
 * The address of the IRQ handlers are checked to make sure they are non-zero before
 * they are called. If the IRQ handler's address is zero, it means that driver was
 * not present in the link (because the IRQ handlers are marked as weak). This would
 * actually be a program error, because it means the master/slave config for the IRQ
 * was set incorrectly.
 */
void SPI_DRV_DmaIRQHandler(uint32_t instance)
{
    assert(instance < SPI_INSTANCE_COUNT);
    SPI_Type *base = g_spiBase[instance];

    if (SPI_HAL_IsMaster(base))
    {
        /* Master mode.*/
        SPI_DRV_DmaMasterIRQHandler(instance);
    }
    else
    {
        /* Slave mode.*/
        SPI_DRV_DmaSlaveIRQHandler(instance);
    }
}

#endif /* FSL_FEATURE_SOC_SPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

