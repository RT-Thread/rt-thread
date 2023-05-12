/*
 * @Copyright : (C) 2022 Phytium Information Technology, Inc. 
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
 * @FilePath: fgic_cpu_interface.S
 * @Date: 2022-03-29 18:04:23
 * @LastEditTime: 2022-03-29 18:04:27
 * @Description:  This file is Mapping of MSR and MRS to physical and virtual CPU interface registers.
 * 
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */


#ifdef __aarch64__

/*
 * Mapping of MSR and MRS to physical and virtual CPU interface registers
 *
 * ARM Generic Interrupt Controller Architecture Specification
 * GIC architecture version 3.0 and version 4.0
 * Table 8-5
 */
#define ICC_AP0R0_EL1 S3_0_C12_C8_4
#define ICC_AP0R1_EL1 S3_0_C12_C8_5
#define ICC_AP0R2_EL1 S3_0_C12_C8_6
#define ICC_AP0R3_EL1 S3_0_C12_C8_7

#define ICC_AP1R0_EL1 S3_0_C12_C9_0
#define ICC_AP1R1_EL1 S3_0_C12_C9_1
#define ICC_AP1R2_EL1 S3_0_C12_C9_2
#define ICC_AP1R3_EL1 S3_0_C12_C9_3

#define ICC_ASGI1R_EL1 S3_0_C12_C11_6

#define ICC_BPR0_EL1 S3_0_C12_C8_3
#define ICC_BPR1_EL1 S3_0_C12_C12_3

#define ICC_CTLR_EL1 S3_0_C12_C12_4
#define ICC_CTLR_EL3 S3_6_C12_C12_4

#define ICC_DIR_EL1 S3_0_C12_C11_1

#define ICC_EOIR0_EL1 S3_0_C12_C8_1
#define ICC_EOIR1_EL1 S3_0_C12_C12_1

#define ICC_HPPIR0_EL1 S3_0_C12_C8_2
#define ICC_HPPIR1_EL1 S3_0_C12_C12_2

#define ICC_IAR0_EL1 S3_0_C12_C8_0
#define ICC_IAR1_EL1 S3_0_C12_C12_0

#define ICC_IGRPEN0_EL1 S3_0_C12_C12_6
#define ICC_IGRPEN1_EL1 S3_0_C12_C12_7
#define ICC_IGRPEN1_EL3 S3_6_C12_C12_7

#define ICC_PMR_EL1 S3_0_C4_C6_0
#define ICC_RPR_EL1 S3_0_C12_C11_3

#define ICC_SGI0R_EL1 S3_0_C12_C11_7
#define ICC_SGI1R_EL1 S3_0_C12_C11_5

#define ICC_SRE_EL1 S3_0_C12_C12_5
#define ICC_SRE_EL2 S3_4_C12_C9_5
#define ICC_SRE_EL3 S3_6_C12_C12_5

/*
 * Mapping of MSR and MRS to virtual interface control registers
 *
 * ARM Generic Interrupt Controller Architecture Specification
 * GIC architecture version 3.0 and version 4.0
 * Table 8-6
 */
#define ICH_AP0R0_EL2 S3_4_C12_C8_0
#define ICH_AP0R1_EL2 S3_4_C12_C8_1
#define ICH_AP0R2_EL2 S3_4_C12_C8_2
#define ICH_AP0R3_EL2 S3_4_C12_C8_3

#define ICH_AP1R0_EL2 S3_4_C12_C9_0
#define ICH_AP1R1_EL2 S3_4_C12_C9_1
#define ICH_AP1R2_EL2 S3_4_C12_C9_2
#define ICH_AP1R3_EL2 S3_4_C12_C9_3

#define ICH_HCR_EL2 S3_4_C12_C11_0

#define ICH_VTR_EL2 S3_4_C12_C11_1

#define ICH_MISR_EL2 S3_4_C12_C11_2

#define ICH_EISR_EL2 S3_4_C12_C11_3

#define ICH_ELRSR_EL2 S3_4_C12_C11_5

#define ICH_VMCR_EL2 S3_4_C12_C11_7

#define ICH_LR0_EL2 S3_4_C12_C12_0
#define ICH_LR1_EL2 S3_4_C12_C12_1
#define ICH_LR2_EL2 S3_4_C12_C12_2
#define ICH_LR3_EL2 S3_4_C12_C12_3
#define ICH_LR4_EL2 S3_4_C12_C12_4
#define ICH_LR5_EL2 S3_4_C12_C12_5
#define ICH_LR6_EL2 S3_4_C12_C12_6
#define ICH_LR7_EL2 S3_4_C12_C12_7
#define ICH_LR8_EL2 S3_4_C12_C13_0
#define ICH_LR9_EL2 S3_4_C12_C13_1
#define ICH_LR10_EL2 S3_4_C12_C13_2
#define ICH_LR11_EL2 S3_4_C12_C13_3
#define ICH_LR12_EL2 S3_4_C12_C13_4
#define ICH_LR13_EL2 S3_4_C12_C13_5
#define ICH_LR14_EL2 S3_4_C12_C13_6
#define ICH_LR15_EL2 S3_4_C12_C13_7

#define FUNC_DEFINE(name) .global name ;\
                           .type name, @function ;\
                            name:


/**
 * @name: 
 * @msg: void FGicSetICC_SRE_EL3(GICC_SRE_BITS bits) --- Interrupt Controller System Register Enable
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_SRE_EL3)
    MSR   ICC_SRE_EL3, x0
    ISB
    RET

/**
 * @name: 
 * @msg:  void FGicSetICC_SRE_EL2(GICC_SRE_BITS bits)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_SRE_EL2)
    MSR   ICC_SRE_EL2, x0
    ISB
    RET

/**
 * @name: 
 * @msg:  void FGicSetICC_SRE_EL1(GICC_SRE_BITS bits)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_SRE_EL1)
    MSR   ICC_SRE_EL1, x0
    ISB
    RET



/**
 * @name: 
 * @msg: u32 FGicGetICC_SRE_EL3(void) --  Interrupt Controller System Register Enable
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_SRE_EL3)
    MRS   x0, ICC_SRE_EL3
    RET

/**
 * @name: 
 * @msg: u32 FGicGetICC_SRE_EL2(void)
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_SRE_EL2)
    MRS   x0, ICC_SRE_EL2
    RET

/**
 * @name: 
 * @msg: u32 FGicGetICC_SRE_EL1(void)
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_SRE_EL1)
    MRS   x0, ICC_SRE_EL1
    RET


/**
 * @name: 
 * @msg: void FGicEnableGroup0(void)
 * @return {*}
 */
FUNC_DEFINE(FGicEnableGroup0)
    MOV   w0, #1
    MSR   ICC_IGRPEN0_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg: void FGicDisableGroup0(void)
 * @return {*}
 */
FUNC_DEFINE(FGicDisableGroup0)
    MOV   w0, #0
    MSR   ICC_IGRPEN0_EL1, x0
    ISB
    RET


/**
 * @name: 
 * @msg: 
 * @return {*}
 */
FUNC_DEFINE(FGicEnableGroup1_EL3)
    MOV   w0, #1
    MSR   ICC_IGRPEN1_EL3, x0
    ISB
    RET

/**
 * @name: 
 * @msg: 
 * @return {*}
 */
FUNC_DEFINE(FGicEnableGroup1_EL1)
    MOV   w0, #1
    MSR   ICC_IGRPEN1_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg: void FGicDisableGroup1_EL1(void)
 * @return {*}
 */
FUNC_DEFINE(FGicDisableGroup1_EL1)
    MOV   w0, #0
    MSR   ICC_IGRPEN1_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg: void FGicDisableGroup1_EL3(void)
 * @return {*}
 */
FUNC_DEFINE(FGicDisableGroup1_EL3)
    MOV   w0, #0
    MSR   ICC_IGRPEN1_EL3, x0
    ISB
    RET

/**
 * @name: 
 * @msg: void FGicSetICC_CTLR_EL3(GICC_CTLR_BITS reg_bits)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_CTLR_EL3)
    MSR   ICC_CTLR_EL3, x0
    ISB
    RET

/**
 * @name: 
 * @msg: void FGicSetICC_CTLR_EL1(GICC_CTLR_BITS reg_bits)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_CTLR_EL1)
    MSR   ICC_CTLR_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg: u32 FGicGetICC_CTLR_EL3(void) -- Controls aspects of the behavior of the GIC CPU interface and provides information about the features implemented.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_CTLR_EL3)
    MRS   x0, ICC_CTLR_EL3
    RET

/**
 * @name: 
 * @msg: u32 FGicGetICC_CTLR_EL1(void) -- Controls aspects of the behavior of the GIC CPU interface and provides information about the features implemented.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_CTLR_EL1)
    MRS   x0, ICC_CTLR_EL1
    RET

/**
 * @name: 
 * @msg: u32 FGicWriteICC_APR0(void) -- The PE reads this register to obtain the INTID of the signaled Group 0 interrupt.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_APR0)
    MRS x0, ICC_IAR0_EL1
    RET

/**
 * @name: 
 * @msg: u32 FGicGetICC_APR1(void)  -- The PE reads this register to obtain the INTID of the signaled Group 1 interrupt.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_APR1)
    MRS x0, ICC_IAR1_EL1
    RET

/**
 * @name: 
 * @msg: void FGicSetICC_EOIR0(u32 intnum) -- /* A PE writes to this register to inform the CPU interface that it has completed the processing of the specified Group 0 interrupt
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_EOIR0)
    MSR   ICC_EOIR0_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg: void FGicSetICC_EOIR1(u32 intnum) -- /* A PE writes to this register to inform the CPU interface that it has completed the processing of the specified Group 1 interrupt
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_EOIR1)
    MSR   ICC_EOIR1_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg:  void FGicSetICC_DIR(u32 intnum) -- When interrupt priority drop is separated from interrupt deactivation, a write to this register deactivates the specified interrupt.
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_DIR)
    MSR    ICC_DIR_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg: void FGicSetICC_PMR(u32 priority_mask) -- Provides an interrupt priority filter.
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_PMR)
    MSR   ICC_PMR_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg: u32 FGicGetICC_PMR(void)
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_PMR)
    MRS   x0,ICC_PMR_EL1
    RET

/**
 * @name: 
 * @msg:  u32 FGicGetICC_BPR1(void) --- Defines the point at which the priority value fields split into two parts, the group priority field and the subpriority field. The group priority field determines Group 1 interrupt preemption.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_BPR1)
    MRS   x0,ICC_BPR1_EL1
    RET

/**
 * @name: 
 * @msg:  void FGicSetICC_BPR1(u32 binary_point)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_BPR1)
    MSR   ICC_BPR1_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg:  u32 FGicGetICC_BPR0(void) --- Defines the point at which the priority value fields split into two parts, the group priority field and the subpriority field. The group priority field determines Group 0 interrupt preemption.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_BPR0)
    MRS   x0,ICC_BPR0_EL1
    RET

/**
 * @name: 
 * @msg:  void FGicSetICC_BPR0(u32 binary_point)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_BPR0)
    MSR   ICC_BPR0_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg:  u32 FGicGetICC_HPPIR1(void) --- Indicates the highest priority pending Group 1 interrupt on the CPU interface.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_HPPIR1)
    MRS   x0,ICC_HPPIR1_EL1
    RET

/**
 * @name: 
 * @msg:  void FGicSetICC_HPPIR1(u32 binary_point)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_HPPIR1)
    MSR   ICC_HPPIR1_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg:  u32 FGicGetICC_HPPIR0(void) --- Indicates the highest priority pending Group 0 interrupt on the CPU interface.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_HPPIR0)
    MRS   x0,ICC_HPPIR0_EL1
    RET

/**
 * @name: 
 * @msg:  void FGicSetICC_HPPIR0(u32 binary_point)
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_HPPIR0)
    MSR   ICC_HPPIR0_EL1, x0
    ISB
    RET

/**
 * @name: 
 * @msg:  u32 FGicGetICC_RPR(void) --- Indicates the Running priority of the CPU interface.
 * @return {*}
 */
FUNC_DEFINE(FGicGetICC_RPR)
    MRS   x0,ICC_RPR_EL1
    RET

/* SGI interface */
/**
 * @name: 
 * @msg: void FGicSetICC_SGI0R(u32 intnum,u32 target_list,GICC_SGIR_IRM_BITS mode,u64 affinity_list)    --- Generates Secure Group 0 SGIs
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_SGI0R)
  ORR   x0, x0, x1
  ORR   x0, x0, x2
  ORR   x0, x0, x3
  MSR   ICC_SGI0R_EL1, x0
  ISB
  RET

/**
 * @name: 
 * @msg: void FGicSetICC_SGI1R(u32 intnum,u32 target_list,GICC_SGIR_IRM_BITS mode,u64 affinity_list) 
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_SGI1R)
  ORR   x0, x0, x1
  ORR   x0, x0, x2
  ORR   x0, x0, x3
  MSR   ICC_SGI1R_EL1, x0
  ISB
  RET
   
/**
 * @name: 
 * @msg: void FGicSetICC_ASGI1R(u32 intnum,u32 target_list,GICC_SGIR_IRM_BITS mode,u64 affinity_list) 
 * @return {*}
 */
FUNC_DEFINE(FGicSetICC_ASGI1R)
  ORR   x0, x0, x1
  ORR   x0, x0, x2
  ORR   x0, x0, x3
  MSR   ICC_ASGI1R_EL1, x0
  ISB
  RET
   

#else




#endif


