/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     RT-Thread Panic implementation
 */
use crate::print;

pub fn panic_on_atomic_context(s: &str) {
    use crate::api::is_irq_context;
    if is_irq_context() {
        panic!("In irq context {}", s);
    }
}

#[panic_handler]
#[inline(never)]
fn panic(info: &core::panic::PanicInfo) -> ! {
    print!("{:}", info);
    __rust_panic()
}

#[linkage = "weak"]
#[no_mangle]
fn __rust_panic() -> ! {
    /* Default weak panic handler: loops forever to halt execution. */
    print!("Entered weak panic handler: system will halt.");
    loop {}
}
