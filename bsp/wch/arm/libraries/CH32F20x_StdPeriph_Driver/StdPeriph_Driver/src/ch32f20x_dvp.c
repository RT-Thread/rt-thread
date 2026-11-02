/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_dvp.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the DVP firmware functions. 
*******************************************************************************/ 
#include "ch32f20x_dvp.h"


/*******************************************************************************
* Function Name  : DVP_INTCfg
* Description    : DVP interrupt configuration
* Input          : s: interrupt enable
                    ENABLE
                    DISABLE
                   i: interrupt type
                    RB_DVP_IE_STP_FRM
                    RB_DVP_IE_FIFO_OV
                    RB_DVP_IE_FRM_DONE
                    RB_DVP_IE_ROW_DONE
                    RB_DVP_IE_STR_FRM
* Return         : None
*******************************************************************************/
void DVP_INTCfg( uint8_t s,  uint8_t i )
{
    if(s){
        DVP->IER |= i;
    }
    else{
        DVP->IER &= ~i;
    }
}

/*******************************************************************************
* Function Name  : DVP_Mode
* Description    : DVP mode
* Input          : s: data bit width
                    RB_DVP_D8_MOD
                    RB_DVP_D10_MOD
                    RB_DVP_D12_MOD
                   i: data mode
                    Video_Mode
                    JPEG_Mode
* Return         : None
*******************************************************************************/
void DVP_Mode( uint8_t s,  DVP_Data_ModeTypeDef i)
{
    DVP->CR0 &= ~RB_DVP_MSK_DAT_MOD;

    if(s){
        DVP->CR0 |= s;
    }
    else{
        DVP->CR0 &= ~((uint32_t)3<<4);
    }

    if(i){
        DVP->CR0 |= RB_DVP_JPEG;
    }
    else{
        DVP->CR0 &= ~RB_DVP_JPEG;
    }
}

/*******************************************************************************
* Function Name  : DVP_Cfg
* Description    : DVP configuration
* Input          : s:  DMA enable control
                    DVP_DMA_Enable
                    DVP_DMA_Disable
                   i: DVP all clear
                    DVP_FLAG_FIFO_RESET_Enable
                    DVP_FLAG_FIFO_RESET_Disable
                   j:  receive reset enable
                    DVP_RX_RESET_Enable
                    DVP_RX_RESET_Disable
* Return         : None
*******************************************************************************/
void DVP_Cfg( DVP_DMATypeDef s,  DVP_FLAG_FIFO_RESETTypeDef i, DVP_RX_RESETTypeDef j)
{
    switch( s )
    {
        case DVP_DMA_Enable:
            DVP->CR1 |= RB_DVP_DMA_EN;
            break;
        case DVP_DMA_Disable:
            DVP->CR1 &= ~RB_DVP_DMA_EN;
            break;
        default:
            break;
    }

    switch( i )
    {
        case DVP_RX_RESET_Enable:
            DVP->CR1 |= RB_DVP_ALL_CLR;
            break;
        case DVP_RX_RESET_Disable:
            DVP->CR1 &= ~RB_DVP_ALL_CLR;
            break;
        default:
            break;
    }

    switch( j )
    {
        case DVP_RX_RESET_Enable:
            DVP->CR1 |= RB_DVP_RCV_CLR;
            break;
        case DVP_RX_RESET_Disable:
            DVP->CR1 &= ~RB_DVP_RCV_CLR;
            break;
        default:
            break;
    }

}
