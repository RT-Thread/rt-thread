/**
 * @file win32drv.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "win32drv.h"

#if USE_WIN32DRV

#include <windowsx.h>
#include <process.h>
#include <stdbool.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define WINDOW_EX_STYLE \
    WS_EX_CLIENTEDGE

#define WINDOW_STYLE \
    (WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME))

#ifndef WIN32DRV_MONITOR_ZOOM
#define WIN32DRV_MONITOR_ZOOM 1
#endif

#ifndef USER_DEFAULT_SCREEN_DPI
#define USER_DEFAULT_SCREEN_DPI 96
#endif

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _WINDOW_THREAD_PARAMETER
{
    HANDLE window_mutex;
    HINSTANCE instance_handle;
    HICON icon_handle;
    lv_coord_t hor_res;
    lv_coord_t ver_res;
    int show_window_mode;
} WINDOW_THREAD_PARAMETER, * PWINDOW_THREAD_PARAMETER;

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**
 * @brief Creates a B8G8R8A8 frame buffer.
 * @param WindowHandle A handle to the window for the creation of the frame
 *                     buffer. If this value is NULL, the entire screen will be
 *                     referenced.
 * @param Width The width of the frame buffer.
 * @param Height The height of the frame buffer.
 * @param PixelBuffer The raw pixel buffer of the frame buffer you created.
 * @param PixelBufferSize The size of the frame buffer you created.
 * @return If the function succeeds, the return value is a handle to the device
 *         context (DC) for the frame buffer. If the function fails, the return
 *         value is NULL, and PixelBuffer parameter is NULL.
*/
static HDC lv_win32_create_frame_buffer(
    _In_opt_ HWND WindowHandle,
    _In_ LONG Width,
    _In_ LONG Height,
    _Out_ UINT32** PixelBuffer,
    _Out_ SIZE_T* PixelBufferSize);

/**
 * @brief Enables WM_DPICHANGED message for child window for the associated
 *        window.
 * @param WindowHandle The window you want to enable WM_DPICHANGED message for
 *                     child window.
 * @return If the function succeeds, the return value is non-zero. If the
 *         function fails, the return value is zero.
 * @remarks You need to use this function in Windows 10 Threshold 1 or Windows
 *          10 Threshold 2.
*/
static BOOL lv_win32_enable_child_window_dpi_message(
    _In_ HWND WindowHandle);

/**
 * @brief Registers a window as being touch-capable.
 * @param hWnd The handle of the window being registered.
 * @param ulFlags A set of bit flags that specify optional modifications.
 * @return If the function succeeds, the return value is nonzero. If the
 *         function fails, the return value is zero.
 * @remark For more information, see RegisterTouchWindow.
*/
static BOOL lv_win32_register_touch_window(
    HWND hWnd,
    ULONG ulFlags);

/**
 * @brief Retrieves detailed information about touch inputs associated with a
 *        particular touch input handle.
 * @param hTouchInput The touch input handle received in the LPARAM of a touch
 *                    message.
 * @param cInputs The number of structures in the pInputs array.
 * @param pInputs A pointer to an array of TOUCHINPUT structures to receive
 *                information about the touch points associated with the
 *                specified touch input handle.
 * @param cbSize The size, in bytes, of a single TOUCHINPUT structure.
 * @return If the function succeeds, the return value is nonzero. If the
 *         function fails, the return value is zero.
 * @remark For more information, see GetTouchInputInfo.
*/
static BOOL lv_win32_get_touch_input_info(
    HTOUCHINPUT hTouchInput,
    UINT cInputs,
    PTOUCHINPUT pInputs,
    int cbSize);

/**
 * @brief Closes a touch input handle, frees process memory associated with it,
          and invalidates the handle.
 * @param hTouchInput The touch input handle received in the LPARAM of a touch
 *                    message.
 * @return If the function succeeds, the return value is nonzero. If the
 *         function fails, the return value is zero.
 * @remark For more information, see CloseTouchInputHandle.
*/
static BOOL lv_win32_close_touch_input_handle(
    HTOUCHINPUT hTouchInput);

/**
 * @brief Returns the dots per inch (dpi) value for the associated window.
 * @param WindowHandle The window you want to get information about.
 * @return The DPI for the window.
*/
static UINT lv_win32_get_dpi_for_window(
    _In_ HWND WindowHandle);

static void lv_win32_display_driver_flush_callback(
    lv_disp_drv_t* disp_drv,
    const lv_area_t* area,
    lv_color_t* color_p);

static void lv_win32_display_refresh_handler(
    lv_timer_t* param);

static void lv_win32_pointer_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data);

static void lv_win32_keypad_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data);

static void lv_win32_encoder_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data);

static LRESULT CALLBACK lv_win32_window_message_callback(
    HWND   hWnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam);

static unsigned int __stdcall lv_win32_window_thread_entrypoint(
    void* raw_parameter);

/**********************
 *  GLOBAL VARIABLES
 **********************/

EXTERN_C bool lv_win32_quit_signal = false;

EXTERN_C lv_indev_t* lv_win32_pointer_device_object = NULL;
EXTERN_C lv_indev_t* lv_win32_keypad_device_object = NULL;
EXTERN_C lv_indev_t* lv_win32_encoder_device_object = NULL;

/**********************
 *  STATIC VARIABLES
 **********************/

static HWND g_window_handle = NULL;

static HDC g_buffer_dc_handle = NULL;
static UINT32* g_pixel_buffer = NULL;
static SIZE_T g_pixel_buffer_size = 0;

static lv_disp_t* g_display = NULL;
static bool volatile g_display_refreshing = false;

static bool volatile g_mouse_pressed = false;
static LPARAM volatile g_mouse_value = 0;

static bool volatile g_mousewheel_pressed = false;
static int16_t volatile g_mousewheel_value = 0;

static bool volatile g_keyboard_pressed = false;
static WPARAM volatile g_keyboard_value = 0;

static int volatile g_dpi_value = USER_DEFAULT_SCREEN_DPI;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

EXTERN_C void lv_win32_add_all_input_devices_to_group(
    lv_group_t* group)
{
    if (!group)
    {
        LV_LOG_WARN(
            "The group object is NULL. Get the default group object instead.");

        group = lv_group_get_default();
        if (!group)
        {
            LV_LOG_WARN(
                "The default group object is NULL. Create a new group object "
                "and set it to default instead.");

            group = lv_group_create();
            if (group)
            {
                lv_group_set_default(group);
            }
        }
    }

    LV_ASSERT_MSG(group, "Cannot obtain an available group object.");

    lv_indev_set_group(lv_win32_pointer_device_object, group);
    lv_indev_set_group(lv_win32_keypad_device_object, group);
    lv_indev_set_group(lv_win32_encoder_device_object, group);
}

EXTERN_C bool lv_win32_init(
    HINSTANCE instance_handle,
    int show_window_mode,
    lv_coord_t hor_res,
    lv_coord_t ver_res,
    HICON icon_handle)
{
    PWINDOW_THREAD_PARAMETER parameter =
        (PWINDOW_THREAD_PARAMETER)malloc(sizeof(WINDOW_THREAD_PARAMETER));
    parameter->window_mutex = CreateEventExW(NULL, NULL, 0, EVENT_ALL_ACCESS);
    parameter->instance_handle = instance_handle;
    parameter->icon_handle = icon_handle;
    parameter->hor_res = hor_res;
    parameter->ver_res = ver_res;
    parameter->show_window_mode = show_window_mode;

    _beginthreadex(
        NULL,
        0,
        lv_win32_window_thread_entrypoint,
        parameter,
        0,
        NULL);

    WaitForSingleObjectEx(parameter->window_mutex, INFINITE, FALSE);

    static lv_disp_draw_buf_t display_buffer;
#if (LV_COLOR_DEPTH == 32) || \
    (LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0) || \
    (LV_COLOR_DEPTH == 8) || \
    (LV_COLOR_DEPTH == 1)
    lv_disp_draw_buf_init(
        &display_buffer,
        (lv_color_t*)g_pixel_buffer,
        NULL,
        hor_res * ver_res);
#else
    lv_disp_draw_buf_init(
        &display_buffer,
        (lv_color_t*)malloc(hor_res * ver_res * sizeof(lv_color_t)),
        NULL,
        hor_res * ver_res);
#endif

    static lv_disp_drv_t display_driver;
    lv_disp_drv_init(&display_driver);
    display_driver.hor_res = hor_res;
    display_driver.ver_res = ver_res;
    display_driver.flush_cb = lv_win32_display_driver_flush_callback;
    display_driver.draw_buf = &display_buffer;
    display_driver.direct_mode = 1;
    g_display = lv_disp_drv_register(&display_driver);
    lv_timer_del(g_display->refr_timer);
    g_display->refr_timer = NULL;
    lv_timer_create(lv_win32_display_refresh_handler, 0, NULL);

    static lv_indev_drv_t pointer_driver;
    lv_indev_drv_init(&pointer_driver);
    pointer_driver.type = LV_INDEV_TYPE_POINTER;
    pointer_driver.read_cb = lv_win32_pointer_driver_read_callback;
    lv_win32_pointer_device_object = lv_indev_drv_register(&pointer_driver);

    static lv_indev_drv_t keypad_driver;
    lv_indev_drv_init(&keypad_driver);
    keypad_driver.type = LV_INDEV_TYPE_KEYPAD;
    keypad_driver.read_cb = lv_win32_keypad_driver_read_callback;
    lv_win32_keypad_device_object = lv_indev_drv_register(&keypad_driver);

    static lv_indev_drv_t encoder_driver;
    lv_indev_drv_init(&encoder_driver);
    encoder_driver.type = LV_INDEV_TYPE_ENCODER;
    encoder_driver.read_cb = lv_win32_encoder_driver_read_callback;
    lv_win32_encoder_device_object = lv_indev_drv_register(&encoder_driver);

    return true;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static HDC lv_win32_create_frame_buffer(
    HWND WindowHandle,
    LONG Width,
    LONG Height,
    UINT32** PixelBuffer,
    SIZE_T* PixelBufferSize)
{
    HDC hFrameBufferDC = NULL;

    if (PixelBuffer && PixelBufferSize)
    {
        HDC hWindowDC = GetDC(WindowHandle);
        if (hWindowDC)
        {
            hFrameBufferDC = CreateCompatibleDC(hWindowDC);
            ReleaseDC(WindowHandle, hWindowDC);
        }

        if (hFrameBufferDC)
        {
#if LV_COLOR_DEPTH == 32
            BITMAPINFO BitmapInfo = { 0 };
#elif LV_COLOR_DEPTH == 16
            typedef struct _BITMAPINFO_16BPP {
                BITMAPINFOHEADER bmiHeader;
                DWORD bmiColorMask[3];
            } BITMAPINFO_16BPP, *PBITMAPINFO_16BPP;

            BITMAPINFO_16BPP BitmapInfo = { 0 };
#elif LV_COLOR_DEPTH == 8
            typedef struct _BITMAPINFO_8BPP {
                BITMAPINFOHEADER bmiHeader;
                RGBQUAD bmiColors[256];
            } BITMAPINFO_8BPP, *PBITMAPINFO_8BPP;

            BITMAPINFO_8BPP BitmapInfo = { 0 };
#elif LV_COLOR_DEPTH == 1
            typedef struct _BITMAPINFO_1BPP {
                BITMAPINFOHEADER bmiHeader;
                RGBQUAD bmiColors[2];
            } BITMAPINFO_1BPP, *PBITMAPINFO_1BPP;

            BITMAPINFO_1BPP BitmapInfo = { 0 };
#else
            BITMAPINFO BitmapInfo = { 0 };
#endif

            BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            BitmapInfo.bmiHeader.biWidth = Width;
            BitmapInfo.bmiHeader.biHeight = -Height;
            BitmapInfo.bmiHeader.biPlanes = 1;
#if LV_COLOR_DEPTH == 32
            BitmapInfo.bmiHeader.biBitCount = 32;
            BitmapInfo.bmiHeader.biCompression = BI_RGB;
#elif LV_COLOR_DEPTH == 16
            BitmapInfo.bmiHeader.biBitCount = 16;
            BitmapInfo.bmiHeader.biCompression = BI_BITFIELDS;
            BitmapInfo.bmiColorMask[0] = 0xF800;
            BitmapInfo.bmiColorMask[1] = 0x07E0;
            BitmapInfo.bmiColorMask[2] = 0x001F;
#elif LV_COLOR_DEPTH == 8
            BitmapInfo.bmiHeader.biBitCount = 8;
            BitmapInfo.bmiHeader.biCompression = BI_RGB;
            for (size_t i = 0; i < 256; ++i)
            {
                lv_color8_t color;
                color.full = i;

                BitmapInfo.bmiColors[i].rgbRed = LV_COLOR_GET_R(color) * 36;
                BitmapInfo.bmiColors[i].rgbGreen = LV_COLOR_GET_G(color) * 36;
                BitmapInfo.bmiColors[i].rgbBlue = LV_COLOR_GET_B(color) * 85;
                BitmapInfo.bmiColors[i].rgbReserved = 0xFF;
            }
#elif LV_COLOR_DEPTH == 1
            BitmapInfo.bmiHeader.biBitCount = 8;
            BitmapInfo.bmiHeader.biCompression = BI_RGB;
            BitmapInfo.bmiHeader.biClrUsed = 2;
            BitmapInfo.bmiHeader.biClrImportant = 2;
            BitmapInfo.bmiColors[0].rgbRed = 0x00;
            BitmapInfo.bmiColors[0].rgbGreen = 0x00;
            BitmapInfo.bmiColors[0].rgbBlue = 0x00;
            BitmapInfo.bmiColors[0].rgbReserved = 0xFF;
            BitmapInfo.bmiColors[1].rgbRed = 0xFF;
            BitmapInfo.bmiColors[1].rgbGreen = 0xFF;
            BitmapInfo.bmiColors[1].rgbBlue = 0xFF;
            BitmapInfo.bmiColors[1].rgbReserved = 0xFF;
#else
            BitmapInfo.bmiHeader.biBitCount = 32;
            BitmapInfo.bmiHeader.biCompression = BI_RGB;
#endif

            HBITMAP hBitmap = CreateDIBSection(
                hFrameBufferDC,
                (PBITMAPINFO)(&BitmapInfo),
                DIB_RGB_COLORS,
                (void**)PixelBuffer,
                NULL,
                0);
            if (hBitmap)
            {
#if LV_COLOR_DEPTH == 32
                *PixelBufferSize = Width * Height * sizeof(UINT32);
#elif LV_COLOR_DEPTH == 16
                *PixelBufferSize = Width * Height * sizeof(UINT16);
#elif LV_COLOR_DEPTH == 8
                *PixelBufferSize = Width * Height * sizeof(UINT8);
#elif LV_COLOR_DEPTH == 1
                *PixelBufferSize = Width * Height * sizeof(UINT8);
#else
                *PixelBufferSize = Width * Height * sizeof(UINT32);
#endif

                DeleteObject(SelectObject(hFrameBufferDC, hBitmap));
                DeleteObject(hBitmap);
            }
            else
            {
                DeleteDC(hFrameBufferDC);
                hFrameBufferDC = NULL;
            }
        }
    }

    return hFrameBufferDC;
}

static BOOL lv_win32_enable_child_window_dpi_message(
    HWND WindowHandle)
{
    // This hack is only for Windows 10 TH1/TH2 only.
    // We don't need this hack if the Per Monitor Aware V2 is existed.
    OSVERSIONINFOEXW OSVersionInfoEx = { 0 };
    OSVersionInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
    OSVersionInfoEx.dwMajorVersion = 10;
    OSVersionInfoEx.dwMinorVersion = 0;
    OSVersionInfoEx.dwBuildNumber = 14393;
    if (!VerifyVersionInfoW(
        &OSVersionInfoEx,
        VER_MAJORVERSION | VER_MINORVERSION | VER_BUILDNUMBER,
        VerSetConditionMask(
            VerSetConditionMask(
                VerSetConditionMask(
                    0,
                    VER_MAJORVERSION,
                    VER_GREATER_EQUAL),
                VER_MINORVERSION,
                VER_GREATER_EQUAL),
            VER_BUILDNUMBER,
            VER_LESS)))
    {
        return FALSE;
    }

    HMODULE ModuleHandle = GetModuleHandleW(L"user32.dll");
    if (!ModuleHandle)
    {
        return FALSE;
    }

    typedef BOOL(WINAPI* FunctionType)(HWND, BOOL);

    FunctionType pFunction = (FunctionType)(
        GetProcAddress(ModuleHandle, "EnableChildWindowDpiMessage"));
    if (!pFunction)
    {
        return FALSE;
    }

    return pFunction(WindowHandle, TRUE);
}

static BOOL lv_win32_register_touch_window(
    HWND hWnd,
    ULONG ulFlags)
{
    HMODULE ModuleHandle = GetModuleHandleW(L"user32.dll");
    if (!ModuleHandle)
    {
        return FALSE;
    }

    typedef BOOL(WINAPI* FunctionType)(HWND, ULONG);

    FunctionType pFunction = (FunctionType)(
        GetProcAddress(ModuleHandle, "RegisterTouchWindow"));
    if (!pFunction)
    {
        return FALSE;
    }

    return pFunction(hWnd, ulFlags);
}

static BOOL lv_win32_get_touch_input_info(
    HTOUCHINPUT hTouchInput,
    UINT cInputs,
    PTOUCHINPUT pInputs,
    int cbSize)
{
    HMODULE ModuleHandle = GetModuleHandleW(L"user32.dll");
    if (!ModuleHandle)
    {
        return FALSE;
    }

    typedef BOOL(WINAPI* FunctionType)(HTOUCHINPUT, UINT, PTOUCHINPUT, int);

    FunctionType pFunction = (FunctionType)(
        GetProcAddress(ModuleHandle, "GetTouchInputInfo"));
    if (!pFunction)
    {
        return FALSE;
    }

    return pFunction(hTouchInput, cInputs, pInputs, cbSize);
}

static BOOL lv_win32_close_touch_input_handle(
    HTOUCHINPUT hTouchInput)
{
    HMODULE ModuleHandle = GetModuleHandleW(L"user32.dll");
    if (!ModuleHandle)
    {
        return FALSE;
    }

    typedef BOOL(WINAPI* FunctionType)(HTOUCHINPUT);

    FunctionType pFunction = (FunctionType)(
        GetProcAddress(ModuleHandle, "CloseTouchInputHandle"));
    if (!pFunction)
    {
        return FALSE;
    }

    return pFunction(hTouchInput);
}

static UINT lv_win32_get_dpi_for_window(
    _In_ HWND WindowHandle)
{
    UINT Result = (UINT)(-1);

    HMODULE ModuleHandle = LoadLibraryW(L"SHCore.dll");
    if (ModuleHandle)
    {
        typedef enum MONITOR_DPI_TYPE_PRIVATE {
            MDT_EFFECTIVE_DPI = 0,
            MDT_ANGULAR_DPI = 1,
            MDT_RAW_DPI = 2,
            MDT_DEFAULT = MDT_EFFECTIVE_DPI
        } MONITOR_DPI_TYPE_PRIVATE;

        typedef HRESULT(WINAPI* FunctionType)(
            HMONITOR, MONITOR_DPI_TYPE_PRIVATE, UINT*, UINT*);

        FunctionType pFunction = (FunctionType)(
            GetProcAddress(ModuleHandle, "GetDpiForMonitor"));
        if (pFunction)
        {
            HMONITOR MonitorHandle = MonitorFromWindow(
                WindowHandle,
                MONITOR_DEFAULTTONEAREST);

            UINT dpiX = 0;
            UINT dpiY = 0;
            if (SUCCEEDED(pFunction(
                MonitorHandle,
                MDT_EFFECTIVE_DPI,
                &dpiX,
                &dpiY)))
            {
                Result = dpiX;
            }
        }

        FreeLibrary(ModuleHandle);
    }

    if (Result == (UINT)(-1))
    {
        HDC hWindowDC = GetDC(WindowHandle);
        if (hWindowDC)
        {
            Result = GetDeviceCaps(hWindowDC, LOGPIXELSX);
            ReleaseDC(WindowHandle, hWindowDC);
        }
    }

    if (Result == (UINT)(-1))
    {
        Result = USER_DEFAULT_SCREEN_DPI;
    }

    return Result;
}

static void lv_win32_display_driver_flush_callback(
    lv_disp_drv_t* disp_drv,
    const lv_area_t* area,
    lv_color_t* color_p)
{
    if (lv_disp_flush_is_last(disp_drv))
    {
#if (LV_COLOR_DEPTH == 32) || \
    (LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0) || \
    (LV_COLOR_DEPTH == 8) || \
    (LV_COLOR_DEPTH == 1)
        UNREFERENCED_PARAMETER(color_p);
#elif (LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0)
        SIZE_T count = g_pixel_buffer_size / sizeof(UINT16);
        PUINT16 source = (PUINT16)color_p;
        PUINT16 destination = (PUINT16)g_pixel_buffer;
        for (SIZE_T i = 0; i < count; ++i)
        {
            UINT16 current = *source;
            *destination = (LOBYTE(current) << 8) | HIBYTE(current);

            ++source;
            ++destination;
        }
#else
        for (int y = area->y1; y <= area->y2; ++y)
        {
            for (int x = area->x1; x <= area->x2; ++x)
            {
                g_pixel_buffer[y * disp_drv->hor_res + x] =
                    lv_color_to32(*color_p);
                color_p++;
            }
        }
#endif

        InvalidateRect(g_window_handle, NULL, FALSE);
    }

    lv_disp_flush_ready(disp_drv);
}

static void lv_win32_display_refresh_handler(
    lv_timer_t* param)
{
    UNREFERENCED_PARAMETER(param);

    if (!g_display_refreshing)
    {
        _lv_disp_refr_timer(NULL);
    }
}

static void lv_win32_pointer_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data)
{
    UNREFERENCED_PARAMETER(indev_drv);

    data->state = (lv_indev_state_t)(
        g_mouse_pressed ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL);

    data->point.x = MulDiv(
        GET_X_LPARAM(g_mouse_value),
        USER_DEFAULT_SCREEN_DPI,
        WIN32DRV_MONITOR_ZOOM * g_dpi_value);
    data->point.y = MulDiv(
        GET_Y_LPARAM(g_mouse_value),
        USER_DEFAULT_SCREEN_DPI,
        WIN32DRV_MONITOR_ZOOM * g_dpi_value);

    if (data->point.x < 0)
    {
        data->point.x = 0;
    }
    if (data->point.x > g_display->driver->hor_res - 1)
    {
        data->point.x = g_display->driver->hor_res - 1;
    }
    if (data->point.y < 0)
    {
        data->point.y = 0;
    }
    if (data->point.y > g_display->driver->ver_res - 1)
    {
        data->point.y = g_display->driver->ver_res - 1;
    }
}

static void lv_win32_keypad_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data)
{
    UNREFERENCED_PARAMETER(indev_drv);

    data->state = (lv_indev_state_t)(
        g_keyboard_pressed ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL);

    WPARAM KeyboardValue = g_keyboard_value;

    switch (KeyboardValue)
    {
    case VK_UP:
        data->key = LV_KEY_UP;
        break;
    case VK_DOWN:
        data->key = LV_KEY_DOWN;
        break;
    case VK_LEFT:
        data->key = LV_KEY_LEFT;
        break;
    case VK_RIGHT:
        data->key = LV_KEY_RIGHT;
        break;
    case VK_ESCAPE:
        data->key = LV_KEY_ESC;
        break;
    case VK_DELETE:
        data->key = LV_KEY_DEL;
        break;
    case VK_BACK:
        data->key = LV_KEY_BACKSPACE;
        break;
    case VK_RETURN:
        data->key = LV_KEY_ENTER;
        break;
    case VK_NEXT:
        data->key = LV_KEY_NEXT;
        break;
    case VK_PRIOR:
        data->key = LV_KEY_PREV;
        break;
    case VK_HOME:
        data->key = LV_KEY_HOME;
        break;
    case VK_END:
        data->key = LV_KEY_END;
        break;
    default:
        if (KeyboardValue >= 'A' && KeyboardValue <= 'Z')
        {
            KeyboardValue += 0x20;
        }

        data->key = (uint32_t)KeyboardValue;

        break;
    }
}

static void lv_win32_encoder_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data)
{
    UNREFERENCED_PARAMETER(indev_drv);

    data->state = (lv_indev_state_t)(
        g_mousewheel_pressed ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL);
    data->enc_diff = g_mousewheel_value;
    g_mousewheel_value = 0;
}

static LRESULT CALLBACK lv_win32_window_message_callback(
    HWND   hWnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    {
        g_mouse_value = lParam;
        if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP)
        {
            g_mouse_pressed = (uMsg == WM_LBUTTONDOWN);
        }
        else if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP)
        {
            g_mousewheel_pressed = (uMsg == WM_MBUTTONDOWN);
        }
        return 0;
    }
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        g_keyboard_pressed = (uMsg == WM_KEYDOWN);
        g_keyboard_value = wParam;
        break;
    }
    case WM_MOUSEWHEEL:
    {
        g_mousewheel_value = -(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
        break;
    }
    case WM_TOUCH:
    {
        UINT cInputs = LOWORD(wParam);
        HTOUCHINPUT hTouchInput = (HTOUCHINPUT)(lParam);

        PTOUCHINPUT pInputs = malloc(cInputs * sizeof(TOUCHINPUT));
        if (pInputs)
        {
            if (lv_win32_get_touch_input_info(
                hTouchInput,
                cInputs,
                pInputs,
                sizeof(TOUCHINPUT)))
            {
                for (UINT i = 0; i < cInputs; ++i)
                {
                    POINT Point;
                    Point.x = TOUCH_COORD_TO_PIXEL(pInputs[i].x);
                    Point.y = TOUCH_COORD_TO_PIXEL(pInputs[i].y);
                    if (!ScreenToClient(hWnd, &Point))
                    {
                        continue;
                    }

                    uint16_t x = (uint16_t)(Point.x & 0xffff);
                    uint16_t y = (uint16_t)(Point.y & 0xffff);

                    DWORD MousePressedMask =
                        TOUCHEVENTF_MOVE | TOUCHEVENTF_DOWN;

                    g_mouse_value = (y << 16) | x;
                    g_mouse_pressed = (pInputs[i].dwFlags & MousePressedMask);
                }
            }

            free(pInputs);
        }

        lv_win32_close_touch_input_handle(hTouchInput);

        break;
    }
    case WM_DPICHANGED:
    {
        g_dpi_value = HIWORD(wParam);

        LPRECT SuggestedRect = (LPRECT)lParam;

        SetWindowPos(
            hWnd,
            NULL,
            SuggestedRect->left,
            SuggestedRect->top,
            SuggestedRect->right,
            SuggestedRect->bottom,
            SWP_NOZORDER | SWP_NOACTIVATE);

        RECT ClientRect;
        GetClientRect(hWnd, &ClientRect);

        int WindowWidth = MulDiv(
            g_display->driver->hor_res * WIN32DRV_MONITOR_ZOOM,
            g_dpi_value,
            USER_DEFAULT_SCREEN_DPI);
        int WindowHeight = MulDiv(
            g_display->driver->ver_res * WIN32DRV_MONITOR_ZOOM,
            g_dpi_value,
            USER_DEFAULT_SCREEN_DPI);

        SetWindowPos(
            hWnd,
            NULL,
            SuggestedRect->left,
            SuggestedRect->top,
            SuggestedRect->right + (WindowWidth - ClientRect.right),
            SuggestedRect->bottom + (WindowHeight - ClientRect.bottom),
            SWP_NOZORDER | SWP_NOACTIVATE);

        break;
    }
    case WM_PAINT:
    {
        g_display_refreshing = true;

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (g_display)
        {
            SetStretchBltMode(hdc, HALFTONE);

            StretchBlt(
                hdc,
                ps.rcPaint.left,
                ps.rcPaint.top,
                ps.rcPaint.right - ps.rcPaint.left,
                ps.rcPaint.bottom - ps.rcPaint.top,
                g_buffer_dc_handle,
                0,
                0,
                MulDiv(
                    ps.rcPaint.right - ps.rcPaint.left,
                    USER_DEFAULT_SCREEN_DPI,
                    WIN32DRV_MONITOR_ZOOM * g_dpi_value),
                MulDiv(
                    ps.rcPaint.bottom - ps.rcPaint.top,
                    USER_DEFAULT_SCREEN_DPI,
                    WIN32DRV_MONITOR_ZOOM * g_dpi_value),
                SRCCOPY);
        }

        EndPaint(hWnd, &ps);

        g_display_refreshing = false;

        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

static unsigned int __stdcall lv_win32_window_thread_entrypoint(
    void* raw_parameter)
{
    PWINDOW_THREAD_PARAMETER parameter =
        (PWINDOW_THREAD_PARAMETER)raw_parameter;

    WNDCLASSEXW window_class;
    window_class.cbSize = sizeof(WNDCLASSEXW);
    window_class.style = 0;
    window_class.lpfnWndProc = lv_win32_window_message_callback;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = parameter->instance_handle;
    window_class.hIcon = parameter->icon_handle;
    window_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = L"lv_sim_visual_studio";
    window_class.hIconSm = parameter->icon_handle;
    if (!RegisterClassExW(&window_class))
    {
        return 0;
    }

    HWND window_handle = CreateWindowExW(
        WINDOW_EX_STYLE,
        window_class.lpszClassName,
        L"LVGL Simulator for Windows Desktop",
        WINDOW_STYLE,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        NULL,
        NULL,
        parameter->instance_handle,
        NULL);

    if (!window_handle)
    {
        return 0;
    }

    g_dpi_value = lv_win32_get_dpi_for_window(window_handle);

    RECT window_size;

    window_size.left = 0;
    window_size.right = MulDiv(
        parameter->hor_res * WIN32DRV_MONITOR_ZOOM,
        g_dpi_value,
        USER_DEFAULT_SCREEN_DPI);
    window_size.top = 0;
    window_size.bottom = MulDiv(
        parameter->ver_res * WIN32DRV_MONITOR_ZOOM,
        g_dpi_value,
        USER_DEFAULT_SCREEN_DPI);

    AdjustWindowRectEx(
        &window_size,
        WINDOW_STYLE,
        FALSE,
        WINDOW_EX_STYLE);
    OffsetRect(
        &window_size,
        -window_size.left,
        -window_size.top);

    SetWindowPos(
        window_handle,
        NULL,
        0,
        0,
        window_size.right,
        window_size.bottom,
        SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);

    lv_win32_register_touch_window(window_handle, 0);

    lv_win32_enable_child_window_dpi_message(window_handle);

    HDC hNewBufferDC = lv_win32_create_frame_buffer(
        window_handle,
        parameter->hor_res,
        parameter->ver_res,
        &g_pixel_buffer,
        &g_pixel_buffer_size);

    DeleteDC(g_buffer_dc_handle);
    g_buffer_dc_handle = hNewBufferDC;

    ShowWindow(window_handle, parameter->show_window_mode);
    UpdateWindow(window_handle);
    g_window_handle = window_handle;

    SetEvent(parameter->window_mutex);

    MSG message;
    while (GetMessageW(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    lv_win32_quit_signal = true;

    return 0;
}

#endif /*USE_WIN32DRV*/
