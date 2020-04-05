/**************************************************************************//**
 * @file     sys.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 15/05/04 3:27p $
 * @brief    SYS driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "NUC100Series.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SYS_Driver SYS Driver
  @{
*/


/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/**
  * @brief      Clear reset source
  * @param[in]  u32Src is system reset source. Including :
  *             - \ref SYS_RSTSRC_RSTS_CPU_Msk
  *             - \ref SYS_RSTSRC_RSTS_SYS_Msk
  *             - \ref SYS_RSTSRC_RSTS_BOD_Msk
  *             - \ref SYS_RSTSRC_RSTS_LVR_Msk
  *             - \ref SYS_RSTSRC_RSTS_WDT_Msk
  *             - \ref SYS_RSTSRC_RSTS_RESET_Msk
  *             - \ref SYS_RSTSRC_RSTS_POR_Msk
  * @return     None
  * @details    This function clear the selected system reset source.
  */
void SYS_ClearResetSrc(uint32_t u32Src)
{
    SYS->RSTSRC |= u32Src;
}

/**
  * @brief      Get Brown-out detector output status
  * @param      None
  * @retval     0 System voltage is higher than BOD_VL setting or BOD_EN is 0.
  * @retval     1 System voltage is lower than BOD_VL setting.
  * @details    This function get Brown-out detector output status.
  *             If the BOD_EN is 0, this function always return 0.
  */
uint32_t SYS_GetBODStatus(void)
{
    return (SYS->BODCR & SYS_BODCR_BOD_OUT_Msk) ? 1 : 0;
}

/**
  * @brief      Get reset source
  * @param      None
  * @return     Reset source
  * @details    This function get the system reset source register value.
  */
uint32_t SYS_GetResetSrc(void)
{
    return (SYS->RSTSRC);
}

/**
  * @brief      Check if register lock is set
  * @param      None
  * @retval     0 Write-protection function is disabled.
  * @retval     1 Write-protection function is enabled.
  * @details    This function check register write-protection bit setting.
  */
uint32_t SYS_IsRegLocked(void)
{
    return !(SYS->REGWRPROT & SYS_REGWRPROT_REGPROTDIS_Msk);
}

/**
  * @brief      Get product ID
  * @param      None
  * @return     Product ID
  * @details    This function get product ID.
  */
uint32_t  SYS_ReadPDID(void)
{
    return SYS->PDID;
}

/**
  * @brief      Reset chip with chip reset
  * @param      None
  * @return     None
  * @details    This function reset chip with chip reset.
  */
void SYS_ResetChip(void)
{
    SYS->IPRSTC1 |= SYS_IPRSTC1_CHIP_RST_Msk;
}

/**
  * @brief      Reset chip with CPU reset
  * @param      None
  * @return     None
  * @details    This function reset CPU with CPU reset.
  */
void SYS_ResetCPU(void)
{
    SYS->IPRSTC1 |= SYS_IPRSTC1_CPU_RST_Msk;
}

/**
  * @brief      Reset Module
  * @param[in]  u32ModuleIndex is module index. Including :
  *             - \ref PDMA_RST
  *             - \ref EBI_RST
  *             - \ref GPIO_RST
  *             - \ref TMR0_RST
  *             - \ref TMR1_RST
  *             - \ref TMR2_RST
  *             - \ref TMR3_RST
  *             - \ref I2C0_RST
  *             - \ref I2C1_RST
  *             - \ref SPI0_RST
  *             - \ref SPI1_RST
  *             - \ref SPI2_RST
  *             - \ref SPI3_RST
  *             - \ref UART0_RST
  *             - \ref UART1_RST
  *             - \ref UART2_RST
  *             - \ref PWM03_RST
  *             - \ref PWM47_RST
  *             - \ref ACMP_RST
  *             - \ref PS2_RST
  *             - \ref USBD_RST
  *             - \ref ADC_RST
  *             - \ref I2S_RST
  *             - \ref SC0_RST
  *             - \ref SC1_RST
  *             - \ref SC2_RST
  * @return     None
  * @details    This function reset selected module.
  */
void SYS_ResetModule(uint32_t u32ModuleIndex)
{
    /* Generate reset signal to the corresponding module */
    *(volatile uint32_t *)((uint32_t)&SYS->IPRSTC1 + (u32ModuleIndex >> 24))  |= 1 << (u32ModuleIndex & 0x00ffffff);

    /* Release corresponding module from reset state */
    *(volatile uint32_t *)((uint32_t)&SYS->IPRSTC1 + (u32ModuleIndex >> 24))  &= ~(1 << (u32ModuleIndex & 0x00ffffff));

}

/**
  * @brief      Enable and set Brown-out detector function
  * @param[in]  i32Mode is reset or interrupt mode. Including :
  *             - \ref SYS_BODCR_BOD_RST_EN
  *             - \ref SYS_BODCR_BOD_INTERRUPT_EN
  * @param[in]  u32BODLevel is Brown-out voltage level. Including :
  *             - \ref SYS_BODCR_BOD_VL_4_4V
  *             - \ref SYS_BODCR_BOD_VL_3_7V
  *             - \ref SYS_BODCR_BOD_VL_2_7V
  *             - \ref SYS_BODCR_BOD_VL_2_2V
  * @return     None
  * @details    This function configure Brown-out detector function.
  *             It configure Brown-out detector reset or interrupt mode, enable Brown-out function and set Brown-out voltage level.
  *
  */
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel)
{
    SYS->BODCR |= SYS_BODCR_BOD_EN_Msk;
    SYS->BODCR = (SYS->BODCR & ~SYS_BODCR_BOD_RSTEN_Msk) | i32Mode;
    SYS->BODCR = (SYS->BODCR & ~SYS_BODCR_BOD_VL_Msk) | u32BODLevel;
}

/**
  * @brief      Disable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This function disable Brown-out detector function.
  */
void SYS_DisableBOD(void)
{
    SYS->BODCR &= ~SYS_BODCR_BOD_EN_Msk;
}



/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
