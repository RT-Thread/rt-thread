/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file sdma_event.h
 * @brief SDMA events
 */

#ifndef SDMA_EVENT_H
#define SDMA_EVENT_H

/* SDMA EVENT DEFINITIONS. See mx6's user guider, chapter 3 for detail */
#define SDMA_EVENT_IPU1                     2
#define SDMA_EVENT_EXT_DMA_EVENT_0          2
#define SDMA_EVENT_ECSPI1_RX                 3
#define SDMA_EVENT_I2C3_A                   3
#define SDMA_EVENT_ECSPI1_TX                 4
#define SDMA_EVENT_I2C2_A                   4
#define SDMA_EVENT_ECSPI2_RX                 5
#define SDMA_EVENT_I2C1_A                   5
#define SDMA_EVENT_ECSPI2_TX                 6
#define SDMA_EVENT_ECSPI3_RX                 7
#define SDMA_EVENT_ECSPI3_TX                 8
#define SDMA_EVENT_ECSPI4_RX                 9
#define SDMA_EVENT_EPIT2                    9
#define SDMA_EVENT_ECSPI4_TX                 10
#define SDMA_EVENT_I2C1_B                   10
#define SDMA_EVENT_GPT	                   13
#define SDMA_EVENT_SPDIF_RX                 14
#define SDMA_EVENT_EXT_DMA_EVENT_1          14
#define SDMA_EVENT_SPDIF_TX                 15
#define SDMA_EVENT_EPIT1                    16
#define SDMA_EVENT_I2C3_B                   23
#define SDMA_EVENT_UART1_RX                 25
#define SDMA_EVENT_UART1_TX                 26
#define SDMA_EVENT_UART2_RX                 27
#define SDMA_EVENT_UART2_TX                 28
#define SDMA_EVENT_UART3_RX                 29
#define SDMA_EVENT_UART3_TX                 30
#define SDMA_EVENT_UART4_RX                 31
#define SDMA_EVENT_UART4_TX                 32
#define SDMA_EVENT_UART5_RX                 33
#define SDMA_EVENT_UART5_TX                 34
#define SDMA_EVENT_SSI1_RX1                 35
#define SDMA_EVENT_SSI1_TX1                 36
#define SDMA_EVENT_SSI1_RX0                 37
#define SDMA_EVENT_SSI1_TX0                 38
#define SDMA_EVENT_SSI2_RX1                 39
#define SDMA_EVENT_SSI2_TX1                 40
#define SDMA_EVENT_SSI2_RX0                 41
#define SDMA_EVENT_SSI2_TX0                 42
#define SDMA_EVENT_SSI3_RX1                 43
#define SDMA_EVENT_SSI3_TX1                 44
#define SDMA_EVENT_SSI3_RX0                 45
#define SDMA_EVENT_SSI3_TX0                 46
#define SDMA_EVENT_DTCP                     47

#endif
