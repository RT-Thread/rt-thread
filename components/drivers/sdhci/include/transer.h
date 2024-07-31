#ifndef __SDHCI_TRANSER_H__
#define __SDHCI_TRANSER_H__
#define readb(c)	    u8_read(c)
#define readw(c)		u16_read(c)
#define readl(c)		u32_read(c)
#define readsb(p,d,l)		({ __raw_readsb(p,d,l); __iormb(); })
#define readsw(p,d,l)		({ __raw_readsw(p,d,l); __iormb(); })
#define readsl(p,d,l)		({ __raw_readsl(p,d,l); __iormb(); })

#define writeb(v,c)		u8_write(v,c)
#define writew(v,c)		u16_write(v,c)
#define writel(v,c)		u32_write(v,c)
#define writesb(p,d,l)		({ __iowmb(); __raw_writesb(p,d,l); })
#define writesw(p,d,l)		({ __iowmb(); __raw_writesw(p,d,l); })
#define writesl(p,d,l)		({ __iowmb(); __raw_writesl(p,d,l); })

static inline rt_uint8_t u8_read(const volatile void *addr)
{
    return *(const volatile rt_uint8_t *)addr;
}

static inline rt_uint16_t u16_read(const volatile void *addr)
{
    return *(const volatile rt_uint16_t *)addr;
}

static inline rt_uint32_t u32_read(const volatile void *addr)
{
    return *(const volatile rt_uint32_t *)addr;
}

static inline void u8_write(rt_uint8_t value, volatile void *addr)
{
    *(volatile rt_uint8_t *)addr = value;
}

static inline void u16_write(rt_uint16_t value, volatile void *addr)
{
    *(volatile rt_uint16_t *)addr = value;
}

static inline rt_uint32_t u32_write(rt_uint16_t value, volatile void *addr)
{
    *(volatile rt_uint32_t *)addr = value;
}

#endif