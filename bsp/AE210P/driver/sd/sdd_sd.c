/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Sep.26.2007     Created.
 ****************************************************************************/

/*****************************************************************************
 *
 * FILE NAME                                         VERSION
 *
 *   sdd_sd.c
 *
 * DESCRIPTION
 *
 *   Secure digital card specification 2.0 definition.
 *
 *   Currently only Secure Digital Memory standards are well-defined.
 *   Remaining spec mostly are left for future developers.
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   None
 *
 ****************************************************************************/
#include "sdd.h"
#include "sdd_sd.h"

/*
 * If SDD_SMALL_FOOTPRINT is defined, SD command routines are defined as
 * macros which will be redirect to a general command issuing routine.
 *
 * If performance is required, set SDD_SMALL_FOOTPRINT to 0.  The SD command
 * issuing routines are then a set of expanded code.
 */
#if (SDD_SMALL_FOOTPRINT)
#define SDC_INLINE static _inline
#else /* SDD_SMALL_FOOTPRINT */
#define SDC_INLINE static
#endif /* SDD_SMALL_FOOTPRINT */

/* Local Helper Routines */
SDC_INLINE uint32_t _sd_cmd(uint32_t cmd)
{
	uint32_t retry_cnt = 0;

	/* Make sure card exists */
	if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
		return SDD_CARD_REMOVED;

	/* Clear SDC status bits */
	OUT32(SDC_CLEAR, SDC_RSP_CRC_FAIL_MASK | SDC_RSP_TIMEOUT_MASK |
			SDC_RSP_CRC_OK_MASK | SDC_CMD_SENT_MASK);
	/*OUT32(SDC_CLEAR, SDC_CLEAR_ALL); */

	/* Send command */
	OUT32(SDC_CMD, cmd);

	/* Wait until the command is on the way to the card ... */
	while (retry_cnt++ < SD_CMD_MAX_RETRY_COUNT) {

		/* Make sure card exists */
		if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
			return SDD_CARD_REMOVED;

		/* Get new status of SDC */
		if (GETB32(SDC_STATUS, SDC_SR_CMD_SENT_BIT) != 0)
			return HAL_SUCCESS;
	}

	return SDD_CMD_TIMEOUT;
}

SDC_INLINE uint32_t _sd_cmd_arg(uint32_t cmd, uint32_t arg)
{
	uint32_t retry_cnt = 0;

	/* Make sure card exists */
	if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
		return SDD_CARD_REMOVED;

	/* Clear SDC status bits */
	OUT32(SDC_CLEAR, SDC_RSP_CRC_FAIL_MASK | SDC_RSP_TIMEOUT_MASK |
			SDC_RSP_CRC_OK_MASK | SDC_CMD_SENT_MASK);
	/*OUT32(SDC_CLEAR, SDC_CLEAR_ALL); */

	/* Prepare Argument */
	OUT32(SDC_CMD_ARG, arg);

	/* Send command */
	OUT32(SDC_CMD, cmd);

	/* Wait until the command is on the way to the card ... */
	while (retry_cnt++ < SD_CMD_MAX_RETRY_COUNT) {

		/* Make sure card exists */
		if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
			return SDD_CARD_REMOVED;

		/* Get new status of SDC */
		if (GETB32(SDC_STATUS, SDC_SR_CMD_SENT_BIT) != 0)
			return HAL_SUCCESS;
	}

	return SDD_CMD_TIMEOUT;
}

SDC_INLINE uint32_t _sd_cmd_r32(uint32_t cmd, SD_R32 * rsp)
{
	uint32_t retry_cnt = 0;
	uint32_t sdc_sr = 0;

	/* Make sure card exists */
	if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
		return SDD_CARD_REMOVED;

	/* Clear SDC status bits */
	OUT32(SDC_CLEAR, SDC_RSP_CRC_FAIL_MASK | SDC_RSP_TIMEOUT_MASK |
			SDC_RSP_CRC_OK_MASK | SDC_CMD_SENT_MASK);
	/*OUT32(SDC_CLEAR, SDC_CLEAR_ALL); */

	/* Send command */
	OUT32(SDC_CMD, cmd);

	/* Wait until the command is responsed ... */
	while (retry_cnt++ < SD_CMD_MAX_RETRY_COUNT) {

		sdc_sr = IN32(SDC_STATUS);

		/* Make sure card exists */
		if (sdc_sr & SDC_SR_CARD_DETECT_BIT)
			return SDD_CARD_REMOVED;

		/* Check error status */
		if (sdc_sr & SDC_SR_RSP_CRC_OK_MASK) {

			rsp->r[0] = IN32(SDC_R0);
			return HAL_SUCCESS;
		}
		else if (sdc_sr & SDC_SR_RSP_CRC_FAIL_MASK) {

			return SDD_RSP_CRC_ERROR;
		}
		else if (sdc_sr & SDC_SR_RSP_TIMEOUT_MASK) {

			return SDD_RSP_TIMEOUT;
		}
	}

	return SDD_CMD_TIMEOUT;
}

SDC_INLINE uint32_t _sd_cmd_arg_r32(uint32_t cmd, uint32_t arg, SD_R32 * rsp)
{
	uint32_t sdc_sr = 0;

	/* Make sure card exists */
	if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
		return SDD_CARD_REMOVED;

	/* Clear SDC status bits */
	OUT32(SDC_CLEAR, SDC_RSP_CRC_FAIL_MASK | SDC_RSP_TIMEOUT_MASK |
			SDC_RSP_CRC_OK_MASK);
	/*OUT32(SDC_CLEAR, SDC_CLEAR_ALL); */

	/* Prepare Argument */
	OUT32(SDC_CMD_ARG, arg);

	/* Send command */
	OUT32(SDC_CMD, cmd);

	/* Wait until the command is responsed ... */
	while (1) {

//		_nds_kwait(0x1000);	/* hw need delay ? */

		sdc_sr = IN32(SDC_STATUS);

		/* Make sure card exists */
		if (sdc_sr & SDC_SR_CARD_DETECT_BIT)
			return SDD_CARD_REMOVED;

		/* Check error status */
		if (sdc_sr & SDC_SR_RSP_CRC_OK_MASK) {

			rsp->r[0] = IN32(SDC_R0);
			return HAL_SUCCESS;
		}
		else if (sdc_sr & SDC_SR_RSP_CRC_FAIL_MASK) {

			return SDD_RSP_CRC_ERROR;
		}
		else if (sdc_sr & SDC_SR_RSP_TIMEOUT_MASK) {

			return SDD_RSP_TIMEOUT;
		}
	}

	return SDD_CMD_TIMEOUT;
}

SDC_INLINE uint32_t _sd_cmd_r128(uint32_t cmd, SD_R128 * rsp)
{
	uint32_t retry_cnt = 0;
	uint32_t sdc_sr = 0;

	/* Make sure card exists */
	if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
		return SDD_CARD_REMOVED;

	/* Clear SDC status bits */
	OUT32(SDC_CLEAR, SDC_RSP_CRC_FAIL_MASK | SDC_RSP_TIMEOUT_MASK |
			SDC_RSP_CRC_OK_MASK | SDC_CMD_SENT_MASK);
	/*OUT32(SDC_CLEAR, SDC_CLEAR_ALL); */

	/* Send command */
	OUT32(SDC_CMD, cmd);

	/* Wait until the command is responsed ... */
	while (retry_cnt++ < SD_CMD_MAX_RETRY_COUNT) {

		sdc_sr = IN32(SDC_STATUS);

		/* Make sure card exists */
		if (sdc_sr & SDC_SR_CARD_DETECT_BIT)
			return SDD_CARD_REMOVED;

		/* Check error status */
		if (sdc_sr & SDC_SR_RSP_CRC_OK_MASK) {

			rsp->r[0] = IN32(SDC_R0);
			rsp->r[1] = IN32(SDC_R1);
			rsp->r[2] = IN32(SDC_R2);
			rsp->r[3] = IN32(SDC_R3);

			return HAL_SUCCESS;
		}
		else if (sdc_sr & SDC_SR_RSP_CRC_FAIL_MASK) {

			return SDD_RSP_CRC_ERROR;
		}
		else if (sdc_sr & SDC_SR_RSP_TIMEOUT_MASK) {

			return SDD_RSP_TIMEOUT;
		}
	}

	return SDD_CMD_TIMEOUT;
}

SDC_INLINE uint32_t _sd_cmd_arg_r128(uint32_t cmd, uint32_t arg, SD_R128 * rsp)
{
	uint32_t retry_cnt = 0;
	uint32_t sdc_sr = 0;

	/* Make sure card exists */
	if (GETB32(SDC_STATUS, SDC_SR_CARD_DETECT_BIT))
		return SDD_CARD_REMOVED;

	/* Clear SDC status bits */
	OUT32(SDC_CLEAR, SDC_RSP_CRC_FAIL_MASK | SDC_RSP_TIMEOUT_MASK |
			SDC_RSP_CRC_OK_MASK | SDC_CMD_SENT_MASK);
	/*OUT32(SDC_CLEAR, SDC_CLEAR_ALL); */

	/* Prepare Argument */
	OUT32(SDC_CMD_ARG, arg);

	/* Send command */
	OUT32(SDC_CMD, cmd);

	/* Wait until the command is responsed ... */
	while (retry_cnt++ < SD_CMD_MAX_RETRY_COUNT) {

		sdc_sr = IN32(SDC_STATUS);

		/* Make sure card exists */
		if (sdc_sr & SDC_SR_CARD_DETECT_BIT)
			return SDD_CARD_REMOVED;

		/* Check error status */
		if (sdc_sr & SDC_SR_RSP_CRC_OK_MASK) {

			rsp->r[0] = IN32(SDC_R0);
			rsp->r[1] = IN32(SDC_R1);
			rsp->r[2] = IN32(SDC_R2);
			rsp->r[3] = IN32(SDC_R3);

			return HAL_SUCCESS;
		}
		else if (sdc_sr & SDC_SR_RSP_CRC_FAIL_MASK) {

			return SDD_RSP_CRC_ERROR;
		}
		else if (sdc_sr & SDC_SR_RSP_TIMEOUT_MASK) {

			return SDD_RSP_TIMEOUT;
		}
	}

	return SDD_CMD_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd0
 *
 * DESCRIPTION
 *
 *   This function issues SD command GO_IDLE_STATE: Reset all cards to idle
 *   state.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     idle -> idle
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     None
 *
 * INPUTS
 *
 *   None.
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd0(void)
{
	return _sd_cmd(SDC_CMD0_GO_IDLE_STATE);
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd2
 *
 * DESCRIPTION
 *
 *   This function issues SD command ALL_SEND_CID: Ask any card to send the
 *   CID numbers
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     ready -> identification
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     R2 [127:1] CID
 *
 * INPUTS
 *
 *   cid    : Pointer to SD_CID struct.
 *
 * OUTPUTS
 *
 *   cid    : SD_CID struct which holds the card's CID register value.
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd2(SD_CID * cid)
{
	return _sd_cmd_r128(SDC_CMD2_ALL_SEND_CID, cid);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd3
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_RELATIVE_ADDR: Ask the card to
 *   publish a new RCA.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     identification -> standby
 *     standy -> standby
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     R6 [23:08] card status bits: 23, 22, 19, 12:0
 *        [39:24] New publishded RCA
 *
 * INPUTS
 *
 *   rca    : Pointer to SD_R32 struct to receive RCA.
 *
 * OUTPUTS
 *
 *   rca    : SD_R32 struct where RCA will be placed at [31:16].
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd3(SD_R32 * rca)
{
	return _sd_cmd_r32(SDC_CMD3_SEND_RELATIVE_ADDR, rca);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd4
 *
 * DESCRIPTION
 *
 *   This function issues SD command SET_DSR: Program DSR of all cards.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     standy -> standby
 *
 *   Argument:
 *     [31:16] DSR
 *
 *   Response:
 *     None
 *
 * INPUTS
 *
 *   dsr    : uint32_t value where DSR is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd4(uint32_t dsr)
{
	return _sd_cmd_arg(SDC_CMD4_SET_DSR, dsr);
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd7
 *
 * DESCRIPTION
 *
 *   This function issues SD command SELECT/DESELECT_CARD: Toggles between
 *   standby and transfer states or between programming and disconnect
 *   states.  Cards with matching RCA is selected, otherwise deselected.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     selected card:
 *       standby -> transfer
 *       disconnected -> programming
 *     deselected card
 *       standby -> standby
 *       transfer -> standby
 *       sending-data -> standby
 *       programming -> disconnected
 *
 *   Argument:
 *     [31:16] RCA
 *
 *   Response:
 *     R1b [39:8] card status
 *         DAT0 busy signal
 *
 * INPUTS
 *
 *   rca    : SD_R32 struct where RCA is at [31:16].
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd7(uint32_t rca, SD_R32 * csr)
{
	uint32_t status = _sd_cmd_arg_r32(SDC_CMD7_SELECT_DESELECT_CARD, rca, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd8
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_IF_COND: Send VHS to SD card before
 *   issuing ACMD41 during initialization and identification process.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     idle -> idle
 *
 *   Argument:
 *     [11:8] VHS (see R7 bellow)
 *     [ 7:0] Arbitrary Check Pattern (10101010b(0xaa) is suggested)
 *
 *   Response:
 *     R7 [19:16] voltage accepted (VHS)
 *                  0001b (0x01) -> 2.7-3.6v
 *                  others are reserved or undefined
 *
 * INPUTS
 *
 *   vhs_arg: uint32_t value with VHS at [11:8] and check-ptn at [7:0].
 *   vhs_rsp: Pointer to SD_R32 struct to hold the response.
 *
 * OUTPUTS
 *
 *   vhs_rsp: SD_R32 struct with VHS at [11:8] and check-ptn at [7:0].
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd8(uint32_t vhs_arg, SD_R32 * vhs_rsp)
{
	return _sd_cmd_arg_r32(SDC_CMD8_SEND_IF_COND, vhs_arg, vhs_rsp);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd9
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_CSD: Ask addressed card to send its
 *   CSD on the command line.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     standby -> standby
 *
 *   Argument:
 *     [31:16] RCA
 *
 *   Response:
 *     R2 [127:1] CSD
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *   csd    : Pointer to SD_CSD struct.
 *
 * OUTPUTS
 *
 *   csd    : SD_CSD struct which contains CSD response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd9(uint32_t rca, SD_CSD * csd)
{
	return _sd_cmd_arg_r128(SDC_CMD9_SEND_CSD, rca, csd);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd10
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_CID: Ask addressed card to send its
 *   CID on the command line.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     standby -> standby
 *
 *   Argument:
 *     [31:16] RCA
 *
 *   Response:
 *     R2 [127:1] CID
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *   cid    : Pointer to SD_CID struct.
 *
 * OUTPUTS
 *
 *   cid    : SD_CID struct which contains CID response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd10(uint32_t rca, SD_CID * cid)
{
	return _sd_cmd_arg_r128(SDC_CMD10_SEND_CID, rca, cid);
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd12
 *
 * DESCRIPTION
 *
 *   This function issues SD command STOP_TRANSMISSION: Forces the card to
 *   stop transmission.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     snedning-data -> transfer
 *     receiving-data -> programming
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     R1b [39:8] card status
 *         DAT0 busy signal
 *
 * INPUTS
 *
 *   csr    : Pointer to SD_R32 value.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd12(SD_R32 * csr)
{
	uint32_t status = _sd_cmd_r32(SDC_CMD12_STOP_TRANSMISSION, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))	/* todo: ok to check all error bits */
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd13
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_STATUS: Ask the card to send its
 *   card status.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     standby -> standby
 *     transfer -> transfer
 *     sending-data -> sending-data
 *     receiving-data -> receieving-data
 *     programming -> programming
 *     disconnect -> disconnect
 *
 *   Argument:
 *     [31:16] RCA
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *   csr    : Pointer to SD_R32 to receive CSR.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 which holds the received CSR.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd13(uint32_t rca, SD_R32 * csr)
{
	uint32_t status = _sd_cmd_arg_r32(SDC_CMD13_SEND_STATUS, rca, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd15
 *
 * DESCRIPTION
 *
 *   This function issues SD command GO_INACTIVE_STATE: Inactivate the
 *   addressed card to inactive state.
 *
 *   Class: 0 (basic commands)
 *
 *   State Transition:
 *     standby -> inactive
 *     transfer -> inactive
 *     sending-data -> inactive
 *     receiving-data -> inactive
 *     programming -> inactive
 *     disconnect -> inactive
 *
 *   Argument:
 *     [31:16] RCA
 *     [15: 0] Should be 0!
 *
 *   Response:
 *     None
 *
 * INPUTS
 *
 *   rca    : uint32_t value with RCA at [31:16], 0 at [15:0].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd15(uint32_t rca)
{
	return _sd_cmd_arg(SDC_CMD15_GO_INACTIVE_STATE, rca);
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd16
 *
 * DESCRIPTION
 *
 *   This function issues SD command SET_BLOCKLEN: Set block length (bytes)
 *   for standard capacity SD cards.  SDHC is fixed to 512 bytes and ignores
 *   this field except the LOCK_UNLOCK command.
 *
 *   Class: 2/4/7 (block-oriented read/write/lock_unlock commands)
 *
 *   State Transition:
 *     transfer -> transfer
 *
 *   Argument:
 *     [31:0] block length
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   blk_len: uint32_t block length value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd16(uint32_t blk_len, SD_R32 * csr)
{
	uint32_t status = _sd_cmd_arg_r32(SDC_CMD16_SET_BLOCKLEN, blk_len, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd17
 *
 * DESCRIPTION
 *
 *   This function issues SD command READ_SINGLE_BLOCK: Reads a single block
 *   size of data.
 *
 *   Class: 2 (block-oriented read commands)
 *
 *   State Transition:
 *     transfer -> sending-data
 *
 *   Argument:
 *     [31:0] data address (byte-unit for SD, block unit for SDHC)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd17(uint32_t addr, SD_R32 * csr)
{
#if 0
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {
#endif
		/* Send SD command */
		uint32_t status =
			_sd_cmd_arg_r32(SDC_CMD17_READ_SINGLE_BLOCK, addr, csr);
		if (status != HAL_SUCCESS) {
			return status;
		}

		/* Check error status */
		if (SD_CSR_CHECK_ERROR_BITS(*csr))
			return SDD_CSR_ERROR;
#if 0
		/* Check whether make transition to sending-data state */
		switch (SD_CSR_GET_CURRENT_STATE(*csr)) {
			case SD_STATE_DATA:
				/* The card is ready to send out data */
				return HAL_SUCCESS;
			case SD_STATE_TRAN:
				/* Repeat previous command until the card get to the state */
				break;
			case SD_STATE_STBY:
			case SD_STATE_RCV:
			case SD_STATE_PRG:
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_DIS:
			default:
				/* Invalid current state before deselecting the card. */
				return SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
#else
	return HAL_SUCCESS;
#endif
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd18
 *
 * DESCRIPTION
 *
 *   This function issues SD command READ_MULTIPLE_BLOCK: Reads blocks of data
 *   from card continuously until a STOP_TRANSMISSION command.
 *
 *   Class: 2 (block-oriented read commands)
 *
 *   State Transition:
 *     transfer -> sending-data
 *
 *   Argument:
 *     [31:0] data address (byte-unit for SD, block unit for SDHC)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd18(uint32_t addr, SD_R32 * csr) {
#if 0
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {
#endif
		/* Send SD command */
		uint32_t status =
			_sd_cmd_arg_r32(SDC_CMD18_READ_MULTIPLE_BLOCK, addr,
					csr);
		if (status != HAL_SUCCESS) {
			return status;
		}

		/* Check error status */
		if (SD_CSR_CHECK_ERROR_BITS(*csr))
			return SDD_CSR_ERROR;
#if 0
		/* Check whether make transition to sending-data state */
		switch (SD_CSR_GET_CURRENT_STATE(*csr)) {
			case SD_STATE_DATA:
				/* The card is ready to send out data */
				return HAL_SUCCESS;
			case SD_STATE_TRAN:
				/* Repeat previous command until the card get to the state */
				break;
			case SD_STATE_STBY:
			case SD_STATE_RCV:
			case SD_STATE_PRG:
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_DIS:
			default:
				/* Invalid current state before deselecting the card. */
				return SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
#else
	return HAL_SUCCESS;
#endif
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd24
 *
 * DESCRIPTION
 *
 *   This function issues SD command WRITE_SINGLE_BLOCK: Writes a single
 *   block size of data.
 *
 *   Class: 2 (block-oriented write commands)
 *
 *   State Transition:
 *     transfer -> receiving-data
 *
 *   Argument:
 *     [31:0] data address (byte-unit for SD, block unit for SDHC)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd24(uint32_t addr, SD_R32 * csr) {
#if 0
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {
#endif
		/* Send SD command */
		uint32_t status = _sd_cmd_arg_r32(SDC_CMD24_WRITE_BLOCK, addr, csr);

		if (status != HAL_SUCCESS)
			return status;

		/* Check error status */
		if (SD_CSR_CHECK_ERROR_BITS(*csr))
			return SDD_CSR_ERROR;
#if 0
		/* Check whether make transition to sending-data state */
		switch (SD_CSR_GET_CURRENT_STATE(*csr)) {
			case SD_STATE_RCV:
				/* The card is ready to send out data */
				return HAL_SUCCESS;
			case SD_STATE_TRAN:
				/* Repeat previous command until the card get to the state */
				break;
			case SD_STATE_STBY:
			case SD_STATE_DATA:
			case SD_STATE_PRG:
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_DIS:
			default:
				/* Invalid current state before deselecting the card. */
				return SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
#else
	return HAL_SUCCESS;
#endif
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd25
 *
 * DESCRIPTION
 *
 *   This function issues SD command WRITE_MULTIPLE_BLOCK: Writes blocks of
 *   data to the card continuously until a STOP_TRANSMISSION command.
 *
 *   Class: 2 (block-oriented write commands)
 *
 *   State Transition:
 *     transfer -> receiving-data
 *
 *   Argument:
 *     [31:0] data address (byte-unit for SD, block unit for SDHC)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd25(uint32_t addr, SD_R32 * csr) {
#if 0
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {
#endif
		/* Send SD command */
		uint32_t status = _sd_cmd_arg_r32 (SDC_CMD25_WRITE_MULTIPLE_BLOCK, addr, csr);

		if (status != HAL_SUCCESS)
			return status;

		/* Check error status */
		if (SD_CSR_CHECK_ERROR_BITS(*csr))
			return SDD_CSR_ERROR;
#if 0
		/* Check whether make transition to sending-data state */
		switch (SD_CSR_GET_CURRENT_STATE(*csr)) {
			case SD_STATE_RCV:
				/* The card is ready to send out data */
				return HAL_SUCCESS;
			case SD_STATE_TRAN:
				/* Repeat previous command until the card get to the state */
				break;
			case SD_STATE_STBY:
			case SD_STATE_DATA:
			case SD_STATE_PRG:
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_DIS:
			default:
				/* Invalid current state before deselecting the card. */
				return SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
#else
	return HAL_SUCCESS;
#endif
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd27
 *
 * DESCRIPTION
 *
 *   This function issues SD command PROGRAM_CSD: Programming the
 *   programmable bits of the CSD (using DATx lines).
 *
 *   Class: 2 (block-oriented write commands)
 *
 *   State Transition:
 *     transfer -> receiving-data
 *
 *   Argument:
 *     [31:0] stufing bits
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd27(SD_R32 * csr) {

	uint32_t status = _sd_cmd_r32(SDC_CMD27_PROGRAM_CSD, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd28
 *
 * DESCRIPTION
 *
 *   This function issues SD command SET_WRITE_PROT: Sets the write protection
 *   bits of the addressed group, if supported. (Not supported in SDHC)
 *
 *   Class: 6 (block-oriented write protection commands)
 *
 *   State Transition:
 *     transfer -> programming
 *
 *   Argument:
 *     [31:0] data address (byte unit)
 *
 *   Response:
 *     R1b [39:8] card status
 *         DAT0 busy signal
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd28(uint32_t addr, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_CMD28_SET_WRITE_PROT, addr, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd29
 *
 * DESCRIPTION
 *
 *   This function issues SD command CLR_WRITE_PROT: Clears the write
 *   protection bits of the addressed group, if supported.
 *   (Not supported in SDHC)
 *
 *   Class: 6 (block-oriented write protection commands)
 *
 *   State Transition:
 *     transfer -> programming
 *
 *   Argument:
 *     [31:0] data address (byte unit)
 *
 *   Response:
 *     R1b [39:8] card status
 *         DAT0 busy signal
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd29(uint32_t addr, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_CMD29_CLR_WRITE_PROT, addr, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd30
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_WRITE_PROT: Ask the card to send
 *   the status of the protection bits of the addressed group, if supported.
 *   (Not supported in SDHC)
 *
 *   Class: 6 (block-oriented write protection commands)
 *
 *   State Transition:
 *     transfer -> receiving-data
 *
 *   Argument:
 *     [31:0] data address (byte unit)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd30(uint32_t addr, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_CMD30_SEND_WRITE_PROT, addr, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd32
 *
 * DESCRIPTION
 *
 *   This function issues SD command ERASE_WR_BLK_START: Sets the address of
 *   the first write block to be erased.
 *
 *   Class: 5 (erase commands)
 *
 *   State Transition:
 *     transfer -> transfer
 *
 *   Argument:
 *     [31:0] data address (SD: byte unit, SDHC: block unit)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd32(uint32_t addr, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_CMD32_ERASE_WR_BLK_START, addr, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd33
 *
 * DESCRIPTION
 *
 *   This function issues SD command ERASE_WR_BLK_END: Sets the address of
 *   the last write block of a continuous range to be erased.
 *
 *   Class: 5 (erase commands)
 *
 *   State Transition:
 *     transfer -> transfer
 *
 *   Argument:
 *     [31:0] data address (SD: byte unit, SDHC: block unit)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd33(uint32_t addr, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_CMD33_ERASE_WR_BLK_END, addr, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd38
 *
 * DESCRIPTION
 *
 *   This function issues SD command ERASE: Erase all previously selected
 *   write blocks.
 *
 *   Class: 5 (erase commands)
 *
 *   State Transition:
 *     transfer -> programming
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     R1 [39:8] card status
 *         DAT0 busy signal
 *
 * INPUTS
 *
 *   addr   : uint32_t address value.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd38(SD_R32 * csr) {

	uint32_t status = _sd_cmd_r32(SDC_CMD38_ERASE, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd42
 *
 * DESCRIPTION
 *
 *   This function issues SD command LOCK_UNLOCK: Set/reset the password or
 *   lock/unlock the card.
 *
 *   Class: 7 (lock card)
 *
 *   State Transition:
 *     transfer -> receiving-data
 *
 *   Argument:
 *     [31:0] should be all 0!
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd42(SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_CMD42_LOCK_UNLOCK, 0, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd55
 *
 * DESCRIPTION
 *
 *   This function issues SD command APP_CMD: Indicates the next command is
 *   an application specific command.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     idle -> idle
 *     standby -> standby
 *     transfer -> transfer
 *     sending-data -> sending-data
 *     receiving-data -> receiving-data
 *     programming -> programming
 *     disconnected -> disconnected
 *
 *   Argument:
 *     [31:16] RCA
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_cmd55(uint32_t rca, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32(SDC_CMD55_APP_CMD, rca, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd56
 *
 * DESCRIPTION
 *
 *   This function issues SD command GEN_CMD: To transfer data block from/to
 *   the card for general-purpose/application-specific commands.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     RD/WR = 0 (write)
 *       transfer -> receiving-data
 *     RD/WR = 1 (read)
 *       transfer -> sending-data
 *
 *   Argument:
 *     [31: 1] stuff bits
 *     [0]     RD/WR
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   rdwr   : uint32_t value where bit [0] is RD/WR.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd56(uint32_t rdwr, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32(SDC_CMD56_GEN_CMD, rdwr, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_acmd6
 *
 * DESCRIPTION
 *
 *   This function issues SD command SET_BUS_WIDTH: Defines the data bus
 *   width to be used for data transfer.  The allowed bus widths are given
 *   in the SCR register.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     transfer -> transfer
 *
 *   Argument:
 *     [31:2] stuff bits
 *     [ 1:0] bus width (00b -> 1bit, 10b -> 4bits)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   bw     : uint32_t value where bit [1:0] is bus width.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_acmd6(uint32_t bw, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_ACMD6_SET_BUS_WIDTH, bw, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_acmd13
 *
 * DESCRIPTION
 *
 *   This function issues SD command SD_STATUS: Send the SD status.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     transfer -> sending-data
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_acmd13(SD_R32 * csr) {

	uint32_t status = _sd_cmd_r32(SDC_ACMD13_SD_STATUS, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_acmd22
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_NUM_WR_BLOCKS: Send the number of
 *   non-error write blocks.
 *
 *   If (WRITE_BL_PARTIAL == 0)
 *     unit of ACMD22 is 512 bytes
 *   else
 *     unit of ACMD22 is a block length of write command
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     transfer -> sending-data
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_acmd22(SD_R32 * csr) {

	uint32_t status = _sd_cmd_r32 (SDC_ACMD22_SEND_NUM_WR_BLOCKS, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_acmd23
 *
 * DESCRIPTION
 *
 *   This function issues SD command SET_WR_BLK_ERASE_COUNT: Send the number
 *   of write blocks to be pre-erased before writing (for faster multiple-
 *   block-WR command).  Default is 1.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     transfer -> transfer
 *
 *   Argument:
 *     [31:23] stuff bits
 *     [22: 0] number of blocks
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   blocks : uint32_t value represents the number of blocks.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_acmd23(uint32_t blocks, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_ACMD23_SET_WR_BLK_ERASE_COUNT, blocks, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_acmd41
 *
 * DESCRIPTION
 *
 *   This function issues SD command SD_SEND_OP_COND: Send HCS and get OCR
 *   during the initialization and identification process.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     idle -> ready (OCR check OK and card is not busy)
 *     idle -> idle (OCR check OK and card is busy)
 *     idle -> inactive (OCR check fails)
 *     idle -> idle (query mode)
 *
 *   Argument:
 *     [30]   HCS (OCR[32])
 *     [23:0] Vdd voltage window (OCR[23:0])
 *
 *   Response:
 *     R3 [39:8] OCR
 *
 * INPUTS
 *
 *   hcs    : uint32_t value represents the host capacity support information.
 *   ocr    : Pointer to SD_OCR struct.
 *
 * OUTPUTS
 *
 *   ocr    : SD_OCR struct which holds the R3/OCR response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_acmd41(uint32_t hcs, SD_OCR * ocr) {

	return _sd_cmd_arg_r32 (SDC_ACMD41_SD_SEND_OP_COND, hcs, ocr);
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_acmd42
 *
 * DESCRIPTION
 *
 *   This function issues SD command SET_CLR_CARD_DETECT: Connect/Disconnect
 *   the 50 KOmh pull-up resister on CD/DAT3 (pin1) of the card.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     transfer -> transfer
 *
 *   Argument:
 *     [0] set_cd (1: connect, 0: disconnect)
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   conn   : uint32_t value where [0] denotes set_cd.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_acmd42(uint32_t conn, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_ACMD42_SET_CLR_CARD_DETECT, conn, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_acmd51
 *
 * DESCRIPTION
 *
 *   This function issues SD command SEND_SCR: Reads the SD configuration
 *   register (SCR).
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     transfer -> sending-data
 *
 *   Argument:
 *     [31:0] stuff bits
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_acmd51(SD_R32 * csr) {

	uint32_t status = _sd_cmd_r32(SDC_ACMD51_SEND_SCR, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_cmd6
 *
 * DESCRIPTION
 *
 *   This function issues SD command SWITCH_FUNC: Check switchable function
 *   or switch card function.
 *
 *   Class: 8 (application-specific commands)
 *
 *   State Transition:
 *     transfer -> sending-data
 *
 *   Argument:
 *     [31]    mode (0: check, 1: switch)
 *     [30:24] should be 0
 *     [23:20] 00h or 0fh (reserved for function group 6)
 *     [19:16] 00h or 0fh (reserved for function group 5)
 *     [15:12] 00h or 0fh (reserved for function group 4)
 *     [11: 8] 00h or 0fh (reserved for function group 3)
 *     [ 7: 4] function group 2 for command system
 *     [ 3: 0] function group 1 for access mode
 *
 *   Response:
 *     R1 [39:8] card status
 *
 * INPUTS
 *
 *   mode   : uint32_t value which holds the function mode.
 *   csr    : Pointer to SD_R32 struct.
 *
 * OUTPUTS
 *
 *   csr    : SD_R32 struct which holds the R1 response.
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
#if (SDD_SMALL_SD_FOOTPRINT == 0)
uint32_t _sd_cmd6(uint32_t mode, SD_R32 * csr) {

	uint32_t status = _sd_cmd_arg_r32 (SDC_CMD6_SWITCH_FUNC, mode, csr);

	if (status != HAL_SUCCESS)
		return status;

	if (SD_CSR_CHECK_ERROR_BITS(*csr))
		return SDD_CSR_ERROR;

	return HAL_SUCCESS;
}
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

#if 0
/*****************************************************************************
 * FUNCTION
 *
 *   _sd_wait_sending_state
 *
 * DESCRIPTION
 *
 *   This function waits the transfer state make transition to the sending-
 *   data state.  This is equivalent to waiting for the card start to send
 *   out data after cmd17 or cmd18.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_wait_sending_state(uint32_t rca) {
	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ <
			SD_TRANSFER_MAX_RETRY_COUNT) {
		/* Get current state */
		status =
			_sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		switch (SD_CSR_GET_CURRENT_STATE
				(sd_rsp32)) {
			case SD_STATE_DATA:
				return HAL_SUCCESS;
			case SD_STATE_TRAN:
				break;
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_STBY:
			case SD_STATE_RCV:
			case SD_STATE_DIS:
			case SD_STATE_PRG:
			default:
				return
					SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_wait_receiving_state
 *
 * DESCRIPTION
 *
 *   This function waits the transfer state make transition to the receiving-
 *   data state.  This is equivalent to waiting for the card start to receive
 *   data after cmd24/25/27/42/56.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_wait_receiving_state(uint32_t rca) {
	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ <
			SD_TRANSFER_MAX_RETRY_COUNT) {
		/* Get current state */
		status =
			_sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		switch (SD_CSR_GET_CURRENT_STATE
				(sd_rsp32)) {
			case SD_STATE_RCV:
				if (SD_CSR_GET_READY_FOR_DATA(sd_rsp32))
					return
						HAL_SUCCESS;
				break;
			case SD_STATE_TRAN:
				break;
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_STBY:
			case SD_STATE_DATA:
			case SD_STATE_DIS:
			case SD_STATE_PRG:
			default:
				return
					SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}
#endif /* 0 */

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_wait_programmed
 *
 * DESCRIPTION
 *
 *   This function waits the disconnected state make transition to the
 *   standby state or the transfer state.  This is equivalent to waiting for
 *   the completion of programming.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_wait_programmed(uint32_t rca) {

	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ < SD_TRANSFER_MAX_RETRY_COUNT) {

		/* Get current state */
		status = _sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		switch (SD_CSR_GET_CURRENT_STATE
				(sd_rsp32)) {
			case SD_STATE_STBY:
			case SD_STATE_TRAN:
				return HAL_SUCCESS;
			case SD_STATE_DIS:
			case SD_STATE_PRG:
				break;
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_DATA:
			case SD_STATE_RCV:
			default:
				return
					SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_wait_transferred
 *
 * DESCRIPTION
 *
 *   This function waits the data/rcv/prog state make transition to the
 *   transfer state.  This is equivalent to waiting for the
 *   completion of all current data transfer traffic.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_wait_transferred(uint32_t rca) {

	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ < SD_TRANSFER_MAX_RETRY_COUNT) {

		/* Get current state */
		status = _sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		switch (SD_CSR_GET_CURRENT_STATE (sd_rsp32)) {

			case SD_STATE_TRAN:
				return HAL_SUCCESS;
			case SD_STATE_DATA:
			case SD_STATE_RCV:
			case SD_STATE_PRG:
				break;
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_STBY:
			case SD_STATE_DIS:
			default:
				return
					SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_disconnect
 *
 * DESCRIPTION
 *
 *   This function forces the prog state make transition to the
 *   disconnect state.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_disconnect(uint32_t rca) {

	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {
		/* Get current state */
		status = _sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		/* Perform state transition according to spec 2.0 fig 4-3. */
		switch (SD_CSR_GET_CURRENT_STATE (sd_rsp32)) {

			case SD_STATE_STBY:
			case SD_STATE_DIS:
				/* The card with the target rca is already disconnected. Just */
				/* return that the card is disconnected successfully. */
				return HAL_SUCCESS;
			case SD_STATE_PRG:
				/* Try to enter disconnected state ... */
				status = _sd_cmd7(rca, &sd_rsp32);	/* disconnect the card */
				if (status != HAL_SUCCESS)
					return status;
				break;
			case SD_STATE_TRAN:
			case SD_STATE_DATA:
			case SD_STATE_RCV:
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			default:
				/* Invalid current state before disconnect the card. */
				return
					SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_connect
 *
 * DESCRIPTION
 *
 *   This function forces the disconnect state make transition to the
 *   programming state.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_connect(uint32_t rca) {

	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {

		/* Get current state */
		status = _sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		/* Perform state transition according to spec 2.0 fig 4-3. */
		switch (SD_CSR_GET_CURRENT_STATE (sd_rsp32)) {
			case SD_STATE_PRG:
			case SD_STATE_TRAN:
				/*
				 * The card with the target rca is already connected. Just
				 * return that the card is connected successfully.
				 */
				return HAL_SUCCESS;
			case SD_STATE_DIS:
				/* Try to enter programming state ... */
				status = _sd_cmd7(rca, &sd_rsp32);	/* connect the card */
				if (status != HAL_SUCCESS)
					return status;
				break;
			case SD_STATE_STBY:
			case SD_STATE_DATA:
			case SD_STATE_RCV:
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			default:
				/* Invalid current state before connect the card. */
				return
					SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_deselect_card
 *
 * DESCRIPTION
 *
 *   This function forces the transfer state make transition to the
 *   standby state.
 *
 *   If the card is currently in data or transfer state, the function will
 *   issue trnasition command and continue loop until the card enters standby
 *   state.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_deselect_card(uint32_t rca) {

	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {
		/* Get current state */
		status = _sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		/* Perform state transition according to spec 2.0 fig 4-3. */
		switch (SD_CSR_GET_CURRENT_STATE (sd_rsp32)) {

			case SD_STATE_STBY:
				/*
				 * The card with the target rca is already deselected. Just
				 * return that the card is deselected successfully.
				 */
				return HAL_SUCCESS;
			case SD_STATE_TRAN:
			case SD_STATE_DATA:
				/* Try to enter standby state ... */
				status = _sd_cmd7(rca, &sd_rsp32);	/* deselect the card */
				if (status != HAL_SUCCESS)
					return status;
				break;
			case SD_STATE_RCV:
			case SD_STATE_PRG:
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_DIS:
			default:
				/* Invalid current state before deselecting the card. */
				return
					SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_select_card
 *
 * DESCRIPTION
 *
 *   This function forces the standby state make transition to the
 *   transfer state.
 *
 *   If the card is currently in data/rcv state, the function will wait for
 *   a limitted time.  After timeout, it forces to stop the current
 *   operation and try to make transition back to standby state.
 *
 *   If the card is currently in the prog state, the function will wait for
 *   a limitted time.  If timeout then it will return that failed to make
 *   the desired state transition.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_select_card(uint32_t rca) {

	uint32_t status;
	SD_R32 sd_rsp32;
	uint32_t retry = 0;

	while (retry++ < SD_STATE_MAX_RETRY_COUNT) {

		/* Get current state */
		status = _sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		/* Perform state transition according to spec 2.0 fig 4-3. */
		switch (SD_CSR_GET_CURRENT_STATE (sd_rsp32)) {

			case SD_STATE_TRAN:
				/*
				 * The card with the target rca is already selected. Just
				 * return that the card is selected successfully.
				 */
				return HAL_SUCCESS;
			case SD_STATE_STBY:
				/* Try to enter transfer state ... */
				status = _sd_cmd7(rca, &sd_rsp32);	/* select the card */
				if (status != HAL_SUCCESS)
					return status;
				break;
			case SD_STATE_DATA:
			case SD_STATE_RCV:
				/*
				 * The card is still transferring data or programming.
				 * Wait a short period for transfer completion. The
				 * card will back to transfer state after operation
				 * completion.
				 */
				status = _sd_wait_transferred (rca);

				if (status == HAL_SUCCESS) {

					return HAL_SUCCESS;
				}
				else if (status == SDD_WAIT_TIMEOUT)
				{
					/*
					 * Stop the current transmission after waiting timeout. Then
					 * continue status check loop to fall back to transfer state.
					 */
					status = _sd_cmd12(&sd_rsp32);	/* stop transmission */
					if (status != HAL_SUCCESS)
						return status;
				}
				else {
					return status;
				}
				break;
			case SD_STATE_PRG:

				status = _sd_wait_transferred (rca);
				if (status != HAL_SUCCESS)
					return status;

				break;
			case SD_STATE_DIS:
				/* Continue status check loop to fall back to standby state. */
				break;
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			default:
				/* Invalid current state before selecting the card. */
				return SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _sd_stop_transmission
 *
 * DESCRIPTION
 *
 *   This function forces the data/rcv/prog state make transition to the
 *   transfer state.
 *
 *   If the card is currently in data/rcv state, the function will issue
 *   stop command directly.  Then continue check loop to wait for back to
 *   the transfer or standby state.
 *
 *   If the card is currently in the prog state, the function will wait for
 *   a limitted time.  If timeout then it will return that failed to make
 *   the desired state transition.
 *
 * INPUTS
 *
 *   rca    : uint32_t value where RCA is at [31:16].
 *
 * OUTPUTS
 *
 *   uint32_t : Returns HAL_SUCCESS if successful,
 *            else positive value is SDD-specific error code,
 *            else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _sd_stop_transmission(uint32_t rca) {

	uint32_t status;
	SD_R32 sd_rsp32;

	while (1) {

		// _nds_kwait(0x1000);

		/* Get current state */
		status = _sd_cmd13(rca, &sd_rsp32);
		if (status != HAL_SUCCESS)
			return status;

		/* Perform state transition according to spec 2.0 fig 4-3. */
		switch (SD_CSR_GET_CURRENT_STATE (sd_rsp32)) {

			case SD_STATE_STBY:
			case SD_STATE_TRAN:
				/* The card with the target rca is already stopped. Just */
				/* return that the card is stopped successfully. */
				return HAL_SUCCESS;
			case SD_STATE_DATA:
			case SD_STATE_RCV:
				/* Try to back to transfer state ... */
				status = _sd_cmd12(&sd_rsp32);	/* stop transmission */
				if (status != HAL_SUCCESS)
					return status;
				break;
			case SD_STATE_PRG:
				/* The card is still transferring data or programming. */
				/* Wait a short period for transfer completion. The */
				/* card will back to transfer state after operation */
				/* completion. */
				status = _sd_wait_transferred (rca);
				if (status != HAL_SUCCESS)
					return status;

				break;
			case SD_STATE_IDLE:
			case SD_STATE_READY:
			case SD_STATE_IDENT:
			case SD_STATE_DIS:
			default:
				/* Invalid current state before selecting the card. */
				return SDD_INVALID_STATE;
		}
	}

	return SDD_WAIT_TIMEOUT;
}
