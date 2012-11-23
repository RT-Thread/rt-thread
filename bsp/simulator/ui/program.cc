#include <rtthread.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/list_view.h>
#include <rtgui/rtgui_xml.h>
#include <rtgui/widgets/panel.h>

#ifdef _WIN32_NATIVE
#include <io.h>
#include <dirent.h>
#include <sys/stat.h>
#define PATH_SEPARATOR      '\\'
#else
#include <dfs_posix.h>
#define PATH_SEPARATOR      '/'
#endif

#define APP_PATH            "/programs"
#define ITEM_MAX            10

static struct rtgui_list_item *items = RT_NULL;
static rtgui_list_view_t* _view = RT_NULL;
static int pos = -1;

typedef enum
{
    IDLE,
    READ_NAME,
    READ_ICON,
    READ_AUTHOR,
    READ_LICENSE,
}XML_STATUS;

static int xml_event_handler(rt_uint8_t event, const char* text, rt_size_t len, void* user)
{
    static XML_STATUS status = IDLE;
    char fn[64];

    if(event == EVENT_START)
    {
        if(strcmp(text, "name") == 0)
            status = READ_NAME;
        else if(strcmp(text, "image") == 0)
            status = READ_ICON;
        else if(strcmp(text, "author") == 0)
            status = READ_AUTHOR;
        else if(strcmp(text, "license") == 0)
            status = READ_LICENSE;
    }
    else if(event == EVENT_TEXT)
    {
        switch(status)
        {
        case READ_NAME:    
            items[++pos].name = rt_strdup(text);
            items[pos].parameter = items[pos].name;
            break;
        case READ_ICON:
            rt_snprintf(fn, sizeof(fn), "%s/%s", APP_PATH, text);
            items[pos].image = rtgui_image_create(fn, RT_TRUE);
            if(items[pos].image == RT_NULL) rt_kprintf("image create failed\n");
            break;
        case READ_AUTHOR:
            break;
        case READ_LICENSE:
            break;
        }
        status = IDLE;
    }
        
    return 1;    
}

static int xml_load_items(const char* filename)
{    
    struct rtgui_filerw* filerw;
    char buffer[512];
    rtgui_xml_t *xml;
    int length;

    /* create filerw context */
    filerw = rtgui_filerw_create_file(filename, "rb");
    if (filerw == RT_NULL) 
    {
        rt_kprintf("read file fail %s\n", filename);
        return 0;
    }

    length = rtgui_filerw_read(filerw, buffer, 512, 1);
    if(length <= 0)
    {
        rt_kprintf("read fail\n");
        rtgui_filerw_close(filerw);        
        return 0;
    }
    
    xml = rtgui_xml_create(512, xml_event_handler, RT_NULL);
    if (xml != RT_NULL)    
    {        
        rtgui_xml_parse(xml, buffer, length);
        rtgui_xml_destroy(xml);    
    }

    rtgui_filerw_close(filerw);        
    return 0;
}

static void exec_app(rtgui_widget_t* widget, void* parameter)
{
    char path[64];
    rt_module_t module;

    RT_ASSERT(parameter != RT_NULL);

    rt_snprintf(path, sizeof(path), "%s/%s/%s.mo", APP_PATH, 
        (char*)parameter, (char*)parameter);
    
#ifndef _WIN32
    module = rt_module_find((const char*)parameter);
    if(module == RT_NULL)
        rt_module_open(path);
    else
    {
        struct rtgui_app* app;
        RT_ASSERT(module->module_thread);
        app = (struct rtgui_app*)(module->module_thread->user_data);
        
        if(app != RT_NULL) rtgui_app_activate(app);
        else rt_kprintf("application is null\n");
    }
#endif
}

static void scan_app_dir(const char* path)
{
    DIR* dir;
    struct dirent* entry;
    char fn[32];

    dir = opendir(path);
    if (dir == RT_NULL)
    {
        rt_kprintf("open directory %s failed\n", path);
        return;
    }

    do
    {
        entry = readdir(dir);
        if (entry != RT_NULL)
        {
            if(entry->d_type == DFS_DT_REG) break;
            rt_sprintf(fn, "%s/%s/%s.xml", path, entry->d_name, entry->d_name);
            xml_load_items(fn);
        }
    } while(entry != RT_NULL);

    /* close directory */
    closedir(dir);
}

struct rtgui_panel* program_create(struct rtgui_panel* panel)
{
    int i = 0;
    struct rtgui_rect rect;

    RT_ASSERT(panel != RT_NULL);
    rtgui_widget_get_extent(RTGUI_WIDGET(panel), &rect);

    items = (struct rtgui_list_item *) rtgui_malloc((ITEM_MAX) * sizeof(struct rtgui_list_item));
    for(i=0; i< ITEM_MAX; i++) items[i].action = exec_app;

    /* create application list */
    rtgui_rect_inflate(&rect, -15);

    scan_app_dir(APP_PATH);
    if(pos >= 0) 
    {
        _view = rtgui_list_view_create(items, pos + 1, &rect, RTGUI_LIST_VIEW_ICON);
        rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(_view));
    }        

    return RTGUI_PANEL(panel);
}

