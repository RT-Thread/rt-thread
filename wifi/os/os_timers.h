/*
 * Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */

#ifndef	_OS_TIMERS_H
#define _OS_TIMERS_H
#include "os_defs.h"

typedef struct __WLAN_DRV_TIMER
{
    //struct timer_list tl;
    struct rt_timer tl;
	void (*timeoutfunction)(void* parameter);
    void (*timer_function) (void *context);
	void *timer_parameter;
    void *function_context;
    unsigned int time_period;
	char * name;
    BOOLEAN timer_is_periodic;
    BOOLEAN timer_is_canceled;
	char init_flag;	  /*0:uninitialized 1:initialized 2:has been used at least once*/
} WLAN_DRV_TIMER, *PWLAN_DRV_TIMER;

static  void TimerHandler(void* fcontext)
{
 
    PWLAN_DRV_TIMER timer = (PWLAN_DRV_TIMER) fcontext;

    timer->timer_function(timer->function_context);

   // if (timer->timer_is_periodic == TRUE) {
  //      mod_timer(&timer->tl, jiffies + ((timer->time_period * HZ) / 1000));
  //  }

}

static  void
InitializeTimer(PWLAN_DRV_TIMER timer,
                void (*TimerFunction) (void *context), void *FunctionContext,char *name)
{


    timer->timeoutfunction = TimerHandler;
	timer->timer_parameter=timer;
	if(name!=NULL)
   	timer->name=name;
    // then tell the proxy which function to call and what to pass it       
    timer->timer_function = TimerFunction;
    timer->function_context = FunctionContext;
    timer->timer_is_canceled = FALSE;
	timer->init_flag=1;
}

static  void
SetTimer(PWLAN_DRV_TIMER timer, unsigned int MillisecondPeriod)
{
 /*   timer->time_period = MillisecondPeriod;
    timer->timer_is_periodic = FALSE;
    timer->tl.expires = jiffies + (MillisecondPeriod * HZ) / 1000;
    add_timer(&timer->tl);
    timer->timer_is_canceled = FALSE;
    */
}
static  void
ModTimer(PWLAN_DRV_TIMER timer, unsigned int MillisecondPeriod)
{

  int tick=	(MillisecondPeriod/1000)*RT_TICK_PER_SECOND;
  timer->timer_is_periodic = FALSE;
  timer->time_period = MillisecondPeriod;
  if(timer->init_flag==1)
  {
  	rt_timer_init(&timer->tl, timer->name, timer->timeoutfunction,timer->timer_parameter,
		tick,RT_TIMER_FLAG_ONE_SHOT);
	timer->init_flag=2;
  }else if(timer->init_flag==2){
  	rt_timer_control(&timer->tl, RT_TIMER_CTRL_SET_TIME, &tick);
  }
  	rt_timer_start(&timer->tl);

  timer->timer_is_periodic = FALSE;
}

static  void
SetPeriodicTimer(PWLAN_DRV_TIMER timer, unsigned int MillisecondPeriod)
{
 /*   timer->time_period = MillisecondPeriod;
    timer->timer_is_periodic = TRUE;
    timer->tl.expires = jiffies + (MillisecondPeriod * HZ) / 1000;
    add_timer(&timer->tl);
    timer->timer_is_canceled = FALSE;
    */
}

#define	FreeTimer(x)	do {} while (0)

static  void CancelTimer(WLAN_DRV_TIMER * timer)
{
  /*  del_timer(&timer->tl);
    timer->timer_is_canceled = TRUE;
    */
     rt_timer_detach(&timer->tl);
}

#endif /* _OS_TIMERS_H */
