# Example Component - RT-Thread Rust 组件示例

## 概述

`example_component` 是一个基于 RT-Thread 的 Rust 组件示例，展示了如何在 RT-Thread 系统中实现、注册和管理 Rust 组件。该项目采用统一的组件注册架构，避免了组件重复注册问题，并支持基于 RT-Thread 配置的条件编译。

## 项目结构

```
example_component/
├── SConscript                      # SCons 构建脚本
├── component_registry/             # 统一组件注册程序
│   ├── Cargo.toml                  # 注册程序配置
│   └── src/
│       └── lib.rs                  # 注册程序实现
├── log/                            # 日志组件示例
│   ├── Cargo.toml                  # 日志组件配置
│   └── src/
│       ├── lib.rs                  # 日志组件实现
│       └── logging.rs              # 日志功能模块
└── tools/                          # 构建工具
    ├── build_component.py          # 组件构建工具
    └── feature_config_component.py # 特性配置
```

## 核心特性

### 1. 统一组件注册架构

- **避免重复注册**: 通过 `component_registry` 统一管理所有组件的注册，避免多个组件重复注册导致的冲突
- **条件编译支持**: 根据 RT-Thread 配置选择性编译和注册组件
- **模块化设计**: 每个组件独立实现，通过注册程序统一管理

### 2. 特性配置系统

- **基于 RT-Thread 配置**: 特性启用完全基于 RT-Thread 的配置项，无需额外配置
- **自动特性映射**: 构建系统自动将 RT-Thread 配置映射为 Rust 特性
- **依赖检查**: 自动检查组件依赖关系，确保构建一致性

### 3. 构建系统集成

- **SCons 集成**: 与 RT-Thread 的 SCons 构建系统完全集成
- **增量构建**: 支持清理和增量构建
- **交叉编译**: 支持 RISC-V 等目标架构的交叉编译

## 组件详解

### Component Registry (组件注册程序)

`component_registry` 是整个架构的核心，负责统一管理所有组件的注册。

#### 主要功能

1. **统一入口点**: 提供 `rust_component_registry` 作为所有组件的统一注册入口
2. **条件编译**: 只在相应特性启用时才包含和注册对应组件
3. **避免冲突**: 确保每个组件只被注册一次


### Log Component (日志组件)

`log` 组件提供了 Rust 风格的日志功能，包括多个日志级别和命令行接口。

#### 主要功能

1. **多级别日志**: 支持 INFO、WARN、ERROR、DEBUG、TRACE 等日志级别
2. **命令行接口**: 提供 `log_info`、`log_warn`、`log_error` 等命令
3. **条件编译**: 只在 `enable-log` 特性启用时编译

#### 使用示例

```rust
// 在代码中使用日志宏
info!("这是一条信息日志");
warn!("这是一条警告日志");
error!("这是一条错误日志");
```

#### 命令行使用

```bash
# 在 RT-Thread 命令行中使用
msh> log_info    # 打印信息日志
msh> log_warn    # 打印警告日志
msh> log_error   # 打印错误日志
```

## 特性配置

### 配置映射

在 `tools/feature_config_component.py` 中定义了 RT-Thread 配置到 Rust 特性的映射：

```python
CONFIG_COMPONENT_FEATURE_MAP = {
    'RUST_LOG_COMPONENT': {
        'feature': 'enable-log',
        'dependency': 'em_component_log',
        'description': 'Enable Rust log component integration'
    }
}
```

### 启用组件

要启用日志组件，需要在 RT-Thread 配置中设置：

```c
// 通过 menuconfig 设置
Enable Rust component support -> Auto-initialize Rust log component
```

## 开发指南

### 添加新组件

1. **创建组件目录**
   ```bash
   cargo new --lib example_component/new_component
   cd example_component/new_component
   ```

2. **创建 Cargo.toml**
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

3. **实现组件功能**
   ```rust
   // src/new.rs
   // 新组件的实现代码

   // src/lib.rs
   #![no_std]
   // 导出需要的库
   ```

4. **更新特性配置**
   ```python
   # 在 tools/feature_config_component.py 中添加
   CONFIG_COMPONENT_FEATURE_MAP = {
       # ... 现有配置 ...
       'RUST_NEW_COMPONENT': {
           'feature': 'enable-new',
           'dependency': 'em_component_new',
           'description': 'Enable new component integration'
       }
   }
   ```

5. **更新注册程序**
   ```toml
   # 在 component_registry/Cargo.toml 中添加
   [dependencies]
   em_component_new = { path = "../new_component", optional = true }

   [features]
   enable-new = ["em_component_new", "em_component_new/enable-new"]
   ```

   ```rust
   // 在 component_registry/src/lib.rs 中注册
   #[cfg(feature = "enable-new")]
   use em_component_new;

   fn component_registry_main() {
       #[cfg(feature = "enable-new")]
       {
           println!("Component registry: New component enabled");
       }
       // ... 其他组件 ...
   }
   ```

### 组件开发最佳实践

1. **使用条件编译**: 所有功能都应该用 `#[cfg(feature = "...")]` 包装
2. **避免直接注册**: 不要在组件中直接使用组件注册宏，让 `component_registry` 统一管理
3. **提供命令接口**: 为组件功能提供命令行接口，方便测试和使用
4. **文档完整**: 为每个组件提供详细的文档和使用示例

## 故障排除

### 常见问题

1. **编译失败**
   - 检查 Rust 工具链是否正确安装
   - 确认目标架构 (如 `riscv64imac-unknown-none-elf`) 已安装
   - 检查依赖路径是否正确

2. **特性未启用**
   - 确认 RT-Thread 配置中已设置相应的宏定义
   - 检查 `feature_config_component.py` 中的映射配置
   - 查看构建日志中的特性启用信息

3. **链接错误**
   - 确认所有依赖组件都已正确构建
   - 检查 `Cargo.toml` 中的依赖配置
   - 验证库文件路径和名称

## 依赖关系

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
