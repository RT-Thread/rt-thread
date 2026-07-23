/**
  ******************************************************************************
  * @file    system_target.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   system source file.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "target.h"

#define NVR_REGINFOCOUNT1        (0x80400)
#define NVR_REGINFOBAKOFFSET     (0x100)

/**
  * @brief  Setup the microcontroller system
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  uint32_t i,nCount,nValue,nAddress,nChecksum;
  
  nCount = *(__IO uint32_t *)NVR_REGINFOCOUNT1;
  nChecksum = nCount;
  nChecksum = ~nChecksum;
  if(nChecksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1+4))
  {
    nCount = *(__IO uint32_t *)(NVR_REGINFOCOUNT1+NVR_REGINFOBAKOFFSET);
    nChecksum = nCount;
    nChecksum = ~nChecksum;
    if(nChecksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1+NVR_REGINFOBAKOFFSET+4))
    {
      while(1);
    }
  }
  
  for(i=0; i<nCount; i++)
  {
    nAddress = *(__IO uint32_t *)(NVR_REGINFOCOUNT1+8+i*12);
    nValue = *(__IO uint32_t *)(NVR_REGINFOCOUNT1+12+i*12);
    nChecksum = nAddress + nValue;
    nChecksum = ~nChecksum;
    if(nChecksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1+16+i*12))
    {
      nAddress = *(__IO uint32_t *)(NVR_REGINFOCOUNT1+NVR_REGINFOBAKOFFSET+8+i*12);
      nValue = *(__IO uint32_t *)(NVR_REGINFOCOUNT1+NVR_REGINFOBAKOFFSET+12+i*12);
      nChecksum = nAddress + nValue;
      nChecksum = ~nChecksum;
      if(nChecksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1+NVR_REGINFOBAKOFFSET+16+i*12))
      {
        while(1);
      }
    }
    if((nAddress>=0x40014800) && (nAddress<=0x40015000))
    {
      RTC_WriteRegisters(nAddress, &nValue, 1);
    }
    else
    {
      *(__IO uint32_t *)(nAddress) = nValue;
    }
  }
}

/**
  * @brief  Initializes registers.
  * @param  None
  * @retval None
  */
void SystemUpdate(void)
{
 
}


/*********************************** END OF FILE ******************************/
