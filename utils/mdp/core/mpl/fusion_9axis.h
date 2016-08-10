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

#ifndef MLDMP_FUSION9AXIS_H__
#define MLDMP_FUSION9AXIS_H__

#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

    void inv_init_9x_fusion(void);
    inv_error_t inv_9x_fusion_state_change(unsigned char newState);
    inv_error_t inv_enable_9x_sensor_fusion(void);
    inv_error_t inv_disable_9x_sensor_fusion(void);
    inv_error_t inv_start_9x_sensor_fusion(void);
    inv_error_t inv_stop_9x_sensor_fusion(void);
    inv_error_t inv_9x_fusion_set_mag_fb(float fb);
    inv_error_t inv_9x_fusion_enable_jitter_reduction(int en);
    inv_error_t inv_9x_fusion_use_timestamps(int en);

#ifdef __cplusplus
}
#endif


#endif // MLDMP_FUSION9AXIS_H__