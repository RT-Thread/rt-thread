/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef _FSL_USART_CMSIS_H_
#define _FSL_USART_CMSIS_H_

#include "fsl_common.h"
#include "Driver_USART.h"
#include "RTE_Device.h"
#include "fsl_usart.h"
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_usart_dma.h"
#endif

#if defined(USART0)
extern ARM_DRIVER_USART Driver_USART0;
#endif /* USART0 */

#if defined(USART1)
extern ARM_DRIVER_USART Driver_USART1;
#endif /* USART1 */

#if defined(USART2)
extern ARM_DRIVER_USART Driver_USART2;
#endif /* USART2 */

#if defined(USART3)
extern ARM_DRIVER_USART Driver_USART3;
#endif /* USART3 */

#if defined(USART4)
extern ARM_DRIVER_USART Driver_USART4;
#endif /* USART4 */

#if defined(USART5)
extern ARM_DRIVER_USART Driver_USART5;
#endif /* USART5 */

#if defined(USART6)
extern ARM_DRIVER_USART Driver_USART6;
#endif /* USART6 */

#if defined(USART7)
extern ARM_DRIVER_USART Driver_USART7;
#endif /* USART7 */

#endif /* _FSL_USART_CMSIS_H_ */
