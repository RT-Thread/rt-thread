/*
 * File Name	 board_config.h
 * Descriptions	 PIN /Version
 * Change Logs
 * Date             Author       Notes
 * 2020-11-23       Eric     	 first implementation
*/

#ifndef DRIVERS_INCLUDE_INCLUDE_USER_BOARD_CONFIG_H_
#define DRIVERS_INCLUDE_INCLUDE_USER_BOARD_CONFIG_H_

/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <board.h>
#include <stdint.h>
#include <stdbool.h>

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/* ########################### PIN USE Selection ############################ */
#define CHARGE_PIN
#define SWITCH_PIN
#define OLED_PIN
#define ADC_PIN
#define RGB_PIN
#define BME280_PIN
#define RSCDRRM020NDSE3_PIN

/* ########################### Command Selection ############################ */
#define BOARD_VERSION

/*----------------------------------------------------------------------------*
**                                                                            *
**                            Board Version Define                            *
**                                                                            *
**----------------------------------------------------------------------------*/
//#define BOARD_VERSION
#ifdef BOARD_VERSION
#define BUILD (__DATE__ " " __TIME__)
#define VERSION ("V 1.1")
#endif

/*----------------------------------------------------------------------------*
**                                                                            *
**                          Board Pin Map Definitions                         *
**                                                                            *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                       Charge pin configuration                             *
**----------------------------------------------------------------------------*/
//#define CHARGE_PIN
#ifdef CHARGE_PIN
#define CHARGE_S_PIN       GET_PIN(C,8)    //Charge status indicator output (open drain)
#define CHARGE_D_PIN       GET_PIN(C,7)    //Power good indicator output (open drain)
#endif

/*----------------------------------------------------------------------------*
**                       Switch pin configuration                             *
**----------------------------------------------------------------------------*/
//#define SWITCH_PIN
#ifdef SWITCH_PIN
#define SWITCH_INT_PIN     GET_PIN(A,8)
#define SWITCH_KILL_PIN    GET_PIN(C,9)
#endif
/*----------------------------------------------------------------------------*
**                       Oled pin configuration                             *
**----------------------------------------------------------------------------*/
//#define OLED_PIN
#ifdef OLED_PIN
/* OLED POWER CONFIGURATION*/
#define OLED_POWER_PIN     GET_PIN(A , 2)    //PA2   Power configuration High active
/* OLED  CONFIGURATION  */
#define OLED_SPI_PIN_RES   GET_PIN(A , 4)    //PA4   This is a reset signal input pad.
#define OLED_SPI_PIN_DC    GET_PIN(A , 6)    //PA6   This is the Data/Command control pads that determines whether the data bits are data or a command.
#define OLED_SPI_PIN_CS    GET_PIN(A , 3)    //PA3   This pad is the chip select input
/*In u8x8.h  U8X8_USE_PIN  */
#define U8G2_PIN_UP        GET_PIN(E,2)    //PE2   KEY3 Low active
#define U8G2_PIN_DOWN      GET_PIN(E,3)    //PE3   KEY2 Low active
#define U8G2_PIN_LEFT      U8X8_PIN_NONE   //NONE
#define U8G2_PIN_RIGHT     GET_PIN(E,4)    //PE4   KEY1 Low active
#define U8G2_PIN_SELECT    GET_PIN(E,5)    //PE5   KEY0 Low active
#define U8G2_PIN_HOME      GET_PIN(E,6)//8X8_PIN_NONE    //NONE
#endif

/*----------------------------------------------------------------------------*
**                       Li ADC pin configuration                             *
**----------------------------------------------------------------------------*/
//#define ADC_PIN
#ifdef ADC_PIN
#define ADC_VIN_LIN_PIN    GET_PIN(A,1)
#endif

/*----------------------------------------------------------------------------*
**                          RGB pin configuration                             *
**----------------------------------------------------------------------------*/
//#define RGB_PIN
#ifdef RGB_PIN
#define LIGHT_B_PIN        GET_PIN(E,9)    //PE9   B_TIM1_CH1
#define LIGHT_G_PIN        GET_PIN(E,11)   //PE11  G_TIM1_CH2
#define LIGHT_R_PIN        GET_PIN(E,13)   //PE13  R_TIM1_CH3
#endif

/*----------------------------------------------------------------------------*
**                           BME280 configuration                             *
**----------------------------------------------------------------------------*/
//#define BME280_PIN
#ifdef BME280_PIN
#define BME280_SDO_PIN            GET_PIN(B,5)  //
#define BME280_SCL_PIN            GET_PIN(B,8)  //95
#define BME280_SDA_PIN            GET_PIN(B,9)  //96
#endif

/*----------------------------------------------------------------------------*
**                 RSCDRRM020NDSE3 pin configuration                          *
**----------------------------------------------------------------------------*/
//#define RSCDRRM020NDSE3_PIN
#ifdef RSCDRRM020NDSE3_PIN
#define RSCDRRM020NDSE3_PWER_EN_PIN		GET_PIN(B, 11)/* defined the PWER_EN pin: PB11 */
#define RSCDRRM020NDSE3_RDY_PIN			GET_PIN(B, 12)/* defined the RDY pin: PB12 */
#define RSCDRRM020NDSE3_CS_AD_PIN	 	GET_PIN(B, 10)/* defined the CS_ADC pin: PB10 */
#define RSCDRRM020NDSE3_CS_EE_PIN	 	GET_PIN(E, 15)/* defined the CS_EE pin: PE15 */
#endif

/*----------------------------------------------------------------------------*
**                           BT pin configuration                             *
**----------------------------------------------------------------------------*/


/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
#endif /* DRIVERS_INCLUDE_INCLUDE_USER_BOARD_CONFIG_H_ */
