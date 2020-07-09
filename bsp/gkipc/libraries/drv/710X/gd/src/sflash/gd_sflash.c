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

/*
*******************************************************************************
**
** serial flash specific commands for Spansion flash devices
**
*******************************************************************************
*/
GD_SFLASH_CMD_S sd_sflash_commands_mx =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast */  0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0xbb,
    /* readData4     */ 0xeb,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x38,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};


/*
*******************************************************************************
**
** serial flash specific commands for Spansion flash devices
**
*******************************************************************************
*/
GD_SFLASH_CMD_S sd_sflash_commands_issi =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast */  0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0xbb,
    /* readData4     */ 0xeb,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x38,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};


GD_SFLASH_CMD_S sd_sflash_commands_spansion =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0xbb,
    /* readData4     */ 0xeb,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};

/*
*******************************************************************************
**
** serial flash specific commands for STmicro flash devices
**
*******************************************************************************
*/
GD_SFLASH_CMD_S sd_sflash_commands_stmicro =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x00,
    /* readData4     */ 0x00,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x00,
    /* pageRead      */ 0x00
};

/*
*******************************************************************************
**
** serial flash specific commands for Atmel flash devices
**
*******************************************************************************
*/
GD_SFLASH_CMD_S sd_sflash_commands_atmel =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x00,
    /* readData4     */ 0x00,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x00,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};

/*
*******************************************************************************
**
** serial flash specific commands for NUMONYX flash devices
**
*******************************************************************************
*/
GD_SFLASH_CMD_S sd_sflash_commands_numonyx =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0xbb,
    /* readData4     */ 0xeb,
    /* programPage2  */ 0xd2,
    /* programPage4  */ 0x12,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};

GD_SFLASH_CMD_S sd_sflash_commands_wb =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0xbb,
    /* readData4     */ 0xeb,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};

GD_SFLASH_CMD_S  sd_sflash_command_sst =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0x20,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x80,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x00,
    /* readData4     */ 0x0B,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};

GD_SFLASH_CMD_S sd_sflash_commands_gd =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0xbb,
    /* readData4     */ 0xeb,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};

GD_SFLASH_CMD_S sd_sflash_commands_eon =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0xC7,
    /* programPage   */ 0x02,
    /* statusMaskWIP */ 0x01,
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x00,
    /* readData4     */ 0x0b,
    /* programPage2  */ 0x00,
    /* programPage4  */ 0x02,
    /* pageRead      */ 0x00,
    /* programExecute*/ 0x00
};

GD_SFLASH_CMD_S sd_sflash_commands_gd_spi_nand =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x0F, // in the datasheet, equals to get feature
    /* writeStatus   */ 0x1F, // in the datasheet, equals to set feature
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0x00, // no such functionality ???
    /* programPage   */ 0x02, // 0x32 for quad program page ???
    /* statusMaskWIP */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x3B,
    /* readData4     */ 0x6B,
    /* programPage2  */ 0x00, // no such function
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x13,
    /* programExecute*/ 0x10
};

GD_SFLASH_CMD_S sd_sflash_commands_esmt_spi_nand =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x0F, // in the datasheet, equals to get feature
    /* writeStatus   */ 0x1F, // in the datasheet, equals to set feature
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0x00, // no such functionality ???
    /* programPage   */ 0x02, // 0x32 for quad program page ???
    /* statusMaskWIP */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x3B,
    /* readData4     */ 0x6B,
    /* programPage2  */ 0x00, // no such function
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x13,
    /* programExecute*/ 0x10
};

GD_SFLASH_CMD_S sd_sflash_commands_wb_spi_nand =
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x0F, // or 0x05  in the datasheet, equals to get feature
    /* writeStatus   */ 0x1F, // or 0x01 in the datasheet, equals to set feature
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0x00, // no such functionality ???
    /* programPage   */ 0x02, // 0x32 for quad program page ???
    /* statusMaskWIP */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x3B,
    /* readData4     */ 0x6B,
    /* programPage2  */ 0x00, // no such function
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x13,
    /* programExecute*/ 0x10
};

GD_SFLASH_CMD_S sd_sflash_commands_mx_spi_nand = 
{
    /* readID        */ 0x9F,
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x0F, // or 0x05  in the datasheet, equals to get feature
    /* writeStatus   */ 0x1F, // or 0x01 in the datasheet, equals to set feature
    /* readData      */ 0x03,
    /* readDataFast  */ 0x0B,
    /* eraseSector   */ 0xD8,
    /* eraseChip     */ 0x00, // no such functionality ???
    /* programPage   */ 0x02, // 0x32 for quad program page ???
    /* statusMaskWIP */ 0x01, // in the datasheet, equals to bit named OIP in get feature register
    /* statusMaskWEL */ 0x02,
    /* readData2     */ 0x3B,
    /* readData4     */ 0x6B,
    /* programPage2  */ 0x00, // no such function
    /* programPage4  */ 0x32,
    /* pageRead      */ 0x13,
    /* programExecute*/ 0x10   
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
GD_SFLASH_DEV_S gd_sflash_devices_supported[] =
{

   /*
    ** Spansion seem to use unique sectors
    ** with 64kBytes each, they increment the
    ** number of sectors for bigger chips
    */
    {
        /* manufactureID   */ 0x01,
        /* deviceID        */ 0x0212,
        /* manufactureName */ "Spansion",
        /* deviceName      */ "S25FL004A",
        /* deviceBytes     */ 524288,
        /* sectorCount     */ 8,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_spansion,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x01,
        /* deviceID        */ 0x0213,
        /* manufactureName */ "Spansion",
        /* deviceName      */ "S25FL008A",
        /* deviceBytes     */ 1048576,
        /* sectorCount     */ 16,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_spansion,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x01,
        /* deviceID        */ 0x0214,
        /* manufactureName */ "Spansion",
        /* deviceName      */ "S25FL016A",
        /* deviceBytes     */ 2097152,
        /* sectorCount     */ 32,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_spansion,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x01,
        /* deviceID        */ 0x0215,
        /* manufactureName */ "Spansion",
        /* deviceName      */ "S25FL032P",
        /* deviceBytes     */ 4194304,
        /* sectorCount     */ 64,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_spansion,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x01,
        /* deviceID        */ 0x0216,
        /* manufactureName */ "Spansion",
        /* deviceName      */ "S25FL064A",
        /* deviceBytes     */ 8388608,
        /* sectorCount     */ 128,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_spansion,
        /* ioMode          */ GD_SFLASH_4X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x01,
        /* deviceID        */ 0x2018,
        /* manufactureName */ "Spansion",
        /* deviceName      */ "FL128PIFL",
        /* deviceBytes     */ 16777216,
        /* sectorCount     */ 256,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_spansion,
        /* ioMode          */ GD_SFLASH_4X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },

    /*
    ** MX seem to use unique sectors
    ** with 64kBytes each, they increment the
    ** number of sectors for bigger chips
    */
    /* gk6105 8M SFlash */
    {
        /* manufactureID   */ 0xc2,
        /* deviceID        */ 0x2617,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX25L6455E",
        /* deviceBytes     */ 8388608,
        /* sectorCount     */ 128,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_mx,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc2,
        /* deviceID        */ 0x2017,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX25L6465E",
        /* deviceBytes     */ 8388608,
        /* sectorCount     */ 128,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_mx,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc2,
        /* deviceID        */ 0x2018,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX25L12845",
        /* deviceBytes     */ 16777216,
        /* sectorCount     */ 256,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_mx,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc2,
        /* deviceID        */ 0x5e16,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX253235D",
        /* deviceBytes     */ 4194304,
        /* sectorCount     */ 64,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_mx,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc2,
        /* deviceID        */ 0x2415,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX25L1605D",
        /* deviceBytes     */ 2097152,
        /* sectorCount     */ 32,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_mx,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc2,
        /* deviceID        */ 0x2415,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX25L1635D",
        /* deviceBytes     */ 2097152,
        /* sectorCount     */ 32,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_mx,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc2,
        /* deviceID        */ 0x9e16,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX25L3255D",
        /* deviceBytes     */ 4194304,
        /* sectorCount     */ 64,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_mx,
        /* ioMode          */ GD_SFLASH_4X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xef,
        /* deviceID        */ 0x4015,
        /* manufactureName */ "Winbond",
        /* deviceName      */ "W25Q16BV",
        /* deviceBytes     */ 2097152,
        /* sectorCount     */ 32,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_wb,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xef,
        /* deviceID        */ 0x4016,
        /* manufactureName */ "Winbond",
        /* deviceName      */ "W25Q32FV",
        /* deviceBytes     */ 4194304,
        /* sectorCount     */ 64,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_wb,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xef,
        /* deviceID        */ 0x4017,
        /* manufactureName */ "Winbond",
        /* deviceName      */ "W25Q64FV",
        /* deviceBytes     */ 8388608,
        /* sectorCount     */ 128,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_wb,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xef,
        /* deviceID        */ 0x4018,
        /* manufactureName */ "Winbond",
        /* deviceName      */ "W25Q128FV",
        /* deviceBytes     */ 16777216,
        /* sectorCount     */ 256,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_wb,
        /* ioMode          */ GD_SFLASH_4X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xbf,
        /* deviceID        */ 0x2601,
        /* manufactureName */ "SST",
        /* deviceName      */ "SST26VF016",
        /* deviceBytes     */ 2097152,
        /* sectorCount     */ 512,
        /* sectorBytes     */ 4096,
        /* sectorPages     */ 16,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_command_sst,
        /* ioMode          */ GD_SFLASH_4X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x20,
        /* deviceID        */ 0xba18,
        /* manufactureName */ "numonyx",
        /* deviceName      */ "N25Q128",
        /* deviceBytes     */ 8388608*2,
        /* sectorCount     */ 256,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_numonyx,
        /* ioMode          */ GD_SFLASH_4X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc8,
        /* deviceID        */ 0x4017,
        /* manufactureName */ "GigaDevice",
        /* deviceName      */ "GD25Q64C",
        /* deviceBytes     */ 8388608,
        /* sectorCount     */ 128,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_gd,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc8,
        /* deviceID        */ 0x4018,
        /* manufactureName */ "GigaDevice",
        /* deviceName      */ "GD25Q128C",
        /* deviceBytes     */ 8388608*2,
        /* sectorCount     */ 256,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_gd,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x1c,
        /* deviceID        */ 0x3017,
        /* manufactureName */ "EON",
        /* deviceName      */ "EN25Q64",
        /* deviceBytes     */ 8388608,
        /* sectorCount     */ 128,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_eon,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufacture_ID   */ 0x1C,
        /* device_ID        */ 0x7017,
        /* manufacture_name */ "EON",
        /* device_name      */ "EN25QH64A",
        /* device_bytes     */ 8388608,
        /* sector_count     */ 128,
        /* sector_bytes     */ 65536,
        /* sector_pages     */ 256,
        /* page_bytes       */ 256,
        /* commands         */ &sd_sflash_commands_eon,
        /* feature          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel          */ GD_SFLASH_CHANNEL_0,
    },    
    {
        /* manufactureID   */ 0x1c,
        /* deviceID        */ 0x7018,
        /* manufactureName */ "EON",
        /* deviceName      */ "EN25QH128A",
        /* deviceBytes     */ 8388608*2,
        /* sectorCount     */ 256,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_eon,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_4X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xc8,
        /* deviceID        */ 0x00f1,
        /* manufactureName */ "GigaDevice",
        /* deviceName      */ "GD5F1GQ4UAW",
        /* deviceBytes     */ 134217728,
        /* sectorCount     */ 1024,
        /* sectorBytes     */ 131072,
        /* sectorPages     */ 64,
        /* pageBytes       */ 2048,
        /* commands        */ &sd_sflash_commands_gd_spi_nand,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NAND,
        /* channel         */ GD_SFLASH_CHANNEL_1
    },
    {
        /* manufactureID   */ 0xc8,
        /* deviceID        */ 0x00f2,
        /* manufactureName */ "GigaDevice",
        /* deviceName      */ "GD5F2GQ4UAW",
        /* deviceBytes     */ 268435456,
        /* sectorCount     */ 2048,
        /* sectorBytes     */ 131072,
        /* sectorPages     */ 64,
        /* pageBytes       */ 2048,
        /* commands        */ &sd_sflash_commands_gd_spi_nand,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NAND,
        /* channel         */ GD_SFLASH_CHANNEL_1
    },
    {
        /* manufactureID   */ 0xc8,
        /* deviceID        */ 0x00f4,
        /* manufactureName */ "GigaDevice",
        /* deviceName      */ "GD5F4GQ4UAW",
        /* deviceBytes     */ 536870912,
        /* sectorCount     */ 4096,
        /* sectorBytes     */ 131072,
        /* sectorPages     */ 64,
        /* pageBytes       */ 2048,
        /* commands        */ &sd_sflash_commands_gd_spi_nand,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NAND,
        /* channel         */ GD_SFLASH_CHANNEL_1
    },
    {
        /* manufactureID   */ 0xc8,
        /* deviceID        */ 0x0020,
        /* manufactureName */ "ESMT",
        /* deviceName      */ "F50L512M41A",
        /* deviceBytes     */ 67108864,
        /* sectorCount     */ 512,
        /* sectorBytes     */ 131072,
        /* sectorPages     */ 64,
        /* pageBytes       */ 2048,
        /* commands        */ &sd_sflash_commands_esmt_spi_nand,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NAND,
        /* channel         */ GD_SFLASH_CHANNEL_1
    },
    {
        /* manufactureID   */ 0xEF,
        /* deviceID        */ 0xAA21,
        /* manufactureName */ "Winbond",
        /* deviceName      */ "W25N01GV",
        /* deviceBytes     */ 134217728,       // 128MB=1Gb
        /* sectorCount     */ 1024,
        /* sectorBytes     */ 131072,
        /* sectorPages     */ 64,
        /* pageBytes       */ 2048,
        /* commands        */ &sd_sflash_commands_wb_spi_nand,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NAND,
        /* channel         */ GD_SFLASH_CHANNEL_1
    },
    {
        /* manufactureID   */ 0x9D,
        /* deviceID        */ 0x6017,
        /* manufactureName */ "issi",
        /* deviceName      */ "IC25LP064",
        /* deviceBytes     */ 8388608,
        /* sectorCount     */ 128,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_issi,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0x9D,
        /* deviceID        */ 0x6018,
        /* manufactureName */ "issi",
        /* deviceName      */ "IC25LP128",
        /* deviceBytes     */ 8388608*2,
        /* sectorCount     */ 256,
        /* sectorBytes     */ 65536,
        /* sectorPages     */ 256,
        /* pageBytes       */ 256,
        /* commands        */ &sd_sflash_commands_issi,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NOR,
        /* channel         */ GD_SFLASH_CHANNEL_0
    },
    {
        /* manufactureID   */ 0xC2,
        /* deviceID        */ 0x12,
        /* manufactureName */ "MX",
        /* deviceName      */ "MX35LF1GE4AB",
        /* deviceBytes     */ 134217728,       // 128MB=1Gb
        /* sectorCount     */ 1024,
        /* sectorBytes     */ 131072,
        /* sectorPages     */ 64,
        /* pageBytes       */ 2048,
        /* commands        */ &sd_sflash_commands_mx_spi_nand,
        /* ioMode          */ GD_SFLASH_1X_WRITE | GD_SFLASH_1X_READ,
        /* type            */ GD_SPI_NAND,
        /* channel         */ GD_SFLASH_CHANNEL_1
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
static GD_SFLASH_DEV_S* gd_sflash_device[GD_SFLASH_CHANNEL_NUM] = {0};

/*
*******************************************************************************
**
** gd_sflash_handle is used to store information during GD_SFLASH_Open()
** according to H/W design, 1 or 2 instance could be supported
**
*******************************************************************************
*/
static GD_SFLASH_DEV_S* gd_sflash_handle[GD_SFLASH_CHANNEL_NUM] = {0};

/*
*******************************************************************************
**
** gd_flash_device is used to point to the device structure
** refering to the device found during GD_SFLASH_Init()
**
*******************************************************************************
*/
static GD_SFLASH_FUNC_S gd_sflash_func[GD_SFLASH_CHANNEL_NUM] = {{0}};

static GBOOL InitDone = GFALSE;
/*
*******************************************************************************
**
** sflashGetDevice is used check and get the GD_SFLASH_DEV_S pointer from
** a given handle variable.
**
*******************************************************************************
*/

GERR sflashEnableIO4Hw(GD_HANDLE handle,GBOOL enable)
{
    U32 CESetting = 0;
    GD_SFLASH_DEV_S* device = (GD_SFLASH_DEV_S*)(void*)handle;
    if(!device)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    CESetting = gd_sflash_func[device->channel].GH_SFLASH_get_CE();
    CESetting &= 0xC0;
    if(enable == GTRUE)
    {
        CESetting |= 0x38;
    }
    else
    {
        CESetting |= 0x0E;
    }
    gd_sflash_func[device->channel].GH_SFLASH_set_CE(CESetting);
    return GD_OK;
}


static GD_SFLASH_DEV_S* sflashGetDevice(GD_HANDLE handle)
{
    GD_SFLASH_DEV_S* device = (GD_SFLASH_DEV_S*)(void*)handle;
    U32 CESetting = 0;
    U32 newCESetting = 0;

    if(device && device->manufactureID)
    {
        CESetting = gd_sflash_func[device->channel].GH_SFLASH_get_CE();
        newCESetting = (CESetting  & 0x3F) | ((U32)device->devicechannel << 6);
        if(CESetting != newCESetting)
        {
            gd_sflash_func[device->channel].GH_SFLASH_set_CE_CHSELECT((U8)device->devicechannel);
        }
        return(device);
    }
    return(0);
}

static void sflashReleaseDevice(GD_HANDLE handle)
{
    GD_SFLASH_DEV_S* device = (GD_SFLASH_DEV_S*)(void*)handle;

    if(device && device->manufactureID)
    {
        gd_sflash_func[device->channel].GH_SFLASH_set_CE_CHSELECT(!device->channel);
    }
}


static GERR sflashCmdBitSet(GH_SFLASH_COMMAND_S *sflashCmd, U32 *cmdBitSet)
{
    if(!sflashCmd)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    sflashCmd->all = (*cmdBitSet);
    (*cmdBitSet) = 0;

    return GD_OK;
}

static GERR sflashWelDoneWait(GD_HANDLE handle)
{
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U8 welMask;
    GH_SFLASH_COMMAND_S SflashCmd,SflashCmd_2;
    U32 cmdBitSet = 0,cmdBitSet_2 = 0;
    U32 status1,status2;


    cmdBitSet |= (device->commands->readStatus  |
                  SFLASH_SEND_CMD               |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                  SFLASH_RWN_READ               |   // read data
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                  (1<<SFLASH_TRANSFER_BYTE_LOC) |   // transfer data number
                  SFLASH_HOLD_TIME_100ns
                 );

    // set the sflash cmd mode, set the sflash data mode
    if(device->manufactureID == 0xbf)
    {
        cmdBitSet |= (SFLASH_CMD_MODE_4X | SFLASH_DATA_CYCLE_NUM_2);
    }
    else
    {
        cmdBitSet |= (SFLASH_CMD_MODE_1X | SFLASH_DATA_CYCLE_NUM_0);
    }
    
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);


    cmdBitSet_2 |= (0x35  |
                  SFLASH_SEND_CMD               |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                  SFLASH_RWN_READ               |   // read data
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                  (1<<SFLASH_TRANSFER_BYTE_LOC) |   // transfer data number
                  SFLASH_HOLD_TIME_100ns
                 );

    // set the sflash cmd mode, set the sflash data mode
    if(device->manufactureID == 0xbf)
    {
        cmdBitSet |= (SFLASH_CMD_MODE_4X | SFLASH_DATA_CYCLE_NUM_2);
    }
    else
    {
        cmdBitSet |= (SFLASH_CMD_MODE_1X | SFLASH_DATA_CYCLE_NUM_0);
    }
    
    sflashCmdBitSet(&SflashCmd_2, &cmdBitSet_2);

    welMask = device->commands->statusMaskWEL;
    while(1)
    {
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data()&0xff;

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd_2.all);
        status2 = gd_sflash_func[device->channel].GH_SFLASH_get_Data()&0xff;        


        if((status1& welMask) == welMask) // flash device ready
        {
            // If use IO4 can not release this
            //sflashReleaseDevice(handle);
            return(GD_OK);           
        }
    }
}


/*
*******************************************************************************
**
** sflashWipDoneWait is used to wait until the WIP (write-in-progress)
** flag is cleared by the device.
**
*******************************************************************************
*/
static GERR sflashWipDoneWait(GD_HANDLE handle)
{
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U8 wipMask;
    GH_SFLASH_COMMAND_S SflashCmd;
    U32 cmdBitSet = 0;


    cmdBitSet |= (device->commands->readStatus  |
                  SFLASH_SEND_CMD               |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                  SFLASH_RWN_READ               |   // read data
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                  (1<<SFLASH_TRANSFER_BYTE_LOC) |   // transfer data number
                  SFLASH_HOLD_TIME_100ns
                 );

    // set the sflash cmd mode, set the sflash data mode
    if(device->manufactureID == 0xbf)
    {
        cmdBitSet |= (SFLASH_CMD_MODE_4X | SFLASH_DATA_CYCLE_NUM_2);
    }
    else
    {
        cmdBitSet |= (SFLASH_CMD_MODE_1X | SFLASH_DATA_CYCLE_NUM_0);
    }
    
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);

//#else


    wipMask = device->commands->statusMaskWIP;
    while(1)
    {
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);

        if((gd_sflash_func[device->channel].GH_SFLASH_get_Data() & wipMask) != wipMask) // flash device ready
        {
            // If use IO4 can not release this
            //sflashReleaseDevice(handle);
            return(GD_OK);
            
        }
    }
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U8 oipMask;
    GH_SFLASH_COMMAND_S   SflashCmd;
    U32 cmdBitSet = 0;
    U8 readStatus = 0;

    cmdBitSet |= (device->commands->readStatus      |   // command
                  SFLASH_SEND_CMD                   |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                  SFLASH_RWN_READ                   |   // read data
                  SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                  (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                  SFLASH_HOLD_TIME_100ns
                  );
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);
    oipMask = device->commands->statusMaskWIP;

    while(1)
    {
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xc0);

        readStatus = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("readStatus(0xc0):0x%02x\n",readStatus);
#endif
        if((readStatus & oipMask) != oipMask) // flash device ready
        {
            // If use IO4 can not release this
            //sflashReleaseDevice(handle);
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    GH_SFLASH_COMMAND_S SflashCmd;
    U32 cmdBitSet = 0, i;
    U32 readPage = startPage;
    U32 length, pageCnt = 0;
    U32 start_addr = startAddr;
    GBOOL pageMatched = GFALSE;
    SFLASH_get_Data get_Data;
    get_Data = gd_sflash_func[device->channel].GH_SFLASH_get_Data;

    if((startAddr == 0x0) && (endAddr == 0x0))
    {
        pageMatched = GTRUE;
    }
    // start read page from spi-nand
    while(readPage < endPage)
    {
        sflashGetDevice(handle);
        // 1. page read to cache
        cmdBitSet |= (device->commands->pageRead    |   // command
                      SFLASH_SEND_CMD               |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                      SFLASH_RWN_READ               |   // read data
                      SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                      SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(readPage);                   // here address should be page/block address,
                                                        // since total page number = size / pageBytes
                                                        // for size = 128MB, pageSize = 2KB
                                                        // total page number = 128MB / 2KB = 64KB
        // 2. check if page read is done
#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashRead\n");
#endif
        sflashReleaseDevice(handle);
        spiNandFlashOipDoneWait(handle);

        sflashGetDevice(handle);
        // 3. read from cache
        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            cmdBitSet |= (device->commands->readData4   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else if((device->ioMode & 0x0F) == GD_SFLASH_2X_READ)
        {
            cmdBitSet |= (device->commands->readData2   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_1       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else
        {
            cmdBitSet |= (device->commands->readData    |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);

        if((device->manufactureID == 0xEF) || (device->manufactureID == 0xC8)|| (device->manufactureID == 0xC2))
        {
            gd_sflash_func[device->channel].GH_SFLASH_set_Data(start_addr<<8);
        }
        else
        {
            gd_sflash_func[device->channel].GH_SFLASH_set_Data((0x00004000 | start_addr));      // fixed as 2048 wrap
        }
        length = (device->pageBytes - start_addr) /  sizeof(U32);

        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }

        for(i=0;i<length;i++)
        {
            *buffer++ = get_Data();
        }
        
        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }
        // only for debug, to be removed later
        // printf("[spi-nand-write] readPage = %d, length = %d, start_addr = 0x%08x, endAddr = 0x%08x, pageCnt = %d \n", readPage, length, start_addr, endAddr, pageCnt);

        readPage++;
        pageCnt++;
        if(pageCnt == 0x1)
        {
            start_addr = 0x0;
        }
        sflashReleaseDevice(handle);
    }

    // last page
    if(pageMatched == GFALSE)
    {
        sflashGetDevice(handle);
        // 1. page read to cache
        cmdBitSet |= (device->commands->pageRead    |   // command
                      SFLASH_SEND_CMD               |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                      SFLASH_RWN_READ               |   // read data
                      SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                      SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(readPage);                   // here address should be page/block address,
                                                        // since total page number = size / pageBytes
                                                        // for size = 128MB, pageSize = 2KB
                                                        // total page number = 128MB / 2KB = 64KB
        // 2. check if page read is done
#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashRead\n");
#endif
        sflashReleaseDevice(handle);
        spiNandFlashOipDoneWait(handle);

        sflashGetDevice(handle);
        // 3. read from cache
        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            cmdBitSet |= (device->commands->readData4   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else if((device->ioMode & 0x0F) == GD_SFLASH_2X_READ)
        {
            cmdBitSet |= (device->commands->readData2   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_1       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else
        {
            cmdBitSet |= (device->commands->readData    |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);

        if((device->manufactureID == 0xEF) || (device->manufactureID == 0xC8)|| (device->manufactureID == 0xC2))
        {
            gd_sflash_func[device->channel].GH_SFLASH_set_Data(start_addr<<8);
        }
        else
        {
            gd_sflash_func[device->channel].GH_SFLASH_set_Data((0x00004000 | start_addr));      // fixed as 2048 wrap
        }
        length = (endAddr - start_addr) / sizeof(U32);
        // only for debug, to be removed later
        // printf("[spi-nand-write] readPage = %d, length = %d, start_addr = 0x%08x, endAddr = 0x%08x, pageCnt = %d \n", readPage, length, start_addr, endAddr, pageCnt);
        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }
        for(i=0;i<length;i++)
        {
            *buffer++ = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
        }
        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }
        
        sflashReleaseDevice(handle);
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    GH_SFLASH_COMMAND_S SflashCmd;
    U32 cmdBitSet = 0, i;
    U32 writePage = startPage;
    U32 length, pageCnt = 0;
    U32 start_addr = startAddr;
    GERR result = GD_ERR_SFLASH_WRITE;
    GBOOL pageMatched = GFALSE;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)gd_sflash_func[device->channel].GH_SFLASH_set_Data;

    if((startAddr == 0x0) && (endAddr == 0x0))
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
        sflashGetDevice(handle);

        cmdBitSet |= (device->commands->writeEnable     |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_NOTHING                |   // no read/write data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (0<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                      SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();

        if((device->ioMode & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            cmdBitSet |= (device->commands->programPage4    |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // write data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2           |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                          SFLASH_HOLD_TIME_100ns
                         );
        }
        else if((device->ioMode & 0xF0) == GD_SFLASH_2X_WRITE)
        {
            if(device->commands->programPage2 == 0x00)
            {
                return(GD_ERR_SFLASH_TYPE_NOT_SUPPORTED);
            }

            cmdBitSet |= (device->commands->programPage2    |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // write data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_1           |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                          SFLASH_HOLD_TIME_100ns
                         );
        }
        else
        {
            cmdBitSet |= (device->commands->programPage     |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // write data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                          SFLASH_HOLD_TIME_100ns
                         );
        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(start_addr);

        length = (device->pageBytes - start_addr) /  sizeof(U32);
        
        if((device->ioMode & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }
        for(i=0;i<length;i++)
        {
            set_Data(*buffer++);
        }
        
        if((device->ioMode & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }
        
        sflashReleaseDevice(handle);
        sflashGetDevice(handle);

        cmdBitSet |= (device->commands->programExecute  |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_3       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_WRITE                  |   // write data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                      SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(writePage);

        // only for debug, to be removed later
        // printf("[spi-nand-write] writePage = %d, length = %d, start_addr = 0x%08x, endAddr = 0x%08x, pageCnt = %d \n", writePage, length, start_addr, endAddr, pageCnt);

#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashWrite\n");
#endif
        sflashReleaseDevice(handle);
        result = spiNandFlashOipDoneWait(handle);
        if(result != GD_OK)
            break;

        writePage++;
        pageCnt++;
        if(pageCnt == 0x1)
        {
            start_addr = 0x0;
        }
        sflashReleaseDevice(handle);
    }

    // last page
    if(pageMatched == GFALSE)
    {
        sflashGetDevice(handle);
        //
        // issue a write command sequence to prepare
        // the device for data to be written
        //
        cmdBitSet |= (device->commands->writeEnable     |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_NOTHING                |   // no read/write data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (0<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                      SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();

        if((device->ioMode & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            cmdBitSet |= (device->commands->programPage4    |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // write data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2           |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                          SFLASH_HOLD_TIME_100ns
                         );
        }
        else if((device->ioMode & 0xF0) == GD_SFLASH_2X_WRITE)
        {
            cmdBitSet |= (device->commands->programPage2    |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // write data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_1           |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                          SFLASH_HOLD_TIME_100ns
                         );
        }
        else
        {
            cmdBitSet |= (device->commands->programPage     |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_2       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // write data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                          SFLASH_HOLD_TIME_100ns
                         );
        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(start_addr);

        length = (endAddr - start_addr) / sizeof(U32);
        if((device->ioMode & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GTRUE);
        }
        for(i=0;i<length;i++)
        {
            gd_sflash_func[device->channel].GH_SFLASH_set_Data(*buffer++);
        }
        if((device->ioMode & 0xF0) == GD_SFLASH_4X_WRITE)
        {
            sflashEnableIO4Hw(handle,GFALSE);
        }
        // only for debug, to be removed later
        // printf("[spi-nand-write] writePage = %d, length = %d, start_addr = 0x%08x, endAddr = 0x%08x, pageCnt = %d \n", writePage, length, start_addr, endAddr, pageCnt);

        cmdBitSet |= (device->commands->programExecute  |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_3       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_WRITE                  |   // write data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                      SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(writePage);

#ifdef DEBUG_PRINT
        GM_Printf("spiNandFlashWrite\n");
#endif
        result = spiNandFlashOipDoneWait(handle);
        sflashReleaseDevice(handle);
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    GH_SFLASH_COMMAND_S SflashCmd;
    U32 cmdBitSet = 0;
    U32 blockAddr;
    GERR gerr;
    //
    // issue a write command sequence to prepare
    // the device for data to be written
    //
    cmdBitSet |= (device->commands->writeEnable     |   // command
                  SFLASH_SEND_CMD                   |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                  SFLASH_RWN_NOTHING                |   // no read/write data
                  SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                  (0<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                  SFLASH_HOLD_TIME_100ns
                 );
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);
    gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
    gd_sflash_func[device->channel].GH_SFLASH_get_Data();

    cmdBitSet |= (device->commands->eraseSector     |   // command
                  SFLASH_SEND_CMD                   |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_3       |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                  SFLASH_RWN_WRITE                  |   // write data
                  SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                  SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                  SFLASH_HOLD_TIME_100ns
                 );
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);

    gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
    blockAddr = address / device->pageBytes;
    gd_sflash_func[device->channel].GH_SFLASH_set_Data(blockAddr);

#ifdef DEBUG_PRINT
    GM_Printf("spiNandFlashEraseSector\n");
#endif
    sflashReleaseDevice(handle);
    gerr = spiNandFlashOipDoneWait(handle);
    return gerr;
}

/*!
********************************************************************************
**
** \brief Initialize the serial flash driver
**
** This function initializes the serial flash driver, it tries to detect a
** serial flash device by executing the readID commands for all supported
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
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_set_Handle      = NULL;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_set_Command     = GH_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_set_Data        = GH_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_get_Data        = GH_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_set_CE          = GH_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_get_CE          = GH_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_get_CE_CHSELECT = GH_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_set_Speed       = GH_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_CHANNEL_0].GH_SFLASH_set_CE_CHSELECT = GH_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_set_Handle      = NULL;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_set_Command     = GH_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_set_Data        = GH_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_get_Data        = GH_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_set_CE          = GH_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_get_CE          = GH_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_get_CE_CHSELECT = GH_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_set_Speed       = GH_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_CHANNEL_1].GH_SFLASH_set_CE_CHSELECT = GH_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_0].GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_1].GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_4].GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_5].GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_6].GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_0_7].GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;

    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_set_Handle      = GH_SPI_SFLASH_set_Handle;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_set_Command     = GH_SPI_SFLASH_set_Command;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_set_Data        = GH_SPI_SFLASH_set_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_get_Data        = GH_SPI_SFLASH_get_Data;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_set_CE          = GH_SPI_SFLASH_set_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_get_CE          = GH_SPI_SFLASH_get_CE;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_get_CE_CHSELECT = GH_SPI_SFLASH_get_CE_CHSELECT;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_set_Speed       = GH_SPI_SFLASH_set_Speed;
    gd_sflash_func[GD_SFLASH_SPI_CHANNEL_1_0].GH_SFLASH_set_CE_CHSELECT = GH_SPI_SFLASH_set_CE_CHSELECT;
    for(i=0;i<GD_SFLASH_CHANNEL_NUM;i++)
    {
        gd_sflash_device[i] = NULL;
        gd_sflash_handle[i] = NULL;
    }
    InitDone = GTRUE;
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
        gd_sflash_func[i].GH_SFLASH_set_Handle      = NULL;
        gd_sflash_func[i].GH_SFLASH_set_Command     = GH_SFLASH_set_Command;
        gd_sflash_func[i].GH_SFLASH_set_Data        = GH_SFLASH_set_Data;
        gd_sflash_func[i].GH_SFLASH_get_Data        = GH_SFLASH_get_Data;
        gd_sflash_func[i].GH_SFLASH_set_CE          = GH_SFLASH_set_CE;
        gd_sflash_func[i].GH_SFLASH_get_CE          = GH_SFLASH_get_CE;
        gd_sflash_func[i].GH_SFLASH_get_CE_CHSELECT = GH_SFLASH_get_CE_CHSELECT;
        gd_sflash_func[i].GH_SFLASH_set_Speed       = GH_SFLASH_set_Speed;
        gd_sflash_func[i].GH_SFLASH_set_CE_CHSELECT = GH_SFLASH_set_CE_CHSELECT;

        gd_sflash_device[i] = NULL;
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
    U32 sflashData;
    U8  manufactureID;
    U16 deviceID;
    U32 index;
    U32 count;
    U32 cmdBitSet = 0;
    U8  status;
    U32 prot1,prot2;
    GD_SFLASH_DEV_S* device;
    GH_SFLASH_COMMAND_S SflashCmd;
    U32 CESetting = 0x0E;//0x38
    GD_HANDLE   spi;
    GD_SPI_OPEN_PARAMS_S openParams;
    U32 devicechannel = 0;
    U32 sflash_data;
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
        devicechannel = channel;
        break;
    case GD_SFLASH_SPI_CHANNEL_0_0:
    case GD_SFLASH_SPI_CHANNEL_0_1:
        {
            openParams.spi      = GD_SPI_CHANNEL_0;
            openParams.slave    = GD_SPI_SLAVE0 + channel - GD_SFLASH_SPI_CHANNEL_0_0;
            openParams.baudrate = speed_mode;

            GD_SPI_Open(&openParams, &spi);
            gd_sflash_func[channel].GH_SFLASH_set_Handle((GD_SPI_STATUS_PARAMS_S*)spi);

            devicechannel = openParams.slave;
        }
        break;
    case GD_SFLASH_SPI_CHANNEL_0_4:
    case GD_SFLASH_SPI_CHANNEL_0_5:
    case GD_SFLASH_SPI_CHANNEL_0_6:
    case GD_SFLASH_SPI_CHANNEL_0_7:
        {
            openParams.spi      = GD_SPI_CHANNEL_0;
            openParams.slave    = GD_SPI_SLAVE4 + channel - GD_SFLASH_SPI_CHANNEL_0_4;
            openParams.baudrate = speed_mode;

            GD_SPI_Open(&openParams, &spi);
            gd_sflash_func[channel].GH_SFLASH_set_Handle((GD_SPI_STATUS_PARAMS_S*)spi);

            devicechannel = openParams.slave;
        }
        break;
    case GD_SFLASH_SPI_CHANNEL_1_0:
        {
            openParams.spi      = GD_SPI_CHANNEL_1;
            openParams.slave    = GD_SPI_SLAVE0;
            openParams.baudrate = speed_mode;

            GD_SPI_Open(&openParams, &spi);
            gd_sflash_func[channel].GH_SFLASH_set_Handle((GD_SPI_STATUS_PARAMS_S*)spi);

            devicechannel = openParams.slave;
        }
        break;
     default:
        break;
    }

    CESetting = CESetting | ((U32)devicechannel << 6);

    gd_sflash_func[channel].GH_SFLASH_set_CE(CESetting);
    gd_sflash_func[channel].GH_SFLASH_set_Speed(speed_mode); //0 -- 1/2freq 1--1/4freq  2....4

    gd_sflash_device[channel]  = 0;
    gd_sflash_handle[channel]  = 0;
    count = sizeof(gd_sflash_devices_supported)/sizeof(GD_SFLASH_DEV_S);

    // send readID cmd
    cmdBitSet |= (SFLASH_SEND_CMD|                    // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_0|        // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0|       // dummy cycle
                  SFLASH_RWN_READ|                    // read data
                  SFLASH_CMD_MODE_1X|                 // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0|      // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0|            // set the sflash data mode
                  (3<<SFLASH_TRANSFER_BYTE_LOC)       // transfer data number
                  );

    cmdBitSet |= 0x9F; // readID command
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);
    gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
    sflashData = gd_sflash_func[channel].GH_SFLASH_get_Data();
    manufactureID = (U8)((sflashData & 0x00ff0000) >> 16);
    deviceID = (U16)(sflashData & 0x0000FFFF);

    // normal spi serial flash
    for(index=0;index<count;index++)
    {
        device = &(gd_sflash_devices_supported[index]);
        if((manufactureID == device->manufactureID) &&
           (deviceID      == device->deviceID))
        {
            if(manufactureID == 0xbf) // SST sflash which support most quad io cmd
            {
                cmdBitSet |= (0x38|                  // enable quad command
                    SFLASH_SEND_CMD|                 // transfer the command
                    SFLASH_SEND_ADDR_BYTE_NUM_0|     // address num
                    SFLASH_SEND_DUMMY_BYTE_NUM_0|    // dummy cycle
                    SFLASH_RWN_NOTHING|              // no read/write
                    SFLASH_CMD_MODE_1X|              // set command mode
                    SFLASH_ADDR_DUMMY_CYCLE_NUM_0|   // set the sflash adr mode
                    SFLASH_DATA_CYCLE_NUM_0|         // set the sflash data mode
                    (0<<SFLASH_TRANSFER_BYTE_LOC)    // transfer data number
                    );

                sflashCmdBitSet(&SflashCmd, &cmdBitSet);
                gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[channel].GH_SFLASH_get_Data();

                cmdBitSet |= (0xaf|                  // enable quad command
                    SFLASH_SEND_CMD|                 // transfer the command
                    SFLASH_SEND_ADDR_BYTE_NUM_0|     // address num
                    SFLASH_SEND_DUMMY_BYTE_NUM_0|    // dummy cycle
                    SFLASH_RWN_READ|                 // read
                    SFLASH_CMD_MODE_4X|              // set command mode
                    SFLASH_ADDR_DUMMY_CYCLE_NUM_0|   // set the sflash adr mode
                    SFLASH_DATA_CYCLE_NUM_2|         // set the sflash data mode
                    (3<<SFLASH_TRANSFER_BYTE_LOC)    // transfer data number
                    );

                sflashCmdBitSet(&SflashCmd, &cmdBitSet);
                gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);

                sflashData = gd_sflash_func[channel].GH_SFLASH_get_Data();

                manufactureID = (U8)((sflashData & 0x00ff0000) >> 16);
                deviceID = (U16)(sflashData & 0x0000FFFF);

                if(manufactureID != 0xbf || deviceID != 0x2601)
                {
                    return(GD_ERR_SFLASH_TYPE_NOT_SUPPORTED);
                }

                // ok read the protection bit for each block
                SflashCmd.bitc.code = 0x72;          // read block protection register
                SflashCmd.bitc.datanum = 0x6;        // transfer data number

                gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
                prot1 = gd_sflash_func[channel].GH_SFLASH_get_Data();
                prot2 = gd_sflash_func[channel].GH_SFLASH_get_Data();

                // ok write enable the device
                SflashCmd.bitc.code = 0x06;          // enable quad command
                SflashCmd.bitc.rwn =  SFLASH_RWN_NOTHING>>15;//3; no read/write
                SflashCmd.bitc.datanum = 0;
                gd_sflash_func[channel].GH_SFLASH_set_Command( SflashCmd.all );
                gd_sflash_func[channel].GH_SFLASH_get_Data();

                // program the prot bit
                SflashCmd.bitc.code = 0x42;          // enable quad command
                SflashCmd.bitc.rwn = SFLASH_RWN_WRITE>>15;//1; //write
                SflashCmd.bitc.datanum = 6;
                prot1 = 0x0;
                prot2 = 0x0;
                gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[channel].GH_SFLASH_set_Data(prot1);
                gd_sflash_func[channel].GH_SFLASH_set_Data(prot2);

                // wait the program
                SflashCmd.bitc.code = 0x05;          // read status
                SflashCmd.bitc.rwn = SFLASH_RWN_READ>>15;//0; //read
                SflashCmd.bitc.datanum = 1;
                do
                {
                    gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
                    status = gd_sflash_func[device->channel].GH_SFLASH_get_Data()&0xff;
                }while((status & 0x80) == 0x80);

                // ok read the protection bit for each block
                SflashCmd.bitc.code = 0x72;          // enable quad command
                SflashCmd.bitc.datanum = 0x6;        // transfer data number
                gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
                prot1 = gd_sflash_func[channel].GH_SFLASH_get_Data();
                prot2 = gd_sflash_func[channel].GH_SFLASH_get_Data();
            }
            
            else if(device->manufactureID == 0x0c2)
            {
                cmdBitSet |= (0x2b|                  // command
                    SFLASH_SEND_CMD|                 // transfer the command
                    SFLASH_SEND_ADDR_BYTE_NUM_0|     // address num
                    SFLASH_SEND_DUMMY_BYTE_NUM_0|    // dummy cycle
                    SFLASH_RWN_READ|                 // read data
                    SFLASH_CMD_MODE_1X|              // set the sflash cmd mode
                    SFLASH_ADDR_DUMMY_CYCLE_NUM_0|   // set the sflash adr mode
                    SFLASH_DATA_CYCLE_NUM_0|         // set the sflash data mode
                    (1<<SFLASH_TRANSFER_BYTE_LOC)    // transfer data number
                    );

                sflashCmdBitSet(&SflashCmd,&cmdBitSet);
                gd_sflash_func[channel].GH_SFLASH_set_Command( SflashCmd.all );
                status = gd_sflash_func[channel].GH_SFLASH_get_Data() & 0xff;
                if((status&0x80) == 0x80)
                {
                    SflashCmd.bitc.code = device->commands->writeEnable; // command
                    SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;// 3; // not read & write
                    SflashCmd.bitc.datanum = 0x0;    // not transfer data
                    gd_sflash_func[channel].GH_SFLASH_set_Command( SflashCmd.all );
                    gd_sflash_func[channel].GH_SFLASH_get_Data();
                    SflashCmd.bitc.code = 0x05;      // read status
                    SflashCmd.bitc.rwn = SFLASH_RWN_READ>>15;//0; //read
                    SflashCmd.bitc.datanum = 1;

                    do
                    {
                        gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
                        status = gd_sflash_func[channel].GH_SFLASH_get_Data() & 0xff;
                    }while((status&0x01) == 0x01);

                    SflashCmd.bitc.code = 0x98; //command
                    SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;// 3; // not read & write
                    SflashCmd.bitc.datanum = 0x0; //not transfer data
                    gd_sflash_func[channel].GH_SFLASH_set_Command( SflashCmd.all );
                    gd_sflash_func[channel].GH_SFLASH_get_Data();
                    SflashCmd.bitc.code = 0x05; //read status
                    SflashCmd.bitc.rwn = SFLASH_RWN_READ>>15;//0; //read
                    SflashCmd.bitc.datanum = 1;

                    do
                    {
                        gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
                        status = gd_sflash_func[channel].GH_SFLASH_get_Data() & 0xff;
                    }while((status & 0x01) == 0x01);
                }
				if(device->ioMode & GD_SFLASH_4X_READ)
				{
	                    // check if the chip support 4X read mode?
	                cmdBitSet |= (0x5A|                           /*command RDSFDP*/
		                        SFLASH_SEND_CMD|                            /*transfer the command*/
	                        SFLASH_SEND_ADDR_BYTE_NUM_3|                /*address num*/
	                        SFLASH_SEND_DUMMY_BYTE_NUM_1|               /*dummy cycle*/
	                        SFLASH_RWN_READ|                            /*read data*/
	                        SFLASH_CMD_MODE_1X|                         /*set the sflash cmd mode*/
	                        SFLASH_ADDR_DUMMY_CYCLE_NUM_0|              /*set the sflash adr mode*/
	                        SFLASH_DATA_CYCLE_NUM_0|                    /*set the sflash data mode*/
	                        SFLASH_TRANSFER_BYTE_NUM_4|                 /*transfer data number*/
	                        SFLASH_HOLD_TIME_100ns
	                        );

	                sflashCmdBitSet(&SflashCmd,&cmdBitSet);
	                gd_sflash_func[channel].GH_SFLASH_set_Command( SflashCmd.all );
	                gd_sflash_func[channel].GH_SFLASH_set_Data( 0x30 );
	                sflash_data = gd_sflash_func[channel].GH_SFLASH_get_Data();


                    // command-address-data
                    // 0x32[bit12]=1:1-2-2
                    // 0x32[bit13]=1:1-2-4
                    // 0x32[bit14]=1:1-4-4
                    // sflash_data=0x30 31 32 33
                    if((sflash_data != 0x00000000) || (sflash_data != 0xFFFFFFFF))
                    {
                		device->ioMode &= 0xFFFFFFF8;
                        if(sflash_data & 0x00006000)
                        {
                    		device->ioMode |= GD_SFLASH_4X_READ;

                        	GM_Printf("support 4X mode read:0x%08x\n", sflash_data);
                        }
                        else
                        {
                            device->ioMode |= GD_SFLASH_1X_READ;
							device->ioMode &= ~GD_SFLASH_4X_READ;
	                        GM_Printf("not support 4X mode read:0x%08x\n", sflash_data);
                        }
                    }
				}
            }
            device->devicechannel = devicechannel;
            device->channel       = channel;
            gd_sflash_device[channel] = device;
            gd_sflash_handle[channel]  = gd_sflash_device[channel] ;
            *pHandle = (GD_HANDLE)(void*)gd_sflash_handle[channel] ;
            return( GD_OK );
        }
    }

    // spi nand flash: send readID cmd
    cmdBitSet |= (SFLASH_SEND_CMD|                    // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_1|        // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0|       // dummy cycle
                  SFLASH_RWN_READ|                    // read data
                  SFLASH_CMD_MODE_1X|                 // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0|      // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0|            // set the sflash data mode
                  (2<<SFLASH_TRANSFER_BYTE_LOC)       // transfer data number
                  );

    cmdBitSet |= 0x9F; // readID command
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);
    gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
    gd_sflash_func[channel].GH_SFLASH_set_Data(0x00);
    sflashData = gd_sflash_func[channel].GH_SFLASH_get_Data();

    manufactureID = (U8)((sflashData & 0x0000FF00) >> 8);
    deviceID      = (U16)(sflashData & 0x000000FF);
    for(index=0;index<count;index++)
    {
        device = &(gd_sflash_devices_supported[index]);
        if((manufactureID == device->manufactureID) &&
           (deviceID      == device->deviceID))
        {
            device->devicechannel = devicechannel;
            device->channel       = channel;
            gd_sflash_device[channel] = device;
            gd_sflash_handle[channel]  = gd_sflash_device[channel] ;
            *pHandle = (GD_HANDLE)(void*)gd_sflash_handle[channel] ;
            return( GD_OK );
        }
    }

    // spi nand flash: send readID cmd
    cmdBitSet |= (SFLASH_SEND_CMD|                    // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_1|        // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0|       // dummy cycle
                  SFLASH_RWN_READ|                    // read data
                  SFLASH_CMD_MODE_1X|                 // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0|      // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0|            // set the sflash data mode
                  (3<<SFLASH_TRANSFER_BYTE_LOC)       // transfer data number
                  );

    cmdBitSet |= 0x9F; // readID command
    sflashCmdBitSet(&SflashCmd, &cmdBitSet);
    gd_sflash_func[channel].GH_SFLASH_set_Command(SflashCmd.all);
    gd_sflash_func[channel].GH_SFLASH_set_Data(0x00);
    sflashData = gd_sflash_func[device->channel].GH_SFLASH_get_Data();

    manufactureID = (U8)((sflashData & 0x00FF0000) >> 16);
    deviceID      = (U16)(sflashData & 0x0000FFFF);
    for(index=0;index<count;index++)
    {
        device = &(gd_sflash_devices_supported[index]);
        if((manufactureID == device->manufactureID) &&
           (deviceID      == device->deviceID))
        {
            // Set to BUF 1 mode
            if(device->manufactureID == 0xEF)
            {
                U32 status1;
                device->devicechannel = devicechannel;
                device->channel       = channel;
                gd_sflash_device[channel] = device;
                gd_sflash_handle[channel]  = gd_sflash_device[channel] ;
                *pHandle = (GD_HANDLE)(void*)gd_sflash_handle[channel] ;

                // 1. read out the status firstly
                cmdBitSet = (device->commands->readStatus      |   // command
                             SFLASH_SEND_CMD                   |   // transfer the command
                             SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                             SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                             SFLASH_RWN_READ                   |   // read data
                             SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                             SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                             SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                             (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                             SFLASH_HOLD_TIME_100ns
                            );
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xb0);
                status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
                GM_Printf("GD_SFLASH_EnableIO4\nreadStatus(0xb0):0x%02x\n",status1);
#endif

                // 2. set BUF bit, then write it back into register
                cmdBitSet = (device->commands->writeStatus     |   // command
                             SFLASH_SEND_CMD                   |   // transfer the command
                             SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                             SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                             SFLASH_RWN_WRITE                  |   // write data
                             SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                             SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                             SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                             (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                             SFLASH_HOLD_TIME_100ns
                             );
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                status1 = (status1 | 0x08);                        // QE[bit0]
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xb0);
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(status1);
            }
            return( GD_OK );
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
    GD_SFLASH_DEV_S* device;
    if(!pHandle)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    device = sflashGetDevice(*pHandle);
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
GERR GD_SFLASH_EnableIO4(GD_HANDLE* pHandle)
{
    U8 status1, status2 = 0;
    U32 data = 0;
    U32 cmdBitSet = 0;
    GD_SFLASH_DEV_S* device;
    GH_SFLASH_COMMAND_S SflashCmd;
    if(!pHandle)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    device = sflashGetDevice(*pHandle);
    if(device == NULL)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    
    if(device->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        // after initialization, the SST enter IO4 mode automatically!
        if(device->manufactureID == 0xbf)
        {
            return GD_OK;
        }

        if(device->manufactureID == 0x1c)
        {
            cmdBitSet |= (0x38                          |   // enable quad command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_NOTHING            |   // no read/write
                          SFLASH_CMD_MODE_1X            |   // set command mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                         );
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            gd_sflash_func[device->channel].GH_SFLASH_get_Data();
            return GD_OK;
        }
        /* first read the status */
        cmdBitSet |= (device->commands->readStatus      |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_READ                   |   // read data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;

        
        if((device->manufactureID == 0xef)  ||              // winbond read status2
           (device->manufactureID == 0x01)  ||              // for FL064P;Tom.wang;2010-10-21
           (device->manufactureID == 0xc8))                 // for GD liujinyng2011-10-12
        {
            SflashCmd.bitc.code = 0x35;                     // command
            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status2 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
        }

        /* write enable the device */
//            SflashCmd.bitc.code = 0x50;// command
            SflashCmd.bitc.code = device->commands->writeEnable;
        SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;        // not read & write
        SflashCmd.bitc.datanum = 0x0;                       // not transfer data
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();

        sflashReleaseDevice(*pHandle);
//        sflashWelDoneWait(*pHandle);
        device = sflashGetDevice(*pHandle);

        if(device->manufactureID == 0xc2)
        {
            data = status1 | 0x40;
        }
        else if(device->manufactureID == 0xef)              // winbond nand
        {
            data = (status2 | 0x2);
        }
        else if(device->manufactureID == 0x01)              // for FL064P;Tom.wang;2010-10-21
        {
            data = ((status1 & 0x63) << 8) + (status2 | 0x2);
        }
        else if(device->manufactureID == 0xc8)
        {
            data = status2 | 0x2;
        }
        /* write the status register */
        if(device->manufactureID == 0x01)
        {
            cmdBitSet |= (device->commands->writeStatus     |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // read data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                          (2<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                         );
        }
        else if((device->manufactureID == 0xc8)||(device->manufactureID == 0xef))
        {
            cmdBitSet |= (0x31                              |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // read data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                          (1<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                         );
        }
        else
        {
            cmdBitSet |= (device->commands->writeStatus     |   // command
                          SFLASH_SEND_CMD                   |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                          SFLASH_RWN_WRITE                  |   // read data
                          SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                          (1<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                         );
        }
        
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(data);

        sflashWipDoneWait(*pHandle);
        sflashReleaseDevice(*pHandle);
    }
    else if(device->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        // 1. read out the status firstly
        cmdBitSet = (device->commands->readStatus      |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_READ                   |   // read data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                    );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xb0);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_EnableIO4\nreadStatus(0xb0):0x%02x\n",status1);
#endif

        // 2. set QE bit, then write it back into register
        cmdBitSet = (device->commands->writeStatus     |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_WRITE                  |   // write data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = (status1 | 0x01);                        // QE[bit0]
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xb0);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(status1);
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
GERR GD_SFLASH_DisEnableIO4( GD_HANDLE* pHandle )
{
    U8 status1, status2 = 0;
    U32 data = 0;
    U32 cmdBitSet = 0;
    GD_SFLASH_DEV_S* device;
    GH_SFLASH_COMMAND_S SflashCmd;

    if(!pHandle)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    device = sflashGetDevice(*pHandle);
    if(device == NULL)
    {
        return(GD_ERR_BAD_PARAMETER);
    }


    if(device->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        // after initialization, the SST enter IO4 mode automatically!
        // so here simply do nothing at all!
        if(device->manufactureID == 0xbf)
        {
            return GD_OK;
        }

        if(device->manufactureID == 0x1c)
        {
            cmdBitSet |= (0xff                          |   // disable quad command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_NOTHING            |   // no read/write
                          SFLASH_CMD_MODE_4X            |   // set command mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          (0<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                         );
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            gd_sflash_func[device->channel].GH_SFLASH_get_Data();
            return GD_OK;
        }

        /* first read the status */
        cmdBitSet |= (device->commands->readStatus      |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_READ                   |   // read data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_DisEnableIO4\nreadStatus(nor):0x%02x\n",status1);
#endif

        if((device->manufactureID == 0xef)  ||              // winbond read status2
           (device->manufactureID == 0x01)  ||              // for FL064P;Tom.wang;2010-10-21
           (device->manufactureID == 0xc8))                 // for GD liujinyng2011-10-12
        {
            SflashCmd.bitc.code = 0x35;                     // command
            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status2 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
        }
        /* write enable the device */
        SflashCmd.bitc.code = device->commands->writeEnable;// command
        SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;        // not read & write
        SflashCmd.bitc.datanum = 0x0;                       // not transfer data
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();

        sflashReleaseDevice(*pHandle);
//        sflashWelDoneWait(*pHandle);
        device = sflashGetDevice(*pHandle);


        if(device->manufactureID == 0xc2)
        {
            //data = status1 & (~0x40);                       // clear quad //for GK7101 workaround do not enable reset mode otherwise code can not bootup
            data = status1;                                                  
        }
        else if(device->manufactureID == 0xef)
        {
            data = (status2 & (~0x2));     //clear the quad
        }
        else if(device->manufactureID == 0x01)              // for FL064P;Tom.wang;2010-10-21
        {
            data = ((status1 & 0x63) << 8) + (status2 & (~0x2));     //clear the quad
        }
        else if(device->manufactureID == 0xc8)
        {
            data = status2 & (~0x2);
        }

        /* write the status register */
        SflashCmd.bitc.code = device->commands->writeStatus;// command
        SflashCmd.bitc.rwn = SFLASH_RWN_WRITE>>15;          // write
        if(device->manufactureID == 0xc2)
        {
            SflashCmd.bitc.datanum = 0x1;                   // transfer data
        }
        else if(device->manufactureID == 0xef)
        {
            SflashCmd.bitc.code = 0x31;
            SflashCmd.bitc.datanum = 0x1;                   // transfer data
        }
        else if(device->manufactureID == 0x01)              // for FL064P;Tom.wang;2010-10-21
        {
            SflashCmd.bitc.datanum = 0x2;                   // transfer data
        }
        else if(device->manufactureID == 0xc8)
        {
            SflashCmd.bitc.code = 0x31;
            SflashCmd.bitc.datanum = 0x1;                   // transfer data
        }
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(data);

        sflashWipDoneWait(*pHandle);
        sflashReleaseDevice(*pHandle);
//        sflashWelDoneWait(*pHandle);

    }
    else if(device->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        // 1. read out the status firstly
        cmdBitSet = (device->commands->readStatus      |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_READ                   |   // read data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                    );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xb0);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_DisEnableIO4\nreadStatus(0xb0):0x%02x\n",status1);
#endif

        // 2. clear QE bit, then write it back into register
        cmdBitSet = (device->commands->writeStatus     |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_WRITE                  |   // write data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = (status1 & 0xfe);                        // QE[bit0]
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xb0);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(status1);
    }
    return GD_OK;
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
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 startAddr, endAddr, startPage, endPage;
    SFLASH_get_Data get_Data;
    get_Data = gd_sflash_func[device->channel].GH_SFLASH_get_Data;

    if(device->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        cmdBitSet |= (device->commands->readData    |   // command
                      SFLASH_SEND_CMD               |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                      SFLASH_RWN_READ               |   // read data
                      SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                      SFLASH_TRANSFER_BYTE_NUM_4    |   // transfer data number
                      SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);
        while(words--)
        {
            *buffer++ = get_Data();
        }
        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        startPage   = address / device->pageBytes;
        startAddr   = address % device->pageBytes;
        endPage     = (address + words * 4) / device->pageBytes;
        endAddr     = (address + words * 4) % device->pageBytes;

        spiNandFlashRead(handle, buffer, startPage, startAddr, endPage, endAddr);
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
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 startAddr, endAddr, startPage, endPage;
    SFLASH_get_Data get_Data;
    get_Data = gd_sflash_func[device->channel].GH_SFLASH_get_Data;

    if(device->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        if(device->manufactureID == 0x20)
        {
            cmdBitSet |= (device->commands->readData2   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_2  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_1 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_1       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else
        {
            cmdBitSet |= (device->commands->readData2   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_1  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_1 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_1       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);

        while(words--)
        {
            *buffer++ = get_Data();
        }
        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        startPage   = address / device->pageBytes;
        startAddr   = address % device->pageBytes;
        endPage     = (address + words * 4) / device->pageBytes;
        endAddr     = (address + words * 4) % device->pageBytes;

        spiNandFlashRead(handle, buffer, startPage, startAddr, endPage, endAddr);
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
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 startAddr, endAddr, startPage, endPage;
    SFLASH_get_Data get_Data;
    get_Data = gd_sflash_func[device->channel].GH_SFLASH_get_Data;


    if(device->manufactureID == 0x20)
    {
        result = GD_OK;
    }
    if(device->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        if(device->manufactureID == 0xbf)
        {
            cmdBitSet |= (device->commands->readData4   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_1  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_4X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_2 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else if(device->manufactureID == 0x1c)
        {
            cmdBitSet |= (device->commands->readData4   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_3  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_4X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_2 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else if(device->manufactureID == 0x20)
        {
            cmdBitSet |= (device->commands->readData4   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_5  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_2 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else if(device->manufactureID == 0x01)
        {
           cmdBitSet |= (device->commands->readData4    |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_3  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_2 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        
        else
        {
           cmdBitSet |= (device->commands->readData4    |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_3  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_2 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);
        sflashEnableIO4Hw(handle,GTRUE);
        while(words--)
        {
            *buffer++ = get_Data();
        }
        sflashEnableIO4Hw(handle,GFALSE);
        if(device->manufactureID == 0x20)
        {
            result = sflashWipDoneWait(handle);
        }
        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        startPage   = address / device->pageBytes;
        startAddr   = address % device->pageBytes;
        endPage     = (address + words * 4) / device->pageBytes;
        endAddr     = (address + words * 4) % device->pageBytes;

        result      = spiNandFlashRead(handle, buffer, startPage, startAddr, endPage, endAddr);
        sflashReleaseDevice(handle);
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    address &= 0xFFFFFFFC;

    if((address + (sizeof(U32) * words) - 4) >= device->deviceBytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!buffer)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO4)
        {
            old_feature = GD_SFLASH_FEATURE_IO4;
            if(device->manufactureID != 0x20)
            {
                gerr = GD_SFLASH_EnableIO4(&handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }    
        gerr = GD_SFLASH_ReadIO4(handle, address, buffer, words);
    }
    else if((device->ioMode & 0x0F) == GD_SFLASH_2X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO2)
        {
            old_feature = GD_SFLASH_FEATURE_IO2;
            if(device->manufactureID != 0x20)
            {
                gerr = GD_SFLASH_DisEnableIO4(&handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
        gerr = GD_SFLASH_ReadIO2(handle, address, buffer, words);
    }
    else if((device->ioMode & 0x0F) == GD_SFLASH_1X_READ)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO1)
        {
            old_feature = GD_SFLASH_FEATURE_IO1;
            if(device->manufactureID != 0x20)
            {
                gerr = GD_SFLASH_DisEnableIO4(&handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }    
        gerr = GD_SFLASH_ReadIO1(handle, address, buffer, words);
    }
    else
    {
        gerr = GD_ERR_SFLASH_TYPE_NOT_SUPPORTED;
    }

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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 count;
    U32 pageWords;
    U32 writeWords = words;
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GERR result = GD_ERR_SFLASH_WRITE;
    U32 startAddr, endAddr, startPage, endPage;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)gd_sflash_func[device->channel].GH_SFLASH_set_Data;

    pageWords = device->pageBytes / sizeof(U32);
    count = 0;

    if(device->type == GD_SPI_NOR)                                  // check if spi-nor flash
    {
        while(writeWords--)
        {
            if(count == 0)
            {
                //
                // issue a write command sequence to prepare
                // the device for data to be written
                //
                sflashGetDevice(handle);
                cmdBitSet |= (device->commands->writeEnable     |   // command
                              SFLASH_SEND_CMD                   |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                              SFLASH_RWN_NOTHING                |   // no read/write data
                              SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                              (0<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                              SFLASH_HOLD_TIME_100ns
                             );
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_get_Data();

                cmdBitSet |= (device->commands->programPage     |   // command
                              SFLASH_SEND_CMD                   |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_3       |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                              SFLASH_RWN_WRITE                  |   // write data
                              SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                              SFLASH_TRANSFER_BYTE_NUM_4        |   // transfer data number
                              SFLASH_HOLD_TIME_100ns
                             );
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);
            }
            set_Data(*buffer++);
            count++;
            address += 4;

            if((address % device->pageBytes) == 0)
            {
                //
                // we are at a page boundary so we have to
                // wait until the WIP status to be cleared
                // by the device
                //
                result = sflashWipDoneWait(handle);

                if(result != GD_OK)
                    break;

                count = 0;
                sflashReleaseDevice(handle);
            }
        }

        // new added for the case that words < pageWords
        if(words < pageWords)
        {
            result = sflashWipDoneWait(handle);
            if(result != GD_OK)
            {
                return(result);
            }
        }
        sflashGetDevice(handle);

        cmdBitSet |= (device->commands->readStatus      |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_READ                   |   // read data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                      SFLASH_HOLD_TIME_100ns
                      );

        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();
        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                            // check if spi-nand flash
    {
        startPage   = address / device->pageBytes;
        startAddr   = address % device->pageBytes;
        endPage     = (address + words * 4) / device->pageBytes;
        endAddr     = (address + words * 4) % device->pageBytes;

        result      = spiNandFlashWrite(handle, buffer, startPage, startAddr, endPage, endAddr);
    }
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 count;
    U32 pageWords;
    U32 writeWords = words;
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GERR result = GD_ERR_SFLASH_WRITE;
    U32 startAddr, endAddr, startPage, endPage;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)gd_sflash_func[device->channel].GH_SFLASH_set_Data;

    if(device->type == GD_SPI_NOR)                                  // check if spi-nor flash
    {
        pageWords = device->pageBytes / sizeof(U32);
        count = 0;
        while(writeWords--)
        {
            if(count == 0)
            {
                sflashGetDevice(handle);
                //
                // issue a write command sequence to prepare
                // the device for data to be written
                //
                cmdBitSet |= (device->commands->writeEnable |   // command
                              SFLASH_SEND_CMD               |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                              SFLASH_RWN_NOTHING            |   // no read/write data
                              SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                              (0<<SFLASH_TRANSFER_BYTE_LOC) |    // transfer data number
                              SFLASH_HOLD_TIME_100ns
                             );
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command( SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_get_Data();

                cmdBitSet |= (device->commands->programPage2|   // command
                              SFLASH_SEND_CMD               |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                              SFLASH_RWN_WRITE              |   // write data
                              SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_1       |   // set the sflash data mode
                              SFLASH_TRANSFER_BYTE_NUM_4    |  // transfer data number
                              SFLASH_HOLD_TIME_100ns
                             );
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);
            }
            set_Data(*buffer++);
            count++;
            address += 4;

            if((address % device->pageBytes) == 0)
            {
                //
                // we are at a page boundary so we have to
                // wait until the WIP status to be cleared
                // by the device
                //
                result = sflashWipDoneWait(handle);
                if(result != GD_OK)
                    break;

                count = 0;
                sflashReleaseDevice(handle);
            }
        }

        sflashGetDevice(handle);
        // new added for the case that words < pageWords
        if(words < pageWords)
        {
            result = sflashWipDoneWait(handle);
            if(result != GD_OK)
            {
                return(result);
            }
        }

        cmdBitSet |= (device->commands->readStatus      |   // command
                     SFLASH_SEND_CMD                    |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_0        |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0       |   // dummy cycle
                     SFLASH_RWN_READ                    |   // read data
                     SFLASH_CMD_MODE_1X                 |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_1      |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_1            |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)          // transfer data number
                     );

        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();
        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                            // check if spi-nand flash
    {
        startPage   = address / device->pageBytes;
        startAddr   = address % device->pageBytes;
        endPage     = (address + words * 4) / device->pageBytes;
        endAddr     = (address + words * 4) % device->pageBytes;

        result      = spiNandFlashWrite(handle, buffer, startPage, startAddr, endPage, endAddr);
    }
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 count;
    U32 pageWords;
    U32 writeWords = words;
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GERR result = GD_ERR_SFLASH_WRITE;
    U32 startAddr, endAddr, startPage, endPage;
    SFLASH_set_Data set_Data;
    set_Data = (SFLASH_set_Data)gd_sflash_func[device->channel].GH_SFLASH_set_Data;


    if(device->type == GD_SPI_NOR)                                  // check if spi-nor flash
    {
        pageWords = device->pageBytes / sizeof(U32);
        count = 0;
        while(writeWords--)
        {
            if(count == 0)
            {
                sflashGetDevice(handle);
                //
                // issue a write command sequence to prepare
                // the device for data to be written
                //
                cmdBitSet |= (device->commands->writeEnable     |   // command
                              SFLASH_SEND_CMD                   |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                              SFLASH_RWN_NOTHING                |   // no read/write data
                              SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                              (0<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                              SFLASH_HOLD_TIME_100ns
                             );

                if(device->manufactureID == 0xbf)
                {
                    cmdBitSet |= SFLASH_CMD_MODE_4X;
                }
                else if(device->manufactureID == 0x1c)
                {
                    cmdBitSet |= SFLASH_CMD_MODE_4X;
                }
                else if(device->manufactureID == 0xC2)
                {
                    cmdBitSet |= SFLASH_CMD_MODE_1X;
                }
                else
                {
                    cmdBitSet |= SFLASH_CMD_MODE_1X;
                }
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_get_Data();

                cmdBitSet |= (device->commands->programPage4    |   // command
                              SFLASH_SEND_CMD                   |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_3       |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                              SFLASH_RWN_WRITE                  |   // write data
                            //SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                            //SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_2           |   // set the sflash data mode
                              (0x1f<<SFLASH_TRANSFER_BYTE_LOC)  |   // transfer data number
                              SFLASH_HOLD_TIME_100ns
                             );

                if(device->manufactureID == 0xbf)                   // SST
                {
                    cmdBitSet |= SFLASH_CMD_MODE_4X;                // set the sflash cmd mode
                }
                else if(device->manufactureID == 0x1c)              // eon
                {
                    cmdBitSet |= SFLASH_CMD_MODE_4X;
                }
                else if(device->manufactureID == 0xC2)
                {
                    cmdBitSet |= SFLASH_CMD_MODE_1X;
                }
                else
                {
                    cmdBitSet |= SFLASH_CMD_MODE_1X;                // set the sflash cmd mode
                }

                if(device->manufactureID == 0xc2)                   // MX sflash
                {
                    cmdBitSet |= SFLASH_ADDR_DUMMY_CYCLE_NUM_2;     // set the sflash adr mode
                }
                else if(device->manufactureID == 0xbf)              // SST
                {
                    cmdBitSet |= SFLASH_ADDR_DUMMY_CYCLE_NUM_2;     // set the sflash adr mode
                }
                else if(device->manufactureID == 0xef)              // winbond sflash
                {
                    cmdBitSet |= SFLASH_ADDR_DUMMY_CYCLE_NUM_0;     // set the sflash adr mode
                }
                else if(device->manufactureID == 0x01)              // for FL064P;Tom.wang;2010-10-21
                {
                    cmdBitSet |= SFLASH_ADDR_DUMMY_CYCLE_NUM_0;     // set the sflash adr mode
                }
                else if(device->manufactureID == 0x20)
                {
                    cmdBitSet |= SFLASH_ADDR_DUMMY_CYCLE_NUM_2;
                }
                else if(device->manufactureID == 0xc8)              // Giga-Device
                {
                    cmdBitSet |= SFLASH_ADDR_DUMMY_CYCLE_NUM_0;
                }
                else if(device->manufactureID == 0x1c)              // eon
                {
                    cmdBitSet |= SFLASH_ADDR_DUMMY_CYCLE_NUM_2;
                }
                sflashCmdBitSet(&SflashCmd, &cmdBitSet);

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);
                sflashEnableIO4Hw(handle,GTRUE);
            }

            set_Data(*buffer++);
            count++;
            address += 4;

            if((address % device->pageBytes) == 0)
            {
                sflashEnableIO4Hw(handle,GFALSE);
                //
                // we are at a page boundary so we have to
                // wait until the WIP status to be cleared
                // by the device
                //
                result = sflashWipDoneWait(handle);
                if(result != GD_OK)
                    break;

                count = 0;
                sflashReleaseDevice(handle);
                sflashEnableIO4Hw(handle,GTRUE);
            }
        }
        sflashEnableIO4Hw(handle,GFALSE);
        sflashGetDevice(handle);
        // new added for the case that words < pageWords
        //if(words < pageWords)
        {
            result = sflashWipDoneWait(handle);
            if(result != GD_OK)
            {
                return(result);
            }
        }
        cmdBitSet |= (device->commands->readStatus  |   // command
                      SFLASH_SEND_CMD               |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                      SFLASH_RWN_READ               |   // read data
                    //SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                    //SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                     );
        if(device->manufactureID == 0xbf)               // SST
        {
            cmdBitSet |= (SFLASH_CMD_MODE_4X | SFLASH_DATA_CYCLE_NUM_2);
        }
        if(device->manufactureID == 0xC2)               // SST
        {
            cmdBitSet |= (SFLASH_CMD_MODE_4X | SFLASH_DATA_CYCLE_NUM_0);
        }
        else
        {
            cmdBitSet |= (SFLASH_CMD_MODE_1X | SFLASH_DATA_CYCLE_NUM_0);
        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();
        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                            // check if spi-nand flash
    {

        startPage   = address / device->pageBytes;
        startAddr   = address % device->pageBytes;
        endPage     = (address + words * 4) / device->pageBytes;
        endAddr     = (address + words * 4) % device->pageBytes;

        result      = spiNandFlashWrite(handle, buffer, startPage, startAddr, endPage, endAddr);

        sflashReleaseDevice(handle);
    }
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    address &= 0xFFFFFFFC;

    if((address + (sizeof(U32) * words) - 4) >= device->deviceBytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!buffer)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if((device->ioMode & 0xF0) == GD_SFLASH_4X_WRITE)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO4)
        {
            old_feature = GD_SFLASH_FEATURE_IO4;
            if(device->manufactureID != 0x20)
            {
                gerr = GD_SFLASH_EnableIO4(&handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
        gerr = GD_SFLASH_WriteIO4(handle, address, buffer, words);
    }
    else if((device->ioMode & 0xF0) == GD_SFLASH_2X_WRITE)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO2)
        {
            old_feature = GD_SFLASH_FEATURE_IO2;
            if(device->manufactureID != 0x20)
            {
                gerr = GD_SFLASH_DisEnableIO4(&handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
        gerr = GD_SFLASH_WriteIO2(handle, address, buffer, words);
    }
    else if((device->ioMode & 0xF0) == GD_SFLASH_1X_WRITE)
    {
        if(old_feature != GD_SFLASH_FEATURE_IO1)
        {
            old_feature = GD_SFLASH_FEATURE_IO1;
            if(device->manufactureID != 0x20)
            {
                gerr = GD_SFLASH_DisEnableIO4(&handle);                 /*enable the IO4 mode*/
            }
            if(gerr != 0)
            {
                return gerr;
            }
        }
        gerr = GD_SFLASH_WriteIO1(handle, address, buffer, words);
    }
    else
    {
        gerr = GD_ERR_SFLASH_TYPE_NOT_SUPPORTED;
    }

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
    GD_SFLASH_DEV_S* device = sflashGetDevice( handle );
    U32 offset;
    U32 index;
    U32 sectorAddress = 0;
    U16 sectorFirst   = 0;
    U16 sectorLast    = 0;
    U16 sectorIndex   = 0;
    U32 sectorWords   = 0;
    GBOOL isEmpty;
    GERR result;

    if( !device )
        return( GD_ERR_INVALID_HANDLE );

    address &= 0xFFFFFFFC;

    if( ( address + ( words * sizeof(U32) - 4 ) ) >= device->deviceBytes )
        return( GD_ERR_BAD_PARAMETER );

    if( !buffer )
        return( GD_ERR_BAD_PARAMETER );

    if( device->sectorBytes > sizeof(gd_flash_sector_buffer) )
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

        if( sectorIndex == sectorFirst || sectorIndex == sectorLast )
        {
            //
            // only the first and the last sector data needs to be
            // buffered as these sectors may be overwritten just
            // partly, all sectors between will be filled completly
            // so there is no need to buffer them
            //
            result = GD_SFLASH_Read( handle, sectorAddress, gd_flash_sector_buffer, sectorWords );
            if( result != GD_OK )
                return( GD_ERR_SFLASH_READ );

            isEmpty = GTRUE;       //add;Tom wang;2010-10-21
            for( index=0; index < sectorWords; index++ )
            {
                if( gd_flash_sector_buffer[index] != 0xFFFFFFFF )
                {
                    isEmpty = GFALSE;
                    break; //add;Tom wang;2010-10-21
                }
            }
        }
        else
        {
            result = GD_SFLASH_IsSectorEmpty( handle, sectorIndex, &isEmpty ); //move;tom.wang;2010-10-21
            if( result != GD_OK )
                return( result );
        }

        if( sectorFirst == sectorLast )
        {
            //
            // copy only 'words' data from the start address
            // all within the first sector
            //
            offset = ( address - sectorAddress ) / sizeof(U32);
            index=0;
            while( words-- )
            {
                gd_flash_sector_buffer[offset+index] = *buffer++;
                index++;
            }
        }
        else if( sectorIndex == sectorFirst )
        {
            //
            // copy only data from the start address
            // up to the end of the first sector
            //
            offset = ( address - sectorAddress ) / sizeof(U32);
            for( index=0; index < sectorWords-offset; index++ )
            {
                gd_flash_sector_buffer[offset+index] = *buffer++;
                words--;
            }
        }
        else if( sectorIndex == sectorLast )
        {
            for( index=0; words > 0; index++ )
            {
                gd_flash_sector_buffer[index] = *buffer++;
                words--;
            }
        }
        else
        {
            for( index=0; index < sectorWords; index++ )
            {
                gd_flash_sector_buffer[index] = *buffer++;
                words--;
            }
        }

        /*result = GD_SFLASH_IsSectorEmpty( handle, sectorIndex, &isEmpty ); //move;tom.wang;2010-10-21
        if( result != GD_OK )
            return( result );*/

        if( !isEmpty )
        {
            result = GD_SFLASH_EraseSector( handle, sectorIndex );
            if( result != GD_OK )
                return( result );
        }

        result = GD_SFLASH_Write( handle, sectorAddress, gd_flash_sector_buffer, sectorWords );
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    GERR result;
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    U32 CESetting = 0x0E;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }
    CESetting = CESetting | ((U32)device->devicechannel << 6);

    // so far spi-nand chip of Micro and Giga-Device hasn't such feature
    if(device->type == GD_SPI_NAND)                     // check if spi-nand flash
    {
        return(GD_ERR_SFLASH_TYPE_NOT_SUPPORTED);
    }
    gd_sflash_func[device->channel].GH_SFLASH_set_CE(CESetting);

    cmdBitSet |= (device->commands->writeEnable     |   // command
                  SFLASH_SEND_CMD                   |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                  SFLASH_RWN_NOTHING                |   // no read/write data
                  //SFLASH_CMD_MODE_1X              |   // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                  (0<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                  SFLASH_HOLD_TIME_100ns
                  );
    if(device->manufactureID == 0xbf)                   // SST
        cmdBitSet |= SFLASH_CMD_MODE_4X;                // set the sflash cmd mode
    else
        cmdBitSet |= SFLASH_CMD_MODE_1X;                // set the sflash cmd mode

    sflashCmdBitSet(&SflashCmd, &cmdBitSet);
    gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
    gd_sflash_func[device->channel].GH_SFLASH_get_Data();

    SflashCmd.bitc.code = device->commands->eraseChip;  // command
    gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
    gd_sflash_func[device->channel].GH_SFLASH_set_Data(0);

    result = sflashWipDoneWait( handle );

    cmdBitSet |= (device->commands->writeDisable    |   // command
                  SFLASH_SEND_CMD                   |   // transfer the command
                  SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                  SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                  SFLASH_RWN_NOTHING                |   // no read/write data
                //SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                  SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                  SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                  (0<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                 );

    if(device->manufactureID == 0xbf)                   // SST
        cmdBitSet |= SFLASH_CMD_MODE_4X;                // set the sflash cmd mode
    else
        cmdBitSet |= SFLASH_CMD_MODE_1X;                // set the sflash cmd mode

    sflashCmdBitSet(&SflashCmd,&cmdBitSet);
    gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
    gd_sflash_func[device->channel].GH_SFLASH_get_Data();

    sflashReleaseDevice(handle);
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
**     available serial flash sectors [0..sectorCount-1].
** - GD_ERR_SFLASH_ERASE if the bulk erase command has failed
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_EraseSector(GD_HANDLE handle, U16 sectorIndex)
{
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 address     = 0;
    U32 cmdBitSet   = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GERR result;
    U32 CESetting = 0x0E;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    
    CESetting = CESetting | ((U32)device->devicechannel << 6);

    if(sectorIndex >= device->sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(old_feature == GD_SFLASH_FEATURE_IO4)
    {
        old_feature = GD_SFLASH_FEATURE_IO1;
        if(device->manufactureID != 0x20)
        {
            GD_SFLASH_DisEnableIO4(&handle);               /*disable the IO4 mode*/
        }
    }
    result = GD_SFLASH_GetSectorAddress(handle, sectorIndex, &address);
    if(result != GD_OK)
    {
        return(result);
    }
    gd_sflash_func[device->channel].GH_SFLASH_set_CE(CESetting);

    if(device->type == GD_SPI_NOR)                        // check if spi-nor flash
    {
    
        GD_SFLASH_SetResetMode(handle,GTRUE);

        cmdBitSet |= (device->commands->writeEnable     | // command
                      SFLASH_SEND_CMD                   | // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       | // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      | // dummy cycle
                      SFLASH_RWN_NOTHING                | // no read/write data
                    //SFLASH_CMD_MODE_1X                | // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     | // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           | // set the sflash data mode
                     (0<<SFLASH_TRANSFER_BYTE_LOC)      | // transfer data number
                      SFLASH_HOLD_TIME_100ns
                      );

        if(device->manufactureID == 0xbf)                 // SST
        {
            cmdBitSet |= SFLASH_CMD_MODE_4X;              // set the sflash cmd mode
        }
        else
        {
            cmdBitSet |= SFLASH_CMD_MODE_1X;              // set the sflash cmd mode
        }

        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();

        SflashCmd.bitc.code = device->commands->eraseSector;    // command
        SflashCmd.bitc.adrnum = 3;                              // address num
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);

        result = sflashWipDoneWait(handle);

        SflashCmd.bitc.code = device->commands->writeDisable;   // command
        if(device->manufactureID == 0xbf)                       // SST
        {
            SflashCmd.bitc.cmdmode = 2;                         // set the sflash cmd mode
        }
        else
        {
            SflashCmd.bitc.cmdmode = 0;                         // set the sflash cmd mode
        }
        SflashCmd.bitc.adrnum = 0;                              // address num

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();
        GD_SFLASH_SetResetMode(handle,GFALSE);
    }
    else if(device->type == GD_SPI_NAND)                  // check if spi-nand flash
    {
        result = spiNandFlashEraseSector(handle, address);
    }

    
    sflashReleaseDevice(handle);
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
** \param manufactureID The address of a variable where to write the manufactor
**                        id into
** \param deviceID      The address of a variable where to write the device
**                        id into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given manufactureID points to 0
** - GD_ERR_BAD_PARAMETER if the given deviceID points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetCodes(GD_HANDLE handle, U8* manufactureID, U16* deviceID)
{
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!manufactureID)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!deviceID)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *manufactureID = device->manufactureID;
    *deviceID = device->deviceID;
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
** \param manufactureName The address of a string pointer variable where to
**                          write the address to the manufactor name into
** \param deviceName      The address of a string pointer variable where to
**                          write the address to the device name into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given manufactureName points to 0
** - GD_ERR_BAD_PARAMETER if the given deviceName points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetNames(GD_HANDLE handle, char** manufactureName, char** deviceName)
{
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!manufactureName)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!deviceName)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *manufactureName = device->manufactureName;
    *deviceName = device->deviceName;
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
** \param sectorCount The address of a variable where to write the resulting
**                      count into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorCount points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetNumberOfSectors(GD_HANDLE handle, U16* sectorCount)
{
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    *sectorCount = device->sectorCount;
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!sectorAddress)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(sectorIndex >= device->sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    *sectorAddress = sectorIndex * device->sectorBytes;
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(sectorIndex >= device->sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!sectorWords)
        return(GD_ERR_BAD_PARAMETER);

    *sectorWords = device->sectorBytes / sizeof(U32);
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(address >= device->deviceBytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!sectorIndex)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *sectorIndex = address / device->sectorBytes;
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!deviceWords)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *deviceWords = device->deviceBytes / sizeof(U32);
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
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
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
    for(sectorIndex=0; sectorIndex < device->sectorCount; sectorIndex++)
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
    GERR result;
    GD_SFLASH_DEV_S* device = sflashGetDevice(handle);
    U32 words;
    U32 cmdBitSet = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    int i;

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(sectorIndex >= device->sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!isEmpty)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(device->type == GD_SPI_NOR)                          // check if spi-nor flash
    {
        sflashGetDevice(handle);
        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            if(device->manufactureID == 0x20)
            {
                result = GD_OK;
            }
            cmdBitSet |= (device->commands->readData4   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                        //SFLASH_SEND_DUMMY_BYTE_NUM_1  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                        //SFLASH_CMD_MODE_4X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_2 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );

            if(device->manufactureID == 0xbf)               // SST
            {
                // set dummy cycle, set the sflash cmd mode
                cmdBitSet |= (SFLASH_SEND_DUMMY_BYTE_NUM_1 | SFLASH_CMD_MODE_4X);
            }
            else if(device->manufactureID == 0x20)          // Numonyx
            {
                // set dummy cycle, set the sflash cmd mode
                cmdBitSet |= (SFLASH_SEND_DUMMY_BYTE_NUM_5 | SFLASH_CMD_MODE_1X);
            }
            else if(device->manufactureID == 0x1c)          // EON
            {
                cmdBitSet |= (SFLASH_SEND_DUMMY_BYTE_NUM_3 | SFLASH_CMD_MODE_4X);
            }
            else                                            // for all others
            {
                // set dummy cycle, set the sflash cmd mode
                cmdBitSet |= (SFLASH_SEND_DUMMY_BYTE_NUM_3 | SFLASH_CMD_MODE_1X);
            }
        }
        else if((device->ioMode & 0x0F) == GD_SFLASH_2X_READ)
        {
            cmdBitSet |= (device->commands->readData2   |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_1  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_1 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_1       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
        }
        else
        {
            cmdBitSet |= (device->commands->readData    |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );

        }
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(sectorIndex * device->sectorBytes);

        words = device->sectorBytes / sizeof(U32);
        *isEmpty = GTRUE;
        while(*isEmpty && words--)
        {
            if(gd_sflash_func[device->channel].GH_SFLASH_get_Data() != 0xFFFFFFFF)
            {
                *isEmpty = GFALSE;
                break;
            }
        }

        if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
        {
            if(device->manufactureID == 0x20)
            {
                sflashWipDoneWait(handle);
            }
        }
        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                    // check if spi-nand flash
    {
        for(i=0;i<device->sectorPages;i++)
        {
            // 1. page read to cache
            cmdBitSet |= (device->commands->pageRead    |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                         );
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            gd_sflash_func[device->channel].GH_SFLASH_set_Data(sectorIndex * device->sectorPages + i);

            // 2. check if page read is done
#ifdef DEBUG_PRINT
            GM_Printf("GD_SFLASH_IsSectorEmpty\n");
#endif
            spiNandFlashOipDoneWait(handle);

            // 3. read from cache
            if((device->ioMode & 0x0F) == GD_SFLASH_4X_READ)
            {
                cmdBitSet |= (device->commands->readData4   |   // command
                              SFLASH_SEND_CMD               |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_2   |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_1  |   // dummy cycle
                              SFLASH_RWN_READ               |   // read data
                              SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_2       |   // set the sflash data mode
                              SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                             );
            }
            else if((device->ioMode & 0x0F) == GD_SFLASH_2X_READ)
            {
                cmdBitSet |= (device->commands->readData2   |   // command
                              SFLASH_SEND_CMD               |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_2   |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_1  |   // dummy cycle
                              SFLASH_RWN_READ               |   // read data
                              SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_1       |   // set the sflash data mode
                              SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                             );
            }
            else
            {
                cmdBitSet |= (device->commands->readData    |   // command
                              SFLASH_SEND_CMD               |   // transfer the command
                              SFLASH_SEND_ADDR_BYTE_NUM_2   |   // address num
                              SFLASH_SEND_DUMMY_BYTE_NUM_1  |   // dummy cycle
                              SFLASH_RWN_READ               |   // read data
                              SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                              SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                              SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                              SFLASH_TRANSFER_BYTE_NUM_4        // transfer data number
                             );
            }
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            // here always start from 0 in the cache
            if(device->manufactureID == 0xEF || device->manufactureID == 0xC8)
            {
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(0x00000000);
            }
            else
            {
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(0x00004000);      // fixed as 2048 wrap
            }

            words = device->pageBytes / sizeof(U32);
            *isEmpty = GTRUE;
            while(*isEmpty && words--)
            {
                if(gd_sflash_func[device->channel].GH_SFLASH_get_Data() != 0xFFFFFFFF)
                {
                    *isEmpty = GFALSE;
                    break;
                }
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
    U32 command;
    U32 cmdBitSet = 0;
    U32 sflashData = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GD_SFLASH_DEV_S* device;
    U8 status1, status2 = 0;

    device = sflashGetDevice(handle);
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(device->type == GD_SPI_NOR)                          // check if spi-nor flash
    {
        if(device->manufactureID == 0xc2)
        {
            cmdBitSet |= (0x2b                          |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                          );
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
            if((status1 & 0x80) == 0x80)
            {
                SflashCmd.bitc.code = device->commands->writeEnable;    // command
                SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;            // not read & write
                SflashCmd.bitc.datanum = 0x0;                           // not transfer data

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_get_Data();
                sflashWipDoneWait(handle);

                SflashCmd.bitc.code = 0x98;                             // command
                SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;            // not read & write
                SflashCmd.bitc.datanum = 0x0;                           // not transfer data

                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_get_Data();
                sflashWipDoneWait(handle);

                return GD_OK;
            }
        }
        cmdBitSet = 0;
        command = device->commands->readStatus;
        cmdBitSet |= (SFLASH_SEND_CMD               |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                      SFLASH_RWN_READ               |   // read data
                      SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                     );
        cmdBitSet |= command;
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data()& 0xff;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Unlock\nreadStatus(nor):0x%02x\n",status1);
#endif

        if((device->manufactureID == 0xef) ||           // winbond read status2
           (device->manufactureID == 0x01) ||           // for FL064P;Tom.wang;2010-10-21
           (device->manufactureID == 0xc8))             // for GD liujinyng2011-10-12
        {
            SflashCmd.bitc.code = 0x35;                 // command
            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status2 = gd_sflash_func[device->channel].GH_SFLASH_get_Data()& 0xff;
        }



         /* write enable the device */
        SflashCmd.bitc.code = device->commands->writeEnable; //command
        SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;    // not read & write
        SflashCmd.bitc.datanum = 0x0;                   // not transfer data

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();

        /* write the status register */
        sflashReleaseDevice(handle);
        sflashGetDevice(handle);

        SflashCmd.bitc.code = device->commands->writeStatus;    // command
        SflashCmd.bitc.rwn = SFLASH_RWN_WRITE>>15;              // write
        if(device->manufactureID == 0xc2)
        {
            SflashCmd.bitc.datanum = 0x1;               // transfer data
            sflashData = status1 & 0x43;
        }
        else if(device->manufactureID == 0xef)
        {
            SflashCmd.bitc.datanum = 0x2;               // transfer data
            sflashData = ((status1 & (0x03)) << 8) + (status2&0x86);
        }
        else if(device->manufactureID == 0x01) //FL064P
        {
            SflashCmd.bitc.datanum = 0x2;               // transfer data
            sflashData = ((status1 & 0x63) << 8) + ((status2 & 0xa) | 0x24);
        }
        else if(device->manufactureID == 0x20)          // N25Q128
        {
            SflashCmd.bitc.datanum = 0x1;               // transfer data
            sflashData = 0;
        }
        else if(device->manufactureID == 0xc8)
        {
            SflashCmd.bitc.datanum = 0x2;               // transfer data
            sflashData = ((status1 & 0x3) << 8) + (status2 & 0x86);
        }
        else if(device->manufactureID == 0x1c)
        {
            SflashCmd.bitc.datanum = 0x1;               // transfer data
            sflashData = status1 & 0xc3;
        }

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(sflashData);

        sflashWipDoneWait(handle);
        sflashReleaseDevice(handle);
        sflashGetDevice(handle);
    }
    // here, suppose always unlock all sectors
    else if(device->type == GD_SPI_NAND)                   // check if spi-nor flash
    {
        // 1. read out the status firstly
        cmdBitSet = (device->commands->readStatus      |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_READ                   |   // read data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                    );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xa0);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Unlock\nreadStatus(0xa0):0x%02x\n",status1);
#endif

        // 2. clear BP2/BP1/BP0, then write it back into register
        cmdBitSet = (device->commands->writeStatus     |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_WRITE                  |   // write data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = (status1 & 0x87);                        // BP2[bit5], BP1[bit4], BP0[bit3]
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xa0);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(status1);
    }
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
    U32 command     = 0;
    U32 address     = 0;
    U32 cmdBitSet   = 0;
    U32 sflashData  = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GD_SFLASH_DEV_S* device;
    U8 status1, status2 = 0;
    U8 i;

    device = sflashGetDevice(handle);
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    // here, suppose always unlock all sectors
    if(device->type == GD_SPI_NOR)                          // check if spi-nor flash
    {
        if(device->manufactureID == 0xc2)
        {
            cmdBitSet |= (0x2b                          |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                          );
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
            if((status1 & 0x80) == 0)
            {
                SflashCmd.bitc.code = 0x68;                 // command
                SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;// not read & write
                SflashCmd.bitc.datanum = 0x0;               // not transfer data
                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_get_Data();
                sflashWipDoneWait(handle);
                i = 0;
                while(i < 3)
                {
                    SflashCmd.bitc.code = 0x2b;             // command
                    SflashCmd.bitc.rwn = SFLASH_RWN_READ>>15;   // not read & write
                    SflashCmd.bitc.datanum = 0x1;           // not transfer data
                    gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                    status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
                    if((status1 & 0x80) == 0x80)
                    {
                        break;
                    }
                    i++;
                    sflashWipDoneWait(handle);
                }
                if(i >= 3)
                {
                    return GD_ERR_TIMEOUT;
                }
            }
            SflashCmd.bitc.code = device->commands->writeEnable;// command
            SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;    // not read & write
            SflashCmd.bitc.datanum = 0x0;                   // not transfer data
            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            gd_sflash_func[device->channel].GH_SFLASH_get_Data();
            sflashWipDoneWait(handle);

            SflashCmd.bitc.code = 0x98;                     // command
            SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;    // not read & write
            SflashCmd.bitc.datanum = 0x0;                   // not transfer data
            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            gd_sflash_func[device->channel].GH_SFLASH_get_Data();
            sflashWipDoneWait(handle);

            for(i=0;i<0x10;i++)
            {
                SflashCmd.bitc.code = device->commands->writeEnable; //command
                SflashCmd.bitc.adrnum = 0;
                SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;// not read & write
                SflashCmd.bitc.datanum = 0x0;               // not transfer data
                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_get_Data();
                sflashWipDoneWait(handle);

                SflashCmd.bitc.code = 0x36;                 // command
                SflashCmd.bitc.adrnum = 3;
                SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;// not read & write
                SflashCmd.bitc.datanum = 0;                 // not transfer data

                GD_SFLASH_GetSectorAddress(handle, i, &address);
                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
                gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);
                sflashWipDoneWait(handle);
            }
            sflashReleaseDevice(handle);
            return GD_OK;
        }
        command = device->commands->readStatus;
        cmdBitSet |= (SFLASH_SEND_CMD               |       // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0   |       // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0  |       // dummy cycle
                      SFLASH_RWN_READ               |       // read data
                      SFLASH_CMD_MODE_1X            |       // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |       // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0       |       // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                     );
        cmdBitSet |= command;
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Lock\nreadStatus(nor):0x%02x\n",status1);
#endif

        if((device->manufactureID == 0xef)  ||              // winbond read status2
           (device->manufactureID == 0x01)  ||              // for FL064P;Tom.wang;2010-10-21
           (device->manufactureID == 0xc8))                 // for GD liujinyng2011-10-12
        {
            SflashCmd.bitc.code = 0x35;                     // command
            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status2 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
        }

        /* write enable the device */
        SflashCmd.bitc.code = device->commands->writeEnable;// command
        SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;        // not read & write
        SflashCmd.bitc.datanum = 0x0;                       // not transfer data

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_get_Data();

        /* write the status register */
        sflashReleaseDevice(handle);
        sflashGetDevice(handle);

        SflashCmd.bitc.code = device->commands->writeStatus;// command
        SflashCmd.bitc.rwn = SFLASH_RWN_WRITE>>15;          // write
        if(device->manufactureID == 0xef)
        {
            SflashCmd.bitc.datanum = 0x2;                   // transfer data
            sflashData = ((status1 | 0x1c) << 8) + status2;
        }
        else if(device->manufactureID == 0x01)              // FL064P
        {
            SflashCmd.bitc.datanum = 0x2;                   // transfer data
            sflashData = (((status1 & 0x63) | 0x10) << 8) + ((status2 & 0xa) | 0x25);
        }
        else if(device->manufactureID == 0x20)              // N25Q128
        {
            SflashCmd.bitc.datanum = 0x1;                   // transfer data
            sflashData = 0xff;
        }
        else if(device->manufactureID == 0xc8)
        {
            SflashCmd.bitc.datanum = 0x2;                   // transfer data
            sflashData = (((status1 & 0x3) | 0x30) << 8) + (status2 & 0x86);
        }
        else if(device->manufactureID == 0x1c)
        {
            SflashCmd.bitc.datanum = 0x1;                   // transfer data
            sflashData = ((status1 & 0xC3) | 0x34);
        }
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(sflashData);

        sflashWipDoneWait(handle);

        sflashReleaseDevice(handle);
    }
    else if(device->type == GD_SPI_NAND)                   // check if spi-nand flash
    {
        // 1. read out the status firstly
        cmdBitSet = (device->commands->readStatus      |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_READ                   |   // read data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                    );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xa0);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_Lock\nreadStatus(0xa0):0x%02x\n",status1);
#endif

        // 2. add BP2/BP1/BP0, then write it back into register
        cmdBitSet = (device->commands->writeStatus     |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_WRITE                  |   // write data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = (status1 | 0x78);                        // BP2[bit5], BP1[bit4], BP0[bit3]
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xa0);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(status1);
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
    U32 cmdBitSet;
    U8 status1, status2 = 0;
    GH_SFLASH_COMMAND_S SflashCmd;
    GD_SFLASH_DEV_S* device;
    U8 i = 0;

    device = sflashGetDevice(handle);
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!isChipLocked)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    cmdBitSet = 0;

    if(device->type == GD_SPI_NOR)                      // check if spi-nor flash
    {
        if(device->manufactureID == 0xc2)
        {
            cmdBitSet |= (0x2b                          |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                         );
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;

            if((status1 & 0x80) == 0)
            {
                *isChipLocked = GFALSE;
                return GD_OK;
            }
            cmdBitSet = 0;
            cmdBitSet |= (0x3c                          |   // command
                          SFLASH_SEND_CMD               |   // transfer the command
                          SFLASH_SEND_ADDR_BYTE_NUM_3   |   // address num
                          SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                          SFLASH_RWN_READ               |   // read data
                          SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                          SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                          SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                          (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                         );
            sflashCmdBitSet(&SflashCmd, &cmdBitSet);

            // totally 16 sectors checked???
            for(i=0;i<0x10;i++)
            {
                GD_SFLASH_GetSectorAddress(handle, i, &address);
                gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);

                gd_sflash_func[device->channel].GH_SFLASH_set_Data(address);
                status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
                if(status1 == 0x0)
                {
                    *isChipLocked = GFALSE;
                    return GD_OK;
                }
                sflashWipDoneWait(handle);
            }
            *isChipLocked = GFALSE;
            return GD_OK;
        }
        cmdBitSet |= (device->commands->readStatus      |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_READ                   |   // read data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                     );

        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_IsChipLock\nreadStatus(nor):0x%02x\n",status1);
#endif

        if((device->manufactureID == 0xef)  ||              // winbond read status2
           (device->manufactureID == 0x01)  ||              // for FL064P;Tom.wang;2010-10-21
           (device->manufactureID == 0xc8))                 // for GD liujinyng2011-10-12
        {
            SflashCmd.bitc.code = 0x35;                     // command
            gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
            status2 = gd_sflash_func[device->channel].GH_SFLASH_get_Data() & 0xff;
        }
        sflashReleaseDevice(handle);

        if(device->manufactureID == 0xc8)
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
        else if(device->manufactureID == 0x1c)
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
        else if(device->manufactureID == 0x01)
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
        else if(device->manufactureID == 0xef)
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
        else
        {
            *isChipLocked = GFALSE;
            return GD_OK;
        }
    }
    // here, though SPI NAND flash could return different lock status even for each sector
    // just to check if chip fully locked to sync with this function of NOR flash
    else if(device->type == GD_SPI_NAND)                    // check if spi-nor flash
    {
        cmdBitSet = (device->commands->readStatus      |   // command
                     SFLASH_SEND_CMD                   |   // transfer the command
                     SFLASH_SEND_ADDR_BYTE_NUM_1       |   // address num
                     SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                     SFLASH_RWN_READ                   |   // read data
                     SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                     SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                     SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                     (1<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                     SFLASH_HOLD_TIME_100ns
                    );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);

        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(0xa0);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data();
#ifdef DEBUG_PRINT
        GM_Printf("GD_SFLASH_IsChipLock\nreadStatus(0xa0):0x%02x\n",status1);
#endif

        sflashReleaseDevice(handle);

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
**        ioMode  IO mode to get
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_GetIoMode(GD_HANDLE handle, GD_SFLASH_RW_E op, GD_SFLASH_IO_MODE_E* ioMode)
{
    U8 temp = 0;
    GD_SFLASH_DEV_S* device = NULL;

    device = sflashGetDevice(handle);
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(op == GD_SFLASH_READ)
    {
        temp = device->ioMode & 0x0F;
    }
    else
    {
        temp = (device->ioMode & 0xF0) >> 4;
    }

    switch(temp)
    {
        case 0x01:
            *ioMode = GD_SFLASH_IO1_MODE;
            break;

        case 0x02:
            *ioMode = GD_SFLASH_IO2_MODE;
            break;

        case 0x04:
            *ioMode = GD_SFLASH_IO4_MODE;
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
**        ioMode  IO mode to be set
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SFLASH_SetIoMode(GD_HANDLE handle, GD_SFLASH_RW_E op, GD_SFLASH_IO_MODE_E ioMode)
{
    U8 temp = 0x00;
    GD_SFLASH_DEV_S* device = NULL;

    device = sflashGetDevice(handle);
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    switch(ioMode)
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
        device->ioMode &= 0xF0;
        device->ioMode |= temp;
    }
    else
    {
        device->ioMode &= 0x0F;
        device->ioMode |= (temp << 0x4);
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
    GH_SFLASH_COMMAND_S SflashCmd;
    GD_SFLASH_DEV_S* device;
    U32 command     = 0;
    device = sflashGetDevice(handle);
    
    if(device == NULL)
    {
        return(GD_ERR_INVALID_HANDLE);
    }
    if((device->manufactureID == 0xc2)||(device->manufactureID == 0x9D))
    {
        cmdBitSet |= (device->commands->writeEnable     |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_NOTHING                |   // no read/write data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (0<<SFLASH_TRANSFER_BYTE_LOC)     |   // transfer data number
                      SFLASH_HOLD_TIME_100ns
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        //gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        //gd_sflash_func[device->channel].GH_SFLASH_get_Data();
        GH_SFLASH_set_Command(SflashCmd.all);
        GH_SFLASH_get_Data();
        cmdBitSet = 0;
        command = device->commands->readStatus;
        cmdBitSet |= (SFLASH_SEND_CMD               |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0   |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0  |   // dummy cycle
                      SFLASH_RWN_READ               |   // read data
                      SFLASH_CMD_MODE_1X            |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0 |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0       |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)     // transfer data number
                     );
        cmdBitSet |= command;
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        status1 = gd_sflash_func[device->channel].GH_SFLASH_get_Data()& 0xff;
        status1 = status1 & (0x83);
        if(mode == GFALSE)
        {
            status1 = status1 | 0x40;
        }
        SflashCmd.bitc.code = device->commands->writeEnable;// command
        SflashCmd.bitc.rwn = SFLASH_RWN_NOTHING>>15;        // not read & write
        SflashCmd.bitc.datanum = 0x0;                       // not transfer data
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(status1);
        sflashWipDoneWait(handle);
        cmdBitSet |= (device->commands->writeStatus     |   // command
                      SFLASH_SEND_CMD                   |   // transfer the command
                      SFLASH_SEND_ADDR_BYTE_NUM_0       |   // address num
                      SFLASH_SEND_DUMMY_BYTE_NUM_0      |   // dummy cycle
                      SFLASH_RWN_WRITE                  |   // read data
                      SFLASH_CMD_MODE_1X                |   // set the sflash cmd mode
                      SFLASH_ADDR_DUMMY_CYCLE_NUM_0     |   // set the sflash adr mode
                      SFLASH_DATA_CYCLE_NUM_0           |   // set the sflash data mode
                      (1<<SFLASH_TRANSFER_BYTE_LOC)         // transfer data number
                     );
        sflashCmdBitSet(&SflashCmd, &cmdBitSet);
        gd_sflash_func[device->channel].GH_SFLASH_set_Command(SflashCmd.all);
        gd_sflash_func[device->channel].GH_SFLASH_set_Data(status1);
        sflashWipDoneWait(handle);
    }
    return(GD_OK);
}
