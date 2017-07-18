// 龙芯1c外设寄存器


#ifndef __OPENLOONGSON_LS1C_REGS_H
#define __OPENLOONGSON_LS1C_REGS_H




// 时钟相关寄存器地址
#define LS1C_START_FREQ                     (0xbfe78030)
#define LS1C_CLK_DIV_PARAM                  (0xbfe78034)


// gpio相关寄存器地址
#define LS1C_GPIO_CFG0                      (0xbfd010c0)
#define LS1C_GPIO_EN0                       (0xbfd010d0)
#define LS1C_GPIO_IN0                       (0xbfd010e0)
#define LS1C_GPIO_OUT0                      (0xbfd010f0)

#define LS1C_GPIO_CFG1                      (0xbfd010c4)
#define LS1C_GPIO_EN1                       (0xbfd010d4)
#define LS1C_GPIO_IN1                       (0xbfd010e4)
#define LS1C_GPIO_OUT1                      (0xbfd010f4)

#define LS1C_GPIO_CFG2                      (0xbfd010c8)
#define LS1C_GPIO_EN2                       (0xbfd010d8)
#define LS1C_GPIO_IN2                       (0xbfd010e8)
#define LS1C_GPIO_OUT2                      (0xbfd010f8)

#define LS1C_GPIO_CFG3                      (0xbfd010cc)
#define LS1C_GPIO_EN3                       (0xbfd010dc)
#define LS1C_GPIO_IN3                       (0xbfd010ec)
#define LS1C_GPIO_OUT3                      (0xbfd010fc)



// 复用相关寄存器
#define LS1C_CBUS_FIRST0                    (0xbfd011c0)
#define LS1C_CBUS_SECOND0                   (0xbfd011d0)
#define LS1C_CBUS_THIRD0                    (0xbfd011e0)
#define LS1C_CBUS_FOURTH0                   (0xbfd011f0)
#define LS1C_CBUS_FIFTH0                    (0xbfd01200)

#define LS1C_CBUS_FIRST1                    (0xbfd011c4)
#define LS1C_CBUS_SECOND1                   (0xbfd011d4)
#define LS1C_CBUS_THIRD1                    (0xbfd011e4)
#define LS1C_CBUS_FOURTH1                   (0xbfd011f4)
#define LS1C_CBUS_FIFTH1                    (0xbfd01204)

#define LS1C_CBUS_FIRST2                    (0xbfd011c8)
#define LS1C_CBUS_SECOND2                   (0xbfd011d8)
#define LS1C_CBUS_THIRD2                    (0xbfd011e8)
#define LS1C_CBUS_FOURTH2                   (0xbfd011f8)
#define LS1C_CBUS_FIFTH2                    (0xbfd01208)

#define LS1C_CBUS_FIRST3                    (0xbfd011cc)
#define LS1C_CBUS_SECOND3                   (0xbfd011dc)
#define LS1C_CBUS_THIRD3                    (0xbfd011ec)
#define LS1C_CBUS_FOURTH3                   (0xbfd011fc)
#define LS1C_CBUS_FIFTH3                    (0xbfd0120c)


// PWM寄存器偏移
#define LS1C_PWM_CNTR                       (0x0)
#define LS1C_PWM_HRC                        (0x4)
#define LS1C_PWM_LRC                        (0x8)
#define LS1C_PWM_CTRL                       (0xC)
// PWM基地址
#define LS1C_REG_BASE_PWM0                  (0xbfe5c000)
#define LS1C_REG_BASE_PWM1                  (0xbfe5c010)
#define LS1C_REG_BASE_PWM2                  (0xbfe5c020)
#define LS1C_REG_BASE_PWM3                  (0xbfe5c030)













#endif

