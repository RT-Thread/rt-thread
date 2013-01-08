/*
 * Cache operations for the cache instruction.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * (C) Copyright 1996, 97, 99, 2002, 03 Ralf Baechle
 * (C) Copyright 1999 Silicon Graphics, Inc.
 */
#ifndef __CACHE_H__
#define __CACHE_H__


#define KUSEG           		0x00000000
#define KSEG0           		0x80000000
#define KSEG1           		0xa0000000
#define KSEG2           		0xc0000000
#define KSEG3           		0xe0000000

/*
 * Cache Operations available on all MIPS processors with R4000-style caches
 */
#define Index_Invalidate_I      0x00
#define Index_Writeback_Inv_D   0x01
#define Index_Load_Tag_I		0x04
#define Index_Load_Tag_D		0x05
#define Index_Store_Tag_I		0x08
#define Index_Store_Tag_D		0x09

#define Hit_Invalidate_I		0x10
#define Hit_Invalidate_D		0x11
#define Hit_Writeback_Inv_D		0x15
#define Hit_Writeback_I			0x18
#define Hit_Writeback_D			0x19

/*
 *The lock state is cleared by executing an Index
Invalidate, Index Writeback Invalidate, Hit
Invalidate, or Hit Writeback Invalidate
operation to the locked line, or via an Index
Store Tag operation with the lock bit reset in
the TagLo register.
 */
#define Fetch_And_Lock_I  		0x1c
#define Fetch_And_Lock_D  		0x1d
/*
 * R4000-specific cacheops
 */
#define Create_Dirty_Excl_D		0x0d
#define Fill					0x14

/*
 * R4000SC and R4400SC-specific cacheops
 */
#define Index_Invalidate_SI     0x02
#define Index_Writeback_Inv_SD  0x03
#define Index_Load_Tag_SI		0x06
#define Index_Load_Tag_SD		0x07
#define Index_Store_Tag_SI		0x0A
#define Index_Store_Tag_SD		0x0B
#define Create_Dirty_Excl_SD	0x0f
#define Hit_Invalidate_SI		0x12
#define Hit_Invalidate_SD		0x13
#define Hit_Writeback_Inv_SD	0x17
#define Hit_Writeback_SD		0x1b
#define Hit_Set_Virtual_SI		0x1e
#define Hit_Set_Virtual_SD		0x1f

/*
 * R5000-specific cacheops
 */
#define R5K_Page_Invalidate_S	0x17

/*
 * RM7000-specific cacheops
 */
#define Page_Invalidate_T		0x16

/*
 * R1000-specific cacheops
 *
 * Cacheops 0x02, 0x06, 0x0a, 0x0c-0x0e, 0x16, 0x1a and 0x1e are unused.
 * Most of the _S cacheops are identical to the R4000SC _SD cacheops.
 */
#define Index_Writeback_Inv_S	0x03
#define Index_Load_Tag_S		0x07
#define Index_Store_Tag_S		0x0B
#define Hit_Invalidate_S		0x13
#define Cache_Barrier			0x14
#define Hit_Writeback_Inv_S		0x17
#define Index_Load_Data_I		0x18
#define Index_Load_Data_D		0x19
#define Index_Load_Data_S		0x1b
#define Index_Store_Data_I		0x1c
#define Index_Store_Data_D		0x1d
#define Index_Store_Data_S		0x1f


#ifndef __ASSEMBLER__

#ifndef dcache_size
#define dcache_size	(g_mips_core.dcache_ways * g_mips_core.dcache_lines_per_way * g_mips_core.dcache_line_size)
#endif

#ifndef icache_size
#define icache_size	(g_mips_core.dcache_ways * g_mips_core.dcache_lines_per_way * g_mips_core.dcache_line_size)
#endif

#ifndef cpu_dcache_line_size
#define cpu_dcache_line_size()	g_mips_core.icache_line_size
#endif

#ifndef cpu_icache_line_size
#define cpu_icache_line_size()	g_mips_core.icache_line_size
#endif

#define cache_op(op, addr)						\
	__asm__ __volatile__(						\
	"	.set	noreorder				\n"	\
	"	.set	mips3\n\t				\n"	\
	"	cache	%0, %1					\n"	\
	"	.set	mips0					\n"	\
	"	.set	reorder"					\
	:								\
	: "i" (op), "m" (*(unsigned char *)(addr)))

#define cache16_unroll32(base, op)					\
	__asm__ __volatile__(						\
	"	.set noreorder					\n"	\
	"	.set mips3					\n"	\
	"	cache %1, 0x000(%0); cache %1, 0x010(%0)	\n"	\
	"	cache %1, 0x020(%0); cache %1, 0x030(%0)	\n"	\
	"	cache %1, 0x040(%0); cache %1, 0x050(%0)	\n"	\
	"	cache %1, 0x060(%0); cache %1, 0x070(%0)	\n"	\
	"	cache %1, 0x080(%0); cache %1, 0x090(%0)	\n"	\
	"	cache %1, 0x0a0(%0); cache %1, 0x0b0(%0)	\n"	\
	"	cache %1, 0x0c0(%0); cache %1, 0x0d0(%0)	\n"	\
	"	cache %1, 0x0e0(%0); cache %1, 0x0f0(%0)	\n"	\
	"	cache %1, 0x100(%0); cache %1, 0x110(%0)	\n"	\
	"	cache %1, 0x120(%0); cache %1, 0x130(%0)	\n"	\
	"	cache %1, 0x140(%0); cache %1, 0x150(%0)	\n"	\
	"	cache %1, 0x160(%0); cache %1, 0x170(%0)	\n"	\
	"	cache %1, 0x180(%0); cache %1, 0x190(%0)	\n"	\
	"	cache %1, 0x1a0(%0); cache %1, 0x1b0(%0)	\n"	\
	"	cache %1, 0x1c0(%0); cache %1, 0x1d0(%0)	\n"	\
	"	cache %1, 0x1e0(%0); cache %1, 0x1f0(%0)	\n"	\
	"	.set mips0					\n"	\
	"	.set reorder					\n"	\
		:							\
		: "r" (base),						\
		  "i" (op));


static inline void flush_icache_line_indexed(rt_ubase_t addr)
{
	cache_op(Index_Invalidate_I, addr);
}

static inline void flush_dcache_line_indexed(rt_ubase_t addr)
{
	cache_op(Index_Writeback_Inv_D, addr);
}

static inline void flush_icache_line(rt_ubase_t addr)
{
	cache_op(Hit_Invalidate_I, addr);
}

static inline void lock_icache_line(rt_ubase_t addr)
{
	cache_op(Fetch_And_Lock_I, addr);
}

static inline void lock_dcache_line(rt_ubase_t addr)
{
	cache_op(Fetch_And_Lock_D, addr);
}

static inline void flush_dcache_line(rt_ubase_t addr)
{
	cache_op(Hit_Writeback_Inv_D, addr);
}

static inline void invalidate_dcache_line(rt_ubase_t addr)
{
	cache_op(Hit_Invalidate_D, addr);
}

static inline void blast_dcache16(void)
{
	rt_ubase_t start = KSEG0;
	rt_ubase_t end = start + dcache_size;
	rt_ubase_t addr;

	for (addr = start; addr < end; addr += 0x200)
		cache16_unroll32(addr, Index_Writeback_Inv_D);
}

static inline void inv_dcache16(void)
{
	rt_ubase_t start = KSEG0;
	rt_ubase_t end = start + dcache_size;
	rt_ubase_t addr;

	for (addr = start; addr < end; addr += 0x200)
		cache16_unroll32(addr, Hit_Invalidate_D);
}

static inline void blast_icache16(void)
{
	rt_ubase_t start = KSEG0;
	rt_ubase_t end = start + icache_size;
	rt_ubase_t addr;

	for (addr = start; addr < end; addr += 0x200)
		cache16_unroll32(addr, Index_Invalidate_I);
}



void r4k_cache_init(void);
void r4k_cache_flush_all(void);
void r4k_icache_flush_all(void);
void r4k_icache_flush_range(rt_ubase_t addr, rt_ubase_t size);
void r4k_icache_lock_range(rt_ubase_t addr, rt_ubase_t size);
void r4k_dcache_inv(rt_ubase_t addr, rt_ubase_t size);
void r4k_dcache_wback_inv(rt_ubase_t addr, rt_ubase_t size);

#endif /*end of __ASSEMBLER__ */

#endif /* end of __CACHE_H__ */
