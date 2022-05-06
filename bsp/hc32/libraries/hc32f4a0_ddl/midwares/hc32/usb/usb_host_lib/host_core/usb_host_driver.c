/**
 *******************************************************************************
 * @file  usb_host_driver.c
 * @brief Host Interface Layer.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_driver.h"
#include "usb_bsp.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Initialize the driver for the host mode
 * @param  [in] pdev        device instance
 * @retval None
 */
void host_driver_init(usb_core_instance *pdev)
{
    uint8_t i;

    pdev->host.is_dev_connect = 0U;
    for (i = 0U; i < USB_MAX_TX_FIFOS; i++) {
        pdev->host.ErrCnt[i] = 0U;
        pdev->host.XferCnt[i] = 0U;
        pdev->host.HC_Status[i] = HOST_CH_IDLE;
    }
    pdev->host.hc[0].max_packet = 8U;

    usb_setregaddr(&pdev->regs, &pdev->basic_cfgs);;

    usb_gintdis(&pdev->regs);
    usb_initusbcore(&pdev->regs, &pdev->basic_cfgs);
    /* force to work in host mode*/
    usb_modeset(&pdev->regs, HOST_MODE);
    /* configure charge pump IO */
    usb_bsp_cfgvbus(&pdev->regs);
    usb_vbusctrl(&pdev->regs, 1U);
    usb_mdelay(50UL);

    usb_hostmodeinit(&pdev->regs, &pdev->basic_cfgs);
    usb_ginten(&pdev->regs);
}

/**
 * @brief  get current speed when in host mode
 * @param  [in] pdev        device instance
 * @retval current speed
 */
uint32_t host_driver_getcurrentspd(usb_core_instance *pdev)
{
    uint32_t u32hppt;
    u32hppt = READ_REG32(*pdev->regs.HPRT);
    return ((u32hppt & USBFS_HPRT_PSPD) >> USBFS_HPRT_PSPD_POS);
}

/**
 * @brief  get current DM DP state
 * @param  [in] pdev        device instance
 * @retval DM DP state
 *         0x00 DM L, DP L
 *         0x01 DM L, DP H
 *         0x02 DM H, DP L
 *         0x03 DM H, DP H
 */
uint32_t host_driver_getdmdpstate(usb_core_instance *pdev)
{
    uint32_t u32hppt;
    u32hppt = READ_REG32(*pdev->regs.HPRT);
    return ((u32hppt & USBFS_HPRT_PLSTS) >> USBFS_HPRT_PLSTS_POS);
}

/**
 * @brief  get vbus drive state
 * @param  [in] pdev        device instance
 * @retval vbus driver state
 *         0x00 vbus driver disable
 *         0x01 vbus driver enable
 */
uint32_t host_driver_getvbusdrivestate(usb_core_instance *pdev)
{
    uint32_t u32hppt;
    u32hppt = READ_REG32(*pdev->regs.HPRT);
    return ((u32hppt & USBFS_HPRT_PWPR) >> USBFS_HPRT_PWPR_POS);
}

/**
 * @brief  reset the port
 * @param  [in] pdev        device instance
 * @retval None
 */
void host_driver_portrst(usb_core_instance *pdev)
{
    usb_hprtrst(&pdev->regs);
}

/**
 * @brief  get the connected status of the device
 * @param  [in] pdev        device instance
 * @retval 1 connected or 0 disconnected
 */
uint32_t host_driver_ifdevconnected(usb_core_instance *pdev)
{
    return (pdev->host.is_dev_connect);
}

/**
 * @brief  gets the frame number for of sof packet
 * @param  [in] pdev        device instance
 * @retval number of frame
 */
uint32_t host_driver_getcurrentfrm(usb_core_instance *pdev)
{
    return (READ_REG32(pdev->regs.HREGS->HFNUM) & 0xFFFFUL) ;
}

/**
 * @brief  gets the last xfer state
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      channel number
 * @retval HOST_CH_XFER_STATE
 */
HOST_CH_XFER_STATE host_driver_getxferstate(usb_core_instance *pdev, uint8_t ch_num)
{
    return pdev->host.URB_State[ch_num] ;
}

/**
 * @brief  gets the xfer count
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      channel number
 * @retval number of data trandmitted in bytes
 */
uint32_t host_driver_getxfercnt(usb_core_instance *pdev, uint8_t ch_num)
{
    return pdev->host.XferCnt[ch_num] ;
}

/**
 * @brief  gets the host channel status
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      channel number
 * @retval HOST_CH_STATUS
 */
HOST_CH_STATUS host_driver_gethostchstate(usb_core_instance *pdev,  uint8_t ch_num)
{
    return pdev->host.HC_Status[ch_num] ;
}

/**
 * @brief  prepare a host channel and start a transfer
 * @param  [in] pdev        device instance
 * @param  [in] hc_num      channel number
 * @retval status
 */
uint32_t host_driver_hostch_init(usb_core_instance *pdev, uint8_t hc_num)
{
    return usb_inithch(&pdev->regs, hc_num, &pdev->host.hc[hc_num], pdev->basic_cfgs.dmaen);
}

/**
 * @brief  prepare a host channel and start a transfer
 * @param  [in] pdev        device instance
 * @param  [in] hc_num      channel number
 * @retval status
 */
uint32_t host_driver_submitrequest(usb_core_instance *pdev, uint8_t hc_num)
{
    pdev->host.URB_State[hc_num] = HOST_CH_XFER_IDLE;
    pdev->host.hc[hc_num].xfer_count = 0U ;
    return usb_hchtransbegin(&pdev->regs, hc_num, &pdev->host.hc[hc_num], pdev->basic_cfgs.dmaen);
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
