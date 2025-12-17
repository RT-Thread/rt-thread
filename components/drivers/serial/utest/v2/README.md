## 1、介绍

该目录下 c 文件是新版本串口的测试用例，在 `examples/utest/testcases/drivers/serial_v2` 目录结构里，该测试用例用来测试串口的各个操作模式是否正常工作。

## 2、 文件说明

| 文件             | 描述                                      |
| ---------------- | ----------------------------------------- |
| uart_rxb_txb.c   | 串口接收阻塞和发送阻塞模式 的测试用例     |
| uart_rxb_txnb.c  | 串口接收阻塞和发送非阻塞模式 的测试用例   |
| uart_rxnb_txb.c  | 串口接收非阻塞和发送阻塞模式 的测试用例   |
| uart_rxnb_txnb.c | 串口接收非阻塞和发送非阻塞模式 的测试用例 |
| uart_blocking_tx.c| 串口阻塞发送模式 的测试                       |
| uart_blocking_rx.c| 串口阻塞接收模式 的测试                       |
| uart_nonblocking_tx.c| 串口非阻塞发送模式 的测试                   |
| uart_nonblocking_rx.c  | 串口非阻塞接收模式 的测试                   |
| uart_flush_rx | 刷新接收缓冲区的测试 |
| uart_flush_txb | 阻塞模式下刷新发送缓冲区的测试 |
| uart_flush_txnb | 非阻塞模式下刷新发送缓冲区的测试 |
| uart_timeout_rxb_txb | 串口 发送 / 接收 超时的测试 |
| uart_overflow_rxb_txb | 串口溢出处理的测试 |
| uart_get_unread_bytes_count | 获取串口接收缓冲区中的数据长度的测试 |
| uart_posix_nonblock | posix非阻塞测试 |
| uart_posix_echo_block | posix阻塞echo测试 |

## 3、软硬件环境

硬件上需要支持 RT-Thread 的完整版操作系统，版本为4.0.4及以上，且硬件有串口硬件外设，软件上需要支持 内核接口、IPC 、Device 框架。

## 4、测试项

### 4.1 测试说明

上文所提及的模式是指串口使用时的操作模式，不涉及硬件的工作模式的配置情况（硬件工作模式一般有轮询POLL、中断INT、DMA），因此使用时需要结合具体的硬件工作模式去配置使用。例如 发送阻塞和接收非阻塞模式 ，这个测试有很多种硬件配置，配置情况例如：DMA发送阻塞和DMA接收非阻塞，INT发送阻塞和DMA接收非阻塞，POLL发送阻塞和DMA接收非阻塞等等。因此通过排列组合后的测试场景有4*9=36种，有意义的组合方式为20种。如下表：


| 接收非阻塞 | 发送阻塞 | 组合              | 有意义的组合方式 |
| ---------- | -------- | ----------------- | ---------------- |
| POLL       | POLL     | RX_POLL + TX_POLL |                  |
|            | INT      | RX_POLL + TX_INT  |                  |
|            | DMA      | RX_POLL + TX_DMA  |                  |
| INT        | POLL     | RX_INT + TX_POLL  | ✔                |
|            | INT      | RX_INT + TX_INT   | ✔                |
|            | DMA      | RX_INT + TX_DMA   | ✔                |
| DMA        | POLL     | RX_DMA + TX_POLL  | ✔                |
|            | INT      | RX_DMA + TX_INT   | ✔                |
|            | DMA      | RX_DMA + TX_DMA   | ✔                |

| 接收非阻塞 | 发送非阻塞 | 组合              | 有意义的组合方式 |
| ---------- | ---------- | ----------------- | ---------------- |
| POLL       | POLL       | RX_POLL + TX_POLL |                  |
|            | INT        | RX_POLL + TX_INT  |                  |
|            | DMA        | RX_POLL + TX_DMA  |                  |
| INT        | POLL       | RX_INT + TX_POLL  |                  |
|            | INT        | RX_INT + TX_INT   | ✔                |
|            | DMA        | RX_INT + TX_DMA   | ✔                |
| DMA        | POLL       | RX_DMA + TX_POLL  |                  |
|            | INT        | RX_DMA + TX_INT   | ✔                |
|            | DMA        | RX_DMA + TX_DMA   | ✔                |

| 接收阻塞 | 发送阻塞 | 组合              | 有意义的组合方式 |
| -------- | -------- | ----------------- | ---------------- |
| POLL     | POLL     | RX_POLL + TX_POLL |                  |
|          | INT      | RX_POLL + TX_INT  |                  |
|          | DMA      | RX_POLL + TX_DMA  |                  |
| INT      | POLL     | RX_INT + TX_POLL  | ✔                |
|          | INT      | RX_INT + TX_INT   | ✔                |
|          | DMA      | RX_INT + TX_DMA   | ✔                |
| DMA      | POLL     | RX_DMA + TX_POLL  | ✔                |
|          | INT      | RX_DMA + TX_INT   | ✔                |
|          | DMA      | RX_DMA + TX_DMA   | ✔                |

| 接收阻塞 | 发送非阻塞 | 组合              | 有意义的组合方式 |
| -------- | ---------- | ----------------- | ---------------- |
| POLL     | POLL       | RX_POLL + TX_POLL |                  |
|          | INT        | RX_POLL + TX_INT  |                  |
|          | DMA        | RX_POLL + TX_DMA  |                  |
| INT      | POLL       | RX_INT + TX_POLL  |                  |
|          | INT        | RX_INT + TX_INT   | ✔                |
|          | DMA        | RX_INT + TX_DMA   | ✔                |
| DMA      | POLL       | RX_DMA + TX_POLL  |                  |
|          | INT        | RX_DMA + TX_INT   | ✔                |
|          | DMA        | RX_DMA + TX_DMA   | ✔                |

需要解释的是，为什么会存在无意义的组合模式，举个例子，非阻塞模式下，肯定是不会出现POLL（轮询）方式的，因为POLL方式已经表明是阻塞方式了。
该测试用例在测试多种组合时，需要通过更改`rtconfig.h`文件对硬件模式进行静态配置。

### 4.2 测试条件

**短接串口的发送TX引脚和接收RX引脚，完成自发自收的回路**。

大致的测试思路:

>发送测试流程 :
>>1. 先关闭串口,再以需要测试的模式打开.
>>2. 然后依次发送 UART_SEND_TIMES * （1000以内的随机数）个数据.
>>3. 打印记录的数据,通过LOG日志的时钟周期来反应发送效率, 通过成功发送的数据量来反应是否产生丢包问题.
>
>接收测试流程 : 
>>1. 先关闭串口,再以需要测试的模式打开.
>>2. 然后以此接收 同发送测试流程一致的 UART_SEND_TIMES *（1000以内随机数）个数据
>>3. 接收的同时记录成功接收的数据数量
>>4. 打印记录的数据, 通过现实成功接收的数据量与串口发送的数据量做对比,来验证是否出现丢包问题

## 5、配置

使用该测试用例需要在 `env` 工具的 `menuconfig` 中做相关配置，配置如下所示（使用 RT-Thread-Studio 的配置路径一致 ）：

```
RT-Thread Utestcases  --->
    [*] RT-Thread Utestcases  --->
           Utest Serial Testcase --->
                [*] Serial testcase --->
                	the device name for serial test: uart2	(选择测试的串口)
                	(128)the rx buffer size for serial test	(测试串口rx缓冲区大小)
                	(128)the tx buffer size for serial test	(测试串口tx缓冲区大小)
                	(100)the number of iterations for the test routine.	(测试例程的迭代次数)
                [*] Serial posix testcase --->
                	the device name for serial posix test: dev/uart2	(posix测试的串口)
                	(100)the number of iterations for the posix test routine.	(posix测试例程的迭代次数)
```

## 6、使用

\- 编译下载。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_blocking_tx` 运行串口阻塞发送测试

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_blocking_rx` 运行串口阻塞接收测试

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_nonblocking_tx` 运行串口非阻塞发送测试

其余同理，可在函数内部查看命令。

如果仅仅配置了 `Serial testcase` 相关的测试用例，则直接输入 `utest_run *` 运行即可将上述测试用例按序测试。

## 7、注意事项

\- 需配置正确的测试用例。

\- 如有需要，可开启 ULOG 查看测试用例日志信息。

\- 需在 MSH 中输入正确的命令行。

\- 该测试用例需要结合硬件具体的工作模式（POLL 、INT、DMA）进行测试，而硬件工作模式只能选择一种，因此需要在 `rtconfig.h` 中对串口相应的宏进行配置，来选择不同的工作模式去进行测试。

