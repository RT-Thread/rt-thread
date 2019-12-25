/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef PHY_PLME_PIB_H_INCLUDED
#define PHY_PLME_PIB_H_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include "phy_common.h"

/** @file
 * This file contains declarations of PHY Information Base routines and necessary types.
 *
 * @defgroup phy_pib PHY PIB API
 * @ingroup phy_15_4
 * @{
 * @brief Module to declare PHY Information Base API
 * @details The PHY PIB module declares PHY Information Base routines and necessary types according to
 * the PHY specification. More specifically, PHY PIB Get request plme_get_req(), PHY PIB Set request
 * plme_set_req(), PHY PIB Get confirm plme_get_conf(), and PHY PIB Set confirm plme_set_conf()
 * primitives are declared. Two additional primitives not covered by the standard are declared. These are
 * plme_get() and plme_set() which are synchronous versions of plme_get_req() and plme_set_req() accordingly.
 */

#define PHY_TX_POWER_TOLERANCE_1DB        0x00
#define PHY_TX_POWER_TOLERANCE_3DB        0x40
#define PHY_TX_POWER_TOLERANCE_6DB        0x80
#define PHY_TX_POWER_TOLERANCE_MASK       0xC0

/**
 * @brief   PHY PIB attribute identificators.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.4.2.
 */
typedef enum
{
    PHY_CURRENT_CHANNEL_ID              = 0x00,  /**< Current channel. */
    PHY_CHANNELS_SUPPORTED_ID           = 0x01,  /**< Supported channels. @note read only. */
    PHY_TRANSMIT_POWER_ID               = 0x02,  /**< Transmit power. */
    PHY_CCA_MODE_ID                     = 0x03,  /**< CCA mode. */
    PHY_CURRENT_PAGE_ID                 = 0x04,  /**< Current page. */
    PHY_MAX_FRAME_DURATION_ID           = 0X05,  /**< MAX Frame duration. @note read only. */
    PHY_SHR_DURATION_ID                 = 0x06,  /**< SHR Duration. @note read only. */
    PHY_SYMBOLS_PER_OCTET_ID            = 0x07,  /**< Symbols per octet. @note read only. */
} plme_pib_attr_id_t;


/**
 * @brief   PHY PIB attribute type sizes.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, Table 23.
 */
typedef union
{
    uint8_t      phy_current_channel;            /**< Current channel. */
    uint32_t     phy_channels_supported;         /**< Supported channels. */
    int8_t       phy_transmit_power;             /**< Returns one of the DBM_xxx macro values. */
    uint8_t      phy_cca_mode;                   /**< CCA mode. */
    uint8_t      phy_current_page;               /**< Current page. */
    uint16_t     phy_max_frame_duration;         /**< MAX Frame duration. */
    uint8_t      phy_shr_duration;               /**< SHR Duration. */
    uint16_t     phy_symbols_per_octet;          /**< Symbols per octet. */
} phy_pib_item_t;


/**@brief   PLME-GET.request parameters.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.2.2.5.
 */
typedef struct
{
    plme_pib_attr_id_t      pib_attribute;       /**< PIB attribute. */
} plme_get_req_t;


/**@brief   PLME-GET.confirm parameters.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.2.2.6.
 */
typedef struct
{
    phy_status_t            status;              /**< Status of operation. */
    plme_pib_attr_id_t      pib_attribute;       /**< PIB attribute. */
    phy_pib_item_t          pib_attribute_value; /**< Attribute value. */
} plme_get_conf_t;


/**@brief   PLME-SET.request parameters.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.2.2.9.
 */
typedef struct
{
    plme_pib_attr_id_t      pib_attribute;       /**< PIB attribute. */
    phy_pib_item_t          pib_attribute_value; /**< Attribute value. */
} plme_set_req_t;


/**@brief   PLME-SET.confirm parameters.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.2.2.10.
 */
typedef struct
{
    phy_status_t            status;              /**< Status of operation. */
    plme_pib_attr_id_t      pib_attribute;       /**< PIB attribute. */
} plme_set_conf_t;


/**@brief   PLME-GET.request.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.2.2.5.
 *
 * @param[in] req   Pointer to PLME-GET.request parameters. See @ref plme_get_req_t.
 */
void plme_get_req(plme_get_req_t * req);


/**@brief   PLME-GET.confirm callback function, implemented by the next higher layer.
 *
 * @details The PLME-GET.confirm primitive is generated by the PLME and issued
 *          to its next higher layer in response to an PLME-GET.request primitive.
 *          In accordance with IEEE Std 802.15.4-2006, section 6.2.2.6.
 *
 * @param[out] conf Pointer to PLME-GET.confirm parameters. See @ref plme_get_conf_t.
 */
void plme_get_conf(plme_get_conf_t * conf);


/**@brief   PLME-SET.request.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.2.2.9.
 *
 * @param[in] req Pointer to PLME-SET.request parameters. See @ref plme_set_req_t.
 */
void plme_set_req(plme_set_req_t * req);


/**@brief   PLME-SET.confirm callback function, implemented by the next higher layer.
 *
 * @details In accordance with IEEE Std 802.15.4-2006, section 6.2.2.10.
 *
 * @param[out] conf    Pointer to PLME-SET.confirm parameters. See @ref plme_set_conf_t.
 */
void plme_set_conf(plme_set_conf_t * conf);

/**
 * @brief   Getting parameters from PIB directly (without request - confirm approach)
 *
 * @details Optional. Not covered by a standard.
 *
 * @param[in] id attribute id.
 * @param[out] mem pointer to memory for parameter storing.
 *
 * @return status of operation.
 */
phy_status_t plme_get(plme_pib_attr_id_t id, void * mem);


/**
 * @brief   Setting parameters to PIB directly (without request - confirm approach)
 *
 * @details Optional. Not covered by a standard.
 *
 * @param[in] id attribute id.
 * @param[out] mem pointer to memory for parameter storing.
 *
 * @return status of operation.
 */
phy_status_t plme_set(plme_pib_attr_id_t id, void * mem);

/** @} */

#endif // PHY_PLME_PIB_H_INCLUDED
