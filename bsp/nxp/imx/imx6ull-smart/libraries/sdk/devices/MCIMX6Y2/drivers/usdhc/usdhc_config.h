/*
 * SD-Card board config
 *   SD-Card board config file
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-23     Lyons        first version
 */

#ifndef _BOARD_SDCARD_H_
#define _BOARD_SDCARD_H_

#define BOARD_SD_PIN_CONFIG(speed, strength)
#define BOARD_MMC_PIN_CONFIG(speed, strength)

#define BOARD_USDHC_SDCARD_POWER_CONTROL_INIT()
#define BOARD_USDHC_SDCARD_POWER_CONTROL(state)

#define BOARD_USDHC_MMCCARD_POWER_CONTROL_INIT()
#define BOARD_USDHC_MMCCARD_POWER_CONTROL(state)

/*
 * Insert detection is not used
 * Following setting no needed to care
 */
#define BOARD_USDHC_CD_STATUS() 0
#define BOARD_USDHC_CD_GPIO_INIT()
#define BOARD_USDHC_CD_INTERRUPT_STATUS() 0
#define BOARD_USDHC_CD_CLEAR_INTERRUPT(flag)

#define BOARD_USDHC_CD_GPIO_BASE GPIO1
#define BOARD_USDHC_CD_GPIO_PIN 19
#define BOARD_USDHC_CD_PORT_IRQ GPIO1_Combined_16_31_IRQn
#define BOARD_USDHC_CD_PORT_IRQ_HANDLER GPIO_IRQ_Handler

#define BOARD_USDHC1_CLK_FREQ (CLOCK_GetSysPfdFreq(kCLOCK_Pfd2) / (CLOCK_GetDiv(kCLOCK_Usdhc1Div) + 1U))
#define BOARD_USDHC2_CLK_FREQ (CLOCK_GetSysPfdFreq(kCLOCK_Pfd2) / (CLOCK_GetDiv(kCLOCK_Usdhc2Div) + 1U))

#define BOARD_SD_HOST_BASEADDR USDHC1_BASE
#define BOARD_SD_HOST_CLK_FREQ BOARD_USDHC1_CLK_FREQ
#define BOARD_SD_HOST_IRQ USDHC1_IRQn

#define BOARD_SD_SUPPORT_180V (0U)
#define BOARD_MMC_SUPPORT_8BIT_BUS (0U)

#define BOARD_SD_HOST_SUPPORT_SDR104_FREQ (130000000U)
#define BOARD_SD_HOST_SUPPORT_HS200_FREQ (150000000U)

#endif /* _BOARD_SDCARD_H_ */
