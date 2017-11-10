/******************************************************************************
*
* @brief    Real-ETMe counter (RTC) driver head file.  
*
******************************************************************************/
#ifndef RTC_H_
#define RTC_H_
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
* RTC control bit definition
*
*//*! @addtogroup rtc_controlbit
* @{
*******************************************************************************/

#define RTC_OUTPUT_ENABLE           1	/*!< enable RTCO pin  */ 
#define RTC_INTERRUPT_ENABLE        1	/*!< enable RTC interrupt  */ 
#define RTC_CLKSRC_EXTERNAL         0	/*!< select external clock as RTC clock source  */
#define RTC_CLKSRC_1KHZ             1	/*!< select LPO as RTC clock source  */
#define RTC_CLKSRC_IREF             2	/*!< select internal reference clock as RTC clock source  */
#define RTC_CLKSRC_BUS              3	/*!< select bus clock as RTC clock source  */
#define RTC_CLK_PRESCALER_128       1	/*!< presalcer is 1 or 128 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_256       2	/*!< presalcer is 2 or 256 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_512       3	/*!< presalcer is 4 or 512 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_1024      4	/*!< presalcer is 8 or 1024 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_2048      5	/*!< presalcer is 16 or 2048 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_100       6	/*!< presalcer is 32 or 100 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_1000      7	/*!< presalcer is 64 or 1000 according to RTCLKS bits */


/*! @} End of rtc_controlbit                                                  */

/******************************************************************************
* Types
******************************************************************************/

/*
 * Callback type
 */

/******************************************************************************
* RTC callback function declaration
*
*//*! @addtogroup rtc_callback
* @{
*******************************************************************************/

/*!
 * @brief RTC Callback type.
 *
 */

typedef void (*RTC_CallbackType)(void);

/*! @} End of rtc_callback                                                    */


/* RTC configuration structure 
 */  
/*!
 * @brief RTC configuration type.
 *
 */
typedef struct
{   
    uint16_t bReserved                  : 4;    /*!< reserved */     
    uint16_t bRTCOut                    : 1;    /*!< 1: RTCO pin is enable, 0: RTCO pin is disable */
    uint16_t bReserved1                 : 1;    /*!< reserved */ 
    uint16_t bInterruptEn               : 1;    /*!< 1: RTC interrupt is enable, 0: RTC interrupt is disable */
    uint16_t bFlag                      : 1;    /*!< 1: RTC flag is set, 0: RTC flag is not set */   
    uint16_t bClockPresaler             : 3;    /*!< 1: RTC presclaer, from 0x0 to 0x7 */    
    uint16_t bReserved2                 : 3;    /*!< reserved */ 
    uint16_t bClockSource               : 2;    /*!< RTC clock source selection from 0x0 to 0x3 */
    uint16_t u16ModuloValue                ;    /*!< 16-bit rtc modulo value */
} RTC_ConfigType, *RTC_ConfigPtr; 


/******************************************************************************
* Global variables
******************************************************************************/

/*!
 * inline functions
 */

/******************************************************************************
* RTC API list
*
*//*! @addtogroup rtc_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief enable rtc interrupt.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void RTC_EnableInt(void)
{
    RTC->SC |= RTC_SC_RTIE_MASK;
}


/*****************************************************************************//*!
*
* @brief disable rtc interrupt.
*        
* @param   none
*
* @return non
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void RTC_DisableInt(void)
{
    RTC->SC &= ~RTC_SC_RTIE_MASK;
}


/*****************************************************************************//*!
*
* @brief set rtc modulo value.
*        
* @param[in]   u16Mod_Value
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void RTC_SetModulo(uint16_t u16Mod_Value)
{
 
    RTC->MOD = u16Mod_Value;
}

/*****************************************************************************//*!
*
* @brief set rtc clock source and presalcer.
*        
* @param[in]   u16Clock_Number clock source number
* @param[in]   u16Presalcer prescaler value
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void RTC_SetClock(uint16_t u16Clock_Number, uint16_t u16Presalcer)
{
    uint32_t u32rtc_sc;
        
    u32rtc_sc  = RTC->SC; 
    u32rtc_sc &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
    u32rtc_sc |= RTC_SC_RTCLKS(u16Clock_Number) | RTC_SC_RTCPS(u16Presalcer); 
    RTC->SC   = u32rtc_sc;
}

/*****************************************************************************//*!
*
* @brief get rtc flag bit.
*        
* @param  none 
*
* @return bflag.
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t RTC_GetFlags(void)
{
  uint8_t bflag;
  
  bflag = RTC->SC & RTC_SC_RTIF_MASK; 
  
  return bflag;  
}


/*****************************************************************************//*!
*
* @brief clear rtc flag bit.
*        
* @param  none 
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void RTC_ClrFlags(void)
{
    RTC->SC |= RTC_SC_RTIF_MASK; 
}


/******************************************************************************
* Global functions
******************************************************************************/
void RTC_Init(RTC_ConfigType *pConfig);
void RTC_SetCallback(RTC_CallbackType pfnCallback);
void RTC_DeInit(void);

/*! @} End of rtc_api_list                                                   */

#ifdef __cplusplus
}
#endif
#endif /* RTC_H_ */
