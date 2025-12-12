# Example Component - RT-Thread Rust Component Example

## Overview

`example_component` is a Rust component example based on RT-Thread, demonstrating how to implement, register, and manage Rust components in RT-Thread systems. This project adopts a unified component registration architecture that avoids component duplicate registration issues and supports conditional compilation based on RT-Thread configuration.

## Project Structure

```
example_component/
├── SConscript                      # SCons build script
├── component_registry/             # Unified component registry
│   ├── Cargo.toml                  # Registry configuration
│   └── src/
│       └── lib.rs                  # Registry implementation
├── log/                            # Log component example
│   ├── Cargo.toml                  # Log component configuration
│   └── src/
│       ├── lib.rs                  # Log component implementation
│       └── logging.rs              # Logging functionality module
└── tools/                          # Build tools
    ├── build_component.py          # Component build tool
    └── feature_config_component.py # Feature configuration
```

## Core Features

### 1. Unified Component Registration Architecture

- **Avoid Duplicate Registration**: Unified management of all component registrations through `component_registry`, avoiding conflicts caused by multiple component duplicate registrations
- **Conditional Compilation Support**: Selectively compile and register components based on RT-Thread configuration
- **Modular Design**: Each component is implemented independently and managed uniformly through the registry

### 2. Feature Configuration System

- **Based on RT-Thread Configuration**: Feature enablement is entirely based on RT-Thread configuration items, requiring no additional configuration
- **Automatic Feature Mapping**: Build system automatically maps RT-Thread configuration to Rust features
- **Dependency Checking**: Automatically checks component dependencies to ensure build consistency

### 3. Build System Integration

- **SCons Integration**: Fully integrated with RT-Thread's SCons build system
- **Incremental Build**: Supports clean and incremental builds
- **Cross Compilation**: Supports cross-compilation for target architectures like RISC-V

## Component Details

### Component Registry

`component_registry` is the core of the entire architecture, responsible for unified management of all component registrations.

#### Main Functions

1. **Unified Entry Point**: Provides `rust_component_registry` as the unified registration entry for all components
2. **Conditional Compilation**: Only includes and registers corresponding components when respective features are enabled
3. **Avoid Conflicts**: Ensures each component is registered only once

### Log Component

The `log` component provides Rust-style logging functionality, including multiple log levels and command-line interface.

#### Main Functions

1. **Multi-level Logging**: Supports INFO, WARN, ERROR, DEBUG, TRACE and other log levels
2. **Command-line Interface**: Provides commands like `log_info`, `log_warn`, `log_error`
3. **Conditional Compilation**: Only compiles when `enable-log` feature is enabled

#### Usage Examples

```rust
// Using log macros in code
info!("This is an info log");
warn!("This is a warning log");
error!("This is an error log");
```

#### Command-line Usage

```bash
# Using in RT-Thread command line
msh> log_info    # Print info log
msh> log_warn    # Print warning log
msh> log_error   # Print error log
```

## Feature Configuration

### Configuration Mapping

The mapping from RT-Thread configuration to Rust features is defined in `tools/feature_config_component.py`:

```python
CONFIG_COMPONENT_FEATURE_MAP = {
    'RUST_LOG_COMPONENT': {
        'feature': 'enable-log',
        'dependency': 'em_component_log',
        'description': 'Enable Rust log component integration'
    }
}
```

### Enabling Components

To enable the log component, set in RT-Thread configuration:

```c
// Set through menuconfig
Enable Rust component support -> Auto-initialize Rust log component
```

## Development Guide

### Adding New Components

1. **Create Component Directory**
   ```bash
   cargo new --lib example_component/new_component
   cd example_component/new_component
   ```

2. **Create Cargo.toml**
   ```toml
   [package]
   name = "em_component_new"
   version = "0.1.0"
   edition = "2021"

   [lib]
   name = "em_component_new"
   crate-type = ["staticlib"]

   [dependencies]
   rt-rust = { path = "../../rust" }
   macro_main = { path = "../../rust/macro-main" }

   [features]
   default = []
   enable-new = []
   ```

3. **Implement Component Functionality**
   ```rust
   // src/new.rs
   // New component implementation code

   // src/lib.rs
   #![no_std]
   // Export required libraries
   ```

4. **Update Feature Configuration**
   ```python
   # Add to tools/feature_config_component.py
   CONFIG_COMPONENT_FEATURE_MAP = {
       # ... existing configuration ...
       'RUST_NEW_COMPONENT': {
           'feature': 'enable-new',
           'dependency': 'em_component_new',
           'description': 'Enable new component integration'
       }
   }
   ```

5. **Update Registry**
   ```toml
   # Add to component_registry/Cargo.toml
   [dependencies]
   em_component_new = { path = "../new_component", optional = true }

   [features]
   enable-new = ["em_component_new", "em_component_new/enable-new"]
   ```

   ```rust
   // Register in component_registry/src/lib.rs
   #[cfg(feature = "enable-new")]
   use em_component_new;

   fn component_registry_main() {
       #[cfg(feature = "enable-new")]
       {
           println!("Component registry: New component enabled");
       }
       // ... other components ...
   }
   ```

### Component Development Best Practices

1. **Use Conditional Compilation**: All functionality should be wrapped with `#[cfg(feature = "...")]`
2. **Avoid Direct Registration**: Don't use component registration macros directly in components, let `component_registry` manage uniformly
3. **Provide Command Interface**: Provide command-line interfaces for component functionality for easy testing and usage
4. **Complete Documentation**: Provide detailed documentation and usage examples for each component

## Troubleshooting

### Common Issues

1. **Compilation Failure**
   - Check if Rust toolchain is correctly installed
   - Confirm target architecture (e.g., `riscv64imac-unknown-none-elf`) is installed
   - Check if dependency paths are correct

2. **Features Not Enabled**
   - Confirm corresponding macro definitions are set in RT-Thread configuration
   - Check mapping configuration in `feature_config_component.py`
   - Review feature enablement information in build logs

3. **Linking Errors**
   - Confirm all dependent components are correctly built
   - Check dependency configuration in `Cargo.toml`
   - Verify library file paths and names

## Dependency Relationships

```
RT-Thread Config
      ↓
Feature Mapping
      ↓
Rust Features
      ↓
Component Registry ← Individual Components
      ↓
RT-Thread System
```