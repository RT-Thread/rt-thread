#include <string.h>
#include "drv_es8336.h"
#include "fdebug.h"
#include "fdrivers_port.h"
#include "fparameters.h"
#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)
#include "fi2c.h"
#include "fi2c_hw.h"
#include "drv_i2c.h"
#endif
#if defined(PD2408_TEST_B_BOARD)
#include "fi2c_msg.h"
#include "fi2c_msg_hw.h"
#include "drv_i2c_msg.h"
#endif

#include "rtconfig.h"

#define ES_8336_ADDR             0x10

static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

static int i2c_ctrl_init()
{
    char name[RT_NAME_MAX];
#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)
    rt_strncpy(name, "MIO14", RT_NAME_MAX);
#endif
#if defined(PD2408_TEST_B_BOARD)
    rt_strncpy(name, "I2C3_MSG", RT_NAME_MAX);
#endif
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);
    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        rt_kprintf("find %s device!!!!\n", name);
    }

    return 0;
}

int _i2c_master_read_reg(u16 device_addr, int addr, int addr_len, void *data, int data_len)
{
    FError ret = FT_SUCCESS;
    u8 word_address = addr & 0xff;
    struct rt_i2c_msg msgs[2];
    msgs[0].addr = device_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = &word_address;
    msgs[0].len = 1;
    rt_i2c_transfer(i2c_bus, &msgs[0], 1);

    msgs[1].addr = device_addr;
    msgs[1].flags = FI2C_M_RD;
    msgs[1].buf = data;
    msgs[1].len = data_len;
    rt_i2c_transfer(i2c_bus, &msgs[1], 1);
    return ret;
}

int _i2c_master_write_reg(u16 device_addr, int addr, int addr_len, void *data, int data_len)
{
    FError ret = FT_SUCCESS;
    u8 write_buf[2];
    write_buf[0] = addr & 0xff;
    memcpy(write_buf + 1, data, data_len);

    struct rt_i2c_msg write_msgs;
    write_msgs.addr = device_addr;
    write_msgs.flags = RT_I2C_WR;
    write_msgs.buf = write_buf;
    write_msgs.len = data_len + 1;

    ret = rt_i2c_transfer(i2c_bus, &write_msgs, 1);
    return ret;
}

int es8336_write_reg(int reg, int value)
{
    return _i2c_master_write_reg(ES_8336_ADDR, reg, 1, &value, 1);
}

int es8336_read_reg(int reg, int *value)
{
    *value = 0;
    return _i2c_master_read_reg(ES_8336_ADDR, reg, 1, value, 1);
}

int es8336_set_voice_mute(boolean enable)
{
    int res = 0;
    int reg = 0;
    res = es8336_read_reg(ES8336_DAC_SET1_REG30, &reg);
    reg = reg & 0xFB;
    res |= es8336_write_reg(ES8336_DAC_SET1_REG30, reg | (((int) enable) << 2));
    return res;
}

int es8336_start(codec_dec_work_mode_t mode)
{
    int res = 0;
    es8336_write_reg(ES8336_RESET_REG00, 0xC0);
    es8336_write_reg(ES8336_SYS_PDN_REG0D, 0x00);
    es8336_write_reg(ES8336_SDP_ADCFMT_REG0A, 0x0C);
    es8336_write_reg(ES8336_SDP_DACFMT_REG0B, 0x0C);
    es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01, 0x7F);
    if (mode == CODEC_DEV_WORK_MODE_DAC) {
        es8336_write_reg(ES8336_SYS_LP1_REG0E, 0x3F);
        es8336_write_reg(ES8336_SYS_LP2_REG0F, 0x1F);
        es8336_write_reg(ES8336_HPMIX_SWITCH_REG14, 0x88);
        es8336_write_reg(ES8336_HPMIX_PDN_REG15, 0x00);
        es8336_write_reg(ES8336_HPMIX_VOL_REG16, 0x00);
        es8336_write_reg(ES8336_CPHP_PDN2_REG1A, 0x10);
        es8336_write_reg(ES8336_CPHP_LDOCTL_REG1B, 0x30);
        es8336_write_reg(ES8336_CPHP_PDN1_REG19, 0x02);
        es8336_write_reg(ES8336_DAC_PDN_REG2F, 0x00);
        es8336_write_reg(ES8336_CPHP_OUTEN_REG17, 0x66);
        es8336_write_reg(ES8336_RESET_REG00, 0xc0);
        es8336_write_reg(ES8336_DAC_VOLL_REG33, 0x0);
        es8336_write_reg(ES8336_DAC_VOLR_REG34, 0x28);
        es8336_write_reg(ES8336_DAC_SET1_REG30, 0x00);/*the connect of Lin,Lout,Rin,Rout*/
        es8336_write_reg(ES8336_DAC_VOLL_REG33, 0x0);/*digital volume control*/
        es8336_write_reg(ES8336_DAC_VOLR_REG34, 0x28);
        es8336_write_reg(ES8336_DAC_VOLL_REG33, 0x1);
        es8336_write_reg(ES8336_DAC_VOLR_REG34, 0x1);
        es8336_write_reg(ES8336_ADC_VOLUME_REG27, 0x1);
        es8336_write_reg(ES8336_ADC_VOLUME_REG28, 0x1);

    } else if(mode == CODEC_DEV_WORK_MODE_ADC) {
        es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01,
                    ES8336_CLKMGR_ADC_MCLK_EN |
                    ES8336_CLKMGR_ADC_ANALOG_EN);
    }
    else if(mode == CODEC_DEV_WORK_MODE_BOTH) {
        es8336_write_reg(ES8336_RESET_REG00, 0xC0);
        es8336_write_reg(ES8336_SYS_PDN_REG0D, 0x00);
        es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01, 0x7F); /*set the clock*/
        es8336_write_reg(ES8336_SYS_LP1_REG0E, 0x3F); /*low power mode of ADC*/
        es8336_write_reg(ES8336_SYS_LP2_REG0F, 0x1F); /*low power mode of output*/
        es8336_write_reg(ES8336_HPMIX_SWITCH_REG14, 0x88); /*headphone mixer*/
        es8336_write_reg(ES8336_HPMIX_PDN_REG15, 0x00);
        es8336_write_reg(ES8336_HPMIX_VOL_REG16, 0x00); /*the gain of headphone mixer*/
        es8336_write_reg(ES8336_CPHP_PDN2_REG1A, 0x10); /*Power down charge pump circuits*/
        es8336_write_reg(ES8336_CPHP_LDOCTL_REG1B, 0x30); /*set the voltage*/
        es8336_write_reg(ES8336_CPHP_PDN1_REG19, 0x02);
        es8336_write_reg(ES8336_DAC_PDN_REG2F, 0x00);
        es8336_write_reg(ES8336_CPHP_OUTEN_REG17, 0x66);
        es8336_write_reg(ES8336_RESET_REG00, 0xc0);
        es8336_write_reg(ES8336_DAC_VOLL_REG33, 0x0);
        es8336_write_reg(ES8336_DAC_VOLR_REG34, 0x28);
    }
#if defined SOC_TARGET_PD2408
    es8336_write_reg(ES8336_ADC_PDN_LINSEL_REG22, 0x20); /*select the output and input source */
#elif defined SOC_TARGET_PE220X
    es8336_write_reg(ES8336_ADC_PDN_LINSEL_REG22, 0x30); /*select the output and input source*/
#endif
    return res;
}

int es8336_stop(codec_dec_work_mode_t mode)
{
    int res = 0;
    if (mode == CODEC_DEV_WORK_MODE_DAC) {
        es8336_write_reg(ES8336_CPHP_OUTEN_REG17, 0x00);
        es8336_write_reg(ES8336_DAC_PDN_REG2F, 0x11);
        es8336_write_reg(ES8336_CPHP_LDOCTL_REG1B, 0x03);
        es8336_write_reg(ES8336_CPHP_PDN2_REG1A, 0x22);
        es8336_write_reg(ES8336_CPHP_PDN1_REG19, 0x06);
        es8336_write_reg(ES8336_HPMIX_SWITCH_REG14, 0x00);
        es8336_write_reg(ES8336_HPMIX_PDN_REG15, 0x33);
        es8336_write_reg(ES8336_HPMIX_VOL_REG16, 0x00);
        es8336_write_reg(ES8336_SYS_PDN_REG0D, 0x00);
        es8336_write_reg(ES8336_SYS_LP1_REG0E, 0xFF);
        es8336_write_reg(ES8336_SYS_LP2_REG0F, 0xFF);
        es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01,0x7F);
    }
    if (mode == CODEC_DEV_WORK_MODE_ADC) {
        res |= es8336_write_reg(ES8336_ADC_PDN_LINSEL_REG22, 0xC0); /* power down adc and line in*/
        res |= es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01,
                    ES8336_CLKMGR_ADC_MCLK_EN |
                    ES8336_CLKMGR_ADC_ANALOG_DIS);
    }
    if (mode == CODEC_DEV_WORK_MODE_BOTH) {
        es8336_write_reg(ES8336_SYS_PDN_REG0D, 0x3F);
        res |= es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01, 0xF3); /* disable mclk */
    }
    return res;
}

int es8336_config_fmt(codec_dec_work_mode_t mode, i2s_fmt_t fmt)
{
    int res = 0;
    int reg = 0;
    if (mode & CODEC_DEV_WORK_MODE_ADC) {
        res |= es8336_write_reg(ES8336_SDP_ADCFMT_REG0A, reg | (fmt << 1));
    }
    if (mode & CODEC_DEV_WORK_MODE_DAC) {
        res |= es8336_write_reg(ES8336_SDP_DACFMT_REG0B, reg | (fmt << 1));
    }
    return res;
}

int es8336_set_mic_gain(float db)
{
    int gain = db > 0 ? (int) (db / 3) : 0;
    gain = (gain << 4) + gain;
    return es8336_write_reg(ES8336_ADC_PGAGAIN_REG23, gain); /* MIC PGA*/
}

int es8336_set_bits_per_sample(codec_dec_work_mode_t mode)
{
    int res = 0;
    int reg = 0;
    if (mode & CODEC_DEV_WORK_MODE_ADC) {
        res = es8336_read_reg(ES8336_SDP_ADCFMT_REG0A, &reg);
        res |= es8336_write_reg(ES8336_SDP_ADCFMT_REG0A, reg | (0x3 << 2));
    }
    if (mode & CODEC_DEV_WORK_MODE_DAC) {
        res = es8336_read_reg(ES8336_SDP_ADCFMT_REG0A, &reg);
        res |= es8336_write_reg(ES8336_SDP_DACFMT_REG0B, reg | (0x3 << 2));
    }
    return res;
}

int es8336_open()
{
    i2c_ctrl_init();
    int value = 0;
    value = es8336_read_reg(ES8336_RESET_REG00, &value);
    es8336_write_reg(ES8336_RESET_REG00, 0x3f);
    FDriverUdelay(100); /*ensure reset success*/
    es8336_write_reg(ES8336_RESET_REG00, 0x03);
    es8336_write_reg(ES8336_RESET_REG00, 0x3f);
    FDriverUdelay(500); /*ensure reset success*/
    es8336_write_reg(ES8336_RESET_REG00, 0x00);
    es8336_write_reg(ES8336_SYS_VMIDSEL_REG0C, 0xFF); /*vmisel config */
    FDriverUdelay(30);
    es8336_write_reg(ES8336_CLKMGR_CLKSEL_REG02, 0x08);
    es8336_write_reg(ES8336_CLKMGR_ADCOSR_REG03, 0x20);
    es8336_write_reg(ES8336_CLKMGR_ADCDIV1_REG04, 0x11);
    es8336_write_reg(ES8336_CLKMGR_ADCDIV2_REG05, 0x00);
    es8336_write_reg(ES8336_CLKMGR_DACDIV1_REG06, 0x11);
    es8336_write_reg(ES8336_CLKMGR_DACDIV2_REG07, 0x00);
    es8336_write_reg(ES8336_CLKMGR_CPDIV_REG08, 0x00);
    es8336_write_reg(ES8336_SDP_MS_BCKDIV_REG09, 0x04);
    es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01, 0x7F);
    es8336_write_reg(ES8336_CAL_TYPE_REG1C, 0x0F);
    es8336_write_reg(ES8336_CAL_HPLIV_REG1E, 0x90);
    es8336_write_reg(ES8336_CAL_HPRIV_REG1F, 0x90);
    es8336_write_reg(ES8336_ADC_VOLUME_REG27, 0x00);
    es8336_write_reg(ES8336_ADC_PDN_LINSEL_REG22, 0xc0);
    es8336_write_reg(ES8336_ADC_D2SEPGA_REG24, 0x00);
    es8336_write_reg(ES8336_ADC_DMIC_REG25, 0x08);
    es8336_write_reg(ES8336_DAC_SET1_REG30, 0x00);
    es8336_write_reg(ES8336_DAC_SET2_REG31, 0x20);
    es8336_write_reg(ES8336_DAC_SET3_REG32, 0x00);
    es8336_write_reg(ES8336_DAC_VOLL_REG33, 0x00);
    es8336_write_reg(ES8336_DAC_VOLR_REG34, 0x00);
    es8336_write_reg(ES8336_SDP_ADCFMT_REG0A, 0x00);
    es8336_write_reg(ES8336_SDP_DACFMT_REG0B, 0x00);
    es8336_write_reg(ES8336_SYS_VMIDLOW_REG10, 0x11);
    es8336_write_reg(ES8336_SYS_VSEL_REG11, 0xFC);
    es8336_write_reg(ES8336_SYS_REF_REG12, 0x28);
    es8336_write_reg(ES8336_SYS_LP1_REG0E, 0x04);
    es8336_write_reg(ES8336_SYS_LP2_REG0F, 0x0C);
    es8336_write_reg(ES8336_DAC_PDN_REG2F, 0x11);
    es8336_write_reg(ES8336_HPMIX_SEL_REG13, 0x00);
    es8336_write_reg(ES8336_HPMIX_SWITCH_REG14, 0x88);
    es8336_write_reg(ES8336_HPMIX_PDN_REG15, 0x00);
    es8336_write_reg(ES8336_HPMIX_VOL_REG16, 0xBB);
    es8336_write_reg(ES8336_CPHP_PDN2_REG1A, 0x10);
    es8336_write_reg(ES8336_CPHP_LDOCTL_REG1B, 0x30);
    es8336_write_reg(ES8336_CPHP_PDN1_REG19, 0x02);
    es8336_write_reg(ES8336_CPHP_ICAL_VOL_REG18, 0x00);
    es8336_write_reg(ES8336_GPIO_SEL_REG4D, 0x02);
    es8336_write_reg(ES8336_GPIO_DEBUNCE_INT_REG4E, 0x02);
    es8336_write_reg(ES8336_TESTMODE_REG50, 0xA0);
    es8336_write_reg(ES8336_TEST1_REG51, 0x00);
    es8336_write_reg(ES8336_TEST2_REG52, 0x00);
    es8336_write_reg(ES8336_SYS_PDN_REG0D, 0x00);
    es8336_write_reg(ES8336_RESET_REG00, 0xC0);
    FDriverUdelay(50);
    es8336_write_reg(ES8336_ADC_PGAGAIN_REG23, 0x60);
    es8336_write_reg(ES8336_ADC_D2SEPGA_REG24, 0x01);
    /* adc ds mode, HPF enable */
    es8336_write_reg(ES8336_ADC_DMIC_REG25, 0x08);
    es8336_write_reg(ES8336_ADC_ALC1_REG29, 0xcd);
    es8336_write_reg(ES8336_ADC_ALC2_REG2A, 0x08);
    es8336_write_reg(ES8336_ADC_ALC3_REG2B, 0xa0);
    es8336_write_reg(ES8336_ADC_ALC4_REG2C, 0x05);
    es8336_write_reg(ES8336_ADC_ALC5_REG2D, 0x06);
    es8336_write_reg(ES8336_ADC_ALC6_REG2E, 0x61);

    es8336_write_reg(ES8336_GPIO_SEL_REG4D, 0x02);
    /* max debance time, enable interrupt, low active */
    es8336_write_reg(ES8336_GPIO_DEBUNCE_INT_REG4E, 0xF3);
    es8336_write_reg(ES8336_CPHP_OUTEN_REG17, 0x00);
    es8336_write_reg(ES8336_DAC_PDN_REG2F, 0x11);
    es8336_write_reg(ES8336_CPHP_LDOCTL_REG1B, 0x03);
    es8336_write_reg(ES8336_CPHP_PDN2_REG1A, 0x22);
    es8336_write_reg(ES8336_CPHP_PDN1_REG19, 0x06);
    es8336_write_reg(ES8336_HPMIX_SWITCH_REG14, 0x00);
    es8336_write_reg(ES8336_HPMIX_PDN_REG15, 0x33);
    es8336_write_reg(ES8336_HPMIX_VOL_REG16, 0x00);
    es8336_write_reg(ES8336_SYS_LP1_REG0E, 0xFF);
    es8336_write_reg(ES8336_SYS_LP2_REG0F, 0xFF);
    es8336_write_reg(ES8336_CLKMGR_CLKSW_REG01, 0xF3);
    es8336_write_reg(ES8336_ADC_PDN_LINSEL_REG22, 0xD0);

    return 0;
}

int  es8336_test()
{
    es8336_open();
    es8336_start(CODEC_DEV_WORK_MODE_BOTH);

    return 0;
}

INIT_COMPONENT_EXPORT(es8336_test);