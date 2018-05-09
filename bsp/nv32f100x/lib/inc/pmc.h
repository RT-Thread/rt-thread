/******************************************************************************
*
* @brief header file for PMC. 
*
*******************************************************************************
*
* provide APIs for accessing PMC
******************************************************************************/
#ifndef PMC_H_
#define PMC_H_
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/
/******************************************************************************
* PMC system mode definition
*
*//*! @addtogroup pmc_sysmode
* @{
*******************************************************************************/
#define PmcModeRun     0                     /*!< run mode */
#define PmcModeWait    1                     /*!< wait mode */
#define PmcModeStop4   2                     /*!< stop4 mode */
#define PmcModeStop3   3                     /*!< stop3 mode */
/*! @} End of pmc_sysmode                                                     */

/******************************************************************************
* PMC LVD and LVW voltage definition
*
*//*! @addtogroup pmc_voltageselect
* @{
*******************************************************************************/
#define PmcLVDTrip_Low   0                    /*!< LVD low trip point */
#define PmcLVDTrip_High  1                     /*!< LVD high trip point  */

#define PmcLVWTrip_Low   0                     /*!< LVW low trip point */
#define PmcLVWTrip_Mid1  1                     /*!< LVW mid1 trip point */
#define PmcLVWTrip_Mid2  2                     /*!< LVW mid2 trip point */
#define PmcLVWTrip_High  3                     /*!< LVW high trip point */
/*! @} End of pmc_voltageselect                                               */


/******************************************************************************
* Types
******************************************************************************/

/******************************************************************************
* PMC control  struct
*
*//*! @addtogroup pmc_ctrlstruct
* @{
*******************************************************************************/
/*!
 * @brief PMC Control Structure Type.
 *
 */

typedef union 
{
   uint8_t byte;						  /*!< byte field of union type */
   struct 
   {     
       uint8_t bBandgapEn        :1;      /*!< bandgap enable */
       uint8_t bBandgapDrv       :1;      /*!< bandgap drive select */
       uint8_t bLvdEn            :1;      /*!< LVD enable */
       uint8_t bLvdStopEn        :1;      /*!< LVD enable in stop mode */
       uint8_t bLvdRstEn         :1;      /*!< reset enable when VLD evvent */
       uint8_t bLvwIrqEn         :1;      /*!< LVW int enable */
       uint8_t bLvwAck           :1;      /*!< LVW acknowledge */
       uint8_t bLvwFlag          :1;      /*!< LVW flag */
   }bits; 								  /*!< bitfield of union type */
}PMC_Ctrl1Type, *PMC_Ctrl1Ptr;		  /*!< PMC control1 reg structure */
/*! @} End of pmc_ctrlstruct                                                  */

/******************************************************************************
* PMC control-- voltage select type.
*
*//*! @addtogroup pmc_voltselectstruct
* @{
*******************************************************************************/
/*!
 * @brief PMC control-- voltage select type.
 *
 */
typedef union 
{
   uint8_t byte;						   /*!< byte field of union type */
   struct 
   {     
       uint8_t           :4;               /*!< none */  
       uint8_t bLVWV     :2;               /*!< LVW voltage select */  
       uint8_t bLVDV     :1;               /*!< LVD voltage select */  
       uint8_t           :1;               /*!< none */                 
   }bits;  								   /*!< bitfield of union type */
}PMC_Ctrl2Type, *PMC_Ctrl2Ptr;		   /*!< PMC control2 reg structure */
/*! @} End of pmc_voltselectstruct                                            */

/******************************************************************************
* PMC configrue type.
*
*//*! @addtogroup pmc_configstruct
* @{
*******************************************************************************/
/*!
 * @brief PMC configrue type.
 *
 */

typedef struct 
{
    PMC_Ctrl1Type    sCtrlstatus;          /*!< PMC control and status */  
    PMC_Ctrl2Type    sDetectVoltSelect;    /*!< LVW and LVW voltage select */  
}PMC_ConfigType, *PMC_ConfigPtr;		   /*!< PMC configuration structure */
/*! @} End of pmc_configstruct                                            */  



/******************************************************************************
* Global variables
******************************************************************************/

/*!
 * inline functions
 */
/******************************************************************************
* PMC api list.
*
*//*! @addtogroup pmc_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
*
* @brief  enable LVD events during stop mode.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_DisableLVDInStopMode.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVDInStopMode(PMC_Type *pPMC)
{
    pPMC->SPMSC1 |= PMC_SPMSC1_LVDSE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable LVD events during stop mode.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_EnableLVDInStopMode.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVDInStopMode(PMC_Type *pPMC)
{
    pPMC->SPMSC1 &= ~PMC_SPMSC1_LVDSE_MASK;
}

/*****************************************************************************//*!
*
* @brief  enable LVD events to generate a hardware reset,  note: write once.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_DisableLVDRst.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVDRst(PMC_Type *pPMC)
{
    pPMC->SPMSC1 |= PMC_SPMSC1_LVDRE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable LVD events to generate a hardware reset,  note: write once.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_EnableLVDRst.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVDRst(PMC_Type *pPMC)
{
    pPMC->SPMSC1 &= ~PMC_SPMSC1_LVDRE_MASK;
}

/*****************************************************************************//*!
*
* @brief  enable low-voltage detect logic,  note: write once.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_DisableLVD.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVD(PMC_Type *pPMC)
{
    pPMC->SPMSC1 |= PMC_SPMSC1_LVDE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable low-voltage detect logic,  note: write once
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see PMC_EnableLVD.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVD(PMC_Type *pPMC)
{
    pPMC->SPMSC1 &= ~PMC_SPMSC1_LVDE_MASK;
}

/*****************************************************************************//*!
*
* @brief  set the low-voltage detect trip point voltage, note: write once.
* 
* @param[in]  pPMC              pointer to the PMC module.
* @param[in]  Trippoint         LVD trip point voltage,0~1.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_SetLVWTripVolt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_SetLVDTripVolt(PMC_Type *pPMC, uint8_t Trippoint)
{
    if(Trippoint)
        pPMC->SPMSC2 |= PMC_SPMSC2_LVDV_MASK;
    else
        pPMC->SPMSC2 &= ~PMC_SPMSC2_LVDV_MASK;
}

/*****************************************************************************//*!
*
* @brief  set the low-voltage warning (LVW) trip point voltage.
* 
* @param[in]  pPMC              pointer to the PMC module.
* @param[in]  Trippoint         LVW trip point voltage,0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_SetLVDTripVolt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_SetLVWTripVolt(PMC_Type *pPMC, uint8_t Trippoint)
{
    pPMC->SPMSC2 &= ~PMC_SPMSC2_LVWV_MASK;
    pPMC->SPMSC2 |= PMC_SPMSC2_LVWV(Trippoint);
}

/*****************************************************************************//*!
*
* @brief  Enable hardware interrupt requests for LVWF.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_DisableLVWInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVWInterrupt(PMC_Type *pPMC)
{
   pPMC->SPMSC1 |= PMC_SPMSC1_LVWIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  Disable hardware interrupt requests for LVWF.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_EnableLVWInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVWInterrupt(PMC_Type *pPMC)
{
   pPMC->SPMSC1 &= ~PMC_SPMSC1_LVWIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  get the lvw warning flag.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return uint8_t lvw warning flag.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_ClrLVWFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t PMC_GetLVWFlag(PMC_Type *pPMC)
{
   return (pPMC->SPMSC1 & PMC_SPMSC1_LVWF_MASK);
}

/*****************************************************************************//*!
*
* @brief  clear the lvw warning flag.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_GetLVWFlag.
*
*****************************************************************************/
__STATIC_INLINE void PMC_ClrLVWFlag(PMC_Type *pPMC)
{
   pPMC->SPMSC1 |= PMC_SPMSC1_LVWACK_MASK;
}

/*! @} End of pmc_api_list                                                    */

/******************************************************************************
* Global functions
******************************************************************************/

void PMC_Init(PMC_Type *pPMC, PMC_ConfigType *pPMC_Config);
void PMC_DeInit(PMC_Type *pPMC);
void PMC_SetMode(PMC_Type *pPMC,uint8_t u8PmcMode);

#ifdef __cplusplus
}
#endif
#endif /* PMC_H_ */
