/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef MAC_MLME_PIB_H_INCLUDED
#define MAC_MLME_PIB_H_INCLUDED

#include <stdint.h>
#include "mac_common.h"
#include "phy_plme_pib.h"
#include "mac_task_scheduler.h"
#include "mac_security.h"
#include "sys_debug.h"

/** @file
 * The MAC MLME PIB module declares the MAC PHY Information Base routines and
 * necessary types/macros according to the MAC specification.
 *
 * @defgroup mac_pib MAC MLME PIB API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME PIB API.
 * @details The MAC PIB module declares routines and necessary types to deal with the PHY Information Base
 * functionality related to MAC. More specifically, MLME PIB Get request aka mlme_get_req(), MLME
 * PIB Set request aka mlme_set_req(), MLME PIB confirmation callbacks aka mlme_get_conf_cb_t, and
 * mlme_set_conf_cb_t primitives are declared. Two additional primitives not covered by the
 * standard are declared. These are mlme_get() and mlme_set() which are synchronous versions of
 * mlme_get_req() and mlme_set_req() accordingly. There is one helper informational routine
 * mlme_pib_attr_size_calc() to count MLME attribute size in bytes. Refer to the
 * mac_pib_param_test application for detailed samples of implementation of these primitives.
 * This module also defines the MAC Table API. The tables can be used to deal with MAC attributes.
 * A special initialization routine mac_table_init() should be called before using of any other MAC
 * table API. The mac_table_reset() routine is used to clean up an existing (initialized) table.
 * mac_table_idx_get() searches through a MAC table to find the item with requested idx. The
 * mac_table_item_set() routine is needed to substitute a table item with a new value. The
 * mac_table_item_remove() routine removes the item with the given index from the table and
 * frees all resources associated with the item. mac_table_item_front() and mac_table_item_next()
 * return the first and next item from the table. The mac_table_size_get() routine returns the
 * number of items in the table, while mac_table_is_empty() checks if the table is empty.
 */

/**
 * @brief MAC PIB attribute identificators
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.4.2
 */
typedef enum
{
    MAC_ACK_WAIT_DURATION              = 0x40,
    MAC_ASSOCIATION_PERMIT,
    MAC_AUTO_REQUEST,
    MAC_BATT_LIFE_EXT,
    MAC_BATT_LIFE_EXT_PERIODS,
    MAC_BEACON_PAYLOAD,                /* 0x45 */
    MAC_BEACON_PAYLOAD_LENGTH,
    MAC_BEACON_ORDER,                  /**< Specification of how often the
                                                 coordinator transmits its
                                                 beacon. If BO = 15, the
                                                 coordinator will not transmit
                                                 a periodic beacon.*/
    MAC_BEACON_TX_TIME,
    MAC_BSN,
    MAC_COORD_EXTENDED_ADDRESS,        /* 0x4A */
    MAC_COORD_SHORT_ADDRESS,
    MAC_DSN,
    MAC_GTS_PERMIT,
    MAC_MAX_CSMA_BACKOFFS,
    MAC_MIN_BE,
    MAC_PAN_ID,                        /* 0x50 */
    MAC_PROMISCUOUS_MODE,
    MAC_RX_ON_WHEN_IDLE,
    MAC_SHORT_ADDRESS,
    MAC_SUPERFRAME_ORDER,
    MAC_TRANSACTION_PERSISTENCE_TIME,  /* 0x55 */
    MAC_ASSOCIATED_PAN_COORD,
    MAC_MAX_BE,
    MAC_MAX_FRAME_TOTAL_WAIT_TIME,
    MAC_MAX_FRAME_RETRIES,
    MAC_RESPONSE_WAIT_TIME,            /* 0x5A */
    MAC_SYNC_SYMBOL_OFFSET,
    MAC_TIMESTAMP_SUPPORTED,
    MAC_SECURITY_ENABLED,
    MAC_MIN_LIFS_PERIOD,               /* 0x5E No attribute id in Table 86.*/
    MAC_MIN_SIFS_PERIOD,               /* 0x5F No attribute id in Table 86.*/
    MAC_EXTENDED_ADDRESS,              /* 0x60 Not covered by standard.*/
    MAC_IS_PAN_COORD,

#if (CONFIG_SECURE == 1)
    MAC_KEY_TABLE                      = 0x71,
    MAC_KEY_TABLE_ENTRIES,
    MAC_DEVICE_TABLE,
    MAC_DEVICE_TABLE_ENTRIES,
    MAC_SECURITY_LEVEL_TABLE,          /* 0x75 */
    MAC_SECURITY_LEVEL_TABLE_ENTRIES,
    MAC_FRAME_COUNTER,
    MAC_AUTO_REQUEST_SECURITY_LEVEL,
    MAC_AUTO_REQUEST_KEY_ID_MODE,
    MAC_AUTO_REQUEST_KEY_SOURCE,       /* 0x7A */
    MAC_AUTO_REQUEST_KEY_INDEX,
    MAC_DEFAULT_KEY_SOURCE,
    MAC_PAN_COORD_EXTENDED_ADDRESS,
    MAC_PAN_COORD_SHORT_ADDRESS,

    /* Items below do not covered by the standard */

    // these three IDs are used to make access to the root of security tables
    MAC_KEY_TABLE_POINTER,
    MAC_DEVICE_TABLE_POINTER,
    MAC_SECURITY_LEVEL_TABLE_POINTER,

    // these three IDs are stored inside PIB base and
    // used to get table item sizes
    MAC_KEY_ID_LOOKUP_LIST,
    MAC_KEY_DEVICE_LIST,
    MAC_KEY_USAGE_LIST,
#endif
} mlme_pib_attr_id_t;


/**
 * @brief United PIB attribute identifiers
 *
 * To unite access to MAC and PHY PIB by one API
 */
typedef union
{
    mlme_pib_attr_id_t mlme_id;            /**< PIB is MAC-based. */
    plme_pib_attr_id_t plme_id;            /**< PIB is PHY-based. */
} pib_id_t;


/**
 * @brief   MLME-GET.confirm
 *
 * @details structure for confirming information about a given PIB attribute.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.6.2
 */
typedef struct
{
    mac_status_t       status;             /**< Status of operation. */
    pib_id_t           pib_attribute;      /**< PIB Attribute. */
    uint8_t            pib_attribute_idx;  /**< PIB Attribute index. */
    /** value size is calculated with 'mlme_pib_attr_size_calc' */
    uint8_t          * value;              /**< Attribute value. */
} mlme_get_conf_t;


/**
 * @brief   MLME-GET.request
 *
 * @details structure for requesting information about a given PIB attribute.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.6.1
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t service;

    /** Confirm to this request. */
    mlme_get_conf_t    confirm;

    pib_id_t           pib_attribute;      /**< PIB Attribute. */
    uint8_t            pib_attribute_idx;  /**< PIB Attribute index. */
} mlme_get_req_t;


/**
 * @brief   MLME-SET.confirm
 *
 * @details structure for reporting the results of an attempt to write a value
 * to a PIB attribute.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.13.2
 */
typedef struct
{
    mac_status_t       status;             /**< Status of operation. */
    pib_id_t           pib_attribute;      /**< PIB Attribute. */
    uint8_t            pib_attribute_idx;  /**< PIB Attribute index. */
} mlme_set_conf_t;


/**
 * @brief   MLME-SET.request
 *
 * @details structure for setting a PIB attribute.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.13.1
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t service;

    /** Confirm to this request. */
    mlme_set_conf_t    confirm;

    pib_id_t           pib_attribute;      /**< PIB Attribute. */
    uint8_t            pib_attribute_idx;  /**< PIB Attribute index. */
    uint8_t          * value;              /**< Attribute value. The value size is calculated
                                                with mlme_pib_attr_size_calc. */
} mlme_set_req_t;


/**
 * @brief Customer's function of confirmation
 *
 * @details The MLME-GET.confirm primitive is generated by the MLME and issued
 * to its next higher layer in response to an MLME-GET.request primitive.
 * This primitive returns a status of either SUCCESS, indicating that the request
 * to read a PIB attribute was successful, or an error code of UNSUPPORTED_ATTRIBUTE.
 * When an error code of UNSUPPORTED_ATTRIBUTE is returned, the PIBAttribute value
 * parameter will be set to length zero. The status values are fully described in 7.1.6.1.3.
 *
 * @param pointer to confirmation primitive
 */
typedef void (* mlme_get_conf_cb_t)(mlme_get_conf_t *);


/**
 * @brief Customer's function of confirmation
 *
 * @details The MLME-SET.confirm primitive is generated by the MLME and issued to its
 * next higher layer in response to an MLME-SET.request primitive. The MLME-SET.confirm
 * primitive returns a status of either SUCCESS, indicating that the requested value was
 * written to the indicated PIB attribute, or the appropriate error code.
 * The status values are fully described in 7.1.13.1.3.
 *
 * @param pointer to confirmation primitive
 */
typedef void (* mlme_set_conf_cb_t)(mlme_set_conf_t *);


/**
 * @brief   MLME-GET request
 *
 * @details Request information about a given PIB attribute.
 *
 * @param[in] req pointer to request structure.
 * @param[in] conf_cb pointer to user callback.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.6.
 * See \a mlme_get() for more details.
 */
void mlme_get_req(mlme_get_req_t * req, mlme_get_conf_cb_t conf_cb);


/**
 * @brief   MLME-SET request
 *
 * @details Request to set a PIB attribute.
 *          After request completion, user callback will be issued with
 *          valid data stored in structure @ref mlme_set_conf_t.
 *
 *          See \a mlme_set() for more details.
 *
 *          In accordance with IEEE Std 802.15.4-2006, section 7.1.13
 *
 * @param[in] req  MLME_SET request structure.
 * @param[in] conf_cb pointer to user callback.
 */
void mlme_set_req(mlme_set_req_t * req, mlme_set_conf_cb_t conf_cb);


/**
 * @brief   Counts MLME attribute size
 *
 * @details This is an implementation-specific function not covered by the standard.
 *
 * @param[in] id attribute id.
 * @param[in] idx index inside the table in case the attribute is a table.
 *
 * @return size of attribute in bytes.
 */
size_t mlme_pib_attr_size_calc(pib_id_t id, uint8_t idx);


/**
 * @brief   Gets parameters from PIB directly (without request - confirm approach)
 *
 * @details Optional. Not covered by a standard.
 *
 * For non-tabled attributes this function will return value to location
 * passed to the last argument.
 *
 * For tabled attributes this function will return pointer to
 * a descriptor structure of corresponding table.
 *
 * @param[in] id attribute id.
 * @param[in] idx index inside the table in case the attribute is a table.
 * @param[out] mem either pointer to memory where attribute value is returned
 *                 (for all attributes except MAC_KEY_TABLE, MAC_DEVICE_TABLE,
 *                 MAC_SECURITY_LEVEL_TABLE), or pointer to memory where pointer
 *                 to attribute storage place is returned.
 *
 * @return status of operation
 */
mac_status_t mlme_get(pib_id_t id, uint8_t idx, void * mem);


/**
 * @brief   Sets parameters to PIB directly (without request - confirm approach)
 *
 * @details Optional. Not covered by a standard.
 *
 *          This function performs copying or replacement of some attribute value
 *          into the PIB base memory.
 *
 *          Note, that all security tables are copied into dynamic memory, that
 *          mlme_set is responsible to allocate. For nested tables copying is done
 *          in a shallow manner (in Python sense). It means that passed \a mac_key_descr_t
 *          is copied as-is, without creating copies of internal tables.
 *          Caller must allocate and prepare all nested tables such as
 *          #MAC_KEY_DEVICE_LIST, #MAC_KEY_ID_LOOKUP_LIST and #MAC_KEY_USAGE_LIST
 *          before calling this function.
 *
 *          Passed attribute value will replace the current one, if the item with such
 *          \a id and \a idx already exists. This function is responsible for
 *          freeing all items during destruction of existing objects.
 *
 * @note    Nested tables may be expanded and reduced with \a mac_table_item_set()
 *          and other similar functions.
 *
 * @param[in] id attribute id.
 * @param[in] idx index inside the table in case the attribute is a table.
 * @param[out] mem pointer to memory for parameter storing.
 *
 * @return status of operation
 */
mac_status_t mlme_set(pib_id_t id, uint8_t idx, void * mem);


#if (CONFIG_SECURE == 1)
/**
 * @brief   Initializes a table. This function MUST be called before accessing
 * to a newly allocated table.
 *
 * @param[out] p_table Pointer to a fresh table.
 */
void mac_table_init(mac_table_t * p_table);

/**
 * @brief   Resets a table, freeing all its elements.
 *
 * @param[in] p_table Pointer to the table to reset.
 * @param[in] id One of #MAC_KEY_TABLE, #MAC_DEVICE_TABLE, #MAC_SECURITY_LEVEL_TABLE,
 * #MAC_KEY_ID_LOOKUP_LIST, #MAC_KEY_DEVICE_LIST, #MAC_KEY_USAGE_LIST to let
 * function know about the size of p_item.
 */
void mac_table_reset(mac_table_t * p_table, mlme_pib_attr_id_t id);

/**
 * @brief   Searches through mac_table_t and finds the item with requested idx.
 *
 * @param[in] p_table Table to search through.
 * @param[in] idx Item idx to match.
 *
 * @return Pointer to mac_table_item_t with requested idx or NULL if such
 * an item cannot be found.
 */
mac_table_item_t * mac_table_idx_get(const mac_table_t * p_table, uint8_t idx);

/**
 * @brief   Sets new value item for mac_table_t.
 *
 * @param[out] p_table Pointer to the table to add item to.
 * @param[in] p_item Pointer to a new item. This item must include appropriate idx
 * (less than the maximum table size).
 * @param[in] id One of #MAC_KEY_TABLE, #MAC_DEVICE_TABLE, #MAC_SECURITY_LEVEL_TABLE,
 * #MAC_KEY_ID_LOOKUP_LIST, #MAC_KEY_DEVICE_LIST, #MAC_KEY_USAGE_LIST to let
 * function know about the size of p_item.
 * @param[in] idx Item index inside the selected table.
 *
 * @details This function performs a "deep copy" of passed table item to conform with
 * mlme_set behavior. New copy resides in the heap memory. If an item with requested
 * idx has been already set earlier, this function frees the old item and pushes
 * a new one instead.
 *
 * @retval #MAC_INVALID_INDEX if idx exceeds allowed maximum number of items in
 * the table.
 * @retval #MAC_LIMIT_REACHED if there is no enough dynamic memory to put this item
 * into the security table.
 * @retval #MAC_SUCCESS if insertion has been performed successfully.
 */
mac_status_t mac_table_item_set(mac_table_t * p_table,
                                const mac_table_item_t * p_item,
                                mlme_pib_attr_id_t id,
                                uint8_t idx);

/**
 * @brief   Removes an item from a mac_table_t instance and frees all resources,
 * associated with this item.
 *
 * @param[out] p_table Pointer to the table to remove item from.
 * @param[in] id One of #MAC_KEY_TABLE, #MAC_DEVICE_TABLE, #MAC_SECURITY_LEVEL_TABLE,
 * #MAC_KEY_ID_LOOKUP_LIST, #MAC_KEY_DEVICE_LIST, #MAC_KEY_USAGE_LIST to let
 * function perform down-casting correctly.
 * @param[in] idx Item index inside of selected table.
 *
 * @retval #MAC_INVALID_INDEX if passed index is not found in the table or exceeds
 * the allowed maximum.
 * @retval #MAC_SUCCESS if no errors happen during removing.
 */
mac_status_t mac_table_item_remove(mac_table_t * p_table,
                                   mlme_pib_attr_id_t id,
                                   uint8_t idx);

/**
 * @brief   Gets first available item from a table.
 *
 * @details This function might be used along with \a mac_table_item_next to
 * search through some table.
 *
 * @param[in] p_table Pointer to a MAC table.
 *
 * @return Pointer to the first table item or NULL if the table is empty.
 */
mac_table_item_t * mac_table_item_front(const mac_table_t * p_table);

/**
 * @brief   Returns the next available item in table.
 *
 * @details MAC tables are stored unsorted in memory, so there is no guarantee that
 * index of the next item is always greater or smaller than the current one.
 * Items are not stored in chronological order either.
 *
 * @param[in] p_table Pointer to a table to select item from.
 * @param[in] p_current_item Pointer to the current item.
 *
 * @return Pointer to the next item in table or NULL, if the item is the last one.
 */
mac_table_item_t * mac_table_item_next(const mac_table_t * p_table,
                                       const mac_table_item_t * p_current_item);

/**
 * @brief   Gets number of items used inside mac_table_t.
 *
 * @param[in] p_table Pointer to interested table.
 *
 * @return 8-bit integer equal to number of items inside the table that have
 * been set at least once.
 */
static inline uint8_t mac_table_size_get(const mac_table_t * p_table)
{
    ASSERT(p_table != NULL);

    return p_table->size;
}

/**
 * @brief   This function checks if a MAC table is empty.
 *
 * @param[in] p_table Pointer to a MAC table.
 *
 * @return true if there are no items inside table, false otherwise.
 */
static inline bool mac_table_is_empty(const mac_table_t * p_table)
{
    ASSERT(p_table != NULL);

    return sys_queue_is_empty(&p_table->queue);
}
#endif

/** @} */

#endif // MAC_MLME_PIB_H_INCLUDED
