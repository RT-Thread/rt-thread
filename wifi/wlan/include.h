/** @file include.h
 * 
 * @brief This file contains all the necessary include file.
 *  
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
 */
/********************************************************
Change log:
	10/11/05: Add Doxygen format comments
	01/11/06: Conditional include file removal/addition
	01/30/06: Add kernel 2.6 support
	
********************************************************/

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include    "..\os\os_headers.h"
#include	"wlan_debug.h"
#include    "wlan_types.h"
#include    "wlan_defs.h"
#include    "wlan_thread.h"	   //dennis

#include    "wlan_wmm.h"
#include    "wlan_11d.h"



#include    "host.h"
#include    "hostcmd.h"

#include    "wlan_scan.h"
#include    "wlan_join.h"

#include    "wlan_dev.h"


#include    "sbi.h"

#include    "..\spi\gspi_io.h"

#include    "wlan_wext.h"
#include    "wlan_decl.h"
#endif /* _INCLUDE_H_ */
