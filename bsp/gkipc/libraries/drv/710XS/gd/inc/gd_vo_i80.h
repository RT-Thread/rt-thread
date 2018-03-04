/*!
*******************************************************************************
**
** \file      gd_i80.h
**
** \brief     I80
**
**            Copyright:   2012 - 2015 (C) GoKe Microelectronics Chengdu Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      
**
******************************************************************************/
#ifndef _GD_VO_I80_H_
#define _GD_VO_I80_H_

#include <gtypes.h>
#include "gmodids.h"
#include "gd_int.h"
#include "gd_uart.h"

#define DEAD_LOOP_CHECK

#define I80_DESIGN_REF_CLK_FREQ 200//MHz    GK7101S-->200MHz GK8601-->300MHz   

#define I80_CLK_FREQ			100//MHz   GK7101S: FPGA-->100MHz   IC-->200MHz
//#define I80_CLK_PERIOD			(1000/I80_CLK_FREQ)//   5ns/Cycle
#define TIMING_PARA_CEIL_NS(x)	(((x)*I80_CLK_FREQ+999)/1000)

#define I80_1ST_H_L_COUNTER     (10*I80_DESIGN_REF_CLK_FREQ)
#define I80_2ND_H_COUNTER       (100*I80_DESIGN_REF_CLK_FREQ)
#define I80_HW_DELAY_COUNTER    (100*I80_DESIGN_REF_CLK_FREQ)
//#define I80_RST_1ST_UNIT        (I80_1ST_H_L_COUNTER/I80_CLK_FREQ)//us  10
//#define I80_RST_2ND_UNIT        (I80_2ND_H_COUNTER/I80_CLK_FREQ)//us  100

#define TIMING_PARA_FIRST_H_CEIL_MS(x)  ((1000*I80_CLK_FREQ*(x)+I80_1ST_H_L_COUNTER-1)/I80_1ST_H_L_COUNTER)
#define TIMING_PARA_FIRST_L_CEIL_MS(x)  ((1000*I80_CLK_FREQ*(x)+I80_1ST_H_L_COUNTER-1)/I80_1ST_H_L_COUNTER)
#define TIMING_PARA_SECOND_H_CEIL_MS(x) ((1000*I80_CLK_FREQ*(x)+I80_2ND_H_COUNTER-1)/I80_2ND_H_COUNTER)
#define TIMING_PARA_HW_DELAY_CEIL_MS(x) ((1000*I80_CLK_FREQ*(x)+I80_HW_DELAY_COUNTER-1)/I80_HW_DELAY_COUNTER)
//#define I80_CLK_10US_CYCLE	(10*I80_CLK_FREQ)//2000     //(10000/(1000/200))cycles     
//#define I80_CLK_100US_CYCLE	(100*I80_CLK_FREQ)//20000 //(100000/(1000/200))cycles
//#define TIMING_PARA_FIRST_H_CEIL_MS(x)	(((x)*1000*I80_CLK_FREQ+I80_CLK_10US_CYCLE-1)/I80_CLK_10US_CYCLE)//1ms*(200/2000*(10^6)
//#define TIMING_PARA_FIRST_L_CEIL_MS(x) 	(((x)*1000*I80_CLK_FREQ+I80_CLK_10US_CYCLE-1)/I80_CLK_10US_CYCLE)
//#define TIMING_PARA_SECOND_H_CEIL_MS(x)	(((x)*1000*I80_CLK_FREQ+I80_CLK_100US_CYCLE-1)/I80_CLK_100US_CYCLE)

#define I80READ     0
#define I80WRITE    1
#define I80COMMAND  0
#define I80PARA     1
#define LCD_WRITE_CMD(x)    ((I80COMMAND<<17)   |   (I80WRITE<<16)  |   (x))
#define LCD_WRITE_PARA(x)   ((I80PARA<<17)      |   (I80WRITE<<16)  |   (x))
#define LCD_READ_CMD(x)     ((I80COMMAND<<17)   |   (I80WRITE<<16)  |   (x))
#define LCD_READ_PARA       ((I80PARA<<17)      |   (I80READ <<16)  |   (0))
#define I80_DELAY_CMD       ((I80COMMAND<<17)   |   (I80WRITE<<16)  |   (0xFFFF))//never conflict with the command of driver ic!!!!

#define MAX_CMDPARA_NUM     128
#define MAX_READINFO_NUM    10

#define GD_VO_I80_ERR_BASE   (26 << 16)//(GD_ETH_MODULE_ID << 16)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************
enum
{
    GD_ERR_I80_NOT_SUPPORTED    = GD_VO_I80_ERR_BASE, //!< Device not supported.
    GD_ERR_I80_CMD_ERROR        = GD_VO_I80_ERR_BASE+1,
    GD_ERR_I80_SRAM_OVER_FLOW   = GD_VO_I80_ERR_BASE+2,
    GD_ERR_I80_FRAME_HEAD_ERROR = GD_VO_I80_ERR_BASE+4,
    GD_ERR_I80_CHECK_TIME_OUT   = GD_VO_I80_ERR_BASE+8,
};

#define DCn_LOW_CMD     (0<<5)
#define DCn_HIGH_CMD    (1<<5)
#define CSn_RISING      (0<<4)
#define CSn_FALLING     (1<<4)
#define VSYNC_LOW       (0<<3)
#define VSYNC_HIGH      (1<<3)
#define LCDRST_LOW      (0<<2)
#define LCDRST_HIGH     (1<<2)
#define RD_RISING       (0<<1)
#define RD_FALLING      (1<<1)
#define WR_RISING       (0<<0)
#define WR_FALLING      (1<<0)

//typedef     GD_INT_DATA_S* (*GD_I2S_ISR_T)(U8 channelIndex);

typedef enum
{
    GD_VO_I80_OFF=0,  //!< disable. 
    GD_VO_I80_ON=1,  //!< enable.

}GD_VO_I80_ONOFF_E;


/*!
*******************************************************************************
**
** \brief I80 data width modes.
**
** \sa    GD_VO_I80_DATA_WIDTH_E
**
******************************************************************************/
typedef enum
{
    GD_VO_I80_8BIT=0,  //!< 8 BIT.
    GD_VO_I80_9BIT=1,  //!< 9 BIT.
    GD_VO_I80_16BIT=2, //!< 16 BIT.
    GD_VO_I80_18BIT=3, //!< 18 BIT.
    GD_VO_I80_24BIT=4, //!< 24 BIT.
}GD_VO_I80_DATA_WIDTH_E;


/*!
*******************************************************************************
**
** \brief I2S operition modes.
**
** \sa    GD_VO_I80_COLOR_FORMAT_E
**
******************************************************************************/
typedef enum
{
    GD_VO_I80_PIXEL_16BIT=0, //!< 16 BIT.
    GD_VO_I80_PIXEL_18BIT=1, //!< 18 BIT.
    GD_VO_I80_PIXEL_24BIT=2, //!< 24 BIT.
    GD_VO_I80_PIXEL_12BIT=3, //!< 12 BIT.
}GD_VO_I80_COLOR_FORMAT_E;

/*!
*******************************************************************************
**
** \brief I80 trans data format.
**
** \sa    GD_VO_I80_TRANS_FORMAT_E
**
******************************************************************************/
typedef enum
{
    GD_VO_I80_18BIT_TWICE_1PIXEL = 0,     //!< 1PIXEL/TWICE
    GD_VO_I80_18BIT_TRICE_2PIXEL = 1,     //!< 2PIXEL/TRICE
}GD_VO_I80_TRANS_FORMAT_E;

/*!
*******************************************************************************
**
** \brief I80 command width.
**
** \sa    GD_VO_I80_CMD_WIDTH_E
**
******************************************************************************/
typedef enum
{
    GD_VO_I80_CMD_8BIT =0 ,     //!< 8BIT.
    GD_VO_I80_CMD_16BIT =1 ,    //!< 16BIT.
}GD_VO_I80_CMD_WIDTH_E;

/*!
*******************************************************************************
**
** \brief I80 command endian.
**
** \sa    GD_VO_I80_CMD_ENDIAN_E
**
******************************************************************************/
typedef enum
{
    GD_VO_I80_CMD_LITTLE_ENDIAN = 0 ,//!< low byte first.
    GD_VO_I80_CMD_BIG_ENDIAN =1 ,    //!< high byte first.  
}GD_VO_I80_CMD_ENDIAN_E;


/*!
*******************************************************************************
**
** \brief the struct of picture resolution.
**
** \sa    GD_VO_I80_PIC_RESOLUTION_S
**
******************************************************************************/
typedef struct
{
    U16 width;
    U16 height; 
}GD_VO_I80_PIC_RESOLUTION_S;


typedef struct
{
    U16 firstHTime;//11bits,10us/unit
    U16 firstLTime;//11bits,10us/unit
    U16 secondHTime;//11bits,100us/unit
}GD_VO_I80_RST_TIMING_S;

typedef struct
{
    U16 twrh;//9bit
    U16 twrl;//9bit
    U16 trdh;//9bit
    U16 trdl;//9bit
    U8  csref;//0--wr/rd as reference   1--cs as reference
    U16 tas;//9bit
    U16 pwcsh_wt;//9bit when cs_ref=1
    U16 pwcsl_wt;//9bit when cs_ref=1
    U16 pwcsh_rd;//9bit when cs_ref=1
    U16 pwcsl_rd;//9bit when cs_ref=1
    U16 todh;//9bit
}GD_VO_I80_TRANS_TIMING_S;


typedef struct
{
    U16 rdstatecmd;//read command--write to driver ic of lcd
    U8  rdnum;//state number including dummy
    U8  rddummynum;//dummy number
    U16 *plcdinfo;//array for lcd state, dummy state will not be put into plcdinfo
}GD_VO_I80_READ_STATE_S;//only one read command

typedef struct
{
//  GBOOL bcmdwr;//1--include reading command
//  GBOOL bcmdrd;//1--include writing command
    U8    cmdparanum;//1--total number of command and parameter
    U8    rdnum;//state number including dummy
    U32  *plcdcmdpara;//array of command and parameter 
    U16  *plcdinfo;//array of lcd state, dummy state will be put into plcdinfo
}GD_VO_I80_TRANS_STATE_S;

///*!
//*******************************************************************************
//**
//** I80 OPEN  parameter.
//**
//******************************************************************************/
typedef struct
{
    /*!
    Flag to request DMA for read/write transfer operation.
    */
//	U32                 	using;
	GD_VO_I80_DATA_WIDTH_E 	datawidth;
	GD_VO_I80_COLOR_FORMAT_E   colorformat;
	GD_VO_I80_TRANS_FORMAT_E   datatransformat;	
	U16						wrcmd;/*write pixel command*/
	U16						rdcmd;/*read pixel command*/
	GD_VO_I80_CMD_WIDTH_E		cmdwidth;
	GD_VO_I80_CMD_ENDIAN_E		cmdformat;
	U32						polarctrl;
	GD_VO_I80_PIC_RESOLUTION_S picresolution;	
	GD_VO_I80_TRANS_TIMING_S	transtiming;
	U32						isUseHWDelay;
	U16						delayms;
	U16						delaycmd;
//	GBOOL 					isCfgValidImmediately;
} GD_VO_I80_OPEN_PARAMS_S;

typedef struct
{
    U32                         using;
    GD_VO_I80_DATA_WIDTH_E      datawidth;
    GD_VO_I80_COLOR_FORMAT_E    colorformat;
    GD_VO_I80_TRANS_FORMAT_E    datatransformat;
    U16                         wrcmd;/*write command*/
    U16                         rdcmd;/*read command*/
    GD_VO_I80_CMD_WIDTH_E       cmdwidth;
    GD_VO_I80_CMD_ENDIAN_E      cmdformat;
    U32                         polarctrl;
    GD_VO_I80_PIC_RESOLUTION_S  picresolution;
    GD_VO_I80_RST_TIMING_S      rstlcmtiming;
    GD_VO_I80_TRANS_TIMING_S    transtiming;
    U32                         isUseHWDelay;
    U16                         delayms;
    U16                         delaycmd;
    GBOOL                       isCfgValidImmediately;
//    GD_HANDLE           i80Handle;      /* INT handle */
//    GD_I2S_ISR_T        i2sIsrRx;       /* ISR of the block */
//    GD_I2S_ISR_T        i2sIsrTx;       /* ISR of the block */
} GD_VO_I80_STATE_MACHINE_S;


#ifdef __cplusplus
extern "C" {
#endif

GERR GD_VO_I80_Exit(void);
GERR GD_VO_I80_Init(void);
GERR GD_VO_I80_Open(GD_VO_I80_OPEN_PARAMS_S * openParamsP,GD_HANDLE * pHandle);
GERR GD_VO_I80_Close(GD_HANDLE *pHandle);
GERR GD_VO_I80_OnOff(GD_HANDLE *pHandle,GD_VO_I80_ONOFF_E onoff);
GERR GD_VO_I80_SetTransWidth(GD_HANDLE* pHandle,GD_VO_I80_DATA_WIDTH_E data_width);
GERR GD_VO_I80_SetPixelTransCmd(GD_HANDLE* pHandle, U16 pixelwrcmd,U16 pixelrdcmd);
GERR GD_VO_I80_SetPixelBits(GD_HANDLE* pHandle,GD_VO_I80_COLOR_FORMAT_E color_format);
GERR GD_VO_I80_SetMultiTransSeq(GD_HANDLE* pHandle,GD_VO_I80_TRANS_FORMAT_E datatransformat);
GERR GD_VO_I80_SetPicResolution(GD_HANDLE* pHandle, GD_VO_I80_PIC_RESOLUTION_S picresolution);
GERR GD_VO_I80_SetCmdFormat(GD_HANDLE* pHandle,GD_VO_I80_CMD_WIDTH_E cmdwidth,GD_VO_I80_CMD_ENDIAN_E cmdformat);
GERR GD_VO_I80_SetTransTiming(GD_HANDLE* pHandle,GD_VO_I80_TRANS_TIMING_S *pTranstiming);
GERR GD_VO_I80_SetCfgValidImmediately(GD_HANDLE* pHandle,GBOOL bValidimmediately);
GERR GD_VO_I80_CfgInvalid(void);
GERR GD_VO_I80_CfgValid(void);
GERR GD_VO_I80_CmdParaInvalid(void);
GERR GD_VO_I80_CmdParaValid(void);
GERR GD_VO_I80_SetPolarCtrl(GD_HANDLE* pHandle, U32 polarctrl);
GERR GD_VO_I80_HWResetLCM(GD_HANDLE* pHandle,GD_VO_I80_RST_TIMING_S *pRrstlcmtiming);
GERR GD_VO_I80_DelayEnable(GD_HANDLE* pHandle,U16 delayms,U16 delaycmd);
GERR GD_VO_I80_DelayDisable(GD_HANDLE* pHandle);
GBOOL GD_VO_I80_CheckNoCmdParaTrans(void);
GBOOL GD_VO_I80_CheckRdCmdParaReady(void);
GBOOL GD_VO_I80_ClearRdCmdParaReady(void);
GERR GD_VO_I80_CheckCmdErr(void);
GERR GD_VO_I80_CheckSramOverFlowErr(void);
GERR GD_VO_I80_CheckFramErr(void);
U16 GD_VO_I80_GetLcdState(U8 indexreg);
GERR GD_VO_I80_ReadLcdInfo(GD_HANDLE* pHandle,GD_VO_I80_READ_STATE_S *pLcdrdstate);
//GERR GD_VO_I80_WriteCmdPara(GD_HANDLE * pHandle,U32 lcdcmdpara[],U8 cmdparanum);
GERR GD_VO_I80_TransCmdPara(GD_HANDLE* pHandle,GD_VO_I80_TRANS_STATE_S *pLcdtransstate);
GERR GD_VO_I80_EnterPixelWrite(GD_HANDLE* pHandle);
GERR GD_VO_I80_EnterPixelReading(GD_HANDLE* pHandle);
#ifdef __cplusplus
}
#endif



#endif /* _GD_VO_I80_H_ */


/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

