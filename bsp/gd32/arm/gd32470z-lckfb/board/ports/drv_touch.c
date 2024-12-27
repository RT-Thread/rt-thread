#include <board.h>
#include <rthw.h>
#include <rtthread.h>
#include "drv_touch.h"
#include "drv_lcd.h"

#define DRV_DEBUG
#define LOG_TAG "drv.touch"
#include <drv_log.h>

_m_tp_dev tp_dev;

const uint16_t FT5206_TPX_TBL[5] = {FT_TP1_REG, FT_TP2_REG, FT_TP3_REG, FT_TP4_REG, FT_TP5_REG};
uint8_t        g_gt_tnum         = 5; // 默认支持的触摸屏点数(5点触摸)

void delay_us(uint32_t _nus)
{
    uint8_t  fac_us = 0;
    uint32_t ticks;
    uint32_t t_old, t_now, t_cnt = 0;
    uint32_t reload = SysTick->LOAD; //获取重装载值（只查询，不影响）

    fac_us = SystemCoreClock / 1000000;
    ticks  = _nus * fac_us - fac_us * 7 / 20;
    t_old  = SysTick->VAL; //获取当前值作为旧值（只查询，不影响）

    while (1)
    {
        /*systick为向下递减，未减到0导致重装载的情况下，新值小于旧值*/
        t_now = SysTick->VAL; //获取当前值作为新值（只查询，不影响）

        if (t_now < t_old)
        {
            t_cnt += t_old - t_now; //未发生重装载，cnt记录减少的值
        }
        else
        {
            t_cnt += t_old + (reload - t_now); //重装载后，旧值已递减完毕，cnt需在再加上重装载值与新值的差值
        }

        if (t_cnt >= ticks)
        {
            break; //当计数cnt大于等于用户需要的ticks，即认为延时完毕，跳出循环
        }

        t_old = t_now; //获取当前值作为旧值，以供下一次循环做判断（只查询，不影响）
    };
}


void touch_delay_1us(uint16_t us)
{
    delay_us(us);
}

// 控制I2C速度的延时
void CT_Delay(void)
{
    touch_delay_1us(2);
}

// 电容触摸芯片IIC接口初始化
void CT_IIC_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(SCL_RCU);
    /* configure led GPIO port */
    gpio_mode_set(SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SCL_PIN);
    gpio_output_options_set(SCL_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SCL_PIN);

    rcu_periph_clock_enable(SDA_RCU);
    gpio_mode_set(SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SDA_PIN);
    gpio_output_options_set(SDA_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SDA_PIN);
}
// 产生IIC起始信号
void CT_IIC_Start(void)
{
    CT_SDA_OUT(); // sda线输出
    SDA_ON;
    SCL_ON;       // SCL=1时，SDA由1到0跳变
    touch_delay_1us(30);
    SDA_OFF;      // START:when CLK is high,DATA change form high to low
    CT_Delay();
    SCL_OFF;      // 钳住I2C总线，准备发送或接收数据
}
// 产生IIC停止信号
void CT_IIC_Stop(void)
{
    CT_SDA_OUT(); // sda线输出
    SCL_ON;       // SCL=1时，SDA由0到1跳变
    touch_delay_1us(30);
    SDA_OFF;      // STOP:when CLK is high DATA change form low to high
    CT_Delay();
    SDA_ON;       // 发送I2C总线结束信号
}
// 等待应答信号到来
// 返回值：1，接收应答失败
//         0，接收应答成功
uint8_t CT_IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    CT_SDA_IN(); // SDA设置为输入
    SDA_ON;
    SCL_ON;
    CT_Delay();
    while (CT_READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            CT_IIC_Stop();
            return 1;
        }
        CT_Delay();
    }
    SCL_OFF; // 时钟输出0
    return 0;
}
// 产生ACK应答
void CT_IIC_Ack(void)
{
    SCL_OFF;
    CT_SDA_OUT();
    CT_Delay();
    SDA_OFF;
    CT_Delay();
    SCL_ON;
    CT_Delay();
    SCL_OFF;
}
// 不产生ACK应答
void CT_IIC_NAck(void)
{
    SCL_OFF;
    CT_SDA_OUT();
    CT_Delay();
    SDA_ON;
    CT_Delay();
    SCL_ON;
    CT_Delay();
    SCL_OFF;
}
// IIC发送一个字节
// 返回从机有无应答
// 1，有应答
// 0，无应答
void CT_IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    CT_SDA_OUT();
    SCL_OFF; // 拉低时钟开始数据传输
    CT_Delay();
    for (t = 0; t < 8; t++)
    {
        // CT_IIC_SDA=(txd&0x80)>>7;
        // CT_IIC_SDA((txd&0x80)>>7);
        if ((txd & 0x80) >> 7)
        {
            gpio_bit_set(SDA_PORT, SDA_PIN);
        }
        else
        {
            gpio_bit_reset(SDA_PORT, SDA_PIN);
        }

        txd <<= 1;
        SCL_ON;
        CT_Delay();
        SCL_OFF;
        CT_Delay();
    }
}
// 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
    volatile uint8_t i, receive = 0;
    CT_SDA_IN(); // SDA设置为输入
    touch_delay_1us(30);
    for (i = 0; i < 8; i++)
    {
        SCL_OFF;
        CT_Delay();
        SCL_ON;
        receive <<= 1;

        // printf("%d ",CT_READ_SDA);
        if (CT_READ_SDA)
            receive++;
    }
    // printf("\r\n receive:%0x \r\n",receive);

    if (!ack)
        CT_IIC_NAck(); // 发送nACK
    else
        CT_IIC_Ack();  // 发送ACK
    return receive;
}

// 向FT5206写入一次数据
uint8_t FT5206_WR_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t ret = 0;
    CT_IIC_Start();
    CT_IIC_Send_Byte(FT_CMD_WR);  // 发送写命令
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg & 0XFF); // 发送低8位地址
    CT_IIC_Wait_Ack();
    for (i = 0; i < len; i++)
    {
        CT_IIC_Send_Byte(buf[i]); // 发数据
        ret = CT_IIC_Wait_Ack();
        if (ret)
            break;
    }
    CT_IIC_Stop(); // 产生一个停止条件
    return ret;
}

// 从FT5206读出一次数据
void FT5206_RD_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    CT_IIC_Start();
    CT_IIC_Send_Byte(FT_CMD_WR);  // 发送写命令
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg & 0XFF); // 发送低8位地址
    CT_IIC_Wait_Ack();
    CT_IIC_Start();
    CT_IIC_Send_Byte(FT_CMD_RD); // 发送读命令
    CT_IIC_Wait_Ack();
    for (i = 0; i < len; i++)
    {
        buf[i] = CT_IIC_Read_Byte(i == (len - 1) ? 0 : 1); // 发数据
    }
    CT_IIC_Stop();                                         // 产生一个停止条件
}

// 初始化FT5206触摸屏
uint8_t FT5206_Init(void)
{
    uint8_t temp[5];
    // PD11设置为上拉输入(INT)
    /* enable the led clock */
    rcu_periph_clock_enable(INT_RCU);
    /* configure led GPIO port */
    gpio_mode_set(INT_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, INT_PIN);

    // 初始化电容屏的I2C总线
    CT_IIC_Init();

    FT5206_WR_Reg(FT_DEVIDE_MODE, temp, 1);  // 进入正常操作模式
    FT5206_WR_Reg(FT_ID_G_MODE, temp, 1);    // 查询模式
    temp[0] = 22;                            // 触摸有效值，22，越小越灵敏
    FT5206_WR_Reg(FT_ID_G_THGROUP, temp, 1); // 设置触摸有效值
    temp[0] = 12;                            // 激活周期，不能小于12，最大14
    FT5206_WR_Reg(FT_ID_G_PERIODACTIVE, temp, 1);
    // 读取版本号，参考值：0x3003
    FT5206_RD_Reg(FT_ID_G_LIB_VERSION, &temp[0], 2);
    printf("CTP ID:%x\r\n", ((uint16_t)temp[0] << 8) + temp[1]);
    return 0;
}

// 扫描触摸屏(采用查询方式)
// mode:0,正常扫描.
// 返回值:当前触屏状态.
// 0,触屏无触摸;1,触屏有触摸
uint8_t FT5206_Scan(uint8_t mode)
{
    uint8_t        buf[4];
    uint8_t        i   = 0;
    uint8_t        res = 0;
    uint8_t        temp;
    uint16_t       tempsta;
    static uint8_t t = 0;                           // 控制查询间隔,从而降低CPU占用率
    t++;
    if ((t % 10) == 0 || t < 10)                    // 空闲时,每进入10次CTP_Scan函数才检测1次,从而节省CPU使用率
    {
        FT5206_RD_Reg(FT_REG_NUM_FINGER, &mode, 1); // 读取触摸点的状态
        if ((mode & 0XF) && ((mode & 0XF) <= g_gt_tnum))
        {
            temp                    = 0XFF << (mode & 0XF); // 将点的个数转换为1的位数,匹配tp_dev.sta定义
            tempsta                 = tp_dev.sta;           // 保存当前的tp_dev.sta值
            tp_dev.sta              = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;
            tp_dev.x[g_gt_tnum - 1] = tp_dev.x[0];          // 保存触点0的数据,保存在最后一个上
            tp_dev.y[g_gt_tnum - 1] = tp_dev.y[0];
            // delay_1ms(4);    //必要的延时，否则老是认为有按键按下
            for (i = 0; i < g_gt_tnum; i++)
            {
                if (tp_dev.sta & (1 << i))                    // 触摸有效?
                {
                    FT5206_RD_Reg(FT5206_TPX_TBL[i], buf, 4); // 读取XY坐标值
                    if (tp_dev.touchtype & 0X01)              // 横屏
                    {
                        tp_dev.y[i] = ((uint16_t)(buf[0] & 0X0F) << 8) + buf[1];
                        tp_dev.x[i] = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
                    }
                    else
                    {
                        tp_dev.x[i] = (((uint16_t)(buf[0] & 0X0F) << 8) + buf[1]);
                        tp_dev.y[i] = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
                    }
                }
            }
            res = 1;
            if (tp_dev.x[0] > ACTIVE_WIDTH || tp_dev.y[0] > ACTIVE_HEIGHT) // 非法数据(坐标超出了)
            {
                if ((mode & 0XF) > 1)                                      // 有其他点有数据,则复第二个触点的数据到第一个触点.
                {
                    tp_dev.x[0] = tp_dev.x[1];
                    tp_dev.y[0] = tp_dev.y[1];
                    t           = 0; // 触发一次,则会最少连续监测10次,从而提高命中率
                }
                else                 // 非法数据,则忽略此次数据(还原原来的)
                {
                    tp_dev.x[0] = tp_dev.x[g_gt_tnum - 1];
                    tp_dev.y[0] = tp_dev.y[g_gt_tnum - 1];
                    mode        = 0X80;
                    tp_dev.sta  = tempsta; // 恢复tp_dev.sta
                }
            }
            else
                t = 0; // 触发一次,则会最少连续监测10次,从而提高命中率
        }
    }

    if ((mode & 0X1F) == 0)              // 无触摸点按下
    {
        if (tp_dev.sta & TP_PRES_DOWN)   // 之前是被按下的
        {
            tp_dev.sta &= ~TP_PRES_DOWN; // 标记按键松开
        }
        else                             // 之前就没有被按下
        {
            tp_dev.x[0]  = 0xffff;
            tp_dev.y[0]  = 0xffff;
            tp_dev.sta  &= 0XE0; // 清除点有效标记
        }
    }

    if (t > 240)
        t = 10; // 重新从10开始计数
    return res;
}

/**********************************************************
 * 函 数 名 称：letgo_scan
 * 函 数 功 能：触摸松手判断
 * 传 入 参 数：contact：第几个触点(一共有5个触点)
 * 				(sx,sy)：判断触摸地的起始坐标
 * 				(ex,ey)：判断触摸地的结束坐标
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void letgo_scan(uint16_t contact, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
    //等待松手
    while (FT5206_Scan(0))
    {
        //如果离开了x轴触摸范围
        if (tp_dev.x[contact] <= sx || tp_dev.x[contact] >= ex)
        {
            return;
        }
        //如果离开了y轴触摸范围
        if (tp_dev.y[contact] <= sy && tp_dev.y[contact] >= ey)
        {
            return;
        }
    }
}

int touch_test(void)
{
    int touch_state = 0;
    FT5206_Init();

    while (1)
    {
        touch_state = FT5206_Scan(0);

        if (touch_state == 1)
        {
            rt_kprintf("touch\r\n");
        }
        rt_thread_mdelay(10);
    }
}
MSH_CMD_EXPORT(touch_test, touch test)
