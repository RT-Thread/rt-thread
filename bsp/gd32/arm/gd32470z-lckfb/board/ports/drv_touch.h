#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "stdio.h"
#include "string.h"
#include "gd32f4xx.h"


#define SCL_RCU    RCU_GPIOB
#define SCL_PORT   GPIOB
#define SCL_PIN    GPIO_PIN_6
#define SCL_ON     gpio_bit_set(SCL_PORT, SCL_PIN)
#define SCL_OFF    gpio_bit_reset(SCL_PORT, SCL_PIN)
#define SCL_TOGGLE gpio_bit_toggle(SCL_PORT, SCL_PIN)

#define SDA_RCU    RCU_GPIOB
#define SDA_PORT   GPIOB
#define SDA_PIN    GPIO_PIN_7
#define SDA_ON     gpio_bit_set(SDA_PORT, SDA_PIN)
#define SDA_OFF    gpio_bit_reset(SDA_PORT, SDA_PIN)
#define SDA_TOGGLE gpio_bit_toggle(SDA_PORT, SDA_PIN)

// IO方向设置
#define CT_SDA_IN()  gpio_mode_set(SCL_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, SDA_PIN);  //{GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=0<<2*11;}	//PF11输入模式
#define CT_SDA_OUT() gpio_mode_set(SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SDA_PIN); //{GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=1<<2*11;} 	//PF11输出模式
// IO操作函数
#define CT_IIC_SCL                                            // PBout(0) 	//SCL
#define CT_IIC_SDA(val) ((val) == 1 ? SDA_ON : SDA_OFF)       // PFout(11) //SDA
#define CT_READ_SDA     gpio_input_bit_get(SDA_PORT, SDA_PIN) // PFin(11)  //输入SDA

#define RST_RCU    RCU_GPIOD
#define RST_PORT   GPIOD
#define RST_PIN    GPIO_PIN_12
#define RST_ON     gpio_bit_set(RST_PORT, RST_PIN);
#define RST_OFF    gpio_bit_reset(RST_PORT, RST_PIN);
#define RST_TOGGLE gpio_bit_toggle(RST_PORT, RST_PIN);

#define INT_RCU    RCU_GPIOD
#define INT_PORT   GPIOD
#define INT_PIN    GPIO_PIN_11
#define INT_ON     gpio_bit_set(INT_PORT, INT_PIN);
#define INT_OFF    gpio_bit_reset(INT_PORT, INT_PIN);
#define INT_TOGGLE gpio_bit_toggle(INT_PORT, INT_PIN);

// I2C读写命令
#define FT_CMD_WR 0X70 // 写命令
#define FT_CMD_RD 0X71 // 读命令
// FT5206 部分寄存器定义
#define FT_DEVIDE_MODE    0x00    // FT5206模式控制寄存器
#define FT_REG_NUM_FINGER 0x02    // 触摸状态寄存器
#define FT_TP1_REG        0X03    // 第一个触摸点数据地址
#define FT_TP2_REG        0X09    // 第二个触摸点数据地址
#define FT_TP3_REG        0X0F    // 第三个触摸点数据地址
#define FT_TP4_REG        0X15    // 第四个触摸点数据地址
#define FT_TP5_REG        0X1B    // 第五个触摸点数据地址

#define FT_ID_G_LIB_VERSION  0xA1 // 版本
#define FT_ID_G_MODE         0xA4 // FT5206中断模式控制寄存器
#define FT_ID_G_THGROUP      0x80 // 触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE 0x88 // 激活状态周期设置寄存器

#define TP_PRES_DOWN 0x80         // 触屏被按下
#define TP_CATH_PRES 0x40         // 有按键按下了
#define CT_MAX_TOUCH 5            // 电容屏支持的点数,固定为5点
// 触摸屏控制器
typedef struct
{
    //    uint8_t (*init)(void);			//初始化触摸屏控制器
    //    uint8_t (*scan)(uint8_t);				//扫描触摸屏.0,屏幕扫描;1,物理坐标;
    //    void (*adjust)(void);		//触摸屏校准
    uint16_t x[CT_MAX_TOUCH]; // 当前坐标
    uint16_t y[CT_MAX_TOUCH]; // 电容屏有最多5组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
    uint8_t  sta;             // 笔的状态
    float    xfac;
    float    yfac;
    short    xoff;
    short    yoff;
    uint8_t  touchtype;
} _m_tp_dev;
extern _m_tp_dev tp_dev; // 触屏控制器在touch.c里面定义

// IIC所有操作函数
void    CT_IIC_Init(void);                   // 初始化IIC的IO口
void    CT_IIC_Start(void);                  // 发送IIC开始信号
void    CT_IIC_Stop(void);                   // 发送IIC停止信号
void    CT_IIC_Send_Byte(uint8_t txd);       // IIC发送一个字节
uint8_t CT_IIC_Read_Byte(unsigned char ack); // IIC读取一个字节
uint8_t CT_IIC_Wait_Ack(void);               // IIC等待ACK信号
void    CT_IIC_Ack(void);                    // IIC发送ACK信号
void    CT_IIC_NAck(void);                   // IIC不发送ACK信号

// 触摸屏操作函数
uint8_t FT5206_WR_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
void    FT5206_RD_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
uint8_t FT5206_Init(void);
uint8_t FT5206_Scan(uint8_t mode);
void    letgo_scan(uint16_t contact, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);

#endif
