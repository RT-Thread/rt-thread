/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     thread test demo
 * 2025-10-29     foxglove     Updated to demonstrate new modular macro interface
 */
#![no_std]

use core::time::Duration;
use rt_macros::msh_cmd_export;
use rt_rust::param::Param;
use rt_rust::println;
use rt_rust::thread;
use rt_rust::time;

#[msh_cmd_export(name = "rust_thread_demo", desc = "Rust example app.")]
fn main(_param: Param) {
    let _ = thread::Thread::new()
        .name("thread 1")
        .stack_size(1024)
        .start(move || {
            loop {
                println!("thread a will sleep 1s");
                time::sleep(Duration::new(1, 0));
            }
        });

    let _ = thread::Thread::new()
        .name("thread 2")
        .stack_size(1024)
        .start(move || {
            loop {
                println!("thread b will sleep 3s");
                time::sleep(Duration::new(3, 0));
            }
        });
}
