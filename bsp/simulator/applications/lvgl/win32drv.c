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
#include <malloc.h>
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

static void lv_win32_pointer_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data);

static void lv_win32_keypad_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data);

static void lv_win32_encoder_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data);

static lv_win32_window_context_t* lv_win32_get_display_context(
    lv_disp_t* display);

static LRESULT CALLBACK lv_win32_window_message_callback(
    HWND   hWnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam);

static unsigned int __stdcall lv_win32_window_thread_entrypoint(
    void* raw_parameter);

static void lv_win32_push_key_to_keyboard_queue(
    lv_win32_window_context_t* context,
    uint32_t key,
    lv_indev_state_t state)
{
    lv_win32_keyboard_queue_item_t* current =
        (lv_win32_keyboard_queue_item_t*)(_aligned_malloc(
            sizeof(lv_win32_keyboard_queue_item_t),
            MEMORY_ALLOCATION_ALIGNMENT));
    if (current)
    {
        current->key = key;
        current->state = state;
        InterlockedPushEntrySList(
            context->keyboard_queue,
            &current->ItemEntry);
    }
}

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

EXTERN_C lv_win32_window_context_t* lv_win32_get_window_context(
    HWND window_handle)
{
    return (lv_win32_window_context_t*)(
        GetPropW(window_handle, L"LVGL.SimulatorWindow.WindowContext"));
}

EXTERN_C bool lv_win32_init_window_class()
{
    WNDCLASSEXW window_class;
    window_class.cbSize = sizeof(WNDCLASSEXW);
    window_class.style = 0;
    window_class.lpfnWndProc = lv_win32_window_message_callback;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = NULL;
    window_class.hIcon = NULL;
    window_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = LVGL_SIMULATOR_WINDOW_CLASS;
    window_class.hIconSm = NULL;
    return RegisterClassExW(&window_class);
}

EXTERN_C HWND lv_win32_create_display_window(
    const wchar_t* window_title,
    lv_coord_t hor_res,
    lv_coord_t ver_res,
    HINSTANCE instance_handle,
    HICON icon_handle,
    int show_window_mode)
{
    HWND display_window_handle = CreateWindowExW(
        WINDOW_EX_STYLE,
        LVGL_SIMULATOR_WINDOW_CLASS,
        window_title,
        WINDOW_STYLE,
        CW_USEDEFAULT,
        0,
        hor_res,
        ver_res,
        NULL,
        NULL,
        instance_handle,
        NULL);
    if (display_window_handle)
    {
        SendMessageW(
            display_window_handle,
            WM_SETICON,
            TRUE,
            (LPARAM)icon_handle);
        SendMessageW(
            display_window_handle,
            WM_SETICON,
            FALSE,
            (LPARAM)icon_handle);

        ShowWindow(display_window_handle, show_window_mode);
        UpdateWindow(display_window_handle);
    }

    return display_window_handle;
}

EXTERN_C bool lv_win32_init(
    HINSTANCE instance_handle,
    int show_window_mode,
    lv_coord_t hor_res,
    lv_coord_t ver_res,
    HICON icon_handle)
{
    if (!lv_win32_init_window_class())
    {
        return false;
    }

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

    lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
        lv_win32_get_window_context(g_window_handle));
    if (!context)
    {
        return false;
    }

    lv_win32_pointer_device_object = context->mouse_device_object;
    lv_win32_keypad_device_object = context->keyboard_device_object;
    lv_win32_encoder_device_object = context->mousewheel_device_object;

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
    lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
        lv_win32_get_window_context((HWND)disp_drv->user_data));
    if (context)
    {
        if (lv_disp_flush_is_last(disp_drv))
        {
#if (LV_COLOR_DEPTH == 32) || \
    (LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0) || \
    (LV_COLOR_DEPTH == 8) || \
    (LV_COLOR_DEPTH == 1)
            UNREFERENCED_PARAMETER(color_p);
#elif (LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0)
            SIZE_T count = context->display_framebuffer_size / sizeof(UINT16);
            PUINT16 source = (PUINT16)color_p;
            PUINT16 destination = (PUINT16)context->display_framebuffer_base;
            for (SIZE_T i = 0; i < count; ++i)
            {
                UINT16 current = *source;
                *destination = (LOBYTE(current) << 8) | HIBYTE(current);

                ++source;
                ++destination;
            }
#else
            uint32_t* destination = context->display_framebuffer_base;

            for (int y = area->y1; y <= area->y2; ++y)
            {
                for (int x = area->x1; x <= area->x2; ++x)
                {
                    destination[y * disp_drv->hor_res + x] =
                        lv_color_to32(*color_p);
                    color_p++;
                }
            }
#endif

            InvalidateRect(disp_drv->user_data, NULL, FALSE);
        }
    }

    lv_disp_flush_ready(disp_drv);
}

static void lv_win32_pointer_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data)
{
    lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
        lv_win32_get_display_context(indev_drv->disp));
    if (!context)
    {
        return;
    }

    data->state = context->mouse_state;
    data->point = context->mouse_point;
}

static void lv_win32_keypad_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data)
{
    lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
        lv_win32_get_display_context(indev_drv->disp));
    if (!context)
    {
        return;
    }

    EnterCriticalSection(&context->keyboard_mutex);

    lv_win32_keyboard_queue_item_t* current =
        (lv_win32_keyboard_queue_item_t*)(InterlockedPopEntrySList(
            context->keyboard_queue));
    if (current)
    {
        data->key = current->key;
        data->state = current->state;

        _aligned_free(current);

        data->continue_reading = true;
    }

    LeaveCriticalSection(&context->keyboard_mutex);
}

static void lv_win32_encoder_driver_read_callback(
    lv_indev_drv_t* indev_drv,
    lv_indev_data_t* data)
{
    lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
        lv_win32_get_display_context(indev_drv->disp));
    if (!context)
    {
        return;
    }

    data->state = context->mousewheel_state;
    data->enc_diff = context->mousewheel_enc_diff;
    context->mousewheel_enc_diff = 0;
}

static lv_win32_window_context_t* lv_win32_get_display_context(
    lv_disp_t* display)
{
    if (display)
    {
        return lv_win32_get_window_context((HWND)display->driver->user_data);
    }

    return NULL;
}

static LRESULT CALLBACK lv_win32_window_message_callback(
    HWND   hWnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        // Note: Return -1 directly because WM_DESTROY message will be sent
        // when destroy the window automatically. We free the resource when
        // processing the WM_DESTROY message of this window.

        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            malloc(sizeof(lv_win32_window_context_t)));
        if (!context)
        {
            return -1;
        }

        RECT request_content_size;
        GetWindowRect(hWnd, &request_content_size);

        context->display_hor_res =
            request_content_size.right - request_content_size.left;
        context->display_ver_res =
            request_content_size.bottom - request_content_size.top;
        context->display_dpi = lv_win32_get_dpi_for_window(hWnd);
        context->display_framebuffer_context_handle =
            lv_win32_create_frame_buffer(
                hWnd,
                context->display_hor_res,
                context->display_ver_res,
                &context->display_framebuffer_base,
                &context->display_framebuffer_size);
#if (LV_COLOR_DEPTH == 32) || \
    (LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0) || \
    (LV_COLOR_DEPTH == 8) || \
    (LV_COLOR_DEPTH == 1)
        lv_disp_draw_buf_init(
            &context->display_buffer,
            (lv_color_t*)context->display_framebuffer_base,
            NULL,
            context->display_hor_res * context->display_ver_res);
#else
        size_t draw_buffer_size = sizeof(lv_color_t);
        draw_buffer_size *= context->display_hor_res;
        draw_buffer_size *= context->display_ver_res;
        lv_disp_draw_buf_init(
            &context->display_buffer,
            (lv_color_t*)malloc(draw_buffer_size),
            NULL,
            context->display_hor_res * context->display_ver_res);
#endif
        lv_disp_drv_init(&context->display_driver);
        context->display_driver.hor_res = context->display_hor_res;
        context->display_driver.ver_res = context->display_ver_res;
        context->display_driver.flush_cb =
            lv_win32_display_driver_flush_callback;
        context->display_driver.draw_buf = &context->display_buffer;
        context->display_driver.direct_mode = 1;
        context->display_driver.user_data = hWnd;
        context->display_device_object =
            lv_disp_drv_register(&context->display_driver);
        if (!context->display_device_object)
        {
            return -1;
        }

        context->mouse_state = LV_INDEV_STATE_REL;
        context->mouse_point.x = 0;
        context->mouse_point.y = 0;
        lv_indev_drv_init(&context->mouse_driver);
        context->mouse_driver.type = LV_INDEV_TYPE_POINTER;
        context->mouse_driver.disp = context->display_device_object;
        context->mouse_driver.read_cb =
            lv_win32_pointer_driver_read_callback;
        context->mouse_device_object =
            lv_indev_drv_register(&context->mouse_driver);
        if (!context->mouse_device_object)
        {
            return -1;
        }

        context->mousewheel_state = LV_INDEV_STATE_REL;
        context->mousewheel_enc_diff = 0;
        lv_indev_drv_init(&context->mousewheel_driver);
        context->mousewheel_driver.type = LV_INDEV_TYPE_ENCODER;
        context->mousewheel_driver.disp = context->display_device_object;
        context->mousewheel_driver.read_cb =
            lv_win32_encoder_driver_read_callback;
        context->mousewheel_device_object =
            lv_indev_drv_register(&context->mousewheel_driver);
        if (!context->mousewheel_device_object)
        {
            return -1;
        }

        InitializeCriticalSection(&context->keyboard_mutex);
        context->keyboard_queue = _aligned_malloc(
            sizeof(SLIST_HEADER),
            MEMORY_ALLOCATION_ALIGNMENT);
        if (!context->keyboard_queue)
        {
            return -1;
        }
        InitializeSListHead(context->keyboard_queue);
        context->keyboard_utf16_high_surrogate = 0;
        context->keyboard_utf16_low_surrogate = 0;
        lv_indev_drv_init(&context->keyboard_driver);
        context->keyboard_driver.type = LV_INDEV_TYPE_KEYPAD;
        context->keyboard_driver.disp = context->display_device_object;
        context->keyboard_driver.read_cb =
            lv_win32_keypad_driver_read_callback;
        context->keyboard_device_object =
            lv_indev_drv_register(&context->keyboard_driver);
        if (!context->keyboard_device_object)
        {
            return -1;
        }

        if (!SetPropW(
            hWnd,
            L"LVGL.SimulatorWindow.WindowContext",
            (HANDLE)(context)))
        {
            return -1;
        }

        RECT calculated_window_size;

        calculated_window_size.left = 0;
        calculated_window_size.right = MulDiv(
            context->display_hor_res * WIN32DRV_MONITOR_ZOOM,
            context->display_dpi,
            USER_DEFAULT_SCREEN_DPI);
        calculated_window_size.top = 0;
        calculated_window_size.bottom = MulDiv(
            context->display_ver_res * WIN32DRV_MONITOR_ZOOM,
            context->display_dpi,
            USER_DEFAULT_SCREEN_DPI);

        AdjustWindowRectEx(
            &calculated_window_size,
            WINDOW_STYLE,
            FALSE,
            WINDOW_EX_STYLE);
        OffsetRect(
            &calculated_window_size,
            -calculated_window_size.left,
            -calculated_window_size.top);

        SetWindowPos(
            hWnd,
            NULL,
            0,
            0,
            calculated_window_size.right,
            calculated_window_size.bottom,
            SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);

        lv_win32_register_touch_window(hWnd, 0);

        lv_win32_enable_child_window_dpi_message(hWnd);

        break;
    }
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    {
        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            lv_win32_get_window_context(hWnd));
        if (!context)
        {
            return 0;
        }

        context->mouse_point.x = MulDiv(
            GET_X_LPARAM(lParam),
            USER_DEFAULT_SCREEN_DPI,
            WIN32DRV_MONITOR_ZOOM * context->display_dpi);
        context->mouse_point.y = MulDiv(
            GET_Y_LPARAM(lParam),
            USER_DEFAULT_SCREEN_DPI,
            WIN32DRV_MONITOR_ZOOM * context->display_dpi);
        if (context->mouse_point.x < 0)
        {
            context->mouse_point.x = 0;
        }
        if (context->mouse_point.x > context->display_hor_res - 1)
        {
            context->mouse_point.x = context->display_hor_res - 1;
        }
        if (context->mouse_point.y < 0)
        {
            context->mouse_point.y = 0;
        }
        if (context->mouse_point.y > context->display_ver_res - 1)
        {
            context->mouse_point.y = context->display_ver_res - 1;
        }

        if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP)
        {
            context->mouse_state = (
                uMsg == WM_LBUTTONDOWN
                ? LV_INDEV_STATE_PR
                : LV_INDEV_STATE_REL);
        }
        else if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP)
        {
            context->mousewheel_state = (
                uMsg == WM_MBUTTONDOWN
                ? LV_INDEV_STATE_PR
                : LV_INDEV_STATE_REL);
        }
        return 0;
    }
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            lv_win32_get_window_context(hWnd));
        if (context)
        {
            EnterCriticalSection(&context->keyboard_mutex);

            bool skip_translation = false;
            uint32_t translated_key = 0;

            switch (wParam)
            {
            case VK_UP:
                translated_key = LV_KEY_UP;
                break;
            case VK_DOWN:
                translated_key = LV_KEY_DOWN;
                break;
            case VK_LEFT:
                translated_key = LV_KEY_LEFT;
                break;
            case VK_RIGHT:
                translated_key = LV_KEY_RIGHT;
                break;
            case VK_ESCAPE:
                translated_key = LV_KEY_ESC;
                break;
            case VK_DELETE:
                translated_key = LV_KEY_DEL;
                break;
            case VK_BACK:
                translated_key = LV_KEY_BACKSPACE;
                break;
            case VK_RETURN:
                translated_key = LV_KEY_ENTER;
                break;
            case VK_TAB:
            case VK_NEXT:
                translated_key = LV_KEY_NEXT;
                break;
            case VK_PRIOR:
                translated_key = LV_KEY_PREV;
                break;
            case VK_HOME:
                translated_key = LV_KEY_HOME;
                break;
            case VK_END:
                translated_key = LV_KEY_END;
                break;
            default:
                skip_translation = true;
                break;
            }

            if (!skip_translation)
            {
                lv_win32_push_key_to_keyboard_queue(
                    context,
                    translated_key,
                    ((uMsg == WM_KEYUP)
                        ? LV_INDEV_STATE_REL
                        : LV_INDEV_STATE_PR));
            }

            LeaveCriticalSection(&context->keyboard_mutex);
        }

        break;
    }
    case WM_CHAR:
    {
        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            lv_win32_get_window_context(hWnd));
        if (context)
        {
            EnterCriticalSection(&context->keyboard_mutex);

            uint16_t raw_code_point = (uint16_t)(wParam);

            if (raw_code_point >= 0x20 && raw_code_point != 0x7F)
            {
                if (IS_HIGH_SURROGATE(raw_code_point))
                {
                    context->keyboard_utf16_high_surrogate = raw_code_point;
                }
                else if (IS_LOW_SURROGATE(raw_code_point))
                {
                    context->keyboard_utf16_low_surrogate = raw_code_point;
                }

                uint32_t code_point = raw_code_point;

                if (context->keyboard_utf16_high_surrogate &&
                    context->keyboard_utf16_low_surrogate)
                {
                    uint16_t high_surrogate =
                        context->keyboard_utf16_high_surrogate;
                    uint16_t low_surrogate =
                        context->keyboard_utf16_low_surrogate;

                    code_point = (low_surrogate & 0x03FF);
                    code_point += (((high_surrogate & 0x03FF) + 0x40) << 10);

                    context->keyboard_utf16_high_surrogate = 0;
                    context->keyboard_utf16_low_surrogate = 0;
                }

                uint32_t lvgl_code_point =
                    _lv_txt_unicode_to_encoded(code_point);

                lv_win32_push_key_to_keyboard_queue(
                    context,
                    lvgl_code_point,
                    LV_INDEV_STATE_PR);
                lv_win32_push_key_to_keyboard_queue(
                    context,
                    lvgl_code_point,
                    LV_INDEV_STATE_REL);
            }

            LeaveCriticalSection(&context->keyboard_mutex);
        }

        break;
    }
    case WM_MOUSEWHEEL:
    {
        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            lv_win32_get_window_context(hWnd));
        if (context)
        {
            context->mousewheel_enc_diff =
                -(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
        }

        break;
    }
    case WM_TOUCH:
    {
        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            lv_win32_get_window_context(hWnd));
        if (context)
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

                        context->mouse_point.x = MulDiv(
                            Point.x,
                            USER_DEFAULT_SCREEN_DPI,
                            WIN32DRV_MONITOR_ZOOM * context->display_dpi);
                        context->mouse_point.y = MulDiv(
                            Point.y,
                            USER_DEFAULT_SCREEN_DPI,
                            WIN32DRV_MONITOR_ZOOM * context->display_dpi);

                        DWORD MousePressedMask =
                            TOUCHEVENTF_MOVE | TOUCHEVENTF_DOWN;

                        context->mouse_state = (
                            pInputs[i].dwFlags & MousePressedMask
                            ? LV_INDEV_STATE_PR
                            : LV_INDEV_STATE_REL);
                    }
                }

                free(pInputs);
            }

            lv_win32_close_touch_input_handle(hTouchInput);
        }

        break;
    }
    case WM_DPICHANGED:
    {
        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            lv_win32_get_window_context(hWnd));
        if (context)
        {
            context->display_dpi = HIWORD(wParam);

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
                context->display_hor_res * WIN32DRV_MONITOR_ZOOM,
                context->display_dpi,
                USER_DEFAULT_SCREEN_DPI);
            int WindowHeight = MulDiv(
                context->display_ver_res * WIN32DRV_MONITOR_ZOOM,
                context->display_dpi,
                USER_DEFAULT_SCREEN_DPI);

            SetWindowPos(
                hWnd,
                NULL,
                SuggestedRect->left,
                SuggestedRect->top,
                SuggestedRect->right + (WindowWidth - ClientRect.right),
                SuggestedRect->bottom + (WindowHeight - ClientRect.bottom),
                SWP_NOZORDER | SWP_NOACTIVATE);
        }

        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            lv_win32_get_window_context(hWnd));
        if (context)
        {
            if (context->display_framebuffer_context_handle)
            {
                SetStretchBltMode(hdc, HALFTONE);

                StretchBlt(
                    hdc,
                    ps.rcPaint.left,
                    ps.rcPaint.top,
                    ps.rcPaint.right - ps.rcPaint.left,
                    ps.rcPaint.bottom - ps.rcPaint.top,
                    context->display_framebuffer_context_handle,
                    0,
                    0,
                    MulDiv(
                        ps.rcPaint.right - ps.rcPaint.left,
                        USER_DEFAULT_SCREEN_DPI,
                        WIN32DRV_MONITOR_ZOOM * context->display_dpi),
                    MulDiv(
                        ps.rcPaint.bottom - ps.rcPaint.top,
                        USER_DEFAULT_SCREEN_DPI,
                        WIN32DRV_MONITOR_ZOOM * context->display_dpi),
                    SRCCOPY);
            }
        }

        EndPaint(hWnd, &ps);

        break;
    }
    case WM_DESTROY:
    {
        lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
            RemovePropW(hWnd, L"LVGL.SimulatorWindow.WindowContext"));
        if (context)
        {
            lv_disp_t* display_device_object = context->display_device_object;
            context->display_device_object = NULL;
            lv_disp_remove(display_device_object);
#if (LV_COLOR_DEPTH == 32) || \
    (LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0) || \
    (LV_COLOR_DEPTH == 8) || \
    (LV_COLOR_DEPTH == 1)
#else
            free(context->display_buffer.buf1);
#endif
            DeleteDC(context->display_framebuffer_context_handle);

            lv_indev_t* mouse_device_object =
                context->mouse_device_object;
            context->mouse_device_object = NULL;
            lv_indev_delete(mouse_device_object);

            lv_indev_t* mousewheel_device_object =
                context->mousewheel_device_object;
            context->mousewheel_device_object = NULL;
            lv_indev_delete(mousewheel_device_object);

            lv_indev_t* keyboard_device_object =
                context->keyboard_device_object;
            context->keyboard_device_object = NULL;
            lv_indev_delete(keyboard_device_object);
            do
            {
                PSLIST_ENTRY current = InterlockedPopEntrySList(
                    context->keyboard_queue);
                if (!current)
                {
                    _aligned_free(context->keyboard_queue);
                    context->keyboard_queue = NULL;
                    break;
                }

                _aligned_free(current);

            } while (true);
            DeleteCriticalSection(&context->keyboard_mutex);

            free(context);
        }

        PostQuitMessage(0);

        break;
    }
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

    g_window_handle = lv_win32_create_display_window(
        L"LVGL Simulator for Windows Desktop (Display 1)",
        parameter->hor_res,
        parameter->ver_res,
        parameter->instance_handle,
        parameter->icon_handle,
        parameter->show_window_mode);
    if (!g_window_handle)
    {
        return 0;
    }

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
