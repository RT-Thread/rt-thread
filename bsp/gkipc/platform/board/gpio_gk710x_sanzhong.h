#ifndef GK710X_SANZHONG_H
#define GK710X_SANZHONG_H

#include "adi_types.h"
#include "adi_gpio.h"

#define SYSTEM_USE_EXTERN_I2S       0
#define SYSTEM_USE_SDCARD           1
#define SYSTEM_USE_EXTERN_ETHPHY    0
#define SYSTEM_INIT_GD_GPIO         0

#define CONFIG_PHY_USE_AO_MCLK
#define CONFIG_SYSTEM_USE_SDCARD

#ifdef CONFIG_PHY_USE_AO_MCLK
    #define SYSTEM_GPIO_PHY_CLK     GD_GPIO_TYPE_OUTPUT_AOMCLK
#endif
#ifdef CONFIG_PHY_USE_SD_CLK
    #define SYSTEM_GPIO_PHY_CLK     GD_GPIO_TYPE_OUTPUT_SDIO_CLK
#endif
#ifdef CONFIG_PHY_USE_EXTERN_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_INPUT_0
#endif


#ifdef CONFIG_SYSTEM_USE_SDCARD
#define SYSTEM_GADI_GPIO_SD_TABLE                         \
    { GADI_GPIO_2, GADI_GPIO_TYPE_INOUT_SD_DATA_3                }, \
    { GADI_GPIO_3, GADI_GPIO_TYPE_INOUT_SD_CMD                   }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_INOUT_SD_DATA_0               }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_INPUT_SD_CD_N                 }, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_INOUT_SD_DATA_1               }, \
    { GADI_GPIO_40, GADI_GPIO_TYPE_OUTPUT_1    /*power enable */ }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_INOUT_SD_DATA_2               }, 
#else
#define SYSTEM_GADI_GPIO_SD_TABLE                         \
    { GADI_GPIO_2,  GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_3,  GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_40, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_INPUT_0                       },  
#endif

#define SYSTEM_GPIO_EXTPHY_TABLE                          \
    { GADI_GPIO_19, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_INPUT_0                       }, 

#define SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_19, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_3             }, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_OUTPUT_AOMCLK                 }, 

//------------------------system gpio map---------------------------
#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                 }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_OUTPUT_SF_CS1                 }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_INOUT_I2C_DATA2               }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_INOUT_I2C_CLK2                }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_OUTPUT_0     /* wifi enable */}, \
    { GADI_GPIO_8 , GADI_GPIO_TYPE_OUTPUT_0   /* sensor enable */}, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_OUTPUT_0         /* led ctrl*/}, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_INPUT_0       /* set default*/}, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_INPUT_0      /* sensor PWDNF*/}, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_OUTPUT_0       /* SPK Enable*/}, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX                }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX               }, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_I2C_DATA                }, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_INOUT_I2C_CLK                 }, \
    { GADI_GPIO_37, GADI_GPIO_TYPE_INPUT_UART1_RX                }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_OUTPUT_UART1_TX               }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_43, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_44, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_45, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_48, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    SYSTEM_GADI_GPIO_SD_TABLE                         

#define SYSTEM_GPIO_IR_CUT1                    GADI_GPIO_20
#define SYSTEM_GPIO_IR_CUT2                    0xFF

#define SYSTEM_ETH_PHY_RESET_GPIO              0xFF
#define SYSTEM_GPIO_SENSOR_RESET    		   GADI_GPIO_27

#define SYSTEM_GPIO_SENSOR_ENABLE              GADI_GPIO_8
#define SYSTEM_GPIO_SENSOR_PWDNF               GADI_GPIO_13
#define SYSTEM_GPIO_WIFI_ENABLE                GADI_GPIO_7
#define SYSTEM_GPIO_LED_CTRL                   GADI_GPIO_10
#define SYSTEM_GPIO_SPI_SETDEFAULT             GADI_GPIO_11 
#define SYSTEM_GPIO_SPK_ENABLE                 GADI_GPIO_17 
#define SYSTEM_GPIO_SD_POWER                   GADI_GPIO_40 
#endif
