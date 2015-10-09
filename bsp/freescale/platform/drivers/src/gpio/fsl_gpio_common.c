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

#if FSL_FEATURE_SOC_GPIO_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for GPIO instances. */
GPIO_Type * const g_gpioBase[GPIO_INSTANCE_COUNT] = GPIO_BASE_PTRS;

#if defined(FGPIO_INSTANCE_COUNT)
/* Table of base addresses for FGPIO instances. */
FGPIO_Type * const g_fgpioBase[FGPIO_INSTANCE_COUNT ] = FGPIO_BASE_PTRS;
#endif

/* Table of base addresses for PORT instances. */
PORT_Type * const g_portBase[PORT_INSTANCE_COUNT] = PORT_BASE_PTRS;

/* Table to save port IRQ enum numbers defined in CMSIS files. */
const IRQn_Type g_portIrqId[PORT_INSTANCE_COUNT] = PORT_IRQS;

#endif /* FSL_FEATURE_SOC_GPIO_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

