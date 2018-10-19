/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef FH_DEF_H_
#define FH_DEF_H_



#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef char				SINT8;
typedef short				SINT16;
typedef int					SINT32;
typedef long long			SINT64;
typedef unsigned char		UINT8;
typedef unsigned short		UINT16;
typedef unsigned int		UINT32;
typedef unsigned long long	UINT64;

#ifndef TYPE_DEFINED
typedef	unsigned char		uchar;
typedef signed   char		int8;
typedef unsigned char		uint8;
typedef signed   short		int16;
typedef unsigned short		uint16;
typedef signed   int		int32;
typedef unsigned int		uint32;
typedef signed   long  long	int64;
typedef unsigned long long	uint64;
typedef float        		ieee_single;
typedef double       		ieee_double;

typedef unsigned long  		boolean;

#define TYPE_DEFINED

#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define reg_read(addr) (*((volatile UINT32 *)(addr)))
#define reg_write(addr,value) (*(volatile UINT32 *)(addr)=(value))

#define GET_REG(addr) reg_read(addr)
#define SET_REG(addr,value) reg_write(addr,value)
#define SET_REG_M(addr,value,mask) reg_write(addr,(reg_read(addr)&(~(mask)))|((value)&(mask)))
#define SET_REG_B(addr,element,highbit,lowbit) SET_REG_M((addr),((element)<<(lowbit)),(((1<<((highbit)-(lowbit)+1))-1)<<(lowbit)))

#define GET_REG8(addr) (*((volatile UINT8 *)(addr)))
#define SET_REG8(addr,value) (*(volatile UINT8 *)(addr)=(value))

#define read_reg(addr)  (*((volatile uint32 *)(addr)))
#define write_reg(addr, reg)  (*((volatile uint32 *)(addr))) = (uint32)(reg)
#define inw(addr)  (*((volatile uint32 *)(addr)))
#define outw(addr, reg)  (*((volatile uint32 *)(addr))) = (uint32)(reg)
#ifndef BIT
#define BIT(nr)         (1UL << (nr))
#endif

typedef volatile const unsigned int RoReg; /**< Read only 32-bit register (volatile const unsigned int) */
typedef volatile       unsigned int WoReg; /**< Write only 32-bit register (volatile unsigned int) */
typedef volatile       unsigned int RwReg; /**< Read-Write 32-bit register (volatile unsigned int) */



#endif /* FH_DEF_H_ */
