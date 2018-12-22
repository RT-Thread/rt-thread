#ifndef _GPIO_RB_TW9912_H_
#define _GPIO_RB_TW9912_H_

#include "adi_types.h"
#include "adi_gpio.h"

#define SYSTEM_USE_EXTERN_I2S       0
#define SYSTEM_USE_SDCARD           1
#define SYSTEM_USE_EXTERN_ETHPHY    0
#define SYSTEM_INIT_GD_GPIO         0

#define CONFIG_PHY_USE_AO_MCLK
#ifdef CONFIG_PHY_USE_AO_MCLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_OUTPUT_AOMCLK
#endif
#ifdef CONFIG_PHY_USE_SD_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_OUTPUT_SDIO_CLK
#endif
#ifdef CONFIG_PHY_USE_EXTERN_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_INPUT_0
#endif

//#ifdef CONFIG_SYSTEM_USE_SDCARD
#define SYSTEM_GPIO_SD_TABLE                              \
        { GADI_GPIO_33, GADI_GPIO_TYPE_OUTPUT_SDIO1_CLK               }, \
        { GADI_GPIO_32, GADI_GPIO_TYPE_INOUT_SD1_CMD                  }, \
        { GADI_GPIO_34, GADI_GPIO_TYPE_INOUT_SD1_DATA_0               }, \
        { GADI_GPIO_35, GADI_GPIO_TYPE_INOUT_SD1_DATA_1               }, \
        { GADI_GPIO_30, GADI_GPIO_TYPE_INOUT_SD1_DATA_2               }, \
        { GADI_GPIO_31, GADI_GPIO_TYPE_INOUT_SD1_DATA_3               }, 
        //{ GADI_GPIO_36, GADI_GPIO_TYPE_OUTPUT_1/*SDIO_CARD_POWER_EN*/}, \
//#endif

#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                 }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_OUTPUT_SF_CS1                 }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_OUTPUT_SPI1_SO  /*lcd_sda*/      }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_OUTPUT_SPI1_SCLK/*lcd_scl*/      }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_OUTPUT_VD_DATA0 /*LCD_R*/ }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_OUTPUT_VD_DATA1           }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_OUTPUT_VD_DATA2           }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_OUTPUT_VD_DATA3           }, \
    { GADI_GPIO_8 , GADI_GPIO_TYPE_OUTPUT_VD_DATA4           }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_OUTPUT_VD_DATA5           }, \
    { GADI_GPIO_10 , GADI_GPIO_TYPE_OUTPUT_VD_DATA6           }, \
    { GADI_GPIO_11 , GADI_GPIO_TYPE_OUTPUT_VD_DATA7           }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_OUTPUT_1  /*lcd_reset*/   }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_OUTPUT_SPI1_CS0 /*lcd_cs*/}, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_OUTPUT_VD_VSYNC           }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_OUTPUT_VD_HSYNC           }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_OUTPUT_VD_CLOCK/*lcd_clk*/}, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_OUTPUT_0/*lcd_sel*/       }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_OUTPUT_0/*lcd_bl_en*/     }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_INPUT_1           /*IR_CUT-*/}, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX                }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX               }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_OUTPUT_1      /*Sensor reset*/}, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_I2C_DATA         /*S D*/}, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_INOUT_I2C_CLK          /*S C*/}, \
	SYSTEM_GPIO_SD_TABLE\
    { GADI_GPIO_37, GADI_GPIO_TYPE_INPUT_UART1_RX                       }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_OUTPUT_UART1_TX                       }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_INPUT_SD_CD_N                 }, \
    { GADI_GPIO_40, GADI_GPIO_TYPE_INPUT_0                       }, \
    //{ GADI_GPIO_41, GADI_GPIO_TYPE_INOUT_SD_DATA_3               }, \
    //{ GADI_GPIO_42, GADI_GPIO_TYPE_INOUT_SD_DATA_2               }, \
    //{ GADI_GPIO_43, GADI_GPIO_TYPE_INOUT_SD_CMD                  }, \
    //{ GADI_GPIO_44, GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
    //{ GADI_GPIO_45, GADI_GPIO_TYPE_INOUT_SD_DATA_1               }, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_OUTPUT_1/*SDIO_CARD_POWER_EN*/}, \
    //{ GADI_GPIO_47, GADI_GPIO_TYPE_INOUT_SD_DATA_0               }, \
    { GADI_GPIO_55, GADI_GPIO_TYPE_INPUT_0                       }, \
    SYSTEM_GPIO_INTPHY_TABLE

#define SYSTEM_GPIO_IR_LED_CTRL     GADI_GPIO_4  // not real pin
#define SYSTEM_GPIO_IR_CUT1         GADI_GPIO_20
#define SYSTEM_GPIO_IR_CUT2         GADI_GPIO_23
#define SYSTEM_GPIO_SENSOR_RESET    GADI_GPIO_27
#define SYSTEM_GPIO_PHY_SPEED_LED   GADI_GPIO_54

#define SYSTEM_GPIO_SPI0_EN0        GADI_GPIO_5  // not real pin
#define SYSTEM_GPIO_SPI1_EN0        GADI_GPIO_6  // not real pin
#define SYSTEM_GPIO_PWM0            GADI_GPIO_7  // not real pin
#define SYSTEM_GPIO_PWM1            GADI_GPIO_8  // not real pin
#define SYSTEM_GPIO_PWM2            GADI_GPIO_9  // not real pin
#define SYSTEM_GPIO_PWM3            GADI_GPIO_10 // not real pin
#define SYSTEM_GPIO_USB_HOST        GADI_GPIO_11 // not real pin
#define SYSTEM_GPIO_SD_DETECT       GADI_GPIO_39
#define SYSTEM_GPIO_SD_POWER        GADI_GPIO_46

#define SYSTEM_ETH_PHY_RESET_GPIO    GADI_GPIO_33

#define SYSTEM_GPIO_TEST_KEY        GADI_GPIO_40

#define SYSTEM_GPIO_LCD_BL_ENABLE    GADI_GPIO_19

#define SYSTEM_GPIO_LCD_ENABLE    GADI_GPIO_18


#endif /* _GPIO_RB_TW9912_H_ */
