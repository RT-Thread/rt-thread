/*
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef FSL_FTFX_FLASH_H
#define FSL_FTFX_FLASH_H

#include "fsl_ftfx_controller.h"

/*!
 * @addtogroup ftfx_flash_driver
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define kStatus_FLASH_Success kStatus_FTFx_Success
#define kFLASH_ApiEraseKey    kFTFx_ApiEraseKey

/*!
 * @name Flash version
 * @{
 */
/*! @brief Flash driver version for SDK*/
#define FSL_FLASH_DRIVER_VERSION (MAKE_VERSION(3U, 1U, 3U)) /*!< Version 3.1.3. */

/*! @brief Flash driver version for ROM*/
#define FSL_FLASH_DRIVER_VERSION_ROM (MAKE_VERSION(3U, 0U, 0U)) /*!< Version 3.0.0. */

/*! @} */

/*!
 * @brief Enumeration for the three possible flash protection levels.
 */
typedef enum _flash_protection_state
{
    kFLASH_ProtectionStateUnprotected, /*!< Flash region is not protected.*/
    kFLASH_ProtectionStateProtected,   /*!< Flash region is protected.*/
    kFLASH_ProtectionStateMixed        /*!< Flash is mixed with protected and unprotected region.*/
} flash_prot_state_t;

/*!
 * @brief PFlash protection status
 */
typedef union _pflash_protection_status
{
    uint32_t protl; /*!< PROT[31:0] .*/
    uint32_t proth; /*!< PROT[63:32].*/
    uint8_t protsl; /*!< PROTS[7:0] .*/
    uint8_t protsh; /*!< PROTS[15:8] .*/
    uint8_t reserved[2];
} pflash_prot_status_t;

#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
/*!
 * @brief Enumeration for the three possible flash execute access levels.
 */
typedef enum _flash_execute_only_access_state
{
    kFLASH_AccessStateUnLimited,   /*!< Flash region is unlimited.*/
    kFLASH_AccessStateExecuteOnly, /*!< Flash region is execute only.*/
    kFLASH_AccessStateMixed        /*!< Flash is mixed with unlimited and execute only region.*/
} flash_xacc_state_t;
#endif /* not define FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL */

/*!
 * @brief Enumeration for various flash properties.
 */
typedef enum _flash_property_tag
{
    kFLASH_PropertyPflash0SectorSize         = 0x00U, /*!< Pflash sector size property.*/
    kFLASH_PropertyPflash0TotalSize          = 0x01U, /*!< Pflash total size property.*/
    kFLASH_PropertyPflash0BlockSize          = 0x02U, /*!< Pflash block size property.*/
    kFLASH_PropertyPflash0BlockCount         = 0x03U, /*!< Pflash block count property.*/
    kFLASH_PropertyPflash0BlockBaseAddr      = 0x04U, /*!< Pflash block base address property.*/
    kFLASH_PropertyPflash0FacSupport         = 0x05U, /*!< Pflash fac support property.*/
    kFLASH_PropertyPflash0AccessSegmentSize  = 0x06U, /*!< Pflash access segment size property.*/
    kFLASH_PropertyPflash0AccessSegmentCount = 0x07U, /*!< Pflash access segment count property.*/

    kFLASH_PropertyPflash1SectorSize         = 0x10U, /*!< Pflash sector size property.*/
    kFLASH_PropertyPflash1TotalSize          = 0x11U, /*!< Pflash total size property.*/
    kFLASH_PropertyPflash1BlockSize          = 0x12U, /*!< Pflash block size property.*/
    kFLASH_PropertyPflash1BlockCount         = 0x13U, /*!< Pflash block count property.*/
    kFLASH_PropertyPflash1BlockBaseAddr      = 0x14U, /*!< Pflash block base address property.*/
    kFLASH_PropertyPflash1FacSupport         = 0x15U, /*!< Pflash fac support property.*/
    kFLASH_PropertyPflash1AccessSegmentSize  = 0x16U, /*!< Pflash access segment size property.*/
    kFLASH_PropertyPflash1AccessSegmentCount = 0x17U, /*!< Pflash access segment count property.*/

    kFLASH_PropertyFlexRamBlockBaseAddr = 0x20U, /*!< FlexRam block base address property.*/
    kFLASH_PropertyFlexRamTotalSize     = 0x21U, /*!< FlexRam total size property.*/
} flash_property_tag_t;

/*! @brief Flash driver state information.
 *
 * An instance of this structure is allocated by the user of the flash driver and
 * passed into each of the driver APIs.
 */
typedef struct _flash_config
{
    ftfx_config_t ftfxConfig[FTFx_FLASH_COUNT];
} flash_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 *
 * @param config Pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_PartitionStatusUpdateFailure Failed to update the partition status.
 */
status_t FLASH_Init(flash_config_t *config);

/*! @} */

/*!
 * @name Erasing
 * @{
 */

/*!
 * @brief Erases the Dflash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 *
 * @param config The pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be erased.
 *              The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *                      to be erased. Must be word-aligned.
 * @param key The value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the appropriate number of flash sectors based on the
 *         desired start address and length were erased successfully.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError The parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_AddressError The address is out of range.
 * @retval #kStatus_FTFx_EraseKeyError The API erase key is invalid.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_Erase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);

/*!
 * @brief Erases the Dflash sectors encompassed by parameters passed into function.
 *
 * This function erases one flash sector size based on the start address, and it is
 * executed asynchronously.
 *
 * NOTE: This function can only erase one flash sector at a time, and the other commands
 *       can be executed after the previous command has been completed.
 *
 * @param config The pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be erased.
 *              The start address does not need to be sector-aligned but must be word-aligned.
 * @param key The value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError The parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_AddressError The address is out of range.
 * @retval #kStatus_FTFx_EraseKeyError The API erase key is invalid.
 */
status_t FLASH_EraseSectorNonBlocking(flash_config_t *config, uint32_t start, uint32_t key);

/*!
 * @brief Erases entire flexnvm
 *
 * @param config Pointer to the storage for the driver runtime state.
 * @param key A value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the all pflash and flexnvm were erased successfully,
 *         the swap and eeprom have been reset to unconfigured state.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_EraseKeyError API erase key is invalid.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FTFx_PartitionStatusUpdateFailure Failed to update the partition status.
 */
status_t FLASH_EraseAll(flash_config_t *config, uint32_t key);

#if defined(FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD) && FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD
/*!
 * @brief Erases the entire flexnvm, including protected sectors.
 *
 * @param config Pointer to the storage for the driver runtime state.
 * @param key A value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully;
 *         the protected sectors of flash were reset to unprotected status.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_EraseKeyError API erase key is invalid.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FTFx_PartitionStatusUpdateFailure Failed to update the partition status.
 */
status_t FLASH_EraseAllUnsecure(flash_config_t *config, uint32_t key);
#endif /* FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD */

/*! @} */

/*!
 * @name Programming
 * @{
 */

/*!
 * @brief Programs flash with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              word-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the desired data were programed successfully
 *         into flash based on desired start address and length.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_Program(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);

/*!
 * @brief Program the Program-Once-Field through parameters.
 *
 * This function Program the Program-once-feild with given index and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param index The index indicating the area of program once field to be read.
 * @param src A pointer to the source buffer of data that is used to store
 *        data to be write.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; The index indicating the area
 *         of program once field was programed successfully.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_ProgramOnce(flash_config_t *config, uint32_t index, uint8_t *src, uint32_t lengthInBytes);

#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
/*!
 * @brief Programs flash with data at locations passed in through parameters via the Program Section command.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              word-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the desired data have been programed successfully into
 *         flash based on start address and length.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FTFx_SetFlexramAsRamError Failed to set flexram as RAM.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FTFx_RecoverFlexramAsEepromError Failed to recover FlexRAM as EEPROM.
 */
status_t FLASH_ProgramSection(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
#endif /* FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD */

/*! @} */

/*!
 * @name Reading
 * @{
 */

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
/*!
 * @brief Reads the resource with data at locations passed in through parameters.
 *
 * This function reads the flash memory with the desired location for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              word-aligned.
 * @param dst A pointer to the destination buffer of data that is used to store
 *        data to be read.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be read. Must be word-aligned.
 * @param option The resource option which indicates which area should be read back.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully;  the data have been read successfully from
 *         program flash IFR, data flash IFR space, and the Version ID field.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_ReadResource(
    flash_config_t *config, uint32_t start, uint8_t *dst, uint32_t lengthInBytes, ftfx_read_resource_opt_t option);
#endif /* FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD */

/*!
 * @brief Reads the Program Once Field through parameters.
 *
 * This function reads the read once feild with given index and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param index The index indicating the area of program once field to be read.
 * @param dst A pointer to the destination buffer of data that is used to store
 *        data to be read.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be programmed. Must be word-aligned.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the data have been successfuly
 *         read form Program flash0 IFR map and Program Once field based on index and length.

 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_ReadOnce(flash_config_t *config, uint32_t index, uint8_t *dst, uint32_t lengthInBytes);

/*! @} */

/*!
 * @name Verification
 * @{
 */

/*!
 * @brief Verifies an erasure of the desired flash area at a specified margin level.
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 * to the specified read margin level.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 * @param margin Read margin choice.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the specified FLASH region has been erased.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyErase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, ftfx_margin_value_t margin);

/*!
 * @brief Verifies erasure of the entire flash at a specified margin level.
 *
 * This function checks whether the flash is erased to the
 * specified read margin level.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param margin Read margin choice.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; all program flash and flexnvm were in erased state.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyEraseAll(flash_config_t *config, ftfx_margin_value_t margin);

/*!
 * @brief Verifies programming of the desired flash area at a specified margin level.
 *
 * This function verifies the data programmed in the flash memory using the
 * Flash Program Check Command and compares it to the expected data for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified. Must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 * @param expectedData A pointer to the expected data that is to be
 *        verified against.
 * @param margin Read margin choice.
 * @param failedAddress A pointer to the returned failing address.
 * @param failedData A pointer to the returned failing data.  Some derivatives do
 *        not include failed data as part of the FCCOBx registers.  In this
 *        case, zeros are returned upon failure.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the desired data have been successfully programed into
 *         specified FLASH region.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyProgram(flash_config_t *config,
                             uint32_t start,
                             uint32_t lengthInBytes,
                             const uint8_t *expectedData,
                             ftfx_margin_value_t margin,
                             uint32_t *failedAddress,
                             uint32_t *failedData);

/*! @} */

/*!
 * @name Security
 * @{
 */

/*!
 * @brief Returns the security state via the pointer passed into the function.
 *
 * This function retrieves the current flash security status, including the
 * security enabling state and the backdoor key enabling state.
 *
 * @param config A pointer to storage for the driver runtime state.
 * @param state A pointer to the value returned for the current security status code:
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the security state of flash was stored to state.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 */
status_t FLASH_GetSecurityState(flash_config_t *config, ftfx_security_state_t *state);

/*!
 * @brief Allows users to bypass security with a backdoor key.
 *
 * If the MCU is in secured state, this function unsecures the MCU by
 * comparing the provided backdoor key with ones in the flash configuration
 * field.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param backdoorKey A pointer to the user buffer containing the backdoor key.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_SecurityBypass(flash_config_t *config, const uint8_t *backdoorKey);

/*! @} */

/*!
 * @name FlexRAM
 * @{
 */

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
/*!
 * @brief Sets the FlexRAM function command.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param option The option used to set the work mode of FlexRAM.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the FlexRAM has been successfully configured as RAM or
 * EEPROM.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_SetFlexramFunction(flash_config_t *config, ftfx_flexram_func_opt_t option);
#endif /* FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD */

/*! @} */

/*!
 * @name Swap
 * @{
 */

#if defined(FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP) && FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP
/*!
 * @brief Swaps the lower half flash with the higher half flash.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param address Address used to configure the flash swap function
 * @param isSetEnable The possible option used to configure the Flash Swap function or check the flash Swap status.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the lower half flash and higher half flash have been
 * swaped.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FTFx_SwapIndicatorAddressError Swap indicator address is invalid.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FTFx_SwapSystemNotInUninitialized Swap system is not in an uninitialized state.
 */
status_t FLASH_Swap(flash_config_t *config, uint32_t address, bool isSetEnable);
#endif /* FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP */

/*! @} */

/*!
 * @name Protection
 * @{
 */

/*!
 * @brief Returns the protection state of the desired flash area via the pointer passed into the function.
 *
 * This function retrieves the current flash protect status for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be checked. Must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *        to be checked.  Must be word-aligned.
 * @param protection_state A pointer to the value returned for the current
 *        protection status code for the desired flash area.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the protection state of specified FLASH region was
 * stored to protection_state.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FTFx_AddressError The address is out of range.
 */
status_t FLASH_IsProtected(flash_config_t *config,
                           uint32_t start,
                           uint32_t lengthInBytes,
                           flash_prot_state_t *protection_state);

#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
/*!
 * @brief Returns the access state of the desired flash area via the pointer passed into the function.
 *
 * This function retrieves the current flash access status for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be checked. Must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be checked.  Must be word-aligned.
 * @param access_state A pointer to the value returned for the current
 *        access status code for the desired flash area.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the executeOnly state of specified FLASH region was
 * stored to access_state.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError The parameter is not aligned to the specified baseline.
 * @retval #kStatus_FTFx_AddressError The address is out of range.
 */
status_t FLASH_IsExecuteOnly(flash_config_t *config,
                             uint32_t start,
                             uint32_t lengthInBytes,
                             flash_xacc_state_t *access_state);
#endif /* FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL */

/*!
 * @brief Sets the PFlash Protection to the intended protection status.
 *
 * @param config A pointer to storage for the driver runtime state.
 * @param protectStatus The expected protect status to set to the PFlash protection register. Each bit is
 * corresponding to protection of 1/32(64) of the total PFlash. The least significant bit is corresponding to the lowest
 * address area of PFlash. The most significant bit is corresponding to the highest address area of PFlash. There are
 * two possible cases as shown below:
 *       0: this area is protected.
 *       1: this area is unprotected.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the specified FLASH region is protected.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during command execution.
 */
status_t FLASH_PflashSetProtection(flash_config_t *config, pflash_prot_status_t *protectStatus);

/*!
 * @brief Gets the PFlash protection status.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param protectStatus  Protect status returned by the PFlash IP. Each bit is corresponding to the protection of
 * 1/32(64)
 * of the
 * total PFlash. The least significant bit corresponds to the lowest address area of the PFlash. The most significant
 * bit corresponds to the highest address area of PFlash. There are two possible cases as shown below:
 *       0: this area is protected.
 *       1: this area is unprotected.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the Protection state was stored to protectStatus;
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 */
status_t FLASH_PflashGetProtection(flash_config_t *config, pflash_prot_status_t *protectStatus);

/*! @} */

/*!
 * @name Properties
 * @{
 */

/*!
 * @brief Returns the desired flash property.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param whichProperty The desired property from the list of properties in
 *        enum flash_property_tag_t
 * @param value A pointer to the value returned for the desired flash property.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the flash property was stored to value.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_UnknownProperty An unknown property tag.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);

/*! @} */

/*!
 * @name commantStatus
 * @{
 */

/*!
 * @brief Get previous command status.
 *
 * This function is used to obtain the execution status of the previous command.
 *
 * @retval #kStatus_FTFx_Success The previous command is executed successfully.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_GetCommandState(void);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FTFX_FLASH_H */
