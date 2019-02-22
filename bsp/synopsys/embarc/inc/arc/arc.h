/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2014-06-20
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup ARC_HAL_CORE_COMM
 * \brief  header file including common core definitions
 */

 /**
  * \addtogroup ARC_HAL_CORE_COMM
  * @{
  */


#ifndef _ARC_HAL_CORE_H_
#define _ARC_HAL_CORE_H_

#include "inc/arc/arc_feature_config.h"

/**
 * \name exception number definitions
 * @{
 */

/* ARC exception number */
#define EXC_NO_RESET			(0)	/*!< reset vector, the entry of power up and reset */
#define EXC_NO_MEM_ERR			(1)	/*!< external memory bus error */
#define EXC_NO_INS_ERR			(2)	/*!< illegal instruction or illegal instruction sequence */
#define EXC_NO_MAC_CHK			(3)	/*!< machine check error */
#define EXC_NO_TLB_MISS_I		(4)	/*!< instruction TLB missing exception, useless without MMU */
#define EXC_NO_TLB_MISS_D		(5)	/*!< data TLB missing exception, useless without MMU */
#define EXC_NO_PRO_VIO			(6)	/*!< protection violation */
#define EXC_NO_PRI_VIO			(7)	/*!< privilege violation */
#define EXC_NO_SWI			(8)	/*!< software interrupt */
#define EXC_NO_TRAP			(9)	/*!< trap */
#define EXC_NO_EXT			(10)	/*!< extension exception */
#define EXC_NO_DIV_ZER0			(11)	/*!< divide by zero */
#define EXC_NO_DC_ERR			(12)	/*!< data cache consistency error */
#define EXC_NO_MAL_ALIGN		(13)	/*!< misaligned data access */
#define EXC_NO_RESERVE0			(14)	/*!< reserved */
#define EXC_NO_RESERVE1			(15)	/*!< reserved */

/* extension interrupts */
#define EXC_NO_16			(16)	/*!< interrupt vector 16 */
#define EXC_NO_17			(17)	/*!< interrupt vector 17 */
#define EXC_NO_18			(18)	/*!< interrupt vector 18 */
#define EXC_NO_19			(19)	/*!< interrupt vector 19 */
#define EXC_NO_20			(20)	/*!< interrupt vector 20 */
#define EXC_NO_21			(21)	/*!< interrupt vector 21 */
#define EXC_NO_22			(22)	/*!< interrupt vector 22 */
#define EXC_NO_23			(23)	/*!< interrupt vector 23 */
#define EXC_NO_24			(24)	/*!< interrupt vector 24 */
#define EXC_NO_25			(25)	/*!< interrupt vector 25 */
#define EXC_NO_26			(26)	/*!< interrupt vector 26 */
#define EXC_NO_27			(27)	/*!< interrupt vector 27 */
#define EXC_NO_28			(28)	/*!< interrupt vector 28 */
#define EXC_NO_29			(29)	/*!< interrupt vector 29 */
#define EXC_NO_30			(30)	/*!< interrupt vector 30 */
#define EXC_NO_31			(31)	/*!< interrupt vector 31 */
/* ... ARC supports 255 interrupt vectors at most */
#define EXC_NO_255			(255)	/*!< interrupt vector 255 */

/** @} */

/**
 * \name exception vector offset
 * @{
 */
#define EXC_NO_TO_OFFSET(no)	(no << 2)

/* ARC exception vector offset */
#define EXC_VECTOR_RESET		(0x00)	/*!< EXC_NO_RESET offset */
#define EXC_VECTOR_MEM_ERR		(0x04)	/*!< EXC_NO_MEM_ERR offset */
#define EXC_VECTOR_INS_ERR		(0x08)	/*!< EXC_NO_INS_ERR offset */
#define EXC_VECTOR_MAC_CHK		(0x0c)	/*!< EXC_NO_MAC_CHK offset */
#define EXC_VECTOR_TLB_MISS_I		(0x10)	/*!< EXC_NO_TLB_MISS_I offset */
#define EXC_VECTOR_TLB_MISS_D		(0x14)	/*!< EXC_NO_TLB_MISS_D offset */
#define EXC_VECTOR_PRO_VIO		(0x18)	/*!< EXC_NO_PRO_VIO offset */
#define EXC_VECTOR_PRI_VIO		(0x1c)	/*!< EXC_NO_PRI_VIO offset */
#define EXC_VECTOR_SWI			(0x20)	/*!< EXC_NO_SWI offset */
#define EXC_VECTOR_TRAP			(0x24)	/*!< EXC_NO_TRAP offset */
#define EXC_VECTOR_EXT			(0x28)	/*!< EXC_NO_EXT offset */
#define EXC_VECTOR_DIV_ZER0		(0x2c)	/*!< EXC_NO_DIV_ZER0 offset */
#define EXC_VECTOR_DC_ERR		(0x30)	/*!< EXC_NO_DC_ERR offset */
#define EXC_VECTOR_MAL_ALIGN		(0x34)	/*!< EXC_NO_MAL_ALIGN offset */
#define EXC_VECTOR_RESERVE0		(0x38)	/*!< EXC_NO_RESERVE0 offset */
#define EXC_VECTOR_RESERVE1		(0x3c)	/*!< EXC_NO_RESERVE1 offset */
/** @} */

/**
 * \name build configuration register
 * @{
 */
#define AUX_BCR_VER			(0x60)	/*!< build configuration register version */
#define AUX_BCR_BTA			(0x63)	/*!< build configuration for BTA LINK */
#define AUX_BCR_VECBASE			(0x68)	/*!< build configuration for interrupt vector base */
#define AUX_BCR_MPU			(0x6d)	/*!< build configuration for memory protection unit */
#define AUX_BCR_RF			(0x6e)	/*!< build configuration for core registers */
#define AUX_BCR_D_CACHE			(0x72)	/*!< build configuration for data cache */
#define AUX_BCR_DCCM			(0x74)	/*!< build configuration for DCCM */
#define AUX_BCR_TIMERS			(0x75)	/*!< build configuration for processor timers */
#define AUX_BCR_AP 			(0x76)	/*!< build configuration for actionpoints */
#define AUX_BCR_I_CACHE			(0x77)	/*!< build configuration for instruction cache */
#define AUX_BCR_ICCM			(0x78)	/*!< build configuration for ICCM */
#define AUX_BCR_DSP			(0x7a)	/*!< build configuration for DSP */
#define AUX_BCR_MUL			(0x7b)	/*!< build configuration for multiply */
#define AUX_BCR_SWAP			(0x7c)	/*!< build configuration for swap */
#define AUX_BCR_NORM			(0x7d)	/*!< build configuration for normalize */
#define AUX_BCR_MIXMAX			(0x7e)	/*!< build configuration for MIN/MAX */
#define AUX_BCR_BARREL			(0x7f)	/*!< build configuration for barrel shift */
#define AUX_BCR_ISA			(0xc1)	/*!< build configuration for ISA configuration */
#define AUX_BCR_STACK			(0xc5)	/*!< build configuration for stack region */
#define AUX_BCR_ERP			(0xc7)	/*!< build configuration for error protection */
#define AUX_BCR_FPU			(0xc8)	/*!< build configuration for floating-point unit */
#define AUX_BCR_CPORT			(0xc9)	/*!< build configuration for code protection */
#define AUX_BCR_BS			(0xcb)	/*!< build configuration for bitstream */
#define AUX_BCR_AGU			(0xcc)	/*!< build configuration for address generate unit */
#define AUX_BCR_DMAC			(0xcd)	/*!< build configuration for DMA */
#define AUX_BCR_CONNECT_SYSTEM		(0xd0)	/*!< build configuration for arc connect */
#define AUX_BCR_CONNECT_SEMA		(0xd1)	/*!< build configuration for inter-core semaphore */
#define AUX_BCR_CONNECT_MESSAGE		(0xd2)	/*!< build configuration for inter-code message */
#define AUX_BCR_CONNECT_PMU		(0xd3)	/*!< build configuration for power management unit */
#define AUX_BCR_CONNECT_GFRC		(0xd6)	/*!< build configuration for global free running counter */
#define AUX_BCR_CAL_STORE		(0xd9)	/*!< build configuration for calibration parameter storage */
#define AUX_BCR_CONNECT_ICI		(0xe0)	/*!< build configuration for inter-core interrupt unit */
#define AUX_BCR_CONNECT_ICD		(0xe1)	/*!< build configuration for inter-core debug unit */
#define AUX_BCR_CONNECT_PDM		(0xe3)	/*!< build configuration for power domain management unit*/
#define AUX_BCR_RTT			(0xf2)	/*!< build configuration for real-time trace */
#define AUX_BCR_IRQ			(0xf3)	/*!< build configuration for interrupt */
#define AUX_BCR_PCT			(0xf5)	/*!< build configuration for performance counters */
#define AUX_BCR_CC			(0xf6)	/*!< build configuration for performance counters */
#define AUX_BCR_PDM_DVFS		(0xf7)	/*!< build configuration for PDM and DVFS */

#define AUX_BCR_SEC_BUILD		(0xdb)

/* from 0xF5 and 0xF6 */

#define AUX_BCR_IFQUEUE			(0xfe)	/*!< build configuration for instruction fetch queue */
#define AUX_BCR_SMART			(0xff)   /*!< build configuration for SmaRT debug feature */
/** @} */


#define	AUX_SEC_STAT			(0x9)
#define AUX_SEC_STAT_BIT_SSC		(0)
#define AUX_SEC_STAT_BIT_NSRT		(1)
#define AUX_SEC_STAT_BIT_NSRU		(2)
#define AUX_SEC_STAT_BIT_IRM		(3)
#define AUX_SEC_STAT_BIT_SUE		(4)
#define AUX_SEC_STAT_BIT_NIC		(5)

/**
 * \name status register STATUS32
 * @{
 */
#define AUX_STATUS32			(0xa)
#define AUX_STATUS32_P0			(0xb)

/* STATUS32 bit-field definition */
#define AUX_STATUS_BIT_AE		(5)	/*!< processor is in an exception */
#define AUX_STATUS_BIT_DE		(6)	/*!< delayed branch is pending */
#define AUX_STATUS_BIT_U		(7)	/*!< user mode */
#define AUX_STATUS_BIT_L		(12)	/*!< zero-overhead loop enable */
#define AUX_STATUS_BIT_IE		(31)	/*!< interrupt enable */

/* masks correspond to STATUS32 bit-field */
#define AUX_STATUS_MASK_AE		(1<<AUX_STATUS_BIT_AE)	/*!< mask of AUX_STATUS_BIT_AE */
#define AUX_STATUS_MASK_DE		(1<<AUX_STATUS_BIT_DE)	/*!< mask of AUX_STATUS_BIT_DE */
#define AUX_STATUS_MASK_U		(1<<AUX_STATUS_BIT_U)	/*!< mask of AUX_STATUS_BIT_U */
#define AUX_STATUS_MASK_L		(1<<AUX_STATUS_BIT_L)	/*!< mask of AUX_STATUS_BIT_L */
#define AUX_STATUS_MASK_IE		(1<<AUX_STATUS_BIT_IE)	/*!< mask of AUX_STATUS_BIT_IE */
/** @} */

/**
 * \name zero overhead loop auxiliary register
 * @{
 */
#define AUX_LP_START			(0x2) 	/*!< loop start address (32-bit) */
#define AUX_LP_END			(0x3) 	/*!< loop end address (32-bit) */
/** @} */

#define AUX_USER_SP			(0xd)	/*!< user-mode stack pointer */
/* added in silverstone */
#define AUX_KERNEL_SP			(0x38)	/*!< kernel-mode stack pointer */
#define AUX_SEC_U_SP			(0x39)	/*!< secure user-mode stack pointer */
#define AUX_SEC_K_SP			(0x3a)	/*!< secure kernel-mode stack pointer */

/* additional stack checkingh registers for secure mode */
#define AUX_S_USTACK_BASE		(0x263)
#define AUX_S_USTACK_TOP		(0x262)

#define AUX_S_KSTACK_BASE		(0x267)
#define AUX_S_KSTACK_TOP		(0x266)

/**
 * \name auxiliary register for hardware counter 0 and 1
 * @{
 */
#define AUX_TIMER0_LIMIT		(0x23)	/*!< timer 0 limit value */
#define AUX_TIMER0_CTRL			(0x22)	/*!< timer 0 control value */
#define AUX_TIMER0_CNT			(0x21)	/*!< timer 0 count value */
#define AUX_TIMER1_LIMIT		(0x102)	/*!< timer 1 limit value */
#define AUX_TIMER1_CTRL			(0x101)	/*!< timer 1 control value */
#define AUX_TIMER1_CNT			(0x100)	/*!< timer 1 count value */
/** @} */

#define AUX_SECURE_TIMER0_CNT		(0x106) /*!< secure timer 0 count value */
#define AUX_SECURE_TIMER0_CTRL		(0x107) /*!< secure timer 0 control value */
#define AUX_SECURE_TIMER0_LIMIT		(0x108) /*!< secure timer 0 limit value */
#define AUX_SECURE_TIMER1_CNT		(0x109) /*!< secure timer 1 count value */
#define AUX_SECURE_TIMER1_CTRL		(0x10a) /*!< secure timer 1 control value */
#define AUX_SECURE_TIMER1_LIMIT		(0x10b) /*!< secure timer 1 limit value */


/**
 * \name auxiliary register for real-time counter
 * @{
 */
#define AUX_RTC_CTRL			(0x103)	/*!< real-time counter control register */
#define AUX_RTC_LOW			(0x104)	/*!< real-time counter count low register */
#define AUX_RTC_HIGH			(0x105)	/*!< real-time counter count high register */
/** @} */

/**
 * \name indexed table auxiliary register
 * @{
 */
#define AUX_JLI_BASE			(0x290)	/*!< jump and link indexed base address */
#define AUX_LDI_BASE			(0x291)	/*!< load indexed base address */
#define AUX_EI_BASE			(0x292)	/*!< execute indexed base address */
/** @} */

/**
 * \name baseline auxiliary register set
 * @{
 */
/* to be added */
#define AUX_ERRET			(0x400)	/*!< exception return address */
#define AUX_ERBTA			(0x401)	/*!< BTA saved on exception entry */
#define AUX_ERSTATUS			(0x402)	/*!< STATUS32 saved on exception */
#define AUX_ECR				(0x403)	/*!< exception cause register */
#define AUX_EFA				(0x404) /*!< exception fault address */
#define AUX_BTA				(0x412)	/*!< branch target address */
/** @} */

/* New register to control which exceptions can be handled in NS mode */
#define AUX_ERSEC_STAT			(0x406)
#define AUX_ERSEC_STAT_BIT_ERM		31
#define AUX_SEC_EXCEPT			(0x407)

/**
 * \name MPU register set
 * @{
 */
#define AUX_MPU_EN      		(0x409)	/*!< MPU enable register  */
#define AUX_MPU_ECR			(0x420)	/*!< MPU exception cause */
#define AUX_MPU_RDB0    		(0x422)	/*!< MPU region descriptor base 0 */
#define AUX_MPU_RDP0    		(0x423)	/*!< MPU region descriptor permission 0 */

/* MPU register set in silverstone */
#define AUX_MPU_INDEX			(0x448)
#define AUX_MPU_INDEX_BIT_D		(31)
#define AUX_MPU_RSTART			(0x449)
#define AUX_MPU_REND			(0x44a)
#define AUX_MPU_RPER			(0x44b)
#define AUX_MPU_RPER_BIT_S		(15)
#define AUX_MPU_PROBE			(0x44c)
#define AUX_MPU_ECR			(0x420)

#define AUX_NSC_TABLE_BASE		(0x269)
#define AUX_NSC_TABLE_TOP		(0x268)

/** @} */

/**
 * \name exception cause register (ECR) bit-field definition
 * @{
 */
#define AUX_ECR_VEC_MASK		(0xff0000)	/*!< [23:16] = exception vector */
#define AUX_ECR_CODE_MASK		(0x00ff00)	/*!< [15: 8] = exception cause code */
#define AUX_ECR_PARAM_MASK		(0x0000ff)	/*!< [ 7: 0] = exception parameters */
/** @} */

/**
 * \name exception vector number and cause code
 * @{
 */
#define AUX_ECR_V_INSN_ERR		(0x02)	/*!< vector number of illegal instruction */
#define AUX_ECR_V_MACH_CHK		(0x03)	/*!< vector number of machine check */
#define AUX_ECR_V_ITLB_MISS		(0x04)	/*!< vector number of instruction TLB missing exception */
#define AUX_ECR_V_DTLB_MISS		(0x05)	/*!< vector number of data TLB missing exception */
#define AUX_ECR_V_PROTV			(0x06)	/*!< vector number of protection violation */
#define AUX_ECR_V_TRAP			(0x09)	/*!< vector number of trap */
#define AUX_ECR_V_MISALIG_DATA 		(0x0d)	/*!< vector number of misaligned data access */

#define AUX_ECR_C_PROTV_INST_FETCH	(0x00)	/*!< cause code of instruction fetch (protection violation) */
#define AUX_ECR_C_PROTV_LOAD		(0x01)	/*!< cause code related memory read (protection violation) */
#define AUX_ECR_C_PROTV_STORE		(0x02)	/*!< cause code related memory write (protection violation) */
#define AUX_ECR_C_PROTV_XCHG		(0x03)	/*!< cause code related read-modify-write (protection violation) */

#define AUX_ECR_C_MCHK_DUP_TLB		(0x01)	/*!< \todo definition is to be added. */

#define AUX_ECR_C_BIT_DTLB_LD_MISS	(8)	/*!< \todo definition is to be added. */
#define AUX_ECR_C_BIT_DTLB_ST_MISS	(9)	/*!< \todo definition is to be added. */
/** @} */

/**
 * \name interrupt related auxiliary register
 * @{
 */
#define AUX_IRQ_CTRL			(0xe)	/*!< interrupt context saving control register */
#define AUX_INT_VECT_BASE		(0x25)	/*!< interrupt vector base register */
#define AUX_INT_VECT_BASE_S		(0x26)	/*!< secure interrupt vector based register */
#define AUX_IRQ_ACT			(0x43)	/*!< active interrupts register */
#define AUX_IRQ_CAUSE			(0x40a)	/*!< interrupt cause register */
#define AUX_IRQ_SELECT			(0x40b)	/*!< interrupt select register */
#define AUX_IRQ_PRIORITY		(0x206)	/*!< interrupt priority register */
#define AUX_IRQ_PRIORITY_BIT_S		(0x8)	/*!< S bit offset in interrupt priority register */
#define AUX_IRQ_ENABLE			(0x40c)	/*!< interrupt enable register */
#define AUX_IRQ_TRIGGER			(0x40d)	/*!< interrupt trigger: level or pulse */
#define AUX_IRQ_PENDING			(0x416)	/*!< interrupt pending register */
#define AUX_IRQ_PLUSE_CLR		(0x415)	/*!< interrupt pulse cancel register */
#define AUX_IRQ_STATUS			(0x40f)	/*!< interrupt status register */
#define AUX_IRQ_PRI_PENDING		(0x200)	/*!< interrupt priority pending register */
#define AUX_IRQ_HINT			(0x201)	/*!< software interrupt trigger */
/** @} */

/**
 * \name cache related auxiliary register
 * @{
 */
#define AUX_IC_IVIC			(0x10)	/*!< invalidate instruction cache */
#define AUX_IC_CTRL			(0x11)	/*!< instruction cache control register */
#define AUX_IC_LIL			(0x13)	/*!< lock instruction cache line */
#define AUX_IC_IVIL			(0x19)	/*!< invalidate instruction cache line */
#define AUX_IC_RAM_ADDR			(0x1a)	/*!< instruction cache external access address */
#define AUX_IC_TAG			(0x1b)	/*!< instruction cache tag access */
#define AUX_IC_DATA			(0x1d)	/*!< instruction cache data access */
#define AUX_DC_IVDC			(0x47)	/*!< invalidate data cache */
#define AUX_DC_CTRL			(0x48)	/*!< data cache control register */
#define AUX_DC_LDL			(0x49)	/*!< lock data cache line */
#define AUX_DC_IVDL			(0x4a)	/*!< invalidate data cache line */
#define AUX_DC_FLSH			(0x4b)	/*!< flush data cache */
#define AUX_DC_FLDL			(0x4c)	/*!< flush data line */
#define AUX_DC_RAM_ADDR			(0x58)	/*!< data cache external access address */
#define AUX_DC_TAG			(0x59)	/*!< data cache tag access */
#define AUX_DC_DATA			(0x5b)	/*!< data cache data access */
/** @} */

/**
 * \name dmac related auxiliary register
 * @{
 */
#define AUX_DMACTRL			(0x680)	/*!< DMA control register */
#define AUX_DMACENB			(0x681)	/*!< DMA channel enable register */
#define AUX_DMACDSB			(0x682)	/*!< DMA channel disable register */
#define AUX_DMACHPRI			(0x683)	/*!< DMA channel high priority level register */
#define AUX_DMACNPRI			(0x684)	/*!< DMA channel normal priority level register */
#define AUX_DMACREQ			(0x685)	/*!< DMA channel transfer request register */
#define AUX_DMACSTAT0			(0x686)	/*!< DMA channel status register 0 */
#define AUX_DMACSTAT1			(0x687)	/*!< DMA channel status register 1 */
#define AUX_DMACIRQ			(0x688)	/*!< DMA channel interrupt request status/clear register */
#define AUX_DMACBASE			(0x689)	/*!< DMA channel structure register base address */
#define AUX_DMACRST			(0x68A)	/*!< DMA channel reset register base address */

#define AUX_DMACTRL0			(0x690)	/*!< DMA channel 0 control register when mapped in aux */
#define AUX_DMASAR0			(0x691)	/*!< DMA channel 0 source address register when mapped in aux */
#define AUX_DMADAR0			(0x692)	/*!< DMA channel 0 destination register when mapped in aux */
#define AUX_DMACTRLx			(AUX_DMACTRL0)	/*!< DMA channel 0 control register when mapped in aux */
#define AUX_DMASARx			(AUX_DMASAR0)	/*!< DMA channel 0 source address register when mapped in aux */
#define AUX_DMADARx			(AUX_DMADAR0)	/*!< DMA channel 0 destination register when mapped in aux */
/** @} */



/**
 * \name other auxiliary register
 * @{
 */
#define AUX_IDENTITY			(0x4) 	/*!< identity register */
#define AUX_DMP_PERIPHERAL		(0x20a) /*!< peripheral memory region */
#define AUX_XFLAGS			(0x44f) /*!< user extension flags register */
#define AUX_MCIP_CMD			(0x600) /*!< \todo definition is to be added. */
#define AUX_MCIP_WDATA			(0x601) /*!< \todo definition is to be added. */
#define AUX_MCIP_READBACK		(0x602) /*!< \todo definition is to be added. */
#define AUX_SMART_CONTROL		(0x700) /*!< \todo definition is to be added. */
#define AUX_SMART_DATA			(0x701) /*!< \todo definition is to be added. */

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLY__
/* add type definition and function declaration here */
#endif	/* assembly */

#ifdef __cplusplus
}
#endif


#endif	/* _ARC_HAL_CORE_H_ */

 /**  @} */
