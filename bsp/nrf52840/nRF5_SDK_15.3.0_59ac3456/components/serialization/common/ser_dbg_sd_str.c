/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "ser_dbg_sd_str.h"
#include "nrf_soc.h"
#include "nrf_log.h"
#include <string.h>
#include "sdk_common.h"

#ifdef BLE_STACK_SUPPORT_REQD
#include "ble_ranges.h"
#endif

#ifdef ANT_STACK_SUPPORT_REQD
#include "ant_interface.h"
#include "ant_parameters.h"
#endif

#if NRF_MODULE_ENABLED(NRF_LOG) && defined(BLE_STACK_SUPPORT_REQD)
static const char * sd_events[] = {
    "BLE_EVT_USER_MEM_REQUEST",                /*0x01*/
    "BLE_EVT_USER_MEM_RELEASE",                /*0x02*/
    "SD_EVT_UNKNOWN",                          /*0x03*/
    "SD_EVT_UNKNOWN",                          /*0x04*/
    "SD_EVT_UNKNOWN",                          /*0x05*/
    "SD_EVT_UNKNOWN",                          /*0x06*/
    "SD_EVT_UNKNOWN",                          /*0x07*/
    "SD_EVT_UNKNOWN",                          /*0x08*/
    "SD_EVT_UNKNOWN",                          /*0x09*/
    "SD_EVT_UNKNOWN",                          /*0x0a*/
    "SD_EVT_UNKNOWN",                          /*0x0b*/
    "SD_EVT_UNKNOWN",                          /*0x0c*/
    "SD_EVT_UNKNOWN",                          /*0x0d*/
    "SD_EVT_UNKNOWN",                          /*0x0e*/
    "SD_EVT_UNKNOWN",                          /*0x0f*/
    "BLE_GAP_EVT_CONNECTED",                   /*0x10*/
    "BLE_GAP_EVT_DISCONNECTED",                /*0x11*/
    "BLE_GAP_EVT_CONN_PARAM_UPDATE",           /*0x12*/
    "BLE_GAP_EVT_SEC_PARAMS_REQUEST",          /*0x13*/
    "BLE_GAP_EVT_SEC_INFO_REQUEST",            /*0x14*/
    "BLE_GAP_EVT_PASSKEY_DISPLAY",             /*0x15*/
    "BLE_GAP_EVT_KEY_PRESSED",                 /*0x16*/
    "BLE_GAP_EVT_AUTH_KEY_REQUEST",            /*0x17*/
    "BLE_GAP_EVT_LESC_DHKEY_REQUEST",          /*0x18*/
    "BLE_GAP_EVT_AUTH_STATUS",                 /*0x19*/
    "BLE_GAP_EVT_CONN_SEC_UPDATE",             /*0x1a*/
    "BLE_GAP_EVT_TIMEOUT",                     /*0x1b*/
    "BLE_GAP_EVT_RSSI_CHANGED",                /*0x1c*/
    "BLE_GAP_EVT_ADV_REPORT",                  /*0x1d*/
    "BLE_GAP_EVT_SEC_REQUEST",                 /*0x1e*/
    "BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST",   /*0x1f*/
    "BLE_GAP_EVT_SCAN_REQ_REPORT",             /*0x20*/
    "BLE_GAP_EVT_PHY_UPDATE_REQUEST",          /*0x21*/
    "BLE_GAP_EVT_PHY_UPDATE",                  /*0x22*/
    "BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST",  /*0x23*/
    "BLE_GAP_EVT_DATA_LENGTH_UPDATE",          /*0x24*/
    "BLE_GAP_EVT_QOS_CHANNEL_SURVEY_REPORT",   /*0x25*/
    "BLE_GAP_EVT_ADV_SET_TERMINATED",          /*0x26*/
    "SD_EVT_UNKNOWN",                          /*0x27*/
    "SD_EVT_UNKNOWN",                          /*0x28*/
    "SD_EVT_UNKNOWN",                          /*0x29*/
    "SD_EVT_UNKNOWN",                          /*0x2a*/
    "SD_EVT_UNKNOWN",                          /*0x2b*/
    "SD_EVT_UNKNOWN",                          /*0x2c*/
    "SD_EVT_UNKNOWN",                          /*0x2d*/
    "SD_EVT_UNKNOWN",                          /*0x2e*/
    "SD_EVT_UNKNOWN",                          /*0x2f*/
    "BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP",        /*0x30*/
    "BLE_GATTC_EVT_REL_DISC_RSP",              /*0x31*/
    "BLE_GATTC_EVT_CHAR_DISC_RSP",             /*0x32*/
    "BLE_GATTC_EVT_DESC_DISC_RSP",             /*0x33*/
    "BLE_GATTC_EVT_ATTR_INFO_DISC_RSP",        /*0x34*/
    "BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP", /*0x35*/
    "BLE_GATTC_EVT_READ_RSP",                  /*0x36*/
    "BLE_GATTC_EVT_CHAR_VALS_READ_RSP",        /*0x37*/
    "BLE_GATTC_EVT_WRITE_RSP",                 /*0x38*/
    "BLE_GATTC_EVT_HVX",                       /*0x39*/
    "BLE_GATTC_EVT_EXCHANGE_MTU_RSP",          /*0x3a*/
    "BLE_GATTC_EVT_TIMEOUT",                   /*0x3b*/
    "SD_EVT_UNKNOWN",                          /*0x3c*/
    "SD_EVT_UNKNOWN",                          /*0x3d*/
    "SD_EVT_UNKNOWN",                          /*0x3e*/
    "SD_EVT_UNKNOWN",                          /*0x3f*/
    "SD_EVT_UNKNOWN",                          /*0x40*/
    "SD_EVT_UNKNOWN",                          /*0x41*/
    "SD_EVT_UNKNOWN",                          /*0x42*/
    "SD_EVT_UNKNOWN",                          /*0x43*/
    "SD_EVT_UNKNOWN",                          /*0x44*/
    "SD_EVT_UNKNOWN",                          /*0x45*/
    "SD_EVT_UNKNOWN",                          /*0x46*/
    "SD_EVT_UNKNOWN",                          /*0x47*/
    "SD_EVT_UNKNOWN",                          /*0x48*/
    "SD_EVT_UNKNOWN",                          /*0x49*/
    "SD_EVT_UNKNOWN",                          /*0x4a*/
    "SD_EVT_UNKNOWN",                          /*0x4b*/
    "SD_EVT_UNKNOWN",                          /*0x4c*/
    "SD_EVT_UNKNOWN",                          /*0x4d*/
    "SD_EVT_UNKNOWN",                          /*0x4e*/
    "SD_EVT_UNKNOWN",                          /*0x4f*/
    "BLE_GATTS_EVT_WRITE",                     /*0x50*/
    "BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST",      /*0x51*/
    "BLE_GATTS_EVT_SYS_ATTR_MISSING",          /*0x52*/
    "BLE_GATTS_EVT_HVC",                       /*0x53*/
    "BLE_GATTS_EVT_SC_CONFIRM",                /*0x54*/
    "BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST",      /*0x55*/
    "BLE_GATTS_EVT_TIMEOUT",                   /*0x56*/
};

static const char * sd_functions[] = {
    /* 0x60 offset */
    "SD_BLE_ENABLE",                           /*0x60*/
    "SD_BLE_EVT_GET",                          /*0x61*/
    "SD_BLE_UUID_VS_ADD",                      /*0x62*/
    "SD_BLE_UUID_DECODE",                      /*0x63*/
    "SD_BLE_UUID_ENCODE",                      /*0x64*/
    "SD_BLE_VERSION_GET",                      /*0x65*/
    "SD_BLE_USER_MEM_REPLY",                   /*0x66*/
    "SD_BLE_OPT_SET",                          /*0x67*/
    "SD_BLE_OPT_GET",                          /*0x68*/
    "SD_BLE_CFG_SET",                          /*0x69*/
    "SD_UNKNOWN",                              /*0x6A*/
    "SD_UNKNOWN",                              /*0x6B*/
    "SD_BLE_GAP_ADDR_SET"                ,     /*0x6C*/
    "SD_BLE_GAP_ADDR_GET"                ,     /*0x6D*/
    "SD_BLE_GAP_WHITELIST_SET"           ,     /*0x6E*/
    "SD_BLE_GAP_DEVICE_IDENTITIES_SET"   ,     /*0x6F*/
    "SD_BLE_GAP_PRIVACY_SET"             ,     /*0x70*/
    "SD_BLE_GAP_PRIVACY_GET"             ,     /*0x71*/
    "SD_BLE_GAP_ADV_SET_CONFIGURE"       ,     /*0x72*/
    "SD_BLE_GAP_ADV_START"               ,     /*0x73*/
    "SD_BLE_GAP_ADV_STOP"                ,     /*0x74*/
    "SD_BLE_GAP_CONN_PARAM_UPDATE"       ,     /*0x75*/
    "SD_BLE_GAP_DISCONNECT"              ,     /*0x76*/
    "SD_BLE_GAP_TX_POWER_SET"            ,     /*0x77*/
    "SD_BLE_GAP_APPEARANCE_SET"          ,     /*0x78*/
    "SD_BLE_GAP_APPEARANCE_GET"          ,     /*0x79*/
    "SD_BLE_GAP_PPCP_SET"                ,     /*0x7a*/
    "SD_BLE_GAP_PPCP_GET"                ,     /*0x7b*/
    "SD_BLE_GAP_DEVICE_NAME_SET"         ,     /*0x7c*/
    "SD_BLE_GAP_DEVICE_NAME_GET"         ,     /*0x7d*/
    "SD_BLE_GAP_AUTHENTICATE"            ,     /*0x7e*/
    "SD_BLE_GAP_SEC_PARAMS_REPLY"        ,     /*0x7f*/
    "SD_BLE_GAP_AUTH_KEY_REPLY"          ,     /*0x80*/
    "SD_BLE_GAP_LESC_DHKEY_REPLY"        ,     /*0x81*/
    "SD_BLE_GAP_KEYPRESS_NOTIFY"         ,     /*0x82*/
    "SD_BLE_GAP_LESC_OOB_DATA_GET"       ,     /*0x83*/
    "SD_BLE_GAP_LESC_OOB_DATA_SET"       ,     /*0x84*/
    "SD_BLE_GAP_ENCRYPT"                 ,     /*0x85*/
    "SD_BLE_GAP_SEC_INFO_REPLY"          ,     /*0x86*/
    "SD_BLE_GAP_CONN_SEC_GET"            ,     /*0x87*/
    "SD_BLE_GAP_RSSI_START"              ,     /*0x88*/
    "SD_BLE_GAP_RSSI_STOP"               ,     /*0x89*/
    "SD_BLE_GAP_SCAN_START"              ,     /*0x8a*/
    "SD_BLE_GAP_SCAN_STOP"               ,     /*0x8b*/
    "SD_BLE_GAP_CONNECT"                 ,     /*0x8c*/
    "SD_BLE_GAP_CONNECT_CANCEL "         ,     /*0x8d*/
    "SD_BLE_GAP_RSSI_GET"                ,     /*0x8e*/
    "SD_BLE_GAP_PHY_UPDATE"              ,     /*0x8f*/
    "SD_BLE_GAP_DATA_LENGTH_UPDATE"      ,     /*0x90*/
    "SD_BLE_GAP_QOS_CHANNEL_SURVEY_START",     /*0x91*/
    "SD_BLE_GAP_QOS_CHANNEL_SURVEY_STOP" ,     /*0x92*/
    "SD_UNKNOWN",                              /*0x93*/
    "SD_UNKNOWN",                              /*0x94*/
    "SD_UNKNOWN",                              /*0x95*/
    "SD_UNKNOWN",                              /*0x96*/
    "SD_UNKNOWN",                              /*0x97*/
    "SD_UNKNOWN",                              /*0x98*/
    "SD_UNKNOWN",                              /*0x99*/
    "SD_UNKNOWN",                              /*0x9A*/
    "SD_BLE_GATTC_PRIMARY_SERVICES_DISCOVER",  /*0x9B*/
    "SD_BLE_GATTC_RELATIONSHIPS_DISCOVER",     /*0x9C*/
    "SD_BLE_GATTC_CHARACTERISTICS_DISCOVER",   /*0x9D*/
    "SD_BLE_GATTC_DESCRIPTORS_DISCOVER",       /*0x9E*/
    "SD_BLE_GATTC_ATTR_INFO_DISCOVER",         /*0x9F*/
    "SD_BLE_GATTC_CHAR_VALUE_BY_UUID_READ",    /*0xA0*/
    "SD_BLE_GATTC_READ",                       /*0xA1*/
    "SD_BLE_GATTC_CHAR_VALUES_READ",           /*0xA2*/
    "SD_BLE_GATTC_WRITE",                      /*0xA3*/
    "SD_BLE_GATTC_HV_CONFIRM",                 /*0xA4*/
    "SD_BLE_GATTC_EXCHANGE_MTU_REQUEST",       /*0xA5*/
    "SD_UNKNOWN",                              /*0xA6*/
    "SD_UNKNOWN",                              /*0xA7*/
    "SD_BLE_GATTS_SERVICE_ADD",                /*0xA8*/
    "SD_BLE_GATTS_INCLUDE_ADD",                /*0xA9*/
    "SD_BLE_GATTS_CHARACTERISTIC_ADD",         /*0xAA*/
    "SD_BLE_GATTS_DESCRIPTOR_ADD",             /*0xAB*/
    "SD_BLE_GATTS_VALUE_SET",                  /*0xAC*/
    "SD_BLE_GATTS_VALUE_GET",                  /*0xAD*/
    "SD_BLE_GATTS_HVX",                        /*0xAE*/
    "SD_BLE_GATTS_SERVICE_CHANGED",            /*0xAF*/
    "SD_BLE_GATTS_RW_AUTHORIZE_REPLY",         /*0xB0*/
    "SD_BLE_GATTS_SYS_ATTR_SET",               /*0xB1*/
    "SD_BLE_GATTS_SYS_ATTR_GET",               /*0xB2*/
    "SD_BLE_GATTS_INITIAL_USER_HANDLE_GET",    /*0xB3*/
    "SD_BLE_GATTS_ATTR_GET",                   /*0xB4*/
    "SD_BLE_GATTS_EXCHANGE_MTU_REPLY",         /*0xB5*/
};
#endif // NRF_MODULE_ENABLED(NRF_LOG) && defined(BLE_STACK_SUPPORT_REQD)

#ifdef ANT_STACK_SUPPORT_REQD
const char * string[] =
{
    "ANT SVC",
    "ANT_EVT",
};
#endif // ANT_STACK_SUPPORT_REQD

const char * ser_dbg_sd_call_str_get(uint8_t opcode)
{
#if NRF_MODULE_ENABLED(NRF_LOG)
    const char * p_str = "SD_CALL_UNKNOWN";
#ifdef BLE_STACK_SUPPORT_REQD
    if (opcode >= BLE_SVC_BASE && opcode <= BLE_GATTS_SVC_LAST)
    {
        uint32_t idx = opcode-BLE_SVC_BASE;
        if (idx < ARRAY_SIZE(sd_functions) )
        {
            p_str = sd_functions[idx];
        }
    }
#endif // BLE_STACK_SUPPORT_REQD

#ifdef ANT_STACK_SUPPORT_REQD
    // Check if opcode is within the range of the ANT Stack API SVC numbers
#ifdef BLE_STACK_SUPPORT_REQD
    else if (opcode >= STK_SVC_BASE_2)
#else
    if (opcode >= STK_SVC_BASE_2)
#endif // BLE_STACK_SUPPORT_REQD
    {
        p_str = string[0];
    }
#endif // ANT_STACK_SUPPORT_REQD
    else
    {
        switch (opcode)
        {
            case SD_ECB_BLOCK_ENCRYPT:
                p_str = "SD_ECB_BLOCK_ENCRYPT";
                break;
            case SD_TEMP_GET:
                p_str = "SD_TEMP_GET";
                break;
            default:
                break;
        }
    }
    return p_str;
#else
    return NULL;
#endif
}

const char * ser_dbg_sd_evt_str_get(uint16_t opcode)
{
#if NRF_MODULE_ENABLED(NRF_LOG)
    const char * p_str = "SD_EVT_UNKNOWN";
#ifdef BLE_STACK_SUPPORT_REQD
    if (opcode >= BLE_EVT_BASE && opcode <= BLE_GATTS_EVT_LAST)
    {
        uint32_t idx = opcode - BLE_EVT_BASE;
        if (idx < ARRAY_SIZE(sd_events))
        {
            p_str = sd_events[idx];
        }
    }
#endif // BLE_STACK_SUPPORT_REQD

#ifdef ANT_STACK_SUPPORT_REQD
    // Check if opcode is within the range of the ANT Stack API SVC numbers
#ifdef BLE_STACK_SUPPORT_REQD
    else if (opcode <= EVENT_BLOCKED)
#else
    if (opcode <= EVENT_BLOCKED)
#endif // BLE_STACK_SUPPORT_REQD
    {
        p_str = string[1];
    }
#endif
    return p_str;
#else
    return NULL;
#endif // NRF_MODULE_ENABLED(NRF_LOG)
}
