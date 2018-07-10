/******************************************************************************
**
** \file      gh_usb_phy.c
**
** \brief     USB_PHY.
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
#include "gh_usb_phy.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register USB_PHY_Tx_Config (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_Tx_Config(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_TX_CONFIG = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Config] <-- 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,data,data);
    #endif
}
U16  GH_USB_PHY_get_Tx_Config(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_CONFIG);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Config] --> 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,value);
    #endif
    return value;
}
void GH_USB_PHY_set_Tx_Config_tx_dma_blk(U8 data)
{
    GH_USB_PHY_TX_CONFIG_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_TX_CONFIG;
    d.bitc.tx_dma_blk = data;
    *(volatile U16 *)REG_USB_PHY_TX_CONFIG = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Config_tx_dma_blk] <-- 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_Tx_Config_tx_dma_blk(void)
{
    GH_USB_PHY_TX_CONFIG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_CONFIG);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Config_tx_dma_blk] --> 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,value);
    #endif
    return tmp_value.bitc.tx_dma_blk;
}
void GH_USB_PHY_set_Tx_Config_tx_ack_ignore(U8 data)
{
    GH_USB_PHY_TX_CONFIG_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_TX_CONFIG;
    d.bitc.tx_ack_ignore = data;
    *(volatile U16 *)REG_USB_PHY_TX_CONFIG = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Config_tx_ack_ignore] <-- 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_Tx_Config_tx_ack_ignore(void)
{
    GH_USB_PHY_TX_CONFIG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_CONFIG);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Config_tx_ack_ignore] --> 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,value);
    #endif
    return tmp_value.bitc.tx_ack_ignore;
}
void GH_USB_PHY_set_Tx_Config_tx_dma_rclr(U8 data)
{
    GH_USB_PHY_TX_CONFIG_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_TX_CONFIG;
    d.bitc.tx_dma_rclr = data;
    *(volatile U16 *)REG_USB_PHY_TX_CONFIG = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Config_tx_dma_rclr] <-- 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_Tx_Config_tx_dma_rclr(void)
{
    GH_USB_PHY_TX_CONFIG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_CONFIG);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Config_tx_dma_rclr] --> 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,value);
    #endif
    return tmp_value.bitc.tx_dma_rclr;
}
void GH_USB_PHY_set_Tx_Config_tx_dma_rcvd(U8 data)
{
    GH_USB_PHY_TX_CONFIG_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_TX_CONFIG;
    d.bitc.tx_dma_rcvd = data;
    *(volatile U16 *)REG_USB_PHY_TX_CONFIG = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Config_tx_dma_rcvd] <-- 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_Tx_Config_tx_dma_rcvd(void)
{
    GH_USB_PHY_TX_CONFIG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_CONFIG);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Config_tx_dma_rcvd] --> 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,value);
    #endif
    return tmp_value.bitc.tx_dma_rcvd;
}
void GH_USB_PHY_set_Tx_Config_tx_dma_countL(U8 data)
{
    GH_USB_PHY_TX_CONFIG_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_TX_CONFIG;
    d.bitc.tx_dma_countl = data;
    *(volatile U16 *)REG_USB_PHY_TX_CONFIG = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Config_tx_dma_countL] <-- 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_Tx_Config_tx_dma_countL(void)
{
    GH_USB_PHY_TX_CONFIG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_CONFIG);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Config_tx_dma_countL] --> 0x%08x\n",
                        REG_USB_PHY_TX_CONFIG,value);
    #endif
    return tmp_value.bitc.tx_dma_countl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_Tx_Dma_Count (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_Tx_Dma_Count(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Dma_Count] <-- 0x%08x\n",
                        REG_USB_PHY_TX_DMA_COUNT,data,data);
    #endif
}
U16  GH_USB_PHY_get_Tx_Dma_Count(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Dma_Count] --> 0x%08x\n",
                        REG_USB_PHY_TX_DMA_COUNT,value);
    #endif
    return value;
}
void GH_USB_PHY_set_Tx_Dma_Count_tx_dma_countM(U8 data)
{
    GH_USB_PHY_TX_DMA_COUNT_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT;
    d.bitc.tx_dma_countm = data;
    *(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Dma_Count_tx_dma_countM] <-- 0x%08x\n",
                        REG_USB_PHY_TX_DMA_COUNT,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_Tx_Dma_Count_tx_dma_countM(void)
{
    GH_USB_PHY_TX_DMA_COUNT_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Dma_Count_tx_dma_countM] --> 0x%08x\n",
                        REG_USB_PHY_TX_DMA_COUNT,value);
    #endif
    return tmp_value.bitc.tx_dma_countm;
}
void GH_USB_PHY_set_Tx_Dma_Count_tx_dma_countH(U8 data)
{
    GH_USB_PHY_TX_DMA_COUNT_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT;
    d.bitc.tx_dma_counth = data;
    *(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_Tx_Dma_Count_tx_dma_countH] <-- 0x%08x\n",
                        REG_USB_PHY_TX_DMA_COUNT,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_Tx_Dma_Count_tx_dma_countH(void)
{
    GH_USB_PHY_TX_DMA_COUNT_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_TX_DMA_COUNT);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_Tx_Dma_Count_tx_dma_countH] --> 0x%08x\n",
                        REG_USB_PHY_TX_DMA_COUNT,value);
    #endif
    return tmp_value.bitc.tx_dma_counth;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_00 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_00(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_00(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_00_pdn_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.pdn_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_pdn_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_pdn_override(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_pdn_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.pdn_override;
}
void GH_USB_PHY_set_UTMI_REG_00_term_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.term_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_term_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_term_override(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_term_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.term_override;
}
void GH_USB_PHY_set_UTMI_REG_00_ref_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.ref_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_ref_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_ref_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_ref_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.ref_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_dp_puen(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.dp_puen = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_dp_puen] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_dp_puen(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_dp_puen] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.dp_puen;
}
void GH_USB_PHY_set_UTMI_REG_00_dm_puen(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.dm_puen = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_dm_puen] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_dm_puen(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_dm_puen] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.dm_puen;
}
void GH_USB_PHY_set_UTMI_REG_00_r_pumode(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.r_pumode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_r_pumode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_r_pumode(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_r_pumode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.r_pumode;
}
void GH_USB_PHY_set_UTMI_REG_00_r_dp_pden(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.r_dp_pden = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_r_dp_pden] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_r_dp_pden(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_r_dp_pden] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.r_dp_pden;
}
void GH_USB_PHY_set_UTMI_REG_00_r_dm_pden(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.r_dm_pden = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_r_dm_pden] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_r_dm_pden(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_r_dm_pden] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.r_dm_pden;
}
void GH_USB_PHY_set_UTMI_REG_00_hs_dm_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.hs_dm_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_hs_dm_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_hs_dm_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_hs_dm_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.hs_dm_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_pll_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.pll_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_pll_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_pll_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_pll_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.pll_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_hs_ted_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.hs_ted_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_hs_ted_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_hs_ted_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_hs_ted_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.hs_ted_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_hs_preamp_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.hs_preamp_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_hs_preamp_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_hs_preamp_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_hs_preamp_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.hs_preamp_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_f1_xcvf_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.f1_xcvf_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_f1_xcvf_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_f1_xcvf_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_f1_xcvf_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.f1_xcvf_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_vbusdet_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.vbusdet_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_vbusdet_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_vbusdet_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_vbusdet_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.vbusdet_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_iref_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.iref_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_iref_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_iref_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_iref_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.iref_pdn;
}
void GH_USB_PHY_set_UTMI_REG_00_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_00_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.pdn;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_01 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_01(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_01(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_01_sel_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.sel_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_sel_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_sel_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_sel_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.sel_override;
}
void GH_USB_PHY_set_UTMI_REG_01_fsls_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.fsls_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_fsls_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_fsls_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_fsls_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.fsls_sel;
}
void GH_USB_PHY_set_UTMI_REG_01_clk12_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.clk12_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_clk12_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_clk12_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_clk12_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.clk12_sel;
}
void GH_USB_PHY_set_UTMI_REG_01_nrzi_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.nrzi_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_nrzi_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_nrzi_en(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_nrzi_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.nrzi_en;
}
void GH_USB_PHY_set_UTMI_REG_01_bitstuff_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.bitstuff_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_bitstuff_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_bitstuff_en(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_bitstuff_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.bitstuff_en;
}
void GH_USB_PHY_set_UTMI_REG_01_fl_lowimode(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.fl_lowimode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_fl_lowimode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_fl_lowimode(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_fl_lowimode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.fl_lowimode;
}
void GH_USB_PHY_set_UTMI_REG_01_hs_tx_ten(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.hs_tx_ten = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_hs_tx_ten] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_hs_tx_ten(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_hs_tx_ten] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.hs_tx_ten;
}
void GH_USB_PHY_set_UTMI_REG_01_bond_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.bond_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_bond_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_bond_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_bond_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.bond_sel;
}
void GH_USB_PHY_set_UTMI_REG_01_bitstuff_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.bitstuff_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_bitstuff_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_bitstuff_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_bitstuff_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.bitstuff_override;
}
void GH_USB_PHY_set_UTMI_REG_01_nrzi_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.nrzi_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_nrzi_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_nrzi_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_nrzi_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.nrzi_override;
}
void GH_USB_PHY_set_UTMI_REG_01_fl_sel_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.fl_sel_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_fl_sel_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_fl_sel_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_fl_sel_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.fl_sel_override;
}
void GH_USB_PHY_set_UTMI_REG_01_eop40_det_delay_cnt(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.eop40_det_delay_cnt = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_eop40_det_delay_cnt] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_eop40_det_delay_cnt(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_eop40_det_delay_cnt] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.eop40_det_delay_cnt;
}
void GH_USB_PHY_set_UTMI_REG_01_linestate_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.linestate_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_linestate_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_linestate_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_linestate_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.linestate_sel;
}
void GH_USB_PHY_set_UTMI_REG_01_hs_rterm_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.hs_rterm_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_hs_rterm_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_01_hs_rterm_pdn(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_hs_rterm_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.hs_rterm_pdn;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_02 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_02(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_02(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_chip(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.hs_tx_en_chip = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_chip] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_chip(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_chip] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.hs_tx_en_chip;
}
void GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_sw(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.hs_tx_en_sw = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_sw] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_sw(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_sw] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.hs_tx_en_sw;
}
void GH_USB_PHY_set_UTMI_REG_02_dummy(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_dummy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_02_dummy(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_dummy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.dummy;
}
void GH_USB_PHY_set_UTMI_REG_02_tx_in_sel_multi_phase(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.tx_in_sel_multi_phase = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_tx_in_sel_multi_phase] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_02_tx_in_sel_multi_phase(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_tx_in_sel_multi_phase] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.tx_in_sel_multi_phase;
}
void GH_USB_PHY_set_UTMI_REG_02_tx_out_sel_multi_phase(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.tx_out_sel_multi_phase = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_tx_out_sel_multi_phase] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_02_tx_out_sel_multi_phase(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_tx_out_sel_multi_phase] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.tx_out_sel_multi_phase;
}
void GH_USB_PHY_set_UTMI_REG_02_utmi_tx_wait_cnt(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.utmi_tx_wait_cnt = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_utmi_tx_wait_cnt] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_02_utmi_tx_wait_cnt(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_utmi_tx_wait_cnt] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.utmi_tx_wait_cnt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_03 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_03(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_03(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_03_rx_swreset(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.rx_swreset = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_rx_swreset] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_rx_swreset(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_rx_swreset] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.rx_swreset;
}
void GH_USB_PHY_set_UTMI_REG_03_utmi_tx_sw_reset(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.utmi_tx_sw_reset = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_utmi_tx_sw_reset] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_utmi_tx_sw_reset(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_utmi_tx_sw_reset] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.utmi_tx_sw_reset;
}
void GH_USB_PHY_set_UTMI_REG_03_tx_force_hs_current_enable(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_force_hs_current_enable = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_force_hs_current_enable] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_tx_force_hs_current_enable(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_force_hs_current_enable] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_force_hs_current_enable;
}
void GH_USB_PHY_set_UTMI_REG_03_tx_fl_early_4(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_fl_early_4 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_fl_early_4] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_tx_fl_early_4(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_fl_early_4] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_fl_early_4;
}
void GH_USB_PHY_set_UTMI_REG_03_tx_fl_latency_delay_1(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_fl_latency_delay_1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_fl_latency_delay_1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_tx_fl_latency_delay_1(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_fl_latency_delay_1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_fl_latency_delay_1;
}
void GH_USB_PHY_set_UTMI_REG_03_hs_stage_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.hs_stage_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_hs_stage_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_hs_stage_select(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_hs_stage_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.hs_stage_select;
}
void GH_USB_PHY_set_UTMI_REG_03_otg_dual_role(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.otg_dual_role = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_otg_dual_role] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_otg_dual_role(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_otg_dual_role] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.otg_dual_role;
}
void GH_USB_PHY_set_UTMI_REG_03_tx_reset_fsm(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_reset_fsm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_reset_fsm] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_tx_reset_fsm(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_reset_fsm] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_reset_fsm;
}
void GH_USB_PHY_set_UTMI_REG_03_cdr_mode_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.cdr_mode_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_cdr_mode_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_cdr_mode_sel(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_cdr_mode_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.cdr_mode_sel;
}
void GH_USB_PHY_set_UTMI_REG_03_tx_reserved(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_reserved = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_reserved] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_tx_reserved(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_reserved] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_reserved;
}
void GH_USB_PHY_set_UTMI_REG_03_vbusdet_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.vbusdet_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_vbusdet_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_03_vbusdet_test(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_vbusdet_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.vbusdet_test;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_04 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_04(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_04(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_04_utmi_clk_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.utmi_clk_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_utmi_clk_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_utmi_clk_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_utmi_clk_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.utmi_clk_en;
}
void GH_USB_PHY_set_UTMI_REG_04_utmi_clk120_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.utmi_clk120_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_utmi_clk120_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_utmi_clk120_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_utmi_clk120_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.utmi_clk120_en;
}
void GH_USB_PHY_set_UTMI_REG_04_clktest_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clktest_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clktest_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_clktest_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clktest_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clktest_en;
}
void GH_USB_PHY_set_UTMI_REG_04_clk_extra_0_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_extra_0_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_extra_0_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_clk_extra_0_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_extra_0_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_extra_0_en;
}
void GH_USB_PHY_set_UTMI_REG_04_clk_extra_1_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_extra_1_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_extra_1_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_clk_extra_1_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_extra_1_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_extra_1_en;
}
void GH_USB_PHY_set_UTMI_REG_04_xtal12_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.xtal12_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_xtal12_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_xtal12_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_xtal12_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.xtal12_en;
}
void GH_USB_PHY_set_UTMI_REG_04_clk_ctl_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_ctl_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_ctl_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_clk_ctl_override(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_ctl_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_ctl_override;
}
void GH_USB_PHY_set_UTMI_REG_04_force_pll_on(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.force_pll_on = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_force_pll_on] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_force_pll_on(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_force_pll_on] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.force_pll_on;
}
void GH_USB_PHY_set_UTMI_REG_04_ck214_syn_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.ck214_syn_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_ck214_syn_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_ck214_syn_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_ck214_syn_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.ck214_syn_en;
}
void GH_USB_PHY_set_UTMI_REG_04_clk_274_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_274_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_274_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_clk_274_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_274_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_274_en;
}
void GH_USB_PHY_set_UTMI_REG_04_hs_rx_roboust_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.hs_rx_roboust_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_hs_rx_roboust_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_04_hs_rx_roboust_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_hs_rx_roboust_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.hs_rx_roboust_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_05 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_05(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_05(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_05_utmi_clk_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.utmi_clk_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_utmi_clk_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_05_utmi_clk_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_utmi_clk_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.utmi_clk_inv;
}
void GH_USB_PHY_set_UTMI_REG_05_utmi_clk120_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.utmi_clk120_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_utmi_clk120_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_05_utmi_clk120_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_utmi_clk120_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.utmi_clk120_inv;
}
void GH_USB_PHY_set_UTMI_REG_05_dummy1(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.dummy1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_dummy1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_05_dummy1(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_dummy1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.dummy1;
}
void GH_USB_PHY_set_UTMI_REG_05_clktest_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.clktest_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_clktest_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_05_clktest_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_clktest_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.clktest_inv;
}
void GH_USB_PHY_set_UTMI_REG_05_clk_extra_0_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.clk_extra_0_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_clk_extra_0_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_05_clk_extra_0_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_clk_extra_0_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.clk_extra_0_inv;
}
void GH_USB_PHY_set_UTMI_REG_05_clk_extra_1_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.clk_extra_1_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_clk_extra_1_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_05_clk_extra_1_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_clk_extra_1_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.clk_extra_1_inv;
}
void GH_USB_PHY_set_UTMI_REG_05_ck_inv_reserved(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.ck_inv_reserved = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_ck_inv_reserved] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_05_ck_inv_reserved(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_ck_inv_reserved] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.ck_inv_reserved;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_06 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_06(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_06(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_06_test_clock_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.test_clock_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_test_clock_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_06_test_clock_select(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_test_clock_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.test_clock_select;
}
void GH_USB_PHY_set_UTMI_REG_06_mac_clk_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.mac_clk_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_mac_clk_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_06_mac_clk_sel(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_mac_clk_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.mac_clk_sel;
}
void GH_USB_PHY_set_UTMI_REG_06_double_data_rate(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.double_data_rate = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_double_data_rate] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_06_double_data_rate(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_double_data_rate] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.double_data_rate;
}
void GH_USB_PHY_set_UTMI_REG_06_clk_extra0_div_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.clk_extra0_div_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_clk_extra0_div_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_06_clk_extra0_div_select(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_clk_extra0_div_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.clk_extra0_div_select;
}
void GH_USB_PHY_set_UTMI_REG_06_clk_extra1_div_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.clk_extra1_div_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_clk_extra1_div_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_06_clk_extra1_div_select(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_clk_extra1_div_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.clk_extra1_div_select;
}
void GH_USB_PHY_set_UTMI_REG_06_utmi_ck_en_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.utmi_ck_en_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_utmi_ck_en_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_06_utmi_ck_en_sel(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_utmi_ck_en_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.utmi_ck_en_sel;
}
void GH_USB_PHY_set_UTMI_REG_06_utmi_ckinv_en_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.utmi_ckinv_en_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_utmi_ckinv_en_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_06_utmi_ckinv_en_sel(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_utmi_ckinv_en_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.utmi_ckinv_en_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_STATUS (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_USB_PHY_get_UTMI_STATUS(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return value;
}
U8   GH_USB_PHY_get_UTMI_STATUS_elasticity_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_elasticity_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.elasticity_error;
}
U8   GH_USB_PHY_get_UTMI_STATUS_Sync_pattern_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_Sync_pattern_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.sync_pattern_error;
}
U8   GH_USB_PHY_get_UTMI_STATUS_EOP_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_EOP_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.eop_error;
}
U8   GH_USB_PHY_get_UTMI_STATUS_bit_stuffer_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_bit_stuffer_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.bit_stuffer_error;
}
U8   GH_USB_PHY_get_UTMI_STATUS_elasticity_underflow(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_elasticity_underflow] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.elasticity_underflow;
}
U8   GH_USB_PHY_get_UTMI_STATUS_overflow(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_overflow] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.overflow;
}
U8   GH_USB_PHY_get_UTMI_STATUS_clock_ready(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_clock_ready] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.clock_ready;
}
U8   GH_USB_PHY_get_UTMI_STATUS_interrupt(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_interrupt] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.interrupt;
}
U8   GH_USB_PHY_get_UTMI_STATUS_device(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_device] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.device;
}
U8   GH_USB_PHY_get_UTMI_STATUS_host(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_host] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.host;
}
U8   GH_USB_PHY_get_UTMI_STATUS_Disconnect(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_Disconnect] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.disconnect;
}
U8   GH_USB_PHY_get_UTMI_STATUS_TX_FSM(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_TX_FSM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.tx_fsm;
}
U8   GH_USB_PHY_get_UTMI_STATUS_RX_FSM(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_RX_FSM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.rx_fsm;
}
U8   GH_USB_PHY_get_UTMI_STATUS_low_speed(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_low_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.low_speed;
}
U8   GH_USB_PHY_get_UTMI_STATUS_full_speed(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_full_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.full_speed;
}
U8   GH_USB_PHY_get_UTMI_STATUS_Hign_speed(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_Hign_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.hign_speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_08 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_08(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_08(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_08_test_bus_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.test_bus_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_test_bus_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_test_bus_select(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_test_bus_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.test_bus_select;
}
void GH_USB_PHY_set_UTMI_REG_08_force_rx_nonbusy(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.force_rx_nonbusy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_force_rx_nonbusy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_force_rx_nonbusy(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_force_rx_nonbusy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.force_rx_nonbusy;
}
void GH_USB_PHY_set_UTMI_REG_08_force_tx_nonbusy(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.force_tx_nonbusy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_force_tx_nonbusy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_force_tx_nonbusy(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_force_tx_nonbusy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.force_tx_nonbusy;
}
void GH_USB_PHY_set_UTMI_REG_08_utmi_int_clr(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.utmi_int_clr = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_utmi_int_clr] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_utmi_int_clr(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_utmi_int_clr] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.utmi_int_clr;
}
void GH_USB_PHY_set_UTMI_REG_08_se0_set(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.se0_set = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_se0_set] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_se0_set(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_se0_set] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.se0_set;
}
void GH_USB_PHY_set_UTMI_REG_08_tx_data(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_tx_data(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_data;
}
void GH_USB_PHY_set_UTMI_REG_08_tx_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_tx_en(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_en;
}
void GH_USB_PHY_set_UTMI_REG_08_tx_se0(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_se0 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_se0] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_tx_se0(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_se0] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_se0;
}
void GH_USB_PHY_set_UTMI_REG_08_tx_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_tx_override(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_override;
}
void GH_USB_PHY_set_UTMI_REG_08_power_good_rst(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.power_good_rst = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_power_good_rst] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_power_good_rst(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_power_good_rst] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.power_good_rst;
}
void GH_USB_PHY_set_UTMI_REG_08_phy_mode_enable(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.phy_mode_enable = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_phy_mode_enable] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_phy_mode_enable(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_phy_mode_enable] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.phy_mode_enable;
}
void GH_USB_PHY_set_UTMI_REG_08_error_flag_clr(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.error_flag_clr = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_error_flag_clr] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_error_flag_clr(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_error_flag_clr] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.error_flag_clr;
}
void GH_USB_PHY_set_UTMI_REG_08_hd_tx_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.hd_tx_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_hd_tx_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_08_hd_tx_override(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_hd_tx_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.hd_tx_override;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_09 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_09(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_09(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_09_deglitch_prd(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.deglitch_prd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_deglitch_prd] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_09_deglitch_prd(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_deglitch_prd] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.deglitch_prd;
}
void GH_USB_PHY_set_UTMI_REG_09_vdd2low_rst_enz(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.vdd2low_rst_enz = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_vdd2low_rst_enz] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_09_vdd2low_rst_enz(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_vdd2low_rst_enz] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.vdd2low_rst_enz;
}
void GH_USB_PHY_set_UTMI_REG_09_deglitch_enz(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.deglitch_enz = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_deglitch_enz] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_09_deglitch_enz(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_deglitch_enz] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.deglitch_enz;
}
void GH_USB_PHY_set_UTMI_REG_09_usbsyn_rst(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.usbsyn_rst = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_usbsyn_rst] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_09_usbsyn_rst(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_usbsyn_rst] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.usbsyn_rst;
}
void GH_USB_PHY_set_UTMI_REG_09_reg_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.reg_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_reg_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_09_reg_test(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_reg_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.reg_test;
}
void GH_USB_PHY_set_UTMI_REG_09_ib_rterm_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.ib_rterm_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_ib_rterm_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_09_ib_rterm_test(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_ib_rterm_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.ib_rterm_test;
}
void GH_USB_PHY_set_UTMI_REG_09_test_p1(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.test_p1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_test_p1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_09_test_p1(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_test_p1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.test_p1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_0A (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_0A(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_0A(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_0A_vbusvalid(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.vbusvalid = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_vbusvalid] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_vbusvalid(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_vbusvalid] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.vbusvalid;
}
void GH_USB_PHY_set_UTMI_REG_0A_avalid(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.avalid = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_avalid] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_avalid(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_avalid] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.avalid;
}
void GH_USB_PHY_set_UTMI_REG_0A_sessend(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.sessend = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_sessend] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_sessend(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_sessend] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.sessend;
}
void GH_USB_PHY_set_UTMI_REG_0A_iddig(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.iddig = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_iddig] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_iddig(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_iddig] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.iddig;
}
void GH_USB_PHY_set_UTMI_REG_0A_opmode(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.opmode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_opmode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_opmode(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_opmode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.opmode;
}
void GH_USB_PHY_set_UTMI_REG_0A_xcvrsel(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.xcvrsel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_xcvrsel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_xcvrsel(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_xcvrsel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.xcvrsel;
}
void GH_USB_PHY_set_UTMI_REG_0A_termsel(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.termsel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_termsel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_termsel(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_termsel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.termsel;
}
void GH_USB_PHY_set_UTMI_REG_0A_macmode_ovd(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.macmode_ovd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_macmode_ovd] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_macmode_ovd(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_macmode_ovd] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.macmode_ovd;
}
void GH_USB_PHY_set_UTMI_REG_0A_suspendm(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.suspendm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_suspendm] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_suspendm(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_suspendm] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.suspendm;
}
void GH_USB_PHY_set_UTMI_REG_0A_usb_bond_ovd(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.usb_bond_ovd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_usb_bond_ovd] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_usb_bond_ovd(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_usb_bond_ovd] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.usb_bond_ovd;
}
void GH_USB_PHY_set_UTMI_REG_0A_usb_bond_set(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.usb_bond_set = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_usb_bond_set] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_usb_bond_set(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_usb_bond_set] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.usb_bond_set;
}
void GH_USB_PHY_set_UTMI_REG_0A_host_chirp_det(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.host_chirp_det = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_host_chirp_det] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_host_chirp_det(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_host_chirp_det] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.host_chirp_det;
}
void GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.hs_tx_ien_mask = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.hs_tx_ien_mask;
}
void GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask_method(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.hs_tx_ien_mask_method = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask_method] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask_method(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask_method] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.hs_tx_ien_mask_method;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_0B (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_0B(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0B] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_0B(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0B);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0B] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_0B_f(U16 data)
{
    GH_USB_PHY_UTMI_REG_0B_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B;
    d.bitc.f = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0B_f] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,d.all,d.all);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_0B_f(void)
{
    GH_USB_PHY_UTMI_REG_0B_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0B);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0B_f] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,value);
    #endif
    return tmp_value.bitc.f;
}
void GH_USB_PHY_set_UTMI_REG_0B_N(U8 data)
{
    GH_USB_PHY_UTMI_REG_0B_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B;
    d.bitc.n = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0B_N] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG_0B_N(void)
{
    GH_USB_PHY_UTMI_REG_0B_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0B);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0B_N] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,value);
    #endif
    return tmp_value.bitc.n;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_0C (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG_0C(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0C = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0C] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_0C(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0C);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0C] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG_0C_f(U16 data)
{
    GH_USB_PHY_UTMI_REG_0C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0C;
    d.bitc.f = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0C_f] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,d.all,d.all);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG_0C_f(void)
{
    GH_USB_PHY_UTMI_REG_0C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0C_f] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,value);
    #endif
    return tmp_value.bitc.f;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG10 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG10(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG10(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG10_input_clock(U8 data)
{
    GH_USB_PHY_UTMI_REG10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG10;
    d.bitc.input_clock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10_input_clock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG10_input_clock(void)
{
    GH_USB_PHY_UTMI_REG10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10_input_clock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return tmp_value.bitc.input_clock;
}
void GH_USB_PHY_set_UTMI_REG10_divider_selection(U8 data)
{
    GH_USB_PHY_UTMI_REG10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG10;
    d.bitc.divider_selection = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10_divider_selection] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG10_divider_selection(void)
{
    GH_USB_PHY_UTMI_REG10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10_divider_selection] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return tmp_value.bitc.divider_selection;
}
void GH_USB_PHY_set_UTMI_REG10_divider_control(U8 data)
{
    GH_USB_PHY_UTMI_REG10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG10;
    d.bitc.divider_control = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10_divider_control] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG10_divider_control(void)
{
    GH_USB_PHY_UTMI_REG10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10_divider_control] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return tmp_value.bitc.divider_control;
}
void GH_USB_PHY_set_UTMI_REG10_clock_outputs_source(U8 data)
{
    GH_USB_PHY_UTMI_REG10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG10;
    d.bitc.clock_outputs_source = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10_clock_outputs_source] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG10_clock_outputs_source(void)
{
    GH_USB_PHY_UTMI_REG10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10_clock_outputs_source] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return tmp_value.bitc.clock_outputs_source;
}
void GH_USB_PHY_set_UTMI_REG10_clock_outputs_ratio(U8 data)
{
    GH_USB_PHY_UTMI_REG10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG10;
    d.bitc.clock_outputs_ratio = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10_clock_outputs_ratio] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG10_clock_outputs_ratio(void)
{
    GH_USB_PHY_UTMI_REG10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10_clock_outputs_ratio] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return tmp_value.bitc.clock_outputs_ratio;
}
void GH_USB_PHY_set_UTMI_REG10_digital_output(U8 data)
{
    GH_USB_PHY_UTMI_REG10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG10;
    d.bitc.digital_output = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10_digital_output] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG10_digital_output(void)
{
    GH_USB_PHY_UTMI_REG10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10_digital_output] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return tmp_value.bitc.digital_output;
}
void GH_USB_PHY_set_UTMI_REG10_transmitter(U8 data)
{
    GH_USB_PHY_UTMI_REG10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG10;
    d.bitc.transmitter = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG10_transmitter] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG10_transmitter(void)
{
    GH_USB_PHY_UTMI_REG10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG10_transmitter] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG10,value);
    #endif
    return tmp_value.bitc.transmitter;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG11 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG11(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG11(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG11_ENDISC(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.endisc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_ENDISC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_ENDISC(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_ENDISC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.endisc;
}
void GH_USB_PHY_set_UTMI_REG11_EXTDISC(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.extdisc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_EXTDISC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_EXTDISC(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_EXTDISC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.extdisc;
}
void GH_USB_PHY_set_UTMI_REG11_ENLOCKZ(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.enlockz = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_ENLOCKZ] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_ENLOCKZ(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_ENLOCKZ] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.enlockz;
}
void GH_USB_PHY_set_UTMI_REG11_ENAUTO(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.enauto = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_ENAUTO] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_ENAUTO(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_ENAUTO] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.enauto;
}
void GH_USB_PHY_set_UTMI_REG11_ENDCC(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.endcc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_ENDCC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_ENDCC(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_ENDCC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.endcc;
}
void GH_USB_PHY_set_UTMI_REG11_TVCO(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.tvco = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_TVCO] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_TVCO(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_TVCO] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.tvco;
}
void GH_USB_PHY_set_UTMI_REG11_output_source(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.output_source = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_output_source] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_output_source(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_output_source] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.output_source;
}
void GH_USB_PHY_set_UTMI_REG11_ENINV(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.eninv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_ENINV] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_ENINV(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_ENINV] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.eninv;
}
void GH_USB_PHY_set_UTMI_REG11_ENINVENTMUX(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.eninventmux = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_ENINVENTMUX] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_ENINVENTMUX(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_ENINVENTMUX] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.eninventmux;
}
void GH_USB_PHY_set_UTMI_REG11_input_clock(U8 data)
{
    GH_USB_PHY_UTMI_REG11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG11;
    d.bitc.input_clock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG11_input_clock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG11_input_clock(void)
{
    GH_USB_PHY_UTMI_REG11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG11_input_clock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG11,value);
    #endif
    return tmp_value.bitc.input_clock;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG12 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG12(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG12 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG12] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG12(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG12);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG12] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG12_ICTL33(U8 data)
{
    GH_USB_PHY_UTMI_REG12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG12;
    d.bitc.ictl33 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG12_ICTL33] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG12_ICTL33(void)
{
    GH_USB_PHY_UTMI_REG12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG12_ICTL33] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,value);
    #endif
    return tmp_value.bitc.ictl33;
}
void GH_USB_PHY_set_UTMI_REG12_DIS_HVFLAG_DISC(U8 data)
{
    GH_USB_PHY_UTMI_REG12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG12;
    d.bitc.dis_hvflag_disc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG12_DIS_HVFLAG_DISC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG12_DIS_HVFLAG_DISC(void)
{
    GH_USB_PHY_UTMI_REG12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG12_DIS_HVFLAG_DISC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,value);
    #endif
    return tmp_value.bitc.dis_hvflag_disc;
}
void GH_USB_PHY_set_UTMI_REG12_ENSYN33(U8 data)
{
    GH_USB_PHY_UTMI_REG12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG12;
    d.bitc.ensyn33 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG12_ENSYN33] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG12_ENSYN33(void)
{
    GH_USB_PHY_UTMI_REG12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG12_ENSYN33] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,value);
    #endif
    return tmp_value.bitc.ensyn33;
}
void GH_USB_PHY_set_UTMI_REG12_Regulated(U8 data)
{
    GH_USB_PHY_UTMI_REG12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG12;
    d.bitc.regulated = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG12_Regulated] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG12_Regulated(void)
{
    GH_USB_PHY_UTMI_REG12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG12_Regulated] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,value);
    #endif
    return tmp_value.bitc.regulated;
}
void GH_USB_PHY_set_UTMI_REG12_Regulator(U8 data)
{
    GH_USB_PHY_UTMI_REG12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG12;
    d.bitc.regulator = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG12_Regulator] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG12_Regulator(void)
{
    GH_USB_PHY_UTMI_REG12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG12_Regulator] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG12,value);
    #endif
    return tmp_value.bitc.regulator;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG13 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG13(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG13 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG13] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG13(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG13);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG13] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG13_De_glitch_time(U8 data)
{
    GH_USB_PHY_UTMI_REG13_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG13;
    d.bitc.de_glitch_time = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG13 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG13_De_glitch_time] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG13_De_glitch_time(void)
{
    GH_USB_PHY_UTMI_REG13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG13);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG13_De_glitch_time] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,value);
    #endif
    return tmp_value.bitc.de_glitch_time;
}
void GH_USB_PHY_set_UTMI_REG13_Squelch_detector(U8 data)
{
    GH_USB_PHY_UTMI_REG13_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG13;
    d.bitc.squelch_detector = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG13 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG13_Squelch_detector] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG13_Squelch_detector(void)
{
    GH_USB_PHY_UTMI_REG13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG13);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG13_Squelch_detector] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,value);
    #endif
    return tmp_value.bitc.squelch_detector;
}
void GH_USB_PHY_set_UTMI_REG13_receiver_bias(U8 data)
{
    GH_USB_PHY_UTMI_REG13_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG13;
    d.bitc.receiver_bias = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG13 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG13_receiver_bias] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG13_receiver_bias(void)
{
    GH_USB_PHY_UTMI_REG13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG13);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG13_receiver_bias] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG13,value);
    #endif
    return tmp_value.bitc.receiver_bias;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG14 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG14(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG14(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG14_slew_rate(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.slew_rate = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_slew_rate] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_slew_rate(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_slew_rate] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.slew_rate;
}
void GH_USB_PHY_set_UTMI_REG14_Hign_speed(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.hign_speed = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_Hign_speed] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_Hign_speed(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_Hign_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.hign_speed;
}
void GH_USB_PHY_set_UTMI_REG14_Full_speed0(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.full_speed0 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_Full_speed0] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_Full_speed0(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_Full_speed0] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.full_speed0;
}
void GH_USB_PHY_set_UTMI_REG14_Full_speed1(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.full_speed1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_Full_speed1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_Full_speed1(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_Full_speed1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.full_speed1;
}
void GH_USB_PHY_set_UTMI_REG14_slew(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.slew = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_slew] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_slew(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_slew] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.slew;
}
void GH_USB_PHY_set_UTMI_REG14_Disable(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.disable = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_Disable] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_Disable(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_Disable] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.disable;
}
void GH_USB_PHY_set_UTMI_REG14_test_DM(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.test_dm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_test_DM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_test_DM(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_test_DM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.test_dm;
}
void GH_USB_PHY_set_UTMI_REG14_test_DP(U8 data)
{
    GH_USB_PHY_UTMI_REG14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG14;
    d.bitc.test_dp = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG14_test_DP] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG14_test_DP(void)
{
    GH_USB_PHY_UTMI_REG14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG14_test_DP] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG14,value);
    #endif
    return tmp_value.bitc.test_dp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG15 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG15(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG15(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG15_VSPOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.vspout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_VSPOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_VSPOUT(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_VSPOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.vspout;
}
void GH_USB_PHY_set_UTMI_REG15_VSMOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.vsmout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_VSMOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_VSMOUT(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_VSMOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.vsmout;
}
void GH_USB_PHY_set_UTMI_REG15_VCPOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.vcpout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_VCPOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_VCPOUT(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_VCPOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.vcpout;
}
void GH_USB_PHY_set_UTMI_REG15_VCMOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.vcmout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_VCMOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_VCMOUT(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_VCMOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.vcmout;
}
void GH_USB_PHY_set_UTMI_REG15_PGD(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.pgd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_PGD] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_PGD(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_PGD] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.pgd;
}
void GH_USB_PHY_set_UTMI_REG15_Power_Good_33V(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.power_good_33v = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_Power_Good_33V] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_Power_Good_33V(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_Power_Good_33V] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.power_good_33v;
}
void GH_USB_PHY_set_UTMI_REG15_Power_Good(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.power_good = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_Power_Good] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_Power_Good(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_Power_Good] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.power_good;
}
void GH_USB_PHY_set_UTMI_REG15_VBG(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.vbg = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_VBG] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_VBG(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_VBG] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.vbg;
}
void GH_USB_PHY_set_UTMI_REG15_VBGR(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.vbgr = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_VBGR] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_VBGR(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_VBGR] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.vbgr;
}
void GH_USB_PHY_set_UTMI_REG15_Power_Good_POR(U8 data)
{
    GH_USB_PHY_UTMI_REG15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG15;
    d.bitc.power_good_por = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG15_Power_Good_POR] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG15_Power_Good_POR(void)
{
    GH_USB_PHY_UTMI_REG15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG15_Power_Good_POR] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG15,value);
    #endif
    return tmp_value.bitc.power_good_por;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG16 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG16(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG16(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG16_TX_text_clock(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.tx_text_clock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_TX_text_clock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_TX_text_clock(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_TX_text_clock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.tx_text_clock;
}
void GH_USB_PHY_set_UTMI_REG16_TX_output_adjust(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.tx_output_adjust = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_TX_output_adjust] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_TX_output_adjust(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_TX_output_adjust] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.tx_output_adjust;
}
void GH_USB_PHY_set_UTMI_REG16_TX_pre_emphasis_adjust(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.tx_pre_emphasis_adjust = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_TX_pre_emphasis_adjust] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_TX_pre_emphasis_adjust(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_TX_pre_emphasis_adjust] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.tx_pre_emphasis_adjust;
}
void GH_USB_PHY_set_UTMI_REG16_TX_pre_emphasis_bias(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.tx_pre_emphasis_bias = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_TX_pre_emphasis_bias] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_TX_pre_emphasis_bias(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_TX_pre_emphasis_bias] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.tx_pre_emphasis_bias;
}
void GH_USB_PHY_set_UTMI_REG16_TX_current_bias(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.tx_current_bias = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_TX_current_bias] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_TX_current_bias(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_TX_current_bias] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.tx_current_bias;
}
void GH_USB_PHY_set_UTMI_REG16_HS_RTERM(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.hs_rterm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_HS_RTERM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_HS_RTERM(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_HS_RTERM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.hs_rterm;
}
void GH_USB_PHY_set_UTMI_REG16_HS_TX(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.hs_tx = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_HS_TX] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_HS_TX(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_HS_TX] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.hs_tx;
}
void GH_USB_PHY_set_UTMI_REG16_VBUSDET_NC(U8 data)
{
    GH_USB_PHY_UTMI_REG16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG16;
    d.bitc.vbusdet_nc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG16_VBUSDET_NC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG16_VBUSDET_NC(void)
{
    GH_USB_PHY_UTMI_REG16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG16_VBUSDET_NC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG16,value);
    #endif
    return tmp_value.bitc.vbusdet_nc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG17 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG17(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG17(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG17_HS_RX(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.hs_rx = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_HS_RX] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_HS_RX(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_HS_RX] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.hs_rx;
}
void GH_USB_PHY_set_UTMI_REG17_RTERM(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.rterm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_RTERM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_RTERM(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_RTERM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.rterm;
}
void GH_USB_PHY_set_UTMI_REG17_HS_RTERM(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.hs_rterm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_HS_RTERM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_HS_RTERM(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_HS_RTERM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.hs_rterm;
}
void GH_USB_PHY_set_UTMI_REG17_HS_TX_ITEST(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.hs_tx_itest = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_HS_TX_ITEST] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_HS_TX_ITEST(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_HS_TX_ITEST] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.hs_tx_itest;
}
void GH_USB_PHY_set_UTMI_REG17_Mute(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.mute = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_Mute] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_Mute(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_Mute] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.mute;
}
void GH_USB_PHY_set_UTMI_REG17_pre_emphasis_en(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.pre_emphasis_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_pre_emphasis_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_pre_emphasis_en(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_pre_emphasis_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.pre_emphasis_en;
}
void GH_USB_PHY_set_UTMI_REG17_transition_edge(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.transition_edge = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_transition_edge] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_transition_edge(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_transition_edge] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.transition_edge;
}
void GH_USB_PHY_set_UTMI_REG17_enable_edge(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.enable_edge = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_enable_edge] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_enable_edge(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_enable_edge] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.enable_edge;
}
void GH_USB_PHY_set_UTMI_REG17_clock_output(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.clock_output = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_clock_output] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_clock_output(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_clock_output] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.clock_output;
}
void GH_USB_PHY_set_UTMI_REG17_source(U8 data)
{
    GH_USB_PHY_UTMI_REG17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG17;
    d.bitc.source = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG17_source] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG17_source(void)
{
    GH_USB_PHY_UTMI_REG17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG17_source] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG17,value);
    #endif
    return tmp_value.bitc.source;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG18 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG18(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG18(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG18_lock(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.lock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_lock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_lock(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_lock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.lock;
}
void GH_USB_PHY_set_UTMI_REG18_flag1(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.flag1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_flag1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_flag1(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_flag1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.flag1;
}
void GH_USB_PHY_set_UTMI_REG18_flag2(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.flag2 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_flag2] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_flag2(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_flag2] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.flag2;
}
void GH_USB_PHY_set_UTMI_REG18_test(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_test(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.test;
}
void GH_USB_PHY_set_UTMI_REG18_Power_good(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.power_good = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_Power_good] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_Power_good(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_Power_good] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.power_good;
}
void GH_USB_PHY_set_UTMI_REG18_Vbus(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.vbus = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_Vbus] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_Vbus(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_Vbus] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.vbus;
}
void GH_USB_PHY_set_UTMI_REG18_OTG(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.otg = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_OTG] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_OTG(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_OTG] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.otg;
}
void GH_USB_PHY_set_UTMI_REG18_CID(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.cid = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_CID] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_CID(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_CID] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.cid;
}
void GH_USB_PHY_set_UTMI_REG18_AVALID_ATOP(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.avalid_atop = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_AVALID_ATOP] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_AVALID_ATOP(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_AVALID_ATOP] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.avalid_atop;
}
void GH_USB_PHY_set_UTMI_REG18_HS_DISCONNECT(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.hs_disconnect = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_HS_DISCONNECT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_HS_DISCONNECT(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_HS_DISCONNECT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.hs_disconnect;
}
void GH_USB_PHY_set_UTMI_REG18_HS_RX_DATA(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.hs_rx_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_HS_RX_DATA] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_HS_RX_DATA(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_HS_RX_DATA] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.hs_rx_data;
}
void GH_USB_PHY_set_UTMI_REG18_HS_RX_CHIRP(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.hs_rx_chirp = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_HS_RX_CHIRP] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_HS_RX_CHIRP(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_HS_RX_CHIRP] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.hs_rx_chirp;
}
void GH_USB_PHY_set_UTMI_REG18_FL_LINESTATE0(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.fl_linestate0 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_FL_LINESTATE0] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_FL_LINESTATE0(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_FL_LINESTATE0] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.fl_linestate0;
}
void GH_USB_PHY_set_UTMI_REG18_FL_LINESTATE1(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.fl_linestate1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_FL_LINESTATE1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_FL_LINESTATE1(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_FL_LINESTATE1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.fl_linestate1;
}
void GH_USB_PHY_set_UTMI_REG18_failed(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.failed = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_failed] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_failed(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_failed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.failed;
}
void GH_USB_PHY_set_UTMI_REG18_finish(U8 data)
{
    GH_USB_PHY_UTMI_REG18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG18;
    d.bitc.finish = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG18_finish] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG18_finish(void)
{
    GH_USB_PHY_UTMI_REG18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG18_finish] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG18,value);
    #endif
    return tmp_value.bitc.finish;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG19 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG19(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG19 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG19] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG19(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG19);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG19] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG19_pg_tx_length(U8 data)
{
    GH_USB_PHY_UTMI_REG19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG19;
    d.bitc.pg_tx_length = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG19_pg_tx_length] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG19_pg_tx_length(void)
{
    GH_USB_PHY_UTMI_REG19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG19_pg_tx_length] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,value);
    #endif
    return tmp_value.bitc.pg_tx_length;
}
void GH_USB_PHY_set_UTMI_REG19_pg_tx_go(U8 data)
{
    GH_USB_PHY_UTMI_REG19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG19;
    d.bitc.pg_tx_go = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG19_pg_tx_go] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG19_pg_tx_go(void)
{
    GH_USB_PHY_UTMI_REG19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG19_pg_tx_go] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,value);
    #endif
    return tmp_value.bitc.pg_tx_go;
}
void GH_USB_PHY_set_UTMI_REG19_pg_tx_mode(U8 data)
{
    GH_USB_PHY_UTMI_REG19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG19;
    d.bitc.pg_tx_mode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG19_pg_tx_mode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG19_pg_tx_mode(void)
{
    GH_USB_PHY_UTMI_REG19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG19_pg_tx_mode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,value);
    #endif
    return tmp_value.bitc.pg_tx_mode;
}
void GH_USB_PHY_set_UTMI_REG19_pg_tx_fixed_data(U8 data)
{
    GH_USB_PHY_UTMI_REG19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG19;
    d.bitc.pg_tx_fixed_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG19_pg_tx_fixed_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG19_pg_tx_fixed_data(void)
{
    GH_USB_PHY_UTMI_REG19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG19_pg_tx_fixed_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,value);
    #endif
    return tmp_value.bitc.pg_tx_fixed_data;
}
void GH_USB_PHY_set_UTMI_REG19_continuous_mode(U8 data)
{
    GH_USB_PHY_UTMI_REG19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG19;
    d.bitc.continuous_mode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG19_continuous_mode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG19_continuous_mode(void)
{
    GH_USB_PHY_UTMI_REG19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG19_continuous_mode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,value);
    #endif
    return tmp_value.bitc.continuous_mode;
}
void GH_USB_PHY_set_UTMI_REG19_receiving_mode(U8 data)
{
    GH_USB_PHY_UTMI_REG19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG19;
    d.bitc.receiving_mode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG19_receiving_mode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG19_receiving_mode(void)
{
    GH_USB_PHY_UTMI_REG19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG19_receiving_mode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG19,value);
    #endif
    return tmp_value.bitc.receiving_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG1A (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG1A(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1A = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1A] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1A,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1A(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1A);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1A] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1A,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG1A_pg_tx_data(U16 data)
{
    GH_USB_PHY_UTMI_REG1A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1A;
    d.bitc.pg_tx_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1A_pg_tx_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1A,d.all,d.all);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1A_pg_tx_data(void)
{
    GH_USB_PHY_UTMI_REG1A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1A_pg_tx_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1A,value);
    #endif
    return tmp_value.bitc.pg_tx_data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG1B (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG1B(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1B = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1B] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1B,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1B(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1B);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1B] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1B,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG1B_pg_tx_inc(U16 data)
{
    GH_USB_PHY_UTMI_REG1B_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1B;
    d.bitc.pg_tx_inc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1B = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1B_pg_tx_inc] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1B,d.all,d.all);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1B_pg_tx_inc(void)
{
    GH_USB_PHY_UTMI_REG1B_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1B);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1B_pg_tx_inc] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1B,value);
    #endif
    return tmp_value.bitc.pg_tx_inc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG1C (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG1C(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1C(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG1C_en_ck192(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.en_ck192 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_en_ck192] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_en_ck192(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_en_ck192] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.en_ck192;
}
void GH_USB_PHY_set_UTMI_REG1C_vigen_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.vigen_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_vigen_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_vigen_pdn(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_vigen_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.vigen_pdn;
}
void GH_USB_PHY_set_UTMI_REG1C_selport(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.selport = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_selport] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_selport(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_selport] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.selport;
}
void GH_USB_PHY_set_UTMI_REG1C_dp_status(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.dp_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_dp_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_dp_status(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_dp_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.dp_status;
}
void GH_USB_PHY_set_UTMI_REG1C_dm_status(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.dm_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_dm_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_dm_status(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_dm_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.dm_status;
}
void GH_USB_PHY_set_UTMI_REG1C_dp1_status(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.dp1_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_dp1_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_dp1_status(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_dp1_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.dp1_status;
}
void GH_USB_PHY_set_UTMI_REG1C_dm1_status(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.dm1_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_dm1_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_dm1_status(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_dm1_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.dm1_status;
}
void GH_USB_PHY_set_UTMI_REG1C_asrst_on(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.asrst_on = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_asrst_on] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_asrst_on(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_asrst_on] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.asrst_on;
}
void GH_USB_PHY_set_UTMI_REG1C_VBUS(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.vbus = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_VBUS] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_VBUS(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_VBUS] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.vbus;
}
void GH_USB_PHY_set_UTMI_REG1C_dummy(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_dummy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_dummy(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_dummy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.dummy;
}
void GH_USB_PHY_set_UTMI_REG1C_reserved(U8 data)
{
    GH_USB_PHY_UTMI_REG1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1C;
    d.bitc.reserved = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1C_reserved] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1C_reserved(void)
{
    GH_USB_PHY_UTMI_REG1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1C_reserved] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1C,value);
    #endif
    return tmp_value.bitc.reserved;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG1D (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG1D(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1D = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1D] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1D,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1D(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1D);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1D] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1D,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG1D_test_serdes(U8 data)
{
    GH_USB_PHY_UTMI_REG1D_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1D;
    d.bitc.test_serdes = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1D = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1D_test_serdes] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1D,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1D_test_serdes(void)
{
    GH_USB_PHY_UTMI_REG1D_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1D);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1D_test_serdes] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1D,value);
    #endif
    return tmp_value.bitc.test_serdes;
}
void GH_USB_PHY_set_UTMI_REG1D_reg_test(U8 data)
{
    GH_USB_PHY_UTMI_REG1D_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1D;
    d.bitc.reg_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1D = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1D_reg_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1D,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1D_reg_test(void)
{
    GH_USB_PHY_UTMI_REG1D_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1D);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1D_reg_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1D,value);
    #endif
    return tmp_value.bitc.reg_test;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG1E (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_USB_PHY_set_UTMI_REG1E(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1E = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1E] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,data,data);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1E(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1E);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1E] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,value);
    #endif
    return value;
}
void GH_USB_PHY_set_UTMI_REG1E_ca_start(U8 data)
{
    GH_USB_PHY_UTMI_REG1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1E;
    d.bitc.ca_start = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1E_ca_start] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1E_ca_start(void)
{
    GH_USB_PHY_UTMI_REG1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1E_ca_start] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,value);
    #endif
    return tmp_value.bitc.ca_start;
}
void GH_USB_PHY_set_UTMI_REG1E_ca_end(U8 data)
{
    GH_USB_PHY_UTMI_REG1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1E;
    d.bitc.ca_end = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1E_ca_end] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1E_ca_end(void)
{
    GH_USB_PHY_UTMI_REG1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1E_ca_end] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,value);
    #endif
    return tmp_value.bitc.ca_end;
}
void GH_USB_PHY_set_UTMI_REG1E_power_good_sts(U8 data)
{
    GH_USB_PHY_UTMI_REG1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1E;
    d.bitc.power_good_sts = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1E_power_good_sts] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,d.all,d.all);
    #endif
}
U8   GH_USB_PHY_get_UTMI_REG1E_power_good_sts(void)
{
    GH_USB_PHY_UTMI_REG1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1E_power_good_sts] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,value);
    #endif
    return tmp_value.bitc.power_good_sts;
}
void GH_USB_PHY_set_UTMI_REG1E_ca_data(U16 data)
{
    GH_USB_PHY_UTMI_REG1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG1E;
    d.bitc.ca_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG1E_ca_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,d.all,d.all);
    #endif
}
U16  GH_USB_PHY_get_UTMI_REG1E_ca_data(void)
{
    GH_USB_PHY_UTMI_REG1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG1E_ca_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG1E,value);
    #endif
    return tmp_value.bitc.ca_data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_USB_PHY_init(void)
{
    GH_USB_PHY_set_Tx_Config((U16)0x00000000);
    GH_USB_PHY_set_Tx_Dma_Count((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG_00((U16)0x0000ff05);
    GH_USB_PHY_set_UTMI_REG_01((U16)0x00009080);
    GH_USB_PHY_set_UTMI_REG_02((U16)0x00003000);
    GH_USB_PHY_set_UTMI_REG_03((U16)0x00003020);
    GH_USB_PHY_set_UTMI_REG_04((U16)0x00000483);
    GH_USB_PHY_set_UTMI_REG_05((U16)0x00008044);
    GH_USB_PHY_set_UTMI_REG_06((U16)0x000000c0);
    GH_USB_PHY_set_UTMI_REG_08((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG_09((U16)0x000000ff);
    GH_USB_PHY_set_UTMI_REG_0A((U16)0x0000000b);
    GH_USB_PHY_set_UTMI_REG_0B((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG_0C((U16)0x000023cc);
    GH_USB_PHY_set_UTMI_REG10((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG11((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG12((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG13((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG14((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG15((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG16((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG17((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG18((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG19((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG1A((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG1B((U16)0x00000001);
    GH_USB_PHY_set_UTMI_REG1C((U16)0x00002801);
    GH_USB_PHY_set_UTMI_REG1D((U16)0x00000000);
    GH_USB_PHY_set_UTMI_REG1E((U16)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

