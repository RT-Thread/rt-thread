/*
 * Assembly Macros For MIPS
 *
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */


#ifndef __ASM_H__
#define __ASM_H__

#include <rtconfig.h>
/*
 * LEAF - declare leaf routine
 */
#define	LEAF(symbol)                        \
        .globl	symbol;                     \
        .align	2;                          \
        .type	symbol,@function;           \
        .ent	symbol,0;                   \
symbol:		.frame	sp,0,ra

/*
 * NESTED - declare nested routine entry point
 */
#define	NESTED(symbol, framesize, rpc)      \
        .globl	symbol;                     \
        .align	2;                          \
        .type	symbol,@function;           \
        .ent	symbol,0;                   \
symbol:		.frame	sp, framesize, rpc

/*
 * END - mark end of function
 */
#define	END(function)                       \
        .end	function;		        	\
        .size	function,.-function

/*
 * EXPORT - export definition of symbol
 */
#define EXPORT(symbol)						\
        .globl	symbol;                     \
symbol:

/*
 * FEXPORT - export definition of a function symbol
 */
#define FEXPORT(symbol)						\
        .globl	symbol;						\
        .type	symbol,@function;			\
symbol:

/*
 * Global data declaration with size.
 */
#define EXPORTS(name,sz) 		\
      .globl name; 				\
      .type name,@object; 		\
      .size name,sz; 				\
name:

/*
 * Weak data declaration with size.
 */
#define WEXPORT(name,sz) 		\
      .weakext name; 				\
      .type name,@object; 		\
      .size name,sz; 				\
name:

/*
 * Global data reference with size.
 */
#define	IMPORT(name, size) 		\
    .extern	name,size

/*
 * Global zeroed data.
 */
#define BSS(name,size) 			\
      .type name,@object; 		\
    .comm	name,size

/*
 * Local zeroed data.
 */
#define LBSS(name,size) 		\
      .lcomm	name,size


/*
 * ABS - export absolute symbol
 */
#define	ABS(symbol,value)       \
        .globl	symbol;         \
symbol		=	value


#define	TEXT(msg)               \
        .pushsection .data;		\
8:		.asciiz	msg;            \
        .popsection;


#define ENTRY(name) 			\
  .globl name;					\
  .align 2;						\
  .ent name,0;					\
  name##:

/*
 * Macros to handle different pointer/register sizes for 32/64-bit code
 */
#if defined ARCH_MIPS64
/*
 * Size of a register
 */
#define SZREG	8

/*
 * Use the following macros in assemblercode to load/store registers,
 * pointers etc.
 */
#define REG_S		sd
#define REG_L		ld
#define REG_SUBU	dsubu
#define REG_ADDU	daddu

/*
 * How to add/sub/load/store/shift C int variables.
 */
#define INT_ADD		dadd
#define INT_ADDU	daddu
#define INT_ADDI	daddi
#define INT_ADDIU	daddiu
#define INT_SUB		dsub
#define INT_SUBU	dsubu
#define INT_L		ld
#define INT_S		sd
#define INT_SLL		dsll
#define INT_SLLV	dsllv
#define INT_SRL		dsrl
#define INT_SRLV	dsrlv
#define INT_SRA		dsra
#define INT_SRAV	dsrav

/*
 * Use the following macros in assemblercode to load/store registers,
 * pointers etc.
 */
#define LONG_ADD	dadd
#define LONG_ADDU	daddu
#define LONG_ADDI	daddi
#define LONG_ADDIU	daddiu
#define LONG_SUB	dsub
#define LONG_SUBU	dsubu
#define LONG_L		ld
#define LONG_S		sd
#define LONG_SP		sdp
#define LONG_SLL	dsll
#define LONG_SLLV	dsllv
#define LONG_SRL	dsrl
#define LONG_SRLV	dsrlv
#define LONG_SRA	dsra
#define LONG_SRAV	dsrav

#define LONG		.dword
#define LONGSIZE	8
#define LONGMASK	7
#define LONGLOG		3

/*
 * How to add/sub/load/store/shift pointers.
 */
#define PTR_ADD		dadd
#define PTR_ADDU	daddu
#define PTR_ADDI	daddi
#define PTR_ADDIU	daddiu
#define PTR_SUB		dsub
#define PTR_SUBU	dsubu
#define PTR_L		ld
#define PTR_S		sd
#define PTR_LA		dla
#define PTR_LI		dli
#define PTR_SLL		dsll
#define PTR_SLLV	dsllv
#define PTR_SRL		dsrl
#define PTR_SRLV	dsrlv
#define PTR_SRA		dsra
#define PTR_SRAV	dsrav

#define PTR_SCALESHIFT	3

#define PTR		.dword
#define PTRSIZE		8
#define PTRLOG		3

#define MFC0		dmfc0
#define MTC0		dmtc0

#else
/*
 * Size of a register
 */
#define SZREG	4


/*
 * Use the following macros in assemblercode to load/store registers,
 * pointers etc.
 */
#define REG_S		sw
#define REG_L		lw
#define REG_SUBU	subu
#define REG_ADDU	addu


/*
 * How to add/sub/load/store/shift C int variables.
 */
#define INT_ADD		add
#define INT_ADDU	addu
#define INT_ADDI	addi
#define INT_ADDIU	addiu
#define INT_SUB		sub
#define INT_SUBU	subu
#define INT_L		lw
#define INT_S		sw
#define INT_SLL		sll
#define INT_SLLV	sllv
#define INT_SRL		srl
#define INT_SRLV	srlv
#define INT_SRA		sra
#define INT_SRAV	srav



/*
 * How to add/sub/load/store/shift C long variables.
 */
#define LONG_ADD	add
#define LONG_ADDU	addu
#define LONG_ADDI	addi
#define LONG_ADDIU	addiu
#define LONG_SUB	sub
#define LONG_SUBU	subu
#define LONG_L		lw
#define LONG_S		sw
#define LONG_SLL	sll
#define LONG_SLLV	sllv
#define LONG_SRL	srl
#define LONG_SRLV	srlv
#define LONG_SRA	sra
#define LONG_SRAV	srav

#define LONG		.word
#define LONGSIZE	4
#define LONGMASK	3
#define LONGLOG		2



/*
 * How to add/sub/load/store/shift pointers.
 */
#define PTR_ADD		add
#define PTR_ADDU	addu
#define PTR_ADDI	addi
#define PTR_ADDIU	addiu
#define PTR_SUB		sub
#define PTR_SUBU	subu
#define PTR_L		lw
#define PTR_S		sw
#define PTR_LA		la
#define PTR_SLL		sll
#define PTR_SLLV	sllv
#define PTR_SRL		srl
#define PTR_SRLV	srlv
#define PTR_SRA		sra
#define PTR_SRAV	srav

#define PTR_SCALESHIFT	2

#define PTR			.word
#define PTRSIZE		4
#define PTRLOG		2


/*
 * Some cp0 registers were extended to 64bit for MIPS III.
 */
#define MFC0		mfc0
#define MTC0		mtc0

#endif

#define SSNOP		sll zero, zero, 1

#endif /* end of __ASM_H__ */
