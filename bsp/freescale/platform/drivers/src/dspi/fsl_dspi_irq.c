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
#include <stdbool.h>
#include "fsl_dspi_shared_function.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup dspi_irq
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

#if (SPI_INSTANCE_COUNT == 1)
/*!
 * @brief This function is the implementation of SPI0 handler named in startup code.
 *
 * It passes the instance to the shared DSPI IRQ handler.
 */
void SPI0_IRQHandler(void)
{
    DSPI_DRV_IRQHandler(SPI0_IDX);
}

#elif (SPI_INSTANCE_COUNT == 2)
/*!
 * @brief This function is the implementation of SPI0 handler named in startup code.
 *
 * It passes the instance to the shared DSPI IRQ handler.
 */
void SPI0_IRQHandler(void)
{
    DSPI_DRV_IRQHandler(SPI0_IDX);
}

/*!
 * @brief This function is the implementation of SPI1 handler named in startup code.
 *
 * It passes the instance to the shared DSPI IRQ handler.
 */
void SPI1_IRQHandler(void)
{
    DSPI_DRV_IRQHandler(SPI1_IDX);
}

#else
/*!
 * @brief This function is the implementation of SPI0 handler named in startup code.
 *
 * It passes the instance to the shared DSPI IRQ handler.
 */
void SPI0_IRQHandler(void)
{
    DSPI_DRV_IRQHandler(SPI0_IDX);
}

/*!
 * @brief This function is the implementation of SPI1 handler named in startup code.
 *
 * It passes the instance to the shared DSPI IRQ handler.
 */
void SPI1_IRQHandler(void)
{
    DSPI_DRV_IRQHandler(SPI1_IDX);
}

/*!
 * @brief This function is the implementation of SPI2 handler named in startup code.
 *
 * It passes the instance to the shared DSPI IRQ handler.
 */
void SPI2_IRQHandler(void)
{
    DSPI_DRV_IRQHandler(SPI2_IDX);
}

#endif

/*! @} */

/*******************************************************************************
 * EOF
 ******************************************************************************/

