#include <stdio.h>
#include <string.h>
#include <rtthread.h>
#include "avifile.h"

//#define DEBUGINFO

AVI_TypeDef AVI_file;

#define MAKE_FOURCC(a, b, c, d) ((uint32_t)(d)<<24 | (uint32_t)(c)<<16 | (uint32_t)(b)<<8 | (uint32_t)(a))
#define READ_WORD(a) ((uint32_t)*(a)<<24 | (uint32_t)*(a)<<16 | (uint32_t)*(a)<<8 | (uint32_t)*(a))

static uint32_t _REV(uint32_t value)
{
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 |
           (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}

static int search_fourcc(uint32_t fourcc, const uint8_t *buffer, uint32_t length)
{
    uint32_t i, j;
    uint32_t *pdata;
    j = length - 4;
    rt_kprintf("movi index:%d\n\n", j);
    for (i = 0; i < j; i++)
    {
        pdata = (uint32_t *)(buffer + i);
        if (fourcc == *pdata)
        {
            rt_kprintf("==>find movi:%#x,%d\n", pdata, i);
            return i;
        }
    }
    return -1;
}

static int Strl_Parser(const uint8_t *buffer, uint32_t length, uint32_t *list_length)
{
    /**
     * TODO: how to deal with the list is not complete in the buffer
     */
    const uint8_t *pdata = buffer;
    // strl(stream list), include "strh" and "strf"
    AVI_LIST_HEAD *strl = (AVI_LIST_HEAD *)pdata;
    if (strl->List != LIST_ID || strl->FourCC != strl_ID)
    {
        return -1;
    }
    pdata += sizeof(AVI_LIST_HEAD);
    *list_length = strl->size + 8; //return the entire size of list

    // strh
    AVI_STRH_CHUNK *strh = (AVI_STRH_CHUNK *)pdata;
    if (strh->FourCC != strh_ID || strh->size + 8 != sizeof(AVI_STRH_CHUNK))
    {
        return -5;
    }
#ifdef DEBUGINFO
    rt_kprintf("-----strh info------\r\n");
    rt_kprintf("fourcc_type:0x%x\r\n", strh->fourcc_type);
    rt_kprintf("fourcc_codec:0x%x\r\n", strh->fourcc_codec);
    rt_kprintf("flags:%d\r\n", strh->flags);
    rt_kprintf("Priority:%d\r\n", strh->priority);
    rt_kprintf("Language:%d\r\n", strh->language);
    rt_kprintf("InitFrames:%d\r\n", strh->init_frames);
    rt_kprintf("Scale:%d\r\n", strh->scale);
    rt_kprintf("Rate:%d\r\n", strh->rate);
    rt_kprintf("Start:%d\r\n", strh->start);
    rt_kprintf("Length:%d\r\n", strh->length);
    rt_kprintf("RefBufSize:%d\r\n", strh->suggest_buff_size);
    rt_kprintf("Quality:%d\r\n", strh->quality);
    rt_kprintf("SampleSize:%d\r\n", strh->sample_size);
    rt_kprintf("FrameLeft:%d\r\n", strh->rcFrame.left);
    rt_kprintf("FrameTop:%d\r\n", strh->rcFrame.top);
    rt_kprintf("FrameRight:%d\r\n", strh->rcFrame.right);
    rt_kprintf("FrameBottom:%d\r\n\n", strh->rcFrame.bottom);
#endif
    pdata += sizeof(AVI_STRH_CHUNK);

    if (vids_ID == strh->fourcc_type)
    {
        rt_kprintf("Find a video stream\n");
        if (mjpg_ID != strh->fourcc_codec)
        {
            rt_kprintf("only support mjpeg decoder, but needed is 0x%x\n", strh->fourcc_codec);
            return -1;
        }
        AVI_VIDS_STRF_CHUNK *strf = (AVI_VIDS_STRF_CHUNK *)pdata;
        if (strf->FourCC != strf_ID || strf->size + 8 != sizeof(AVI_VIDS_STRF_CHUNK))
        {
            return -5;
        }
#ifdef DEBUGINFO
        rt_kprintf("-----video strf info------\r\n");
        rt_kprintf("本结构体大小:%d\r\n", strf->size1);
        rt_kprintf("图像宽:%d\r\n", strf->width);
        rt_kprintf("图像高:%d\r\n", strf->height);
        rt_kprintf("平面数:%d\r\n", strf->planes);
        rt_kprintf("像素位数:%d\r\n", strf->bitcount);
        rt_kprintf("压缩类型:0x%x\r\n", strf->fourcc_compression);
        rt_kprintf("图像大小:%d\r\n", strf->image_size);
        rt_kprintf("水平分辨率:%d\r\n", strf->x_pixels_per_meter);
        rt_kprintf("垂直分辨率:%d\r\n", strf->y_pixels_per_meter);
        rt_kprintf("使用调色板颜色数:%d\r\n", strf->num_colors);
        rt_kprintf("重要颜色:%d\r\n\n", strf->imp_colors);
#endif
        AVI_file.vids_fps = strh->rate / strh->scale;
        AVI_file.vids_width = strf->width;
        AVI_file.vids_height = strf->height;
        pdata += sizeof(AVI_VIDS_STRF_CHUNK);

    }
    else if (auds_ID == strh->fourcc_type)
    {
        rt_kprintf("Find a audio stream\n");
        AVI_AUDS_STRF_CHUNK *strf = (AVI_AUDS_STRF_CHUNK *)pdata;
        if (strf->FourCC != strf_ID || (strf->size + 8 != sizeof(AVI_AUDS_STRF_CHUNK) && strf->size + 10 != sizeof(AVI_AUDS_STRF_CHUNK)))
        {
            rt_kprintf("FourCC=0x%x|%x, size=%d|%d\n", strf->FourCC, strf_ID, strf->size, sizeof(AVI_AUDS_STRF_CHUNK));
            return -5;
        }
#ifdef DEBUGINFO
        rt_kprintf("-----audio strf info------\r\n");
        rt_kprintf("strf数据块信息(音频流):");
        rt_kprintf("格式标志:%d\r\n", strf->format_tag);
        rt_kprintf("声道数:%d\r\n", strf->channels);
        rt_kprintf("采样率:%d\r\n", strf->samples_per_sec);
        rt_kprintf("波特率:%d\r\n", strf->avg_bytes_per_sec);
        rt_kprintf("块对齐:%d\r\n", strf->block_align);
        rt_kprintf("采样位宽:%d\r\n\n", (uint8_t)strf->bits_per_sample);
#endif
        AVI_file.auds_channels = strf->channels;
        AVI_file.auds_sample_rate = strf->samples_per_sec;
        AVI_file.auds_bits = strf->bits_per_sample;
        pdata += sizeof(AVI_AUDS_STRF_CHUNK);
    }
    else
    {
        rt_kprintf("Unsupport stream 0x%x\n", strh->fourcc_type);
    }
    return 0;
}

int AVI_Parser(const uint8_t *buffer, uint32_t length)
{
    const uint8_t *pdata = buffer;
    AVI_LIST_HEAD *riff = (AVI_LIST_HEAD *)pdata;
    if (riff->List != RIFF_ID || riff->FourCC != AVI_ID)
    {
        return -1;
    }
    AVI_file.RIFFchunksize = riff->size; //RIFF数据块长度
    pdata += sizeof(AVI_LIST_HEAD);

    AVI_LIST_HEAD *list = (AVI_LIST_HEAD *)pdata;
    if (list->List != LIST_ID || list->FourCC != hdrl_ID)
    {
        return -3;
    }
    AVI_file.LISTchunksize = list->size; //LIST数据块长度
    pdata += sizeof(AVI_LIST_HEAD);

    // avih chunk
    AVI_AVIH_CHUNK *avih = (AVI_AVIH_CHUNK *)pdata;
    if (avih->FourCC != avih_ID || avih->size + 8 != sizeof(AVI_AVIH_CHUNK))
    {
        return -5;
    }
    AVI_file.avihsize = avih->size; //avih数据块长度

    AVI_file.avi_hd.avih.us_per_frame = avih->us_per_frame;
    AVI_file.avi_hd.avih.max_bytes_per_sec = avih->max_bytes_per_sec;
    AVI_file.avi_hd.avih.total_frames = avih->total_frames;
    AVI_file.avi_hd.avih.init_frames = avih->init_frames;

#ifdef DEBUGINFO
    rt_kprintf("\r\n-----avih info------\r\n");
    rt_kprintf("显示一帧所需时间:%dus\r\n", avih->us_per_frame);
    rt_kprintf("最大数据传输率:%d\r\n", avih->max_bytes_per_sec);
    rt_kprintf("视频总帧数:%d\r\n", avih->total_frames);
    rt_kprintf("开始播放前需要帧数:%d\r\n", avih->init_frames);
    rt_kprintf("数据流个数:%d\r\n", avih->streams);
    rt_kprintf("缓冲区的大小:%d\r\n", avih->suggest_buff_size);
    rt_kprintf("主窗口宽度:%d\r\n", avih->width);
    rt_kprintf("主窗口高度:%d\r\n\n", avih->height);
#endif
    if ((avih->width > 800) || (avih->height > 480))
    {
        rt_kprintf("The size of video is too large\n");
        return -6;    //视频尺寸不支持
    }
    pdata += sizeof(AVI_AVIH_CHUNK);

    // process all streams in turn
    for (size_t i = 0; i < avih->streams; i++)
    {
        uint32_t strl_size = 0;
        int ret = Strl_Parser(pdata, length - (pdata - buffer), &strl_size);
        if (0 > ret)
        {
            rt_kprintf("strl of stream%d prase failed\n", i);
            break;
            /**
             * TODO: how to deal this error? maybe we should search for the next strl.
             */
        }
        pdata += strl_size;
    }

    rt_kprintf("MAKE_FOURCC:%d\n\n", MAKE_FOURCC('m', 'o', 'v', 'i'));
    int movi_offset = search_fourcc(MAKE_FOURCC('m', 'o', 'v', 'i'), pdata, length - (pdata - buffer));
    if (0 > movi_offset)
    {
        rt_kprintf("can't find \"movi\" list\n");
        return -7;
    }
    AVI_file.movi_start = movi_offset + 4  + pdata - buffer;
    pdata += movi_offset - 8; // back to the list head
    AVI_LIST_HEAD *movi = (AVI_LIST_HEAD *)pdata;
    if (movi->List != LIST_ID || movi->FourCC != movi_ID)
    {
        return -8;
    }
    AVI_file.movi_size = movi->size; //LIST数据块长度
    pdata += sizeof(AVI_LIST_HEAD);
    rt_kprintf("movi pos:%d, size:%d\n", AVI_file.movi_start, AVI_file.movi_size);

    return 0;
}
