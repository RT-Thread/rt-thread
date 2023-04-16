/***************************************************************************//**
* \file cy_smif_memslot.c
* \version 2.40
*
* \brief
*  This file provides the source code for the memory-level APIs of the SMIF driver.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2016-2022 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXSMIF)

#include "cy_smif_memslot.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \cond INTERNAL */
/***************************************
*     Internal Constants
***************************************/
#define SMIF_MAX_RX_COUNT           (65536UL)
#define ONE_MILLI_IN_MICRO          (1000UL)
#define TIMEOUT_SLICE_MAX           (1000000UL)    /* The maximum timeout slice (microseconds)
                                                    * while polling the memory */
#define TIMEOUT_SLICE_DIV           (4U)           /* The division factor to use for slicing the timeout
                                                    * while polling the memory
                                                    */
#if (CY_IP_MXSMIF_VERSION>=2)
static cy_en_smif_status_t cy_smif_octalddrenable(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context);
#endif
/** \endcond */

/*******************************************************************************
* Function Name: Cy_SMIF_MemInit
****************************************************************************//**
*
* This function initializes the slots of the memory device in the SMIF
* configuration.
* This function must be called when a memory device is required to be used
* in memory-mapped (XIP) mode. This function can also be called instead of
* calling \ref Cy_SMIF_MemSfdpDetect when SFDP auto-discovery is enabled.
* Note that this function performs SFDP on all the external memories whereas
* \ref Cy_SMIF_MemSfdpDetect performs it only on one memory that is specified
* through the arguments. This function configures the SMIF device slot registers
* with the configuration from \ref cy_stc_smif_mem_config_t structure which is
* a member of the \ref cy_stc_smif_block_config_t structure. If SFDP discovery
* is enabled in the configuration structure through autoDetectSfdp field,
* this function calls \ref Cy_SMIF_MemSfdpDetect function for each memory,
* fills the structures with the discovered parameters, and configures the
* SMIF device slot registers accordingly. \ref Cy_SMIF_Init must have been
* called prior to calling this function.
* The \ref cy_stc_smif_context_t context structure returned from \ref Cy_SMIF_Init
* is passed as a parameter to this function.
*
* \note 4-byte addressing mode is set when the memory device supports
*       3- or 4-byte addressing mode.
*
* \param base
* The address of the slave-slot device register to initialize.
*
* \param blockConfig
* The configuration structure array that configures the SMIF memory device to be
* mapped into the PSoC memory map. \ref cy_stc_smif_mem_config_t
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The memory slot initialization status.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_BAD_PARAM
*       - \ref CY_SMIF_SFDP_SS0_FAILED
*       - \ref CY_SMIF_SFDP_SS1_FAILED
*       - \ref CY_SMIF_SFDP_SS2_FAILED
*       - \ref CY_SMIF_SFDP_SS3_FAILED
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemInit(SMIF_Type *base,
                            cy_stc_smif_block_config_t const * blockConfig,
                            cy_stc_smif_context_t *context)
{
    SMIF_DEVICE_Type volatile * device;
    cy_stc_smif_mem_config_t const * memCfg;
    uint32_t result = (uint32_t)CY_SMIF_BAD_PARAM;
    uint32_t sfdpRes =(uint32_t)CY_SMIF_SUCCESS;
    uint32_t idx;

    if ((NULL != base) && (NULL != blockConfig) && (NULL != blockConfig->memConfig)
        && (NULL != context) && (0U != blockConfig->memCount))
    {
        uint32_t size = blockConfig->memCount;
        cy_stc_smif_mem_config_t** extMemCfg = blockConfig->memConfig;

        result = (uint32_t)CY_SMIF_SUCCESS;
        for(idx = 0UL; idx < size; idx++)
        {
            memCfg = extMemCfg[idx];
            if (NULL != memCfg)
            {
                /* Check smif memory slot configuration */
                CY_ASSERT_L3(CY_SMIF_SLAVE_SEL_VALID(memCfg->slaveSelect));
                CY_ASSERT_L3(CY_SMIF_DATA_SEL_VALID(memCfg->dataSelect));
                CY_ASSERT_L1(NULL != memCfg->deviceCfg);

                device = Cy_SMIF_GetDeviceBySlot(base, memCfg->slaveSelect);
                if (NULL != device)
                {
                    /* The slave-slot initialization of the device control register.
                     * Cy_SMIF_MemSfdpDetect() must work */
                    SMIF_DEVICE_CTL(device)  = _CLR_SET_FLD32U(SMIF_DEVICE_CTL(device),
                                                               SMIF_DEVICE_CTL_DATA_SEL,
                                                              (uint32_t)memCfg->dataSelect);
                    uint32_t sfdpRet = (uint32_t)CY_SMIF_SUCCESS;
                    if (0U != (memCfg->flags & CY_SMIF_FLAG_DETECT_SFDP))
                    {
                        sfdpRet = (uint32_t)Cy_SMIF_MemSfdpDetect(base,
                                                memCfg->deviceCfg,
                                                memCfg->slaveSelect,
                                                memCfg->dataSelect,
                                                context);
                        if((uint32_t)CY_SMIF_SUCCESS != sfdpRet)
                        {
                            sfdpRes |=  ((uint32_t)CY_SMIF_SFDP_FAIL << idx);
                        }
                    }
                    /* Check the size of the smif memory slot address */
                    CY_ASSERT_L2(MEM_ADDR_SIZE_VALID(memCfg->deviceCfg->numOfAddrBytes));

                    /* Check if SMIF XIP is already enabled, then do not overwrite XIP registers */
                    if (((uint32_t)CY_SMIF_SUCCESS == sfdpRet) &&
                         (0U != (memCfg->flags & CY_SMIF_FLAG_MEMORY_MAPPED)) &&
                         (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 1U))
                    {
                        /* Check valid parameters for XIP */
                        CY_ASSERT_L3(MEM_ADDR_VALID( memCfg->baseAddress, memCfg->memMappedSize));
                        CY_ASSERT_L3(MEM_MAPPED_SIZE_VALID( memCfg->memMappedSize));

                        XipRegInit(device, memCfg);

#if(CY_IP_MXSMIF_VERSION>=2)
                        context->preXIPDataRate = memCfg->deviceCfg->readCmd->dataRate;
#endif /* CY_IP_MXSMIF_VERSION */

                        /* The device control register initialization */
                        SMIF_DEVICE_CTL(device) = _VAL2FLD(SMIF_DEVICE_CTL_WR_EN, ((bool)(memCfg->flags & CY_SMIF_FLAG_WRITE_ENABLE))? 1U : 0U) |
                                      _VAL2FLD(SMIF_DEVICE_CTL_CRYPTO_EN, ((bool)(memCfg->flags & CY_SMIF_FLAG_CRYPTO_ENABLE))? 1U : 0U) |
                                      _VAL2FLD(SMIF_DEVICE_CTL_DATA_SEL,  (uint32_t)memCfg->dataSelect) |
#if(CY_IP_MXSMIF_VERSION>=2)
                                      _VAL2FLD(SMIF_DEVICE_CTL_MERGE_EN,  ((bool)(memCfg->flags & CY_SMIF_FLAG_MERGE_ENABLE))? 1U : 0U)  |
                                      _VAL2FLD(SMIF_DEVICE_CTL_MERGE_TIMEOUT,  (uint32_t)memCfg->mergeTimeout) |
#endif /* CY_IP_MXSMIF_VERSION */
                                      SMIF_DEVICE_CTL_ENABLED_Msk;
                    }
                }
                else
                {
                    result = (uint32_t)CY_SMIF_BAD_PARAM;
                    break;
                }
            }
        }
    }
    if((uint32_t)CY_SMIF_SUCCESS != sfdpRes)
    {
        result = (((uint32_t)CY_SMIF_ID) | ((uint32_t)CY_PDL_STATUS_ERROR) | sfdpRes);
    }
    return (cy_en_smif_status_t) result;
}

/*******************************************************************************
* Function Name: Cy_SMIF_MemDeInit
****************************************************************************//**
*
* This function de-initializes all slave slots of the memory device to their default
* values.
*
* \param base
* Holds the base address of the SMIF block registers.
*
*******************************************************************************/
void Cy_SMIF_MemDeInit(SMIF_Type *base)
{
    /* Configure the SMIF device slots to the default values. The default value is 0 */
    uint32_t deviceIndex;

    for(deviceIndex = 0UL; deviceIndex < (uint32_t)SMIF_DEVICE_NR; deviceIndex++)
    {
        SMIF_DEVICE_IDX_CTL(base, deviceIndex)           = 0U;
        SMIF_DEVICE_IDX_ADDR(base, deviceIndex)          = 0U;
        SMIF_DEVICE_IDX_MASK(base, deviceIndex)          = 0U;
        SMIF_DEVICE_IDX_ADDR_CTL(base, deviceIndex)      = 0U;
        SMIF_DEVICE_IDX_RD_CMD_CTL(base, deviceIndex)    = 0U;
        SMIF_DEVICE_IDX_RD_ADDR_CTL(base, deviceIndex)   = 0U;
        SMIF_DEVICE_IDX_RD_MODE_CTL(base, deviceIndex)   = 0U;
        SMIF_DEVICE_IDX_RD_DUMMY_CTL(base, deviceIndex)  = 0U;
        SMIF_DEVICE_IDX_RD_DATA_CTL(base, deviceIndex)   = 0U;
        SMIF_DEVICE_IDX_WR_CMD_CTL(base, deviceIndex)    = 0U;
        SMIF_DEVICE_IDX_WR_ADDR_CTL(base, deviceIndex)   = 0U;
        SMIF_DEVICE_IDX_WR_MODE_CTL(base, deviceIndex)   = 0U;
        SMIF_DEVICE_IDX_WR_DUMMY_CTL(base, deviceIndex)  = 0U;
        SMIF_DEVICE_IDX_WR_DATA_CTL(base, deviceIndex)   = 0U;
    }
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdWriteEnable
****************************************************************************//**
*
* This function sends the Write Enable command to the memory device.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* The Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode,
* this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdWriteEnable(SMIF_Type *base,
                                        cy_stc_smif_mem_config_t const *memDevice,
                                        cy_stc_smif_context_t const *context)
{
    /* The memory Write Enable */
    cy_stc_smif_mem_cmd_t* writeEn = memDevice->deviceCfg->writeEnCmd;

    cy_en_smif_status_t result = CY_SMIF_CMD_NOT_FOUND;

    if(NULL != writeEn)
    {
#if (CY_IP_MXSMIF_VERSION>=2)
        result = Cy_SMIF_TransmitCommand_Ext( base,
                                (uint16_t)(writeEn->command | writeEn->command << 8),
                                (writeEn->cmdWidth == CY_SMIF_WIDTH_OCTAL) ? true : false,
                                writeEn->cmdWidth,
                                writeEn->cmdRate,
                                NULL,
                                0,
                                CY_SMIF_WIDTH_NA,
                                writeEn->addrRate,
                                memDevice->slaveSelect,
                                CY_SMIF_TX_LAST_BYTE,
                                context);
#else
        result = Cy_SMIF_TransmitCommand( base, (uint8_t) writeEn->command,
                                        writeEn->cmdWidth,
                                        NULL,
                                        CY_SMIF_CMD_WITHOUT_PARAM,
                                        CY_SMIF_WIDTH_NA,
                                        memDevice->slaveSelect,
                                        CY_SMIF_TX_LAST_BYTE,
                                        context);
#endif
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdWriteDisable
****************************************************************************//**
*
* This function sends a Write Disable command to the memory device.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode
* this API should be called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdWriteDisable(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context)
{
    cy_stc_smif_mem_cmd_t* writeDis = memDevice->deviceCfg->writeDisCmd;

    cy_en_smif_status_t result = CY_SMIF_CMD_NOT_FOUND;

    if(NULL != writeDis)
    {
#if (CY_IP_MXSMIF_VERSION>=2)
        result = Cy_SMIF_TransmitCommand_Ext( base,
                                (uint16_t)(writeDis->command | writeDis->command << 8),
                                (writeDis->cmdWidth == CY_SMIF_WIDTH_OCTAL) ? true : false,
                                writeDis->cmdWidth,
                                writeDis->cmdRate,
                                NULL,
                                0,
                                CY_SMIF_WIDTH_NA,
                                writeDis->addrRate,
                                memDevice->slaveSelect,
                                CY_SMIF_TX_LAST_BYTE,
                                context);
#else
        /* The memory write disable */
        result = Cy_SMIF_TransmitCommand( base, (uint8_t)writeDis->command,
                                          writeDis->cmdWidth,
                                          NULL,
                                          CY_SMIF_CMD_WITHOUT_PARAM,
                                          CY_SMIF_WIDTH_NA,
                                          memDevice->slaveSelect,
                                          CY_SMIF_TX_LAST_BYTE,
                                          context);
#endif
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemIsBusy
****************************************************************************//**
*
* This function checks if the status of the memory device is busy.
* This is done by reading the status register and the corresponding bit
* (stsRegBusyMask). This function is a blocking function until the status
* register from the memory is read.
*
* \note In the dual quad mode, this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
*  The device to which the command is sent.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the memory device.
*       - True - The device is busy or a timeout occurs.
*       - False - The device is not busy.
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
bool Cy_SMIF_MemIsBusy(SMIF_Type *base, cy_stc_smif_mem_config_t const *memDevice,
                            cy_stc_smif_context_t const *context)
{
    uint16_t  status = 1U;
    cy_en_smif_status_t readStsResult = CY_SMIF_CMD_NOT_FOUND;
    cy_stc_smif_mem_device_cfg_t* device =  memDevice->deviceCfg;

    if(NULL != device->readStsRegWipCmd)
    {
#if (CY_IP_MXSMIF_VERSION>=2)
        if (device->readStsRegWipCmd->cmdWidth == CY_SMIF_WIDTH_OCTAL)
        {
            uint8_t addr_param[4] = {0};
            /* Read the memory status register */
            readStsResult = Cy_SMIF_TransmitCommand_Ext( base,
                        (uint16_t)(device->readStsRegWipCmd->command | (device->readStsRegWipCmd->command << 8)),
                        true,
                        device->readStsRegWipCmd->cmdWidth,
                        device->readStsRegWipCmd->cmdRate,
                        addr_param, sizeof(addr_param),
                        device->readStsRegWipCmd->addrWidth,
                        device->readStsRegWipCmd->addrRate,
                        memDevice->slaveSelect,
                        CY_SMIF_TX_NOT_LAST_BYTE,
                        context);

            if(CY_SMIF_SUCCESS == readStsResult)
            {
                readStsResult = Cy_SMIF_SendDummyCycles_Ext(base,
                    device->readStsRegWipCmd->addrWidth,
                    device->readStsRegWipCmd->addrRate,
                    device->readStsRegWipCmd->dummyCycles);
            }
            if (CY_SMIF_SUCCESS == readStsResult)
            {
                readStsResult = Cy_SMIF_ReceiveDataBlocking_Ext( base, (uint8_t *)&status,
                                        (device->readStsRegWipCmd->cmdRate == CY_SMIF_DDR) ? 2U : 1U,
                                           device->readStsRegWipCmd->cmdWidth,
                                           device->readStsRegWipCmd->cmdRate,
                                           context);
            }

        }
        else
        {
#endif
            readStsResult = Cy_SMIF_MemCmdReadStatus(base, memDevice,  (uint8_t *)&status,
                            (uint8_t)device->readStsRegWipCmd->command,
                            context);
#if (CY_IP_MXSMIF_VERSION>=2)
        }
#endif
    }

    if (CY_SMIF_SUCCESS == readStsResult)
    {
        /* Masked not busy bits in returned status */
        status &= (uint8_t)device->stsRegBusyMask;
    }

    return (0U != status);
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemQuadEnable
****************************************************************************//**
*
* This function enables the memory device for the quad mode of operation.
* This command must be executed before sending quad SPI commands to the
* memory device.
*
* \note In the dual quad mode, this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command.
*   - \ref CY_SMIF_SUCCESS
*   - \ref CY_SMIF_NO_QE_BIT
*   - \ref CY_SMIF_CMD_FIFO_FULL
*   - \ref CY_SMIF_BAD_PARAM
*   - \ref CY_SMIF_CMD_NOT_FOUND
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemQuadEnable(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result= CY_SMIF_CMD_NOT_FOUND;
    uint8_t statusReg[CY_SMIF_QE_BIT_STATUS_REG2_T1] = {0U};
    cy_stc_smif_mem_device_cfg_t* device =  memDevice->deviceCfg;

    /* Check that command exists */
    if((NULL != device->readStsRegQeCmd)  &&
       (NULL != device->writeStsRegQeCmd) &&
       (NULL != device->readStsRegWipCmd))
    {
        uint8_t readQeCmd  = (uint8_t)device->readStsRegQeCmd->command;
        uint8_t writeQeCmd = (uint8_t)device->writeStsRegQeCmd->command;
        uint8_t readWipCmd = (uint8_t)device->readStsRegWipCmd->command;

        result = Cy_SMIF_MemCmdReadStatus(base, memDevice, &statusReg[0U],
                    readQeCmd, context);
        if (CY_SMIF_SUCCESS == result)
        {
            uint32_t qeMask = device->stsRegQuadEnableMask;

            switch(qeMask)
            {
                case CY_SMIF_SFDP_QE_BIT_6_OF_SR_1:
                    statusReg[0U] |= (uint8_t)qeMask;
                    result = Cy_SMIF_MemCmdWriteStatus(base, memDevice,
                                &statusReg[0U], writeQeCmd, context);
                    break;
                case CY_SMIF_SFDP_QE_BIT_1_OF_SR_2:
                    /* Read status register 1 with the assumption that WIP is always in
                    * status register 1 */
                    result = Cy_SMIF_MemCmdReadStatus(base, memDevice,
                                &statusReg[0U], readWipCmd, context);
                    if (CY_SMIF_SUCCESS == result)
                    {
                        result = Cy_SMIF_MemCmdReadStatus(base, memDevice,
                                    &statusReg[1U], readQeCmd, context);
                        if (CY_SMIF_SUCCESS == result)
                        {
                            statusReg[1U] |= (uint8_t)qeMask;

                            if (writeQeCmd == CY_SMIF_WRITE_STATUS_REG2_T2_CMD)
                            {
                                result = Cy_SMIF_MemCmdWriteStatus(base, memDevice,
                                        &statusReg[1U], writeQeCmd, context);
                            }
                            else
                            {
                                result = Cy_SMIF_MemCmdWriteStatus(base, memDevice,
                                        statusReg, writeQeCmd, context);
                            }
                        }
                    }
                    break;
                case CY_SMIF_SFDP_QE_BIT_7_OF_SR_2:
                    result = Cy_SMIF_MemCmdReadStatus(base, memDevice,
                                &statusReg[1U], readQeCmd, context);
                    if (CY_SMIF_SUCCESS == result)
                    {
                        statusReg[1U] |= (uint8_t)qeMask;
                        result = Cy_SMIF_MemCmdWriteStatus(base, memDevice,
                                    &statusReg[1U], writeQeCmd, context);
                    }
                    break;
                default:
                    result = CY_SMIF_NO_QE_BIT;
                    break;
            }
        }
    }
    return(result);
}
#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SMIF_MemOctalEnable
****************************************************************************//**
*
* This function enables the memory device for the octal mode of operation.
* This command must be executed before sending octal SPI commands to the
* memory device.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param dataRate
* Specifies the data rate to enable (SDR/DDR).
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command.
*   - \ref CY_SMIF_SUCCESS
*   - \ref CY_SMIF_NO_OE_BIT
*   - \ref CY_SMIF_CMD_FIFO_FULL
*   - \ref CY_SMIF_BAD_PARAM
*   - \ref CY_SMIF_CMD_NOT_FOUND
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemOctalEnable(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_en_smif_data_rate_t dataRate,
                                    cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result= CY_SMIF_CMD_NOT_FOUND;
    cy_stc_smif_mem_device_cfg_t* device =  memDevice->deviceCfg;

    if (dataRate == CY_SMIF_DDR)
    {
        return cy_smif_octalddrenable(base, memDevice, context);
    }
    /* Check that command exists */
    if((NULL != device->readStsRegOeCmd)  &&
       (NULL != device->writeStsRegOeCmd))
    {
        uint8_t readOeCmd  = (uint8_t)device->readStsRegOeCmd->command;
        uint8_t writeOeCmd = (uint8_t)device->writeStsRegOeCmd->command;
        uint8_t octalEnableAddr[5] = {0U};

        if (device->octalEnableRegAddr != CY_SMIF_NO_COMMAND_OR_MODE)
        {
            result = ReadAnyReg(base, memDevice->slaveSelect, &octalEnableAddr[4],
                                    readOeCmd, 0, (uint8_t *)&device->octalEnableRegAddr,
                                    4, context);

            if (CY_SMIF_SUCCESS == result)
            {
                uint32_t oeMask = device->stsRegOctalEnableMask;

                octalEnableAddr[4] |= (uint8_t)oeMask;

                /* The Write Enable */
                result =  Cy_SMIF_MemCmdWriteEnable(base, memDevice, context);

                /* The Write Status */
                if (CY_SMIF_SUCCESS == result)
                {
                    octalEnableAddr[3] = (uint8_t) device->octalEnableRegAddr; /* only 8 bits are valid as per SFDP spec */

                    result = Cy_SMIF_TransmitCommand( base, writeOeCmd, CY_SMIF_WIDTH_SINGLE,
                                (uint8_t const *)octalEnableAddr, 5, CY_SMIF_WIDTH_SINGLE,
                                memDevice->slaveSelect, CY_SMIF_TX_LAST_BYTE, context);
                }
            }
        }
        else
        {
            uint8_t statusReg = 0;
            result = Cy_SMIF_MemCmdReadStatus(base, memDevice, &statusReg,
                        readOeCmd, context);
            if (CY_SMIF_SUCCESS == result)
            {
                uint32_t oeMask = device->stsRegOctalEnableMask;

                statusReg |= (uint8_t)oeMask;
                result = Cy_SMIF_MemCmdWriteStatus(base, memDevice,
                             &statusReg, writeOeCmd, context);
            }
        }
    }

    return(result);
}
#endif
#if (CY_IP_MXSMIF_VERSION>=2)
static cy_en_smif_status_t cy_smif_octalddrenable(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result= CY_SMIF_CMD_NOT_FOUND;
    cy_stc_smif_mem_device_cfg_t* device =  memDevice->deviceCfg;
    cy_stc_smif_octal_ddr_en_seq_t* oDDREnSeq = device->octalDDREnableSeq;

    /* Check that command exists */
    if ((oDDREnSeq != NULL) && (base != NULL) && (context != NULL))
    {
        /* Send Command Sequence 1 */
        if (oDDREnSeq->cmdSeq1Len > 0U)
        {
            result = Cy_SMIF_TransmitCommand( base, oDDREnSeq->cmdSeq1[0], CY_SMIF_WIDTH_SINGLE,
                        (uint8_t const *)&oDDREnSeq->cmdSeq1[1U],
                        ((uint32_t)oDDREnSeq->cmdSeq1Len - 1U), CY_SMIF_WIDTH_SINGLE,
                        memDevice->slaveSelect, CY_SMIF_TX_LAST_BYTE, context);
        }
        /* Send Command Sequence 2 */
        if (oDDREnSeq->cmdSeq2Len > 0U)
        {
            result = Cy_SMIF_TransmitCommand( base, oDDREnSeq->cmdSeq2[0], CY_SMIF_WIDTH_SINGLE,
                        (uint8_t const *)&oDDREnSeq->cmdSeq2[1U],
                        ((uint32_t)oDDREnSeq->cmdSeq2Len - 1U), CY_SMIF_WIDTH_SINGLE,
                        memDevice->slaveSelect, CY_SMIF_TX_LAST_BYTE, context);
        }

#if (CY_IP_MXSMIF_VERSION>=5)
        /* Set the clock to xSPI mode */
        Cy_SMIF_SetRxCaptureMode(base, CY_SMIF_SEL_XSPI_HYPERBUS_WITH_DQS);
#endif

        /* Change Write Enable to 16-bit Octal DDR */
        device->writeEnCmd->commandH = CY_SMIF_WRITE_ENABLE_CMD;
        device->writeEnCmd->cmdRate = CY_SMIF_DDR;
        device->writeEnCmd->cmdWidth = CY_SMIF_WIDTH_OCTAL;
        device->writeEnCmd->cmdPresence = CY_SMIF_PRESENT_2BYTE;

        /* Change Write Disable to 16-bit Octal DDR*/
        device->writeDisCmd->commandH = CY_SMIF_WRITE_ENABLE_CMD;
        device->writeDisCmd->cmdRate = CY_SMIF_DDR;
        device->writeDisCmd->cmdWidth = CY_SMIF_WIDTH_OCTAL;
        device->writeDisCmd->cmdPresence = CY_SMIF_PRESENT_2BYTE;

        /* Change Read WIP status register to 16-bit Octal DDR */
        device->readStsRegWipCmd->commandH = CY_SMIF_READ_STATUS_REG1_CMD;
        device->readStsRegWipCmd->cmdRate = CY_SMIF_DDR;
        device->readStsRegWipCmd->cmdWidth = CY_SMIF_WIDTH_OCTAL;
        device->readStsRegWipCmd->cmdPresence = CY_SMIF_PRESENT_2BYTE;
        device->readStsRegWipCmd->addrRate = CY_SMIF_DDR;
        device->readStsRegWipCmd->addrWidth = CY_SMIF_WIDTH_OCTAL;
        device->readStsRegWipCmd->dummyCycles= 3;
        device->readStsRegWipCmd->dummyCyclesPresence = CY_SMIF_PRESENT_2BYTE;

        /* Change Chip Erase command to 16-bit Octal DDR */
        device->chipEraseCmd->commandH = CY_SMIF_CHIP_ERASE_CMD;
        device->chipEraseCmd->cmdRate = CY_SMIF_DDR;
        device->chipEraseCmd->cmdWidth = CY_SMIF_WIDTH_OCTAL;
        device->chipEraseCmd->cmdPresence = CY_SMIF_PRESENT_2BYTE;

        /* Change Chip Erase command to 16-bit Octal DDR */
        device->eraseCmd->commandH = CY_SMIF_CHIP_ERASE_CMD;
        device->eraseCmd->cmdRate = CY_SMIF_DDR;
        device->eraseCmd->cmdWidth = CY_SMIF_WIDTH_OCTAL;
        device->eraseCmd->cmdPresence = CY_SMIF_PRESENT_2BYTE;
        device->eraseCmd->addrRate = CY_SMIF_DDR;
        device->eraseCmd->addrWidth = CY_SMIF_WIDTH_OCTAL;

        /* Change Program command to 16-bit Octal DDR */
        device->programCmd->commandH = device->programCmd->command;
        device->programCmd->cmdRate = CY_SMIF_DDR;
        device->programCmd->cmdWidth = CY_SMIF_WIDTH_OCTAL;
        device->programCmd->cmdPresence = CY_SMIF_PRESENT_2BYTE;
        device->programCmd->addrRate = CY_SMIF_DDR;
        device->programCmd->addrWidth = CY_SMIF_WIDTH_OCTAL;
        device->programCmd->dataRate = CY_SMIF_DDR;
        device->programCmd->dataWidth = CY_SMIF_WIDTH_OCTAL;
    }
    return(result);
}
#endif
/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdReadStatus
****************************************************************************//**
*
* This function reads the status register. This function is a blocking function,
* it will block the execution flow until the status register is read.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* the Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode,
* this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param status
* The status register value returned by the external memory.
*
* \param command
* The command required to read the status/configuration register.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command reception.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdReadStatus(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    uint8_t *status,
                                    uint8_t command,
                                    cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result = CY_SMIF_CMD_NOT_FOUND;

    /* Read the memory status register */
    result = Cy_SMIF_TransmitCommand( base, command, CY_SMIF_WIDTH_SINGLE,
                NULL, CY_SMIF_CMD_WITHOUT_PARAM,
                CY_SMIF_WIDTH_NA, memDevice->slaveSelect,
                CY_SMIF_TX_NOT_LAST_BYTE, context);

    if (CY_SMIF_SUCCESS == result)
    {
        result = Cy_SMIF_ReceiveDataBlocking( base, status,
                    CY_SMIF_READ_ONE_BYTE, CY_SMIF_WIDTH_SINGLE, context);
    }

    return(result);
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdWriteStatus
****************************************************************************//**
*
* This function writes the status register. This is a blocking function, it will
* block the execution flow until the command transmission is completed.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* The Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode,
* this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param status
* The status to write into the status register.
*
* \param command
* The command to write into the status/configuration register.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdWriteStatus(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    void const *status,
                                    uint8_t command,
                                    cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result;

    /* The Write Enable */
    result =  Cy_SMIF_MemCmdWriteEnable(base, memDevice, context);

    /* The Write Status */
    if (CY_SMIF_SUCCESS == result)
    {
        uint32_t size;
        uint32_t qeMask = memDevice->deviceCfg->stsRegQuadEnableMask;

        size = ( (CY_SMIF_SFDP_QE_BIT_1_OF_SR_2 == qeMask) && (memDevice->deviceCfg->writeStsRegQeCmd->command == CY_SMIF_WRITE_STATUS_REG1_CMD)) ?
                  CY_SMIF_WRITE_TWO_BYTES:CY_SMIF_WRITE_ONE_BYTE;
        result = Cy_SMIF_TransmitCommand( base, command, CY_SMIF_WIDTH_SINGLE,
                    (uint8_t const *)status, size, CY_SMIF_WIDTH_SINGLE,
                    memDevice->slaveSelect, CY_SMIF_TX_LAST_BYTE, context);
    }

    return(result);
}
/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdChipErase
****************************************************************************//**
*
* This function performs a chip erase of the external memory. The Write Enable
* command is called before this API.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode,
* this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdChipErase(SMIF_Type *base,
                cy_stc_smif_mem_config_t const *memDevice,
                cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result= CY_SMIF_CMD_NOT_FOUND;

    cy_stc_smif_mem_cmd_t *cmdErase = memDevice->deviceCfg->chipEraseCmd;
    if(NULL != cmdErase)
    {
        result = Cy_SMIF_TransmitCommand( base, (uint8_t)cmdErase->command,
                cmdErase->cmdWidth, NULL,
                CY_SMIF_CMD_WITHOUT_PARAM, CY_SMIF_WIDTH_NA,
                memDevice->slaveSelect, CY_SMIF_TX_LAST_BYTE, context);
    }

    return(result);
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdSectorErase
****************************************************************************//**
*
* This function performs a block Erase of the external memory. The Write Enable
* command is called before this API.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* The Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode,
* this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param sectorAddr
* The sector address to erase.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_BAD_PARAM
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdSectorErase(SMIF_Type *base,
                                        cy_stc_smif_mem_config_t const *memDevice,
                                        uint8_t const *sectorAddr,
                                        cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;

    CY_ASSERT_L1(NULL != memDevice);

    if (NULL != sectorAddr)
    {
        cy_stc_smif_mem_device_cfg_t *device = memDevice->deviceCfg;
        cy_stc_smif_mem_cmd_t *cmdErase = device->eraseCmd;
        cy_stc_smif_hybrid_region_info_t* hybrInfo = NULL;

        result = Cy_SMIF_MemLocateHybridRegion(memDevice, &hybrInfo,
                ByteArrayToValue(sectorAddr, device->numOfAddrBytes));

        if ((NULL != cmdErase) && (CY_SMIF_WIDTH_NA != cmdErase->cmdWidth) && (result != CY_SMIF_BAD_PARAM))
        {
            uint16_t eraseCommand = (uint16_t)((result == CY_SMIF_SUCCESS) ? (hybrInfo->eraseCmd) : (cmdErase->command));
#if (CY_IP_MXSMIF_VERSION>=2)
            if (device->eraseCmd->cmdWidth != CY_SMIF_WIDTH_OCTAL)
            {
#endif
                result = Cy_SMIF_TransmitCommand( base, (uint8_t)eraseCommand,
                        cmdErase->cmdWidth, sectorAddr, device->numOfAddrBytes,
                        cmdErase->cmdWidth, memDevice->slaveSelect,
                        CY_SMIF_TX_LAST_BYTE, context);

#if (CY_IP_MXSMIF_VERSION>=2)
            }
            else
            {
                result = Cy_SMIF_TransmitCommand_Ext( base, (eraseCommand | ((uint16_t)eraseCommand << 8)),
                    true,cmdErase->cmdWidth, cmdErase->cmdRate, sectorAddr, device->numOfAddrBytes,
                    cmdErase->cmdWidth, cmdErase->addrRate, memDevice->slaveSelect,
                    CY_SMIF_TX_LAST_BYTE, context);

            }
#endif
        }
        else
        {
            result = CY_SMIF_CMD_NOT_FOUND;
        }
    }
    return(result);
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdProgram
****************************************************************************//**
*
* This function performs the Program operation.
*
* \note This function uses the  Cy_SMIF_TransmitCommand() API.
* The Cy_SMIF_TransmitCommand() API works in the blocking mode. In the dual quad mode,
* this API works with both types of memory simultaneously.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param addr
* The address to program.
*
* \param writeBuff
* The pointer to the data to program. If this pointer is a NULL, then the
* function does not enable the interrupt. This use case is  typically used when
* the FIFO is handled outside the interrupt and is managed in either a
* polling-based code or a DMA. The user would handle the FIFO management
* in a DMA or a polling-based code.
* If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation
* \ref Cy_SMIF_TransmitData().
*
* \param size
* The size of data to program. The user must ensure that the data size
* does not exceed the page size.
*
* \param cmdCompleteCb
* The callback function to call after the transfer completion. NULL interpreted
* as no callback.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of a transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_BAD_PARAM
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdProgram(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    uint8_t const *addr,
                                    uint8_t const *writeBuff,
                                    uint32_t size,
                                    cy_smif_event_cb_t cmdCompleteCb,
                                    cy_stc_smif_context_t *context)
{
    cy_en_smif_status_t result = CY_SMIF_SUCCESS;
    cy_en_smif_slave_select_t slaveSelected;

    cy_stc_smif_mem_device_cfg_t *device = memDevice->deviceCfg;
    cy_stc_smif_mem_cmd_t *cmdProg = device->programCmd;

    if(NULL == cmdProg)
    {
        result = CY_SMIF_CMD_NOT_FOUND;
    }
    else if ((NULL == addr) || (size > device->programSize))
    {
        result = CY_SMIF_BAD_PARAM;
    }
    else
    {
        slaveSelected = (0U == memDevice->dualQuadSlots)?  memDevice->slaveSelect :
                                                        (cy_en_smif_slave_select_t)memDevice->dualQuadSlots;

#if (CY_IP_MXSMIF_VERSION>=2)
        if(cmdProg->cmdWidth == CY_SMIF_WIDTH_OCTAL)
        {
            /* The page program command */
            result = Cy_SMIF_TransmitCommand_Ext( base, (uint16_t)(cmdProg->command | cmdProg->command << 8),
                    true,
                    cmdProg->cmdWidth, cmdProg->cmdRate,
                    addr, device->numOfAddrBytes,
                    cmdProg->addrWidth, cmdProg->addrRate, slaveSelected, CY_SMIF_TX_NOT_LAST_BYTE,
                    context);

            if((CY_SMIF_SUCCESS == result) && (CY_SMIF_NO_COMMAND_OR_MODE != cmdProg->mode))
            {
                result = Cy_SMIF_TransmitCommand(base, (uint8_t)cmdProg->mode,
                            cmdProg->modeWidth, NULL,
                            CY_SMIF_CMD_WITHOUT_PARAM, CY_SMIF_WIDTH_NA,
                            (cy_en_smif_slave_select_t)slaveSelected,
                            CY_SMIF_TX_NOT_LAST_BYTE, context);
            }

            if((CY_SMIF_SUCCESS == result) && (cmdProg->dummyCycles > 0U))
            {
                result = Cy_SMIF_SendDummyCycles_Ext(base, CY_SMIF_WIDTH_OCTAL, cmdProg->addrRate, cmdProg->dummyCycles);
            }

            if(CY_SMIF_SUCCESS == result)
            {
                result = Cy_SMIF_TransmitData_Ext( base, writeBuff, size,
                        cmdProg->dataWidth, cmdProg->dataRate, cmdCompleteCb, context);
            }

        }
        else
        {
#endif
            /* The page program command */
            result = Cy_SMIF_TransmitCommand( base, (uint8_t)cmdProg->command,
                    cmdProg->cmdWidth, addr, device->numOfAddrBytes,
                    cmdProg->addrWidth, slaveSelected, CY_SMIF_TX_NOT_LAST_BYTE,
                    context);

            if((CY_SMIF_SUCCESS == result) && (CY_SMIF_NO_COMMAND_OR_MODE != cmdProg->mode))
            {
                result = Cy_SMIF_TransmitCommand(base, (uint8_t)cmdProg->mode,
                            cmdProg->modeWidth, NULL,
                            CY_SMIF_CMD_WITHOUT_PARAM, CY_SMIF_WIDTH_NA,
                            (cy_en_smif_slave_select_t)slaveSelected,
                            CY_SMIF_TX_NOT_LAST_BYTE, context);
            }

            if((CY_SMIF_SUCCESS == result) && (cmdProg->dummyCycles > 0U))
            {
                result = Cy_SMIF_SendDummyCycles(base, cmdProg->dummyCycles);
            }

            if(CY_SMIF_SUCCESS == result)
            {
                result = Cy_SMIF_TransmitData( base, writeBuff, size,
                        cmdProg->dataWidth, cmdCompleteCb, context);
            }
#if (CY_IP_MXSMIF_VERSION>=2)
        }
#endif
    }

    return(result);
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdRead
****************************************************************************//**
*
* This function performs the Read operation.
*
* \note This function uses the Cy_SMIF_TransmitCommand() API.
* The Cy_SMIF_TransmitCommand() API works in the blocking mode. In the dual quad mode,
* this API works with both types of memory simultaneously.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param addr
* The address to read.
*
* \param readBuff
* The pointer to the variable where the read data is stored. If this pointer is
* a NULL, then the function does not enable the interrupt. This use case is
* typically used when the FIFO is handled outside the interrupt and is managed
* in either a  polling-based code or a DMA. The user would handle the FIFO
* management in a DMA or a polling-based code.
* If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation
* \ref Cy_SMIF_TransmitData().
*
* \param size
* The size of data to read.
*
* \param cmdCompleteCb
* The callback function to call after the transfer completion. NULL interpreted
* as no callback.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_BAD_PARAM
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdRead(SMIF_Type *base,
                                cy_stc_smif_mem_config_t const *memDevice,
                                uint8_t const *addr,
                                uint8_t* readBuff,
                                uint32_t size,
                                cy_smif_event_cb_t cmdCompleteCb,
                                cy_stc_smif_context_t *context)
{
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;
    cy_en_smif_slave_select_t slaveSelected;
    cy_stc_smif_mem_device_cfg_t *device = memDevice->deviceCfg;
    cy_stc_smif_mem_cmd_t *cmdRead = device->readCmd;

    if(NULL == cmdRead)
    {
        result = CY_SMIF_CMD_NOT_FOUND;
    }
    else if(NULL == addr)
    {
        result = CY_SMIF_BAD_PARAM;
    }
    else
    {
        slaveSelected = (0U == memDevice->dualQuadSlots)?  memDevice->slaveSelect :
                               (cy_en_smif_slave_select_t)memDevice->dualQuadSlots;

        result = Cy_SMIF_TransmitCommand( base, (uint8_t)cmdRead->command,
                    cmdRead->cmdWidth, addr, device->numOfAddrBytes,
                    cmdRead->addrWidth, slaveSelected, CY_SMIF_TX_NOT_LAST_BYTE,
                    context);

        if((CY_SMIF_SUCCESS == result) && (CY_SMIF_NO_COMMAND_OR_MODE != cmdRead->mode))
        {
            result = Cy_SMIF_TransmitCommand(base, (uint8_t)cmdRead->mode,
                        cmdRead->modeWidth, NULL,
                        CY_SMIF_CMD_WITHOUT_PARAM, CY_SMIF_WIDTH_NA,
                        (cy_en_smif_slave_select_t)slaveSelected,
                        CY_SMIF_TX_NOT_LAST_BYTE, context);
        }

        if((CY_SMIF_SUCCESS == result) && (0U < cmdRead->dummyCycles))
        {
            result = Cy_SMIF_SendDummyCycles(base, cmdRead->dummyCycles);
        }

        if(CY_SMIF_SUCCESS == result)
        {
            result = Cy_SMIF_ReceiveData(base, readBuff, size,
                        cmdRead->dataWidth, cmdCompleteCb, context);
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemLocateHybridRegion
****************************************************************************//**
*
* This function locates the region structure by the address which belongs to it.
*
* \note This function is valid for the memories with hybrid sectors.
*
* \param memDevice
* The memory device configuration.
*
* \param regionInfo
* Places a hybrid region configuration structure that contains the region
* specific parameters. See \ref cy_stc_smif_hybrid_region_info_t for
* reference.
*
* \param address
* The address for which a region is searched.
*
* \return A status of the region location.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_NOT_HYBRID_MEM
*       - \ref CY_SMIF_BAD_PARAM
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_MemLocateHybridRegion
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemLocateHybridRegion(cy_stc_smif_mem_config_t const *memDevice,
                                               cy_stc_smif_hybrid_region_info_t** regionInfo,
                                               uint32_t address)
{
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;
    cy_stc_smif_hybrid_region_info_t* currInfo = NULL;
    CY_ASSERT_L1(NULL != memDevice);
    cy_stc_smif_mem_device_cfg_t *device = memDevice->deviceCfg;

    /* Check if the address exceeds the memory size */
    if(address < device->memSize)
    {
        result = CY_SMIF_NOT_HYBRID_MEM;
        /* Check if the memory is hybrid */
        if(NULL != device->hybridRegionInfo)
        {
            uint32_t idx;
            uint32_t regionStartAddr;
            uint32_t regionEndAddr;
            for(idx = 0UL; idx < device->hybridRegionCount; idx++)
            {
                currInfo = device->hybridRegionInfo[idx];
                regionStartAddr = currInfo->regionAddress;
                regionEndAddr = regionStartAddr + (currInfo->sectorsCount * currInfo->eraseSize);
                if ((address >= regionStartAddr) && (address < regionEndAddr))
                {
                    *regionInfo = currInfo;
                    result = CY_SMIF_SUCCESS;
                    break;
                }
            }
        }
    }

    return result;
}

/*******************************************************************************
* Function Name: Cy_SMIF_SetReadyPollingDelay
****************************************************************************//**
*
* This function sets the polling delay in micro seconds to check memory device availability.
* By default polling delay is set to 0.
*
* \param pollTimeoutUs
* Specifies the polling timeout value in micro seconds.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*
*******************************************************************************/
void Cy_SMIF_SetReadyPollingDelay(uint16_t pollTimeoutUs,
                                  cy_stc_smif_context_t *context)
{
    CY_ASSERT_L1(NULL != context);

    context->memReadyPollDealy = pollTimeoutUs;
}

/*******************************************************************************
* Function Name: Cy_SMIF_MemIsReady
****************************************************************************//**
*
* Polls the memory device to check whether it is ready to accept new commands or
* not until either it is ready or the retries have exceeded the limit.
* This is a blocking function, it will block the execution flow until
* the command transmission is completed.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memConfig
* The memory device configuration.
*
* \param timeoutUs
*  The timeout value in microseconds to apply while polling the memory.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The status of the operation.
* \ref CY_SMIF_SUCCESS        - Memory is ready to accept new commands.
* \ref CY_SMIF_EXCEED_TIMEOUT - Memory is busy.
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_MemIsReady
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemIsReady(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                       uint32_t timeoutUs, cy_stc_smif_context_t const *context)
{
    bool isBusy = Cy_SMIF_Memslot_IsBusy(base, (cy_stc_smif_mem_config_t* )memConfig, context);

    CY_ASSERT_L1(NULL != context);

    if (context->memReadyPollDealy > 0U)
    {
        if (isBusy)
        {
            uint16_t pollingDelay = (timeoutUs > context->memReadyPollDealy) ? context->memReadyPollDealy : (uint16_t)timeoutUs;
            do
            {
                /* Avoid using weak function if XIP is enabled */
                if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
                {
                    Cy_SysLib_DelayUs(pollingDelay);
                }
                else
                {
                    Cy_SysLib_Rtos_DelayUs(pollingDelay);
                }
                isBusy = Cy_SMIF_Memslot_IsBusy(base, (cy_stc_smif_mem_config_t* )memConfig, context);
                timeoutUs = (timeoutUs > pollingDelay) ? (timeoutUs - pollingDelay) : 0UL;
            } while(isBusy && (timeoutUs > 0UL));
        }
    }
    else
    {
        if(isBusy)
        {
            uint32_t delayMs = 0UL;
            uint32_t timeoutSlice = 0UL;
            uint16_t delayUs = 0U;

            /* Calculate the slice of time to split the timeoutUs delay into TIMEOUT_SLICE_DIV times */
            timeoutSlice = timeoutUs / TIMEOUT_SLICE_DIV;

            /* Reduce the slice if needed to avoid too big idle period between checking the busy state */
            if (timeoutSlice > TIMEOUT_SLICE_MAX)
            {
                timeoutSlice = TIMEOUT_SLICE_MAX;
            }
            if(timeoutSlice == 0UL)
            {
                timeoutSlice = 1UL;
            }

            do
            {
                delayMs = timeoutSlice / 1000UL;
                delayUs = (uint16_t) (timeoutSlice % 1000UL);

                /* Avoid using weak function if XIP is enabled */
                if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
                {
                    Cy_SysLib_Delay(delayMs);
                    Cy_SysLib_DelayUs(delayUs);
                }
                else
                {
                    Cy_SysLib_Rtos_Delay(delayMs);
                    Cy_SysLib_Rtos_DelayUs(delayUs);
                }

                isBusy = Cy_SMIF_Memslot_IsBusy(base, (cy_stc_smif_mem_config_t* )memConfig, context);

                timeoutUs = (timeoutUs > timeoutSlice) ? (timeoutUs - timeoutSlice) : 0UL;

            } while(isBusy && (timeoutUs > 0UL));
        }
    }

    return (isBusy ? CY_SMIF_EXCEED_TIMEOUT : CY_SMIF_SUCCESS);
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemIsQuadEnabled
****************************************************************************//**
*
* Checks whether the QE (Quad Enable) bit is set or not in the configuration
* register of the memory.
* This is a blocking function, it will block the execution flow until
* the command transmission is completed.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memConfig
* The memory device configuration.
*
* \param isQuadEnabled
* This parameter is updated to indicate whether quad mode is enabled (true) or
* not (false). The value is valid only when the function returns
* CY_SMIF_SUCCESS.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The status of the operation. See \ref cy_en_smif_status_t.
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_MemIsQuadEnabled
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemIsQuadEnabled(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                             bool *isQuadEnabled, cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t status;
    uint8_t readStatus = 0U;
    CY_ASSERT_L1(NULL !=  memConfig);
    uint32_t statusCmd = memConfig->deviceCfg->readStsRegQeCmd->command;
    uint8_t maskQE = (uint8_t) memConfig->deviceCfg->stsRegQuadEnableMask;

    status = Cy_SMIF_MemCmdReadStatus(base, memConfig, &readStatus, (uint8_t)statusCmd, context);

    *isQuadEnabled = false;
    if(CY_SMIF_SUCCESS == status)
    {
        /* Check whether quad mode is already enabled or not */
        *isQuadEnabled = (maskQE == (readStatus & maskQE));
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemEnableQuadMode
****************************************************************************//**
*
* Sets the QE (QUAD Enable) bit in the external memory
* configuration register to enable quad SPI mode.
* This is a blocking function, it will block the execution flow until
* the command transmission is completed.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memConfig
* The memory device configuration.
*
* \param timeoutUs
*  The timeout value in microseconds to apply while polling the memory.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The status of the operation. See \ref cy_en_smif_status_t.
*
* \funcusage
* See \ref Cy_SMIF_MemIsQuadEnabled usage.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemEnableQuadMode(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                              uint32_t timeoutUs, cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t status;

    CY_ASSERT_L1(NULL !=  memConfig);

    /* Send Write Enable to the external memory */
    status = Cy_SMIF_MemCmdWriteEnable(base, (cy_stc_smif_mem_config_t* )memConfig, context);

    if(CY_SMIF_SUCCESS == status)
    {
        status = Cy_SMIF_MemQuadEnable(base, (cy_stc_smif_mem_config_t* )memConfig, context);

        if(CY_SMIF_SUCCESS == status)
        {
            /* Poll the memory for the completion of the operation */
            status = Cy_SMIF_MemIsReady(base, memConfig, timeoutUs, context);
        }
    }

    return status;
}

/*******************************************************************************
* Function Name: Cy_SMIF_MemRead
****************************************************************************//**
*
* Reads data from the external memory and blocks until the read
* transfer is complete or a timeout occurs.
* This is a blocking function, it will block the execution flow until
* the command transmission is completed.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memConfig
* The memory device configuration.
*
* \param address
* The address to read data from.
*
* \param rxBuffer
* The buffer for storing the read data.
*
* \param length
* The size of data to read.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The status of the operation. See \ref cy_en_smif_status_t.
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_MemRead
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemRead(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                    uint32_t address, uint8_t rxBuffer[],
                                    uint32_t length, cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t status = CY_SMIF_BAD_PARAM;
    uint32_t chunk = 0UL;
    uint8_t addrArray[CY_SMIF_FOUR_BYTES_ADDR] = {0U};
    cy_stc_smif_mem_cmd_t *cmdRead;

    CY_ASSERT_L1(NULL != memConfig);
    CY_ASSERT_L1(NULL != rxBuffer);

    cmdRead = memConfig->deviceCfg->readCmd;

    if((address + length) <= memConfig->deviceCfg->memSize)  /* Check if the address exceeds the memory size */
    {
        uint32_t interruptState = 0;

        /* If XIP is enabled, disable interrupts to avoid task switching to XIP location */
        if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
        {
            interruptState = Cy_SysLib_EnterCriticalSection();
        }

        /* SMIF can read only up to 65536 bytes in one go. Split the larger read into multiple chunks */
        while (length > 0UL)
        {
            /* Get the number of bytes which can be read during one operation */
            chunk = (length > SMIF_MAX_RX_COUNT) ? (SMIF_MAX_RX_COUNT) : length;
            ValueToByteArray(address, &addrArray[0], 0UL,
                             memConfig->deviceCfg->numOfAddrBytes);

#if (CY_IP_MXSMIF_VERSION>=2)
            status = Cy_SMIF_TransmitCommand_Ext(base,
                                             (uint16_t)(cmdRead->command | cmdRead->commandH << 8),
                                             ((bool)cmdRead->commandH),
                                             cmdRead->cmdWidth,
                                             cmdRead->cmdRate,
                                             (const uint8_t *)addrArray,
                                             memConfig->deviceCfg->numOfAddrBytes,
                                             cmdRead->addrWidth,
                                             cmdRead->addrRate,
                                             memConfig->slaveSelect,
                                             CY_SMIF_TX_NOT_LAST_BYTE,
                                             context);

            if((CY_SMIF_SUCCESS == status) && (CY_SMIF_NO_COMMAND_OR_MODE != cmdRead->mode))
            {
                status = Cy_SMIF_TransmitCommand_Ext(base,
                                                 (uint16_t)cmdRead->mode,
                                                 false,
                                                 cmdRead->modeWidth,
                                                 cmdRead->modeRate,
                                                 NULL,
                                                 CY_SMIF_CMD_WITHOUT_PARAM,
                                                 CY_SMIF_WIDTH_NA,
                                                 cmdRead->modeRate,
                                                 memConfig->slaveSelect,
                                                 CY_SMIF_TX_NOT_LAST_BYTE,
                                                 context);
            }

            if((CY_SMIF_SUCCESS == status) && (0U < cmdRead->dummyCycles))
            {
                status = Cy_SMIF_SendDummyCycles_Ext(base, cmdRead->dataWidth, cmdRead->dataRate, cmdRead->dummyCycles);
            }

            if(CY_SMIF_SUCCESS == status)
            {
                 status = Cy_SMIF_ReceiveDataBlocking_Ext(base,
                                            rxBuffer,
                                            chunk,
                                            cmdRead->dataWidth,
                                            cmdRead->dataRate,
                                            context);
            }
#else
            status = Cy_SMIF_TransmitCommand(base,
                                                (uint8_t)cmdRead->command,
                                                cmdRead->cmdWidth,
                                                (const uint8_t *)addrArray,
                                                memConfig->deviceCfg->numOfAddrBytes,
                                                cmdRead->addrWidth,
                                                memConfig->slaveSelect,
                                                CY_SMIF_TX_NOT_LAST_BYTE,
                                                context);

            if((CY_SMIF_SUCCESS == status) && (CY_SMIF_NO_COMMAND_OR_MODE != cmdRead->mode))
            {
                status = Cy_SMIF_TransmitCommand(base,
                                                    (uint8_t)cmdRead->mode,
                                                    cmdRead->modeWidth,
                                                    NULL,
                                                    CY_SMIF_CMD_WITHOUT_PARAM,
                                                    CY_SMIF_WIDTH_NA,
                                                    memConfig->slaveSelect,
                                                    CY_SMIF_TX_NOT_LAST_BYTE,
                                                    context);
            }

            if((CY_SMIF_SUCCESS == status) && (0U < cmdRead->dummyCycles))
            {
                status = Cy_SMIF_SendDummyCycles(base, cmdRead->dummyCycles);
            }

            if(CY_SMIF_SUCCESS == status)
            {
                    status = Cy_SMIF_ReceiveDataBlocking(base,
                                            rxBuffer,
                                            chunk,
                                            cmdRead->dataWidth,
                                            context);
            }
#endif /* CY_IP_MXSMIF_VERSION */

            if(CY_SMIF_SUCCESS != status)
            {
                break;
            }

            /* Recalculate the next rxBuffer offset */
            length -= chunk;
            address += chunk;
            rxBuffer = (uint8_t *)rxBuffer + chunk;
        }
        /* Restore interrupts */
        if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
        {
             Cy_SysLib_ExitCriticalSection(interruptState);
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemWrite
****************************************************************************//**
*
* This function writes data to the external memory.
* This is a blocking function, it will block the execution flow until
* the command transmission is completed.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memConfig
* The memory device configuration.
*
* \param address
* The address to write data at.
*
* \param txBuffer
* The buffer holding the data to write in the external memory.
*
* \param length
* The size of data to write.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The status of the operation. See \ref cy_en_smif_status_t.
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_MemWrite
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemWrite(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                     uint32_t address, uint8_t const txBuffer[],
                                     uint32_t length, cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t status = CY_SMIF_BAD_PARAM;
    uint32_t offset = 0UL;
    uint32_t chunk = 0UL;
    uint32_t pageSize;
    uint8_t addrArray[CY_SMIF_FOUR_BYTES_ADDR] = {0U};
    cy_stc_smif_mem_cmd_t *cmdProgram;

    CY_ASSERT_L1(NULL != memConfig);
    CY_ASSERT_L1(NULL != txBuffer);

    pageSize = memConfig->deviceCfg->programSize; /* Get the page size */
    cmdProgram = memConfig->deviceCfg->programCmd; /* Get the program command */

    if((address + length) <= memConfig->deviceCfg->memSize)  /* Check if the address exceeds the memory size */
    {
        uint32_t interruptState = 0;

        /* If XIP is enabled, disable interrupts to avoid task switching to XIP location */
        if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
        {
            interruptState = Cy_SysLib_EnterCriticalSection();
        }
        /* SMIF can read only up to 65536 bytes in one go. Split the larger read into multiple chunks */
        while (length > 0UL)
        {
            /* Get the number of bytes which can be written during one operation */
            offset = address % pageSize;
            chunk = ((offset + length) < pageSize) ? length : (pageSize - offset);

            /* The Write Enable bit may be cleared by the memory after every successful
             * operation of write or erase operations. Therefore, must be set for
             * every loop.
             */
            status = Cy_SMIF_MemCmdWriteEnable(base, memConfig, context);

            if(CY_SMIF_SUCCESS == status)
            {
                ValueToByteArray(address, &addrArray[0], 0UL,
                                 memConfig->deviceCfg->numOfAddrBytes);

                status = Cy_SMIF_TransmitCommand(base,
                                                 (uint8_t)cmdProgram->command,
                                                 cmdProgram->cmdWidth,
                                                 (const uint8_t *)addrArray,
                                                 memConfig->deviceCfg->numOfAddrBytes,
                                                 cmdProgram->addrWidth,
                                                 memConfig->slaveSelect,
                                                 CY_SMIF_TX_NOT_LAST_BYTE,
                                                 context);

                if((CY_SMIF_SUCCESS == status) && (CY_SMIF_NO_COMMAND_OR_MODE != cmdProgram->mode))
                {
                    status = Cy_SMIF_TransmitCommand(base,
                                                     (uint8_t)cmdProgram->mode,
                                                     cmdProgram->modeWidth,
                                                     NULL,
                                                     CY_SMIF_CMD_WITHOUT_PARAM,
                                                     CY_SMIF_WIDTH_NA,
                                                     memConfig->slaveSelect,
                                                     CY_SMIF_TX_NOT_LAST_BYTE,
                                                     context);
                }

                if((CY_SMIF_SUCCESS == status) && (cmdProgram->dummyCycles > 0U))
                {
                    status = Cy_SMIF_SendDummyCycles(base, cmdProgram->dummyCycles);
                }

                if(CY_SMIF_SUCCESS == status)
                {
                    status = Cy_SMIF_TransmitDataBlocking(base,
                                                         (uint8_t *)txBuffer,
                                                         chunk,
                                                         cmdProgram->dataWidth,
                                                         context);
                }

                if(CY_SMIF_SUCCESS == status)
                {
                    /* Check if the memory has completed the write operation. ProgramTime is in microseconds */
                    status = Cy_SMIF_MemIsReady(base, memConfig, memConfig->deviceCfg->programTime, context);
                }
                    }

            if(CY_SMIF_SUCCESS != status)
            {
                break;
            }

            /* Recalculate the next rxBuffer offset */
            txBuffer = (uint8_t *)txBuffer + chunk;
            address += chunk;
            length -= chunk;
        }
        /* Restore interrupts */
        if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
        {
            Cy_SysLib_ExitCriticalSection(interruptState);
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemEraseSector
****************************************************************************//**
*
* Erases a block/sector of the external memory.
* This is a blocking function, it will block the execution flow until
* the command transmission is completed.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memConfig
* The memory device configuration.
*
* \param address
* The address of the block to be erased. The address will be aligned to
* the start address of the sector in which address is located.
*
* \param length
* The length of data to erase. The length will be aligned to the sector
* boundary where end address is located. If length exceeds memory size
* API returns \ref CY_SMIF_BAD_PARAM without performing erase operation.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The status of the operation. See \ref cy_en_smif_status_t.
*
* \note Memories like hybrid have sectors of different sizes. \n
* Check the address and length parameters before calling this function.
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_MemEraseSector
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemEraseSector(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                           uint32_t address, uint32_t length,
                                           cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t status = CY_SMIF_SUCCESS;
    uint32_t endAddress = address + length - 1UL;
    uint32_t hybridRegionEnd = 0UL;
    uint32_t hybridRegionStart = 0UL;
    uint8_t addrArray[CY_SMIF_FOUR_BYTES_ADDR] = {0U};
    cy_stc_smif_hybrid_region_info_t* hybrInfo = NULL;
    CY_ASSERT_L1(NULL != memConfig);
    cy_stc_smif_mem_device_cfg_t *device = memConfig->deviceCfg;
    uint32_t eraseSectorSize = device->eraseSize;
    uint32_t maxEraseTime = device->eraseTime;

    /* Check if the address exceeds the memory size */
    if (endAddress < device->memSize)
    {
        /* Align start address and end address to corresponding sector boundary */
        cy_stc_smif_hybrid_region_info_t* regionInfo = NULL;

        /* Check if it is a hybrid memory */
        status = Cy_SMIF_MemLocateHybridRegion(memConfig, &regionInfo, address);

        if ((CY_SMIF_SUCCESS == status) && (regionInfo != NULL)) /* Hybrid */
        {
            uint32_t offsetInRegion = address - regionInfo->regionAddress;
            uint32_t sectorOffsetInRegion = offsetInRegion / regionInfo->eraseSize;

            /* Align start address */
            address = regionInfo->regionAddress + (sectorOffsetInRegion * regionInfo->eraseSize);

            /* Last hybrid region in desired block */
            status = Cy_SMIF_MemLocateHybridRegion(memConfig, &regionInfo, endAddress);
            if (CY_SMIF_SUCCESS == status)
            {
                offsetInRegion = endAddress - regionInfo->regionAddress + 1UL;
                sectorOffsetInRegion  = offsetInRegion / regionInfo->eraseSize;
                if (0UL != offsetInRegion % regionInfo->eraseSize)
                {
                    sectorOffsetInRegion++;
                }
                /* Align end address */
                endAddress = regionInfo->regionAddress + (sectorOffsetInRegion * regionInfo->eraseSize);

                /* Update length according the aligned start address and end address */
                length = endAddress - address;
            }
        }
        else /* Not hybrid (unified) sectors layout */
        {
            /* If start address is somewhere at the middle of erase page, align it to the page start */
            if (0UL != (address % eraseSectorSize))
            {
                address = eraseSectorSize * (address / eraseSectorSize);
            }

            /* If end address is somewhere at the middle of erase page, align it to the page end */
            if (0UL != ((endAddress + 1UL) % eraseSectorSize))
            {
                endAddress = (eraseSectorSize * (endAddress + 1UL) / eraseSectorSize);
            }
            /* Update length according the aligned start address and end address */
            length = endAddress - address + 1UL;

            status = CY_SMIF_SUCCESS;
        }

        /* Check if the address exceeds the memory size */
        if (endAddress < device->memSize)
        {
            uint32_t interruptState = 0UL;

            /* If XIP is enabled, disable interrupts to avoid task switching to a code running in
             * XIP when erase operation is ongoing */
            if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
            {
                interruptState = Cy_SysLib_EnterCriticalSection();
            }

            while(length > 0UL)
            {
                /* In case of hybrid memory - update erase size and time for current region */
                status = Cy_SMIF_MemLocateHybridRegion(memConfig, &hybrInfo, address);
                if (CY_SMIF_SUCCESS == status)
                {
                    maxEraseTime =  hybrInfo->eraseTime;
                    eraseSectorSize = hybrInfo->eraseSize;
                    hybridRegionStart = hybrInfo->regionAddress;
                    hybridRegionEnd = (hybrInfo->sectorsCount * eraseSectorSize) + hybridRegionStart - 1UL;
                    if(endAddress < hybridRegionEnd)
                    {
                        hybridRegionEnd = endAddress;
                    }
                }
                else
                {
                    hybridRegionEnd = endAddress;
                }

                while (address < hybridRegionEnd)
                {
                    /* The Write Enable bit may be cleared by the memory after every successful
                    * operation of write/erase operations. Therefore, it must be set for
                    * every loop.
                    */
                    status = Cy_SMIF_MemCmdWriteEnable(base, memConfig, context);
                    if(CY_SMIF_SUCCESS == status)
                    {
                        ValueToByteArray(address, &addrArray[0], 0UL, device->numOfAddrBytes);

                        /* Send the command to erase one sector */
                        status = Cy_SMIF_MemCmdSectorErase(base, (cy_stc_smif_mem_config_t* )memConfig,
                                                           (const uint8_t *)addrArray, context);
                        if(CY_SMIF_SUCCESS == status)
                        {
                            /* Wait until the erase operation is completed or a timeout occurs.
                             * Note: eraseTime is in milliseconds */
                            status = Cy_SMIF_MemIsReady(base, memConfig, (maxEraseTime * ONE_MILLI_IN_MICRO), context);

                            /* Recalculate the next sector address offset */
                            if(length > eraseSectorSize)
                            {
                                address += eraseSectorSize;
                                length -= eraseSectorSize;
                            }
                            else
                            {
                                length = 0;
                                break;
                            }
                        }
                    }

                    if(CY_SMIF_SUCCESS != status)
                    {
                        break;
                    }
                }
            }

            /* Restore interrupts */
            if (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 0U)
            {
                Cy_SysLib_ExitCriticalSection(interruptState);
            }
        }
        else
        {
            /* Aligned end address exceeds memory size */
            status = CY_SMIF_BAD_PARAM;
        }
    }
    else
    {
        /* end address exceeds memory size */
        status = CY_SMIF_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_SMIF_MemEraseChip
****************************************************************************//**
*
* Erases the entire chip of the external memory.
* This is a blocking function, it will block the execution flow until
* the command transmission is completed.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memConfig
* The memory device configuration.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return The status of the operation. See \ref cy_en_smif_status_t.
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_MemEraseChip
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemEraseChip(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                         cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t status;

    CY_ASSERT_L1(NULL != memConfig);

    /* The Write Enable bit may be cleared by the memory after every successful
    * operation of write/erase operations. Therefore, it must be set for
    * every loop
    */
    status = Cy_SMIF_MemCmdWriteEnable(base, memConfig, context);

    if(CY_SMIF_SUCCESS == status)
    {
        /* Send the command to erase the entire chip */
        status = Cy_SMIF_MemCmdChipErase(base, memConfig, context);

        if(CY_SMIF_SUCCESS == status)
        {
            /* Wait until the erase operation is completed or a timeout occurs. chipEraseTime is in milliseconds */
            status = Cy_SMIF_MemIsReady(base, memConfig,
                     (memConfig->deviceCfg->chipEraseTime * ONE_MILLI_IN_MICRO), context);
        }
    }

    return status;
}

/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdPowerDown
****************************************************************************//**
*
* This function sends a Power-down command to the selected memory device in
* Single SPI mode. Please note that, once \ref Cy_SMIF_MemCmdPowerDown is issued, external
* memory will not respond to any other command except \ref Cy_SMIF_MemCmdReleasePowerDown.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode
* this API should be called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command transmission.
*        - \ref CY_SMIF_SUCCESS
*        - \ref CY_SMIF_EXCEED_TIMEOUT
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdPowerDown(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context)
{

    cy_en_smif_status_t result;

    /* The memory Power-down command */
    result = Cy_SMIF_TransmitCommand( base, CY_SMIF_POWER_DOWN_CMD,
                                          CY_SMIF_WIDTH_SINGLE,
                                          NULL,
                                          CY_SMIF_CMD_WITHOUT_PARAM,
                                          CY_SMIF_WIDTH_NA,
                                          memDevice->slaveSelect,
                                          CY_SMIF_TX_LAST_BYTE,
                                          context);

    return result;
}
/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdReleasePowerDown
****************************************************************************//**
*
* This function sends a Release Power-down command to the selected memory device
* in Single SPI mode.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode
* this API should be called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memDevice
* The device to which the command is sent.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command transmission.
*        - \ref CY_SMIF_SUCCESS
*        - \ref CY_SMIF_EXCEED_TIMEOUT
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemCmdReleasePowerDown(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context)
{

    cy_en_smif_status_t result;

    /* The memory Release Power-down command */
    result = Cy_SMIF_TransmitCommand( base, CY_SMIF_RELEASE_POWER_DOWN_CMD,
                                          CY_SMIF_WIDTH_SINGLE,
                                          NULL,
                                          CY_SMIF_CMD_WITHOUT_PARAM,
                                          CY_SMIF_WIDTH_NA,
                                          memDevice->slaveSelect,
                                          CY_SMIF_TX_LAST_BYTE,
                                          context);

    return result;
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXSMIF */

/* [] END OF FILE */
