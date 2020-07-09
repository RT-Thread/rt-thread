/******************************************************************************
*
* @brief providing APIs for configuring KBI. 
*
*******************************************************************************
*
* provide APIs for configuring KBI
******************************************************************************/
#include "common.h"
#include "kbi.h"
/******************************************************************************
* External objects
******************************************************************************/

/******************************************************************************
* Global variables
******************************************************************************/
KBI_CallbackType KBI_Callback[KBI_MAX_NO] = {(KBI_CallbackType)NULL};

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
* KBI api list
*
*//*! @addtogroup kbi_api_list
* @{
*******************************************************************************/


/******************************************************************************
* Global functions
******************************************************************************/

/*****************************************************************************//*!
*
* @brief initialize KBI module.
*        
* @param[in]  pKBI        pointer to KBI module.
* @param[in]  pConfig     pointer to KBI configuration structure.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_DeInit.
*
*****************************************************************************/
void KBI_Init(KBI_Type *pKBI, KBI_ConfigType *pConfig)
{
#if defined(CPU_NV32)
    uint16_t    i;
    uint8_t     sc = 0;
    uint8_t     u8Port;
    uint8_t     u8PinPos;
    uint16_t    u16PinMapping[KBI_MAX_NO][8] = 
    {
        {
            0, 1, 2, 3, 8, 9, 10, 11           /* KBI0 pins position in GPIOA register */
        },
        {
            24, 25, 26, 27, 28, 29, 30, 31      /* KBI1 pins position in GPIOA register */
        }
    };
#elif defined(CPU_NV32M3)
    uint16_t    i;
    uint8_t     sc = 0;
    uint8_t     u8Port;
    uint8_t     u8PinPos;
    uint16_t    u16PinMapping[KBI_MAX_NO][8] = 
    {
        {
            0, 1, 2, 3, 8, 9, 10, 11           /* KBI0 pins position in GPIOA register */
        },
        {
            20, 21, 16, 17, 18, 19, 12, 13      /* KBI1 pins position in GPIOA register */
        }
    };
#elif defined(CPU_NV32M4)
     uint32_t    i;
     uint32_t     sc = 0;
     uint32_t     u8Port;
     uint32_t     u8PinPos;

     uint32_t    u16PinMapping[KBI_MAX_NO][KBI_MAX_PINS_PER_PORT] =
    {
        {/* KBI0P0~KBI0P31 pins position in GPIOA register */
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31           
        },
        {/* KBI1P0~KBI1P31 pins position in GPIOB register */
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31		   
        }
    };
#endif	 
 
    
    if(KBI0 == pKBI)
    {
        SIM->SCGC   |= SIM_SCGC_KBI0_MASK;             /* enable clock to KBI0 */\
        u8Port      =  0;
    }
    else if (KBI1 == pKBI)
    {        
        SIM->SCGC   |= SIM_SCGC_KBI1_MASK;             /* enable clock to KBI1 */
        u8Port      =  1;
    }
    
    /* mask keyboard interrupts first */
    sc          = pConfig->sBits.bMode;
    pKBI->SC    = sc;

    /* configure KBI pin polarity and others */
    for (i = 0; i < KBI_MAX_PINS_PER_PORT; i++)
    {
        if(pConfig->sPin[i].bEn)
        {
            pKBI->PE    |= (1<<i);                      /* enable this KBI pin */
            pKBI->ES    = (pKBI->ES & ~(1<<i)) | (pConfig->sPin[i].bEdge << i);     
            u8PinPos = u16PinMapping[u8Port][i];
            ASSERT(!(u8PinPos & 0x80));
		#if defined(CPU_NV32)|| defined(CPU_NV32M3)	
            FGPIOA->PIDR  &= ~(1<<u8PinPos);              /* enable GPIO input */     
            FGPIOA->PDDR  &= ~(1<<u8PinPos);              /* configure pin as input */  
            PORT->PUEL  |= (1<<u8PinPos);                 /* enable pullup for the pin */
        #elif defined(CPU_NV32M4)
		   if (u8Port == 0)   /* KBI0 */
           {
		   	FGPIOA->PIDR  &= ~(1<<u8PinPos);              /* enable GPIO input */    
            FGPIOA->PDDR  &= ~(1<<u8PinPos);              /* configure pin as input */ 
            PORT->PUE0  |= (1<<u8PinPos);                 /*enable pullup for the pin */
           }
		   else if (u8Port == 1)   /* KBI1 */
           {
		   	FGPIOB->PIDR  &= ~(1<<u8PinPos);              /* enable GPIO input */     
            FGPIOB->PDDR  &= ~(1<<u8PinPos);              /* configure pin as input */ 
            PORT->PUE1  |= (1<<u8PinPos);                 /*enable pullup for the pin */
           }
		#endif  
		}
    }
    
    #if defined(CPU_NV32M4)
    /*Reset KBI_SP register*/
	sc = pConfig->sBits.bRstKbsp<<KBI_SC_RSTKBSP_SHIFT;
	pKBI->SC    |= sc;
	
    /*Real KBI_SP register enable*/
	sc = pConfig->sBits.bKbspEn<<KBI_SC_KBSPEN_SHIFT;
	pKBI->SC    |= sc;
	#endif
  
	/* write to KBACK to clear any false interrupts */
    pKBI->SC    = sc;
    
    /* enable interrupt if needed */
    if(pConfig->sBits.bIntEn)
    {
        pKBI->SC    |=  KBI_SC_KBIE_MASK;
        
        if(KBI0 == pKBI)
        {
            NVIC_EnableIRQ(KBI0_IRQn);
        }
        else
        {
            NVIC_EnableIRQ(KBI1_IRQn);            
        }
    }
}

/*****************************************************************************//*!
*
* @brief set up KBI callback routine.
*        
* @param[in] pKBI          pointer to KBI module.
* @param[in] pfnCallback   pointer to callback routine.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void KBI_SetCallback(KBI_Type *pKBI, KBI_CallbackType pfnCallback)
{
    if(KBI0 == pKBI)
    {
        KBI_Callback[0] = pfnCallback;
    }
    else
    {
        KBI_Callback[1] = pfnCallback;        
    }
}

/*****************************************************************************//*!
*
* @brief deinit the kbi module.
*        
* @param[in]  pKBI       pointer to KBI module.
*         
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_Init.
*
*****************************************************************************/
void KBI_DeInit(KBI_Type *pKBI)
{
    if(KBI0 == pKBI)
    {
        NVIC_DisableIRQ(KBI0_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(KBI1_IRQn);        
    }
    
    pKBI->PE = 0;
    pKBI->SC = 0;
    pKBI->ES = 0;
    
    if(KBI0 == pKBI)
    {
        SIM->SCGC   &= ~SIM_SCGC_KBI0_MASK;             /* disable clock to KBI0 */
    }
    else
    {
        SIM->SCGC   &= ~SIM_SCGC_KBI1_MASK;             /* disable clock to KBI1 */       
    }
}

/*! @} End of acmp_api_list                                                  */

/*****************************************************************************//*!
*
* @brief button group 0 (KBI0) interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/

void KBI0_Isr(void)	
{
  KBI0->SC |= KBI_SC_KBACK_MASK;                        /* clear interrupt flag */

  if(KBI_Callback[0])
  {
      KBI_Callback[0]();
  }
}



/*****************************************************************************//*!
*
* @brief button group 0 (KBI0) interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/

void KBI1_Isr(void)	
{
  KBI1->SC |= KBI_SC_KBACK_MASK;                        /* clear interrupt flag */
 
  if(KBI_Callback[1])
  {
      KBI_Callback[1]();
  }
}

