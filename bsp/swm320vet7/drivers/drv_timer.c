/******************************************************************************
* @file drv_timer.c
* @author Zohar_Lee
* @version V1.00
* @date 2018.10.16
* @brief
******************************************************************************/
#include "SWM320.h"
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef RT_USING_HWTIMER

#ifdef BSP_USING_HWTIMER0
static rt_hwtimer_t _timer0;
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
static rt_hwtimer_t _timer1;
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
static rt_hwtimer_t _timer2;
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
static rt_hwtimer_t _timer3;
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
static rt_hwtimer_t _timer4;
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
static rt_hwtimer_t _timer5;
#endif //BSP_USING_HWTIMER5

static volatile rt_hwtimer_mode_t _timer0_mode = HWTIMER_MODE_PERIOD;
static volatile rt_hwtimer_mode_t _timer1_mode = HWTIMER_MODE_PERIOD;
static volatile rt_hwtimer_mode_t _timer2_mode = HWTIMER_MODE_PERIOD;
static volatile rt_hwtimer_mode_t _timer3_mode = HWTIMER_MODE_PERIOD;
static volatile rt_hwtimer_mode_t _timer4_mode = HWTIMER_MODE_PERIOD;
static volatile rt_hwtimer_mode_t _timer5_mode = HWTIMER_MODE_PERIOD;

void _hwtimer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
#ifdef BSP_USING_HWTIMER0
  if (&_timer0 == timer)
  {
    TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock / timer->freq, 1);
    if (1 == state)
      TIMR_Start(TIMR0);
    else if (0 == state)
      TIMR_Stop(TIMR0);
  }
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
  if (&_timer1 == timer)
  {
    TIMR_Init(TIMR1, TIMR_MODE_TIMER, SystemCoreClock / timer->freq, 1);
    if (1 == state)
      TIMR_Start(TIMR1);
    else if (0 == state)
      TIMR_Stop(TIMR1);
  }
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
  if (&_timer2 == timer)
  {
    TIMR_Init(TIMR2, TIMR_MODE_TIMER, SystemCoreClock / timer->freq, 1);
    if (1 == state)
      TIMR_Start(TIMR2);
    else if (0 == state)
      TIMR_Stop(TIMR2);
  }
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
  if (&_timer3 == timer)
  {
    TIMR_Init(TIMR3, TIMR_MODE_TIMER, SystemCoreClock / timer->freq, 1);
    if (1 == state)
      TIMR_Start(TIMR3);
    else if (0 == state)
      TIMR_Stop(TIMR3);
  }
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
  if (&_timer4 == timer)
  {
    TIMR_Init(TIMR4, TIMR_MODE_TIMER, SystemCoreClock / timer->freq, 1);
    if (1 == state)
      TIMR_Start(TIMR4);
    else if (0 == state)
      TIMR_Stop(TIMR4);
  }
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
  if (&_timer5 == timer)
  {
    TIMR_Init(TIMR5, TIMR_MODE_TIMER, SystemCoreClock / timer->freq, 1);
    if (1 == state)
      TIMR_Start(TIMR5);
    else if (0 == state)
      TIMR_Stop(TIMR5);
  }
#endif //BSP_USING_HWTIMER5
}

rt_err_t _hwtimer_start(struct rt_hwtimer_device *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
#ifdef BSP_USING_HWTIMER0
  if (&_timer0 == timer)
    TIMR_Start(TIMR0);
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
  if (&_timer1 == timer)
    TIMR_Start(TIMR1);
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
  if (&_timer2 == timer)
    TIMR_Start(TIMR2);
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
  if (&_timer3 == timer)
    TIMR_Start(TIMR3);
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
  if (&_timer4 == timer)
    TIMR_Start(TIMR4);
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
  if (&_timer5 == timer)
    TIMR_Start(TIMR5);
#endif //BSP_USING_HWTIMER5

  return RT_EOK;
}

void _hwtimer_stop(struct rt_hwtimer_device *timer)
{
#ifdef BSP_USING_HWTIMER0
  if (&_timer0 == timer)
    TIMR_Stop(TIMR0);
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
  if (&_timer1 == timer)
    TIMR_Stop(TIMR1);
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
  if (&_timer2 == timer)
    TIMR_Stop(TIMR2);
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
  if (&_timer3 == timer)
    TIMR_Stop(TIMR3);
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
  if (&_timer4 == timer)
    TIMR_Stop(TIMR4);
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
  if (&_timer5 == timer)
    TIMR_Stop(TIMR5);
#endif //BSP_USING_HWTIMER5
}

rt_uint32_t _hwtimer_count_get(struct rt_hwtimer_device *timer)
{
  rt_uint32_t hwtimer_count = 0;

#ifdef BSP_USING_HWTIMER0
  if (&_timer0 == timer)
    hwtimer_count = TIMR_GetCurValue(TIMR0);
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
  if (&_timer1 == timer)
    hwtimer_count = TIMR_GetCurValue(TIMR1);
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
  if (&_timer2 == timer)
    hwtimer_count = TIMR_GetCurValue(TIMR2);
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
  if (&_timer3 == timer)
    hwtimer_count = TIMR_GetCurValue(TIMR3);
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
  if (&_timer4 == timer)
    hwtimer_count = TIMR_GetCurValue(TIMR4);
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
  if (&_timer5 == timer)
    hwtimer_count = TIMR_GetCurValue(TIMR5);
#endif //BSP_USING_HWTIMER5

  return hwtimer_count;
}

void _hwtimer_freq_set(struct rt_hwtimer_device *timer, void *freq)
{
  uint32_t period = SystemCoreClock / *(uint32_t *)freq;

#ifdef BSP_USING_HWTIMER0
  if (&_timer0 == timer)
    TIMR_SetPeriod(TIMR0, period);
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
  if (&_timer1 == timer)
    TIMR_SetPeriod(TIMR1, period);
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
  if (&_timer2 == timer)
    TIMR_SetPeriod(TIMR2, period);
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
  if (&_timer3 == timer)
    TIMR_SetPeriod(TIMR3, period);
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
  if (&_timer4 == timer)
    TIMR_SetPeriod(TIMR4, period);
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
  if (&_timer5 == timer)
    TIMR_SetPeriod(TIMR5, period);
#endif //BSP_USING_HWTIMER5
}

void _hwtimer_info_get(struct rt_hwtimer_device *timer, void *info)
{
  *(struct rt_hwtimer_info *)info = *timer->info;
}

rt_uint32_t _hwtimer_mode_set(struct rt_hwtimer_device *timer, void *mode)
{

#ifdef BSP_USING_HWTIMER0
  if (&_timer0 == timer)
  {
    if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
    {
      _timer0_mode = HWTIMER_MODE_ONESHOT;
    }
    else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
    {
      _timer0_mode = HWTIMER_MODE_PERIOD;
    }
    else
    {
      return 0;
    }
  }
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
  if (&_timer1 == timer)
  {
    if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
    {
      _timer1_mode = HWTIMER_MODE_ONESHOT;
    }
    else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
    {
      _timer1_mode = HWTIMER_MODE_PERIOD;
    }
    else
    {
      return 0;
    }
  }
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
  if (&_timer2 == timer)
  {
    if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
    {
      _timer2_mode = HWTIMER_MODE_ONESHOT;
    }
    else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
    {
      _timer2_mode = HWTIMER_MODE_PERIOD;
    }
    else
    {
      return 0;
    }
  }
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
  if (&_timer3 == timer)
  {
    if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
    {
      _timer3_mode = HWTIMER_MODE_ONESHOT;
    }
    else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
    {
      _timer3_mode = HWTIMER_MODE_PERIOD;
    }
    else
    {
      return 0;
    }
  }
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
  if (&_timer4 == timer)
  {
    if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
    {
      _timer4_mode = HWTIMER_MODE_ONESHOT;
    }
    else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
    {
      _timer4_mode = HWTIMER_MODE_PERIOD;
    }
    else
    {
      return 0;
    }
  }
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
  if (&_timer5 == timer)
  {
    if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
    {
      _timer5_mode = HWTIMER_MODE_ONESHOT;
    }
    else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
    {
      _timer5_mode = HWTIMER_MODE_PERIOD;
    }
    else
    {
      return 0;
    }
  }
#endif //BSP_USING_HWTIMER5

  return RT_EOK;
}

rt_err_t _hwtimer_control(struct rt_hwtimer_device *timer, rt_uint32_t cmd, void *args)
{
  switch (cmd)
  {
  case HWTIMER_CTRL_FREQ_SET:
    _hwtimer_freq_set(timer, args);
    break;
  case HWTIMER_CTRL_STOP:
    _hwtimer_stop(timer);
    break;
  case HWTIMER_CTRL_INFO_GET:
    _hwtimer_info_get(timer, args);
    break;
  case HWTIMER_CTRL_MODE_SET:
    _hwtimer_mode_set(timer, args);
    break;
  default:
    break;
  }

  return RT_EOK;
}

#ifdef BSP_USING_HWTIMER0
void TIMR0_Handler(void)
{
  TIMR_INTClr(TIMR0);
  rt_device_hwtimer_isr(&_timer0);
}
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
void TIMR1_Handler(void)
{
  TIMR_INTClr(TIMR1);
  rt_device_hwtimer_isr(&_timer1);
}
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
void TIMR2_Handler(void)
{
  TIMR_INTClr(TIMR2);
  rt_device_hwtimer_isr(&_timer2);
}
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
void TIMR3_Handler(void)
{
  TIMR_INTClr(TIMR3);
  rt_device_hwtimer_isr(&_timer3);
}
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
void TIMR4_Handler(void)
{
  TIMR_INTClr(TIMR4);
  rt_device_hwtimer_isr(&_timer4);
}
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
void TIMR5_Handler(void)
{
  TIMR_INTClr(TIMR5);
  rt_device_hwtimer_isr(&_timer5);
}
#endif //BSP_USING_HWTIMER5

struct rt_hwtimer_ops _hwtimer_ops =
    {
        _hwtimer_init,
        _hwtimer_start,
        _hwtimer_stop,
        _hwtimer_count_get,
        _hwtimer_control};
struct rt_hwtimer_info _hwtimer_info =
    {
        32000, //默认使用最低频率工作，即32K
        1,     //2的32次方
        4294967295,
        0};
int bsp_hwtimer_init(void)
{
#ifdef BSP_USING_HWTIMER0
  _timer0.info = &_hwtimer_info;
  _timer0.ops = &_hwtimer_ops;
  rt_device_hwtimer_register(&_timer0, "timer0", TIMR0);
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
  _timer1.info = &_hwtimer_info;
  _timer1.ops = &_hwtimer_ops;
  rt_device_hwtimer_register(&_timer1, "timer1", TIMR1);
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
  _timer2.info = &_hwtimer_info;
  _timer2.ops = &_hwtimer_ops;
  rt_device_hwtimer_register(&_timer2, "timer2", TIMR2);
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
  _timer3.info = &_hwtimer_info;
  _timer3.ops = &_hwtimer_ops;
  rt_device_hwtimer_register(&_timer3, "timer3", TIMR3);

#endif //BSP_USING_HWTIMER3
#ifdef BSP_USING_HWTIMER4
  _timer4.info = &_hwtimer_info;
  _timer4.ops = &_hwtimer_ops;
  rt_device_hwtimer_register(&_timer4, "timer4", TIMR4);
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
  _timer5.info = &_hwtimer_info;
  _timer5.ops = &_hwtimer_ops;
  rt_device_hwtimer_register(&_timer5, "timer5", TIMR5);
#endif //BSP_USING_HWTIMER5o

  return 0;
}
INIT_DEVICE_EXPORT(bsp_hwtimer_init);

#endif //RT_USING_HWTIMER

/******************************* end of file *********************************/
