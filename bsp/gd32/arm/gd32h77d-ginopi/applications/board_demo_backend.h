/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BOARD_DEMO_BACKEND_H
#define BOARD_DEMO_BACKEND_H

#include <rtthread.h>

#define BOARD_DEMO_FS_PATH_MAX          128
#define BOARD_DEMO_FS_NAME_MAX          BOARD_DEMO_FS_PATH_MAX
#define BOARD_DEMO_FS_ENTRY_MAX         32
#define BOARD_DEMO_FILE_PREVIEW_MAX     1536
#define BOARD_DEMO_CAN_LOG_MAX          16
#define BOARD_DEMO_MQTT_TOPIC_MAX       64
#define BOARD_DEMO_MQTT_PAYLOAD_MAX     256
#define BOARD_DEMO_STATUS_MAX           80
#define BOARD_DEMO_I2C_ADDRESS_COUNT    128
#define BOARD_DEMO_I2C_BUS_NAME         "hwi2c1"
#define BOARD_DEMO_BUS_LOG_MAX          3072

enum board_demo_i2c_address_state
{
    BOARD_DEMO_I2C_SKIPPED = 0,
    BOARD_DEMO_I2C_PENDING,
    BOARD_DEMO_I2C_ACK,
    BOARD_DEMO_I2C_NACK,
    BOARD_DEMO_I2C_ERROR,
};

enum board_demo_storage_id
{
    BOARD_DEMO_STORAGE_FLASH = 0,
    BOARD_DEMO_STORAGE_SD,
    BOARD_DEMO_STORAGE_USB,
    BOARD_DEMO_STORAGE_COUNT,
};

extern const char *const board_demo_storage_roots[BOARD_DEMO_STORAGE_COUNT];

struct board_demo_fs_entry
{
    char name[BOARD_DEMO_FS_NAME_MAX];
    rt_uint32_t size;
    rt_bool_t is_directory;
};

struct board_demo_can_frame
{
    rt_uint32_t id;
    rt_uint32_t tick;
    rt_uint8_t data[8];
    rt_uint8_t length;
    rt_bool_t extended;
    rt_bool_t transmitted;
};

struct board_demo_snapshot
{
    rt_uint32_t fs_sequence;
    char fs_path[BOARD_DEMO_FS_PATH_MAX];
    char fs_status[BOARD_DEMO_STATUS_MAX];
    struct board_demo_fs_entry fs_entries[BOARD_DEMO_FS_ENTRY_MAX];
    rt_uint8_t fs_entry_count;

    rt_uint32_t file_sequence;
    char file_name[BOARD_DEMO_FS_PATH_MAX];
    char file_preview[BOARD_DEMO_FILE_PREVIEW_MAX];

    rt_uint32_t can_sequence;
    char can_status[BOARD_DEMO_STATUS_MAX];
    struct board_demo_can_frame can_frames[BOARD_DEMO_CAN_LOG_MAX];
    rt_uint8_t can_frame_count;
    rt_uint32_t can_baud_rate;
    rt_uint32_t can_rx_count;
    rt_uint32_t can_tx_count;
    rt_uint32_t can_error_count;
    rt_bool_t can_ready;

    rt_uint32_t mqtt_sequence;
    char mqtt_status[BOARD_DEMO_STATUS_MAX];
    char mqtt_rx_topic[BOARD_DEMO_MQTT_TOPIC_MAX];
    char mqtt_rx_payload[BOARD_DEMO_MQTT_PAYLOAD_MAX];
    char mqtt_tx_topic[BOARD_DEMO_MQTT_TOPIC_MAX];
    char mqtt_tx_payload[BOARD_DEMO_MQTT_PAYLOAD_MAX];
    rt_bool_t mqtt_running;
    rt_bool_t mqtt_connected;

    rt_uint32_t pwm_sequence;
    char pwm_status[BOARD_DEMO_STATUS_MAX];
    rt_uint32_t pwm_frequency;
    rt_uint8_t pwm2_duty;
    rt_uint8_t pwm30_duty;
    rt_bool_t pwm2_enabled;
    rt_bool_t pwm30_enabled;

    rt_uint32_t spi_sequence;
    char spi_status[BOARD_DEMO_STATUS_MAX];
    char spi_log[BOARD_DEMO_BUS_LOG_MAX];
    rt_uint32_t spi_frequency;
    rt_uint16_t spi_length;
    rt_uint16_t spi_mismatch_index;
    rt_bool_t spi_passed;
    rt_bool_t spi_busy;

    rt_uint32_t i2c_sequence;
    char i2c_status[BOARD_DEMO_STATUS_MAX];
    char i2c_bus_name[RT_NAME_MAX];
    rt_uint8_t i2c_addresses[BOARD_DEMO_I2C_ADDRESS_COUNT];
    rt_err_t i2c_result_code;
    char i2c_log[BOARD_DEMO_BUS_LOG_MAX];
    rt_uint8_t i2c_device_count;
    rt_bool_t i2c_busy;
};

int board_demo_backend_init(void);
int board_demo_backend_get_snapshot(struct board_demo_snapshot *snapshot);

int board_demo_fs_source(const char *path);
rt_uint8_t board_demo_storage_mounts(void);
int board_demo_request_fs_list(const char *path);
int board_demo_request_file_preview(const char *path);
int board_demo_request_can_baud(rt_uint32_t baud_rate);
int board_demo_request_can_send(rt_uint32_t id, rt_bool_t extended,
                                const rt_uint8_t *data, rt_uint8_t length);
int board_demo_request_mqtt_start(void);
int board_demo_request_mqtt_stop(void);
int board_demo_request_mqtt_publish(const char *topic, const char *payload);
int board_demo_request_pwm(rt_uint32_t frequency,
                           rt_bool_t pwm2_enabled, rt_uint8_t pwm2_duty,
                           rt_bool_t pwm30_enabled, rt_uint8_t pwm30_duty);
int board_demo_request_spi_loopback(rt_uint32_t frequency, rt_uint16_t length);
int board_demo_request_i2c_scan(const char *bus_name);

#endif /* BOARD_DEMO_BACKEND_H */
