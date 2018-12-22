/*
 * File      : mips_asm.h
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
 * 2016Äê9ÔÂ7ÈÕ     Urey         the first version
 */

#ifndef _MIPS_ASM_H_
#define _MIPS_ASM_H_


/* ********************************************************************* */
/* Interface macro & data definition */

#ifdef __ASSEMBLY__

/******** ASSEMBLER SPECIFIC DEFINITIONS ********/

#ifdef  __ghs__
#define ALIGN(x) .##align (1 << (x))
#else
#define ALIGN(x) .##align (x)
#endif

#ifdef __ghs__
#define SET_MIPS3()
#define SET_MIPS0()
#define SET_PUSH()
#define SET_POP()
#else
#define SET_MIPS3() .##set mips3
#define SET_MIPS0() .##set mips0
#define SET_PUSH()  .##set push
#define SET_POP()   .##set pop
#endif

/*  Different assemblers have different requirements for how to
 *  indicate that the next section is bss :
 *
 *  Some use :   .bss
 *  Others use : .section bss
 *
 *  We select which to use based on _BSS_OLD_, which may be defined
 *  in makefile.
 */
#ifdef _BSS_OLD_
#define BSS	.##section bss
#else
#define BSS	.##bss
#endif

#define LEAF(name)\
  		.##text;\
  		.##globl	name;\
  		.##ent	name;\
name:


#define SLEAF(name)\
  		.##text;\
  		.##ent	name;\
name:


#ifdef __ghs__
#define END(name)\
  		.##end	name
#else
#define END(name)\
  		.##size name,.-name;\
  		.##end	name
#endif


#define EXTERN(name)

#else

#define U64 unsigned long long
#define U32 unsigned int
#define U16 unsigned short
#define U8  unsigned char
#define S64 signed long long
#define S32 int
#define S16 short int
#define S8  signed char
//#define bool U8

#ifndef _SIZE_T_
#define _SIZE_T_
#ifdef __ghs__
   typedef unsigned int size_t;
#else
   typedef unsigned long size_t;
#endif
#endif

/* Sets the result on bPort */
#define BIT_SET(bPort,bBitMask)        (bPort |= bBitMask)
#define BIT_CLR(bPort,bBitMask)        (bPort &= ~bBitMask)

/* Returns the result */
#define GET_BIT_SET(bPort,bBitMask)    (bPort | bBitMask)
#define GET_BIT_CLR(bPort,bBitMask)    (bPort & ~bBitMask)

/* Returns 0 if the condition is False & a non-zero value if it is True */
#define TEST_BIT_SET(bPort,bBitMask)   (bPort & bBitMask)
#define TEST_BIT_CLR(bPort,bBitMask)   ((~bPort) & bBitMask)

/* Split union definitions */
typedef union tunSU16
{
        U16 hwHW;
        struct tst2U8
        {
                U8 bB0;
                U8 bB1;
        }st2U8;
}tunSU16;

typedef union tunSU32
{
        U32 wW;
        struct tst2U16
        {
                U16 hwHW0;
                U16 hwHW1;
        }st2U16;
        struct tst4U8
        {
                U8 bB0;
                U8 bB1;
                U8 bB2;
                U8 bB3;
        }st4U8;
}tunSU32;

#endif /* #ifdef __ASSEMBLY__ */


/******** DEFINITIONS FOR BOTH ASSEMBLER AND C ********/


#define  NO_ERR             0x00000000     /* operation completed successfully */
#define  ERR                0xffffffff     /* operation completed not successfully */

#define False 0
#define True !False

#ifndef NULL
#define NULL		      	((void *)0)
#endif//NULL

#ifndef MIN
#define MIN(x,y)           ((x) < (y) ? (x) : (y))
#endif//MIN

#ifndef MAX
#define MAX(x,y)      		((x) > (y) ? (x) : (y))
#endif//MAX

#define MAXUINT(w)	(\
		((w) == sizeof(U8))  ? 0xFFU :\
		((w) == sizeof(U16)) ? 0xFFFFU :\
		((w) == sizeof(U32)) ? 0xFFFFFFFFU : 0\
		        )

#define MAXINT(w)	(\
		((w) == sizeof(S8))  ? 0x7F :\
		((w) == sizeof(S16)) ? 0x7FFF :\
		((w) == sizeof(S32)) ? 0x7FFFFFFF : 0\
		        )

#define MSK(n)			  ((1 << (n)) - 1)

#define KUSEG_MSK		  0x80000000
#define KSEG_MSK		  0xE0000000

#define KUSEGBASE		  0x00000000
#define KSEG0BASE		  0x80000000
#define KSEG1BASE		  0xA0000000
#define KSSEGBASE		  0xC0000000
#define KSEG3BASE		  0xE0000000

/*  Below macros perform the following functions :
 *
 *  KSEG0    : Converts KSEG0/1 or physical addr (below 0.5GB) to KSEG0.
 *  KSEG1    : Converts KSEG0/1 or physical addr (below 0.5GB) to KSEG1.
 *  PHYS     : Converts KSEG0/1 or physical addr (below 0.5GB) to physical address.
 *  KSSEG    : Not relevant for converting, but used for determining range.
 *  KSEG3    : Not relevant for converting, but used for determining range.
 *  KUSEG    : Not relevant for converting, but used for determining range.
 *  KSEG0A   : Same as KSEG0 but operates on register rather than constant.
 *  KSEG1A   : Same as KSEG1 but operates on register rather than constant.
 *  PHYSA    : Same as PHYS  but operates on register rather than constant.
 *  CACHED   : Alias for KSEG0 macro .
 *	       (Note that KSEG0 cache attribute is determined by K0
 *	       field of Config register, but this is typically cached).
 *  UNCACHED : Alias for KSEG1 macro .
 */
#ifdef __ASSEMBLY__
#define KSEG0(addr)     (((addr) & ~KSEG_MSK)  | KSEG0BASE)
#define KSEG1(addr)     (((addr) & ~KSEG_MSK)  | KSEG1BASE)
#define KSSEG(addr)     (((addr) & ~KSEG_MSK)  | KSSEGBASE)
#define KSEG3(addr)     (((addr) & ~KSEG_MSK)  | KSEG3BASE)
#define KUSEG(addr)     (((addr) & ~KUSEG_MSK) | KUSEGBASE)
#define PHYS(addr)      ( (addr) & ~KSEG_MSK)
#define KSEG0A(reg) 	and reg, ~KSEG_MSK; or reg, KSEG0BASE
#define KSEG1A(reg) 	and reg, ~KSEG_MSK; or reg, KSEG1BASE
#define PHYSA(reg)	and reg, ~KSEG_MSK
#else
#define KSEG0(addr)     (((U32)(addr) & ~KSEG_MSK)  | KSEG0BASE)
#define KSEG1(addr)     (((U32)(addr) & ~KSEG_MSK)  | KSEG1BASE)
#define KSSEG(addr)	(((U32)(addr) & ~KSEG_MSK)  | KSSEGBASE)
#define KSEG3(addr)	(((U32)(addr) & ~KSEG_MSK)  | KSEG3BASE)
#define KUSEG(addr)	(((U32)(addr) & ~KUSEG_MSK) | KUSEGBASE)
#define PHYS(addr) 	((U32)(addr)  & ~KSEG_MSK)
#endif

#define CACHED(addr)	KSEG0(addr)
#define UNCACHED(addr)	KSEG1(addr)


#ifdef __ASSEMBLY__
/* Macroes to access variables at constant addresses
 * Compensates for signed 16 bit displacement
 * Typical use:	li	a0, HIKSEG1(ATLAS_ASCIIWORD)
 *		sw	v1, LO_OFFS(ATLAS_ASCIIWORD)(a0)
 */
#define HIKSEG0(addr)	((KSEG0(addr) + 0x8000) & 0xffff0000)
#define HIKSEG1(addr)	((KSEG1(addr) + 0x8000) & 0xffff0000)
#define HI_PART(addr)	(((addr) + 0x8000) & 0xffff0000)
#define LO_OFFS(addr)	((addr) & 0xffff)
#endif


/* Most/Least significant 32 bit from 64 bit double word */
#define HI32(data64)		  ((U32)(data64 >> 32))
#define LO32(data64)		  ((U32)(data64 & 0xFFFFFFFF))

#if ((!defined(__ASSEMBLY__)) && (!defined(__LANGUAGE_ASSEMBLY)))
#define REG8( addr )		  (*(volatile U8 *) (addr))
#define REG16( addr )		  (*(volatile U16 *)(addr))
#define REG32( addr )		  (*(volatile U32 *)(addr))
#define REG64( addr )		  (*(volatile U64 *)(addr))
#endif

/* Register field mapping */
#define REGFIELD(reg, rfld)	  (((reg) & rfld##_MSK) >> rfld##_SHF)

/* absolute register address, access 					*/
#define	REGA(addr)		  REG32(addr)

/* physical register address, access: base address + offsett		*/
#define	REGP(base,phys)	REG32( (U32)(base) + (phys) )

/* relative register address, access: base address + offsett		*/
#define REG(base,offs)  REG32( (U32)(base) + offs##_##OFS )

/* relative register address, access: base address + offsett		*/
#define REG_8(base,offs)  REG8( (U32)(base) + offs##_##OFS )

/* relative register address, access: base address + offsett		*/
#define REG_16(base,offs)  REG16( (U32)(base) + offs##_##OFS )

/* relative register address, access: base address + offsett		*/
#define REG_64(base,offs)  REG64( (U32)(base) + offs##_##OFS )

/**************************************
 * Macroes not used by YAMON any more
 * (kept for backwards compatibility)
 */
/* register read field							*/
#define	REGARD(addr,fld)	((REGA(addr) & addr##_##fld##_##MSK) 	\
			 >> addr##_##fld##_##SHF)

/* register write numeric field value					*/
#define	REGAWRI(addr,fld,intval) ((REGA(addr) & ~(addr##_##fld##_##MSK))\
				 | ((intval) << addr##_##fld##_##SHF))

/* register write enumerated field value				*/
#define	REGAWRE(addr,fld,enumval) ((REGA(addr) & ~(addr##_##fld##_##MSK))\
			| ((addr##_##fld##_##enumval) << addr##_##fld##_##SHF))


/* Examples:
 *
 *	exccode = REGARD(CPU_CAUSE,EXC);
 *
 *	REGA(SDR_CONTROL) = REGAWRI(OSG_CONTROL,TMO,17)
 *			 | REGAWRE(OSG_CONTROL,DTYPE,PC1);
 */


/* register read field							*/
#define	REGRD(base,offs,fld) ((REG(base,offs) & offs##_##fld##_##MSK) 	\
			 >> offs##_##fld##_##SHF)

/* register write numeric field value					*/
#define	REGWRI(base,offs,fld,intval)((REG(base,offs)& ~(offs##_##fld##_##MSK))\
                                 | (((intval) << offs##_##fld##_##SHF) & offs##_##fld##_##MSK))

/* register write enumerated field value				*/
#define	REGWRE(base,offs,fld,enumval)((REG(base,offs) & ~(offs##_##fld##_##MSK))\
				| ((offs##_##fld##_##enumval) << offs##_##fld##_##SHF))


/* physical register read field							*/
#define	REGPRD(base,phys,fld) ((REGP(base,phys) & phys##_##fld##_##MSK) 	\
			 >> phys##_##fld##_##SHF)

/* physical register write numeric field value					*/
#define	REGPWRI(base,phys,fld,intval)((REGP(base,phys)& ~(phys##_##fld##_##MSK))\
				 | ((intval) << phys##_##fld##_##SHF))

/* physical register write enumerated field value				*/
#define	REGPWRE(base,phys,fld,enumval)((REGP(base,phys) & ~(phys##_##fld##_##MSK))\
				| ((phys##_##fld##_##enumval) << phys##_##fld##_##SHF))
/*
 * End of macroes not used by YAMON any more
 *********************************************/

/* Endian related macros */

#define SWAP_BYTEADDR32( addr )   ( (addr) ^ 0x3 )
#define SWAP_U16ADDR32( addr ) ( (addr) ^ 0x2 )

/* Set byte address to little endian format */
#ifdef EL
#define SWAP_BYTEADDR_EL(addr) 	  addr
#else
#define SWAP_BYTEADDR_EL(addr)    SWAP_BYTEADDR32( addr )
#endif

/* Set byte address to big endian format */
#ifdef EB
#define SWAP_BYTEADDR_EB(addr) 	  addr
#else
#define SWAP_BYTEADDR_EB(addr)    SWAP_BYTEADDR32( addr )
#endif

/* Set U16 address to little endian format */
#ifdef EL
#define SWAP_U16ADDR_EL(addr)  addr
#else
#define SWAP_U16ADDR_EL(addr)  SWAP_U16ADDR32( addr )
#endif

/* Set U16 address to big endian format */
#ifdef EB
#define SWAP_U16ADDR_EB(addr)  addr
#else
#define SWAP_U16ADDR_EB(addr)  SWAP_U16ADDR32( addr )
#endif

#ifdef EL
#define REGW32LE(addr, data)      REG32(addr) = (data)
#define REGR32LE(addr, data)      (data)      = REG32(addr)
#else
#define REGW32LE(addr, data)      REG32(addr) = SWAPEND32(data)
#define REGR32LE(addr, data)      (data)      = REG32(addr), (data) = SWAPEND32(data)
#endif

/* Set of 'LE'-macros, convert by BE: */
#ifdef EL
#define CPU_TO_LE32( value ) (value)
#define LE32_TO_CPU( value ) (value)

#define CPU_TO_LE16( value ) (value)
#define LE16_TO_CPU( value ) (value)
#else
#define CPU_TO_LE32( value ) ( (                ((U32)value)  << 24) |   \
                               ((0x0000FF00UL & ((U32)value)) <<  8) |   \
                               ((0x00FF0000UL & ((U32)value)) >>  8) |   \
                               (                ((U32)value)  >> 24)   )
#define LE32_TO_CPU( value ) CPU_TO_LE32( value )

#define CPU_TO_LE16( value ) ( ((U16)(((U16)value)  << 8)) |   \
                               ((U16)(((U16)value)  >> 8))   )
#define LE16_TO_CPU( value ) CPU_TO_LE16( value )
#endif

/* Set of 'BE'-macros, convert by LE: */
#ifdef EB
#define CPU_TO_BE32( value ) (value)
#define BE32_TO_CPU( value ) (value)

#define CPU_TO_BE16( value ) (value)
#define BE16_TO_CPU( value ) (value)
#else
#define CPU_TO_BE32( value ) ( (                ((U32)value)  << 24) |   \
                               ((0x0000FF00UL & ((U32)value)) <<  8) |   \
                               ((0x00FF0000UL & ((U32)value)) >>  8) |   \
                               (                ((U32)value)  >> 24)   )
#define BE32_TO_CPU( value ) CPU_TO_BE32( value )

#define CPU_TO_BE16( value ) ( ((U16)(((U16)value)  << 8)) |   \
                               ((U16)(((U16)value)  >> 8))   )
#define BE16_TO_CPU( value ) CPU_TO_BE16( value )
#endif


/* Control characters */
#define CTRL_A          ('A'-0x40)
#define CTRL_B          ('B'-0x40)
#define CTRL_C          ('C'-0x40)
#define CTRL_D          ('D'-0x40)
#define CTRL_E          ('E'-0x40)
#define CTRL_F          ('F'-0x40)
#define CTRL_H          ('H'-0x40)
#define CTRL_K          ('K'-0x40)
#define CTRL_N          ('N'-0x40)
#define CTRL_P          ('P'-0x40)
#define CTRL_U          ('U'-0x40)
#define BACKSPACE       0x08
#define DEL             0x7F
#define TAB             0x09
#define CR              0x0D /* Enter Key */
#define LF              0x0A
#define ESC             0x1B
#define SP              0x20
#define CSI             0x9B


/* DEF2STR(x) converts #define symbol to string */
#define DEF2STR1(x) #x
#define DEF2STR(x)  DEF2STR1(x)


#endif /* _MIPS_ASM_H_ */
