# RT-Thread to Rust Feature Configuration System

这个文档说明如何使用示例配置文件来管理 RT-Thread 组件配置与 Rust features 之间的映射关系。

## 概述

配置系统允许你通过示例配置文件来扩展 RT-Thread 组件配置项与 Rust features 的映射关系，并确保只有依赖了相关组件的应用才会启用对应的 features，用户可以根据需要添加新的组件配置映射。这使得系统更加模块化和可扩展。

## 核心组件


### 1. 配置映射表 (CONFIG_FEATURE_MAP)

位于 `tools/feature_config_examples.py` 中的 `CONFIG_FEATURE_MAP` 定义了 RT-Thread 组件配置项到 Rust features 的基础映射关系：

```python
CONFIG_FEATURE_MAP = {
    'RUST_LOG_COMPONENT': {
        'feature': 'enable-log',
        'dependencies': ['em_component_log'],
        'description': 'Enable Rust logging component integration'
    },
}
```

### 2. 依赖检查机制

系统会自动检查应用程序的 `Cargo.toml` 文件，确保只有依赖了相关组件的应用才会启用对应的 features。

## 如何添加新的组件

### 使用示例配置文件

1. 查看 `feature_config_examples.py` 中的示例配置
2. 根据需要修改示例配置文件，添加你需要的组件配置映射
3. 系统会自动加载示例配置文件中的映射
4. 确保在应用程序的 `Cargo.toml` 中添加了相关组件的依赖

## 配置项格式

每个配置项包含以下字段：

- `feature`: 要启用的 Rust feature 名称
- `dependencies`: 可选，应用程序必须依赖的组件列表
- `description`: 可选，配置项的描述

## 示例场景

1. 在 RT-Thread 的 Kconfig 中添加 `RUST_LOG_COMPONENT` 配置项
2. 在 `feature_config_examples.py` 中添加对应的映射：

```python
CONFIG_FEATURE_MAP.update({
    'RUST_LOG_COMPONENT': {
        'feature': 'enable-log',
        'dependencies': ['em_component_log'],
        'description': 'Enable Rust logging component integration'
    },
})
```

3. 在需要日志功能的 Rust 应用的 `Cargo.toml` 中：

```toml
[features]
enable-log = ["em_component_log/enable-log"]

[dependencies]
em_component_log = { path = "PATH/TO/components/log" }
```

## 故障排除

### 常见问题

1. **Feature 未启用**: 检查应用是否依赖了相关组件
2. **构建失败**: 确保应用的 `Cargo.toml` 中定义了相应的 features
3. **配置不生效**: 验证 RT-Thread 配置项是否正确启用
4. **示例配置未加载**: 检查 `feature_config_examples.py` 文件是否存在且语法正确

### 调试步骤

1. 检查构建日志中的配置加载信息
2. 验证示例配置文件的语法
3. 检查构建日志中的 feature 启用信息
4. 验证应用的 `Cargo.toml` 配置
5. 确认 RT-Thread 配置项状态