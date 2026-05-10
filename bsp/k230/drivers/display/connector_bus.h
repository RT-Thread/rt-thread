#ifndef _CONNECTOR_BUS_H_
#define _CONNECTOR_BUS_H_

#include "connector_bus_dsi.h"
#include "k_type.h"

#ifdef __cplusplus
extern "C" {
#endif

struct panel_desc;

enum panel_bus_type {
    PANEL_BUS_DSI,
    PANEL_BUS_SPI,
    PANEL_BUS_I8080_SPI,
    PANEL_BUS_QSPI,
    PANEL_BUS_NONE,
};

struct panel_bus_ops {
    int (*init)(const struct panel_desc* desc);
    int (*enable)(const struct panel_desc* desc);
    int (*disable)(const struct panel_desc* desc);
    int (*send_cmd)(const struct panel_desc* desc, k_u8 cmd,
                     const k_u8* data, k_u32 len);
    int (*send_frame)(const struct panel_desc* desc, void* data, k_u32 size);
};

extern const struct panel_bus_ops dsi_bus_ops;

#ifdef __cplusplus
}
#endif

#endif /* _CONNECTOR_BUS_H_ */
