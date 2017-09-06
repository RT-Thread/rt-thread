// ÁúÐ¾1cÍâÉè¼Ä´æÆ÷


#ifndef __OPENLOONGSON_LS1C_REGS_H
#define __OPENLOONGSON_LS1C_REGS_H




// Ê±ÖÓÏà¹Ø¼Ä´æÆ÷µØÖ·
#define LS1C_START_FREQ                     (0xbfe78030)
#define LS1C_CLK_DIV_PARAM                  (0xbfe78034)


// gpioÏà¹Ø¼Ä´æÆ÷µØÖ·
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



// ¸´ÓÃÏà¹Ø¼Ä´æÆ÷
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


// PWM¼Ä´æÆ÷Æ«ÒÆ
#define LS1C_PWM_CNTR                       (0x0)
#define LS1C_PWM_HRC                        (0x4)
#define LS1C_PWM_LRC                        (0x8)
#define LS1C_PWM_CTRL                       (0xC)
// PWM»ùµØÖ·
#define LS1C_REG_BASE_PWM0                  (0xbfe5c000)
#define LS1C_REG_BASE_PWM1                  (0xbfe5c010)
#define LS1C_REG_BASE_PWM2                  (0xbfe5c020)
#define LS1C_REG_BASE_PWM3                  (0xbfe5c030)



// ÖÐ¶ÏÅäÖÃ¼Ä´æÆ÷
#define LS1C_INT0_SR                        (0xbfd01040)
#define LS1C_INT0_EN                        (0xbfd01044)
#define LS1C_INT0_SET                       (0xbfd01048)
#define LS1C_INT0_CLR                       (0xbfd0104c)
#define LS1C_INT0_POL                       (0xbfd01050)
#define LS1C_INT0_EDGE                      (0xbfd01054)

#define LS1c_INT1_SR                        (0xbfd01058)
#define LS1C_INT1_EN                        (0xbfd0105c)
#define LS1C_INT1_SET                       (0xbfd01060)
#define LS1C_INT1_CLR                       (0xbfd01064)
#define LS1C_INT1_POL                       (0xbfd01068)
#define LS1C_INT1_EDGE                      (0xbfd0106c)

#define LS1C_INT2_SR                        (0xbfd01070)
#define LS1C_INT2_EN                        (0xbfd01074)
#define LS1C_INT2_SET                       (0xbfd01078)
#define LS1C_INT2_CLR                       (0xbfd0107c)
#define LS1C_INT2_POL                       (0xbfd01080)
#define LS1C_INT2_EDGE                      (0xbfd01084)

#define LS1C_INT3_SR                        (0xbfd01088)
#define LS1C_INT3_EN                        (0xbfd0108c)
#define LS1C_INT3_SET                       (0xbfd01090)
#define LS1C_INT3_CLR                       (0xbfd01094)
#define LS1C_INT3_POL                       (0xbfd01098)
#define LS1C_INT3_EDGE                      (0xbfd0109c)

#define LS1C_INT4_SR                        (0xbfd010a0)
#define LS1C_INT4_EN                        (0xbfd010a4)
#define LS1C_INT4_SET                       (0xbfd010a8)
#define LS1C_INT4_CLR                       (0xbfd010ac)
#define LS1C_INT4_POL                       (0xbfd010b0)
#define LS1C_INT4_EDGE                      (0xbfd010b4)


// I2C¼Ä´æÆ÷
#define LS1C_I2C0_BASE                      (0xbfe58000)
#define LS1C_I2C1_BASE                      (0xbfe68000)
#define LS1C_I2C2_BASE                      (0xbfe70000)


#endif

