# rt_macros 使用说明

rt_macros 是为 RT-Thread 提供的 Rust 过程宏集合，帮助在 `no_std` 环境下将 Rust 函数以约定的方式导出为系统入口、初始化段或 Shell 命令，从而与 RT-Thread 的启动与命令机制顺畅对接。

## 背景与目标

在 `no_std` 模式下不能直接使用传统的 `main` 函数。rt_macros 通过过程宏生成符合 C ABI 的包装入口，以及必要的链接段条目，让 RT-Thread 能在启动期或命令扫描阶段发现并调用对应的 Rust 逻辑。

## 提供的宏（参考RT-Thread的声明）

- `rt_thread_main!`：标记 Rust 主线程入口。
  - 函数签名：`fn()`（无参数、无返回值）。
  - 约束：不支持 `const`、`unsafe`、`async`、变参；不可使用显式 ABI；不可含泛型；函数可见性需为默认（非 `pub`）。
  - 作用：导出可由 RT-Thread 识别和调用的主线程入口。

- `rt_component_export!`：导出为组件初始化入口。
  - 函数签名：`fn()`。
  - 约束同上；可选参数：`name = "..."`（用于生成内部符号名称）。
  - 链接段：将函数指针落入 `.rti_fn.4` 段，供组件初始化阶段调用。

- `rt_app_export!`：导出为应用初始化入口。
  - 函数签名：`fn()`。
  - 约束同上；可选参数：`name = "..."`。
  - 链接段：将函数指针落入 `.rti_fn.6` 段，供应用初始化阶段调用。

- `msh_cmd_export!`：导出为 RT-Thread Shell 命令。
  - 函数签名：`fn(args: vec::IntoIter<rt_rust::param::ParamItem>)`。
  - 属性参数：`name`（必填，命令名），`desc`（可选，命令描述）。
  - 链接段与数据：
    - 生成命令描述结构体并落入 `FSymTab` 段。
    - 命令名与描述以以 `\0` 结尾的字节数组形式落入 `.rodata.name` 段。
  - 调用封装：生成 `extern "C"` 包装函数 `(argc, argv)`，把 `argv` 转换为 `Vec<ParamItem>`，再调用原始 Rust 命令函数。

## 链接段与启动流程

- 组件初始化入口：`.rti_fn.4`
- 应用初始化入口：`.rti_fn.6`
- Shell 命令表：`FSymTab`
- Shell 名称/描述字符串：`.rodata.name`

RT-Thread 在启动或命令表扫描时，会遍历对应段的条目并完成调用或注册，从而将 Rust 编写的逻辑纳入系统。

## 使用示例

### 主线程入口
```rust
use rt_macros::rt_thread_main;

#[rt_thread_main]
fn main() {
    // 在此编写主线程逻辑
}
```

### 组件导出
```rust
use rt_macros::rt_component_export;

#[rt_component_export(name = "rust_component_registry")]
fn my_component_init() {
    // 组件初始化逻辑
}
```

### 应用导出
```rust
use rt_macros::rt_app_export;

#[rt_app_export(name = "rust_app_example")]
fn my_app_init() {
    // 应用初始化逻辑
}
```

### Shell 命令导出
```rust
use rt_macros::msh_cmd_export;

#[msh_cmd_export(name = "hello", desc = "Say hello")]
fn hello_cmd(args: vec::IntoIter<rt_rust::param::ParamItem>) {
    // 命令处理逻辑，例如解析 args 并打印输出
}
```

## 与 C 代码的交互

当需要从 C 调用导出的 Rust 入口时，应在 C 侧声明原型并使用 `extern "C"` 指定调用约定，例如：

```c
extern "C" void rust_function_name(void);
```

命令导出宏会生成 `(argc, argv)` 形式的包装函数，RT-Thread 的命令系统会调用该包装函数并将参数传递给原始 Rust 函数。

## 常见问题与诊断

- 编译期报错：宏会在函数签名不符合约束时给出明确的错误信息（例如必须为 `fn()` 或必须为特定的参数形式）。请按上文的签名要求调整。
- 可见性要求：入口函数应保持默认（非 `pub`），以满足宏的约束。
- `alloc` 依赖：Shell 命令宏内部使用 `alloc::vec::Vec`，需确保运行环境提供分配器（RT-Thread 通常可满足）。

## 参考实现

- [RUST support for rt-thread](https://github.com/rust-for-rtthread/rtt_rust)
