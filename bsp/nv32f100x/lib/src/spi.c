
/******************************************************************************
* @brief providing APIs for configuring SPI module (SPI). 
*
*******************************************************************************
*
* provide APIs for configuring SPI module (SPI).
******************************************************************************/
#include "common.h"
#include "spi.h"


/******************************************************************************
* Local variables
******************************************************************************/

SPI_CallbackType SPI_Callback[MAX_SPI_NO] = {(SPI_CallbackType)NULL};


/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local functions
*****************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* define SPI APIs
*
*//*! @addtogroup spi_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief initialize SPI as per params.
   *        
   * @param[in]  pSPI   point to SPI module type.
   * @param[in]  pConfig point to configuration parameters.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
void SPI_Init(SPI_Type *pSPI, SPI_ConfigType *pConfig)
{
#if defined(CPU_NV32M3)  
     /* sanity check */
    ASSERT((pSPI == SPI0));
    SIM->SCGC |= SIM_SCGC_SPI0_MASK;
#else
    /* sanity check */
    ASSERT((pSPI == SPI0) ||  (pSPI == SPI1));
    
    /* enable SPI clock gating on */
    if( pSPI == SPI0)
    {
        SIM->SCGC |= SIM_SCGC_SPI0_MASK;
    }
    else
    {
        SIM->SCGC |= SIM_SCGC_SPI1_MASK;     
    }
#endif
    /* configure other control bits */
    if( pConfig->sSettings.bIntEn)
    {
        SPI_IntEnable(pSPI);
#if defined(CPU_NV32M3)  
        NVIC_EnableIRQ(SPI0_IRQn);  
#else
        if( pSPI == SPI0 )
        {
			NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
			NVIC_EnableIRQ(SPI1_IRQn);
        }
#endif
    }

    if( pConfig->sSettings.bTxIntEn)
    {
        SPI_TxIntEnable(pSPI);
#if defined(CPU_NV32M3)  
        NVIC_EnableIRQ(SPI0_IRQn);  
#else
        if( pSPI == SPI0 )
        {
			NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
			NVIC_EnableIRQ(SPI1_IRQn);
        }
#endif
    }
    if( pConfig->sSettings.bMasterMode)
    {
        SPI_SetMasterMode(pSPI);
    }
    else
    {
		SPI_SetSlaveMode(pSPI);
    }

    if( pConfig->sSettings.bClkPolarityLow)
    {
    	SPI_SetClockPol(pSPI,1);
    }
    if( pConfig->sSettings.bClkPhase1)
    {
        SPI_SetClockPhase(pSPI,1);
    }else
	{	
     SPI_SetClockPhase(pSPI,0);
	}  
    if( pConfig->sSettings.bShiftLSBFirst)
    {
        SPI_SetLSBFirst(pSPI);
    }
    if( pConfig->sSettings.bMatchIntEn)
    {
        SPI_MatchIntEnable(pSPI);
    }
    if( pConfig->sSettings.bModeFaultEn)
    {
        SPI_ModfEnable(pSPI);
    }
    if( pConfig->sSettings.bMasterAutoDriveSS)
    {
        /* set both SSOE and MODFEN bits when auto drive slave SS is enabled */
        SPI_SSOutputEnable(pSPI);
        SPI_ModfEnable(pSPI);
    }    
 
    if( pConfig->sSettings.bPinAsOuput)
    {
        SPI_BidirPinEnable(pSPI);
    }

    if( pConfig->sSettings.bBidirectionModeEn)
    {
        SPI_BidirOutEnable(pSPI);
    }
    if( pConfig->sSettings.bStopInWaitMode)
    {
        SPI_ClockStopEnable(pSPI);
    }
    
    if(pConfig->sSettings.bMasterMode)
    {
        SPI_SetBaudRate(pSPI,pConfig->u32BusClkHz,pConfig->u32BitRate);
    }

	/* enable SPI module */
    if( pConfig->sSettings.bModuleEn)
    {
        SPI_Enable(pSPI);
    }
}

/*****************************************************************************//*!
   *
   * @brief SPI set band rate.
   *        
   * @param[in]  pSPI   point to SPI module type.
   * @param[in]  u32BusClock   Bus clock.
   * @param[in]  u32Bps   set spi's baudrate.
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
void SPI_SetBaudRate(SPI_Type *pSPI,uint32_t u32BusClock,uint32_t u32Bps)
{
	uint32_t u32BitRateDivisor;
	uint8_t u8Sppr;
	uint8_t u8Spr;
    uint8_t u8ReadFlag;
	u32BitRateDivisor = u32BusClock/u32Bps; /* calculate bit rate divisor */
       
    u8ReadFlag = 0;
    /* find best fit SPPR and SPR */
    for (u8Spr = 0; u8Spr <= 8; u8Spr++)
    {
        for(u8Sppr = 0; u8Sppr <= 7; u8Sppr++)
        {
            if((u32BitRateDivisor>>(u8Spr+1))<=(u8Sppr+1))
            {
                u8ReadFlag = 1;
                break;
            }
        }
        if(u8ReadFlag)
        {
            break;
        }
    }
    if(u8Sppr >=8)
    {
        u8Sppr = 7;
    }
    if(u8Spr >8)
    {
        u8Spr = 8;
    }
    /* set bit rate */
    pSPI->BR = SPI_BR_SPPR(u8Sppr) | SPI_BR_SPR(u8Spr);
}

/*****************************************************************************//*!
   *
   * @brief implement write data to SPI.
   *        
   * @param[in]   pSPI  pointer to SPI module type.
   * @param[in]   pWrBuff -- write data buffer pointer. 
   * @param[in]   uiLength -- read/write data length.
   * @param[out]   pRdBuff -- read data buffer pointer. 
   * 
   * @return  if <0, means error, 0: success.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
ResultType SPI_TransferWait(SPI_Type *pSPI, SPI_WidthType* pRdBuff, SPI_WidthType *pWrBuff,uint32 uiLength)
{
    ResultType err = SPI_ERR_SUCCESS;
    uint32_t  i;
    
    if(!uiLength)
    {
        return (err);
    }
    for(i = 0; i < uiLength; i++)
    {
        while(!SPI_IsSPTEF(pSPI));
        SPI_WriteDataReg(pSPI,pWrBuff[i]);
        while(!SPI_IsSPRF(pSPI));
        pRdBuff[i] = SPI_ReadDataReg(pSPI);
    }
    return (err);        
}



/*****************************************************************************//*!
   *
   * @brief Deinitialize SPI to the default state (reset value).
   *        
   * @param[in]   pSPI  pointer to SPI module type.
   *         
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
void SPI_DeInit(SPI_Type *pSPI)
{  
    int16 i;
    pSPI->C1 = SPI_C1_DEFAULT;
    pSPI->C2 = SPI_C2_DEFAULT;
    pSPI->BR = SPI_BR_DEFAULT;
    pSPI->M  = SPI_M_DEFAULT;
    for(i = 0; i<100; i++);                 /* wait for some cycles for the ISR exit */
}

/*****************************************************************************//*!
   *
   * @brief  set up SPI callback routines to be called by interrupt service routine.
   *        
   * @param[in]   pSPI  pointer to SPI module type.
   * @param[in]  pfnCallback  callback routine. 
   *  
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
*****************************************************************************/
void SPI_SetCallback(SPI_Type *pSPI,SPI_CallbackType pfnCallback)
{
    uint32_t    u32Port = ((uint32_t)pSPI-(uint32_t)SPI0)>>12;
    ASSERT(u32Port <2);
    SPI_Callback[u32Port] = pfnCallback;
}

/*! @} End of spi_api_list                                               						*/


/*****************************************************************************//*!
   *
   * @brief SPI0 interrupt service routine.
   *        
   * @param   none.
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/

void SPI0_Isr(void)
{
    if( SPI_Callback[0] )
    {
		SPI_Callback[0]();
    }
}
#ifndef CPU_NV32M3
/*****************************************************************************//*!
   *
   * @brief SPI1 interrupt service routine.
   *        
   * @param   none.
   * @return  none.
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

void SPI1_Isr(void)
{
    if( SPI_Callback[1] )
    {
		SPI_Callback[1]();
    }
}
#endif


