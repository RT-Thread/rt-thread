/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/*******************************************************************************
 *
 * $Id$
 *
 ******************************************************************************/

#ifndef MLDMP_ACCEL_AUTO_CALIBRATION_H__
#define MLDMP_ACCEL_AUTO_CALIBRATION_H__

#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

inv_error_t inv_enable_in_use_auto_calibration(void);
inv_error_t inv_disable_in_use_auto_calibration(void);
inv_error_t inv_stop_in_use_auto_calibration(void);
inv_error_t inv_start_in_use_auto_calibration(void);
inv_error_t inv_in_use_auto_calibration_is_enabled(unsigned char *is_enabled);
inv_error_t inv_init_in_use_auto_calibration(void);
void inv_init_accel_maxmin(void);
void inv_record_good_accel_maxmin(void);
int inv_get_accel_bias_stage(void);

#ifdef __cplusplus
}
#endif

#endif // MLDMP_ACCEL_AUTO_CALIBRATION_H__

