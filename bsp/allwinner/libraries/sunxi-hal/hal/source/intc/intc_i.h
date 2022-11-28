/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                              interrupt  module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : intc_i.h
* By      : Sunny
* Version : v1.0
* Date    : 2012-5-3
* Descript: interrupt controller internal header.
* Update  : date                auther      ver     notes
*           2012-5-3 13:27:40   Sunny       1.0     Create this file.
*********************************************************************************************************
*/

#ifndef __INTC_I_H__
#define __INTC_I_H__

#include <hal_interrupt.h>
#include <sunxi_hal_common.h>

/*interrput controller registers Offset*/
typedef struct intc_regs {
    /*offset 0x00 */
    volatile u32 vector;
    volatile u32 base_addr;
    volatile u32 reserved0;
    volatile u32 control;

    /*offset 0x10 */
    volatile u32 pending;
    volatile u32 pending1;
    volatile u32 pending2;
    volatile u32 reserved1[9];

    /*offset 0x40 */
    volatile u32 enable;
    volatile u32 enable1;
    volatile u32 enable2;
    volatile u32 reserved2[1];

    /*offset 0x50 */
    volatile u32 mask;
    volatile u32 mask1;
    volatile u32 mask2;
    volatile u32 reserved3[5];

    /*offset 0x70 */
    volatile u32 fast_forcing;
    volatile u32 reserved4[3];

    /*offset 0x80 */
    volatile u32 priority0;
    volatile u32 priority1;
    volatile u32 reserved5[14];

    /*offset 0xc0 */
    volatile u32 group_config0;
    volatile u32 group_config1;
    volatile u32 group_config2;
    volatile u32 group_config3;
} intc_regs_t;

struct int_isr_node {
    __pISR_hdle_t pisr;     /*ISR process handler */
    void *parg;     /*argument for isr process */
};

/*local functions*/
s32 intc_init(void);
s32 intc_exit(void);
s32 intc_set_fiq_triggermode(u32 triggermode);
s32 intc_enable_interrupt(u32 intno);
s32 intc_disable_interrupt(u32 intno);
u32 intc_get_current_interrupt(void);
s32 intc_set_mask(u32 intno, u32 mask);
s32 intc_set_group_config(u32 grp_irq_num, u32 mask);

s32 isr_default(int dummy, void *arg);

/*pointer of register list*/
extern struct intc_regs *pintc_regs;

#endif /*__INTC_I_H__*/
