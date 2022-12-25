#ifndef __WDR_FIRMWARE_H__
#define __WDR_FIRMWARE_H__

#include <img_param.h>
#include "bl_comm_sns.h"
#include "bl_comm_aaa.h"

typedef struct {
    aaa_stats_cfg_t stats_cfg;
} wdr_config_t;

int  wdr_init();
int  wdr_config(wdr_config_t *config, bool is_virtual_sensor);
int  wdr_control(wdr_fw_config_t *config);
void wdr_hw_update(void);

#endif
