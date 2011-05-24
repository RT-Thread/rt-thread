/*
 * rt_base_t rt_hw_interrupt_disable()
 */
    .globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:

/*
 * void rt_hw_interrupt_enable(rt_base_t level)
 */
    .globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:

/*
 * void rt_hw_context_switch_to(rt_uint32 to)/*
 * a0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * a0 --> from
 * a1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to)/*
 */
    .globl rt_thread_switch_interrput_flag
    .globl rt_interrupt_from_thread
    .globl rt_interrupt_to_thread
    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:

