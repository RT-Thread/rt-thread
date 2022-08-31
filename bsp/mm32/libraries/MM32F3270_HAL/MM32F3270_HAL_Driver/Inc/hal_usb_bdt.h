/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_USB_BDT_H__
#define __HAL_USB_BDT_H__

#include "hal_common.h"

/*!
 * @addtogroup USB
 * @{
 */

/*!
 * @brief USB BufDesp EndPoint number.
 */
#define USB_BDT_EP_NUM          16u  /*!< USB BufDesp EndPoint num. */

/*!
 * @brief USB BufDesp EndPoint direction number.
 */
#define USB_BDT_DIRECTION_NUM   2u  /*!< USB BufDesp EndPoint direction num. */

/*!
 * @brief  USB BufDesp EndPoint buffer number.
 */
#define USB_BDT_BUF_NUM         2u  /*!< USB BufDesp EndPoint buffer num. */

/*!
 * @brief This type of structure instance is used to implement the buffer descriptor for USB.
 */
typedef struct
{
    union
    {
        uint32_t HEAD; /*!< Head. */
        struct
        {
            uint32_t RESEVED0   :2;  /*!< RESEVED. */
            uint32_t BDT_STALL  :1;  /*!< Stall. */
            uint32_t DTS        :1;  /*!< Data shift sync. */
            uint32_t NINC       :1;  /*!< DMA addr cannot increasing. */
            uint32_t KEEP       :1;  /*!< Keep BD held by USB. */
            uint32_t DATA       :1;  /*!< DATA0 or DATA1. */
            uint32_t OWN        :1;  /*!< Owner, 0 is CPU, 1 is USB. */
            uint32_t RESEVED1   :8;  /*!< RESEVED. */
            uint32_t BC         :10; /*!< Packet size. */
            uint32_t RESEVED2   :6;  /*!< RESEVED. */
        };
        struct
        {
            uint32_t RESEVED3   :2;  /*!< RESEVED. */
            uint32_t TOK_PID    :4;  /*!< Token pid. */
            uint32_t RESEVED4   :26; /*!< RESEVED. */
        };
    };
    uint32_t ADDR; /*!< Buffer addr. */
} USB_BufDesp_Type;

/*!
 * @brief This type of structure instance is used to implement the buffer descriptor table for USB.
 */
typedef union
{
    USB_BufDesp_Type Table[USB_BDT_EP_NUM][ USB_BDT_DIRECTION_NUM][ USB_BDT_BUF_NUM]; /*!< [EndPoint] [Direction] [Odd_Even]. */
    USB_BufDesp_Type Index[USB_BDT_EP_NUM * USB_BDT_DIRECTION_NUM * USB_BDT_BUF_NUM]; /*!< Index. */
} USB_BufDespTable_Type;

/*!
 * @}
 */

#endif /* __HAL_USB_BDT_H__ */

