/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef _MIPS_REGS_H_
#define _MIPS_REGS_H_
#include <rtconfig.h>
#define REG_A0  4
#define REG_SP  29
#define REG_GP  28
#define REG_FP  30
#define REG_RA  31

#ifndef ARCH_MIPS64
#define zero    $0  /* wired zero */
#define AT  $1  /* assembler temp  - uppercase because of ".set at" */
#define v0  $2  /* return value */
#define v1  $3
#define a0  $4  /* argument registers */
#define a1  $5
#define a2  $6
#define a3  $7
#define t0  $8  /* caller saved */
#define t1  $9
#define t2  $10
#define t3  $11
#define t4  $12
#define ta0 $12
#define t5  $13
#define ta1 $13
#define t6  $14
#define ta2 $14
#define t7  $15
#define ta3 $15
#define s0  $16 /* callee saved */
#define s1  $17
#define s2  $18
#define s3  $19
#define s4  $20
#define s5  $21
#define s6  $22
#define s7  $23
#define t8  $24 /* caller saved */
#define t9  $25
#define jp  $25 /* PIC jump register */
#define k0  $26 /* kernel scratch */
#define k1  $27
#define gp  $28 /* global pointer */
#define sp  $29 /* stack pointer */
#define fp  $30 /* frame pointer */
#define s8  $30 /* same like fp! */
#define ra  $31 /* return address */

#else

#define zero    $0  /* wired zero */
#define AT  $at /* assembler temp - uppercase because of ".set at" */
#define v0  $2  /* return value - caller saved */
#define v1  $3
#define a0  $4  /* argument registers */
#define a1  $5
#define a2  $6
#define a3  $7
#define a4  $8  /* arg reg 64 bit; caller saved in 32 bit */
#define ta0 $8
#define a5  $9
#define ta1 $9
#define a6  $10
#define ta2 $10
#define a7  $11
#define ta3 $11
#define t0  $12 /* caller saved */
#define t1  $13
#define t2  $14
#define t3  $15
#define s0  $16 /* callee saved */
#define s1  $17
#define s2  $18
#define s3  $19
#define s4  $20
#define s5  $21
#define s6  $22
#define s7  $23
#define t8  $24 /* caller saved */
#define t9  $25 /* callee address for PIC/temp */
#define jp  $25 /* PIC jump register */
#define k0  $26 /* kernel temporary */
#define k1  $27
#define gp  $28 /* global pointer - caller saved for PIC */
#define sp  $29 /* stack pointer */
#define fp  $30 /* frame pointer */
#define s8  $30 /* callee saved */
#define ra  $31 /* return address */

#endif

#define fv0 $f0  /* return value */
#define fv0f    $f1
#define fv1 $f2
#define fv1f    $f3
#define fa0 $f12     /* argument registers */
#define fa0f    $f13
#define fa1 $f14
#define fa1f    $f15
#define ft0 $f4  /* caller saved */
#define ft0f    $f5
#define ft1 $f6
#define ft1f    $f7
#define ft2 $f8
#define ft2f    $f9
#define ft3 $f10
#define ft3f    $f11
#define ft4 $f16
#define ft4f    $f17
#define ft5 $f18
#define ft5f    $f19
#define fs0 $f20     /* callee saved */
#define fs0f    $f21
#define fs1 $f22
#define fs1f    $f23
#define fs2 $f24
#define fs2f    $f25
#define fs3 $f26
#define fs3f    $f27
#define fs4 $f28
#define fs4f    $f29
#define fs5 $f30
#define fs5f    $f31

#define fcr31   $31  /* FPU status register */


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
#define CP0_TX39_CACHE  $7

/*
 * Coprocessor 1 (FPU) register names
 */
#define CP1_REVISION    $0
#define CP1_UFR     $1
#define CP1_UNFR    $4
#define CP1_FCCR    $25
#define CP1_FEXR    $26
#define CP1_FENR    $28
#define CP1_STATUS  $31


/*
 * Bits in the MIPS32/64 coprocessor 1 (FPU) revision register.
 */
#define MIPS_FPIR_S     (_ULCAST_(1) << 16)
#define MIPS_FPIR_D     (_ULCAST_(1) << 17)
#define MIPS_FPIR_PS        (_ULCAST_(1) << 18)
#define MIPS_FPIR_3D        (_ULCAST_(1) << 19)
#define MIPS_FPIR_W     (_ULCAST_(1) << 20)
#define MIPS_FPIR_L     (_ULCAST_(1) << 21)
#define MIPS_FPIR_F64       (_ULCAST_(1) << 22)
#define MIPS_FPIR_HAS2008   (_ULCAST_(1) << 23)
#define MIPS_FPIR_UFRP      (_ULCAST_(1) << 28)
#define MIPS_FPIR_FREP      (_ULCAST_(1) << 29)

/*
 * Bits in the MIPS32/64 coprocessor 1 (FPU) condition codes register.
 */
#define MIPS_FCCR_CONDX_S   0
#define MIPS_FCCR_CONDX     (_ULCAST_(255) << MIPS_FCCR_CONDX_S)
#define MIPS_FCCR_COND0_S   0
#define MIPS_FCCR_COND0     (_ULCAST_(1) << MIPS_FCCR_COND0_S)
#define MIPS_FCCR_COND1_S   1
#define MIPS_FCCR_COND1     (_ULCAST_(1) << MIPS_FCCR_COND1_S)
#define MIPS_FCCR_COND2_S   2
#define MIPS_FCCR_COND2     (_ULCAST_(1) << MIPS_FCCR_COND2_S)
#define MIPS_FCCR_COND3_S   3
#define MIPS_FCCR_COND3     (_ULCAST_(1) << MIPS_FCCR_COND3_S)
#define MIPS_FCCR_COND4_S   4
#define MIPS_FCCR_COND4     (_ULCAST_(1) << MIPS_FCCR_COND4_S)
#define MIPS_FCCR_COND5_S   5
#define MIPS_FCCR_COND5     (_ULCAST_(1) << MIPS_FCCR_COND5_S)
#define MIPS_FCCR_COND6_S   6
#define MIPS_FCCR_COND6     (_ULCAST_(1) << MIPS_FCCR_COND6_S)
#define MIPS_FCCR_COND7_S   7
#define MIPS_FCCR_COND7     (_ULCAST_(1) << MIPS_FCCR_COND7_S)

/*
 * Bits in the MIPS32/64 coprocessor 1 (FPU) enables register.
 */
#define MIPS_FENR_FS_S      2
#define MIPS_FENR_FS        (_ULCAST_(1) << MIPS_FENR_FS_S)

/*
 * FPU Status Register Values
 */
#define FPU_CSR_COND_S  23                  /* $fcc0 */
#define FPU_CSR_COND    (_ULCAST_(1) << FPU_CSR_COND_S)

#define FPU_CSR_FS_S    24      /* flush denormalised results to 0 */
#define FPU_CSR_FS  (_ULCAST_(1) << FPU_CSR_FS_S)

#define FPU_CSR_FO      0x00400000
#define FPU_CSR_FN      0x00200000

#define FPU_CSR_CONDX_S 25                  /* $fcc[7:1] */
#define FPU_CSR_CONDX   (_ULCAST_(127) << FPU_CSR_CONDX_S)
#define FPU_CSR_COND1_S 25                  /* $fcc1 */
#define FPU_CSR_COND1   (_ULCAST_(1) << FPU_CSR_COND1_S)
#define FPU_CSR_COND2_S 26                  /* $fcc2 */
#define FPU_CSR_COND2   (_ULCAST_(1) << FPU_CSR_COND2_S)
#define FPU_CSR_COND3_S 27                  /* $fcc3 */
#define FPU_CSR_COND3   (_ULCAST_(1) << FPU_CSR_COND3_S)
#define FPU_CSR_COND4_S 28                  /* $fcc4 */
#define FPU_CSR_COND4   (_ULCAST_(1) << FPU_CSR_COND4_S)
#define FPU_CSR_COND5_S 29                  /* $fcc5 */
#define FPU_CSR_COND5   (_ULCAST_(1) << FPU_CSR_COND5_S)
#define FPU_CSR_COND6_S 30                  /* $fcc6 */
#define FPU_CSR_COND6   (_ULCAST_(1) << FPU_CSR_COND6_S)
#define FPU_CSR_COND7_S 31                  /* $fcc7 */
#define FPU_CSR_COND7   (_ULCAST_(1) << FPU_CSR_COND7_S)

/*
 * Bits 22:20 of the FPU Status Register will be read as 0,
 * and should be written as zero.
 */
#define FPU_CSR_RSVD    (_ULCAST_(7) << 20)

#define FPU_CSR_ABS2008 (_ULCAST_(1) << 19)
#define FPU_CSR_NAN2008 (_ULCAST_(1) << 18)

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

/* Bits 0 and 1 of FPU Status Register specify the rounding mode */
#define FPU_CSR_RM  0x00000003
#define FPU_CSR_RN  0x0 /* nearest */
#define FPU_CSR_RZ  0x1 /* towards zero */
#define FPU_CSR_RU  0x2 /* towards +Infinity */
#define FPU_CSR_RD  0x3 /* towards -Infinity */

#define PM_4K       0x00000000
#define PM_16K      0x00006000
#define PM_64K      0x0001e000
#define PM_256K     0x0007e000
#define PM_1M       0x001fe000
#define PM_4M       0x007fe000
#define PM_16M      0x01ffe000
#define PM_64M      0x07ffe000
#define PM_256M     0x1fffe000


/*
 * Values used for computation of new tlb entries
 */
#define PL_4K       12
#define PL_16K      14
#define PL_64K      16
#define PL_256K     18
#define PL_1M       20
#define PL_4M       22
#define PL_16M      24
#define PL_64M      26
#define PL_256M     28

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
#define ST0_IE          0x00000001
#define ST0_EXL         0x00000002
#define ST0_ERL         0x00000004
#define ST0_KSU         0x00000018
#  define KSU_USER      0x00000010
#  define KSU_SUPERVISOR    0x00000008
#  define KSU_KERNEL        0x00000000
#define ST0_UX          0x00000020
#define ST0_SX          0x00000040
#define ST0_KX          0x00000080
#define ST0_DE          0x00010000
#define ST0_CE          0x00020000

/*
 * Bitfields in the R[23]000 cp0 status register.
 */
#define ST0_IEC                 0x00000001
#define ST0_KUC         0x00000002
#define ST0_IEP         0x00000004
#define ST0_KUP         0x00000008
#define ST0_IEO         0x00000010
#define ST0_KUO         0x00000020
/* bits 6 & 7 are reserved on R[23]000 */
#define ST0_ISC         0x00010000
#define ST0_SWC         0x00020000
#define ST0_CM          0x00080000

/*
 * Bits specific to the R4640/R4650
 */
#define ST0_UM          (_ULCAST_(1) <<  4)
#define ST0_IL          (_ULCAST_(1) << 23)
#define ST0_DL          (_ULCAST_(1) << 24)


/*
 * Status register bits available in all MIPS CPUs.
 */
#define ST0_IM          0x0000ff00
#define  STATUSB_IP0        8
#define  STATUSF_IP0        (_ULCAST_(1) <<  8)
#define  STATUSB_IP1        9
#define  STATUSF_IP1        (_ULCAST_(1) <<  9)
#define  STATUSB_IP2        10
#define  STATUSF_IP2        (_ULCAST_(1) << 10)
#define  STATUSB_IP3        11
#define  STATUSF_IP3        (_ULCAST_(1) << 11)
#define  STATUSB_IP4        12
#define  STATUSF_IP4        (_ULCAST_(1) << 12)
#define  STATUSB_IP5        13
#define  STATUSF_IP5        (_ULCAST_(1) << 13)
#define  STATUSB_IP6        14
#define  STATUSF_IP6        (_ULCAST_(1) << 14)
#define  STATUSB_IP7        15
#define  STATUSF_IP7        (_ULCAST_(1) << 15)
#define  STATUSB_IP8        0
#define  STATUSF_IP8        (_ULCAST_(1) <<  0)
#define  STATUSB_IP9        1
#define  STATUSF_IP9        (_ULCAST_(1) <<  1)
#define  STATUSB_IP10       2
#define  STATUSF_IP10       (_ULCAST_(1) <<  2)
#define  STATUSB_IP11       3
#define  STATUSF_IP11       (_ULCAST_(1) <<  3)
#define  STATUSB_IP12       4
#define  STATUSF_IP12       (_ULCAST_(1) <<  4)
#define  STATUSB_IP13       5
#define  STATUSF_IP13       (_ULCAST_(1) <<  5)
#define  STATUSB_IP14       6
#define  STATUSF_IP14       (_ULCAST_(1) <<  6)
#define  STATUSB_IP15       7
#define  STATUSF_IP15       (_ULCAST_(1) <<  7)
#define ST0_CH          0x00040000
#define ST0_SR          0x00100000
#define ST0_TS          0x00200000
#define ST0_BEV         0x00400000
#define ST0_RE          0x02000000
#define ST0_FR          0x04000000
#define ST0_CU          0xf0000000
#define ST0_CU0         0x10000000
#define ST0_CU1         0x20000000
#define ST0_CU1_SHIFT           29
#define ST0_CU2         0x40000000
#define ST0_CU3         0x80000000
#define ST0_XX          0x80000000  /* MIPS IV naming */

/*
 * Bitfields and bit numbers in the coprocessor 0 cause register.
 *
 * Refer to your MIPS R4xx0 manual, chapter 5 for explanation.
 */
#define  CAUSEB_EXCCODE     2
#define  CAUSEF_EXCCODE     (_ULCAST_(31)  <<  2)
#define  CAUSEB_IP      8
#define  CAUSEF_IP      (_ULCAST_(255) <<  8)
#define  CAUSEB_IP0     8
#define  CAUSEF_IP0     (_ULCAST_(1)   <<  8)
#define  CAUSEB_IP1     9
#define  CAUSEF_IP1     (_ULCAST_(1)   <<  9)
#define  CAUSEB_IP2     10
#define  CAUSEF_IP2     (_ULCAST_(1)   << 10)
#define  CAUSEB_IP3     11
#define  CAUSEF_IP3     (_ULCAST_(1)   << 11)
#define  CAUSEB_IP4     12
#define  CAUSEF_IP4     (_ULCAST_(1)   << 12)
#define  CAUSEB_IP5     13
#define  CAUSEF_IP5     (_ULCAST_(1)   << 13)
#define  CAUSEB_IP6     14
#define  CAUSEF_IP6     (_ULCAST_(1)   << 14)
#define  CAUSEB_IP7     15
#define  CAUSEF_IP7     (_ULCAST_(1)   << 15)
#define  CAUSEB_IV      23
#define  CAUSEF_IV      (_ULCAST_(1)   << 23)
#define  CAUSEB_CE      28
#define  CAUSEF_CE      (_ULCAST_(3)   << 28)
#define  CAUSEB_BD      31
#define  CAUSEF_BD      (_ULCAST_(1)   << 31)

/*
 * Bits in the coprocessor 0 config register.
 */
/* Generic bits.  */
#define CONF_CM_CACHABLE_NO_WA      0
#define CONF_CM_CACHABLE_WA     1
#define CONF_CM_UNCACHED        2
#define CONF_CM_CACHABLE_NONCOHERENT    3
#define CONF_CM_CACHABLE_CE     4
#define CONF_CM_CACHABLE_COW        5
#define CONF_CM_CACHABLE_CUW        6
#define CONF_CM_CACHABLE_ACCELERATED    7
#define CONF_CM_CMASK           7
#define CONF_BE         (_ULCAST_(1) << 15)

/* Bits common to various processors.  */
#define CONF_CU         (_ULCAST_(1) <<  3)
#define CONF_DB         (_ULCAST_(1) <<  4)
#define CONF_IB         (_ULCAST_(1) <<  5)
#define CONF_DC         (_ULCAST_(7) <<  6)
#define CONF_IC         (_ULCAST_(7) <<  9)
#define CONF_EB         (_ULCAST_(1) << 13)
#define CONF_EM         (_ULCAST_(1) << 14)
#define CONF_SM         (_ULCAST_(1) << 16)
#define CONF_SC         (_ULCAST_(1) << 17)
#define CONF_EW         (_ULCAST_(3) << 18)
#define CONF_EP         (_ULCAST_(15)<< 24)
#define CONF_EC         (_ULCAST_(7) << 28)
#define CONF_CM         (_ULCAST_(1) << 31)

/* Bits specific to the R4xx0.  */
#define R4K_CONF_SW     (_ULCAST_(1) << 20)
#define R4K_CONF_SS     (_ULCAST_(1) << 21)
#define R4K_CONF_SB     (_ULCAST_(3) << 22)

/* Bits specific to the R5000.  */
#define R5K_CONF_SE     (_ULCAST_(1) << 12)
#define R5K_CONF_SS     (_ULCAST_(3) << 20)

/* Bits specific to the R10000.  */
#define R10K_CONF_DN        (_ULCAST_(3) <<  3)
#define R10K_CONF_CT        (_ULCAST_(1) <<  5)
#define R10K_CONF_PE        (_ULCAST_(1) <<  6)
#define R10K_CONF_PM        (_ULCAST_(3) <<  7)
#define R10K_CONF_EC        (_ULCAST_(15)<<  9)
#define R10K_CONF_SB        (_ULCAST_(1) << 13)
#define R10K_CONF_SK        (_ULCAST_(1) << 14)
#define R10K_CONF_SS        (_ULCAST_(7) << 16)
#define R10K_CONF_SC        (_ULCAST_(7) << 19)
#define R10K_CONF_DC        (_ULCAST_(7) << 26)
#define R10K_CONF_IC        (_ULCAST_(7) << 29)

/* Bits specific to the VR41xx.  */
#define VR41_CONF_CS        (_ULCAST_(1) << 12)
#define VR41_CONF_M16       (_ULCAST_(1) << 20)
#define VR41_CONF_AD        (_ULCAST_(1) << 23)

/* Bits specific to the R30xx.  */
#define R30XX_CONF_FDM      (_ULCAST_(1) << 19)
#define R30XX_CONF_REV      (_ULCAST_(1) << 22)
#define R30XX_CONF_AC       (_ULCAST_(1) << 23)
#define R30XX_CONF_RF       (_ULCAST_(1) << 24)
#define R30XX_CONF_HALT     (_ULCAST_(1) << 25)
#define R30XX_CONF_FPINT    (_ULCAST_(7) << 26)
#define R30XX_CONF_DBR      (_ULCAST_(1) << 29)
#define R30XX_CONF_SB       (_ULCAST_(1) << 30)
#define R30XX_CONF_LOCK     (_ULCAST_(1) << 31)

/* Bits specific to the TX49.  */
#define TX49_CONF_DC        (_ULCAST_(1) << 16)
#define TX49_CONF_IC        (_ULCAST_(1) << 17)  /* conflict with CONF_SC */
#define TX49_CONF_HALT      (_ULCAST_(1) << 18)
#define TX49_CONF_CWFON     (_ULCAST_(1) << 27)

/* Bits specific to the MIPS32/64 PRA.  */
#define MIPS_CONF_MT        (_ULCAST_(7) <<  7)
#define MIPS_CONF_AR        (_ULCAST_(7) << 10)
#define MIPS_CONF_AT        (_ULCAST_(3) << 13)
#define MIPS_CONF_M     (_ULCAST_(1) << 31)

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
#define CE0_CYCLES          0
#define CE0_INSN_ISSUED         1
#define CE0_LPSC_ISSUED         2
#define CE0_S_ISSUED            3
#define CE0_SC_ISSUED           4
#define CE0_SC_FAILED           5
#define CE0_BRANCH_DECODED      6
#define CE0_QW_WB_SECONDARY     7
#define CE0_CORRECTED_ECC_ERRORS    8
#define CE0_ICACHE_MISSES       9
#define CE0_SCACHE_I_MISSES     10
#define CE0_SCACHE_I_WAY_MISSPREDICTED  11
#define CE0_EXT_INTERVENTIONS_REQ   12
#define CE0_EXT_INVALIDATE_REQ      13
#define CE0_VIRTUAL_COHERENCY_COND  14
#define CE0_INSN_GRADUATED      15

/*
 * Events counted by counter #1
 */
#define CE1_CYCLES          0
#define CE1_INSN_GRADUATED      1
#define CE1_LPSC_GRADUATED      2
#define CE1_S_GRADUATED         3
#define CE1_SC_GRADUATED        4
#define CE1_FP_INSN_GRADUATED       5
#define CE1_QW_WB_PRIMARY       6
#define CE1_TLB_REFILL          7
#define CE1_BRANCH_MISSPREDICTED    8
#define CE1_DCACHE_MISS         9
#define CE1_SCACHE_D_MISSES     10
#define CE1_SCACHE_D_WAY_MISSPREDICTED  11
#define CE1_EXT_INTERVENTION_HITS   12
#define CE1_EXT_INVALIDATE_REQ      13
#define CE1_SP_HINT_TO_CEXCL_SC_BLOCKS  14
#define CE1_SP_HINT_TO_SHARED_SC_BLOCKS 15

/*
 * These flags define in which priviledge mode the counters count events
 */
#define CEB_USER    8   /* Count events in user mode, EXL = ERL = 0 */
#define CEB_SUPERVISOR  4   /* Count events in supvervisor mode EXL = ERL = 0 */
#define CEB_KERNEL  2   /* Count events in kernel mode EXL = ERL = 0 */
#define CEB_EXL     1   /* Count events with EXL = 1, ERL = 0 */

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

#define __read_32bit_c0_register(source, sel)               \
({ int __res;                               \
    if (sel == 0)                           \
        __asm__ __volatile__(                   \
            "mfc0\t%0, " #source "\n\t"         \
            : "=r" (__res));                \
    else                                \
        __asm__ __volatile__(                   \
            ".set\tmips32\n\t"              \
            "mfc0\t%0, " #source ", " #sel "\n\t"       \
            ".set\tmips0\n\t"               \
            : "=r" (__res));                \
    __res;                              \
})

#define __read_64bit_c0_register(source, sel)               \
({ unsigned long __res;                         \
    if (sel == 0)                           \
        __asm__ __volatile__(                   \
            ".set\tmips3\n\t"               \
            "dmfc0\t%0, " #source "\n\t"            \
            ".set\tmips0"                   \
            : "=r" (__res));                \
    else                                \
        __asm__ __volatile__(                   \
            ".set\tmips64\n\t"              \
            "dmfc0\t%0, " #source ", " #sel "\n\t"      \
            ".set\tmips0"                   \
            : "=r" (__res));                \
    __res;                              \
})

#define __write_32bit_c0_register(register, sel, value)         \
do {                                    \
    if (sel == 0)                           \
        __asm__ __volatile__(                   \
            "mtc0\t%z0, " #register "\n\t"          \
            : : "Jr" (value));              \
    else                                \
        __asm__ __volatile__(                   \
            ".set\tmips32\n\t"              \
            "mtc0\t%z0, " #register ", " #sel "\n\t"    \
            ".set\tmips0"                   \
            : : "Jr" (value));              \
} while (0)

#define __write_64bit_c0_register(register, sel, value)         \
do {                                    \
    if (sel == 0)                           \
        __asm__ __volatile__(                   \
            ".set\tmips3\n\t"               \
            "dmtc0\t%z0, " #register "\n\t"         \
            ".set\tmips0"                   \
            : : "Jr" (value));              \
    else                                \
        __asm__ __volatile__(                   \
            ".set\tmips64\n\t"              \
            "dmtc0\t%z0, " #register ", " #sel "\n\t"   \
            ".set\tmips0"                   \
            : : "Jr" (value));              \
} while (0)

#define __read_ulong_c0_register(reg, sel)              \
    ((sizeof(unsigned long) == 4) ?                 \
    __read_32bit_c0_register(reg, sel) :                \
    __read_64bit_c0_register(reg, sel))

#define __write_ulong_c0_register(reg, sel, val)            \
do {                                    \
    if (sizeof(unsigned long) == 4)                 \
        __write_32bit_c0_register(reg, sel, val);       \
    else                                \
        __write_64bit_c0_register(reg, sel, val);       \
} while (0)

/*
 * These versions are only needed for systems with more than 38 bits of
 * physical address space running the 32-bit kernel.  That's none atm :-)
 */
#define __read_64bit_c0_split(source, sel)              \
({                                  \
    unsigned long long val;                     \
    unsigned long flags;                        \
                                    \
    local_irq_save(flags);                      \
    if (sel == 0)                           \
        __asm__ __volatile__(                   \
            ".set\tmips64\n\t"              \
            "dmfc0\t%M0, " #source "\n\t"           \
            "dsll\t%L0, %M0, 32\n\t"            \
            "dsrl\t%M0, %M0, 32\n\t"            \
            "dsrl\t%L0, %L0, 32\n\t"            \
            ".set\tmips0"                   \
            : "=r" (val));                  \
    else                                \
        __asm__ __volatile__(                   \
            ".set\tmips64\n\t"              \
            "dmfc0\t%M0, " #source ", " #sel "\n\t"     \
            "dsll\t%L0, %M0, 32\n\t"            \
            "dsrl\t%M0, %M0, 32\n\t"            \
            "dsrl\t%L0, %L0, 32\n\t"            \
            ".set\tmips0"                   \
            : "=r" (val));                  \
    local_irq_restore(flags);                   \
                                    \
    val;                                \
})

#define __write_64bit_c0_split(source, sel, val)            \
do {                                    \
    unsigned long flags;                        \
                                    \
    local_irq_save(flags);                      \
    if (sel == 0)                           \
        __asm__ __volatile__(                   \
            ".set\tmips64\n\t"              \
            "dsll\t%L0, %L0, 32\n\t"            \
            "dsrl\t%L0, %L0, 32\n\t"            \
            "dsll\t%M0, %M0, 32\n\t"            \
            "or\t%L0, %L0, %M0\n\t"             \
            "dmtc0\t%L0, " #source "\n\t"           \
            ".set\tmips0"                   \
            : : "r" (val));                 \
    else                                \
        __asm__ __volatile__(                   \
            ".set\tmips64\n\t"              \
            "dsll\t%L0, %L0, 32\n\t"            \
            "dsrl\t%L0, %L0, 32\n\t"            \
            "dsll\t%M0, %M0, 32\n\t"            \
            "or\t%L0, %L0, %M0\n\t"             \
            "dmtc0\t%L0, " #source ", " #sel "\n\t"     \
            ".set\tmips0"                   \
            : : "r" (val));                 \
    local_irq_restore(flags);                   \
} while (0)

#define read_c0_index()     __read_32bit_c0_register($0, 0)
#define write_c0_index(val) __write_32bit_c0_register($0, 0, val)

#define read_c0_entrylo0()  __read_ulong_c0_register($2, 0)
#define write_c0_entrylo0(val)  __write_ulong_c0_register($2, 0, val)

#define read_c0_entrylo1()  __read_ulong_c0_register($3, 0)
#define write_c0_entrylo1(val)  __write_ulong_c0_register($3, 0, val)

#define read_c0_conf()      __read_32bit_c0_register($3, 0)
#define write_c0_conf(val)  __write_32bit_c0_register($3, 0, val)

#define read_c0_context()   __read_ulong_c0_register($4, 0)
#define write_c0_context(val)   __write_ulong_c0_register($4, 0, val)

#define read_c0_pagemask()  __read_32bit_c0_register($5, 0)
#define write_c0_pagemask(val)  __write_32bit_c0_register($5, 0, val)

#define read_c0_wired()     __read_32bit_c0_register($6, 0)
#define write_c0_wired(val) __write_32bit_c0_register($6, 0, val)

#define read_c0_info()      __read_32bit_c0_register($7, 0)

#define read_c0_cache()     __read_32bit_c0_register($7, 0) /* TX39xx */
#define write_c0_cache(val) __write_32bit_c0_register($7, 0, val)

#define read_c0_count()     __read_32bit_c0_register($9, 0)
#define write_c0_count(val) __write_32bit_c0_register($9, 0, val)

#define read_c0_entryhi()   __read_ulong_c0_register($10, 0)
#define write_c0_entryhi(val)   __write_ulong_c0_register($10, 0, val)

#define read_c0_compare()   __read_32bit_c0_register($11, 0)
#define write_c0_compare(val)   __write_32bit_c0_register($11, 0, val)

#define read_c0_status()    __read_32bit_c0_register($12, 0)
#define write_c0_status(val)    __write_32bit_c0_register($12, 0, val)

#define read_c0_cause()     __read_32bit_c0_register($13, 0)
#define write_c0_cause(val) __write_32bit_c0_register($13, 0, val)

#define read_c0_prid()      __read_32bit_c0_register($15, 0)

#define read_c0_ebase()     __read_32bit_c0_register($15, 1)
#define write_c0_ebase(val) __write_32bit_c0_register($15, 1, val)

#define read_c0_config()    __read_32bit_c0_register($16, 0)
#define read_c0_config1()   __read_32bit_c0_register($16, 1)
#define read_c0_config2()   __read_32bit_c0_register($16, 2)
#define read_c0_config3()   __read_32bit_c0_register($16, 3)
#define write_c0_config(val)    __write_32bit_c0_register($16, 0, val)
#define write_c0_config1(val)   __write_32bit_c0_register($16, 1, val)
#define write_c0_config2(val)   __write_32bit_c0_register($16, 2, val)
#define write_c0_config3(val)   __write_32bit_c0_register($16, 3, val)

/*
 * The WatchLo register.  There may be upto 8 of them.
 */
#define read_c0_watchlo0()  __read_ulong_c0_register($18, 0)
#define read_c0_watchlo1()  __read_ulong_c0_register($18, 1)
#define read_c0_watchlo2()  __read_ulong_c0_register($18, 2)
#define read_c0_watchlo3()  __read_ulong_c0_register($18, 3)
#define read_c0_watchlo4()  __read_ulong_c0_register($18, 4)
#define read_c0_watchlo5()  __read_ulong_c0_register($18, 5)
#define read_c0_watchlo6()  __read_ulong_c0_register($18, 6)
#define read_c0_watchlo7()  __read_ulong_c0_register($18, 7)
#define write_c0_watchlo0(val)  __write_ulong_c0_register($18, 0, val)
#define write_c0_watchlo1(val)  __write_ulong_c0_register($18, 1, val)
#define write_c0_watchlo2(val)  __write_ulong_c0_register($18, 2, val)
#define write_c0_watchlo3(val)  __write_ulong_c0_register($18, 3, val)
#define write_c0_watchlo4(val)  __write_ulong_c0_register($18, 4, val)
#define write_c0_watchlo5(val)  __write_ulong_c0_register($18, 5, val)
#define write_c0_watchlo6(val)  __write_ulong_c0_register($18, 6, val)
#define write_c0_watchlo7(val)  __write_ulong_c0_register($18, 7, val)

/*
 * The WatchHi register.  There may be upto 8 of them.
 */
#define read_c0_watchhi0()  __read_32bit_c0_register($19, 0)
#define read_c0_watchhi1()  __read_32bit_c0_register($19, 1)
#define read_c0_watchhi2()  __read_32bit_c0_register($19, 2)
#define read_c0_watchhi3()  __read_32bit_c0_register($19, 3)
#define read_c0_watchhi4()  __read_32bit_c0_register($19, 4)
#define read_c0_watchhi5()  __read_32bit_c0_register($19, 5)
#define read_c0_watchhi6()  __read_32bit_c0_register($19, 6)
#define read_c0_watchhi7()  __read_32bit_c0_register($19, 7)

#define write_c0_watchhi0(val)  __write_32bit_c0_register($19, 0, val)
#define write_c0_watchhi1(val)  __write_32bit_c0_register($19, 1, val)
#define write_c0_watchhi2(val)  __write_32bit_c0_register($19, 2, val)
#define write_c0_watchhi3(val)  __write_32bit_c0_register($19, 3, val)
#define write_c0_watchhi4(val)  __write_32bit_c0_register($19, 4, val)
#define write_c0_watchhi5(val)  __write_32bit_c0_register($19, 5, val)
#define write_c0_watchhi6(val)  __write_32bit_c0_register($19, 6, val)
#define write_c0_watchhi7(val)  __write_32bit_c0_register($19, 7, val)

#define read_c0_xcontext()  __read_ulong_c0_register($20, 0)
#define write_c0_xcontext(val)  __write_ulong_c0_register($20, 0, val)

#define read_c0_intcontrol()    __read_32bit_c0_register($20, 1)
#define write_c0_intcontrol(val) __write_32bit_c0_register($20, 1, val)

#define read_c0_framemask() __read_32bit_c0_register($21, 0)
#define write_c0_framemask(val) __write_32bit_c0_register($21, 0, val)

#define read_c0_debug()     __read_32bit_c0_register($23, 0)
#define write_c0_debug(val) __write_32bit_c0_register($23, 0, val)

#define read_c0_depc()      __read_ulong_c0_register($24, 0)
#define write_c0_depc(val)  __write_ulong_c0_register($24, 0, val)

#define read_c0_ecc()       __read_32bit_c0_register($26, 0)
#define write_c0_ecc(val)   __write_32bit_c0_register($26, 0, val)

#define read_c0_derraddr0() __read_ulong_c0_register($26, 1)
#define write_c0_derraddr0(val) __write_ulong_c0_register($26, 1, val)

#define read_c0_cacheerr()  __read_32bit_c0_register($27, 0)

#define read_c0_derraddr1() __read_ulong_c0_register($27, 1)
#define write_c0_derraddr1(val) __write_ulong_c0_register($27, 1, val)

#define read_c0_taglo()     __read_32bit_c0_register($28, 0)
#define write_c0_taglo(val) __write_32bit_c0_register($28, 0, val)

#define read_c0_taghi()     __read_32bit_c0_register($29, 0)
#define write_c0_taghi(val) __write_32bit_c0_register($29, 0, val)

#define read_c0_errorepc()  __read_ulong_c0_register($30, 0)
#define write_c0_errorepc(val)  __write_ulong_c0_register($30, 0, val)

#define read_c0_epc()       __read_ulong_c0_register($14, 0)
#define write_c0_epc(val)   __write_ulong_c0_register($14, 0, val)

#if 1
/*
 * Macros to access the system control coprocessor
 */
#define read_32bit_cp0_register(source)                         \
({ int __res;                                                   \
        __asm__ __volatile__(                                   \
    ".set\tpush\n\t"                    \
    ".set\treorder\n\t"                 \
        "mfc0\t%0,"STR(source)"\n\t"                            \
    ".set\tpop"                     \
        : "=r" (__res));                                        \
        __res;})

#define read_32bit_cp0_set1_register(source)                    \
({ int __res;                                                   \
        __asm__ __volatile__(                                   \
    ".set\tpush\n\t"                    \
    ".set\treorder\n\t"                 \
        "cfc0\t%0,"STR(source)"\n\t"                            \
    ".set\tpop"                     \
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
        "mtc0\t%0,"STR(register)"\n\t"              \
    "nop"                           \
        : : "r" (value));

#define write_32bit_cp0_set1_register(register,value)           \
        __asm__ __volatile__(                                   \
        "ctc0\t%0,$"STR(register)"\n\t"             \
    "nop"                           \
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
    "#.set\tmips64\n\t"                 \
    "#mfc0\t$1, $16, 1\n\t"                 \
    "#.set\tmips0\n\t"                  \
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
    ".set\tpush\n\t"                    \
    ".set\treorder\n\t"                 \
        "cfc1\t%0,$"STR(source)"\n\t"                            \
    ".set\tpop"                     \
        : "=r" (__res));                                        \
        __res;})

#define write_32bit_cp1_register(register,value)                \
        __asm__ __volatile__(                                   \
        "ctc1\t%0,$"STR(register)"\n\t"             \
    "nop"                           \
        : : "r" (value));

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
#define __BUILD_SET_C0(name,register)               \
static inline unsigned int                  \
set_c0_##name(unsigned int set)                 \
{                               \
    unsigned int res;                   \
                                \
    res = read_c0_##name();                 \
    res |= set;                     \
    write_c0_##name(res);                   \
                                \
    return res;                     \
}                               \
                                \
static inline unsigned int                  \
clear_c0_##name(unsigned int clear)             \
{                               \
    unsigned int res;                   \
                                \
    res = read_c0_##name();                 \
    res &= ~clear;                      \
    write_c0_##name(res);                   \
                                \
    return res;                     \
}                               \
                                \
static inline unsigned int                  \
change_c0_##name(unsigned int change, unsigned int new)     \
{                               \
    unsigned int res;                   \
                                \
    res = read_c0_##name();                 \
    res &= ~change;                     \
    res |= (new & change);                  \
    write_c0_##name(res);                   \
                                \
    return res;                     \
}

__BUILD_SET_C0(status,CP0_STATUS)
__BUILD_SET_C0(cause,CP0_CAUSE)
__BUILD_SET_C0(config,CP0_CONFIG)

#define set_cp0_status(x)   set_c0_status(x)
#define set_cp0_cause(x)    set_c0_cause(x)
#define set_cp0_config(x)   set_c0_config(x)

#define read_c1_status()    read_32bit_cp1_register(31)
#define write_c1_status(x)  write_32bit_cp1_register(31, x)

#define readb(reg)      (*((volatile unsigned char *) (reg)))
#define readw(reg)      (*((volatile unsigned short *) (reg)))
#define readl(reg)      (*((volatile unsigned int *) (reg)))

#define writeb(data, reg)   ((*((volatile unsigned char *)(reg))) = (unsigned char)(data))
#define writew(data, reg)   ((*((volatile unsigned short *)(reg))) = (unsigned short)(data))
#define writel(data, reg)   ((*((volatile unsigned int *)(reg))) = (unsigned int)(data))

#endif /* !__ASSEMBLY__ */

#endif /* _MIPS_REGS_H_ */
