/**
 ****************************************************************************************
 *
 * @file l2cm_int.h
 *
 * @brief Header file - L2CM internal.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef L2CM_INT_H_
#define L2CM_INT_H_

/**
 ****************************************************************************************
 * @addtogroup L2C_INT Logical Link Control and Adaptation Protocol internals
 * @ingroup HOST
 * @brief Logical Link Control and Adaptation Protocol - Internal API.
 *
 * @{
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_L2CM)
#include <stdbool.h>
#include <stdint.h>
#include "ble_arch.h"
#include "l2cm.h"
//

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

/// L2CAP Manager environment structure to be saved
struct l2cm_env_tag
{
    #if (BLE_L2CC)
    /// bit field used to know per connection if TX activity is on-going
    uint32_t    con_tx_state;
    #endif //  (BLE_L2CC)
    /// Lower Layer buffers length
    uint16_t    le_acl_data_pkt_len;
    /// Total number of available Lower Layer buffers
    uint16_t    le_acl_total_nb_acl_pkt;
    /// Number of available Lower Layer buffers
    uint16_t    nb_buffer_avail;
 };

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */
extern struct l2cm_env_tag l2cm_env;
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Acquire low layer LE ACL packet
 ****************************************************************************************
 */
__INLINE void l2cm_buffer_acquire(void)
{
    l2cm_env.nb_buffer_avail--;
}

/**
 ****************************************************************************************
 * @brief Release low layer LE ACL packet
 *
 * @parm[in] nb Number of buffer to release.
 ****************************************************************************************
 */
__INLINE void l2cm_buffer_release(uint16_t nb)
{
    l2cm_env.nb_buffer_avail += nb;
}


/**
 ****************************************************************************************
 * @brief Retrieve low layer LE ACL Buffers size
 *
 * @return size of LE ACL Buffers
 ****************************************************************************************
 */
 __INLINE uint16_t l2cm_get_buffer_size(void)
 {
     return l2cm_env.le_acl_data_pkt_len;
 }


/**
 ****************************************************************************************
 * @brief Set if TX queue for specific connection is empty or not.
 *
 * If not empty, it will request L2CM to start transmission of buffers
 *
 * @param[in] conidx           Connection index
 * @param[in] busy             False if TX buffer queue is empty, True else
 *
 ****************************************************************************************
 */
void l2cm_tx_status(uint8_t conidx, bool busy);

/// @} L2CM_INT

#endif //(BLE_L2CM)

#endif // L2CM_INT_H_
