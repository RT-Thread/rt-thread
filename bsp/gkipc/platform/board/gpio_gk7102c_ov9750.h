#ifndef GPIO_CFG_GK7101C_OV9750_H
#define GPIO_CFG_GK7101C_OV9750_H
#include "adi_types.h"
#include "adi_gpio.h"

#define SYSTEM_USE_EXTERN_I2S       1
#define SYSTEM_USE_SDCARD           0
#define SYSTEM_GPIO_INTPHY_TABLE    0


#if SYSTEM_USE_EXTERN_I2S == 1
#define SYSTEM_GPIO_I2S_TABLE                              \

#else
#define SYSTEM_GPIO_I2S_TABLE                              \

#endif

#ifdef CONFIG_PHY_USE_AO_MCLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_UNDEFINED
#endif
#ifdef CONFIG_PHY_USE_SD_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_UNDEFINED
#endif
#ifdef CONFIG_PHY_USE_EXTERN_CLK
    #define SYSTEM_GPIO_PHY_CLK     GADI_GPIO_TYPE_UNDEFINED
#endif

#define SYSTEM_GPIO_EXTPHY_TABLE                          \
    { GADI_GPIO_18, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_0    },
#define SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_18, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_0    },

#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                  }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_UNDEFINED /*sensor rst*/         }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_6,  GADI_GPIO_TYPE_UNDEFINED     			      }, \
    { GADI_GPIO_7,  GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_8,  GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_UNDEFINED          			  }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_UNDEFINED            		  }, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_UNDEFINED         		      }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_INOUT_I2C_DATA      		      }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_UNDEFINED             		  }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_UNDEFINED                	  }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_INOUT_I2C_CLK    			  }, \
    SYSTEM_GPIO_INTPHY_TABLE\
    { GADI_GPIO_19, GADI_GPIO_TYPE_UNDEFINED     		          }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_UNDEFINED    			      }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_UNDEFINED  			          }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_UNDEFINED   				      }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_UNDEFINED   			          }, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_UNDEFINED    			      }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX  				  }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX  			  }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_UNDEFINED 				      }, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_30, GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_31, GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_32, GADI_GPIO_TYPE_UNDEFINED                      }, \
    { GADI_GPIO_33, GADI_GPIO_TYPE_UNDEFINED        			  }, \
    { GADI_GPIO_34, GADI_GPIO_TYPE_UNDEFINED         			  }, \
    { GADI_GPIO_35, GADI_GPIO_TYPE_UNDEFINED         			  }, \
    { GADI_GPIO_36, GADI_GPIO_TYPE_UNDEFINED        			  }, \
    { GADI_GPIO_37, GADI_GPIO_TYPE_UNDEFINED        			  }, \
    { GADI_GPIO_38, GADI_GPIO_TYPE_UNDEFINED        			  }, \
    { GADI_GPIO_39, GADI_GPIO_TYPE_UNDEFINED        			  }, \
    { GADI_GPIO_40, GADI_GPIO_TYPE_UNDEFINED         		      }, \
    { GADI_GPIO_41, GADI_GPIO_TYPE_UNDEFINED         		      }, \
    { GADI_GPIO_42, GADI_GPIO_TYPE_UNDEFINED          			  }

#define SYSTEM_GPIO_IR_LED_CTRL     GADI_GPIO_NUM
#define SYSTEM_GPIO_IR_CUT1         GADI_GPIO_15
#define SYSTEM_GPIO_IR_CUT2         GADI_GPIO_16
#define SYSTEM_GPIO_SENSOR_RESET    GADI_GPIO_1
#define SYSTEM_GPIO_PHY_RESET       GADI_GPIO_NUM
#define SYSTEM_GPIO_PHY_SPEED_LED   GADI_GPIO_NUM

#define SYSTEM_GPIO_SPI0_EN0        GADI_GPIO_NUM
#define SYSTEM_GPIO_SPI1_EN0        GADI_GPIO_NUM
#define SYSTEM_GPIO_USB_HOST        GADI_GPIO_NUM

#endif /*GPIO_CFG_GK7101C_OV9750_H*/
