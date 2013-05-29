/** @file sys_selftest.c 
*   @brief Selftest Source File
*   @date 29.May.2013
*   @version 03.05.02
*
*   This file contains:
*   - Selftest API's
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "sys_selftest.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void ccmSelfCheck(void)
*   @brief CCM module self check Driver
*
*   This function self checks the CCM module.
*/
void ccmSelfCheck(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

	/* Run a diagnostic check on the CCM-R4F module */
	/* This step ensures that the CCM-R4F can actually indicate an error */

	/* Configure CCM in self-test mode */
	CCMKEYR = 0x6U;								
	/* Wait for CCM self-test to complete */
	while ((CCMSR & 0x100U) != 0x100U)
	{ 
	}/* Wait */ 		

/* USER CODE BEGIN (3) */
/* USER CODE END */
	
	/* Check if there was an error during the self-test */
	if ((CCMSR & 0x1U) == 0x1U)
	{
		/* STE is set */
		ccmFail(0U);								
	}
	else
	{
		/* Check CCM-R4 self-test error flag by itself (without compare error) */
		if ((esmREG->ESTATUS1[0U] & 0x80000000U) != 0x80000000U)
		{
			/* ESM flag is not set */
			ccmFail(1U);						
		}
		else
		{
			/* clear ESM group1 channel 31 flag */
			esmREG->ESTATUS1[0U] = 0x80000000U;	
			
			/* Configure CCM in error-forcing mode */
			CCMKEYR = 0x9U;
			
            /* check if compare error flag is set */
			if ((esmREG->ESTATUS1[1U] & 0x4U) != 0x4U)
			{
				/* ESM flag is not set */
				ccmFail(2U);
			}
			else
			{
		        /* Check FIQIVEC to ESM High Interrupt flag is set */ 
				if((vimREG->FIQINDEX & 0x000000FFU) != 1U)
				{
				   /* ESM High Interrupt flag is not set in VIM*/
				   ccmFail(3U);				
				}
				/* clear ESM group2 channel 2 flag */ 
				esmREG->ESTATUS1[1U] = 0x4U;
				
				/* clear ESM group2 shadow status flag */
				esmREG->ESTATUS5EMU = 0x4U;				
				
				/* ESM self-test error needs to also be cleared */
				esmREG->ESTATUS1[0U] = 0x80000000U;		
				
				/* Clear CCM-R4 CMPE flag */
				CCMSR = 0x00010000U;

				/* Return CCM-R4 to lock-step mode */
				CCMKEYR = 0x0U;
				
				/* The nERROR pin will become inactive once the LTC counter expires */
				esmREG->KEY = 0x5U;	
			}
		}
	}
}

/* USER CODE BEGIN (4) */
/* USER CODE END */

/** @fn void ccmFail(uint32 x)
*   @brief CCM module fail service routine
*
*   This function is called if CCM module selftest fail.
*/
void ccmFail(uint32 x)
{
/* USER CODE BEGIN (5) */
/* USER CODE END */
	if (x == 0U)
	{
		/* CCM-R4 is not able to flag a compare error in self-test mode.
		 * Lock-step operation cannot be verified.
		 */
/* USER CODE BEGIN (6) */
/* USER CODE END */
	}
	else if (x == 1U)
	{
		/* CCM-R4 self-test error flag is not set in ESM register.
		 * Could be due to a connection issue inside the part.
		 */
/* USER CODE BEGIN (7) */
/* USER CODE END */
	}
	else if (x == 2U)
	{
		/* CCM-R4 compare error flag is not set in ESM.
		 * Lock-step operation cannot be verified.
		 */
/* USER CODE BEGIN (8) */
/* USER CODE END */
	}
	else if (x == 3U)
	{
		/* ESM High Interrupt Flag is not set in VIM.
		 */
/* USER CODE BEGIN (9) */
/* USER CODE END */
	}	
	else
	{
		/*  */
/* USER CODE BEGIN (10) */
/* USER CODE END */
	}	
}

/** @fn void memoryInit(uint32 ram)
*   @brief Memory Initialization Driver
*
*   This function is called to perform Memory initialization of selected RAM's.
*/
void memoryInit(uint32 ram)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

	/* Enable Memory Hardware Initialization */
	systemREG1->MINITGCR = 0xAU;	
	
    /* Enable Memory Hardware Initialization for selected RAM's */
	systemREG1->MSINENA  = ram;
    
	/* Wait until Memory Hardware Initialization complete */
	while((systemREG1->MSTCGSTAT & 0x00000100U) != 0x00000100U)
	{ 
	}/* Wait */ 		
	
	/* Disable Memory Hardware Initialization */
	systemREG1->MINITGCR = 0x5U;	
	
/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/** @fn void stcSelfCheck(void)
*   @brief STC module self check Driver
*
*   This function is called to perform STC module self check.
*/
void stcSelfCheck(void)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */
	volatile uint32 i = 0U;

	/* Run a diagnostic check on the CPU self-test controller */
	/* First set up the STC clock divider as STC is only supported up to 90MHz */
	
	/* STC clock is now normal mode CPU clock frequency/2 = 180MHz/2 */
	systemREG2->STCCLKDIV = 0x01000000U;	
	
	/* Select one test interval, restart self-test next time, 0x00010001 */
	stcREG->STCGCR0 = 0x00010001U;						
	
	/* Enable comparator self-check and stuck-at-0 fault insertion in CPU, 0x1A */
	stcREG->STCSCSCR = 0x1AU;							
	
	/* Maximum time-out period */
	stcREG->STCTPR = 0xFFFFFFFFU;						

	/* wait for 16 VBUS clock cycles at least, based on HCLK to VCLK ratio */
	for (i=0U; i<(16U + (16U * 1U)); i++){ /* Wait */ }								

	/* Enable self-test */
	stcREG->STCGCR1 = 0xAU;								
	
	/* wait for 16 VBUS clock cycles at least, based on HCLK to VCLK ratio */
	for (i=0U; i<(16U + (16U * 1U)); i++){ /* Wait */ }	

/* USER CODE BEGIN (14) */
/* USER CODE END */
	
	/* Idle the CPU so that the self-test can start */
	_gotoCPUIdle_();

/* USER CODE BEGIN (15) */
/* USER CODE END */
}

/** @fn void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test)
*   @brief CPU self test Driver
*   @param[in] no_of_intervals - Number of Test Intervals to be 
*   @param[in] max_timeout     - Maximum Timeout to complete selected test Intervals
*   @param[in] restart_test    - Restart the test from Interval 0 or Continue from where it stopped.
*
*   This function is called to perform CPU self test using STC module.
*/
void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test)
{
	volatile uint32 i = 0U;

/* USER CODE BEGIN (16) */
/* USER CODE END */
	
	/* Run specified no of test intervals starting from interval 0 */
	/* Start test from interval 0 or continue the test. */ 
	stcREG->STCGCR0 = (no_of_intervals << 16U)
	                | (uint32) restart_test;						
	
	/* Configure Maximum time-out period */
	stcREG->STCTPR = max_timeout;						
	
	/* wait for 16 VBUS clock cycles at least, based on HCLK to VCLK ratio */
	for (i=0U; i<(16U + (16U * 1U)); i++){ /* Wait */ }								

	/* Enable self-test */
	stcREG->STCGCR1 = 0xAU;								

/* USER CODE BEGIN (17) */
/* USER CODE END */
	/* Idle the CPU so that the self-test can start */
	
	_gotoCPUIdle_();
	
}

/** @fn void pbistSelfCheck(void)
*   @brief PBIST self test Driver
*
*   This function is called to perform PBIST self test.
*/
void pbistSelfCheck(void)
{
	volatile uint32 i = 0U;
/* USER CODE BEGIN (18) */
/* USER CODE END */
	/* Run a diagnostic check on the memory self-test controller */
	/* First set up the PBIST ROM clock as this clock frequency is limited to 90MHz */
	
	/* PBIST ROM clock frequency = HCLK frequency /2 */
	systemREG1->MSTGCR |= 0x00000100U;				
	
	/* Enable PBIST controller */
	systemREG1->MSINENA = 0x1U;							
	
	/* clear MSTGENA field */
	systemREG1->MSTGCR &= ~(0xFU);						
	
	/* Enable PBIST self-test */
	systemREG1->MSTGCR |= 0xAU;							
	
	/* wait for 32 VBUS clock cycles at least, based on HCLK to VCLK ratio */
	for (i=0U; i<(32U + (32U * 1U)); i++){ /* Wait */ }								

/* USER CODE BEGIN (19) */
/* USER CODE END */
	
	/* Enable PBIST clocks and ROM clock */
	pbistREG->PACT = 0x3U;								
	
	/* Select algo#3, march13n to be run */
	pbistREG->ALGO = 0x00000004U;						
	
	/* Select RAM Group 1, which is actually the PBIST ROM */
	pbistREG->RINFOL = 0x1U;								
	
	/* ROM contents will not override ALGO and RINFOx settings */
	pbistREG->OVER = 0x0U;								
	
	/* Algorithm code is loaded from ROM */
	pbistREG->ROM = 0x3U;								
	
	/* Start PBIST */
	pbistREG->DLR = 0x14U;								
	
	/* wait until memory self-test done is indicated */
	while ((systemREG1->MSTCGSTAT & 0x1U) != 0x1U)
	{ 
	}/* Wait */ 				
	
	/* Check for the failure */
	if (((pbistREG->FSRF0 & 0x1U) != 0x1U) & ((pbistREG->FSRF1 & 0x1U) != 0x1U))
	{
		/* no failure was indicated even if the march13n algorithm was run on a ROM */
		pbistSelfCheckFail();
/* USER CODE BEGIN (20) */
/* USER CODE END */
	}
	else												
	{
	    /* PBIST self-check has passed */
		
		/* Disable PBIST clocks and ROM clock */
		pbistREG->PACT = 0x0U;							
		
		/* Disable PBIST */
		systemREG1->MSTGCR &= ~(0xFU);					
		systemREG1->MSTGCR |= 0x5U;
		
/* USER CODE BEGIN (21) */
/* USER CODE END */
    }
}

/** @fn void pbistSelfCheckFail(void)
*   @brief PBIST self test Driver failure service routine
*
*   This function is called on PBIST self test failure.
*/
void pbistSelfCheckFail(void)
{
	/* The PBIST controller is not capable of reporting a failure.
	 * PBIST cannot be used to verify memory integrity.
	 * Need custom handler here.
	 */
/* USER CODE BEGIN (22) */
/* USER CODE END */
}

/** @fn void pbistRun(uint32 raminfoL, uint32 algomask)
*   @brief CPU self test Driver
*   @param[in] raminfoL   - Select the list of RAM to be tested.
*   @param[in] algomask   - Select the list of Algorithm to be run.
*
*   This function performs Memory Built-in Self test using PBIST module.
*/
void pbistRun(uint32 raminfoL, uint32 algomask)
{
	volatile uint32 i = 0U;

/* USER CODE BEGIN (23) */
/* USER CODE END */

	/* PBIST ROM clock frequency = HCLK frequency /2 */
	systemREG1->MSTGCR |= 0x00000100U;					
	
	/* Enable PBIST controller */
	systemREG1->MSINENA = 0x1U;							 
	
	/* clear MSTGENA field */
	systemREG1->MSTGCR &= ~(0xFU);						 
	
	/* Enable PBIST self-test */
	systemREG1->MSTGCR |= 0xAU;							 
	
	/* wait for 32 VBUS clock cycles at least, based on HCLK to VCLK ratio */
	for (i=0U; i<(32U + (32U * 1U)); i++){ /* Wait */ }							 

/* USER CODE BEGIN (24) */
/* USER CODE END */
	
	/* Enable PBIST clocks and ROM clock */
	pbistREG->PACT = 0x3U;								 
	
	/* Select all algorithms to be tested */
	pbistREG->ALGO = algomask;						     
	
	/* Select RAM groups */
	pbistREG->RINFOL = raminfoL;						 
	
	/* Select all RAM groups */
	pbistREG->RINFOU = 0x00000000U;						
	
	/* ROM contents will not override RINFOx settings */
	pbistREG->OVER = 0x0U;								 
	
	/* Algorithm code is loaded from ROM */
	pbistREG->ROM = 0x3U;								 
	
	/* Start PBIST */
	pbistREG->DLR = 0x14U;								 

/* USER CODE BEGIN (25) */
/* USER CODE END */
}

/** @fn void pbistStop(void)
*   @brief Routine to stop PBIST test enabled.
*
*   This function is called to stop PBIST after test is performed.
*/
void pbistStop(void)
{
/* USER CODE BEGIN (26) */
/* USER CODE END */
    /* disable pbist clocks and ROM clock */
	pbistREG->PACT = 0x0U;							
	systemREG1->MSTGCR &= ~(0xFU);
	systemREG1->MSTGCR |= 0x5U;
/* USER CODE BEGIN (27) */
/* USER CODE END */
}

/** @fn boolean pbistIsTestCompleted(void)
*   @brief Checks to see if the PBIST test is completed.
*   @return 1 if PBIST test completed, otherwise 0.
*
*   Checks to see if the PBIST test is completed.
*/
boolean pbistIsTestCompleted(void)
{
/* USER CODE BEGIN (28) */
/* USER CODE END */

	return ((systemREG1->MSTCGSTAT & 0x1U) != 0U);
/* USER CODE BEGIN (29) */
/* USER CODE END */
}

/** @fn boolean pbistIsTestPassed(void)
*   @brief Checks to see if the PBIST test is completed successfully.
*   @return 1 if PBIST test passed, otherwise 0.
*
*   Checks to see if the PBIST test is completed successfully.
*/
boolean pbistIsTestPassed(void)
{
/* USER CODE BEGIN (30) */
/* USER CODE END */

	return (((pbistREG->FSRF0 ==0U) && (pbistREG->FSRF1 ==0U)) == TRUE);
/* USER CODE BEGIN (31) */
/* USER CODE END */
}

/** @fn boolean pbistPortTestStatus(uint32 port)
*   @brief Checks to see if the PBIST Port test is completed successfully.
*   @param[in] port   - Select the port to get the status.
*   @return 1 if PBIST Port test completed successfully, otherwise 0.
*
*   Checks to see if the selected PBIST Port test is completed successfully.
*/
boolean pbistPortTestStatus(uint32 port)
{
    boolean status;
/* USER CODE BEGIN (32) */
/* USER CODE END */

    if(port == PBIST_PORT0)
	{
	  status =  ((boolean)pbistREG->FSRF0 == 0U);
	}
	else
	{
	  status =  ((boolean)pbistREG->FSRF1 == 0U);	
	}
	
	return  status;
}

/** @fn void efcCheck(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFSUE module.
*/
void efcCheck(void)
{
	uint32 efcStatus = 0U;

/* USER CODE BEGIN (33) */
/* USER CODE END */
	
	/* read the EFC Error Status Register */
	efcStatus = efcREG->ERROR;						

/* USER CODE BEGIN (34) */
/* USER CODE END */
	
	if (efcStatus == 0x0U)
	{
	    /* run stuck-at-zero test and check if it passed */
		if (efcStuckZeroTest()== TRUE)						
		{
		    /* start EFC ECC logic self-test */
			efcSelfTest();							
		}
		else
		{
		    /* EFC output is stuck-at-zero, device operation unreliable */
			efcClass2Error();						
		}
	}
	/* EFC Error Register is not zero */
	else											
	{
		/* one-bit error detected during autoload */
		if (efcStatus == 0x15U)						
		{
		    /* start EFC ECC logic self-test */
			efcSelfTest();							
		}
		else
		{
		    /* Some other EFC error was detected */
		    efcClass2Error();					
		}
	}
}

/** @fn boolean efcStuckZeroTest(void)
*   @brief Checks to see if the EFUSE Stuck at zero test is completed successfully.
*   @return 1 if EFUSE Stuck at zero test completed, otherwise 0.
*
*   Checks to see if the EFUSE Stuck at zero test is completed successfully.
*/
boolean efcStuckZeroTest(void)
{
/* USER CODE BEGIN (35) */
/* USER CODE END */

	boolean result = FALSE;
  	uint32 error_checks = EFC_INSTRUCTION_INFO_EN  | 
							  	EFC_INSTRUCTION_ERROR_EN | 
							  	EFC_AUTOLOAD_ERROR_EN 	 | 
							  	EFC_SELF_TEST_ERROR_EN   ;
	
	/* configure the output enable for auto load error , instruction info,
  	   instruction error, and self test error using boundary register 
  	   and drive values one across all the errors */
  	efcREG->BOUNDARY = (OUTPUT_ENABLE | error_checks);
  	
	/* Read from the pin register. This register holds the current values 
  	   of above errors. This value should be 0x5c00.If not at least one of
  	   the above errors is stuck at 0. */
	if ((efcREG->PINS & 0x5C00U) == 0x5C00U)
	{
		/* check if the ESM group1 channels 40 is set and group3 channel 2 is set */
		if (((esmREG->ESTATUS4[0U] & 0x200U) == 0x200U) & ((esmREG->ESTATUS1[2U] & 0x2U) == 0x2U))
		{
           /* stuck-at-zero test passed */
		   result = TRUE;									
		}
	}
	
	/* put the pins back low */
	efcREG->BOUNDARY = OUTPUT_ENABLE;
	
	/* clear group1 flags */
	esmREG->ESTATUS4[0U] = 0x300U;
	
	/* clear group3 flag */
	esmREG->ESTATUS1[2U] = 0x2U;					
	
	/* The nERROR pin will become inactive once the LTC counter expires */
	esmREG->KEY = 0x5U;							

	return result;
}

/** @fn void efcSelfTest(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFSUE module.
*/
void efcSelfTest(void)
{
/* USER CODE BEGIN (36) */
/* USER CODE END */
	/* configure self-test cycles */
	efcREG->SELF_TEST_CYCLES = 0x258U;
	
	/* configure self-test signature */
	efcREG->SELF_TEST_SIGN = 0x5362F97FU;
	
	/* configure boundary register to start ECC self-test */
	efcREG->BOUNDARY = 0x0000200FU;
}

/** @fn boolean checkefcSelfTest(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFSUE module.
*/
boolean checkefcSelfTest(void)
{
/* USER CODE BEGIN (37) */
/* USER CODE END */
	boolean result = FALSE;
	
	/* wait until EFC self-test is done */
	while((!(efcREG->PINS & EFC_SELF_TEST_DONE)) != 0U)
	{ 
	}/* Wait */ 		
	
	/* check if EFC self-test error occurred */
	if (((!(efcREG->PINS & EFC_SELF_TEST_ERROR)) & (!(efcREG->ERROR & SELF_TEST_ERROR))) !=0U)
	{
		/* check if EFC self-test error is set */
		if ((esmREG->ESTATUS4[0U] & 0x100U) != 0x100U)		
		{
			result = TRUE;
		}
	}
	return result;
}

/** @fn void efcClass1Error(void)
*   @brief EFUSE Class1 Error service routine
*
*   This function is called if EFC ECC logic self-test.
*/
void efcClass1Error(void)
{
/* USER CODE BEGIN (38) */
/* USER CODE END */
	/* Autoload error was detected during device power-up, and device operation is not reliable. */
	/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (39) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (40) */
/* USER CODE END */
}

/** @fn void efcClass2Error(void)
*   @brief EFUSE Class2 Error service routine
*
*   This function is called if EFC output is stuck-at-zero.
*/
void efcClass2Error(void)
{
/* USER CODE BEGIN (41) */
/* USER CODE END */
	/* The ECC logic inside the eFuse controller is not operational. Device operation is not reliable. */
	/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (42) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (43) */
/* USER CODE END */
}

/** @fn void fmcBus2Check(void)
*   @brief Self Check Flash Bus2 Interface
*
*   This function self checks Flash Bus2 Interface
*/
void fmcBus2Check(void)
{
/* USER CODE BEGIN (44) */
/* USER CODE END */
    /* enable ECC logic inside FMC */
	flashWREG->FEDACCTRL1 = 0x000A060AU;		

	if ((esmREG->ESTATUS1[0U] & 0x40U) == 0x40U)
	{
		/* a 1-bit error was detected during flash OTP read by flash module
		   run a self-check on ECC logic inside FMC */
		
		/* clear ESM group1 channel 6 flag */
		esmREG->ESTATUS1[0U] = 0x40U;	
		
		fmcECCcheck();
	}
	
	/* no 2-bit or 1-bit error detected during power-up */
	else										
	{
		fmcECCcheck();
	}
/* USER CODE BEGIN (45) */
/* USER CODE END */
}

/** @fn void fmcECCcheck(void)
*   @brief Check Flash ECC Single Bit and multi Bit errors detection logic.
*
*   This function Checks Flash ECC Single Bit and multi Bit errors detection logic.
*/
void fmcECCcheck(void)
{
	volatile uint32 otpread;
	volatile uint32 temp;

/* USER CODE BEGIN (46) */
/* USER CODE END */

	/* read location with deliberate 1-bit error */
	otpread = flash1bitError;				
	if ((esmREG->ESTATUS1[0U] & 0x40U) == 0x40U)
	{
		/* 1-bit failure was indicated and corrected */
		flashWREG->FEDACSTATUS = 0x00010006U;
		
		/* clear ESM group1 channel 6 flag */
		esmREG->ESTATUS1[0U] = 0x40U;			
		
        /* read location with deliberate 2-bit error */
		otpread = flash2bitError;			
		if ((esmREG->ESTATUS1[2U] & 0x80U) == 0x80U)
		{
			/* 2-bit failure was detected correctly */
			temp = flashWREG->FUNCERRADD;
			flashWREG->FEDACSTATUS = 0x00020100U;
			
			/* clear ESM group3 channel 7 */
			esmREG->ESTATUS1[2U] = 0x80U;		
			
			/* The nERROR pin will become inactive once the LTC counter expires */
			esmREG->KEY = 0x5U;				

		}
		else
		{
		    /* ECC logic inside FMC cannot detect 2-bit error */
			fmcClass2Error();				
		}
	}
	else
	{
	    /* ECC logic inside FMC cannot detect 1-bit error */
		fmcClass2Error();					
	}
/* USER CODE BEGIN (47) */
/* USER CODE END */
}

/** @fn void fmcClass1Error(void)
*   @brief Flash Multi bit ECC error service routine detected during reset configuration.
*
*   This function is called if Flash Multi bit ECC error detected during reset configuration.
*/
void fmcClass1Error(void)
{
/* USER CODE BEGIN (48) */
/* USER CODE END */
	/* there was a multi-bit error detected during the reset configuration word read from the OTP */
	/* This affects the device power domains, endianness, and exception handling ISA */
	/* Device operation is not reliable. */
    /* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (49) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (50) */
/* USER CODE END */
}

/** @fn void fmcClass2Error(void)
*   @brief Flash OTP or EEPROM read Multi bit ECC error service routine
*
*   This function is called if Flash OTP or EEPROM read Multi bit ECC error detected.
*/
void fmcClass2Error(void)
{
/* USER CODE BEGIN (51) */
/* USER CODE END */
	/* The ECC logic inside FMC used to protect against 1-bit and 2-bit errors in OTP and EEPROM banks */
	/* is not operational. Device operation is not reliable. */
	/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (52) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (53) */
/* USER CODE END */
}

/** @fn void checkB0RAMECC(void)
*   @brief Check TCRAM1 ECC error detection logic.
*
*   This function checks TCRAM1 ECC error detection logic.
*/
void checkB0RAMECC(void)
{
	volatile uint32 ramread = 0U;
    volatile uint32 i;
/* USER CODE BEGIN (54) */
/* USER CODE END */

	/* enable writes to ECC RAM, enable ECC error response */
	tcram1REG->RAMCTRL = 0x0005010AU;			
	tcram2REG->RAMCTRL = 0x0005010AU;

	/* the first 1-bit error will cause an error response */
	tcram1REG->RAMTHRESHOLD = 0x1U;				
	tcram2REG->RAMTHRESHOLD = 0x1U;

	/* allow SERR to be reported to ESM */
	tcram1REG->RAMINTCTRL = 0x1U;				
	tcram2REG->RAMINTCTRL = 0x1U;
    
	/* cause a 1-bit ECC error */
	tcramA1bitError ^= 0x1U;		
	
	/* disable writes to ECC RAM */
	tcram1REG->RAMCTRL = 0x0005000AU;			
	tcram2REG->RAMCTRL = 0x0005000AU;

	/* read from location with 1-bit ECC error */
	ramread = tcramA1bit;		
	
	/* SERR not set in TCRAM1 or TCRAM2 modules */
	if ((!(((tcram1REG->RAMERRSTATUS & 1U) == 1U) || ((tcram2REG->RAMERRSTATUS & 1U) == 1U))) !=0U)	
	{
		/* TCRAM module does not reflect 1-bit error reported by CPU */
		tcramClass2Error();						
	}
	else
	{
	    /* clear SERR flag */
		tcram1REG->RAMERRSTATUS = 0x1U;			
		tcram2REG->RAMERRSTATUS = 0x1U;
		
		/* clear status flags for ESM group1 channels 26 and 28 */
		esmREG->ESTATUS1[0U] = 0x14000000U;		
	}

	/* enable writes to ECC RAM, enable ECC error response */
	tcram1REG->RAMCTRL = 0x0005010AU;			
	tcram2REG->RAMCTRL = 0x0005010AU;

	/* cause a 2-bit ECC error */
	tcramA2bitError ^= 0x3U;						
	ramread = tcram1REG->RAMCTRL;
	ramread = tcram2REG->RAMCTRL;

	/* read from location with 2-bit ECC error this will cause a data abort to be generated */
	ramread = tcramA2bit;

    /* delay before restoring the ram value */
	for(i=0U;i<10U;i++)
	{ 
	}/* Wait */ 		   

	/* disable RAM ECC Support */
	_coreDisableRamEcc_();	
	
	/* enable writes to ECC RAM, enable ECC error response */
	tcram1REG->RAMCTRL = 0x0005010AU;			
	tcram2REG->RAMCTRL = 0x0005010AU;

	/* revert back the flipped bits */
	tcramA1bitError ^= 0x1U;	    
	tcramA2bitError ^= 0x3U;						
	
	/* disable writes to ECC RAM */
	tcram1REG->RAMCTRL = 0x0005000AU;			
	tcram2REG->RAMCTRL = 0x0005000AU;

	/* enable RAM ECC Support */
	_coreEnableRamEcc_();
	
/* USER CODE BEGIN (55) */
/* USER CODE END */
}

/** @fn void checkB1RAMECC(void)
*   @brief Check TCRAM2 ECC error detection logic.
*
*   This function checks TCRAM2 ECC error detection logic.
*/
void checkB1RAMECC(void)
{
	volatile uint32 ramread = 0U;
	volatile uint32 i;
/* USER CODE BEGIN (56) */
/* USER CODE END */

	/* enable writes to ECC RAM, enable ECC error response */
	tcram1REG->RAMCTRL = 0x0005010AU;			
	tcram2REG->RAMCTRL = 0x0005010AU;
    
	/* the first 1-bit error will cause an error response */
	tcram1REG->RAMTHRESHOLD = 0x1U;				
	tcram2REG->RAMTHRESHOLD = 0x1U;

	/* allow SERR to be reported to ESM */
	tcram1REG->RAMINTCTRL = 0x1U;				 
	tcram2REG->RAMINTCTRL = 0x1U;

	/* cause a 1-bit ECC error */
	tcramB1bitError ^= 0x1U;						 
	
	/* disable writes to ECC RAM */
	tcram1REG->RAMCTRL = 0x0005000AU;			 
	tcram2REG->RAMCTRL = 0x0005000AU;

	/* read from location with 1-bit ECC error */
	ramread = tcramB1bit;						 
	
	/* SERR not set in TCRAM1 or TCRAM2 modules */
	if ((!(((tcram1REG->RAMERRSTATUS & 1U) == 1U) || ((tcram2REG->RAMERRSTATUS & 1U) == 1U))) !=0U)	
	{
		/* TCRAM module does not reflect 1-bit error reported by CPU */
		tcramClass2Error();						
	}
	else
	{
		/* clear SERR flag */
		tcram1REG->RAMERRSTATUS = 0x1U;			 
		tcram2REG->RAMERRSTATUS = 0x1U;
		
		/* clear status flags for ESM group1 channels 26 and 28 */
		esmREG->ESTATUS1[0U] = 0x14000000U;		 
	}

	/* enable writes to ECC RAM, enable ECC error response */
	tcram1REG->RAMCTRL = 0x0005010AU;			 
	tcram2REG->RAMCTRL = 0x0005010AU;
	
	/* cause a 2-bit ECC error */
	tcramB2bitError ^= 0x3U;						 
	
	/* disable writes to ECC RAM */
	tcram1REG->RAMCTRL = 0x0005000AU;			 
	tcram2REG->RAMCTRL = 0x0005000AU;
	
    /* delay before restoring the ram value */
	for(i=0U;i<10U;i++)
	{ 
	}/* Wait */ 		   

	/* disable RAM ECC Support */
	_coreDisableRamEcc_();	

    /* enable writes to ECC RAM, enable ECC error response */
	tcram1REG->RAMCTRL = 0x0005010AU;			 
	tcram2REG->RAMCTRL = 0x0005010AU;

	/* revert back the flipped bits */
	tcramB1bitError ^= 0x1U;	    
	tcramB2bitError ^= 0x3U;						
	
	/* disable writes to ECC RAM */
	tcram1REG->RAMCTRL = 0x0005000AU;			 
	tcram2REG->RAMCTRL = 0x0005000AU;

	/* enable RAM ECC Support */
	_coreEnableRamEcc_();	

/* USER CODE BEGIN (57) */
/* USER CODE END */
}

/** @fn void tcramClass1Error(void)
*   @brief Error service routine called if TCRAM module cannot capture 2-bit error.
*
*   Error service routine called if TCRAM module cannot respond to 2-bit error.
*/
void tcramClass1Error(void)
{
/* USER CODE BEGIN (58) */
/* USER CODE END */
	/* TCRAM module is not capable of responding to 2-bit error indicated by CPU.
	 * Device operation is not reliable and not recommended.
	 */
	/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */ 
/* USER CODE BEGIN (59) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (60) */
/* USER CODE END */
}

/** @fn void tcramClass2Error(void)
*   @brief Error service routine called if TCRAM module cannot capture 1-bit error.
*
*   Error service routine called if TCRAM module cannot respond to 1-bit error.
*/
void tcramClass2Error(void)
{
/* USER CODE BEGIN (61) */
/* USER CODE END */
	/* TCRAM module is not capable of responding to 1-bit error indicated by CPU.
	 * Device operation is possible, but is prone to future multi-bit errors not being detected.
	 * Need custom handler here instead of the infinite loop.
	 */
	 /* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
	 
/* USER CODE BEGIN (62) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (63) */
/* USER CODE END */
}

/** @fn void checkFlashECC(void)
*   @brief Check Flash ECC error detection logic.
*
*   This function checks Flash ECC error detection logic.
*/
void checkFlashECC(void)
{
	/* Routine to check operation of ECC logic inside CPU for accesses to program flash */
	volatile uint32 flashread = 0U;

/* USER CODE BEGIN (64) */
/* USER CODE END */
	
	/* Flash Module ECC Response enabled */
	flashWREG->FEDACCTRL1 = 0x000A060AU;			
    
	/* Enable diagnostic mode and select diag mode 7 */
	flashWREG->FDIAGCTRL = 0x00050007U;			
	
	/* Select ECC diagnostic mode, single-bit to be corrupted */
	flashWREG->FPAROVR = 0x00005A01U;			
	
	/* Set the trigger for the diagnostic mode */
	flashWREG->FDIAGCTRL |= 0x01000000U;			
    
	/* read a flash location from the mirrored memory map */
	flashread = flashBadECC;	
	
	/* disable diagnostic mode */
	flashWREG->FDIAGCTRL = 0x000A0007U;			

	/* this will have caused a single-bit error to be generated and corrected by CPU */
	/* single-bit error not captured in flash module */
	if ((!(flashWREG->FEDACSTATUS & 0x2U)) !=0U)		
	{
		flashClass2Error();
	}
	else
	{
        /* clear single-bit error flag */
		flashWREG->FEDACSTATUS = 0x2U;				

		/* clear ESM flag */
		esmREG->ESTATUS1[0U] = 0x40U;					

		/* Enable diagnostic mode and select diag mode 7 */
		flashWREG->FDIAGCTRL = 0x00050007U;			
		
		/* Select ECC diagnostic mode, two bits of ECC to be corrupted */
		flashWREG->FPAROVR = 0x00005A03U;			
		
		/* Set the trigger for the diagnostic mode */
		flashWREG->FDIAGCTRL |= 0x01000000U;			

		/* read from flash location from mirrored memory map this will cause a data abort */
		flashread = flashBadECC;

		/* disable diagnostic mode */
		flashWREG->FDIAGCTRL = 0x000A0007U;			
	}

/* USER CODE BEGIN (65) */
/* USER CODE END */
}

/** @fn void flashClass1Error(void)
*   @brief Error service routine called if Flash module cannot capture 2-bit error.
*
*   Error service routine called if Flash module cannot capture 2-bit error.
*/
void flashClass1Error(void)
{
/* USER CODE BEGIN (66) */
/* USER CODE END */
	/* Flash module not able to capture 2-bit error from CPU.
	 * Device operation not reliable.
	 */
	/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (67) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (68) */
/* USER CODE END */

}

/** @fn void flashClass2Error(void)
*   @brief Error service routine called if Flash module cannot capture 1-bit error.
*
*   Error service routine called if Flash module cannot capture 1-bit error.
*/
void flashClass2Error(void)
{
	/* Flash module not able to capture 1-bit error from CPU.
	 * Device operation possible if this weakness in diagnostic is okay.
	 */
/* USER CODE BEGIN (69) */
/* USER CODE END */
}

/** @fn void custom_dabort(void)
*   @brief Custom Data abort routine for the application.
*
*   Custom Data abort routine for the application.
*/
void custom_dabort(void)
{
	/* Need custom data abort handler here.
	 * This data abort is not caused due to diagnostic checks of flash and TCRAM ECC logic.
	 */
/* USER CODE BEGIN (70) */
/* USER CODE END */
}

/** @fn void stcSelfCheckFail(void)
*   @brief STC Self test check fail service routine
*
*   This function is called if STC Self test check fail.
*/
void stcSelfCheckFail(void)
{
/* USER CODE BEGIN (71) */
/* USER CODE END */
	/* CPU self-test controller's own self-test failed.
	 * It is not possible to verify that STC is capable of indicating a CPU self-test error.
	 * It is not recommended to continue operation.
	 */
	 
	/* User can add small piece of code to take system to Safe state using user code section.
	 * Note: Just removing the for(;;) will take the system to unknown state under ST failure,
     * since it is not handled by HALCogen driver */
/* USER CODE BEGIN (72) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (73) */
/* USER CODE END */
}

/** @fn void cpuSelfTestFail(void)
*   @brief CPU Self test check fail service routine
*
*   This function is called if CPU Self test check fail.
*/
void cpuSelfTestFail(void)
{
/* USER CODE BEGIN (74) */
/* USER CODE END */
	/* CPU self-test has failed.
	 * CPU operation is not reliable.
	 */
	/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (75) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (76) */
/* USER CODE END */
}


/** @fn void vimParityCheck(void)
*   @brief Routine to check VIM RAM parity error detection and signaling mechanism
*
*   Routine to check VIM RAM parity error detection and signaling mechanism
*/
void vimParityCheck(void)
{
	volatile uint32 vimramread = 0U;

/* USER CODE BEGIN (77) */
/* USER CODE END */
	
	/* Enable parity checking and parity test mode */
	VIM_PARCTL = 0x0000010AU;
	
	/* flip a bit in the VIM RAM parity location */
	VIMRAMPARLOC ^= 0x1U;					
	
	/* disable parity test mode */
	VIM_PARCTL = 0x0000000AU;				

	/* cause parity error */
	vimramread = VIMRAMLOC;					
   
    /* check if ESM group1 channel 15 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x8000U))	!=0U)
	{
		/* VIM RAM parity error was not flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop. */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (78) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (79) */
/* USER CODE END */

	}
	else
	{
	    /* clear VIM RAM parity error flag in VIM */
		VIM_PARFLG = 0x1U;					
		
		/* clear ESM group1 channel 15 flag */
		esmREG->ESTATUS1[0U] = 0x8000U;		
		
		/* Enable parity checking and parity test mode */
		VIM_PARCTL = 0x0000010AU;
	
		/* Revert back to correct data, flip bit 0 of the parity location */
		VIMRAMPARLOC ^= 0x1U;					
	
		/* disable parity test mode */
		VIM_PARCTL = 0x0000000AU;		
	}
/* USER CODE BEGIN (80) */
/* USER CODE END */
}

/** @fn void dmaParityCheck(void)
*   @brief Routine to check DMA control packet RAM parity error detection and signaling mechanism
*
*   Routine to check DMA control packet RAM parity error detection and signaling mechanism
*/
void dmaParityCheck(void)
{
	volatile uint32 dmaread = 0U;

/* USER CODE BEGIN (81) */
/* USER CODE END */
	
	/* Enable parity checking and parity test mode */
	DMA_PARCR = 0x0000010AU;			
	
	/* Flip a bit in DMA RAM parity location */
	DMARAMPARLOC ^= 0x1U;					
	
	/* Disable parity test mode */
	DMA_PARCR = 0x0000000AU;					
    
	/* Cause parity error */
	dmaread = DMARAMLOC;					
    
	/* Check if ESM group1 channel 3 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x8U)) != 0U)		
	{
		/* DMA RAM parity error was not flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop. */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (82) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (83) */
/* USER CODE END */
	}
	else
	{
		/* clear DMA parity error flag in DMA */
		DMA_PARADDR = 0x01000000U;			
		
		/* clear ESM group1 channel 3 flag */
		esmREG->ESTATUS1[0U] = 0x8U;	

		/* Enable parity checking and parity test mode */
		DMA_PARCR = 0x0000010AU;			
	
		/* Revert back to correct data, flip bit 0 of the parity location */
		DMARAMPARLOC ^= 0x1U;					
	
		/* Disable parity test mode */
		DMA_PARCR = 0x0000000AU;		
	}
/* USER CODE BEGIN (84) */
/* USER CODE END */
}

/** @fn void het1ParityCheck(void)
*   @brief Routine to check HET1 RAM parity error detection and signaling mechanism
*
*   Routine to check HET1 RAM parity error detection and signaling mechanism
*/
void het1ParityCheck(void)
{
	volatile uint32 nhetread = 0U;

/* USER CODE BEGIN (85) */
/* USER CODE END */
	
	/* Set TEST mode and enable parity checking */
	hetREG1->PCR = 0x0000010AU;			
	
	/* flip parity bit */
	NHET1RAMPARLOC ^= 0x1U;					
	
	/* Disable TEST mode */
	hetREG1->PCR = 0x0000000AU;			

	/* read to cause parity error */
	nhetread = NHET1RAMLOC;					

	/* check if ESM group1 channel 7 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x80U)) !=0U)
	{
		/* NHET1 RAM parity error was not flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop. */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (86) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (87) */
/* USER CODE END */
	}
	else
	{
	    /* clear ESM group1 channel 7 flag */
		esmREG->ESTATUS1[0U] = 0x80U;	

		/* Set TEST mode and enable parity checking */
		hetREG1->PCR = 0x0000010AU;			
	
		/* Revert back to correct data, flip bit 0 of the parity location */
		NHET1RAMPARLOC ^= 0x1U;					
	
		/* Disable TEST mode */
		hetREG1->PCR = 0x0000000AU;			
	}
/* USER CODE BEGIN (88) */
/* USER CODE END */
}

/** @fn void htu1ParityCheck(void)
*   @brief Routine to check HTU1 RAM parity error detection and signaling mechanism
*
*   Routine to check HTU1 RAM parity error detection and signaling mechanism
*/
void htu1ParityCheck(void)
{
	volatile uint32 hturead = 0U;

/* USER CODE BEGIN (89) */
/* USER CODE END */

    /* Enable parity and TEST mode */
	htuREG1->PCR = 0x0000010AU;	
	
	/* flip parity bit */	
	HTU1PARLOC ^= 0x1U;			
	
	/* Disable parity RAM test mode */
	htuREG1->PCR = 0x0000000AU;	
	
	/* read to cause parity error */
	hturead = HTU1RAMLOC;		
   
    /* check if ESM group1 channel 8 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x100U)) != 0U)		 
	{
		/* HTU1 RAM parity error was not flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop. */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (90) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (91) */
/* USER CODE END */
	}
	else
	{
	    /* Clear HTU parity error flag */
		htuREG1->PAR = 0x00010000U;			
		esmREG->ESTATUS1[0U] = 0x100U;

		/* Enable parity and TEST mode */
		htuREG1->PCR = 0x0000010AU;	
	
		/* Revert back to correct data, flip bit 0 of the parity location */
		HTU1PARLOC ^= 0x1U;			
	
		/* Disable parity RAM test mode */
		htuREG1->PCR = 0x0000000AU;	
		
	}

/* USER CODE BEGIN (92) */
/* USER CODE END */

}

/** @fn void het2ParityCheck(void)
*   @brief Routine to check HET2 RAM parity error detection and signaling mechanism
*
*   Routine to check HET2 RAM parity error detection and signaling mechanism
*/
void het2ParityCheck(void)
{
	volatile uint32 nhetread = 0U;

/* USER CODE BEGIN (93) */
/* USER CODE END */
    
	/* Set TEST mode and enable parity checking */
	hetREG2->PCR = 0x0000010AU;			
	
	/* flip parity bit */
	NHET2RAMPARLOC ^= 0x1U;					
	
	/* Disable TEST mode */
	hetREG2->PCR = 0x0000000AU;			

	/* read to cause parity error */
	nhetread = NHET2RAMLOC;					

	/* check if ESM group1 channel 7 or 34 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x80U) != 0U) && (!(esmREG->ESTATUS4[0U] & 0x4U) !=0U))		
	{
		/* NHET2 RAM parity error was not flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop. */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (94) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (95) */
/* USER CODE END */
	}
	else
	{
	    /* clear ESM group1 channel 7 flag */
		esmREG->ESTATUS1[0U] = 0x80U;			
		
		/* clear ESM group1 channel 34 flag */
		esmREG->ESTATUS4[0U] = 0x4U;	

		/* Set TEST mode and enable parity checking */
		hetREG2->PCR = 0x0000010AU;			
	
		/* Revert back to correct data, flip bit 0 of the parity location */
		NHET2RAMPARLOC ^= 0x1U;					
	
		/* Disable TEST mode */
		hetREG2->PCR = 0x0000000AU;			
	}
	
/* USER CODE BEGIN (96) */
/* USER CODE END */
}

/** @fn void htu2ParityCheck(void)
*   @brief Routine to check HTU2 RAM parity error detection and signaling mechanism
*
*   Routine to check HTU2 RAM parity error detection and signaling mechanism
*/
void htu2ParityCheck(void)
{
	volatile uint32 hturead = 0U;

/* USER CODE BEGIN (97) */
/* USER CODE END */
	
	/* Enable parity and TEST mode */
	htuREG2->PCR = 0x0000010AU;		
	
	/* flip parity bit */
	HTU2PARLOC ^= 0x1U;						
	
	/* Disable parity RAM test mode */
	htuREG2->PCR = 0x0000000AU;				

	/* read to cause parity error */
	hturead = HTU2RAMLOC;					

	/* check if ESM group1 channel 8 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x100U)) != 0U)		
	{
		/* HTU2 RAM parity error was not flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop. */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (98) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (99) */
/* USER CODE END */
	}
	else
	{
	    /* Clear HTU parity error flag */
		htuREG2->PAR = 0x00010000U;			
		esmREG->ESTATUS1[0U] = 0x100U;
		
		/* Enable parity and TEST mode */
		htuREG2->PCR = 0x0000010AU;		
	
		/* Revert back to correct data, flip bit 0 of the parity location */
		HTU2PARLOC ^= 0x1U;						
	
		/* Disable parity RAM test mode */
		htuREG2->PCR = 0x0000000AU;				
	}
	
/* USER CODE BEGIN (100) */
/* USER CODE END */
}

/** @fn void adc1ParityCheck(void)
*   @brief Routine to check ADC1 RAM parity error detection and signaling mechanism
*
*   Routine to check ADC1 RAM parity error detection and signaling mechanism
*/
void adc1ParityCheck(void)
{
	volatile uint32 adcramread = 0U;

/* USER CODE BEGIN (101) */
/* USER CODE END */
	
	/* Set the TEST bit in the PARCR and enable parity checking */
	adcREG1->PARCR = 0x10AU;				
	
	/* Invert the parity bits inside the ADC1 RAM's first location */
	adcPARRAM1 = ~(adcPARRAM1);				

	/* clear the TEST bit */
	adcREG1->PARCR = 0x00AU;				

	/* This read is expected to trigger a parity error */
	adcramread = adcRAM1;					

	/* Check for ESM group1 channel 19 to be flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x80000U)) !=0U)	
	{
		/* no ADC1 RAM parity error was flagged to ESM */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (102) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (103) */
/* USER CODE END */
	}
	else
	{
	    /* clear ADC1 RAM parity error flag */
		esmREG->ESTATUS1[0U] = 0x80000U;	

		/* Set the TEST bit in the PARCR and enable parity checking */
		adcREG1->PARCR = 0x10AU;				
	
		/* Revert back the parity bits to correct data */
		adcPARRAM1 = ~(adcPARRAM1);				

		/* clear the TEST bit */
		adcREG1->PARCR = 0x00AU;			
	}
	
/* USER CODE BEGIN (104) */
/* USER CODE END */
}

/** @fn void adc2ParityCheck(void)
*   @brief Routine to check ADC2 RAM parity error detection and signaling mechanism
*
*   Routine to check ADC2 RAM parity error detection and signaling mechanism
*/
void adc2ParityCheck(void)
{
	volatile uint32 adcramread = 0U;

/* USER CODE BEGIN (105) */
/* USER CODE END */
	
	/* Set the TEST bit in the PARCR and enable parity checking */
	adcREG2->PARCR = 0x10AU;				
	
	/* Invert the parity bits inside the ADC2 RAM's first location */
	adcPARRAM2 = ~(adcPARRAM2);				

	/* clear the TEST bit */
	adcREG2->PARCR = 0x00AU;				

	/* This read is expected to trigger a parity error */
	adcramread = adcRAM2;					

	/* Check for ESM group1 channel 1 to be flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x2U)) != 0U)		
	{
		/* no ADC2 RAM parity error was flagged to ESM */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (106) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (107) */
/* USER CODE END */
	}
	else
	{
        /* clear ADC2 RAM parity error flag */	
		esmREG->ESTATUS1[0U] = 0x2U;	

		/* Set the TEST bit in the PARCR and enable parity checking */
		adcREG2->PARCR = 0x10AU;				
	
		/* Revert back the parity bits to correct data */
		adcPARRAM2 = ~(adcPARRAM2);				

		/* clear the TEST bit */
		adcREG2->PARCR = 0x00AU;			
	}
	
/* USER CODE BEGIN (108) */
/* USER CODE END */
}

/** @fn void can1ParityCheck(void)
*   @brief Routine to check CAN1 RAM parity error detection and signaling mechanism
*
*   Routine to check CAN1 RAM parity error detection and signaling mechanism
*/
void can1ParityCheck(void)
{
	volatile uint32 canread = 0U;

/* USER CODE BEGIN (109) */
/* USER CODE END */
	
	/* Disable parity, init mode, TEST mode */
	canREG1->CTL = 0x00001481U;				
	
	/* Enable RAM Direct Access mode */
	canREG1->TEST = 0x00000200U;			

	/* flip the parity bit */
	canPARRAM1 ^= 0x00001000U;				

	/* Enable parity, disable init, still TEST mode */
	canREG1->CTL = 0x00002880U;				

	/* Read location with parity error */
	canread = canRAM1;					

	/* check if ESM group1 channel 21 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x00200000U))	!= 0U)
	{
		/* No DCAN1 RAM parity error was flagged to ESM */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (110) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (111) */
/* USER CODE END */
	}
	else
	{
	    /* clear ESM group1 channel 21 flag */
		esmREG->ESTATUS1[0U] = 0x00200000U;	
		
		/* Disable parity, init mode, TEST mode */
		canREG1->CTL = 0x00001481U;

		/* Enable RAM Direct Access mode */
		canREG1->TEST = 0x00000200U;

		/* Revert back to correct data, flip bit 0 of the parity location */
		canPARRAM1 ^= 0x00001000U;
		
		/* disable TEST mode */
		canREG1->CTL = 0x00002800U;			
	}
	
/* USER CODE BEGIN (112) */
/* USER CODE END */
}

/** @fn void can2ParityCheck(void)
*   @brief Routine to check CAN2 RAM parity error detection and signaling mechanism
*
*   Routine to check CAN2 RAM parity error detection and signaling mechanism
*/
void can2ParityCheck(void)
{
	volatile uint32 canread = 0U;

/* USER CODE BEGIN (113) */
/* USER CODE END */
	
	/* Disable parity, init mode, TEST mode */
	canREG2->CTL = 0x00001481U;			

	/* Enable RAM Direct Access mode */	
	canREG2->TEST = 0x00000200U;			

	/* flip the parity bit */
	canPARRAM2 ^= 0x00001000U;				

	/* Enable parity, disable init, still TEST mode */
	canREG2->CTL = 0x00002880U;				

	/* Read location with parity error */
	canread = canRAM2;					
	
	/* check if ESM group1 channel 23 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x00800000U)) != 0U)	
	{
		/* No DCAN2 RAM parity error was flagged to ESM */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (114) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (115) */
/* USER CODE END */
	}
	else
	{
	    /* clear ESM group1 channel 23 flag */
		esmREG->ESTATUS1[0U] = 0x00800000U;	

		/* Disable parity, init mode, TEST mode */
		canREG2->CTL = 0x00001481U;			

		/* Enable RAM Direct Access mode */	
		canREG2->TEST = 0x00000200U;			

		/* Revert back to correct data, flip bit 0 of the parity location */
		canPARRAM2 ^= 0x00001000U;				
		
		/* disable TEST mode */
		canREG2->CTL = 0x00002800U;			
	}
	
/* USER CODE BEGIN (116) */
/* USER CODE END */
}

/** @fn void can3ParityCheck(void)
*   @brief Routine to check CAN3 RAM parity error detection and signaling mechanism
*
*   Routine to check CAN3 RAM parity error detection and signaling mechanism
*/
void can3ParityCheck(void)
{
	volatile uint32 canread = 0U;

/* USER CODE BEGIN (117) */
/* USER CODE END */
	
	/* Disable parity, init mode, TEST mode */
	canREG3->CTL = 0x00001481U;			

    /* Enable RAM Direct Access mode */	
	canREG3->TEST = 0x00000200U;			

	/* flip the parity bit */
	canPARRAM3 ^= 0x00001000U;				

	/* Enable parity, disable init, still TEST mode */
	canREG3->CTL = 0x00002880U;				

	/* Read location with parity error */
	canread = canRAM3;					

	/* check if ESM group1 channel 22 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x00400000U)) != 0U)	
	{
		/* No DCAN3 RAM parity error was flagged to ESM */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (118) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (119) */
/* USER CODE END */
	}
	else
	{
	    /* clear ESM group1 channel 22 flag */
		esmREG->ESTATUS1[0U] = 0x00400000U;	

		/* Disable parity, init mode, TEST mode */
		canREG3->CTL = 0x00001481U;			

		/* Enable RAM Direct Access mode */	
		canREG3->TEST = 0x00000200U;			

		/* Revert back to correct data, flip bit 0 of the parity location */
		canPARRAM3 ^= 0x00001000U;				
		
		/* disable TEST mode */
		canREG3->CTL = 0x00002800U;			
	}
	
/* USER CODE BEGIN (120) */
/* USER CODE END */
}

/** @fn void mibspi1ParityCheck(void)
*   @brief Routine to check MIBSPI1 RAM parity error detection and signaling mechanism
*
*   Routine to check MIBSPI1 RAM parity error detection and signaling mechanism
*/
void mibspi1ParityCheck(void)
{
	volatile uint32 spiread = 0U;

/* USER CODE BEGIN (121) */
/* USER CODE END */

	/* enable multi-buffered mode */
	mibspiREG1->MIBSPIE = 0x1U;				

	/* enable parity error detection */
    mibspiREG1->UERRCTRL = (mibspiREG1->UERRCTRL & 0xFFFFFFF0U) | (0xAU);
	
	/* enable parity test mode */
	mibspiREG1->UERRCTRL |= 1U << 8U;				
	
	/* flip bit 0 of the parity location */
	mibspiPARRAM1 ^= 0x1U;					

	/* disable parity test mode */
	mibspiREG1->UERRCTRL &= ~(1U << 8U);				

	/* read from MibSPI1 RAM to cause parity error */
	spiread = *(uint32 *) mibspiRAM1;	

	/* check if ESM group1 channel 17 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x20000U))	!= 0U)
	{
		/* No MibSPI1 RAM parity error was flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (122) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (123) */
/* USER CODE END */
	}
	else
	{
	    /* clear parity error flags */
		mibspiREG1->UERRSTAT = 0x3U;			
		
		/* clear ESM group1 channel 17 flag */
		esmREG->ESTATUS1[0U] = 0x20000U;		
		
		/* enable parity test mode */
	    mibspiREG1->UERRCTRL |= 1U << 8U;			
		
		/* Revert back to correct data, flip bit 0 of the parity location */
	    mibspiPARRAM1 ^= 0x1U;				
		
		/* disable parity test mode */
	    mibspiREG1->UERRCTRL &= ~(1U << 8U);	

    	/* revert multi-buffered mode */
	    mibspiREG1->MIBSPIE = 0x0U;			
	}

/* USER CODE BEGIN (124) */
/* USER CODE END */
}

/** @fn void mibspi3ParityCheck(void)
*   @brief Routine to check MIBSPI3 RAM parity error detection and signaling mechanism
*
*   Routine to check MIBSPI3 RAM parity error detection and signaling mechanism
*/
void mibspi3ParityCheck(void)
{
	volatile uint32 spiread = 0U;

/* USER CODE BEGIN (125) */
/* USER CODE END */
	
	/* enable multi-buffered mode */
	mibspiREG3->MIBSPIE = 0x1U;				

	/* enable parity test mode */
	mibspiREG3->UERRCTRL |= 1U << 8U;				
	
	/* flip bit 0 of the parity location */
	mibspiPARRAM3 ^= 0x1U;					

	/* enable parity error detection */
    mibspiREG3->UERRCTRL = (mibspiREG3->UERRCTRL & 0xFFFFFFF0U) | (0xAU);
	
	/* disable parity test mode */
	mibspiREG3->UERRCTRL &= ~(1U << 8U);				

	/* read from MibSPI3 RAM to cause parity error */
	spiread = *(uint32 *) mibspiRAM3;	

	/* check if ESM group1 channel 18 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x40000U))	!= 0U)
	{
		/* No MibSPI3 RAM parity error was flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (126) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (127) */
/* USER CODE END */
	}
	else
	{
	    /* clear parity error flags */
		mibspiREG3->UERRSTAT = 0x3U;			
		
		/* clear ESM group1 channel 18 flag */
		esmREG->ESTATUS1[0U] = 0x40000U;		
		
		/* enable parity test mode */
	    mibspiREG3->UERRCTRL |= 1U << 8U;			
		
		/* Revert back to correct data, flip bit 0 of the parity location */
	    mibspiPARRAM3 ^= 0x1U;				
		
		/* disable parity test mode */
	    mibspiREG3->UERRCTRL &= ~(1U << 8U);	

    	/* revert multi-buffered mode */
	    mibspiREG3->MIBSPIE = 0x0U;			
	}
	
/* USER CODE BEGIN (128) */
/* USER CODE END */
}

/** @fn void mibspi5ParityCheck(void)
*   @brief Routine to check MIBSPI5 RAM parity error detection and signaling mechanism
*
*   Routine to check MIBSPI5 RAM parity error detection and signaling mechanism
*/
void mibspi5ParityCheck(void)
{
	volatile uint32 spiread = 0U;

/* USER CODE BEGIN (129) */
/* USER CODE END */
	
	/* enable multi-buffered mode */
	mibspiREG5->MIBSPIE = 0x1U;				

	/* enable parity test mode */
	mibspiREG5->UERRCTRL |= 1U << 8U;	
    
	/* flip bit 0 of the parity location */	
	mibspiPARRAM5 ^= 0x1U;					

	/* enable parity error detection */
    mibspiREG5->UERRCTRL = (mibspiREG5->UERRCTRL & 0xFFFFFFF0U) | (0xAU);
	
	/* disable parity test mode */
	mibspiREG5->UERRCTRL &= ~(1U << 8U);				

	/* read from MibSPI5 RAM to cause parity error */
	spiread = *(uint32 *) mibspiRAM5;	

	/* check if ESM group1 channel 24 is flagged */
	if ((!(esmREG->ESTATUS1[0U] & 0x01000000U)) != 0U)
	{
		/* No MibSPI5 RAM parity error was flagged to ESM. */
		/* Need custom routine to handle this failure instead of the infinite loop */
		/* for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below */
/* USER CODE BEGIN (130) */
/* USER CODE END */
	for(;;)
	{ 
	}/* Wait */ 		
/* USER CODE BEGIN (131) */
/* USER CODE END */
	}
	else
	{
	    /* clear parity error flags */
		mibspiREG5->UERRSTAT = 0x3U;			
		
		/* clear ESM group1 channel 24 flag */
		esmREG->ESTATUS1[0U] = 0x01000000U;	
		
	    /* enable parity test mode */
		mibspiREG5->UERRCTRL |= 1U << 8U;			
	    
		/* Revert back to correct data, flip bit 0 of the parity location */
		mibspiPARRAM5 ^= 0x1U;				
	    
		/* disable parity test mode */
		mibspiREG5->UERRCTRL &= ~(1U << 8U);	

    	/* revert multi-buffered mode */
	    mibspiREG5->MIBSPIE = 0x0U;			
	}
	
/* USER CODE BEGIN (132) */
/* USER CODE END */
}


/** @fn void pbistGetConfigValue(pbist_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void pbistGetConfigValue(pbist_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_RAMT = PBIST_RAMT_CONFIGVALUE;
		config_reg->CONFIG_DLR = PBIST_DLR_CONFIGVALUE;
		config_reg->CONFIG_PACT = PBIST_PACT_CONFIGVALUE;
		config_reg->CONFIG_PBISTID = PBIST_PBISTID_CONFIGVALUE;
		config_reg->CONFIG_OVER = PBIST_OVER_CONFIGVALUE;
		config_reg->CONFIG_FSRDL1 = PBIST_FSRDL1_CONFIGVALUE;
		config_reg->CONFIG_ROM = PBIST_ROM_CONFIGVALUE;
		config_reg->CONFIG_ALGO = PBIST_ALGO_CONFIGVALUE;
		config_reg->CONFIG_RINFOL = PBIST_RINFOL_CONFIGVALUE;
		config_reg->CONFIG_RINFOU = PBIST_RINFOU_CONFIGVALUE;
	}
	else
	{
		config_reg->CONFIG_RAMT = pbistREG->RAMT;
		config_reg->CONFIG_DLR = pbistREG->DLR;
		config_reg->CONFIG_PACT = pbistREG->PACT;
		config_reg->CONFIG_PBISTID = pbistREG->PBISTID;
		config_reg->CONFIG_OVER = pbistREG->OVER;
		config_reg->CONFIG_FSRDL1 = pbistREG->FSRDL1;
		config_reg->CONFIG_ROM = pbistREG->ROM;
		config_reg->CONFIG_ALGO = pbistREG->ALGO;
		config_reg->CONFIG_RINFOL = pbistREG->RINFOL;
		config_reg->CONFIG_RINFOU = pbistREG->RINFOU;
	}
}

/** @fn void stcGetConfigValue(stc_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void stcGetConfigValue(stc_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_STCGCR0 = STC_STCGCR0_CONFIGVALUE;
		config_reg->CONFIG_STCGCR1 = STC_STCGCR1_CONFIGVALUE;
		config_reg->CONFIG_STCTPR = STC_STCTPR_CONFIGVALUE;
		config_reg->CONFIG_STCSCSCR = STC_STCSCSCR_CONFIGVALUE;
	}
	else
	{
		config_reg->CONFIG_STCGCR0 = stcREG->STCGCR0;
		config_reg->CONFIG_STCGCR1 = stcREG->STCGCR1;
		config_reg->CONFIG_STCTPR = stcREG->STCTPR;
		config_reg->CONFIG_STCSCSCR = stcREG->STCSCSCR;
	}
}


/** @fn void efcGetConfigValue(efc_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void efcGetConfigValue(efc_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_BOUNDARY = EFC_BOUNDARY_CONFIGVALUE;
		config_reg->CONFIG_PINS = EFC_PINS_CONFIGVALUE;
		config_reg->CONFIG_SELFTESTCYCLES = EFC_SELFTESTCYCLES_CONFIGVALUE;
		config_reg->CONFIG_SELFTESTSIGN = EFC_SELFTESTSIGN_CONFIGVALUE;
	}
	else
	{
		config_reg->CONFIG_BOUNDARY = efcREG->BOUNDARY;
		config_reg->CONFIG_PINS = efcREG->PINS;
		config_reg->CONFIG_SELFTESTCYCLES = efcREG->SELF_TEST_CYCLES;
		config_reg->CONFIG_SELFTESTSIGN = efcREG->SELF_TEST_SIGN;
	}
}


/** @fn void ccmr4GetConfigValue(ccmr4_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void ccmr4GetConfigValue(ccmr4_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_CCMKEYR = CCMR4_CCMKEYR_CONFIGVALUE;
	}
	else
	{
		config_reg->CONFIG_CCMKEYR = CCMKEYR;
	}
}
