/******************************************************************************
* Copyright (c) 2014 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xreg_cortexr5.h
*
* This header file contains definitions for using inline assembler code. It is
* written specifically for the GNU, IAR, ARMCC compiler.
*
* All of the ARM Cortex R5 GPRs, SPRs, and Debug Registers are defined along
* with the positions of the bits within the registers.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who      Date     Changes
* ----- -------- -------- -----------------------------------------------
* 5.00  pkp  02/10/14 Initial version
* </pre>
*
******************************************************************************/
#ifndef XREG_CORTEXR5_H /* prevent circular inclusions */
#define XREG_CORTEXR5_H /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* GPRs */
#define XREG_GPR0               r0
#define XREG_GPR1               r1
#define XREG_GPR2               r2
#define XREG_GPR3               r3
#define XREG_GPR4               r4
#define XREG_GPR5               r5
#define XREG_GPR6               r6
#define XREG_GPR7               r7
#define XREG_GPR8               r8
#define XREG_GPR9               r9
#define XREG_GPR10              r10
#define XREG_GPR11              r11
#define XREG_GPR12              r12
#define XREG_GPR13              r13
#define XREG_GPR14              r14
#define XREG_GPR15              r15
#define XREG_CPSR               cpsr

/* Coprocessor number defines */
#define XREG_CP0                0
#define XREG_CP1                1
#define XREG_CP2                2
#define XREG_CP3                3
#define XREG_CP4                4
#define XREG_CP5                5
#define XREG_CP6                6
#define XREG_CP7                7
#define XREG_CP8                8
#define XREG_CP9                9
#define XREG_CP10               10
#define XREG_CP11               11
#define XREG_CP12               12
#define XREG_CP13               13
#define XREG_CP14               14
#define XREG_CP15               15

/* Coprocessor control register defines */
#define XREG_CR0                cr0
#define XREG_CR1                cr1
#define XREG_CR2                cr2
#define XREG_CR3                cr3
#define XREG_CR4                cr4
#define XREG_CR5                cr5
#define XREG_CR6                cr6
#define XREG_CR7                cr7
#define XREG_CR8                cr8
#define XREG_CR9                cr9
#define XREG_CR10               cr10
#define XREG_CR11               cr11
#define XREG_CR12               cr12
#define XREG_CR13               cr13
#define XREG_CR14               cr14
#define XREG_CR15               cr15

/* Current Processor Status Register (CPSR) Bits */
#define XREG_CPSR_THUMB_MODE            0x20U
#define XREG_CPSR_MODE_BITS         0x1FU
#define XREG_CPSR_SYSTEM_MODE           0x1FU
#define XREG_CPSR_UNDEFINED_MODE        0x1BU
#define XREG_CPSR_DATA_ABORT_MODE       0x17U
#define XREG_CPSR_SVC_MODE          0x13U
#define XREG_CPSR_IRQ_MODE          0x12U
#define XREG_CPSR_FIQ_MODE          0x11U
#define XREG_CPSR_USER_MODE         0x10U

#define XREG_CPSR_IRQ_ENABLE            0x80U
#define XREG_CPSR_FIQ_ENABLE            0x40U

#define XREG_CPSR_N_BIT             0x80000000U
#define XREG_CPSR_Z_BIT             0x40000000U
#define XREG_CPSR_C_BIT             0x20000000U
#define XREG_CPSR_V_BIT             0x10000000U

/*MPU region definitions*/
#define REGION_32B     0x00000004U
#define REGION_64B     0x00000005U
#define REGION_128B    0x00000006U
#define REGION_256B    0x00000007U
#define REGION_512B    0x00000008U
#define REGION_1K      0x00000009U
#define REGION_2K      0x0000000AU
#define REGION_4K      0x0000000BU
#define REGION_8K      0x0000000CU
#define REGION_16K     0x0000000DU
#define REGION_32K     0x0000000EU
#define REGION_64K     0x0000000FU
#define REGION_128K    0x00000010U
#define REGION_256K    0x00000011U
#define REGION_512K    0x00000012U
#define REGION_1M      0x00000013U
#define REGION_2M      0x00000014U
#define REGION_4M      0x00000015U
#define REGION_8M      0x00000016U
#define REGION_16M     0x00000017U
#define REGION_32M     0x00000018U
#define REGION_64M     0x00000019U
#define REGION_128M    0x0000001AU
#define REGION_256M    0x0000001BU
#define REGION_512M    0x0000001CU
#define REGION_1G      0x0000001DU
#define REGION_2G      0x0000001EU
#define REGION_4G      0x0000001FU

#define REGION_EN  0x00000001U



#define SHAREABLE               0x00000004U     /*shareable */
#define STRONG_ORDERD_SHARED    0x00000000U /*strongly ordered, always shareable*/

#define DEVICE_SHARED           0x00000001U /*device, shareable*/
#define DEVICE_NONSHARED        0x00000010U /*device, non shareable*/

#define NORM_NSHARED_WT_NWA     0x00000002U     /*Outer and Inner write-through, no write-allocate non-shareable*/
#define NORM_SHARED_WT_NWA      0x00000006U     /*Outer and Inner write-through, no write-allocate shareable*/

#define NORM_NSHARED_WB_NWA     0x00000003U     /*Outer and Inner write-back, no write-allocate non shareable*/
#define NORM_SHARED_WB_NWA      0x00000007U     /*Outer and Inner write-back, no write-allocate shareable*/

#define NORM_NSHARED_NCACHE     0x00000008U     /*Outer and Inner Non cacheable  non shareable*/
#define NORM_SHARED_NCACHE      0x0000000CU     /*Outer and Inner Non cacheable shareable*/

#define NORM_NSHARED_WB_WA      0x0000000BU     /*Outer and Inner write-back non shared*/
#define NORM_SHARED_WB_WA       0x0000000FU     /*Outer and Inner write-back shared*/

/* inner and outer cache policies can be combined for different combinations */

#define NORM_IN_POLICY_NCACHE   0x00000020U /*inner non cacheable*/
#define NORM_IN_POLICY_WB_WA    0x00000021U /*inner write back write allocate*/
#define NORM_IN_POLICY_WT_NWA   0x00000022U /*inner write through no write allocate*/
#define NORM_IN_POLICY_WB_NWA   0x00000023U /*inner write back no write allocate*/

#define NORM_OUT_POLICY_NCACHE  0x00000020U /*outer non cacheable*/
#define NORM_OUT_POLICY_WB_WA   0x00000028U /*outer write back write allocate*/
#define NORM_OUT_POLICY_WT_NWA  0x00000030U /*outer write through no write allocate*/
#define NORM_OUT_POLICY_WB_NWA  0x00000038U /*outer write back no write allocate*/

#define NO_ACCESS               (0x00000000U<<8U)   /*No access*/
#define PRIV_RW_USER_NA         (0x00000001U<<8U) /*Privileged access only*/
#define PRIV_RW_USER_RO         (0x00000002U<<8U) /*Writes in User mode generate permission faults*/
#define PRIV_RW_USER_RW         (0x00000003U<<8U)   /*Full Access*/
#define PRIV_RO_USER_NA         (0x00000005U<<8U) /*Privileged eead only*/
#define PRIV_RO_USER_RO         (0x00000006U<<8U) /*Privileged/User read-only*/

#define EXECUTE_NEVER           (0x00000001U<<12U)  /* Bit 12*/


/* CP15 defines */

/* C0 Register defines */
#define XREG_CP15_MAIN_ID           "p15, 0, %0,  c0,  c0, 0"
#define XREG_CP15_CACHE_TYPE            "p15, 0, %0,  c0,  c0, 1"
#define XREG_CP15_TCM_TYPE          "p15, 0, %0,  c0,  c0, 2"
#define XREG_CP15_TLB_TYPE          "p15, 0, %0,  c0,  c0, 3"
#define XREG_CP15_MPU_TYPE          "p15, 0, %0,  c0,  c0, 4"
#define XREG_CP15_MULTI_PROC_AFFINITY       "p15, 0, %0,  c0,  c0, 5"

#define XREG_CP15_PROC_FEATURE_0        "p15, 0, %0,  c0,  c1, 0"
#define XREG_CP15_PROC_FEATURE_1        "p15, 0, %0,  c0,  c1, 1"
#define XREG_CP15_DEBUG_FEATURE_0       "p15, 0, %0,  c0,  c1, 2"
#define XREG_CP15_MEMORY_FEATURE_0      "p15, 0, %0,  c0,  c1, 4"
#define XREG_CP15_MEMORY_FEATURE_1      "p15, 0, %0,  c0,  c1, 5"
#define XREG_CP15_MEMORY_FEATURE_2      "p15, 0, %0,  c0,  c1, 6"
#define XREG_CP15_MEMORY_FEATURE_3      "p15, 0, %0,  c0,  c1, 7"

#define XREG_CP15_INST_FEATURE_0        "p15, 0, %0,  c0,  c2, 0"
#define XREG_CP15_INST_FEATURE_1        "p15, 0, %0,  c0,  c2, 1"
#define XREG_CP15_INST_FEATURE_2        "p15, 0, %0,  c0,  c2, 2"
#define XREG_CP15_INST_FEATURE_3        "p15, 0, %0,  c0,  c2, 3"
#define XREG_CP15_INST_FEATURE_4        "p15, 0, %0,  c0,  c2, 4"
#define XREG_CP15_INST_FEATURE_5        "p15, 0, %0,  c0,  c2, 5"

#define XREG_CP15_CACHE_SIZE_ID         "p15, 1, %0,  c0,  c0, 0"
#define XREG_CP15_CACHE_LEVEL_ID        "p15, 1, %0,  c0,  c0, 1"
#define XREG_CP15_AUXILARY_ID           "p15, 1, %0,  c0,  c0, 7"

#define XREG_CP15_CACHE_SIZE_SEL        "p15, 2, %0,  c0,  c0, 0"

/* C1 Register Defines */
#define XREG_CP15_SYS_CONTROL           "p15, 0, %0,  c1,  c0, 0"
#define XREG_CP15_AUX_CONTROL           "p15, 0, %0,  c1,  c0, 1"
#define XREG_CP15_CP_ACCESS_CONTROL     "p15, 0, %0,  c1,  c0, 2"


/* XREG_CP15_CONTROL bit defines */
#define XREG_CP15_CONTROL_TE_BIT        0x40000000U
#define XREG_CP15_CONTROL_AFE_BIT       0x20000000U
#define XREG_CP15_CONTROL_TRE_BIT       0x10000000U
#define XREG_CP15_CONTROL_NMFI_BIT      0x08000000U
#define XREG_CP15_CONTROL_EE_BIT        0x02000000U
#define XREG_CP15_CONTROL_HA_BIT        0x00020000U
#define XREG_CP15_CONTROL_RR_BIT        0x00004000U
#define XREG_CP15_CONTROL_V_BIT         0x00002000U
#define XREG_CP15_CONTROL_I_BIT         0x00001000U
#define XREG_CP15_CONTROL_Z_BIT         0x00000800U
#define XREG_CP15_CONTROL_SW_BIT        0x00000400U
#define XREG_CP15_CONTROL_B_BIT         0x00000080U
#define XREG_CP15_CONTROL_C_BIT         0x00000004U
#define XREG_CP15_CONTROL_A_BIT         0x00000002U
#define XREG_CP15_CONTROL_M_BIT         0x00000001U
/* C2 Register Defines */
/* Not Used */

/* C3 Register Defines */
/* Not Used */

/* C4 Register Defines */
/* Not Used */

/* C5 Register Defines */
#define XREG_CP15_DATA_FAULT_STATUS     "p15, 0, %0,  c5,  c0, 0"
#define XREG_CP15_INST_FAULT_STATUS     "p15, 0, %0,  c5,  c0, 1"

#define XREG_CP15_AUX_DATA_FAULT_STATUS     "p15, 0, %0,  c5,  c1, 0"
#define XREG_CP15_AUX_INST_FAULT_STATUS     "p15, 0, %0,  c5,  c1, 1"

/* C6 Register Defines */
#define XREG_CP15_DATA_FAULT_ADDRESS        "p15, 0, %0,  c6,  c0, 0"
#define XREG_CP15_INST_FAULT_ADDRESS        "p15, 0, %0,  c6,  c0, 2"

#define XREG_CP15_MPU_REG_BASEADDR          "p15, 0, %0,  c6,  c1, 0"
#define XREG_CP15_MPU_REG_SIZE_EN           "p15, 0, %0,  c6,  c1, 2"
#define XREG_CP15_MPU_REG_ACCESS_CTRL       "p15, 0, %0,  c6,  c1, 4"

#define XREG_CP15_MPU_MEMORY_REG_NUMBER         "p15, 0, %0,  c6,  c2, 0"

/* C7 Register Defines */
#define XREG_CP15_NOP               "p15, 0, %0,  c7,  c0, 4"

#define XREG_CP15_INVAL_IC_POU          "p15, 0, %0,  c7,  c5, 0"
#define XREG_CP15_INVAL_IC_LINE_MVA_POU     "p15, 0, %0,  c7,  c5, 1"

/* The CP15 register access below has been deprecated in favor of the new
 * isb instruction in Cortex R5.
 */
#define XREG_CP15_INST_SYNC_BARRIER     "p15, 0, %0,  c7,  c5, 4"
#define XREG_CP15_INVAL_BRANCH_ARRAY        "p15, 0, %0,  c7,  c5, 6"
#define XREG_CP15_INVAL_BRANCH_ARRAY_LINE       "p15, 0, %0,  c7,  c5, 7"

#define XREG_CP15_INVAL_DC_LINE_MVA_POC     "p15, 0, %0,  c7,  c6, 1"
#define XREG_CP15_INVAL_DC_LINE_SW      "p15, 0, %0,  c7,  c6, 2"


#define XREG_CP15_CLEAN_DC_LINE_MVA_POC     "p15, 0, %0,  c7, c10, 1"
#define XREG_CP15_CLEAN_DC_LINE_SW      "p15, 0, %0,  c7, c10, 2"

#define XREG_CP15_INVAL_DC_ALL      "p15, 0, %0,  c15, c5, 0"
/* The next two CP15 register accesses below have been deprecated in favor
 * of the new dsb and dmb instructions in Cortex R5.
 */
#define XREG_CP15_DATA_SYNC_BARRIER     "p15, 0, %0,  c7, c10, 4"
#define XREG_CP15_DATA_MEMORY_BARRIER       "p15, 0, %0,  c7, c10, 5"

#define XREG_CP15_CLEAN_DC_LINE_MVA_POU     "p15, 0, %0,  c7, c11, 1"

#define XREG_CP15_NOP2              "p15, 0, %0,  c7, c13, 1"

#define XREG_CP15_CLEAN_INVAL_DC_LINE_MVA_POC   "p15, 0, %0,  c7, c14, 1"
#define XREG_CP15_CLEAN_INVAL_DC_LINE_SW    "p15, 0, %0,  c7, c14, 2"

/* C8 Register Defines */
/* Not Used */


/* C9 Register Defines */

#define XREG_CP15_ATCM_REG_SIZE_ADDR        "p15, 0, %0,  c9, c1, 1"
#define XREG_CP15_BTCM_REG_SIZE_ADDR        "p15, 0, %0,  c9, c1, 0"
#define XREG_CP15_TCM_SELECTION             "p15, 0, %0,  c9, c2, 0"

#define XREG_CP15_PERF_MONITOR_CTRL     "p15, 0, %0,  c9, c12, 0"
#define XREG_CP15_COUNT_ENABLE_SET      "p15, 0, %0,  c9, c12, 1"
#define XREG_CP15_COUNT_ENABLE_CLR      "p15, 0, %0,  c9, c12, 2"
#define XREG_CP15_V_FLAG_STATUS         "p15, 0, %0,  c9, c12, 3"
#define XREG_CP15_SW_INC            "p15, 0, %0,  c9, c12, 4"
#define XREG_CP15_EVENT_CNTR_SEL        "p15, 0, %0,  c9, c12, 5"

#define XREG_CP15_PERF_CYCLE_COUNTER        "p15, 0, %0,  c9, c13, 0"
#define XREG_CP15_EVENT_TYPE_SEL        "p15, 0, %0,  c9, c13, 1"
#define XREG_CP15_PERF_MONITOR_COUNT        "p15, 0, %0,  c9, c13, 2"

#define XREG_CP15_USER_ENABLE           "p15, 0, %0,  c9, c14, 0"
#define XREG_CP15_INTR_ENABLE_SET       "p15, 0, %0,  c9, c14, 1"
#define XREG_CP15_INTR_ENABLE_CLR       "p15, 0, %0,  c9, c14, 2"

/* C10 Register Defines */
/* Not used */

/* C11 Register Defines */
/* Not used */

/* C12 Register Defines */
/* Not used */

/* C13 Register Defines */
#define XREG_CP15_CONTEXT_ID            "p15, 0, %0, c13,  c0, 1"
#define USER_RW_THREAD_PID          "p15, 0, %0, c13,  c0, 2"
#define USER_RO_THREAD_PID          "p15, 0, %0, c13,  c0, 3"
#define USER_PRIV_THREAD_PID            "p15, 0, %0, c13,  c0, 4"

/* C14 Register Defines */
/* not used */

/* C15 Register Defines */
#define XREG_CP15_SEC_AUX_CTRL          "p15, 0, %0, c15,  c0, 0"




/* MPE register definitions */
#define XREG_FPSID              c0
#define XREG_FPSCR              c1
#define XREG_MVFR1              c6
#define XREG_MVFR0              c7
#define XREG_FPEXC              c8
#define XREG_FPINST             c9
#define XREG_FPINST2            c10

/* FPSID bits */
#define XREG_FPSID_IMPLEMENTER_BIT  (24U)
#define XREG_FPSID_IMPLEMENTER_MASK (0x000000FFU << FPSID_IMPLEMENTER_BIT)
#define XREG_FPSID_SOFTWARE     (0X00000001U << 23U)
#define XREG_FPSID_ARCH_BIT     (16U)
#define XREG_FPSID_ARCH_MASK        (0x0000000FU  << FPSID_ARCH_BIT)
#define XREG_FPSID_PART_BIT     (8U)
#define XREG_FPSID_PART_MASK        (0x000000FFU << FPSID_PART_BIT)
#define XREG_FPSID_VARIANT_BIT      (4U)
#define XREG_FPSID_VARIANT_MASK     (0x0000000FU  << FPSID_VARIANT_BIT)
#define XREG_FPSID_REV_BIT      (0U)
#define XREG_FPSID_REV_MASK     (0x0000000FU  << FPSID_REV_BIT)

/* FPSCR bits */
#define XREG_FPSCR_N_BIT        (0X00000001U << 31U)
#define XREG_FPSCR_Z_BIT        (0X00000001U << 30U)
#define XREG_FPSCR_C_BIT        (0X00000001U << 29U)
#define XREG_FPSCR_V_BIT        (0X00000001U << 28U)
#define XREG_FPSCR_QC           (0X00000001U << 27U)
#define XREG_FPSCR_AHP          (0X00000001U << 26U)
#define XREG_FPSCR_DEFAULT_NAN      (0X00000001U << 25U)
#define XREG_FPSCR_FLUSHTOZERO      (0X00000001U << 24U)
#define XREG_FPSCR_ROUND_NEAREST    (0X00000000U << 22U)
#define XREG_FPSCR_ROUND_PLUSINF    (0X00000001U << 22U)
#define XREG_FPSCR_ROUND_MINUSINF   (0X00000002U << 22U)
#define XREG_FPSCR_ROUND_TOZERO     (0X00000003U << 22U)
#define XREG_FPSCR_RMODE_BIT        (22U)
#define XREG_FPSCR_RMODE_MASK       (0X00000003U << FPSCR_RMODE_BIT)
#define XREG_FPSCR_STRIDE_BIT       (20U)
#define XREG_FPSCR_STRIDE_MASK      (0X00000003U << FPSCR_STRIDE_BIT)
#define XREG_FPSCR_LENGTH_BIT       (16U)
#define XREG_FPSCR_LENGTH_MASK      (0X00000007U << FPSCR_LENGTH_BIT)
#define XREG_FPSCR_IDC          (0X00000001U << 7U)
#define XREG_FPSCR_IXC          (0X00000001U << 4U)
#define XREG_FPSCR_UFC          (0X00000001U << 3U)
#define XREG_FPSCR_OFC          (0X00000001U << 2U)
#define XREG_FPSCR_DZC          (0X00000001U << 1U)
#define XREG_FPSCR_IOC          (0X00000001U << 0U)

/* MVFR0 bits */
#define XREG_MVFR0_RMODE_BIT        (28U)
#define XREG_MVFR0_RMODE_MASK       (0x0000000FU << XREG_MVFR0_RMODE_BIT)
#define XREG_MVFR0_SHORT_VEC_BIT    (24U)
#define XREG_MVFR0_SHORT_VEC_MASK   (0x0000000FU << XREG_MVFR0_SHORT_VEC_BIT)
#define XREG_MVFR0_SQRT_BIT     (20U)
#define XREG_MVFR0_SQRT_MASK        (0x0000000FU << XREG_MVFR0_SQRT_BIT)
#define XREG_MVFR0_DIVIDE_BIT       (16U)
#define XREG_MVFR0_DIVIDE_MASK      (0x0000000FU << XREG_MVFR0_DIVIDE_BIT)
#define XREG_MVFR0_EXEC_TRAP_BIT    (12U)
#define XREG_MVFR0_EXEC_TRAP_MASK   (0x0000000FU << XREG_MVFR0_EXEC_TRAP_BIT)
#define XREG_MVFR0_DP_BIT       (8U)
#define XREG_MVFR0_DP_MASK      (0x0000000FU << XREG_MVFR0_DP_BIT)
#define XREG_MVFR0_SP_BIT       (4U)
#define XREG_MVFR0_SP_MASK      (0x0000000FU << XREG_MVFR0_SP_BIT)
#define XREG_MVFR0_A_SIMD_BIT       (0U)
#define XREG_MVFR0_A_SIMD_MASK      (0x0000000FU << MVFR0_A_SIMD_BIT)

/* FPEXC bits */
#define XREG_FPEXC_EX           (0X00000001U << 31U)
#define XREG_FPEXC_EN           (0X00000001U << 30U)
#define XREG_FPEXC_DEX          (0X00000001U << 29U)


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XREG_CORTEXR5_H */
