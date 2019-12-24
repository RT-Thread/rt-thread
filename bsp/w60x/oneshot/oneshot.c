/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-25     winner micro
 */

#include <rtthread.h>
#include "oneshot.h"
#include "wm_wifi_oneshot.h"
#include "wm_wifi.h"

/* start oneshot */
int wm_oneshot_start(WM_ONESHOT_MODE mode, wm_oneshot_callback callback)
{
	tls_wifi_oneshot_callback_register(callback);
	if(mode == WM_UDP)
	{
		tls_wifi_set_oneshot_config_mode(0);
	}
    else if (mode == WM_APSOCKET)
    {
        tls_wifi_set_oneshot_config_mode(1);
	}
	else if(mode == WM_APWEB)
	{
		tls_wifi_set_oneshot_config_mode(2);
	}
	else
	{
		return -1;
	}
	tls_wifi_set_oneshot_flag(1);
	return 0;
}

/* stop oneshot */
int wm_oneshot_stop(void)
{
	tls_wifi_oneshot_callback_delete();
	tls_wifi_set_oneshot_flag(0);
	return 0;
}

/* get status */
int wm_oneshot_get(void)
{
	return tls_wifi_get_oneshot_flag();
}
