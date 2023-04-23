#include "bflb_rtc.h"
#include "hardware/rtc_reg.h"

#if defined(BL602) || defined(BL702) || defined(BL702L)
#define BFLB_RTC_BASE 0x4000F000
#elif defined(BL808) || defined(BL606P) || defined(BL616)
#define BFLB_RTC_BASE 0x2000F000
#elif defined(BL628)
#define BFLB_RTC_BASE 0x2008F000
#endif

void bflb_rtc_disable(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = BFLB_RTC_BASE;

    /* Clear & Disable RTC counter */
    regval = getreg32(reg_base + HBN_CTL_OFFSET);
    regval &=~ HBN_RTC_ENABLE;
    putreg32(regval, reg_base + HBN_CTL_OFFSET);
}

void bflb_rtc_set_time(struct bflb_device_s *dev, uint64_t time)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t rtc_cnt;

    reg_base = BFLB_RTC_BASE;

    /* Clear RTC Control */
    regval = getreg32(reg_base + HBN_CTL_OFFSET);
    regval &= ~HBN_RTC_CTL_MASK;
    putreg32(regval, reg_base + HBN_CTL_OFFSET);

    regval |= HBN_RTC_DLY_OPTION;
    regval |= HBN_RTC_BIT39_0_COMPARE;
    putreg32(regval, reg_base + HBN_CTL_OFFSET);

    /* Tigger RTC val read */
    regval = getreg32(reg_base + HBN_RTC_TIME_H_OFFSET);
    regval |= HBN_RTC_TIME_LATCH;
    putreg32(regval, reg_base + HBN_RTC_TIME_H_OFFSET);
    regval &= ~HBN_RTC_TIME_LATCH;
    putreg32(regval, reg_base + HBN_RTC_TIME_H_OFFSET);

    /* Read RTC val */
    rtc_cnt = getreg32(reg_base + HBN_RTC_TIME_H_OFFSET) & 0xff;
    rtc_cnt <<= 32;
    rtc_cnt |= getreg32(reg_base + HBN_RTC_TIME_L_OFFSET);

    /* calculate RTC Comp time */
    rtc_cnt += time;

    /* Set RTC Comp time  */
    putreg32((uint32_t)rtc_cnt, reg_base + HBN_TIME_L_OFFSET);
    putreg32((uint32_t)(rtc_cnt >> 32) & 0xff, reg_base + HBN_TIME_H_OFFSET);

    /* Enable RTC Counter */
    regval = getreg32(reg_base + HBN_CTL_OFFSET);
    regval |= HBN_RTC_ENABLE;
    putreg32(regval, reg_base + HBN_CTL_OFFSET);
}

uint64_t bflb_rtc_get_time(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t time_l;
    uint64_t time_h;

    reg_base = BFLB_RTC_BASE;

    /* Tigger RTC val read */
    regval = getreg32(reg_base + HBN_RTC_TIME_H_OFFSET);
    regval |= HBN_RTC_TIME_LATCH;
    putreg32(regval, reg_base + HBN_RTC_TIME_H_OFFSET);
    regval &= ~HBN_RTC_TIME_LATCH;
    putreg32(regval, reg_base + HBN_RTC_TIME_H_OFFSET);

    /* Read RTC val */
    time_l = getreg32(reg_base + HBN_RTC_TIME_L_OFFSET);
    time_h = getreg32(reg_base + HBN_RTC_TIME_H_OFFSET) & 0xff;

    return (((uint64_t)time_h << 32) | (uint64_t)time_l);
}