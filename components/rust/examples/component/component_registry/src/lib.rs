/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
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

/* Demonstrate the new modular macro interface */
use rt_macros::rt_component_export;
use rt_rust::param::{Param, ParamItem};
use rt_rust::println;

/* Re-export component functionality for other modules */
#[cfg(feature = "enable-log")]
pub use em_component_log::*;
#[cfg(feature = "enable-log")]
use em_component_log::logging::Level;

/** Unified component registration entrypoint */
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

/** Provide a no-op implementation when no component feature is enabled */
#[cfg(not(feature = "enable-log"))]
pub extern "C" fn component_init() {
    /* Empty implementation to ensure the library still links */
}
