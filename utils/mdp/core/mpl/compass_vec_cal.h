/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/*******************************************************************************
 *
 * $Id:$
 *
 ******************************************************************************/

#ifndef COMPASS_ONLY_CAL_H__
#define COMPASS_ONLY_CAL_H__

#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

inv_error_t inv_enable_vector_compass_cal(void);
inv_error_t inv_disable_vector_compass_cal(void);
inv_error_t inv_start_vector_compass_cal(void);
inv_error_t inv_stop_vector_compass_cal(void);
void inv_vector_compass_cal_sensitivity(float sens);
inv_error_t inv_init_vector_compass_cal(void);

#ifdef __cplusplus
}
#endif

#endif // COMPASS_ONLY_CAL_H__

