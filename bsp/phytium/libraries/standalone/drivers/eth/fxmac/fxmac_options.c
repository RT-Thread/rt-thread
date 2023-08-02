/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fxmac_options.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for options functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 * 1.1  liuzhihong  2023/4/11     jumbo support
 */

#include "fxmac_hw.h"
#include "fxmac.h"
#include "fassert.h"
#include "ftypes.h"


/**
 * @name: FXmacSetMacAddress
 *
 * @msg: Set the MAC address for this driver/device.  The address is a 48-bit value.
 * The device must be stopped before calling this function.
 *
 * @param {FXmac *}: instance_p is a pointer to the instance to be worked on.
 * @param address_ptr is a pointer to a 6-byte MAC address.
 * @param index plus 1 is a index to which MAC (1-4) address.
 *
 * @return
 * - FT_SUCCESS if the MAC address was set successfully
 * - FXMAC_ERR_MAC_IS_PROCESSING if the device has not yet been stopped
 *
 */
FError FXmacSetMacAddress(FXmac *instance_p, u8 *address_ptr, u8 index)
{
    u32 mac_addr;
    u8 *aptr = (u8 *)(void *)address_ptr;
    u8 index_loc = index;
    FError status;
    FASSERT(instance_p != NULL);
    FASSERT(aptr != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);
    FASSERT((index_loc < (u8)FXMAC_MAX_MAC_ADDR));

    /* Be sure device has been stopped */
    if (instance_p->is_started == (u32)FT_COMPONENT_IS_STARTED)
    {
        status = (FError)(FXMAC_ERR_MAC_IS_PROCESSING);
    }
    else
    {
        /* Set the MAC bits [31:0] in BOT */
        mac_addr = *(aptr);
        mac_addr |= ((u32)(*(aptr + 1)) << 8U);
        mac_addr |= ((u32)(*(aptr + 2)) << 16U);
        mac_addr |= ((u32)(*(aptr + 3)) << 24U);
        FXMAC_WRITEREG32(instance_p->config.base_address,
                         ((u32)FXMAC_GEM_SA1B + ((u32)index_loc * (u32)8)), mac_addr);

        /* There are reserved bits in TOP so don't affect them */
        mac_addr = FXMAC_READREG32(instance_p->config.base_address,
                                   ((u32)FXMAC_GEM_SA1T + ((u32)index_loc * (u32)8)));

        mac_addr &= (u32)(~FXMAC_GEM_SAB_MASK);

        /* Set MAC bits [47:32] in TOP */
        mac_addr |= (u32)(*(aptr + 4));
        mac_addr |= (u32)(*(aptr + 5)) << 8U;

        FXMAC_WRITEREG32(instance_p->config.base_address,
                         ((u32)FXMAC_GEM_SA1T + ((u32)index_loc * (u32)8)), mac_addr);

        status = (FError)(FT_SUCCESS);
    }
    return status;
}

/**
 * @name: FXmacGetMacAddress
 * @msg:  Set the MAC address according to index
 * @param {FXmac} *mac is a pointer to the instance to be worked on.
 * @param {void} *address_ptr is an output parameter, and is a pointer to a buffer into
 *        which the current MAC address will be copied.
 * @param {u8} index is a index to which MAC (0-3) address.
 */
void FXmacGetMacAddress(FXmac *instance_p, u8 *address_ptr, u8 index)
{
    u32 reg_value;
    u8 *ptr = (u8 *)address_ptr;
    FASSERT(instance_p != NULL);
    FASSERT(ptr != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT((index < FXMAC_MAX_MAC_ADDR));

    reg_value = FXMAC_READREG32(instance_p->config.base_address, FXMAC_GEM_SA1B + ((u32)index * (u32)8));
    *ptr = (u8)reg_value;
    *(ptr + 1) = (u8)(reg_value >> 8U);
    *(ptr + 2) = (u8)(reg_value >> 16U);
    *(ptr + 3) = (u8)(reg_value >> 24U);

    reg_value = FXMAC_READREG32(instance_p->config.base_address, FXMAC_GEM_SA1T + ((u32)index * (u32)8));
    *(ptr + 4) = (u8)(reg_value);
    *(ptr + 5) = (u8)(reg_value >> 8U);
}


/**
 * Set the Type ID match for this driver/device.  The register is a 32-bit
 * value. The device must be stopped before calling this function.
 *
 * @param instance_p is a pointer to the instance to be worked on.
 * @param id_check is type ID to be configured.
 * @param index plus 1 is a index to which Type ID (1-4).
 *
 * @return
 * - FT_SUCCESS if the MAC address was set successfully
 * - FXMAC_ERR_MAC_IS_PROCESSING if the device has not yet been stopped
 *
 */
FError FXmacSetTypeIdCheck(FXmac *instance_p, u32 id_check, u8 index)
{
    u8 index_loc = index;
    FError status;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT((index_loc < (u8)FXMAC_MAX_TYPE_ID));

    /* Be sure device has been stopped */
    if (instance_p->is_started == (u32)FT_COMPONENT_IS_STARTED)
    {
        status = (FError)(FXMAC_ERR_MAC_IS_PROCESSING);
    }
    else
    {

        /* Set the ID bits in MATCHx register */
        FXMAC_WRITEREG32(instance_p->config.base_address,
                         ((u32)FXMAC_MATCH1_OFFSET + ((u32)index_loc * (u32)4)), id_check);

        status = (FError)(FT_SUCCESS);
    }
    return status;
}


/**
 * Set options for the driver/device. The driver should be stopped with
 * FXmacStop() before changing options.
 *
 * @param instance_p is a pointer to the instance to be worked on.
 * @param options are the options to set. Multiple options can be set by OR'ing
 *        FXMAC_*_OPTIONS constants together. options not specified are not
 *        affected.
 * @param queue_num is the Buffer Queue Index ,Used for jumbo frames only
 *
 * @return
 * - FT_SUCCESS if the options were set successfully
 * - FXMAC_ERR_MAC_IS_PROCESSING if the device has not yet been stopped
 *
 * @note
 * See fxmac.h for a description of the available options.
 *
 */
FError FXmacSetOptions(FXmac *instance_p, u32 options, u32 queue_num)
{
    u32 reg;            /* Generic register contents */
    u32 reg_netcfg;     /* Reflects original contents of NET_CONFIG */
    u32 reg_new_netcfg; /* Reflects new contents of NET_CONFIG */
    FError status;
    FXmacConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);
    config_p = &instance_p->config;
    /* Be sure device has been stopped */
    if (instance_p->is_started == (u32)FT_COMPONENT_IS_STARTED)
    {
        status = (FError)(FXMAC_ERR_MAC_IS_PROCESSING);
    }
    else
    {

        /* Many of these options will change the NET_CONFIG registers.
         * To reduce the amount of IO to the device, group these options here
         * and change them all at once.
         */

        /* Grab current register contents */
        reg_netcfg = FXMAC_READREG32(config_p->base_address,
                                     FXMAC_NWCFG_OFFSET);
        reg_new_netcfg = reg_netcfg;

        /*
         * It is configured to max 1536.
         */
        if ((options & FXMAC_FRAME1536_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= (FXMAC_NWCFG_1536RXEN_MASK);
        }

        /* Turn on VLAN packet only, only VLAN tagged will be accepted */
        if ((options & FXMAC_VLAN_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= FXMAC_NWCFG_NVLANDISC_MASK;
        }

        /* Turn on FCS stripping on receive packets */
        if ((options & FXMAC_FCS_STRIP_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= FXMAC_NWCFG_FCS_REMOVE_MASK;
        }

        /* Turn on length/type field checking on receive packets */
        if ((options & FXMAC_LENTYPE_ERR_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= FXMAC_NWCFG_LENGTH_FIELD_ERROR_FRAME_DISCARD_MASK;
        }

        /* Turn on flow control */
        if ((options & FXMAC_FLOW_CONTROL_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= FXMAC_NWCFG_PAUSE_ENABLE_MASK;
        }

        /* Turn on promiscuous frame filtering (all frames are received) */
        if ((options & FXMAC_PROMISC_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= FXMAC_NWCFG_COPYALLEN_MASK;
        }

        /* Allow broadcast address reception */
        if ((options & FXMAC_BROADCAST_OPTION) != 0x00000000U)
        {
            reg_new_netcfg &= (u32)(~FXMAC_NWCFG_BCASTDI_MASK);
        }

        /* Allow multicast address filtering */
        if ((options & FXMAC_MULTICAST_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= FXMAC_NWCFG_MCASTHASHEN_MASK;
        }

        /* enable RX checksum offload */
        if ((options & FXMAC_RX_CHKSUM_ENABLE_OPTION) != 0x00000000U)
        {
            reg_new_netcfg |= FXMAC_NWCFG_RXCHKSUMEN_MASK;
        }

        /* Enable jumbo frames */
        if ((options & FXMAC_JUMBO_ENABLE_OPTION) != 0x00000000U)
        {
            instance_p->max_mtu_size = FXMAC_MTU_JUMBO;
            instance_p->max_frame_size = FXMAC_MAX_FRAME_SIZE_JUMBO;

            reg_new_netcfg |= FXMAC_NWCFG_JUMBO_MASK;
            FXMAC_WRITEREG32(config_p->base_address,
                             FXMAC_JUMBOMAXLEN_OFFSET, FXMAC_MAX_FRAME_SIZE_JUMBO);
            FXMAC_WRITEREG32(config_p->base_address,
                            FXMAC_TXQSEGALLOC_QLOWER_OFFSET,FXMAC_TXQSEGALLOC_QLOWER_MASK);
            if (queue_num == 0)
            {
                u32 rx_buf_size = 0;
                reg = FXMAC_READREG32(config_p->base_address,
                                      FXMAC_DMACR_OFFSET);
                reg &= ~FXMAC_DMACR_RXBUF_MASK;

                rx_buf_size = ((u32)instance_p->max_frame_size / (u32)FXMAC_RX_BUF_UNIT);
                rx_buf_size += (((u32)instance_p->max_frame_size % (u32)FXMAC_RX_BUF_UNIT) != (u32)0) ? 1U : 0U;

                reg |= ((rx_buf_size << (u32)(FXMAC_DMACR_RXBUF_SHIFT)) &
                        (u32)(FXMAC_DMACR_RXBUF_MASK));
                FXMAC_WRITEREG32(config_p->base_address,
                                 FXMAC_DMACR_OFFSET, reg);
            }
            else if (queue_num < instance_p->config.max_queue_num)
            {
                u32 rx_buf_size = 0;
                rx_buf_size = ((u32)instance_p->max_frame_size / (u32)FXMAC_RX_BUF_UNIT);
                rx_buf_size += (((u32)instance_p->max_frame_size % (u32)FXMAC_RX_BUF_UNIT) != (u32)0) ? 1U : 0U;

                FXMAC_WRITEREG32(config_p->base_address, FXMAC_RXBUFQX_SIZE_OFFSET(queue_num), rx_buf_size & FXMAC_RXBUFQX_SIZE_MASK);
            }
        }

        if (((options & FXMAC_SGMII_ENABLE_OPTION) != 0x00000000U))
        {
            reg_new_netcfg |= (FXMAC_NWCFG_SGMII_MODE_ENABLE_MASK |
                               FXMAC_NWCFG_PCSSEL_MASK);
        }

        if ((options & FXMAC_LOOPBACK_NO_MII_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
            reg |= FXMAC_NWCTRL_LOOPBACK_LOCAL_MASK;
            FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, reg);
        }

        if ((options & FXMAC_LOOPBACK_USXGMII_OPTION) != 0x00000000U)
        {
            FXMAC_WRITEREG32(config_p->base_address, FXMAC_TEST_CONTROL_OFFSET, 2);
        }

        /* Officially change the NET_CONFIG registers if it needs to be
         * modified.
         */
        if (reg_netcfg != reg_new_netcfg)
        {
            FXMAC_WRITEREG32(config_p->base_address,
                             FXMAC_NWCFG_OFFSET, reg_new_netcfg);
        }

        /* Enable TX checksum offload */
        if ((options & FXMAC_TX_CHKSUM_ENABLE_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(config_p->base_address,
                                  FXMAC_DMACR_OFFSET);
            reg |= FXMAC_DMACR_TCPCKSUM_MASK;
            FXMAC_WRITEREG32(config_p->base_address,
                             FXMAC_DMACR_OFFSET, reg);
        }

        /* Enable transmitter */
        if ((options & FXMAC_TRANSMITTER_ENABLE_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(config_p->base_address,
                                  FXMAC_NWCTRL_OFFSET);
            reg |= FXMAC_NWCTRL_TXEN_MASK;
            FXMAC_WRITEREG32(config_p->base_address,
                             FXMAC_NWCTRL_OFFSET, reg);
        }

        /* Enable receiver */
        if ((options & FXMAC_RECEIVER_ENABLE_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(config_p->base_address,
                                  FXMAC_NWCTRL_OFFSET);
            reg |= FXMAC_NWCTRL_RXEN_MASK;
            FXMAC_WRITEREG32(config_p->base_address,
                             FXMAC_NWCTRL_OFFSET, reg);
        }

        /* The remaining options not handled here are managed elsewhere in the
         * driver. No register modifications are needed at this time. Reflecting
         * the option in instance_p->options is good enough for now.
         */

        /* Set options word to its new value */
        instance_p->options |= options;

        status = (FError)(FT_SUCCESS);
    }
    return status;
}


/**
 * Clear options for the driver/device
 *
 * @param instance_p is a pointer to the instance to be worked on.
 * @param options are the options to clear. Multiple options can be cleared by
 *        OR'ing FXMAC_*_options constants together. options not specified
 *        are not affected.
 * @param queue_num is the Buffer Queue Index ,Used for jumbo frames only
 * @return
 * - FT_SUCCESS if the options were set successfully
 * - FXMAC_ERR_MAC_IS_PROCESSING if the device has not yet been stopped
 *
 * @note
 * See fxmac.h for a description of the available options.
 */
FError FXmacClearOptions(FXmac *instance_p, u32 options, u32 queue_num)
{
    u32 reg;             /* Generic */
    u32 reg_net_cfg;     /* Reflects original contents of NET_CONFIG */
    u32 reg_new_net_cfg; /* Reflects new contents of NET_CONFIG */
    FError status;
    FXmacConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);
    config_p = &instance_p->config;
    /* Be sure device has been stopped */
    if (instance_p->is_started == (u32)FT_COMPONENT_IS_STARTED)
    {
        status = (FError)(FXMAC_ERR_MAC_IS_PROCESSING);
    }
    else
    {
        /* Many of these options will change the NET_CONFIG registers.
         * To reduce the amount of IO to the device, group these options here
         * and change them all at once.
         */
        /* Grab current register contents */
        reg_net_cfg = FXMAC_READREG32(instance_p->config.base_address,
                                      FXMAC_NWCFG_OFFSET);
        reg_new_net_cfg = reg_net_cfg;
        /* There is only RX configuration!?
         * It is configured in two different length, up to 1536 and 10240 bytes
         */
        if ((options & FXMAC_FRAME1536_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_1536RXEN_MASK);
        }

        /* Turn off VLAN packet only */
        if ((options & FXMAC_VLAN_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_NVLANDISC_MASK);
        }

        /* Turn off FCS stripping on receive packets */
        if ((options & FXMAC_FCS_STRIP_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_FCS_REMOVE_MASK);
        }

        /* Turn off length/type field checking on receive packets */
        if ((options & FXMAC_LENTYPE_ERR_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_LENGTH_FIELD_ERROR_FRAME_DISCARD_MASK);
        }

        /* Turn off flow control */
        if ((options & FXMAC_FLOW_CONTROL_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_PAUSE_ENABLE_MASK);
        }

        /* Turn off promiscuous frame filtering (all frames are received) */
        if ((options & FXMAC_PROMISC_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_COPYALLEN_MASK);
        }

        /* Disallow broadcast address filtering => broadcast reception */
        if ((options & FXMAC_BROADCAST_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg |= FXMAC_NWCFG_BCASTDI_MASK;
        }

        /* Disallow multicast address filtering */
        if ((options & FXMAC_MULTICAST_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_MCASTHASHEN_MASK);
        }

        /* Disable RX checksum offload */
        if ((options & FXMAC_RX_CHKSUM_ENABLE_OPTION) != 0x00000000U)
        {
            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_RXCHKSUMEN_MASK);
        }

        /* Disable jumbo frames */
        if (((options & FXMAC_JUMBO_ENABLE_OPTION) != 0x00000000U)) /* 恢复之前buffer 容量 */
        {

            instance_p->max_mtu_size = FXMAC_MTU;
            instance_p->max_frame_size = FXMAC_MAX_FRAME_SIZE;

            reg_new_net_cfg &= (u32)(~FXMAC_NWCFG_JUMBO_MASK);
            reg = FXMAC_READREG32(instance_p->config.base_address,
                                  FXMAC_DMACR_OFFSET);
            reg &= ~FXMAC_DMACR_RXBUF_MASK;
            FXMAC_WRITEREG32(config_p->base_address,
                            FXMAC_TXQSEGALLOC_QLOWER_OFFSET,FXMAC_TXQSEGALLOC_QLOWER_CLEAN_MASK);

            if (queue_num == 0)
            {
                u32 rx_buf_size = 0;

                reg = FXMAC_READREG32(instance_p->config.base_address, FXMAC_DMACR_OFFSET);
                reg &= ~FXMAC_DMACR_RXBUF_MASK;

                rx_buf_size = ((u32)instance_p->max_frame_size / (u32)FXMAC_RX_BUF_UNIT);
                rx_buf_size += ((u32)instance_p->max_frame_size % ((u32)FXMAC_RX_BUF_UNIT) != (u32)0) ? 1U : 0U;

                reg |= ((rx_buf_size << (u32)(FXMAC_DMACR_RXBUF_SHIFT)) & (u32)(FXMAC_DMACR_RXBUF_MASK));

                FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_DMACR_OFFSET, reg);
            }
            else if (queue_num < instance_p->config.max_queue_num)
            {
                u32 rx_buf_size = 0;
                rx_buf_size = ((u32)instance_p->max_frame_size / (u32)FXMAC_RX_BUF_UNIT);
                rx_buf_size += (((u32)instance_p->max_frame_size % (u32)FXMAC_RX_BUF_UNIT) != (u32)0) ? 1U : 0U;

                FXMAC_WRITEREG32(config_p->base_address, FXMAC_RXBUFQX_SIZE_OFFSET(queue_num), rx_buf_size & FXMAC_RXBUFQX_SIZE_MASK);
            }
        }

        if (((options & FXMAC_SGMII_ENABLE_OPTION) != 0x00000000U))
        {
            reg_new_net_cfg &= (u32)(~(FXMAC_NWCFG_SGMII_MODE_ENABLE_MASK |
                                       FXMAC_NWCFG_PCSSEL_MASK));
        }

        if ((options & FXMAC_LOOPBACK_NO_MII_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
            reg &= (u32)(~FXMAC_NWCTRL_LOOPBACK_LOCAL_MASK);
            FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, reg);
        }

        if ((options & FXMAC_LOOPBACK_USXGMII_OPTION) != 0x00000000U)
        {
            FXMAC_WRITEREG32(config_p->base_address, FXMAC_TEST_CONTROL_OFFSET, (FXMAC_READREG32(config_p->base_address, FXMAC_TEST_CONTROL_OFFSET) & ~2));
        }

        /* Officially change the NET_CONFIG registers if it needs to be
         * modified.
         */
        if (reg_net_cfg != reg_new_net_cfg)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_NWCFG_OFFSET, reg_new_net_cfg);
        }

        /* Disable TX checksum offload */
        if ((options & FXMAC_TX_CHKSUM_ENABLE_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(instance_p->config.base_address,
                                  FXMAC_DMACR_OFFSET);
            reg &= (u32)(~FXMAC_DMACR_TCPCKSUM_MASK);
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_DMACR_OFFSET, reg);
        }

        /* Disable transmitter */
        if ((options & FXMAC_TRANSMITTER_ENABLE_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(instance_p->config.base_address,
                                  FXMAC_NWCTRL_OFFSET);
            reg &= (u32)(~FXMAC_NWCTRL_TXEN_MASK);
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_NWCTRL_OFFSET, reg);
        }

        /* Disable receiver */
        if ((options & FXMAC_RECEIVER_ENABLE_OPTION) != 0x00000000U)
        {
            reg = FXMAC_READREG32(instance_p->config.base_address,
                                  FXMAC_NWCTRL_OFFSET);
            reg &= (u32)(~FXMAC_NWCTRL_RXEN_MASK);
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_NWCTRL_OFFSET, reg);
        }

        /* The remaining options not handled here are managed elsewhere in the
         * driver. No register modifications are needed at this time. Reflecting
         * option in instance_p->options is good enough for now.
         */

        /* Set options word to its new value */
        instance_p->options &= ~options;

        status = (FError)(FT_SUCCESS);
    }
    return status;
}


/**
 * Clear the Hash registers for the mac address pointed by address_ptr.
 *
 * @param instance_p is a pointer to the instance to be worked on.
 *
 */
void FXmacClearHash(FXmac *instance_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);

    FXMAC_WRITEREG32(instance_p->config.base_address,
                     FXMAC_HASHL_OFFSET, 0x0U);

    /* write bits [63:32] in TOP */
    FXMAC_WRITEREG32(instance_p->config.base_address,
                     FXMAC_HASHH_OFFSET, 0x0U);
}


/**
 * Write data to the specified PHY register. The Ethernet driver does not
 * require the device to be stopped before writing to the PHY.  Although it is
 * probably a good idea to stop the device, it is the responsibility of the
 * application to deem this necessary. The MAC provides the driver with the
 * ability to talk to a PHY that adheres to the Media Independent Interface
 * (MII) as defined in the IEEE 802.3 standard.
 *
 * Prior to PHY access with this function, the user should have setup the MDIO
 * clock with FXmacSetMdioDivisor().
 *
 * @param instance_p is a pointer to the FXmac instance to be worked on.
 * @param phy_address is the address of the PHY to be written (supports multiple
 *        PHYs)
 * @param register_num is the register number, 0-31, of the specific PHY register
 *        to write
 * @param phy_data is the 16-bit value that will be written to the register
 *
 * @return
 *
 * - FT_SUCCESS if the PHY was written to successfully. Since there is no error
 *   status from the MAC on a write, the user should read the PHY to verify the
 *   write was successful.
 * - FXMAC_ERR_PHY_BUSY if there is another PHY operation in progress
 *
 * @note
 *
 * This function is not thread-safe. The user must provide mutually exclusive
 * access to this function if there are to be multiple threads that can call it.
 *
 * There is the possibility that this function will not return if the hardware
 * is broken (i.e., it never sets the status bit indicating that the write is
 * done). If this is of concern to the user, the user should provide a mechanism
 * suitable to their needs for recovery.
 *
 * For the duration of this function, all host interface reads and writes are
 * blocked to the current FXmac instance.
 *
 ******************************************************************************/
FError FXmacPhyWrite(FXmac *instance_p, u32 phy_address,
                     u32 register_num, u16 phy_data)
{
    u32 mgtcr;
    volatile u32 ipisr;
    u32 ip_write_temp;
    FError status;

    FASSERT(instance_p != NULL);

    /* Make sure no other PHY operation is currently in progress */
    if ((!(FXMAC_READREG32(instance_p->config.base_address,
                           FXMAC_NWSR_OFFSET) &
           FXMAC_NWSR_MDIOIDLE_MASK)) == TRUE)
    {
        status = (FError)(FXMAC_ERR_PHY_BUSY);
    }
    else
    {
        /* Construct mgtcr mask for the operation */
        mgtcr = FXMAC_PHYMNTNC_OP_MASK | FXMAC_PHYMNTNC_OP_W_MASK |
                (phy_address << FXMAC_PHYMNTNC_PHAD_SHFT_MSK) |
                (register_num << FXMAC_PHYMNTNC_PREG_SHFT_MSK) | (u32)phy_data;

        /* Write mgtcr and wait for completion */
        FXMAC_WRITEREG32(instance_p->config.base_address,
                         FXMAC_PHYMNTNC_OFFSET, mgtcr);

        do
        {
            ipisr = FXMAC_READREG32(instance_p->config.base_address,
                                    FXMAC_NWSR_OFFSET);
            ip_write_temp = ipisr;
        }
        while ((ip_write_temp & FXMAC_NWSR_MDIOIDLE_MASK) == 0x00000000U);

        status = (FError)(FT_SUCCESS);
    }
    return status;
}


/**
 * Read the current value of the PHY register indicated by the phy_address and
 * the register_num parameters. The MAC provides the driver with the ability to
 * talk to a PHY that adheres to the Media Independent Interface (MII) as
 * defined in the IEEE 802.3 standard.
 *
 *
 * @param instance_p is a pointer to the FXmac instance to be worked on.
 * @param phy_address is the address of the PHY to be read (supports multiple
 *        PHYs)
 * @param register_num is the register number, 0-31, of the specific PHY register
 *        to read
 * @param phydat_aptr is an output parameter, and points to a 16-bit buffer into
 *        which the current value of the register will be copied.
 *
 * @return
 *
 * - FT_SUCCESS if the PHY was read from successfully
 * - FXMAC_ERR_PHY_BUSY if there is another PHY operation in progress
 *
 * @note
 *
 * This function is not thread-safe. The user must provide mutually exclusive
 * access to this function if there are to be multiple threads that can call it.
 *
 * There is the possibility that this function will not return if the hardware
 * is broken (i.e., it never sets the status bit indicating that the read is
 * done). If this is of concern to the user, the user should provide a mechanism
 * suitable to their needs for recovery.
 *
 * For the duration of this function, all host interface reads and writes are
 * blocked to the current FXmac instance.
 *
 ******************************************************************************/
FError FXmacPhyRead(FXmac *instance_p, u32 phy_address,
                    u32 register_num, u16 *phydat_aptr)
{
    u32 mgtcr;
    volatile u32 ipisr;
    u32 IpReadTemp;
    FError status;

    FASSERT(instance_p != NULL);

    /* Make sure no other PHY operation is currently in progress */
    if ((!(FXMAC_READREG32(instance_p->config.base_address,
                           FXMAC_NWSR_OFFSET) &
           FXMAC_NWSR_MDIOIDLE_MASK)) == TRUE)
    {
        status = (FError)(FXMAC_ERR_PHY_BUSY);
    }
    else
    {
        /* Construct mgtcr mask for the operation */
        mgtcr = FXMAC_PHYMNTNC_OP_MASK | FXMAC_PHYMNTNC_OP_R_MASK |
                (phy_address << FXMAC_PHYMNTNC_PHAD_SHFT_MSK) |
                (register_num << FXMAC_PHYMNTNC_PREG_SHFT_MSK);

        /* Write mgtcr and wait for completion */
        FXMAC_WRITEREG32(instance_p->config.base_address,
                         FXMAC_PHYMNTNC_OFFSET, mgtcr);

        do
        {
            ipisr = FXMAC_READREG32(instance_p->config.base_address,
                                    FXMAC_NWSR_OFFSET);
            IpReadTemp = ipisr;
        }
        while ((IpReadTemp & FXMAC_NWSR_MDIOIDLE_MASK) == 0x00000000U);

        /* Read data */
        *phydat_aptr = (u16)FXMAC_READREG32(instance_p->config.base_address,
                                            FXMAC_PHYMNTNC_OFFSET);
        status = (FError)(FT_SUCCESS);
    }
    return status;
}

boolean FXmacUsxLinkStatus(FXmac *instance_p)
{
    u32 reg = 0;
    FASSERT(instance_p != NULL);

    reg = FXMAC_READREG32(instance_p->config.base_address, FXMAC_GEM_USX_STATUS_OFFSET);
    if (reg & FXMAC_GEM_USX_STATUS_BLOCK_LOCK)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
