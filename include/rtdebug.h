#ifndef __RTDEBUG_H__
#define __RTDEBUG_H__

#include <rtconfig.h>

/* Using this macro to control all kernel debug features. */
#ifdef RT_DEBUG

/* Turn on some of these (set to non-zero) to debug kernel */
#ifndef RT_DEBUG_MEM
#define RT_DEBUG_MEM        0
#endif

#ifndef RT_DEBUG_MODULE
#define RT_DEBUG_MODULE     0
#endif

#ifndef RT_DEBUG_SCHEDULER
#define RT_DEBUG_SCHEDULER  0
#endif

#ifndef RT_DEBUG_SLAB
#define RT_DEBUG_SLAB       0
#endif

#ifndef RT_DEBUG_THREAD
#define RT_DEBUG_THREAD     0
#endif

#ifndef RT_DEBUG_TIMER
#define RT_DEBUG_TIMER      0
#endif

#ifndef RT_DEBUG_IRQ
#define RT_DEBUG_IRQ        0
#endif

#ifndef RT_DEBUG_IPC
#define RT_DEBUG_IPC        0
#endif

/* Turn on this to enable reentrance check */
#ifndef RT_DEBUG_REENT_CHK
#define RT_DEBUG_REENT_CHK  1
#endif

#define RT_DEBUG_LOG(type,message)  do{ if(type) rt_kprintf message;}while(0)

#define RT_ASSERT(EX)   if (!(EX)) {volatile char dummy=0;\
                            rt_kprintf("(%s) assert failed at %s:%d \n", \
                            #EX, __FUNCTION__, __LINE__); while (dummy==0);}

/* Reentrance check */
/* counter */
extern rt_uint8_t rt_debug_reent_cnt;

#define RT_DEBUG_REENT_IN if(RT_DEBUG_REENT_CHK){\
        rt_base_t level;\
        level = rt_hw_interrupt_disable();\
        rt_debug_reent_cnt++;\
        rt_hw_interrupt_enable(level);}

#define RT_DEBUG_REENT_OUT if(RT_DEBUG_REENT_CHK){\
        rt_base_t level;\
        level = rt_hw_interrupt_disable();\
        rt_debug_reent_cnt--;\
        rt_hw_interrupt_enable(level);}

/* Mark those non-reentrant functions with this macro */
#define RT_DEBUG_NOT_REENT if(RT_DEBUG_REENT_CHK){\
        rt_base_t level;\
        level = rt_hw_interrupt_disable();\
        if(rt_debug_reent_cnt != 0){\
            rt_kprintf("Non-reentrant function used in critical area!\n");\
            RT_ASSERT(0)}\
        rt_hw_interrupt_enable(level);}


#else /* RT_DEBUG */

#define RT_ASSERT(EX)
#define RT_DEBUG_LOG(type,message)
#define RT_DEBUG_REENT_IN
#define RT_DEBUG_REENT_OUT
#define RT_DEBUG_NOT_REENT

#endif /* RT_DEBUG */



#endif /* __RTDEBUG_H__ */
