#include "bl616_common.h"

enum pm_pds_sleep_level {
    PM_PDS_LEVEL_1 = 1,
    PM_PDS_LEVEL_2 = 2,
    PM_PDS_LEVEL_3 = 3,
    PM_PDS_LEVEL_7 = 7,
    PM_PDS_LEVEL_15 = 15,
};

enum pm_hbn_sleep_level {
    PM_HBN_LEVEL_0,
    PM_HBN_LEVEL_1,
    PM_HBN_LEVEL_2,
};

enum pm_event_type {
    PM_HBN_WAKEUP_EVENT_NONE,
    PM_HBN_GPIO16_WAKEUP_EVENT,
    PM_HBN_GPIO17_WAKEUP_EVENT,
    PM_HBN_GPIO18_WAKEUP_EVENT,
    PM_HBN_GPIO19_WAKEUP_EVENT,
    PM_HBN_RTC_WAKEUP_EVENT,
    PM_HBN_BOD_WAKEUP_EVENT,
    PM_HBN_ACOMP0_WAKEUP_EVENT,
    PM_HBN_ACOMP1_WAKEUP_EVENT,
};

void pm_pds_mask_all_wakeup_src(void);
BL_Err_Type pm_pds_wakeup_src_en(uint32_t WakeupType);
BL_Sts_Type pm_pds_get_wakeup_src(uint32_t WakeupType);
void pm_pds_mode_enter(enum pm_pds_sleep_level pds_level, uint32_t sleep_time);
void pm_hbn_mode_enter(enum pm_hbn_sleep_level hbn_level, uint64_t sleep_time);
void pm_set_wakeup_callback(void (*wakeup_callback)(void));
void pm_set_boot2_app_jump_para(uint32_t para);
void pm_hbn_out0_irq_register(void);
void pm_hbn_out1_irq_register(void);
void HBN_OUT0_IRQ(void);
void HBN_OUT1_IRQ(void);
void pm_irq_callback(enum pm_event_type event);
void pm_pds_irq_register(void);
void PDS_WAKEUP_IRQ(void);
void hal_pm_ldo11_use_ext_dcdc(void);
