/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include <stdio.h>
#ifdef _WIN32
#include <sdl.h>
#else
#include <SDL/SDL.h>
#endif
#include <rtdevice.h>
#include <rtgui/driver.h>

#define SDL_SCREEN_WIDTH    480
#define SDL_SCREEN_HEIGHT   320

extern void rt_hw_exit(void);

#define SDL_SCREEN_FORMAT   SDL_PIXELFORMAT_RGB565

struct sdlfb_device
{
    struct rt_device parent;

    SDL_Renderer *renderer;         /* window renderer */
    SDL_Surface  *surface;          /* screen surface  */

    rt_uint16_t width;
    rt_uint16_t height;
};
struct sdlfb_device _device;

/* common device interface */
static rt_err_t  sdlfb_init(rt_device_t dev)
{
    return RT_EOK;
}
static rt_err_t  sdlfb_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}
static rt_err_t  sdlfb_close(rt_device_t dev)
{
    SDL_Quit();
    return RT_EOK;
}

int sdlfb_info(int *format, int *bpp)
{
    int bit_pp;                         /* texture bits per pixel */
    Uint32 Rmask, Gmask, Bmask, Amask;  /* masks for pixel format passed into OpenGL */

                                        /* Grab info about format that will be passed into OpenGL */
    SDL_PixelFormatEnumToMasks(SDL_SCREEN_FORMAT, &bit_pp, &Rmask, &Gmask,
        &Bmask, &Amask);

    *bpp = bit_pp;
    switch (SDL_SCREEN_FORMAT)
    {
    case SDL_PIXELFORMAT_RGB565:
        *format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
        break;
    case SDL_PIXELFORMAT_RGB888:
        *format = RTGRAPHIC_PIXEL_FORMAT_RGB888;
        break;
    case SDL_PIXELFORMAT_ARGB8888:
        *format = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
        break;
    case SDL_PIXELFORMAT_ABGR8888:
        *format = RTGRAPHIC_PIXEL_FORMAT_ABGR888;
    }

    return 0;
}

static rt_mutex_t sdllock;
static rt_err_t  sdlfb_control(rt_device_t dev, int cmd, void *args)
{
    struct sdlfb_device *device;

    rt_mutex_take(sdllock, RT_WAITING_FOREVER);
    device = (struct sdlfb_device *)dev;
    RT_ASSERT(device != RT_NULL);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
    {
        int format, bpp;
        struct rt_device_graphic_info *info;

        sdlfb_info(&format, &bpp);
        info = (struct rt_device_graphic_info *) args;
        info->bits_per_pixel = bpp;
        info->pixel_format = format;
        info->framebuffer = (rt_uint8_t*)device->surface->pixels;
        info->width = device->width;
        info->height = device->height;
    }
    break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        SDL_Texture * texture;
        struct rt_device_rect_info *rect;
        SDL_Rect _rect = { 0, 0, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT };

        rect = (struct rt_device_rect_info *)args;

        SDL_RenderClear(_device.renderer);

        texture = SDL_CreateTextureFromSurface(_device.renderer, _device.surface);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(_device.renderer, texture, NULL, &_rect);

        SDL_RenderPresent(_device.renderer);

        SDL_DestroyTexture(texture);
    }
    break;
    case RTGRAPHIC_CTRL_SET_MODE:
    {
        break;
    }
    break;
    }
    rt_mutex_release(sdllock);
    return RT_EOK;
}

Uint16 pixels[16 * 16] = {  // ...or with raw pixel data:
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
    0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
    0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
    0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
    0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
    0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
    0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
    0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
    0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
    0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
    0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
    0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
    0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
    0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
    0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
    0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
    0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
    0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
    0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
    0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
    0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
};

static void sdlfb_hw_init(void)
{
    SDL_Window *win;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    _device.parent.init = sdlfb_init;
    _device.parent.open = sdlfb_open;
    _device.parent.close = sdlfb_close;
    _device.parent.read = RT_NULL;
    _device.parent.write = RT_NULL;
    _device.parent.control = sdlfb_control;

    _device.width  = SDL_SCREEN_WIDTH;
    _device.height = SDL_SCREEN_HEIGHT;

    {
        int bpp;                            /* texture bits per pixel */
        Uint32 Rmask, Gmask, Bmask, Amask;  /* masks for pixel format passed into OpenGL */

        /* Grab info about format that will be passed into OpenGL */
        SDL_PixelFormatEnumToMasks(SDL_SCREEN_FORMAT, &bpp, &Rmask, &Gmask,
            &Bmask, &Amask);

        _device.surface = SDL_CreateRGBSurface(0, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT,
            bpp, Rmask, Gmask, Bmask, Amask);
    }

    win = SDL_CreateWindow("RT-Thread/Persimmon",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (win == NULL)
    {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        exit(1);
    }

    /* set the icon of Window */
    {
        SDL_Surface *surface;
        surface = SDL_CreateRGBSurfaceFrom(pixels, 16, 16, 16, 16 * 2, 0x0f00, 0x00f0, 0x000f, 0xf000);
        SDL_SetWindowIcon(win, surface);
    }

    _device.renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    rt_device_register(RT_DEVICE(&_device), "sdl", RT_DEVICE_FLAG_RDWR);

    sdllock = rt_mutex_create("fb", RT_IPC_FLAG_FIFO);
    if (sdllock == RT_NULL) 
    {
        LOG_E("Create mutex for sdlfb failed!");
    }
}

#ifdef _WIN32
#include  <windows.h>
#include  <mmsystem.h>
#else
#include <pthread.h>
#include <signal.h>
#endif

#include  <stdio.h>
#include <rtgui/event.h>
#include <rtgui/kbddef.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

#ifdef _WIN32
static HANDLE  sdl_ok_event = NULL;

static DWORD WINAPI sdl_loop(LPVOID lpParam)
#else
static pthread_mutex_t sdl_ok_mutex;
static pthread_cond_t sdl_ok_event;

static void *sdl_loop(void *lpParam)
#endif
{
    int quit = 0;
    SDL_Event event;
    int state = 0;
    rt_device_t device;
    int timeout = 1000000;

    int last_x = -1, last_y = -1;

    int motion_x, motion_y;
    int motion_button = 0;
    int motion_tick = 50;

    int mouse_id = 1;

#ifndef _WIN32
    sigset_t  sigmask, oldmask;
    /* set the getchar without buffer */
    sigfillset(&sigmask);
    pthread_sigmask(SIG_BLOCK, &sigmask, &oldmask);
    pthread_mutex_lock(&sdl_ok_mutex);
#endif

    sdlfb_hw_init();

    device = rt_device_find("sdl");
    RT_ASSERT(device);
    rtgui_graphic_set_device(device);
#ifdef _WIN32
    SetEvent(sdl_ok_event);
#else
    pthread_cond_signal(&sdl_ok_event);
    pthread_mutex_unlock(&sdl_ok_mutex);
#endif
    /* handle SDL event */
    while (!quit)
    {
        if (motion_button & RTGUI_MOUSE_BUTTON_DOWN)
        {
            timeout = motion_tick - SDL_GetTicks();
        }
        else
        {
            timeout = 1000 * 1000;
        }

        int tick = SDL_GetTicks();
        SDL_WaitEventTimeout(&event, timeout);
        if (SDL_GetTicks() >= motion_tick && (motion_button & RTGUI_MOUSE_BUTTON_DOWN)) /* whether timeout */
        {
            /* sendout motion event */
            struct rtgui_event_mouse emouse;

            emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
            emouse.parent.sender = RT_NULL;
            emouse.wid = RT_NULL;
            emouse.id = mouse_id;
            emouse.ts = rt_tick_get();

            if ((motion_x > 0 && motion_x < SDL_SCREEN_WIDTH) &&
                (motion_y > 0 && motion_y < SDL_SCREEN_HEIGHT))
            {
                emouse.x = motion_x;
                emouse.y = motion_y;

                /* init mouse button */
                emouse.button = motion_button;

                /* send event to server */
                rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));
            }

            /* reset motion tick */
            motion_tick = 50 + SDL_GetTicks();
        }

        switch (event.type)
        {
        case SDL_MOUSEMOTION:
        {
            /* save to (x,y) in the motion */
            motion_x = ((SDL_MouseMotionEvent *)&event)->x;
            motion_y = ((SDL_MouseMotionEvent *)&event)->y;
        }
        break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            int x, y;
            struct rtgui_event_mouse emouse;
            SDL_MouseButtonEvent *mb;

            emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
            emouse.parent.sender = RT_NULL;
            emouse.wid = RT_NULL;
            if (event.type == SDL_MOUSEBUTTONDOWN && state == 0)
                mouse_id = rt_tick_get();

            emouse.id = mouse_id;
            emouse.ts = rt_tick_get();

            mb = (SDL_MouseButtonEvent *)&event;

            x = mb->x;
            y = mb->y;
            if ((x > 0 && x < SDL_SCREEN_WIDTH) &&
                (y > 0 && y < SDL_SCREEN_HEIGHT))
            {
                emouse.x = x;
                emouse.y = y;

                /* init mouse button */
                emouse.button = 0;

                /* set emouse button */
                if (mb->button & (1 << (SDL_BUTTON_LEFT - 1)))
                {
                    emouse.button |= RTGUI_MOUSE_BUTTON_LEFT;
                }
                else if (mb->button & (1 << (SDL_BUTTON_RIGHT - 1)))
                {
                    emouse.button |= RTGUI_MOUSE_BUTTON_RIGHT;
                }
                else if (mb->button & (1 << (SDL_BUTTON_MIDDLE - 1)))
                {
                    emouse.button |= RTGUI_MOUSE_BUTTON_MIDDLE;
                }

                if (mb->type == SDL_MOUSEBUTTONDOWN)
                {
                    emouse.button |= RTGUI_MOUSE_BUTTON_DOWN;
                    motion_button = emouse.button;

                    /* set motion timeout tick */
                    motion_tick = 50 + SDL_GetTicks();

                    if (state == 0)
                    {
                        /* send event to server */
                        rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));
                        last_x = -1; last_y = -1;

                        state = 1;
                    }
                }
                else
                {
                    emouse.button |= RTGUI_MOUSE_BUTTON_UP;
                    motion_button = 0;

                    if (state == 1)
                    {
                        /* send event to server */
                        rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));
                        last_x = -1; last_y = -1;

                        state = 0;
                    }
                }
            }
        }
        break;

        case SDL_KEYUP:
        {
            struct rtgui_event_kbd ekbd;
            ekbd.parent.type    = RTGUI_EVENT_KBD;
            ekbd.parent.sender  = RT_NULL;
            ekbd.type = RTGUI_KEYUP;
            ekbd.wid = RT_NULL;
            ekbd.mod = event.key.keysym.mod;
            ekbd.key = event.key.keysym.sym;

            /* FIXME: unicode */
            ekbd.unicode = 0;

            /* send event to server */
            rtgui_server_post_event(&ekbd.parent, sizeof(struct rtgui_event_kbd));
        }
        break;

        case SDL_KEYDOWN:
        {
            struct rtgui_event_kbd ekbd;
            ekbd.parent.type    = RTGUI_EVENT_KBD;
            ekbd.parent.sender  = RT_NULL;
            ekbd.type = RTGUI_KEYDOWN;
            ekbd.wid = RT_NULL;
            ekbd.mod = event.key.keysym.mod;
            ekbd.key = event.key.keysym.sym;

            /* FIXME: unicode */
            ekbd.unicode = 0;

            /* send event to server */
            rtgui_server_post_event(&ekbd.parent, sizeof(struct rtgui_event_kbd));
        }
        break;

        case SDL_QUIT:
            SDL_Quit();
            quit = 1;
            break;

        default:
            break;
        }

        if (quit)
        {
            exit(1);
            break;
        }

    }
    rt_hw_exit();
    return 0;
}

/* start sdl thread */
void rt_hw_sdl_start(void)
{
#ifdef _WIN32
    HANDLE thread;
    DWORD  thread_id;
    sdl_ok_event = CreateEvent(NULL,
        FALSE,
        FALSE,
        NULL);
    if (sdl_ok_event == NULL)
    {
        printf("error, create SDL event failed\n");
        exit(-1);
    }
    /* create thread that loop sdl event */
    thread = CreateThread(NULL,
                          0,
                          (LPTHREAD_START_ROUTINE)sdl_loop,
                          0,
                          CREATE_SUSPENDED,
                          &thread_id);
    if (thread == NULL)
    {
        //Display Error Message

        return;
    }
    ResumeThread(thread);

    /* wait until SDL LCD device is registered and seted */
    WaitForSingleObject(sdl_ok_event, INFINITE);
#else
    /* Linux */
    pthread_t pid;
    int res;

    pthread_mutex_init(&sdl_ok_mutex, NULL);
    pthread_cond_init(&sdl_ok_event, NULL);

    res = pthread_create(&pid, NULL, &sdl_loop, NULL);
    if (res)
    {
        printf("pthread create sdl thread faild, <%d>\n", res);
        exit(EXIT_FAILURE);
    }
    pthread_mutex_lock(&sdl_ok_mutex);
    pthread_cond_wait(&sdl_ok_event, &sdl_ok_mutex);

    pthread_mutex_destroy(&sdl_ok_mutex);
    pthread_cond_destroy(&sdl_ok_event);
#endif
}
