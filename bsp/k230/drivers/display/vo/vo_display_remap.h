#ifndef VO_DISPLAY_REMAP_H
#define VO_DISPLAY_REMAP_H

#ifdef __cplusplus
extern "C" {
#endif

struct vo_display_remap {
    void *vo_base;
    void *dsi_base;
    void *sysctl_base;
    void *phy_base;
    void *clock_base;
    void *timestamp_base;
};

extern struct vo_display_remap *display_remap;

int vo_display_remap_init(void);
void vo_display_remap_deinit(void);

#ifdef __cplusplus
}
#endif

#endif
