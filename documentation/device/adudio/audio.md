@page page_device_audio Audio Device

# Audio Introduction

The Audio device is a crucial component in embedded systems, responsible for audio data sampling and output. An Audio device typically consists of a data bus interface, control bus interface, audio codec (Codec), speaker, and microphone, as shown below:

## API List

For more details, see @ref group_Audio

## Audio Device Features

The RT-Thread Audio device driver framework serves as the underlying layer of the Audio framework. It handles raw audio data acquisition/output, audio stream control, device management, volume adjustment, and hardware/Codec abstraction.

- **Interface**: Standard device interface (`open/close/read/control`).
- **Synchronous access mode**.
- **Supports playback and recording**.
- **Audio parameter management**.
- **Volume control**.

# Accessing Audio Devices

## Finding an Audio Device

Applications obtain a device handle using the Audio device name. The device lookup function is as follows:

```c
rt_device_t rt_device_find(const char* name);
```

| **Parameter** | **Description**                       |
|---------------|---------------------------------------|
| name          | Audio device name                     |
| **Return**    | ——                                   |
| Device handle | Returns the handle if found           |
| RT_NULL       | Device not found                      |

Example usage:
```c
#define SOUND_DEVICE_NAME    "sound0"    /* Audio device name */

static rt_device_t snd_dev;              /* Audio device handle */

/* Find Audio device by name and obtain handle */
snd_dev = rt_device_find(SOUND_DEVICE_NAME);
```

## Opening an Audio Device

Applications can open/close devices using the device handle. To open a device:

```c
rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflags);
```

| **Parameter** | **Description**                                                                 |
|---------------|---------------------------------------------------------------------------------|
| dev           | Device handle                                                                   |
| oflags        | Device mode flags                                                               |
| **Return**    | ——                                                                             |
| RT_EOK        | Device opened successfully                                                     |
| -RT_EBUSY     | Device cannot be reopened if registered with `RT_DEVICE_FLAG_STANDALONE`        |
| -RT_EINVAL    | Unsupported open flags                                                         |
| Other errors  | Device open failure                                                            |

Supported `oflags` values:
```c
#define RT_DEVICE_OFLAG_WRONLY      0x002     /* Write-only mode for playback devices */
#define RT_DEVICE_FLAG_RDONLY       0x001     /* Read-only mode for recording devices */
```

Audio devices are categorized into playback (output) and recording (input). Playback devices use the write-only flag, while recording devices use read-only.

Example for opening a playback device:
```c
rt_device_open(snd_dev, RT_DEVICE_OFLAG_WRONLY)
```

Example for opening a recording device:
```c
rt_device_open(mic_dev, RT_DEVICE_FLAG_RDONLY)
```

## Controlling an Audio Device

Applications configure Audio devices using control commands:

```c
rt_err_t rt_device_control(rt_device_t dev, rt_uint8_t cmd, void* arg);
```

| **Parameter** | **Description**                               |
|---------------|-----------------------------------------------|
| dev           | Device handle                                 |
| cmd           | Control command (see below)                   |
| arg           | Control parameter (see below)                 |
| **Return**    | ——                                           |
| RT_EOK        | Operation succeeded                           |
| -RT_ENOSYS    | Failed (null device handle)                   |
| Other errors  | Operation failed                              |

Supported control commands:
```c
/* AUDIO commands */
#define _AUDIO_CTL(a) (0x10 + a)

#define AUDIO_CTL_GETCAPS                   _AUDIO_CTL(1) /* Get device capabilities */
#define AUDIO_CTL_CONFIGURE                 _AUDIO_CTL(2) /* Configure device */
```

Device capability structure:
```c
struct rt_audio_caps
{
    int main_type;                            /* Main command type */
    int sub_type;                             /* Sub command type */

    union
    {
        rt_uint32_t mask;
        int     value;                       /* Parameter value */
        struct rt_audio_configure config;    /* Audio configuration */
    } udata;
};
```

### Setting Playback Parameters

Configure playback sample rate, channels, and bit depth:
```c
struct rt_audio_caps caps;

caps.main_type               = AUDIO_TYPE_OUTPUT; /* Playback device */
caps.sub_type                = AUDIO_DSP_PARAM;   /* Set all audio parameters */
caps.udata.config.samplerate = 44100;             /* Sample rate */
caps.udata.config.channels   = 2;                 /* Channels */
caps.udata.config.samplebits = 16;                /* Bit depth */
rt_device_control(device, AUDIO_CTL_CONFIGURE, &caps);
```

### Setting Playback Volume

Adjust master playback volume (0-100):
```c
struct rt_audio_caps caps;

caps.main_type   = AUDIO_TYPE_MIXER;       /* Volume control type */
caps.sub_type    = AUDIO_MIXER_VOLUME;     /* Set master volume */
caps.udata.value = volume;                 /* Range: 0-100 */
rt_device_control(snd_dev, AUDIO_CTL_CONFIGURE, &caps);
```

### Setting Recording Parameters

Configure recording sample rate, channels, and bit depth:
```c
struct rt_audio_caps caps;

caps.main_type               = AUDIO_TYPE_INPUT;  /* Recording device */
caps.sub_type                = AUDIO_DSP_PARAM;   /* Set all audio parameters */
caps.udata.config.samplerate = 44100;             /* Sample rate */
caps.udata.config.channels   = 2;                 /* Channels */
caps.udata.config.samplebits = 16;                /* Bit depth */
rt_device_control(device, AUDIO_CTL_CONFIGURE, &caps);
```

### Setting Recording Volume

Adjust microphone gain (0-100):
```c
struct rt_audio_caps caps;

caps.main_type = AUDIO_TYPE_MIXER;       /* Volume control type */
caps.sub_type  = AUDIO_MIXER_MIC;        /* Set microphone gain */
caps.udata.value = volume;               /* Range: 0-100 */
rt_device_control(player->device, AUDIO_CTL_CONFIGURE, &caps);
```

## Writing Audio Data

Write data to a playback device:
```c
rt_size_t rt_device_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);
```

| **Parameter** | **Description**                               |
|---------------|-----------------------------------------------|
| dev           | Device handle                                 |
| pos           | Unused (reserved for offset)                  |
| buffer        | Data buffer to write                          |
| size          | Data size to write                            |
| **Return**    | ——                                           |
| Bytes written | Actual bytes written (synchronous operation)  |

This synchronous function writes data to the device's internal buffer. The call blocks when the buffer is full.

## Reading Audio Data

Read data from a recording device:
```c
rt_size_t rt_device_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
```

| **Parameter** | **Description**                               |
|---------------|-----------------------------------------------|
| dev           | Device handle                                 |
| pos           | Unused (reserved for offset)                  |
| buffer        | Buffer to store read data                     |
| size          | Data size to read                             |
| **Return**    | ——                                           |
| Bytes read    | Actual bytes read (synchronous operation)     |
| 0             | Check thread's errno for error status         |

This synchronous function reads data from the device's internal pipe. The call blocks if insufficient data is available.

## Closing an Audio Device

Close the device after operations:
```c
rt_err_t rt_device_close(rt_device_t dev);
```

| **Parameter** | **Description**                       |
|---------------|---------------------------------------|
| dev           | Device handle                         |
| **Return**    | ——                                   |
| RT_EOK        | Device closed successfully           |
| -RT_ERROR     | Device already closed                 |
| Other errors  | Close failure                        |

# Audio Device Usage Example

Audio devices are used for playback and recording, often accompanied by audio file encoding and decoding. Below are examples of playing and recording WAV files. The complete code can be obtained from the [RT-Thread WAV Player Package](https://github.com/RT-Thread-packages/wavplayer).

## Playback

The main steps to play an audio file are as follows:

1. First, find the Audio device and obtain the device handle.
2. Open the Audio device in write-only mode.
3. Set audio parameters (sampling rate, channels, etc.).
4. Decode the audio file data.
5. Write the audio file data.
6. After playback is complete, close the device.

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <dfs_posix.h>

#define BUFSZ   1024
#define SOUND_DEVICE_NAME    "sound0"    /* Audio device name */
static rt_device_t snd_dev;              /* Audio device handle */

struct RIFF_HEADER_DEF
{
    char riff_id[4];     // 'R','I','F','F'
    uint32_t riff_size;
    char riff_format[4]; // 'W','A','V','E'
};

struct WAVE_FORMAT_DEF
{
    uint16_t FormatTag;
    uint16_t Channels;
    uint32_t SamplesPerSec;
    uint32_t AvgBytesPerSec;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
};

struct FMT_BLOCK_DEF
{
    char fmt_id[4];    // 'f','m','t',' '
    uint32_t fmt_size;
    struct WAVE_FORMAT_DEF wav_format;
};

struct DATA_BLOCK_DEF
{
    char data_id[4];     // 'R','I','F','F'
    uint32_t data_size;
};

struct wav_info
{
    struct RIFF_HEADER_DEF header;
    struct FMT_BLOCK_DEF   fmt_block;
    struct DATA_BLOCK_DEF  data_block;
};

int wavplay_sample(int argc, char **argv)
{
    int fd = -1;
    uint8_t *buffer = NULL;
    struct wav_info *info = NULL;
    struct rt_audio_caps caps = {0};

    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("wavplay_sample song.wav\n");
        return 0;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        rt_kprintf("open file failed!\n");
        goto __exit;
    }

    buffer = rt_malloc(BUFSZ);
    if (buffer == RT_NULL)
        goto __exit;

    info = (struct wav_info *) rt_malloc(sizeof * info);
    if (info == RT_NULL)
        goto __exit;

    if (read(fd, &(info->header), sizeof(struct RIFF_HEADER_DEF)) <= 0)
        goto __exit;
    if (read(fd, &(info->fmt_block),  sizeof(struct FMT_BLOCK_DEF)) <= 0)
        goto __exit;
    if (read(fd, &(info->data_block), sizeof(struct DATA_BLOCK_DEF)) <= 0)
        goto __exit;

    rt_kprintf("wav information:\n");
    rt_kprintf("samplerate %d\n", info->fmt_block.wav_format.SamplesPerSec);
    rt_kprintf("channel %d\n", info->fmt_block.wav_format.Channels);

    /* Find the Audio device by name and obtain the device handle */
    snd_dev = rt_device_find(SOUND_DEVICE_NAME);

    /* Open the Audio playback device in write-only mode */
    rt_device_open(snd_dev, RT_DEVICE_OFLAG_WRONLY);

    /* Set audio parameters such as sampling rate, channels, and bit depth */
    caps.main_type               = AUDIO_TYPE_OUTPUT;                           /* Output type (playback device) */
    caps.sub_type                = AUDIO_DSP_PARAM;                             /* Set all audio parameters */
    caps.udata.config.samplerate = info->fmt_block.wav_format.SamplesPerSec;    /* Sampling rate */
    caps.udata.config.channels   = info->fmt_block.wav_format.Channels;         /* Channels */
    caps.udata.config.samplebits = 16;                                          /* Bit depth */
    rt_device_control(snd_dev, AUDIO_CTL_CONFIGURE, &caps);

    while (1)
    {
        int length;

        /* Read audio data from the file system */
        length = read(fd, buffer, BUFSZ);

        if (length <= 0)
            break;

        /* Write audio data to the Audio device */
        rt_device_write(snd_dev, 0, buffer, length);
    }

    /* Close the Audio device */
    rt_device_close(snd_dev);

__exit:

    if (fd >= 0)
        close(fd);

    if (buffer)
        rt_free(buffer);

    if (info)
        rt_free(info);

    return 0;
}

MSH_CMD_EXPORT(wavplay_sample,  play wav file);
```

## Recording

The main steps to record an audio file are as follows:

1. First, find the Audio device and obtain the device handle.
2. Open the Audio device in read-only mode.
3. Set audio parameters (sampling rate, channels, etc.).
4. Read data from the Audio device.
5. Process the recorded data.
6. After recording is complete, close the device.

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <dfs_posix.h>

#define RECORD_TIME_MS      5000
#define RECORD_SAMPLERATE   16000
#define RECORD_CHANNEL      2
#define RECORD_CHUNK_SZ     ((RECORD_SAMPLERATE * RECORD_CHANNEL * 2) * 20 / 1000)

#define SOUND_DEVICE_NAME    "mic0"      /* Audio device name */
static rt_device_t mic_dev;              /* Audio device handle */

struct wav_header
{
    char  riff_id[4];              /* "RIFF" */
    int   riff_datasize;           /* RIFF chunk data size, excluding riff_id[4] and riff_datasize, total - 8 */
    char  riff_type[4];            /* "WAVE" */
    char  fmt_id[4];               /* "fmt " */
    int   fmt_datasize;            /* fmt chunk data size, 16 for PCM */
    short fmt_compression_code;    /* 1 for PCM */
    short fmt_channels;            /* 1(mono) or 2(stereo) */
    int   fmt_sample_rate;         /* samples per second */
    int   fmt_avg_bytes_per_sec;   /* sample_rate * channels * bit_per_sample / 8 */
    short fmt_block_align;         /* number of bytes per sample, bit_per_sample * channels / 8 */
    short fmt_bit_per_sample;      /* bits of each sample(8,16,32). */
    char  data_id[4];              /* "data" */
    int   data_datasize;           /* data chunk size, pcm_size - 44 */
};

static void wavheader_init(struct wav_header *header, int sample_rate, int channels, int datasize)
{
    memcpy(header->riff_id, "RIFF", 4);
    header->riff_datasize = datasize + 44 - 8;
    memcpy(header->riff_type, "WAVE", 4);
    memcpy(header->fmt_id, "fmt ", 4);
    header->fmt_datasize = 16;
    header->fmt_compression_code = 1;
    header->fmt_channels = channels;
    header->fmt_sample_rate = sample_rate;
    header->fmt_bit_per_sample = 16;
    header->fmt_avg_bytes_per_sec = header->fmt_sample_rate * header->fmt_channels * header->fmt_bit_per_sample / 8;
    header->fmt_block_align = header->fmt_bit_per_sample * header->fmt_channels / 8;
    memcpy(header->data_id, "data", 4);
    header->data_datasize = datasize;
}

int wavrecord_sample(int argc, char **argv)
{
    int fd = -1;
    uint8_t *buffer = NULL;
    struct wav_header header;
    struct rt_audio_caps caps = {0};
    int length, total_length = 0;

    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("wavrecord_sample file.wav\n");
        return -1;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        rt_kprintf("open file for recording failed!\n");
        return -1;
    }
    write(fd, &header, sizeof(struct wav_header));

    buffer = rt_malloc(RECORD_CHUNK_SZ);
    if (buffer == RT_NULL)
        goto __exit;

    /* Find the Audio device by name and obtain the device handle */
    mic_dev = rt_device_find(SOUND_DEVICE_NAME);
    if (mic_dev == RT_NULL)
        goto __exit;

    /* Open the Audio recording device in read-only mode */
    rt_device_open(mic_dev, RT_DEVICE_OFLAG_RDONLY);

    /* Set audio parameters such as sampling rate, channels, and bit depth */
    caps.main_type               = AUDIO_TYPE_INPUT;                            /* Input type (recording device) */
    caps.sub_type                = AUDIO_DSP_PARAM;                             /* Set all audio parameters */
    caps.udata.config.samplerate = RECORD_SAMPLERATE;                           /* Sampling rate */
    caps.udata.config.channels   = RECORD_CHANNEL;                              /* Channels */
    caps.udata.config.samplebits = 16;                                          /* Bit depth */
    rt_device_control(mic_dev, AUDIO_CTL_CONFIGURE, &caps);

    while (1)
    {
        /* Read 20ms of audio data from the Audio device */
        length = rt_device_read(mic_dev, 0, buffer, RECORD_CHUNK_SZ);

        if (length)
        {
            /* Write the audio data to the file system */
            write(fd, buffer, length);
            total_length += length;
        }

        if ((total_length / RECORD_CHUNK_SZ) >  (RECORD_TIME_MS / 20))
            break;
    }

    /* Rewrite the WAV file header */
    wavheader_init(&header, RECORD_SAMPLERATE, RECORD_CHANNEL, total_length);
    lseek(fd, 0, SEEK_SET);
    write(fd, &header, sizeof(struct wav_header));
    close(fd);

    /* Close the Audio device */
    rt_device_close(mic_dev);

__exit:
    if (fd >= 0)
        close(fd);

    if (buffer)
        rt_free(buffer);

    return 0;
}
MSH_CMD_EXPORT(wavrecord_sample, record voice to a wav file);
```

