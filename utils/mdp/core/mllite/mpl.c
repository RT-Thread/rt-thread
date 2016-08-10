/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
/**
 *   @defgroup  MPL mpl
 *   @brief     Motion Library - Start Point
 *              Initializes MPL.
 *
 *   @{
 *       @file  mpl.c
 *       @brief MPL start point.
 */

#include "storage_manager.h"
#include "log.h"
#include "mpl.h"
#include "start_manager.h"
#include "data_builder.h"
#include "results_holder.h"
#include "mlinclude.h"

/**
 * @brief  Initializes the MPL. Should be called first and once 
 * @return Returns INV_SUCCESS if successful or an error code if not.
 */
inv_error_t inv_init_mpl(void)
{
    inv_init_storage_manager();

    /* initialize the start callback manager */
    INV_ERROR_CHECK(inv_init_start_manager());

    /* initialize the data builder */
    INV_ERROR_CHECK(inv_init_data_builder());

    INV_ERROR_CHECK(inv_enable_results_holder());

    return INV_SUCCESS;
}

const char ml_ver[] = "InvenSense MA 5.1.2";

/**
 *  @brief  used to get the MPL version.
 *  @param  version     a string where the MPL version gets stored.
 *  @return INV_SUCCESS if successful or a non-zero error code otherwise.
 */
inv_error_t inv_get_version(char **version)
{
    INVENSENSE_FUNC_START;
    /* cast out the const */
    *version = (char *)&ml_ver;
    return INV_SUCCESS;
}

/** 
 *  @brief  Starts the MPL. Typically called after inv_init_mpl() or after a
 *          inv_stop_mpl() to start the MPL back up an running.
 *  @return INV_SUCCESS if successful or a non-zero error code otherwise.
 */
inv_error_t inv_start_mpl(void)
{
    INV_ERROR_CHECK(inv_execute_mpl_start_notification());
    return INV_SUCCESS;
}

/**
 * @}
 */