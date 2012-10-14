#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_405EP		1	/* this is a PPC405 CPU */
#define CONFIG_4xx		1	/*  member of PPC4xx family */

#define CONFIG_SYS_DCACHE_SIZE	(16 << 10)/* For AMCC 405 CPUs	*/
#define CONFIG_SYS_SDRAM_BASE	0x00000000	/* _must_ be 0		*/

#define CONFIG_SYS_CBSIZE	256	/* Console I/O Buffer Size	*/
#define CONFIG_SYS_PROMPT	"=> "	/* Monitor Command Prompt	*/
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)

#define CONFIG_SYS_CLK_RECFG	0	/* Config the sys clks */
#define CONFIG_SYS_CLK_FREQ     33333333 /*3300000*//* external frequency to pll   */
#define CONFIG_SYS_HZ           100
#define CONFIG_SYS_PIT_RELOAD   (CONFIG_SYS_CLK_FREQ / CONFIG_SYS_HZ)  

/*
 * UART
 */
#define CONFIG_BAUDRATE		115200
#define CONFIG_SERIAL_MULTI
#define CONFIG_SYS_BAUDRATE_TABLE  \
    {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}

/*
 * If CONFIG_SYS_EXT_SERIAL_CLOCK, then the UART divisor is 1.
 * If CONFIG_SYS_405_UART_ERRATA_59, then UART divisor is 31.
 * Otherwise, UART divisor is determined by CPU Clock and CONFIG_SYS_BASE_BAUD value.
 * The Linux BASE_BAUD define should match this configuration.
 *    baseBaud = cpuClock/(uartDivisor*16)
 * If CONFIG_SYS_405_UART_ERRATA_59 and 200MHz CPU clock,
 * set Linux BASE_BAUD to 403200.
 */
#define CONFIG_SYS_BASE_BAUD		691200
#define CONFIG_UART1_CONSOLE		1

/*-----------------------------------------------------------------------
 * Start addresses for the final memory configuration
 * (Set up by the startup code)
 */
#define CONFIG_SYS_FLASH_BASE		0xFFE00000

/*-----------------------------------------------------------------------
 * FLASH organization
 */
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#define CONFIG_SYS_MAX_FLASH_SECT	256	/* max number of sectors on one chip	*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write (in ms)	*/

#define CONFIG_SYS_FLASH_ADDR0         0x555
#define CONFIG_SYS_FLASH_ADDR1         0x2aa
#define CONFIG_SYS_FLASH_WORD_SIZE     unsigned short

#endif	/* __CONFIG_H */
