#include <rtgui/rtgui_object.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/list.h>
#include <rtgui/widgets/view.h>

/* image for file and folder */
rtgui_image_t *file_image, *folder_image;

static void _filelist_view_constructor(filelist_view *view)
{
	/* default rect */
	struct rtgui_rect rect = {0, 0, 200, 200};

	/* set default widget rect and set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(view),filelist_view_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(view), &rect);

	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(list)) = RTGUI_RGB(212, 208, 200);

	view->count = 0;
	view->current_directory = RT_NULL;
	view->pattern = RT_NULL;
	rtgui_list_init(&view->list);
}

rtgui_type_t *filelist_view_type_get(void)
{
	static rtgui_type_t *filelist_view_type = RT_NULL;

	if (!filelist_view_type)
	{
		filelist_view_type = rtgui_type_create("flview", RTGUI_VIEW_TYPE,
			sizeof(filelist_view_t), RTGUI_CONSTRUCTOR(_filelist_view_constructor), RT_NULL);
	}

	return filelist_view_type;
}

rt_bool_t filelist_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct filelist_view* view = RT_NULL;

	view = FILELIST_VIEW(widget);
	switch (event.type)
	{
	case RTGUI_EVENT_PAINT:
		break;

    case RTGUI_EVENT_RESIZE:
        {
            /* recalculate page items */
        }
        break;

    case RTGUI_EVENT_KBD:
        {
            struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
            if (ekbd->type == RTGUI_KEYDOWN)
            {
                switch (ekbd->key)
                {
                case RTGUIK_UP:
                    break;

                case RTGUIK_DOWN:
                    break;

                default:
                    break;
                }
            }
        }
        break;
	}

    /* use view event handler */
    return rtgui_view_event_handler(widget, event);
}

filelist_view_t* filelist_view_create(const char* directory, const char* pattern)
{
	struct filelist_view* view = RT_NULL;

	view = (struct filelist_view*) rtgui_widget_create(FILELIST_VIEW_TYPE);
	if (view != RT_NULL)
	{
	    view->pattern = rt_strdup(pattern);
	    filelist_view_set_directory(view, directory);
	}

	return list;
}

void filelist_view_destroy(filelist_view_t* view)
{
    /* delete all file items */
    filelist_view_clear(view);

    /* destroy view */
	rtgui_widget_destroy(RTGUI_WIDGET(view));
}

/* clear all file items */
void filelist_view_clear(filelist_view_t* view)
{
    struct rtgui_list_node* node;
    struct file_item* item;

    while (view->list.next != RT_NULL)
    {
    	node = view->list.next;
    	rtgui_list_remove(&view->list, node);

    	item = rtgui_list_entry(node, struct file_item, list);
    	rtgui_free(item->name);
    	rtgui_free(item);
    }
}

void filelist_view_set_directory(filelist_view_t* view, const char* directory)
{
    rt_uint8_t fullpath[256];
    struct file_item *item;

    RT_ASSERT(view != RT_NULL);

    /* clear file items firstly */
    filelist_view_clear(view);
    if (directory != RT_NULL)
    {
        DIR* dir;
        dir = opendir(directory);
        if (dir != RT_NULL)
        {
            struct dfs_dirent* dirent;
            struct dfs_stat s;

            do
            {
                dirent = readdir(dir);
                if (dirent == RT_NULL) break;
                if (fnmatch(dirent->d_name, view->pattern, FNM_FILE_NAME) != 0) continue;

                item = (struct file_item*) rt_malloc (sizeof(struct file_item));
                if (item == RT_NULL) break;

                rt_memset(&s, 0, sizeof(struct dfs_stat));

                /* build full path for the file */
                rt_sprintf(fullpath, "%s/%s", directory, dirent->d_name);

                item->name = strdup(direct->d_name);
                rtgui_list_init(&item->list);
                stat(fullpath, &s);
                if ( s.st_mode & DFS_S_IFDIR )
                {
                    item->type = FITEM_DIR;
                    item->size = 0;
                }
                else
                {
                    item->type = FITEM_FILE;
                    item->size = s.st_size;
                }

                rtgui_list_append(&view->list, &item->list);
                view->count ++;
            } while (dirent != RT_NULL);

            closedir(dir);
        }
    }

    if (view->count > 0)
    {
        /* select first one */
        view->selected = rtgui_list_entry(view->list.next,
            struct file_item, list);
    }
    else view->selected = RT_NULL;

    /* update view */
    rtgui_widget_update(RTGUI_WIDGET(view));
}
