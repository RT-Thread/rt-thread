# ktime

## 1、介绍

ktime 为 kernel time，为内核时间子系统，实现了内核启动时间以及芯片内核 cputimer 时间管理以及一个 ns 精度的高精度定时器，

## 2、如何打开 ktime

使用 ktime 需要在 RT-Thread 的 menuconfig 中选择它，具体路径如下：

```
RT-Thread Components
    [*] Ktime: kernel time
```

## 3、使用 ktime

> 函数的功能以及参数类型已经写在头文件的注释之中，本文不再赘述

### 3.1、boottime

boottime 为系统启动时间，即为系统从上电开始到现在运行的时间，默认的时间基准为芯片内核的 cputimer 的 cnt 值，已经适配了 aarch64 与 riscv64 平台，例如 stm32 等平台需要在自己的 bsp 里面进行适配（boottime 里面函数都为 weak function），需要注意 tick 从中断到设置中间的时延

**此值应当为 Readonly**

### 3.2、cputimer

cputimer 为芯片内核的 cputimer，也可以认为是 os tick 来源的那个定时器，cputimer 主要是提供了一个统一的接口去获得其分辨率，频率，cnt 值

**此值应当为 Readonly**

### 3.3、hrtimer

> TODO: hrtimer 目前还是使用优先级链表的方式进行管理，在遇到任务的大规模并发时还是存在部分性能问题，待内核有一个统一的红黑树组件后，再进行优化

hrtimer 为高精度定时器，需要重写其 weak 函数（需要对接到硬件定时器，否则默认走的是软件定时器，分辨率只有 os tick 的值）才能正常使用，其主要使用方法：

#### 3.3.1、延时

hrtimer 的延时并不是 while(1)式死等，它会将一个线程挂起，睡眠多少时间后通过硬件定时器将其唤醒（注：延时 ns 并不是真的能准确的延时这么多，而是在保证性能的情况下尽可能的延时）

- rt_ktime_hrtimer_sleep：单位为 cputimer 的 tick 值
- rt_ktime_hrtimer_ndelay：单位为 ns
- rt_ktime_hrtimer_udelay：单位为 us
- rt_ktime_hrtimer_mdelay：单位为 ms

#### 3.3.1、定时器

hrtimer 还提供了一套 rt_timer 风格的 api

- rt_ktime_hrtimer_init
- rt_ktime_hrtimer_delete
- rt_ktime_hrtimer_start
- rt_ktime_hrtimer_stop
- rt_ktime_hrtimer_control
- rt_ktime_hrtimer_detach

需要注意，此定时器回调函数依旧处于中断之中，不能做一些耗时的任务

## 5、联系方式

- 维护：xqyjlj
- 主页：https://github.com/xqyjlj
