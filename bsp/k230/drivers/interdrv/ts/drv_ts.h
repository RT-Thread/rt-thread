
#ifndef __DRV_TS__
#define __DRV_TS__

#include <rtdef.h>

#define RT_DEVICE_TS_CTRL_SET_MODE          1
#define RT_DEVICE_TS_CTRL_GET_MODE          2
#define RT_DEVICE_TS_CTRL_SET_TRIM          3
#define RT_DEVICE_TS_CTRL_GET_TRIM          4

#define RT_DEVICE_TS_CTRL_MODE_SINGLE       0x01
#define RT_DEVICE_TS_CTRL_MODE_CONTINUUOS   0x02

#endif /*__DRV_TS__*/