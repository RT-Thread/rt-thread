/** @file system.c 
*   @brief System Driver Source File
*   @date 29.May.2013
*   @version 03.05.02
*
*   This file contains:
*   - API Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "system.h"
#include "sys_selftest.h"
#include "sys_pcr.h"
#include "pinmux.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void systemInit(void)
*   @brief Initializes System Driver
*
*   This function initializes the System driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void setupPLL(void)
{

/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** - Configure PLL control registers */
    /** @b Initialize @b Pll1: */

    /**   - Setup pll control register 1:
    *     - Setup reset on oscillator slip 
    *     - Setup bypass on pll slip
    *     - setup Pll output clock divider to max before Lock
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider 
    *     - Setup Pll multiplier          
    */
    systemREG1->PLLCTL1 =  0x00000000U 
                        |  0x20000000U 
                        | ((0x1FU)<< 24U) 
                        |  0x00000000U 
                        | ((6U - 1U)<< 16U) 
                        | ((150U - 1U)<< 8U);

    /**   - Setup pll control register 2
    *     - Enable/Disable frequency modulation
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    systemREG1->PLLCTL2 =  0x00000000U
                        | (255U << 22U)
                        | (7U << 12U)
                        | ((2U - 1U)<< 9U)
                        |  61U;

    /** @b Initialize @b Pll2: */

    /**   - Setup pll2 control register :
    *     - setup Pll output clock divider to max before Lock
    *     - Setup reference clock divider 
    *     - Setup internal Pll output divider
    *     - Setup Pll multiplier          
    */
    systemREG2->PLLCTL3 = ((2U - 1U) << 29U)
                        | ((0x1FU)<< 24U) 
                        | ((6U - 1U)<< 16U) 
                        | ((150U - 1U) << 8U);

	/** - Enable PLL(s) to start up or Lock */
    systemREG1->CSDIS = 0x00000000U	
                      | 0x00000000U 
                      | 0x00000008U 
                      | 0x00000080U 
                      | 0x00000000U 
                      | 0x00000000U 
                      | 0x00000000U;
}

void trimLPO(void)
{

/* USER CODE BEGIN (4) */
/* USER CODE END */

    /** @b Initialize Lpo: */
    /** Load TRIM values from OTP if present else load user defined values */
    if(LPO_TRIM_VALUE != 0xFFFFU)
    {
    
        systemREG1->LPOMONCTL  = (1U << 24U)
                                | LPO_TRIM_VALUE;
    }
    else
    {

    	systemREG1->LPOMONCTL 	= (1U << 24U)
                                 | (16U << 8U)
                                 | 8U;
    }

/* USER CODE BEGIN (5) */
/* USER CODE END */

}

void setupFlash(void)
{

/* USER CODE BEGIN (6) */
/* USER CODE END */

    /** - Setup flash read mode, address wait states and data wait states */
    flashWREG->FRDCNTL =  0x00000000U 
                       | (3U << 8U) 
                       | (1U << 4U) 
                       |  1U;

    /** - Setup flash access wait states for bank 7 */
    FSM_WR_ENA_HL    = 0x5U;
    EEPROM_CONFIG_HL = 0x00000002U
	                 | (3U << 16U) ;

/* USER CODE BEGIN (7) */
/* USER CODE END */

    /** - Disable write access to flash state machine registers */
    FSM_WR_ENA_HL    = 0xAU;

    /** - Setup flash bank power modes */
    flashWREG->FBFALLBACK = 0x00000000U
                          | (SYS_ACTIVE << 14U) 
                          | (SYS_SLEEP << 12U) 
                          | (SYS_SLEEP << 10U) 
                          | (SYS_SLEEP << 8U) 
                          | (SYS_SLEEP << 6U) 
                          | (SYS_SLEEP << 4U) 
                          | (SYS_ACTIVE << 2U) 
                          |  SYS_ACTIVE;

/* USER CODE BEGIN (8) */
/* USER CODE END */

}

void periphInit(void)
{

/* USER CODE BEGIN (9) */
/* USER CODE END */

    /** - Disable Peripherals before peripheral powerup*/
    systemREG1->CLKCNTL &= 0xFFFFFEFFU;

	/** - Release peripherals from reset and enable clocks to all peripherals */
    /** - Power-up all peripherals */
    pcrREG->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /** - Enable Peripherals */
    systemREG1->CLKCNTL |= 1U << 8U;
	
/* USER CODE BEGIN (10) */
/* USER CODE END */

}

void mapClocks(void)
{
	
/* USER CODE BEGIN (11) */
/* USER CODE END */

    /** @b Initialize @b Clock @b Tree: */
    /** - Disable / Enable clock domain */
    systemREG1->CDDIS= (FALSE << 4U ) /* AVCLK 1 OFF */
                      |(TRUE << 5U ) /* AVCLK 2 OFF */
	                  |(FALSE << 8U ) /* VCLK3 OFF */
					  |(FALSE << 9U ) /* VCLK4 OFF */
	                  |(FALSE << 10U) /* AVCLK 3 OFF */
                      |(FALSE << 11U); /* AVCLK 4 OFF */


    /* Work Around for Errata SYS#46:
     * 
     * Errata Description:            
     *            Clock Source Switching Not Qualified with Clock Source Enable And Clock Source Valid
     * Workaround:
     *            Always check the CSDIS register to make sure the clock source is turned on and check 
     * the CSVSTAT register to make sure the clock source is valid. Then write to GHVSRC to switch the clock.
     */
	/** - Wait for until clocks are locked */
    while ((systemREG1->CSVSTAT & ((systemREG1->CSDIS ^ 0xFFU) & 0xFFU)) != ((systemREG1->CSDIS ^ 0xFFU) & 0xFFU))
    { 
	} /* Wait */

/* USER CODE BEGIN (12) */
/* USER CODE END */

	/* Now the PLLs are locked and the PLL outputs can be sped up */
	/* The R-divider was programmed to be 0xF. Now this divider is changed to programmed value */
    systemREG1->PLLCTL1 = (systemREG1->PLLCTL1 & 0xE0FFFFFFU)|((1U - 1U)<< 24U);
    systemREG2->PLLCTL3 = (systemREG2->PLLCTL3 & 0xE0FFFFFFU)|((1U - 1U)<< 24U);

	/** - Map device clock domains to desired sources and configure top-level dividers */
	/** - All clock domains are working off the default clock sources until now */
	/** - The below assignments can be easily modified using the HALCoGen GUI */
    
    /** - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = (SYS_PLL1 << 24U) 
                       | (SYS_PLL1 << 16U) 
                       |  SYS_PLL1;
                       
    /** - Setup synchronous peripheral clock dividers for VCLK1, VCLK2, VCLK3 */
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xF0F0FFFFU) 
						 | (1U << 24U)  
						 | (1U << 16U);  
	systemREG2->CLK2CNTL = (systemREG2->CLK2CNTL & 0xFFFFF0F0U)
	                     | (1U) << 8U
						 | (1U);

/* USER CODE BEGIN (13) */
/* USER CODE END */
	
    /** - Setup RTICLK1 and RTICLK2 clocks */
    systemREG1->RCLKSRC = (1U << 24U)
                        | (SYS_VCLK << 16U) 
                        | (1U << 8U)  
                        |  SYS_VCLK;

    /** - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    systemREG1->VCLKASRC = (SYS_VCLK << 8U)
                          |  SYS_VCLK;

    systemREG2->VCLKACON1 = ((1U - 1U ) << 24U) 
                           | (0U << 20U) 
                           | (SYS_VCLK << 16U)
                           | ((1U - 1U ) << 8U)
                           | (0U << 4U) 
                           | SYS_VCLK;

/* USER CODE BEGIN (14) */
/* USER CODE END */

}

void systemInit(void)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

	/* Configure PLL control registers and enable PLLs.
	 * The PLL takes (127 + 1024 * NR) oscillator cycles to acquire lock.
	 * This initialization sequence performs all the tasks that are not
	 * required to be done at full application speed while the PLL locks.
	 */
	setupPLL();
	
/* USER CODE BEGIN (16) */
/* USER CODE END */

	/* Run eFuse controller start-up checks and start eFuse controller ECC self-test.
	 * This includes a check for the eFuse controller error outputs to be stuck-at-zero.
	 */
	//efcCheck();
	
/* USER CODE BEGIN (17) */
/* USER CODE END */
	
	/* Enable clocks to peripherals and release peripheral reset */
	periphInit();

/* USER CODE BEGIN (18) */
/* USER CODE END */

	/* Configure device-level multiplexing and I/O multiplexing */
	//muxInit();
	
/* USER CODE BEGIN (19) */
/* USER CODE END */

#if 0
	/* Wait for eFuse controller self-test to complete and check results */
	if ((!checkefcSelfTest()) !=0U)							/* eFuse controller ECC logic self-test failed */
	{
		efcClass2Error();								/* device operation is not reliable */
	}
#endif
/* USER CODE BEGIN (20) */
/* USER CODE END */

	/** - Set up flash address and data wait states based on the target CPU clock frequency
	 * The number of address and data wait states for the target CPU clock frequency are specified
	 * in the specific part's datasheet.
	 */
	setupFlash();

/* USER CODE BEGIN (21) */
/* USER CODE END */

	/** - Configure the LPO such that HF LPO is as close to 10MHz as possible */
	trimLPO();

/* USER CODE BEGIN (23) */
/* USER CODE END */

	/** - Wait for PLLs to start up and map clock domains to desired clock sources */
	mapClocks();

/* USER CODE BEGIN (24) */
/* USER CODE END */

	/** - set ECLK pins functional mode */
    systemREG1->SYSPC1 = 0U;

    /** - set ECLK pins default output value */
    systemREG1->SYSPC4 = 0U;

    /** - set ECLK pins output direction */
    systemREG1->SYSPC2 = 1U;

    /** - set ECLK pins open drain enable */
    systemREG1->SYSPC7 = 0U;

    /** - set ECLK pins pullup/pulldown enable */
    systemREG1->SYSPC8 = 0U;   

    /** - set ECLK pins pullup/pulldown select */
    systemREG1->SYSPC9 = 1U;

    /** - Setup ECLK */
    systemREG1->ECPCNTL = (0U << 24U)
                        | (0U << 23U)
                        | ((8U - 1U) & 0xFFFFU);

/* USER CODE BEGIN (25) */
/* USER CODE END */
}

void systemPowerDown(uint32 mode)
{

/* USER CODE BEGIN (26) */
/* USER CODE END */

    /* Disable clock sources */
    systemREG1->CSDISSET = mode & 0x000000FFU;

    /* Disable clock domains */
    systemREG1->CDDIS = (mode >> 8U) & 0x00000FFFU;

    /* Idle CPU */
	/*SAFETYMCUSW 88 S MR:2.1 <REVIEWED> "Assembly in C needed" */
    asm(" wfi");

/* USER CODE BEGIN (27) */
/* USER CODE END */

}

/* USER CODE BEGIN (28) */
/* USER CODE END */

/** @fn void systemGetConfigValue(system_config_reg_t *config_reg, config_value_type_t type)
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

void systemGetConfigValue(system_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_SYSPC1 = SYS_SYSPC1_CONFIGVALUE;
		config_reg->CONFIG_SYSPC2 = SYS_SYSPC2_CONFIGVALUE;
		config_reg->CONFIG_SYSPC7 = SYS_SYSPC7_CONFIGVALUE;
		config_reg->CONFIG_SYSPC8 = SYS_SYSPC8_CONFIGVALUE;
		config_reg->CONFIG_SYSPC9 = SYS_SYSPC9_CONFIGVALUE;
		config_reg->CONFIG_CSDIS = SYS_CSDIS_CONFIGVALUE;
		config_reg->CONFIG_CDDIS = SYS_CDDIS_CONFIGVALUE;
		config_reg->CONFIG_GHVSRC = SYS_GHVSRC_CONFIGVALUE;
		config_reg->CONFIG_VCLKASRC = SYS_VCLKASRC_CONFIGVALUE;
		config_reg->CONFIG_RCLKSRC = SYS_RCLKSRC_CONFIGVALUE;
		config_reg->CONFIG_MSTGCR = SYS_MSTGCR_CONFIGVALUE;
		config_reg->CONFIG_MINITGCR = SYS_MINITGCR_CONFIGVALUE;
		config_reg->CONFIG_MSINENA = SYS_MSINENA_CONFIGVALUE;
		config_reg->CONFIG_PLLCTL1 = SYS_PLLCTL1_CONFIGVALUE_2;
		config_reg->CONFIG_PLLCTL2 = SYS_PLLCTL2_CONFIGVALUE;
		config_reg->CONFIG_UERFLAG = SYS_UERFLAG_CONFIGVALUE;
		if(LPO_TRIM_VALUE != 0xFFFFU)
		{
			config_reg->CONFIG_LPOMONCTL = SYS_LPOMONCTL_CONFIGVALUE_1;
		}
		else
		{
			config_reg->CONFIG_LPOMONCTL = SYS_LPOMONCTL_CONFIGVALUE_2;
		}
		config_reg->CONFIG_CLKTEST = SYS_CLKTEST_CONFIGVALUE;
		config_reg->CONFIG_DFTCTRLREG1 = SYS_DFTCTRLREG1_CONFIGVALUE;
		config_reg->CONFIG_DFTCTRLREG2 = SYS_DFTCTRLREG2_CONFIGVALUE;
		config_reg->CONFIG_GPREG1 = SYS_GPREG1_CONFIGVALUE;
		config_reg->CONFIG_RAMGCR = SYS_RAMGCR_CONFIGVALUE;
		config_reg->CONFIG_BMMCR1 = SYS_BMMCR1_CONFIGVALUE;
		config_reg->CONFIG_MMUGCR = SYS_MMUGCR_CONFIGVALUE;
		config_reg->CONFIG_CLKCNTL = SYS_CLKCNTL_CONFIGVALUE;
		config_reg->CONFIG_ECPCNTL = SYS_ECPCNTL_CONFIGVALUE;
		config_reg->CONFIG_DEVCR1 = SYS_DEVCR1_CONFIGVALUE;
		config_reg->CONFIG_SYSECR = SYS_SYSECR_CONFIGVALUE;

		config_reg->CONFIG_PLLCTL3 = SYS2_PLLCTL3_CONFIGVALUE_2;
		config_reg->CONFIG_STCCLKDIV = SYS2_STCCLKDIV_CONFIGVALUE;
		config_reg->CONFIG_CLK2CNTL = SYS2_CLK2CNTL_CONFIGVALUE;
		config_reg->CONFIG_VCLKACON1 = SYS2_VCLKACON1_CONFIGVALUE;
		config_reg->CONFIG_CLKSLIP = SYS2_CLKSLIP_CONFIGVALUE;
		config_reg->CONFIG_EFC_CTLEN = SYS2_EFC_CTLEN_CONFIGVALUE;
	}
	else
	{
		config_reg->CONFIG_SYSPC1 = systemREG1->SYSPC1;
		config_reg->CONFIG_SYSPC2 = systemREG1->SYSPC2;
		config_reg->CONFIG_SYSPC7 = systemREG1->SYSPC7;
		config_reg->CONFIG_SYSPC8 = systemREG1->SYSPC8;
		config_reg->CONFIG_SYSPC9 = systemREG1->SYSPC9;
		config_reg->CONFIG_CSDIS = systemREG1->CSDIS;
		config_reg->CONFIG_CDDIS = systemREG1->CDDIS;
		config_reg->CONFIG_GHVSRC = systemREG1->GHVSRC;
		config_reg->CONFIG_VCLKASRC = systemREG1->VCLKASRC;
		config_reg->CONFIG_RCLKSRC = systemREG1->RCLKSRC;
		config_reg->CONFIG_MSTGCR = systemREG1->MSTGCR;
		config_reg->CONFIG_MINITGCR = systemREG1->MINITGCR;
		config_reg->CONFIG_MSINENA = systemREG1->MSINENA;
		config_reg->CONFIG_PLLCTL1 = systemREG1->PLLCTL1;
		config_reg->CONFIG_PLLCTL2 = systemREG1->PLLCTL2;
		config_reg->CONFIG_UERFLAG = systemREG1->UERFLAG;
		config_reg->CONFIG_LPOMONCTL = systemREG1->LPOMONCTL;
		config_reg->CONFIG_CLKTEST = systemREG1->CLKTEST;
		config_reg->CONFIG_DFTCTRLREG1 = systemREG1->DFTCTRLREG1;
		config_reg->CONFIG_DFTCTRLREG2 = systemREG1->DFTCTRLREG2;
		config_reg->CONFIG_GPREG1 = systemREG1->GPREG1;
		config_reg->CONFIG_RAMGCR = systemREG1->RAMGCR;
		config_reg->CONFIG_BMMCR1 = systemREG1->BMMCR1;
		config_reg->CONFIG_MMUGCR = systemREG1->MMUGCR;
		config_reg->CONFIG_CLKCNTL = systemREG1->CLKCNTL;
		config_reg->CONFIG_ECPCNTL = systemREG1->ECPCNTL;
		config_reg->CONFIG_DEVCR1 = systemREG1->DEVCR1;
		config_reg->CONFIG_SYSECR = systemREG1->SYSECR;
		
		config_reg->CONFIG_PLLCTL3 = systemREG2->PLLCTL3;
		config_reg->CONFIG_STCCLKDIV = systemREG2->STCCLKDIV;
		config_reg->CONFIG_CLK2CNTL = systemREG2->CLK2CNTL;
		config_reg->CONFIG_VCLKACON1 = systemREG2->VCLKACON1;
		config_reg->CONFIG_CLKSLIP = systemREG2->CLKSLIP;
		config_reg->CONFIG_EFC_CTLEN = systemREG2->EFC_CTLEN;
	}
}

/** @fn void tcmflashGetConfigValue(tcmflash_config_reg_t *config_reg, config_value_type_t type)
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

void tcmflashGetConfigValue(tcmflash_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg-> CONFIG_FRDCNTL = TCMFLASH_FRDCNTL_CONFIGVALUE;
		config_reg-> CONFIG_FEDACCTRL1 = TCMFLASH_FEDACCTRL1_CONFIGVALUE;
		config_reg-> CONFIG_FEDACCTRL2 = TCMFLASH_FEDACCTRL2_CONFIGVALUE;
		config_reg-> CONFIG_FEDACSDIS = TCMFLASH_FEDACSDIS_CONFIGVALUE;
		config_reg-> CONFIG_FBPROT = TCMFLASH_FBPROT_CONFIGVALUE;
		config_reg-> CONFIG_FBSE = TCMFLASH_FBSE_CONFIGVALUE;
		config_reg-> CONFIG_FBAC = TCMFLASH_FBAC_CONFIGVALUE;
		config_reg-> CONFIG_FBFALLBACK = TCMFLASH_FBFALLBACK_CONFIGVALUE;
		config_reg-> CONFIG_FPAC1 = TCMFLASH_FPAC1_CONFIGVALUE;
		config_reg-> CONFIG_FPAC2 = TCMFLASH_FPAC2_CONFIGVALUE;
		config_reg-> CONFIG_FMAC = TCMFLASH_FMAC_CONFIGVALUE;
		config_reg-> CONFIG_FLOCK = TCMFLASH_FLOCK_CONFIGVALUE;
		config_reg-> CONFIG_FDIAGCTRL = TCMFLASH_FDIAGCTRL_CONFIGVALUE;
		config_reg-> CONFIG_FEDACSDIS2 = TCMFLASH_FEDACSDIS2_CONFIGVALUE;
	}
	else
	{
		config_reg-> CONFIG_FRDCNTL = flashWREG->FRDCNTL;
		config_reg-> CONFIG_FEDACCTRL1 = flashWREG->FEDACCTRL1;
		config_reg-> CONFIG_FEDACCTRL2 = flashWREG->FEDACCTRL2;
		config_reg-> CONFIG_FEDACSDIS = flashWREG->FEDACSDIS;
		config_reg-> CONFIG_FBPROT = flashWREG->FBPROT;
		config_reg-> CONFIG_FBSE = flashWREG->FBSE;
		config_reg-> CONFIG_FBAC = flashWREG->FBAC;
		config_reg-> CONFIG_FBFALLBACK = flashWREG->FBFALLBACK;
		config_reg-> CONFIG_FPAC1 = flashWREG->FPAC1;
		config_reg-> CONFIG_FPAC2 = flashWREG->FPAC2;
		config_reg-> CONFIG_FMAC = flashWREG->FMAC;
		config_reg-> CONFIG_FLOCK = flashWREG->FLOCK;
		config_reg-> CONFIG_FDIAGCTRL = flashWREG->FDIAGCTRL;
		config_reg-> CONFIG_FEDACSDIS2 = flashWREG->FEDACSDIS2;
	}
}



/** @fn void sramGetConfigValue(sram_config_reg_t *config_reg, config_value_type_t type)
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

void sramGetConfigValue(sram_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_RAMCTRL[0U] = SRAM_RAMCTRL_CONFIGVALUE;
		config_reg->CONFIG_RAMTHRESHOLD[0U] = SRAM_RAMTHRESHOLD_CONFIGVALUE;
		config_reg->CONFIG_RAMINTCTRL[0U] = SRAM_RAMINTCTRL_CONFIGVALUE;
		config_reg->CONFIG_RAMTEST[0U] = SRAM_RAMTEST_CONFIGVALUE;
		config_reg->CONFIG_RAMADDRDECVECT[0U] = SRAM_RAMADDRDECVECT_CONFIGVALUE;
		
		config_reg->CONFIG_RAMCTRL[1U] = SRAM_RAMCTRL_CONFIGVALUE;
		config_reg->CONFIG_RAMTHRESHOLD[1U] = SRAM_RAMTHRESHOLD_CONFIGVALUE;
		config_reg->CONFIG_RAMINTCTRL[1U] = SRAM_RAMINTCTRL_CONFIGVALUE;
		config_reg->CONFIG_RAMTEST[1U] = SRAM_RAMTEST_CONFIGVALUE;
		config_reg->CONFIG_RAMADDRDECVECT[1U] = SRAM_RAMADDRDECVECT_CONFIGVALUE;
	}
	else
	{
		config_reg->CONFIG_RAMCTRL[0U] = tcram1REG->RAMCTRL;
		config_reg->CONFIG_RAMTHRESHOLD[0U] = tcram1REG->RAMTHRESHOLD;
		config_reg->CONFIG_RAMINTCTRL[0U] = tcram1REG->RAMINTCTRL;
		config_reg->CONFIG_RAMTEST[0U] = tcram1REG->RAMTEST;
		config_reg->CONFIG_RAMADDRDECVECT[0U] = tcram1REG->RAMADDRDECVECT;
	
		config_reg->CONFIG_RAMCTRL[1U] = tcram2REG->RAMCTRL;
		config_reg->CONFIG_RAMTHRESHOLD[1U] = tcram2REG->RAMTHRESHOLD;
		config_reg->CONFIG_RAMINTCTRL[1U] = tcram2REG->RAMINTCTRL;
		config_reg->CONFIG_RAMTEST[1U] = tcram2REG->RAMTEST;
		config_reg->CONFIG_RAMADDRDECVECT[1U] = tcram2REG->RAMADDRDECVECT;
	}
}
