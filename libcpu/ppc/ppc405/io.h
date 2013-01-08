#ifndef __IO_H__
#define __IO_H__

#define __iomem

/*
 * 8, 16 and 32 bit, big and little endian I/O operations, with barrier.
 *
 * Read operations have additional twi & isync to make sure the read
 * is actually performed (i.e. the data has come back) before we start
 * executing any following instructions.
 */
static inline int in_8(const volatile unsigned char __iomem *addr)
{
	int ret;

	__asm__ __volatile__(
		"sync; lbz%U1%X1 %0,%1;\n"
		"twi 0,%0,0;\n"
		"isync" : "=r" (ret) : "m" (*addr));
	return ret;
}

static inline void out_8(volatile unsigned char __iomem *addr, int val)
{
	__asm__ __volatile__("stb%U0%X0 %1,%0; eieio" : "=m" (*addr) : "r" (val));
}

extern inline int in_le16(const volatile unsigned short __iomem *addr)
{
	int ret;

	__asm__ __volatile__("sync; lhbrx %0,0,%1;\n"
			     "twi 0,%0,0;\n"
			     "isync" : "=r" (ret) :
			      "r" (addr), "m" (*addr));
	return ret;
}

extern inline int in_be16(const volatile unsigned short __iomem *addr)
{
	int ret;

	__asm__ __volatile__("sync; lhz%U1%X1 %0,%1;\n"
			     "twi 0,%0,0;\n"
			     "isync" : "=r" (ret) : "m" (*addr));
	return ret;
}

extern inline void out_le16(volatile unsigned short __iomem *addr, int val)
{
	__asm__ __volatile__("sync; sthbrx %1,0,%2" : "=m" (*addr) :
			      "r" (val), "r" (addr));
}

extern inline void out_be16(volatile unsigned short __iomem *addr, int val)
{
	__asm__ __volatile__("sync; sth%U0%X0 %1,%0" : "=m" (*addr) : "r" (val));
}

extern inline unsigned in_le32(const volatile unsigned __iomem *addr)
{
	unsigned ret;

	__asm__ __volatile__("sync; lwbrx %0,0,%1;\n"
			     "twi 0,%0,0;\n"
			     "isync" : "=r" (ret) :
			     "r" (addr), "m" (*addr));
	return ret;
}

extern inline unsigned in_be32(const volatile unsigned __iomem *addr)
{
	unsigned ret;

	__asm__ __volatile__("sync; lwz%U1%X1 %0,%1;\n"
			     "twi 0,%0,0;\n"
			     "isync" : "=r" (ret) : "m" (*addr));
	return ret;
}

extern inline void out_le32(volatile unsigned __iomem *addr, int val)
{
	__asm__ __volatile__("sync; stwbrx %1,0,%2" : "=m" (*addr) :
			     "r" (val), "r" (addr));
}

extern inline void out_be32(volatile unsigned __iomem *addr, int val)
{
	__asm__ __volatile__("sync; stw%U0%X0 %1,%0" : "=m" (*addr) : "r" (val));
}

#endif
