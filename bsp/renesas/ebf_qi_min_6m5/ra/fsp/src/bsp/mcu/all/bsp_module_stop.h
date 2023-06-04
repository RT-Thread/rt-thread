/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_MODULE_H
#define BSP_MODULE_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#if __has_include("internal/bsp_module_stop_internal.h")
 #include "internal/bsp_module_stop_internal.h"
#endif

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

#if BSP_FEATURE_TZ_HAS_TRUSTZONE

/* MSTPCRA is located in R_MSTP for Star devices. */
 #define R_BSP_MSTPCRA    (R_MSTP->MSTPCRA)
#else

/* MSTPCRA is located in R_SYSTEM for W1D and Peaks devices. */
 #define R_BSP_MSTPCRA    (R_SYSTEM->MSTPCRA)
#endif

/*******************************************************************************************************************//**
 * Cancels the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_START(ip, channel)         {FSP_CRITICAL_SECTION_DEFINE;                                   \
                                                 FSP_CRITICAL_SECTION_ENTER;                                    \
                                                 BSP_MSTP_REG_ ## ip(channel) &= ~BSP_MSTP_BIT_ ## ip(channel); \
                                                 FSP_REGISTER_READ(BSP_MSTP_REG_ ## ip(channel));               \
                                                 FSP_CRITICAL_SECTION_EXIT;}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_STOP(ip, channel)          {FSP_CRITICAL_SECTION_DEFINE;                                  \
                                                 FSP_CRITICAL_SECTION_ENTER;                                   \
                                                 BSP_MSTP_REG_ ## ip(channel) |= BSP_MSTP_BIT_ ## ip(channel); \
                                                 FSP_REGISTER_READ(BSP_MSTP_REG_ ## ip(channel));              \
                                                 FSP_CRITICAL_SECTION_EXIT;}

/** @} (end addtogroup BSP_MCU) */

#if 0U == BSP_FEATURE_BSP_MSTP_HAS_MSTPCRE
 #define BSP_MSTP_REG_FSP_IP_GPT(channel)       R_MSTP->MSTPCRD
 #define BSP_MSTP_BIT_FSP_IP_GPT(channel)       ((BSP_FEATURE_BSP_MSTP_GPT_MSTPD5_MAX_CH >= \
                                                  channel) ? (1U << 5U) : (1U << 6U));

 #ifndef BSP_MSTP_REG_FSP_IP_AGT
  #define BSP_MSTP_REG_FSP_IP_AGT(channel)      R_MSTP->MSTPCRD
 #endif
 #ifndef BSP_MSTP_BIT_FSP_IP_AGT
  #define BSP_MSTP_BIT_FSP_IP_AGT(channel)      (1U << (3U - channel));
 #endif

 #define BSP_MSTP_REG_FSP_IP_POEG(channel)      R_MSTP->MSTPCRD
 #define BSP_MSTP_BIT_FSP_IP_POEG(channel)      (1U << (14U));
#else
 #if (2U == BSP_FEATURE_ELC_VERSION)
  #if BSP_MCU_GROUP_RA6T2
   #define BSP_MSTP_REG_FSP_IP_GPT(channel)     R_MSTP->MSTPCRE
   #define BSP_MSTP_BIT_FSP_IP_GPT(channel)     (1U << 31);
   #define BSP_MSTP_REG_FSP_IP_AGT(channel)     R_MSTP->MSTPCRD
   #define BSP_MSTP_BIT_FSP_IP_AGT(channel)     (1U << (3U - channel));
  #else
   #define BSP_MSTP_REG_FSP_IP_GPT(channel)     R_MSTP->MSTPCRE
   #define BSP_MSTP_BIT_FSP_IP_GPT(channel)     (1U << (31 - channel));
   #define BSP_MSTP_REG_FSP_IP_AGT(channel)     R_MSTP->MSTPCRD
   #define BSP_MSTP_BIT_FSP_IP_AGT(channel)     (1U << (5U - channel));
  #endif
  #define BSP_MSTP_REG_FSP_IP_KEY(channel)      R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_KEY(channel)      (1U << 4U);
  #define BSP_MSTP_REG_FSP_IP_POEG(channel)     R_MSTP->MSTPCRD
  #define BSP_MSTP_BIT_FSP_IP_POEG(channel)     (1U << (14U - channel));
  #define BSP_MSTP_REG_FSP_IP_ULPT(channel)     R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_ULPT(channel)     (1U << (9U - channel));
 #else
  #define BSP_MSTP_REG_FSP_IP_GPT(channel)      R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_GPT(channel)      (1U << (31 - channel));
  #define BSP_MSTP_REG_FSP_IP_AGT(channel)      *((3U >= channel) ? &R_MSTP->MSTPCRD : &R_MSTP->MSTPCRE)
  #define BSP_MSTP_BIT_FSP_IP_AGT(channel)      ((3U >= \
                                                  channel) ? (1U << (3U - channel)) : (1U << (15U - (channel - 4U))));
  #define BSP_MSTP_REG_FSP_IP_KEY(channel)      R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_KEY(channel)      (1U << (4U - channel));
  #define BSP_MSTP_REG_FSP_IP_POEG(channel)     R_MSTP->MSTPCRD
  #define BSP_MSTP_BIT_FSP_IP_POEG(channel)     (1U << (14U - channel));
 #endif
#endif

#define BSP_MSTP_REG_FSP_IP_DMAC(channel)       R_BSP_MSTPCRA
#define BSP_MSTP_BIT_FSP_IP_DMAC(channel)       (1U << (22U));
#define BSP_MSTP_REG_FSP_IP_DTC(channel)        R_BSP_MSTPCRA
#define BSP_MSTP_BIT_FSP_IP_DTC(channel)        (1U << (22U));
#define BSP_MSTP_REG_FSP_IP_CAN(channel)        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_CAN(channel)        (1U << (2U - channel));
#define BSP_MSTP_REG_FSP_IP_CEC(channel)        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_CEC(channel)        (1U << (3U));
#define BSP_MSTP_REG_FSP_IP_I3C(channel)        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_I3C(channel)        (1U << (BSP_FEATURE_I3C_MSTP_OFFSET - channel));
#define BSP_MSTP_REG_FSP_IP_IRDA(channel)       R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_IRDA(channel)       (1U << (5U - channel));
#define BSP_MSTP_REG_FSP_IP_QSPI(channel)       R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_QSPI(channel)       (1U << (6U - channel));
#define BSP_MSTP_REG_FSP_IP_IIC(channel)        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_IIC(channel)        (1U << (9U - channel));
#define BSP_MSTP_REG_FSP_IP_USBFS(channel)      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_USBFS(channel)      (1U << (11U - channel));
#define BSP_MSTP_REG_FSP_IP_USBHS(channel)      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_USBHS(channel)      (1U << (12U - channel));
#define BSP_MSTP_REG_FSP_IP_EPTPC(channel)      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_EPTPC(channel)      (1U << (13U - channel));
#define BSP_MSTP_REG_FSP_IP_ETHER(channel)      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_ETHER(channel)      (1U << (15U - channel));
#define BSP_MSTP_REG_FSP_IP_OSPI(channel)       R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_OSPI(channel)       (1U << (16U - channel));
#define BSP_MSTP_REG_FSP_IP_SPI(channel)        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_SPI(channel)        (1U << (19U - channel));
#define BSP_MSTP_REG_FSP_IP_SCI(channel)        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_SCI(channel)        (1U << (31U - channel));
#define BSP_MSTP_REG_FSP_IP_CAC(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CAC(channel)        (1U << (0U - channel));
#define BSP_MSTP_REG_FSP_IP_CRC(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CRC(channel)        (1U << (1U - channel));
#define BSP_MSTP_REG_FSP_IP_PDC(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_PDC(channel)        (1U << (2U - channel));
#define BSP_MSTP_REG_FSP_IP_CTSU(channel)       R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CTSU(channel)       (1U << (3U - channel));
#define BSP_MSTP_REG_FSP_IP_SLCDC(channel)      R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SLCDC(channel)      (1U << (4U - channel));
#define BSP_MSTP_REG_FSP_IP_GLCDC(channel)      R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_GLCDC(channel)      (1U << (4U - channel));
#define BSP_MSTP_REG_FSP_IP_JPEG(channel)       R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_JPEG(channel)       (1U << (5U - channel));
#define BSP_MSTP_REG_FSP_IP_DRW(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_DRW(channel)        (1U << (6U - channel));
#define BSP_MSTP_REG_FSP_IP_SSI(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SSI(channel)        (1U << (8U - channel));
#define BSP_MSTP_REG_FSP_IP_SRC(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SRC(channel)        (1U << (9U - channel));
#define BSP_MSTP_REG_FSP_IP_SDHIMMC(channel)    R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SDHIMMC(channel)    (1U << (12U - channel));
#define BSP_MSTP_REG_FSP_IP_DOC(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_DOC(channel)        (1U << (13U - channel));
#define BSP_MSTP_REG_FSP_IP_ELC(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_ELC(channel)        (1U << (14U - channel));
#define BSP_MSTP_REG_FSP_IP_CEU(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CEU(channel)        (1U << (16U - channel));
#define BSP_MSTP_REG_FSP_IP_TFU(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_TFU(channel)        (1U << (20U - channel));
#define BSP_MSTP_REG_FSP_IP_IIRFA(channel)      R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_IIRFA(channel)      (1U << (21U - channel));
#define BSP_MSTP_REG_FSP_IP_CANFD(channel)      R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CANFD(channel)      (1U << (27U - channel));
#define BSP_MSTP_REG_FSP_IP_TRNG(channel)       R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_TRNG(channel)       (1U << (28U - channel));
#define BSP_MSTP_REG_FSP_IP_SCE(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SCE(channel)        (1U << (31U - channel));
#define BSP_MSTP_REG_FSP_IP_AES(channel)        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_AES(channel)        (1U << (31U - channel));
#define BSP_MSTP_REG_FSP_IP_ADC(channel)        R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ADC(channel)        (1U << (16U - channel));
#define BSP_MSTP_REG_FSP_IP_SDADC(channel)      R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_SDADC(channel)      (1U << (17U - channel));
#if (BSP_FEATURE_DAC_MAX_CHANNELS > 2U)
 #define BSP_MSTP_REG_FSP_IP_DAC(channel)       R_MSTP->MSTPCRD
 #define BSP_MSTP_BIT_FSP_IP_DAC(channel)       (1U << (20U - channel));
#else
 #define BSP_MSTP_REG_FSP_IP_DAC8(channel)      R_MSTP->MSTPCRD
 #define BSP_MSTP_BIT_FSP_IP_DAC8(channel)      (1U << (19U));
 #define BSP_MSTP_REG_FSP_IP_DAC(channel)       R_MSTP->MSTPCRD
 #define BSP_MSTP_BIT_FSP_IP_DAC(channel)       (1U << (20U));
#endif
#define BSP_MSTP_REG_FSP_IP_TSN(channel)        R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_TSN(channel)        (1U << (22U - channel));
#define BSP_MSTP_REG_FSP_IP_ACMPHS(channel)     R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ACMPHS(channel)     (1U << (28U - channel));
#define BSP_MSTP_REG_FSP_IP_ACMPLP(channel)     R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ACMPLP(channel)     (1U << 29U);
#define BSP_MSTP_REG_FSP_IP_OPAMP(channel)      R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_OPAMP(channel)      (1U << (31U - channel));

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
