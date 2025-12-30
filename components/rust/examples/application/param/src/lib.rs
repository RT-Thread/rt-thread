/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     param test demo
 * 2025-10-29     foxglove     Updated to demonstrate new modular macro interface
 */
#![no_std]

extern crate alloc;

use alloc::string::String;
use rt_macros::{rt_app_export, msh_cmd_export};
use rt_rust::param::Param;
use rt_rust::println;

// 演示新的模块化宏接口 - 使用 msh_cmd_export 导出参数测试命令
#[msh_cmd_export(name = "rust_param_demo", desc = "Rust parameter demo")]
fn main(param: Param) {
    for i in param {
        println!("{}", String::from_utf8_lossy(&*i))
    }
}
