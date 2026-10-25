#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* RT-Thread Kernel */

/* klibc options */

/* rt_vsnprintf options */

/* end of rt_vsnprintf options */

/* rt_vsscanf options */

/* end of rt_vsscanf options */

/* rt_memset options */

/* end of rt_memset options */

/* rt_memcpy options */

/* end of rt_memcpy options */

/* rt_memmove options */

/* end of rt_memmove options */

/* rt_memcmp options */

/* end of rt_memcmp options */

/* rt_strstr options */

/* end of rt_strstr options */

/* rt_strcasecmp options */

/* end of rt_strcasecmp options */

/* rt_strncpy options */

/* end of rt_strncpy options */

/* rt_strcpy options */

/* end of rt_strcpy options */

/* rt_strncmp options */

/* end of rt_strncmp options */

/* rt_strcmp options */

/* end of rt_strcmp options */

/* rt_strlen options */

/* end of rt_strlen options */

/* rt_strnlen options */

/* end of rt_strnlen options */
/* end of klibc options */
#define RT_NAME_MAX 24
#define RT_USING_SMP
#define RT_CPUS_NR 4
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 4096
#define SYSTEM_THREAD_STACK_SIZE 8192
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 4096

/* kservice options */

/* end of kservice options */
#define RT_USING_DEBUG
#define RT_DEBUGING_ASSERT
#define RT_DEBUGING_COLOR
#define RT_DEBUGING_CONTEXT

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
/* end of Inter-Thread communication */

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_MEMHEAP_FAST_MODE
#define RT_USING_MEMHEAP_AS_HEAP
#define RT_USING_MEMHEAP_AUTO_BINDING
#define RT_USING_HEAP
/* end of Memory Management */
#define RT_USING_DEVICE
#define RT_USING_DEVICE_OPS
#define RT_USING_INTERRUPT_INFO
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 256
#define RT_CONSOLE_DEVICE_NAME "uart0"
#define RT_USING_CONSOLE_OUTPUT_CTL
#define RT_VER_NUM 0x50400
#define RT_USING_STDC_ATOMIC
#define RT_BACKTRACE_LEVEL_MAX_NR 32
/* end of RT-Thread Kernel */

/* AArch64 Architecture Configuration */

#define ARCH_TEXT_OFFSET 0x80000
#define ARCH_RAM_OFFSET 0x40000000
#define ARCH_SECONDARY_CPU_STACK_SIZE 4096
#define ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
#define ARCH_USING_GENERIC_CPUID
#define ARCH_HEAP_SIZE 0x4000000
#define ARCH_INIT_PAGE_SIZE 0x200000
/* end of AArch64 Architecture Configuration */
#define ARCH_CPU_64BIT
#define RT_USING_CACHE
#define RT_USING_CPU_FFS
#define ARCH_MM_MMU
#define ARCH_ARM
#define ARCH_ARM_MMU
#define ARCH_ARMV8
#define ARCH_USING_ASID
#define ARCH_USING_HW_THREAD_SELF
#define ARCH_USING_IRQ_CTX_LIST

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 8192
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 16384
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
#define FINSH_USING_OPTION_COMPLETION

/* DFS: device virtual file system */

#define RT_USING_DFS
#define DFS_USING_POSIX
#define DFS_USING_WORKDIR
#define DFS_FD_MAX 16
#define RT_USING_DFS_V1
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FILESYSTEM_TYPES_MAX 4
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_LFN_UNICODE_0
#define RT_DFS_ELM_LFN_UNICODE 0
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 512
#define RT_DFS_ELM_REENTRANT
#define RT_DFS_ELM_MUTEX_TIMEOUT 3000
/* end of elm-chan's FatFs, Generic FAT Filesystem Module */
#define RT_USING_DFS_DEVFS
/* end of DFS: device virtual file system */

/* Device Drivers */

#define RT_USING_DM
#define RT_USING_DEV_BUS
#define RT_USING_DEVICE_IPC
#define RT_UNAMED_PIPE_NUMBER 64
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 8192
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_RB_BUFSZ 256
#define RT_SERIAL_8250
#define RT_SERIAL_8250_DW
#define RT_USING_ADC
#define RT_USING_ADC_V1
#define RT_ADC_SUNXI_GPADC
#define RT_INPUT_SUNXI_LRADC
#define RT_USING_CLOCK_TIME
#define RT_CLOCK_TIME_ARM_ARCH
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_I2C_SUNXI
#define RT_USING_PWM
#define RT_PWM_SUNXI
#define RT_USING_INPUT_CAPTURE
#define RT_INPUT_CAPTURE_RB_SIZE 100
#define RT_INPUT_CAPTURE_SUNXI_IRRX
#define RT_USING_MTD_NOR
#define RT_USING_MTD_NOR_SPI
#define RT_USING_RTC
#define RT_USING_ALARM
#define RT_ALARM_STACK_SIZE 4096
#define RT_ALARM_TIMESLICE 5
#define RT_ALARM_PRIORITY 10
#define RT_RTC_SUNXI
#define RT_USING_SDIO
#define RT_SDIO_STACK_SIZE 8192
#define RT_SDIO_THREAD_PRIORITY 15
#define RT_MMCSD_STACK_SIZE 8192
#define RT_MMCSD_THREAD_PRIORITY 22
#define RT_MMCSD_MAX_PARTITION 16
#define RT_SDIO_SUNXI
#define RT_USING_SPI
#define RT_USING_SPI_ISR
#define RT_USING_SFUD
#define RT_SFUD_USING_SFDP
#define RT_SFUD_USING_FLASH_INFO_TABLE
#define RT_SFUD_SPI_MAX_HZ 50000000
#define RT_SPI_SUNXI
#define RT_USING_WDT
#define RT_WDT_SUNXI
#define RT_USING_AUDIO
#define RT_AUDIO_REPLAY_MP_BLOCK_SIZE 4096
#define RT_AUDIO_REPLAY_MP_BLOCK_COUNT 2
#define RT_AUDIO_RECORD_PIPE_SIZE 2048
#define RT_AUDIO_SUN50I_H616_CODEC
#define RT_AUDIO_SUN50I_H616_AHUB
#define RT_USING_LCD
#define RT_USING_GRAPHIC
#define RT_GRAPHIC_FB
#define RT_GRAPHIC_FB_SIMPLE
#define RT_GRAPHIC_FB_SUN50I_H616_DE33
#define RT_GRAPHIC_LOGO
#define RT_GRAPHIC_LOGO_RT_THREAD_CLUT224
#define RT_USING_HWCRYPTO
#define RT_HWCRYPTO_DEFAULT_NAME "hwcryto"
#define RT_HWCRYPTO_IV_MAX_SIZE 16
#define RT_HWCRYPTO_KEYBIT_MAX_SIZE 256
#define RT_HWCRYPTO_USING_AES
#define RT_HWCRYPTO_USING_AES_ECB
#define RT_HWCRYPTO_USING_AES_CBC
#define RT_HWCRYPTO_USING_RNG
#define RT_HWCRYPTO_SUN50I_H616_CE
#define RT_USING_LED
#define RT_LED_GPIO
#define RT_USING_INPUT
#define RT_INPUT_POWER
#define RT_USING_BLK

/* Partition Types */

#define RT_BLK_PARTITION_DFS
#define RT_BLK_PARTITION_EFI
/* end of Partition Types */
#define RT_USING_DVFS
#define RT_USING_DVFS_EVENT
#define RT_USING_DVFS_OPP_RETRY_MAX 10

/* DVFS Event Drivers */

/* DVFS CPUfreq Drivers */

#define RT_DVFS_SUN50I_H616_CPUFREQ

/* DVFS Devfreq Drivers */

#define RT_USING_REGULATOR
#define RT_REGULATOR_AXP313A
#define RT_REGULATOR_FIXED
#define RT_REGULATOR_GPIO
#define RT_USING_RESET

/* Power Management (PM) Domains device drivers */

/* end of Power Management (PM) Domains device drivers */
#define RT_USING_THERMAL

/* Thermal Sensors Drivers */

#define RT_THERMAL_SUN50I_H616

/* Thermal Cool Drivers */

#define RT_THERMAL_COOL_DVFS
#define RT_USING_NVMEM
#define RT_NVMEM_SUNXI_SID
#define RT_USING_DMA
#define RT_DMA_SUNXI
#define RT_USING_MFD
#define RT_MFD_SYSCON
#define RT_USING_OFW
#define RT_FDT_EARLYCON_MSG_SIZE 128
#define RT_USING_OFW_BUS_RANGES_NUMBER 8
#define RT_USING_PIC
#define MAX_HANDLERS 256
#define RT_PIC_ARM_GIC
#define RT_PIC_ARM_GIC_MAX_NR 1
#define RT_USING_PIN
#define RT_USING_PINCTRL
#define RT_PINCTRL_SUN50I_H616
#define RT_USING_CLK
#define RT_CLK_SUN50I_H616

/* SoC (System on Chip) Drivers */

#define RT_SOC_SUNXI_G2D
#define RT_SOC_SUNXI_JPEG_DEC
/* end of SoC (System on Chip) Drivers */
/* end of Device Drivers */

/* C/C++ and POSIX layer */

/* ISO-ANSI C layer */

/* Timezone and Daylight Saving Time */

#define RT_LIBC_USING_LIGHT_TZ_DST
#define RT_LIBC_TZ_DEFAULT_HOUR 8
#define RT_LIBC_TZ_DEFAULT_MIN 0
#define RT_LIBC_TZ_DEFAULT_SEC 0
/* end of Timezone and Daylight Saving Time */
/* end of ISO-ANSI C layer */

/* POSIX (Portable Operating System Interface) layer */


/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */

/* end of Interprocess Communication (IPC) */
/* end of POSIX (Portable Operating System Interface) layer */
/* end of C/C++ and POSIX layer */

/* Network */

/* end of Network */

/* Memory protection */

/* end of Memory protection */

/* Utilities */

#define RT_USING_ADT
#define RT_USING_ADT_AVL
#define RT_USING_ADT_BITMAP
#define RT_USING_ADT_HASHMAP
#define RT_USING_ADT_REF
/* end of Utilities */

/* Memory management */

#define RT_PAGE_AFFINITY_BLOCK_SIZE 0x1000
#define RT_PAGE_MAX_ORDER 11
#define RT_USING_MEMBLOCK
#define RT_INIT_MEMORY_REGIONS 128

/* Debugging */

/* end of Debugging */
/* end of Memory management */

/* Using USB legacy version */

/* end of Using USB legacy version */
/* end of RT-Thread Components */

/* RT-Thread Utestcases */

/* end of RT-Thread Utestcases */
#define SOC_H616

#endif
