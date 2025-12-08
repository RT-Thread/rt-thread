/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     queue test demo
 * 2025-10-29     foxglove     Updated to demonstrate new modular macro interface
 */
#![no_std]

extern crate alloc;

use alloc::string::String;
use alloc::sync::Arc;
use core::time::Duration;
use rt_macros::msh_cmd_export;
use rt_rust::queue::Queue;
use rt_rust::param::Param;
use rt_rust::println;
use rt_rust::thread;
use rt_rust::time;

#[msh_cmd_export(name = "rust_queue_demo", desc = "Rust example app.")]
fn main(_param: Param) {
    let send = Arc::new(Queue::new(2).unwrap());
    let recv = send.clone();

    let _ = thread::Thread::new()
        .name("thread 1")
        .stack_size(1024)
        .start(move || {
            loop {
                time::sleep(Duration::new(1, 0));
                send.send(String::from("msg"), 0).unwrap();
            }
        });
    time::sleep(Duration::new(1, 0));
    let _ = thread::Thread::new()
        .name("thread 2")
        .stack_size(1024)
        .start(move || {
            loop {
                println!("waiting!");
                let a = recv.recv_wait_forever().unwrap();
                println!("recv {}", a);
            }
        });
}

