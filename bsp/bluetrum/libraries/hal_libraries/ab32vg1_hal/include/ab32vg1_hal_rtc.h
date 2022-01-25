/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_RTC_H__
#define AB32VG1_HAL_RTC_H__

#define RTC_BASE    ((hal_sfr_t)&RTCCON)

enum
{
    RTCxCON,
    RTCxDAT,
    RTCxCPND = 3,
};

// RTCCON
#define RTC_CON_VUSB_OLINE                  (0x1u << 20)    /*!< VUSB online state                  */
#define RTC_CON_WK_PIN_STATE                (0x1u << 19)    /*!< RTC wakeup pin state               */
#define RTC_CON_1S_PEND                     (0x1u << 18)    /*!< RTC 1s pending                     */
#define RTC_CON_ALM_PEND                    (0x1u << 17)    /*!< RTC alarm pending                  */
#define RTC_CON_TRANS_DONE                  (0x1u << 16)    /*!< RTC trans done                     */
#define RTC_CON_ALM_WK_ENABLE               (0x1u <<  8)    /*!< RTC alarm wakeup enable            */
#define RTC_CON_1S_WK_ENABLE                (0x1u <<  7)    /*!< RTC 1s wakeup enable               */
#define RTC_CON_VUSB_RST_ENABLE             (0x1u <<  6)    /*!< VUSB insert reset system enable    */
#define RTC_CON_WK_RST_ENABLE               (0x1u <<  5)    /*!< RTC wakeup power down mode reset   \
                                                                                    system enable   */
#define RTC_CON_ALM_INTERRUPT               (0x1u <<  4)    /*!< RTC alarm interrupt enable         */
#define RTC_CON_1S_INTERRUPT                (0x1u <<  3)    /*!< RTC 1s interrupt enable            */
#define RTC_CON_BAUD_SELECT                 (0x3u <<  1)    /*!< Increase clock selection           */
#define RTC_CON_CHIP_SELECT                 (0x1u <<  0)    /*!< RTC chip select                    */

// RTCCPND
#define RTC_CPND_1S                         (0x1u <<  18)    /*!< Clear RTC 1S pending              */
#define RTC_CPND_ALM                        (0x1u <<  17)    /*!< Clear RTC alarm pendind           */

// RTCCON0
#define RTC_CON0_PWRUP_FIRST                (0x01u << 7)    /*!< RTC first power up flag            */
#define RTC_CON0_INTERNAL_32K               (0x01u << 6)    /*!< Internal 32K select                */
#define RTC_CON0_VDD_ENABLE                 (0x01u << 5)    /*!< RTC VDD12 enable                   */
#define RTC_CON0_BG_ENABLE                  (0x01u << 4)    /*!< BG enable                          */
#define RTC_CON0_LVD_OUTPUT_ENABLE          (0x01u << 3)    /*!< LVD output enable                  */
#define RTC_CON0_LVD_ENABLE                 (0x01u << 2)    /*!< LVD enbale                         */
#define RTC_CON0_XOSC32K_ENABLE             (0x01u << 1)    /*!< XOSC32K enable                     */
#define RTC_CON0_RCOSC_ENABLE               (0x01u << 0)    /*!< RCOSC enable                       */

// RTCCON2
#define RTC_CON2_32K_SELECT                 (0x01u << 7)    /*!< 32K osc select                     */

#endif
