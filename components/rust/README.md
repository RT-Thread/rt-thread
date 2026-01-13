# RT-Thread Rust Component

RT-Thread's general-purpose Rust component for the RTOS, with automatic detection of multiple architectures.

## Features

- Multi-architecture support: automatically detects ARM, AArch64, and RISC-V target architectures.
- Zero configuration: no manual platform target setup required.
- Modular design: core modules and example code are clearly separated.
- RT-Thread integration: full access to RT-Thread kernel APIs.

## Project Layout

```
rust/
├── README.md                    # Project documentation
├── Kconfig                      # Configuration options
├── SConscript                   # Top-level build script
├── core/                        # Core Rust library
│   ├── Cargo.toml               # Rust project config
│   ├── SConscript               # Core library build script
│   ├── rust_cmd.c               # MSH command registration
│   └── src/                     # Source directory
│       ├── lib.rs               # Library entry
│       ├── init.rs              # Component initialization
│       ├── allocator.rs         # Memory allocator
│       ├── panic.rs             # Panic handler
│       ├── bindings/            # RT-Thread API FFI bindings
│       ├── api/                 # RT-Thread API Rust wrappers
│       ├── prelude/             # Common imports
│       ├── thread.rs            # Thread operations
│       ├── mutex.rs             # Mutex
│       ├── sem.rs               # Semaphore
│       ├── queue.rs             # Message queue
│       ├── time.rs              # Time functions
│       ├── fs.rs                # Filesystem
│       ├── libloader.rs         # Dynamic library loading
│       ├── param.rs             # Parameter passing
│       └── out.rs               # Output functions
├── rt_macros/                   # Rust procedural macros
│   ├── Cargo.toml               # Macros crate config
│   └── src/                     # Macros source
│       ├── lib.rs               # Macros crate entry
│       └── macros/              # Macro implementations
│           ├── mod.rs           # Module definitions
│           ├── main.rs          # main macro
│           ├── component.rs     # component export macro
│           ├── app.rs           # application export macro
│           └── cmd.rs           # command export macro
├── examples/                    # Example code
│   ├── Kconfig                  # Examples config
│   ├── SConscript               # Examples build scripts
│   ├── application/             # Application examples
│   ├── component/               # Component examples
│   └── modules/                 # Dynamic module examples
├── docs/                        # Detailed documentation
└── tools/                       # Build tools
    ├── build_support.py        # Build support functions
    ├── build_component.py      # Component build tool
    ├── build_usrapp.py         # User app build tool
    ├── feature_config_component.py  # Component feature config
    └── feature_config_examples.py   # Example feature config
```

## Quick Start

### Prerequisites

1. Install Rust:

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

2. Add target platforms (choose according to your architecture):

```bash
# RISC-V64 (soft-float)
rustup target add riscv64imac-unknown-none-elf

# ARM Cortex-M4
rustup target add thumbv7em-none-eabi

# Add other targets that match your toolchain/ABI as needed
```

### Build

```bash
# Enable the Rust component in menuconfig
scons --menuconfig
# Navigate to: Rust Component Support → Enable

# Build
scons

# Clean
scons -c
```

## Supported Architectures

| Architecture   | Target                            | Auto-detect |
| -------------- | --------------------------------- | ----------- |
| Cortex-M3      | thumbv7m-none-eabi                | ✓           |
| Cortex-M4/M7   | thumbv7em-none-eabi               | ✓           |
| Cortex-M4F/M7F | thumbv7em-none-eabihf             | ✓           |
| ARMv7-A        | armv7a-none-eabi                  | ✓           |
| AArch64        | aarch64-unknown-none              | ✓           |
| RISC-V32       | riscv32ima[f]c-unknown-none-elf   | ✓           |
| RISC-V64       | riscv64[gc/imac]-unknown-none-elf | ✓           |

The build system will automatically determine the correct target from the RT-Thread configuration.

## Example MSH Commands

- `rust_param_demo`  — Parameter passing demo
- `rust_thread_demo` — Thread demo
- `rust_mutex_demo`  — Mutex demo
- `rust_queue_demo`  — Queue demo
- `rust_sem_demo`    — Semaphore demo
- `rust_dl_demo`     — Dynamic module loading demo
- `rust_fs_demo`     — File and logging operations demo (requires logging component)

## Configuration Options

Available in menuconfig:

- `RT_USING_RUST` - Enable/disable the Rust component
- `RT_RUST_CORE` - Enable/disable the core support library
- `RUST_INIT_COMPONENT` - Initialize automatically at startup
- `RT_USING_RUST_EXAMPLES`
  - `RT_RUST_BUILD_APPLICATIONS`: Enable/disable user applications
  - `RT_RUST_BUILD_COMPONENTS`: Enable/disable components
  - `RT_RUST_BUILD_MODULES`: Enable/disable building dynamic modules
- `RUST_DEBUG_BUILD` - Enable/disable debug build

## Technical Details

- No-std: embedded-friendly `#![no_std]` environment.
- FFI: seamless C/Rust interoperability.
- Static linking: produces `.a` library files.
- Memory safety: compile-time guarantees from Rust.
- Zero-cost abstractions: performance comparable to C.

## Use Cases

- Safety-critical code: leverage Rust's memory-safety guarantees.
- Complex algorithms: use Rust's advanced abstraction capabilities.
- Device drivers: type-safe hardware abstractions.
- Network protocol stacks: safe packet handling.
- Cryptography libraries: secure implementations that help prevent memory leaks.

## Troubleshooting

### Linker Error

If you encounter the error "can't link double-float modules with soft-float modules":

- The build system should auto-detect the correct ABI.
- Check whether the compiler `-mabi` flag matches the Rust target.

### Target Not Installed

If a target is reported as not installed:

```bash
rustup target add <target-name>
```

### Detection Failed

If the target architecture cannot be detected:

- Verify that the RT-Thread configuration is correct.
- Inspect compiler flags in `rtconfig.py`.

## License

Apache-2.0

## References

- https://docs.rust-embedded.org/
- https://www.rt-thread.org/document/site/
- https://doc.rust-lang.org/nomicon/ffi.html
- https://riscv.org/technical/specifications/
