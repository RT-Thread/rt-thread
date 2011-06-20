To test the ELM FatFs:
1. Please copy "bsp/efm32/copy_this_file_dfs_elm.c" to "components/dfs/filesystems/elmfat/"
2. rename it to "dfs_elm.c" replacing the original file
3. and then compile

Warning:
FatFs is really FAT! (35KB)
You may remove the following defines in "rtconfig.h" to save space:
//#define RT_MEM_DEBUG
//#define THREAD_DEBUG
//#define IRQ_DEBUG

//#define RT_IRQHDL_DEBUG
//#define RT_IIC_DEBUG
//#define RT_MISC_DEBUG
//#define RT_ADC_DEBUG
//#define RT_ACMP_DEBUG
//#define RT_TIMER_DEBUG
//#define RT_RTC_DEBUG

//#define RT_USING_EVENT
//#define RT_USING_MAILBOX
//#define RT_USING_MESSAGEQUEUE
//#define RT_USING_MEMPOOL

//#define RT_USING_IIC0			0x1UL
//#define RT_USING_ACMP0
//#define RT_USING_ADC0
//#define RT_USING_TIMER2			(0x00) 		/* Continuous mode */
//#define RT_USING_RTC
//#define EFM32_USING_SFLASH