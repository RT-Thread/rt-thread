#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <stdio.h>
#include <stdlib.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

#include <stm32f10x.h>
#include <rtthread.h>
#include <dfs_posix.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include "http.h"
#include "player_bg.h"

/* */
#define RADIO_FN                    "/radio.pls"
#define RADIO_LIST_UPDATE_URL       "http://radio.rt-thread.org/radio.pls"
/* */

/* */
extern int http_read_line( int socket, char * buffer, int size );
extern int http_is_error_header(char *mime_buf);
extern int http_resolve_address(struct sockaddr_in *server, const char * url, char *host_addr, char** request);
/* */

const char _radio_list_update_get[] = "GET %s HTTP/1.0\r\nHost: %s:%d\r\nUser-Agent: RT-Thread HTTP Agent\r\nConnection: close\r\n\r\n";
rt_mq_t update_radio_mq = RT_NULL;
static struct rtgui_view* update_radio_list_view = RT_NULL;

typedef enum
{
    UPDATE_RAIDO_LIST_PROC,
    UPDATE_RADIO_LIST_CONNECT_FAILED,
    UPDATE_RADIO_LIST_SUCCEED,
} UPDATE_RADIO_LIST_STATE;

static UPDATE_RADIO_LIST_STATE update_radio_list_state;

int  radio_list_update_servicer_connect(struct sockaddr_in* server, char* host_addr, const char* url)
{
    int socket_handle;
    int peer_handle;
    int rc;
    char mimeBuffer[256];

    if((socket_handle = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0)
    {
        rt_kprintf( "RLUS: SOCKET FAILED\n" );
        return -1;
    }

    peer_handle = connect( socket_handle, (struct sockaddr *) server, sizeof(*server));
    if ( peer_handle < 0 )
    {
        closesocket(socket_handle);
        rt_kprintf( "RLUS: CONNECT FAILED %i\n", peer_handle );
        return -1;
    }

    {
        char *buf;
        rt_uint32_t length;

        buf = rt_malloc (512);
        if (*url)
            length = rt_snprintf(buf, 512, _radio_list_update_get, url, host_addr, ntohs(server->sin_port));
        else
            length = rt_snprintf(buf, 512, _radio_list_update_get, "/", host_addr, ntohs(server->sin_port));

        rc = send(peer_handle, buf, length, 0);
        rt_kprintf("radio list update request:\n%s", buf);

        /* release buffer */
        rt_free(buf);
    }
    /* read the header information */
    while ( 1 )
    {
        // read a line from the header information.
        rc = http_read_line(peer_handle, mimeBuffer, 100);
        rt_kprintf(">>%s", mimeBuffer);

        if ( rc < 0 )
        {
            closesocket(peer_handle);
            return rc;
        }
        // End of headers is a blank line.  exit.
        if (rc == 0) break;
        if ((rc == 2) && (mimeBuffer[0] == '\r')) break;

        if (strstr(mimeBuffer, "HTTP/1."))
        {
            rc = http_is_error_header(mimeBuffer);
            if(rc)
            {
                rt_kprintf("HTTP: status code = %d!\n", rc);
                closesocket(peer_handle);
                return -rc;
            }
        }

        if (strstr(mimeBuffer, "content-type:"))
        {
            /* check content-type */
            if (strstr(mimeBuffer, "text/plain") == RT_NULL)
            {
                rt_kprintf("radio list update content is not text/plain.\n");
                closesocket(peer_handle);
                return -1;
            }
        }

        if (strstr(mimeBuffer, "Content-Type:"))
        {
            /* check content-type */
            if (strstr(mimeBuffer, "text/plain") == RT_NULL)
            {
                rt_kprintf("radio list update content is not text/plain.\n");
                closesocket(peer_handle);
                return -1;
            }
        }
    }

    return peer_handle;
}

int radio_list_update_servicer_session_open(char* url)
{
    int peer_handle = -1;
    struct sockaddr_in server;
    char *request, host_addr[32];

    if(http_resolve_address(&server, url, &host_addr[0], &request) != 0)
    {
        return -1;
    }
    rt_kprintf("connect to: %s...\n", host_addr);

    if((peer_handle = radio_list_update_servicer_connect(&server, host_addr, request)) < 0)
    {
        rt_kprintf("radio list update: failed to connect to '%s'!\n", host_addr);
    }
    return peer_handle;

}
int update_radio_list(char* url)
{
    char *buf = NULL;
    int peer_handle = 0;
    int fd;
    int rc;

    peer_handle = radio_list_update_servicer_session_open(url);

    if(peer_handle < 0)
    {
        return -1;
    }

    fd = open(RADIO_FN, O_WRONLY | O_CREAT | O_TRUNC, 0);
    if(fd < 0)
    {
        return -1;
    }
    buf = rt_malloc (512);
    while ( 1 )
    {
        // read a line from the header information.
        rc = http_read_line(peer_handle, buf, 100);

        if ( rc < 0 ) break;

        // End of headers is a blank line.  exit.
        if (rc == 0) break;
        if ((rc == 2) && (buf[0] == '\r')) break;
        rt_kprintf(">>%s", buf);

        write(fd, buf, rc);
    }
    rt_free(buf);

    closesocket(peer_handle);

    if(close(fd) == 0)
    {
        rt_kprintf("Update radio list succeed \r\n");
    }
    return 0;
}

void update_radio_list_req(void)
{

    struct player_request request;
    extern rt_mq_t player_thread_mq;
    char* ch = RT_NULL;

    update_radio_list_state = UPDATE_RAIDO_LIST_PROC;
    request.type = PLAYER_REQUEST_UPDATE_RADIO_LIST;
    ch = strncpy(request.fn, RADIO_LIST_UPDATE_URL, strlen(RADIO_LIST_UPDATE_URL));

    /* send to message queue */
    rt_mq_send(update_radio_mq, (void*)&request, sizeof(struct player_request));

}

void update_radio_thread(void* parameter)
{
    rt_err_t result;
    struct player_request request;
    rt_thread_t update_radio_list_thread;


    while(1)
    {
        /* get request from message queue */
        result = rt_mq_recv(update_radio_mq, (void*)&request,
                            sizeof(struct player_request), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            switch (request.type)
            {

            case PLAYER_REQUEST_UPDATE_RADIO_LIST:
                if ((strstr(request.fn, "http://") == request.fn ||
                        (strstr(request.fn, "HTTP://") == request.fn )))
                {
                    struct rtgui_event_command ecmd;

                    if(update_radio_list(request.fn)==0)
                    {
                        update_radio_list_state = 	UPDATE_RADIO_LIST_SUCCEED;
                    }
                    else
                    {
                        update_radio_list_state = 	UPDATE_RADIO_LIST_CONNECT_FAILED;
                    }
                    RTGUI_EVENT_COMMAND_INIT(&ecmd);
                    ecmd.type = RTGUI_EVENT_PAINT;
                    ecmd.command_id = PLAYER_REQUEST_UPDATE_RADIO_LIST;
                    rtgui_thread_send(rt_thread_find("ply_ui"), &ecmd.parent, sizeof(ecmd));
                }
                break;
            }
        }
        rt_mq_delete(update_radio_mq);
        update_radio_mq = RT_NULL;
        update_radio_list_thread = rt_thread_self();
        rt_thread_delete(update_radio_list_thread);
    }
}

void drawing_update_state_info(struct rtgui_widget* widget)
{
    char* line;
    struct rtgui_dc* dc;
    struct rtgui_rect rect;

    line = rtgui_malloc(256);
    if (line == RT_NULL) return ;

    dc = rtgui_dc_begin_drawing(widget);
    if (dc == RT_NULL)
    {
        rt_free(line);
        return;
    }

    rtgui_widget_get_rect(widget, &rect);

    /* fill background */
    rtgui_dc_fill_rect(dc, &rect);

    rect.y2 = rect.y1 + 18;
    switch(update_radio_list_state)
    {
    case UPDATE_RAIDO_LIST_PROC:
        sprintf(line, "正在更新电台列表......");
        break	;

    case UPDATE_RADIO_LIST_CONNECT_FAILED:
        sprintf(line, "更新电台列表失败,请返回");
        break;

    case UPDATE_RADIO_LIST_SUCCEED:
        sprintf(line, "更新电台列表成功,请返回");
        break;
    }

    rtgui_dc_draw_text(dc, line, &rect);

    rtgui_dc_end_drawing(dc);

    rtgui_free(line);
}

static rt_bool_t update_radio_list_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
    switch (event->type)
    {
    case RTGUI_EVENT_COMMAND:
    {
        struct rtgui_event_command* ecmd = (struct rtgui_event_command*)event;
        switch(ecmd->type)
        {
        case RTGUI_EVENT_PAINT:
            drawing_update_state_info(widget);
            return RT_FALSE;
        }
        return RT_FALSE;
    }
    case RTGUI_EVENT_PAINT:
    {
        drawing_update_state_info(widget);
        return RT_FALSE;
    }

    case RTGUI_EVENT_KBD:
    {
        struct rtgui_event_kbd* ekbd;

        ekbd = (struct rtgui_event_kbd*)event;
        if (ekbd->type == RTGUI_KEYDOWN && ekbd->key == RTGUIK_RETURN)
        {
            rtgui_workbench_t* workbench;

            workbench = RTGUI_WORKBENCH(RTGUI_WIDGET(update_radio_list_view)->parent);
            rtgui_workbench_remove_view(workbench, update_radio_list_view);

            rtgui_view_destroy(update_radio_list_view);
            update_radio_list_view = RT_NULL;
        }
    }
    return RT_FALSE;
    }

    /* use parent event handler */
    return rtgui_view_event_handler(widget, event);
}

rtgui_view_t *update_radio_list_view_create(rtgui_workbench_t* workbench)
{
    if (update_radio_list_view != RT_NULL)
    {
        rtgui_view_show(update_radio_list_view, RT_FALSE);
    }
    else
    {
        /* create a view */
        update_radio_list_view = rtgui_view_create("update radio list Info");
        /* set view event handler */
        rtgui_widget_set_event_handler(RTGUI_WIDGET(update_radio_list_view), update_radio_list_view_event_handler);
        /* this view can be focused */
        RTGUI_WIDGET(update_radio_list_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

        /* add view to workbench */
        rtgui_workbench_add_view(workbench, update_radio_list_view);
    }

    return update_radio_list_view;
}


