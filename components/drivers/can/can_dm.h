/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __CAN_DM_H__
#define __CAN_DM_H__

#include <drivers/misc.h>

/* Special address description flags for the CAN_ID */
#define CAN_EFF_FLAG        0x80000000U     /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG        0x40000000U     /* Remote transmission request */
#define CAN_ERR_FLAG        0x20000000U     /* Error message frame */

/* Valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK        0x000007ffU     /* Standard frame format (SFF) */
#define CAN_EFF_MASK        0x1fffffffU     /* Extended frame format (EFF) */
#define CAN_ERR_MASK        0x1fffffffU     /* Omit EFF, RTR, ERR flags */
#define CANXL_PRIO_MASK     CAN_SFF_MASK    /* 11 bit priority mask */

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC         8
#define CAN_MAX_RAW_DLC     15
#define CAN_MAX_DLEN        8

/* CAN FD payload length and DLC definitions according to ISO 11898-7 */
#define CANFD_MAX_DLC       15
#define CANFD_MAX_DLEN      64

/*
 * To be used in the CAN netdriver receive path to ensure conformance with
 * ISO 11898-1 Chapter 8.4.2.3 (DLC field)
 */
#define can_get_dlc(v)      (rt_min_t(rt_uint8_t, (v), CAN_MAX_DLC))
#define canfd_get_dlc(v)    (rt_min_t(rt_uint8_t, (v), CANFD_MAX_DLC))

/**
 * @brief Convert CAN DLC value to actual data length
 *
 * Converts a CAN Data Length Code (DLC) to the actual number of data bytes
 * according to ISO 11898-1 and ISO 11898-7 (CAN FD) specifications.
 *
 * @param can_dlc The DLC value (0-15)
 * @return The actual data length in bytes
 */
rt_uint8_t can_dlc2len(rt_uint8_t can_dlc);

/**
 * @brief Convert data length to CAN DLC value
 *
 * Converts a data length in bytes to the appropriate CAN Data Length Code (DLC)
 * according to ISO 11898-1 and ISO 11898-7 (CAN FD) specifications.
 *
 * @param len The data length in bytes (0-64)
 * @return The corresponding DLC value (0-15)
 */
rt_uint8_t can_len2dlc(rt_uint8_t len);

#endif /* __CAN_DM_H__ */
