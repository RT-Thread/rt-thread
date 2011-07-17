/** @file if_gspi.h
 *  @brief This file contains MSU registers definition
 * 
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/********************************************************
Change log:
	09/26/05: Add Doxygen format comments
	
********************************************************/

#ifndef __IF_GSPI_DEBUG_H_
#define __IF_GSPI_DEBUG_H_
#define DEBUG_IF_SSP_LEVEL3
#ifdef DEBUG_IF_SSP_LEVEL0
#define ifspi_debug1(...)
#define ifspi_debug2(...) 
#define ifspi_debug3(...) 
#endif
#ifdef DEBUG_IF_SSP_LEVEL1
#define ifspi_debug1(a...) rt_kprintf(a)
#define ifspi_debug2(a...) do{}while(0)
#define ifspi_debug3(a...) do{}while(0)
#endif

#ifdef DEBUG_IF_SSP_LEVEL2
#define ifspi_debug1(a...) rt_kprintf(a)
#define ifspi_debug2(a...) rt_kprintf(a)
#define ifspi_debug3(a...) do{}while(0)
#endif

#ifdef DEBUG_IF_SSP_LEVEL3
#define ifspi_debug1(a...) rt_kprintf(a)
#define ifspi_debug2(a...) rt_kprintf(a)
#define ifspi_debug3(a...) rt_kprintf(a)
#endif

#endif /* __GSPIREG_H_ */
