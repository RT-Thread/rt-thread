/*
*******************************************************************************
**
** \file      gd_sflash.c
**
** \brief     Generic sflash device driver (core functions).
**
**            (C) Goke Microelectronics SH 2009
**
** \attention THIS SAMPLE CODE IS PROVDMAD AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
*******************************************************************************
*/
#include <gtypes.h>
#include <gh_sflash.h>
#include <gh_debug_adc.h>
#include <gh_debug_rct.h>

#include "gd_sflash.h"

//#define DEBUG_PRINT 1

extern void GH_SPI_SFLASH_set_Handle(GD_SPI_STATUS_PARAMS_S* pHandle);
extern void GH_SPI_SFLASH_set_Command(U32 data);
extern void GH_SPI_SFLASH_set_Data(U32 data);
extern U32  GH_SPI_SFLASH_get_Data(void);
extern void GH_SPI_SFLASH_set_CE(U32 data);
extern U32  GH_SPI_SFLASH_get_CE(void);
extern U8   GH_SPI_SFLASH_get_CE_CHSELECT(void);
extern void GH_SPI_SFLASH_set_Speed(U32 data);
extern void GH_SPI_SFLASH_set_CE_CHSELECT(U8 data);

static GD_SFLASH_FEATURE old_feature = GD_SFLASH_FEATURE_IO1;
typedef U32 (*SFLASH_get_Data)(void);
typedef U32 (*SFLASH_set_Data)(U32 data);

/*-------------------------------------------------------------------------------*/
/* serial flash specific commands for Spansion flash devices                                            */
/*-------------------------------------------------------------------------------*/
static GD_SFLASH_CMD_S sflash_commands_mx =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0xBB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0xEB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_3      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x38                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S sflash_commands_spansion =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ 0x35                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (2<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0xBB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0xEB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_3      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

/*-------------------------------------------------------------------------------*/
/* serial flash specific commands for STmicro flash devices                      */
/*-------------------------------------------------------------------------------*/
static GD_SFLASH_CMD_S sflash_commands_stmicro =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ SFLASH_NOT_SUPPORT,
    /*read_io4         */ SFLASH_NOT_SUPPORT,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ SFLASH_NOT_SUPPORT,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

/*-------------------------------------------------------------------------------*/
/* serial flash specific commands for Atmel flash devices                        */
/*-------------------------------------------------------------------------------*/
static GD_SFLASH_CMD_S sflash_commands_atmel =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ SFLASH_NOT_SUPPORT,
    /*read_io4         */ SFLASH_NOT_SUPPORT,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ SFLASH_NOT_SUPPORT,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

/*-------------------------------------------------------------------------------*/
/* serial flash specific commands for NUMONYX flash devices                      */
/*-------------------------------------------------------------------------------*/
static GD_SFLASH_CMD_S sflash_commands_numonyx =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0xBB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_2      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0xEB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_5      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ 0xD2                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page4    */ 0x12                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S sflash_commands_wb =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ 0x35                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (2<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0xBB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0xEB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_3      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ 0xC8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (2<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_ext_addr   */ 0xC5 |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*die_sel          */ 0xC2                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S  sflash_command_sst =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_4X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_4X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_4X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_4X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ SFLASH_NOT_SUPPORT,
    /*read_io4         */ 0x0B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_4X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_4X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0x20                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x80,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S sflash_commands_gd =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ 0x35                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_status     */ 0x31                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0xBB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0xEB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_3      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S sflash_commands_eon =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_3us,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ SFLASH_NOT_SUPPORT,
    /*read_io4         */ 0x6B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S sflash_commands_issi =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0xBB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0xEB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_3      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S sflash_commands_fidelix =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x05                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ 0x35                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_status     */ 0x01                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (2<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x03                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0xBB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_2X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0xEB                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_3      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_4X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ 0xC7                              |
                          SFLASH_NO_SEND_CMD                |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01,
    /*status_mask_wel  */ 0x02,
    /*page_read        */ SFLASH_NOT_SUPPORT,
    /*program_execute  */ SFLASH_NOT_SUPPORT,
    /*reset            */ SFLASH_NOT_SUPPORT,
};

static GD_SFLASH_CMD_S sflash_commands_gd_snand_a =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (2<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x0F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x1F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x0B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0x3B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0x6B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ SFLASH_NOT_SUPPORT,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /*status_mask_wel  */ 0x02,
    /*page_read        */ 0x13                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_execute  */ 0x10                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*reset            */ 0xFF                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
};

static GD_SFLASH_CMD_S sflash_commands_gd_snand_c =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x0F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x1F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x0B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0x3B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0x6B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ SFLASH_NOT_SUPPORT,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /*status_mask_wel  */ 0x02,
    /*page_read        */ 0x13                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_execute  */ 0x10                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*reset            */ 0xFF                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
};

static GD_SFLASH_CMD_S sflash_commands_esmt_snand =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (2<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x0F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x1F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x0B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0x3B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0x6B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ SFLASH_NOT_SUPPORT,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /*status_mask_wel  */ 0x02,
    /*page_read        */ 0x13                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_execute  */ 0x10                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*reset            */ 0xFF                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
};

static GD_SFLASH_CMD_S sflash_commands_ato_snand =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x0F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x1F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x0B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0x3B                              |   //not supported
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0x6B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ SFLASH_NOT_SUPPORT,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /*status_mask_wel  */ 0x02,
    /*page_read        */ 0x13                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_execute  */ 0x10                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*reset            */ 0xFF                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
};

static GD_SFLASH_CMD_S sflash_commands_wb_snand =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (3<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x0F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x1F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x0B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0x3B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0x6B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ SFLASH_NOT_SUPPORT,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ 0xC2                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*status_mask_wip  */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /*status_mask_wel  */ 0x02,
    /*page_read        */ 0x13                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_execute  */ 0x10                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*reset            */ 0xFF                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
};

static GD_SFLASH_CMD_S sflash_commands_mx_snand =
{
    /*read_ID          */ 0x9F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (2<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_enable     */ 0x06                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*write_disable    */ 0x04                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status      */ 0x0F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_status2     */ SFLASH_NOT_SUPPORT,
    /*write_status     */ 0x1F                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_1       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
    /*read_data        */ 0x0B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io2         */ 0x3B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_2X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*read_io4         */ 0x6B                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_1      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page     */ 0x02                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_page2    */ SFLASH_NOT_SUPPORT,
    /*program_page4    */ 0x32                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_4X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_sector     */ 0xD8                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*erase_chip       */ SFLASH_NOT_SUPPORT,
    /*read_ext_addr    */ SFLASH_NOT_SUPPORT,
    /*write_ext_addr   */ SFLASH_NOT_SUPPORT,
    /*die_sel          */ SFLASH_NOT_SUPPORT,
    /*status_mask_wip  */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /*status_mask_wel  */ 0x02,
    /*page_read        */ 0x13                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_READ                   |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*program_execute  */ 0x10                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_3       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_WRITE                  |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          SFLASH_TRANSFER_BYTE_NUM_4        |
                          SFLASH_HOLD_TIME_100ns,
    /*reset            */ 0xFF                              |
                          SFLASH_SEND_CMD                   |
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |
                          SFLASH_RWN_NOTHING                |
                          SFLASH_CMD_MODE_1X                |
                          SFLASH_ADDR_MODE_1X               |
                          SFLASH_DATA_MODE_1X               |
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     |
                          SFLASH_HOLD_TIME_100ns,
};

/*
*******************************************************************************
**
** gd_sflash_devices_supported is an array containing serial flash
** geometry and information data of all supported devices, it will
** be used during GD_SFLASH_Init() to find the connected serial
** flash decive
**
*******************************************************************************
*/
static GD_SFLASH_DEV_S gd_sflash_devices_supported[] =
{

   /*
    ** Spansion seem to use unique sectors
    ** with 64kBytes each, they increment the
    ** number of sectors for bigger chips
    */
    {
        /*manufacture_ID   */ SPANSION_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x010212,
        /*manufacture_name */ "Spansion",
        /*device_name      */ "S25FL004A",
        /*device_bytes     */ 1024*512,
        /*sector_count     */ 8,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_spansion,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x9CF5,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ SPANSION_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x010213,
        /*manufacture_name */ "Spansion",
        /*device_name      */ "S25FL008A",
        /*device_bytes     */ 1024*1024*1,
        /*sector_count     */ 16,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_spansion,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x9CF5,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ SPANSION_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x010214,
        /*manufacture_name */ "Spansion",
        /*device_name      */ "S25FL016A",
        /*device_bytes     */ 1024*1024*2,
        /*sector_count     */ 32,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_spansion,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x9CF5,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ SPANSION_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x010215,
        /*manufacture_name */ "Spansion",
        /*device_name      */ "S25FL032P",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_spansion,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x9CF5,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ SPANSION_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x010216,
        /*manufacture_name */ "Spansion",
        /*device_name      */ "S25FL064A",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_spansion,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x9CF5,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ SPANSION_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x012018,
        /*manufacture_name */ "Spansion",
        /*device_name      */ "FL128PIFL",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_spansion,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x9CF5,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
    ** MXIC seem to use unique sectors
    ** with 64kBytes each, they increment the
    ** number of sectors for bigger chips
    */
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC22016,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX25L3206E",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_mx,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x00BC,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC22017,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX25L6465E",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_mx,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x00BC,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC22018,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX25L12845",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_mx,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x00BC,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC22415,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX25L1605D",
        /*device_bytes     */ 1024*1024*2,
        /*sector_count     */ 32,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_mx,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x00BC,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC22617,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX25L6455E",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_mx,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x00BC,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC25E16,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX253235D",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_mx,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x00BC,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC29E16,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX25L3255D",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_mx,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x00BC,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** Winbond seem to use unique sectors
     ** with 64kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ WINBOND_MID,
        /*commbo           */ 1,
        /*device_ID        */ 0xEF4015,
        /*manufacture_name */ "Winbond",
        /*device_name      */ "W25Q16BV",
        /*device_bytes     */ 1024*1024*2,
        /*sector_count     */ 32,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_wb,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x1C00,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ WINBOND_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xEF4016,
        /*manufacture_name */ "Winbond",
        /*device_name      */ "W25Q32FV",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_wb,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x1C00,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ WINBOND_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xEF4017,
        /*manufacture_name */ "Winbond",
        /*device_name      */ "W25Q64FV",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_wb,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x1C00,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ WINBOND_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xEF4018,
        /*manufacture_name */ "Winbond",
        /*device_name      */ "W25Q128FV",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_wb,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x1C00,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ WINBOND_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xEF4019,
        /*manufacture_name */ "Winbond",
        /*device_name      */ "W25Q256FV",
        /*device_bytes     */ 1024*1024*32,
        /*sector_count     */ 512,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_wb,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x3C00,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** SST seem to use unique sectors
     ** with 4kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ SST_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xBF2601,
        /*manufacture_name */ "SST",
        /*device_name      */ "SST26VF016",
        /*device_bytes     */ 1024*1024*2,
        /*sector_count     */ 512,
        /*sector_bytes     */ 1024*4,
        /*sector_pages     */ 16,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_command_sst,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  |                      GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** numonyx seem to use unique sectors
     ** with 64kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ NUMONYX_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x20BA18,
        /*manufacture_name */ "numonyx",
        /*device_name      */ "N25Q128",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_numonyx,
        /*feature          */ GD_SFLASH_4X_WRITE | GD_SFLASH_2X_WRITE | GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** giga seem to use unique sectors
     ** with 64kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC84016,
        /*manufacture_name */ "giga",
        /*device_name      */ "GD25Q32C",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_gd,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFC79,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC84017,
        /*manufacture_name */ "giga",
        /*device_name      */ "GD25Q64C",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_gd,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFC79,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC84018,
        /*manufacture_name */ "giga",
        /*device_name      */ "GD25Q128C",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_gd,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFC79,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** EON seem to use unique sectors
     ** with 64kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ EON_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x1C3017,
        /*manufacture_name */ "EON",
        /*device_name      */ "EN25Q64",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_eon,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  |                      GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x003C,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ EON_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x1C7017,
        /*manufacture_name */ "EON",
        /*device_name      */ "ENQH64A",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_eon,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  |                      GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x003C,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ EON_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x1C7018,
        /*manufacture_name */ "EON",
        /*device_name      */ "EN25Q128",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_eon,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  |                      GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x003C,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** XMC seem to use unique sectors
     ** with 64kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ XMC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x207017,
        /*manufacture_name */ "XMC",
        /*device_name      */ "XMQH64A",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_eon,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  |                      GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x003C,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ XMC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x207018,
        /*manufacture_name */ "XMC",
        /*device_name      */ "XM25Q128",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_eon,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  |                      GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x003C,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** ISSI seem to use unique sectors
     ** with 64kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ ISSI_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x9D6016,
        /*manufacture_name */ "ISSI",
        /*device_name      */ "IS25LP032",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_issi,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ ISSI_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x9D6017,
        /*manufacture_name */ "ISSI",
        /*device_name      */ "IS25LP064",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_issi,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ ISSI_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x9D6018,
        /*manufacture_name */ "ISSI",
        /*device_name      */ "IS25LP128",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 256,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_issi,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    {
        /*manufacture_ID   */ ISSI_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x7F9D46,
        /*manufacture_name */ "ISSI",
        /*device_name      */ "P25LQ032",
        /*device_bytes     */ 1024*1024*4,
        /*sector_count     */ 64,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_issi,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** Fidelix seem to use unique sectors
     ** with 64kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ FIDELIX_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xF83217,
        /*manufacture_name */ "Fidelix",
        /*device_name      */ "FM25Q64A",
        /*device_bytes     */ 1024*1024*8,
        /*sector_count     */ 128,
        /*sector_bytes     */ 1024*64,
        /*sector_pages     */ 256,
        /*page_bytes       */ 256,
        /*commands         */ &sflash_commands_fidelix,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0x3C00,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NOR,
    },
    /*
     ** GIGA seem to use unique sectors
     ** with 128kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC8F1,
        /*manufacture_name */ "GigaDevice",
        /*device_name      */ "GD5F1GQ4UA",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 1024,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_gd_snand_a,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC8F2,
        /*manufacture_name */ "GigaDevice",
        /*device_name      */ "GD5F2GQ4UA",
        /*device_bytes     */ 1024*1024*256,
        /*sector_count     */ 1024*2,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_gd_snand_a,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC8F4,
        /*manufacture_name */ "GigaDevice",
        /*device_name      */ "GD5F4GQ4UA",
        /*device_bytes     */ 1024*1024*512,
        /*sector_count     */ 1024*4,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_gd_snand_a,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC8D148,
        /*manufacture_name */ "GigaDevice",
        /*device_name      */ "GD5F1GQ4UC",
        /*device_bytes     */ 1024*1024*16,
        /*sector_count     */ 1024,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_gd_snand_c,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC8D248,
        /*manufacture_name */ "GigaDevice",
        /*device_name      */ "GD5F2GQ4UC",
        /*device_bytes     */ 1024*1024*256,
        /*sector_count     */ 1024*2,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_gd_snand_c,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    {
        /*manufacture_ID   */ GIGA_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC8D448,
        /*manufacture_name */ "GigaDevice",
        /*device_name      */ "GD5F4GQ4UC",
        /*device_bytes     */ 1024*1024*512,
        /*sector_count     */ 1024*4,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_gd_snand_a,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    /*
     ** ESMT seem to use unique sectors
     ** with 128kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ ESMT_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC820,
        /*manufacture_name */ "ESMT",
        /*device_name      */ "F50L512M41A",
        /*device_bytes     */ 64*1024*1024,
        /*sector_count     */ 512,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_esmt_snand,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    /*
     ** ATO seem to use unique sectors
     ** with 128kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ ATO_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0x9B0012,
        /*manufacture_name */ "ATO",
        /*device_name      */ "ATO25D1GA",
        /*device_bytes     */ 1024*1024*128,
        /*sector_count     */ 1024,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_ato_snand,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    /*
     ** WINBOND seem to use unique sectors
     ** with 128kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ WINBOND_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xEFAA21,
        /*manufacture_name */ "Winbond",
        /*device_name      */ "W25N01GV",
        /*device_bytes     */ 1024*1024*128,
        /*sector_count     */ 1024,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_wb_snand,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    {
        /*manufacture_ID   */ WINBOND_MID,
        /*commbo           */ 1,
        /*device_ID        */ 0xEFAB21,
        /*manufacture_name */ "Winbond",
        /*device_name      */ "W25M161AV-W25N01GV",
        /*device_bytes     */ 1024*1024*128,
        /*sector_count     */ 1024,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_wb_snand,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
    /*
     ** MXIC seem to use unique sectors
     ** with 128kBytes each, they increment the
     ** number of sectors for bigger chips
     */
    {
        /*manufacture_ID   */ MXIC_MID,
        /*commbo           */ 0,
        /*device_ID        */ 0xC212,
        /*manufacture_name */ "MX",
        /*device_name      */ "MX35LF1GE4AB",
        /*device_bytes     */ 1024*1024*128,
        /*sector_count     */ 1024,
        /*sector_bytes     */ 1024*128,
        /*sector_pages     */ 64,
        /*page_bytes       */ 1024*2,
        /*commands         */ &sflash_commands_mx_snand,
        /*feature          */ GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                              GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ,
        /*lock_mask        */ 0xFFFF,
        /*io4_mask         */ 0xFFFF,
        /*type             */ GD_SPI_NAND,
    },
};

/*
*******************************************************************************
**
** gd_flash_sector_buffer is used during the programming phase to buffer
** the contents of one sector, this buffer must be big enough to store
** the largest supported sector, which is currently 262144 bytes.
**
*******************************************************************************
*/
static U32 gd_flash_sector_buffer[262144/sizeof(U32)];

/*
*******************************************************************************
**
** gd_flash_device is used to point to the device structure
** refering to the device found during GD_SFLASH_Init()
**
*******************************************************************************
*/
static GD_SFLASH_HANDLE_S gd_sflash_devices[GD_SFLASH_CHANNEL_NUM] = {0};

/*
*******************************************************************************
**
** gd_sflash_handle is used to store information during GD_SFLASH_Open()
** according to H/W design, 1 or 2 instance could be supported
**
*******************************************************************************
*/
static GD_SFLASH_HANDLE_S* gd_sflash_handle[GD_SFLASH_CHANNEL_NUM] = {0};

static GBOOL InitDone = GFALSE;
/*
*******************************************************************************
**
** sflashGetDevice is used check and get the GD_SFLASH_HANDLE_S pointer from
** a given handle variable.
**
*******************************************************************************
*/

GERR sflashEnableIO4Hw(GD_HANDLE handle,GBOOL enable)
{
    U32 CESetting = 0;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)(void*)handle;
    if(!device)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    CESetting = device->func.GH_SFLASH_get_CE();
    CESetting &= 0xC0;
    if(enable == GTRUE)
    {
        CESetting |= 0x38;
    }
    else
    {
        CESetting |= 0x0E;
    }
    device->func.GH_SFLASH_set_CE(CESetting);
    return GD_OK;
}

/*
*******************************************************************************
**
** sflash_wip_done_wait is used to wait until the WIP (write-in-progress)
** flag is cleared by the device.
**
*******************************************************************************
*/
static GERR sflash_wip_done_wait(GD_HANDLE handle)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U8 wipMask;

    wipMask = device->dev->commands->status_mask_wip;
    while(1)
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);

        if((device->func.GH_SFLASH_get_Data() & wipMask) != wipMask)
        {
            return(GD_OK);
        }
    }
}

static GERR sflash_wel_done_wait(GD_HANDLE handle)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U8 welMask;
    U32 status;

    welMask = device->dev->commands->status_mask_wel;
    while(1)
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        status = device->func.GH_SFLASH_get_Data()&0xff;

        if((status& welMask) == welMask)
        {
            return(GD_OK);
        }
    }
}

static GERR sflash_write_enable(GD_HANDLE handle)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
    device->func.GH_SFLASH_get_Data();

    return sflash_wel_done_wait(handle);
}

/*
*******************************************************************************
**
** spiNandFlashOipDoneWait is used to wait until the OIP (operation-in-progress)
** flag is cleared by the device.
**
*******************************************************************************
*/
static GERR spiNandFlashOipDoneWait(GD_HANDLE handle)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U8 oipMask;
    U8 read_status = 0;

    oipMask = device->dev->commands->status_mask_wip;

    while(1)
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        device->func.GH_SFLASH_set_Data(0xC0);

        read_status = device->func.GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("read_status(0xc0):0x%02x\n",read_status);
#endif
        if((read_status & oipMask) != oipMask)
        {
            return(GD_OK);
        }
    }
}

/*
*******************************************************************************
**
** spiNandFlashRead is used to read contents from spi-nand flash.
**
*******************************************************************************
*/
static GERR spiNandFlashRead(GD_HANDLE handle,
                             U32* buffer,
                             U32 startPage,
                             U32 startAddr,
                             U32 endPage,
                             U32 endAddr)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 i;
    U32 readPage = startPage;
    U32 length, pageCnt = 0;
    U32 start_addr = startAddr;
    GBOOL pageMatched = GFALSE;
    SFLASH_get_Data get_Data;
    get_Data = device->func.GH_SFLASH_get_Data;

    if((startAddr == 0x0) && (endAddr == 0x0))
    {
        pageMatched = GTRUE;
    }
    // start read page from spi-nand
    while(readPage < endPage)
    {
        // 1. page read to cache
        device->func.GH_SFLASH_set_Command(device->dev->commands->page_read);
        device->func.GH_SFLASH_set_Data(readPage);      // here address should be page/block address,
                                                        // since total page number = size / page_bytes
                                                        // for size = 128MB, pageSize = 2KB
                                                        // total page number = 128MB / 2KB = 64KB
        // 2. check if page read is done
#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashRead\n");
#endif
        spiNandFlashOipDoneWait(handle);

        // 3. read from cache
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_io4);
        }
        else if((device->feature & 0x0F) == GD_SFLASH_2X_READ)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_io2);
        }
        else
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_data);
        }

        device->func.GH_SFLASH_set_Data(start_addr);

        length = (device->dev->page_bytes - start_addr) /  sizeof(U32);

        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }

        for(i=0;i<length;i++)
        {
            *buffer++ = get_Data();
        }

        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }

        readPage++;
        pageCnt++;
        if(pageCnt == 0x1)
        {
            start_addr = 0x0;
        }
    }

    // last page
    if(pageMatched == GFALSE)
    {
        // 1. page read to cache
        device->func.GH_SFLASH_set_Command(device->dev->commands->page_read);
        device->func.GH_SFLASH_set_Data(readPage);                   // here address should be page/block address,
                                                        // since total page number = size / page_bytes
                                                        // for size = 128MB, pageSize = 2KB
                                                        // total page number = 128MB / 2KB = 64KB
        // 2. check if page read is done
#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashRead\n");
#endif
        spiNandFlashOipDoneWait(handle);

        // 3. read from cache
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_io4);
        }
        else if((device->feature & 0x0F) == GD_SFLASH_2X_READ)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_io2);
        }
        else
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_data);
        }
        device->func.GH_SFLASH_set_Data(start_addr);

        length = (endAddr - start_addr) / sizeof(U32);
        // only for debug, to be removed later
        // printf("[spi-nand-write] readPage = %d, length = %d, start_addr = 0x%08x, endAddr = 0x%08x, pageCnt = %d \n", readPage, length, start_addr, endAddr, pageCnt);
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }
        for(i=0;i<length;i++)
        {
            *buffer++ = device->func.GH_SFLASH_get_Data();
        }
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }
    }
    return GD_OK;
}

/*
*******************************************************************************
**
** spiNandFlashWrite is used to write contents to spi-nand flash.
**
*******************************************************************************
*/
static GERR spiNandFlashWrite(GD_HANDLE handle,
                             U32* buffer,
                             U32 startPage,
                             U32 startAddr,
                             U32 endPage,
                             U32 endAddr)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 i;
    U32 writePage = startPage;
    U32 length, pageCnt = 0;
    U32 start_addr = startAddr;
    U32 *temp_buf;
    GERR result = GD_ERR_SFLASH_WRITE;
    GBOOL pageMatched = GFALSE;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)device->func.GH_SFLASH_set_Data;

    if(endAddr == 0x0)
    {
        pageMatched = GTRUE;
    }

    // start write page to spi-nand
    while(writePage < endPage)
    {
        //
        // issue a write command sequence to prepare
        // the device for data to be written
        //

        if(device->dev->manufacture_ID == 0xbf)
        {
            if(start_addr==0)
            {
                length = device->dev->page_bytes /  sizeof(U32);
                temp_buf = buffer;
                for(i=0;i<length;i++)
                {
                    if(temp_buf[i] != 0xFFFFFFFF)
                    {
                        // need write to snand
                        break;
                    }
                }
                if(i==length)
                {
                   buffer += length;
                   writePage++;
                   pageCnt++;
                   continue;
                }
            }
        }

        device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
        device->func.GH_SFLASH_get_Data();

        if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page4);
        }
        else if((device->feature & 0xF0) == GD_SFLASH_2X_WRITE)
        {
            if(device->dev->commands->program_page2 == SFLASH_NOT_SUPPORT)
            {
                return(GD_ERR_SFLASH_TYPE_NOT_SUPPORTED);
            }
            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page2);
        }
        else
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page);
        }
        device->func.GH_SFLASH_set_Data(start_addr);

        length = (device->dev->page_bytes - start_addr) /  sizeof(U32);

        if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }
        for(i=0;i<length;i++)
        {
            set_Data(*buffer++);
        }

        if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }

        device->func.GH_SFLASH_set_Command(device->dev->commands->program_execute);
        device->func.GH_SFLASH_set_Data(writePage);

        // only for debug, to be removed later
        // printf("[spi-nand-write] writePage = %d, length = %d, start_addr = 0x%08x, endAddr = 0x%08x, pageCnt = %d \n", writePage, length, start_addr, endAddr, pageCnt);

#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashWrite\n");
#endif
        result = spiNandFlashOipDoneWait(handle);
        if(result != GD_OK)
            break;

        writePage++;
        pageCnt++;
        if(pageCnt == 0x1)
        {
            start_addr = 0x0;
        }
    }

    // last page
    if(pageMatched == GFALSE)
    {
        //
        // issue a write command sequence to prepare
        // the device for data to be written
        //
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
        device->func.GH_SFLASH_get_Data();

        if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page4);
        }
        else if((device->feature & 0xF0) == GD_SFLASH_2X_WRITE)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page2);
        }
        else
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page);
        }
        device->func.GH_SFLASH_set_Data(start_addr);

        length = (endAddr - start_addr) / sizeof(U32);
        if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }
        for(i=0;i<length;i++)
        {
            device->func.GH_SFLASH_set_Data(*buffer++);
        }
        if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }
        // only for debug, to be removed later
        // printf("[spi-nand-write] writePage = %d, length = %d, start_addr = 0x%08x, endAddr = 0x%08x, pageCnt = %d \n", writePage, length, start_addr, endAddr, pageCnt);
        device->func.GH_SFLASH_set_Command(device->dev->commands->program_execute);
        device->func.GH_SFLASH_set_Data(writePage);

#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashWrite\n");
#endif
        result = spiNandFlashOipDoneWait(handle);
    }
    return result;
}

/*
*******************************************************************************
**
** spiNandFlashEraseSector is used to erase sector of spi-nand flash.
**
*******************************************************************************
*/
static GERR spiNandFlashEraseSector(GD_HANDLE handle, U32 address)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 blockAddr;
    GERR gerr;
    //
    // issue a write command sequence to prepare
    // the device for data to be written
    //
    device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
    device->func.GH_SFLASH_get_Data();

    device->func.GH_SFLASH_set_Command(device->dev->commands->erase_sector);
    blockAddr = address / device->dev->page_bytes;
    device->func.GH_SFLASH_set_Data(blockAddr);

#ifdef DEBUG_PRINT
    GM_Printf("spiNandFlashEraseSector\n");
#endif
    gerr = spiNandFlashOipDoneWait(handle);
    return gerr;
}

/*!
********************************************************************************
**
** \brief Initialize the serial flash driver
**
** This function initializes the serial flash driver, it tries to detect a
** serial flash device by executing the read_ID commands for all supported
** vendors, the resulting mannufactor ID and device ID will be checked
** with the values from an internal array containing data for all supported
** devices.
**
** \return
** - GD_ERR_ALREADY_INITIALIZED if already initialized
** - GD_ERR_SFLASH_TYPE_NOT_SUPPORTED if the connected device is not (yet)
**   supported
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_Init(void)
{
    U32 i;
    if(InitDone)
    {
        return(GD_ERR_ALREADY_INITIALIZED);
    }
    for(i=0;i<GD_SFLASH_CHANNEL_NUM;i++)
    {
        gd_sflash_handle[i] = NULL;
    }
    InitDone = GTRUE;
    GH_PLL_set_IOCTRL_SFLASH(0x11);
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Terminates the serial flash driver
**
** This function terminates the serial flash driver.
**
** \return
** - GD_ERR_NOT_INITIALIZED if the driver was not initialized before
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_Exit(void)
{
    U32 i;
    if(!InitDone)
    {
        return(GD_ERR_NOT_INITIALIZED);
    }
    for(i=0;i<GD_SFLASH_CHANNEL_NUM;i++)
    {
        gd_sflash_handle[i] = NULL;
    }
    InitDone = GFALSE;
    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Opens a new serial flash driver instance
**
** This function opens a new instance of the serial flash driver for
** application use. It first checks whether the driver is currently not in
** use because it is not allowed to open more that one instance.
**
** \param pHandle The address of a variable where to store the resulting handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_ERR_SFLASH_IN_USE if the driver is already in use
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_Open(GD_HANDLE* pHandle, GD_SFLASH_SPEED_MODE speed_mode, GD_SFLASH_CHANNEL_E channel)
{
    U32 sflash_data;
    U8  manufacture_ID;
    U32 device_ID;
    U32 index;
    U32 count;
    U32 cmd_bit_set = 0;
    U8  status;
    U32 prot1,prot2;
    GD_SFLASH_DEV_S* device;
    U32 CESetting = 0x0E;
    GD_HANDLE   spi;
    GD_SPI_OPEN_PARAMS_S openParams;
    if( !pHandle )
        return( GD_ERR_BAD_PARAMETER );

    if(channel >= GD_SFLASH_CHANNEL_NUM)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if( gd_sflash_handle[channel] )
    {
        return(GD_ERR_ALREADY_OPEN);
    }

    switch(channel)
    {
    case GD_SFLASH_CHANNEL_0:
    case GD_SFLASH_CHANNEL_1:
        gd_sflash_devices[channel].func.GH_SFLASH_set_Handle      = NULL;
        gd_sflash_devices[channel].func.GH_SFLASH_set_Command     = GH_SFLASH_set_Command;
        gd_sflash_devices[channel].func.GH_SFLASH_set_Data        = GH_SFLASH_set_Data;
        gd_sflash_devices[channel].func.GH_SFLASH_get_Data        = GH_SFLASH_get_Data;
        gd_sflash_devices[channel].func.GH_SFLASH_set_CE          = GH_SFLASH_set_CE;
        gd_sflash_devices[channel].func.GH_SFLASH_get_CE          = GH_SFLASH_get_CE;
        gd_sflash_devices[channel].func.GH_SFLASH_get_CE_CHSELECT = GH_SFLASH_get_CE_CHSELECT;
        gd_sflash_devices[channel].func.GH_SFLASH_set_Speed       = GH_SFLASH_set_Speed;
        gd_sflash_devices[channel].func.GH_SFLASH_set_CE_CHSELECT = GH_SFLASH_set_CE_CHSELECT;
        gd_sflash_devices[channel].channel = channel;
        gd_sflash_devices[channel].devicechannel = 0;
        break;
    case GD_SFLASH_CHANNEL_0_DIE1:
    case GD_SFLASH_CHANNEL_1_DIE1:
        gd_sflash_devices[channel].func.GH_SFLASH_set_Handle      = NULL;
        gd_sflash_devices[channel].func.GH_SFLASH_set_Command     = GH_SFLASH_set_Command;
        gd_sflash_devices[channel].func.GH_SFLASH_set_Data        = GH_SFLASH_set_Data;
        gd_sflash_devices[channel].func.GH_SFLASH_get_Data        = GH_SFLASH_get_Data;
        gd_sflash_devices[channel].func.GH_SFLASH_set_CE          = GH_SFLASH_set_CE;
        gd_sflash_devices[channel].func.GH_SFLASH_get_CE          = GH_SFLASH_get_CE;
        gd_sflash_devices[channel].func.GH_SFLASH_get_CE_CHSELECT = GH_SFLASH_get_CE_CHSELECT;
        gd_sflash_devices[channel].func.GH_SFLASH_set_Speed       = GH_SFLASH_set_Speed;
        gd_sflash_devices[channel].func.GH_SFLASH_set_CE_CHSELECT = GH_SFLASH_set_CE_CHSELECT;
        gd_sflash_devices[channel].channel = channel - GD_SFLASH_CHANNEL_0_DIE1;
        gd_sflash_devices[channel].devicechannel = 1;
        break;
    case GD_SFLASH_SPI_CHANNEL_0_0:
    case GD_SFLASH_SPI_CHANNEL_0_1:
    case GD_SFLASH_SPI_CHANNEL_0_4:
    case GD_SFLASH_SPI_CHANNEL_0_5:
    case GD_SFLASH_SPI_CHANNEL_0_6:
    case GD_SFLASH_SPI_CHANNEL_0_7:
        {
            openParams.spi      = GD_SPI_CHANNEL_0;
            openParams.slave    = GD_SPI_SLAVE0 + channel - GD_SFLASH_SPI_CHANNEL_0_0;
            openParams.baudrate = speed_mode;

            GD_SPI_Open(&openParams, &spi);

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle((GD_SPI_STATUS_PARAMS_S*)spi);
            gd_sflash_devices[channel].channel = GD_SPI_CHANNEL_0;
            gd_sflash_devices[channel].devicechannel = 0;
        }
        break;
    case GD_SFLASH_SPI_CHANNEL_0_0_DIE1:
    case GD_SFLASH_SPI_CHANNEL_0_1_DIE1:
    case GD_SFLASH_SPI_CHANNEL_0_4_DIE1:
    case GD_SFLASH_SPI_CHANNEL_0_5_DIE1:
    case GD_SFLASH_SPI_CHANNEL_0_6_DIE1:
    case GD_SFLASH_SPI_CHANNEL_0_7_DIE1:
        {
            openParams.spi      = GD_SPI_CHANNEL_0;
            openParams.slave    = GD_SPI_SLAVE0 + channel - GD_SFLASH_SPI_CHANNEL_0_0;
            openParams.baudrate = speed_mode;

            GD_SPI_Open(&openParams, &spi);

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle((GD_SPI_STATUS_PARAMS_S*)spi);
            gd_sflash_devices[channel].channel = GD_SPI_CHANNEL_0;
            gd_sflash_devices[channel].devicechannel = 1;
        }
        break;
    case GD_SFLASH_SPI_CHANNEL_1_0:
        {
            openParams.spi      = GD_SPI_CHANNEL_1;
            openParams.slave    = GD_SPI_SLAVE0;
            openParams.baudrate = speed_mode;

            GD_SPI_Open(&openParams, &spi);

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle((GD_SPI_STATUS_PARAMS_S*)spi);
            gd_sflash_devices[channel].channel = GD_SPI_CHANNEL_1;
            gd_sflash_devices[channel].devicechannel = 0;
        }
        break;
    case GD_SFLASH_SPI_CHANNEL_1_0_DIE1:
        {
            openParams.spi      = GD_SPI_CHANNEL_1;
            openParams.slave    = GD_SPI_SLAVE0;
            openParams.baudrate = speed_mode;

            GD_SPI_Open(&openParams, &spi);

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
            gd_sflash_devices[channel].func.GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
            gd_sflash_devices[channel].func.GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
            gd_sflash_devices[channel].func.GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

            gd_sflash_devices[channel].func.GH_SFLASH_set_Handle((GD_SPI_STATUS_PARAMS_S*)spi);
            gd_sflash_devices[channel].channel = GD_SPI_CHANNEL_1;
            gd_sflash_devices[channel].devicechannel = 1;
        }
        break;
     default:
        return(GD_ERR_BAD_PARAMETER);
    }

    CESetting = CESetting | ((U32)gd_sflash_devices[channel].channel << 6);

    gd_sflash_devices[channel].func.GH_SFLASH_set_CE(CESetting);
    gd_sflash_devices[channel].func.GH_SFLASH_set_Speed(speed_mode); //0 -- 1/2freq 1--1/4freq  2....4

    gd_sflash_handle[channel]  = 0;
    count = sizeof(gd_sflash_devices_supported)/sizeof(GD_SFLASH_DEV_S);

    // normal spi serial flash
    for(index=0;index<count;index++)
    {
        device = &(gd_sflash_devices_supported[index]);
        if((gd_sflash_devices[channel].devicechannel == 1) &&
           (device->type == GD_SPI_NOR))
        {
            continue;
        }

        gd_sflash_devices[channel].func.GH_SFLASH_set_CE(CESetting);
        //////////////////////////////////////////
        // Steven Yu:Add code for winband W25M161AV=W25Q16JV+W25N01GV
        if(device->commbo &&
          (device->commands->die_sel != SFLASH_NOT_SUPPORT))
        {
            gd_sflash_devices[channel].func.GH_SFLASH_set_Command(device->commands->die_sel);
            gd_sflash_devices[channel].func.GH_SFLASH_set_Data(gd_sflash_devices[channel].devicechannel);
        }
        //////////////////////////////////////////

        gd_sflash_devices[channel].func.GH_SFLASH_set_Command(device->commands->read_ID);
        if(device->type == GD_SPI_NAND)
        {
            gd_sflash_devices[channel].func.GH_SFLASH_set_Data(0x00);
        }

        sflash_data = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();

        device_ID = sflash_data & 0x00FFFFFF;
        if(device->type == GD_SPI_NAND)
        {
            if(((device->commands->read_ID & (0x3 << SFLASH_TRANSFER_BYTE_LOC)) >> SFLASH_TRANSFER_BYTE_LOC) == 2)
            {
                device_ID &= 0x0000FFFF;
            }
        }
        if(device_ID      == device->device_ID)
        {
            if(device->type == GD_SPI_NOR)
            {
                if(manufacture_ID == SST_MID) // SST sflash which support most quad io cmd
                {
                    cmd_bit_set = (0x38                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_NOTHING               |
                                   SFLASH_CMD_MODE_1X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_1X              |
                                   (0<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );

                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                    gd_sflash_devices[channel].func.GH_SFLASH_get_Data();

                    cmd_bit_set = (0xaf                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_READ                  |
                                   SFLASH_CMD_MODE_4X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_4X              |
                                   (3<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );

                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);

                    sflash_data = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();

                    device_ID = (U16)(sflash_data & 0x00FFFFFF);

                    if(device_ID != 0xBF2601)
                    {
                        return(GD_ERR_SFLASH_TYPE_NOT_SUPPORTED);
                    }

                    // ok read the protection bit for each block
                    cmd_bit_set = (0x72                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_READ                  |
                                   SFLASH_CMD_MODE_4X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_4X              |
                                   (6<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );

                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                    prot1 = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();
                    prot2 = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();

                    // ok write enable the device
                    cmd_bit_set = (0x06                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_NOTHING               |
                                   SFLASH_CMD_MODE_4X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_4X              |
                                   (0<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );
                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                    gd_sflash_devices[channel].func.GH_SFLASH_get_Data();

                    // program the prot bit
                    cmd_bit_set = (0x42                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_WRITE                 |
                                   SFLASH_CMD_MODE_4X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_4X              |
                                   (6<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );
                    prot1 = 0x0;
                    prot2 = 0x0;
                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                    gd_sflash_devices[channel].func.GH_SFLASH_set_Data(prot1);
                    gd_sflash_devices[channel].func.GH_SFLASH_set_Data(prot2);

                    // wait the program
                    cmd_bit_set = (0x05                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_READ                  |
                                   SFLASH_CMD_MODE_4X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_4X              |
                                   (1<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );
                    do
                    {
                        gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                        status = gd_sflash_devices[channel].func.GH_SFLASH_get_Data()&0xff;
                    }while((status & 0x80) == 0x80);

                    // ok read the protection bit for each block
                    cmd_bit_set = (0x72                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_READ                  |
                                   SFLASH_CMD_MODE_4X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_4X              |
                                   (6<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );
                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                    prot1 = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();
                    prot2 = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();
                }
                else if(device->manufacture_ID == MXIC_MID)
                {
                    cmd_bit_set = (0x2B                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                   SFLASH_RWN_READ                  |
                                   SFLASH_CMD_MODE_1X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_1X              |
                                   (1<<SFLASH_TRANSFER_BYTE_LOC)    |
                                   SFLASH_HOLD_TIME_100ns
                                  );

                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                    status = gd_sflash_devices[channel].func.GH_SFLASH_get_Data() & 0xff;
                    if((status&0x80) == 0x80)
                    {
                        gd_sflash_devices[channel].func.GH_SFLASH_set_Command(device->commands->write_enable);
                        gd_sflash_devices[channel].func.GH_SFLASH_get_Data();
                        cmd_bit_set = (0x05                             |
                                       SFLASH_SEND_CMD                  |
                                       SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                       SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                       SFLASH_RWN_READ                  |
                                       SFLASH_CMD_MODE_1X               |
                                       SFLASH_ADDR_MODE_1X              |
                                       SFLASH_DATA_MODE_1X              |
                                       (1<<SFLASH_TRANSFER_BYTE_LOC)    |
                                       SFLASH_HOLD_TIME_100ns
                                      );
                        do
                        {
                            gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                            status = gd_sflash_devices[channel].func.GH_SFLASH_get_Data() & 0xff;
                        }while((status&0x01) == 0x01);

                        cmd_bit_set = (0x98                             |
                                       SFLASH_SEND_CMD                  |
                                       SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                       SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                       SFLASH_RWN_NOTHING               |
                                       SFLASH_CMD_MODE_1X               |
                                       SFLASH_ADDR_MODE_1X              |
                                       SFLASH_DATA_MODE_1X              |
                                       (0<<SFLASH_TRANSFER_BYTE_LOC)    |
                                       SFLASH_HOLD_TIME_100ns
                                      );
                        gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                        gd_sflash_devices[channel].func.GH_SFLASH_get_Data();
                        cmd_bit_set = (0x05                             |
                                       SFLASH_SEND_CMD                  |
                                       SFLASH_SEND_ADDR_BYTE_NUM_0      |
                                       SFLASH_SEND_DUMMY_BYTE_NUM_0     |
                                       SFLASH_RWN_READ                  |
                                       SFLASH_CMD_MODE_1X               |
                                       SFLASH_ADDR_MODE_1X              |
                                       SFLASH_DATA_MODE_1X              |
                                       (1<<SFLASH_TRANSFER_BYTE_LOC)    |
                                       SFLASH_HOLD_TIME_100ns
                                      );
                        do
                        {
                            gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                            status = gd_sflash_devices[channel].func.GH_SFLASH_get_Data() & 0xff;
                        }while((status & 0x01) == 0x01);
                    }
                    // check if the chip support 4X read mode?
                    cmd_bit_set = (0x5A                             |
                                   SFLASH_SEND_CMD                  |
                                   SFLASH_SEND_ADDR_BYTE_NUM_3      |
                                   SFLASH_SEND_DUMMY_BYTE_NUM_1     |
                                   SFLASH_RWN_READ                  |
                                   SFLASH_CMD_MODE_1X               |
                                   SFLASH_ADDR_MODE_1X              |
                                   SFLASH_DATA_MODE_1X              |
                                   SFLASH_TRANSFER_BYTE_NUM_4       |
                                   SFLASH_HOLD_TIME_100ns
                                  );
                    gd_sflash_devices[channel].func.GH_SFLASH_set_Command(cmd_bit_set);
                    gd_sflash_devices[channel].func.GH_SFLASH_set_Data(0x30);
                    sflash_data = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();
                    // command-address-data
                    // 0x32[bit12]=1:1-2-2
                    // 0x32[bit13]=1:1-4-4
                    // 0x32[bit14]=1:1-1-4
                    // sflash_data=0x30 31 32 33
                    if((sflash_data != 0x00000000) || (sflash_data != 0xFFFFFFFF))
                    {
                        if(sflash_data & 0x00006000)
                        {
                            //device->feature = GD_SFLASH_4X_WRITE |                      GD_SFLASH_1X_WRITE |\
                            //                  GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ  | GD_SFLASH_1X_READ;
                            //printf("support 4X mode read:0x%08x\n", sflash_data);
                        }
                        else
                        {
                            device->feature &= ~(GD_SFLASH_4X_WRITE | GD_SFLASH_2X_WRITE);
                            device->feature &= ~(GD_SFLASH_4X_READ  | GD_SFLASH_2X_READ);
                            //printf("not support 4X mode read:0x%08x\n", sflash_data);
                        }
                    }
                }
                else // SPANSION_MID WINBOND_MID NUMONYX_MID GIGA_MID EON_MID ISSI_MID FIDELIX_MID
                {
                }
            }
            device->feature =  GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ;
            gd_sflash_devices[channel].dev = device;
            gd_sflash_devices[channel].feature = 0x00;
            if((device->feature & GD_SFLASH_4X_READ) == GD_SFLASH_4X_READ)
            {
                if(device->commands->read_io4 == SFLASH_NOT_SUPPORT)
                {
                    if(device->commands->read_io2 == SFLASH_NOT_SUPPORT)
                    {
                        gd_sflash_devices[channel].feature |= GD_SFLASH_1X_READ;
                    }
                    else
                    {
                        gd_sflash_devices[channel].feature |= GD_SFLASH_2X_READ;
                    }
                }
                else
                {
                    gd_sflash_devices[channel].feature |= GD_SFLASH_4X_READ;
                }
            }
            else if((device->feature & GD_SFLASH_2X_READ) == GD_SFLASH_2X_READ)
            {
                if(device->commands->read_io2 == SFLASH_NOT_SUPPORT)
                {
                    gd_sflash_devices[channel].feature |= GD_SFLASH_1X_READ;
                }
            }
            else
            {
                gd_sflash_devices[channel].feature |= GD_SFLASH_1X_READ;
            }
            if(device->feature & GD_SFLASH_4X_WRITE)
            {
                if(device->commands->program_page4 == SFLASH_NOT_SUPPORT)
                {
                    if(device->commands->program_page2 == SFLASH_NOT_SUPPORT)
                    {
                        gd_sflash_devices[channel].feature |= GD_SFLASH_1X_WRITE;
                    }
                    else
                    {
                        gd_sflash_devices[channel].feature |= GD_SFLASH_2X_WRITE;
                    }
                }
                else
                {
                    gd_sflash_devices[channel].feature |= GD_SFLASH_4X_WRITE;
                }
            }
            else if((device->feature & GD_SFLASH_2X_WRITE) == GD_SFLASH_2X_WRITE)
            {
                if(device->commands->program_page2 == SFLASH_NOT_SUPPORT)
                {
                    gd_sflash_devices[channel].feature |= GD_SFLASH_1X_WRITE;
                }
            }
            else
            {
                gd_sflash_devices[channel].feature |= GD_SFLASH_1X_WRITE;
            }
#ifdef DEBUG_PRINT
            GM_Printf("[%s] USE %dX mode read and %dX mode write\n",
                gd_sflash_devices[channel].dev->device_name,
                (gd_sflash_devices[channel].feature & 0x0F),
                (gd_sflash_devices[channel].feature & 0xF0) >> 4);
#endif
            gd_sflash_handle[channel]  = &gd_sflash_devices[channel];
            *pHandle = (GD_HANDLE)(void*)gd_sflash_handle[channel];

            GD_SFLASH_Unlock(*pHandle);

            // Set to BUF 1 mode
            if((device->type == GD_SPI_NAND) &&
               (device->manufacture_ID == WINBOND_MID))
            {
                // 1. read out the status firstly
                gd_sflash_devices[channel].func.GH_SFLASH_set_Command(device->commands->read_status);
                gd_sflash_devices[channel].func.GH_SFLASH_set_Data(0xB0);
                sflash_data = gd_sflash_devices[channel].func.GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
                GM_Printf("GD_SFLASH_EnableIO4\nreadStatus(0xb0):0x%02x\n",sflash_data);
#endif

                // 2. set BUF bit, then write it back into register
                gd_sflash_devices[channel].func.GH_SFLASH_set_Command(device->commands->write_status);
                sflash_data = (sflash_data | 0x08);         // QE[bit0]
                gd_sflash_devices[channel].func.GH_SFLASH_set_Data(0xB0);
                gd_sflash_devices[channel].func.GH_SFLASH_set_Data(sflash_data);
            }
            return(GD_OK);
        }
    }
    return(GD_ERR_SFLASH_TYPE_NOT_SUPPORTED);
}

/*!
********************************************************************************
**
** \brief Closes a serial flash driver instance
**
** This function closes an open instance of the serial flash driver
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_Close(GD_HANDLE* pHandle)
{
    GD_SFLASH_HANDLE_S* device;
    if(!pHandle)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    device = (GD_SFLASH_HANDLE_S*)(void*)(*pHandle);
    if(device != gd_sflash_handle[device->channel])
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    gd_sflash_handle[device->channel] = NULL;
    *pHandle = NULL;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief enable the sflash IO4 mdoe
**
** This function make the sflash to receive the IO4 command
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_EnableIO4(GD_HANDLE handle)
{
    U8 status1, status2 = 0;
    U32 data = 0;
    U32 cmd_bit_set = 0;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)(void*)handle;

    if(device == NULL)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(device->dev->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        // after initialization, the SST enter IO4 mode automatically!
        if(device->dev->manufacture_ID == SST_MID)
        {
            return GD_OK;
        }

        if(device->dev->manufacture_ID == EON_MID)
        {
            return GD_OK;
        }
        /* first read the status */
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        status1 = device->func.GH_SFLASH_get_Data() & 0xff;
        if(device->dev->commands->read_status2 != SFLASH_NOT_SUPPORT)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_status2);
            status2 = device->func.GH_SFLASH_get_Data()&0xff;
        }

        /* write enable the device */
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
        device->func.GH_SFLASH_get_Data();

        if((device->dev->manufacture_ID == MXIC_MID) || (device->dev->manufacture_ID == ISSI_MID))
        {
            data = status1|0x40;
        }
        else if((device->dev->manufacture_ID == WINBOND_MID) ||
                (device->dev->manufacture_ID == SPANSION_MID) ||
                (device->dev->manufacture_ID == FIDELIX_MID))
        {
            data = (status1<<8)+(status2|0x2);
        }
        else if(device->dev->manufacture_ID == GIGA_MID)
        {
            data = status2|0x2;
        }
        else // SST_MID NUMONYX_MID EON_MID
        {
            data = status1;
        }
        /* write the status register */
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        device->func.GH_SFLASH_set_Data(data);

        sflash_wip_done_wait(handle);
    }
    else if(device->dev->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        // 1. read out the status firstly
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        device->func.GH_SFLASH_set_Data(0xB0);
        status1 = device->func.GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_EnableIO4\nreadStatus(0xb0):0x%02x\n",status1);
#endif

        // 2. set QE bit, then write it back into register
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        status1 = (status1 | 0x01);                        // QE[bit0]
        device->func.GH_SFLASH_set_Data(0xB0);
        device->func.GH_SFLASH_set_Data(status1);
    }
    return GD_OK;
}

/*!
********************************************************************************
**
** \brief disenable the sflash IO4 mdoe
**
** This function make the sflash to exit the IO4 mode
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_DisableIO4(GD_HANDLE handle)
{
    U8 status1, status2 = 0;
    U32 data = 0;
    U32 cmd_bit_set = 0;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)(void*)handle;

    if(device == NULL)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(device->dev->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        // after initialization, the SST enter IO4 mode automatically!
        // so here simply do nothing at all!
        if(device->dev->manufacture_ID == SST_MID)
        {
            return 0;
        }

        if(device->dev->manufacture_ID == EON_MID)
        {       
            return GD_OK;
        }

        /* first read the status */
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        status1 = device->func.GH_SFLASH_get_Data() & 0xff;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_DisableIO4\nreadStatus(nor):0x%02x\n",status1);
#endif

        if(device->dev->commands->read_status2 != SFLASH_NOT_SUPPORT)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_status2);
            status2 = device->func.GH_SFLASH_get_Data()&0xff;
        }

        /* write enable the device */
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
        device->func.GH_SFLASH_get_Data();

        if((device->dev->manufacture_ID == MXIC_MID) || (device->dev->manufacture_ID == ISSI_MID))
        {
            //Steven Yu: // clear quad
            //for GK workaround do not enable reset mode otherwise code can not bootup
            //data = status1&(~0x40);                                  /*clear quad*/
            //write back status1
            data = status1;
        }
        else if((device->dev->manufacture_ID == WINBOND_MID) ||
                (device->dev->manufacture_ID == SPANSION_MID) ||
                (device->dev->manufacture_ID == FIDELIX_MID))
        {
            data = (status1<<8)+ (status2 & (~0x2));                 /*clear the quad*/
        }
        else if(device->dev->manufacture_ID == GIGA_MID)
        {
            data = status2 & (~0x2);
        }
        else // SST_MID NUMONYX_MID EON_MID
        {
            data = status1;
        }

        /* write the status register */
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        device->func.GH_SFLASH_set_Data(data);

        sflash_wip_done_wait(handle);
    }
    else if(device->dev->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        // 1. read out the status firstly
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        device->func.GH_SFLASH_set_Data(0xB0);
        status1 = device->func.GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_DisableIO4\nreadStatus(0xb0):0x%02x\n",status1);
#endif

        // 2. clear QE bit, then write it back into register
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        status1 = (status1 & 0xfe);                        // QE[bit0]
        device->func.GH_SFLASH_set_Data(0xB0);
        device->func.GH_SFLASH_set_Data(status1);
    }
    return GD_OK;
}

static GERR sflash_set_ext_addr(GD_HANDLE handle, U8 offset)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U8 extadd = 0;

    sflash_write_enable(handle);

    device->func.GH_SFLASH_set_Command(device->dev->commands->read_ext_addr);
    extadd = device->func.GH_SFLASH_get_Data();
    if(offset == extadd)
    {
        return 0;
    }

    sflash_write_enable(handle);

    device->func.GH_SFLASH_set_Command(device->dev->commands->write_ext_addr);
    device->func.GH_SFLASH_set_Data(offset);
    return 0;
}

/*!
********************************************************************************
**
** \brief Reads serial flash data by IO1 mode
**  This function is called by GD_SFLASH_Read()
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start reading at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to store the read data
** \param words   The number of long words to read from the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
********************************************************************************
*/
static GERR GD_SFLASH_ReadIO1(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    SFLASH_get_Data get_Data;
    get_Data = device->func.GH_SFLASH_get_Data;

    if(address >= GD_SFLASH_16M_SIZE)
    {
        sflash_set_ext_addr(handle, address/GD_SFLASH_16M_SIZE);
    }
    device->func.GH_SFLASH_set_Command(device->dev->commands->read_data);
    device->func.GH_SFLASH_set_Data(address);
    while(words--)
    {
        *buffer++ = get_Data();
    }
    if(address >= GD_SFLASH_16M_SIZE)
    {
        //restore to 0x00
        sflash_set_ext_addr(handle, 0x00);
    }
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Reads serial flash data by IO2 mode
**  This function is called by GD_SFLASH_Read()
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start reading at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to store the read data
** \param words   The number of long words to read from the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
********************************************************************************
*/
static GERR GD_SFLASH_ReadIO2(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    SFLASH_get_Data get_Data;
    get_Data = device->func.GH_SFLASH_get_Data;

    if(address >= GD_SFLASH_16M_SIZE)
    {
        sflash_set_ext_addr(handle, address/GD_SFLASH_16M_SIZE);
    }
    device->func.GH_SFLASH_set_Command(device->dev->commands->read_io2);
    device->func.GH_SFLASH_set_Data(address);

    while(words--)
    {
        *buffer++ = get_Data();
    }
    if(address >= GD_SFLASH_16M_SIZE)
    {
        //restore to 0x00
        sflash_set_ext_addr(handle, 0x00);
    }
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Reads serial flash data by IO4 mode
**  This function is called by GD_SFLASH_Read()
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start reading at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to store the read data
** \param words   The number of long words to read from the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
********************************************************************************
*/
static GERR GD_SFLASH_ReadIO4(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GERR result = GD_OK;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    SFLASH_get_Data get_Data;
    get_Data = device->func.GH_SFLASH_get_Data;

    if(address >= GD_SFLASH_16M_SIZE)
    {
        sflash_set_ext_addr(handle, address/GD_SFLASH_16M_SIZE);
    }

    device->func.GH_SFLASH_set_Command(device->dev->commands->read_io4);
    device->func.GH_SFLASH_set_Data(address);

    sflashEnableIO4Hw(handle,GTRUE);
    while(words--)
    {
        *buffer++ = get_Data();
    }
    sflashEnableIO4Hw(handle,GFALSE);

    if(address >= GD_SFLASH_16M_SIZE)
    {
        //restore to 0x00
        sflash_set_ext_addr(handle, 0x00);
    }
    return result;
}

/*!
********************************************************************************
**
** \brief Reads serial flash data
**
** This function reads data from the serial flash into the given data buffer.
** The function starts reading at the given byte address which should be long
** word aligned, internally this address will be masked by 0xFFFFFFFC.
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start reading at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to store the read data
** \param words   The number of long words to read from the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_Read(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GERR gerr = GD_OK;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 CESetting = 0x0E;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    address &= 0xFFFFFFFC;

    if((address + (sizeof(U32) * words) - 4) >= device->dev->device_bytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!buffer)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    CESetting = CESetting | ((U32)device->channel << 6);//0x0000004E
    device->func.GH_SFLASH_set_CE(CESetting);

    //////////////////////////////////////////
    // Steven Yu:Add code for winband W25M161AV=W25Q16JV+W25N01GV
    if(device->dev->commbo &&
      (device->dev->commands->die_sel != SFLASH_NOT_SUPPORT))
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->die_sel);
        device->func.GH_SFLASH_set_Data(device->devicechannel);
    }
    //////////////////////////////////////////
#if 0 // all flash 1X read by xiahong    
    if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO4)
        {
            old_feature = GD_SFLASH_FEATURE_IO4;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_EnableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else if((device->feature & 0x0F) == GD_SFLASH_2X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO2)
        {
            old_feature = GD_SFLASH_FEATURE_IO2;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_DisableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else if((device->feature & 0x0F) == GD_SFLASH_1X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO1)
        {
            old_feature = GD_SFLASH_FEATURE_IO1;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_DisableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else
    {
        gerr = GD_ERR_SFLASH_TYPE_NOT_SUPPORTED;
    }
#else
    if(old_feature != GD_SFLASH_FEATURE_IO1)
    {
        old_feature = GD_SFLASH_FEATURE_IO1;
        if(device->dev->manufacture_ID != NUMONYX_MID)
        {
            gerr = GD_SFLASH_DisableIO4(handle);                 /*enable the IO4 mode*/
        }
        if(gerr != 0)
        {
            return gerr;
        }
    }
#endif 

    if(device->dev->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            gerr = GD_SFLASH_ReadIO4(handle, address, buffer, words);
        }
        else if((device->feature & 0x0F) == GD_SFLASH_2X_READ)
        {
            gerr = GD_SFLASH_ReadIO2(handle, address, buffer, words);
        }
        else if((device->feature & 0x0F) == GD_SFLASH_1X_READ)
        {
            gerr = GD_SFLASH_ReadIO1(handle, address, buffer, words);
        }
        else
        {
            gerr = GD_ERR_SFLASH_TYPE_NOT_SUPPORTED;
        }
    }
    else if(device->dev->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        U32 startAddr, endAddr, startPage, endPage;
        startPage   = address / device->dev->page_bytes;
        startAddr   = address % device->dev->page_bytes;
        endPage     = (address + words * 4) / device->dev->page_bytes;
        endAddr     = (address + words * 4) % device->dev->page_bytes;
        spiNandFlashRead(handle, buffer, startPage, startAddr, endPage, endAddr);
    }

    CESetting = CESetting & (~((U32)device->channel << 6));
    device->func.GH_SFLASH_set_CE(CESetting);

    return gerr;
}

/*!
********************************************************************************
**
** \brief Writes serial flash data
**
** This function writes data to the serial flash from the given data buffer.
** The function starts writing at the given byte address which should be long
** word aligned, internally this address will be masked by 0xFFFFFFFC.
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start writing at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to read data from
** \param words   The number of long words to write into the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
** \note This function assumes that the serial flash is ready to be get
**       written, it does not check whether the sectors to write to are
**       empty.
**
** \note This function acts as a low level serial flash write function
**       used by the more user friendly function GD_SFLASH_Program
**
********************************************************************************
*/
GERR GD_SFLASH_WriteIO1(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 count;
    U32 pageWords;
    U32 writeWords = words;
    U32 extadd = 0;
    GERR result = GD_ERR_SFLASH_WRITE;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)device->func.GH_SFLASH_set_Data;

    pageWords = device->dev->page_bytes / sizeof(U32);
    count = 0;

    while(writeWords--)
    {
        if(count == 0)
        {
            // >16MB
            if((extadd == 0) && (address >= GD_SFLASH_16M_SIZE))
            {
                extadd = 1;
                sflash_set_ext_addr(handle, address/GD_SFLASH_16M_SIZE);
            }
            //
            // issue a write command sequence to prepare
            // the device for data to be written
            //
            device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
            device->func.GH_SFLASH_get_Data();

            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page);
            device->func.GH_SFLASH_set_Data(address);
        }
        set_Data(*buffer++);
        count++;
        address += 4;

        if((address % device->dev->page_bytes) == 0)
        {
            //
            // we are at a page boundary so we have to
            // wait until the WIP status to be cleared
            // by the device
            //
            result = sflash_wip_done_wait(handle);

            if(result != GD_OK)
                break;

            count = 0;
        }
    }

    // new added for the case that words < pageWords
    if(words < pageWords)
    {
        result = sflash_wip_done_wait(handle);
        if(result != GD_OK)
        {
            return(result);
        }
    }
    if(extadd)
    {
        //restore to 0x00
        sflash_set_ext_addr(handle, 0x00);
    }

    device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
    device->func.GH_SFLASH_get_Data();
    return(result);
}

/*!
********************************************************************************
**
** \brief Writes serial flash data
**
** This function writes data to the serial flash from the given data buffer.
** The function starts writing at the given byte address which should be long
** word aligned, internally this address will be masked by 0xFFFFFFFC.
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start writing at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to read data from
** \param words   The number of long words to write into the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
** \note This function assumes that the serial flash is ready to be get
**       written, it does not check whether the sectors to write to are
**       empty.
**
** \note This function acts as a low level serial flash write function
**       used by the more user friendly function GD_SFLASH_Program
**
********************************************************************************
*/
GERR GD_SFLASH_WriteIO2(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 count;
    U32 pageWords;
    U32 writeWords = words;
    U32 extadd = 0;
    GERR result = GD_ERR_SFLASH_WRITE;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)device->func.GH_SFLASH_set_Data;

    pageWords = device->dev->page_bytes / sizeof(U32);
    count = 0;
    while(writeWords--)
    {
        if(count == 0)
        {
            // >16MB
            if((extadd == 0) && (address >= GD_SFLASH_16M_SIZE))
            {
                extadd = 1;
                sflash_set_ext_addr(handle, address/GD_SFLASH_16M_SIZE);
            }
            //
            // issue a write command sequence to prepare
            // the device for data to be written
            //
            device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
            device->func.GH_SFLASH_get_Data();

            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page2);
            device->func.GH_SFLASH_set_Data(address);
        }
        set_Data(*buffer++);
        count++;
        address += 4;

        if((address % device->dev->page_bytes) == 0)
        {
            //
            // we are at a page boundary so we have to
            // wait until the WIP status to be cleared
            // by the device
            //
            result = sflash_wip_done_wait(handle);
            if(result != GD_OK)
                break;

            count = 0;
        }
    }

    // new added for the case that words < pageWords
    if(words < pageWords)
    {
        result = sflash_wip_done_wait(handle);
        if(result != GD_OK)
        {
            return(result);
        }
    }

    device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
    device->func.GH_SFLASH_get_Data();
    return(result);
}

/*!
********************************************************************************
**
** \brief Writes serial flash data
**
** This function writes data to the serial flash from the given data buffer.
** The function starts writing at the given byte address which should be long
** word aligned, internally this address will be masked by 0xFFFFFFFC.
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start writing at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to read data from
** \param words   The number of long words to write into the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
** \note This function assumes that the serial flash is ready to be get
**       written, it does not check whether the sectors to write to are
**       empty.
**
** \note This function acts as a low level serial flash write function
**       used by the more user friendly function GD_SFLASH_Program
**
********************************************************************************
*/
GERR GD_SFLASH_WriteIO4(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 count;
    //U32 pageWords;
    U32 writeWords = words;
    U32 extadd = 0;
    GERR result = GD_ERR_SFLASH_WRITE;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)device->func.GH_SFLASH_set_Data;

    //pageWords = device->dev->page_bytes / sizeof(U32);
    count = 0;
    while(writeWords--)
    {
        if(count == 0)
        {
            // >16MB
            if((extadd == 0) && (address >= GD_SFLASH_16M_SIZE))
            {
                extadd = 1;
                sflash_set_ext_addr(handle, address/GD_SFLASH_16M_SIZE);
            }
            //
            // issue a write command sequence to prepare
            // the device for data to be written
            //
            device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
            device->func.GH_SFLASH_get_Data();

            device->func.GH_SFLASH_set_Command(device->dev->commands->program_page4);
            device->func.GH_SFLASH_set_Data(address);
            sflashEnableIO4Hw(handle,GTRUE);
        }

        set_Data(*buffer++);
        count++;
        address += 4;

        if((address % device->dev->page_bytes) == 0)
        {
            sflashEnableIO4Hw(handle,GFALSE);
            //
            // we are at a page boundary so we have to
            // wait until the WIP status to be cleared
            // by the device
            //
            result = sflash_wip_done_wait(handle);
            if(result != GD_OK)
                break;

            count = 0;
            sflashEnableIO4Hw(handle,GTRUE);
        }
    }
    sflashEnableIO4Hw(handle,GFALSE);
    // new added for the case that words < pageWords
    //if(words < pageWords)
    {
        result = sflash_wip_done_wait(handle);
        if(result != GD_OK)
        {
            return(result);
        }
    }
    device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
    device->func.GH_SFLASH_get_Data();
    return(result);
}

/*!
********************************************************************************
**
** \brief Writes serial flash data
**
** This function writes data to the serial flash from the given data buffer.
** The function starts writing at the given byte address which should be long
** word aligned, internally this address will be masked by 0xFFFFFFFC.
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start writing at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to read data from
** \param words   The number of long words to write into the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
** \note This function assumes that the serial flash is ready to be get
**       written, it does not check whether the sectors to write to are
**       empty.
**
** \note This function acts as a low level serial flash write function
**       used by the more user friendly function GD_SFLASH_Program
**
********************************************************************************
*/
GERR GD_SFLASH_Write(GD_HANDLE handle, U32 address, U32* buffer, U32 words)
{
    GERR gerr = GD_OK;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 CESetting = 0x0E;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    address &= 0xFFFFFFFC;

    if((address + (sizeof(U32) * words) - 4) >= device->dev->device_bytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!buffer)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    CESetting = CESetting | ((U32)device->channel << 6);
    device->func.GH_SFLASH_set_CE(CESetting);

    //////////////////////////////////////////
    // Steven Yu:Add code for winband W25M161AV=W25Q16JV+W25N01GV
    if(device->dev->commbo &&
      (device->dev->commands->die_sel != SFLASH_NOT_SUPPORT))
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->die_sel);
        device->func.GH_SFLASH_set_Data(device->devicechannel);
    }
    //////////////////////////////////////////
    if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO4)
        {
            old_feature = GD_SFLASH_FEATURE_IO4;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_EnableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else if((device->feature & 0xF0) == GD_SFLASH_2X_WRITE)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO2)
        {
            old_feature = GD_SFLASH_FEATURE_IO2;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_DisableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else if((device->feature & 0xF0) == GD_SFLASH_1X_WRITE)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO1)
        {
            old_feature = GD_SFLASH_FEATURE_IO1;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_DisableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else
    {
        gerr = GD_ERR_SFLASH_TYPE_NOT_SUPPORTED;
    }
    if(device->dev->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        if((device->feature & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            gerr = GD_SFLASH_WriteIO4(handle, address, buffer, words);
        }
        else if((device->feature & 0xF0) == GD_SFLASH_2X_WRITE)
        {
            gerr = GD_SFLASH_WriteIO2(handle, address, buffer, words);
        }
        else if((device->feature & 0xF0) == GD_SFLASH_1X_WRITE)
        {
            gerr = GD_SFLASH_WriteIO1(handle, address, buffer, words);
        }
        else
        {
            gerr = GD_ERR_SFLASH_TYPE_NOT_SUPPORTED;
        }
    }
    else if(device->dev->type == GD_SPI_NAND)                            // check if spi-nand flash
    {
        U32 startAddr, endAddr, startPage, endPage;
        startPage   = address / device->dev->page_bytes;
        startAddr   = address % device->dev->page_bytes;
        endPage     = (address + words * 4) / device->dev->page_bytes;
        endAddr     = (address + words * 4) % device->dev->page_bytes;

        gerr        = spiNandFlashWrite(handle, buffer, startPage, startAddr, endPage, endAddr);
    }

    CESetting = CESetting & (~((U32)device->channel << 6));
    device->func.GH_SFLASH_set_CE(CESetting);

    return gerr;
}

/*!
********************************************************************************
**
** \brief Writes serial flash data
**
** This function programs data to the serial flash from the given data buffer.
** The function starts writing at the given byte address which should be long
** word aligned, internally this address will be masked by 0xFFFFFFFC.
** The difference to the function GD_SFLASH_Write is that this function first
** buffers the current serial flash sector contents before overwriting it.
**
** \param handle  The handle describing an opened serial flash device
** \param address The address to start writing at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial flash device
** \param buffer  The adress of a data buffer where to read data from
** \param words   The number of long words to write into the serial flash
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     flash memory
** - GD_OK if successfull
**
** \note This function assumes that the serial flash is ready to be get
**       written, it does not check whether the sectors to write to are
**       empty.
**
** \note This function acts as a low level serial flash write function
**       used by the more user friendly function GD_SFLASH_Program
**
********************************************************************************
*/
GERR GD_SFLASH_Program( GD_HANDLE handle, U32 address, U32* buffer, U32 words )
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 offset;
    U32 index;
    U32 sectorAddress = 0;
    U16 sectorFirst   = 0;
    U16 sectorLast    = 0;
    U16 sectorIndex   = 0;
    U32 sectorWords   = 0;
    U32 *temp_data   ;
    U32 *writebuf ;
    U32 writelen = 0 ;
    GBOOL isEmpty;
    GERR result;

    if( !device )
        return( GD_ERR_INVALID_HANDLE );

    address &= 0xFFFFFFFC;

    if( ( address + ( words * sizeof(U32) - 4 ) ) >= device->dev->device_bytes )
        return( GD_ERR_BAD_PARAMETER );

    if( !buffer )
        return( GD_ERR_BAD_PARAMETER );

    if( device->dev->sector_bytes > sizeof(gd_flash_sector_buffer) )
        return( GD_ERR_OUT_OF_MEMORY );

    result = GD_SFLASH_GetSector( handle, address, &sectorFirst );
    if( result != GD_OK )
        return( result );

    offset = (words-1) * sizeof(U32);
    result = GD_SFLASH_GetSector( handle, address+offset, &sectorLast );
    if( result != GD_OK )
        return( result );

    for( sectorIndex=sectorFirst; sectorIndex <= sectorLast; sectorIndex++ )
    {
        result = GD_SFLASH_GetSectorAddress( handle, sectorIndex, &sectorAddress );
        if( result != GD_OK )
            return( result );

        result = GD_SFLASH_GetSectorSize( handle, sectorIndex, &sectorWords );
        if( result != GD_OK )
            return( result );

        if( sectorFirst == sectorLast )
        {
            //
            // copy only 'words' data from the start address
            // all within the first sector
            //
            result = GD_SFLASH_Read( handle, sectorAddress, gd_flash_sector_buffer, sectorWords );
            if( result != GD_OK )
                return( GD_ERR_SFLASH_READ );

            offset = ( address - sectorAddress ) / sizeof(U32);
            index=0;

            writebuf=buffer;
            writelen=words;

            isEmpty = GTRUE;
            while( words-- )
            {
                temp_data = &gd_flash_sector_buffer[offset+index];

                if(isEmpty == GTRUE)
                {
                    if( *temp_data != 0xFFFFFFFF )
                    {
                        writebuf=gd_flash_sector_buffer;
                        writelen=sectorWords;
                        isEmpty = GFALSE;
                    }
                }
                *temp_data = *buffer++;
                index++;
            }
            if(isEmpty)
            {
                sectorAddress = address;
            }
        }
        else if( sectorIndex == sectorFirst )
        {
            //
            // copy only data from the start address
            // up to the end of the first sector
            //
            result = GD_SFLASH_Read( handle, sectorAddress, gd_flash_sector_buffer, sectorWords );
            if( result != GD_OK )
                return( GD_ERR_SFLASH_READ );

            offset = ( address - sectorAddress ) / sizeof(U32);
            writebuf=buffer;
            writelen=sectorWords-offset;

            isEmpty = GTRUE;
            for( index=0; index < writelen; index++ )
            {
                temp_data = &gd_flash_sector_buffer[offset+index];
                if(isEmpty == GTRUE)
                {
                    if( *temp_data != 0xFFFFFFFF )
                    {
                        writebuf=gd_flash_sector_buffer;
                        writelen=sectorWords;
                        isEmpty = GFALSE;
                    }
                }
                *temp_data = *buffer++;
                words--;
            }
            if(isEmpty == GTRUE)
            {
                sectorAddress = address;
            }

        }
        else if( sectorIndex == sectorLast )
        {
            result = GD_SFLASH_Read( handle, sectorAddress, gd_flash_sector_buffer, sectorWords );
            if( result != GD_OK )
                return( GD_ERR_SFLASH_READ );

            writebuf=gd_flash_sector_buffer;
            writelen=words;


            isEmpty = GTRUE;
            for( index=0; words > 0; index++ )
            {
                temp_data = &gd_flash_sector_buffer[index];

                if(isEmpty == GTRUE)
                {
                    if( *temp_data != 0xFFFFFFFF )
                    {
                        writelen=sectorWords;
                        isEmpty = GFALSE;
                    }
                }
                *temp_data = *buffer++;
                words--;
            }
        }
        else
        {
            writebuf=buffer;
            writelen=sectorWords;

            buffer +=sectorWords;
            words -=sectorWords;

            isEmpty = GTRUE;
            result = GD_SFLASH_IsSectorEmpty( handle, sectorIndex, &isEmpty );
            if( result != GD_OK )
                isEmpty = GFALSE;
        }
        if( !isEmpty )
        {
            result = GD_SFLASH_EraseSector( handle, sectorIndex );
            if( result != GD_OK )
                return( result );
        }
        result = GD_SFLASH_Write( handle, sectorAddress, writebuf, writelen );
        if( result != GD_OK )
            return( GD_ERR_SFLASH_READ );
    }
    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Erase the entire serial flash device memory
**
** This function erases the entire flash device memory.
**
** \param handle  The handle describing an opened serial flash device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_SFLASH_ERASE if the bulk erase command has failed
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_EraseChip(GD_HANDLE handle)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    GERR result;
    U32 CESetting = 0x38;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    // so far spi-nand chip of Micro and Giga-Device hasn't such feature
    if(device->dev->commands->erase_chip == SFLASH_NOT_SUPPORT)
    {
        return(GD_ERR_SFLASH_TYPE_NOT_SUPPORTED);
    }
    //////////////////////////////////////////
    // Steven Yu:Add code for winband W25M161AV=W25Q16JV+W25N01GV
    if(device->dev->commbo &&
      (device->dev->commands->die_sel != SFLASH_NOT_SUPPORT))
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->die_sel);
        device->func.GH_SFLASH_set_Data(device->devicechannel);
    }
    CESetting = CESetting | ((U32)device->channel << 6);
    device->func.GH_SFLASH_set_CE(CESetting);

    device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);

    device->func.GH_SFLASH_get_Data();

    device->func.GH_SFLASH_set_Command(device->dev->commands->erase_chip);
    device->func.GH_SFLASH_set_Data(0);

    result = sflash_wip_done_wait( handle );

    device->func.GH_SFLASH_set_Command(device->dev->commands->write_disable);

    device->func.GH_SFLASH_get_Data();

    return(result);
}

/*!
********************************************************************************
**
** \brief Erase a serial flash sector
**
** This function erases the given serial flash sector.
**
** \param handle      The handle describing an opened serial flash device
** \param sectorIndex The index of the sector to erase, indexing starts with 0.
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sector index is out of range of the
**     available serial flash sectors [0..sector_count-1].
** - GD_ERR_SFLASH_ERASE if the bulk erase command has failed
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_EraseSector(GD_HANDLE handle, U16 sectorIndex)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 address     = 0;
    GERR result;
    U32 CESetting = 0x38;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(sectorIndex >= device->dev->sector_count)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    result = GD_SFLASH_GetSectorAddress(handle, sectorIndex, &address);
    if(result != GD_OK)
    {
        return(result);
    }

    CESetting = CESetting | ((U32)device->channel << 6);
    device->func.GH_SFLASH_set_CE(CESetting);
    //////////////////////////////////////////
    // Steven Yu:Add code for winband W25M161AV=W25Q16JV+W25N01GV
    if(device->dev->commbo &&
      (device->dev->commands->die_sel != SFLASH_NOT_SUPPORT))
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->die_sel);
        device->func.GH_SFLASH_set_Data(device->devicechannel);
    }
    //////////////////////////////////////////
    if(device->dev->type == GD_SPI_NOR)                        // check if spi-nor flash
    {
        // >16MB
        if(address >= GD_SFLASH_16M_SIZE)
        {
            sflash_set_ext_addr(handle, address/GD_SFLASH_16M_SIZE);
        }
        if(old_feature == GD_SFLASH_FEATURE_IO4)
        {
            old_feature = GD_SFLASH_FEATURE_IO1;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                GD_SFLASH_DisableIO4(handle);               /*disable the IO4 mode*/
            }
        }

        sflash_write_enable(handle);

        device->func.GH_SFLASH_set_Command(device->dev->commands->erase_sector);
        device->func.GH_SFLASH_set_Data(address);

        result = sflash_wip_done_wait(handle);

        if(address >= GD_SFLASH_16M_SIZE)
        {
            //restore to 0x00
            sflash_set_ext_addr(handle, 0x00);
        }

        device->func.GH_SFLASH_set_Command(device->dev->commands->write_disable);
        device->func.GH_SFLASH_get_Data();
    }
    else if(device->dev->type == GD_SPI_NAND)                  // check if spi-nand flash
    {
        result = spiNandFlashEraseSector(handle, address);
    }

    CESetting = CESetting & (~((U32)device->channel << 6));
    device->func.GH_SFLASH_set_CE(CESetting);
    return(result);
}

/*!
********************************************************************************
**
** \brief Retrieve manufactor id and device id
**
** This function returns the manufactor id and the device id of the serial
** flash device initialized by the function GD_SFLASH_Init().
**
** \param handle        The handle describing an opened serial flash device
** \param manufacture_ID The address of a variable where to write the manufactor
**                        id into
** \param device_ID      The address of a variable where to write the device
**                        id into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given manufacture_ID points to 0
** - GD_ERR_BAD_PARAMETER if the given device_ID points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetCodes(GD_HANDLE handle, U8* manufacture_ID, U16* device_ID)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!manufacture_ID)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!device_ID)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *manufacture_ID = device->dev->manufacture_ID;
    *device_ID = device->dev->device_ID;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve manufactor name and device name
**
** This function returns the manufactor name and the device name of the serial
** flash device initialized by the function GD_SFLASH_Init().
**
** \param handle          The handle describing an opened serial flash device
** \param manufacture_name The address of a string pointer variable where to
**                          write the address to the manufactor name into
** \param device_name      The address of a string pointer variable where to
**                          write the address to the device name into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given manufacture_name points to 0
** - GD_ERR_BAD_PARAMETER if the given device_name points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetNames(GD_HANDLE handle, char** manufacture_name, char** device_name)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!manufacture_name)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!device_name)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *manufacture_name = device->dev->manufacture_name;
    *device_name = device->dev->device_name;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the sector count
**
** This function returns the number of sectors of the serial
** flash device initialized by the function GD_SFLASH_Init().
**
** \param handle      The handle describing an opened serial flash device
** \param sector_count The address of a variable where to write the resulting
**                      count into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sector_count points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetNumberOfSectors(GD_HANDLE handle, U16* sector_count)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!sector_count)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    *sector_count = device->dev->sector_count;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the start address of a sector
**
** This function returns the start address of the serial flash device sector
** given by sectorIndex.
**
** \param handle        The handle describing an opened serial flash device
** \param sectorIndex   The index of the sector to find the start address of                     count into
** \param sectorAddress The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorAddress points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex is out of range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetSectorAddress(GD_HANDLE handle, U16 sectorIndex, U32* sectorAddress)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!sectorAddress)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(sectorIndex >= device->dev->sector_count)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    *sectorAddress = sectorIndex * device->dev->sector_bytes;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the size of a given sector in long words
**
** This function returns the size of the serial flash device sector
** given by sectorIndex. The returned value is in long words not in bytes.
**
** \param handle        The handle describing an opened serial flash device
** \param sectorIndex   The index of the sector to find the start address of                     count into
** \param sectorWords   The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorWords points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex is out of range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetSectorSize(GD_HANDLE handle, U16 sectorIndex, U32* sectorWords)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(sectorIndex >= device->dev->sector_count)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!sectorWords)
        return(GD_ERR_BAD_PARAMETER);

    *sectorWords = device->dev->sector_bytes / sizeof(U32);
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the sector index of a given serial flash address
**
** This function returns the sector index for the given serial flash address.
**
** \param handle        The handle describing an opened serial flash device
** \param sectorIndex   The index of the sector to find the start address of                     count into
** \param sectorWords   The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex points to 0
** - GD_ERR_BAD_PARAMETER if the given address is out of the memory range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetSector(GD_HANDLE handle, U32 address, U16* sectorIndex)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(address >= device->dev->device_bytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!sectorIndex)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *sectorIndex = address / device->dev->sector_bytes;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the size of the serial flash device in long words
**
** This function returns the size of the serial flash device specified by the
** given handle. The size is returned in long words not in bytes.
**
** \param handle        The handle describing an opened serial flash device
** \param deviceWords   The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex points to 0
** - GD_ERR_BAD_PARAMETER if the given address is out of the memory range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetSize(GD_HANDLE handle, U32* deviceWords)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!deviceWords)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *deviceWords = device->dev->device_bytes / sizeof(U32);
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Check if the serial device memory is empty
**
** This function checks if the entire serial flash memory is empty, meaning
** all memory words are set to 0xFFFFFFFF.
**
** \param handle    The handle describing an opened serial flash device
** \param isEmpty   The address of a variable where to write the resulting
**                        flag value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given isEmpty points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_IsChipEmpty(GD_HANDLE handle, GBOOL* isEmpty)
{
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U16 sectorIndex;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!isEmpty)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *isEmpty = GTRUE;
    for(sectorIndex=0; sectorIndex < device->dev->sector_count; sectorIndex++)
    {
        GD_SFLASH_IsSectorEmpty(handle, sectorIndex, isEmpty);
        if(*isEmpty == GFALSE)
            break;
    }
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Check if a sector of the serial device memory is empty
**
** This function checks if the given sector within the serial flash memory is
** empty, meaning all memory words are set to 0xFFFFFFFF. Sector indexing
** starts with 0.
**
** \param handle    The handle describing an opened serial flash device
** \param isEmpty   The address of a variable where to write the resulting
**                        flag value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given isEmpty points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex is out of range of serial
**     flash device sectors
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_IsSectorEmpty(GD_HANDLE handle, U16 sectorIndex, GBOOL* isEmpty)
{
    GERR gerr;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 words;
    int i;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(sectorIndex >= device->dev->sector_count)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!isEmpty)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO4)
        {
            old_feature = GD_SFLASH_FEATURE_IO4;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_EnableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else if((device->feature & 0x0F) == GD_SFLASH_2X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO2)
        {
            old_feature = GD_SFLASH_FEATURE_IO2;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_DisableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    else if((device->feature & 0x0F) == GD_SFLASH_1X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO1)
        {
            old_feature = GD_SFLASH_FEATURE_IO1;
            if(device->dev->manufacture_ID != NUMONYX_MID)
            {
                gerr = GD_SFLASH_DisableIO4(handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
    }
    if(device->dev->type == GD_SPI_NOR)                          // check if spi-nor flash
    {
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_io4);
        }
        else if((device->feature & 0x0F) == GD_SFLASH_2X_READ)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_io2);
        }
        else
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_data);
        }
        device->func.GH_SFLASH_set_Data(sectorIndex * device->dev->sector_bytes);

        words = device->dev->sector_bytes / sizeof(U32);
        *isEmpty = GTRUE;
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }
        while(*isEmpty && words--)
        {
            if(device->func.GH_SFLASH_get_Data() != 0xFFFFFFFF)
            {
                *isEmpty = GFALSE;
                break;
            }
        }
        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }

        if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
        {
            if(device->dev->manufacture_ID == NUMONYX_MID)
            {
                sflash_wip_done_wait(handle);
            }
        }
    }
    else if(device->dev->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        for(i=0;i<device->dev->sector_pages;i++)
        {
            // 1. page read to cache
            device->func.GH_SFLASH_set_Command(device->dev->commands->page_read);
            device->func.GH_SFLASH_set_Data(sectorIndex * device->dev->sector_pages + i);

            // 2. check if page read is done
#ifdef DEBUG_PRINT
            GM_Printf("GD_SFLASH_IsSectorEmpty\n");
#endif
            spiNandFlashOipDoneWait(handle);

            // 3. read from cache
            if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
            {
                device->func.GH_SFLASH_set_Command(device->dev->commands->read_io4);
            }
            else if((device->feature & 0x0F) == GD_SFLASH_2X_READ)
            {
                device->func.GH_SFLASH_set_Command(device->dev->commands->read_io2);
            }
            else
            {
                device->func.GH_SFLASH_set_Command(device->dev->commands->read_data);
            }

            // here always start from 0 in the cache
            if(device->dev->manufacture_ID == WINBOND_MID || device->dev->manufacture_ID == GIGA_MID)
            {
                device->func.GH_SFLASH_set_Data(0x00000000);
            }
            else
            {
                device->func.GH_SFLASH_set_Data(0x00004000);      // fixed as 1024*2 wrap
            }

            words = device->dev->page_bytes / sizeof(U32);
            *isEmpty = GTRUE;
            if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
            {
                sflashEnableIO4Hw(handle,GTRUE);
            }
            while(*isEmpty && words--)
            {
                if(device->func.GH_SFLASH_get_Data() != 0xFFFFFFFF)
                {
                    *isEmpty = GFALSE;
                    break;
                }
            }
            if((device->feature & 0x0F) == GD_SFLASH_4X_READ)
            {
                sflashEnableIO4Hw(handle,GFALSE);
            }
        }
    }
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief unlock the serial flash
**
** This function unlock the serial flash.
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_OK if unlock operation successfully
**
********************************************************************************
*/
GERR GD_SFLASH_Unlock(GD_HANDLE handle)
{
    U32 cmd_bit_set = 0;
    U32 sflash_data = 0;
    U32 CESetting = 0x38;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U8 status;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }
    CESetting = CESetting | ((U32)device->channel << 6);
    device->func.GH_SFLASH_set_CE(CESetting);
    if(device->dev->type == GD_SPI_NOR)                          // check if spi-nor flash
    {
        if(device->dev->manufacture_ID == MXIC_MID)
        {
            cmd_bit_set = (0x2B                         |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                          SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                          );
            device->func.GH_SFLASH_set_Command(cmd_bit_set);
            status = device->func.GH_SFLASH_get_Data() & 0xff;
            if((status & 0x80) == 0x80)
            {
                device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
                device->func.GH_SFLASH_get_Data();
                sflash_wip_done_wait(handle);

                cmd_bit_set = (0x98                         |   // command
                              SFLASH_SEND_CMD               |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                              SFLASH_RWN_NOTHING            |   // not read & write
                              SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                              SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                              SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                              (0<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                              );
                device->func.GH_SFLASH_set_Command(cmd_bit_set);
                device->func.GH_SFLASH_get_Data();
                sflash_wip_done_wait(handle);
                return GD_OK;
            }
        }

        sflash_write_enable(handle);

        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        status = device->func.GH_SFLASH_get_Data()& 0xff;
        sflash_data = status;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Unlock\nreadStatus(nor):0x%02x\n",status);
#endif

        if(device->dev->commands->read_status2 != SFLASH_NOT_SUPPORT)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_status2);
            status = device->func.GH_SFLASH_get_Data()& 0xff;
            sflash_data = (sflash_data << 8) + status;
#ifdef DEBUG_PRINT
            GM_Printf("GD_SFLASH_Unlock\nreadStatus(nor):0x%02x\n",status);
#endif
        }

        sflash_write_enable(handle);

        sflash_data &= ~(device->dev->lock_mask);
        if(device->dev->manufacture_ID == SPANSION_MID)
        {
            sflash_data &= 0xFF0A;
            sflash_data |= 0x0024;
        } // MXIC_MID WINBOND_MID SST_MID NUMONYX_MID GIGA_MID EON_MID ISSI_MID FIDELIX_MID

        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        device->func.GH_SFLASH_set_Data(sflash_data);

        sflash_wip_done_wait(handle);
    }
    // here, suppose always unlock all sectors
    else if(device->dev->type == GD_SPI_NAND)                   // check if spi-nor flash
    {
        // 1. read out the status firstly
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        device->func.GH_SFLASH_set_Data(0xA0);
        status = device->func.GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Unlock\nreadStatus(0xa0):0x%02x\n",status);
#endif

        // 2. clear BP2/BP1/BP0, then write it back into register
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        status = (status & 0x87);                        // BP2[bit5], BP1[bit4], BP0[bit3]
        device->func.GH_SFLASH_set_Data(0xA0);
        device->func.GH_SFLASH_set_Data(status);
    }
    CESetting = CESetting & (~((U32)device->channel << 6));
    device->func.GH_SFLASH_set_CE(CESetting);
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief lock the serial flash
**
** This function lock the serial flash.
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_ERR_TIMEOUT if lock operation failed
** - GD_OK if lock operation successfully
**
********************************************************************************
*/
GERR GD_SFLASH_Lock(GD_HANDLE handle)
{
    U32 address     = 0;
    U32 cmd_bit_set   = 0;
    U32 sflash_data  = 0;
    U8 status1, status2 = 0;
    U8 i;

    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }
    // here, suppose always unlock all sectors
    if(device->dev->type == GD_SPI_NOR)                          // check if spi-nor flash
    {
        if(device->dev->manufacture_ID == 0xc2)
        {
            cmd_bit_set = (0x2B                          |   // command
                           SFLASH_SEND_CMD               |   // transfer the command
                           SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                           SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                           SFLASH_RWN_READ               |   // read data
                           SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                           SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                           SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                           (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                           );

            device->func.GH_SFLASH_set_Command(cmd_bit_set);
            status1 = device->func.GH_SFLASH_get_Data() & 0xff;
            if((status1 & 0x80) == 0)
            {
                cmd_bit_set = (0x68                          |   // command
                               SFLASH_SEND_CMD               |   // transfer the command
                               SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                               SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                               SFLASH_RWN_NOTHING            |   // not read & write
                               SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                               SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                               SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                               (0<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                               );
                device->func.GH_SFLASH_set_Command(cmd_bit_set);
                device->func.GH_SFLASH_get_Data();
                sflash_wip_done_wait(handle);
                i = 0;
                while(i < 3)
                {
                    cmd_bit_set = (0x2B                          |   // command
                                   SFLASH_SEND_CMD               |   // transfer the command
                                   SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                                   SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                                   SFLASH_RWN_READ               |   // read data
                                   SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                                   SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                                   SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                                   (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                                   );
                    device->func.GH_SFLASH_set_Command(cmd_bit_set);
                    status1 = device->func.GH_SFLASH_get_Data();
                    if((status1 & 0x80) == 0x80)
                    {
                        break;
                    }
                    i++;
                    sflash_wip_done_wait(handle);
                }
                if(i >= 3)
                {
                    return GD_ERR_TIMEOUT;
                }
            }
            device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
            device->func.GH_SFLASH_get_Data();
            sflash_wip_done_wait(handle);

            cmd_bit_set = (0x98                          |   // command
                           SFLASH_SEND_CMD               |   // transfer the command
                           SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                           SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                           SFLASH_RWN_NOTHING            |   // not read & write
                           SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                           SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                           SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                           (0<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                           );
            device->func.GH_SFLASH_set_Command(cmd_bit_set);
            device->func.GH_SFLASH_get_Data();
            sflash_wip_done_wait(handle);

            for(i=0;i<0x10;i++)
            {
                device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
                device->func.GH_SFLASH_get_Data();
                sflash_wip_done_wait(handle);

                cmd_bit_set = (0x36                          |   // command
                               SFLASH_SEND_CMD               |   // transfer the command
                               SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                               SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                               SFLASH_RWN_NOTHING            |   // not read & write
                               SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                               SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                               SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                               (0<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                               );
                GD_SFLASH_GetSectorAddress(handle, i, &address);
                device->func.GH_SFLASH_set_Command(cmd_bit_set);
                device->func.GH_SFLASH_set_Data(address);
                sflash_wip_done_wait(handle);
            }
            return GD_OK;
        }
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        status1 = device->func.GH_SFLASH_get_Data() & 0xff;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Lock\nreadStatus(nor):0x%02x\n",status1);
#endif

        if(device->dev->commands->read_status2 != SFLASH_NOT_SUPPORT)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_status2);
            status2 = device->func.GH_SFLASH_get_Data() & 0xff;
        }

        /* write enable the device */
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
        device->func.GH_SFLASH_get_Data();

        /* write the status register */
        if(device->dev->manufacture_ID == WINBOND_MID)
        {
            sflash_data = ((status1 | 0x1c) << 8) + status2;
        }
        else if(device->dev->manufacture_ID == SPANSION_MID)              // FL064P
        {
            sflash_data = (((status1 & 0x63) | 0x10) << 8) + ((status2 & 0xa) | 0x25);
        }
        else if(device->dev->manufacture_ID == NUMONYX_MID)              // N25Q128
        {
            sflash_data = 0xff;
        }
        else if(device->dev->manufacture_ID == GIGA_MID)
        {
            sflash_data = (((status1 & 0x3) | 0x30) << 8) + (status2 & 0x86);
        }
        else if(device->dev->manufacture_ID == EON_MID)
        {
            sflash_data = ((status1 & 0xC3) | 0x34);
        }
        else // ATO_MID ISSI_MID SST_MID MXIC_MID ESMT_MID FIDELIX_MID
        {
            sflash_data = status1;
        }
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        device->func.GH_SFLASH_set_Data(sflash_data);

        sflash_wip_done_wait(handle);
    }
    else if(device->dev->type == GD_SPI_NAND)                   // check if spi-nand flash
    {
        // 1. read out the status firstly
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        device->func.GH_SFLASH_set_Data(0xA0);
        status1 = device->func.GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Lock\nreadStatus(0xa0):0x%02x\n",status1);
#endif

        // 2. add BP2/BP1/BP0, then write it back into register
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        status1 = (status1 | 0x78);                        // BP2[bit5], BP1[bit4], BP0[bit3]
        device->func.GH_SFLASH_set_Data(0xA0);
        device->func.GH_SFLASH_set_Data(status1);
    }
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief get lock status of the serial flash
**
** This function return if the serial flash locked or not.
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given isChipLocked points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_IsChipLocked(GD_HANDLE handle, GBOOL* isChipLocked)
{
    U32 address = 0;
    U32 cmd_bit_set;
    U8 status1, status2 = 0;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U8 i = 0;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!isChipLocked)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    cmd_bit_set = 0;

    if(device->dev->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        if(device->dev->manufacture_ID == 0xc2)
        {
            cmd_bit_set = (0x2B                          |   // command
                           SFLASH_SEND_CMD               |   // transfer the command
                           SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                           SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                           SFLASH_RWN_READ               |   // read data
                           SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                           SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                           SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                           (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                          );
            device->func.GH_SFLASH_set_Command(cmd_bit_set);
            status1 = device->func.GH_SFLASH_get_Data() & 0xff;

            if((status1 & 0x80) == 0)
            {
                *isChipLocked = GFALSE;
                return GD_OK;
            }
            cmd_bit_set = (0x3C                          |   // command
                           SFLASH_SEND_CMD               |   // transfer the command
                           SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                           SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                           SFLASH_RWN_READ               |   // read data
                           SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                           SFLASH_ADDR_MODE_1X           |   // set the sflash adr mode
                           SFLASH_DATA_MODE_1X           |   // set the sflash data mode
                           (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                          );
            // totally 16 sectors checked???
            for(i=0;i<0x10;i++)
            {
                GD_SFLASH_GetSectorAddress(handle, i, &address);
                device->func.GH_SFLASH_set_Command(cmd_bit_set);

                device->func.GH_SFLASH_set_Data(address);
                status1 = device->func.GH_SFLASH_get_Data() & 0xff;
                if(status1 == 0x0)
                {
                    *isChipLocked = GFALSE;
                    return GD_OK;
                }
                sflash_wip_done_wait(handle);
            }
            *isChipLocked = GFALSE;
            return GD_OK;
        }
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        status1 = device->func.GH_SFLASH_get_Data() & 0xff;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_IsChipLock\nreadStatus(nor):0x%02x\n",status1);
#endif

        if(device->dev->commands->read_status2 != SFLASH_NOT_SUPPORT)
        {
            device->func.GH_SFLASH_set_Command(device->dev->commands->read_status2);
            status2 = device->func.GH_SFLASH_get_Data() & 0xff;
        }

        if(device->dev->manufacture_ID == GIGA_MID)
        {
            if(((status2 & 0x41) == 0x0) && ((status1 & 0xfc) == 0x30))
            {
                *isChipLocked = GTRUE;
                return GD_OK;
            }
            else
            {
                *isChipLocked = GFALSE;
                return GD_OK;
            }
        }
        else if(device->dev->manufacture_ID == EON_MID)
        {
            if(((status1 & 0x3c) == 0x34))
            {
                *isChipLocked = GTRUE;
                return GD_OK;
            }
            else
            {
                *isChipLocked = GFALSE;
                return GD_OK;
            }
        }
        else if(device->dev->manufacture_ID == SPANSION_MID)
        {
            if(((status2 & 0x25) == 0x25) && ((status1 & 0x9c) == 0x10))
            {
                *isChipLocked = GTRUE;
                return GD_OK;
            }
            else
            {
                *isChipLocked = GFALSE;
                return GD_OK;
            }
        }
        else if(device->dev->manufacture_ID == WINBOND_MID)
        {
            if(((status2 & 0x41) == 0x0) && ((status1 & 0xFC) == 0x30))
            {
                *isChipLocked = GTRUE;
                return GD_OK;
            }
            else
            {
                *isChipLocked = GFALSE;
                return GD_OK;
            }
        }
        else //NUMONYX_MID ATO_MID ISSI_MID SST_MID MXIC_MID ESMT_MID FIDELIX_MID
        {
            *isChipLocked = GFALSE;
            return GD_OK;
        }
    }
    // here, though SPI NAND flash could return different lock status even for each sector
    // just to check if chip fully locked to sync with this function of NOR flash
    else if(device->dev->type == GD_SPI_NAND)                    // check if spi-nor flash
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        device->func.GH_SFLASH_set_Data(0xA0);
        status1 = device->func.GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_IsChipLock\nreadStatus(0xa0):0x%02x\n",status1);
#endif

        if((status1 & 0x38) == 0x38)
        {
            *isChipLocked = GTRUE;
            return GD_OK;
        }
        else if((status1 & 0x38) == 0x00)
        {
            *isChipLocked = GFALSE;
            return GD_OK;
        }
        else
        {
            *isChipLocked = GTRUE;                            // here, actually partially locked
            return GD_OK;
        }
    }
    return GD_OK;
}

/*!
********************************************************************************
**
** \brief get the sflash IO mdoe
**
** This function return the sflash working IO mode
** support
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**        op      Read or Write mode
**        feature  IO mode to get
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetIoMode(GD_HANDLE handle, GD_SFLASH_RW_E op, GD_SFLASH_IO_MODE_E* feature)
{
    U8 temp = 0;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(op == GD_SFLASH_READ)
    {
        temp = device->feature & 0x0F;
    }
    else
    {
        temp = (device->feature & 0xF0) >> 4;
    }

    switch(temp)
    {
        case 0x01:
            *feature = GD_SFLASH_IO1_MODE;
            break;

        case 0x02:
            *feature = GD_SFLASH_IO2_MODE;
            break;

        case 0x04:
            *feature = GD_SFLASH_IO4_MODE;
            break;

        default:
            return(GD_ERR_INVALID_HANDLE);
    }
    return GD_OK;
}

/*!
********************************************************************************
**
** \brief set the sflash IO mode
**
** This function make the sflash to switch between IO1/IO2/IO4 only if it could
** support
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**        op      Read or Write mode
**        feature  IO mode to be set
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_SetIoMode(GD_HANDLE handle, GD_SFLASH_RW_E op, GD_SFLASH_IO_MODE_E feature)
{
    U8 temp = 0x00;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    switch(feature)
    {
        case GD_SFLASH_IO1_MODE:
            temp = 0x01;
            break;

        case GD_SFLASH_IO2_MODE:
            temp = 0x02;
            break;

        case GD_SFLASH_IO4_MODE:
            temp = 0x04;
            break;

        default:
            break;
    }

    if(op == GD_SFLASH_READ)
    {
        device->feature &= 0xF0;
        device->feature |= temp;
    }
    else
    {
        device->feature &= 0x0F;
        device->feature |= (temp << 0x4);
    }
    return(GD_OK);
}
/*!
********************************************************************************
**
** \brief enable/disable reset mode
**
** This function make the sflash to switch between IO1/IO2/IO4 only if it could
** support
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**        mode    enalbe/disable reset mode
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_SetResetMode(GD_HANDLE handle, GBOOL mode)
{
    U32 cmdBitSet = 0;
    U8 status1 = 0;
    GD_SFLASH_HANDLE_S* device = (GD_SFLASH_HANDLE_S*)handle;
    U32 command     = 0;

    if(device == NULL)
    {
        return(GD_ERR_INVALID_HANDLE);
    }
    if((device->dev->manufacture_ID == MXIC_MID) ||
       (device->dev->manufacture_ID == ISSI_MID))
    {
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
        device->func.GH_SFLASH_get_Data();

        device->func.GH_SFLASH_set_Command(device->dev->commands->read_status);
        status1 = device->func.GH_SFLASH_get_Data() & 0xff;

        status1 = status1 & (0x83);
        if(mode == GFALSE)
        {
            status1 = status1 | 0x40;
        }
        device->func.GH_SFLASH_set_Command(device->dev->commands->write_enable);
        device->func.GH_SFLASH_get_Data();

        device->func.GH_SFLASH_set_Command(device->dev->commands->write_status);
        device->func.GH_SFLASH_set_Data(status1);
        sflash_wip_done_wait(handle);
    }
    return(GD_OK);
}

