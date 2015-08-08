
#define OS_RTTHREAD     1

#if (OS_RTTHREAD == 0)
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

#define DEBUG printf
#define SLEEP(x) sleep(x)
#else
#include <rtthread.h>
#include <lwip/netdb.h> 
#include <lwip/sockets.h>
#include <arch/sys_arch.h>
#include <lwip/sys.h>

#define DEBUG rt_kprintf
#define SLEEP(x) rt_thread_delay((x)*RT_TICK_PER_SECOND)
#endif

#include <string.h>
#include "MQTTPacket.h"

#define HOSTNAME     "m2m.eclipse.org"
#define HOSTPORT     1883
#define USERNAME     "testuser"
#define PASSWORD     "testpassword"
#define TOPIC        "test"

#define KEEPALIVE_INTERVAL    20

typedef struct
{
    int qos;
    unsigned char retained;
    unsigned char dup;
    unsigned short id;
    int payloadlen;
    unsigned char *payload;
}mqtt_msg_t;

typedef struct
{
    int sockfd;
    unsigned char *wbuf; //
    int wbuflen;
    unsigned char *rbuf;
    int rbuflen;
    int (*getfn)(unsigned char*, int);
}mqtt_client_t;

static mqtt_client_t _cpub;
static mqtt_client_t _csub;

static void *mqtt_ping_thread(void *param)
{
    int *sockfd = (int*)param;
    unsigned char buf[2];
    int len;

    DEBUG("ping start\n");

    while (*sockfd >= 0)
    {
        SLEEP(KEEPALIVE_INTERVAL-1);
        len = MQTTSerialize_pingreq(buf, sizeof(buf));

        send(*sockfd, buf, len, 0);
    }

    DEBUG("ping exit\n");

    return 0;
}

void mqtt_ping_start(int *sockfd)
{
    #if (OS_RTTHREAD == 0)
    pthread_t tid;

    pthread_create(&tid, NULL, mqtt_ping_thread, (void*)sockfd);
    #else
    sys_thread_new("ping",
                   mqtt_ping_thread,
                   (void*)sockfd,
                   512,
                   20); 
    #endif
}

static int sub_read(unsigned char *buf,  int len)
{
    int bytes = 0;
    struct timeval interval;
    int rc;

    interval.tv_sec = 3;
    interval.tv_usec = 0;

    rc = setsockopt(_csub.sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&interval, sizeof(struct timeval));

    while (bytes < len)
    {
        rc = recv(_csub.sockfd, &buf[bytes], (size_t)(len - bytes), 0);

        if (rc == -1)
        {
            if (errno != ENOTCONN && errno != ECONNRESET)
            {
                bytes = -1;
                break;
            }
        }
        else
            bytes += rc;
    }

    return bytes;
}

static int pub_read(unsigned char *buf,  int len)
{
    int bytes = 0;
    struct timeval interval;
    int rc;

    interval.tv_sec = 3;
    interval.tv_usec = 0;

    rc = setsockopt(_cpub.sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&interval, sizeof(struct timeval));

    while (bytes < len)
    {
        rc = recv(_cpub.sockfd, &buf[bytes], (size_t)(len - bytes), 0);

        if (rc == -1)
        {
            if (errno != ENOTCONN && errno != ECONNRESET)
            {
                bytes = -1;
                break;
            }
        }
        else
            bytes += rc;
    }

    return bytes;
}

int mqtt_write(int sockfd, unsigned char *buf,  int len)
{
    int rc;
    struct timeval tv;

    tv.tv_sec = 2;
    tv.tv_usec = 0;

    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(struct timeval));
    rc = send(sockfd, buf, len, 0);
    if (rc == len)
        rc = 0;

    return rc;
}

int mqtt_subscribe(mqtt_client_t *c, char* topicstr, int qos)
{
    MQTTString topic = MQTTString_initializer;
    int msgid = 1;
    int len;
    int rc = -1;

    topic.cstring = topicstr;
    len = MQTTSerialize_subscribe(c->wbuf, c->wbuflen, 0, msgid, 1, &topic, &qos);
    if (len <= 0)
        goto exit;

    rc = mqtt_write(c->sockfd, c->wbuf, len);
    if (rc < 0)
        goto exit;

    if (MQTTPacket_read(c->rbuf, c->rbuflen, c->getfn) == SUBACK)
    {
        unsigned short submsgid;
        int subcount;
        int granted_qos;

        rc = MQTTDeserialize_suback(&submsgid, 1, &subcount, &granted_qos, c->rbuf, c->rbuflen);
        if (granted_qos != 0)
        {
            DEBUG("granted qos != 0, %d\n", granted_qos);
            rc = -1;
        }
        else
        {
            rc = 0;
        }
    }
    else
    {
        rc = -1;
    }

exit:
    return rc;
}

int mqtt_publish(mqtt_client_t *c, char* topicstr, mqtt_msg_t *msg)
{
    int rc = -1;
    MQTTString topic = MQTTString_initializer;
    int len;
    int pktype;

    topic.cstring = topicstr;

    len = MQTTSerialize_publish(c->wbuf, c->wbuflen,
                                                   msg->dup, msg->qos, msg->retained, msg->id,
                                                   topic, msg->payload, msg->payloadlen);
    if (len <= 0)
        goto exit;

    if ((rc = mqtt_write(c->sockfd, c->wbuf, len)) <= 0)
        goto exit;

    pktype = MQTTPacket_read(c->rbuf, c->rbuflen, c->getfn);

    if (msg->qos == 1)
    {
        if (pktype == PUBACK)
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->rbuf, c->rbuflen) != 1)
                rc = -1;
        }
        else
            rc = -1;
    }
    else if (msg->qos == 2)
    {
        if (pktype == PUBCOMP)
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->rbuf, c->rbuflen) != 1)
                rc = -1;
        }
        else
            rc = -1;
    }

exit:
    return rc;
}

int mqtt_netconnect(char *addr, int port)
{
    struct hostent *host = 0;
    struct sockaddr_in sockaddr;
    int sock;

    host = gethostbyname(addr);
    if (host == 0)
        return -1;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        return -1;
    }

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr = *((struct in_addr *)host->h_addr);
    memset(&(sockaddr.sin_zero), 0, sizeof(sockaddr.sin_zero));

    if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr)) == -1)
    {
        #if (OS_RTTHREAD == 0)
        close(sock);
        #else
        closesocket(sock);
        #endif
        return -2;
    }

    return sock;
}

void mqtt_netdisconnect(int *sockfd)
{
    #if (OS_RTTHREAD == 0)
    close(*sockfd);
    #else
    closesocket(*sockfd);
    #endif
    *sockfd = -1;
}

int mqtt_connect(mqtt_client_t *c, MQTTPacket_connectData *data)
{
    int rc = -1;
    int len;

    len = MQTTSerialize_connect(c->wbuf, c->wbuflen, data);
    if (len <= 0)
        goto exit;

    rc = mqtt_write(c->sockfd, c->wbuf, len);
    if (rc < 0)
        goto exit;

    rc = MQTTPacket_read(c->rbuf, c->rbuflen, c->getfn);
    if (rc < 0)
        goto exit;

    if (rc == CONNACK)
    {
        unsigned char sessionPresent, connack_rc;

        if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, c->rbuf, c->rbuflen) == 1)
        {
            rc = connack_rc;
        }
        else
        {
            rc = -1;
        }
    }
    else
        rc = -1;

exit:
    return rc;
}
int mqtt_disconnect(mqtt_client_t *c)
{
    int rc = -1;
    int len;

    len = MQTTSerialize_disconnect(c->wbuf, c->wbuflen);
    if (len > 0)
    {
        rc = mqtt_write(c->sockfd, c->wbuf, len);
    }

    return rc;
}

static void *mqtt_pub_thread(void *param)
{
    MQTTPacket_connectData condata = MQTTPacket_connectData_initializer;
    int rc;
    unsigned char rbuf[64];
    unsigned char wbuf[64];

    DEBUG("pub thread start\n");
    /*  */
    _cpub.rbuf = rbuf;
    _cpub.rbuflen = sizeof(rbuf);
    _cpub.wbuf = wbuf;
    _cpub.wbuflen = sizeof(wbuf);
    _cpub.getfn = pub_read;

    if ((_cpub.sockfd = mqtt_netconnect(HOSTNAME, HOSTPORT)) < 0)
    {
        DEBUG("pub netconnet fail\n");

        return 0;
    }

    DEBUG("pub connect to: %s %d\n", HOSTNAME, HOSTPORT);

    condata.clientID.cstring = "mqttpub";
    condata.keepAliveInterval = KEEPALIVE_INTERVAL;
    condata.cleansession = 1;
    condata.username.cstring = USERNAME;
    condata.password.cstring = PASSWORD;

    rc = mqtt_connect(&_cpub, &condata);
    if (rc < 0)
        goto exit;

    DEBUG("pub connect ok\n");

    mqtt_ping_start(&_cpub.sockfd);

    while (rc == 0)
    {
        mqtt_msg_t msg;

        SLEEP(5);
        msg.dup = 0;
        msg.id    = 0;
        msg.qos = 0;
        msg.retained = 0;
        msg.payload = (unsigned char*)"RT-Thread";
        msg.payloadlen = strlen((const char*)msg.payload);

        rc = mqtt_publish(&_cpub, TOPIC, &msg);
    }

exit:
    mqtt_netdisconnect(&_cpub.sockfd);
    DEBUG("pub thread exit\n");

    return 0;
}

void msgprocess(MQTTString *topic, mqtt_msg_t *msg)
{
    msg->payload[msg->payloadlen] = 0;
    DEBUG("recv: size = %d, msg = %s\n", msg->payloadlen, msg->payload);
}

static void *mqtt_sub_thread(void *param)
{
    MQTTPacket_connectData condata = MQTTPacket_connectData_initializer;
    int pktype, rc, len;
    int failcnt = 0;
    unsigned char wbuf[64];
    unsigned char rbuf[64];

    DEBUG("sub thread start\n");

    _csub.wbuf = wbuf;
    _csub.wbuflen = sizeof(wbuf);
    _csub.rbuf = rbuf;
    _csub.rbuflen = sizeof(rbuf);
    _csub.getfn = sub_read;

    if ((_csub.sockfd = mqtt_netconnect(HOSTNAME, HOSTPORT)) < 0)
    {
        DEBUG("sub netconnect fail\n");

        return 0;
    }

    DEBUG("sub connect to: %s %d\n", HOSTNAME, HOSTPORT);

    condata.clientID.cstring = "mqttsub";
    condata.keepAliveInterval = KEEPALIVE_INTERVAL;
    condata.cleansession = 1;
    condata.username.cstring = USERNAME;
    condata.password.cstring = PASSWORD;

    rc = mqtt_connect(&_csub, &condata);
    if (rc < 0)
        goto exit;

    DEBUG("sub connect ok\n");

    rc = mqtt_subscribe(&_csub, TOPIC, 0);
    if (rc < 0)
        goto exit;

    DEBUG("sub topic: %s\n", TOPIC);

    mqtt_ping_start(&_csub.sockfd);

    while (1)
    {
        pktype = MQTTPacket_read(_csub.rbuf, _csub.rbuflen, sub_read);

        switch (pktype)
        {
        case CONNACK:
        case PUBACK:
        case SUBACK:
            break;
        case PUBLISH:
        {
            MQTTString topic;
            mqtt_msg_t msg;

            if (MQTTDeserialize_publish(&msg.dup, &msg.qos, &msg.retained, &msg.id, &topic,
                                                         &msg.payload, &msg.payloadlen, _csub.rbuf, _csub.rbuflen) != 1)
                goto exit;

            msgprocess(&topic, &msg);

            if (msg.qos != 0)
            {
                if (msg.qos == 1)
                    len = MQTTSerialize_ack(_csub.wbuf, _csub.wbuflen, PUBACK, 0, msg.id);
                else if (msg.qos == 2)
                    len = MQTTSerialize_ack(_csub.wbuf, _csub.wbuflen, PUBREC, 0, msg.id);

                if (len <= 0)
                    rc = -1;
                else
                    rc = mqtt_write(_csub.sockfd, _csub.wbuf, len);

                if (rc == -1)
                    goto exit;
            }
        }
        break;
        case PUBCOMP:
            break;
        case PINGRESP:
            failcnt = 0;
            break;
        case -1:
            if (++failcnt > KEEPALIVE_INTERVAL)
            {
                /*  */
                goto exit;
            }
            break;
        }
    }
    /*  */
    mqtt_disconnect(&_csub);

exit:
    mqtt_netdisconnect(&_csub.sockfd);
    DEBUG("sub thread exit\n");

    return 0;
}

void mqtt_client_init(void)
{
    #if (OS_RTTHREAD == 0)
    pthread_t tid;

    pthread_create(&tid, NULL, mqtt_sub_thread, NULL);
    pthread_create(&tid, NULL, mqtt_pub_thread, NULL);
    #else
    sys_thread_new("sub",
                   mqtt_sub_thread,
                   NULL,
                   1024,
                   20);
    sys_thread_new("pub",
                   mqtt_pub_thread,
                   NULL,
                   1024,
                   20); 
    #endif
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(mqtt_client_init, MQTT Pub/Sub Test);
#endif
