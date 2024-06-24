

#include <rtthread.h>
#include <rtdevice.h>

#define FXAS2100_DEV_NAME        ("fxas2100")
#define FXAS2100_I2C_DEV_NAME    ("i2c2")
#define FXAS2100_CHIP_ADDR       (0x20)

/* register addresses FXAS21002C_H_*/
#define FXAS21002C_H_STATUS           0x00
#define FXAS21002C_H_DR_STATUS        0x07
#define FXAS21002C_H_F_STATUS         0x08
#define FXAS21002C_H_OUT_X_MSB        0x01
#define FXAS21002C_H_OUT_X_LSB        0x02
#define FXAS21002C_H_OUT_Y_MSB        0x03
#define FXAS21002C_H_OUT_Y_LSB        0x04
#define FXAS21002C_H_OUT_Z_MSB        0x05
#define FXAS21002C_H_OUT_Z_LSB        0x06
#define FXAS21002C_H_F_SETUP          0x09
#define FXAS21002C_H_F_EVENT          0x0A
#define FXAS21002C_H_INT_SRC_FLAG     0x0B
#define FXAS21002C_H_WHO_AM_I         0x0C
#define FXAS21002C_H_CTRL_REG0        0x0D
#define FXAS21002C_H_RT_CFG           0x0E
#define FXAS21002C_H_RT_SRC           0x0F
#define FXAS21002C_H_RT_THS           0x10
#define FXAS21002C_H_RT_COUNT         0x11
#define FXAS21002C_H_TEMP             0x12
#define FXAS21002C_H_CTRL_REG1        0x13
#define FXAS21002C_H_CTRL_REG2        0x14
#define FXAS21002C_H_CTRL_REG3        0x15

#define DBG_TAG "drv.fxas2100"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>



typedef struct
{
    struct rt_device            parent;
    struct rt_i2c_bus_device    *bus;
    uint8_t i2c_addr;
}fxas2100_t;


static uint8_t fxos_read_reg(fxas2100_t *dev, uint8_t reg_addr)
{
    uint8_t val;

    rt_i2c_master_send(dev->bus, dev->i2c_addr, RT_I2C_WR, &reg_addr, 1);
    rt_i2c_master_recv(dev->bus, dev->i2c_addr, RT_I2C_RD, &val, 1);
    return val;
}


static void fxos_write_reg(fxas2100_t *dev, uint8_t reg_addr, uint8_t val)
{
    uint8_t buf[2];
    buf[0] = reg_addr;
    buf[1] = val;

    rt_i2c_master_send(dev->bus, dev->i2c_addr, RT_I2C_WR, buf, 2);
}



static rt_err_t fxas2100_open(rt_device_t dev, rt_uint16_t oflag)
{
    int i;
    uint8_t val;

    fxas2100_t *fxas2100 = (fxas2100_t *)dev;

    for(i=0; i<5; i++)
    {
        val = fxos_read_reg(fxas2100, 0x0C);

        if(val == 0xD7)
        {
            LOG_D("fxas2100 found, id:0x%X", val);
            /* stand by */
            val = fxos_read_reg(fxas2100, FXAS21002C_H_CTRL_REG1);
            fxos_write_reg(fxas2100, FXAS21002C_H_CTRL_REG1, val & ~(0x03));

            /* Disable FIFO, route FIFO and rate threshold interrupts to INT2, enable data ready interrupt, route to INT1*/
            /* Active HIGH, push-pull output driver on interrupts*/
            fxos_write_reg(fxas2100, FXAS21002C_H_CTRL_REG2, 0x0E);
            fxos_write_reg(fxas2100, FXAS21002C_H_CTRL_REG0, 0x80);

             /* Set up rate threshold detection; at max rate threshold = FSR; rate threshold = THS*FSR/128*/
            fxos_write_reg(fxas2100, FXAS21002C_H_RT_CFG, 0x07);         /* enable rate threshold detection on all axes*/
            fxos_write_reg(fxas2100, FXAS21002C_H_RT_THS, 0x00 | 0x0D);  /* unsigned 7-bit THS, set to one-tenth FSR; set clearing debounce counter*/
            fxos_write_reg(fxas2100, FXAS21002C_H_RT_COUNT, 0x04);       /* set to 4 (can set up to 255)*/

            val = fxos_read_reg(fxas2100, FXAS21002C_H_CTRL_REG1);
            fxos_write_reg(fxas2100, FXAS21002C_H_CTRL_REG1, val & ~(0x03));  /* Clear bits 0 and 1; standby mode*/
            fxos_write_reg(fxas2100, FXAS21002C_H_CTRL_REG1, val |   0x02);   /* Set bit 1 to 1, active mode; data acquisition enabled*/
            return RT_EOK;
        }
        else
        {
            LOG_D("fxas2100 cannot found, id:0x%X", val);
        }

    }

    return RT_ERROR;
}


static rt_ssize_t fxas2100_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    fxas2100_t *fxas2100 = (fxas2100_t *)dev;

    uint8_t buf[12];
    buf[0] = FXAS21002C_H_OUT_X_MSB;

    rt_i2c_master_send(fxas2100->bus, fxas2100->i2c_addr, RT_I2C_WR, buf, 1);
    rt_i2c_master_recv(fxas2100->bus, fxas2100->i2c_addr, RT_I2C_RD, buf, 6);


    int16_t idata[3];
    idata[0] = (int16_t)((((int16_t)buf[0] << 8) | buf[1]));
    idata[1] = (int16_t)((((int16_t)buf[2] << 8) | buf[3]));
    idata[2] = (int16_t)((((int16_t)buf[4] << 8) | buf[5]));

    float *out_buf = buffer;

    out_buf[0] = (float)idata[0] *(2000.0F/32768.0F);
    out_buf[1] = (float)idata[1] *(2000.0F/32768.0F);
    out_buf[2] = (float)idata[2] *(2000.0F/32768.0F);
}


int rt_hw_fxas2100_init(void)
{
    static fxas2100_t fxas2100;
    struct rt_i2c_bus_device *bus;

    bus = rt_i2c_bus_device_find(FXAS2100_I2C_DEV_NAME);
    if (bus == RT_NULL)
    {
        return RT_ENOSYS;
    }

    fxas2100.parent.type               = RT_Device_Class_Sensor;
    fxas2100.parent.rx_indicate        = RT_NULL;
    fxas2100.parent.tx_complete        = RT_NULL;
    fxas2100.parent.init               = RT_NULL;
    fxas2100.parent.open               = fxas2100_open;
    fxas2100.parent.close              = RT_NULL;
    fxas2100.parent.read               = fxas2100_read;
    fxas2100.parent.write              = RT_NULL;
    fxas2100.parent.user_data          = RT_NULL;

    fxas2100.bus = bus;
    fxas2100.i2c_addr = FXAS2100_CHIP_ADDR;

    rt_device_register(&fxas2100.parent, FXAS2100_DEV_NAME, RT_DEVICE_FLAG_RDWR);
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_fxas2100_init);
