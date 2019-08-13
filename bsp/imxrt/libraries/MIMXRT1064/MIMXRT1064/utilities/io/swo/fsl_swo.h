/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _FSL_SWO_H_
#define _FSL_SWO_H_

#include "fsl_common.h"

/*!
 * @addtogroup debugconsole
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* swo protocol */
enum _swo_protocol
{
    kSWO_ProtocolManchester = 1U, /*!< SWO manchester protocol */
    kSWO_ProtocolNrz = 2U,        /*!< SWO UART/NRZ protocol */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief io init function.
 *
 * Call this function to init SWO.
 *
 * @param port port used to transfer data
 * @param baudRate SWO clock
 * @param clkSrcFreq core clock frequency
 */
status_t SWO_Init(uint32_t port, uint32_t baudRate, uint32_t clkSrcFreq);

/*!
 * @brief Deinit IO.
 *
 * Call this function to Deinit SWO.
 *
 * @param port port to deinit.
 * @return deinit status
 */
void SWO_Deinit(uint32_t port);

/*!
 * @brief io transfer function.
 *
 * Call this function to print log.
 *
 * @param port port used to transfer data
 * @param ch  transfer buffer pointer
 * @param size transfer size
 */
status_t SWO_SendBlocking(uint32_t port, uint8_t *ch, size_t size);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_SWO_H_ */
