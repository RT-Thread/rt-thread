/**
  ******************************************************************************
  * @file    lib_LoadNVR.c 
  * @author  Application Team
  * @version V4.7.0
  * @date    2019-12-12
  * @brief   Load information from NVR.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lib_LoadNVR.h"


/**
  * @breif  Load Analog trim data from NVR manually.
  * @note   Successful Operation:
  *           - Load [0x40DC0] or [0x40DD0] to ANA registers(B C D E), return 0.
  *         Operation failed:
  *           - return 1.
  * @param  None
  * @retval 0: Function succeeded.
            1: Function failed(Checksum error). 
  */
uint32_t NVR_LoadANADataManual(void)
{
  uint32_t checksum;
  uint32_t op_reg;
  uint32_t ana_data;
  uint32_t key_reg = 0xFFFFFFFF;
  
  /* Get Analog data1 */
  ana_data = *NVR_ANA_TRIMDATA1;
  op_reg = *NVR_ANA_OPREG1;
  /* Calculate checksum1 */
  checksum = ~(ana_data + op_reg + key_reg);
  /* Compare checksum1 */
  if (checksum == (*NVR_ANA_CHECKSUM1))
  {
    ANA->REGB = (uint8_t)(ana_data);
    ANA->REGC = (uint8_t)(ana_data >> 8);
    ANA->REGD = (uint8_t)(ana_data >> 16);
    ANA->REGE = (uint8_t)(ana_data >> 24);
    return 0;
  }
  
  /* Get Analog data2 */
  ana_data = *NVR_ANA_TRIMDATA2;
  op_reg = *NVR_ANA_OPREG2;
  /* Calculate checksum2 */
  checksum = ~(ana_data + op_reg + key_reg);
  /* Compare checksum2 */
  if (checksum == (*NVR_ANA_CHECKSUM2)) 
  {
    ANA->REGB = (uint8_t)(ana_data);
    ANA->REGC = (uint8_t)(ana_data >> 8);
    ANA->REGD = (uint8_t)(ana_data >> 16);
    ANA->REGE = (uint8_t)(ana_data >> 24);
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
  * @breif  Get the parameters of ADC voltage measuring.
  * @note   Voltage(unit:V) = aParameter*ADC_DATA + bParameter
  *             ADC_DATA: ADC channel original data
  *             aParameter/bParameter: Get from this function
  * @param  [in]Mode:
  *                NVR_3V_EXTERNAL_NODIV
  *                NVR_3V_EXTERNAL_RESDIV
  *                NVR_3V_EXTERNAL_CAPDIV
  *                NVR_3V_VDD_RESDIV
  *                NVR_3V_VDD_CAPDIV
  *                NVR_3V_BATRTC_RESDIV
  *                NVR_3V_BATRTC_CAPDIV
  *                NVR_5V_EXTERNAL_NODIV
  *                NVR_5V_EXTERNAL_RESDIV
  *                NVR_5V_EXTERNAL_CAPDIV
  *                NVR_5V_VDD_RESDIV
  *                NVR_5V_VDD_CAPDIV
  *                NVR_5V_BATRTC_RESDIV
  *                NVR_5V_BATRTC_CAPDIV
  * @param  [out]Parameter: The parameters get from NVR
  * @retval 0: Function succeeded.
            1: Function failed(Checksum error). 
  */
uint32_t NVR_GetADCVoltageParameter(uint32_t Mode, NVR_ADCVOLPARA *Parameter)
{
  uint32_t checksum;
  uint32_t i;
  int32_t tmp_int;

  /* Check the parameters */
  assert_parameters(IS_NVR_ADCVOL_MODE(Mode));

  /*----- Power supply: 5V -----*/
  if (0x100UL & Mode)
  {
    checksum = 0UL;
    for (i=0; i<14; i++)
      checksum += *(NVR_5VPARA_BASEADDR1+i);
    checksum = ~(checksum);
    if (checksum != *(NVR_5VPARA_BASEADDR1+i))     /* Checksum1 error */
    {
      checksum = 0UL;
      for (i=0; i<14; i++)
        checksum += *(NVR_5VPARA_BASEADDR2+i);
      checksum = ~(checksum);
      if (checksum != *(NVR_5VPARA_BASEADDR2+i))   /* Checksum2 error */
      {
        return 1;
      }
      else
      {
        tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR2+2*(Mode-0x100UL));
        Parameter->aParameter = (float)(tmp_int / 100000000.0);
        tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR2+2*(Mode-0x100UL)+1);
        Parameter->bParameter = (float)(tmp_int / 100000000.0);
        return 0;
      }
    }
    else
    {
      tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR1+2*(Mode-0x100UL));
      Parameter->aParameter = (float)(tmp_int / 100000000.0);
      tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR1+2*(Mode-0x100UL)+1);
      Parameter->bParameter = (float)(tmp_int / 100000000.0);
      return 0;
    }
  }
  /*----- Power supply: 3.3V -----*/
  else
  {
    checksum = 0UL;
    for (i=0; i<14; i++)
      checksum += *(NVR_3VPARA_BASEADDR1+i);
    checksum = ~(checksum);
    if (checksum != *(NVR_3VPARA_BASEADDR1+i))     /* Checksum1 error */
    {
      checksum = 0UL;
      for (i=0; i<14; i++)
        checksum += *(NVR_3VPARA_BASEADDR2+i);
      checksum = ~(checksum); 
      if (checksum != *(NVR_3VPARA_BASEADDR2+i))   /* Checksum2 error */ 
      {
        return 1;
      }  
      else
      {
        tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR2+2*(Mode));
        Parameter->aParameter = (float)(tmp_int / 100000000.0);
        tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR2+2*(Mode)+1);
        Parameter->bParameter = (float)(tmp_int / 100000000.0);
        return 0;
      } 
    }
    else
    {
      tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR1+2*(Mode));
      Parameter->aParameter = (float)(tmp_int / 100000000.0);
      tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR1+2*(Mode)+1);
      Parameter->bParameter = (float)(tmp_int / 100000000.0);
      return 0;
    }
  }
}

/**
  * @breif  Get BAT Measure result.
  * @param  [out]MEAResult   The pointer to struct NVR_BATMEARES.
  * @retval 0: Function succeeded.
            1: Function failed(Checksum error). 
  */
uint32_t NVR_GetBATOffset(NVR_BATMEARES *MEAResult)
{
  uint32_t bat_r;
  uint32_t bat_c;
  uint32_t checksum;
  
  bat_r = *NVR_BAT_R1;
  bat_c = *NVR_BAT_C1;
  /* Calculate checksum1 */
  checksum = ~(bat_r + bat_c);
  if (checksum == (*NVR_BATMEA_CHECHSUM1))
  {
    MEAResult->BATRESResult = (float)((int32_t)bat_r / 1000.0);
    MEAResult->BATCAPResult = (float)((int32_t)bat_c / 1000.0);
    return 0;
  }

  bat_r = *NVR_BAT_R2;
  bat_c = *NVR_BAT_C2;
  /* Calculate checksum2 */
  checksum = ~(bat_r + bat_c);
  if (checksum == (*NVR_BATMEA_CHECHSUM2))
  {
    MEAResult->BATRESResult = (float)((int32_t)bat_r / 1000.0);
    MEAResult->BATCAPResult = (float)((int32_t)bat_c / 1000.0);
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
  * @breif  Load RTC ACPx pramameters from NVR to RTC registers.
            Get RTC pramameters.
  * @param  [out]RTCTempData   The pointer to struct NVR_RTCINFO.
  * @retval 0: Function succeeded.
           !0: Function not succeeded, load default value to registers.
            bit[0]=1: Temperature Measure delta information checksum error, default value is 0.
            bit[1]=1: P paramters checksum error, default value as follows
                [P0]-214, [P1]1060, [P2]-19746971, [P5]6444, [P6]1342, [P7]0 
            bit[2]=1: P4 checksum error, default value is 0
            bit[3]=1: ACKx checksum error,  default value as follows
                [K1]20827, [K2]21496, [K3]22020, [K4]24517, [K5]25257
            bit[4]=1: ACTI checksum error, default value is 0x1800(24.0)
            bit[5]=1: ACKTEMP checksum error, defalut value is 0x3C2800EC
  */
uint32_t NVR_GetInfo_LoadRTCData(NVR_RTCINFO *RTCTempData)
{
  uint32_t real_temp, mea_temp;
  uint32_t rtc_data1, rtc_data2, rtc_data3, rtc_data4;
  uint32_t rtc_p4;
  uint32_t rtc_ack[5];
  uint32_t rtc_acti;
  uint32_t rtc_acktemp;
  uint32_t checksum;
  float pclk_mul;
  
  int16_t TempDelta;
  uint32_t retval = 0;
  
/*------------------------ Temperature Measure delta -------------------------*/
  real_temp = *NVR_REALTEMP1;
  mea_temp  = *NVR_MEATEMP1;
  /* Calculate checksum1 */
  checksum = ~(real_temp + mea_temp);
  if (checksum == (*NVR_TEMP_CHECKSUM1)) //checksum1 true
  {
    TempDelta = (int16_t)real_temp - (int16_t)mea_temp;
  }
  else
  {
    real_temp = *NVR_REALTEMP2;
    mea_temp  = *NVR_MEATEMP2;
    /* Calculate checksum2 */  
    checksum = ~(real_temp + mea_temp);
    if (checksum == (*NVR_TEMP_CHECKSUM2)) //checksum2 true 
    {
      TempDelta = (int16_t)real_temp - (int16_t)mea_temp;
    }
    else
    {
      TempDelta = 0;
      retval |= BIT0;
    }
  }
  /* Get Measure delta information */
  RTCTempData->RTCTempDelta = TempDelta;
  
/*------------------------------ P parameters --------------------------------*/
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro(); 
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  /* Get PCLK */
  RTCTempData->APBClock = CLK_GetPCLKFreq();
  pclk_mul = RTCTempData->APBClock / 6553600.0;
  
  rtc_data1 = *NVR_RTC1_P1_P0;
  rtc_data2 = *NVR_RTC1_P2;
  rtc_data3 = *NVR_RTC1_P5_P4;
  rtc_data4 = *NVR_RTC1_P7_P6;
  /* Calculate checksum1 */
  checksum = ~(rtc_data1 + rtc_data2 + rtc_data3 + rtc_data4);
  if (checksum == (*NVR_RTC1_PCHECHSUM)) //checksum1 true
  {
    /* Get information */
    RTCTempData->RTCTempP0 = (int16_t)(rtc_data1);
    RTCTempData->RTCTempP1 = (int16_t)(rtc_data1 >> 16);
    RTCTempData->RTCTempP2 = (int32_t)((int32_t)rtc_data2 + (((int32_t)TempDelta)*256));
    RTCTempData->RTCTempP5 = (int16_t)(rtc_data3 >> 16);
    RTCTempData->RTCTempP6 = (int16_t)(rtc_data4 * pclk_mul);
    RTCTempData->RTCTempP7 = (int16_t)(rtc_data4 >> 16);
  
    /* Load data to ACPx register */
    RTC->ACP0 = (uint16_t)(rtc_data1 & 0xFFFF);
    RTC->ACP1 = (uint16_t)((rtc_data1 >> 16) & 0xFFFF);
    RTC->ACP2 = (uint32_t)((int32_t)rtc_data2 + (((int32_t)TempDelta)*256));
    RTC->ACP5 = (uint16_t)((rtc_data3 >> 16) & 0xFFFF);
    RTC->ACP6 = (uint16_t)((int16_t)(rtc_data4 * pclk_mul));
    RTC->ACP7 = (uint16_t)((rtc_data4 >> 16) & 0xFFFF); 
  }
  else
  {
    rtc_data1 = *NVR_RTC2_P1_P0;
    rtc_data2 = *NVR_RTC2_P2;
    rtc_data3 = *NVR_RTC2_P5_P4;
    rtc_data4 = *NVR_RTC2_P7_P6;
    /* Calculate checksum2 */
    checksum = ~(rtc_data1 + rtc_data2 + rtc_data3 + rtc_data4);
    if (checksum == (*NVR_RTC2_PCHECHSUM)) //checksum2 true 
    {
      /* Get information */
      RTCTempData->RTCTempP0 = (int16_t)(rtc_data1);
      RTCTempData->RTCTempP1 = (int16_t)(rtc_data1 >> 16);
      RTCTempData->RTCTempP2 = (int32_t)((int32_t)rtc_data2 + (((int32_t)TempDelta)*256));
      RTCTempData->RTCTempP5 = (int16_t)(rtc_data3 >> 16);
      RTCTempData->RTCTempP6 = (int16_t)(rtc_data4 * pclk_mul);
      RTCTempData->RTCTempP7 = (int16_t)(rtc_data4 >> 16);
  
      /* Load data to ACPx register */
      RTC->ACP0 = (uint16_t)(rtc_data1 & 0xFFFF);
      RTC->ACP1 = (uint16_t)((rtc_data1 >> 16) & 0xFFFF);
      RTC->ACP2 = (uint32_t)((int32_t)rtc_data2 + (((int32_t)TempDelta)*256));
      RTC->ACP5 = (uint16_t)((rtc_data3 >> 16) & 0xFFFF);
      RTC->ACP6 = (uint16_t)((int16_t)(rtc_data4 * pclk_mul));
      RTC->ACP7 = (uint16_t)((rtc_data4 >> 16) & 0xFFFF);    
    }
    else
    {
      /* Get information */
      RTCTempData->RTCTempP0 = -214;
      RTCTempData->RTCTempP1 = 1060;
      RTCTempData->RTCTempP2 = -19746971 + (TempDelta*256);
      RTCTempData->RTCTempP5 = 6444;
      RTCTempData->RTCTempP6 = (uint32_t)((int32_t)(1342*pclk_mul));
      RTCTempData->RTCTempP7 = 0;

      /* Load data to ACPx register */
      RTC->ACP0 = (uint16_t)(-214);
      RTC->ACP1 = (uint16_t)(1060);
      RTC->ACP2 = (uint32_t)(-19746971 + (TempDelta*256));
      RTC->ACP5 = (uint16_t)(6444);
      RTC->ACP6 = (uint16_t)((int32_t)(1342*pclk_mul));
      RTC->ACP7 = (uint16_t)(0); 
      
      retval |= BIT1;
    }
  }
 
/*----------------------------------- P4 -------------------------------------*/
  /* Calculate checksum1 */
  rtc_p4 = *NVR_RTC1_P4;
  checksum = ~rtc_p4;
  if (checksum == (*NVR_RTC1_P4_CHKSUM))//checksum1 true 
  {
    /* Get information */
    RTCTempData->RTCTempP4 = (int16_t)(*NVR_RTC1_P4);
    RTC->ACP4 = *NVR_RTC1_P4;   
  }
  else
  {
    rtc_p4 = *NVR_RTC2_P4;
    checksum = ~rtc_p4;
    if (checksum == (*NVR_RTC2_P4_CHKSUM))//checksum2 true
    {
      /* Get information */
      RTCTempData->RTCTempP4 = (int16_t)(*NVR_RTC1_P4);
      RTC->ACP4 = *NVR_RTC1_P4;      
    }
    else
    {
      RTCTempData->RTCTempP4 = 0;
      RTC->ACP4 = 0;
      
      retval |= BIT2;
    }
  }

/*-------------------------- RTC ACKx parameters -----------------------------*/
  rtc_ack[0] = *NVR_RTC1_ACK1;
  rtc_ack[1] = *NVR_RTC1_ACK2;
  rtc_ack[2] = *NVR_RTC1_ACK3;
  rtc_ack[3] = *NVR_RTC1_ACK4;
  rtc_ack[4] = *NVR_RTC1_ACK5;
  checksum = ~(rtc_ack[0] + rtc_ack[1] + rtc_ack[2] + rtc_ack[3] + rtc_ack[4]);
  if (checksum == (*NVR_RTC1_ACK_CHKSUM))//checksum1 true 
  {
    /* Get information */
    RTCTempData->RTCTempK1 = rtc_ack[0];
    RTCTempData->RTCTempK2 = rtc_ack[1];
    RTCTempData->RTCTempK3 = rtc_ack[2];
    RTCTempData->RTCTempK4 = rtc_ack[3];
    RTCTempData->RTCTempK5 = rtc_ack[4];
    
    /* Load data to ACKx register */
    RTC->ACK1 = rtc_ack[0];
    RTC->ACK2 = rtc_ack[1];
    RTC->ACK3 = rtc_ack[2];
    RTC->ACK4 = rtc_ack[3];
    RTC->ACK5 = rtc_ack[4];    
  }
  else
  {
    rtc_ack[0] = *NVR_RTC2_ACK1;
    rtc_ack[1] = *NVR_RTC2_ACK2;
    rtc_ack[2] = *NVR_RTC2_ACK3;
    rtc_ack[3] = *NVR_RTC2_ACK4;
    rtc_ack[4] = *NVR_RTC2_ACK5;
    checksum = ~(rtc_ack[0] + rtc_ack[1] + rtc_ack[2] + rtc_ack[3] + rtc_ack[4]);
    if (checksum == (*NVR_RTC2_ACK_CHKSUM))//checksum2 true 
    {
      /* Get information */
      RTCTempData->RTCTempK1 = rtc_ack[0];
      RTCTempData->RTCTempK2 = rtc_ack[1];
      RTCTempData->RTCTempK3 = rtc_ack[2];
      RTCTempData->RTCTempK4 = rtc_ack[3];
      RTCTempData->RTCTempK5 = rtc_ack[4];
   
      /* Load data to ACKx register */
      RTC->ACK1 = rtc_ack[0];
      RTC->ACK2 = rtc_ack[1];
      RTC->ACK3 = rtc_ack[2];
      RTC->ACK4 = rtc_ack[3];
      RTC->ACK5 = rtc_ack[4];      
    }
    else
    {
      /* Get information */
      RTCTempData->RTCTempK1 = 20827;
      RTCTempData->RTCTempK2 = 21496;
      RTCTempData->RTCTempK3 = 22020;
      RTCTempData->RTCTempK4 = 24517;
      RTCTempData->RTCTempK5 = 25257;

      /* Load data to ACKx register */
      RTC->ACK1 = 20827;
      RTC->ACK2 = 21496;
      RTC->ACK3 = 22020;
      RTC->ACK4 = 24517;
      RTC->ACK5 = 25257;
      
      retval |= BIT3;
    }
  }
  
/*-------------------------- RTC ACTI parameters -----------------------------*/
  rtc_acti = *NVR_RTC1_ACTI;
  checksum = ~rtc_acti;
  if (checksum == (*NVR_RTC1_ACTI_CHKSUM))
  {
    /* Get information */
    RTCTempData->RTCACTI = rtc_acti;
    /* Load data to ACKx register */
    RTC->ACTI = rtc_acti;
  }
  else
  {
    rtc_acti = *NVR_RTC2_ACTI;
    checksum = ~rtc_acti;  
    if (checksum == (*NVR_RTC2_ACTI_CHKSUM))
    {
      /* Get information */
      RTCTempData->RTCACTI = rtc_acti;
      /* Load data to ACKx register */
      RTC->ACTI = rtc_acti;     
    }
    else
    {
      /* Get information */
      RTCTempData->RTCACTI = 0x1800;
      RTC->ACTI = 0x1800;
      
      retval |= BIT4;
    }
  }
  
/*------------------------- RTC ACKTemp parameters ---------------------------*/
  rtc_acktemp = *NVR_RTC1_ACKTEMP;
  checksum = ~rtc_acktemp;
  if (checksum == (*NVR_RTC1_ACKTEMP_CHKSUM))
  {
    /* Get information */
    RTCTempData->RTCACKTemp = rtc_acktemp;
    /* Load data to ACKx register */
    RTC->ACKTEMP = rtc_acktemp;    
  }
  else
  {
    rtc_acktemp = *NVR_RTC2_ACKTEMP;
    checksum = ~rtc_acktemp;
    if (checksum == (*NVR_RTC2_ACKTEMP_CHKSUM))
    {
      /* Get information */
      RTCTempData->RTCACKTemp = rtc_acktemp;
      /* Load data to ACKx register */
      RTC->ACKTEMP = rtc_acktemp;  
    }
    else
    {
      /* Get information */
      RTCTempData->RTCACKTemp = 0x3C2800EC; 
      RTC->ACKTEMP = 0x3C2800EC;  
      
      retval |= BIT5;
    }
  }
/*--------------------------------- ACF200 -----------------------------------*/
  RTCTempData->RTCACF200 = (uint32_t)((int32_t)(pclk_mul*0x320000));
  RTC->ACF200 = (uint32_t)((int32_t)(pclk_mul*0x320000));

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro(); 
  
  return retval;
}

/**
  * @breif  Get Power/Clock Measure result.
  * @param  [out]MEAResult   The pointer to struct NVR_PWRMEARES.
  * @retval 0: Function succeeded.
            1: Function failed(Checksum error). 
  */
uint32_t NVR_GetMISCGain(NVR_MISCGain *MEAResult)
{
  uint32_t avcc_data, dvcc_data, bgp_data, rcl_data, rch_data;
  uint32_t checksum;
  
  avcc_data = *NVR_AVCC_MEA1;
  dvcc_data = *NVR_DVCC_MEA1;
  bgp_data   = *NVR_BGP_MEA1;
  rcl_data   = *NVR_RCL_MEA1;
  rch_data   = *NVR_RCH_MEA1;
  /* Calculate checksum1 */
  checksum = ~(avcc_data + dvcc_data + bgp_data + rcl_data + rch_data);
  if (checksum == (*NVR_PWR_CHECKSUM1))
  {
    MEAResult->AVCCMEAResult = avcc_data;
    MEAResult->DVCCMEAResult = dvcc_data;
    MEAResult->BGPMEAResult   = bgp_data;
    MEAResult->RCLMEAResult   = rcl_data;
    MEAResult->RCHMEAResult   = rch_data;
    return 0;
  }
  
  avcc_data = *NVR_AVCC_MEA2;
  dvcc_data = *NVR_DVCC_MEA2;
  bgp_data   = *NVR_BGP_MEA2;
  rcl_data   = *NVR_RCL_MEA2;
  rch_data   = *NVR_RCH_MEA2;
  /* Calculate checksum2 */
  checksum = ~(avcc_data + dvcc_data + bgp_data + rcl_data + rch_data);
  if (checksum == (*NVR_PWR_CHECKSUM2))
  {
    MEAResult->AVCCMEAResult = avcc_data;
    MEAResult->DVCCMEAResult = dvcc_data;
    MEAResult->BGPMEAResult   = bgp_data;
    MEAResult->RCLMEAResult   = rcl_data;
    MEAResult->RCHMEAResult   = rch_data;
    return 0;    
  }
  else
  {
    return 1;
  }
}

/**
  * @breif  Get Chip ID.
  * @param  [out]ChipID   The pointer to struct NVR_CHIPID.
  * @retval 0: Function succeeded.
            1: Function failed(Checksum error). 
  */
uint32_t NVR_GetChipID(NVR_CHIPID *ChipID)
{
  uint32_t id0, id1;
  uint32_t checksum;
  
  id0 = *NVR_CHIP1_ID0;
  id1 = *NVR_CHIP1_ID1;
  /* Calculate checksum1 */
  checksum = ~(id0 + id1);
  if (checksum == (*NVR_CHIP1_CHECKSUM))
  {
    ChipID->ChipID0 = id0;
    ChipID->ChipID1 = id1;
    return 0;  
  }
  
  id0 = *NVR_CHIP2_ID0;
  id1 = *NVR_CHIP2_ID1;
  /* Calculate checksum2 */
  checksum = ~(id0 + id1);
  if (checksum == (*NVR_CHIP2_CHECKSUM))
  {
    ChipID->ChipID0 = id0;
    ChipID->ChipID1 = id1;
    return 0;  
  } 
  else 
  {
    return 1;
  }
}

/**
  * @breif  Get LCD information.
  * @param  [out]LCDInfo   The pointer to struct NVR_LCDINFO.
  * @retval 0: Function succeeded.
            1: Function failed(Checksum error). 
  */
uint32_t NVR_GetLCDInfo(NVR_LCDINFO *LCDInfo)
{
  uint32_t lcd_ldo, lcd_vol;
  uint32_t checksum;
  
  lcd_ldo = *NVR_LCD_LDO1;
  lcd_vol = *NVR_LCD_VOL1;
  /* Calculate checksum1 */
  checksum = ~(lcd_ldo + lcd_vol);
  if (checksum == (*NVR_LCD_CHECKSUM1))
  {
    LCDInfo->MEALCDLDO = lcd_ldo;
    LCDInfo->MEALCDVol = lcd_vol;
    return 0;
  }

  lcd_ldo = *NVR_LCD_LDO2;
  lcd_vol = *NVR_LCD_VOL2;
  /* Calculate checksum2 */
  checksum = ~(lcd_ldo + lcd_vol);
  if (checksum == (*NVR_LCD_CHECKSUM2))  
  {
    LCDInfo->MEALCDLDO = lcd_ldo;
    LCDInfo->MEALCDVol = lcd_vol; 
    return 0;
  }
  else
  {
    return 1;
  }
}

/*********************************** END OF FILE ******************************/
