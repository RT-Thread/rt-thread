/**
 ****************************************************************************************
 *
 * @file l2cm.h
 *
 * @brief Header file - L2CM.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef L2CM_H_
#define L2CM_H_

/**
 ****************************************************************************************
 * @addtogroup L2C Logical Link Control and Adaptation Protocol
 * @ingroup HOST
 * @brief Logical Link Control and Adaptation Protocol - BLE Host.
 *
 * The L2C module is responsible for L2CAP provides connection-oriented
 * and connection-less data services to upper layer protocols with protocol
 * multiplexing capability and segmentation and re-assembly operation.
 *
 * @{
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @addtogroup L2CM L2CAP Manager
 * @ingroup L2C
 * @brief L2CAP block for signaling and resource management functions
 *
 * The L2CM is an internal L2CAP block responsible for managing
 * the signaling messages and propagation of connection and disconnection
 * related L2CAP messages within the Host.
 *
 * @{
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_L2CM)
#include <stdbool.h>
#include <stdint.h>

/*
 * INCLUDE FILES
 ****************************************************************************************
 */


/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Create and Initialize the L2CAP manager task.
 *
 * @param[in] reset   true if it's requested by a reset; false if it's boot initialization
 *
 ****************************************************************************************
 */
void l2cm_init(bool reset);



/**
 ****************************************************************************************
 * @brief Allocates an L2CAP resource.
 *
 * @param[in] conidx           connection index
 *
 ****************************************************************************************
 */
void l2cm_create(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief De-initializes the L2CAP resources for specified link.
 *
 * @param[in] conidx           connection index
 *
 ****************************************************************************************
 */
void l2cm_cleanup(uint8_t conidx);


/**
 ****************************************************************************************
 * @brief Sets link layer buffer size capacity
 *
 * @param[in] pkt_len           length of the packet
 * @param[in] nb_acl            number of acl
 *
 ****************************************************************************************
 */
void l2cm_set_link_layer_buff_size(uint16_t pkt_len, uint16_t nb_acl);

/**
 ****************************************************************************************
 * @brief Retrieve number of low layer buffer available
 *
 * @return Number of low layer buffer available
 ****************************************************************************************
 */
uint16_t l2cm_get_nb_buffer_available(void);

/// @} L2CM

#endif //(BLE_L2CM)

#endif // L2CM_H_
