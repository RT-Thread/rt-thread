/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_exit.c
 * @brief    source file for setting exit
 *
 * Change Logs:
 * Date            Author             Version        Notes
 * 2021-12-24      yangzhengfeng      V1.0.0         Modify the register module configuration
 * 2021-01-03      wangjingfan        V1.0.1         Compile error correction
 * 2021-01-20      yangzhengfeng      V1.0.2         Update library function
 */

#include "yc_exti.h"

/**
  * @brief  Clear interrupt flag
  * @param  EXTI_Line:EXTI_Line_0...EXTI_Line_4
  * @param  EXTI_PinSource:EXTI_PinSource0...EXTI_PinSource15
  * @retval none
  */
void EXTI_ClearITPendingBit(EXTI_LineTypeDef EXTI_Line, EXTI_PIN_TypeDef EXTI_PinSource)
{
    _ASSERT(IS_EXTI_LINE(EXTI_Line));
    _ASSERT(IS_EXTI_PIN_SOURCE(EXTI_PinSource));

    MGPIO->IRQ_STATUS.reg[EXTI_Line] |= EXTI_PinSource;
}

/**
  * @brief  Deinitializes the EXTI registers to default reset values.
  * @param  none
  * @retval none
  */
void EXTI_DeInit()
{
    uint32_t i;

    for (i = 0; i < EXIT_Num; i++)
    {
        MGPIO->INTR.reg[i]           = 0;
        MGPIO->IRQ_LEVEL.reg[i]            = 0;
        MGPIO->IRQ_RISE.reg[i]            = 0;
        MGPIO->IRQ_FALL.reg[i]            = 0;
    }
}

/**
  * @brief  get interrupt status
  * @param  EXTI_Line:EXTI_Line_0...EXTI_Line_4
  * @retval none
  */
uint16_t EXTI_GetITLineStatus(EXTI_LineTypeDef EXTI_Line)
{
    _ASSERT(IS_EXTI_LINE(EXTI_Line));

    return MGPIO->INTR.reg[EXTI_Line];
}

/**
  * @brief  get interrupt pinsource status
  * @param  EXTI_Line:EXTI_Line_0...EXTI_Line_4
  * @param  EXTI_PinSource:EXTI_PinSource0...EXTI_PinSource15
  * @retval none
  */
uint16_t EXTI_GetITEXTI_PinSourceStatus(EXTI_LineTypeDef EXTI_Line, EXTI_PIN_TypeDef EXTI_PinSource)
{
    _ASSERT(IS_EXTI_LINE(EXTI_Line));
    _ASSERT(IS_EXTI_PIN_SOURCE(EXTI_PinSource));

    if(MGPIO->INTR.reg[EXTI_Line] & EXTI_PinSource)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }

}

/**
  * @brief  EXTI LineConfig
  * @param  EXTI_Line:EXTI_Line_0...EXTI_Line_4
  * @param  EXTI_PinSource:EXTI_PinSource0...EXTI_PinSource15
  * @param  EXTI_Trigger:EXTI Trigger mode
  * @retval none
  */
void EXTI_LineConfig(EXTI_LineTypeDef EXTI_Line, EXTI_PIN_TypeDef EXTI_PinSource, EXTI_TriggerTypeDef EXTI_Trigger)
{
    _ASSERT(IS_EXTI_LINE(EXTI_Line));
    _ASSERT(IS_EXTI_PIN_SOURCE(EXTI_PinSource));
    _ASSERT(IS_TRIG_TYPEDEF(EXTI_Trigger));

    uint16_t val_intr_lts,val_intr_rts,val_intr_fts,val_intr_en;
    switch (EXTI_Trigger)
    {
    case EXTI_Trigger_Off:
        val_intr_en  = ~EXTI_PinSource;
        val_intr_lts = ~EXTI_PinSource;
        val_intr_rts = ~EXTI_PinSource;
        val_intr_fts = ~EXTI_PinSource;
        break;
    case EXTI_Trigger_HighLev:
        val_intr_en  = EXTI_PinSource;
        val_intr_lts = ~EXTI_PinSource;
        val_intr_rts = ~EXTI_PinSource;
        val_intr_fts = ~EXTI_PinSource;
        break;
    case EXTI_Trigger_LowLev:
        val_intr_en  = EXTI_PinSource;
        val_intr_lts = EXTI_PinSource;
        val_intr_rts = ~EXTI_PinSource;
        val_intr_fts = ~EXTI_PinSource;
        break;
    case EXTI_Trigger_Rising:
        val_intr_en  = EXTI_PinSource;
        val_intr_lts = ~EXTI_PinSource;
        val_intr_rts = EXTI_PinSource;
        val_intr_fts = ~EXTI_PinSource;
        break;
    case EXTI_Trigger_Falling:
        val_intr_en  = EXTI_PinSource;
        val_intr_lts = ~EXTI_PinSource;
        val_intr_rts = ~EXTI_PinSource;
        val_intr_fts = EXTI_PinSource;
        break;
    case EXTI_Trigger_Rising_Falling:
        val_intr_en  = EXTI_PinSource;
        val_intr_lts = ~EXTI_PinSource;
        val_intr_rts = EXTI_PinSource;
        val_intr_fts = EXTI_PinSource;
        break;
    default:
        break;
    }
    if (EXTI_Trigger == EXTI_Trigger_Off)
    {
        MGPIO->INTR.reg[EXTI_Line] &= val_intr_en;
        MGPIO->IRQ_LEVEL.reg[EXTI_Line]  &= val_intr_lts;
        MGPIO->IRQ_RISE.reg[EXTI_Line]  &= val_intr_rts;
        MGPIO->IRQ_FALL.reg[EXTI_Line]  &= val_intr_fts;
    }
    else if (EXTI_Trigger == EXTI_Trigger_HighLev )
    {
        MGPIO->IRQ_LEVEL.reg[EXTI_Line]  &= val_intr_lts;
        MGPIO->IRQ_RISE.reg[EXTI_Line]  &= val_intr_rts;
        MGPIO->IRQ_FALL.reg[EXTI_Line]  &= val_intr_fts;
        MGPIO->INTR.reg[EXTI_Line] |= val_intr_en;
    }
    else if (EXTI_Trigger == EXTI_Trigger_LowLev )
    {
        MGPIO->IRQ_LEVEL.reg[EXTI_Line]  |= val_intr_lts;
        MGPIO->IRQ_RISE.reg[EXTI_Line]  &= val_intr_rts;
        MGPIO->IRQ_FALL.reg[EXTI_Line]  &= val_intr_fts;
        MGPIO->INTR.reg[EXTI_Line] |= val_intr_en;
    }
    else if (EXTI_Trigger == EXTI_Trigger_Rising )
    {
        MGPIO->IRQ_LEVEL.reg[EXTI_Line]  &= val_intr_lts;
        MGPIO->IRQ_RISE.reg[EXTI_Line]  |= val_intr_rts;
        MGPIO->IRQ_FALL.reg[EXTI_Line]  &= val_intr_fts;
        MGPIO->INTR.reg[EXTI_Line] |= val_intr_en;
    }
    else if (EXTI_Trigger == EXTI_Trigger_Falling )
    {
        MGPIO->IRQ_LEVEL.reg[EXTI_Line]  &= val_intr_lts;
        MGPIO->IRQ_RISE.reg[EXTI_Line]  &= val_intr_rts;
        MGPIO->IRQ_FALL.reg[EXTI_Line]  |= val_intr_fts;
        MGPIO->INTR.reg[EXTI_Line] |= val_intr_en;
    }
    else if (EXTI_Trigger == EXTI_Trigger_Rising_Falling )
    {
        MGPIO->IRQ_LEVEL.reg[EXTI_Line]  &= val_intr_lts;
        MGPIO->IRQ_RISE.reg[EXTI_Line]  |= val_intr_rts;
        MGPIO->IRQ_FALL.reg[EXTI_Line]  |= val_intr_fts;
        MGPIO->INTR.reg[EXTI_Line] |= val_intr_en;
    }
}

//extern void VBAT_IRQHandler(void);
//extern void EXTI0_IRQHandler(void);
//extern void EXTI1_IRQHandler(void);
//extern void EXTI2_IRQHandler(void);
//extern void EXTI3_IRQHandler(void);
//extern void EXTI4_IRQHandler(void);

//void GPIO_IRQHandler()
//{
//    uint8_t Exti_irq_index;

//    NVIC_DisableIRQ(GPIO_IRQn);

//    if (MSYSCTRL->CHGR_EVENT_IRQ.bit.VBAT_OV & MSYSCTRL->CHGR_EVENT_ICTRL.bit.VBAT_OV_IE)
//    {
//        //VBAT_IRQHandler();
//    }

//    Exti_irq_index = MGPIO->IRQ_NUM.reg;
//    if(MGPIO->INTR.reg[Exti_irq_index/EXIT_Pin_Num] &(1 << (Exti_irq_index%EXIT_Pin_Num)))
//    {
//        switch (Exti_irq_index/EXIT_Pin_Num)
//        {
//        case EXTI_Line_0:
//            EXTI0_IRQHandler();
//            break;
//        case EXTI_Line_1:
//            EXTI1_IRQHandler();
//            break;
//        case EXTI_Line_2:
//            EXTI2_IRQHandler();
//            break;
//        case EXTI_Line_3:
//            EXTI3_IRQHandler();
//            break;

//        case EXTI_Line_4:
//            EXTI4_IRQHandler();
//            break;
//        default:
//            break;
//        }
//        EXTI_ClearITPendingBit((EXTI_LineTypeDef)(Exti_irq_index/EXIT_Pin_Num),(EXTI_PIN_TypeDef)(BIT(Exti_irq_index%EXIT_Pin_Num)));
//    }
//    NVIC_EnableIRQ(GPIO_IRQn);
//}

/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
