/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_PLATFORM_H__
#define __SBI_PLATFORM_H__

/**
 * OpenSBI 32-bit platform version with:
 * 1. upper 16-bits as major number
 * 2. lower 16-bits as minor number
 */
#define SBI_PLATFORM_VERSION(Major, Minor) ((Major << 16) | Minor)

/** Offset of opensbi_version in struct sbi_platform */
#define SBI_PLATFORM_OPENSBI_VERSION_OFFSET (0x00)
/** Offset of platform_version in struct sbi_platform */
#define SBI_PLATFORM_VERSION_OFFSET (0x04)
/** Offset of name in struct sbi_platform */
#define SBI_PLATFORM_NAME_OFFSET (0x08)
/** Offset of features in struct sbi_platform */
#define SBI_PLATFORM_FEATURES_OFFSET (0x48)
/** Offset of hart_count in struct sbi_platform */
#define SBI_PLATFORM_HART_COUNT_OFFSET (0x50)
/** Offset of hart_stack_size in struct sbi_platform */
#define SBI_PLATFORM_HART_STACK_SIZE_OFFSET (0x54)
/** Offset of platform_ops_addr in struct sbi_platform */
#define SBI_PLATFORM_OPS_OFFSET (0x58)
/** Offset of firmware_context in struct sbi_platform */
#define SBI_PLATFORM_FIRMWARE_CONTEXT_OFFSET (0x58 + __SIZEOF_POINTER__)
/** Offset of hart_index2id in struct sbi_platform */
#define SBI_PLATFORM_HART_INDEX2ID_OFFSET (0x58 + (__SIZEOF_POINTER__ * 2))

#define SBI_PLATFORM_TLB_RANGE_FLUSH_LIMIT_DEFAULT		(1UL << 12)

#ifndef __ASSEMBLER__

#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_scratch.h>
#include <sbi/sbi_version.h>

struct sbi_domain_memregion;
struct sbi_trap_info;
struct sbi_trap_regs;

/** Possible feature flags of a platform */
enum sbi_platform_features {
	/** Platform has fault delegation support */
	SBI_PLATFORM_HAS_MFAULTS_DELEGATION = (1 << 1),

	/** Last index of Platform features*/
	SBI_PLATFORM_HAS_LAST_FEATURE = SBI_PLATFORM_HAS_MFAULTS_DELEGATION,
};

/** Default feature set for a platform */
#define SBI_PLATFORM_DEFAULT_FEATURES                                \
	(SBI_PLATFORM_HAS_MFAULTS_DELEGATION)

/** Platform functions */
struct sbi_platform_operations {
	/** Platform early initialization */
	int (*early_init)(bool cold_boot);
	/** Platform final initialization */
	int (*final_init)(bool cold_boot);

	/** Platform early exit */
	void (*early_exit)(void);
	/** Platform final exit */
	void (*final_exit)(void);

	/**
	 * For platforms that do not implement misa, non-standard
	 * methods are needed to determine cpu extension.
	 */
	int (*misa_check_extension)(char ext);

	/**
	 * For platforms that do not implement misa, non-standard
	 * methods are needed to get MXL field of misa.
	 */
	int (*misa_get_xlen)(void);

	/** Initialize (or populate) domains for the platform */
	int (*domains_init)(void);

	/** Initialize the platform console */
	int (*console_init)(void);

	/** Initialize the platform interrupt controller for current HART */
	int (*irqchip_init)(bool cold_boot);
	/** Exit the platform interrupt controller for current HART */
	void (*irqchip_exit)(void);

	/** Initialize IPI for current HART */
	int (*ipi_init)(bool cold_boot);
	/** Exit IPI for current HART */
	void (*ipi_exit)(void);

	/** Get tlb flush limit value **/
	u64 (*get_tlbr_flush_limit)(void);

	/** Initialize platform timer for current HART */
	int (*timer_init)(bool cold_boot);
	/** Exit platform timer for current HART */
	void (*timer_exit)(void);

	/** platform specific SBI extension implementation probe function */
	int (*vendor_ext_check)(long extid);
	/** platform specific SBI extension implementation provider */
	int (*vendor_ext_provider)(long extid, long funcid,
				   const struct sbi_trap_regs *regs,
				   unsigned long *out_value,
				   struct sbi_trap_info *out_trap);
};

/** Platform default per-HART stack size for exception/interrupt handling */
#define SBI_PLATFORM_DEFAULT_HART_STACK_SIZE	8192

/** Representation of a platform */
struct sbi_platform {
	/**
	 * OpenSBI version this sbi_platform is based on.
	 * It's a 32-bit value where upper 16-bits are major number
	 * and lower 16-bits are minor number
	 */
	u32 opensbi_version;
	/**
	 * OpenSBI platform version released by vendor.
	 * It's a 32-bit value where upper 16-bits are major number
	 * and lower 16-bits are minor number
	 */
	u32 platform_version;
	/** Name of the platform */
	char name[64];
	/** Supported features */
	u64 features;
	/** Total number of HARTs */
	u32 hart_count;
	/** Per-HART stack size for exception/interrupt handling */
	u32 hart_stack_size;
	/** Pointer to sbi platform operations */
	unsigned long platform_ops_addr;
	/** Pointer to system firmware specific context */
	unsigned long firmware_context;
	/**
	 * HART index to HART id table
	 *
	 * For used HART index <abc>:
	 *     hart_index2id[<abc>] = some HART id
	 * For unused HART index <abc>:
	 *     hart_index2id[<abc>] = -1U
	 *
	 * If hart_index2id == NULL then we assume identity mapping
	 *     hart_index2id[<abc>] = <abc>
	 *
	 * We have only two restrictions:
	 * 1. HART index < sbi_platform hart_count
	 * 2. HART id < SBI_HARTMASK_MAX_BITS
	 */
	const u32 *hart_index2id;
};

/** Get pointer to sbi_platform for sbi_scratch pointer */
#define sbi_platform_ptr(__s) \
	((const struct sbi_platform *)((__s)->platform_addr))
/** Get pointer to sbi_platform for current HART */
#define sbi_platform_thishart_ptr() ((const struct sbi_platform *) \
	(sbi_scratch_thishart_ptr()->platform_addr))
/** Get pointer to platform_ops_addr from platform pointer **/
#define sbi_platform_ops(__p) \
	((const struct sbi_platform_operations *)(__p)->platform_ops_addr)

/** Check whether the platform supports fault delegation */
#define sbi_platform_has_mfaults_delegation(__p) \
	((__p)->features & SBI_PLATFORM_HAS_MFAULTS_DELEGATION)

/**
 * Get HART index for the given HART
 *
 * @param plat pointer to struct sbi_platform
 * @param hartid HART ID
 *
 * @return 0 <= value < hart_count for valid HART otherwise -1U
 */
u32 sbi_platform_hart_index(const struct sbi_platform *plat, u32 hartid);

/**
 * Get the platform features in string format
 *
 * @param plat pointer to struct sbi_platform
 * @param features_str pointer to a char array where the features string will be
 *		       updated
 * @param nfstr length of the features_str. The feature string will be truncated
 *		if nfstr is not long enough.
 */
void sbi_platform_get_features_str(const struct sbi_platform *plat,
				   char *features_str, int nfstr);

/**
 * Get name of the platform
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return pointer to platform name on success and "Unknown" on failure
 */
static inline const char *sbi_platform_name(const struct sbi_platform *plat)
{
	if (plat)
		return plat->name;
	return "Unknown";
}

/**
 * Get the platform features
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return the features value currently set for the given platform
 */
static inline unsigned long sbi_platform_get_features(
						const struct sbi_platform *plat)
{
	if (plat)
		return plat->features;
	return 0;
}

/**
 * Get platform specific tlb range flush maximum value. Any request with size
 * higher than this is upgraded to a full flush.
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return tlb range flush limit value. Returns a default (page size) if not
 * defined by platform.
 */
static inline u64 sbi_platform_tlbr_flush_limit(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->get_tlbr_flush_limit)
		return sbi_platform_ops(plat)->get_tlbr_flush_limit();
	return SBI_PLATFORM_TLB_RANGE_FLUSH_LIMIT_DEFAULT;
}

/**
 * Get total number of HARTs supported by the platform
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return total number of HARTs
 */
static inline u32 sbi_platform_hart_count(const struct sbi_platform *plat)
{
	if (plat)
		return plat->hart_count;
	return 0;
}

/**
 * Get per-HART stack size for exception/interrupt handling
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return stack size in bytes
 */
static inline u32 sbi_platform_hart_stack_size(const struct sbi_platform *plat)
{
	if (plat)
		return plat->hart_stack_size;
	return 0;
}

/**
 * Check whether given HART is invalid
 *
 * @param plat pointer to struct sbi_platform
 * @param hartid HART ID
 *
 * @return TRUE if HART is invalid and FALSE otherwise
 */
static inline bool sbi_platform_hart_invalid(const struct sbi_platform *plat,
					     u32 hartid)
{
	if (!plat)
		return TRUE;
	if (plat->hart_count <= sbi_platform_hart_index(plat, hartid))
		return TRUE;
	return FALSE;
}

/**
 * Early initialization for current HART
 *
 * @param plat pointer to struct sbi_platform
 * @param cold_boot whether cold boot (TRUE) or warm_boot (FALSE)
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_early_init(const struct sbi_platform *plat,
					  bool cold_boot)
{
	if (plat && sbi_platform_ops(plat)->early_init)
		return sbi_platform_ops(plat)->early_init(cold_boot);
	return 0;
}

/**
 * Final initialization for current HART
 *
 * @param plat pointer to struct sbi_platform
 * @param cold_boot whether cold boot (TRUE) or warm_boot (FALSE)
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_final_init(const struct sbi_platform *plat,
					  bool cold_boot)
{
	if (plat && sbi_platform_ops(plat)->final_init)
		return sbi_platform_ops(plat)->final_init(cold_boot);
	return 0;
}

/**
 * Early exit for current HART
 *
 * @param plat pointer to struct sbi_platform
 */
static inline void sbi_platform_early_exit(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->early_exit)
		sbi_platform_ops(plat)->early_exit();
}

/**
 * Final exit for current HART
 *
 * @param plat pointer to struct sbi_platform
 */
static inline void sbi_platform_final_exit(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->final_exit)
		sbi_platform_ops(plat)->final_exit();
}

/**
 * Check CPU extension in MISA
 *
 * @param plat pointer to struct sbi_platform
 * @param ext shorthand letter for CPU extensions
 *
 * @return zero for not-supported and non-zero for supported
 */
static inline int sbi_platform_misa_extension(const struct sbi_platform *plat,
					      char ext)
{
	if (plat && sbi_platform_ops(plat)->misa_check_extension)
		return sbi_platform_ops(plat)->misa_check_extension(ext);
	return 0;
}

/**
 * Get MXL field of MISA
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return 1/2/3 on success and error code on failure
 */
static inline int sbi_platform_misa_xlen(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->misa_get_xlen)
		return sbi_platform_ops(plat)->misa_get_xlen();
	return -1;
}

/**
 * Initialize (or populate) domains for the platform
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_domains_init(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->domains_init)
		return sbi_platform_ops(plat)->domains_init();
	return 0;
}

/**
 * Initialize the platform console
 *
 * @param plat pointer to struct sbi_platform
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_console_init(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->console_init)
		return sbi_platform_ops(plat)->console_init();
	return 0;
}

/**
 * Initialize the platform interrupt controller for current HART
 *
 * @param plat pointer to struct sbi_platform
 * @param cold_boot whether cold boot (TRUE) or warm_boot (FALSE)
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_irqchip_init(const struct sbi_platform *plat,
					    bool cold_boot)
{
	if (plat && sbi_platform_ops(plat)->irqchip_init)
		return sbi_platform_ops(plat)->irqchip_init(cold_boot);
	return 0;
}

/**
 * Exit the platform interrupt controller for current HART
 *
 * @param plat pointer to struct sbi_platform
 */
static inline void sbi_platform_irqchip_exit(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->irqchip_exit)
		sbi_platform_ops(plat)->irqchip_exit();
}

/**
 * Initialize the platform IPI support for current HART
 *
 * @param plat pointer to struct sbi_platform
 * @param cold_boot whether cold boot (TRUE) or warm_boot (FALSE)
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_ipi_init(const struct sbi_platform *plat,
					bool cold_boot)
{
	if (plat && sbi_platform_ops(plat)->ipi_init)
		return sbi_platform_ops(plat)->ipi_init(cold_boot);
	return 0;
}

/**
 * Exit the platform IPI support for current HART
 *
 * @param plat pointer to struct sbi_platform
 */
static inline void sbi_platform_ipi_exit(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->ipi_exit)
		sbi_platform_ops(plat)->ipi_exit();
}

/**
 * Initialize the platform timer for current HART
 *
 * @param plat pointer to struct sbi_platform
 * @param cold_boot whether cold boot (TRUE) or warm_boot (FALSE)
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_timer_init(const struct sbi_platform *plat,
					  bool cold_boot)
{
	if (plat && sbi_platform_ops(plat)->timer_init)
		return sbi_platform_ops(plat)->timer_init(cold_boot);
	return 0;
}

/**
 * Exit the platform timer for current HART
 *
 * @param plat pointer to struct sbi_platform
 */
static inline void sbi_platform_timer_exit(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->timer_exit)
		sbi_platform_ops(plat)->timer_exit();
}

/**
 * Check if a vendor extension is implemented or not.
 *
 * @param plat pointer to struct sbi_platform
 * @param extid	vendor SBI extension id
 *
 * @return 0 if extid is not implemented and 1 if implemented
 */
static inline int sbi_platform_vendor_ext_check(const struct sbi_platform *plat,
						long extid)
{
	if (plat && sbi_platform_ops(plat)->vendor_ext_check)
		return sbi_platform_ops(plat)->vendor_ext_check(extid);

	return 0;
}

/**
 * Invoke platform specific vendor SBI extension implementation.
 *
 * @param plat pointer to struct sbi_platform
 * @param extid	vendor SBI extension id
 * @param funcid SBI function id within the extension id
 * @param regs pointer to trap registers passed by the caller
 * @param out_value output value that can be filled by the callee
 * @param out_trap trap info that can be filled by the callee
 *
 * @return 0 on success and negative error code on failure
 */
static inline int sbi_platform_vendor_ext_provider(
					const struct sbi_platform *plat,
					long extid, long funcid,
					const struct sbi_trap_regs *regs,
					unsigned long *out_value,
					struct sbi_trap_info *out_trap)
{
	if (plat && sbi_platform_ops(plat)->vendor_ext_provider) {
		return sbi_platform_ops(plat)->vendor_ext_provider(extid,
								funcid, regs,
								out_value,
								out_trap);
	}

	return SBI_ENOTSUPP;
}

#endif

#endif
