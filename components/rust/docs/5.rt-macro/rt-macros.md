# rt_macros Usage Guide

rt_macros is a collection of Rust procedural macros for RT-Thread. It helps export Rust functions as system entry points, initialization entries, or shell commands in a `no_std` environment, so they integrate cleanly with RT-Thread’s startup and command mechanisms.

## Background and Goals

In `no_std` mode, the traditional `main` function is not directly available. rt_macros generates C-ABI-compatible wrapper entries and the required link-section items so RT-Thread can discover and invoke the corresponding Rust logic during startup or shell command scanning.

## Provided Macros (aligned with RT-Thread conventions)

- `rt_thread_main!`: Marks the Rust main-thread entry.
  - Function signature: `fn()` (no parameters, no return value).
  - Constraints: no `const`, `unsafe`, `async`, varargs; no explicit ABI; no generics; default visibility (non-`pub`).
  - Purpose: exports an entry that RT-Thread can recognize and call as the main thread.

- `rt_component_export!`: Exports a component initialization entry.
  - Function signature: `fn()`.
  - Same constraints; optional parameter: `name = "..."` (used to generate internal symbol names).
  - Link section: places the function pointer into `.rti_fn.4`, executed during the component initialization phase.

- `rt_app_export!`: Exports an application initialization entry.
  - Function signature: `fn()`.
  - Same constraints; optional parameter: `name = "..."`.
  - Link section: places the function pointer into `.rti_fn.6`, executed during the application initialization phase.

- `msh_cmd_export!`: Exports an RT-Thread shell command.
  - Function signature: `fn(args: vec::IntoIter<rt_rust::param::ParamItem>)`.
  - Attributes: `name` (required, command name), `desc` (optional, command description).
  - Link sections and data:
    - Generates a command descriptor struct placed into `FSymTab`.
    - Command name and description are `\0`-terminated byte arrays placed into `.rodata.name`.
  - Invocation wrapper: generates an `extern "C"` wrapper `(argc, argv)`, converts `argv` to `Vec<ParamItem>`, and calls the original Rust command function.

## Link Sections and Startup Flow

- Component init entries: `.rti_fn.4`
- Application init entries: `.rti_fn.6`
- Shell command table: `FSymTab`
- Shell name/description strings: `.rodata.name`

During startup or shell scanning, RT-Thread traverses these sections to register or invoke the corresponding Rust logic.

## Usage Examples

### Main-thread entry
```rust
use rt_macros::rt_thread_main;

#[rt_thread_main]
fn main() {
    // Main thread logic here
}
```

### Component export
```rust
use rt_macros::rt_component_export;

#[rt_component_export(name = "rust_component_registry")]
fn my_component_init() {
    // Component init logic
}
```

### Application export
```rust
use rt_macros::rt_app_export;

#[rt_app_export(name = "rust_app_example")]
fn my_app_init() {
    // Application init logic
}
```

### Shell command export
```rust
use rt_macros::msh_cmd_export;

#[msh_cmd_export(name = "hello", desc = "Say hello")]
fn hello_cmd(args: vec::IntoIter<rt_rust::param::ParamItem>) {
    // Handle args and print output, etc.
}
```

## Interacting with C Code

When calling exported Rust entries from C, declare the prototype and use `extern "C"` for the calling convention, for example:

```c
extern "C" void rust_function_name(void);
```

The command export macro generates a wrapper with `(argc, argv)`; RT-Thread’s command system calls this wrapper and passes the arguments to the original Rust function.

## Common Issues and Diagnostics

- Compile-time errors: the macros produce explicit diagnostics if the function signature does not match (e.g., must be `fn()` or a specific parameter shape). Adjust the function to meet the requirements above.
- Visibility requirement: keep the entry function at default (non-`pub`) visibility to satisfy macro constraints.
- `alloc` dependency: the shell command macro uses `alloc::vec::Vec`, ensure an allocator is available at runtime (RT-Thread usually provides one).

## References

- [RUST support for rt-thread](https://github.com/rust-for-rtthread/rtt_rust)