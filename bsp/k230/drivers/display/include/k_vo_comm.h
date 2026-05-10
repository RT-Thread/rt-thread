#ifndef __K_VO_COMM_H__
#define __K_VO_COMM_H__

#include "k_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Display device / channel constants */
#define K_VO_MAX_DEV_NUMS   (1)
#define K_VO_MAX_CHN_NUMS   (8)
#define K_VO_DISPLAY_DEV_ID (0)

#define K_VO_DEFAULT_MIX_ORDER (0x0000000076543210)

typedef struct {
    k_u32 x;
    k_u32 y;
} k_vo_position;

typedef struct {
    k_u32 width;
    k_u32 height;
} k_vo_size;

struct vo_disp_layer_mix_priority_t {
    union {
        struct {
            k_u64 layer0_sel : 4;
            k_u64 layer1_sel : 4;
            k_u64 layer2_sel : 4;
            k_u64 layer3_sel : 4;
            k_u64 layer4_sel : 4;
            k_u64 layer5_sel : 4;
            k_u64 layer6_sel : 4;
            k_u64 layer7_sel : 4;
            k_u64 layer8_sel : 4;
            k_u64 layer9_sel : 4;
            k_u64 layer10_sel : 4;
            k_u64 layer11_sel : 4;
            k_u64 recv : 16;
        } bits;
        k_u64 reg;
    };
};

/* Display timing parameters */
typedef struct {
    k_u32 pclk_khz;
    k_u32 hactive;
    k_u32 hsync_len;
    k_u32 hback_porch;
    k_u32 hfront_porch;
    k_u32 vactive;
    k_u32 vsync_len;
    k_u32 vback_porch;
    k_u32 vfront_porch;
} k_vo_timing;

/* DSI lane config */
typedef enum {
    K_DSI_1LAN = 0,
    K_DSI_2LAN = 1,
    K_DSI_4LAN = 3,
} k_vo_dsi_lane_num;

typedef enum {
    K_VO_LP_MODE = 0,
    K_VO_HS_MODE,
} k_vo_dsi_cmd_mode;

typedef enum {
    K_BURST_MODE = 0,
    K_NON_BURST_MODE_WITH_SYNC_EVENT = 1,
    K_NON_BURST_MODE_WITH_PULSES = 2,
} k_vo_dsi_video_mode;

typedef struct {
    struct {
        k_u32 datarate;
        k_u32 m, n, voc, hs_freq;
    } phy;

    const k_vo_timing* timing;

    k_vo_dsi_lane_num   lanes;
    k_vo_dsi_cmd_mode   cmd_mode;
    k_vo_dsi_video_mode video_mode;
    k_u8                vc_id;
    k_u8                lp_speed_mhz;
} k_vo_dsi_config;

#ifdef __cplusplus
}
#endif

#endif /* __K_VO_COMM_H__ */
