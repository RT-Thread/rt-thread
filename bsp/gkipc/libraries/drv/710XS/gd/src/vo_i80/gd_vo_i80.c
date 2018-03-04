/******************************************************************************
**
** \file      gd_i80.c
**
** \brief     I80.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics Chengdu Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note     
**
******************************************************************************/

#include "gd_gpio.h"
#include "gd_vo_i80.h"    
#include "gh_vo_i80.h"    
#include "gd_timer.h"

//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <gm_lib/gm_debug.h>
#endif

#define REG_WR(reg,value)                                 (*((volatile U32 *)(reg))=(value))
#define REG_RD(reg,ret)                                   ((ret)=*((volatile U32 *)(reg)))


static GD_VO_I80_STATE_MACHINE_S i80_state_machine_dat = {0};
///*---------------------------------------------------------------------------*/
///* local data                                                                */
///*---------------------------------------------------------------------------*/
static U8                       I80InitDone = 0;  //is or not already initialized

GERR GD_VO_I80_CfgInvalid(void)
{
    GH_VO_I80_set_Ctrl_cfg_end(0);//cfg_end=0
    
    return GD_OK;
}

GERR GD_VO_I80_CfgValid(void)
{
    GH_VO_I80_set_Ctrl_cfg_end(1);//cfg_end=1
    
    return GD_OK;
}

GERR GD_VO_I80_CmdParaInvalid(void)
{
    GH_VO_I80_set_Cmd_Sram_State_sram_state(0);//sram_state=0
    
    return GD_OK;
}


GERR GD_VO_I80_CmdParaValid(void)
{
    GH_VO_I80_set_Cmd_Sram_State_sram_state(1);//sram_state=1
    
    return GD_OK;
}

GERR GD_VO_I80_OnOff(GD_HANDLE *pHandle,GD_VO_I80_ONOFF_E onoff)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }  
    if(onoff == GD_VO_I80_OFF)
    {
        GH_VO_I80_set_Ctrl_module_en(0);
    }
    else
    {
        GH_VO_I80_set_Ctrl_module_en(1);
    }
    
    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }     
    return GD_OK;
}

GERR GD_VO_I80_SetTransWidth(GD_HANDLE* pHandle,GD_VO_I80_DATA_WIDTH_E data_width)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    
     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }

    switch(data_width)
    {
    case GD_VO_I80_8BIT:
        GH_VO_I80_set_Data_Format_data_width(0);
        device->datawidth = GD_VO_I80_8BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 8bits mode\n");
#endif
        break;
    case GD_VO_I80_9BIT:
        GH_VO_I80_set_Data_Format_data_width(1);
        device->datawidth = GD_VO_I80_9BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 9bits mode\n");
#endif
        break;
    case GD_VO_I80_16BIT:
        GH_VO_I80_set_Data_Format_data_width(2);
        device->datawidth = GD_VO_I80_16BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 16bits mode\n");
#endif
        break;
    case GD_VO_I80_18BIT:
        GH_VO_I80_set_Data_Format_data_width(3);
        device->datawidth = GD_VO_I80_18BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 18bits mode\n");
#endif
        break;
    case GD_VO_I80_24BIT:
        GH_VO_I80_set_Data_Format_data_width(4);
        device->datawidth = GD_VO_I80_24BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 24bits mode\n");
#endif
        break;
    }
    
     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }          
    return GD_OK;
}

GERR GD_VO_I80_SetPixelBits(GD_HANDLE* pHandle,GD_VO_I80_COLOR_FORMAT_E color_format)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    
     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }
        
    switch(color_format)
    {
    case GD_VO_I80_PIXEL_16BIT:
        GH_VO_I80_set_Data_Format_color_format(0);
        device->colorformat = GD_VO_I80_PIXEL_16BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 16bits/pixel mode\n");
#endif
        break;
    case GD_VO_I80_PIXEL_18BIT:
        GH_VO_I80_set_Data_Format_color_format(1);
        device->colorformat = GD_VO_I80_PIXEL_18BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 18bits/pixel mode\n");
#endif
        break;        
    case GD_VO_I80_PIXEL_24BIT:
        GH_VO_I80_set_Data_Format_color_format(2);
        device->colorformat = GD_VO_I80_PIXEL_24BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 24bits/pixel mode\n");
#endif
        break;
    case GD_VO_I80_PIXEL_12BIT:
        GH_VO_I80_set_Data_Format_color_format(3);
        device->colorformat = GD_VO_I80_PIXEL_12BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 work in 12bits/pixel mode\n");
#endif
        break; 
    }        

     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }          
    return GD_OK;
}

GERR GD_VO_I80_SetMultiTransSeq(GD_HANDLE* pHandle,GD_VO_I80_TRANS_FORMAT_E datatransformat)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
 
     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }
       
    switch(datatransformat)
    {
        case GD_VO_I80_18BIT_TWICE_1PIXEL:
            GH_VO_I80_set_Data_Format_data_transfer_format(0);
            device->datatransformat = GD_VO_I80_18BIT_TWICE_1PIXEL;
#ifdef DEBUG_PRINT
               GM_Printf("Set i80 work in 1PIXEL/TWICE mode\n");
#endif            
            break;
        case GD_VO_I80_18BIT_TRICE_2PIXEL:
            GH_VO_I80_set_Data_Format_data_transfer_format(1);
            device->datatransformat = GD_VO_I80_18BIT_TRICE_2PIXEL;
#ifdef DEBUG_PRINT
               GM_Printf("Set i80 work in 2PIXEL/TRICE mode\n");
#endif                        
            break;
    }
    
     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }      
    return GD_OK;    
}


GERR GD_VO_I80_SetPixelTransCmd(GD_HANDLE* pHandle, U16 pixelwrcmd,U16 pixelrdcmd)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);

    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }
        
    GH_VO_I80_set_Pixel_RdWrcmd_pixel_wrcmd(pixelwrcmd);
    device->wrcmd = pixelwrcmd;
#ifdef DEBUG_PRINT
    GM_Printf("Set i80 write command:%x\n",pixelwrcmd);
#endif
    GH_VO_I80_set_Pixel_RdWrcmd_pixel_rdcmd(pixelrdcmd);
    device->rdcmd = pixelrdcmd;    
#ifdef DEBUG_PRINT
    GM_Printf("Set i80 read command:%x\n",pixelrdcmd);
#endif  

     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }      
    return GD_OK;
}


GERR GD_VO_I80_SetCmdFormat(GD_HANDLE* pHandle,GD_VO_I80_CMD_WIDTH_E cmdwidth,GD_VO_I80_CMD_ENDIAN_E cmdformat)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);

    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }
        
    switch(cmdwidth)
    {
    case GD_VO_I80_CMD_8BIT:
        GH_VO_I80_set_Cmd_Format_cmd_width(0);
        device->cmdwidth = GD_VO_I80_CMD_8BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 command in 8bits mode\n");
#endif
        break;
    case GD_VO_I80_CMD_16BIT:
        GH_VO_I80_set_Cmd_Format_cmd_width(1);
        device->cmdwidth = GD_VO_I80_CMD_16BIT;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 command in 16bits mode\n");
#endif
        break;
    }    
    
    switch(cmdformat)
    {
    case GD_VO_I80_CMD_LITTLE_ENDIAN:
        GH_VO_I80_set_Cmd_Format_cmd_transfer_format(0);
        device->cmdformat = GD_VO_I80_CMD_LITTLE_ENDIAN;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 command in little endian mode\n");
#endif
        break;
    case GD_VO_I80_CMD_BIG_ENDIAN:
        GH_VO_I80_set_Cmd_Format_cmd_transfer_format(1);
        device->cmdformat = GD_VO_I80_CMD_BIG_ENDIAN;
#ifdef DEBUG_PRINT
        GM_Printf("Set i80 command in big endian mode\n");
#endif
        break;
    }          

     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }     
    return GD_OK;
}

GERR GD_VO_I80_SetPolarCtrl(GD_HANDLE* pHandle, U32 polarctrl)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    
    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }
              
    GH_VO_I80_set_Polar_Ctrl(polarctrl);
    device->polarctrl = polarctrl;
#ifdef DEBUG_PRINT
    GM_Printf("Set i80 polar:\n%d\n",polarctrl);
#endif

     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }     
    return GD_OK;
}

GERR GD_VO_I80_SetPicResolution(GD_HANDLE* pHandle, GD_VO_I80_PIC_RESOLUTION_S picresolution)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);

    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }  
        
    GH_VO_I80_set_Pic_Resolution_width(picresolution.width);
    device->picresolution.width = picresolution.width;
#ifdef DEBUG_PRINT
    GM_Printf("Set i80 picture width:\n%d\n",picresolution.width);
#endif

    GH_VO_I80_set_Pic_Resolution_height(picresolution.height);
    device->picresolution.height = picresolution.height;
#ifdef DEBUG_PRINT
    GM_Printf("Set i80 picture height:\n%d\n",picresolution.height);
#endif

     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }     
    return GD_OK;    
        
}

GERR GD_VO_I80_SetTransTiming(GD_HANDLE* pHandle,GD_VO_I80_TRANS_TIMING_S *pTranstiming)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    
    if( pTranstiming==NULL)
    {
        return GD_ERR_BAD_PARAMETER;
       }
    
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);

    GH_VO_I80_set_Tcs_Timing_cs_ref(pTranstiming->csref);                                   
    device->transtiming.csref= pTranstiming->csref;

    GH_VO_I80_set_Tcs_Timing_tas(pTranstiming->tas);    
    device->transtiming.tas  = pTranstiming->tas;     
         
    if(pTranstiming->csref==1)
    { 
        GH_VO_I80_set_Tcsref_Wt_Timing_pwcsh_wt(pTranstiming->pwcsh_wt);                      
        device->transtiming.pwcsh_wt = pTranstiming->pwcsh_wt;    

        GH_VO_I80_set_Tcsref_Wt_Timing_pwcsl_wt(pTranstiming->pwcsl_wt);                  
        device->transtiming.pwcsl_wt = pTranstiming->pwcsl_wt; 

        GH_VO_I80_set_Tcsref_Rd_Timing_pwcsh_rd(pTranstiming->pwcsh_rd);                    
        device->transtiming.pwcsh_rd = pTranstiming->pwcsh_rd; 
        
        GH_VO_I80_set_Tcsref_Rd_Timing_pwcsl_rd(pTranstiming->pwcsl_rd);                         
        device->transtiming.pwcsl_rd = pTranstiming->pwcsl_rd;                     
    }
    else
    {
        GH_VO_I80_set_Twr_Timing_twrh(pTranstiming->twrh);
        device->transtiming.twrh = pTranstiming->twrh; 
    
        GH_VO_I80_set_Twr_Timing_twrl(pTranstiming->twrl);                             
        device->transtiming.twrl = pTranstiming->twrl;         
    
        GH_VO_I80_set_Trd_Timing_trdh(pTranstiming->trdh);                            
        device->transtiming.trdh = pTranstiming->trdh;      
    
        GH_VO_I80_set_Trd_Timing_trdl(pTranstiming->trdl);                                   
        device->transtiming.trdl = pTranstiming->trdl;             
    }
    GH_VO_I80_set_Todh_Timing((U32)(pTranstiming->todh));
    device->transtiming.todh =  pTranstiming->todh;          

    
    return GD_OK;                            
}

GERR GD_VO_I80_SetCfgValidImmediately(GD_HANDLE* pHandle,GBOOL bValidimmediately)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);        
    
    device->isCfgValidImmediately=bValidimmediately;
       
       return GD_OK;
}

GERR GD_VO_I80_Init(void)
{

    /* check if already initialized */
    if(I80InitDone != 0)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }

    I80InitDone = 1;
    return GD_OK;

}

GERR GD_VO_I80_Exit(void)
{
    if( I80InitDone == 0 )
    {
        return( GD_ERR_NOT_INITIALIZED );
    }
    i80_state_machine_dat.using    = 0;
    I80InitDone = 0;

    return( GD_OK );
}


GERR GD_VO_I80_Open( GD_VO_I80_OPEN_PARAMS_S *openParamsP,GD_HANDLE *pHandle)
{
    GD_VO_I80_Init();
    if(openParamsP==NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    if(i80_state_machine_dat.using)
    {
        return GD_ERR_DEVICE_BUSY;
    }
    
    i80_state_machine_dat.using = GTRUE;
    *pHandle=(GD_HANDLE )(&i80_state_machine_dat);
    
    i80_state_machine_dat.isCfgValidImmediately = GFALSE;
	//parameter decided by LCM(LCD module),put in the function of GD_VO_I80_Open()
	GD_VO_I80_SetTransWidth(pHandle,openParamsP->datawidth);
	GD_VO_I80_SetPixelBits(pHandle,openParamsP->colorformat);
	GD_VO_I80_SetMultiTransSeq(pHandle,openParamsP->datatransformat);// See LCD driver IC Spec,such as ILI9342C-MDT[1:0] which is configurable
	GD_VO_I80_SetPixelTransCmd(pHandle,openParamsP->wrcmd,openParamsP->rdcmd);
	GD_VO_I80_SetCmdFormat(pHandle,openParamsP->cmdwidth,openParamsP->cmdformat);//width of command
	GD_VO_I80_SetPolarCtrl(pHandle,openParamsP->polarctrl);	//6'b001000	
	GD_VO_I80_SetPicResolution(pHandle,openParamsP->picresolution);//Picture/Video Feature given by VOUT
	GD_VO_I80_SetTransTiming(pHandle,&(openParamsP->transtiming));	//write and read timing
	i80_state_machine_dat.isUseHWDelay=openParamsP->isUseHWDelay;
	//i80 delay parameter
	if(openParamsP->isUseHWDelay==1)
	{
		GD_VO_I80_DelayEnable(pHandle,openParamsP->delayms,openParamsP->delaycmd);		
	}
	else
	{
		GD_VO_I80_DelayDisable(pHandle); 	
	}

    return GD_OK;

}

GERR GD_VO_I80_Close(GD_HANDLE *pHandle)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    device->using = GFALSE;
    pHandle = NULL;
    GD_VO_I80_OnOff(pHandle,GD_VO_I80_OFF);
    return( GD_OK );
}



/*reset timing*/
GERR GD_VO_I80_HWResetLCM(GD_HANDLE* pHandle,GD_VO_I80_RST_TIMING_S *pRrstlcmtiming)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    
    if(pRrstlcmtiming==NULL)
    {
        return GD_ERR_BAD_PARAMETER;
       }

    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }  
           
    GH_VO_I80_set_Lcd_Rst_Para1_lcdrst_first_hlevel(pRrstlcmtiming->firstHTime);
    device->rstlcmtiming.firstHTime=pRrstlcmtiming->firstHTime;
    GH_VO_I80_set_Lcd_Rst_Para2_lcdrst_level(pRrstlcmtiming->firstLTime);
    device->rstlcmtiming.firstLTime=pRrstlcmtiming->firstLTime;    
    GH_VO_I80_set_Lcd_Rst_Para2_lcdrst_hsetup(pRrstlcmtiming->secondHTime);
    device->rstlcmtiming.secondHTime=pRrstlcmtiming->secondHTime;      
    
    GH_VO_I80_set_Lcd_Rst_Para1_lcdrst_en(1);//lcd reset enable,hardware will clean this bit automatically.
    
     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }     
    return GD_OK; 
}


GERR GD_VO_I80_DelayEnable(GD_HANDLE* pHandle,U16 delayms,U16 delaycmd)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    
    if(delayms>2047/10)
    {
        return GD_ERR_BAD_PARAMETER;
       }

    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }  
      
	GH_VO_I80_set_Delay_Para_delay_time(TIMING_PARA_HW_DELAY_CEIL_MS(delayms));
    device->delayms=delayms;
    GH_VO_I80_set_Delay_Para_delay_cmd(delaycmd);    
    device->delaycmd=delaycmd;    
    
    GH_VO_I80_set_Delay_Para_delay_cmd_en(1);//enable delay
    device->isUseHWDelay=1;    
    
     if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }   
    return GD_OK;     
    
}

GERR GD_VO_I80_DelayDisable(GD_HANDLE* pHandle)
{
    GD_VO_I80_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);
    
        
    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgInvalid();//cfg_end=0;
    }
    
    GH_VO_I80_set_Delay_Para_delay_cmd_en(0);//disable delay
    device->isUseHWDelay=0;    
        
    if(device->isCfgValidImmediately==GTRUE)
    {
        GD_VO_I80_CfgValid();//cfg_end=1;
    }
    
    return GD_OK;        
}

//wait sram_state=0
GBOOL GD_VO_I80_CheckNoCmdParaTrans(void)
{
    U32 i=0; 
    U8 value;
    while ( i < 2000 )//how to ensure the numbers of the cycle??
    {
        value = GH_VO_I80_get_Cmd_Sram_State_sram_state();
        if(value == 0) //no trans
            return GTRUE;
    #ifndef DEAD_LOOP_CHECK    //dead loop
        i++;
    #endif
    }
    return GFALSE;//time out
}


//wait rdcmd_para_en=1
GBOOL GD_VO_I80_CheckRdCmdParaReady(void)
{
    U32 i=0; 
    U8 value;
    while ( i < 2000 )//how to ensure the numbers of the cycle??
    {
        value = GH_VO_I80_get_Lcd_State_rdcmd_para_en();
        if(value == 1) //info of lcd_statexx is ready 
            return GTRUE;
    #ifndef DEAD_LOOP_CHECK    //dead loop
        i++;
    #endif
    }
    return GFALSE;//time out
}


GERR GD_VO_I80_CheckCmdErr(void)
{
    if(1==GH_VO_I80_get_I80_State_cmd_err())
    {
        return GD_ERR_I80_CMD_ERROR;
    }
    else
    {
        return GD_OK;
    }
}

GERR GD_VO_I80_CheckSramOverFlowErr(void)
{
    if(1==GH_VO_I80_get_I80_State_sram_overflow())
    {
        return GD_ERR_I80_SRAM_OVER_FLOW;
    }
    else
    {
        return GD_OK;
    }
}

GERR GD_VO_I80_CheckFramErr(void)
{
    if(1==GH_VO_I80_get_I80_State_frame_head_err())
    {
        return GD_ERR_I80_FRAME_HEAD_ERROR;
    }
    else
    {
        return GD_OK;
    }
}

//clear rdcmd_para_en=0
GBOOL GD_VO_I80_ClearRdCmdParaReady(void)
{
    while(0!=GH_VO_I80_get_Lcd_State_rdcmd_para_en())//!!!!!!!!!!!!!!
    {
        GH_VO_I80_set_Lcd_State_rdcmd_para_en(0);
    }
    return GTRUE;
}

U16 GD_VO_I80_GetLcdState(U8 indexreg)
{
    U16 retval;
    switch(indexreg)
    {
    case 0:
        retval=GH_VO_I80_get_Lcd_State0_lcd_para0();
        break;
    case 1:
        retval=GH_VO_I80_get_Lcd_State0_lcd_para1();
        break;
    case 2:
        retval=GH_VO_I80_get_Lcd_State1_lcd_para2();
        break;
    case 3:
        retval=GH_VO_I80_get_Lcd_State1_lcd_para3();
        break;
    case 4:
        retval=GH_VO_I80_get_Lcd_State2_lcd_para4();
        break;
    case 5:
        retval=GH_VO_I80_get_Lcd_State2_lcd_para5();
        break;
    case 6:
        retval=GH_VO_I80_get_Lcd_State3_lcd_para6();
        break;
    case 7:
        retval=GH_VO_I80_get_Lcd_State3_lcd_para7();
        break;
    case 8:
        retval=GH_VO_I80_get_Lcd_State4_lcd_para8();
        break;
    case 9:
        retval=GH_VO_I80_get_Lcd_State4_lcd_para9();
        break;
    default:
        retval=0xdead;                   
        break;
    }
    return retval;
}

///*--------------------------write only, no read----------------------------*/
//GERR GD_VO_I80_WriteCmdPara(GD_HANDLE * pHandle,U32 lcdcmdpara[],U8 cmdparanum)
//{
//    GBOOL   retval;
//    U8 i;
//    volatile U32 *psram;
//    if(pHandle == NULL)
//    {
//        return GD_ERR_INVALID_HANDLE;
//    }
//    
//    if(lcdcmdpara == NULL || cmdparanum>MAX_CMDPARA_NUM)
//    {
//        return GD_ERR_BAD_PARAMETER;
//       }    
//        
//    //wait sram_state=0
//    retval=GD_VO_I80_CheckNoCmdParaTrans();
//    if(retval==GFALSE)
//    {
//        return GD_ERR_I80_CHECK_TIME_OUT;
//    }
//    
//    //set number of command and parameter
//    GH_VO_I80_set_cmd_sram_state_cpn(cmdparanum);
//    
//    //write cmd and parameter to sram
//    psram=(volatile U32 *)REG_VOUT_I80_SRAM_BASE;
//    for(i=0;i<cmdparanum;i++)
//    {
//        *psram++=lcdcmdpara[i];
//    }
//    
//    GD_VO_I80_CmdParaValid();//sram_state=1
//    return GD_OK;
//}

/*--------read only, no write, one command, skip the dummy data, No Frame transferring-------------*/
GERR GD_VO_I80_ReadLcdInfo(GD_HANDLE* pHandle,GD_VO_I80_READ_STATE_S *pLcdrdstate)
{
    GBOOL   retval;
    U8 i;
    volatile U32 *psram;    
    volatile U16 dummydat;
    U16 *pinfo;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    
    if(pLcdrdstate == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
       }    
    
    if( (pLcdrdstate->rdnum<pLcdrdstate->rddummynum) || 
        (pLcdrdstate->rdnum>MAX_READINFO_NUM) || 
        (pLcdrdstate->plcdinfo==NULL) )
    {
        return GD_ERR_BAD_PARAMETER;
    }

    //wait sram_state=0
    retval=GD_VO_I80_CheckNoCmdParaTrans();
    if(retval==GFALSE)
    {
        return GD_ERR_I80_CHECK_TIME_OUT;
    }
    
    //set number of command and parameter
    GH_VO_I80_set_Cmd_Sram_State_cmd_para_num(1+pLcdrdstate->rdnum);//add 1 for command self        
    //set number of read parameter
    GH_VO_I80_set_Cmd_Sram_State_rd_para_num(pLcdrdstate->rdnum);
    //write cmd and parameter to sram
    psram=(volatile U32 *)REG_VO_I80_SRAM_CMDPARA;
    *psram++=LCD_READ_CMD((U32)(pLcdrdstate->rdstatecmd));
    for(i=0;i<pLcdrdstate->rdnum;i++)
    {
        *psram++=LCD_READ_PARA;
    }
    
    GD_VO_I80_CmdParaValid();//sram_state=1      
    
    //wait rdcmd_para_en=1,LCD information ready
    retval=GD_VO_I80_CheckRdCmdParaReady();
    if(retval==GFALSE)
    {
        return GD_ERR_I80_CHECK_TIME_OUT;
    }    
    //read lcd_state register
    for(i=0;i<pLcdrdstate->rddummynum;i++)//skip dummy data
    {
        dummydat=GD_VO_I80_GetLcdState(i);
    }
    
    for(pinfo=pLcdrdstate->plcdinfo;i<pLcdrdstate->rdnum;i++)//useful data
    {
        *pinfo++=GD_VO_I80_GetLcdState(i);
    }
    //finish reading LCD information , rdcmd_para_en is cleaned by hardware or software
    GD_VO_I80_ClearRdCmdParaReady();
        
       return GD_OK;
}

/*--------------------read&write, not skip the dummy data-------------------*/
GERR GD_VO_I80_TransCmdPara(GD_HANDLE* pHandle,GD_VO_I80_TRANS_STATE_S *pLcdtransstate)
{
    GBOOL   retval0,retval1;
    U8 i;
    volatile U32 *psram;    
    U16 *pinfo;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    
    if(pLcdtransstate == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
       }    

    if( (pLcdtransstate->cmdparanum>MAX_CMDPARA_NUM) || 
        (pLcdtransstate->rdnum>MAX_READINFO_NUM) || 
        (pLcdtransstate->plcdcmdpara==NULL) ||
        ((pLcdtransstate->rdnum!=0) && (pLcdtransstate->plcdinfo==NULL)) )
    {
        return GD_ERR_BAD_PARAMETER;
    }    
    
    //wait sram_state=0
    retval0=GD_VO_I80_CheckNoCmdParaTrans();
    if(retval0==GFALSE)
    {
        return GD_ERR_I80_CHECK_TIME_OUT;
    }
    
    //set number of command and parameter
    GH_VO_I80_set_Cmd_Sram_State_cmd_para_num(pLcdtransstate->cmdparanum);
    //set number of read parameter
    GH_VO_I80_set_Cmd_Sram_State_rd_para_num(pLcdtransstate->rdnum);
        
    //write cmd and parameter to sram
    psram=(volatile U32 *)REG_VO_I80_SRAM_CMDPARA;
    for(i=0;i<pLcdtransstate->cmdparanum;i++)
    {
        *psram++=pLcdtransstate->plcdcmdpara[i];
    }
    
    GD_VO_I80_CmdParaValid();//sram_state=1
    
    if(0!=pLcdtransstate->rdnum)
    {
        //wait rdcmd_para_en=1,LCD information ready
        retval1=GD_VO_I80_CheckRdCmdParaReady();
        if(retval1==GFALSE)
        {
            return GD_ERR_I80_CHECK_TIME_OUT;
        }    
        
        pinfo=pLcdtransstate->plcdinfo;
        for(i=0;i<pLcdtransstate->rdnum;i++)//dummy and useful data
        {
            *pinfo++=GD_VO_I80_GetLcdState(i);
        }
        //finish LCD information read, rdcmd_para_en cleaned by hardware
        GD_VO_I80_ClearRdCmdParaReady();        
        
    }
    
    return GD_OK;    
    
}

/*-----------------send pixel-writing command to LCM-------------------*/
GERR GD_VO_I80_EnterPixelWrite(GD_HANDLE* pHandle)
{
    GD_VO_I80_TRANS_STATE_S        wrstate;
    GD_VO_I80_STATE_MACHINE_S    *device;
    U32    wrcmdinsram;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);    
    
    wrcmdinsram=LCD_WRITE_CMD((U32)(device->wrcmd));
    wrstate.cmdparanum=1;
    wrstate.rdnum=0;
    wrstate.plcdcmdpara=&wrcmdinsram;
    wrstate.plcdinfo=NULL;    
    return(GD_VO_I80_TransCmdPara(pHandle,&wrstate));
}

/*-----------------send pixel-reading command to LCM-------------------*/
GERR GD_VO_I80_EnterPixelReading(GD_HANDLE* pHandle)
{
    GD_VO_I80_TRANS_STATE_S        wrstate;
    GD_VO_I80_STATE_MACHINE_S    *device;
    U32    rdcmdinsram;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_VO_I80_STATE_MACHINE_S *)(*pHandle);    
    
    rdcmdinsram=LCD_WRITE_CMD((U32)(device->rdcmd));
    wrstate.cmdparanum=1;
    wrstate.rdnum=0;
    wrstate.plcdcmdpara=&rdcmdinsram;
    wrstate.plcdinfo=NULL;    
    return(GD_VO_I80_TransCmdPara(pHandle,&wrstate));
}

