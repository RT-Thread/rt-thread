/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file usbhs_defines.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __USBHS_DEF_H__
#define __USBHS_DEF_H__

#include  "usbhs_conf.h"


#define USB_SPEED_PARAM_HIGH 0
#define USB_SPEED_PARAM_HIGH_IN_FULL 1

#define USB_EMBEDDED_PHY    1

#define GAHBCFG_TXFEMPTYLVL_EMPTY              1
#define GAHBCFG_TXFEMPTYLVL_HALFEMPTY          0
#define GAHBCFG_GLBINT_ENABLE                  1
#define GAHBCFG_INT_DMA_BURST_SINGLE           0
#define GAHBCFG_INT_DMA_BURST_INCR             1
#define GAHBCFG_INT_DMA_BURST_INCR4            3
#define GAHBCFG_INT_DMA_BURST_INCR8            5
#define GAHBCFG_INT_DMA_BURST_INCR16           7
#define GAHBCFG_DMAENABLE                      1
#define GAHBCFG_TXFEMPTYLVL_EMPTY              1
#define GAHBCFG_TXFEMPTYLVL_HALFEMPTY          0
#define GRXSTS_PKTSTS_IN                       2
#define GRXSTS_PKTSTS_IN_XFER_COMP             3
#define GRXSTS_PKTSTS_DATA_TOGGLE_ERR          5
#define GRXSTS_PKTSTS_CH_HALTED                7


#define A_HOST                                 1
#define A_SUSPEND                              2
#define A_PERIPHERAL                           3
#define B_PERIPHERAL                           4
#define B_HOST                                 5
#define DEVICE_MODE                            0
#define HOST_MODE                              1
#define OTG_MODE                               2

#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ     0
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ     1
#define DSTS_ENUMSPD_LS_PHY_6MHZ               2
#define DSTS_ENUMSPD_FS_PHY_48MHZ              3

#define DCFG_FRAME_INTERVAL_80                 0
#define DCFG_FRAME_INTERVAL_85                 1
#define DCFG_FRAME_INTERVAL_90                 2
#define DCFG_FRAME_INTERVAL_95                 3

#define DEP0CTRL_MPS_64                         0
#define DEP0CTRL_MPS_32                         1
#define DEP0CTRL_MPS_16                         2
#define DEP0CTRL_MPS_8                          3

#define EP_SPEED_LOW                           0
#define EP_SPEED_FULL                          1
#define EP_SPEED_HIGH                          2

#define EP_TYPE_CTRL                           0
#define EP_TYPE_ISOC                           1
#define EP_TYPE_BULK                           2
#define EP_TYPE_INTR                           3
#define EP_TYPE_MSK                            3

#define STS_GOUT_NAK                           1
#define STS_DATA_UPDT                          2
#define STS_XFER_COMP                          3
#define STS_SETUP_COMP                         4
#define STS_SETUP_UPDT                         6

#define HCH_PID_DATA0                          0
#define HCH_PID_DATA2                          1
#define HCH_PID_DATA1                          2
#define HCH_PID_SETUP                          3

#define HPCS_PRTSPD_HIGH_SPEED                 0
#define HPCS_PRTSPD_FULL_SPEED                 1
#define HPCS_PRTSPD_LOW_SPEED                  2

#define HCFG_30_60_MHZ                         0
#define HCFG_48_MHZ                            1
#define HCFG_6_MHZ                             2

#define HCHCTRL_CTRL                           0
#define HCHCTRL_ISOC                           1
#define HCHCTRL_BULK                           2
#define HCHCTRL_INTR                           3

#define MIN(a, b)      (((a) < (b)) ? (a) : (b))

typedef enum
{
  USBHS1_CORE_ID = 0,
  USBHS2_CORE_ID = 1
}USB_CORE_ID_TypeDef;

typedef enum
{
    USB_ENUM_HS = 0,
    USB_ENUM_FS = 1
}USB_ENUM_CORE;


#define USB_READ_REG32(REG) (*(__IO uint32_t *)(REG))
#define USB_WRITE_REG32(REG, VAL) (*(__IO uint32_t *)(REG) = (VAL))
#define USB_MODIFY_REG32(REG, clear_mask, set_mask)  USB_WRITE_REG32((REG), (((USB_READ_REG32(REG)) & ~(clear_mask)) | (set_mask)))

#define USB_SET_REG32_BIT(REG, BIT) ((*(__IO uint32_t *)(REG)) |= ((uint32_t)(BIT)))
#define USB_READ_REG32_BIT(REG, BIT) ((*(__IO uint32_t *)(REG)) &= ((uint32_t)(BIT)))
#define USB_CLR_REG32_BIT(REG, BIT) ((*(__IO uint32_t *)(REG)) &= ((uint32_t)(~((uint32_t)(BIT)))))

#define USB_CLR_REG32(REG) (*(__IO uint32_t *)(REG) = ((uint32_t)(0UL)))

/** ENUMERATION TYPE **/
enum USB_SPEED
{
    USB_SPEED_UNKNOWN = 0,
    USB_SPEED_LOW,
    USB_SPEED_FULL,
    USB_SPEED_HIGH
};

#endif /* __USB_DEFINES__H__ */
