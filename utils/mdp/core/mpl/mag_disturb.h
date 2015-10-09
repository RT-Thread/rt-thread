/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

#ifndef MLDMP_MAGDISTURB_H__
#define MLDMP_MAGDISTURB_H__

#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

    int inv_check_magnetic_disturbance(unsigned long delta_time, const long *quat,
        const long *compass, const long *gravity);

    void inv_track_dip_angle(int mode, float currdip);

    inv_error_t inv_enable_magnetic_disturbance(void);
    inv_error_t inv_disable_magnetic_disturbance(void);
    int inv_get_magnetic_disturbance_state(void);
    inv_error_t inv_set_magnetic_disturbance(int time_ms);
    inv_error_t inv_disable_dip_tracking(void);
    inv_error_t inv_enable_dip_tracking(void);
    inv_error_t inv_init_magnetic_disturbance(void);

    float Mag3ofNormalizedLong(const long *x);

#ifdef __cplusplus
}
#endif


#endif // MLDMP_MAGDISTURB_H__