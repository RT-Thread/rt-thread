/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-08     CYFS         implement the board dashboard for peripherals, storage, camera, and MQTT
 */

#include <rtconfig.h>

#if defined(PKG_USING_LVGL) && defined(BSP_USING_LVGL_BOARD_DEMO)

#include <lvgl.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <stdlib.h>

#include "board_demo_backend.h"

#ifdef BSP_USING_OV7670_PREVIEW
#include "ov7670_preview.h"
#endif

#define DBG_TAG                         "app.board.demo"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

#ifndef BSP_GD32VW553_MQTT_HOST
#define BSP_GD32VW553_MQTT_HOST         "broker.emqx.io"
#endif

#ifndef BSP_GD32VW553_MQTT_SUB_TOPIC
#define BSP_GD32VW553_MQTT_SUB_TOPIC    "rtt/gd32vw553/sub"
#endif

#ifndef BSP_GD32VW553_MQTT_PUB_TOPIC
#define BSP_GD32VW553_MQTT_PUB_TOPIC    "rtt/gd32vw553/pub"
#endif

#define BOARD_DEMO_WIDTH                720
#define BOARD_DEMO_HEIGHT               720
#define BOARD_DEMO_SIDEBAR_WIDTH        132
#define BOARD_DEMO_HEADER_HEIGHT        64
#define BOARD_DEMO_CONTENT_WIDTH        (BOARD_DEMO_WIDTH - BOARD_DEMO_SIDEBAR_WIDTH)
#define BOARD_DEMO_CONTENT_HEIGHT       (BOARD_DEMO_HEIGHT - BOARD_DEMO_HEADER_HEIGHT)
#define BOARD_DEMO_PAGE_INNER_WIDTH     (BOARD_DEMO_CONTENT_WIDTH - 32)
#define BOARD_DEMO_REFRESH_MS           150U
#define BOARD_DEMO_STORAGE_POLL_MS      1000U
#define BOARD_DEMO_KEYBOARD_HEIGHT      260
#define BOARD_DEMO_LCD_DEVICE_NAME      "lcd"

#define COLOR_NAV                       lv_color_hex(0x242A2D)
#define COLOR_NAV_ACTIVE                lv_color_hex(0x365B56)
#define COLOR_PAGE                      lv_color_hex(0xF1F4F5)
#define COLOR_SURFACE                   lv_color_hex(0xFFFFFF)
#define COLOR_TEXT                      lv_color_hex(0x1F2933)
#define COLOR_MUTED                     lv_color_hex(0x64727D)
#define COLOR_BORDER                    lv_color_hex(0xD6DEE2)
#define COLOR_ACCENT                    lv_color_hex(0x0F766E)
#define COLOR_INFO                      lv_color_hex(0x2563A6)
#define COLOR_ACCENT_SOFT               lv_color_hex(0xE1F0EB)
#define COLOR_WARNING                   lv_color_hex(0xB45309)
#define COLOR_DANGER                    lv_color_hex(0xB42318)

enum board_demo_page_id
{
    BOARD_DEMO_PAGE_OVERVIEW = 0,
    BOARD_DEMO_PAGE_FILES,
    BOARD_DEMO_PAGE_CAN,
    BOARD_DEMO_PAGE_MQTT,
    BOARD_DEMO_PAGE_PWM,
    BOARD_DEMO_PAGE_CAMERA,
    BOARD_DEMO_PAGE_SPI,
    BOARD_DEMO_PAGE_I2C,
    BOARD_DEMO_PAGE_COUNT,
};

static const char *const board_demo_page_names[BOARD_DEMO_PAGE_COUNT] =
{
    "Overview", "Files", "CAN", "MQTT",
    "PWM", "Camera", "SPI", "I2C",
};

static const char *const board_demo_page_symbols[BOARD_DEMO_PAGE_COUNT] =
{
    LV_SYMBOL_HOME, LV_SYMBOL_DIRECTORY, LV_SYMBOL_LOOP, LV_SYMBOL_WIFI,
    LV_SYMBOL_SETTINGS, LV_SYMBOL_IMAGE, LV_SYMBOL_SHUFFLE, LV_SYMBOL_LIST,
};

static lv_obj_t *demo_screen;
static lv_obj_t *demo_pages[BOARD_DEMO_PAGE_COUNT];
static lv_obj_t *demo_nav_buttons[BOARD_DEMO_PAGE_COUNT];
static lv_obj_t *demo_header_title;
static lv_obj_t *demo_header_status;
static lv_obj_t *demo_keyboard;
static lv_timer_t *demo_refresh_timer;
static enum board_demo_page_id demo_active_page;

static lv_obj_t *overview_status[BOARD_DEMO_PAGE_COUNT];
static lv_obj_t *overview_uptime;

static lv_obj_t *files_source_buttons[BOARD_DEMO_STORAGE_COUNT];
static lv_obj_t *files_source_status[BOARD_DEMO_STORAGE_COUNT];
static lv_obj_t *files_up_button;
static lv_obj_t *files_path_label;
static lv_obj_t *files_status_label;
static lv_obj_t *files_table;
static lv_obj_t *files_empty_label;
static lv_obj_t *files_preview_title;
static lv_obj_t *files_preview_panel;
static lv_obj_t *files_preview_label;

static lv_obj_t *can_status_label;
static lv_obj_t *can_baud_dropdown;
static lv_obj_t *can_id_textarea;
static lv_obj_t *can_data_textarea;
static lv_obj_t *can_extended_switch;
static lv_obj_t *can_table;

static lv_obj_t *mqtt_status_label;
static lv_obj_t *mqtt_topic_textarea;
static lv_obj_t *mqtt_payload_textarea;
static lv_obj_t *mqtt_rx_topic_label;
static lv_obj_t *mqtt_rx_payload_label;

static lv_obj_t *pwm_status_label;
static lv_obj_t *brightness_slider;
static lv_obj_t *brightness_value_label;
static lv_obj_t *pwm_frequency_dropdown;
static lv_obj_t *pwm2_switch;
static lv_obj_t *pwm2_slider;
static lv_obj_t *pwm2_value_label;
static lv_obj_t *pwm30_switch;
static lv_obj_t *pwm30_slider;
static lv_obj_t *pwm30_value_label;

static lv_obj_t *camera_status_label;
static lv_obj_t *camera_counter_label;

static lv_obj_t *spi_status_label;
static lv_obj_t *spi_frequency_dropdown;
static lv_obj_t *spi_length_dropdown;
static lv_obj_t *spi_run_button;
static lv_obj_t *spi_log_label;

static lv_obj_t *i2c_status_label;
static lv_obj_t *i2c_result_table;
static lv_obj_t *i2c_scan_button;
static lv_obj_t *i2c_log_label;

static rt_device_t board_demo_lcd_device;

static struct board_demo_snapshot demo_snapshot;
static rt_uint32_t files_sequence;
static rt_uint32_t file_sequence;
static rt_uint32_t can_sequence;
static rt_uint32_t mqtt_sequence;
static rt_uint32_t pwm_sequence;
static rt_uint32_t spi_sequence;
static rt_uint32_t i2c_sequence;
static rt_uint8_t storage_mounts;
static rt_uint32_t storage_poll_tick;
static rt_bool_t storage_polled;

static void board_demo_show_page(enum board_demo_page_id page_id);
static void board_demo_update_files(void);
static void board_demo_update_storage(void);
static void board_demo_update_runtime(void);

static void board_demo_files_request_path(const char *path)
{
    char status[64];
    int result;

    lv_label_set_text(files_path_label, path);
    lv_label_set_text(files_status_label, "Loading...");
    result = board_demo_request_fs_list(path);
    if (result == RT_EOK)
    {
        result = board_demo_backend_get_snapshot(&demo_snapshot);
        if (result == RT_EOK)
        {
            board_demo_update_files();
            LOG_I("storage list completed: %s", path);
        }
        else
        {
            lv_label_set_text(files_status_label, "Storage state unavailable");
            LOG_E("cannot read storage state for %s: %d", path, result);
        }
    }
    else
    {
        rt_snprintf(status, sizeof(status), "Storage scan failed: %d", result);
        lv_label_set_text(files_status_label, status);
        LOG_E("cannot scan storage path %s: %d", path, result);
    }
}

static void board_demo_copy_string(char *destination, const char *source,
                                   rt_size_t destination_size)
{
    if (destination_size == 0U)
    {
        return;
    }

    rt_strncpy(destination, source, destination_size - 1U);
    destination[destination_size - 1U] = '\0';
}

static void board_demo_set_label_text(lv_obj_t *label, const char *text)
{
    if (rt_strcmp(lv_label_get_text(label), text) != 0)
    {
        lv_label_set_text(label, text);
    }
}

static lv_obj_t *board_demo_create_label(lv_obj_t *parent, const char *text,
                                         lv_coord_t x, lv_coord_t y,
                                         lv_coord_t width)
{
    lv_obj_t *label;

    label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_width(label, width);
    lv_obj_set_style_text_color(label, COLOR_TEXT, 0);
    return label;
}

static lv_obj_t *board_demo_create_line(lv_obj_t *parent, const char *text,
                                        lv_coord_t x, lv_coord_t y,
                                        lv_coord_t width)
{
    lv_obj_t *label = board_demo_create_label(parent, text, x, y, width);

    lv_label_set_long_mode(label, LV_LABEL_LONG_MODE_DOTS);
    lv_obj_set_height(label, 22);
    return label;
}

static void board_demo_style_table(lv_obj_t *table)
{
    lv_obj_set_style_radius(table, 6, 0);
    lv_obj_set_style_border_width(table, 1, 0);
    lv_obj_set_style_border_color(table, COLOR_BORDER, 0);
    lv_obj_set_style_bg_color(table, COLOR_SURFACE, 0);
    lv_obj_set_style_pad_all(table, 0, 0);
    lv_obj_set_style_pad_hor(table, 10, LV_PART_ITEMS);
    lv_obj_set_style_pad_ver(table, 12, LV_PART_ITEMS);
    lv_obj_set_style_border_color(table, COLOR_BORDER, LV_PART_ITEMS);
    lv_obj_set_style_border_side(table, LV_BORDER_SIDE_BOTTOM, LV_PART_ITEMS);
    lv_obj_set_style_bg_color(table, COLOR_ACCENT_SOFT,
                              LV_PART_ITEMS | LV_STATE_PRESSED);
    lv_obj_set_scroll_dir(table, LV_DIR_VER);
}

static lv_obj_t *board_demo_create_button(lv_obj_t *parent, const char *text,
                                          lv_coord_t x, lv_coord_t y,
                                          lv_coord_t width, lv_coord_t height,
                                          lv_event_cb_t event_callback)
{
    lv_obj_t *button;
    lv_obj_t *label;

    button = lv_button_create(parent);
    lv_obj_set_pos(button, x, y);
    lv_obj_set_size(button, width, height);
    lv_obj_set_style_radius(button, 6, 0);
    lv_obj_set_style_bg_color(button, COLOR_ACCENT, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);
    lv_obj_set_style_pad_all(button, 6, 0);
    lv_obj_set_style_text_color(button, lv_color_white(), 0);
    if (event_callback != RT_NULL)
    {
        lv_obj_add_event_cb(button, event_callback, LV_EVENT_CLICKED, RT_NULL);
    }

    label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_width(label, lv_pct(100));
    lv_obj_set_height(label, 22);
    lv_label_set_long_mode(label, LV_LABEL_LONG_MODE_DOTS);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(label);
    return button;
}

static lv_obj_t *board_demo_create_page(enum board_demo_page_id page_id)
{
    lv_obj_t *page;
    lv_obj_t *title;

    page = lv_obj_create(demo_screen);
    lv_obj_set_pos(page, BOARD_DEMO_SIDEBAR_WIDTH, BOARD_DEMO_HEADER_HEIGHT);
    lv_obj_set_size(page, BOARD_DEMO_CONTENT_WIDTH, BOARD_DEMO_CONTENT_HEIGHT);
    lv_obj_set_style_bg_color(page, COLOR_PAGE, 0);
    lv_obj_set_style_bg_opa(page, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(page, 0, 0);
    lv_obj_set_style_radius(page, 0, 0);
    lv_obj_set_style_pad_all(page, 16, 0);
    lv_obj_set_scroll_dir(page, LV_DIR_VER);

    title = board_demo_create_label(page, board_demo_page_names[page_id],
                                    0, 0, BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    return page;
}

static void board_demo_hide_keyboard(void)
{
    lv_keyboard_set_textarea(demo_keyboard, RT_NULL);
    lv_obj_set_hidden(demo_keyboard, true);
    lv_obj_set_height(demo_pages[demo_active_page], BOARD_DEMO_CONTENT_HEIGHT);
    lv_obj_scroll_to_y(demo_pages[demo_active_page], 0, LV_ANIM_OFF);
}

static void board_demo_keyboard_event(lv_event_t *event)
{
    lv_event_code_t code;

    code = lv_event_get_code(event);
    if ((code == LV_EVENT_READY) || (code == LV_EVENT_CANCEL))
    {
        board_demo_hide_keyboard();
    }
}

static void board_demo_textarea_event(lv_event_t *event)
{
    lv_obj_t *textarea;

    if ((lv_event_get_code(event) != LV_EVENT_FOCUSED) &&
        (lv_event_get_code(event) != LV_EVENT_CLICKED))
    {
        return;
    }

    textarea = lv_event_get_target_obj(event);
    lv_keyboard_set_textarea(demo_keyboard, textarea);
    lv_obj_set_hidden(demo_keyboard, false);
    lv_obj_move_foreground(demo_keyboard);
    lv_obj_set_height(demo_pages[demo_active_page],
                       BOARD_DEMO_CONTENT_HEIGHT - BOARD_DEMO_KEYBOARD_HEIGHT);
    lv_obj_update_layout(demo_pages[demo_active_page]);
    lv_obj_scroll_to_view(textarea, LV_ANIM_OFF);
}

static void board_demo_nav_event(lv_event_t *event)
{
    enum board_demo_page_id page_id;

    page_id = (enum board_demo_page_id)(rt_ubase_t)lv_event_get_user_data(event);
    board_demo_show_page(page_id);
}

static void board_demo_show_page(enum board_demo_page_id page_id)
{
    enum board_demo_page_id index;

    if (page_id >= BOARD_DEMO_PAGE_COUNT)
    {
        return;
    }

    board_demo_hide_keyboard();
    demo_active_page = page_id;
    for (index = BOARD_DEMO_PAGE_OVERVIEW;
         index < BOARD_DEMO_PAGE_COUNT; index++)
    {
        if (index == page_id)
        {
            lv_obj_set_hidden(demo_pages[index], false);
            lv_obj_set_style_bg_color(demo_nav_buttons[index], COLOR_NAV_ACTIVE, 0);
        }
        else
        {
            lv_obj_set_hidden(demo_pages[index], true);
            lv_obj_set_style_bg_color(demo_nav_buttons[index], COLOR_NAV, 0);
        }
    }

    if (page_id == BOARD_DEMO_PAGE_FILES)
    {
        board_demo_files_request_path(demo_snapshot.fs_path[0] == '\0' ?
                                      "/flash" : demo_snapshot.fs_path);
    }
}

static void board_demo_storage_source_event(lv_event_t *event)
{
    const char *path;

    path = (const char *)lv_event_get_user_data(event);
    board_demo_files_request_path(path);
}

static void board_demo_files_refresh_event(lv_event_t *event)
{
    RT_UNUSED(event);
    board_demo_files_request_path(demo_snapshot.fs_path[0] == '\0' ?
                                  "/flash" : demo_snapshot.fs_path);
}

static void board_demo_files_up_event(lv_event_t *event)
{
    char path[BOARD_DEMO_FS_PATH_MAX];
    char *separator = RT_NULL;
    char *cursor;
    rt_size_t root_length;
    int source;

    RT_UNUSED(event);
    board_demo_copy_string(path, demo_snapshot.fs_path, sizeof(path));
    source = board_demo_fs_source(path);
    if (source < 0)
    {
        return;
    }
    root_length = rt_strlen(board_demo_storage_roots[source]);
    if (rt_strlen(path) <= root_length)
    {
        return;
    }

    for (cursor = path; *cursor != '\0'; cursor++)
    {
        if (*cursor == '/')
        {
            separator = cursor;
        }
    }
    if ((separator != RT_NULL) &&
        ((rt_size_t)(separator - path) >= root_length))
    {
        *separator = '\0';
        board_demo_files_request_path(path);
    }
}

static void board_demo_files_table_event(lv_event_t *event)
{
    char path[BOARD_DEMO_FS_PATH_MAX];
    const struct board_demo_fs_entry *entry;
    uint32_t row;
    uint32_t column;
    int length;
    int result;

    RT_UNUSED(event);
    lv_table_get_selected_cell(files_table, &row, &column);
    RT_UNUSED(column);
    if ((row == 0U) || (row > demo_snapshot.fs_entry_count))
    {
        return;
    }

    entry = &demo_snapshot.fs_entries[row - 1U];
    length = rt_snprintf(path, sizeof(path), "%s/%s",
                         demo_snapshot.fs_path, entry->name);
    if ((length <= 0) || ((rt_size_t)length >= sizeof(path)))
    {
        return;
    }

    if (entry->is_directory)
    {
        board_demo_files_request_path(path);
    }
    else
    {
        lv_label_set_text(files_preview_title, entry->name);
        lv_label_set_text(files_preview_label, "Reading...");
        result = board_demo_request_file_preview(path);
        if (result == RT_EOK)
        {
            result = board_demo_backend_get_snapshot(&demo_snapshot);
            if (result == RT_EOK)
            {
                board_demo_update_files();
            }
        }
        if (result != RT_EOK)
        {
            lv_label_set_text(files_preview_label, "Cannot read file preview");
            LOG_E("cannot read file preview for %s: %d", path, result);
        }
    }
}

static int board_demo_hex_digit(char character)
{
    if ((character >= '0') && (character <= '9'))
    {
        return character - '0';
    }
    if ((character >= 'a') && (character <= 'f'))
    {
        return character - 'a' + 10;
    }
    if ((character >= 'A') && (character <= 'F'))
    {
        return character - 'A' + 10;
    }
    return -1;
}

static int board_demo_parse_can_data(const char *text, rt_uint8_t data[8],
                                     rt_uint8_t *length)
{
    int high;
    int low;
    rt_uint8_t count = 0U;

    while (*text != '\0')
    {
        while ((*text == ' ') || (*text == ',') || (*text == ':') ||
               (*text == '-'))
        {
            text++;
        }
        if (*text == '\0')
        {
            break;
        }
        if (count >= 8U)
        {
            return -RT_EFULL;
        }

        high = board_demo_hex_digit(*text++);
        if (high < 0)
        {
            return -RT_EINVAL;
        }
        low = board_demo_hex_digit(*text++);
        if (low < 0)
        {
            return -RT_EINVAL;
        }
        data[count++] = (rt_uint8_t)((high << 4) | low);

        if ((*text != '\0') && (*text != ' ') && (*text != ',') &&
            (*text != ':') && (*text != '-'))
        {
            return -RT_EINVAL;
        }
    }

    *length = count;
    return RT_EOK;
}

static void board_demo_can_baud_event(lv_event_t *event)
{
    static const rt_uint32_t baud_rates[] =
    {
        CAN125kBaud, CAN250kBaud, CAN500kBaud, CAN1MBaud,
    };
    uint32_t selected;

    RT_UNUSED(event);
    selected = lv_dropdown_get_selected(can_baud_dropdown);
    if (selected < sizeof(baud_rates) / sizeof(baud_rates[0]))
    {
        board_demo_request_can_baud(baud_rates[selected]);
    }
}

static void board_demo_can_send_event(lv_event_t *event)
{
    const char *id_text;
    const char *data_text;
    char *end;
    rt_uint32_t id;
    rt_uint8_t data[8];
    rt_uint8_t length;
    rt_bool_t extended;
    int result;

    RT_UNUSED(event);
    id_text = lv_textarea_get_text(can_id_textarea);
    data_text = lv_textarea_get_text(can_data_textarea);
    id = (rt_uint32_t)strtoul(id_text, &end, 16);
    if ((id_text[0] == '\0') || (*end != '\0'))
    {
        lv_label_set_text(can_status_label, "Invalid CAN identifier");
        return;
    }

    result = board_demo_parse_can_data(data_text, data, &length);
    if (result != RT_EOK)
    {
        lv_label_set_text(can_status_label, "Use hexadecimal byte pairs, up to 8 bytes");
        return;
    }

    extended = lv_obj_has_state(can_extended_switch, LV_STATE_CHECKED) ?
               RT_TRUE : RT_FALSE;
    result = board_demo_request_can_send(id, extended, data, length);
    if (result != RT_EOK)
    {
        lv_label_set_text(can_status_label, "CAN frame is outside the valid range");
    }
}

static void board_demo_mqtt_start_event(lv_event_t *event)
{
    char status[64];
    int result;

    RT_UNUSED(event);
    result = board_demo_request_mqtt_start();
    if (result == RT_EOK)
    {
        lv_label_set_text(mqtt_status_label, "MQTT worker started");
        LOG_I("MQTT start command accepted from the UI");
    }
    else if (result == -RT_EBUSY)
    {
        lv_label_set_text(mqtt_status_label, "MQTT is already running");
    }
    else
    {
        rt_snprintf(status, sizeof(status), "MQTT start request failed: %d", result);
        lv_label_set_text(mqtt_status_label, status);
        LOG_E("cannot start MQTT: %d", result);
    }
}

static void board_demo_mqtt_stop_event(lv_event_t *event)
{
    char status[64];
    int result;

    RT_UNUSED(event);
    result = board_demo_request_mqtt_stop();
    if (result == RT_EOK)
    {
        lv_label_set_text(mqtt_status_label, "MQTT stopping");
        LOG_I("MQTT stop command accepted from the UI");
    }
    else
    {
        rt_snprintf(status, sizeof(status), "MQTT stop request failed: %d", result);
        lv_label_set_text(mqtt_status_label, status);
        LOG_E("cannot stop MQTT: %d", result);
    }
}

static void board_demo_mqtt_publish_event(lv_event_t *event)
{
    const char *topic;
    const char *payload;
    char status[64];
    int result;

    RT_UNUSED(event);
    topic = lv_textarea_get_text(mqtt_topic_textarea);
    payload = lv_textarea_get_text(mqtt_payload_textarea);
    result = board_demo_request_mqtt_publish(topic, payload);
    if (result == RT_EOK)
    {
        lv_label_set_text(mqtt_status_label, "MQTT publish requested");
        LOG_I("MQTT publish requested from the UI: %s", topic);
    }
    else if ((topic[0] == '\0') || (payload[0] == '\0'))
    {
        lv_label_set_text(mqtt_status_label, "Topic and payload are required");
    }
    else
    {
        rt_snprintf(status, sizeof(status), "MQTT publish request failed: %d", result);
        lv_label_set_text(mqtt_status_label, status);
        LOG_E("cannot publish MQTT message: %d", result);
    }
}

static void board_demo_pwm_slider_event(lv_event_t *event)
{
    lv_obj_t *slider;
    lv_obj_t *value_label;
    char text[16];

    slider = lv_event_get_target_obj(event);
    value_label = (lv_obj_t *)lv_event_get_user_data(event);
    rt_snprintf(text, sizeof(text), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(value_label, text);
}

static void board_demo_brightness_event(lv_event_t *event)
{
    lv_obj_t *slider;
    rt_uint8_t brightness;
    char text[16];

    slider = lv_event_get_target_obj(event);
    brightness = (rt_uint8_t)lv_slider_get_value(slider);
    rt_snprintf(text, sizeof(text), "%u%%", brightness);
    lv_label_set_text(brightness_value_label, text);

    if (board_demo_lcd_device == RT_NULL)
    {
        board_demo_lcd_device = rt_device_find(BOARD_DEMO_LCD_DEVICE_NAME);
    }
    if ((board_demo_lcd_device == RT_NULL) ||
        (rt_device_control(board_demo_lcd_device,
                           RTGRAPHIC_CTRL_SET_BRIGHTNESS,
                           &brightness) != RT_EOK))
    {
        LOG_E("cannot set display brightness to %u%%", brightness);
    }
}

static void board_demo_pwm_apply_event(lv_event_t *event)
{
    static const rt_uint32_t frequencies[] = {1000U, 10000U, 20000U};
    uint32_t selected;

    RT_UNUSED(event);
    selected = lv_dropdown_get_selected(pwm_frequency_dropdown);
    if (selected >= sizeof(frequencies) / sizeof(frequencies[0]))
    {
        return;
    }

    board_demo_request_pwm(frequencies[selected],
                           lv_obj_has_state(pwm2_switch, LV_STATE_CHECKED),
                           (rt_uint8_t)lv_slider_get_value(pwm2_slider),
                           lv_obj_has_state(pwm30_switch, LV_STATE_CHECKED),
                           (rt_uint8_t)lv_slider_get_value(pwm30_slider));
}

static void board_demo_camera_open_event(lv_event_t *event)
{
    RT_UNUSED(event);
#ifdef BSP_USING_OV7670_PREVIEW
    if (ov7670_preview_request_start() != RT_EOK)
    {
        lv_label_set_text(camera_status_label, "Camera preview is not ready");
    }
#endif
}

static void board_demo_camera_stop_event(lv_event_t *event)
{
    RT_UNUSED(event);
#ifdef BSP_USING_OV7670_PREVIEW
    ov7670_preview_request_stop();
#endif
}

static void board_demo_bus_request_feedback(lv_obj_t *status_label,
                                            lv_obj_t *log_label, int result)
{
    const char *reason;

    if (result == RT_EOK)
    {
        if (board_demo_backend_get_snapshot(&demo_snapshot) == RT_EOK)
        {
            board_demo_update_runtime();
        }
        return;
    }

    reason = result == -RT_ENOSYS ? "Feature disabled" :
             (result == -RT_EBUSY ? "Test already running" : "Request failed");
    lv_label_set_text_fmt(status_label, "%s: %d", reason, result);
    lv_obj_set_style_text_color(status_label, COLOR_DANGER, 0);
    lv_label_set_text_fmt(log_label, "FAIL %s: %d", reason, result);
    LOG_E("bus test request: %s (%d)", reason, result);
}

static void board_demo_spi_run_event(lv_event_t *event)
{
    static const rt_uint32_t frequencies[] = {1000000U, 5000000U, 10000000U};
    static const rt_uint16_t lengths[] = {32U, 64U, 128U, 256U};
    uint32_t frequency_index;
    uint32_t length_index;
    int result;

    RT_UNUSED(event);
    frequency_index = lv_dropdown_get_selected(spi_frequency_dropdown);
    length_index = lv_dropdown_get_selected(spi_length_dropdown);
    if ((frequency_index < sizeof(frequencies) / sizeof(frequencies[0])) &&
        (length_index < sizeof(lengths) / sizeof(lengths[0])))
    {
        result = board_demo_request_spi_loopback(frequencies[frequency_index],
                                                 lengths[length_index]);
        board_demo_bus_request_feedback(spi_status_label, spi_log_label, result);
    }
}

static void board_demo_i2c_scan_event(lv_event_t *event)
{
    int result;

    RT_UNUSED(event);
    result = board_demo_request_i2c_scan(BOARD_DEMO_I2C_BUS_NAME);
    board_demo_bus_request_feedback(i2c_status_label, i2c_log_label, result);
}

static void board_demo_create_sidebar(void)
{
    lv_obj_t *sidebar;
    lv_obj_t *brand;
    lv_obj_t *button;
    lv_obj_t *label;
    enum board_demo_page_id index;

    sidebar = lv_obj_create(demo_screen);
    lv_obj_set_pos(sidebar, 0, 0);
    lv_obj_set_size(sidebar, BOARD_DEMO_SIDEBAR_WIDTH, BOARD_DEMO_HEIGHT);
    lv_obj_set_style_bg_color(sidebar, COLOR_NAV, 0);
    lv_obj_set_style_bg_opa(sidebar, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(sidebar, 0, 0);
    lv_obj_set_style_radius(sidebar, 0, 0);
    lv_obj_set_style_pad_all(sidebar, 0, 0);
    lv_obj_set_scrollable(sidebar, false);

    brand = lv_label_create(sidebar);
    lv_label_set_text(brand, "Gino");
    lv_obj_set_style_text_color(brand, lv_color_white(), 0);
    lv_obj_set_style_text_font(brand, &lv_font_montserrat_16, 0);
    lv_obj_align(brand, LV_ALIGN_TOP_MID, 0, 24);

    for (index = BOARD_DEMO_PAGE_OVERVIEW;
         index < BOARD_DEMO_PAGE_COUNT; index++)
    {
        button = lv_button_create(sidebar);
        lv_obj_set_pos(button, 8, 82 + (lv_coord_t)index * 70);
        lv_obj_set_size(button, BOARD_DEMO_SIDEBAR_WIDTH - 16, 62);
        lv_obj_set_style_radius(button, 6, 0);
        lv_obj_set_style_pad_all(button, 0, 0);
        lv_obj_set_style_bg_color(button, COLOR_NAV, 0);
        lv_obj_set_style_shadow_width(button, 0, 0);
        lv_obj_add_event_cb(button, board_demo_nav_event, LV_EVENT_CLICKED,
                            (void *)(rt_ubase_t)index);
        demo_nav_buttons[index] = button;

        label = lv_label_create(button);
        lv_label_set_text(label, board_demo_page_symbols[index]);
        lv_obj_set_style_text_color(label, lv_color_white(), 0);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 9);
        label = lv_label_create(button);
        lv_label_set_text(label, board_demo_page_names[index]);
        lv_obj_set_style_text_color(label, lv_color_white(), 0);
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -9);
    }

    label = lv_label_create(sidebar);
    lv_label_set_text(label, "RT-Thread");
    lv_obj_set_style_text_color(label, lv_color_hex(0xAAB6BF), 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -18);
}

static void board_demo_create_header(void)
{
    lv_obj_t *header;

    header = lv_obj_create(demo_screen);
    lv_obj_set_pos(header, BOARD_DEMO_SIDEBAR_WIDTH, 0);
    lv_obj_set_size(header, BOARD_DEMO_CONTENT_WIDTH, BOARD_DEMO_HEADER_HEIGHT);
    lv_obj_set_style_bg_color(header, COLOR_SURFACE, 0);
    lv_obj_set_style_bg_opa(header, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(header, 1, 0);
    lv_obj_set_style_border_color(header, COLOR_BORDER, 0);
    lv_obj_set_style_border_side(header, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_set_style_pad_all(header, 0, 0);
    lv_obj_set_scrollable(header, false);

    demo_header_title = board_demo_create_label(header, "GD32H77D", 16, 23, 180);
    lv_obj_set_style_text_font(demo_header_title, &lv_font_montserrat_16, 0);

    demo_header_status = board_demo_create_label(header, "Starting services",
                                                  200, 12, BOARD_DEMO_CONTENT_WIDTH - 216);
    lv_obj_set_style_text_align(demo_header_status, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(demo_header_status, COLOR_MUTED, 0);
}

static void board_demo_build_overview_page(void)
{
    lv_obj_t *page;
    lv_obj_t *button;
    lv_obj_t *label;
    enum board_demo_page_id index;

    page = board_demo_create_page(BOARD_DEMO_PAGE_OVERVIEW);
    demo_pages[BOARD_DEMO_PAGE_OVERVIEW] = page;

    for (index = BOARD_DEMO_PAGE_FILES; index < BOARD_DEMO_PAGE_COUNT; index++)
    {
        button = lv_button_create(page);
        lv_obj_set_pos(button, 0, 40 + (index - BOARD_DEMO_PAGE_FILES) * 76);
        lv_obj_set_size(button, BOARD_DEMO_PAGE_INNER_WIDTH, 66);
        lv_obj_set_style_radius(button, 6, 0);
        lv_obj_set_style_pad_all(button, 0, 0);
        lv_obj_set_style_shadow_width(button, 0, 0);
        lv_obj_set_style_bg_color(button, COLOR_SURFACE, 0);
        lv_obj_add_event_cb(button, board_demo_nav_event, LV_EVENT_CLICKED,
                            (void *)(rt_ubase_t)index);
        label = board_demo_create_label(button, board_demo_page_symbols[index],
                                         14, 24, 26);
        lv_obj_set_style_text_color(label,
            (index == BOARD_DEMO_PAGE_CAN || index == BOARD_DEMO_PAGE_SPI ||
             index == BOARD_DEMO_PAGE_I2C) ? COLOR_INFO : COLOR_ACCENT, 0);
        board_demo_create_line(button, board_demo_page_names[index], 52, 10, 200);
        overview_status[index] = board_demo_create_line(button, "-", 52, 36,
                                                         BOARD_DEMO_PAGE_INNER_WIDTH - 98);
        lv_obj_set_style_text_color(overview_status[index], COLOR_MUTED, 0);
        label = board_demo_create_label(button, LV_SYMBOL_RIGHT,
                                         BOARD_DEMO_PAGE_INNER_WIDTH - 30, 24, 18);
        lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    }

    overview_uptime = board_demo_create_line(page, "Uptime 0 s", 0, 592,
                                               BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(overview_uptime, COLOR_MUTED, 0);
}

static void board_demo_build_files_page(void)
{
    lv_obj_t *page;
    lv_obj_t *preview_panel;
    lv_obj_t *button;
    lv_obj_t *label;
    int source;
    static const char *const source_names[BOARD_DEMO_STORAGE_COUNT] =
    {
        LV_SYMBOL_DRIVE " Flash", LV_SYMBOL_SD_CARD " SD card", LV_SYMBOL_USB " USB Host",
    };

    page = board_demo_create_page(BOARD_DEMO_PAGE_FILES);
    demo_pages[BOARD_DEMO_PAGE_FILES] = page;

    for (source = 0; source < BOARD_DEMO_STORAGE_COUNT; source++)
    {
        button = lv_button_create(page);
        lv_obj_set_pos(button, source * 188, 38);
        lv_obj_set_size(button, 180, 64);
        lv_obj_set_style_radius(button, 6, 0);
        lv_obj_set_style_pad_all(button, 0, 0);
        lv_obj_set_style_shadow_width(button, 0, 0);
        lv_obj_set_style_border_width(button, 1, 0);
        lv_obj_set_style_border_color(button, COLOR_BORDER, 0);
        lv_obj_set_style_bg_color(button, COLOR_SURFACE, 0);
        lv_obj_add_event_cb(button, board_demo_storage_source_event,
                            LV_EVENT_CLICKED, (void *)board_demo_storage_roots[source]);
        files_source_buttons[source] = button;
        label = board_demo_create_line(button, source_names[source], 12, 9, 156);
        lv_obj_set_style_text_color(label, COLOR_TEXT, 0);
        files_source_status[source] = board_demo_create_line(button, "Not mounted",
                                                               12, 35, 156);
        lv_obj_set_style_text_color(files_source_status[source], COLOR_MUTED, 0);
    }
    files_up_button = board_demo_create_button(page, LV_SYMBOL_UP,
                                                456, 114, 44, 44,
                                                board_demo_files_up_event);
    board_demo_create_button(page, LV_SYMBOL_REFRESH, 512, 114, 44, 44,
                             board_demo_files_refresh_event);

    files_path_label = board_demo_create_line(page, "/flash", 0, 124, 440);
    files_status_label = board_demo_create_line(page, "Not scanned", 0, 168,
                                                BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(files_status_label, COLOR_MUTED, 0);

    files_table = lv_table_create(page);
    lv_obj_set_pos(files_table, 0, 198);
    lv_obj_set_size(files_table, BOARD_DEMO_PAGE_INNER_WIDTH, 228);
    board_demo_style_table(files_table);
    lv_table_set_column_count(files_table, 3U);
    lv_table_set_row_count(files_table, 1U);
    lv_table_set_column_width(files_table, 0U, 44);
    lv_table_set_column_width(files_table, 1U, 398);
    lv_table_set_column_width(files_table, 2U, 112);
    lv_table_set_cell_value(files_table, 0U, 0U, "");
    lv_table_set_cell_value(files_table, 0U, 1U, "Name");
    lv_table_set_cell_value(files_table, 0U, 2U, "Size");
    lv_obj_add_event_cb(files_table, board_demo_files_table_event,
                        LV_EVENT_VALUE_CHANGED, RT_NULL);

    files_empty_label = board_demo_create_line(page, "No files", 16, 300,
                                               BOARD_DEMO_PAGE_INNER_WIDTH - 32);
    lv_obj_set_style_text_align(files_empty_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(files_empty_label, COLOR_MUTED, 0);
    lv_obj_set_hidden(files_empty_label, true);

    files_preview_title = board_demo_create_line(page, "File preview", 0, 440,
                                                  BOARD_DEMO_PAGE_INNER_WIDTH);
    preview_panel = lv_obj_create(page);
    files_preview_panel = preview_panel;
    lv_obj_set_pos(preview_panel, 0, 472);
    lv_obj_set_size(preview_panel, BOARD_DEMO_PAGE_INNER_WIDTH, 144);
    lv_obj_set_style_radius(preview_panel, 6, 0);
    lv_obj_set_style_border_width(preview_panel, 1, 0);
    lv_obj_set_style_border_color(preview_panel, COLOR_BORDER, 0);
    lv_obj_set_style_bg_color(preview_panel, COLOR_SURFACE, 0);
    lv_obj_set_style_pad_all(preview_panel, 10, 0);
    lv_obj_set_scroll_dir(preview_panel, LV_DIR_VER);

    files_preview_label = board_demo_create_label(preview_panel,
                                                  "No file selected",
                                                  0, 0, BOARD_DEMO_PAGE_INNER_WIDTH - 24);
}

static void board_demo_build_can_page(void)
{
    lv_obj_t *page;
    lv_obj_t *label;

    page = board_demo_create_page(BOARD_DEMO_PAGE_CAN);
    demo_pages[BOARD_DEMO_PAGE_CAN] = page;

    can_status_label = board_demo_create_line(page, "CAN initializing", 0, 36,
                                               BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(can_status_label, COLOR_MUTED, 0);

    can_baud_dropdown = lv_dropdown_create(page);
    lv_obj_set_pos(can_baud_dropdown, 0, 68);
    lv_obj_set_size(can_baud_dropdown, 150, 42);
    lv_dropdown_set_options(can_baud_dropdown, "125 kbit/s\n250 kbit/s\n500 kbit/s\n1 Mbit/s");
    lv_dropdown_set_selected(can_baud_dropdown, 3U);
    board_demo_create_button(page, "Apply", 162, 68, 82, 42,
                             board_demo_can_baud_event);

    label = board_demo_create_label(page, "ID", 0, 122, 90);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    can_id_textarea = lv_textarea_create(page);
    lv_obj_set_pos(can_id_textarea, 0, 142);
    lv_obj_set_size(can_id_textarea, 120, 44);
    lv_textarea_set_one_line(can_id_textarea, true);
    lv_textarea_set_max_length(can_id_textarea, 8U);
    lv_textarea_set_text(can_id_textarea, "321");
    lv_obj_add_event_cb(can_id_textarea, board_demo_textarea_event,
                        LV_EVENT_ALL, RT_NULL);

    label = board_demo_create_label(page, "Data", 134, 122, 240);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    can_data_textarea = lv_textarea_create(page);
    lv_obj_set_pos(can_data_textarea, 134, 142);
    lv_obj_set_size(can_data_textarea, 270, 44);
    lv_textarea_set_one_line(can_data_textarea, true);
    lv_textarea_set_max_length(can_data_textarea, 32U);
    lv_textarea_set_text(can_data_textarea, "01 02 03 04");
    lv_obj_add_event_cb(can_data_textarea, board_demo_textarea_event,
                        LV_EVENT_ALL, RT_NULL);

    can_extended_switch = lv_switch_create(page);
    lv_obj_set_pos(can_extended_switch, 424, 147);
    lv_obj_set_size(can_extended_switch, 48, 26);
    label = board_demo_create_label(page, "EXT", 484, 150, 60);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    board_demo_create_button(page, LV_SYMBOL_UPLOAD " Send", 444, 68, 112, 42,
                             board_demo_can_send_event);

    can_table = lv_table_create(page);
    lv_obj_set_pos(can_table, 0, 204);
    lv_obj_set_size(can_table, BOARD_DEMO_PAGE_INNER_WIDTH, 412);
    board_demo_style_table(can_table);
    lv_table_set_column_count(can_table, 4U);
    lv_table_set_row_count(can_table, 1U);
    lv_table_set_column_width(can_table, 0U, 52);
    lv_table_set_column_width(can_table, 1U, 110);
    lv_table_set_column_width(can_table, 2U, 52);
    lv_table_set_column_width(can_table, 3U, 340);
    lv_table_set_cell_value(can_table, 0U, 0U, "Dir");
    lv_table_set_cell_value(can_table, 0U, 1U, "ID");
    lv_table_set_cell_value(can_table, 0U, 2U, "Len");
    lv_table_set_cell_value(can_table, 0U, 3U, "Data");
}

static void board_demo_build_mqtt_page(void)
{
    lv_obj_t *page;
    lv_obj_t *label;
    lv_obj_t *rx_panel;

    page = board_demo_create_page(BOARD_DEMO_PAGE_MQTT);
    demo_pages[BOARD_DEMO_PAGE_MQTT] = page;

    mqtt_status_label = board_demo_create_line(page, "MQTT stopped", 0, 36,
                                                BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(mqtt_status_label, COLOR_MUTED, 0);

    label = board_demo_create_line(page, "Broker: " BSP_GD32VW553_MQTT_HOST,
                                    0, 76, 326);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    label = board_demo_create_line(page, "Subscribe: " BSP_GD32VW553_MQTT_SUB_TOPIC,
                                    0, 116, BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    board_demo_create_button(page, LV_SYMBOL_PLAY " Start", 344, 68, 100, 40,
                             board_demo_mqtt_start_event);
    board_demo_create_button(page, LV_SYMBOL_STOP " Stop", 456, 68, 100, 40,
                             board_demo_mqtt_stop_event);

    label = board_demo_create_label(page, "Publish topic", 0, 158, 200);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    mqtt_topic_textarea = lv_textarea_create(page);
    lv_obj_set_pos(mqtt_topic_textarea, 0, 184);
    lv_obj_set_size(mqtt_topic_textarea, BOARD_DEMO_PAGE_INNER_WIDTH, 44);
    lv_textarea_set_one_line(mqtt_topic_textarea, true);
    lv_textarea_set_max_length(mqtt_topic_textarea, BOARD_DEMO_MQTT_TOPIC_MAX - 1U);
    lv_textarea_set_text(mqtt_topic_textarea, BSP_GD32VW553_MQTT_PUB_TOPIC);
    lv_obj_add_event_cb(mqtt_topic_textarea, board_demo_textarea_event,
                        LV_EVENT_ALL, RT_NULL);

    label = board_demo_create_label(page, "Payload", 0, 244, 200);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    mqtt_payload_textarea = lv_textarea_create(page);
    lv_obj_set_pos(mqtt_payload_textarea, 0, 270);
    lv_obj_set_size(mqtt_payload_textarea, BOARD_DEMO_PAGE_INNER_WIDTH, 88);
    lv_textarea_set_max_length(mqtt_payload_textarea,
                               BOARD_DEMO_MQTT_PAYLOAD_MAX - 1U);
    lv_textarea_set_text(mqtt_payload_textarea, "hello from GD32H77D");
    lv_obj_add_event_cb(mqtt_payload_textarea, board_demo_textarea_event,
                        LV_EVENT_ALL, RT_NULL);
    board_demo_create_button(page, LV_SYMBOL_UPLOAD " Publish", 418, 372, 138, 44,
                             board_demo_mqtt_publish_event);

    label = board_demo_create_label(page, "Last received topic", 0, 436, 240);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    mqtt_rx_topic_label = board_demo_create_line(page, "-", 0, 464,
                                                  BOARD_DEMO_PAGE_INNER_WIDTH);
    label = board_demo_create_label(page, "Last received payload", 0, 500, 240);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    rx_panel = lv_obj_create(page);
    lv_obj_set_pos(rx_panel, 0, 528);
    lv_obj_set_size(rx_panel, BOARD_DEMO_PAGE_INNER_WIDTH, 88);
    lv_obj_set_style_radius(rx_panel, 6, 0);
    lv_obj_set_style_pad_all(rx_panel, 10, 0);
    lv_obj_set_style_border_width(rx_panel, 1, 0);
    lv_obj_set_style_border_color(rx_panel, COLOR_BORDER, 0);
    lv_obj_set_scroll_dir(rx_panel, LV_DIR_VER);
    mqtt_rx_payload_label = board_demo_create_label(rx_panel, "-", 0, 0,
                                                    BOARD_DEMO_PAGE_INNER_WIDTH - 24);
}

static void board_demo_build_pwm_page(void)
{
    lv_obj_t *page;
    lv_obj_t *label;
    rt_uint8_t brightness = 100U;
    char brightness_text[16];

    page = board_demo_create_page(BOARD_DEMO_PAGE_PWM);
    demo_pages[BOARD_DEMO_PAGE_PWM] = page;

    pwm_status_label = board_demo_create_line(page, "PWM idle", 0, 36,
                                               BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(pwm_status_label, COLOR_MUTED, 0);

    label = board_demo_create_label(page, "Display brightness", 0, 78, 200);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    board_demo_lcd_device = rt_device_find(BOARD_DEMO_LCD_DEVICE_NAME);
    if (board_demo_lcd_device != RT_NULL)
    {
        (void)rt_device_control(board_demo_lcd_device,
                                RTGRAPHIC_CTRL_GET_BRIGHTNESS,
                                &brightness);
    }
    rt_snprintf(brightness_text, sizeof(brightness_text), "%u%%", brightness);
    brightness_value_label = board_demo_create_label(page, brightness_text,
                                                      470, 78, 60);
    brightness_slider = lv_slider_create(page);
    lv_obj_set_pos(brightness_slider, 0, 112);
    lv_obj_set_size(brightness_slider, 450, 18);
    lv_slider_set_range(brightness_slider, 0, 100);
    lv_slider_set_value(brightness_slider, brightness, LV_ANIM_OFF);
    lv_obj_add_event_cb(brightness_slider, board_demo_brightness_event,
                        LV_EVENT_VALUE_CHANGED, RT_NULL);

    label = board_demo_create_label(page, "Output frequency", 0, 154, 150);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    pwm_frequency_dropdown = lv_dropdown_create(page);
    lv_obj_set_pos(pwm_frequency_dropdown, 0, 178);
    lv_obj_set_size(pwm_frequency_dropdown, 170, 44);
    lv_dropdown_set_options(pwm_frequency_dropdown, "1 kHz\n10 kHz\n20 kHz");

    label = board_demo_create_label(page, "PWM2 channel 2", 0, 250, 180);
    pwm2_switch = lv_switch_create(page);
    lv_obj_set_pos(pwm2_switch, 200, 244);
    lv_obj_set_size(pwm2_switch, 48, 26);
    pwm2_slider = lv_slider_create(page);
    lv_obj_set_pos(pwm2_slider, 0, 288);
    lv_obj_set_size(pwm2_slider, 450, 18);
    lv_slider_set_range(pwm2_slider, 0, 100);
    lv_slider_set_value(pwm2_slider, 50, LV_ANIM_OFF);
    pwm2_value_label = board_demo_create_label(page, "50%", 470, 279, 60);
    lv_obj_add_event_cb(pwm2_slider, board_demo_pwm_slider_event,
                        LV_EVENT_VALUE_CHANGED, pwm2_value_label);

    label = board_demo_create_label(page, "PWM30 channel 3", 0, 346, 180);
    pwm30_switch = lv_switch_create(page);
    lv_obj_set_pos(pwm30_switch, 200, 340);
    lv_obj_set_size(pwm30_switch, 48, 26);
    pwm30_slider = lv_slider_create(page);
    lv_obj_set_pos(pwm30_slider, 0, 384);
    lv_obj_set_size(pwm30_slider, 450, 18);
    lv_slider_set_range(pwm30_slider, 0, 100);
    lv_slider_set_value(pwm30_slider, 50, LV_ANIM_OFF);
    pwm30_value_label = board_demo_create_label(page, "50%", 470, 375, 60);
    lv_obj_add_event_cb(pwm30_slider, board_demo_pwm_slider_event,
                        LV_EVENT_VALUE_CHANGED, pwm30_value_label);

    board_demo_create_button(page, LV_SYMBOL_OK " Apply outputs", 0, 440, 160, 46,
                             board_demo_pwm_apply_event);
}

static void board_demo_build_camera_page(void)
{
    lv_obj_t *page;
    lv_obj_t *preview_panel;
    lv_obj_t *icon;

    page = board_demo_create_page(BOARD_DEMO_PAGE_CAMERA);
    demo_pages[BOARD_DEMO_PAGE_CAMERA] = page;

    camera_status_label = board_demo_create_line(page, "Camera idle", 0, 36,
                                                  BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(camera_status_label, COLOR_MUTED, 0);

    preview_panel = lv_obj_create(page);
    lv_obj_set_pos(preview_panel, 0, 76);
    lv_obj_set_size(preview_panel, BOARD_DEMO_PAGE_INNER_WIDTH, 390);
    lv_obj_set_style_bg_color(preview_panel, lv_color_black(), 0);
    lv_obj_set_style_border_width(preview_panel, 0, 0);
    lv_obj_set_style_radius(preview_panel, 4, 0);
    lv_obj_set_scrollable(preview_panel, false);
    icon = lv_label_create(preview_panel);
    lv_label_set_text(icon, LV_SYMBOL_IMAGE);
    lv_obj_set_style_text_color(icon, lv_color_hex(0xAAB6BF), 0);
    lv_obj_set_style_text_font(icon, &lv_font_montserrat_16, 0);
    lv_obj_center(icon);

    camera_counter_label = board_demo_create_label(
        page, "Captured 0 | Shown 0 | Dropped 0 | Errors 0",
        0, 486, BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(camera_counter_label, COLOR_MUTED, 0);
    board_demo_create_button(page, LV_SYMBOL_PLAY " Open preview", 0, 530, 150, 46,
                             board_demo_camera_open_event);
    board_demo_create_button(page, LV_SYMBOL_STOP " Stop", 162, 530, 100, 46,
                             board_demo_camera_stop_event);
}

static lv_obj_t *board_demo_create_bus_log(lv_obj_t *page, const char *text,
                                           lv_coord_t y, lv_coord_t height)
{
    lv_obj_t *panel;

    panel = lv_obj_create(page);
    lv_obj_set_pos(panel, 0, y);
    lv_obj_set_size(panel, BOARD_DEMO_PAGE_INNER_WIDTH, height);
    lv_obj_set_style_bg_color(panel, COLOR_SURFACE, 0);
    lv_obj_set_style_border_color(panel, COLOR_BORDER, 0);
    lv_obj_set_style_radius(panel, 6, 0);
    lv_obj_set_style_pad_all(panel, 12, 0);
    lv_obj_set_scroll_dir(panel, LV_DIR_VER);
    return board_demo_create_label(panel, text, 0, 0,
                                   BOARD_DEMO_PAGE_INNER_WIDTH - 28);
}

static void board_demo_build_spi_page(void)
{
    lv_obj_t *page;
    lv_obj_t *label;

    page = board_demo_create_page(BOARD_DEMO_PAGE_SPI);
    demo_pages[BOARD_DEMO_PAGE_SPI] = page;

    spi_status_label = board_demo_create_line(page, "SPI loopback idle", 0, 36,
                                               BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(spi_status_label, COLOR_MUTED, 0);

    label = board_demo_create_label(page, "Clock", 0, 90, 150);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    spi_frequency_dropdown = lv_dropdown_create(page);
    lv_obj_set_pos(spi_frequency_dropdown, 0, 116);
    lv_obj_set_size(spi_frequency_dropdown, 170, 44);
    lv_dropdown_set_options(spi_frequency_dropdown, "1 MHz\n5 MHz\n10 MHz");

    label = board_demo_create_label(page, "Transfer length", 200, 90, 150);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    spi_length_dropdown = lv_dropdown_create(page);
    lv_obj_set_pos(spi_length_dropdown, 200, 116);
    lv_obj_set_size(spi_length_dropdown, 170, 44);
    lv_dropdown_set_options(spi_length_dropdown, "32 bytes\n64 bytes\n128 bytes\n256 bytes");

    spi_run_button = board_demo_create_button(page, LV_SYMBOL_PLAY " Run loopback",
                                              0, 182, 160, 46, board_demo_spi_run_event);
    label = board_demo_create_line(page, "SPI3 | SCK PE12 | MOSI PF1 - MISO PF0",
                                   0, 244, BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    label = board_demo_create_line(page, "Loopback log", 0, 278,
                                   BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    spi_log_label = board_demo_create_bus_log(page, "No loopback results", 308, 304);
}

static void board_demo_build_i2c_page(void)
{
    lv_obj_t *page;
    lv_obj_t *label;
    rt_uint16_t row;
    rt_uint16_t column;

    page = board_demo_create_page(BOARD_DEMO_PAGE_I2C);
    demo_pages[BOARD_DEMO_PAGE_I2C] = page;

    i2c_status_label = board_demo_create_line(page, "I2C scan idle", 0, 36,
                                               BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(i2c_status_label, COLOR_MUTED, 0);

    label = board_demo_create_label(page, "External bus", 0, 86, 170);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    board_demo_create_line(page, BOARD_DEMO_I2C_BUS_NAME, 0, 122, 170);
    i2c_scan_button = board_demo_create_button(page, LV_SYMBOL_REFRESH " Scan",
                                              190, 112, 112, 44, board_demo_i2c_scan_event);

    label = board_demo_create_line(page, "Address map", 0, 180, 240);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    i2c_result_table = lv_table_create(page);
    lv_obj_set_pos(i2c_result_table, 0, 210);
    lv_obj_set_size(i2c_result_table, BOARD_DEMO_PAGE_INNER_WIDTH, 278);
    board_demo_style_table(i2c_result_table);
    lv_obj_set_style_pad_hor(i2c_result_table, 3, LV_PART_ITEMS);
    lv_obj_set_style_pad_ver(i2c_result_table, 4, LV_PART_ITEMS);
    lv_obj_set_style_text_align(i2c_result_table, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS);
    lv_table_set_row_count(i2c_result_table, 9U);
    lv_table_set_column_count(i2c_result_table, 17U);
    lv_table_set_column_width(i2c_result_table, 0U, 42);
    lv_table_set_cell_value(i2c_result_table, 0U, 0U, "");
    for (column = 1U; column <= 16U; column++)
    {
        lv_table_set_column_width(i2c_result_table, column, 32);
        lv_table_set_cell_value_fmt(i2c_result_table, 0U, column, "%02X", column - 1U);
    }
    for (row = 1U; row <= 8U; row++)
    {
        lv_table_set_cell_value_fmt(i2c_result_table, row, 0U, "%02X:", (row - 1U) * 16U);
        for (column = 1U; column <= 16U; column++)
        {
            lv_table_set_cell_value(i2c_result_table, row, column, "");
        }
    }
    label = board_demo_create_line(page, "Scan log", 0, 504,
                                   BOARD_DEMO_PAGE_INNER_WIDTH);
    lv_obj_set_style_text_color(label, COLOR_MUTED, 0);
    i2c_log_label = board_demo_create_bus_log(page, "No scan activity", 534, 78);
}

static void board_demo_update_storage(void)
{
    rt_uint8_t mounts;
    rt_uint8_t changed;
    int source;

    if (storage_polled &&
        (lv_tick_elaps(storage_poll_tick) < BOARD_DEMO_STORAGE_POLL_MS))
    {
        return;
    }
    storage_poll_tick = lv_tick_get();
    mounts = board_demo_storage_mounts();
    changed = storage_polled ? (mounts ^ storage_mounts) : 0U;
    storage_mounts = mounts;
    storage_polled = RT_TRUE;
    for (source = 0; source < BOARD_DEMO_STORAGE_COUNT; source++)
    {
        board_demo_set_label_text(files_source_status[source],
            (mounts & (1U << source)) ? "Mounted" : "Not mounted");
        lv_obj_set_style_text_color(files_source_status[source],
            (mounts & (1U << source)) ? COLOR_ACCENT : COLOR_MUTED, 0);
    }

    source = board_demo_fs_source(demo_snapshot.fs_path);
    if ((source >= 0) && (changed & (1U << source)))
    {
        /* A replacement drive may not contain the previous subdirectory. */
        board_demo_files_request_path(board_demo_storage_roots[source]);
    }
}

static void board_demo_update_files(void)
{
    char size_text[24];
    rt_uint8_t index;
    int source;

    if (files_sequence != demo_snapshot.fs_sequence)
    {
        files_sequence = demo_snapshot.fs_sequence;
        lv_label_set_text(files_path_label, demo_snapshot.fs_path);
        lv_label_set_text(files_status_label, demo_snapshot.fs_status);
        source = board_demo_fs_source(demo_snapshot.fs_path);
        for (index = 0U; index < BOARD_DEMO_STORAGE_COUNT; index++)
        {
            lv_obj_set_style_bg_color(files_source_buttons[index],
                source == index ? COLOR_ACCENT_SOFT : COLOR_SURFACE, 0);
            lv_obj_set_style_border_color(files_source_buttons[index],
                source == index ? COLOR_ACCENT : COLOR_BORDER, 0);
        }
        if ((source >= 0) &&
            (rt_strcmp(demo_snapshot.fs_path, board_demo_storage_roots[source]) != 0))
        {
            lv_obj_remove_state(files_up_button, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(files_up_button, LV_STATE_DISABLED);
        }
        lv_obj_set_hidden(files_empty_label, demo_snapshot.fs_entry_count != 0U);
        lv_label_set_text(files_empty_label,
            (source >= 0 && (storage_mounts & (1U << source))) ?
            demo_snapshot.fs_status : "Storage unavailable");
        lv_table_set_row_count(files_table,
                               (uint32_t)demo_snapshot.fs_entry_count + 1U);
        for (index = 0U; index < demo_snapshot.fs_entry_count; index++)
        {
            lv_table_set_cell_value(files_table, index + 1U, 0U,
                                    demo_snapshot.fs_entries[index].is_directory ?
                                    LV_SYMBOL_DIRECTORY : LV_SYMBOL_FILE);
            lv_table_set_cell_value(files_table, index + 1U, 1U,
                                    demo_snapshot.fs_entries[index].name);
            if (demo_snapshot.fs_entries[index].is_directory)
            {
                size_text[0] = '\0';
            }
            else if (demo_snapshot.fs_entries[index].size >= 1024U * 1024U)
            {
                rt_snprintf(size_text, sizeof(size_text), "%u MB",
                            demo_snapshot.fs_entries[index].size / (1024U * 1024U));
            }
            else if (demo_snapshot.fs_entries[index].size >= 1024U)
            {
                rt_snprintf(size_text, sizeof(size_text), "%u KB",
                            demo_snapshot.fs_entries[index].size / 1024U);
            }
            else
            {
                rt_snprintf(size_text, sizeof(size_text), "%u B",
                            demo_snapshot.fs_entries[index].size);
            }
            lv_table_set_cell_value(files_table, index + 1U, 2U, size_text);
        }
        lv_obj_scroll_to_y(files_table, 0, LV_ANIM_OFF);
        lv_obj_invalidate(files_table);
        LOG_I("storage table updated: %s, %u entries (%s)",
              demo_snapshot.fs_path, demo_snapshot.fs_entry_count,
              demo_snapshot.fs_status);
    }

    if (file_sequence != demo_snapshot.file_sequence)
    {
        file_sequence = demo_snapshot.file_sequence;
        lv_label_set_text(files_preview_title, demo_snapshot.file_name[0] == '\0' ?
                          "File preview" : demo_snapshot.file_name);
        lv_label_set_text(files_preview_label, demo_snapshot.file_preview[0] == '\0' ?
                          "No file selected" : demo_snapshot.file_preview);
        lv_obj_scroll_to_y(files_preview_panel, 0, LV_ANIM_OFF);
    }
}

static void board_demo_update_can(void)
{
    char id_text[16];
    char length_text[8];
    char data_text[32];
    rt_size_t used;
    rt_uint8_t frame_index;
    rt_uint8_t data_index;

    if (can_sequence == demo_snapshot.can_sequence)
    {
        return;
    }
    can_sequence = demo_snapshot.can_sequence;
    lv_label_set_text(can_status_label, demo_snapshot.can_status);
    lv_table_set_row_count(can_table, (uint32_t)demo_snapshot.can_frame_count + 1U);

    for (frame_index = 0U; frame_index < demo_snapshot.can_frame_count; frame_index++)
    {
        rt_snprintf(id_text, sizeof(id_text),
                    demo_snapshot.can_frames[frame_index].extended ?
                    "%08X" : "%03X",
                    demo_snapshot.can_frames[frame_index].id);
        rt_snprintf(length_text, sizeof(length_text), "%u",
                    demo_snapshot.can_frames[frame_index].length);
        used = 0U;
        data_text[0] = '\0';
        for (data_index = 0U;
             data_index < demo_snapshot.can_frames[frame_index].length;
             data_index++)
        {
            used += (rt_size_t)rt_snprintf(data_text + used,
                                           sizeof(data_text) - used,
                                           "%02X%s",
                                           demo_snapshot.can_frames[frame_index].data[data_index],
                                           data_index + 1U ==
                                           demo_snapshot.can_frames[frame_index].length ?
                                           "" : " ");
            if (used >= sizeof(data_text))
            {
                break;
            }
        }
        lv_table_set_cell_value(can_table, frame_index + 1U, 0U,
                                demo_snapshot.can_frames[frame_index].transmitted ?
                                "TX" : "RX");
        lv_table_set_cell_value(can_table, frame_index + 1U, 1U, id_text);
        lv_table_set_cell_value(can_table, frame_index + 1U, 2U, length_text);
        lv_table_set_cell_value(can_table, frame_index + 1U, 3U, data_text);
    }
}

static void board_demo_update_bus_log(lv_obj_t *label, const char *text)
{
    lv_obj_t *panel = lv_obj_get_parent(label);
    rt_bool_t follow = lv_obj_get_scroll_bottom(panel) <= 0;

    board_demo_set_label_text(label, text);
    if (follow)
    {
        lv_obj_update_layout(panel);
        lv_obj_scroll_to_y(panel, lv_obj_get_scroll_y(panel) +
                          lv_obj_get_scroll_bottom(panel), LV_ANIM_OFF);
    }
}

static void board_demo_update_i2c_table(void)
{
    rt_uint16_t address;
    rt_uint16_t row;
    rt_uint16_t column;
    char text[4];
    const char *value;

    for (address = 0U; address < BOARD_DEMO_I2C_ADDRESS_COUNT; address++)
    {
        switch (demo_snapshot.i2c_addresses[address])
        {
        case BOARD_DEMO_I2C_ACK:
            rt_snprintf(text, sizeof(text), "%02X", address);
            value = text;
            break;
        case BOARD_DEMO_I2C_NACK:
            value = "--";
            break;
        case BOARD_DEMO_I2C_PENDING:
            value = "..";
            break;
        case BOARD_DEMO_I2C_ERROR:
            value = "!!";
            break;
        default:
            value = "";
            break;
        }
        row = address / 16U + 1U;
        column = address % 16U + 1U;
        if (rt_strcmp(lv_table_get_cell_value(i2c_result_table, row, column), value) != 0)
        {
            lv_table_set_cell_value(i2c_result_table, row, column, value);
        }
    }
}

static void board_demo_update_runtime(void)
{
    char text[96];
#ifdef BSP_USING_OV7670_PREVIEW
    struct ov7670_preview_status camera_status;
#endif

    if (mqtt_sequence != demo_snapshot.mqtt_sequence)
    {
        mqtt_sequence = demo_snapshot.mqtt_sequence;
        lv_label_set_text(mqtt_status_label, demo_snapshot.mqtt_status);
        lv_label_set_text(mqtt_rx_topic_label,
                          demo_snapshot.mqtt_rx_topic[0] == '\0' ?
                          "-" : demo_snapshot.mqtt_rx_topic);
        lv_label_set_text(mqtt_rx_payload_label,
                          demo_snapshot.mqtt_rx_payload[0] == '\0' ?
                          "-" : demo_snapshot.mqtt_rx_payload);
    }
    if (pwm_sequence != demo_snapshot.pwm_sequence)
    {
        pwm_sequence = demo_snapshot.pwm_sequence;
        lv_label_set_text(pwm_status_label, demo_snapshot.pwm_status);
    }
    if (spi_sequence != demo_snapshot.spi_sequence)
    {
        spi_sequence = demo_snapshot.spi_sequence;
        lv_label_set_text(spi_status_label, demo_snapshot.spi_status);
        board_demo_update_bus_log(spi_log_label, demo_snapshot.spi_log);
        lv_obj_set_style_text_color(spi_status_label,
                                    demo_snapshot.spi_busy ? COLOR_INFO :
                                    (demo_snapshot.spi_passed ? COLOR_ACCENT : COLOR_DANGER), 0);
        lv_obj_set_state(spi_run_button, LV_STATE_DISABLED, demo_snapshot.spi_busy);
        lv_obj_set_state(spi_frequency_dropdown, LV_STATE_DISABLED, demo_snapshot.spi_busy);
        lv_obj_set_state(spi_length_dropdown, LV_STATE_DISABLED, demo_snapshot.spi_busy);
    }
    if (i2c_sequence != demo_snapshot.i2c_sequence)
    {
        i2c_sequence = demo_snapshot.i2c_sequence;
        lv_label_set_text(i2c_status_label, demo_snapshot.i2c_status);
        board_demo_update_i2c_table();
        board_demo_update_bus_log(i2c_log_label, demo_snapshot.i2c_log);
        lv_obj_set_style_text_color(i2c_status_label,
                                    demo_snapshot.i2c_busy ? COLOR_INFO :
                                    (demo_snapshot.i2c_result_code != RT_EOK ? COLOR_DANGER :
                                    (demo_snapshot.i2c_device_count ? COLOR_ACCENT : COLOR_WARNING)), 0);
        lv_obj_set_state(i2c_scan_button, LV_STATE_DISABLED, demo_snapshot.i2c_busy);
    }

#ifdef BSP_USING_OV7670_PREVIEW
    ov7670_preview_get_status(&camera_status);
    if (camera_status.active)
    {
        board_demo_set_label_text(camera_status_label, "Camera preview active");
    }
    else if (!camera_status.ready)
    {
        board_demo_set_label_text(camera_status_label, "Camera preview unavailable");
    }
    else if (camera_status.last_result != RT_EOK)
    {
        rt_snprintf(text, sizeof(text), "Camera idle, last result %d",
                    camera_status.last_result);
        board_demo_set_label_text(camera_status_label, text);
    }
    else
    {
        board_demo_set_label_text(camera_status_label, "Camera ready");
    }
    rt_snprintf(text, sizeof(text),
                "Captured %u | Shown %u\nDropped %u | Errors %u",
                camera_status.frame_count, camera_status.display_count,
                camera_status.drop_count, camera_status.error_count);
    board_demo_set_label_text(camera_counter_label, text);
#else
    board_demo_set_label_text(camera_status_label, "Camera disabled");
#endif
}

static void board_demo_update_overview(void)
{
    char camera_text[96];
    char storage_text[96];
    char header_text[96];
    char uptime_text[64];
#ifdef BSP_USING_OV7670_PREVIEW
    struct ov7670_preview_status camera_status;

    ov7670_preview_get_status(&camera_status);
    rt_snprintf(camera_text, sizeof(camera_text),
                "%s | Captured %u | Shown %u | Drop %u | Err %u",
                camera_status.active ? "Active" :
                (!camera_status.ready ? "Unavailable" :
                 (camera_status.last_result != RT_EOK ? "Error" : "Ready")),
                camera_status.frame_count, camera_status.display_count,
                camera_status.drop_count, camera_status.error_count);
#else
    rt_snprintf(camera_text, sizeof(camera_text), "Disabled");
#endif

    rt_snprintf(storage_text, sizeof(storage_text), "Flash %s | SD %s | USB %s",
                (storage_mounts & (1U << BOARD_DEMO_STORAGE_FLASH)) ? "ready" : "--",
                (storage_mounts & (1U << BOARD_DEMO_STORAGE_SD)) ? "ready" : "--",
                (storage_mounts & (1U << BOARD_DEMO_STORAGE_USB)) ? "ready" : "--");
    board_demo_set_label_text(overview_status[BOARD_DEMO_PAGE_FILES], storage_text);
    board_demo_set_label_text(overview_status[BOARD_DEMO_PAGE_CAN], demo_snapshot.can_status);
    board_demo_set_label_text(overview_status[BOARD_DEMO_PAGE_MQTT], demo_snapshot.mqtt_status);
    board_demo_set_label_text(overview_status[BOARD_DEMO_PAGE_PWM], demo_snapshot.pwm_status);
    board_demo_set_label_text(overview_status[BOARD_DEMO_PAGE_CAMERA], camera_text);
    board_demo_set_label_text(overview_status[BOARD_DEMO_PAGE_SPI], demo_snapshot.spi_status);
    board_demo_set_label_text(overview_status[BOARD_DEMO_PAGE_I2C], demo_snapshot.i2c_status);

    rt_snprintf(uptime_text, sizeof(uptime_text), "Uptime %u s | CAN RX %u TX %u",
                (rt_uint32_t)(((rt_uint64_t)rt_tick_get()) / RT_TICK_PER_SECOND),
                demo_snapshot.can_rx_count, demo_snapshot.can_tx_count);
    board_demo_set_label_text(overview_uptime, uptime_text);

    rt_snprintf(header_text, sizeof(header_text), "CAN %s | MQTT %s\nUSB Host %s",
                demo_snapshot.can_ready ? "ready" : "unavailable",
                demo_snapshot.mqtt_connected ? "online" : "offline",
                (storage_mounts & (1U << BOARD_DEMO_STORAGE_USB)) ? "mounted" : "not mounted");
    board_demo_set_label_text(demo_header_status, header_text);
}

static void board_demo_refresh(lv_timer_t *timer)
{
    RT_UNUSED(timer);
    /* Camera preview has its own screen. Refresh the dashboard after returning,
     * without reallocating hidden labels or polling storage during each frame. */
    if (lv_screen_active() != demo_screen)
    {
        return;
    }
    if (board_demo_backend_get_snapshot(&demo_snapshot) != RT_EOK)
    {
        return;
    }

    board_demo_update_storage();
    board_demo_update_files();
    board_demo_update_can();
    board_demo_update_runtime();
    board_demo_update_overview();
}

void board_demo_init(void)
{
    enum board_demo_page_id index;

    if (demo_screen != RT_NULL)
    {
        return;
    }
    if (board_demo_backend_init() != RT_EOK)
    {
        LOG_E("cannot initialize board demo backend");
        return;
    }

#ifdef BSP_USING_OV7670_PREVIEW
    ov7670_preview_init();
#endif

#if LV_USE_THEME_DEFAULT
    lv_display_set_theme(lv_display_get_default(),
        lv_theme_default_init(lv_display_get_default(), COLOR_ACCENT, COLOR_INFO,
                              false, &lv_font_montserrat_16));
#endif

    demo_screen = lv_obj_create(RT_NULL);
    lv_obj_set_style_bg_color(demo_screen, COLOR_PAGE, 0);
    lv_obj_set_style_bg_opa(demo_screen, LV_OPA_COVER, 0);
    lv_obj_set_scrollable(demo_screen, false);

    board_demo_create_sidebar();
    board_demo_create_header();
    board_demo_build_overview_page();
    board_demo_build_files_page();
    board_demo_build_can_page();
    board_demo_build_mqtt_page();
    board_demo_build_pwm_page();
    board_demo_build_camera_page();
    board_demo_build_spi_page();
    board_demo_build_i2c_page();

    demo_keyboard = lv_keyboard_create(demo_screen);
    lv_obj_set_size(demo_keyboard, BOARD_DEMO_CONTENT_WIDTH, BOARD_DEMO_KEYBOARD_HEIGHT);
    lv_obj_align(demo_keyboard, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_hidden(demo_keyboard, true);
    lv_obj_add_event_cb(demo_keyboard, board_demo_keyboard_event,
                        LV_EVENT_READY, RT_NULL);
    lv_obj_add_event_cb(demo_keyboard, board_demo_keyboard_event,
                        LV_EVENT_CANCEL, RT_NULL);

    for (index = BOARD_DEMO_PAGE_FILES;
         index < BOARD_DEMO_PAGE_COUNT; index++)
    {
        lv_obj_set_hidden(demo_pages[index], true);
    }
    board_demo_show_page(BOARD_DEMO_PAGE_OVERVIEW);
    lv_screen_load(demo_screen);

    demo_refresh_timer = lv_timer_create(board_demo_refresh,
                                         BOARD_DEMO_REFRESH_MS, RT_NULL);
    if (demo_refresh_timer == RT_NULL)
    {
        LOG_E("cannot create board demo refresh timer");
    }

    board_demo_update_storage();
    board_demo_files_request_path("/flash");
    LOG_I("GD32H77D LVGL board demo started");
}

#endif /* PKG_USING_LVGL && BSP_USING_LVGL_BOARD_DEMO */
