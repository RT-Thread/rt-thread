/**
  ******************************************************************************
  * @file               ft32f4xx_fdcan.c
  * @author             FMD AE
  * @brief              FDCAN module driver.
  *               This file provides firmware functions to manage the following
  *                     functionalities of the Flexible DataRate Controller Area Network
  *               (FDCAN) peripheral::
  *                 + Initialization and de-initialization functions
  *                 + IO operation functions
  *                 + Peripheral Configuration and Control functions
  *               + Peripheral State and Error functions
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @data                   2025-03-06
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Initialize the FDCAN peripheral using FDCAN_Init function.
            (++) FDCAN_Init
            (++) FDCAN_DeInit
      (#) If needed , configure the reception filters and optional features using
          the following configuration functions:
            (++) FDCAN_ConfigFilter
            (++) FDCAN_ConfigRxFifoOverwrite
            (++) FDCAN_ConfigTimestampLocation
            (++) FDCAN_EnableTimestampCounter
            (++) FDCAN_ConfigTxDelayCompensation
            (++) FDCAN_EnableTxDelayCompensation
            (++) FDCAN_EnableISOMode
            (++) FDCAN_DisableISOMode

      (#) If needed , configure the TxBuffer and get RxBuffer and other value using
          the following configuration functions:
            (++) FDCAN_ConfigTxBuffer
            (++) FDCAN_GetRxBuffer
            (++) FDCAN_GetArbLostCap
            (++) FDCAN_GetErrorCnt

      (#) Start the FDCAN module using FDCAN_Start function. At this level
          the node is active on the bus: it can send and receive messages.

      (#) The following Tx control functions can only be called when the FDCAN
          module is started:
            (++) FDCAN_AddMessageToTxPTB
            (++) FDCAN_AddMessageToTxSTBFifoQ
            (++) FDCAN_AbortTxRequest

      (#) After having submitted a Tx request in Tx Fifo or Queue, it is possible to
          get STB Tx buffer status if used STB for transmission thanks to
          FDCAN_GetSecondaryBufferStatus API.
          It is then possible to abort transmission from STB which has been requested
          but not started yet using FDCAN_AbortTxRequest API.

      (#) When a message is received into the FDCAN message RAM, it can be
          retrieved using the FDCAN_GetRxMessage function.

      (#) Calling the FDCAN_Stop function stops the FDCAN module by entering
          it to initialization mode and re-enabling access to configuration
          registers through the configuration functions listed here above.

      (#) All other control functions can be called any time after initialization
          phase, no matter if the FDCAN module is started or stopped.

      *** Polling mode operation ***
      ==============================
    [..]
        (#) Reception and transmission states can be monitored via the following
            functions:
              (++) HAL_FDCAN_GetRxFifoFillStatus
              (++) FDCAN_GetSecondaryBufferStatus

      *** Interrupt mode operation ***
      ================================
      [..]
        (#) There are one interrupt line for each FDCAN: line 0.
            By default, all interrupts are assigned to line 0.

        (#) Notifications are activated using FDCAN_ActivateNotification
            function. Then, the process can be controlled through one of the
            available user callbacks: CANx_Handler.

  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_fdcan.h"
#include "ft32f4xx_rcc.h"


/**
  * @brief  Calculate each RAM block start address and size
  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @retval none
 */
//static void FDCAN_CalcultateBlockBaseAddresses(FDCAN_TypeDef* fdcan) //zhujia
//{
//}

//arbitration need handle process how or just leave function head file?

/*  ==============================================================================
              ##### Initialization and de-initialization functions #####
    ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the FDCAN.
      (+) De-initialize the FDCAN.
      (+) Enter FDCAN peripheral in power down mode.
*/
/**
  * @brief  Initializes the FDCAN peripheral according to the specified
  *         parameters in the FDCAN_InitTypeDef structure.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  fdcanInit: specifies the fdcan initial config value
  *             @arg FrameFormat: Specifies the FDCAN frame format
  *             The value of FrameFormat: FDCAN_FRAME_CLASSIC
  *                                       FDCAN_FRAME_FD_NO_BRS
  *                                       FDCAN_FRAME_FD_BRS
  *             @arg AutoPrimaryRetransmission: Enable or disable the automatic retransmission mode for PTB
  *             The value of AutoPrimaryRetransmission: ENABLE
  *                                                     DISABLE
  *             @arg AutoSecondaryRetransmission: Enable or disable the automatic retransmission mode for STB
  *             The value of AutoSecondaryRetransmission: ENABLE
  *                                                       DISABLE
  *             @arg TTCANMode: Enable or disable the Time Trigger CAN
  *             The value of TTCANMode: ENABLE
  *                                     DISABLE
  *             @arg FDCANSACK: Specifies the Self-ACKnowledge in External LoopBack mode
  *             The value of FDCANSACK: FDCAN_NO_SACK
  *                                     FDCAN_SACK
  *             @arg ReceiveBufferStoreAllFrames: Specifies the receive buffer stores all frames or normal frames
  *             The value of ReceiveBufferStoreAllFrames: FDCAN_RBUF_STORE_NORMAL_OPERATION
  *                                                       FDCAN_RBUF_STORE_ALL_DATA_FRAMES
  *             CAN_S_SEG_UNIT_SET: Config the follow parameter in this register:
  *             @arg NominalPrescaler: Specifies the value by which the oscillator frequency
  *                                    is divided for generating the nominal bit time quanta
  *             The value of NominalPrescaler: 1 and 255
  *             @arg NominalSyncJumpWidth: Specifies the maximum number of time quanta the FDCAN hardware
  *                                        is allowed to lengthen or shorten a bit to performresynchronization
  *             The value of NominalSyncJumpWidth: 2 and 127
  *             @arg NominalTimeSeg1: Specifies the number of time quanta in Bit Segment 1
  *             The value of NominalTimeSeg1: 3 and 255
  *             @arg NominalTimeSeg2: Specifies the number of time quanta in Bit Segment 2
  *             The value of NominalTimeSeg2: 2 and 127
  *             CAN_F_SEG_UNIT_SET: Config the follow parameter in this register:
  *             @arg DataPrescaler: Specifies the value by which the oscillator frequency
  *                                 is divided for generating the data bit time quanta
  *             The value of DataPrescaler: 1 and 255
  *             @arg DataSyncJumpWidth: Specifies the maximum number of time quanta the FDCAN hardware
  *                                     is allowed to lengthen or shorten a data bit to perform resynchronization
  *             The value of DataSyncJumpWidth: 2 and 15
  *             @arg DataTimeSeg1: Specifies the number of time quanta in Data Bit Segment 1
  *             The value of DataTimeSeg1: 3 and 31
  *             @arg DataTimeSeg2: Specifies the number of time quanta in Data Bit Segment 2
  *             The value of DataTimeSeg2: 2 and 15
  *             @arg TimeTriggerPrescaler: Specifies the value by which bit time is divided for time trigger timer
  *             The value of TimeTriggerPrescaler: FDCAN_TIME_TRIGGER_PRESCALER_1
  *                                                FDCAN_TIME_TRIGGER_PRESCALER_2
  *                                                FDCAN_TIME_TRIGGER_PRESCALER_4
  *                                                FDCAN_TIME_TRIGGER_PRESCALER_8
  *             @arg TimeTriggerType: Specifies the kind of trigger in Time Trigger mode CAN_TRIG_CFG[TTYPE]
  *             The value of TimeTriggerType: FDCAN_TTCAN_IMMEDIATE_TRIG
  *                                           FDCAN_TTCAN_TIME_TRIG
  *                                           FDCAN_TTCAN_SINGLE_SHOT_TRIG
  *                                           FDCAN_TTCAN_TRANSMIT_START_TRIG
  *                                           FDCAN_TTCAN_TRANSMIT_STOP_TRIG
  *             @arg TransmitEnableWindow: Specifies the ticks of transmit enable window CAN_TRIG_CFG[TEW]
  *             The value of TransmitEnableWindow: 0 and 15
  *             @arg TriggerTime: Specifies the cycle time for a trigger CAN_TRIG_CFG[TT_TRIG]
  *             The value of TriggerTime: 0 and 255
  *             @arg WatchTriggerTime: Specifies the cycle time for a watch trigger CAN_TRANS_INT_STAT[TT_WTRIG]
  *             The value of WatchTriggerTime: 0 and 255
  * @retval None.
  */

void FDCAN_Init(FDCAN_TypeDef* fdcan, FDCAN_InitTypeDef* fdcanInit)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));/*Check fdcan ?= FDCAN1/2/3/4*/

    /* Check Init parameters */
    assert_param(IS_FDCAN_FRAME_FORMAT(fdcanInit->FrameFormat));
    assert_param(IS_FUNCTIONAL_STATE(fdcanInit->AutoPrimaryRetransmission));
    assert_param(IS_FUNCTIONAL_STATE(fdcanInit->AutoSecondaryRetransmission));
    assert_param(IS_FDCAN_FDCANSACK(fdcanInit->FDCANSACK));
    assert_param(IS_FDCAN_RBUF_STORE_ALL(fdcanInit->ReceiveBufferStoreAllFrames));
    assert_param(IS_FDCAN_NOMINAL_PRESCALER(fdcanInit->NominalPrescaler));
    assert_param(IS_FDCAN_NOMINAL_SJW(fdcanInit->NominalSyncJumpWidth));
    assert_param(IS_FDCAN_NOMANAL_SEG1(fdcanInit->NominalTimeSeg1));
    assert_param(IS_FDCAN_NOMANAL_SEG2(fdcanInit->NominalTimeSeg2));
    assert_param(IS_FDCAN_DATA_PRESCALER(fdcanInit->DataPrescaler));
    assert_param(IS_FDCAN_DATA_SJW(fdcanInit->DataSyncJumpWidth));
    assert_param(IS_FDCAN_DATA_SEG1(fdcanInit->DataTimeSeg1));
    assert_param(IS_FDCAN_DATA_SEG2(fdcanInit->DataTimeSeg2));

    if (fdcanInit->TTCANMode == ENABLE) /*The TTCAN is set*/
    {
        assert_param(IS_FDCAN_TTCAN_PRESCALER(fdcanInit->TimeTriggerPrescaler));
        assert_param(IS_FDCAN_TTCAN_TYPE(fdcanInit->TimeTriggerType));
        assert_param(IS_FDCAN_TTCAN_TR_EN_WIN(fdcanInit->TransmitEnableWindow));
        assert_param(IS_FDCAN_TTCAN_TRIGGER_TIME(fdcanInit->TriggerTime));
        assert_param(IS_FDCAN_TTCAN_WATCH_TIME(fdcanInit->WatchTriggerTime));

        /* Set the value by which bit time is divided for time trigger timer */
        fdcan->CAN_INT_FLAG2 |= fdcanInit->TimeTriggerPrescaler;

        uint32_t CAN_TRG_CFG_VALUE;
        CAN_TRG_CFG_VALUE = fdcan->CAN_TRIG_CFG;
        CAN_TRG_CFG_VALUE = (CAN_TRG_CFG_VALUE & ~CAN_TRIG_CFG_TTPTR);
        /* Set the cycle time for a trigger */
        /* Set the kind of trigger in Time Trigger mode */
        /* Set the ticks of transmit enable window */
        fdcan->CAN_TRIG_CFG  |= ((fdcanInit->TriggerTime << 16U)         |
                                 fdcanInit->TimeTriggerType             |
                                 (fdcanInit->TransmitEnableWindow << 12U) |
                                 CAN_TRG_CFG_VALUE)                     ;
    }

    if (fdcanInit->WatchTriggerTime != DISABLE)
    {
        /* Set the cycle time for a watch trigger */
        uint32_t CAN_TRANS_INT_STAT_VALUE;
        CAN_TRANS_INT_STAT_VALUE = fdcan->CAN_TRANS_INT_STAT ;
        CAN_TRANS_INT_STAT_VALUE = (CAN_TRANS_INT_STAT_VALUE & ~CAN_TRANS_INT_STAT_WTRIG);
        fdcan->CAN_TRANS_INT_STAT  = (CAN_TRANS_INT_STAT_VALUE | fdcanInit->WatchTriggerTime);
    }

    /*  Set the nominal bit timing register */
    fdcan->CAN_S_SEG_UNIT_SET = (((fdcanInit->NominalPrescaler) << 24U) |
                                 ((fdcanInit->NominalSyncJumpWidth) << 16U) |
                                 ((fdcanInit->NominalTimeSeg2) <<  8U) |
                                 ((fdcanInit->NominalTimeSeg1) <<  0U));

    /* If FD operation with BRS is selected, set the data bit timing register */
    fdcan->CAN_F_SEG_UNIT_SET = (((fdcanInit->DataPrescaler) << 24U) |
                                 ((fdcanInit->DataSyncJumpWidth) << 16U) |
                                 ((fdcanInit->DataTimeSeg2) <<  8U) |
                                 ((fdcanInit->DataTimeSeg1) <<  0U));

    /* If FD_CAN AutoPrimaryRetransmission is ENABLE */
    if (fdcanInit->AutoPrimaryRetransmission == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_TPSS;
    }

    /* If FD_CAN AutoSecondaryRetransmission is ENABLE */
    if (fdcanInit->AutoSecondaryRetransmission == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_TSSS;
    }

    if (fdcanInit->FDCANSACK == FDCAN_SACK)
    {
        /* Set FD_CAN Self_Acknowledg */
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_SACK;
    }

    if (fdcanInit->ReceiveBufferStoreAllFrames == ENABLE)
    {
        /* Set FD_CAN receive buffer stores all frames */
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_RBALL;
    }
}
/**
  * @brief  Deinitializes the CANx peripheral registers to their default
  *         reset values.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @retval None
  */

void FDCAN_DeInit(FDCAN_TypeDef* fdcan)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (fdcan == FDCAN1)
    {
        /* Enable CAN1 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN1, ENABLE);
        /* Release CAN1 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN1, DISABLE);
    }

    if (fdcan == FDCAN2)
    {
        /* Enable CAN2 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN2, ENABLE);
        /* Release CAN2 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN2, DISABLE);
    }

    if (fdcan == FDCAN3)
    {
        /* Enable CAN3 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN3, ENABLE);
        /* Release CAN3 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN3, DISABLE);
    }

    if (fdcan == FDCAN4)
    {
        /* Enable CAN4 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN4, ENABLE);
        /* Release CAN4 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1PeriphRst_CAN4, DISABLE);
    }
}

/**
  * @brief  config can_ctrl in reset or run mode.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_Reset(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_RESET;
    }
    else
    {
        fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_RESET;
    }
}

/**
  * @brief  config can_ctrl mode.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  Mode: Specifies the FDCAN mode
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_MODE_NORMAL
  *             @arg FDCAN_MODE_LOM
  *             @arg FDCAN_MODE_INTERNAL_LOOPBACK
  *             @arg FDCAN_MODE_EXTERNAL_LOOPBACK
  * @retval None
  */
void FDCAN_ConfigMode(FDCAN_TypeDef* fdcan, uint32_t Mode)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_MODE(Mode));

    /* Set FD_CAN Mode */
    fdcan->CAN_CMD_CTRL |= Mode;
}



/**
  * @brief  config can_ctrl in reset or run mode.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  ReceiveBufferAlmostFullWarningLimit: Specifies the limit value of recevie buffer almost full
  *             The value of ReceiveBufferAlmostFullWarningLimit: 1 and 6
  * @retval None
  */
void FDCAN_SetRxBufAFWL(FDCAN_TypeDef* fdcan, uint32_t ReceiveBufferAlmostFullWarningLimit)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_RBUF_AF_LIMIT(ReceiveBufferAlmostFullWarningLimit));

    /* get can int flag1 value */
    uint32_t can_int_flag1_value;
    can_int_flag1_value = fdcan->CAN_INT_FLAG1;

    /* clear can int flag in this reg*/
    can_int_flag1_value = can_int_flag1_value & CAN_INT_FLAG1_MASK;
    /* clear afwl value */
    can_int_flag1_value = can_int_flag1_value & ~CAN_INT_FLAG1_AFWL;
    fdcan->CAN_INT_FLAG1 = (can_int_flag1_value | (ReceiveBufferAlmostFullWarningLimit << 28U));
}

/**
  * @brief  config can_ctrl in reset or run mode.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  ProgrammableErrorWarningLimit: Specifies the limit value of programmable error warning
  *             The value of ProgrammableErrorWarningLimit: 0 and 15
  * @retval None
  */

void FDCAN_SetEWL(FDCAN_TypeDef* fdcan, uint32_t ProgrammableErrorWarningLimit)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_PROG_ERROR_WARN_LIMIT(ProgrammableErrorWarningLimit));

    /* get can int flag1 value */
    uint32_t can_int_flag1_value;
    can_int_flag1_value = fdcan->CAN_INT_FLAG1;

    /* clear can int flag in this reg*/
    can_int_flag1_value = can_int_flag1_value & CAN_INT_FLAG1_MASK;
    /* clear ewl value */
    can_int_flag1_value = can_int_flag1_value & ~CAN_INT_FLAG1_EWL;

    /* Config ewl value */
    fdcan->CAN_INT_FLAG1 = (can_int_flag1_value | (ProgrammableErrorWarningLimit << 24U));
}

/**
  * @brief  config can_ctrl in reset or run mode.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  TransBufferSelect: Selects the trransmit buffer
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_SELECT_PTB
  *             @arg FDCAN_SELECT_STB
  * @retval None
  */
void FDCAN_TransBufferSelect(FDCAN_TypeDef* fdcan, uint32_t TransBufferSelect)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_BUF_SEL(TransBufferSelect));
    if (TransBufferSelect == FDCAN_SELECT_STB)
    {
        /* Set FD_CAN TransBufferSelect is STB */
        fdcan->CAN_CMD_CTRL |= FDCAN_SELECT_STB;
    }
    else if (TransBufferSelect == FDCAN_SELECT_PTB)
    {
        /* Set FD_CAN TransBufferSelect is PTB */
        fdcan->CAN_CMD_CTRL &= ~FDCAN_SELECT_STB;
    }
}

/**
  * @brief  Select TTCAN trans buffer mode
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_TTCANTransBufferMode(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_TTTBM;
    }
    else
    {
        fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_TTTBM;
    }
}


/**
  * @brief  Start PTB trans
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_PTBTrans(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_TPE;
    }
    else
    {
        fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_TPE;
    }
}

/**
  * @brief  Abort PTB trans
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_PTBAbort(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_TPA;
    }
    else
    {
        fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_TPA;
    }
}

/**
  * @brief  Start STB trans
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  STBFifoPriorityMode the STB transmit fifo or priority Mode selection
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_STB_FIFO: stb in fifo mode
  *             @arg FDCAN_STB_PRIORITY: stb in priority mode
  * @retval None
  */
void FDCAN_TransSTBMode(FDCAN_TypeDef* fdcan, uint32_t STBFifoPriorityMode)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_STB_FP_MODE(STBFifoPriorityMode));

    /* Set FD_CAN STB transmit is fifo or priority */
    fdcan->CAN_CMD_CTRL |= STBFifoPriorityMode;

}

/**
  * @brief  Start STB trans
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  STBTransmitOneAllMode:Specifies the STB transmit one frame or all frame Mode selection
  *             @arg  FDCAN_STB_NO_TRANSMIT
  *             @arg  FDCAN_STB_NO_TRANSMIT_ONE
  *             @arg  FDCAN_STB_NO_TRANSMIT_ALL
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_STBTrans(FDCAN_TypeDef* fdcan, uint32_t STBTransmitOneAllMode, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_STB_OA_MODE(STBTransmitOneAllMode));

    uint32_t can_cmd_ctrl_value;
    can_cmd_ctrl_value = fdcan->CAN_CMD_CTRL;
    /* clr tsnext value */
    can_cmd_ctrl_value = (can_cmd_ctrl_value & (~CAN_CMD_CTRL_TSNEXT));

    if (NewState == ENABLE)
    {
        /* Set FD_CAN STB transmit is one or all and don't set tsnext */
        fdcan->CAN_CMD_CTRL = (can_cmd_ctrl_value | STBTransmitOneAllMode);
    }
    else
    {
        fdcan->CAN_CMD_CTRL = (can_cmd_ctrl_value & (~STBTransmitOneAllMode));
    }
}

/**
  * @brief  Abort STB trans
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_STBAbort(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_TSA;
    }
    else
    {
        fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_TSA;
    }
}

/**
  * @brief  Get arbitration lost position
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @retval None
  */
uint8_t FDCAN_GetArbLostPosition(FDCAN_TypeDef* fdcan)
{
    uint8_t temp;
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    temp = ((fdcan->CAN_ERR_CNT) & CAN_ERR_CNT_ALC);

    return temp;
}

/**
  * @brief  Get kind of error
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @retval None
  */
uint8_t FDCAN_GetKindOfError(FDCAN_TypeDef* fdcan)
{
    uint8_t temp;
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    temp = (((fdcan->CAN_ERR_CNT) & CAN_ERR_CNT_KOER) >> 5U);

    return temp;
}

/**
  * @brief  Release RxBuffer
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_RxBufRelease(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_RREL;
    }
    else
    {
        fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_RREL;
    }
}

/**
  * @brief  Enable CAN standby
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's reset.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_StandbyMode(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_STBY;
    }
    else
    {
        fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_STBY;
    }
}

/**
  * @brief  Enable CAN standby
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  FDCAN_ReceiveBufferOverflow_Mode: specifies the ROM value.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_RECEIVE_OVERFLOW_OVERWRITTEN: ROM=0,The oldest message will be overwritten
  *             @arg FDCAN_RECEIVE_OVERFLOW_DISCARD:     ROM=1,The new message will not be stored
  * @retval None
  */
void FDCAN_RbufOverFlowMode(FDCAN_TypeDef* fdcan, uint32_t FDCAN_ReceiveBufferOverflow_Mode)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_RECEIVE_BUFFER_OVERFLOW_MODE(FDCAN_ReceiveBufferOverflow_Mode));

    fdcan->CAN_CMD_CTRL |= FDCAN_ReceiveBufferOverflow_Mode;
}


/** @defgroup FDCAN_Exported_Functions_Group2 Configuration functions
 *  @brief    FDCAN Configuration functions.
 *
@verbatim
  ==============================================================================
              ##### Configuration functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) FDCAN_ConfigFilter                  : Configure the FDCAN reception filters
      (+) FDCAN_ConfigRxFifoOverwrite         : Configure the Rx FIFO operation mode
      (+) FDCAN_ConfigTimestampLocation       : Configure the timestamp Location in SOF or EOF
      (+) FDCAN_EnableTimestampCounter        : Enable or Disable the timestamp counter
      (+) FDCAN_ConfigTxDelayCompensation     : Configure the transmitter delay compensation
      (+) FDCAN_EnableTxDelayCompensation     : Enable or Disable the transmitter delay compensation
      (+) FDCAN_EnableISOMode                 : Enable ISO 11898-1 protocol mode
      (+) FDCAN_DisableISOMode                : Disable ISO 11898-1 protocol mode

@endverbatim
  * @{
  */

/**
  * @brief  Configure the FDCAN reception filter according to the specified
  *         parameters in the FDCAN_FilterTypeDef structure.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  sFilterConfig pointer to an FDCAN_FilterTypeDef structure that
  *         contains the filter configuration information
  *          This parameter can be any combination of the following values:
  *             @arg FilterAddress: Specifies the filter which will be initialized
  *             The value of FilterAddress: 0 and 15
  *             @arg SelectAcceptanceMask: Enable or disable the filter mask
  *             The value of SelectAcceptanceMask: ENABLE
  *                                                DISABLE
  *             @arg FilterAcceptanceCODE: Specifies the filter identification
  *             The value of FilterAcceptanceCODE: 0 and 0x7FF for standard frames
  *                                                0 and 0x1FFFFFFF for extended frames
  *             @arg FilterAcceptanceMASK: Specifies the filter acceptance mask
  *                                    1: acceptance check for these bis of receive ID with AC_CODE disable
  *                                    0: acceptance check for these bis of receive ID with AC_CODE enable
  *             The value of FilterAcceptanceMASK: 0 and 0x7FF for standard frames
  *                                                0 and 0x1FFFFFFF for extended frames
  *             @arg FilterAcceptanceMaskIDECheck: Specifies the filter acceptance mask IDE bit check enable
  *             The value of FilterAcceptanceMaskIDECheck: FDCAN_ACCEP_MASK_AIDE_DISABLE
  *                                                        FDCAN_ACCEP_MASK_AIDE_ENABLE
  *             @arg FilterAcceptanceMaskIDE: Specifies the filter acceptance mask IDE bit value
  *             The value of FilterAcceptanceMaskIDE: FDCAN_ACCEP_MASK_IDE_STANDARD
  *                                                   FDCAN_ACCEP_MASK_IDE_EXTENDED
  * @retval HAL status
  */

void FDCAN_ConfigFilter(FDCAN_TypeDef* fdcan, FDCAN_FilterTypeDef* sFilterConfig)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_FILTER_ADDR(sFilterConfig->FilterAddress));
    assert_param(IS_FUNCTIONAL_STATE(sFilterConfig->SelectAcceptanceMask));
    assert_param(IS_FDCAN_FILTER_ACODE(sFilterConfig->FilterAcceptanceCODE));
    assert_param(IS_FDCAN_FILTER_AMASK(sFilterConfig->FilterAcceptanceMASK));
    assert_param(IS_FDCAN_FILTER_AMASK_IDEE(sFilterConfig->FilterAcceptanceMaskIDECheck));
    assert_param(IS_FDCAN_FILTER_AMASK_IDE(sFilterConfig->FilterAcceptanceMaskIDE));

    uint32_t CAN_FILTER_CTRL_VALUE;
    /* GET CAN_FILTER_CTRL_VALUE */
    CAN_FILTER_CTRL_VALUE = fdcan->CAN_FILTER_CTRL;
    /* CLR ACFADR BUT REMAIN OTHERS BITS*/
    CAN_FILTER_CTRL_VALUE = (CAN_FILTER_CTRL_VALUE & ~CAN_FILTER_CTRL_ACFADR);
    /* CLR SELMASK */
    CAN_FILTER_CTRL_VALUE = (CAN_FILTER_CTRL_VALUE & ~CAN_FILTER_CTRL_SELMASK);
    /* Set filter address, choose which filter be set */
    fdcan->CAN_FILTER_CTRL = (CAN_FILTER_CTRL_VALUE | sFilterConfig->FilterAddress);

    /* Set acceptance code */
    fdcan->CAN_ACF = (sFilterConfig->FilterAcceptanceCODE);

    /* If select acceptance mask, set mask value */
    if (sFilterConfig->SelectAcceptanceMask == ENABLE)
    {
        /* Select MASK, CAN_ACF Point to AMASK */
        fdcan->CAN_FILTER_CTRL |= CAN_FILTER_CTRL_SELMASK;

        /* Set mask value, 0 and 0x7FF for standard frames, 0 and 0x1FFFFFFF for extended frames */
        fdcan->CAN_ACF = (sFilterConfig->FilterAcceptanceMASK);
    }

    /* If FilterAcceptanceMaskIDECheck is 0 AIDEE=0, Accept Filter accepts both standard and extended frames*/
    /* If FilterAcceptanceMaskIDECheck is 1 AIDEE=1, set FilterAcceptanceMaskIDE(accepts standard or extended frames)*/
    if (sFilterConfig->FilterAcceptanceMaskIDECheck == FDCAN_ACCEP_MASK_AIDE_ENABLE)
    {
        /* Set AIDEE, If AIDEE=1, Accept Filter accepts standard and extended frames decided by AIDE*/
        fdcan->CAN_ACF |= CAN_ACF_AIDEE;

        /* Set AIDE, If AIDEE=1,AIDE=0, only accept standard frames */
        /* Set AIDE, If AIDEE=1,AIDE=1, only accept extended frames */
        if (sFilterConfig->FilterAcceptanceMaskIDE == FDCAN_ACCEP_MASK_IDE_EXTENDED)
        {
            fdcan->CAN_ACF |= CAN_ACF_AIDE;
        }
        else if (sFilterConfig->FilterAcceptanceMaskIDE == FDCAN_ACCEP_MASK_IDE_STANDARD)
        {
            fdcan->CAN_ACF &= ~CAN_ACF_AIDE;
        }
    }
}

/**
  * @brief  Configure the FDCAN reception filter according to the specified
  *         parameters in the FDCAN_FilterTypeDef structure.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  FDCAN_ACE: specifies the filter.
  *           This parameter can be any combination of the following values:
  *             @arg FDCAN_CAN_FILTER0:  choose filter0
  *             @arg FDCAN_CAN_FILTER1:  choose filter1
  *             @arg FDCAN_CAN_FILTER2:  choose filter2
  *             @arg FDCAN_CAN_FILTER3:  choose filter3
  *             @arg FDCAN_CAN_FILTER4:  choose filter4
  *             @arg FDCAN_CAN_FILTER5:  choose filter5
  *             @arg FDCAN_CAN_FILTER6:  choose filter6
  *             @arg FDCAN_CAN_FILTER7:  choose filter7
  *             @arg FDCAN_CAN_FILTER8:  choose filter8
  *             @arg FDCAN_CAN_FILTER9:  choose filter9
  *             @arg FDCAN_CAN_FILTER10: choose filter10
  *             @arg FDCAN_CAN_FILTER11: choose filter11
  *             @arg FDCAN_CAN_FILTER12: choose filter12
  *             @arg FDCAN_CAN_FILTER13: choose filter13
  *             @arg FDCAN_CAN_FILTER14: choose filter14
  *             @arg FDCAN_CAN_FILTER15: choose filter15
  *             @arg FDCAN_CAN_FILTER_ALL: choose all filter
  * @param  NewState: new state of the specified instance's TxDelay.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_EnableFilter(FDCAN_TypeDef* fdcan, uint32_t FDCAN_ACE, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_FILTER_ACE(FDCAN_ACE));

    /* Set the Fdcan Filter NewState */
    if (NewState == ENABLE)
    {
        fdcan->CAN_FILTER_CTRL |= FDCAN_ACE;
    }
    else
    {
        fdcan->CAN_FILTER_CTRL &= ~FDCAN_ACE;
    }
}

/**
  * @brief  Select the Receive Buffer accept mode while full.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  FdcanRbOverMode: specifies the ROM.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_RECEIVE_OVERFLOW_OVERWRITTEN: the new message will be writen in receive buffer
  *             @arg FDCAN_RECEIVE_OVERFLOW_DISCARD: the new message will not be written
  * @retval None
  */
void FDCAN_ConfigRxFifoOverwrite(FDCAN_TypeDef* fdcan, uint32_t FdcanRbOverMode)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_RBUF_OVERFLOW_MODE(FdcanRbOverMode));

    /* Set the Receive Buffer write mode while it's full */
    fdcan->CAN_CMD_CTRL |= FdcanRbOverMode;
}


/**
  * @brief  Select the Fdcan TimeStamp location.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  FdcanTimeStampLocation: specifies the TimeStamp Location.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_TIMESTAMP_SOF: the TimeStamp in SOF
  *             @arg FDCAN_TIMESTAMP_EOF: the TimeStamp in EOF
  * @retval None
  */
void FDCAN_ConfigTimestampLocation(FDCAN_TypeDef* fdcan, uint32_t FdcanTimeStampLocation)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_TIME_STAMP_LOCATION(FdcanTimeStampLocation));

    /* Set the Fdcan TimeStamp Location SOF or EOF*/
    fdcan->CAN_FILTER_CTRL |= FdcanTimeStampLocation;
}

/**
  * @brief  Enable or Disable the Fdcan TimeStamp.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's timestamp.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_EnableTimestampCounter(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Set the Fdcan TimeStamp NewState */
    if (NewState == ENABLE)
    {
        fdcan->CAN_FILTER_CTRL |= FDCAN_TIMESTAMP_ENABLE;
    }
    else
    {
        fdcan->CAN_FILTER_CTRL &= ~FDCAN_TIMESTAMP_ENABLE;
        /* wait timestamp disable success */
        while ((fdcan->CAN_FILTER_CTRL & FDCAN_TIMESTAMP_DISABLE) == FDCAN_TIMESTAMP_DISABLE);
    }
}

/**
  * @brief  Config the txdelay value.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  FdcanTxDelayValue: specifies the TXDelay value.
  *          This parameter can be the range of 0~0x7F
  * @retval None
  */
void FDCAN_ConfigTxDelayCompensation(FDCAN_TypeDef* fdcan, uint32_t FdcanTxDelayValue)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_TXDELAY_VALUE(FdcanTxDelayValue));

    /* Set the Fdcan TimeStamp Location */
    fdcan->CAN_ERR_CNT |= (FdcanTxDelayValue << 8U);
}

/**
  * @brief  Enable or Disable the txdelay.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  NewState: new state of the specified instance's TxDelay.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FDCAN_EnableTxDelayCompensation(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Set the Fdcan TxDelay NewState*/
    if (NewState == ENABLE)
    {
        fdcan->CAN_ERR_CNT |= FDCAN_TXDELAY_ENABLE;
    }
    else
    {
        fdcan->CAN_ERR_CNT &= ~FDCAN_TXDELAY_ENABLE;
        /* wait txdelay disable success */
        while ((fdcan->CAN_ERR_CNT & FDCAN_TXDELAY_DISABLE) == FDCAN_TXDELAY_DISABLE);
    }
}

/**
  * @brief  Enable ISO 11898-1 protocol mode.
  *         CAN FD frame format is according to ISO 11898-1 standard.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @retval None
  */
void FDCAN_EnableISOMode(FDCAN_TypeDef* fdcan)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Enable ISO mode */
    fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_FD_ISO;

}

/**
  * @brief  Disable ISO 11898-1 protocol mode.
  *         CAN FD frame format is according to Bosch CAN FD specification.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @retval None
  */
void FDCAN_DisableISOMode(FDCAN_TypeDef* fdcan)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Disable ISO mode */
    fdcan->CAN_CMD_CTRL &= ~CAN_CMD_CTRL_FD_ISO;

    /* Wait ISO bit clear */
    while ((fdcan->CAN_CMD_CTRL & CAN_CMD_CTRL_FD_ISO) == CAN_CMD_CTRL_FD_ISO);
}


/** @defgroup FDCAN_Exported_Functions_Group3 Configuration TxBuffer And Get RxBuffer
 *  @brief    FDCAN Configuration TxBuffer And Get RxBuffer.
 *
@verbatim
  ==============================================================================
              ##### Configuration functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) FDCAN_ConfigTxBuffer: Configure the FDCAN TxBuffer
      (+) FDCAN_GetRxBuffer: Get the FDCAN RxBuffer
      (+) FDCAN_GetArbLostCap: Get the FDCAN ArbitrationLostCapture
      (+) FDCAN_GetErrorCnt: Get the FDCAN ErrorCounter TECNT, RECNT and KOER
      (+) FDCAN_ConfigTsnext: Set TSNEXT and Clear by hardware

      @endverbatim
  * @{
  */

/**
  * @brief  Config TxBuffer.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  TxHeader: specifies the TxBuffer config.
  *             @arg Identifier: Specifies the identifier
  *             The value of Identifier: 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
  *                                      0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
  *             @arg IdType: Specifies the identifier type for the transmitted message
  *             The value of IdType: FDCAN_STANDARD_ID
  *                                  FDCAN_EXTENDED_ID
  *             @arg TxFrameType: Specifies the frame type of the transmitted message
  *             The value of TxFrameType: FDCAN_DATA_FRAME
  *                                       FDCAN_REMOTE_FRAME
  *             @arg DataLength: Specifies the data length of the transmitted frame
  *             The value of DataLength: FDCAN_DLC_BYTES_0
  *                                      FDCAN_DLC_BYTES_1
  *                                      FDCAN_DLC_BYTES_2
  *                                      FDCAN_DLC_BYTES_3
  *                                      FDCAN_DLC_BYTES_4
  *                                      FDCAN_DLC_BYTES_5
  *                                      FDCAN_DLC_BYTES_6
  *                                      FDCAN_DLC_BYTES_7
  *                                      FDCAN_DLC_BYTES_8
  *                                      FDCAN_DLC_BYTES_12
  *                                      FDCAN_DLC_BYTES_16
  *                                      FDCAN_DLC_BYTES_20
  *                                      FDCAN_DLC_BYTES_24
  *                                      FDCAN_DLC_BYTES_32
  *                                      FDCAN_DLC_BYTES_48
  *                                      FDCAN_DLC_BYTES_64
  *             @arg BitRateSwitch:  Specifies whether the Tx frame is transmitted with or without bit rate switching
  *             The value of BitRateSwitch: FDCAN_BRS_OFF
  *                                         FDCAN_BRS_ON
  *             @arg FDFormat: Specifies whether the Tx frame is transmitted in classic or FD format
  *             The value of FDFormat: FDCAN_CLASSIC_CAN
  *                                    FDCAN_FD_CAN
  *             @arg TTSEN: Specifies the enable if transmit Time-Stamp in CiA 603
  *             The value of TTSEN: FDCAN_TTS_DISABLE
  *                                 FDCAN_TTS_ENABLE
  * @retval None
  */
void FDCAN_ConfigTxBuffer(FDCAN_TypeDef* fdcan, FDCAN_TxHeaderTypeDef* TxHeader, uint8_t message_data[16][4])
{
    uint32_t i;

    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_ID(TxHeader->Identifier));
    assert_param(IS_FDCAN_IDTYPE(TxHeader->IdType));
    assert_param(IS_FDCAN_FRAME_TYPE(TxHeader->TxFrameType));
    assert_param(IS_FDCAN_TYPE(TxHeader->FDFormat));
    assert_param(IS_FDCAN_BRS(TxHeader->BitRateSwitch));
    assert_param(IS_FDCAN_DATA_LENGTH(TxHeader->DataLength));
    assert_param(IS_FDCAN_TTS_STATE(TxHeader->TTSEN));

    /* Config frame ID and TTSEN */
    fdcan->CAN_TRANSMIT_BUFFER0 = (TxHeader->Identifier |
                                   TxHeader->TTSEN);

    /* Config IDE RTR FDF BRS and DLC*/
    fdcan->CAN_TRANSMIT_BUFFER1 = (TxHeader->IdType        | /* Config id type */
                                   TxHeader->TxFrameType   | /* Config frame type */
                                   TxHeader->FDFormat      | /* Config fdcan format */
                                   TxHeader->BitRateSwitch | /* Config fdcan bit rate switch */
                                   TxHeader->DataLength);    /* Config date length */

    if (TxHeader->TxFrameType == FDCAN_DATA_FRAME)
    {
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_1)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_2)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) |
                                            (message_data[0][1] << 8) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_3)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) |
                                            (message_data[0][1] << 8) |
                                            (message_data[0][2] << 16) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_4)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) |
                                            (message_data[0][1] << 8) |
                                            (message_data[0][2] << 16) |
                                            (message_data[0][3] << 24) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_5)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) |
                                            (message_data[0][1] << 8) |
                                            (message_data[0][2] << 16) |
                                            (message_data[0][3] << 24) ;

            fdcan->CAN_TRANSMIT_BUFFER[1] = (message_data[1][0]) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_6)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) |
                                            (message_data[0][1] << 8) |
                                            (message_data[0][2] << 16) |
                                            (message_data[0][3] << 24) ;

            fdcan->CAN_TRANSMIT_BUFFER[1] = (message_data[1][0]) |
                                            (message_data[1][1] << 8) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_7)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) |
                                            (message_data[0][1] << 8) |
                                            (message_data[0][2] << 16) |
                                            (message_data[0][3] << 24) ;

            fdcan->CAN_TRANSMIT_BUFFER[1] = (message_data[1][0]) |
                                            (message_data[1][1] << 8) |
                                            (message_data[1][2] << 16) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_8)
        {
            fdcan->CAN_TRANSMIT_BUFFER[0] = (message_data[0][0]) |
                                            (message_data[0][1] << 8) |
                                            (message_data[0][2] << 16) |
                                            (message_data[0][3] << 24) ;

            fdcan->CAN_TRANSMIT_BUFFER[1] = (message_data[1][0]) |
                                            (message_data[1][1] << 8) |
                                            (message_data[1][2] << 16) |
                                            (message_data[1][3] << 24) ;
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_12)
        {
            if (TxHeader->FDFormat != FDCAN_FD_CAN)
            {
                for (i = 0; i < 2; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
            else
            {
                for (i = 0; i < 3; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_16)
        {
            if (TxHeader->FDFormat != FDCAN_FD_CAN)
            {
                for (i = 0; i < 2; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
            else
            {
                for (i = 0; i < 4; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_20)
        {
            if (TxHeader->FDFormat != FDCAN_FD_CAN)
            {
                for (i = 0; i < 2; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
            else
            {
                for (i = 0; i < 5; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_24)
        {
            if (TxHeader->FDFormat != FDCAN_FD_CAN)
            {
                for (i = 0; i < 2; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
            else
            {
                for (i = 0; i < 6; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_32)
        {
            if (TxHeader->FDFormat != FDCAN_FD_CAN)
            {
                for (i = 0; i < 2; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
            else
            {
                for (i = 0; i < 8; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_48)
        {
            if (TxHeader->FDFormat != FDCAN_FD_CAN)
            {
                for (i = 0; i < 2; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
            else
            {
                for (i = 0; i < 11; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
        }
        if (TxHeader->DataLength == FDCAN_DLC_BYTES_64)
        {
            if (TxHeader->FDFormat != FDCAN_FD_CAN)
            {
                for (i = 0; i < 2; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
            else
            {
                for (i = 0; i < 16; i++)
                {
                    fdcan->CAN_TRANSMIT_BUFFER[i] = (message_data[i][0]) |
                                                    (message_data[i][1] << 8) |
                                                    (message_data[i][2] << 16) |
                                                    (message_data[i][3] << 24) ;
                }
            }
        }
    }
}


/**
  * @brief  Get RxBuffer.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  RxHeader: specifies the RxBuffer Value.
  *          This parameter can be any combination of the following values:
  *             @arg Identifier: Specifies the identifier
  *             The value of Identifier: 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
  *                                      0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
  *             @arg IdType: Specifies the identifier type of the received message
  *             The value of IdType: FDCAN_STANDARD_ID
  *                                  FDCAN_EXTENDED_ID
  *             @arg RxFrameType: Specifies the the received message frame type
  *             The value of RxFrameType: FDCAN_DATA_FRAME
  *                                       FDCAN_REMOTE_FRAME
  *             @arg DataLength: pecifies the received frame length
  *             The value of DataLength: FDCAN_DLC_BYTES_0
  *                                      FDCAN_DLC_BYTES_1
  *                                      FDCAN_DLC_BYTES_2
  *                                      FDCAN_DLC_BYTES_3
  *                                      FDCAN_DLC_BYTES_4
  *                                      FDCAN_DLC_BYTES_5
  *                                      FDCAN_DLC_BYTES_6
  *                                      FDCAN_DLC_BYTES_7
  *                                      FDCAN_DLC_BYTES_8
  *                                      FDCAN_DLC_BYTES_12
  *                                      FDCAN_DLC_BYTES_16
  *                                      FDCAN_DLC_BYTES_20
  *                                      FDCAN_DLC_BYTES_24
  *                                      FDCAN_DLC_BYTES_32
  *                                      FDCAN_DLC_BYTES_48
  *                                      FDCAN_DLC_BYTES_64
  *             @arg ErrorStateIndicator: Specifies the error state indicator
  *             The value of ErrorStateIndicator: FDCAN_ESI_ACTIVE
  *                                               FDCAN_ESI_PASSIVE
  *             @arg BitRateSwitch: Specifies whether the Rx frame is received with or without bit rate switching
  *             The value of BitRateSwitch: FDCAN_BRS_OFF
  *                                         FDCAN_BRS_ON
  *             @arg FDFormat: Specifies whether the Rx frame is received in classic or FD format
  *             The value of FDFormat: FDCAN_CLASSIC_CAN
  *                                    FDCAN_FD_CAN
  *             @arg RxKOER: Specifies the kind of ERROR of receive frames
  *             The value of RxKOER: FDCAN_NO_ERROR
  *                                  FDCAN_BIT_ERROR
  *                                  FDCAN_FORM_ERROR
  *                                  FDCAN_STUFF_ERROR
  *                                  FDCAN_ACK_ERROR
  *                                  FDCAN_CRC_ERROR
  *                                  FDCAN_OTHER_ERROR
  *                                  FDCAN_NOT_USED
  *             @arg CycleTime: Specifies the time-stamp cycle time only in TTCAN mode
  *             The value of CycleTime: This parameter must be a number between 0 and 0xFFFF
  * @retval None
  */
void FDCAN_GetRxBuffer(FDCAN_TypeDef* fdcan, FDCAN_RxHeaderTypeDef* RxHeader, uint8_t message_data[16][4])
{
    uint32_t i;
    uint32_t j;

    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Get ID type */
    RxHeader->IdType = (fdcan->CAN_RECEIVE_BUFFER1 & FDCAN_EXTENDED_ID);

    /* Get ID value */
    RxHeader->Identifier =  fdcan->CAN_RECEIVE_BUFFER0;

    /* Get Rx frame type */
    RxHeader->RxFrameType = (fdcan->CAN_RECEIVE_BUFFER1 & FDCAN_REMOTE_FRAME);

    /* Get FDCAN format */
    RxHeader->FDFormat = (fdcan->CAN_RECEIVE_BUFFER1 & FDCAN_FD_CAN);

    /* Get the error state indicator */
    RxHeader->ErrorStateIndicator = (fdcan->CAN_RECEIVE_BUFFER0 & FDCAN_ESI_PASSIVE);

    /* Get whether the Rx frame is received with or without bit rate switching*/
    RxHeader->BitRateSwitch = (fdcan->CAN_RECEIVE_BUFFER1 & FDCAN_BRS_ON);

    /* Get the kind of ERROR of receive frames */
    RxHeader->RxKOER = ((fdcan->CAN_RECEIVE_BUFFER1 & 0x0000E000) >> 13U);

    /* Get the time-stamp cycle time only in TTCAN mode */
    if ((fdcan->CAN_FILTER_CTRL & FDCAN_TIMESTAMP_ENABLE) == FDCAN_TIMESTAMP_ENABLE)
    {
        RxHeader->CycleTime = ((fdcan->CAN_RECEIVE_BUFFER1 & 0xffff0000) >> 16U);
    }

    /* Get RX date length */
    RxHeader->DataLength = (fdcan->CAN_RECEIVE_BUFFER1 & FDCAN_DLC_BYTES_64);

    /* Only data frame can read rxbuf data */
    if (RxHeader->RxFrameType == FDCAN_DATA_FRAME)
    {
        /*Get Rx date value*/
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_1)
        {
            uint32_t rbuf_data0_value;
            rbuf_data0_value = fdcan->CAN_RECEIVE_BUFFER[0];
            message_data[0][0] = (rbuf_data0_value & 0x000000ff);
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_2)
        {
            uint32_t rbuf_data0_value;
            rbuf_data0_value = fdcan->CAN_RECEIVE_BUFFER[0];
            message_data[0][0] = (rbuf_data0_value & 0x000000ff);
            message_data[0][1] = ((rbuf_data0_value & 0x0000ff00) >>  8U);
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_3)
        {
            uint32_t rbuf_data0_value;
            rbuf_data0_value = fdcan->CAN_RECEIVE_BUFFER[0];
            message_data[0][0] = (rbuf_data0_value & 0x000000ff);
            message_data[0][1] = ((rbuf_data0_value & 0x0000ff00) >>  8U);
            message_data[0][2] = ((rbuf_data0_value & 0x00ff0000) >> 16U);
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_4)
        {
            uint32_t rbuf_data0_value;
            rbuf_data0_value = fdcan->CAN_RECEIVE_BUFFER[0];
            message_data[0][0] = (rbuf_data0_value & 0x000000ff);
            message_data[0][1] = ((rbuf_data0_value & 0x0000ff00) >>  8U);
            message_data[0][2] = ((rbuf_data0_value & 0x00ff0000) >> 16U);
            message_data[0][3] = ((rbuf_data0_value & 0xff000000) >> 24U);
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_5)
        {
            uint32_t rbuf_data0_value;
            uint32_t rbuf_data1_value;
            rbuf_data0_value = fdcan->CAN_RECEIVE_BUFFER[0];
            rbuf_data1_value = fdcan->CAN_RECEIVE_BUFFER[1];
            message_data[0][0] = (rbuf_data0_value & 0x000000ff);
            message_data[0][1] = ((rbuf_data0_value & 0x0000ff00) >>  8U);
            message_data[0][2] = ((rbuf_data0_value & 0x00ff0000) >> 16U);
            message_data[0][3] = ((rbuf_data0_value & 0xff000000) >> 24U);

            message_data[1][0] = (rbuf_data1_value & 0x000000ff);
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_6)
        {
            uint32_t rbuf_data0_value;
            uint32_t rbuf_data1_value;
            rbuf_data0_value = fdcan->CAN_RECEIVE_BUFFER[0];
            rbuf_data1_value = fdcan->CAN_RECEIVE_BUFFER[1];
            message_data[0][0] = (rbuf_data0_value & 0x000000ff);
            message_data[0][1] = ((rbuf_data0_value & 0x0000ff00) >>  8U);
            message_data[0][2] = ((rbuf_data0_value & 0x00ff0000) >> 16U);
            message_data[0][3] = ((rbuf_data0_value & 0xff000000) >> 24U);

            message_data[1][0] = (rbuf_data1_value & 0x000000ff);
            message_data[1][1] = ((rbuf_data1_value & 0x0000ff00) >>  8U);
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_7)
        {
            uint32_t rbuf_data0_value;
            uint32_t rbuf_data1_value;
            rbuf_data0_value = fdcan->CAN_RECEIVE_BUFFER[0];
            rbuf_data1_value = fdcan->CAN_RECEIVE_BUFFER[1];
            message_data[0][0] = (rbuf_data0_value & 0x000000ff);
            message_data[0][1] = ((rbuf_data0_value & 0x0000ff00) >>  8U);
            message_data[0][2] = ((rbuf_data0_value & 0x00ff0000) >> 16U);
            message_data[0][3] = ((rbuf_data0_value & 0xff000000) >> 24U);

            message_data[1][0] = (rbuf_data1_value & 0x000000ff);
            message_data[1][1] = ((rbuf_data1_value & 0x0000ff00) >>  8U);
            message_data[1][2] = ((rbuf_data1_value & 0x00ff0000) >> 16U);
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_8)
        {
            uint32_t message_data_one[2];
            for (i = 0; i < 2; i++)
            {
                message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
            }
            for (j = 0; j < 2; j++)
            {
                message_data[j][0] = (message_data_one[j] & 0x000000ff);
                message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
            }
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_12)
        {
            if (RxHeader->FDFormat == FDCAN_CLASSIC_CAN)
            {
                uint32_t message_data_one[2];
                for (i = 0; i < 2; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 2; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
            else
            {
                uint32_t message_data_one[3];
                for (i = 0; i < 3; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 3; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_16)
        {
            if (RxHeader->FDFormat == FDCAN_CLASSIC_CAN)
            {
                uint32_t message_data_one[2];
                for (i = 0; i < 2; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 2; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
            else
            {
                uint32_t message_data_one[4];
                for (i = 0; i < 4; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 4; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_20)
        {
            if (RxHeader->FDFormat == FDCAN_CLASSIC_CAN)
            {
                uint32_t message_data_one[2];
                for (i = 0; i < 2; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 2; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
            else
            {
                uint32_t message_data_one[5];
                for (i = 0; i < 5; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 5; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_24)
        {
            if (RxHeader->FDFormat == FDCAN_CLASSIC_CAN)
            {
                uint32_t message_data_one[2];
                for (i = 0; i < 2; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 2; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
            else
            {
                uint32_t message_data_one[6];
                for (i = 0; i < 6; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 6; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_32)
        {
            if (RxHeader->FDFormat == FDCAN_CLASSIC_CAN)
            {
                uint32_t message_data_one[2];
                for (i = 0; i < 2; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 2; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
            else
            {
                uint32_t message_data_one[8];
                for (i = 0; i < 8; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 8; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_48)
        {
            if (RxHeader->FDFormat == FDCAN_CLASSIC_CAN)
            {
                uint32_t message_data_one[2];
                for (i = 0; i < 2; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 2; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
            else
            {
                uint32_t message_data_one[12];
                for (i = 0; i < 12; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 12; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
        }
        if (RxHeader->DataLength == FDCAN_DLC_BYTES_64)
        {
            if (RxHeader->FDFormat == FDCAN_CLASSIC_CAN)
            {
                uint32_t message_data_one[2];
                for (i = 0; i < 2; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 2; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
            else
            {
                uint32_t message_data_one[16];
                for (i = 0; i < 16; i++)
                {
                    message_data_one[i] = fdcan->CAN_RECEIVE_BUFFER[i];
                }
                for (j = 0; j < 16; j++)
                {
                    message_data[j][0] = (message_data_one[j] & 0x000000ff);
                    message_data[j][1] = ((message_data_one[j] & 0x0000ff00) >>  8U);
                    message_data[j][2] = ((message_data_one[j] & 0x00ff0000) >> 16U);
                    message_data[j][3] = ((message_data_one[j] & 0xff000000) >> 24U);
                }
            }
        }
    }
}

/**
  * @brief  Get Arbitration Lost Capture Value.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  ArbLostCap: specifies the ALC value.
  *         This parameter can be any combination of the following values:
  *             @arg ArbitrationLostCapture:Specifies the bit position in the frame where the arbitration has been lost
  *             The value of ArbitrationLostCapture: This parameter must be a number between 0 and 31
  * @retval None
  */
void FDCAN_GetArbLostCap(FDCAN_TypeDef* fdcan, FDCAN_ArbitrationLostCaptureTypeDef* ArbLostCap)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Get ALC value */
    ArbLostCap->ArbitrationLostCapture = fdcan->CAN_ERR_CNT;
}

/**
  * @brief  Get TECNT, RECNT and KOER.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  ErrorCnt: specifies the TECNT, RECNT and KOER value.
  *         This parameter can be any combination of the following values:
  *             @arg TxErrorCnt: Specifies the Transmit Error Counter Value
  *             The value of TxErrorCnt: This parameter can be a number between 0 and 255
  *             @arg RxErrorCnt: Specifies the Receive Error Counter Value
  *             The value of RxErrorCnt: This parameter can be a number between 0 and 255
  *             @arg KOER: Specifies the kind of Error
  *             The value of KOER: FDCAN_NO_ERROR
  *                                FDCAN_BIT_ERROR
  *                                FDCAN_FORM_ERROR
  *                                FDCAN_STUFF_ERROR
  *                                FDCAN_ACK_ERROR
  *                                FDCAN_CRC_ERROR
  *                                FDCAN_OTHER_ERROR
  *                                FDCAN_NOT_USED
  * @retval None
  */
void FDCAN_GetErrorCnt(FDCAN_TypeDef* fdcan, FDCAN_ErrorCountersTypeDef* ErrorCnt)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Get TECNT, RECNT and KOER */
    ErrorCnt->TxErrorCnt = ((fdcan->CAN_ERR_CNT & 0xff000000) >> 24U);
    ErrorCnt->RxErrorCnt = ((fdcan->CAN_ERR_CNT & 0x00ff0000) >> 16U);
    ErrorCnt->KOER       = ((fdcan->CAN_ERR_CNT & 0x000000E0) >> 5U);
}

/**
  * @brief  Get TECNT, RECNT and KOER.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @retval None
  */
void FDCAN_ConfigTsnext(FDCAN_TypeDef* fdcan)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    /* Set TSNEXT */
    fdcan->CAN_CMD_CTRL |= CAN_CMD_CTRL_TSNEXT;

    /* Wait TSNEXT be clear by hardware */
    while ((fdcan->CAN_CMD_CTRL & CAN_CMD_CTRL_TSNEXT) == CAN_CMD_CTRL_TSNEXT);
}

/**
  * @brief  Get TECNT, RECNT and KOER.
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @retval None
  */
void FDCAN_ConfigInitialOffset(FDCAN_TypeDef* fdcan)
{
    /* Check the parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (fdcan == FDCAN1)
    {
        fdcan->CAN_INIT_CFG_OFFSET = 0x000;
    }

    if (fdcan == FDCAN2)
    {
        fdcan->CAN_INIT_CFG_OFFSET = 0x0F4;
    }

    if (fdcan == FDCAN3)
    {
        fdcan->CAN_INIT_CFG_OFFSET = 0x1E8;
    }

    if (fdcan == FDCAN4)
    {
        fdcan->CAN_INIT_CFG_OFFSET = 0x2DC;
    }
}

/** @defgroup FDCAN_Exported_Functions_Group4 Interrupts management
 *  @brief    Interrupts management
 *
@verbatim
  ==============================================================================
                       ##### Interrupts management #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) FDCAN_ActivateNotification      : Enable interrupts
      (+) FDCAN_DeactivateNotification    : Disable interrupts

@endverbatim
  * @{
  */

/**
  * @brief  Enable interrupts.
  * @param  fdcan pointer to an FDCAN_TypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  FDCAN_INT_REG: specifies the int in which reg.
  *         This parameter can be one of the following values:
  *          FDCAN_INT_REG_FLAG1: int in CAN_INT_FLAG1
  *          FDCAN_INT_REG_FLAG2: int in CAN_INT_FLAG2
  * @param  ActiveITs indicates which interrupts will be enabled.
  *         This parameter can be any combination of the following values:
  *         FDCAN_IT_RECEIVE:                 Receive interrupt enable
  *         FDCAN_IT_RBUF_OVERRUN:            Receive buffer overrun interrupt enable
  *         FDCAN_IT_RBUF_FULL:               Receive buffer full interupt enable
  *         FDCAN_IT_RB_ALMOST_FULL:          Receive buffer almost full interupt enable
  *         FDCAN_IT_TRANSMISSION_PRIMARY :   Transmission primary successfully interupt enable
  *         FDCAN_IT_TRANSMISSION_SECONDARY:  Transmission secondary successfully interupt enable
  *         FDCAN_IT_ERROR:                   Error interupt enable
  *         FDCAN_IT_ERROR_PASSIVE:           Node is error passive interupt enable
  *         FDCAN_IT_ARBITRATION_LOST:        Lost arbitration interupt enable
  *         FDCAN_IT_BUS_ERROR:               Bus error interupt enable
  *         FDCAN_IT_TIME_TRIGGER:            Time Trigger interupt enable
  *         FDCAN_IT_WATCH_TRIGGER:           Watch Trigger interupt enable
  * @retval None.
  */
void FDCAN_ActivateNotification(FDCAN_TypeDef* fdcan, uint32_t FDCAN_INT_REG, uint32_t ActiveITs)
{

    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_IT(ActiveITs));
    assert_param(IS_FDCAN_INT_REG(FDCAN_INT_REG));


    if (FDCAN_INT_REG == FDCAN_INT_REG_FLAG1)
    {
        /* get can int enable value */
        uint32_t can_int_flag1_value;
        can_int_flag1_value = fdcan->CAN_INT_FLAG1;

        /* clear can int flag in this reg*/
        can_int_flag1_value = can_int_flag1_value & CAN_INT_FLAG1_MASK;

        /* Enable choosed Interrupt */
        fdcan->CAN_INT_FLAG1 = can_int_flag1_value | ActiveITs;
    }

    if (FDCAN_INT_REG == FDCAN_INT_REG_FLAG2)
    {
        /* Enable Interrupt */
        fdcan->CAN_INT_FLAG2 |= ActiveITs;
    }
}

/**
  * @brief  Disable interrupts.
  * @param  fdcan pointer to an FDCAN_TypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  FDCAN_INT_REG: specifies the int in which reg.
  *         This parameter can be one of the following values:
  *          FDCAN_INT_REG_FLAG1: int in CAN_INT_FLAG1
  *          FDCAN_INT_REG_FLAG2: int in CAN_INT_FLAG2
  * @param  InactiveITs indicates which interrupts will be disabled.
  *         This parameter can be any combination of @arg FDCAN_Interrupts:
  *         FDCAN_IT_RECEIVE:                 Receive interrupt enable
  *         FDCAN_IT_RBUF_OVERRUN:            Receive buffer overrun interrupt enable
  *         FDCAN_IT_RBUF_FULL:               Receive buffer full interupt enable
  *         FDCAN_IT_RB_ALMOST_FULL:          Receive buffer almost full interupt enable
  *         FDCAN_IT_TRANSMISSION_PRIMARY :   Transmission primary successfully interupt enable
  *         FDCAN_IT_TRANSMISSION_SECONDARY:  Transmission secondary successfully interupt enable
  *         FDCAN_IT_ERROR:                   Error interupt enable
  *         FDCAN_IT_ERROR_PASSIVE:           Node is error passive interupt enable
  *         FDCAN_IT_ARBITRATION_LOST:        Lost arbitration interupt enable
  *         FDCAN_IT_BUS_ERROR:               Bus error interupt enable
  *         FDCAN_IT_TIME_TRIGGER:            Time Trigger interupt enable
  *         FDCAN_IT_WATCH_TRIGGER:           Watch Trigger interupt enable
  * @retval None.
  */
void FDCAN_DeactivateNotification(FDCAN_TypeDef* fdcan, uint32_t FDCAN_INT_REG, uint32_t InactiveITs)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_IT(InactiveITs));
    assert_param(IS_FDCAN_INT_REG(FDCAN_INT_REG));

    if (FDCAN_INT_REG == FDCAN_INT_REG_FLAG1)
    {
        /* get can int enable value */
        uint32_t can_int_flag1_value;
        can_int_flag1_value = fdcan->CAN_INT_FLAG1;

        /* clear can int flag in this reg*/
        can_int_flag1_value = can_int_flag1_value & CAN_INT_FLAG1_MASK;

        /* disable choosed int enable bit */
        fdcan->CAN_INT_FLAG1 = (can_int_flag1_value & (~InactiveITs));

        if (((InactiveITs & FDCAN_IT_RECEIVE)              != 0U) || ((InactiveITs & FDCAN_IT_RBUF_OVERRUN)           != 0U) || \
                ((InactiveITs & FDCAN_IT_RBUF_FULL)            != 0U) || ((InactiveITs & FDCAN_IT_RB_ALMOST_FULL)         != 0U) || \
                ((InactiveITs & FDCAN_IT_TRANSMISSION_PRIMARY) != 0U) || ((InactiveITs & FDCAN_IT_TRANSMISSION_SECONDARY) != 0U) || \
                ((InactiveITs & FDCAN_IT_ERROR)                != 0U) || ((InactiveITs & FDCAN_IT_ERROR_PASSIVE)          != 0U) || \
                ((InactiveITs & FDCAN_IT_ARBITRATION_LOST)     != 0U) || ((InactiveITs & FDCAN_IT_BUS_ERROR)              != 0U))
        {
            /* Wait choosed Interrupts are disabled */
            while ((fdcan->CAN_INT_FLAG1 & InactiveITs) == InactiveITs);

        }

    }

    if (FDCAN_INT_REG == FDCAN_INT_REG_FLAG2)
    {
        fdcan->CAN_INT_FLAG2 &= ~InactiveITs;

        /* Check which interrupts are enabled before */
        if (((InactiveITs & FDCAN_IT_TIME_TRIGGER)         != 0U) || ((InactiveITs & FDCAN_IT_WATCH_TRIGGER)          != 0U))
        {
            /* Wait choosed Interrupts are disabled */
            while ((fdcan->CAN_INT_FLAG2 & InactiveITs) == InactiveITs);
        }
    }

}
/**
  * @}
  */

/**
  * @brief  get single bit STAT status.
  * @param  fdcan pointer to an FDCAN_TypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  FDCAN_FLAG_REG: specifies the flag in which reg.
  *         This parameter can be one of the following values:
  *          FDCAN_FLAG_REG_CMD: flag in CAN_CMD_CTRL
  *          FDCAN_FLAG_REG_FLAG1: flag in CAN_INT_FLAG1
  *          FDCAN_FLAG_REG_FLAG2: flag in CAN_INT_FLAG2
  * @param  FDCAN_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *          FDCAN_FLAG_ROV:       receive buffer overflow
  *          FDCAN_FLAG_RACTIVE:   receiving
  *          FDCAN_FLAG_TACTIVE:   transmiting
  *          FDCAN_FLAG_EPIF:      passive error interrupt flag
  *          FDCAN_FLAG_ALIF:      arbit lose interrupt flag
  *          FDCAN_FLAG_BEIF:      bus error interrupt flag
  *          FDCAN_FLAG_RIF:       receive interrupr flag
  *          FDCAN_FLAG_ROIF:      receive overflow interrupt flag
  *          FDCAN_FLAG_RFIF:      receive full interrupt flag
  *          FDCAN_FLAG_RAFIF:     receive almost full interrupr flag
  *          FDCAN_FLAG_TPIF:      transmit primary interrupt flag
  *          FDCAN_FLAG_TSIF:      transmit secondry interrupt flag
  *          FDCAN_FLAG_EIF:       error interrupt flag
  *          FDCAN_FLAG_AIF:       abort interrupr flag
  *          FDCAN_FLAG_WTIF:      watch dog trig interrupt flag
  *          FDCAN_FLAG_TEIF:      timer trig error interrupt flag
  *          FDCAN_FLAG_TTIF:      timer trig interrupt flag
  * @retval None.
  */
FlagStatus FDCAN_GetFlagStatus(FDCAN_TypeDef* fdcan, uint32_t FDCAN_FLAG_REG, uint32_t FDCAN_FLAG)
{
    FlagStatus bitstatus = RESET;
    assert_param(IS_FDCAN_FLAG(FDCAN_FLAG));
    assert_param(IS_FDCAN_FLAG_REG(FDCAN_FLAG_REG));

    if (FDCAN_FLAG_REG == FDCAN_FLAG_REG_CMD)
    {
        if ((fdcan->CAN_CMD_CTRL & FDCAN_FLAG) != (uint16_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    if (FDCAN_FLAG_REG == FDCAN_FLAG_REG_FLAG1)
    {
        if ((fdcan->CAN_INT_FLAG1 & FDCAN_FLAG) != (uint16_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    if (FDCAN_FLAG_REG == FDCAN_FLAG_REG_FLAG2)
    {
        if ((fdcan->CAN_INT_FLAG2 & FDCAN_FLAG) != (uint16_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    return bitstatus;
}

/**
  * @brief  get single bit STAT status.
  * @param  fdcan pointer to an FDCAN_TypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  FDCAN_FLAG_REG: specifies the flag in which reg.
  *         This parameter can be one of the following values:
  *          FDCAN_FLAG_REG_FLAG1: flag in CAN_INT_FLAG1
  *          FDCAN_FLAG_REG_FLAG2: flag in CAN_INT_FLAG2
  * @param  FDCAN_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *          FDCAN_FLAG_EPIF:      passive error interrupt flag
  *          FDCAN_FLAG_ALIF:      arbit lose interrupt flag
  *          FDCAN_FLAG_BEIF:      bus error interrupt flag
  *          FDCAN_FLAG_RIF:       receive interrupr flag
  *          FDCAN_FLAG_ROIF:      receive overflow interrupt flag
  *          FDCAN_FLAG_RFIF:      receive full interrupt flag
  *          FDCAN_FLAG_RAFIF:     receive almost full interrupr flag
  *          FDCAN_FLAG_TPIF:      transmit primary interrupt flag
  *          FDCAN_FLAG_TSIF:      transmit secondry interrupt flag
  *          FDCAN_FLAG_EIF:       error interrupt flag
  *          FDCAN_FLAG_AIF:       abort interrupr flag
  *          FDCAN_FLAG_WTIF:      watch dog trig interrupt flag
  *          FDCAN_FLAG_TEIF:      timer trig error interrupt flag
  *          FDCAN_FLAG_TTIF:      timer trig interrupt flag
  *          FDCAN_FLAG_RTIF_ALL:  can_rtif all flag
  * @retval None.
  */
void FDCAN_ClearInterruptFlag(FDCAN_TypeDef* fdcan,  uint32_t FDCAN_FLAG_REG, uint32_t FDCAN_FLAG)
{
    assert_param(IS_FDCAN_FLAG(FDCAN_FLAG));
    assert_param(IS_FDCAN_FLAG_REG(FDCAN_FLAG_REG));

    if (FDCAN_FLAG_REG == FDCAN_FLAG_REG_FLAG1)
    {
        /* get can int enable value */
        uint32_t can_int_flag1_value;
        can_int_flag1_value = fdcan->CAN_INT_FLAG1;

        /* clear can int flag in this reg*/
        can_int_flag1_value = can_int_flag1_value & CAN_INT_FLAG1_MASK;

        fdcan->CAN_INT_FLAG1 = (can_int_flag1_value | FDCAN_FLAG);
    }
    else if (FDCAN_FLAG_REG == FDCAN_FLAG_REG_FLAG2)
    {
        fdcan->CAN_INT_FLAG2 |= FDCAN_FLAG;
    }
}

/**
  * @brief  get dual bits STAT status.
  * @param  fdcan pointer to an FDCAN_TypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  FDCAN_BUF_TYPE: specifies the buffer status.
  *         This parameter can be one of the following values:
  *              @arg FDCAN_TRANS_BUFFER_STAT:   Transmission Secondary buffer Status
  *              @arg FDCAN_RECEIVE_BUFFER_STAT: Receive buffer status
  *
  * @retval None.
  */
int FDCAN_GetFifoStatus(FDCAN_TypeDef* fdcan, uint32_t FDCAN_BUF_TYPE)
{
    int dual_bitstatus = Empty;

    if (FDCAN_BUF_TYPE == FDCAN_TRANS_BUFFER_STAT)
    {
        if (((fdcan->CAN_CMD_CTRL & FDCAN_TBUF_FULL) >> 16) == 0x0)
        {
            dual_bitstatus = Empty;
        }
        else if (((fdcan->CAN_CMD_CTRL & FDCAN_TBUF_FULL) >> 16) == 0x1)
        {
            dual_bitstatus = Less_HalfFull;
        }
        else if (((fdcan->CAN_CMD_CTRL & FDCAN_TBUF_FULL) >> 16) == 0x2)
        {
            dual_bitstatus = More_HalfFull;
        }
        else if (((fdcan->CAN_CMD_CTRL & FDCAN_TBUF_FULL) >> 16) == 0x3)
        {
            dual_bitstatus = Full;
        }
    }
    else if (FDCAN_BUF_TYPE == FDCAN_RECEIVE_BUFFER_STAT)
    {
        if (((fdcan->CAN_CMD_CTRL & FDCAN_RBUF_FULL) >> 24) == 0x0)
        {
            dual_bitstatus = Empty;
        }
        else if (((fdcan->CAN_CMD_CTRL & FDCAN_RBUF_FULL) >> 24) == 0x1)
        {
            dual_bitstatus = Less_HalfFull;
        }
        else if (((fdcan->CAN_CMD_CTRL & FDCAN_RBUF_FULL) >> 24) == 0x2)
        {
            dual_bitstatus = More_HalfFull;
        }
        else if (((fdcan->CAN_CMD_CTRL & FDCAN_RBUF_FULL) >> 24) == 0x3)
        {
            dual_bitstatus = Full;
        }
    }
    return dual_bitstatus;
}


/**
  * @brief  Set reference message
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  FDCAN_REF_MSG_IDE:ref_msg id type
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_REF_MSG_STD:standard id
  *             @arg FDCAN_REF_MSG_EXT:externed id
  * @param  FDCAN_REF_MSG_ID:reference id value
  * @retval None
  */

void FDCAN_RefMessageSet(FDCAN_TypeDef* fdcan, uint32_t FDCAN_REF_MSG_IDE, uint32_t FDCAN_REF_MSG_ID)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_REF_MSG_IDTYPE(FDCAN_REF_MSG_IDE));
    assert_param(IS_FDCAN_REF_MSG_ID_VALUE(FDCAN_REF_MSG_ID));

    fdcan->CAN_REF_MSG = (FDCAN_REF_MSG_IDE | FDCAN_REF_MSG_ID);
}

/**
  * @brief  Set reference message
  * @param  fdcan: specifies the instance.
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN1: the instance is can1
  *             @arg FDCAN2: the instance is can2
  *             @arg FDCAN3: the instance is can3
  *             @arg FDCAN4: the instance is can4
  * @param  FDCAN_TBPTR:point tbuf ptb or stb
  * @retval None
  */

void FDCAN_TbufSoltPoint(FDCAN_TypeDef* fdcan, uint32_t FDCAN_TBPTR)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_TBPTR_VALUE(FDCAN_TBPTR));

    /* CLR OLD TBPTR VALUE */
    uint32_t CAN_INT_FLAG2_VALUE;
    CAN_INT_FLAG2_VALUE = fdcan->CAN_INT_FLAG2;
    CAN_INT_FLAG2_VALUE = (CAN_INT_FLAG2_VALUE & ~CAN_INT_FLAG2_TBPTR);
    /* SET NEW TBPTR VALUE */
    fdcan->CAN_INT_FLAG2 = ((FDCAN_TBPTR << 16U) | CAN_INT_FLAG2_VALUE);
}

void FDCAN_TransmitSoltPoint(FDCAN_TypeDef* fdcan, uint32_t FDCAN_TTPTR)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_TTPTR_VALUE(FDCAN_TTPTR));

    /* CLR OLD TTPTR VALUE */
    uint32_t CAN_TRG_CFG_VALUE;
    CAN_TRG_CFG_VALUE = fdcan->CAN_TRIG_CFG;
    CAN_TRG_CFG_VALUE = (CAN_TRG_CFG_VALUE & ~CAN_TRIG_CFG_TTPTR);
    CAN_TRG_CFG_VALUE = (CAN_TRG_CFG_VALUE & ~0xFFFF0000);
    /* SET NEW TTPTR VALUE */
    fdcan->CAN_TRIG_CFG = (FDCAN_TTPTR | CAN_TRG_CFG_VALUE);
}


void FDCAN_SetTbufSoltEmpty(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_INT_FLAG2 |= CAN_INT_FLAG2_TBE;
        while ((fdcan->CAN_INT_FLAG2 & CAN_INT_FLAG2_TBE) == CAN_INT_FLAG2_TBE);
    }
    else if (NewState == DISABLE)
    {
        fdcan->CAN_INT_FLAG2 &= ~CAN_INT_FLAG2_TBE;
    }
}

void FDCAN_SetTbufSoltFull(FDCAN_TypeDef* fdcan, FunctionalState NewState)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        fdcan->CAN_INT_FLAG2 |= CAN_INT_FLAG2_TBF;
        while ((fdcan->CAN_INT_FLAG2 & CAN_INT_FLAG2_TBF) == CAN_INT_FLAG2_TBF);
    }
    else if (NewState == DISABLE)
    {
        fdcan->CAN_INT_FLAG2 &= ~CAN_INT_FLAG2_TBF;
    }
}

void FDCAN_TimeTrigEnable(FDCAN_TypeDef* fdcan, FunctionalState NewState)/* Function used enbale tten*/
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        /* Set the Time_Triger Enable */
        fdcan->CAN_INT_FLAG2 |= CAN_INT_FLAG2_TTEN;
    }
    else if (NewState == DISABLE)
    {
        /* clr the Time_Triger Enable */
        fdcan->CAN_INT_FLAG2 &= ~CAN_INT_FLAG2_TTEN;
    }
}
/**
  * @param  FDCAN_TIMEPOS:time stamp position
  *          This parameter can be any combination of the following values:
  *             @arg FDCAN_TIMEPOS_SOF:time stamp position in sof
  *             @arg FDCAN_TIMEPOS_EOF:time stamp position in eof
*/
void FDCAN_TimeStampPosition(FDCAN_TypeDef* fdcan, uint32_t FDCAN_TIMEPOS)/* Function used set timepos*/
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));
    assert_param(IS_FDCAN_TIME_POS(FDCAN_TIMEPOS));

    if (FDCAN_TIMEPOS == FDCAN_TIMEPOS_SOF)
    {
        /* Set the Time_Stamp Position in SOF */
        fdcan->CAN_FILTER_CTRL &= ~CAN_FILTER_CTRL_TIMEPOS;
    }
    else if (FDCAN_TIMEPOS == FDCAN_TIMEPOS_EOF)
    {
        /* Set the Time_Stamp Position in EOF */
        fdcan->CAN_FILTER_CTRL |= FDCAN_TIMEPOS_EOF;
    }
}

void FDCAN_TimeStampEnable(FDCAN_TypeDef* fdcan, FunctionalState NewState)/* Function used enbale timestamp*/
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    if (NewState == ENABLE)
    {
        /* Set the Time_Stamp Enable */
        fdcan->CAN_FILTER_CTRL |= CAN_FILTER_CTRL_TIMEEN;
    }
    else if (NewState == DISABLE)
    {
        /* Clr the Time_Stamp Enable */
        fdcan->CAN_FILTER_CTRL &= ~CAN_FILTER_CTRL_TIMEEN;
    }
}

void FDCAN_GetCanTransmisionTs(FDCAN_TypeDef* fdcan, uint32_t can_transmission_ts[2])
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(fdcan));

    uint32_t i;
    for (i = 0; i < 2; i++)
    {
        can_transmission_ts[i] = fdcan->CAN_TRANSMISION_TS[i];
    }

}


/**
  * @}
  */


