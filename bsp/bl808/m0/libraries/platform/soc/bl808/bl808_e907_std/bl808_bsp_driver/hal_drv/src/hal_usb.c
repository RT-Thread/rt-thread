/**
 * @file hal_usb.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_usb.h"
#include "bl808_usb.h"
#include "bl808_glb.h"

#ifndef CONFIG_USB_VDMA_ENABLE
#define CONFIG_USB_VDMA_ENABLE
#endif

#ifndef CONFIG_USB_PINGPONG_ENABLE
// #define CONFIG_USB_PINGPONG_ENABLE
#endif

#ifndef CONFIG_USB_VDMA_OUT_ENABLE
// #define CONFIG_USB_VDMA_OUT_ENABLE
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define USB_DC_LOG_WRN(a, ...) //printf(a, ##__VA_ARGS__)
#define USB_DC_LOG_DBG(a, ...)
#define USB_DC_LOG_ERR(a, ...) //printf(a, ##__VA_ARGS__)
#define USB_DC_LOG(a, ...)     //printf(a, ##__VA_ARGS__)

static uint8_t fifo_ep_map[4] = { 0, 0, 0, 0 };

static usb_dc_device_t usb_hs_device __attribute__((section(".RW_OCRAM_NOINIT")));
static void USBD_IRQHandler(void);

static uint8_t usb_ep_is_enabled(uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    /* Check if ep enabled */
    if ((USB_EP_DIR_IS_OUT(ep)) &&
        usb_hs_device.out_ep[ep_idx].ep_ena) {
        return 1;
    } else if ((USB_EP_DIR_IS_IN(ep)) &&
               usb_hs_device.in_ep[ep_idx].ep_ena) {
        return 1;
    }

    return 0;
}
#ifndef CONFIG_USB_VDMA_ENABLE
static int usb_dma_write(uint8_t fifo_num, const uint8_t *data, uint32_t len)
{
    uint32_t timeout = 0xffffff;

    USB_DMA_Cfg_Type dma_cfg;

    dma_cfg.dir = USB_DMA_TRANS_DIR_MEM_2_FIFO;
    dma_cfg.memAddr = (uint32_t)(uintptr_t)data;
    dma_cfg.length = len;

    csi_dcache_clean_range((uint32_t *)data, len);
    /* dma config */
    USB_Set_DMA_Config(fifo_num, &dma_cfg);
    /* dma start */
    USB_Set_DMA_Start();
    /* dma wait */
    while (1) {
        if (USB_Get_Sub_Group_2_IntStatus() & USB_SUB_GROUP_2_ERROR_BIT_MUSK) {
            USB_DC_LOG_ERR("dma error\r\n");
            USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_ERROR_BIT_MUSK);
            return -USB_DC_DMA_ERR;
        }
        if (USB_Get_Sub_Group_2_IntStatus() & USB_SUB_GROUP_2_CMPLT_BIT_MUSK) {
            USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_CMPLT_BIT_MUSK);
            break;
        }
        timeout--;
        if (!timeout) {
            USB_DC_LOG_ERR("fifo%d wait free timeout\r\n", fifo_num);
            return -USB_DC_EP_TIMEOUT_ERR;
        }
    }
    USB_Reset_DMA_Accessing_Fifo();
    return 0;
}

static int usb_dma_read(uint8_t fifo_num, const uint8_t *data, uint32_t len)
{
    uint32_t timeout = 0xffffff;

    USB_DMA_Cfg_Type dma_cfg;

    dma_cfg.dir = USB_DMA_TRANS_DIR_FIFO_2_MEM;
    dma_cfg.memAddr = (uint32_t)(uintptr_t)data;
    dma_cfg.length = len;

    /* dma config */
    USB_Set_DMA_Config(fifo_num, &dma_cfg);
    /* dma start */
    USB_Set_DMA_Start();
    /* dma wait */
    while (1) {
        if (USB_Get_Sub_Group_2_IntStatus() & USB_SUB_GROUP_2_ERROR_BIT_MUSK) {
            USB_DC_LOG_ERR("dma error\r\n");
            USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_ERROR_BIT_MUSK);
            return -USB_DC_DMA_ERR;
        }
        if (USB_Get_Sub_Group_2_IntStatus() & USB_SUB_GROUP_2_CMPLT_BIT_MUSK) {
            USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_CMPLT_BIT_MUSK);
            break;
        }
        timeout--;
        if (!timeout) {
            USB_DC_LOG_ERR("fifo%d wait free timeout\r\n", fifo_num);
            return -USB_DC_EP_TIMEOUT_ERR;
        }
    }
    USB_Reset_DMA_Accessing_Fifo();
    csi_dcache_invalid_range((uint32_t *)data, len);
    return 0;
}
#else
static int usb_vdma_write(uint8_t fifo_num, const uint8_t *data, uint32_t len)
{
    uint32_t timeout = 0xffffff;

    USB_VDMA_Cfg_Type vdma_fifo_cfg;

    vdma_fifo_cfg.dir = USB_VDMA_TRANS_DIR_MEM_2_FIFO;
    vdma_fifo_cfg.memAddr = (uint32_t)(uintptr_t)data;
    vdma_fifo_cfg.length = len;

    csi_dcache_clean_range((uint32_t *)data, len);

    USB_Set_VDMA_Config(fifo_num, &vdma_fifo_cfg);
    USB_Set_VDMA_Start(fifo_num);

    while (USB_Get_VDMA_Start(fifo_num)) {
        timeout--;
        if (!timeout) {
            USB_DC_LOG_ERR("fifo%d wait free timeout\r\n", fifo_num);
            return -USB_DC_EP_TIMEOUT_ERR;
        }
    }

    return 0;
}

static int usb_vdma_read(uint8_t fifo_num, const uint8_t *data, uint32_t len)
{
    uint32_t timeout = 0xffffff;

    USB_VDMA_Cfg_Type vdma_fifo_cfg;

    vdma_fifo_cfg.dir = USB_VDMA_TRANS_DIR_FIFO_2_MEM;
    vdma_fifo_cfg.memAddr = (uint32_t)(uintptr_t)data;
    vdma_fifo_cfg.length = len;
    USB_Set_VDMA_Config(fifo_num, &vdma_fifo_cfg);
    USB_Set_VDMA_Start(fifo_num);

    while (USB_Get_VDMA_Start(fifo_num)) {
        timeout--;
        if (!timeout) {
            USB_DC_LOG_ERR("fifo%d wait free timeout\r\n", fifo_num);
            return -USB_DC_EP_TIMEOUT_ERR;
        }
    }

    csi_dcache_invalid_range((uint32_t *)data, len);
    return 0;
}
#endif

static uint8_t usb_get_transfer_fifo(uint8_t ep_idx)
{
    uint8_t target_fifo_id;

    if (usb_hs_device.out_ep[ep_idx].ep_cfg.ep_mps > 512 || usb_hs_device.in_ep[ep_idx].ep_cfg.ep_mps > 512) {
#ifdef CONFIG_USB_PINGPONG_ENABLE
        target_fifo_id = (4 * ep_idx - 3);
#else
        target_fifo_id = (2 * ep_idx - 1);
#endif
    } else {
#ifdef CONFIG_USB_PINGPONG_ENABLE
        target_fifo_id = (2 * ep_idx - 1);
#else
        target_fifo_id = ep_idx;
#endif
    }

    return target_fifo_id;
}

/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int usb_dc_init(void)
{
    CPU_Interrupt_Disable(USB_IRQn);

    PDS_Turn_On_USB(1);

    /* interrupt config */
    USB_Global_IntEnable(DISABLE);

    /* software reset usb */
    USB_NORMAL_Cfg_Type usbNormalCfg = {
#ifdef CONFIG_USB_HS
        .forceFullSpeed = 0,
#else
        .forceFullSpeed = 1,
#endif
        .chipEn = 1,
        .swRst = 1,
        .remoteWakeupEn = 0,
        .rstTimeOut = 0xFFFF
    };
    USB_Set_Normal_Config(&usbNormalCfg);
#ifdef CONFIG_USB_HS
    USB_SOF_Mask_Time_HighSpeed();
#else
    USB_SOF_Mask_Time_FullSpeed();
#endif
    USB_Set_Device_Address(0);
    USB_Non_Ctrl_Transfer_Disable();

    USB_Reset_FIFO(USB_FIFO_0);
    USB_Reset_FIFO(USB_FIFO_1);
    USB_Reset_FIFO(USB_FIFO_2);
    USB_Reset_FIFO(USB_FIFO_3);
    USB_Clear_CTRL_FIFO();

    USB_Group_IntMask(USB_GRP_INT_G0, UNMASK);
    USB_Group_IntMask(USB_GRP_INT_G1, UNMASK);
    USB_Group_IntMask(USB_GRP_INT_G2, UNMASK);
    USB_Group_IntMask(USB_GRP_INT_G3, UNMASK);
    USB_Group_IntMask(USB_GRP_INT_G4, UNMASK);

    USB_Global_IntMask(USB_GLOBAL_INT_DEV, UNMASK);
    USB_Global_IntMask(USB_GLOBAL_INT_OTG, MASK);
    USB_Global_IntMask(USB_GLOBAL_INT_HC, MASK);

    USB_Sub_Group_IntMask(USB_INT_DMA_CMPLT | USB_INT_DMA_ERROR | USB_INT_IDLE | USB_INT_RX0BYTE | USB_INT_TX0BYTE);
    USB_Sub_Group_IntMask(USB_INT_VDMA_CMPLT_CXF | USB_INT_VDMA_CMPLT_F0 | USB_INT_VDMA_CMPLT_F1 | USB_INT_VDMA_CMPLT_F2 | USB_INT_VDMA_CMPLT_F3 |
                          USB_INT_VDMA_ERROR_CXF | USB_INT_VDMA_ERROR_F0 | USB_INT_VDMA_ERROR_F1 | USB_INT_VDMA_ERROR_F2 | USB_INT_VDMA_ERROR_F3);

    USB_Sub_Group_IntUnmask(USB_INT_CX_SETUP | USB_INT_CX_IN | USB_INT_CX_OUT | USB_INT_CX_COMFAIL | USB_INT_CX_COMABORT);
    USB_Sub_Group_IntUnmask(USB_INT_RESET | USB_INT_SUSPEND | USB_INT_RESUME | USB_INT_RX0BYTE);

    USB_Get_Sub_Group_0_IntClear(USB_SUB_GROUP_0_CX_COMABORT_BIT_MUSK);
    USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_RESET_BIT_MUSK | USB_SUB_GROUP_2_SUSPEND_BIT_MUSK | USB_SUB_GROUP_2_RESUME_BIT_MUSK |
                                 USB_SUB_GROUP_2_TX0BYTE_BIT_MUSK | USB_SUB_GROUP_2_RX0BYTE_BIT_MUSK |
                                 USB_SUB_GROUP_2_CMPLT_BIT_MUSK | USB_SUB_GROUP_2_ERROR_BIT_MUSK);
    USB_Get_Sub_Group_3_IntClear(0xffffffff); //VDMA INT
    USB_Get_Sub_Group_4_IntClear(USB_SUB_GROUP_4_L1_BIT_MUSK);

    /* modify ep1 ~ ep8 fifo map ,default is fifo3 */
    for (uint8_t i = USB_Endpoint_1; i <= USB_Endpoint_8; i++) {
        USB_Set_FIFO_Of_Endpoint_IN(i, 15);
        USB_Set_FIFO_Of_Endpoint_OUT(i, 15);
    }

#ifdef CONFIG_USB_VDMA_ENABLE
    USB_Set_VDMA_Enable();
#endif

    memset(&usb_hs_device, 0, sizeof(usb_hs_device));

    usb_hs_device.out_ep[0].ep_ena = 1U;
    usb_hs_device.in_ep[0].ep_ena = 1U;
    usb_hs_device.out_ep[0].ep_cfg.ep_mps = 64;
    usb_hs_device.out_ep[0].ep_cfg.ep_type = USBD_EP_TYPE_CTRL;
    usb_hs_device.in_ep[0].ep_cfg.ep_mps = 64;
    usb_hs_device.in_ep[0].ep_cfg.ep_type = USBD_EP_TYPE_CTRL;

    Interrupt_Handler_Register(USB_IRQn, USBD_IRQHandler);
    CPU_Interrupt_Enable(USB_IRQn);
    USB_SoftDetach_Disable();
    USB_Global_IntEnable(ENABLE);

    return 0;
}

/**
 * @brief Set USB device address
 *
 * @param[in] addr Device address
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_set_address(const uint8_t addr)
{
    USB_Set_Device_Address(addr);
    return 0;
}

/**
 * @brief configure and enable endpoint
 * This function sets endpoint configuration according to one specified in USB
 * endpoint descriptor and then enables it for data transfers.
 *
 * @param dev
 * @param ep_cfg  ep_cfg Endpoint
 * @return int
 */
int usbd_ep_open(const struct usb_dc_ep_cfg *ep_cfg)
{
    uint8_t ep;
    USB_FIFO_Cfg_Type fifo_cfg;

    if (!ep_cfg) {
        return -1;
    }

    ep = ep_cfg->ep_addr;

    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (ep_idx > 4) {
        return -1;
    }

    USB_DC_LOG_DBG("%s ep %x, mps %d, type %d\r\n", __func__, ep, ep_cfg->ep_mps, ep_cfg->ep_type);

    if (ep_idx == 0) {
        return 0;
    }

    fifo_cfg.enable = 1;
    fifo_cfg.fifoType = ep_cfg->ep_type;
    fifo_cfg.epID = ep_idx;

    if (USB_EP_DIR_IS_OUT(ep)) {
        fifo_cfg.dir = USB_FIFO_DIR_OUT;
        usb_hs_device.out_ep[ep_idx].ep_cfg.ep_mps = ep_cfg->ep_mps;
        usb_hs_device.out_ep[ep_idx].ep_cfg.ep_type = ep_cfg->ep_type;
        usb_hs_device.out_ep[ep_idx].ep_ena = 1U;

        USB_Set_Endpoint_OUT_MaxPacketSize(ep_idx, ep_cfg->ep_mps);

    } else {
        fifo_cfg.dir = USB_FIFO_DIR_IN;
        usb_hs_device.in_ep[ep_idx].ep_cfg.ep_mps = ep_cfg->ep_mps;
        usb_hs_device.in_ep[ep_idx].ep_cfg.ep_type = ep_cfg->ep_type;
        usb_hs_device.in_ep[ep_idx].ep_ena = 1U;

        USB_Set_Endpoint_IN_MaxPacketSize(ep_idx, ep_cfg->ep_mps);
    }

#ifndef CONFIG_USB_PINGPONG_ENABLE
    fifo_cfg.blockType = USB_FIFO_BLOCK_CNT_SINGLE_BLOCK;

    if (ep_cfg->ep_mps <= 512) {
        if (ep_idx > 4) {
            return -1;
        }
        fifo_ep_map[0] = 0x01;
        fifo_ep_map[1] = 0x02;
        fifo_ep_map[2] = 0x03;
        fifo_ep_map[3] = 0x04;

        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_1, USB_FIFO_0);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_1, USB_FIFO_0);
        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_2, USB_FIFO_1);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_2, USB_FIFO_1);
        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_3, USB_FIFO_2);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_3, USB_FIFO_2);
        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_4, USB_FIFO_3);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_4, USB_FIFO_3);

        fifo_cfg.blockSize = USB_FIFO_BLOCK_MAX_SIZE_512;
        USB_Set_FIFO_Config(ep_idx - 1, &fifo_cfg);

        if (USB_EP_DIR_IS_OUT(ep)) {
#ifdef CONFIG_USB_VDMA_OUT_ENABLE
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0 + (ep_idx - 1)));
#else
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP1_INT_F0_OUT + 2 * (ep_idx - 1)));
#endif
        } else {
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0 + (ep_idx - 1)));
        }

        if (ep_cfg->ep_type == 0x01) {
            uint32_t tmpVal;
            tmpVal = BL_RD_WORD(USB_BASE + USB_DEV_INMPS1_OFFSET + 0x04 * (ep_idx - 1));
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_TX_NUM_HBW_IEP1, 0);
            BL_WR_WORD(USB_BASE + USB_DEV_INMPS1_OFFSET + 0x04 * (ep_idx - 1), tmpVal);
        }
    } else {
        if (ep_idx > 2) {
            return -1;
        }
        fifo_ep_map[0] = 0x01;
        fifo_ep_map[1] = 0x01;
        fifo_ep_map[2] = 0x02;
        fifo_ep_map[3] = 0x02;

        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_1, USB_FIFO_0);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_1, USB_FIFO_0);
        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_2, USB_FIFO_2);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_2, USB_FIFO_2);

        fifo_cfg.blockSize = USB_FIFO_BLOCK_MAX_SIZE_1024;
        USB_Set_FIFO_Config(2 * ep_idx - 2, &fifo_cfg);
        fifo_cfg.enable = 0;
        USB_Set_FIFO_Config(2 * ep_idx - 1, &fifo_cfg);

        if (USB_EP_DIR_IS_OUT(ep)) {
#ifdef CONFIG_USB_VDMA_OUT_ENABLE
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0 + 2 * (ep_idx - 1)));
#else
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP1_INT_F0_OUT + 4 * (ep_idx - 1)));
#endif
        } else {
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0 + 2 * (ep_idx - 1)));
        }

        if (ep_cfg->ep_type == 0x01) {
            uint32_t tmpVal;
            tmpVal = BL_RD_WORD(USB_BASE + USB_DEV_INMPS1_OFFSET + 0x04 * (ep_idx - 1));
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, USB_TX_NUM_HBW_IEP1, 0);
            BL_WR_WORD(USB_BASE + USB_DEV_INMPS1_OFFSET + 0x04 * (ep_idx - 1), tmpVal);
        }
    }
#else
    fifo_cfg.blockType = USB_FIFO_BLOCK_CNT_DOUBLE_BLOCKS;

    if (ep_cfg->ep_mps <= 512) {
        if (ep_idx > 2) {
            return -1;
        }
        fifo_ep_map[0] = 0x01;
        fifo_ep_map[1] = 0x01;
        fifo_ep_map[2] = 0x02;
        fifo_ep_map[3] = 0x02;

        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_1, USB_FIFO_0);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_1, USB_FIFO_0);
        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_2, USB_FIFO_2);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_2, USB_FIFO_2);

        fifo_cfg.blockSize = USB_FIFO_BLOCK_MAX_SIZE_512;
        USB_Set_FIFO_Config(2 * ep_idx - 2, &fifo_cfg);
        fifo_cfg.enable = 0;
        USB_Set_FIFO_Config(2 * ep_idx - 1, &fifo_cfg);

        if (USB_EP_DIR_IS_OUT(ep)) {
#ifdef CONFIG_USB_VDMA_OUT_ENABLE
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0 + 2 * (ep_idx - 1)));
#else
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP1_INT_F0_OUT + 4 * (ep_idx - 1)));
#endif
        } else {
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0 + 2 * (ep_idx - 1)));
        }
    } else {
        if (ep_idx > 1) {
            return -1;
        }

        fifo_ep_map[0] = 0x01;
        fifo_ep_map[1] = 0x01;
        fifo_ep_map[2] = 0x01;
        fifo_ep_map[3] = 0x01;

        USB_Set_FIFO_Of_Endpoint_IN(USB_Endpoint_1, USB_FIFO_0);
        USB_Set_FIFO_Of_Endpoint_OUT(USB_Endpoint_1, USB_FIFO_0);

        fifo_cfg.blockSize = USB_FIFO_BLOCK_MAX_SIZE_1024;
        USB_Set_FIFO_Config(2 * ep_idx - 2, &fifo_cfg);
        fifo_cfg.enable = 0;
        USB_Set_FIFO_Config(2 * ep_idx - 1, &fifo_cfg);
        USB_Set_FIFO_Config(2 * ep_idx, &fifo_cfg);
        USB_Set_FIFO_Config(2 * ep_idx + 1, &fifo_cfg);

        if (USB_EP_DIR_IS_OUT(ep)) {
#ifdef CONFIG_USB_VDMA_OUT_ENABLE
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0));
#else
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP1_INT_F0_OUT));
#endif
        } else {
            USB_Sub_Group_IntUnmask(1ULL << (USB_SUB_GRP3_INT_VDMA_CMPLT_F0));
        }
    }
#endif

    USB_Non_Ctrl_Transfer_Enable();

    return 0;
}

/**
 * @brief Disable the selected endpoint
 *
 * Function to disable the selected endpoint. Upon success interrupts are
 * disabled for the corresponding endpoint and the endpoint is no longer able
 * for transmitting/receiving data.
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_close(const uint8_t ep)
{
    return 0;
}
/**
 * @brief Set stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_set_stall(const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        if (ep_idx == 0) {
            USB_Set_CTRL_Endpoint_Stall_Once();
        } else {
            USB_Set_Endpoint_OUT_Stall(ep_idx, ENABLE);
            usb_hs_device.out_ep[ep_idx].is_stalled = 1U;
        }
    } else {
        if (ep_idx == 0) {
            USB_Set_CTRL_Endpoint_Stall_Once();
        } else {
            USB_Set_Endpoint_IN_Stall(ep_idx, ENABLE);
            usb_hs_device.in_ep[ep_idx].is_stalled = 1U;
        }
    }
    return 0;
}
/**
 * @brief Clear stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_clear_stall(const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (ep_idx) {
        if (USB_EP_DIR_IS_OUT(ep)) {
            USB_Reset_Endpoint_OUT_Data_Toggle_Sequence(ep_idx);
            USB_Set_Endpoint_OUT_Stall(ep_idx, DISABLE);
            usb_hs_device.out_ep[ep_idx].is_stalled = 0;
        } else {
            USB_Reset_Endpoint_IN_Data_Toggle_Sequence(ep_idx);
            USB_Set_Endpoint_IN_Stall(ep_idx, DISABLE);
            usb_hs_device.in_ep[ep_idx].is_stalled = 0;
        }
    }
    return 0;
}
/**
 * @brief Check if the selected endpoint is stalled
 *
 * @param dev usb device
 * @param[in]  ep       Endpoint address corresponding to the one
 *                      listed in the device configuration table
 * @param[out] stalled  Endpoint stall status
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_is_stalled(const uint8_t ep, uint8_t *stalled)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!stalled) {
        return -1;
    }
    *stalled = 0U;
    if (ep_idx == 0)
        return 0;

    if (USB_EP_DIR_IS_OUT(ep)) {
        if (usb_hs_device.out_ep[ep_idx].is_stalled) {
            *stalled = 1U;
        }
    } else {
        if (usb_hs_device.in_ep[ep_idx].is_stalled) {
            *stalled = 1U;
        }
    }

    return 0;
}

/**
 * @brief Write data to the specified endpoint
 *
 * This function is called to write data to the specified endpoint. The
 * supplied usbd_endpoint_callback function will be called when data is transmitted
 * out.
 *
 * @param dev
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  data      Pointer to data to write
 * @param[in]  data_len  Length of the data requested to write. This may
 *                       be zero for a zero length status packet.
 * @param[out] ret_bytes Bytes scheduled for transmission. This value
 *                       may be NULL if the application expects all
 *                       bytes to be written
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_write(const uint8_t ep, const uint8_t *data, uint32_t data_len, uint32_t *ret_bytes)
{
    uint32_t timeout = 0xffffff;
    uint32_t target_fifo_id = 0;
    uint8_t mps_over_flag = 0;
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    int ret = 0;
    /* Check if IN ep */
    if (USB_EP_GET_DIR(ep) != USB_EP_DIR_IN) {
        return -USB_DC_EP_DIR_ERR;
    }

    /* Check if ep enabled */
    if (!usb_ep_is_enabled(ep)) {
        return -USB_DC_EP_EN_ERR;
    }

    if (!data && data_len) {
        USB_DC_LOG_ERR("data is null\r\n");
        return -USB_DC_ADDR_ERR;
    }

    if (ep_idx == 0) {
        if (!data_len) {
            /* enable ep0 transfer */
            USB_CTRL_Endpoint_Data_Transfer_Done();
            return USB_DC_OK;
        }
        if (data_len > usb_hs_device.in_ep[ep_idx].ep_cfg.ep_mps) {
            /* Check if transfer len is too big */
            data_len = usb_hs_device.in_ep[ep_idx].ep_cfg.ep_mps;
            mps_over_flag = 1;
        }

#ifdef CONFIG_USB_VDMA_ENABLE
        ret = usb_vdma_write(0, data, data_len);
#else
        ret = usb_dma_write(0, data, data_len);
#endif
        if (ret < 0) {
            return ret;
        }
        if (!mps_over_flag) {
            USB_CTRL_Endpoint_Data_Transfer_Done();
        }

    } else {
        if (!data_len) {
            /* send zlp */
            USB_Endpoint_Transmit_Zero_Length_Packet(ep_idx);
            while (1) {
                if (USB_Is_Endpoint_Transfer_Zero_Length_Packet(ep_idx)) {
                    USB_Clear_Endpoint_Transfer_Zero_Length_Packet_Status(ep_idx);
                    break;
                }
                timeout--;
                if (!timeout) {
                    USB_DC_LOG_ERR("ep%d wait free timeout\r\n", ep);
                    return -USB_DC_EP_TIMEOUT_ERR;
                }
            }
            return USB_DC_OK;
        }

        target_fifo_id = usb_get_transfer_fifo(ep_idx);
#ifdef CONFIG_USB_VDMA_ENABLE
        ret = usb_vdma_write(target_fifo_id, data, data_len);
#else
        ret = usb_dma_write(target_fifo_id, data, data_len);
#endif
        if (ret < 0) {
            return ret;
        }
    }

    USB_DC_LOG_DBG("EP%d write %u bytes\r\n", ep_idx, data_len);

    if (ret_bytes) {
        *ret_bytes = data_len;
    }

    return USB_DC_OK;
}

/**
 * @brief Read data from the specified endpoint
 *
 * This function is called by the endpoint handler function, after an OUT
 * interrupt has been received for that EP. The application must only call this
 * function through the supplied usbd_ep_callback function. This function clears
 * the ENDPOINT NAK when max_data_len is 0, if all data in the endpoint FIFO has been read,
 * so as to accept more data from host.
 *
 * @param[in]  ep           Endpoint address corresponding to the one
 *                          listed in the device configuration table
 * @param[in]  data         Pointer to data buffer to write to
 * @param[in]  max_data_len Max length of data to read
 * @param[out] read_bytes   Number of bytes read. If data is NULL and
 *                          max_data_len is 0 the number of bytes
 *                          available for read should be returned.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_read(const uint8_t ep, uint8_t *data, uint32_t data_len, uint32_t *read_bytes)
{
    uint32_t read_len = 0;
    uint32_t target_fifo_id = 0;
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    int ret = 0;

    /* Check if OUT ep */
    if (USB_EP_GET_DIR(ep) != USB_EP_DIR_OUT) {
        USB_DC_LOG_ERR("Wrong endpoint direction\r\n");
        return -USB_DC_EP_DIR_ERR;
    }

    /* Check if ep enabled */
    if (!usb_ep_is_enabled(ep)) {
        USB_DC_LOG_ERR("Not enabled endpoint\r\n");
        return -USB_DC_EP_EN_ERR;
    }

    if (!data && data_len) {
        USB_DC_LOG_ERR("data is null\r\n");
        return -USB_DC_ADDR_ERR;
    }

    /* Allow to read 0 bytes */
    if (!data_len) {
        // if (ep_idx) {
        //     target_fifo_id = usb_get_transfer_fifo(ep_idx);
        //     uint32_t tmp = BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET);
        //     tmp &= ~(1 << (2 * (target_fifo_id - 1)));
        //     BL_WR_WORD(USB_BASE + USB_DEV_MISG1_OFFSET, tmp);
        // }
        return USB_DC_OK;
    }

    if (ep_idx == 0) {
        /*setup handler*/
        if ((data_len == 8) && !read_bytes) {
            USB_Get_Setup_Command((uint32_t *)data);
            return USB_DC_OK;
        } else {
            read_len = BL_GET_REG_BITS_VAL(BL_RD_REG(USB_BASE, USB_DEV_CXCFE), USB_CX_FNT);
#if defined(CONFIG_USB_VDMA_ENABLE)
            ret = usb_vdma_read(0, data, read_len);
#else
            ret = usb_dma_read(0, data, read_len);
#endif
            if (ret < 0) {
                return ret;
            }
        }
    } else {
        target_fifo_id = usb_get_transfer_fifo(ep_idx);
        read_len = USB_Get_OUT_FIFO_Count(target_fifo_id - 1);
        if (read_len == 0) {
            if (read_bytes) {
                *read_bytes = 0;
            }
            return 0;
        }
#ifdef CONFIG_USB_VDMA_ENABLE
        ret = usb_vdma_read(target_fifo_id, data, read_len);
#else
        ret = usb_dma_read(target_fifo_id, data, read_len);
#endif
        if (ret < 0) {
            return ret;
        }
    }
    if (read_bytes) {
        *read_bytes = read_len;
    }
    USB_DC_LOG_DBG("Read EP%d, req %d, read %d bytes\r\n", ep, data_len, *read_bytes);

    return USB_DC_OK;
}

int usbd_ep_write_async(const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint32_t target_fifo_id = 0;
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    /* Check if IN ep */
    if (USB_EP_GET_DIR(ep) != USB_EP_DIR_IN) {
        return -USB_DC_EP_DIR_ERR;
    }

    /* Check if ep enabled */
    if (!usb_ep_is_enabled(ep)) {
        return -USB_DC_EP_EN_ERR;
    }

    if (!data && data_len) {
        USB_DC_LOG_ERR("data is null\r\n");
        return -USB_DC_ADDR_ERR;
    }

    target_fifo_id = usb_get_transfer_fifo(ep_idx);

    USB_VDMA_Cfg_Type vdma_fifo_cfg;

    vdma_fifo_cfg.dir = USB_VDMA_TRANS_DIR_MEM_2_FIFO;
    vdma_fifo_cfg.memAddr = (uint32_t)(uintptr_t)data;
    vdma_fifo_cfg.length = data_len;

    USB_Set_VDMA_Config(target_fifo_id, &vdma_fifo_cfg);
    USB_Set_VDMA_Start(target_fifo_id);

    return 0;
}

int usbd_ep_read_async(const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint32_t target_fifo_id = 0;
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    /* Check if IN ep */
    if (USB_EP_GET_DIR(ep) != USB_EP_DIR_OUT) {
        return -USB_DC_EP_DIR_ERR;
    }

    /* Check if ep enabled */
    if (!usb_ep_is_enabled(ep)) {
        return -USB_DC_EP_EN_ERR;
    }

    if (!data && data_len) {
        USB_DC_LOG_ERR("data is null\r\n");
        return -USB_DC_ADDR_ERR;
    }

    target_fifo_id = usb_get_transfer_fifo(ep_idx);

    USB_VDMA_Cfg_Type vdma_fifo_cfg;

    vdma_fifo_cfg.dir = USB_VDMA_TRANS_DIR_FIFO_2_MEM;
    vdma_fifo_cfg.memAddr = (uint32_t)(uintptr_t)data;
    vdma_fifo_cfg.length = data_len;

    USB_Set_VDMA_Config(target_fifo_id, &vdma_fifo_cfg);
    USB_Set_VDMA_Start(target_fifo_id);

    return 0;
}

extern void usbd_event_notify_handler(uint8_t event, void *arg);

static void usb_group0_isr(void)
{
    uint32_t group0intstatus = USB_Get_Sub_Group_0_IntStatus() & ~USB_Get_Sub_Group_0_IntMask();

    if (group0intstatus & USB_SUB_GROUP_0_CX_COMABORT_BIT_MUSK) {
        /* CX_COMABT_INT  */
        USB_DC_LOG_ERR("CX COMABT\r\n");
        USB_Get_Sub_Group_0_IntClear(USB_SUB_GROUP_0_CX_COMABORT_BIT_MUSK);
        return;
    }
    if (group0intstatus & USB_SUB_GROUP_0_CX_COMFAIL_BIT_MUSK) {
        /* CX_COMFAIL_INT */
        USB_DC_LOG_ERR("CX COMFAIL\r\n");
        return;
    }
    if (group0intstatus & USB_SUB_GROUP_0_CX_OUT_BIT_MUSK) {
        /* CX_OUT_INT     */
        usbd_event_notify_handler(USB_DC_EVENT_EP0_OUT_NOTIFY, NULL);
        return;
    }
    if (group0intstatus & USB_SUB_GROUP_0_CX_IN_BIT_MUSK) {
        /* CX_IN_INT      */
        usbd_event_notify_handler(USB_DC_EVENT_EP0_IN_NOTIFY, NULL);
        return;
    }
    if (group0intstatus & USB_SUB_GROUP_0_CX_SETUP_BIT_MUSK) {
        /* CX_SETUP_INT   */
        usbd_event_notify_handler(USB_DC_EVENT_SETUP_NOTIFY, NULL);
        return;
    }
}
static void usb_group1_isr(void)
{
    uint32_t group1intstatus = USB_Get_Sub_Group_1_IntStatus() & ~USB_Get_Sub_Group_1_IntMask();

    if (group1intstatus & USB_SUB_GROUP_1_F0_OUT_BIT_MUSK) {
        /* F0_OUT_INT */
        //BL_WR_WORD(USB_BASE + USB_DEV_MISG1_OFFSET, BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET) | (1 << 0));
        usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[0] & 0x7f));
    }

    if (group1intstatus & USB_SUB_GROUP_1_F1_OUT_BIT_MUSK) {
        /* F1_OUT_INT */
        //BL_WR_WORD(USB_BASE + USB_DEV_MISG1_OFFSET, BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET) | (1 << 2));
        usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[1] & 0x7f));
    }

    if (group1intstatus & USB_SUB_GROUP_1_F2_OUT_BIT_MUSK) {
        /* F2_OUT_INT */
        //BL_WR_WORD(USB_BASE + USB_DEV_MISG1_OFFSET, BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET) | (1 << 4));
        usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[2] & 0x7f));
    }

    if (group1intstatus & USB_SUB_GROUP_1_F3_OUT_BIT_MUSK) {
        /* F3_OUT_INT */
        //BL_WR_WORD(USB_BASE + USB_DEV_MISG1_OFFSET, BL_RD_WORD(USB_BASE + USB_DEV_MISG1_OFFSET) | (1 << 6));
        usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[3] & 0x7f));
    }

    if (group1intstatus & USB_SUB_GROUP_1_F0_IN_BIT_MUSK) {
        /* F0_IN_INT  */
        usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[0] | 0x80));
    }

    if (group1intstatus & USB_SUB_GROUP_1_F1_IN_BIT_MUSK) {
        /* F1_IN_INT  */
        usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[1] | 0x80));
    }

    if (group1intstatus & USB_SUB_GROUP_1_F2_IN_BIT_MUSK) {
        /* F2_IN_INT  */
        usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[2] | 0x80));
    }

    if (group1intstatus & USB_SUB_GROUP_1_F3_IN_BIT_MUSK) {
        /* F3_IN_INT  */
        usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[3] | 0x80));
    }
}
static void usb_group2_isr(void)
{
    uint32_t group2intstatus = USB_Get_Sub_Group_2_IntStatus() & ~USB_Get_Sub_Group_2_IntMask();

    if (group2intstatus & USB_SUB_GROUP_2_WAKEUP_BY_VBUS_BIT_MUSK) {
        /* Dev_Wakeup_byVBUS */
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_IDLE_BIT_MUSK) {
        /* Dev_Idle(HOV) */
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_ERROR_BIT_MUSK) {
        /* DMA_ERROR(HOV) */
        USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_ERROR_BIT_MUSK);
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_CMPLT_BIT_MUSK) {
        /* DMA_CMPLT(HOV) */
        USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_CMPLT_BIT_MUSK);
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_RX0BYTE_BIT_MUSK) {
        /* RX0BYTE_INT */
        USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_RX0BYTE_BIT_MUSK);
        for (uint32_t i = USB_Endpoint_1; i <= USB_Endpoint_8; i++) {
            if (USB_Is_Endpoint_Receive_Zero_Length_Packet(i))
                USB_Clear_Endpoint_Receive_Zero_Length_Packet_Status(i);
        }
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_TX0BYTE_BIT_MUSK) {
        /* TX0BYTE_INT */
        USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_TX0BYTE_BIT_MUSK);
        for (uint32_t i = USB_Endpoint_1; i <= USB_Endpoint_8; i++) {
            if (USB_Is_Endpoint_Transfer_Zero_Length_Packet(i))
                USB_Clear_Endpoint_Transfer_Zero_Length_Packet_Status(i);
        }
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_RESUME_BIT_MUSK) {
        /* RESM_INT */
        USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_RESUME_BIT_MUSK);
        usbd_event_notify_handler(USB_DC_EVENT_RESUME, NULL);
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_SUSPEND_BIT_MUSK) {
        /* SUSP_INT */
        USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_SUSPEND_BIT_MUSK);
        usbd_event_notify_handler(USB_DC_EVENT_SUSPEND, NULL);
        return;
    }
    if (group2intstatus & USB_SUB_GROUP_2_RESET_BIT_MUSK) {
        /* USBRST_INT */
        USB_Get_Sub_Group_2_IntClear(USB_SUB_GROUP_2_RESET_BIT_MUSK);
        USB_Non_Ctrl_Transfer_Disable();
        USB_Reset_FIFO(USB_FIFO_0);
        USB_Reset_FIFO(USB_FIFO_1);
        USB_Reset_FIFO(USB_FIFO_2);
        USB_Reset_FIFO(USB_FIFO_3);
        USB_Clear_CTRL_FIFO();

#ifdef CONFIG_USB_HS
        USB_SOF_Mask_Time_HighSpeed();
#else
        USB_SOF_Mask_Time_FullSpeed();
#endif
        usbd_event_notify_handler(USB_DC_EVENT_RESET, NULL);
        return;
    }
}
#ifdef CONFIG_USB_VDMA_ENABLE
static void usb_group3_isr(void)
{
    uint32_t group3intstatus = USB_Get_Sub_Group_3_IntStatus() & ~USB_Get_Sub_Group_3_IntMask();

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_CMPLT_CXF_BIT_MUSK) {
        /* VDMA_CMPLT_CXF */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_CMPLT_CXF_BIT_MUSK);
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_CMPLT_F0_BIT_MUSK) {
        /* VDMA_CMPLT_F0  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_CMPLT_F0_BIT_MUSK);
        if (usb_hs_device.in_ep[fifo_ep_map[0]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[0] | 0x80));
        } else if (usb_hs_device.out_ep[fifo_ep_map[0]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[0] & 0x7f));
        }
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_CMPLT_F1_BIT_MUSK) {
        /* VDMA_CMPLT_F1  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_CMPLT_F1_BIT_MUSK);
        if (usb_hs_device.in_ep[fifo_ep_map[1]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[1] | 0x80));
        } else if (usb_hs_device.out_ep[fifo_ep_map[1]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[1] & 0x7f));
        }
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_CMPLT_F2_BIT_MUSK) {
        /* VDMA_CMPLT_F2  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_CMPLT_F2_BIT_MUSK);
        if (usb_hs_device.in_ep[fifo_ep_map[2]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[2] | 0x80));
        } else if (usb_hs_device.out_ep[fifo_ep_map[2]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[2] & 0x7f));
        }
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_CMPLT_F3_BIT_MUSK) {
        /* VDMA_CMPLT_F3  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_CMPLT_F3_BIT_MUSK);
        if (usb_hs_device.in_ep[fifo_ep_map[3]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_IN_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[3] | 0x80));
        } else if (usb_hs_device.out_ep[fifo_ep_map[3]].ep_ena) {
            usbd_event_notify_handler(USB_DC_EVENT_EP_OUT_NOTIFY, (void *)(uintptr_t)(fifo_ep_map[3] & 0x7f));
        }
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_ERROR_CXF_BIT_MUSK) {
        /* VDMA_ERROR_CXF */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_ERROR_CXF_BIT_MUSK);
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_ERROR_F0_BIT_MUSK) {
        /* VDMA_ERROR_F0  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_ERROR_F0_BIT_MUSK);
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_ERROR_F1_BIT_MUSK) {
        /* VDMA_ERROR_F1  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_ERROR_F1_BIT_MUSK);
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_ERROR_F2_BIT_MUSK) {
        /* VDMA_ERROR_F2  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_ERROR_F2_BIT_MUSK);
    }

    if (group3intstatus & USB_SUB_GROUP_3_VDMA_ERROR_F3_BIT_MUSK) {
        /* VDMA_ERROR_F3  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_3_VDMA_ERROR_F3_BIT_MUSK);
    }
}
#endif
static void usb_group4_isr(void)
{
    uint32_t group4intstatus = USB_Get_Sub_Group_4_IntStatus() & ~USB_Get_Sub_Group_4_IntMask();

    if (group4intstatus & USB_SUB_GROUP_4_L1_BIT_MUSK) {
        /* L1_INT  */
        USB_Get_Sub_Group_3_IntClear(USB_SUB_GROUP_4_L1_BIT_MUSK);
        return;
    }
}

/**
 * @brief
 *
 */
void USBD_IRQHandler(void)
{
    if (USB_Global_IntStatus(USB_GLOBAL_INT_DEV)) {
        /* group 0 int */
        if (USB_Group_IntStatus(USB_GRP_INT_G0)) {
            usb_group0_isr();
        }
        /* group 1 int */
        if (USB_Group_IntStatus(USB_GRP_INT_G1)) {
            usb_group1_isr();
        }
        /* group 2 int */
        if (USB_Group_IntStatus(USB_GRP_INT_G2)) {
            usb_group2_isr();
        }
#ifdef CONFIG_USB_VDMA_ENABLE
        /* group 3 int */
        if (USB_Group_IntStatus(USB_GRP_INT_G3)) {
            usb_group3_isr();
        }
#endif
        /* group 4 int */
        if (USB_Group_IntStatus(USB_GRP_INT_G4)) {
            usb_group4_isr();
        }
    }
}

#ifdef USB_TEST_MODE
void usbd_set_feature(uint16_t index, uint16_t value)
{
    switch (value) {
        case 0: //USB_FEATURE_ENDPOINT_HALT
            //implement in usb_dc_ep_set_stall
            break;
        case 1: //USB_FEATURE_REMOTE_WAKEUP
        {
            uint32_t tmpVal;
            tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);
            tmpVal = BL_SET_REG_BIT(tmpVal, USB_CAP_RMWAKUP);
            BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);
        } break;
        case 2: //USB_FEATURE_TEST_MODE
            switch (index >> 8) {
                case 1: // Test_J
                {
                    uint32_t tmpVal;
                    tmpVal = BL_RD_REG(USB_BASE, USB_PHY_TST);
                    tmpVal = BL_SET_REG_BIT(tmpVal, USB_TST_JSTA);
                    BL_WR_REG(USB_BASE, USB_PHY_TST, tmpVal);
                } break;
                case 2: // Test_K
                {
                    uint32_t tmpVal;
                    tmpVal = BL_RD_REG(USB_BASE, USB_PHY_TST);
                    tmpVal = BL_SET_REG_BIT(tmpVal, USB_TST_KSTA);
                    BL_WR_REG(USB_BASE, USB_PHY_TST, tmpVal);
                } break;
                case 3: // TEST_SE0_NAK
                {
                    uint32_t tmpVal;
                    tmpVal = BL_RD_REG(USB_BASE, USB_PHY_TST);
                    tmpVal = BL_SET_REG_BIT(tmpVal, USB_TST_SE0NAK);
                    BL_WR_REG(USB_BASE, USB_PHY_TST, tmpVal);
                } break;
                case 4: // Test_Packet
                {
                    uint32_t tmpVal;
                    tmpVal = BL_RD_REG(USB_BASE, USB_PHY_TST);
                    tmpVal = BL_SET_REG_BIT(tmpVal, USB_TST_PKT);
                    BL_WR_REG(USB_BASE, USB_PHY_TST, tmpVal);
                } break;
                case 5: // Test_Force_Enable
                {
                    uint8_t temp[53];
                    uint8_t *pp;
                    uint8_t i;
                    pp = temp;

                    for (i = 0; i < 9; i++) /*JKJKJKJK x 9*/
                        *pp++ = 0x00;

                    for (i = 0; i < 8; i++) /* 8*AA */
                        *pp++ = 0xAA;

                    for (i = 0; i < 8; i++) /* 8*EE */
                        *pp++ = 0xEE;

                    *pp++ = 0xFE;

                    for (i = 0; i < 11; i++) /* 11*FF */
                        *pp++ = 0xFF;

                    *pp++ = 0x7F;
                    *pp++ = 0xBF;
                    *pp++ = 0xDF;
                    *pp++ = 0xEF;
                    *pp++ = 0xF7;
                    *pp++ = 0xFB;
                    *pp++ = 0xFD;
                    *pp++ = 0xFC;
                    *pp++ = 0x7E;
                    *pp++ = 0xBF;
                    *pp++ = 0xDF;
                    *pp++ = 0xEF;
                    *pp++ = 0xF7;
                    *pp++ = 0xFB;
                    *pp++ = 0xFD;
                    *pp++ = 0x7E;

                    uint32_t tmpVal;
                    tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CXCFE);
                    tmpVal = BL_SET_REG_BIT(tmpVal, USB_TST_PKDONE);
                    BL_WR_REG(USB_BASE, USB_DEV_CXCFE, tmpVal);

                } break;

                default:
                    break;
            }
            break;
        case 3: //USB_FEATURE_BHNPENABLE
        {
            uint32_t tmpVal;
            tmpVal = BL_RD_REG(USB_BASE, USB_OTG_CSR);
            tmpVal = BL_SET_REG_BIT(tmpVal, USB_B_BUS_REQ);
            BL_WR_REG(USB_BASE, USB_OTG_CSR, tmpVal);

            tmpVal = BL_RD_REG(USB_BASE, USB_OTG_CSR);
            tmpVal = BL_SET_REG_BIT(tmpVal, USB_B_HNP_EN);
            BL_WR_REG(USB_BASE, USB_OTG_CSR, tmpVal);
        } break;
        case 4: //USB_FEATURE_AHNPSUPPORT

            break;
        case 5: //USB_FEATURE_AALTHNPSUPPORT

            break;

        default:
            break;
    }
}

void usbd_clear_feature(uint16_t index, uint16_t value)
{
    switch (value) {
        case 0: //USB_FEATURE_ENDPOINT_HALT
            //implement in usb_dc_ep_clear_stall
            break;
        case 1: //USB_FEATURE_REMOTE_WAKEUP
        {
            uint32_t tmpVal;
            tmpVal = BL_RD_REG(USB_BASE, USB_DEV_CTL);
            tmpVal = BL_CLR_REG_BIT(tmpVal, USB_CAP_RMWAKUP);
            BL_WR_REG(USB_BASE, USB_DEV_CTL, tmpVal);
        } break;

        default:
            break;
    }
}
#endif
