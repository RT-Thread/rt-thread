#include <stdint.h>
#include <stdio.h>

#include <hal_cmd.h>
#include <hal_timer.h>
#include <sunxi_hal_thermal.h>
#include <sunxi_hal_common.h>
#include <hal_log.h>

#if 0
#define THS_DBG(fmt,arg...)   printf("THS:" fmt, ##arg)
#else
#define THS_DBG(fmt,arg...)   do{}while(0)
#endif

extern int hal_efuse_get_thermal_cdata(unsigned char *buffer);

/* Temp Unit: millidegree Celsius */
static int hal_ths_reg2temp(int reg)
{
    THS_DBG("OFFSET:%d[0x%x], SCALE:%d[0x%x], reg:%d[0x%x]\n", OFFSET, OFFSET, SCALE, SCALE, reg, reg);

    return (reg + OFFSET) * SCALE;
}

static void hal_ths_calibrate(short int *buf, unsigned int len)
{
    unsigned int i;
    int ft_temp;

    if (!buf[0] || len < 2 + 2 * THS_NUM)
        return;

    ft_temp = buf[0] & FT_TEMP_MASK;

    for (i = 0; i < THS_NUM; i++) {
        int reg = (int)buf[i + 1];
        int sensor_temp = hal_ths_reg2temp(reg);
        int delta, cdata, calib_offest;

        /*
         * To calculate the calibration value:
         *
         * X(in Celsius) = Ts - ft_temp
         * delta = X * 10000 / TEMP_TO_REG
         * cdata = CALIBRATE_DEFAULT - delta
         *
         * cdata: calibration value
         */
        delta = (sensor_temp - ft_temp * 100) * 10 / TEMP_TO_REG;
        cdata = CALIBRATE_DEFAULT - delta;

        THS_DBG("sensor_temp:%d[0x%x], ft_temp:%d[0x%x], TEMP_TO_REG:%d[0x%x],"
               "delta:%d[0x%x], CALIBRATE_DEFAULT:%d[0x%x], cdata:%d[0x%x]\n",
               sensor_temp, sensor_temp, ft_temp, ft_temp, TEMP_TO_REG, TEMP_TO_REG,
               delta, delta, CALIBRATE_DEFAULT, CALIBRATE_DEFAULT, cdata, cdata);

        if (cdata & ~TEMP_CALIB_MASK) {
            /*
             * Calibration value more than 12-bit, but calibration
             * register is 12-bit. In this case, ths hardware can
             * still work without calibration, although the data
             * won't be so accurate.
             */
            continue;
        }

        calib_offest = THS_CALIB + (i / 2) * 0x4;

        THS_DBG("calib_offest:%d[0x%x], THS_CALIB:%d[0x%x]\n", calib_offest, calib_offest, THS_CALIB, THS_CALIB);

        if (i % 2) {
            hal_writel((hal_readl((unsigned long)THS_CALIB) & TEMP_CALIB_MASK) | (cdata << 16), (unsigned long)calib_offest);
        } else {
            hal_writel(cdata, (unsigned long)calib_offest);
        }
    }
}


int hal_ths_init(void)
{
    int ret = 0;
    char buffer[8] = {0};

    //TODO: clk init
    hal_writel(0x10001, (unsigned long)0x020019fc);

    /*
     * clkin = 24MHz
     * T acquire = clkin / (x + 1)
     *           = 20us
     */
    hal_log_err("0x%x, 0x%x, 0x%x, 0x%x", THS_EN, THS_CTL, THS_MFC, THS_PCTL);
    hal_writel(THS_CTRL_T_ACQ(479), (unsigned long)THS_CTL);
    /* average over 4 samples */
    hal_writel(THS_FILTER_EN | THS_FILTER_TYPE(1), (unsigned long)THS_MFC);
    /* period = (x + 1) * 4096 / clkin; ~10ms */
    hal_writel(THS_PC_TEMP_PERIOD(58), (unsigned long)THS_PCTL);
    /* enable sensor */
    hal_writel(THS_NUM, (unsigned long)THS_EN);

    ret = hal_efuse_get_thermal_cdata(buffer);
    if (ret < 0) {
        printf("get thermal calibration data failed.\n");
        return ret;
    }

    hal_ths_calibrate((short int *)buffer, 8);
    return ret ;

}

int hal_ths_uninit(void)
{
    hal_writel(0x0, (unsigned long)0x020019fc);

    return 0;
}

int hal_ths_get_temp(unsigned int num, int *temp)
{
    uint32_t val;

    val = hal_readl((unsigned long)THS_DATA + 0x4 * num);
    THS_DBG("num:%d[0x%x], val:%d[0x%x]\n", num, num, val, val);

    /* ths have no data yet */
    if (!val)
        return -1;

    *temp = hal_ths_reg2temp(val);

    return 0;
}


