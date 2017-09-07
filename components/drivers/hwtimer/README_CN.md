定时器设备
===
  
##功能
---
* 时间测量
* 周期或单次执行回调函数
  
##编译
---
1. 在rtconfig.h添加 `#define RT_USING_HWTIMER`
  
##使用流程
---
1. 以读写方式打开设备
2. 设置超时回调函数（如果需要）
3. 根据需要设置定时模式（单次/周期）
4. 设置计数频率（可选）
5. 写入超时值，定时器随即启动
6. 停止定时器（可选）
7. 关闭设备（如果需要）
  
应用参考 [hwtimer_test] (/examples/test/hwtimer\_test.c)

##驱动编写指南
---
###操作接口

``` 
struct rt_hwtimer_ops
{
    void (*init)(struct rt_hwtimer_device *timer, rt_uint32_t state);
    rt_err_t (*start)(struct rt_hwtimer_device *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode);
    void (*stop)(struct rt_hwtimer_device *timer);
    rt_uint32_t (*count_get)(struct rt_hwtimer_device *timer);
    rt_err_t (*control)(struct rt_hwtimer_device *timer, rt_uint32_t cmd, void *args);
};
```

* init - state <1 打开设备 0 关闭设备> 
* start - cnt <超时值> - mode <单次/周期>
* stop - <停止计数>
* count_get - <读取计数器值>
* control - <设置计数频率 >

###定时器特征信息
  
```
struct rt_hwtimer_info
{
    rt_int32_t maxfreq;   
    rt_int32_t minfreq;    
    rt_uint32_t maxcnt;     
    rt_uint8_t  cntmode;  
 };
```

* maxfreq <设备支持的最大计数频率>
* minfreq <设备支持的最小计数频率>
* maxcnt  <计数器最大计数值>
* cntmode <递增计数/递减计数>
  
###注册设备
```
static rt_hwtimer_t _timer0;
int stm32_hwtimer_init(void)
{
    _timer0.info = &_info;
    _timer0.ops  = &_ops;

    rt_device_hwtimer_register(&_timer0, "timer0", TIM2);

    return 0;
}
```
  
###定时器中断
```
void timer_irq_handler(void)
{
    //其它操作
    
    rt_device_hwtimer_isr(&_timer0);
}
```

##注意事项
---
  
<font color="#FF0000">可能出现定时误差</font>
  

误差原因：

假设计数器最大值0xFFFF，计数频率1Mhz，定时时间1秒又1微秒。
  
由于定时器一次最多只能计时到65535us，对于1000001us的定时要求。
可以50000us定时20次完成，此时将会出现计算误差1us。
