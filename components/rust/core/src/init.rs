/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-15     foxglove     1.0 version
 */

//! Rust component initialization module
//! 
//! Handles the initialization of the Rust component within RT-Thread

use crate::println;

/// Component initialization function
/// This function is called during RT-Thread system initialization
#[no_mangle]
pub extern "C" fn rust_init() -> i32 {
    // Test the print! and println! macros
    println!("[rust_init]: Rust component initialized!");    
    0
}