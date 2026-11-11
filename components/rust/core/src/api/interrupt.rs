/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     latest version
 */
use crate::bindings::*;

#[cfg(not(feature = "smp"))]
unsafe fn irq_close() -> rt_base_t {
    rt_hw_interrupt_disable()
}
#[cfg(feature = "smp")]
unsafe fn irq_close() -> rt_base_t {
    rt_cpus_lock()
}

#[cfg(not(feature = "smp"))]
unsafe fn irq_open(f: rt_base_t) {
    rt_hw_interrupt_enable(f)
}
#[cfg(feature = "smp")]
unsafe fn irq_open(f: rt_base_t) {
    rt_cpus_unlock(f)
}

pub fn no_irq<F, T>(f: F) -> T
where
    F: FnOnce() -> T,
{
    let level;
    let out;
    unsafe { level = irq_close() }
    out = f();
    unsafe { irq_open(level) }
    out
}

#[derive(Debug, Copy, Clone)]
pub struct InterruptFlag(rt_base_t);

pub const INTERRUPT_FLAG_INIT: InterruptFlag = InterruptFlag { 0: 0 as _ };

pub fn interrupt_disable() -> InterruptFlag {
    unsafe { InterruptFlag(irq_close()) }
}

pub fn interrupt_enable(f: InterruptFlag) {
    unsafe { irq_open(f.0) }
}

pub fn interrupt_enter() {
    unsafe {
        rt_interrupt_enter();
    }
}

pub fn interrupt_leave() {
    unsafe {
        rt_interrupt_leave();
    }
}

pub fn is_irq_context() -> bool {
    unsafe { rt_interrupt_get_nest() != 0 }
}