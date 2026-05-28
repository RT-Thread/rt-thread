#ifndef VO_KD_DSI_REG_H
#define VO_KD_DSI_REG_H

#include "k_vo_comm.h"

#ifdef __cplusplus
extern "C" {
#endif

void k230_dsi_write_phy_reg(k_u8 addr, k_u8 value);
void k230_dsi_phy_pll_config(k_u32 m, k_u32 n, k_u8 voc);
void k230_dsi_phy0_config(k_u32 m, k_u32 n, k_u8 voc, k_u8 hs_freq);
void k230_dsi_phy1_config(k_u8 hs_freq);
void k230_dsi_phy_config(k_u32 lane_num, k_u32 m, k_u32 n, k_u8 voc,
                         k_u8 hs_freq);

int dwc_dsi_send_packet(k_u8 type, k_u8 channel, const void *payload,
                        k_u32 payload_len, k_u8 read);
int dwc_dsi_dcs_write(const void *data, k_u32 len, k_u8 channel);
int dwc_dsi_dcs_read(k_u8 cmd, void *data, k_u32 len, k_u8 channel);
int dwc_dsi_generic_write(const void *data, k_u32 len, k_u8 channel);
int dwc_dsi_generic_read(const void *params, k_u32 params_len, void *data,
                         k_u32 len, k_u8 channel);

void dwc_dsi_init(k_vo_dsi_config *config);
int dwc_dsi_enable(void);
int dwc_dsi_disable(void);
void dwc_dsi_dump_config(const k_vo_dsi_config *config);
void dwc_dsi_debug_dump(void);
void dwc_dsi_set_dpi_color_coding(k_u32 coding);
void dwc_dsi_set_video_scan(k_u32 dpi_color, k_u32 pkt_size,
                            k_u32 hsa, k_u32 hbp, k_u32 hline,
                            k_u32 video_mode);

#ifdef __cplusplus
}
#endif

#endif
