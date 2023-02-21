/**************************************************************************//**
 * @file     sys.c
 * @brief    SYS driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
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


/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/**
  * @brief      Reset selected module
  * @param[in]  u32ModuleIndex is module index. Including :
  *             - \ref PDMA0_RST
  *             - \ref PDMA1_RST
  *             - \ref PDMA2_RST
  *             - \ref PDMA3_RST
  *             - \ref DISPC_RST
  *             - \ref VCAP0_RST
  *             - \ref VCAP1_RST
  *             - \ref GFX_RST
  *             - \ref VDEC_RST
  *             - \ref WRHO0_RST
  *             - \ref WRHO1_RST
  *             - \ref GMAC0_RST
  *             - \ref GMAC1_RST
  *             - \ref HWSEM0_RST
  *             - \ref EBI_RST
  *             - \ref HSUSBH0_RST
  *             - \ref HSUSBH1_RST
  *             - \ref HSUSBD_RST
  *             - \ref USBHL_RST
  *             - \ref SDH0_RST
  *             - \ref SDH1_RST
  *             - \ref NAND_RST
  *             - \ref GPIO_RST
  *             - \ref MCTLP_RST
  *             - \ref MCTLC_RST
  *             - \ref DDRPUB_RST
  *             - \ref TMR0_RST
  *             - \ref TMR1_RST
  *             - \ref TMR2_RST
  *             - \ref TMR3_RST
  *             - \ref I2C0_RST
  *             - \ref I2C1_RST
  *             - \ref I2C2_RST
  *             - \ref I2C3_RST
  *             - \ref QSPI0_RST
  *             - \ref SPI0_RST
  *             - \ref SPI1_RST
  *             - \ref SPI2_RST
  *             - \ref UART0_RST
  *             - \ref UART1_RST
  *             - \ref UART2_RST
  *             - \ref UART3_RST
  *             - \ref UART4_RST
  *             - \ref UART5_RST
  *             - \ref UART6_RST
  *             - \ref UART7_RST
  *             - \ref MCAN0_RST
  *             - \ref MCAN1_RST
  *             - \ref EADC0_RST
  *             - \ref I2S0_RST
  *             - \ref SC0_RST
  *             - \ref SC1_RST
  *             - \ref QSPI1_RST
  *             - \ref SPI3_RST
  *             - \ref EPWM0_RST
  *             - \ref EPWM1_RST
  *             - \ref QEI0_RST
  *             - \ref QEI1_RST
  *             - \ref ECAP0_RST
  *             - \ref ECAP1_RST
  *             - \ref MCAN2_RST
  *             - \ref ADC0_RST
  *             - \ref TMR4_RST
  *             - \ref TMR5_RST
  *             - \ref TMR6_RST
  *             - \ref TMR7_RST
  *             - \ref TMR8_RST
  *             - \ref TMR9_RST
  *             - \ref TMR10_RST
  *             - \ref TMR11_RST
  *             - \ref UART8_RST
  *             - \ref UART9_RST
  *             - \ref UART10_RST
  *             - \ref UART11_RST
  *             - \ref UART12_RST
  *             - \ref UART13_RST
  *             - \ref UART14_RST
  *             - \ref UART15_RST
  *             - \ref UART16_RST
  *             - \ref I2S1_RST
  *             - \ref I2C4_RST
  *             - \ref I2C5_RST
  *             - \ref EPWM2_RST
  *             - \ref ECAP2_RST
  *             - \ref QEI2_RST
  *             - \ref MCAN3_RST
  *             - \ref KPI_RST
  *             - \ref GIC_RST
  *             - \ref SSMCC_RST
  *             - \ref SSPCC_RST
  * @return     None
  * @details    This function reset selected module.
  */
void SYS_ResetModule(uint32_t u32ModuleIndex)
{
    uint32_t u32tmpVal = 0UL, u32tmpAddr = 0UL;

    /* Generate reset signal to the corresponding module */
    u32tmpVal = (1UL << (u32ModuleIndex & 0x00ffffffUL));
    u32tmpAddr = (vu32)&SYS->IPRST0 + ((u32ModuleIndex >> 24UL));
    *(vu32 *)u32tmpAddr |= u32tmpVal;

    /* Release corresponding module from reset state */
    u32tmpVal = ~(1UL << (u32ModuleIndex & 0x00ffffffUL));
    *(vu32 *)u32tmpAddr &= u32tmpVal;
}


/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

