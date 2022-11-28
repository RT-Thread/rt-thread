/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                              interrupt  module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : intc.h
* By      : Sunny
* Version : v1.0
* Date    : 2012-4-27
* Descript: interrupt controller public header.
* Update  : date                auther      ver     notes
*           2012-4-27 10:52:56  Sunny       1.0     Create this file.
*********************************************************************************************************
*/

#ifndef __INTC_H__
#define __INTC_H__

#include <hal_interrupt.h>
#include <sunxi_hal_common.h>

/*
*********************************************************************************************************
*                                       INIT INTERRUPT MANAGER
*
* Description:  initialize interrupt manager.
*
* Arguments  :  none.
*
* Returns    :  OK if initialize interrupt manager succeeded, others if failed.
*********************************************************************************************************
*/
s32 interrupt_init(void);

/*
*********************************************************************************************************
*                                       EXIT INTERRUPT MANAGER
*
* Description:  exit interrupt manager.
*
* Arguments  :  none.
*
* Returns    :  OK if exit interrupt manager succeeded, others if failed.
*********************************************************************************************************
*/
s32 interrupt_exit(void);

/*
*********************************************************************************************************
*                                           ENABLE INTERRUPT
*
* Description:  enable a specific interrupt.
*
* Arguments  :  intno : the number of interrupt which we want to enable.
*
* Returns    :  OK if enable interrupt succeeded, others if failed.
*********************************************************************************************************
*/
s32 interrupt_enable(u32 intno);

/*
*********************************************************************************************************
*                                           DISABLE INTERRUPT
*
* Description:  disable a specific interrupt.
*
* Arguments  :  intno : the number of interrupt which we want to disable.
*
* Returns    :  OK if disable interrupt succeeded, others if failed.
*********************************************************************************************************
*/
s32 interrupt_disable(u32 intno);

/*
*********************************************************************************************************
*                                           SET NMI TRIGGER
*
* Description:  set nmi trigger.
*
* Arguments  :  type : the trigger type.
*
* Returns    :  OK if set trigger type succeeded, others if failed.
*********************************************************************************************************
*/
s32 interrupt_set_nmi_trigger(u32 type);

s32 interrupt_set_mask(u32 intno, u32 mask);
s32 interrupt_set_group_config(u32 grp_irq_num, u32 mask);
/*
*********************************************************************************************************
*                                           INSTALL ISR
*
* Description:  install ISR for a specific interrupt.
*
* Arguments  :  intno   : the number of interrupt which we want to install ISR.
*               pisr    : the ISR which to been install.
*               parg    : the argument for the ISR.
*
* Returns    :  OK if install ISR succeeded, others if failed.
*
* Note       :  the ISR execute entironment : CPU disable interrupt response.
*********************************************************************************************************
*/
s32 install_isr(u32 intno, __pISR_hdle_t pisr, void *parg);

/*
*********************************************************************************************************
*                                           UNINSTALL ISR
*
* Description:  uninstall ISR for a specific interrupt.
*
* Arguments  :  intno   : the number of interrupt which we want to uninstall ISR.
*               pisr    : the ISR which to been uninstall.
*
* Returns    :  OK if uninstall ISR succeeded, others if failed.
*********************************************************************************************************
*/
s32 uninstall_isr(u32 intno, __pISR_hdle_t pisr);


/*
*********************************************************************************************************
*                                           INTERRUPT ENTRY
*
* Description:  the entry of CPU IRQ, mainly for CPU IRQ exception.
*
* Arguments  :  none.
*
* Returns    :  OK if process CPU IRQ succeeded, others if failed.
*********************************************************************************************************
*/
s32 interrupt_entry(void);

s32 interrupt_query_pending(u32 intno);
s32 interrupt_clear_pending(u32 intno);

u32 interrupt_get_current_intno(void);

s32 interrupt_standby_enter(void);
s32 interrupt_standby_exit(void);

#endif /* __INTC_H__ */
