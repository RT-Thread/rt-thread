/*
 *	Debugging macros
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */

#define	DEBUG_SSP_LEVEL3

#ifdef DEBUG_SSP_LEVEL0
#define spi_debug1(...)  
#define spi_debug2(...)  
#define spi_debug3(...)  
#endif
#ifdef DEBUG_SSP_LEVEL1
#define spi_debug1 rt_kprintf
#define spi_debug2 //rt_kprintf
#define spi_debug3 //rt_kprintf
#endif
#ifdef DEBUG_SSP_LEVEL2
#define spi_debug1 rt_kprintf
#define spi_debug2 rt_kprintf
#define spi_debug3 //rt_kprintf
#endif

#ifdef DEBUG_SSP_LEVEL3
#define spi_debug1 rt_kprintf
#define spi_debug2 rt_kprintf
#define spi_debug3 rt_kprintf
#endif
