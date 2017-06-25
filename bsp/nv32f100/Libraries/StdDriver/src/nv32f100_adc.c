/**************************************************************************!
 *     ¼¼ÊõÌÖÂÛ£ºQQÈº  123763203
 *     ¹ÙÍø    £ºwww.navota.com
 *
 * @file       adc.c
 * @brief      ÊýÄ£×ª»»Ä£¿é(ADC)¿âº¯Êý¯Êý¿â
 * @author     Navota
 * @date       2017-1-1
 ****************************************************************************/
 
#include "nv32f100.h"

/****************************************************************************!
 * @ ´æ·ÅACMP»Øµ÷º¯Êý½Ó¿Ú
 ****************************************************************************/
ADC_CallbackType ADC_Callback[1] = {NULL};

/*****************************************************************************//**
   *
   * @brief  ³õÊ¼»¯ADCÄ£¿é.
   *
   * @param[in]  pADC         Ö¸ÏòADCÄ£¿éÀàÐÍ.
   * @param[in]  pADC_Config  Ö¸ÏòADCÄ£¿éÅäÖÃ½á¹¹Ìå
   *
   * @return none
   *
   *****************************************************************************/
void ADC_Init(ADC_Type *pADC, ADC_ConfigTypePtr pADC_Config)
{
    if( pADC == ADC)
    {
        SIM->SCGC |= SIM_SCGC_ADC_MASK;
    }
    /* Ñ¡ÔñADCÄ£¿éÊ±ÖÓÔ´ */
    ADC_SelectClock(pADC,pADC_Config->u8ClockSource);
    /* Éè¶¨Ê±ÖÓ·ÖÆµ */
    ADC_SelectClockDivide(pADC,pADC_Config->u8ClockDiv);
    /* ÉèÖÃADC×ª»»Ä£Ê½ */
    ADC_SetMode(pADC,pADC_Config->u8Mode);
    /* ÉèÖÃFIFOÉî¶È */
    ADC_SetFifoLevel(pADC,pADC_Config->u8FiFoLevel);
    /* ADCÊäÈëÒý½Å¿ØÖÆ */
    pADC->APCTL1 = pADC_Config->u16PinControl;
    if( pADC_Config->sSetting.bCompareEn )
    {
        ADC_CompareEnable(pADC);     //Ê¹ÄÜADC±È½Ï¹¦ÄÜ
    }
    if( pADC_Config->sSetting.bCompareGreaterEn )
    {
        ADC_CompareGreaterFunction(pADC);  //ÊäÈë´óÓÚ»òµÈÓÚ±È½ÏµçÆ½Ê±±È½Ï´¥·¢
    }
    if( pADC_Config->sSetting.bContinuousEn )
    {
        ADC_ContinuousConversion(pADC);    // Ê¹ÄÜADCÁ¬Ðø×ª»».
    }
    if( pADC_Config->sSetting.bCompareAndEn )
    {
        ADC_CompareFifoAnd(pADC);     //¶ÔËùÓÐ±È½Ï´¥·¢×öÓëÔËËã
    }
    if( pADC_Config->sSetting.bFiFoScanModeEn )
    {
        ADC_FifoScanModeEnable(pADC);  //Ê¹ÄÜFIFOÉ¨ÃèÄ£Ê½
    }
    if( pADC_Config->sSetting.bHardwareTriggerEn )
    {
        ADC_SetHardwareTrigger(pADC);  // ÉèÖÃADCÓ²¼þ´¥·¢.
    }
    if( pADC_Config->sSetting.bIntEn )  //Ê¹ÄÜÖÐ¶Ï
    {
        ADC_IntEnable(pADC);
        NVIC_EnableIRQ( ADC0_IRQn );
    }
    if( pADC_Config->sSetting.bLongSampleEn )
    {
        ADC_SetLongSample(pADC);   // ÉèÖÃADC³¤²ÉÑù.
    }
    if( pADC_Config->sSetting.bLowPowerEn )
    {
        ADC_SetLowPower(pADC);   // ÉèÖÃADCÎªµÍ¹¦ºÄÄ£Ê½
    }
#if !defined(CPU_NV32)
    if( pADC_Config->sSetting.bHTRGMEn )
    {
        ADC_HardwareTriggerMultiple(pADC);
    }
    else
    {
        ADC_HardwareTriggerSingle(pADC);
    }
    if( pADC_Config->sSetting.bHTRGMASKEn )
    {
        ADC_HardwareTriggerMaskEnable(pADC);
    }
    else
    {
        ADC_HardwareTriggerMaskDisable(pADC);
    }
    if( pADC_Config->sSetting.bHTRGMASKSEL )
    {
        ADC_HardwareTriggerMaskAuto(pADC);
    }
    else
    {
        ADC_HardwareTriggerMaskNonAuto(pADC);
    }
#endif
}

/*****************************************************************************//*!
   *
   * @brief ½ûÓÃADCÄ£¿é
   *
   * @param[in]  pADC Ö¸ÏòADCÄ£¿éÀàÐÍ
   *
   * @return none.
   *
   *****************************************************************************/
void ADC_DeInit( ADC_Type *pADC )
{
    ADC_SetChannel(pADC,ADC_CHANNEL_DISABLE);
    SIM->SCGC &= ~SIM_SCGC_ADC_MASK;
}

/*****************************************************************************//*!
   *
   * @brief ¿ªÊ¼×ª»»ºÍ¶ÁÈ¡×ª»»½á¹û
   *
   * @param[in]  pADC  Ö¸ÏòADCÄ£¿é
   * @param[in]  u8Channel ADC×ª»»Í¨µÀ
   *
   * @return ADC ×ª»»½á¹û.
   *
   *****************************************************************************/
unsigned int ADC_PollRead( ADC_Type *pADC, uint8_t u8Channel )
{
    ADC_SetChannel(pADC,u8Channel);
    while( !ADC_IsCOCOFlag(pADC) )
    {
        ;
    }
    return ADC_ReadResultReg(pADC);
}

/*****************************************************************************//*!
   *
   * @brief ×¢²á ADC »Øµ÷º¯Êý£¬Í¨¹ýÖÐ¶Ï·þÎñº¯Êýµ÷ÓÃ
   *
   * @param[in]  pADC_CallBack Ö¸ÏòADC»Øµ÷º¯ÊýµØÖ·.
   *
   * @return none.
   *
   *****************************************************************************/
void ADC_SetCallBack(ADC_CallbackType pADC_CallBack)
{
    ADC_Callback[0] = pADC_CallBack;
}

/*****************************************************************************//*!
   *
   * @brief Ñ¡ÔñADCÊäÈëÍ¨µÀ.
   *
   * @param[in]  pADC  Ö¸ÏòADCÄ£¿é.
   * @param[in]  u8Channel ADC×ª»»Í¨µÀ
   *
   * @return none
   *
   *****************************************************************************/
void ADC_SetChannel( ADC_Type *pADC, uint8_t u8Channel )
{
    uint32_t u32temp;
    u32temp = pADC->SC1;
    u32temp &= ~ADC_SC1_ADCH_MASK;
    pADC->SC1 = u32temp|ADC_SC1_ADCH(u8Channel);
}

/*****************************************************************************//*!
   *
   * @brief Ñ¡ÔñADC»ù×¼µçÑ¹.
   *
   * @param[in]  pADC    Ö¸ÏòADCÄ£¿é
   * @param[in]  u8Vref  Ñ¡ÔñADC»ù×¼µçÑ¹.
   *
   * @return none
   *
   *****************************************************************************/
void ADC_VrefSelect( ADC_Type *pADC, uint8_t u8Vref )
{
    uint32_t u32Temp;
    u32Temp = pADC->SC2;
    u32Temp &= ~ADC_SC2_REFSEL_MASK;
    pADC->SC2 = u32Temp|ADC_SC2_REFSEL(u8Vref);
}

/*****************************************************************************//*!
   *
   * @brief ÉèÖÃADCÊ±ÖÓÔ´·ÖÆµ
   *
   * @param[in]  pADC  Ö¸ÏòADCÄ£¿é.
   * @param[in]  u8Div Ñ¡Ôñ·ÖÆµÏµÊý.
   *
   * @return none
   *
   *****************************************************************************/
void ADC_SelectClockDivide( ADC_Type *pADC, uint8_t u8Div )
{
    uint32_t u32Temp;
    u32Temp = pADC->SC3;
    u32Temp &= ~ADC_SC3_ADIV_MASK;
    pADC->SC3 = u32Temp|ADC_SC3_ADIV(u8Div);
}

/*****************************************************************************//*!
   *
   * @brief ÉèÖÃADC×ª»»Ä£Ê½
   *
   * @param[in]  pADC Ö¸ÏòADCÄ£¿é
   * @param[in]  u8Mode Ñ¡ÔñADC×ª»»²ÎÊý.
   *
   * @return none
   *
   *****************************************************************************/
void ADC_SetMode( ADC_Type *pADC, uint8_t u8Mode )
{
    uint32_t u32Temp;
    u32Temp = pADC->SC3;
    u32Temp &= ~ADC_SC3_MODE_MASK;
    pADC->SC3 = u32Temp|ADC_SC3_MODE(u8Mode);
}

/*****************************************************************************//*!
   *
   * @brief  ÉèÖÃADCÊäÈëÊ±ÖÓ.
   *
   * @param[in]  pADC    Ö¸ÏòADCÄ£¿é
   * @param[in]  u8Clock Ñ¡ÔñÊäÈëÊ±ÖÓÔ´.
   *
   * @return none
   *
   *****************************************************************************/
void ADC_SelectClock( ADC_Type *pADC, uint8_t u8Clock )
{
    uint32_t u32Temp;
    u32Temp = pADC->SC3;
    u32Temp &= ~ADC_SC3_ADICLK_MASK;
    pADC->SC3 = u32Temp|ADC_SC3_ADICLK(u8Clock);
}

/*****************************************************************************//*!
   *
   * @brief ÉèÖÃFIFOÉî¶È
   *
   * @param[in]  pADC Ö¸ÏòADCÄ£¿é.
   * @param[in]  u8FifoLevel Ñ¡ÔñFIFOÉî¶È.
   *
   * @return none
   *
   *****************************************************************************/
void ADC_SetFifoLevel( ADC_Type *pADC, uint8_t u8FifoLevel )
{
    uint32_t u32Temp;
    u32Temp = pADC->SC4;
    u32Temp &= ~ADC_SC4_AFDEP_MASK;
    pADC->SC4 = u32Temp|ADC_SC4_AFDEP(u8FifoLevel);
}

/*****************************************************************************//*!
   *
   * @brief ADC ÖÐ¶Ï·þÎñº¯Êý.
   *
   * @param  none.
   *
   * @return none.
   *
   *****************************************************************************/
void ADC_Isr(void)
{
    if( ADC_Callback[0] )
    {
        ADC_Callback[0]();
    }
}
