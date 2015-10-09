/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/*******************************************************************************
 *
 * $Id:$
 *
 ******************************************************************************/
/**
 *   @defgroup  Start_Manager start_manager
 *   @brief     Motion Library - Start Manager
 *              Start Manager
 *
 *   @{
 *       @file start_manager.c
 *       @brief This handles all the callbacks when inv_start_mpl() is called.
 */


#include <string.h>
#include "log.h"
#include "start_manager.h"

typedef inv_error_t (*inv_start_cb_func)();
struct inv_start_cb_t {
    int num_cb;
    inv_start_cb_func start_cb[INV_MAX_START_CB];
};

static struct inv_start_cb_t inv_start_cb;

/** Initilize the start manager. Typically called by inv_start_mpl();
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_init_start_manager(void)
{
    memset(&inv_start_cb, 0, sizeof(inv_start_cb));
    return INV_SUCCESS;
}

/** Removes a callback from start notification
* @param[in] start_cb function to remove from start notification
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_unregister_mpl_start_notification(inv_error_t (*start_cb)(void))
{
    int kk;

    for (kk=0; kk<inv_start_cb.num_cb; ++kk) {
        if (inv_start_cb.start_cb[kk] == start_cb) {
            // Found the match
            if (kk != (inv_start_cb.num_cb-1)) {
                memmove(&inv_start_cb.start_cb[kk],
                    &inv_start_cb.start_cb[kk+1],
                    (inv_start_cb.num_cb-kk-1)*sizeof(inv_start_cb_func));
            }
            inv_start_cb.num_cb--;
            return INV_SUCCESS;
        }
    }
    return INV_ERROR_INVALID_PARAMETER;
}

/** Register a callback to receive when inv_start_mpl() is called.
* @param[in] start_cb Function callback that will be called when inv_start_mpl() is
*            called.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_register_mpl_start_notification(inv_error_t (*start_cb)(void))
{
    if (inv_start_cb.num_cb >= INV_MAX_START_CB)
        return INV_ERROR_INVALID_PARAMETER;

    inv_start_cb.start_cb[inv_start_cb.num_cb] = start_cb;
    inv_start_cb.num_cb++;
    return INV_SUCCESS;
}

/** Callback all the functions that want to be notified when inv_start_mpl() was
* called.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_execute_mpl_start_notification(void)
{
    inv_error_t result,first_error;
    int kk;

    first_error = INV_SUCCESS;

    for (kk = 0; kk < inv_start_cb.num_cb; ++kk) {
        result = inv_start_cb.start_cb[kk]();
        if (result && (first_error == INV_SUCCESS)) {
            first_error = result;
        }
    }
    return first_error;
}

/**
 * @}
 */