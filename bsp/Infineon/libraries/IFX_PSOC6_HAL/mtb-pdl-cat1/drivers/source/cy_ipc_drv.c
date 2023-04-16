/***************************************************************************//**
* \file cy_ipc_drv.c
* \version 1.80
*
*  \brief
*   IPC Driver - This source file contains the low-level driver code for
*   the IPC hardware.
*
********************************************************************************
* Copyright 2016-2020 Cypress Semiconductor Corporation
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

#if defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS) || defined (CY_IP_MXIPC)

#include "cy_ipc_drv.h"

/*******************************************************************************
* Function Name: Cy_IPC_Drv_LockRelease
****************************************************************************//**
*
* The function is used to release an IPC channel from the locked state.
* The function also has a way to specify through a parameter which IPC
* interrupts must be notified during the release event.
*
* \param base
* This parameter is a handle that represents the base address of the registers
* of the IPC channel.
* The parameter is generally returned from a call to the \ref
* Cy_IPC_Drv_GetIpcBaseAddress.
*
* \param releaseEventIntr
* Bit encoded list of IPC interrupt lines that are triggered by a release event.
*
* \return   Status of the operation
*   \retval CY_IPC_DRV_SUCCESS: The function executed successfully and the IPC channel
*                       was released.
*   \retval CY_IPC_DRV_ERROR: The IPC channel was not acquired before the
*                       function call.
*
* \funcusage
* \snippet ipc/snippet/main.c snippet_Cy_IPC_Drv_ReadMsgPtr
*
*******************************************************************************/
cy_en_ipcdrv_status_t Cy_IPC_Drv_LockRelease (IPC_STRUCT_Type* base, uint32_t releaseEventIntr)
{
    cy_en_ipcdrv_status_t retStatus;

    /* Check to make sure the IPC is Acquired */
    if( Cy_IPC_Drv_IsLockAcquired(base) )
    {
        /* The IPC was acquired, release the IPC channel */
        Cy_IPC_Drv_ReleaseNotify(base, releaseEventIntr);

        retStatus = CY_IPC_DRV_SUCCESS;
    }
    else   /* The IPC channel was already released (not acquired) */
    {
        retStatus = CY_IPC_DRV_ERROR;
    }

    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_IPC_Drv_SendMsgWord
****************************************************************************//**
*
* This function is used to send a 32-bit word message through an IPC channel.
* The function also has an associated notification field that will let the
* message notify one or multiple IPC interrupts. The IPC channel is locked and
* remains locked after the function returns.  The receiver of the message should
* release the channel.
*
* \param base
* This parameter is a handle that represents the base address of the registers
* of the IPC channel.
* The parameter is generally returned from a call to the \ref
* Cy_IPC_Drv_GetIpcBaseAddress.
*
* \param notifyEventIntr
* Bit encoded list of IPC interrupt lines that are triggered by a notification.
*
* \param message
* The message word that is the data placed in the IPC data register.
*
* \return   Status of the operation:
*   \retval CY_IPC_DRV_SUCCESS: The send operation was successful.
*   \retval CY_IPC_DRV_ERROR: The IPC channel is unavailable because it is already locked.
*
* \funcusage
* \snippet ipc/snippet/main.c snippet_Cy_IPC_Drv_SendMsgWord
*
*******************************************************************************/
cy_en_ipcdrv_status_t  Cy_IPC_Drv_SendMsgWord (IPC_STRUCT_Type* base, uint32_t notifyEventIntr, uint32_t message)
{
    cy_en_ipcdrv_status_t retStatus;

    if( CY_IPC_DRV_SUCCESS == Cy_IPC_Drv_LockAcquire(base) )
    {
        /* If the channel was acquired, send the message. */
        Cy_IPC_Drv_WriteDataValue(base, message);

        Cy_IPC_Drv_AcquireNotify(base, notifyEventIntr);

        retStatus = CY_IPC_DRV_SUCCESS;
    }
    else
    {
        /* Channel was already acquired, return Error */
        retStatus = CY_IPC_DRV_ERROR;
    }
    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_IPC_Drv_ReadMsgWord
****************************************************************************//**
*
* This function is used to read a 32-bit word message through an IPC channel.
* This function assumes that the channel is locked (for a valid message).
* If the channel is not locked, the message is invalid.  The user must call
* Cy_IPC_Drv_Release() function after reading the message to release the
* IPC channel.
*
* \param base
* This parameter is a handle that represents the base address of the registers
* of the IPC channel.
* The parameter is generally returned from a call to the \ref
* Cy_IPC_Drv_GetIpcBaseAddress.
*
* \param message
*  A variable where the read data is copied.
*
* \return  Status of the operation
*   \retval CY_IPC_DRV_SUCCESS: The function executed successfully and the IPC
*                       was acquired.
*   \retval CY_IPC_DRV_ERROR:   The function encountered an error because the IPC
*                       channel was already in a released state, meaning the data
*                       may be invalid.
*
* \funcusage
* \snippet ipc/snippet/main.c snippet_Cy_IPC_Drv_ReadMsgWord
*
*******************************************************************************/
cy_en_ipcdrv_status_t  Cy_IPC_Drv_ReadMsgWord (IPC_STRUCT_Type const * base, uint32_t * message)
{
    cy_en_ipcdrv_status_t retStatus;

    CY_ASSERT_L1(NULL != message);

    if ( Cy_IPC_Drv_IsLockAcquired(base) )
    {
        /* The channel is locked; message is valid. */
        *message = Cy_IPC_Drv_ReadDataValue(base);

        retStatus = CY_IPC_DRV_SUCCESS;
    }
    else
    {
        /* The channel is not locked so channel is invalid. */
        retStatus = CY_IPC_DRV_ERROR;
    }
    return(retStatus);
}

#if defined (CY_IP_M33SYSCPUSS_VERSION) || defined (CY_IP_M7CPUSS) || ( defined (CY_IP_M4CPUSS) && (CY_IP_M4CPUSS_VERSION > 1)) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_IPC_Drv_SendMsgDWord
****************************************************************************//**
*
* This function is used to send two 32-bit word message through an IPC channel.
* The function also has an associated notification field that will let the
* message notify one or multiple IPC interrupts. The IPC channel is locked and
* remains locked after the function returns.  The receiver of the message should
* release the channel.
*
* \param base
* This parameter is a handle that represents the base address of the registers
* of the IPC channel.
* The parameter is generally returned from a call to the \ref
* Cy_IPC_Drv_GetIpcBaseAddress.
*
* \param notifyEventIntr
* Bit encoded list of IPC interrupt lines that are triggered by a notification.
*
* \param message
* The message word that is the data placed in the IPC data register.
*
* \return   Status of the operation:
*   \retval CY_IPC_DRV_SUCCESS: The send operation was successful.
*   \retval CY_IPC_DRV_ERROR: The IPC channel is unavailable because it is already locked.
*
* \funcusage
* \snippet ipc/snippet/main.c snippet_Cy_IPC_Drv_SendMsgWord
*
*******************************************************************************/
CY_IPC_SECTION_BEGIN
cy_en_ipcdrv_status_t  Cy_IPC_Drv_SendMsgDWord (IPC_STRUCT_Type* base, uint32_t notifyEventIntr, uint32_t* message)
{
    cy_en_ipcdrv_status_t retStatus = CY_IPC_DRV_ERROR;

    CY_ASSERT_L1(NULL != message);

    if( CY_IPC_DRV_SUCCESS == Cy_IPC_Drv_LockAcquire(base) )
    {
        /* If the channel was acquired, send the message. */
        Cy_IPC_Drv_WriteDDataValue(base, message);
        Cy_IPC_Drv_AcquireNotify(base, notifyEventIntr);
        retStatus = CY_IPC_DRV_SUCCESS;
    }
    else
    {
        /* Channel was already acquired, return Error */
        retStatus = CY_IPC_DRV_ERROR;
    }
    return (retStatus);
}
CY_IPC_SECTION_END

/*******************************************************************************
* Function Name: Cy_IPC_Drv_ReadMsgDWord
****************************************************************************//**
*
* This function is used to read two 32-bit word message through an IPC channel.
* This function assumes that the channel is locked (for a valid message).
* If the channel is not locked, the message is invalid.  The user must call
* Cy_IPC_Drv_Release() function after reading the message to release the
* IPC channel.
*
* \param base
* This parameter is a handle that represents the base address of the registers
* of the IPC channel.
* The parameter is generally returned from a call to the \ref
* Cy_IPC_Drv_GetIpcBaseAddress.
*
* \param message
*  A variable where the read data is copied.
*
* \return  Status of the operation
*   \retval CY_IPC_DRV_SUCCESS: The function executed successfully and the IPC
*                       was acquired.
*   \retval CY_IPC_DRV_ERROR:   The function encountered an error because the IPC
*                       channel was already in a released state, meaning the data
*                       may be invalid.
*
* \funcusage
* \snippet ipc/snippet/main.c snippet_Cy_IPC_Drv_ReadMsgWord
*
*******************************************************************************/
cy_en_ipcdrv_status_t  Cy_IPC_Drv_ReadMsgDWord (IPC_STRUCT_Type const* base, uint32_t* message)
{
    cy_en_ipcdrv_status_t retStatus;

    CY_ASSERT_L1(NULL != message);

    if ( Cy_IPC_Drv_IsLockAcquired(base) )
    {
        /* The channel is locked; message is valid. */
        Cy_IPC_Drv_ReadDDataValue(base, message);
        retStatus = CY_IPC_DRV_SUCCESS;
    }
    else
    {
        /* The channel is not locked so channel is invalid. */
        retStatus = CY_IPC_DRV_ERROR;
    }
    return(retStatus);
}
#endif /* CY_IP_M33SYSCPUSS_VERSION, CY_IP_M4CPUSS, CY_IP_M4CPUSS_VERSION,  CY_IP_M7CPUSS*/

#endif /* CY_IP_M4CPUSS, CY_IP_M7CPUSS*/
/* [] END OF FILE */
