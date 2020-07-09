#ifndef GK710X_HZD_H
#define GK710X_HZD_H

#include "adi_types.h"
#include "adi_gpio.h"

#define SYSTEM_USE_EXTERN_I2S       0
#define SYSTEM_USE_SDCARD           1
#define SYSTEM_USE_EXTERN_ETHPHY    0
#define SYSTEM_INIT_GD_GPIO         0

#define CONFIG_PHY_USE_AO_MCLK
#define CONFIG_SYSTEM_USE_SDCARD

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
#define SYSTEM_GADI_GPIO_SD_TABLE                              \
    { GADI_GPIO_40, GADI_GPIO_TYPE_INOUT_SD_DATA_3               }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_UNDEFINED                 }, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_INOUT_SD_DATA_0               }, \
    { GADI_GPIO_43, GADI_GPIO_TYPE_INOUT_SD_DATA_2               }, \
    { GADI_GPIO_44, GADI_GPIO_TYPE_INOUT_SD_DATA_1               }, \
    { GADI_GPIO_45, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_OUTPUT_1                      }, \
    { GADI_GPIO_48, GADI_GPIO_TYPE_INOUT_SD_CMD                  }, \
    { GADI_GPIO_50, GADI_GPIO_TYPE_INPUT_SD_CD_N                 },
#else
#define SYSTEM_GADI_GPIO_SD_TABLE                              \
    { GADI_GPIO_40, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_9           }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_UNDEFINED                       }, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_6           }, \
    { GADI_GPIO_43, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_7           }, \
    { GADI_GPIO_44, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_8           }, \
    { GADI_GPIO_45, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_3           }, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_4           }, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_5           }, \
    { GADI_GPIO_48, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_0           }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_1           }, \
    { GADI_GPIO_50, GADI_GPIO_TYPE_OUTPUT_AHB_DAC_DR_2           },
#endif
#define SYSTEM_GPIO_EXTPHY_TABLE                          \
    { GADI_GPIO_18, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXDV           }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXER           }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_OUTPUT_AOMCLK                 }, \
    { GADI_GPIO_53, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_0          }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_2   /*CLK*/}

#define SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_18, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_3             }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_0             }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_OUTPUT_AOMCLK                 }, \
    { GADI_GPIO_53, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_INPUT_0                       }

//------------------------system gpio map---------------------------
#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                 }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_OUTPUT_SF_CS1                 }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_INPUT_0 },					\
    { GADI_GPIO_3 , GADI_GPIO_TYPE_INPUT_0 }, 				\
    { GADI_GPIO_8 , GADI_GPIO_TYPE_INPUT_0       /* SPI0_HOLD */}, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_INPUT_0               }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_INPUT_0               }, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_OUTPUT_0  /* IR_CUT+ */       }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_OUTPUT_0  /* IR_CUT- */       }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_OUTPUT_0  /* IR_LED_CTRL */   }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_INPUT_0   /* IR_DET_ADC */    }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_OUTPUT_SPI0_CS0               }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_OUTPUT_SPI0_SCLK              }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_INPUT_UART0_RX                }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_OUTPUT_UART2_DTR_N/*RS485_RE*/}, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_OUTPUT_UART0_TX               }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_OUTPUT_UART1_TX               }, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_OUTPUT_UART2_TX               }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART1_RX                }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_INPUT_UART2_RX                }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_OUTPUT_1      /*Sensor reset*/}, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_I2C_DATA         /*S D*/}, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_INOUT_I2C_CLK          /*S C*/}, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_37, GADI_GPIO_TYPE_OUTPUT_0            /* PTZ  */}, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_INOUT_I2C_DATA2               }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_INOUT_I2C_CLK2                }, \
    SYSTEM_GADI_GPIO_SD_TABLE	\
    { GADI_GPIO_51, GADI_GPIO_TYPE_OUTPUT_AOBCLK                 }, \
    { GADI_GPIO_52, GADI_GPIO_TYPE_OUTPUT_AOLRCLK                }, \
	SYSTEM_GPIO_INTPHY_TABLE                          \



#define SYSTEM_GPIO_IR_CUT1                       GADI_GPIO_12
#define SYSTEM_GPIO_IR_CUT2                       GADI_GPIO_11

#define SYSTEM_ETH_PHY_RESET_GPIO                 GADI_GPIO_41
#define SYSTEM_GPIO_SENSOR_RESET    			  GADI_GPIO_27

#endif
