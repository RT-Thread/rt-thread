/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-20 09:51:46
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_OS_GMAC_H
#define FT_OS_GMAC_H
#include "ft_gmac.h"
#include "ft_parameters.h"

#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

#include "lwip/netif.h"

#define FT_OS_GMAC0_ID FT_GMAC0_ID
#define FT_OS_GMAC1_ID FT_GMAC1_ID

#ifdef PHY_USING_AR8035
#define USE_LWIP
#endif

#define FT_NETIF_LINKUP 0x1U
#define FT_NETIF_DOWN 0x2U

struct Ipv4Address
{
    u8 Ip_Address[4];
    u8 Netmask_Address[4];
    u8 GateWay_Address[4];
};

struct GmacThread
{
    const char *Thread_Name;
    u16 StackDepth; /* The number of words the stack */
    u32 Priority;   /* Defines the priority at which the task will execute. */
    TaskHandle_t Thread_Handle;
};

typedef struct
{
    u32 Gmac_Instance; /* select Gmac global object */
    u32 Isr_Priority;  /* irq Priority */
    struct Ipv4Address Address;

    /* Gmac input thread */
    struct GmacThread MacInputThread;
    struct GmacThread MacStatusThread;

} Ft_Os_Gmac_Config;

typedef struct
{
    Ft_Gmac_t Gmac;
    struct netif Netif_Object;
    Ft_Os_Gmac_Config Config;
    u8 *Rxbuffer; /* Buffer for RxDesc */
    u8 *Txbuffer; /* Buffer for TxDesc */
    u8 IsReady;   /* Ft_Os_Gmac Object first need Init use Ft_Os_GmacObjec_Init */

    SemaphoreHandle_t s_xSemaphore;    /*   Semaphore to signal incoming packets */
    EventGroupHandle_t s_xStatusEvent; /* Event Group to show netif's status ,follow FT_NETIF_XX*/
} Ft_Os_Gmac;
void Ft_Os_GmacObject_Init(Ft_Os_Gmac *Os_Gmac, Ft_Os_Gmac_Config *Config);
void Ft_Os_Gmac_Init(Ft_Os_Gmac *Ft_Os_Gmac);
void Ft_Os_Gmac_Start(Ft_Os_Gmac *Os_Gmac);
void Ft_Os_Gmac_Stop(Ft_Os_Gmac *Os_Gmac);

#ifdef USE_LWIP

#endif

#endif // ! FT_OS_GMAC_H