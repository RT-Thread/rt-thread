/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-29     bigmagic       first version
 */
#ifndef __DRV_BT_H__
#define __DRV_BT_H__

#define     BT_HCI_COMMAND_PKT          (0x01)
#define     BT_OGF_HOST_CONTROL         (0x03)
#define     BT_OGF_LE_CONTROL           (0x08)
#define     BT_OGF_VENDOR               (0x3f)
#define     BT_COMMAND_SET_BDADDR       (0x01)
#define     BT_COMMAND_RESET_CHIP       (0x03)
#define     BT_COMMAND_SET_BAUD         (0x18)
#define     BT_COMMAND_LOAD_FIRMWARE    (0x2e)
#define     BT_HCI_ACL_PKT              (0x02)
#define     BT_HCI_EVENT_PKT            (0x04)
#define     BT_COMMAND_COMPLETE_CODE    (0x0e)
#define     BT_CONNECT_COMPLETE_CODE    (0x0f)
#define     BT_LL_SCAN_ACTIVE           (0x01)
#define     BT_LL_ADV_NONCONN_IND       (0x03)

#endif
