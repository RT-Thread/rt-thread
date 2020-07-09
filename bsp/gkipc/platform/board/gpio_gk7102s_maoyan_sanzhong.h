#ifndef GPIO_CFG_SANZHONF_H_
#define GPIO_CFG_SANZHONF_H_

#include "adi_types.h"
#include "adi_gpio.h"

#define CONFIG_PHY_USE_AO_MCLK
#define CONFIG_SYSTEM_USE_SDCARD
//#define CONFIG_PHY_USE_SD_CLK
#define SYSTEM_INIT_GADI_GPIO       1

#ifdef CONFIG_PHY_USE_AO_MCLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_OUTPUT_AOMCLK
#endif
#ifdef CONFIG_PHY_USE_SD_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_OUTPUT_SDIO_CLK
#endif
#ifdef CONFIG_PHY_USE_EXTERN_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_INPUT_0
#endif

#ifdef CONFIG_SYSTEM_USE_SDCARD
#define SYSTEM_GPIO_SD_TABLE                              \
    { GADI_GPIO_44, GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
    { GADI_GPIO_43, GADI_GPIO_TYPE_INOUT_SD_CMD                  }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_INPUT_SD_CD_N                 }, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_INOUT_SD_DATA_0               }, \
    { GADI_GPIO_45, GADI_GPIO_TYPE_INOUT_SD_DATA_1               }, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_INOUT_SD_DATA_2               }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_INOUT_SD_DATA_3               }, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_INOUT_SD1_DATA_0              }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_INOUT_SD1_DATA_1              }, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_INOUT_SD1_DATA_2              }, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_INOUT_SD1_DATA_3              }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_OUTPUT_SDIO1_CLK              }, \
	{ GADI_GPIO_36, GADI_GPIO_TYPE_INPUT_SD1_CD_N                }, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_INOUT_SD1_CMD                 }, 
#endif

#if SYSTEM_INIT_GADI_GPIO == 1
#define SYSTEM_GPIO_XREF_TABLE                      \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0             }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_OUTPUT_SF_CS1             }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_OUTPUT_SPI1_SO  /*lcd_sda*/      }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_OUTPUT_SPI1_SCLK/*lcd_scl*/      }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_OUTPUT_VD_DATA2 /*LCD_R*/ }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_OUTPUT_VD_DATA3           }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_OUTPUT_VD_DATA4           }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_OUTPUT_VD_DATA5           }, \
    { GADI_GPIO_8 , GADI_GPIO_TYPE_OUTPUT_VD_DATA6           }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_OUTPUT_VD_DATA7           }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_OUTPUT_1  /*lcd_reset*/   }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_OUTPUT_SPI1_CS0 /*lcd_cs*/}, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_OUTPUT_VD_VSYNC           }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_OUTPUT_VD_HSYNC           }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_OUTPUT_VD_CLOCK/*lcd_clk*/}, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_OUTPUT_0/*lcd_sel*/       }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_OUTPUT_0/*lcd_bl_en*/     }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_OUTPUT_0/*ir_cut*/        }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_OUTPUT_0                  }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_OUTPUT_0                  }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_OUTPUT_0                  }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX            }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX           }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_UNDEFINED /*sensor reset*/}, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_I2C_DATA/*SDA*/     }, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_INOUT_I2C_CLK /*SCL*/     }, \
    SYSTEM_GPIO_SD_TABLE\
    { GADI_GPIO_37, GADI_GPIO_TYPE_INPUT_UART1_RX            }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_OUTPUT_UART1_TX           }
#endif /*USE_LCD_RGB280H45P01*/

#define SYSTEM_GPIO_IR_CUT1          GADI_GPIO_20
#define SYSTEM_GPIO_IR_CUT2          GADI_GPIO_NUM

#define SYSTEM_GPIO_WIFI_LED         GADI_GPIO_21
#define SYSTEM_GPIO_SPK_EN           GADI_GPIO_22
#define SYSTEM_GPIO_RINGER_CONTROL   GADI_GPIO_23
#define SYSTEM_GPIO_SENSOR_RESET     GADI_GPIO_27
#define SYSTEM_GPIO_NETWORK_PHY_CLK  GADI_GPIO_48
#define SYSTEM_GPIO_KEY1             GADI_GPIO_50
#define SYSTEM_GPIO_LCD_BL_EN        GADI_GPIO_19  /*lcd_bl_en*/

#endif /* GPIO_CFG_JOYHONEST_H_ */
