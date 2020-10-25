# STM32F103 仿真工程

本工程为STM32F103芯片的仿真工程，让用户无需使用硬件开发板即可使用/调试/仿真最新的RT-Thread代码。



## 使用方法

点击窗口上方工具栏中的按钮![img](https://www.rt-thread.org/document/site/tutorial/quick-start/stm32f103-simulator/figures/compile.jpg)，对该工程进行编译，如图所示：

![编译工程](https://www.rt-thread.org/document/site/tutorial/quick-start/stm32f103-simulator/figures/project1.png)

编译的结果显示在窗口下方的 `Build` 栏中，没什么意外的话，最后一行会显示“0 Error(s), * Warning(s).”，即无任何错误和警告。

> 注：由于工程中包含的内核例程代码较多，若使用的是 MDK 试用版本，则会有 16KB 限制，此时可以只保留某个目标例程的代码（例如内核例程只保留一个 thread_sample.c 参与编译），将其他不用的例程先从工程中移除，然后编译。

在编译完 RT-Thread/STM32 后，我们可以通过 MDK-ARM 的模拟器来仿真运行 RT-Thread。点击窗口右上方的按钮![img](https://www.rt-thread.org/document/site/tutorial/quick-start/stm32f103-simulator/figures/debug.jpg)或直接按 `Ctrl+F5` 进入仿真界面，再按 `F5` 开始运行，然后点击该图工具栏中的按钮或者选择菜单栏中的 `View→Serial Windows→UART#1`，打开串口 1 窗口，可以看到串口的输出只显示了 RT-Thread 的 LOGO，这是因为用户代码是空的，其模拟运行的结果如图所示：

![模拟运行 RT-Thread](https://www.rt-thread.org/document/site/tutorial/quick-start/stm32f103-simulator/figures/10.png)



> 提示
>
> 我们可以通过输入`Tab键`或者 `help + 回车` 输出当前系统所支持的所有命令，如下图所示。

![模拟运行 RT-Thread](https://www.rt-thread.org/document/site/tutorial/quick-start/stm32f103-simulator/figures/6.png)



## 感谢 & 维护

- 感谢[obito0](https://github.com/obito0)提供的[原始工程](../stm32f103-mini-system)
- [Meco Man](https://github.com/mysterywolf): jiantingman@foxmail.com