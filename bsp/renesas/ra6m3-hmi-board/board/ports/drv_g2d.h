#ifndef __DRV_G2D_H__
#define __DRV_G2D_H__

#include <rtthread.h>
#include "hal_data.h"

int G2d_Drv_HWInit(void);

#ifdef PKG_USING_LVGL
#include "lvgl.h"
void lv_port_gpu_blit(int32_t      x,
                      int32_t      y,
                      const void  *p,
                      const lv_area_t *area);
#endif
#endif
