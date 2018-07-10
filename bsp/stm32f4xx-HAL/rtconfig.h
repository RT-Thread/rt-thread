#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
/* RT_THREAD_PRIORITY_8 is not set */
#define RT_THREAD_PRIORITY_32
/* RT_THREAD_PRIORITY_256 is not set */
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 100
#define RT_DEBUG
#define RT_USING_OVERFLOW_CHECK
#define RT_DEBUG_INIT 0
#define RT_DEBUG_THREAD 0
#define RT_USING_HOOK
#define IDLE_THREAD_STACK_SIZE 256
/* RT_USING_TIMER_SOFT is not set */

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
/* RT_USING_SIGNALS is not set */

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
/* RT_USING_NOHEAP is not set */
#define RT_USING_SMALL_MEM
/* RT_USING_SLAB is not set */
/* RT_USING_MEMHEAP_AS_HEAP is not set */
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
/* RT_USING_INTERRUPT_INFO is not set */
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart2"
/* RT_USING_MODULE is not set */

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN

/* C++ features */

/* RT_USING_CPLUSPLUS is not set */

/* Command shell */

#define RT_USING_FINSH
#define FINSH_USING_HISTORY
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_CMD_SIZE 80
/* FINSH_USING_AUTH is not set */
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY

/* Device virtual file system */

/* RT_USING_DFS is not set */

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SERIAL
/* RT_USING_CAN is not set */
/* RT_USING_HWTIMER is not set */
/* RT_USING_I2C is not set */
#define RT_USING_PIN
/* RT_USING_MTD_NOR is not set */
/* RT_USING_MTD_NAND is not set */
/* RT_USING_RTC is not set */
/* RT_USING_SDIO is not set */
/* RT_USING_SPI is not set */
/* RT_USING_WDT is not set */
/* RT_USING_WIFI is not set */

/* Using USB */

/* RT_USING_USB_HOST is not set */
/* RT_USING_USB_DEVICE is not set */

/* POSIX layer and C standard library */

/* RT_USING_LIBC is not set */
/* RT_USING_PTHREADS is not set */

/* Network stack */

/* light weight TCP/IP stack */

/* RT_USING_LWIP is not set */

/* Modbus master and slave stack */

/* RT_USING_MODBUS is not set */

/* RT-Thread UI Engine */

/* PKG_USING_GUIENGINE is not set */

/* VBUS(Virtual Software BUS) */

/* RT_USING_VBUS is not set */

/* Utilities */

/* RT_USING_LOGTRACE is not set */
/* RT_USING_RYM is not set */

/* RT-Thread online packages */

/* system packages */

/* PKG_USING_PARTITION is not set */
/* PKG_USING_SQLITE is not set */

/* IoT - internet of things */

/* PKG_USING_CJSON is not set */
/* PKG_USING_PAHOMQTT is not set */
/* PKG_USING_WEBCLIENT is not set */
/* PKG_USING_MONGOOSE is not set */
/* PKG_USING_WEBTERMINAL is not set */

/* security packages */

/* PKG_USING_MBEDTLS is not set */

/* language packages */

/* PKG_USING_JERRYSCRIPT is not set */

/* multimedia packages */

/* tools packages */

/* PKG_USING_CMBACKTRACE is not set */
/* PKG_USING_EASYLOGGER is not set */

/* miscellaneous packages */

/* PKG_USING_HELLO is not set */
/* SOC_STM32F405RG is not set */
/* SOC_STM32F405VG is not set */
/* SOC_STM32F405ZG is not set */
/* SOC_STM32F415RG is not set */
/* SOC_STM32F415VG is not set */
/* SOC_STM32F415ZG is not set */
#define SOC_STM32F407VG
/* SOC_STM32F407VE is not set */
/* SOC_STM32F407ZG is not set */
/* SOC_STM32F407ZE is not set */
/* SOC_STM32F407IG is not set */
/* SOC_STM32F407IE is not set */
/* SOC_STM32F417VG is not set */
/* SOC_STM32F417VE is not set */
/* SOC_STM32F417ZG is not set */
/* SOC_STM32F417ZE is not set */
/* SOC_STM32F417IG is not set */
/* SOC_STM32F417IE is not set */
/* SOC_STM32F427VG is not set */
/* SOC_STM32F427VI is not set */
/* SOC_STM32F427ZG is not set */
/* SOC_STM32F427ZI is not set */
/* SOC_STM32F427IG is not set */
/* SOC_STM32F427II is not set */
/* SOC_STM32F437VG is not set */
/* SOC_STM32F437VI is not set */
/* SOC_STM32F437ZG is not set */
/* SOC_STM32F437ZI is not set */
/* SOC_STM32F437IG is not set */
/* SOC_STM32F437II is not set */
/* SOC_STM32F429VG is not set */
/* SOC_STM32F429VI is not set */
/* SOC_STM32F429ZG is not set */
/* SOC_STM32F429ZI is not set */
/* SOC_STM32F429BG is not set */
/* SOC_STM32F429BI is not set */
/* SOC_STM32F429NG is not set */
/* SOC_STM32F429NI is not set */
/* SOC_STM32F429IG is not set */
/* SOC_STM32F429II is not set */
/* SOC_STM32F439VG is not set */
/* SOC_STM32F439VI is not set */
/* SOC_STM32F439ZG is not set */
/* SOC_STM32F439ZI is not set */
/* SOC_STM32F439BG is not set */
/* SOC_STM32F439BI is not set */
/* SOC_STM32F439NG is not set */
/* SOC_STM32F439NI is not set */
/* SOC_STM32F439IG is not set */
/* SOC_STM32F439II is not set */
/* SOC_STM32F401CB is not set */
/* SOC_STM32F401CC is not set */
/* SOC_STM32F401RB is not set */
/* SOC_STM32F401RC is not set */
/* SOC_STM32F401VB is not set */
/* SOC_STM32F401VC is not set */
/* SOC_STM32F401CD is not set */
/* SOC_STM32F401RD is not set */
/* SOC_STM32F401VD is not set */
/* SOC_STM32F401CE is not set */
/* SOC_STM32F401RE is not set */
/* SOC_STM32F401VE is not set */
/* SOC_STM32F410T8 is not set */
/* SOC_STM32F410TB is not set */
/* SOC_STM32F410C8 is not set */
/* SOC_STM32F410CB is not set */
/* SOC_STM32F410R8 is not set */
/* SOC_STM32F410RB is not set */
/* SOC_STM32F411CC is not set */
/* SOC_STM32F411RC is not set */
/* SOC_STM32F411VC is not set */
/* SOC_STM32F411CE is not set */
/* SOC_STM32F411RE is not set */
/* SOC_STM32F411VE is not set */
/* SOC_STM32F446MC is not set */
/* SOC_STM32F446ME is not set */
/* SOC_STM32F446RC is not set */
/* SOC_STM32F446RE is not set */
/* SOC_STM32F446VC is not set */
/* SOC_STM32F446VE is not set */
/* SOC_STM32F446ZC is not set */
/* SOC_STM32F446ZE is not set */
/* SOC_STM32F469AI is not set */
/* SOC_STM32F469II is not set */
/* SOC_STM32F469BI is not set */
/* SOC_STM32F469NI is not set */
/* SOC_STM32F469AG is not set */
/* SOC_STM32F469IG is not set */
/* SOC_STM32F469BG is not set */
/* SOC_STM32F469NG is not set */
/* SOC_STM32F469AE is not set */
/* SOC_STM32F469IE is not set */
/* SOC_STM32F469BE is not set */
/* SOC_STM32F469NE is not set */
/* SOC_STM32F479AI is not set */
/* SOC_STM32F479II is not set */
/* SOC_STM32F479BI is not set */
/* SOC_STM32F479NI is not set */
/* SOC_STM32F479AG is not set */
/* SOC_STM32F479IG is not set */
/* SOC_STM32F479BG is not set */
/* SOC_STM32F479NG is not set */
/* SOC_STM32F412CEU is not set */
/* SOC_STM32F412CGU is not set */
/* SOC_STM32F412ZET is not set */
/* SOC_STM32F412ZGT is not set */
/* SOC_STM32F412ZEJ is not set */
/* SOC_STM32F412ZGJ is not set */
/* SOC_STM32F412VET is not set */
/* SOC_STM32F412VGT is not set */
/* SOC_STM32F412VEH is not set */
/* SOC_STM32F412VGH is not set */
/* SOC_STM32F412RET is not set */
/* SOC_STM32F412RGT is not set */
/* SOC_STM32F412REY is not set */
/* SOC_STM32F412RGY is not set */
/* SOC_STM32F413CH is not set */
/* SOC_STM32F413MH is not set */
/* SOC_STM32F413RH is not set */
/* SOC_STM32F413VH is not set */
/* SOC_STM32F413ZH is not set */
/* SOC_STM32F413CG is not set */
/* SOC_STM32F413MG is not set */
/* SOC_STM32F413RG is not set */
/* SOC_STM32F413VG is not set */
/* SOC_STM32F413ZG is not set */
/* SOC_STM32F423CH is not set */
/* SOC_STM32F423RH is not set */
/* SOC_STM32F423VH is not set */
/* SOC_STM32F423ZH is not set */
/* RT_USING_HSI is not set */
#define RT_HSE_VALUE 8000000
#define RT_HSE_HCLK 168000000
/* RT_USING_UART1 is not set */
#define RT_USING_UART2
/* RT_USING_UART6 is not set */

#endif
