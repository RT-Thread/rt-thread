#ifndef _GPIO_RB_JXH42_H_
#define _GPIO_RB_JXH42_H_

#include "adi_types.h"
#include "adi_gpio.h"

#if defined(GK7102_JXH42_V10) || defined(GK7102S_JXH42_V10)
#define CONFIG_MACH_GK7102_RB_JXH42_V1_00
#endif

#if defined(GK7102_JXH42_V20) || defined(GK7102S_JXH42_V20)
#define CONFIG_MACH_GK7102_RB_JXH42_V2_00
#endif

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

#if defined(CONFIG_MACH_GK7102_RB_JXH42_V1_00)
#define SYSTEM_GPIO_EXTPHY_TABLE                          \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_INPUT_ENET_PHY_RXER           }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_OUTPUT_ENET_GMII_MDC_O        }, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_1          }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_INOUT_ETH_MDIO                }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_RESET         /*ETH reset*/}, \
    { GADI_GPIO_43, SYSTEM_GPIO_PHY_CLK                     }, \
    { GADI_GPIO_44, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_TXEN          }, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_1         }, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_0         }, \
    { GADI_GPIO_48, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_50, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_2   /*CLK*/}, \
    { GADI_GPIO_51, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXDV           }, \
    { GADI_GPIO_52, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_0          },

#define SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_43, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_44, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_48, SYSTEM_GPIO_PHY_CLK                     }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_3             }, \
    { GADI_GPIO_50, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_51, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_52, GADI_GPIO_TYPE_INPUT_0                       },

#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                 }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_OUTPUT_SF_CS1                 }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_8 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_OUTPUT_0       /*IR_LED_CTRL*/}, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_INPUT_0         /*IR_DET_ADC*/}, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_OUTPUT_0           /*IR_CUT+*/}, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_OUTPUT_0           /*IR_CUT-*/}, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_OUTPUT_1      /*Sensor reset*/}, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_I2C_DATA         /*S D*/}, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_INOUT_I2C_CLK          /*S C*/}, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_OUTPUT_UART0_TX               }, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_INPUT_UART0_RX                }, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_INOUT_I2C_DATA2               }, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_INOUT_I2C_CLK2                }, \
    { GADI_GPIO_37, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_40, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_45, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_53, GADI_GPIO_TYPE_INPUT_0        /* ALARM_OUT */}, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_INPUT_0         /* ALARM_IN */}, \
    { GADI_GPIO_55, GADI_GPIO_TYPE_INPUT_0                       }, \
	SYSTEM_GPIO_INTPHY_TABLE

#define SYSTEM_GPIO_IR_LED_CTRL     GADI_GPIO_12
#define SYSTEM_GPIO_IR_CUT1         GADI_GPIO_20
#define SYSTEM_GPIO_IR_CUT2         GADI_GPIO_23
#define SYSTEM_GPIO_SENSOR_RESET    GADI_GPIO_27
#define SYSTEM_GPIO_PHY_SPEED_LED   GADI_GPIO_49

#define SYSTEM_GPIO_SPI0_EN0        GADI_GPIO_37 // not real pin
#define SYSTEM_GPIO_SPI1_EN0        GADI_GPIO_38 // not real pin
#define SYSTEM_GPIO_PWM0            GADI_GPIO_39 // not real pin
#define SYSTEM_GPIO_PWM1            GADI_GPIO_40 // not real pin
#define SYSTEM_GPIO_PWM2            GADI_GPIO_42 // not real pin
#define SYSTEM_GPIO_PWM3            GADI_GPIO_45 // not real pin
#define SYSTEM_GPIO_USB_HOST        GADI_GPIO_55 // not real pin
#define SYSTEM_GPIO_SD_DETECT       GADI_GPIO_4  // not real pin
#define SYSTEM_GPIO_SD_POWER        GADI_GPIO_5  // not real pin

#define SYSTEM_ETH_PHY_RESET_GPIO    GADI_GPIO_33

#endif /* CONFIG_MACH_GK7102_RB_JXH42_V1_00 */

#if defined(CONFIG_MACH_GK7102_RB_JXH42_V2_00)
#define SYSTEM_GPIO_EXTPHY_TABLE                          \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_INPUT_ENET_PHY_RXDV           }, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_TXEN          }, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_1         }, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_0         }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXER           }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_OUTPUT_ENET_GMII_MDC_O        }, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_INOUT_ETH_MDIO                }, \
    { GADI_GPIO_48, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_OUTPUT_ENET_PHY_RESET         /*ETH reset*/}, \
    { GADI_GPIO_50, SYSTEM_GPIO_PHY_CLK                     }, \
    { GADI_GPIO_51, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_1          }, \
    { GADI_GPIO_52, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_2   /*CLK*/}, \
    { GADI_GPIO_53, GADI_GPIO_TYPE_INPUT_ENET_PHY_RXD_0          }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_INPUT_0                         },

#define SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_48, SYSTEM_GPIO_PHY_CLK                     }, \
    { GADI_GPIO_49, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_50, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_51, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_52, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_53, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_54, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_3             },

#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                 }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_OUTPUT_SF_CS1                 }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_6 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_7 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_8 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_OUTPUT_0       /*IR_LED_CTRL*/}, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_INPUT_0           /*IR_DET_ADC*/}, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_OUTPUT_0           /*IR_CUT+*/}, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_OUTPUT_0           /*IR_CUT-*/}, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_INPUT_0                         }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX                }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX               }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_OUTPUT_1      /*Sensor reset*/}, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_I2C_DATA         /*S D*/}, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_INOUT_I2C_CLK          /*S C*/}, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_37, GADI_GPIO_TYPE_INPUT_UART1_RX                       }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_OUTPUT_UART1_TX                       }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_INPUT_SD_CD_N                 }, \
    { GADI_GPIO_40, GADI_GPIO_TYPE_INPUT_0                       }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_INOUT_SD_DATA_3               }, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_INOUT_SD_DATA_2               }, \
    { GADI_GPIO_43, GADI_GPIO_TYPE_INOUT_SD_CMD                  }, \
    { GADI_GPIO_44, GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
    { GADI_GPIO_45, GADI_GPIO_TYPE_INOUT_SD_DATA_1               }, \
    { GADI_GPIO_46, GADI_GPIO_TYPE_OUTPUT_1/*SDIO_CARD_POWER_EN*/}, \
    { GADI_GPIO_47, GADI_GPIO_TYPE_INOUT_SD_DATA_0               }, \
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

#endif /* CONFIG_MACH_GK7102_RB_JXH42_V2_00 */

#endif /* _GPIO_RB_JXH42_H_ */
