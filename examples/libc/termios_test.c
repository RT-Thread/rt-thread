/*
 * termios_test.c
 *
 *  Created on: 2017-12-06
 *      Author: JasonJia
 */

#include <rtthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#if defined (RT_USING_POSIX)
    #include <dfs_posix.h>
    #include <dfs_select.h>
    #if defined (RT_USING_POSIX_TERMIOS)
        #include <termios.h>
    #else
        #error "TERMIOS need RT_USING_POSIX_TERMIOS"
    #endif
#else
    #error "POSIX poll/select need RT_USING_POSIX"
#endif

#define JOINT(x,y) x##y
#define B(x) JOINT(B,x)
#define Default_baud_rate   115200
#define Default_parity      'n'
#define BUFFER_SIZE         64

struct termios_test_s
{
    int baud_rate;
    const char *dev;
};

static struct termios_test_s term_param;

static int _check_baud_rate(int baud_rate)
{
    #define BAUD_RATE(x) \
    {\
        if(x==baud_rate) \
        {\
            rt_kprintf("%d baud rate\n",baud_rate);\
            return JOINT(B,x);\
        }\
    }
    BAUD_RATE(110);
    BAUD_RATE(200);
    BAUD_RATE(300);
    BAUD_RATE(600);
    BAUD_RATE(1200);
    BAUD_RATE(1800);
    BAUD_RATE(2400);
    BAUD_RATE(4800);
    BAUD_RATE(9600);
    BAUD_RATE(19200);
    BAUD_RATE(38400);
    BAUD_RATE(57600);
    BAUD_RATE(115200);
    BAUD_RATE(230400);
    BAUD_RATE(460800);
    BAUD_RATE(921600);

    rt_kprintf("%d is not support,use default %d value.\n",baud_rate,Default_baud_rate);
    return B(Default_baud_rate);
}

int open_comm(const char *name)
{
    int fd;
    fd = open(name, O_RDWR | O_NOCTTY | O_NONBLOCK, 0);
    if(fd == -1)
    {
        rt_kprintf("Open %s fail.\n",name);
        return -1;
    }
    else
    {
        rt_kprintf("Open %s success,fd:%d\n",name,fd);
    }

    return fd;
}

void close_comm(int fd)
{
    if(fd != -1)
    {
        close(fd);
    }
}

void config_comm(int fd, int speed_baud_rate, char parity, int data_bits, int stop_bits)
{
    int valid_baud_rate = 0;
    struct termios new_tc;

    memset(&new_tc, 0x00, sizeof(struct termios));

    valid_baud_rate = _check_baud_rate(speed_baud_rate);

    new_tc.c_cflag |= (CLOCAL | CREAD);//Enable in default.

    /*
    *Set baud rate. e.g B115200 is 115200 bauds.
    */
    cfsetispeed(&new_tc, valid_baud_rate);//input speed
    cfsetospeed(&new_tc, valid_baud_rate);//output speed

    /*
    *Set parity.
    */
    switch(parity)
    {
        case 'n':
        case 'N':
            new_tc.c_cflag &= ~PARENB;  //Disable parity.
            break;
        case 'o':
        case 'O':
            new_tc.c_cflag |= PARENB;   //Enable parity.
            new_tc.c_cflag |= PARODD;   //Odd parity.
            break;
        case 'e':
        case 'E':
            new_tc.c_cflag |= PARENB;   //Enable parity.
            new_tc.c_cflag &= ~PARODD;  //even parity.
            break;
    }

    /*
    *Set data bits.
    */
    new_tc.c_cflag &= ~CSIZE;
    switch(data_bits)
    {
        case 5:
            break;
        case 6:
            break;
        case 7:
            new_tc.c_cflag |= CS7;
            break;
        case 8:
            new_tc.c_cflag |= CS8;
            break;
    }

    /*
    *Set stop bits.
    */
    (stop_bits == 2)?(new_tc.c_cflag |= CSTOPB):(new_tc.c_cflag &= ~ CSTOPB);

    tcflush(fd,TCIFLUSH);
    //new_tc.c_cc[VTIME] = 0;
    //new_tc.c_cc[VMIN] = 1;

    if( tcsetattr(fd, TCSANOW, &new_tc) != 0)
    {
        rt_kprintf("Set port config fail!\n");
    }
}

int recv_comm(int fd, unsigned char *buffer, rt_size_t size, struct timeval *timeout)
{
    struct timeval t;
    int ret = 0;
    rt_size_t drv_recved = 0;
    int recved = 0, need = size;
    int timeout_cnt = 0;
    unsigned char *c = RT_NULL;
    fd_set readSet;

    RT_ASSERT(RT_NULL != buffer);

    if(fd == -1)
    {
        return -1;
    }

    t.tv_sec = 0;
    t.tv_usec = 100000;

    if(RT_NULL == timeout)
    {
        /* Wait forever approximate, it's a large time. */
        timeout_cnt = 0xffffffff;
    }
    else
    {
        timeout_cnt = (timeout->tv_sec * 1000 * 1000 + timeout->tv_usec)/(t.tv_sec * 1000 * 1000 + t.tv_usec);
    }

    while(1)
    {
        FD_ZERO(&readSet);
        FD_SET(fd, &readSet);

        ret = select(fd+1,&readSet,RT_NULL,RT_NULL,&t);
        if(ret < 0)
        {
            rt_kprintf("select error %d\n",ret);
            break;
        }
        else if(ret == 0)
        {
            /* timeout */
            timeout_cnt--;

            if(timeout_cnt == 0)
            {
                rt_kprintf("need %d data in timeout %d ms,but only %d recved.\n",
                            size,
                            timeout->tv_sec * 1000 + timeout->tv_usec / 1000,
                            recved);

                recved = 0;

                break;
            }
        }
        else
        {
            if(FD_ISSET(fd, &readSet))
            {
                c = &buffer[size - need];
                ioctl(fd, FIONREAD, &drv_recved);

                /* check poll and ioctl */
                RT_ASSERT(drv_recved != 0);

                drv_recved = (drv_recved > need ? need : drv_recved);
                recved = read(fd, c, drv_recved);
                if(recved != drv_recved)
                {
                    rt_kprintf("fatal error %s(%d).\n",__FUNCTION__,__LINE__);
                    RT_ASSERT(0);
                    recved = 0;
                    break;
                }

                need -= recved;

                if(need)
                {
                    continue;
                }
                else if (need == 0)
                {
                    recved = size;
                    break;
                }
                else
                {
                    rt_kprintf("fatal error %s(%d).\n",__FUNCTION__,__LINE__);
                    RT_ASSERT(0);
                }

            }
        }
    }

    return recved;
}

int send_comm(int fd, const unsigned char *buffer, rt_size_t size)
{
    RT_ASSERT(RT_NULL != buffer);

    if(fd == -1)
    {
        return -1;
    }

    //serial framework does not support poll out now
    write(fd, buffer, size);

    return 0;
}

int flush_comm(int fd)
{
    if(fd == -1)
    {
        return -1;
    }
    tcflush(fd,TCIFLUSH);
    return 0;
}

void termios_test_entry(void *p)
{
    int len = 0;
    int fd = -1;
    unsigned char *pBuf = RT_NULL;
    struct termios_test_s *pTerm = (struct termios_test_s *)p;

    if((fd = open_comm(pTerm->dev)) == -1)
    {
        rt_kprintf("Check the device name...\n");
        return;
    }

    pBuf = (unsigned char *)rt_malloc(BUFFER_SIZE);
    RT_ASSERT(pBuf != RT_NULL);

    memset(pBuf, 0x00, BUFFER_SIZE);

    config_comm(fd, pTerm->baud_rate, Default_parity, 8, 1);

    flush_comm(fd);

    rt_kprintf("Block recv 10 bytes.\n");
    /* Block recv 10 bytes */
    len = recv_comm(fd, pBuf, 10, RT_NULL);

    rt_kprintf("Recv:%s\n", pBuf);

    send_comm(fd, pBuf, len);
    rt_kprintf("Termios test exit.\n");

    close_comm(fd);

    rt_free(pBuf);
    pBuf = RT_NULL;
}

int termios_test(int argc, char **argv)
{
    rt_thread_t tid;

    if(argc < 2)
    {
        rt_kprintf("Please input device name...\n");
        return -1;
    }

    term_param.dev = argv[1];
    term_param.baud_rate = ((argc >= 3) ? atoi(argv[2]) : Default_baud_rate);

    tid = rt_thread_create("termtest",
        termios_test_entry, (void *)&term_param,
        512, RT_THREAD_PRIORITY_MAX/3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

#ifdef RT_USING_FINSH
    #include <finsh.h>
    #ifdef FINSH_USING_MSH
        MSH_CMD_EXPORT_ALIAS(termios_test, termtest, e.g: termtest /dev/uart4 115200);
    #endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */

