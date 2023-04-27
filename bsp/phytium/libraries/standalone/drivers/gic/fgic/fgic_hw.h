/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fgic_hw.h
 * Date: 2022-03-24 11:44:48
 * LastEditTime: 2022-03-24 11:44:48
 * Description: This file is for gic register definition.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */

#ifndef FGIC_HW_H
#define FGIC_HW_H

#include "ftypes.h"
#include "fio.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Distributor */
#define FGIC_GICD_CTLR_OFFSET 0x00000000U       /* Distributor Control Register ,RW */
#define FGIC_GICD_TYPER_OFFSET 0x00000004U      /* Interrupt Controller Type Register ,RO */
#define FGIC_GICD_IIDR_OFFSET 0x00000008U       /* Distributor Implementer Identification Register ,RO */
#define FGIC_GICD_TYPER2_OFFSET 0x0000000CU     /* Interrupt controller Type Register 2,RO */
#define FGIC_GICD_STATUSR_OFFSET 0x00000010U    /* Error Reporting Status Register, optional ,RW */
#define FGIC_GICD_SETSPI_NSR_OFFSET 0x00000040U /* Set SPI Register ,WO */
#define FGIC_GICD_CLRSPI_NSR_OFFSET 0x00000048U /*  Clear SPI Register ,WO */
#define FGIC_GICD_SETSPI_SR_OFFSET 0x00000050U  /*  Set SPI, Secure Register ,WO */
#define FGIC_GICD_CLRSPI_SR_OFFSET 0x00000058U  /*  Clear SPI, Secure Register ,WO */
#define FGIC_GICD_IGROUPR_OFFSET 0x00000080U    /* Interrupt Group Registers ,RW */

#define FGIC_GICD_ISENABLER_OFFSET 0x00000100U  /* Interrupt Set-Enable Registers ,RW */
#define FGIC_GICD_ICENABLER_OFFSET 0x00000180U  /* Interrupt Clear-Enable Registers ,RW */
#define FGIC_GICD_ISPENDR_OFFSET 0x00000200U    /* Interrupt Set-Pending Registers ,RW */
#define FGIC_GICD_ICPENDR_OFFSET 0x00000280U    /* Interrupt Clear-Pending Registers ,RW */
#define FGIC_GICD_ISACTIVER_OFFSET 0x00000300U  /* Interrupt Set-Active Registers ,RW */
#define FGIC_GICD_ICACTIVER_OFFSET 0x00000380U  /* Interrupt Clear-Active Registers ,RW */
#define FGIC_GICD_IPRIORITYR_OFFSET 0x00000400U /* Interrupt Priority Registers ,RW */
#define FGIC_GICD_ITARGETSR_OFFSET 0x00000800U  /* Interrupt Processor Targets Registers ,RO */

#define FGIC_GICD_ICFGR_OFFSET 0x00000C00U    /* Interrupt Configuration Registers ,RW */
#define FGIC_GICD_IGRPMODR_OFFSET 0x00000D00U /* Interrupt Group Modifier Registers */

#define FGIC_GICD_NSACR_OFFSET 0x00000E00U     /* Non-secure Access Control ,RW */
#define FGIC_GICD_SGIR_OFFSET 0x00000F00U      /* Software Generated Interrupt Register ,WO */
#define FGIC_GICD_CPENDSGIR_OFFSET 0x00000F10U /* SGI Clear-Pending Registers ,RW */
#define FGIC_GICD_SPENDSGIR_OFFSET 0x00000F20U /* SGI Set-Pending Registers ,RW */

#define FGIC_GICD_IGROUPR_E_OFFSET 0x00001000U /* Interrupt Group Registers for extended SPI ,RW */

#define FGIC_GICD_ISENABLER_E_OFFSET 0x00001200U /* Interrupt Set-Enable for extended SPI ,RW */

#define FGIC_GICD_ICENABLER_E_OFFSET 0x00001400U /* Interrupt Clear-Enable for extended SPI ,RW */

#define FGIC_GICD_ISPENDR_E_OFFSET 0x00001600U /* Interrupt Set-Pend for extended SPI range ,RW */
#define FGIC_GICD_ICPENDR_E_OFFSET 0x00001800U /* Interrupt Clear-Pend for extended SPI ,RW */

#define FGIC_GICD_ISACTIVER_E_OFFSET 0x00001A00U /* Interrupt Set-Active for extended SPI ,RW */

#define FGIC_GICD_ICACTIVER_E_OFFSET 0x00001C00U /* Interrupt Clear-Active for extended SPI ,RW */

#define FGIC_GICD_IPRIORITYR_E_OFFSET 0x00002000U /* Interrupt Priority for extended SPI range ,RW */
#define FGIC_GICD_ICFGR_E_OFFSET 0x00003000U      /* Extended SPI Configuration Register ,RW */
#define FGIC_GICD_IGRPMODR_E_OFFSET 0x00003400U   /* Interrupt Group Modifier for extended SPI ,RW */
#define FGIC_GICD_NSACR_E_OFFSET 0x00003600U      /* Non-secure Access Control Registers for extended SPI range ,RW */

#define FGIC_GICD_IROUTER_OFFSET 0x00006000U   /* Interrupt Routing Registers ,RW ,The offset of the GICD_IROUTER<n> register is 0x6000 + 8n. */
#define FGIC_GICD_IROUTER_E_OFFSET 0x00008000U /* Interrupt Routing Registers for extended SPI range ,RW */

/* Redistributor - RD_BASE */
/* Each Redistributor defines two 64KB frames in the physical address map */
#define FGIC_GICR_CTLR_OFFSET 0x00000000U    /* See the register description Redistributor Control Register ,RW */
#define FGIC_GICR_IIDR_OFFSET 0x00000004U    /* Implementer Identification Register ,RO */
#define FGIC_GICR_TYPER_OFFSET 0x00000008U   /* Redistributor Type Register ,RO */
#define FGIC_GICR_STATUSR_OFFSET 0x00000010U /* Error Reporting Status Register, optional ,RW */
#define FGIC_GICR_WAKER_OFFSET 0x00000014U   /* See the register description Redistributor Wake Register ,RW */
#define FGIC_GICR_MPAMIDR_OFFSET 0x00000018U /* Report maximum PARTID and PMG Register ,RO */
#define FGIC_GICR_PARTIDR_OFFSET 0x0000001CU /* Set PARTID and PMG Register ,RW */

#define FGIC_GICR_SETLPIR_OFFSET 0x00000040U /* Set LPI Pending Register ,WO */
#define FGIC_GICR_CLRLPIR_OFFSET 0x00000048U /* Clear LPI Pending Register ,WO */

#define FGIC_GICR_PROPBASER_OFFSET 0x00000070U /* Redistributor Properties Base Address Register ,RW */
#define FGIC_GICR_PENDBASER_OFFSET 0x00000078U /* Redistributor LPI Pending Table Base Address Register ,RW */

/* Redistributor - SGI_BASE */

#define FGIC_GICR_SGI_BASE_OFFSET 0x10000U /* 64KB frames */

#define FGIC_GICR_IGROUPR0_OFFSET 0x00000080U  /* Interrupt Group Register 0 ,RW */
#define FGIC_GICR_IGROUPR_E_OFFSET 0x00000084U /* Interrupt Group Registers for extended PPI range ,RW */

#define FGIC_GICR_ISENABLER0_OFFSET 0x00000100U  /* Interrupt Set-Enable Register 0 ,RW */
#define FGIC_GICR_ISENABLER_E_OFFSET 0x00000104U /* Interrupt Set-Enable for extended PPI range ,RW */

#define FGIC_GICR_ICENABLER0_OFFSET 0x00000180U  /* Interrupt Clear-Enable Register 0 ,RW */
#define FGIC_GICR_ICENABLER_E_OFFSET 0x00000184U /* Interrupt Clear-Enable for extended PPI range ,RW */


#define FGIC_GICR_ISPENDR0_OFFSET 0x00000200U  /* Interrupt Set-Pend Register 0 ,RW */
#define FGIC_GICR_ISPENDR_E_OFFSET 0x00000204U /* Interrupt Set-Pend for extended PPI range ,RW */

#define FGIC_GICR_ICPENDR0_OFFSET 0x00000280U /* Interrupt Clear-Pend Register 0 ,RW */

#define FGIC_GICR_ICPENDR_E_OFFSET 0x00000284U /* Interrupt Clear-Pend for extended PPI range ,RW */

#define FGIC_GICR_ISACTIVER0_OFFSET 0x00000300U  /* Interrupt Set-Active Register 0 ,RW */
#define FGIC_GICR_ISACTIVER_E_OFFSET 0x00000304U /* Interrupt Set-Active for extended PPI range ,RW */

#define FGIC_GICR_ICACTIVER0_OFFSET 0x00000380U  /* Interrupt Clear-Active Register 0 ,RW */
#define FGIC_GICR_ICACTIVER_E_OFFSET 0x00000384U /* Interrput Clear-Active for extended PPI range ,RW */

#define FGIC_GICR_IPRIORITYR_OFFSET 0x00000400U   /* Interrupt Priority Registers ,RW */
#define FGIC_GICR_IPRIORITYR_E_OFFSET 0x00000420U /* Interrupt Priority for extended PPI range ,RW */

#define FGIC_GICR_ICFGR0_OFFSET 0x00000C00U /*  SGI Configuration Register ,RW*/
#define FGIC_GICR_ICFGR1_OFFSET 0x00000C04U /*  PPI Configuration Register ,RW*/

#define FGIC_GICR_ICFGR_E_OFFSET 0x00000C08U   /* Extended PPI Configuration Register ,RW */
#define FGIC_GICR_IGRPMODR0_OFFSET 0x00000D00U /* Interrupt Group Modifier Register 0 ,RW */

#define FGIC_GICR_IGRPMODR_E_OFFSET 0x00000D04U /* Interrupt Group Modifier for extended PPI range ,RW */

#define FGIC_GICR_NSACR_OFFSET 0x00000E00U /* Non-Secure Access Control Register ,RW */

#define FGIC_READREG8(addr, reg_offset) FtIn8(addr + (u8)reg_offset)
#define FGIC_WRITEREG8(addr, reg_offset, reg_value) FtOut8(addr + (u8)reg_offset, (u8)reg_value)

#define FGIC_READREG32(addr, reg_offset) FtIn32(addr + (u32)reg_offset)
#define FGIC_WRITEREG32(addr, reg_offset, reg_value) FtOut32(addr + (u32)reg_offset, (u32)reg_value)

#define FGIC_READREG64(addr, reg_offset) FtIn64(addr + (u64)reg_offset)
#define FGIC_WRITEREG64(addr, reg_offset, reg_value) FtOut64(addr +(u64)reg_offset, (u64)reg_value)


#define FGIC_SETBIT(base_addr, reg_offset, data) \
    FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FGIC_CLEARBIT(base_addr, reg_offset, data) \
    FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))

/* FGIC_GICD_CTLR_OFFSET --- Distributor switch */
#define FGIC_GICD_CTLR_RWP_MASK BIT(31)
#define FGIC_GICD_CTLR_DS_MASK  BIT(6)

/* Need check system whether support Security states */

#define FGIC_GICD_CTLR_WRITE(gicd_base, reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_CTLR_OFFSET, reg)
#define FGIC_GICD_CTLR_READ(gicd_base) FGIC_READREG32(gicd_base , FGIC_GICD_CTLR_OFFSET)

/* FGIC_GICD_ISENABLER_OFFSET --- SPI Open */
#define FGIC_GICD_ISENABLER_VALUE_OFFSET(itnum) ((itnum % 32U))
#define FGIC_GICD_ISENABLER_VALUE_MASK(itnum)   (0x1U << FGIC_GICD_ISENABLER_VALUE_OFFSET(itnum))
#define FGIC_GICD_ISENABLER_READ_N_MASK(gicd_base,itnum)   FGIC_READREG32(gicd_base , FGIC_GICD_ISENABLER_OFFSET + ((itnum >> 5)<<2) )
#define FGIC_GICD_ISENABLER_WRITE_N_MASK(gicd_base,itnum,reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_ISENABLER_OFFSET + ((itnum >> 5)<<2), reg)

/* FGIC_GICD_TYPER_OFFSET --- Provides information about what features the GIC implementation supports. */
#define FGIC_GICD_TYPER_ITLINESNUMBER_MASK 0x1f


/* FGIC_GICD_ICENABLER_OFFSET --- SPI close */
#define FGIC_GICD_ICENABLER_DEFAULT_MASK  BIT_MASK(32)
#define FGIC_GICD_ICENABLER_VALUE_OFFSET(itnum) ((itnum % 32U))
#define FGIC_GICD_ICENABLER_VALUE_MASK(itnum)   (0x1U << FGIC_GICD_ICENABLER_VALUE_OFFSET(itnum))
#define FGIC_GICD_ICENABLER_READ_N_MASK(gicd_base,itnum)   FGIC_READREG32(gicd_base , FGIC_GICD_ICENABLER_OFFSET + ((itnum >> 5)<<2) )
#define FGIC_GICD_ICENABLER_WRITE_N_MASK(gicd_base,itnum,reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_ICENABLER_OFFSET + ((itnum >> 5)<<2), reg)


/* FGIC_GICD_IPRIORITYR_OFFSET --- SPI priority */
#define FGIC_GICD_IPRIORITYR_VALUE_MASK(itnum)   (0xFFU << ((itnum % 4U) << 3))
#define FGIC_GICD_IPRIORITYR_READ_N_MASK(gicd_base,itnum)   FGIC_READREG32(gicd_base , FGIC_GICD_IPRIORITYR_OFFSET + ((itnum >> 2)<<2) )
#define FGIC_GICD_IPRIORITYR_WRITE_N_MASK(gicd_base,itnum,reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_IPRIORITYR_OFFSET + ((itnum >> 2)<<2), reg)

/* FGIC_GICD_IROUTER_OFFSET --- SPI Routing */
#define FGIC_GICD_IROUTER_AFFINITY_MASK (((0xFFULL) <<32)|((0xFFULL) <<16)|((0xFFULL)<<8)|(0xFFULL)) /* affinity mask */
#define FGIC_GICD_IROUTER_RANGE_LIMIT (1023) /* GICD_IROUTER<n>, Interrupt Routing Registers, n = 0 - 1019 */
#define FGIC_GICD_IROUTER_BYTE_WIDTH 8
#define FGIC_GICD_IROUTER_WRITE(gicd_base, bank, reg) FGIC_WRITEREG64(gicd_base , FGIC_GICD_IROUTER_OFFSET + (bank * FGIC_GICD_IROUTER_BYTE_WIDTH), reg)
#define FGIC_GICD_IROUTER_READ(gicd_base, bank) FGIC_READREG64(gicd_base , FGIC_GICD_IROUTER_OFFSET + (bank * FGIC_GICD_IROUTER_BYTE_WIDTH))

/* FGIC_GICD_ITARGETSR_OFFSET --- legacy operation （ affinity routing is not enabled）  */
#define FGIC_GICD_ITARGETSR_BYTE_WIDTH 4
#define FGIC_GICD_ITARGETSR_WRITE(gicd_base, bank, reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_ITARGETSR_OFFSET + (bank * FGIC_GICD_ITARGETSR_BYTE_WIDTH), reg)
#define FGIC_GICD_ITARGETSR_READ(gicd_base, bank) FGIC_READREG32(gicd_base , FGIC_GICD_ITARGETSR_OFFSET + (bank * FGIC_GICD_ITARGETSR_BYTE_WIDTH))

/* FGIC_GICD_ICFGR_OFFSET --- edge-triggered or level-sensitive */
#define FGIC_GICD_ICFGR_VALUE_OFFSET(itnum) ((itnum % 16U) << 1)
#define FGIC_GICD_ICFGR_VALUE_MASK(itnum)   (0x3U << FGIC_GICD_ICFGR_VALUE_OFFSET(itnum))
#define FGIC_GICD_ICFGR_READ_N_MASK(gicd_base,itnum)   FGIC_READREG32(gicd_base , FGIC_GICD_ICFGR_OFFSET + ((itnum >> 4)<<2) )
#define FGIC_GICD_ICFGR_WRITE_N_MASK(gicd_base,itnum,reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_ICFGR_OFFSET + ((itnum >> 4)<<2), reg)


/* FGIC_GICD_ISPENDR_OFFSET --- about spi pending */
#define FGIC_GICD_ISPENDR_BYTE_WIDTH 4
#define FGIC_GICD_ISPENDR_WRITE(gicd_base, bank, reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_ISPENDR_OFFSET + (bank * FGIC_GICD_ISPENDR_BYTE_WIDTH), reg)
#define FGIC_GICD_ISPENDR_READ(gicd_base, bank) FGIC_READREG32(gicd_base , FGIC_GICD_ISPENDR_OFFSET + (bank * FGIC_GICD_ISPENDR_BYTE_WIDTH))


/* FGIC_GICD_ICPENDR_OFFSET --- about spi pending */
#define FGIC_GICD_ICPENDR_DEFAULT_MASK  BIT_MASK(32)
#define FGIC_GICD_ICPENDR_VALUE_OFFSET(itnum) ((itnum % 32U))
#define FGIC_GICD_ICPENDR_VALUE_MASK(itnum)   (0x1U << FGIC_GICD_ICPENDR_VALUE_OFFSET(itnum))
#define FGIC_GICD_ICPENDR_READ_N_MASK(gicd_base,itnum)   FGIC_READREG32(gicd_base , FGIC_GICD_ICPENDR_OFFSET + ((itnum >> 5)<<2) )
#define FGIC_GICD_ICPENDR_WRITE_N_MASK(gicd_base,itnum,reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_ICPENDR_OFFSET + ((itnum >> 5)<<2), reg)




/* FGIC_GICD_IGROUPR_OFFSET ---  */
#define FGIC_GICD_IGROUPR_VALUE_OFFSET(itnum) ((itnum % 32U))
#define FGIC_GICD_IGROUPR_VALUE_MASK(itnum)   (0x1U << FGIC_GICD_IGROUPR_VALUE_OFFSET(itnum))
#define FGIC_GICD_IGROUPR_READ_N_MASK(gicd_base,itnum)   FGIC_READREG32(gicd_base , FGIC_GICD_IGROUPR_OFFSET + ((itnum >> 5)<<2) )
#define FGIC_GICD_IGROUPR_WRITE_N_MASK(gicd_base,itnum,reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_IGROUPR_OFFSET + ((itnum >> 5)<<2), reg)


/* FGIC_GICD_IGRPMODR_OFFSET --- Controls whether the corresponding interrupt is in Secure Group 0、Non-secure Group 1、 Secure Group 1 */
#define FGIC_GICD_IGRPMODR_DEFAULT_MASK BIT_MASK(32)
#define FGIC_GICD_IGRPMODR_VALUE_OFFSET(itnum) ((itnum % 32U))
#define FGIC_GICD_IGRPMODR_VALUE_MASK(itnum)   (0x1U << FGIC_GICD_IGRPMODR_VALUE_OFFSET(itnum))
#define FGIC_GICD_IGRPMODR_READ_N_MASK(gicd_base,itnum)   FGIC_READREG32(gicd_base , FGIC_GICD_IGRPMODR_OFFSET + ((itnum >> 5)<<2) )
#define FGIC_GICD_IGRPMODR_WRITE_N_MASK(gicd_base,itnum,reg) FGIC_WRITEREG32(gicd_base , FGIC_GICD_IGRPMODR_OFFSET + ((itnum >> 5)<<2), reg)


/* FGIC_GICR_TYPER_OFFSET --- Provides information about the configuration of this Redistributor. */
#define FGIC_GICR_TYPER_BYTE_WIDTH 4
#define FGIC_GICR_TYPER_L_READ(redis_base) FGIC_READREG32(redis_base , FGIC_GICR_TYPER_OFFSET)
#define FGIC_GICR_TYPER_H_READ(redis_base) FGIC_READREG32(redis_base , FGIC_GICR_TYPER_OFFSET + FGIC_GICR_TYPER_BYTE_WIDTH)

/* FGIC_GICR_WAKER_OFFSET ---  Permits software to control the behavior of the WakeRequest power management signal corresponding to the Redistributor */
#define FGIC_GICR_WAKER_PROCESSOR_SLEEP_MASK BIT(1)
#define FGIC_GICR_WAKER_CHILDREN_ASLEEP_MASK BIT(2)
#define FGIC_GICR_WAKER_CLEAR_BIT(redis_base, bit) FGIC_CLEARBIT(redis_base,FGIC_GICR_WAKER_OFFSET,bit)
#define FGIC_GICR_WAKER_WRITE(redis_base, reg) FGIC_WRITEREG32(redis_base , FGIC_GICR_WAKER_OFFSET, reg)
#define FGIC_GICR_WAKER_READ(redis_base) FGIC_READREG32(redis_base , FGIC_GICR_WAKER_OFFSET)

/* FGIC_GICR_IPRIORITYR_OFFSET --- Enables forwarding of the corresponding SGI or PPI to the CPU interfaces*/
#define FGIC_GICR_IPRIORITYR_VALUE_MASK(itnum)   (0xFFU << ((itnum % 4U) << 3))
#define FGIC_GICR_IPRIORITYR_READ(sgi_base,itnum)   FGIC_READREG32(sgi_base , FGIC_GICR_IPRIORITYR_OFFSET + ((itnum >> 2)<<2) )
#define FGIC_GICR_IPRIORITYR_WRITE(sgi_base,itnum,reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_IPRIORITYR_OFFSET + ((itnum >> 2)<<2), reg)

/* FGIC_GICR_ISPENDR0_OFFSET --- Adds the pending state to the corresponding SGI or PPI. */
#define FGIC_GICR_ISPENDR0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ISPENDR0_OFFSET, reg)
#define FGIC_GICR_ISPENDR0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ISPENDR0_OFFSET)

/* FGIC_GICR_ICPENDR0_OFFSET --- Removes the pending state from the corresponding SGI or PPI. */
#define FGIC_GICR_ICPENDR0_DEFAULT_MASK BIT_MASK(32)
#define FGIC_GICR_ICPENDR0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ICPENDR0_OFFSET, reg)
#define FGIC_GICR_ICPENDR0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ICPENDR0_OFFSET)

/* FGIC_GICR_ISACTIVER0_OFFSET --- Activates the corresponding SGI or PPI. These registers are used when saving and restoring GIC state. */

#define FGIC_GICR_ISACTIVER0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ISACTIVER0_OFFSET, reg)
#define FGIC_GICR_ISACTIVER0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ISACTIVER0_OFFSET)

/* FGIC_GICR_ICACTIVER0_OFFSET --- Deactivates the corresponding SGI or PPI. These registers are used when saving and restoring GIC state.*/
#define FGIC_GICR_ICACTIVER0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ICACTIVER0_OFFSET, reg)
#define FGIC_GICR_ICACTIVER0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ICACTIVER0_OFFSET)

/* FGIC_GICR_IGROUPR0_OFFSET --- Controls whether the corresponding SGI or PPI is in Group 0 or Group 1. */
#define FGIC_GICR_IGROUPR0_DEFAULT_MASK BIT_MASK(32)
#define FGIC_GICR_IGROUPR0_VALUE_OFFSET(itnum) ((itnum % 32U))
#define FGIC_GICR_IGROUPR0_VALUE_MASK(itnum)   (0x1U << FGIC_GICR_IGROUPR0_VALUE_OFFSET(itnum))
#define FGIC_GICR_IGROUPR0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_IGROUPR0_OFFSET, reg)
#define FGIC_GICR_IGROUPR0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_IGROUPR0_OFFSET)

/* FGIC_GICR_IGRPMODR0_OFFSET --- controls whether the corresponding interrupt is in: • Secure Group 0.• Non-secure Group 1.• When System register access is enabled, Secure Group 1. */
#define FGIC_GICR_IGRPMODR0_DEFAULT_MASK BIT_MASK(32)
#define FGIC_GICR_IGRPMODR0_VALUE_OFFSET(itnum) ((itnum % 32U))
#define FGIC_GICR_IGRPMODR0_VALUE_MASK(itnum)   (0x1U << FGIC_GICR_IGRPMODR0_VALUE_OFFSET(itnum))
#define FGIC_GICR_IGRPMODR0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_IGRPMODR0_OFFSET, reg)
#define FGIC_GICR_IGRPMODR0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_IGRPMODR0_OFFSET)

/* FGIC_GICR_ISENABLER0_OFFSET --- Enables forwarding of the corresponding interrupt to the CPU interfaces. */
#define FGIC_GICR_ISENABLER0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ISENABLER0_OFFSET, reg)
#define FGIC_GICR_ISENABLER0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ISENABLER0_OFFSET)

/* FGIC_GICR_ICENABLER0_OFFSET --- Disables forwarding of the corresponding interrupt to the CPU interfaces. */
#define FGIC_GICR_ICENABLER0_DEFAULT_MASK BIT_MASK(32)
#define FGIC_GICR_ICENABLER0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ICENABLER0_OFFSET, reg)
#define FGIC_GICR_ICENABLER0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ICENABLER0_OFFSET)

/* FGIC_GICR_ICFGR0_OFFSET */
#define FGIC_GICR_ICFGR0_DEFAULT_MASK   0
#define FGIC_GICR_ICFGR0_VALUE_OFFSET(itnum) ((itnum % 16U) << 1)
#define FGIC_GICR_ICFGR0_VALUE_MASK(itnum)   (0x3U << FGIC_GICR_ICFGR0_VALUE_OFFSET(itnum))
#define FGIC_GICR_ICFGR0_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ICFGR0_OFFSET, reg)
#define FGIC_GICR_ICFGR0_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ICFGR0_OFFSET)

/* FGIC_GICR_ICFGR1_OFFSET */
#define FGIC_GICR_ICFGR1_VALUE_OFFSET(itnum) ((itnum % 16U) << 1)
#define FGIC_GICR_ICFGR1_VALUE_MASK(itnum)   (0x3U << FGIC_GICR_ICFGR1_VALUE_OFFSET(itnum))
#define FGIC_GICR_ICFGR1_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_ICFGR1_OFFSET, reg)
#define FGIC_GICR_ICFGR1_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_ICFGR1_OFFSET)

/* FGIC_GICR_CTLR_OFFSET */

#define FGIC_GICR_CTLR_RWP_MASK BIT(2)

/* FGIC_GICR_NSACR_OFFSET */

#define FGIC_GICR_NSACR_WRITE(sgi_base, reg) FGIC_WRITEREG32(sgi_base , FGIC_GICR_NSACR_OFFSET, reg)
#define FGIC_GICR_NSACR_READ(sgi_base) FGIC_READREG32(sgi_base , FGIC_GICR_NSACR_OFFSET)

#ifdef __cplusplus
}
#endif

#endif
