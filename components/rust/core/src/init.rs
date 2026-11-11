/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-15     foxglove     1.0 version
 */

/* Rust component initialization module
 * Handles initialization of the Rust component within RT-Thread.
 */

use crate::println;

#[no_mangle]
pub extern "C" fn rust_init() -> i32 {
    println!("[rust_init]: Rust component initialized!");    
    0
}
