//*****************************************************************************
//
//  am_hal_pwrctrl.h
//! @file
//!
//! @brief Functions for enabling and disabling power domains.
//!
//! @addtogroup pwrctrl2 Power Control
//! @ingroup apollo2hal
//! @{

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

#ifndef AM_HAL_PWRCTRL_H
#define AM_HAL_PWRCTRL_H

//*****************************************************************************
//
// Peripheral enable bits for am_hal_pwrctrl_periph_enable/disable()
//
//*****************************************************************************
#define AM_HAL_PWRCTRL_ADC      AM_REG_PWRCTRL_DEVICEEN_ADC_EN
#define AM_HAL_PWRCTRL_IOM0     AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_EN
#define AM_HAL_PWRCTRL_IOM1     AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1_EN
#define AM_HAL_PWRCTRL_IOM2     AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2_EN
#define AM_HAL_PWRCTRL_IOM3     AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3_EN
#define AM_HAL_PWRCTRL_IOM4     AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4_EN
#define AM_HAL_PWRCTRL_IOM5     AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5_EN
#define AM_HAL_PWRCTRL_IOS      AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE_EN
#define AM_HAL_PWRCTRL_PDM      AM_REG_PWRCTRL_DEVICEEN_PDM_EN
#define AM_HAL_PWRCTRL_UART0    AM_REG_PWRCTRL_DEVICEEN_UART0_EN
#define AM_HAL_PWRCTRL_UART1    AM_REG_PWRCTRL_DEVICEEN_UART1_EN

//*****************************************************************************
//
// Macro to set the appropriate IOM peripheral when using
//  am_hal_pwrctrl_periph_enable()/disable().
// For Apollo2, the module argument must resolve to be a value from 0-5.
//
//*****************************************************************************
#define AM_HAL_PWRCTRL_IOM(module)                      \
    (AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_EN << module)

//*****************************************************************************
//
// Macro to set the appropriate UART peripheral when using
//  am_hal_pwrctrl_periph_enable()/disable().
// For Apollo2, the module argument must resolve to be a value from 0-1.
//
//*****************************************************************************
#define AM_HAL_PWRCTRL_UART(module)                     \
    (AM_REG_PWRCTRL_DEVICEEN_UART0_EN << module)


//*****************************************************************************
//
// Memory enable values for am_hal_pwrctrl_memory_enable()
//
//*****************************************************************************
#define AM_HAL_PWRCTRL_MEMEN_SRAM8K     AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM8K
#define AM_HAL_PWRCTRL_MEMEN_SRAM16K    AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM16K
#define AM_HAL_PWRCTRL_MEMEN_SRAM24K   (AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM16K | \
                                        AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM2)
#define AM_HAL_PWRCTRL_MEMEN_SRAM32K    AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM32K
#define AM_HAL_PWRCTRL_MEMEN_SRAM64K    AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM64K
#define AM_HAL_PWRCTRL_MEMEN_SRAM96K                    \
            (AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM64K    |   \
             AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP2)
#define AM_HAL_PWRCTRL_MEMEN_SRAM128K   AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM128K
#define AM_HAL_PWRCTRL_MEMEN_SRAM160K                   \
            (AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM128K   |   \
             AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP4)
#define AM_HAL_PWRCTRL_MEMEN_SRAM192K                   \
            (AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM128K   |   \
             AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP4     |   \
             AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP5)
#define AM_HAL_PWRCTRL_MEMEN_SRAM224K                   \
            (AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM128K   |   \
             AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP4     |   \
             AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP5     |   \
             AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP6)
#define AM_HAL_PWRCTRL_MEMEN_SRAM256K   AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM256K

#define AM_HAL_PWRCTRL_MEMEN_FLASH512K  AM_REG_PWRCTRL_MEMEN_FLASH0_EN
#define AM_HAL_PWRCTRL_MEMEN_FLASH1M                \
            (AM_REG_PWRCTRL_MEMEN_FLASH0_EN     |   \
             AM_REG_PWRCTRL_MEMEN_FLASH1_EN)
#define AM_HAL_PWRCTRL_MEMEN_CACHE                  \
            (AM_REG_PWRCTRL_MEMEN_CACHEB0_EN    |   \
             AM_REG_PWRCTRL_MEMEN_CACHEB2_EN)
#define AM_HAL_PWRCTRL_MEMEN_CACHE_DIS              \
            ~(AM_REG_PWRCTRL_MEMEN_CACHEB0_EN   |   \
              AM_REG_PWRCTRL_MEMEN_CACHEB2_EN)

//
// Power up all available memory devices (this is the default power up state)
//
#define AM_HAL_PWRCTRL_MEMEN_ALL                    \
            (AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    |   \
             AM_REG_PWRCTRL_MEMEN_FLASH0_EN     |   \
             AM_REG_PWRCTRL_MEMEN_FLASH1_EN     |   \
             AM_REG_PWRCTRL_MEMEN_CACHEB0_EN    |   \
             AM_REG_PWRCTRL_MEMEN_CACHEB2_EN)

//*****************************************************************************
//
// Peripheral power enable and disable delays
// The delay counts are based on an internal clock that runs at half of
// HFRC. Therefore, we need to double the delay cycles.
//
//*****************************************************************************
#define AM_HAL_PWRCTRL_DEVICEEN_DELAYCYCLES     (22 * 2)
#define AM_HAL_PWRCTRL_DEVICEDIS_DELAYCYCLES    (22 * 2)

//
// Use the following only when enabling after sleep (not during initialization).
//
#define AM_HAL_PWRCTRL_BUCKEN_DELAYCYCLES       (0 * 2)
#define AM_HAL_PWRCTRL_BUCKDIS_DELAYCYCLES      (15 * 2)

//*****************************************************************************
//
// Peripheral PWRONSTATUS groupings.
//
//*****************************************************************************
//
// Group DEVICEEN bits (per PWRONSTATUS groupings).
//
#define AM_HAL_PWRCTRL_DEVICEEN_IOM_0_2                     \
            (AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_EN      |   \
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1_EN      |   \
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2_EN )

#define AM_HAL_PWRCTRL_DEVICEEN_IOM_3_5                     \
            (AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3_EN      |   \
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4_EN      |   \
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5_EN )

#define AM_HAL_PWRCTRL_DEVICEEN_IOS_UARTS                   \
            (AM_REG_PWRCTRL_DEVICEEN_UART0_EN           |   \
             AM_REG_PWRCTRL_DEVICEEN_UART1_EN           |   \
             AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE_EN )

#define AM_HAL_PWRCTRL_DEVICEEN_ADC             AM_REG_PWRCTRL_DEVICEEN_ADC_EN
#define AM_HAL_PWRCTRL_DEVICEEN_PDM             AM_REG_PWRCTRL_DEVICEEN_PDM_EN

//
// Map PWRONSTATUS bits to peripheral groupings.
//
#define AM_HAL_PWRCTRL_PWRONSTATUS_IOS_UARTS    AM_REG_PWRCTRL_PWRONSTATUS_PDA_M
#define AM_HAL_PWRCTRL_PWRONSTATUS_IOM_3_5      AM_REG_PWRCTRL_PWRONSTATUS_PDC_M
#define AM_HAL_PWRCTRL_PWRONSTATUS_IOM_0_2      AM_REG_PWRCTRL_PWRONSTATUS_PDB_M
#define AM_HAL_PWRCTRL_PWRONSTATUS_ADC          AM_REG_PWRCTRL_PWRONSTATUS_PDADC_M
#define AM_HAL_PWRCTRL_PWRONSTATUS_PDM          AM_REG_PWRCTRL_PWRONSTATUS_PD_PDM_M

#define POLL_PWRSTATUS(ui32Peripheral)                                  \
    if ( 1 )                                                            \
    {                                                                   \
        uint32_t ui32PwrOnStat;                                         \
        if ( ui32Peripheral & AM_HAL_PWRCTRL_DEVICEEN_IOM_0_2 )         \
        {                                                               \
            ui32PwrOnStat = AM_HAL_PWRCTRL_PWRONSTATUS_IOM_0_2;         \
        }                                                               \
        else if ( ui32Peripheral & AM_HAL_PWRCTRL_DEVICEEN_IOM_3_5 )    \
        {                                                               \
            ui32PwrOnStat = AM_HAL_PWRCTRL_PWRONSTATUS_IOM_3_5;         \
        }                                                               \
        else if ( ui32Peripheral & AM_HAL_PWRCTRL_DEVICEEN_IOS_UARTS )  \
        {                                                               \
            ui32PwrOnStat = AM_HAL_PWRCTRL_PWRONSTATUS_IOS_UARTS;       \
        }                                                               \
        else if ( ui32Peripheral & AM_HAL_PWRCTRL_DEVICEEN_ADC )        \
        {                                                               \
            ui32PwrOnStat = AM_HAL_PWRCTRL_PWRONSTATUS_ADC;             \
        }                                                               \
        else if ( ui32Peripheral & AM_HAL_PWRCTRL_DEVICEEN_PDM )        \
        {                                                               \
            ui32PwrOnStat = AM_HAL_PWRCTRL_PWRONSTATUS_PDM;             \
        }                                                               \
        else                                                            \
        {                                                               \
            ui32PwrOnStat = 0xFFFFFFFF;                                 \
        }                                                               \
                                                                        \
        /* */                                                           \
        /* Wait for the power control setting to take effect. */        \
        /* */                                                           \
        while ( !(AM_REG(PWRCTRL, PWRONSTATUS) & ui32PwrOnStat) );      \
    }

//*****************************************************************************
//
// Memory PWRONSTATUS enable values for am_hal_pwrctrl_memory_enable()
//
//*****************************************************************************
#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_8K                  \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_16K                 \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_24K                 \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_32K                 \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_64K                 \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_96K                 \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_128K                \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_160K                \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP4_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_192K                \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP5_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP4_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_224K                \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP6_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP5_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP4_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_256K                \
           (AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP7_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP6_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP5_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP4_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP3_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP2_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP1_SRAM_M   |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM3_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM2_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM1_M  |   \
            AM_REG_PWRCTRL_PWRONSTATUS_PD_GRP0_SRAM0_M)

#define AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL                 \
        AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_256K

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************
extern void am_hal_pwrctrl_periph_enable(uint32_t ui32Peripheral);
extern void am_hal_pwrctrl_periph_disable(uint32_t ui32Peripheral);
extern bool am_hal_pwrctrl_memory_enable(uint32_t ui32MemEn);
extern void am_hal_pwrctrl_bucks_init(void);
extern void am_hal_pwrctrl_bucks_enable(void);
extern void am_hal_pwrctrl_bucks_disable(void);
extern void am_hal_pwrctrl_low_power_init(void);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_PWRCTRL_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
