/** @file rtp.h
*   @brief RTP Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#ifndef __RTP_H__
#define __RTP_H__

#include "reg_rtp.h"

/** 
 *  @defgroup RTP RTP
 *  @brief RAM Trace Port.
 *  
 *  RAM Trace Port (RTP) module provides the features to datalog the RAM contents of the devices 
 *  or accesses to peripherals without program intrusion. It can trace all data write or read accesses to internal RAM.
 *
 *	Related Files
 *   - reg_rtp.h
 *   - rtp.h
 *   - rtp.c
 *  @addtogroup RTP
 *  @{
 */
 
/* RTP Interface Functions */
void rtpInit(void);

/**@}*/
#endif
