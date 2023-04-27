#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include <rtdevice.h>

#ifdef RT_USING_CAN

#include "fcan.h"

#ifdef __cplusplus
extern "C"
{
#endif

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif
#endif /* __DRV_CAN_H__ */