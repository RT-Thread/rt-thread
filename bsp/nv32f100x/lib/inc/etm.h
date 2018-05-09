/******************************************************************************
* @brief header file for ETM. 
*
*******************************************************************************
*
* provide APIs for accessing ETM
******************************************************************************/
#ifndef ETM_H_
#define ETM_H_
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Includes
******************************************************************************/

/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
* ETM return status definition
*
*//*! @addtogroup ETM_returnstatus
* @{
*******************************************************************************/
#define ETM_ERR_SUCCESS         0               /*!< return ok */
#define ETM_ERR_INVALID_PARAM   1               /*!< return invalid parameter */
/*! @} End of ETM_returnstatus                                                */


/******************************************************************************
* ETM channel number definition
*
*//*! @addtogroup ETM_channelnumber
* @{
*******************************************************************************/
#define ETM_CHANNEL_CHANNEL0    0               /*!< channel 0 */
#define ETM_CHANNEL_CHANNEL1    1               /*!< channel 1 */
#define ETM_CHANNEL_CHANNEL2    2               /*!< channel 2 */
#define ETM_CHANNEL_CHANNEL3    3               /*!< channel 3 */
#define ETM_CHANNEL_CHANNEL4    4               /*!< channel 4 */
#define ETM_CHANNEL_CHANNEL5    5               /*!< channel 5 */

#define ETM_CHANNELPAIR0        0               /*!< channel pair 0:ch0 & ch1 */
#define ETM_CHANNELPAIR1        2               /*!< channel pair 1:ch2 & ch3 */
#define ETM_CHANNELPAIR2        4               /*!< channel pair 2:ch4 & ch5 */

/*! @} End of ETM_channelnumber                                               */

/******************************************************************************
* ETM pwm mode definition
*
*//*! @addtogroup ETM_pwmmode
* @{
*******************************************************************************/
#define ETM_PWMMODE_EDGEALLIGNED      1          /*!< EPWM */
#define ETM_PWMMODE_CENTERALLIGNED    2          /*!< CPWM */
#define ETM_PWMMODE_COMBINE           3          /*!< Combine PWM */
/*! @} End of ETM_pwmmode                                                     */

/******************************************************************************
* ETM init value definition
*
*//*! @addtogroup ETM_initvalue
* @{
*******************************************************************************/
#define ETM_MOD_INIT	(20000-1)                /*!< MOD inite value */
#define ETM_C0V_INIT	1000                     /*!< C0V inite value */
#define ETM_C1V_INIT	1000                     /*!< C1V inite value */
#define ETM_C2V_INIT	1000                     /*!< C2V inite value */    
#define ETM_C3V_INIT	1000                     /*!< C3V inite value */
#define ETM_C4V_INIT	1000                     /*!< C4V inite value */
#define ETM_C5V_INIT	1000                     /*!< C5V inite value */
/*! @} End of ETM_initvalue                                                   */

/******************************************************************************
* ETM combine feature definition
*
*//*! @addtogroup ETM_combinefeature
* @{
*******************************************************************************/
#define ETM_COMBINE_FAULTEN_MASK  0x40       /*!< fault enable */
#define ETM_COMBINE_SYNCEN_MASK   0x20       /*!< sync enable */
#define ETM_COMBINE_DTEN_MASK     0x10       /*!< dead ETMe insertion enable */
#define ETM_COMBINE_DECAP_MASK    0x08       /*!< dual capture status */
#define ETM_COMBINE_DECAPEN_MASK  0x04       /*!< dual capture enable */
#define ETM_COMBINE_COMP_MASK     0x02       /*!< complementary enable */
#define ETM_COMBINE_COMBINE_MASK  0x01       /*!< combine enable */
/*! @} End of ETM_combinefeature                                              */

/******************************************************************************
* ETM clock sources definition
*
*//*! @addtogroup ETM_clocksource
* @{
*******************************************************************************/
#define ETM_CLOCK_NOCLOCK             0                 /*!< No Clock */
#define ETM_CLOCK_SYSTEMCLOCK         1                 /*!< System clock/2 */
#define ETM_CLOCK_FIXEDFREQCLOCK      2                 /*!< Fixed Freq Clock */
#define ETM_CLOCK_EXTERNALCLOCK       3                 /*!< External Clock */

/* clock prescale */
#define ETM_CLOCK_PS_DIV1             0                 /*!< DIV 1 */
#define ETM_CLOCK_PS_DIV2             1                 /*!< DIV 2 */
#define ETM_CLOCK_PS_DIV4             2                 /*!< DIV 4 */
#define ETM_CLOCK_PS_DIV8             3                 /*!< DIV 8 */
#define ETM_CLOCK_PS_DIV16            4                 /*!< DIV 16 */
#define ETM_CLOCK_PS_DIV32            5                 /*!< DIV 32 */
#define ETM_CLOCK_PS_DIV64            6                 /*!< DIV 64 */
#define ETM_CLOCK_PS_DIV128           7                 /*!< DIV 128 */
/*! @} End of ETM_clocksource                                                 */

/******************************************************************************
* ETM dead ETMe clock prescale definition
*
*//*! @addtogroup ETM_deadETMeprescale
* @{
*******************************************************************************/
/*  */
#define ETM_DEADETME_DTPS_DIV1        0                 /*!< DIV 1 */
#define ETM_DEADETME_DTPS_DIV4        2                 /*!< DIV 4 */
#define ETM_DEADETME_DTPS_DIV16       3                 /*!< DIV 16 */
/*! @} End of ETM_deadETMeprescale                                            */

/******************************************************************************
* ETM output mode definition
*
*//*! @addtogroup ETM_outputmode
* @{
*******************************************************************************/
/* output mode */
#define ETM_OUTPUT_TOGGLE   1                    /*!< toggle output on match */
#define ETM_OUTPUT_CLEAR    2                    /*!< clear output on match */
#define ETM_OUTPUT_SET      3                    /*!< set output on match */
/*! @} End of ETM_outputmode                                                  */

/******************************************************************************
* ETM input capture edge definition
*
*//*! @addtogroup ETM_inputcaptureedge
* @{
*******************************************************************************/
/* mode edge select*/
#define ETM_INPUTCAPTURE_RISINGEDGE           1     /*!< rising edge */
#define ETM_INPUTCAPTURE_FALLINGEDGE          2     /*!< falling edge */
#define ETM_INPUTCAPTURE_BOTHEDGE             3     /*!< both edge */

#define ETM_INPUTCAPTURE_DUALEDGE_NOEDGE      0     /*!< none */
#define ETM_INPUTCAPTURE_DUALEDGE_RISINGEDGE  1     /*!< rising edge*/
#define ETM_INPUTCAPTURE_DUALEDGE_FALLInGEDGE 2     /*!< falling edge*/
#define ETM_INPUTCAPTURE_DUALEDGE_BOTHEDGE    3     /*!< both edge */
/*! @} End of ETM_inputcaptureedge                                            */

/******************************************************************************
* ETM dual edge capture mode definition
*
*//*! @addtogroup ETM_dualcapturemode
* @{
*******************************************************************************/
#define ETM_INPUTCAPTURE_DUALEDGE_ONESHOT     4  /*!< dual edge one shot mode*/ 
#define ETM_INPUTCAPTURE_DUALEDGE_CONTINUOUS  5  /*!< dual edge continuouse mode*/
/*! @} End of ETM_dualcapturemode                                            */

/******************************************************************************
* ETM PWM edge definition
*
*//*! @addtogroup ETM_pwmedge
* @{
*******************************************************************************/
#define ETM_PWM_HIGHTRUEPULSE        1            /*!< high true pulses */
#define ETM_PWM_LOWTRUEPULSE         2            /*!< low true pulses */
/*! @} End of ETM_pwmedge                                                     */

/******************************************************************************
* ETM sync trigger source definition
*
*//*! @addtogroup ETM_syncsource
* @{
*******************************************************************************/
#define ETM_SYNC_TRIGGER_SOFTWARE    1        /*!< Software synchronization */
#define ETM_SYNC_TRIGGER_TRIGGER2    2        /*!< Tigger2 synchronization, SIM_SOPT[ETMSYNC] */
#define ETM_SYNC_TRIGGER_TRIGGER1    3        /*!< Tigger1 synchronization, ETM0CH0 */
#define ETM_SYNC_TRIGGER_TRIGGER0    4        /*!< Tigger0 synchronization, ACMP0 */
/*! @} End of ETM_syncsource                                                  */

/******************************************************************************
* ETM SW output control definition
*
*//*! @addtogroup ETM_swoutputcontrol
* @{
*******************************************************************************/ 
#define ETM_SWOCTRL_HIGH    1                /*!< software output high */
#define ETM_SWOCTRL_LOW     0                /*!< software output low */
/*! @} End of ETM_swoutputcontrol                                             */

/******************************************************************************
* ETM  polarity definition
*
*//*! @addtogroup ETM_polarity
* @{
*******************************************************************************/
#define ETM_POLARITY_HIGHACTIVE     0        /*!< active high */
#define ETM_POLARITY_LOWACTIVE      1        /*!< active low */
/*! @} End of ETM_polarity                                                    */


/******************************************************************************
* Types
******************************************************************************/
/*! @brief ETM_CALLBACK function declaration                                  */
typedef void (*ETM_CallbackPtr)(void);
/*! @} End of ETM_callback                                                    */

/******************************************************************************
* ETM configure struct.
*
*//*! @addtogroup ETM_configsturct
* @{
*******************************************************************************/
/*!
* @brief ETM configure struct.
*
*/

typedef struct
{
  uint8_t   clk_source;       /*!< clock source */
  uint8_t   prescaler;        /*!< clock prescaler */
  uint8_t   sc;               /*!< status and control */
  uint16_t  modulo;           /*!< counter mod */
  uint16_t  cnt;              /*!< counter value */
  uint16_t  cntin;            /*!< counter inite */
  uint8_t   mode;             /*!< features mode selction */
  uint8_t   sync;             /*!< synchronization */
  uint8_t   outinit;          /*!< initial state for channels output  */
  uint8_t   outmask;          /*!< output mask */
  uint32_t  combine;          /*!< function for linked channels */
  uint16_t  deadETMe;         /*!< dead ETMe insertion control */
  uint8_t   exttrig;          /*!< external trigger */
  uint8_t   pol;              /*!< channels polarity */
  uint16_t  filter;           /*!< input filter control */
  uint8_t   fms;              /*!< fault mode status */
  uint16_t  fltctrl;          /*!< fault control */
  uint8_t   fltpol;           /*!< fault input polarity */
  uint16_t  conf;             /*!< ETM configuration */
  uint32_t  synconf;          /*!< synchronization configuration*/
  uint8_t   invctrl;          /*!< inverting control */
  uint16_t  swoctrl;          /*!< software output control */
  uint16_t  pwmload;          /*!< pwm load control */
} ETM_ConfigType, *ETM_ConfigPtr;
/*! @} End of ETM_configsturct                                                */

/******************************************************************************
* ETM channel configure struct.
*
*//*! @addtogroup ETM_chconfigsturct
* @{
*******************************************************************************/
/*!
* @brief ETM channel configure struct.
*
*/
typedef struct
{
  uint8_t         u8CnSC;                  /*!< ETM channel status and control */
  uint16_t        u16CnV;                  /*!< ETM channel value control */
  union
  {
    uint32_t      u32dw;
    struct 
    {
      uint32_t    bMode         : 3;        /*!< flexETMer mode: GPIO, INPUT_CAPTURE, OUTPUT_COMPARE, EDGE_ALIGNED_PWM, CENTER_ALIGNED_PWM,
                                             * COMBINE_PWM, DUAL_EDGE_CAPTURE 
                                             */
      uint32_t    bEdge         : 2;        /*!< edge select */
      uint32_t    bOutCmp       : 2;        /*!< toggle, clear, set */
      uint32_t    bPWMPol       : 1;        /*!< high-true pulse, low-true pulses */
      uint32_t    bDualCapMode  : 1;        /*!< dual edge capture mode: one-shot, continuous mode */
      uint32_t    bCHIE         : 1;        /*!< enable channel interrupt */
    }bits;
  }ctrl;                                    /*!< ETM channel feature control */
} ETM_ChParamsType;

/*! @} End of ETM_chconfigsturct                                              */

/******************************************************************************
* Global variables
******************************************************************************/

/*!
 * inline functions
 */
/******************************************************************************
* ETM inline functions
*
*//*! @addtogroup ETM_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
*
* @brief  enable the over flow interrupt.
*        
* @param[in]    pETM          pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_DisableOverflowInt.
*
*****************************************************************************/
__STATIC_INLINE void ETM_EnableOverflowInt(ETM_Type *pETM)
{
    if(pETM->SC & ETM_SC_TOF_MASK)
    {
        pETM->SC &= ~ETM_SC_TOF_MASK;
    }
    pETM->SC |= ETM_SC_TOIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable the over flow interrupt.
*        
* @param[in]    pETM          pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see ETM_EnableOverflowInt.
*
*****************************************************************************/
__STATIC_INLINE void ETM_DisableOverflowInt(ETM_Type *pETM)
{
    pETM->SC &= ~ETM_SC_TOIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  enable the channel interrupt.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
* @param[in]    u8ETM_Channel  channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_DisableChannelInt.
*
*****************************************************************************/
__STATIC_INLINE void ETM_EnableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->CONTROLS[u8ETM_Channel].CnSC |= ETM_CnSC_CHIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable the channel interrupt.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
* @param[in]    u8ETM_Channel  channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_EnableChannelInt.
*
*****************************************************************************/
__STATIC_INLINE void ETM_DisableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->CONTROLS[u8ETM_Channel].CnSC &= ~ETM_CnSC_CHIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  get the over flow flag.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
*    
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_ClrOverFlowFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t ETM_GetOverFlowFlag(ETM_Type *pETM)
{
    return (pETM->SC & ETM_SC_TOF_MASK);
}

/*****************************************************************************//*!
*
* @brief  clear the over flow flag.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
*    
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_GetOverFlowFlag.
*
*****************************************************************************/
__STATIC_INLINE void ETM_ClrOverFlowFlag(ETM_Type *pETM)
{
    if(pETM->SC & ETM_SC_TOF_MASK)
    {
         pETM->SC &= ~ETM_SC_TOF_MASK;
    }
}

/*****************************************************************************//*!
*
* @brief  get the channel flag.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
* @param[in]    u8ETM_Channel  channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_ClrChannelFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t ETM_GetChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    return (pETM->CONTROLS[u8ETM_Channel].CnSC & ETM_CnSC_CHF_MASK);
}

/*****************************************************************************//*!
*
* @brief  clear the channel flag.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
*    
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_GetChannelFlag.
*
*****************************************************************************/
__STATIC_INLINE void ETM_ClrChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->CONTROLS[u8ETM_Channel].CnSC &= ~ETM_CnSC_CHF_MASK;
}

/*********************************************************************************//*!
*
* @brief enable the write protection function.Write protected bits cannot be written. 
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_WriteProtectionDisable.
*
*********************************************************************************/
__STATIC_INLINE void ETM_WriteProtectionEnable(ETM_Type *pETM)
{
    pETM->FMS |= ETM_FMS_WPEN_MASK;
}

/*********************************************************************************//*!
*
* @brief disable the write protection function.Write protected bits can be written. 
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_WriteProtectionDisable.
*
*********************************************************************************/
__STATIC_INLINE void ETM_WriteProtectionDisable(ETM_Type *pETM)
{
    if (pETM->FMS & ETM_FMS_WPEN_MASK)
    {
        pETM->MODE |= ETM_MODE_WPDIS_MASK;
    }
}

/*****************************************************************************//*!
*
* @brief  set ETMEN bit to enable ETM-specific register.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
*    
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetETMBasic.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetETMEnhanced(ETM_Type *pETM)
{
    if(pETM->MODE & ETM_MODE_WPDIS_MASK)   /* if not write protected */
    {
        pETM->MODE |= ETM_MODE_ETMEN_MASK;
    }
    else
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->MODE |= ETM_MODE_ETMEN_MASK;
        ETM_WriteProtectionEnable(pETM);
    }    
}

/*****************************************************************************//*!
*
* @brief  clear ETMEN bit to disable ETM-specific registers, only TPM-compatible
*         registers can be used.
*        
* @param[in]    pETM           pointer to one of three ETM base register address.
*    
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetETMEnhanced.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetETMBasic(ETM_Type *pETM)
{
    if(pETM->MODE & ETM_MODE_WPDIS_MASK)    /* if not write protected */
    {
        pETM->MODE &= ~ETM_MODE_ETMEN_MASK;
    }
    else
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->MODE &= ~ETM_MODE_ETMEN_MASK;
        ETM_WriteProtectionEnable(pETM);
    }  
}

/*****************************************************************************//*!
*
* @brief  set the ETM mod value.
*              
* @param[in]    pETM           pointer to one of three ETM base register address.
* @param[in]    u16ModValue    the mod value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetChannelValue.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetModValue(ETM_Type *pETM, uint16_t u16ModValue)
{
    pETM->CNT = 0;
    pETM->MOD = u16ModValue;
    if(ETM2 == pETM)
    {
        if(pETM->MODE & ETM_MODE_ETMEN_MASK)
        {
            pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;
        }
        else
        {
        }
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  set the ETM channel value.
*                
* @param[in]    pETM             pointer to one of three ETM base register address.
* @param[in]    u16ChannelValue  the CnV value required to set.
* @param[in]    u8ETM_Channel    ETM channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetModValue.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetChannelValue(ETM_Type *pETM, uint8_t u8ETM_Channel, uint16_t u16ChannelValue)
{
    pETM->CONTROLS[u8ETM_Channel].CnV = u16ChannelValue;
    if(ETM2 == pETM)
    {
        if(pETM->MODE & ETM_MODE_ETMEN_MASK)
        {
            if(u8ETM_Channel < 2)
            {
                pETM->COMBINE |= ETM_COMBINE_SYNCEN0_MASK;  /* enable the sync function */
            }
            else if (u8ETM_Channel < 4)
            {
                pETM->COMBINE |= ETM_COMBINE_SYNCEN1_MASK;
            }
            else
            {
                pETM->COMBINE |= ETM_COMBINE_SYNCEN2_MASK;
            }
            pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;  
        }
        else
        {
        }
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  set the ETM channel value.
*               
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u16CounterValue   the CNTIN value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see ETM_SetModValue.
*
*****************************************************************************/
__STATIC_INLINE void ETM_SetCounterInitValue(ETM_Type *pETM, uint16_t u16CounterValue)
{
    pETM->CNTIN = u16CounterValue;
    if(pETM->MODE & ETM_MODE_ETMEN_MASK)
    {
        pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  set the channel output mask value, ETM2 used only.
*               
* @param[in]    pETM            pointer to one of three ETM base register address.
* @param[in]    u16ChMask       the CNTIN value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see ETM_UnMaskChannels.
*
*****************************************************************************/
__STATIC_INLINE void ETM_MaskChannels(ETM_Type *pETM, uint16_t u16ChMask)
{
     pETM->OUTMASK |= u16ChMask;
}

/*****************************************************************************//*!
*
* @brief  clear the channel output mask value, ETM2 used only.
*               
* @param[in]    pETM            pointer to one of three ETM base register address.
* @param[in]    u16ChMask       the CNTIN value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see ETM_MaskChannels.
*
*****************************************************************************/
__STATIC_INLINE void ETM_UnMaskChannels(ETM_Type *pETM, uint16_t u16ChMask)
{
     pETM->OUTMASK &= ~u16ChMask;
}

/*********************************************************************************//*!
*
* @brief set ETM channels polarity.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
* @param[in]    u8ChsPolValue         the channels value need to be set.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_GetChannelsPolarity.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetChannelsPolarity(ETM_Type *pETM, uint8_t u8ChsPolValue)
{
    pETM->POL = u8ChsPolValue;
}

/*********************************************************************************//*!
*
* @brief get ETM channels polarity.
*        
* @param[in]    pETM                  pointer to one of three ETM base register address.
*
* @return uint8_t the channels polarity.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetChannelsPolarity.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetChannelsPolarity(ETM_Type *pETM)
{
    return (pETM->POL);
}

/*********************************************************************************//*!
*
* @brief select the enhanced SYNC mode.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_DisableEnhancedSYNCMode.
*
*********************************************************************************/
__STATIC_INLINE void ETM_EnableEnhancedSYNCMode(ETM_Type *pETM)
{
    pETM->SYNCONF   |= ETM_SYNCONF_SYNCMODE_MASK;   /* recommend enhanced sync mode */
}

/*********************************************************************************//*!
*
* @brief select the legacy SYNC mode.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_EnableEnhancedSYNCMode.
*
*********************************************************************************/
__STATIC_INLINE void ETM_DisableEnhancedSYNCMode(ETM_Type *pETM)
{
    pETM->SYNCONF   &= ~ETM_SYNCONF_SYNCMODE_MASK;   /* recommend enhanced sync mode */
}

/*********************************************************************************//*!
*
* @brief set the external trigger source.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8TirggerSource   initial trigger or CHn(0~5)trigger
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_GetExternalTriggerFlag.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetExternalTrigger(ETM_Type *pETM, uint8_t u8TirggerSource)
{
    pETM->EXTTRIG   = u8TirggerSource;
}

/*********************************************************************************//*!
*
* @brief get the external trigger flag.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return ex trigger flag.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetExternalTrigger.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetExternalTriggerFlag(ETM_Type *pETM)
{
    return (pETM->EXTTRIG & ETM_EXTTRIG_TRIGF_MASK);
}

/*********************************************************************************//*!
*
* @brief set LDOK bit.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetLoadMatchChannel.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetLoadEnable(ETM_Type *pETM)
{
    pETM->PWMLOAD |= ETM_PWMLOAD_LDOK_MASK;
}

/*********************************************************************************//*!
*
* @brief set the channel in the matching process.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8Matchchannel    the channel in the matching process.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_SetLoadEnable.
*
*********************************************************************************/
__STATIC_INLINE void ETM_SetLoadMatchChannel(ETM_Type *pETM, uint8_t u8Matchchannel)
{
    pETM->PWMLOAD |= u8Matchchannel;
}

/*********************************************************************************//*!
*
* @brief disable the channel input capture filter.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8ETM_Channel     the channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_InputCaptureFilterSet.
*
*********************************************************************************/
__STATIC_INLINE void ETM_InputCaptureFilterClr(ETM_Type *pETM, uint8_t u8ETM_Channel)
{
    pETM->FILTER &= ~(0x000F << (u8ETM_Channel << 2));
}

/*********************************************************************************//*!
*
* @brief set the channel input capture filter value.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8ETM_Channel     the channel number: 0~3.
* @param[in]    u8FilterValue     fliter cycles:1~15, 0: disable channel filter.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_InputCaptureFilterClr.
*
*********************************************************************************/
__STATIC_INLINE void ETM_InputCaptureFilterSet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8FilterValue)
{
    if (u8FilterValue)
    {
        pETM->FILTER |= (u8FilterValue << (u8ETM_Channel << 2));
    }
    else
    {
        ETM_InputCaptureFilterClr(pETM, u8ETM_Channel);
    }
}


/*********************************************************************************//*!
*
* @brief enable the fault input pin.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_FaultPinDisable.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinEnable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) /* if not protected */
    {
        pETM->FLTCTRL |= (1 << u8FaultPin);
    }
    else                                  /* if protected */ 
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL |= (1 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief disable the fault input pin.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_FaultPinEnable.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinDisable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) /* if not protected */
    {
        pETM->FLTCTRL &= ~(1 << u8FaultPin);
    }
    else                                  /* if protected */ 
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL &= ~(1 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief enable the fault pin filter.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_FaultPinFilterDisable.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterEnable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) /* if not protected */
    {
        pETM->FLTCTRL |= (0x10 << u8FaultPin);
    }
    else                                  /* if protected */ 
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL |= (0x10 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief disable the fault pin filter.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_FaultPinFilterDisable.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterDisable(ETM_Type *pETM, uint8_t u8FaultPin)
{
    if (pETM->MODE & ETM_MODE_WPDIS_MASK) /* if not protected */
    {
        pETM->FLTCTRL &= ~(0x10 << u8FaultPin);
    }
    else                                  /* if protected */ 
    {
        ETM_WriteProtectionDisable(pETM);
        pETM->FLTCTRL &= ~(0x10 << u8FaultPin);
        ETM_WriteProtectionEnable(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief disable all the fault pins filter together. 
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_FaultPinFilterSet.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterCDisableAll(ETM_Type *pETM)
{
    pETM->FLTCTRL &= ~ETM_FLTCTRL_FFVAL_MASK;
}

/*********************************************************************************//*!
*
* @brief set the fault filter value. All channels share the same filter value.
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8FilterValue     the fault input filter value: 1~15, 0 disable the filter.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_FaultPinFilterCDisableAll.
*
*********************************************************************************/
__STATIC_INLINE void ETM_FaultPinFilterSet(ETM_Type *pETM, uint8_t u8FilterValue)
{
    if (u8FilterValue)
    {
        pETM->FLTCTRL |= ETM_FLTCTRL_FFVAL(u8FilterValue);
    }
    else
    {
        ETM_FaultPinFilterCDisableAll(pETM);
    }
}

/*********************************************************************************//*!
*
* @brief get the logic OR of all the fault detection flags
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_GetFaultDetectionFlag.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetFaultDetectionLogicORFlag(ETM_Type *pETM)
{
    return (pETM->FMS & ETM_FMS_FAULTF_MASK);
}

/*********************************************************************************//*!
*
* @brief get the fault detection flag
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
* @param[in]    u8FaultPin        fault input pin number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see ETM_GetFaultDetectionLogicORFlag.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetFaultDetectionFlag(ETM_Type *pETM, uint8_t u8FaultPin)
{
    return (pETM->FMS & (1 << u8FaultPin));
}

/*********************************************************************************//*!
*
* @brief get the logic OR value of the fault inputs
*        
* @param[in]    pETM              pointer to one of three ETM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
__STATIC_INLINE uint8_t ETM_GetFaultInputsLogicORValue(ETM_Type *pETM)
{
    return (pETM->FMS & ETM_FMS_FAULTIN_MASK);
}

/*! @} End of ETM_api_list                                                    */

/******************************************************************************
* Global functions
******************************************************************************/

void ETM_ClockSet(ETM_Type *pETM, uint8_t u8ClockSource, uint8_t u8ClockPrescale);
void ETM_PWMInit(ETM_Type *pETM, uint8_t u8PWMModeSelect, uint8_t u8PWMEdgeSelect);
void ETM_InputCaptureInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CaptureMode);
void ETM_DualEdgeCaptureInit(ETM_Type *pETM, uint8_t u8ChannelPair, uint8_t u8CaptureMode, 
                             uint8_t u8Channel_N_Edge, uint8_t u8Channel_Np1_Edge);
void ETM_OutputCompareInit(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8CompareMode);
void ETM_SoftwareSync(ETM_Type *pETM);
void ETM_HardwareSync(ETM_Type *pETM, uint8_t u8TriggerN);
void ETM_HardwareSyncCombine(ETM_Type *pETM, uint8_t u8TriggerMask);
void ETM_GenerateTrig2(ETM_Type *pETM);
void ETM_PWMDeadETMeSet(ETM_Type *pETM, uint8_t u8PrescalerValue, uint8_t u8DeadETMeValue);
void ETM_OutputMaskSet(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_SWOutputControlSet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8ChannelValue);
void ETM_SetDebugModeBehavior(ETM_Type *pETM, uint8_t u8DebugMode);
void ETM_SetTOFFrequency(ETM_Type *pETM, uint8_t u8TOFNUM);
void ETM_PolaritySet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8ActiveValue);
void ETM_InvertChannel(ETM_Type *pETM, uint8_t u8ChannelPair);
void ETM_Init(ETM_Type *pETM, ETM_ConfigType *pConfig);
void ETM_DeInit(ETM_Type *pETM);
void ETM_ChannelInit(ETM_Type *pETM, uint8_t u8ETM_Channel, ETM_ChParamsType *pETM_ChParams);
void ETM_SetDutyCycleCombine(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8DutyCycle);
void ETM_SetCallback(ETM_Type *pETM, ETM_CallbackPtr pfnCallback);
void  ETM_SyncConfigActivate(ETM_Type *pETM, uint32_t u32ConfigValue);
void ETM_SyncConfigDeactivate(ETM_Type * pETM, uint32_t u32ConfigValue);
uint8_t ETM_GetFaultDetectionLogicORFlag(ETM_Type *pETM);
uint8_t ETM_GetFaultDetectionFlag(ETM_Type *pETM, uint8_t u8FaultPin);
uint8_t ETM_GetFaultInputsLogicORValue(ETM_Type *pETM);
void ETM_WriteProtectionEnable(ETM_Type *pETM);
void ETM_WriteProtectionDisable(ETM_Type *pETM);
void ETM_FaultPinFilterCDisableAll(ETM_Type *pETM);
void ETM_FaultPinFilterSet(ETM_Type *pETM, uint8_t u8FilterValue);
void ETM_FaultPinFilterDisable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_FaultPinFilterEnable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_FaultPinEnable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_FaultPinDisable(ETM_Type *pETM, uint8_t u8FaultPin);
void ETM_InputCaptureFilterClr(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_InputCaptureFilterSet(ETM_Type *pETM, uint8_t u8ETM_Channel, uint8_t u8FilterValue);
void ETM_SetLoadMatchChannel(ETM_Type *pETM, uint8_t u8Matchchannel);
void ETM_SetLoadEnable(ETM_Type *pETM);
uint8_t ETM_GetExternalTriggerFlag(ETM_Type *pETM);
void ETM_DisableEnhancedSYNCMode(ETM_Type *pETM);
void ETM_EnableEnhancedSYNCMode(ETM_Type *pETM);
uint8_t ETM_GetChannelsPolarity(ETM_Type *pETM);
void ETM_SetChannelsPolarity(ETM_Type *pETM, uint8_t u8ChsPolValue);
void ETM_UnMaskChannels(ETM_Type *pETM, uint16_t u16ChMask);
void ETM_MaskChannels(ETM_Type *pETM, uint16_t u16ChMask);
void ETM_SetCounterInitValue(ETM_Type *pETM, uint16_t u16CounterValue);
void ETM_SetChannelValue(ETM_Type *pETM, uint8_t u8ETM_Channel, uint16_t u16ChannelValue);
void ETM_SetModValue(ETM_Type *pETM, uint16_t u16ModValue);
void ETM_SetETMBasic(ETM_Type *pETM);
void ETM_SetETMEnhanced(ETM_Type *pETM);
void ETM_ClrChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel);
uint8_t ETM_GetChannelFlag(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_ClrOverFlowFlag(ETM_Type *pETM);
uint8_t ETM_GetOverFlowFlag(ETM_Type *pETM);
void ETM_DisableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_EnableChannelInt(ETM_Type *pETM, uint8_t u8ETM_Channel);
void ETM_DisableOverflowInt(ETM_Type *pETM);
void ETM_EnableOverflowInt(ETM_Type *pETM);

#ifdef __cplusplus
}
#endif
#endif /* ETM_H_ */
