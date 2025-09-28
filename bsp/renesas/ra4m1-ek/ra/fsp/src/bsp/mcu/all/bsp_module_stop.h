/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_MODULE_H
#define BSP_MODULE_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

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
#if BSP_CFG_MSTP_CHANGE_DELAY_ENABLE
 #define R_BSP_MODULE_START(ip, channel)    {FSP_CRITICAL_SECTION_DEFINE;                                   \
                                             FSP_CRITICAL_SECTION_ENTER;                                    \
                                             BSP_MSTP_REG_ ## ip(channel) &= ~BSP_MSTP_BIT_ ## ip(channel); \
                                             FSP_REGISTER_READ(BSP_MSTP_REG_ ## ip(channel));               \
                                             R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US,           \
                                                                 BSP_DELAY_UNITS_MICROSECONDS);             \
                                             FSP_CRITICAL_SECTION_EXIT;}
#else
 #define R_BSP_MODULE_START(ip, channel)    {FSP_CRITICAL_SECTION_DEFINE;                                           \
                                             FSP_CRITICAL_SECTION_ENTER;                                            \
                                             BSP_MSTP_REG_ ## ip(channel) &=                                        \
                                                 (BSP_MSTP_REG_TYPE_ ## ip(channel)) ~BSP_MSTP_BIT_ ## ip(channel); \
                                             FSP_REGISTER_READ(BSP_MSTP_REG_ ## ip(channel));                       \
                                             FSP_CRITICAL_SECTION_EXIT;}
#endif

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#if BSP_CFG_MSTP_CHANGE_DELAY_ENABLE
 #define R_BSP_MODULE_STOP(ip, channel)     {FSP_CRITICAL_SECTION_DEFINE;                                  \
                                             FSP_CRITICAL_SECTION_ENTER;                                   \
                                             BSP_MSTP_REG_ ## ip(channel) |= BSP_MSTP_BIT_ ## ip(channel); \
                                             FSP_REGISTER_READ(BSP_MSTP_REG_ ## ip(channel));              \
                                             R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US,          \
                                                                 BSP_DELAY_UNITS_MICROSECONDS);            \
                                             FSP_CRITICAL_SECTION_EXIT;}
#else
 #define R_BSP_MODULE_STOP(ip, channel)     {FSP_CRITICAL_SECTION_DEFINE;                                  \
                                             FSP_CRITICAL_SECTION_ENTER;                                   \
                                             BSP_MSTP_REG_ ## ip(channel) |= BSP_MSTP_BIT_ ## ip(channel); \
                                             FSP_REGISTER_READ(BSP_MSTP_REG_ ## ip(channel));              \
                                             FSP_CRITICAL_SECTION_EXIT;}
#endif

/** @} (end addtogroup BSP_MCU) */

#if 0U == BSP_FEATURE_BSP_MSTP_HAS_MSTPCRE
 #define BSP_MSTP_REG_FSP_IP_GPT(channel)               R_MSTP->MSTPCRD
 #if !BSP_FEATURE_BSP_MSTP_GPT_MSTPD5
  #define BSP_MSTP_BIT_FSP_IP_GPT(channel)              (1U << 6U)
 #else
  #define BSP_MSTP_BIT_FSP_IP_GPT(channel)              ((BSP_FEATURE_BSP_MSTP_GPT_MSTPD5_MAX_CH >= \
                                                          channel) ? (1U << 5U) : (1U << 6U));
 #endif
 #define BSP_MSTP_REG_TYPE_FSP_IP_GPT(channel)          uint32_t
 #define BSP_MSTP_REG_FSP_IP_GPT_PDG(channel)           R_MSTP->MSTPCRD
 #define BSP_MSTP_BIT_FSP_IP_GPT_PDG(channel)           (1U << (31U));
 #define BSP_MSTP_REG_TYPE_FSP_IP_GPT_PDG(channel)      uint32_t

 #define BSP_MSTP_REG_FSP_IP_AGT(channel)               R_MSTP->MSTPCRD

 #if BSP_MCU_GROUP_RA2A2

/* RA2A2 has a combination of AGT and AGTW.
 * Ch 0-1: MSTPD[ 3: 2] (AGTW0, AGTW1)
 * Ch 2-3: MSTPD[19:18] (AGT0, AGT1)
 * Ch 4-5: MSTPD[ 1: 0] (AGT2, AGT3)
 * Ch 6-9: MSTPD[10: 7] (AGT4, AGT5, AGT6, AGT7)
 */
  #define BSP_MSTP_BIT_FSP_IP_AGT(channel)              (1U <<                                                         \
                                                         ((channel < BSP_FEATURE_AGT_AGTW_CHANNEL_COUNT)               \
                                                          ? (3U - channel)                                             \
                                                          : ((channel < BSP_FEATURE_AGT_AGTW_CHANNEL_COUNT + 2U)       \
                                                             ? (19U - channel + BSP_FEATURE_AGT_AGTW_CHANNEL_COUNT)    \
                                                             : ((channel < BSP_FEATURE_AGT_AGTW_CHANNEL_COUNT + 4U)    \
                                                                ? (1U - channel + BSP_FEATURE_AGT_AGTW_CHANNEL_COUNT + \
                                                                   2U)                                                 \
                                                                : (10U - channel +                                     \
                                                                   BSP_FEATURE_AGT_AGTW_CHANNEL_COUNT +                \
                                                                   4U)))));

 #else
  #define BSP_MSTP_BIT_FSP_IP_AGT(channel)              (1U << (3U - channel));
 #endif
 #define BSP_MSTP_REG_TYPE_FSP_IP_AGT(channel)          uint32_t

 #define BSP_MSTP_REG_FSP_IP_POEG(channel)              R_MSTP->MSTPCRD
 #if BSP_FEATURE_BSP_MSTP_POEG_MSTPD13
  #define BSP_MSTP_BIT_FSP_IP_POEG(channel)             (1U << (14U - channel));
 #else
  #define BSP_MSTP_BIT_FSP_IP_POEG(channel)             (1U << (14U));
 #endif
 #define BSP_MSTP_REG_TYPE_FSP_IP_POEG(channel)         uint32_t
#else
 #if (2U == BSP_FEATURE_ELC_VERSION)
  #if BSP_MCU_GROUP_RA6T2
   #define BSP_MSTP_REG_FSP_IP_GPT(channel)             R_MSTP->MSTPCRE
   #define BSP_MSTP_BIT_FSP_IP_GPT(channel)             (1U << 31);
   #define BSP_MSTP_REG_TYPE_FSP_IP_GPT(channel)        uint32_t
   #define BSP_MSTP_REG_FSP_IP_GPT_PDG(channel)         R_MSTP->MSTPCRE
   #define BSP_MSTP_BIT_FSP_IP_GPT_PDG(channel)         (1U << (31U));
   #define BSP_MSTP_REG_TYPE_FSP_IP_GPT_PDG(channel)    uint32_t
   #define BSP_MSTP_REG_FSP_IP_AGT(channel)             R_MSTP->MSTPCRD
   #define BSP_MSTP_BIT_FSP_IP_AGT(channel)             (1U << (3U - channel));
   #define BSP_MSTP_REG_TYPE_FSP_IP_AGT(channel)        uint32_t
  #elif BSP_MCU_GROUP_RA8_GEN2
   #define BSP_MSTP_REG_FSP_IP_GPT(channel)             R_MSTP->MSTPCRE
   #define BSP_MSTP_BIT_FSP_IP_GPT(channel)             (1U << \
                                                         (31 - ((channel >= 4U && channel <= 9U) ? 4U : channel))) // GPT Channels 4-9 share stop bits on this MCU
   #define BSP_MSTP_REG_TYPE_FSP_IP_GPT(channel)        uint32_t
   #define BSP_MSTP_REG_FSP_IP_GPT_PDG(channel)         R_MSTP->MSTPCRD
   #define BSP_MSTP_BIT_FSP_IP_GPT_PDG(channel)         (1U << (6U));
   #define BSP_MSTP_REG_TYPE_FSP_IP_GPT_PDG(channel)    uint32_t
   #define BSP_MSTP_REG_FSP_IP_AGT(channel)             R_MSTP->MSTPCRD
   #define BSP_MSTP_BIT_FSP_IP_AGT(channel)             (1U << (5U - channel));
   #define BSP_MSTP_REG_TYPE_FSP_IP_AGT(channel)        uint32_t
  #else
   #define BSP_MSTP_REG_FSP_IP_GPT(channel)             R_MSTP->MSTPCRE
   #define BSP_MSTP_BIT_FSP_IP_GPT(channel)             (1U << (31 - channel));
   #define BSP_MSTP_REG_TYPE_FSP_IP_GPT(channel)        uint32_t
   #define BSP_MSTP_REG_FSP_IP_GPT_PDG(channel)         R_MSTP->MSTPCRE
   #define BSP_MSTP_BIT_FSP_IP_GPT_PDG(channel)         (1U << (31U));
   #define BSP_MSTP_REG_TYPE_FSP_IP_GPT_PDG(channel)    uint32_t
   #define BSP_MSTP_REG_FSP_IP_AGT(channel)             R_MSTP->MSTPCRD
   #define BSP_MSTP_BIT_FSP_IP_AGT(channel)             (1U << (5U - channel));
   #define BSP_MSTP_REG_TYPE_FSP_IP_AGT(channel)        uint32_t
  #endif
  #define BSP_MSTP_REG_FSP_IP_KEY(channel)              R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_KEY(channel)              (1U << 4U);
  #define BSP_MSTP_REG_TYPE_FSP_IP_KEY(channel)         uint32_t
  #define BSP_MSTP_REG_FSP_IP_POEG(channel)             R_MSTP->MSTPCRD
  #define BSP_MSTP_BIT_FSP_IP_POEG(channel)             (1U << (14U - channel));
  #define BSP_MSTP_REG_TYPE_FSP_IP_POEG(channel)        uint32_t
  #define BSP_MSTP_REG_FSP_IP_ULPT(channel)             R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_ULPT(channel)             (1U << (9U - channel));
  #define BSP_MSTP_REG_TYPE_FSP_IP_ULPT(channel)        uint32_t
 #else
  #define BSP_MSTP_REG_FSP_IP_GPT(channel)              R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_GPT(channel)              (1U << (31 - channel));
  #define BSP_MSTP_REG_TYPE_FSP_IP_GPT(channel)         uint32_t
  #define BSP_MSTP_REG_FSP_IP_GPT_PDG(channel)          R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_GPT_PDG(channel)          (1U << (31U));
  #define BSP_MSTP_REG_TYPE_FSP_IP_GPT_PDG(channel)     uint32_t
  #define BSP_MSTP_REG_FSP_IP_AGT(channel)              *((3U >= channel) ? &R_MSTP->MSTPCRD : &R_MSTP->MSTPCRE)
  #define BSP_MSTP_BIT_FSP_IP_AGT(channel)              ((3U >=                                       \
                                                          channel) ? (1U << (3U - channel)) : (1U <<  \
                                                                                               (15U - \
                                                                                                (channel - 4U))));
  #define BSP_MSTP_REG_TYPE_FSP_IP_AGT(channel)         uint32_t
  #define BSP_MSTP_REG_FSP_IP_KEY(channel)              R_MSTP->MSTPCRE
  #define BSP_MSTP_BIT_FSP_IP_KEY(channel)              (1U << (4U - channel));
  #define BSP_MSTP_REG_TYPE_FSP_IP_KEY(channel)         uint32_t
  #define BSP_MSTP_REG_FSP_IP_POEG(channel)             R_MSTP->MSTPCRD
  #define BSP_MSTP_BIT_FSP_IP_POEG(channel)             (1U << (14U - channel));
  #define BSP_MSTP_REG_TYPE_FSP_IP_POEG(channel)        uint32_t
 #endif
#endif

#define BSP_MSTP_REG_FSP_IP_NPU(channel)                R_BSP_MSTPCRA
#define BSP_MSTP_BIT_FSP_IP_NPU(channel)                (1U << (16U));

#define BSP_MSTP_REG_FSP_IP_DMAC(channel)               R_BSP_MSTPCRA
#if BSP_MCU_GROUP_RA8_GEN2 && (1U == BSP_CFG_CPU_CORE)
 #define BSP_MSTP_BIT_FSP_IP_DMAC(channel)              (1U << (23U));
#else
 #define BSP_MSTP_BIT_FSP_IP_DMAC(channel)              (1U << (22U));
#endif

#define BSP_MSTP_REG_TYPE_FSP_IP_DMAC(channel)          uint32_t

#if BSP_FEATURE_CGC_REGISTER_SET_B
 #define BSP_MSTP_REG_FSP_IP_DTC(channel)               R_BSP_MSTPCRA
 #define BSP_MSTP_BIT_FSP_IP_DTC(channel)               (1U << (6U))
 #define BSP_MSTP_REG_TYPE_FSP_IP_DTC(channel)          uint16_t
#else
 #define BSP_MSTP_REG_FSP_IP_DTC(channel)               R_BSP_MSTPCRA
 #define BSP_MSTP_BIT_FSP_IP_DTC(channel)               (1U << (22U));
 #define BSP_MSTP_REG_TYPE_FSP_IP_DTC(channel)          uint32_t
#endif
#define BSP_MSTP_REG_FSP_IP_CAN(channel)                R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_CAN(channel)                (1U << (2U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_CAN(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_CEC(channel)                R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_CEC(channel)                (1U << (3U));
#define BSP_MSTP_REG_TYPE_FSP_IP_CEC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_I3C(channel)                R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_I3C(channel)                (1U << (BSP_FEATURE_I3C_MSTP_OFFSET - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_I3C(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_IRDA(channel)               R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_IRDA(channel)               (1U << (5U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_IRDA(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_QSPI(channel)               R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_QSPI(channel)               (1U << (6U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_QSPI(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_SAU(channel)                R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_SAU(channel)                (1U << (6U + channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SAU(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_IIC(channel)                R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_IIC(channel)                (1U << (9U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_IIC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_IICA(channel)               R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_IICA(channel)               (1U << (10U + channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_IICA(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_USBFS(channel)              R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_USBFS(channel)              (1U << (11U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_USBFS(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_USBHS(channel)              R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_USBHS(channel)              (1U << (12U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_USBHS(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_EPTPC(channel)              R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_EPTPC(channel)              (1U << (13U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_EPTPC(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_USBCC(channel)              R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_USBCC(channel)              (1U << (14U));
#define BSP_MSTP_REG_TYPE_FSP_IP_USBCC(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_ETHER(channel)              R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_ETHER(channel)              (1U << (15U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_ETHER(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_UARTA(channel)              R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_UARTA(channel)              (1U << BSP_FEATURE_UARTA_MSTP_OFFSET);
#define BSP_MSTP_REG_TYPE_FSP_IP_UARTA(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_OSPI(channel)               R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_OSPI(channel)               (1U << (16U + channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_OSPI(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_SPI(channel)                R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_SPI(channel)                (1U << (19U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SPI(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_SCI(channel)                R_MSTP->MSTPCRB
#define BSP_MSTP_REG_TYPE_FSP_IP_SCI(channel)           uint32_t
#define BSP_MSTP_BIT_FSP_IP_SCI(channel)                (1U << (31U - channel));
#define BSP_MSTP_REG_FSP_IP_CAC(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_REG_TYPE_FSP_IP_CAC(channel)           uint32_t
#define BSP_MSTP_BIT_FSP_IP_CAC(channel)                (1U << (0U - channel));
#define BSP_MSTP_REG_FSP_IP_CRC(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_REG_TYPE_FSP_IP_CRC(channel)           uint32_t
#define BSP_MSTP_BIT_FSP_IP_CRC(channel)                (1U << (1U - channel));
#define BSP_MSTP_REG_FSP_IP_PDC(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_PDC(channel)                (1U << (2U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_PDC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_CTSU(channel)               R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CTSU(channel)               (1U << (3U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_CTSU(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_SLCDC(channel)              R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SLCDC(channel)              (1U << (4U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SLCDC(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_GLCDC(channel)              R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_GLCDC(channel)              (1U << (4U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_GLCDC(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_JPEG(channel)               R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_JPEG(channel)               (1U << (5U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_JPEG(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_DRW(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_DRW(channel)                (1U << (6U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_DRW(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_SSI(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SSI(channel)                (1U << (8U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SSI(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_SRC(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SRC(channel)                (1U << (9U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SRC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_MIPI_DSI(channel)           R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_MIPI_DSI(channel)           (1U << (10U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_MIPI_DSI(channel)      uint32_t
#define BSP_MSTP_REG_FSP_IP_SDHIMMC(channel)            R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SDHIMMC(channel)            (1U << (12U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SDHIMMC(channel)       uint32_t
#define BSP_MSTP_REG_FSP_IP_DOC(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_DOC(channel)                (1U << (13U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_DOC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_ELC(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_ELC(channel)                (1U << (14U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_ELC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_MACL(channel)               R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_MACL(channel)               (1U << (15U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_MACL(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_CEU(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_REG_TYPE_FSP_IP_CEU(channel)           uint32_t
#define BSP_MSTP_BIT_FSP_IP_CEU(channel)                (1U << (16U - channel));
#define BSP_MSTP_REG_FSP_IP_MIPI_CSI(channel)           R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_MIPI_CSI(channel)           (1U << (17U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_MIPI_CSI(channel)      uint32_t
#define BSP_MSTP_REG_FSP_IP_TFU(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_TFU(channel)                (1U << (20U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_TFU(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_IIRFA(channel)              R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_IIRFA(channel)              (1U << (21U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_IIRFA(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_PDM(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_PDM(channel)                (1U << (24U));
#define BSP_MSTP_REG_TYPE_FSP_IP_PDM(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_CANFD(channel)              R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CANFD(channel)              (1U << (27U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_CANFD(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_TRNG(channel)               R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_TRNG(channel)               (1U << (28U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_TRNG(channel)          uint32_t
#define BSP_MSTP_REG_FSP_IP_SCE(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SCE(channel)                (1U << (31U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SCE(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_AES(channel)                R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_AES(channel)                (1U << (31U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_AES(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_TAU(channel)                R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_TAU(channel)                (1U << (0U));
#define BSP_MSTP_REG_TYPE_FSP_IP_TAU(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_TML(channel)                R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_TML(channel)                (1U << (4U));
#define BSP_MSTP_REG_TYPE_FSP_IP_TML(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_ADC(channel)                R_MSTP->MSTPCRD
#if BSP_MCU_GROUP_RA8_GEN2
 #define BSP_MSTP_BIT_FSP_IP_ADC(channel)               (1U << (21U - channel));
#else
 #define BSP_MSTP_BIT_FSP_IP_ADC(channel)               (1U << (16U - channel));
#endif
#define BSP_MSTP_REG_TYPE_FSP_IP_ADC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_SDADC(channel)              R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_SDADC(channel)              (1U << (17U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_SDADC(channel)         uint32_t
#define BSP_MSTP_REG_FSP_IP_DAC(channel)                R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_DAC(channel)                (1U << (20U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_DAC(channel)           uint32_t
#if (BSP_PERIPHERAL_DAC8_PRESENT)
 #define BSP_MSTP_REG_FSP_IP_DAC8(channel)              R_MSTP->MSTPCRD
 #define BSP_MSTP_BIT_FSP_IP_DAC8(channel)              (1U << (19U));
 #define BSP_MSTP_REG_TYPE_FSP_IP_DAC8(channel)         uint32_t
#endif
#define BSP_MSTP_REG_FSP_IP_TSN(channel)                R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_TSN(channel)                (1U << (22U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_TSN(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_RTC(channel)                R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_RTC(channel)                (1U << (23U));
#define BSP_MSTP_REG_TYPE_FSP_IP_RTC(channel)           uint32_t
#define BSP_MSTP_REG_FSP_IP_ACMPHS(channel)             R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ACMPHS(channel)             (1U << (28U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_ACMPHS(channel)        uint32_t
#define BSP_MSTP_REG_FSP_IP_ACMPLP(channel)             R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ACMPLP(channel)             (1U << 29U);
#define BSP_MSTP_REG_TYPE_FSP_IP_ACMPLP(channel)        uint32_t
#define BSP_MSTP_REG_FSP_IP_OPAMP(channel)              R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_OPAMP(channel)              (1U << (31U - channel));
#define BSP_MSTP_REG_TYPE_FSP_IP_OPAMP(channel)         uint32_t
#if (1U == BSP_FEATURE_CGC_HAS_OSTDCSE)
 #define BSP_MSTP_REG_FSP_IP_SOSTD(channel)             R_BSP_MSTPCRA
 #define BSP_MSTP_BIT_FSP_IP_SOSTD(channel)             (1U << (16U));
 #define BSP_MSTP_REG_TYPE_FSP_IP_SOSTD(channel)        uint32_t
 #define BSP_MSTP_REG_FSP_IP_MOSTD(channel)             R_BSP_MSTPCRA
 #define BSP_MSTP_BIT_FSP_IP_MOSTD(channel)             (1U << (17U));
 #define BSP_MSTP_REG_TYPE_FSP_IP_MOSTD(channel)        uint32_t
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
