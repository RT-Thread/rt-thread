/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_can.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_can.h"
#include "n32g45x_rcc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup CAN
 * @brief CAN driver modules
 * @{
 */

/** @addtogroup CAN_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup CAN_Private_Defines
 * @{
 */

/* CAN Master Control Register bits */
#define MCTRL_DBGF ((uint32_t)0x00010000) /* Debug freeze */
#define MCTRL_MRST ((uint32_t)0x00010000) /* software master reset */

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ ((uint32_t)0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define FMC_FINITM ((uint32_t)0x00000001) /* Filter init mode */

/* Time out for INAK bit */
#define INIAK_TIMEOUT ((uint32_t)0x0000FFFF)
/* Time out for SLAK bit */
#define SLPAK_TIMEOUT ((uint32_t)0x0000FFFF)

/* Flags in TSTS register */
#define CAN_FLAGS_TSTS ((uint32_t)0x08000000)
/* Flags in RFF1 register */
#define CAN_FLAGS_RFF1 ((uint32_t)0x04000000)
/* Flags in RFF0 register */
#define CAN_FLAGS_RFF0 ((uint32_t)0x02000000)
/* Flags in MSTS register */
#define CAN_FLAGS_MSTS ((uint32_t)0x01000000)
/* Flags in ESTS register */
#define CAN_FLAGS_ESTS ((uint32_t)0x00F00000)

/* Mailboxes definition */
#define CAN_TXMAILBOX_0 ((uint8_t)0x00)
#define CAN_TXMAILBOX_1 ((uint8_t)0x01)
#define CAN_TXMAILBOX_2 ((uint8_t)0x02)

#define CAN_MODE_MASK ((uint32_t)0x00000003)
/**
 * @}
 */

/** @addtogroup CAN_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup CAN_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup CAN_Private_FunctionPrototypes
 * @{
 */

static INTStatus CheckINTStatus(uint32_t CAN_Reg, uint32_t Int_Bit);

/**
 * @}
 */

/** @addtogroup CAN_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the CAN peripheral registers to their default reset values.
 * @param CANx where x can be 1 or 2 to select the CAN peripheral.
 */
void CAN_DeInit(CAN_Module* CANx)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    if (CANx == CAN1)
    {
        /* Enable CAN1 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_CAN1, ENABLE);
        /* Release CAN1 from reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_CAN1, DISABLE);
    }
    else
    {
        /* Enable CAN2 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_CAN2, ENABLE);
        /* Release CAN2 from reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_CAN2, DISABLE);
    }
}

/**
 * @brief  Initializes the CAN peripheral according to the specified
 *         parameters in the CAN_InitParam.
 * @param CANx where x can be 1 or 2 to to select the CAN
 *                         peripheral.
 * @param CAN_InitParam pointer to a CAN_InitType structure that
 *                         contains the configuration information for the
 *                         CAN peripheral.
 * @return Constant indicates initialization succeed which will be
 *         CAN_InitSTS_Failed or CAN_InitSTS_Success.
 */
uint8_t CAN_Init(CAN_Module* CANx, CAN_InitType* CAN_InitParam)
{
    uint8_t InitStatus = CAN_InitSTS_Failed;
    uint32_t wait_ack  = 0x00000000;
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitParam->TTCM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitParam->ABOM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitParam->AWKUM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitParam->NART));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitParam->RFLM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitParam->TXFP));
    assert_param(IS_CAN_MODE(CAN_InitParam->OperatingMode));
    assert_param(IS_CAN_RSJW(CAN_InitParam->RSJW));
    assert_param(IS_CAN_TBS1(CAN_InitParam->TBS1));
    assert_param(IS_CAN_TBS2(CAN_InitParam->TBS2));
    assert_param(IS_CAN_BAUDRATEPRESCALER(CAN_InitParam->BaudRatePrescaler));

    /* Exit from sleep mode */
    CANx->MCTRL &= (~(uint32_t)CAN_MCTRL_SLPRQ);

    /* Request initialisation */
    CANx->MCTRL |= CAN_MCTRL_INIRQ;

    /* Wait the acknowledge */
    while (((CANx->MSTS & CAN_MSTS_INIAK) != CAN_MSTS_INIAK) && (wait_ack != INIAK_TIMEOUT))
    {
        wait_ack++;
    }

    /* Check acknowledge */
    if ((CANx->MSTS & CAN_MSTS_INIAK) != CAN_MSTS_INIAK)
    {
        InitStatus = CAN_InitSTS_Failed;
    }
    else
    {
        /* Set the time triggered communication mode */
        if (CAN_InitParam->TTCM == ENABLE)
        {
            CANx->MCTRL |= CAN_MCTRL_TTCM;
        }
        else
        {
            CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_TTCM;
        }

        /* Set the automatic bus-off management */
        if (CAN_InitParam->ABOM == ENABLE)
        {
            CANx->MCTRL |= CAN_MCTRL_ABOM;
        }
        else
        {
            CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_ABOM;
        }

        /* Set the automatic wake-up mode */
        if (CAN_InitParam->AWKUM == ENABLE)
        {
            CANx->MCTRL |= CAN_MCTRL_AWKUM;
        }
        else
        {
            CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_AWKUM;
        }

        /* Set the no automatic retransmission */
        if (CAN_InitParam->NART == ENABLE)
        {
            CANx->MCTRL |= CAN_MCTRL_NART;
        }
        else
        {
            CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_NART;
        }

        /* Set the receive DATFIFO locked mode */
        if (CAN_InitParam->RFLM == ENABLE)
        {
            CANx->MCTRL |= CAN_MCTRL_RFLM;
        }
        else
        {
            CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_RFLM;
        }

        /* Set the transmit DATFIFO priority */
        if (CAN_InitParam->TXFP == ENABLE)
        {
            CANx->MCTRL |= CAN_MCTRL_TXFP;
        }
        else
        {
            CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_TXFP;
        }

        /* Set the bit timing register */
        CANx->BTIM = (uint32_t)((uint32_t)CAN_InitParam->OperatingMode << 30) | ((uint32_t)CAN_InitParam->RSJW << 24)
                    | ((uint32_t)CAN_InitParam->TBS1 << 16) | ((uint32_t)CAN_InitParam->TBS2 << 20)
                    | ((uint32_t)CAN_InitParam->BaudRatePrescaler - 1);

        /* Request leave initialisation */
        CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_INIRQ;

        /* Wait the acknowledge */
        wait_ack = 0;

        while (((CANx->MSTS & CAN_MSTS_INIAK) == CAN_MSTS_INIAK) && (wait_ack != INIAK_TIMEOUT))
        {
            wait_ack++;
        }

        /* ...and check acknowledged */
        if ((CANx->MSTS & CAN_MSTS_INIAK) == CAN_MSTS_INIAK)
        {
            InitStatus = CAN_InitSTS_Failed;
        }
        else
        {
            InitStatus = CAN_InitSTS_Success;
        }
    }

    /* At this step, return the status of initialization */
    return InitStatus;
}

/**
 * @brief  Initializes the CAN1 peripheral according to the specified
 *         parameters in the CAN_InitFilterStruct.
 * @param CAN_InitFilterStruct pointer to a CAN_FilterInitType
 *                               structure that contains the configuration
 *                               information.
 */
void CAN1_InitFilter(CAN_FilterInitType* CAN_InitFilterStruct)
{
    uint32_t filter_number_bit_pos = 0;
    /* Check the parameters */
    assert_param(IS_CAN_FILTER_NUM(CAN_InitFilterStruct->Filter_Num));
    assert_param(IS_CAN_FILTER_MODE(CAN_InitFilterStruct->Filter_Mode));
    assert_param(IS_CAN_FILTER_SCALE(CAN_InitFilterStruct->Filter_Scale));
    assert_param(IS_CAN_FILTER_FIFO(CAN_InitFilterStruct->Filter_FIFOAssignment));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitFilterStruct->Filter_Act));

    filter_number_bit_pos = ((uint32_t)1) << CAN_InitFilterStruct->Filter_Num;

    /* Initialisation mode for the filter */
    CAN1->FMC |= FMC_FINITM;

    /* Filter Deactivation */
    CAN1->FA1 &= ~(uint32_t)filter_number_bit_pos;

    /* Filter Scale */
    if (CAN_InitFilterStruct->Filter_Scale == CAN_Filter_16bitScale)
    {
        /* 16-bit scale for the filter */
        CAN1->FS1 &= ~(uint32_t)filter_number_bit_pos;

        /* First 16-bit identifier and First 16-bit mask */
        /* Or First 16-bit identifier and Second 16-bit identifier */
        CAN1->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_LowId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_LowId);

        /* Second 16-bit identifier and Second 16-bit mask */
        /* Or Third 16-bit identifier and Fourth 16-bit identifier */
        CAN1->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_HighId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_HighId);
    }

    if (CAN_InitFilterStruct->Filter_Scale == CAN_Filter_32bitScale)
    {
        /* 32-bit scale for the filter */
        CAN1->FS1 |= filter_number_bit_pos;
        /* 32-bit identifier or First 32-bit identifier */
        CAN1->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_HighId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_LowId);
        /* 32-bit mask or Second 32-bit identifier */
        CAN1->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_HighId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_LowId);
    }

    /* Filter Mode */
    if (CAN_InitFilterStruct->Filter_Mode == CAN_Filter_IdMaskMode)
    {
        /*Id/Mask mode for the filter*/
        CAN1->FM1 &= ~(uint32_t)filter_number_bit_pos;
    }
    else /* CAN_InitFilterStruct->Filter_Mode == CAN_Filter_IdListMode */
    {
        /*Identifier list mode for the filter*/
        CAN1->FM1 |= (uint32_t)filter_number_bit_pos;
    }

    /* Filter DATFIFO assignment */
    if (CAN_InitFilterStruct->Filter_FIFOAssignment == CAN_Filter_FIFO0)
    {
        /* DATFIFO 0 assignation for the filter */
        CAN1->FFA1 &= ~(uint32_t)filter_number_bit_pos;
    }

    if (CAN_InitFilterStruct->Filter_FIFOAssignment == CAN_Filter_FIFO1)
    {
        /* DATFIFO 1 assignation for the filter */
        CAN1->FFA1 |= (uint32_t)filter_number_bit_pos;
    }

    /* Filter activation */
    if (CAN_InitFilterStruct->Filter_Act == ENABLE)
    {
        CAN1->FA1 |= filter_number_bit_pos;
    }

    /* Leave the initialisation mode for the filter */
    CAN1->FMC &= ~FMC_FINITM;
}

/**
 * @brief  Initializes the CAN2 peripheral according to the specified
 *         parameters in the CAN_InitFilterStruct.
 * @param CAN_InitFilterStruct pointer to a CAN_FilterInitType
 *                               structure that contains the configuration
 *                               information.
 */
void CAN2_InitFilter(CAN_FilterInitType* CAN_InitFilterStruct)
{
    uint32_t filter_number_bit_pos = 0;
    /* Check the parameters */
    assert_param(IS_CAN_FILTER_NUM(CAN_InitFilterStruct->Filter_Num));
    assert_param(IS_CAN_FILTER_MODE(CAN_InitFilterStruct->Filter_Mode));
    assert_param(IS_CAN_FILTER_SCALE(CAN_InitFilterStruct->Filter_Scale));
    assert_param(IS_CAN_FILTER_FIFO(CAN_InitFilterStruct->Filter_FIFOAssignment));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitFilterStruct->Filter_Act));

    filter_number_bit_pos = ((uint32_t)1) << CAN_InitFilterStruct->Filter_Num;

    /* Initialisation mode for the filter */
    CAN2->FMC |= FMC_FINITM;

    /* Filter Deactivation */
    CAN2->FA1 &= ~(uint32_t)filter_number_bit_pos;

    /* Filter Scale */
    if (CAN_InitFilterStruct->Filter_Scale == CAN_Filter_16bitScale)
    {
        /* 16-bit scale for the filter */
        CAN2->FS1 &= ~(uint32_t)filter_number_bit_pos;

        /* First 16-bit identifier and First 16-bit mask */
        /* Or First 16-bit identifier and Second 16-bit identifier */
        CAN2->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_LowId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_LowId);

        /* Second 16-bit identifier and Second 16-bit mask */
        /* Or Third 16-bit identifier and Fourth 16-bit identifier */
        CAN2->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_HighId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_HighId);
    }

    if (CAN_InitFilterStruct->Filter_Scale == CAN_Filter_32bitScale)
    {
        /* 32-bit scale for the filter */
        CAN2->FS1 |= filter_number_bit_pos;
        /* 32-bit identifier or First 32-bit identifier */
        CAN2->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_HighId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->Filter_LowId);
        /* 32-bit mask or Second 32-bit identifier */
        CAN2->sFilterRegister[CAN_InitFilterStruct->Filter_Num].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_HighId) << 16)
            | (0x0000FFFF & (uint32_t)CAN_InitFilterStruct->FilterMask_LowId);
    }

    /* Filter Mode */
    if (CAN_InitFilterStruct->Filter_Mode == CAN_Filter_IdMaskMode)
    {
        /*Id/Mask mode for the filter*/
        CAN2->FM1 &= ~(uint32_t)filter_number_bit_pos;
    }
    else /* CAN_InitFilterStruct->Filter_Mode == CAN_Filter_IdListMode */
    {
        /*Identifier list mode for the filter*/
        CAN2->FM1 |= (uint32_t)filter_number_bit_pos;
    }

    /* Filter DATFIFO assignment */
    if (CAN_InitFilterStruct->Filter_FIFOAssignment == CAN_Filter_FIFO0)
    {
        /* DATFIFO 0 assignation for the filter */
        CAN2->FFA1 &= ~(uint32_t)filter_number_bit_pos;
    }

    if (CAN_InitFilterStruct->Filter_FIFOAssignment == CAN_Filter_FIFO1)
    {
        /* DATFIFO 1 assignation for the filter */
        CAN2->FFA1 |= (uint32_t)filter_number_bit_pos;
    }

    /* Filter activation */
    if (CAN_InitFilterStruct->Filter_Act == ENABLE)
    {
        CAN2->FA1 |= filter_number_bit_pos;
    }

    /* Leave the initialisation mode for the filter */
    CAN2->FMC &= ~FMC_FINITM;
}

/**
 * @brief  Fills each CAN_InitParam member with its default value.
 * @param CAN_InitParam pointer to a CAN_InitType structure which
 *                         will be initialized.
 */
void CAN_InitStruct(CAN_InitType* CAN_InitParam)
{
    /* Reset CAN init structure parameters values */

    /* Initialize the time triggered communication mode */
    CAN_InitParam->TTCM = DISABLE;

    /* Initialize the automatic bus-off management */
    CAN_InitParam->ABOM = DISABLE;

    /* Initialize the automatic wake-up mode */
    CAN_InitParam->AWKUM = DISABLE;

    /* Initialize the no automatic retransmission */
    CAN_InitParam->NART = DISABLE;

    /* Initialize the receive DATFIFO locked mode */
    CAN_InitParam->RFLM = DISABLE;

    /* Initialize the transmit DATFIFO priority */
    CAN_InitParam->TXFP = DISABLE;

    /* Initialize the OperatingMode member */
    CAN_InitParam->OperatingMode = CAN_Normal_Mode;

    /* Initialize the RSJW member */
    CAN_InitParam->RSJW = CAN_RSJW_1tq;

    /* Initialize the TBS1 member */
    CAN_InitParam->TBS1 = CAN_TBS1_4tq;

    /* Initialize the TBS2 member */
    CAN_InitParam->TBS2 = CAN_TBS2_3tq;

    /* Initialize the BaudRatePrescaler member */
    CAN_InitParam->BaudRatePrescaler = 1;
}

/**
 * @brief  Enables or disables the DBG Freeze for CAN.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param Cmd new state of the CAN peripheral. This parameter can
 *                   be: ENABLE or DISABLE.
 */
void CAN_DebugFreeze(CAN_Module* CANx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable Debug Freeze  */
        CANx->MCTRL |= MCTRL_DBGF;
    }
    else
    {
        /* Disable Debug Freeze */
        CANx->MCTRL &= ~MCTRL_DBGF;
    }
}

/**
 * @brief  Enables or disabes the CAN Time TriggerOperation communication mode.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param Cmd Mode new state , can be one of @ref FunctionalState.
 * @note   when enabled, Time stamp (TIME[15:0]) value is sent in the last
 *         two data bytes of the 8-byte message: TIME[7:0] in data byte 6
 *         and TIME[15:8] in data byte 7
 * @note   DLC must be programmed as 8 in order Time Stamp (2 bytes) to be
 *         sent over the CAN bus.
 */
void CAN_EnTTComMode(CAN_Module* CANx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the TTCM mode */
        CANx->MCTRL |= CAN_MCTRL_TTCM;

        /* Set TGT bits */
        CANx->sTxMailBox[0].TMDT |= ((uint32_t)CAN_TMDT0_TGT);
        CANx->sTxMailBox[1].TMDT |= ((uint32_t)CAN_TMDT1_TGT);
        CANx->sTxMailBox[2].TMDT |= ((uint32_t)CAN_TMDT2_TGT);
    }
    else
    {
        /* Disable the TTCM mode */
        CANx->MCTRL &= (uint32_t)(~(uint32_t)CAN_MCTRL_TTCM);

        /* Reset TGT bits */
        CANx->sTxMailBox[0].TMDT &= ((uint32_t)~CAN_TMDT0_TGT);
        CANx->sTxMailBox[1].TMDT &= ((uint32_t)~CAN_TMDT1_TGT);
        CANx->sTxMailBox[2].TMDT &= ((uint32_t)~CAN_TMDT2_TGT);
    }
}
/**
 * @brief  Initiates the transmission of a message.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param TxMessage pointer to a structure which contains CAN Id, CAN
 *                    DLC and CAN data.
 * @return The number of the mailbox that is used for transmission
 *                    or CAN_TxSTS_NoMailBox if there is no empty mailbox.
 */
uint8_t CAN_TransmitMessage(CAN_Module* CANx, CanTxMessage* TxMessage)
{
    uint8_t transmit_mailbox = 0;
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_ID(TxMessage->IDE));
    assert_param(IS_CAN_RTRQ(TxMessage->RTR));
    assert_param(IS_CAN_DLC(TxMessage->DLC));

    /* Select one empty transmit mailbox */
    if ((CANx->TSTS & CAN_TSTS_TMEM0) == CAN_TSTS_TMEM0)
    {
        transmit_mailbox = 0;
    }
    else if ((CANx->TSTS & CAN_TSTS_TMEM1) == CAN_TSTS_TMEM1)
    {
        transmit_mailbox = 1;
    }
    else if ((CANx->TSTS & CAN_TSTS_TMEM2) == CAN_TSTS_TMEM2)
    {
        transmit_mailbox = 2;
    }
    else
    {
        transmit_mailbox = CAN_TxSTS_NoMailBox;
    }

    if (transmit_mailbox != CAN_TxSTS_NoMailBox)
    {
        /* Set up the Id */
        CANx->sTxMailBox[transmit_mailbox].TMI &= TMIDxR_TXRQ;
        if (TxMessage->IDE == CAN_Standard_Id)
        {
            assert_param(IS_CAN_STDID(TxMessage->StdId));
            CANx->sTxMailBox[transmit_mailbox].TMI |= ((TxMessage->StdId << 21) | TxMessage->RTR);
        }
        else
        {
            assert_param(IS_CAN_EXTID(TxMessage->ExtId));
            CANx->sTxMailBox[transmit_mailbox].TMI |= ((TxMessage->ExtId << 3) | TxMessage->IDE | TxMessage->RTR);
        }

        /* Set up the DLC */
        TxMessage->DLC &= (uint8_t)0x0000000F;
        CANx->sTxMailBox[transmit_mailbox].TMDT &= (uint32_t)0xFFFFFFF0;
        CANx->sTxMailBox[transmit_mailbox].TMDT |= TxMessage->DLC;

        /* Set up the data field */
        CANx->sTxMailBox[transmit_mailbox].TMDL =
            (((uint32_t)TxMessage->Data[3] << 24) | ((uint32_t)TxMessage->Data[2] << 16)
             | ((uint32_t)TxMessage->Data[1] << 8) | ((uint32_t)TxMessage->Data[0]));
        CANx->sTxMailBox[transmit_mailbox].TMDH =
            (((uint32_t)TxMessage->Data[7] << 24) | ((uint32_t)TxMessage->Data[6] << 16)
             | ((uint32_t)TxMessage->Data[5] << 8) | ((uint32_t)TxMessage->Data[4]));
        /* Request transmission */
        CANx->sTxMailBox[transmit_mailbox].TMI |= TMIDxR_TXRQ;
    }
    return transmit_mailbox;
}

/**
 * @brief  Checks the transmission of a message.
 * @param CANx where x can be 1 or 2 to to select the
 *                          CAN peripheral.
 * @param TransmitMailbox the number of the mailbox that is used for
 *                          transmission.
 * @return CAN_TxSTS_Ok if the CAN driver transmits the message, CAN_TxSTS_Failed
 *         in an other case.
 */
uint8_t CAN_TransmitSTS(CAN_Module* CANx, uint8_t TransmitMailbox)
{
    uint32_t state = 0;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_TRANSMITMAILBOX(TransmitMailbox));

    switch (TransmitMailbox)
    {
    case (CAN_TXMAILBOX_0):
        state = CANx->TSTS & (CAN_TSTS_RQCPM0 | CAN_TSTS_TXOKM0 | CAN_TSTS_TMEM0);
        break;
    case (CAN_TXMAILBOX_1):
        state = CANx->TSTS & (CAN_TSTS_RQCPM1 | CAN_TSTS_TXOKM1 | CAN_TSTS_TMEM1);
        break;
    case (CAN_TXMAILBOX_2):
        state = CANx->TSTS & (CAN_TSTS_RQCPM2 | CAN_TSTS_TXOKM2 | CAN_TSTS_TMEM2);
        break;
    default:
        state = CAN_TxSTS_Failed;
        break;
    }
    switch (state)
    {
        /* transmit pending  */
    case (0x0):
        state = CAN_TxSTS_Pending;
        break;
        /* transmit failed  */
    case (CAN_TSTS_RQCPM0 | CAN_TSTS_TMEM0):
        state = CAN_TxSTS_Failed;
        break;
    case (CAN_TSTS_RQCPM1 | CAN_TSTS_TMEM1):
        state = CAN_TxSTS_Failed;
        break;
    case (CAN_TSTS_RQCPM2 | CAN_TSTS_TMEM2):
        state = CAN_TxSTS_Failed;
        break;
        /* transmit succeeded  */
    case (CAN_TSTS_RQCPM0 | CAN_TSTS_TXOKM0 | CAN_TSTS_TMEM0):
        state = CAN_TxSTS_Ok;
        break;
    case (CAN_TSTS_RQCPM1 | CAN_TSTS_TXOKM1 | CAN_TSTS_TMEM1):
        state = CAN_TxSTS_Ok;
        break;
    case (CAN_TSTS_RQCPM2 | CAN_TSTS_TXOKM2 | CAN_TSTS_TMEM2):
        state = CAN_TxSTS_Ok;
        break;
    default:
        state = CAN_TxSTS_Failed;
        break;
    }
    return (uint8_t)state;
}

/**
 * @brief  Cancels a transmit request.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param Mailbox Mailbox number.
 */
void CAN_CancelTransmitMessage(CAN_Module* CANx, uint8_t Mailbox)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_TRANSMITMAILBOX(Mailbox));
    /* abort transmission */
    switch (Mailbox)
    {
    case (CAN_TXMAILBOX_0):
        CANx->TSTS |= CAN_TSTS_ABRQM0;
        break;
    case (CAN_TXMAILBOX_1):
        CANx->TSTS |= CAN_TSTS_ABRQM1;
        break;
    case (CAN_TXMAILBOX_2):
        CANx->TSTS |= CAN_TSTS_ABRQM2;
        break;
    default:
        break;
    }
}

/**
 * @brief  Receives a message.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param FIFONum Receive DATFIFO number, CAN_FIFO0 or CAN_FIFO1.
 * @param RxMessage pointer to a structure receive message which contains
 *                     CAN Id, CAN DLC, CAN datas and FMI number.
 */
void CAN_ReceiveMessage(CAN_Module* CANx, uint8_t FIFONum, CanRxMessage* RxMessage)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONum));
    /* Get the Id */
    RxMessage->IDE = (uint8_t)0x04 & CANx->sFIFOMailBox[FIFONum].RMI;
    if (RxMessage->IDE == CAN_Standard_Id)
    {
        RxMessage->StdId = (uint32_t)0x000007FF & (CANx->sFIFOMailBox[FIFONum].RMI >> 21);
    }
    else
    {
        RxMessage->ExtId = (uint32_t)0x1FFFFFFF & (CANx->sFIFOMailBox[FIFONum].RMI >> 3);
    }

    RxMessage->RTR = (uint8_t)0x02 & CANx->sFIFOMailBox[FIFONum].RMI;
    /* Get the DLC */
    RxMessage->DLC = (uint8_t)0x0F & CANx->sFIFOMailBox[FIFONum].RMDT;
    /* Get the FMI */
    RxMessage->FMI = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDT >> 8);
    /* Get the data field */
    RxMessage->Data[0] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONum].RMDL;
    RxMessage->Data[1] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDL >> 8);
    RxMessage->Data[2] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDL >> 16);
    RxMessage->Data[3] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDL >> 24);
    RxMessage->Data[4] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONum].RMDH;
    RxMessage->Data[5] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDH >> 8);
    RxMessage->Data[6] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDH >> 16);
    RxMessage->Data[7] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONum].RMDH >> 24);
    /* Release the DATFIFO */
    /* Release FIFO0 */
    if (FIFONum == CAN_FIFO0)
    {
        CANx->RFF0 |= CAN_RFF0_RFFOM0;
    }
    /* Release FIFO1 */
    else /* FIFONum == CAN_FIFO1 */
    {
        CANx->RFF1 |= CAN_RFF1_RFFOM1;
    }
}

/**
 * @brief  Releases the specified DATFIFO.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param FIFONum DATFIFO to release, CAN_FIFO0 or CAN_FIFO1.
 */
void CAN_ReleaseFIFO(CAN_Module* CANx, uint8_t FIFONum)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONum));
    /* Release FIFO0 */
    if (FIFONum == CAN_FIFO0)
    {
        CANx->RFF0 |= CAN_RFF0_RFFOM0;
    }
    /* Release FIFO1 */
    else /* FIFONum == CAN_FIFO1 */
    {
        CANx->RFF1 |= CAN_RFF1_RFFOM1;
    }
}

/**
 * @brief  Returns the number of pending messages.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param FIFONum Receive DATFIFO number, CAN_FIFO0 or CAN_FIFO1.
 * @return NbMessage : which is the number of pending message.
 */
uint8_t CAN_PendingMessage(CAN_Module* CANx, uint8_t FIFONum)
{
    uint8_t message_pending = 0;
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONum));
    if (FIFONum == CAN_FIFO0)
    {
        message_pending = (uint8_t)(CANx->RFF0 & (uint32_t)0x03);
    }
    else if (FIFONum == CAN_FIFO1)
    {
        message_pending = (uint8_t)(CANx->RFF1 & (uint32_t)0x03);
    }
    else
    {
        message_pending = 0;
    }
    return message_pending;
}

/**
  * @brief   Select the CAN Operation mode.
  * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
  * @param CAN_OperatingMode CAN Operating Mode. This parameter can be one
  *                            of @ref CAN_operating_mode enumeration.
  * @return status of the requested mode which can be
  *         - CAN_ModeSTS_Failed    CAN failed entering the specific mode
  *         - CAN_ModeSTS_Success   CAN Succeed entering the specific mode

  */
uint8_t CAN_OperatingModeReq(CAN_Module* CANx, uint8_t CAN_OperatingMode)
{
    uint8_t status = CAN_ModeSTS_Failed;

    /* Timeout for INAK or also for SLAK bits*/
    uint32_t timeout = INIAK_TIMEOUT;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_OPERATING_MODE(CAN_OperatingMode));

    if (CAN_OperatingMode == CAN_Operating_InitMode)
    {
        /* Request initialisation */
        CANx->MCTRL = (uint32_t)((CANx->MCTRL & (uint32_t)(~(uint32_t)CAN_MCTRL_SLPRQ)) | CAN_MCTRL_INIRQ);

        /* Wait the acknowledge */
        while (((CANx->MSTS & CAN_MODE_MASK) != CAN_MSTS_INIAK) && (timeout != 0))
        {
            timeout--;
        }
        if ((CANx->MSTS & CAN_MODE_MASK) != CAN_MSTS_INIAK)
        {
            status = CAN_ModeSTS_Failed;
        }
        else
        {
            status = CAN_ModeSTS_Success;
        }
    }
    else if (CAN_OperatingMode == CAN_Operating_NormalMode)
    {
        /* Request leave initialisation and sleep mode  and enter Normal mode */
        CANx->MCTRL &= (uint32_t)(~(CAN_MCTRL_SLPRQ | CAN_MCTRL_INIRQ));

        /* Wait the acknowledge */
        while (((CANx->MSTS & CAN_MODE_MASK) != 0) && (timeout != 0))
        {
            timeout--;
        }
        if ((CANx->MSTS & CAN_MODE_MASK) != 0)
        {
            status = CAN_ModeSTS_Failed;
        }
        else
        {
            status = CAN_ModeSTS_Success;
        }
    }
    else if (CAN_OperatingMode == CAN_Operating_SleepMode)
    {
        /* Request Sleep mode */
        CANx->MCTRL = (uint32_t)((CANx->MCTRL & (uint32_t)(~(uint32_t)CAN_MCTRL_INIRQ)) | CAN_MCTRL_SLPRQ);

        /* Wait the acknowledge */
        while (((CANx->MSTS & CAN_MODE_MASK) != CAN_MSTS_SLPAK) && (timeout != 0))
        {
            timeout--;
        }
        if ((CANx->MSTS & CAN_MODE_MASK) != CAN_MSTS_SLPAK)
        {
            status = CAN_ModeSTS_Failed;
        }
        else
        {
            status = CAN_ModeSTS_Success;
        }
    }
    else
    {
        status = CAN_ModeSTS_Failed;
    }

    return (uint8_t)status;
}

/**
 * @brief  Enters the low power mode.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @return status: CAN_SLEEP_Ok if sleep entered, CAN_SLEEP_Failed in an
 *                 other case.
 */
uint8_t CAN_EnterSleep(CAN_Module* CANx)
{
    uint8_t sleepstatus = CAN_SLEEP_Failed;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* Request Sleep mode */
    CANx->MCTRL = (((CANx->MCTRL) & (uint32_t)(~(uint32_t)CAN_MCTRL_INIRQ)) | CAN_MCTRL_SLPRQ);

    /* Sleep mode status */
    if ((CANx->MSTS & (CAN_MSTS_SLPAK | CAN_MSTS_INIAK)) == CAN_MSTS_SLPAK)
    {
        /* Sleep mode not entered */
        sleepstatus = CAN_SLEEP_Ok;
    }
    /* return sleep mode status */
    return (uint8_t)sleepstatus;
}

/**
 * @brief  Wakes the CAN up.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @return status:  CAN_WKU_Ok if sleep mode left, CAN_WKU_Failed in an
 *                  other case.
 */
uint8_t CAN_WakeUp(CAN_Module* CANx)
{
    uint32_t wait_slak   = SLPAK_TIMEOUT;
    uint8_t wakeupstatus = CAN_WKU_Failed;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* Wake up request */
    CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_SLPRQ;

    /* Sleep mode status */
    while (((CANx->MSTS & CAN_MSTS_SLPAK) == CAN_MSTS_SLPAK) && (wait_slak != 0x00))
    {
        wait_slak--;
    }
    if ((CANx->MSTS & CAN_MSTS_SLPAK) != CAN_MSTS_SLPAK)
    {
        /* wake up done : Sleep mode exited */
        wakeupstatus = CAN_WKU_Ok;
    }
    /* return wakeup status */
    return (uint8_t)wakeupstatus;
}

/**
 * @brief  Returns the CANx's last error code (LEC).
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @return CAN_ErrorCode: specifies the Error code :
 *                        - CAN_ERRORCODE_NoErr            No Error
 *                        - CAN_ERRORCODE_StuffErr         Stuff Error
 *                        - CAN_ERRORCODE_FormErr          Form Error
 *                        - CAN_ERRORCODE_ACKErr           Acknowledgment Error
 *                        - CAN_ERRORCODE_BitRecessiveErr  Bit Recessive Error
 *                        - CAN_ERRORCODE_BitDominantErr   Bit Dominant Error
 *                        - CAN_ERRORCODE_CRCErr           CRC Error
 *                        - CAN_ERRORCODE_SoftwareSetErr   Software Set Error
 */

uint8_t CAN_GetLastErrCode(CAN_Module* CANx)
{
    uint8_t errorcode = 0;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* Get the error code*/
    errorcode = (((uint8_t)CANx->ESTS) & (uint8_t)CAN_ESTS_LEC);

    /* Return the error code*/
    return errorcode;
}
/**
 * @brief  Returns the CANx Receive Error Counter (REC).
 * @note   In case of an error during reception, this counter is incremented
 *         by 1 or by 8 depending on the error condition as defined by the CAN
 *         standard. After every successful reception, the counter is
 *         decremented by 1 or reset to 120 if its value was higher than 128.
 *         When the counter value exceeds 127, the CAN controller enters the
 *         error passive state.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @return CAN Receive Error Counter.
 */
uint8_t CAN_GetReceiveErrCounter(CAN_Module* CANx)
{
    uint8_t counter = 0;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* Get the Receive Error Counter*/
    counter = (uint8_t)((CANx->ESTS & CAN_ESTS_RXEC) >> 24);

    /* Return the Receive Error Counter*/
    return counter;
}

/**
 * @brief  Returns the LSB of the 9-bit CANx Transmit Error Counter(TEC).
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @return LSB of the 9-bit CAN Transmit Error Counter.
 */
uint8_t CAN_GetLSBTransmitErrCounter(CAN_Module* CANx)
{
    uint8_t counter = 0;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* Get the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
    counter = (uint8_t)((CANx->ESTS & CAN_ESTS_TXEC) >> 16);

    /* Return the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
    return counter;
}

/**
 * @brief  Enables or disables the specified CANx interrupts.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param CAN_INT specifies the CAN interrupt sources to be enabled or disabled.
 *                 This parameter can be:
 *                 - CAN_INT_TME,
 *                 - CAN_INT_FMP0,
 *                 - CAN_INT_FF0,
 *                 - CAN_INT_FOV0,
 *                 - CAN_INT_FMP1,
 *                 - CAN_INT_FF1,
 *                 - CAN_INT_FOV1,
 *                 - CAN_INT_EWG,
 *                 - CAN_INT_EPV,
 *                 - CAN_INT_LEC,
 *                 - CAN_INT_ERR,
 *                 - CAN_INT_WKU or
 *                 - CAN_INT_SLK.
 * @param Cmd new state of the CAN interrupts.
 *                   This parameter can be: ENABLE or DISABLE.
 */
void CAN_INTConfig(CAN_Module* CANx, uint32_t CAN_INT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_INT(CAN_INT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected CANx interrupt */
        CANx->INTE |= CAN_INT;
    }
    else
    {
        /* Disable the selected CANx interrupt */
        CANx->INTE &= ~CAN_INT;
    }
}
/**
 * @brief  Checks whether the specified CAN flag is set or not.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param CAN_FLAG specifies the flag to check.
 *                   This parameter can be one of the following flags:
 *                  - CAN_FLAG_EWGFL
 *                  - CAN_FLAG_EPVFL
 *                  - CAN_FLAG_BOFFL
 *                  - CAN_FLAG_RQCPM0
 *                  - CAN_FLAG_RQCPM1
 *                  - CAN_FLAG_RQCPM2
 *                  - CAN_FLAG_FFMP1
 *                  - CAN_FLAG_FFULL1
 *                  - CAN_FLAG_FFOVR1
 *                  - CAN_FLAG_FFMP0
 *                  - CAN_FLAG_FFULL0
 *                  - CAN_FLAG_FFOVR0
 *                  - CAN_FLAG_WKU
 *                  - CAN_FLAG_SLAK
 *                  - CAN_FLAG_LEC
 * @return The new state of CAN_FLAG (SET or RESET).
 */
FlagStatus CAN_GetFlagSTS(CAN_Module* CANx, uint32_t CAN_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_GET_FLAG(CAN_FLAG));

    if ((CAN_FLAG & CAN_FLAGS_ESTS) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->ESTS & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
        {
            /* CAN_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* CAN_FLAG is reset */
            bitstatus = RESET;
        }
    }
    else if ((CAN_FLAG & CAN_FLAGS_MSTS) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->MSTS & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
        {
            /* CAN_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* CAN_FLAG is reset */
            bitstatus = RESET;
        }
    }
    else if ((CAN_FLAG & CAN_FLAGS_TSTS) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->TSTS & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
        {
            /* CAN_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* CAN_FLAG is reset */
            bitstatus = RESET;
        }
    }
    else if ((CAN_FLAG & CAN_FLAGS_RFF0) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->RFF0 & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
        {
            /* CAN_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* CAN_FLAG is reset */
            bitstatus = RESET;
        }
    }
    else /* if (CAN_FLAG & CAN_FLAGS_RFF1 != (uint32_t)RESET) */
    {
        /* Check the status of the specified CAN flag */
        if ((uint32_t)(CANx->RFF1 & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
        {
            /* CAN_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* CAN_FLAG is reset */
            bitstatus = RESET;
        }
    }
    /* Return the CAN_FLAG status */
    return bitstatus;
}

/**
 * @brief  Clears the CAN's pending flags.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param CAN_FLAG specifies the flag to clear.
 *                   This parameter can be one of the following flags:
 *                    - CAN_FLAG_RQCPM0
 *                    - CAN_FLAG_RQCPM1
 *                    - CAN_FLAG_RQCPM2
 *                    - CAN_FLAG_FFULL1
 *                    - CAN_FLAG_FFOVR1
 *                    - CAN_FLAG_FFULL0
 *                    - CAN_FLAG_FFOVR0
 *                    - CAN_FLAG_WKU
 *                    - CAN_FLAG_SLAK
 *                    - CAN_FLAG_LEC
 */
void CAN_ClearFlag(CAN_Module* CANx, uint32_t CAN_FLAG)
{
    uint32_t flagtmp = 0;
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_CLEAR_FLAG(CAN_FLAG));

    if (CAN_FLAG == CAN_FLAG_LEC) /* ESTS register */
    {
        /* Clear the selected CAN flags */
        CANx->ESTS = (uint32_t)RESET;
    }
    else /* MSTS or TSTS or RFF0 or RFF1 */
    {
        flagtmp = CAN_FLAG & 0x000FFFFF;

        if ((CAN_FLAG & CAN_FLAGS_RFF0) != (uint32_t)RESET)
        {
            /* Receive Flags */
            CANx->RFF0 = (uint32_t)(flagtmp);
        }
        else if ((CAN_FLAG & CAN_FLAGS_RFF1) != (uint32_t)RESET)
        {
            /* Receive Flags */
            CANx->RFF1 = (uint32_t)(flagtmp);
        }
        else if ((CAN_FLAG & CAN_FLAGS_TSTS) != (uint32_t)RESET)
        {
            /* Transmit Flags */
            CANx->TSTS = (uint32_t)(flagtmp);
        }
        else /* if ((CAN_FLAG & CAN_FLAGS_MSTS)!=(uint32_t)RESET) */
        {
            /* Operating mode Flags */
            CANx->MSTS = (uint32_t)(flagtmp);
        }
    }
}

/**
 * @brief  Checks whether the specified CANx interrupt has occurred or not.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param CAN_INT specifies the CAN interrupt source to check.
 *                  This parameter can be one of the following flags:
 *                 -  CAN_INT_TME
 *                 -  CAN_INT_FMP0
 *                 -  CAN_INT_FF0
 *                 -  CAN_INT_FOV0
 *                 -  CAN_INT_FMP1
 *                 -  CAN_INT_FF1
 *                 -  CAN_INT_FOV1
 *                 -  CAN_INT_WKU
 *                 -  CAN_INT_SLK
 *                 -  CAN_INT_EWG
 *                 -  CAN_INT_EPV
 *                 -  CAN_INT_BOF
 *                 -  CAN_INT_LEC
 *                 -  CAN_INT_ERR
 * @return The current state of CAN_INT (SET or RESET).
 */
INTStatus CAN_GetIntStatus(CAN_Module* CANx, uint32_t CAN_INT)
{
    INTStatus itstatus = RESET;
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_INT(CAN_INT));

    /* check the enable interrupt bit */
    if ((CANx->INTE & CAN_INT) != RESET)
    {
        /* in case the Interrupt is enabled, .... */
        switch (CAN_INT)
        {
        case CAN_INT_TME:
            /* Check CAN_TSTS_RQCPx bits */
            itstatus = CheckINTStatus(CANx->TSTS, CAN_TSTS_RQCPM0 | CAN_TSTS_RQCPM1 | CAN_TSTS_RQCPM2);
            break;
        case CAN_INT_FMP0:
            /* Check CAN_RFF0_FFMP0 bit */
            itstatus = CheckINTStatus(CANx->RFF0, CAN_RFF0_FFMP0);
            break;
        case CAN_INT_FF0:
            /* Check CAN_RFF0_FFULL0 bit */
            itstatus = CheckINTStatus(CANx->RFF0, CAN_RFF0_FFULL0);
            break;
        case CAN_INT_FOV0:
            /* Check CAN_RFF0_FFOVR0 bit */
            itstatus = CheckINTStatus(CANx->RFF0, CAN_RFF0_FFOVR0);
            break;
        case CAN_INT_FMP1:
            /* Check CAN_RFF1_FFMP1 bit */
            itstatus = CheckINTStatus(CANx->RFF1, CAN_RFF1_FFMP1);
            break;
        case CAN_INT_FF1:
            /* Check CAN_RFF1_FFULL1 bit */
            itstatus = CheckINTStatus(CANx->RFF1, CAN_RFF1_FFULL1);
            break;
        case CAN_INT_FOV1:
            /* Check CAN_RFF1_FFOVR1 bit */
            itstatus = CheckINTStatus(CANx->RFF1, CAN_RFF1_FFOVR1);
            break;
        case CAN_INT_WKU:
            /* Check CAN_MSTS_WKUINT bit */
            itstatus = CheckINTStatus(CANx->MSTS, CAN_MSTS_WKUINT);
            break;
        case CAN_INT_SLK:
            /* Check CAN_MSTS_SLAKINT bit */
            itstatus = CheckINTStatus(CANx->MSTS, CAN_MSTS_SLAKINT);
            break;
        case CAN_INT_EWG:
            /* Check CAN_ESTS_EWGFL bit */
            itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_EWGFL);
            break;
        case CAN_INT_EPV:
            /* Check CAN_ESTS_EPVFL bit */
            itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_EPVFL);
            break;
        case CAN_INT_BOF:
            /* Check CAN_ESTS_BOFFL bit */
            itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_BOFFL);
            break;
        case CAN_INT_LEC:
            /* Check CAN_ESTS_LEC bit */
            itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_LEC);
            break;
        case CAN_INT_ERR:
            /* Check CAN_MSTS_ERRINT bit */
            itstatus = CheckINTStatus(CANx->MSTS, CAN_MSTS_ERRINT);
            break;
        default:
            /* in case of error, return RESET */
            itstatus = RESET;
            break;
        }
    }
    else
    {
        /* in case the Interrupt is not enabled, return RESET */
        itstatus = RESET;
    }

    /* Return the CAN_INT status */
    return itstatus;
}

/**
 * @brief  Clears the CANx's interrupt pending bits.
 * @param CANx where x can be 1 or 2 to to select the CAN peripheral.
 * @param CAN_INT specifies the interrupt pending bit to clear.
 *                  -  CAN_INT_TME
 *                  -  CAN_INT_FF0
 *                  -  CAN_INT_FOV0
 *                  -  CAN_INT_FF1
 *                  -  CAN_INT_FOV1
 *                  -  CAN_INT_WKU
 *                  -  CAN_INT_SLK
 *                  -  CAN_INT_EWG
 *                  -  CAN_INT_EPV
 *                  -  CAN_INT_BOF
 *                  -  CAN_INT_LEC
 *                  -  CAN_INT_ERR
 */
void CAN_ClearINTPendingBit(CAN_Module* CANx, uint32_t CAN_INT)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_CLEAR_INT(CAN_INT));

    switch (CAN_INT)
    {
    case CAN_INT_TME:
        /* Clear CAN_TSTS_RQCPx (rc_w1)*/
        CANx->TSTS = CAN_TSTS_RQCPM0 | CAN_TSTS_RQCPM1 | CAN_TSTS_RQCPM2;
        break;
    case CAN_INT_FF0:
        /* Clear CAN_RFF0_FFULL0 (rc_w1)*/
        CANx->RFF0 = CAN_RFF0_FFULL0;
        break;
    case CAN_INT_FOV0:
        /* Clear CAN_RFF0_FFOVR0 (rc_w1)*/
        CANx->RFF0 = CAN_RFF0_FFOVR0;
        break;
    case CAN_INT_FF1:
        /* Clear CAN_RFF1_FFULL1 (rc_w1)*/
        CANx->RFF1 = CAN_RFF1_FFULL1;
        break;
    case CAN_INT_FOV1:
        /* Clear CAN_RFF1_FFOVR1 (rc_w1)*/
        CANx->RFF1 = CAN_RFF1_FFOVR1;
        break;
    case CAN_INT_WKU:
        /* Clear CAN_MSTS_WKUINT (rc_w1)*/
        CANx->MSTS = CAN_MSTS_WKUINT;
        break;
    case CAN_INT_SLK:
        /* Clear CAN_MSTS_SLAKINT (rc_w1)*/
        CANx->MSTS = CAN_MSTS_SLAKINT;
        break;
    case CAN_INT_EWG:
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_MSTS_ERRINT;
        /* Note : the corresponding Flag is cleared by hardware depending
                  of the CAN Bus status*/
        break;
    case CAN_INT_EPV:
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_MSTS_ERRINT;
        /* Note : the corresponding Flag is cleared by hardware depending
                  of the CAN Bus status*/
        break;
    case CAN_INT_BOF:
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_MSTS_ERRINT;
        /* Note : the corresponding Flag is cleared by hardware depending
                  of the CAN Bus status*/
        break;
    case CAN_INT_LEC:
        /*  Clear LEC bits */
        CANx->ESTS = RESET;
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_MSTS_ERRINT;
        break;
    case CAN_INT_ERR:
        /*Clear LEC bits */
        CANx->ESTS = RESET;
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_MSTS_ERRINT;
        /* Note : BOFF, EPVF and EWGF Flags are cleared by hardware depending
            of the CAN Bus status*/
        break;
    default:
        break;
    }
}

/**
 * @brief  Checks whether the CAN interrupt has occurred or not.
 * @param CAN_Reg specifies the CAN interrupt register to check.
 * @param Int_Bit specifies the interrupt source bit to check.
 * @return The new state of the CAN Interrupt (SET or RESET).
 */
static INTStatus CheckINTStatus(uint32_t CAN_Reg, uint32_t Int_Bit)
{
    INTStatus pendingbitstatus = RESET;

    if ((CAN_Reg & Int_Bit) != (uint32_t)RESET)
    {
        /* CAN_INT is set */
        pendingbitstatus = SET;
    }
    else
    {
        /* CAN_INT is reset */
        pendingbitstatus = RESET;
    }
    return pendingbitstatus;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
