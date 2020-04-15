/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SDMMC_H_
#define _FSL_SDMMC_H_

#include "fsl_card.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Reverse byte sequence in uint32_t */
#define SWAP_WORD_BYTE_SEQUENCE(x) (__REV(x))
/*! @brief Reverse byte sequence for each half word in uint32_t */
#define SWAP_HALF_WROD_BYTE_SEQUENCE(x) (__REV16(x))

/*! @brief Maximum loop count to check the card operation voltage range */
#define FSL_SDMMC_MAX_VOLTAGE_RETRIES (1000U)
/*! @brief Maximum loop count to send the cmd */
#define FSL_SDMMC_MAX_CMD_RETRIES (10U)
/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Selects the card to put it into transfer state.
 *
 * @param base HOST peripheral base address.
 * @param transfer HOST transfer function.
 * @param relativeAddress Relative address.
 * @param isSelected True to put card into transfer state.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SelectCard(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer, uint32_t relativeAddress, bool isSelected);

/*!
 * @brief Sends an application command.
 *
 * @param base HOST peripheral base address.
 * @param transfer HOST transfer function.
 * @param relativeAddress Card relative address.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_CardNotSupport Card doesn't support.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SendApplicationCommand(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer, uint32_t relativeAddress);

/*!
 * @brief Sets the block count.
 *
 * @param base HOST peripheral base address.
 * @param transfer HOST transfer function.
 * @param blockCount Block count.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SetBlockCount(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer, uint32_t blockCount);

/*!
 * @brief Sets the card to be idle state.
 *
 * @param base HOST peripheral base address.
 * @param transfer HOST transfer function.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_GoIdle(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer);

/*!
 * @brief Sets data block size.
 *
 * @param base HOST peripheral base address.
 * @param transfer HOST transfer function.
 * @param blockSize Block size.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SetBlockSize(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer, uint32_t blockSize);

/*!
 * @brief Sets card to inactive status
 *
 * @param base HOST peripheral base address.
 * @param transfer HOST transfer function.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SetCardInactive(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer);

/*!
 * @brief provide a simple delay function for sdmmc
 *
 * @param num Delay num*10000.
 */
void SDMMC_Delay(uint32_t num);

/*!
 * @brief provide a voltage switch function for SD/SDIO card
 *
 * @param base HOST peripheral base address.
 * @param transfer HOST transfer function.
 */
status_t SDMMC_SwitchVoltage(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer);

/*!
 * @brief excute tuning
 *
 * @param base HOST peripheral base address.
 * @param transfer Host transfer function
 * @param tuningCmd Tuning cmd
 * @param blockSize Tuning block size
 */
status_t SDMMC_ExecuteTuning(HOST_TYPE *base, HOST_TRANSFER_FUNCTION transfer, uint32_t tuningCmd, uint32_t blockSize);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_SDMMC_H_ */
