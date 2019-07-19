/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-09-04     bernard      porting to JZ47xx
 * 2019-07-19     Zhou Yanjie  clean up code
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "../common/mips_def.h"
#include "../common/stackframe.h"
#include "sdram_cfg.h"
#include "cache.h"
#include "rtconfig.h"

#define SR_BOOT_EXC_VEC		0x00400000


/* config pll div for cpu and sdram */
#define PLL_MULT            (0x54)  // 晶振为24Mhz时，PLL=504Mhz
#define SDRAM_DIV           (0)     // SDRAM为CPU的2分频
#define CPU_DIV             (2)     // CPU为PLL的2分频

	// 配置内存大小
#define MEM_SIZE    (0x02000000)        // 32MByte

	/* Delay macro */
#define	DELAY(count)	\
		li v0, count;	\
	99: 		\
		bnez	v0, 99b;\
		addiu	v0, -1


#define msize		s2
#define	output_en	s3




	.section ".start", "ax"
	.set noreorder

	/* the program entry */
	.globl  _start
_start:
	.set	noreorder
	la	ra, _start

#if !defined(RT_USING_SELF_BOOT)

	/* disable interrupt */
	mfc0	t0, CP0_STATUS
	and 	t0, 0xfffffffe	# By default it will be disabled.
	mtc0	t0, CP0_STATUS	# Set CPU to disable interrupt.
	nop

	/* disable cache */
	mfc0	t0, CP0_CONFIG
	and	t0, 0xfffffff8
	or	t0, 0x2		# disable,!default value is not it!
	mtc0	t0, CP0_CONFIG	# Set CPU to disable cache.
	nop

	/* setup stack pointer */
	li	sp, SYSTEM_STACK
	la	gp, _gp

	/* clear bss */
	la	t0, __bss_start
	la	t1, __bss_end
_clr_bss_loop:
	sw	zero, 0(t0)
	bne	t0, t1, _clr_bss_loop
	addiu	t0, t0, 4

	/* jump to RT-Thread RTOS */
	jal	rtthread_startup
	nop

	/* restart, never die */
	j	_start
	nop
	
#else

	mtc0	zero, CP0_STATUS	// 清零cp0 status寄存器
	mtc0	zero, CP0_CAUSE		// 清零cp0 cause寄存器

	/*
	设置启动异常向量入口地址为ROM地址(0xbfc00000)
	将寄存器cp0 status的BEV置1，使CPU采用ROM(kseg1)空间的异常入口点
	*/
	li	t0, SR_BOOT_EXC_VEC /* Exception to Boostrap Location */
	mtc0	t0, CP0_STATUS

	/* setup stack pointer */
	li	sp, SYSTEM_STACK
	la	gp, _gp
		
	/* initialize spi */
	li	t0, 0xbfe80000		//地址0xbfe80000为SPI0的寄存器基地址
	li	t1, 0x17			// div 4, fast_read + burst_en + memory_en double I/O 模式 部分SPI flash可能不支持
	sb	t1, 0x4(t0) 		// 设置寄存器sfc_param
	li	t1, 0x05
	sb	t1, 0x6(t0) 		// 设置寄存器sfc_timing

	/* 设置sdram cs1复用关系，开发板使用ejtag_sel gpio_0引脚(第五复用)作为第二片sdram的片选
	  注意sw2拨码开关的设置，使用ejtag烧录pmon时需要调整拨码开关，烧录完再调整回来 */
	li	a0, 0xbfd011c0
	lw	a1, 0x40(a0)
	ori a1, 0x01
	sw	a1, 0x40(a0)


	bal locate
	nop

	/* restart, never die */
	j	_start
	nop
#endif

	.set	reorder

	.globl  cp0_get_cause
cp0_get_cause:
	mfc0	v0, CP0_CAUSE
	jr	ra
	nop

	.globl  cp0_get_status
cp0_get_status:
	mfc0	v0, CP0_STATUS
	jr	ra
	nop

	.globl	cp0_get_hi
cp0_get_hi:
	mfhi	v0
	jr	ra
	nop

	.globl	cp0_get_lo
cp0_get_lo:
	mflo	v0
	jr	ra
	nop

#if defined(RT_USING_SELF_BOOT)

/****************************************LOCATE*********************************/

/*
 *  We get here from executing a bal to get the PC value of the current execute
 *  location into ra. Check to see if we run from ROM or if this is ramloaded.
 *  寄存器ra内保持着函数的返回地址，根据ra的值来判断当前是从ROM冷启动，还是从RAM热复位的
 *  ROM冷启动由通电引起，RAM热复位为各种异常引起，比如看门狗引起的复位等，
 *  也就是RAM热复位之前CPU已经开始运行了
 *  如果是从ROM冷启动，则寄存器ra的值为指令"bal	locate"所在位置加8字节，大概在0xBFC00000附近
 *  如果是从RAM热复位，则集成器ra的值为0x80xxxxxx
 */
locate:
//	la		s0, uncached
//	subu	s0, ra, s0
    /*
     * start.s的这段汇编程序在ROM（入口点为0xBFC00000）中运行
     * 而编译链接时指定的起始地址是0x80100000，所以需要修正一下地址
     * s0中保存着ra与start的差值，在后续的代码中可以起到修正地址的作用
     * 在看看文件开始的时候，对寄存器s0用途的描述是“         link versus load offset, used to relocate absolute adresses”
     * 除了修正地址外，还通过s0的值来判断是从ROM冷启动，还是从RAM热启动
     */
		
	la		s0, _start           // s0 = _start， 其中start的地址为编译链接时，指定的0x80010000
	subu	s0, ra, s0          // s0 = ra - s0，其中ra的值在ROM入口地址0xBFC00000附近
	and	s0, 0xffff0000          // s0 = s0 & 0xffff0000

    /*
     * 初始化cp0的status寄存器和cause寄存器
     * 在异常引起的(从RAM)热复位后，需要重新初始化cp0的status和cause，
     * 如果是从ROM冷启动的，那么前面已经初始化了，这里是再次重复初始化，没有影响的
     */
	li		t0, SR_BOOT_EXC_VEC
	mtc0	t0, CP0_CONFIG        // 重新初始化cp0的status寄存器
	mtc0	zero, CP0_CAUSE       // 重新清零cp0的cause寄存器
	.set	noreorder
    
	li	t0, 0xbfe78030          // 地址0xbfe78030为PLL/SDRAM频率配置寄存器的地址
	/* 设置PLL倍频 及SDRAM分频 */
	li	t2, (0x80000008 | (PLL_MULT << 8) | (0x3 << 2) | SDRAM_DIV)
	/* 设置CPU分频 */
	li	t3, (0x00008003 | (CPU_DIV << 8))
	/* 注意：首先需要把分频使能位清零 */
	li	t1, 0x2
	sw	t1, 0x4(t0)         // 清零CPU_DIV_VALID，即disable
	sw	t2, 0x0(t0)         // 写寄存器START_FREQ
	sw	t3, 0x4(t0)         // 写寄存器CLK_DIV_PARAM
	DELAY(2000)

	/* 芯片上电默认使用gpio(输入模式）但大多时候是使用模块的功能，如lcd i2c spi ac97等
	   所以这里把gpio都关闭，方便使用模块功能。如果上电后需要gpio输出一个确定电平，
	   如继电器、LDE等，可以修改这里的代码。*/
	/* disable all gpio */
	li a0,0xbfd00000
	sw zero,0x10c0(a0)	/* disable gpio 0-31 */
	sw zero,0x10c4(a0)	/* disable gpio 32-63 */
	sw zero,0x10c8(a0)	/* disable gpio 64-95 */
	sw zero,0x10cc(a0)

	li t0, 0xffffffff
	sw t0, 0x10d0(a0)
	sw t0, 0x10d4(a0)
	sw t0, 0x10d8(a0)
	sw t0, 0x10dc(a0)

	sw t0, 0x10f0(a0)
	sw t0, 0x10f4(a0)
	sw t0, 0x10f8(a0)
	sw t0, 0x10fc(a0)


	/* lcd soft_reset and panel config & timing */
#ifdef DC_FB0
/*	li a0, 0xbc301240
	li a1, 0x00100103
	sw a1, 0x0(a0)
	li a1, 0x00000103
	sw a1, 0x0(a0)		//soft_reset
	li a1, 0x00100103
	sw a1, 0x0(a0)

	li a1, 0x80001111
	sw a1, 0x180(a0)	//panel config
	li a1, 0x33333333
	sw a1, 0x1a0(a0)*/
#endif

	li output_en, 0x1
#ifdef FAST_STARTUP
	li a1, 0x03000000
	sw a1, 0x10c4(a0)
	sw a1, 0x10d4(a0)
	lw a2, 0x10e4(a0)
	and a2, a1
	beq a2, a1, get_pin_val_finish
	nop
	li output_en, 0x1

get_pin_val_finish:

#endif

	/* Initializing. Standby... */
    /*
     *  根据s0的值判断是否为ROM冷启动
     *  如果s0不等于0，则是ROM冷启动；如果等于0，则是RAM热复位
     *  冷启动，则需要初始化内存，cache，加载代码到内存等
     */
	bnez s0, 1f     // 如果寄存器s0不等于0，则说明是ROM冷启动，则跳转到下一个标号1处进行彻底初始化
	nop
	li a0, 128

	jal rtthread_startup    // 热复位，则直接跳转到函数main
	nop
1:

/* use only 8wins */
#define CPU_WIN_BASE 0xbfd00000
#define CPU_WIN_MASK 0xbfd00040
#define CPU_WIN_MMAP 0xbfd00080

#define set_cpu_window(id, base, mask, mmap) \
        li      t0, CPU_WIN_BASE          ;  \
        sw      $0, 0x80+id*8(t0)         ;  \
        li      t1, base                  ;  \
        sw      t1, 0x00+id*8(t0)         ;  \
        sw      $0, 0x04+id*8(t0)         ;  \
        li      t1, mask                  ;  \
        sw      t1, 0x40+id*8(t0)         ;  \
        sw      $0, 0x44+id*8(t0)         ;  \
        li      t1, mmap                  ;  \
        sw      t1, 0x80+id*8(t0)         ;  \
        sw      $0, 0x84+id*8(t0)

/* fixup cpu window */
cpu_win_fixup:
	//
	// hit         = (paddr & mask) == (mmap & mask)
	// mapped_addr =  paddr &~mask | mmap & mask
	//
	// mmap[7] -> enable
	// mmap[5] -> block trans enable
	// mmap[4] -> cachable
	// mmap[1:0] -> destination
	//
	// NOTE: the address windows has priority, win0 > win1 > ... > win7

/*	set_cpu_window(0, 0x1c280000, 0xfff80000, 0x1c280083) // camera 512K
	set_cpu_window(1, 0x1c300000, 0xfff00000, 0x1c300081) // dc 1M
	set_cpu_window(2, 0x1fe10000, 0xffffe000, 0x1fe10082) // gmac0	8K
	set_cpu_window(3, 0x1fe10000, 0xffff0000, 0x1fe100d0) // gmac0	64K
	set_cpu_window(4, 0x1f000000, 0xff000000, 0x1f000082) // AXIMUX   16M
	set_cpu_window(5, 0x00000000, 0x00000000, 0x000000f0) // ddr 0
	set_cpu_window(6, 0x00000000, 0x00000000, 0x000000f0) // ddr 0
	set_cpu_window(7, 0x00000000, 0x00000000, 0x000000f0) // ddr 0*/

/*	set_cpu_window(0, 0x1c280000, 0xfff80000, 0x1c2800d3) // camera
//	set_cpu_window(1, 0x1fc00000, 0xfff00000, 0x1fc000f2) //
	set_cpu_window(2, 0x1c300000, 0xfff00000, 0x1c3000d1) // dc 1M
//	set_cpu_window(3, 0x1f000000, 0xff000000, 0x1f0000d2) //
	set_cpu_window(4, 0x00000000, 0x00000000, 0x000000f0)
	set_cpu_window(5, 0x00000000, 0x00000000, 0x000000f0)
	set_cpu_window(6, 0x00000000, 0x00000000, 0x000000f0) // ddr 0
	set_cpu_window(7, 0x00000000, 0x00000000, 0x000000f0) // ddr 0*/

	// after this fixup, the kernel code should be compiled with
	// uncached instruction fetch patch

	/* 配置内存 */
	li msize, MEM_SIZE    
#if !defined(NAND_BOOT_EN)

    /* 
       手册建议，先写寄存器SD_CONFIG[31:0]，然后再写寄存器的SD_CONFIG[63:32]，
       即先写低32位，再写高32位。
       写三次寄存器，最后一次将最高位置一，即使能
    */

    // 写第一次
	li  	t1, 0xbfd00410      // 寄存器SD_CONFIG[31:0]的地址为0xbfd00410
	li		a1, SD_PARA0        // 宏SD_PARA0在sdram_cfg.S中定义的
	sw		a1, 0x0(t1)         // 将宏SD_PARA0的值写入寄存器SD_CONFIG[31:0]
	li		a1, SD_PARA1
	sw		a1, 0x4(t1)         // 同理，将宏SD_PARA1的值写入寄存器SD_CONFIG[63:32]

	// 写第二次
	li		a1, SD_PARA0
	sw		a1, 0x0(t1)
	li		a1, SD_PARA1
	sw		a1, 0x4(t1)

    // 写第三次	
	li		a1, SD_PARA0
	sw		a1, 0x0(t1)
	li		a1, SD_PARA1_EN     // 使能
	sw		a1, 0x4(t1)
//	DELAY(100)
#endif

	/**************************************CACHE*****************************/
	
#define CF_7_SE         (1 << 3)        /* Secondary cache enable */
#define CF_7_SC         (1 << 31)       /* Secondary cache not present */
#define CF_7_TE         (1 << 12)       /* Tertiary cache enable */
#define CF_7_TC         (1 << 17)       /* Tertiary cache not present */
#define CF_7_TS         (3 << 20)       /* Tertiary cache size */
#define CF_7_TS_AL      20              /* Shift to align */
#define NOP8 nop;nop;nop;nop;nop;nop;nop;nop
	
do_caches:
	/* Init caches... */
	li	s7, 0					/* no L2 cache */
	li	s8, 0					/* no L3 cache */

	bal 	cache_init			// 调用汇编函数cache_init
	nop

	mfc0   a0, CP0_CONFIG 		// 将协处理器0的config寄存器的值加载到寄存器a0
	and    a0, a0, ~((1<<12) | 7)	// a0 = a0 & ~((1<<12) | 7)
	or	   a0, a0, 2				// a0 |= 2
	mtc0   a0, CP0_CONFIG 		// 将寄存器a0的值写入协处理器0的config寄存器

/***********************MEMORY DEBUGGING AND COPY SELF TO RAM***********************/
//#include "newtest.32/mydebug.S"
bootnow:
	/* copy program to sdram to make copy fast */
	/* 先将执行拷贝pmon到内存任务的代码，拷贝到内存0xa0000000 */
	
	/* 先确定需要拷贝的代码段为标号121到标号122之间的代码
	 * 由于链接时指定的起始地址是0x80010000，
	 * 而目前正在ROM（SPI NOR FLASH，起始地址为0xBFC00000）运行
	 * 所以需要用寄存器s0来修正一下地址
	 */
	la		t0, 121f			// 将下一个标号121所在地址，加载到寄存器t0
	addu	t0, s0				// 使用寄存器s0修正t0中的(标号121的)地址
	la		t1, 122f			// 将下一个标号122所在地址，加载到寄存器t1
	addu	t1, s0				// 使用寄存器s0修正t1中的(标号122的)地址
	
	li		t2, 0xa0000000		// 将立即数0xa0000000（起始地址）加载到寄存器t2
1:
	lw		v0, (t0)			// 将寄存器t0所指的内存地址开始4字节的数据加载到寄存器v0
	sw		v0, (t2)			// 将寄存器v0的内容保存到寄存器t2所指的内存中
	addu	t0, 4				// 寄存器t0向后移4字节
	addu	t2, 4				// 寄存器t2向后移4字节
	ble t0, t1, 1b				// 如果t0 <= t1，则跳转到上一个标号1处，继续拷贝后面的4字节
	nop

	li		t0, 0xa0000000		// 将立即数0xa0000000加载到寄存器t0
	jr		t0					// 跳转到起始地址0xa0000000处开始执行（拷贝任务）
	nop 	

121: 
	/* Copy PMON to execute location... */
	/* 将固件拷贝到起始地址为0xa0010000的内存空间
	   由于kseg0(0x8000 0000 - 0x9FFF FFFF)和kseg1(0xA000 0000 - 0xBFFF FFFF)是映射到物理内存的相同区域
	   即拷贝到0xA000 0000开始的kseg1，就相当于拷贝到0x8000 0000开始的kseg0
	   这就是为什么链接时，指定的地址是0x8001 0000，而拷贝的目标起始地址是0xA001 0000
	*/
	la		a0, _start			// 加载符号start所在地址0x80010000加载到寄存器a0中
	addu	a1, a0, s0			// 使用寄存器s0修正寄存器a0中的地址，a1=0xBFC00000
	la		a2, __bss_start			// 加载_edata（链接脚本中的一个符号）到寄存器a2
	or		a0, 0xa0000000		// a0 = a0 | 0xa0000000 = 0xa0010000
	or		a2, 0xa0000000		// a2 = a2 | 0xa0000000，修正地址_edata
	subu	t1, a2, a0			// t1 = a2 - a0，即计算从start到_edata之间的长度（字节数）
	srl t1, t1, 2				// t1 >>= 2，即t1除以4。(和前面类似，每次拷贝4字节，所以除以4)
								// 似乎t1计算结果没有被使用，马上就被后面的覆盖了

	move	t0, a0				// t0 = a0 = 0xa0010000 (目标起始地址)
	move	t1, a1				// t1 = a1 = 0xBFC00000 (start在ROM中的地址，源起始地址)
	move	t2, a2				// t2 = a2 (_edata在ROM中的地址，源结束地址)

	/* copy text section */
1:	and t3, t0, 0x0000ffff		// t3 = t0 & 0x0000ffff，取低16位
	bnez	t3, 2f				// 如果t3不等于0，则跳转到下一个标号2处继续执行，t3的计算结果似乎没被使用，就被后面的覆盖了
	nop
2:	lw		t3, 0(t1)			// 从源地址t1处加载4字节到寄存器t3中
	nop
	sw		t3, 0(t0)			// 将寄存器t3中的4字节数据保存到目标地址t0处
	addu	t0, 4				// 目标地址t0后移4字节
	addu	t1, 4				// 源地址t1	  后移4字节
	bne t2, t0, 1b				// 如果t2不等于t0，则跳到上一个标号1处继续拷贝，总的来说就是判断拷贝是否结束
	nop
	/* copy text section done. */
	
	/* clear bss */
	la	t0, __bss_start
	la	t1, __bss_end
_clr_bss_loop:
	sw	zero, 0(t0)
	bne	t0, t1, _clr_bss_loop
	addiu	t0, t0, 4

	/* disable interrupt */
	mfc0	t0, CP0_STATUS
	and 	t0, 0xfffffffe	# By default it will be disabled.
	mtc0	t0, CP0_STATUS	# Set CPU to disable interrupt.
	nop

	/* disable cache */
	mfc0	t0, CP0_CONFIG
	and t0, 0xfffffff8
	or	t0, 0x2 	# disable,!default value is not it!
	mtc0	t0, CP0_CONFIG	# Set CPU to disable cache.
	nop

	/* jump to RT-Thread RTOS */
	jal	rtthread_startup
	nop

	/* restart, never die */
	j	_start
	nop
	

122:

stuck:
	b	stuck
	nop
#endif

	.extern tlb_refill_handler
	.extern cache_error_handler

	/* Exception Handler */

	/* 0x0 - TLB refill handler */
	.section .vectors.1, "ax", %progbits
	.global tlb_refill_exception
	.type	tlb_refill_exception,@function
tlb_refill_exception:
	j	tlb_refill_handler
	nop
	
	/* 0x100 - Cache error handler */
	.section .vectors.2, "ax", %progbits
	j	cache_error_handler
	nop
    
	/* 0x180 - Exception/Interrupt handler */
	.section .vectors.3, "ax", %progbits
	.global general_exception
	.type	general_exception,@function
general_exception:
	j	_general_exception_handler
	nop
    
	/* 0x200 - Special Exception Interrupt handler (when IV is set in CP0_CAUSE) */
	.section .vectors.4, "ax", %progbits
	.global irq_exception
	.type	irq_exception,@function
irq_exception:
	j	_irq_handler
	nop
	
	.section .vectors, "ax", %progbits
	.extern mips_irq_handle

	/* general exception handler */
_general_exception_handler:
	.set	noreorder
	la	k0, mips_irq_handle
	jr	k0
	nop
	.set	reorder

	/* interrupt handler */
_irq_handler:
	.set	noreorder
	la	k0, mips_irq_handle
	jr	k0
	nop
	.set	reorder
