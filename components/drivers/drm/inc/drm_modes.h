#ifndef _DRM_DRM_MODES_H_
#define _DRM_DRM_MODES_H_


#include "drm_mode.h"

struct drm_connector;
struct drm_display_mode;
struct drm_mode_modeinfo;


enum drm_mode_status {
    MODE_OK = 0,
    MODE_HSYNC,
    MODE_VSYNC,
    MODE_H_ILLEGAL,
    MODE_V_ILLEGAL,
    MODE_BAD_WIDTH,
    MODE_NOMODE,
    MODE_NO_INTERLACE,
    MODE_NO_DBLESCAN,
    MODE_NO_VSCAN,
    MODE_MEM,
    MODE_VIRTUAL_X,
    MODE_VIRTUAL_Y,
    MODE_MEM_VIRT,
    MODE_NOCLOCK,
    MODE_CLOCK_HIGH,
    MODE_CLOCK_LOW,
    MODE_CLOCK_RANGE,
    MODE_BAD_HVALUE,
    MODE_BAD_VVALUE,
    MODE_BAD_VSCAN,
    MODE_HSYNC_NARROW,
    MODE_HSYNC_WIDE,
    MODE_HBLANK_NARROW,
    MODE_HBLANK_WIDE,
    MODE_VSYNC_NARROW,
    MODE_VSYNC_WIDE,
    MODE_VBLANK_NARROW,
    MODE_VBLANK_WIDE,
    MODE_PANEL,
    MODE_INTERLACE_WIDTH,
    MODE_ONE_WIDTH,
    MODE_ONE_HEIGHT,
    MODE_ONE_SIZE,
    MODE_NO_REDUCED,
    MODE_NO_STEREO,
    MODE_NO_420,
    MODE_STALE = -3,
    MODE_BAD = -2,
    MODE_ERROR = -1
};

struct drm_display_mode {
    rt_list_t head;

    char name[DRM_DISPLAY_MODE_LEN];
    enum drm_mode_status status;
    unsigned int type;

    int clock; /* in kHz */
    int hdisplay;
    int hsync_start;
    int hsync_end;
    int htotal;
    int hskew;
    int vdisplay;
    int vsync_start;
    int vsync_end;
    int vtotal;
    int vscan;
    unsigned int flags;

    int width_mm;
    int height_mm;

    int vrefresh;
};

void drm_mode_copy(struct drm_display_mode* dst,
                   const struct drm_display_mode* src);

int drm_add_dmt_modes(struct drm_connector* connector, int hdisplay,
                      int vdisplay);

int drm_mode_convert_umode(struct drm_display_mode* out,
                           const struct drm_mode_modeinfo* in);
void drm_mode_convert_to_umode(struct drm_mode_modeinfo* out,
                               const struct drm_display_mode* in);

void drm_set_preferred_mode(struct drm_connector* connector, int hpref,
                            int vpref);

#endif
