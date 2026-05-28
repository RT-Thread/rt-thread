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
void kd_vo_set_background_yuv(k_u32 yuv);
void kd_vo_set_osd_rgb565_framebuffer(k_u32 osd, k_u64 paddr, k_u32 width, k_u32 height, k_u32 pitch);
void kd_vo_set_osd_rgb565_framebuffer_ex(k_u32 osd, k_u64 paddr, k_u64 alpha_paddr,
                                         k_u32 width, k_u32 height, k_u32 pitch,
                                         k_u32 dma_ctrl, k_u32 addr_sel);
void kd_vo_set_osd_rgb565_framebuffer_raw(k_u32 osd, k_u64 paddr, k_u64 alpha_paddr,
                                          k_u32 width, k_u32 height, k_u32 stride_reg,
                                          k_u32 dma_ctrl, k_u32 addr_sel);
void kd_vo_set_osd_rgb565_framebuffer_format_raw(k_u32 osd, k_u64 paddr, k_u64 alpha_paddr,
                                                 k_u32 width, k_u32 height, k_u32 stride_reg,
                                                 k_u32 info, k_u32 dma_ctrl, k_u32 addr_sel);
void kd_vo_select_osd(k_u32 osd);
void kd_vo_disable_osd_all(void);
void kd_vo_commit(void);
void kd_vo_poke(k_u32 offset, k_u32 value);
void kd_vo_enable(void);
void kd_vo_timestamp_enable(void);
void k230_get_timestamp(k_u32 *ptp_time, k_u32 *time);
void kd_vo_debug_dump(void);
void kd_vo_debug_summary(void);

#ifdef __cplusplus
}
#endif

#endif
