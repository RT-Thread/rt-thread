#include <rtthread.h>
#include <rtdevice.h>

#include <virtio_input.h>
#include <poll.h>

#define DBG_TAG "mouse"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct virtio_input_event_un
{
    struct timeval time;
#define virtio_input_event_sec  time.tv_sec;
#define virtio_input_event_usec time.tv_usec;
    rt_uint16_t type;
    rt_uint16_t code;
    rt_uint32_t value;
};

struct hidevent
{
    rt_list_t list;
    struct virtio_input_event_un ev;
};

struct mousedev
{
    struct rt_device dev;

    struct rt_mutex lock;
    struct rt_spinlock list_lock;
    rt_list_t idle;
    rt_list_t ready;
};

static struct mousedev _mdev;
static rt_device_t tablet_dev = RT_NULL;

static struct hidevent _evpool[512];
static rt_uint32_t cur_min[2];
static rt_uint32_t cur_max[2];
static rt_uint32_t cur_range[2];
static rt_uint32_t cur_points[2];
static rt_int32_t cur_last_points[2] = {100,100};
static void event_report(struct mousedev *mdev, uint16_t type, uint16_t code, int val)
{
    struct hidevent *ev = 0;

    rt_spin_lock(&mdev->list_lock);
    if (!rt_list_isempty(&mdev->idle))
    {
        ev = rt_list_first_entry(&mdev->idle, struct hidevent, list);
        rt_list_remove(&ev->list);
    }
    rt_spin_unlock(&mdev->list_lock);

    if (ev)
    {
        struct timespec ts = { 0, 0 };

	    clock_gettime(CLOCK_MONOTONIC, &ts);

        ev->ev.time.tv_usec = ts.tv_nsec / 1000;
        ev->ev.time.tv_sec = ts.tv_sec;
        ev->ev.type = type;
        ev->ev.code = code;
        ev->ev.value = val;

        rt_spin_lock(&mdev->list_lock);
        rt_list_insert_before(&mdev->ready, &ev->list);

        rt_spin_unlock(&mdev->list_lock);

        rt_wqueue_wakeup(&mdev->dev.wait_queue, (void *)POLLIN);
    }
}
#define input_report_key(a, b, c) event_report(a, EV_KEY, b, !!(c))
#define input_report_rel(a, b, c) event_report(a, EV_REL, b, c)


void event_handler(struct virtio_input_event event)
{

    if (event.type == EV_ABS)
    {
        if (event.code == REL_X)
        {
            cur_points[0] = (cur_max[0] * (event.value - cur_min[0]) + cur_range[0] / 2) / cur_range[0];
            cur_last_points[0] = cur_points[0]-cur_last_points[0];
            input_report_rel(&_mdev,event.code, cur_last_points[0]);
            cur_last_points[0] =  cur_points[0];
        }
        else if (event.code == REL_Y)
        {
            cur_points[1] = (cur_max[1] * (event.value - cur_min[1]) + cur_range[1] / 2) / cur_range[1];
            cur_last_points[1] = cur_points[1]-cur_last_points[1];
            input_report_rel(&_mdev,event.code, cur_last_points[1]);
            cur_last_points[1] =  cur_points[1];
        } 
    }
    if(event.type == EV_KEY)
    {
        input_report_key(&_mdev, event.code, event.value);
    }
    if (event.type == EV_SYN)
    {   
        event_report(&_mdev, EV_SYN, 0, 0);
    }
    

}

#include <dfs_fs.h>
#include <dfs_file.h>

static inline struct mousedev *mdev_from_file(struct dfs_file *file)
{
    return (struct mousedev *)file->vnode->data;
}

static int mdev_open(struct dfs_file *file)
{
    return 0;
}

static int mdev_close(struct dfs_file *file)
{


    return 0;
}

static ssize_t mdev_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    struct mousedev *mdev = mdev_from_file(file);
    int ret = 0;
    struct hidevent *ev = RT_NULL;

    if ((count < sizeof(struct virtio_input_event_un)) || !buf)
        return -EINVAL;

    while (ret < count)
    {
        rt_spin_lock(&mdev->list_lock);
        if (!rt_list_isempty(&mdev->ready))
        {
            ev = rt_list_first_entry(&mdev->ready, struct hidevent, list);
            rt_list_remove(&ev->list);
        }
        rt_spin_unlock(&mdev->list_lock);

        if (ev)
        {
            rt_memcpy(&((char *)buf)[ret], &ev->ev, sizeof(struct virtio_input_event_un));

            rt_spin_lock(&mdev->list_lock);
            rt_list_insert_before(&mdev->idle, &ev->list);

            rt_spin_unlock(&mdev->list_lock);

            ret += sizeof(struct virtio_input_event_un);
            ev = RT_NULL;
        }
        else
        {
            break;
        }
    }

    return ret;
}

static int mdev_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int mask = 0;
    struct mousedev *mdev = mdev_from_file(file);

    rt_poll_add(&mdev->dev.wait_queue, req);

    rt_spin_lock(&mdev->list_lock);
    if (!rt_list_isempty(&mdev->ready))
    {
        mask |= POLLIN;
    }
    rt_spin_unlock(&mdev->list_lock);

    return mask;
}

static int mdev_ioctl(struct dfs_file *file, int cmd, void *arg)
{

    return 0;
}

static const struct dfs_file_ops _fops = {
    .open = mdev_open,
    .close = mdev_close,
    .read = mdev_read,
    .poll = mdev_poll,
    .ioctl = mdev_ioctl,
};

static int mdev_init(void)
{   
    char dev_name[RT_NAME_MAX];
    rt_device_t device = RT_NULL;
    struct virtio_input_config tablet_config;

    rt_memset(&_mdev, 0, sizeof(_mdev));
    rt_spin_lock_init(&_mdev.list_lock);
    rt_list_init(&_mdev.idle);
    rt_list_init(&_mdev.ready);
    rt_mutex_init(&_mdev.lock, "mouse", 0);

    for (int i = 0; i < 3; ++i)
    {
        rt_snprintf(dev_name, RT_NAME_MAX, "virtio-input%d", i);
        device = rt_device_find(dev_name);
        if(device->open_flag) {
            rt_kprintf("%s has  opened  !! \n",dev_name);
            return -RT_ENOMEM;
        }
        device->user_data = &_mdev;
        if (device != RT_NULL && rt_device_open(device, 0) == RT_EOK) {
            rt_kprintf("%s open success !! \n",dev_name);
             enum virtio_input_type type;
            rt_device_control(device, VIRTIO_DEVICE_CTRL_INPUT_GET_TYPE, &type);
            if (type == VIRTIO_INPUT_TYPE_TABLET) {
                tablet_dev = device;
            }
            else {
                rt_device_close(device);
            }
        }
        else {
            return -RT_ENOMEM;
        }
    }

    cur_max[0] = 800;
    cur_max[1] = 600;

    rt_device_control(tablet_dev, VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_X_INFO, &tablet_config);

    cur_min[0] = tablet_config.abs.min;
    cur_range[0] = tablet_config.abs.max - cur_min[0];

    rt_device_control(tablet_dev, VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_Y_INFO, &tablet_config);

    cur_min[1] = tablet_config.abs.min;
    cur_range[1] = tablet_config.abs.max - cur_min[1];

    rt_device_control(tablet_dev, VIRTIO_DEVICE_CTRL_INPUT_BIND_BSCT_HANDLER, event_handler);

    for (int i = 0; i < sizeof(_evpool) / sizeof(_evpool[0]); i++)
    {
        rt_list_init(&_evpool[i].list);
        rt_list_insert_before(&_mdev.idle, &_evpool[i].list);
    }

    rt_device_register(&_mdev.dev, "mouse0", 0);
    _mdev.dev.fops = &_fops;

    return 0;
}
INIT_ENV_EXPORT(mdev_init);


#include <stdlib.h>
static int mmv(int argc, char **argv)
{
    struct mousedev *dev = &_mdev;
    int data[2] = {0};

    if (argc != 3)
    {
        rt_kprintf("mmv X Y");
        return -1;
    }

    data[0] = atoi(argv[1]);
    data[1] = atoi(argv[2]);

    input_report_rel(dev, REL_X, data[0]);
    input_report_rel(dev, REL_Y, data[1]);
    event_report(dev, EV_SYN, 0, 0);

    return 0;
}
MSH_CMD_EXPORT(mmv, mouse move);


static int lbc(int argc, char **argv)
{
    struct mousedev *dev = &_mdev;

    input_report_key(dev, BTN_LEFT, 1);
    event_report(dev, EV_SYN, 0, 0);
    input_report_key(dev, BTN_LEFT, 0);
    event_report(dev, EV_SYN, 0, 0);

    return 0;
}
MSH_CMD_EXPORT(lbc, left button click);

