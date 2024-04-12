/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __ZYNQMP_REG_H__
#define __ZYNQMP_REG_H__

/* bit field helpers. */
#define __M(n)                    (~(~0<<(n)))
#define __RBF(number, n)          ((number)&__M(n))
#define __BF(number, n, m)        __RBF((number>>m), (n-m+1))
#define REG_BF(number, n, m)      (m<n ? __BF(number, n, m) : __BF(number, m, n))

#define readb(reg)                (*((volatile unsigned char *)(reg)))
#define readw(reg)                (*((volatile unsigned short *)(reg)))
#define readl(reg)                (*((volatile unsigned int *)(reg)))
#define readq(reg)                (*((volatile unsigned long long *)(reg)))

#define writeb(data, reg)         ((*((volatile unsigned char *)(reg))) = (unsigned char)(data))
#define writew(data, reg)         ((*((volatile unsigned short *)(reg))) = (unsigned short)(data))
#define writel(data, reg)         ((*((volatile unsigned int *)(reg))) = (unsigned int)(data))
#define writeq(data, reg)         ((*((volatile unsigned long long *)(reg))) = (unsigned long long)(data))

#define clrsetreg(addr, clr, set) writel(((clr) | (set)) << 16 | (set), addr)
#define clrreg(addr, clr)         writel((clr) << 16, addr)
#define setreg(addr, set)         writel((set) << 16 | (set), addr)

#define DUMP_REG(base, reg)                          \
do {                                                 \
    rt_uint32_t status = 0x00000000;                 \
    status = readl(base + reg);                      \
    rt_kprintf(#reg ":\n");                          \
    rt_kprintf("\t%p 0x%.8x\n", base + reg, status); \
} while(0);

#endif /* __ZYNQMP_REG_H__ */
