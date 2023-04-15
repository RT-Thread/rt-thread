/***************************************************************************//**
* \file cy_flash_v2.c
* \version 1.0
*
* \brief
* Provides the public functions for the API for the Flash Driver.
*
********************************************************************************
* \copyright
* Copyright 2021, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cy_device.h"
#if defined(CY_IP_MXFLASHC_VERSION_ECT)

#include "cy_flash.h"
#include "cy_sysint.h"
#include "cy_ipc_drv.h"
#include "cy_syslib.h"

/** SROM API flash region ID shift for flash row information */
#define CY_FLASH_REGION_ID_SHIFT           (16U)
#define CY_FLASH_ROW_ID_MASK               (0xFFFFU)
/** SROM API flash region IDs */
#define CY_FLASH_REGION_ID_MAIN         (0UL)
#define CY_FLASH_REGION_ID_WFLASH       (1UL)

#define ADDRESS_LENGTH_32_BIT (4U)
#define ADDRESS_LENGTH_256_BIT (32U)
#define DATA_LENGTH_32_BIT (1U)
#define DATA_LENGTH_256_BIT (8U)

static cy_en_flashdrv_status_t Cy_Flash_GetRowDetails(uint32_t rowAddr, uint8_t *rowID, cy_en_flash_checksum_bank_t *bank, cy_en_flash_checksum_region_t *region);
static cy_en_flashdrv_status_t Cy_Flash_CalculateHash_Ext(const cy_stc_flash_computehash_config_t *config,  uint32_t* hashPtr);
static cy_en_flashdrv_status_t Cy_Flash_EraseSector_Ext(const cy_stc_flash_erasesector_config_t *config, cy_en_flash_driver_blocking_t block);
static en_flash_bounds_t Cy_Flash_WorkBoundsCheck(uint32_t address);
static en_flash_bounds_t Cy_Flash_MainBoundsCheck(uint32_t address);
static en_flash_bounds_t Cy_Flash_BoundsCheck(uint32_t flashAddr);
static cy_en_flashdrv_status_t Cy_Flash_ProcessOpcode(uint32_t opcode);
static uint8_t g_non_block_context = 0;

/*******************************************************************************
* Function Name: Cy_Flash_CallSromApiForFlashWrite
****************************************************************************//**
*
* This function call SROM API driver for flash writing (e.g. program row,
* erase sector). Then, processes response message of the
* driver API and response message of SROM API if required.
*
* apiArgs pointer to SROM API arguments.
*
* block driver blocking mode cy_en_flash_driver_blocking_t
*
* Returns the status of the Flash operation.
*
*******************************************************************************/
static cy_en_flashdrv_status_t Cy_Flash_CallSromApiForFlashWrite(const un_srom_api_args_t* apiArgs, cy_en_flash_driver_blocking_t block)
{
    if(block == CY_FLASH_DRIVER_BLOCKING)
    {
        un_srom_api_resps_t apiResp = {{ 0UL }};

        /* Call SROM API with blocking mode */
        cy_en_srom_driver_status_t sromDrvStatus;
        sromDrvStatus = Cy_Srom_CallApi(apiArgs, &apiResp);
        if(sromDrvStatus == CY_SROM_DR_IPC_BUSY)
        {
            return CY_FLASH_DRV_IPC_BUSY;
        }
        else if(sromDrvStatus == CY_SROM_DR_TIMEOUT)
        {
            return CY_FLASH_DRV_SROM_API_TIMEOUT;
        }
        else if(sromDrvStatus == CY_SROM_DR_API_UNKNOWN)
        {
            return CY_FLASH_DRV_ERR_UNC;
        }
        else
        {
            cy_en_flashdrv_status_t result;
            result = Cy_Flash_ProcessOpcode(apiResp.resp[0]);
            if(result != CY_FLASH_DRV_SUCCESS)
            {
                return result;
            }

            /* Invalidates the flash cache and buffer */
            FLASHC_FLASH_CMD = _VAL2FLD(FLASHC_FLASH_CMD_INV, 1U);

            // Wait for completion (HW will clear bit)
            while (_FLD2VAL(FLASHC_FLASH_CMD_INV, FLASHC_FLASH_CMD) != 0U)
            {
            }

            return CY_FLASH_DRV_SUCCESS;
        }
    }
    else
    {
        /* Call SROM API with non-blocking mode */
        cy_en_srom_driver_status_t status = Cy_Srom_CallApi_NonBlock(apiArgs);

        if ( status != CY_SROM_DR_SUCCEEDED)
        {
            /* The IPC structure is already locked by another process */
            return CY_FLASH_DRV_IPC_BUSY;
        }
        return CY_FLASH_DRV_SUCCESS;
    }
}


/*******************************************************************************
* Function Name: Cy_Flash_Program_WorkFlash
****************************************************************************//**
*
* This function writes an array of data to work flash. Reports success or
* or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash. User firmware should not enter the hibernate
* mode until flash Write is complete. The Flash operation is allowed in Sleep and
* Deep-sleep modes. During the Flash operation, the device should not be reset,
* including the XRES pin, a software reset, and watchdog reset sources. Also,
* low-voltage detect circuits should be configured to generate an interrupt instead
* of a reset. Otherwise, portions of flash may undergo unexpected changes.
*
* config configuration of this function.
* This parameter is defined by the cy_stc_flash_programrow_config_t
* in group_flash_srom_config_structure macro.
*
* Returns the status of the Flash operation (see cy_en_flashdrv_status_t).
*
* Note: row or page is same and of the size 512 bytes
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_Program_WorkFlash(const cy_stc_flash_programrow_config_t* config)
{
    cy_en_flashdrv_status_t status = CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;

    /* Checks if input pointers are not NULL */
    if(config == NULL)
    {
        return status;
    }

    /* Checks if input address are valid */
    if((Cy_Flash_WorkBoundsCheck((uint32_t)config->destAddr) == CY_FLASH_OUT_OF_BOUNDS) || (config->dataAddr == NULL))
    {
        return status;
    }
    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
    apiArgs.ProgramRow.arg0.opcode         = (uint32_t)CY_SROM_OP_FLASH_PROGRAM_WFLASH;
    apiArgs.ProgramRow.arg0.blocking       = (uint32_t)CY_FLASH_PROGRAMROW_BLOCKING;
    apiArgs.ProgramRow.arg0.skipBlankCheck = (uint32_t)config->skipBC;
    apiArgs.ProgramRow.arg1.dataLoc        = (uint32_t)config->dataLoc;
    apiArgs.ProgramRow.arg1.dataSize       = (uint32_t)config->dataSize;
    apiArgs.ProgramRow.arg1.interruptMask  = (uint32_t)config->intrMask;
    apiArgs.ProgramRow.arg2.dstAddr        = (uint32_t)config->destAddr;
    apiArgs.ProgramRow.arg3.srcAddr        = (uint32_t)config->dataAddr;
    /* Call SROM API driver and process response */
    status = Cy_Flash_CallSromApiForFlashWrite(&apiArgs, CY_FLASH_DRIVER_BLOCKING);
    return status;
}

/*******************************************************************************
* Function Name: Cy_Flash_Program
****************************************************************************//**
*
* This function writes an array of data to a single row of flash. Reports success or
* or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash. User firmware should not enter the hibernate
* mode until flash Write is complete. The Flash operation is allowed in Sleep and
* Deep-sleep modes. During the Flash operation, the device should not be reset,
* including the XRES pin, a software reset, and watchdog reset sources. Also,
* low-voltage detect circuits should be configured to generate an interrupt instead
* of a reset. Otherwise, portions of flash may undergo unexpected changes.
*
* config configuration of this function.
* This parameter is defined by the cy_stc_flash_programrow_config_t
* in group_flash_srom_config_structure macro.
*
* Returns the status of the Flash operation (see cy_en_flashdrv_status_t).
*
* Note: row or page is same and of the size 512 bytes
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_Program(const cy_stc_flash_programrow_config_t* config, cy_en_flash_driver_blocking_t block)
{
    cy_en_flashdrv_status_t status;

    /* Checks if input pointers are not NULL */
    if(config == NULL)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }

    /* Checks if input address are valid */
    if((Cy_Flash_BoundsCheck((uint32_t)config->destAddr) == CY_FLASH_OUT_OF_BOUNDS) || (config->dataAddr == NULL))
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }

    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
    apiArgs.ProgramRow.arg0.opcode         = (uint32_t)CY_SROM_OP_FLASH_PROGRAM_ROW;
    apiArgs.ProgramRow.arg0.blocking       = (uint32_t)config->blocking;
    apiArgs.ProgramRow.arg0.skipBlankCheck = (uint32_t)config->skipBC;
    apiArgs.ProgramRow.arg1.dataLoc        = (uint32_t)config->dataLoc;
    apiArgs.ProgramRow.arg1.dataSize       = (uint32_t)config->dataSize;
    apiArgs.ProgramRow.arg1.interruptMask  = (uint32_t)config->intrMask;
    apiArgs.ProgramRow.arg2.dstAddr        = (uint32_t)config->destAddr;
    apiArgs.ProgramRow.arg3.srcAddr        = (uint32_t)config->dataAddr;
    /* Call SROM API driver and process response */
    status = Cy_Flash_CallSromApiForFlashWrite(&apiArgs, block);

    if(status == CY_FLASH_DRV_SUCCESS && block == CY_FLASH_DRIVER_NON_BLOCKING)
    {
        g_non_block_context = (uint8_t)(FLASHC_FM_CTL_ECT_STATUS_PGM_WORK_Msk | FLASHC_FM_CTL_ECT_STATUS_PGM_CODE_Msk);
        status = CY_FLASH_DRV_OPERATION_STARTED;
    }
    return status;
}

/*******************************************************************************
* Function Name: Cy_Flash_Checksum
****************************************************************************//**
*
* Returns a checksum value of the specified flash row. supports only blocking
* mode for now.
* rowNum The Checksum is calculated to the flash row.
*
* checksumPtr The pointer to the address where checksum is to be stored
*
* Returns the status of the Flash operation.
*
* Note:row or page is same and of the size 512 bytes
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_Checksum(const cy_stc_flash_checksum_config_t *config, uint32_t* checksumPtr)
{
    /* Checks whether the input parameters are valid */
    if (config->rowId >= CY_FLASH_NUMBER_ROWS)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 14.3', 1, \
'Checked manually. Intentional  expression will always be true for CAT1C devices.');
    if(CPUSS_FLASH_SIZE >= 4096u)
    {
        apiArgs.CheckSum.arg0.opcode = (uint32_t)CY_SROM_OP_FLASH_CHECKSUM;
        apiArgs.CheckSum.arg0.region = (uint32_t)config->region;
        apiArgs.CheckSum.arg0.whole  = (uint32_t)config->whole;
        apiArgs.CheckSum.arg0.row_id = (uint32_t)config->rowId;
        apiArgs.CheckSum.arg0.bank   = (uint32_t)config->bank;
    }
    else
    {
        apiArgs.CheckSumLessThan4M.arg0.opcode = (uint32_t)CY_SROM_OP_FLASH_CHECKSUM;
        apiArgs.CheckSumLessThan4M.arg0.region = (uint32_t)config->region;
        apiArgs.CheckSumLessThan4M.arg0.whole  = (uint32_t)config->whole;
        apiArgs.CheckSumLessThan4M.arg0.row_id = (uint32_t)config->rowId;
        apiArgs.CheckSumLessThan4M.arg0.bank   = (uint32_t)config->bank;
    }
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 14.3');
    /* Call SROM API with blocking mode */
    un_srom_api_resps_t apiResp = {{ 0UL }};
    cy_en_srom_driver_status_t sromDrvStatus;
    sromDrvStatus = Cy_Srom_CallApi(&apiArgs, &apiResp);
    if(sromDrvStatus == CY_SROM_DR_IPC_BUSY)
    {
        return CY_FLASH_DRV_IPC_BUSY;
    }
    else if(sromDrvStatus == CY_SROM_DR_TIMEOUT)
    {
        return CY_FLASH_DRV_SROM_API_TIMEOUT;
    }
    else if(sromDrvStatus == CY_SROM_DR_API_UNKNOWN)
    {
        return CY_FLASH_DRV_ERR_UNC;
    }
    else
    {
        /* non-empty terminating "else" statement. */
    }

    /* Process response message from API */
    cy_en_flashdrv_status_t result;
    result = Cy_Flash_ProcessOpcode(apiResp.resp[0]);
    if(result == CY_FLASH_DRV_SUCCESS)
    {
        // checksum is in data1 not data0. the the pointer returned is to data0.
        uint32_t data[2];
//        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.1','Checked manually. Intentional Non boolean type is interpreted as boolean.');
        Cy_IPC_Drv_ReadDDataValue(Cy_IPC_Drv_GetIpcBaseAddress((uint32_t)CY_IPC_CHAN_SYSCALL), data );
        *checksumPtr = data[1];
    }
    return result;
}


/*******************************************************************************
* Function Name: Cy_Flash_CalculateHash_Ext
****************************************************************************//**
*
* Returns a hash value of the specified region of flash. supports only blocking
* mode for now.
* data Start the data address.
*
* numberOfBytes The hash value is calculated for the number of bytes after the
* start data address (0 - 1 byte, 1- 2 bytes etc).
*
* hashPtr The pointer to the address where hash is to be stored
*
* Returns the status of the Flash operation.
*
*******************************************************************************/
static cy_en_flashdrv_status_t Cy_Flash_CalculateHash_Ext(const cy_stc_flash_computehash_config_t *config,  uint32_t* hashPtr)
{
    /* Checks whether the input parameters are valid */
    if ((config->startAddr == NULL) || (config->numOfByte == 0UL) || (hashPtr == NULL))
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
    apiArgs.ComputeHash.arg0.opcode      = (uint32_t)CY_SROM_OP_FLASH_HASH;
    apiArgs.ComputeHash.arg0.type        = (uint32_t)config->type;
    apiArgs.ComputeHash.arg1.start_addr  = (uint32_t)config->startAddr;
    apiArgs.ComputeHash.arg2.number_byte = (config->numOfByte - 1UL);

    /* Call SROM API with blocking mode */
    un_srom_api_resps_t apiResp = {{ 0UL }};
    cy_en_srom_driver_status_t sromDrvStatus;
    sromDrvStatus = Cy_Srom_CallApi(&apiArgs, &apiResp);
    if(sromDrvStatus == CY_SROM_DR_IPC_BUSY)
    {
        return CY_FLASH_DRV_IPC_BUSY;
    }
    else if(sromDrvStatus == CY_SROM_DR_TIMEOUT)
    {
        return CY_FLASH_DRV_SROM_API_TIMEOUT;
    }
    else if(sromDrvStatus == CY_SROM_DR_API_UNKNOWN)
    {
        return CY_FLASH_DRV_ERR_UNC;
    }
    else
    {
        /* non-empty terminating "else" statement. */
    }

    /* Process response message from API */
    cy_en_flashdrv_status_t result;
    result = Cy_Flash_ProcessOpcode(apiResp.resp[0]);
    if(result == CY_FLASH_DRV_SUCCESS)
    {
        *hashPtr = apiResp.ComputeHash.resp0.hash_crc;
    }
    return result;
}


/*******************************************************************************
* Function Name: Cy_Flash_WorkBoundsCheck
****************************************************************************//**
*
* Checks if Flash address is out of work region.
*
* address Address to be checked
*
* en_flash_bounds_t
*
*******************************************************************************/
static en_flash_bounds_t Cy_Flash_WorkBoundsCheck(uint32_t address)
{
    cy_en_bankmode_t bankmode = Cy_Flashc_GetWorkBankMode();
    if(bankmode == CY_FLASH_SINGLE_BANK_MODE)
    {
        if(( CY_WFLASH_LG_SBM_TOP <= address) && (address < CY_WFLASH_LG_SBM_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if((CY_WFLASH_SM_SBM_TOP <= address) && (address < CY_WFLASH_SM_SBM_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }
    }
    else
    {
        if(( CY_WFLASH_LG_DBM0_TOP <= address) && (address < CY_WFLASH_LG_DBM0_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if(( CY_WFLASH_SM_DBM0_TOP <= address) && (address < CY_WFLASH_SM_DBM0_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if(( CY_WFLASH_LG_DBM1_TOP <= address) && (address < CY_WFLASH_LG_DBM1_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if(( CY_WFLASH_SM_DBM1_TOP <= address) && (address < CY_WFLASH_SM_DBM1_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }
    }

    return(CY_FLASH_OUT_OF_BOUNDS);
}

/*******************************************************************************
* Function Name: Cy_Flash_MainBoundsCheck
****************************************************************************//**
*
* Returns 1 if Flash address is out of main region, otherwise returns 0.
*
* address Address to be checked
*
* 1 - out of bound, 0 - in flash bounds
*
*******************************************************************************/
static en_flash_bounds_t Cy_Flash_MainBoundsCheck(uint32_t address)
{
    cy_en_bankmode_t bankmode = Cy_Flashc_GetMainBankMode();
    if(bankmode == CY_FLASH_SINGLE_BANK_MODE)
    {
        if(( CY_FLASH_LG_SBM_TOP <= address) && (address < CY_FLASH_LG_SBM_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if(( CY_FLASH_SM_SBM_TOP <= address) && (address < CY_FLASH_SM_SBM_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }
    }
    else
    {
        if(( CY_FLASH_LG_DBM0_TOP <= address) && (address < CY_FLASH_LG_DBM0_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if(( CY_FLASH_SM_DBM0_TOP <= address) && (address < CY_FLASH_SM_DBM0_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if(( CY_FLASH_LG_DBM1_TOP <= address) && (address < CY_FLASH_LG_DBM1_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }

        if(( CY_FLASH_SM_DBM1_TOP <= address) && (address < CY_FLASH_SM_DBM1_END))
        {
            return(CY_FLASH_IN_BOUNDS);
        }
    }

    return(CY_FLASH_OUT_OF_BOUNDS);
}

/*******************************************************************************
* Function Name: Cy_Flash_BoundsCheck
****************************************************************************//**
*
* Returns 1 if Flash address is out of boundary, otherwise returns 0.
*
* flashAddr Address to be checked
*
* 1 - out of bound, 0 - in flash bounds
*
*******************************************************************************/
static en_flash_bounds_t Cy_Flash_BoundsCheck(uint32_t flashAddr)
{
    if(Cy_Flash_WorkBoundsCheck(flashAddr) == CY_FLASH_IN_BOUNDS)
    {
        return(CY_FLASH_IN_BOUNDS);
    }

    if(Cy_Flash_MainBoundsCheck(flashAddr) == CY_FLASH_IN_BOUNDS)
    {
        return(CY_FLASH_IN_BOUNDS);
    }

    return (CY_FLASH_OUT_OF_BOUNDS);
}

/*******************************************************************************
* Function Name: Cy_Flash_ProcessOpcode
****************************************************************************//**
*
* Converts System Call returns to the Flash driver return defines.
*
* opcode The value returned by the System Call.
*
* Flash driver return. cy_en_flashdrv_status_t only support a
*         part of SROM response. please use Cy_Srom_GetApiResponse to
*         get complete status of SROM API.
*
*******************************************************************************/
static cy_en_flashdrv_status_t Cy_Flash_ProcessOpcode(uint32_t opcode)
{
    cy_en_flashdrv_status_t retVal;
    cy_en_srom_api_status_t apiStatus;
    apiStatus = Cy_Srom_ConvertRespToStatus(opcode);

    // Process error code
    switch (apiStatus)
    {
    case CY_SROM_STATUS_SUCCESS:
        retVal = CY_FLASH_DRV_SUCCESS;
        break;
    case CY_SROM_STATUS_INVALID:
        retVal = CY_FLASH_DRV_ERR_UNC;
        break;
    case CY_SROM_STATUS_INVALID_PROTECTION:
        retVal = CY_FLASH_DRV_INV_PROT;
        break;
    case CY_SROM_STATUS_INVALID_FM_PL:
        retVal = CY_FLASH_DRV_INVALID_FM_PL;
        break;
    case CY_SROM_STATUS_INVALID_FLASH_ADDR:
        retVal = CY_FLASH_DRV_INVALID_FLASH_ADDR;
        break;
    case CY_SROM_STATUS_NVM_PROTECTED:
        retVal = CY_FLASH_DRV_ROW_PROTECTED;
        break;
    case CY_SROM_STATUS_INVALID_IPC_STRUCT:
        retVal = CY_FLASH_DRV_IPC_BUSY;
        break;
    case CY_SROM_STAUTS_CHECKSUM_NON_ZERO:
        retVal = CY_FLASH_DRV_CHECKSUM_NON_ZERO;
        break;
    case CY_SROM_STATUS_SECTOR_SUSPEND:
        retVal = CY_FLASH_DRV_SECTOR_SUSPEND;
        break;
    case CY_SROM_STATUS_NO_ERASE_SUSPEND:
        retVal = CY_FLASH_DRV_NO_ERASE_SUSPEND;
        break;
    case CY_SROM_STATUS_FLASH_NOT_ERASED:
        retVal = CY_FLASH_DRV_FLASH_NOT_ERASED;
        break;
    case CY_SROM_STATUS_NO_ERASE_ONGOING:
        retVal = CY_FLASH_DRV_NO_ERASE_ONGOING;
        break;
    case CY_SROM_STATUS_ACTIVE_ERASE:
        retVal = CY_FLASH_DRV_ACTIVE_ERASE;
        break;
    case CY_SROM_STAUTS_INVALID_DATA_WIDTH:
        retVal = CY_FLASH_DRV_INVALID_DATA_WIDTH;
        break;
    case CY_SROM_STATUS_FLASH_SAFTEY_ENABLED:
        retVal = CY_FLASH_DRV_FLASH_SAFTEY_ENABLED;
        break;
    case CY_SROM_STATUS_INVALID_SFLASH_ADDR:
        retVal = CY_FLASH_DRV_INVALID_SFLASH_ADDR;
        break;
    case CY_SROM_STATUS_SFLASH_BACKUP_ERASED:
        retVal = CY_FLASH_DRV_SFLASH_BACKUP_ERASED;
        break;
    default:
        retVal = CY_FLASH_DRV_ERR_UNC;
        break;
    }

    return (retVal);
}

/*******************************************************************************
* Function Name: Cy_Flash_EraseSector_Ext
****************************************************************************//**
*
* This function Starts the sector erase operation on the specified sector.
* This function cannot be called on SFLASH. Reports success
* or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash. User firmware should not enter the hibernate
* mode until flash Erase is complete. The Flash operation is allowed in Sleep and
* Deep-sleep modes. During the Flash operation, the device should not be reset,
* including the XRES pin, a software reset, and watchdog reset sources. Also,
* low-voltage detect circuits should be configured to generate an interrupt instead
* of a reset. Otherwise, portions of flash may undergo unexpected changes.
*
* config configuration of  this function.
* This parameter is defined by the cy_stc_flash_erasesector_config_t
* in group_flash_srom_config_structure macro.
*
* Returns the status of the Flash operation (see cy_en_flashdrv_status_t).
*
*******************************************************************************/
static cy_en_flashdrv_status_t Cy_Flash_EraseSector_Ext(const cy_stc_flash_erasesector_config_t *config, cy_en_flash_driver_blocking_t block)
{
    cy_en_flashdrv_status_t status;
    /* Checks if input pointers are not NULL */
    if (config == NULL)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }

    /* Checks if input address is in work/main region */
    if(Cy_Flash_BoundsCheck((uint32_t)(config->sectorAddr)) == CY_FLASH_OUT_OF_BOUNDS)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }

    /* Checks if input address is word aligned */
    if(((uint32_t)(config->sectorAddr) % sizeof(uint32_t)) != 0UL)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
    apiArgs.EraseSector.arg0.opcode        = (uint32_t)CY_SROM_OP_FLASH_ERASE_SECTOR;
    apiArgs.EraseSector.arg0.blocking      = (uint32_t)config->blocking;
    apiArgs.EraseSector.arg0.interruptMask = (uint32_t)config->intrMask;
    apiArgs.EraseSector.arg1.address       = (uint32_t)config->sectorAddr;

    /* Call SROM API driver and process response */
    status = Cy_Flash_CallSromApiForFlashWrite(&apiArgs, block);
    return status;
}

/*******************************************************************************
* Function Name: Cy_Flash_EraseSuspend
****************************************************************************//**
*
* This function suspends an ongoing erase operation. User should not read from a
* sector which is suspended from an erase operation. Cy_Flash_ProgramRow function
* will return error if invoked on suspended sector.
* This function cannot be called on SFLASH. Reports success
* or a reason for failure. Does not return until the Erase operation is complete.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash.
* This function supports only blocking mode for now.
*
* Returns the status of the Flash operation (see cy_en_flashdrv_status_t).
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseSuspend(void)
{
    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
    apiArgs.EraseSuspend.arg0.opcode = (uint32_t)CY_SROM_OP_FLASH_ERASE_SUSPEND;

    /* Call SROM API with blocking mode */
    un_srom_api_resps_t apiResp = {{ 0UL }};
    cy_en_srom_driver_status_t sromDrvStatus;
    sromDrvStatus = Cy_Srom_CallApi(&apiArgs, &apiResp);
    if(sromDrvStatus == CY_SROM_DR_IPC_BUSY)
    {
        return CY_FLASH_DRV_IPC_BUSY;
    }
    else if(sromDrvStatus == CY_SROM_DR_TIMEOUT)
    {
        return CY_FLASH_DRV_SROM_API_TIMEOUT;
    }
    else if(sromDrvStatus == CY_SROM_DR_API_UNKNOWN)
    {
        return CY_FLASH_DRV_ERR_UNC;
    }
    else
    {
        /* non-empty terminating "else" statement. */
    }

    /* Process response message from API */
    cy_en_flashdrv_status_t result;
    result = Cy_Flash_ProcessOpcode(apiResp.resp[0]);
    if(result == CY_FLASH_DRV_SUCCESS)
    {
        /* Invalidates the flash cache and buffer */
        FLASHC_FLASH_CMD = _VAL2FLD(FLASHC_FLASH_CMD_INV, 1U);

        // Wait for completion (HW will clear bit)
        while (_FLD2VAL(FLASHC_FLASH_CMD_INV, FLASHC_FLASH_CMD) != 0U)
        {
        }
    }
    return result;
}

/*******************************************************************************
* Function Name: Cy_Flash_EraseResume
****************************************************************************//**
*
* This function calls to resume a suspended erase operation.
* Reports success or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash.
*
* config configuration of this function.
* This parameter is defined by the cy_stc_flash_eraseresume_config_t
* in group_flash_srom_config_structure macro.
*
* Returns the status of the Flash operation (see cy_en_flashdrv_status_t).
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseResume(const cy_stc_flash_eraseresume_config_t *config)
{
    /* Checks if input pointers are not NULL */
    if (config == NULL)
    {
        return (cy_en_flashdrv_status_t)CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
    apiArgs.EraseResume.arg0.opcode   = (uint32_t)CY_SROM_OP_FLASH_ERASE_RESUME;
    apiArgs.EraseResume.arg0.blocking = (uint32_t)config->intrMask;
    apiArgs.EraseResume.arg0.intrmask = (uint32_t)config->blocking;

    /* Call SROM API with blocking mode */
    un_srom_api_resps_t apiResp = {{ 0UL }};
    cy_en_srom_driver_status_t sromDrvStatus;
    sromDrvStatus = Cy_Srom_CallApi(&apiArgs, &apiResp);
    if(sromDrvStatus == CY_SROM_DR_IPC_BUSY)
    {
        return CY_FLASH_DRV_IPC_BUSY;
    }
    else if(sromDrvStatus == CY_SROM_DR_TIMEOUT)
    {
        return CY_FLASH_DRV_SROM_API_TIMEOUT;
    }
    else if(sromDrvStatus == CY_SROM_DR_API_UNKNOWN)
    {
        return CY_FLASH_DRV_ERR_UNC;
    }
    else
    {
        /* Process response message from API */
        cy_en_flashdrv_status_t result;
        result = Cy_Flash_ProcessOpcode(apiResp.resp[0]);
        return result;
    }
}


/*******************************************************************************
* Function Name: Cy_Flash_BlankCheck
****************************************************************************//**
*
* This function performs blank check on the addressed work FLASH.
* Reports success or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash.
*
* config configuration of this function.
* This parameter is defined by the cy_stc_flash_blankcheck_config_t
* in group_flash_srom_config_structure macro.
*
* Returns the status of the Flash operation (see cy_en_flashdrv_status_t).
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_BlankCheck(const cy_stc_flash_blankcheck_config_t *config, cy_en_flash_driver_blocking_t block)
{
    /* Checks if input pointers are not NULL */
    if (config == NULL)
    {
        return (cy_en_flashdrv_status_t)CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }

    if(config->numOfWordsToBeChecked == 0UL)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    /* Checks if input address are valid */
    if ((Cy_Flash_WorkBoundsCheck((uint32_t)config->addrToBeChecked) == CY_FLASH_OUT_OF_BOUNDS) ||
        (Cy_Flash_WorkBoundsCheck((uint32_t)config->addrToBeChecked + config->numOfWordsToBeChecked*4UL - 1UL) == CY_FLASH_OUT_OF_BOUNDS))
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }

    /* Prepares arguments to be passed to SROM API */
    un_srom_api_args_t apiArgs = {{ 0UL }};
    apiArgs.BlankCheck.arg0.opcode = (uint32_t)CY_SROM_OP_FLASH_BLANK_CHECK;
    apiArgs.BlankCheck.arg1.addrToBeChecked = (uint32_t)config->addrToBeChecked;
    apiArgs.BlankCheck.arg2.numOfWordsToBeChecked = (config->numOfWordsToBeChecked - 1UL);

    /* Tries to acquire the IPC structure and pass the arguments to SROM API */
    if(block == CY_FLASH_DRIVER_BLOCKING)
    {
        /* Call SROM API with blocking mode */
        un_srom_api_resps_t apiResp = {{ 0UL }};
        cy_en_srom_driver_status_t sromDrvStatus;
        sromDrvStatus = Cy_Srom_CallApi(&apiArgs, &apiResp);
        if(sromDrvStatus == CY_SROM_DR_IPC_BUSY)
        {
            return CY_FLASH_DRV_IPC_BUSY;
        }
        else if(sromDrvStatus == CY_SROM_DR_TIMEOUT)
        {
            return CY_FLASH_DRV_SROM_API_TIMEOUT;
        }
        else if(sromDrvStatus == CY_SROM_DR_API_UNKNOWN)
        {
            return CY_FLASH_DRV_ERR_UNC;
        }
        else
        {
            /* Process response message from API */
            cy_en_flashdrv_status_t result;
            result = Cy_Flash_ProcessOpcode(apiResp.resp[0]);
            return result;
        }
    }
    else
    {
        g_non_block_context = (uint8_t)FLASHC_FM_CTL_ECT_STATUS_BLANK_CHECK_WORK_Msk;
        /* Send message by IPC */
        cy_en_srom_driver_status_t status = Cy_Srom_CallApi_NonBlock(&apiArgs);
        if (status != CY_SROM_DR_SUCCEEDED)
        {
            /* The IPC structure is already locked by another process */
            return CY_FLASH_DRV_IPC_BUSY;
        }
        return CY_FLASH_DRV_SUCCESS;
    }
}

/*******************************************************************************
* Function Name: Cy_Flashc_InjectECC
****************************************************************************//**
*
* This function enables ECC injection and sets the address where a parity will be injected
* and the parity value.
* Reports success or a reason for failure.
*
* region An indicator which region (Code/Work/Cache) ECC parity will be injected to.
* This parameter is defined by the cy_en_region_t
* in group_flash_macro macro.
*
* address The address where ECC parity will be injected.
*
* parity The parity value which will be injected.
*
* Returns the status of the Flash operation (see cy_en_flashdrv_status_t).
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flashc_InjectECC(cy_en_region_t region, uint32_t address, uint8_t parity)
{
    cy_en_flashdrv_status_t result =CY_FLASH_DRV_SUCCESS;

    switch(region)
    {
    case CY_FLASH_MAIN_REGION:
        if (Cy_Flash_MainBoundsCheck(address) == CY_FLASH_OUT_OF_BOUNDS)
        {
                return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
        }
        FLASHC_FLASH_CTL |= _VAL2FLD(FLASHC_FLASH_CTL_MAIN_ECC_INJ_EN, 1U);
        FLASHC_ECC_CTL = (_VAL2FLD(FLASHC_ECC_CTL_WORD_ADDR, address) |
                         _VAL2FLD(FLASHC_ECC_CTL_PARITY, parity ));
        break;
    case CY_FLASH_WORK_REGION:
        if (Cy_Flash_WorkBoundsCheck(address) == CY_FLASH_OUT_OF_BOUNDS)
        {
            return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
        }
        FLASHC_FLASH_CTL |= _VAL2FLD(FLASHC_FLASH_CTL_WORK_ECC_INJ_EN, 1U);
        FLASHC_ECC_CTL = (_VAL2FLD(FLASHC_ECC_CTL_WORD_ADDR, address) |
                         _VAL2FLD(FLASHC_ECC_CTL_PARITY, parity ));
        break;
    case CY_FLASH_CA_CM0P_REGION:
        if (Cy_Flash_MainBoundsCheck(address) == CY_FLASH_OUT_OF_BOUNDS)
        {
                return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
        }
        FLASHC_FLASH_CTL |= _VAL2FLD(FLASHC_CM0_CA_CTL0_RAM_ECC_INJ_EN, 1U);
        FLASHC_ECC_CTL = (_VAL2FLD(FLASHC_ECC_CTL_WORD_ADDR, address) |
                         _VAL2FLD(FLASHC_ECC_CTL_PARITY, parity ));
        break;
    default:
        // Default case. Nothing to do.
        break;
    }

    return result;
}

/*******************************************************************************
* Function Name: Cy_Flash_OperationStatus
****************************************************************************//**
*
* Checks the status of the Flash Operation, and returns it.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_OperationStatus(void)
{
    un_srom_api_resps_t resp = {{ 0UL }};
    if(0UL != (FLASHC_FM_CTL_ECT_FLASH_STATUS & g_non_block_context))
    {
        return CY_FLASH_DRV_OPERATION_STARTED;
    }
    else
    {
        g_non_block_context = 0;
        cy_en_srom_api_status_t status = Cy_Srom_GetApiResponse(&resp);
        if(CY_SROM_STATUS_SUCCESS == status)
        {
            return Cy_Flash_ProcessOpcode(resp.resp[0]);
        }
        else
        {
            return CY_FLASH_DRV_ERR_UNC;
        }

    }
}

/*******************************************************************************
* Function Name: Cy_Flash_StartWrite
****************************************************************************//**
*
* Starts programming the flash row with
* the input data. Returns immediately and reports a successful start
* or reason for failure. Reports a \ref CY_FLASH_DRV_IPC_BUSY error
* in the case when another process is writing to flash. User
* firmware should not enter the Hibernate or Deep-Sleep mode until
* flash Write is complete. The Flash operation is allowed in Sleep mode.
* During the flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, the low-voltage
* detect circuits should be configured to generate an interrupt instead of a reset.
* Otherwise, portions of flash may undergo unexpected changes.
* \note Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
*
* rowAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* data The pointer to the data to be written to flash. The size
* of the data array must be equal to the flash row size. The flash row size for
* the selected device is defined by the \ref CY_FLASH_SIZEOF_ROW macro. Refer to
* the device datasheet for the details.
*
* Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_StartWrite(uint32_t rowAddr, const uint32_t* data)
{
    cy_en_flashdrv_status_t result = CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    uint32_t prog_length = (uint32_t)ADDRESS_LENGTH_32_BIT;
    uint32_t data_length = (uint32_t)DATA_LENGTH_32_BIT;
    if (data == NULL)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    else
    {

        cy_stc_flash_programrow_config_t flash_programrow_config =
        {
            .destAddr  =   (const uint32_t *)rowAddr,
            .dataAddr  =   (const uint32_t *)data,
            .blocking  =   CY_FLASH_PROGRAMROW_NON_BLOCKING,
            .skipBC    =   CY_FLASH_PROGRAMROW_SKIP_BLANK_CHECK,
            .dataSize  =   CY_FLASH_PROGRAMROW_DATA_SIZE_32BIT,
            .dataLoc   =   CY_FLASH_PROGRAMROW_DATA_LOCATION_SRAM,
            .intrMask  =   CY_FLASH_PROGRAMROW_SET_INTR_MASK,
        };
        /* Checks whether the input parameters are valid */
        if(Cy_Flash_WorkBoundsCheck(rowAddr) == CY_FLASH_IN_BOUNDS)
        {
            flash_programrow_config.dataSize = CY_FLASH_PROGRAMROW_DATA_SIZE_32BIT;
        }
        else if(Cy_Flash_MainBoundsCheck(rowAddr) == CY_FLASH_IN_BOUNDS)
        {
            prog_length = ADDRESS_LENGTH_256_BIT;
            data_length = DATA_LENGTH_256_BIT;
            flash_programrow_config.dataSize = CY_FLASH_PROGRAMROW_DATA_SIZE_256BIT;
        }
        else
        {
            /* non-empty terminating "else" statement */
        }

        for(uint32_t i_addr = rowAddr;  i_addr < rowAddr + CY_FLASH_SIZEOF_ROW; i_addr+=prog_length)
        {
            flash_programrow_config.destAddr = (const uint32_t *)i_addr;
            flash_programrow_config.dataAddr = (const uint32_t *)(data);
            g_non_block_context = (uint8_t)(FLASHC_FM_CTL_ECT_STATUS_PGM_WORK_Msk | FLASHC_FM_CTL_ECT_STATUS_PGM_CODE_Msk);
            result = Cy_Flash_Program(&flash_programrow_config,CY_FLASH_DRIVER_NON_BLOCKING);
            if(result == CY_FLASH_DRV_OPERATION_STARTED)
            {
                while((Cy_Flash_IsOperationComplete() != CY_FLASH_DRV_SUCCESS))
                {
                }
                data+=data_length;
            }
            else
            {
                return result;
            }
        }
    }
    return CY_FLASH_DRV_OPERATION_STARTED;
}

/*******************************************************************************
* Function Name: Cy_Flash_StartEraseSector
****************************************************************************//**
*
* Starts erasing a sector of flash. Returns immediately
* and reports a successful start or reason for failure.
* Reports a CY_FLASH_DRV_IPC_BUSY error in the case when IPC structure is locked
* by another process. User firmware should not enter the Hibernate or Deep Sleep mode until
* flash Erase is complete. The Flash operation is allowed in Sleep mode.
* During the flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, the low-voltage
* detect circuits should be configured to generate an interrupt instead of a reset.
* Otherwise, portions of flash may undergo unexpected changes.
* Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
*
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_StartEraseSector(uint32_t sectorAddr)
{
    cy_en_flashdrv_status_t result = CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;

    /* Checks whether the input parameters are valid */
    if(Cy_Flash_BoundsCheck((uint32_t)(sectorAddr)) == CY_FLASH_OUT_OF_BOUNDS)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    cy_stc_flash_erasesector_config_t flash_erasesector_config =
    {
        .sectorAddr  =  (const uint32_t *)sectorAddr,
        .blocking    =  CY_FLASH_ERASESECTOR_NON_BLOCKING,
        .intrMask    =  CY_FLASH_ERASESECTOR_SET_INTR_MASK,
    };
    g_non_block_context = (uint8_t)(FLASHC_FM_CTL_ECT_STATUS_ERASE_CODE_Msk | FLASHC_FM_CTL_ECT_STATUS_ERASE_WORK_Msk);
    result = Cy_Flash_EraseSector_Ext(&flash_erasesector_config, CY_FLASH_DRIVER_NON_BLOCKING);
    if(result != CY_FLASH_DRV_SUCCESS)
    {
        return result;
    }

    return CY_FLASH_DRV_OPERATION_STARTED;
}

/*******************************************************************************
* Function Name: Cy_Flash_ProgramRow
****************************************************************************//**
*
* This function writes an array of data to a single row of flash. Reports
* success or a reason for failure. Does not return until the Program operation
* is complete.
* Returns immediately and reports a \ref CY_FLASH_DRV_IPC_BUSY error in the case
* when another process is writing to flash. User firmware should not enter the
* Hibernate or Deep-sleep mode until flash Write is complete. The Flash operation
* is allowed in Sleep mode. During the Flash operation, the device should not be
* reset, including the XRES pin, a software reset, and watchdog reset sources.
* Also, low-voltage detect circuits should be configured to generate an interrupt
* instead of a reset. Otherwise, portions of flash may undergo unexpected
* changes.\n
* Before calling this function, the target flash region must be erased by
* the StartErase/EraseRow function.\n
* Data to be programmed must be located in the SRAM memory region.
* \note Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_ProgramRow(uint32_t rowAddr, const uint32_t* data)
{
    cy_en_flashdrv_status_t result = CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    uint32_t prog_length = (uint32_t)ADDRESS_LENGTH_32_BIT;
    uint32_t data_length = (uint32_t)DATA_LENGTH_32_BIT;

    if (data == NULL)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    cy_stc_flash_programrow_config_t flash_programrow_config =
    {
        .destAddr  =   (const uint32_t *)rowAddr,
        .dataAddr  =   (const uint32_t *)data,
        .blocking  =   CY_FLASH_PROGRAMROW_BLOCKING,
        .skipBC    =   CY_FLASH_PROGRAMROW_SKIP_BLANK_CHECK,
        .dataSize  =   CY_FLASH_PROGRAMROW_DATA_SIZE_32BIT,
        .dataLoc   =   CY_FLASH_PROGRAMROW_DATA_LOCATION_SRAM,
        .intrMask  =   CY_FLASH_PROGRAMROW_NOT_SET_INTR_MASK,
    };
    /* Checks whether the input parameters are valid */
    if(Cy_Flash_WorkBoundsCheck(rowAddr) == CY_FLASH_IN_BOUNDS)
    {
        flash_programrow_config.dataSize = CY_FLASH_PROGRAMROW_DATA_SIZE_32BIT;
    }
    else if(Cy_Flash_MainBoundsCheck(rowAddr) == CY_FLASH_IN_BOUNDS)
    {
        prog_length = ADDRESS_LENGTH_256_BIT;
        data_length = DATA_LENGTH_256_BIT;
        flash_programrow_config.dataSize = CY_FLASH_PROGRAMROW_DATA_SIZE_256BIT;
    }
    else
    {
        /* empty else statement. */
    }
    for(uint32_t i_addr = rowAddr;  i_addr < rowAddr + CY_FLASH_SIZEOF_ROW; i_addr+=prog_length)
    {
        flash_programrow_config.destAddr = (const uint32_t *)i_addr;
        flash_programrow_config.dataAddr = (const uint32_t *)(data);
        result = Cy_Flash_Program(&flash_programrow_config, CY_FLASH_DRIVER_BLOCKING);
        if(result != CY_FLASH_DRV_SUCCESS)
        {
            break;
        }
        data+=data_length;
    }
    return (result);
}

/*******************************************************************************
* Function Name: Cy_Flash_EraseSector
****************************************************************************//**
*
* This function erases a sector of flash. Reports success or
* a reason for failure. Does not return until the Erase operation is
* complete. Returns immediately and reports a \ref CY_FLASH_DRV_IPC_BUSY error in
* the case when another process is writing to flash or erasing the row.
* User firmware should not enter the Hibernate or Deep Sleep mode until flash Erase
* is complete. The Flash operation is allowed in Sleep mode.
* During the Flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, low-voltage
* detect circuits should be configured to generate an interrupt instead of a
* reset. Otherwise, portions of flash may undergo unexpected changes.
*
* \param sectorAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseSector(uint32_t sectorAddr)
{
    cy_en_flashdrv_status_t result = CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;

    /* Checks whether the input parameters are valid */
    if(Cy_Flash_BoundsCheck((uint32_t)(sectorAddr)) == CY_FLASH_OUT_OF_BOUNDS)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    cy_stc_flash_erasesector_config_t flash_erasesector_config =
    {
        .sectorAddr  =  (const uint32_t *)sectorAddr,
        .blocking    =  CY_FLASH_ERASESECTOR_BLOCKING,
        .intrMask    =  CY_FLASH_ERASESECTOR_NOT_SET_INTR_MASK,
    };
    result = Cy_Flash_EraseSector_Ext(&flash_erasesector_config, CY_FLASH_DRIVER_BLOCKING);

    return (result);
}

/*******************************************************************************
* Function Name: Cy_Flash_CalculateHash
****************************************************************************//**
*
* Returns a hash value of the specified region of flash.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_CalculateHash(const uint32_t* data, uint32_t numberOfBytes, uint32_t* hashPtr)
{
    cy_en_flashdrv_status_t result = CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;

    /* Checks whether the input parameters are valid */
    if ((data == NULL) || (numberOfBytes == 0UL) || (hashPtr == NULL))
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    cy_stc_flash_computehash_config_t flash_computehash_config =
    {
        .startAddr =  (const uint32_t *)data,
        .numOfByte =  numberOfBytes,
        .type      =  CY_FLASH_COMPUTEHASH_BASIC,
    };
    result = Cy_Flash_CalculateHash_Ext(&flash_computehash_config, hashPtr);

    return (result);
}

/*******************************************************************************
* Function Name: Cy_Flash_RowChecksum
****************************************************************************//**
*
* Returns a checksum value of the specified flash row.
*
* \note Now Cy_Flash_RowChecksum() requires the row <b>address</b> (rowAddr)
*       as a parameter. In previous versions of the driver, this function used
*       the row <b>number</b> (rowNum) for this parameter.
*
* rowAddr The address of the flash row.
*
* checksumPtr The pointer to the address where checksum is to be stored
*
* Returns the status of the Flash operation.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_RowChecksum(uint32_t rowAddr, uint32_t* checksumPtr)
{
    cy_en_flashdrv_status_t result = CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    uint8_t rowID = 0;
    cy_en_flash_checksum_bank_t bank = CY_FLASH_CHECKSUM_BANK0;
    cy_en_flash_checksum_region_t region = CY_FLASH_CHECKSUM_MAIN;

    /* Checks whether the input parameters are valid */
    if ((Cy_Flash_BoundsCheck(rowAddr)== CY_FLASH_OUT_OF_BOUNDS) || (checksumPtr == NULL))
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    if (CY_FLASH_DRV_SUCCESS == Cy_Flash_GetRowDetails(rowAddr,&rowID, &bank, &region))
    {
        cy_stc_flash_checksum_config_t flash_computechecksum_config =
        {
            .rowId      =  rowID,
            .bank       =  bank,
            .whole      =  CY_FLASH_CHECKSUM_PAGE,
            .region     = region,
        };
        result = Cy_Flash_Checksum(&flash_computechecksum_config, checksumPtr);
    }

    return (result);
}

/*******************************************************************************
* Function Name: Cy_Flash_GetRowDetails
****************************************************************************//**
*
* Returns flash region ID, Bank and row number of the Flash address.
*******************************************************************************/
static cy_en_flashdrv_status_t Cy_Flash_GetRowDetails(uint32_t rowAddr, uint8_t *rowID, cy_en_flash_checksum_bank_t *bank, cy_en_flash_checksum_region_t *region)
{
    cy_en_flashdrv_status_t result = CY_FLASH_DRV_SUCCESS;
    if (Cy_Flash_WorkBoundsCheck(rowAddr) == CY_FLASH_OUT_OF_BOUNDS)
    {
        return CY_FLASH_DRV_INVALID_INPUT_PARAMETERS;
    }
    cy_en_bankmode_t bankmode = Cy_Flashc_GetMainBankMode();
    if(bankmode == CY_FLASH_SINGLE_BANK_MODE)
    {

        if ((rowAddr >= CY_WFLASH_LG_SBM_TOP) && (rowAddr < CY_WFLASH_SM_SBM_END))
        {
            *rowID = (uint8_t)((CY_FLASH_REGION_ID_WFLASH << CY_FLASH_REGION_ID_SHIFT) |
                     ((rowAddr - CY_WFLASH_LG_SBM_TOP) / CY_FLASH_SIZEOF_ROW));
            *bank = CY_FLASH_CHECKSUM_BANK0;
            *region = CY_FLASH_CHECKSUM_WORK;
        }
        else if ((rowAddr >= CY_FLASH_LG_SBM_TOP) && (rowAddr < CY_FLASH_SM_SBM_END))
        {
            *rowID = (uint8_t)((CY_FLASH_REGION_ID_WFLASH << CY_FLASH_REGION_ID_SHIFT) |
                     ((rowAddr - CY_WFLASH_LG_SBM_TOP) / CY_FLASH_SIZEOF_ROW));
            *bank = CY_FLASH_CHECKSUM_BANK0;
            *region = CY_FLASH_CHECKSUM_MAIN;
        }
        else
        {
            /* rowAddr oout of bounds. */
        }
    }
    else
    {
        if ((rowAddr >= CY_WFLASH_LG_DBM0_TOP) && (rowAddr < CY_WFLASH_SM_DBM0_END))
        {
            *rowID = (uint8_t)((CY_FLASH_REGION_ID_WFLASH << CY_FLASH_REGION_ID_SHIFT) |
                     ((rowAddr - CY_WFLASH_LG_DBM0_TOP) / CY_FLASH_SIZEOF_ROW));
            *bank = CY_FLASH_CHECKSUM_BANK0;
            *region = CY_FLASH_CHECKSUM_WORK;
        }
        else if ((rowAddr >= CY_WFLASH_LG_DBM1_TOP) && (rowAddr < CY_WFLASH_SM_DBM1_END))
        {
            *rowID = (uint8_t)((CY_FLASH_REGION_ID_WFLASH << CY_FLASH_REGION_ID_SHIFT) |
                     ((rowAddr - CY_WFLASH_LG_SBM_TOP) / CY_FLASH_SIZEOF_ROW));
            *bank = CY_FLASH_CHECKSUM_BANK1;
            *region = CY_FLASH_CHECKSUM_WORK;
        }
        else if ((rowAddr >= CY_FLASH_LG_DBM0_TOP) && (rowAddr < CY_FLASH_SM_DBM0_END))
        {
            *rowID = (uint8_t)((CY_FLASH_REGION_ID_MAIN << CY_FLASH_REGION_ID_SHIFT) |
                     ((rowAddr - CY_FLASH_LG_DBM0_TOP) / CY_FLASH_SIZEOF_ROW));
            *bank = CY_FLASH_CHECKSUM_BANK0;
            *region = CY_FLASH_CHECKSUM_MAIN;
        }
        else if ((rowAddr >= CY_FLASH_LG_DBM1_TOP) && (rowAddr < CY_FLASH_SM_DBM1_END))
        {
            *rowID = (uint8_t)((CY_FLASH_REGION_ID_MAIN << CY_FLASH_REGION_ID_SHIFT) |
                     ((rowAddr - CY_FLASH_LG_DBM1_TOP) / CY_FLASH_SIZEOF_ROW));
            *bank = CY_FLASH_CHECKSUM_BANK1;
            *region = CY_FLASH_CHECKSUM_MAIN;
        }
        else
        {
            /* rowAddr oout of bounds. */
        }

    }

    return (result);
}

/*******************************************************************************
* Function Name: Cy_Flash_Init
****************************************************************************//**
*
* Initiates all needed prerequisites to support flash erase/write.
* Should be called from each core.
*
* This function is called in the SystemInit() function, for proper flash write
* and erase operations. If the default startup file is not used, or the function
* SystemInit() is not called in your project, ensure to perform the following steps
* before any flash or EmEEPROM write/erase operations:
*
*******************************************************************************/
void Cy_Flash_Init(void)
{
    /* In Blocking mode the calling function get's the response and sends it to the user.
     * In Non blocking mode user will call operation status and gets the response in return.
     * There is no need for the driver to handle error in the interrupt handler.
     * Error needs to be passed to the user.
     */
    Cy_Srom_SetResponseHandler(NULL);
}

/*******************************************************************************
* Function Name: Cy_Flash_IsOperationComplete
****************************************************************************//**
*
* Reports a successful operation result, reason of failure or busy status
* ( CY_FLASH_DRV_OPCODE_BUSY ).
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_IsOperationComplete(void)
{
    return (Cy_Flash_OperationStatus());
}


/*******************************************************************************
* Function Name: Cy_Flashc_MainWriteEnable
****************************************************************************//**
*
* Enable writing main flash
*
*******************************************************************************/
void Cy_Flashc_MainWriteEnable(void)
{
    FLASHC_FM_CTL_ECT_MAIN_FLASH_SAFETY |= FLASHC_FM_CTL_ECT_MAIN_FLASH_SAFETY_MAINFLASHWRITEENABLE_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_MainWriteDisable
****************************************************************************//**
*
* Disable writing main flash
*
*******************************************************************************/
void Cy_Flashc_MainWriteDisable(void)
{
    FLASHC_FM_CTL_ECT_MAIN_FLASH_SAFETY &= (uint32_t) ~FLASHC_FM_CTL_ECT_MAIN_FLASH_SAFETY_MAINFLASHWRITEENABLE_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_WorkWriteEnable
****************************************************************************//**
*
* Enable writing work flash
*
*******************************************************************************/
void Cy_Flashc_WorkWriteEnable(void)
{
    FLASHC_FM_CTL_ECT_WORK_FLASH_SAFETY |= FLASHC_FM_CTL_ECT_WORK_FLASH_SAFETY_WORKFLASHWRITEENABLE_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_WorkWriteDisable
****************************************************************************//**
*
* Disable writing work flash
*
*******************************************************************************/
void Cy_Flashc_WorkWriteDisable(void)
{
    FLASHC_FM_CTL_ECT_WORK_FLASH_SAFETY &= (uint32_t) ~FLASHC_FM_CTL_ECT_WORK_FLASH_SAFETY_WORKFLASHWRITEENABLE_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_WorkECCEnable
****************************************************************************//**
*
* Enables ECC for work flash
*
*******************************************************************************/
void Cy_Flashc_WorkECCEnable(void)
{
    FLASHC_FLASH_CTL |= FLASHC_FLASH_CTL_WORK_ECC_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_WorkECCDisable
****************************************************************************//**
*
* Disables ECC for work flash
*
*******************************************************************************/
void Cy_Flashc_WorkECCDisable(void)
{
    FLASHC_FLASH_CTL &= (uint32_t) ~FLASHC_FLASH_CTL_WORK_ECC_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_MainECCEnable
****************************************************************************//**
*
* Enables ECC for main flash
*
*******************************************************************************/
void Cy_Flashc_MainECCEnable(void)
{
    FLASHC_FLASH_CTL |= FLASHC_FLASH_CTL_MAIN_ECC_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_MainECCDisable
****************************************************************************//**
*
* Disables ECC for main flash
*
*******************************************************************************/
void Cy_Flashc_MainECCDisable(void)
{
    FLASHC_FLASH_CTL &= (uint32_t) ~FLASHC_FLASH_CTL_MAIN_ECC_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_Flashc_SetWorkBankMode
****************************************************************************//**
*
* Sets bank mode for work flash
*
* mode bank mode to be set
*
*******************************************************************************/
void Cy_Flashc_SetWorkBankMode(cy_en_bankmode_t mode)
{
    if(CY_FLASH_DUAL_BANK_MODE == mode)
    {
        FLASHC_FLASH_CTL |= FLASHC_FLASH_CTL_WORK_BANK_MODE_Msk;
    }
    else
    {
        FLASHC_FLASH_CTL &= (uint32_t) ~FLASHC_FLASH_CTL_WORK_BANK_MODE_Msk;
    }
}

/*******************************************************************************
* Function Name: Cy_Flashc_GetWorkBankMode
****************************************************************************//**
*
* Gets current bank mode for work flash
*
*******************************************************************************/
cy_en_bankmode_t Cy_Flashc_GetWorkBankMode(void)
{
   uint32_t bank_mode = _FLD2VAL(FLASHC_FLASH_CTL_WORK_BANK_MODE, FLASHC_FLASH_CTL);
   if(bank_mode == 0UL)
    {
        return CY_FLASH_SINGLE_BANK_MODE;
    }
    else
    {
        return CY_FLASH_DUAL_BANK_MODE;
    }
}

/*******************************************************************************
* Function Name: Cy_Flashc_SetMainBankMode
****************************************************************************//**
*
*  Sets bank mode for main flash
*
*  mode bank mode to be set
*
*******************************************************************************/
void Cy_Flashc_SetMainBankMode(cy_en_bankmode_t mode)
{
   if(CY_FLASH_DUAL_BANK_MODE == mode)
    {
        FLASHC_FLASH_CTL |= FLASHC_FLASH_CTL_MAIN_BANK_MODE_Msk;
    }
    else
    {
        FLASHC_FLASH_CTL &= (uint32_t) ~FLASHC_FLASH_CTL_MAIN_BANK_MODE_Msk;
    }
}

/*******************************************************************************
* Function Name: Cy_Flashc_GetMainBankMode
****************************************************************************//**
*
*  Gets current bank mode for main flash
*
*******************************************************************************/
cy_en_bankmode_t Cy_Flashc_GetMainBankMode(void)
{
    uint32_t bank_mode = _FLD2VAL(FLASHC_FLASH_CTL_MAIN_BANK_MODE, FLASHC_FLASH_CTL);
    if(bank_mode == 0UL)
    {
        return CY_FLASH_SINGLE_BANK_MODE;
    }
    else
    {
        return CY_FLASH_DUAL_BANK_MODE;
    }
}


#endif // defined(CY_IP_MXFLASHC_VERSION_ECT)

/* [] END OF FILE */
