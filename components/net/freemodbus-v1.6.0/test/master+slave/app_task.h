/*********************************************************************************************************
//                             NCLUDE FILES
*********************************************************************************************************/
#ifndef APP_TASK_H
#define APP_TASK_H

#include <stdlib.h>
#include <stdio.h>
#include <rthw.h>
#include <rtthread.h>
#include "rtconfig.h"
#include "cpuusage.h"
#include "user_mb_app.h"


#if RT_TICK_PER_SECOND == 1
#define DELAY_1S			(RT_TICK_PER_SECOND)		
#define DELAY_S(X) 			(X*DELAY_1S)

#elif RT_TICK_PER_SECOND == 10				
#define DELAY_100MS(X)		(X)
#define DELAY_S(X)			(X*10)

#elif RT_TICK_PER_SECOND == 100		
#define	DELAY_10MS(X)		(X)
#define	DELAY_100MS(X)		(X*10)
#define DELAY_S(X)			(X*100)

#elif (RT_TICK_PER_SECOND == 1000)

#define DELAY_1MS           (RT_TICK_PER_SECOND/1000)		
#define DELAY_MS(X)         (X*DELAY_1MS)
#define DELAY_S(X)		    (X*1000*DELAY_1MS)

#elif (RT_TICK_PER_SECOND == 10000)||(RT_TICK_PER_SECOND == 100000)||(RT_TICK_PER_SECOND == 100000)
#define DELAY_100US(X)      (X*RT_TICK_PER_SECOND/10000)
#define DELAY_1MS           (RT_TICK_PER_SECOND/1000)		
#define DELAY_MS(X)         (X*DELAY_1MS)
#define DELAY_S(X)		    (X*1000*DELAY_1MS)

#endif

#define DELAY_SYS_MONITOR			DELAY_MS(500)  //system monitor thread delay
#define DELAY_MB_SLAVE_POLL		    DELAY_MS(10)   //Modbus slave poll
#define DELAY_MB_MASTER_POLL	    DELAY_MS(10)   //Modbus master poll


extern uint16_t   ucSDiscInBuf[]  ;
extern uint16_t   ucSCoilBuf[]    ;
extern uint16_t   usSRegInBuf[]   ;
extern uint16_t   usSRegHoldBuf[] ;


extern void cpu_usage_get(rt_uint8_t *major, rt_uint8_t *minor);
extern void cpu_usage_init(void);



#endif
