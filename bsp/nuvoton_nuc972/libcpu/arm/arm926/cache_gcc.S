/*
 * File      : cache_gcc.S
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017年3月21日     Urey         the first version
 */


#define _CACHE_LINE_SIZE           32
#define _CACHE_LOOP_OP_MAX_SIZE    (16 * 1024)

.globl rt_hw_dcache_flush_range
rt_hw_dcache_flush_range:
    MCR     p15, 0, R0, c7, c10, 1
    ADD     R0, R0, #_CACHE_LINE_SIZE
    CMP     R0, R1
    BCC     rt_hw_dcache_flush_range
    BX      LR

.globl rt_hw_dcache_flush_all
rt_hw_dcache_flush_all:
    MRC     p15, 0, R15, c7, c10, 3                                     ;/*  测试回写指令                */
    BNE     rt_hw_dcache_flush_all
    MOV     R0, #0
    MCR     p15, 0, R0, c7, c10, 4                                      ;/* Drain write-buffer           */
    BX      LR

.globl rt_hw_dcache_clear_all
rt_hw_dcache_clear_all:
    MRC     p15, 0, R15, c7, c14, 3                                     ;/*  测试回写并无效指令          */
    BNE     rt_hw_dcache_clear_all
    MOV     R0, #0
    MCR     p15, 0, R0, c7, c10, 4                                      ;/* Drain write-buffer           */
    BX      LR

.globl rt_hw_dcache_invalidate_range
rt_hw_dcache_invalidate_range:
	MCR     p15, 0, R0, c7, c6, 1
    ADD     R0, R0, #_CACHE_LINE_SIZE
    CMP     R0, R1
    BCC     rt_hw_dcache_invalidate_range
    BX      LR

.globl rt_hw_dcache_invalidate_all
rt_hw_dcache_invalidate_all:
    MOV     R0, #0
    MCR     p15, 0, R0, c7, c6, 0
    BX      LR
