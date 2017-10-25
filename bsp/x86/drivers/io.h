/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

#ifndef IO_H_
#define IO_H_
#ifndef IO_VALUE_FIRST
#define writel WRITE32
#define writew WRITE32
#define writeb WRITE8
#else
#define writel(v,a) WRITE32(a,v)
#define writew(v,a) WRITE32(a,v)
#define writeb(v,a) WRITE8(a,v)
#endif

#define readl READ32
#define readw READ32
#define readb READ8


#define WRITE8(address, value)      (*(volatile uint8_t*)(address) = (value))
#define READ8(address)              ((uint8_t)(*(volatile uint8_t*)(address)))

#define WRITE16(address, value)     (*(volatile uint16_t*)(address) = (value))
#define READ16(address)             ((uint16_t)(*(volatile uint16_t*)(address)))

#define WRITE32(address, value)     (*(volatile uint32_t*)(address) = (value))
#define READ32(address)             ((uint32_t)(*(volatile uint32_t*)(address)))

#define WRITE64(address, value)     (*(volatile uint64_t*)(address) = (value))
#define READ64(address)             ((uint64_t)(*(volatile uint64_t*)(address)))

/* Not aligned reads */
#define READ32_NA(address )			( (((uint32_t)(((uint8_t *)address)[0]))<<24) +	\
									  (((uint32_t)(((uint8_t *)address)[1]))<<16) +	\
									  (((uint32_t)(((uint8_t *)address)[2]))<<8) +	\
									  ((uint32_t)(((uint8_t *)address)[3])) )

#define READ16_NA(address )			( (((uint16_t)(((uint8_t *)address)[0]))<<8) +	\
									  (((uint16_t)(((uint8_t *)address)[1]))) )

#define SET32(  _addr, _val)		(*(volatile uint32_t*)(_addr) |= (_val))
#define CLEAR32(_addr, _val)		(*(volatile uint32_t*)(_addr) &= ~(_val))


/* READWRITE macros
 * address - The address to read/write from/to
 * mask    - The value read is inverted and AND:ed with mask
 * val     - The Value to write.
 *
 * READWRITE32(0x120,0x0,0x9) - Read from address 0x120 (contains 0x780), ANDs with
 *                              0xffff_ffff and ORs in 0x9 -> Write 0x789 to 0x120
 *
 */
#define READWRITE32(address,mask,val)  WRITE32(address,(READ32(address)&~(mask))|val)
#define READWRITE8(address,mask,val)   WRITE8(address,(READ8(address)&~(mask))|val)



/* NA - Not Aligned */
#define WRITE32_NA(address, value ) \
	do { \
    	((uint8_t *)address)[0] = ((value>>24)&0xff); \
    	((uint8_t *)address)[1] = ((value>>16)&0xff); \
    	((uint8_t *)address)[2] = ((value>>8)&0xff);  \
    	((uint8_t *)address)[3] = ((value&0xff)); \
	} while(0)

#define WRITE16_NA(address, value ) \
	do { \
    	((uint8_t *)address)[0] = ((value>>8)&0xff); \
    	((uint8_t *)address)[1] = ((value&0xff)); \
	} while(0)

#ifdef __X86__
static __inline unsigned char inb(int port)
{
	unsigned char data;
	__asm __volatile("inb %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

static __inline unsigned short inw(int port)
{
	unsigned short data;
	__asm __volatile("inw %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

static __inline unsigned int inl(int port)
{
	unsigned int data;
	__asm __volatile("inl %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

static __inline void outb(int port, unsigned char data)
{
	__asm __volatile("outb %0,%w1" : : "a" (data), "d" (port));
}

static __inline void outw(int port, unsigned short data)
{
	__asm __volatile("outw %0,%w1" : : "a" (data), "d" (port));
}

static __inline void outl(unsigned short dest_port, unsigned int input_data)
{
	asm volatile (
		"outl       %%eax, %%dx"
		:: "d" (dest_port), "a"((unsigned int)input_data));
}

#else
#define inb(p) readb(p)
#define inw(p) readw(p)
#define inl(p) readl(p)
#define outb(p,v) WRITE8(p,v)
#define outw(p,v) WRITE16(p,v)
#define outl(p,v) WRITE32(p,v)
#endif /* __X86 */


#endif /* IO_H_ */
