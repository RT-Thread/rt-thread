/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "de_eink.h"

#define EE_CTL               (0x000)
#define EE_IRQ               (0x004)
#define EE_IDX_GEN           (0x008)
#define EE_IMG_SIZE          (0x00c)
#define EE_LAST_IMG_ADDR     (0x010)
#define EE_LAST_IMG_PITCH    (0x014)
#define EE_CURR_IMG_ADDR     (0x018)
#define EE_CURR_IMG_PITCH    (0x01c)
#define EE_LAST_IDX_ADDR     (0x020)
#define EE_IDX_WIN0          (0x024)
#define EE_IDX_WIN1          (0x028)
#define EE_NEW_IDX_ADDR      (0x02c)

#define EE_PIPE_EN           (0x040)
#define EE_PIPE_WIN0         (0x044)
#define EE_PIPE_WIN1         (0x048)
#define EE_WAV_FILE_ADDR     (0x04c)

#define EE_DEC_CTL           (0x150)
#define EE_DEC_IDX_ADDR      (0x154)
#define EE_DEC_WAV_ADDR      (0x158)
#define EE_DEC_WAV_PITCH     (0x15c)

#define EDMA_GLB_CTL         (0x400)
#define EDMA_CTL             (0x404)
#define EDMA_WAV_ADDR        (0x408)
#define EDMA_WAV_PITCH       (0x40c)
#define EDMA_WAV_SIZE        (0x410)
#define EDMA_IMG_COOR        (0x414)
#define EDMA_IMG_SIZE        (0x418)
#define EDMA_PIXEL_VALUE     (0x41c)

#define EDMA_WB_ADDR         (0x440)
#define EDMA_WB_STS          (0x444)

static unsigned long ee_base;

/* #define ee_writel writel */
/* #define ee_readl readl */
#define EINK_RUINT32(offset)          (*((volatile u32 *)((offset))))
#define EINK_WUINT32(value, offset)   (*((volatile u32 *)((offset))) = (value))


extern s32 disp_delay_us(u32 us);
extern s32 disp_delay_ms(u32 ms);

int eink_set_base(unsigned long reg_base)
{
    ee_base = reg_base;

    return 0;
}
/*
*int eink_set_mode(unsigned char in_mode, unsigned char out_mode)
*{
*   unsigned int tmp;
*
*   tmp = ((out_mode&0x1)<<4)|(in_mode&0x3);
*   EINK_WUINT32(tmp,ee_base + EE_CTL);
*
*   return 0;
*
*}
*/
s32 eink_config(unsigned char in_mode, unsigned int out_mode)
{
    unsigned int tmp;

    tmp = ((out_mode&0x1)<<4)|(in_mode&0x3);
    EINK_WUINT32(tmp, ee_base + EE_CTL);

    return 0;
}

int eink_irq_enable(void)
{
    EINK_WUINT32(1<<4, ee_base + EE_IRQ);

/*  unsigned int tmp;
 *  tmp = EINK_RUINT32(ee_base + EE_IRQ);
 *  pr_info("eink_irq_en 0x%x\n", tmp);
 */
    return 0;
}

int eink_irq_disable(void)
{
    EINK_WUINT32(0, ee_base + EE_IRQ);

    return 0;
}

int eink_irq_query(void)
{
    unsigned int idx_irq, dec_irq;
    unsigned reg_val = 0;

    reg_val = EINK_RUINT32(ee_base + EE_IRQ);
    dec_irq = reg_val&0x1;
    idx_irq = reg_val&0x2;

    if (dec_irq == 0x1) {
        EINK_WUINT32(reg_val&0x1d, ee_base + EE_IRQ);
        return 0;
    }
    if (idx_irq == 0x2) {
        EINK_WUINT32(reg_val&0x1e, ee_base + EE_IRQ);
        return 1;
    }
    return -1;
}

int eink_irq_query_index(void)
{
    unsigned int idx_irq;
    unsigned reg_val = 0;

    reg_val = EINK_RUINT32(ee_base + EE_IRQ);
    idx_irq = reg_val&0x2;

    if (idx_irq == 0x2) {
        EINK_WUINT32(reg_val&0x1e, ee_base + EE_IRQ);
        return 1;
    }
    return -1;

}

/*
int eink_start_idx (u32 disp, u32 old_index_data_paddr,
            u32 new_index_data_paddr, struct ee_img* last_image,
            struct ee_img* current_image, unsigned char flash_mode,
            unsigned char win_en, struct area_info* area)
{
    return 0;

}
*/

int eink_start_idx(struct ee_img *last_img, struct ee_img *curr_img,
        unsigned char flash_mode, unsigned char win_en,
        unsigned long last_idx_addr, unsigned long curr_idx_addr,
        struct area_info *info)
{
    unsigned int tmp, w, h;
    unsigned int x, y;

    x = 0;
    y = 0;
    w = last_img->w?(last_img->w-1)&0xfff:0;
    h = last_img->h?(last_img->h-1)&0xfff:0;
    tmp = ((h<<16)|w);
    EINK_WUINT32(tmp, ee_base + EE_IMG_SIZE);
    /* tmp = last_img->y*last_img->pitch + last_img->x + last_img->addr; */
    tmp = y*last_img->pitch + x + last_img->addr;
    EINK_WUINT32(tmp, ee_base + EE_LAST_IMG_ADDR);
    EINK_WUINT32(last_img->pitch, ee_base + EE_LAST_IMG_PITCH);

    /* tmp = curr_img->y*curr_img->pitch + curr_img->x + curr_img->addr; */

    tmp = y*curr_img->pitch + x + curr_img->addr;
    EINK_WUINT32(tmp, ee_base + EE_CURR_IMG_ADDR);
    EINK_WUINT32(curr_img->pitch, ee_base + EE_CURR_IMG_PITCH);

    if (!win_en) {
        tmp = ((info->y_top&0xfff)<<16)|(info->x_top&0xfff);
        EINK_WUINT32(tmp, ee_base + EE_IDX_WIN0);
        tmp = ((info->y_bottom&0xfff)<<16)|(info->x_bottom&0xfff);
        EINK_WUINT32(tmp, ee_base + EE_IDX_WIN1);
    }

    EINK_WUINT32(last_idx_addr, ee_base + EE_LAST_IDX_ADDR);
    EINK_WUINT32(curr_idx_addr, ee_base + EE_NEW_IDX_ADDR);

    tmp = (flash_mode&0x3)<<8;
    tmp |= (win_en&0x1)<<4;
    tmp |= 0x1;
    EINK_WUINT32(tmp, ee_base + EE_IDX_GEN);

    return 0;
}

int eink_index_finish(void)
{
    unsigned int reg_val;

    reg_val = EINK_RUINT32(ee_base + EE_IRQ)&0x2;
    if (reg_val == 0x2)
        return 1;
    else
        return 0;
}

int eink_get_updata_area(struct area_info *info)
{
    unsigned int reg_val;

    reg_val = EINK_RUINT32(ee_base + EE_IDX_WIN0);
    info->x_top = reg_val & 0xfff;
    info->y_top = (reg_val >> 16) & 0xfff;

    reg_val = EINK_RUINT32(ee_base + EE_IDX_WIN1);
    info->x_bottom = reg_val & 0xfff;
    info->y_bottom = (reg_val >> 16) & 0xfff;

    return 0;
}

int eink_pipe_enable(unsigned int pipe_no)
{
    unsigned int pipe_base;
    unsigned int reg_val;

    pipe_base = ee_base + EE_PIPE_EN + (pipe_no << 4);
    EINK_WUINT32(0x1, pipe_base);

    reg_val = EINK_RUINT32(pipe_base);
    return 0;
}

int eink_pipe_disable(unsigned int pipe_no)
{
    unsigned int pipe_base;

    pipe_base = ee_base + EE_PIPE_EN + (pipe_no << 4);
    EINK_WUINT32(0x0, pipe_base);

    return 0;
}

int  eink_pipe_config(struct area_info *info, unsigned int pipe_no)
{
    unsigned int pipe_base, tmp;

    tmp = ((info->y_top & 0xfff) << 16)|(info->x_top & 0xfff);
    pipe_base = ee_base + EE_PIPE_WIN0 + (pipe_no << 4);
    EINK_WUINT32(tmp, pipe_base);

    tmp = ((info->y_bottom & 0xfff) << 16)|(info->x_bottom & 0xfff);
    pipe_base = ee_base + EE_PIPE_WIN1 + (pipe_no << 4);
    EINK_WUINT32(tmp, pipe_base);
/*
*   pipe_base = ee_base + EE_WAV_FILE_ADDR + (pipe_no<<4);
*   EINK_WUINT32(wav_file_addr,pipe_base);
*/
    return 0;
}

int eink_pipe_config_wavefile(unsigned long wav_file_addr, unsigned int pipe_no)
{
    unsigned int pipe_base;

    pipe_base = ee_base + EE_WAV_FILE_ADDR + (pipe_no << 4);
    EINK_WUINT32(wav_file_addr, pipe_base);


    return 0;
}

int eink_decoder_start(unsigned long new_idx_addr, unsigned long wav_data_addr,
                        struct eink_init_param *para)
{
    unsigned int w, h, tmp;

    w = para->timing.width ? (para->timing.width - 1) & 0xfff : 0;
    h = para->timing.height ? (para->timing.height - 1) & 0xfff : 0;
    tmp = ((h << 16) | w);
    EINK_WUINT32(tmp, ee_base + EE_IMG_SIZE);

    tmp = para->eink_mode ? (((para->timing.lbl + para->timing.lsl +
                    para->timing.lel) << 2) +
                    (para->timing.width >> 1)) :
                    (((para->timing.lbl + para->timing.lsl +
                       para->timing.lel) << 1) +
                     (para->timing.width >> 1));
    EINK_WUINT32(tmp, ee_base + EE_DEC_WAV_PITCH);
    EINK_WUINT32(new_idx_addr, ee_base + EE_DEC_IDX_ADDR);

    tmp = para->eink_mode ? ((para->timing.fbl + para->timing.fsl) * tmp +
                ((para->timing.lbl + para->timing.lsl) << 2)) :
                 ((para->timing.fbl + para->timing.fsl) * tmp +
                  ((para->timing.lbl + para->timing.lsl) << 1));

    tmp += wav_data_addr;
    EINK_WUINT32(tmp, ee_base + EE_DEC_WAV_ADDR);

    EINK_WUINT32(0x1, ee_base + EE_DEC_CTL);

    return 0;
}

int eink_edma_init(unsigned char mode)
{
    unsigned int tmp;

    tmp = 0x1<<31;
    tmp |= (mode<<4);
    tmp |= 0x1;
    EINK_WUINT32(tmp, ee_base + EDMA_CTL);

    tmp = 0x1<<31;


/*  tmp |= (0x1<<16); */
    EINK_WUINT32(tmp, ee_base + EDMA_GLB_CTL);
/*  tmp = EINK_RUINT32(ee_base + EDMA_GLB_CTL);*/
/*  eink_dbuf_rdy(); */
    return 0;
}

int eink_edma_cfg(unsigned long wav_addr, struct eink_init_param *para)
{
    unsigned int tmp, w, h, hsync, vsync;

    EINK_WUINT32(wav_addr, ee_base + EDMA_WAV_ADDR);
    hsync = para->timing.lbl + para->timing.lsl + para->timing.lel;
    vsync = para->timing.fbl + para->timing.fsl + para->timing.fel;

    tmp = para->eink_mode ? (hsync << 3) : (hsync << 2);
    EINK_WUINT32(((para->timing.width + tmp) >> 1),
                    ee_base + EDMA_WAV_PITCH);
    w = para->timing.width + tmp;
    w = w ? (w - 1) : 0;
    h = para->timing.height + vsync;
    h = h ? (h-1) : 0;
    tmp = (h << 16) | w;
    EINK_WUINT32(tmp, ee_base + EDMA_WAV_SIZE);

    tmp = (para->timing.lbl + para->timing.lsl);
    tmp = para->eink_mode ? (tmp << 3) : (tmp << 2);
    tmp = ((para->timing.fbl + para->timing.fsl) << 16) | tmp;
    EINK_WUINT32(tmp, ee_base + EDMA_IMG_COOR);
    w = para->timing.width ? (para->timing.width - 1) : 0;
    h = para->timing.height ? (para->timing.height - 1) : 0;
    tmp = (h << 16) | w;
    EINK_WUINT32(tmp, ee_base + EDMA_IMG_SIZE);

    return 0;
}

int eink_edma_cfg_addr(unsigned long wav_addr)
{

    EINK_WUINT32(wav_addr, ee_base + EDMA_WAV_ADDR);
/*
*   tmp = 0x1<<31;
*   tmp |= (0x1<<16);
*   tmp |= 0x1;
*   EINK_WUINT32(tmp,ee_base + EDMA_GLB_CTL);
*/
    return 0;
}


int eink_edma_en(unsigned char en)
{
    unsigned int tmp;

    tmp = EINK_RUINT32(ee_base + EDMA_CTL);
    tmp |= en & 0x1;
    EINK_WUINT32(tmp, ee_base + EDMA_CTL);

    return 0;
}

int eink_dbuf_rdy(void)
{
    unsigned int tmp;

    tmp = 0x1 << 31;
    tmp |= (0x1 << 16);
    tmp |= 0x1;
    EINK_WUINT32(tmp, ee_base + EDMA_GLB_CTL);

    return 0;
}

/* wb_en: default :0, enablen write back for debug */
int  eink_set_wb(unsigned char wb_en, unsigned long wb_addr)
{
    unsigned int tmp;

    tmp = 0x1 << 31;
    tmp |= (0x1 << 16);
    tmp |= wb_en ? (0x3 << 8) : 0x0;
    tmp |= 0x1;
    EINK_WUINT32(tmp, ee_base + EDMA_GLB_CTL);
    EINK_WUINT32(wb_addr, ee_base + EDMA_WB_ADDR);

    return 0;
}


