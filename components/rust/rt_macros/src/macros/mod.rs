/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-29     foxglove     RT-Thread Rust macro module
 */

//! RT-Thread Rust Macro Module
//! 
//! This module contains various macro definitions for RT-Thread system:
//! 
//! - `rt_thread_main!` - Main thread entry macro
//! - `rt_component_export!` - Component export macro
//! - `rt_app_export!` - Application export macro
//! - `msh_cmd_export!` - Shell command export macro

pub mod main;
pub mod component;
pub mod app;
pub mod cmd;
