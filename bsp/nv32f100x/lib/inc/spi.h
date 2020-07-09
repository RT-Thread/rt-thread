/******************************************************************************
*
* @brief header file for SPI module utilities (SPI). 
*
*******************************************************************************
*
* provide APIs for accessing SPI module (SPI)
******************************************************************************/

#ifndef SPI_H_
#define SPI_H_
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
/* maximum number of SPIs */
#define     MAX_SPI_NO              2



/******************************************************************************
* define SPI register default value
*
*//*! @addtogroup spi_default_value
* @{
*******************************************************************************/

#define SPI_C1_DEFAULT          0x04						/*!< SPI C1 register */
#define SPI_C2_DEFAULT          0x00						/*!< SPI C2 register */
#define SPI_BR_DEFAULT          0x00						/*!< SPI BR register */
#define SPI_S_DEFAULT           0x20						/*!< SPI S register */
#define SPI_M_DEFAULT           0x00						/*!< SPI M register */
/*! @} End of spi_default_value                                                    					*/

/******************************************************************************
* define SPI error status
*
*//*! @addtogroup spi_error_list
* @{
*******************************************************************************/

#define     SPI_ERR_SUCCESS            0                                /*!< success */
#define     SPI_ERR_CODE_BASE         ((uint32)SPI0 - 0x40000000L)      /*!< error code base for SPI */
#define     SPI_ERR_TXBUF_NOT_EMPTY   (SPI_ERR_CODE_BASE+1)             /*!< failure due to SPTEF (empty) not set */
#define     SPI_ERR_RXBUF_NOT_FULL    (SPI_ERR_CODE_BASE+2)             /*!< failure due to SPRF (full) not set */
/*! @} End of spi_error_list                                            */
        
/******************************************************************************
* Types
******************************************************************************/

typedef uint8_t   SPI_WidthType;  /* SPI width type */
typedef uint32_t  ResultType;     /* SPI routine Result code */

/******************************************************************************
* define SPI call back funtion
*
*//*! @addtogroup spi_callback
* @{
*******************************************************************************/
typedef void (*SPI_CallbackType)(void);  /*!< SPI call back function */
/*! @} End of spi_callback                                            */

/******************************************************************************
*
*//*! @addtogroup spi_setting_type
* @{
*******************************************************************************/
/*!
 * @brief SPI setting type.
 *
 */
typedef struct
{
    uint32_t bIntEn                               : 1; /*!< 1: Interrupt Enable, 0: Interrupt disable */
    uint32_t bModuleEn                            : 1; /*!< 1: SPI module Enable, 0: SPI module disable */
    uint32_t bTxIntEn                             : 1; /*!< 1: Tx Interrupt Enable, 0: Tx Interrupt disable */
    uint32_t bMasterMode                          : 1; /*!< 1: Master mode, 0: Slave mode */
    uint32_t bClkPolarityLow                      : 1; /*!< 1: Active-low SPI clock, 0: Active-HIgh SPI clock */
    uint32_t bClkPhase1                           : 1; /*!< Set clock phase */
    uint32_t bMasterAutoDriveSS                   : 1; /*!< Slave select output enable */
    uint32_t bShiftLSBFirst                       : 1; /*!< 1: LSB first, 0: MSB first */
    uint32_t bMatchIntEn                          : 1; /*!< 1: Match interrupt Enable, 0: Match interrupt disable */
    uint32_t bModeFaultEn                         : 1; /*!< Master mode-fault function enable */
    uint32_t bBidirectionModeEn                   : 1; /*!< Bidirectional mode output enable */
    uint32_t bPinAsOuput                          : 1; /*!< enables bidirectional pin configurations */
    uint32_t bStopInWaitMode                      : 1; /*!< SPI stop in wait mode */
    uint32_t bRsvd                                : 19;
} SPI_SettingType;
/*! @} End of spi_setting_type                                            */

/******************************************************************************
*
*//*! @addtogroup spi_config_type
* @{
*******************************************************************************/
/*!
 * @brief SPI configuration type.
 *
 */
typedef struct 
{
    SPI_SettingType     sSettings;              /*!< SPI settings */
    uint32_t              u32BitRate;             /*!< set baud rate */
    uint32_t              u32BusClkHz;            /*!< input bus clock */
} SPI_ConfigType;                              /*!< SPI configuration structure */
/*! @} End of spi_config_type                                            */

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* inline function
******************************************************************************/
/******************************************************************************
*
*//*! @addtogroup spi_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief LSB first (shifter direction).
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetLSBFirst(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_LSBFE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief MSB first (shifter direction).
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetMSBFirst(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_LSBFE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief set SPI clock polarity.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   * @param[in]  u8PolLow   set clock polarity, 1 - Active-low SPI clock (idles high).  
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetClockPol(SPI_Type *pSPI,uint8_t u8PolLow)
{
	if( u8PolLow )
	{
		pSPI->C1 |= SPI_C1_CPOL_MASK;	
	}
	else
	{
		pSPI->C1 &= ~SPI_C1_CPOL_MASK;	
	}
}
/*****************************************************************************//*!
   *
   * @brief set SPI clock phase.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   * @param[in]  u8Phase   set clock phase, 1 - First edge on SPSCK occurs at the start of the first cycle of a data transfer. 
   * 
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetClockPhase(SPI_Type *pSPI,uint8_t u8Phase)
{
	if( u8Phase )
	{
		pSPI->C1 |= SPI_C1_CPHA_MASK;	
	}
	else
	{
		pSPI->C1 &= ~SPI_C1_CPHA_MASK;	
	}
}
/*****************************************************************************//*!
   *
   * @brief enable SPI module.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 __STATIC_INLINE void SPI_Enable(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_SPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief disable SPI module.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *  
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 __STATIC_INLINE void SPI_Disable(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_SPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief enable SPI interrupt.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 __STATIC_INLINE void SPI_IntEnable(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_SPIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief disable SPI interrupt.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_IntDisable(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_SPIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief set SPI to master mode.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_SetMasterMode(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_MSTR_MASK;
}
/*****************************************************************************//*!
   *
   * @brief set SPI to slave mode.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_SetSlaveMode(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_MSTR_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI transmit interrupt enable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE void SPI_TxIntEnable(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_SPTIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI transmit interrupt disable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_TxIntDisable(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_SPTIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Slave select output enable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_SSOutputEnable(SPI_Type *pSPI )
{
	pSPI->C1 |= SPI_C1_SSOE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Slave select output disable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_SSOutputDisable(SPI_Type *pSPI )
{
	pSPI->C1 &= ~SPI_C1_SSOE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI match interrupt enable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   * 
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_MatchIntEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_SPMIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI match interrupt disable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE void SPI_MatchIntDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_SPMIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Master mode-fault function disable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE void SPI_ModfDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_MODFEN_MASK;
}
/*****************************************************************************//*!

   *
   * @brief Master mode-fault function enable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE void SPI_ModfEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_MODFEN_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Bidirectional mode output enable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirOutEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_BIDIROE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief Bidirectional mode output disable.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirOutDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_BIDIROE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI stop in wait mode
   *        
   * @param[in]  pSPI   point to SPI module type.  
   * 
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE void SPI_ClockStopDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_SPISWAI_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI stop in wait mode.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *  
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_ClockStopEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_SPISWAI_MASK;
}
/*****************************************************************************//*!
   *
   * @brief enables bidirectional pin configurations.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *   
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirPinEnable(SPI_Type *pSPI)
{
	pSPI->C2 |= SPI_C2_SPC0_MASK;
}
/*****************************************************************************//*!
   *
   * @brief enables bidirectional pin configurations.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *   
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirPinDisable(SPI_Type *pSPI)
{
	pSPI->C2 &= ~SPI_C2_SPC0_MASK;
}
/*****************************************************************************//*!
   *
   * @brief check SPI read buffer full flag.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *    
   * @return  TRUE or FALSE.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsSPRF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_SPRF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check SPI match flag.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *    
   * @return  TRUE or FALSE.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsSPMF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_SPMF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check SPI transmit buffer empty flag.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *    
   * @return  TRUE or FALSE.
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsSPTEF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_SPTEF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief check master mode fault flag.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *    
   * @return  TRUE or FALSE.
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsMODF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_MODF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief read SPI data register.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *    
   * @return data register value
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_ReadDataReg(SPI_Type *pSPI )
{
	return pSPI->D;
}
/*****************************************************************************//*!
   *
   * @brief write SPI data register.
   *        
   * @param[in]  pSPI   point to SPI module type. 
   * @param[in]  u8WrBuff   data buffer write to spi data register. 
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_WriteDataReg(SPI_Type *pSPI, uint8_t u8WrBuff )
{
	pSPI->D = u8WrBuff;
}
/*****************************************************************************//*!
   *
   * @brief write SPI match  register.
   *        
   * @param[in]  pSPI   point to SPI module type. 
   * @param[in]  u8WrBuff   the data buffer write to match register. 
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_WriteMatchValue(SPI_Type *pSPI, uint8_t u8WrBuff )
{
	pSPI->M = u8WrBuff;
}
/******************************************************************************
* Global functions
******************************************************************************/
void SPI_Enable(SPI_Type *pSPI);
void SPI_Disable(SPI_Type *pSPI);
void SPI_SetLSBFirst(SPI_Type *pSPI);
void SPI_SetMSBFirst(SPI_Type *pSPI);
void SPI_IntEnable(SPI_Type *pSPI);
void SPI_IntDisable(SPI_Type *pSPI);
void SPI_SetMasterMode(SPI_Type *pSPI);
void SPI_SetSlaveMode(SPI_Type *pSPI);
void SPI_TxIntEnable(SPI_Type *pSPI);
void SPI_TxIntDisable(SPI_Type *pSPI);
void SPI_SSOutputEnable(SPI_Type *pSPI );
void SPI_SSOutputDisable(SPI_Type *pSPI );
void SPI_MatchIntEnable(SPI_Type *pSPI );
void SPI_MatchIntDisable(SPI_Type *pSPI );
void SPI_ModfDisable(SPI_Type *pSPI );
void SPI_ModfEnable(SPI_Type *pSPI );
void SPI_BidirOutEnable(SPI_Type *pSPI );
void SPI_BidirOutDisable(SPI_Type *pSPI );
void SPI_ClockStopDisable(SPI_Type *pSPI );
void SPI_ClockStopEnable(SPI_Type *pSPI );
void SPI_BidirPinEnable(SPI_Type *pSPI );
void SPI_BidirPinDisable(SPI_Type *pSPI );
void SPI_SetClockPol(SPI_Type *pSPI,uint8_t u8PolLow);
void SPI_SetClockPhase(SPI_Type *pSPI,uint8_t u8Phase);
void SPI_SetBaudRate(SPI_Type *pSPI,uint32_t u32BusClock,uint32_t u32Bps );
uint8_t SPI_IsSPRF(SPI_Type *pSPI );
uint8_t SPI_IsSPMF(SPI_Type *pSPI );
uint8_t SPI_IsSPTEF(SPI_Type *pSPI );
uint8_t SPI_IsMODF(SPI_Type *pSPI );
uint8_t SPI_ReadDataReg(SPI_Type *pSPI );
void SPI_WriteDataReg(SPI_Type *pSPI, uint8_t u8WrBuff );
void SPI_WriteMatchValue(SPI_Type *pSPI, uint8_t u8WrBuff );
void SPI_Init(SPI_Type *pSPI, SPI_ConfigType *pConfig);
void SPI_DeInit(SPI_Type *pSPI);
ResultType SPI_TransferWait(SPI_Type *pSPI, SPI_WidthType* pRdBuff, SPI_WidthType *pWrBuff,uint32 uiLength);
void SPI_SetCallback(SPI_Type *pSPI,SPI_CallbackType pfnCallback);

/*! @} End of spi_api_list                                            */
#ifdef __cplusplus
}
#endif
#endif /* SPI_H_ */
