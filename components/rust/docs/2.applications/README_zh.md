# RT-Thread Rust 示例用户应用程序

这个目录包含了一系列用于演示 RT-Thread 中 Rust 编程功能的示例用户应用程序和组件。这些示例展示了如何在 RT-Thread 实时操作系统中使用 Rust 语言进行系统编程。

## 目录结构

```
example_usrapp/
├── SConscript              # SCons 构建脚本
├── fs/                     # 文件系统操作示例
├── loadlib/                # 动态库加载示例
├── mutex/                  # 互斥锁同步示例
├── param/                  # 参数处理示例
├── queue/                  # 消息队列示例
├── semaphore/              # 信号量同步示例
└── thread/                 # 线程管理示例
```

## 构建和运行

### 前提条件

1. 确保 RT-Thread 配置中启用了 Rust 支持 (`RT_USING_RUST`)，并且开启 examples 编译(`RT_USING_RUST_EXAMPLES`)中的应用(`RT_RUST_BUILD_APPLICATIONS`)
2. 安装 Rust 工具链和相关依赖
3. 配置正确的交叉编译环境

### 构建步骤

1. 在 RT-Thread 项目根目录执行：
   ```bash
   scons -j$(nproc)
   ```

2. 构建系统会自动：
   - 检测启用的 RT-Thread 配置
   - 根据配置启用相应的 Rust 特性
   - 编译所有示例应用为静态库
   - 链接到最终的固件镜像

### 运行示例

在 RT-Thread 系统启动后，可以通过命令行运行各个示例：

```bash
# 查看所有可用示例
help

# 运行线程示例
rust_thread_demo

# 运行文件系统示例
rust_file_demo

# 其他示例类似...
```

## 技术特性

### 依赖管理

所有示例应用都依赖以下核心组件：
- `rt-rust`: RT-Thread Rust 绑定库
- `rt-macro`: 主函数宏支持

`fs`示例还依赖日志组件：
- `em_component_log`: 日志组件

### 特性配置

- 支持条件编译特性
- 自动特性检测和启用
- 模块化的功能配置

### 构建系统集成

- 与 SCons 构建系统完全集成
- 支持清理和增量构建
- 自动依赖管理

## 开发指南

### 添加新示例

1. 在 `example_usrapp/` 下创建新目录
2. 添加 `Cargo.toml` 配置文件
3. 在 `src/lib.rs` 中实现示例代码
4. 使用 `#[macro_main_use]` 宏定义入口点

### 示例模板

```rust
#![no_std]

use macro_main::macro_main_use;
use rt_rust::param::Param;
use rt_rust::println;

#[macro_main_use(
    name = "your_demo_name",
    component = "是否为组件示例",
    app = "是否为用户应用示例",
    cmd = true,
    desc = "Your demo description."
)]
fn main(_param: Param) {
    println!("Hello from your demo!");
    // 你的示例代码...
}
```

## 故障排除

### 常见问题

1. **编译失败**: 检查 Rust 工具链是否正确安装
2. **链接错误**: 确认交叉编译目标配置正确
3. **运行时错误**: 检查栈大小和内存配置

### 调试建议

1. 使用 `println!` 进行基本调试输出
2. 启用日志特性获取详细信息
3. 检查 RT-Thread 配置项是否正确启用
