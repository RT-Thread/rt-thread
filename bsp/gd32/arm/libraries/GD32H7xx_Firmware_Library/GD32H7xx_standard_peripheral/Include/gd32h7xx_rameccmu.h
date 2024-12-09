/*!
    \file    gd32h7xx_rameccmu.h
    \brief   definitions for the RAMECCMU

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_RAMECCMU_H
#define GD32H7XX_RAMECCMU_H

#include "gd32h7xx.h"

/* RAMECCMU definitions */
#define RAMECCMU0                                (RAMECCMU_BASE + 0x09FE6000U)                               /*!< RAMECCMU for Region 0 */
#define RAMECCMU1                                RAMECCMU_BASE                                               /*!< RAMECCMU for Region 1 */

/* registers definitions */
#define RAMECCMU_INT(rameccmux)                  REG32((rameccmux) + 0x00000000U)                            /*!< RAMECCMU global interruput register */

#define RAMECCMU_M0CTL(rameccmux)                REG32((rameccmux) + 0x00000020U)                            /*!< RAMECCMU monitor 0 control register */
#define RAMECCMU_M0STAT(rameccmux)               REG32((rameccmux) + 0x00000024U)                            /*!< RAMECCMU monitor 0 status register */
#define RAMECCMU_M0FADDR(rameccmux)              REG32((rameccmux) + 0x00000028U)                            /*!< RAMECCMU monitor 0 ECC failing address register */
#define RAMECCMU_M0FDL(rameccmux)                REG32((rameccmux) + 0x0000002CU)                            /*!< RAMECCMU monitor 0 ECC failing data low register */
#define RAMECCMU_M0FDH(rameccmux)                REG32((rameccmux) + 0x00000030U)                            /*!< RAMECCMU monitor 0 ECC failing data high register */
#define RAMECCMU_M0FECODE(rameccmux)             REG32((rameccmux) + 0x00000034U)                            /*!< RAMECCMU monitor 0 failing ECC error code register */

#define RAMECCMU_M1CTL(rameccmux)                REG32((rameccmux) + 0x00000040U)                            /*!< RAMECCMU monitor 1 control register */
#define RAMECCMU_M1STAT(rameccmux)               REG32((rameccmux) + 0x00000044U)                            /*!< RAMECCMU monitor 1 status register */
#define RAMECCMU_M1FADDR(rameccmux)              REG32((rameccmux) + 0x00000048U)                            /*!< RAMECCMU monitor 1 ECC failing address register */
#define RAMECCMU_M1FDL(rameccmux)                REG32((rameccmux) + 0x0000004CU)                            /*!< RAMECCMU monitor 1 ECC failing data low register */
#define RAMECCMU_M1FDH(rameccmux)                REG32((rameccmux) + 0x00000050U)                            /*!< RAMECCMU monitor 1 ECC failing data high register */
#define RAMECCMU_M1FECODE(rameccmux)             REG32((rameccmux) + 0x00000054U)                            /*!< RAMECCMU monitor 1 failing ECC error code register */

#define RAMECCMU_M2CTL(rameccmux)                REG32((rameccmux) + 0x00000060U)                            /*!< RAMECCMU monitor 2 control register */
#define RAMECCMU_M2STAT(rameccmux)               REG32((rameccmux) + 0x00000064U)                            /*!< RAMECCMU monitor 2 status register */
#define RAMECCMU_M2FADDR(rameccmux)              REG32((rameccmux) + 0x00000068U)                            /*!< RAMECCMU monitor 2 ECC failing address register */
#define RAMECCMU_M2FDL(rameccmux)                REG32((rameccmux) + 0x0000006CU)                            /*!< RAMECCMU monitor 2 ECC failing data low register */
#define RAMECCMU_M2FDH(rameccmux)                REG32((rameccmux) + 0x00000070U)                            /*!< RAMECCMU monitor 2 ECC failing data high register */
#define RAMECCMU_M2FECODE(rameccmux)             REG32((rameccmux) + 0x00000074U)                            /*!< RAMECCMU monitor 2 failing ECC error code register */

#define RAMECCMU_M3CTL(rameccmux)                REG32((rameccmux) + 0x00000080U)                            /*!< RAMECCMU monitor 3 control register */
#define RAMECCMU_M3STAT(rameccmux)               REG32((rameccmux) + 0x00000084U)                            /*!< RAMECCMU monitor 3 status register */
#define RAMECCMU_M3FADDR(rameccmux)              REG32((rameccmux) + 0x00000088U)                            /*!< RAMECCMU monitor 3 ECC failing address register */
#define RAMECCMU_M3FDL(rameccmux)                REG32((rameccmux) + 0x0000008CU)                            /*!< RAMECCMU monitor 3 ECC failing data low register */
#define RAMECCMU_M3FDH(rameccmux)                REG32((rameccmux) + 0x00000090U)                            /*!< RAMECCMU monitor 3 ECC failing data high register */
#define RAMECCMU_M3FECODE(rameccmux)             REG32((rameccmux) + 0x00000094U)                            /*!< RAMECCMU monitor 3 failing ECC error code register */

#define RAMECCMU_M4CTL(rameccmux)                REG32((rameccmux) + 0x000000A0U)                            /*!< RAMECCMU monitor 4 control register */
#define RAMECCMU_M4STAT(rameccmux)               REG32((rameccmux) + 0x000000A4U)                            /*!< RAMECCMU monitor 4 status register */
#define RAMECCMU_M4FADDR(rameccmux)              REG32((rameccmux) + 0x000000A8U)                            /*!< RAMECCMU monitor 4 ECC failing address register */
#define RAMECCMU_M4FDL(rameccmux)                REG32((rameccmux) + 0x000000ACU)                            /*!< RAMECCMU monitor 4 ECC failing data low register */
#define RAMECCMU_M4FDH(rameccmux)                REG32((rameccmux) + 0x000000B0U)                            /*!< RAMECCMU monitor 4 ECC failing data high register */
#define RAMECCMU_M4FECODE(rameccmux)             REG32((rameccmux) + 0x000000B4U)                            /*!< RAMECCMU monitor 4 failing ECC error code register */

/* bits definitions */
/* RAMECCMU_INT */
#define RAMECCMU_INT_GEIE                        BIT(0)                                                      /*!< global ECC interrupt enable */
#define RAMECCMU_INT_GESERRIE                    BIT(1)                                                      /*!< global ECC single error interrupt enable */
#define RAMECCMU_INT_GEDERRIE                    BIT(2)                                                      /*!< global ECC double error interrupt enable */
#define RAMECCMU_INT_GEDERRBWIE                  BIT(3)                                                      /*!< global ECC double error on byte write interrupt enable */

/* RAMECCMU_MxCTL */
#define RAMECCMU_MXCTL_ECCSERRIE                 BIT(2)                                                      /*!< ECC single error interrupt enable */
#define RAMECCMU_MXCTL_ECCDERRIE                 BIT(3)                                                      /*!< ECC double error interrupt enable */
#define RAMECCMU_MXCTL_ECCDERRBWIE               BIT(4)                                                      /*!< ECC double error on byte write interrupt enable */
#define RAMECCMU_MXCTL_ECCERRLATEN               BIT(5)                                                      /*!< ECC error latching enable */

/* RAMECCMU_MxSTAT */
#define RAMECCMU_MXSTAT_ECCSERRDCF               BIT(0)                                                      /*!< ECC single error detected and corrected flag */
#define RAMECCMU_MXSTAT_ECCDERRDF                BIT(1)                                                      /*!< ECC double error detected flag */
#define RAMECCMU_MXSTAT_ECCDERRBWDF              BIT(2)                                                      /*!< ECC double error on byte write detected flag */

/* RAMECCMU_MxFADDR */
#define RAMECCMU_MXFADDR_ECCFADDR                BITS(0,31)                                                  /*!< ECC error failing address */

/* RAMECCMU_MxFDL */
#define RAMECCMU_MXFDL_ECCFDL                    BITS(0,31)                                                  /*!< ECC failing data low bits */

/* RAMECCMU_MxFDH */
#define RAMECCMU_MXFDH_ECCFDH                    BITS(0,31)                                                  /*!< ECC failing data high bits */

/* RAMECCMU_MxFECODE */
#define RAMECCMU_MXFECODE_ECCFECODE              BITS(0,31)                                                  /*!< ECC failing error code */

/* constants definitions */
/* RAMECCMU monitor select */
typedef enum
{
    RAMECCMU0_MONITOR0 = 0x00U,                                                                              /*!< RAMECCMU0 monitor 0 */
    RAMECCMU0_MONITOR1 = 0x01U,                                                                              /*!< RAMECCMU0 monitor 1 */
    RAMECCMU0_MONITOR2 = 0x02U,                                                                              /*!< RAMECCMU0 monitor 2 */
    RAMECCMU0_MONITOR3 = 0x03U,                                                                              /*!< RAMECCMU0 monitor 3 */
    RAMECCMU0_MONITOR4 = 0x04U,                                                                              /*!< RAMECCMU0 monitor 4 */
    RAMECCMU1_MONITOR0 = 0x10U,                                                                              /*!< RAMECCMU1 monitor 0 */
    RAMECCMU1_MONITOR1 = 0x11U,                                                                              /*!< RAMECCMU1 monitor 1 */
    RAMECCMU1_MONITOR2 = 0x12U                                                                               /*!< RAMECCMU1 monitor 2 */
} rameccmu_monitor_enum;

/* RAMECCMUx monitor register address */
#define RAMECCMU_MXCTL(rameccmu_monitor)          REG32(RAMECCMU0 - ((uint32_t)(rameccmu_monitor) >> 4U)*0x09FE6000U + 0x20U + ((rameccmu_monitor) & 0x0FU) * 0x20U)         /*!< RAMECCMU monitor control register */
#define RAMECCMU_MXSTAT(rameccmu_monitor)         REG32(RAMECCMU0 - ((uint32_t)(rameccmu_monitor) >> 4U)*0x09FE6000U + 0x24U + ((rameccmu_monitor) & 0x0FU) * 0x20U)         /*!< RAMECCMU monitor status register */
#define RAMECCMU_MXFADDR(rameccmu_monitor)        REG32(RAMECCMU0 - ((uint32_t)(rameccmu_monitor) >> 4U)*0x09FE6000U + 0x28U + ((rameccmu_monitor) & 0x0FU) * 0x20U)         /*!< RAMECCMU monitor ECC failing address register */
#define RAMECCMU_MXFDL(rameccmu_monitor)          REG32(RAMECCMU0 - ((uint32_t)(rameccmu_monitor) >> 4U)*0x09FE6000U + 0x2CU + ((rameccmu_monitor) & 0x0FU) * 0x20U)         /*!< RAMECCMU monitor ECC failing data low register */
#define RAMECCMU_MXFDH(rameccmu_monitor)          REG32(RAMECCMU0 - ((uint32_t)(rameccmu_monitor) >> 4U)*0x09FE6000U + 0x30U + ((rameccmu_monitor) & 0x0FU) * 0x20U)         /*!< RAMECCMU monitor ECC failing data high register */
#define RAMECCMU_MXFECODE(rameccmu_monitor)       REG32(RAMECCMU0 - ((uint32_t)(rameccmu_monitor) >> 4U)*0x09FE6000U + 0x34U + ((rameccmu_monitor) & 0x0FU) * 0x20U)         /*!< RAMECCMU monitor failing ECC error code register */

#define RAMECCMU_INT_ECC_GLOBAL_ERROR             BIT(0)                                                     /*!< ECC global error interrupt */
#define RAMECCMU_INT_ECC_SINGLE_ERROR             BIT(1)                                                     /*!< ECC single error interrupt */
#define RAMECCMU_INT_ECC_DOUBLE_ERROR             BIT(2)                                                     /*!< ECC double error interrupt */
#define RAMECCMU_INT_ECC_DOUBLE_ERROR_BYTE_WRITE  BIT(3)                                                     /*!< ECC double error on byte write interrupt */
#define RAMECCMU_INT_ECC_ERROR_LATCHING           BIT(4)                                                     /*!< ECC error latching */

#define RAMECCMU_FLAG_ECC_SINGLE_ERROR            RAMECCMU_MXSTAT_ECCSERRDCF                                 /*!< ECC single error detected and corrected flag */
#define RAMECCMU_FLAG_ECC_DOUBLE_ERROR            RAMECCMU_MXSTAT_ECCDERRDF                                  /*!< ECC double error detected flag */
#define RAMECCMU_FLAG_ECC_DOUBLE_ERROR_BYTE_WRITE RAMECCMU_MXSTAT_ECCDERRBWDF                                /*!< ECC double error on byte write detected flag */

#define RAMECCMU_INT_FLAG_ECC_SINGLE_ERROR            RAMECCMU_MXSTAT_ECCSERRDCF                             /*!< ECC single error detected and corrected flag */
#define RAMECCMU_INT_FLAG_ECC_DOUBLE_ERROR            RAMECCMU_MXSTAT_ECCDERRDF                              /*!< ECC double error detected flag */
#define RAMECCMU_INT_FLAG_ECC_DOUBLE_ERROR_BYTE_WRITE RAMECCMU_MXSTAT_ECCDERRBWDF                            /*!< ECC double error on byte write detected flag */


/* function declarations */
/* deinit RAMECCMU unit */
void rameccmu_deinit(uint32_t rameccmu_periph);

/* RAMECCMU monitor ECC functions */
/* get RAMECCMU monitor ECC failing address */
uint32_t rameccmu_monitor_failing_address_get(rameccmu_monitor_enum rameccmu_monitor);
/* get RAMECCMU monitor ECC failing data low 32 bits */
uint32_t rameccmu_monitor_failing_data_low_bits_get(rameccmu_monitor_enum rameccmu_monitor);
/* get RAMECCMU monitor ECC failing data high 32 bits */
uint32_t rameccmu_monitor_failing_data_high_bits_get(rameccmu_monitor_enum rameccmu_monitor);
/* get RAMECCMU monitor failing ECC error code */
uint32_t rameccmu_monitor_failing_ecc_error_code_get(rameccmu_monitor_enum rameccmu_monitor);

/* interrupt & flag functions */
/* enable RAMECCMU global ECC interruput */
void rameccmu_global_interrupt_enable(uint32_t rameccmu_periph, uint32_t interrupt);
/* disable RAMECCMU global ECC interruput */
void rameccmu_global_interrupt_disable(uint32_t rameccmu_periph, uint32_t interrupt);
/* enable RAMECCMU monitor ECC error interruput */
void rameccmu_monitor_interrupt_enable(rameccmu_monitor_enum rameccmu_monitor, uint32_t monitor_interrupt);
/* disable RAMECCMU monitor ECC error interruput */
void rameccmu_monitor_interrupt_disable(rameccmu_monitor_enum rameccmu_monitor, uint32_t monitor_interrupt);
/* get RAMECCMU monitor ECC error flag */
FlagStatus rameccmu_monitor_flag_get(rameccmu_monitor_enum rameccmu_monitor, uint32_t flag);
/* clear RAMECCMU monitor ECC error flag */
void rameccmu_monitor_flag_clear(rameccmu_monitor_enum rameccmu_monitor, uint32_t flag);
/* get RAMECCMU monitor ECC interrupt error flag */
FlagStatus rameccmu_monitor_interrupt_flag_get(rameccmu_monitor_enum rameccmu_monitor, uint32_t int_flag);
/* clear RAMECCMU monitor interrupt ECC error flag */
void rameccmu_monitor_interrupt_flag_clear(rameccmu_monitor_enum rameccmu_monitor, uint32_t int_flag);

#endif /* GD32H7XX_RAMECCMU_H */
