## 说明
1. 当前 pre-build 目录存放的是编译好的相关文件，编译源码请参考 [https://github.com/milkv-duo/duo-buildroot-sdk](https://github.com/milkv-duo/duo-buildroot-sdk)。
2. 需要修改 `duo-buildroot-sdk/build/boards` 目录下对应开发板下 `u-boot/cvi_board_init.c` 文件，注释掉 `int cvi_board_init(void)` 函数中的部分代码，否则会导致在 RT-Thread 中无法使用相关外设。