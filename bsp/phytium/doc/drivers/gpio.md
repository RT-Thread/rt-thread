# GPIO

- E2000，PhytiumPI，系列芯片集成 6 个 GPIO 控制器提供 96 个 GPIO 信号。96 位 GPIO 信号，支持外部中断功能，每路中断信号没有优先级区分，并产生一个统一的中断报送到全芯片的中断管理模块。在中断管理模块内可针对 GPIO0~5 两路中断设置不同的优先级。支持中断单独屏
蔽和清除。GPIO0~2 的每位中断单独上报，GPIO3~5 的中断由模块内合成一个中断上报

- 在RT-Thread使用以下等函数接口时

```
void rt_pin_mode(rt_base_t pin, rt_uint8_t mode);
void rt_pin_write(rt_base_t pin, rt_ssize_t value);
rt_ssize_t rt_pin_read(rt_base_t pin);
rt_base_t rt_pin_get(const char *name);
rt_err_t rt_pin_attach_irq(rt_base_t pin, rt_uint8_t mode,
                           void (*hdr)(void *args), void  *args);
rt_err_t rt_pin_detach_irq(rt_base_t pin);
rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint8_t enabled);
```

- 需要传入`rt_base_t pin`参数，可使用以下方法进行赋值

```
rt_base_t pin = FGPIO_ID(FGPIO_CTRL_4, FGPIO_PIN_11)
```
- 表示使用GPIO控制器4的11号引脚，（注：使用FGPIO_ID宏定义需要包含`fparameters.h`头文件）


