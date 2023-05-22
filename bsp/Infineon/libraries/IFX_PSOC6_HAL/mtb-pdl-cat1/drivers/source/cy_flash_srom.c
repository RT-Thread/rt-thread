/***************************************************************************//**
* \file cy_flash_srom.c
* \version 3.70
*
* \brief
* Provides functions for controlling the SROM APIs.
*
********************************************************************************
* \copyright
* Copyright 2021, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cy_device.h"
#if defined (CY_IP_M7CPUSS)
#include "cy_flash_srom.h"
#include "cy_ipc_drv.h"

CY_SECTION_SHAREDMEM
CY_ALIGN(32) static un_srom_api_scrach_sram_t g_scratch; // This must locate on SRAM.
CY_SECTION_SHAREDMEM
CY_ALIGN(32) static un_srom_api_args_2_t      g_scratch2; // This must locate on SRAM.
static uint32_t message[2];
static cy_srom_handler gp_srom_resp_handler = NULL;

static void Cy_Srom_ISR_ResponseIPC(void);
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
static uint32_t Cy_Srom_Get_DataSize(cy_en_programrow_datasize_t size);
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
/*******************************************************************************
* Function Name: Cy_Srom_CallApi
****************************************************************************//**
*
* This function calls SROM API. CPU will wait for API completed inside this
* function by checking IPC released. Even after checking 0x00FFFFFF times, if it
* is still not released, this function will return timeout status.
* If IPC was busy when this function was called, it would return busy status
* immediately.
* If SROM API returned error status, this function would return error status.
* But actual message is still in first word of memory pointed by second input
* parameter "resp" (if not NULL).
* All messages will be passed via SRAM pointed to scratch address. The SRAM area
* is reserved in this file as a variable named "g_scratch".
* This function is not re-entrant.
*
* \param params
* Pointer to memory which contains SROM API arguments. The contents of arguments
* will be copied to "g_scratch". \ref un_srom_api_args_t
*
* \param resp
* Pointer to memory which SROM API response message will be copied to. Even if
* this function return error status, response message will be copied to the
* memory. If pointer is NULL, response will not be copied \ref un_srom_api_resps_t
*
* \return
* \ref cy_en_srom_driver_status_t
*
*******************************************************************************/
cy_en_srom_driver_status_t Cy_Srom_CallApi(const un_srom_api_args_t* params, un_srom_api_resps_t* resp)
{
    if(params == NULL)
    {
        return CY_SROM_DR_INVALID_INPUT;
    }

    IPC_STRUCT_Type* syscall_ipc_struct = Cy_IPC_Drv_GetIpcBaseAddress((uint32_t)CY_IPC_CHAN_SYSCALL);
    uint32_t timeOut = 0x0FFFFFFFUL;

    // Copy input contents to SRAM reserved
    g_scratch.args = *params;

    // Make Bit[0] to 0, it indicates all arguments are passed through scratch address
    g_scratch.u32[0] = g_scratch.u32[0] & 0xFFFFFFFEUL;

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    uint32_t size_in_bytes = Cy_Srom_Get_DataSize((cy_en_programrow_datasize_t)(params->ProgramRow.arg1.dataSize));
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 3, \
'Checked manually. Intentional expression The object pointer of type non "uint32_t *" is cast to type "uint32_t *".');

    SCB_CleanDCache_by_Addr((uint32_t*)&g_scratch, (int32_t)sizeof(g_scratch));
    SCB_CleanDCache_by_Addr((uint32_t*)params->ProgramRow.arg3.srcAddr, (int32_t)size_in_bytes);

    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    // Send message by IPC
    if (Cy_IPC_Drv_SendMsgWord(syscall_ipc_struct, CY_SROM_DR_IPC_NOTIFY_STRUCT, (uint32_t)&g_scratch) != CY_IPC_DRV_SUCCESS)
    {
        // The IPC structure is already locked by another process
        return CY_SROM_DR_IPC_BUSY;
    }
    while(true)
    {
        // Checks if the IPC structure is not locked
        if (Cy_IPC_Drv_IsLockAcquired(syscall_ipc_struct) == false)
        {
            // The result of SROM API calling is in the SRAM reserved.
            // Copy the contents to the memory pointed by input pointer
            if(resp != NULL)
            {
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
                CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 1, \
'Checked manually. Intentional expression The object pointer of type non "uint32_t *" is cast to type "uint32_t *".');
                SCB_InvalidateDCache_by_Addr ((uint32_t*)&g_scratch, (int32_t)sizeof(g_scratch));
                SCB_InvalidateDCache_by_Addr ((uint32_t*)params->ProgramRow.arg2.dstAddr, (int32_t)size_in_bytes);
                CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
                *resp = g_scratch.resps;
            }
            break;
        }

        // Decrement time out counter value
        timeOut--;

        // If time out counter is "0" return time out status
        if(timeOut == 0U)
        {
            return CY_SROM_DR_TIMEOUT;
        }
    }

    if(Cy_Srom_GetResponseType() == CY_SROM_RESPONSE_FAIL)
    {
        // If the SROM API returned an error in the scratch RAM, return error
        return CY_SROM_DR_API_ERROR;
    }
    else if(Cy_Srom_GetResponseType() == CY_SROM_RESPONSE_SUCCESS)
    {
        // If the SROM API returned "OK", return success
        return CY_SROM_DR_SUCCEEDED;
    }
    else
    {
        // Return unknown status
        return CY_SROM_DR_API_UNKNOWN;
    }
}

/*******************************************************************************
* Function Name: Cy_Srom_CallApi_NonBlock
****************************************************************************//**
*
* This function calls SROM API. CPU "won't" wait for API completed inside this
* function by checking IPC released.
* If IPC was busy when this function was called, it would return busy status
* immediately.
* Please call "Cy_Srom_Get_Api_Response" to retrieve API response.
* All messages will be passed via SRAM pointed to scratch address. The SRAM area
* is reserved in this file as a variable named "g_scratch".
* This function is not re-entrant.
* Once user called this function, this function and also "Cy_Srom_CallApi"
* must not called until SROM API finished.
*
* \param params
* Pointer to memory which contains SROM API arguments. The contents of arguments
* will be copied to "g_scratch". \ref un_srom_api_args_t
*
* \return
* \ref cy_en_srom_driver_status_t
*
*******************************************************************************/
cy_en_srom_driver_status_t Cy_Srom_CallApi_NonBlock(const un_srom_api_args_t* params)
{
    if(params == NULL)
    {
        return CY_SROM_DR_INVALID_INPUT;
    }
    IPC_STRUCT_Type* syscall_ipc_struct = Cy_IPC_Drv_GetIpcBaseAddress((uint32_t)CY_IPC_CHAN_SYSCALL);
    uint32_t timeOut = 0x0FFFFFFFUL;

    // Copy input contents to SRAM reserved
    g_scratch.args = *params;

    // Make Bit[0] to 0, it indicates all arguments are passed through scratch address
    g_scratch.u32[0] = g_scratch.u32[0] & 0xFFFFFFFEUL;

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    uint32_t size_in_bytes = Cy_Srom_Get_DataSize((cy_en_programrow_datasize_t)(params->ProgramRow.arg1.dataSize));
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 3, \
'Checked manually. Intentional expression The object pointer of type non "uint32_t *" is cast to type "uint32_t *".');
    SCB_CleanDCache_by_Addr((uint32_t*)&g_scratch, (int32_t)sizeof(g_scratch));
    SCB_CleanDCache_by_Addr((uint32_t*)params->ProgramRow.arg3.srcAddr, (int32_t)size_in_bytes);

    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    // Send message by IPC
    if (Cy_IPC_Drv_SendMsgWord(syscall_ipc_struct, CY_SROM_DR_IPC_NOTIFY_STRUCT, (uint32_t)&g_scratch) != CY_IPC_DRV_SUCCESS)
    {
        // The IPC structure is already locked by another process
        return CY_SROM_DR_IPC_BUSY;
    }
    while(true)
   {
       // Checks if the IPC structure is not locked
       if (Cy_IPC_Drv_IsLockAcquired(syscall_ipc_struct) == false)
       {
           // The result of SROM API calling is in the SRAM reserved.
           // Copy the contents to the memory pointed by input pointer
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
                CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 1, \
'Checked manually. Intentional expression The object pointer of type non "uint32_t *" is cast to type "uint32_t *".');
                SCB_InvalidateDCache_by_Addr ((uint32_t*)params->ProgramRow.arg2.dstAddr, (int32_t)size_in_bytes);
                CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
           break;
       }
       // Decrement time out counter value
       timeOut--;

       // If time out counter is "0" return time out status
       if(timeOut == 0U)
       {
           return CY_SROM_DR_TIMEOUT;
       }
   }
    // Return succeeded status
    return CY_SROM_DR_SUCCEEDED;
}

/*******************************************************************************
* Function Name: Cy_Srom_CallApi_2
****************************************************************************//**
*
* This function calls SROM API which need also IPC DATA1. Other is same as
* "Cy_SROM_CallApi"
*
* \param params
* Pointer to memory which contains SROM API arguments. The contents of arguments
* will be copied to "g_scratch". \ref un_srom_api_args_t
*
* \param params
* Pointer to memory which contains SROM API arguments 2. The contents of arguments
* will be copied to "g_scratch2". \ref un_srom_api_args_2_t
*
* \param resp
* Pointer to memory which SROM API response message will be copied to. Even if
* this function return error status, response message will be copied to the
* memory. If pointer is NULL, response will not be copied \ref un_srom_api_resps_t
*
* \return
* \ref cy_en_srom_driver_status_t
*
*******************************************************************************/
cy_en_srom_driver_status_t Cy_Srom_CallApi_2(const un_srom_api_args_t* params, const un_srom_api_args_2_t* params2, un_srom_api_resps_t* resp)
{
    if((params == NULL) || (params2 == NULL))
    {
        return CY_SROM_DR_INVALID_INPUT;
    }
//    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.1','Checked manually. Intentional Non boolean type is interpreted as boolean.');
    IPC_STRUCT_Type* syscall_ipc_struct = Cy_IPC_Drv_GetIpcBaseAddress((uint32_t)CY_IPC_CHAN_SYSCALL);
    uint32_t timeOut = 0x00FFFFFFUL;

    // Copy input contents to SRAM reserved
    g_scratch.args = *params;
    g_scratch2     = *params2;

    // Make Bit[0] to 0, it indicates all arguments are passed through scratch address
    g_scratch.u32[0]  = g_scratch.u32[0]  & 0xFFFFFFFEUL;
    g_scratch2.arg[0] = g_scratch2.arg[0] & 0xFFFFFFFEUL;


    message[0] = (uint32_t)&g_scratch;
    message[1] = (uint32_t)&g_scratch2;
    // Send message by IPC
    if (Cy_IPC_Drv_SendMsgDWord(syscall_ipc_struct, CY_SROM_DR_IPC_NOTIFY_STRUCT, message) != CY_IPC_DRV_SUCCESS)
    {
        // The IPC structure is already locked by another process
        return CY_SROM_DR_IPC_BUSY;
    }
    while(true)
    {
        // Checks if the IPC structure is not locked
        if (Cy_IPC_Drv_IsLockAcquired(syscall_ipc_struct) == false)
        {
            // The result of SROM API calling is in the SRAM reserved.
            // Copy the contents to the memory pointed by input pointer
            if(resp != NULL)
            {
                *resp = g_scratch.resps;
            }
            break;
        }

        // Decrement time out counter value
        timeOut--;

        // If time out counter is "0" return time out status
        if(timeOut == 0u)
        {
            return CY_SROM_DR_TIMEOUT;
        }
    }

    if(Cy_Srom_GetResponseType() == CY_SROM_RESPONSE_FAIL)
    {
        // If the SROM API returned an error in the scratch RAM, return error
        return CY_SROM_DR_API_ERROR;
    }
    else if(Cy_Srom_GetResponseType() == CY_SROM_RESPONSE_SUCCESS)
    {
        // If the SROM API returned "OK", return success
        return CY_SROM_DR_SUCCEEDED;
    }
    else
    {
        // Return unknown status
        return CY_SROM_DR_API_UNKNOWN;
    }
}

/*******************************************************************************
* Function Name: Cy_Srom_CallApi_NonBlock_2
****************************************************************************//**
*
* This function calls SROM API which need also IPC DATA1. Other is same as
* "Cy_SROM_CallApi_NonBlock_2"
*
* \param params
* Pointer to memory which contains SROM API arguments. The contents of arguments
* will be copied to "g_scratch". \ref un_srom_api_args_t
*
* \param params
* Pointer to memory which contains SROM API arguments 2. The contents of arguments
* will be copied to "g_scratch2". \ref un_srom_api_args_2_t
*
* \return
* \ref cy_en_srom_driver_status_t
*
*******************************************************************************/
cy_en_srom_driver_status_t Cy_Srom_CallApi_NonBlock_2(const un_srom_api_args_t* params, const un_srom_api_args_2_t* params2)
{
    if((params == NULL) || (params2 == NULL))
    {
        return CY_SROM_DR_INVALID_INPUT;
    }
//    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.1','Checked manually. Intentional Non boolean type is interpreted as boolean.');
    IPC_STRUCT_Type* syscall_ipc_struct = Cy_IPC_Drv_GetIpcBaseAddress((uint32_t)CY_IPC_CHAN_SYSCALL);

    // Copy input contents to SRAM reserved
    g_scratch.args = *params;
    g_scratch2     = *params2;

    // Make Bit[0] to 0, it indicates all arguments are passed through scratch address
    g_scratch.u32[0]  = g_scratch.u32[0]  & 0xFFFFFFFEUL;
    g_scratch2.arg[0] = g_scratch2.arg[0] & 0xFFFFFFFEUL;

    message[0] = (uint32_t)&g_scratch;
    message[1] = (uint32_t)&g_scratch2;
    // Send message by IPC
    if (Cy_IPC_Drv_SendMsgDWord(syscall_ipc_struct, CY_SROM_DR_IPC_NOTIFY_STRUCT, message) != CY_IPC_DRV_SUCCESS)
    {
        // The IPC structure is already locked by another process
        return CY_SROM_DR_IPC_BUSY;
    }
    // Return succeeded status
    return CY_SROM_DR_SUCCEEDED;
}


/*******************************************************************************
* Function Name: Cy_Srom_GetResponseType
****************************************************************************//**
*
* This function returns status of SROM API response defined by \ref
* cy_en_srom_response_type_t
* Please call this function after "Cy_Srom_CallApi_NonBlock" was called.
*
* \return
* \ref cy_en_srom_response_type_t
*
*******************************************************************************/
cy_en_srom_response_type_t Cy_Srom_GetResponseType(void)
{
    if((g_scratch.u32[0] & 0xF0000000UL) == 0xA0000000UL)
    {
        return CY_SROM_RESPONSE_SUCCESS;
    }
    else if((g_scratch.u32[0] & 0xF0000000UL) == 0xF0000000UL)
    {
        return CY_SROM_RESPONSE_FAIL;
    }
    else
    {
        return CY_SROM_NOT_RESPONSE;
    }
}

/*******************************************************************************
* Function Name: Cy_Srom_Get_Api_Response
****************************************************************************//**
*
* This function returns g_scratch value as a response of SROM API.
* Please call this function after "Cy_Srom_CallApi_NonBlock" was called.
* "resp" is raw response data from SROM API on the other hands, return value
* indicate status of the response data like as invalid, succeeded, or failed.
* (if failed return value is same as resp.u32[0])
*
* \param resp
* Pointer to memory into which SROM API response to be copied if not NULL.
*  \ref un_srom_api_resps_t
*
* \return
* \ref cy_en_srom_api_status_t
*
*******************************************************************************/
cy_en_srom_api_status_t Cy_Srom_GetApiResponse(un_srom_api_resps_t* resp)
{
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 3, \
'Checked manually. Intentional expression The object pointer of type non "uint32_t *" is cast to type "uint32_t *".');
    SCB_InvalidateDCache_by_Addr ((uint32_t*)&g_scratch, (int32_t)sizeof(g_scratch));
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    cy_en_srom_response_type_t type = Cy_Srom_GetResponseType();
    if(type == CY_SROM_NOT_RESPONSE)
    {
        return CY_SROM_STATUS_INVALID;
    }
    else
    {
        if(resp != NULL)
        {
            *resp = g_scratch.resps;
        }

        if(type == CY_SROM_RESPONSE_SUCCESS)
        {
            return CY_SROM_STATUS_SUCCESS;
        }
        else // CY_SROM_RESPONSE_FAIL
        {
            // return error code.
            return (cy_en_srom_api_status_t)g_scratch.u32[0];
        }
    }
}

/*******************************************************************************
* Function Name: Cy_Srom_ConvertRespToStatus
****************************************************************************//**
*
* This function returns g_scratch value as a response of SROM API.
* Please call this function after "Cy_Srom_CallApi_NonBlock" was called.
* "resp" is raw response data from SROM API on the other hands, return value
* indicate status of the response data like as invalid, succeeded, or failed.
* (if failed return value is same as resp.u32[0])
*
* \param resp
* Pointer to memory into which SROM API response to be copied if not NULL.
*  \ref un_srom_api_resps_t
*
* \return
* \ref cy_en_srom_api_status_t
*
*******************************************************************************/
cy_en_srom_api_status_t Cy_Srom_ConvertRespToStatus(uint32_t resp0)
{
    if((resp0 & 0xF0000000UL) == 0xA0000000UL)
    {
        return CY_SROM_STATUS_SUCCESS;
    }
    else if((resp0 & 0xF0000000UL) == 0xF0000000UL)
    {
        // Error Code
        return (cy_en_srom_api_status_t)resp0;
    }
    else
    {
        return CY_SROM_STATUS_INVALID;
    }
}

/*******************************************************************************
* Function Name: Cy_Srom_SetResponseHandler
****************************************************************************//**
*
* This function sets response handler which is supposed to be called when SROM
* API is complete.
*
* \param handler
* This will be invoked when SROM API finished and the IPC released.
*
*******************************************************************************/
void Cy_Srom_SetResponseHandler(cy_srom_handler handler)
{

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.1', 3, \
'Checked manually. Intentional  expression "NvicMux3_IRQn" of type enum is used as an operand to the arithmetic operator "<<".');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.4', 1, \
'Checked manually. Intentional  expression "NvicMux3_IRQn" of type enum is used as an operand to the arithmetic operator "<<".');
    const cy_stc_sysint_t irq_cfg = {
        .intrSrc = ((NvicMux3_IRQn << 16UL) | CY_SROM_DR_IPC_INTR_NO),
        .intrPriority = 2UL,
    };
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.4');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.1');
    /* set response handler */
    gp_srom_resp_handler = handler;

    /*  Set CPUSS interrupt    */
    cy_en_sysint_status_t sysStatus = Cy_SysInt_Init(&irq_cfg, Cy_Srom_ISR_ResponseIPC);
    if(CY_SYSINT_SUCCESS != sysStatus)
    {
        NVIC_EnableIRQ((IRQn_Type) NvicMux3_IRQn);
    }

    /*  Set IPC interrupt mask    */
    IPC_INTR_STRUCT_Type* sromRespIntrStr = Cy_IPC_Drv_GetIntrBaseAddr(CY_SROM_DR_IPC_INTR_STRUCT);

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.1','Checked manually. Intentional Non boolean type is interpreted as boolean.');
    Cy_IPC_Drv_SetInterruptMask(sromRespIntrStr, (uint32_t)(1UL << (uint32_t)CY_IPC_CHAN_SYSCALL), 0UL);
}

/*******************************************************************************
* Function Cy_Srom_ISR_ResponseIPC
****************************************************************************//**
*
* This is interrupt handler called when SROM API was finished by CM0+ via IPC
* This function will be assigned in "Cy_Srom_SetResponseHandler".
*
*******************************************************************************/
static void Cy_Srom_ISR_ResponseIPC(void)
{
    uint32_t masked = 0;

    IPC_INTR_STRUCT_Type* sromRespIntrStr = Cy_IPC_Drv_GetIntrBaseAddr(CY_SROM_DR_IPC_INTR_STRUCT);
    masked = Cy_IPC_Drv_GetInterruptStatusMasked(sromRespIntrStr);

//    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.1','Checked manually. Intentional Non boolean type is interpreted as boolean.');
    if((uint32_t)(masked & (uint32_t)(1UL << (uint32_t)CY_IPC_CHAN_SYSCALL)) != 0UL)
    {
        if(gp_srom_resp_handler != NULL)
        {
            gp_srom_resp_handler();
        }
    }

    Cy_IPC_Drv_ClearInterrupt(
                                sromRespIntrStr,
                                (masked & 0x0000FFFFUL),
                                (masked & 0xFFFF0000UL) >> 16UL
                              );
}
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
/*******************************************************************************
* Function Cy_Srom_Get_DataSize
****************************************************************************//**
*
* This returns the actual size in bytes based on the enumeration value passed.
*
*******************************************************************************/
static uint32_t Cy_Srom_Get_DataSize(cy_en_programrow_datasize_t size)
{
    uint32_t data_size;
    switch(size)
    {
        case CY_SROM_PROGRAMROW_DATA_SIZE_8BIT:
            data_size = 1u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_16BIT:
            data_size = 2u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_32BIT:
            data_size = 4u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_64BIT:
            data_size = 8u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_128BIT:
            data_size = 16u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_256BIT:
            data_size = 32u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_512BIT:
            data_size = 64u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_1024BIT:
            data_size = 128u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_2048BIT:
            data_size = 256u;
            break;
        case CY_SROM_PROGRAMROW_DATA_SIZE_4096BIT:
            data_size = 512u;
            break;
        default:
            data_size = 0u;
            break;
    }
    return data_size;
}

#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
#endif /* CY_IP_M4CPUSS  CY_IP_M7CPUSS*/
