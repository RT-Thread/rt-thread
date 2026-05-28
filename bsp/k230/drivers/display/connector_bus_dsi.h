#ifndef _CONNECTOR_BUS_DSI_H_
#define _CONNECTOR_BUS_DSI_H_

#include <stdint.h>
#include <stdbool.h>

#include "k_vo_comm.h"

#ifdef __cplusplus
extern "C" {
#endif

struct panel_desc;

/* MIPI DSI DCS Command Types */
#define DSI_DCS_SHORT_WRITE       0x05
#define DSI_DCS_SHORT_WRITE_PARAM 0x15
#define DSI_DCS_LONG_WRITE        0x39

/* MIPI DSI Generic Command Types */
#define DSI_GENERIC_SHORT_WRITE_0_PARAM 0x03
#define DSI_GENERIC_SHORT_WRITE_1_PARAM 0x13
#define DSI_GENERIC_SHORT_WRITE_2_PARAM 0x23
#define DSI_GENERIC_LONG_WRITE          0x29

k_s32 dsi_send_cmd_sequence(const struct panel_desc* desc, const k_u8* cmd_seq,
                             size_t cmd_size, k_bool dump);
k_u32 dsi_read_chip_id(const struct panel_desc* desc);
k_u32 dsi_correct_pclk(k_u32 pclk_hz, k_vo_dsi_lane_num lanes);

/* DWC DSI controller HAL implemented by display/vo. */
void dwc_dsi_init(k_vo_dsi_config* cfg);
int  dwc_dsi_enable(void);
int  dwc_dsi_disable(void);
int  dwc_dsi_send_packet(uint8_t type, uint8_t vc, const void* data,
                          uint32_t len, uint8_t req_ack);
int  dwc_dsi_dcs_write(const void* data, uint32_t len, uint8_t vc);
int  dwc_dsi_dcs_read(uint8_t addr, void* buf, uint32_t len, uint8_t vc);
int  dwc_dsi_generic_write(const void* data, uint32_t len, uint8_t vc);
int  dwc_dsi_generic_read(const void* cmd, uint32_t cmd_len,
                          void* buf, uint32_t len, uint8_t vc);
void dwc_dsi_dump_reg_val(void);

#ifdef __cplusplus
}
#endif

#endif /* _CONNECTOR_BUS_DSI_H_ */
