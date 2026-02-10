/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __SCMI_H__
#define __SCMI_H__

#include <rtdef.h>
#include <drivers/misc.h>
#include <drivers/byteorder.h>

#define SCMI_PROTOCOL_ID_BASE       0x10
#define SCMI_PROTOCOL_ID_POWER      0x11
#define SCMI_PROTOCOL_ID_SYSTEM     0x12
#define SCMI_PROTOCOL_ID_PERF       0x13
#define SCMI_PROTOCOL_ID_CLOCK      0x14
#define SCMI_PROTOCOL_ID_SENSOR     0x15
#define SCMI_PROTOCOL_ID_RESET      0x16
#define SCMI_PROTOCOL_ID_VOLTAGE    0x17
#define SCMI_PROTOCOL_ID_POWERCAP   0x18
#define SCMI_PROTOCOL_ID_PINCTRL    0x19

#define SCMI_SUCCESS                0       /* Success */
#define SCMI_ERR_SUPPORT            (-1)    /* Not supported */
#define SCMI_ERR_PARAMS             (-2)    /* Invalid Parameters */
#define SCMI_ERR_ACCESS             (-3)    /* Invalid access/permission denied */
#define SCMI_ERR_ENTRY              (-4)    /* Not found */
#define SCMI_ERR_RANGE              (-5)    /* Value out of range */
#define SCMI_ERR_BUSY               (-6)    /* Device busy */
#define SCMI_ERR_COMMS              (-7)    /* Communication Error */
#define SCMI_ERR_GENERIC            (-8)    /* Generic Error */
#define SCMI_ERR_HARDWARE           (-9)    /* Hardware Error */
#define SCMI_ERR_PROTOCOL           (-10)   /* Protocol Error */

#define SCMI_MAX_STR_SIZE           64
#define SCMI_SHORT_NAME_MAX_SIZE    16
#define SCMI_MAX_NUM_RATES          16

struct rt_scmi_device;

typedef void (*rt_scmi_msg_callback)(struct rt_scmi_device *sdev, rt_uint8_t *msg, rt_size_t size);

/*
 * struct rt_scmi_msg - Context of a SCMI message sent and the response received
 *
 */
struct rt_scmi_msg
{
    struct rt_scmi_device *sdev;

    rt_scmi_msg_callback rx_callback;

    rt_uint32_t message_id;

    rt_uint8_t *in_msg;
    rt_size_t in_msg_size;

    rt_uint8_t *out_msg;
    rt_size_t out_msg_size;
};

/* Helper macro to match a message on input/output array references */
#define RT_SCMI_MSG_RAW(MSG_ID, IN, IN_SIZE, OUT, OUT_SIZE) \
(struct rt_scmi_msg) {              \
    .message_id = MSG_ID,           \
    .in_msg = (rt_uint8_t *)(IN),   \
    .in_msg_size = IN_SIZE,         \
    .out_msg = (rt_uint8_t *)(OUT), \
    .out_msg_size = OUT_SIZE,       \
}

#define RT_SCMI_MSG_IN_OUT(MSG_ID, IN, OUT) \
    RT_SCMI_MSG_RAW(MSG_ID, IN, sizeof(*(IN)), OUT, sizeof(*(OUT)))

#define RT_SCMI_MSG_IN(MSG_ID, IN) \
    RT_SCMI_MSG_RAW(MSG_ID, IN, sizeof(*(IN)), RT_NULL, 0)

#define RT_SCMI_MSG_OUT(MSG_ID, OUT) \
    RT_SCMI_MSG_RAW(MSG_ID, RT_NULL, 0, OUT, sizeof(*(OUT)))

#define SCMI_HDR_TOKEN(token)           (((token) << 18) & RT_GENMASK(31, 18))
#define SCMI_HDR_PROTOCOL_ID(proto)     (((proto) << 10) & RT_GENMASK(17, 10))
#define SCMI_HDR_MESSAGE_TYPE(type)     (((type) << 18) & RT_GENMASK(9, 8))
#define SCMI_HDR_MESSAGE_ID(id)         ((id) & RT_GENMASK(7, 0))

rt_inline rt_uint32_t scmi_header(unsigned msg_id, unsigned msg_type,
        unsigned protocol_id, unsigned token)
{
    return SCMI_HDR_TOKEN(token) |
           SCMI_HDR_MESSAGE_TYPE(msg_type) |
           SCMI_HDR_PROTOCOL_ID(protocol_id) |
           SCMI_HDR_MESSAGE_ID(msg_id);
}

enum scmi_common_message_id
{
    SCMI_COM_MSG_VERSION = 0x0,
    SCMI_COM_MSG_ATTRIBUTES = 0x1,
    SCMI_COM_MSG_MESSAGE_ATTRIBUTES = 0x2,
};

/*
 * SCMI Power Protocol
 */
enum scmi_power_protocol_cmd
{
    SCMI_POWER_DOMAIN_ATTRIBUTES = 0x3,
    SCMI_POWER_STATE_SET = 0x4,
    SCMI_POWER_STATE_GET = 0x5,
    SCMI_POWER_STATE_NOTIFY = 0x6,
    SCMI_POWER_DOMAIN_NAME_GET = 0x8,
};

/**
 * struct scmi_power_attributes - Response payload for SCMI_COM_MSG_ATTRIBUTES command
 */
struct scmi_power_attributes
{
    rt_le32_t state;
    rt_le16_t num_domains;
    rt_le16_t reserved;
    rt_le32_t stats_addr_low;
    rt_le32_t stats_addr_high;
    rt_le32_t stats_size;
};

/**
 * struct scmi_power_state_set_in - Message payload for SCMI_POWER_STATE_SET command
 */
struct scmi_power_state_set_in
{
    rt_le32_t flags;
    rt_le32_t domain;
#define SCMI_POWER_STATE_TYPE_SHIFT         30
#define SCMI_POWER_STATE_ID_MASK            (RT_BIT(28) - 1)
#define SCMI_POWER_STATE_PARAM(type, id)    ((((type) & RT_BIT(0)) << SCMI_POWER_STATE_TYPE_SHIFT) | ((id) & SCMI_POWER_STATE_ID_MASK))
#define SCMI_POWER_STATE_GENERIC_ON         SCMI_POWER_STATE_PARAM(0, 0)
#define SCMI_POWER_STATE_GENERIC_OFF        SCMI_POWER_STATE_PARAM(1, 0)
    rt_le32_t state;
};

/**
 * struct scmi_power_state_set_out - Response payload for SCMI_POWER_STATE_SET command
 */
struct scmi_power_state_set_out
{
    rt_le32_t state;
};

/*
 * SCMI Clock Protocol
 */
enum scmi_clock_message_id
{
    SCMI_CLOCK_ATTRIBUTES = 0x3,
    SCMI_CLOCK_DESCRIBE_RATES = 0x4,
    SCMI_CLOCK_RATE_SET = 0x5,
    SCMI_CLOCK_RATE_GET = 0x6,
    SCMI_CLOCK_CONFIG_SET = 0x7,
    SCMI_CLOCK_NAME_GET = 0x8,
};

/**
 * struct scmi_clk_attributes - Response payload for SCMI_COM_MSG_ATTRIBUTES command
 */
struct scmi_clk_attributes
{
    rt_le32_t status;
    rt_le16_t num_clocks;
    rt_uint8_t max_async_req;
    rt_uint8_t reserved;
};

/**
 * struct scmi_clk_describe_attributes_in - Message payload for SCMI_CLOCK_ATTRIBUTES command
 */
struct scmi_clk_describe_attributes_in
{
    rt_le32_t clock_id;
};

/**
 * struct scmi_clk_describe_attributes_out - Response payload for SCMI_CLOCK_ATTRIBUTES command
 *                          clock in response to a clock enable request from an agent
 */
struct scmi_clk_describe_attributes_out
{
    rt_le32_t status;
    rt_le32_t attributes;
#define CLOCK_ENABLE                            RT_BIT(0)
#define SUPPORTS_RATE_CHANGED_NOTIF(x)          ((x) & RT_BIT(31))
#define SUPPORTS_RATE_CHANGE_REQUESTED_NOTIF(x) ((x) & RT_BIT(30))
#define SUPPORTS_EXTENDED_NAMES(x)              ((x) & RT_BIT(29))
    rt_uint8_t name[SCMI_SHORT_NAME_MAX_SIZE];
    rt_le32_t clock_enable_latency;
};

/**
 * struct scmi_clk_describe_rates_in - Message payload for SCMI_CLOCK_DESCRIBE_RATES command
 */
struct scmi_clk_describe_rates_in
{
    rt_le32_t id;
    rt_le32_t rate_index;
};

/**
 * struct scmi_clk_describe_rates_out - Response payload for SCMI_CLOCK_DESCRIBE_RATES command
 */
struct scmi_clk_describe_rates_out
{
    rt_le32_t status;
    rt_le32_t num_rates_flags;
#define SCMI_NUM_RETURNED(x)    ((x) & 0xfff)
#define SCMI_RATE_DISCRETE(x)   !((x) & RT_BIT(12))
#define SCMI_NUM_REMAINING(x)   ((x) >> 16)
    struct
    {
        rt_le32_t value_low;
        rt_le32_t value_high;
    } rate[];
#define SCMI_RATE_TO_U64(X)     \
({                              \
    typeof(X) x = (X);          \
    rt_le32_to_cpu((x).value_low) | (rt_uint64_t)rt_le32_to_cpu((x).value_high) << 32; \
})
};

/**
 * struct scmi_clk_state_in - Message payload for SCMI_CLOCK_RATE_SET command
 */
struct scmi_clk_rate_set_in
{
#define SCMI_CLK_RATE_ASYNC_NOTIFY  RT_BIT(0)
#define SCMI_CLK_RATE_ASYNC_NORESP  (RT_BIT(0) | RT_BIT(1))
#define SCMI_CLK_RATE_ROUND_DOWN    0
#define SCMI_CLK_RATE_ROUND_UP      RT_BIT(2)
#define SCMI_CLK_RATE_ROUND_CLOSEST RT_BIT(3)
    rt_le32_t flags;
    rt_le32_t clock_id;
    rt_le32_t rate_lsb;
    rt_le32_t rate_msb;
};

/**
 * struct scmi_clk_rate_set_out - Response payload for SCMI_CLOCK_RATE_SET command
 */
struct scmi_clk_rate_set_out
{
    rt_le32_t status;
};

/**
 * struct scmi_clk_state_in - Message payload for SCMI_CLOCK_RATE_GET command
 */
struct scmi_clk_rate_get_in
{
    rt_le32_t clock_id;
};

/**
 * struct scmi_clk_rate_get_out - Response payload for SCMI_CLOCK_RATE_GET command
 */
struct scmi_clk_rate_get_out
{
    rt_le32_t status;
    rt_le32_t rate_lsb;
    rt_le32_t rate_msb;
};

/**
 * struct scmi_clk_state_in - Message payload for SCMI_CLOCK_CONFIG_SET command
 */
struct scmi_clk_state_in
{
    rt_le32_t clock_id;
    rt_le32_t attributes;
    rt_le32_t ext_config_val;
};

/**
 * struct scmi_clk_state_out - Response payload for SCMI_CLOCK_CONFIG_SET command
 */
struct scmi_clk_state_out
{
    rt_le32_t status;
};

/**
 * struct scmi_clk_name_in - Message payload for SCMI_CLOCK_NAME_GET command
 */
struct scmi_clk_name_in
{
    rt_le32_t clock_id;
};

/**
 * struct scmi_clk_name_out - Response payload for SCMI_CLOCK_NAME_GET command
 */
struct scmi_clk_name_out
{
    rt_le32_t status;
    rt_le32_t flags;
    rt_uint8_t name[SCMI_MAX_STR_SIZE];
};

/*
 * SCMI Sensor Domain Protocol
 */
enum scmi_sensor_message_id
{
    SCMI_SENSOR_DESCRIPTION_GET = 0x3,
    SCMI_SENSOR_TRIP_POINT_NOTIFY = 0x4,
    SCMI_SENSOR_TRIP_POINT_CONFIG = 0x5,
    SCMI_SENSOR_READING_GET = 0x6,
    SCMI_SENSOR_AXIS_DESCRIPTION_GET = 0x7,
    SCMI_SENSOR_LIST_UPDATE_INTERVALS = 0x8,
    SCMI_SENSOR_CONFIG_GET = 0x9,
    SCMI_SENSOR_CONFIG_SET = 0xa,
    SCMI_SENSOR_CONTINUOUS_UPDATE_NOTIFY = 0xb,
    SCMI_SENSOR_NAME_GET = 0xc,
    SCMI_SENSOR_AXIS_NAME_GET = 0xd,
};

enum scmi_sensor_type
{
    SCMI_SENSOR_TYPE_NONE                   = 0x0,
    SCMI_SENSOR_TYPE_UNSPEC                 = 0x1,
    SCMI_SENSOR_TYPE_TEMPERATURE_C          = 0x2,
    SCMI_SENSOR_TYPE_TEMPERATURE_F          = 0x3,
    SCMI_SENSOR_TYPE_TEMPERATURE_K          = 0x4,
    SCMI_SENSOR_TYPE_VOLTAGE                = 0x5,
    SCMI_SENSOR_TYPE_CURRENT                = 0x6,
    SCMI_SENSOR_TYPE_POWER                  = 0x7,
    SCMI_SENSOR_TYPE_ENERGY                 = 0x8,
    SCMI_SENSOR_TYPE_CHARGE                 = 0x9,
    SCMI_SENSOR_TYPE_VOLTAMPERE             = 0xa,
    SCMI_SENSOR_TYPE_NITS                   = 0xb,
    SCMI_SENSOR_TYPE_LUMENS                 = 0xc,
    SCMI_SENSOR_TYPE_LUX                    = 0xd,
    SCMI_SENSOR_TYPE_CANDELAS               = 0xe,
    SCMI_SENSOR_TYPE_KPA                    = 0xf,
    SCMI_SENSOR_TYPE_PSI                    = 0x10,
    SCMI_SENSOR_TYPE_NEWTON                 = 0x11,
    SCMI_SENSOR_TYPE_CFM                    = 0x12,
    SCMI_SENSOR_TYPE_RPM                    = 0x13,
    SCMI_SENSOR_TYPE_HERTZ                  = 0x14,
    SCMI_SENSOR_TYPE_SECS                   = 0x15,
    SCMI_SENSOR_TYPE_MINS                   = 0x16,
    SCMI_SENSOR_TYPE_HOURS                  = 0x17,
    SCMI_SENSOR_TYPE_DAYS                   = 0x18,
    SCMI_SENSOR_TYPE_WEEKS                  = 0x19,
    SCMI_SENSOR_TYPE_MILS                   = 0x1a,
    SCMI_SENSOR_TYPE_INCHES                 = 0x1b,
    SCMI_SENSOR_TYPE_FEET                   = 0x1c,
    SCMI_SENSOR_TYPE_CUBIC_INCHES           = 0x1d,
    SCMI_SENSOR_TYPE_CUBIC_FEET             = 0x1e,
    SCMI_SENSOR_TYPE_METERS                 = 0x1f,
    SCMI_SENSOR_TYPE_CUBIC_CM               = 0x20,
    SCMI_SENSOR_TYPE_CUBIC_METERS           = 0x21,
    SCMI_SENSOR_TYPE_LITERS                 = 0x22,
    SCMI_SENSOR_TYPE_FLUID_OUNCES           = 0x23,
    SCMI_SENSOR_TYPE_RADIANS                = 0x24,
    SCMI_SENSOR_TYPE_STERADIANS             = 0x25,
    SCMI_SENSOR_TYPE_REVOLUTIONS            = 0x26,
    SCMI_SENSOR_TYPE_CYCLES                 = 0x27,
    SCMI_SENSOR_TYPE_GRAVITIES              = 0x28,
    SCMI_SENSOR_TYPE_OUNCES                 = 0x29,
    SCMI_SENSOR_TYPE_POUNDS                 = 0x2a,
    SCMI_SENSOR_TYPE_FOOT_POUNDS            = 0x2b,
    SCMI_SENSOR_TYPE_OUNCE_INCHES           = 0x2c,
    SCMI_SENSOR_TYPE_GAUSS                  = 0x2d,
    SCMI_SENSOR_TYPE_GILBERTS               = 0x2e,
    SCMI_SENSOR_TYPE_HENRIES                = 0x2f,
    SCMI_SENSOR_TYPE_FARADS                 = 0x30,
    SCMI_SENSOR_TYPE_OHMS                   = 0x31,
    SCMI_SENSOR_TYPE_SIEMENS                = 0x32,
    SCMI_SENSOR_TYPE_MOLES                  = 0x33,
    SCMI_SENSOR_TYPE_BECQUERELS             = 0x34,
    SCMI_SENSOR_TYPE_PPM                    = 0x35,
    SCMI_SENSOR_TYPE_DECIBELS               = 0x36,
    SCMI_SENSOR_TYPE_DBA                    = 0x37,
    SCMI_SENSOR_TYPE_DBC                    = 0x38,
    SCMI_SENSOR_TYPE_GRAYS                  = 0x39,
    SCMI_SENSOR_TYPE_SIEVERTS               = 0x3a,
    SCMI_SENSOR_TYPE_COLOR_TEMP_K           = 0x3b,
    SCMI_SENSOR_TYPE_BITS                   = 0x3c,
    SCMI_SENSOR_TYPE_BYTES                  = 0x3d,
    SCMI_SENSOR_TYPE_WORDS                  = 0x3e,
    SCMI_SENSOR_TYPE_DWORDS                 = 0x3f,
    SCMI_SENSOR_TYPE_QWORDS                 = 0x40,
    SCMI_SENSOR_TYPE_PERCENTAGE             = 0x41,
    SCMI_SENSOR_TYPE_PASCALS                = 0x42,
    SCMI_SENSOR_TYPE_COUNTS                 = 0x43,
    SCMI_SENSOR_TYPE_GRAMS                  = 0x44,
    SCMI_SENSOR_TYPE_NEWTON_METERS          = 0x45,
    SCMI_SENSOR_TYPE_HITS                   = 0x46,
    SCMI_SENSOR_TYPE_MISSES                 = 0x47,
    SCMI_SENSOR_TYPE_RETRIES                = 0x48,
    SCMI_SENSOR_TYPE_OVERRUNS               = 0x49,
    SCMI_SENSOR_TYPE_UNDERRUNS              = 0x4a,
    SCMI_SENSOR_TYPE_COLLISIONS             = 0x4b,
    SCMI_SENSOR_TYPE_PACKETS                = 0x4c,
    SCMI_SENSOR_TYPE_MESSAGES               = 0x4d,
    SCMI_SENSOR_TYPE_CHARS                  = 0x4e,
    SCMI_SENSOR_TYPE_ERRORS                 = 0x4f,
    SCMI_SENSOR_TYPE_CORRECTED_ERRS         = 0x50,
    SCMI_SENSOR_TYPE_UNCORRECTABLE_ERRS     = 0x51,
    SCMI_SENSOR_TYPE_SQ_MILS                = 0x52,
    SCMI_SENSOR_TYPE_SQ_INCHES              = 0x53,
    SCMI_SENSOR_TYPE_SQ_FEET                = 0x54,
    SCMI_SENSOR_TYPE_SQ_CM                  = 0x55,
    SCMI_SENSOR_TYPE_SQ_METERS              = 0x56,
    SCMI_SENSOR_TYPE_RADIANS_SEC            = 0x57,
    SCMI_SENSOR_TYPE_BPM                    = 0x58,
    SCMI_SENSOR_TYPE_METERS_SEC_SQUARED     = 0x59,
    SCMI_SENSOR_TYPE_METERS_SEC             = 0x5a,
    SCMI_SENSOR_TYPE_CUBIC_METERS_SEC       = 0x5b,
    SCMI_SENSOR_TYPE_MM_MERCURY             = 0x5c,
    SCMI_SENSOR_TYPE_RADIANS_SEC_SQUARED    = 0x5d,
    SCMI_SENSOR_TYPE_OEM_UNIT               = 0xff
};

/**
 * struct scmi_sensor_attributes - Response payload for SCMI_COM_MSG_ATTRIBUTES command
 */
struct scmi_sensor_attributes
{
    rt_le16_t num_sensors;
    rt_uint8_t max_requests;
    rt_uint8_t reserved;
    rt_le32_t reg_addr_low;
    rt_le32_t reg_addr_high;
    rt_le32_t reg_size;
};

/**
 * struct scmi_sensor_description_get_in - Payload for SCMI_SENSOR_DESCRIPTION_GET command
 */
struct scmi_sensor_description_get_in
{
    rt_le32_t desc_index;
};

/**
 * struct scmi_sensor_description_get_out - Response payload for SCMI_SENSOR_DESCRIPTION_GET command
 */
struct scmi_sensor_description_get_out
{
    rt_le32_t status;
#define SCMI_SENSOR_DESC_RETURNED_NR(x)     RT_FIELD_GET(RT_GENMASK(11, 0), (x))
#define SCMI_SENSOR_DESC_REMAINING_NR(x)    RT_FIELD_GET(RT_GENMASK(31, 16), (x))
    rt_le32_t num_sensor_flags;
    struct
    {
        rt_le32_t id;
#define SCMI_SENSOR_ASYNC_READ(x)           RT_FIELD_GET(RT_BIT(31), (x))
#define SCMI_SENSOR_EXT_NAMES(x)            RT_FIELD_GET(RT_BIT(29), (x))
#define SCMI_SENSOR_TRIP_POINTS_NR(x)       RT_FIELD_GET(RT_GENMASK(7, 0), (x))
        rt_le32_t attributes_low;
#define SCMI_SENSOR_SCALE(x)                RT_FIELD_GET(RT_GENMASK(15, 11), (x))
#define SCMI_SENSOR_SCALE_SIGN              RT_BIT(4)
#define SCMI_SENSOR_SCALE_EXTEND            RT_GENMASK(31, 5)
#define SCMI_SENSOR_TYPE(x)                 RT_FIELD_GET(RT_GENMASK(7, 0), (x))
        rt_le32_t attributes_high;
        rt_uint8_t name[SCMI_SHORT_NAME_MAX_SIZE];
        rt_le32_t power;
        rt_le32_t resolution;
        rt_le32_t min_range_low;
        rt_le32_t min_range_high;
        rt_le32_t max_range_low;
        rt_le32_t max_range_high;
    } desc[];
};

/**
 * struct scmi_scmi_sensor_axis_description_get_in - Payload for SCMI_SENSOR_AXIS_DESCRIPTION_GET command
 */
struct scmi_scmi_sensor_axis_description_get_in
{
    rt_le32_t id;
    rt_le32_t axis_desc_index;
};

/**
 * struct scmi_scmi_sensor_axis_description_get_out - Response payload for SCMI_SENSOR_AXIS_DESCRIPTION_GET command
 */
struct scmi_scmi_sensor_axis_description_get_out
{
    rt_le32_t status;
#define SCMI_SENSOR_AXIS_RETURNED_NR(x)     RT_FIELD_GET(RT_GENMASK(5, 0), (x))
#define SCMI_SENSOR_AXIS_REMAINING_NR(x)    RT_FIELD_GET(RT_GENMASK(31, 26), (x))
    rt_le32_t num_axis_flags;
    struct
    {
        rt_le32_t axis_id;
#define SCMI_SENSOR_AXIS_EXT_AXIS_NAME(x)   RT_FIELD_GET(RT_BIT(9), (x))
        rt_le32_t axis_attributes_low;
#define SCMI_SENSOR_AXIS_SCALE(x)           RT_FIELD_GET(RT_GENMASK(15, 11), (x))
#define SCMI_SENSOR_AXIS_TYPE(x)            RT_FIELD_GET(RT_GENMASK(7, 0), (x))
        rt_le32_t axis_attributes_high;
        rt_uint8_t name[SCMI_SHORT_NAME_MAX_SIZE];
        rt_le32_t axis_resolution;
        rt_le32_t axis_min_range_low;
        rt_le32_t axis_min_range_high;
        rt_le32_t axis_max_range_low;
        rt_le32_t axis_max_range_high;
    } desc[];
};

/**
 * struct scmi_sensor_list_update_intervals_in - Payload for SCMI_SENSOR_LIST_UPDATE_INTERVALS command
 */
struct scmi_sensor_list_update_intervals_in
{
    rt_le32_t id;
    rt_le32_t index;
};

/**
 * struct scmi_sensor_list_update_intervals_out - Response payload for SCMI_SENSOR_LIST_UPDATE_INTERVALS command
 */
struct scmi_sensor_list_update_intervals_out
{
    rt_le32_t status;
    rt_le32_t flags;
    rt_le32_t intervals[];
};

/**
 * struct scmi_sensor_trip_point_notify_in - Payload for SCMI_SENSOR_TRIP_POINT_NOTIFY command
 */
struct scmi_sensor_trip_point_notify_in
{
    rt_le32_t id;
#define SCMI_SENSOR_NOTIFY_ALL  RT_BIT(0)
    rt_le32_t event_control;
};

/**
 * struct scmi_sensor_trip_point_notify_out - Response payload for SCMI_SENSOR_TRIP_POINT_NOTIFY command
 */
struct scmi_sensor_trip_point_notify_out
{
    rt_le32_t status;
};

/**
 * struct scmi_sensor_trip_point_config_in - Payload for SCMI_SENSOR_TRIP_POINT_CONFIG command
 */
struct scmi_sensor_trip_point_config_in
{
    rt_le32_t id;
#define SCMI_SENSOR_TRIP_POINT_EVENT_MASK   0x3
#define SCMI_SENSOR_TRIP_POINT_DISABLED     0x0
#define SCMI_SENSOR_TRIP_POINT_POSITIVE     0x1
#define SCMI_SENSOR_TRIP_POINT_NEGATIVE     0x2
#define SCMI_SENSOR_TRIP_POINT_BOTH         0x3
#define SCMI_SENSOR_TRIP_POINT_ID(x)        (((x) & 0xff) << 4)
    rt_le32_t trip_point_ev_ctrl;
    rt_le32_t trip_point_val_low;
    rt_le32_t trip_point_val_high;
};

/**
 * struct scmi_sensor_trip_point_config_out - Response payload for SCMI_SENSOR_TRIP_POINT_CONFIG command
 */
struct scmi_sensor_trip_point_config_out
{
    rt_le32_t status;
};

/**
 * struct scmi_sensor_config_get_in - Payload for SCMI_SENSOR_CONFIG_GET command
 */
struct scmi_sensor_config_get_in
{
    rt_le32_t id;
};

/**
 * struct scmi_sensor_config_get_out - Response payload for SCMI_SENSOR_CONFIG_GET command
 */
struct scmi_sensor_config_get_out
{
    rt_le32_t status;
#define SCMI_SENSOR_INTERVALS_SEC(x)    RT_FIELD_GET(RT_GENMASK(31, 16), (x))
#define SCMI_SENSOR_INTERVALS_EXP(x)    RT_FIELD_GET(RT_GENMASK(15, 11), (x))   /* SEC x (10 ^ EXP) */
#define SCMI_SENSOR_TEMP_RP(x)          RT_FIELD_GET(RT_BIT(1), (x))
#define SCMI_SENSOR_STATUS_EN(x)        RT_FIELD_GET(RT_BIT(0), (x))
    rt_le32_t config;
};

/**
 * struct scmi_sensor_config_set_in - Payload for SCMI_SENSOR_CONFIG_SET command
 */
struct scmi_sensor_config_set_in
{
    rt_le32_t id;
    rt_le32_t config;
};

/**
 * struct scmi_sensor_config_set_out - Response payload for SCMI_SENSOR_CONFIG_SET command
 */
struct scmi_sensor_config_set_out
{
    rt_le32_t status;
};

/**
 * struct scmi_sensor_reading_in - Payload for SCMI_SENSOR_READING_GET command
 */
struct scmi_sensor_reading_in
{
    rt_le32_t id;
#define SCMI_SENSOR_FLAG_ASYNC      RT_BIT(0)
    rt_le32_t flags;
};

/**
 * struct scmi_sensor_reading_out - Response payload for SCMI_SENSOR_READING_GET command
 */
struct scmi_sensor_reading_out
{
    rt_le32_t status;
    struct
    {
        rt_le32_t value_low;
        rt_le32_t value_high;
        rt_le32_t timestamp_low;
        rt_le32_t timestamp_high;
    } readings[];
};

/**
 * struct scmi_sensor_continuous_update_notify_in - Payload for SCMI_SENSOR_CONTINUOUS_UPDATE_NOTIFY command
 */
struct scmi_sensor_continuous_update_notify_in
{
    rt_le32_t id;
#define SCMI_SENSOR_FLAG_NOTIFY_ENABLE  RT_BIT(0)
    rt_le32_t notify_enable;
};

/**
 * struct scmi_sensor_continuous_update_notify_out - Response payload for SCMI_SENSOR_CONTINUOUS_UPDATE_NOTIFY command
 */
struct scmi_sensor_continuous_update_notify_out
{
    rt_le32_t status;
};

/**
 * struct scmi_sensor_name_in - Payload for SCMI_SENSOR_NAME_GET command
 */
struct scmi_sensor_name_in
{
    rt_le32_t id;
};

/**
 * struct scmi_sensor_name_out - Response payload for SCMI_SENSOR_NAME_GET command
 */
struct scmi_sensor_name_out
{
    rt_le32_t status;
    rt_le32_t flags;
    rt_uint8_t name[SCMI_MAX_STR_SIZE];
};

/**
 * struct scmi_sensor_axis_name_in - Payload for SCMI_SENSOR_AXIS_NAME_GET command
 */
struct scmi_sensor_axis_name_in
{
    rt_le32_t id;
    rt_le32_t axis_id;
};

/**
 * struct scmi_sensor_axis_name_out - Response payload for SCMI_SENSOR_AXIS_NAME_GET command
 */
struct scmi_sensor_axis_name_out
{
    rt_le32_t status;
    rt_le32_t flags;
    struct
    {
        rt_le32_t axis_id;
        rt_uint8_t name[SCMI_MAX_STR_SIZE];
    } desc[];
};

/*
 * SCMI Reset Domain Protocol
 */

enum scmi_reset_message_id
{
    SCMI_RESET_DOMAIN_ATTRIBUTES = 0x3,
    SCMI_RESET_RESET = 0x4,
};

#define SCMI_RESET_ATTRIBUTES_FLAG_ASYNC    RT_BIT(31)
#define SCMI_RESET_ATTRIBUTES_FLAG_NOTIF    RT_BIT(30)

/**
 * struct scmi_reset_attr_in - Payload for SCMI_RESET_DOMAIN_ATTRIBUTES message
 */
struct scmi_reset_attr_in
{
    rt_le32_t domain_id;
};

/**
 * struct scmi_reset_attr_out - Payload for SCMI_RESET_DOMAIN_ATTRIBUTES response
 */
struct scmi_reset_attr_out
{
    rt_le32_t status;
    rt_le32_t attributes;
    rt_le32_t latency;
    rt_uint8_t name[SCMI_SHORT_NAME_MAX_SIZE];
};

/**
 * struct scmi_reset_in - Message payload for SCMI_RESET_RESET command
 */
struct scmi_reset_in
{
    rt_le32_t domain_id;
#define SCMI_RESET_FLAG_RESET        RT_BIT(0)
#define SCMI_RESET_FLAG_ASSERT       RT_BIT(1)
#define SCMI_RESET_FLAG_ASYNC        RT_BIT(2)
    rt_le32_t flags;
#define SCMI_ARCH_COLD_RESET        0
    rt_le32_t reset_state;
};

/**
 * struct scmi_reset_out - Response payload for SCMI_RESET_RESET command
 */
struct scmi_reset_out
{
    rt_le32_t status;
};

/*
 * SCMI Voltage Domain Protocol
 */

enum scmi_voltage_domain_message_id
{
    SCMI_VOLTAGE_DOMAIN_ATTRIBUTES = 0x3,
    SCMI_VOLTAGE_DOMAIN_CONFIG_SET = 0x5,
    SCMI_VOLTAGE_DOMAIN_CONFIG_GET = 0x6,
    SCMI_VOLTAGE_DOMAIN_LEVEL_SET = 0x7,
    SCMI_VOLTAGE_DOMAIN_LEVEL_GET = 0x8,
};

#define SCMI_VOLTAGE_CONFIG_MASK    RT_GENMASK(3, 0)
#define SCMI_VOLTAGE_CONFIG_OFF     0
#define SCMI_VOLTAGE_CONFIG_ON      0x7

/**
 * struct scmi_voltage_attributes - Response payload for SCMI_COM_MSG_ATTRIBUTES command
 */
struct scmi_voltage_attributes
{
    rt_le32_t status;
    rt_le16_t num_domains;
    rt_le16_t reserved;
};

/**
 * struct scmi_voltage_attr_in - Payload for SCMI_VOLTAGE_DOMAIN_ATTRIBUTES message
 */
struct scmi_voltage_attr_in
{
    rt_le32_t domain_id;
};

/**
 * struct scmi_voltage_attr_out - Payload for SCMI_VOLTAGE_DOMAIN_ATTRIBUTES response
 */
struct scmi_voltage_attr_out
{
    rt_le32_t status;
    rt_le32_t attributes;
    char name[SCMI_SHORT_NAME_MAX_SIZE];
};

/**
 * struct scmi_voltage_config_set_in - Message payload for SCMI_VOLTAGE_DOMAIN_CONFIG_SET cmd
 */
struct scmi_voltage_config_set_in
{
    rt_le32_t domain_id;
    rt_le32_t config;
};

/**
 * struct scmi_voltage_config_set_out - Response for SCMI_VOLTAGE_DOMAIN_CONFIG_SET command
 */
struct scmi_voltage_config_set_out
{
    rt_le32_t status;
};

/**
 * struct scmi_voltage_config_get_in - Message payload for SCMI_VOLTAGE_CONFIG_GET cmd
 */
struct scmi_voltage_config_get_in
{
    rt_le32_t domain_id;
};

/**
 * struct scmi_voltage_config_get_out - Response for SCMI_VOLTAGE_CONFIG_GET command
 */
struct scmi_voltage_config_get_out
{
    rt_le32_t status;
    rt_le32_t config;
};

/**
 * struct scmi_voltage_level_set_in - Message payload for SCMI_VOLTAGE_DOMAIN_LEVEL_SET cmd
 */
struct scmi_voltage_level_set_in
{
    rt_le32_t domain_id;
    rt_le32_t flags;
    rt_le32_t voltage_level;
};

/**
 * struct scmi_voltage_level_set_out - Response for SCMI_VOLTAGE_DOMAIN_LEVEL_SET command
 */
struct scmi_voltage_level_set_out
{
    rt_le32_t status;
};

/**
 * struct scmi_voltage_level_get_in - Message payload for SCMI_VOLTAGE_DOMAIN_LEVEL_GET cmd
 */
struct scmi_voltage_level_get_in
{
    rt_le32_t domain_id;
};

/**
 * struct scmi_voltage_level_get_out - Response for SCMI_VOLTAGE_DOMAIN_LEVEL_GET command
 */
struct scmi_voltage_level_get_out
{
    rt_le32_t status;
    rt_le32_t voltage_level;
};

/*
 * SCMI Pinctrl Protocol
 */

enum scmi_pinctrl_message_id
{
    SCMI_PINCTRL_ATTRIBUTES = 0x3,
    SCMI_PINCTRL_LIST_ASSOCIATIONS = 0x4,
    SCMI_PINCTRL_SETTINGS_GET = 0x5,
    SCMI_PINCTRL_SETTINGS_CONFIGURE = 0x6,
    SCMI_PINCTRL_REQUEST = 0x7,
    SCMI_PINCTRL_RELEASE = 0x8,
    SCMI_PINCTRL_NAME_GET = 0x9,
    SCMI_PINCTRL_SET_PERMISSIONS = 0xa,
};

enum scmi_pinctrl_selector_type
{
    SCMI_PINCTRL_TYPE_PIN = 0,
    SCMI_PINCTRL_TYPE_GROUP,
    SCMI_PINCTRL_TYPE_FUNCTION,
};

enum scmi_pinctrl_conf_type
{
    SCMI_PINCTRL_DEFAULT                = 0,
    SCMI_PINCTRL_BIAS_BUS_HOLD          = 1,
    SCMI_PINCTRL_BIAS_DISABLE           = 2,
    SCMI_PINCTRL_BIAS_HIGH_IMPEDANCE    = 3,
    SCMI_PINCTRL_BIAS_PULL_UP           = 4,
    SCMI_PINCTRL_BIAS_PULL_DEFAULT      = 5,
    SCMI_PINCTRL_BIAS_PULL_DOWN         = 6,
    SCMI_PINCTRL_DRIVE_OPEN_DRAIN       = 7,
    SCMI_PINCTRL_DRIVE_OPEN_SOURCE      = 8,
    SCMI_PINCTRL_DRIVE_PUSH_PULL        = 9,
    SCMI_PINCTRL_DRIVE_STRENGTH         = 10,
    SCMI_PINCTRL_INPUT_DEBOUNCE         = 11,
    SCMI_PINCTRL_INPUT_MODE             = 12,
    SCMI_PINCTRL_PULL_MODE              = 13,
    SCMI_PINCTRL_INPUT_VALUE            = 14,
    SCMI_PINCTRL_INPUT_SCHMITT          = 15,
    SCMI_PINCTRL_LOW_POWER_MODE         = 16,
    SCMI_PINCTRL_OUTPUT_MODE            = 17,
    SCMI_PINCTRL_OUTPUT_VALUE           = 18,
    SCMI_PINCTRL_POWER_SOURCE           = 19,
    SCMI_PINCTRL_SLEW_RATE              = 20,
    SCMI_PINCTRL_OEM_START              = 192,
    SCMI_PINCTRL_OEM_END                = 255,
};

/**
 * struct scmi_pinctrl_protocol_attributes - Response payload for SCMI_COM_MSG_ATTRIBUTES command
 */
struct scmi_pinctrl_protocol_attributes
{
    rt_le32_t status;
#define SCMI_PINCTRL_GROUPS_NR(x)       RT_FIELD_GET(RT_GENMASK(31, 16), (x))
#define SCMI_PINCTRL_PINS_NR(x)         RT_FIELD_GET(RT_GENMASK(15, 0), (x))
#define SCMI_PINCTRL_FUNCTIONS_NR(x)    RT_FIELD_GET(RT_GENMASK(15, 0), (x))
    rt_le32_t attributes_low;
    rt_le32_t attributes_high;
};

/**
 * struct scmi_pinctrl_attributes_in - Message payload for SCMI_PINCTRL_ATTRIBUTES command
 */
struct scmi_pinctrl_attributes_in
{
    rt_le32_t identifier;
    rt_le32_t flags;
};

/**
 * struct scmi_pinctrl_attributes_out - Response payload for SCMI_PINCTRL_ATTRIBUTES command
 */
struct scmi_pinctrl_attributes_out
{
#define SCMI_PINCTRL_EXT_NAME_FLAG(x)   RT_FIELD_GET(RT_BIT(31), (x))
#define SCMI_PINCTRL_NUM_ELEMS(x)       RT_FIELD_GET(RT_GENMASK(15, 0), (x))
    rt_le32_t status;
    rt_le32_t attributes;
    rt_uint8_t name[SCMI_SHORT_NAME_MAX_SIZE];
};

/**
 * struct scmi_pinctrl_list_assoc_in - Message payload for SCMI_PINCTRL_LIST_ASSOCIATIONS command
 */
struct scmi_pinctrl_list_assoc_in
{
    rt_le32_t identifier;
    rt_le32_t flags;
    rt_le32_t index;
};

/**
 * struct scmi_pinctrl_list_assoc_out - Response payload for SCMI_PINCTRL_LIST_ASSOCIATIONS command
 */
struct scmi_pinctrl_list_assoc_out
{
#define SCMI_PINCTRL_REMAINING(x)       RT_FIELD_GET(RT_GENMASK(31, 16), (x))
#define SCMI_PINCTRL_RETURNED(x)        RT_FIELD_GET(RT_GENMASK(11, 0), (x))
    rt_le32_t status;
    rt_le32_t flags;
    rt_le16_t array[];
};

/**
 * struct scmi_pinctrl_settings_get_in - Message payload for SCMI_PINCTRL_SETTINGS_GET command
 */
struct scmi_pinctrl_settings_get_in
{
#define SCMI_PINCTRL_CONFIG_FLAG_MASK   RT_GENMASK(19, 18)
#define SCMI_PINCTRL_SELECTOR_MASK      RT_GENMASK(17, 16)
#define SCMI_PINCTRL_SKIP_CONFIGS_MASK  RT_GENMASK(15, 8)
#define SCMI_PINCTRL_CONFIG_TYPE_MASK   RT_GENMASK(7, 0)
    rt_le32_t identifier;
    rt_le32_t attributes;
};

/**
 * struct scmi_pinctrl_settings_get_out - Response payload for SCMI_PINCTRL_SETTINGS_GET command
 */
struct scmi_pinctrl_settings_get_out
{
    rt_le32_t status;
    rt_le32_t function_selected;
    rt_le32_t num_configs;
    rt_le32_t configs[];
};

/**
 * struct scmi_pinctrl_settings_conf_in - Message payload for SCMI_PINCTRL_SETTINGS_CONFIGURE command
 */
struct scmi_pinctrl_settings_conf_in
{
    rt_le32_t identifier;
    rt_le32_t function_id;
    rt_le32_t attributes;
    rt_le32_t configs[];
};

/**
 * struct scmi_pinctrl_settings_conf_out - Response payload for SCMI_PINCTRL_SETTINGS_CONFIGURE command
 */
struct scmi_pinctrl_settings_conf_out
{
    rt_le32_t status;
};

/**
 * struct scmi_pinctrl_request_in - Message payload for SCMI_PINCTRL_REQUEST command
 */
struct scmi_pinctrl_request_in
{
    rt_le32_t identifier;
    rt_le32_t flags;
};

/**
 * struct scmi_pinctrl_request_out - Response payload for SCMI_PINCTRL_REQUEST command
 */
struct scmi_pinctrl_request_out
{
    rt_le32_t status;
};

/**
 * struct scmi_pinctrl_request_in - Message payload for SCMI_PINCTRL_NAME_GET command
 */
struct scmi_pinctrl_name_get_in
{
    rt_le32_t identifier;
    rt_le32_t flags;
};

/**
 * struct scmi_pinctrl_name_get_out - Response payload for SCMI_PINCTRL_NAME_GET command
 */
struct scmi_pinctrl_name_get_out
{
    rt_le32_t status;
    rt_le32_t flags;
    rt_uint8_t name[SCMI_MAX_STR_SIZE];
};

struct scmi_agent;

struct rt_scmi_device_id
{
    rt_uint8_t protocol_id;
    const char *name;
};

struct rt_scmi_device
{
    struct rt_device parent;

    const char *name;
    rt_uint8_t protocol_id;

    struct scmi_agent *agent;
};

struct rt_scmi_driver
{
    struct rt_driver parent;

    const char *name;
    const struct rt_scmi_device_id *ids;

    rt_err_t (*probe)(struct rt_scmi_device *sdev);
    rt_err_t (*remove)(struct rt_scmi_device *sdev);
    rt_err_t (*shutdown)(struct rt_scmi_device *sdev);
};

rt_err_t rt_scmi_driver_register(struct rt_scmi_driver *driver);
rt_err_t rt_scmi_device_register(struct rt_scmi_device *device);

#define RT_SCMI_DRIVER_EXPORT(driver)  RT_DRIVER_EXPORT(driver, scmi, BUILIN)

rt_err_t rt_scmi_process_msg(struct rt_scmi_device *sdev, struct rt_scmi_msg *msg);
const char *rt_scmi_strerror(rt_base_t err);

#endif /* __SCMI_H__ */
