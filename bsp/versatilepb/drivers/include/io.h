
#ifndef IO_H_
#define IO_H_

#include <rtthread.h>

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


#define WRITE8(address, value)      (*(volatile rt_uint8_t*)(address) = (value))
#define READ8(address)              ((rt_uint8_t)(*(volatile rt_uint8_t*)(address)))

#define WRITE16(address, value)     (*(volatile rt_uint16_t*)(address) = (value))
#define READ16(address)             ((rt_uint16_t)(*(volatile rt_uint16_t*)(address)))

#define WRITE32(address, value)     (*(volatile rt_uint32_t*)(address) = (value))
#define READ32(address)             ((rt_uint32_t)(*(volatile rt_uint32_t*)(address)))

#define WRITE64(address, value)     (*(volatile rt_uint64_t*)(address) = (value))
#define READ64(address)             ((rt_uint64_t)(*(volatile rt_uint64_t*)(address)))

/* Not aligned reads */
#define READ32_NA(address )			( (((rt_uint32_t)(((rt_uint8_t *)address)[0]))<<24) +	\
									  (((rt_uint32_t)(((rt_uint8_t *)address)[1]))<<16) +	\
									  (((rt_uint32_t)(((rt_uint8_t *)address)[2]))<<8) +	\
									  ((rt_uint32_t)(((rt_uint8_t *)address)[3])) )

#define READ16_NA(address )			( (((rt_uint16_t)(((rt_uint8_t *)address)[0]))<<8) +	\
									  (((rt_uint16_t)(((rt_uint8_t *)address)[1]))) )

#define SET32(  _addr, _val)		(*(volatile rt_uint32_t*)(_addr) |= (_val))
#define CLEAR32(_addr, _val)		(*(volatile rt_uint32_t*)(_addr) &= ~(_val))


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
    	((rt_uint8_t *)address)[0] = ((value>>24)&0xff); \
    	((rt_uint8_t *)address)[1] = ((value>>16)&0xff); \
    	((rt_uint8_t *)address)[2] = ((value>>8)&0xff);  \
    	((rt_uint8_t *)address)[3] = ((value&0xff)); \
	} while(0)

#define WRITE16_NA(address, value ) \
	do { \
    	((rt_uint8_t *)address)[0] = ((value>>8)&0xff); \
    	((rt_uint8_t *)address)[1] = ((value&0xff)); \
	} while(0)




#endif /* IO_H_ */
