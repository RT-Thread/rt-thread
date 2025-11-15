/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     RT-Thread Panic implementation
 */
//! Panic handling for RT-Thread Rust runtime
//! 
//! This module provides panic handling functionality for the RT-Thread Rust runtime,
//! including context-aware panic handling and the global panic handler.

use crate::print;

/// Check if we're in an atomic context and panic if so
/// 
/// This function checks if the current execution context is an interrupt context
/// and panics with a descriptive message if it is, as certain operations are
/// not safe to perform in interrupt contexts.
/// 
/// # Arguments
/// 
/// * `s` - A string slice describing the operation that triggered the check
pub fn panic_on_atomic_context(s: &str) {
    use crate::api::is_irq_context;
    if is_irq_context() {
        panic!("In irq context {}", s);
    }
}

/// Global panic handler for the RT-Thread Rust runtime
/// 
/// This function is called when a panic occurs in the Rust code. It prints
/// the panic information and then calls the weak `__rust_panic` function
/// to handle the actual panic behavior.
/// 
/// # Arguments
/// 
/// * `info` - Panic information containing details about the panic
#[panic_handler]
#[inline(never)]
fn panic(info: &core::panic::PanicInfo) -> ! {
    print!("{:}", info);
    __rust_panic()
}

/// Weak panic implementation
/// 
/// This is a weak symbol that can be overridden by user code to provide
/// custom panic behavior. The default implementation simply loops forever.
/// 
/// # Safety
/// 
/// This function is marked as `unsafe` because it's a no-mangle function
/// that can be overridden by external code.
#[linkage = "weak"]
#[unsafe(no_mangle)]
fn __rust_panic() -> ! {
    // Default weak panic handler: intentionally loops forever to halt execution.
    // Override this function for custom panic behavior.
    print!("Entered weak panic handler: system will halt.");
    loop {}
}