/*
 * File      : vfp.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
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
 * 2014-11-07     weety      first version
 */

#ifndef __VFP_H__
#define __VFP_H__

/* FPSID register bits */
#define FPSID_IMPLEMENTER_BIT   (24)
#define FPSID_IMPLEMENTER_MASK  (0xff << FPSID_IMPLEMENTER_BIT)
#define FPSID_SW                (1 << 23)
#define FPSID_FORMAT_BIT        (21)
#define FPSID_FORMAT_MASK       (0x3 << FPSID_FORMAT_BIT)
#define FPSID_NODOUBLE          (1 << 20)
#define FPSID_ARCH_BIT          (16)
#define FPSID_ARCH_MASK         (0xF << FPSID_ARCH_BIT)
#define FPSID_PART_BIT          (8)
#define FPSID_PART_MASK         (0xFF << FPSID_PART_BIT)
#define FPSID_VARIANT_BIT       (4)
#define FPSID_VARIANT_MASK      (0xF << FPSID_VARIANT_BIT)
#define FPSID_REVISION_BIT      (0)
#define FPSID_REVISION_MASK     (0xF << FPSID_REVISION_BIT)

/* FPSCR register bits */
#define FPSCR_DN           (1<<25) /* Default NaN mode enable bit */
#define FPSCR_FZ           (1<<24) /* Flush-to-zero mode enable bit */
#define FPSCR_RN           (0<<22) /* Round to nearest (RN) mode */
#define FPSCR_RP           (1<<22) /* Round towards plus infinity (RP) mode */
#define FPSCR_RM           (2<<22) /* Round towards minus infinity (RM) mode */
#define FPSCR_RZ           (3<<22) /* Round towards zero (RZ) mode */
#define FPSCR_RMODE_BIT    (22)
#define FPSCR_RMODE_MASK   (3 << FPSCR_RMODE_BIT)
#define FPSCR_STRIDE_BIT   (20)
#define FPSCR_STRIDE_MASK  (3 << FPSCR_STRIDE_BIT)
#define FPSCR_LENGTH_BIT   (16)
#define FPSCR_LENGTH_MASK  (7 << FPSCR_LENGTH_BIT)
#define FPSCR_IDE          (1<<15) /* Input Subnormal exception trap enable bit */
#define FPSCR_IXE          (1<<12) /* Inexact exception trap enable bit */
#define FPSCR_UFE          (1<<11) /* Underflow exception trap enable bit */
#define FPSCR_OFE          (1<<10) /* Overflow exception trap enable bit */
#define FPSCR_DZE          (1<<9)  /* Division by Zero exception trap enable bit */
#define FPSCR_IOE          (1<<8)  /* Invalid Operation exception trap enable bit */
#define FPSCR_IDC          (1<<7)  /* Input Subnormal cumulative exception flag */
#define FPSCR_IXC          (1<<4)  /* Inexact cumulative exception flag */
#define FPSCR_UFC          (1<<3)  /* Underflow cumulative exception flag */
#define FPSCR_OFC          (1<<2)  /* Overflow cumulative exception flag */
#define FPSCR_DZC          (1<<1)  /* Division by Zero cumulative exception flag */
#define FPSCR_IOC          (1<<0)  /* Invalid Operation cumulative exception flag */

/* FPEXC register bits */
#define FPEXC_EX          (1 << 31) /* When EX is set, the VFP coprocessor is in the exceptional state */
#define FPEXC_EN          (1 << 30) /* VFP enable bit */
#define FPEXC_DEX         (1 << 29) /* Defined synchronous instruction exceptional flag */
#define FPEXC_FP2V        (1 << 28) /*  FPINST2 instruction valid flag */
#define FPEXC_LENGTH_BIT  (8)
#define FPEXC_LENGTH_MASK (7 << FPEXC_LENGTH_BIT)
#define FPEXC_INV         (1 << 7)  /* Input exception flag */
#define FPEXC_UFC         (1 << 3)  /* Potential underflow flag */
#define FPEXC_OFC         (1 << 2)  /* Potential overflow flag */
#define FPEXC_IOC         (1 << 0)  /* Potential invalid operation flag */
#define FPEXC_TRAP_MASK   (FPEXC_INV|FPEXC_UFC|FPEXC_OFC|FPEXC_IOC)


/* MVFR0 register bits */
#define MVFR0_A_SIMD_BIT    (0)
#define MVFR0_A_SIMD_MASK   (0xf << MVFR0_A_SIMD_BIT)


/* thread switch micro */
#define THREAD_INIT   0
#define THREAD_EXIT   1

/*
 * get VFP register
 */

#define vmrs(vfp) ({ \
    rt_uint32_t var; \
    asm("vmrs  %0, "#vfp"" : "=r" (var) : : "cc"); \
    var; \
 })

#define vmsr(vfp, var) \
    asm("vmsr  "#vfp",  %0"	\
       : : "r" (var) : "cc")


#endif


