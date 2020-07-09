/******************************************************************************
**
** \file      gh_usb.c
**
** \brief     USB.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#include "gh_usb.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_USB_POWER_W_PERI_S                   m_usb_power_w_peri;
GH_USB_POWER_W_HOST_S                   m_usb_power_w_host;
GH_USB_CSR0L_W_PERI_S                   m_usb_csr0l_w_peri;
GH_USB_CSR0H_W_PERI_S                   m_usb_csr0h_w_peri;
GH_USB_CSR0L_W_HOST_S                   m_usb_csr0l_w_host;
GH_USB_CSR0H_W_HOST_S                   m_usb_csr0h_w_host;
GH_USB_TXCSRL_W_PERI_S                  m_usb_txcsrl_w_peri;
GH_USB_TXCSRH_W_PERI_S                  m_usb_txcsrh_w_peri;
GH_USB_TXCSRL_W_HOST_S                  m_usb_txcsrl_w_host;
GH_USB_TXCSRH_W_HOST_S                  m_usb_txcsrh_w_host;
GH_USB_RXCSRL_W_PERI_S                  m_usb_rxcsrl_w_peri;
GH_USB_RXCSRH_W_PERI_S                  m_usb_rxcsrh_w_peri;
GH_USB_RXCSRL_W_HOST_S                  m_usb_rxcsrl_w_host;
GH_USB_RXCSRH_W_HOST_S                  m_usb_rxcsrh_w_host;
GH_USB_DEVCTL_W_S                       m_usb_devctl_w;
U32                                     m_usb_vcontrol;

/*----------------------------------------------------------------------------*/
/* register USB_FAddr (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_FAddr(U8 data)
{
    *(volatile U8 *)REG_USB_FADDR = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FAddr] <-- 0x%08x\n",
                        REG_USB_FADDR,data,data);
    #endif
}
U8   GH_USB_get_FAddr(void)
{
    U8 value = (*(volatile U8 *)REG_USB_FADDR);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FAddr] --> 0x%08x\n",
                        REG_USB_FADDR,value);
    #endif
    return value;
}
void GH_USB_set_FAddr_FuncAddr(U8 data)
{
    GH_USB_FADDR_S d;
    d.all = *(volatile U8 *)REG_USB_FADDR;
    d.bitc.funcaddr = data;
    *(volatile U8 *)REG_USB_FADDR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FAddr_FuncAddr] <-- 0x%08x\n",
                        REG_USB_FADDR,d.all,d.all);
    #endif
}
U8   GH_USB_get_FAddr_FuncAddr(void)
{
    GH_USB_FADDR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_FADDR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FAddr_FuncAddr] --> 0x%08x\n",
                        REG_USB_FADDR,value);
    #endif
    return tmp_value.bitc.funcaddr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_R_PERI (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_Power_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return value;
}
U8   GH_USB_get_Power_R_PERI_Enable_SuspendM(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Enable_SuspendM] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.enable_suspendm;
}
U8   GH_USB_get_Power_R_PERI_Suspend_Mode(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Suspend_Mode] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.suspend_mode;
}
U8   GH_USB_get_Power_R_PERI_Resume(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Resume] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.resume;
}
U8   GH_USB_get_Power_R_PERI_Reset(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Reset] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.reset;
}
U8   GH_USB_get_Power_R_PERI_HS_Mode(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_HS_Mode] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.hs_mode;
}
U8   GH_USB_get_Power_R_PERI_HS_Enab(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_HS_Enab] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.hs_enab;
}
U8   GH_USB_get_Power_R_PERI_Soft_Conn(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Soft_Conn] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.soft_conn;
}
U8   GH_USB_get_Power_R_PERI_ISO_Update(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_ISO_Update] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.iso_update;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_W_PERI (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_Power_W_PERI(U8 data)
{
    m_usb_power_w_peri.all = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,data,data);
    #endif
}
U8   GH_USB_getm_Power_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI] --> 0x%08x\n",
                        m_usb_power_w_peri.all);
    #endif
    return m_usb_power_w_peri.all;
}
void GH_USB_set_Power_W_PERI_Enable_SuspendM(U8 data)
{
    m_usb_power_w_peri.bitc.enable_suspendm = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_Enable_SuspendM] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
U8   GH_USB_getm_Power_W_PERI_Enable_SuspendM(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_Enable_SuspendM] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.enable_suspendm);
    #endif
    return m_usb_power_w_peri.bitc.enable_suspendm;
}
void GH_USB_set_Power_W_PERI_Resume(U8 data)
{
    m_usb_power_w_peri.bitc.resume = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_Resume] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
U8   GH_USB_getm_Power_W_PERI_Resume(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_Resume] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.resume);
    #endif
    return m_usb_power_w_peri.bitc.resume;
}
void GH_USB_set_Power_W_PERI_HS_Enab(U8 data)
{
    m_usb_power_w_peri.bitc.hs_enab = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_HS_Enab] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
U8   GH_USB_getm_Power_W_PERI_HS_Enab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_HS_Enab] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.hs_enab);
    #endif
    return m_usb_power_w_peri.bitc.hs_enab;
}
void GH_USB_set_Power_W_PERI_Soft_Conn(U8 data)
{
    m_usb_power_w_peri.bitc.soft_conn = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_Soft_Conn] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
U8   GH_USB_getm_Power_W_PERI_Soft_Conn(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_Soft_Conn] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.soft_conn);
    #endif
    return m_usb_power_w_peri.bitc.soft_conn;
}
void GH_USB_set_Power_W_PERI_ISO_Update(U8 data)
{
    m_usb_power_w_peri.bitc.iso_update = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_ISO_Update] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
U8   GH_USB_getm_Power_W_PERI_ISO_Update(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_ISO_Update] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.iso_update);
    #endif
    return m_usb_power_w_peri.bitc.iso_update;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_R_HOST (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_Power_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_Power_R_HOST_Enable_SuspendM(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_Enable_SuspendM] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.enable_suspendm;
}
U8   GH_USB_get_Power_R_HOST_Resume(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_Resume] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.resume;
}
U8   GH_USB_get_Power_R_HOST_Reset(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_Reset] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.reset;
}
U8   GH_USB_get_Power_R_HOST_HS_Mode(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_HS_Mode] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.hs_mode;
}
U8   GH_USB_get_Power_R_HOST_HS_Enab(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_HS_Enab] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.hs_enab;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_W_HOST (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_Power_W_HOST(U8 data)
{
    m_usb_power_w_host.all = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,data,data);
    #endif
}
U8   GH_USB_getm_Power_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST] --> 0x%08x\n",
                        m_usb_power_w_host.all);
    #endif
    return m_usb_power_w_host.all;
}
void GH_USB_set_Power_W_HOST_Enable_SuspendM(U8 data)
{
    m_usb_power_w_host.bitc.enable_suspendm = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Enable_SuspendM] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
U8   GH_USB_getm_Power_W_HOST_Enable_SuspendM(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Enable_SuspendM] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.enable_suspendm);
    #endif
    return m_usb_power_w_host.bitc.enable_suspendm;
}
void GH_USB_set_Power_W_HOST_Suspend_Mode(U8 data)
{
    m_usb_power_w_host.bitc.suspend_mode = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Suspend_Mode] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
U8   GH_USB_getm_Power_W_HOST_Suspend_Mode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Suspend_Mode] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.suspend_mode);
    #endif
    return m_usb_power_w_host.bitc.suspend_mode;
}
void GH_USB_set_Power_W_HOST_Resume(U8 data)
{
    m_usb_power_w_host.bitc.resume = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Resume] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
U8   GH_USB_getm_Power_W_HOST_Resume(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Resume] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.resume);
    #endif
    return m_usb_power_w_host.bitc.resume;
}
void GH_USB_set_Power_W_HOST_Reset(U8 data)
{
    m_usb_power_w_host.bitc.reset = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Reset] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
U8   GH_USB_getm_Power_W_HOST_Reset(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Reset] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.reset);
    #endif
    return m_usb_power_w_host.bitc.reset;
}
void GH_USB_set_Power_W_HOST_HS_Enab(U8 data)
{
    m_usb_power_w_host.bitc.hs_enab = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_HS_Enab] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
U8   GH_USB_getm_Power_W_HOST_HS_Enab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_HS_Enab] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.hs_enab);
    #endif
    return m_usb_power_w_host.bitc.hs_enab;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrTx (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_USB_get_IntrTx(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return value;
}
U8   GH_USB_get_IntrTx_EP0(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP0] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep0;
}
U8   GH_USB_get_IntrTx_EP1Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP1Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep1tx;
}
U8   GH_USB_get_IntrTx_EP2Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP2Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep2tx;
}
U8   GH_USB_get_IntrTx_EP3Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP3Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep3tx;
}
U8   GH_USB_get_IntrTx_EP4Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP4Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep4tx;
}
U8   GH_USB_get_IntrTx_EP5Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP5Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep5tx;
}
U8   GH_USB_get_IntrTx_EP6Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP6Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep6tx;
}
U8   GH_USB_get_IntrTx_EP7Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP7Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep7tx;
}
U8   GH_USB_get_IntrTx_EP8Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP8Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep8tx;
}
U8   GH_USB_get_IntrTx_EP9Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP9Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep9tx;
}
U8   GH_USB_get_IntrTx_EP10Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP10Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep10tx;
}
U8   GH_USB_get_IntrTx_EP11Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP11Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep11tx;
}
U8   GH_USB_get_IntrTx_EP12Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP12Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep12tx;
}
U8   GH_USB_get_IntrTx_EP13Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP13Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep13tx;
}
U8   GH_USB_get_IntrTx_EP14Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP14Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep14tx;
}
U8   GH_USB_get_IntrTx_EP15Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP15Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep15tx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrRx (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_USB_get_IntrRx(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return value;
}
U8   GH_USB_get_IntrRx_EP1Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP1Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep1rx;
}
U8   GH_USB_get_IntrRx_EP2Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP2Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep2rx;
}
U8   GH_USB_get_IntrRx_EP3Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP3Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep3rx;
}
U8   GH_USB_get_IntrRx_EP4Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP4Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep4rx;
}
U8   GH_USB_get_IntrRx_EP5Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP5Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep5rx;
}
U8   GH_USB_get_IntrRx_EP6Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP6Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep6rx;
}
U8   GH_USB_get_IntrRx_EP7Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP7Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep7rx;
}
U8   GH_USB_get_IntrRx_EP8Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP8Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep8rx;
}
U8   GH_USB_get_IntrRx_EP9Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP9Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep9rx;
}
U8   GH_USB_get_IntrRx_EP10Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP10Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep10rx;
}
U8   GH_USB_get_IntrRx_EP11Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP11Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep11rx;
}
U8   GH_USB_get_IntrRx_EP12Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP12Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep12rx;
}
U8   GH_USB_get_IntrRx_EP13Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP13Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep13rx;
}
U8   GH_USB_get_IntrRx_EP14Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP14Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep14rx;
}
U8   GH_USB_get_IntrRx_EP15Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP15Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep15rx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrTxE (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_IntrTxE(U16 data)
{
    *(volatile U16 *)REG_USB_INTRTXE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE] <-- 0x%08x\n",
                        REG_USB_INTRTXE,data,data);
    #endif
}
U16  GH_USB_get_IntrTxE(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return value;
}
void GH_USB_set_IntrTxE_EP0(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep0 = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP0] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP0(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP0] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep0;
}
void GH_USB_set_IntrTxE_EP1Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep1tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP1Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP1Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP1Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep1tx;
}
void GH_USB_set_IntrTxE_EP2Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep2tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP2Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP2Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP2Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep2tx;
}
void GH_USB_set_IntrTxE_EP3Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep3tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP3Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP3Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP3Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep3tx;
}
void GH_USB_set_IntrTxE_EP4Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep4tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP4Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP4Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP4Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep4tx;
}
void GH_USB_set_IntrTxE_EP5Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep5tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP5Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP5Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP5Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep5tx;
}
void GH_USB_set_IntrTxE_EP6Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep6tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP6Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP6Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP6Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep6tx;
}
void GH_USB_set_IntrTxE_EP7Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep7tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP7Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP7Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP7Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep7tx;
}
void GH_USB_set_IntrTxE_EP8Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep8tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP8Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP8Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP8Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep8tx;
}
void GH_USB_set_IntrTxE_EP9Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep9tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP9Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP9Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP9Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep9tx;
}
void GH_USB_set_IntrTxE_EP10Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep10tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP10Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP10Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP10Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep10tx;
}
void GH_USB_set_IntrTxE_EP11Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep11tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP11Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP11Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP11Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep11tx;
}
void GH_USB_set_IntrTxE_EP12Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep12tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP12Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP12Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP12Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep12tx;
}
void GH_USB_set_IntrTxE_EP13Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep13tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP13Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP13Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP13Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep13tx;
}
void GH_USB_set_IntrTxE_EP14Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep14tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP14Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP14Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP14Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep14tx;
}
void GH_USB_set_IntrTxE_EP15Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep15tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP15Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrTxE_EP15Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP15Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep15tx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrRxE (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_IntrRxE(U16 data)
{
    *(volatile U16 *)REG_USB_INTRRXE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE] <-- 0x%08x\n",
                        REG_USB_INTRRXE,data,data);
    #endif
}
U16  GH_USB_get_IntrRxE(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return value;
}
void GH_USB_set_IntrRxE_EP1Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep1rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP1Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP1Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP1Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep1rx;
}
void GH_USB_set_IntrRxE_EP2Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep2rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP2Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP2Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP2Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep2rx;
}
void GH_USB_set_IntrRxE_EP3Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep3rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP3Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP3Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP3Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep3rx;
}
void GH_USB_set_IntrRxE_EP4Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep4rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP4Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP4Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP4Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep4rx;
}
void GH_USB_set_IntrRxE_EP5Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep5rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP5Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP5Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP5Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep5rx;
}
void GH_USB_set_IntrRxE_EP6Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep6rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP6Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP6Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP6Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep6rx;
}
void GH_USB_set_IntrRxE_EP7Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep7rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP7Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP7Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP7Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep7rx;
}
void GH_USB_set_IntrRxE_EP8Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep8rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP8Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP8Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP8Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep8rx;
}
void GH_USB_set_IntrRxE_EP9Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep9rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP9Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP9Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP9Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep9rx;
}
void GH_USB_set_IntrRxE_EP10Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep10rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP10Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP10Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP10Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep10rx;
}
void GH_USB_set_IntrRxE_EP11Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep11rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP11Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP11Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP11Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep11rx;
}
void GH_USB_set_IntrRxE_EP12Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep12rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP12Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP12Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP12Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep12rx;
}
void GH_USB_set_IntrRxE_EP13Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep13rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP13Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP13Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP13Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep13rx;
}
void GH_USB_set_IntrRxE_EP14Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep14rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP14Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP14Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP14Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep14rx;
}
void GH_USB_set_IntrRxE_EP15Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep15rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP15Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrRxE_EP15Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP15Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep15rx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrUSB (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_IntrUSB(void)
{
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return value;
}
U8   GH_USB_get_IntrUSB_Suspend(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Suspend] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.suspend;
}
U8   GH_USB_get_IntrUSB_Resume(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Resume] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.resume;
}
U8   GH_USB_get_IntrUSB_Reset_Babble(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Reset_Babble] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.reset_babble;
}
U8   GH_USB_get_IntrUSB_SOF(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_SOF] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.sof;
}
U8   GH_USB_get_IntrUSB_Conn(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Conn] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.conn;
}
U8   GH_USB_get_IntrUSB_Discon(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Discon] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.discon;
}
U8   GH_USB_get_IntrUSB_Sess_Req(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Sess_Req] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.sess_req;
}
U8   GH_USB_get_IntrUSB_VBus_Error(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_VBus_Error] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.vbus_error;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrUSBE (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_IntrUSBE(U8 data)
{
    *(volatile U8 *)REG_USB_INTRUSBE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,data,data);
    #endif
}
U8   GH_USB_get_IntrUSBE(void)
{
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return value;
}
void GH_USB_set_IntrUSBE_Suspend(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.suspend = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Suspend] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_Suspend(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Suspend] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.suspend;
}
void GH_USB_set_IntrUSBE_Resume(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.resume = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Resume] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_Resume(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Resume] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.resume;
}
void GH_USB_set_IntrUSBE_Reset_Babble(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.reset_babble = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Reset_Babble] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_Reset_Babble(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Reset_Babble] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.reset_babble;
}
void GH_USB_set_IntrUSBE_SOF(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.sof = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_SOF] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_SOF(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_SOF] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.sof;
}
void GH_USB_set_IntrUSBE_Conn(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.conn = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Conn] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_Conn(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Conn] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.conn;
}
void GH_USB_set_IntrUSBE_Discon(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.discon = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Discon] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_Discon(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Discon] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.discon;
}
void GH_USB_set_IntrUSBE_Sess_Req(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.sess_req = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Sess_Req] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_Sess_Req(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Sess_Req] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.sess_req;
}
void GH_USB_set_IntrUSBE_VBus_Error(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.vbus_error = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_VBus_Error] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
U8   GH_USB_get_IntrUSBE_VBus_Error(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_VBus_Error] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.vbus_error;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Frame (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_USB_get_Frame(void)
{
    U16 value = (*(volatile U16 *)REG_USB_FRAME);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Frame] --> 0x%08x\n",
                        REG_USB_FRAME,value);
    #endif
    return value;
}
U16  GH_USB_get_Frame_Number(void)
{
    GH_USB_FRAME_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_FRAME);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Frame_Number] --> 0x%08x\n",
                        REG_USB_FRAME,value);
    #endif
    return tmp_value.bitc.number;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Index (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_Index(U8 data)
{
    *(volatile U8 *)REG_USB_INDEX = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Index] <-- 0x%08x\n",
                        REG_USB_INDEX,data,data);
    #endif
}
U8   GH_USB_get_Index(void)
{
    U8 value = (*(volatile U8 *)REG_USB_INDEX);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Index] --> 0x%08x\n",
                        REG_USB_INDEX,value);
    #endif
    return value;
}
void GH_USB_set_Index_SelectedEndpoint(U8 data)
{
    GH_USB_INDEX_S d;
    d.all = *(volatile U8 *)REG_USB_INDEX;
    d.bitc.selectedendpoint = data;
    *(volatile U8 *)REG_USB_INDEX = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Index_SelectedEndpoint] <-- 0x%08x\n",
                        REG_USB_INDEX,d.all,d.all);
    #endif
}
U8   GH_USB_get_Index_SelectedEndpoint(void)
{
    GH_USB_INDEX_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INDEX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Index_SelectedEndpoint] --> 0x%08x\n",
                        REG_USB_INDEX,value);
    #endif
    return tmp_value.bitc.selectedendpoint;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Testmode (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_Testmode(U8 data)
{
    *(volatile U8 *)REG_USB_TESTMODE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode] <-- 0x%08x\n",
                        REG_USB_TESTMODE,data,data);
    #endif
}
U8   GH_USB_get_Testmode(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return value;
}
void GH_USB_set_Testmode_Test_SE0_NAK(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_se0_nak = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_SE0_NAK] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_Test_SE0_NAK(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_SE0_NAK] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_se0_nak;
}
void GH_USB_set_Testmode_Test_J(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_j = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_J] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_Test_J(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_J] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_j;
}
void GH_USB_set_Testmode_Test_K(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_k = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_K] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_Test_K(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_K] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_k;
}
void GH_USB_set_Testmode_Test_Packet(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_packet = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_Packet] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_Test_Packet(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_Packet] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_packet;
}
void GH_USB_set_Testmode_Force_HS(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.force_hs = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Force_HS] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_Force_HS(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Force_HS] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.force_hs;
}
void GH_USB_set_Testmode_Force_FS(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.force_fs = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Force_FS] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_Force_FS(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Force_FS] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.force_fs;
}
void GH_USB_set_Testmode_FIFO_Access(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.fifo_access = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_FIFO_Access] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_FIFO_Access(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_FIFO_Access] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.fifo_access;
}
void GH_USB_set_Testmode_Force_Host(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.force_host = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Force_Host] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
U8   GH_USB_get_Testmode_Force_Host(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Force_Host] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.force_host;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_R_PERI (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_CSR0L_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return value;
}
U8   GH_USB_get_CSR0L_R_PERI_RxPktRdy(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_RxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
U8   GH_USB_get_CSR0L_R_PERI_TxPktRdy(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_TxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
U8   GH_USB_get_CSR0L_R_PERI_SentStall(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_SentStall] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.sentstall;
}
U8   GH_USB_get_CSR0L_R_PERI_SetupEnd(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_SetupEnd] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.setupend;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_W_PERI (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_CSR0L_W_PERI(U8 data)
{
    m_usb_csr0l_w_peri.all = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,data,data);
    #endif
}
U8   GH_USB_getm_CSR0L_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.all);
    #endif
    return m_usb_csr0l_w_peri.all;
}
void GH_USB_set_CSR0L_W_PERI_TxPktRdy(U8 data)
{
    m_usb_csr0l_w_peri.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_PERI_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_TxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.txpktrdy);
    #endif
    return m_usb_csr0l_w_peri.bitc.txpktrdy;
}
void GH_USB_set_CSR0L_W_PERI_SentStall(U8 data)
{
    m_usb_csr0l_w_peri.bitc.sentstall = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_SentStall] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_PERI_SentStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_SentStall] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.sentstall);
    #endif
    return m_usb_csr0l_w_peri.bitc.sentstall;
}
void GH_USB_set_CSR0L_W_PERI_DataEnd(U8 data)
{
    m_usb_csr0l_w_peri.bitc.dataend = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_DataEnd] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_PERI_DataEnd(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_DataEnd] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.dataend);
    #endif
    return m_usb_csr0l_w_peri.bitc.dataend;
}
void GH_USB_set_CSR0L_W_PERI_SendStall(U8 data)
{
    m_usb_csr0l_w_peri.bitc.sendstall = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_SendStall] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_PERI_SendStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_SendStall] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.sendstall);
    #endif
    return m_usb_csr0l_w_peri.bitc.sendstall;
}
void GH_USB_set_CSR0L_W_PERI_ServicedRxPktRdy(U8 data)
{
    m_usb_csr0l_w_peri.bitc.servicedrxpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_ServicedRxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_PERI_ServicedRxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_ServicedRxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.servicedrxpktrdy);
    #endif
    return m_usb_csr0l_w_peri.bitc.servicedrxpktrdy;
}
void GH_USB_set_CSR0L_W_PERI_ServicedSetupEnd(U8 data)
{
    m_usb_csr0l_w_peri.bitc.servicedsetupend = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_ServicedSetupEnd] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_PERI_ServicedSetupEnd(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_ServicedSetupEnd] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.servicedsetupend);
    #endif
    return m_usb_csr0l_w_peri.bitc.servicedsetupend;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0H_W_PERI (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_CSR0H_W_PERI(U8 data)
{
    m_usb_csr0h_w_peri.all = data;
    *(volatile U8 *)REG_USB_CSR0H_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_PERI] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_PERI,data,data);
    #endif
}
U8   GH_USB_getm_CSR0H_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_PERI] --> 0x%08x\n",
                        m_usb_csr0h_w_peri.all);
    #endif
    return m_usb_csr0h_w_peri.all;
}
void GH_USB_set_CSR0H_W_PERI_FlushFIFO(U8 data)
{
    m_usb_csr0h_w_peri.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_CSR0H_W_PERI = m_usb_csr0h_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_PERI_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_PERI,m_usb_csr0h_w_peri.all,m_usb_csr0h_w_peri.all);
    #endif
}
U8   GH_USB_getm_CSR0H_W_PERI_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_PERI_FlushFIFO] --> 0x%08x\n",
                        m_usb_csr0h_w_peri.bitc.flushfifo);
    #endif
    return m_usb_csr0h_w_peri.bitc.flushfifo;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_R_HOST (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_CSR0L_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_CSR0L_R_HOST_RxPktRdy(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_RxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
U8   GH_USB_get_CSR0L_R_HOST_TxPktRdy(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_TxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
U8   GH_USB_get_CSR0L_R_HOST_RxStall(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_RxStall] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.rxstall;
}
U8   GH_USB_get_CSR0L_R_HOST_SetupPkt(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_SetupPkt] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.setuppkt;
}
U8   GH_USB_get_CSR0L_R_HOST_Error(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_Error] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.error;
}
U8   GH_USB_get_CSR0L_R_HOST_ReqPkt(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_ReqPkt] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.reqpkt;
}
U8   GH_USB_get_CSR0L_R_HOST_StatusPkt(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_StatusPkt] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.statuspkt;
}
U8   GH_USB_get_CSR0L_R_HOST_NAKTimeout(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_NAKTimeout] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.naktimeout;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0H_R_HOST (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_CSR0H_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CSR0H_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0H_R_HOST] --> 0x%08x\n",
                        REG_USB_CSR0H_R_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_CSR0H_R_HOST_DataToggle(void)
{
    GH_USB_CSR0H_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0H_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0H_R_HOST_DataToggle] --> 0x%08x\n",
                        REG_USB_CSR0H_R_HOST,value);
    #endif
    return tmp_value.bitc.datatoggle;
}
U8   GH_USB_get_CSR0H_R_HOST_DisPing(void)
{
    GH_USB_CSR0H_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0H_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0H_R_HOST_DisPing] --> 0x%08x\n",
                        REG_USB_CSR0H_R_HOST,value);
    #endif
    return tmp_value.bitc.disping;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_W_HOST (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_CSR0L_W_HOST(U8 data)
{
    m_usb_csr0l_w_host.all = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,data,data);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST] --> 0x%08x\n",
                        m_usb_csr0l_w_host.all);
    #endif
    return m_usb_csr0l_w_host.all;
}
void GH_USB_set_CSR0L_W_HOST_RxPktRdy(U8 data)
{
    m_usb_csr0l_w_host.bitc.rxpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_RxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_RxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_RxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.rxpktrdy);
    #endif
    return m_usb_csr0l_w_host.bitc.rxpktrdy;
}
void GH_USB_set_CSR0L_W_HOST_TxPktRdy(U8 data)
{
    m_usb_csr0l_w_host.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_TxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.txpktrdy);
    #endif
    return m_usb_csr0l_w_host.bitc.txpktrdy;
}
void GH_USB_set_CSR0L_W_HOST_RxStall(U8 data)
{
    m_usb_csr0l_w_host.bitc.rxstall = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_RxStall] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_RxStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_RxStall] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.rxstall);
    #endif
    return m_usb_csr0l_w_host.bitc.rxstall;
}
void GH_USB_set_CSR0L_W_HOST_SetupPkt(U8 data)
{
    m_usb_csr0l_w_host.bitc.setuppkt = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_SetupPkt] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_SetupPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_SetupPkt] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.setuppkt);
    #endif
    return m_usb_csr0l_w_host.bitc.setuppkt;
}
void GH_USB_set_CSR0L_W_HOST_Error(U8 data)
{
    m_usb_csr0l_w_host.bitc.error = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_Error] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_Error(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_Error] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.error);
    #endif
    return m_usb_csr0l_w_host.bitc.error;
}
void GH_USB_set_CSR0L_W_HOST_ReqPkt(U8 data)
{
    m_usb_csr0l_w_host.bitc.reqpkt = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_ReqPkt] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_ReqPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_ReqPkt] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.reqpkt);
    #endif
    return m_usb_csr0l_w_host.bitc.reqpkt;
}
void GH_USB_set_CSR0L_W_HOST_StatusPkt(U8 data)
{
    m_usb_csr0l_w_host.bitc.statuspkt = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_StatusPkt] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_StatusPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_StatusPkt] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.statuspkt);
    #endif
    return m_usb_csr0l_w_host.bitc.statuspkt;
}
void GH_USB_set_CSR0L_W_HOST_NAKTimeout(U8 data)
{
    m_usb_csr0l_w_host.bitc.naktimeout = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_NAKTimeout] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0L_W_HOST_NAKTimeout(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_NAKTimeout] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.naktimeout);
    #endif
    return m_usb_csr0l_w_host.bitc.naktimeout;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0H_W_HOST (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_CSR0H_W_HOST(U8 data)
{
    m_usb_csr0h_w_host.all = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,data,data);
    #endif
}
U8   GH_USB_getm_CSR0H_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST] --> 0x%08x\n",
                        m_usb_csr0h_w_host.all);
    #endif
    return m_usb_csr0h_w_host.all;
}
void GH_USB_set_CSR0H_W_HOST_FlushFIFO(U8 data)
{
    m_usb_csr0h_w_host.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0H_W_HOST_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_FlushFIFO] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.flushfifo);
    #endif
    return m_usb_csr0h_w_host.bitc.flushfifo;
}
void GH_USB_set_CSR0H_W_HOST_DataToggle(U8 data)
{
    m_usb_csr0h_w_host.bitc.datatoggle = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_DataToggle] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0H_W_HOST_DataToggle(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_DataToggle] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.datatoggle);
    #endif
    return m_usb_csr0h_w_host.bitc.datatoggle;
}
void GH_USB_set_CSR0H_W_HOST_DataToggleWriteEnable(U8 data)
{
    m_usb_csr0h_w_host.bitc.datatogglewriteenable = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_DataToggleWriteEnable] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0H_W_HOST_DataToggleWriteEnable(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_DataToggleWriteEnable] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.datatogglewriteenable);
    #endif
    return m_usb_csr0h_w_host.bitc.datatogglewriteenable;
}
void GH_USB_set_CSR0H_W_HOST_DisPing(U8 data)
{
    m_usb_csr0h_w_host.bitc.disping = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_DisPing] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
U8   GH_USB_getm_CSR0H_W_HOST_DisPing(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_DisPing] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.disping);
    #endif
    return m_usb_csr0h_w_host.bitc.disping;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_Count0 (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_Count0(void)
{
    U8 value = (*(volatile U8 *)REG_USB_COUNT0);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Count0] --> 0x%08x\n",
                        REG_USB_COUNT0,value);
    #endif
    return value;
}
U8   GH_USB_get_Count0_Endpoint0RxCount(void)
{
    GH_USB_COUNT0_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_COUNT0);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Count0_Endpoint0RxCount] --> 0x%08x\n",
                        REG_USB_COUNT0,value);
    #endif
    return tmp_value.bitc.endpoint0rxcount;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Type0 (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_Type0(U8 data)
{
    *(volatile U8 *)REG_USB_TYPE0 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Type0] <-- 0x%08x\n",
                        REG_USB_TYPE0,data,data);
    #endif
}
U8   GH_USB_get_Type0(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TYPE0);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Type0] --> 0x%08x\n",
                        REG_USB_TYPE0,value);
    #endif
    return value;
}
void GH_USB_set_Type0_Speed(U8 data)
{
    GH_USB_TYPE0_S d;
    d.all = *(volatile U8 *)REG_USB_TYPE0;
    d.bitc.speed = data;
    *(volatile U8 *)REG_USB_TYPE0 = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Type0_Speed] <-- 0x%08x\n",
                        REG_USB_TYPE0,d.all,d.all);
    #endif
}
U8   GH_USB_get_Type0_Speed(void)
{
    GH_USB_TYPE0_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TYPE0);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Type0_Speed] --> 0x%08x\n",
                        REG_USB_TYPE0,value);
    #endif
    return tmp_value.bitc.speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_NAKLimit0_HOST (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_NAKLimit0_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_NAKLIMIT0_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_NAKLimit0_HOST] <-- 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,data,data);
    #endif
}
U8   GH_USB_get_NAKLimit0_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_NAKLIMIT0_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_NAKLimit0_HOST] --> 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,value);
    #endif
    return value;
}
void GH_USB_set_NAKLimit0_HOST_Endpoint0NAKLimit(U8 data)
{
    GH_USB_NAKLIMIT0_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_NAKLIMIT0_HOST;
    d.bitc.endpoint0naklimit = data;
    *(volatile U8 *)REG_USB_NAKLIMIT0_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_NAKLimit0_HOST_Endpoint0NAKLimit] <-- 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_NAKLimit0_HOST_Endpoint0NAKLimit(void)
{
    GH_USB_NAKLIMIT0_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_NAKLIMIT0_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_NAKLimit0_HOST_Endpoint0NAKLimit] --> 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,value);
    #endif
    return tmp_value.bitc.endpoint0naklimit;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_ConfigData (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_ConfigData(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return value;
}
U8   GH_USB_get_ConfigData_UTMI_DataWidth(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_UTMI_DataWidth] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.utmi_datawidth;
}
U8   GH_USB_get_ConfigData_SoftConE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_SoftConE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.softcone;
}
U8   GH_USB_get_ConfigData_DynFIFO_Sizing(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_DynFIFO_Sizing] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.dynfifo_sizing;
}
U8   GH_USB_get_ConfigData_HBTxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_HBTxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.hbtxe;
}
U8   GH_USB_get_ConfigData_HBRxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_HBRxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.hbrxe;
}
U8   GH_USB_get_ConfigData_BigEndian(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_BigEndian] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.bigendian;
}
U8   GH_USB_get_ConfigData_MPTxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_MPTxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.mptxe;
}
U8   GH_USB_get_ConfigData_MPRxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_MPRxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.mprxe;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxMaxP (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxMaxP(U16 data)
{
    *(volatile U16 *)REG_USB_TXMAXP = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxMaxP] <-- 0x%08x\n",
                        REG_USB_TXMAXP,data,data);
    #endif
}
U16  GH_USB_get_TxMaxP(void)
{
    U16 value = (*(volatile U16 *)REG_USB_TXMAXP);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxMaxP] --> 0x%08x\n",
                        REG_USB_TXMAXP,value);
    #endif
    return value;
}
void GH_USB_set_TxMaxP_TxMaxP(U16 data)
{
    GH_USB_TXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_TXMAXP;
    d.bitc.txmaxp = data;
    *(volatile U16 *)REG_USB_TXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxMaxP_TxMaxP] <-- 0x%08x\n",
                        REG_USB_TXMAXP,d.all,d.all);
    #endif
}
U16  GH_USB_get_TxMaxP_TxMaxP(void)
{
    GH_USB_TXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxMaxP_TxMaxP] --> 0x%08x\n",
                        REG_USB_TXMAXP,value);
    #endif
    return tmp_value.bitc.txmaxp;
}
void GH_USB_set_TxMaxP_multiplier(U8 data)
{
    GH_USB_TXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_TXMAXP;
    d.bitc.multiplier = data;
    *(volatile U16 *)REG_USB_TXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxMaxP_multiplier] <-- 0x%08x\n",
                        REG_USB_TXMAXP,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxMaxP_multiplier(void)
{
    GH_USB_TXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxMaxP_multiplier] --> 0x%08x\n",
                        REG_USB_TXMAXP,value);
    #endif
    return tmp_value.bitc.multiplier;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_TXCSRL_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return value;
}
U8   GH_USB_get_TXCSRL_R_PERI_TxPktRdy(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_TxPktRdy] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
U8   GH_USB_get_TXCSRL_R_PERI_FIFONotEmpty(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_FIFONotEmpty] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.fifonotempty;
}
U8   GH_USB_get_TXCSRL_R_PERI_UnderRun(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_UnderRun] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.underrun;
}
U8   GH_USB_get_TXCSRL_R_PERI_SendStall(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_SendStall] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sendstall;
}
U8   GH_USB_get_TXCSRL_R_PERI_SentStall(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_SentStall] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sentstall;
}
U8   GH_USB_get_TXCSRL_R_PERI_IncompTx(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_IncompTx] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_TXCSRH_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return value;
}
U8   GH_USB_get_TXCSRH_R_PERI_DMAReqMode(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_DMAReqMode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
U8   GH_USB_get_TXCSRH_R_PERI_FrcDataTog(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_FrcDataTog] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.frcdatatog;
}
U8   GH_USB_get_TXCSRH_R_PERI_DMAReqEnab(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
U8   GH_USB_get_TXCSRH_R_PERI_Mode(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_Mode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.mode;
}
U8   GH_USB_get_TXCSRH_R_PERI_ISO(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_ISO] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.iso;
}
U8   GH_USB_get_TXCSRH_R_PERI_AutoSet(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_AutoSet] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_TXCSRL_W_PERI(U8 data)
{
    m_usb_txcsrl_w_peri.all = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,data,data);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.all);
    #endif
    return m_usb_txcsrl_w_peri.all;
}
void GH_USB_set_TXCSRL_W_PERI_TxPktRdy(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_TxPktRdy] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.txpktrdy);
    #endif
    return m_usb_txcsrl_w_peri.bitc.txpktrdy;
}
void GH_USB_set_TXCSRL_W_PERI_FIFONotEmpty(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.fifonotempty = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_FIFONotEmpty] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_FIFONotEmpty(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_FIFONotEmpty] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.fifonotempty);
    #endif
    return m_usb_txcsrl_w_peri.bitc.fifonotempty;
}
void GH_USB_set_TXCSRL_W_PERI_UnderRun(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.underrun = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_UnderRun] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_UnderRun(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_UnderRun] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.underrun);
    #endif
    return m_usb_txcsrl_w_peri.bitc.underrun;
}
void GH_USB_set_TXCSRL_W_PERI_FlushFIFO(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_FlushFIFO] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.flushfifo);
    #endif
    return m_usb_txcsrl_w_peri.bitc.flushfifo;
}
void GH_USB_set_TXCSRL_W_PERI_SendStall(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.sendstall = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_SendStall] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_SendStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_SendStall] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.sendstall);
    #endif
    return m_usb_txcsrl_w_peri.bitc.sendstall;
}
void GH_USB_set_TXCSRL_W_PERI_SentStall(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.sentstall = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_SentStall] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_SentStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_SentStall] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.sentstall);
    #endif
    return m_usb_txcsrl_w_peri.bitc.sentstall;
}
void GH_USB_set_TXCSRL_W_PERI_ClrDataTog(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_ClrDataTog] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.clrdatatog);
    #endif
    return m_usb_txcsrl_w_peri.bitc.clrdatatog;
}
void GH_USB_set_TXCSRL_W_PERI_IncompTx(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.incomptx = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_IncompTx] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_PERI_IncompTx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_IncompTx] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.incomptx);
    #endif
    return m_usb_txcsrl_w_peri.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_TXCSRH_W_PERI(U8 data)
{
    m_usb_txcsrh_w_peri.all = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,data,data);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.all);
    #endif
    return m_usb_txcsrh_w_peri.all;
}
void GH_USB_set_TXCSRH_W_PERI_DMAReqMode(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_PERI_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_DMAReqMode] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.dmareqmode);
    #endif
    return m_usb_txcsrh_w_peri.bitc.dmareqmode;
}
void GH_USB_set_TXCSRH_W_PERI_FrcDataTog(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.frcdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_FrcDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_PERI_FrcDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_FrcDataTog] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.frcdatatog);
    #endif
    return m_usb_txcsrh_w_peri.bitc.frcdatatog;
}
void GH_USB_set_TXCSRH_W_PERI_DMAReqEnab(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_PERI_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_DMAReqEnab] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.dmareqenab);
    #endif
    return m_usb_txcsrh_w_peri.bitc.dmareqenab;
}
void GH_USB_set_TXCSRH_W_PERI_Mode(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.mode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_Mode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_PERI_Mode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_Mode] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.mode);
    #endif
    return m_usb_txcsrh_w_peri.bitc.mode;
}
void GH_USB_set_TXCSRH_W_PERI_ISO(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.iso = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_ISO] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_PERI_ISO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_ISO] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.iso);
    #endif
    return m_usb_txcsrh_w_peri.bitc.iso;
}
void GH_USB_set_TXCSRH_W_PERI_AutoSet(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.autoset = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_AutoSet] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_PERI_AutoSet(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_AutoSet] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.autoset);
    #endif
    return m_usb_txcsrh_w_peri.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_TXCSRL_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_TXCSRL_R_HOST_TxPktRdy(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_TxPktRdy] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
U8   GH_USB_get_TXCSRL_R_HOST_FIFONotEmpty(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_FIFONotEmpty] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.fifonotempty;
}
U8   GH_USB_get_TXCSRL_R_HOST_Error(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_Error] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.error;
}
U8   GH_USB_get_TXCSRL_R_HOST_SetupPkt(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_SetupPkt] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.setuppkt;
}
U8   GH_USB_get_TXCSRL_R_HOST_RxStall(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_RxStall] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.rxstall;
}
U8   GH_USB_get_TXCSRL_R_HOST_IncompTx(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_IncompTx] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_TXCSRH_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_TXCSRH_R_HOST_DataToggle(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_DataToggle] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.datatoggle;
}
U8   GH_USB_get_TXCSRH_R_HOST_DMAReqMode(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_DMAReqMode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
U8   GH_USB_get_TXCSRH_R_HOST_FrcDataTog(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_FrcDataTog] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.frcdatatog;
}
U8   GH_USB_get_TXCSRH_R_HOST_DMAReqEnab(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
U8   GH_USB_get_TXCSRH_R_HOST_Mode(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_Mode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.mode;
}
U8   GH_USB_get_TXCSRH_R_HOST_AutoSet(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_AutoSet] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_TXCSRL_W_HOST(U8 data)
{
    m_usb_txcsrl_w_host.all = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,data,data);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.all);
    #endif
    return m_usb_txcsrl_w_host.all;
}
void GH_USB_set_TXCSRL_W_HOST_TxPktRdy(U8 data)
{
    m_usb_txcsrl_w_host.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_TxPktRdy] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.txpktrdy);
    #endif
    return m_usb_txcsrl_w_host.bitc.txpktrdy;
}
void GH_USB_set_TXCSRL_W_HOST_FIFONotEmpty(U8 data)
{
    m_usb_txcsrl_w_host.bitc.fifonotempty = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_FIFONotEmpty] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_FIFONotEmpty(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_FIFONotEmpty] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.fifonotempty);
    #endif
    return m_usb_txcsrl_w_host.bitc.fifonotempty;
}
void GH_USB_set_TXCSRL_W_HOST_Error(U8 data)
{
    m_usb_txcsrl_w_host.bitc.error = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_Error] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_Error(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_Error] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.error);
    #endif
    return m_usb_txcsrl_w_host.bitc.error;
}
void GH_USB_set_TXCSRL_W_HOST_FlushFIFO(U8 data)
{
    m_usb_txcsrl_w_host.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_FlushFIFO] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.flushfifo);
    #endif
    return m_usb_txcsrl_w_host.bitc.flushfifo;
}
void GH_USB_set_TXCSRL_W_HOST_SetupPkt(U8 data)
{
    m_usb_txcsrl_w_host.bitc.setuppkt = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_SetupPkt] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_SetupPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_SetupPkt] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.setuppkt);
    #endif
    return m_usb_txcsrl_w_host.bitc.setuppkt;
}
void GH_USB_set_TXCSRL_W_HOST_RxStall(U8 data)
{
    m_usb_txcsrl_w_host.bitc.rxstall = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_RxStall] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_RxStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_RxStall] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.rxstall);
    #endif
    return m_usb_txcsrl_w_host.bitc.rxstall;
}
void GH_USB_set_TXCSRL_W_HOST_ClrDataTog(U8 data)
{
    m_usb_txcsrl_w_host.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_ClrDataTog] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.clrdatatog);
    #endif
    return m_usb_txcsrl_w_host.bitc.clrdatatog;
}
void GH_USB_set_TXCSRL_W_HOST_IncompTx(U8 data)
{
    m_usb_txcsrl_w_host.bitc.incomptx = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_IncompTx] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRL_W_HOST_IncompTx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_IncompTx] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.incomptx);
    #endif
    return m_usb_txcsrl_w_host.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_TXCSRH_W_HOST(U8 data)
{
    m_usb_txcsrh_w_host.all = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,data,data);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.all);
    #endif
    return m_usb_txcsrh_w_host.all;
}
void GH_USB_set_TXCSRH_W_HOST_DataToggle(U8 data)
{
    m_usb_txcsrh_w_host.bitc.datatoggle = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DataToggle] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST_DataToggle(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DataToggle] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.datatoggle);
    #endif
    return m_usb_txcsrh_w_host.bitc.datatoggle;
}
void GH_USB_set_TXCSRH_W_HOST_DataToggleWriteEnable(U8 data)
{
    m_usb_txcsrh_w_host.bitc.datatogglewriteenable = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DataToggleWriteEnable] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST_DataToggleWriteEnable(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DataToggleWriteEnable] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.datatogglewriteenable);
    #endif
    return m_usb_txcsrh_w_host.bitc.datatogglewriteenable;
}
void GH_USB_set_TXCSRH_W_HOST_DMAReqMode(U8 data)
{
    m_usb_txcsrh_w_host.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DMAReqMode] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.dmareqmode);
    #endif
    return m_usb_txcsrh_w_host.bitc.dmareqmode;
}
void GH_USB_set_TXCSRH_W_HOST_FrcDataTog(U8 data)
{
    m_usb_txcsrh_w_host.bitc.frcdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_FrcDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST_FrcDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_FrcDataTog] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.frcdatatog);
    #endif
    return m_usb_txcsrh_w_host.bitc.frcdatatog;
}
void GH_USB_set_TXCSRH_W_HOST_DMAReqEnab(U8 data)
{
    m_usb_txcsrh_w_host.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DMAReqEnab] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.dmareqenab);
    #endif
    return m_usb_txcsrh_w_host.bitc.dmareqenab;
}
void GH_USB_set_TXCSRH_W_HOST_Mode(U8 data)
{
    m_usb_txcsrh_w_host.bitc.mode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_Mode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST_Mode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_Mode] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.mode);
    #endif
    return m_usb_txcsrh_w_host.bitc.mode;
}
void GH_USB_set_TXCSRH_W_HOST_AutoSet(U8 data)
{
    m_usb_txcsrh_w_host.bitc.autoset = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_AutoSet] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_TXCSRH_W_HOST_AutoSet(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_AutoSet] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.autoset);
    #endif
    return m_usb_txcsrh_w_host.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RxMaxP (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxMaxP(U16 data)
{
    *(volatile U16 *)REG_USB_RXMAXP = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxMaxP] <-- 0x%08x\n",
                        REG_USB_RXMAXP,data,data);
    #endif
}
U16  GH_USB_get_RxMaxP(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RXMAXP);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxMaxP] --> 0x%08x\n",
                        REG_USB_RXMAXP,value);
    #endif
    return value;
}
void GH_USB_set_RxMaxP_TxMaxP(U16 data)
{
    GH_USB_RXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_RXMAXP;
    d.bitc.txmaxp = data;
    *(volatile U16 *)REG_USB_RXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxMaxP_TxMaxP] <-- 0x%08x\n",
                        REG_USB_RXMAXP,d.all,d.all);
    #endif
}
U16  GH_USB_get_RxMaxP_TxMaxP(void)
{
    GH_USB_RXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxMaxP_TxMaxP] --> 0x%08x\n",
                        REG_USB_RXMAXP,value);
    #endif
    return tmp_value.bitc.txmaxp;
}
void GH_USB_set_RxMaxP_multiplier(U8 data)
{
    GH_USB_RXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_RXMAXP;
    d.bitc.multiplier = data;
    *(volatile U16 *)REG_USB_RXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxMaxP_multiplier] <-- 0x%08x\n",
                        REG_USB_RXMAXP,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxMaxP_multiplier(void)
{
    GH_USB_RXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxMaxP_multiplier] --> 0x%08x\n",
                        REG_USB_RXMAXP,value);
    #endif
    return tmp_value.bitc.multiplier;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_RXCSRL_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return value;
}
U8   GH_USB_get_RXCSRL_R_PERI_RxPktRdy(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_RxPktRdy] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
U8   GH_USB_get_RXCSRL_R_PERI_FIFOFull(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_FIFOFull] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.fifofull;
}
U8   GH_USB_get_RXCSRL_R_PERI_OverRun(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_OverRun] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.overrun;
}
U8   GH_USB_get_RXCSRL_R_PERI_DataError(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_DataError] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.dataerror;
}
U8   GH_USB_get_RXCSRL_R_PERI_SendStall(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_SendStall] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sendstall;
}
U8   GH_USB_get_RXCSRL_R_PERI_SentStall(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_SentStall] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sentstall;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_RXCSRH_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return value;
}
U8   GH_USB_get_RXCSRH_R_PERI_IncompRx(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_IncompRx] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.incomprx;
}
U8   GH_USB_get_RXCSRH_R_PERI_DMAReqMode(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_DMAReqMode] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
U8   GH_USB_get_RXCSRH_R_PERI_DisNyet_PIDError(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_DisNyet_PIDError] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.disnyet_piderror;
}
U8   GH_USB_get_RXCSRH_R_PERI_DMAReqEnab(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
U8   GH_USB_get_RXCSRH_R_PERI_ISO(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_ISO] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.iso;
}
U8   GH_USB_get_RXCSRH_R_PERI_AutoClear(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_AutoClear] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_RXCSRL_W_PERI(U8 data)
{
    m_usb_rxcsrl_w_peri.all = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,data,data);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.all);
    #endif
    return m_usb_rxcsrl_w_peri.all;
}
void GH_USB_set_RXCSRL_W_PERI_RxPktRdy(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.rxpktrdy = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_RxPktRdy] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_PERI_RxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_RxPktRdy] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.rxpktrdy);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.rxpktrdy;
}
void GH_USB_set_RXCSRL_W_PERI_OverRun(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.overrun = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_OverRun] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_PERI_OverRun(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_OverRun] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.overrun);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.overrun;
}
void GH_USB_set_RXCSRL_W_PERI_FlushFIFO(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_PERI_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_FlushFIFO] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.flushfifo);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.flushfifo;
}
void GH_USB_set_RXCSRL_W_PERI_SendStall(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.sendstall = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_SendStall] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_PERI_SendStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_SendStall] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.sendstall);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.sendstall;
}
void GH_USB_set_RXCSRL_W_PERI_SentStall(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.sentstall = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_SentStall] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_PERI_SentStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_SentStall] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.sentstall);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.sentstall;
}
void GH_USB_set_RXCSRL_W_PERI_ClrDataTog(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_PERI_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_ClrDataTog] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.clrdatatog);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.clrdatatog;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_RXCSRH_W_PERI(U8 data)
{
    m_usb_rxcsrh_w_peri.all = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,data,data);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.all);
    #endif
    return m_usb_rxcsrh_w_peri.all;
}
void GH_USB_set_RXCSRH_W_PERI_IncompRx(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.incomprx = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_IncompRx] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_PERI_IncompRx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_IncompRx] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.incomprx);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.incomprx;
}
void GH_USB_set_RXCSRH_W_PERI_DMAReqMode(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_PERI_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_DMAReqMode] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.dmareqmode);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.dmareqmode;
}
void GH_USB_set_RXCSRH_W_PERI_DisNyet_PIDError(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.disnyet_piderror = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_DisNyet_PIDError] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_PERI_DisNyet_PIDError(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_DisNyet_PIDError] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.disnyet_piderror);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.disnyet_piderror;
}
void GH_USB_set_RXCSRH_W_PERI_DMAReqEnab(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_PERI_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_DMAReqEnab] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.dmareqenab);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.dmareqenab;
}
void GH_USB_set_RXCSRH_W_PERI_ISO(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.iso = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_ISO] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_PERI_ISO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_ISO] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.iso);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.iso;
}
void GH_USB_set_RXCSRH_W_PERI_AutoClear(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.autoclear = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_AutoClear] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_PERI_AutoClear(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_AutoClear] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.autoclear);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_RXCSRL_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_RXCSRL_R_HOST_RxPktRdy(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_RxPktRdy] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
U8   GH_USB_get_RXCSRL_R_HOST_FIFOFull(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_FIFOFull] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.fifofull;
}
U8   GH_USB_get_RXCSRL_R_HOST_Error(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_Error] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.error;
}
U8   GH_USB_get_RXCSRL_R_HOST_DataError_NAKTimeout(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_DataError_NAKTimeout] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.dataerror_naktimeout;
}
U8   GH_USB_get_RXCSRL_R_HOST_ReqPkt(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_ReqPkt] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.reqpkt;
}
U8   GH_USB_get_RXCSRL_R_HOST_RxStall(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_RxStall] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.rxstall;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_RXCSRH_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_RXCSRH_R_HOST_IncompRx(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_IncompRx] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.incomprx;
}
U8   GH_USB_get_RXCSRH_R_HOST_DataToggle(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DataToggle] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.datatoggle;
}
U8   GH_USB_get_RXCSRH_R_HOST_DataToggleWriteEnable(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DataToggleWriteEnable] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.datatogglewriteenable;
}
U8   GH_USB_get_RXCSRH_R_HOST_DMAReqMode(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DMAReqMode] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
U8   GH_USB_get_RXCSRH_R_HOST_PIDError(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_PIDError] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.piderror;
}
U8   GH_USB_get_RXCSRH_R_HOST_DMAReqEnab(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
U8   GH_USB_get_RXCSRH_R_HOST_AutoReq(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_AutoReq] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.autoreq;
}
U8   GH_USB_get_RXCSRH_R_HOST_AutoClear(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_AutoClear] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_RXCSRL_W_HOST(U8 data)
{
    m_usb_rxcsrl_w_host.all = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,data,data);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.all);
    #endif
    return m_usb_rxcsrl_w_host.all;
}
void GH_USB_set_RXCSRL_W_HOST_RxPktRdy(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.rxpktrdy = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_RxPktRdy] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST_RxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_RxPktRdy] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.rxpktrdy);
    #endif
    return m_usb_rxcsrl_w_host.bitc.rxpktrdy;
}
void GH_USB_set_RXCSRL_W_HOST_Error(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.error = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_Error] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST_Error(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_Error] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.error);
    #endif
    return m_usb_rxcsrl_w_host.bitc.error;
}
void GH_USB_set_RXCSRL_W_HOST_DataError_NAKTimeout(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.dataerror_naktimeout = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_DataError_NAKTimeout] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST_DataError_NAKTimeout(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_DataError_NAKTimeout] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.dataerror_naktimeout);
    #endif
    return m_usb_rxcsrl_w_host.bitc.dataerror_naktimeout;
}
void GH_USB_set_RXCSRL_W_HOST_FlushFIFO(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_FlushFIFO] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.flushfifo);
    #endif
    return m_usb_rxcsrl_w_host.bitc.flushfifo;
}
void GH_USB_set_RXCSRL_W_HOST_ReqPkt(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.reqpkt = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_ReqPkt] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST_ReqPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_ReqPkt] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.reqpkt);
    #endif
    return m_usb_rxcsrl_w_host.bitc.reqpkt;
}
void GH_USB_set_RXCSRL_W_HOST_RxStall(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.rxstall = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_RxStall] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST_RxStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_RxStall] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.rxstall);
    #endif
    return m_usb_rxcsrl_w_host.bitc.rxstall;
}
void GH_USB_set_RXCSRL_W_HOST_ClrDataTog(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRL_W_HOST_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_ClrDataTog] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.clrdatatog);
    #endif
    return m_usb_rxcsrl_w_host.bitc.clrdatatog;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_RXCSRH_W_HOST(U8 data)
{
    m_usb_rxcsrh_w_host.all = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,data,data);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.all);
    #endif
    return m_usb_rxcsrh_w_host.all;
}
void GH_USB_set_RXCSRH_W_HOST_IncompRx(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.incomprx = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_IncompRx] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_HOST_IncompRx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_IncompRx] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.incomprx);
    #endif
    return m_usb_rxcsrh_w_host.bitc.incomprx;
}
void GH_USB_set_RXCSRH_W_HOST_DMAReqMode(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_HOST_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_DMAReqMode] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.dmareqmode);
    #endif
    return m_usb_rxcsrh_w_host.bitc.dmareqmode;
}
void GH_USB_set_RXCSRH_W_HOST_DMAReqEnab(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_HOST_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_DMAReqEnab] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.dmareqenab);
    #endif
    return m_usb_rxcsrh_w_host.bitc.dmareqenab;
}
void GH_USB_set_RXCSRH_W_HOST_AutoReq(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.autoreq = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_AutoReq] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_HOST_AutoReq(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_AutoReq] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.autoreq);
    #endif
    return m_usb_rxcsrh_w_host.bitc.autoreq;
}
void GH_USB_set_RXCSRH_W_HOST_AutoClear(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.autoclear = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_AutoClear] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
U8   GH_USB_getm_RXCSRH_W_HOST_AutoClear(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_AutoClear] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.autoclear);
    #endif
    return m_usb_rxcsrh_w_host.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RxCount (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_RxCount(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCOUNT);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxCount] --> 0x%08x\n",
                        REG_USB_RXCOUNT,value);
    #endif
    return value;
}
U8   GH_USB_get_RxCount_EndpointRxCount(void)
{
    GH_USB_RXCOUNT_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCOUNT);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxCount_EndpointRxCount] --> 0x%08x\n",
                        REG_USB_RXCOUNT,value);
    #endif
    return tmp_value.bitc.endpointrxcount;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxType_HOST (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxType_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_TXTYPE_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,data,data);
    #endif
}
U8   GH_USB_get_TxType_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return value;
}
void GH_USB_set_TxType_HOST_TargetEndpointNumber(U8 data)
{
    GH_USB_TXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXTYPE_HOST;
    d.bitc.targetendpointnumber = data;
    *(volatile U8 *)REG_USB_TXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST_TargetEndpointNumber] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxType_HOST_TargetEndpointNumber(void)
{
    GH_USB_TXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST_TargetEndpointNumber] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.targetendpointnumber;
}
void GH_USB_set_TxType_HOST_Protocol(U8 data)
{
    GH_USB_TXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXTYPE_HOST;
    d.bitc.protocol = data;
    *(volatile U8 *)REG_USB_TXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST_Protocol] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxType_HOST_Protocol(void)
{
    GH_USB_TXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST_Protocol] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.protocol;
}
void GH_USB_set_TxType_HOST_Speed(U8 data)
{
    GH_USB_TXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXTYPE_HOST;
    d.bitc.speed = data;
    *(volatile U8 *)REG_USB_TXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST_Speed] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxType_HOST_Speed(void)
{
    GH_USB_TXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST_Speed] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxInterval_HOST (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxInterval_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_TXINTERVAL_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxInterval_HOST] <-- 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,data,data);
    #endif
}
U8   GH_USB_get_TxInterval_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXINTERVAL_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxInterval_HOST] --> 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,value);
    #endif
    return value;
}
void GH_USB_set_TxInterval_HOST_TxPollingInterval_NAKLimit(U8 data)
{
    GH_USB_TXINTERVAL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXINTERVAL_HOST;
    d.bitc.txpollinginterval_naklimit = data;
    *(volatile U8 *)REG_USB_TXINTERVAL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxInterval_HOST_TxPollingInterval_NAKLimit] <-- 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxInterval_HOST_TxPollingInterval_NAKLimit(void)
{
    GH_USB_TXINTERVAL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXINTERVAL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxInterval_HOST_TxPollingInterval_NAKLimit] --> 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,value);
    #endif
    return tmp_value.bitc.txpollinginterval_naklimit;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxType_HOST (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxType_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_RXTYPE_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,data,data);
    #endif
}
U8   GH_USB_get_RxType_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return value;
}
void GH_USB_set_RxType_HOST_TargetEndpointNumber(U8 data)
{
    GH_USB_RXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXTYPE_HOST;
    d.bitc.targetendpointnumber = data;
    *(volatile U8 *)REG_USB_RXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST_TargetEndpointNumber] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxType_HOST_TargetEndpointNumber(void)
{
    GH_USB_RXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST_TargetEndpointNumber] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.targetendpointnumber;
}
void GH_USB_set_RxType_HOST_Protocol(U8 data)
{
    GH_USB_RXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXTYPE_HOST;
    d.bitc.protocol = data;
    *(volatile U8 *)REG_USB_RXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST_Protocol] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxType_HOST_Protocol(void)
{
    GH_USB_RXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST_Protocol] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.protocol;
}
void GH_USB_set_RxType_HOST_Speed(U8 data)
{
    GH_USB_RXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXTYPE_HOST;
    d.bitc.speed = data;
    *(volatile U8 *)REG_USB_RXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST_Speed] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxType_HOST_Speed(void)
{
    GH_USB_RXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST_Speed] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxInterval_HOST (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxInterval_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_RXINTERVAL_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxInterval_HOST] <-- 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,data,data);
    #endif
}
U8   GH_USB_get_RxInterval_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXINTERVAL_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxInterval_HOST] --> 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,value);
    #endif
    return value;
}
void GH_USB_set_RxInterval_HOST_RxPollingInterval_NAKLimit(U8 data)
{
    GH_USB_RXINTERVAL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXINTERVAL_HOST;
    d.bitc.rxpollinginterval_naklimit = data;
    *(volatile U8 *)REG_USB_RXINTERVAL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxInterval_HOST_RxPollingInterval_NAKLimit] <-- 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxInterval_HOST_RxPollingInterval_NAKLimit(void)
{
    GH_USB_RXINTERVAL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXINTERVAL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxInterval_HOST_RxPollingInterval_NAKLimit] --> 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,value);
    #endif
    return tmp_value.bitc.rxpollinginterval_naklimit;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FIFOSize (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_FIFOSize(void)
{
    U8 value = (*(volatile U8 *)REG_USB_FIFOSIZE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOSize] --> 0x%08x\n",
                        REG_USB_FIFOSIZE,value);
    #endif
    return value;
}
U8   GH_USB_get_FIFOSize_TxFIFOSize(void)
{
    GH_USB_FIFOSIZE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_FIFOSIZE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOSize_TxFIFOSize] --> 0x%08x\n",
                        REG_USB_FIFOSIZE,value);
    #endif
    return tmp_value.bitc.txfifosize;
}
U8   GH_USB_get_FIFOSize_RxFIFOSize(void)
{
    GH_USB_FIFOSIZE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_FIFOSIZE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOSize_RxFIFOSize] --> 0x%08x\n",
                        REG_USB_FIFOSIZE,value);
    #endif
    return tmp_value.bitc.rxfifosize;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FIFOs (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_FIFOs(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FIFOs] <-- 0x%08x\n",
                        (REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)),data,data);
    #endif
}
U8   GH_USB_get_FIFOs(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOs] --> 0x%08x\n",
                        (REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DevCtl_R (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_DevCtl_R(void)
{
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return value;
}
U8   GH_USB_get_DevCtl_R_Session(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_Session] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.session;
}
U8   GH_USB_get_DevCtl_R_Host_Req(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_Host_Req] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.host_req;
}
U8   GH_USB_get_DevCtl_R_Host_Mode(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_Host_Mode] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.host_mode;
}
U8   GH_USB_get_DevCtl_R_VBus(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_VBus] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.vbus;
}
U8   GH_USB_get_DevCtl_R_LSDev(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_LSDev] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.lsdev;
}
U8   GH_USB_get_DevCtl_R_FSDev(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_FSDev] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.fsdev;
}
U8   GH_USB_get_DevCtl_R_B_Device(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_B_Device] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.b_device;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DevCtl_W (write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_DevCtl_W(U8 data)
{
    m_usb_devctl_w.all = data;
    *(volatile U8 *)REG_USB_DEVCTL_W = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DevCtl_W] <-- 0x%08x\n",
                        REG_USB_DEVCTL_W,data,data);
    #endif
}
U8   GH_USB_getm_DevCtl_W(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_DevCtl_W] --> 0x%08x\n",
                        m_usb_devctl_w.all);
    #endif
    return m_usb_devctl_w.all;
}
void GH_USB_set_DevCtl_W_Session(U8 data)
{
    m_usb_devctl_w.bitc.session = data;
    *(volatile U8 *)REG_USB_DEVCTL_W = m_usb_devctl_w.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DevCtl_W_Session] <-- 0x%08x\n",
                        REG_USB_DEVCTL_W,m_usb_devctl_w.all,m_usb_devctl_w.all);
    #endif
}
U8   GH_USB_getm_DevCtl_W_Session(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_DevCtl_W_Session] --> 0x%08x\n",
                        m_usb_devctl_w.bitc.session);
    #endif
    return m_usb_devctl_w.bitc.session;
}
void GH_USB_set_DevCtl_W_Host_Req(U8 data)
{
    m_usb_devctl_w.bitc.host_req = data;
    *(volatile U8 *)REG_USB_DEVCTL_W = m_usb_devctl_w.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DevCtl_W_Host_Req] <-- 0x%08x\n",
                        REG_USB_DEVCTL_W,m_usb_devctl_w.all,m_usb_devctl_w.all);
    #endif
}
U8   GH_USB_getm_DevCtl_W_Host_Req(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_DevCtl_W_Host_Req] --> 0x%08x\n",
                        m_usb_devctl_w.bitc.host_req);
    #endif
    return m_usb_devctl_w.bitc.host_req;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_Misc (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_Misc(U8 data)
{
    *(volatile U8 *)REG_USB_MISC = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Misc] <-- 0x%08x\n",
                        REG_USB_MISC,data,data);
    #endif
}
U8   GH_USB_get_Misc(void)
{
    U8 value = (*(volatile U8 *)REG_USB_MISC);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Misc] --> 0x%08x\n",
                        REG_USB_MISC,value);
    #endif
    return value;
}
void GH_USB_set_Misc_rx_edma(U8 data)
{
    GH_USB_MISC_S d;
    d.all = *(volatile U8 *)REG_USB_MISC;
    d.bitc.rx_edma = data;
    *(volatile U8 *)REG_USB_MISC = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Misc_rx_edma] <-- 0x%08x\n",
                        REG_USB_MISC,d.all,d.all);
    #endif
}
U8   GH_USB_get_Misc_rx_edma(void)
{
    GH_USB_MISC_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_MISC);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Misc_rx_edma] --> 0x%08x\n",
                        REG_USB_MISC,value);
    #endif
    return tmp_value.bitc.rx_edma;
}
void GH_USB_set_Misc_tx_edma(U8 data)
{
    GH_USB_MISC_S d;
    d.all = *(volatile U8 *)REG_USB_MISC;
    d.bitc.tx_edma = data;
    *(volatile U8 *)REG_USB_MISC = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Misc_tx_edma] <-- 0x%08x\n",
                        REG_USB_MISC,d.all,d.all);
    #endif
}
U8   GH_USB_get_Misc_tx_edma(void)
{
    GH_USB_MISC_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_MISC);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Misc_tx_edma] --> 0x%08x\n",
                        REG_USB_MISC,value);
    #endif
    return tmp_value.bitc.tx_edma;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxFIFOsz (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxFIFOsz(U8 data)
{
    *(volatile U8 *)REG_USB_TXFIFOSZ = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOsz] <-- 0x%08x\n",
                        REG_USB_TXFIFOSZ,data,data);
    #endif
}
U8   GH_USB_get_TxFIFOsz(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXFIFOSZ);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOsz] --> 0x%08x\n",
                        REG_USB_TXFIFOSZ,value);
    #endif
    return value;
}
void GH_USB_set_TxFIFOsz_SZ(U8 data)
{
    GH_USB_TXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_TXFIFOSZ;
    d.bitc.sz = data;
    *(volatile U8 *)REG_USB_TXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOsz_SZ] <-- 0x%08x\n",
                        REG_USB_TXFIFOSZ,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxFIFOsz_SZ(void)
{
    GH_USB_TXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOsz_SZ] --> 0x%08x\n",
                        REG_USB_TXFIFOSZ,value);
    #endif
    return tmp_value.bitc.sz;
}
void GH_USB_set_TxFIFOsz_DPB(U8 data)
{
    GH_USB_TXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_TXFIFOSZ;
    d.bitc.dpb = data;
    *(volatile U8 *)REG_USB_TXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOsz_DPB] <-- 0x%08x\n",
                        REG_USB_TXFIFOSZ,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxFIFOsz_DPB(void)
{
    GH_USB_TXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOsz_DPB] --> 0x%08x\n",
                        REG_USB_TXFIFOSZ,value);
    #endif
    return tmp_value.bitc.dpb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxFIFOsz (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxFIFOsz(U8 data)
{
    *(volatile U8 *)REG_USB_RXFIFOSZ = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOsz] <-- 0x%08x\n",
                        REG_USB_RXFIFOSZ,data,data);
    #endif
}
U8   GH_USB_get_RxFIFOsz(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXFIFOSZ);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOsz] --> 0x%08x\n",
                        REG_USB_RXFIFOSZ,value);
    #endif
    return value;
}
void GH_USB_set_RxFIFOsz_SZ(U8 data)
{
    GH_USB_RXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_RXFIFOSZ;
    d.bitc.sz = data;
    *(volatile U8 *)REG_USB_RXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOsz_SZ] <-- 0x%08x\n",
                        REG_USB_RXFIFOSZ,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxFIFOsz_SZ(void)
{
    GH_USB_RXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOsz_SZ] --> 0x%08x\n",
                        REG_USB_RXFIFOSZ,value);
    #endif
    return tmp_value.bitc.sz;
}
void GH_USB_set_RxFIFOsz_DPB(U8 data)
{
    GH_USB_RXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_RXFIFOSZ;
    d.bitc.dpb = data;
    *(volatile U8 *)REG_USB_RXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOsz_DPB] <-- 0x%08x\n",
                        REG_USB_RXFIFOSZ,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxFIFOsz_DPB(void)
{
    GH_USB_RXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOsz_DPB] --> 0x%08x\n",
                        REG_USB_RXFIFOSZ,value);
    #endif
    return tmp_value.bitc.dpb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxFIFOadd (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxFIFOadd(U16 data)
{
    *(volatile U16 *)REG_USB_TXFIFOADD = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOadd] <-- 0x%08x\n",
                        REG_USB_TXFIFOADD,data,data);
    #endif
}
U16  GH_USB_get_TxFIFOadd(void)
{
    U16 value = (*(volatile U16 *)REG_USB_TXFIFOADD);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOadd] --> 0x%08x\n",
                        REG_USB_TXFIFOADD,value);
    #endif
    return value;
}
void GH_USB_set_TxFIFOadd_Startaddress(U16 data)
{
    GH_USB_TXFIFOADD_S d;
    d.all = *(volatile U16 *)REG_USB_TXFIFOADD;
    d.bitc.startaddress = data;
    *(volatile U16 *)REG_USB_TXFIFOADD = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOadd_Startaddress] <-- 0x%08x\n",
                        REG_USB_TXFIFOADD,d.all,d.all);
    #endif
}
U16  GH_USB_get_TxFIFOadd_Startaddress(void)
{
    GH_USB_TXFIFOADD_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXFIFOADD);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOadd_Startaddress] --> 0x%08x\n",
                        REG_USB_TXFIFOADD,value);
    #endif
    return tmp_value.bitc.startaddress;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxFIFOadd (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxFIFOadd(U16 data)
{
    *(volatile U16 *)REG_USB_RXFIFOADD = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOadd] <-- 0x%08x\n",
                        REG_USB_RXFIFOADD,data,data);
    #endif
}
U16  GH_USB_get_RxFIFOadd(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RXFIFOADD);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOadd] --> 0x%08x\n",
                        REG_USB_RXFIFOADD,value);
    #endif
    return value;
}
void GH_USB_set_RxFIFOadd_Startaddress(U16 data)
{
    GH_USB_RXFIFOADD_S d;
    d.all = *(volatile U16 *)REG_USB_RXFIFOADD;
    d.bitc.startaddress = data;
    *(volatile U16 *)REG_USB_RXFIFOADD = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOadd_Startaddress] <-- 0x%08x\n",
                        REG_USB_RXFIFOADD,d.all,d.all);
    #endif
}
U16  GH_USB_get_RxFIFOadd_Startaddress(void)
{
    GH_USB_RXFIFOADD_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXFIFOADD);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOadd_Startaddress] --> 0x%08x\n",
                        REG_USB_RXFIFOADD,value);
    #endif
    return tmp_value.bitc.startaddress;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_VStatus (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_USB_get_VStatus(void)
{
    U32 value = (*(volatile U32 *)REG_USB_VSTATUS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_VStatus] --> 0x%08x\n",
                        REG_USB_VSTATUS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_VControl (write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_USB_set_VControl(U32 data)
{
    m_usb_vcontrol = data;
    *(volatile U32 *)REG_USB_VCONTROL = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_VControl] <-- 0x%08x\n",
                        REG_USB_VCONTROL,data,data);
    #endif
}
U32  GH_USB_getm_VControl(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_VControl] --> 0x%08x\n",
                        m_usb_vcontrol);
    #endif
    return m_usb_vcontrol;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_HWVers (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_USB_get_HWVers(void)
{
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return value;
}
U16  GH_USB_get_HWVers_MinorVersion(void)
{
    GH_USB_HWVERS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers_MinorVersion] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return tmp_value.bitc.minorversion;
}
U8   GH_USB_get_HWVers_MajorVersion(void)
{
    GH_USB_HWVERS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers_MajorVersion] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return tmp_value.bitc.majorversion;
}
U8   GH_USB_get_HWVers_RC(void)
{
    GH_USB_HWVERS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers_RC] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return tmp_value.bitc.rc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_EPInfo (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_EPInfo(void)
{
    U8 value = (*(volatile U8 *)REG_USB_EPINFO);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_EPInfo] --> 0x%08x\n",
                        REG_USB_EPINFO,value);
    #endif
    return value;
}
U8   GH_USB_get_EPInfo_TxEndPoints(void)
{
    GH_USB_EPINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_EPINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_EPInfo_TxEndPoints] --> 0x%08x\n",
                        REG_USB_EPINFO,value);
    #endif
    return tmp_value.bitc.txendpoints;
}
U8   GH_USB_get_EPInfo_RxEndPoints(void)
{
    GH_USB_EPINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_EPINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_EPInfo_RxEndPoints] --> 0x%08x\n",
                        REG_USB_EPINFO,value);
    #endif
    return tmp_value.bitc.rxendpoints;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RAMInfo (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_RAMInfo(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RAMINFO);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RAMInfo] --> 0x%08x\n",
                        REG_USB_RAMINFO,value);
    #endif
    return value;
}
U8   GH_USB_get_RAMInfo_RamBits(void)
{
    GH_USB_RAMINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RAMINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RAMInfo_RamBits] --> 0x%08x\n",
                        REG_USB_RAMINFO,value);
    #endif
    return tmp_value.bitc.rambits;
}
U8   GH_USB_get_RAMInfo_DMAChans(void)
{
    GH_USB_RAMINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RAMINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RAMInfo_DMAChans] --> 0x%08x\n",
                        REG_USB_RAMINFO,value);
    #endif
    return tmp_value.bitc.dmachans;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LinkInfo (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_LinkInfo(U8 data)
{
    *(volatile U8 *)REG_USB_LINKINFO = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LinkInfo] <-- 0x%08x\n",
                        REG_USB_LINKINFO,data,data);
    #endif
}
U8   GH_USB_get_LinkInfo(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LINKINFO);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LinkInfo] --> 0x%08x\n",
                        REG_USB_LINKINFO,value);
    #endif
    return value;
}
void GH_USB_set_LinkInfo_WTID(U8 data)
{
    GH_USB_LINKINFO_S d;
    d.all = *(volatile U8 *)REG_USB_LINKINFO;
    d.bitc.wtid = data;
    *(volatile U8 *)REG_USB_LINKINFO = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LinkInfo_WTID] <-- 0x%08x\n",
                        REG_USB_LINKINFO,d.all,d.all);
    #endif
}
U8   GH_USB_get_LinkInfo_WTID(void)
{
    GH_USB_LINKINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LINKINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LinkInfo_WTID] --> 0x%08x\n",
                        REG_USB_LINKINFO,value);
    #endif
    return tmp_value.bitc.wtid;
}
void GH_USB_set_LinkInfo_WTCON(U8 data)
{
    GH_USB_LINKINFO_S d;
    d.all = *(volatile U8 *)REG_USB_LINKINFO;
    d.bitc.wtcon = data;
    *(volatile U8 *)REG_USB_LINKINFO = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LinkInfo_WTCON] <-- 0x%08x\n",
                        REG_USB_LINKINFO,d.all,d.all);
    #endif
}
U8   GH_USB_get_LinkInfo_WTCON(void)
{
    GH_USB_LINKINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LINKINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LinkInfo_WTCON] --> 0x%08x\n",
                        REG_USB_LINKINFO,value);
    #endif
    return tmp_value.bitc.wtcon;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_VPLen (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_VPLen(U8 data)
{
    *(volatile U8 *)REG_USB_VPLEN = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_VPLen] <-- 0x%08x\n",
                        REG_USB_VPLEN,data,data);
    #endif
}
U8   GH_USB_get_VPLen(void)
{
    U8 value = (*(volatile U8 *)REG_USB_VPLEN);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_VPLen] --> 0x%08x\n",
                        REG_USB_VPLEN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_HS_EOF1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_HS_EOF1(U8 data)
{
    *(volatile U8 *)REG_USB_HS_EOF1 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_HS_EOF1] <-- 0x%08x\n",
                        REG_USB_HS_EOF1,data,data);
    #endif
}
U8   GH_USB_get_HS_EOF1(void)
{
    U8 value = (*(volatile U8 *)REG_USB_HS_EOF1);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HS_EOF1] --> 0x%08x\n",
                        REG_USB_HS_EOF1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FS_EOF1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_FS_EOF1(U8 data)
{
    *(volatile U8 *)REG_USB_FS_EOF1 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FS_EOF1] <-- 0x%08x\n",
                        REG_USB_FS_EOF1,data,data);
    #endif
}
U8   GH_USB_get_FS_EOF1(void)
{
    U8 value = (*(volatile U8 *)REG_USB_FS_EOF1);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FS_EOF1] --> 0x%08x\n",
                        REG_USB_FS_EOF1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LS_EOF1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_LS_EOF1(U8 data)
{
    *(volatile U8 *)REG_USB_LS_EOF1 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LS_EOF1] <-- 0x%08x\n",
                        REG_USB_LS_EOF1,data,data);
    #endif
}
U8   GH_USB_get_LS_EOF1(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LS_EOF1);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LS_EOF1] --> 0x%08x\n",
                        REG_USB_LS_EOF1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_SOFT_RST (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_SOFT_RST(U8 data)
{
    *(volatile U8 *)REG_USB_SOFT_RST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_SOFT_RST] <-- 0x%08x\n",
                        REG_USB_SOFT_RST,data,data);
    #endif
}
U8   GH_USB_get_SOFT_RST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_SOFT_RST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_SOFT_RST] --> 0x%08x\n",
                        REG_USB_SOFT_RST,value);
    #endif
    return value;
}
void GH_USB_set_SOFT_RST_NRST(U8 data)
{
    GH_USB_SOFT_RST_S d;
    d.all = *(volatile U8 *)REG_USB_SOFT_RST;
    d.bitc.nrst = data;
    *(volatile U8 *)REG_USB_SOFT_RST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_SOFT_RST_NRST] <-- 0x%08x\n",
                        REG_USB_SOFT_RST,d.all,d.all);
    #endif
}
U8   GH_USB_get_SOFT_RST_NRST(void)
{
    GH_USB_SOFT_RST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_SOFT_RST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_SOFT_RST_NRST] --> 0x%08x\n",
                        REG_USB_SOFT_RST,value);
    #endif
    return tmp_value.bitc.nrst;
}
void GH_USB_set_SOFT_RST_NRSTX(U8 data)
{
    GH_USB_SOFT_RST_S d;
    d.all = *(volatile U8 *)REG_USB_SOFT_RST;
    d.bitc.nrstx = data;
    *(volatile U8 *)REG_USB_SOFT_RST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_SOFT_RST_NRSTX] <-- 0x%08x\n",
                        REG_USB_SOFT_RST,d.all,d.all);
    #endif
}
U8   GH_USB_get_SOFT_RST_NRSTX(void)
{
    GH_USB_SOFT_RST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_SOFT_RST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_SOFT_RST_NRSTX] --> 0x%08x\n",
                        REG_USB_SOFT_RST,value);
    #endif
    return tmp_value.bitc.nrstx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxFuncAddr (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxFuncAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFuncAddr] <-- 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
U8   GH_USB_get_TxFuncAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFuncAddr] --> 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
void GH_USB_set_TxFuncAddr_AddressofTargetFunction(U8 index, U8 data)
{
    GH_USB_TXFUNCADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.addressoftargetfunction = data;
    *(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFuncAddr_AddressofTargetFunction] <-- 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_TxFuncAddr_AddressofTargetFunction(U8 index)
{
    GH_USB_TXFUNCADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFuncAddr_AddressofTargetFunction] --> 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.addressoftargetfunction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxHubAddr (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxHubAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubAddr] <-- 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
U8   GH_USB_get_TxHubAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubAddr] --> 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
void GH_USB_set_TxHubAddr_HubAddress(U8 index, U8 data)
{
    GH_USB_TXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubaddress = data;
    *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubAddr_HubAddress] <-- 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_TxHubAddr_HubAddress(U8 index)
{
    GH_USB_TXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubAddr_HubAddress] --> 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubaddress;
}
void GH_USB_set_TxHubAddr_MultipleTranslators(U8 index, U8 data)
{
    GH_USB_TXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.multipletranslators = data;
    *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubAddr_MultipleTranslators] <-- 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_TxHubAddr_MultipleTranslators(U8 index)
{
    GH_USB_TXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubAddr_MultipleTranslators] --> 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.multipletranslators;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxHubPort (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxHubPort(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubPort] <-- 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
U8   GH_USB_get_TxHubPort(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubPort] --> 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
void GH_USB_set_TxHubPort_HubPort(U8 index, U8 data)
{
    GH_USB_TXHUBPORT_S d;
    d.all = *(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubport = data;
    *(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubPort_HubPort] <-- 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_TxHubPort_HubPort(U8 index)
{
    GH_USB_TXHUBPORT_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubPort_HubPort] --> 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubport;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxFuncAddr (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxFuncAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFuncAddr] <-- 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
U8   GH_USB_get_RxFuncAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFuncAddr] --> 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
void GH_USB_set_RxFuncAddr_AddressofTargetFunction(U8 index, U8 data)
{
    GH_USB_RXFUNCADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.addressoftargetfunction = data;
    *(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFuncAddr_AddressofTargetFunction] <-- 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_RxFuncAddr_AddressofTargetFunction(U8 index)
{
    GH_USB_RXFUNCADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFuncAddr_AddressofTargetFunction] --> 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.addressoftargetfunction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxHubAddr (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxHubAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubAddr] <-- 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
U8   GH_USB_get_RxHubAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubAddr] --> 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
void GH_USB_set_RxHubAddr_HubAddress(U8 index, U8 data)
{
    GH_USB_RXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubaddress = data;
    *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubAddr_HubAddress] <-- 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_RxHubAddr_HubAddress(U8 index)
{
    GH_USB_RXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubAddr_HubAddress] --> 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubaddress;
}
void GH_USB_set_RxHubAddr_MultipleTranslators(U8 index, U8 data)
{
    GH_USB_RXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.multipletranslators = data;
    *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubAddr_MultipleTranslators] <-- 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_RxHubAddr_MultipleTranslators(U8 index)
{
    GH_USB_RXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubAddr_MultipleTranslators] --> 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.multipletranslators;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxHubPort (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxHubPort(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubPort] <-- 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
U8   GH_USB_get_RxHubPort(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubPort] --> 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
void GH_USB_set_RxHubPort_HubPort(U8 index, U8 data)
{
    GH_USB_RXHUBPORT_S d;
    d.all = *(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubport = data;
    *(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubPort_HubPort] <-- 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
U8   GH_USB_get_RxHubPort_HubPort(U8 index)
{
    GH_USB_RXHUBPORT_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubPort_HubPort] --> 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubport;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_INTR (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_DMA_INTR(U8 data)
{
    *(volatile U8 *)REG_USB_DMA_INTR = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,data,data);
    #endif
}
U8   GH_USB_get_DMA_INTR(void)
{
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return value;
}
void GH_USB_set_DMA_INTR_CH0(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch0 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH0] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH0(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH0] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch0;
}
void GH_USB_set_DMA_INTR_CH1(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch1 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH1] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH1(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH1] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch1;
}
void GH_USB_set_DMA_INTR_CH2(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch2 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH2] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH2(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH2] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch2;
}
void GH_USB_set_DMA_INTR_CH3(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch3 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH3] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH3(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH3] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch3;
}
void GH_USB_set_DMA_INTR_CH4(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch4 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH4] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH4(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH4] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch4;
}
void GH_USB_set_DMA_INTR_CH5(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch5 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH5] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH5(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH5] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch5;
}
void GH_USB_set_DMA_INTR_CH6(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch6 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH6] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH6(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH6] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch6;
}
void GH_USB_set_DMA_INTR_CH7(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch7 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH7] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_INTR_CH7(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH7] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_CNTL (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_DMA_CNTL(U8 index, U16 data)
{
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),data,data);
    #endif
}
U16  GH_USB_get_DMA_CNTL(U8 index)
{
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return value;
}
void GH_USB_set_DMA_CNTL_DMA_ENAB(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_enab = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_ENAB] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_CNTL_DMA_ENAB(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_ENAB] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_enab;
}
void GH_USB_set_DMA_CNTL_DMA_DIR(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_dir = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_DIR] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_CNTL_DMA_DIR(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_DIR] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_dir;
}
void GH_USB_set_DMA_CNTL_DMAMODE(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dmamode = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMAMODE] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_CNTL_DMAMODE(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMAMODE] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dmamode;
}
void GH_USB_set_DMA_CNTL_DMAIE(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dmaie = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMAIE] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_CNTL_DMAIE(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMAIE] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dmaie;
}
void GH_USB_set_DMA_CNTL_DMAEP(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dmaep = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMAEP] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_CNTL_DMAEP(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMAEP] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dmaep;
}
void GH_USB_set_DMA_CNTL_DMA_ERR(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_err = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_ERR] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_CNTL_DMA_ERR(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_ERR] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_err;
}
void GH_USB_set_DMA_CNTL_DMA_BRSTM(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_brstm = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_BRSTM] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_USB_get_DMA_CNTL_DMA_BRSTM(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_BRSTM] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_brstm;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_ADDR (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_DMA_ADDR(U8 index, U32 data)
{
    *(volatile U32 *)(REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_ADDR] <-- 0x%08x\n",
                        (REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)),data,data);
    #endif
}
U32  GH_USB_get_DMA_ADDR(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_ADDR] --> 0x%08x\n",
                        (REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_COUNT (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_DMA_COUNT(U8 index, U32 data)
{
    *(volatile U32 *)(REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_COUNT] <-- 0x%08x\n",
                        (REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)),data,data);
    #endif
}
U32  GH_USB_get_DMA_COUNT(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_COUNT] --> 0x%08x\n",
                        (REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RqPktCount_HOST (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RqPktCount_HOST(U16 data)
{
    *(volatile U16 *)REG_USB_RQPKTCOUNT_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RqPktCount_HOST] <-- 0x%08x\n",
                        REG_USB_RQPKTCOUNT_HOST,data,data);
    #endif
}
U16  GH_USB_get_RqPktCount_HOST(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RQPKTCOUNT_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RqPktCount_HOST] --> 0x%08x\n",
                        REG_USB_RQPKTCOUNT_HOST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxDPktBufDis (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_RxDPktBufDis(U16 data)
{
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,data,data);
    #endif
}
U16  GH_USB_get_RxDPktBufDis(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return value;
}
void GH_USB_set_RxDPktBufDis_EP1(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep1 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP1] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP1(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP1] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep1;
}
void GH_USB_set_RxDPktBufDis_EP2(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep2 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP2] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP2(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP2] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep2;
}
void GH_USB_set_RxDPktBufDis_EP3(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep3 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP3] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP3(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP3] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep3;
}
void GH_USB_set_RxDPktBufDis_EP4(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep4 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP4] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP4(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP4] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep4;
}
void GH_USB_set_RxDPktBufDis_EP5(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep5 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP5] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP5(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP5] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep5;
}
void GH_USB_set_RxDPktBufDis_EP6(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep6 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP6] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP6(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP6] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep6;
}
void GH_USB_set_RxDPktBufDis_EP7(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep7 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP7] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP7(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP7] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep7;
}
void GH_USB_set_RxDPktBufDis_EP8(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep8 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP8] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP8(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP8] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep8;
}
void GH_USB_set_RxDPktBufDis_EP9(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep9 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP9] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP9(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP9] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep9;
}
void GH_USB_set_RxDPktBufDis_EP10(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep10 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP10] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP10(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP10] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep10;
}
void GH_USB_set_RxDPktBufDis_EP11(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep11 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP11] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP11(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP11] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep11;
}
void GH_USB_set_RxDPktBufDis_EP12(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep12 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP12] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP12(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP12] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep12;
}
void GH_USB_set_RxDPktBufDis_EP13(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep13 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP13] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP13(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP13] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep13;
}
void GH_USB_set_RxDPktBufDis_EP14(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep14 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP14] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP14(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP14] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep14;
}
void GH_USB_set_RxDPktBufDis_EP15(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep15 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP15] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_RxDPktBufDis_EP15(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP15] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep15;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxDPktBufDis (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_TxDPktBufDis(U16 data)
{
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,data,data);
    #endif
}
U16  GH_USB_get_TxDPktBufDis(void)
{
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return value;
}
void GH_USB_set_TxDPktBufDis_EP1(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep1 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP1] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP1(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP1] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep1;
}
void GH_USB_set_TxDPktBufDis_EP2(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep2 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP2] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP2(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP2] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep2;
}
void GH_USB_set_TxDPktBufDis_EP3(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep3 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP3] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP3(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP3] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep3;
}
void GH_USB_set_TxDPktBufDis_EP4(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep4 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP4] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP4(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP4] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep4;
}
void GH_USB_set_TxDPktBufDis_EP5(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep5 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP5] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP5(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP5] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep5;
}
void GH_USB_set_TxDPktBufDis_EP6(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep6 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP6] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP6(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP6] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep6;
}
void GH_USB_set_TxDPktBufDis_EP7(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep7 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP7] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP7(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP7] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep7;
}
void GH_USB_set_TxDPktBufDis_EP8(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep8 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP8] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP8(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP8] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep8;
}
void GH_USB_set_TxDPktBufDis_EP9(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep9 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP9] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP9(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP9] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep9;
}
void GH_USB_set_TxDPktBufDis_EP10(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep10 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP10] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP10(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP10] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep10;
}
void GH_USB_set_TxDPktBufDis_EP11(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep11 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP11] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP11(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP11] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep11;
}
void GH_USB_set_TxDPktBufDis_EP12(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep12 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP12] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP12(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP12] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep12;
}
void GH_USB_set_TxDPktBufDis_EP13(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep13 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP13] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP13(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP13] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep13;
}
void GH_USB_set_TxDPktBufDis_EP14(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep14 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP14] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP14(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP14] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep14;
}
void GH_USB_set_TxDPktBufDis_EP15(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep15 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP15] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
U8   GH_USB_get_TxDPktBufDis_EP15(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP15] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep15;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_C_T_UCH (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_C_T_UCH(U16 data)
{
    *(volatile U16 *)REG_USB_C_T_UCH = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_UCH] <-- 0x%08x\n",
                        REG_USB_C_T_UCH,data,data);
    #endif
}
U16  GH_USB_get_C_T_UCH(void)
{
    U16 value = (*(volatile U16 *)REG_USB_C_T_UCH);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_UCH] --> 0x%08x\n",
                        REG_USB_C_T_UCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_C_T_HSRTN (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_C_T_HSRTN(U16 data)
{
    *(volatile U16 *)REG_USB_C_T_HSRTN = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_HSRTN] <-- 0x%08x\n",
                        REG_USB_C_T_HSRTN,data,data);
    #endif
}
U16  GH_USB_get_C_T_HSRTN(void)
{
    U16 value = (*(volatile U16 *)REG_USB_C_T_HSRTN);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_HSRTN] --> 0x%08x\n",
                        REG_USB_C_T_HSRTN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_C_T_HSBT (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_C_T_HSBT(U8 data)
{
    *(volatile U8 *)REG_USB_C_T_HSBT = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_HSBT] <-- 0x%08x\n",
                        REG_USB_C_T_HSBT,data,data);
    #endif
}
U8   GH_USB_get_C_T_HSBT(void)
{
    U8 value = (*(volatile U8 *)REG_USB_C_T_HSBT);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_HSBT] --> 0x%08x\n",
                        REG_USB_C_T_HSBT,value);
    #endif
    return value;
}
void GH_USB_set_C_T_HSBT_HSTimeoutAdder(U8 data)
{
    GH_USB_C_T_HSBT_S d;
    d.all = *(volatile U8 *)REG_USB_C_T_HSBT;
    d.bitc.hstimeoutadder = data;
    *(volatile U8 *)REG_USB_C_T_HSBT = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_HSBT_HSTimeoutAdder] <-- 0x%08x\n",
                        REG_USB_C_T_HSBT,d.all,d.all);
    #endif
}
U8   GH_USB_get_C_T_HSBT_HSTimeoutAdder(void)
{
    GH_USB_C_T_HSBT_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_C_T_HSBT);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_HSBT_HSTimeoutAdder] --> 0x%08x\n",
                        REG_USB_C_T_HSBT,value);
    #endif
    return tmp_value.bitc.hstimeoutadder;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_ATTR (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_USB_get_LPM_ATTR(void)
{
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return value;
}
U8   GH_USB_get_LPM_ATTR_LinkState(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_LinkState] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.linkstate;
}
U8   GH_USB_get_LPM_ATTR_HIRD(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_HIRD] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.hird;
}
U8   GH_USB_get_LPM_ATTR_RmtWak(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_RmtWak] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.rmtwak;
}
U8   GH_USB_get_LPM_ATTR_EndPnt(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_EndPnt] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.endpnt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_CNTRL_PERI (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_LPM_CNTRL_PERI(U8 data)
{
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,data,data);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return value;
}
void GH_USB_set_LPM_CNTRL_PERI_LPMXMT(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmxmt = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMXMT] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_PERI_LPMXMT(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMXMT] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmxmt;
}
void GH_USB_set_LPM_CNTRL_PERI_LPMRES(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmres = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMRES] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_PERI_LPMRES(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmres;
}
void GH_USB_set_LPM_CNTRL_PERI_LPMEN(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmen = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMEN] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_PERI_LPMEN(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMEN] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmen;
}
void GH_USB_set_LPM_CNTRL_PERI_LPMNAK(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmnak = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMNAK] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_PERI_LPMNAK(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMNAK] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmnak;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_CNTRL_HOST (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_LPM_CNTRL_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_LPM_CNTRL_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_HOST] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,data,data);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_HOST] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,value);
    #endif
    return value;
}
void GH_USB_set_LPM_CNTRL_HOST_LPMXMT(U8 data)
{
    GH_USB_LPM_CNTRL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_HOST;
    d.bitc.lpmxmt = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_HOST_LPMXMT] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_HOST_LPMXMT(void)
{
    GH_USB_LPM_CNTRL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_HOST_LPMXMT] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,value);
    #endif
    return tmp_value.bitc.lpmxmt;
}
void GH_USB_set_LPM_CNTRL_HOST_LPMRES(U8 data)
{
    GH_USB_LPM_CNTRL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_HOST;
    d.bitc.lpmres = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_HOST_LPMRES] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_CNTRL_HOST_LPMRES(void)
{
    GH_USB_LPM_CNTRL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_HOST_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,value);
    #endif
    return tmp_value.bitc.lpmres;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_INTREN (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_LPM_INTREN(U8 data)
{
    *(volatile U8 *)REG_USB_LPM_INTREN = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,data,data);
    #endif
}
U8   GH_USB_get_LPM_INTREN(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return value;
}
void GH_USB_set_LPM_INTREN_LPMSTEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmsten = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMSTEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_INTREN_LPMSTEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMSTEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmsten;
}
void GH_USB_set_LPM_INTREN_LPMNYEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmnyen = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMNYEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_INTREN_LPMNYEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMNYEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmnyen;
}
void GH_USB_set_LPM_INTREN_LPMACKEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmacken = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMACKEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_INTREN_LPMACKEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMACKEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmacken;
}
void GH_USB_set_LPM_INTREN_LPMNCEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmncen = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMNCEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_INTREN_LPMNCEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMNCEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmncen;
}
void GH_USB_set_LPM_INTREN_LPMRESEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmresen = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMRESEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_INTREN_LPMRESEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMRESEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmresen;
}
void GH_USB_set_LPM_INTREN_LPMERREN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmerren = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMERREN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
U8   GH_USB_get_LPM_INTREN_LPMERREN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMERREN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmerren;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_INTR_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_LPM_INTR_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return value;
}
U8   GH_USB_get_LPM_INTR_PERI_LPMST(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMST] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmst;
}
U8   GH_USB_get_LPM_INTR_PERI_LPMNY(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMNY] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmny;
}
U8   GH_USB_get_LPM_INTR_PERI_LPMACK(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMACK] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmack;
}
U8   GH_USB_get_LPM_INTR_PERI_LPMNC(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMNC] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmnc;
}
U8   GH_USB_get_LPM_INTR_PERI_LPMRES(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmres;
}
U8   GH_USB_get_LPM_INTR_PERI_LPMERR(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMERR] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmerr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_INTR_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_LPM_INTR_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_LPM_INTR_HOST_LPMST(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMST] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmst;
}
U8   GH_USB_get_LPM_INTR_HOST_LPMNY(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMNY] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmny;
}
U8   GH_USB_get_LPM_INTR_HOST_LPMACK(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMACK] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmack;
}
U8   GH_USB_get_LPM_INTR_HOST_LPMNC(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMNC] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmnc;
}
U8   GH_USB_get_LPM_INTR_HOST_LPMRES(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmres;
}
U8   GH_USB_get_LPM_INTR_HOST_LPMERR(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMERR] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmerr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_FADDR_HOST (read)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_USB_get_LPM_FADDR_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_FADDR_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_FADDR_HOST] --> 0x%08x\n",
                        REG_USB_LPM_FADDR_HOST,value);
    #endif
    return value;
}
U8   GH_USB_get_LPM_FADDR_HOST_LPMFADDR(void)
{
    GH_USB_LPM_FADDR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_FADDR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_FADDR_HOST_LPMFADDR] --> 0x%08x\n",
                        REG_USB_LPM_FADDR_HOST,value);
    #endif
    return tmp_value.bitc.lpmfaddr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FIFOs_U32 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_set_FIFOs_U32(U8 index, U32 data)
{
    *(volatile U32 *)(REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FIFOs_U32] <-- 0x%08x\n",
                        (REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)),data,data);
    #endif
}
U32  GH_USB_get_FIFOs_U32(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOs_U32] --> 0x%08x\n",
                        (REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_USB_init(void)
{
    int i;

    GH_USB_set_FAddr((U8)0x00000000);
    GH_USB_set_Power_W_PERI((U8)0x00000000);
    GH_USB_set_Power_W_HOST((U8)0x00000000);
    GH_USB_set_IntrTxE((U16)0x00000000);
    GH_USB_set_IntrRxE((U16)0x00000000);
    GH_USB_set_IntrUSBE((U8)0x00000000);
    GH_USB_set_Index((U8)0x00000000);
    GH_USB_set_Testmode((U8)0x00000000);
    GH_USB_set_CSR0L_W_PERI((U8)0x00000000);
    GH_USB_set_CSR0H_W_PERI((U8)0x00000000);
    GH_USB_set_CSR0L_W_HOST((U8)0x00000000);
    GH_USB_set_CSR0H_W_HOST((U8)0x00000000);
    GH_USB_set_Type0((U8)0x00000000);
    GH_USB_set_NAKLimit0_HOST((U8)0x00000000);
    GH_USB_set_TxMaxP((U16)0x00000000);
    GH_USB_set_TXCSRL_W_PERI((U8)0x00000000);
    GH_USB_set_TXCSRH_W_PERI((U8)0x00000000);
    GH_USB_set_TXCSRL_W_HOST((U8)0x00000000);
    GH_USB_set_TXCSRH_W_HOST((U8)0x00000000);
    GH_USB_set_RxMaxP((U16)0x00000000);
    GH_USB_set_RXCSRL_W_PERI((U8)0x00000000);
    GH_USB_set_RXCSRH_W_PERI((U8)0x00000000);
    GH_USB_set_RXCSRL_W_HOST((U8)0x00000000);
    GH_USB_set_RXCSRH_W_HOST((U8)0x00000000);
    GH_USB_set_TxType_HOST((U8)0x00000000);
    GH_USB_set_TxInterval_HOST((U8)0x00000000);
    GH_USB_set_RxType_HOST((U8)0x00000000);
    GH_USB_set_RxInterval_HOST((U8)0x00000000);
    for (i=0; i<16; i++)
    {
        GH_USB_set_FIFOs(i, (U8)0x00000000);
    }
    GH_USB_set_DevCtl_W((U8)0x00000000);
    GH_USB_set_Misc((U8)0x00000000);
    GH_USB_set_TxFIFOsz((U8)0x00000000);
    GH_USB_set_RxFIFOsz((U8)0x00000000);
    GH_USB_set_TxFIFOadd((U16)0x00000000);
    GH_USB_set_RxFIFOadd((U16)0x00000000);
    GH_USB_set_VControl((U32)0x00000000);
    GH_USB_set_LinkInfo((U8)0x00000000);
    GH_USB_set_VPLen((U8)0x00000000);
    GH_USB_set_HS_EOF1((U8)0x00000000);
    GH_USB_set_FS_EOF1((U8)0x00000000);
    GH_USB_set_LS_EOF1((U8)0x00000000);
    GH_USB_set_SOFT_RST((U8)0x00000000);
    for (i=0; i<16; i++)
    {
        GH_USB_set_TxFuncAddr(i, (U8)0x00000000);
    }
    for (i=0; i<16; i++)
    {
        GH_USB_set_TxHubAddr(i, (U8)0x00000000);
    }
    for (i=0; i<16; i++)
    {
        GH_USB_set_TxHubPort(i, (U8)0x00000000);
    }
    for (i=0; i<16; i++)
    {
        GH_USB_set_RxFuncAddr(i, (U8)0x00000000);
    }
    for (i=0; i<16; i++)
    {
        GH_USB_set_RxHubAddr(i, (U8)0x00000000);
    }
    for (i=0; i<16; i++)
    {
        GH_USB_set_RxHubPort(i, (U8)0x00000000);
    }
    GH_USB_set_DMA_INTR((U8)0x00000000);
    for (i=0; i<8; i++)
    {
        GH_USB_set_DMA_CNTL(i, (U16)0x00000000);
    }
    for (i=0; i<8; i++)
    {
        GH_USB_set_DMA_ADDR(i, (U32)0x00000000);
    }
    for (i=0; i<8; i++)
    {
        GH_USB_set_DMA_COUNT(i, (U32)0x00000000);
    }
    GH_USB_set_RqPktCount_HOST((U16)0x00000000);
    GH_USB_set_RxDPktBufDis((U16)0x00000000);
    GH_USB_set_TxDPktBufDis((U16)0x00000000);
    GH_USB_set_C_T_UCH((U16)0x00000000);
    GH_USB_set_C_T_HSRTN((U16)0x00000000);
    GH_USB_set_C_T_HSBT((U8)0x00000000);
    GH_USB_set_LPM_CNTRL_PERI((U8)0x00000000);
    GH_USB_set_LPM_CNTRL_HOST((U8)0x00000000);
    GH_USB_set_LPM_INTREN((U8)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

