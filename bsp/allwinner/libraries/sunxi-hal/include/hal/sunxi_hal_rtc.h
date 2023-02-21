#ifndef _SUNXI_HAL_RTC_H
#define _SUNXI_HAL_RTC_H

#include <sunxi_hal_common.h>
#include <rtc/rtc.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <rtc/platform_rtc.h>

/*
 * Time unit conversions
 */
#define SEC_IN_MIN              60
#define SEC_IN_HOUR             (60 * SEC_IN_MIN)
#define SEC_IN_DAY              (24 * SEC_IN_HOUR)

/*
 * The year parameter passed to the driver is usually an offset relative to
 * the year 1900. This macro is used to convert this offset to another one
 * relative to the minimum year allowed by the hardware.
 */
#define SUNXI_YEAR_OFF(x)           ((x)->min - 1900)

#define EFEX_FLAG  (0x5AA5A55A)
#define RTC_FEL_INDEX  2
#define RTC_BOOT_INDEX 6
#define RTC_LOG_LEVEL_INDEX 5

/* debug */
#define SUNXI_DEBUG_MODE_FLAG           (0x59)
/* efex */
#define SUNXI_EFEX_CMD_FLAG             (0x5A)
/* boot-resignature */
#define SUNXI_BOOT_RESIGNATURE_FLAG     (0x5B)
/* recovery or boot-recovery */
#define SUNXI_BOOT_RECOVERY_FLAG        (0x5C)
/* sysrecovery */
#define SUNXI_SYS_RECOVERY_FLAG         (0x5D)
/* usb-recovery*/
#define SUNXI_USB_RECOVERY_FLAG         (0x5E)
/* bootloader */
#define SUNXI_FASTBOOT_FLAG             (0x5F)
/* uboot */
#define SUNXI_UBOOT_FLAG                (0x60)

#define SUNXI_MASK_DH               0x0000001f
#define SUNXI_MASK_SM               0x0000003f
#define SUNXI_MASK_M                0x0000000f
#define SUNXI_MASK_LY               0x00000001
#define SUNXI_MASK_D                0x00000ffe

#define SUNXI_GET(x, mask, shift)       (((x) & ((mask) << (shift))) \
        >> (shift))

#define SUNXI_SET(x, mask, shift)       (((x) & (mask)) << (shift))

/*
 * Get date values
 */
#define SUNXI_DATE_GET_DAY_VALUE(x)     SUNXI_GET(x, SUNXI_MASK_DH, 0)
#define SUNXI_DATE_GET_MON_VALUE(x)     SUNXI_GET(x, SUNXI_MASK_M, 8)
#define SUNXI_DATE_GET_YEAR_VALUE(x, d) SUNXI_GET(x, (d)->mask, (d)->yshift)

/*
 * Get time values
 */
#define SUNXI_TIME_GET_SEC_VALUE(x)     SUNXI_GET(x, SUNXI_MASK_SM, 0)
#define SUNXI_TIME_GET_MIN_VALUE(x)     SUNXI_GET(x, SUNXI_MASK_SM, 8)
#define SUNXI_TIME_GET_HOUR_VALUE(x)    SUNXI_GET(x, SUNXI_MASK_DH, 16)

/*
 * Get alarm values
 */
#define SUNXI_ALRM_GET_SEC_VALUE(x)     SUNXI_GET(x, SUNXI_MASK_SM, 0)
#define SUNXI_ALRM_GET_MIN_VALUE(x)     SUNXI_GET(x, SUNXI_MASK_SM, 8)
#define SUNXI_ALRM_GET_HOUR_VALUE(x)    SUNXI_GET(x, SUNXI_MASK_DH, 16)

/*
 * Set date values
 */
#define SUNXI_DATE_SET_DAY_VALUE(x)     SUNXI_DATE_GET_DAY_VALUE(x)
#define SUNXI_DATE_SET_MON_VALUE(x)     SUNXI_SET(x, SUNXI_MASK_M, 8)
#define SUNXI_DATE_SET_YEAR_VALUE(x, d) SUNXI_SET(x, (d)->mask, (d)->yshift)
#define SUNXI_LEAP_SET_VALUE(x, shift)  SUNXI_SET(x, SUNXI_MASK_LY, shift)

/*
 * Set time values
 */
#define SUNXI_TIME_SET_SEC_VALUE(x)     SUNXI_TIME_GET_SEC_VALUE(x)
#define SUNXI_TIME_SET_MIN_VALUE(x)     SUNXI_SET(x, SUNXI_MASK_SM, 8)
#define SUNXI_TIME_SET_HOUR_VALUE(x)    SUNXI_SET(x, SUNXI_MASK_DH, 16)

/*
 * Set alarm values
 */
#define SUNXI_ALRM_SET_SEC_VALUE(x)     SUNXI_ALRM_GET_SEC_VALUE(x)
#define SUNXI_ALRM_SET_MIN_VALUE(x)     SUNXI_SET(x, SUNXI_MASK_SM, 8)
#define SUNXI_ALRM_SET_HOUR_VALUE(x)    SUNXI_SET(x, SUNXI_MASK_DH, 16)
#define SUNXI_ALRM_SET_DAY_VALUE(x)     SUNXI_SET(x, SUNXI_MASK_D, 21)

typedef int (*rtc_callback_t)(void);
/*
 * min and max year are arbitrary set considering the limited range of the
 * hardware register field
 */
struct hal_rtc_data_year
{
    unsigned int min;       /* min year allowed */
    unsigned int max;       /* max year allowed */
    unsigned int mask;      /* mask for the year field */
    unsigned int yshift;        /* bit shift to get the year */
    unsigned char leap_shift;   /* bit shift to get the leap year */
};

struct hal_rtc_dev
{
    struct hal_rtc_data_year *data_year;
    rtc_callback_t user_callback;
    unsigned long base;
    int irq;
    hal_clk_t bus_clk;
    hal_clk_t rtc1k_clk;
    hal_clk_t rtcspi_clk;
    struct reset_control *reset;

};

typedef enum
{
    RTC_GET_TIME = 0,
    RTC_SET_TIME = 1,
    RTC_GET_ALARM = 2,
    RTC_SET_ALARM = 3,
    RTC_CALLBACK = 4,
    RTC_IRQENABLE = 5
} hal_rtc_transfer_cmd_t;

void hal_rtc_set_fel_flag(void);
u32  hal_rtc_probe_fel_flag(void);
void hal_rtc_clear_fel_flag(void);
int hal_rtc_get_bootmode_flag(void);
int hal_rtc_set_bootmode_flag(u8 flag);
void hal_rtc_write_data(int index, u32 val);
u32  hal_rtc_read_data(int index);
int hal_rtc_gettime(struct rtc_time *rtc_tm);
int hal_rtc_settime(struct rtc_time *rtc_tm);
int hal_rtc_getalarm(struct rtc_wkalrm *wkalrm);
int hal_rtc_setalarm(struct rtc_wkalrm *wkalrm);
int hal_rtc_alarm_irq_enable(unsigned int enabled);
void hal_rtc_min_year_show(unsigned int *min);
void hal_rtc_max_year_show(unsigned int *max);
int hal_rtc_register_callback(rtc_callback_t user_callback);
int hal_rtc_init(void);
int hal_rtc_deinit(void);

#endif /* _SUNXI_HAL_RTC_H */
