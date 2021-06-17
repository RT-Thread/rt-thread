/*!
 *   \file  	 cmd_parser.c
 *   \brief	     uart and usb command parser /ARM/IAR/GCC compiler
 *   \details
 *   \Change Logs
 *   \date           \author           \Notes
 *   2020-11-23      Eric -  first implementation
*/
#ifndef __RSCDRRM020NDSE3COPY_H__
#define __RSCDRRM020NDSE3COPY_H__

/*
 --------------------------------------------------------------------------------
    Dependencies
 --------------------------------------------------------------------------------
 */
/* <Header file of standard Library> */
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <stdbool.h>
/*----------------------------------------------------------------------------*/
/* "Header file of nonstandard Library" */

/*
 --------------------------------------------------------------------------------
    Debugging Flag
 --------------------------------------------------------------------------------
 */

 /*
 --------------------------------------------------------------------------------
    Compiler Flag
 --------------------------------------------------------------------------------
 */
#ifdef __cplusplus
extern   "C"
{
#endif
/*
 --------------------------------------------------------------------------------
    Mcaro Definitions
 --------------------------------------------------------------------------------
 */
/* sensor device name */
#define RSCDRRM020NDSE3_DEVICE_NAME "rscm020"
/* rt_device_control cmd code */
#define RSCDRRM020NDSE3_START       (0x01)  //start
#define RSCDRRM020NDSE3_STOP        (0x02)  //stop
#define RSCDRRM020NDSE3_AUTO_ZERO   (0x03)  //auto zero
#define RSCDRRM020NDSE3_SET_FREQ    (0x04)  //set frequence
#define RSCDRRM020NDSE3_GET_FREQ    (0x05)  //read frequence
#define RSCDRRM020NDSE3_GET_TEMP        (0x06)  //read temperature (℃)

/*
 --------------------------------------------------------------------------------
    Data Structures
 --------------------------------------------------------------------------------
 */
enum rscdrrm020ndse3_mode
{
    RSCDRRM020NDSE3_PRESSURE = 0, //pressure read mode
    RSCDRRM020NDSE3_TEMPERATURE    //temterature read mode
};

struct rscdrrm020ndse3_device
{
    /* inherit from rt_device */
    struct rt_device parent;
    /* spi eeprom device */
    struct rt_spi_device* spi_ee_device;
    /* spi adc device */
    struct rt_spi_device* spi_adc_device;
    /* adc config param(read from eeprom) */
    uint8_t adc_cfg_param[4];
    /* start(0=stop,1=start) */
    bool start;
    /* crrent read mode(0=pressre,1=temperature) */
    enum rscdrrm020ndse3_mode mode;
    /* pressure compensation */
    float pressure_comp;
    /* temperature ADC */
    uint32_t temperature;
    /* bool auto_zero  */
    bool auto_zero;
    /* frequency index [0=20HZ 1=40HZ 2=45HZ 3=90HZ 4=175HZ] */
    uint32_t freq_index;
    /* mutex lock */
    struct rt_mutex lock;   
};
 /*
 -------------------------------------------------------------------------------
    Typedefinitions
 -------------------------------------------------------------------------------
 */
/* auto zero complete callback function */
typedef void (*AUTO_ZERO_CPL_FUNC)(void);
/*
 --------------------------------------------------------------------------------
    Local Vars
 --------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------
    Extern Function
 --------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------
    Local Function Definitions
 --------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------
    Global Function Definitions
 --------------------------------------------------------------------------------
 */

/*
* Function: cmd_init()
* Descriptions: This function will initialize cmd parser
* Author: Eric
* Returns:
* Parameter:
* History:
*/

/*
 -------------------------------------------------------------------------------
    Exported Function Declarations
 -------------------------------------------------------------------------------
 */


/*
 --------------------------------------------------------------------------------
    Compiler Flag
 --------------------------------------------------------------------------------
 */
#ifdef   __cplusplus
}
#endif
// End of xxx.c
#endif  
// End of xxx.H
