

#include <rtthread.h>
#include <rtdevice.h>

#define FXOS8700_DEV_NAME        ("fxos8700")
#define FXOS8700_I2C_DEV_NAME    ("i2c2")
#define FXOS8700_CHIP_ADDR       (0x1E)


#define DBG_TAG "drv.fxos8700"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>




#define CTRL_REG1 0x2A
#define XYZ_DATA_CFG_REG 0x0E
#define M_CTRL_REG1 0x5B
#define F_SETUP_REG 0x09
#define M_CTRL_REG2 0x5C
#define OUT_X_MSB_REG 0x01
#define OUT_X_LSB_REG 0x02
#define OUT_Y_MSB_REG 0x03
#define OUT_Y_LSB_REG 0x04
#define OUT_Z_MSB_REG 0x05
#define OUT_Z_LSB_REG 0x06


#define F_MODE_DISABLED 0x00
#define ASLP_RATE1_MASK 0x80
#define ASLP_RATE0_MASK 0x40
#define DR2_MASK 0x20
#define DR1_MASK 0x10
#define DR0_MASK 0x08
#define LNOISE_MASK 0x04
#define FREAD_MASK 0x02
#define ACTIVE_MASK 0x01
#define ASLP_RATE_MASK 0xC0
#define DR_MASK 0x38
#define M_HYB_AUTOINC_MASK 0x20
#define M_MAXMIN_DIS_MASK 0x10
#define M_MAXMIN_DIS_THS_MASK 0x08
#define M_MAXMIN_RST_MASK 0x04
#define M_RST_CNT1_MASK 0x02
#define M_RST_CNT0_MASK 0x01

#define M_ACAL_MASK 0x80
#define M_RST_MASK 0x40
#define M_OST_MASK 0x20
#define M_OSR2_MASK 0x10
#define M_OSR1_MASK 0x08
#define M_OSR0_MASK 0x04
#define M_HMS1_MASK 0x02
#define M_HMS0_MASK 0x01
#define M_OSR_MASK 0x1C
#define M_HMS_MASK 0x03


typedef struct
{
    struct rt_device            parent;
    struct rt_i2c_bus_device    *bus;
    uint8_t i2c_addr;
}fxos8700_t;


static uint8_t fxos_read_reg(fxos8700_t *dev, uint8_t reg_addr)
{
    uint8_t val;

    rt_i2c_master_send(dev->bus, dev->i2c_addr, RT_I2C_WR, &reg_addr, 1);
    rt_i2c_master_recv(dev->bus, dev->i2c_addr, RT_I2C_RD, &val, 1);
    return val;
}


static void fxos_write_reg(fxos8700_t *dev, uint8_t reg_addr, uint8_t val)
{
    uint8_t buf[2];
    buf[0] = reg_addr;
    buf[1] = val;

    rt_i2c_master_send(dev->bus, dev->i2c_addr, RT_I2C_WR, buf, 2);
}



static rt_err_t fxos8700_open(rt_device_t dev, rt_uint16_t oflag)
{
    int i;
    uint8_t val;

    fxos8700_t *fxos8700 = (fxos8700_t *)dev;

    for(i=0; i<5; i++)
    {
        val = fxos_read_reg(fxos8700, 0x0D);

        if(val == 0xC7)
        {
            LOG_D("fxos8700 found, id:0x%X", val);

            /* reset */
        /*    fxos_write_reg(instance, gChipAddr, CTRL_REG2, RST_MASK);*/
            /* wait for a bit */
            for (i = 0; i < 0xFFFF; i++)
            {
                __asm("NOP");
            }

            /* setup auto sleep with FFMT trigger */
            /* go to standby */
            val = fxos_read_reg(fxos8700, CTRL_REG1);
            fxos_write_reg(fxos8700, CTRL_REG1, val & (uint8_t)~ACTIVE_MASK);

            /* Disable the FIFO */
            fxos_write_reg(fxos8700, F_SETUP_REG, F_MODE_DISABLED);

            /* set up Mag OSR and Hybrid mode using M_CTRL_REG1, use default for Acc */
            fxos_write_reg(fxos8700, M_CTRL_REG1, (M_RST_MASK | M_OSR_MASK | M_HMS_MASK));

            /* Enable hyrid mode auto increment using M_CTRL_REG2 */
            fxos_write_reg(fxos8700, M_CTRL_REG2, (M_HYB_AUTOINC_MASK));

            fxos_write_reg(fxos8700, XYZ_DATA_CFG_REG, 0x02);

            val = fxos_read_reg(fxos8700, CTRL_REG1);
            fxos_write_reg(fxos8700, CTRL_REG1, val | LNOISE_MASK);
            fxos_write_reg(fxos8700, CTRL_REG1, val | ACTIVE_MASK | LNOISE_MASK);
            return RT_EOK;
        }
        else
        {
            LOG_D("fxos8700 cannot found, id:0x%X", val);
        }

    }

    return RT_ERROR;
}



static rt_ssize_t fxos8700_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    fxos8700_t *fxos8700 = (fxos8700_t *)dev;

    uint8_t buf[12];
    buf[0] = OUT_X_MSB_REG;

    rt_i2c_master_send(fxos8700->bus, fxos8700->i2c_addr, RT_I2C_WR, buf, 1);
    rt_i2c_master_recv(fxos8700->bus, fxos8700->i2c_addr, RT_I2C_RD, buf, 12);


    int16_t iacc[3];
    iacc[0] = (int16_t)((((int16_t)buf[0] << 8) | buf[1]));
    iacc[1] = (int16_t)((((int16_t)buf[2] << 8) | buf[3]));
    iacc[2] = (int16_t)((((int16_t)buf[4] << 8) | buf[5]));

    float *out_buf = buffer;

    out_buf[0] = (float)iacc[0] / 4096;
    out_buf[1] = (float)iacc[1] / 4096;
    out_buf[2] = (float)iacc[2] / 4096;
    return 3*4;
}


int rt_hw_fxos8700_init(void)
{
    static fxos8700_t fxos8700;
    struct rt_i2c_bus_device *bus;

    bus = rt_i2c_bus_device_find(FXOS8700_I2C_DEV_NAME);
    if (bus == RT_NULL)
    {
        return RT_ENOSYS;
    }

    fxos8700.parent.type               = RT_Device_Class_Sensor;
    fxos8700.parent.rx_indicate        = RT_NULL;
    fxos8700.parent.tx_complete        = RT_NULL;
    fxos8700.parent.init               = RT_NULL;
    fxos8700.parent.open               = fxos8700_open;
    fxos8700.parent.close              = RT_NULL;
    fxos8700.parent.read               = fxos8700_read;
    fxos8700.parent.write              = RT_NULL;
    fxos8700.parent.user_data          = RT_NULL;

    fxos8700.bus = bus;
    fxos8700.i2c_addr = FXOS8700_CHIP_ADDR;

    rt_device_register(&fxos8700.parent, FXOS8700_DEV_NAME, RT_DEVICE_FLAG_RDWR);
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_fxos8700_init);
