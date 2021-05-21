/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-26 10:49:20
 * @Description:  This files is for gic v2.0 register implementation
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef GICV3_HW_H
#define GICV3_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_parameters.h"
#include "ft_gicv3.h"
    /* interrupt priority  */

#define SHIFT_PER_WORD 5
#define BITS_PER_WORD 32
#define CONFIGS_PER_WORD 16
#define PRIOS_PER_WORD 4
#define TARGETS_PER_WORD 4
#define NWORD(bitnum) (bitnum / 32)
#define BIT(bitnum) (1 << (bitnum % BITS_PER_WORD))

#define GIC_PRIO(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_IPRIORITYR_OFFSET + \
                                                          (0x4 * (Periph / PRIOS_PER_WORD))))

#define GIR_PRIO(gic_redist_addr, Periph) ((volatile u32 *)(gic_redist_addr + GICR_IPRIORITYR_OFFSET + \
                                                            (0x4 * (Periph / PRIOS_PER_WORD))))

    /* clear interrupt enable */

#define GIC_INTENCLR(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_ICENABLE_OFFSET + \
                                                              (0x4 * NWORD(Periph))))

    /* set interrupt enable  */
#define GICD_ISENABLER(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_ISENABLER_OFFSET + \
                                                                (0x4 * NWORD(Periph))))

    /* clear pending interrupt */

#define GIC_INTPENDCLR(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_ICPENDR_OFFSET + \
                                                                (0x4 * NWORD(Periph))))

    /* CPU target */

#define GIC_CPUTARG(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_ITARGETSR_OFFSET + \
                                                             (0x4 * (Periph / TARGETS_PER_WORD))))

    /* Interrupt Routing */

#define GIC_INTRPUTE_LOW(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_IROUTER_E_OFFSET + \
                                                                  (0x8 * (Periph))))

#define GIC_INTRPUTE_HIGH(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_IROUTER_E_OFFSET + \
                                                                   (0x8 * (Periph)) + 4)) /* interrupt configuration */

#define GIC_CONFIG(gic_dist_addr, Periph) ((volatile u32 *)(gic_dist_addr + GICD_ICFGR_OFFSET + \
                                                            (0x4 * (Periph / CONFIGS_PER_WORD))))

#define GIC_TRIGGER_LEVEL_SENSITIVE 0
#define GIC_TRIGGER_EDGE_SENSITIVE 1

    /* ARM GIC interrupt distributor and CPU interface register access macros */

#define GIC_CPU_DIR_DEFAULT 0x01010101    /* all interrupts are directed to CPU0 */
#define GIC_V3_CPU_DIR_DEFAULT_LOW 0x0llu /* all interrupts are directed to CPU0 */
#define GIC_V3_CPU_DIR_DEFAULT_HIGH 0
#define GIC_CONTROL_ENABLE 0x01

#define GIC_INT_ALL_ENABLED 0xFF         /* priority 0-0xFF can run */
#define GIC_INT_ALL_DISABLED 0x00        /* nothing higher than 0 hence disabled */
#define GIC_INT_SPURIOUS 0x3FF           /* no interrupt currently */
#define GIC_INT_ONEMINUS_HIGH 0x55555555 /* interrupt config to 1-N, High */
#define GIC_CPU_BINP_DEFAULT 0x07        /* split all priority to subpriority */
#define GIC_CPU_BINP_PREEMPT_VAL 0x1     /* split all priority to group-priority */
#define GIC_CPU_BINP_NONPREEMPT_VAL 0x07 /* split all priority to sub-priority */
#define GIC_CPU_CONTROL_ENABLE 0x1       /* enable the processor interface */
#define GIC_CPU_ALL_ENABLED 0xFF         /* priority 0-E can run */
#define GIC_CPU_ALL_DISABLED 0x00        /* nothing higher than 0 */
#define GIC_SGI_SRC_CPU_ID_MASK 0x1C00
#define GIC_INT_HIGHEST_PRIORITY 0x0 /* the highest priority for interrupts */
#define GIC_INT_LOWEST_PRIORITY 0x1F /* the lowest priority for interrupts */
#define GIC_INT_PRIORITY_SHIFT 0x8
#define GIC_INT_PRIORITY_MASK 0xFF

#define GIC_INT_TRIGGER_SHIFT 0x2
    /************ Distributor register map  ****************/

#define GICD_CTLR_OFFSET 0x00000000U          /*  Distributor Control Register  */
#define GICD_TYPER_OFFSET 0x00000004U         /* Interrupt Controller Type Register */
#define GICD_IIDR_OFFSET 0x00000008U          /* Distributor Implementer Identification Register */
#define GICD_TYPER2_OFFSET 0x0000000CU        /* Interrupt controller Type Register 2 */
#define GICD_STATUSR_OFFSET 0x00000010U       /* Error Reporting Status Register, optional */
#define GICD_SETSPI_NSR_OFFSET 0x00000040U    /*  Set SPI Register */
#define GICD_CLRSPI_NSR_OFFSET 0x00000048U    /* Clear SPI Register */
#define GICD_SETSPI_SR_OFFSET 0x00000050U     /*  Set SPI, Secure Register */
#define GICD_CLRSPI_SR_OFFSET 0x00000058U     /* Clear SPI, Secure Register */
#define GICD_IGROUPR_OFFSET 0x00000080U       /* Interrupt Group Registers  */
#define GICD_ISENABLER_OFFSET 0x00000100U     /* Interrupt Set-Enable Registers  */
#define GICD_ICENABLE_OFFSET 0x00000180U      /* Interrupt Clear-Enable Registers */
#define GICD_ISPENDR_OFFSET 0x00000200U       /* Interrupt Set-Pending Registers */
#define GICD_ICPENDR_OFFSET 0x00000280U       /* Interrupt Clear-Pending Registers */
#define GICD_ISACTIVER_OFFSET 0x00000300U     /* Interrupt Set-Active Registers */
#define GICD_ICACTIVER_OFFSET 0x00000380U     /* Interrupt Clear-Active Registers */
#define GICD_IPRIORITYR_OFFSET 0x00000400U    /* Interrupt Priority Registers */
#define GICD_ITARGETSR_OFFSET 0x00000800U     /* Interrupt Processor Targets Registers  */
#define GICD_ICFGR_OFFSET 0x00000C00U         /* Interrupt Configuration Registers */
#define GICD_IGRPMODR_OFFSET 0x00000D00U      /* Interrupt Group Modifier Registers  */
#define GICD_NSACR_OFFSET 0x000000E00U        /* Non-secure Access Control Registers */
#define GICD_SGIR_OFFSET 0x000000F00U         /* Software Generated Interrupt Register */
#define GICD_CPENDSGIR_OFFSET 0x000000F10U    /* SGI Clear-Pending Registers */
#define GICD_SPENDSGIR_OFFSET 0x000000F20U    /* SGI Set-Pending Registers */
#define GICD_IGROUPR_E_OFFSET 0x000001000U    /* Interrupt Group Registers for extended SPI range */
#define GICD_ISENABLER_E_OFFSET 0x000001200U  /* Interrupt Set-Enable for extended SPI range */
#define GICD_ICENABLER_E_OFFSET 0x000001400U  /* Interrupt Clear-Enable for extended SPI range */
#define GICD_ISPENDR_E_OFFSET 0x000001600U    /* Interrupt Set-Pend for extended SPI range */
#define GICD_ICPENDR_E_OFFSET 0x000001800U    /* Interrupt Clear-Pend for extended SPI  range */
#define GICD_ISACTIVER_E_OFFSET 0x000001A00U  /* Interrupt Set-Active for extended SPI  range */
#define GICD_ICACTIVER_E_OFFSET 0x000001C00U  /* Interrupt Clear-Active for extended SPI  range */
#define GICD_IPRIORITYR_E_OFFSET 0x000002000U /* Interrupt Priority for extended SPI range */
#define GICD_ICFGR_E_OFFSET 0x000003000U      /* Extended SPI Configuration Register */
#define GICD_IGRPMODR_E_OFFSET 0x000003400U   /* Interrupt Group Modifier for extended SPI range */
#define GICD_NSACR_E_OFFSET 0x000003600U      /* Non-secure Access Control Registers for extended SPI range */
#define GICD_IROUTER_E_OFFSET 0x000006000U    /*  Interrupt Routing Registers  */
#define GICD_IROUTER_E_E_OFFSET 0x000008000U  /* Interrupt Routing Registers for extended SPI range */

    /************ physical LPI Redistributor register map ****************/

#define GICR_CTLR_OFFSET 0x0000      /*See the register description Redistributor Control Register*/
#define GICR_IIDR_OFFSET 0x0004      /*IMPLEMENTATION DEFINED Implementer Identification Register*/
#define GICR_TYPER_OFFSET 0x0008     /*IMPLEMENTATION DEFINED Redistributor Type Register*/
#define GICR_STATUSR_OFFSET 0x0010   /*0x0000 0000 Error Reporting Status Register, optional*/
#define GICR_WAKER_OFFSET 0x0014     /*See the register description Redistributor Wake Register*/
#define GICR_MPAMIDR_OFFSET 0x0018   /*- Report maximum PARTID and PMG Register*/
#define GICR_PARTIDR_OFFSET 0x001C   /*0 Set PARTID and PMG Register*/
#define GICR_SETLPIRa_OFFSET 0x0040  /*- Set LPI Pending Register*/
#define GICR_CLRLPIRa_OFFSET 0x0048  /*- Clear LPI Pending Register*/
#define GICR_PROPBASER_OFFSET 0x0070 /*- Redistributor Properties Base Address Register*/
#define GICR_PENDBASER_OFFSET 0x0078 /*- Redistributor LPI Pending Table Base Address*/
#define GICR_INVLPIRA_OFFSET 0x00A0  /*Redistributor Invalidate LPI Register*/
#define GICR_INVALLRA_OFFSET 0x00B0  /*Redistributor Invalidate All Register */
#define GICR_SYNCRA_OFFSET 0x00C0    /*Redistributor Synchronize Register*/

#define GICR_WAKER_CPU(gicr_addr, cpu) ((gicr_addr + cpu * (2 << 16) + GICR_WAKER_OFFSET))

/******************* SGI and PPI Redistributor register map ************************/
#define GICR_IGROUPR0_OFFSET 0x0080     /* Interrupt Group Register 0*/
#define GICR_ISENABLER0_OFFSET 0x0100   /* DEFINED Interrupt Set-Enable Register 0*/
#define GICR_ICENABLER0_OFFSET 0x0180   /* DEFINED Interrupt Clear-Enable Register 0*/
#define GICR_ISPENDR0_OFFSET 0x0200     /*  Interrupt Set-Pend Register 0*/
#define GICR_ICPENDR0_OFFSET 0x0280     /*  Interrupt Clear-Pend Register 0*/
#define GICR_ISACTIVER0_OFFSET 0x0300   /*  Interrupt Set-Active Register 0*/
#define GICR_ICACTIVER0_OFFSET 0x0380   /*  Interrupt Clear-Active Register 0*/
#define GICR_IPRIORITYR_OFFSET 0x0400   /* Interrupt Priority Registers*/
#define GICR_IGROUPR_E_OFFSET 0x0084    /*Interrupt Group Registers for extended PPI range*/
#define GICR_ISENABLER_E_OFFSET 0x0104  /* Interrupt Set-Enable for extended PPI range*/
#define GICR_ICENABLER_E_OFFSET 0x0184  /* Interrupt Clear-Enable for extended PPI range*/
#define GICR_ISPENDR_E_OFFSET 0x0204    /* Interrupt Set-Pend for extended PPI range*/
#define GICR_ICPENDR_E_OFFSET 0x0284    /* Interrupt Clear-Pend for extended PPI range*/
#define GICR_ISACTIVER_E_OFFSET 0x0304  /* Interrupt Set-Active for extended PPI range*/
#define GICR_ICACTIVER_E_OFFSET 0x0384  /* Interrput Clear-Active for extended PPI range*/
#define GICR_IPRIORITYR_E_OFFSET 0x0420 /* Interrupt Priority for extended PPI range*/
#define GICR_ICFGR_E_OFFSET 0x0C08      /* Extended PPI Configuration Register */
#define GICR_IGRPMODR_E_OFFSET 0x0D04   /* Interrupt Group Modifier for extended PPI range */
#define GICR_ICFGR0_OFFSET 0x0C00       /*SGI Configuration Register*/
#define GICR_ICFGR1_OFFSET 0x0C04       /*PPI Configuration Register*/
#define GICR_IGRPMODR0_OFFSET 0x0D00    /*Interrupt Group Modifier Register 0*/
#define GICR_NSACR_OFFSET 0x0E00        /* Secure Access Control Register*/

#define GICR_INTENABLE_CPU(gic_dist_addr, cpu) ((gic_dist_addr + cpu * (2 << 16) + GICR_ISENABLER0_OFFSET))
#define GICR_INTENCLR_CPU(gic_dist_addr, cpu) ((gic_dist_addr + cpu * (2 << 16) + GICR_ICENABLER0_OFFSET))

/****************** CPU interface register map *************************/
#ifdef CPU_GICC_SUPPORT

#define GICC_CTLR_OFFSET 0x0000    /*See the register description CPU Interface Control Register*/
#define GICC_PMR_OFFSET 0x0004     /* Interrupt Priority Mask Register*/
#define GICC_BPR_OFFSET 0x0008     /* Binary Point Register*/
#define GICC_IAR_OFFSET 0x000C     /* Interrupt Acknowledge Register*/
#define GICC_EOIR_OFFSET 0x0010    /* End of Interrupt Register*/
#define GICC_RPR_OFFSET 0x0014     /* Running Priority Register*/
#define GICC_HPPIR_OFFSET 0x0018   /* Highest Priority Pending Interrupt Register*/
#define GICC_ABPR_OFFSET 0x001C    /* Aliased Binary Point Register*/
#define GICC_AIAR_OFFSET 0x0020    /* Aliased Interrupt Acknowledge Register*/
#define GICC_AEOIR_OFFSET 0x0024   /* Aliased End of Interrupt Register*/
#define GICC_AHPPIR_OFFSET 0x0028  /* Aliased Highest Priority Pending Interrupt Register*/
#define GICC_STATUSR_OFFSET 0x002C /* Error Reporting Status Register, optional*/
#define GICC_APR_OFFSET 0x00D0     /* Active Priorities Registers*/
#define GICC_NSAPR_OFFSET 0x00E0   /* Non-secure Active Priorities Registers*/
#define GICC_IIDR_OFFSET 0x00FC    /* CPU Interface Identification Register */
#define GICC_DIR_OFFSET 0x1000     /* Deactivate Interrupt Register */

#endif

    /** Redistributor Wake Register **/

#define GICC_WAKER_PROCESSORSLEEP_IN (1U << 1)
#define GICC_WAKER_PROCESSORSLEEP_NOT_IN (0U << 1)

#define GICC_WAKER_CHILDRENASLEEP_ACTIVE (0U << 2)
#define GICC_WAKER_CHILDRENASLEEP_QUIESCENT (1U << 2)

    /** GICR_ISENABLER0  **/

#define ALL_PPI_INT_MASK 0xFFFF0000 /* bit field for all PPI interrupts */
#define ALL_SGI_INT_MASK 0x0000FFFF /* bit field for all SGI interrupts */

    /** ICC_SRE **/

#define ICC_SRE_SRE (1U << 0)

/** GICD_IPRIORITYR **/
#define GICD_IPRIORITYR_MASK 0xffU

/** GICD_ICFGR **/
#define GICD_ICFGR_MASK 0x03

    /** GICD_CTLR **/

#define GICD_CTLR_MASK 1

    /**************************** Function Prototypes  ****************************************/
    s32 FGicv3_InstanceInitialize(FGicv3_Config_t *Config);
    void FGicv3_InterruptHandler(u32 CurrentLevel, u32 InstanceId);
    s32 FGicv3_RegisterHandler(FGicv3_Config_t *Config, u32 InterruptID, FGicv3_InterruptHandler_t InterruptHandler, void *Args);
    s32 FGicV3_SetPriTrigTypeByDistAddr(u32 GicBaseAddress, u32 InterruptID, u8 Trigger, u8 Priorty);
    void FGicV3_GetPriTrigTypeByDistAddr(u32 GicBaseAddress, u32 InterruptID, u8 *Trigger, u8 *Priorty);
    void FGicV3_InterruptUnmapByDistAddr(u32 GicBaseAddress, u32 InterruptID, u8 CpuID);
    void FGicV3_DisableInterrupt(FGicv3_Config_t *Config, u32 InterruptID);
    void FGicV3_EnableInterrupt(FGicv3_Config_t *Config, u32 InterruptID);
    void FGicV3_Stop(FGicv3_Config_t *Config, u8 CpuID);

#ifdef __cplusplus
}
#endif

#endif //