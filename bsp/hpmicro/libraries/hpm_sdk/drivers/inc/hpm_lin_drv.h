/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_LIN_DRV_H
#define HPM_LIN_DRV_H

#include <math.h>
#include "hpm_common.h"
#include "hpm_lin_regs.h"
#include "hpm_soc_feature.h"

/** bit4 and bit5 encode data length in ID */
#define LIN_ID_DATA_LEN_SHIFT 4U
#define LIN_ID_DATA_LEN_MASK  0x30U
#define LIN_ID_DATA_LEN_GET(x) (((uint8_t)(x) & LIN_ID_DATA_LEN_MASK) >> LIN_ID_DATA_LEN_SHIFT)

/**
 * @brief LIN driver APIs
 * @defgroup lin_interface LIN driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief data length in ID bit4 and bit5
 */
typedef enum {
    id_data_length_2bytes,
    id_data_length_2bytes_2, /**< both 0 and 1 represent 2 bytes */
    id_data_length_4bytes,
    id_data_length_8bytes
} lin_id_data_length_t;

/**
 * @brief bus inactivity tome to go to sleep
 */
typedef enum  {
    bus_inactivity_time_4s,
    bus_inactivity_time_6s,
    bus_inactivity_time_8s,
    bus_inactivity_time_10s
} lin_bus_inactivity_time_t;

/**
 * @brief wakeup repeat time
 */
typedef enum {
    wakeup_repeat_time_180ms,
    wakeup_repeat_time_200ms,
    wakeup_repeat_time_220ms,
    wakeup_repeat_time_240ms
} lin_wakeup_repeat_time_t;

typedef struct {
    uint32_t src_freq_in_hz;        /**< Source clock frequency in Hz */
    uint32_t baudrate;              /**< Baudrate */
} lin_timing_t;

/**
 * @brief LIN config
 */
typedef struct {
    uint8_t id;                     /**< ID */
    uint8_t *data_buff;             /**< data buff */
    bool data_length_from_id;       /**< data length should be decoded from the identifier or not) */
    uint8_t data_length;            /**< used when data_length_from_id is false */
    bool enhanced_checksum;         /**< true for enhanced checksum; false for classic checksum */
    bool transmit;                  /**< true for transmit operation; false for receive operation */
    /* bool start; */               /**< true for start operation; false for only configuration */
} lin_trans_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief lin get STATE register value
 *
 * @param [in] ptr lin base address
 * @return uint8_t STATE register value
 */
static inline uint8_t lin_get_status(LIN_Type *ptr)
{
    return ptr->STATE;
}

/**
 * @brief lin reset interrupt
 *
 * @param ptr lin base address
 */
static inline void lin_reset_interrupt(LIN_Type *ptr)
{
    ptr->CONTROL |= LIN_CONTROL_RESET_INT_MASK;
}

/**
 * @brief lin reset error
 *
 * @param ptr lin base address
 */
static inline void lin_reset_error(LIN_Type *ptr)
{
    ptr->CONTROL |= LIN_CONTROL_RESET_ERROR_MASK;
}

/**
 * @brief lin wakeup
 *
 * @param ptr lin base address
 */
static inline void lin_wakeup(LIN_Type *ptr)
{
    ptr->CONTROL |= LIN_CONTROL_WAKEUP_REQ_MASK;
}

/**
 * @brief lin sleep
 *
 * @param ptr lin base address
 */
static inline void lin_sleep(LIN_Type *ptr)
{
    ptr->CONTROL |= LIN_CONTROL_SLEEP_MASK;
}

/**
 * @brief lin slave stop
 *
 * @param ptr lin base address
 */
static inline void lin_slave_stop(LIN_Type *ptr)
{
    ptr->CONTROL |= LIN_CONTROL_STOP_MASK;
}

/**
 * @brief lin slave ack
 *
 * @param ptr lin base address
 */
static inline void lin_slave_ack(LIN_Type *ptr)
{
    ptr->CONTROL |= LIN_CONTROL_DATA_ACK_MASK;
}

/**
 * @brief lin slave set bus inactivity time
 *
 * @param ptr lin base address
 * @param time lin_bus_inactivity_time_t
 */
static inline void lin_slave_set_bus_inactivity_time(LIN_Type *ptr, lin_bus_inactivity_time_t time)
{
    ptr->TV |= LIN_TV_BUS_INACTIVITY_TIME_SET(time);
}

/**
 * @brief lin slave set wakeup repeat time
 *
 * @param ptr lin base address
 * @param time lin_wakeup_repeat_time_t
 */
static inline void lin_slave_set_wakeup_repeat_time(LIN_Type *ptr, lin_wakeup_repeat_time_t time)
{
    ptr->TV |= LIN_TV_WUP_REPEAT_TIME_SET(time);
}

/**
 * @brief lin set mode
 *
 * @param ptr lin base address
 * @param master true for master mode, false  for slave mode
 */
static inline void lin_set_mode(LIN_Type *ptr, bool master)
{
    if (master) {
        ptr->TV |= LIN_TV_MASTER_MODE_MASK;
    } else {
        ptr->TV &= ~LIN_TV_MASTER_MODE_MASK;
    }
}

/**
 * @brief lin get data value in byte
 *
 * @param ptr lin base address
 * @param index byte index
 * @return uint8_t byte value
 */
static inline uint8_t lin_get_data_byte(LIN_Type *ptr, uint8_t index)
{
    return ptr->DATABYTE[index];
}

/**
 * @brief lin write data value in byte
 *
 * @param ptr lin base address
 * @param index byte index
 * @param data byte value
 */
static inline void lin_write_data_byte(LIN_Type *ptr, uint8_t index, uint8_t data)
{
    ptr->DATABYTE[index] = data;
}

/**
 * @brief lin active status
 *
 * @param ptr lin base address
 * @return bool true for active, false for inactive
 */
static inline bool lin_is_active(LIN_Type *ptr)
{
    return ((ptr->STATE & LIN_STATE_LIN_ACTIVE_MASK) == LIN_STATE_LIN_ACTIVE_MASK) ? true : false;
}

/**
 * @brief lin complete status
 *
 * @param ptr lin base address
 * @return bool true for complete, false for incomplete
 */
static inline bool lin_is_complete(LIN_Type *ptr)
{
    return ((ptr->STATE & LIN_STATE_COMPLETE_MASK) == LIN_STATE_COMPLETE_MASK) ? true : false;
}

/**
 * @brief lin get ID
 *
 * @param ptr lin base address
 * @return uint8_t ID value
 */
static inline uint8_t lin_get_id(LIN_Type *ptr)
{
    return ptr->ID;
}

/**
 * @brief lin configure timing on master mode
 *
 * @param ptr lin base address
 * @param timing lin_timing_t
 * @return hpm_stat_t
 */
hpm_stat_t lin_master_configure_timing(LIN_Type *ptr, lin_timing_t *timing);

/**
 * @brief lin config timing on slave mode
 *
 * @param ptr lin base address
 * @param src_freq_in_hz source frequency
 * @return hpm_stat_t
 */
hpm_stat_t lin_slave_configure_timing(LIN_Type *ptr, uint32_t src_freq_in_hz);

/**
 * @brief lin transfer on master mode
 *
 * @param ptr lin base address
 * @param config lin_trans_config_t
 */
void lin_master_transfer(LIN_Type *ptr, lin_trans_config_t *config);

/**
 * @brief lin transfer on slave mode
 *
 * @note call this function after lin generate data request interrupt
 *
 * @param ptr lin base address
 * @param config lin_trans_config_t
 */
void lin_slave_transfer(LIN_Type *ptr, lin_trans_config_t *config);

/**
 * @brief get data length
 *
 * @note data length is determined by DATA_LEN register and ID
 *
 * @param ptr lin base address
 * @return uint8_t data length
 */
uint8_t lin_get_data_length(LIN_Type *ptr);

/**
 * @brief lin send data on master mode
 *
 * @param ptr lin base address
 * @param config lin_trans_config_t
 * @return status_timeout
 * @return status_success
 */
hpm_stat_t lin_master_sent(LIN_Type *ptr, lin_trans_config_t *config);

/**
 * @brief lin receive data on master mode
 *
 * @param ptr lin base address
 * @param config lin_trans_config_t
 * @return status_timeout
 * @return status_success
 */
hpm_stat_t lin_master_receive(LIN_Type *ptr, lin_trans_config_t *config);

/**
 * @brief lin send data on slave mode
 *
 * @param ptr lin base address
 * @param config lin_trans_config_t
 * @return status_timeout
 * @return status_success
 */
hpm_stat_t lin_slave_sent(LIN_Type *ptr, lin_trans_config_t *config);

/**
 * @brief lin receive data on slave mode
 *
 * @param ptr lin base address
 * @param config lin_trans_config_t
 * @return status_timeout
 * @return status_success
 */
hpm_stat_t lin_slave_receive(LIN_Type *ptr, lin_trans_config_t *config);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_LIN_DRV_H */

