////////////////////////////////////////////////////////////////////////////////
/// @file     hal_dma.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE DMA FIRMWARE FUNCTIONS.
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
#define _HAL_DMA_C_

// Files includes
#include "types.h"
#include "hal_dma.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DMA_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DMA_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the DMA Channeln registers to their default reset
///         values.
/// @param   select the DMA Channel.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_DeInit(DMA_Channel_TypeDef* channel)
{
    channel->CCR &= ~DMA_CCR_EN;
    channel->CCR   = 0;
    channel->CNDTR = 0;
    channel->CPAR  = 0;
    channel->CMAR  = 0;
    if((*(vu32*)&channel) >= (*(vu32*)DMA2_Channel1_BASE)) {
        DMA2->IFCR |= (u32)0x0F << (((*(vu32*)&channel & (u32)0xff) - 8) / 5);
    }
    else {
        DMA1->IFCR |= (u32)0x0F << (((*(vu32*)&channel & (u32)0xff) - 8) / 5);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the DMA Channeln according to the specified
///         parameters in the init_struct.
/// @param  select the DMA Channel.
/// @param  init_struct: pointer to a DMA_InitTypeDef structure that
///         contains the configuration information for the specified DMA
///         Channel.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_Init(DMA_Channel_TypeDef* channel, DMA_InitTypeDef* init_struct)
{
    MODIFY_REG(
        channel->CCR,
        (DMA_CCR_DIR | DMA_CCR_CIRC | DMA_CCR_PINC | DMA_CCR_MINC | DMA_CCR_PSIZE | DMA_CCR_MSIZE | DMA_CCR_PL | DMA_CCR_M2M),
        ((u32)init_struct->DMA_DIR | (u32)init_struct->DMA_Mode | (u32)init_struct->DMA_PeripheralInc |
         (u32)init_struct->DMA_MemoryInc | (u32)init_struct->DMA_PeripheralDataSize | (u32)init_struct->DMA_MemoryDataSize |
         (u32)init_struct->DMA_Priority | (u32)init_struct->DMA_M2M));

    MODIFY_REG(channel->CCR, DMA_CCR_ARE, init_struct->DMA_Auto_reload);
    channel->CNDTR = init_struct->DMA_BufferSize;
    channel->CPAR  = init_struct->DMA_PeripheralBaseAddr;
    channel->CMAR  = init_struct->DMA_MemoryBaseAddr;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each init_struct member with its default value.
/// @param  init_struct : pointer to a DMA_InitTypeDef structure which will
///         be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_StructInit(DMA_InitTypeDef* init_struct)
{
    init_struct->DMA_PeripheralBaseAddr = 0;
    init_struct->DMA_MemoryBaseAddr     = 0;
    init_struct->DMA_DIR                = DMA_DIR_PeripheralSRC;
    init_struct->DMA_BufferSize         = 0;
    init_struct->DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    init_struct->DMA_MemoryInc          = DMA_MemoryInc_Disable;
    init_struct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    init_struct->DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    init_struct->DMA_Mode               = DMA_Mode_Normal;
    init_struct->DMA_Priority           = DMA_Priority_Low;
    init_struct->DMA_M2M                = DMA_M2M_Disable;

    init_struct->DMA_Auto_reload         = DMA_Auto_Reload_Disable;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified DMA Channeln.
/// @param  channel: select the DMA Channel.
/// @param  state: new state of the DMA Channeln.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_Cmd(DMA_Channel_TypeDef* channel, FunctionalState state)
{
    MODIFY_REG(channel->CCR, DMA_CCR_EN, state << DMA_CCR_EN_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified DMA Channeln interrupts.
/// @param  channel: select the DMA Channel.
/// @param  it: specifies the DMA interrupts sources to be enabled
///         or disabled.
///         This parameter can be any combination of the following values:
///    @arg DMA_IT_TC:  Transfer complete interrupt mask
///    @arg DMA_IT_HT:  Half transfer interrupt mask
///    @arg DMA_IT_TE:  Transfer error interrupt mask
/// @param  state: new state of the specified DMA interrupts.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_ITConfig(DMA_Channel_TypeDef* channel, DMA_Interrupt_EN_TypeDef it, FunctionalState state)
{
    (state) ? (channel->CCR |= it) : (channel->CCR &= ~it);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of data units in the select the DMA Channel .
/// @param  channel: select the DMA Channel
/// @param  DataNumber: The number of data units in the current DMAy Channelx
///         transfer.
/// @note   This function can only be used when the DMAy_Channelx is disabled.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* channel, u16 length)
{
    channel->CNDTR = length;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the number of remaining data units in the current
///         DMA Channeln transfer.
/// @param  channel: select the DMA Channel.
/// @retval The number of remaining data units in the current DMA Channeln
///         transfer.
////////////////////////////////////////////////////////////////////////////////
u16 DMA_GetCurrDataCounter(DMA_Channel_TypeDef* channel)
{
    return channel->CNDTR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified DMA Channeln flag is set or not.
/// @param  flag: specifies the flag to check.
///         This parameter can be one of the following values:
///    @arg DMA1_FLAG_GLn: DMA1 Channeln global flag(n = 1..7).
///    @arg DMA1_FLAG_TCn: DMA1 Channeln transfer complete flag(n = 1..7).
///    @arg DMA1_FLAG_HTn: DMA1 Channeln half transfer flag(n = 1..7).
///    @arg DMA1_FLAG_TEn: DMA1 Channeln transfer error flag(n = 1..7).
///    @arg DMA2_FLAG_GLn: DMA1 Channeln global flag(n = 1..5).
///    @arg DMA2_FLAG_TCn: DMA1 Channeln transfer complete flag(n = 1..5).
///    @arg DMA2_FLAG_HTn: DMA1 Channeln half transfer flag(n = 1..5).
///    @arg DMA2_FLAG_TEn: DMA1 Channeln transfer error flag(n = 1..5).
/// @retval The new state of DMAy_FLAG (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus DMA_GetFlagStatus(DMA_Flags_TypeDef flag)
{
    if(flag >= DMA2_FLAG_GL1 ) {
        return (DMA2->ISR & flag) ? SET : RESET;
    }
    return (DMA1->ISR & flag) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the DMA Channeln's pending flags.
/// @param  flag: specifies the flag to clear.
///         This parameter can be any combination (for the same DMA) of the
///         following values:
///    @arg DMA1_FLAG_GLn: DMA1 Channeln global flag(n = 1..7).
///    @arg DMA1_FLAG_TCn: DMA1 Channeln transfer complete flag(n = 1..7).
///    @arg DMA1_FLAG_HTn: DMA1 Channeln half transfer flag(n = 1..7).
///    @arg DMA1_FLAG_TEn: DMA1 Channeln transfer error flag(n = 1..7).
///    @arg DMA2_FLAG_GLn: DMA1 Channeln global flag(n = 1..5).
///    @arg DMA2_FLAG_TCn: DMA1 Channeln transfer complete flag(n = 1..5).
///    @arg DMA2_FLAG_HTn: DMA1 Channeln half transfer flag(n = 1..5).
///    @arg DMA2_FLAG_TEn: DMA1 Channeln transfer error flag(n = 1..5).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_ClearFlag(DMA_Flags_TypeDef flag)
{
    if(flag >= DMA2_FLAG_GL1 ) {
        DMA2->IFCR = flag;
        return ;
    }
    DMA1->IFCR = flag;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified DMA Channeln interrupt has occurred or
/// not.
/// @param  it: specifies the DMA interrupt source to check.
///         This parameter can be one of the following values:
///    @arg DMA1_IT_GLn: DMA1 Channeln global interrupt(n = 1..7).
///    @arg DMA1_IT_TCn: DMA1 Channeln transfer complete interrupt(n = 1..7).
///    @arg DMA1_IT_HTn: DMA1 Channeln half transfer interrupt(n = 1..7).
///    @arg DMA1_IT_TEn: DMA1 Channeln transfer error interrupt(n = 1..7).
///    @arg DMA2_IT_GLn: DMA1 Channeln global flag(n = 1..5).
///    @arg DMA2_IT_TCn: DMA1 Channeln transfer complete flag(n = 1..5).
///    @arg DMA2_IT_HTn: DMA1 Channeln half transfer flag(n = 1..5).
///    @arg DMA2_IT_TEn: DMA1 Channeln transfer error flag(n = 1..5).
/// @retval  The new state of DMAy_IT (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus DMA_GetITStatus(DMA_Interrupts_TypeDef it)
{
    if(it >= DMA2_IT_GL1 ) {
        return (DMA2->ISR & it) ? SET : RESET;
    }
    return (DMA1->ISR & it) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the DMA Channeln's interrupt pending bits.
/// @param  it: specifies the DMA interrupt pending bit to clear.
///         This parameter can be any combination (for the same DMA) of the
///         following values:
///    @arg DMA1_IT_GLn: DMA1 Channeln global interrupt(n = 1..7).
///    @arg DMA1_IT_TCn: DMA1 Channeln transfer complete interrupt(n = 1..7).
///    @arg DMA1_IT_HTn: DMA1 Channeln half transfer interrupt(n = 1..7).
///    @arg DMA1_IT_TEn: DMA1 Channeln transfer error interrupt(n = 1..7).
///    @arg DMA2_IT_GLn: DMA1 Channeln global flag(n = 1..5).
///    @arg DMA2_IT_TCn: DMA1 Channeln transfer complete flag(n = 1..5).
///    @arg DMA2_IT_HTn: DMA1 Channeln half transfer flag(n = 1..5).
///    @arg DMA2_IT_TEn: DMA1 Channeln transfer error flag(n = 1..5).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_ClearITPendingBit(DMA_Interrupts_TypeDef it)
{
    if(it >= DMA2_IT_GL1 ) {
        DMA2->IFCR = it;
        return ;
    }
    DMA1->IFCR = it;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the DMA Channeln's Peripheral address.
/// @param  channel : where n can be 1 to 7 for DMA1 to select the DMA Channel.
/// @param  address : DMA Peripheral address.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exDMA_SetPeripheralAddress(DMA_Channel_TypeDef* channel, u32 address)
{
    channel->CPAR = address;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the DMA Channeln's Peripheral address.
/// @param  channel : select the DMA Channel.
/// @param  length : Transmit lengths.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exDMA_SetTransmitLen(DMA_Channel_TypeDef* channel, u16 length)
{
    channel->CNDTR = length;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the DMA Channeln's Peripheral address.
/// @param  channel :select the DMA Channel.
/// @param  address : DMA memery address.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exDMA_SetMemoryAddress(DMA_Channel_TypeDef* channel, u32 address)
{
    channel->CMAR = address;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the DMA Channeln's interrupt pending bits.
/// @param  it: specifies the DMA interrupt pending bit to clear.
///         This parameter can be any combination (for the same DMA) of the
///         following values:
///    @arg DMA1_IT_GLn: DMA1 Channeln global interrupt(n = 1..7).
///    @arg DMA1_IT_TCn: DMA1 Channeln transfer complete interrupt(n = 1..7).
///    @arg DMA1_IT_HTn: DMA1 Channeln half transfer interrupt(n = 1..7).
///    @arg DMA1_IT_TEn: DMA1 Channeln transfer error interrupt(n = 1..7).
///    @arg DMA2_IT_GLn: DMA1 Channeln global flag(n = 1..5).
///    @arg DMA2_IT_TCn: DMA1 Channeln transfer complete flag(n = 1..5).
///    @arg DMA2_IT_HTn: DMA1 Channeln half transfer flag(n = 1..5).
///    @arg DMA2_IT_TEn: DMA1 Channeln transfer error flag(n = 1..5).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exDMA_ClearITPendingBit(DMA_Channel_TypeDef* channel, u32 it)
{
    if(it >= DMA2_IT_GL1 ) {
        DMA2->IFCR |= (u32)0x0F << (((*(vu32*)&channel & (u32)0xff) - 8) / 5);
        DMA2->IFCR = it;
        return ;
    }
    DMA1->IFCR |= (u32)0x0F << (((*(vu32*)&channel & (u32)0xff) - 8) / 5);
    DMA1->IFCR = it;
}
/// @}

/// @}

/// @}
