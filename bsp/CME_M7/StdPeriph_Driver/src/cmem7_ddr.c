/**
    *****************************************************************************
    * @file     cmem7_ddr.c
    *
    * @brief    CMEM7 DDR source file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_ddr.h"

#define MAX(a, b)   ((a >= b) ? (a) : (b))
#define CAL_DDR3_CL(cl)   ((cl>11)?(((cl-12)<<MR_CL_OFFSET)|0x4):((cl-4)<<MR_CL_OFFSET))

#define CHIP_MIN_CAPACITY  32
#define CHIP_CAPACITY_32MB  CHIP_MIN_CAPACITY
#define CHIP_CAPACITY_64MB (CHIP_CAPACITY_32MB*2)
#define CHIP_CAPACITY_128MB (CHIP_CAPACITY_64MB*2)
#define CHIP_CAPACITY_256MB (CHIP_CAPACITY_128MB*2)
#define CHIP_CAPACITY_512MB (CHIP_CAPACITY_256MB*2)
#define CHIP_CAPACITY_1024MB (CHIP_CAPACITY_512MB*2)

/** @defgroup DDR time
  * @{
  */
  #define POWER_UP_NOP      200*1000        /*ns*//*JEDEC Standard No. 79-2E   page 17   */
  #define PRE_ALL_NOP           400        /*ns*/
  #define POWER_UP_MIN_CK    200
  #define DDR2_TMRD                2            /*JEDEC Standard No. 79-2E   page 80   */
  #define DDR3_TMRD                4            /*JEDEC Standard No. 79-2E   page 80   */
  #define DDR3_TMOD_CK                12            /*JEDEC Standard No. 79-3E   page 171  table 68   */
  #define DDR3_TMOD                15          /*ns*/  /*JEDEC Standard No. 79-3E   page 171  table 68   */
  #define DDR3_TZQINIT_CK                512         /*JEDEC Standard No. 79-3E   page 171  table 68   */
  #define DDR3_TZQINIT                640   /*ns*/      /*JEDEC Standard No. 79-3E   page 171  table 68   */
  #define DDR3_TDLLK_CK                512         /*JEDEC Standard No. 79-3E   page 171  table 68   */
  #define RSTH_NOP      500*1000        /*ns*//*JEDEC Standard No. 79-3E   page 20   */
  #define DDR_TREF      7800 /*ns*/
  /**
  * @}
  */
#ifndef NULL
#define NULL    0
#endif

/** @defgroup DDRC_SW_PROC_CMD
  * @{
  */
#define SW_CMD_NO_PARM        0
#define SW_CMD_DES          0x0       /*des 5'b00000     [31:29]=3'b000           [28:0] DES time cke hold*/
#define SW_CMD_NOP          0x20000000        /*nop 5'b00100     [31:29]=3'b001           [28:0] NOP time cke hold*/
#define SW_CMD_DESCKE         0x40000000       /*descke 5'b01000     [31:29]=3'b010           [28:0] DES time change cke high*/
#define SW_CMD_NOPCKE         0x60000000     /*nopcke 5'b01100     [31:29]=3'b011           [28:0] NOP time change cke high*/
#define SW_CMD_PREA             0x80000000   /*nopcke 5'b10000     [31:27]=5'b10000           */

#define SW_CMD_MR           0x88000000      /*JEDEC Standard No. 79-2E   page 19   */
#define SW_CMD_EMR1             0x88010000  /*JEDEC Standard No. 79-2E   page 19   */
#define SW_CMD_EMR2             0x88020000
#define SW_CMD_EMR3             0x88030000
#define SW_CMD_EMR1_TEST  0x88010004
#define SW_CMD_REF          0x90000000  /*REF 5'b10010     [31:27]=5'b10010       */

#define SW_CMD_RSTH         0xb0000000  /*RSTH 5'b10110    [31:27]=5'b10110       */
#define SW_CMD_ZQCL         0xb8000000  /*ZQCL 5'b10111    [31:27]=5'b10111       */

#define SW_CMD_DLL_EN         0x880103C4
#define SW_CMD_DLL_RST        0x88000953
/**
  * @}
  */
/** @defgroup DDR2  mode register
  * @{
  */
 /*JEDEC Standard    */
#define MR_BURST_LEN_4          0x2
#define MR_BURST_LEN_8          0x3
#define MR_BT_SEQ                    0x0
#define MR_BT_INT                    0x08
#define MR_CL_OFFSET             4
#define MR_TM_NORMAL            0
#define MR_TM_TEST                 0x80
#define MR_DLL_NO                   0
#define MR_DLL_YES                 0x100
#define MR_WR_OFFSET           9
#define MR_PPD_FAST              0x1000
#define MR2_CWL_OFFSET        3
#define MR1_RZQ_4                 0x4
/**
  * @}
  */
const uint8_t DDR2_MODE[BUS_WIDTH_MAX][CHIP_NUM_MAX][CHIP_TYPE_MAX]=
{
    {
        {0x20,0x23,0x28,0x2a,0x30,0x21,0x22,0x29,0x2b,0x31,0xff},/*chip x1*/
        {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}/*chip x2*/
    },/*bus width x8*/

    {
        {0xff,0xff,0xff,0xff,0xff,0x25,0x26,0x2d,0x2f,0x33,0xff},/*chip x1*/
        {0x24,0x27,0x2c,0x2e,0x32,0xff,0xff,0xff,0xff,0xff,0xff}/*chip x2*/
    }/*bus width x16*/
};
const uint8_t DDR3_MODE[BUS_WIDTH_MAX][CHIP_NUM_MAX][CHIP_TYPE_MAX]=
{
    {
        {0xff,0x00,0x01,0x02,0x03,0xff,0x04,0x05,0x06,0x07,0x10},/*chip x1*/
        {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}/*chip x2*/
    },/*bus width x8*/

    {
        {0xff,0xff,0xff,0xff,0xff,0xff,0x0c,0x0d,0x0e,0x0f,0x11},/*chip x1*/
        {0xff,0x08,0x09,0x0a,0x0b,0xff,0xff,0xff,0xff,0xff,0xff}/*chip x2*/
    }/*bus width x16*/
};
const DDR2MEM DDR2PREDEF[] = {
    {
// #define DDR2_400C            4   // sg5E //DDR2-400C CL=4, tCK=5000 ps (dev-brd using)
        /*tCK*/ 5000,
        /*tCL*/ 6,//4,
        /*RCD*/4, /*RP*/4, /*RC*/13, /*RAS*/9, /*WR*/3, /*RRD*/2, /*WTR*/11, /*RTP*/4,
        /*FAW*/10,
    },

    {
// #define DDR2_800D            0   // sg25E //DDR2-800D CL=5, tCK=2500 ps
        /*tCK*/ 2500,
        /*tCL*/ 5, /*RCD*/5, /*RP*/5, /*RC*/24, //from sim model
        /*RAS*/18, /*WR*/6, /*RRD*/4, /*WTR*/11, /*RTP*/5,
        /*FAW*/30, //from sim model
    }, {
// #define DDR2_667C            1   // sg3E //DDR2-667C CL=4, tCK=3000 ps
        /*tCK*/ 3000,
        /*tCL*/ 4, /*RCD*/4, /*RP*/4, /*RC*/19, /*RAS*/15, /*WR*/5, /*RRD*/4, /*WTR*/10, /*RTP*/5,
        /*FAW*/17,
    }, {
// #define DDR2_667D            2   // sg3 //DDR2-667D CL=5, tCK=3000 ps
        /*tCK*/ 3000,
        /*tCL*/ 5, /*RCD*/5, /*RP*/5, /*RC*/20, /*RAS*/15, /*WR*/5, /*RRD*/4, /*WTR*/3, /*RTP*/3,
        /*FAW*/17,
    }, {
// #define DDR2_533C            3   // sg37E //DDR2-533C CL=4, tCK=3750 ps
        /*tCK*/ 3750,
        /*tCL*/ 4, /*RCD*/4, /*RP*/4, /*RC*/16, /*RAS*/12, /*WR*/4, /*RRD*/3, /*WTR*/9, /*RTP*/4,
        /*FAW*/14,
    },
};

const DDR3MEM DDR3PREDEF[] = {
    {
// #define DDR3_400         14  //  Base on DDR3-800D (5-5-5) tCK=5ns
        /*tCK*/ 2500,
        /*tCL*//*9*/ 5, /*WCL*/7/*cwl should be 5 ,but phy has 2 cycles delay.So,wcl should plus the 2 cycles delay.*/ , /*RCD*//*9*/5, /*RAS*//*24*/8, /*RP*//*9*/5, /*RC*//*33*/10, /*RRD*/ 100,
        /*FAW*//*30*/10, /*WR*/5/*10*/, /*RTP*/4, /*ZQCL*/256, /*ZQCS*/64,
    }  ,

    {
// #define DDR3_667         15  //  Base on DDR3-800D (5-5-5) tCK=5ns
        /*tCK*/ 3000,
        /*tCL*//*9*/ 5, /*WCL*/7 /*cwl should be 5 ,but phy has 2 cycles delay.So,wcl should plus the 2 cycles delay.*/ , /*RCD*//*9*/5, /*RAS*//*24*/30, /*RP*//*9*/5, /*RC*//*33*/60, /*RRD*/16,
        /*FAW*//*30*/17, /*WR*/5/*10*/, /*RTP*/4, /*ZQCL*/256, /*ZQCS*/64,
    },

    {
// #define DDR3_2133N           0   // sg093 //DDR3-2133N (14-14-14) tCK=0.938ns
        /*tCK*/ 938,
        /*tCL*/ 14, /*WCL*/10, /*RCD*/14, /*RAS*/36, /*RP*/14, /*RC*/50, /*RRD*/7,
        /*FAW*/38, /*WR*/16, /*RTP*/10, /*ZQCL*/342, /*ZQCS*/86,
    }, {
// #define DDR3_2133M           1   // sg093E //DDR3-2133M (13-13-13) tCK=0.938ns
        /*tCK*/ 938,
        /*tCL*/ 13, /*WCL*/10, /*RCD*/13, /*RAS*/36, /*RP*/13, /*RC*/49, /*RRD*/7,
        /*FAW*/38, /*WR*/16, /*RTP*/10, /*ZQCL*/342, /*ZQCS*/86,
    }, {
// #define DDR3_2133L           2   // sg093F //DDR3-2133L (12-12-12) tCK=0.938ns
        /*tCK*/ 938,
        /*tCL*/ 12, /*WCL*/10, /*RCD*/12, /*RAS*/36, /*RP*/12, /*RC*/48, /*RRD*/7,
        /*FAW*/38, /*WR*/16, /*RTP*/10, /*ZQCL*/342, /*ZQCS*/86,
    }, {
// #define DDR3_1866L           3   // sg107E //DDR3-1866L (12-12-12) tCK=1.07ns
        /*tCK*/ 1070,
        /*tCL*/ 12, /*WCL*/9, /*RCD*/12, /*RAS*/32, /*RP*/12, /*RC*/44, /*RRD*/6,
        /*FAW*/33, /*WR*/14, /*RTP*/9, /*ZQCL*/300, /*ZQCS*/75,
    }, {
// #define DDR3_1866K           4   // sg107F //DDR3-1866K (11-11-11) tCK=1.07ns
        /*tCK*/ 1070,
        /*tCL*/ 11, /*WCL*/9, /*RCD*/11, /*RAS*/32, /*RP*/11, /*RC*/43, /*RRD*/6,
        /*FAW*/33, /*WR*/14, /*RTP*/9, /*ZQCL*/300, /*ZQCS*/75,
    }, {
// #define DDR3_1600J           5   // sg125E //DDR3-1600J (10-10-10) tCK=1.25ns
        /*tCK*/ 1250,
        /*tCL*/ 10, /*WCL*/8, /*RCD*/10, /*RAS*/28, /*RP*/10, /*RC*/38, /*RRD*/6,
        /*FAW*/32, /*WR*/12, /*RTP*/8, /*ZQCL*/256, /*ZQCS*/64,
    }, {
// #define DDR3_1600K           6   // sg125 //DDR3-1600K (11-11-11) tCK=1.25ns
        /*tCK*/ 1250,
        /*tCL*/ 11, /*WCL*/8, /*RCD*/11, /*RAS*/28, /*RP*/11, /*RC*/37, /*RRD*/6,
        /*FAW*/32, /*WR*/12, /*RTP*/8, /*ZQCL*/256, /*ZQCS*/64,
    }, {
// #define DDR3_1333H           7   // sg15E //DDR3-1333H (9-9-9) tCK=1.5ns
        /*tCK*/ 1500,
        /*tCL*/ 9, /*WCL*/7, /*RCD*/9, /*RAS*/24, /*RP*/9, /*RC*/33, /*RRD*/5,
        /*FAW*/30, /*WR*/10, /*RTP*/5, /*ZQCL*/256, /*ZQCS*/64,
    }, {
// #define DDR3_1333J           8   // sg15 //DDR3-1333J (10-10-10) tCK=1.5ns
        /*tCK*/ 1500,
        /*tCL*/ 10, /*WCL*/7, /*RCD*/10, /*RAS*/24, /*RP*/10, /*RC*/34, /*RRD*/5,
        /*FAW*/30, /*WR*/10, /*RTP*/7, /*ZQCL*/256, /*ZQCS*/64,
    }, {
// #define DDR3_1066F           9   // sg187E //DDR3-1066F (7-7-7) tCK=1.875ns
        /*tCK*/ 1875,
        /*tCL*/ 7, /*WCL*/6, /*RCD*/7, /*RAS*/20, /*RP*/7, /*RC*/27, /*RRD*/6,
        /*FAW*/27, /*WR*/8, /*RTP*/6, /*ZQCL*/256, /*ZQCS*/64,
    }, {
// #define DDR3_1066G           10  // sg187 //DDR3-1066G (8-8-8) tCK=1.875ns
        /*tCK*/ 1875,
        /*tCL*/ 8, /*WCL*/6, /*RCD*/8, /*RAS*/20, /*RP*/8, /*RC*/28, /*RRD*/6,
        /*FAW*/27, /*WR*/8, /*RTP*/6, /*ZQCL*/256, /*ZQCS*/64,
    }, {
// #define DDR3_800D            11  // sg25E //DDR3-800D (5-5-5) tCK=2.5ns
        /*tCK*/ 2500,
        /*tCL*/ 5, /*WCL*/5, /*RCD*/5, /*RAS*/15, /*RP*/5, /*RC*/20, /*RRD*/4,
        /*FAW*/17, /*WR*/5, /*RTP*/3, /*ZQCL*/256, /*ZQCS*/64,
    }, {
// #define DDR3_800E            12  // sg25 //DDR3-800E (6-6-6) tCK=2.5ns
        /*tCK*/ 2500,
        /*tCL*/ 6, /*WCL*/5, /*RCD*/6, /*RAS*/15, /*RP*/6, /*RC*/21, /*RRD*/4,
        /*FAW*/20, /*WR*/6, /*RTP*/6, /*ZQCL*/256, /*ZQCS*/64,
    },
    {
    // #define DDR3_266MPW          13  // sg25 //DDR3-800E (5-5-5) tCK=2.5ns
//      /*tCL*/ 5, /*WCL*/7, /*RCD*/5, /*RAS*/9/*37.5/4*/, /*RP*/5, /*RC*/13, /*RRD*/4,
//      /*FAW 50/4*/15, /*WR6*/5, /*RTP*/4, /*ZQCL*/256, /*ZQCS*/64,
// #define DDR3_250MPW          13  // sg25 //DDR3-800E (5-5-5) tCK=2.5ns
        /*tCK*/ 2500,
        /*tCL*/ 5, /*WCL*/7, /*RCD*/5, /*RAS*/9/*37.5/4*/, /*RP*/5, /*RC*/13, /*RRD*/4,
        /*FAW 50/4*/15, /*WR6*/5, /*RTP*/4, /*ZQCL*/256, /*ZQCS*/64,

    },
};
uint32_t Get_DDR_Capacity(const MEM_CHIP_INFO *chip_info)
{
    uint32_t n=0;
    uint32_t capacity=0;

    assert_param(chip_info);
    n=(chip_info->Chip_type<_16Mbx16)?(chip_info->Chip_type):(chip_info->Chip_type-_16Mbx16);
    capacity=(chip_info->Chip_type<_16Mbx16)?(CHIP_MIN_CAPACITY*(1<<n)*(chip_info->Chip_num+1)):(CHIP_MIN_CAPACITY*(1<<n)*(chip_info->Bus_width+1)/(BUS_WIDTH_16+1));
    return capacity;


}
uint32_t Calc_DDR_RFC(const MEM_CHIP_INFO *chip_info)
{
    uint32_t capacity=0;
    uint32_t tRFC=0;
    assert_param(chip_info);


    capacity=Get_DDR_Capacity(chip_info);
    if (chip_info->mem_type==MEM_DDR2) {

        switch(capacity){
            case CHIP_CAPACITY_32MB:tRFC=75;break;
            case CHIP_CAPACITY_64MB:tRFC=105;break;
            case CHIP_CAPACITY_128MB:tRFC=128;break;
            case CHIP_CAPACITY_256MB:tRFC=195;break;
            case CHIP_CAPACITY_512MB:tRFC=328;break;
        }
    }
    else{
        switch(capacity){
            case CHIP_CAPACITY_64MB:tRFC=90;break;
            case CHIP_CAPACITY_128MB:tRFC=110;break;
            case CHIP_CAPACITY_256MB:tRFC=160;break;
            case CHIP_CAPACITY_512MB:tRFC=300;break;
            case CHIP_CAPACITY_1024MB:tRFC=350;break;
        }
    }

    return tRFC;


}
static void DDR_Cmd(const uint32_t cmd ,const uint32_t param)
{
        DDRC->CMD =((cmd)|(param));

}
static void DDR_Latency(const uint32_t cycle  )
{
    DDR_Cmd(SW_CMD_NOP,cycle);
}
static void DDR2_conf(const MEM_CHIP_INFO *chip_info ,const void *ddr)
{
    uint32_t period=0;
    const DDR2MEM *ptr = (const DDR2MEM *)ddr;
    uint32_t tRFC=0;

    assert_param(ddr);
    tRFC=Calc_DDR_RFC(chip_info);
    period = (1000 / (SYSTEM_CLOCK_FREQ / 1000000));
    CFG_CTRL->DONE_b.CMD = 0x1;

    DDRC->MODE_b.LANE = 1;
    DDRC->MODE_b.B16 = 1;
    DDRC->REF_b.TIME =( DDR_TREF/period);
    DDRC->RP_b.RPA = 1;
    DDRC->RFC_b.DI = (tRFC/period);
    DDRC->PHUNG_b.MODE = 1;
    DDRC->RD_SEL_b.PHY_SEL = 5;

    DDRC->DQSEN0_b.DL = 2;
    DDRC->DQSEN1_b.DL = 2;
    DDRC->DQSEN2_b.DL = 2;
    DDRC->DQSEN3_b.DL = 2;
    DDRC->INTCTL_b.DONE = 1;
    DDRC->INTCTL_b.ERR = 0;
    DDRC->RDQ_b.L3 = DDRC->RDQ_b.L2 = DDRC->RDQ_b.L1 = DDRC->RDQ_b.L0 = 0x32;
    DDRC->ITMDLY_b.I0 = DDRC->ITMDLY_b.IS0 = DDRC->ITMDLY_b.I1 = DDRC->ITMDLY_b.IS1 =
        DDRC->ITMDLY_b.I2 = DDRC->ITMDLY_b.IS2 = DDRC->ITMDLY_b.I3 = DDRC->ITMDLY_b.IS3 = 3;


    DDR_Latency((POWER_UP_NOP/period));
    DDR_Cmd(SW_CMD_NOPCKE,(PRE_ALL_NOP/period));
    DDR_Cmd(SW_CMD_PREA,NULL);
    DDR_Latency(ptr->tRP);/*tRP*/
    DDR_Cmd(SW_CMD_EMR2,NULL);
    DDR_Latency(DDR2_TMRD);
    DDR_Cmd(SW_CMD_EMR3,NULL);
    DDR_Latency(DDR2_TMRD);
    DDR_Cmd(SW_CMD_DLL_EN,NULL);
    DDR_Latency(DDR2_TMRD);
    DDR_Cmd(SW_CMD_DLL_RST,NULL);
    DDR_Latency(DDR2_TMRD);
    DDR_Cmd(SW_CMD_PREA,NULL);
    DDR_Latency(ptr->tRP);
    DDR_Cmd(SW_CMD_REF,NULL);
    DDR_Latency((tRFC/period));/*tRFC*/
    DDR_Cmd(SW_CMD_REF,NULL);
    DDR_Latency((tRFC/period));
    DDR_Cmd(SW_CMD_MR,(((ptr->tWR-1)<<MR_WR_OFFSET)|(ptr->tCL<<MR_CL_OFFSET)|MR_BURST_LEN_8));
    DDR_Latency(POWER_UP_MIN_CK);
    DDR_Cmd(SW_CMD_EMR1_TEST,NULL);
    DDR_Latency(DDR2_TMRD);
}

static void DDR3_conf(const MEM_CHIP_INFO *chip_info ,const void *ddr)
{

    uint32_t period = 0;
    uint32_t tRFC = 0;
    const DDR3MEM *ptr = (const DDR3MEM *)ddr;

    tRFC = Calc_DDR_RFC(chip_info);
    period = (1000 / (SYSTEM_CLOCK_FREQ / 1000000));

    DDRC->MODE_b.LANE = 0x1;
    DDRC->QUE_b.DEPTH=1;
    DDRC->REF_b.TIME = (DDR_TREF / period);////// //2Gb periodic refresh interval 7.8us 7.8us/5ns
    DDRC->REF_b.TRIG = 1;
    DDRC->REF_b.THRD = 8;
    DDRC->ZQCSR_b.EN = 1;
    DDRC->ZQCSI = 128 * 1000000 / period;
    DDRC->RP_b.RPA = 1;
    DDRC->RFC_b.DI = (tRFC / period);

    if (ptr->tCK == 2500) { // 200MHz
        DDRC->RD_SEL_b.PHY_SEL = 5;
    } else if (ptr->tCK == 3000) { // 333MHz
        DDRC->RD_SEL_b.PHY_SEL = 6;
    }

    DDRC->PHUNG_b.MODE = 1;
    DDRC->DQSEN0_b.DL = 2;
    DDRC->DQSEN1_b.DL = 2;
    DDRC->DQSEN2_b.DL = 2;
    DDRC->DQSEN3_b.DL = 2;

    // config MR#
    DDR_Latency((POWER_UP_NOP/period));//200us nop
    DDR_Cmd(SW_CMD_RSTH,NULL);// RESET H
    DDR_Latency((RSTH_NOP/period));// 500us nop
    DDR_Cmd(SW_CMD_NOPCKE,((tRFC+10)/period));//     cke high 170/tck tck txpr max(5nck, trfc(min) + 10ns)   2Gb refresh time 160ns
    DDR_Cmd(SW_CMD_EMR2,((ptr->tWCL-5)<<MR2_CWL_OFFSET)); //MR2
    DDR_Latency(DDR3_TMRD);// tmrd  4nck
    DDR_Cmd(SW_CMD_EMR3,NULL);// MR3
    DDR_Latency(DDR3_TMRD); // tmrd
    DDR_Cmd(SW_CMD_EMR1,MR1_RZQ_4); // MR1
    DDR_Latency(DDR3_TMRD); // tmrd
    DDR_Cmd(SW_CMD_MR,(MR_PPD_FAST|MR_DLL_YES|((ptr->tWR-1)<<MR_WR_OFFSET)|(CAL_DDR3_CL(ptr->tCL))));
                                                        // MR0
                                                        // A1 , A0 2'b0 fixed 8
                                                        // A2 CL 0
                                                        // A3 nibble sequential 0  Interleave 1
                                                        // A6,A5,A4 CL 101 CL =9
                                                        // A7 normal mode 0
                                                        // A8 DLL reset 1
                                                        // A11,A10,A9 wr=(twr/ck)=(15/3)=5  =001
                                                        // A12 DLL control for precharge PD fast exit 1
                                                        // MR0 =0xb50
    DDR_Latency(MAX(DDR3_TMOD_CK,(DDR3_TMOD/period)));// tmod max (12nck,15ns)
    DDR_Cmd(SW_CMD_ZQCL,NULL);// ZQCL starting ZQ calibration
    DDR_Latency(MAX(DDR3_TZQINIT_CK,(DDR3_TZQINIT/period))); // tdllk 512nck (should be 500nck)
    DDR_Latency(DDR3_TDLLK_CK); // tZQinit max(512nck,640ns)

}

BOOL DDR_Init(const MEM_CHIP_INFO *chip_info, const void *ddr)
{
    uint32_t tCL, tWR, tWCL, tWTR, tCK,mode;

    assert_param(chip_info);
    assert_param(ddr);
    if((chip_info->Bus_width<BUS_WIDTH_MAX)
        &&(chip_info->Chip_num<CHIP_NUM_MAX)
        &&(chip_info->Chip_type<    CHIP_TYPE_MAX))
    {
        if(chip_info->mem_type==MEM_DDR2)
        {
            mode=DDR2_MODE[chip_info->Bus_width][chip_info->Chip_num][chip_info->Chip_type];
        }
        else
        {
            mode=DDR3_MODE[chip_info->Bus_width][chip_info->Chip_num][chip_info->Chip_type];
        }
        if(mode==0xff)
        {
            return FALSE;
        }


    }
    else
    {
        return FALSE;
    }


    PDPROT->LOCK_b.EN = 0;
    do {
        CFG_CTRL->PDLLSTR_b.C2R1D = 0; // rst dll_c2r1
        udelay(10);
        CFG_CTRL->PDLLSTR_b.C2R1D = 1; // releset rst
        udelay(10);
    } while ((PDLOCK->GCLK & 0x40) != 0x40);
    PDPROT->LOCK_b.EN = 1;

    DDRC->MODE_b.MODE = mode;

    if (chip_info->mem_type==MEM_DDR2) {
        const DDR2MEM *ptr = (const DDR2MEM *)ddr;
        DDRC->RL_b.VAL = ptr->tCL;
        DDRC->RCD_b.DI = ptr->tRCD;
        DDRC->RP_b.DI = ptr->tRP;
        DDRC->RC_b.DI = ptr->tRC;
        DDRC->RAS_b.DI = ptr->tRAS;
        tWR = ptr->tWR;
        tWTR = ptr->tWTR;
        DDRC->RRD_b.DI = ptr->tRRD;
        DDRC->RTP_b.DI = ptr->tRTP;
        DDRC->FAW_b.DI = ptr->tFAW;
        DDR2_conf(chip_info,ptr);
    } else {
        const DDR3MEM *ptr = (const DDR3MEM *)ddr;
        DDRC->RL_b.VAL = ptr->tCL;
        tWCL = ptr->tWCL;
        DDRC->RCD_b.DI = ptr->tRCD;
        DDRC->RAS_b.DI = ptr->tRAS;
        DDRC->RP_b.DI = ptr->tRP;
        DDRC->RC_b.DI = ptr->tRC;
        DDRC->RRD_b.DI = ptr->tRRD;
        DDRC->FAW_b.DI = ptr->tFAW;
        tWR = ptr->tWR;
        tCK = ptr->tCK;
        DDRC->RTP_b.DI = ptr->tRTP;
        DDRC->ZQCL_b.DI = ptr->tZQoper;
        DDRC->ZQCS_b.DI = ptr->tZQCS;
        DDR3_conf(chip_info,ptr);
    }

    tCL = DDRC->RL_b.VAL;

    DDRC->WTR_b.DI  = (DDRC->MODE_b.MODE & 0x20) ?
        (tWCL + tWTR + (DDRC->BURST_b.LEN ? 2 : 4)) :
        ((tCK * 4) > 7500) ? 18 : (tCK * 4 + 7500 - 1) / 7500;               //4

    DDRC->CCD_b.DI  = (DDRC->MODE_b.MODE & 0x20) ? (DDRC->BURST_b.LEN ? 2 : 4) : 4;
    DDRC->RTW_b.DI  = (DDRC->MODE_b.MODE & 0x20) ? (DDRC->BURST_b.LEN ? 4 : 6) : (tCL + DDRC->CCD_b.DI - tWCL + (DDRC->BURST_b.LEN ? 0 : 2));
    DDRC->WTP_b.DI  = (DDRC->MODE_b.MODE & 0x20) ? (tCL + tWR + (DDRC->BURST_b.LEN ? 1 : 3)) : (tWCL + tWR + (DDRC->BURST_b.LEN ? 2 : 4));
    DDRC->WL_b.VAL  = (DDRC->MODE_b.MODE & 0x20) ? (MAX(tCL, 3) - 3) : (tWCL - 2);
    DDRC->ODTH_b.DL = (DDRC->MODE_b.MODE & 0x20) ? (MAX(tCL, 4) - 4) : 0;
    if (tCK == 2500) { // 200MHz
        DDRC->ODTL_b.DL = (DDRC->MODE_b.MODE & 0x20) ? (DDRC->BURST_b.LEN ? (tCL - 1) : (tCL + 1)) : (DDRC->BURST_b.LEN ? 4 : 6);
    } else if (tCK == 3000) { // 333MHz
        DDRC->ODTL_b.DL = 0x1f;
    }


    // DEBUG INFO HERE
    DDRC->CTRL_b.STR = 1;

    while (0 == DDRC->STA_b.EMPTY);
    while(0 == DDRC->INTRAW_b.DONE);
    DDRC->CTRL_b.STR = DDRC->CTRL_b.TO = 0;

    return TRUE;
}
