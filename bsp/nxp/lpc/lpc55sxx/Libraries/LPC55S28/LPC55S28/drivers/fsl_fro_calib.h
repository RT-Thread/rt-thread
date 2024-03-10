/*
 * Copyright (c) 2017, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_FRO_CALIB_H_
#define _FSL_FRO_CALIB_H_

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include <stdint.h>

/*!
 * @addtogroup power
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief FRO_CALIB driver version 1.0.0. */
#define FSL_FRO_CALIB_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.fro_calib"
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Returns the version of the FRO Calibration library */
unsigned int fro_calib_Get_Lib_Ver(void);

/* ctimer instance */
/* ctimer clock frquency in KHz */
void Chip_TIMER_Instance_Freq(CTIMER_Type *base, unsigned int ctimerFreq);

/* USB_SOF_Event */
/* Application software should be written to make sure the USB_SOF_EVENT() is */
/* being called with lower interrupt latency for calibration to work properly */
void USB_SOF_Event(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _FSL_FRO_CALIB_H_ */
