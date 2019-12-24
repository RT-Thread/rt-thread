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
 * \date 2016-09-08
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup ARC_HAL_MISC
 * \brief header file for arc feature configuration
 */

/**
 * \addtogroup ARC_HAL_MISC
 * @{
 */

#ifndef _ARC_FEATURE_CONFIG_H_
#define _ARC_FEATURE_CONFIG_H_

// Enable core_config.h in EMSK OSP
//#ifdef EMBARC_TCF_GENERATED
#include "arc_core_config.h"
//#endif

/** ARC baseline instruction set version number */
#if !defined(_ARCVER)
#if defined(core_config_cir_identity_arcver)
#define _ARCVER				core_config_cir_identity_arcver
#else
#define _ARCVER				0x42
#endif
#endif

/** ARC CPU Clock Frequency in Hz unit */
#if !defined(ARC_FEATURE_CPU_CLOCK_FREQ)
#if defined(core_config_clock_speed)
#define ARC_FEATURE_CPU_CLOCK_FREQ	(core_config_clock_speed*1000000)
#endif
#endif

/** ARC PC size */
#if !defined(ARC_FEATURE_PC_SIZE)
#if defined(core_config_pc_size)
#define ARC_FEATURE_PC_SIZE		core_config_pc_size
#else
#define ARC_FEATURE_PC_SIZE		32
#endif
#endif

/** ARC LPC size */
#if !defined(ARC_FEATURE_LPC_SIZE)
#if defined(core_config_lpc_size)
#define ARC_FEATURE_LPC_SIZE		core_config_lpc_size
#else
#define ARC_FEATURE_LPC_SIZE		32
#endif
#endif

/** ARC Addr size */
#if !defined(ARC_FEATURE_ADDR_SIZE)
#if defined(core_config_addr_size)
#define ARC_FEATURE_ADDR_SIZE		core_config_addr_size
#else
#define ARC_FEATURE_ADDR_SIZE		32
#endif
#endif

/** ARC Endian/Byte Order */
#define ARC_FEATURE_LITTLE_ENDIAN	1234
#define ARC_FEATURE_BIG_ENDIAN		4321

#if !defined(ARC_FEATURE_BYTE_ORDER)
#if defined(core_config_bcr_isa_config_b)
#if core_config_bcr_isa_config_b == 0
#define ARC_FEATURE_BYTE_ORDER		ARC_FEATURE_LITTLE_ENDIAN
#else
#define ARC_FEATURE_BYTE_ORDER		ARC_FEATURE_BIG_ENDIAN
#endif
#else
#define ARC_FEATURE_BYTE_ORDER		ARC_FEATURE_LITTLE_ENDIAN
#endif
#endif

/** Reduced register option, if enabled, ARC_FEATURE_RF16 will be defined */
#if !defined(ARC_FEATURE_RF16)
#if defined(core_config_bcr_rf_build_e) && core_config_bcr_rf_build_e == 1
#define ARC_FEATURE_RF16
#endif
#endif

/** Unaligned access option, if enabled, ARC_FEATURE_UNALIGNED will be defined */
#if !defined(ARC_FEATURE_UNALIGNED)
#if defined(core_config_unaligned) && core_config_unaligned == 1
#define ARC_FEATURE_UNALIGNED
#endif
#endif


/** Code density option, if enabled, ARC_FEATURE_CODE_DENSITY will be defined */
#if !defined(ARC_FEATURE_CODE_DENSITY)
#if defined(core_config_code_density) && core_config_code_density == 1
#define ARC_FEATURE_CODE_DENSITY
#endif
#endif

/** The number of register file banks */
#if !defined(ARC_FEATURE_RGF_NUM_BANKS)
#if defined(core_config_rgf_num_banks)
#define ARC_FEATURE_RGF_NUM_BANKS	core_config_rgf_num_banks
#else
#define ARC_FEATURE_RGF_NUM_BANKS	1
#endif
#endif

/** The number of registers replicated per register bank */
#if !defined(ARC_FEATURE_RGF_BANKED_REGS)
#if defined(core_config_rgf_banked_regs)
#define ARC_FEATURE_RGF_BANKED_REGS	core_config_rgf_banked_regs
#endif
#endif

/** Interrupt unit presence */
#if !defined(ARC_FEATURE_INTERRUPTS_PRESENT)
#if defined(core_config_interrupts_present)
#define ARC_FEATURE_INTERRUPTS_PRESENT	core_config_interrupts_present
#endif
#endif

/** FIRQ_OPTION configuration option, 1 for enabled, 0 for disabled */
#if !defined(ARC_FEATURE_FIRQ)
#if defined(core_config_bcr_irq_build_f)
#define ARC_FEATURE_FIRQ		core_config_bcr_irq_build_f
#else
#define ARC_FEATURE_FIRQ		0
#endif
#endif

/** The number of interrupts */
#if !defined(NUM_EXC_INT)
#if defined(core_config_interrupts_number)
#define NUM_EXC_INT			core_config_interrupts_number
#endif
#endif

/** The number of external interrupts */
#if !defined(NUM_EXC_EXT_INT)
#if defined(core_config_interrupts_externals)
#define NUM_EXC_EXT_INT			core_config_interrupts_externals
#endif
#endif

/** The interrupt priority levels */
#if !defined(INT_PRI_MIN)
#if defined(core_config_interrupts_priorities)
#define INT_PRI_MIN			(-core_config_interrupts_priorities)
#endif
#endif

// ARC TIMER_BUILD
/** Timer0 present or not */
#if !defined(ARC_FEATURE_TIMER0_PRESENT)
#if defined(core_config_timer0)
#define ARC_FEATURE_TIMER0_PRESENT	core_config_timer0
#define ARC_FEATURE_TIMER0_LEVEL	(core_config_timer0_level-core_config_interrupts_priorities)
#define ARC_FEATURE_TIMER0_VECTOR	core_config_timer0_vector
#endif
#endif

/** Timer1 present or not */
#if !defined(ARC_FEATURE_TIMER1_PRESENT)
#if defined(core_config_timer1)
#define ARC_FEATURE_TIMER1_PRESENT	core_config_timer1
#define ARC_FEATURE_TIMER1_LEVEL	(core_config_timer1_level-core_config_interrupts_priorities)
#define ARC_FEATURE_TIMER1_VECTOR	core_config_timer1_vector
#endif
#endif

/** Secure Timer0 present or not */
#if !defined(ARC_FEATURE_SEC_TIMER0_PRESENT)
#if defined(core_config_sec_timer0)
#define ARC_FEATURE_SEC_TIMER0_PRESENT	core_config_sec_timer0
#define ARC_FEATURE_SEC_TIMER0_LEVEL	(core_config_sec_timer0_level-core_config_interrupts_priorities)
#define ARC_FEATURE_SEC_TIMER0_VECTOR	20
#endif
#endif

/** Secure Timer1 present or not */
#if !defined(ARC_FEATURE_SEC_TIMER1_PRESENT)
#if defined(core_config_sec_timer1)
#define ARC_FEATURE_SEC_TIMER1_PRESENT	core_config_sec_timer1
#define ARC_FEATURE_SEC_TIMER1_LEVEL	(core_config_sec_timer1_level-core_config_interrupts_priorities)
#define ARC_FEATURE_SEC_TIMER1_VECTOR	21
#endif
#endif


/** 64bit RTC present or not */
#if !defined(ARC_FEATURE_RTC_PRESENT)
#if defined(core_config_rtc)
#define ARC_FEATURE_RTC_PRESENT		core_config_rtc
#endif
#endif

// Memory related definitions
/** ICCM Presence, base address and size */
#if !defined(ARC_FEATURE_ICCM_PRESENT)
#if defined(core_config_iccm_present) && core_config_iccm_present == 1
#define ARC_FEATURE_ICCM_PRESENT	1
#define ARC_FEATURE_ICCM_BASE		core_config_iccm_base
#define ARC_FEATURE_ICCM_SIZE		core_config_iccm_size
#endif
#endif

/** ICCM0 Presence, base address and size */
#if !defined(ARC_FEATURE_ICCM0_PRESENT)
#if defined(core_config_iccm0_present) && core_config_iccm0_present == 1
#define ARC_FEATURE_ICCM0_PRESENT	1
#define ARC_FEATURE_ICCM0_BASE		core_config_iccm0_base
#define ARC_FEATURE_ICCM0_SIZE		core_config_iccm0_size
#endif
#endif

/** ICCM1 Presence, base address and size */
#if !defined(ARC_FEATURE_ICCM1_PRESENT)
#if defined(core_config_iccm1_present) && core_config_iccm1_present == 1
#define ARC_FEATURE_ICCM1_PRESENT	1
#define ARC_FEATURE_ICCM1_BASE		core_config_iccm1_base
#define ARC_FEATURE_ICCM1_SIZE		core_config_iccm1_size
#endif
#endif

/** DCCM Presence, base address and size */
#if !defined(ARC_FEATURE_DCCM_PRESENT)
#if defined(core_config_dccm_present) && core_config_dccm_present == 1
#define ARC_FEATURE_DCCM_PRESENT	1
#define ARC_FEATURE_DCCM_BASE		core_config_dccm_base
#define ARC_FEATURE_DCCM_SIZE		core_config_dccm_size
#ifdef core_config_dccm_interleave
#define ARC_FEATURE_DCCM_INTERLEAVE	core_config_dccm_interleave
#endif
#endif
#endif

/** Peripheral memory region(DMP) base address, if dmp configured, this macro will be defined as base address */
#if !defined(ARC_FEATURE_DMP_PERIPHERAL)
#if defined(core_config_cir_dmp_peripheral)
#define ARC_FEATURE_DMP_PERIPHERAL	core_config_cir_dmp_peripheral
#endif
#endif

/** MPU options */
#if !defined(ARC_FEATURE_MPU_PRESENT)
#if defined(core_config_mpu_present) && core_config_mpu_present == 1
#define ARC_FEATURE_MPU_PRESENT		1
#define ARC_FEATURE_MPU_VERSION		core_config_bcr_mpu_build_version
#define ARC_FEATURE_MPU_REGIONS		core_config_mpu_regions
#ifdef core_config_bcr_mpu_build_i
#define ARC_FEATURE_MPU_BUILD_I		core_config_bcr_mpu_build_i
#endif
#ifdef core_config_bcr_mpu_build_s
#define ARC_FEATURE_MPU_BUILD_S		core_config_bcr_mpu_build_s
#endif
#endif
#endif

/** Secure BCR SEC_BUILD BCR */
#if !defined(ARC_FEATURE_SEC_PRESENT)
#if defined(core_config_bcr_sec_build)
#define ARC_FEATURE_SEC_PRESENT		1
#define ARC_FEATURE_SEC_VERSION		core_config_bcr_sec_build_version
#define	ARC_FEATURE_SEC_BUILD_DSM	core_config_bcr_sec_build_dsm
#define	ARC_FEATURE_SEC_BUILD_NSM	core_config_bcr_sec_build_nsm
#define	ARC_FEATURE_SEC_BUILD_I1SM	core_config_bcr_sec_build_i1sm
#define	ARC_FEATURE_SEC_BUILD_I0SM	core_config_bcr_sec_build_i0sm
#define	ARC_FEATURE_SEC_BUILD_S		core_config_bcr_sec_build_s
#define	ARC_FEATURE_SEC_BUILD_EI	core_config_bcr_sec_build_ei
#define	ARC_FEATURE_SEC_BUILD_ED	core_config_bcr_sec_build_ed
#endif
#endif

#if !defined(ARC_FEATURE_SEC_MODES)
#if defined(core_config_sec_modes)
#define ARC_FEATURE_SEC_MODES		core_config_sec_modes
#endif
#endif

/** Data Cache options */
#if !defined(ARC_FEATURE_DCACHE_PRESENT)
#if defined(core_config_dcache_present) && core_config_dcache_present == 1
#define ARC_FEATURE_DCACHE_PRESENT		1
#define ARC_FEATURE_DCACHE_BUILD		core_config_bcr_d_cache_build
#define ARC_FEATURE_DCACHE_BUILD_VERSION	core_config_bcr_d_cache_build_version
#define ARC_FEATURE_DCACHE_BUILD_ASSOC		core_config_bcr_d_cache_build_assoc
#define ARC_FEATURE_DCACHE_BUILD_CAPACITY	core_config_bcr_d_cache_build_capacity
#define ARC_FEATURE_DCACHE_BUILD_BSIZE		core_config_bcr_d_cache_build_bsize
#define ARC_FEATURE_DCACHE_BUILD_FL		core_config_bcr_d_cache_build_fl
#define ARC_FEATURE_DCACHE_BUILD_U		core_config_bcr_d_cache_build_u
#define ARC_FEATURE_DCACHE_SIZE			core_config_dcache_size
#define ARC_FEATURE_DCACHE_LINE_SIZE		core_config_dcache_line_size
#define ARC_FEATURE_DCACHE_WAYS			core_config_dcache_ways
#define ARC_FEATURE_DCACHE_FEATURE		core_config_dcache_feature
#endif
#endif

/** Instruction Cache options */
#if !defined(ARC_FEATURE_ICACHE_PRESENT)
#if defined(core_config_icache_present) && core_config_icache_present == 1
#define ARC_FEATURE_ICACHE_PRESENT		1
#define ARC_FEATURE_ICACHE_BUILD		core_config_bcr_i_cache_build
#define ARC_FEATURE_ICACHE_BUILD_VERSION	core_config_bcr_i_cache_build_version
#define ARC_FEATURE_ICACHE_BUILD_ASSOC		core_config_bcr_i_cache_build_assoc
#define ARC_FEATURE_ICACHE_BUILD_CAPACITY	core_config_bcr_i_cache_build_capacity
#define ARC_FEATURE_ICACHE_BUILD_BSIZE		core_config_bcr_i_cache_build_bsize
#define ARC_FEATURE_ICACHE_BUILD_FL		core_config_bcr_i_cache_build_fl
#define ARC_FEATURE_ICACHE_BUILD_D		core_config_bcr_i_cache_build_d
#define ARC_FEATURE_ICACHE_SIZE			core_config_icache_size
#define ARC_FEATURE_ICACHE_LINE_SIZE		core_config_icache_line_size
#define ARC_FEATURE_ICACHE_WAYS			core_config_icache_ways
#define ARC_FEATURE_ICACHE_FEATURE		core_config_icache_feature
#endif
#endif

/** ARC uDMA options */
#if !defined(ARC_FEATURE_DMAC)
#if defined(core_config_dmac)
#define ARC_FEATURE_DMAC		core_config_dmac
#define CORE_DMAC_CHANNELS		core_config_dmac_channels
#define CORE_DMAC_REGISTERS		core_config_dmac_registers
#if core_config_bcr_dmac_build_int_cfg == 2 && core_config_bcr_dmac_build_int_cfg == 4
#define DMA_MULTI_IRQ			1
#else
#define DMA_MULTI_IRQ			0
#endif
#define ARC_FEATURE_DMAC_PRESENT	core_config_dmac
#define ARC_FEATURE_DMAC_VERSION	core_config_bcr_dmac_build_version
#define ARC_FEATURE_DMAC_CHANNELS	core_config_dmac_channels
#define ARC_FEATURE_DMAC_REGISTERS	core_config_dmac_registers
#define ARC_FEATURE_DMAC_INT_CFG	core_config_bcr_dmac_build_int_cfg
#define ARC_FEATURE_DMAC_FIFO_DEPTH	core_config_dmac_fifo_depth

#ifdef ARC_FEATURE_SEC_TIMER0_PRESENT
#define DMA_IRQ_NUM_START		22
#define ARC_FEATURE_DMAC_VECTOR_START	22
#else
#define DMA_IRQ_NUM_START		20
#define ARC_FEATURE_DMAC_VECTOR_START	20
#endif

#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef ARC_FEATURE_UNALIGNED
#define STATUS32_RESET_VALUE		(1<<19)
#else
#define STATUS32_RESET_VALUE		(0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _ARC_FEATURE_CONFIG_H_ */

/** @} */
