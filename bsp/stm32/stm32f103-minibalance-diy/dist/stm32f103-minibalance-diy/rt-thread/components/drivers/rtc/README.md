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

### 2.4 启用 NTP 时间自动同步

如果 RT-Thread 已接入互联网，可启用 NTP 时间自动同步功能，定期同步本地时间。

在 menuconfig 中启用 `RTC_SYNC_USING_NTP` 配置。启用该功能后，会自动开启 [netutils package](https://github.com/RT-Thread-packages/netutils) 的 NTP 功能。同时务必确保 RT-Thread 网络访问正常。

启用该配置后，还有两个配置是用户可选配置：

- `RTC_NTP_FIRST_SYNC_DELAY`: 首次执行 NTP 时间同步的延时。延时的目的在于，给网络连接预留一定的时间，尽量提高第一次执行 NTP 时间同步时的成功率。默认时间为 30S；
- `RTC_NTP_SYNC_PERIOD`: NTP 自动同步周期，单位为秒，默认一小时（即 3600S）同步一次。

> 注意：如果没有使用组件自动初始化功能，则需手动调用 `int rt_rtc_ntp_sync_init(void)` ，完成该功能初始化。

### 2.5 启用 Soft RTC （软件模拟 RTC）

这个模式非常适用于对时间精度要求不高，没有硬件 RTC 的产品。

#### 2.5.1 使用方法

在 menuconfig 中启用 `RT_USING_SOFT_RTC` 配置。

> 注意：如果没有使用组件自动初始化功能，则需手动调用 `int rt_soft_rtc_init(void)` ，完成该功能初始化。

