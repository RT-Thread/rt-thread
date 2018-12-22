//*****************************************************************************
//
//! @file am_reg_base_addresses.h
//!
//! @brief Register defines for all module base addresses
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_REG_BASE_ADDRESSES_H
#define AM_REG_BASE_ADDRESSES_H

#include "stdint.h"

// ARM standard register space (needed for macros)
#define REG_ITM_BASEADDR                         (0x00000000UL)
#define REG_JEDEC_BASEADDR                       (0x00000000UL)
#define REG_NVIC_BASEADDR                        (0x00000000UL)
#define REG_SYSCTRL_BASEADDR                     (0x00000000UL)
#define REG_SYSTICK_BASEADDR                     (0x00000000UL)
#define REG_TPIU_BASEADDR                        (0x00000000UL)

// Peripheral register space
#define REG_ADC_BASEADDR                         (0x50010000UL)
#define REG_CACHECTRL_BASEADDR                   (0x40018000UL)
#define REG_CLKGEN_BASEADDR                      (0x40004000UL)
#define REG_CTIMER_BASEADDR                      (0x40008000UL)
#define REG_GPIO_BASEADDR                        (0x40010000UL)
#define REG_IOMSTR_BASEADDR                      (0x50004000UL)
#define REG_IOSLAVE_BASEADDR                     (0x50000000UL)
#define REG_MCUCTRL_BASEADDR                     (0x40020000UL)
#define REG_PDM_BASEADDR                         (0x50011000UL)
#define REG_PWRCTRL_BASEADDR                     (0x40021000UL)
#define REG_RSTGEN_BASEADDR                      (0x40000000UL)
#define REG_RTC_BASEADDR                         (0x40004000UL)
#define REG_UART_BASEADDR                        (0x4001C000UL)
#define REG_VCOMP_BASEADDR                       (0x4000C000UL)
#define REG_WDT_BASEADDR                         (0x40024000UL)

// SRAM address space
#define SRAM_BASEADDR                            (0x10000000UL)

#endif // AM_REG_BASE_ADDRESSES_H

