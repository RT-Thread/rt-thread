# RT-Thread to Rust Feature Configuration System

This document explains how to use example configuration files to manage the mapping relationship between RT-Thread component configurations and Rust features.

## Overview

The configuration system allows you to extend the mapping relationship between RT-Thread component configuration items and Rust features through example configuration files, ensuring that only applications that depend on related components will enable corresponding features. Users can add new component configuration mappings as needed. This makes the system more modular and extensible.

## Core Components

### 1. Configuration Mapping Table (CONFIG_FEATURE_MAP)

The `CONFIG_FEATURE_MAP` located in `tools/feature_config_examples.py` defines the basic mapping relationship from RT-Thread component configuration items to Rust features:

```python
CONFIG_FEATURE_MAP = {
    'RUST_LOG_COMPONENT': {
        'feature': 'enable-log',
        'dependencies': ['em_component_log'],
        'description': 'Enable Rust logging component integration'
    },
}
```

### 2. Dependency Check Mechanism

The system automatically checks the application's `Cargo.toml` file to ensure that only applications that depend on related components will enable corresponding features.

## How to Add New Components

### Using Example Configuration Files

1. View the example configurations in `feature_config_examples.py`
2. Modify the example configuration file as needed, adding the component configuration mappings you require
3. The system will automatically load the mappings from the example configuration file
4. Ensure that related component dependencies are added to the application's `Cargo.toml`

## Configuration Item Format

Each configuration item contains the following fields:

- `feature`: The name of the Rust feature to enable
- `dependencies`: Optional, list of components that the application must depend on
- `description`: Optional, description of the configuration item

## Example Scenario

1. Add the `RUST_LOG_COMPONENT` configuration item in RT-Thread's Kconfig
2. Add the corresponding mapping in `feature_config_examples.py`:

```python
CONFIG_FEATURE_MAP.update({
    'RUST_LOG_COMPONENT': {
        'feature': 'enable-log',
        'dependencies': ['em_component_log'],
        'description': 'Enable Rust logging component integration'
    },
})
```

3. In the `Cargo.toml` of a Rust application that needs logging functionality:

```toml
[features]
enable-log = ["em_component_log/enable-log"]

[dependencies]
em_component_log = { path = "PATH/TO/components/log" }
```

## Troubleshooting

### Common Issues

1. **Feature not enabled**: Check if the application depends on the related components
2. **Build failure**: Ensure that the corresponding features are defined in the application's `Cargo.toml`
3. **Configuration not taking effect**: Verify that the RT-Thread configuration item is correctly enabled
4. **Example configuration not loaded**: Check if the `feature_config_examples.py` file exists and has correct syntax

### Debugging Steps

1. Check the configuration loading information in the build logs
2. Verify the syntax of the example configuration file
3. Check the feature enabling information in the build logs
4. Verify the application's `Cargo.toml` configuration
5. Confirm the RT-Thread configuration item status