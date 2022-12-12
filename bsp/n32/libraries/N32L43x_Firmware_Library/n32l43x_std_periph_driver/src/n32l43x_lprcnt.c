/** ----------------------------------------------------------------------------
 *         Nationz Technology Software Support  -  NATIONZ  -
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022, Nationz Corporation  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
 *
 * Nationz's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONZ "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
 * -----------------------------------------------------------------------------
 */

/** ****************************************************************************
 * @copyright      Nationz Co.,Ltd
 *                 Copyright (c) 2019 All Rights Reserved
 *******************************************************************************
 * @file     n32l43x_LPRCNT.c
 * @author
 * @date
 * @version  v1.2.0
 * @brief
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "n32l43x_LPRCNT.h"
//nclude "n32l43x_rcc.h"
//#include "n32l43x.h"
#include "n32l43x_exti.h"
#include "misc.h"
/** @addtogroup n32l43x_StdPeriph_Driver
  * @{
  */

/** @defgroup LPRCNT
  * @brief LPRCNT driver modules
  * @{
  */

/** @defgroup LPRCNT_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */




/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/**
  * @brief clear LPRCNT interrupt flag funtion.
  * @param  intflag: include LPRCNT interrupt flag
  *   This parameter can be one of the following values:
  *     @arg CALIBRATION_INT_FLAG
  *     @arg REPORT_INT_FLAG
  *     @arg ALARM_INT_FLAG
  * @retval None
  */
void LPRCNT_ClrIntBit(uint32_t IntFlag)
{
    LPRCNT->INTSTS |= IntFlag;
}

/**
 * @brief  Checks whether the specified LPRCNT interrupt has occurred or not.
 * @param LPRCNT_INT specifies the LPRCNT interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg CALIBRATION_INT_FLAG   Calibration mode damped oscillation interrupt.
 *     @arg REPORT_INT_FLAG        Report interrupt.
 *     @arg ALARM_INT_FLAG         Alarm interrupt .
 * @return The new state of LPRCNT_INT (SET or RESET).
 */
INTStatus LPRCNT_GetIntSts(uint32_t Int)
{
    INTStatus bitstatus = RESET;
    uint32_t Temp = 0;

    Temp  = LPRCNT->INTSTS ;
    Temp  &= 0x00070000;
    if (Temp == Int)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;

}
/**
  * @brief LPRCNT interrupt funtion.
  * @param  MODE_IE: include LPRCNT interrupt
  *   This parameter can be one of the following values:
  *     @arg CALIBRATION_INT
  *     @arg REPORT_INT
  *     @arg ALARM_INT
  * @param  NewState: open or disable
  *     @arg DISABLE
  *     @arg ENABLE
  * @retval None
  */
void LPRCNT_IntEn(uint32_t Mode ,FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        LPRCNT->CTRL |= Mode;
    }
    else
    {
        LPRCNT->CTRL &= ~Mode;
    }
}
/**
  * @brief  configure per channel sensor detection time.
  * @param  ch: sensor channel .
  * @param  vibrationtime: comparator processing duration time.
  * @param  dischargetime: discharge duration time.
  * @param  chargetime: power charge duration time.
  * @retval None
  */
void CfgChannelTime(uint8_t Ch,uint8_t VibrationTime ,uint8_t DischargeTime,uint8_t  ChargeTime )
{
    uint32_t Temp = 0;
    switch (Ch)
    {
       case CHANNEL_0 :
            Temp = LPRCNT->CH0CFG1;
            Temp &= CLEAR_TIME_VALE;
            Temp |= (uint32_t)((VibrationTime << 16) | (DischargeTime << 8) | (ChargeTime));
            LPRCNT->CH0CFG1 = Temp;
            break;
       case CHANNEL_1 :
            Temp = LPRCNT->CH1CFG1;
            Temp &= CLEAR_TIME_VALE;
            Temp |= (uint32_t)((VibrationTime << 16) | (DischargeTime << 8) | (ChargeTime));
            LPRCNT->CH1CFG1 = Temp;
            break;
       case CHANNEL_2 :
            Temp = LPRCNT->CH2CFG1;
            Temp &= CLEAR_TIME_VALE;
            Temp |= (uint32_t)((VibrationTime << 16) | (DischargeTime << 8) | (ChargeTime));
            LPRCNT->CH2CFG1 = Temp;
            break;
       default: break ;
    }
}

/**
  * @brief  get the comparator processing duration time.
  * @param  ch: sensor channel .
  * @retval duration time
  */
uint8_t GetVibrationTime(uint8_t Ch)
{
    uint8_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = (LPRCNT->CH0CFG1 >> 16);
            break;
        case CHANNEL_1 :
            Temp = (LPRCNT->CH1CFG1 >> 16);
            break;
        case CHANNEL_2 :
            Temp = (LPRCNT->CH2CFG1 >> 16);
            break;
    }
    return  Temp;
}
/**
  * @brief  get discharge duration time.
  * @param  ch: sensor channel .
  * @retval discharge duration time
  */
uint8_t GetDischargeTime(uint8_t Ch)
{
    uint8_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = ((LPRCNT->CH0CFG1 >> 8) & 0x3f);
            break;
        case CHANNEL_1 :
            Temp = ((LPRCNT->CH1CFG1 >> 8) & 0x3f);
            break;
        case CHANNEL_2 :
            Temp = ((LPRCNT->CH2CFG1 >> 8) & 0x3f);
            break;
    }
    return  Temp;
}
/**
  * @brief  get charge duration time.
  * @param  ch: sensor channel .
  * @retval charge duration time
  */
uint8_t GetChargeTime(uint8_t Ch)
{
    uint8_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = (LPRCNT->CH0CFG1 & 0x3f);
            break;
        case CHANNEL_1 :
            Temp = (LPRCNT->CH1CFG1 & 0x3f);
            break;
        case CHANNEL_2 :
            Temp = (LPRCNT->CH2CFG1 & 0x3f);
            break;
    }
    return  Temp;
}
/**
  * @brief  configure per channel sensor detection threshold.
  * @param  ch: sensor channel .
  * @param  dacreference: DAC reference value for comparator.
  * @retval None
  */
void CfgChannelDacRefVol(uint8_t Ch,uint8_t DacRef)
{
    uint32_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = LPRCNT->CH0CFG0;
            Temp &= (~LPRCNT_CH0CFG0_DACREF);
            Temp |= (uint32_t)(DacRef <<16);
            LPRCNT->CH0CFG0 = Temp;
            break;
        case CHANNEL_1 :
            Temp = LPRCNT->CH1CFG0;
            Temp &= (~LPRCNT_CH1CFG0_DACREF);
            Temp |= (uint32_t)(DacRef <<16);
            LPRCNT->CH1CFG0 = Temp;
            break;
        case CHANNEL_2 :
            Temp = LPRCNT->CH2CFG0;
            Temp &= (~LPRCNT_CH2CFG0_DACREF);
            Temp |= (uint32_t)(DacRef <<16);
            LPRCNT->CH2CFG0 = Temp;
            break;
        default:
            break ;
    }

}
/**
  * @brief  get the DAC reference voltage.
  * @param  ch: sensor channel .
  * @retval DAC reference voltage values,Temp <= 64
  */
uint8_t GetDacRefVol(uint8_t Ch)
{
    uint8_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = ((LPRCNT->CH0CFG0 >> 16) & 0x3f);
            break;
        case CHANNEL_1 :
            Temp = ((LPRCNT->CH1CFG0 >> 16) & 0x3f);
            break;
        case CHANNEL_2 :
            Temp = ((LPRCNT->CH2CFG0 >> 16) & 0x3f);
            break;
    }
    return  Temp;
}

/**
  * @brief  configure per channel sensor detection threshold.
  * @param  ch: sensor channel .
  * @param  undampedTh: undamped threshold.
  * @param  dampedTh: damped threshold.
  * @retval None
  */
void CfgChannelThr(uint8_t Ch, uint8_t UndampedTh, uint8_t DampedTh)
{
    uint32_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = LPRCNT->CH0CFG0;
            Temp &= CLEAR_TH_VALE;
            Temp |= (uint32_t)((UndampedTh <<8) | DampedTh);
            LPRCNT->CH0CFG0 = Temp;
            break;
        case CHANNEL_1 :
            Temp = LPRCNT->CH1CFG0;
            Temp &= CLEAR_TH_VALE;
            Temp |= (uint32_t)((UndampedTh <<8) | DampedTh);
            LPRCNT->CH1CFG0 = Temp;
            break;
        case CHANNEL_2 :
            Temp = LPRCNT->CH2CFG0;
            Temp &= CLEAR_TH_VALE;
            Temp |= (uint32_t)((UndampedTh <<8) | DampedTh);
            LPRCNT->CH2CFG0 = Temp;
            break;
      default: break ;
    }
}

/**
  * @brief  get undamped threshold.
  * @param  ch: sensor channel .
  * @retval undamped threshold.
  */
uint8_t GetUndampedTh(uint8_t Ch)
{
    uint8_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = (LPRCNT->CH0CFG0 >> 8);
            break;
        case CHANNEL_1 :
            Temp = (LPRCNT->CH1CFG0 >> 8);
            break;
        case CHANNEL_2 :
            Temp = (LPRCNT->CH2CFG0 >> 8);
            break;
    }
    return  Temp;
}
/**
  * @brief  get damped threshold.
  * @param  ch: sensor channel .
  * @retval damped threshold.
  */
uint8_t GetDampedTh(uint8_t Ch)
{
    uint8_t Temp = 0;
    switch (Ch)
    {
        case CHANNEL_0 :
            Temp = (LPRCNT->CH0CFG0);
            break;
        case CHANNEL_1 :
            Temp = (LPRCNT->CH1CFG0);
            break;
        case CHANNEL_2 :
            Temp = (LPRCNT->CH2CFG0);
            break;
    }
    return  Temp;
}
/**
  * @brief MSI clock prescale.
  * @param  div: division factor
  *   This parameter can be one of the following values:
  *     @arg LPRCNT_PRESCALER_DIV1
  *     @arg LPRCNT_PRESCALER_DIV2
  *     @arg LPRCNT_PRESCALER_DIV4
  *     @arg LPRCNT_PRESCALER_DIV8
  * @retval None
  */
void SetMsiClkPrescale(uint32_t Div)
{
    uint32_t Temp = 0;
    Temp = LPRCNT->CTRL;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CTRL_CLKDIV);
    Temp |= Div;
    LPRCNT->CTRL = Temp;
}

/**
  * @brief  get the Circle value .
  * @param  ch: there are three state mode
  *   This parameter can be one of the following values:
  * @retval the ratation Circle value
  */

uint16_t GetRotationCircle(void)
{
    uint16_t Temp;
    Temp  = (uint16_t)LPRCNT->INTSTS;
    return Temp ;

}
/**
  * @brief  get the user set circle value .
  *   This parameter can be one of the following values:
  * @retval the set ratation Circle value
  */

uint16_t GetSetRcnt(void)
{
    uint16_t Temp;
    Temp  = (uint16_t)LPRCNT->CTRL;
    return Temp ;
}
/**
  * @brief clear the RCNT circle.
  * @param  None
  * @retval None
  */
void ClrRcntCircle(void)
{
    uint32_t Temp;
     Temp = LPRCNT->CMD;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CMD_CLRCNT);
    Temp |= LPRCNT_CMD_CLRCNT;
    LPRCNT->CMD = Temp;
}
/**
  * @brief when the setting number is reach ,it is will creat a overflow interrupt.
  * @param  Circle: the rotating Circle number
  * @retval None
  */
void SetAutoReportCircle(uint16_t Circle)
{
    uint32_t Temp = 0;
    uint16_t Cnt = 0;
    //when set the circle numbers,need add the lase numbers
    Cnt = GetRotationCircle();
    Temp = LPRCNT->CTRL;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CTRL_RPTTH);
    Temp |= (uint32_t)(Circle + Cnt);
    LPRCNT->CTRL = Temp;

}
#if  0
/**
  * @brief when the setting number is reach ,it is will creat a overflow interrupt.
  * @param  Circle: the rotating Circle number
  * @retval None
  */
void SetAutoReportCircle(uint16_t Circle)
{
    uint32_t Temp = 0;
    Temp = LPRCNT->CTRL;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CTRL_RPTTH);
    Temp |= (uint32_t)Circle;
    LPRCNT->CTRL = Temp;
}
#endif
/**
  * @brief enable to auto detect  comparator stop.
  * @param  CMD: ENABLE or DISABLE
  * @retval None
  */
void SetAutoDetectEnale(FunctionalState NewState )
{
    uint32_t Temp = 0;
    Temp = LPRCNT->CTRL;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CTRL_CMPAUT);
    Temp |= (uint32_t)(NewState <<23);
    LPRCNT->CTRL = Temp;
}
/**
  * @brief set auto detect  comparator stop need wait period.
  * @param  per: AUTODETPERIOD4 or AUTODETPERIOD8
  * @retval None
  */
void SetAutoDetectPeriod(bool per)
{
    uint32_t Temp = 0;
    Temp = LPRCNT->CAL3;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CAL3_CMP_AUTO_MODE);
    Temp |= (uint32_t)(per <<6);
    LPRCNT->CAL3 = Temp;
}
/**
  * @brief set auto to charge by DAC.
  * @param  En: ENABLE or DISABLE
  * @retval None
  */
void SetPwrAutoCharge(bool En)
{
    uint32_t Temp = 0;
    Temp = LPRCNT->CAL3;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CAL3_PWR_DUR_EN);
    Temp |= (uint32_t)(En <<7);
    LPRCNT->CAL3 = Temp;
}
/**
  * @brief  After seveval rounds of scanning , it is necessary to take the average .
  * @param  n: the scanning times , times = 2^n
  * @retval None
  */
void SetScanAverageValue(uint8_t N)
{
    uint32_t Temp = 0;
    if (N <= 3)
    {
       Temp = LPRCNT->CTRL;
       //clear the bit that need add new vale
       Temp &= (~LPRCNT_CTRL_AVGSEL);
       Temp |= (uint32_t)(N << 18);
       LPRCNT->CTRL = Temp;
    }
}
/**
  * @brief  SetVibrationPower.
  * @param  value: the damped vibration power select.
  *   This parameter can be one of the following values:
  *     @arg POWERSELECT1V5
  *     @arg POWERSELECT1V65
  *     @arg POWERSELECT1V8
  *     @arg POWERSELECT2V0
  * @retval None
  */
void SetVibrationPower(uint8_t Value)
{
    uint32_t Temp = 0;
    Temp = LPRCNT->CTRL;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CTRL_PWRLVL);
    Temp |= (uint32_t)(Value << 21);
    LPRCNT->CTRL = Temp;
}

/**
  * @brief  configure normal sensor scan frequence.
  * @param  low_speed: if the rotating object does not move for a long time ,it will enter into low speed .
  * @param  hight_speed: In other cases, MCU keep in hight speed to detect rotation.
  * @param  swtich_time: the time interval about hight speed swtich to low speed.
  * @retval None
  */
void SetNormalSensorScanfrequence(uint16_t Low_speed,uint8_t Hight_speed,uint8_t Swtich_time)
{
    uint32_t Temp = 0;
    Temp = LPRCNT->SCTRL;
    //clear the bit that need add new vale
    Temp &= 0xfc000000;
    Temp |= (uint32_t)((Low_speed <<16) | (Swtich_time <<8) | (Hight_speed));
    LPRCNT->SCTRL = Temp;
}
/**
  * @brief  get normal sensor low speed values.
  * @retval low speed values
  */
uint16_t GetNormalSensorLowSpeed(void)
{
    uint16_t Temp = 0;
    Temp = (uint16_t)((LPRCNT->SCTRL >> 16) & 0x03ff);
    return  Temp;
}
/**
  * @brief  get normal sensor hight speed values.
  * @retval hight speed values
  */
uint8_t GetNormalSensorHightSpeed(void)
{
    uint8_t Temp = 0;
    Temp = (uint8_t)(LPRCNT->SCTRL);
    return  Temp;
}
/**
  * @brief  get normal sensor swtich time.
  * @retval swtich time values
  */
uint8_t GetNormalSensorSwtichTime(void)
{
    uint8_t Temp = 0;
    Temp = (uint8_t)(LPRCNT->SCTRL >> 8);
    return  Temp;
}
/**
  * @brief  SetAlarmSensorScanfrequence.
  * @param  the frequence is several times than the normal sensor .
  *   This parameter can be one of the following values:
  *     @arg FRETIME4
  *     @arg FRETIME8
  *     @arg FRETIME16
  *     @arg FRETIME32
  * @retval None
  */
void SetAlarmSensorScanfrequence(uint8_t Period)
{
    uint32_t Temp = 0;
    Temp = LPRCNT->CTRL;
    //clear the bit that need add new vale
    Temp &= (~LPRCNT_CTRL_ALMPRD);
    Temp |= (uint32_t)(Period <<26);
    LPRCNT->CTRL = Temp;
}
/**
  * @brief  set LPRCNT module CMD .
  * @param  command .
  *   This parameter can be one of the following values:
  * @retval None
  */
//void LPRCNTModeEnable(uint8_t Cmd)
//{
//  LPRCNT->CMD |= (uint32_t)Cmd;
//
//}
/**
  * @brief Read lprcnt Start state .
  * @param  void .
  * @retval 0 or 1
  */
bool ReadStartState(void)
{
   bool temp;
   temp = LPRCNT->CMD;
   return temp ;
}

/**
  * @brief  After the comparator , the square waves can be got for each channel .
  * @param  ch: there are in total three sensor.The frequence of the three sensors is staggered,
  *             so the number of square waves will be different.
  * @retval the waves number
  */
uint8_t GetChannelSensorWavesNum(uint8_t Ch)
{
    uint8_t Temp =0;
    if (Ch == CHANNEL_0)
    {
       Temp = (LPRCNT->CAL0 & 0x000000ff);
       return Temp;
    }
    else if (Ch == CHANNEL_1)
    {
       Temp =((LPRCNT->CAL0 & 0x00ff0000)>> 16);
       return Temp;
    }
    else
    {
       Temp = (LPRCNT->CAL1 & 0x000000ff);
       return Temp;
    }
}

/**
  * @brief  Through the threshold value judgment,per channel can redefine as the state mode .
  * @param  ch: there are three state mode
  *   This parameter can be one of the following values:
  *         @arg 0: undamped
  *         @arg 1: middle state
  *         @arg 2: damped
  * @retval the state value
  */
uint8_t GetChannelSensorState(uint8_t Ch)
{
    if (Ch == CHANNEL_0)
    {
       return ((uint8_t)((LPRCNT->CAL0  >> 8) & 0x3));
    }
    else if (Ch == CHANNEL_1)
    {
       return ((uint8_t)((LPRCNT->CAL0  >> 24) & 0x3));
    }
    else if (Ch == CHANNEL_2)
    {
       return ((uint8_t)((LPRCNT->CAL1  >> 8) & 0x3));
    }
    else
    {
       return CHANNEL_ERROR;//channel error
    }
}

/**
  * @brief  get the sample mode .
  * @param  ch: there are three state mode
  *   This parameter can be one of the following values:
  * @retval the ratation Circle value
  */
uint8_t GetSampleMode(void)
{
    uint8_t Temp;
    Temp  = (uint8_t)((LPRCNT->CAL2 >> 25) & 0x01);
    return Temp ;
}
/**
  * @brief  LPRCNT module can work in two mode.this is LPRCNT mode and calibration mode .
  * @param  mode: working mode .
  *   This parameter can be one of the following values:
  *     @arg 0: calibration mode , for calibration rotation object parameters
  *     @arg 1: LPRCNT mode, the mode can detect the Circle of rotation
  * @retval None
  */
//void SetLPRCNTWorkMode(uint8_t mode)//封装成一个宏
//{
//  LPRCNT->CTRL |= (uint32_t)(mode << 24);
//}

/**
  * @brief  LPRCNT COMP Init.
  * @param  COMP_InitStruct.
  *   This parameter can be one of the following values:
  *   LPRCNT_COMP_InitType
  * @retval None
  */
void LPRCNT_CompInit(LPRCNT_COMP_InitType* COMP_InitStruct)
{
    uint32_t Temp ;
    Temp = LPRCNT->CAL3;
    //clear the bits about COMP  hysteresis
    Temp &= (~LPRCNT_CAL3_CMP_HYSEL);
    Temp |= COMP_InitStruct->Hyst;
    //clear input minus selection bits
    Temp &= (~LPRCNT_CAL3_CMP_INMSEL);
    Temp |= COMP_InitStruct->InmSel;
    //COMP low power enable
    Temp |= COMP_InitStruct->LowPoweMode;
    LPRCNT->CAL3 = Temp;
}

/**
  * @brief  DigitalfilterConfig.
* @param  cmd:enable or disable.
* @param  filterTh:Filter threshold control.
  *   This parameter can be one of the following values:
  *   CMP_FILTH_MODE0 : T/2~T
  *   CMP_FILTH_MODE1 : T~3T/2
  *   CMP_FILTH_MODE2 : 3T/2~2T
  * @retval None
  */
void CompDigitalFilterCfg(bool Cmd, uint32_t FilterThr)
{
    uint32_t Temp ;
    Temp = LPRCNT->CAL3;
    //clear FILTH bit
    Temp &= (~LPRCNT_CAL3_FILTH);
    Temp |= FilterThr;
    LPRCNT->CAL3 = Temp;
    if (Cmd == ENABLE)
    {
       LPRCNT->CAL3 |= LPRCNT_CAL3_DIGFILEN;
    }
    else
    {
       LPRCNT->CAL3 &= (~LPRCNT_CAL3_DIGFILEN);
    }
}
/**
  * @brief  COMPDigitalfilterEnable.
  * @param  cmd:ENABLE or DISABLE.
  * @retval None
  */
void CompAnalogFilterEn(bool Cmd)
{
    if (Cmd == ENABLE)
    {
       LPRCNT->CAL3 |= LPRCNT_CAL3_ANGFILEN;
    }
    else
    {
       LPRCNT->CAL3 &= (~LPRCNT_CAL3_ANGFILEN);
    }
}

/**
  * @brief  Digital filter phase control.
  * @param  direction:P or N.
  * @retval None
  */
void CompDigitalFilterPhase(bool dir)
{
    uint32_t Temp ;
    Temp = LPRCNT->CAL3;
    Temp &= (~LPRCNT_CAL3_DIGFILPH);
    if (dir == POPH)
    {
       Temp |= LPRCNT_CAL3_DIGFILPH_P;
       LPRCNT->CAL3 = Temp;
    }
    else
    {
       Temp |= LPRCNT_CAL3_DIGFILPH_N;
       LPRCNT->CAL3 = Temp;
    }
}


/**
  * @brief  DAC & CMP always on enable while 1 round sampling.
  * @param  NewState:ENABLE or DISABLE.
  * @retval None
  */
void DAC_CMP_ALWSONCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
     /* Enable the selected LPRCNT AlwaysON，hardware auto turn on MSI clock */
     LPRCNT->CAL3 |= LPRCNT_CAL3_DAC_CMP_ALWSON;
     RCC_EnableMsi(DISABLE);
  }
  else
  {
     /* Disable the selected LPRCNT stop */
     LPRCNT->CAL3 &= ~LPRCNT_CAL3_DAC_CMP_ALWSON;
  }
}
/**
  * @brief  LPRCNT analog filter,include gated values and phases.
  * @param  None
  * @retval None
  */
void LPRCNTAnalogFilterConfig(void)
{
    SetAnalogFilterTh(1);
    CompAnalogFilterPhase(POPH);
    CompAnalogFilterEn(ENABLE);
}
/**
  * @brief  LPRCNT module Init.
  * @param  LPRCNT are ready to run  .
  *   This parameter can be one of the following values:
  *     @arg 0: LPRCNT_InitStruct , for init rotation object parameters
  * @retval None
  */
void LPRCNTInit(LPRCNT_InitType* LPRCNT_InitStruct)
{
    //clock and charge voltage
    SetMsiClkPrescale(LPRCNT_InitStruct->PrescaleDiv);
    SetVibrationPower(LPRCNT_InitStruct->ChargeVol);
    //SetPwrAutoCharge(ENABLE);
    //DAC_CMP_ALWSONCmd(ENABLE);
    //sensor time paragram
    CfgChannelTime(CHANNEL_0,LPRCNT_InitStruct->ChTime[0].vibrationtime,LPRCNT_InitStruct->ChTime[0].dischargetime,LPRCNT_InitStruct->ChTime[0].chargetime);
    CfgChannelTime(CHANNEL_1,LPRCNT_InitStruct->ChTime[1].vibrationtime,LPRCNT_InitStruct->ChTime[1].dischargetime,LPRCNT_InitStruct->ChTime[1].chargetime);
    CfgChannelTime(CHANNEL_2,LPRCNT_InitStruct->ChTime[2].vibrationtime,LPRCNT_InitStruct->ChTime[2].dischargetime,LPRCNT_InitStruct->ChTime[2].chargetime);
    //sensor state paragram
    CfgChannelThr(CHANNEL_0,LPRCNT_InitStruct->ChTH[0].undampedTh,LPRCNT_InitStruct->ChTH[0].dampedTh);
    CfgChannelDacRefVol(CHANNEL_0,LPRCNT_InitStruct->ChTH[0].dacreference);
    CfgChannelThr(CHANNEL_1,LPRCNT_InitStruct->ChTH[1].undampedTh,LPRCNT_InitStruct->ChTH[1].dampedTh);
    CfgChannelDacRefVol(CHANNEL_1,LPRCNT_InitStruct->ChTH[1].dacreference);
    CfgChannelThr(CHANNEL_2,LPRCNT_InitStruct->ChTH[2].undampedTh,LPRCNT_InitStruct->ChTH[2].dampedTh);
    CfgChannelDacRefVol(CHANNEL_2,LPRCNT_InitStruct->ChTH[2].dacreference);
    SetNormalSensorScanfrequence(LPRCNT_InitStruct->NormalFreq.low_speed,LPRCNT_InitStruct->NormalFreq.hight_speed,LPRCNT_InitStruct->NormalFreq.swtich_time);
    SetScanAverageValue(0);//default 0
    //scan period
    SetNormalSensorScanfrequence(LPRCNT_InitStruct->NormalFreq.low_speed,LPRCNT_InitStruct->NormalFreq.hight_speed,LPRCNT_InitStruct->NormalFreq.swtich_time);
    SetAlarmSensorScanfrequence(LPRCNT_InitStruct->AlarmFreq);
    SetAutoDetectPeriod(LPRCNT_InitStruct->AutoWaitPer);
    SetAutoDetectEnale(LPRCNT_InitStruct->AutoDetEn);
    //setup time funtion
    DacSetupTimeConfig();
    CompSetupTimeConfig();
    //ChargeAndDischargeGap(5);
    ClrRcntCircle();
    SetAutoReportCircle(LPRCNT_InitStruct->Circle);
    LPRCNTAnalogFilterConfig();//default to select the analog filter
    SetLPRCNTWorkMode(LPRCNT_InitStruct->WorkMode);
    //interruput
    LPRCNT_ClrIntBit(LPRCNT_INTSTS_RPTIF);
    LPRCNT_IntEn(LPRCNT_InitStruct->Int,LPRCNT_InitStruct->IntEn);
}



/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2019 NATIONZ *****END OF FILE****/

