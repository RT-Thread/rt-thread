
/******************************************************************************
*
* @brief providing APIs for system integration module (SIM). 
*
*******************************************************************************
*
* provide APIs for SIM
******************************************************************************/
#include "common.h"
#include "sim.h"

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local functions
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
   * @brief initialize SIM registers.
   * 
   * @param[in]  pConfig    pointer to SIM configuration.  
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see SIM_ConfigType
   *****************************************************************************/
void SIM_Init(SIM_ConfigType *pConfig)
{
    uint32_t    u32Sopt;
    uint32_t    u32PinSel;
    uint32_t    u32Scgc;
    uint32_t    u32BusDiv;
    /*
     * intialize the registers to reset default values
     */
    u32Sopt     = 0x0010000E;                 /* enable SWD, RESET, and NMI pins */
    u32PinSel   = 0;
    u32Scgc     = 0x00003000;           /* enable SWD and FLASH */
    u32BusDiv   = 0;
    u32BusDiv = pConfig->sBits.bBusDiv;
    if(pConfig->sBits.bDisableNMI)
    {
        u32Sopt &= ~SIM_SOPT_NMIE_MASK;        
    }
    if(pConfig->sBits.bDisableRESET)
    {
        u32Sopt &= ~SIM_SOPT_RSTPE_MASK;        
    }   
    if(pConfig->sBits.bDisableSWD)
    {
        u32Sopt &= ~SIM_SOPT_SWDE_MASK;        
    } 
    if(pConfig->sBits.bEnableCLKOUT)
    {
        u32Sopt |= SIM_SOPT_CLKOE_MASK;        
    } 
    if(pConfig->sBits.bETMSYNC)
    {
        u32Sopt |= SIM_SOPT_ETMSYNC_MASK;        
    }  
    if(pConfig->sBits.bRXDCE)
    {
        u32Sopt |= SIM_SOPT_RXDCE_MASK;        
    }
    if(pConfig->sBits.bTXDME)
    {
        u32Sopt |= SIM_SOPT_TXDME_MASK;        
    }
    if(pConfig->sBits.bACIC)
    {
        u32Sopt |= SIM_SOPT_ACIC_MASK;
    }
        if(pConfig->sBits.bRTCC)
    {
        u32Sopt |= SIM_SOPT_RTCC_MASK;        
    }
        if(pConfig->sBits.bRXDFE)
    {
        u32Sopt |= SIM_SOPT_RXDFE_MASK;        
    }
    u32Sopt |= ((pConfig->u8BusRef & 0x07) << 16);        
    u32Sopt |= ((pConfig->u8Delay) << 24);        
    u32Sopt |= ((pConfig->sBits.u8ADHWT & 0x03) << 8);
    u32PinSel = pConfig->u32PinSel;
    u32Scgc = pConfig->u32SCGC;   
    
/* write SIM registers */
    SIM->SOPT = u32Sopt;
    SIM->PINSEL = u32PinSel;
    SIM->SCGC = u32Scgc; 
    SIM->BUSDIV = u32BusDiv;
}
#elif defined(CPU_NV32M3)
/*****************************************************************************//*!
   *
   * @brief initialize SIM registers.
   * 
   * @param[in]  pConfig    pointer to SIM configuration.  
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see SIM_ConfigType
   *****************************************************************************/

void SIM_Init(SIM_ConfigType *pConfig)
{
    uint32_t    u32Sopt;
    uint32_t    u32PinSel;
    uint32_t    u32Scgc;
    uint32_t    u32ClockDiv;
    /*
     * intialize the registers to reset default values
     */
    u32Sopt     = 0x0010000E;                 /* enable SWD, RESET, and NMI pins */
    u32PinSel   = 0;
    u32Scgc     = 0x00003000;           /* enable SWD and FLASH */
    u32ClockDiv = 0;
    u32ClockDiv = pConfig->u32CLKDIV;
    if(pConfig->sBits.bDisableNMI)
    {
        u32Sopt &= ~SIM_SOPT_NMIE_MASK;        
    }
    if(pConfig->sBits.bDisableRESET)
    {
        u32Sopt &= ~SIM_SOPT_RSTPE_MASK;        
    }   
    if(pConfig->sBits.bDisableSWD)
    {
        u32Sopt &= ~SIM_SOPT_SWDE_MASK;        
    } 
    if(pConfig->sBits.bEnableCLKOUT)
    {
        u32Sopt |= SIM_SOPT_CLKOE_MASK;        
    } 
    if(pConfig->sBits.bETMSYNC)
    {
        u32Sopt |= SIM_SOPT_ETMSYNC_MASK;        
    }  
    if(pConfig->sBits.bRXDCE)
    {
        u32Sopt |= SIM_SOPT_RXDCE_MASK;        
    }
    if(pConfig->sBits.bTXDME)
    {
        u32Sopt |= SIM_SOPT_TXDME_MASK;        
    }
    if(pConfig->sBits.bACTRG)
    {
        u32Sopt |= SIM_SOPT_ACTRG_MASK;
    }
    u32Sopt |= ((pConfig->u8BusRef & 0x07) << 16);        
    u32Sopt |= ((pConfig->u8Delay) << 24);        
    u32Sopt |= ((pConfig->sBits.u8ADHWT & 0x07) << 20);
    u32Sopt |= ((pConfig->sBits.bRXDFE)&0x03<<8);
    u32Sopt |= ((pConfig->sBits.bETMIC)&0x03<<6);

    u32PinSel = pConfig->u32PinSel;
    u32Scgc = pConfig->u32SCGC;    
/* write SIM registers */
    SIM->SOPT = u32Sopt;
    SIM->PINSEL = u32PinSel;
    SIM->SCGC = u32Scgc;
    SIM->CLKDIV = u32ClockDiv;
}
#elif defined(CPU_NV32M4)
/*****************************************************************************//*!
   *
   * @brief initialize SIM registers.
   * 
   * @param[in]  pConfig    pointer to SIM configuration.  
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see SIM_ConfigType
   *****************************************************************************/
void SIM_Init(SIM_ConfigType *pConfig)
{
    uint32_t    u32Sopt;
    uint32_t    u32PinSel;
    uint32_t    u32Scgc;
    uint32_t    u32ClockDiv;
    /*
     * intialize the registers to reset default values
     */
    u32Sopt     = 0x0E;                 /* enable SWD, RESET, and NMI pins */
    u32PinSel   = 0;
    u32Scgc     = 0x00003000;           /* enable SWD and FLASH */
    u32ClockDiv = 0;
    u32ClockDiv = pConfig->u32CLKDIV;
    if(pConfig->sBits.bDisableNMI)
    {
        u32Sopt &= ~SIM_SOPT0_NMIE_MASK;        
    }
    if(pConfig->sBits.bDisableRESET)
    {
        u32Sopt &= ~SIM_SOPT0_RSTPE_MASK;        
    }   
    if(pConfig->sBits.bDisableSWD)
    {
        u32Sopt &= ~SIM_SOPT0_SWDE_MASK;        
    } 
    if(pConfig->sBits.bEnableCLKOUT)
    {
        u32Sopt |= SIM_SOPT0_CLKOE_MASK;        
    } 
    if(pConfig->sBits.bETMSYNC)
    {
        u32Sopt |= SIM_SOPT0_ETMSYNC_MASK;        
    }  
    if(pConfig->sBits.bRXDCE)
    {
        u32Sopt |= SIM_SOPT0_RXDCE_MASK;        
    }
    if(pConfig->sBits.bTXDME)
    {
        u32Sopt |= SIM_SOPT0_TXDME_MASK;        
    }
    if(pConfig->sBits.bACTRG)
    {
        u32Sopt |= SIM_SOPT0_ACTRG_MASK;
    }
    u32Sopt |= ((pConfig->u8BusRef & 0x07) << 16);        
    u32Sopt |= ((pConfig->u8Delay) << 24);        
    u32Sopt |= ((pConfig->sBits.u8ADHWT & 0x07) << 20);
    u32Sopt |= ((pConfig->sBits.bRXDFE)&0x03<<8);
    //u32Sopt |= ((pConfig->sBits.bETMIC)&0x03<<6);

    u32PinSel = pConfig->u32PinSel;
    u32Scgc = pConfig->u32SCGC;    
/* write SIM registers */
    SIM->SOPT0 = u32Sopt;
    SIM->PINSEL = u32PinSel;
    SIM->SCGC = u32Scgc;
    SIM->CLKDIV = u32ClockDiv;
}
#endif

/*****************************************************************************//*!
   *
   * @brief set SIM clock gating registers to enable or disable peripheral clocks.
   * 
   * @param[in]  u32PeripheralMask    peripherial bits mask.  
   * @param[in]  u8GateOn             1: ON, 0: OFF.  
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

void SIM_SetClockGating(uint32_t u32PeripheralMask, uint8_t u8GateOn)
{
    uint32_t    u32Scgc;

    /*
     * save original clock gating value
     */
    u32Scgc     = SIM->SCGC;
    
    if(u8GateOn)
    {
        u32Scgc |= u32PeripheralMask;
    }
    else
    {
        u32Scgc &= ~u32PeripheralMask;        
    }

    SIM->SCGC = u32Scgc;
}


/*****************************************************************************//*!
   *
   * @brief read the corresponding status flags.
   * 
   * @param[in]  u32StatusMask    indicates which status to be read. 
   *
   * @return status.
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
uint32_t SIM_GetStatus(uint32_t u32StatusMask)
{
    uint32_t    u32Status;

    u32Status = SIM->SRSID & u32StatusMask;
    return (u32Status);
}

/*****************************************************************************//*!
   *
   * @brief read the corresponding ID.
   * 
   * @param[in]  u8ID    type of ID. 
   *
   * @return ID
   *
   * @ Pass/ Fail criteria: none.
   * @see   IDType.
   *****************************************************************************/
uint8_t SIM_ReadID(IDType sID)
{
    uint32_t    u32ID;
    uint8_t u8IDOffset[4] = 
    { 
        28, 24, 20,16
    };  
    u32ID = (SIM->SRSID >> u8IDOffset[sID]) & 0x0F;
    return (u32ID);
}
/*! @} End of sim_api_list                                                    */



