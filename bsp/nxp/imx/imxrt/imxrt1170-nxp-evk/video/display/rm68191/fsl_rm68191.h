/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RM68191_H_
#define _FSL_RM68191_H_

#include "fsl_display.h"
#include "fsl_mipi_dsi_cmd.h"

/*
 * Change log:
 *
 *   1.1.0
 *     - Fix MISRA-C 2012 issues.
 *     - Change rm68191_resource_t structure.
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief RM68191 resource.
 */
typedef struct _rm68191_resource
{
    mipi_dsi_device_t *dsiDevice;      /*!< MIPI DSI device. */
    void (*pullResetPin)(bool pullUp); /*!< Function to pull reset pin high or low. */
    void (*pullPowerPin)(bool pullUp); /*!< Function to pull power pin high or low. */
} rm68191_resource_t;

extern const display_operations_t rm68191_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t RM68191_Init(display_handle_t *handle, const display_config_t *config);

status_t RM68191_Deinit(display_handle_t *handle);

status_t RM68191_Start(display_handle_t *handle);

status_t RM68191_Stop(display_handle_t *handle);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_RM68191_H_ */
