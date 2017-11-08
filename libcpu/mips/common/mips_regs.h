/*
 * File      : mips_regs.h
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
 * 2016年9月7日     Urey         the first version
 */

#ifndef _MIPS_REGS_H_
#define _MIPS_REGS_H_


#if !defined(__ASSEMBLY__) && !defined(ASSEMBLY)
#include <rtdef.h>

#define MIPS_REG_NR             32
typedef struct {
    rt_uint32_t  regs[MIPS_REG_NR];                             	/*  32 个通用目的寄存器         */
    rt_uint32_t  CP0Status;                                        	/*  CP0 协处理器状态寄存器      */
    rt_uint32_t  CP0DataHI;                                        	/*  除数高位寄存器              */
    rt_uint32_t  CP0DataLO;                                        	/*  除数低位寄存器              */
    rt_uint32_t  CP0BadVAddr;                                      	/*  出错地址寄存器              */
    rt_uint32_t  CP0Cause;                                         	/*  产生中断或者异常查看的寄存器*/
    rt_uint32_t  CP0EPC;                                           	/*  程序计数器寄存器			*/
} mips_reg_ctx;

#define MIPS_ARG_REG_NR         4
typedef struct
{
	rt_uint32_t  args[MIPS_ARG_REG_NR];                              /*  4 个参数寄存器              */
} mips_arg_ctx;

struct linkctx
{
	rt_uint32_t id;
	struct linkctx *next;
};

struct fpctx
{
  struct linkctx link;
  rt_uint32_t fcsr;
  rt_uint32_t reserved;
};


struct fp32ctx
{
  struct fpctx fp;
  union
    {
      double d[16];	/* even doubles */
      float s[32];	/* even singles, padded */
    };
};

struct fp64ctx
{
  struct fpctx fp;
  union
    {
      double d[32];	/* even doubles, followed by odd doubles */
      float s[64];	/* even singles, followed by odd singles, padded */
    };
};

#endif /* !defined(__ASSEMBLY__) && !defined(ASSEMBLY) */

#define MIPS_STK_CTX_WORD_SIZE			38
#define SZREG			4
/*********************************************************************************************************
  MIPS 的寄存器索引
*********************************************************************************************************/
#define REG_ZERO                0                                       /*  wired zero                  */
#define REG_AT                  1                                       /*  assembler temp              */
#define REG_V0                  2                                       /*  return reg 0                */
#define REG_V1                  3                                       /*  return reg 1                */
#define REG_A0                  4                                       /*  arg reg 0                   */
#define REG_A1                  5                                       /*  arg reg 1                   */
#define REG_A2                  6                                       /*  arg reg 2                   */
#define REG_A3                  7                                       /*  arg reg 3                   */
#define REG_T0                  8                                       /*  caller saved 0              */
#define REG_T1                  9                                       /*  caller saved 1              */
#define REG_T2                  10                                      /*  caller saved 2              */
#define REG_T3                  11                                      /*  caller saved 3              */
#define REG_T4                  12                                      /*  caller saved 4              */
#define REG_T5                  13                                      /*  caller saved 5              */
#define REG_T6                  14                                      /*  caller saved 6              */
#define REG_T7                  15                                      /*  caller saved 7              */
#define REG_S0                  16                                      /*  callee saved 0              */
#define REG_S1                  17                                      /*  callee saved 1              */
#define REG_S2                  18                                      /*  callee saved 2              */
#define REG_S3                  19                                      /*  callee saved 3              */
#define REG_S4                  20                                      /*  callee saved 4              */
#define REG_S5                  21                                      /*  callee saved 5              */
#define REG_S6                  22                                      /*  callee saved 6              */
#define REG_S7                  23                                      /*  callee saved 7              */
#define REG_T8                  24                                      /*  caller saved 8              */
#define REG_T9                  25                                      /*  caller saved 9              */
#define REG_K0                  26                                      /*  kernel temp 0               */
#define REG_K1                  27                                      /*  kernel temp 1               */
#define REG_GP                  28                                      /*  global pointer              */
#define REG_SP                  29                                      /*  stack pointer               */
#define REG_S8                  30                                      /*  callee saved 8              */
#define REG_FP                  REG_S8                                  /*  callee saved 8              */
#define REG_RA                  31                                      /*  return address              */

#define STK_CTX_SIZE            (MIPS_STK_CTX_WORD_SIZE * SZREG)
#define STK_OFFSET_SR           ((32 + 0) * SZREG)
#define STK_OFFSET_HI           ((32 + 1) * SZREG)
#define STK_OFFSET_LO           ((32 + 2) * SZREG)
#define STK_OFFSET_BADVADDR     ((32 + 3) * SZREG)
#define STK_OFFSET_CAUSE        ((32 + 4) * SZREG)
#define STK_OFFSET_EPC          ((32 + 5) * SZREG)

#define STK_OFFSET_LAST         ((MIPS_STK_CTX_WORD_SIZE - 1) * SZREG)

#define FP32CTX_CSR	((SZREG)*2)
#define FP64CTX_CSR	((SZREG)*2)

#define LINKCTX_ID      ((SZREG)*0)
#define LINKCTX_NEXT    ((SZREG)*1)
#define LINKCTX_TYPE_MSA        0x004D5341
#define LINKCTX_TYPE_FP32       0x46503332
#define LINKCTX_TYPE_FP64       0x46503634
#define LINKCTX_TYPE_FMSA       0x463D5341
#define LINKCTX_TYPE_DSP        0x00445350
#define LINKCTX_TYPE_STKSWP     0x53574150
#define LINKCTX_TYPE_XPA	0x00585041

#define FP32CTX_0	((SZREG)*4)
#define FP32CTX_2	(FP32CTX_0 + (1 * 8))
#define FP32CTX_4	(FP32CTX_0 + (2 * 8))
#define FP32CTX_6	(FP32CTX_0 + (3 * 8))
#define FP32CTX_8	(FP32CTX_0 + (4 * 8))
#define FP32CTX_10	(FP32CTX_0 + (5 * 8))
#define FP32CTX_12	(FP32CTX_0 + (6 * 8))
#define FP32CTX_14	(FP32CTX_0 + (7 * 8))
#define FP32CTX_16	(FP32CTX_0 + (8 * 8))
#define FP32CTX_18	(FP32CTX_0 + (9 * 8))
#define FP32CTX_20	(FP32CTX_0 + (10 * 8))
#define FP32CTX_22	(FP32CTX_0 + (11 * 8))
#define FP32CTX_24	(FP32CTX_0 + (12 * 8))
#define FP32CTX_26	(FP32CTX_0 + (13 * 8))
#define FP32CTX_28	(FP32CTX_0 + (14 * 8))
#define FP32CTX_30	(FP32CTX_0 + (15 * 8))
#define FP32CTX_SIZE	(FP32CTX_30 + (17 * 8))

#define FP64CTX_0	((SZREG)*4)
#define FP64CTX_2	(FP64CTX_0 + (1 * 8))
#define FP64CTX_4	(FP64CTX_0 + (2 * 8))
#define FP64CTX_6	(FP64CTX_0 + (3 * 8))
#define FP64CTX_8	(FP64CTX_0 + (4 * 8))
#define FP64CTX_10	(FP64CTX_0 + (5 * 8))
#define FP64CTX_12	(FP64CTX_0 + (6 * 8))
#define FP64CTX_14	(FP64CTX_0 + (7 * 8))
#define FP64CTX_16	(FP64CTX_0 + (8 * 8))
#define FP64CTX_18	(FP64CTX_0 + (9 * 8))
#define FP64CTX_20	(FP64CTX_0 + (10 * 8))
#define FP64CTX_22	(FP64CTX_0 + (11 * 8))
#define FP64CTX_24	(FP64CTX_0 + (12 * 8))
#define FP64CTX_26	(FP64CTX_0 + (13 * 8))
#define FP64CTX_28	(FP64CTX_0 + (14 * 8))
#define FP64CTX_30	(FP64CTX_0 + (15 * 8))
#define FP64CTX_1	(FP64CTX_30 + (1 * 8))
#define FP64CTX_3	(FP64CTX_30 + (2 * 8))
#define FP64CTX_5	(FP64CTX_30 + (3 * 8))
#define FP64CTX_7	(FP64CTX_30 + (4 * 8))
#define FP64CTX_9	(FP64CTX_30 + (5 * 8))
#define FP64CTX_11	(FP64CTX_30 + (6 * 8))
#define FP64CTX_13	(FP64CTX_30 + (7 * 8))
#define FP64CTX_15	(FP64CTX_30 + (8 * 8))
#define FP64CTX_17	(FP64CTX_30 + (9 * 8))
#define FP64CTX_19	(FP64CTX_30 + (10 * 8))
#define FP64CTX_21	(FP64CTX_30 + (11 * 8))
#define FP64CTX_23	(FP64CTX_30 + (12 * 8))
#define FP64CTX_25	(FP64CTX_30 + (13 * 8))
#define FP64CTX_27	(FP64CTX_30 + (14 * 8))
#define FP64CTX_29	(FP64CTX_30 + (15 * 8))
#define FP64CTX_31	(FP64CTX_30 + (16 * 8))
#define FP64CTX_SIZE	(FP64CTX_31 + (17 * 8))

#define FPCTX_SIZE()	(mips_getsr() & ST0_FR ? FP64CTX_SIZE : FP32CTX_SIZE)

/*
 * The following macros are especially useful for __asm__
 * inline assembler.
 */
#ifndef __STR
#define __STR(x) #x
#endif
#ifndef STR
#define STR(x) __STR(x)
#endif

/*
 *  Configure language
 */
#ifdef __ASSEMBLY__
#define _ULCAST_
#else
#define _ULCAST_ (unsigned long)
#endif

/*
 * Coprocessor 0 register names
 */
#define CP0_INDEX $0
#define CP0_RANDOM $1
#define CP0_ENTRYLO0 $2
#define CP0_ENTRYLO1 $3
#define CP0_CONF $3
#define CP0_CONTEXT $4
#define CP0_PAGEMASK $5
#define CP0_WIRED $6
#define CP0_INFO $7
#define CP0_BADVADDR $8
#define CP0_COUNT $9
#define CP0_ENTRYHI $10
#define CP0_COMPARE $11
#define CP0_STATUS $12
#define CP0_CAUSE $13
#define CP0_EPC $14
#define CP0_PRID $15
#define CP0_CONFIG $16
#define CP0_LLADDR $17
#define CP0_WATCHLO $18
#define CP0_WATCHHI $19
#define CP0_XCONTEXT $20
#define CP0_FRAMEMASK $21
#define CP0_DIAGNOSTIC $22
#define CP0_DEBUG $23
#define CP0_DEPC $24
#define CP0_PERFORMANCE $25
#define CP0_ECC $26
#define CP0_CACHEERR $27
#define CP0_TAGLO $28
#define CP0_TAGHI $29
#define CP0_ERROREPC $30
#define CP0_DESAVE $31

/*
 * R4640/R4650 cp0 register names.  These registers are listed
 * here only for completeness; without MMU these CPUs are not useable
 * by Linux.  A future ELKS port might take make Linux run on them
 * though ...
 */
#define CP0_IBASE $0
#define CP0_IBOUND $1
#define CP0_DBASE $2
#define CP0_DBOUND $3
#define CP0_CALG $17
#define CP0_IWATCH $18
#define CP0_DWATCH $19

/*
 * Coprocessor 0 Set 1 register names
 */
#define CP0_S1_DERRADDR0  $26
#define CP0_S1_DERRADDR1  $27
#define CP0_S1_INTCONTROL $20

/*
 *  TX39 Series
 */
#define CP0_TX39_CACHE	$7

/*
 * Coprocessor 1 (FPU) register names
 */
#define CP1_REVISION   $0
#define CP1_STATUS     $31

/*
 * FPU Status Register Values
 */
/*
 * Status Register Values
 */

#define FPU_CSR_FLUSH   0x01000000      /* flush denormalised results to 0 */
#define FPU_CSR_COND    0x00800000      /* $fcc0 */
#define FPU_CSR_COND0   0x00800000      /* $fcc0 */
#define FPU_CSR_COND1   0x02000000      /* $fcc1 */
#define FPU_CSR_COND2   0x04000000      /* $fcc2 */
#define FPU_CSR_COND3   0x08000000      /* $fcc3 */
#define FPU_CSR_COND4   0x10000000      /* $fcc4 */
#define FPU_CSR_COND5   0x20000000      /* $fcc5 */
#define FPU_CSR_COND6   0x40000000      /* $fcc6 */
#define FPU_CSR_COND7   0x80000000      /* $fcc7 */

/*
 * X the exception cause indicator
 * E the exception enable
 * S the sticky/flag bit
*/
#define FPU_CSR_ALL_X   0x0003f000
#define FPU_CSR_UNI_X   0x00020000
#define FPU_CSR_INV_X   0x00010000
#define FPU_CSR_DIV_X   0x00008000
#define FPU_CSR_OVF_X   0x00004000
#define FPU_CSR_UDF_X   0x00002000
#define FPU_CSR_INE_X   0x00001000

#define FPU_CSR_ALL_E   0x00000f80
#define FPU_CSR_INV_E   0x00000800
#define FPU_CSR_DIV_E   0x00000400
#define FPU_CSR_OVF_E   0x00000200
#define FPU_CSR_UDF_E   0x00000100
#define FPU_CSR_INE_E   0x00000080

#define FPU_CSR_ALL_S   0x0000007c
#define FPU_CSR_INV_S   0x00000040
#define FPU_CSR_DIV_S   0x00000020
#define FPU_CSR_OVF_S   0x00000010
#define FPU_CSR_UDF_S   0x00000008
#define FPU_CSR_INE_S   0x00000004

/* rounding mode */
#define FPU_CSR_RN      0x0     /* nearest */
#define FPU_CSR_RZ      0x1     /* towards zero */
#define FPU_CSR_RU      0x2     /* towards +Infinity */
#define FPU_CSR_RD      0x3     /* towards -Infinity */


/*
 * Values for PageMask register
 */
#ifdef CONFIG_CPU_VR41XX

/* Why doesn't stupidity hurt ... */

#define PM_1K		0x00000000
#define PM_4K		0x00001800
#define PM_16K		0x00007800
#define PM_64K		0x0001f800
#define PM_256K		0x0007f800

#else

#define PM_4K		0x00000000
#define PM_16K		0x00006000
#define PM_64K		0x0001e000
#define PM_256K		0x0007e000
#define PM_1M		0x001fe000
#define PM_4M		0x007fe000
#define PM_16M		0x01ffe000
#define PM_64M		0x07ffe000
#define PM_256M		0x1fffe000

#endif

/*
 * Values used for computation of new tlb entries
 */
#define PL_4K		12
#define PL_16K		14
#define PL_64K		16
#define PL_256K		18
#define PL_1M		20
#define PL_4M		22
#define PL_16M		24
#define PL_64M		26
#define PL_256M		28

/*
 * R4x00 interrupt enable / cause bits
 */
#define IE_SW0          (_ULCAST_(1) <<  8)
#define IE_SW1          (_ULCAST_(1) <<  9)
#define IE_IRQ0         (_ULCAST_(1) << 10)
#define IE_IRQ1         (_ULCAST_(1) << 11)
#define IE_IRQ2         (_ULCAST_(1) << 12)
#define IE_IRQ3         (_ULCAST_(1) << 13)
#define IE_IRQ4         (_ULCAST_(1) << 14)
#define IE_IRQ5         (_ULCAST_(1) << 15)

/*
 * R4x00 interrupt cause bits
 */
#define C_SW0           (_ULCAST_(1) <<  8)
#define C_SW1           (_ULCAST_(1) <<  9)
#define C_IRQ0          (_ULCAST_(1) << 10)
#define C_IRQ1          (_ULCAST_(1) << 11)
#define C_IRQ2          (_ULCAST_(1) << 12)
#define C_IRQ3          (_ULCAST_(1) << 13)
#define C_IRQ4          (_ULCAST_(1) << 14)
#define C_IRQ5          (_ULCAST_(1) << 15)

/*
 * Bitfields in the R4xx0 cp0 status register
 */
#define ST0_IE			0x00000001
#define ST0_EXL			0x00000002
#define ST0_ERL			0x00000004
#define ST0_KSU			0x00000018
#  define KSU_USER		0x00000010
#  define KSU_SUPERVISOR	0x00000008
#  define KSU_KERNEL		0x00000000
#define ST0_UX			0x00000020
#define ST0_SX			0x00000040
#define ST0_KX 			0x00000080
#define ST0_DE			0x00010000
#define ST0_CE			0x00020000

/*
 * Bitfields in the R[23]000 cp0 status register.
 */
#define ST0_IEC                 0x00000001
#define ST0_KUC			0x00000002
#define ST0_IEP			0x00000004
#define ST0_KUP			0x00000008
#define ST0_IEO			0x00000010
#define ST0_KUO			0x00000020
/* bits 6 & 7 are reserved on R[23]000 */
#define ST0_ISC			0x00010000
#define ST0_SWC			0x00020000
#define ST0_CM			0x00080000

/*
 * Bits specific to the R4640/R4650
 */
#define ST0_UM			(_ULCAST_(1) <<  4)
#define ST0_IL			(_ULCAST_(1) << 23)
#define ST0_DL			(_ULCAST_(1) << 24)

/*
 * Bitfields in the TX39 family CP0 Configuration Register 3
 */
#define TX39_CONF_ICS_SHIFT	19
#define TX39_CONF_ICS_MASK	0x00380000
#define TX39_CONF_ICS_1KB 	0x00000000
#define TX39_CONF_ICS_2KB 	0x00080000
#define TX39_CONF_ICS_4KB 	0x00100000
#define TX39_CONF_ICS_8KB 	0x00180000
#define TX39_CONF_ICS_16KB 	0x00200000

#define TX39_CONF_DCS_SHIFT	16
#define TX39_CONF_DCS_MASK	0x00070000
#define TX39_CONF_DCS_1KB 	0x00000000
#define TX39_CONF_DCS_2KB 	0x00010000
#define TX39_CONF_DCS_4KB 	0x00020000
#define TX39_CONF_DCS_8KB 	0x00030000
#define TX39_CONF_DCS_16KB 	0x00040000

#define TX39_CONF_CWFON 	0x00004000
#define TX39_CONF_WBON  	0x00002000
#define TX39_CONF_RF_SHIFT	10
#define TX39_CONF_RF_MASK	0x00000c00
#define TX39_CONF_DOZE		0x00000200
#define TX39_CONF_HALT		0x00000100
#define TX39_CONF_LOCK		0x00000080
#define TX39_CONF_ICE		0x00000020
#define TX39_CONF_DCE		0x00000010
#define TX39_CONF_IRSIZE_SHIFT	2
#define TX39_CONF_IRSIZE_MASK	0x0000000c
#define TX39_CONF_DRSIZE_SHIFT	0
#define TX39_CONF_DRSIZE_MASK	0x00000003

/*
 * Status register bits available in all MIPS CPUs.
 */
#define ST0_IM			0x0000ff00
#define  STATUSB_IP0		8
#define  STATUSF_IP0		(_ULCAST_(1) <<  8)
#define  STATUSB_IP1		9
#define  STATUSF_IP1		(_ULCAST_(1) <<  9)
#define  STATUSB_IP2		10
#define  STATUSF_IP2		(_ULCAST_(1) << 10)
#define  STATUSB_IP3		11
#define  STATUSF_IP3		(_ULCAST_(1) << 11)
#define  STATUSB_IP4		12
#define  STATUSF_IP4		(_ULCAST_(1) << 12)
#define  STATUSB_IP5		13
#define  STATUSF_IP5		(_ULCAST_(1) << 13)
#define  STATUSB_IP6		14
#define  STATUSF_IP6		(_ULCAST_(1) << 14)
#define  STATUSB_IP7		15
#define  STATUSF_IP7		(_ULCAST_(1) << 15)
#define  STATUSB_IP8		0
#define  STATUSF_IP8		(_ULCAST_(1) <<  0)
#define  STATUSB_IP9		1
#define  STATUSF_IP9		(_ULCAST_(1) <<  1)
#define  STATUSB_IP10		2
#define  STATUSF_IP10		(_ULCAST_(1) <<  2)
#define  STATUSB_IP11		3
#define  STATUSF_IP11		(_ULCAST_(1) <<  3)
#define  STATUSB_IP12		4
#define  STATUSF_IP12		(_ULCAST_(1) <<  4)
#define  STATUSB_IP13		5
#define  STATUSF_IP13		(_ULCAST_(1) <<  5)
#define  STATUSB_IP14		6
#define  STATUSF_IP14		(_ULCAST_(1) <<  6)
#define  STATUSB_IP15		7
#define  STATUSF_IP15		(_ULCAST_(1) <<  7)
#define ST0_CH			0x00040000
#define ST0_SR			0x00100000
#define ST0_TS			0x00200000
#define ST0_BEV			0x00400000
#define ST0_RE			0x02000000
#define ST0_FR			0x04000000
#define ST0_CU			0xf0000000
#define ST0_CU0			0x10000000
#define ST0_CU1			0x20000000
#define ST0_CU1_SHIFT			29
#define ST0_CU2			0x40000000
#define ST0_CU3			0x80000000
#define ST0_XX			0x80000000	/* MIPS IV naming */

/*
 * Bitfields and bit numbers in the coprocessor 0 cause register.
 *
 * Refer to your MIPS R4xx0 manual, chapter 5 for explanation.
 */
#define  CAUSEB_EXCCODE		2
#define  CAUSEF_EXCCODE		(_ULCAST_(31)  <<  2)
#define  CAUSEB_IP		8
#define  CAUSEF_IP		(_ULCAST_(255) <<  8)
#define  CAUSEB_IP0		8
#define  CAUSEF_IP0		(_ULCAST_(1)   <<  8)
#define  CAUSEB_IP1		9
#define  CAUSEF_IP1		(_ULCAST_(1)   <<  9)
#define  CAUSEB_IP2		10
#define  CAUSEF_IP2		(_ULCAST_(1)   << 10)
#define  CAUSEB_IP3		11
#define  CAUSEF_IP3		(_ULCAST_(1)   << 11)
#define  CAUSEB_IP4		12
#define  CAUSEF_IP4		(_ULCAST_(1)   << 12)
#define  CAUSEB_IP5		13
#define  CAUSEF_IP5		(_ULCAST_(1)   << 13)
#define  CAUSEB_IP6		14
#define  CAUSEF_IP6		(_ULCAST_(1)   << 14)
#define  CAUSEB_IP7		15
#define  CAUSEF_IP7		(_ULCAST_(1)   << 15)
#define  CAUSEB_IV		23
#define  CAUSEF_IV		(_ULCAST_(1)   << 23)
#define  CAUSEB_CE		28
#define  CAUSEF_CE		(_ULCAST_(3)   << 28)
#define  CAUSEB_BD		31
#define  CAUSEF_BD		(_ULCAST_(1)   << 31)

/*
 * Bits in the coprocessor 0 config register.
 */
/* Generic bits.  */
#define CONF_CM_CACHABLE_NO_WA		0
#define CONF_CM_CACHABLE_WA		1
#define CONF_CM_UNCACHED		2
#define CONF_CM_CACHABLE_NONCOHERENT	3
#define CONF_CM_CACHABLE_CE		4
#define CONF_CM_CACHABLE_COW		5
#define CONF_CM_CACHABLE_CUW		6
#define CONF_CM_CACHABLE_ACCELERATED	7
#define CONF_CM_CMASK			7
#define CONF_BE			(_ULCAST_(1) << 15)

/* Bits common to various processors.  */
#define CONF_CU			(_ULCAST_(1) <<  3)
#define CONF_DB			(_ULCAST_(1) <<  4)
#define CONF_IB			(_ULCAST_(1) <<  5)
#define CONF_DC			(_ULCAST_(7) <<  6)
#define CONF_IC			(_ULCAST_(7) <<  9)
#define CONF_EB			(_ULCAST_(1) << 13)
#define CONF_EM			(_ULCAST_(1) << 14)
#define CONF_SM			(_ULCAST_(1) << 16)
#define CONF_SC			(_ULCAST_(1) << 17)
#define CONF_EW			(_ULCAST_(3) << 18)
#define CONF_EP			(_ULCAST_(15)<< 24)
#define CONF_EC			(_ULCAST_(7) << 28)
#define CONF_CM			(_ULCAST_(1) << 31)

/* Bits specific to the R4xx0.  */
#define R4K_CONF_SW		(_ULCAST_(1) << 20)
#define R4K_CONF_SS		(_ULCAST_(1) << 21)
#define R4K_CONF_SB		(_ULCAST_(3) << 22)

/* Bits specific to the R5000.  */
#define R5K_CONF_SE		(_ULCAST_(1) << 12)
#define R5K_CONF_SS		(_ULCAST_(3) << 20)

/* Bits specific to the R10000.  */
#define R10K_CONF_DN		(_ULCAST_(3) <<  3)
#define R10K_CONF_CT		(_ULCAST_(1) <<  5)
#define R10K_CONF_PE		(_ULCAST_(1) <<  6)
#define R10K_CONF_PM		(_ULCAST_(3) <<  7)
#define R10K_CONF_EC		(_ULCAST_(15)<<  9)
#define R10K_CONF_SB		(_ULCAST_(1) << 13)
#define R10K_CONF_SK		(_ULCAST_(1) << 14)
#define R10K_CONF_SS		(_ULCAST_(7) << 16)
#define R10K_CONF_SC		(_ULCAST_(7) << 19)
#define R10K_CONF_DC		(_ULCAST_(7) << 26)
#define R10K_CONF_IC		(_ULCAST_(7) << 29)

/* Bits specific to the VR41xx.  */
#define VR41_CONF_CS		(_ULCAST_(1) << 12)
#define VR41_CONF_M16		(_ULCAST_(1) << 20)
#define VR41_CONF_AD		(_ULCAST_(1) << 23)

/* Bits specific to the R30xx.  */
#define R30XX_CONF_FDM		(_ULCAST_(1) << 19)
#define R30XX_CONF_REV		(_ULCAST_(1) << 22)
#define R30XX_CONF_AC		(_ULCAST_(1) << 23)
#define R30XX_CONF_RF		(_ULCAST_(1) << 24)
#define R30XX_CONF_HALT		(_ULCAST_(1) << 25)
#define R30XX_CONF_FPINT	(_ULCAST_(7) << 26)
#define R30XX_CONF_DBR		(_ULCAST_(1) << 29)
#define R30XX_CONF_SB		(_ULCAST_(1) << 30)
#define R30XX_CONF_LOCK		(_ULCAST_(1) << 31)

/* Bits specific to the TX49.  */
#define TX49_CONF_DC		(_ULCAST_(1) << 16)
#define TX49_CONF_IC		(_ULCAST_(1) << 17)  /* conflict with CONF_SC */
#define TX49_CONF_HALT		(_ULCAST_(1) << 18)
#define TX49_CONF_CWFON		(_ULCAST_(1) << 27)

/* Bits specific to the MIPS32/64 PRA.  */
#define MIPS_CONF_MT		(_ULCAST_(7) <<  7)
#define MIPS_CONF_AR		(_ULCAST_(7) << 10)
#define MIPS_CONF_AT		(_ULCAST_(3) << 13)
#define MIPS_CONF_M		(_ULCAST_(1) << 31)

/*
 * R10000 performance counter definitions.
 *
 * FIXME: The R10000 performance counter opens a nice way to implement CPU
 *        time accounting with a precission of one cycle.  I don't have
 *        R10000 silicon but just a manual, so ...
 */

/*
 * Events counted by counter #0
 */
#define CE0_CYCLES			0
#define CE0_INSN_ISSUED			1
#define CE0_LPSC_ISSUED			2
#define CE0_S_ISSUED			3
#define CE0_SC_ISSUED			4
#define CE0_SC_FAILED			5
#define CE0_BRANCH_DECODED		6
#define CE0_QW_WB_SECONDARY		7
#define CE0_CORRECTED_ECC_ERRORS	8
#define CE0_ICACHE_MISSES		9
#define CE0_SCACHE_I_MISSES		10
#define CE0_SCACHE_I_WAY_MISSPREDICTED	11
#define CE0_EXT_INTERVENTIONS_REQ	12
#define CE0_EXT_INVALIDATE_REQ		13
#define CE0_VIRTUAL_COHERENCY_COND	14
#define CE0_INSN_GRADUATED		15

/*
 * Events counted by counter #1
 */
#define CE1_CYCLES			0
#define CE1_INSN_GRADUATED		1
#define CE1_LPSC_GRADUATED		2
#define CE1_S_GRADUATED			3
#define CE1_SC_GRADUATED		4
#define CE1_FP_INSN_GRADUATED		5
#define CE1_QW_WB_PRIMARY		6
#define CE1_TLB_REFILL			7
#define CE1_BRANCH_MISSPREDICTED	8
#define CE1_DCACHE_MISS			9
#define CE1_SCACHE_D_MISSES		10
#define CE1_SCACHE_D_WAY_MISSPREDICTED	11
#define CE1_EXT_INTERVENTION_HITS	12
#define CE1_EXT_INVALIDATE_REQ		13
#define CE1_SP_HINT_TO_CEXCL_SC_BLOCKS	14
#define CE1_SP_HINT_TO_SHARED_SC_BLOCKS	15

/*
 * These flags define in which priviledge mode the counters count events
 */
#define CEB_USER	8	/* Count events in user mode, EXL = ERL = 0 */
#define CEB_SUPERVISOR	4	/* Count events in supvervisor mode EXL = ERL = 0 */
#define CEB_KERNEL	2	/* Count events in kernel mode EXL = ERL = 0 */
#define CEB_EXL		1	/* Count events with EXL = 1, ERL = 0 */

#ifndef __ASSEMBLY__

#define CAUSE_EXCCODE(x) ((CAUSEF_EXCCODE & (x->cp0_cause)) >> CAUSEB_EXCCODE)
#define CAUSE_EPC(x) (x->cp0_epc + (((x->cp0_cause & CAUSEF_BD) >> CAUSEB_BD) << 2))

/*
 * Functions to access the r10k performance counter and control registers
 */
#define read_r10k_perf_cntr(counter)                            \
({ unsigned int __res;                                          \
        __asm__ __volatile__(                                   \
        "mfpc\t%0, "STR(counter)                                \
        : "=r" (__res));                                        \
        __res;})

#define write_r10k_perf_cntr(counter,val)                       \
        __asm__ __volatile__(                                   \
        "mtpc\t%0, "STR(counter)                                \
        : : "r" (val));

#define read_r10k_perf_cntl(counter)                            \
({ unsigned int __res;                                          \
        __asm__ __volatile__(                                   \
        "mfps\t%0, "STR(counter)                                \
        : "=r" (__res));                                        \
        __res;})

#define write_r10k_perf_cntl(counter,val)                       \
        __asm__ __volatile__(                                   \
        "mtps\t%0, "STR(counter)                                \
        : : "r" (val));

/*
 * Macros to access the system control coprocessor
 */

#define __read_32bit_c0_register(source, sel)				\
({ int __res;								\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			"mfc0\t%0, " #source "\n\t"			\
			: "=r" (__res));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips32\n\t"				\
			"mfc0\t%0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	__res;								\
})

#define __read_64bit_c0_register(source, sel)				\
({ unsigned long __res;							\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips3\n\t"				\
			"dmfc0\t%0, " #source "\n\t"			\
			".set\tmips0"					\
			: "=r" (__res));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmfc0\t%0, " #source ", " #sel "\n\t"		\
			".set\tmips0"					\
			: "=r" (__res));				\
	__res;								\
})

#define __write_32bit_c0_register(register, sel, value)			\
do {									\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			"mtc0\t%z0, " #register "\n\t"			\
			: : "Jr" (value));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips32\n\t"				\
			"mtc0\t%z0, " #register ", " #sel "\n\t"	\
			".set\tmips0"					\
			: : "Jr" (value));				\
} while (0)

#define __write_64bit_c0_register(register, sel, value)			\
do {									\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips3\n\t"				\
			"dmtc0\t%z0, " #register "\n\t"			\
			".set\tmips0"					\
			: : "Jr" (value));				\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmtc0\t%z0, " #register ", " #sel "\n\t"	\
			".set\tmips0"					\
			: : "Jr" (value));				\
} while (0)

#define __read_ulong_c0_register(reg, sel)				\
	((sizeof(unsigned long) == 4) ?					\
	__read_32bit_c0_register(reg, sel) :				\
	__read_64bit_c0_register(reg, sel))

#define __write_ulong_c0_register(reg, sel, val)			\
do {									\
	if (sizeof(unsigned long) == 4)					\
		__write_32bit_c0_register(reg, sel, val);		\
	else								\
		__write_64bit_c0_register(reg, sel, val);		\
} while (0)

/*
 * These versions are only needed for systems with more than 38 bits of
 * physical address space running the 32-bit kernel.  That's none atm :-)
 */
#define __read_64bit_c0_split(source, sel)				\
({									\
	unsigned long long val;						\
	unsigned long flags;						\
									\
	local_irq_save(flags);						\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmfc0\t%M0, " #source "\n\t"			\
			"dsll\t%L0, %M0, 32\n\t"			\
			"dsrl\t%M0, %M0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			".set\tmips0"					\
			: "=r" (val));					\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dmfc0\t%M0, " #source ", " #sel "\n\t"		\
			"dsll\t%L0, %M0, 32\n\t"			\
			"dsrl\t%M0, %M0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			".set\tmips0"					\
			: "=r" (val));					\
	local_irq_restore(flags);					\
									\
	val;								\
})

#define __write_64bit_c0_split(source, sel, val)			\
do {									\
	unsigned long flags;						\
									\
	local_irq_save(flags);						\
	if (sel == 0)							\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc0\t%L0, " #source "\n\t"			\
			".set\tmips0"					\
			: : "r" (val));					\
	else								\
		__asm__ __volatile__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc0\t%L0, " #source ", " #sel "\n\t"		\
			".set\tmips0"					\
			: : "r" (val));					\
	local_irq_restore(flags);					\
} while (0)

#define read_c0_index()		__read_32bit_c0_register($0, 0)
#define write_c0_index(val)	__write_32bit_c0_register($0, 0, val)

#define read_c0_entrylo0()	__read_ulong_c0_register($2, 0)
#define write_c0_entrylo0(val)	__write_ulong_c0_register($2, 0, val)

#define read_c0_entrylo1()	__read_ulong_c0_register($3, 0)
#define write_c0_entrylo1(val)	__write_ulong_c0_register($3, 0, val)

#define read_c0_conf()		__read_32bit_c0_register($3, 0)
#define write_c0_conf(val)	__write_32bit_c0_register($3, 0, val)

#define read_c0_context()	__read_ulong_c0_register($4, 0)
#define write_c0_context(val)	__write_ulong_c0_register($4, 0, val)

#define read_c0_pagemask()	__read_32bit_c0_register($5, 0)
#define write_c0_pagemask(val)	__write_32bit_c0_register($5, 0, val)

#define read_c0_wired()		__read_32bit_c0_register($6, 0)
#define write_c0_wired(val)	__write_32bit_c0_register($6, 0, val)

#define read_c0_info()		__read_32bit_c0_register($7, 0)

#define read_c0_cache()		__read_32bit_c0_register($7, 0)	/* TX39xx */
#define write_c0_cache(val)	__write_32bit_c0_register($7, 0, val)

#define read_c0_count()		__read_32bit_c0_register($9, 0)
#define write_c0_count(val)	__write_32bit_c0_register($9, 0, val)

#define read_c0_entryhi()	__read_ulong_c0_register($10, 0)
#define write_c0_entryhi(val)	__write_ulong_c0_register($10, 0, val)

#define read_c0_compare()	__read_32bit_c0_register($11, 0)
#define write_c0_compare(val)	__write_32bit_c0_register($11, 0, val)

#define read_c0_status()	__read_32bit_c0_register($12, 0)
#define write_c0_status(val)	__write_32bit_c0_register($12, 0, val)

#define read_c0_cause()		__read_32bit_c0_register($13, 0)
#define write_c0_cause(val)	__write_32bit_c0_register($13, 0, val)

#define read_c0_prid()		__read_32bit_c0_register($15, 0)

#define read_c0_config()	__read_32bit_c0_register($16, 0)
#define read_c0_config1()	__read_32bit_c0_register($16, 1)
#define read_c0_config2()	__read_32bit_c0_register($16, 2)
#define read_c0_config3()	__read_32bit_c0_register($16, 3)
#define write_c0_config(val)	__write_32bit_c0_register($16, 0, val)
#define write_c0_config1(val)	__write_32bit_c0_register($16, 1, val)
#define write_c0_config2(val)	__write_32bit_c0_register($16, 2, val)
#define write_c0_config3(val)	__write_32bit_c0_register($16, 3, val)

/*
 * The WatchLo register.  There may be upto 8 of them.
 */
#define read_c0_watchlo0()	__read_ulong_c0_register($18, 0)
#define read_c0_watchlo1()	__read_ulong_c0_register($18, 1)
#define read_c0_watchlo2()	__read_ulong_c0_register($18, 2)
#define read_c0_watchlo3()	__read_ulong_c0_register($18, 3)
#define read_c0_watchlo4()	__read_ulong_c0_register($18, 4)
#define read_c0_watchlo5()	__read_ulong_c0_register($18, 5)
#define read_c0_watchlo6()	__read_ulong_c0_register($18, 6)
#define read_c0_watchlo7()	__read_ulong_c0_register($18, 7)
#define write_c0_watchlo0(val)	__write_ulong_c0_register($18, 0, val)
#define write_c0_watchlo1(val)	__write_ulong_c0_register($18, 1, val)
#define write_c0_watchlo2(val)	__write_ulong_c0_register($18, 2, val)
#define write_c0_watchlo3(val)	__write_ulong_c0_register($18, 3, val)
#define write_c0_watchlo4(val)	__write_ulong_c0_register($18, 4, val)
#define write_c0_watchlo5(val)	__write_ulong_c0_register($18, 5, val)
#define write_c0_watchlo6(val)	__write_ulong_c0_register($18, 6, val)
#define write_c0_watchlo7(val)	__write_ulong_c0_register($18, 7, val)

/*
 * The WatchHi register.  There may be upto 8 of them.
 */
#define read_c0_watchhi0()	__read_32bit_c0_register($19, 0)
#define read_c0_watchhi1()	__read_32bit_c0_register($19, 1)
#define read_c0_watchhi2()	__read_32bit_c0_register($19, 2)
#define read_c0_watchhi3()	__read_32bit_c0_register($19, 3)
#define read_c0_watchhi4()	__read_32bit_c0_register($19, 4)
#define read_c0_watchhi5()	__read_32bit_c0_register($19, 5)
#define read_c0_watchhi6()	__read_32bit_c0_register($19, 6)
#define read_c0_watchhi7()	__read_32bit_c0_register($19, 7)

#define write_c0_watchhi0(val)	__write_32bit_c0_register($19, 0, val)
#define write_c0_watchhi1(val)	__write_32bit_c0_register($19, 1, val)
#define write_c0_watchhi2(val)	__write_32bit_c0_register($19, 2, val)
#define write_c0_watchhi3(val)	__write_32bit_c0_register($19, 3, val)
#define write_c0_watchhi4(val)	__write_32bit_c0_register($19, 4, val)
#define write_c0_watchhi5(val)	__write_32bit_c0_register($19, 5, val)
#define write_c0_watchhi6(val)	__write_32bit_c0_register($19, 6, val)
#define write_c0_watchhi7(val)	__write_32bit_c0_register($19, 7, val)

#define read_c0_xcontext()	__read_ulong_c0_register($20, 0)
#define write_c0_xcontext(val)	__write_ulong_c0_register($20, 0, val)

#define read_c0_intcontrol()	__read_32bit_c0_register($20, 1)
#define write_c0_intcontrol(val) __write_32bit_c0_register($20, 1, val)

#define read_c0_framemask()	__read_32bit_c0_register($21, 0)
#define write_c0_framemask(val)	__write_32bit_c0_register($21, 0, val)

#define read_c0_debug()		__read_32bit_c0_register($23, 0)
#define write_c0_debug(val)	__write_32bit_c0_register($23, 0, val)

#define read_c0_depc()		__read_ulong_c0_register($24, 0)
#define write_c0_depc(val)	__write_ulong_c0_register($24, 0, val)

#define read_c0_ecc()		__read_32bit_c0_register($26, 0)
#define write_c0_ecc(val)	__write_32bit_c0_register($26, 0, val)

#define read_c0_derraddr0()	__read_ulong_c0_register($26, 1)
#define write_c0_derraddr0(val)	__write_ulong_c0_register($26, 1, val)

#define read_c0_cacheerr()	__read_32bit_c0_register($27, 0)

#define read_c0_derraddr1()	__read_ulong_c0_register($27, 1)
#define write_c0_derraddr1(val)	__write_ulong_c0_register($27, 1, val)

#define read_c0_taglo()		__read_32bit_c0_register($28, 0)
#define write_c0_taglo(val)	__write_32bit_c0_register($28, 0, val)

#define read_c0_taghi()		__read_32bit_c0_register($29, 0)
#define write_c0_taghi(val)	__write_32bit_c0_register($29, 0, val)

#define read_c0_errorepc()	__read_ulong_c0_register($30, 0)
#define write_c0_errorepc(val)	__write_ulong_c0_register($30, 0, val)

#define read_c0_epc()		__read_ulong_c0_register($14, 0)
#define write_c0_epc(val)	__write_ulong_c0_register($14, 0, val)

#if 1
/*
 * Macros to access the system control coprocessor
 */
#define read_32bit_cp0_register(source)                         \
({ int __res;                                                   \
        __asm__ __volatile__(                                   \
	".set\tpush\n\t"					\
	".set\treorder\n\t"					\
        "mfc0\t%0,"STR(source)"\n\t"                            \
	".set\tpop"						\
        : "=r" (__res));                                        \
        __res;})

#define read_32bit_cp0_set1_register(source)                    \
({ int __res;                                                   \
        __asm__ __volatile__(                                   \
	".set\tpush\n\t"					\
	".set\treorder\n\t"					\
        "cfc0\t%0,"STR(source)"\n\t"                            \
	".set\tpop"						\
        : "=r" (__res));                                        \
        __res;})

/*
 * For now use this only with interrupts disabled!
 */
#define read_64bit_cp0_register(source)                         \
({ int __res;                                                   \
        __asm__ __volatile__(                                   \
        ".set\tmips3\n\t"                                       \
        "dmfc0\t%0,"STR(source)"\n\t"                           \
        ".set\tmips0"                                           \
        : "=r" (__res));                                        \
        __res;})

#define write_32bit_cp0_register(register,value)                \
        __asm__ __volatile__(                                   \
        "mtc0\t%0,"STR(register)"\n\t"				\
	"nop"							\
        : : "r" (value));

#define write_32bit_cp0_set1_register(register,value)           \
        __asm__ __volatile__(                                   \
        "ctc0\t%0,"STR(register)"\n\t"				\
	"nop"							\
        : : "r" (value));

#define write_64bit_cp0_register(register,value)                \
        __asm__ __volatile__(                                   \
        ".set\tmips3\n\t"                                       \
        "dmtc0\t%0,"STR(register)"\n\t"                         \
        ".set\tmips0"                                           \
        : : "r" (value))

/*
 * This should be changed when we get a compiler that support the MIPS32 ISA.
 */
#define read_mips32_cp0_config1()                               \
({ int __res;                                                   \
        __asm__ __volatile__(                                   \
	".set\tnoreorder\n\t"                                   \
	".set\tnoat\n\t"                                        \
	"#.set\tmips64\n\t"					\
	"#mfc0\t$1, $16, 1\n\t"					\
	"#.set\tmips0\n\t"					\
     	".word\t0x40018001\n\t"                                 \
	"move\t%0,$1\n\t"                                       \
	".set\tat\n\t"                                          \
	".set\treorder"                                         \
	:"=r" (__res));                                         \
        __res;})

#endif
/*
 * Macros to access the floating point coprocessor control registers
 */
#define read_32bit_cp1_register(source)                         \
({ int __res;                                                   \
	__asm__ __volatile__(                                   \
	".set\tpush\n\t"					\
	".set\treorder\n\t"					\
        "cfc1\t%0,"STR(source)"\n\t"                            \
	".set\tpop"						\
        : "=r" (__res));                                        \
        __res;})

/* TLB operations. */
static inline void tlb_probe(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbp\n\t"
		".set reorder");
}

static inline void tlb_read(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbr\n\t"
		".set reorder");
}

static inline void tlb_write_indexed(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbwi\n\t"
		".set reorder");
}

static inline void tlb_write_random(void)
{
	__asm__ __volatile__(
		".set noreorder\n\t"
		"tlbwr\n\t"
		".set reorder");
}

/*
 * Manipulate bits in a c0 register.
 */
#define __BUILD_SET_C0(name,register)				\
static inline unsigned int					\
set_c0_##name(unsigned int set)					\
{								\
	unsigned int res;					\
								\
	res = read_c0_##name();					\
	res |= set;						\
	write_c0_##name(res);					\
								\
	return res;						\
}								\
								\
static inline unsigned int					\
clear_c0_##name(unsigned int clear)				\
{								\
	unsigned int res;					\
								\
	res = read_c0_##name();					\
	res &= ~clear;						\
	write_c0_##name(res);					\
								\
	return res;						\
}								\
								\
static inline unsigned int					\
change_c0_##name(unsigned int change, unsigned int new)		\
{								\
	unsigned int res;					\
								\
	res = read_c0_##name();					\
	res &= ~change;						\
	res |= (new & change);					\
	write_c0_##name(res);					\
								\
	return res;						\
}

__BUILD_SET_C0(status,CP0_STATUS)
__BUILD_SET_C0(cause,CP0_CAUSE)
__BUILD_SET_C0(config,CP0_CONFIG)

#define set_cp0_status(x)	set_c0_status(x)
#define set_cp0_cause(x)	set_c0_cause(x)
#define set_cp0_config(x)	set_c0_config(x)

#endif /* !__ASSEMBLY__ */

#endif /* _MIPS_REGS_H_ */
