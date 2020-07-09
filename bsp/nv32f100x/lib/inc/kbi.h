/******************************************************************************
**
* @brief header file for KBI. 
*
*******************************************************************************
*
* provide APIs for accessing KBI
******************************************************************************/
#ifndef _KBI_H_
#define _KBI_H_
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Includes
******************************************************************************/

/******************************************************************************
* Constants
******************************************************************************/

/*!
* @brief KBI MODE select enum.
*
*/
typedef enum
{
    KBI_MODE_EDGE_ONLY = 0,             /*!< select  edge only mode  */         
    KBI_MODE_EDGE_LEVEL                 /*!< select  both edge and level  mode */
}KBI_ModeType;


 /*!
 * @brief KBI Edge select enum.
 *
 */
typedef enum
{
    KBI_FALLING_EDGE_LOW_LEVEL = 0,     /*!< select falling edge and/or low level  */
    KBI_RISING_EDGE_HIGH_LEVEL          /*!< select rising edge and/or high level  */
}KBI_EdgeType;


/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
* KBI module max number and port pins definition
*
*//*! @addtogroup kbi_macro
* @{
*******************************************************************************/
#define KBI_MAX_NO              2                  /*!< max number of modules */

#if defined(CPU_NV32)|| defined(CPU_NV32M3)
   #define KBI_MAX_PINS_PER_PORT   8                  /*!< max number of pins */
#elif defined(CPU_NV32M4)
   #define KBI_MAX_PINS_PER_PORT   32                  /*!< max number of pins */
#endif
/*! @} End of kbi_macro                                                    */


/******************************************************************************
* Types
******************************************************************************/

/*! @brief KBI_CALLBACK function declaration                                  */
typedef void (*KBI_CallbackType)(void);                     
/*! @} End of kbi_callback                                                    */



/******************************************************************************
* KBI pin config struct
*
*//*! @addtogroup kbi_pinconfigstruct
* @{
*******************************************************************************/
/*!
* @brief KBI pin enable and edge select struct.
*
*/

typedef struct
{
    uint8_t     bEdge   : 1;                                /*!< edge/level select bit */
    uint8_t     bEn     : 1;                                /*!< pin enable bit */
    uint8_t     bRsvd   : 6;                                /*!< reserved */
} KBI_PinConfigType;
/*! @} End of kbi_pinconfigstruct                                             */


/******************************************************************************
* KBI config struct
*
*//*! @addtogroup kbi_configstruct
* @{
*******************************************************************************/
/*!
 * @brief KBI status and control struct.
 *
 */

typedef struct
{
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
    struct
    {
        uint8_t     bMode   : 1;                            /*!< KBI detection mode select */
        uint8_t     bIntEn  : 1;                            /*!< KBI interrupt enable bit */
        uint8_t     bRsvd   : 6;                            /*!< reserved */
    } sBits;
#elif  defined(CPU_NV32M4)
    struct
    {
        uint32_t     bMode   : 1;                            /*!< KBI detection mode select */
        uint32_t     bIntEn  : 1;                            /*!< KBI interrupt enable bit */
        uint32_t     bRsvd2  : 2;                           /*!< reserved */
        uint32_t     bKbspEn : 1;							  /*!<Real KBI_SP register enable*/
		uint32_t     bRstKbsp: 1;                            /*!<Reset KBI_SP register*/
        uint32_t     bRsvd26 : 26;                           /*!< reserved */
    } sBits;
#endif
    KBI_PinConfigType   sPin[KBI_MAX_PINS_PER_PORT];
} KBI_ConfigType, *KBI_ConfigTypePtr;
/*! @} End of kbi_configstruct                                                */

/******************************************************************************
* Global variables
******************************************************************************/
/*!
 * inline functions
 */
/******************************************************************************
* KBI api list
*
*//*! @addtogroup kbi_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
*
* @brief set detect falling edge only.
*        
* @param[in]   pKBI          pointer to KBI module.
* @param[in]   PinMasks      indicate pin numbers.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_DetectRisingEdge.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectFallingEdge(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectFallingEdge(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC &= ~KBI_SC_KBMOD_MASK;
    pKBI->ES &= ~(PinMasks);
}

/*****************************************************************************//*!
*
* @brief set detect falling edge only.
*        
* @param[in]   pKBI         pointer to KBI module.
* @param[in]   PinMasks     indicate pin numbers.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_DetectFallingEdge.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectRisingEdge(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectRisingEdge(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC &= ~KBI_SC_KBMOD_MASK;
    pKBI->ES |= (PinMasks);    
}

/*****************************************************************************//*!
*
* @brief set detect falling edge only.
*        
* @param[in]   pKBI         pointer to KBI module.
* @param[in]   PinMasks     indicate pin number/mask.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_DetectFallingEdgeLowLevel.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectRisingEdgeHighLevel(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectRisingEdgeHighLevel(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC |= KBI_SC_KBMOD_MASK;
    pKBI->ES |= (PinMasks);    
}

/*****************************************************************************//*!
*
* @brief set detect falling edge only.
*        
* @param[in]   pKBI         pointer to KBI module.
* @param[in]   PinMasks     indicate pin number/mask.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_DetectRisingEdgeHighLevel.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectFallingEdgeLowLevel(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectFallingEdgeLowLevel(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC |= KBI_SC_KBMOD_MASK;
    pKBI->ES &= ~(PinMasks);        
}

/*****************************************************************************//*!
*
* @brief enable the pin specified.
*        
* @param[in]   pKBI         pointer to KBI module.
* @param[in]   PinMasks     indicate pin number/mask.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_Disable.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_Enable(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_Enable(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->PE |= (PinMasks);        
}

/*****************************************************************************//*!
*
* @brief disable the pin specified.
*        
* @param[in]   pKBI         pointer to KBI module.
* @param[in]   PinMasks     indicate pin number/mask.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_Enable.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_Disable(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_Disable(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->PE &= ~(PinMasks);        
}

/*****************************************************************************//*!
*
* @brief enable the corresponding interrupt.
*        
* @param[in]   pKBI         pointer to KBI module.
*          
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_DisableInt.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_EnableInt(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_KBIE_MASK;        
}


/*****************************************************************************//*!
*
* @brief disable the corresponding interrupt.
*        
* @param[in]  pKBI         pointer to KBI module.
*          
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see KBI_EnableInt.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_DisableInt(KBI_Type *pKBI)
{
    pKBI->SC &= ~KBI_SC_KBIE_MASK;        
}

/*****************************************************************************//*!
*
* @brief Get the corresponding status flag bits.
*        
* @param[in]   pKBI         pointer to KBI module.
*          
* @return uint8_t.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_ClrFlags.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  uint8_t KBI_GetFlags(KBI_Type *pKBI)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  uint32_t KBI_GetFlags(KBI_Type *pKBI)
#endif
{
    return (pKBI->SC & KBI_SC_KBF_MASK);        
}

/*****************************************************************************//*!
*
* @brief clear the corresponding status flag bits.
*        
* @param[in]   pKBI         pointer to KBI module
*          
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see KBI_GetFlags.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_ClrFlags(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_KBACK_MASK;        
}

#if defined(CPU_NV32M4)
/*****************************************************************************//*!
*
* @brief Real KBI_SP register enable.
*        
* @param[in]   pKBI         pointer to KBI module
*          
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see The real ETMe value of Keyboard source pin to be read.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_SPEnable(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_KBSPEN_MASK;        
}

/*****************************************************************************//*!
*
* @brief Get KBI source pin register fields.
*        
* @param[in]   pKBI         pointer to KBI module.
*          
* @return uint32_t.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_GetSP.
*
*****************************************************************************/
__STATIC_INLINE  uint32_t KBI_GetSP(KBI_Type *pKBI)
{
    return (pKBI->SP & KBI_SP_SP_MASK);        
}

/*****************************************************************************//*!
*
* @brief Reset KBI_SP register.
*        
* @param[in]   pKBI         pointer to KBI module
*          
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see KBI_RstSP.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_RstSP(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_RSTKBSP_MASK;        
}
#endif

/*! @} End of kbi_api_list                                                  */

/******************************************************************************
* Global functions
******************************************************************************/

void KBI_Init(KBI_Type *pKBI, KBI_ConfigType *pConfig);
void KBI_SetCallback(KBI_Type *pKBI, KBI_CallbackType pfnCallback);

#ifdef __cplusplus
}
#endif
#endif 
