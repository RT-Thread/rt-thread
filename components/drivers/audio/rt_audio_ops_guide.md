# RT-Thread Audio 驱动适配指南 (I2S + DDMA)

## 1. rt_audio_ops 接口概述

`rt_audio_ops` 是音频设备底层操作接口，由驱动工程师实现，框架层调用。

```c
struct rt_audio_ops
{
    rt_err_t (*getcaps)(struct rt_audio_device *audio, struct rt_audio_caps *caps);
    rt_err_t (*configure)(struct rt_audio_device *audio, struct rt_audio_caps *caps);
    rt_err_t (*init)(struct rt_audio_device *audio);
    rt_err_t (*start)(struct rt_audio_device *audio, int stream);
    rt_err_t (*stop)(struct rt_audio_device *audio, int stream);
    rt_ssize_t (*transmit)(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size);
    void (*buffer_info)(struct rt_audio_device *audio, struct rt_audio_buf_info *info);
};
```

---

## 2. 各函数功能详解

### 2.1 init - 硬件初始化

**调用时机**: 设备注册时 `rt_device_register()` -> `_audio_dev_init()` 内部调用

**你的职责**:
- 初始化 I2S 控制器 (时钟、GPIO引脚、格式配置)
- 初始化 DDMA 通道
- 配置 I2S 为从模式或主模式
- 设置采样率、字长等默认参数
- **不分配 DMA 缓冲区** (由 `buffer_info` 负责)

**示例**:
```c
static rt_err_t i2s_ddma_init(struct rt_audio_device *audio)
{
    /* 初始化I2S控制器 */
    rk_i2s_init(audio);

    /* 初始化DDMA */
    rk_ddma_init();

    return RT_EOK;
}
```

---

### 2.2 getcaps - 查询设备能力

**调用时机**: 应用调用 `ioctl(fd, AUDIO_CTL_GETCAPS, &caps)`

**你的职责**: 根据 `caps->main_type` 和 `caps->sub_type` 返回对应能力

| main_type | sub_type | 返回内容 |
|-----------|----------|----------|
| AUDIO_TYPE_QUERY | 任意 | 返回支持的类型掩码 (OUTPUT/INPUT/MIXER) |
| AUDIO_TYPE_OUTPUT | AUDIO_DSP_SAMPLERATE | 返回支持的采样率掩码 |
| AUDIO_TYPE_OUTPUT | AUDIO_DSP_CHANNELS | 返回支持的通道数 (1=单声道, 2=立体声) |
| AUDIO_TYPE_OUTPUT | AUDIO_DSP_SAMPLEBITS | 返回支持的采样精度 (16/24/32bit) |
| AUDIO_TYPE_MIXER | AUDIO_MIXER_VOLUME | 返回音量范围 0~100 |

**示例**:
```c
static rt_err_t i2s_ddma_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_INPUT | AUDIO_TYPE_MIXER;
        break;
    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.mask = AUDIO_SAMP_RATE_48K | AUDIO_SAMP_RATE_44K | ...;
            break;
        case AUDIO_DSP_CHANNELS:
            caps->udata.value = 2;  /* 立体声 */
            break;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.value = 16; /* 16bit */
            break;
        }
        break;
    case AUDIO_TYPE_MIXER:
        caps->udata.mask = AUDIO_MIXER_VOLUME;
        break;
    }
    return RT_EOK;
}
```

---

### 2.3 configure - 配置音频参数

**调用时机**: 应用调用 `ioctl(fd, AUDIO_CTL_CONFIGURE, &caps)`

**你的职责**: 根据配置设置硬件参数

| main_type | sub_type | 含义 |
|-----------|----------|------|
| AUDIO_TYPE_OUTPUT | AUDIO_DSP_SAMPLERATE | 采样率 (48000, 44100等) |
| AUDIO_TYPE_OUTPUT | AUDIO_DSP_CHANNELS | 通道数 (1=单声道, 2=立体声) |
| AUDIO_TYPE_OUTPUT | AUDIO_DSP_SAMPLEBITS | 采样精度 (16, 24, 32) |
| AUDIO_TYPE_MIXER | AUDIO_MIXER_VOLUME | 音量 (0~100) |

**对于 I2S + DDMA，你需要**:
```c
static rt_err_t i2s_ddma_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    if (caps->main_type == AUDIO_TYPE_OUTPUT)
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_SAMPLERATE:
            i2s_set_sample_rate(caps->udata.value);
            break;
        case AUDIO_DSP_CHANNELS:
            i2s_set_channels(caps->udata.value);
            break;
        case AUDIO_DSP_SAMPLEBITS:
            i2s_set_sample_bits(caps->udata.value);
            break;
        }
    }
    else if (caps->main_type == AUDIO_TYPE_MIXER)
    {
        if (caps->sub_type == AUDIO_MIXER_VOLUME)
        {
            codec_set_volume(caps->udata.value); /* 音量控制通过CODEC实现 */
        }
    }
    return RT_EOK;
}
```

---

### 2.4 buffer_info - 获取DMA缓冲区信息

**调用时机**: `_audio_dev_init()` 结束时调用

**你的职责**: 填充 `rt_audio_buf_info` 结构

```c
struct rt_audio_buf_info
{
    rt_uint8_t *buffer;      /* DMA缓冲区地址 */
    rt_uint16_t block_size;  /* 每次传输的块大小(字节) */
    rt_uint16_t block_count;  /* 块数量 */
    rt_uint32_t total_size;   /* 总大小 = block_size * block_count */
};
```

**对于 I2S + DDMA**:
```c
static void i2s_ddma_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    /* 分配双缓冲 ping-pong 模式 */
    static rt_uint8_t dma_buffer[2][1024];

    info->buffer = dma_buffer;
    info->block_size = 1024;
    info->block_count = 2;
    info->total_size = 1024 * 2;
}
```

---

### 2.5 start - 启动音频流

**调用时机**: 开始播放/录音时调用

**参数**:
- `stream = AUDIO_STREAM_REPLAY` (0) -> 播放
- `stream = AUDIO_STREAM_RECORD` (1) -> 录音

**你的职责**:
- 启动 DDMA 通道
- 使能 I2S TX/RX
- 开始 DMA 传输

```c
static rt_err_t i2s_ddma_start(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_REPLAY)
    {
        /* 启动DDMA TX通道 */
        ddma_start_tx();

        /* 使能I2S发送 */
        i2s_enable_tx();
    }
    else
    {
        /* 启动DDMA RX通道 */
        ddma_start_rx();

        /* 使能I2S接收 */
        i2s_enable_rx();
    }
    return RT_EOK;
}
```

---

### 2.6 stop - 停止音频流

**调用时机**: 停止播放/录音时调用

**你的职责**:
- 停止 DDMA 通道
- 失能 I2S TX/RX

```c
static rt_err_t i2s_ddma_stop(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_REPLAY)
    {
        i2s_disable_tx();
        ddma_stop_tx();
    }
    else
    {
        i2s_disable_rx();
        ddma_stop_rx();
    }
    return RT_EOK;
}
```

---

### 2.7 transmit - 数据传输

**调用时机**: `_audio_send_replay_frame()` 内部调用，DDMA半满/半空中断回调调用 `rt_audio_tx_complete()` 触发

**重要**: 这是 DDMA 双缓冲模式下数据更新的关键函数

**你的职责**:
- 将 `writeBuf` 中的数据通过 DDMA 发送 (playback)
- 或从 DDMA 读取数据到 `readBuf` (record)
- 返回实际传输的字节数

**Ping-Pong 双缓冲工作流程**:

```c
static rt_ssize_t i2s_ddma_transmit(struct rt_audio_device *audio,
                                     const void *writeBuf,
                                     void *readBuf,
                                     rt_size_t size)
{
    if (writeBuf != RT_NULL)
    {
        /* Playback: 将writeBuf数据复制到当前DMA缓冲区并启动传输 */
        rt_memcpy(current_dma_buffer, writeBuf, size);
        ddma_start_transfer(current_dma_buffer, size);

        /* 切换到另一个缓冲区 */
        current_dma_buffer = (current_dma_buffer == ping_buffer) ? pong_buffer : ping_buffer;
    }

    if (readBuf != RT_NULL)
    {
        /* Record: 从DMA缓冲区读取数据 */
        rt_memcpy(readBuf, current_dma_buffer, size);
    }

    return size;
}
```

---

## 3. 数据流图

```
应用层
  |
  v
write() -> 数据入队 rt_data_queue_push()
  |
  v
Audio Framework (_audio_send_replay_frame)
  |
  v
transmit() [DDMA双缓冲] -> I2S TX FIFO
  |
  v
DAC/CODEC -> 扬声器

录音方向相反:
MIC -> ADC -> I2S RX FIFO -> DDMA双缓冲 -> read()
```

---

## 4. 完整 ops 结构示例

```c
static struct rt_audio_ops i2s_ddma_ops =
{
    .init        = i2s_ddma_init,
    .getcaps     = i2s_ddma_getcaps,
    .configure   = i2s_ddma_configure,
    .start       = i2s_ddma_start,
    .stop        = i2s_ddma_stop,
    .transmit    = i2s_ddma_transmit,
    .buffer_info = i2s_ddma_buffer_info,
};
```

---

## 5. 关键注意事项

1. **中断处理**: DDMA 半满/传输完成中断中调用 `rt_audio_tx_complete(audio)` 触发下次传输

2. **buffer_info 时机**: 在 `init` 之后调用，必须返回有效的 DMA 缓冲区地址

3. **transmit 的 ping-pong**: 典型实现使用双缓冲区交替，传输完成触发 `rt_audio_tx_complete()`

4. **音量控制**: 通过 CODEC_CMD_SET_VOLUME (ioctl) 发送到 CODEC 芯片

5. **start/stop 必须配对**: 确保资源正确释放

---

## 6. 注册设备示例

```c
struct rt_audio_device audio_dev;

audio_dev.ops = &i2s_ddma_ops;
rt_audio_register(&audio_dev, "audio0", RT_DEVICE_FLAG_WRONLY, RT_NULL);
```

注册后应用通过标准文件操作 (open/read/write/ioctl) 使用音频设备。