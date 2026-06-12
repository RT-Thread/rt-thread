# RT-Thread 测试用例集合

## 简介

为了保证某一部分代码的质量，通常可以通过编写测试用例的方式，验证此代码的功能。为了保证 RT-Thread 相关仓库的代码质量，我们基于 utest 框架搭建了一套简易的自动化测试环境。有兴趣，有精力的小伙伴可以利用这套机制完善自己的代码检查。如果有意愿让社区上更多的小伙伴受益，也可以在提交代码的时候，把对应的测试用例也提交上来。

## 相关配置

自动化测试使用的配置文件维护在 [.github/utest/configs](../../../.github/utest/configs)，每一个目录代表一种功能集合，如：kernel, net 等。

## 如何贡献

### 1. 编写测试用例

参考已有的测试用例，在对应模块目录下添加 `utest` 目录并维护自己的测试用例，例如串口测试用例位于 `components/drivers/serial/utest`。测试用例的编写方法参考文档中心[《utest 测试框架》章节](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/utest/utest)。

### 2. 本地测试

1. 在 `bsp\qemu-vexpress-a9` 目录下打开 `menuconfig`，使能对应的测试用例，如下：

```
RT-Thread Utestcases  --->
  [*] RT-Thread Utestcases
        Utest Self Testcase  --->
          [*] Pass test
```

2. 保存并退出，输入 scons 编译当前 bsp。

3. 输入 .\qemu.bat 运行当前 bsp，在 msh 环境下执行 utest_run 命令，验证代码运行是否正常。

```
msh />utest_run
[I/utest] [==========] [ utest    ] loop 1/1
[I/utest] [==========] [ utest    ] started
[I/utest] [----------] [ testcase ] (testcases.utest.pass_tc) started
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:16) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:17) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:19) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:20) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:22) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:23) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:25) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:26) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:28) is passed
[D/utest] [    OK    ] [ unit     ] (test_assert_pass:29) is passed
[I/utest] [  PASSED  ] [ result   ] testcase (testcases.utest.pass_tc)
[I/utest] [----------] [ testcase ] (testcases.utest.pass_tc) finished
[I/utest] [==========] [ utest    ] finished
```

### 3. 提交

1. 如果是对已有测试集合的完善，需要把添加的测试用例的配置项，以及对应的依赖项添加到对应测试集合的配置文件里，如：[.github/utest/configs/kernel/mem.cfg](../../../.github/utest/configs/kernel/mem.cfg)。

```
CONFIG_RT_UTEST_MEMHEAP=y

# dependencies
CONFIG_RT_USING_MEMHEAP=y
```

2. 如果要添加新的测试集合，需要参考已有的测试集合，在 [.github/utest/configs](../../../.github/utest/configs) 目录下添加新的测试集合配置项。并更新 [.github/workflows/utest_auto_run.yml](../../../.github/workflows/utest_auto_run.yml) 内的测试集合。

```
- platform: { UTEST: "A9", RTT_BSP: "bsp/qemu-vexpress-a9", QEMU_ARCH: "arm", QEMU_MACHINE: "vexpress-a9", SD_FILE: "sd.bin", KERNEL: "standard", SMP_RUN: "" }
  config_file: "kernel/mem.cfg"
```

3. 向 RT-Thread 主仓库提交合并请求。
