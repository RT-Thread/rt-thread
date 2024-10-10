/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_HX8394_H_
#define _FSL_HX8394_H_

#include "fsl_display.h"
#include "fsl_mipi_dsi_cmd.h"

/*
 * Change log:
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief HX8394 resource.
 */
typedef struct _hx8394_resource
{
    mipi_dsi_device_t *dsiDevice;      /*!< MIPI DSI device. */
    void (*pullResetPin)(bool pullUp); /*!< Function to pull reset pin high or low. */
    void (*pullPowerPin)(bool pullUp); /*!< Function to pull power pin high or low. */
} hx8394_resource_t;

extern const display_operations_t hx8394_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t HX8394_Init(display_handle_t *handle, const display_config_t *config);

status_t HX8394_Deinit(display_handle_t *handle);

status_t HX8394_Start(display_handle_t *handle);

status_t HX8394_Stop(display_handle_t *handle);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_HX8394_H_ */
