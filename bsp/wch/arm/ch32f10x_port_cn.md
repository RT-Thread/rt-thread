# CH32F10X系列BSP移植
## 1 工程结构
+ wch\arm\ch32f103c8-core
+ wch\arm\Libraries
+ wch\arm\Libraries\ch32_drivers
+ wch\arm\Libraries\CH32F10x_StdPeriph_Driver
+ wch\arm\tools

ch32f103c8-core为移植到具体芯片的BSP, Libraries存放的是厂商的驱动库(CH32F10x_StdPeriph_Driver等)和适配rt-thread的驱动(ch32_drivers),
tools是在env环境下使用scons --dist所需要的依赖工具

### 1.1 已适配rt-thread的驱动(ch32_drivers)：
现已支持以下驱动(支持的驱动，使用到的宏开关，需要实现的接口)：
+ GPIO
   + RT_USING_PIN
+ UART 1/2/3
   + RT_USING_SERIAL
   + BSP_USING_UART
      + BSP_USING_UART1
      + BSP_USING_UART2
      + BSP_USING_UART3
~~~c
void ch32f1_usart_clock_and_io_init(USART_TypeDef* usartx);
~~~
+ SPI 1/2
   + RT_USING_SPI
   + BSP_USING_SPI
      + BSP_USING_SPI1
      + BSP_USING_SPI2
~~~c
void ch32f1_spi_clock_and_io_init(SPI_TypeDef* spix);
rt_uint32_t ch32f1_spi_clock_get(SPI_TypeDef* spix);
~~~
+ I2C(hardware) 1/2
   + RT_USING_I2C
   + BSP_USING_HWI2C
      + BSP_USING_HWI2C1
      + BSP_USING_HWI2C2
~~~c
void ch32f1_i2c_clock_and_io_init(I2C_TypeDef* i2cx);
void ch32f1_i2c_config(I2C_TypeDef* i2cx);
~~~
+ WDT
   + RT_USING_WDT
   + BSP_USING_IWDT
      + LSI_VALUE
+ RTC
   + RT_USING_RTC
   + BSP_USING_RTC
      + BSP_USING_RTC_LSI
      + LSI_VALUE
+ HWTIMER 1/2/3/4
   + RT_USING_HWTIMER
   + BSP_USING_HWTIMER
      + BSP_USING_TIM1_HWTIMER
      + BSP_USING_TIM2_HWTIMER
      + BSP_USING_TIM3_HWTIMER
      + BSP_USING_TIM4_HWTIMER
~~~c
void ch32f1_tim_clock_init(TIM_TypeDef *timx);
rt_uint32_t ch32f1_tim_clock_get(TIM_TypeDef *timx);
~~~
~~~c
struct rt_hwtimer_info* ch32f1_hwtimer_info_config_get(TIM_TypeDef *timx);
~~~
+ PWM  4(timer) x 4 (channel)
   + RT_USING_PWM
   + BSP_USING_TIM1_PWM
      + BSP_USING_TIM1_PWM_CH1
      + BSP_USING_TIM1_PWM_CH2
      + BSP_USING_TIM1_PWM_CH3
      + BSP_USING_TIM1_PWM_CH4
   + BSP_USING_TIM2_PWM
      + BSP_USING_TIM2_PWM_CH1
      + BSP_USING_TIM2_PWM_CH2
      + BSP_USING_TIM2_PWM_CH3
      + BSP_USING_TIM2_PWM_CH4
   + BSP_USING_TIM3_PWM
      + BSP_USING_TIM3_PWM_CH1
      + BSP_USING_TIM3_PWM_CH2
      + BSP_USING_TIM3_PWM_CH3
      + BSP_USING_TIM3_PWM_CH4
   + BSP_USING_TIM4_PWM
      + BSP_USING_TIM4_PWM_CH1
      + BSP_USING_TIM4_PWM_CH2
      + BSP_USING_TIM4_PWM_CH3
      + BSP_USING_TIM4_PWM_CH4
~~~c
void ch32f1_pwm_io_init(TIM_TypeDef *timx, rt_uint8_t channel);
~~~
其中需要依赖定时器的接口：
~~~c
void ch32f1_tim_clock_init(TIM_TypeDef *timx);
rt_uint32_t ch32f1_tim_clock_get(TIM_TypeDef *timx);
~~~


### 1.2 需要实现的接口：
除了使用上面驱动提及的接口外，以下的接口必须实现：
~~~c
rt_uint32_t ch32_get_sysclock_frequency(void);
~~~
## 2 构建具体芯片BSP
以ch32f103c8-core为例，在ENV环境下，使用MDK，至少需要准备
+ ch32f103c8-core (具体的BSP名)
+ ch32f103c8-core\applications
+ ch32f103c8-core\applications\SConscript
+ ch32f103c8-core\applications\main.c
+ ch32f103c8-core\board
+ ch32f103c8-core\board\linker_scripts
+ ch32f103c8-core\board\linker_scripts\link.sct
+ ch32f103c8-core\board\board.c
+ ch32f103c8-core\board\board.h
+ ch32f103c8-core\board\ch32f10x_conf.h
+ ch32f103c8-core\board\system_ch32f10x.c
+ ch32f103c8-core\board\Kconfig
+ ch32f103c8-core\board\SConscript
+ ch32f103c8-core\Kconfig
+ ch32f103c8-core\rtconfig.py
+ ch32f103c8-core\SConscript
+ ch32f103c8-core\SConstruct
+ ch32f103c8-core\template.uvprojx

### 2.1 创建template.uvprojx
新建名为template的MDK工程，删除多余的子目录target1，将目录改名为rtthread-ch32f103x，options选项栏device设置具体芯片，user编译后的动作, 如"fromelf --bin !L --output rtthread.bin"

### 2.2 编写board/Kconfig

~~~
menu "Hardware Drivers Config"

config SOC_CH32F103C8
        bool
        select SOC_ARM_SERIES_CH32F103
        select RT_USING_COMPONENTS_INIT
        select RT_USING_USER_MAIN
        default y
~~~
SOC_CH32F103C8为具体的芯片，SOC_ARM_SERIES_CH32F103在Libraries\Kconfig下已定义。
RT_USING_COMPONENTS_INIT，RT_USING_USER_MAIN为rt-thread设备框架默认选项。


使用适配的驱动根据宏开关编写即可，以串口驱动为例：
+ BSP_USING_XXX
   + select RT_USING_XXX
      + BSP_USING_XXX1
      + BSP_USING_XXX2

~~~
menu "On-chip Peripheral Drivers"

config BSP_USING_UART
        bool "using onchip usart"
        select RT_USING_SERIAL
        default n

        if BSP_USING_UART
                config BSP_USING_UART1
                        bool "using uart1"
                        default n

                config BSP_USING_UART2
                        bool "using uart2"
                        default n

                config BSP_USING_UART3
                        bool "using uart3"
                        default n
        endif
~~~

比较特殊的定时器和PWM驱动额外定义了以下宏开关，详见ch32f103c8-core。
+ BSP_USING_TIM
   + BSP_USING_TIM1
   + BSP_USING_TIM2
   + BSP_USING_TIM3
   + BSP_USING_TIM4
### 2.3 在board/board.h加入接口，并在board/board.c实现
使用适配的驱动根据宏开关编写即可,如串口驱动：
+ BSP_USING_XXX
~~~
#ifdef BSP_USING_UART
void ch32f1_usart_clock_and_io_init(USART_TypeDef* usartx);
#endif
~~~
比较特殊的定时器和PWM驱动使用额外定义了的宏开关
~~~c
#ifdef BSP_USING_TIM
void ch32f1_tim_clock_init(TIM_TypeDef *timx);
rt_uint32_t ch32f1_tim_clock_get(TIM_TypeDef *timx);

#ifdef BSP_USING_HWTIMER
struct rt_hwtimer_info* ch32f1_hwtimer_info_config_get(TIM_TypeDef *timx);
#endif

#ifdef BSP_USING_PWM
void ch32f1_pwm_io_init(TIM_TypeDef *timx, rt_uint8_t channel);
#endif
#endif
~~~
