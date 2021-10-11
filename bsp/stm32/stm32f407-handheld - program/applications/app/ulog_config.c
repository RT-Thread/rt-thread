/*
 * File Name      ulog_condif.c
 * Descriptions	  print and config the debug messege
 * Change Logs
 * Date             Author       Notes
 * 2020-11-23       Eric     	 first implementation
*/

/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
/* <Header file of standard Library> */
#include <stdlib.h>
#include <rtthread.h>
/*----------------------------------------------------------------------------*/
/* "Header file of nonstandard Library" */

/**---------------------------------------------------------------------------*
 **                            Debugging Flag                                 *
 **---------------------------------------------------------------------------*/
#ifndef ULOG_USING_SYSLOG
    #define LOG_TAG              "[proj_ulog.c]"
    #define LOG_LVL              LOG_LVL_DBG
    #include <ulog.h>
#else
    #include <syslog.h>
#endif /* ULOG_USING_SYSLOG */
// /* log format output different level log by LOG_X API */
// LOG_D("LOG_D(%d): RT-Thread is an open source IoT operating system from China.", count);
// LOG_I("LOG_I(%d): RT-Thread is an open source IoT operating system from China.", count);
// LOG_W("LOG_W(%d): RT-Thread is an open source IoT operating system from China.", count);
// LOG_E("LOG_E(%d): RT-Thread is an open source IoT operating system from China.", count);
// ulog_d("test", "ulog_d(%d): RT-Thread is an open source IoT operating system from China.", count);
// ulog_i("test", "ulog_i(%d): RT-Thread is an open source IoT operating system from China.", count);
// ulog_w("test", "ulog_w(%d): RT-Thread is an open source IoT operating system from China.", count);
// ulog_e("test", "ulog_e(%d): RT-Thread is an open source IoT operating system from China.", count);

typedef struct
{
    const char *Cmd_Titel_Head;
    const char *Cmd_Titel_Content_First;
    const char *Cmd_Titel_Content_Cecond;
    const char *Cmd_Titel_Content_Third;
    const char *Cmd_Titel_Tail;
} Cmd_Titel;

static Cmd_Titel cmd_titel[] =
{
    "\r\n/*---------------------------------------------------*/",
    "$ Cmd_list:",
    "Ignore Upper and Lower case\r\n",
    NULL,
    "/*---------------------------------------------------*/\r\n",
};

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Extern Function                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Function Define                                *
**----------------------------------------------------------------------------*/
/*
* Function: ulog_global_config()
* Descriptions: This function will config ulog ouput
* Author: Eric
* Returns:
* Parameter:
* History:
*/
void ulog_global_config(void)
{
    #ifdef ULOG_USING_SYSLOG
    //openlog("example1", 0, 0);
    //LOG_D("LOG_D: ulog run sucesse!hello world!");
    #endif


    #ifndef ULOG_USING_SYSLOG
    /* output different level log by LOG_X API */
    LOG_D("LOG_D: ulog run sucesse!");
    #ifdef ULOG_USING_FILTER

    /* Set the global filer level is INFO. All of DEBUG log will stop output */
    //ulog_global_filter_lvl_set(LOG_LVL_INFO);
    ulog_tag_lvl_filter_set("[main.cpp]", LOG_LVL_ERROR);
    LOG_D("ulog_tag_lvl_filter_set()"[main.cpp]", LOG_LVL_ERROR");
    /* Set the test tag's level filter's level is ERROR. The DEBUG, INFO, WARNING log will stop output. */

    #endif /* ULOG_USING_FILTER */

    #else
    /* output different priority log by syslog API */
    //syslog(LOG_INFO, "syslog(%d) LOG_INFO: RT-Thread is an open source IoT operating system from China.", count);
    #endif /* ULOG_USING_SYSLOG */

}
INIT_COMPONENT_EXPORT(ulog_global_config);



/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of xxx.c
