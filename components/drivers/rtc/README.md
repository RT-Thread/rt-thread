# RT-Thread RTC 设备

## 1、介绍

RT-Thread 的 RTC （实时时钟）设备为操作系统的时间系统提供了基础服务。面对越来越多的 IoT 场景，RTC 已经成为产品的标配，甚至在诸如 SSL 的安全传输过程中，RTC 已经成为不可或缺的部分。

## 2、使用

应用层对于 RTC 设备一般不存在直接调用的 API ，如果使用到 C 标准库中的时间 API （目前主要是获取当前时间的  `time_t time(time_t *t)`），则会间接通过设备的 control 接口完成交互。

> 注意：目前系统内只允许存在一个 RTC 设备，且名称为 `"rtc"` 。

### 2.1  设置日期

```C
rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day)
```

|参数                                    |描述|
|:-----                                  |:----|
|year                                    |待设置生效的年份|
|month                                   |待设置生效的月份|
|day                                     |待设置生效的日|

### 2.2 设置时间

```C
rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second)
```

|参数                                    |描述|
|:-----                                  |:----|
|hour                                    |待设置生效的时|
|minute                                  |待设置生效的分|
|second                                  |待设置生效的秒|

### 2.3 使用 Finsh/MSH 命令 查看/设置 日期和时间

#### 2.3.1 查看日期和时间

输入 `date` 即可，大致效果如下：

```
msh />date
Fri Feb 16 01:11:56 2018
msh />
```

#### 2.3.2 设置日期和时间

同样使用 `date` 命令，在命令后面再依次输入 `年` `月` `日` `时` `分` `秒` （中间空格隔开, 24H 制），大致效果如下：

```
msh />date 2018 02 16 01 15 30    # 设置当前时间为 2018-02-16 01:15:30
msh />
```

### 2.4 启用 Soft RTC （软件模拟 RTC）

这个模式非常适用于对时间精度要求不高，没有硬件 RTC 的产品。

#### 2.4.1 使用方法

在 menuconfig 中启用 `RT_USING_SOFT_RTC` 配置。

