## serialX User Manual

serialX 驱动框架在尽量延续 v1 版使用方法的前提下，增加阻塞和非阻塞操作，同时对 DMA 收发缓冲机制进行了调整。

RT-Thread 论坛上有几篇介绍和讲解 serialX 的文章，使用 serialX 前请先了解它。

如果用分层理论解释 serialX ，那么它可以划分成应用层、中间驱动框架层、底层硬件层。这三层各有分工，又相互影响。

硬件是千变万化的，驱动的一个职责就是把千变万化的硬件进行包装，把共性的行为固化出来，交给应用层使用。


### 串口驱动框架和硬件底层接口功能定义详解

```
struct rt_uart_ops
{
    // 配置外设寄存器设置默认波特率等；外设时钟配置、引脚功能复用（如果还没配置过）；启用外设等等
    int (*init)(struct rt_serial_device *serial);
    // 仅仅用于配置外设波特率、数据位数、停止位等等
    rt_err_t (*configure)(struct rt_serial_device *serial, struct serial_configure *cfg);
    // 用于使能禁用中断，初始配置 DMA
    rt_err_t (*control)(struct rt_serial_device *serial, int cmd, void *arg);
    // 串口外设“写数据寄存器”*为空*，把数据放入“写数据寄存器”。*不为空*，死等
    int (*putc)(struct rt_serial_device *serial, char c);
    // 串口外设“读数据寄存器”*不为空*，读出“读数据寄存器”的值。*为空*，返回 -1
    int (*getc)(struct rt_serial_device *serial);

    // 启动发送，多数是使能串口外设“发送寄存器”*空*中断
    void (*start_tx)(struct rt_serial_device *serial);
    // 结束发送，多数是禁止串口外设“发送寄存器”*空*中断
    void (*stop_tx)(struct rt_serial_device *serial);

#ifdef RT_SERIAL_USING_DMA
    // 判断 DMA 是否在发送过程中，必须有效检测 DMA 是否在发送数据中，有些芯片有寄存器位标志，可以用标志位判断，如果没有，使用变量标志。
    rt_bool_t (*is_dma_txing)(struct rt_serial_device *serial);
    // 启动 DMA 发送，数据缓存首地址和数据长度由驱动框架提供。（最后置位 DMA tx 标志）
    void (*start_dma_tx)(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size);
    // 停止 DMA 发送，停用 DMA 发送，（最后复位 DMA tx 标志）
    void (*stop_dma_tx)(struct rt_serial_device *serial);
#endif
    // 使能串口外设中断，添加这个的初衷是减少全局中断开关操作。目前这部分代码已被注释并使用 rt_hw_interrupt_enable
    void (*enable_interrupt)(struct rt_serial_device *serial);
    // 禁用串口外设中断，添加这个的初衷是减少全局中断开关操作。目前这部分代码已被注释并使用 rt_hw_interrupt_disable
    void (*disable_interrupt)(struct rt_serial_device *serial);
};
```

其中，`control` 是一个多功能扩展接口，目前支持的 `cmd` 包括：
- `RT_DEVICE_CTRL_OPEN`： 先清理一些可能出现的中断，最后配置并使能外设中断
- `RT_DEVICE_CTRL_CLOSE`： 禁止外设中断，清理中断，卸载外设
- `RT_DEVICE_CTRL_CLR_INT`： 定向禁止中断，包括接收中断，接收通道 DMA 中断，发送通道 DMA 中断
- `RT_DEVICE_CTRL_SET_INT`： 定向使能中断，包括接收中断，接收通道 DMA 中断，发送通道 DMA 中断
- `RT_DEVICE_CTRL_CONFIG`： 这部分主要是初始化配置接收通道 DMA 和发送通道 DMA。

`enable_interrupt` `disable_interrupt` 两个接口是一组很细腻的操作，但是有些外设如果用中断方式，有些用 DMA 方式。这时候需要区别当前外设是否使用了 DMA ，是否需要操作 DMA 中断。（某外设 “是否支持 DMA 收发” 和外设 “使用了 DMA 收发” 是两个概念）

PS: `control` 好像是无所不能的，有了它，为什么还要添加 `init` `start_tx` `stop_tx` `enable_interrupt` `disable_interrupt`？

#### `rt_hw_serial_isr` 中断回调函数怎么调用？

在 serialX 里只关心五种中断，
1. “接收寄存器不空” `rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);`
2. “发送寄存器空” `rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);`
3. “接收通道空闲” `rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));`
4. “接收通道 DMA 半/全中断” `rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));`
5. “发送通道 DMA 发送完成中断” `rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);`

其中，dma_cnt 是 DMA 接收缓存中已接收数据字节数。

前两个用于中断收发，后三个用于 DMA 收发。

> 注：其它异常错误中断，或者清理掉，或者转入其它流程，这些不在 serialX 驱动考虑范围内。

### 重新定义 `rt_serial_device` 定义：

```
struct rt_serial_device
{
    struct rt_device          parent;

    const struct rt_uart_ops *ops;
    struct serial_configure   config;
    rt_uint32_t bufsz;          // 驱动层收发缓存容量大小

    void *serial_rx;            // 串口接收缓存
    void *serial_tx;            // 串口发送缓存

#ifdef RT_SERIAL_USING_DMA                          // 串口收发缓存和 DMA 使用的二级缓存分开
    rt_size_t dma_idx_rx;
    rt_uint8_t serial_dma_rx[RT_SERIAL_DMA_BUFSZ];  // DMA 接收缓存
    rt_uint8_t serial_dma_tx[RT_SERIAL_DMA_BUFSZ];  // DMA 发送缓存
#endif

    cb_serial_tx _cb_tx;        // 写过程回调函数指针
    cb_serial_rx _cb_rx;        // 读过程回调函数指针

    struct rt_completion completion_tx;             // 发送完成
    struct rt_completion completion_rx;             // 接收到新数据
};
typedef struct rt_serial_device rt_serial_t;
```

在最近的一次修改中，把 `struct serial_configure` 中的 `bufsz` 成员挪到了 `struct rt_serial_device` 。就是为了 open 了设备之后还能修改波特率，而且，修改缓存大小的功能可以挪到 `control` 里，达到 open 设备之后还能修改缓存大小的目地。

### 之前写过的文章汇总

#### 理论类

- [rt-thread 驱动篇 之 串口驱动框架剖析及性能提升](https://club.rt-thread.org/ask/article/0ee3da5b6a9c347d.html) 这里是 serialX 的理论基础，之后的所有工作都是这些想法的实现。
- [rt-thread 驱动篇 之 serialX 全网公测](https://club.rt-thread.org/ask/article/bfd92159ba11aef6.html) 这是第一次在 stm32 上实现并进行的测试，内含测试代码。 `struct rt_uart_ops` 结构体接口定义有很详细的注释，在新的芯片上写底层驱动时，这些注释说明很重要，一定严格按照这些接口定义的功能进行实现。

#### 实践类

- [rt-thread 驱动篇（五）serialX 小试牛刀](http://www.elecfans.com/d/1849301.html) 这是在控制台串口上使用 serialX 的实践。
以及，[rt-thread 驱动篇（六）serialX弊端及解决方法](https://www.elecfans.com/d/1850548.html) 会告诉你在控制台上使用**中断/DMA**收发模式时，可能遇到的尴尬问题以及怎么去避免它们。
- [测试 serialX 的 posix 支持](https://club.rt-thread.org/ask/article/e7b067264f6badfe.html) 这里是 posix 接口测试。内含测试代码
- [基于 serialX 串口驱动移植 libmodbus](https://club.rt-thread.org/ask/article/91437d9031d4ac5a.html) 这篇是使用 serialX 驱动跑的 libmodbus 。开启了 posix 之后，serialX 驱动和 libmodbus 配合的还是蛮好的。

### 仓库

最后，serialX 的[源码仓库](https://gitee.com/thewon/serialX) ，里面有一份儿移植说明文档，以及两个测试程序。我们可以从测试程序里看到所有的用法。

目前已经实现了几种芯片底层驱动，想移植到其它芯片上，可以参考。

