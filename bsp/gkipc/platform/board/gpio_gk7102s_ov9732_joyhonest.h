#ifndef GPIO_CFG_JOYHONEST_H_
#define GPIO_CFG_JOYHONEST_H_

#include "adi_types.h"
#include "adi_gpio.h"

#if defined(GK7102S_OV9732_JOYHONEST) 
#define CONFIG_MACH_GK7102S_OV9732_JOYHONEST
#endif

#if defined(GK7102S_QFN_OV9732_JH) 
#define CONFIG_MACH_GK7102S_QFN_OV9732_JH
#endif

#define CONFIG_PHY_USE_AO_MCLK
#define CONFIG_SYSTEM_USE_SDCARD
//#define CONFIG_PHY_USE_SD_CLK

#ifdef CONFIG_PHY_USE_AO_MCLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_OUTPUT_AOMCLK
#endif
#ifdef CONFIG_PHY_USE_SD_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_OUTPUT_SDIO_CLK
#endif
#ifdef CONFIG_PHY_USE_EXTERN_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_INPUT_0
#endif

#if defined(CONFIG_MACH_GK7102S_OV9732_JOYHONEST)

#ifdef CONFIG_SYSTEM_USE_EXTERN_I2S
#define SYSTEM_GPIO_I2S_TABLE                             \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_INPUT_CLK_AU                  }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_INPUT_I2S_WS                  }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_INPUT_I2S_SI                  }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_INPUT_I2S_CLK                 },
#else
#define SYSTEM_GPIO_I2S_TABLE                             \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_OUTPUT_SPI1_SO                }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_OUTPUT_SPI0_SO                }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_OUTPUT_SPI1_SCLK              }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_OUTPUT_PWM3_OUT               },
#endif

#ifdef CONFIG_SYSTEM_USE_SDCARD
#define SYSTEM_GPIO_SD_TABLE                              \
    { GADI_GPIO_2,  GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
	{ GADI_GPIO_58, GADI_GPIO_TYPE_INPUT_SD_CD_N                 }, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_INOUT_SD_CMD                  }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_INOUT_SD_DATA_0               }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_INOUT_SD_DATA_1               }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_INOUT_SD_DATA_2               }, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_INOUT_SD_DATA_3               }, \
    { GADI_GPIO_60, GADI_GPIO_TYPE_INOUT_SD1_DATA_0              }, \
    { GADI_GPIO_3,  GADI_GPIO_TYPE_INOUT_SD1_DATA_1              }, \
    { GADI_GPIO_56, GADI_GPIO_TYPE_INOUT_SD1_DATA_2              }, \
    { GADI_GPIO_59, GADI_GPIO_TYPE_INOUT_SD1_DATA_3              }, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_OUTPUT_SDIO1_CLK              }, \
    { GADI_GPIO_57, GADI_GPIO_TYPE_INOUT_SD1_CMD                 }, 
#endif

//------------------------system gpio map---------------------------
#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                 }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_8 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_INPUT_0			             }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_OUTPUT_1   /*Sensor pwdn*/    }, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX                }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX               }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_OUTPUT_1      /*Sensor reset*/}, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_I2C_DATA         /*S D*/}, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_INOUT_I2C_CLK          /*S C*/}, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_OUTPUT_0                      }, \
    { GADI_GPIO_37, GADI_GPIO_TYPE_INOUT_I2C_DATA2               }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_INOUT_I2C_CLK2                }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_INPUT_0                       }, \
    SYSTEM_GPIO_SD_TABLE\
    { GADI_GPIO_48, SYSTEM_GPIO_PHY_CLK                          }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_51, GADI_GPIO_TYPE_OUTPUT_1                      }, \
    { GADI_GPIO_52, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_53, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_3             }, \
    { GADI_GPIO_55, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_61, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_62, GADI_GPIO_TYPE_INPUT_0                       }

#define SYSTEM_GPIO_IR_CUT1         GADI_GPIO_49
#define SYSTEM_GPIO_IR_CUT2         GADI_GPIO_24
#define SYSTEM_GPIO_RED_LED_CTRL    GADI_GPIO_10		
#define SYSTEM_GPIO_BLUE_LED_CTRL   GADI_GPIO_9
#define SYSTEM_GPIO_SENSOR_RESET    GADI_GPIO_27
#define SYSTEM_GPIO_RECORD_CTRL     GADI_GPIO_47		
#define SYSTEM_GPIO_SNAP_CTRL       GADI_GPIO_50
#define SYSTEM_GPIO_PHY_SPEED_LED   GADI_GPIO_54

#define SYSTEM_GPIO_SPI0_EN0        GADI_GPIO_8		// not real pin
#define SYSTEM_GPIO_SPI1_EN0        GADI_GPIO_9		// not real pin
#define SYSTEM_GPIO_USB_HOST        GADI_GPIO_50 	// not real pin
#define SYSTEM_GPIO_SD_DETECT       GADI_GPIO_45
#define SYSTEM_GPIO_SD_POWER        GADI_GPIO_55 	// not real pin
#endif /***CONFIG_MACH_GK7102S_OV9732_JOYHONEST END***/



#if defined(CONFIG_MACH_GK7102S_QFN_OV9732_JH)

//------------------------system gpio map---------------------------
#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                 }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_OUTPUT_SF_CS1                 }, \
	{ GADI_GPIO_2 , GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_UNDEFINED                       }, \
	{ GADI_GPIO_4 , GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_INOUT_I2C_CLK          /*S C*/}, \
    { GADI_GPIO_8 , GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_UNDEFINED                       }, \
	{ GADI_GPIO_11, GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_UNDEFINED                       }, \
	{ GADI_GPIO_13, GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_INOUT_I2C_DATA         /*S D*/}, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_20, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_UNDEFINED			         }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_OUTPUT_1   /*Sensor pwdn*/   }, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX                }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX               }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_OUTPUT_1      /*Sensor reset*/ }, \
	{ GADI_GPIO_28, GADI_GPIO_TYPE_UNDEFINED                       }, \
	{ GADI_GPIO_29, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_32, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_33, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_34, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_35, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_36, GADI_GPIO_TYPE_INOUT_SD1_DATA_1              }, \
	{ GADI_GPIO_37, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_40, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_INOUT_SD_DATA_2               }, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_INOUT_SD_DATA_3               }, \
    { GADI_GPIO_43, GADI_GPIO_TYPE_INOUT_SD_CMD                  }, \
    { GADI_GPIO_44, GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
    { GADI_GPIO_45, GADI_GPIO_TYPE_INOUT_SD_DATA_0               }, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_INOUT_SD_DATA_1               }, \
	{ GADI_GPIO_47, GADI_GPIO_TYPE_INPUT_SD_CD_N                 }, \
    { GADI_GPIO_48, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_50, GADI_GPIO_TYPE_UNDEFINED                     }, \
	{ GADI_GPIO_51, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_52, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_53, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_3             }, \
    { GADI_GPIO_55, GADI_GPIO_TYPE_UNDEFINED                     }, \
    { GADI_GPIO_56, GADI_GPIO_TYPE_INOUT_SD1_DATA_2              }, \
    { GADI_GPIO_57, GADI_GPIO_TYPE_OUTPUT_SDIO1_CLK              }, \
    { GADI_GPIO_58, GADI_GPIO_TYPE_INOUT_SD1_CMD                 }, \
    { GADI_GPIO_59, GADI_GPIO_TYPE_INOUT_SD1_DATA_3              }, \
    { GADI_GPIO_60, GADI_GPIO_TYPE_INOUT_SD1_DATA_0              }, \
	{ GADI_GPIO_61, GADI_GPIO_TYPE_INOUT_I2C_DATA2               }, \
    { GADI_GPIO_62, GADI_GPIO_TYPE_INOUT_I2C_CLK2                }

#define SYSTEM_GPIO_IR_CUT1         GADI_GPIO_32
#define SYSTEM_GPIO_IR_CUT2         GADI_GPIO_31
#define SYSTEM_GPIO_RED_LED_CTRL    GADI_GPIO_6		
#define SYSTEM_GPIO_BLUE_LED_CTRL   GADI_GPIO_5
#define SYSTEM_GPIO_SENSOR_RESET    GADI_GPIO_27
#define SYSTEM_GPIO_PHY_RESET       GADI_GPIO_30
#define SYSTEM_GPIO_PHY_SPEED_LED   GADI_GPIO_33

#define SYSTEM_GPIO_RECORD_CTRL     GADI_GPIO_20		
#define SYSTEM_GPIO_SNAP_CTRL       GADI_GPIO_21


#endif /*CONFIG_MACH_GK7102S_QFN_OV9732_JH END*/


#endif /* GPIO_CFG_JOYHONEST_H_ */
