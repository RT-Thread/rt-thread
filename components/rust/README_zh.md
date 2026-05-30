# RT-Thread Rust 组件

RT-Thread RTOS 的通用 Rust 组件，支持多架构自动检测。

## 特性

- **多架构支持**：自动检测 ARM、AArch64 和 RISC-V 目标架构
- **零配置**：无需手动配置目标平台
- **模块化设计**：核心模块与示例代码清晰分离
- **RT-Thread 集成**：完整访问 RT-Thread 内核 API

## 项目结构

```
rust/
├── README.md                    # 项目说明文档
├── Kconfig                      # 配置选项
├── SConscript                   # 主构建脚本
├── core/                        # 核心 Rust 库
│   ├── Cargo.toml              # Rust 项目配置
│   ├── SConscript              # 核心库构建脚本
│   ├── rust_cmd.c              # MSH 命令注册
│   └── src/                    # 源代码目录
│       ├── lib.rs              # 主库入口
│       ├── init.rs             # 组件初始化
│       ├── allocator.rs        # 内存分配器
│       ├── panic.rs            # Panic 处理
│       ├── bindings/           # RT-Thread API FFI 绑定
│       ├── api/                # RT-Thread API Rust 封装
│       ├── prelude/            # 常用导入
│       ├── thread.rs           # 线程操作
│       ├── mutex.rs            # 互斥锁
│       ├── sem.rs              # 信号量
│       ├── queue.rs            # 消息队列
│       ├── time.rs             # 时间函数
│       ├── fs.rs               # 文件系统
│       ├── libloader.rs        # 动态库加载
│       ├── param.rs            # 参数传递
│       └── out.rs              # 输出函数
├── rt_macros/                   # Rust 宏定义库
│   ├── Cargo.toml              # 宏库配置
│   └── src/                    # 宏源代码
│       ├── lib.rs              # 宏库入口
│       └── macros/             # 宏实现
│           ├── mod.rs          # 模块定义
│           ├── main.rs         # 主函数宏
│           ├── component.rs    # 组件导出宏
│           ├── app.rs          # 应用导出宏
│           └── cmd.rs          # 命令导出宏
├── examples/                    # 示例代码
│   ├── Kconfig                 # 示例配置
│   ├── SConscript              # 示例构建脚本
│   ├── application/            # 应用示例
│   ├── component/              # 组件示例
│   └── modules/                # 动态模块示例
├── docs/                        # 详细文档
└── tools/                       # 构建工具
    ├── build_support.py        # 构建支持函数
    ├── build_component.py      # 组件构建工具
    ├── build_usrapp.py         # 用户应用构建工具
    ├── feature_config_component.py  # 组件特性配置
    └── feature_config_examples.py   # 示例特性配置
```

## 快速开始

### 前置要求

1. **安装 Rust**

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

2. **添加目标平台**（根据您的架构）

```bash
# RISC-V64（软浮点）
rustup target add riscv64imac-unknown-none-elf

# ARM Cortex-M4
rustup target add thumbv7em-none-eabi

# 其他目标请根据实际工具链/ABI 添加对应的 Rust target
```

### 构建

```bash
# 在 menuconfig 中启用 Rust 组件
scons --menuconfig
# 导航至：Rust Component Support → Enable

# 构建
scons

# 清理
scons -c
```

## 支持的架构

| 架构           | 目标                              | 自动检测 |
| -------------- | --------------------------------- | -------- |
| Cortex-M3      | thumbv7m-none-eabi                | ✓        |
| Cortex-M4/M7   | thumbv7em-none-eabi               | ✓        |
| Cortex-M4F/M7F | thumbv7em-none-eabihf             | ✓        |
| ARMv7-A        | armv7a-none-eabi                  | ✓        |
| AArch64        | aarch64-unknown-none              | ✓        |
| RISC-V32       | riscv32ima[f]c-unknown-none-elf   | ✓        |
| RISC-V64       | riscv64[gc/imac]-unknown-none-elf | ✓        |

构建系统会自动从 RT-Thread 配置中检测正确的目标。

## 用户测试 MSH 命令

| 命令               | 描述                               |
| ------------------ | ---------------------------------- |
| `rust_param_demo`  | 参数传递演示                       |
| `rust_thread_demo` | 线程演示                           |
| `rust_mutex_demo`  | 互斥锁演示                         |
| `rust_queue_demo`  | 队列演示                           |
| `rust_sem_demo`    | 信号量演示                         |
| `rust_dl_demo`     | 动态模块加载演示                   |
| `rust_fs_demo`     | 文件与日志操作演示(需启用日志组件) |

## 配置选项

通过 `menuconfig` 配置：

- `RT_USING_RUST` - 启用/禁用 Rust 组件
- `RT_RUST_CORE` - 启用/禁用核心支持库
- `RUST_INIT_COMPONENT` - 启动时自动初始化
- `RT_USING_RUST_EXAMPLES`
  - `RT_RUST_BUILD_APPLICATIONS`：启用/禁用用户程序
  - `RT_RUST_BUILD_COMPONENTS`：启用/禁用组件
  - `RT_RUST_BUILD_MODULES`：启用/禁用编译动态模块
- `RUST_DEBUG_BUILD` - 启用/禁用debug模式

## 技术细节

- **No-std**：嵌入式友好的 `#![no_std]` 环境
- **FFI**：无缝的 C/Rust 互操作性
- **静态链接**：生成 `.a` 库文件
- **内存安全**：Rust 的编译时保证
- **零成本**：性能与 C 相当

## 应用场景

Rust 组件特别适合以下场景：

- **安全关键代码**：利用 Rust 的内存安全保证
- **复杂算法**：利用 Rust 的高级抽象能力
- **设备驱动**：类型安全的硬件抽象
- **网络协议栈**：安全的数据包处理
- **加密库**：防止内存泄露的安全实现

## 故障排除

### 链接错误

如果遇到 "can't link double-float modules with soft-float modules" 错误：

- 构建系统应该自动检测正确的 ABI
- 检查编译器的 `-mabi` 标志是否与 Rust 目标匹配

### 目标未安装

如果提示目标未安装：

```bash
rustup target add <目标名称>
```

### 检测失败

如果无法检测目标架构：

- 检查 RT-Thread 配置是否正确
- 查看 rtconfig.py 中的编译器标志

## 许可证

Apache-2.0

## 参考资料

- [Rust 嵌入式编程手册](https://docs.rust-embedded.org/)
- [RT-Thread 文档中心](https://www.rt-thread.org/document/site/)
- [Rust FFI 编程](https://doc.rust-lang.org/nomicon/ffi.html)
- [RISC-V 规范](https://riscv.org/technical/specifications/)