/**
 ****************************************************************************************
 *
 * @file gattm.h
 *
 * @brief Header file - GATT Manager.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef GATTM_H_
#define GATTM_H_



/**
 ****************************************************************************************
 * @addtogroup GATTM Generic Attribute Profile Manager
 * @ingroup GATT
 * @brief Generic Attribute Profile.
 *
 * The GATT manager module is responsible for providing an API for all action operations
 * not related to a connection. It's responsible to managing internal database.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
/* kernel task */
#include "rwip_config.h"

#if (BLE_CENTRAL || BLE_PERIPHERAL)
#include <stdint.h>
#include <stdbool.h>

/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialization of the GATT manager module.
 * This function performs all the initialization steps of the GATT module.
 *
 * @param[in] reset  true if it's requested by a reset; false if it's boot initialization
 *
 ****************************************************************************************
 */
void gattm_init(bool reset);


/**
 ****************************************************************************************
 * @brief Initialize GATT attribute database
 *
 * @param[in] start_hdl  Service Start Handle
 * @param[in] svc_chg_en Service Change feature enabled
 *
 * @return status code of attribute database initialization
 * Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If database creation succeeds.
 *  - @ref ATT_ERR_INVALID_HANDLE: If start_hdl given in parameter + nb of attribute override
 *                            some existing services handles.
 *  - @ref ATT_ERR_INSUFF_RESOURCE: There is not enough memory to allocate service buffer.
 *                           or of new attribute cannot be added because all expected
 *                           attributes already add
 ****************************************************************************************
 */
uint8_t gattm_init_attr(uint16_t start_hdl, bool svc_chg_en);

/**
 ****************************************************************************************
 * @brief Initialize GATT resources for connection.
 *
 * @param[in] conidx connection record index
 * @param[in] role   device role after connection establishment
 *
 ****************************************************************************************
 */
void gattm_create(uint8_t conidx);
/**
 ****************************************************************************************
 * @brief Cleanup GATT resources for connection
 *
 * @param[in] conidx   connection record index
 *
 ****************************************************************************************
 */
void gattm_cleanup(uint8_t conidx);


#if (BLE_ATTS)
/**
 ****************************************************************************************
 * @brief Return the start handle of the GATT service in the database *
 ****************************************************************************************
 */
uint16_t gattm_svc_get_start_hdl(void);
#endif //(BLE_ATTS)
#endif /* (BLE_CENTRAL || BLE_PERIPHERAL) */

/// @} GATTM
#endif // GATTM_H_
