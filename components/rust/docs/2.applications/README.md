# RT-Thread Rust Example User Applications

This directory contains a series of example user applications and components that demonstrate Rust programming capabilities in RT-Thread. These examples showcase how to use the Rust programming language for system programming in the RT-Thread real-time operating system.

## Directory Structure

```
example_usrapp/
├── SConscript              # SCons build script
├── fs/                     # File system operation examples
├── loadlib/                # Dynamic library loading examples
├── mutex/                  # Mutex synchronization examples
├── param/                  # Parameter handling examples
├── queue/                  # Message queue examples
├── semaphore/              # Semaphore synchronization examples
└── thread/                 # Thread management examples
```

## Build and Run

### Prerequisites

1. Ensure Rust support is enabled in RT-Thread configuration (`RT_USING_RUST`), and enable examples compilation (`RT_USING_RUST_EXAMPLES`) and application examples compilation (`RT_RUST_BUILD_APPLICATIONS`).
2. Install Rust toolchain and related dependencies
3. Configure the correct cross-compilation environment

### Build Steps

1. Execute in the RT-Thread project root directory:
   ```bash
   scons -j$(nproc)
   ```

2. The build system will automatically:
   - Detect enabled RT-Thread configurations
   - Enable corresponding Rust features based on configuration
   - Compile all example applications as static libraries
   - Link to the final firmware image

### Running Examples

After RT-Thread system startup, you can run various examples through the command line:

```bash
# View all available examples
help

# Run thread example
rust_thread_demo

# Run file system example
rust_file_demo

# Other examples similarly...
```

## Technical Features

### Dependency Management

All example applications depend on the following core components:
- `rt-rust`: RT-Thread Rust binding library
- `macro_main`: Main function macro support

The `fs` example also depends on the logging component:
- `em_component_log`: Logging component

### Feature Configuration

- Support for conditional compilation features
- Automatic feature detection and enabling
- Modular functionality configuration

### Build System Integration

- Fully integrated with SCons build system
- Support for clean and incremental builds
- Automatic dependency management

## Development Guide

### Adding New Examples

1. Create a new directory under `example_usrapp/`
2. Add `Cargo.toml` configuration file
3. Implement example code in `src/lib.rs`
4. Use `#[macro_main_use]` macro to define entry point

### Example Template

```rust
#![no_std]

use macro_main::macro_main_use;
use rt_rust::param::Param;
use rt_rust::println;

#[macro_main_use(
    name = "your_demo_name",
    component = "Whether it's a component example",
    app = "Whether it's a user application example",
    cmd = true,
    desc = "Your demo description."
)]
fn main(_param: Param) {
    println!("Hello from your demo!");
    // Your example code...
}
```

## Troubleshooting

### Common Issues

1. **Compilation failure**: Check if Rust toolchain is correctly installed
2. **Linking errors**: Confirm cross-compilation target configuration is correct
3. **Runtime errors**: Check stack size and memory configuration

### Debugging Suggestions

1. Use `println!` for basic debug output
2. Enable logging features to get detailed information
3. Check if RT-Thread configuration items are correctly enabled