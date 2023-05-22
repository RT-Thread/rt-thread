/**
  ******************************************************************************
  * @file    bl602_sf_cfg_ext.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "bl602_glb.h"
#include "bl602_sf_cfg_ext.h"
#include "bflb_sf_cfg.h"
#include "bflb_xip_sflash.h"
#include "bl602_romdriver.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SF_CFG_EXT
 *  @{
 */

/** @defgroup  SF_CFG_EXT_Private_Macros
 *  @{
 */
#define BFLB_FLASH_CFG_MAGIC                    "FCFG"

/*@} end of group SF_CFG_EXT_Private_Macros */

/** @defgroup  SF_CFG_EXT_Private_Types
 *  @{
 */
typedef struct {
    uint32_t jedec_id;
    char *name;
    const spi_flash_cfg_type *cfg;
}flash_info_t;

/*@} end of group SF_CFG_EXT_Private_Types */

/** @defgroup  SF_CFG_EXT_Private_Variables
 *  @{
 */
static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flashcfg_fm_25q08={
        .reset_c_read_cmd=0xff,
        .reset_c_read_cmd_size=3,
        .mid=0xc8,

        .de_burst_wrap_cmd=0x77,
        .de_burst_wrap_cmd_dmy_clk=0x3,
        .de_burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .de_burst_wrap_data=0xF0,

        /*reg*/
        .write_enable_cmd=0x06,
        .wr_enable_index=0x00,
        .wr_enable_bit=0x01,
        .wr_enable_read_reg_len=0x01,

        .qe_index=1,
        .qe_bit=0x01,
        .qe_write_reg_len=0x02,
        .qe_read_reg_len=0x1,

        .busy_index=0,
        .busy_bit=0x00,
        .busy_read_reg_len=0x1,
        .release_powerdown=0xab,

        .read_reg_cmd[0]=0x05,
        .read_reg_cmd[1]=0x35,
        .write_reg_cmd[0]=0x01,
        .write_reg_cmd[1]=0x01,

        .fast_read_qio_cmd=0xeb,
        .fr_qio_dmy_clk=16/8,
        .c_read_support=1,
        .c_read_mode=0xa0,

        .burst_wrap_cmd=0x77,
        .burst_wrap_cmd_dmy_clk=0x3,
        .burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .burst_wrap_data=0x40,
         /*erase*/
        .chip_erase_cmd=0xc7,
        .sector_erase_cmd=0x20,
        .blk32_erase_cmd=0x52,
        .blk64_erase_cmd=0xd8,
        /*write*/
        .page_program_cmd=0x02,
        .qpage_program_cmd=0x32,
        .qpp_addr_mode=SF_CTRL_ADDR_1_LINE,

        .io_mode=SF_CTRL_QIO_MODE,
        .clk_delay=1,
        .clk_invert=0x01,

        .reset_en_cmd=0x66,
        .reset_cmd=0x99,
        .c_rexit=0xff,
        .wr_enable_write_reg_len=0x00,

        /*id*/
        .jedec_id_cmd=0x9f,
        .jedec_id_cmd_dmy_clk=0,
        .qpi_jedec_id_cmd=0x9f,
        .qpi_jedec_id_cmd_dmy_clk=0x00,
        .sector_size=4,
        .page_size=256,

        /*read*/
        .fast_read_cmd=0x0b,
        .fr_dmy_clk=8/8,
        .qpi_fast_read_cmd =0x0b,
        .qpi_fr_dmy_clk=8/8,
        .fast_read_do_cmd=0x3b,
        .fr_do_dmy_clk=8/8,
        .fast_read_dio_cmd=0xbb,
        .fr_dio_dmy_clk=0,
        .fast_read_qo_cmd=0x6b,
        .fr_qo_dmy_clk=8/8,

        .qpi_fast_read_qio_cmd=0xeb,
        .qpi_fr_qio_dmy_clk=16/8,
        .qpi_page_program_cmd=0x02,
        .write_vreg_enable_cmd=0x50,

        /* qpi mode */
        .enter_qpi=0x38,
        .exit_qpi=0xff,

         /*AC*/
        .time_e_sector=300,
        .time_e_32k=1200,
        .time_e_64k=1200,
        .time_page_pgm=5,
        .time_ce=33000,
        .pd_delay=20,
        .qe_data=0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flashcfg_gd_md_40d={
        .reset_c_read_cmd=0xff,
        .reset_c_read_cmd_size=3,
        .mid=0x51,

        .de_burst_wrap_cmd=0x77,
        .de_burst_wrap_cmd_dmy_clk=0x3,
        .de_burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .de_burst_wrap_data=0xF0,

        /*reg*/
        .write_enable_cmd=0x06,
        .wr_enable_index=0x00,
        .wr_enable_bit=0x01,
        .wr_enable_read_reg_len=0x01,

        .qe_index=1,
        .qe_bit=0x01,
        .qe_write_reg_len=0x02,
        .qe_read_reg_len=0x1,

        .busy_index=0,
        .busy_bit=0x00,
        .busy_read_reg_len=0x1,
        .release_powerdown=0xab,

        .read_reg_cmd[0]=0x05,
        .read_reg_cmd[1]=0x35,
        .write_reg_cmd[0]=0x01,
        .write_reg_cmd[1]=0x01,

        .fast_read_qio_cmd=0xeb,
        .fr_qio_dmy_clk=16/8,
        .c_read_support=0,
        .c_read_mode=0xA0,

        .burst_wrap_cmd=0x77,
        .burst_wrap_cmd_dmy_clk=0x3,
        .burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .burst_wrap_data=0x40,
         /*erase*/
        .chip_erase_cmd=0xc7,
        .sector_erase_cmd=0x20,
        .blk32_erase_cmd=0x52,
        .blk64_erase_cmd=0xd8,
        /*write*/
        .page_program_cmd=0x02,
        .qpage_program_cmd=0x32,
        .qpp_addr_mode=SF_CTRL_ADDR_1_LINE,

        .io_mode=0x11,
        .clk_delay=1,
        .clk_invert=0x01,

        .reset_en_cmd=0x66,
        .reset_cmd=0x99,
        .c_rexit=0xff,
        .wr_enable_write_reg_len=0x00,

        /*id*/
        .jedec_id_cmd=0x9f,
        .jedec_id_cmd_dmy_clk=0,
        .qpi_jedec_id_cmd=0x9f,
        .qpi_jedec_id_cmd_dmy_clk=0x00,
        .sector_size=4,
        .page_size=256,

        /*read*/
        .fast_read_cmd=0x0b,
        .fr_dmy_clk=8/8,
        .qpi_fast_read_cmd =0x0b,
        .qpi_fr_dmy_clk=8/8,
        .fast_read_do_cmd=0x3b,
        .fr_do_dmy_clk=8/8,
        .fast_read_dio_cmd=0xbb,
        .fr_dio_dmy_clk=0,
        .fast_read_qo_cmd=0x6b,
        .fr_qo_dmy_clk=8/8,

        .qpi_fast_read_qio_cmd=0xeb,
        .qpi_fr_qio_dmy_clk=16/8,
        .qpi_page_program_cmd=0x02,
        .write_vreg_enable_cmd=0x50,

        /* qpi mode */
        .enter_qpi=0x38,
        .exit_qpi=0xff,

         /*AC*/
        .time_e_sector=300,
        .time_e_32k=1200,
        .time_e_64k=1200,
        .time_page_pgm=5,
        .time_ce=33000,
        .pd_delay=20,
        .qe_data=0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flashcfg_xm25qh16={
        .reset_c_read_cmd=0xff,
        .reset_c_read_cmd_size=3,
        .mid=0x20,

        .de_burst_wrap_cmd=0x77,
        .de_burst_wrap_cmd_dmy_clk=0x3,
        .de_burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .de_burst_wrap_data=0xF0,

        /*reg*/
        .write_enable_cmd=0x06,
        .wr_enable_index=0x00,
        .wr_enable_bit=0x01,
        .wr_enable_read_reg_len=0x01,

        .qe_index=1,
        .qe_bit=0x01,
        .qe_write_reg_len=0x01,
        .qe_read_reg_len=0x1,

        .busy_index=0,
        .busy_bit=0x00,
        .busy_read_reg_len=0x1,
        .release_powerdown=0xab,

        .read_reg_cmd[0]=0x05,
        .read_reg_cmd[1]=0x35,
        .write_reg_cmd[0]=0x01,
        .write_reg_cmd[1]=0x31,

        .fast_read_qio_cmd=0xeb,
        .fr_qio_dmy_clk=16/8,
        .c_read_support=1,
        .c_read_mode=0x20,

        .burst_wrap_cmd=0x77,
        .burst_wrap_cmd_dmy_clk=0x3,
        .burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .burst_wrap_data=0x40,
         /*erase*/
        .chip_erase_cmd=0xc7,
        .sector_erase_cmd=0x20,
        .blk32_erase_cmd=0x52,
        .blk64_erase_cmd=0xd8,
        /*write*/
        .page_program_cmd=0x02,
        .qpage_program_cmd=0x32,
        .qpp_addr_mode=SF_CTRL_ADDR_1_LINE,

        .io_mode=SF_CTRL_QIO_MODE,
        .clk_delay=1,
        .clk_invert=0x01,

        .reset_en_cmd=0x66,
        .reset_cmd=0x99,
        .c_rexit=0xff,
        .wr_enable_write_reg_len=0x00,

        /*id*/
        .jedec_id_cmd=0x9f,
        .jedec_id_cmd_dmy_clk=0,
        .qpi_jedec_id_cmd=0x9f,
        .qpi_jedec_id_cmd_dmy_clk=0x00,
        .sector_size=4,
        .page_size=256,

        /*read*/
        .fast_read_cmd=0x0b,
        .fr_dmy_clk=8/8,
        .qpi_fast_read_cmd =0x0b,
        .qpi_fr_dmy_clk=8/8,
        .fast_read_do_cmd=0x3b,
        .fr_do_dmy_clk=8/8,
        .fast_read_dio_cmd=0xbb,
        .fr_dio_dmy_clk=0,
        .fast_read_qo_cmd=0x6b,
        .fr_qo_dmy_clk=8/8,

        .qpi_fast_read_qio_cmd=0xeb,
        .qpi_fr_qio_dmy_clk=16/8,
        .qpi_page_program_cmd=0x02,
        .write_vreg_enable_cmd=0x50,

        /* qpi mode */
        .enter_qpi=0x38,
        .exit_qpi=0xff,

         /*AC*/
        .time_e_sector=400,
        .time_e_32k=1600,
        .time_e_64k=2000,
        .time_page_pgm=5,
        .time_ce=33000,
        .pd_delay=3,
        .qe_data=0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flashcfg_mx_kh25={
        .reset_c_read_cmd=0xff,
        .reset_c_read_cmd_size=3,
        .mid=0xc2,

        .de_burst_wrap_cmd=0x77,
        .de_burst_wrap_cmd_dmy_clk=0x3,
        .de_burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .de_burst_wrap_data=0xF0,

        /*reg*/
        .write_enable_cmd=0x06,
        .wr_enable_index=0x00,
        .wr_enable_bit=0x01,
        .wr_enable_read_reg_len=0x01,

        .qe_index=1,
        .qe_bit=0x01,
        .qe_write_reg_len=0x01,
        .qe_read_reg_len=0x1,

        .busy_index=0,
        .busy_bit=0x00,
        .busy_read_reg_len=0x1,
        .release_powerdown=0xab,

        .read_reg_cmd[0]=0x05,
        .read_reg_cmd[1]=0x00,
        .write_reg_cmd[0]=0x01,
        .write_reg_cmd[1]=0x00,

        .fast_read_qio_cmd=0xeb,
        .fr_qio_dmy_clk=16/8,
        .c_read_support=0,
        .c_read_mode=0x20,

        .burst_wrap_cmd=0x77,
        .burst_wrap_cmd_dmy_clk=0x3,
        .burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .burst_wrap_data=0x40,
         /*erase*/
        .chip_erase_cmd=0xc7,
        .sector_erase_cmd=0x20,
        .blk32_erase_cmd=0x52,
        .blk64_erase_cmd=0xd8,
        /*write*/
        .page_program_cmd=0x02,
        .qpage_program_cmd=0x32,
        .qpp_addr_mode=SF_CTRL_ADDR_1_LINE,

        .io_mode=0x11,
        .clk_delay=1,
        .clk_invert=0x01,

        .reset_en_cmd=0x66,
        .reset_cmd=0x99,
        .c_rexit=0xff,
        .wr_enable_write_reg_len=0x00,

        /*id*/
        .jedec_id_cmd=0x9f,
        .jedec_id_cmd_dmy_clk=0,
        .qpi_jedec_id_cmd=0x9f,
        .qpi_jedec_id_cmd_dmy_clk=0x00,
        .sector_size=4,
        .page_size=256,

        /*read*/
        .fast_read_cmd=0x0b,
        .fr_dmy_clk=8/8,
        .qpi_fast_read_cmd =0x0b,
        .qpi_fr_dmy_clk=8/8,
        .fast_read_do_cmd=0x3b,
        .fr_do_dmy_clk=8/8,
        .fast_read_dio_cmd=0xbb,
        .fr_dio_dmy_clk=0,
        .fast_read_qo_cmd=0x6b,
        .fr_qo_dmy_clk=8/8,

        .qpi_fast_read_qio_cmd=0xeb,
        .qpi_fr_qio_dmy_clk=16/8,
        .qpi_page_program_cmd=0x02,
        .write_vreg_enable_cmd=0x50,

        /* qpi mode */
        .enter_qpi=0x38,
        .exit_qpi=0xff,

         /*AC*/
        .time_e_sector=300,
        .time_e_32k=1200,
        .time_e_64k=1200,
        .time_page_pgm=5,
        .time_ce=33000,
        .pd_delay=20,
        .qe_data=0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flashcfg_zd_25q16b={
        .reset_c_read_cmd=0xff,
        .reset_c_read_cmd_size=3,
        .mid=0xba,

        .de_burst_wrap_cmd=0x77,
        .de_burst_wrap_cmd_dmy_clk=0x3,
        .de_burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .de_burst_wrap_data=0xF0,

        /*reg*/
        .write_enable_cmd=0x06,
        .wr_enable_index=0x00,
        .wr_enable_bit=0x01,
        .wr_enable_read_reg_len=0x01,

        .qe_index=1,
        .qe_bit=0x01,
        .qe_write_reg_len=0x02,
        .qe_read_reg_len=0x1,

        .busy_index=0,
        .busy_bit=0x00,
        .busy_read_reg_len=0x1,
        .release_powerdown=0xab,

        .read_reg_cmd[0]=0x05,
        .read_reg_cmd[1]=0x35,
        .write_reg_cmd[0]=0x01,
        .write_reg_cmd[1]=0x01,

        .fast_read_qio_cmd=0xeb,
        .fr_qio_dmy_clk=16/8,
        .c_read_support=1,
        .c_read_mode=0xa0,

        .burst_wrap_cmd=0x77,
        .burst_wrap_cmd_dmy_clk=0x3,
        .burst_wrap_data_mode=SF_CTRL_DATA_4_LINES,
        .burst_wrap_data=0x40,
         /*erase*/
        .chip_erase_cmd=0xc7,
        .sector_erase_cmd=0x20,
        .blk32_erase_cmd=0x52,
        .blk64_erase_cmd=0xd8,
        /*write*/
        .page_program_cmd=0x02,
        .qpage_program_cmd=0x32,
        .qpp_addr_mode=SF_CTRL_ADDR_1_LINE,

        .io_mode=0x14,
        .clk_delay=1,
        .clk_invert=0x01,

        .reset_en_cmd=0x66,
        .reset_cmd=0x99,
        .c_rexit=0xff,
        .wr_enable_write_reg_len=0x00,

        /*id*/
        .jedec_id_cmd=0x9f,
        .jedec_id_cmd_dmy_clk=0,
        .qpi_jedec_id_cmd=0x9f,
        .qpi_jedec_id_cmd_dmy_clk=0x00,
        .sector_size=4,
        .page_size=256,

        /*read*/
        .fast_read_cmd=0x0b,
        .fr_dmy_clk=8/8,
        .qpi_fast_read_cmd =0x0b,
        .qpi_fr_dmy_clk=8/8,
        .fast_read_do_cmd=0x3b,
        .fr_do_dmy_clk=8/8,
        .fast_read_dio_cmd=0xbb,
        .fr_dio_dmy_clk=0,
        .fast_read_qo_cmd=0x6b,
        .fr_qo_dmy_clk=8/8,

        .qpi_fast_read_qio_cmd=0xeb,
        .qpi_fr_qio_dmy_clk=16/8,
        .qpi_page_program_cmd=0x02,
        .write_vreg_enable_cmd=0x50,

        /* qpi mode */
        .enter_qpi=0x38,
        .exit_qpi=0xff,

         /*AC*/
        .time_e_sector=300,
        .time_e_32k=1200,
        .time_e_64k=1200,
        .time_page_pgm=5,
        .time_ce=33000,
        .pd_delay=20,
        .qe_data=0,
};

static const ATTR_TCM_CONST_SECTION flash_info_t flash_infos[]={
    {
        .jedec_id=0x1440A1,
        //.name="FM_25Q08",
        .cfg=&flashcfg_fm_25q08,
    },
    {
        .jedec_id=0x134051,
        //.name="GD_MD04D_04_33",
        .cfg=&flashcfg_gd_md_40d,
    },
    {
        .jedec_id=0x144020,
        //.name="XM_25QH80_80_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x154020,
        //.name="XM_25QH16_16_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x164020,
        //.name="XM_25QH32_32_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x174020,
        //.name="XM_25QH64_64_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x1320C2,
        //.name="MX_KH40_04_33",
        .cfg=&flashcfg_mx_kh25,
    },
    {
        .jedec_id=0x1420C2,
        //.name="MX_KH80_08_33",
        .cfg=&flashcfg_mx_kh25,
    },
    {
        .jedec_id=0x1520C2,
        //.name="MX_KH16_16_33",
        .cfg=&flashcfg_mx_kh25,
    },
    {
        .jedec_id=0x13325E,
        //.name="ZB_D40B_80_33",
        .cfg=&flashcfg_mx_kh25,
    },
    {
        .jedec_id=0x14325E,
        //.name="ZB_D80B_80_33",
        .cfg=&flashcfg_mx_kh25,
    },
    {
        .jedec_id=0x15405E,
        //.name="ZB_25Q16B_15_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x16405E,
        //.name="ZB_25Q32B_16_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x17405E,
        //.name="ZB_25VQ64_64_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x15605E,
        //.name="ZB_25VQ16_16_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x15345E,
        //.name="ZB_25WQ16_16_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x1560EB,
        //.name="TH_25Q16",
        .cfg=&flashcfg_fm_25q08,
    },
    {
        .jedec_id=0x1740C8,
        //.name="GD_25Q64E_64_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x1840C8,
        //.name="GD_25Q127C_128_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x176085,
        //.name="Puya_P25Q64H_64_33",
        .cfg=&flashcfg_xm25qh16,
    },
    {
        .jedec_id=0x17400B,
        //.name="XT_25F64B",
        .cfg=&flashcfg_fm_25q08,
    },
    {
        .jedec_id=0x1560BA,
        //.name="ZD_25Q16B",
        .cfg=&flashcfg_zd_25q16b,
    },
    {
        .jedec_id=0x1460CD,
        //.name="TH_25Q80HB",
        .cfg=&flashcfg_fm_25q08,
    },
    {
        .jedec_id=0x1870EF,
        //.name="W25Q128JV_128_33",
        .cfg=&flashcfg_xm25qh16,
    },
};

/*@} end of group SF_CFG_EXT_Private_Variables */

/** @defgroup  SF_CFG_EXT_Global_Variables
 *  @{
 */

/*@} end of group SF_CFG_EXT_Global_Variables */

/** @defgroup  SF_CFG_EXT_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SF_CFG_EXT_Private_Fun_Declaration */

/** @defgroup  SF_CFG_EXT_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Get flash config according to flash ID
 *
 * @param  flash_id: Flash ID
 * @param  p_flash_cfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_sf_cfg_get_flash_cfg_need_lock_ext(uint32_t flash_id, spi_flash_cfg_type * p_flash_cfg,
                                                             uint8_t group, uint8_t bank)
{
    uint32_t i;
    uint8_t buf[sizeof(spi_flash_cfg_type)+8];
    uint32_t crc,*p_crc;
    char flash_cfg_magic[] = "FCFG";

    if(flash_id==0){
        bflb_xip_sflash_read_via_cache_need_lock(8+BL602_FLASH_XIP_BASE,buf,sizeof(spi_flash_cfg_type)+8,group,bank);
        if(BL602_MemCmp(buf,flash_cfg_magic,4)==0){
            crc=BFLB_Soft_CRC32((uint8_t *)buf+4,sizeof(spi_flash_cfg_type));
            p_crc=(uint32_t *)(buf+4+sizeof(spi_flash_cfg_type));
            if(*p_crc==crc){
                BL602_MemCpy_Fast(p_flash_cfg,(uint8_t *)buf+4,sizeof(spi_flash_cfg_type));
                return 0 ;
            }
        }
    }else{
        if(bflb_sf_cfg_get_flash_cfg_need_lock(flash_id, p_flash_cfg, group, bank) == 0){
            return 0;
        }
        for(i=0;i<sizeof(flash_infos)/sizeof(flash_infos[0]);i++){
            if(flash_infos[i].jedec_id==flash_id){
                BL602_MemCpy_Fast(p_flash_cfg,flash_infos[i].cfg,sizeof(spi_flash_cfg_type));
                return 0;
            }
        }
    }

    return -1;
}

/****************************************************************************//**
 * @brief  Identify one flash
 *
 * @param  call_from_flash: code run at flash or ram
 * @param  autoScan: Auto scan all GPIO pin
 * @param  flash_in_cfg: Specify flash GPIO config, not auto scan
 * @param  restore_default: Wether restore default flash GPIO config
 * @param  p_flash_cfg: Flash config pointer
 *
 * @return Flash ID
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION bflb_sf_cfg_flash_identify_ext(uint8_t call_from_flash, uint8_t flash_in_cfg,
                uint8_t restore_default, spi_flash_cfg_type * p_flash_cfg, uint8_t group, uint8_t bank)
{
    uint32_t jedec_id=0;
    uint32_t i=0;
    uint32_t ret=0;

    ret=bflb_sf_cfg_flash_identify(call_from_flash,flash_in_cfg,restore_default,p_flash_cfg,group,bank);
    if(call_from_flash){
        bflb_sflash_set_xip_cfg(p_flash_cfg,p_flash_cfg->io_mode&0xf,1,0,32,bank);
    }
    if((ret&BFLB_FLASH_ID_VALID_FLAG)!=0){
        return ret;
    }

    jedec_id=(ret&0xffffff);
    for(i=0;i<sizeof(flash_infos)/sizeof(flash_infos[0]);i++){
        if(flash_infos[i].jedec_id==jedec_id){
            BL602_MemCpy_Fast(p_flash_cfg,flash_infos[i].cfg,sizeof(spi_flash_cfg_type));
            break;
        }
    }
    if(i==sizeof(flash_infos)/sizeof(flash_infos[0])){
        return jedec_id;
    }else{
        return (jedec_id|BFLB_FLASH_ID_VALID_FLAG);
    }
}

/*@} end of group SF_CFG_EXT_Public_Functions */

/*@} end of group SF_CFG_EXT */

/*@} end of group BL602_Peripheral_Driver */
