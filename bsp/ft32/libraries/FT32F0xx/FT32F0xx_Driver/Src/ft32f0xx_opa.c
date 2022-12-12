/**
  ******************************************************************************
  * @file    			ft32f0xx_opa.c
  * @author  			FMD AE
  * @brief   			This file provides firmware functions to manage the following 
  *          			functionalities of the comparators (OPA1 and OPA2) peripheral
  *          			applicable only on FT32F030 devices: 
  *           		+ Comparators configuration
  *           		+ Window mode control
  * @version 			V1.0.0           
  * @data		 			2021-07-01
	******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_comp.h"
#include "ft32f0xx_opa.h"

/* CSR register Mask */
#define OPA_CR_CLEAR_MASK              ((uint32_t)0x0003FFC1)

/* Clear PRMAP BIT*/
#define	OPA_OP2_CLEAR_PRMAP				((uint32_t)0x00020000)         

/**
  * @brief  Deinitializes OPA peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the OPA configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAx: the selected comparator. 
  *         This parameter can be one of the following values:
  *         @arg OPA:  OPA1 selected
  *         @arg OPA2: OPA2 selected
  * @retval None
  */
void OPA_DeInit(OPA_TypeDef* OPAx)
{
    /* Check the parameters */
    assert_param(IS_OPA_ALL_PERIPH(OPAx)); 
	
    OPAx->CR = ((uint32_t)0x00000000);    /*!< Set OPA_CSR register to reset value */
}

/**
  * @brief  Initializes the OPA peripheral according to the specified parameters
  *         in OPA_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   To correctly run this function, the OPA_Cali() function must be called before.       
  * @param  OPAx: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg OPA:  OPA1 selected
  *            @arg OPA2: OPA2 selected
  * @param  OPA_InitStruct: pointer to an OPA_InitTypeDef structure that contains 
  *         the configuration information for the specified OPA peripheral.
  * @retval None
  */
void OPA_Init(OPA_TypeDef* OPAx, OPA_InitTypeDef* OPA_InitStruct)
{
	uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_OPA_VIP_SEL(OPA_InitStruct->OPA_OP0PSel));
	assert_param(IS_OPA_VIN_SEL(OPA_InitStruct->OPA_OP0NSel));
	assert_param(IS_OPA_FR_SEL(OPA_InitStruct->OPA_OP0FR));
	assert_param(IS_OPA_FCAP_SEL(OPA_InitStruct->OPA_OP0FCAPE));
	assert_param(IS_OPA_ODIG_SEL(OPA_InitStruct->OPA_OPTODIG));
	assert_param(IS_OPA_OIO_SEL(OPA_InitStruct->OPA_OPTOIO));

	/*!< Get the OPA_CR register value */
	tmpreg = OPAx->CR;

	/*!< Clear the bits */ 
	tmpreg &= (uint32_t) ~(OPA_CR_CLEAR_MASK);

	/*!< Configure OPA: OPA_VipSel, OPA_VinSel, OPA_OutputSel value and OPA_Pol */
	tmpreg |= (uint32_t)((OPA_InitStruct->OPA_OP0PSel | OPA_InitStruct->OPA_OP0NSel|
					   OPA_InitStruct->OPA_OP0FR | OPA_InitStruct->OPA_OP0FCAPE | OPA_InitStruct->OPA_OPTODIG |OPA_InitStruct->OPA_OPTOIO));

	/*!< Write to OPA_CR register */
	OPAx->CR = tmpreg;  
}

/**
  * @brief  Fills each OPA_InitStruct member with its default value.
  * @param  OPA_InitStruct: pointer to an OPA_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
{
	OPA_InitStruct->OPA_OP0PSel = 0x00000000;
	OPA_InitStruct->OPA_OP0NSel = 0x00002000;
	OPA_InitStruct->OPA_OP0FR = 0x00000000;
	OPA_InitStruct->OPA_OP0FCAPE = 0x00000000;
	OPA_InitStruct->OPA_OPTODIG = 0x00000080;
	OPA_InitStruct->OPA_OPTOIO = 0x00000040;
}

/**
  * @brief  Enable or disable the OPA peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAx: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg OPA: OPA1 selected
  *            @arg OPA2: OPA2 selected
  * @param  NewState: new state of the OPA peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the comparator compares the non inverting input with 
  *         the inverting input and the comparison result is available on comparator output.
  * @note   When disabled, the comparator doesn't perform comparison and the 
  *         output level is low.
  * @retval None
  */
void OPA_Cmd(OPA_TypeDef* OPAx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_OPA_ALL_PERIPH(OPAx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable the selected OPA peripheral */
		OPAx->CR |= OPA_OP1_ON;
	}
	else
	{
		/* Disable the selected OPA peripheral  */
		OPAx->CR &= ~OPA_OP1_ON;
	}
}

/**
  * @brief  Return the output level (high or low) of the selected comparator. 
  * @note   The output level depends on the selected polarity.
  * @note   If the polarity is not inverted:
  *          - Comparator output is low when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is high when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @note   If the polarity is inverted:
  *          - Comparator output is high when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is low when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @param  OPAx: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg OPA:  OPA1 selected
  *            @arg OPA2: OPA2 selected  
  * @param  OPA_OutLevel:  
  *          This parameter can be one of the following values:
  *            @arg OPA_OutputLevel_High
  *            @arg OPA_OutputLevel_Low   
  * @retval Returns the selected comparator output level: low or high.
  *       
  */
uint32_t OPA_GetOutputLevel(OPA_TypeDef* OPAx, uint32_t OPA_OutLevel)
{
	uint32_t compout = 0x0;

	/* Check the parameters */
	assert_param(IS_OPA_ALL_PERIPH(OPAx));
	assert_param(IS_OPA_OUTPUT_LEVEL(OPA_OutLevel));

	/* Check if selected comparator output is high */
	if ((OPAx->CR & OPA_OutLevel) != 0)
	{
		compout = OPA_OutLevel;
	}
	else
	{
		compout = OPA_OutputLevel_Low;
	}

	/* Return the comparator output level */
	return (uint32_t)(compout);
}

/**
  * @brief  Return the output level (high or low) of the selected comparator. 
  * @note   The output level depends on the selected polarity.
  * @param  OPAx: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg OPA:  OPA1 selected
  *            @arg OPA2: OPA2 selected 
  * @retval Returns:	0：fail		others：The calibration value 
  *       
  */
uint8_t OPA_Cali(OPA_TypeDef* OPAx)
{
	uint32_t    opadelay;
	uint32_t    outstate;
	uint8_t  	CalDA, CalDB;
	uint32_t	opatmp32;
	uint32_t	delay_time = 0x1fff;
	
	/* Check the parameters */
	assert_param(IS_OPA_ALL_PERIPH(OPAx));
  
	/* Enable the selected OPA peripheral */
	OPAx->CR |= OPA_OP1_ON;

	/* Enable OP0TM */
	OPAx->CR |= OPA_OP1_TM;

	/* OP0NSEL = 00   ,  SET TO GND */
	OPAx->CR &= ~OPA_OP1_NSEL;

	/* OP0PSEL = 1   ,  SET TO GND */
	OPAx->CR |= OPA_OP1_PSEL;

	/* OP0FCAPE = 0 */
	OPAx->CR &= ~OPA_OP1_FCAPE;

	/* OPTODIG = 1 */
	OPAx->CR |= OPA_OP1_TODIG;

	/* OP0FR = 000 */
	OPAx->CR &= ~OPA_OP1_FR;

	if (OPAx == OPA)
	{
		/* PA2 TO FLOAT */
		GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint32_t)2 * 2));	
	}
	else
	{
		/* Clear PRMAP */
		OPAx->CR &= (~OPA_OP2_CLEAR_PRMAP);
		
		/* PF4 TO FLOAT */
		GPIOF ->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint32_t)4 * 2));			
	}

	#if defined (FT32F072xB)
		/* OP0COF = 00000 */
		OPAx->CR &= ~OPA_OP1_COF;
		CalDA = 0;
		opadelay = delay_time;
		while(opadelay--);			
		outstate = OPAx->CR;		// save
		
		for(;;)
		{
			CalDA++;
			if(CalDA >= 0x1F) 
			return 0;				//fail
		
			opatmp32 = OPAx->CR & (~OPA_OP1_COF);
			OPAx->CR = opatmp32 | (CalDA << 1);
			opadelay = delay_time;
			while(opadelay--);
			
			if( (outstate ^ OPAx->CR) & OPA_OP1_OUT) 
			break;
		}

		OPAx->CR |= OPA_OP1_COF;		//0x1F
		CalDB = 0x1F;
		opadelay = delay_time;
		while(opadelay--);		
		outstate = OPAx->CR;		// save
		
		for(;;)
		{
			if(0 == CalDB) 
			return 0;
		
			CalDB--;
			opatmp32 = OPAx->CR & (~OPA_OP1_COF);
			OPAx->CR = opatmp32 | (CalDB << 1);
			opadelay = delay_time;
			while(opadelay--);
			
			if( (outstate ^ OPAx->CR) & OPA_OP1_OUT ) 
			break;
		}

		CalDA+= CalDB;
		CalDA/= 2;
		opatmp32 = OPAx->CR & (~OPA_OP1_COF);
		OPAx->CR = opatmp32 | (CalDA << 1);	
	#else
		/* OP0COF = 10000 */
		OPAx->CR &= ~OPA_OP1_COF;
		OPAx->CR |= OPA_OP1_COF_4;
		CalDA = 0;
		opadelay = delay_time;
		while(opadelay--);
		outstate = OPAx->CR;		// save
		
		for(;;)
		{
			CalDA++;
			if(CalDA >= 0x0F) 
			return 0;
		
			opatmp32 = OPAx->CR & (~OPA_OP1_COF);
			OPAx->CR = opatmp32 | (CalDA << 1);
			opadelay = delay_time;
			while(opadelay--);
			
			if((outstate^OPAx->CR) & OPA_OP1_OUT) 
			break;
		}
		
		OPAx->CR &= ~OPA_OP1_COF;		
		OPAx->CR |= OPA_OP1_COF_0 | OPA_OP1_COF_1 | OPA_OP1_COF_2 | OPA_OP1_COF_3;	//0x0F
		CalDB = 0x0F;
		opadelay = delay_time;
		while(opadelay--);		
		outstate = OPAx->CR;		// save

		for(;;)
		{
			if(0 == CalDB) 
			return 0;
		
			CalDB--;
			opatmp32 = OPAx->CR & (~OPA_OP1_COF);
			OPAx->CR = opatmp32 | (CalDB << 1);
			opadelay = delay_time;
			while(opadelay--);
			
			if( (outstate^OPAx->CR) & OPA_OP1_OUT ) 
			break;
		}

		CalDA+= CalDB;
		CalDA/= 2;
		opatmp32 = OPAx->CR & (~OPA_OP1_COF);
		OPAx->CR = opatmp32 | (CalDA << 1);			
	#endif

	return CalDA;
}







/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
