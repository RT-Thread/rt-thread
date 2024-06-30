# 版本发布前自动更新与部署

在ENV环境下，并在release文件夹下执行 `python buildbot.py update` 可完成自动版本发布**前** **部分** 准备工作。 欢迎补充其他发布前自动化脚本。

目前可以自动更新和部署的内容包括：

1. 更新所有BSP工程，包括.config文件、rtconfig文件更新，以及Keil\IAR等工程的刷新
2. STM32启动文件更新：
   1. 对gcc的汇编启动文件中main替换为entry函数
   2. 将启动文件heap降为0(Keil IAR)
   3. 将GCC的堆大小扩展到0x400，与Keil IAR保持一致

## clang-format代码自动格式化

run-clang-format.py 根据`.clang-format`和`.clang-format-ignore`文件，使用clang-format工具对代码进行格式化。

如果**不希望**对某个文件夹进行格式化，那么在该文件夹下增加一个`.clang-format`，内容为：

```yaml
---
Language: Cpp
DisableFormat: true
---
```

如果**不希望**对某个代码片段进行格式化，那么在代码中插入`// clang-format off/on`：

```c
int formatted_code;
// clang-format off
    void    unformatted_code  ;
// clang-format on
void formatted_code_again;
```

使用以下命令，将对除了bsp、elmfat、lwip等文件夹之外的所有代码进行格式化：

```shell
# 安装clang-format
pip install clang-format
# 切换到RTT目录
cd $RTT_ROOT
# 执行格式化
# -r递归子目录，-i是将格式化结果写入文件，-e是排除目录，-j是并行线程，.是当前目录
python tools/release/run-clang-format.py -r -i -e bsp/**/* -j 10 .
```

如果格式化过程中提示以下错误，一般是文件中存在UTF-8编码无法识别的字符。

```shell
error: Command 'clang-format -i libcpu\aarch64\common\asm-fpu.h' returned non-zero exit status 1
```
