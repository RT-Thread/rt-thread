#ifndef __K_CONNECTOR_COMM_H__
#define __K_CONNECTOR_COMM_H__

#include "k_type.h"
#include "k_vo_comm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Connector chip identifier */
typedef enum {
    K_CHIP_VIRTUAL  = 0,
    K_CHIP_HX8399   = 1,
    K_CHIP_ILI9806  = 2,
    K_CHIP_ILI9881  = 3,
    K_CHIP_NT35516  = 4,
    K_CHIP_NT35532  = 5,
    K_CHIP_GC9503   = 6,
    K_CHIP_ST7102   = 7,
    K_CHIP_AML020T  = 8,
    K_CHIP_ST7701   = 9,
    K_CHIP_JD9852   = 10,
    K_CHIP_LT9611   = 11,
    K_CHIP_ST7789   = 12,
    K_CHIP_NV3030B  = 13,
} k_connector_chip;

/** Connector bus type */
typedef enum {
    K_BUS_DSI        = 0,
    K_BUS_HDMI       = 1,
    K_BUS_SPI        = 2,
} k_connector_bus;

/*
 * k_connector_type encoding (32-bit):
 *   [31:26] chip    (6 bits)
 *   [25:24] bus     (2 bits)
 *   [23:20] version (4 bits)
 *   [19:10] width   (10 bits)  — h >> 1
 *    [9:0]  height  (10 bits)  — v >> 1
 */
#define _CONN_CHIP_BITS   6
#define _CONN_BUS_BITS    2
#define _CONN_VER_BITS    4
#define _CONN_W_BITS      10
#define _CONN_H_BITS      10

#define _CONN_H_SHIFT     0
#define _CONN_W_SHIFT     10
#define _CONN_VER_SHIFT   20
#define _CONN_BUS_SHIFT   24
#define _CONN_CHIP_SHIFT  26

#define _CONN_MASK(bits)  ((1U << (bits)) - 1)

#define K_CONN_TYPE(chip, bus, w, h, ver)                                       \
    ((k_u32)                                                                    \
     ((((k_u32)(chip) & _CONN_MASK(_CONN_CHIP_BITS)) << _CONN_CHIP_SHIFT) |    \
      (((k_u32)(bus)  & _CONN_MASK(_CONN_BUS_BITS))  << _CONN_BUS_SHIFT)  |    \
      (((k_u32)(ver)  & _CONN_MASK(_CONN_VER_BITS))  << _CONN_VER_SHIFT)  |    \
      (((k_u32)((w) >> 1) & _CONN_MASK(_CONN_W_BITS)) << _CONN_W_SHIFT)   |    \
      (((k_u32)((h) >> 1) & _CONN_MASK(_CONN_H_BITS)) << _CONN_H_SHIFT)))

#define K_CONN_CHIP(type)    ((k_connector_chip)(((type) >> _CONN_CHIP_SHIFT) & _CONN_MASK(_CONN_CHIP_BITS)))
#define K_CONN_BUS(type)     ((k_connector_bus)(((type) >> _CONN_BUS_SHIFT) & _CONN_MASK(_CONN_BUS_BITS)))
#define K_CONN_VER(type)     (((type) >> _CONN_VER_SHIFT) & _CONN_MASK(_CONN_VER_BITS))
#define K_CONN_WIDTH(type)   ((((type) >> _CONN_W_SHIFT) & _CONN_MASK(_CONN_W_BITS)) << 1)
#define K_CONN_HEIGHT(type)  ((((type) >> _CONN_H_SHIFT) & _CONN_MASK(_CONN_H_BITS)) << 1)

typedef k_u32 k_connector_type;

/* ST7701 variants */
#define ST7701_480_800_DSI_V1       K_CONN_TYPE(K_CHIP_ST7701,   K_BUS_DSI,  480,  800, 1)
#define ST7701_480_854_DSI_V1       K_CONN_TYPE(K_CHIP_ST7701,   K_BUS_DSI,  480,  854, 1)
#define ST7701_480_640_DSI_V1       K_CONN_TYPE(K_CHIP_ST7701,   K_BUS_DSI,  480,  640, 1)
#define ST7701_368_544_DSI_V1       K_CONN_TYPE(K_CHIP_ST7701,   K_BUS_DSI,  368,  544, 1)

#define CONNECTOR_BUTT              ((k_u32)0xFFFFFFFF)

typedef enum {
    K_CONNECTOR_BL_MODE_OFF = 0,
    K_CONNECTOR_BL_MODE_ON = 1,
    K_CONNECTOR_BL_MODE_PWM = 2,
} k_connector_backlight_mode;

typedef struct {
    k_connector_backlight_mode mode;
    k_u32 duty;
} k_connector_backlight_attr;

typedef struct {
    char connector_name[32];
    k_connector_type type;
    union {
        k_vo_timing timing;
        k_vo_timing resolution;
    };
    k_u32 bg_color;
} k_connector_info;

typedef struct {
    k_u8 cmd_type;
    k_u8 cmd_delay;
    k_u8 cmd_size;
    k_u8 cmd_data[0];
} k_connector_cmd_slice;

#define CONNECTOR_CMD_SEQUENCE(type, delay, ...)                               \
    (type), (delay), sizeof((k_u8[]) { __VA_ARGS__ }) / sizeof(k_u8), __VA_ARGS__

#ifdef __cplusplus
}
#endif

#endif /* __K_CONNECTOR_COMM_H__ */
