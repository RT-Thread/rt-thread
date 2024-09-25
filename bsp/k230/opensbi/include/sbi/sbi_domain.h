/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_DOMAIN_H__
#define __SBI_DOMAIN_H__

#include <sbi/sbi_types.h>
#include <sbi/sbi_hartmask.h>

struct sbi_scratch;

/** Domain access types */
enum sbi_domain_access {
	SBI_DOMAIN_READ = (1UL << 0),
	SBI_DOMAIN_WRITE = (1UL << 1),
	SBI_DOMAIN_EXECUTE = (1UL << 2),
	SBI_DOMAIN_MMIO = (1UL << 3)
};

/** Representation of OpenSBI domain memory region */
struct sbi_domain_memregion {
	/**
	 * Size of memory region as power of 2
	 * It has to be minimum 3 and maximum __riscv_xlen
	 */
	unsigned long order;
	/**
	 * Base address of memory region
	 * It must be 2^order aligned address
	 */
	unsigned long base;
	/** Flags representing memory region attributes */
#define SBI_DOMAIN_MEMREGION_READABLE		(1UL << 0)
#define SBI_DOMAIN_MEMREGION_WRITEABLE		(1UL << 1)
#define SBI_DOMAIN_MEMREGION_EXECUTABLE		(1UL << 2)
#define SBI_DOMAIN_MEMREGION_MMODE		(1UL << 3)
#define SBI_DOMAIN_MEMREGION_ACCESS_MASK	(0xfUL)

#define SBI_DOMAIN_MEMREGION_MMIO		(1UL << 31)
	unsigned long flags;
};

/** Maximum number of domains */
#define SBI_DOMAIN_MAX_INDEX			32

/** Representation of OpenSBI domain */
struct sbi_domain {
	/**
	 * Logical index of this domain
	 * Note: This set by sbi_domain_finalize() in the coldboot path
	 */
	u32 index;
	/**
	 * HARTs assigned to this domain
	 * Note: This set by sbi_domain_init() and sbi_domain_finalize()
	 * in the coldboot path
	 */
	struct sbi_hartmask assigned_harts;
	/** Name of this domain */
	char name[64];
	/** Possible HARTs in this domain */
	const struct sbi_hartmask *possible_harts;
	/** Array of memory regions terminated by a region with order zero */
	struct sbi_domain_memregion *regions;
	/** HART id of the HART booting this domain */
	u32 boot_hartid;
	/** Arg1 (or 'a1' register) of next booting stage for this domain */
	unsigned long next_arg1;
	/** Address of next booting stage for this domain */
	unsigned long next_addr;
	/** Privilege mode of next booting stage for this domain */
	unsigned long next_mode;
	/** Is domain allowed to reset the system */
	bool system_reset_allowed;
};

/** The root domain instance */
extern struct sbi_domain root;

/** HART id to domain table */
extern struct sbi_domain *hartid_to_domain_table[];

/** Get pointer to sbi_domain from HART id */
#define sbi_hartid_to_domain(__hartid) \
	hartid_to_domain_table[__hartid]

/** Get pointer to sbi_domain for current HART */
#define sbi_domain_thishart_ptr() \
	sbi_hartid_to_domain(current_hartid())

/** Index to domain table */
extern struct sbi_domain *domidx_to_domain_table[];

/** Get pointer to sbi_domain from index */
#define sbi_index_to_domain(__index) \
	domidx_to_domain_table[__index]

/** Iterate over each domain */
#define sbi_domain_for_each(__i, __d) \
	for ((__i) = 0; ((__d) = sbi_index_to_domain(__i)); (__i)++)

/** Iterate over each memory region of a domain */
#define sbi_domain_for_each_memregion(__d, __r) \
	for ((__r) = (__d)->regions; (__r)->order; (__r)++)

/**
 * Check whether given HART is assigned to specified domain
 * @param dom pointer to domain
 * @param hartid the HART ID
 * @return TRUE if HART is assigned to domain otherwise FALSE
 */
bool sbi_domain_is_assigned_hart(const struct sbi_domain *dom, u32 hartid);

/**
 * Get ulong assigned HART mask for given domain and HART base ID
 * @param dom pointer to domain
 * @param hbase the HART base ID
 * @return ulong possible HART mask
 * Note: the return ulong mask will be set to zero on failure.
 */
ulong sbi_domain_get_assigned_hartmask(const struct sbi_domain *dom,
				       ulong hbase);

/**
 * Initialize a domain memory region based on it's physical
 * address and size.
 *
 * @param addr start physical address of memory region
 * @param size physical size of memory region
 * @param flags memory region flags
 * @param reg pointer to memory region being initialized
 */
void sbi_domain_memregion_init(unsigned long addr,
				unsigned long size,
				unsigned long flags,
				struct sbi_domain_memregion *reg);

/**
 * Check whether we can access specified address for given mode and
 * memory region flags under a domain
 * @param dom pointer to domain
 * @param addr the address to be checked
 * @param mode the privilege mode of access
 * @param access_flags bitmask of domain access types (enum sbi_domain_access)
 * @return TRUE if access allowed otherwise FALSE
 */
bool sbi_domain_check_addr(const struct sbi_domain *dom,
			   unsigned long addr, unsigned long mode,
			   unsigned long access_flags);

/** Dump domain details on the console */
void sbi_domain_dump(const struct sbi_domain *dom, const char *suffix);

/** Dump all domain details on the console */
void sbi_domain_dump_all(const char *suffix);

/**
 * Register a new domain
 * @param dom pointer to domain
 * @param assign_mask pointer to HART mask of HARTs assigned to the domain
 *
 * @return 0 on success and negative error code on failure
 */
int sbi_domain_register(struct sbi_domain *dom,
			const struct sbi_hartmask *assign_mask);

/**
 * Add a memory region to the root domain
 * @param reg pointer to the memory region to be added
 *
 * @return 0 on success and negative error code on failure
 */
int sbi_domain_root_add_memregion(const struct sbi_domain_memregion *reg);

/** Finalize domain tables and startup non-root domains */
int sbi_domain_finalize(struct sbi_scratch *scratch, u32 cold_hartid);

/** Initialize domains */
int sbi_domain_init(struct sbi_scratch *scratch, u32 cold_hartid);

#endif
