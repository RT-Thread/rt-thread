/*
 * File      : mmu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-04-25     Yi.qiu       first version
 */

#include <rtthread.h>
#include "s3c24x0.h"

// #define _MMUTT_STARTADDRESS	 0x30080000
#define _MMUTT_STARTADDRESS	 0x30200000

#define DESC_SEC	(0x2|(1<<4))
#define CB		(3<<2)  //cache_on, write_back
#define CNB		(2<<2)  //cache_on, write_through
#define NCB             (1<<2)  //cache_off,WR_BUF on
#define NCNB		(0<<2)  //cache_off,WR_BUF off
#define AP_RW		(3<<10) //supervisor=RW, user=RW
#define AP_RO		(2<<10) //supervisor=RW, user=RO

#define DOMAIN_FAULT	(0x0)
#define DOMAIN_CHK	(0x1)
#define DOMAIN_NOTCHK	(0x3)
#define DOMAIN0		(0x0<<5)
#define DOMAIN1		(0x1<<5)

#define DOMAIN0_ATTR	(DOMAIN_CHK<<0)
#define DOMAIN1_ATTR	(DOMAIN_FAULT<<2)

#define RW_CB		(AP_RW|DOMAIN0|CB|DESC_SEC)
#define RW_CNB		(AP_RW|DOMAIN0|CNB|DESC_SEC)
#define RW_NCNB		(AP_RW|DOMAIN0|NCNB|DESC_SEC)
#define RW_FAULT	(AP_RW|DOMAIN1|NCNB|DESC_SEC)

#ifdef __GNU_C__
void mmu_setttbase(register rt_uint32_t i)
{
	asm ("mcr p15, 0, %0, c2, c2, 0": :"r" (i));
}

void mmu_setdomain(register rt_uint32_t i)
{
	asm ("mcr p15,0, %0, c3, c0,  0": :"r" (i));
}

void mmu_enablemmu()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= 0x1;

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disablemmu()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~0x1;

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_enableicache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= (1 << 12);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_enabledcache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= (1 << 2);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disableicache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~(1 << 12);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disabledcache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~(1 << 2);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_enablealignfault()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= (1 << 1);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disablealignfault()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~(1 << 1);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_cleaninvalidatedcacheindex(int index)
{
	asm ("mcr p15, 0, %0, c7, c14, 2": :"r" (index));
}

void mmu_invalidatetlb()
{
	asm ("mcr p15, 0, %0, c8, c7, 0": :"r" (0));
}

void mmu_invalidateicache()
{
	asm ("mcr p15, 0, %0, c7, c5, 0": :"r" (0));
}
#endif

#ifdef __CC_ARM
__asm void mmu_setttbase(rt_uint32_t i)
{
	mcr p15, 0, r0, c2, c2, 0
}

__asm void mmu_setdomain(rt_uint32_t i)
{
	mcr p15,0, r0, c3, c0,  0
}

__asm void mmu_enablemmu()
{
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x01
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_disablemmu()
{
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x01
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_enableicache()
{
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x100
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_enabledcache()
{
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x02
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_disableicache()
{
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x100
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_disabledcache()
{
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x100
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_enablealignfault()
{
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x01
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_disablealignfault()
{
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x02
	mcr p15, 0, r0, c1, c0, 0
}

__asm void mmu_cleaninvalidatedcacheindex(int index)
{
	mcr p15, 0, r0, c7, c14, 2
}

__asm void mmu_invalidatetlb()
{
	mov r0, #0x0
	mcr p15, 0, r0, c8, c7, 0
}

__asm void mmu_invalidateicache()
{
	mov r0, #0
	mcr p15, 0, r0, c7, c5, 0
}
#endif

void mmu_setmtt(int vaddrStart,int vaddrEnd,int paddrStart,int attr)
{
    volatile rt_uint32_t *pTT;
    volatile int i,nSec;
    pTT=(rt_uint32_t *)_MMUTT_STARTADDRESS+(vaddrStart>>20);
    nSec=(vaddrEnd>>20)-(vaddrStart>>20);
    for(i=0;i<=nSec;i++)
    {
		*pTT = attr |(((paddrStart>>20)+i)<<20);
		pTT++;
    }
}

void rt_hw_mmu_init(void)
{
	int i,j;
	//========================== IMPORTANT NOTE =========================
	//The current stack and code area can't be re-mapped in this routine.
	//If you want memory map mapped freely, your own sophiscated mmu
	//initialization code is needed.
	//===================================================================

	mmu_disabledcache();
	mmu_disableicache();

	//If write-back is used,the DCache should be cleared.
	for(i=0;i<64;i++)
		for(j=0;j<8;j++)
			mmu_cleaninvalidatedcacheindex((i<<26)|(j<<5));

	mmu_invalidateicache();

	//To complete mmu_Init() fast, Icache may be turned on here.
	mmu_enableicache();

	mmu_disablemmu();
	mmu_invalidatetlb();

	//mmu_setmtt(int vaddrStart,int vaddrEnd,int paddrStart,int attr);
	mmu_setmtt(0x00000000,0x07f00000,0x00000000,RW_CNB);  //bank0
	mmu_setmtt(0x00000000,0x03f00000,(int)0x30000000,RW_CB);  //bank0
	mmu_setmtt(0x04000000,0x07f00000,0,RW_NCNB);  			//bank0
	mmu_setmtt(0x08000000,0x0ff00000,0x08000000,RW_CNB);  //bank1
	mmu_setmtt(0x10000000,0x17f00000,0x10000000,RW_NCNB); //bank2
	mmu_setmtt(0x18000000,0x1ff00000,0x18000000,RW_NCNB); //bank3
	//mmu_setmtt(0x20000000,0x27f00000,0x20000000,RW_CB); //bank4
	mmu_setmtt(0x20000000,0x27f00000,0x20000000,RW_CNB); //bank4 for STRATA Flash
	mmu_setmtt(0x28000000,0x2ff00000,0x28000000,RW_NCNB); //bank5
	//30f00000->30100000, 31000000->30200000
	mmu_setmtt(0x30000000,0x30100000,0x30000000,RW_CB);	  //bank6-1
	mmu_setmtt(0x30200000,0x33e00000,0x30200000,RW_NCNB); //bank6-2

	mmu_setmtt(0x33f00000,0x33f00000,0x33f00000,RW_CB);   //bank6-3
	mmu_setmtt(0x38000000,0x3ff00000,0x38000000,RW_NCNB); //bank7

	mmu_setmtt(0x40000000,0x47f00000,0x40000000,RW_NCNB); //SFR
	mmu_setmtt(0x48000000,0x5af00000,0x48000000,RW_NCNB); //SFR
	mmu_setmtt(0x5b000000,0x5b000000,0x5b000000,RW_NCNB); //SFR
	mmu_setmtt(0x5b100000,0xfff00000,0x5b100000,RW_FAULT);//not used
	mmu_setmtt(0x60000000,0x67f00000,0x60000000,RW_NCNB); //SFR

	mmu_setttbase(_MMUTT_STARTADDRESS);

	/* DOMAIN1: no_access, DOMAIN0,2~15=client(AP is checked) */
	mmu_setdomain(0x55555550|DOMAIN1_ATTR|DOMAIN0_ATTR);

	//mmu_SetProcessId(0x0);
	mmu_enablealignfault();

	mmu_enablemmu();
	mmu_enableicache();

	/* DCache should be turned on after mmu is turned on. */
	mmu_enabledcache();
}
