/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-25     winner micro
 */

#ifndef DRV_ONESHOT_H__
#define DRV_ONESHOT_H__

typedef enum{
	WM_UDP,
    WM_APSOCKET,
	WM_APWEB
}WM_ONESHOT_MODE;


typedef void (*wm_oneshot_callback)(int state, unsigned char *ssid, unsigned char *key);

extern int wm_oneshot_start(WM_ONESHOT_MODE mode, wm_oneshot_callback callback);
extern int wm_oneshot_stop(void);
extern int wm_oneshot_get(void);

#endif
