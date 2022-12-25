#ifndef __IMG_PORC_H__
#define __IMG_PORC_H__

#include "bl_comm_aaa.h"

#include "ae_algo.h"
#include "awb_algo.h"

#define AE_ENABLE_BIT          (1 << 0)
#define AWB_ENABLE_BIT         (1 << 1)

typedef struct {
    aaa_stats_cfg_t stats_cfg;
} img_proc_cfg_t;

int  imgproc_init(void);
int  imgproc_bind_sensor_model(const char* sensor_name);
int  imgproc_set_config(img_proc_cfg_t *config, bool is_virtual_sensor);
int  imgproc_start(void);
int  imgproc_stop(void);
int  imgproc_update_force(void);
void imgproc_night_mode_enable(bool enable);
void imgproc_dbg_set_awb_algo(AWB_ALGO algo);
void ir_cut_switch(bool enable);


#endif  /* __IMG_PROC_H__ */

