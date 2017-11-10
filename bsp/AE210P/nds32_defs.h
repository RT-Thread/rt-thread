/*
 *  Copyright (C) 2008 Andes Technology, Inc.
 */

#ifndef __NDS32_DEFS_H__
#define __NDS32_DEFS_H__
/******************************************************************************
 * cr0: CPU_VER (CPU Version Register)
 *****************************************************************************/

#define CPU_VER_offCFGID	0	/* Minor configuration */
#define CPU_VER_offREV		16	/* Revision of the CPU version */
#define CPU_VER_offCPUID	24	/* Major CPU versions */

#define CPU_VER_mskCFGID	( 0xFFFF << CPU_VER_offCFGID )
#define CPU_VER_mskREV		( 0xFF << CPU_VER_offREV )
#define CPU_VER_mskCPUID	( 0xFF << CPU_VER_offCPUID )

/******************************************************************************
 * cr1: ICM_CFG (Instruction Cache/Memory Configuration Register)
 *****************************************************************************/
#define ICM_CFG_offISET		0	/* I-cache sets (# of cache lines) per way */
#define ICM_CFG_offIWAY		3	/* I-cache ways */
#define ICM_CFG_offISZ		6	/* I-cache line size */
#define ICM_CFG_offILCK		9	/* I-cache locking support */
#define ICM_CFG_offILMB		10	/* On-chip ILM banks */
#define ICM_CFG_offBSAV		13	/* ILM base register alignment version */
#define ICM_CFG_offEXT		15	/* External ILM or not */
#define ICM_CFG_offULM_2BANK	16	/* In ULM configuration, ILM has two banks */
/* bit 17:31 reserved */

#define ICM_CFG_mskISET		( 0x7 << ICM_CFG_offISET )
#define ICM_CFG_mskIWAY		( 0x7 << ICM_CFG_offIWAY )
#define ICM_CFG_mskISZ		( 0x7 << ICM_CFG_offISZ )
#define ICM_CFG_mskILCK		( 0x1 << ICM_CFG_offILCK )
#define ICM_CFG_mskILMB		( 0x7 << ICM_CFG_offILMB )
#define ICM_CFG_mskBSAV		( 0x3 << ICM_CFG_offBSAV )
#define ICM_CFG_mskEXT		( 0x1 << ICM_CFG_offEXT )
#define ICM_CFG_mskULM_2BANK	( 0x1 << ICM_CFG_offULM_2BANK )

/******************************************************************************
 * cr2: DCM_CFG (Data Cache/Memory Configuration Register)
 *****************************************************************************/
#define DCM_CFG_offDSET		0	/* D-cache sets (# of cache lines) per way */
#define DCM_CFG_offDWAY		3	/* D-cache ways */
#define DCM_CFG_offDSZ		6	/* D-cache line size */
#define DCM_CFG_offDLCK		9	/* D-cache locking support */
#define DCM_CFG_offDLMB		10	/* On-chip DLM banks */
#define DCM_CFG_offBSAV		13	/* DLM base register alignment version */
#define DCM_CFG_offEXT		15	/* External DLM or not */
#define DCM_CFG_offULM_2BANK	16	/* In ULM configuration, DLM has two banks */
/* bit 17:31 reserved */

#define DCM_CFG_mskDSET		( 0x7 << DCM_CFG_offDSET )
#define DCM_CFG_mskDWAY		( 0x7 << DCM_CFG_offDWAY )
#define DCM_CFG_mskDSZ		( 0x7 << DCM_CFG_offDSZ )
#define DCM_CFG_mskDLCK		( 0x1 << DCM_CFG_offDLCK )
#define DCM_CFG_mskDLMB		( 0x7 << DCM_CFG_offDLMB )
#define DCM_CFG_mskBSAV		( 0x3 << DCM_CFG_offBSAV )
#define DCM_CFG_mskEXT          ( 0x1 << DCM_CFG_offEXT )
#define DCM_CFG_mskULM_2BANK    ( 0x1 << DCM_CFG_offULM_2BANK )

/******************************************************************************
 * cr3: MMU_CFG (MMU Configuration Register)
 *****************************************************************************/
#define MMU_CFG_offMMPS		0	/* Memory management protection scheme */
#define MMU_CFG_offMMPV		2	/* Memory management protection version number */
#define MMU_CFG_offFATB		7	/* Fully-associative or non-fully-associative TLB */

#ifdef CONFIG_FULL_ASSOC
#define MMU_CFG_offFATBSZ	8	/* TLB entries while using full-associative TLB */
#else
#define MMU_CFG_offTBW		8	/* TLB ways(non-associative) TBS */
#define MMU_CFG_offTBS		11	/* TLB sets per way(non-associative) TBS */
/* bit 14:14 reserved */
#endif

#define MMU_CFG_offEP8MIN4	15	/* 8KB page supported while minimum page is 4KB */
#define MMU_CFG_offfEPSZ	16	/* Extra page size supported */
#define MMU_CFG_offTLBLCK	24	/* TLB locking support */
#define MMU_CFG_offHPTWK	25	/* Hardware Page Table Walker implemented */
#define MMU_CFG_offDE		26	/* Default endian */
#define MMU_CFG_offNTPT		27	/* Partitions for non-translated attributes */
#define MMU_CFG_offIVTB		28	/* Invisible TLB */
#define MMU_CFG_offVLPT		29	/* VLPT for fast TLB fill handling implemented */
#define MMU_CFG_offNTME		30	/* Non-translated VA to PA mapping */
#define MMU_CFG_offDRDE		31	/* Device register default endian */

#define MMU_CFG_mskMMPS		( 0x3 << MMU_CFG_offMMPS )
#define MMU_CFG_mskMMPV		( 0x1F << MMU_CFG_offMMPV )
#define MMU_CFG_mskFATB		( 0x1 << MMU_CFG_offFATB )
#ifdef CONFIG_FULL_ASSOC
#define MMU_CFG_mskFATBSZ	( 0x7f << MMU_CFG_offFATBSZ )
#else
#define MMU_CFG_mskTBW		( 0x7 << MMU_CFG_offTBW )
#define MMU_CFG_mskTBS		( 0x7 << MMU_CFG_offTBS )
#endif
#define MMU_CFG_mskEP8MIN4	( 0x1 << MMU_CFG_offEP8MIN4 )
#define MMU_CFG_mskfEPSZ	( 0xFF << MMU_CFG_offfEPSZ )
#define MMU_CFG_mskTLBLCK	( 0x1 << MMU_CFG_offTLBLCK )
#define MMU_CFG_mskHPTWK	( 0x1 << MMU_CFG_offHPTWK )
#define MMU_CFG_mskDE		( 0x1 << MMU_CFG_offDE )
#define MMU_CFG_mskNTPT		( 0x1 << MMU_CFG_offNTPT )
#define MMU_CFG_mskIVTB		( 0x1 << MMU_CFG_offIVTB )
#define MMU_CFG_mskVLPT		( 0x1 << MMU_CFG_offVLPT )
#define MMU_CFG_mskNTME		( 0x1 << MMU_CFG_offNTME )
#define MMU_CFG_mskDRDE		( 0x1 << MMU_CFG_offDRDE )

/******************************************************************************
 * cr4: MSC_CFG (Misc Configuration Register)
 *****************************************************************************/
#define MSC_CFG_offEDM		0	/* EDM */
#define MSC_CFG_offLMDMA	1	/* Local memory DMA engine */
#define MSC_CFG_offPFM		2	/* Performance monitoring feature */
#define MSC_CFG_offHSMP		3	/* HSMP_SADDR (V1 and V2 of HSMP) register */
#define MSC_CFG_offTRACE	4	/* Debug Tracer Unit */
#define MSC_CFG_offDIV		5	/* Divide instructions support */
#define MSC_CFG_offMAC		6	/* Multiply instructions support */
#define MSC_CFG_offAUDIO	7	/* AUDIO ISA extension support */
#define MSC_CFG_offL2C		9	/* L2 unified cache */
#define MSC_CFG_offRDREG	10	/* Reduced Register configuration */
#define MSC_CFG_offADR24	11	/* Reduced Address Space to 24-bit configuration */
#define MSC_CFG_offINTLC	12	/* interruption level configuration */
#define MSC_CFG_offBASEV	13	/* Baseline instructions version */
#define MSC_CFG_offNOD		16	/* Dx registers */
#define MSC_CFG_offIMV		17	/* Implementation-dependent register detection scheme version */
#define MSC_CFG_offIMR		18	/* First implementation-dependent register of SR encoding {2, 15, 0} */
#define MSC_CFG_offIFC		19	/* IFC support */
#define MSC_CFG_offMCU		20	/* MCU family */
#define MSC_CFG_offSHADOW	21	/* shadow registers support */
#define MSC_CFG_offEIT		24	/* EX9 support */
#define MSC_CFG_offULM		25	/* ULM configuration */
#define MSC_CFG_offPFT		26	/* Performance Throttling feature support */
#define MSC_CFG_offHSP		27	/* HW Stack protection/recording feature support */
/* bit 28:29 reserved */
#define MSC_CFG_offMSC_EXT	30	/* Miscellaneous Configuration Extension */

#define MSC_CFG_mskEDM		( 0x1 << MSC_CFG_offEDM )
#define MSC_CFG_mskLMDMA	( 0x1 << MSC_CFG_offLMDMA )
#define MSC_CFG_mskPFM		( 0x1 << MSC_CFG_offPFM )
#define MSC_CFG_mskHSMP		( 0x1 << MSC_CFG_offHSMP )
#define MSC_CFG_mskTRACE	( 0x1 << MSC_CFG_offTRACE )
#define MSC_CFG_mskDIV		( 0x1 << MSC_CFG_offDIV )
#define MSC_CFG_mskMAC		( 0x1 << MSC_CFG_offMAC )
#define MSC_CFG_mskAUDIO	( 0x3 << MSC_CFG_offAUDIO )
#define MSC_CFG_mskL2C		( 0x1 << MSC_CFG_offL2C )
#define MSC_CFG_mskRDREG	( 0x1 << MSC_CFG_offRDREG )
#define MSC_CFG_mskADR24	( 0x1 << MSC_CFG_offADR24 )
#define MSC_CFG_mskINTLC	( 0x1 << MSC_CFG_offINTLC )
#define MSC_CFG_mskBASEV	( 0x7 << MSC_CFG_offBASEV )
#define MSC_CFG_mskNOD		( 0x1 << MSC_CFG_offNOD )
#define MSC_CFG_mskIMV		( 0x1 << MSC_CFG_offIMV )
#define MSC_CFG_mskIMR		( 0x1 << MSC_CFG_offIMR )
#define MSC_CFG_mskIFC		( 0x1 << MSC_CFG_offIFC )
#define MSC_CFG_mskMCU		( 0x1 << MSC_CFG_offMCU )
#define MSC_CFG_mskSHADOW	( 0x7 << MSC_CFG_offSHADOW )
#define MSC_CFG_mskEIT		( 0x1 << MSC_CFG_offEIT )
#define MSC_CFG_mskULM		( 0x1 << MSC_CFG_offULM )
#define MSC_CFG_mskPFT		( 0x1 << MSC_CFG_offPFT )
#define MSC_CFG_mskHSP		( 0x1 << MSC_CFG_offHSP )
#define MSC_CFG_mskMSC_EXT	( 0x3 << MSC_CFG_offMSC_EXT )

/******************************************************************************
 * cr5: CORE_CFG (Core Identification Register)
 *****************************************************************************/
#define CORE_ID_offCOREID	0
/* bit 4:31 reserved */

#define CORE_ID_mskCOREID	( 0xF << CORE_ID_offCOREID )

/******************************************************************************
 * cr6: FUCOP_EXIST (FPU and Coprocessor Existence Configuration Register)
 *****************************************************************************/
#define FUCOP_EXIST_offCP0EX	0	/* Coprocessor #0 existence */
#define FUCOP_EXIST_offCP1EX	1	/* Coprocessor #1 existence */
#define FUCOP_EXIST_offCP2EX	2	/* Coprocessor #2 existence */
#define FUCOP_EXIST_offCP3EX	3	/* Coprocessor #3 existence */
/* bit 4:15 reserved */
#define FUCOP_EXIST_offCPV	16	/* Coprocessor ISA extension version */
/* bit 18:30 reserved */
#define FUCOP_EXIST_offCP0ISFPU	31	/* Coprocessor #0 is FPU when CP0EX is 1 */

#define FUCOP_EXIST_mskCP0EX	( 0x1 << FUCOP_EXIST_offCP0EX )
#define FUCOP_EXIST_mskCP1EX	( 0x1 << FUCOP_EXIST_offCP1EX )
#define FUCOP_EXIST_mskCP2EX	( 0x1 << FUCOP_EXIST_offCP2EX )
#define FUCOP_EXIST_mskCP3EX	( 0x1 << FUCOP_EXIST_offCP3EX )
#define FUCOP_EXIST_mskCPV	( 0x3 << FUCOP_EXIST_offCPV )
#define FUCOP_EXIST_mskCP0ISFPU	( 0x1 << FUCOP_EXIST_offCP0ISFPU )

/******************************************************************************
 * ir0: PSW (Processor Status Word Register)
 * ir1: IPSW (Interruption PSW Register)
 * ir2: P_IPSW (Previous IPSW Register)
 *****************************************************************************/
#define PSW_offGIE		0	/* Global Interrupt Enable */
#define PSW_offINTL		1	/* Interruption Stack Level */
#define PSW_offPOM		3	/* Processor Operation Mode, User/Superuser */
#define PSW_offBE		5	/* Endianness for data memory access, 1:MSB, 0:LSB */
#define PSW_offIT		6	/* Enable instruction address translation */
#define PSW_offDT		7	/* Enable data address translation */
#define PSW_offIME		8	/* Instruction Machine Error flag */
#define PSW_offDME		9	/* Data Machine Error flag */
#define PSW_offDEX		10	/* Debug Exception */
#define PSW_offHSS		11	/* Hardware Single Stepping */
#define PSW_offDRBE		12	/* Device Register Endian mode for device register */
#define PSW_offAEN		13	/* Audio ISA special features enable control */
#define PSW_offWBNA		14	/* write-back, write-allocation to write-back, no-write-allocation */
#define PSW_offIFCON		15	/* Hardware Single Stepping */
#define PSW_offCPL		16	/* Current Priority Level */
/* bit 19 reserved */
#define PSW_offOV		20	/* Overflow flag for saturation arithmetic instructions */
#define PSW_offPFT_EN		21	/* Enable performance throttling */
/* bit 22:31 reserved */

#define PSW_mskGIE		( 0x1 << PSW_offGIE )
#define PSW_mskINTL		( 0x3 << PSW_offINTL )
#define PSW_mskPOM		( 0x3 << PSW_offPOM )
#define PSW_mskBE		( 0x1 << PSW_offBE )
#define PSW_mskIT		( 0x1 << PSW_offIT )
#define PSW_mskDT		( 0x1 << PSW_offDT )
#define PSW_mskIME		( 0x1 << PSW_offIME )
#define PSW_mskDME		( 0x1 << PSW_offDME )
#define PSW_mskDEX		( 0x1 << PSW_offDEX )
#define PSW_mskHSS		( 0x1 << PSW_offHSS )
#define PSW_mskDRBE		( 0x1 << PSW_offDRBE )
#define PSW_mskAEN		( 0x1 << PSW_offAEN )
#define PSW_mskWBNA		( 0x1 << PSW_offWBNA )
#define PSW_mskIFCON		( 0x1 << PSW_offIFCON )
#define PSW_mskCPL		( 0x7 << PSW_offCPL )
#define PSW_mskOV		( 0x1 << PSW_offOV )
#define PSW_mskPFT_EN		( 0x1 << PSW_offPFT_EN )

/******************************************************************************
 * ir3: IVB (Interruption Vector Base Register)
 *****************************************************************************/
#define IVB_offPROG_PRI_LVL	0	/* Programmable Priority Level */////
#define IVB_offNIVIC		1	/* Number of input for Internal Vector Interrupt Controller*/
/* bit 4:10 reserved */
#define IVB_offIVIC_VER		11	/* Internal Vectored Interrupt Controller (IVIC) Version */
#define IVB_offEVIC		13	/* External Vector Interrupt Controller mode */
#define IVB_offESZ		14	/* Size of each vector entry */
#define IVB_offIVBASE		16	/* BasePA of interrupt vector table */

#define IVB_mskPROG_PRI_LVL	( 0x1 << IVB_offPROG_PRI_LVL)
#define IVB_mskNIVIC		( 0x7 << IVB_offNIVIC)
#define IVB_mskIVIC_VER		( 0x3 << IVB_offIVIC_VER )
#define IVB_mskEVIC		( 0x1 << IVB_offEVIC )
#define IVB_mskESZ		( 0x3 << IVB_offESZ )
#define IVB_mskIVBASE		( 0xFFFF << IVB_offIVBASE )

/******************************************************************************
 * ir4: EVA (Exception Virtual Address Register)
 * ir5: P_EVA (Previous EVA Register)
 *****************************************************************************/

	/* This register contains the VA that causes the exception */

/******************************************************************************
 * ir6: ITYPE (Interruption Type Register)
 * ir7: P_ITYPE (Previous ITYPE Register)
 *****************************************************************************/
#define ITYPE_offETYPE		0	/* Exception Type */
#define ITYPE_offINST		4	/* Exception caused by insn fetch or data access */
/* bit 5:15 reserved */
#define ITYPE_offSWID		16	/* SWID of debugging exception */
/* bit 31:31 reserved */

#define ITYPE_mskETYPE		( 0xF << ITYPE_offETYPE )
#define ITYPE_mskINST		( 0x1 << ITYPE_offINST )
#define ITYPE_mskSWID		( 0x7FFF << ITYPE_offSWID )

/******************************************************************************
 * ir8: MERR (Machine Error Log Register)
 *****************************************************************************/
/* bit 0:30 reserved */
#define MERR_offBUSERR		31	/* Bus error caused by a load insn */

#define MERR_mskBUSERR		( 0x1 << MERR_offBUSERR )

/******************************************************************************
 * ir9: IPC (Interruption Program Counter Register)
 * ir10: P_IPC (Previous IPC Register)
 * ir11: OIPC (Overflow Interruption Program Counter Register)
 *****************************************************************************/

	/* This is the shadow stack register of the Program Counter */

/******************************************************************************
 * ir12: P_P0 (Previous P0 Register)
 * ir13: P_P1 (Previous P1 Register)
 *****************************************************************************/

	/* These are shadow registers of $p0 and $p1 */

/******************************************************************************
 * ir14: INT_MASK (Interruption Masking Register)
 *****************************************************************************/
#define INT_MASK_offH0IM	0	/* Hardware Interrupt 0 Mask bit */
#define INT_MASK_offH1IM	1	/* Hardware Interrupt 1 Mask bit */
#define INT_MASK_offH2IM	2	/* Hardware Interrupt 2 Mask bit */
#define INT_MASK_offH3IM	3	/* Hardware Interrupt 3 Mask bit */
#define INT_MASK_offH4IM	4	/* Hardware Interrupt 4 Mask bit */
#define INT_MASK_offH5IM	5	/* Hardware Interrupt 5 Mask bit */
#define INT_MASK_offH6IM	6	/* Hardware Interrupt 6 Mask bit */
#define INT_MASK_offH7IM	7	/* Hardware Interrupt 7 Mask bit */
#define INT_MASK_offH8IM	8	/* Hardware Interrupt 8 Mask bit */
#define INT_MASK_offH9IM	9	/* Hardware Interrupt 9 Mask bit */
#define INT_MASK_offH10IM	10	/* Hardware Interrupt 10 Mask bit */
#define INT_MASK_offH11IM	11	/* Hardware Interrupt 11 Mask bit */
#define INT_MASK_offH12IM	12	/* Hardware Interrupt 12 Mask bit */
#define INT_MASK_offH13IM	13	/* Hardware Interrupt 13 Mask bit */
#define INT_MASK_offH14IM	14	/* Hardware Interrupt 14 Mask bit */
#define INT_MASK_offH15IM	15	/* Hardware Interrupt 15 Mask bit */
#define INT_MASK_offSIM		16	/* Software Interrupt Mask bit */
/* bit 17:28 reserved */
#define INT_MASK_offALZ		29	/* All zero opcode reserved instruction exception mask */
#define INT_MASK_offIDIVZE	30	/* Enable detection for Divide-By-Zero */
#define INT_MASK_offDSSIM	31	/* Default Single Stepping Interruption Mask */

#define INT_MASK_mskH0IM	( 0x1 << INT_MASK_offH0IM )
#define INT_MASK_mskH1IM	( 0x1 << INT_MASK_offH1IM )
#define INT_MASK_mskH2IM	( 0x1 << INT_MASK_offH2IM )
#define INT_MASK_mskH3IM	( 0x1 << INT_MASK_offH3IM )
#define INT_MASK_mskH4IM	( 0x1 << INT_MASK_offH4IM )
#define INT_MASK_mskH5IM	( 0x1 << INT_MASK_offH5IM )
#define INT_MASK_mskH6IM	( 0x1 << INT_MASK_offH6IM )
#define INT_MASK_mskH7IM	( 0x1 << INT_MASK_offH7IM )
#define INT_MASK_mskH8IM	( 0x1 << INT_MASK_offH8IM )
#define INT_MASK_mskH9IM	( 0x1 << INT_MASK_offH9IM )
#define INT_MASK_mskH10IM	( 0x1 << INT_MASK_offH10IM )
#define INT_MASK_mskH11IM	( 0x1 << INT_MASK_offH11IM )
#define INT_MASK_mskH12IM	( 0x1 << INT_MASK_offH12IM )
#define INT_MASK_mskH13IM	( 0x1 << INT_MASK_offH13IM )
#define INT_MASK_mskH14IM	( 0x1 << INT_MASK_offH14IM )
#define INT_MASK_mskH15IM	( 0x1 << INT_MASK_offH15IM )
#define INT_MASK_mskSIM		( 0x1 << INT_MASK_offSIM )
#define INT_MASK_mskALZ		( 0x1 << INT_MASK_offALZ )
#define INT_MASK_mskIDIVZE	( 0x1 << INT_MASK_offIDIVZE )
#define INT_MASK_mskDSSIM	( 0x1 << INT_MASK_offDSSIM )

/******************************************************************************
 * ir15: INT_PEND (Interruption Pending Register)
 *****************************************************************************/
#define INT_PEND_offH0I		0	/* Hardware Interrupt 0 pending bit */
#define INT_PEND_offH1I		1	/* Hardware Interrupt 1 pending bit */
#define INT_PEND_offH2I		2	/* Hardware Interrupt 2 pending bit */
#define INT_PEND_offH3I		3	/* Hardware Interrupt 3 pending bit */
#define INT_PEND_offH4I		4	/* Hardware Interrupt 4 pending bit */
#define INT_PEND_offH5I		5	/* Hardware Interrupt 5 pending bit */
#define INT_PEND_offH6I		6	/* Hardware Interrupt 6 pending bit */
#define INT_PEND_offH7I		7	/* Hardware Interrupt 7 pending bit */
#define INT_PEND_offH8I		8	/* Hardware Interrupt 8 pending bit */
#define INT_PEND_offH9I		9	/* Hardware Interrupt 9 pending bit */
#define INT_PEND_offH10I	10	/* Hardware Interrupt 10 pending bit */
#define INT_PEND_offH11I	11	/* Hardware Interrupt 11 pending bit */
#define INT_PEND_offH12I	12	/* Hardware Interrupt 12 pending bit */
#define INT_PEND_offH13I	13	/* Hardware Interrupt 13 pending bit */
#define INT_PEND_offH14I	14	/* Hardware Interrupt 14 pending bit */
#define INT_PEND_offH15I	15	/* Hardware Interrupt 15 pending bit */

#define INT_PEND_offCIPL	0	/* Current Interrupt Priority Level */

#define INT_PEND_offSWI		16	/* Software Interrupt pending bit */
/* bit 17:31 reserved */

#define INT_PEND_mskH0I		( 0x1 << INT_PEND_offH0I )
#define INT_PEND_mskH1I		( 0x1 << INT_PEND_offH1I )
#define INT_PEND_mskH2I		( 0x1 << INT_PEND_offH2I )
#define INT_PEND_mskH3I		( 0x1 << INT_PEND_offH3I )
#define INT_PEND_mskH4I		( 0x1 << INT_PEND_offH4I )
#define INT_PEND_mskH5I		( 0x1 << INT_PEND_offH5I )
#define INT_PEND_mskH6I		( 0x1 << INT_PEND_offH6I )
#define INT_PEND_mskH7I		( 0x1 << INT_PEND_offH7I )
#define INT_PEND_mskH8I		( 0x1 << INT_PEND_offH8I )
#define INT_PEND_mskH9I		( 0x1 << INT_PEND_offH9I )
#define INT_PEND_mskH10I	( 0x1 << INT_PEND_offH10I )
#define INT_PEND_mskH11I	( 0x1 << INT_PEND_offH11I )
#define INT_PEND_mskH12I	( 0x1 << INT_PEND_offH12I )
#define INT_PEND_mskH13I	( 0x1 << INT_PEND_offH13I )
#define INT_PEND_mskH14I	( 0x1 << INT_PEND_offH14I )
#define INT_PEND_mskH15I	( 0x1 << INT_PEND_offH15I )
#define INT_PEND_mskCIPL	( 0x1 << INT_PEND_offCIPL )
#define INT_PEND_mskSWI		( 0x1 << INT_PEND_offSWI )

/******************************************************************************
 * ir16: SP_USR (Shadowed User Stack Pointer Register)
 * ir17: SP_PRIV (Shadowed Privileged Stack Pointer Register)
 *****************************************************************************/

	/* These are shadow registers of $sp */

/******************************************************************************
 * ir18: INT_PRI (Interrupt Priority Register)
 *****************************************************************************/
#define INT_PRI_offH0PRI	0	/* Hardware Interrupt 0 Priority Level */
#define INT_PRI_offH1PRI	2	/* Hardware Interrupt 1 Priority Level */
#define INT_PRI_offH2PRI	4	/* Hardware Interrupt 2 Priority Level */
#define INT_PRI_offH3PRI	6	/* Hardware Interrupt 3 Priority Level */
#define INT_PRI_offH4PRI	8	/* Hardware Interrupt 4 Priority Level */
#define INT_PRI_offH5PRI	10	/* Hardware Interrupt 5 Priority Level */
#define INT_PRI_offH6PRI	12	/* Hardware Interrupt 6 Priority Level */
#define INT_PRI_offH7PRI	14	/* Hardware Interrupt 7 Priority Level */
#define INT_PRI_offH8PRI	16	/* Hardware Interrupt 8 Priority Level */
#define INT_PRI_offH9PRI	18	/* Hardware Interrupt 9 Priority Level */
#define INT_PRI_offH10PRI	20	/* Hardware Interrupt 10 Priority Level */
#define INT_PRI_offH11PRI	22	/* Hardware Interrupt 11 Priority Level */
#define INT_PRI_offH12PRI	24	/* Hardware Interrupt 12 Priority Level */
#define INT_PRI_offH13PRI	26	/* Hardware Interrupt 13 Priority Level */
#define INT_PRI_offH14PRI	28	/* Hardware Interrupt 14 Priority Level */
#define INT_PRI_offH15PRI	30	/* Hardware Interrupt 15 Priority Level */

#define INT_PRI_mskH0PRI	( 0x3 << INT_PRI_offH0PRI )
#define INT_PRI_mskH1PRI	( 0x3 << INT_PRI_offH1PRI )
#define INT_PRI_mskH2PRI	( 0x3 << INT_PRI_offH2PRI )
#define INT_PRI_mskH3PRI	( 0x3 << INT_PRI_offH3PRI )
#define INT_PRI_mskH4PRI	( 0x3 << INT_PRI_offH4PRI )
#define INT_PRI_mskH5PRI	( 0x3 << INT_PRI_offH5PRI )
#define INT_PRI_mskH6PRI	( 0x3 << INT_PRI_offH6PRI )
#define INT_PRI_mskH7PRI	( 0x3 << INT_PRI_offH7PRI )
#define INT_PRI_mskH8PRI	( 0x3 << INT_PRI_offH8PRI )
#define INT_PRI_mskH9PRI	( 0x3 << INT_PRI_offH9PRI )
#define INT_PRI_mskH10PRI	( 0x3 << INT_PRI_offH10PRI )
#define INT_PRI_mskH11PRI	( 0x3 << INT_PRI_offH11PRI )
#define INT_PRI_mskH12PRI	( 0x3 << INT_PRI_offH12PRI )
#define INT_PRI_mskH13PRI	( 0x3 << INT_PRI_offH13PRI )
#define INT_PRI_mskH14PRI	( 0x3 << INT_PRI_offH14PRI )
#define INT_PRI_mskH15PRI	( 0x3 << INT_PRI_offH15PRI )

/******************************************************************************
 * ir19: INT_CTRL (Interrupt Control Register)
 *****************************************************************************/
#define INT_CTRL_offPPL2FIX_EN	0
/* bit 1:31 reserved */

#define INT_CTRL_mskPPL2FIX_EN	( 0x1 << INT_CTRL_offPPL2FIX_EN )

/******************************************************************************
 * ir26: INT_MASK2 (Interruption Masking Register 2)
 *****************************************************************************/
#define INT_MASK2_offH0IM	0	/* Hardware Interrupt 0 Mask bit */
#define INT_MASK2_offH1IM	1	/* Hardware Interrupt 1 Mask bit */
#define INT_MASK2_offH2IM	2	/* Hardware Interrupt 2 Mask bit */
#define INT_MASK2_offH3IM	3	/* Hardware Interrupt 3 Mask bit */
#define INT_MASK2_offH4IM	4	/* Hardware Interrupt 4 Mask bit */
#define INT_MASK2_offH5IM	5	/* Hardware Interrupt 5 Mask bit */
#define INT_MASK2_offH6IM	6	/* Hardware Interrupt 6 Mask bit */
#define INT_MASK2_offH7IM	7	/* Hardware Interrupt 7 Mask bit */
#define INT_MASK2_offH8IM	8	/* Hardware Interrupt 8 Mask bit */
#define INT_MASK2_offH9IM	9	/* Hardware Interrupt 9 Mask bit */
#define INT_MASK2_offH10IM	10	/* Hardware Interrupt 10 Mask bit */
#define INT_MASK2_offH11IM	11	/* Hardware Interrupt 11 Mask bit */
#define INT_MASK2_offH12IM	12	/* Hardware Interrupt 12 Mask bit */
#define INT_MASK2_offH13IM	13	/* Hardware Interrupt 13 Mask bit */
#define INT_MASK2_offH14IM	14	/* Hardware Interrupt 14 Mask bit */
#define INT_MASK2_offH15IM	15	/* Hardware Interrupt 15 Mask bit */
#define INT_MASK2_offH16IM	16	/* Hardware Interrupt 16 Mask bit */
#define INT_MASK2_offH17IM	17	/* Hardware Interrupt 17 Mask bit */
#define INT_MASK2_offH18IM	18	/* Hardware Interrupt 18 Mask bit */
#define INT_MASK2_offH19IM	19	/* Hardware Interrupt 19 Mask bit */
#define INT_MASK2_offH20IM	20	/* Hardware Interrupt 20 Mask bit */
#define INT_MASK2_offH21IM	21	/* Hardware Interrupt 21 Mask bit */
#define INT_MASK2_offH22IM	22	/* Hardware Interrupt 22 Mask bit */
#define INT_MASK2_offH23IM	23	/* Hardware Interrupt 23 Mask bit */
#define INT_MASK2_offH24IM	24	/* Hardware Interrupt 24 Mask bit */
#define INT_MASK2_offH25IM	25	/* Hardware Interrupt 25 Mask bit */
#define INT_MASK2_offH26IM	26	/* Hardware Interrupt 26 Mask bit */
#define INT_MASK2_offH27IM	27	/* Hardware Interrupt 27 Mask bit */
#define INT_MASK2_offH28IM	28	/* Hardware Interrupt 28 Mask bit */
#define INT_MASK2_offH29IM	29	/* Hardware Interrupt 29 Mask bit */
#define INT_MASK2_offH30IM	30	/* Hardware Interrupt 30 Mask bit */
#define INT_MASK2_offH31IM	31	/* Hardware Interrupt 31 Mask bit */

#define INT_MASK2_mskH0IM	( 0x1 << INT_MASK2_offH0IM )
#define INT_MASK2_mskH1IM	( 0x1 << INT_MASK2_offH1IM )
#define INT_MASK2_mskH2IM	( 0x1 << INT_MASK2_offH2IM )
#define INT_MASK2_mskH3IM	( 0x1 << INT_MASK2_offH3IM )
#define INT_MASK2_mskH4IM	( 0x1 << INT_MASK2_offH4IM )
#define INT_MASK2_mskH5IM	( 0x1 << INT_MASK2_offH5IM )
#define INT_MASK2_mskH6IM	( 0x1 << INT_MASK2_offH6IM )
#define INT_MASK2_mskH7IM	( 0x1 << INT_MASK2_offH7IM )
#define INT_MASK2_mskH8IM	( 0x1 << INT_MASK2_offH8IM )
#define INT_MASK2_mskH9IM	( 0x1 << INT_MASK2_offH9IM )
#define INT_MASK2_mskH10IM	( 0x1 << INT_MASK2_offH10IM )
#define INT_MASK2_mskH11IM	( 0x1 << INT_MASK2_offH11IM )
#define INT_MASK2_mskH12IM	( 0x1 << INT_MASK2_offH12IM )
#define INT_MASK2_mskH13IM	( 0x1 << INT_MASK2_offH13IM )
#define INT_MASK2_mskH14IM	( 0x1 << INT_MASK2_offH14IM )
#define INT_MASK2_mskH15IM	( 0x1 << INT_MASK2_offH15IM )
#define INT_MASK2_mskH16IM	( 0x1 << INT_MASK2_offH16IM )
#define INT_MASK2_mskH17IM	( 0x1 << INT_MASK2_offH17IM )
#define INT_MASK2_mskH18IM	( 0x1 << INT_MASK2_offH18IM )
#define INT_MASK2_mskH19IM	( 0x1 << INT_MASK2_offH19IM )
#define INT_MASK2_mskH20IM	( 0x1 << INT_MASK2_offH20IM )
#define INT_MASK2_mskH21IM	( 0x1 << INT_MASK2_offH21IM )
#define INT_MASK2_mskH22IM	( 0x1 << INT_MASK2_offH22IM )
#define INT_MASK2_mskH23IM	( 0x1 << INT_MASK2_offH23IM )
#define INT_MASK2_mskH24IM	( 0x1 << INT_MASK2_offH24IM )
#define INT_MASK2_mskH25IM	( 0x1 << INT_MASK2_offH25IM )
#define INT_MASK2_mskH26IM	( 0x1 << INT_MASK2_offH26IM )
#define INT_MASK2_mskH27IM	( 0x1 << INT_MASK2_offH27IM )
#define INT_MASK2_mskH28IM	( 0x1 << INT_MASK2_offH28IM )
#define INT_MASK2_mskH29IM	( 0x1 << INT_MASK2_offH29IM )
#define INT_MASK2_mskH30IM	( 0x1 << INT_MASK2_offH30IM )
#define INT_MASK2_mskH31IM	( 0x1 << INT_MASK2_offH31IM )

/******************************************************************************
 * ir27: INT_PEND2 (Interruption Pending Register 2)
 *****************************************************************************/
#define INT_PEND2_offH0I	0	/* Hardware Interrupt 0 Pending bit */
#define INT_PEND2_offH1I	1	/* Hardware Interrupt 1 Pending bit */
#define INT_PEND2_offH2I	2	/* Hardware Interrupt 2 Pending bit */
#define INT_PEND2_offH3I	3	/* Hardware Interrupt 3 Pending bit */
#define INT_PEND2_offH4I	4	/* Hardware Interrupt 4 Pending bit */
#define INT_PEND2_offH5I	5	/* Hardware Interrupt 5 Pending bit */
#define INT_PEND2_offH6I	6	/* Hardware Interrupt 6 Pending bit */
#define INT_PEND2_offH7I	7	/* Hardware Interrupt 7 Pending bit */
#define INT_PEND2_offH8I	8	/* Hardware Interrupt 8 Pending bit */
#define INT_PEND2_offH9I	9	/* Hardware Interrupt 9 Pending bit */
#define INT_PEND2_offH10I	10	/* Hardware Interrupt 10 Pending bit */
#define INT_PEND2_offH11I	11	/* Hardware Interrupt 11 Pending bit */
#define INT_PEND2_offH12I	12	/* Hardware Interrupt 12 Pending bit */
#define INT_PEND2_offH13I	13	/* Hardware Interrupt 13 Pending bit */
#define INT_PEND2_offH14I	14	/* Hardware Interrupt 14 Pending bit */
#define INT_PEND2_offH15I	15	/* Hardware Interrupt 15 Pending bit */
#define INT_PEND2_offH16I	16	/* Hardware Interrupt 16 Pending bit */
#define INT_PEND2_offH17I	17	/* Hardware Interrupt 17 Pending bit */
#define INT_PEND2_offH18I	18	/* Hardware Interrupt 18 Pending bit */
#define INT_PEND2_offH19I	19	/* Hardware Interrupt 19 Pending bit */
#define INT_PEND2_offH20I	20	/* Hardware Interrupt 20 Pending bit */
#define INT_PEND2_offH21I	21	/* Hardware Interrupt 21 Pending bit */
#define INT_PEND2_offH22I	22	/* Hardware Interrupt 22 Pending bit */
#define INT_PEND2_offH23I	23	/* Hardware Interrupt 23 Pending bit */
#define INT_PEND2_offH24I	24	/* Hardware Interrupt 24 Pending bit */
#define INT_PEND2_offH25I	25	/* Hardware Interrupt 25 Pending bit */
#define INT_PEND2_offH26I	26	/* Hardware Interrupt 26 Pending bit */
#define INT_PEND2_offH27I	27	/* Hardware Interrupt 27 Pending bit */
#define INT_PEND2_offH28I	28	/* Hardware Interrupt 28 Pending bit */
#define INT_PEND2_offH29I	29	/* Hardware Interrupt 29 Pending bit */
#define INT_PEND2_offH30I	30	/* Hardware Interrupt 30 Pending bit */
#define INT_PEND2_offH31I	31	/* Hardware Interrupt 31 Pending bit */

#define INT_PEND2_mskH0I	( 0x1 << INT_PEND2_offH0I )
#define INT_PEND2_mskH1I	( 0x1 << INT_PEND2_offH1I )
#define INT_PEND2_mskH2I	( 0x1 << INT_PEND2_offH2I )
#define INT_PEND2_mskH3I	( 0x1 << INT_PEND2_offH3I )
#define INT_PEND2_mskH4I	( 0x1 << INT_PEND2_offH4I )
#define INT_PEND2_mskH5I	( 0x1 << INT_PEND2_offH5I )
#define INT_PEND2_mskH6I	( 0x1 << INT_PEND2_offH6I )
#define INT_PEND2_mskH7I	( 0x1 << INT_PEND2_offH7I )
#define INT_PEND2_mskH8I	( 0x1 << INT_PEND2_offH8I )
#define INT_PEND2_mskH9I	( 0x1 << INT_PEND2_offH9I )
#define INT_PEND2_mskH10I	( 0x1 << INT_PEND2_offH10I )
#define INT_PEND2_mskH11I	( 0x1 << INT_PEND2_offH11I )
#define INT_PEND2_mskH12I	( 0x1 << INT_PEND2_offH12I )
#define INT_PEND2_mskH13I	( 0x1 << INT_PEND2_offH13I )
#define INT_PEND2_mskH14I	( 0x1 << INT_PEND2_offH14I )
#define INT_PEND2_mskH15I	( 0x1 << INT_PEND2_offH15I )
#define INT_PEND2_mskH16I	( 0x1 << INT_PEND2_offH16I )
#define INT_PEND2_mskH17I	( 0x1 << INT_PEND2_offH17I )
#define INT_PEND2_mskH18I	( 0x1 << INT_PEND2_offH18I )
#define INT_PEND2_mskH19I	( 0x1 << INT_PEND2_offH19I )
#define INT_PEND2_mskH20I	( 0x1 << INT_PEND2_offH20I )
#define INT_PEND2_mskH21I	( 0x1 << INT_PEND2_offH21I )
#define INT_PEND2_mskH22I	( 0x1 << INT_PEND2_offH22I )
#define INT_PEND2_mskH23I	( 0x1 << INT_PEND2_offH23I )
#define INT_PEND2_mskH24I	( 0x1 << INT_PEND2_offH24I )
#define INT_PEND2_mskH25I	( 0x1 << INT_PEND2_offH25I )
#define INT_PEND2_mskH26I	( 0x1 << INT_PEND2_offH26I )
#define INT_PEND2_mskH27I	( 0x1 << INT_PEND2_offH27I )
#define INT_PEND2_mskH28I	( 0x1 << INT_PEND2_offH28I )
#define INT_PEND2_mskH29I	( 0x1 << INT_PEND2_offH29I )
#define INT_PEND2_mskH30I	( 0x1 << INT_PEND2_offH30I )
#define INT_PEND2_mskH31I	( 0x1 << INT_PEND2_offH31I )

/******************************************************************************
 * ir28: INT_PRI2 (Interrupt Priority Register)
 *****************************************************************************/
#define INT_PRI_offH16PRI	0	/* Hardware Interrupt 16 Priority Level */
#define INT_PRI_offH17PRI	2	/* Hardware Interrupt 17 Priority Level */
#define INT_PRI_offH18PRI	4	/* Hardware Interrupt 18 Priority Level */
#define INT_PRI_offH19PRI	6	/* Hardware Interrupt 19 Priority Level */
#define INT_PRI_offH20PRI	8	/* Hardware Interrupt 20 Priority Level */
#define INT_PRI_offH21PRI	10	/* Hardware Interrupt 21 Priority Level */
#define INT_PRI_offH22PRI	12	/* Hardware Interrupt 22 Priority Level */
#define INT_PRI_offH23PRI	14	/* Hardware Interrupt 23 Priority Level */
#define INT_PRI_offH24PRI	16	/* Hardware Interrupt 24 Priority Level */
#define INT_PRI_offH25PRI	18	/* Hardware Interrupt 25 Priority Level */
#define INT_PRI_offH26PRI	20	/* Hardware Interrupt 26 Priority Level */
#define INT_PRI_offH27PRI	22	/* Hardware Interrupt 27 Priority Level */
#define INT_PRI_offH28PRI	24	/* Hardware Interrupt 28 Priority Level */
#define INT_PRI_offH29PRI	26	/* Hardware Interrupt 29 Priority Level */
#define INT_PRI_offH30PRI	28	/* Hardware Interrupt 30 Priority Level */
#define INT_PRI_offH31PRI	30	/* Hardware Interrupt 31 Priority Level */

#define INT_PRI_mskH16PRI	( 0x3 << INT_PRI_offH16PRI )
#define INT_PRI_mskH17PRI	( 0x3 << INT_PRI_offH17PRI )
#define INT_PRI_mskH18PRI	( 0x3 << INT_PRI_offH18PRI )
#define INT_PRI_mskH19PRI	( 0x3 << INT_PRI_offH19PRI )
#define INT_PRI_mskH20PRI	( 0x3 << INT_PRI_offH20PRI )
#define INT_PRI_mskH21PRI	( 0x3 << INT_PRI_offH21PRI )
#define INT_PRI_mskH22PRI	( 0x3 << INT_PRI_offH22PRI )
#define INT_PRI_mskH23PRI	( 0x3 << INT_PRI_offH23PRI )
#define INT_PRI_mskH24PRI	( 0x3 << INT_PRI_offH24PRI )
#define INT_PRI_mskH25PRI	( 0x3 << INT_PRI_offH25PRI )
#define INT_PRI_mskH26PRI	( 0x3 << INT_PRI_offH26PRI )
#define INT_PRI_mskH27PRI	( 0x3 << INT_PRI_offH27PRI )
#define INT_PRI_mskH28PRI	( 0x3 << INT_PRI_offH28PRI )
#define INT_PRI_mskH29PRI	( 0x3 << INT_PRI_offH29PRI )
#define INT_PRI_mskH30PRI	( 0x3 << INT_PRI_offH30PRI )
#define INT_PRI_mskH31PRI	( 0x3 << INT_PRI_offH31PRI )

/******************************************************************************
 * ir29: INT_TRIGGER (Interrupt Trigger Type Register)
 *****************************************************************************/
#define INT_TRIGGER_offH0TRIG	0	/* Hardware Interrupt 0 Trigger Type bit */
#define INT_TRIGGER_offH1TRIG	1	/* Hardware Interrupt 1 Trigger Type bit */
#define INT_TRIGGER_offH2TRIG	2	/* Hardware Interrupt 2 Trigger Type bit */
#define INT_TRIGGER_offH3TRIG	3	/* Hardware Interrupt 3 Trigger Type bit */
#define INT_TRIGGER_offH4TRIG	4	/* Hardware Interrupt 4 Trigger Type bit */
#define INT_TRIGGER_offH5TRIG	5	/* Hardware Interrupt 5 Trigger Type bit */
#define INT_TRIGGER_offH6TRIG	6	/* Hardware Interrupt 6 Trigger Type bit */
#define INT_TRIGGER_offH7TRIG	7	/* Hardware Interrupt 7 Trigger Type bit */
#define INT_TRIGGER_offH8TRIG	8	/* Hardware Interrupt 8 Trigger Type bit */
#define INT_TRIGGER_offH9TRIG	9	/* Hardware Interrupt 9 Trigger Type bit */
#define INT_TRIGGER_offH10TRIG	10	/* Hardware Interrupt 10 Trigger Type bit */
#define INT_TRIGGER_offH11TRIG	11	/* Hardware Interrupt 11 Trigger Type bit */
#define INT_TRIGGER_offH12TRIG	12	/* Hardware Interrupt 12 Trigger Type bit */
#define INT_TRIGGER_offH13TRIG	13	/* Hardware Interrupt 13 Trigger Type bit */
#define INT_TRIGGER_offH14TRIG	14	/* Hardware Interrupt 14 Trigger Type bit */
#define INT_TRIGGER_offH15TRIG	15	/* Hardware Interrupt 15 Trigger Type bit */
#define INT_TRIGGER_offH16TRIG	16	/* Hardware Interrupt 16 Trigger Type bit */
#define INT_TRIGGER_offH17TRIG	17	/* Hardware Interrupt 17 Trigger Type bit */
#define INT_TRIGGER_offH18TRIG	18	/* Hardware Interrupt 18 Trigger Type bit */
#define INT_TRIGGER_offH19TRIG	19	/* Hardware Interrupt 19 Trigger Type bit */
#define INT_TRIGGER_offH20TRIG	20	/* Hardware Interrupt 20 Trigger Type bit */
#define INT_TRIGGER_offH21TRIG	21	/* Hardware Interrupt 21 Trigger Type bit */
#define INT_TRIGGER_offH22TRIG	22	/* Hardware Interrupt 22 Trigger Type bit */
#define INT_TRIGGER_offH23TRIG	23	/* Hardware Interrupt 23 Trigger Type bit */
#define INT_TRIGGER_offH24TRIG	24	/* Hardware Interrupt 24 Trigger Type bit */
#define INT_TRIGGER_offH25TRIG	25	/* Hardware Interrupt 25 Trigger Type bit */
#define INT_TRIGGER_offH26TRIG	26	/* Hardware Interrupt 26 Trigger Type bit */
#define INT_TRIGGER_offH27TRIG	27	/* Hardware Interrupt 27 Trigger Type bit */
#define INT_TRIGGER_offH28TRIG	28	/* Hardware Interrupt 28 Trigger Type bit */
#define INT_TRIGGER_offH29TRIG	29	/* Hardware Interrupt 29 Trigger Type bit */
#define INT_TRIGGER_offH30TRIG	30	/* Hardware Interrupt 30 Trigger Type bit */
#define INT_TRIGGER_offH31TRIG	31	/* Hardware Interrupt 31 Trigger Type bit */

#define INT_TRIGGER_mskH0TRIG	( 0x1 << INT_TRIGGER_offH0TRIG )
#define INT_TRIGGER_mskH1TRIG	( 0x1 << INT_TRIGGER_offH1TRIG )
#define INT_TRIGGER_mskH2TRIG	( 0x1 << INT_TRIGGER_offH2TRIG )
#define INT_TRIGGER_mskH3TRIG	( 0x1 << INT_TRIGGER_offH3TRIG )
#define INT_TRIGGER_mskH4TRIG	( 0x1 << INT_TRIGGER_offH4TRIG )
#define INT_TRIGGER_mskH5TRIG	( 0x1 << INT_TRIGGER_offH5TRIG )
#define INT_TRIGGER_mskH6TRIG	( 0x1 << INT_TRIGGER_offH6TRIG )
#define INT_TRIGGER_mskH7TRIG	( 0x1 << INT_TRIGGER_offH7TRIG )
#define INT_TRIGGER_mskH8TRIG	( 0x1 << INT_TRIGGER_offH8TRIG )
#define INT_TRIGGER_mskH9TRIG	( 0x1 << INT_TRIGGER_offH9TRIG )
#define INT_TRIGGER_mskH10TRIG	( 0x1 << INT_TRIGGER_offH10TRIG )
#define INT_TRIGGER_mskH11TRIG	( 0x1 << INT_TRIGGER_offH11TRIG )
#define INT_TRIGGER_mskH12TRIG	( 0x1 << INT_TRIGGER_offH12TRIG )
#define INT_TRIGGER_mskH13TRIG	( 0x1 << INT_TRIGGER_offH13TRIG )
#define INT_TRIGGER_mskH14TRIG	( 0x1 << INT_TRIGGER_offH14TRIG )
#define INT_TRIGGER_mskH15TRIG	( 0x1 << INT_TRIGGER_offH15TRIG )
#define INT_TRIGGER_mskH16TRIG	( 0x1 << INT_TRIGGER_offH16TRIG )
#define INT_TRIGGER_mskH17TRIG	( 0x1 << INT_TRIGGER_offH17TRIG )
#define INT_TRIGGER_mskH18TRIG	( 0x1 << INT_TRIGGER_offH18TRIG )
#define INT_TRIGGER_mskH19TRIG	( 0x1 << INT_TRIGGER_offH19TRIG )
#define INT_TRIGGER_mskH20TRIG	( 0x1 << INT_TRIGGER_offH20TRIG )
#define INT_TRIGGER_mskH21TRIG	( 0x1 << INT_TRIGGER_offH21TRIG )
#define INT_TRIGGER_mskH22TRIG	( 0x1 << INT_TRIGGER_offH22TRIG )
#define INT_TRIGGER_mskH23TRIG	( 0x1 << INT_TRIGGER_offH23TRIG )
#define INT_TRIGGER_mskH24TRIG	( 0x1 << INT_TRIGGER_offH24TRIG )
#define INT_TRIGGER_mskH25TRIG	( 0x1 << INT_TRIGGER_offH25TRIG )
#define INT_TRIGGER_mskH26TRIG	( 0x1 << INT_TRIGGER_offH26TRIG )
#define INT_TRIGGER_mskH27TRIG	( 0x1 << INT_TRIGGER_offH27TRIG )
#define INT_TRIGGER_mskH28TRIG	( 0x1 << INT_TRIGGER_offH28TRIG )
#define INT_TRIGGER_mskH29TRIG	( 0x1 << INT_TRIGGER_offH29TRIG )
#define INT_TRIGGER_mskH30TRIG	( 0x1 << INT_TRIGGER_offH30TRIG )
#define INT_TRIGGER_mskH31TRIG	( 0x1 << INT_TRIGGER_offH31TRIG )

/******************************************************************************
 * mr0: MMU_CTL (MMU Control Register)
 *****************************************************************************/
#define MMU_CTL_offD		0	/* Default minimum page size */
#define MMU_CTL_offNTC0		1	/* Non-Translated Cachebility of partition 0 */
#define MMU_CTL_offNTC1		3	/* Non-Translated Cachebility of partition 1 */
#define MMU_CTL_offNTC2		5	/* Non-Translated Cachebility of partition 2 */
#define MMU_CTL_offNTC3		7	/* Non-Translated Cachebility of partition 3 */
#define MMU_CTL_offTBALCK	9	/* TLB all-lock resolution scheme */
#define MMU_CTL_offMPZIU	10	/* Multiple Page Size In Use bit */
#define MMU_CTL_offNTM0		11	/* Non-Translated VA to PA of partition 0 */
#define MMU_CTL_offNTM1		13	/* Non-Translated VA to PA of partition 1 */
#define MMU_CTL_offNTM2		15	/* Non-Translated VA to PA of partition 2 */
#define MMU_CTL_offNTM3		17	/* Non-Translated VA to PA of partition 3 */
#define MMU_CTL_offDREE		19	/* Device register endian control enable */
/* bit 20:31 reserved */

#define MMU_CTL_mskD		( 0x1 << MMU_CTL_offD )
#define MMU_CTL_mskNTC0		( 0x3 << MMU_CTL_offNTC0 )
#define MMU_CTL_mskNTC1		( 0x3 << MMU_CTL_offNTC1 )
#define MMU_CTL_mskNTC2		( 0x3 << MMU_CTL_offNTC2 )
#define MMU_CTL_mskNTC3		( 0x3 << MMU_CTL_offNTC3 )
#define MMU_CTL_mskTBALCK	( 0x1 << MMU_CTL_offTBALCK )
#define MMU_CTL_mskMPZIU	( 0x1 << MMU_CTL_offMPZIU )
#define MMU_CTL_mskNTM0		( 0x3 << MMU_CTL_offNTM0 )
#define MMU_CTL_mskNTM1         ( 0x3 << MMU_CTL_offNTM1 )
#define MMU_CTL_mskNTM2         ( 0x3 << MMU_CTL_offNTM2 )
#define MMU_CTL_mskNTM3         ( 0x3 << MMU_CTL_offNTM3 )
#define MMU_CTL_mskDREE		( 0x1 << MMU_CTL_offDREE )

/******************************************************************************
 * mr1: L1_PPTB (L1 Physical Page Table Base Register)
 *****************************************************************************/
#define L1_PPTB_offNV		0	/* Enable Hardware Page Table Walker (HPTWK) */
/* bit 1:11 reserved */
#define L1_PPTB_offBASE		12	/* First level physical page table base address */

#define L1_PPTB_mskNV		( 0x1 << L1_PPTB_offNV )
#define L1_PPTB_mskBASE		( 0xFFFFF << L1_PPTB_offBASE )

/******************************************************************************
 * mr2: TLB_VPN (TLB Access VPN Register)
 *****************************************************************************/
/* bit 0:11 reserved */
#define TLB_VPN_offVPN		12	/* Virtual Page Number */

#define TLB_VPN_mskVPN		( 0xFFFFF << TLB_VPN_offVPN )

/******************************************************************************
 * mr3: TLB_DATA (TLB Access Data Register)
 *****************************************************************************/
#define TLB_DATA_offV		0	/* PTE is valid and present */
#define TLB_DATA_offM		1	/* Page read/write access privilege */
#define TLB_DATA_offD		4	/* Dirty bit */
#define TLB_DATA_offX		5	/* Executable bit */
#define TLB_DATA_offA		6	/* Access bit */
#define TLB_DATA_offG		7	/* Global page (shared across contexts) */
#define TLB_DATA_offC		8	/* Cacheability atribute */
/* bit 11:11 reserved */
#define TLB_DATA_offPPN		12	/* Phisical Page Number */

#define TLB_DATA_mskV		( 0x1 << TLB_DATA_offV )
#define TLB_DATA_mskM		( 0x7 << TLB_DATA_offM )
#define TLB_DATA_mskD		( 0x1 << TLB_DATA_offD )
#define TLB_DATA_mskX		( 0x1 << TLB_DATA_offX )
#define TLB_DATA_mskA		( 0x1 << TLB_DATA_offA )
#define TLB_DATA_mskG		( 0x1 << TLB_DATA_offG )
#define TLB_DATA_mskC		( 0x7 << TLB_DATA_offC )
#define TLB_DATA_mskPPN		( 0xFFFFF << TLB_DATA_offPPN )

/******************************************************************************
 * mr4: TLB_MISC (TLB Access Misc Register)
 *****************************************************************************/
#define TLB_MISC_offACC_PSZ	0	/* Page size of a PTE entry */
#define TLB_MISC_offCID		4	/* Context id */
/* bit 13:31 reserved */

#define TLB_MISC_mskACC_PSZ    ( 0xF << TLB_MISC_offACC_PSZ )
#define TLB_MISC_mskCID        ( 0x1FF << TLB_MISC_offCID )

/******************************************************************************
 * mr5: VLPT_IDX (Virtual Linear Page Table Index Register)
 *****************************************************************************/
#define VLPT_IDX_offZERO	0	/* Always 0 */
#define VLPT_IDX_offEVPN	2	/* Exception Virtual Page Number */
#define VLPT_IDX_offVLPTB	22	/* Base VA of VLPT */

#define VLPT_IDX_mskZERO	( 0x3 << VLPT_IDX_offZERO )
#define VLPT_IDX_mskEVPN	( 0xFFFFF << VLPT_IDX_offEVPN )
#define VLPT_IDX_mskVLPTB	( 0x3FF << VLPT_IDX_offVLPTB )

/******************************************************************************
 * mr6: ILMB (Instruction Local Memory Base Register)
 *****************************************************************************/
#define ILMB_offIEN		0	/* Enable ILM */
#define ILMB_offILMSZ		1	/* Size of ILM */
/* bit 5:19 reserved */
#define ILMB_offIBPA		10	/* Base PA of ILM */

#define ILMB_mskIEN		( 0x1 << ILMB_offIEN )
#define ILMB_mskILMSZ		( 0xF << ILMB_offILMSZ )
#define ILMB_mskIBPA		( 0xFFF << ILMB_offIBPA )

/******************************************************************************
 * mr7: DLMB (Data Local Memory Base Register)
 *****************************************************************************/
#define DLMB_offDEN		0	/* Enable DLM */
#define DLMB_offDLMSZ		1	/* Size of DLM */
#define DLMB_offDBM		5	/* Enable Double-Buffer Mode for DLM */
#define DLMB_offDBB		6	/* Double-buffer bank which can be accessed by the processor */
/* bit 7:19 reserved */
#define DLMB_offDBPA		10	/* Base PA of DLM */

#define DLMB_mskDEN		( 0x1 << DLMB_offDEN )
#define DLMB_mskDLMSZ		( 0xF << DLMB_offDLMSZ )
#define DLMB_mskDBM		( 0x1 << DLMB_offDBM )
#define DLMB_mskDBB		( 0x1 << DLMB_offDBB )
#define DLMB_mskDBPA		( 0xFFF << DLMB_offDBPA )

/******************************************************************************
 * mr8: CACHE_CTL (Cache Control Register)
 *****************************************************************************/
#define CACHE_CTL_offIC_EN	0	/* Enable I-cache */
#define CACHE_CTL_offDC_EN	1	/* Enable D-cache */
#define CACHE_CTL_offICALCK	2	/* I-cache all-lock resolution scheme */
#define CACHE_CTL_offDCALCK	3	/* D-cache all-lock resolution scheme */
#define CACHE_CTL_offDCCWF	4	/* Enable D-cache Critical Word Forwarding */
#define CACHE_CTL_offDCPMW	5	/* Enable D-cache concurrent miss and write-back processing */
/* bit 6:31 reserved */

#define CACHE_CTL_mskIC_EN	( 0x1 << CACHE_CTL_offIC_EN )
#define CACHE_CTL_mskDC_EN	( 0x1 << CACHE_CTL_offDC_EN )
#define CACHE_CTL_mskICALCK	( 0x1 << CACHE_CTL_offICALCK )
#define CACHE_CTL_mskDCALCK	( 0x1 << CACHE_CTL_offDCALCK )
#define CACHE_CTL_mskDCCWF	( 0x1 << CACHE_CTL_offDCCWF )
#define CACHE_CTL_mskDCPMW	( 0x1 << CACHE_CTL_offDCPMW )

/******************************************************************************
 * mr9: HSMP_SADDR (High Speed Memory Port Starting Address)
 *****************************************************************************/
#define HSMP_SADDR_offEN	0	/* Enable control bit for the High Speed Memory port */
#define HSMP_SADDR_offRANGE	1	/* Denote the address range (only defined in HSMP v2 ) */
/* bit 13:19 reserved */

#define HSMP_SADDR_offSADJ1DR	20	/* Starting base PA of the High Speed Memory Port region */

#define HSMP_SADDR_mskEN	( 0x1 << HSMP_SADDR_offEN )
#define HSMP_SADDR_mskRANGE	( 0xFFF << HSMP_SADDR_offRANGE )
#define HSMP_SADDR_mskSADDR	( 0xFFF << HSMP_SADDR_offSADDR )

/******************************************************************************
 * mr10: HSMP_EADDR (High Speed Memory Port Ending Address)
 *****************************************************************************/
/* bit 0:19 reserved */
#define HSMP_EADDR_offEADDR	20

#define HSMP_EADDR_mskEADDR	( 0xFFF << HSMP_EADDR_offEADDR )

/******************************************************************************
 * dr0+(n*5): BPCn (n=0-7) (Breakpoint Control Register)
 *****************************************************************************/
#define BPC_offWP		0	/* Configuration of BPAn */
#define BPC_offEL		1	/* Enable BPAn */
#define BPC_offS		2	/* Data address comparison for a store instruction */
#define BPC_offP		3	/* Compared data address is PA */
#define BPC_offC		4	/* CID value is compared with the BPCIDn register */
#define BPC_offBE0		5	/* Enable byte mask for the comparison with register */
#define BPC_offBE1		6	/* Enable byte mask for the comparison with register */
#define BPC_offBE2		7	/* Enable byte mask for the comparison with register */
#define BPC_offBE3		8	/* Enable byte mask for the comparison with register */
#define BPC_offT		9	/* Enable breakpoint Embedded Tracer triggering operation */

#define BPC_mskWP		( 0x1 << BPC_offWP )
#define BPC_mskEL		( 0x1 << BPC_offEL )
#define BPC_mskS		( 0x1 << BPC_offS )
#define BPC_mskP		( 0x1 << BPC_offP )
#define BPC_mskC		( 0x1 << BPC_offC )
#define BPC_mskBE0		( 0x1 << BPC_offBE0 )
#define BPC_mskBE1		( 0x1 << BPC_offBE1 )
#define BPC_mskBE2		( 0x1 << BPC_offBE2 )
#define BPC_mskBE3		( 0x1 << BPC_offBE3 )
#define BPC_mskT		( 0x1 << BPC_offT )

/******************************************************************************
 * dr1+(n*5): BPAn (n=0-7) (Breakpoint Address Register)
 *****************************************************************************/

	/* These registers contain break point address */

/******************************************************************************
 * dr2+(n*5): BPAMn (n=0-7) (Breakpoint Address Mask Register)
 *****************************************************************************/

	/* These registerd contain the address comparison mask for the BPAn register */

/******************************************************************************
 * dr3+(n*5): BPVn (n=0-7) Breakpoint Data Value Register
 *****************************************************************************/

	/* The BPVn register contains the data value that will be compared with the
	 * incoming load/store data value */

/******************************************************************************
 * dr4+(n*5): BPCIDn (n=0-7) (Breakpoint Context ID Register)
 *****************************************************************************/
#define BPCID_offCID		0	/* CID that will be compared with a process's CID */
/* bit 9:31 reserved */

#define BPCID_mskCID		( 0x1FF << BPCID_offCID )

/******************************************************************************
 * dr40: EDM_CFG (EDM Configuration Register)
 *****************************************************************************/
#define EDM_CFG_offBC		0	/* Number of hardware breakpoint sets implemented */
#define EDM_CFG_offDIMU		3	/* Debug Instruction Memory Unit exists */
/* bit 4:15 reserved */
#define EDM_CFG_offVER		16	/* EDM version */

#define EDM_CFG_mskBC		( 0x7 << EDM_CFG_offBC )
#define EDM_CFG_mskDIMU		( 0x1 << EDM_CFG_offDIMU )
#define EDM_CFG_mskVER		( 0xFFFF << EDM_CFG_offVER )

/******************************************************************************
 * dr41: EDMSW (EDM Status Word)
 *****************************************************************************/
#define EDMSW_offWV		0	/* Write Valid */
#define EDMSW_offRV		1	/* Read Valid */
#define EDMSW_offDE		2	/* Debug exception has occurred for this core */
/* bit 3:31 reserved */

#define EDMSW_mskWV		( 0x1 << EDMSW_offWV )
#define EDMSW_mskRV		( 0x1 << EDMSW_offRV )
#define EDMSW_mskDE		( 0x1 << EDMSW_offDE )

/******************************************************************************
 * dr42: EDM_CTL (EDM Control Register)
 *****************************************************************************/
/* bit 0:30 reserved */
#define EDM_CTL_offDEH_SEL	31	/* Controls where debug exception is directed to */

#define EDM_CTL_mskDEH_SEL	( 0x1 << EDM_CTL_offDEH_SEL )

/******************************************************************************
 * dr43: EDM_DTR (EDM Data Transfer Register)
 *****************************************************************************/

	/* This is used to exchange data between the embedded EDM logic
	 * and the processor core */

/******************************************************************************
 * dr44: BPMTC (Breakpoint Match Trigger Counter Register)
 *****************************************************************************/
#define BPMTC_offBPMTC		0	/* Breakpoint match trigger counter value */
/* bit 16:31 reserved */

#define BPMTC_mskBPMTC		( 0xFFFF << BPMTC_offBPMTC )

/******************************************************************************
 * dr45: DIMBR (Debug Instruction Memory Base Register)
 *****************************************************************************/
/* bit 0:11 reserved */
#define DIMBR_offDIMB		12	/* Base address of the Debug Instruction Memory (DIM)*/
#define DIMBR_mskDIMB		( 0xFFFFF << DIMBR_offDIMB )

/******************************************************************************
 * dr46: TECR0(Trigger Event Control register 0)
 * dr47: TECR1 (Trigger Event Control register 1)
 *****************************************************************************/
#define TECR_offBP		0	/* Controld which BP is used as a trigger source */
#define TECR_offNMI		8	/* Use NMI as a trigger source */
#define TECR_offHWINT		9	/* Corresponding interrupt is used as a trigger source */
#define TECR_offEVIC		15	/* Enable HWINT as a trigger source in EVIC mode */
#define TECR_offSYS		16	/* Enable SYSCALL instruction as a trigger source */
#define TECR_offDBG		17	/* Enable debug exception as a trigger source */
#define TECR_offMRE		18	/* Enable MMU related exception as a trigger source */
#define TECR_offE		19	/* An exception is used as a trigger source */
/* bit 20:30 reserved */
#define TECR_offL		31	/* Link/Cascade TECR0 trigger event to TECR1 trigger event */

#define TECR_mskBP		( 0xFF << TECR_offBP )
#define TECR_mskNMI		( 0x1 << TECR_offBNMI )
#define TECR_mskHWINT		( 0x3F << TECR_offBHWINT )
#define TECR_mskEVIC		( 0x1 << TECR_offBEVIC )
#define TECR_mskSYS		( 0x1 << TECR_offBSYS )
#define TECR_mskDBG		( 0x1 << TECR_offBDBG )
#define TECR_mskMRE		( 0x1 << TECR_offBMRE )
#define TECR_mskE		( 0x1 << TECR_offE )
#define TECR_mskL		( 0x1 << TECR_offL )

/******************************************************************************
 * hspr0: HSP_CTL (HW Stack Protection Control Register)
 *****************************************************************************/
#define HSP_CTL_offHSP_EN	0	/* Enable bit for the stack protection and recording mechanism */
#define HSP_CTL_offSCHM		1	/* Operating scheme of the stack protection and recording */
#define HSP_CTL_offSU		2	/* Enable the SP protection and recording in the super-user mode */
#define HSP_CTL_offU		3	/* Enable the SP protection and recording in the user mode */
#define HSP_CTL_offSPL		4	/* (Secure Core Only) the enabled Security Privilege Level */
/* bit 7:31 reserved */

#define HSP_CTL_mskHSP_EN	( 0x1 << HSP_CTL_offHSP_EN )
#define HSP_CTL_mskSCHM		( 0x1 << HSP_CTL_offSCHM )
#define HSP_CTL_mskSU		( 0x1 << HSP_CTL_offSU )
#define HSP_CTL_mskU		( 0x1 << HSP_CTL_offU )
#define HSP_CTL_mskSPL		( 0x7 << HSP_CTL_offSPL )

/******************************************************************************
 * hspr1: SP_BOUND (SP Bound Register)
 * hspr2: SP_BOUND_PRIV (Shadowed Privileged SP Bound Register)
 *****************************************************************************/

	/* These registers contains the stack overflow bound */

/******************************************************************************
 * pfr0-2: PFMC0-2 (Performance Counter Register 0-2)
 *****************************************************************************/

	/* These registers contains performance event count */

/******************************************************************************
 * pfr3: PFM_CTL (Performance Counter Control Register)
 *****************************************************************************/
#define PFM_CTL_offEN0		0	/* Enable PFMC0 */
#define PFM_CTL_offEN1		1	/* Enable PFMC1 */
#define PFM_CTL_offEN2		2	/* Enable PFMC2 */
#define PFM_CTL_offIE0		3	/* Enable interrupt for PFMC0 */
#define PFM_CTL_offIE1		4	/* Enable interrupt for PFMC1 */
#define PFM_CTL_offIE2		5	/* Enable interrupt for PFMC2 */
#define PFM_CTL_offOVF0		6	/* Overflow bit of PFMC0 */
#define PFM_CTL_offOVF1		7	/* Overflow bit of PFMC1 */
#define PFM_CTL_offOVF2		8	/* Overflow bit of PFMC2 */
#define PFM_CTL_offKS0		9	/* Enable superuser mode event counting for PFMC0 */
#define PFM_CTL_offKS1		10	/* Enable superuser mode event counting for PFMC1 */
#define PFM_CTL_offKS2		11	/* Enable superuser mode event counting for PFMC2 */
#define PFM_CTL_offKU0		12	/* Enable user mode event counting for PFMC0 */
#define PFM_CTL_offKU1		13	/* Enable user mode event counting for PFMC1 */
#define PFM_CTL_offKU2		14	/* Enable user mode event counting for PFMC2 */
#define PFM_CTL_offSEL0		15	/* The event selection for PFMC0 */
#define PFM_CTL_offSEL1		16	/* The event selection for PFMC1 */
#define PFM_CTL_offSEL2		22	/* The event selection for PFMC2 */
/* bit 28:30 reserved */
#define PFM_CTL_offMIN_CFG	31	/* Minimum Configuration */

#define PFM_CTL_mskEN0		( 0x01 << PFM_CTL_offEN0 )
#define PFM_CTL_mskEN1		( 0x01 << PFM_CTL_offEN1 )
#define PFM_CTL_mskEN2		( 0x01 << PFM_CTL_offEN2 )
#define PFM_CTL_mskIE0		( 0x01 << PFM_CTL_offIE0 )
#define PFM_CTL_mskIE1		( 0x01 << PFM_CTL_offIE1 )
#define PFM_CTL_mskIE2		( 0x01 << PFM_CTL_offIE2 )
#define PFM_CTL_mskOVF0		( 0x01 << PFM_CTL_offOVF0 )
#define PFM_CTL_mskOVF1		( 0x01 << PFM_CTL_offOVF1 )
#define PFM_CTL_mskOVF2		( 0x01 << PFM_CTL_offOVF2 )
#define PFM_CTL_mskKS0		( 0x01 << PFM_CTL_offKS0 )
#define PFM_CTL_mskKS1		( 0x01 << PFM_CTL_offKS1 )
#define PFM_CTL_mskKS2		( 0x01 << PFM_CTL_offKS2 )
#define PFM_CTL_mskKU0		( 0x01 << PFM_CTL_offKU0 )
#define PFM_CTL_mskKU1		( 0x01 << PFM_CTL_offKU1 )
#define PFM_CTL_mskKU2		( 0x01 << PFM_CTL_offKU2 )
#define PFM_CTL_mskSEL0		( 0x01 << PFM_CTL_offSEL0 )
#define PFM_CTL_mskSEL1		( 0x3F << PFM_CTL_offSEL1 )
#define PFM_CTL_mskSEL2		( 0x3F << PFM_CTL_offSEL2 )
#define PFM_CTL_mskMIN_CFG	( 0x01 << PFM_CTL_offMIN_CFG )

/******************************************************************************
 * pfr4: PFT_CTL (Performance Throttling Control Register)
 *****************************************************************************/
/* bit 0:3 reserved */
#define PFT_CTL_offT_LEVEL	4	/* Throttling Level */
#define PFT_CTL_offFAST_INT	8	/* Fast interrupt response */
/* bit 9:31 reserved */

#define PFT_CTL_mskT_LEVEL	( 0x0F << PFT_CTL_offT_LEVEL )
#define PFT_CTL_mskFAST_INT	( 0x01 << PFT_CTL_offFAST_INT )

/******************************************************************************
 * idr0: SDZ_CTL (Structure Downsizing Control Register)
 *****************************************************************************/
#define SDZ_CTL_offICDZ		0	/* I-cache downsizing control */
#define SDZ_CTL_offDCDZ		3	/* D-cache downsizing control */
#define SDZ_CTL_offMTBDZ	6	/* MTLB downsizing control */
#define SDZ_CTL_offBTBDZ	9	/* Branch Target Table downsizing control */
/* bit 12:31 reserved */
#define SDZ_CTL_mskICDZ		( 0x07 << SDZ_CTL_offICDZ )
#define SDZ_CTL_mskDCDZ		( 0x07 << SDZ_CTL_offDCDZ )
#define SDZ_CTL_mskMTBDZ	( 0x07 << SDZ_CTL_offMTBDZ )
#define SDZ_CTL_mskBTBDZ	( 0x07 << SDZ_CTL_offBTBDZ )

/******************************************************************************
 * idr1: MISC_CTL (Miscellaneous Control Register)
 *****************************************************************************/
#define MISC_CTL_offBTB		0	/* Disable Branch Target Buffer */
#define MISC_CTL_offRTP		1	/* Disable Return Target Predictor */
#define MISC_CTL_offPTEEPF	2	/* Disable HPTWK L2 PTE pefetch */
#define MISC_CTL_offTCM		3	/* Disable Two Cycle Multiplication */
#define MISC_CTL_offSP_SHADOW_EN	4	/* Enable control for shadow stack pointers */
#define MISC_CTL_offLP_CACHE	5	/* Disable the Loop Cache */
/* bit 6:6 reserved */
#define MISC_CTL_offILMC_EN	7	/* Enable Instruction Local Memory Cache */
#define MISC_CTL_offACE		8	/* Disable Andes Custom Extension */
/* bit 9:31 reserved */

#define MISC_CTL_makBTB		( 0x1 << MISC_CTL_makBTB )
#define MISC_CTL_makRTP		( 0x1 << MISC_CTL_makRTP )
#define MISC_CTL_makPTEEPF	( 0x1 << MISC_CTL_makPTEEPF )
#define MISC_CTL_mskTCM		( 0x1 << MISC_CTL_offTCM )
#define MISC_CTL_mskSP_SHADOW_EN ( 0x1 << MISC_CTL_offSP_SHADOW_EN )
#define MISC_CTL_mskLP_CACHE	( 0x1 << MISC_CTL_offLP_CACHE )
#define MISC_CTL_mskILMC_EN	( 0x1 << MISC_CTL_offILMC_EN )
#define MISC_CTL_mskACE		( 0x1 << MISC_CTL_offACE )

/******************************************************************************
 * racr0: PRUSR_ACC_CTL (Privileged Resource User Access Control Registers)
 *****************************************************************************/
#define PRUSR_ACC_CTL_offDMA_EN	0	/* Allow user mode access of DMA registers */
#define PRUSR_ACC_CTL_offPFM_EN	1	/* Allow user mode access of PFM registers */

#define PRUSR_ACC_CTL_mskDMA_EN	( 0x1 << PRUSR_ACC_CTL_offDMA_EN )
#define PRUSR_ACC_CTL_mskPFM_EN	( 0x1 << PRUSR_ACC_CTL_offPFM_EN )

/******************************************************************************
 * dmar0: DMA_CFG (DMA Configuration Register)
 *****************************************************************************/
#define DMA_CFG_offNCHN		0	/* The number of DMA channels implemented */
#define DMA_CFG_offUNEA		2	/* Un-aligned External Address transfer feature */
#define DMA_CFG_off2DET		3	/* 2-D Element Transfer feature */
/* bit 4:15 reserved */
#define DMA_CFG_offVER		16	/* DMA architecture and implementation version */

#define DMA_CFG_mskNCHN		( 0x3 << DMA_CFG_offNCHN )
#define DMA_CFG_mskUNEA		( 0x1 << DMA_CFG_offUNEA )
#define DMA_CFG_msk2DET		( 0x1 << DMA_CFG_off2DET )
#define DMA_CFG_mskVER		( 0xFFFF << DMA_CFG_offVER )

/******************************************************************************
 * dmar1: DMA_GCSW (DMA Global Control and Status Word Register)
 *****************************************************************************/
#define DMA_GCSW_offC0STAT	0	/* DMA channel 0 state */
#define DMA_GCSW_offC1STAT	3	/* DMA channel 1 state */
/* bit 6:11 reserved */
#define DMA_GCSW_offC0INT	12	/* DMA channel 0 generate interrupt */
#define DMA_GCSW_offC1INT	13	/* DMA channel 1 generate interrupt */
#define DMA_GCSW_offHCHAN	16	/* Head channel number */
#define DMA_GCSW_offFSM		18	/* Fast-start mode field */
#define DMA_GCSW_offSCMD	20	/* DMA Sub-Action Command used in the fast-start mode */
/* bit 22:27 reserved */
#define DMA_GCSW_offSDBE	28	/* Shadow DBM and DBB bits Enable control */
#define DMA_GCSW_offDBM		29	/* Double-Buffer Mode enable control for the data local memory */
#define DMA_GCSW_offDBB		30	/* Double-Buffer Bank */
#define DMA_GCSW_offEN		31	/* Enable DMA engine */

#define DMA_GCSW_mskC0STAT	( 0x7 << DMA_GCSW_offC0STAT )
#define DMA_GCSW_mskC1STAT	( 0x7 << DMA_GCSW_offC1STAT )
#define DMA_GCSW_mskC0INT	( 0x1 << DMA_GCSW_offC0INT )
#define DMA_GCSW_mskC1INT	( 0x1 << DMA_GCSW_offC1INT )
#define DMA_GCSW_mskHCHAN	( 0x3 << DMA_GCSW_offHCHAN )
#define DMA_GCSW_mskFSM		( 0x3 << DMA_GCSW_offFSM )
#define DMA_GCSW_mskSCMD	( 0x3 << DMA_GCSW_offSCMD )
#define DMA_GCSW_mskSDBE	( 0x1 << DMA_GCSW_offSDBE )
#define DMA_GCSW_mskDBM		( 0x1 << DMA_GCSW_offDBM )
#define DMA_GCSW_mskDBB		( 0x1 << DMA_GCSW_offDBB )
#define DMA_GCSW_mskEN		( 0x1 << DMA_GCSW_offEN )

/******************************************************************************
 * dmar2: DMA_CHNSEL (DMA Channel Selection Register)
 *****************************************************************************/
#define DMA_CHNSEL_offCHAN	0	/* Selected channel number */
/* bit 2:31 reserved */

#define DMA_CHNSEL_mskCHAN	( 0x3 << DMA_CHNSEL_offCHAN )

/******************************************************************************
 * dmar3: DMA_ACT (DMA Action Register)
 *****************************************************************************/
#define DMA_ACT_offACMD		0	/* DMA Action Command */
#define DMA_ACT_offSCMD		2	/* DMA Sub-action Command */
/* bit 4:31 reserved */
#define DMA_ACT_mskACMD		( 0x3 << DMA_ACT_offACMD )
#define DMA_ACT_mskSCMD		( 0x3 << DMA_ACT_offSCMD )

/******************************************************************************
 * dmar4: DMA_SETUP (DMA Setup Register)
 *****************************************************************************/
#define DMA_SETUP_offLM		0	/* Local Memory Selection */
#define DMA_SETUP_offTDIR	1	/* Transfer Direction */
#define DMA_SETUP_offTES	2	/* Transfer Element Size */
#define DMA_SETUP_offESTR	4	/* External memory transfer Stride */
#define DMA_SETUP_offCIE	16	/* Interrupt Enable on Completion */
#define DMA_SETUP_offSIE	17	/* Interrupt Enable on explicit Stop */
#define DMA_SETUP_offEIE	18	/* Interrupt Enable on Error */
#define DMA_SETUP_offUE		19	/* Enable the Un-aligned External Address */
#define DMA_SETUP_off2DE	20	/* Enable the 2-D External Transfer */
#define DMA_SETUP_offCOA	21	/* Transfer Coalescable */
/* bit 24:31 reserved */

#define DMA_SETUP_mskLM		( 0x1 << DMA_SETUP_offLM )
#define DMA_SETUP_mskTDIR	( 0x1 << DMA_SETUP_offTDIR )
#define DMA_SETUP_mskTES	( 0x3 << DMA_SETUP_offTES )
#define DMA_SETUP_mskESTR	( 0xFFF << DMA_SETUP_offESTR )
#define DMA_SETUP_mskCIE	( 0x1 << DMA_SETUP_offCIE )
#define DMA_SETUP_mskSIE	( 0x1 << DMA_SETUP_offSIE )
#define DMA_SETUP_mskEIE	( 0x1 << DMA_SETUP_offEIE )
#define DMA_SETUP_mskUE		( 0x1 << DMA_SETUP_offUE )
#define DMA_SETUP_msk2DE	( 0x1 << DMA_SETUP_off2DE )
#define DMA_SETUP_mskCOA	( 0x7 << DMA_SETUP_offCOA )

/******************************************************************************
 * dmar5: DMA_ISADDR (DMA Internal Start Address Register)
 *****************************************************************************/
#define DMA_ISADDR_offISADDR	0	/* Internal Start Address */
/* bit 20:31 reserved */
#define DMA_ISADDR_mskISADDR	( 0xFFFFF << DMA_ISADDR_offISADDR )

/******************************************************************************
 * dmar6: DMA_ESADDR (DMA External Start Address Register)
 *****************************************************************************/
	/* This register holds External Start Address */

/******************************************************************************
 * dmar7: DMA_TCNT (DMA Transfer Element Count Register)
 *****************************************************************************/
#define DMA_TCNT_offTCNT	0	/* DMA transfer element count */
/* bit 18:31 reserved */
#define DMA_TCNT_mskTCNT	( 0x7FFFFF << DMA_TCNT_offTCNT )

/******************************************************************************
 * dmar8: DMA_STATUS (DMA Status Register)
 *****************************************************************************/
#define DMA_STATUS_offSTAT	0	/* DMA channel state */
#define DMA_STATUS_offSTUNA	3	/* Un-aligned error on External Stride value */
#define DMA_STATUS_offDERR	4	/* DMA Transfer Disruption Error */
#define DMA_STATUS_offEUNA	5	/* Un-aligned error on the External address */
#define DMA_STATUS_offIUNA	6	/* Un-aligned error on the Internal address */
#define DMA_STATUS_offIOOR	7	/* Out-Of-Range error on the Internal address */
#define DMA_STATUS_offEBUS	8	/* Bus Error on an External DMA transfer */
#define DMA_STATUS_offESUP	9	/* DMA setup error */
/* bit 10:30 reserved */
#define DMA_STATUS_offWE	31	/* Wait event */

#define DMA_STATUS_mskSTAT	( 0x7 << DMA_STATUS_offSTAT )
#define DMA_STATUS_mskSTUNA	( 0x1 << DMDMA_STATUS_offSTUNA )
#define DMA_STATUS_mskDERR	( 0x1 << DMDMA_STATUS_offDERR )
#define DMA_STATUS_mskEUNA	( 0x1 << DMDMA_STATUS_offEUNA )
#define DMA_STATUS_mskIUNA	( 0x1 << DMDMA_STATUS_offIUNA )
#define DMA_STATUS_mskIOOR	( 0x1 << DMDMA_STATUS_offIOOR )
#define DMA_STATUS_mskEBUS	( 0x1 << DMDMA_STATUS_offEBUS )
#define DMA_STATUS_mskESUP	( 0x1 << DMDMA_STATUS_offESUP )
#define DMA_STATUS_mskWE	( 0x1 << DMA_STATUS_offWE )

/******************************************************************************
 * dmar9: DMA_2DSET (DMA 2D Setup Register)
 *****************************************************************************/
#define DMA_2DSET_offWECNT	0	/* The Width Element Count for a 2-D region */
#define DMA_2DSET_offHTSTR	16	/* The Height Stride for a 2-D region */

#define DMA_2DSET_mskHTSTR	( 0xFFFF << DMA_2DSET_offHTSTR )
#define DMA_2DSET_mskWECNT	( 0xFFFF << DMA_2DSET_offWECNT )

/******************************************************************************
 * dmar10: DMA_2DSCTL (DMA 2D Startup Control Register)
 *****************************************************************************/
#define DMA_2DSCTL_offSTWECNT	0	/* Startup Width Element Count for a 2-D region */
/* bit 16:31 reserved */

#define DMA_2DSCTL_mskSTWECNT	( 0xFFFF << DMA_2DSCTL_offSTWECNT )

/******************************************************************************
 * fpcsr: FPCSR (Floating-Point Control Status Register)
 *****************************************************************************/
#define FPCSR_offRM		0
#define FPCSR_offIVO		2
#define FPCSR_offDBZ		3
#define FPCSR_offOVF		4
#define FPCSR_offUDF		5
#define FPCSR_offIEX		6
#define FPCSR_offIVOE		7
#define FPCSR_offDBZE		8
#define FPCSR_offOVFE		9
#define FPCSR_offUDFE		10
#define FPCSR_offIEXE		11
#define FPCSR_offDNZ		12
#define FPCSR_offIVOT		13
#define FPCSR_offDBZT		14
#define FPCSR_offOVFT		15
#define FPCSR_offUDFT		16
#define FPCSR_offIEXT		17
#define FPCSR_offDNIT		18
#define FPCSR_offRIT		19

#define FPCSR_mskRM             ( 0x3 << FPCSR_offRM )
#define FPCSR_mskIVO            ( 0x1 << FPCSR_offIVO )
#define FPCSR_mskDBZ            ( 0x1 << FPCSR_offDBZ )
#define FPCSR_mskOVF            ( 0x1 << FPCSR_offOVF )
#define FPCSR_mskUDF            ( 0x1 << FPCSR_offUDF )
#define FPCSR_mskIEX            ( 0x1 << FPCSR_offIEX )
#define FPCSR_mskIVOE           ( 0x1 << FPCSR_offIVOE )
#define FPCSR_mskDBZE           ( 0x1 << FPCSR_offDBZE )
#define FPCSR_mskOVFE           ( 0x1 << FPCSR_offOVFE )
#define FPCSR_mskUDFE           ( 0x1 << FPCSR_offUDFE )
#define FPCSR_mskIEXE           ( 0x1 << FPCSR_offIEXE )
#define FPCSR_mskDNZ            ( 0x1 << FPCSR_offDNZ )
#define FPCSR_mskIVOT           ( 0x1 << FPCSR_offIVOT )
#define FPCSR_mskDBZT           ( 0x1 << FPCSR_offDBZT )
#define FPCSR_mskOVFT           ( 0x1 << FPCSR_offOVFT )
#define FPCSR_mskUDFT           ( 0x1 << FPCSR_offUDFT )
#define FPCSR_mskIEXT           ( 0x1 << FPCSR_offIEXT )
#define FPCSR_mskDNIT           ( 0x1 << FPCSR_offDNIT )
#define FPCSR_mskRIT            ( 0x1 << FPCSR_offRIT )

/******************************************************************************
 * fpcfg: FPCFG (Floating-Point Configuration Register)
 *****************************************************************************/
#define	FPCFG_offSP		0
#define FPCFG_offDP		1
#define FPCFG_offFREG		2
#define FPCFG_offFMA		4
/* bit 5:21 reserved */
#define FPCFG_offIMVER		22
#define FPCFG_offAVER		27

#define FPCFG_mskSP		( 0x1 << FPCFG_offSP )
#define FPCFG_mskDP		( 0x1 << FPCFG_offDP )
#define FPCFG_mskFREG		( 0x3 << FPCFG_offFREG )
#define FPCFG_mskFMA		( 0x1 << FPCFG_offFMA )
#define FPCFG_mskIMVER		( 0x1F << FPCFG_offIMVER )
#define FPCFG_mskAVER		( 0x1F << FPCFG_offAVER )

/******************************************************************************
 * fucpr: FUCOP_CTL (FPU and Coprocessor Enable Control Register)
 *****************************************************************************/
#define FUCOP_CTL_offFPUEN	0
#define FUCOP_CTL_offCP1EN	1
#define FUCOP_CTL_offCP2EN	2
#define FUCOP_CTL_offCP3EN	3
/* bit 4:30 reserved */
#define FUCOP_CTL_offAUEN	31

#define FUCOP_CTL_mskFPUEN	( 0x1 << FUCOP_CTL_offFPUEN )
#define FUCOP_CTL_mskCP1EN	( 0x1 << FUCOP_CTL_offCP1EN )
#define FUCOP_CTL_mskCP2EN      ( 0x1 << FUCOP_CTL_offCP2EN )
#define FUCOP_CTL_mskCP3EN      ( 0x1 << FUCOP_CTL_offCP3EN )
#define FUCOP_CTL_mskAUEN	( 0x1 << FUCOP_CTL_offAUEN )

#ifdef CONFIG_CACHE_L2
/******************************************************************************
 * L2_CA_CONF (Cache architecture configuration)
 *****************************************************************************/
#define L2_CA_CONF_offL2CLSZ		8
#define L2_CA_CONF_mskL2CLSZ	(0x7 << L2_CA_CONF_offL2CLSZ)
//TODO finish this table

/******************************************************************************
 * L2CC_SETUP (L2CC Setup register)
 *****************************************************************************/
#define L2CC_SETUP_offPART		0
#define L2CC_SETUP_mskPART		(0x3 << L2_CA_CONF_offPART)
#define L2CC_SETUP_offDDLATC		4
#define L2CC_SETUP_mskDDLATC		(0x3 << L2_CA_CONF_offDDLATC)
#define L2CC_SETUP_offTDLATC		8
#define L2CC_SETUP_mskTDLATC		(0x3 << L2_CA_CONF_offTDLATC)

/******************************************************************************
 * L2CC_PROT (L2CC Protect register)
 *****************************************************************************/
#define L2CC_PROT_offMRWEN		31
#define L2CC_PROT_mskMRWEN	(0x1 << L2CC_PROT_offMRWEN)
//TODO finish this table
//
/******************************************************************************
 * L2_CCTL_STATUS_Mn (The L2CCTL command working status for Master n)
 *****************************************************************************/
#define L2CC_CTRL_offEN			31
#define L2CC_CTRL_mskEN			(0x1 << L2CC_CTRL_offEN)

/******************************************************************************
 * L2_CCTL_STATUS_Mn (The L2CCTL command working status for Master n)
 *****************************************************************************/
#define L2_CCTL_STATUS_offCMD_COMP	31
#define L2_CCTL_STATUS_mskCMD_COMP	(0x1 << L2_CCTL_STATUS_offCMD_COMP)
//TODO finish this table

#endif

#endif /* __NDS32_DEFS_H__ */
