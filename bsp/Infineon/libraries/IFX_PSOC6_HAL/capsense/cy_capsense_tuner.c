/***************************************************************************//**
* \file cy_capsense_tuner.c
* \version 3.0
*
* \brief
* This file provides the source code for the Tuner module functions.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <stddef.h>
#include "cy_syslib.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_tuner.h"
#include "cy_capsense_control.h"
#include "cy_capsense_common.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))


/*******************************************************************************
* Function Name: Cy_CapSense_TuInitialize
****************************************************************************//**
*
* Initializes the communication interface with the CAPSENSE&trade; Tuner tool.
*
*******************************************************************************/
void Cy_CapSense_TuInitialize(cy_stc_capsense_context_t * context)
{
    volatile cy_stc_capsense_common_context_t * ptrCommonCxt = context->ptrCommonContext;
    ptrCommonCxt->tunerCmd = (uint16_t)CY_CAPSENSE_TU_CMD_NONE_E;
    ptrCommonCxt->tunerSt = (uint8_t)CY_CAPSENSE_TU_FSM_RUNNING;
}


/*******************************************************************************
* Function Name: Cy_CapSense_RunTuner
****************************************************************************//**
*
* Establishes synchronized operation between the CAPSENSE&trade; Middleware and
* the CAPSENSE&trade; Tuner tool.
*
* This function is called periodically in the application program. It serves
* the CAPSENSE&trade; Tuner tool requests and commands to synchronize the operation.
* Mostly, the best place to call this function is between processing and next
* scanning.
* If the user changes some parameters in the Tuner tool, the middleware is
* re-started - the Tuner issues a restart command to be executed by this
* function.
*
* The Tuner interface supports two communication protocol: EZI2C and UART.
*
* To use an EZI2C-based tuner interface, only initialization of the EZI2C
* driver and interface is required in the application program. Refer to
* the I2C driver documentation for details of the protocol implementation
* and data package format by the EZI2C interface.
*
* To use a UART-based tuner interface, the user must:
* * Initialize the UART driver and interface
* * Use a callback function to facilitate data transmission and reception
*   using the UART driver.
*
* The application program must:
* * Form a transmission data packet
* * Validate the data package on receiver implementation prior to passing
*   to the CAPSENSE&trade; Middleware.
*
* The transmission packet includes a CAPSENSE&trade; context structure sandwiched
* between a header (0x0D0A) and a tail (0x00FFFF), hence the package size
* is dependent on CAPSENSE&trade; context information. The receiver packet is
* 16-byte (fixed length) data explained under the
* Cy_CapSense_CheckTunerCmdIntegrity() function.
* The Cy_CapSense_CheckTunerCmdIntegrity() function is used to validate
* the received data package prior to passing it to the CAPSENSE&trade; middleware.
*
* Periodical calling the Cy_CapSense_RunTuner() function is:
* * mandatory for operation of a UART-based tuner interface. The middleware
*   operation is always synchronous to the Tuner tool.
* * optional to periodically call Cy_CapSense_RunTuner() for EZI2C based
*   interface.
*
* If the Cy_CapSense_RunTuner() function is not periodically called by
* the application program, the middleware operation is asynchronous to
* the Tuner tool and the following disadvantages are applicable:
* * The raw counts displayed in the CAPSENSE&trade; Tuner tool may be filtered
*   and/or non-filtered. Result - noise and SNR measurements are not accurate.
* * The CAPSENSE&trade; Tuner tool can read sensor data (such as raw counts) from
*   a scan multiply. Result - noise and SNR measurement are not accurate.
* * The CAPSENSE&trade; Tuner tool and Host controller should not change the
*   parameters via the Tuner interface - in async mode this leads to
*   abnormal behavior.
* * Displaying detected gestures may be missed.
*
* \warning
* This function executes received commands. Two commands
* CY_CAPSENSE_TU_CMD_ONE_SCAN_E and CY_CAPSENSE_TU_CMD_SUSPEND_E change
* the FW tuner module state to suspend. In this state, the function waits
* until CY_CAPSENSE_TU_CMD_RESUME_E is received. Use a callback mechanism
* of command receiving to avoid FW hanging. Refer to
* the Function Usage section for examples.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* The return parameter indicates whether a middleware re-start was executed
* by this function or not:
* - CY_CAPSENSE_STATUS_RESTART_DONE - Based on a received command, the
* CAPSENSE&trade; was re-initialized.
* - CY_CAPSENSE_STATUS_RESTART_NONE - Re-start was not executed by this
* function.
*
* \funcusage
*
* An example of synchronization with the Tuner tool using EzI2C:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_Tuner_EzI2C
*
* An example of synchronization with the Tuner tool using UART.<br>
* Tuner Send callback implementation: Transmitting data through UART interface:
* \snippet capsense/snippet/main.c snippet_TunerSend
*
* Tuner Receive callback implementation: Receiving data from UART interface:
* \snippet capsense/snippet/main.c snippet_TunerReceive
*
* A part of the main.c FW flow with registering callbacks:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_Tuner_UART
*
* Refer to the \ref group_capsense_callbacks section for details.
*
*******************************************************************************/
uint32_t Cy_CapSense_RunTuner(cy_stc_capsense_context_t * context)
{
    uint32_t interruptState;
    uint32_t updateFlag = 0uL;
    uint32_t tunerStatus = CY_CAPSENSE_STATUS_RESTART_NONE;
    uint16_t tunerCommand;
    uint32_t cmdOffset;
    uint32_t cmdSize;
    uint8_t cmdCounter;

    uint8_t * tunerStructure = NULL;
    uint8_t * commandPacket = NULL;
    volatile cy_stc_capsense_common_context_t * ptrCommonCxt = context->ptrCommonContext;
    uint8_t tunerState = ptrCommonCxt->tunerSt;

    cy_capsense_tuner_send_callback_t sendCallback = context->ptrInternalContext->ptrTunerSendCallback;
    cy_capsense_tuner_receive_callback_t receiveCallback = context->ptrInternalContext->ptrTunerReceiveCallback;

    do
    {
        /*
        * ONE_SCAN command could be interpreted as two commands:
        * RESUME till next call of this function and then
        * SUSPEND till next command receiving.
        * So, after one scan cycle tuner state is changed to suspend.
        */
        if ((uint8_t)CY_CAPSENSE_TU_FSM_ONE_SCAN == tunerState)
        {
            interruptState = Cy_SysLib_EnterCriticalSection();
            context->ptrCommonContext->tunerCmd = (uint16_t)CY_CAPSENSE_TU_CMD_SUSPEND_E;
            Cy_SysLib_ExitCriticalSection(interruptState);
        }

        /* Send Data to the CAPSENSE&trade; Tuner tool */
        if(NULL != sendCallback)
        {
            sendCallback((void *)context);
        }

        /* Command can come from EzI2C by direct writing into data structure */
        tunerCommand = context->ptrCommonContext->tunerCmd;
        cmdCounter = context->ptrCommonContext->tunerCnt + 1u;

        /* Call user's callback function if it is registered */
        if (NULL != receiveCallback)
        {
            commandPacket = NULL;
            tunerStructure = NULL;
            receiveCallback(&commandPacket, &tunerStructure, context);

            /* If command exists and is correct then read command */
            if ((NULL != commandPacket) && (NULL != tunerStructure))
            {
                if (CY_CAPSENSE_COMMAND_OK == Cy_CapSense_CheckTunerCmdIntegrity(commandPacket))
                {
                    tunerCommand = commandPacket[CY_CAPSENSE_COMMAND_CODE_0_IDX];
                    ptrCommonCxt->tunerCmd = tunerCommand;
                    cmdCounter = commandPacket[CY_CAPSENSE_COMMAND_CNTR_0_IDX];
                }
            }
        }

        /* Check command register */
        switch (tunerCommand)
        {
        case (uint16_t)CY_CAPSENSE_TU_CMD_SUSPEND_E:
            tunerState = (uint8_t)CY_CAPSENSE_TU_FSM_SUSPENDED;
            updateFlag = 1u;
            break;

        case (uint16_t)CY_CAPSENSE_TU_CMD_RESUME_E:
            tunerState = (uint8_t)CY_CAPSENSE_TU_FSM_RUNNING;
            updateFlag = 1u;
            break;

        case (uint16_t)CY_CAPSENSE_TU_CMD_RESTART_E:
            (void)Cy_CapSense_Enable(context);
            tunerStatus = CY_CAPSENSE_STATUS_RESTART_DONE;
            tunerState = (uint8_t)CY_CAPSENSE_TU_FSM_RUNNING;
            updateFlag = 1u;
            break;

        case (uint16_t)CY_CAPSENSE_TU_CMD_PING_E:
            tunerState = (uint8_t)CY_CAPSENSE_TU_FSM_RUNNING;
            updateFlag = 1u;
            break;

        case (uint16_t)CY_CAPSENSE_TU_CMD_ONE_SCAN_E:
            tunerState = (uint8_t)CY_CAPSENSE_TU_FSM_ONE_SCAN;
            updateFlag = 0u;
            break;

        case (uint16_t)CY_CAPSENSE_TU_CMD_WRITE_E:
            if((NULL != receiveCallback) && (NULL != commandPacket) && (NULL != tunerStructure))
            {
                /* Tuner state is not changed */
                cmdOffset = (uint32_t)((uint32_t)commandPacket[CY_CAPSENSE_COMMAND_OFFS_0_IDX] << CY_CAPSENSE_MSB_SHIFT) |
                                       (uint32_t)commandPacket[CY_CAPSENSE_COMMAND_OFFS_1_IDX];
                cmdSize = commandPacket[CY_CAPSENSE_COMMAND_SIZE_0_IDX];

                if (1u == cmdSize)
                {
                    tunerStructure[cmdOffset] = commandPacket[CY_CAPSENSE_COMMAND_DATA_0_IDX + 3u];
                }
                else if (2u == cmdSize)
                {
                    tunerStructure[cmdOffset + 1u] = commandPacket[CY_CAPSENSE_COMMAND_DATA_0_IDX + 2u];
                    tunerStructure[cmdOffset + 0u] = commandPacket[CY_CAPSENSE_COMMAND_DATA_0_IDX + 3u];
                }
                else
                {
                    tunerStructure[cmdOffset + 3u] = commandPacket[CY_CAPSENSE_COMMAND_DATA_0_IDX + 0u];
                    tunerStructure[cmdOffset + 2u] = commandPacket[CY_CAPSENSE_COMMAND_DATA_0_IDX + 1u];
                    tunerStructure[cmdOffset + 1u] = commandPacket[CY_CAPSENSE_COMMAND_DATA_0_IDX + 2u];
                    tunerStructure[cmdOffset + 0u] = commandPacket[CY_CAPSENSE_COMMAND_DATA_0_IDX + 3u];
                }

                updateFlag = 1u;
            }
            break;

        default:
            /* No action on other commands */
            break;
        }

        ptrCommonCxt->tunerSt = tunerState;

        /* Set Complete flag in command register if needed */
        if (0uL != updateFlag)
        {
            interruptState = Cy_SysLib_EnterCriticalSection();
            /* Check that command wasn't overwritten with new command */
            if (tunerCommand == ptrCommonCxt->tunerCmd)
            {
                ptrCommonCxt->tunerCmd |= CY_CAPSENSE_TU_CMD_COMPLETE_BIT;
                ptrCommonCxt->tunerCnt = cmdCounter;
            }
            Cy_SysLib_ExitCriticalSection(interruptState);
            updateFlag = 0uL;
        }

    } while ((uint8_t)CY_CAPSENSE_TU_FSM_SUSPENDED == tunerState);

    return tunerStatus;
}


/*******************************************************************************
* Function Name: Cy_CapSense_CheckTunerCmdIntegrity
****************************************************************************//**
*
* Checks command format, header, tail, CRC, etc.
*
* This function checks whether the specified packet with the size
* CY_CAPSENSE_COMMAND_PACKET_SIZE could be represented as a
* command received from the CAPSENSE&trade; Tuner tool.
* The verification includes the following items:
* * Header
* * Tail
* * CRC
* * Command code
*
* Command format is the following:
* * Byte  0: Header 0 = 0x0D
* * Byte  1: Header 1 = 0x0A
* * Byte  2: Command code = cy_en_capsense_tuner_cmd_t
* * Byte  3: Command counter
* * Byte  4: Size = either 1, 2 or 4
* * Byte  5: Offset MSB
* * Byte  6: Offset LSB
* * Byte  7: Data MSB
* * Byte  8: Data
* * Byte  9: Data
* * Byte 10: Data LSB
* * Byte 11: 16-bit CRC MSB
* * Byte 12: 16-bit CRC LSB
* * Byte 13: Tail 0 = 0x00
* * Byte 14: Tail 1 = 0xFF
* * Byte 15: Tail 2 = 0xFF
*
* \param commandPacket
* The pointer to the data packet that should be verified.
*
* \return
* Returns the result of the command verification:
* - CY_CAPSENSE_COMMAND_OK - Command is correct.
* - CY_CAPSENSE_WRONG_HEADER - Wrong header.
* - CY_CAPSENSE_WRONG_TAIL - Wrong tail.
* - CY_CAPSENSE_WRONG_CRC - Wrong CRC.
* - CY_CAPSENSE_WRONG_CODE - Wrong Command code.
*
*******************************************************************************/
uint32_t Cy_CapSense_CheckTunerCmdIntegrity(const uint8_t * commandPacket)
{
    uint32_t cmdCheckStatus = CY_CAPSENSE_COMMAND_OK;
    uint16_t crcValue;

    if (CY_CAPSENSE_COMMAND_HEAD_0 != commandPacket[CY_CAPSENSE_COMMAND_HEAD_0_IDX])
    {
        cmdCheckStatus = CY_CAPSENSE_WRONG_HEADER;
    }
    else if (CY_CAPSENSE_COMMAND_HEAD_1 != commandPacket[CY_CAPSENSE_COMMAND_HEAD_1_IDX])
    {
        cmdCheckStatus = CY_CAPSENSE_WRONG_HEADER;
    }
    else if (CY_CAPSENSE_COMMAND_TAIL_0 != commandPacket[CY_CAPSENSE_COMMAND_TAIL_0_IDX])
    {
        cmdCheckStatus = CY_CAPSENSE_WRONG_TAIL;
    }
    else if (CY_CAPSENSE_COMMAND_TAIL_1 != commandPacket[CY_CAPSENSE_COMMAND_TAIL_1_IDX])
    {
        cmdCheckStatus = CY_CAPSENSE_WRONG_TAIL;
    }
    else if (CY_CAPSENSE_COMMAND_TAIL_2 != commandPacket[CY_CAPSENSE_COMMAND_TAIL_2_IDX])
    {
        cmdCheckStatus = CY_CAPSENSE_WRONG_TAIL;
    }
    else if (((uint8_t)CY_CAPSENSE_TU_CMD_WRITE_E) < commandPacket[CY_CAPSENSE_COMMAND_CODE_0_IDX])
    {
        cmdCheckStatus = CY_CAPSENSE_WRONG_CODE;
    }
    else
    {
        crcValue = (uint16_t)((uint16_t)commandPacket[CY_CAPSENSE_COMMAND_CRC_0_IDX] << CY_CAPSENSE_MSB_SHIFT);
        crcValue |= (uint16_t)commandPacket[CY_CAPSENSE_COMMAND_CRC_1_IDX];
        if (crcValue != Cy_CapSense_GetCRC(&commandPacket[0u], CY_CAPSENSE_COMMAND_CRC_DATA_SIZE))
        {
            cmdCheckStatus = CY_CAPSENSE_WRONG_CRC;
        }
    }

    return cmdCheckStatus;
}

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */


/* [] END OF FILE */
