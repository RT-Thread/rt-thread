////////////////////////////////////////////////////////////////////////////////
/// @file     hal_comp.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE COMP FIRMWARE FUNCTIONS.
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
#define _HAL_COMP_C_

// Files includes
#include "hal_comp.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup COMP_HAL
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup COMP_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes COMP peripheral registers to their default reset
///         values.
/// @param  selection: the selected comparator.
///         select the COMP peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_DeInit(COMP_Selection_TypeDef selection)
{
    *(vu32*)(COMP_BASE + selection) = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the COMP peripheral according to the specified
/// @param  selection: the selected comparator.
///         select the COMP peripheral.
/// @param  init_struct: pointer to an COMP_InitTypeDef structure that
///         contains the configuration information for the specified COMP
///         peripheral.
///         - COMP_InvertingInput specifies the inverting input of COMP
///         - COMP_NonInvertingInput specifies the non inverting input of COMP
///         - COMP_Output connect COMP output to selected timer
///           input (Input capture / Output Compare Reference Clear / Break
///           Input)
///         - COMP_BlankingSrce specifies the blanking source of COMP
///         - COMP_OutputPol select output polarity
///         - COMP_Hysteresis configures COMP hysteresis value
///         - COMP_Mode configures COMP power mode
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_Init(COMP_Selection_TypeDef selection, COMP_InitTypeDef* init_struct)
{
    *(vu32*)(COMP_BASE + selection) =    init_struct->Invert     |
                                         init_struct->NonInvert  |
                                         init_struct->Output     |
                                         init_struct->OutputPol  |
                                         init_struct->BlankingSrce   |
                                         init_struct->Hysteresis |
                                         init_struct->Mode       |
                                         init_struct->OFLT;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each init_struct member with its default value.
/// @param  init_struct: pointer to an COMP_InitTypeDef structure which will
///         be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_StructInit(COMP_InitTypeDef* init_struct)
{

    init_struct->Invert         = COMP_InvertingInput_IO1;
    init_struct->NonInvert      = COMP_NonInvertingInput_IO1;
    init_struct->Output         = COMP_Output_None;
    init_struct->BlankingSrce   = COMP_BlankingSrce_None;
    init_struct->OutputPol      = COMP_NonInverted;
    init_struct->Hysteresis     = COMP_Hysteresis_No;
    init_struct->Mode           = COMP_Mode_UltraLowPower;
    init_struct->OFLT           = COMP_Filter_4_Period;                                                               ///< to adjust the speed/consumption.
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable or disable the COMP peripheral.
/// @param  selection: the selected comparator.
///         select the COMP peripheral.
/// @param  NewState: new state of the COMP peripheral.
///         This parameter can be: ENABLE or DISABLE.
///         When enabled, the comparator compares the non inverting input with
///         the inverting input and the comparison result is available on
///         comparator output.
///         When disabled, the comparator doesn't perform comparison and the
///         output level is low.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_Cmd(COMP_Selection_TypeDef selection, FunctionalState state)
{
    (state) ? (*(vu32*)(COMP_BASE + selection) |=  COMP_CSR_EN) :
    (*(vu32*)(COMP_BASE + selection) &= ~COMP_CSR_EN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Select CRV param.
/// @param  crv_select: Select source for CRV.
/// @param  crv_level: Set level for CRV.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_SetCrv(u8 crv_select, u8 crv_level)
{
    u32 temreg = 0;
    temreg = COMP->CRV;
    temreg &= ~COMP_CRV_MASK;
    // Load config to CRV and enable
    temreg |= crv_select | crv_level | (1 << 4);
    COMP->CRV = temreg;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Close or Open the SW1 switch.
/// @param  selection: the selected comparator.
///         select the COMP peripheral.
/// @param  state: new state of the COMP peripheral.
///         This parameter can be: ENABLE or DISABLE.
///         When enabled, the comparator compares the non inverting input with
///         the inverting input and the comparison result is available on
///         comparator output.
///         When disabled, the comparator doesn't perform comparison and the
///         output level is low.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_SwitchCmd(COMP_Selection_TypeDef selection, FunctionalState state)
{
    (state) ?
    (*(vu32*)(COMP_BASE + selection) |=  COMP_CSR_COMPSW1) :
    (*(vu32*)(COMP_BASE + selection) &= ~COMP_CSR_COMPSW1);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Return the output level (high or low) of the selected comparator.
///         The output level depends on the selected polarity.
///         If the polarity is not inverted:
///           - Comparator output is low when the non-inverting input is at a
///           lower voltage than the inverting input
///           - Comparator output is high when the non-inverting input is at a
///           higher voltage than the inverting input
///         If the polarity is inverted:
///           - Comparator output is high when the non-inverting input is at a
///           lower voltage than the inverting input
///           - Comparator output is low when the non-inverting input is at a
///           higher voltage than the inverting input
/// @param  comp: the selected comparator.
///         select the COMP peripheral.
/// @retval  The selected comparator output level: low or high.
////////////////////////////////////////////////////////////////////////////////
u32 COMP_GetOutputLevel(COMP_Selection_TypeDef selection)
{
    return (((*(vu32*)(COMP_BASE + selection) & COMP_CSR_STA) != 0) ?
            COMP_OutputLevel_High :
            COMP_OutputLevel_Low );
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Lock the selected comparator (COMP1/COMP2) configuration.
/// @param  selection: the selected comparator.
///         select the COMP peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_LockConfig(COMP_Selection_TypeDef selection)
{
    *(vu32*)(COMP_BASE + selection) |= COMP_CSR_LOCK;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable or disable the COMP register.
/// @param  state: new state of the COMP peripheral.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exCOMP_CrvCmd(FunctionalState state)
{
    (state) ? (COMP->CRV |= COMP_CRV_EN_ENABLE) : (COMP->CRV &= ~COMP_CRV_EN_ENABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Select comparator external reference voltage.
/// @param  selection: the selected external reference voltage.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exCOMP_SwitchCrv(u32 crv)
{
    COMP->CRV |= crv;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Select comparator external reference voltage source.
/// @param  selection: the selected external reference voltage source.
///         This parameter can be: COMP_CRV_SRC_AVDD or COMP_CRV_SRC_VREF.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exCOMP_CrvSrc(u32 src)
{
    COMP->CRV |= src;
}





/// @}

/// @}

/// @}
