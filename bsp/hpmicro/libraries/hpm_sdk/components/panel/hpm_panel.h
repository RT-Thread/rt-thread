/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_PANEL_H
#define _HPM_PANEL_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

struct hpm_panel;
typedef struct hpm_panel hpm_panel_t;

typedef struct hpm_panel_timing {
    uint32_t pixel_clock_khz;  /*!< pixel clocl,UINT: KHz */
    uint32_t hactive;          /*!< Horizontal active video */
	uint32_t hfront_porch;     /*!< Horizontal Front Porch */
	uint32_t hback_porch;      /*!< Horizontal Back Porch */
	uint32_t hsync_len;        /*!< Horizontal sync len */

	uint32_t vactive;          /*!< Vertical active video */
	uint32_t vfront_porch;     /*!< Vertical Front Porch */
	uint32_t vback_porch;      /*!< Vertical Back Porch */
	uint32_t vsync_len;        /*!< Vertical sync len */
    uint32_t hsync_pol :1;     /*!< Horizontal Synchronization Signal Polarity, 0: High Active, 1: Low Active */
    uint32_t vsync_pol :1;     /*!< Vertical Synchronization Signal Polarity, 0: High Active, 1: Low Active */
    uint32_t de_pol :1;        /*!< Data Enable Signal Polarity, 0: High Active, 1: Low Active */
    uint32_t pixel_clk_pol :1; /*!< Pixel Clock Signal Polarity, 0: High Active, 1: Low Active */
    uint32_t pixel_data_pol :1;/*!< Pixel Data Signal Polarity, 0: High Active, 1: Low Active */
} hpm_panel_timing_t;

typedef enum hpm_panel_mipi_format {
    HPM_PANEL_MIPI_FORMAT_RGB888,
    HPM_PANEL_MIPI_FORMAT_RGB666,
    HPM_PANEL_MIPI_FORMAT_RGB666_PACKED,
    HPM_PANEL_MIPI_FORMAT_RGB565
} hpm_panel_mipi_format;

typedef struct hpm_panel_hw_interface {
    uint32_t lcdc_pixel_clk_khz;
    void (*set_reset_pin_level)(uint8_t level);
    void (*set_backlight)(uint16_t percent);
    void (*set_video_router)(void);
    union {
        struct {
            hpm_panel_mipi_format format;
            void *mipi_host_base;
            void *mipi_phy_base;
        } mipi;
        struct {
            uint32_t channel_di_index :8;
            uint32_t channel_index :8;
            void *lvb_base;
        } lvds;
    } video;
} hpm_panel_hw_interface_t;

typedef struct hpm_panel_funcs {
    void (*reset)(hpm_panel_t *panel);
    void (*init)(hpm_panel_t *panel);
    void (*power_on)(hpm_panel_t *panel);
    void (*power_off)(hpm_panel_t *panel);
} hpm_panel_funcs_t;

typedef enum hpm_panel_if_type {
    HPM_PANEL_IF_TYPE_RGB,
    HPM_PANEL_IF_TYPE_LVDS_SINGLE,
    HPM_PANEL_IF_TYPE_LVDS_SPLIT,
    HPM_PANEL_IF_TYPE_MIPI,
} hpm_panel_if_type_t;

typedef enum hpm_panel_state_power {
    HPM_PANEL_STATE_POWER_OFF,
    HPM_PANEL_STATE_POWER_ON
} hpm_panel_power_state_t;

typedef struct hpm_panel_state {
    uint8_t backlight_percent;
    uint8_t power_state;
} hpm_panel_state_t;

struct hpm_panel {
    const char *name;
    hpm_panel_if_type_t if_type;
    const hpm_panel_timing_t timing;
    hpm_panel_state_t state;
    hpm_panel_hw_interface_t hw_if;
    hpm_panel_funcs_t funcs;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find default panel
 *
 * @return pointer of panel instance
 */
hpm_panel_t *hpm_panel_find_device_default(void);

/**
 * @brief Find panel for name
 *
 * @param [in] name of panel
 *
 * @return pointer of panel instance
 */
hpm_panel_t *hpm_panel_find_device(const char *name);

/**
 * @brief Get panel name
 *
 * @param panel pointer of panel instance
 *
 * @return panel name
 */
const char *hpm_panel_get_name(hpm_panel_t *panel);

/**
 * @brief Get panel timing
 *
 * @param panel pointer of panel instance
 *
 * @return pointer of timing
 */
const hpm_panel_timing_t *hpm_panel_get_timing(hpm_panel_t *panel);

/**
 * @brief Get panel interface type
 *
 * @param [in] panel pointer of panel instance
 *
 * @return panel interface type @ref hpm_panel_if_type_t
 */
hpm_panel_if_type_t hpm_panel_get_if_type(hpm_panel_t *panel);

/**
 * @brief Register platform level hardware interface
 *
 * @param [in] panel pointer of panel instance
 * @param [in] hw_if pointer of hardware interface
 */
void hpm_panel_register_interface(hpm_panel_t *panel, hpm_panel_hw_interface_t *hw_if);

/**
 * @brief Reset the panel
 *
 * @param [in] panel pointer of panel instance
 */
void hpm_panel_reset(hpm_panel_t *panel);

/**
 * @brief Initialize the panel
 *
 * @param [in] panel pointer of panel instance
 */
void hpm_panel_init(hpm_panel_t *panel);

/**
 * @brief Power on the panel
 *
 * @param [in] panel pointer of panel instance
 */
void hpm_panel_power_on(hpm_panel_t *panel);

/**
 * @brief Power off the panel
 *
 * @param [in] panel pointer of panel instance
 */
void hpm_panel_power_off(hpm_panel_t *panel);

/**
 * @brief Set backlight value
 *
 * @param [in] panel pointer of panel instance
 * @param [in] percent percent of backlight [0 - 100]
 */
void hpm_panel_set_backlight(hpm_panel_t *panel, uint16_t percent);

/**
 *
 * @brief Get backlight value
 *
 * @param [in] panel pointer of panel instance
 * @return percent of backlight [0 - 100]
 */
uint8_t hpm_panel_get_backlight(hpm_panel_t *panel);

/**
 * @brief Delay specified milliseconds
 *
 * @param [in] ms expected delay interval in milliseconds
 */
void hpm_panel_delay_ms(uint32_t ms);

/**
 * @brief Delay specified microseconds
 *
 * @param [in] us expected delay interval in microseconds
 */
void hpm_panel_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* _HPM_PANEL_H */