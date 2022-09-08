/**************************************************************************//**
 * @file     sys.c
 * @version  V3.00
 * @brief    M460 series SYS driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include "NuMicro.h"

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

int32_t g_SYS_i32ErrCode = 0;       /*!< SYS global error code */

/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/**
  * @brief      Clear reset source
  * @param[in]  u32Src is system reset source. Including :
  *             - \ref SYS_RSTSTS_CPULKRF_Msk
  *             - \ref SYS_RSTSTS_CPURF_Msk
  *             - \ref SYS_RSTSTS_HRESETRF_Msk
  *             - \ref SYS_RSTSTS_MCURF_Msk
  *             - \ref SYS_RSTSTS_BODRF_Msk
  *             - \ref SYS_RSTSTS_LVRF_Msk
  *             - \ref SYS_RSTSTS_WDTRF_Msk
  *             - \ref SYS_RSTSTS_PINRF_Msk
  *             - \ref SYS_RSTSTS_PORF_Msk
  * @return     None
  * @details    This function clear the selected system reset source.
  */
void SYS_ClearResetSrc(uint32_t u32Src)
{
    SYS->RSTSTS = u32Src;
}

/**
  * @brief      Get Brown-out detector output status
  * @param      None
  * @retval     0 System voltage is higher than BODVL setting or BODEN is 0.
  * @retval     1 System voltage is lower than BODVL setting.
  * @details    This function get Brown-out detector output status.
  */
uint32_t SYS_GetBODStatus(void)
{
    return ((SYS->BODCTL & SYS_BODCTL_BODOUT_Msk) >> SYS_BODCTL_BODOUT_Pos);
}

/**
  * @brief      Get reset status register value
  * @param      None
  * @return     Reset source
  * @details    This function get the system reset status register value.
  */
uint32_t SYS_GetResetSrc(void)
{
    return (SYS->RSTSTS);
}

/**
  * @brief      Check if register is locked nor not
  * @param      None
  * @retval     0 Write-protection function is disabled.
  *             1 Write-protection function is enabled.
  * @details    This function check register write-protection bit setting.
  */
uint32_t SYS_IsRegLocked(void)
{
    return SYS->REGLCTL & 1UL ? 0UL : 1UL;
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
  *             The register write-protection function should be disabled before using this function.
  */
void SYS_ResetChip(void)
{
    SYS->IPRST0 |= SYS_IPRST0_CHIPRST_Msk;
}

/**
  * @brief      Reset chip with CPU reset
  * @param      None
  * @return     None
  * @details    This function reset CPU with CPU reset.
  *             The register write-protection function should be disabled before using this function.
  */
void SYS_ResetCPU(void)
{
    SYS->IPRST0 |= SYS_IPRST0_CPURST_Msk;
}

/**
  * @brief      Reset selected module
  * @param[in]  u32ModuleIndex is module index. Including :
  *             - \ref PDMA0_RST
  *             - \ref PDMA1_RST
  *             - \ref EBI_RST
  *             - \ref EMAC0_RST
  *             - \ref SDH0_RST
  *             - \ref SDH1_RST
  *             - \ref CRC_RST
  *             - \ref CCAP_RST
  *             - \ref HSUSBD_RST
  *             - \ref HBI_RST
  *             - \ref CRPT_RST
  *             - \ref KS_RST
  *             - \ref SPIM_RST
  *             - \ref HSUSBH_RST
  *             - \ref CANFD0_RST
  *             - \ref CANFD1_RST
  *             - \ref CANFD2_RST
  *             - \ref CANFD3_RST
  *             - \ref GPIO_RST
  *             - \ref TMR0_RST
  *             - \ref TMR1_RST
  *             - \ref TMR2_RST
  *             - \ref TMR3_RST
  *             - \ref ACMP01_RST
  *             - \ref ACMP23_RST
  *             - \ref I2C0_RST
  *             - \ref I2C1_RST
  *             - \ref I2C2_RST
  *             - \ref I2C3_RST
  *             - \ref I2C4_RST
  *             - \ref QSPI0_RST
  *             - \ref QSPI1_RST
  *             - \ref SPI0_RST
  *             - \ref SPI1_RST
  *             - \ref SPI2_RST
  *             - \ref SPI3_RST
  *             - \ref SPI4_RST
  *             - \ref SPI5_RST
  *             - \ref SPI6_RST
  *             - \ref SPI7_RST
  *             - \ref SPI8_RST
  *             - \ref SPI9_RST
  *             - \ref SPI10_RST
  *             - \ref UART0_RST
  *             - \ref UART1_RST
  *             - \ref UART2_RST
  *             - \ref UART3_RST
  *             - \ref UART4_RST
  *             - \ref UART5_RST
  *             - \ref UART6_RST
  *             - \ref UART7_RST
  *             - \ref UART8_RST
  *             - \ref UART9_RST
  *             - \ref OTG_RST
  *             - \ref USBD_RST
  *             - \ref EADC0_RST
  *             - \ref EADC1_RST
  *             - \ref EADC2_RST
  *             - \ref I2S0_RST
  *             - \ref I2S1_RST
  *             - \ref HSOTG_RST
  *             - \ref TRNG_RST
  *             - \ref SC0_RST
  *             - \ref SC1_RST
  *             - \ref SC2_RST
  *             - \ref USCI0_RST
  *             - \ref PSIO_RST
  *             - \ref DAC_RST
  *             - \ref EPWM0_RST
  *             - \ref EPWM1_RST
  *             - \ref BPWM0_RST
  *             - \ref BPWM1_RST
  *             - \ref EQEI0_RST
  *             - \ref EQEI1_RST
  *             - \ref EQEI2_RST
  *             - \ref EQEI3_RST
  *             - \ref ECAP0_RST
  *             - \ref ECAP1_RST
  *             - \ref ECAP2_RST
  *             - \ref ECAP3_RST
  *             - \ref EADC1_RST
  *             - \ref KPI_RST
  * @return     None
  * @details    This function reset selected module.
  *             The register write-protection function should be disabled before using this function.
  */
void SYS_ResetModule(uint32_t u32ModuleIndex)
{
    uint32_t u32tmpVal = 0UL, u32tmpAddr = 0UL;

    /* Generate reset signal to the corresponding module */
    u32tmpVal = (1UL << (u32ModuleIndex & 0x00ffffffUL));
    u32tmpAddr = (uint32_t)&SYS->IPRST0 + ((u32ModuleIndex >> 24UL));
    *(volatile uint32_t *)u32tmpAddr |= u32tmpVal;

    /* Release corresponding module from reset state */
    u32tmpVal = ~(1UL << (u32ModuleIndex & 0x00ffffffUL));
    *(volatile uint32_t *)u32tmpAddr &= u32tmpVal;
}

/**
  * @brief      Enable and configure Brown-out detector function
  * @param[in]  i32Mode is reset or interrupt mode. Including :
  *             - \ref SYS_BODCTL_BOD_RST_EN
  *             - \ref SYS_BODCTL_BOD_INTERRUPT_EN
  * @param[in]  u32BODLevel is Brown-out voltage level. Including :
  *             - \ref SYS_BODCTL_BODVL_3_0V
  *             - \ref SYS_BODCTL_BODVL_2_8V
  *             - \ref SYS_BODCTL_BODVL_2_6V
  *             - \ref SYS_BODCTL_BODVL_2_4V
  *             - \ref SYS_BODCTL_BODVL_2_2V
  *             - \ref SYS_BODCTL_BODVL_2_0V
  *             - \ref SYS_BODCTL_BODVL_1_8V
  *             - \ref SYS_BODCTL_BODVL_1_6V
  * @return     None
  * @details    This function configure Brown-out detector reset or interrupt mode, enable Brown-out function and set Brown-out voltage level.
  *             The register write-protection function should be disabled before using this function.
  */
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel)
{
    /* Enable Brown-out Detector function */
    /* Enable Brown-out interrupt or reset function */
    /* Select Brown-out Detector threshold voltage */
    SYS->BODCTL = (SYS->BODCTL & ~(SYS_BODCTL_BODRSTEN_Msk | SYS_BODCTL_BODVL_Msk)) |
                  ((uint32_t)i32Mode) | (u32BODLevel) | (SYS_BODCTL_BODEN_Msk);
}

/**
  * @brief      Disable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This function disable Brown-out detector function.
  *             The register write-protection function should be disabled before using this function.
  */
void SYS_DisableBOD(void)
{
    SYS->BODCTL &= ~SYS_BODCTL_BODEN_Msk;
}

/**
  * @brief      Set Power Level
  * @param[in]  u32PowerLevel is power level setting. Including :
  *             - \ref SYS_PLCTL_PLSEL_PL0  : Supports system clock up to 200MHz.
  *             - \ref SYS_PLCTL_PLSEL_PL1  : Supports system clock up to 180MHz.
  * @return     None
  * @details    This function select power level.
  *             The register write-protection function should be disabled before using this function.
  * @note       This function sets g_SYS_i32ErrCode to SYS_TIMEOUT_ERR if waiting SYS time-out.
  */
void SYS_SetPowerLevel(uint32_t u32PowerLevel)
{
    uint32_t u32TimeOutCount = 0;

    g_SYS_i32ErrCode = 0;

    /* Wait for power level change busy flag is cleared */
    u32TimeOutCount = SystemCoreClock; /* 1 second time-out */
    while (SYS->PLSTS & SYS_PLSTS_PLCBUSY_Msk)
    {
        if (--u32TimeOutCount == 0)
        {
            g_SYS_i32ErrCode = SYS_TIMEOUT_ERR; /* Time-out error */
            break;
        }
    }

    /* Set power voltage level */
    SYS->PLCTL = (SYS->PLCTL & (~SYS_PLCTL_PLSEL_Msk)) | (u32PowerLevel);

    /* Wait for power level change busy flag is cleared */
    u32TimeOutCount = SystemCoreClock; /* 1 second time-out */
    while (SYS->PLSTS & SYS_PLSTS_PLCBUSY_Msk)
    {
        if (--u32TimeOutCount == 0)
        {
            g_SYS_i32ErrCode = SYS_TIMEOUT_ERR; /* Time-out error */
            break;
        }
    }
}

/**
  * @brief      Set Reference Voltage
  * @param[in]  u32VRefCTL is reference voltage setting. Including :
  *             - \ref SYS_VREFCTL_VREF_PIN
  *             - \ref SYS_VREFCTL_VREF_1_6V
  *             - \ref SYS_VREFCTL_VREF_2_0V
  *             - \ref SYS_VREFCTL_VREF_2_5V
  *             - \ref SYS_VREFCTL_VREF_3_0V
  * @return     None
  * @details    This function select reference voltage.
  *             The register write-protection function should be disabled before using this function.
  */
void SYS_SetVRef(uint32_t u32VRefCTL)
{
    /* Set reference voltage */
    SYS->VREFCTL = (SYS->VREFCTL & (~SYS_VREFCTL_VREFCTL_Msk)) | (u32VRefCTL);
}

/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif
