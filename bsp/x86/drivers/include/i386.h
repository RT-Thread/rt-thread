/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 */
#ifndef __I386_H_
#define __I386_H_

#ifdef __cplusplus
extern "C" {
#endif

static __inline unsigned char inb(int port)
{
    unsigned char data;
    __asm __volatile("inb %w1,%0" : "=a" (data) : "d" (port));
    return data;
}
static __inline unsigned char inb_p(unsigned short port)
{
    unsigned char _v;
    __asm__ __volatile__ ("inb %1, %0\n\t"
                          "outb %0,$0x80"
                          :"=a" (_v)
                          :"d" ((unsigned short) port));
    return _v;
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

static __inline void insl(int port, void *addr, int cnt)
{
    __asm __volatile("cld\n\trepne\n\tinsl"         :
             "=D" (addr), "=c" (cnt)        :
             "d" (port), "0" (addr), "1" (cnt)  :
             "memory", "cc");
}

static __inline void outb(int port, unsigned char data)
{
    __asm __volatile("outb %0,%w1" : : "a" (data), "d" (port));
}


static __inline void outb_p(char value, unsigned short port)
{
    __asm__ __volatile__ ("outb %0,%1\n\t"
                          "outb %0,$0x80"
                          ::"a" ((char) value),"d" ((unsigned short) port));
}

static __inline void outw(int port, unsigned short data)
{
    __asm __volatile("outw %0,%w1" : : "a" (data), "d" (port));
}

static __inline unsigned char readcmos(int reg)
{
    outb(0x70,reg);
    return (unsigned char) inb(0x71);
}

#define io_delay()                      \
    __asm__ __volatile__ ("pushal \n\t" \
            "mov $0x3F6, %dx \n\t"      \
            "inb %dx, %al \n\t"         \
            "inb %dx, %al \n\t"         \
            "inb %dx, %al \n\t"         \
            "inb %dx, %al \n\t"         \
                          "popal")

/* Gate descriptors are slightly different*/
struct Gatedesc {
    unsigned gd_off_15_0 : 16;   // low 16 bits of offset in segment
    unsigned gd_ss : 16;         // segment selector
    unsigned gd_args : 5;        // # args, 0 for interrupt/trap gates
    unsigned gd_rsv1 : 3;        // reserved(should be zero I guess)
    unsigned gd_type :4;         // type(STS_{TG,IG32,TG32})
    unsigned gd_s : 1;           // must be 0 (system)
    unsigned gd_dpl : 2;         // descriptor(meaning new) privilege level
    unsigned gd_p : 1;           // Present
    unsigned gd_off_31_16 : 16;  // high bits of offset in segment
};

/* Pseudo-descriptors used for LGDT, LLDT and LIDT instructions*/
struct Pseudodesc {
    rt_uint16_t pd__garbage;         // LGDT supposed to be from address 4N+2
    rt_uint16_t pd_lim;              // Limit
    rt_uint32_t pd_base __attribute__ ((packed));       // Base address
};

#define SETGATE(gate, istrap, sel, off, dpl)             \
    {                                                    \
        (gate).gd_off_15_0 = (rt_uint32_t)(off)&0xffff;  \
        (gate).gd_ss = (sel);                            \
        (gate).gd_args = 0;                              \
        (gate).gd_rsv1 = 0;                              \
        (gate).gd_type = (istrap) ? STS_TG32 : STS_IG32; \
        (gate).gd_s = 0;                                 \
        (gate).gd_dpl = dpl;                             \
        (gate).gd_p = 1;                                 \
        (gate).gd_off_31_16 = (rt_uint32_t)(off) >> 16;  \
    }

/* Global descriptor numbers*/
#define GD_KT 0x08 // kernel text
#define GD_KD 0x10 // kernel data
#define GD_UT 0x18 // user text
#define GD_UD 0x20 // user data

/* Application segment type bits*/
#define STA_X 0x8 // Executable segment
#define STA_E 0x4 // Expand down(non-executable segments)
#define STA_C 0x4 // Conforming code segment(executable only)
#define STA_W 0x2 // Writeable(non-executable segments)
#define STA_R 0x2 // Readable(executable segments)
#define STA_A 0x1 // Accessed

/* System segment type bits*/
#define STS_T16A 0x1 // Available 16-bit TSS
#define STS_LDT  0x2 // Local Descriptor Table
#define STS_T16B 0x3 // Busy 16-bit TSS
#define STS_CG16 0x4 // 16-bit Call Gate
#define STS_TG   0x5 // Task Gate / Coum Transmitions
#define STS_IG16 0x6 // 16-bit Interrupt Gate
#define STS_TG16 0x7 // 16-bit Trap Gate
#define STS_T32A 0x9 // Available 32-bit TSS
#define STS_T32B 0xb // Busy 32-bit TSS
#define STS_CG32 0xc // 32-bit Call Gate
#define STS_IG32 0xe // 32-bit Interrupt Gate
#define STS_TG32 0xf // 32-bit Trap Gate

#ifdef __cplusplus
 }
#endif

#endif
