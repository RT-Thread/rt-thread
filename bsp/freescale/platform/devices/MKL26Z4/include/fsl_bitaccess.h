/*
** ###################################################################
**     Version:             rev. 1.6, 2015-02-18
**     Build:               b150218
**
**     Abstract:
**         Register bit field access macros.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2012-12-12)
**         Initial version.
**     - rev. 1.1 (2013-04-12)
**         SystemInit function fixed for clock configuration 1.
**         Name of the interrupt num. 31 updated to reflect proper function.
**     - rev. 1.2 (2014-05-27)
**         Updated to Kinetis SDK support standard.
**         MCG OSC clock select supported (MCG_C7[OSCSEL]).
**     - rev. 1.3 (2014-07-25)
**         System initialization updated:
**         - Prefix added to the system initialization parameterization constants to avoid name conflicts..
**         - VLLSx wake-up recovery added.
**         - Delay of 1 ms added to SystemInit() to ensure stable FLL output in FEI and FEE MCG modes.
**     - rev. 1.4 (2014-08-28)
**         Update of system files - default clock configuration changed, fix of OSC initialization.
**         Update of startup files - possibility to override DefaultISR added.
**     - rev. 1.5 (2014-10-14)
**         Renamed interrupt vector LPTimer to LPTMR0
**     - rev. 1.6 (2015-02-18)
**         Renamed interrupt vector LLW to LLWU
**
** ###################################################################
*/

#ifndef _FSL_BITACCESS_H
#define _FSL_BITACCESS_H  1

#include <stdint.h>
#include <stdlib.h>

#define BME_AND_MASK  (1<<26)
#define BME_OR_MASK   (1<<27)
#define BME_XOR_MASK  (3<<26)
#define BME_BFI_MASK(BIT,WIDTH)   (1<<28) | (BIT<<23) | ((WIDTH-1)<<19)
#define BME_UBFX_MASK(BIT,WIDTH)  (1<<28) | (BIT<<23) | ((WIDTH-1)<<19)

/* Decorated Store: Logical AND */
#define BME_AND8(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_AND_MASK) = wdata)
#define BME_AND16(addr, wdata) (*(volatile uint16_t*)((uintptr_t)addr | BME_AND_MASK) = wdata)
#define BME_AND32(addr, wdata) (*(volatile uint32_t*)((uintptr_t)addr | BME_AND_MASK) = wdata)

/* Decorated Store: Logical OR */
#define BME_OR8(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_OR_MASK) = wdata)
#define BME_OR16(addr, wdata) (*(volatile uint16_t*)((uintptr_t)addr | BME_OR_MASK) = wdata)
#define BME_OR32(addr, wdata) (*(volatile uint32_t*)((uintptr_t)addr | BME_OR_MASK) = wdata)

/* Decorated Store: Logical XOR */
#define BME_XOR8(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_XOR_MASK) = wdata)
#define BME_XOR16(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_XOR_MASK) = wdata)
#define BME_XOR32(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_XOR_MASK) = wdata)

/* Decorated Store: Bit Field Insert */
#define BME_BFI8(addr, wdata, bit, width) (*(volatile uint8_t*)((uintptr_t)addr | BME_BFI_MASK(bit,width)) = wdata)
#define BME_BFI16(addr, wdata, bit, width) (*(volatile uint16_t*)((uintptr_t)addr | BME_BFI_MASK(bit,width)) = wdata)
#define BME_BFI32(addr, wdata, bit, width) (*(volatile uint32_t*)((uintptr_t)addr | BME_BFI_MASK(bit,width)) = wdata)

/* Decorated Load: Unsigned Bit Field Extract */
#define BME_UBFX8(addr, bit, width) (*(volatile uint8_t*)((uintptr_t)addr | BME_UBFX_MASK(bit,width)))
#define BME_UBFX16(addr, bit, width) (*(volatile uint16_t*)((uintptr_t)addr | BME_UBFX_MASK(bit,width)))
#define BME_UBFX32(addr, bit, width) (*(volatile uint32_t*)((uintptr_t)addr | BME_UBFX_MASK(bit,width)))

#endif /* _FSL_BITACCESS_H */

/******************************************************************************/
