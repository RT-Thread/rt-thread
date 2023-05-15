# 版本发布前自动更新与部署

在ENV环境下，并在release文件夹下执行 `python buildbot.py update` 可完成自动版本发布**前** **部分** 准备工作。 欢迎补充其他发布前自动化脚本。

目前可以自动更新和部署的内容包括：
1. 更新所有BSP工程，包括.config文件、rtconfig文件更新，以及Keil\IAR等工程的刷新
2. STM32启动文件更新：
   1. 对gcc的汇编启动文件中main替换为entry函数
   2. 将启动文件heap降为0(Keil IAR)
   3. 将GCC的堆大小扩展到0x400，与Keil IAR保持一致
