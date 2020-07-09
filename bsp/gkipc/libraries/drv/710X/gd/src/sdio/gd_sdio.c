#include <stdio.h>
#include <string.h>

#include <gtypes.h>
#include <gd_int.h>
#include <gd_timer.h>
#include <gh_sdio_all.h>
#include <gh_gpio.h>
//#include "gkos/rtos_lib.h"
#include "gd_sdio.h"
#include "gd_gpio.h"
#include "rtthread.h"


int sdioInitDone=0;
//#define DEBUG_PRINT
#define SDIO_TIMEOUT_ACMD41      1000              /*timeout for acmd41 1s*/
#define SDIO_MAX_BLOCK_LEN       512               /*block size*/

#define REG_WR(reg,value)                                 (*((volatile U32 *)(reg))=(value))
#define REG_RD(reg,ret)                                   ((ret)=*((volatile U32 *)(reg)))

#define bit_to_litte(x) \
    ((U32)( \
        (((U32)(x) & (U32)0x000000ffUL) << 24) | \
        (((U32)(x) & (U32)0x0000ff00UL) <<  8) | \
        (((U32)(x) & (U32)0x00ff0000UL) >>  8) | \
        (((U32)(x) & (U32)0xff000000UL) >> 24) ))

#if 0
/*
 *sd card status
*/
enum
{
    SDIO_COM_STATE_CARD_REMOVED     = 0,
    SDIO_COM_STATE_CARD_DETECTION,
    SDIO_COM_STATE_CARD_READY,
};
#endif

/*
 *just like config
 *
*/
#define SDIO_PRE_ERASE          1
#define SWITCH_HIGH_SPEED       1

#define SWITCH_4BIT_MODE        1
#define SWITCH_1BIT_MODE        0

#define SDIO_AUTO_CMD12         0
#ifdef GK7101S
#define SDIO_HANDLE_COUNT       2              /* total handle count */
#else
#define SDIO_HANDLE_COUNT       1              /* total handle count */
#endif

#define SDIO_MAX_TRENSFER_BLK   0x80          /* 64K */
#define SDIO_MAX_ERASE_BLK      65535

#define GD_SDIO0                0
#define GD_SDIO1                1
/*
*interrupt config
*/
#define SDIO_INT_STATUS_EN      (1 | 1<<1 | 1<<3 | 1<<4 |1<<5 | 1<<6 | 1<<7)
#define SDIO_INT_SIG_EN         (1 | 1<<1 | 1<<3 | 1<<4 |1<<5 | 1<<6 | 1<<7)

/*config for dma*/
/* 7 -> 512Kbyte 6->256 5->128 4->64 3->32 2->16 1->8 0->4*/
#define SD_DEFAULT_BOUNDARY_SIZE    (512* 1024)
#define SD_DEFAULT_BOUNDARY_ARG     (7)

/*config for high speed*/
#define SDIO_SWITCH_CHECK        0
#define SDIO_SWITCH_SWITCH       1

#define MMC_NOREP                (1<<0)        /* no response*/
#define MMC_REP_136              (1<<1)        /* 136 bit response */
#define MMC_REP_48               (1<<2)        /* 48 bit response */
#define MMC_REP_48_BUSY          (1<<3)        /* card may send busy */
#define MMC_REP_CRC              (1<<4)        /* expect valid crc */
#define MMC_COM_INDEX_CHEC       (1<<5)        /* command index check enable */
#define MMC_DATE_PRES            (1<<6)        /* data present select */

#if 0
#define MMC_CMD_MASK   (3 << 5)          /* non-SPI command type */
#define MMC_CMD_AC     (0 << 5)
#define MMC_CMD_ADTC   (1 << 5)
#define MMC_CMD_BC     (2 << 5)
#define MMC_CMD_BCR    (3 << 5)

#define MMC_RSP_SPI_S1   (1 << 7)        /* one status byte */
#define MMC_RSP_SPI_S2   (1 << 8)        /* second byte */
#define MMC_RSP_SPI_B4   (1 << 9)        /* four data bytes */
#define MMC_RSP_SPI_BUSY (1 << 10)       /* card may send busy */
#endif

#define MMC_RSP_NONE        (0)
#define MMC_RSP_R1          (MMC_REP_48|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R1B         (MMC_REP_48_BUSY|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R2          (MMC_REP_136|MMC_REP_CRC)
#define MMC_RSP_R3          (MMC_REP_48)
#define MMC_RSP_R4          (MMC_REP_48)
#define MMC_RSP_R5          (MMC_REP_48|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R6          (MMC_REP_48|MMC_REP_CRC|MMC_COM_INDEX_CHEC)
#define MMC_RSP_R7          (MMC_REP_48)

#define SDIO_IRQ_CMD_COMPLETE        0x0001
#define SDIO_IRQ_BLOCK_GAP_EVENT     0x0002
#define SDIO_IRQ_DMA                 0x0004
#define SDIO_IRQ_TRANSFER_COMPLETE   0x0008
#define SDIO_IRQ_WRITE_READY         0x0010
#define SDIO_IRQ_CARD_INSERTED       0x0020
#define SDIO_IRQ_READ_READY          0x0040
#define SDIO_IRQ_CARD_REMOVED        0x0080

#define SDIO_IRQ_NO_CARD             0x0100
#define SDIO_ERROR_IRQ               0x8000

/*SDIO  STATUS*/
#define SDIO_ERR_CMD                  -1
#define SDIO_WAIT                    0x00
#define SDIO_CMD_COMPLETE            0x01
#define SDIO_TRANSFER_COMPLETE       0x02

/*SDIO ERROR*/
#define SDIO_OK                      0

static int g_sdioError      = SDIO_OK;
static int g_cmdStatus      = SDIO_WAIT;
static int g_transferStatus = SDIO_WAIT;
#if 1
static GBOOL sdInsertState  = GTRUE;
static GBOOL sdChangeState  = GTRUE;
#endif

U8 *g_buffer                =NULL;
U32 g_block_size            =0;
U32 resp[SDIO_HANDLE_COUNT][4];

/* frequency bases */
/* divided by 10 to be nice to platforms without floating point */
static const int fbase[] = {
    10000,
    100000,
    1000000,
    10000000,
};

/* Multiplier values for TRAN_SPEED.  Multiplied by 10 to be nice
 * to platforms without floating point.
 */
static const int multipliers[] = {
    0,    /* reserved */
    10,
    12,
    13,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60,
    70,
    80,
};

static sdioHandleT    sdioHandleArray[SDIO_HANDLE_COUNT];
static U32   sdioComState[SDIO_HANDLE_COUNT];
static U32   dma_buffer[0x8000] __attribute__ ((section(".nocache_buffer"))) = {0,};//128K
static U8    wifiIndex = 0xFF;

GD_HANDLE                sdioHandle0;
GD_HANDLE                sdioHandle1;
#ifdef GK7101S
GD_HANDLE                sdioHandle2;
GD_HANDLE                sdioHandle3;
#endif


/* class 1 */
#define MMC_GO_IDLE_STATE         0   /* bc                                  */
#define MMC_SEND_OP_COND          1   /* bcr  [31:0] OCR       R3      */
#define MMC_ALL_SEND_CID          2   /* bcr                           R2         */
#define MMC_SET_RELATIVE_ADDR     3   /* ac   [31:16] RCA        R1     */
#define MMC_SET_DSR               4   /* bc   [31:16] RCA                */
#define MMC_SWITCH                6   /* ac   [31:0] See below   R1b     */
#define MMC_SELECT_CARD           7   /* ac   [31:16] RCA        R1      */
#define MMC_SEND_EXT_CSD          8   /* adtc                    R1          */
#define MMC_SEND_CSD              9   /* ac   [31:16] RCA        R2      */
#define MMC_SEND_CID             10   /* ac   [31:16] RCA        R2      */
#define MMC_READ_DAT_UNTIL_STOP  11   /* adtc [31:0] dadr        R1      */
#define MMC_STOP_TRANSMISSION    12   /* ac                      R1b         */
#define MMC_SEND_STATUS          13   /* ac   [31:16] RCA        R1      */
#define MMC_GO_INACTIVE_STATE    15   /* ac   [31:16] RCA               */
#define MMC_SPI_READ_OCR         58   /* spi                  spi_R3         */
#define MMC_SPI_CRC_ON_OFF       59   /* spi  [0:0] flag      spi_R1     */

/* class 2 */
#define MMC_SET_BLOCKLEN         16   /* ac   [31:0] block len   R1      */
#define MMC_READ_SINGLE_BLOCK    17   /* adtc [31:0] data addr   R1  */
#define MMC_READ_MULTIPLE_BLOCK  18   /* adtc [31:0] data addr   R1  */

/* class 3 */
#define MMC_WRITE_DAT_UNTIL_STOP 20   /* adtc [31:0] data addr   R1  */

/* class 4 */
#define MMC_SET_BLOCK_COUNT      23   /* adtc [31:0] data addr   R1  */
#define MMC_WRITE_BLOCK          24   /* adtc [31:0] data addr   R1  */
#define MMC_WRITE_MULTIPLE_BLOCK 25   /* adtc                    R1            */
#define MMC_PROGRAM_CID          26   /* adtc                    R1            */
#define MMC_PROGRAM_CSD          27   /* adtc                    R1         */

/* class 6 */
#define MMC_SET_WRITE_PROT       28   /* ac   [31:0] data addr   R1b */
#define MMC_CLR_WRITE_PROT       29   /* ac   [31:0] data addr   R1b */
#define MMC_SEND_WRITE_PROT      30   /* adtc [31:0] wpdata addr R1 */

/* class 5 */
#define MMC_ERASE_GROUP_START    35   /* ac   [31:0] data addr   R1  */
#define MMC_ERASE_GROUP_END      36   /* ac   [31:0] data addr   R1  */
#define MMC_ERASE                38   /* ac                      R1b        */

/* class 9 */
#define MMC_FAST_IO              39   /* ac   <Complex>         R4  */
#define MMC_GO_IRQ_STATE         40   /* bcr                     R5          */

/* class 7 */
#define MMC_LOCK_UNLOCK          42   /* adtc                    R1b */

/* class 8 */
#define MMC_APP_CMD              55   /* ac   [31:16] RCA        R1  */
#define MMC_GEN_CMD              56   /* adtc [0] RD/WR          R1  */


/* SD commands                           type  argument     response */
/* class 0 */
/* This is basically the same command as for MMC with some quirks. */
#define SD_SEND_RELATIVE_ADDR     3   /* bcr                     R6  */
#define SD_SEND_IF_COND           8   /* bcr  [11:0] See below   R7  */

/* class 10 */
#define SD_SWITCH                 6   /* adtc [31:0] See below   R1  */

/* Application commands */
#define SD_APP_SET_BUS_WIDTH      6   /* ac   [1:0] bus width    R1  */
#define SD_APP_SEND_NUM_WR_BLKS  22   /* adtc                    R1  */
#define SD_APP_OP_COND           41   /* bcr  [31:0] OCR         R3  */
#define SD_APP_SEND_SCR          51   /* adtc                    R1  */


#define SD_CMD_ERASE_WR_BLK_START  32
#define SD_CMD_ERASE_WR_BLK_END    33

int GM_Printf(const char *__format, ...);
void GD_SDIO_SetSdState( U32 index, U32 uSdioState);
U32 GD_SDIO_GetSdState( U32 index);
GBOOL GD_SDIO_Get_inserted_flag(U32 index);

#if 0
static void printf_buff(char *function, unsigned char *ptr)
{
	int i = 0;

	GM_Printf("===================%s start===================\n", function);
	for(i = 0; i < 0x200; i++)
	{
		if(i%16 == 0)
		{
			GM_Printf("\n");
		}
		GM_Printf("%02x ", ptr[i]);

	}
	GM_Printf("\n===================%s end===================\n", function);
}
#endif

/*!
********************************************************************************
**note:wo need flush date to memery when wo use dma or adma
**
********************************************************************************
*/
static sdioHandleT *sdioAllocateHandle(U32 index)
{
    sdioHandleT *sdioptr=NULL;

    sdioHandleArray[index].inUse           = 1;
    sdioHandleArray[index].index           = index;
    sdioHandleArray[index].devicePtr.index = index;
    sdioptr                                = &(sdioHandleArray[index]);
    return sdioptr;
}

static void sdioSoftReset(U32 index)
{
    GH_SDIO_set_Control01Reg_SoftwareResetAll(index, 1);
    GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index, 1);
    GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index, 1);
}

static void sdioClockOnOff(U32 index, U32 on)
{
    if (on == 0)
    {
        GH_SDIO_set_Control01Reg_SdClkEn(index, 0);
    }
    else
    {
        GH_SDIO_set_Control01Reg_SdClkEn(index, 1);
    }
}

static void sdioSetClockDiv(U32 index, U8 div)
{

    GH_SDIO_set_Control01Reg_SdclkFreSelect(index, div);
    GH_SDIO_set_Control01Reg_InternalClkEn(index, 1);

    while(1)
    {
        if(GH_SDIO_get_Control01Reg_InternalClkStable(index)&0x1)
              break;
    }
    sdioClockOnOff(index, 1);
}

static void sdioSelectVoltage(U32 index)
{
    U32 caps = 0;
    caps=GH_SDIO_get_CapReg(index);

    if(caps & 0x1<<24)
    {
        GH_SDIO_set_Control00Reg_SdBusVoltageSelect(index, 0x7);
        GH_SDIO_set_Control00Reg_SdBusPower(index, 1);
#ifdef DEBUG_PRINT
        GM_Printf("sdio 3.3v\n");
#endif
    }
    else if(caps & 0x1<<25)
    {
        GH_SDIO_set_Control00Reg_SdBusVoltageSelect(index, 0x6);
        GH_SDIO_set_Control00Reg_SdBusPower(index, 1);
    }
    else if(caps & 0x1<<26)
    {
        GH_SDIO_set_Control00Reg_SdBusVoltageSelect(index, 0x5);
        GH_SDIO_set_Control00Reg_SdBusPower(index, 1);
    }
}

static void sdioSetTimeoutControl(U32 index,U8 timeout)
{
    GH_SDIO_set_Control01Reg_DataTimeoutCounterValue(index, timeout);
}

static void sdioSetHostctlSpeed(U32 index, U8 mode)
{
    GH_SDIO_set_Control00Reg_HostSpeedEn(index, mode);
}

static void sdioSetHostctlWidth(U32 index,U8 mode)
{
    GH_SDIO_set_Control00Reg_DataTraWidth(index, mode);
}

static void sdioEnableIntStatus(U32 index)
{
    /*clear int*/
    if(GH_SDIO_get_NorIntStaReg_ErrInt(index) & 0x1)
    {
        GH_SDIO_set_NorIntStaReg(index, GH_SDIO_get_NorIntStaReg(index));
        GH_SDIO_set_ErrIntStaReg(index, GH_SDIO_get_ErrIntStaReg(index));
    }
    GH_SDIO_set_NorIntStaEnReg(index, 0x0000);
    GH_SDIO_set_NorIntStaEnReg(index, SDIO_INT_STATUS_EN);
    GH_SDIO_set_ErrIntStaEnReg(index, 0xffff);
}

static void sdioEnableIntSig(U32 index)
{
    GH_SDIO_set_NorIntSigEnReg(index, 0x0000);
    GH_SDIO_set_NorIntSigEnReg(index, SDIO_INT_SIG_EN);
    GH_SDIO_set_ErrIntSigEnReg(index, 0xffff);
}


static void sdioSetBlkSizeRegister(U32 index, U16 boundary,U16 blksize)
{
    GH_SDIO_set_BlkSizeReg_HostSdmaBufSize(index, boundary);
    GH_SDIO_set_BlkSizeReg_TraBlkSize(index, blksize);
}

static void sdioSetBlkCntRegister(U32 index, U16  blkcnt)
{
    GH_SDIO_set_BlkCouReg_BlkCountForCurTra(index, blkcnt);
}

static void sdioSetArgRegister (U32 index, U32 arg)
{
    GH_SDIO_set_ArgReg(index, arg);
}

static U32 sdioSetTraModeRegister (U32 index, U32  multblk, U32 direction, U32  autocmd12en,
    U32  blkcnten, U32  dmaen)
{
    U32 modereg=GH_SDIO_get_TranModeReg(index);
    modereg=(modereg & ~0xffff) | (direction << 5)| (multblk << 4) | (dmaen << 2) | (autocmd12en << 1) | (blkcnten << 0) ;
    return modereg<<16;
}

static void sdioSetSystemAddressReg(U32 index,U32 addr)
{
    GH_SDIO_set_SysAddrReg(index, addr);
}

/*
 *    note:There are two types of Data packet format for the SD card
 *
 *    when Data Packet Format for Wide Width Data,wo need do some change
*/
static U32 GD_SDIO_Swab32(U32 value)
{
    union w
    {
        int a;
        char b;
    } c;
    c.a = 1;
    if(c.b ==1)
    {
        return bit_to_litte(value);
    }
    return value;
}

#if 0
/*!
********************************************************************************
**sdio config gpio
**
********************************************************************************
*/
static void GD_SDIO_GpioConfig()
{
    GH_GPIO_set_INPUT_CFG(12, 0x00000029);
    //REG_WR((REG_GPIO_INPUT_CFG  + 0x30),0x00000029);  /* sd_wp  GPIO41   */
    GH_GPIO_set_INPUT_CFG(15, 0x0000002c);
    //REG_WR((REG_GPIO_INPUT_CFG  + 0x3c),0x0000002c);  /* sd_data1  GPIO44 */
    GH_GPIO_set_INPUT_CFG(14, 0x0000002a);
    //REG_WR((REG_GPIO_INPUT_CFG  + 0x38),0x0000002a);  /* sd_data0  GPIO42 */
    GH_GPIO_set_INPUT_CFG(13, 0x00000032);
    //REG_WR((REG_GPIO_INPUT_CFG  + 0x34),0x00000032);  /* sd_cdn  GPIO50  */
    GH_GPIO_set_INPUT_CFG(22, 0x00000030);
    //REG_WR((REG_GPIO_INPUT_CFG  + 0x58),0x00000030);  /* sd_cmd   GPIO48 */
    GH_GPIO_set_INPUT_CFG(17, 0x00000028);
    //REG_WR((REG_GPIO_INPUT_CFG  + 0x44),0x00000028);  /* sd_data3  GPIO40  */
    GH_GPIO_set_INPUT_CFG(16, 0x0000002b);
    //REG_WR((REG_GPIO_INPUT_CFG  + 0x40),0x0000002b);  /* sd_data2  GPIO43  */
    GH_GPIO_set_OUTPUT_CFG(44, 0x00008917);
    //REG_WR((REG_GPIO_OUTPUT_CFG + 0xb0),0x00008917);  /* sd_data1  GPIO44 */
    GH_GPIO_set_OUTPUT_CFG(42, 0x00008816);
    //REG_WR((REG_GPIO_OUTPUT_CFG + 0xa8),0x00008816);  /* sd_data0  GPIO42 */
    GH_GPIO_set_OUTPUT_CFG(46, 0x0000001f);
    //REG_WR((REG_GPIO_OUTPUT_CFG + 0xb8),0x0000001f);  /* sd_clk  GPIO46 */
    GH_GPIO_set_OUTPUT_CFG(48, 0x0000901e);
    //REG_WR((REG_GPIO_OUTPUT_CFG + 0xc0),0x0000901e);  /* sd_cmd  GPIO48 */
    GH_GPIO_set_OUTPUT_CFG(40, 0x00008b19);
    //REG_WR((REG_GPIO_OUTPUT_CFG + 0xa0),0x00008b19);  /* sd_data3  GPIO40*/
    GH_GPIO_set_OUTPUT_CFG(43, 0x00008a18);
    //REG_WR((REG_GPIO_OUTPUT_CFG + 0xac),0x00008a18);  /* sd_data2  GPIO43 */
    GH_GPIO_set_INT_EN((U32)0x00000001);
    //REG_WR(REG_GPIO_INT_EN,0x00000001);
}
#endif

void GD_SDIO_Rest(U32 index)
{
    sdioSoftReset(index);
    sdioClockOnOff(index, 0);
    sdioSetClockDiv(index, 1);
    sdioSelectVoltage(index);
    sdioSetTimeoutControl(index, 0xe);
    sdioSetHostctlSpeed(index, 0);
    sdioSetHostctlWidth(index, 0);
    /*clear interrupt status*/
    GH_SDIO_set_NorIntStaReg(index, GH_SDIO_get_NorIntStaReg(index));
    GH_SDIO_set_ErrIntStaReg(index, GH_SDIO_get_ErrIntStaReg(index));

    /*card remove*/

	GD_SDIO_SetSdState(index, SDIO_COM_STATE_CARD_REMOVED);
    g_sdioError  = SDIO_OK;
    g_cmdStatus  = SDIO_WAIT;
    g_transferStatus = SDIO_WAIT;

    g_buffer=NULL;
    g_block_size=0;
    memset(resp[index],0,sizeof(resp[index]));
    memset(&sdioHandleArray[index].devicePtr,0,sizeof(sdioHandleArray[index].devicePtr));
    sdioEnableIntStatus(index);
    sdioEnableIntSig(index);
}

/*!
********************************************************************************
**sdio set cmd reg
**
********************************************************************************
*/
static void sdioSetCmdReg(U32 index,U32 cmdarg,U32 data,U32 flags)
{
    U8 cmd=cmdarg & 0x3f;
    unsigned short cmdval=(cmd<<8);
    //U32  arg;

    if(cmd==12)
    {
        /*abort cmd*/
        cmdval |=(3<<6);
    }
    else
    {
        /*suspend/resume cmd(sdio)*/
    }

    if (flags & MMC_REP_136)                /* Long REP */
    {
        cmdval |= 0x01;
    }
    else if (flags & MMC_REP_48_BUSY)        /* R1B */
    {
        cmdval |= 0x03;
    }
    else if (flags & MMC_REP_48)            /* Normal REP */
    {
        cmdval |= 0x02;
    }

    if (flags & MMC_COM_INDEX_CHEC)
    {
        cmdval |= (1<<5);
    }

    if (flags & MMC_REP_CRC)
    {
        cmdval |= (1<<3);
    }

    if (data)
    {
        cmdval |= (1<<4);
    }

    //arg=cmdval<<16 | cmdarg>>16;
    //GH_SDIO_set_TranModeReg(arg);
    GH_SDIO_set_TranModeReg(index, cmdarg>>16);
    GH_SDIO_set_CmdReg(index, cmdval);
}

/*!
********************************************************************************
**
** \brief send command
** This function set and  send command.
**
** \param cmd     cmd mode
** \param arg      command argument
** \param data    data==1:data present:no data present
** \param flags    response mode
**
** \return
** - GD_OK  if no error
** - -1  if error
********************************************************************************
*/

static int  sdioIssueCmd(U32 index,U32 cmd, U32 arg, U32 data, U32 flags)
{
    int i;
    /*wait for cmd line free */
    for(i=0;i<0x1000;i++)
    {
        if(!(GH_SDIO_get_PresentStateReg_CmdInhibitCmd(index)))
            break;
        GD_TIMER_Delay(10);
    }
	if (i >= 0x1000)
	{
		printf("Error! Wait for cmd line free time out!\n");
		return -1;
	}

    /*wait for data line free */
    if(flags & MMC_REP_48_BUSY)
    {
		 if(cmd != MMC_STOP_TRANSMISSION)
		 {
			 for(i = 0; i < 0x1000; i++)
			 {
				 if(!(GH_SDIO_get_PresentStateReg_CmdInhibitData(index)))
					 break;
				 GD_TIMER_Delay(10);
			 }
		 }
		 if (i >= 0x1000)
		 {
			printf("Error! Wait for data line free time out!\n");
			return -1;
		 }
    }
    GH_SDIO_set_ArgReg(index, arg);
    g_cmdStatus=SDIO_WAIT;
    g_transferStatus=SDIO_WAIT;
    sdioSetCmdReg(index,cmd,data,flags);
     while(g_cmdStatus !=SDIO_ERR_CMD && g_cmdStatus != SDIO_CMD_COMPLETE)
     {
		if(!GD_SDIO_Get_inserted_flag(index))
		{
		 	return -1;
		}
	 	rt_thread_yield();
		//msleep(1);
     }
    g_cmdStatus=SDIO_WAIT;
    if(g_sdioError != GD_OK)
    {
        g_sdioError=GD_OK;
        return GD_ERR_SDIO_CMD_FAILED;
    }
    return GD_OK;
}

/*!
********************************************************************************
**\brief get card cid info
**
** \return
** - GD_OK  if no error
** - -1  if error
********************************************************************************
*/
static int GD_SDIO_GetCid(sdioBlockT *cardInfo)
{
    int i;
    int ret;
    ret=sdioIssueCmd(cardInfo->index, MMC_ALL_SEND_CID, 0, 0, MMC_RSP_R2);
    if (ret)
    {
#ifdef DEBUG_PRINT
        GM_Printf("CID broken\n");
#endif
        return GD_ERR_SDIO_CMD_FAILED;
    }

    for(i=0;i<4;i++)
    {
        cardInfo->cid[i]=resp[cardInfo->index][i];
    }

    /*Manufacturer ID*/
    cardInfo->cidInfo.MID=(resp[cardInfo->index][0]>>24)&0xff;
    /*OEM/Application ID*/
    cardInfo->cidInfo.OID=(resp[cardInfo->index][0]>>8)&0xff;
    /*Product name*/
    cardInfo->cidInfo.PNM[0]=resp[cardInfo->index][1] & 0xff;
    cardInfo->cidInfo.PNM[1]=((resp[cardInfo->index][1]>>8)&0xff);
    cardInfo->cidInfo.PNM[2]=((resp[cardInfo->index][1]>>16)&0xff);
    cardInfo->cidInfo.PNM[3]=((resp[cardInfo->index][1]>>24)&0xff);
    cardInfo->cidInfo.PNM[4]=resp[cardInfo->index][0]&0xff;
    /*Product revision*/
    cardInfo->cidInfo.PRV=(resp[cardInfo->index][2]>>24)&0xff;
    /*Product serial number*/
    cardInfo->cidInfo.PSN=((resp[cardInfo->index][3]>>24)&0xff) | ((resp[cardInfo->index][2]&0x00ffffff)<<8);
    /*Manufacturing date*/
    cardInfo->cidInfo.MDT=(resp[cardInfo->index][3]>>8)&0xfff;

    return GD_OK;
}

/*!
********************************************************************************
**\brief get card csd info
**
** \return
** - GD_OK  if no error
** - -1  if error
********************************************************************************
*/
static int GD_SDIO_GetCsd(sdioBlockT *cardInfo)
{
    int ret;
    unsigned long long csize,cmult;
    U32 freq,mult;
    int i;
    U32 temp=1;
    ret = sdioIssueCmd(cardInfo->index, MMC_SEND_CSD, cardInfo->rca, 0, MMC_RSP_R2);
    if(ret)
    {
#ifdef DEBUG_PRINT
        GM_Printf("sd get csd register failed \n");
#endif
        return GD_ERR_SDIO_CMD_FAILED;
    }
    for(i=0;i<4;i++)
    {
        cardInfo->csd[i]=resp[cardInfo->index][i];
    }
    /*csd revision(SDHC 2.0CSD; SD 1.0CSD)*/
    cardInfo->csdInfo.csdStructure=(resp[cardInfo->index][0]>>30) & 0x3;
    /*sd speed*/
    freq = fbase[(resp[cardInfo->index][0] & 0x7)];
    mult = multipliers[((resp[cardInfo->index][0] >> 3) & 0xf)];
    cardInfo->tran_speed = freq * mult;                /*speed:250000*/
    /*r/w blen*/
    cardInfo->read_bl_len = 1 << ((resp[cardInfo->index][1] >> 16) & 0xf);
    cardInfo->write_bl_len = cardInfo->read_bl_len;
    if (cardInfo->read_bl_len > SDIO_MAX_BLOCK_LEN)
    {
        temp = cardInfo->read_bl_len/SDIO_MAX_BLOCK_LEN;
        cardInfo->read_bl_len = SDIO_MAX_BLOCK_LEN;
    }
    if (cardInfo->write_bl_len > SDIO_MAX_BLOCK_LEN)
    {
        cardInfo->write_bl_len = SDIO_MAX_BLOCK_LEN;
    }

    if (cardInfo->highCapacity)
    {
        csize = (resp[cardInfo->index][1] & 0x3f) << 16 | (resp[cardInfo->index][2] & 0xffff0000) >> 16;
        cmult = 8;
    }
    else
    {
        csize = (resp[cardInfo->index][1] & 0x3ff) << 2 | (resp[cardInfo->index][2] & 0xc0000000) >> 30;
        cmult = (resp[cardInfo->index][2] & 0x00038000) >> 15;
    }
    /* sectorcount*/
    cardInfo->sectorcount=((csize + 1) << (cmult + 2))*temp;
    /*Get devicesize*/
    cardInfo->capacity_user = cardInfo->read_bl_len*cardInfo->sectorcount;
    cardInfo->csdInfo.tranSpeed=cardInfo->tran_speed;             /*transfer speed*/
    cardInfo->csdInfo.eraseBlkEn=((resp[cardInfo->index][2]>>14) & 0x1);          /*erase block enable*/
    cardInfo->csdInfo.permWriteProtect=(resp[cardInfo->index][3]>>13) & 0x1;      /*write protect*/
    cardInfo->csdInfo.tmpWriteProtect=(resp[cardInfo->index][3]>>12) & 0x1;       /*write protect*/
    return GD_OK;
}

/*!
********************************************************************************
**\brief get card rca info
**
** \return
** - GD_OK  if no error
** - -1  if error
********************************************************************************
*/
static int GD_SDIO_GetRca(sdioBlockT *cardInfo)
{
    int ret=0;
    ret = sdioIssueCmd(cardInfo->index, MMC_SET_RELATIVE_ADDR, 0x00000000,0, MMC_RSP_R6);
    if(ret)
    {
        return GD_ERR_SDIO_CMD_FAILED;
    }
    cardInfo->rca=resp[cardInfo->index][0] & 0xffff0000;
    return GD_OK;
}

/*!
********************************************************************************
**\brief get card scr info
**
** \return
** - GD_OK  if no error
** - -1  if error
********************************************************************************
*/
static int GD_SDIO_GetScr(sdioBlockT *cardInfo)
{
    int ret =0;
    U32 buffer[2]={0x00, 0x00};
    U32 cmd = 0;
    int dir_read=1;
    U32 addr1,addr2;

    ret = sdioIssueCmd(cardInfo->index,MMC_APP_CMD,cardInfo->rca,0, MMC_RSP_R1);
    if(ret)
    {
        return -1;
    }
    else
    {
        sdioSetBlkSizeRegister(cardInfo->index, 7,8);
        sdioSetBlkCntRegister(cardInfo->index, 1);
        sdioSetArgRegister(cardInfo->index, 0);
        cmd=sdioSetTraModeRegister(cardInfo->index, 0,dir_read,0,0,0);
        cmd |=SD_APP_SEND_SCR;
        g_block_size=8;
        g_buffer=(U8 *)&buffer[0];
        ret = sdioIssueCmd(cardInfo->index, cmd, 0, 1, MMC_RSP_R1);
        if(ret)
        {
            return GD_ERR_SDIO_CMD_NO_SUPPORTED;
        }
        while(g_transferStatus !=SDIO_ERR_CMD && g_transferStatus != SDIO_TRANSFER_COMPLETE)
        {
			if(!GD_SDIO_Get_inserted_flag(cardInfo->index))
			{
				return -1;
			}
			rt_thread_yield();
			//msleep(1);
        }
        g_transferStatus=SDIO_WAIT;
        addr1=buffer[0];
        addr2=buffer[1];
        buffer[0]= GD_SDIO_Swab32(addr1);
        buffer[1]= GD_SDIO_Swab32(addr2);
#ifdef DEBUG_PRINT
        printf("buffer[0]:%x,buffer[1]:%x",buffer[0],buffer[1]);
#endif

        cardInfo->scr.scrStructure  =  (buffer[0]&0xF0000000)>>28;
        cardInfo->scr.sdSpec        =  (buffer[0]&0x0F000000)>>24;
        cardInfo->scr.stateaftererase    =  (buffer[0]&0x00800000)>>23;
        cardInfo->scr.sdSecurity    =  (buffer[0]&0x00700000)>>20;
        cardInfo->scr.sdBusWith     =  (buffer[0]&0x000F0000)>>16;
    }

#ifdef DEBUG_PRINT
	switch (cardInfo->scr.sdSpec)
	{
		case 0:
			printf("sd card 1.0\n");
			break;
		case 1:
			printf("sd card 1.1\n");
			break;
		case 2:
			if ((buffer[0] >> 15) & 0x1)
			{
				printf("sd card 3.0\n");
			}
			else
			{
				printf("sd card 2.0\n");
			}
			break;
		default:
			break;
	}
#endif

   return GD_OK;
}

/*
*******************************************************************************
**
** \brief  sdio Handle Check
**
** \return
** - GD_OK  if no error
** - GD_ERR_INVALID_HANDLE   if error
*******************************************************************************
*/
static GERR    GD_SDIO_HandleCheck(sdioHandleT *sdioHandle)
{
	U32 index = 0;

	index = sdioHandle->index;
	if (index >= SDIO_HANDLE_COUNT || sdioHandleArray[index].inUse == 0)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_OK;
}

/*!
 ********************************************************************************
 **
 ** \brief check and switch sdio speed mode
 **
 ** This function set and  query switch group.
 **
 ** \param mode     mode==1?set:query
 ** \param group     which group
 ** \param value     value==1:set:no change
 ** \param status    return card status
 **
 ** \return
 ** - GD_OK if no error
 ********************************************************************************
 */
static int GD_SDIO_Switch(sdioBlockT *cardInfo,int mode, int group, U8 value, U32 *status)
{
    U32  arg = 0;
    U32 cmd=0;
    void *p = NULL;

    arg=mode<<31 |0x00ffffff;
    arg&=~(0xf<<(group*4));
    arg |=value<<(group*4);

    sdioSetBlkSizeRegister(cardInfo->index,7,0x40);
    sdioSetBlkCntRegister(cardInfo->index,1);
    sdioSetArgRegister(cardInfo->index,0);
    cmd=sdioSetTraModeRegister(cardInfo->index,0,1,0,0,0);
    cmd |=SD_SWITCH;
    g_block_size=64;
    p=(void *)status;
    g_buffer=(U8 *)p;
    if(sdioIssueCmd(cardInfo->index,cmd,arg,1,MMC_RSP_R1))
    {
        return GD_ERR_SDIO_CMD_FAILED;
    }
    while(g_transferStatus !=SDIO_ERR_CMD && g_transferStatus != SDIO_TRANSFER_COMPLETE)
    {
		if(!GD_SDIO_Get_inserted_flag(cardInfo->index))
		{
			return -1;
		}
		rt_thread_yield();
		//msleep(1);
    }
    g_transferStatus=SDIO_WAIT;
    return GD_OK;
}

/*!
********************************************************************************
**sdio set 4bit mode
**
** \return
** - GD_OK if no error
********************************************************************************
*/
static GERR GD_SDIO_EnableIO4(sdioBlockT *cardInfo)
{
     if(cardInfo->scr.sdBusWith & 0x1<<2)
     {
        if(sdioIssueCmd(cardInfo->index,MMC_APP_CMD,cardInfo->rca,0,MMC_RSP_R1))
        {
            return GD_ERR_SDIO_CARD_INIT_FAILED;
        }
        else
        {
            if(sdioIssueCmd(cardInfo->index,SD_SWITCH,0x02,0,MMC_RSP_R1))
            {
                return GD_ERR_SDIO_CARD_INIT_FAILED;
            }
        }
        GH_SDIO_set_Control00Reg_DataTraWidth(cardInfo->index,1);
    }
    return GD_OK;
}

#if 0
/*!
********************************************************************************
**sdio set 1bit mode
**
********************************************************************************
*/
static GERR GD_SDIO_EnableIO1(sdioBlockT *cardInfo)
{
     if(cardInfo->scr.sdBusWith & 0x1)
     {
        if(sdioIssueCmd(cardInfo->index, MMC_APP_CMD,cardInfo->rca,0,MMC_RSP_R1))
        {
            return GD_ERR_SDIO_CARD_INIT_FAILED;
        }
        else
        {
            if(sdioIssueCmd(cardInfo->index,SD_SWITCH,0x00,0,MMC_RSP_R1))
            {
                return GD_ERR_SDIO_CARD_INIT_FAILED;
            }
        }
        GH_SDIO_set_Control00Reg_DataTraWidth(cardInfo->index,0);
    }
    return GD_OK;
}
#endif

/*!
********************************************************************************
**sdio set high speed mode
**
********************************************************************************
*/
static int  GD_SDIO_EnableHSpeed(sdioBlockT *cardInfo)
{
    U32 timeout;
    U32 switch_status[16];
    if(cardInfo->scr.sdSpec>=1)
    {
        timeout=10;
        while (timeout--)
        {
            if(GD_SDIO_Switch(cardInfo, SDIO_SWITCH_CHECK, 0, 1,switch_status))
            {
                return GD_ERR_SDIO_CMD_FAILED;
            }

            if (!(GD_SDIO_Swab32(switch_status[7]) & 0x00020000))        /* busy or not*/
            {
#ifdef DEBUG_PRINT
                GM_Printf("card not busy\n");
#endif
                break;
            }
#ifdef DEBUG_PRINT
            GM_Printf("card busy timeout %d\n",timeout);
#endif
        }

        if ((GD_SDIO_Swab32(switch_status[3]) & 0x00020000))
        {
#ifdef DEBUG_PRINT
            GM_Printf("sd card support high speed\n");
#endif
            if(GD_SDIO_Switch(cardInfo, SDIO_SWITCH_SWITCH, 0, 1,switch_status))
            {
                return GD_ERR_SDIO_CARD_INIT_FAILED;
            }
            if ((GD_SDIO_Swab32(switch_status[4]) & 0x0f000000) == 0x01000000)
            {
                cardInfo->inhighspeed=1;
                return GD_OK;
            }
        }
    }
    return GD_ERR_SDIO_CMD_FAILED;
}

/*!
********************************************************************************
**sdio  HC card init
**
********************************************************************************
*/
static int GD_SDIO_SDInit(sdioBlockT *cardInfo)
{
    int ret=0;
    U32 hcs=0;
    int retries=1000;
    cardInfo->type=CARDTYPE_NONE;
    cardInfo->inhighspeed=0;
    cardInfo->maxTransferBlk=SDIO_MAX_TRENSFER_BLK;
    cardInfo->eraseGrpSize=SDIO_MAX_ERASE_BLK;
    ret=sdioIssueCmd(cardInfo->index, MMC_GO_IDLE_STATE, 0x00, 0, 0);
    if(ret)
    {
        return GD_ERR_SDIO_CARD_INIT_FAILED;
    }
    ret = sdioIssueCmd(cardInfo->index, SD_SEND_IF_COND, 0x000001aa,0,  MMC_RSP_R7);
    if (!ret && ((resp[cardInfo->index][0] & 0xff) == 0xaa))
    {
#ifdef DEBUG_PRINT
        printf("Cmd8:this is SD2.0 card\n");
#endif
        cardInfo->type=CARDTYPE_SD20;
        hcs = 0x00000000;
    }
    else if(ret)
    {
#ifdef DEBUG_PRINT
        printf("Cmd8:this is SD1.0 card\n");
#endif
        cardInfo->type=CARDTYPE_SD10;
    }

    retries=SDIO_TIMEOUT_ACMD41/10;
    while (retries--)
    {
        ret = sdioIssueCmd(cardInfo->index, MMC_APP_CMD, 0x00000000, 0,MMC_RSP_R1);
        if (ret)
        {
#ifdef DEBUG_PRINT
            printf("Cmd55 error!\n");
#endif
            continue;
        }

        ret = sdioIssueCmd(cardInfo->index, SD_APP_OP_COND, hcs | 0x00300000, 0,MMC_RSP_R3);
        if (ret)
        {
#ifdef DEBUG_PRINT
            printf("cmd41 error!\n");
#endif
            continue;
        }

        if ((resp[cardInfo->index][0] >> 24) & (1 << 7))
        {
            if(resp[cardInfo->index][0]>>24 & (1<<6))
            {
                cardInfo->type=CARDTYPE_SDHC;
                cardInfo->highCapacity=1;
#ifdef DEBUG_PRINT
                printf("this is sdhc card\n");
#endif
             }
             retries = -2;
             break;
        }
        GD_TIMER_Delay(10);
   }
   return retries;
}

/*!
********************************************************************************
**sdio  HC card init
**
********************************************************************************
*/
static GERR GD_SDIO_SDHCInit(sdioBlockT *cardInfo)
{
    int ret=0;
    U32 hcs=0;
    int retries=1000;
    cardInfo->type=CARDTYPE_NONE;
    cardInfo->inhighspeed=0;
    cardInfo->maxTransferBlk=SDIO_MAX_TRENSFER_BLK;
    cardInfo->eraseGrpSize=SDIO_MAX_ERASE_BLK;
    ret=sdioIssueCmd(cardInfo->index, MMC_GO_IDLE_STATE, 0x00, 0, 0);
    if(ret)
    {
        return GD_ERR_SDIO_CARD_INIT_FAILED;
    }
    ret = sdioIssueCmd(cardInfo->index, SD_SEND_IF_COND, 0x000001aa,0,  MMC_RSP_R7);
    if (!ret && ((resp[cardInfo->index][0] & 0xff) == 0xaa))
    {
#ifdef DEBUG_PRINT
        printf("Cmd8:this is SD2.0 card\n");
#endif
        cardInfo->type=CARDTYPE_SD20;
        hcs = 0x40000000;
    }
    else if(ret)
    {
#ifdef DEBUG_PRINT
        printf("Cmd8:this is SD1.0 card\n");
#endif
        cardInfo->type=CARDTYPE_SD10;
    }

    retries=SDIO_TIMEOUT_ACMD41/10;
    while (retries--)
    {
        ret = sdioIssueCmd(cardInfo->index, MMC_APP_CMD, 0x00000000, 0,MMC_RSP_R1);
        if (ret)
        {
#ifdef DEBUG_PRINT
            printf("Cmd55 error!\n");
#endif
            continue;
        }

        ret = sdioIssueCmd(cardInfo->index, SD_APP_OP_COND, hcs | 0x00300000, 0,MMC_RSP_R3);
        if (ret)
        {
#ifdef DEBUG_PRINT
            printf("cmd41 error!\n");
#endif
            continue;
        }

        if ((resp[cardInfo->index][0] >> 24) & (1 << 7))
        {
            if(resp[cardInfo->index][0]>>24 & (1<<6))
            {
                cardInfo->type=CARDTYPE_SDHC;
                cardInfo->highCapacity=1;
            }
            retries = -2;
            break;
        }
        GD_TIMER_Delay(10);
    }
    return retries;
}
/*!
********************************************************************************
**sdio init sd card
**
********************************************************************************
*/
static GERR GD_SDIO_CardInit(U32 index)
{
    int ret=0;
    sdioBlockT *cardInfo = &sdioHandleArray[index].devicePtr;
    ret = GD_SDIO_SDHCInit(cardInfo);
    if(ret != -1)
    {
#ifdef DEBUG_PRINT
        printf("this is sdhc card\n");
#endif
    }
    else
    {
        if(GD_SDIO_SDInit(cardInfo)== -1)
        {
#ifdef DEBUG_PRINT
            printf("no card info\n");
#endif
            return GD_ERR_SDIO_NO_CARD;
        }
        else
        {
#ifdef DEBUG_PRINT
            printf("this is sd card\n");
#endif
        }
    }

    ret=GD_SDIO_GetCid(cardInfo);
    if(ret)
    {
#ifdef DEBUG_PRINT
        printf("get cid failed!\n");
#endif
        return GD_ERR_SDIO_CARD_INIT_FAILED;
    }

    ret=GD_SDIO_GetRca(cardInfo);
    if(ret)
    {
#ifdef DEBUG_PRINT
        printf("get relative card address failed!\n");
#endif
        return GD_ERR_SDIO_CARD_INIT_FAILED;
    }

    ret=GD_SDIO_GetCsd(cardInfo);
    if(ret)
    {
#ifdef DEBUG_PRINT
        printf("sd get csd register failed\n");
#endif
        return GD_ERR_SDIO_CARD_INIT_FAILED;
    }

    ret = sdioIssueCmd(cardInfo->index, MMC_SELECT_CARD, cardInfo->rca, 0, MMC_RSP_R1);
    if(ret)
    {
#ifdef DEBUG_PRINT
        printf("select card failed!\n");
#endif
        return GD_ERR_SDIO_CARD_INIT_FAILED;
    }

    ret=GD_SDIO_GetScr(cardInfo);
    if(ret)
    {
#ifdef DEBUG_PRINT
        printf("sd get scr register failed\n");
#endif
        return GD_ERR_SDIO_CARD_INIT_FAILED;
    }
    sdioSetHostctlSpeed(cardInfo->index,0);
    sdioClockOnOff(cardInfo->index,0);
    sdioSetClockDiv(cardInfo->index,1);
#if SWITCH_HIGH_SPEED
    ret=GD_SDIO_EnableHSpeed(cardInfo);
    if(ret==GD_OK)
    {
#ifdef DEBUG_PRINT
        printf("switch high speed ok\n");
#endif
    }
#endif

#if SWITCH_4BIT_MODE
    ret= GD_SDIO_EnableIO4(cardInfo);
    if(ret==GD_OK)
    {
#ifdef DEBUG_PRINT
        printf("sd card set 4 bit mode ok\n");
#endif
    }
#endif

#if SWITCH_1BIT_MODE
    ret= GD_SDIO_EnableIO1(cardInfo);
    if(ret==GD_OK)
    {
#ifdef DEBUG_PRINT
        printf("sd card set 1 bit mode ok\n");
#endif
    }
#endif

    if(cardInfo->inhighspeed==1)
    {
        cardInfo->tran_speed=50000000;
        sdioSetHostctlSpeed(cardInfo->index,1);
        sdioClockOnOff(cardInfo->index,0);
        sdioSetClockDiv(cardInfo->index,SDIO_CLK_DIV);
    }
    else
    {
        sdioSetHostctlSpeed(cardInfo->index,0);
        sdioClockOnOff(cardInfo->index,0);
        sdioSetClockDiv(cardInfo->index,1);
    }
    return GD_OK;
}

static void sdioExecuteHandleCallback( U32 index, U32 comState)
{
    if( sdioHandleArray[index].inUse &&
        sdioHandleArray[index].openParams.notifyFunc )
    {
       sdioHandleArray[index].openParams.notifyFunc( index, comState, sdioHandleArray[index].openParams.notifyFuncOptPtr);
    }
}



/*!
*****************************************************************************
**
** The function is activated when an card status is changed .
** The operating environment has to call it as soon
** as the related ISR has been processed.
**
*****************************************************************************
*/
static GERR GD_SDIO_CardBsr(U32 index, U32 privData)
{
    if(GD_SDIO_GetSdState(index)==SDIO_COM_STATE_CARD_DETECTION)
    {
        if((GH_SDIO_get_PresentStateReg(index) & 0x00070000)==0x00070000)
        {
            if(GD_SDIO_CardInit(index))
            {
                GD_SDIO_Rest(index);
                return GD_ERR_SDIO_CARD_INIT_FAILED;
            }
			GD_SDIO_SetSdState(index, SDIO_COM_STATE_CARD_READY);
            return GD_OK;
        }

		GD_SDIO_SetSdState(index, SDIO_COM_STATE_CARD_REMOVED);
        return GD_ERR_SDIO_NO_CARD;
    }

    if((GD_SDIO_GetSdState(index)==SDIO_COM_STATE_CARD_REMOVED) && privData)
    {
        GD_SDIO_Rest(index);
    }

    return GD_OK;
}

static int GD_SDIO_CheckStatus(sdioBlockT* cardInfo,int timeout)
{
    int err, retries = 10;
    do{
        err = sdioIssueCmd(cardInfo->index, MMC_SEND_STATUS, cardInfo->rca, 0, MMC_RSP_R1);
        if (!err)
        {
            if ((resp[cardInfo->index][0] & 0x1<<8) && (resp[cardInfo->index][0] & 0xf<<9) != 0x7<<9)
            {
                break;
            }
            else if (resp[cardInfo->index][0] & ~0x0206BF7F)
            {
#ifdef DEBUG_PRINT
                GM_Printf("Status Error: 0x%08X\n",resp[cardInfo->index][0]);
#endif
                return -1;
            }
        }
        else if (--retries < 0)
        {
            return err;
        }

        GD_TIMER_Delay(10);
    } while (timeout--);

    if (timeout <= 0)
    {
#ifdef DEBUG_PRINT
        GM_Printf("Timeout waiting card ready\n");
#endif
        return -1;
    }
    return GD_OK;
}

/*
*******************************************************************************
**
** sdio write blocks/block
**
*******************************************************************************
*/
static int GD_SDIO_WriteBlocks(sdioBlockT *cardInfo, U32 isusedma,void *scr, U32  start,U32  blkcnt)
{
    U8 cmdidx;
    U32 cmdarg=0,multblk=0;
    U8 *soucre=(U8 *)scr;
    int dir_write=0;
    U32 cmd=0,dmaen=0;

    if (blkcnt > 1)
    {
        cmdidx = MMC_WRITE_MULTIPLE_BLOCK;
        multblk=1;
    }
    else
    {
        cmdidx = MMC_WRITE_BLOCK;
        multblk=0;
    }

    if (cardInfo->highCapacity)
    {
        cmdarg = start;
    }
    else
    {
        cmdarg = start * cardInfo->write_bl_len;
    }

#if  SDIO_PRE_ERASE
    if(cmdidx==MMC_WRITE_MULTIPLE_BLOCK)
    {
        if(sdioIssueCmd(cardInfo->index, MMC_APP_CMD,cardInfo->rca,0, MMC_RSP_R1))
        {
                return GD_ERR_SDIO_CMD_FAILED;
        }
        else
        {
            if(sdioIssueCmd(cardInfo->index,MMC_SET_BLOCK_COUNT,blkcnt,0,MMC_RSP_R1))
                return GD_ERR_SDIO_CMD_FAILED;
        }
    }
#endif

    if(isusedma)
    {
        sdioSetSystemAddressReg(cardInfo->index,(U32 )soucre);
        dmaen=1;
        g_buffer=(U8 *)scr;
    }
    else
    {
        g_block_size=cardInfo->write_bl_len;
        g_buffer=(U8 *)scr;
        dmaen=0;
    }

    sdioSetBlkSizeRegister(cardInfo->index,SD_DEFAULT_BOUNDARY_ARG,cardInfo->write_bl_len);
    sdioSetBlkCntRegister(cardInfo->index,blkcnt);

    if(cmdidx==MMC_WRITE_MULTIPLE_BLOCK)
    {
        cmd=sdioSetTraModeRegister(cardInfo->index,multblk,dir_write,SDIO_AUTO_CMD12,multblk,dmaen);
        cmd |=cmdidx;
    }
    else
    {
        cmd=sdioSetTraModeRegister(cardInfo->index,multblk,dir_write,0,multblk,dmaen);
        cmd |=cmdidx;
    }

    if(sdioIssueCmd(cardInfo->index,cmd,cmdarg,1,MMC_RSP_R1)== GD_OK)
    {
        while(g_transferStatus !=SDIO_ERR_CMD &&
              g_transferStatus != SDIO_TRANSFER_COMPLETE)
        {

			if(GD_SDIO_GetSdState(cardInfo->index) == SDIO_COM_STATE_CARD_REMOVED)
			{

				printf("\n GD_SDIO_WriteBlocks failed in card removed status !\n");
				return -1;
			}

			rt_thread_yield();
			//msleep(1);
        }
        g_transferStatus=SDIO_WAIT;
    }
    else
    {
#ifdef DEBUG_PRINT
        printf("write send cmd failed\n");
#endif
        return -1;
    }

    if (blkcnt > 1 && SDIO_AUTO_CMD12==0)
    {
        if(sdioIssueCmd(cardInfo->index,MMC_STOP_TRANSMISSION, 0, 0, MMC_RSP_R1B)==GD_OK)
        {
#if 0
            while(g_transferStatus !=SDIO_ERR_CMD &&
                  g_transferStatus != SDIO_TRANSFER_COMPLETE)
            {
                GD_SDIO_Rsponse();
            }
            g_transferStatus=SDIO_WAIT;
#endif
        }
        else
        {
#ifdef DEBUG_PRINT
            printf("mmc fail to send stop cmd\n");
#endif
            return 0;
        }

    }

    if (GD_SDIO_CheckStatus(cardInfo,1000))
    {
        return -4;
    }
    return blkcnt;
}

/*!
********************************************************************************
**
** \brief Writes sdio card data
**
** This function writes data to the sd card from the given data buffer.
**
** \param handle  The handle describing an opened sd card
** \param startblk  The sd card block address to start writing at.
** \param buffer  The adress of a data buffer where to write data from
** \param blkcount  The number of block count  to write into the sdio card
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the  parameter is invaild
** - GD_ERR_SDIO_WRITE_FAILED if failed to write.
** - GD_OK if successfull
**
** \note if wo use dma to write blocks .  buffer  should be a Physical Address.
**
********************************************************************************
*/
GERR GD_SDIO_WriteSector(sdioHandleT* sdioHandle, U32 startblk, void* buffer, U32 blkcount)
{
    int ret=0;
    U32 cur, blocks_todo = blkcount;
    U8 *source = (U8 *)buffer;
    U32 *dma_buf = dma_buffer;

    sdioBlockT *cardInfo = &sdioHandle->devicePtr;
    //dma_buf = (U32 *)(((U32)dma_buf + 0x10000)&0xFFFF0000);

    if (blkcount <=0)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    if ((startblk + blkcount) > cardInfo->sectorcount)
    {
#ifdef DEBUG_PRINT
        printf("bad  arg!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    if(source==NULL)
    {
#ifdef DEBUG_PRINT
        printf("bad  arg!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    ret=GD_SDIO_HandleCheck( sdioHandle );
    if(ret!=GD_OK)
    {
        return     GD_ERR_INVALID_HANDLE;
    }
    if(sdioIssueCmd(cardInfo->index, MMC_SET_BLOCKLEN, cardInfo->write_bl_len, 0, MMC_RSP_R1))
    {
#ifdef DEBUG_PRINT
        printf("set block size 512 failed!\n");
#endif
        return GD_ERR_SDIO_SET_BLOCK_SIZE;
    }

    do{
        cur = (blocks_todo > cardInfo->maxTransferBlk) ?  cardInfo->maxTransferBlk : blocks_todo;

        if(sdioHandle->openParams.isUseDmaWay)
        {
            memcpy(dma_buf, source, cur*cardInfo->write_bl_len);
            ret=GD_SDIO_WriteBlocks(cardInfo,sdioHandle->openParams.isUseDmaWay,dma_buf,startblk, cur);
        }
        else
        {
            ret=GD_SDIO_WriteBlocks(cardInfo,sdioHandle->openParams.isUseDmaWay,source,startblk, cur);
        }
        if(ret!= cur)
        {
            return GD_ERR_SDIO_WRITE_FAILED;
        }

        blocks_todo -= cur;
        startblk += cur;
        source += cur * cardInfo->write_bl_len;

    } while (blocks_todo > 0);

    return GD_OK;
}

/*!
********************************************************************************
**sdio read Block/Blocks
**
********************************************************************************
*/
static GERR GD_SDIO_ReadBlocks(sdioBlockT *cardInfo,U32 isusedma,void *dst, U32  start,U32  blkcnt)
{
    U8 cmdidx;
    U32 cmdarg=0,dmaen=0,multblk=0;
    int dir_read=1;
    U8 *destination=(U8 *)dst;
    U32 cmd=0;

    if (blkcnt > 1)
    {
        cmdidx = MMC_READ_MULTIPLE_BLOCK;
        multblk=1;
    }
    else
    {
        multblk=0;
        cmdidx = MMC_READ_SINGLE_BLOCK;        /*read single block*/
    }

    if (cardInfo->highCapacity)
    {
        cmdarg = start;
    }
    else
    {
        cmdarg = start * cardInfo->read_bl_len;
    }

    if(GD_SDIO_CheckStatus(cardInfo,1000))
    {
        return GD_ERR_SDIO_READ_FAILED;
    }

    if(isusedma)
    {
        sdioSetSystemAddressReg(cardInfo->index,(U32)destination);
        dmaen=1;
        g_buffer=(U8 *)dst;
    }
    else
    {
        g_block_size=cardInfo->read_bl_len;
        g_buffer=(U8 *)dst;
        dmaen=0;
    }

    sdioSetBlkSizeRegister(cardInfo->index,SD_DEFAULT_BOUNDARY_ARG,cardInfo->read_bl_len);
    sdioSetBlkCntRegister(cardInfo->index,blkcnt);

    if(cmdidx==MMC_READ_MULTIPLE_BLOCK)
    {
        cmd=sdioSetTraModeRegister(cardInfo->index,multblk,dir_read,SDIO_AUTO_CMD12,multblk,dmaen);
        cmd |=cmdidx;
    }
    else
    {
        cmd=sdioSetTraModeRegister(cardInfo->index,multblk,dir_read,0,multblk,dmaen);
        cmd |=cmdidx;
    }

    if(sdioIssueCmd(cardInfo->index, cmd,cmdarg,1,MMC_RSP_R1) == GD_OK)
    {
        while(g_transferStatus != SDIO_ERR_CMD &&
              g_transferStatus != SDIO_TRANSFER_COMPLETE)
        {
			if(GD_SDIO_GetSdState(cardInfo->index) == SDIO_COM_STATE_CARD_REMOVED)
			{

				printf("\n GD_SDIO_ReadBlocks failed in card removed status !\n");
				return GD_ERR_SDIO_READ_FAILED;
			}

			rt_thread_yield();
			//msleep(1);
        }
        g_transferStatus=SDIO_WAIT;
    }
    else
    {
        return GD_ERR_SDIO_CMD_FAILED;
    }

    if (blkcnt > 1 && SDIO_AUTO_CMD12==0)
    {
        if(sdioIssueCmd(cardInfo->index, MMC_STOP_TRANSMISSION, 0, 0, MMC_RSP_R1B)== GD_OK)
        {
#if 0
              while(g_transferStatus !=SDIO_ERR_CMD &&
                    g_transferStatus != SDIO_TRANSFER_COMPLETE)
              {
                   GD_SDIO_Rsponse();
              }
              g_transferStatus=SDIO_WAIT;
#endif

        }
        else
        {
            return GD_ERR_SDIO_CMD_FAILED;
        }
    }
    return blkcnt;
}

/*!
********************************************************************************
**
** \brief Reads sdio card date
**
** This function reads data from the sd card into the given data buffer.
**
** \param handle  The handle describing an opened sd card  device
** \param stratblk  The blocks address to start reading at.
** \param buffer      The adress of a data buffer where to store the read data
** \param blkcount  wo want to read how many blocks
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the  parameter is invaild
** - GD_ERR_SDIO_SET_BLOCK_SIZE  if wo set card block count failed
** - GD_ERR_SDIO_READ_FAILED  if wo read block failed
** - GD_OK if successfull
**
** \note if wo use dma to read blocks .  buffer  should be a Physical Address.
********************************************************************************
*/
GERR GD_SDIO_ReadSector(sdioHandleT *sdiohandle, U32 startblk, void* buffer, U32 blkcount)
{
    int gerr;
    U32 cur, blocks_todo = blkcount;
    U8 *des=(U8 *)buffer;
    U32 *dma_buf = dma_buffer;
	int usedma = sdiohandle->openParams.isUseDmaWay;

    sdioBlockT  *cardInfo   = &sdiohandle->devicePtr;
    //dma_buf = (U32 *)(((U32)dma_buf + 0x10000)&0xFFFF0000);

    if (blkcount <= 0)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    if ((startblk + blkcount - 1) > cardInfo->sectorcount)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    if(des==NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    gerr=GD_SDIO_HandleCheck( sdiohandle );
    if(gerr!=GD_OK)
    {
        return  GD_ERR_INVALID_HANDLE;
    }

    if(sdioIssueCmd(cardInfo->index,MMC_SET_BLOCKLEN, cardInfo->read_bl_len, 0, MMC_RSP_R1))
    {
        return GD_ERR_SDIO_SET_BLOCK_SIZE;
    }

    do{
        cur = (blocks_todo > cardInfo->maxTransferBlk) ?  cardInfo->maxTransferBlk: blocks_todo;

        if(usedma)
        {
            if(GD_SDIO_ReadBlocks(cardInfo,usedma,dma_buf, startblk, cur) != cur)
            {
                return GD_ERR_SDIO_READ_FAILED;
            }
            memcpy(des, dma_buf, cur*cardInfo->read_bl_len);
        }
        else
        {
            if(GD_SDIO_ReadBlocks(cardInfo,usedma,des, startblk, cur) != cur)
            {
                return GD_ERR_SDIO_READ_FAILED;
            }
        }
        blocks_todo -= cur;
        startblk += cur;
        des += cur * cardInfo->read_bl_len;
    } while (blocks_todo > 0);

	//printf_buff(__FUNCTION__, buffer);

    return GD_OK;
}

#if 1
void GD_SDIO_SetSdioError( int uSdioError)
{
    g_sdioError = uSdioError;
}

void GD_SDIO_SetcmdStatus( int uCmdStatus)
{
    g_cmdStatus = uCmdStatus;
}

void GD_SDIO_SetTranStatus( int uTranStatus)
{
    g_transferStatus = uTranStatus;
}

void GD_SDIO_SetSdState( U32 index, U32 uSdioState)
{
	if(index < 0 || index >= SDIO_HANDLE_COUNT)
	{
		return;
	}
	if(sdioComState[index] == uSdioState)
	{
		return;
	}
    sdioComState[index] = uSdioState;
	sdioExecuteHandleCallback(index, uSdioState);
}

U32 GD_SDIO_GetSdState( U32 index)
{
	if(index < 0 || index >= SDIO_HANDLE_COUNT)
	{
		return SDIO_COM_STATE_CARD_REMOVED;
	}
	return sdioComState[index];
}


void GD_SDIO_card_init(void)
{
    int i;
    for(i=0;i<SDIO_HANDLE_COUNT;i++)
    {
        sdioHandleArray[i].inUse=0;
    }
    GD_SDIO_Rest(GD_SDIO0);
#ifdef GK710S
    GD_SDIO_Rest(GD_SDIO1);
#endif
    sdioInitDone=1;
}

/************************************************************
*Function Name : Gd_setInsertState
*
*Description :SD media notify function, be called when SD media change
*
*Input : none
*
*Output :none
*
*Return : none
***************************************************************/
void Gd_setInsertState(GBOOL state)
{
    sdInsertState = state;
    sdChangeState = GTRUE;
}

void Gd_setChangedState(GBOOL state)
{
    sdChangeState = state;
}

GBOOL Gd_GetInsertState(GBOOL *state)
{
    *state = sdInsertState;
    return sdChangeState;
}

#endif

/*!
********************************************************************************
**
** \brief SDIO0 interrupt handle
**
**
********************************************************************************
*/
static GISR1 GD_SDIO_ISR0(void)
{
    U32  index = 0;
    U32  data= 0,i=0;
    U32  bufferpos= 0;
	#ifdef DEBUG_PRINT
    static int ts=0;
	#endif
    void *pdata = NULL;
    U32  irq_status_reg =(GH_SDIO_get_NorIntStaReg(index)| GH_SDIO_get_ErrIntStaReg(index)<<16);
    g_sdioError    = 0;
    for(i=0;i<4;i++)
    {
        resp[index][i]=0;
    }
    //GM_Printf("irq_status_reg:%x\n",irq_status_reg);

    if( irq_status_reg & SDIO_ERROR_IRQ )
    {
#ifdef DEBUG_PRINT
        printf("error irq_status_reg:%x\n",irq_status_reg);
#endif

        if(irq_status_reg & 0x1)
        {
#ifdef DEBUG_PRINT
            printf("cmd complete\n");
#endif
        }
        else if(irq_status_reg & 0x2)
        {
#ifdef DEBUG_PRINT
            printf("transfer complete\n");
#endif
        }

        GH_SDIO_set_NorIntStaReg(index,GH_SDIO_get_NorIntStaReg(index));
        GH_SDIO_set_ErrIntStaReg(index,GH_SDIO_get_ErrIntStaReg(index));
        GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index,1);
        GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index,1);
        g_cmdStatus    = SDIO_ERR_CMD;
        g_transferStatus = SDIO_ERR_CMD;
        g_sdioError    = (irq_status_reg>>16);
#ifdef DEBUG_PRINT
        GM_Printf(" - Error IRQ %x\n", g_sdioError);
#endif

    }
    else if( irq_status_reg & SDIO_IRQ_CMD_COMPLETE )
    {
		//GM_Printf("irq_status_reg:%x\n",irq_status_reg);
        if(GH_SDIO_get_CmdReg_RepTypeSelect(index)==1)
        {
            resp[index][0]=GH_SDIO_get_Resp3Reg(index)<<8 | (GH_SDIO_get_Resp2Reg(index) & 0xff000000)>>24;
            resp[index][1]=GH_SDIO_get_Resp2Reg(index)<<8 | (GH_SDIO_get_Resp1Reg(index) & 0xff000000)>>24;
            resp[index][2]=GH_SDIO_get_Resp1Reg(index)<<8 | (GH_SDIO_get_Resp0Reg(index) & 0xff000000)>>24;
            resp[index][3]=GH_SDIO_get_Resp0Reg(index)<<8;
        }
        else
        {
            resp[index][0]=GH_SDIO_get_Resp0Reg(index);
        }
        g_sdioError     = 0;
        g_cmdStatus    = SDIO_CMD_COMPLETE;
        g_transferStatus=SDIO_WAIT;
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CMD_COMPLETE);
    }
    else if( irq_status_reg & SDIO_IRQ_CARD_REMOVED )
    {
#ifdef DEBUG_PRINT
        printf(" - Card removed IRQ\n");
#endif
        GD_SDIO_Rest(index);
        //GD_SDIO_Close(&sdioHandleArray[index], index);
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_REMOVED);
    }
    else if( irq_status_reg & SDIO_IRQ_CARD_INSERTED )
    {
#ifdef DEBUG_PRINT
        printf(" - Card inserted IRQ\n");
#endif
		GD_SDIO_SetSdState(index, SDIO_COM_STATE_CARD_DETECTION);
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_INSERTED);
    }
    else if( irq_status_reg & SDIO_IRQ_READ_READY )
    {

        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<11))
        {
            return;
        }
        else
        {
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_READ_READY);
            while( bufferpos < g_block_size )
            {
                data = GH_SDIO_get_BufferDataPortReg(index);

                if( g_buffer)
                {
                    pdata=(void *)g_buffer;
                    *(U32 *)pdata = data;
                    g_buffer += 4;
                    bufferpos+=4;
                }
            }
#ifdef DEBUG_PRINT
            printf("read %d \n",ts++);
#endif
        }

    }
    else if( irq_status_reg & SDIO_IRQ_WRITE_READY )
    {
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<10))
        {
            return;
        }
        else
        {
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_WRITE_READY);
            while( bufferpos < g_block_size )
            {
                if( g_buffer )
                {
                    pdata=(void *)g_buffer;
                    GH_SDIO_set_BufferDataPortReg(index, *((U32 *)pdata));
                    g_buffer +=4;
                    bufferpos+=4;
                }
            }
#ifdef DEBUG_PRINT
            GM_Printf("write %d \n",ts++);
#endif
        }
    }
    else if(irq_status_reg & SDIO_IRQ_DMA)
    {
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_DMA);
        g_buffer += SD_DEFAULT_BOUNDARY_SIZE;
        sdioSetSystemAddressReg(index,(U32)g_buffer);
#ifdef DEBUG_PRINT
        printf("dma int %d \n",ts++);
#endif
    }
    else if( irq_status_reg & SDIO_IRQ_TRANSFER_COMPLETE )
    {
        g_sdioError        = 0;
        g_transferStatus    = SDIO_TRANSFER_COMPLETE;
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_TRANSFER_COMPLETE);
		#ifdef DEBUG_PRINT
        ts=0;
		#endif
    }
}

/*!
********************************************************************************
**
** \brief SDIO1 interrupt handle
**
**
********************************************************************************
*/
#ifdef Gk7101S
static GISR1 GD_SDIO_ISR1(void)
{
    U32  index = 1;
    U32  data= 0,i=0;
    U32  bufferpos= 0;
    U32  irq_status_reg =(GH_SDIO_get_NorIntStaReg(index)| GH_SDIO_get_ErrIntStaReg(index)<<16);
    static int ts=0;
    void *pdata;
    U32  command = 0;
    g_sdioError    = 0;
    for(i=0;i<4;i++)
    {
        resp[index][i]=0;
    }

    if( irq_status_reg & SDIO_ERROR_IRQ )
    {
#ifdef DEBUG_PRINT
        printf("error irq_status_reg:%x\n",irq_status_reg);
#endif

        if(irq_status_reg & 0x1)
        {
#ifdef DEBUG_PRINT
            printf("cmd complete\n");
#endif
        }
        else if(irq_status_reg & 0x2)
        {
#ifdef DEBUG_PRINT
            printf("transfer complete\n");
#endif
        }

        GH_SDIO_set_NorIntStaReg(index,GH_SDIO_get_NorIntStaReg(index));
        GH_SDIO_set_ErrIntStaReg(index,GH_SDIO_get_ErrIntStaReg(index));
        GH_SDIO_set_Control01Reg_SoftwareResetDatLine(index,1);
        GH_SDIO_set_Control01Reg_SoftwareResetCmdLine(index,1);
        g_cmdStatus    = SDIO_ERR_CMD;
        g_transferStatus = SDIO_ERR_CMD;
        g_sdioError    = (irq_status_reg>>16);
#ifdef DEBUG_PRINT
        printf(" - Error IRQ %x\n", g_sdioError);
#endif

    }
    else if( irq_status_reg & SDIO_IRQ_CMD_COMPLETE )
    {

        if(GH_SDIO_get_CmdReg_RepTypeSelect(index)==1)
        {
            resp[index][0]=GH_SDIO_get_Resp3Reg(index)<<8 | (GH_SDIO_get_Resp2Reg(index) & 0xff000000)>>24;
            resp[index][1]=GH_SDIO_get_Resp2Reg(index)<<8 | (GH_SDIO_get_Resp1Reg(index) & 0xff000000)>>24;
            resp[index][2]=GH_SDIO_get_Resp1Reg(index)<<8 | (GH_SDIO_get_Resp0Reg(index) & 0xff000000)>>24;
            resp[index][3]=GH_SDIO_get_Resp0Reg(index)<<8;
        }
        else
        {
            resp[index][0]=GH_SDIO_get_Resp0Reg(index);
        }
        g_sdioError     = 0;
        g_cmdStatus    = SDIO_CMD_COMPLETE;
        g_transferStatus=SDIO_WAIT;
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CMD_COMPLETE);
    }
    else if( irq_status_reg & SDIO_IRQ_CARD_REMOVED )
    {
#ifdef DEBUG_PRINT
        printf(" - Card removed IRQ\n");
#endif
        GD_SDIO_Rest(index);
        GD_SDIO_Close(&sdioHandleArray[index], index);
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_REMOVED);
    }
    else if( irq_status_reg & SDIO_IRQ_CARD_INSERTED )
    {
#ifdef DEBUG_PRINT
        printf(" - Card inserted IRQ\n");
#endif
		GD_SDIO_SetSdState(index, SDIO_COM_STATE_CARD_DETECTION);
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_CARD_INSERTED);
    }
    else if( irq_status_reg & SDIO_IRQ_READ_READY )
    {

        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<11))
        {
            return;
        }
        else
        {
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_READ_READY);
            while( bufferpos < g_block_size )
            {
                data = GH_SDIO_get_BufferDataPortReg(index);

                if( g_buffer)
                {
                    pdata=(void *)g_buffer;
                    *(U32 *)pdata = data;
                    g_buffer += 4;
                    bufferpos+=4;
                }
            }
#ifdef DEBUG_PRINT
            printf("read %d \n",ts++);
#endif
        }

    }
    else if( irq_status_reg & SDIO_IRQ_WRITE_READY )
    {
        if (!(GH_SDIO_get_PresentStateReg(index) & 0x1<<10))
        {
            return;
        }
        else
        {
            GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_WRITE_READY);
            while( bufferpos < g_block_size )
            {
                if( g_buffer )
                {
                    pdata=(void *)g_buffer;
                    GH_SDIO_set_BufferDataPortReg(index, *((U32 *)pdata));
                    g_buffer +=4;
                    bufferpos+=4;
                }
            }
#ifdef DEBUG_PRINT
            printf("write %d \n",ts++);
#endif
        }
    }
    else if(irq_status_reg & SDIO_IRQ_DMA)
    {
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_DMA);
        g_buffer += SD_DEFAULT_BOUNDARY_SIZE;
        sdioSetSystemAddressReg(index,(U32)g_buffer);
#ifdef DEBUG_PRINT
        printf("dma int %d \n",ts++);
#endif
    }
    else if( irq_status_reg & SDIO_IRQ_TRANSFER_COMPLETE )
    {
        g_sdioError        = 0;
        g_transferStatus    = SDIO_TRANSFER_COMPLETE;
        GH_SDIO_set_NorIntStaReg(index, SDIO_IRQ_TRANSFER_COMPLETE);
        ts=0;
    }
}
#endif
/*!
********************************************************************************
**
** \brief Initialize the SDIO driver
**
** Initializes the SDIO interrupt and  Reset SDIO card.
**
** \return
** - GD_OK if successfull
** -else GD_INT_Open failed
**
********************************************************************************
*/

GERR GD_SDIO_Init(GD_SDIO_OpenParamsT* openParamsP, U32 index)
{
    int i;
    GERR                     ret;
    
    GD_INT_OPEN_PARAMS_S     intParams0;
    GD_INT_OPEN_PARAMS_S     intParams1;
#ifdef GK7101S
    GD_INT_OPEN_PARAMS_S     intParams2;
    GD_INT_OPEN_PARAMS_S     intParams3;
#endif
    // don't config gpio at here, please use include/GK7101/BOARD_XXX.h.
    // GD_SDIO_GpioConfig();
    /*open the sdio control interrupt*/
	if(index == GD_SDIO0)
	{
		intParams0.type           = (S8)GD_INT_SD_CONTROLLER_IRQ;
	    intParams0.sensitivity    = GD_INT_LEVEL_HIGH;
	    intParams0.active         = GD_INT_INVERT_IRQ;
	    intParams0.priority       = GD_INT_MID_PRIORITY;
	    intParams0.isrFct.lowPrio = openParamsP->irqFunc;
	    ret = GD_INT_Open(&intParams0, &sdioHandle0);
	    if(ret != GD_OK)
	    {
	        return GD_ERR_SDIO_INT_ERR;
	    }
	    //GD_INT_SetHandler(intParams0.type, GD_SDIO_ISR);
	    GD_INT_Enable(&sdioHandle0,GD_INT_ENABLED);
	    /*open the sdio detec interrupt*/
	    intParams1.type           = (S8)GD_INT_SD_CARD_DETECT_IRQ;
	    intParams1.sensitivity    = GD_INT_BOTH_EDGES;
	    intParams1.active         = GD_INT_INVERT_IRQ;
	    intParams1.priority       = GD_INT_MID_PRIORITY;
	    intParams1.isrFct.lowPrio = openParamsP->irqFunc;
	    ret = GD_INT_Open(&intParams1, &sdioHandle1);
	    if(ret != GD_OK)
	    {
	        return GD_ERR_SDIO_INT_ERR;
	    }
	    //GD_INT_SetHandler(intParams1.type, GD_SDIO_ISR);
	    GD_INT_Enable(&sdioHandle1,GD_INT_ENABLED);
	    if(ret != GD_OK)
	    {
	        return GD_ERR_SDIO_INT_ERR;
	    }
		openParamsP->resetFunc(GD_SDIO0);
	}
	#ifdef GK7101S
	else
	{


	    intParams2.type           = (S8)GD_INT_SD2_CONTROLLER_IRQ;
	    intParams2.sensitivity    = GD_INT_LEVEL_HIGH;
	    intParams2.active         = GD_INT_INVERT_IRQ;
	    intParams2.priority       = GD_INT_MID_PRIORITY;
	    intParams2.isrFct.lowPrio = openParamsP->irqFunc;
	    ret = GD_INT_Open(&intParams2, &sdioHandle2);
	    if(ret != GD_OK)
	    {
	        return GD_ERR_SDIO_INT_ERR;
	    }
	    //GD_INT_SetHandler(intParams0.type, GD_SDIO_ISR);
	    GD_INT_Enable(&sdioHandle2,GD_INT_ENABLED);
	    /*open the sdio detec interrupt*/
	    intParams3.type           = (S8)GD_INT_SD2_CARD_DETECT_IRQ;
	    intParams3.sensitivity    = GD_INT_BOTH_EDGES;
	    intParams3.active         = GD_INT_INVERT_IRQ;
	    intParams3.priority       = GD_INT_MID_PRIORITY;
	    intParams3.isrFct.lowPrio = openParamsP->irqFunc;
	    ret = GD_INT_Open(&intParams3, &sdioHandle3);
	    if(ret != GD_OK)
	    {
	        return GD_ERR_SDIO_INT_ERR;
	    }
	    GD_INT_Enable(&sdioHandle3,GD_INT_ENABLED);

	    for(i=0;i<SDIO_HANDLE_COUNT;i++)
	    {
	        sdioHandleArray[i].inUse=0;
	    }

	    openParamsP->resetFunc(GD_SDIO1);
	}
	#endif
    return GD_OK;
}


/*!
********************************************************************************
**sido exit
**
********************************************************************************
*/
GERR GD_SDIO_Exit(sdioHandleT*sdioHandle, U32 index)
{
    if(sdioInitDone==0)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if(sdioHandle->inUse==1)
    {
        GD_SDIO_Close(sdioHandle, index);
    }
    return GD_OK;
}

/*!
********************************************************************************
**
** \brief Opens sdio card
**
** This function opens a new instance of the sd card driver for application use.
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle or openParamsp parameter points to 0
** - GD_ERR_OUT_OF_MEMORY if all handle are already in use
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SDIO_Open(GD_SDIO_OpenParamsT* openParamsP, sdioHandleT *pHandle, U32 index)
{
    sdioHandleT *sdioptr=NULL;
    GERR ret;
    if(openParamsP==NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    if(openParamsP->isUseDmaWay !=0 && openParamsP->isUseDmaWay !=1)
    {
        return GD_ERR_BAD_PARAMETER;
    }

	if(openParamsP->type == GAPI_SDIO_TRANSFER_TYPE_WIFI)
	{
		ret = GD_SDIO_Init(openParamsP, index);
		sdioptr=sdioAllocateHandle(index);
		if(sdioptr==NULL || sdioptr->inUse==0)
	    {
	        return GD_ERR_OUT_OF_MEMORY;
	    }
		wifiIndex = index;
		
		return ret;
	}
	else
	{
		if(index == GD_SDIO0)
			openParamsP->irqFunc = GD_SDIO_ISR0;
		#ifdef Gk7101S
		else
			openParamsP->irqFunc = GD_SDIO_ISR1;
		#endif
		openParamsP->resetFunc = GD_SDIO_Rest;
		GD_SDIO_Init(openParamsP, index);
	    sdioptr=sdioAllocateHandle(index);
	    if(sdioptr==NULL || sdioptr->inUse==0)
	    {
	        return GD_ERR_OUT_OF_MEMORY;
	    }

	    memcpy(&(sdioptr->openParams),openParamsP,sizeof(GD_SDIO_OpenParamsT));

	    if((GD_SDIO_GetSdState(index) !=SDIO_COM_STATE_CARD_READY) && (GH_SDIO_get_PresentStateReg(index) & 0x00070000))
	    {
			GD_SDIO_SetSdState(index, SDIO_COM_STATE_CARD_DETECTION);

	        ret=GD_SDIO_CardBsr(index, 1);
	        if(ret!= GD_OK)
	        {
	            return ret;
	        }
	    }
	}

    //pHandle=sdioptr;
    memcpy((void*)pHandle,(void*)sdioptr,sizeof(sdioHandleT));
    return GD_OK;

}

/*!
********************************************************************************
**release handle
**
********************************************************************************
*/
GERR GD_SDIO_Close(sdioHandleT *sdiohandle, U32 index)
{
    GERR    ret;

    if(sdiohandle==NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
	
	if(wifiIndex == index)//only close sdio wifi interrupt.
	{
		 wifiIndex = 0xFF;
		 
		if(index == GD_SDIO0)
		{
			GD_INT_Close(&sdioHandle0);
			GD_INT_Close(&sdioHandle1);
		}
		#ifdef GK7101S
		else
		{
			GD_INT_Close(&sdioHandle2);
			GD_INT_Close(&sdioHandle3);
		}
		#endif
	}
	
    ret=GD_SDIO_HandleCheck(sdiohandle);
    if(GD_OK!=ret)
    {
        return ret;
    }
    sdiohandle->inUse=0;

    return GD_OK;
}


/*!
********************************************************************************
**sdio get card status
**
********************************************************************************
*/
static U32 GD_SDIO_IsProgram(sdioBlockT*cardInfo)
{
    int err;
    err = sdioIssueCmd(cardInfo->index,MMC_SEND_STATUS, cardInfo->rca, 0, MMC_RSP_R1);
    if(err)
    {
        return GD_ERR_SDIO_CMD_FAILED;
    }
    else
    {
        return GD_OK;
    }
}


/*!
********************************************************************************
**
** \brief erase sdio card block
**
** This function erase sd blocks.
**
** \param handle  The handle describing an opened sd card  device
** \param strat     The blocks address to start erase at.
** \param blkcnt   wo want to erase how many blocks
**
**
** \return
** - GD_ERR_SDIO_CMD_FAILED  if sending CMD failed
** - GD_OK if successfull
**
********************************************************************************
*/
static U32 GD_SDIO_EarseBlocks(sdioBlockT*cardInfo,U32 start, U32 blkcnt)
{
    U32  end;

    if (cardInfo->highCapacity)
    {
        end = start + blkcnt - 1;
    }
    else
    {
        end = (start + blkcnt -1) * cardInfo->read_bl_len;
        start *= cardInfo->read_bl_len;
    }

    if(sdioIssueCmd(cardInfo->index,SD_CMD_ERASE_WR_BLK_START,start,0,MMC_RSP_R1))
    {
        return GD_ERR_SDIO_CMD_FAILED;
    }

    if(sdioIssueCmd(cardInfo->index,SD_CMD_ERASE_WR_BLK_END,end, 0,MMC_RSP_R1))
    {
        return GD_ERR_SDIO_CMD_FAILED;
    }
    if(sdioIssueCmd(cardInfo->index,MMC_ERASE, 0x0000,0,MMC_RSP_R1B))
    {
        return GD_ERR_SDIO_CMD_FAILED;
    }

    return GD_OK;
}

/*!
********************************************************************************
**
** \brief erase sdio card block
**
** This function erase sd blocks.
**
** \param handle  The handle describing an opened sd card  device
** \param strat     The blocks address to start erase at.
** \param blkcnt   wo want to erase how many blocks
**
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the  parameter is invaild
** - GD_ERR_SDIO_SET_BLOCK_SIZE  if wo set card block count failed
** - GD_ERR_SDIO_CMD_NO_SUPPORTED  if wo can't support
** - GD_ERR_SDIO_ERASE_FAILED  if wo erase block failed
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SDIO_EraseSector(sdioHandleT* sdioHandle, U32 start, U32 blkcnt)
{
    int  ret = 0;
    U32  blk = 0, blk_r = 0;
    sdioBlockT* cardInfo = &sdioHandle->devicePtr;

    if((cardInfo->csd[1]>>20 & 0x020)==0)
    {
        return GD_ERR_SDIO_CMD_NO_SUPPORTED;
    }

    if(((cardInfo->csd[2]>>14) & 0x1) == 0)
    {
#ifdef DEBUG_PRINT
        printf("card no support block erase \n");
#endif
        return GD_ERR_SDIO_CMD_NO_SUPPORTED;
    }

    ret=GD_SDIO_HandleCheck( sdioHandle );
    if(ret!=GD_OK)
    {
        return    GD_ERR_INVALID_HANDLE;
    }

    if(sdioIssueCmd(cardInfo->index, MMC_SET_BLOCKLEN, cardInfo->read_bl_len, 0, MMC_RSP_R1))
    {
#ifdef DEBUG_PRINT
        printf("sd read set block failed \n");
#endif
        return GD_ERR_SDIO_SET_BLOCK_SIZE;
    }

    ret = GD_SDIO_IsProgram(cardInfo);
    if(ret)
    {
        return  GD_ERR_SDIO_CMD_FAILED;
    }

    if(resp[cardInfo->index][0] & ((U32)0x02000000))
    {
        return GD_ERR_SDIO_CARD_LOCKED;
    }

    while (blk < blkcnt)
    {
        blk_r = ((blkcnt - blk) >= cardInfo->eraseGrpSize) ? cardInfo->eraseGrpSize : (blkcnt - blk);
        ret = GD_SDIO_EarseBlocks(cardInfo,start + blk, blk_r);
        if (ret!=GD_OK)
        {
            return GD_ERR_SDIO_ERASE_FAILED;
        }
        blk += blk_r;

        /* Waiting for the ready status */
        ret = GD_SDIO_IsProgram(cardInfo);
        if(ret!=GD_OK)
        {
            return  GD_ERR_SDIO_ERASE_FAILED;
        }
        while ((ret == GD_OK) && ((( (resp[cardInfo->index][0]>>9) & 0xf ) != 0x00000004)))
        {
            GD_TIMER_Delay(10);
            ret = GD_SDIO_IsProgram(cardInfo);
            if(ret!=GD_OK)
            {
                return  GD_ERR_SDIO_ERASE_FAILED;
            }
        }
    }
    return GD_OK;
}


/*!
********************************************************************************
**
** \brief get sdio card info
**
** This function get  sd info.
**
** \param handle  The handle describing an opened sd card  device
** \param info     The handle describing an opened sd card  info.
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SDIO_GetCardInfo(sdioHandleT* sdioHandle, GD_SDIO_VolumeInfoT *info,U32 index)
{
    int ret;
    int i;

    sdioBlockT * cardInfo   = &sdioHandle->devicePtr;
    ret=GD_SDIO_HandleCheck(sdioHandle);
    if(ret!=GD_OK)
    {
        return    GD_ERR_INVALID_HANDLE;
    }

    if((GD_SDIO_GetSdState(sdioHandle->index) !=SDIO_COM_STATE_CARD_READY))
    {
        info->isConnected=0;
        return GD_OK;
    }
    info->isConnected=1;
    info->mediaType=cardInfo->type;
    info->sectorCount=cardInfo->sectorcount;
    info->sectorSize=cardInfo->read_bl_len;
    info->serialNumber=cardInfo->cidInfo.PSN;
    info->manufacturerID=cardInfo->cidInfo.MID;
    info->applicationID=cardInfo->cidInfo.OID;
    info->productRevision=cardInfo->cidInfo.PRV;

    for(i=0;i<5;i++)
    {
        info->productName[i]=cardInfo->cidInfo.PNM[i];
    }
    return GD_OK;
}

GBOOL GD_SDIO_Get_inserted_flag(U32 index)
{
    return ((GH_SDIO_get_PresentStateReg(index)&0x00070000) == 0x00070000);
}

