/*************************************************************************//**
 * @file     sys.c
 * @version  V1.00
 * $Revision: 16 $
 * $Date: 15/10/21 1:39p $
 * @brief    NUC472/NUC442 SYS driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include  "NUC472_442.h"
/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_SYS_Driver SYS Driver
  @{
*/


/** @addtogroup NUC472_442_SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/**
  * @brief  This function clear the selected system reset source
  * @param[in]  u32RstSrc is system reset source. Including:
    *           - \ref SYS_RSTSTS_PORF_Msk
    *           - \ref SYS_RSTSTS_PINRF_Msk
    *           - \ref SYS_RSTSTS_WDTRF_Msk
    *           - \ref SYS_RSTSTS_LVRF_Msk
    *           - \ref SYS_RSTSTS_BODRF_Msk
    *           - \ref SYS_RSTSTS_SYSRF_Msk
    *           - \ref SYS_RSTSTS_CPURF_Msk
  * @return None
  */
void SYS_ClearResetSrc(uint32_t u32RstSrc)
{
    SYS->RSTSTS |= u32RstSrc;
}

/**
  * @brief  This function get Brown-out detector output status
  * @return 0: System voltage is higher than BODVL setting or BODEN is 0.
  *         1: System voltage is lower than BODVL setting.
  *         Note : If the BOD_EN is 0, this function always return 0.
  */
uint32_t SYS_GetBODStatus()
{
    return (SYS->BODCTL & SYS_BODCTL_BODOUT_Msk);
}

/**
  * @brief  This function get the system reset source register value
  * @return Reset source
  */
uint32_t SYS_GetResetSrc(void)
{
    return (SYS->RSTSTS);
}

/**
  * @brief  This function check register write-protection bit setting
  * @return 0: Write-protection function is disabled.
  *         1: Write-protection function is enabled.
  */
uint32_t SYS_IsRegLocked(void)
{
    return !(SYS->REGLCTL & SYS_REGLCTL_REGLCTL_Msk);
}

/**
  * @brief  This function enable register write-protection function
  * @return None
  * @details To lock the protected register to forbid write access
  */
void SYS_LockReg(void)
{
    SYS->REGLCTL = 0;
}


/**
  * @brief  This function disable register write-protection function
  * @return None
  * @details To unlock the protected register to allow write access
  */
void SYS_UnlockReg(void)
{
    while(SYS->REGLCTL != SYS_REGLCTL_REGLCTL_Msk) {
        SYS->REGLCTL = 0x59;
        SYS->REGLCTL = 0x16;
        SYS->REGLCTL = 0x88;
    }
}

/**
  * @brief  This function get product ID.
  * @return Product ID
  */
uint32_t  SYS_ReadPDID(void)
{
    return SYS->PDID;
}

/**
  * @brief  This function reset chip.
  * @return None
  */
void SYS_ResetChip(void)
{
    SYS->IPRST0 |= SYS_IPRST0_CHIPRST_Msk;
}

/**
  * @brief  This function reset CPU.
  * @return None
  */
void SYS_ResetCPU(void)
{
    SYS->IPRST0 |= SYS_IPRST0_CPURST_Msk;
}

/**
  * @brief  This function reset selected modules.
  * @param[in]  u32ModuleIndex is module index. Including :
  * - \ref PDMA_RST
  * - \ref EBI_RST
  * - \ref USBH_RST
  * - \ref EMAC_RST
  * - \ref SDH_RST
  * - \ref CRC_RST
  * - \ref CAP_RST
  * - \ref CRYPTO_RST
  * - \ref GPIO_RST
  * - \ref TMR0_RST
  * - \ref TMR1_RST
  * - \ref TMR2_RST
  * - \ref TMR3_RST
  * - \ref ACMP_RST
  * - \ref I2C0_RST
  * - \ref I2C1_RST
  * - \ref I2C2_RST
  * - \ref I2C3_RST
  * - \ref SPI0_RST
  * - \ref SPI1_RST
  * - \ref SPI2_RST
  * - \ref SPI3_RST
  * - \ref UART0_RST
  * - \ref UART1_RST
  * - \ref UART2_RST
  * - \ref UART3_RST
  * - \ref UART4_RST
  * - \ref UART5_RST
  * - \ref CAN0_RST
  * - \ref CAN1_RST
  * - \ref OTG_RST
  * - \ref USBD_RST
  * - \ref ADC_RST
  * - \ref I2S0_RST
  * - \ref I2S1_RST
  * - \ref PS2_RST
  * - \ref SC0_RST
  * - \ref SC1_RST
  * - \ref SC2_RST
  * - \ref SC3_RST
  * - \ref SC4_RST
  * - \ref SC5_RST
  * - \ref I2C4_RST
  * - \ref PWM0_RST
  * - \ref PWM1_RST
  * - \ref QEI0_RST
  * - \ref QEI1_RST
  * @return None
  */
void SYS_ResetModule(uint32_t u32ModuleIndex)
{
    *(volatile uint32_t *)((uint32_t)&(SYS->IPRST0) + (u32ModuleIndex>>24)) |= 1<<(u32ModuleIndex & 0x00ffffff);
    *(volatile uint32_t *)((uint32_t)&(SYS->IPRST0) + (u32ModuleIndex>>24)) &= ~(1<<(u32ModuleIndex & 0x00ffffff));
}

/**
  * @brief  This function configure BOD function.
  *         Configure BOD reset or interrupt mode and set Brown-out voltage level.
  *         Enable Brown-out function
  * @param[in]  i32Mode is reset or interrupt mode. Including :
  *         - \ref SYS_BODCTL_BODRSTEN
  *         - \ref SYS_BODCTL_BODINTEN
  * @param[in]  u32BODLevel is Brown-out voltage level. Including :
  *         - \ref SYS_BODCTL_BODVL_2_2V
  *         - \ref SYS_BODCTL_BODVL_2_7V
  *         - \ref SYS_BODCTL_BODVL_3_8V
  *         - \ref SYS_BODCTL_BODVL_4_5V
  *
  * @return None
  */
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel)
{
    SYS->BODCTL &= ~(SYS_BODCTL_BODVL_Msk|SYS_BODCTL_BODRSTEN_Msk);
    SYS->BODCTL |=(i32Mode|u32BODLevel|SYS_BODCTL_BODEN_Msk);
}

/**
  * @brief  This function disable BOD function.
  * @return None
  */
void SYS_DisableBOD(void)
{
    SYS->BODCTL  &= ~SYS_BODCTL_BODEN_Msk;
}



/*@}*/ /* end of group NUC472_442_SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_SYS_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

