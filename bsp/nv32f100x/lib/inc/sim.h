/******************************************************************************
*
* @brief header file for SIM utilities. 
*
*******************************************************************************
*
* provide APIs for accessing SIM
******************************************************************************/

#ifndef SIM_H_
#define SIM_H_

/******************************************************************************
* Includes
******************************************************************************/

/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* define SIM device ID types
*
*//*! @addtogroup sim_id_types
* @{
*******************************************************************************/

typedef enum {
    ID_TYPE_FAMID,                  /*!< device Family ID */
    ID_TYPE_SUBFAMID,               /*!< device Subfamily ID */ 
    ID_TYPE_REVID,                  /*!< device Revision ID */
    ID_TYPE_PINID                   /*!< device Pin ID (Pin count) */
} IDType;
/*! @} End of sim_id_types                                                    					*/

/******************************************************************************
* Macros
******************************************************************************/ 

/******************************************************************************
* Types
******************************************************************************/
    
/* SIM configuration structure 
 */ 
 
/******************************************************************************
* define SIM configuration structure
*
*//*! @addtogroup sim_config_type
* @{
*******************************************************************************/

/*!
 * @brief SIM configuration structure.
 *
 */
#if defined(CPU_NV32)
typedef struct{
    struct{
        uint32_t bEnableCLKOUT  : 1;        /*!< 1: enable , 0: disable */
        uint32_t bTXDME         : 1;        /*!< 1: enable TXDME, 0: disable */
        uint32_t bETMSYNC       : 1;        /*!< 1: enable ETM SYNC, 0: no sync */
        uint32_t bRXDFE         : 1;        /*!< 1: enable RXD filter, 0: no filter */
        uint32_t bRXDCE         : 1;        /*!< 1: enable RXD capture, 0: no capture */
        uint32_t bACIC          : 1;        /*!< 1: ACMP0 to ETM1 channel0 connection, 0: no connection */
        uint32_t bRTCC          : 1;        /*!< 1: RTC overflow connected to ETM1 channel1, 0: no connection */
        uint32_t u8ADHWT        : 2;        /*!< ADC h/w trigger source selection */
        uint32_t bDisableSWD    : 1;        /*!< 1: disable SWD, 0: enable */
        uint32_t bDisableRESET  : 1;        /*!< 1: disable RESET pin, 0: enable */
        uint32_t bDisableNMI    : 1;        /*!< 1: disable NMI pin, 0: enable */
        uint32_t bBusDiv        : 1;        /*!< bus divider BUSDIV value */
    } sBits;
    uint8_t     u8Delay;                /*!< delay value */
    uint8_t     u8BusRef;               /*!< bus reference */
    uint32_t    u32PinSel;              /*!< pin select reg value */
    uint32_t    u32SCGC;                /*!< clock gating value register */   
} SIM_ConfigType, *SIM_ConfigPtr; /*!< sim configuration structure type */
#elif defined(CPU_NV32M3)
typedef struct{
    struct{
        uint32_t bEnableCLKOUT  : 1;        /*!< 1: enable , 0: disable */
        uint32_t bTXDME         : 1;        /*!< 1: enable TXDME, 0: disable */
        uint32_t bETMSYNC       : 1;        /*!< 1: enable ETM SYNC, 0: no sync */
        uint32_t bRXDCE         : 1;        /*!< 1: enable RXD capture, 0: no capture */
        uint32_t bRXDFE         : 2;        /*!< 1: enable RXD filter, 0: no filter */
        uint32_t u8ADHWT        : 3;        /*!< ADC h/w trigger source selection */
        uint32_t bETMIC         : 2;        /*!< ETM0CH0 input capture source selection */
        uint32_t bACTRG         : 1;        /*!< ACMP Trigger ETM2 selection*/
        uint32_t bDisableSWD    : 1;        /*!< 1: disable SWD, 0: enable */
        uint32_t bDisableRESET  : 1;        /*!< 1: disable RESET pin, 0: enable */
        uint32_t bDisableNMI    : 1;        /*!< 1: disable NMI pin, 0: enable */
    } sBits;
    uint8_t     u8Delay;                /*!< delay value */
    uint8_t     u8BusRef;               /*!< bus reference */
    uint32_t    u32PinSel;              /*!< pin select reg value */
    uint32_t    u32SCGC;                /*!< clock gating value register */ 
    uint32_t    u32CLKDIV;              /*!< clock divider CLKDIV value */   
} SIM_ConfigType, *SIM_ConfigPtr; /*!< sim configuration structure type */
#elif defined(CPU_NV32M4)
typedef struct{
    struct{
        uint32_t bEnableCLKOUT  : 1;        /*!< 1: enable , 0: disable */
        uint32_t bTXDME         : 1;        /*!< 1: enable TXDME, 0: disable */
        uint32_t bETMSYNC       : 1;        /*!< 1: enable ETM SYNC, 0: no sync */
        uint32_t bRXDCE         : 1;        /*!< 1: enable RXD capture, 0: no capture */
        uint32_t bRXDFE         : 2;        /*!< 1: enable RXD filter, 0: no filter */
        uint32_t u8ADHWT        : 3;        /*!< ADC h/w trigger source selection */
        uint32_t bACTRG         : 1;        /*!< ACMP Trigger ETM2 selection*/
        uint32_t bDisableSWD    : 1;        /*!< 1: disable SWD, 0: enable */
        uint32_t bDisableRESET  : 1;        /*!< 1: disable RESET pin, 0: enable */
        uint32_t bDisableNMI    : 1;        /*!< 1: disable NMI pin, 0: enable */
    } sBits;
    uint8_t     u8Delay;                /*!< delay value */
    uint8_t     u8BusRef;               /*!< bus reference */
    uint32_t    u32PinSel;              /*!< pin select reg value */
    uint32_t    u32SCGC;                /*!< clock gating value register */ 
    uint32_t    u32CLKDIV;              /*!< clock divider CLKDIV value */   
} SIM_ConfigType, *SIM_ConfigPtr; /*!< sim configuration structure type */
#endif
/*! @} End of sim_config_type                                                    					*/
  
/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/
/******************************************************************************
* define SIM API list
*
*//*! @addtogroup sim_api_list
* @{
*******************************************************************************/
#if defined(CPU_NV32)
/*****************************************************************************//*!
*
* @brief delay ETM2 triggering ADC for u8Delay bus clock output divide. 
*        
* @param[in]   u8Delay     delay value of Bus clock output divide.
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DelayETM2Trig2ADC(uint8_t u8Delay)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_DELAY_MASK)) | SIM_SOPT_DELAY(u8Delay);    
}
/*****************************************************************************//*!
*
* @brief enable clock output.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see  SIM_DisableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_EnableClockOutput(void)
{
    SIM->SOPT |= (SIM_SOPT_CLKOE_MASK);    
}

/*****************************************************************************//*!
*
* @brief disable clock output.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see  SIM_EnableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_DisableClockOutput(void)
{
    SIM->SOPT &= ~(SIM_SOPT_CLKOE_MASK);    
}
/*****************************************************************************//*!
*
* @brief set bus clock output divide. 
*        
* @param[in]  u8Divide     divide (3-bits)
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClockOutputDivide(uint8_t u8Divide)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_BUSREF_MASK)) | SIM_SOPT_BUSREF(u8Divide & 0x07);    
}
/*****************************************************************************//*!
*
* @brief enable UART0 RXD connect with UART0 module  and ETM0 channel 1.. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0RXDConnectETMOCH1(void)
{
    SIM->SOPT |= (SIM_SOPT_RXDCE_MASK);    
}
/*****************************************************************************//*!
*
* @brief enable UART0 TX modulation. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Modulation(void)
{
    SIM->SOPT |= (SIM_SOPT_TXDME_MASK);    
}

/*****************************************************************************//*!
*
* @brief disable UART0 TX modulation. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DisableUART0Modulation(void)
{
    SIM->SOPT &= ~(SIM_SOPT_TXDME_MASK);    
}
/*****************************************************************************//*!
*
* @brief generate a softare sync trigger to ETM2 module (trigger).
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_GenerateSoftwareTrig2ETM2(void)
{
    SIM->SOPT |= (SIM_SOPT_ETMSYNC_MASK);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH3 pin from default to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH3Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS3_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap ETM2CH2 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH2Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS2_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH1 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH1Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap SPI0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapSPI0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_SPI0PS_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap I2C pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapI2CPin(void)
{
    SIM->PINSEL |= SIM_PINSEL_IICPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief enable UART0 RX filter. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Filter(void)
{
    SIM->SOPT |= (SIM_SOPT_RXDFE_MASK);    
}
/******************************************************************************!

* @function name: SIM_DisableUART0Filter
*
* @brief disable UART0 RX filter. 
*        
* @param         
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DisableUART0Filter(void)
{
    SIM->SOPT &= ~(SIM_SOPT_RXDFE_MASK);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to RTC overflow. 
*        
* @param  none        
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByRTC(void)
{
    SIM->SOPT &= ~(SIM_SOPT_ADHWT_MASK);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to PIT . 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPIT(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(1);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ETM2 init trigger with 8-bit programmable delay. 
*        
* @param  none      
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Init(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(2);    
}

/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ETM2 match trigger with 8-bit programmable delay. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Match(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(3);    
}
/*****************************************************************************//*!
*
* @brief enable RTC capture to ETM1 input channel1. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableRTCCapture(void)
{
    SIM->SOPT |= (SIM_SOPT_RTCC_MASK);    
}
/*****************************************************************************//*!
*
* @brief disable RTC capture to ETM1 input channel1. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DisableRTCCapture(void)
{
    SIM->SOPT &= ~(SIM_SOPT_RTCC_MASK);    
}
/*****************************************************************************//*!
*
* @brief enable ACMP0 input capture to ETM1 input channel0. 
*        
* @param  none      
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableACMP0InputCapture(void)
{
    SIM->SOPT |= (SIM_SOPT_ACIC_MASK);    
}
/*****************************************************************************//*!
*
* @brief disable ACMP0 input capture to ETM1 input channel0. 
*        
* @param  none      
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DisableACMP0InputCapture(void)
{
    SIM->SOPT &= ~(SIM_SOPT_ACIC_MASK);    
}
/*****************************************************************************//*!
*
* @brief remap RTC pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapRTCPin(void)
{
    SIM->PINSEL |= SIM_PINSEL_RTCPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief set bus divide BUSDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetBusDivide(uint8_t u8Divide)
{
    SIM->BUSDIV = u8Divide;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH1 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH1Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS1_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap ETM2CH0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS0_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap ETM1CH1 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH1Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM1PS1_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap ETM1CH0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM1PS0_MASK;    
}
#elif defined(CPU_NV32M3)
/*****************************************************************************//*!
*
* @brief delay ETM2 triggering ADC for u8Delay bus clock output divide. 
*        
* @param[in]   u8Delay     delay value of Bus clock output divide.
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DelayETM2Trig2ADC(uint8_t u8Delay)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_DELAY_MASK)) | SIM_SOPT_DELAY(u8Delay);    
}
/*****************************************************************************//*!
*
* @brief enable clock output.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see  SIM_DisableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_EnableClockOutput(void)
{
    SIM->SOPT |= (SIM_SOPT_CLKOE_MASK);    
}

/*****************************************************************************//*!
*
* @brief disable clock output.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see  SIM_EnableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_DisableClockOutput(void)
{
    SIM->SOPT &= ~(SIM_SOPT_CLKOE_MASK);    
}
/*****************************************************************************//*!
*
* @brief set bus clock output divide. 
*        
* @param[in]  u8Divide     divide (3-bits)
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClockOutputDivide(uint8_t u8Divide)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_BUSREF_MASK)) | SIM_SOPT_BUSREF(u8Divide & 0x07);    
}
/*****************************************************************************//*!
*
* @brief enable UART0 RXD connect with UART0 module  and ETM0 channel 1.. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0RXDConnectETMOCH1(void)
{
    SIM->SOPT |= (SIM_SOPT_RXDCE_MASK);    
}
/*****************************************************************************//*!
*
* @brief enable UART0 TX modulation. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Modulation(void)
{
    SIM->SOPT |= (SIM_SOPT_TXDME_MASK);    
}

/*****************************************************************************//*!
*
* @brief disable UART0 TX modulation. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DisableUART0Modulation(void)
{
    SIM->SOPT &= ~(SIM_SOPT_TXDME_MASK);    
}
/*****************************************************************************//*!
*
* @brief generate a softare sync trigger to ETM2 module (trigger).
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_GenerateSoftwareTrig2ETM2(void)
{
    SIM->SOPT |= (SIM_SOPT_ETMSYNC_MASK);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH3 pin from default to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH3Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS3_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap ETM2CH2 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH2Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2PS2_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH1 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH1Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap SPI0 pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapSPI0Pin(void)
{
    SIM->PINSEL |= SIM_PINSEL_SPI0PS_MASK;    
}

/*****************************************************************************//*!
*
* @brief remap I2C pin from default  to the other. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapI2CPin(void)
{
    SIM->PINSEL |= SIM_PINSEL_IICPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief UART0 RXD input signal is connected to UART0 module directly. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Filter(void)
{
    SIM->SOPT &= ~(SIM_SOPT_RXDFE_MASK);   
}
/*****************************************************************************//*!
*
* @brief UART0 RXD input signal is filtered by ACMP0, then injected to UART0. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0FilterByACMP0(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_RXDFE_MASK)) | SIM_SOPT_RXDFE(1);  
}
/*****************************************************************************//*!
*
* @brief UART0 RXD input signal is filtered by ACMP1, then injected to UART0. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0FilterByACMP1(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_RXDFE_MASK)) | SIM_SOPT_RXDFE(2);  
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to RTC overflow. 
*        
* @param  none        
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByRTC(void)
{
    SIM->SOPT &= ~(SIM_SOPT_ADHWT_MASK);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ETM0 init trigger . 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPIT(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(1);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ETM2 init trigger with 8-bit programmable delay. 
*        
* @param  none      
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Init(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(2);    
}

/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ETM2 match trigger with 8-bit programmable delay. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Match(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(3);    
}

/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to PIT channel0 overflow. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPITCH0Overflow(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(4);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to PIT channel1 overflow. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPITChannel1Overflow(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(5);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ACMP0 out. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByACMP0Out(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(6);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ACMP1 out. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByACMP1Out(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ADHWT_MASK)) | SIM_SOPT_ADHWT(7);    
}
/*****************************************************************************//*!
*
* @brief Select ETM0CH0 as ETM0CH0 Input Capture Source. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelETM0CH0AsETM0CH0ICS(void)
{
    SIM->SOPT &= ~(SIM_SOPT_ETMIC_MASK);   
}
/*****************************************************************************//*!
*
* @brief Select ACMP0 OUT as ETM0CH0 Input Capture Source. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelACMP0AsETM0CH0ICS(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ETMIC_MASK)) | SIM_SOPT_ETMIC(1);  
}
/*****************************************************************************//*!
*
* @brief Select ACMP1 OUT as ETM0CH0 Input Capture Source. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelACMP1AsETM0CH0ICS(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ETMIC_MASK)) | SIM_SOPT_ETMIC(2);  
}
/*****************************************************************************//*!
*
* @brief Select RTC overflow as ETM0CH0 Input Capture Source. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelRTCOverflowAsETM0CH0ICS(void)
{
    SIM->SOPT = (SIM->SOPT & ~(SIM_SOPT_ETMIC_MASK)) | SIM_SOPT_ETMIC(3);  
}
/*****************************************************************************//*!
*
* @brief Select ACMP0 output as the trigger0 input of ETM2. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelACMP0AsETM2Trigger0(void)
{
    SIM->SOPT &= ~(SIM_SOPT_ACTRG_MASK);  
}
/*****************************************************************************//*!
*
* @brief Select ACMP1 output as the trigger0 input of ETM2. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelACMP1AsETM2Trigger0(void)
{
    SIM->SOPT |= (SIM_SOPT_ACTRG_MASK);  
}
/*****************************************************************************//*!
*
* @brief set clock3 divide CLKDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClock3Divide(void)
{
    SIM->CLKDIV |= SIM_CLKDIV_OUTDIV3_MASK;    
}
/*****************************************************************************//*!
*
* @brief set clock2 divide CLKDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClock2Divide(void)
{
    SIM->CLKDIV |= SIM_CLKDIV_OUTDIV2_MASK;    
}
/*****************************************************************************//*!
*
* @brief set clock1 divide CLKDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClock1Divide(uint8_t u8divide)
{
    SIM->CLKDIV |= SIM_CLKDIV_OUTDIV1(u8divide);    
}
/*****************************************************************************//*!
*
* @brief select TCLK2 for PWT module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK2ForPWT(void)
{
    SIM->PINSEL |= SIM_PINSEL_PWTCLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK1 for PWT module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK1ForPWT(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_PWTCLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK2 for ETM2 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK2ForETM2(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM2CLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK1 for ETM2 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK1ForETM2(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM2CLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK2 for ETM0 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK2ForETM0(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0CLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK1 for ETM0 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK1ForETM0(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM0CLKPS_MASK;    
}
#elif defined(CPU_NV32M4)
/*****************************************************************************//*!
*
* @brief delay ETM2 triggering ADC for u8Delay bus clock output divide. 
*        
* @param[in]   u8Delay     delay value of Bus clock output divide.
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DelayETM2Trig2ADC(uint8_t u8Delay)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_DELAY_MASK)) | SIM_SOPT0_DELAY(u8Delay);    
}
/*****************************************************************************//*!
*
* @brief enable clock output.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see  SIM_DisableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_EnableClockOutput(void)
{
    SIM->SOPT0 |= (SIM_SOPT0_CLKOE_MASK);    
}

/*****************************************************************************//*!
*
* @brief disable clock output.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see  SIM_EnableClockOutput
*****************************************************************************/
__STATIC_INLINE void SIM_DisableClockOutput(void)
{
    SIM->SOPT0 &= ~(SIM_SOPT0_CLKOE_MASK);    
}
/*****************************************************************************//*!
*
* @brief set bus clock output divide. 
*        
* @param[in]  u8Divide     divide (3-bits)
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClockOutputDivide(uint8_t u8Divide)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_BUSREF_MASK)) | SIM_SOPT0_BUSREF(u8Divide & 0x07);    
}
/*****************************************************************************//*!
*
* @brief enable UART0 RXD connect with UART0 module  and ETM0 channel 1.. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0RXDConnectETMOCH1(void)
{
    SIM->SOPT0 |= (SIM_SOPT0_RXDCE_MASK);    
}
/*****************************************************************************//*!
*
* @brief enable UART0 TX modulation. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Modulation(void)
{
    SIM->SOPT0 |= (SIM_SOPT0_TXDME_MASK);    
}

/*****************************************************************************//*!
*
* @brief disable UART0 TX modulation. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DisableUART0Modulation(void)
{
    SIM->SOPT0 &= ~(SIM_SOPT0_TXDME_MASK);    
}
/*****************************************************************************//*!
*
* @brief generate a softare sync trigger to ETM2 module (trigger).
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_GenerateSoftwareTrig2ETM2(void)
{
    SIM->SOPT0 |= (SIM_SOPT0_ETMSYNC_MASK);    
}
/*****************************************************************************//*!
*
* @brief select PWTIN3 input signal from UART0RX.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

__STATIC_INLINE void SIM_SetPWTIN3InputFromUART0Rx(void)
{
    SIM->SOPT1 = (SIM->SOPT1 & (~SIM_SOPT1_UARTPWTS_MASK)) | SIM_SOPT1_UARTPWTS(0);    
}
/*****************************************************************************//*!
*
* @brief select PWTIN3 input signal from UART1RX.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

__STATIC_INLINE void SIM_SetPWTIN3InputFromUART1Rx(void)
{
    SIM->SOPT1 = (SIM->SOPT1 & (~SIM_SOPT1_UARTPWTS_MASK)) | SIM_SOPT1_UARTPWTS(1);    
}
/*****************************************************************************//*!
*
* @brief select PWTIN3 input signal from UART2RX.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

__STATIC_INLINE void SIM_SetPWTIN3InputFromUART2Rx(void)
{
    SIM->SOPT1 = (SIM->SOPT1 & (~SIM_SOPT1_UARTPWTS_MASK)) | SIM_SOPT1_UARTPWTS(2);    
}
/*****************************************************************************//*!
*
* @brief select PWTIN2 input signal from ACMP0_OUT.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetPWTIN2InputFromACMP0(void)
{
    SIM->SOPT1 &= (~SIM_SOPT1_ACPWTS_MASK);    
}
/*****************************************************************************//*!
*
* @brief select PWTIN2 input signal from ACMP1_OUT.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetPWTIN2InputFromACMP1(void)
{
    SIM->SOPT1 |= SIM_SOPT1_ACPWTS_MASK;    
}
/*****************************************************************************//*!
*
* @brief enable invertion of the I2C output.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableI2C0OuputInvertion(void)
{
    SIM->SOPT1 |= SIM_SOPT1_I2C0OINV_MASK;    
}
/*****************************************************************************//*!
*
* @brief disable invertion of the I2C output.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_DisableI2C0OuputInvertion(void)
{
    SIM->SOPT1 &= ~SIM_SOPT1_I2C0OINV_MASK;    
}

/*****************************************************************************//*!
*
* @brief enable 4-wire I2C.
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_Enable4WireI2C0(void)
{
    SIM->SOPT1 |= SIM_SOPT1_I2C04WEN_MASK;    
}
/*****************************************************************************//*!
*
* @brief  disable 4-wire I2C..
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_Disable4WireI2C0(void)
{
    SIM->SOPT1 &= ~SIM_SOPT1_I2C04WEN_MASK;    
}
/*****************************************************************************//*!
*
* @brief UART0 RXD input signal is connected to UART0 module directly. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0Filter(void)
{
    SIM->SOPT0 &= ~(SIM_SOPT0_RXDFE_MASK);   
}
/*****************************************************************************//*!
*
* @brief UART0 RXD input signal is filtered by ACMP0, then injected to UART0. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0FilterByACMP0(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_RXDFE_MASK)) | SIM_SOPT0_RXDFE(1);  
}
/*****************************************************************************//*!
*
* @brief UART0 RXD input signal is filtered by ACMP1, then injected to UART0. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableUART0FilterByACMP1(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_RXDFE_MASK)) | SIM_SOPT0_RXDFE(2);  
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to RTC overflow. 
*        
* @param  none        
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByRTC(void)
{
    SIM->SOPT0 &= ~(SIM_SOPT0_ADHWT_MASK);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to PIT . 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPIT(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_ADHWT_MASK)) | SIM_SOPT0_ADHWT(1);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ETM2 init trigger with 8-bit programmable delay. 
*        
* @param  none      
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Init(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_ADHWT_MASK)) | SIM_SOPT0_ADHWT(2);    
}

/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ETM2 match trigger with 8-bit programmable delay. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByETM2Match(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_ADHWT_MASK)) | SIM_SOPT0_ADHWT(3);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to PIT channel0 overflow. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPITCH0Overflow(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_ADHWT_MASK)) | SIM_SOPT0_ADHWT(4);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to PIT channel1 overflow. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByPITChannel1Overflow(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_ADHWT_MASK)) | SIM_SOPT0_ADHWT(5);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ACMP0 out. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByACMP0Out(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_ADHWT_MASK)) | SIM_SOPT0_ADHWT(6);    
}
/*****************************************************************************//*!
*
* @brief set ADC hardware trigger source to ACMP1 out. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_TriggerADCByACMP1Out(void)
{
    SIM->SOPT0 = (SIM->SOPT0 & ~(SIM_SOPT0_ADHWT_MASK)) | SIM_SOPT0_ADHWT(7);    
}
/*****************************************************************************//*!
*
* @brief Select ACMP0 output as the trigger0 input of ETM2. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelACMP0AsETM2Trigger0(void)
{
    SIM->SOPT0 &= ~(SIM_SOPT0_ACTRG_MASK);  
}
/*****************************************************************************//*!
*
* @brief Select ACMP1 output as the trigger0 input of ETM2. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelACMP1AsETM2Trigger0(void)
{
    SIM->SOPT0 |= (SIM_SOPT0_ACTRG_MASK);  
}
/*****************************************************************************//*!
*
* @brief enable RTC capture to ETM1 input channel1. 
*        
* @param  none       
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableRTCCapture(void)
{
    SIM->SOPT0 |= (SIM_SOPT0_RTCC_MASK);    
}
/*****************************************************************************//*!
*
* @brief enable ACMP0 input capture to ETM1 input channel0. 
*        
* @param  none      
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_EnableACMP0InputCapture(void)
{
    SIM->SOPT0 |= (SIM_SOPT0_ACIC_MASK);    
}
/*****************************************************************************//*!
*
* @brief select TCLK0 for PWT module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK0ForPWT(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_PWTCLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK1 for PWT module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK1ForPWT(void)
{
    SIM->PINSEL = (SIM->PINSEL&(~SIM_PINSEL_PWTCLKPS_MASK)) | SIM_PINSEL_PWTCLKPS(1) ;    
}
/*****************************************************************************//*!
*
* @brief select TCLK2 for PWT module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK2ForPWT(void)
{
    SIM->PINSEL = (SIM->PINSEL&(~SIM_PINSEL_PWTCLKPS_MASK)) | SIM_PINSEL_PWTCLKPS(2) ;    
}
/*****************************************************************************//*!
*
* @brief select TCLK0 for ETM2 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK0ForETM2(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM2CLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK1 for ETM2 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK1ForETM2(void)
{
    SIM->PINSEL = (SIM->PINSEL & (~SIM_PINSEL_ETM2CLKPS_MASK)) | (((uint32_t)0x1)<<SIM_PINSEL_ETM2CLKPS_SHIFT);    
}
/*****************************************************************************//*!
*
* @brief select TCLK2 for ETM2 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK2ForETM2(void)
{
    SIM->PINSEL =(SIM->PINSEL & (~SIM_PINSEL_ETM2CLKPS_MASK)) | (((uint32_t)0x2)<<SIM_PINSEL_ETM2CLKPS_SHIFT);    
}
/*****************************************************************************//*!
*
* @brief select TCLK0 for ETM1 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK0ForETM1(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM1CLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK1 for ETM1 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK1ForETM1(void)
{
    SIM->PINSEL = (SIM->PINSEL & (~SIM_PINSEL_ETM1CLKPS_MASK)) | (((uint32_t)0x1)<<SIM_PINSEL_ETM1CLKPS_SHIFT);    
}
/*****************************************************************************//*!
*
* @brief select TCLK2 for ETM1 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK2ForETM1(void)
{
    SIM->PINSEL = (SIM->PINSEL & (~SIM_PINSEL_ETM1CLKPS_MASK)) | (((uint32_t)0x2)<<SIM_PINSEL_ETM1CLKPS_SHIFT);    
}
/*****************************************************************************//*!
*
* @brief select TCLK0 for ETM0 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK0ForETM0(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM0CLKPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief select TCLK1 for ETM0 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK1ForETM0(void)
{
    SIM->PINSEL = (SIM->PINSEL &(~SIM_PINSEL_ETM0CLKPS_MASK)) | (((uint32_t)0x1)<<SIM_PINSEL_ETM0CLKPS_SHIFT);    
}
/*****************************************************************************//*!
*
* @brief select TCLK2 for ETM0 module. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SelectTCLK2ForETM0(void)
{
    SIM->PINSEL = (SIM->PINSEL &(~SIM_PINSEL_ETM0CLKPS_MASK)) | (((uint32_t)0x2)<<SIM_PINSEL_ETM0CLKPS_SHIFT);    
}
/*****************************************************************************//*!
*
* @brief remap ETM1CH1 to pin PTC5 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH1ToPTC5(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM1PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM1CH1 to pin PTE7. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH1ToPTE7(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM1PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM1CH0 to pin PTC4 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH0ToPTC4(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM1PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM1CH0 to pin PTH2. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM1CH0ToPTH2(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM1PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH1 to pin PTA1 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH1ToPTA1(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH1 to pin PTB3. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH1ToPTB3(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM0PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH0 to pin PTA0 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH0ToPTA1(void)
{
    SIM->PINSEL |= SIM_PINSEL_ETM0PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM0CH0 to pin PTB2. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM0CH0ToPTB3(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_ETM0PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART0 to pin PTB0/1 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART0ToPTB_0_1(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_UART0PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART0 to pin PTA2/3. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART0ToPTA_2_3(void)
{
    SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap SPI0 to pin PTB2/3/4/5 (default).  
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapSPI0ToPTB_2_3_4_5(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_SPI0PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap SPI0 to pin PTE01/2/3.  
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapSPI0ToPTE_0_12_3(void)
{
    SIM->PINSEL |= SIM_PINSEL_SPI0PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap I2C to pin PTA2/3 (default).  
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapI2CToPTA_2_3(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_I2C0PS_MASK;    
}   
/*****************************************************************************//*!
*
* @brief remap I2C to pin PTB6/7 (default).  
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapI2CToPTB_6_7(void)
{
    SIM->PINSEL |= SIM_PINSEL_I2C0PS_MASK;    
} 
/*****************************************************************************//*!
*
* @brief remap RTC to pin PTC4 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapRTCToPTC4(void)
{
    SIM->PINSEL &= ~SIM_PINSEL_RTCPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap RTC to pin PTC5. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapRTCToPTC5(void)
{
    SIM->PINSEL |= SIM_PINSEL_RTCPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap MSCAN to pin PTC6/7 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapMSCANToPTC_6_7(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_MSCANPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap MSCAN to pin PTH2/7. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapMSCANToPTH_2_7(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_MSCANPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap PWTIN1 to pin PTB0 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapPWTIN1ToPTB0(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_MSCANPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap PWTIN1 to pin PTH7. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapPWTIN1ToPTH7(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_MSCANPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap PWTIN0 to pin PTD5 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapPWTIN0ToPTD5(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_MSCANPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap PWTIN0 to pin PTE2. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapPWTIN0ToPTE2(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_MSCANPS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART2 to pin PTD6/7 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART2ToPTD_6_7(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART2 to pin PTI0/1. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART2ToPTI_0_1(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_UART2PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART1 to pin PTC6/7 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART1ToPTC_6_7(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_UART1PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap UART1 to pin PTF2/3. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapUART1ToPTF_2_3(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap SPI1 to pin PTD0/1/2/3 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapSPI1ToPTD_0_1_2_3(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_SPI1PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap SPI1 to pin PTG4/5/6/7. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapSPI1ToPTG_4_5_6_7(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_SPI1PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap I2C1 to pin PTE0/1 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapI2C1ToPTE_0_1(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_I2C1PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap I2C1 to pin PTH3/4. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapI2C1ToPTH_3_4(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_I2C1PS_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH5 to pin PTB5 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH5ToPTB5(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_ETM2PS5_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH5 to pin PTG7. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH5ToPTG7(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_ETM2PS5_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH4 to pin PTB4 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH4ToPTB4(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_ETM2PS4_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH4 to pin PTG6. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH4ToPTG6(void)
{
    SIM->PINSEL1 |= SIM_PINSEL1_ETM2PS4_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH3 to pin PTC3 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH3ToPTC3(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_ETM2PS3_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH3 to pin PTD1. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH3ToPTD1(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 & (~SIM_PINSEL1_ETM2PS3_MASK)) | SIM_PINSEL1_ETM2PS3(1);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH3 to pin PTG5. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH3ToPTG5(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 & (~SIM_PINSEL1_ETM2PS3_MASK)) | SIM_PINSEL1_ETM2PS3(2);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH2 to pin PTC2 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH2ToPTC2(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_ETM2PS2_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH2 to pin PTD0. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH2ToPTD0(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 & (~SIM_PINSEL1_ETM2PS2_MASK)) | SIM_PINSEL1_ETM2PS2(1);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH2 to pin PTG4. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH2ToPTG4(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 & (~SIM_PINSEL1_ETM2PS2_MASK)) | SIM_PINSEL1_ETM2PS2(2);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH1 to pin PTC1 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH1ToPTC1(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_ETM2PS1_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH1 to pin PTH1. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH1ToPTH1(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 & (~SIM_PINSEL1_ETM2PS1_MASK)) | SIM_PINSEL1_ETM2PS1(1);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH1 to pin PTF1. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH1ToPTF1(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 & (~SIM_PINSEL1_ETM2PS1_MASK)) | SIM_PINSEL1_ETM2PS1(2);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH0 to pin PTC0 (default). 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH0ToPTC0(void)
{
    SIM->PINSEL1 &= ~SIM_PINSEL1_ETM2PS0_MASK;    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH0 to pin PTH0. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH0ToPTH0(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 & (~SIM_PINSEL1_ETM2PS0_MASK)) | SIM_PINSEL1_ETM2PS0(1);    
}
/*****************************************************************************//*!
*
* @brief remap ETM2CH0 to pin PTF0. 
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_RemapETM2CH0ToPTF0(void)
{
    SIM->PINSEL1 = (SIM->PINSEL1 &(~SIM_PINSEL1_ETM2PS0_MASK)) | SIM_PINSEL1_ETM2PS0(2);    
}
/*****************************************************************************//*!
*
* @brief set clock3 divide CLKDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClock3Divide(void)
{
    SIM->CLKDIV |= SIM_CLKDIV_OUTDIV3_MASK;    
}
/*****************************************************************************//*!
*
* @brief set clock2 divide CLKDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClock2Divide(void)
{
    SIM->CLKDIV |= SIM_CLKDIV_OUTDIV2_MASK;    
}
/*****************************************************************************//*!
*
* @brief set clock1 divide CLKDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetClock1Divide(uint8_t u8divide)
{
    SIM->CLKDIV |= SIM_CLKDIV_OUTDIV1(u8divide);    
}
/*****************************************************************************//*!
*
* @brief set bus divide BUSDIV.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void SIM_SetBusDivide(uint8_t u8Divide)
{
    SIM->CLKDIV = u8Divide;    
}

#endif


/*! @} End of sim_api_list                                                   */

void SIM_Init(SIM_ConfigType *pConfig);
void SIM_SetClockGating(uint32_t u32PeripheralMask, uint8_t u8GateOn);
uint32_t SIM_GetStatus(uint32_t u32StatusMask);
uint8_t SIM_ReadID(IDType sID);

#endif /* SIM_H_ */


