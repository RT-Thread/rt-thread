/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     Basic library module template
 */
#![no_std]
/* Bring rt-rust's println! macro into scope */ 
use rt_rust::println;
use core::ffi::{c_char, CStr};
#[no_mangle]
pub extern "C" fn rust_mylib_println(s: *const c_char) {
    if s.is_null() {
        println!("");
    } else {
            let cs = unsafe {CStr::from_ptr(s)};
            match cs.to_str() {
                Ok(msg) => println!("{}", msg),
                Err(_) => println!("[invalid UTF-8]"),
            }
    }
}

#[no_mangle]
pub extern "C" fn rust_mylib_add(a: usize, b: usize) -> usize {
    a + b
}
