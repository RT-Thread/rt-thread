#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

#define SOC_C6678

/* RT-Thread Kernel */

#define RT_NAME_MAX 12
#define RT_USING_ARCH_DATA_TYPE
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_8
#define RT_THREAD_PRIORITY_MAX 8
#define RT_TICK_PER_SECOND 100
//#define RT_USING_HOOK
//#define RT_USING_IDLE_HOOK
//#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 4096
//#define RT_DEBUG
//#define RT_DEBUG_COLOR

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_HEAP

/* Kernel Device Object */

/* RT-Thread Components */

/* C++ features */


/* Command shell */

/* Device virtual file system */


/* Device Drivers */

/* Using WiFi */


/* Using USB */


/* POSIX layer and C standard library */


/* Network */

/* Socket abstraction layer */


/* light weight TCP/IP stack */


/* Modbus master and slave stack */


/* AT commands */


/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */


/* IoT Cloud */


/* security packages */


/* language packages */


/* multimedia packages */


/* tools packages */


/* system packages */


/* peripheral libraries and drivers */


/* miscellaneous packages */


/* samples: kernel and components samples */

#include "rtconfig_project.h"

#endif
