/* generated configuration header file - do not edit */
#ifndef BSP_MCU_OFS_CFG_H_
#define BSP_MCU_OFS_CFG_H_
#ifndef BSP_CFG_OPTION_SETTING_OFS0
#define OFS_IWDT (0xA001A001 | 1 << 1 | 3 << 2 | 15 << 4 | 3 << 8 | 3 << 10 | 1 << 12 | 1 << 14)
#define OFS_WDT  (1 << 17 | 3 << 18 | 15 << 20 | 3 << 24 | 3 << 26 | 1 << 28 | 1 << 30)
#define BSP_CFG_OPTION_SETTING_OFS0  (OFS_IWDT | OFS_WDT)
#endif
#ifndef BSP_CFG_OPTION_SETTING_OFS1
#ifndef BSP_CFG_OPTION_SETTING_OFS1_ICSATS
#define BSP_CFG_OPTION_SETTING_OFS1_ICSATS (1 << 31)
#endif
#define BSP_CFG_OPTION_SETTING_OFS1_NO_HOCOFRQ  (0x7FFF8EC3 | 1 <<2 | 3 << 3 | 1 << 8 | BSP_CFG_OPTION_SETTING_OFS1_ICSATS)

#define BSP_CFG_OPTION_SETTING_OFS1  ((uint32_t) BSP_CFG_OPTION_SETTING_OFS1_NO_HOCOFRQ | ((uint32_t) BSP_CFG_HOCO_FREQUENCY << BSP_FEATURE_BSP_OFS1_HOCOFRQ_OFFSET))
#endif
#endif /* BSP_MCU_OFS_CFG_H_ */
