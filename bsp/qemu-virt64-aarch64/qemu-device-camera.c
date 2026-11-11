#if 0
rm -f /tmp/qemu-device-camera.sock
gcc $0 -o qemu-device-camera -lvfio-user && LD_LIBRARY_PATH=/usr/local/lib/ ./qemu-device-camera $1
rm -f /tmp/qemu-device-camera.sock qemu-device-camera
exit
#endif
/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-07     GuEe-GUI     the first version
 */

/*
 * Install libvfio-user
 *  1. Dependency library
 *      Debian:
 *          sudo apt install libjson-c-dev libcmocka-dev
 *      RedHat:
 *          sudo yum install json-c-devel libcmocka-devel
 *
 *  2. git clone https://github.com/nutanix/libvfio-user.git
 *  3. meson build
 *  4. ninja -C build
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <linux/videodev2.h>
#include <vfio-user/libvfio-user.h>

#ifndef MFD_CLOEXEC
#define MFD_CLOEXEC             0x0001U
#endif

#define DEBUG                   0
#define SOCKET_PATH             "/tmp/qemu-device-camera.sock"

#define BAR3_FRAME_COUNT_OFFSET 0x00
#define BAR3_FRAME_READY_OFFSET 0x04
#define BAR3_SIZE               0x1000

struct vfio_camera
{
    void *bar0_width;
    size_t bar0_width_size;
    void *bar1_height;
    size_t bar1_height_size;
    void *bar2_framebuffer;
    size_t bar2_framebuffer_size;
    int bar2_fd;  /* Shared memory fd for zero-copy */
    void *bar3_status;
    size_t bar3_status_size;
    uint32_t frame_count;
    uint32_t frame_ready;
    int fd;
    enum v4l2_buf_type type;
    struct v4l2_format fmt;
    struct video_buffer *buffers;
    int buffer_count;
    bool streaming;
};

struct video_buffer
{
    void *start;
    size_t length;
};

static volatile sig_atomic_t running = 1;

static void handle_signal(int sig)
{
    running = 0;
}

static void setup_signal(void)
{
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

/* Create shared memory file descriptor */
static int create_shmem_fd(size_t size)
{
    int fd;

    /* Try memfd_create first (Linux 3.17+) */
#ifdef __NR_memfd_create
    fd = syscall(__NR_memfd_create, "camera_fb", MFD_CLOEXEC);
    if (fd >= 0)
    {
        if (ftruncate(fd, size) == 0)
        {
            return fd;
        }
        close(fd);
    }
#endif

    /* Fallback: use shm_open */
    fd = shm_open("/camera_framebuffer", O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd >= 0)
    {
        /* Unlink but keep fd */
        shm_unlink("/camera_framebuffer");
        if (ftruncate(fd, size) == 0)
        {
            return fd;
        }
        close(fd);
    }

    return -1;
}

static inline uint64_t round_up_pow2_u64(uint64_t x)
{
    if (x <= 1)
    {
        return 1;
    }
    return 1ULL << (64 - __builtin_clzll(x - 1));
}

static inline unsigned char clamp(int v)
{
    if (v < 0)
    {
        return 0;
    }
    if (v > 255)
    {
        return 255;
    }
    return v;
}

static inline void yuyv_to_rgb_pair(unsigned char *src, unsigned char *dst)
{
    int y0 = src[0];
    int u  = src[1] - 128;
    int y1 = src[2];
    int v  = src[3] - 128;
    int r, g, b;

    /* pixel 0 */
    r = y0 + ((1436 * v) >> 10);
    g = y0 - ((352 * u + 731 * v) >> 10);
    b = y0 + ((1815 * u) >> 10);
    dst[0] = clamp(r);
    dst[1] = clamp(g);
    dst[2] = clamp(b);

    /* pixel 1 */
    r = y1 + ((1436 * v) >> 10);
    g = y1 - ((352 * u + 731 * v) >> 10);
    b = y1 + ((1815 * u) >> 10);
    dst[3] = clamp(r);
    dst[4] = clamp(g);
    dst[5] = clamp(b);
}

/* Try to capture one frame (non-blocking) */
static void try_capture_frame(struct vfio_camera *vc)
{
    struct v4l2_buffer buf;
    unsigned char *src, *dst;
    int pixels;

    if (!vc->streaming)
    {
        return;
    }

    memset(&buf, 0, sizeof(buf));
    buf.type = vc->type;
    buf.memory = V4L2_MEMORY_MMAP;

    /* Non-blocking dequeue */
    if (ioctl(vc->fd, VIDIOC_DQBUF, &buf) < 0)
    {
        if (errno == EAGAIN)
        {
            /* No frame ready */
            return;
        }
        perror("DQBUF");
        return;
    }

    /* Convert YUYV to RGB24 */
    if (buf.bytesused > 0)
    {
        src = vc->buffers[buf.index].start;
        dst = vc->bar2_framebuffer;
        pixels = vc->fmt.fmt.pix.width * vc->fmt.fmt.pix.height;

        for (int i = 0; i < pixels; i += 2)
        {
            yuyv_to_rgb_pair(src, dst);
            src += 4;
            dst += 6;
        }

        /* Update frame status */
        vc->frame_count++;
        vc->frame_ready = 1;
        memcpy((char *)vc->bar3_status + BAR3_FRAME_COUNT_OFFSET, &vc->frame_count, sizeof(uint32_t));
        memcpy((char *)vc->bar3_status + BAR3_FRAME_READY_OFFSET, &vc->frame_ready, sizeof(uint32_t));
    }

    /* Re-queue buffer */
    if (ioctl(vc->fd, VIDIOC_QBUF, &buf) < 0)
    {
        perror("QBUF");
    }
}

static void get_max_resolution(int fd, uint32_t pixfmt, int *max_w, int *max_h)
{
    struct v4l2_frmsizeenum fsize;

    memset(&fsize, 0, sizeof(fsize));

    for (int i = 0; ; ++i)
    {
        fsize.index = i;
        fsize.pixel_format = pixfmt;

        if (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &fsize) < 0)
        {
            break;
        }

        if (fsize.type == V4L2_FRMSIZE_TYPE_DISCRETE)
        {
            if (fsize.discrete.width * fsize.discrete.height > (*max_w) * (*max_h))
            {
                *max_w = fsize.discrete.width;
                *max_h = fsize.discrete.height;
            }
        }
        else if (fsize.type == V4L2_FRMSIZE_TYPE_STEPWISE ||
                 fsize.type == V4L2_FRMSIZE_TYPE_CONTINUOUS)
        {
            *max_w = fsize.stepwise.max_width;
            *max_h = fsize.stepwise.max_height;
            break;
        }
    }
}

static void vfio_log_cb(vfu_ctx_t *vfu_ctx, int level, const char *msg)
{
    fprintf(stderr, "[VFIO] %s", msg);
}

static ssize_t bar0_width_access(vfu_ctx_t *vfu_ctx, char *buf, size_t count,
                                  loff_t offset, bool is_write)
{
    struct vfio_camera *vc = vfu_get_private(vfu_ctx);

#if DEBUG
    fprintf(stderr, "BAR0 access: offset=0x%lx, count=%zu, is_write=%d\n",
            (unsigned long)offset, count, is_write);
#endif

    if (offset + count > vc->bar0_width_size)
    {
        errno = EINVAL;
        return -1;
    }

    if (!is_write)
    {
        memcpy(buf, (char *)vc->bar0_width + offset, count);
    }

    return (ssize_t)count;
}

static ssize_t bar1_height_access(vfu_ctx_t *vfu_ctx, char *buf, size_t count,
                                    loff_t offset, bool is_write)
{
    struct vfio_camera *vc = vfu_get_private(vfu_ctx);

#if DEBUG
    fprintf(stderr, "BAR1 access: offset=0x%lx, count=%zu, is_write=%d\n",
            (unsigned long)offset, count, is_write);
#endif

    if (offset + count > vc->bar1_height_size)
    {
        errno = EINVAL;
        return -1;
    }

    if (!is_write)
    {
        memcpy(buf, (char *)vc->bar1_height + offset, count);
    }

    return (ssize_t)count;
}

static ssize_t bar2_framebuffer_access(vfu_ctx_t *vfu_ctx, char *buf, size_t count,
                                        loff_t offset, bool is_write)
{
    struct vfio_camera *vc = vfu_get_private(vfu_ctx);

#if DEBUG
    fprintf(stderr, "BAR2 access: offset=0x%lx, count=%zu, is_write=%d\n",
            (unsigned long)offset, count, is_write);
#endif

    /* Try to capture a frame when framebuffer is accessed */
    try_capture_frame(vc);

    if (offset + count > vc->bar2_framebuffer_size)
    {
        errno = EINVAL;
        return -1;
    }

    if (!is_write)
    {
        memcpy(buf, (char *)vc->bar2_framebuffer + offset, count);
    }

    return (ssize_t)count;
}

static ssize_t bar3_status_access(vfu_ctx_t *vfu_ctx, char *buf, size_t count,
                                   loff_t offset, bool is_write)
{
    struct vfio_camera *vc = vfu_get_private(vfu_ctx);

#if DEBUG
    fprintf(stderr, "BAR3 access: offset=0x%lx, count=%zu, is_write=%d\n",
            (unsigned long)offset, count, is_write);
#endif

    /* Try to capture frame when status is read */
    if (!is_write)
    {
        try_capture_frame(vc);
    }

    if (offset + count > vc->bar3_status_size)
    {
        errno = EINVAL;
        return -1;
    }

    if (!is_write)
    {
        memcpy(buf, (char *)vc->bar3_status + offset, count);
    }
    else
    {
        /* Allow RT-Thread to clear frame_ready flag */
        memcpy((char *)vc->bar3_status + offset, buf, count);
        if (offset <= BAR3_FRAME_READY_OFFSET && offset + count >= BAR3_FRAME_READY_OFFSET + sizeof(uint32_t))
        {
            memcpy(&vc->frame_ready, (char *)vc->bar3_status + BAR3_FRAME_READY_OFFSET, sizeof(uint32_t));
        }
    }

    return (ssize_t)count;
}

static int device_reset(vfu_ctx_t *vfu_ctx, vfu_reset_type_t type)
{
    vfu_log(vfu_ctx, LOG_DEBUG, "Device reset");
    return 0;
}

static void cleanup_buffers(struct video_buffer *buffers, int count)
{
    if (!buffers) return;

    for (int i = 0; i < count; ++i)
    {
        if (buffers[i].start && buffers[i].start != MAP_FAILED)
        {
            munmap(buffers[i].start, buffers[i].length);
        }
    }
    free(buffers);
}

int main(int argc, char *argv[])
{
    int fd, ret;
    vfu_ctx_t *vfu_ctx;
    struct vfio_camera vc;
    struct v4l2_buffer buf;
    struct v4l2_requestbuffers req;
    size_t expected_frame_size;

    memset(&vc, 0, sizeof(vc));
    vc.bar2_fd = -1;

    /* Open camera device */
    fd = open(argc > 1 ? argv[1] : "/dev/video0", O_RDWR | O_NONBLOCK);
    if (fd < 0)
    {
        perror("open camera");
        return -1;
    }
    vc.fd = fd;

    /* Set format */
    memset(&vc.fmt, 0, sizeof(vc.fmt));
    vc.fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vc.fmt.fmt.pix.width = 640;
    vc.fmt.fmt.pix.height = 480;
    vc.fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    vc.fmt.fmt.pix.field = V4L2_FIELD_ANY;

    get_max_resolution(fd, vc.fmt.fmt.pix.pixelformat,
                       &vc.fmt.fmt.pix.width, &vc.fmt.fmt.pix.height);

    if (ioctl(fd, VIDIOC_S_FMT, &vc.fmt) < 0)
    {
        perror("VIDIOC_S_FMT");
        goto _err_close;
    }

    /* Request buffers */
    memset(&req, 0, sizeof(req));
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (ioctl(fd, VIDIOC_REQBUFS, &req) < 0)
    {
        perror("REQBUFS");
        goto _err_close;
    }

    vc.buffers = calloc(req.count, sizeof(*vc.buffers));
    if (!vc.buffers)
    {
        perror("calloc buffers");
        goto _err_close;
    }
    vc.buffer_count = req.count;

    /* Map buffers */
    for (int i = 0; i < req.count; ++i)
    {
        memset(&buf, 0, sizeof(buf));
        buf.type = req.type;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) < 0)
        {
            perror("QUERYBUF");
            goto _err_cleanup;
        }

        vc.buffers[i].length = buf.length;
        vc.buffers[i].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                                   MAP_SHARED, fd, buf.m.offset);
        if (vc.buffers[i].start == MAP_FAILED)
        {
            perror("mmap");
            goto _err_cleanup;
        }
    }

    /* Queue buffers */
    for (int i = 0; i < req.count; ++i)
    {
        memset(&buf, 0, sizeof(buf));
        buf.type = req.type;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
        {
            perror("QBUF");
            goto _err_streamoff;
        }
    }

    /* Start streaming */
    vc.type = req.type;
    if (ioctl(fd, VIDIOC_STREAMON, &vc.type) < 0)
    {
        perror("STREAMON");
        goto _err_streamoff;
    }
    vc.streaming = true;

    /* Setup BARs */
    expected_frame_size = vc.fmt.fmt.pix.width * vc.fmt.fmt.pix.height * 3;

    vc.bar0_width_size = 0x1000;
    vc.bar0_width = mmap(NULL, vc.bar0_width_size, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (vc.bar0_width == MAP_FAILED)
    {
        perror("mmap bar0");
        goto _err_streamoff;
    }
    memcpy(vc.bar0_width, &vc.fmt.fmt.pix.width, sizeof(uint32_t));

    vc.bar1_height_size = 0x1000;
    vc.bar1_height = mmap(NULL, vc.bar1_height_size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (vc.bar1_height == MAP_FAILED)
    {
        perror("mmap bar1");
        goto _err_unmap_bar0;
    }
    memcpy(vc.bar1_height, &vc.fmt.fmt.pix.height, sizeof(uint32_t));

    /* Allocate framebuffer with shared memory for zero-copy */
    vc.bar2_framebuffer_size = round_up_pow2_u64(expected_frame_size);
    vc.bar2_fd = create_shmem_fd(vc.bar2_framebuffer_size);
    if (vc.bar2_fd < 0)
    {
        perror("create_shmem_fd");
        goto _err_unmap_bar1;
    }

    vc.bar2_framebuffer = mmap(NULL, vc.bar2_framebuffer_size, PROT_READ | PROT_WRITE,
                               MAP_SHARED, vc.bar2_fd, 0);
    if (vc.bar2_framebuffer == MAP_FAILED)
    {
        perror("mmap bar2");
        close(vc.bar2_fd);
        goto _err_unmap_bar1;
    }
    memset(vc.bar2_framebuffer, 0, vc.bar2_framebuffer_size);

    vc.bar3_status_size = BAR3_SIZE;
    vc.bar3_status = mmap(NULL, vc.bar3_status_size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (vc.bar3_status == MAP_FAILED)
    {
        perror("mmap bar3");
        goto _err_unmap_bar2;
    }
    vc.frame_count = 0;
    vc.frame_ready = 0;
    memcpy((char *)vc.bar3_status + BAR3_FRAME_COUNT_OFFSET, &vc.frame_count, sizeof(uint32_t));
    memcpy((char *)vc.bar3_status + BAR3_FRAME_READY_OFFSET, &vc.frame_ready, sizeof(uint32_t));

    /* Create VFIO context */
    vfu_ctx = vfu_create_ctx(VFU_TRANS_SOCK, SOCKET_PATH, 0, &vc, VFU_DEV_TYPE_PCI);
    if (!vfu_ctx)
    {
        perror("vfu_create_ctx");
        goto _err_unmap_bar3;
    }

    ret = vfu_setup_log(vfu_ctx, vfio_log_cb, DEBUG ? LOG_DEBUG : LOG_ERR);
    if (ret < 0)
    {
        perror("vfu_setup_log");
        goto _err_destroy_ctx;
    }

    ret = vfu_pci_init(vfu_ctx, VFU_PCI_TYPE_CONVENTIONAL, PCI_HEADER_TYPE_NORMAL, 0);
    if (ret < 0)
    {
        perror("vfu_pci_init");
        goto _err_destroy_ctx;
    }

    vfu_pci_set_id(vfu_ctx, 0x1234, 0x5678, 0x0000, 0x0000);
    vfu_pci_set_class(vfu_ctx, 0xff, 0x00, 0x00);

    /* Setup BAR regions */
    ret = vfu_setup_region(vfu_ctx, VFU_PCI_DEV_BAR0_REGION_IDX, vc.bar0_width_size,
                           bar0_width_access, VFU_REGION_FLAG_READ | VFU_REGION_FLAG_MEM,
                           NULL, 0, -1, 0);
    if (ret < 0)
    {
        perror("vfu_setup_region BAR0");
        goto _err_destroy_ctx;
    }

    ret = vfu_setup_region(vfu_ctx, VFU_PCI_DEV_BAR1_REGION_IDX, vc.bar1_height_size,
                           bar1_height_access, VFU_REGION_FLAG_READ | VFU_REGION_FLAG_MEM,
                           NULL, 0, -1, 0);
    if (ret < 0)
    {
        perror("vfu_setup_region BAR1");
        goto _err_destroy_ctx;
    }

    /* BAR2: Framebuffer region with zero-copy mmap */
    struct iovec bar2_mmap_areas[1] =
    {
        { .iov_base = 0, .iov_len = expected_frame_size }
    };

    ret = vfu_setup_region(vfu_ctx, VFU_PCI_DEV_BAR2_REGION_IDX, vc.bar2_framebuffer_size,
                           bar2_framebuffer_access,  /* Fallback callback for non-mmap access */
                           VFU_REGION_FLAG_READ | VFU_REGION_FLAG_MEM,
                           bar2_mmap_areas, 1, vc.bar2_fd, 0);
    if (ret < 0)
    {
        perror("vfu_setup_region BAR2");
        goto _err_destroy_ctx;
    }

    ret = vfu_setup_region(vfu_ctx, VFU_PCI_DEV_BAR3_REGION_IDX, vc.bar3_status_size,
                           bar3_status_access, VFU_REGION_FLAG_READ | VFU_REGION_FLAG_MEM,
                           NULL, 0, -1, 0);
    if (ret < 0)
    {
        perror("vfu_setup_region BAR3");
        goto _err_destroy_ctx;
    }

    ret = vfu_setup_device_reset_cb(vfu_ctx, device_reset);
    if (ret < 0)
    {
        perror("vfu_setup_device_reset_cb");
        goto _err_destroy_ctx;
    }

    ret = vfu_setup_device_nr_irqs(vfu_ctx, VFU_DEV_INTX_IRQ, 1);
    if (ret < 0)
    {
        perror("vfu_setup_device_nr_irqs");
        goto _err_destroy_ctx;
    }

    ret = vfu_realize_ctx(vfu_ctx);
    if (ret < 0)
    {
        perror("vfu_realize_ctx");
        goto _err_destroy_ctx;
    }

    ret = vfu_attach_ctx(vfu_ctx);
    if (ret < 0)
    {
        perror("vfu_attach_ctx");
        goto _err_destroy_ctx;
    }

    setup_signal();

    /* Main loop */
    while (running)
    {
        ret = vfu_run_ctx(vfu_ctx);
        if (ret < 0)
        {
            if (errno == ENOTCONN)
            {
            #if DEBUG
                fprintf(stderr, "QEMU disconnected\n");
            #endif

                ret = vfu_attach_ctx(vfu_ctx);
                if (ret < 0)
                {
                #if DEBUG
                    fprintf(stderr, "Failed to re-attach: %s\n", strerror(errno));
                #endif
                    break;
                }
            #if DEBUG
                fprintf(stderr, "Re-attached to QEMU\n");
            #endif
                continue;
            }
            perror("vfu_run_ctx");
            break;
        }
    }

_err_destroy_ctx:
    vfu_destroy_ctx(vfu_ctx);
_err_unmap_bar3:
    munmap(vc.bar3_status, vc.bar3_status_size);
_err_unmap_bar2:
    if (vc.bar2_fd >= 0)
    {
        close(vc.bar2_fd);
    }
    munmap(vc.bar2_framebuffer, vc.bar2_framebuffer_size);
_err_unmap_bar1:
    munmap(vc.bar1_height, vc.bar1_height_size);
_err_unmap_bar0:
    munmap(vc.bar0_width, vc.bar0_width_size);
_err_streamoff:
    ioctl(fd, VIDIOC_STREAMOFF, &vc.type);
_err_cleanup:
    cleanup_buffers(vc.buffers, vc.buffer_count);
_err_close:
    close(fd);

    return 0;
}
