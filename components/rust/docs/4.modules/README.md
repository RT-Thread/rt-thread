# Writing a Rust Dynamic Library Usable by RT-Thread

1. Set up the project
Create a new `cargo` project as usual. There are some flags to tell `cargo` to generate a system library instead of a regular Rust target.

```toml
[lib]
name = "your_crate"
crate-type = ["cdylib"]      # generate a dynamic library
# crate-type = ["staticlib"] # generate a static library
```

Add the following to `config.toml` to specify the target platform:

```toml
[build]
target = "your_target"
```

2. Enable RT-Thread dynamic module loading
To load dynamic modules in RT-Thread, enable it in `Kconfig`:
```
RT-Thread Components → C/C++ and POSIX layer 
    → POSIX (Portable Operating System Interface) layer 
        → Enable dynamic module APIs, dlopen()/dlsym()/dlclose() etc
```

3. Enable the filesystem
To place dynamic modules into RT-Thread, enable a filesystem in `Kconfig`:
```
RT-Thread online packages → system packages 
    → lwext4: an excellent choice of ext2/3/4 filesystem for microcontrollers.
```

## Using the rust library

Add `rt_rust` dependency in `Cargo.toml`:

```toml
[dependencies]
rt_rust = { path = "PATH/TO/rust/rt-rust" }
```

Currently the macro-main library is not supported because it causes entry detection issues.

## References
- [The Embedded Rust Book](https://xxchang.github.io/book/interoperability/rust-with-c.html#extern-c)