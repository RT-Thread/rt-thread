/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
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
 * FilePath: fxmac_debug.c
 * Date: 2023-01-04 15:33:03
 * LastEditTime: 2023-01-04 15:33:04
 * Description:  This file is for user to debug xmac information.
 * 
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#include "fxmac_hw.h"
#include "fxmac.h"
#include "fio.h"
#include "fdebug.h"

#define FXMAC_DEBUG_TAG "FXMAC_DEBUG"
#define FXMAC_ERROR(format, ...) FT_DEBUG_PRINT_E(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_INFO(format, ...) FT_DEBUG_PRINT_I(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_DEBUG(format, ...) FT_DEBUG_PRINT_D(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_WARN(format, ...) FT_DEBUG_PRINT_W(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)


void FXmacDebugTxPrint(FXmac *instance_p)
{
    FXmacConfig *config_p;
    config_p = &instance_p->config;

    FXMAC_INFO("octets_txed_bottom is 0x%x",FtIn32(config_p->base_address+FXMAC_OCTTXL_OFFSET));
    FXMAC_INFO("octets_txed_top is 0x%x",FtIn32(config_p->base_address+FXMAC_OCTTXH_OFFSET));
    FXMAC_INFO("frames_txed_ok is 0x%x",FtIn32(config_p->base_address+FXMAC_TXCNT_OFFSET));
    FXMAC_INFO("broadcast_txed is 0x%x",FtIn32(config_p->base_address+FXMAC_TXBCCNT_OFFSET));
    FXMAC_INFO("multicast_txed is 0x%x",FtIn32(config_p->base_address+FXMAC_TXMCCNT_OFFSET));
    FXMAC_INFO("pause_frames_txed is 0x%x",FtIn32(config_p->base_address+FXMAC_TXPAUSECNT_OFFSET));
    FXMAC_INFO("frames_txed_64 is 0x%x",FtIn32(config_p->base_address+FXMAC_TX64CNT_OFFSET));
    FXMAC_INFO("frames_txed_65 is 0x%x",FtIn32(config_p->base_address+FXMAC_TX65CNT_OFFSET));
    FXMAC_INFO("frames_txed_128 is 0x%x",FtIn32(config_p->base_address+FXMAC_TX128CNT_OFFSET));
    FXMAC_INFO("frames_txed_256 is 0x%x",FtIn32(config_p->base_address+FXMAC_TX256CNT_OFFSET));
    FXMAC_INFO("frames_txed_512 is 0x%x",FtIn32(config_p->base_address+FXMAC_TX512CNT_OFFSET));
    FXMAC_INFO("frames_txed_1024 is 0x%x",FtIn32(config_p->base_address+FXMAC_TX1024CNT_OFFSET));
    FXMAC_INFO("frames_txed_1519 is 0x%x",FtIn32(config_p->base_address+FXMAC_TX1519CNT_OFFSET));
    FXMAC_INFO("tx_underruns is 0x%x",FtIn32(config_p->base_address+FXMAC_TXURUNCNT_OFFSET));
    FXMAC_INFO("single_collisions is 0x%x",FtIn32(config_p->base_address+FXMAC_SNGLCOLLCNT_OFFSET));
    FXMAC_INFO("multiple_collisions is 0x%x",FtIn32(config_p->base_address+FXMAC_MULTICOLLCNT_OFFSET));
    FXMAC_INFO("excessive_collisions is 0x%x",FtIn32(config_p->base_address+FXMAC_EXCESSCOLLCNT_OFFSET));
    FXMAC_INFO("late_collisions is 0x%x",FtIn32(config_p->base_address+FXMAC_LATECOLLCNT_OFFSET));
    FXMAC_INFO("deferred_frames is 0x%x",FtIn32(config_p->base_address+FXMAC_TXDEFERCNT_OFFSET));
    FXMAC_INFO("crs_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_TXCSENSECNT_OFFSET));
}


void FXmacDebugRxPrint(FXmac *instance_p)
{
    FXmacConfig *config_p;
    config_p = &instance_p->config;

    FXMAC_INFO("octets_rxed_bottom is 0x%x",FtIn32(config_p->base_address+FXMAC_OCTRXL_OFFSET));
    FXMAC_INFO("octets_rxed_top is 0x%x",FtIn32(config_p->base_address+FXMAC_OCTRXH_OFFSET));
    FXMAC_INFO("frames_rxed_ok is 0x%x",FtIn32(config_p->base_address+FXMAC_RXCNT_OFFSET));
    FXMAC_INFO("broadcast_rxed is 0x%x",FtIn32(config_p->base_address+FXMAC_RXBROADCNT_OFFSET));
    FXMAC_INFO("multicast_Rxed is 0x%x",FtIn32(config_p->base_address+FXMAC_RXMULTICNT_OFFSET));
    FXMAC_INFO("pause_frames_rxed is 0x%x",FtIn32(config_p->base_address+FXMAC_RXPAUSECNT_OFFSET));
    FXMAC_INFO("frames_rxed_64 is 0x%x",FtIn32(config_p->base_address+FXMAC_RX64CNT_OFFSET));
    FXMAC_INFO("frames_rxed_65 is 0x%x",FtIn32(config_p->base_address+FXMAC_RX65CNT_OFFSET));
    FXMAC_INFO("frames_rxed_128 is 0x%x",FtIn32(config_p->base_address+FXMAC_RX128CNT_OFFSET));
    FXMAC_INFO("frames_rxed_256 is 0x%x",FtIn32(config_p->base_address+FXMAC_RX256CNT_OFFSET));
    FXMAC_INFO("frames_rxed_512 is 0x%x",FtIn32(config_p->base_address+FXMAC_RX512CNT_OFFSET));
    FXMAC_INFO("frames_rxed_1024 is 0x%x",FtIn32(config_p->base_address+FXMAC_RX1024CNT_OFFSET));
    FXMAC_INFO("frames_rxed_1519 is 0x%x",FtIn32(config_p->base_address+FXMAC_RX1519CNT_OFFSET));
    FXMAC_INFO("undersize_frames is 0x%x",FtIn32(config_p->base_address+FXMAC_RXUNDRCNT_OFFSET));
    FXMAC_INFO("excessive_rx_length is 0x%x",FtIn32(config_p->base_address+FXMAC_RXOVRCNT_OFFSET));
    FXMAC_INFO("rx_jabbers is 0x%x",FtIn32(config_p->base_address+FXMAC_RXJABCNT_OFFSET));
    FXMAC_INFO("fcs_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXFCSCNT_OFFSET));
    FXMAC_INFO("rx_length_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXLENGTHCNT_OFFSET));
    FXMAC_INFO("rx_symbol_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXSYMBCNT_OFFSET));
    FXMAC_INFO("alignment_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXALIGNCNT_OFFSET));
    FXMAC_INFO("rx_resource_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXRESERRCNT_OFFSET));
    FXMAC_INFO("rx_overruns is 0x%x",FtIn32(config_p->base_address+FXMAC_RXORCNT_OFFSET));
    FXMAC_INFO("rx_ip_ck_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXIPCCNT_OFFSET));
    FXMAC_INFO("rx_tcp_ck_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXTCPCCNT_OFFSET));
    FXMAC_INFO("rx_udp_ck_errors is 0x%x",FtIn32(config_p->base_address+FXMAC_RXUDPCCNT_OFFSET));
}


void FXmacDebugUsxPrint(FXmac *instance_p)
{
    FXmacConfig *config_p;
    config_p = &instance_p->config;

    FXMAC_INFO("USXGMII control register is 0x%x",FtIn32(config_p->base_address+FXMAC_GEM_USX_CONTROL_OFFSET));
    FXMAC_INFO("USXGMII Status Register is 0x%x",FtIn32(config_p->base_address+FXMAC_GEM_USX_STATUS_OFFSET));
}