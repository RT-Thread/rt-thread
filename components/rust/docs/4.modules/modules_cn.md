# 编写RT-Thread可以使用的rust动态库

1. 设置项目
像往常一样创建一个新的`cargo`项目。有一些标志可以告诉`cargo`去生成一个系统库，而不是常规的rust目标文件。

```toml
[lib]
name = "your_crate"
crate-type = ["cdylib"]      # 生成动态链接库
# crate-type = ["staticlib"] # 生成静态链接库
```

在 `config.toml` 中添加以下内容，以指定目标平台

```toml
[build]
target = "your_target
```

2. 开启 RT-Thread 加载动态模块功能
为了能够在 RT-Thread 中加载动态模块，需要在 `Kconfig` 中开启 
```
RT-Thread Components → C/C++ and POSIX layer 
    → POSIX (Portable Operating System Interface) layer 
        → Enable dynamic module APIs, dlopen()/dlsym()/dlclose() etc
```

3. 打开文件系统
为了能够将动态模块放入 RT-Thread 中，需要在 `Kconfig` 中开启文件系统。

```
RT-Thread online packages → system packages 
    → lwext4: an excellent choice of ext2/3/4 filesystem for microcontrollers.
```

## rust库的使用
 
在 `Cargo.toml` 中添加 `rt_rust` 依赖

```toml
[dependencies]
rt_rust = { path = "PATH/TO/rust/rt-rust" }
```

目前不支持macro-main库的使用，因为它会导致入口识别错误。
## 参考资料
- [The Embedded Rust Book](https://xxchang.github.io/book/interoperability/rust-with-c.html#extern-c)
