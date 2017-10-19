/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	4

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second */
#define RT_TICK_PER_SECOND	100

/* SECTION: RT_DEBUG */
/* Thread Debug */
#define RT_DEBUG
#define RT_THREAD_DEBUG

#define RT_USING_OVERFLOW_CHECK

/* Using Hook */
#define RT_USING_HOOK

/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO		4
#define RT_TIMER_THREAD_STACK_SIZE	512
#define RT_TIMER_TICK_PER_SECOND	10

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex */
#define RT_USING_MUTEX

/* Using Event */
#define RT_USING_EVENT

/* Using MailBox */
#define RT_USING_MAILBOX

/* Using Message Queue */
#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management */
#define RT_USING_HEAP

/* Using Small MM */
#define RT_USING_SMALL_MEM

// <bool name="RT_USING_COMPONENTS_INIT" description="Using RT-Thread components initialization" default="true" />
//#define RT_USING_COMPONENTS_INIT

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE
// <bool name="RT_USING_DEVICE_IPC" description="Using device communication" default="true" />
#define RT_USING_DEVICE_IPC



/* SECTION: device filesystem */
//#define RT_USING_DFS 

#define RT_USING_DFS_ELMFAT
/* Reentrancy (thread safe) of the FatFs module.  */
#define RT_DFS_ELM_REENTRANT
/* Number of volumes (logical drives) to be used. */
#define RT_DFS_ELM_DRIVES			1
/* #define RT_DFS_ELM_USE_LFN			1 */
/* #define RT_DFS_ELM_CODE_PAGE			936 */
#define RT_DFS_ELM_MAX_LFN			255
/* Maximum sector size to be handled. */
#define RT_DFS_ELM_MAX_SECTOR_SIZE  4096

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX			1
/* the max number of opened files 		*/
#define DFS_FD_MAX					4

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
/* #define RT_USING_LWIP */
/* LwIP uses RT-Thread Memory Management */
#define RT_LWIP_USING_RT_MEM
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
/* Enable DNS */
#define RT_LWIP_DNS

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM	5

/* Using DHCP */
/* #define RT_LWIP_DHCP */

/* ip address of target*/
#define RT_LWIP_IPADDR0	192
#define RT_LWIP_IPADDR1	168
#define RT_LWIP_IPADDR2	1
#define RT_LWIP_IPADDR3	30

/* gateway address of target*/
#define RT_LWIP_GWADDR0	192
#define RT_LWIP_GWADDR1	168
#define RT_LWIP_GWADDR2	1
#define RT_LWIP_GWADDR3	1

/* mask address of target*/
#define RT_LWIP_MSKADDR0	255
#define RT_LWIP_MSKADDR1	255
#define RT_LWIP_MSKADDR2	255
#define RT_LWIP_MSKADDR3	0

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY		12
#define RT_LWIP_TCPTHREAD_MBOX_SIZE		10
#define RT_LWIP_TCPTHREAD_STACKSIZE		1024

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY		15
#define RT_LWIP_ETHTHREAD_MBOX_SIZE		10
#define RT_LWIP_ETHTHREAD_STACKSIZE		512

/* TCP sender buffer space */
#define RT_LWIP_TCP_SND_BUF	8192
/* TCP receive window. */
#define RT_LWIP_TCP_WND		8192

/* image support */
/* #define RTGUI_IMAGE_XPM */
/* #define RTGUI_IMAGE_BMP */

// <bool name="RT_USING_CMSIS_OS" description="Using CMSIS OS API" default="true" />
// #define RT_USING_CMSIS_OS
// <bool name="RT_USING_RTT_CMSIS" description="Using CMSIS in RTT" default="true" />
#define RT_USING_RTT_CMSIS
// <bool name="RT_USING_BSP_CMSIS" description="Using CMSIS in BSP" default="true" />
// #define RT_USING_BSP_CMSIS

/* nanopb support */
/* #define RT_USING_NANOPB */

#define RT_USING_CPU_FFS

#define HAL_MODULE_ENABLED
// #define HAL_ADC_MODULE_ENABLED
// #define HAL_CAN_MODULE_ENABLED
// #define HAL_CEC_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
// #define HAL_CRC_MODULE_ENABLED
// #define HAL_DAC_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
// #define HAL_ETH_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
// #define HAL_HCD_MODULE_ENABLED
// #define HAL_I2C_MODULE_ENABLED
// #define HAL_I2S_MODULE_ENABLED
// #define HAL_IRDA_MODULE_ENABLED
// #define HAL_IWDG_MODULE_ENABLED
// #define HAL_NAND_MODULE_ENABLED
// #define HAL_NOR_MODULE_ENABLED
// #define HAL_PCCARD_MODULE_ENABLED
#define HAL_PCD_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
// #define HAL_RTC_MODULE_ENABLED
// #define HAL_SD_MODULE_ENABLED
// #define HAL_SMARTCARD_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
// #define HAL_SRAM_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_USART_MODULE_ENABLED
// #define HAL_WWDG_MODULE_ENABLED
// #define HAL_MMC_MODULE_ENABLED


#define RT_USING_SERIAL

#define RT_USING_PIN

#define RT_USING_UART1

#define RT_CONSOLE_DEVICE_NAME	    "uart1"
/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	        128
// <string name="RT_CONSOLE_DEVICE_NAME" description="The device name for console" default="uart1" />


/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH

//#define FINSH_USING_MSH
/* Using symbol table */
#define FINSH_USING_SYMTAB

#define FINSH_USING_DESCRIPTION

//#define RT_USING_SPI

#define SPI_USE_DMA

#define RT_USING_W25QXX

#endif
