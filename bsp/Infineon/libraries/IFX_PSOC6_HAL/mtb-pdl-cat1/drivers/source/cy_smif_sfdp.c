/***************************************************************************//**
* \file cy_smif_sfdp.c
* \version 2.40
*
* \brief
*  This file provides the source code for SFDP enumeration in SMIF driver.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2022 Cypress Semiconductor Corporation
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

#define READ_ENHANCED_MODE_DISABLED (0xFFU)
#define BITS_IN_BYTE                (8U)
#define BYTES_IN_DWORD              (4U)
#define FOUR_BYTE_ADDRESS           (4U)     /* 4 byte addressing mode */
#define BITS_IN_BYTE_ABOVE_4GB      (3U)     /* Density of memory above 4GBit stored as poser of 2 */
#define PARAM_HEADERS_NUM           (CY_SMIF_SFDP_BFPT_BYTE_06)
#define FIRST_HEADER_OFFSET         (0x08U)  /* The offset of the 1-st Parameter Header */
#define PARAM_ID_MSB_REL_OFFSET     (0x07U)  /* The relative offset of Parameter ID MSB
                                             * in the SFDP Header table
                                             */
#define PARAM_MINOR_REV_REL_OFFSET  (0x01U)  /* The relative offset of Parameter Minor Revision
                                             * in the SFDP Header table
                                             */
#define PARAM_MAJOR_REV_REL_OFFSET  (0x02U)  /* The relative offset of Parameter Major Revision
                                             * in the SFDP Header table
                                             */
#define PARAM_TABLE_PRT_OFFSET      (0x04UL) /* The relative offset of Parameter Table Pointer Byte 1 */
#define PARAM_TABLE_LENGTH_OFFSET   (0X03U)  /* The offset of Parameter Table Length in the Header Table */
#define PARAM_HEADER_NUM            (6U)     /* The supported number of the parameter headers */
#define HEADER_LENGTH               (0x8U)   /* The length of the SFDP header */
#define HEADERS_LENGTH              (HEADER_LENGTH + \
                                                 (CY_SMIF_SFDP_PARAM_HEADER_LENGTH * PARAM_HEADER_NUM))
#define TYPE_STEP                   (2UL)    /* The Erase Type step in the Basic Flash Parameter Table */
#define INSTRUCTION_NOT_SUPPORTED   (0XFFU)  /* The code for the not supported instruction */
#define BASIC_SPI_ID                (0XFF00UL) /* The JEDEC SFDP Basic SPI Flash Parameter ID */
#define SECTOR_MAP_ID               (0xFF81UL) /* The JEDEC SFDP Sector Map ID */
#define SECTOR_MAP_DESCRIPTOR_MASK   (0x2U)  /* The mask for the type bit of the Sector Map descriptor */
#define SECTOR_MAP_COMAND_DESCRIPTOR_TYPE (0U) /* Code for the command descriptor type */
#define SECTOR_MAP_REGION_SIZE_MULTIPLIER (256UL) /* The multiplier for region size units */
#define FOUR_BYTE_ADDR_ID           (0XFF84UL) /* The 4-byte Address Instruction Table is assigned the ID MSB of FFh */
#define FOUR_BYTE_ADDR_ERASE_TYPE_1 (0X4UL)  /* The Erase Type 1 offset in 4-byte Address Instruction Table */
#define FOUR_BYTE_ADDR_ERASE_TYPE_4 (0X7UL)  /* The Erase Type 4 offset in 4-byte Address Instruction Table */
#define ERASE_T_COUNT_Pos           (0UL)    /* Erase Type X Erase, Typical time: count (Bits 4:0) */
#define ERASE_T_COUNT_Msk           (0x1FUL) /* Erase Type X Erase, Typical time: count (Bitfield-Mask) */
#define ERASE_T_UNITS_Pos           (5UL)    /* Erase Type X Erase, Typical time: units (Bits 6:5) */
#define ERASE_T_UNITS_Msk           (0x60UL) /* Erase Type X Erase, Typical time: units (Bitfield-Mask) */
#define ERASE_T_COUNT_OFFSET        (0x04U)  /* The offset of the Erase count 10th DWORD */
#define ERASE_T_LENGTH              (0x07U)  /* The Erase Type Typical time length */
#define SCCR_MAP_SPI_ID             (0xFF87U)  /* SCCR Map for SPI Memory Devices MSB */
#define XSPI_PROFILE_1_0_ID         (0xFF05UL) /* eXtended Serial Peripheral Interface (xSPI) Profile 1.0 */
#define CMD_SEQ_FOR_ODDR_ID         (0xFF0AUL) /* Command Sequences to change to Octal DDR (8D-8D-8D) mode */
#define COMMAND_IS_NOT_FOUND        (0x0U)
#define PARAMETER_IS_NOT_FOUND      (0x0U)

#define SMIF_TRANSFER_TIMEOUT       (1000UL)      /* The timeout (microseconds) to use in polling of
                                                   * the transfer status of the SMIF block
                                                   */
#define SUPPORT_ERASE_COMMAND_Pos   (1UL)          /* The position of the Support for Erase Commands
                                                   * in byte 1 of the JEDEC 4-byte Address Instruction Table
                                                   */
#define SUPPORT_ERASE_COMMAND_Msk   (0x0000001EUL) /* The mask of the Support for Erase Commands
                                                   * in the JEDEC 4-byte Address Instruction Table
                                                   */
#define SUPPORT_FAST_READ_1S_1S_1S_CMD_Pos (1UL)          /* The position of the Support for Fast Read Command 1S-1S-1S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_1S_1S_CMD_Msk (0x00000002UL) /* The mask of the Support for Fast Read Command 1S-1S-1S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_1S_2S_CMD_Pos (2UL)          /* The position of the Support for Fast Read Command 1S-1S-2S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_1S_2S_CMD_Msk (0x00000004UL) /* The mask of the Support for Fast Read Command 1S-1S-2S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_2S_2S_CMD_Pos (3UL)          /* The position of the Support for Fast Read Command 1S-2S-2S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_2S_2S_CMD_Msk (0x00000008UL) /* The mask of the Support for Fast Read Command 1S-2S-2S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_1S_4S_CMD_Pos (4UL)          /* The position of the Support for Fast Read Command 1S-1S-4S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_1S_4S_CMD_Msk (0x00000010UL) /* The mask of the Support for Fast Read Command 1S-1S-4S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_4S_4S_CMD_Pos (5UL)          /* The position of the Support for Fast Read Command 1S-4S-4S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_FAST_READ_1S_4S_4S_CMD_Msk (0x00000020UL) /* The mask of the Support for Fast Read Command 1S-4S-4S
                                                          * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                          */
#define SUPPORT_PP_1S_1S_1S_CMD_Pos (6UL)              /* The position of the Support for Page Program Command 1S-1S-1S
                                                        * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                        */
#define SUPPORT_PP_1S_1S_1S_CMD_Msk (0x00000040UL)     /* The mask of the Support for Page Program Command 1S-1S-1S
                                                        * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                        */
#define SUPPORT_PP_1S_1S_4S_CMD_Pos (7UL)              /* The position of the Support for Page Program Command 1S-1S-4S
                                                        * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                        */
#define SUPPORT_PP_1S_1S_4S_CMD_Msk (0x00000080UL)     /* The mask of the Support for Page Program Command 1S-1S-4S
                                                        * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                        */
#define SUPPORT_PP_1S_4S_4S_CMD_Pos (8UL)              /* The position of the Support for Page Program Command 1S-4S-4S
                                                        * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                        */
#define SUPPORT_PP_1S_4S_4S_CMD_Msk (0x00000100UL)     /* The mask of the Support for Page Program Command 1S-4S-4S
                                                        * in the JEDEC 4-byte Address Instruction Table, DWORD 1
                                                        */
#define SUPPORT_FAST_READ_1S_1S_8S_CMD_Pos (20UL)         /* The position of the Support for Fast Read Command 1S-1S-8S */
#define SUPPORT_FAST_READ_1S_1S_8S_CMD_Msk (0x00100000UL) /* The mask of the Support for Fast Read Command 1S-1S-8S */
#define SUPPORT_FAST_READ_1S_8S_8S_CMD_Pos (21UL)         /* The position of the Support for Fast Read Command 1S-8S-8S */
#define SUPPORT_FAST_READ_1S_8S_8S_CMD_Msk (0x00200000UL) /* The mask of the Support for Fast Read Command 1S-8S-8S */
#define SUPPORT_FAST_READ_1S_8D_8D_CMD_Pos (22UL)         /* The position of the Support for Fast Read Command 1S-8D-8D */
#define SUPPORT_FAST_READ_1S_8D_8D_CMD_Msk (0x00400000UL) /* The mask of the Support for Fast Read Command 1S-8D-8D */
#define SUPPORT_PP_1S_1S_8S_CMD_Pos        (23UL)         /* The position of the Support for Page Program Command 1S-1S-8S */
#define SUPPORT_PP_1S_1S_8S_CMD_Msk        (0x00400000UL) /* The mask of the Support for Page Program Command 1S-1S-8S */
#define SUPPORT_PP_1S_8S_8S_CMD_Pos        (24UL)         /* The position of the Support for Page Program Command 1S-8S-8S */
#define SUPPORT_PP_1S_8S_8S_CMD_Msk        (0x00400000UL) /* The mask of the Support for Page Program Command 1S-8S-8S */

#define FOUR_BYTE_ADDRESS_TABLE_BYTE_0 (0U)  /* Byte 0x00 of the JEDEC 4-byte Address Instruction Table */
#define FOUR_BYTE_ADDRESS_TABLE_BYTE_1 (1U)  /* Byte 0x01 of the JEDEC 4-byte Address Instruction Table */
#define ERASE_TYPE_COUNT               (4U)  /* The number of Erase Types  */

#define MEMORY_SIZE_16MB                (0x1000000U)

#define CY_SMIF_CHECK_DEVICE_MEMBERS(device)   ((NULL != device->writeEnCmd) || \
                                                (NULL != device->writeDisCmd) || \
                                                (NULL != device->writeDisCmd)|| \
                                                (NULL != device->eraseCmd)|| \
                                                (NULL != device->chipEraseCmd)|| \
                                                (NULL != device->programCmd)|| \
                                                (NULL != device->readStsRegWipCmd))

/***************************************
*     Internal enums
***************************************/
/** Specifies protocol mode. */
typedef enum
{
    PROTOCOL_MODE_1S_1S_1S        = 1U,     /**< One DQ signal used during command transfer,
                                             * address transfer, and data transfer. All phases are SDR.
                                             */
    PROTOCOL_MODE_1S_1S_2S        = 2U,     /**< One DQ signal used during command transfer, and address transfer,
                                             *  two DQ signals used during data transfer. All phases are SDR.
                                             */
    PROTOCOL_MODE_1S_2S_2S        = 3U,     /**< One DQ signal used during command transfer, two DQ signals used
                                             *  during address transfer, and data transfer. All phases are SDR.
                                             */
    PROTOCOL_MODE_1S_1S_4S        = 4U,     /**< One DQ signal used during command and address transfer,
                                             * four DQ signals used during data transfer. All phases are SDR.
                                             */
    PROTOCOL_MODE_1S_4S_4S        = 5U,     /**< One DQ signal used during command transfer, four DQ signals used
                                            * during address transfer, and data transfer. All phases are SDR.
                                            */
#if (CY_IP_MXSMIF_VERSION>=2)
    PROTOCOL_MODE_1S_4D_4D          = 6U,        /**< One DQ signal used during command transfer in single data rate,
                                        * four DQ signals used during address transfer and data transfer in
                                        * double data rate.
                                        */
    PROTOCOL_MODE_1S_1S_8S          = 7U,   /**< One DQ signal used during command and addresstransfer in single data rate,
                                              * eight DQ signals used during data transfer in
                                              * single data rate.
                                             */
    PROTOCOL_MODE_1S_8S_8S          = 8U,   /**< One DQ signal used during command transfer in single data rate,
                                              * eighth DQ signals used during address transfer and data transfer in
                                              * single data rate.
                                             */
    PROTOCOL_MODE_8D_8D_8D          = 9U,   /**< eight DQ signal used during command, address and data transfer in
                                              * double data rate.
                                             */
#endif /* CY_IP_MXSMIF_VERSION */
    PROTOCOL_MODE_WRONG           = 0xFFU   /**< Unknown or unsupported mode */
} cy_en_smif_protocol_mode_t;
/** \endcond */


/***************************************
*     Internal Structures
***************************************/

/**
* This internal structure is used to store data for erase types.
*/
typedef struct
{
    uint8_t eraseCmd;  /**< The instruction used for erase transaction */
    uint32_t eraseSize;    /**< The number of bytes to be erased at one erase transaction */
    uint32_t eraseTime;    /**< The maximum erase time for one erase transaction */
} cy_stc_smif_erase_type_t;


/***************************************
*     Internal Function Prototypes
***************************************/
static cy_en_smif_status_t SfdpReadBuffer(SMIF_Type *base,
                                         cy_stc_smif_mem_cmd_t const *cmdSfdp,
                                         uint8_t const sfdpAddress[],
                                         cy_en_smif_slave_select_t  slaveSelect,
                                         uint32_t size,
                                         uint8_t sfdpBuffer[],
                                         cy_stc_smif_context_t *context);
static uint32_t SfdpFindParameterHeader(uint32_t id, uint8_t const sfdpBuffer[]);
static void SfdpFindParameterTableAddress(uint32_t id,
                                          uint8_t const sfdpBuffer[],
                                          uint8_t address[],
                                          uint8_t *tableLength);
static uint32_t SfdpGetNumOfAddrBytes(uint8_t const sfdpBuffer[], uint32_t memorySize);
static uint32_t SfdpGetMemoryDensity(uint8_t const sfdpBuffer[]);
static void SfdpGetReadCmd_1_4_4(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead);
static void SfdpGetReadCmd_1_1_4(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead);
static void SfdpGetReadCmd_1_2_2(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead);
static void SfdpGetReadCmd_1_1_2(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead);
static void SfdpGetReadCmd_1_1_1(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead);
static cy_en_smif_protocol_mode_t SfdpGetReadCmdParams(uint8_t const sfdpBuffer[],
                                                       cy_en_smif_data_select_t dataSelect,
                                                       cy_en_smif_txfr_width_t maxDataWidth,
                                                       cy_stc_smif_mem_cmd_t* cmdRead);
static void SfdpGetReadFourBytesCmd(uint8_t const sfdpBuffer[],
                                    cy_en_smif_protocol_mode_t protocolMode,
                                    cy_stc_smif_mem_cmd_t* cmdRead);
static uint32_t SfdpGetPageSize(uint8_t const sfdpBuffer[]);
static uint32_t SfdpGetEraseTime(uint32_t const eraseOffset, uint8_t const sfdpBuffer[], cy_stc_smif_erase_type_t eraseType[]);
static uint32_t SfdpGetChipEraseTime(uint8_t const sfdpBuffer[]);
static uint32_t SfdpGetPageProgramTime(uint8_t const sfdpBuffer[]);
static void SfdpSetWriteEnableCommand(cy_stc_smif_mem_cmd_t* cmdWriteEnable);
static void SfdpSetWriteDisableCommand(cy_stc_smif_mem_cmd_t* cmdWriteDisable);
static void SfdpSetProgramCommand_1_1_1(cy_stc_smif_mem_cmd_t* cmdProgram);
static void SfdpSetProgramCommandFourBytes_1_1_1(cy_stc_smif_mem_cmd_t* cmdProgram);
static void SfdpSetProgramCommandFourBytes_1_1_4(cy_stc_smif_mem_cmd_t* cmdProgram);
static void SfdpSetProgramCommandFourBytes_1_4_4(cy_stc_smif_mem_cmd_t* cmdProgram);
static void SfdpGetProgramFourBytesCmd(uint8_t const sfdpBuffer[],
                                       cy_en_smif_protocol_mode_t protocolMode,
                                       cy_stc_smif_mem_cmd_t* cmdProgram);
static void SfdpSetChipEraseCommand(cy_stc_smif_mem_cmd_t* cmdChipErase);
static uint32_t SfdpGetSectorEraseCommand(cy_stc_smif_mem_device_cfg_t *device,
                                          uint8_t const sfdpBuffer[],
                                          cy_stc_smif_erase_type_t eraseTypeStc[]);
static cy_en_smif_status_t SfdpEnterFourByteAddressing(SMIF_Type *base, uint8_t entryMethodByte,
                                                              cy_stc_smif_mem_device_cfg_t *device,
                                                              cy_en_smif_slave_select_t slaveSelect,
                                                              cy_stc_smif_context_t const *context);
static void SfdpGetEraseSizeAndCmd(uint8_t const sfdpBuffer[], cy_stc_smif_erase_type_t eraseType[]);
static cy_en_smif_status_t SfdpPopulateRegionInfo(SMIF_Type *base, uint8_t const sectorMapBuff[],
                                   uint32_t const buffLength, cy_stc_smif_mem_device_cfg_t *device,
                                    cy_en_smif_slave_select_t slaveSelect, const cy_stc_smif_context_t *context,
                                    cy_stc_smif_erase_type_t eraseType[]);
static void SfdpSetWipStatusRegisterCommand(cy_stc_smif_mem_cmd_t* readStsRegWipCmd);
#if (CY_IP_MXSMIF_VERSION>=2)
static cy_en_smif_status_t Cy_SMIF_MemCmdWriteRegister(SMIF_Type *base,
                                    cy_en_smif_slave_select_t slaveSelect,
                                    cy_stc_smif_mem_cmd_t *writeEnCmd,
                                    cy_stc_smif_mem_cmd_t *writeCmd,
                                    uint8_t const cmdParam[],
                                    uint32_t paramSize,
                                    cy_stc_smif_context_t const *context);
#endif
#if (CY_IP_MXSMIF_VERSION>=2)
/*******************************************************************************
* Function Name: Cy_SMIF_MemCmdWriteRegister
****************************************************************************//**
*
* This function writes the configuration register. This is a blocking function, it will
* block the execution flow until the command transmission is completed.
*
* \note This function uses the low-level Cy_SMIF_TransmitCommand() API.
* The Cy_SMIF_TransmitCommand() API works in a blocking mode. In the dual quad mode,
* this API is called for each memory.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slaveSelect
* The device to which the command is sent.
*
* \param writeEnCmd
* Write Enable command for issuing before actual write to configuration register.
*
* \param writeCmd
* The command to write into the configuration register.
*
* \param cmdParam
* command parameters include configuration register address and value to be written.
*
* \param paramSize
* command parameter size.
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
*
*******************************************************************************/
static cy_en_smif_status_t Cy_SMIF_MemCmdWriteRegister(SMIF_Type *base,
                                    cy_en_smif_slave_select_t slaveSelect,
                                    cy_stc_smif_mem_cmd_t *writeEnCmd,
                                    cy_stc_smif_mem_cmd_t *writeCmd,
                                    uint8_t const cmdParam[],
                                    uint32_t paramSize,
                                    cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result = CY_SMIF_CMD_NOT_FOUND;

    /* The Write Enable */
    result = Cy_SMIF_TransmitCommand( base, (uint8_t) writeEnCmd->command,
                                        writeEnCmd->cmdWidth,
                                        NULL,
                                        CY_SMIF_CMD_WITHOUT_PARAM,
                                        CY_SMIF_WIDTH_NA,
                                        slaveSelect,
                                        CY_SMIF_TX_LAST_BYTE,
                                        context);

    /* The Write value */
    if (CY_SMIF_SUCCESS == result)
    {
        result = Cy_SMIF_TransmitCommand( base, (uint8_t) writeCmd->command, writeCmd->cmdWidth,
                    cmdParam, paramSize, writeCmd->addrWidth,
                    slaveSelect, CY_SMIF_TX_LAST_BYTE, context);
    }
    return(result);
}
#endif
/*******************************************************************************
* Function Name: SfdpReadBuffer
****************************************************************************//**
*
* This function reads the tables in the SDFP database into the buffer.
*
* \note This function is a blocking function and blocks until the structure data
* is read and returned. This function uses \ref Cy_SMIF_TransmitCommand()
*
* \param *base
* Holds the base address of the SMIF block registers.
*
* \param *cmdSfdp
*  The command structure to store the Read/Write command
*  configuration.
*
* \param sfdpAddress
* The pointer to an array with the address bytes
* associated with the memory command.
*
* \param slaveSelect
* Denotes the number of the slave device to which the transfer is made.
* (0, 1, 2 or 4 - the bit defines which slave to enable). The two-bit enable
* is possible only for the double quad SPI mode.
*
* \param size
* The size of data to be received. Must be > 0 and not greater than 65536.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
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
*       - \ref CY_SMIF_NO_SFDP_SUPPORT
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*
*******************************************************************************/
static cy_en_smif_status_t SfdpReadBuffer(SMIF_Type *base,
                                         cy_stc_smif_mem_cmd_t const *cmdSfdp,
                                         uint8_t const sfdpAddress[],
                                         cy_en_smif_slave_select_t  slaveSelect,
                                         uint32_t size,
                                         uint8_t sfdpBuffer[],
                                         cy_stc_smif_context_t *context)
{
    cy_en_smif_status_t result = CY_SMIF_NO_SFDP_SUPPORT;

#if (CY_IP_MXSMIF_VERSION ==  1U)
    result = Cy_SMIF_TransmitCommand( base, (uint8_t)cmdSfdp->command,
                cmdSfdp->cmdWidth, sfdpAddress, CY_SMIF_SFDP_ADDRESS_LENGTH,
                cmdSfdp->addrWidth, slaveSelect, CY_SMIF_TX_NOT_LAST_BYTE,
                context);

    if(CY_SMIF_SUCCESS == result)
    {
        result = Cy_SMIF_SendDummyCycles(base, cmdSfdp->dummyCycles);

        if(CY_SMIF_SUCCESS == result)
        {
            result = Cy_SMIF_ReceiveDataBlocking(base,
                                                sfdpBuffer,
                                                size,
                                                cmdSfdp->dataWidth,
                                                context);
        }
    }
#else
    bool is2byte_command = ((cmdSfdp->cmdWidth == CY_SMIF_WIDTH_OCTAL) && (cmdSfdp->cmdRate ==  CY_SMIF_DDR));
    uint8_t sfdpAddr_4byte[4];

    sfdpAddr_4byte[0] = 0U;

    for (int i = 0; i<3; i++)
    {
        sfdpAddr_4byte[i+1] = sfdpAddress[i];
    }

    result = Cy_SMIF_TransmitCommand_Ext(base,
                                         (uint16_t)(cmdSfdp->command | (uint16_t)(cmdSfdp->commandH << 8U)),
                                         is2byte_command, cmdSfdp->cmdWidth, cmdSfdp->cmdRate,
                                         is2byte_command? sfdpAddr_4byte : sfdpAddress,
                                         is2byte_command? CY_SMIF_SFDP_ADDRESS_LENGTH + 1U: CY_SMIF_SFDP_ADDRESS_LENGTH,
                                         cmdSfdp->addrWidth, cmdSfdp->addrRate, slaveSelect,
                                         CY_SMIF_TX_NOT_LAST_BYTE, context);

    if(CY_SMIF_SUCCESS == result)
    {
        result = Cy_SMIF_SendDummyCycles_Ext(base, cmdSfdp->addrWidth, cmdSfdp->addrRate, cmdSfdp->dummyCycles);

        if(CY_SMIF_SUCCESS == result)
        {
            result = Cy_SMIF_ReceiveDataBlocking_Ext(base, sfdpBuffer, size,
                                                cmdSfdp->dataWidth, cmdSfdp->dataRate,
                                                context);
        }
    }

#endif
    return(result);
}


/*******************************************************************************
* Function Name: SfdpFindParameterHeader
****************************************************************************//**
*
* Finds the Parameter Header offset from the JEDEC basic flash parameter table.
*
* \param id
* The parameter ID.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \return The relative parameter header offset in bytes.
*  Returns 0 when the parameter header is not found.
*
*******************************************************************************/
static uint32_t SfdpFindParameterHeader(uint32_t id, uint8_t const sfdpBuffer[])
{
    uint32_t headerOffset = PARAMETER_IS_NOT_FOUND;
    uint32_t maxMinorRevison = 0UL;
    uint32_t sfdpAddress = FIRST_HEADER_OFFSET; /* Begin from 1st Parameter Header */

    while (sfdpAddress <= (((uint32_t)sfdpBuffer[PARAM_HEADERS_NUM] *
                                        HEADER_LENGTH) +
                                        FIRST_HEADER_OFFSET))
    {
        /* Check parameter ID */
        if (((id & PARAM_ID_LSB_MASK) == sfdpBuffer[sfdpAddress]) &&  /* Parameter ID LSB */
            (((id >> PARAM_ID_MSB_OFFSET) & PARAM_ID_LSB_MASK) ==
                    sfdpBuffer[sfdpAddress +  /* Parameter ID MSB */
                    PARAM_ID_MSB_REL_OFFSET]))
        {
            /* Check parameter major and minor revisions */
            if ((sfdpBuffer[sfdpAddress + PARAM_MINOR_REV_REL_OFFSET] >= maxMinorRevison) &&
                (sfdpBuffer[sfdpAddress + PARAM_MAJOR_REV_REL_OFFSET] == CY_SMIF_SFDP_MAJOR_REV_1))
            {
                /* Get the maximum minor revision */
                maxMinorRevison = sfdpBuffer[sfdpAddress + PARAM_MINOR_REV_REL_OFFSET];

                /* Save the the Parameter Header offset with the maximum minor revision */
                headerOffset = sfdpAddress;
            }
        }

        sfdpAddress += HEADER_LENGTH;
    }

    return(headerOffset);
}


/*******************************************************************************
* Function Name: SfdpFindParameterTableAddress
****************************************************************************//**
*
* Reads the address and length of the Parameter Table from
* the JEDEC basic flash parameter table. If not found, tableLength set to 0.
*
* \param id
* The parameter ID.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param address
* The Parameter Table address.
*
* \param *tableLength
* The Parameter Table length.
*
*******************************************************************************/
static void SfdpFindParameterTableAddress(uint32_t id,
                                                    uint8_t const sfdpBuffer[],
                                                    uint8_t address[],
                                                    uint8_t *tableLength)
{
    uint32_t headerOffset;

    headerOffset = SfdpFindParameterHeader(id, sfdpBuffer);

    if (PARAMETER_IS_NOT_FOUND != headerOffset)
    {
        /* The Parameter Table address */
        address[2] = sfdpBuffer[headerOffset +
                                PARAM_TABLE_PRT_OFFSET];
        address[1] = sfdpBuffer[headerOffset +
                                PARAM_TABLE_PRT_OFFSET + 1UL];
        address[0] = sfdpBuffer[headerOffset +
                                PARAM_TABLE_PRT_OFFSET + 2UL];

        /* The Parameter Table length */
        *tableLength = (uint8_t)sfdpBuffer[headerOffset + PARAM_TABLE_LENGTH_OFFSET] *
                       BYTES_IN_DWORD;
    }
    else
    {
        *tableLength = 0U;
    }
}


/*******************************************************************************
* Function Name: SfdpGetNumOfAddrBytes
****************************************************************************//**
*
* Reads the number of address bytes from the JEDEC basic flash parameter table.
*
* \note 4-byte addressing mode is set when the memory device supports
*       3- or 4-byte addressing mode and memory density is greater than 16 MB.
*       Otherwise, use 3-byte addresing mode.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param memorySize
* size of the memory device in bytes.
*
* \return The number of address bytes used by the memory slave device.
*
*******************************************************************************/
static uint32_t SfdpGetNumOfAddrBytes(uint8_t const sfdpBuffer[], uint32_t memorySize)
{
    uint32_t addrBytesNum = 0UL;
    uint32_t sfdpAddrCode = _FLD2VAL(CY_SMIF_SFDP_ADDRESS_BYTES,
                                        (uint32_t)sfdpBuffer
                                        [CY_SMIF_SFDP_BFPT_BYTE_02]);
    switch(sfdpAddrCode)
    {
        case CY_SMIF_SFDP_THREE_BYTES_ADDR_CODE:
            addrBytesNum = CY_SMIF_THREE_BYTES_ADDR;
            break;
        case CY_SMIF_SFDP_THREE_OR_FOUR_BYTES_ADDR_CODE:
            if (memorySize > MEMORY_SIZE_16MB)
            {
                addrBytesNum = CY_SMIF_FOUR_BYTES_ADDR;
            }
            else
            {
                addrBytesNum = CY_SMIF_THREE_BYTES_ADDR;
            }
            break;
        case CY_SMIF_SFDP_FOUR_BYTES_ADDR_CODE:
            addrBytesNum = CY_SMIF_FOUR_BYTES_ADDR;
            break;
        default:
            /* Invalid Address code */
            break;
    }

    return(addrBytesNum);
}


/*******************************************************************************
* Function Name: SfdpGetMemoryDensity
****************************************************************************//**
*
* Reads the Memory Density from the JEDEC basic flash parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \return The external memory size:
* For densities of 2 gigabits or less - the size in bytes;
* For densities 4 gigabits and above - bit-31 is set to 1b to define that
* this memory is 4 gigabits and above; and other 30:0 bits define N where
* the density is computed as 2^N bytes.
* For example, 0x80000021 corresponds to 2^30 = 1 gigabyte.
*
*******************************************************************************/
static uint32_t SfdpGetMemoryDensity(uint8_t const sfdpBuffer[])
{
    uint32_t memorySize;
    uint32_t locSize = Cy_SMIF_PackBytesArray(&sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_04], true);

    if (0UL == (locSize & CY_SMIF_SFDP_SIZE_ABOVE_4GB_Msk))
    {
        memorySize = (locSize + 1UL)/BITS_IN_BYTE;
    }
    else
    {
        memorySize = (locSize - BITS_IN_BYTE_ABOVE_4GB) |
                CY_SMIF_SFDP_SIZE_ABOVE_4GB_Msk;
    }

    return(memorySize);
}

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: SfdpGetReadCmd_1_8_8
****************************************************************************//**
*
* Reads the FAST_READ_1_8_8 read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadCmd_1_8_8(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    /* 8-bit command. 8 x I/O Read command */
    cmdRead->command = sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_41];

    /* command presence - 1 byte transfer */
    cmdRead->cmdPresence = CY_SMIF_PRESENT_1BYTE;

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_OCTAL;

    /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    if (0U == (_FLD2VAL(CY_SMIF_SFDP_1_8_8_MODE_CYCLES,
               (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_40])))
    {
        cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    }
    else
    {
        cmdRead->mode = READ_ENHANCED_MODE_DISABLED;
        cmdRead->modeWidth = CY_SMIF_WIDTH_OCTAL;
        cmdRead->modePresence = CY_SMIF_PRESENT_1BYTE;
    }

    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdRead->dummyCycles = _FLD2VAL(CY_SMIF_SFDP_1_8_8_DUMMY_CYCLES,
                           (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_40]);

    /* dummy cycles present - 1 byte transfer */
    if(cmdRead->dummyCycles > 0U)
    {
            cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_1BYTE;
    }

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_OCTAL;
}

/*******************************************************************************
* Function Name: SfdpGetReadCmd_1_1_8
****************************************************************************//**
*
* Reads the FAST_READ_1_1_8 read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadCmd_1_1_8(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    /* 8-bit command. 8 x I/O Read command */
    cmdRead->command = sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_43];

    /* command presence - 1 byte transfer */
    cmdRead->cmdPresence = CY_SMIF_PRESENT_1BYTE;

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_OCTAL;

    /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    if (0U == (_FLD2VAL(CY_SMIF_SFDP_1_1_8_MODE_CYCLES,
               (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_42])))
    {
        cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    }
    else
    {
        cmdRead->mode = READ_ENHANCED_MODE_DISABLED;
        cmdRead->modeWidth = CY_SMIF_WIDTH_OCTAL;
        cmdRead->modePresence = CY_SMIF_PRESENT_1BYTE;
    }

    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdRead->dummyCycles = _FLD2VAL(CY_SMIF_SFDP_1_1_8_DUMMY_CYCLES,
                           (uint32_t)sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_42]);

    /* dummy cycles present - 1 byte transfer */
    if(cmdRead->dummyCycles > 0U)
    {
        cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_1BYTE;
    }

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_OCTAL;
}

/*******************************************************************************
* Function Name: SfdpGetReadCmd_1S_4D_4D
****************************************************************************//**
*
* Reads the FAST_READ_1S_4D_4D read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
static void SfdpGetReadCmd_1S_4D_4D(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    /* 8-bit command. 4 x I/O Read command */
    cmdRead->command = CY_SMIF_FAST_READ_4_BYTES_CMD_1S_4D_4D;

    /* command transfer rate */
    cmdRead->cmdRate = CY_SMIF_SDR;

    /* command presence - 1 byte transfer */
    cmdRead->cmdPresence = CY_SMIF_PRESENT_1BYTE;

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_QUAD;
    cmdRead->addrRate = CY_SMIF_DDR;

    /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    if (0U == (_FLD2VAL(CY_SMIF_SFDP_1_4_4_MODE_CYCLES,
               (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_08])))
    {
        cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    }
    else
    {
        cmdRead->mode = READ_ENHANCED_MODE_DISABLED;
        cmdRead->modeWidth = CY_SMIF_WIDTH_QUAD;
        cmdRead->modeRate = CY_SMIF_DDR;
        cmdRead->modePresence = CY_SMIF_PRESENT_1BYTE;
    }

    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdRead->dummyCycles = _FLD2VAL(CY_SMIF_SFDP_1_4_4_DUMMY_CYCLES,
                           (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_08]);

    /* dummy cycles present - 1 byte transfer */
    cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_1BYTE;

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_QUAD;

    /* The data rate - DDR */
    cmdRead->dataRate = CY_SMIF_DDR;


}
#endif /* CY_IP_MXSMIF_VERSION */

/*******************************************************************************
* Function Name: SfdpGetReadCmd_1_4_4
****************************************************************************//**
*
* Reads the FAST_READ_1_4_4 read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadCmd_1_4_4(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    /* 8-bit command. 4 x I/O Read command */
    cmdRead->command = sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_09];

#if (CY_IP_MXSMIF_VERSION>=2)
    /* command presence - 1 byte transfer */
    cmdRead->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_QUAD;

    /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    if (0U == (_FLD2VAL(CY_SMIF_SFDP_1_4_4_MODE_CYCLES,
               (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_08])))
    {
        cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    }
    else
    {
        cmdRead->mode = READ_ENHANCED_MODE_DISABLED;
        cmdRead->modeWidth = CY_SMIF_WIDTH_QUAD;
#if (CY_IP_MXSMIF_VERSION>=2)
        cmdRead->modePresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    }

    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdRead->dummyCycles = _FLD2VAL(CY_SMIF_SFDP_1_4_4_DUMMY_CYCLES,
                           (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_08]);

#if (CY_IP_MXSMIF_VERSION>=2)
    /* dummy cycles present - 1 byte transfer */
    if(cmdRead->dummyCycles > 0UL)
    {
            cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_1BYTE;
    }
#endif /* CY_IP_MXSMIF_VERSION */

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_QUAD;
}


/*******************************************************************************
* Function Name: SfdpGetReadCmd_1_1_4
****************************************************************************//**
*
* Reads the FAST_READ_1_1_4 read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadCmd_1_1_4(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    /* 8-bit command. 4 x I/O Read command */
    cmdRead->command = sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_0B];

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_SINGLE;

    /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    if ((0U == _FLD2VAL(CY_SMIF_SFDP_1_1_4_MODE_CYCLES, (uint32_t) sfdpBuffer
                    [CY_SMIF_SFDP_BFPT_BYTE_0A])))
    {
        cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    }
    else
    {
        cmdRead->mode = READ_ENHANCED_MODE_DISABLED;
        cmdRead->modeWidth = CY_SMIF_WIDTH_SINGLE;
#if (CY_IP_MXSMIF_VERSION>=2)
        cmdRead->modePresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    }

    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdRead->dummyCycles = _FLD2VAL(CY_SMIF_SFDP_1_1_4_DUMMY_CYCLES,
                          (uint32_t)sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_0A]);

#if (CY_IP_MXSMIF_VERSION>=2)
    /* dummy cycles present - 1 byte transfer */
    if(cmdRead->dummyCycles > 0UL)
    {
            cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_1BYTE;
    }
#endif /* CY_IP_MXSMIF_VERSION */

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_QUAD;
}


/*******************************************************************************
* Function Name: SfdpGetReadCmd_1_2_2
****************************************************************************//**
*
* Reads the FAST_READ_1_2_2 read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadCmd_1_2_2(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    /* 8-bit command. 2 x I/O Read command */
    cmdRead->command  = sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_0F];

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_DUAL;

    /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    if (0U == _FLD2VAL(CY_SMIF_SFDP_1_2_2_MODE_CYCLES, (uint32_t)
              sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_0E]))
    {
        cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    }
    else
    {
        cmdRead->mode = READ_ENHANCED_MODE_DISABLED;
        cmdRead->modeWidth = CY_SMIF_WIDTH_DUAL;
#if (CY_IP_MXSMIF_VERSION>=2)
        cmdRead->modePresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    }

    /* The dummy cycles number. A zero value suggests no dummy cycles. */
    cmdRead->dummyCycles = _FLD2VAL(CY_SMIF_SFDP_1_2_2_DUMMY_CYCLES,
                            (uint32_t) sfdpBuffer [CY_SMIF_SFDP_BFPT_BYTE_0E]);

#if (CY_IP_MXSMIF_VERSION>=2)
    /* dummy cycles present - 1 byte transfer */
    if(cmdRead->dummyCycles > 0UL)
    {
            cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_1BYTE;
    }
#endif /* CY_IP_MXSMIF_VERSION */

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_DUAL;
}


/*******************************************************************************
* Function Name: SfdpGetReadCmd_1_1_2
****************************************************************************//**
*
* Reads the FAST_READ_1_1_2 read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadCmd_1_1_2(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    /* 8-bit command. 2 x I/O Read command */
    cmdRead->command  = sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_0D];

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_SINGLE;

    /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    if (0U == (_FLD2VAL(CY_SMIF_SFDP_1_1_2_MODE_CYCLES, (uint32_t)
        sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_0C])))
    {
        cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    }
    else
    {
        cmdRead->mode = READ_ENHANCED_MODE_DISABLED;
        cmdRead->modeWidth = CY_SMIF_WIDTH_SINGLE;
#if (CY_IP_MXSMIF_VERSION>=2)
        cmdRead->modePresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    }

    /* The dummy cycles number. A zero value suggests no dummy cycles. */
    cmdRead->dummyCycles = _FLD2VAL(CY_SMIF_SFDP_1_1_2_DUMMY_CYCLES,
            (uint32_t)sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_0C]);

#if (CY_IP_MXSMIF_VERSION>=2)
    /* dummy cycles present - 1 byte transfer */
    if(cmdRead->dummyCycles > 0UL)
    {
        cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_1BYTE;
    }
#endif /* CY_IP_MXSMIF_VERSION */

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_DUAL;
}


/*******************************************************************************
* Function Name: SfdpGetReadCmd_1_1_1
****************************************************************************//**
*
* Reads the FAST_READ_1_1_1 read command parameters from the JEDEC basic flash
* parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadCmd_1_1_1(uint8_t const sfdpBuffer[],
                             cy_stc_smif_mem_cmd_t* cmdRead)
{
    (void)sfdpBuffer; /* Suppress warning */

    /* 8-bit command. 1 x I/O Read command */
    cmdRead->command  = CY_SMIF_SINGLE_READ_CMD;

    /* The command transfer width */
    cmdRead->cmdWidth = CY_SMIF_WIDTH_SINGLE;
#if (CY_IP_MXSMIF_VERSION>=2)
            /* command presence - 1 byte transfer */
            cmdRead->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */

    /* The address transfer width */
    cmdRead->addrWidth = CY_SMIF_WIDTH_SINGLE;

    /* The 8 bit-mode byte. This value is 0xFFFFFFFF when there is no mode present */
    cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;

    /* The dummy cycles number. A zero value suggests no dummy cycles. */
    cmdRead->dummyCycles = 0UL;

    /* The data transfer width */
    cmdRead->dataWidth = CY_SMIF_WIDTH_SINGLE;
}


/*******************************************************************************
* Function Name:  zz
****************************************************************************//**
*
* Reads the read command parameters from the JEDEC basic flash parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param dataSelect
* The data line selection options for a slave device.
*
* \param maxDataWidth
* Maximum data width available on the physical interface.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
* \return Protocol Mode.
*
*******************************************************************************/
static cy_en_smif_protocol_mode_t SfdpGetReadCmdParams(uint8_t const sfdpBuffer[],
                                     cy_en_smif_data_select_t dataSelect,
                                     cy_en_smif_txfr_width_t maxDataWidth,
                                     cy_stc_smif_mem_cmd_t* cmdRead)
{
    cy_en_smif_protocol_mode_t protocolMode = PROTOCOL_MODE_WRONG;
    uint32_t sfdpDataIndex = CY_SMIF_SFDP_BFPT_BYTE_02;
    bool quadEnabled = ((CY_SMIF_DATA_SEL1 != dataSelect) &&
                        (CY_SMIF_DATA_SEL3 != dataSelect) &&
                        (maxDataWidth >= CY_SMIF_WIDTH_QUAD));

    if (quadEnabled)
    {
        if (_FLD2BOOL(CY_SMIF_SFDP_FAST_READ_1_4_4,
                      ((uint32_t) sfdpBuffer[sfdpDataIndex])))
        {
#if (CY_IP_MXSMIF_VERSION>=2)
            if(_FLD2BOOL(CY_SMIF_SFDP_DTR_SUPPORT, (uint32_t) sfdpBuffer[sfdpDataIndex]))
            {
                SfdpGetReadCmd_1S_4D_4D(sfdpBuffer, cmdRead);
                protocolMode = PROTOCOL_MODE_1S_4D_4D;
            }
            else
            {
                SfdpGetReadCmd_1_4_4(sfdpBuffer, cmdRead);
                protocolMode = PROTOCOL_MODE_1S_4S_4S;
            }
#else
            SfdpGetReadCmd_1_4_4(sfdpBuffer, cmdRead);
            protocolMode = PROTOCOL_MODE_1S_4S_4S;
#endif /* CY_IP_MXSMIF_VERSION */
        }
        else if (_FLD2BOOL(CY_SMIF_SFDP_FAST_READ_1_1_4,
                            ((uint32_t)sfdpBuffer[sfdpDataIndex])))
        {
            SfdpGetReadCmd_1_1_4(sfdpBuffer, cmdRead);
            protocolMode = PROTOCOL_MODE_1S_1S_4S;
        }
        else
        {
            /* Wrong mode */
            CY_ASSERT_L2(true);
            protocolMode = PROTOCOL_MODE_WRONG;
        }
    }
    else
    {
        if ((_FLD2BOOL(CY_SMIF_SFDP_FAST_READ_1_2_2,
                       (uint32_t)sfdpBuffer[sfdpDataIndex])) &&
            (maxDataWidth >= CY_SMIF_WIDTH_DUAL))
        {
            SfdpGetReadCmd_1_2_2(sfdpBuffer, cmdRead);
            protocolMode = PROTOCOL_MODE_1S_2S_2S;
        }
        else
        {
            if (_FLD2BOOL(CY_SMIF_SFDP_FAST_READ_1_1_2,
                          (uint32_t)sfdpBuffer[sfdpDataIndex]) &&
               (maxDataWidth >= CY_SMIF_WIDTH_DUAL))
            {
                SfdpGetReadCmd_1_1_2(sfdpBuffer, cmdRead);
                protocolMode = PROTOCOL_MODE_1S_1S_2S;
            }
            else
            {
                SfdpGetReadCmd_1_1_1(sfdpBuffer, cmdRead);
                protocolMode = PROTOCOL_MODE_1S_1S_1S;
            }
        }
    }

    return protocolMode;
}
#if (CY_IP_MXSMIF_VERSION>=2)
static void SfdpSetVariableLatencyCmd(SMIF_Type *base,
                                    cy_stc_smif_mem_device_cfg_t *device,
                                    cy_en_smif_slave_select_t slaveSelect,
                                    uint8_t *sccrMapAddr,
                                    cy_stc_smif_context_t *context)
{
    cy_en_smif_status_t result = CY_SMIF_CMD_NOT_FOUND;
    cy_stc_smif_mem_cmd_t *cmdReadLatency = device->readLatencyCmd;
    cy_stc_smif_mem_cmd_t *cmdWriteLatency = device->writeLatencyCmd;
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.8', 1, 'uint8_t to uin32_t type conversion intentional.');
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.6', 4, 'composite expression to uint32_t conversion intentional.');

    if ((sccrMapAddr != NULL) && (cmdReadLatency != NULL) && (cmdWriteLatency != NULL))
    {
        /* SCCR Map 9th DWORD Variable Dummy Cycle Settings */

        uint8_t sccrMapDWord9Value[4];
        uint8_t sccrMapDW9_Address[4];

        /* Initialize DWords */
        for (uint32_t i = 0U; i < 4U; i++)
        {
            sccrMapDWord9Value[i] = 0U;
            sccrMapDW9_Address[i] = 0U;
        }

        ValueToByteArray(ByteArrayToValue(sccrMapAddr, CY_SMIF_SFDP_ADDRESS_LENGTH) + 32U, sccrMapDW9_Address, 0U, CY_SMIF_SFDP_ADDRESS_LENGTH);

        /* Get the JEDEC SCCR Map Table content into sfdpBuffer[] */
        result = SfdpReadBuffer(base, device->readSfdpCmd, sccrMapDW9_Address, slaveSelect,
                            4U, sccrMapDWord9Value, context);

        /* Check if variable latency is supported */
        if ((result == CY_SMIF_SUCCESS) && ((sccrMapDWord9Value[3] & 0x80U) == 0x80U))
        {
            uint32_t latencyMaskoffset = (uint32_t) (sccrMapDWord9Value[3] & 0x7U);
            uint8_t latencyBits = (uint8_t) (((sccrMapDWord9Value[3] >> 5U) & 0x3U));

            cmdReadLatency->command = sccrMapDWord9Value[1];
            cmdWriteLatency->command = sccrMapDWord9Value[0];

            if ((sccrMapDWord9Value[3] & 0x8U) == 0x0U)
            {
                device->latencyCyclesRegAddr = sccrMapDWord9Value[2];
            }
            else
            {
                device->latencyCyclesRegAddr = CY_SMIF_NO_COMMAND_OR_MODE;
            }

            device->latencyCyclesMask = (~(0xFFU << (latencyBits + 2U))) << latencyMaskoffset;

        }
        else
        {
            /* Variable Latency not supported */
            cmdReadLatency->command = CY_SMIF_NO_COMMAND_OR_MODE;
            cmdWriteLatency->command = CY_SMIF_NO_COMMAND_OR_MODE;
        }
    }
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.6');
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.8');
}
#endif
/*******************************************************************************
* Function Name: SfdpGetReadFourBytesCmd
****************************************************************************//**
*
* Reads the read command instruction from the 4-byte Address Instruction Table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer with the 4-byte Address
* Instruction Table.
*
* \param protocolMode
* Protocol Mode.
*
* \param cmdRead
* The pointer to the read command parameters structure.
*
*******************************************************************************/
static void SfdpGetReadFourBytesCmd(uint8_t const sfdpBuffer[],
                                      cy_en_smif_protocol_mode_t protocolMode,
                                      cy_stc_smif_mem_cmd_t* cmdRead)
{
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 7, \
'Pointer type conversion is intentional.');
    /* Get the mask which contains the Support for Fast Read Commands
     * from 4-byte Address Instruction Table, DWORD 1
     */
    uint32_t sfdpForBytesTableDword1 = ((uint32_t*)sfdpBuffer)[FOUR_BYTE_ADDRESS_TABLE_BYTE_0];

    switch (protocolMode)
    {
        case PROTOCOL_MODE_1S_4S_4S:
            if (_FLD2BOOL(SUPPORT_FAST_READ_1S_4S_4S_CMD, sfdpForBytesTableDword1))
            {
                cmdRead->command = CY_SMIF_FAST_READ_4_BYTES_CMD_1S_4S_4S;
            }
            break;
        case PROTOCOL_MODE_1S_1S_4S:
            if (_FLD2BOOL(SUPPORT_FAST_READ_1S_1S_4S_CMD, sfdpForBytesTableDword1))
            {
                cmdRead->command = CY_SMIF_FAST_READ_4_BYTES_CMD_1S_1S_4S;
            }
            break;
        case PROTOCOL_MODE_1S_2S_2S:
            if (_FLD2BOOL(SUPPORT_FAST_READ_1S_2S_2S_CMD, sfdpForBytesTableDword1))
            {
                cmdRead->command = CY_SMIF_FAST_READ_4_BYTES_CMD_1S_2S_2S;
            }
            break;
        case PROTOCOL_MODE_1S_1S_2S:
            if (_FLD2BOOL(SUPPORT_FAST_READ_1S_1S_2S_CMD, sfdpForBytesTableDword1))
            {
                cmdRead->command = CY_SMIF_FAST_READ_4_BYTES_CMD_1S_1S_2S;
            }
            break;
        case PROTOCOL_MODE_1S_1S_1S:
            if (_FLD2BOOL(SUPPORT_FAST_READ_1S_1S_1S_CMD, sfdpForBytesTableDword1))
            {
                cmdRead->command = CY_SMIF_FAST_READ_4_BYTES_CMD_1S_1S_1S;
            }
            break;
        default:
            /* There are no instructions for 4-byte mode. Use instruction for 3-byte mode */
            break;
    }
}


/*******************************************************************************
* Function Name: SfdpGetPageSize
****************************************************************************//**
*
* Reads the page size from the JEDEC basic flash parameter table.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \return The page size in bytes.
*
*******************************************************************************/
static uint32_t SfdpGetPageSize(uint8_t const sfdpBuffer[])
{
    uint32_t size;

    /* The page size */
    size = 0x01UL << _FLD2VAL(CY_SMIF_SFDP_PAGE_SIZE,
        (uint32_t) sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_28]);

    return(size);
}


/*******************************************************************************
* Function Name: SfdpGetEraseTime
****************************************************************************//**
*
* Calculates erase time.
*
* \param eraseOffset
* The offset of the Sector Erase command in the SFDP buffer.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param eraseType
* The pointer to an array with the erase time in us for different erase types.
*
* \return Default erase time in us.
*
*******************************************************************************/
static uint32_t SfdpGetEraseTime(uint32_t const eraseOffset, uint8_t const sfdpBuffer[], cy_stc_smif_erase_type_t eraseType[])
{
    /* Get the value of 10th DWORD from the JEDEC basic flash parameter table */
    uint32_t readEraseTime = ((uint32_t*)sfdpBuffer)[CY_SMIF_JEDEC_BFPT_10TH_DWORD];

    uint32_t eraseTimeDefaultIndex = (((eraseOffset - CY_SMIF_SFDP_BFPT_BYTE_1D) + TYPE_STEP) / TYPE_STEP);
    uint32_t eraseMul = _FLD2VAL(CY_SMIF_SFDP_ERASE_MUL_COUNT, readEraseTime);
    uint32_t eraseUnits = 0UL;
    uint32_t eraseCount = 0UL;
    uint32_t eraseMs = 0UL;
    uint32_t eraseTypeTypicalTime;

    for (uint32_t idx = 0UL; idx < ERASE_TYPE_COUNT; idx++){
        eraseTypeTypicalTime = (readEraseTime >> (idx * ERASE_T_LENGTH))>> ERASE_T_COUNT_OFFSET;
        eraseUnits = _FLD2VAL(ERASE_T_UNITS, eraseTypeTypicalTime);
        eraseCount = _FLD2VAL(ERASE_T_COUNT, eraseTypeTypicalTime);

        switch (eraseUnits)
        {
            case CY_SMIF_SFDP_UNIT_0:
                eraseMs = CY_SMIF_SFDP_ERASE_TIME_1MS;
                break;
            case CY_SMIF_SFDP_UNIT_1:
                eraseMs = CY_SMIF_SFDP_ERASE_TIME_16MS;
                break;
            case CY_SMIF_SFDP_UNIT_2:
                eraseMs = CY_SMIF_SFDP_ERASE_TIME_128MS;
                break;
            case CY_SMIF_SFDP_UNIT_3:
                eraseMs = CY_SMIF_SFDP_ERASE_TIME_1S;
                break;
            default:
                /* An unsupported SFDP value */
                break;
        }

        /* Convert typical time to max time */
        eraseType[idx].eraseTime = ((eraseCount + 1UL) * eraseMs) * (2UL * (eraseMul + 1UL));
    }

    return(eraseType[eraseTimeDefaultIndex - 1UL].eraseTime);
}


/*******************************************************************************
* Function Name: SfdpGetChipEraseTime
****************************************************************************//**
*
* Calculates chip erase time.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \return Chip erase time in us.
*
*******************************************************************************/
static uint32_t SfdpGetChipEraseTime(uint8_t const sfdpBuffer[])
{
    /* Get the value of 10th DWORD from the JEDEC basic flash parameter table */
    uint32_t readEraseTime = ((uint32_t*)sfdpBuffer)[CY_SMIF_JEDEC_BFPT_10TH_DWORD];

    /* Get the value of 11th DWORD from the JEDEC basic flash parameter table */
    uint32_t chipEraseProgTime = ((uint32_t*)sfdpBuffer)[CY_SMIF_JEDEC_BFPT_11TH_DWORD];

    uint32_t chipEraseTimeMax;
    uint32_t chipEraseUnits = _FLD2VAL(CY_SMIF_SFDP_CHIP_ERASE_UNITS, chipEraseProgTime);
    uint32_t chipEraseCount = _FLD2VAL(CY_SMIF_SFDP_CHIP_ERASE_COUNT, chipEraseProgTime);
    uint32_t chipEraseMs = 0UL;
    uint32_t eraseMul = _FLD2VAL(CY_SMIF_SFDP_ERASE_MUL_COUNT, readEraseTime);

    switch (chipEraseUnits)
    {
        case CY_SMIF_SFDP_UNIT_0:
            chipEraseMs = CY_SMIF_SFDP_CHIP_ERASE_TIME_16MS;
            break;
        case CY_SMIF_SFDP_UNIT_1:
            chipEraseMs = CY_SMIF_SFDP_CHIP_ERASE_TIME_256MS;
            break;
        case CY_SMIF_SFDP_UNIT_2:
            chipEraseMs = CY_SMIF_SFDP_CHIP_ERASE_TIME_4S;
            break;
        case CY_SMIF_SFDP_UNIT_3:
            chipEraseMs = CY_SMIF_SFDP_CHIP_ERASE_TIME_64S;
            break;
        default:
            /* An unsupported SFDP value */
            break;
    }

    /* Convert typical time to max time */
    chipEraseTimeMax = ((chipEraseCount + 1UL)*chipEraseMs) * (2UL *(eraseMul + 1UL));

    return(chipEraseTimeMax);
}


/*******************************************************************************
* Function Name: SfdpGetPageProgramTime
****************************************************************************//**
*
* Calculates page program time.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \return Page program time in us.
*
*******************************************************************************/
static uint32_t SfdpGetPageProgramTime(uint8_t const sfdpBuffer[])
{
    /* Get the value of 11th DWORD from the JEDEC basic flash parameter table */
    uint32_t chipEraseProgTime = ((uint32_t*)sfdpBuffer)[CY_SMIF_JEDEC_BFPT_11TH_DWORD];
    uint32_t programTimeMax;
    uint32_t programTimeUnits = _FLD2VAL(CY_SMIF_SFDP_PAGE_PROG_UNITS, chipEraseProgTime);
    uint32_t programTimeCount  = _FLD2VAL(CY_SMIF_SFDP_PAGE_PROG_COUNT, chipEraseProgTime);
    uint32_t progMul = _FLD2VAL(CY_SMIF_SFDP_PROG_MUL_COUNT, chipEraseProgTime);
    uint32_t progUs;

    if (CY_SMIF_SFDP_UNIT_0 == programTimeUnits)
    {
        progUs = CY_SMIF_SFDP_PROG_TIME_8US;
    }
    else
    {
        progUs = CY_SMIF_SFDP_PROG_TIME_64US;
    }

    /* Convert typical time to max time */
    programTimeMax = ((programTimeCount + 1UL) * progUs) * (2UL * (progMul + 1UL));

    return(programTimeMax);
}


/*******************************************************************************
* Function Name: SfdpSetWriteEnableCommand
****************************************************************************//**
*
* Sets the Write Enable command and the width of the command transfer.
*
* \param cmdWriteEnable
* The pointer to the Write Enable command parameters structure.
*
*******************************************************************************/
static void SfdpSetWriteEnableCommand(cy_stc_smif_mem_cmd_t* cmdWriteEnable)
{
    /* 8-bit command. Write Enable */
    cmdWriteEnable->command = CY_SMIF_WRITE_ENABLE_CMD;

    /* The width of the command transfer */
    cmdWriteEnable->cmdWidth = CY_SMIF_WIDTH_SINGLE;

#if (CY_IP_MXSMIF_VERSION>=2)
    cmdWriteEnable->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: SfdpSetWriteDisableCommand
****************************************************************************//**
*
* Sets the Write Disable command and the width of the command transfer.
*
* \param cmdWriteDisable
* The pointer to the Write Disable command parameters structure.
*
*******************************************************************************/
static void SfdpSetWriteDisableCommand(cy_stc_smif_mem_cmd_t* cmdWriteDisable)
{
    /* The 8-bit command. Write Disable */
    cmdWriteDisable->command = CY_SMIF_WRITE_DISABLE_CMD;

    /* The width of the command transfer */
    cmdWriteDisable->cmdWidth = CY_SMIF_WIDTH_SINGLE;
}


/*******************************************************************************
* Function Name: SfdpSetProgramCommand_1_1_1
****************************************************************************//**
*
* Sets the Program command parameters for 1S-1S-1S Protocol mode and
* 3-byte addressing mode.
*
* \param cmdProgram
* The pointer to the Program command parameters structure.
*
*******************************************************************************/
static void SfdpSetProgramCommand_1_1_1(cy_stc_smif_mem_cmd_t* cmdProgram)
{
    /* 8-bit command. 1 x I/O Program command */
    cmdProgram->command = CY_SMIF_SINGLE_PROGRAM_CMD;
#if (CY_IP_MXSMIF_VERSION>=2)
    /* command presence - 1 byte */
    cmdProgram->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    /* The command transfer width */
    cmdProgram->cmdWidth = CY_SMIF_WIDTH_SINGLE;
    /* The address transfer width */
    cmdProgram->addrWidth = CY_SMIF_WIDTH_SINGLE;
    /* 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    cmdProgram->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    /* The width of the mode command transfer */
    cmdProgram->modeWidth = CY_SMIF_WIDTH_SINGLE;
    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdProgram->dummyCycles = 0UL;
    /* The data transfer width */
    cmdProgram->dataWidth = CY_SMIF_WIDTH_SINGLE;
}


/*******************************************************************************
* Function Name: SfdpSetProgramCommandFourBytes_1_1_1
****************************************************************************//**
*
* Sets the Program command parameters for 1S-1S-1S Protocol mode and
* 4-byte addressing mode.
*
* \param cmdProgram
* The pointer to the Program command parameters structure.
*
*******************************************************************************/
static void SfdpSetProgramCommandFourBytes_1_1_1(cy_stc_smif_mem_cmd_t* cmdProgram)
{
    /* 8-bit command. 1 x I/O Program command */
    cmdProgram->command = CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_1S_1S;
#if (CY_IP_MXSMIF_VERSION>=2)
    /* command presence - 1 byte */
    cmdProgram->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    /* The command transfer width */
    cmdProgram->cmdWidth = CY_SMIF_WIDTH_SINGLE;
    /* The address transfer width */
    cmdProgram->addrWidth = CY_SMIF_WIDTH_SINGLE;
    /* 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    cmdProgram->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    /* The width of the mode command transfer */
    cmdProgram->modeWidth = CY_SMIF_WIDTH_SINGLE;
    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdProgram->dummyCycles = 0UL;
    /* The data transfer width */
    cmdProgram->dataWidth = CY_SMIF_WIDTH_SINGLE;
}


/*******************************************************************************
* Function Name: SfdpSetProgramCommandFourBytes_1_1_4
****************************************************************************//**
*
* Sets the Program command parameters for 1S-1S-4S Protocol mode and
* 4-byte addressing mode.
*
* \param cmdProgram
* The pointer to the Program command parameters structure.
*
*******************************************************************************/
static void SfdpSetProgramCommandFourBytes_1_1_4(cy_stc_smif_mem_cmd_t* cmdProgram)
{
    /* 8-bit command. 1 x I/O Program command */
    cmdProgram->command = CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_1S_4S;
#if (CY_IP_MXSMIF_VERSION>=2)
    /* command presence - 1 byte */
    cmdProgram->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    /* The command transfer width */
    cmdProgram->cmdWidth = CY_SMIF_WIDTH_SINGLE;
    /* The address transfer width */
    cmdProgram->addrWidth = CY_SMIF_WIDTH_SINGLE;
    /* 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    cmdProgram->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    /* The width of the mode command transfer */
    cmdProgram->modeWidth = CY_SMIF_WIDTH_SINGLE;
    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdProgram->dummyCycles = 0UL;
    /* The data transfer width */
    cmdProgram->dataWidth = CY_SMIF_WIDTH_QUAD;
}


/*******************************************************************************
* Function Name: SfdpSetProgramCommandFourBytes_1_4_4
****************************************************************************//**
*
* Sets the Program command parameters for 1S-4S-4S Protocol mode and
* 4-byte addressing mode.
*
* \param cmdProgram
* The pointer to the Program command parameters structure.
*
*******************************************************************************/
static void SfdpSetProgramCommandFourBytes_1_4_4(cy_stc_smif_mem_cmd_t* cmdProgram)
{
    /* 8-bit command. 1 x I/O Program command */
    cmdProgram->command = CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_4S_4S;
#if (CY_IP_MXSMIF_VERSION>=2)
    cmdProgram->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
    /* The command transfer width */
    cmdProgram->cmdWidth = CY_SMIF_WIDTH_SINGLE;
    /* The address transfer width */
    cmdProgram->addrWidth = CY_SMIF_WIDTH_QUAD;
    /* 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    cmdProgram->mode = CY_SMIF_NO_COMMAND_OR_MODE;
    /* The width of the mode command transfer */
    cmdProgram->modeWidth = CY_SMIF_WIDTH_QUAD;
    /* The dummy cycles number. A zero value suggests no dummy cycles */
    cmdProgram->dummyCycles = 0UL;
    /* The data transfer width */
    cmdProgram->dataWidth = CY_SMIF_WIDTH_QUAD;
}

/*******************************************************************************
* Function Name: SfdpGetProgramFourBytesCmd
****************************************************************************//**
*
* Sets the Page Program command instruction for 4-byte addressing mode.
*
* \note When the Program command is not found for 4 byte addressing mode
* the Program command instruction is set for 1S-1S-1S Protocol mode and
* 3-byte addressing mode.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer with the 4-byte Address
* Instruction table.
*
* \param protocolMode
* Protocol Mode.
*
* \param cmdProgram
* The pointer to the Program command parameters structure.
*
*******************************************************************************/
static void SfdpGetProgramFourBytesCmd(uint8_t const sfdpBuffer[],
                                       cy_en_smif_protocol_mode_t protocolMode,
                                       cy_stc_smif_mem_cmd_t* cmdProgram)
{
    /* Get the mask which contains the Support for Page Program Commands
     * from 4-byte Address Instruction Table, DWORD 1
     */
    uint32_t sfdpForBytesTableDword1 = ((uint32_t*)sfdpBuffer)[FOUR_BYTE_ADDRESS_TABLE_BYTE_0];

    switch (protocolMode)
    {
        case PROTOCOL_MODE_1S_4S_4S:
#if (CY_IP_MXSMIF_VERSION>=2)
        case PROTOCOL_MODE_1S_4D_4D:
#endif /* CY_IP_MXSMIF_VERSION */
            if (_FLD2BOOL(SUPPORT_PP_1S_4S_4S_CMD, sfdpForBytesTableDword1))
            {
                SfdpSetProgramCommandFourBytes_1_4_4(cmdProgram);
            }
            else if (_FLD2BOOL(SUPPORT_PP_1S_1S_4S_CMD, sfdpForBytesTableDword1))
            {
                SfdpSetProgramCommandFourBytes_1_1_4(cmdProgram);
            }
            else if (_FLD2BOOL(SUPPORT_PP_1S_1S_1S_CMD, sfdpForBytesTableDword1))
            {
                SfdpSetProgramCommandFourBytes_1_1_1(cmdProgram);
            }
            else
            {
                /* There are no instructions for 4-byte mode. Use the instruction for 3-byte mode */
                SfdpSetProgramCommand_1_1_1(cmdProgram);
            }
            break;
        case PROTOCOL_MODE_1S_1S_4S:
            if (_FLD2BOOL(SUPPORT_PP_1S_1S_4S_CMD, sfdpForBytesTableDword1))
            {
                SfdpSetProgramCommandFourBytes_1_1_4(cmdProgram);
            }
            else if (_FLD2BOOL(SUPPORT_PP_1S_1S_1S_CMD, sfdpForBytesTableDword1))
            {
                SfdpSetProgramCommandFourBytes_1_1_1(cmdProgram);
            }
            else
            {
                /* There are no instructions for 4-byte mode. Use the instruction for 3-byte mode */
                SfdpSetProgramCommand_1_1_1(cmdProgram);
            }
            break;
        case PROTOCOL_MODE_1S_2S_2S:
        case PROTOCOL_MODE_1S_1S_2S:
        case PROTOCOL_MODE_1S_1S_1S:
            if (_FLD2BOOL(SUPPORT_PP_1S_1S_1S_CMD, sfdpForBytesTableDword1))
            {
                SfdpSetProgramCommandFourBytes_1_1_1(cmdProgram);
            }
            else
            {
                /* There are no instructions for 4-byte mode. Use the instruction for 3-byte mode */
                SfdpSetProgramCommand_1_1_1(cmdProgram);
            }
            break;
        default:
            /* Wrong mode */
            CY_ASSERT_L2(true);
            break;
    }
}


/*******************************************************************************
* Function Name: SfdpSetWipStatusRegisterCommand
****************************************************************************//**
*
* Sets the WIP-containing status register command and
* the width of the command transfer.
*
* \param readStsRegWipCmd
* The pointer to the WIP-containing status register command parameters structure.
*
*******************************************************************************/
static void SfdpSetWipStatusRegisterCommand(cy_stc_smif_mem_cmd_t* readStsRegWipCmd)
{
    /* 8-bit command. WIP RDSR */
    readStsRegWipCmd->command  = CY_SMIF_READ_STATUS_REG1_CMD;
    /* The command transfer width */
    readStsRegWipCmd->cmdWidth = CY_SMIF_WIDTH_SINGLE;
}


/*******************************************************************************
* Function Name: SfdpSetChipEraseCommand
****************************************************************************//**
*
* Sets the Chip Erase command and the width of the command transfer.
*
* \param cmdChipErase
* The pointer to the Chip Erase command parameters structure.
*
*******************************************************************************/
static void SfdpSetChipEraseCommand(cy_stc_smif_mem_cmd_t* cmdChipErase)
{
    /* 8-bit command. Chip Erase */
    cmdChipErase->command  = CY_SMIF_CHIP_ERASE_CMD;
    /* The width of the command transfer */
    cmdChipErase->cmdWidth = CY_SMIF_WIDTH_SINGLE;
}


/*******************************************************************************
* Function Name: SfdpGetSectorEraseCommand
****************************************************************************//**
*
* Sets the Sector Erase command and the width of the command transfer.
*
* \note When the Erase command is not found the width of the command
*  transfer (cmdWidth) is set to CY_SMIF_WIDTH_NA.
*
* \param device
* The device structure instance declared by the user. This is where the detected
* parameters are stored and returned.
*
* \param sfdpBuffer
* The pointer to an array with the SDFP buffer.
*
* \param eraseTypeStc
* The pointer to an array with the erase commands for different erase types.
*
* \return The offset of the Sector Erase command in the SFDP buffer.
*  Returns 0 when the Sector Erase command is not found.
*
*******************************************************************************/
static uint32_t SfdpGetSectorEraseCommand(cy_stc_smif_mem_device_cfg_t *device,
                                          uint8_t const sfdpBuffer[],
                                          cy_stc_smif_erase_type_t eraseTypeStc[])
{
    uint32_t eraseOffset;
    if (FOUR_BYTE_ADDRESS == device->numOfAddrBytes)
    {
        uint32_t eraseType;     /* Erase Type decreased to 1 */
        uint32_t eraseTypeMask;

        eraseOffset = COMMAND_IS_NOT_FOUND;
        device->eraseCmd->command = CY_SMIF_NO_COMMAND_OR_MODE;

        /* Get the mask which contains the Support for Erase Commands (Types 1-4)
         * from 4-byte Address Instruction Table, DWORD 1
         */
        eraseTypeMask = _FLD2VAL(SUPPORT_ERASE_COMMAND, (uint32_t)sfdpBuffer[FOUR_BYTE_ADDRESS_TABLE_BYTE_1]);

        /* Find Erase Type (decreased to 1) */
        for (eraseType = 0UL; eraseType <= ERASE_TYPE_COUNT; eraseType++)
        {
            if ((1UL << eraseType) == (eraseTypeMask & (1UL << eraseType)))
            {
                /* Erase Type found */
                break;
            }
        }

        if (eraseType < ERASE_TYPE_COUNT)
        {
            /* Calculate the offset for the sector Erase command in the 4-byte Address Instruction Table, DWORD 2 */
            eraseOffset = FOUR_BYTE_ADDR_ERASE_TYPE_1 + eraseType;

            /* Update all erase commands for 4-bytes */
            for(uint32_t i = 0UL; i< ERASE_TYPE_COUNT; i++)
            {
                eraseTypeStc[i].eraseCmd = sfdpBuffer[FOUR_BYTE_ADDR_ERASE_TYPE_1 + i];
            }
            /* Get the sector Erase command
             * from the 4-byte Address Instruction Table, DWORD 2
             */
            device->eraseCmd->command = sfdpBuffer[eraseOffset];
#if (CY_IP_MXSMIF_VERSION>=2)
            device->eraseCmd->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */

            /* Recalculate eraseOffset for the 3-byte Address Instruction Table
             * to find the device->eraseSize and device->eraseTime parameters based on Erase Type.
             */
            eraseOffset = CY_SMIF_SFDP_BFPT_BYTE_1D + (eraseType * TYPE_STEP);
        }
    }
    else
    {
        eraseOffset = CY_SMIF_SFDP_BFPT_BYTE_1D;
        while (INSTRUCTION_NOT_SUPPORTED == sfdpBuffer[eraseOffset])
        {
            if (eraseOffset >= CY_SMIF_SFDP_BFPT_BYTE_23)
            {
                /* The Sector Erase command is not found */
                eraseOffset = COMMAND_IS_NOT_FOUND;
                break;
            }
            eraseOffset += TYPE_STEP; /* Check the next Erase Type */
        }

        if (COMMAND_IS_NOT_FOUND != eraseOffset)
        {
            /* Get the sector Erase command from the JEDEC basic flash parameter table */
            device->eraseCmd->command = sfdpBuffer[eraseOffset];
#if (CY_IP_MXSMIF_VERSION>=2)
            device->eraseCmd->cmdPresence = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
        }
    }

    if (COMMAND_IS_NOT_FOUND != eraseOffset)
    {
        /* The command transfer width */
        device->eraseCmd->cmdWidth = CY_SMIF_WIDTH_SINGLE;

        /* The address transfer width */
        device->eraseCmd->addrWidth = CY_SMIF_WIDTH_SINGLE;
    }
    else
    {
        device->eraseCmd->cmdWidth = CY_SMIF_WIDTH_NA;
    }

    return(eraseOffset);
}

/*******************************************************************************
* Function Name: SfdpEnterFourByteAddressing
****************************************************************************//**
*
* This function sets 4-byte address mode for a memory device as defined in
* 16th DWORD of JEDEC Basic Flash Parameter Table.
*
* \note The entry methods which do not support the required
* operation of writing into the register.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param entryMethodByte
* The byte which defines the supported method to enter 4-byte addressing mode.
*
* \param device
* The device structure instance declared by the user. This is where the detected
* parameters are stored and returned.
*
* \param slaveSelect
* The slave select line for the device.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of 4-byte addressing mode command transmit.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_CMD_NOT_FOUND
*******************************************************************************/
static cy_en_smif_status_t SfdpEnterFourByteAddressing(SMIF_Type *base, uint8_t entryMethodByte,
                                                       cy_stc_smif_mem_device_cfg_t *device,
                                                       cy_en_smif_slave_select_t slaveSelect,
                                                       cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result = CY_SMIF_CMD_NOT_FOUND;

    if ((entryMethodByte & CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_SUPPORTED_MASK) != 0U)
    {
        /* Supports one of the 4-byte Entry methods */
        result = CY_SMIF_SUCCESS;

        if ((entryMethodByte & CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_WR_EN_B7) != 0U)
        {
            /* To enter a 4-byte addressing write enable is required */
            cy_stc_smif_mem_cmd_t* writeEn = device->writeEnCmd;

            if(NULL != writeEn)
            {
                result = Cy_SMIF_TransmitCommand(base,
                                                (uint8_t) writeEn->command,
                                                writeEn->cmdWidth,
                                                NULL,
                                                CY_SMIF_CMD_WITHOUT_PARAM,
                                                CY_SMIF_WIDTH_NA,
                                                slaveSelect,
                                                CY_SMIF_TX_LAST_BYTE,
                                                context);
            }
        }

        if ( (((entryMethodByte & CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_B7) != 0U) ||
             ((entryMethodByte & CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_WR_EN_B7) != 0U)) &&
             (result == CY_SMIF_SUCCESS))
        {
            /* To enter a 4-byte addressing B7 instruction is required */
            result = Cy_SMIF_TransmitCommand(base,
                                             CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_B7_CMD,
                                             CY_SMIF_WIDTH_SINGLE,
                                             NULL,
                                             CY_SMIF_CMD_WITHOUT_PARAM,
                                             CY_SMIF_WIDTH_NA,
                                             slaveSelect,
                                             CY_SMIF_TX_LAST_BYTE,
                                             context);
        }
    }
    return result;
}


/*******************************************************************************
* Function Name: SfdpGetEraseSizeAndCmd
****************************************************************************//**
*
* Fills arrays with an erase size and cmd for all erase types.
*
* \param sfdpBuffer
* The pointer to an array with the Basic Flash Parameter table buffer.
*
* \param eraseType
* The pointer to an array with the erase commands and erase size for all erase types.
*
*******************************************************************************/
static void SfdpGetEraseSizeAndCmd(uint8_t const sfdpBuffer[],
                                   cy_stc_smif_erase_type_t eraseType[])
{
    uint32_t idx = 0UL;
    for (uint32_t currET = 0UL; currET < ERASE_TYPE_COUNT; currET++)
    {
        /* The erase size in the SFDP buffer defined as power of two */
        eraseType[currET].eraseSize = 1UL << sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_1C + idx];
        eraseType[currET].eraseCmd = sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_1D + idx];
        idx += TYPE_STEP;
    }
}


/*******************************************************************************
* Function Name: SfdpPopulateRegionInfo
****************************************************************************//**
*
* Reads the current configuration for regions and populates regionInfo
* structures.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param sectorMapBuff
* The pointer to an array with the Sector Map Parameter Table buffer.
*
* \param buffLength
* Length of the Sector Map Parameter Table buffer.

* \param device
* The device structure instance declared by the user. This is where the detected
* parameters are stored and returned.
*
* \param slaveSelect
* The slave select line for the device.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \param eraseType
* The pointer to an array with the erase size, erase command and erase time for all erase types.
*
* \return A status of the Sector Map Parameter Table parsing.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_SFDP_CORRUPTED_TABLE
*       - \ref CY_SMIF_NOT_HYBRID_MEM
*
*******************************************************************************/
static cy_en_smif_status_t SfdpPopulateRegionInfo(SMIF_Type *base,
                                   uint8_t const sectorMapBuff[],
                                   uint32_t const buffLength,
                                   cy_stc_smif_mem_device_cfg_t *device,
                                   cy_en_smif_slave_select_t slaveSelect,
                                   const cy_stc_smif_context_t *context,
                                   cy_stc_smif_erase_type_t eraseType[])
{
    uint8_t currCmd;
    uint8_t dummyCycles;
    uint8_t regMask;
    uint8_t regValue;
    uint8_t currRegisterAddr[ERASE_TYPE_COUNT];
    uint8_t regionInfoIdx = 0U;
    uint32_t currTableIdx = 0UL;
    uint32_t addrBytesNum = 0UL;
    uint32_t addrCode = 0UL;
    cy_en_smif_status_t result = CY_SMIF_NOT_HYBRID_MEM;

    /* Initialize register address */
    for (uint32_t i = 0U; i < ERASE_TYPE_COUNT; i++)
    {
        currRegisterAddr[i] = 0U;
    }

    /* Loop across all command descriptors to find current configuration */
    while(SECTOR_MAP_COMAND_DESCRIPTOR_TYPE == (sectorMapBuff[currTableIdx] & SECTOR_MAP_DESCRIPTOR_MASK))
    {
        currCmd = sectorMapBuff[currTableIdx + CY_SMIF_SFDP_SECTOR_MAP_CMD_OFFSET];
        regMask = sectorMapBuff[currTableIdx + CY_SMIF_SFDP_SECTOR_MAP_REG_MSK_OFFSET];
        regValue = 0U;

        /* Get the address length for configuration detection */
        addrCode = _FLD2VAL(CY_SMIF_SFDP_SECTOR_MAP_ADDR_BYTES, sectorMapBuff[currTableIdx + CY_SMIF_SFDP_SECTOR_MAP_ADDR_LEN_OFFSET]);
        switch(addrCode)
        {
            case CY_SMIF_SFDP_THREE_BYTES_ADDR_CODE:
                /* No address cycle */
                addrBytesNum = 0UL;
                break;
            case CY_SMIF_SFDP_THREE_OR_FOUR_BYTES_ADDR_CODE:
                addrBytesNum = CY_SMIF_THREE_BYTES_ADDR;
                break;
            case CY_SMIF_SFDP_FOUR_BYTES_ADDR_CODE:
                addrBytesNum = CY_SMIF_FOUR_BYTES_ADDR;
                break;
            default:
                /* Use the current settings */
                addrBytesNum = device->numOfAddrBytes;
                break;
        }

        /* Get the control register address */
        for(uint8_t i = 0U; i < addrBytesNum; i++)
        {
            /* Offset for control register in SFDP has little-endian byte order, need to swap it */
            currRegisterAddr[i] = sectorMapBuff[(currTableIdx + CY_SMIF_SFDP_SECTOR_MAP_REG_ADDR_OFFSET + addrBytesNum) - i - 1UL];
        }

        /* Get the number of latency cycles required for configuration detection command */
        dummyCycles = (uint8_t) _FLD2VAL(CY_SMIF_SFDP_SECTOR_MAP_DUMMY_CYCLES, sectorMapBuff[currTableIdx + CY_SMIF_SFDP_SECTOR_MAP_ADDR_LEN_OFFSET]);

        /* If variable latency is detected use 8 cycles as serial flash repeats RX data in case 0 dummy cycles required */
        if (dummyCycles == 0xFU)
        {
            dummyCycles = 8U;
        }

        /* Read the value of the register for the current configuration detection */
        result = ReadAnyReg(base, slaveSelect, &regValue, currCmd, dummyCycles, &currRegisterAddr[0], addrBytesNum, context);

        if (CY_SMIF_SUCCESS == result)
        {
            /* Set the bit of the region idx to 1 if the config matches */
            regionInfoIdx = ((uint8_t)(regionInfoIdx << 1U)) | (((regValue & regMask) == 0U)?(0U):(1U));
        }

        currTableIdx += HEADER_LENGTH;
        if (currTableIdx > buffLength)
        {
            result = CY_SMIF_SFDP_CORRUPTED_TABLE;
            break;
        }
    }

    if (CY_SMIF_SUCCESS == result)
    {
        /* Find the matching configuration map descriptor */
        while(regionInfoIdx != sectorMapBuff[currTableIdx + 1UL])
        {
            /* Increment the table index to the next map */
            currTableIdx += (sectorMapBuff[currTableIdx + CY_SMIF_SFDP_SECTOR_MAP_CONFIG_ID_OFFSET] + 2UL) * BYTES_IN_DWORD;
            if (currTableIdx > buffLength)
            {
                result = CY_SMIF_SFDP_CORRUPTED_TABLE;
                break;
            }
        }
    }

    if (CY_SMIF_SUCCESS == result)
    {
        /* Populate region data from the sector map */
        uint8_t numOfRegions = sectorMapBuff[currTableIdx + CY_SMIF_SFDP_SECTOR_MAP_REGION_COUNT_OFFSET] + 1U;
        device->hybridRegionCount = (uint32_t) numOfRegions;

        if(numOfRegions <= 1U)
        {
            result = CY_SMIF_NOT_HYBRID_MEM;
        }
        else
        {
            uint8_t eraseTypeCode;
            uint32_t currRegionAddr = 0UL;
            uint32_t regionSize = 0UL;
            uint8_t supportedEraseType;
            uint8_t eraseTypeMask;
            cy_stc_smif_hybrid_region_info_t *currRegionPtr;
            for(uint8_t currRegion = 0U; currRegion< numOfRegions; currRegion++)
            {
                currRegionAddr = currRegionAddr + regionSize;
                currTableIdx += BYTES_IN_DWORD;

                supportedEraseType = 0U;
                eraseTypeMask = 1U;
                eraseTypeCode = sectorMapBuff[currTableIdx] & CY_SMIF_SFDP_SECTOR_MAP_SUPPORTED_ET_MASK;
                while(0U == (eraseTypeCode & eraseTypeMask))
                {
                    /* Erase type number defined as a bit position */
                    eraseTypeMask = eraseTypeMask << 1;
                    supportedEraseType++;
                    if(supportedEraseType > ERASE_TYPE_COUNT)
                    {
                        result = CY_SMIF_SFDP_CORRUPTED_TABLE;
                        break;
                    }
                }

                /* The region size as a zero-based count of 256 byte units */
                regionSize = ((*( (uint32_t*) &sectorMapBuff[currTableIdx]) >> BITS_IN_BYTE) + 1UL) * SECTOR_MAP_REGION_SIZE_MULTIPLIER;
                CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
                currRegionPtr = device->hybridRegionInfo[currRegion];

                currRegionPtr->regionAddress = currRegionAddr;
                currRegionPtr->eraseCmd = (uint32_t)eraseType[supportedEraseType].eraseCmd;
                currRegionPtr->eraseTime = eraseType[supportedEraseType].eraseTime;
                if(regionSize < eraseType[supportedEraseType].eraseSize)
                {
                    /* One region with a single sector */
                    currRegionPtr->eraseSize = regionSize;
                    currRegionPtr->sectorsCount = 1UL;
                }
                else
                {
                    currRegionPtr->eraseSize = eraseType[supportedEraseType].eraseSize;
                    currRegionPtr->sectorsCount = regionSize / eraseType[supportedEraseType].eraseSize;
                }
            }
        }
    }
    return result;
}

#if (CY_IP_MXSMIF_VERSION>=2)
static cy_en_smif_protocol_mode_t GetOctalSDRParams(SMIF_Type *base,
                                    uint8_t sfdpBuffer[],
                                    cy_stc_smif_mem_device_cfg_t *device,
                                    cy_en_smif_slave_select_t slaveSelect,
                                    uint32_t sfdpForBytesTableDword1,
                                    uint8_t *sccrMapAddr,
                                    uint8_t  sccrMapTableLength,
                                    cy_stc_smif_context_t *context)
{
    cy_en_smif_protocol_mode_t protocol = PROTOCOL_MODE_WRONG;
    cy_en_smif_status_t result = CY_SMIF_NO_OE_BIT;
    cy_stc_smif_mem_cmd_t *cmdSfdp = device->readSfdpCmd;
    cy_stc_smif_mem_cmd_t *cmdRead = device->readCmd;

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3', 'Pointer type conversion is intentional.');

    if (_FLD2BOOL(SUPPORT_FAST_READ_1S_8S_8S_CMD,
              sfdpForBytesTableDword1))
    {
         SfdpGetReadCmd_1_8_8(sfdpBuffer, cmdRead);
         protocol = PROTOCOL_MODE_1S_8S_8S;
    }
    else if (_FLD2BOOL(SUPPORT_FAST_READ_1S_8S_8S_CMD,
                        sfdpForBytesTableDword1))
    {
        SfdpGetReadCmd_1_1_8(sfdpBuffer, cmdRead);
        protocol = PROTOCOL_MODE_1S_1S_8S;
    }
    else
    {
        /* Do Nothing */
    }

    if (protocol != PROTOCOL_MODE_WRONG)
    {
        /* Get Octal Enable commands and mask */
        uint8_t sccrMapAddrBuffer[CY_SMIF_SFDP_LENGTH];

        /* Get the JEDEC SCCR Map Table content into sfdpBuffer[] */
        result = SfdpReadBuffer(base, cmdSfdp, sccrMapAddr, slaveSelect,
                            sccrMapTableLength, sccrMapAddrBuffer, context);

        if (result == CY_SMIF_SUCCESS)
        {
            /* Get the mask which contains the Support for Fast Read Commands
             * from SCCR Map Table, DWORD 16
             */
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3', 'Pointer type conversion is intentional.');
            uint32_t sccrMapAddrBufferDword16 = (*(uint32_t*)&sccrMapAddrBuffer[CY_SMIF_SFDP_SCCR_MAP_BYTE_3B]);

            /* Read DWORD-16 to fill read and write Octal Enable commands */
            if (_FLD2BOOL(CY_SMIF_SFDP_OCTAL_ENABLE_BIT_SUPPORT, sccrMapAddrBufferDword16))
            {
                    device->stsRegOctalEnableMask = _FLD2VAL(CY_SMIF_SFDP_OCTAL_ENABLE_BIT, sccrMapAddrBufferDword16);
                    device->writeStsRegOeCmd->command  = _FLD2VAL(CY_SMIF_SFDP_OCTAL_ENABLE_WRITE_CMD, sccrMapAddrBufferDword16);
                    device->readStsRegOeCmd->command  = _FLD2VAL(CY_SMIF_SFDP_OCTAL_ENABLE_READ_CMD, sccrMapAddrBufferDword16);

                    if (_FLD2BOOL(CY_SMIF_SFDP_OCTAL_ENABLE_USE_ADDRESS, sccrMapAddrBufferDword16))
                    {
                       device->octalEnableRegAddr = _FLD2VAL(CY_SMIF_SFDP_OCTAL_ENABLE_REG_ADDR, sccrMapAddrBufferDword16);
                    }
                    else
                    {
                       device->octalEnableRegAddr = CY_SMIF_NO_COMMAND_OR_MODE;
                    }
                    device->writeStsRegOeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
                    device->readStsRegOeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
            }
        }
    }

    return protocol;
}
static cy_en_smif_protocol_mode_t GetOctalDDRParams(SMIF_Type *base,
                                    cy_stc_smif_mem_device_cfg_t *device,
                                    cy_en_smif_slave_select_t slaveSelect,
                                    uint8_t* cmdSeqODDRAddr,
                                    uint8_t cmdSeqODDRTableLength,
                                    uint8_t* xSPiProfile1Addr,
                                    uint8_t xSPIProfile1TableLength,
                                    uint8_t* sccrMapAddr,
                                    uint8_t sccrMapTableLength,
                                    cy_stc_smif_context_t *context)
{
    uint8_t xSPiProfile1AddrBuffer[CY_SMIF_SFDP_LENGTH];
    cy_en_smif_status_t result = CY_SMIF_NO_OE_BIT;
    cy_stc_smif_mem_cmd_t *cmdSfdp = device->readSfdpCmd;
    cy_stc_smif_mem_cmd_t *cmdRead = device->readCmd;
    cy_en_smif_protocol_mode_t pMode = PROTOCOL_MODE_WRONG;
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.8', 5, 'uint8_t to uin32_t type conversion intentional.');
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.6', 4, 'composite expression to uint32_t conversion intentional.');

    /* Initialize SFDP Buffer */
    for (uint32_t i = 0U; i < CY_SMIF_SFDP_LENGTH; i++)
    {
        xSPiProfile1AddrBuffer[i] = 0U;
    }

    /* Get the JEDEC xSPI Profile 1.0 content into xSPiProfile1AddrBuffer[] */
    result = SfdpReadBuffer(base, cmdSfdp, xSPiProfile1Addr, slaveSelect,
                            xSPIProfile1TableLength, xSPiProfile1AddrBuffer, context);

    if (CY_SMIF_SUCCESS == result)
    {
        /* If found Octal DDR read is supported */
        if (xSPiProfile1AddrBuffer[XSPI_PROFILE_1_TABLE_BYTE_1] != 0U)
        {
             cmdRead->command = xSPiProfile1AddrBuffer[XSPI_PROFILE_1_TABLE_BYTE_1];
             cmdRead->commandH = cmdRead->command;

             /* command presence - 2 byte transfer */
             cmdRead->cmdPresence = CY_SMIF_PRESENT_2BYTE;

             /* The command transfer width */
             cmdRead->cmdWidth = CY_SMIF_WIDTH_OCTAL;

             /* DDR rate for all phases */
             cmdRead->cmdRate = CY_SMIF_DDR;
             cmdRead->dataRate = CY_SMIF_DDR;
             cmdRead->modeRate = CY_SMIF_DDR;
             cmdRead->addrRate = CY_SMIF_DDR;

             /* The address transfer width */
             cmdRead->addrWidth = CY_SMIF_WIDTH_OCTAL;

             /* The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
              cmdRead->mode = CY_SMIF_NO_COMMAND_OR_MODE;

             /* Variable latency configuration command */
             if (sccrMapTableLength > 0U)
             {
                SfdpSetVariableLatencyCmd(base, device, slaveSelect, sccrMapAddr, context);
             }

             if ((device->writeLatencyCmd->command != CY_SMIF_NO_COMMAND_OR_MODE))
             {
                uint8_t cfr_reg_address[5U];
                uint8_t cfr_value = 0;

                /* Initialize DWords */
                for (uint8_t i = 0U; i < 5U; i++)
                {
                    cfr_reg_address[i] = 0U;
                }

                switch (device->freq_of_operation)
                {
                    case CY_SMIF_100MHZ_OPERATION:
                        /* DWORD-5, Bits 11:7 should be > 0 to confirm if 100 MHz is supported or not */
                        if ( ((xSPiProfile1AddrBuffer[16] & 0x80U) | ((xSPiProfile1AddrBuffer[17] & 0x0FU) << 1U)) > 0U)
                        {
                            cmdRead->dummyCycles = (uint32_t) ((xSPiProfile1AddrBuffer[16] & 0x80U) | ((xSPiProfile1AddrBuffer[17] & 0x0FU) << 1U));

                            /* DWORD-5 Bits 6:2 */
                            cfr_value = (xSPiProfile1AddrBuffer[16] & 0x7CU);
                        }

                        break;
                    case CY_SMIF_133MHZ_OPERATION:
                        /* DWORD-5, Bits 21:17 should be > 0 to confirm if 133 MHz is supported or not */
                        if ((xSPiProfile1AddrBuffer[17] & 0x3EU) > 0U)
                        {
                             cmdRead->dummyCycles = (uint32_t) (xSPiProfile1AddrBuffer[17] & 0x3EU);

                            /* DWORD-5, Bits 21:17 */
                            cfr_value = ((xSPiProfile1AddrBuffer[17] & 0xF0U) << 1U) | (xSPiProfile1AddrBuffer[18] & 0x1U);
                        }
                        break;
                    case CY_SMIF_166MHZ_OPERATION:
                        /* DWORD-5, Bits 31:27 should be > 0 to confirm if 133 MHz is supported or not */
                        if ((xSPiProfile1AddrBuffer[19] & 0xE0U) > 0U)
                        {
                               cmdRead->dummyCycles = (uint32_t) xSPiProfile1AddrBuffer[19] & 0xE0U;

                            /* DWORD -5 Bits 26:22 */
                            cfr_value = ((xSPiProfile1AddrBuffer[19] & 0x07U) << 2U) | (xSPiProfile1AddrBuffer[18] & 0xC0U);
                        }
                        break;
                    case CY_SMIF_200MHZ_OPERATION:
                        /* DWORD-4, Bits 11:7 should be > 0 to confirm if 133 MHz is supported or not */
                        if ( ((xSPiProfile1AddrBuffer[12] & 0x80U) | ((xSPiProfile1AddrBuffer[13] & 0x0FU) << 1U)) > 0U)
                        {
                            cmdRead->dummyCycles = (uint32_t) ((xSPiProfile1AddrBuffer[12] & 0x80U) | ((xSPiProfile1AddrBuffer[13] & 0x0FU) << 1U));

                            /* DWORD-4 Bits 6:2 */
                            cfr_value = (xSPiProfile1AddrBuffer[12] & 0x7CU);
                        }
                        break;
                    default:
                        /* Do Nothing */
                        break;
                }

                if (cfr_value > 0U)
                {
                    ValueToByteArray(device->latencyCyclesRegAddr, cfr_reg_address, 0, 4U);
                    cfr_reg_address[4] = cfr_value;

                    result = Cy_SMIF_MemCmdWriteRegister(base,
                                         slaveSelect,
                                         device->writeEnCmd,
                                         device->writeLatencyCmd,
                                         cfr_reg_address,
                                         5U,
                                         context);
                }

             }
             else
             {
                 cmdRead->dummyCycles = 8U; /* Default value */
             }

             /* dummy cycles present - 2 byte transfer */
             if(cmdRead->dummyCycles > 0UL)
             {
                 cmdRead->dummyCyclesPresence = CY_SMIF_PRESENT_2BYTE;
             }

             /* The data transfer width */
             cmdRead->dataWidth = CY_SMIF_WIDTH_OCTAL;

             pMode = PROTOCOL_MODE_8D_8D_8D;

             /* Fill command sequence to switch to Octal DDR mode */
             uint8_t cmdSeqODDRAddrBuffer[CY_SMIF_SFDP_LENGTH];

            /* Initialize SFDP Buffer */
            for (uint32_t i = 0U; i < CY_SMIF_SFDP_LENGTH; i++)
            {
                cmdSeqODDRAddrBuffer[i] = 0U;
            }

            if (result == CY_SMIF_SUCCESS)
            {
                 /* Get the command sequence to change to Octal DDR mode content into cmdSeqODDRAddrBuffer[] */
                 result = SfdpReadBuffer(base, cmdSfdp, cmdSeqODDRAddr, slaveSelect,
                                cmdSeqODDRTableLength, cmdSeqODDRAddrBuffer, context);
            }

            if (result == CY_SMIF_SUCCESS)
            {
                cy_stc_smif_octal_ddr_en_seq_t* oDDREnSeq = device->octalDDREnableSeq;

                oDDREnSeq->cmdSeq1Len = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET];
                oDDREnSeq->cmdSeq2Len = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET];
                if (oDDREnSeq->cmdSeq1Len > 0U && oDDREnSeq->cmdSeq1Len < CY_SMIF_SFDP_ODDR_CMD_SEQ_MAX_LEN)
                {
                    oDDREnSeq->cmdSeq1[0] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET - 1U];
                    oDDREnSeq->cmdSeq1[1] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET - 2U];
                    oDDREnSeq->cmdSeq1[2] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET - 3U];
                    oDDREnSeq->cmdSeq1[3] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET + 4U];
                    oDDREnSeq->cmdSeq1[4] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET + 3U];
                    oDDREnSeq->cmdSeq1[5] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET + 2U];
                    oDDREnSeq->cmdSeq1[6] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET + 1U];
                }
                if (oDDREnSeq->cmdSeq2Len > 0U && oDDREnSeq->cmdSeq2Len < CY_SMIF_SFDP_ODDR_CMD_SEQ_MAX_LEN)
                {
                    oDDREnSeq->cmdSeq2[0] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET - 1U];
                    oDDREnSeq->cmdSeq2[1] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET - 2U];
                    oDDREnSeq->cmdSeq2[2] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET - 3U];
                    oDDREnSeq->cmdSeq2[3] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET + 4U];
                    oDDREnSeq->cmdSeq2[4] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET + 3U];
                    oDDREnSeq->cmdSeq2[5] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET + 2U];
                    oDDREnSeq->cmdSeq2[6] = cmdSeqODDRAddrBuffer[CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET + 1U];
                }
            }
        }
    }
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.6');
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.8');
    return pMode;
}
#endif

/*******************************************************************************
* Function Name: Cy_SMIF_MemInitSfdpMode
****************************************************************************//**
*
* This function can be used for any preferred data width based command instruction set from SFDP Buffer.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param memCfg
* The memory configuration structure that configures the SMIF memory device to
*  map into the device memory map. \ref cy_stc_smif_mem_config_t
*
* \param maxdataWidth
* maximum data width available on physical interface.
*
* \param qer_id
* Quad enable requirement ID specifically used for SFDP 1.0 compliant devices where
* Quad mode is available for use, but SFDP basic flash parameter table does not specify
* quad mode enable instruction. In other cases, this can be passed as CY_SMIF_SFDP_QER_0.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_NOT_FOUND
*       - \ref CY_SMIF_SFDP_CORRUPTED_TABLE
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*
*******************************************************************************/

cy_en_smif_status_t Cy_SMIF_MemInitSfdpMode(SMIF_Type *base,
                                    const cy_stc_smif_mem_config_t *memCfg,
                                    cy_en_smif_txfr_width_t maxdataWidth,
                                    cy_en_smif_qer_t qer_id,
                                    cy_stc_smif_context_t *context)
{
    /* Check the input parameters */
    CY_ASSERT_L1(NULL != memCfg);
    CY_ASSERT_L1(NULL != memCfg->deviceCfg);

    uint8_t sfdpBuffer[CY_SMIF_SFDP_LENGTH];
    uint8_t sfdpAddress[CY_SMIF_SFDP_ADDRESS_LENGTH];
    uint8_t addr4ByteAddress[CY_SMIF_SFDP_ADDRESS_LENGTH];
    uint8_t sectorMapAddr[CY_SMIF_SFDP_ADDRESS_LENGTH];
    uint8_t sccrMapAddr[CY_SMIF_SFDP_ADDRESS_LENGTH];
    uint8_t xSPiProfile1Addr[CY_SMIF_SFDP_ADDRESS_LENGTH];
    uint8_t cmdSeqODDRAddr[CY_SMIF_SFDP_ADDRESS_LENGTH];
    cy_en_smif_status_t result = CY_SMIF_NO_SFDP_SUPPORT;
    cy_stc_smif_erase_type_t eraseType[ERASE_TYPE_COUNT];
    uint8_t basicSpiTableLength = 0U, addr4ByteTableLength = 0U, sccrMapTableLength = 0U;
    uint8_t cmdSeqODDRTableLength = 0U, sectorMapTableLength = 0U, xSPIProfile1TableLength = 0U;
    cy_stc_smif_mem_device_cfg_t *device = memCfg->deviceCfg;
    cy_en_smif_slave_select_t slaveSelect = memCfg->slaveSelect;
    cy_en_smif_data_select_t dataSelect = memCfg->dataSelect;
    cy_stc_smif_mem_cmd_t *cmdSfdp = device->readSfdpCmd;

    /* Initialize the SFDP buffer */
    for (uint32_t i = 0U; i < CY_SMIF_SFDP_LENGTH; i++)
    {
        sfdpBuffer[i] = 0U;
    }

    /* Initialize the SFDP Table addresses */
    for (uint8_t i = 0U; i < CY_SMIF_SFDP_ADDRESS_LENGTH; i++)
    {
        sfdpAddress[i] = 0U;
        addr4ByteAddress[i] = 0U;
        sectorMapAddr[i] = 0U;
        sccrMapAddr[i] = 0U;
        xSPiProfile1Addr[i] = 0U;
        cmdSeqODDRAddr[i] = 0U;
    }
    /* Slave slot initialization */
    Cy_SMIF_SetDataSelect(base, slaveSelect, dataSelect);

    if (NULL != cmdSfdp)
    {
        /* Get the SDFP header and all parameter headers content into sfdpBuffer[] */
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 18.6','Data receive is disabled after function return.');
        result = SfdpReadBuffer(base, cmdSfdp, sfdpAddress, slaveSelect, HEADERS_LENGTH, sfdpBuffer, context);
    }
    else
    {
        result = CY_SMIF_NO_SFDP_SUPPORT;
    }

    if((CY_SMIF_SUCCESS == result) &&
       (sfdpBuffer[CY_SMIF_SFDP_SIGNATURE_BYTE_00] == (uint8_t)'S') &&
       (sfdpBuffer[CY_SMIF_SFDP_SIGNATURE_BYTE_01] == (uint8_t)'F') &&
       (sfdpBuffer[CY_SMIF_SFDP_SIGNATURE_BYTE_02] == (uint8_t)'D') &&
       (sfdpBuffer[CY_SMIF_SFDP_SIGNATURE_BYTE_03] == (uint8_t)'P') &&
       (sfdpBuffer[CY_SMIF_SFDP_MAJOR_REV] == CY_SMIF_SFDP_MAJOR_REV_1))
    {
        uint8_t sfdp_minor_revision = sfdpBuffer[CY_SMIF_SFDP_MINOR_REV];

        /* Find the JEDEC SFDP Basic SPI Flash Parameter Header */
        SfdpFindParameterTableAddress(BASIC_SPI_ID, sfdpBuffer, sfdpAddress, &basicSpiTableLength);

        if (basicSpiTableLength > 0U)
        {
            SfdpFindParameterTableAddress(FOUR_BYTE_ADDR_ID, sfdpBuffer, addr4ByteAddress, &addr4ByteTableLength);
            SfdpFindParameterTableAddress(SCCR_MAP_SPI_ID, sfdpBuffer, sccrMapAddr, &sccrMapTableLength);
            SfdpFindParameterTableAddress(XSPI_PROFILE_1_0_ID, sfdpBuffer, xSPiProfile1Addr, &xSPIProfile1TableLength);
            SfdpFindParameterTableAddress(CMD_SEQ_FOR_ODDR_ID, sfdpBuffer, cmdSeqODDRAddr, &cmdSeqODDRTableLength);
            SfdpFindParameterTableAddress(SECTOR_MAP_ID, sfdpBuffer, sectorMapAddr, &sectorMapTableLength);

            if (sectorMapTableLength == 0U)
            {
                device->hybridRegionCount = 0UL;
                device->hybridRegionInfo = NULL;
                result = CY_SMIF_SUCCESS; /* Not a Hybrid Memory */
            }

            /* Check if any of the parameter table size is more than SFDP Buffer length reserved */
            if ((basicSpiTableLength     > CY_SMIF_SFDP_LENGTH) ||
                (sectorMapTableLength    > CY_SMIF_SFDP_LENGTH))
            {
                result = CY_SMIF_SFDP_BUFFER_INSUFFICIENT;
            }
            if (CY_SMIF_SUCCESS == result)
            {
                CY_ASSERT_L1(CY_SMIF_CHECK_DEVICE_MEMBERS(device));

                /* Get the JEDEC basic flash parameter table content into sfdpBuffer[] */
                result = SfdpReadBuffer(base, cmdSfdp, sfdpAddress, slaveSelect, basicSpiTableLength, sfdpBuffer, context);

                /* The erase size and erase time for all 4 erase types */
                SfdpGetEraseSizeAndCmd(sfdpBuffer, eraseType);

                /* The external memory size */
                device->memSize = SfdpGetMemoryDensity(sfdpBuffer);

                /* The number of address bytes used by the memory slave device */
                device->numOfAddrBytes = SfdpGetNumOfAddrBytes(sfdpBuffer, device->memSize);

                /* The Write Enable command */
                SfdpSetWriteEnableCommand(device->writeEnCmd);

                /* The Write Disable command */
                SfdpSetWriteDisableCommand(device->writeDisCmd);

                /* The busy mask for the status registers */
                device->stsRegBusyMask = CY_SMIF_STATUS_REG_BUSY_MASK;

                /* The command to read the WIP-containing status register */
                SfdpSetWipStatusRegisterCommand(device->readStsRegWipCmd);

                if (maxdataWidth >= CY_SMIF_WIDTH_QUAD)
                {
                    if(sfdp_minor_revision != CY_SMIF_SFDP_JEDEC_REV_0)
                    {
                        /* The command to write into the QE-containing status register */
                        CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.8', 1, 'integer to enum conversion intentional.');
                        SfdpGetQuadEnableParameters(device,
                                                    (cy_en_smif_qer_t)(_FLD2VAL(CY_SMIF_SFDP_QE_REQUIREMENTS,
                                                    (uint32_t)sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_3A])));
                        CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.8');
                    }
                    else
                    {
                        SfdpGetQuadEnableParameters(device, qer_id);
                    }
                }

                /* Chip Erase command */
                SfdpSetChipEraseCommand(device->chipEraseCmd);

                /* The Read command for 3-byte addressing. The preference order quad > dual > single SPI */
                cy_stc_smif_mem_cmd_t *cmdRead = device->readCmd;
                cy_en_smif_protocol_mode_t pMode = PROTOCOL_MODE_WRONG;

                if(sfdp_minor_revision != CY_SMIF_SFDP_JEDEC_REV_0)
                {
                    /* The page size */
                    device->programSize = SfdpGetPageSize(sfdpBuffer);

                    /* Chip Erase Time */
                    device->chipEraseTime = SfdpGetChipEraseTime(sfdpBuffer);

                    /* Page Program Time */
                    device->programTime = SfdpGetPageProgramTime(sfdpBuffer);

                }
                else
                {
                    /* The page size - Default value */
                    device->programSize = CY_SMIF_SFDP_PAGE_SIZE_DEFAULT;

                    /* Chip Erase Time - Maximum value by default */
                    device->chipEraseTime = CY_SMIF_SFDP_CHIP_ERASE_TIME_64S;

                    /* Page Program Time - Maximum value by default */
                    device->programTime = CY_SMIF_SFDP_PROG_TIME_DEFAULT;

                    /* Enumerate Single SPI mode for SFDP 1.0 devices with QER 0 */
                    if (qer_id == CY_SMIF_SFDP_QER_0)
                    {
                        maxdataWidth = CY_SMIF_WIDTH_SINGLE;
                    }
                }

                pMode = SfdpGetReadCmdParams(sfdpBuffer, dataSelect, maxdataWidth, cmdRead);

                /* Read, Erase, and Program commands */
                uint32_t eraseTypeOffset = 1UL;
                if (FOUR_BYTE_ADDRESS == device->numOfAddrBytes)
                {
                    /* Enter 4-byte addressing mode */
                    result = SfdpEnterFourByteAddressing(base, sfdpBuffer[CY_SMIF_SFDP_BFPT_BYTE_3F], device, slaveSelect, context);
                    uint8_t fourByteAddressBuffer[CY_SMIF_SFDP_LENGTH];

                    /* Initialize SFDP Buffer */
                    for (uint32_t i = 0U; i < CY_SMIF_SFDP_LENGTH; i++)
                    {
                        fourByteAddressBuffer[i] = 0U;
                    }

                    if (CY_SMIF_SUCCESS == result)
                    {
                        /* Get the JEDEC 4-byte Address Instruction Table content into sfdpBuffer[] */
                        result = SfdpReadBuffer(base, cmdSfdp, addr4ByteAddress, slaveSelect,
                                                addr4ByteTableLength, fourByteAddressBuffer, context);
                    }
#if (CY_IP_MXSMIF_VERSION>=2)
                    /* Check if Octal mode related is supported first */
                    if ((device->readStsRegOeCmd != NULL) && (device->writeStsRegOeCmd != NULL))
                    {
                        if ((CY_SMIF_SUCCESS == result) && (maxdataWidth == CY_SMIF_WIDTH_OCTAL))
                        {
                            cy_en_smif_protocol_mode_t octalProtocolMode = PROTOCOL_MODE_WRONG;

                            if ((cmdSeqODDRTableLength > 0U) && (xSPIProfile1TableLength > 0U) && (device->octalDDREnableSeq != NULL))
                            {
                                octalProtocolMode = GetOctalDDRParams(base, device, slaveSelect,
                                                                      cmdSeqODDRAddr, cmdSeqODDRTableLength,
                                                                      xSPiProfile1Addr, xSPIProfile1TableLength,
                                                                      sccrMapAddr, sccrMapTableLength,
                                                                      context);
                            }

                            if(octalProtocolMode != PROTOCOL_MODE_8D_8D_8D) /* Check for Octal SDR if Octal DDR was not supported */
                            {
                                octalProtocolMode = GetOctalSDRParams(base, sfdpBuffer, device, slaveSelect, fourByteAddressBuffer[FOUR_BYTE_ADDRESS_TABLE_BYTE_0],
                                                             sccrMapAddr, sccrMapTableLength, context);
                            }

                            if (octalProtocolMode != PROTOCOL_MODE_WRONG)
                            {
                                pMode = octalProtocolMode;
                            }
                        }
                        else
                        {
                           device->writeStsRegOeCmd->command  = CY_SMIF_NO_COMMAND_OR_MODE;
                           device->readStsRegOeCmd->command  = CY_SMIF_NO_COMMAND_OR_MODE;
                           device->octalEnableRegAddr = CY_SMIF_NO_COMMAND_OR_MODE;
                           device->stsRegOctalEnableMask = 0UL;
                           device->writeStsRegOeCmd->cmdPresence  = CY_SMIF_NOT_PRESENT;
                           device->readStsRegOeCmd->cmdPresence  = CY_SMIF_NOT_PRESENT;
                        }
                    }
#endif
                    if (CY_SMIF_SUCCESS == result)
                    {
                        /* Rewrite the Read command instruction for 4-byte addressing mode */
                        SfdpGetReadFourBytesCmd(fourByteAddressBuffer, pMode, cmdRead);

                        /* Get the Program command instruction for 4-byte addressing mode */
                        SfdpGetProgramFourBytesCmd(fourByteAddressBuffer, pMode, device->programCmd);

                        /* Find the sector Erase command type with 4-byte addressing */
                        eraseTypeOffset = SfdpGetSectorEraseCommand(device, fourByteAddressBuffer, eraseType);
                    }
                }
                else /* Four Byte addressing not supported by the part */
                {
                    /* The program command for 3-byte addressing mode */
                    SfdpSetProgramCommand_1_1_1(device->programCmd);

                    /* Find the sector Erase command type with 3-byte addressing */
                    eraseTypeOffset = SfdpGetSectorEraseCommand(device, sfdpBuffer, eraseType);
                }

                if (COMMAND_IS_NOT_FOUND != eraseTypeOffset)
                {
                    /* The Erase sector size (from the JEDEC basic flash parameter table) */
                    device->eraseSize = 0x01UL << sfdpBuffer[eraseTypeOffset - 1UL];

                    if(sfdp_minor_revision != CY_SMIF_SFDP_JEDEC_REV_0)
                    {
                        /* Erase Time Type (from the JEDEC basic flash parameter table) */
                        device->eraseTime = SfdpGetEraseTime(eraseTypeOffset, sfdpBuffer, eraseType);
                    }
                    else
                    {
                        device->eraseTime = CY_SMIF_SFDP_ERASE_TIME_1S;
                    }
                }

                if (NULL != device->hybridRegionInfo)
                {
                    /* Get the Sector Map Parameter Table into sfdpBuffer[] */
                    result = SfdpReadBuffer(base, cmdSfdp, sectorMapAddr, slaveSelect,
                                            sectorMapTableLength, sfdpBuffer, context);
                    if (CY_SMIF_SUCCESS == result)
                    {
                        result = SfdpPopulateRegionInfo(base, sfdpBuffer, sectorMapTableLength, device, slaveSelect, context, eraseType);
                        if(result == CY_SMIF_NOT_HYBRID_MEM)
                        {
                            device->hybridRegionCount = 0UL;
                            device->hybridRegionInfo = NULL;
                            result = CY_SMIF_SUCCESS;
                        }
                    }
                }
            }
        }
        else
        {
            result = CY_SMIF_NO_SFDP_SUPPORT;
        }
    }
    else
    {
        result = CY_SMIF_NO_SFDP_SUPPORT;
    }

    /* XIP and Device Register initialization */
    if ((CY_SMIF_SUCCESS == result) &&
        (0U != (memCfg->flags & CY_SMIF_FLAG_MEMORY_MAPPED)) &&
        (_FLD2VAL(SMIF_CTL_XIP_MODE, SMIF_CTL(base)) != 1U))
    {
        /* Check valid parameters for XIP */
        CY_ASSERT_L3(MEM_ADDR_VALID( memCfg->baseAddress, memCfg->memMappedSize));
        CY_ASSERT_L3(MEM_MAPPED_SIZE_VALID( memCfg->memMappedSize));
        SMIF_DEVICE_Type volatile * device_base = Cy_SMIF_GetDeviceBySlot(base, slaveSelect);

        if (device_base != NULL)
        {
            XipRegInit(device_base, memCfg);

#if(CY_IP_MXSMIF_VERSION>=2)
            context->preXIPDataRate = memCfg->deviceCfg->readCmd->dataRate;
#endif /* CY_IP_MXSMIF_VERSION */
        }

        /* The device control register initialization */
        SMIF_DEVICE_CTL(device_base) = _VAL2FLD(SMIF_DEVICE_CTL_WR_EN, ((bool)(memCfg->flags & CY_SMIF_FLAG_WRITE_ENABLE))? 1U : 0U) |
                      _VAL2FLD(SMIF_DEVICE_CTL_CRYPTO_EN, ((bool)(memCfg->flags & CY_SMIF_FLAG_CRYPTO_ENABLE))? 1U : 0U) |
                      _VAL2FLD(SMIF_DEVICE_CTL_DATA_SEL,  (uint32_t)memCfg->dataSelect) |
#if(CY_IP_MXSMIF_VERSION>=2)
                       _VAL2FLD(SMIF_DEVICE_CTL_MERGE_EN,  ((bool)(memCfg->flags & CY_SMIF_FLAG_MERGE_ENABLE))? 1U : 0U)  |
                       _VAL2FLD(SMIF_DEVICE_CTL_MERGE_TIMEOUT,  (uint32_t)memCfg->mergeTimeout) |
#endif /* CY_IP_MXSMIF_VERSION */
                       SMIF_DEVICE_CTL_ENABLED_Msk;
    }


    return(result);
}
/*******************************************************************************
* Function Name: Cy_SMIF_MemSfdpDetect
****************************************************************************//**
*
* This function detects the device signature for SFDP devices.
* Refer to the SFDP spec (JESD216B) for details.
* The function asks the device using an SPI and then populates the relevant
* parameters for \ref cy_stc_smif_mem_device_cfg_t.
*
* \note This function is a blocking function and blocks until the structure data
* is read and returned. This function uses \ref Cy_SMIF_TransmitCommand()
* If there is no support for SFDP in the memory device, the API returns an
* error condition. The function requires:
*   - SMIF initialized and enabled to work in the normal mode;
*   - readSfdpCmd field of \ref cy_stc_smif_mem_device_cfg_t is enabled.
*
* \note The SFDP detect takes into account the types of the SPI supported by the
* memory device and also the dataSelect option selected to choose which SPI mode
* (SPI, DSPI, QSPI) to load into the structures. The algorithm prefers
* QSPI>DSPI>SPI, provided there is support for it in the memory device and the
* dataSelect selected by the user.
*
* \note 4-byte addressing mode is set when the memory device supports
*       3- or 4-byte addressing mode.
*
* \note When the Erase command is not found the width of the command
*  transfer (cmdWidth) is set to CY_SMIF_WIDTH_NA. When the Program command
*  is not found for 4 byte addressing mode the Program command instruction
*  is set for 1S-1S-1S Protocol mode and 3-byte addressing mode.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param device
* The device structure instance declared by the user. This is where the detected
* parameters are stored and returned.
*
* \param slaveSelect
* The slave select line for the device.
*
* \param dataSelect
* The data line selection options for a slave device.
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
*       - \ref CY_SMIF_NO_SFDP_SUPPORT
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_MemSfdpDetect(SMIF_Type *base,
                                    cy_stc_smif_mem_device_cfg_t *device,
                                    cy_en_smif_slave_select_t slaveSelect,
                                    cy_en_smif_data_select_t dataSelect,
                                    cy_stc_smif_context_t *context)
{

    /* Check the input parameters */
    CY_ASSERT_L1(NULL != device);

    cy_stc_smif_mem_config_t memSfdpDetect =
    {
        .slaveSelect = slaveSelect,
        .flags = 0,
        .dataSelect = dataSelect,
        .baseAddress = 0U,
        .memMappedSize = 0U,
        .dualQuadSlots = 0,
        .deviceCfg = device,
    #if (CY_IP_MXSMIF_VERSION >= 3)
        .mergeTimeout = CY_SMIF_MERGE_TIMEOUT_1_CYCLE
    #endif /* CY_IP_MXSMIF_VERSION */
    };

    return Cy_SMIF_MemInitSfdpMode(base, &memSfdpDetect, CY_SMIF_WIDTH_OCTAL, CY_SMIF_SFDP_QER_0, context);
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXSMIF */

/* [] END OF FILE */
