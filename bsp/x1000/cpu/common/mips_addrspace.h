/*
 * File      : mips_addrspace.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016Äê9ÔÂ12ÈÕ     Urey         the first version
 */

#ifndef _MIPS_ADDRSPACE_H_
#define _MIPS_ADDRSPACE_H_


/*
 *  Configure language
 */
#ifdef __ASSEMBLY__
#define _ATYPE_
#define _ATYPE32_
#define _ATYPE64_
#define _CONST64_(x)	x
#else
#define _ATYPE_		__PTRDIFF_TYPE__
#define _ATYPE32_	int
#define _ATYPE64_	__s64
#ifdef CONFIG_64BIT
#define _CONST64_(x)	x ## L
#else
#define _CONST64_(x)	x ## LL
#endif
#endif

/*
 *  32-bit MIPS address spaces
 */
#ifdef __ASSEMBLY__
#define _ACAST32_
#define _ACAST64_
#else
#define _ACAST32_		(_ATYPE_)(_ATYPE32_)	/* widen if necessary */
#define _ACAST64_		(_ATYPE64_)		/* do _not_ narrow */
#endif

/*
 * Returns the kernel segment base of a given address
 */
#define KSEGX(a)		((_ACAST32_ (a)) & 0xe0000000)

/*
 * Returns the physical address of a CKSEGx / XKPHYS address
 */
#define CPHYSADDR(a)		((_ACAST32_(a)) & 0x1fffffff)
#define XPHYSADDR(a)		((_ACAST64_(a)) &			\
				 _CONST64_(0x000000ffffffffff))

#ifdef CONFIG_64BIT

/*
 * Memory segments (64bit kernel mode addresses)
 * The compatibility segments use the full 64-bit sign extended value.  Note
 * the R8000 doesn't have them so don't reference these in generic MIPS code.
 */
#define XKUSEG			_CONST64_(0x0000000000000000)
#define XKSSEG			_CONST64_(0x4000000000000000)
#define XKPHYS			_CONST64_(0x8000000000000000)
#define XKSEG			_CONST64_(0xc000000000000000)
#define CKSEG0			_CONST64_(0xffffffff80000000)
#define CKSEG1			_CONST64_(0xffffffffa0000000)
#define CKSSEG			_CONST64_(0xffffffffc0000000)
#define CKSEG3			_CONST64_(0xffffffffe0000000)

#define CKSEG0ADDR(a)		(CPHYSADDR(a) | CKSEG0)
#define CKSEG1ADDR(a)		(CPHYSADDR(a) | CKSEG1)
#define CKSEG2ADDR(a)		(CPHYSADDR(a) | CKSEG2)
#define CKSEG3ADDR(a)		(CPHYSADDR(a) | CKSEG3)

#else

#define CKSEG0ADDR(a)		(CPHYSADDR(a) | KSEG0BASE)
#define CKSEG1ADDR(a)		(CPHYSADDR(a) | KSEG1BASE)
#define CKSEG2ADDR(a)		(CPHYSADDR(a) | KSEG2BASE)
#define CKSEG3ADDR(a)		(CPHYSADDR(a) | KSEG3BASE)

/*
 * Map an address to a certain kernel segment
 */
#define KSEG0ADDR(a)		(CPHYSADDR(a) | KSEG0BASE)
#define KSEG1ADDR(a)		(CPHYSADDR(a) | KSEG1BASE)
#define KSEG2ADDR(a)		(CPHYSADDR(a) | KSEG2BASE)
#define KSEG3ADDR(a)		(CPHYSADDR(a) | KSEG3BASE)

/*
 * Memory segments (32bit kernel mode addresses)
 * These are the traditional names used in the 32-bit universe.
 */
//#define KUSEGBASE			0x00000000
//#define KSEG0BASE			0x80000000
//#define KSEG1BASE			0xa0000000
//#define KSEG2BASE			0xc0000000
//#define KSEG3BASE			0xe0000000

#define CKUSEG			0x00000000
#define CKSEG0			0x80000000
#define CKSEG1			0xa0000000
#define CKSEG2			0xc0000000
#define CKSEG3			0xe0000000

#endif

/*
 * Cache modes for XKPHYS address conversion macros
 */
#define K_CALG_COH_EXCL1_NOL2	0
#define K_CALG_COH_SHRL1_NOL2	1
#define K_CALG_UNCACHED		2
#define K_CALG_NONCOHERENT	3
#define K_CALG_COH_EXCL		4
#define K_CALG_COH_SHAREABLE	5
#define K_CALG_NOTUSED		6
#define K_CALG_UNCACHED_ACCEL	7

/*
 * 64-bit address conversions
 */
#define PHYS_TO_XKSEG_UNCACHED(p)	PHYS_TO_XKPHYS(K_CALG_UNCACHED, (p))
#define PHYS_TO_XKSEG_CACHED(p)		PHYS_TO_XKPHYS(K_CALG_COH_SHAREABLE, (p))
#define XKPHYS_TO_PHYS(p)		((p) & TO_PHYS_MASK)
#define PHYS_TO_XKPHYS(cm, a)		(_CONST64_(0x8000000000000000) | \
					 (_CONST64_(cm) << 59) | (a))

/*
 * Returns the uncached address of a sdram address
 */
#ifndef __ASSEMBLY__
#if defined(CONFIG_SOC_AU1X00) || defined(CONFIG_TB0229)
/* We use a 36 bit physical address map here and
   cannot access physical memory directly from core */
#define UNCACHED_SDRAM(a) (((unsigned long)(a)) | 0x20000000)
#else	/* !CONFIG_SOC_AU1X00 */
#define UNCACHED_SDRAM(a) CKSEG1ADDR(a)
#endif	/* CONFIG_SOC_AU1X00 */
#endif	/* __ASSEMBLY__ */

/*
 * The ultimate limited of the 64-bit MIPS architecture:  2 bits for selecting
 * the region, 3 bits for the CCA mode.  This leaves 59 bits of which the
 * R8000 implements most with its 48-bit physical address space.
 */
#define TO_PHYS_MASK	_CONST64_(0x07ffffffffffffff)	/* 2^^59 - 1 */

#ifndef CONFIG_CPU_R8000

/*
 * The R8000 doesn't have the 32-bit compat spaces so we don't define them
 * in order to catch bugs in the source code.
 */

#define COMPAT_K1BASE32		_CONST64_(0xffffffffa0000000)
#define PHYS_TO_COMPATK1(x)	((x) | COMPAT_K1BASE32) /* 32-bit compat k1 */

#endif

#define KDM_TO_PHYS(x)		(_ACAST64_ (x) & TO_PHYS_MASK)
#define PHYS_TO_K0(x)		(_ACAST64_ (x) | CAC_BASE)


#ifndef __ASSEMBLY__
/*
 * Change virtual addresses to physical addresses and vv.
 * These are trivial on the 1:1 Linux/MIPS mapping
 */
static inline phys_addr_t virt_to_phys(volatile void * address)
{
#ifndef CONFIG_64BIT
	return CPHYSADDR(address);
#else
	return XPHYSADDR(address);
#endif
}

static inline void * phys_to_virt(unsigned long address)
{
#ifndef CONFIG_64BIT
	return (void *)KSEG0ADDR(address);
#else
	return (void *)CKSEG0ADDR(address);
#endif
}
#endif


#endif /* _MIPS_ADDRSPACE_H_ */
