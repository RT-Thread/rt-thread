
/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-23     foxglove     log component demo
 */
#![no_std]

extern crate alloc;

/* When the `enable-log` feature is enabled, expose logging module and helpers */
#[cfg(feature = "enable-log")]
pub mod logging;
#[cfg(feature = "enable-log")]
use rt_rust::println;
#[cfg(feature = "enable-log")]
use crate::logging::Level;

/* Import panic handler parameters from rt_rust library */
use rt_rust::param::{Param, ParamItem};

/* Provide a no-op implementation when the `enable-log` feature is disabled */
#[cfg(not(feature = "enable-log"))]
pub extern "C" fn component_init() {
    /* Empty implementation to ensure the library still links */
}
