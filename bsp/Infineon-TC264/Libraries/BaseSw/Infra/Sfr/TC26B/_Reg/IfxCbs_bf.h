/**
 * \file IfxCbs_bf.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Cbs_BitfieldsMask Bitfields mask and offset
 * \ingroup IfxLld_Cbs
 * 
 */
#ifndef IFXCBS_BF_H
#define IFXCBS_BF_H 1
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cbs_BitfieldsMask
 * \{  */

/** \brief  Length for Ifx_CBS_COMDATA_Bits.DATA */
#define IFX_CBS_COMDATA_DATA_LEN (32u)

/** \brief  Mask for Ifx_CBS_COMDATA_Bits.DATA */
#define IFX_CBS_COMDATA_DATA_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CBS_COMDATA_Bits.DATA */
#define IFX_CBS_COMDATA_DATA_OFF (0u)

/** \brief  Length for Ifx_CBS_ICTSA_Bits.ADDR */
#define IFX_CBS_ICTSA_ADDR_LEN (32u)

/** \brief  Mask for Ifx_CBS_ICTSA_Bits.ADDR */
#define IFX_CBS_ICTSA_ADDR_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CBS_ICTSA_Bits.ADDR */
#define IFX_CBS_ICTSA_ADDR_OFF (0u)

/** \brief  Length for Ifx_CBS_ICTTA_Bits.ADDR */
#define IFX_CBS_ICTTA_ADDR_LEN (32u)

/** \brief  Mask for Ifx_CBS_ICTTA_Bits.ADDR */
#define IFX_CBS_ICTTA_ADDR_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CBS_ICTTA_Bits.ADDR */
#define IFX_CBS_ICTTA_ADDR_OFF (0u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.CHANNEL */
#define IFX_CBS_INTMOD_CHANNEL_LEN (3u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.CHANNEL */
#define IFX_CBS_INTMOD_CHANNEL_MSK (0x7u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.CHANNEL */
#define IFX_CBS_INTMOD_CHANNEL_OFF (5u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.CHANNEL_P */
#define IFX_CBS_INTMOD_CHANNEL_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.CHANNEL_P */
#define IFX_CBS_INTMOD_CHANNEL_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.CHANNEL_P */
#define IFX_CBS_INTMOD_CHANNEL_P_OFF (4u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.CLR_CS */
#define IFX_CBS_INTMOD_CLR_CS_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.CLR_CS */
#define IFX_CBS_INTMOD_CLR_CS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.CLR_CS */
#define IFX_CBS_INTMOD_CLR_CS_OFF (3u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.CLR_INT_TRC */
#define IFX_CBS_INTMOD_CLR_INT_TRC_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.CLR_INT_TRC */
#define IFX_CBS_INTMOD_CLR_INT_TRC_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.CLR_INT_TRC */
#define IFX_CBS_INTMOD_CLR_INT_TRC_OFF (19u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.INT_MOD */
#define IFX_CBS_INTMOD_INT_MOD_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.INT_MOD */
#define IFX_CBS_INTMOD_INT_MOD_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.INT_MOD */
#define IFX_CBS_INTMOD_INT_MOD_OFF (24u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.INT_TRC */
#define IFX_CBS_INTMOD_INT_TRC_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.INT_TRC */
#define IFX_CBS_INTMOD_INT_TRC_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.INT_TRC */
#define IFX_CBS_INTMOD_INT_TRC_OFF (25u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.SET_CRS */
#define IFX_CBS_INTMOD_SET_CRS_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.SET_CRS */
#define IFX_CBS_INTMOD_SET_CRS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.SET_CRS */
#define IFX_CBS_INTMOD_SET_CRS_OFF (0u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.SET_CS */
#define IFX_CBS_INTMOD_SET_CS_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.SET_CS */
#define IFX_CBS_INTMOD_SET_CS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.SET_CS */
#define IFX_CBS_INTMOD_SET_CS_OFF (2u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.SET_CWS */
#define IFX_CBS_INTMOD_SET_CWS_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.SET_CWS */
#define IFX_CBS_INTMOD_SET_CWS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.SET_CWS */
#define IFX_CBS_INTMOD_SET_CWS_OFF (1u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.SET_INT_MOD */
#define IFX_CBS_INTMOD_SET_INT_MOD_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.SET_INT_MOD */
#define IFX_CBS_INTMOD_SET_INT_MOD_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.SET_INT_MOD */
#define IFX_CBS_INTMOD_SET_INT_MOD_OFF (16u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.SET_INT_TRC */
#define IFX_CBS_INTMOD_SET_INT_TRC_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.SET_INT_TRC */
#define IFX_CBS_INTMOD_SET_INT_TRC_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.SET_INT_TRC */
#define IFX_CBS_INTMOD_SET_INT_TRC_OFF (18u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.TRC_MOD */
#define IFX_CBS_INTMOD_TRC_MOD_LEN (2u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.TRC_MOD */
#define IFX_CBS_INTMOD_TRC_MOD_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.TRC_MOD */
#define IFX_CBS_INTMOD_TRC_MOD_OFF (21u)

/** \brief  Length for Ifx_CBS_INTMOD_Bits.TRC_MOD_P */
#define IFX_CBS_INTMOD_TRC_MOD_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_INTMOD_Bits.TRC_MOD_P */
#define IFX_CBS_INTMOD_TRC_MOD_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_INTMOD_Bits.TRC_MOD_P */
#define IFX_CBS_INTMOD_TRC_MOD_P_OFF (20u)

/** \brief  Length for Ifx_CBS_IOSR_Bits.CHANNEL */
#define IFX_CBS_IOSR_CHANNEL_LEN (3u)

/** \brief  Mask for Ifx_CBS_IOSR_Bits.CHANNEL */
#define IFX_CBS_IOSR_CHANNEL_MSK (0x7u)

/** \brief  Offset for Ifx_CBS_IOSR_Bits.CHANNEL */
#define IFX_CBS_IOSR_CHANNEL_OFF (12u)

/** \brief  Length for Ifx_CBS_IOSR_Bits.COM_SYNC */
#define IFX_CBS_IOSR_COM_SYNC_LEN (1u)

/** \brief  Mask for Ifx_CBS_IOSR_Bits.COM_SYNC */
#define IFX_CBS_IOSR_COM_SYNC_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_IOSR_Bits.COM_SYNC */
#define IFX_CBS_IOSR_COM_SYNC_OFF (7u)

/** \brief  Length for Ifx_CBS_IOSR_Bits.CRSYNC */
#define IFX_CBS_IOSR_CRSYNC_LEN (1u)

/** \brief  Mask for Ifx_CBS_IOSR_Bits.CRSYNC */
#define IFX_CBS_IOSR_CRSYNC_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_IOSR_Bits.CRSYNC */
#define IFX_CBS_IOSR_CRSYNC_OFF (4u)

/** \brief  Length for Ifx_CBS_IOSR_Bits.CW_ACK */
#define IFX_CBS_IOSR_CW_ACK_LEN (1u)

/** \brief  Mask for Ifx_CBS_IOSR_Bits.CW_ACK */
#define IFX_CBS_IOSR_CW_ACK_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_IOSR_Bits.CW_ACK */
#define IFX_CBS_IOSR_CW_ACK_OFF (6u)

/** \brief  Length for Ifx_CBS_IOSR_Bits.CWSYNC */
#define IFX_CBS_IOSR_CWSYNC_LEN (1u)

/** \brief  Mask for Ifx_CBS_IOSR_Bits.CWSYNC */
#define IFX_CBS_IOSR_CWSYNC_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_IOSR_Bits.CWSYNC */
#define IFX_CBS_IOSR_CWSYNC_OFF (5u)

/** \brief  Length for Ifx_CBS_IOSR_Bits.HOSTED */
#define IFX_CBS_IOSR_HOSTED_LEN (1u)

/** \brief  Mask for Ifx_CBS_IOSR_Bits.HOSTED */
#define IFX_CBS_IOSR_HOSTED_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_IOSR_Bits.HOSTED */
#define IFX_CBS_IOSR_HOSTED_OFF (8u)

/** \brief  Length for Ifx_CBS_JDPID_Bits.MODNUMBER */
#define IFX_CBS_JDPID_MODNUMBER_LEN (16u)

/** \brief  Mask for Ifx_CBS_JDPID_Bits.MODNUMBER */
#define IFX_CBS_JDPID_MODNUMBER_MSK (0xffffu)

/** \brief  Offset for Ifx_CBS_JDPID_Bits.MODNUMBER */
#define IFX_CBS_JDPID_MODNUMBER_OFF (16u)

/** \brief  Length for Ifx_CBS_JDPID_Bits.MODREV */
#define IFX_CBS_JDPID_MODREV_LEN (8u)

/** \brief  Mask for Ifx_CBS_JDPID_Bits.MODREV */
#define IFX_CBS_JDPID_MODREV_MSK (0xffu)

/** \brief  Offset for Ifx_CBS_JDPID_Bits.MODREV */
#define IFX_CBS_JDPID_MODREV_OFF (0u)

/** \brief  Length for Ifx_CBS_JDPID_Bits.MODTYPE */
#define IFX_CBS_JDPID_MODTYPE_LEN (8u)

/** \brief  Mask for Ifx_CBS_JDPID_Bits.MODTYPE */
#define IFX_CBS_JDPID_MODTYPE_MSK (0xffu)

/** \brief  Offset for Ifx_CBS_JDPID_Bits.MODTYPE */
#define IFX_CBS_JDPID_MODTYPE_OFF (8u)

/** \brief  Length for Ifx_CBS_JTAGID_Bits.JTAG_ID */
#define IFX_CBS_JTAGID_JTAG_ID_LEN (32u)

/** \brief  Mask for Ifx_CBS_JTAGID_Bits.JTAG_ID */
#define IFX_CBS_JTAGID_JTAG_ID_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CBS_JTAGID_Bits.JTAG_ID */
#define IFX_CBS_JTAGID_JTAG_ID_OFF (0u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC0 */
#define IFX_CBS_OCNTRL_OC0_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC0 */
#define IFX_CBS_OCNTRL_OC0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC0 */
#define IFX_CBS_OCNTRL_OC0_OFF (1u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC0_P */
#define IFX_CBS_OCNTRL_OC0_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC0_P */
#define IFX_CBS_OCNTRL_OC0_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC0_P */
#define IFX_CBS_OCNTRL_OC0_P_OFF (0u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC1 */
#define IFX_CBS_OCNTRL_OC1_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC1 */
#define IFX_CBS_OCNTRL_OC1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC1 */
#define IFX_CBS_OCNTRL_OC1_OFF (3u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC1_P */
#define IFX_CBS_OCNTRL_OC1_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC1_P */
#define IFX_CBS_OCNTRL_OC1_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC1_P */
#define IFX_CBS_OCNTRL_OC1_P_OFF (2u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC2 */
#define IFX_CBS_OCNTRL_OC2_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC2 */
#define IFX_CBS_OCNTRL_OC2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC2 */
#define IFX_CBS_OCNTRL_OC2_OFF (5u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC2_P */
#define IFX_CBS_OCNTRL_OC2_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC2_P */
#define IFX_CBS_OCNTRL_OC2_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC2_P */
#define IFX_CBS_OCNTRL_OC2_P_OFF (4u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC3 */
#define IFX_CBS_OCNTRL_OC3_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC3 */
#define IFX_CBS_OCNTRL_OC3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC3 */
#define IFX_CBS_OCNTRL_OC3_OFF (7u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC3_P */
#define IFX_CBS_OCNTRL_OC3_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC3_P */
#define IFX_CBS_OCNTRL_OC3_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC3_P */
#define IFX_CBS_OCNTRL_OC3_P_OFF (6u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC4 */
#define IFX_CBS_OCNTRL_OC4_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC4 */
#define IFX_CBS_OCNTRL_OC4_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC4 */
#define IFX_CBS_OCNTRL_OC4_OFF (9u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC4_P */
#define IFX_CBS_OCNTRL_OC4_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC4_P */
#define IFX_CBS_OCNTRL_OC4_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC4_P */
#define IFX_CBS_OCNTRL_OC4_P_OFF (8u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC5 */
#define IFX_CBS_OCNTRL_OC5_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC5 */
#define IFX_CBS_OCNTRL_OC5_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC5 */
#define IFX_CBS_OCNTRL_OC5_OFF (11u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OC5_P */
#define IFX_CBS_OCNTRL_OC5_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OC5_P */
#define IFX_CBS_OCNTRL_OC5_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OC5_P */
#define IFX_CBS_OCNTRL_OC5_P_OFF (10u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC0 */
#define IFX_CBS_OCNTRL_OJC0_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC0 */
#define IFX_CBS_OCNTRL_OJC0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC0 */
#define IFX_CBS_OCNTRL_OJC0_OFF (17u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC0_P */
#define IFX_CBS_OCNTRL_OJC0_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC0_P */
#define IFX_CBS_OCNTRL_OJC0_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC0_P */
#define IFX_CBS_OCNTRL_OJC0_P_OFF (16u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC1 */
#define IFX_CBS_OCNTRL_OJC1_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC1 */
#define IFX_CBS_OCNTRL_OJC1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC1 */
#define IFX_CBS_OCNTRL_OJC1_OFF (19u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC1_P */
#define IFX_CBS_OCNTRL_OJC1_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC1_P */
#define IFX_CBS_OCNTRL_OJC1_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC1_P */
#define IFX_CBS_OCNTRL_OJC1_P_OFF (18u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC2 */
#define IFX_CBS_OCNTRL_OJC2_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC2 */
#define IFX_CBS_OCNTRL_OJC2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC2 */
#define IFX_CBS_OCNTRL_OJC2_OFF (21u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC2_P */
#define IFX_CBS_OCNTRL_OJC2_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC2_P */
#define IFX_CBS_OCNTRL_OJC2_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC2_P */
#define IFX_CBS_OCNTRL_OJC2_P_OFF (20u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC3 */
#define IFX_CBS_OCNTRL_OJC3_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC3 */
#define IFX_CBS_OCNTRL_OJC3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC3 */
#define IFX_CBS_OCNTRL_OJC3_OFF (23u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC3_P */
#define IFX_CBS_OCNTRL_OJC3_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC3_P */
#define IFX_CBS_OCNTRL_OJC3_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC3_P */
#define IFX_CBS_OCNTRL_OJC3_P_OFF (22u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC4 */
#define IFX_CBS_OCNTRL_OJC4_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC4 */
#define IFX_CBS_OCNTRL_OJC4_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC4 */
#define IFX_CBS_OCNTRL_OJC4_OFF (25u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC4_P */
#define IFX_CBS_OCNTRL_OJC4_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC4_P */
#define IFX_CBS_OCNTRL_OJC4_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC4_P */
#define IFX_CBS_OCNTRL_OJC4_P_OFF (24u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC5 */
#define IFX_CBS_OCNTRL_OJC5_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC5 */
#define IFX_CBS_OCNTRL_OJC5_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC5 */
#define IFX_CBS_OCNTRL_OJC5_OFF (27u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC5_P */
#define IFX_CBS_OCNTRL_OJC5_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC5_P */
#define IFX_CBS_OCNTRL_OJC5_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC5_P */
#define IFX_CBS_OCNTRL_OJC5_P_OFF (26u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC6 */
#define IFX_CBS_OCNTRL_OJC6_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC6 */
#define IFX_CBS_OCNTRL_OJC6_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC6 */
#define IFX_CBS_OCNTRL_OJC6_OFF (29u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC6_P */
#define IFX_CBS_OCNTRL_OJC6_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC6_P */
#define IFX_CBS_OCNTRL_OJC6_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC6_P */
#define IFX_CBS_OCNTRL_OJC6_P_OFF (28u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC7 */
#define IFX_CBS_OCNTRL_OJC7_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC7 */
#define IFX_CBS_OCNTRL_OJC7_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC7 */
#define IFX_CBS_OCNTRL_OJC7_OFF (31u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.OJC7_P */
#define IFX_CBS_OCNTRL_OJC7_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.OJC7_P */
#define IFX_CBS_OCNTRL_OJC7_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.OJC7_P */
#define IFX_CBS_OCNTRL_OJC7_P_OFF (30u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.STABLE */
#define IFX_CBS_OCNTRL_STABLE_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.STABLE */
#define IFX_CBS_OCNTRL_STABLE_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.STABLE */
#define IFX_CBS_OCNTRL_STABLE_OFF (15u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.STABLE_P */
#define IFX_CBS_OCNTRL_STABLE_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.STABLE_P */
#define IFX_CBS_OCNTRL_STABLE_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.STABLE_P */
#define IFX_CBS_OCNTRL_STABLE_P_OFF (14u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.WDTSUS */
#define IFX_CBS_OCNTRL_WDTSUS_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.WDTSUS */
#define IFX_CBS_OCNTRL_WDTSUS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.WDTSUS */
#define IFX_CBS_OCNTRL_WDTSUS_OFF (13u)

/** \brief  Length for Ifx_CBS_OCNTRL_Bits.WDTSUS_P */
#define IFX_CBS_OCNTRL_WDTSUS_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OCNTRL_Bits.WDTSUS_P */
#define IFX_CBS_OCNTRL_WDTSUS_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OCNTRL_Bits.WDTSUS_P */
#define IFX_CBS_OCNTRL_WDTSUS_P_OFF (12u)

/** \brief  Length for Ifx_CBS_OEC_Bits.AUT_OK */
#define IFX_CBS_OEC_AUT_OK_LEN (1u)

/** \brief  Mask for Ifx_CBS_OEC_Bits.AUT_OK */
#define IFX_CBS_OEC_AUT_OK_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OEC_Bits.AUT_OK */
#define IFX_CBS_OEC_AUT_OK_OFF (19u)

/** \brief  Length for Ifx_CBS_OEC_Bits.AUT_OK_P */
#define IFX_CBS_OEC_AUT_OK_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OEC_Bits.AUT_OK_P */
#define IFX_CBS_OEC_AUT_OK_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OEC_Bits.AUT_OK_P */
#define IFX_CBS_OEC_AUT_OK_P_OFF (18u)

/** \brief  Length for Ifx_CBS_OEC_Bits.DS */
#define IFX_CBS_OEC_DS_LEN (1u)

/** \brief  Mask for Ifx_CBS_OEC_Bits.DS */
#define IFX_CBS_OEC_DS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OEC_Bits.DS */
#define IFX_CBS_OEC_DS_OFF (8u)

/** \brief  Length for Ifx_CBS_OEC_Bits.IF_LCK */
#define IFX_CBS_OEC_IF_LCK_LEN (1u)

/** \brief  Mask for Ifx_CBS_OEC_Bits.IF_LCK */
#define IFX_CBS_OEC_IF_LCK_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OEC_Bits.IF_LCK */
#define IFX_CBS_OEC_IF_LCK_OFF (17u)

/** \brief  Length for Ifx_CBS_OEC_Bits.IF_LCK_P */
#define IFX_CBS_OEC_IF_LCK_P_LEN (1u)

/** \brief  Mask for Ifx_CBS_OEC_Bits.IF_LCK_P */
#define IFX_CBS_OEC_IF_LCK_P_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OEC_Bits.IF_LCK_P */
#define IFX_CBS_OEC_IF_LCK_P_OFF (16u)

/** \brief  Length for Ifx_CBS_OEC_Bits.OCO */
#define IFX_CBS_OEC_OCO_LEN (1u)

/** \brief  Mask for Ifx_CBS_OEC_Bits.OCO */
#define IFX_CBS_OEC_OCO_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OEC_Bits.OCO */
#define IFX_CBS_OEC_OCO_OFF (9u)

/** \brief  Length for Ifx_CBS_OEC_Bits.PAT */
#define IFX_CBS_OEC_PAT_LEN (8u)

/** \brief  Mask for Ifx_CBS_OEC_Bits.PAT */
#define IFX_CBS_OEC_PAT_MSK (0xffu)

/** \brief  Offset for Ifx_CBS_OEC_Bits.PAT */
#define IFX_CBS_OEC_PAT_OFF (0u)

/** \brief  Length for Ifx_CBS_OIFM_Bits.DAPMODE */
#define IFX_CBS_OIFM_DAPMODE_LEN (3u)

/** \brief  Mask for Ifx_CBS_OIFM_Bits.DAPMODE */
#define IFX_CBS_OIFM_DAPMODE_MSK (0x7u)

/** \brief  Offset for Ifx_CBS_OIFM_Bits.DAPMODE */
#define IFX_CBS_OIFM_DAPMODE_OFF (0u)

/** \brief  Length for Ifx_CBS_OIFM_Bits.DAPRST */
#define IFX_CBS_OIFM_DAPRST_LEN (1u)

/** \brief  Mask for Ifx_CBS_OIFM_Bits.DAPRST */
#define IFX_CBS_OIFM_DAPRST_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OIFM_Bits.DAPRST */
#define IFX_CBS_OIFM_DAPRST_OFF (3u)

/** \brief  Length for Ifx_CBS_OIFM_Bits.F_JTAG */
#define IFX_CBS_OIFM_F_JTAG_LEN (1u)

/** \brief  Mask for Ifx_CBS_OIFM_Bits.F_JTAG */
#define IFX_CBS_OIFM_F_JTAG_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OIFM_Bits.F_JTAG */
#define IFX_CBS_OIFM_F_JTAG_OFF (8u)

/** \brief  Length for Ifx_CBS_OIFM_Bits.N_JTAG */
#define IFX_CBS_OIFM_N_JTAG_LEN (1u)

/** \brief  Mask for Ifx_CBS_OIFM_Bits.N_JTAG */
#define IFX_CBS_OIFM_N_JTAG_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OIFM_Bits.N_JTAG */
#define IFX_CBS_OIFM_N_JTAG_OFF (9u)

/** \brief  Length for Ifx_CBS_OIFM_Bits.PADCTL */
#define IFX_CBS_OIFM_PADCTL_LEN (4u)

/** \brief  Mask for Ifx_CBS_OIFM_Bits.PADCTL */
#define IFX_CBS_OIFM_PADCTL_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_OIFM_Bits.PADCTL */
#define IFX_CBS_OIFM_PADCTL_OFF (12u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.AUT_OK */
#define IFX_CBS_OSTATE_AUT_OK_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.AUT_OK */
#define IFX_CBS_OSTATE_AUT_OK_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.AUT_OK */
#define IFX_CBS_OSTATE_AUT_OK_OFF (17u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.EECDIS */
#define IFX_CBS_OSTATE_EECDIS_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.EECDIS */
#define IFX_CBS_OSTATE_EECDIS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.EECDIS */
#define IFX_CBS_OSTATE_EECDIS_OFF (6u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.EECTRC */
#define IFX_CBS_OSTATE_EECTRC_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.EECTRC */
#define IFX_CBS_OSTATE_EECTRC_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.EECTRC */
#define IFX_CBS_OSTATE_EECTRC_OFF (5u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.ENIDIS */
#define IFX_CBS_OSTATE_ENIDIS_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.ENIDIS */
#define IFX_CBS_OSTATE_ENIDIS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.ENIDIS */
#define IFX_CBS_OSTATE_ENIDIS_OFF (4u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.HARR */
#define IFX_CBS_OSTATE_HARR_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.HARR */
#define IFX_CBS_OSTATE_HARR_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.HARR */
#define IFX_CBS_OSTATE_HARR_OFF (8u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.IF_LCK */
#define IFX_CBS_OSTATE_IF_LCK_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.IF_LCK */
#define IFX_CBS_OSTATE_IF_LCK_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.IF_LCK */
#define IFX_CBS_OSTATE_IF_LCK_OFF (16u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OC0 */
#define IFX_CBS_OSTATE_OC0_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OC0 */
#define IFX_CBS_OSTATE_OC0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OC0 */
#define IFX_CBS_OSTATE_OC0_OFF (1u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OC1 */
#define IFX_CBS_OSTATE_OC1_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OC1 */
#define IFX_CBS_OSTATE_OC1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OC1 */
#define IFX_CBS_OSTATE_OC1_OFF (2u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OC2 */
#define IFX_CBS_OSTATE_OC2_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OC2 */
#define IFX_CBS_OSTATE_OC2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OC2 */
#define IFX_CBS_OSTATE_OC2_OFF (3u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OCO */
#define IFX_CBS_OSTATE_OCO_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OCO */
#define IFX_CBS_OSTATE_OCO_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OCO */
#define IFX_CBS_OSTATE_OCO_OFF (19u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OEN */
#define IFX_CBS_OSTATE_OEN_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OEN */
#define IFX_CBS_OSTATE_OEN_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OEN */
#define IFX_CBS_OSTATE_OEN_OFF (0u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OJC1 */
#define IFX_CBS_OSTATE_OJC1_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OJC1 */
#define IFX_CBS_OSTATE_OJC1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OJC1 */
#define IFX_CBS_OSTATE_OJC1_OFF (9u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OJC2 */
#define IFX_CBS_OSTATE_OJC2_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OJC2 */
#define IFX_CBS_OSTATE_OJC2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OJC2 */
#define IFX_CBS_OSTATE_OJC2_OFF (10u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OJC3 */
#define IFX_CBS_OSTATE_OJC3_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OJC3 */
#define IFX_CBS_OSTATE_OJC3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OJC3 */
#define IFX_CBS_OSTATE_OJC3_OFF (11u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.OJC6 */
#define IFX_CBS_OSTATE_OJC6_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.OJC6 */
#define IFX_CBS_OSTATE_OJC6_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.OJC6 */
#define IFX_CBS_OSTATE_OJC6_OFF (14u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.RSTCL0 */
#define IFX_CBS_OSTATE_RSTCL0_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.RSTCL0 */
#define IFX_CBS_OSTATE_RSTCL0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.RSTCL0 */
#define IFX_CBS_OSTATE_RSTCL0_OFF (12u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.RSTCL1 */
#define IFX_CBS_OSTATE_RSTCL1_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.RSTCL1 */
#define IFX_CBS_OSTATE_RSTCL1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.RSTCL1 */
#define IFX_CBS_OSTATE_RSTCL1_OFF (13u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.RSTCL3 */
#define IFX_CBS_OSTATE_RSTCL3_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.RSTCL3 */
#define IFX_CBS_OSTATE_RSTCL3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.RSTCL3 */
#define IFX_CBS_OSTATE_RSTCL3_OFF (15u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.STABLE */
#define IFX_CBS_OSTATE_STABLE_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.STABLE */
#define IFX_CBS_OSTATE_STABLE_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.STABLE */
#define IFX_CBS_OSTATE_STABLE_OFF (18u)

/** \brief  Length for Ifx_CBS_OSTATE_Bits.WDTSUS */
#define IFX_CBS_OSTATE_WDTSUS_LEN (1u)

/** \brief  Mask for Ifx_CBS_OSTATE_Bits.WDTSUS */
#define IFX_CBS_OSTATE_WDTSUS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_OSTATE_Bits.WDTSUS */
#define IFX_CBS_OSTATE_WDTSUS_OFF (7u)

/** \brief  Length for Ifx_CBS_TCCB_Bits.C0 */
#define IFX_CBS_TCCB_C0_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCB_Bits.C0 */
#define IFX_CBS_TCCB_C0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCB_Bits.C0 */
#define IFX_CBS_TCCB_C0_OFF (0u)

/** \brief  Length for Ifx_CBS_TCCB_Bits.C1 */
#define IFX_CBS_TCCB_C1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCB_Bits.C1 */
#define IFX_CBS_TCCB_C1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCB_Bits.C1 */
#define IFX_CBS_TCCB_C1_OFF (1u)

/** \brief  Length for Ifx_CBS_TCCB_Bits.C2 */
#define IFX_CBS_TCCB_C2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCB_Bits.C2 */
#define IFX_CBS_TCCB_C2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCB_Bits.C2 */
#define IFX_CBS_TCCB_C2_OFF (2u)

/** \brief  Length for Ifx_CBS_TCCB_Bits.HSM */
#define IFX_CBS_TCCB_HSM_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCB_Bits.HSM */
#define IFX_CBS_TCCB_HSM_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCB_Bits.HSM */
#define IFX_CBS_TCCB_HSM_OFF (31u)

/** \brief  Length for Ifx_CBS_TCCH_Bits.C0 */
#define IFX_CBS_TCCH_C0_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCH_Bits.C0 */
#define IFX_CBS_TCCH_C0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCH_Bits.C0 */
#define IFX_CBS_TCCH_C0_OFF (0u)

/** \brief  Length for Ifx_CBS_TCCH_Bits.C1 */
#define IFX_CBS_TCCH_C1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCH_Bits.C1 */
#define IFX_CBS_TCCH_C1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCH_Bits.C1 */
#define IFX_CBS_TCCH_C1_OFF (1u)

/** \brief  Length for Ifx_CBS_TCCH_Bits.C2 */
#define IFX_CBS_TCCH_C2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCH_Bits.C2 */
#define IFX_CBS_TCCH_C2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCH_Bits.C2 */
#define IFX_CBS_TCCH_C2_OFF (2u)

/** \brief  Length for Ifx_CBS_TCCH_Bits.HSM */
#define IFX_CBS_TCCH_HSM_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCCH_Bits.HSM */
#define IFX_CBS_TCCH_HSM_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCCH_Bits.HSM */
#define IFX_CBS_TCCH_HSM_OFF (31u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P0 */
#define IFX_CBS_TCIP_P0_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P0 */
#define IFX_CBS_TCIP_P0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P0 */
#define IFX_CBS_TCIP_P0_OFF (0u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P1 */
#define IFX_CBS_TCIP_P1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P1 */
#define IFX_CBS_TCIP_P1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P1 */
#define IFX_CBS_TCIP_P1_OFF (1u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P2 */
#define IFX_CBS_TCIP_P2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P2 */
#define IFX_CBS_TCIP_P2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P2 */
#define IFX_CBS_TCIP_P2_OFF (2u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P3 */
#define IFX_CBS_TCIP_P3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P3 */
#define IFX_CBS_TCIP_P3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P3 */
#define IFX_CBS_TCIP_P3_OFF (3u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P4 */
#define IFX_CBS_TCIP_P4_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P4 */
#define IFX_CBS_TCIP_P4_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P4 */
#define IFX_CBS_TCIP_P4_OFF (4u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P5 */
#define IFX_CBS_TCIP_P5_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P5 */
#define IFX_CBS_TCIP_P5_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P5 */
#define IFX_CBS_TCIP_P5_OFF (5u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P6 */
#define IFX_CBS_TCIP_P6_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P6 */
#define IFX_CBS_TCIP_P6_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P6 */
#define IFX_CBS_TCIP_P6_OFF (6u)

/** \brief  Length for Ifx_CBS_TCIP_Bits.P7 */
#define IFX_CBS_TCIP_P7_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCIP_Bits.P7 */
#define IFX_CBS_TCIP_P7_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCIP_Bits.P7 */
#define IFX_CBS_TCIP_P7_OFF (7u)

/** \brief  Length for Ifx_CBS_TCM_Bits.BRK */
#define IFX_CBS_TCM_BRK_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCM_Bits.BRK */
#define IFX_CBS_TCM_BRK_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCM_Bits.BRK */
#define IFX_CBS_TCM_BRK_OFF (0u)

/** \brief  Length for Ifx_CBS_TCM_Bits.SUS */
#define IFX_CBS_TCM_SUS_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCM_Bits.SUS */
#define IFX_CBS_TCM_SUS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCM_Bits.SUS */
#define IFX_CBS_TCM_SUS_OFF (1u)

/** \brief  Length for Ifx_CBS_TCM_Bits.T0 */
#define IFX_CBS_TCM_T0_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCM_Bits.T0 */
#define IFX_CBS_TCM_T0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCM_Bits.T0 */
#define IFX_CBS_TCM_T0_OFF (8u)

/** \brief  Length for Ifx_CBS_TCM_Bits.T1 */
#define IFX_CBS_TCM_T1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCM_Bits.T1 */
#define IFX_CBS_TCM_T1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCM_Bits.T1 */
#define IFX_CBS_TCM_T1_OFF (9u)

/** \brief  Length for Ifx_CBS_TCM_Bits.T2 */
#define IFX_CBS_TCM_T2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCM_Bits.T2 */
#define IFX_CBS_TCM_T2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCM_Bits.T2 */
#define IFX_CBS_TCM_T2_OFF (10u)

/** \brief  Length for Ifx_CBS_TCM_Bits.T3 */
#define IFX_CBS_TCM_T3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCM_Bits.T3 */
#define IFX_CBS_TCM_T3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCM_Bits.T3 */
#define IFX_CBS_TCM_T3_OFF (11u)

/** \brief  Length for Ifx_CBS_TCTGB_Bits.OTGB0 */
#define IFX_CBS_TCTGB_OTGB0_LEN (16u)

/** \brief  Mask for Ifx_CBS_TCTGB_Bits.OTGB0 */
#define IFX_CBS_TCTGB_OTGB0_MSK (0xffffu)

/** \brief  Offset for Ifx_CBS_TCTGB_Bits.OTGB0 */
#define IFX_CBS_TCTGB_OTGB0_OFF (0u)

/** \brief  Length for Ifx_CBS_TCTGB_Bits.OTGB1 */
#define IFX_CBS_TCTGB_OTGB1_LEN (16u)

/** \brief  Mask for Ifx_CBS_TCTGB_Bits.OTGB1 */
#define IFX_CBS_TCTGB_OTGB1_MSK (0xffffu)

/** \brief  Offset for Ifx_CBS_TCTGB_Bits.OTGB1 */
#define IFX_CBS_TCTGB_OTGB1_OFF (16u)

/** \brief  Length for Ifx_CBS_TCTL_Bits.TL1 */
#define IFX_CBS_TCTL_TL1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCTL_Bits.TL1 */
#define IFX_CBS_TCTL_TL1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCTL_Bits.TL1 */
#define IFX_CBS_TCTL_TL1_OFF (1u)

/** \brief  Length for Ifx_CBS_TCTL_Bits.TL2 */
#define IFX_CBS_TCTL_TL2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCTL_Bits.TL2 */
#define IFX_CBS_TCTL_TL2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCTL_Bits.TL2 */
#define IFX_CBS_TCTL_TL2_OFF (2u)

/** \brief  Length for Ifx_CBS_TCTL_Bits.TL3 */
#define IFX_CBS_TCTL_TL3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCTL_Bits.TL3 */
#define IFX_CBS_TCTL_TL3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCTL_Bits.TL3 */
#define IFX_CBS_TCTL_TL3_OFF (3u)

/** \brief  Length for Ifx_CBS_TCTL_Bits.TL4 */
#define IFX_CBS_TCTL_TL4_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCTL_Bits.TL4 */
#define IFX_CBS_TCTL_TL4_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCTL_Bits.TL4 */
#define IFX_CBS_TCTL_TL4_OFF (4u)

/** \brief  Length for Ifx_CBS_TCTL_Bits.TL5 */
#define IFX_CBS_TCTL_TL5_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCTL_Bits.TL5 */
#define IFX_CBS_TCTL_TL5_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCTL_Bits.TL5 */
#define IFX_CBS_TCTL_TL5_OFF (5u)

/** \brief  Length for Ifx_CBS_TCTL_Bits.TL6 */
#define IFX_CBS_TCTL_TL6_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCTL_Bits.TL6 */
#define IFX_CBS_TCTL_TL6_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCTL_Bits.TL6 */
#define IFX_CBS_TCTL_TL6_OFF (6u)

/** \brief  Length for Ifx_CBS_TCTL_Bits.TL7 */
#define IFX_CBS_TCTL_TL7_LEN (1u)

/** \brief  Mask for Ifx_CBS_TCTL_Bits.TL7 */
#define IFX_CBS_TCTL_TL7_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TCTL_Bits.TL7 */
#define IFX_CBS_TCTL_TL7_OFF (7u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN0 */
#define IFX_CBS_TIPR_PIN0_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN0 */
#define IFX_CBS_TIPR_PIN0_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN0 */
#define IFX_CBS_TIPR_PIN0_OFF (0u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN1 */
#define IFX_CBS_TIPR_PIN1_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN1 */
#define IFX_CBS_TIPR_PIN1_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN1 */
#define IFX_CBS_TIPR_PIN1_OFF (4u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN2 */
#define IFX_CBS_TIPR_PIN2_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN2 */
#define IFX_CBS_TIPR_PIN2_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN2 */
#define IFX_CBS_TIPR_PIN2_OFF (8u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN3 */
#define IFX_CBS_TIPR_PIN3_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN3 */
#define IFX_CBS_TIPR_PIN3_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN3 */
#define IFX_CBS_TIPR_PIN3_OFF (12u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN4 */
#define IFX_CBS_TIPR_PIN4_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN4 */
#define IFX_CBS_TIPR_PIN4_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN4 */
#define IFX_CBS_TIPR_PIN4_OFF (16u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN5 */
#define IFX_CBS_TIPR_PIN5_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN5 */
#define IFX_CBS_TIPR_PIN5_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN5 */
#define IFX_CBS_TIPR_PIN5_OFF (20u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN6 */
#define IFX_CBS_TIPR_PIN6_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN6 */
#define IFX_CBS_TIPR_PIN6_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN6 */
#define IFX_CBS_TIPR_PIN6_OFF (24u)

/** \brief  Length for Ifx_CBS_TIPR_Bits.PIN7 */
#define IFX_CBS_TIPR_PIN7_LEN (4u)

/** \brief  Mask for Ifx_CBS_TIPR_Bits.PIN7 */
#define IFX_CBS_TIPR_PIN7_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TIPR_Bits.PIN7 */
#define IFX_CBS_TIPR_PIN7_OFF (28u)

/** \brief  Length for Ifx_CBS_TL1ST_Bits.C0 */
#define IFX_CBS_TL1ST_C0_LEN (1u)

/** \brief  Mask for Ifx_CBS_TL1ST_Bits.C0 */
#define IFX_CBS_TL1ST_C0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TL1ST_Bits.C0 */
#define IFX_CBS_TL1ST_C0_OFF (0u)

/** \brief  Length for Ifx_CBS_TL1ST_Bits.C1 */
#define IFX_CBS_TL1ST_C1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TL1ST_Bits.C1 */
#define IFX_CBS_TL1ST_C1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TL1ST_Bits.C1 */
#define IFX_CBS_TL1ST_C1_OFF (1u)

/** \brief  Length for Ifx_CBS_TL1ST_Bits.C2 */
#define IFX_CBS_TL1ST_C2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TL1ST_Bits.C2 */
#define IFX_CBS_TL1ST_C2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TL1ST_Bits.C2 */
#define IFX_CBS_TL1ST_C2_OFF (2u)

/** \brief  Length for Ifx_CBS_TL1ST_Bits.DMA */
#define IFX_CBS_TL1ST_DMA_LEN (1u)

/** \brief  Mask for Ifx_CBS_TL1ST_Bits.DMA */
#define IFX_CBS_TL1ST_DMA_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TL1ST_Bits.DMA */
#define IFX_CBS_TL1ST_DMA_OFF (29u)

/** \brief  Length for Ifx_CBS_TL1ST_Bits.HSM */
#define IFX_CBS_TL1ST_HSM_LEN (1u)

/** \brief  Mask for Ifx_CBS_TL1ST_Bits.HSM */
#define IFX_CBS_TL1ST_HSM_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TL1ST_Bits.HSM */
#define IFX_CBS_TL1ST_HSM_OFF (31u)

/** \brief  Length for Ifx_CBS_TL1ST_Bits.HSS */
#define IFX_CBS_TL1ST_HSS_LEN (1u)

/** \brief  Mask for Ifx_CBS_TL1ST_Bits.HSS */
#define IFX_CBS_TL1ST_HSS_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TL1ST_Bits.HSS */
#define IFX_CBS_TL1ST_HSS_OFF (28u)

/** \brief  Length for Ifx_CBS_TLC_Bits.TLSP1 */
#define IFX_CBS_TLC_TLSP1_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLC_Bits.TLSP1 */
#define IFX_CBS_TLC_TLSP1_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLC_Bits.TLSP1 */
#define IFX_CBS_TLC_TLSP1_OFF (4u)

/** \brief  Length for Ifx_CBS_TLC_Bits.TLSP2 */
#define IFX_CBS_TLC_TLSP2_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLC_Bits.TLSP2 */
#define IFX_CBS_TLC_TLSP2_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLC_Bits.TLSP2 */
#define IFX_CBS_TLC_TLSP2_OFF (8u)

/** \brief  Length for Ifx_CBS_TLC_Bits.TLSP3 */
#define IFX_CBS_TLC_TLSP3_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLC_Bits.TLSP3 */
#define IFX_CBS_TLC_TLSP3_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLC_Bits.TLSP3 */
#define IFX_CBS_TLC_TLSP3_OFF (12u)

/** \brief  Length for Ifx_CBS_TLC_Bits.TLSP4 */
#define IFX_CBS_TLC_TLSP4_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLC_Bits.TLSP4 */
#define IFX_CBS_TLC_TLSP4_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLC_Bits.TLSP4 */
#define IFX_CBS_TLC_TLSP4_OFF (16u)

/** \brief  Length for Ifx_CBS_TLC_Bits.TLSP5 */
#define IFX_CBS_TLC_TLSP5_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLC_Bits.TLSP5 */
#define IFX_CBS_TLC_TLSP5_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLC_Bits.TLSP5 */
#define IFX_CBS_TLC_TLSP5_OFF (20u)

/** \brief  Length for Ifx_CBS_TLC_Bits.TLSP6 */
#define IFX_CBS_TLC_TLSP6_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLC_Bits.TLSP6 */
#define IFX_CBS_TLC_TLSP6_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLC_Bits.TLSP6 */
#define IFX_CBS_TLC_TLSP6_OFF (24u)

/** \brief  Length for Ifx_CBS_TLC_Bits.TLSP7 */
#define IFX_CBS_TLC_TLSP7_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLC_Bits.TLSP7 */
#define IFX_CBS_TLC_TLSP7_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLC_Bits.TLSP7 */
#define IFX_CBS_TLC_TLSP7_OFF (28u)

/** \brief  Length for Ifx_CBS_TLCC_Bits.CLR */
#define IFX_CBS_TLCC_CLR_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLCC_Bits.CLR */
#define IFX_CBS_TLCC_CLR_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLCC_Bits.CLR */
#define IFX_CBS_TLCC_CLR_OFF (8u)

/** \brief  Length for Ifx_CBS_TLCC_Bits.LE */
#define IFX_CBS_TLCC_LE_LEN (3u)

/** \brief  Mask for Ifx_CBS_TLCC_Bits.LE */
#define IFX_CBS_TLCC_LE_MSK (0x7u)

/** \brief  Offset for Ifx_CBS_TLCC_Bits.LE */
#define IFX_CBS_TLCC_LE_OFF (4u)

/** \brief  Length for Ifx_CBS_TLCC_Bits.STOP */
#define IFX_CBS_TLCC_STOP_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLCC_Bits.STOP */
#define IFX_CBS_TLCC_STOP_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLCC_Bits.STOP */
#define IFX_CBS_TLCC_STOP_OFF (12u)

/** \brief  Length for Ifx_CBS_TLCC_Bits.TGL */
#define IFX_CBS_TLCC_TGL_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLCC_Bits.TGL */
#define IFX_CBS_TLCC_TGL_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLCC_Bits.TGL */
#define IFX_CBS_TLCC_TGL_OFF (0u)

/** \brief  Length for Ifx_CBS_TLCHE_Bits.TL1 */
#define IFX_CBS_TLCHE_TL1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLCHE_Bits.TL1 */
#define IFX_CBS_TLCHE_TL1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLCHE_Bits.TL1 */
#define IFX_CBS_TLCHE_TL1_OFF (1u)

/** \brief  Length for Ifx_CBS_TLCHE_Bits.TL2 */
#define IFX_CBS_TLCHE_TL2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLCHE_Bits.TL2 */
#define IFX_CBS_TLCHE_TL2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLCHE_Bits.TL2 */
#define IFX_CBS_TLCHE_TL2_OFF (2u)

/** \brief  Length for Ifx_CBS_TLCHE_Bits.TL3 */
#define IFX_CBS_TLCHE_TL3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLCHE_Bits.TL3 */
#define IFX_CBS_TLCHE_TL3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLCHE_Bits.TL3 */
#define IFX_CBS_TLCHE_TL3_OFF (3u)

/** \brief  Length for Ifx_CBS_TLCHS_Bits.TL1 */
#define IFX_CBS_TLCHS_TL1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLCHS_Bits.TL1 */
#define IFX_CBS_TLCHS_TL1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLCHS_Bits.TL1 */
#define IFX_CBS_TLCHS_TL1_OFF (1u)

/** \brief  Length for Ifx_CBS_TLCHS_Bits.TL2 */
#define IFX_CBS_TLCHS_TL2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLCHS_Bits.TL2 */
#define IFX_CBS_TLCHS_TL2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLCHS_Bits.TL2 */
#define IFX_CBS_TLCHS_TL2_OFF (2u)

/** \brief  Length for Ifx_CBS_TLCHS_Bits.TL3 */
#define IFX_CBS_TLCHS_TL3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLCHS_Bits.TL3 */
#define IFX_CBS_TLCHS_TL3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLCHS_Bits.TL3 */
#define IFX_CBS_TLCHS_TL3_OFF (3u)

/** \brief  Length for Ifx_CBS_TLCV_Bits.CV */
#define IFX_CBS_TLCV_CV_LEN (31u)

/** \brief  Mask for Ifx_CBS_TLCV_Bits.CV */
#define IFX_CBS_TLCV_CV_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CBS_TLCV_Bits.CV */
#define IFX_CBS_TLCV_CV_OFF (0u)

/** \brief  Length for Ifx_CBS_TLCV_Bits.SO */
#define IFX_CBS_TLCV_SO_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLCV_Bits.SO */
#define IFX_CBS_TLCV_SO_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLCV_Bits.SO */
#define IFX_CBS_TLCV_SO_OFF (31u)

/** \brief  Length for Ifx_CBS_TLS_Bits.TL1 */
#define IFX_CBS_TLS_TL1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLS_Bits.TL1 */
#define IFX_CBS_TLS_TL1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLS_Bits.TL1 */
#define IFX_CBS_TLS_TL1_OFF (1u)

/** \brief  Length for Ifx_CBS_TLS_Bits.TL2 */
#define IFX_CBS_TLS_TL2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLS_Bits.TL2 */
#define IFX_CBS_TLS_TL2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLS_Bits.TL2 */
#define IFX_CBS_TLS_TL2_OFF (2u)

/** \brief  Length for Ifx_CBS_TLS_Bits.TL3 */
#define IFX_CBS_TLS_TL3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLS_Bits.TL3 */
#define IFX_CBS_TLS_TL3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLS_Bits.TL3 */
#define IFX_CBS_TLS_TL3_OFF (3u)

/** \brief  Length for Ifx_CBS_TLS_Bits.TL4 */
#define IFX_CBS_TLS_TL4_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLS_Bits.TL4 */
#define IFX_CBS_TLS_TL4_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLS_Bits.TL4 */
#define IFX_CBS_TLS_TL4_OFF (4u)

/** \brief  Length for Ifx_CBS_TLS_Bits.TL5 */
#define IFX_CBS_TLS_TL5_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLS_Bits.TL5 */
#define IFX_CBS_TLS_TL5_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLS_Bits.TL5 */
#define IFX_CBS_TLS_TL5_OFF (5u)

/** \brief  Length for Ifx_CBS_TLS_Bits.TL6 */
#define IFX_CBS_TLS_TL6_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLS_Bits.TL6 */
#define IFX_CBS_TLS_TL6_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLS_Bits.TL6 */
#define IFX_CBS_TLS_TL6_OFF (6u)

/** \brief  Length for Ifx_CBS_TLS_Bits.TL7 */
#define IFX_CBS_TLS_TL7_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLS_Bits.TL7 */
#define IFX_CBS_TLS_TL7_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLS_Bits.TL7 */
#define IFX_CBS_TLS_TL7_OFF (7u)

/** \brief  Length for Ifx_CBS_TLT_Bits.TGL */
#define IFX_CBS_TLT_TGL_LEN (4u)

/** \brief  Mask for Ifx_CBS_TLT_Bits.TGL */
#define IFX_CBS_TLT_TGL_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TLT_Bits.TGL */
#define IFX_CBS_TLT_TGL_OFF (0u)

/** \brief  Length for Ifx_CBS_TLT_Bits.TIM */
#define IFX_CBS_TLT_TIM_LEN (16u)

/** \brief  Mask for Ifx_CBS_TLT_Bits.TIM */
#define IFX_CBS_TLT_TIM_MSK (0xffffu)

/** \brief  Offset for Ifx_CBS_TLT_Bits.TIM */
#define IFX_CBS_TLT_TIM_OFF (16u)

/** \brief  Length for Ifx_CBS_TLT_Bits.VTZ */
#define IFX_CBS_TLT_VTZ_LEN (1u)

/** \brief  Mask for Ifx_CBS_TLT_Bits.VTZ */
#define IFX_CBS_TLT_VTZ_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TLT_Bits.VTZ */
#define IFX_CBS_TLT_VTZ_OFF (4u)

/** \brief  Length for Ifx_CBS_TLTTH_Bits.TL1 */
#define IFX_CBS_TLTTH_TL1_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLTTH_Bits.TL1 */
#define IFX_CBS_TLTTH_TL1_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLTTH_Bits.TL1 */
#define IFX_CBS_TLTTH_TL1_OFF (2u)

/** \brief  Length for Ifx_CBS_TLTTH_Bits.TL2 */
#define IFX_CBS_TLTTH_TL2_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLTTH_Bits.TL2 */
#define IFX_CBS_TLTTH_TL2_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLTTH_Bits.TL2 */
#define IFX_CBS_TLTTH_TL2_OFF (4u)

/** \brief  Length for Ifx_CBS_TLTTH_Bits.TL3 */
#define IFX_CBS_TLTTH_TL3_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLTTH_Bits.TL3 */
#define IFX_CBS_TLTTH_TL3_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLTTH_Bits.TL3 */
#define IFX_CBS_TLTTH_TL3_OFF (6u)

/** \brief  Length for Ifx_CBS_TLTTH_Bits.TL4 */
#define IFX_CBS_TLTTH_TL4_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLTTH_Bits.TL4 */
#define IFX_CBS_TLTTH_TL4_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLTTH_Bits.TL4 */
#define IFX_CBS_TLTTH_TL4_OFF (8u)

/** \brief  Length for Ifx_CBS_TLTTH_Bits.TL5 */
#define IFX_CBS_TLTTH_TL5_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLTTH_Bits.TL5 */
#define IFX_CBS_TLTTH_TL5_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLTTH_Bits.TL5 */
#define IFX_CBS_TLTTH_TL5_OFF (10u)

/** \brief  Length for Ifx_CBS_TLTTH_Bits.TL6 */
#define IFX_CBS_TLTTH_TL6_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLTTH_Bits.TL6 */
#define IFX_CBS_TLTTH_TL6_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLTTH_Bits.TL6 */
#define IFX_CBS_TLTTH_TL6_OFF (12u)

/** \brief  Length for Ifx_CBS_TLTTH_Bits.TL7 */
#define IFX_CBS_TLTTH_TL7_LEN (2u)

/** \brief  Mask for Ifx_CBS_TLTTH_Bits.TL7 */
#define IFX_CBS_TLTTH_TL7_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TLTTH_Bits.TL7 */
#define IFX_CBS_TLTTH_TL7_OFF (14u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN0 */
#define IFX_CBS_TOPPS_PIN0_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN0 */
#define IFX_CBS_TOPPS_PIN0_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN0 */
#define IFX_CBS_TOPPS_PIN0_OFF (0u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN1 */
#define IFX_CBS_TOPPS_PIN1_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN1 */
#define IFX_CBS_TOPPS_PIN1_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN1 */
#define IFX_CBS_TOPPS_PIN1_OFF (2u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN2 */
#define IFX_CBS_TOPPS_PIN2_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN2 */
#define IFX_CBS_TOPPS_PIN2_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN2 */
#define IFX_CBS_TOPPS_PIN2_OFF (4u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN3 */
#define IFX_CBS_TOPPS_PIN3_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN3 */
#define IFX_CBS_TOPPS_PIN3_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN3 */
#define IFX_CBS_TOPPS_PIN3_OFF (6u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN4 */
#define IFX_CBS_TOPPS_PIN4_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN4 */
#define IFX_CBS_TOPPS_PIN4_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN4 */
#define IFX_CBS_TOPPS_PIN4_OFF (8u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN5 */
#define IFX_CBS_TOPPS_PIN5_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN5 */
#define IFX_CBS_TOPPS_PIN5_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN5 */
#define IFX_CBS_TOPPS_PIN5_OFF (10u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN6 */
#define IFX_CBS_TOPPS_PIN6_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN6 */
#define IFX_CBS_TOPPS_PIN6_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN6 */
#define IFX_CBS_TOPPS_PIN6_OFF (12u)

/** \brief  Length for Ifx_CBS_TOPPS_Bits.PIN7 */
#define IFX_CBS_TOPPS_PIN7_LEN (2u)

/** \brief  Mask for Ifx_CBS_TOPPS_Bits.PIN7 */
#define IFX_CBS_TOPPS_PIN7_MSK (0x3u)

/** \brief  Offset for Ifx_CBS_TOPPS_Bits.PIN7 */
#define IFX_CBS_TOPPS_PIN7_OFF (14u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN0 */
#define IFX_CBS_TOPR_PIN0_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN0 */
#define IFX_CBS_TOPR_PIN0_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN0 */
#define IFX_CBS_TOPR_PIN0_OFF (0u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN1 */
#define IFX_CBS_TOPR_PIN1_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN1 */
#define IFX_CBS_TOPR_PIN1_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN1 */
#define IFX_CBS_TOPR_PIN1_OFF (4u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN2 */
#define IFX_CBS_TOPR_PIN2_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN2 */
#define IFX_CBS_TOPR_PIN2_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN2 */
#define IFX_CBS_TOPR_PIN2_OFF (8u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN3 */
#define IFX_CBS_TOPR_PIN3_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN3 */
#define IFX_CBS_TOPR_PIN3_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN3 */
#define IFX_CBS_TOPR_PIN3_OFF (12u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN4 */
#define IFX_CBS_TOPR_PIN4_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN4 */
#define IFX_CBS_TOPR_PIN4_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN4 */
#define IFX_CBS_TOPR_PIN4_OFF (16u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN5 */
#define IFX_CBS_TOPR_PIN5_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN5 */
#define IFX_CBS_TOPR_PIN5_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN5 */
#define IFX_CBS_TOPR_PIN5_OFF (20u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN6 */
#define IFX_CBS_TOPR_PIN6_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN6 */
#define IFX_CBS_TOPR_PIN6_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN6 */
#define IFX_CBS_TOPR_PIN6_OFF (24u)

/** \brief  Length for Ifx_CBS_TOPR_Bits.PIN7 */
#define IFX_CBS_TOPR_PIN7_LEN (4u)

/** \brief  Mask for Ifx_CBS_TOPR_Bits.PIN7 */
#define IFX_CBS_TOPR_PIN7_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TOPR_Bits.PIN7 */
#define IFX_CBS_TOPR_PIN7_OFF (28u)

/** \brief  Length for Ifx_CBS_TRC_Bits.BRKIN */
#define IFX_CBS_TRC_BRKIN_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRC_Bits.BRKIN */
#define IFX_CBS_TRC_BRKIN_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRC_Bits.BRKIN */
#define IFX_CBS_TRC_BRKIN_OFF (20u)

/** \brief  Length for Ifx_CBS_TRC_Bits.BRKOUT */
#define IFX_CBS_TRC_BRKOUT_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRC_Bits.BRKOUT */
#define IFX_CBS_TRC_BRKOUT_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRC_Bits.BRKOUT */
#define IFX_CBS_TRC_BRKOUT_OFF (4u)

/** \brief  Length for Ifx_CBS_TRC_Bits.BT1 */
#define IFX_CBS_TRC_BT1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRC_Bits.BT1 */
#define IFX_CBS_TRC_BT1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRC_Bits.BT1 */
#define IFX_CBS_TRC_BT1_OFF (8u)

/** \brief  Length for Ifx_CBS_TRC_Bits.HALT */
#define IFX_CBS_TRC_HALT_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRC_Bits.HALT */
#define IFX_CBS_TRC_HALT_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRC_Bits.HALT */
#define IFX_CBS_TRC_HALT_OFF (0u)

/** \brief  Length for Ifx_CBS_TRC_Bits.SUSIN */
#define IFX_CBS_TRC_SUSIN_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRC_Bits.SUSIN */
#define IFX_CBS_TRC_SUSIN_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRC_Bits.SUSIN */
#define IFX_CBS_TRC_SUSIN_OFF (24u)

/** \brief  Length for Ifx_CBS_TREC_Bits.TR0EV */
#define IFX_CBS_TREC_TR0EV_LEN (4u)

/** \brief  Mask for Ifx_CBS_TREC_Bits.TR0EV */
#define IFX_CBS_TREC_TR0EV_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TREC_Bits.TR0EV */
#define IFX_CBS_TREC_TR0EV_OFF (0u)

/** \brief  Length for Ifx_CBS_TREC_Bits.TR2EV */
#define IFX_CBS_TREC_TR2EV_LEN (4u)

/** \brief  Mask for Ifx_CBS_TREC_Bits.TR2EV */
#define IFX_CBS_TREC_TR2EV_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TREC_Bits.TR2EV */
#define IFX_CBS_TREC_TR2EV_OFF (8u)

/** \brief  Length for Ifx_CBS_TREC_Bits.TR4EV */
#define IFX_CBS_TREC_TR4EV_LEN (4u)

/** \brief  Mask for Ifx_CBS_TREC_Bits.TR4EV */
#define IFX_CBS_TREC_TR4EV_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TREC_Bits.TR4EV */
#define IFX_CBS_TREC_TR4EV_OFF (16u)

/** \brief  Length for Ifx_CBS_TREC_Bits.TR6EV */
#define IFX_CBS_TREC_TR6EV_LEN (4u)

/** \brief  Mask for Ifx_CBS_TREC_Bits.TR6EV */
#define IFX_CBS_TREC_TR6EV_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TREC_Bits.TR6EV */
#define IFX_CBS_TREC_TR6EV_OFF (24u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_0 */
#define IFX_CBS_TRIG_TRGX_0_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_0 */
#define IFX_CBS_TRIG_TRGX_0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_0 */
#define IFX_CBS_TRIG_TRGX_0_OFF (0u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_10 */
#define IFX_CBS_TRIG_TRGX_10_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_10 */
#define IFX_CBS_TRIG_TRGX_10_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_10 */
#define IFX_CBS_TRIG_TRGX_10_OFF (10u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_11 */
#define IFX_CBS_TRIG_TRGX_11_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_11 */
#define IFX_CBS_TRIG_TRGX_11_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_11 */
#define IFX_CBS_TRIG_TRGX_11_OFF (11u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_12 */
#define IFX_CBS_TRIG_TRGX_12_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_12 */
#define IFX_CBS_TRIG_TRGX_12_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_12 */
#define IFX_CBS_TRIG_TRGX_12_OFF (12u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_13 */
#define IFX_CBS_TRIG_TRGX_13_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_13 */
#define IFX_CBS_TRIG_TRGX_13_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_13 */
#define IFX_CBS_TRIG_TRGX_13_OFF (13u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_14 */
#define IFX_CBS_TRIG_TRGX_14_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_14 */
#define IFX_CBS_TRIG_TRGX_14_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_14 */
#define IFX_CBS_TRIG_TRGX_14_OFF (14u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_15 */
#define IFX_CBS_TRIG_TRGX_15_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_15 */
#define IFX_CBS_TRIG_TRGX_15_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_15 */
#define IFX_CBS_TRIG_TRGX_15_OFF (15u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_16 */
#define IFX_CBS_TRIG_TRGX_16_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_16 */
#define IFX_CBS_TRIG_TRGX_16_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_16 */
#define IFX_CBS_TRIG_TRGX_16_OFF (16u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_17 */
#define IFX_CBS_TRIG_TRGX_17_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_17 */
#define IFX_CBS_TRIG_TRGX_17_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_17 */
#define IFX_CBS_TRIG_TRGX_17_OFF (17u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_18 */
#define IFX_CBS_TRIG_TRGX_18_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_18 */
#define IFX_CBS_TRIG_TRGX_18_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_18 */
#define IFX_CBS_TRIG_TRGX_18_OFF (18u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_19 */
#define IFX_CBS_TRIG_TRGX_19_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_19 */
#define IFX_CBS_TRIG_TRGX_19_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_19 */
#define IFX_CBS_TRIG_TRGX_19_OFF (19u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_1 */
#define IFX_CBS_TRIG_TRGX_1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_1 */
#define IFX_CBS_TRIG_TRGX_1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_1 */
#define IFX_CBS_TRIG_TRGX_1_OFF (1u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_20 */
#define IFX_CBS_TRIG_TRGX_20_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_20 */
#define IFX_CBS_TRIG_TRGX_20_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_20 */
#define IFX_CBS_TRIG_TRGX_20_OFF (20u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_21 */
#define IFX_CBS_TRIG_TRGX_21_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_21 */
#define IFX_CBS_TRIG_TRGX_21_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_21 */
#define IFX_CBS_TRIG_TRGX_21_OFF (21u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_22 */
#define IFX_CBS_TRIG_TRGX_22_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_22 */
#define IFX_CBS_TRIG_TRGX_22_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_22 */
#define IFX_CBS_TRIG_TRGX_22_OFF (22u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_23 */
#define IFX_CBS_TRIG_TRGX_23_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_23 */
#define IFX_CBS_TRIG_TRGX_23_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_23 */
#define IFX_CBS_TRIG_TRGX_23_OFF (23u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_2 */
#define IFX_CBS_TRIG_TRGX_2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_2 */
#define IFX_CBS_TRIG_TRGX_2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_2 */
#define IFX_CBS_TRIG_TRGX_2_OFF (2u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_3 */
#define IFX_CBS_TRIG_TRGX_3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_3 */
#define IFX_CBS_TRIG_TRGX_3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_3 */
#define IFX_CBS_TRIG_TRGX_3_OFF (3u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_4 */
#define IFX_CBS_TRIG_TRGX_4_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_4 */
#define IFX_CBS_TRIG_TRGX_4_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_4 */
#define IFX_CBS_TRIG_TRGX_4_OFF (4u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_5 */
#define IFX_CBS_TRIG_TRGX_5_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_5 */
#define IFX_CBS_TRIG_TRGX_5_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_5 */
#define IFX_CBS_TRIG_TRGX_5_OFF (5u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_6 */
#define IFX_CBS_TRIG_TRGX_6_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_6 */
#define IFX_CBS_TRIG_TRGX_6_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_6 */
#define IFX_CBS_TRIG_TRGX_6_OFF (6u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_7 */
#define IFX_CBS_TRIG_TRGX_7_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_7 */
#define IFX_CBS_TRIG_TRGX_7_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_7 */
#define IFX_CBS_TRIG_TRGX_7_OFF (7u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_8 */
#define IFX_CBS_TRIG_TRGX_8_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_8 */
#define IFX_CBS_TRIG_TRGX_8_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_8 */
#define IFX_CBS_TRIG_TRGX_8_OFF (8u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.TRGx_9 */
#define IFX_CBS_TRIG_TRGX_9_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.TRGx_9 */
#define IFX_CBS_TRIG_TRGX_9_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.TRGx_9 */
#define IFX_CBS_TRIG_TRGX_9_OFF (9u)

/** \brief  Length for Ifx_CBS_TRIG_Bits.x */
#define IFX_CBS_TRIG_X_LEN (8u)

/** \brief  Mask for Ifx_CBS_TRIG_Bits.x */
#define IFX_CBS_TRIG_X_MSK (0xffu)

/** \brief  Offset for Ifx_CBS_TRIG_Bits.x */
#define IFX_CBS_TRIG_X_OFF (24u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_0 */
#define IFX_CBS_TRIGC_TRGX_0_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_0 */
#define IFX_CBS_TRIGC_TRGX_0_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_0 */
#define IFX_CBS_TRIGC_TRGX_0_OFF (0u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_10 */
#define IFX_CBS_TRIGC_TRGX_10_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_10 */
#define IFX_CBS_TRIGC_TRGX_10_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_10 */
#define IFX_CBS_TRIGC_TRGX_10_OFF (10u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_11 */
#define IFX_CBS_TRIGC_TRGX_11_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_11 */
#define IFX_CBS_TRIGC_TRGX_11_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_11 */
#define IFX_CBS_TRIGC_TRGX_11_OFF (11u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_12 */
#define IFX_CBS_TRIGC_TRGX_12_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_12 */
#define IFX_CBS_TRIGC_TRGX_12_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_12 */
#define IFX_CBS_TRIGC_TRGX_12_OFF (12u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_13 */
#define IFX_CBS_TRIGC_TRGX_13_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_13 */
#define IFX_CBS_TRIGC_TRGX_13_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_13 */
#define IFX_CBS_TRIGC_TRGX_13_OFF (13u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_14 */
#define IFX_CBS_TRIGC_TRGX_14_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_14 */
#define IFX_CBS_TRIGC_TRGX_14_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_14 */
#define IFX_CBS_TRIGC_TRGX_14_OFF (14u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_15 */
#define IFX_CBS_TRIGC_TRGX_15_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_15 */
#define IFX_CBS_TRIGC_TRGX_15_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_15 */
#define IFX_CBS_TRIGC_TRGX_15_OFF (15u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_16 */
#define IFX_CBS_TRIGC_TRGX_16_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_16 */
#define IFX_CBS_TRIGC_TRGX_16_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_16 */
#define IFX_CBS_TRIGC_TRGX_16_OFF (16u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_17 */
#define IFX_CBS_TRIGC_TRGX_17_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_17 */
#define IFX_CBS_TRIGC_TRGX_17_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_17 */
#define IFX_CBS_TRIGC_TRGX_17_OFF (17u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_18 */
#define IFX_CBS_TRIGC_TRGX_18_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_18 */
#define IFX_CBS_TRIGC_TRGX_18_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_18 */
#define IFX_CBS_TRIGC_TRGX_18_OFF (18u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_19 */
#define IFX_CBS_TRIGC_TRGX_19_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_19 */
#define IFX_CBS_TRIGC_TRGX_19_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_19 */
#define IFX_CBS_TRIGC_TRGX_19_OFF (19u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_1 */
#define IFX_CBS_TRIGC_TRGX_1_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_1 */
#define IFX_CBS_TRIGC_TRGX_1_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_1 */
#define IFX_CBS_TRIGC_TRGX_1_OFF (1u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_20 */
#define IFX_CBS_TRIGC_TRGX_20_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_20 */
#define IFX_CBS_TRIGC_TRGX_20_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_20 */
#define IFX_CBS_TRIGC_TRGX_20_OFF (20u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_21 */
#define IFX_CBS_TRIGC_TRGX_21_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_21 */
#define IFX_CBS_TRIGC_TRGX_21_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_21 */
#define IFX_CBS_TRIGC_TRGX_21_OFF (21u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_22 */
#define IFX_CBS_TRIGC_TRGX_22_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_22 */
#define IFX_CBS_TRIGC_TRGX_22_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_22 */
#define IFX_CBS_TRIGC_TRGX_22_OFF (22u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_23 */
#define IFX_CBS_TRIGC_TRGX_23_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_23 */
#define IFX_CBS_TRIGC_TRGX_23_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_23 */
#define IFX_CBS_TRIGC_TRGX_23_OFF (23u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_2 */
#define IFX_CBS_TRIGC_TRGX_2_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_2 */
#define IFX_CBS_TRIGC_TRGX_2_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_2 */
#define IFX_CBS_TRIGC_TRGX_2_OFF (2u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_3 */
#define IFX_CBS_TRIGC_TRGX_3_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_3 */
#define IFX_CBS_TRIGC_TRGX_3_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_3 */
#define IFX_CBS_TRIGC_TRGX_3_OFF (3u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_4 */
#define IFX_CBS_TRIGC_TRGX_4_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_4 */
#define IFX_CBS_TRIGC_TRGX_4_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_4 */
#define IFX_CBS_TRIGC_TRGX_4_OFF (4u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_5 */
#define IFX_CBS_TRIGC_TRGX_5_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_5 */
#define IFX_CBS_TRIGC_TRGX_5_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_5 */
#define IFX_CBS_TRIGC_TRGX_5_OFF (5u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_6 */
#define IFX_CBS_TRIGC_TRGX_6_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_6 */
#define IFX_CBS_TRIGC_TRGX_6_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_6 */
#define IFX_CBS_TRIGC_TRGX_6_OFF (6u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_7 */
#define IFX_CBS_TRIGC_TRGX_7_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_7 */
#define IFX_CBS_TRIGC_TRGX_7_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_7 */
#define IFX_CBS_TRIGC_TRGX_7_OFF (7u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_8 */
#define IFX_CBS_TRIGC_TRGX_8_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_8 */
#define IFX_CBS_TRIGC_TRGX_8_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_8 */
#define IFX_CBS_TRIGC_TRGX_8_OFF (8u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.TRGx_9 */
#define IFX_CBS_TRIGC_TRGX_9_LEN (1u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.TRGx_9 */
#define IFX_CBS_TRIGC_TRGX_9_MSK (0x1u)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.TRGx_9 */
#define IFX_CBS_TRIGC_TRGX_9_OFF (9u)

/** \brief  Length for Ifx_CBS_TRIGC_Bits.x */
#define IFX_CBS_TRIGC_X_LEN (8u)

/** \brief  Mask for Ifx_CBS_TRIGC_Bits.x */
#define IFX_CBS_TRIGC_X_MSK (0xffu)

/** \brief  Offset for Ifx_CBS_TRIGC_Bits.x */
#define IFX_CBS_TRIGC_X_OFF (24u)

/** \brief  Length for Ifx_CBS_TRIGS_Bits.BITNUM */
#define IFX_CBS_TRIGS_BITNUM_LEN (13u)

/** \brief  Mask for Ifx_CBS_TRIGS_Bits.BITNUM */
#define IFX_CBS_TRIGS_BITNUM_MSK (0x1fffu)

/** \brief  Offset for Ifx_CBS_TRIGS_Bits.BITNUM */
#define IFX_CBS_TRIGS_BITNUM_OFF (0u)

/** \brief  Length for Ifx_CBS_TRMC_Bits.BRKIN */
#define IFX_CBS_TRMC_BRKIN_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRMC_Bits.BRKIN */
#define IFX_CBS_TRMC_BRKIN_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRMC_Bits.BRKIN */
#define IFX_CBS_TRMC_BRKIN_OFF (20u)

/** \brief  Length for Ifx_CBS_TRMC_Bits.BRKOUT */
#define IFX_CBS_TRMC_BRKOUT_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRMC_Bits.BRKOUT */
#define IFX_CBS_TRMC_BRKOUT_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRMC_Bits.BRKOUT */
#define IFX_CBS_TRMC_BRKOUT_OFF (4u)

/** \brief  Length for Ifx_CBS_TRMC_Bits.SUSOUT */
#define IFX_CBS_TRMC_SUSOUT_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRMC_Bits.SUSOUT */
#define IFX_CBS_TRMC_SUSOUT_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRMC_Bits.SUSOUT */
#define IFX_CBS_TRMC_SUSOUT_OFF (8u)

/** \brief  Length for Ifx_CBS_TRMT_Bits.TG0 */
#define IFX_CBS_TRMT_TG0_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRMT_Bits.TG0 */
#define IFX_CBS_TRMT_TG0_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRMT_Bits.TG0 */
#define IFX_CBS_TRMT_TG0_OFF (0u)

/** \brief  Length for Ifx_CBS_TRMT_Bits.TG1 */
#define IFX_CBS_TRMT_TG1_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRMT_Bits.TG1 */
#define IFX_CBS_TRMT_TG1_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRMT_Bits.TG1 */
#define IFX_CBS_TRMT_TG1_OFF (4u)

/** \brief  Length for Ifx_CBS_TRMT_Bits.TG2 */
#define IFX_CBS_TRMT_TG2_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRMT_Bits.TG2 */
#define IFX_CBS_TRMT_TG2_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRMT_Bits.TG2 */
#define IFX_CBS_TRMT_TG2_OFF (8u)

/** \brief  Length for Ifx_CBS_TRMT_Bits.TG3 */
#define IFX_CBS_TRMT_TG3_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRMT_Bits.TG3 */
#define IFX_CBS_TRMT_TG3_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRMT_Bits.TG3 */
#define IFX_CBS_TRMT_TG3_OFF (12u)

/** \brief  Length for Ifx_CBS_TRSS_Bits.SRC0 */
#define IFX_CBS_TRSS_SRC0_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRSS_Bits.SRC0 */
#define IFX_CBS_TRSS_SRC0_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRSS_Bits.SRC0 */
#define IFX_CBS_TRSS_SRC0_OFF (16u)

/** \brief  Length for Ifx_CBS_TRSS_Bits.SRC1 */
#define IFX_CBS_TRSS_SRC1_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRSS_Bits.SRC1 */
#define IFX_CBS_TRSS_SRC1_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRSS_Bits.SRC1 */
#define IFX_CBS_TRSS_SRC1_OFF (20u)

/** \brief  Length for Ifx_CBS_TRSS_Bits.TT */
#define IFX_CBS_TRSS_TT_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRSS_Bits.TT */
#define IFX_CBS_TRSS_TT_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRSS_Bits.TT */
#define IFX_CBS_TRSS_TT_OFF (0u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG10 */
#define IFX_CBS_TRTGB_H_TG10_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG10 */
#define IFX_CBS_TRTGB_H_TG10_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG10 */
#define IFX_CBS_TRTGB_H_TG10_OFF (8u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG11 */
#define IFX_CBS_TRTGB_H_TG11_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG11 */
#define IFX_CBS_TRTGB_H_TG11_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG11 */
#define IFX_CBS_TRTGB_H_TG11_OFF (12u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG12 */
#define IFX_CBS_TRTGB_H_TG12_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG12 */
#define IFX_CBS_TRTGB_H_TG12_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG12 */
#define IFX_CBS_TRTGB_H_TG12_OFF (16u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG13 */
#define IFX_CBS_TRTGB_H_TG13_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG13 */
#define IFX_CBS_TRTGB_H_TG13_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG13 */
#define IFX_CBS_TRTGB_H_TG13_OFF (20u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG14 */
#define IFX_CBS_TRTGB_H_TG14_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG14 */
#define IFX_CBS_TRTGB_H_TG14_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG14 */
#define IFX_CBS_TRTGB_H_TG14_OFF (24u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG15 */
#define IFX_CBS_TRTGB_H_TG15_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG15 */
#define IFX_CBS_TRTGB_H_TG15_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG15 */
#define IFX_CBS_TRTGB_H_TG15_OFF (28u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG8 */
#define IFX_CBS_TRTGB_H_TG8_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG8 */
#define IFX_CBS_TRTGB_H_TG8_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG8 */
#define IFX_CBS_TRTGB_H_TG8_OFF (0u)

/** \brief  Length for Ifx_CBS_TRTGB_H_Bits.TG9 */
#define IFX_CBS_TRTGB_H_TG9_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_H_Bits.TG9 */
#define IFX_CBS_TRTGB_H_TG9_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_H_Bits.TG9 */
#define IFX_CBS_TRTGB_H_TG9_OFF (4u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG0 */
#define IFX_CBS_TRTGB_L_TG0_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG0 */
#define IFX_CBS_TRTGB_L_TG0_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG0 */
#define IFX_CBS_TRTGB_L_TG0_OFF (0u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG1 */
#define IFX_CBS_TRTGB_L_TG1_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG1 */
#define IFX_CBS_TRTGB_L_TG1_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG1 */
#define IFX_CBS_TRTGB_L_TG1_OFF (4u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG2 */
#define IFX_CBS_TRTGB_L_TG2_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG2 */
#define IFX_CBS_TRTGB_L_TG2_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG2 */
#define IFX_CBS_TRTGB_L_TG2_OFF (8u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG3 */
#define IFX_CBS_TRTGB_L_TG3_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG3 */
#define IFX_CBS_TRTGB_L_TG3_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG3 */
#define IFX_CBS_TRTGB_L_TG3_OFF (12u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG4 */
#define IFX_CBS_TRTGB_L_TG4_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG4 */
#define IFX_CBS_TRTGB_L_TG4_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG4 */
#define IFX_CBS_TRTGB_L_TG4_OFF (16u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG5 */
#define IFX_CBS_TRTGB_L_TG5_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG5 */
#define IFX_CBS_TRTGB_L_TG5_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG5 */
#define IFX_CBS_TRTGB_L_TG5_OFF (20u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG6 */
#define IFX_CBS_TRTGB_L_TG6_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG6 */
#define IFX_CBS_TRTGB_L_TG6_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG6 */
#define IFX_CBS_TRTGB_L_TG6_OFF (24u)

/** \brief  Length for Ifx_CBS_TRTGB_L_Bits.TG7 */
#define IFX_CBS_TRTGB_L_TG7_LEN (4u)

/** \brief  Mask for Ifx_CBS_TRTGB_L_Bits.TG7 */
#define IFX_CBS_TRTGB_L_TG7_MSK (0xfu)

/** \brief  Offset for Ifx_CBS_TRTGB_L_Bits.TG7 */
#define IFX_CBS_TRTGB_L_TG7_OFF (28u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXCBS_BF_H */
