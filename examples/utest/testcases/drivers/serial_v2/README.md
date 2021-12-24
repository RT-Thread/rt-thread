## 1、介绍

该目录下 c 文件是新版本串口的测试用例，在 `examples/utest/testcases/drivers/serial_v2` 目录结构里，该测试用例用来测试串口的各个操作模式是否正常工作。

## 2、 文件说明

| 文件             | 描述                                      |
| ---------------- | ----------------------------------------- |
| uart_rxb_txb.c   | 串口接收阻塞和发送阻塞模式 的测试用例     |
| uart_rxb_txnb.c  | 串口接收阻塞和发送非阻塞模式 的测试用例   |
| uart_rxnb_txb.c  | 串口接收非阻塞和发送阻塞模式 的测试用例   |
| uart_rxnb_txnb.c | 串口接收非阻塞和发送非阻塞模式 的测试用例 |

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

### 4.2 测试思路

这四个测试用例的测试思路基本一致。

硬件上：**短接串口的发送TX引脚和接收RX引脚，完成自发自收的回路**。

软件上：创建两个线程A和B，A为接收线程，B为发送线程，设置A线程优先级比B线程优先级高。发送线程发送随机长度（长度范围是 0 到 1000）的数据，接收线程接收到数据进行校验，数据正确则测试通过，默认测试100次。

## 5、配置

使用该测试用例需要在 `env` 工具的 `menuconfig` 中做相关配置，配置如下所示（使用 RT-Thread-Studio 的配置路径一致 ）：

```
RT-Thread Utestcases  --->
    [*] RT-Thread Utestcases  --->
           Utest Serial Testcase --->
                [*] Serial testcase
```

## 6、使用

\- 编译下载。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

\- 在 MSH 中输入 `utest_run testcases.drivers.uart_rxb_txb` 运行串口接收阻塞和发送阻塞测试用例。

如果仅仅配置了 `Serial testcase` 相关的测试用例，则直接输入 `utest_run` 运行即可将上述测试用例按序测试。

## 7、注意事项

\- 需配置正确的测试用例。

\- 如有需要，可开启 ULOG 查看测试用例日志信息。

\- 需在 MSH 中输入正确的命令行。

\- 测试用例默认的测试数据长度范围最大为1000字节，如果接收端的缓冲区大小配置为小于1000字节时，那么在测试接收阻塞模式时，将会由于获取不了1000字节长度导致线程持续阻塞（因为测试用例是按 `recv_len` 长度去接收的，而不是按照单字节去接收的），因此建议接收端的缓冲区大小 （对应宏例如为 `BSP_UART2_RX_BUFSIZE`）设置为1024即可；当然也可按需减小测试的最大数据长度。

\- 该测试用例需要结合硬件具体的工作模式（POLL 、INT、DMA）进行测试，而硬件工作模式只能选择一种，因此需要在 `rtconfig.h` 中对串口相应的宏进行配置，来选择不同的工作模式去进行测试。

