/******************************************************************************
* @brief header file for ACMP utilities. 
*
*******************************************************************************
*
* provide APIs for accessing ACMP
******************************************************************************/
#ifndef _MY_ACMP_H_
#define _MY_ACMP_H_
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Includes
******************************************************************************/

/******************************************************************************
* Constants
******************************************************************************/

/* DAC reference select */
enum
{
    DAC_REF_BANDGAP = 0,
    DAC_REF_VDDA
};

/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
 * ACMP module number definition                                               *
 ******************************************************************************/
#define     MAX_ACMP_NO             2

/******************************************************************************
* ACMP positive and negative pin select definition
*
*//*! @addtogroup acmp_pinsel_list
* @{
*******************************************************************************/
#define     ACMP_INPUT_P_EXT0       (0<<4)  /*!< positive pin select external pin 0 */
#define     ACMP_INPUT_P_EXT1       (1<<4)  /*!< positive pin select external pin 1 */
#define     ACMP_INPUT_P_EXT2       (2<<4)  /*!< positive pin select external pin 2 */
#define     ACMP_INPUT_P_DAC        (3<<4)  /*!< positive pin select internal DAC */

#define     ACMP_INPUT_N_EXT0       0       /*!< positive pin select external pin 0 */
#define     ACMP_INPUT_N_EXT1       1       /*!< positive pin select external pin 1 */
#define     ACMP_INPUT_N_EXT2       2       /*!< positive pin select external pin 2 */
#define     ACMP_INPUT_N_DAC        3       /*!< positive pin select internal DAC */
/*! @} End of acmp_pinsel_list                                                */

/******************************************************************************
* ACMP interrupt sensitivity edge definition
*
*//*! @addtogroup acmp_intedgesel
* @{
*******************************************************************************/
#define     ACMP_SENSITIVITYMODE_FALLING   0    /*!< interrupt on falling edge  */
#define     ACMP_SENSITIVITYMODE_RISING    1    /*!< interrupt on rising edge  */
#define     ACMP_SENSITIVITYMODE_ANY       3    /*!< interrupt on falling or rising edge */ 
/*! @} End of acmp_intedgesel                                                 */


/******************************************************************************
* ACMP hysterisis selection definition
*
*//*! @addtogroup acmp_hyst
* @{
*******************************************************************************/
#define     ACMP_HYST_20MV                 (0<<6)  /*!< 20mv hyst */
#define     ACMP_HYST_30MV                 (1<<6)  /*!< 30mv hyst */
/*! @} End of acmp_hyst                                                       */


/******************************************************************************
* ACMP internal DAC reference selection definition
*
*//*! @addtogroup acmp_dacref
* @{
*******************************************************************************/
#define     ACMP_DAC_REFERENCE_BANDGAP     (0<<6)  /*!< select bandgap as refference */
#define     ACMP_DAC_REFERENCE_VDDA        (1<<6)  /*!< select VDDA as refference */
/*! @} End of acmp_dacref                                                     */


/******************************************************************************
* Types
******************************************************************************/

/*! @brief ACMP_CALLBACK function declaration                                  */
typedef void (*ACMP_CallbackPtr)(void);
/*! @} End of acmp_callback                                                    */

/******************************************************************************
* ACMP control status struct
*
*//*! @addtogroup acmp_ctrlstatusstruct
* @{
*******************************************************************************/
/*!
 * @brief ACMP control and status fields type.
 *
 */

typedef union 
{
    uint8_t byte;    				 /*!< byte field of union type */
    struct 
    {
        uint8_t bMod        : 2;     /*!< Sensitivity modes of the interrupt trigger */
        uint8_t bOutEn      : 1;     /*!< Output can be placed onto an external pin */
        uint8_t bOutState   : 1;     /*!< The current value of the analog comparator output */
        uint8_t bIntEn      : 1;     /*!< ACMP interrupt enable */
        uint8_t bIntFlag    : 1;     /*!< ACMP Interrupt Flag Bit */
        uint8_t bHyst       : 1;     /*!< Selects ACMP hystersis */
        uint8_t bEn         : 1;     /*!< Enables the ACMP module */
    }bits;      				     /*!< bitfield of union type */
}ACMP_CtrlStatusType, *ACMP_CtrlStatusPtr;  /*!< ACMP Control/Status reg structure */
/*! @} End of acmp_ctrlstatusstruct                                           */

/******************************************************************************
* ACMP pin select struct
*
*//*! @addtogroup acmp_pinselectstruct
* @{
*******************************************************************************/
/*!
* @brief ACMP external pins control struct.
*
*/

typedef union 
{
    uint8_t byte;    				 /*!< byte field of union type */
    struct 
    {
        uint8_t bNegPin  : 2;        /*!< Negative pin select */
        uint8_t          : 2;
        uint8_t bPosPin  : 2;        /*!< Positive pin select */
        uint8_t          : 2;
    }bits;      				     /*!< bitfield of union type */  
}ACMP_PinSelType, *ACMP_PinSelPtr; 	     /*!< ACMP Pin select structure */ 
/*! @} End of acmp_pinselectstruct                                            */

/******************************************************************************
* ACMP DAC control struct
*
*//*! @addtogroup acmp_dacctrlstruct
* @{
*******************************************************************************/
/*!
* @brief ACMP internal ADC control struct.
*
*/
typedef union 
{
    uint8_t byte;    				 /*!< byte field of union type */
    struct 
    {
        uint8_t bVal  : 6;           /*!< 6 bit DAC value */
        uint8_t bRef  : 1;           /*!< 6 bit DAC reference select */
        uint8_t bEn   : 1;           /*!< 6 bit DAC enable bit */
    }bits;      				     /*!< bitfield of union type */  
}ACMP_DACType, *ACMP_DACPtr;	     /*!< ACMP DAC control structure */ 
/*! @} End of acmp_dacctrlstruct                                              */

/******************************************************************************
* ACMP pin enable union
*
*//*! @addtogroup acmp_pinenunion
* @{
*******************************************************************************/
/*!
* @brief ACMP external input pin enable control struct.
*
*/
typedef union 
{
    uint8_t byte;    				 /*!< byte field of union type */
    struct 
    {
        uint8_t bEn   : 3;           /*!< ACMP external input pin enable */
        uint8_t bRsvd : 5;
    }bits;      				     /*!< bitfield of union type */  
}ACMP_PinEnType, *ACMP_PinEnPtr;	 /*!< ACMP Pin enable structure */ 
/*! @} End of acmp_pinenunion                                                 */

/******************************************************************************
* ACMP config struct
*
*//*! @addtogroup acmp_configstruct
* @{
*******************************************************************************/
/*!
* @brief ACMP module configuration struct.
*
*/

typedef struct 
{
    ACMP_CtrlStatusType  sCtrlStatus;     /*!< ACMP control and status */
    ACMP_PinSelType      sPinSelect;      /*!< ACMP pin select */
    ACMP_DACType         sDacSet;         /*!< ACMP internal dac set */
    ACMP_PinEnType       sPinEnable;      /*!< ACMP external pin control */
}ACMP_ConfigType, *ACMP_ConfigPtr;
/*! @} End of acmp_configstruct                                               */

/******************************************************************************
* Global variables
******************************************************************************/

/*!
 * inline functions
 */
/******************************************************************************
* ACMP api list.
*
*//*! @addtogroup acmp_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
*
* @brief  enable the acmp module.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_Disable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_Enable(ACMP_Type *pACMPx)
{
    pACMPx->CS |= ACMP_CS_ACE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable the acmp module.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_Enable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_Disable(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACE_MASK;
}

/*****************************************************************************//*!
*
* @brief  select sensitivity modes of the interrupt trigger.
*        
* @param[in]  pACMPx         pointer to an ACMP module.
* @param[in]  u8EdgeSelect   falling or rising selction, 0~3. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_SelectIntMode(ACMP_Type *pACMPx, uint8_t u8EdgeSelect)
{
    pACMPx->CS &= ~ACMP_CS_ACMOD_MASK;
    pACMPx->CS |= ACMP_CS_ACMOD(u8EdgeSelect & 0x3);
}

/*****************************************************************************//*!
*
* @brief  enable the ACMP module analog comparator output.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_DisablePinOut.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_EnablePinOut(ACMP_Type *pACMPx)
{
    pACMPx->CS |= ACMP_CS_ACOPE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable the ACMP module analog comparator output.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_EnablePinOut.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DisablePinOut(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACOPE_MASK;
}

/*****************************************************************************//*!
*
* @brief  select ACMP hystersis. 
*        
* @param[in]  pACMPx           pointer to an ACMP module.
* @param[in]  u8HystSelect     ACMP_HYST_20MV or ACMP_HYST_30MV.   
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_SelectHyst(ACMP_Type *pACMPx, uint8_t u8HystSelect)
{
    pACMPx->CS &= ~ACMP_CS_HYST_MASK;
    pACMPx->CS |= u8HystSelect;
}

/*****************************************************************************//*!
*
* @brief  enable the acmp module interrupt.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_DisableInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_EnableInterrupt(ACMP_Type *pACMPx)
{
    pACMPx->CS |= ACMP_CS_ACIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable the acmp module interrupt.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_EnableInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DisableInterrupt(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  get the interrupt flag bit.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_ClrFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t ACMP_GetFlag(ACMP_Type *pACMPx)
{
    return (pACMPx->CS & ACMP_CS_ACF_MASK);
}

/*****************************************************************************//*!
*
* @brief  clear the interrupt flag bit.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_GetFlag.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_ClrFlag(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACF_MASK;
}

/*****************************************************************************//*!
*
* @brief  ACMP Positive Input Select.
*        
* @param[in]  pACMPx        pointer to an ACMP module.
* @param[in]  u8PosPinSel   positive input select, ACMP_INPUT_P_EXT0~2 or ACMP_INPUT_P_DAC.     
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_NegativeInputSelect.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_PositiveInputSelect(ACMP_Type *pACMPx, uint8_t u8PosPinSel)
{
    pACMPx->C0 &= ~ACMP_C0_ACPSEL_MASK;
    pACMPx->C0 |= u8PosPinSel;
}

/*****************************************************************************//*!
*
* @brief  ACMP Negative Input Select.
*        
* @param[in]  pACMPx        pointer to an ACMP module.
* @param[in]  u8NegPinSel   negative input select, ACMP_INPUT_N_EXT0~2 or ACMP_INPUT_N_DAC.  
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_PositiveInputSelect.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_NegativeInputSelect(ACMP_Type *pACMPx, uint8_t u8NegPinSel)
{
    pACMPx->C0 &= ~ACMP_C0_ACNSEL_MASK;
    pACMPx->C0 |= u8NegPinSel;
}

/*****************************************************************************//*!
*
* @brief  Enable 6 bit DAC in ACMP module.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_DacDisable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacEnable(ACMP_Type *pACMPx)
{
    pACMPx->C1 |= ACMP_C1_DACEN_MASK;
}

/*****************************************************************************//*!
*
* @brief  Disable 6 bit DAC in ACMP module.
*        
* @param[in]  pACMPx      pointer to an ACMP module.
*              
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see    ACMP_DacEnable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacDisable(ACMP_Type *pACMPx)
{
    pACMPx->C1 &= ~ACMP_C1_DACEN_MASK;
}

/*****************************************************************************//*!
*
* @brief  ACMP 6 bit DAC Reference Select.
*        
* @param[in]  pACMPx        pointer to an ACMP module.
* @param[in]  u8RefSelect   dac reference select:ACMP_DAC_REFERENCE_BANDGAP or ACMP_DAC_REFERENCE_VDDA.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacReferenceSelect(ACMP_Type *pACMPx, uint8_t u8RefSelect)
{
    pACMPx->C1 &= ~ACMP_C1_DACREF_MASK;
    pACMPx->C1 |= u8RefSelect;
}

/*****************************************************************************//*!
*
* @brief  ACMP 6 bit DAC Output Value Set.
*        
* @param[in]  pACMPx        pointer to an ACMP module.
* @param[in]  u8DacValue    dac output set, Voutput= (Vin/64)x(DACVAL[5:0]+1).
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacOutputSet(ACMP_Type *pACMPx, uint8_t u8DacValue)
{
    ASSERT(!(u8DacValue & (~ACMP_C1_DACVAL_MASK)));
    pACMPx->C1 &= ~ACMP_C1_DACVAL_MASK;
    pACMPx->C1 |= ACMP_C1_DACVAL(u8DacValue);
}

/*****************************************************************************//*!
*
* @brief  Enable ACMP input pin.
*        
* @param[in]  pACMPx        pointer to an ACMP module.
* @param[in]  u8InputPin    ACMP external pin, 0~2.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_InputPinEnable(ACMP_Type *pACMPx, uint8_t u8InputPin)
{
    ASSERT(!(u8InputPin & (~ACMP_C2_ACIPE_MASK)));
    pACMPx->C2 |= ACMP_C2_ACIPE(u8InputPin);
}

/*****************************************************************************//*!
*
* @brief  Disable ACMP input pin.
*        
* @param[in]  pACMPx        pointer to an ACMP module.
* @param[in]  u8InputPin    ACMP external pin, 0~2.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_InputPinDisable(ACMP_Type *pACMPx, uint8_t u8InputPin)
{
    ASSERT(!(u8InputPin & (~ACMP_C2_ACIPE_MASK)));
    pACMPx->C2 &= ~ACMP_C2_ACIPE(u8InputPin);
}

/*! @} End of acmp_api_list                                                  */

/******************************************************************************
* Global functions
******************************************************************************/
void ACMP_Init(ACMP_Type *pACMPx, ACMP_ConfigType *pConfig);
void ACMP_DeInit(ACMP_Type *pACMPx); 
void ACMP_ConfigDAC(ACMP_Type *pACMPx, ACMP_DACType *pDACConfig);
void ACMP_SetCallback(ACMP_Type *pACMPx, ACMP_CallbackPtr pfnCallback);

#ifdef __cplusplus
}
#endif
#endif /* _MY_ACMP_H_ */



