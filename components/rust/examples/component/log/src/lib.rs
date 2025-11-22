
/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-23     foxglove     log component demo
 */
#![no_std]

extern crate alloc;

#[cfg(feature = "enable-log")]
pub mod logging;
#[cfg(feature = "enable-log")]
use rt_rust::println;
#[cfg(feature = "enable-log")]
use crate::logging::Level;
// 导入rust库的panic_handler
use rt_rust::param::{Param, ParamItem};

// 当 enable-log feature 未启用时，提供一个空的实现
#[cfg(not(feature = "enable-log"))]
pub extern "C" fn component_init() {
    // 空实现，确保库仍然可以被链接
}