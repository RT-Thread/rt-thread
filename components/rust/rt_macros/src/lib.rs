/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-29   foxglove     Modular macro library for RT-Thread Rust
 */

/*! RT-Thread Rust Macro Library

This library provides Rust macros for RT-Thread system, including:

- `rt_thread_main!` - Main thread entry macro
- `rt_component_export!` - Component export macro
- `rt_app_export!` - Application export macro
- `msh_cmd_export!` - Shell command export macro

## Usage Examples

### Main Thread Entry
```rust
use rt_macros::rt_thread_main;

#[rt_thread_main]
fn main() {
    println!("Hello RT-Thread!");
}
```

### Component Export
```rust
use rt_macros::rt_component_export;

#[rt_component_export]
fn my_component_init() {
    // Component initialization code
}
```

### Application Export
```rust
use rt_macros::rt_app_export;

#[rt_app_export]
fn my_app_init() {
    // Application initialization code
}
```

### Shell Command Export
```rust
use rt_macros::msh_cmd_export;

#[msh_cmd_export(name = "hello", desc = "Say hello")]
fn hello_cmd(args: vec::IntoIter<rt_rust::param::ParamItem>) {
    println!("Hello from shell command!");
}
```
*/

#[macro_use]
extern crate quote;

use proc_macro::TokenStream;

/* Import modular macro definitions */
mod macros;

/* Modular macro definitions */
/* RT-Thread main thread entry macro */
#[proc_macro_attribute]
pub fn rt_thread_main(args: TokenStream, input: TokenStream) -> TokenStream {
    macros::main::rt_thread_main(args, input)
}

/* RT-Thread component export macro */
#[proc_macro_attribute]
pub fn rt_component_export(args: TokenStream, input: TokenStream) -> TokenStream {
    macros::component::rt_component_export(args, input)
}

/* RT-Thread application export macro */
#[proc_macro_attribute]
pub fn rt_app_export(args: TokenStream, input: TokenStream) -> TokenStream {
    macros::app::rt_app_export(args, input)
}

/* MSH command export macro */
#[proc_macro_attribute]
pub fn msh_cmd_export(args: TokenStream, input: TokenStream) -> TokenStream {
    macros::cmd::msh_cmd_export(args, input)
}
