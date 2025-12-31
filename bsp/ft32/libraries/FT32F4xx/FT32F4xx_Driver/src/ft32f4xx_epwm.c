/**
  ******************************************************************************
  * @file         ft32f4xx_epwm.c
  * @author       FMD AE
  * @brief        This file provides firmware functions to manage the following
  *               functionalities of the Enhanced Pulse Width Modulator (EPWM):
  *               + Initialization and Configuration
  *               + Interrupts and flags management
  * @version      V1.0.0
  * @data         2025-03-26
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_epwm.h"
#include "ft32f4xx_rcc.h"

/** @defgroup EPWM
  * @brief EPWM driver modules
  * @{
  */



/**
  * @brief  When the EALLOW bit is set to 1, write protection function will be disable and
  *         write operations can be performed on the related registers.
  * @param  EPWMx  where x can be 1 to 4 to select the EPWM peripheral.
  * @retval None
  */
void EALLOW(EPWM_TypeDef* EPWMx)
{
    EPWMx->TBCTL |= EPWM_TBCTL_EALLOW_BITS;
}

/**
  * @brief  When the EALLOW bit is set to 0, write protection function will be enabled and
  *         write operations on the related registers will not be allowed.
  * @param  EPWMx  where x can be 1 to 4 to select the EPWM peripheral.
  * @retval None
  */
void EDIS(EPWM_TypeDef* EPWMx)
{
    EPWMx->TBCTL &= ~EPWM_TBCTL_EALLOW_BITS;
}


/**
  * @brief  Checks whether the specified EPWM TripZone flag is set or not.
  * @param  EPWMx  where x can be 1 to 4 to select the EPWM peripheral.
  * @param  TZ_FLAG: specifies the TripZone flag to check.
  *          This parameter can be one of the following values:
  *            @arg EPWM_TZ_FLAG_INT     : Transmit buffer empty flag.
  *            @arg EPWM_TZ_FLAG_CBC     : Receive buffer not empty flag.
  *            @arg EPWM_TZ_FLAG_OST     : Busy flag.
  *            @arg EPWM_TZ_FLAG_DCAEVT1 : Overrun flag.
  *            @arg EPWM_TZ_FLAG_DCAEVT2 : Mode Fault flag.
  *            @arg EPWM_TZ_FLAG_DCBEVT1 : CRC Error flag.
  *            @arg EPWM_TZ_FLAG_DCBEVT2 : TI frame format error flag.
  * @retval The new state of TZ_FLAG (SET or RESET).
  */
FlagStatus EPWM_TripZone_GetFlagStatus(EPWM_TypeDef* EPWMx, uint16_t TZ_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_EPWM_TZ_GET_FLAG(TZ_FLAG));

    /* Check the status of the specified EPWM flag */
    if ((EPWMx->TZFLG & TZ_FLAG) != (uint16_t)RESET)
    {
        /* TZ_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* TZ_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the TZ_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Checks whether the specified EPWM Event Trigger flag is set or not.
  * @param  EPWMx  where x can be 1 to 4 to select the EPWM peripheral.
  * @param  ET_FLAG: specifies the Event Trigger flag to check.
  *          This parameter can be one of the following values:
  *            @arg EPWM_ET_FLAG_INT  : Transmit buffer empty flag.
  *            @arg EPWM_ET_FLAG_SOCA : Receive buffer not empty flag.
  *            @arg EPWM_ET_FLAG_SOCB : Busy flag.
  * @retval The new state of ET_FLAG (SET or RESET).
  */
FlagStatus EPWM_EventTrigger_GetFlagStatus(EPWM_TypeDef* EPWMx, uint16_t ET_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_EPWM_ET_GET_FLAG(ET_FLAG));

    /* Check the status of the specified EPWM flag */
    if ((EPWMx->ETFLG & ET_FLAG) != (uint16_t)RESET)
    {
        /* ET_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ET_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ET_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Checks whether the specified EPWM Mep Calibration flag is set or not.
  * @param  EPWMx  where x can be 1 to 4 to select the EPWM peripheral.
  * @param  MEP_FLAG: specifies the Mep Calibration flag to check.
  *          This parameter can be one of the following values:
  *            @arg EPWM_MEP_FLAG_INT  : Mep Calibration done flag.
  * @retval The new state of MEP_FLAG (SET or RESET).
  */
FlagStatus EPWM_MepCalibration_GetFlagStatus(EPWM_TypeDef* EPWMx, uint16_t MEP_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_EPWM_MEP_GET_FLAG(MEP_FLAG));

    /* Check the status of the specified EPWM flag */
    if ((EPWMx->MEPFLG & MEP_FLAG) != (uint16_t)RESET)
    {
        /* MEP_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* MEP_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the MEP_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Enable MEP SFO when AUTOCONV = 1.
  * @param  EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval HRMSTEP value when MEPFLG_MEPFLG = 1.
  */
uint8_t EPWM_enableMEPSFO(EPWM_TypeDef* EPWMx)
{
    EALLOW(EPWMx);

    if (((EPWMx->HRCNFG)&EPWM_HRCNFG_AUTOCONV_BITS) == EPWM_HRCNFG_AUTOCONV_BITS)
    {
        EPWMx->HRPWR |=  EPWM_HRPPWR_MEPSFO_BITS;

        while ((EPWM_MepCalibration_GetFlagStatus(EPWM1, EPWM_MEP_FLAG_INT)) != 1) {};

        return (EPWMx->HRMSTEP);
    }

    EDIS(EPWMx);
    return 0;
}

/**
  * @brief  Disable MEP SFO.
  * @param  EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableMEPSFO(EPWM_TypeDef* EPWMx)
{
    EALLOW(EPWMx);

    EPWMx->HRPWR &= ~EPWM_HRPPWR_MEPSFO_BITS;

    EDIS(EPWMx);
}


/**
  * @brief Sets the filter value of the TZ1-3 for the trip zone (TZ).
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param FILTER  The filter value(0~255).
  */
void EPWM_setTripZoneFilter(EPWM_TypeDef* EPWMx, uint8_t FILTER)
{
    EALLOW(EPWMx);

    EPWMx->TZSEL |= (FILTER << 16);

    EDIS(EPWMx);
}




/**
  * @brief     Clears the trip zone (TZ) flag specified
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneFlag  The trip zone flag to clear
  */
void EPWM_clearTripZone(EPWM_TypeDef* EPWMx, const EPWM_TripZoneFlag_e tripZoneFlag)
{
    EALLOW(EPWMx);

    EPWMx->TZCLR |= tripZoneFlag;

    EDIS(EPWMx);

}

/**
  * @brief     Decrement the dead band falling edge delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_decrementDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx)
{

    EPWMx->DBFED--;

}

/**
  * @brief     Decrement the dead band rising edge delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_decrementDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx)
{

    EPWMx->DBRED--;

}

/**
  * @brief     Disables auto conversion of delay line value
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableAutoConvert(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->HRCNFG &= ~EPWM_HRCNFG_AUTOCONV_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Enables the pulse width modulation (PWM) chopping
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableChopping(EPWM_TypeDef* EPWMx)
{

    EPWMx->PCCTL = (uint16_t)1;

}

/**
  * @brief     Disables the pulse width modulation (PWM) chopping
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableChopping(EPWM_TypeDef* EPWMx)
{

    EPWMx->PCCTL &= (~EPWM_PCCTL_CHPEN_BITS);

}

/**
  * @brief     Disables the pulse width modulation (PWM) counter loading from
    the phase register
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableCounterLoad(EPWM_TypeDef* EPWMx)
{

    EPWMx->TBCTL &= (~EPWM_TBCTL_PHSEN_BITS);

}

/**
  * @brief     Disables the pulse width modulation (PWM) deadband
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableDeadBand(EPWM_TypeDef* EPWMx)
{

    EPWMx->DBCTL = 0;

}

/**
  * @brief     Disables the pulse width modulation (PWM) deadband half cycle
    clocking
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableDeadBandHalfCycle(EPWM_TypeDef* EPWMx)
{

    EPWMx->DBCTL &= (~EPWM_DBCTL_HALFCYCLE_BITS);

}

/**
  * @brief     Disables the pulse width modulation (PWM) digital compare
    blanking window
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableDigitalCompareBlankingWindow(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->DCFCTL &= ~EPWM_DCFCTL_BLANKE_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Disables the pulse width modulation (PWM) digital compare
    blanking window inversion
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableDigitalCompareBlankingWindowInversion(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->DCFCTL &= ~EPWM_DCFCTL_BLANKINV_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Disables high resolution period control
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableHrPeriod(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->HRPCTL &= ~EPWM_HRPCTL_HRPE_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Disables high resolution phase synchronization
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableHrPhaseSync(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->HRPCTL &= ~EPWM_HRPCTL_TBPHSHRLOADE_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Disables MEP Calibration Off bit
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableMEPCalibrationOff(EPWM_TypeDef* EPWMx)
{
    EALLOW(EPWMx);

    EPWMx->HRPWR &= ~EPWM_HRPPWR_MEPOFF_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Disables the pulse width modulation (PWM) interrupt
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableInt(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETSEL &= (~EPWM_ETSEL_INTEN_BITS);

}

/**
  * @brief     Disables the pulse width modulation (PWM) start of conversion
    (SOC) B pulse generation
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableSocAPulse(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETSEL &= (~EPWM_ETSEL_SOCAEN_BITS);

}

/**
  * @brief     Disables the pulse width modulation (PWM) start of conversion
    (SOC) B pulse generation
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableSocBPulse(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETSEL &= (~EPWM_ETSEL_SOCBEN_BITS);

}

/**
  * @brief     Disables the pulse width modulation (PWM) trip zones
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_disableTripZones(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->TZSEL = 0;

    EDIS(EPWMx);

}

/**
  * @brief     Disables the pulse width modulation (PWM) trip zones interrupts
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param interruptSource  The interrupt source to disable
  */
void EPWM_disableTripZoneInt(EPWM_TypeDef* EPWMx, const EPWM_TripZoneFlag_e interruptSource)
{

    EALLOW(EPWMx);

    EPWMx->TZEINT &= ~interruptSource;

    EDIS(EPWMx);

}

/**
  * @brief     Disable the pulse width modulation (PWM) trip zone source
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param src        The pulse width modulation (PWM) trip zone source
  */
void EPWM_disableTripZoneSrc(EPWM_TypeDef* EPWMx, const EPWM_TripZoneSrc_e src)
{

    EALLOW(EPWMx);

    EPWMx->TZSEL &= (~src);

    EDIS(EPWMx);

}

/**
  * @brief     Enables auto conversion of delay line value
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableAutoConvert(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->HRCNFG |= EPWM_HRCNFG_AUTOCONV_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Enables the pulse width modulation (PWM) counter loading from
    the phase register
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableCounterLoad(EPWM_TypeDef* EPWMx)
{

    EPWMx->TBCTL |= EPWM_TBCTL_PHSEN_BITS;

}

/**
  * @brief     Enables the pulse width modulation (PWM) deadband half cycle
    clocking
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableDeadBandHalfCycle(EPWM_TypeDef* EPWMx)
{

    EPWMx->DBCTL |= (uint16_t)EPWM_DBCTL_HALFCYCLE_BITS;

}

/**
  * @brief     Enables the pulse width modulation (PWM) digital compare
    blanking window
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableDigitalCompareBlankingWindow(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->DCFCTL |= EPWM_DCFCTL_BLANKE_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Enables the pulse width modulation (PWM) digital compare
    blanking window inversion
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableDigitalCompareBlankingWindowInversion(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->DCFCTL |= EPWM_DCFCTL_BLANKINV_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Enables high resolution period control
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableHrPeriod(EPWM_TypeDef* EPWMx)
{
    EALLOW(EPWMx);

    EPWMx->HRPCTL |= EPWM_HRPCTL_HRPE_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Enables the pulse width modulation (PWM) interrupt
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableInt(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETSEL |= EPWM_ETSEL_INTEN_BITS;

}

/**
  * @brief     Enables high resolution phase synchronization
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableHrPhaseSync(EPWM_TypeDef* EPWMx)
{
    EALLOW(EPWMx);

    EPWMx->HRPCTL |= EPWM_HRPCTL_TBPHSHRLOADE_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Enables MEP Calibration Off bit
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableMEPCalibrationOff(EPWM_TypeDef* EPWMx)
{
    EALLOW(EPWMx);

    EPWMx->HRPWR |= EPWM_HRPPWR_MEPOFF_BITS;

    EDIS(EPWMx);

}

/**
  * @brief     Enables the pulse width modulation (PWM) start of conversion
    (SOC) A pulse generation
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableSocAPulse(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETSEL |= EPWM_ETSEL_SOCAEN_BITS;

}

/**
  * @brief     Enables the pulse width modulation (PWM) start of conversion
    (SOC) B pulse generation
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_enableSocBPulse(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETSEL |= (uint16_t)EPWM_ETSEL_SOCBEN_BITS;

}

/**
  * @brief     Enables the pulse width modulation (PWM) trip zones interrupts
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param interruptSource  The interrupt source to enable
  */
void EPWM_enableTripZoneInt(EPWM_TypeDef* EPWMx, const EPWM_TripZoneFlag_e interruptSource)
{

    EALLOW(EPWMx);

    EPWMx->TZEINT |= interruptSource;

    EDIS(EPWMx);

}

/**
  * @brief     Enable the pulse width modulation (PWM) trip zone source
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param src        The pulse width modulation (PWM) trip zone source
  */
void EPWM_enableTripZoneSrc(EPWM_TypeDef* EPWMx, const EPWM_TripZoneSrc_e src)
{

    EALLOW(EPWMx);

    EPWMx->TZSEL |= src;

    EDIS(EPWMx);

}

/**
  * @brief     Gets the pulse width modulation (PWM) deadband falling edge
    delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The delay
  */
uint16_t EPWM_getDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx)
{

    return (EPWMx->DBFED);
}

/**
  * @brief     Gets the pulse width modulation (PWM) deadband rising edge delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The delay
  */
uint16_t EPWM_getDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx)
{

    return (EPWMx->DBRED);
}

/**
  * @brief     Gets the pulse width modulation (PWM) interrupt event count
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The interrupt event count
  */
uint16_t EPWM_getIntCount(EPWM_TypeDef* EPWMx)
{
    uint16_t intCount;

    intCount = EPWMx->ETPS & EPWM_ETPS_INTCNT_BITS;

    return (intCount);
}

/**
  * @brief     Gets the pulse width modulation (PWM) start of conversion (SOC)
    A count
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The SOC A count
  */
uint16_t EPWM_getSocACount(EPWM_TypeDef* EPWMx)
{
    uint16_t intCount;

    intCount = EPWMx->ETPS & EPWM_ETPS_SOCACNT_BITS;

    intCount >>= 10;

    return (intCount);
}

/**
  * @brief     Gets the pulse width modulation (PWM) start of conversion (SOC)
    B count
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The SOC B count
  */
uint16_t EPWM_getSocBCount(EPWM_TypeDef* EPWMx)
{
    uint16_t intCount;

    intCount = EPWMx->ETPS & (uint16_t)EPWM_ETPS_SOCBCNT_BITS;

    intCount >>= 14;

    return (intCount);
}


EPWM_ShadowStatus_e EPWM_getShadowStatus_CmpA(EPWM_TypeDef* EPWMx)
{
    EPWM_ShadowStatus_e status;

    status = (EPWM_ShadowStatus_e)(EPWMx->CMPCTL & (EPWM_CMPCTL_SHDWAFULL_BITS));

    status >>= 5;

    return (status);
}


EPWM_ShadowStatus_e EPWM_getShadowStatus_CmpB(EPWM_TypeDef* EPWMx)
{
    EPWM_ShadowStatus_e status;

    status = (EPWM_ShadowStatus_e)(EPWMx->CMPCTL & (EPWM_CMPCTL_SHDWBFULL_BITS));

    status >>= 7;

    return (status);
}

/**
  * @brief     Set the High Resolution Control Mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param controlMode   The control mode HREPWM should use
  */
void EPWM_setHrControlMode(EPWM_TypeDef* EPWMx, const EPWM_HrControlMode_e controlMode)
{
    EALLOW(EPWMx);

    EPWMx->HRCNFG &= ~EPWM_HRCNFG_CTLMODE_BITS;

    EPWMx->HRCNFG |= controlMode;

    EDIS(EPWMx);

}

/**
  * @brief     Set the High Resolution Edge Mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param edgeMode   The edge mode HREPWM should use
  */
void EPWM_setHrEdgeMode(EPWM_TypeDef* EPWMx, const EPWM_HrEdgeMode_e edgeMode)
{
    EALLOW(EPWMx);

    EPWMx->HRCNFG &= ~EPWM_HRCNFG_EDGMODE_BITS;

    EPWMx->HRCNFG |= edgeMode;

    EDIS(EPWMx);

}

/**
  * @brief     Set the High Resolution Shadow Load Mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param shadowMode   The shadow load mode HREPWM should use
  */
void EPWM_setHrShadowMode(EPWM_TypeDef* EPWMx, const EPWM_HrShadowMode_e shadowMode)
{
    EALLOW(EPWMx);

    EPWMx->HRCNFG &= ~EPWM_HRCNFG_HRLOAD_BITS;

    EPWMx->HRCNFG |= shadowMode;

    EDIS(EPWMx);

}

/**
  * @brief     Increment the dead band falling edge delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_incrementDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx)
{
    EPWMx->DBFED++;

}

/**
  * @brief     Increment the dead band rising edge delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_incrementDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx)
{
    EPWMx->DBRED++;

}

/**
  * @brief     Initializes the pulse width modulation (PWM) object handle
  * @param pMemory  A pointer to the base address of the EPWM registers
  * @param numBytes The number of bytes allocated for the EPWM object, bytes
  * @retval    The pulse width modulation (PWM) object handle
  */
//EPWM_Handle EPWM_init(void *pMemory, const size_t numBytes)
//{
//    EPWM_TypeDef* EPWMx;
//
//    if(numBytes < sizeof(EPWM_TypeDef))
//    {
//        return((EPWM_Handle)NULL);
//    }
//
//    //
//    // assign the handle
//    //
//
//}


/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM A
    when the counter equals CMPA and the counter is decrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntDown_CmpA_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLA &= (~EPWM_AQCTL_CAD_BITS);

    EPWMx->AQCTLA |= (actionQual << 6);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM B
    when the counter equals CMPA and the counter is decrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntDown_CmpA_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLB &= (~EPWM_AQCTL_CAD_BITS);

    EPWMx->AQCTLB |= (actionQual << 6);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM A
    when the counter equals CMPB and the counter is decrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntDown_CmpB_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLA &= (~EPWM_AQCTL_CBD_BITS);

    EPWMx->AQCTLA |= (actionQual << 10);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM B
    when the counter equals CMPB and the counter is decrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntDown_CmpB_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLB &= (~EPWM_AQCTL_CBD_BITS);

    EPWMx->AQCTLB |= (actionQual << 10);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM A
    when the counter equals CMPA and the counter is incrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntUp_CmpA_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLA &= (~EPWM_AQCTL_CAU_BITS);

    EPWMx->AQCTLA |= (actionQual << 4);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM B
    when the counter equals CMPA and the counter is incrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntUp_CmpA_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLB &= (~EPWM_AQCTL_CAU_BITS);

    EPWMx->AQCTLB |= (actionQual << 4);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM A
    when the counter equals CMPB and the counter is incrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntUp_CmpB_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLA &= (~EPWM_AQCTL_CBU_BITS);

    EPWMx->AQCTLA |= (actionQual << 8);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM B
    when the counter equals CMPB and the counter is incrementing
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_CntUp_CmpB_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLB &= (~EPWM_AQCTL_CBU_BITS);

    EPWMx->AQCTLB |= (actionQual << 8);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM A
    when the counter equals the period
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_Period_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLA &= (~EPWM_AQCTL_PRD_BITS);

    EPWMx->AQCTLA |= (actionQual << 2);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM B
    when the counter equals the period
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_Period_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLB &= (~EPWM_AQCTL_PRD_BITS);

    EPWMx->AQCTLB |= (actionQual << 2);

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM A
    when the counter equals the zero
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_Zero_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLA &= (~EPWM_AQCTL_ZRO_BITS);

    EPWMx->AQCTLA |= actionQual;

}

/**
  * @brief     Sets the pulse width modulation (PWM) object action for EPWM B
    when the counter equals the zero
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param actionQual  The action qualifier
  */
void EPWM_setActionQual_Zero_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual)
{

    EPWMx->AQCTLB &= (~EPWM_AQCTL_ZRO_BITS);

    EPWMx->AQCTLB |= actionQual;

}

/**
  * @brief     Sets the pulse width modulation (PWM) chopping clock frequency
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param clkFreq    The clock frequency
  */
void EPWM_setChoppingClkFreq(EPWM_TypeDef* EPWMx, const EPWM_ChoppingClkFreq_e clkFreq)
{

    EPWMx->PCCTL &= (~EPWM_PCCTL_CHPFREQ_BITS);

    EPWMx->PCCTL |= clkFreq;

}

/**
  * @brief     Sets the pulse width modulation (PWM) chopping clock duty cycle
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param dutyCycle  The duty cycle
  */
void EPWM_setChoppingDutyCycle(EPWM_TypeDef* EPWMx, const EPWM_ChoppingDutyCycle_e dutyCycle)
{

    EPWMx->PCCTL &= (~EPWM_PCCTL_CHPDUTY_BITS);

    EPWMx->PCCTL |= dutyCycle;

}

/**
  * @brief     Sets the pulse width modulation (PWM) chopping clock pulse width
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pulseWidth  The pulse width
  */
void EPWM_setChoppingPulseWidth(EPWM_TypeDef* EPWMx, const EPWM_ChoppingPulseWidth_e pulseWidth)
{

    EPWMx->PCCTL &= (~EPWM_PCCTL_OSHTWTH_BITS);

    EPWMx->PCCTL |= pulseWidth;

}

/**
  * @brief     Sets the pulse width modulation (PWM) high speed clock divisor
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param clkDiv     The clock divisor
  */
void EPWM_setHighSpeedClkDiv(EPWM_TypeDef* EPWMx, const EPWM_HspClkDiv_e clkDiv)
{

    EPWMx->TBCTL &= (~EPWM_TBCTL_HSPCLKDIV_BITS);

    EPWMx->TBCTL |= clkDiv;

}

/**
  * @brief     Sets the pulse width modulation (PWM) clock divisor
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param clkDiv     The clock divisor
  */
void EPWM_setClkDiv(EPWM_TypeDef* EPWMx, const EPWM_ClkDiv_e clkDiv)
{

    EPWMx->TBCTL &= (~EPWM_TBCTL_CLKDIV_BITS);

    EPWMx->TBCTL |= clkDiv;

}

/**
  * @brief     Sets the pulse width modulation (PWM) count
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param count  The count
  */
void EPWM_setCount(EPWM_TypeDef* EPWMx, const uint16_t count)
{

    EPWMx->TBCTR = count;

}

/**
  * @brief     Sets the pulse width modulation (PWM) counter mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param counterMode  The count mode
  */
void EPWM_setCounterMode(EPWM_TypeDef* EPWMx, const EPWM_CounterMode_e counterMode)
{

    EPWMx->TBCTL &= (~EPWM_TBCTL_CTRMODE_BITS);

    EPWMx->TBCTL |= counterMode;

}

/**
  * @brief    Sets the pulse width modulation (PWM) deadband falling edge delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param delay      The delay
  */
void EPWM_setDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx, const uint16_t delay)
{

    EPWMx->DBFED |= delay;

}

/**
  * @brief     Sets the pulse width modulation (PWM) deadband input mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param inputMode  The input mode
  */
void EPWM_setDeadBandInputMode(EPWM_TypeDef* EPWMx, const EPWM_DeadBandInputMode_e inputMode)
{

    EPWMx->DBCTL &= (~EPWM_DBCTL_INMODE_BITS);

    EPWMx->DBCTL |= inputMode;

}

/**
  * @brief     Sets the pulse width modulation (PWM) deadband output mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param outputMode  The output mode
  */
void EPWM_setDeadBandOutputMode(EPWM_TypeDef* EPWMx, const EPWM_DeadBandOutputMode_e outputMode)
{

    EPWMx->DBCTL &= (~EPWM_DBCTL_OUTMODE_BITS);

    EPWMx->DBCTL |= outputMode;

}

/**
  * @brief     Sets the pulse width modulation (PWM) deadband polarity
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param polarity   The polarity
  */
void EPWM_setDeadBandPolarity(EPWM_TypeDef* EPWMx, const EPWM_DeadBandPolarity_e polarity)
{

    EPWMx->DBCTL &= (~EPWM_DBCTL_POLSEL_BITS);

    EPWMx->DBCTL |= polarity;

}

/**
  * @brief     Sets the pulse width modulation (PWM) deadband rising edge delay
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param delay      The delay
  */
void EPWM_setDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx, const uint16_t delay)
{

    EPWMx->DBRED |= delay;

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare filter
    source
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param input      The filter's source
  */
void EPWM_setDigitalCompareFilterSource(EPWM_TypeDef* EPWMx, const EPWM_DigitalCompare_FilterSrc_e input)
{
    EALLOW(EPWMx);

    EPWMx->DCFCTL &= ~EPWM_DCFCTL_SRCSEL_BITS;

    EPWMx->DCFCTL |= input;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare blanking
    pulse
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pulseSelect The pulse selection
  */
void EPWM_setDigitalCompareBlankingPulse(EPWM_TypeDef* EPWMx, const EPWM_DigitalCompare_PulseSel_e pulseSelect)
{
    EALLOW(EPWMx);

    EPWMx->DCFCTL &= ~EPWM_DCFCTL_PULSESEL_BITS;

    EPWMx->DCFCTL |= pulseSelect << 4;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare filter
    offset
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param offset     The offset
  */
void EPWM_setDigitalCompareFilterOffset(EPWM_TypeDef* EPWMx, const uint16_t offset)
{
    EPWMx->DCFOFFSET = offset;

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare filter
    offset
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param window     The window
  */
void EPWM_setDigitalCompareFilterWindow(EPWM_TypeDef* EPWMx, const uint16_t window)
{
    EPWMx->DCFWINDOW = window;

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare input
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param input      Comparator input to change
  * @param inputSel   Input selection for designated input
  */
void EPWM_setDigitalCompareInput(EPWM_TypeDef* EPWMx, const EPWM_DigitalCompare_Input_e input, const EPWM_DigitalCompare_InputSel_e inputSel)
{
    EALLOW(EPWMx);

    EPWMx->DCTRIPSEL &= ~(0x000F << input);

    EPWMx->DCTRIPSEL |= (inputSel << input);

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare A event 1
    source parameters
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param selectFilter   Select filter output if true
  * @param disableSync    Asynchronous if true
  * @param enableSoc      Enable SOC generation if true
  * @param generateSync   Generate SYNC if true
  */
void EPWM_setDigitalCompareAEvent1(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync, const uint16_t  enableSoc, const uint16_t  generateSync)
{
    EALLOW(EPWMx);

    EPWMx->DCACTL &= ~0x000F;

    EPWMx->DCACTL |= selectFilter | (disableSync << 1) | (enableSoc << 2) |
                     (generateSync << 3);

    EDIS(EPWMx);

}


/**
  * @brief     Sets the pulse width modulation (PWM) digital compare A event 2
    source parameters
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param selectFilter   Select filter output if true
  * @param disableSync    Asynchronous if true
  */
void EPWM_setDigitalCompareAEvent2(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync)
{

    EALLOW(EPWMx);

    EPWMx->DCACTL &= ~0x0300;

    EPWMx->DCACTL |= (selectFilter << 8) | (disableSync << 9) ;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare B event 1
    source parameters
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param selectFilter   Select filter output if true
  * @param disableSync    Asynchronous if true
  * @param enableSoc      Enable SOC generation if true
  * @param generateSync   Generate SYNC if true
  */
void EPWM_setDigitalCompareBEvent1(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync, const uint16_t  enableSoc, const uint16_t  generateSync)
{

    EALLOW(EPWMx);

    EPWMx->DCBCTL &= ~0x000F;

    EPWMx->DCBCTL |= selectFilter | (disableSync << 1) | (enableSoc << 2) |
                     (generateSync << 3);

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) digital compare B event 2
    source parameters
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param selectFilter   Select filter output if true
  * @param disableSync    Asynchronous if true
  */
void EPWM_setDigitalCompareBEvent2(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync)
{
    EALLOW(EPWMx);

    EPWMx->DCBCTL &= ~0x0300;

    EPWMx->DCBCTL |= (selectFilter << 8) | (disableSync << 9) ;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) interrupt mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param intMode    The interrupt mode
  */
void EPWM_setIntMode(EPWM_TypeDef* EPWMx, const EPWM_IntMode_e intMode)
{

    EPWMx->ETSEL &= (~EPWM_ETSEL_INTSEL_BITS);

    EPWMx->ETSEL |= intMode;

}

/**
  * @brief     Sets the pulse width modulation (PWM) interrupt period
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param intPeriod  The interrupt period
  */
void EPWM_setIntPeriod(EPWM_TypeDef* EPWMx, const EPWM_IntPeriod_e intPeriod)
{

    EPWMx->ETPS &= (~EPWM_ETPS_INTPRD_BITS);

    EPWMx->ETPS |= intPeriod;

}

/**
  * @brief     Sets the pulse width modulation (PWM) load mode for CMPA
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param loadMode   The load mode
  */
void EPWM_setLoadMode_CmpA(EPWM_TypeDef* EPWMx, const EPWM_LoadMode_e loadMode)
{

    EPWMx->CMPCTL &= (~EPWM_CMPCTL_LOADAMODE_BITS);

    EPWMx->CMPCTL |= loadMode;

}

/**
  * @brief     Sets the pulse width modulation (PWM) load mode for CMPB
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param loadMode   The load mode
  */
void EPWM_setLoadMode_CmpB(EPWM_TypeDef* EPWMx, const EPWM_LoadMode_e loadMode)
{

    EPWMx->CMPCTL &= (~EPWM_CMPCTL_LOADBMODE_BITS);

    EPWMx->CMPCTL |= (loadMode << 2);

}

/**
  * @brief     Sets the pulse width modulation (PWM) period
  *            Initialize the Time-Base Period Register (TBPRD).  These bits determine
  *            the period of the time-base counter.
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param period     The period
  */
void EPWM_setPeriod(EPWM_TypeDef* EPWMx, const uint16_t period)
{

    EPWMx->TBPRD = period;

}

/**
  * @brief     Sets the pulse width modulation (PWM) high resolution period
  *              Initialize the Time-Base Period Register (TBPRD).  These bits determine
  *              the period of the time-base counter.
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param period     The period
  */
void EPWM_setPeriodHr(EPWM_TypeDef* EPWMx, const uint16_t period)
{

    EALLOW(EPWMx);

    EPWMx->TBPRDHR = period;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) phase
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param phase      The phase
  */
void EPWM_setPhase(EPWM_TypeDef* EPWMx, const uint16_t phase)
{

    EPWMx->TBPHS = phase;

}

/**
  * @brief     Sets the pulse width modulation (PWM) phase direction
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param phaseDir   The phase direction
  */
void EPWM_setPhaseDir(EPWM_TypeDef* EPWMx, const EPWM_PhaseDir_e phaseDir)
{

    EPWMx->TBCTL &= (~EPWM_TBCTL_PHSDIR_BITS);

    EPWMx->TBCTL |= phaseDir;

}

/**
  * @brief     Sets the pulse width modulation (PWM) period load mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param periodLoad  The period load mode
  */
void EPWM_setPeriodLoad(EPWM_TypeDef* EPWMx, const EPWM_PeriodLoad_e periodLoad)
{

    EPWMx->TBCTL &= (~EPWM_TBCTL_PRDLD_BITS);

    EPWMx->TBCTL |= periodLoad;

}

/**
  * @brief     Sets the pulse width modulation (PWM) run mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param runMode    The run mode
  */
//void EPWM_setRunMode(EPWM_TypeDef* EPWMx, const EPWM_RunMode_e runMode)
//{
//
//    EPWMx->TBCTL &= (~EPWM_TBCTL_FREESOFT_BITS);
//
//    EPWMx->TBCTL |= runMode;
//
//}

/**
  * @brief     Sets the pulse width modulation (PWM) start of conversion (SOC)
    A interrupt period
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param intPeriod  The interrupt period
  */
void EPWM_setSocAPeriod(EPWM_TypeDef* EPWMx, const EPWM_SocPeriod_e intPeriod)
{

    EPWMx->ETPS &= (~EPWM_ETPS_SOCAPRD_BITS);

    EPWMx->ETPS |= (intPeriod << 8);

}

/**
  * @brief     Sets the pulse width modulation (PWM) start of conversion (SOC)
    A interrupt pulse source
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pulseSrc   The interrupt pulse source
  */
void EPWM_setSocAPulseSrc(EPWM_TypeDef* EPWMx, const EPWM_SocPulseSrc_e pulseSrc)
{

    EPWMx->ETSEL &= (~EPWM_ETSEL_SOCASEL_BITS);

    EPWMx->ETSEL |= (pulseSrc << 8);

}

/**
  * @brief     Sets the pulse width modulation (PWM) start of conversion (SOC)
    B interrupt period
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param intPeriod  The interrupt period
  */
void EPWM_setSocBPeriod(EPWM_TypeDef* EPWMx, const EPWM_SocPeriod_e intPeriod)
{

    EPWMx->ETPS &= (~EPWM_ETPS_SOCBPRD_BITS);

    EPWMx->ETPS |= (intPeriod << 12);

}

/**
  * @brief     Sets the pulse width modulation (PWM) start of conversion (SOC)
    B interrupt pulse source
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pulseSrc   The interrupt pulse source
  */
void EPWM_setSocBPulseSrc(EPWM_TypeDef* EPWMx, const EPWM_SocPulseSrc_e pulseSrc)
{

    EPWMx->ETSEL &= (~EPWM_ETSEL_SOCBSEL_BITS);

    EPWMx->ETSEL |= (pulseSrc << 12);

}

/**
  * @brief     Sets the pulse width modulation (PWM) shadow mode for CMPA
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param shadowMode  The shadow mode
  */
void EPWM_setShadowMode_CmpA(EPWM_TypeDef* EPWMx, const EPWM_ShadowMode_e shadowMode)
{

    EPWMx->CMPCTL &= (~EPWM_CMPCTL_SHDWAMODE_BITS);

    EPWMx->CMPCTL |= (shadowMode << 4);

}

/**
  * @brief     Sets the pulse width modulation (PWM) shadow mode for CMPB
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param shadowMode  The shadow mode
  */
void EPWM_setShadowMode_CmpB(EPWM_TypeDef* EPWMx, const EPWM_ShadowMode_e shadowMode)
{

    EPWMx->CMPCTL &= (~EPWM_CMPCTL_SHDWBMODE_BITS);

    EPWMx->CMPCTL |= (shadowMode << 6);

}

/**
  * @brief     Sets the pulse width modulation (PWM) software sync
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
void EPWM_setSwSync(EPWM_TypeDef* EPWMx)
{

    EPWMx->TBCTL |= 1 << 6;

}

/**
  * @brief     Force Synchronization
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
inline void EPWM_forceSync(EPWM_TypeDef* EPWMx)
{

    EPWMx->TBCTL |= EPWM_TBCTL_SWFSYNC_BITS;

}


/**
  * @brief     Sets the pulse width modulation (PWM) sync mode
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param syncMode   The sync mode
  */
void EPWM_setSyncMode(EPWM_TypeDef* EPWMx, const EPWM_SyncMode_e syncMode)
{

    EPWMx->TBCTL &= (~EPWM_TBCTL_SYNCOSEL_BITS);

    EPWMx->TBCTL |= syncMode;

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone digital compare
    event select for Digital Compare Output A Event 1 (DCAEVT1)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneEvent  The trip zone digital compare event
  */
void EPWM_setTripZoneDCEventSelect_DCAEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent)
{

    EALLOW(EPWMx);

    EPWMx->TZDCSEL &= (~EPWM_TZDCSEL_DCAEVT1_BITS);

    EPWMx->TZDCSEL |= tripZoneEvent << 0;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone digital compare
    event select for Digital Compare Output A Event 2 (DCAEVT2)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneEvent  The trip zone digital compare event
  */
void EPWM_setTripZoneDCEventSelect_DCAEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent)
{

    EALLOW(EPWMx);

    EPWMx->TZDCSEL &= (~EPWM_TZDCSEL_DCAEVT2_BITS);

    EPWMx->TZDCSEL |= tripZoneEvent << 3;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone digital compare
    event select for Digital Compare Output B Event 1 (DCBEVT1)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneEvent  The trip zone digital compare event
  */
void EPWM_setTripZoneDCEventSelect_DCBEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent)
{

    EALLOW(EPWMx);

    EPWMx->TZDCSEL &= (~EPWM_TZDCSEL_DCBEVT1_BITS);

    EPWMx->TZDCSEL |= tripZoneEvent << 6;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone digital compare
    event select for Digital Compare Output B Event 2 (DCBEVT2)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneEvent  The trip zone digital compare event
  */
void EPWM_setTripZoneDCEventSelect_DCBEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent)
{

    EALLOW(EPWMx);

    EPWMx->TZDCSEL &= (~EPWM_TZDCSEL_DCBEVT2_BITS);

    EPWMx->TZDCSEL |= tripZoneEvent << 9;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone state for
    Digital Compare Output A Event 1 (DCAEVT1)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneState  The trip zone state
  */
void EPWM_setTripZoneState_DCAEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState)
{

    EALLOW(EPWMx);

    EPWMx->TZCTL &= (~EPWM_TZCTL_DCAEVT1_BITS);

    EPWMx->TZCTL |= tripZoneState << 4;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone state for
    Digital Compare Output A Event 2 (DCAEVT1)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneState  The trip zone state
  */
void EPWM_setTripZoneState_DCAEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState)
{

    EALLOW(EPWMx);

    EPWMx->TZCTL &= (~EPWM_TZCTL_DCAEVT2_BITS);

    EPWMx->TZCTL |= tripZoneState << 6;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone state for
    Digital Compare Output B Event 1 (DCBEVT1)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneState  The trip zone state
  */
void EPWM_setTripZoneState_DCBEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState)
{

    EALLOW(EPWMx);

    EPWMx->TZCTL &= (~EPWM_TZCTL_DCBEVT1_BITS);

    EPWMx->TZCTL |= tripZoneState << 8;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone state for
    Digital Compare Output B Event 2 (DCBEVT1)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneState  The trip zone state
  */
void EPWM_setTripZoneState_DCBEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState)
{

    EALLOW(EPWMx);

    EPWMx->TZCTL &= (~EPWM_TZCTL_DCBEVT2_BITS);

    EPWMx->TZCTL |= tripZoneState << 10;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone state for Output
    A (TZA)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneState  The trip zone state
  */
void EPWM_setTripZoneState_TZA(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState)
{

    EALLOW(EPWMx);

    EPWMx->TZCTL &= (~EPWM_TZCTL_TZA_BITS);

    EPWMx->TZCTL |= tripZoneState << 0;

    EDIS(EPWMx);

}

/**
  * @brief     Sets the pulse width modulation (PWM) trip zone state for Output
    B (TZB)
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param tripZoneState  The trip zone state
  */
void EPWM_setTripZoneState_TZB(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState)
{

    EALLOW(EPWMx);

    EPWMx->TZCTL &= (~EPWM_TZCTL_TZB_BITS);

    EPWMx->TZCTL |= tripZoneState << 2;

    EDIS(EPWMx);

}







/**
  * @brief     Clears the Mep Calibration interrupt flag
  * @param EPWMx  The pulse width modulation (PWM) object handle
  */
inline void EPWM_clearMepFlag(EPWM_TypeDef* EPWMx)
{
    EPWMx->MEPCLR = EPWM_MEP_INT_BITS;
}


/**
  * @brief     Clears the pulse width modulation (PWM) interrupt flag
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
inline void EPWM_clearIntFlag(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETCLR = EPWM_ETCLR_INT_BITS;

}


/**
  * @brief     Clears the pulse width modulation (PWM) one shot trip
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
inline void EPWM_clearOneShotTrip(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->TZCLR = EPWM_TZCLR_OST_BITS;

    EDIS(EPWMx);

}


/**
  * @brief     Clears the pulse width modulation (PWM) start of conversion
    (SOC) A flag
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
inline void EPWM_clearSocAFlag(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETCLR = EPWM_ETCLR_SOCA_BITS;

}


/**
  * @brief     Clears the pulse width modulation (PWM) start of conversion
    (SOC) B flag
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
inline void EPWM_clearSocBFlag(EPWM_TypeDef* EPWMx)
{

    EPWMx->ETCLR = EPWM_ETCLR_SOCB_BITS;

}


/**
  * @brief     Gets the pulse width modulation (PWM) period value
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The pwm period value
  */
inline uint16_t EPWM_getPeriod(EPWM_TypeDef* EPWMx)
{

    return (EPWMx->TBPRD);
}


/**
  * @brief     Gets the pulse width modulation (PWM) data value from the
    Counter Compare A hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The EPWM compare data value
  */
inline uint16_t EPWM_getCmpA(EPWM_TypeDef* EPWMx)
{

    return (EPWMx->CMPA);
}


/**
  * @brief     Gets the pulse width modulation (PWM) data value from the
    Counter Compare A  Hr hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The EPWM compare high resolution data value
  */
inline uint16_t EPWM_getCmpAHr(EPWM_TypeDef* EPWMx)
{

    return (EPWMx->CMPAHR);
}


/**
  * @brief     Gets the pulse width modulation (PWM) data value from the
    Counter Compare B hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @retval    The EPWM compare data value
  */
inline uint16_t EPWM_getCmpB(EPWM_TypeDef* EPWMx)
{

    return (EPWMx->CMPB);
}


/**
  * @brief     Sets the pulse width modulation (PWM) one shot trip
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  */
inline void EPWM_setOneShotTrip(EPWM_TypeDef* EPWMx)
{

    EALLOW(EPWMx);

    EPWMx->TZFRC |= EPWM_TZFRC_OST_BITS;

    EDIS(EPWMx);

}


/**
  * @brief     Writes the pulse width modulation (PWM) data value to the
    Counter Compare A hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pwmData    The EPWM data value
  */
inline void EPWM_write_CmpA(EPWM_TypeDef* EPWMx, const int16_t pwmData)
{

    int16_t value;
    uint16_t period = EPWMx->TBPRD;
    int32_t tmp;

    /* Compute the compare A (Q0) from the related duty cycle ratio (Q15) */
    tmp = (int32_t)period * (int32_t)(pwmData);      // Q15 = Q0*Q15

    /* Q0 = (Q15->Q0)/2 + (Q0/2) */
    value = (int16_t)(tmp >> 16) + (int16_t)(period >> 1);

    EPWMx->CMPA = value;

}


/**
  * @brief     Writes the pulse width modulation (PWM) data value to the
    Counter Compare A hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pwmData    The EPWM data value
  */
inline void EPWM_setCmpA(EPWM_TypeDef* EPWMx, const uint16_t pwmData)
{

    EPWMx->CMPA = pwmData;

}


/**
  * @brief     Writes the pulse width modulation (PWM) data value to the
    Counter Compare A Hr hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pwmData    The EPWM high resolution data value
  */
inline void EPWM_setCmpAHr(EPWM_TypeDef* EPWMx, const uint16_t pwmData)
{

    EPWMx->CMPAHR = (pwmData << 8);

}


/**
  * @brief     Writes the pulse width modulation (PWM) data value to the
    Counter Compare B hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pwmData    The EPWM data value
  */
inline void EPWM_write_CmpB(EPWM_TypeDef* EPWMx, const int16_t pwmData)
{

    int16_t value;
    uint16_t period = EPWMx->TBPRD;
    int32_t tmp;

    /* Compute the compare A (Q0) from the related duty cycle ratio (Q15) */
    tmp = (int32_t)period * (int32_t)(pwmData);       // Q15 = Q0*Q15

    /* Q0 = (Q15->Q0)/2 + (Q0/2) */
    value = (int16_t)(tmp >> 16) + (int16_t)(period >> 1);

    EPWMx->CMPB = value;

}


/**
  * @brief     Writes the pulse width modulation (PWM) data value to the
    Counter Compare B hardware
  * @param EPWMx  where x can be 1 to 4 to select the EPWM peripheral
  * @param pwmData    The EPWM data value
  */
inline void EPWM_setCmpB(EPWM_TypeDef* EPWMx, const uint16_t pwmData)
{

    EPWMx->CMPB = pwmData;

}





/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
