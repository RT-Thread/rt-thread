/***************************************************************************//**
* \file cyhal_dma_impl.h
*
* \brief
* Implementation details of Infineon Datawire/DMAC DMA.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M4CPUSS_DMA) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMA) || defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXDW) || defined(CY_IP_MXSAXIDMAC)

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_impl_dma DMA (Direct Memory Access)
 * \ingroup group_hal_impl
 * \{
 * DW (DataWire) is one of two DMA hardware implementations for CAT1 (PSoC™ 6).
 * DW is designed for low latency memory to peripheral or peripheral to memory
 * transfers but can also perform memory to memory transfers and peripheral to
 * peripheral transfers.
 *
 * DMAC (Direct Memory Access Controller) is the second of two DMA hardware
 * implementations for CAT1 (PSoC™ 6). It is also the implementation that is
 * found on CAT2 (PMG/PSoC™ 4) devices. DMAC is designed with high memory
 * bandwidth for large memory to memory transfers but can perform peripheral
 * to memory, memory to peripheral, and peripheral to peripheral transfers.
 *
 * Which DMA type is used is dependent on the exact hardware and number of DMA
 * channels already in use. This implementation will attempt to use DMAC first
 * for memory to memory transfers and Datawire otherwise but either type may be
 * used.
 *
 * \section group_hal_impl_dma_interconnect Interconnect
 * For both DW and DMAC each channel has a single input and a single output
 * trigger available. The input, when triggered, initiates a DMA transfer of
 * the configured type (note that this also affects the type transferred by the
 * SW triggering). For output, a trigger is generated when a DMA transfer of
 * the configured type is completed. For DW and DMAC neither input nor output
 * triggers can be disabled completely but the signals do not, of course, have
 * to be connected through the interconnect.
 *
 * */

/** Default DMA channel priority */
#define CYHAL_DMA_PRIORITY_DEFAULT    CYHAL_DMA_PRIORITY_LOW
/** High DMA channel priority */
#define CYHAL_DMA_PRIORITY_HIGH       0
/** Medium DMA channel priority */
#define CYHAL_DMA_PRIORITY_MEDIUM     1
/** Low DMA channel priority */
#define CYHAL_DMA_PRIORITY_LOW        3

/** \cond INTERNAL */
/** Hal-Triggers uses bit 8 to denote a one to one trigger, whereas, the PDL
 * SwTrigger function uses bit 5 to denote a one to one trigger. */
#define _CYHAL_DMA_TRIGGERS_1TO1_MASK (0x80)
#define _CYHAL_DMA_PDL_TRIGGERS_1TO1_MASK (0x10)
/** \endcond */

/** \} group_hal_impl_dma */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M4CPUSS_DMA) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMA) || defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXDW) */
