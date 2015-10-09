/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
#ifndef INV_QUATERNION_SUPERVISOR_H__
#define INV_QUATERNION_SUPERVISOR_H__

#include "mltypes.h"


#ifdef __cplusplus
extern "C" {
#endif

inv_error_t inv_enable_quaternion(void);
inv_error_t inv_disable_quaternion(void);
inv_error_t inv_init_quaternion(void);
inv_error_t inv_start_quaternion(void);
void inv_set_quaternion(long *quat);

#ifdef __cplusplus
}
#endif

#endif // INV_QUATERNION_SUPERVISOR_H__