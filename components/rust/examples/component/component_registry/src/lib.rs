/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-25     foxglove     Component registry for unified component registration
 * 2025-10-29     foxglove     Updated to demonstrate new modular macro interface
 */
#![no_std]

extern crate alloc;

// 演示新的模块化宏接口
use rt_macros::rt_component_export;
use rt_rust::param::{Param, ParamItem};
use rt_rust::println;

// 重新导出组件功能，供其他模块使用
#[cfg(feature = "enable-log")]
pub use em_component_log::*;
#[cfg(feature = "enable-log")]
use em_component_log::logging::Level;

/// 统一的组件注册入口点
#[cfg(feature = "enable-log")]
#[rt_component_export(name = "rust_component_registry")]
fn init_registry_component() {
    println!("[logging component init] hello world");
    log!(Level::Info, "hello world");
    info!("hello world");
    warn!("hello world");
    error!("hello world");
    trace!("hello world");
    debug!("hello world");
}

/// 当没有启用任何组件特性时的空实现
#[cfg(not(feature = "enable-log"))]
pub extern "C" fn component_init() {
    // 空实现，确保库仍然可以被链接
}