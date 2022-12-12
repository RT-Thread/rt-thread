/**
  ******************************************************************************
  * @file    lib_LoadNVR.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Load information from NVR.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lib_LoadNVR.h"


/**
  * @breif  Loads Analog trim data from NVR manually.
  * @note   Successful Operation:
  *           - Load [0x80DC0] or [0x80DD0] to ANA registers(B C D E)
  *           - Load [0x80DE0] or [0x80DE8] to ANA registers(10)
  * @param  None
  * @retval 0: Function succeeded.
           !0: Function failed.
              bit[0]=1: Function failed(ANA registers(B C D E) Checksum error). 
              bit[1]=1: Function failed(ANA registers(10) Checksum error).
  */
uint32_t NVR_LoadANADataManual(void)
{
  uint32_t checksum;
  uint32_t op_reg;
  uint32_t ana_data;
  uint32_t key_reg = 0xFFFFFFFF;
  uint32_t ret = 0;
  
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
  }
  else
  {
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
    }
    else
    {
      ret |= BIT0;
    }
  }

  /* Get Analog data1 */
  ana_data = *NVR_ANA1_REG10;
  /* Calculate checksum1 */
  checksum = ~ana_data;
  /* Compare checksum1 */
  if (checksum == (*NVR_ANA1_REG10_CHKSUM))
  {
    ANA->REG10 = (uint8_t)(ana_data);
  }
  else
  {
    /* Get Analog data2 */
    ana_data = *NVR_ANA2_REG10;
    /* Calculate checksum2 */
    checksum = ~ana_data;
    /* Compare checksum2 */
    if (checksum == (*NVR_ANA2_REG10_CHKSUM))
    {
      ANA->REG10 = (uint8_t)(ana_data);
    }
    else
    {
      ret |= BIT1;
    }
  }

  return ret;
}

/**
  * @breif  Gets the parameters of ADC voltage measuring.
  * @note   Voltage(unit:V) = aParameter*ADC_DATA + bParameter + OffsetParameter
  *             ADC_DATA: ADC channel original data
  *             aParameter/bParameter/OffsetParameter: Get from this function
  * @param  [in]Mode:
  *                NVR_3V_EXTERNAL_NODIV
  *                NVR_3V_EXTERNAL_RESDIV
  *                NVR_3V_BAT1_RESDIV
  *                NVR_3V_BATRTC_RESDIV
  *                NVR_5V_EXTERNAL_NODIV
  *                NVR_5V_EXTERNAL_RESDIV
  *                NVR_5V_BAT1_RESDIV
  *                NVR_5V_BATRTC_RESDIV
  * @param  [out]Parameter: The parameters get from NVR
  * @retval 0: Function succeeded.
            1: Function failed(Checksum error). 
  */
uint32_t NVR_GetVoltageParameters(uint32_t Mode, NVR_ADCVOLPARA *Parameter)
{
  uint32_t checksum;
  uint32_t i;
  int32_t tmp_int;

  /* Check the parameters */
  assert_parameters(IS_NVR_ADCVOL_MODE(Mode));

  /*----- Power supply: 5V -----*/
  if (0x100UL & Mode)
  {
    /*                    Parameter                        */
    checksum = 0UL;
    for (i=0; i<8; i++)
      checksum += *(NVR_5VPARA_BASEADDR1+i);
    checksum = ~(checksum);
    if (checksum != *(NVR_5VPARA_BASEADDR1+i))     /* Checksum1 error */
    {
      checksum = 0UL;
      for (i=0; i<8; i++)
        checksum += *(NVR_5VPARA_BASEADDR2+i);
      checksum = ~(checksum);
      if (checksum != *(NVR_5VPARA_BASEADDR2+i))   /* Checksum2 error */
      {
        return 1;
      }
      else
      {
        tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR2+2*(Mode-0x100UL));
        Parameter->aParameter = (float)(tmp_int / 100000.0);
        tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR2+2*(Mode-0x100UL)+1);
        Parameter->bParameter = (float)(tmp_int / 100000.0);
      }
    }
    else
    {
      tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR1+2*(Mode-0x100UL));
      Parameter->aParameter = (float)(tmp_int / 100000.0);
      tmp_int = (int32_t)*(NVR_5VPARA_BASEADDR1+2*(Mode-0x100UL)+1);
      Parameter->bParameter = (float)(tmp_int / 100000.0);
    }
    /*                    Offset                        */
    /* Calculate checksum1 */
    checksum = 0UL;
    for (i = 0; i < 4; i++)
      checksum += *(NVR_5VADCCHx_NODIV1 + i);
    checksum = ~(checksum);
    if (checksum != *(NVR_5VADCCHx_NODIV1 + i))
    {
      /* Calculate checksum2 */
      checksum = 0UL;
      for (i = 0; i < 4; i++)
        checksum += *(NVR_5VADCCHx_NODIV2+i);
      checksum = ~(checksum);
      if (checksum != *(NVR_5VADCCHx_NODIV2 + i))
      {
        return 1;
      }
      else
      {
        Parameter->OffsetParameter = (float)((int32_t)*(NVR_5VADCCHx_NODIV2 + (Mode-0x100UL)));
        return 0;
      }
    }
    else
    {
      Parameter->OffsetParameter = (float)((int32_t)*(NVR_5VADCCHx_NODIV1 + (Mode-0x100UL)));
      return 0;
    }
  }
  /*----- Power supply: 3.3V -----*/
  else
  {
    checksum = 0UL;
    for (i=0; i<8; i++)
      checksum += *(NVR_3VPARA_BASEADDR1+i);
    checksum = ~(checksum);
    if (checksum != *(NVR_3VPARA_BASEADDR1+i))     /* Checksum1 error */
    {
      checksum = 0UL;
      for (i=0; i<8; i++)
        checksum += *(NVR_3VPARA_BASEADDR2+i);
      checksum = ~(checksum); 
      if (checksum != *(NVR_3VPARA_BASEADDR2+i))   /* Checksum2 error */ 
      {
        return 1;
      }  
      else
      {
        tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR2+2*(Mode));
        Parameter->aParameter = (float)(tmp_int / 100000.0);
        tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR2+2*(Mode)+1);
        Parameter->bParameter = (float)(tmp_int / 100000.0);
      } 
    }
    else
    {
      tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR1+2*(Mode));
      Parameter->aParameter = (float)(tmp_int / 100000.0);
      tmp_int = (int32_t)*(NVR_3VPARA_BASEADDR1+2*(Mode)+1);
      Parameter->bParameter = (float)(tmp_int / 100000.0);
    }
    /* Calculate checksum1 */
    checksum = 0UL;
    for (i = 0; i < 4; i++)
      checksum += *(NVR_3VADCCHx_NODIV1 + i);
    checksum = ~(checksum);
    if (checksum != *(NVR_3VADCCHx_NODIV1 + i))
    {
      /* Calculate checksum2 */
      checksum = 0UL;
      for (i = 0; i < 4; i++)
        checksum += *(NVR_3VADCCHx_NODIV2+i);
      checksum = ~(checksum);
      if (checksum != *(NVR_3VADCCHx_NODIV2 + i))
      {
        return 1;
      }
      else
      {
        Parameter->OffsetParameter = (float)((int32_t)*(NVR_3VADCCHx_NODIV2 + (Mode)));
        return 0;
      }
    }
    else
    {
      Parameter->OffsetParameter = (float)((int32_t)*(NVR_3VADCCHx_NODIV1 + (Mode)));
      return 0;
    }
  }
}

/**
  * @breif  Gets RTC parameters(P0 P1 P2).
  * @param  [out]TempParams   The pointer to struct NVR_TempParams.
  * @retval 0: Function succeeded.
           !0: Function failed.
            bit[0]=1: Temperature Measure delta information checksum error, default value 0.
            bit[1]=1: P0/P1/P2 paramters checksum error, default value 0
  */
uint32_t NVR_GetTempParameters(NVR_TempParams *TempParams)
{
  uint32_t checksum;
  uint32_t data_u32[4];
  int32_t TempDelta;
  uint32_t retval = 0;
  
/*------------------------ Temperature Measure delta -------------------------*/
  data_u32[0] = *NVR_REALTEMP1;
  data_u32[1] = *NVR_MEATEMP1;
  /* Calculate checksum1 */
  checksum = ~(data_u32[0] + data_u32[1]);
  if (checksum == (*NVR_TEMP_CHECKSUM1)) //checksum1 true
  {
    TempDelta = (int32_t)data_u32[0] - (int32_t)data_u32[1];
  }
  else
  {
    data_u32[0] = *NVR_REALTEMP2;
    data_u32[1]  = *NVR_MEATEMP2;
    /* Calculate checksum2 */  
    checksum = ~(data_u32[0] + data_u32[1]);
    if (checksum == (*NVR_TEMP_CHECKSUM2)) //checksum2 true 
    {
      TempDelta = (int32_t)data_u32[0] - (int32_t)data_u32[1];
    }
    else
    {
      TempDelta = 0;
      retval |= BIT0;
    }
  }  
/*------------------------------ P parameters --------------------------------*/

  data_u32[0] = *NVR_RTC1_P1_P0;
  data_u32[1] = *NVR_RTC1_P2;
  data_u32[2] = *NVR_RTC1_P5_P4;
  data_u32[3] = *NVR_RTC1_P7_P6;

  /* Calculate checksum1 */
  checksum = ~(data_u32[0] + data_u32[1] + data_u32[2] + data_u32[3]);
  if (checksum == (*NVR_RTC1_PCHECHSUM)) //checksum1 true
  {
    /* Get information */
    TempParams->RTCTempP0 = (int16_t)(data_u32[0]);
    TempParams->RTCTempP1 = (int16_t)(data_u32[0] >> 16);
    TempParams->RTCTempP2 = (int32_t)((int32_t)(data_u32[1]) + (TempDelta*256));
  }
  else
  {
    data_u32[0] = *NVR_RTC2_P1_P0;
    data_u32[1] = *NVR_RTC2_P2;
    data_u32[2] = *NVR_RTC2_P5_P4;
    data_u32[3] = *NVR_RTC2_P7_P6;
    /* Calculate checksum2 */
    checksum = ~(data_u32[0] + data_u32[1] + data_u32[2] + data_u32[3]);
    if (checksum == (*NVR_RTC2_PCHECHSUM)) //checksum2 true 
    {
      /* Get information */
      TempParams->RTCTempP0 = (int16_t)(data_u32[0]);
      TempParams->RTCTempP1 = (int16_t)(data_u32[0] >> 16);
      TempParams->RTCTempP2 = (int32_t)((int32_t)(data_u32[1]) + (TempDelta*256));
    }
    else
    {
      /* Get information */
      TempParams->RTCTempP0 = 0;
      TempParams->RTCTempP1 = 0;
      TempParams->RTCTempP2 = 0;
      retval |= BIT1;
    }
  }
  return retval;
}

/**
  * @breif  Loads RTC ACPx pramameters from NVR to RTC registers.
            Get RTC pramameters.
  * @param  [out]RTCTempData   The pointer to struct NVR_RTCINFO.
            [in]DivCLKSource   The RTC division output clock source frequency
  * @retval 0: Function succeeded.
           !0: Function not succeeded, load default value to registers.
            bit[0]=1: Temperature Measure delta information checksum error, default value 0.
            bit[1]=1: P paramters checksum error, default value 0
            bit[2]=1: P4 checksum error, default value is 0
            bit[3]=1: ACKx checksum error,  default value 0
            bit[4]=1: ACTI checksum error, default value is 0
            bit[5]=1: ACKTEMP checksum error, defalut value is 0
  */
uint32_t NVR_GetInfo_LoadRTCData(NVR_RTCINFO *RTCTempData, uint32_t DivCLKSource)
{
  uint32_t data_u32[5];
  uint32_t checksum;
  float pclk_mul;
  uint32_t retval = 0;
  
/*------------------------ Temperature Measure delta -------------------------*/
  data_u32[0] = *NVR_REALTEMP1;
  data_u32[1]  = *NVR_MEATEMP1;
  /* Calculate checksum1 */
  checksum = ~(data_u32[0] + data_u32[1]);
  if (checksum == (*NVR_TEMP_CHECKSUM1)) //checksum1 true
  {
    RTCTempData->RTCTempDelta = (int32_t)data_u32[0] - (int32_t)data_u32[1];
  }
  else
  {
    data_u32[0] = *NVR_REALTEMP2;
    data_u32[1] = *NVR_MEATEMP2;
    /* Calculate checksum2 */  
    checksum = ~(data_u32[0] + data_u32[1]);
    if (checksum == (*NVR_TEMP_CHECKSUM2)) //checksum2 true 
    {
      RTCTempData->RTCTempDelta = (int32_t)data_u32[0] - (int32_t)data_u32[1];
    }
    else
    {
      RTCTempData->RTCTempDelta = 0;
      retval |= BIT0;
    }
  }
  
/*------------------------------ P parameters --------------------------------*/
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro(); 
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  /* RTC div output clock source */
  pclk_mul = DivCLKSource / 6553600.0;
  
  data_u32[0] = *NVR_RTC1_P1_P0;
  data_u32[1] = *NVR_RTC1_P2;
  data_u32[2] = *NVR_RTC1_P5_P4;
  data_u32[3] = *NVR_RTC1_P7_P6;
  /* Calculate checksum1 */
  checksum = ~(data_u32[0] + data_u32[1] + data_u32[2] + data_u32[3]);
  if (checksum == (*NVR_RTC1_PCHECHSUM)) //checksum1 true
  {
    /* Get information */
    RTCTempData->RTCTempP0 = (int16_t)(data_u32[0]);
    RTCTempData->RTCTempP1 = (int16_t)(data_u32[0] >> 16);
    RTCTempData->RTCTempP2 = (int32_t)((int32_t)(data_u32[1]) + (RTCTempData->RTCTempDelta*256));
    RTCTempData->RTCTempP5 = (int16_t)(data_u32[2] >> 16);
    RTCTempData->RTCTempP6 = (int16_t)(data_u32[3] * pclk_mul);
    RTCTempData->RTCTempP7 = (int16_t)(data_u32[3] >> 16);
  
    /* Load data to ACPx register */
    RTC->ACP0 = (uint16_t)(data_u32[0] & 0xFFFF);
    RTC->ACP1 = (uint16_t)((data_u32[0] >> 16) & 0xFFFF);
    RTC->ACP2 = (uint32_t)((int32_t)(data_u32[1]) + (RTCTempData->RTCTempDelta*256));
    RTC->ACP5 = (uint16_t)((data_u32[2] >> 16) & 0xFFFF);
    RTC->ACP6 = ((uint16_t)((int16_t)(data_u32[3] * pclk_mul)));
    RTC->ACP7 = (uint16_t)((data_u32[3] >> 16) & 0xFFFF); 
  }
  else
  {
    data_u32[0] = *NVR_RTC2_P1_P0;
    data_u32[1] = *NVR_RTC2_P2;
    data_u32[2] = *NVR_RTC2_P5_P4;
    data_u32[3] = *NVR_RTC2_P7_P6;
    /* Calculate checksum2 */
    checksum = ~(data_u32[0] + data_u32[1] + data_u32[2] + data_u32[3]);
    if (checksum == (*NVR_RTC2_PCHECHSUM)) //checksum2 true 
    {
      /* Get information */
      RTCTempData->RTCTempP0 = (int16_t)(data_u32[0]);
      RTCTempData->RTCTempP1 = (int16_t)(data_u32[0] >> 16);
      RTCTempData->RTCTempP2 = (int32_t)((int32_t)(data_u32[1]) + (RTCTempData->RTCTempDelta*256));
      RTCTempData->RTCTempP5 = (int16_t)(data_u32[2] >> 16);
      RTCTempData->RTCTempP6 = (int16_t)(data_u32[3] * pclk_mul);
      RTCTempData->RTCTempP7 = (int16_t)(data_u32[3] >> 16);
  
      /* Load data to ACPx register */
      RTC->ACP0 = (uint16_t)(data_u32[0] & 0xFFFF);
      RTC->ACP1 = (uint16_t)((data_u32[0] >> 16) & 0xFFFF);
      RTC->ACP2 = (uint32_t)((int32_t)(data_u32[1]) + (RTCTempData->RTCTempDelta*256));
      RTC->ACP5 = (uint16_t)((data_u32[2] >> 16) & 0xFFFF);
      RTC->ACP6 = (uint16_t)((int16_t)(data_u32[3] * pclk_mul));
      RTC->ACP7 = (uint16_t)((data_u32[3] >> 16) & 0xFFFF);    
    }
    else
    {
      /* Get information */
      RTCTempData->RTCTempP0 = 0;
      RTCTempData->RTCTempP1 = 0;
      RTCTempData->RTCTempP2 = 0;
      RTCTempData->RTCTempP5 = 0;
      RTCTempData->RTCTempP6 = 0;
      RTCTempData->RTCTempP7 = 0;     
      retval |= BIT1;
    }
  }
 
/*----------------------------------- P4 -------------------------------------*/
  /* Calculate checksum1 */
  data_u32[0] = *NVR_RTC1_P4;
  checksum = ~data_u32[0];
  if (checksum == (*NVR_RTC1_P4_CHKSUM))//checksum1 true 
  {
    /* Get information */
    RTCTempData->RTCTempP4 = (int16_t)data_u32[0];
    RTC->ACP4 = data_u32[0];   
  }
  else
  {
    data_u32[0] = *NVR_RTC2_P4;
    checksum = ~data_u32[0];
    if (checksum == (*NVR_RTC2_P4_CHKSUM))//checksum2 true
    {
      /* Get information */
      RTCTempData->RTCTempP4 = (int16_t)data_u32[0];
      RTC->ACP4 = data_u32[0];      
    }
    else
    {
      RTCTempData->RTCTempP4 = 0;
      
      retval |= BIT2;
    }
  }

/*-------------------------- RTC ACKx parameters -----------------------------*/
  data_u32[0] = *NVR_RTC1_ACK0;
  data_u32[1] = *NVR_RTC1_ACK1;
  data_u32[2] = *NVR_RTC1_ACK2;
  data_u32[3] = *NVR_RTC1_ACK3;
  data_u32[4] = *NVR_RTC1_ACK4;
  checksum = ~(data_u32[0] + data_u32[1] + data_u32[2] + data_u32[3] + data_u32[4]);
  if (checksum == (*NVR_RTC1_ACK_CHKSUM))//checksum1 true 
  {
    /* Get information */
    RTCTempData->RTCTempK0 = data_u32[0];
    RTCTempData->RTCTempK1 = data_u32[1];
    RTCTempData->RTCTempK2 = data_u32[2];
    RTCTempData->RTCTempK3 = data_u32[3];
    RTCTempData->RTCTempK4 = data_u32[4];
    
    /* Load data to ACKx register */
    RTC->ACK[0] = data_u32[0];
    RTC->ACK[1] = data_u32[1];
    RTC->ACK[2] = data_u32[2];
    RTC->ACK[3] = data_u32[3];
    RTC->ACK[4] = data_u32[4];    
  }
  else
  {
    data_u32[0] = *NVR_RTC2_ACK0;
    data_u32[1] = *NVR_RTC2_ACK1;
    data_u32[2] = *NVR_RTC2_ACK2;
    data_u32[3] = *NVR_RTC2_ACK3;
    data_u32[4] = *NVR_RTC2_ACK4;
    checksum = ~(data_u32[0] + data_u32[1] + data_u32[2] + data_u32[3] + data_u32[4]);
    if (checksum == (*NVR_RTC2_ACK_CHKSUM))//checksum2 true 
    {
      /* Get information */
      RTCTempData->RTCTempK0 = data_u32[0];
      RTCTempData->RTCTempK1 = data_u32[1];
      RTCTempData->RTCTempK2 = data_u32[2];
      RTCTempData->RTCTempK3 = data_u32[3];
      RTCTempData->RTCTempK4 = data_u32[4];
   
      /* Load data to ACKx register */
      RTC->ACK[0] = data_u32[0];
      RTC->ACK[1] = data_u32[1];
      RTC->ACK[2] = data_u32[2];
      RTC->ACK[3] = data_u32[3];
      RTC->ACK[4] = data_u32[4];      
    }
    else
    {
      /* Get information */
      RTCTempData->RTCTempK0 = 0;
      RTCTempData->RTCTempK1 = 0;
      RTCTempData->RTCTempK2 = 0;
      RTCTempData->RTCTempK3 = 0;
      RTCTempData->RTCTempK4 = 0;
      
      retval |= BIT3;
    }
  }
  
/*-------------------------- RTC ACTI parameters -----------------------------*/
  data_u32[0] = *NVR_RTC1_ACTI;
  checksum = ~data_u32[0];
  if (checksum == (*NVR_RTC1_ACTI_CHKSUM))
  {
    /* Get information */
    RTCTempData->RTCACTI = data_u32[0];
    /* Load data to ACKx register */
    RTC->ACTI = data_u32[0];
  }
  else
  {
    data_u32[0] = *NVR_RTC2_ACTI;
    checksum = ~data_u32[0];  
    if (checksum == (*NVR_RTC2_ACTI_CHKSUM))
    {
      /* Get information */
      RTCTempData->RTCACTI = data_u32[0];
      /* Load data to ACKx register */
      RTC->ACTI = data_u32[0];     
    }
    else
    {
      /* Get information */
      RTCTempData->RTCACTI = 0;
      
      retval |= BIT4;
    }
  }
  
/*------------------------- RTC ACKTemp parameters ---------------------------*/
  data_u32[0] = *NVR_RTC1_ACKTEMP;
  checksum = ~data_u32[0];
  if (checksum == (*NVR_RTC1_ACKTEMP_CHKSUM))
  {
    /* Get information */
    RTCTempData->RTCACKTemp = data_u32[0];
    /* Load data to ACKx register */
    RTC->ACKTEMP = data_u32[0];    
  }
  else
  {
    data_u32[0] = *NVR_RTC2_ACKTEMP;
    checksum = ~data_u32[0];
    if (checksum == (*NVR_RTC2_ACKTEMP_CHKSUM))
    {
      /* Get information */
      RTCTempData->RTCACKTemp = data_u32[0];
      /* Load data to ACKx register */
      RTC->ACKTEMP = data_u32[0];  
    }
    else
    {
      /* Get information */
      RTCTempData->RTCACKTemp = 0; 
      
      retval |= BIT5;
    }
  }
/*--------------------------------- ACF200 -----------------------------------*/
  RTCTempData->RTCACF200 = (uint32_t)(int32_t)((pclk_mul * 0x320000));
  RTC->ACF200 = (uint32_t)(int32_t)((pclk_mul * 0x320000));

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro(); 
  
  return retval;
}

/**
  * @breif  Gets Power/Clock Measure result.
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
  * @breif  Gets Chip ID.
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

/*********************************** END OF FILE ******************************/
