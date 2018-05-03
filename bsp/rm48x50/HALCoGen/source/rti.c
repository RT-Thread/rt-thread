/** @file rti.c 
*   @brief RTI Driver Source File
*   @date 29.May.2013
*   @version 03.05.02
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the RTI driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "rti.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void rtiInit(void)
*   @brief Initializes RTI Driver
*
*   This function initializes the RTI driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void rtiInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */
    /** @b Initialize @b RTI1: */

    /** - Setup NTU source, debug options and disable both counter blocks */
    rtiREG1->GCTRL = (1U << 16U) | 0x00000000U;

    /** - Setup timebase for free running counter 0 */
    rtiREG1->TBCTRL = 0x00000000U;

    /** - Enable/Disable capture event sources for both counter blocks */
    rtiREG1->CAPCTRL = 0U | 0U;

    /** - Setup input source compare 0-3 */
    rtiREG1->COMPCTRL = 0x00001000U | 0x00000100U | 0x00000000U | 0x00000000U;

    /** - Reset up counter 0 */
    rtiREG1->CNT[0U].UCx = 0x00000000U;

    /** - Reset free running counter 0 */
    rtiREG1->CNT[0U].FRCx = 0x00000000U;

    /** - Setup up counter 0 compare value 
    *     - 0x00000000: Divide by 2^32
    *     - 0x00000001-0xFFFFFFFF: Divide by (CPUC0 + 1)
    */
    rtiREG1->CNT[0U].CPUCx = 9U;

    /** - Reset up counter 1 */
    rtiREG1->CNT[1U].UCx = 0x00000000U;

    /** - Reset free running counter 1 */
    rtiREG1->CNT[1U].FRCx  = 0x00000000U;

    /** - Setup up counter 1 compare value 
    *     - 0x00000000: Divide by 2^32
    *     - 0x00000001-0xFFFFFFFF: Divide by (CPUC1 + 1)
    */
    rtiREG1->CNT[1U].CPUCx = 9U;

    /** - Setup compare 0 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[0U].COMPx = 10000U;

    /** - Setup update compare 0 value. This value is added to the compare 0 value on each compare match. */
    rtiREG1->CMP[0U].UDCPx = 10000U;

    /** - Setup compare 1 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[1U].COMPx = 50000U;

    /** - Setup update compare 1 value. This value is added to the compare 1 value on each compare match. */
    rtiREG1->CMP[1U].UDCPx = 50000U;

    /** - Setup compare 2 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[2U].COMPx = 80000U;

    /** - Setup update compare 2 value. This value is added to the compare 2 value on each compare match. */
    rtiREG1->CMP[2U].UDCPx = 80000U;

    /** - Setup compare 3 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[3U].COMPx = 100000U;

    /** - Setup update compare 3 value. This value is added to the compare 3 value on each compare match. */
    rtiREG1->CMP[3U].UDCPx = 100000U;

    /** - Clear all pending interrupts */
    rtiREG1->INTFLAG = 0x0007000FU;

    /** - Disable all interrupts */
    rtiREG1->CLEARINT = 0x00070F0FU;

    /**   @note This function has to be called before the driver can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           This function does not start the counters.
    */

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @fn void rtiStartCounter(uint32 counter)
*   @brief Starts RTI Counter block
*   @param[in] counter Select counter block to be started:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be started
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be started
*
*   This function starts selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (6) */
/* USER CODE END */

void rtiStartCounter(uint32 counter)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

    rtiREG1->GCTRL |= (1U << (counter & 3U));

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */


/** @fn void rtiStopCounter(uint32 counter)
*   @brief Stops RTI Counter block
*   @param[in] counter Select counter to be stopped:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be stopped
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be stopped
*
*   This function stops selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (10) */
/* USER CODE END */

void rtiStopCounter(uint32 counter)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    rtiREG1->GCTRL &= ~(1U << (counter & 3U));

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/* USER CODE BEGIN (13) */
/* USER CODE END */


/** @fn uint32 rtiResetCounter(uint32 counter)
*   @brief Reset RTI Counter block
*   @param[in] counter Select counter block to be reset:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be reset
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be reset
*   @return The function will return:
*           - 0: When the counter reset wasn't successful   
*           - 1: When the counter reset was successful   
*
*   This function resets selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (14) */
/* USER CODE END */

uint32 rtiResetCounter(uint32 counter)
{
    uint32 success = 0U;

/* USER CODE BEGIN (15) */
/* USER CODE END */

    if ((!(rtiREG1->GCTRL & (1U << (counter & 3U)))) != 0U)
    {
        rtiREG1->CNT[counter].UCx = 0x00000000U;
        rtiREG1->CNT[counter].FRCx = 0x00000000U;

        success = 1U;
    }

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           The selected counter block has to be stopped before it can reset.
    */

/* USER CODE BEGIN (16) */
/* USER CODE END */

    return success;
}

/* USER CODE BEGIN (17) */
/* USER CODE END */


/** @fn void rtiSetPeriod(uint32 compare, uint32 period)
*   @brief Set new period of RTI compare
*   @param[in] compare Select compare to change period:
*              - rtiCOMPARE0: RTI compare 0 will change the period
*              - rtiCOMPARE1: RTI compare 1 will change the period
*              - rtiCOMPARE2: RTI compare 2 will change the period
*              - rtiCOMPARE3: RTI compare 3 will change the period
*   @param[in] period new period in [ticks - 1]:
*              - 0x00000000: Divide by 1
*              - n: Divide by n + 1
*
*   This function will change the period of the selected compare.
*/

/* USER CODE BEGIN (18) */
/* USER CODE END */

void rtiSetPeriod(uint32 compare, uint32 period)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    rtiREG1->CMP[compare].UDCPx = period;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           When the corresponding counter block is not stopped,\n
    *           the period will change on the next compare match of the old period.
    */

/* USER CODE BEGIN (20) */
/* USER CODE END */
}

/* USER CODE BEGIN (21) */
/* USER CODE END */


/** @fn uint32 rtiGetPeriod(uint32 compare)
*   @brief Get current period of RTI compare
*   @param[in] compare Select compare to return the current period:
*              - rtiCOMPARE0: RTI compare 0 will return the current period
*              - rtiCOMPARE1: RTI compare 1 will return the current period
*              - rtiCOMPARE2: RTI compare 2 will return the current period
*              - rtiCOMPARE3: RTI compare 3 will return the current period
*   @return Current period of selected compare in [ticks - 1]:
*           - 0x00000000: Divide by 1
*           - n: Divide by n + 1
*
*   This function will return the period of the selected compare.
*/

/* USER CODE BEGIN (22) */
/* USER CODE END */

uint32 rtiGetPeriod(uint32 compare)
{
    uint32 period;

/* USER CODE BEGIN (23) */
/* USER CODE END */

    period = rtiREG1->CMP[compare].UDCPx;

    /**   @note The function rtiInit has to be called before this function can be used.
    */

/* USER CODE BEGIN (24) */
/* USER CODE END */

    return period;
}

/* USER CODE BEGIN (25) */
/* USER CODE END */


/** @fn uint32 rtiGetCurrentTick(uint32 compare)
*   @brief Get current tick of RTI compare
*   @param[in] compare Select compare to return the current tick:
*              - rtiCOMPARE0: RTI compare 0 will return the current tick
*              - rtiCOMPARE1: RTI compare 1 will return the current tick
*              - rtiCOMPARE2: RTI compare 2 will return the current tick
*              - rtiCOMPARE3: RTI compare 3 will return the current tick
*   @return Current tick of selected compare
*
*   This function will return the current tick of the selected compare.
*/

/* USER CODE BEGIN (26) */
/* USER CODE END */

uint32 rtiGetCurrentTick(uint32 compare)
{
    uint32 tick;
    uint32 counter = ((rtiREG1->COMPCTRL & (1U << (compare << 2U))) !=0U ) ? 1U : 0U;

/* USER CODE BEGIN (27) */
/* USER CODE END */

    tick = rtiREG1->CNT[counter].FRCx - (rtiREG1->CMP[compare].COMPx - rtiREG1->CMP[compare].UDCPx);

    /**   @note The function rtiInit has to be called before this function can be used.
    */

/* USER CODE BEGIN (28) */
/* USER CODE END */

    return tick;
}

/* USER CODE BEGIN (29) */
/* USER CODE END */

/** @fn void dwdInit(uint16 dwdPreload)
*   @brief Initialize DWD Expiration Period 
*   @param[in] dwdPreload DWD Preload value for expiration time.
*              - Texp = (dwdPreload +1) / RTICLK
*              - n: Divide by n + 1
*
*   This function can be called to set the DWD expiration
*   
*/
void dwdInit(uint16 dwdPreload)
{
/* USER CODE BEGIN (30) */
/* USER CODE END */

    /* Clear the violations if already present */
	rtiREG1->WDSTATUS = 0xFFU;
	
	rtiREG1->DWDPRLD = dwdPreload;
	
/* USER CODE BEGIN (31) */
/* USER CODE END */
}

/* USER CODE BEGIN (32) */
/* USER CODE END */

/** @fn void dwwdInit(dwwdReaction_t Reaction, uint16 dwdPreload, dwwdWindowSize_t Window_Size)
*   @brief Initialize DWD Expiration Period 
*   @param[in] Reaction DWWD reaction if the watchdog is serviced outside the time window.
*              - Generate_Reset  
*              - Generate_NMI
*   @param[in] dwdPreload DWWD Preload value for the watchdog expiration time.
*              - Texp = (dwdPreload +1) / RTICLK
*              - n: Divide by n + 1
*   @param[in] Window_Size DWWD time window size
*              - Size_100_Percent
*              - Size_50_Percent
*              - Size_25_Percent
*              - Size_12_5_Percent
*              - Size_6_25_Percent
*              - Size_3_125_Percent
*
*   This function can be called to set the DWD expiration
*   
*/
void dwwdInit(dwwdReaction_t Reaction, uint16 dwdPreload, dwwdWindowSize_t Window_Size)
{
/* USER CODE BEGIN (33) */
/* USER CODE END */

    /* Clear the violations if already present */
	rtiREG1->WDSTATUS = 0xFFU;

    rtiREG1->WWDSIZECTRL = (uint32) Window_Size;
	rtiREG1->DWDPRLD     = (uint32) dwdPreload;
	rtiREG1->WWDRXNCTRL  = (uint32) Reaction;

/* USER CODE BEGIN (34) */
/* USER CODE END */
}

/* USER CODE BEGIN (35) */
/* USER CODE END */

/** @fn uint32 dwwdGetCurrentDownCounter(void)
*   @brief Get the current DWWD Down Counter 
*   @return Current tick of selected compare
*
*   This function will get the current DWWD down counter value.
*   
*/
uint32 dwwdGetCurrentDownCounter(void)
{
/* USER CODE BEGIN (36) */
/* USER CODE END */

    return (rtiREG1->DWDCNTR);

/* USER CODE BEGIN (37) */
/* USER CODE END */
}

/* USER CODE BEGIN (38) */
/* USER CODE END */

/** @fn void dwdCounterEnable(void)
*   @brief Enable DWD
*
*   This function will Enable the DWD counter.
*   
*/
void dwdCounterEnable(void)
{
/* USER CODE BEGIN (39) */
/* USER CODE END */

	rtiREG1->DWDCTRL = 0xA98559DAU;
	
/* USER CODE BEGIN (40) */
/* USER CODE END */
}

/* USER CODE BEGIN (41) */
/* USER CODE END */

/* USER CODE BEGIN (42) */
/* USER CODE END */
/* USER CODE BEGIN (43) */
/* USER CODE END */
/* USER CODE BEGIN (44) */
/* USER CODE END */
/** @fn void dwdSetPreload(uint16 dwdPreload)
*   @brief Initialize DWD Expiration Period 
*   @param[in] dwdPreload DWD Preload value for the watchdog expiration time.
*              - Texp = (dwdPreload +1) / RTICLK
*              - n: Divide by n + 1
*
*   This function can be called to set the Preload value for the watchdog expiration time.
*   
*/
void dwdSetPreload(uint16 dwdPreload)
{
/* USER CODE BEGIN (45) */
/* USER CODE END */
	rtiREG1->DWDPRLD = dwdPreload;
/* USER CODE BEGIN (46) */
/* USER CODE END */
}

/* USER CODE BEGIN (47) */
/* USER CODE END */

/** @fn void dwdReset(void)
*   @brief Reset Digital Watchdog 
*
*   This function can be called to reset Digital Watchdog.
*   
*/
void dwdReset(void)
{
/* USER CODE BEGIN (48) */
/* USER CODE END */
	rtiREG1->WDKEY = 0x0000E51AU;
	rtiREG1->WDKEY = 0x0000A35CU;
/* USER CODE BEGIN (49) */
/* USER CODE END */
}

/** @fn void dwdGenerateSysReset(void)
*   @brief Generate System Reset through DWD
*
*   This function can be called to generate system reset using DWD.
*   
*/
void dwdGenerateSysReset(void)
{
/* USER CODE BEGIN (50) */
/* USER CODE END */
	rtiREG1->WDKEY = 0x0000E51AU;
	rtiREG1->WDKEY = 0x00002345U;
/* USER CODE BEGIN (51) */
/* USER CODE END */
}

/* USER CODE BEGIN (52) */
/* USER CODE END */

/** @fn boolean IsdwdKeySequenceCorrect(void)
*   @brief Check if DWD Key sequence correct.
*   @return The function will return:
*           - TRUE: When the DWD key sequence is written correctly.
*           - FALSE: When the DWD key sequence is written incorrectly / not written.
*
*   This function will get status of the DWD Key sequence.
*   
*/
boolean IsdwdKeySequenceCorrect(void)
{
	boolean Status;

/* USER CODE BEGIN (53) */
/* USER CODE END */

	if((rtiREG1->WDSTATUS & 0x4U) == 0x4U)
	{
		Status = FALSE;
	}
	else
	{
		Status = TRUE;
	}

/* USER CODE BEGIN (54) */
/* USER CODE END */

	return Status;
}

/* USER CODE BEGIN (55) */
/* USER CODE END */

/** @fn dwdResetStatus_t dwdGetStatus(void)
*   @brief Check if Reset is generated due to DWD.
*   @return The function will return:
*           - Reset_Generated: When the Reset is generated due to DWD.
*           - No_Reset_Generated: No Reset is generated due to DWD.
*
*   This function will get dwd Reset status.
*   
*/
dwdResetStatus_t dwdGetStatus(void)
{
/* USER CODE BEGIN (56) */
/* USER CODE END */
	dwdResetStatus_t Reset_Status;
	if((rtiREG1->WDSTATUS & 0x2U) == 0x2U)
	{
		Reset_Status = Reset_Generated;
	}
	else
	{
		Reset_Status = No_Reset_Generated;
	}

/* USER CODE BEGIN (57) */
/* USER CODE END */
	return Reset_Status;
}

/* USER CODE BEGIN (58) */
/* USER CODE END */

/** @fn void dwdClearFlag(void)
*   @brief Clear the DWD violation flag.
*
*   This function will clear dwd status register.
*   
*/
void dwdClearFlag(void)
{
/* USER CODE BEGIN (59) */
/* USER CODE END */

	rtiREG1->WDSTATUS = 0xFFU;

/* USER CODE BEGIN (60) */
/* USER CODE END */
}

/* USER CODE BEGIN (61) */
/* USER CODE END */

/** @fn dwdViolation_t dwdGetViolationStatus(void)
*   @brief Check the status of the DWD or DWWD violation happened.
*   @return The function will return one of following violations occured:
*           - NoTime_Violation
*           - Key_Seq_Violation
*           - Time_Window_Violation
*           - EndTime_Window_Violation
*           - StartTime_Window_Violation
*
*   This function will get status of the DWD or DWWD violation status.
*   
*/
dwdViolation_t dwdGetViolationStatus(void)
{
/* USER CODE BEGIN (62) */
/* USER CODE END */
	dwdViolation_t Violation_Status;

	if ((rtiREG1->WDSTATUS & 0x20U) == 0x20U)
	{
		Violation_Status = Time_Window_Violation;
	}
	else if ((rtiREG1->WDSTATUS & 0x04U) == 0x04U)
	{
		Violation_Status = Key_Seq_Violation;
	}	
	else if((rtiREG1->WDSTATUS & 0x8U) == 0x8U)
	{
		Violation_Status = StartTime_Window_Violation;
	}
	else if ((rtiREG1->WDSTATUS & 0x10U) == 0x10U)
	{
		Violation_Status = EndTime_Window_Violation;
	}
	else
	{
		Violation_Status = NoTime_Violation;
	}
	
/* USER CODE BEGIN (63) */
/* USER CODE END */

	return Violation_Status;
}

/* USER CODE BEGIN (64) */
/* USER CODE END */

/** @fn void rtiEnableNotification(uint32 notification)
*   @brief Enable notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   This function will enable the selected notification of a RTI module.
*   It is possible to enable multiple notifications masked.
*/

/* USER CODE BEGIN (65) */
/* USER CODE END */

void rtiEnableNotification(uint32 notification)
{
/* USER CODE BEGIN (66) */
/* USER CODE END */

    rtiREG1->INTFLAG = notification;
    rtiREG1->SETINT   = notification;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (67) */
/* USER CODE END */
}

/* USER CODE BEGIN (68) */
/* USER CODE END */

/** @fn void rtiDisableNotification(uint32 notification)
*   @brief Disable notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   This function will disable the selected notification of a RTI module.
*   It is possible to disable multiple notifications masked.
*/

/* USER CODE BEGIN (69) */
/* USER CODE END */

void rtiDisableNotification(uint32 notification)
{
/* USER CODE BEGIN (70) */
/* USER CODE END */

    rtiREG1->CLEARINT = notification;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (71) */
/* USER CODE END */
}

/* USER CODE BEGIN (72) */
/* USER CODE END */

/** @fn void rtiGetConfigValue(rti_config_reg_t *config_reg, config_value_type_t type)
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
void rtiGetConfigValue(rti_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_GCTRL = RTI_GCTRL_CONFIGVALUE;
		config_reg->CONFIG_TBCTRL = RTI_TBCTRL_CONFIGVALUE;
		config_reg->CONFIG_CAPCTRL = RTI_CAPCTRL_CONFIGVALUE;
		config_reg->CONFIG_COMPCTRL = RTI_COMPCTRL_CONFIGVALUE;
		config_reg->CONFIG_UDCP0 = RTI_UDCP0_CONFIGVALUE;
		config_reg->CONFIG_UDCP1 = RTI_UDCP1_CONFIGVALUE;
		config_reg->CONFIG_UDCP2 = RTI_UDCP2_CONFIGVALUE;
		config_reg->CONFIG_UDCP3 = RTI_UDCP3_CONFIGVALUE;
		config_reg->CONFIG_TBLCOMP = RTI_TBLCOMP_CONFIGVALUE;
		config_reg->CONFIG_TBHCOMP = RTI_TBHCOMP_CONFIGVALUE;
		config_reg->CONFIG_SETINT = RTI_SETINT_CONFIGVALUE;
		config_reg->CONFIG_DWDCTRL = RTI_DWDCTRL_CONFIGVALUE;
		config_reg->CONFIG_DWDPRLD = RTI_DWDPRLD_CONFIGVALUE;
		config_reg->CONFIG_WWDRXNCTRL = RTI_WWDRXNCTRL_CONFIGVALUE;
		config_reg->CONFIG_WWDSIZECTRL = RTI_WWDSIZECTRL_CONFIGVALUE;
	}
	else
	{	 
		config_reg->CONFIG_GCTRL = rtiREG1->GCTRL;
		config_reg->CONFIG_TBCTRL = rtiREG1->TBCTRL;
		config_reg->CONFIG_CAPCTRL = rtiREG1->CAPCTRL;
		config_reg->CONFIG_COMPCTRL = rtiREG1->COMPCTRL;
		config_reg->CONFIG_UDCP0 = rtiREG1->CMP[0U].UDCPx;
		config_reg->CONFIG_UDCP1 = rtiREG1->CMP[1U].UDCPx;
		config_reg->CONFIG_UDCP2 = rtiREG1->CMP[2U].UDCPx;
		config_reg->CONFIG_UDCP3 = rtiREG1->CMP[3U].UDCPx;
		config_reg->CONFIG_TBLCOMP = rtiREG1->TBLCOMP;
		config_reg->CONFIG_TBHCOMP = rtiREG1->TBHCOMP;
		config_reg->CONFIG_SETINT = rtiREG1->SETINT;
		config_reg->CONFIG_DWDCTRL = rtiREG1->DWDCTRL;
		config_reg->CONFIG_DWDPRLD = rtiREG1->DWDPRLD;
		config_reg->CONFIG_WWDRXNCTRL = rtiREG1->WWDRXNCTRL;
		config_reg->CONFIG_WWDSIZECTRL = rtiREG1->WWDSIZECTRL;
	}
}

