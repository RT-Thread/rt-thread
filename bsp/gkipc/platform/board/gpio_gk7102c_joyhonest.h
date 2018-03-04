#ifndef GADI_GPIO_CFG_JOYHONEST_H
#define GADI_GPIO_CFG_JOYHONEST_H
#include "adi_types.h"
#include "adi_gpio.h"


#define CONFIG_PHY_USE_AO_MCLK
#define CONFIG_SYSTEM_USE_SDCARD

////
#define SYSTEM_USE_EXTERN_I2S       1
#define SYSTEM_USE_SDCARD           1
#define SYSTEM_USE_EXTERN_ETHPHY    0
#define SYSTEM_INIT_GADI_GPIO       1
/////

#ifdef CONFIG_PHY_USE_AO_MCLK
    #define SYSTEM_GADI_GPIO_PHY_CLK     GADI_GPIO_TYPE_UNDEFINED
#endif
#ifdef CONFIG_PHY_USE_SD_CLK
    #define SYSTEM_GADI_GPIO_PHY_CLK     GADI_GPIO_TYPE_UNDEFINED
#endif
#ifdef CONFIG_PHY_USE_EXTERN_CLK
    #define SYSTEM_GADI_GPIO_PHY_CLK     GADI_GPIO_TYPE_UNDEFINED
#endif

#if 1
#define SYSTEM_GPIO_EXTPHY_TABLE                          \
    { GADI_GPIO_32, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_0    },
#define SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_32, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_0    },

#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                  }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_UNDEFINED /*sensor rst*/        }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_INOUT_I2C_CLK                  }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_INOUT_I2C_DATA                 }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_OUTPUT_SDIO_CLK               }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_INOUT_SD_CMD                  }, \
    { GADI_GPIO_6,  GADI_GPIO_TYPE_INOUT_SD1_DATA_1     	          }, \
    { GADI_GPIO_7,  GADI_GPIO_TYPE_INOUT_SD1_DATA_2                }, \
    { GADI_GPIO_8,  GADI_GPIO_TYPE_INOUT_SD1_CMD                   }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_INOUT_SD1_DATA_0          	  }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_INOUT_SD1_DATA_3            	  }, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_INPUT_SPI0_SI     /*U28 D*/    }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_OUTPUT_SDIO1_CLK                }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_UNDEFINED         		      }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_UNDEFINED      		          }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_UNDEFINED             		  }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_UNDEFINED            	      }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_UNDEFINED    			      }, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_INPUT_SD1_CD_N        		  }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_UNDEFINED     		          }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_UNDEFINED    			      }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_UNDEFINED  			          }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_UNDEFINED   				      }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_INOUT_SD_DATA_1   			  }, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_INOUT_SD_DATA_0    			  }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX  				  }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX  			  }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_INOUT_SD_DATA_3 			  }, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_SD_DATA_2 /*S D*/       }, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_UNDEFINED  /*S C*/             }, \
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
#define SYSTEM_GPIO_IR_CUT1         GADI_GPIO_NUM
#define SYSTEM_GPIO_IR_CUT2         GADI_GPIO_NUM
#define SYSTEM_GPIO_SENSOR_RESET    GADI_GPIO_1
#define SYSTEM_GPIO_PHY_RESET       GADI_GPIO_32
#define SYSTEM_GPIO_PHY_SPEED_LED   GADI_GPIO_NUM

#define SYSTEM_GPIO_SPI0_EN0        GADI_GPIO_NUM
#define SYSTEM_GPIO_SPI1_EN0        GADI_GPIO_NUM
#define SYSTEM_GPIO_USB_HOST        GADI_GPIO_15
#define SYSTEM_GPIO_SD_DETECT       GADI_GPIO_NUM
#define SYSTEM_GPIO_SD_POWER        GADI_GPIO_NUM // not real pin
#define SYSTEM_GPIO_PMU_CTL         GADI_GPIO_NUM // not real pin, only for test
#define SYSTEM_GPIO_LCD_BL_EN       GADI_GPIO_NUM  /*lcd_bl_en*/
#else

#define SYSTEM_GPIO_EXTPHY_TABLE                          \
    { GADI_GPIO_32, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_0    },
#define SYSTEM_GPIO_INTPHY_TABLE                          \
    { GADI_GPIO_32, GADI_GPIO_TYPE_OUTPUT_EPHY_LED_0    },

#define SYSTEM_GPIO_XREF_TABLE                            \
    { GADI_GPIO_0 , GADI_GPIO_TYPE_OUTPUT_SF_CS0                  }, \
    { GADI_GPIO_1 , GADI_GPIO_TYPE_UNDEFINED /*sensor rst*/        }, \
    { GADI_GPIO_2 , GADI_GPIO_TYPE_INOUT_I2C_CLK                  }, \
    { GADI_GPIO_3 , GADI_GPIO_TYPE_INOUT_I2C_DATA                 }, \
    { GADI_GPIO_4 , GADI_GPIO_TYPE_OUTPUT_SDIO1_CLK               }, \
    { GADI_GPIO_5 , GADI_GPIO_TYPE_INOUT_SD1_CMD                  }, \
    { GADI_GPIO_6,  GADI_GPIO_TYPE_INOUT_SD_DATA_1     	          }, \
    { GADI_GPIO_7,  GADI_GPIO_TYPE_INOUT_SD_DATA_2                }, \
    { GADI_GPIO_8,  GADI_GPIO_TYPE_INOUT_SD_CMD                   }, \
    { GADI_GPIO_9 , GADI_GPIO_TYPE_INOUT_SD_DATA_0          	  }, \
    { GADI_GPIO_10, GADI_GPIO_TYPE_INOUT_SD_DATA_3            	  }, \
    { GADI_GPIO_11, GADI_GPIO_TYPE_INPUT_SPI0_SI     /*U28 D*/   }, \
    { GADI_GPIO_12, GADI_GPIO_TYPE_OUTPUT_SDIO_CLK                }, \
    { GADI_GPIO_13, GADI_GPIO_TYPE_UNDEFINED         		      }, \
    { GADI_GPIO_14, GADI_GPIO_TYPE_UNDEFINED      		          }, \
    { GADI_GPIO_15, GADI_GPIO_TYPE_UNDEFINED             		  }, \
    { GADI_GPIO_16, GADI_GPIO_TYPE_UNDEFINED            	      }, \
    { GADI_GPIO_17, GADI_GPIO_TYPE_UNDEFINED    			      }, \
    { GADI_GPIO_18, GADI_GPIO_TYPE_INPUT_SD1_CD_N        		  }, \
    { GADI_GPIO_19, GADI_GPIO_TYPE_UNDEFINED     		          }, \
    { GADI_GPIO_20, GADI_GPIO_TYPE_UNDEFINED    			      }, \
    { GADI_GPIO_21, GADI_GPIO_TYPE_UNDEFINED  			          }, \
    { GADI_GPIO_22, GADI_GPIO_TYPE_UNDEFINED   				      }, \
    { GADI_GPIO_23, GADI_GPIO_TYPE_INOUT_SD1_DATA_1   			  }, \
    { GADI_GPIO_24, GADI_GPIO_TYPE_INOUT_SD1_DATA_0    			  }, \
    { GADI_GPIO_25, GADI_GPIO_TYPE_INPUT_UART0_RX  				  }, \
    { GADI_GPIO_26, GADI_GPIO_TYPE_OUTPUT_UART0_TX  			  }, \
    { GADI_GPIO_27, GADI_GPIO_TYPE_INOUT_SD1_DATA_3 			  }, \
    { GADI_GPIO_28, GADI_GPIO_TYPE_INOUT_SD1_DATA_2 /*S D*/       }, \
    { GADI_GPIO_29, GADI_GPIO_TYPE_UNDEFINED  /*S C*/             }, \
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
#define SYSTEM_GPIO_IR_CUT1         GADI_GPIO_NUM
#define SYSTEM_GPIO_IR_CUT2         GADI_GPIO_NUM
#define SYSTEM_GPIO_SENSOR_RESET    GADI_GPIO_1
#define SYSTEM_GPIO_PHY_RESET       GADI_GPIO_32
#define SYSTEM_GPIO_PHY_SPEED_LED   GADI_GPIO_NUM

#define SYSTEM_GPIO_SPI0_EN0        GADI_GPIO_NUM
#define SYSTEM_GPIO_SPI1_EN0        GADI_GPIO_NUM
#define SYSTEM_GPIO_USB_HOST        GADI_GPIO_15
#define SYSTEM_GPIO_SD_DETECT       GADI_GPIO_NUM
#define SYSTEM_GPIO_SD_POWER        GADI_GPIO_NUM // not real pin
#define SYSTEM_GPIO_PMU_CTL         GADI_GPIO_NUM // not real pin, only for test


#endif 


#endif /*GADI_GPIO_CFG_JOYHONEST_H*/
