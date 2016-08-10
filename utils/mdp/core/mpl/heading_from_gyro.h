/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/******************************************************************************
 *
 * $Id$
 *
 *****************************************************************************/

#ifndef _HEADING_FROM_GYRO_H_
#define _HEADING_FROM_GYRO_H_
#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

    inv_error_t inv_enable_heading_from_gyro(void);
    inv_error_t inv_disable_heading_from_gyro(void);
    void inv_init_heading_from_gyro(void);
    inv_error_t inv_start_heading_from_gyro(void);
    inv_error_t inv_stop_heading_from_gyro(void);

#ifdef __cplusplus
}
#endif


#endif  /* _HEADING_FROM_GYRO_H_ */