#ifndef VO_KD_VO_REG_H
#define VO_KD_VO_REG_H

#include "k_vo_comm.h"

#ifdef __cplusplus
extern "C" {
#endif

void kd_vo_reset(void);
void kd_vo_wrap_init(void);
void kd_vo_set_config_mix(void);
void kd_vo_set_frame_intr(k_bool status);
void kd_vo_set_vtth_intr(k_u32 status, k_u32 line);
void kd_vo_set_pixclk(k_u32 div);
void kd_vo_set_timing(const k_vo_timing *timing);
void kd_vo_set_background(k_u32 rgb888);
void kd_vo_enable(void);
void kd_vo_timestamp_enable(void);
void k230_get_timestamp(k_u32 *ptp_time, k_u32 *time);

#ifdef __cplusplus
}
#endif

#endif
