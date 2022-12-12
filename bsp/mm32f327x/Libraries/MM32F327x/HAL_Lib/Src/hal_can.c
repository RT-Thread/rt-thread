////////////////////////////////////////////////////////////////////////////////
/// @file     hal_can.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE CAN FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define __HAL_CAN_C

// Files includes
#include "hal_can.h"
#include "hal_rcc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup CAN_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup CAN_Exported_Functions
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the CAN peripheral registers to their default reset
/// values.
/// @param  can: select the CAN peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_DeInit(CAN_TypeDef* can)
{
    exRCC_APB1PeriphReset(RCC_APB1ENR_CAN);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief   Initializes the CAN peripheral according to the specified
///          parameters in the CAN_InitStruct.
/// @param   can: select the CAN peripheral.
/// @param   CAN_InitStruct: pointer to a CAN_InitTypeDef structure that
///          contains the configuration information for the CAN peripheral.
/// @retval  Constant indicates initialization succeed which will be
///          CANINITFAILED or CANINITOK.
////////////////////////////////////////////////////////////////////////////////
u8 CAN_Init(CAN_TypeDef* can, CAN_Basic_InitTypeDef* init_struct)
{
    u8 InitStatus = CANINITFAILED;

    can->BTR0 = ((u32)(init_struct->SJW) << 6) | ((u32)(init_struct->BRP));
    can->BTR1 = ((u32)(init_struct->SAM) << 7) | ((u32)(init_struct->TESG2) << 4) | ((u32)(init_struct->TESG1));

    if (init_struct->GTS == ENABLE) {
        can->CMR |= (u32)CAN_SleepMode;
        InitStatus = CANINITFAILED;
    }
    else {
        can->CMR &= ~(u32)CAN_SleepMode;
        InitStatus = CANINITOK;
    }

    (init_struct->GTS == ENABLE) ? (can->CMR |= (u32)CAN_SleepMode) : (can->CMR &= ~(u32)CAN_SleepMode);

    can->CDR |=
        ((init_struct->CBP) << 6) | ((init_struct->RXINTEN) << 5) | ((init_struct->CLOSE_OPEN_CLK) << 3) | (init_struct->CDCLK);

    return InitStatus;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the CAN_Basic reception filter according to the specified
///         parameters in the basic_filter_init_struct.
/// @param  basic_filter_init_struct: pointer to a CAN_Basic_FilterInitTypeDef
///         structure that contains the configuration information.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_FilterInit(CAN_Basic_FilterInitTypeDef* basic_filter_init_struct)
{
    // Filter Mode
    CAN1->ACR = basic_filter_init_struct->CAN_FilterId;
    CAN1->AMR = basic_filter_init_struct->CAN_FilterMaskId;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each init_struct member with its default value.
/// @param  init_struct : pointer to a CAN_Basic_InitTypeDef structure which will be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_StructInit(CAN_Basic_InitTypeDef* init_struct)
{
    // Reset CAN_Basic init structure parameters values

    // initialize the BRP member(where can be set with (0..63))
    init_struct->BRP = 0x0;
    // initialize the SJW member(where can be set with (0..3))
    init_struct->SJW = 0x0;
    // Initialize the TESG1 member(where can be set with (0..15))
    init_struct->TESG1 = 0x0;
    // Initialize the TESG2 member(where can be set with(0..7))
    init_struct->TESG2 = 0x0;
    // Initialize the SAM member(where can be set (SET or RESET))
    init_struct->SAM = RESET;
    // Initialize the GTS member to Sleep Mode(where can be set (ENABLE or
    // DISABLE))
    init_struct->GTS = DISABLE;
    // Initialize the external pin CLKOUT frequence
    init_struct->CDCLK = 0x0;
    // Initialize the external clk is open or close
    init_struct->CLOSE_OPEN_CLK = 0x0;
    // Initialize the TX1 pin work as rx interrupt output
    init_struct->RXINTEN = 0x0;
    // Initialize the CBP of CDR register
    init_struct->CBP = 0x0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified CAN interrupts.
/// @param  can:  select the CAN peripheral.
/// @param  it: specifies the CAN interrupt sources to be enabled or
///         disabled.
///         This parameter can be: CAN_IT_OIE, CAN_IT_EIE, CAN_IT_TIE,
///         CAN_IT_RIE.
/// @param  state: new state of the CAN interrupts.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_ITConfig(CAN_TypeDef* can, u32 it, FunctionalState state)
{
    (state) ? (can->CR |= it) : (can->CR &= ~it);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initiates and transmits a CAN frame message.
/// @param  can:select the CAN peripheral.
/// @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and
///         CAN data.
/// @retval CANTXOK if the CAN driver transmits the message
////////////////////////////////////////////////////////////////////////////////
u8 CAN_Transmit(CAN_TypeDef* can, CanBasicTxMsg* basic_transmit_message)
{
    can->TXID0 = (basic_transmit_message->IDH);
    can->TXID1 = (basic_transmit_message->IDL << 5) | (basic_transmit_message->RTR << 4) | (basic_transmit_message->DLC);
    if ((FunctionalState)(basic_transmit_message->RTR) != ENABLE) {
        can->TXDR0 = basic_transmit_message->Data[0];
        can->TXDR1 = basic_transmit_message->Data[1];
        can->TXDR2 = basic_transmit_message->Data[2];
        can->TXDR3 = basic_transmit_message->Data[3];
        can->TXDR4 = basic_transmit_message->Data[4];
        can->TXDR5 = basic_transmit_message->Data[5];
        can->TXDR6 = basic_transmit_message->Data[6];
        can->TXDR7 = basic_transmit_message->Data[7];
    }

    can->CMR = CAN_CMR_TR;

    return (can->SR & 0x01);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Cancels a transmit request.
/// @param  can: select the CAN peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_CancelTransmit(CAN_TypeDef* can)
{
    // abort transmission
    can->CMR = CAN_AT;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Releases the specified receive FIFO.
/// @param  can: select the CAN peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_FIFORelease(CAN_TypeDef* can)
{
    // Release FIFO
    can->CMR |= (u32)CAN_RRB;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Receives a correct CAN frame.
/// @param  can: select the CAN peripheral.
/// @param  RxMessage: pointer to a structure receive frame which contains CAN
///         Id,CAN DLC, CAN data and FMI number.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Receive(CAN_TypeDef* can, CanBasicRxMsg* basic_receive_message)
{
    u16 tempid;

    basic_receive_message->RTR = (u8)((can->RXID1) >> 4) & 0x1;
    basic_receive_message->DLC = (u8)((can->RXID1) & 0xf);
    tempid              = (u16)(((can->RXID1) & 0xe0) >> 5);
    tempid |= (u16)(can->RXID0 << 3);
    basic_receive_message->ID      = tempid;
    basic_receive_message->Data[0] = CAN1->RXDR0;
    basic_receive_message->Data[1] = CAN1->RXDR1;
    basic_receive_message->Data[2] = CAN1->RXDR2;
    basic_receive_message->Data[3] = CAN1->RXDR3;
    basic_receive_message->Data[4] = CAN1->RXDR4;
    basic_receive_message->Data[5] = CAN1->RXDR5;
    basic_receive_message->Data[6] = CAN1->RXDR6;
    basic_receive_message->Data[7] = CAN1->RXDR7;
    CAN_FIFORelease(can);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Select the Sleep mode or not in Basic workmode
/// @param  state to go into the Sleep mode or go out
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
u8 CAN_Sleep(CAN_TypeDef* can)
{
    can->CMR |= CAN_SleepMode;
    // At this step, sleep mode status
    return (u8)((can->CMR & 0x10) == CAN_SleepMode) ? CANSLEEPOK : CANSLEEPFAILED;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Wakes the CAN up.
/// @param  can: where x can be 1 to select the CAN peripheral.
/// @retval CANWAKEUPOK if sleep mode left, CANWAKEUPFAILED in an other case.
////////////////////////////////////////////////////////////////////////////////
u8 CAN_WakeUp(CAN_TypeDef* can)
{
    // Wake up request
    can->CMR &= ~CAN_SleepMode;
    return (u8)((can->CMR & 0x01) == 0) ? CANWAKEUPOK : CANWAKEUPFAILED;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified CAN flag is set or not.
/// @param  can: select the CAN peripheral.
/// @param  flag: specifies the flag to check.
///         This parameter can be one of the following values:
///            @arg CAN_STATUS_RBS: Receive buffer status
///            @arg CAN_STATUS_DOS: Data overflow status
///            @arg CAN_STATUS_TBS: Transmit buffer status
///            @arg CAN_STATUS_TCS: Transmit complete status
///            @arg CAN_STATUS_RS: Receiving status
///            @arg CAN_STATUS_TS: Transmiting status
///            @arg CAN_STATUS_ES: Error status
///            @arg CAN_STATUS_BS: bus status, close or open
/// @retval The new state of CAN_FLAG (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* can, u32 flag)
{
    return (FlagStatus)(((can->SR & flag) == flag) ? SET : RESET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified CAN interrupt has occurred or not.
/// @param  can: where x can be 1 to select the CAN peripheral.
/// @param  it: specifies the CAN interrupt source to check.
///         This parameter can be one of the following values:
///            @arg CAN_IT_RI: Receive FIFO not empty Interrupt
///            @arg CAN_IT_TI: Transmit Interrupt
///            @arg CAN_IT_EI: ERROR Interrupt
///            @arg CAN_IT_DOI: Data voerflow Interrupt
///            @arg CAN_IT_WUI: Wakeup Interrupt
///            @arg CAN_IT_ALL: use it can enble all Interrupt
/// @retval The current state of it (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus CAN_GetITStatus(CAN_TypeDef* can, u32 it)
{
    return (ITStatus)((can->IR & it) != it) ? RESET : SET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Select the can work as peli mode or basic mode
/// @param  can: where x can be 1 or 2 to to select the CAN peripheral.
/// @param  CAN_MODE: specifies the work mode:CAN_BASICMode,CAN_PELIMode
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Mode_Cmd(CAN_TypeDef* can, u32 mode)
{
    can->CDR |= mode;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Select the Reset mode or not
/// @param  can: where x can be 1 or 2 to to select the CAN peripheral.
/// @param  state to go into the Reset mode or go out
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_ResetMode_Cmd(CAN_TypeDef* can, FunctionalState state)
{
    (state == ENABLE) ? (can->CR |= CAN_ResetMode) : (can->CR &= ~CAN_ResetMode);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clear the data overflow.
/// @param  can: where x can be 1 or 2 to to select the CAN peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_ClearDataOverflow(CAN_TypeDef* can)
{
    can->CMR |= (u32)CAN_CDO;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the CAN's IT pending.
/// @param  can: where x can be 1 or 2 to to select the CAN peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_ClearITPendingBit(CAN_TypeDef* can)
{
    u32 temp = 0;
    temp     = temp;
    temp     = can->IR;  // read this register clear all interrupt
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Select the Sleep mode or not in Peli workmode
/// @param  state to go into the Sleep mode or go out
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_SleepMode_Cmd(FunctionalState state)
{
    (state == ENABLE) ? (CAN1_PELI->MOD |= CAN_SleepMode) : (CAN1_PELI->MOD &= ~CAN_SleepMode);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each CAN1_PELI_InitStruct member with its default value.
/// @param  init_struct : pointer to a CAN_Peli_InitTypeDef structure
///         which will be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_StructInit(CAN_Peli_InitTypeDef* init_struct)
{
    //--------------- Reset CAN_Peli init structure parameters values
    //---------------
    init_struct->BRP   = 0x0;      // initialize the BRP member(where can be set with (0..63))
    init_struct->SJW   = 0x0;      // initialize the SJW member(where can be set with (0..3))
    init_struct->TESG1 = 0x0;      // Initialize the TESG1 member(where can be set with (0..15))
    init_struct->TESG2 = 0x0;      // Initialize the TESG2 member(where can be set with(0..7))
    init_struct->SAM   = RESET;    // Initialize the SAM member(where can be set (SET or RESET))
    init_struct->LOM   = DISABLE;  // Initialize the LOM member
    init_struct->STM   = DISABLE;  // Initialize the STM member
    init_struct->SM    = DISABLE;  // Initialize the SM member
    init_struct->SRR   = DISABLE;
    init_struct->EWLR  = 0x96;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the CAN_Peli peripheral according to the specified
///         parameters in the init_struct.
/// @param  init_struct: pointer to a CAN_Peli_InitTypeDef structure that
///         contains the configuration information for the CAN peripheral in the peli workmode.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_Init(CAN_Peli_InitTypeDef* init_struct)
{
    CAN1_PELI->BTR0 = ((u32)init_struct->SJW << 6) | ((u32)init_struct->BRP);
    CAN1_PELI->BTR1 = ((u32)init_struct->SAM << 7) | ((u32)init_struct->TESG2 << 4) | ((u32)init_struct->TESG1);
    if (init_struct->LOM == ENABLE)
        CAN1_PELI->MOD |= (u32)CAN_ListenOnlyMode;
    else
        CAN1_PELI->MOD &= ~(u32)CAN_ListenOnlyMode;
    if (init_struct->STM == ENABLE)
        CAN1_PELI->MOD |= (u32)CAN_SeftTestMode;
    else
        CAN1_PELI->MOD &= ~(u32)CAN_SeftTestMode;
    if (init_struct->SM == ENABLE)
        CAN1_PELI->MOD |= (u32)CAN_SleepMode;
    else
        CAN1_PELI->MOD &= ~(u32)CAN_SleepMode;
    CAN1_PELI->EWLR = (u32)init_struct->EWLR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the CAN_Peli reception filter according to the specified
///         parameters in the peli_filter_init_struct.
/// @param  peli_filter_init_struct: pointer to a CAN_Peli_FilterInitTypeDef
///         structure that contains the configuration information.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_FilterInit(CAN_Peli_FilterInitTypeDef* peli_filter_init_struct)
{
    (peli_filter_init_struct->AFM == CAN_FilterMode_Singal) ? (CAN1_PELI->MOD |= (u32)CAN_FilterMode_Singal)
    : (CAN1_PELI->MOD &= (u32)CAN_FilterMode_Double);

    CAN1_PELI->FF    = peli_filter_init_struct->CAN_FilterId0;
    CAN1_PELI->ID0   = peli_filter_init_struct->CAN_FilterId1;
    CAN1_PELI->ID1   = peli_filter_init_struct->CAN_FilterId2;
    CAN1_PELI->DATA0 = peli_filter_init_struct->CAN_FilterId3;

    CAN1_PELI->DATA1 = peli_filter_init_struct->CAN_FilterMaskId0;
    CAN1_PELI->DATA2 = peli_filter_init_struct->CAN_FilterMaskId1;
    CAN1_PELI->DATA3 = peli_filter_init_struct->CAN_FilterMaskId2;
    CAN1_PELI->DATA4 = peli_filter_init_struct->CAN_FilterMaskId3;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each peli_filter_init_struct member with its default value.
/// @param  peli_filter_init_struct: pointer to a CAN_InitTypeDef structure
///         which ill be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_FilterStructInit(CAN_Peli_FilterInitTypeDef* peli_filter_init_struct)
{
    peli_filter_init_struct->CAN_FilterId0 = 0;
    peli_filter_init_struct->CAN_FilterId1 = 0;
    peli_filter_init_struct->CAN_FilterId2 = 0;
    peli_filter_init_struct->CAN_FilterId3 = 0;

    peli_filter_init_struct->CAN_FilterMaskId0 = 0;
    peli_filter_init_struct->CAN_FilterMaskId1 = 0;
    peli_filter_init_struct->CAN_FilterMaskId2 = 0;
    peli_filter_init_struct->CAN_FilterMaskId3 = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initiates and transmits a CAN frame message.
/// @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and
///         CAN data.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_Transmit(CanPeliTxMsg* peli_transmit_message)
{
    CAN1_PELI->FF = (peli_transmit_message->FF << 7) | (peli_transmit_message->RTR << 6) | (peli_transmit_message->DLC);
    if (((FunctionalState)peli_transmit_message->FF) != ENABLE) {
        CAN1_PELI->ID0 = (peli_transmit_message->IDHH);

        CAN1_PELI->ID1 = (peli_transmit_message->IDHL & 0xE0);
        if ((FunctionalState)(peli_transmit_message->RTR) != ENABLE) {
            CAN1_PELI->DATA0 = peli_transmit_message->Data[0];
            CAN1_PELI->DATA1 = peli_transmit_message->Data[1];
            CAN1_PELI->DATA2 = peli_transmit_message->Data[2];
            CAN1_PELI->DATA3 = peli_transmit_message->Data[3];
            CAN1_PELI->DATA4 = peli_transmit_message->Data[4];
            CAN1_PELI->DATA5 = peli_transmit_message->Data[5];
            CAN1_PELI->DATA6 = peli_transmit_message->Data[6];
            CAN1_PELI->DATA7 = peli_transmit_message->Data[7];
        }
    }
    else {
        CAN1_PELI->ID0   = peli_transmit_message->IDHH;
        CAN1_PELI->ID1   = peli_transmit_message->IDHL;
        CAN1_PELI->DATA0 = peli_transmit_message->IDLH;
        CAN1_PELI->DATA1 = peli_transmit_message->IDLL;
        if ((FunctionalState)(peli_transmit_message->RTR) != ENABLE) {
            CAN1_PELI->DATA2 = peli_transmit_message->Data[0];
            CAN1_PELI->DATA3 = peli_transmit_message->Data[1];
            CAN1_PELI->DATA4 = peli_transmit_message->Data[2];
            CAN1_PELI->DATA5 = peli_transmit_message->Data[3];
            CAN1_PELI->DATA6 = peli_transmit_message->Data[4];
            CAN1_PELI->DATA7 = peli_transmit_message->Data[5];
            CAN1_PELI->DATA8 = peli_transmit_message->Data[6];
            CAN1_PELI->DATA9 = peli_transmit_message->Data[7];
        }
    }

    (CAN1_PELI->MOD & CAN_MOD_STM) ? (CAN1->CMR = CAN_CMR_GTS | CAN_CMR_AT) : (CAN1->CMR = CAN_CMR_TR | CAN_CMR_AT);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initiates and transmits a CAN frame message.
/// @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and
///         CAN data.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_TransmitRepeat(CanPeliTxMsg* peli_transmit_message)
{
    CAN1_PELI->FF = (peli_transmit_message->FF << 7) | (peli_transmit_message->RTR << 6) | (peli_transmit_message->DLC);
    if (((FunctionalState)peli_transmit_message->FF) != ENABLE) {
        CAN1_PELI->ID0 = (peli_transmit_message->IDHH);

        CAN1_PELI->ID1 = (peli_transmit_message->IDHL & 0xE0);
        if ((FunctionalState)(peli_transmit_message->RTR) != ENABLE) {
            CAN1_PELI->DATA0 = peli_transmit_message->Data[0];
            CAN1_PELI->DATA1 = peli_transmit_message->Data[1];
            CAN1_PELI->DATA2 = peli_transmit_message->Data[2];
            CAN1_PELI->DATA3 = peli_transmit_message->Data[3];
            CAN1_PELI->DATA4 = peli_transmit_message->Data[4];
            CAN1_PELI->DATA5 = peli_transmit_message->Data[5];
            CAN1_PELI->DATA6 = peli_transmit_message->Data[6];
            CAN1_PELI->DATA7 = peli_transmit_message->Data[7];
        }
    }
    else {
        CAN1_PELI->ID0   = peli_transmit_message->IDHH;
        CAN1_PELI->ID1   = peli_transmit_message->IDHL;
        CAN1_PELI->DATA0 = peli_transmit_message->IDLH;
        CAN1_PELI->DATA1 = peli_transmit_message->IDLL;
        if ((FunctionalState)(peli_transmit_message->RTR) != ENABLE) {
            CAN1_PELI->DATA2 = peli_transmit_message->Data[0];
            CAN1_PELI->DATA3 = peli_transmit_message->Data[1];
            CAN1_PELI->DATA4 = peli_transmit_message->Data[2];
            CAN1_PELI->DATA5 = peli_transmit_message->Data[3];
            CAN1_PELI->DATA6 = peli_transmit_message->Data[4];
            CAN1_PELI->DATA7 = peli_transmit_message->Data[5];
            CAN1_PELI->DATA8 = peli_transmit_message->Data[6];
            CAN1_PELI->DATA9 = peli_transmit_message->Data[7];
        }
    }

    (CAN1_PELI->MOD & CAN_MOD_STM) ? (CAN1->CMR = CAN_CMR_GTS | CAN_CMR_AT) : (CAN1->CMR = CAN_CMR_TR);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Receives a correct CAN frame.
/// @param  RxMessage: pointer to a structure receive frame which contains CAN
///         Id,CAN DLC, CAN data and FMI number.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_Receive(CanPeliRxMsg* peli_receive_message)
{
    u32 tempid;
    peli_receive_message->FF  = (CAN1_PELI->FF) >> 7;
    peli_receive_message->RTR = ((CAN1_PELI->FF) >> 6) & 0x1;
    peli_receive_message->DLC = (CAN1_PELI->FF) & 0xf;

    if (((FunctionalState)peli_receive_message->FF) != ENABLE) {
        tempid = (u32)(CAN1_PELI->ID1 >> 5);
        tempid |= (u32)(CAN1_PELI->ID0 << 3);
        peli_receive_message->ID      = tempid;
        peli_receive_message->Data[0] = CAN1_PELI->DATA0;
        peli_receive_message->Data[1] = CAN1_PELI->DATA1;
        peli_receive_message->Data[2] = CAN1_PELI->DATA2;
        peli_receive_message->Data[3] = CAN1_PELI->DATA3;
        peli_receive_message->Data[4] = CAN1_PELI->DATA4;
        peli_receive_message->Data[5] = CAN1_PELI->DATA5;
        peli_receive_message->Data[6] = CAN1_PELI->DATA6;
        peli_receive_message->Data[7] = CAN1_PELI->DATA7;
    }
    else {
        tempid = (u32)((CAN1_PELI->DATA1 & 0xf8) >> 3);
        tempid |= (u32)(CAN1_PELI->DATA0 << 5);
        tempid |= (u32)(CAN1_PELI->ID1 << 13);
        tempid |= (u32)(CAN1_PELI->ID0 << 21);
        peli_receive_message->ID      = tempid;
        peli_receive_message->Data[0] = CAN1_PELI->DATA2;
        peli_receive_message->Data[1] = CAN1_PELI->DATA3;
        peli_receive_message->Data[2] = CAN1_PELI->DATA4;
        peli_receive_message->Data[3] = CAN1_PELI->DATA5;
        peli_receive_message->Data[4] = CAN1_PELI->DATA6;
        peli_receive_message->Data[5] = CAN1_PELI->DATA7;
        peli_receive_message->Data[6] = CAN1_PELI->DATA8;
        peli_receive_message->Data[7] = CAN1_PELI->DATA9;
    }
    CAN_FIFORelease(CAN1);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Get available current informatoin in receive FIFO only in Peli
///         workmode.
/// @retval The value in reg RMC
////////////////////////////////////////////////////////////////////////////////
u32 CAN_Peli_GetRxFIFOInfo(void)
{
    return CAN1_PELI->RMC;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the CAN's last error code (LEC).
/// @retval Error code:
///          - CAN_ERRORCODE_NoErr: No Error
///          - CAN_ERRORCODE_StuffErr: Stuff Error
///          - CAN_ERRORCODE_FormErr: Form Error
///          - CAN_ERRORCODE_ACKErr : Acknowledgment Error
///          - CAN_ERRORCODE_BitRecessiveErr: Bit Recessive Error
///          - CAN_ERRORCODE_BitDominantErr: Bit Dominant Error
///          - CAN_ERRORCODE_CRCErr: CRC Error
///          - CAN_ERRORCODE_SoftwareSetErr: Software Set Error
////////////////////////////////////////////////////////////////////////////////
u8 CAN_Peli_GetLastErrorCode(void)
{
    // Return the error code
    return (u8)CAN1_PELI->ECC;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the CAN Receive Error Counter (REC).
/// @note   In case of an error during reception, this counter is incremented
///         by 1 or by 8 depending on the error condition as defined by the CAN
///         standard. After every successful reception, the counter is
///         decremented by 1 or reset to 120 if its value was higher than 128.
///         When the counter value exceeds 127, the CAN controller enters the
///         error passive state.
/// @retval CAN Receive Error Counter.
////////////////////////////////////////////////////////////////////////////////
u8 CAN_Peli_GetReceiveErrorCounter(void)
{
    // Return the Receive Error Counter
    return (u8)(CAN1_PELI->RXERR);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the LSB of the 9-bit can Transmit Error Counter(TEC).
/// @retval LSB of the 8-bit CAN Transmit Error Counter.
////////////////////////////////////////////////////////////////////////////////
u8 CAN_Peli_GetLSBTransmitErrorCounter(void)
{
    // Return the LSB of the 8-bit CAN Transmit Error Counter(TEC)
    return (u8)(CAN1_PELI->TXERR);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified CAN interrupts in peli workmode.
/// @param  it: specifies the CAN interrupt sources to be enabled or
///         disabled.
///         This parameter can be:
/// @arg    CAN_IT_RI: Receive FIFO not empty Interrupt
/// @arg    CAN_IT_TI: Transmit Interrupt
/// @arg    CAN_IT_EI: ERROR Interrupt
/// @arg    CAN_IT_DOI: Data voerflow Interrupt
/// @arg    CAN_IT_WUI: Wakeup Interrupt
/// @arg    CAN_IT_EPI(only Peli): passive error Interrupt
/// @arg    CAN_IT_ALI(only Peli): arbiter lose Interrupt
/// @arg    CAN_IT_BEI(only Peli): bus error Interrupt
/// @arg    CAN_IT_ALL: use it can enble all Interrupt
/// @param  state: new state of the CAN interrupts.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Peli_ITConfig(u32 it, FunctionalState state)
{
    (state) ? (CAN1_PELI->IER |= it) : (CAN1_PELI->IER &= ~it);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified CAN interrupt has occurred or not.
/// @param  it: specifies the CAN interrupt source to check.
///         This parameter can be one of the following values:
/// @arg    CAN_IT_RI: Receive FIFO not empty Interrupt
/// @arg    CAN_IT_TI: Transmit Interrupt
/// @arg    CAN_IT_EI: ERROR Interrupt
/// @arg    CAN_IT_DOI: Data voerflow Interrupt
/// @arg    CAN_IT_WUI: Wakeup Interrupt
/// @arg    CAN_IT_EPI(only Peli): passive error Interrupt
/// @arg    CAN_IT_ALI(only Peli): arbiter lose Interrupt
/// @arg    CAN_IT_BEI(only Peli): bus error Interrupt
/// @arg    CAN_IT_ALL: use it can enble all Interrupt
/// @retval The current state of it (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus CAN_Peli_GetITStatus(u32 it)
{
    return (ITStatus)(((CAN1_PELI->IR & it) != it) ? RESET : SET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Config CAN_Peli_InitTypeDef baud parameter.
/// @param  CAN_Peli_InitTypeDef: CAN struct.
/// @param  src_clk: CAN module clock.
/// @param  baud: specified baud.
/// @retval The current state of it (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
void CAN_AutoCfg_BaudParam(CAN_Peli_InitTypeDef* init_struct, u32 src_clk, u32 baud)
{
    u32 i, value = baud, record = 1;
    u32 remain = 0, sumPrescaler = 0;
    while ((baud == 0) || (src_clk == 0))
        ;
    sumPrescaler = src_clk / baud;
    sumPrescaler = sumPrescaler / 2;
    for (i = 25; i > 3; i--) {
        remain = sumPrescaler - ((sumPrescaler / i) * i);
        if (remain == 0) {
            record = i;
            break;
        }
        else {
            if (remain < value) {
                value  = remain;
                record = i;
            }
        }
    }
    init_struct->SJW   = 0;
    init_struct->BRP   = (sumPrescaler / record) - 1;
    init_struct->TESG2 = (record - 3) / 3;
    init_struct->TESG1 = (record - 3) - init_struct->TESG2;
}

/// @}

/// @}

/// @}



