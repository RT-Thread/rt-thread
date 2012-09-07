/*
 * File      : filelist_view.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-06     Bernard      first version
 */

#include <rtgui/rtgui_object.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_app.h>

#include <rtgui/list.h>
#include <rtgui/image.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/filelist_view.h>
#include <rtgui/widgets/listbox.h>
#include <rtgui/widgets/window.h>

#if defined(RTGUI_USING_DFS_FILERW)
#ifdef _WIN32
#include <io.h>
#include <dirent.h>
#include <sys/stat.h>
#define PATH_SEPARATOR		'\\'
#else
#include <dfs_posix.h>
#define PATH_SEPARATOR		'/'
#endif

#include <string.h>

#define RTGUI_FILELIST_MARGIN		5

const static char * file_xpm[] = {
"16 16 21 1",
" 	c None",
".	c #999999",
"+	c #818181",
"@	c #FFFFFF",
"#	c #ECECEC",
"$	c #EAEAEA",
"%	c #EBEBEB",
"&	c #EDEDED",
"*	c #F0F0F0",
"=	c #C4C4C4",
"-	c #C5C5C5",
";	c #C6C6C6",
">	c #C7C7C7",
",	c #EEEEEE",
"'	c #EDEDE5",
")	c #EDEDE6",
"!	c #EFEFEF",
"~	c #C8C8C8",
"{	c #F1F1F1",
"]	c #F2F2F2",
"^	c #959595",
".++++++++++++   ",
"+@@@@@@@@@@@@+  ",
"+@#$$%%%##&*@+  ",
"+@$=--;;;;>*@+  ",
"+@$%%###&&,*@+  ",
"+@%-;;;;;;>*@+  ",
"+@%%##&&'#,*@+  ",
"+@%;;;;,,),*@+  ",
"+@##&&,,!!!*@+  ",
"+@#;;;>>~~~*@+  ",
"+@#&,,!!*{{{@+  ",
"+@&;>>~~~{{]@+  ",
"+@&&,!!**{]]@+  ",
"+@@@@@@@@@@@@+  ",
"^++++++++++++^  ",
"                "};

const static char * folder_xpm[] = {
"16 16 121 2",
"  	c None",
". 	c #D9B434",
"+ 	c #E1C25E",
"@ 	c #E2C360",
"# 	c #E2C35F",
"$ 	c #DBB63C",
"% 	c #DAB336",
"& 	c #FEFEFD",
"* 	c #FFFFFE",
"= 	c #FFFEFE",
"- 	c #FFFEFD",
"; 	c #FBF7EA",
"> 	c #E4C76B",
", 	c #E3C76B",
"' 	c #E6CD79",
") 	c #E5CA74",
"! 	c #DAAF35",
"~ 	c #FEFCF7",
"{ 	c #F8E48E",
"] 	c #F5DE91",
"^ 	c #F5E09F",
"/ 	c #F6E1AC",
"( 	c #FEFBEF",
"_ 	c #FEFDF4",
": 	c #FEFCF3",
"< 	c #FEFCF1",
"[ 	c #FEFBEE",
"} 	c #FFFDFA",
"| 	c #DAAF36",
"1 	c #DAAA36",
"2 	c #FDFAF1",
"3 	c #F5DE94",
"4 	c #F4DC93",
"5 	c #F2D581",
"6 	c #EDCA6A",
"7 	c #EACB6C",
"8 	c #EFD385",
"9 	c #EFD280",
"0 	c #EFD07A",
"a 	c #EECF76",
"b 	c #EECF72",
"c 	c #FBF7E9",
"d 	c #DAAE34",
"e 	c #DAAB35",
"f 	c #FBF6E8",
"g 	c #EFD494",
"h 	c #EECE88",
"i 	c #E9C173",
"j 	c #F6E9C9",
"k 	c #FEFCF2",
"l 	c #FEFCF0",
"m 	c #DAAB36",
"n 	c #DAA637",
"o 	c #FFFDF8",
"p 	c #FFFDF6",
"q 	c #FFFCF5",
"r 	c #FCF6D8",
"s 	c #F8E694",
"t 	c #F7E385",
"u 	c #F6DF76",
"v 	c #F5DB68",
"w 	c #F4D85C",
"x 	c #FCF4D7",
"y 	c #DAA435",
"z 	c #DAA136",
"A 	c #FEFCF6",
"B 	c #FCF2C8",
"C 	c #FBEFB9",
"D 	c #FAECAC",
"E 	c #F9E89C",
"F 	c #F7E38B",
"G 	c #F6E07C",
"H 	c #F6DC6C",
"I 	c #F5D95D",
"J 	c #F4D64F",
"K 	c #F3D344",
"L 	c #FCF3D0",
"M 	c #DA9F35",
"N 	c #DA9A36",
"O 	c #FDFAF2",
"P 	c #FAEDB3",
"Q 	c #F9E9A4",
"R 	c #F8E695",
"S 	c #F7E285",
"T 	c #F6DE76",
"U 	c #F5DB65",
"V 	c #F4D757",
"W 	c #F3D449",
"X 	c #F2D13B",
"Y 	c #F1CE30",
"Z 	c #FBF2CC",
"` 	c #DA9835",
" .	c #DA9435",
"..	c #FEFAEF",
"+.	c #F9E9A1",
"@.	c #F8E591",
"#.	c #F7E181",
"$.	c #F6DE72",
"%.	c #F5DA63",
"&.	c #F4D754",
"*.	c #F3D347",
"=.	c #F2D039",
"-.	c #F1CD2E",
";.	c #F0CB26",
">.	c #FBF2CA",
",.	c #D98E33",
"'.	c #FAF0DC",
").	c #F4DDA7",
"!.	c #F4DB9E",
"~.	c #F3DA96",
"{.	c #F3D88E",
"].	c #F3D786",
"^.	c #F2D47F",
"/.	c #F2D379",
"(.	c #F1D272",
"_.	c #F1D06C",
":.	c #F1CF69",
"<.	c #F8EAC2",
"[.	c #D8882D",
"}.	c #D8872D",
"|.	c #D8862C",
"                                ",
"                                ",
"                                ",
"  . + @ @ @ # $                 ",
"  % & * = - * ; > , , , ' )     ",
"  ! ~ { ] ^ / ( _ : < ( [ } |   ",
"  1 2 3 4 5 6 7 8 9 0 a b c d   ",
"  e f g h i j k : k l ( [ * m   ",
"  n * o p q : r s t u v w x y   ",
"  z A B C D E F G H I J K L M   ",
"  N O P Q R S T U V W X Y Z `   ",
"   ...+.@.#.$.%.&.*.=.-.;.>. .  ",
"  ,.'.).!.~.{.].^./.(._.:.<.,.  ",
"    [.}.[.[.[.[.[.[.[.[.}.[.|.  ",
"                                ",
"                                "};

/* image for file and folder */
static rtgui_image_t *file_image, *folder_image;
static struct rtgui_listbox_item items[] =
{
#ifdef RTGUI_USING_FONTHZ
	{"ºþôË`Á§˜Ë", RT_NULL},
	{"í¥Œv`Á§˜Ë", RT_NULL},
	{"ØXµÌ", RT_NULL}
#else
	{"Open folder", RT_NULL},
	{"Select folder", RT_NULL},
	{"Cancel", RT_NULL}
#endif
};
static void rtgui_filelist_view_clear(rtgui_filelist_view_t* view);

static rt_bool_t rtgui_filelist_view_on_folder_item(rtgui_object_t* object, struct rtgui_event* event)
{
	rtgui_win_t *menu;
	rtgui_listbox_t *listbox;
	rtgui_filelist_view_t *view;

	listbox = RTGUI_LISTBOX(object);
	menu = RTGUI_WIN(rtgui_widget_get_toplevel(RTGUI_WIDGET(object)));
	view = RTGUI_FILELIST_VIEW(menu->user_data);

	/* hide window */
	rtgui_win_hiden(menu);

	switch (listbox->current_item)
	{
	case 0:
		{
			char* dir_ptr;

			/* destroy menu window */
			rtgui_win_destroy(menu);

			dir_ptr = (char*) rtgui_malloc (256);
			rtgui_filelist_view_get_fullpath(view, dir_ptr, 256);
			rtgui_filelist_view_set_directory(view, dir_ptr);
			rtgui_free(dir_ptr);
		}
		break;
	case 1:
		/* destroy menu window */
		rtgui_win_destroy(menu);
		break;

	default:
		/* destroy menu window */
		rtgui_win_destroy(menu);
		break;
	}

	return RT_TRUE;
}

static rt_bool_t rtgui_filelist_view_on_menu_deactivate(rtgui_object_t* object, struct rtgui_event* event)
{
	rtgui_win_t *menu;
	menu = RTGUI_WIN(rtgui_widget_get_toplevel(RTGUI_WIDGET(object)));

	/* destroy menu window */
	rtgui_win_destroy(menu);

	return RT_TRUE;
}

static void rtgui_filelist_view_menu_pop(rtgui_widget_t *parent)
{
	rtgui_win_t *menu;
	rtgui_listbox_t *listbox;
	rtgui_rect_t screen, rect = {0, 0, 140, 85};

	rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &screen);
	rtgui_rect_moveto_align(&screen, &rect, RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);

	menu = rtgui_win_create(RTGUI_WIN(rtgui_widget_get_toplevel(parent)),
							"Folder Menu", &rect, RTGUI_WIN_STYLE_DEFAULT);
	if (menu != RT_NULL)
	{
		/* set user data on menu window */
		menu->user_data = (rt_uint32_t)parent;

		rtgui_win_set_ondeactivate(menu, rtgui_filelist_view_on_menu_deactivate);

		listbox = rtgui_listbox_create(items, sizeof(items)/sizeof(items[0]), &rect);
		rtgui_listbox_set_onitem(listbox, rtgui_filelist_view_on_folder_item);
		rtgui_container_add_child(RTGUI_CONTAINER(menu), RTGUI_WIDGET(listbox));
		rtgui_listbox_set_current_item(listbox, 0);
		rtgui_win_show(menu, RT_TRUE);        
	}
}

static void _rtgui_filelist_view_constructor(struct rtgui_filelist_view *view)
{
	/* default rect */
	struct rtgui_rect rect = {0, 0, 200, 200};

	/* set default widget rect and set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(view), rtgui_filelist_view_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(view), &rect);

	RTGUI_WIDGET(view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	view->current_item = 0;
	view->items_count = 0;
	view->page_items = 0;

	view->current_directory = RT_NULL;
	view->pattern = RT_NULL;
	RTGUI_WIDGET_BACKGROUND(view) = white;
	RTGUI_WIDGET_TEXTALIGN(view) = RTGUI_ALIGN_CENTER_VERTICAL;

	file_image = rtgui_image_create_from_mem("xpm",
		(rt_uint8_t*)file_xpm, sizeof(file_xpm), RT_TRUE);
	folder_image = rtgui_image_create_from_mem("xpm",
		(rt_uint8_t*)folder_xpm, sizeof(folder_xpm), RT_TRUE);
}

static void _rtgui_filelist_view_destructor(struct rtgui_filelist_view *view)
{
    /* delete all file items */
    rtgui_filelist_view_clear(view);
	/* delete current directory and pattern */
	if (view->current_directory != RT_NULL)
	{
		rt_free(view->current_directory); 
		view->current_directory = RT_NULL;
	}
	if (view->pattern != RT_NULL) 
	{
		rt_free(view->pattern); 
		view->pattern = RT_NULL;
	}

	/* delete image */
	rtgui_image_destroy(file_image);
	rtgui_image_destroy(folder_image);
}

DEFINE_CLASS_TYPE(filelist, "filelist",
	RTGUI_CONTAINER_TYPE,
	_rtgui_filelist_view_constructor,
	_rtgui_filelist_view_destructor,
	sizeof(struct rtgui_filelist_view));

void rtgui_filelist_view_ondraw(struct rtgui_filelist_view* view)
{
	struct rtgui_dc* dc;
	rt_uint16_t page_index, index;
	struct rtgui_file_item* item;
	struct rtgui_rect rect, item_rect, image_rect;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(view));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	/* get item base rect */
	item_rect = rect;
	item_rect.y1 += 1;
	item_rect.y2 = item_rect.y1 + (1 + rtgui_theme_get_selected_height());

	/* get image base rect */
	image_rect.x1 = RTGUI_FILELIST_MARGIN; image_rect.y1 = 0;
	image_rect.x2 = RTGUI_FILELIST_MARGIN + file_image->w; image_rect.y2 = file_image->h;
	rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);

	/* get current page */
	page_index = (view->current_item / view->page_items) * view->page_items;
	for (index = 0; index < view->page_items; index ++)
	{
		if (page_index + index >= view->items_count) break;

		item = &(view->items[page_index + index]);

		if (page_index + index == view->current_item)
		{
			rtgui_theme_draw_selected(dc, &item_rect);
		}
		else
		{
			/* draw background */
			rtgui_dc_fill_rect(dc, &item_rect);
		}

		/* draw item */
		if (item->type == RTGUI_FITEM_FILE)
			rtgui_image_blit(file_image, dc, &image_rect);
		else
			rtgui_image_blit(folder_image, dc, &image_rect);

        /* draw text */
		item_rect.x1 += RTGUI_FILELIST_MARGIN + file_image->w + 2;
		rtgui_dc_draw_text(dc, item->name, &item_rect);
		item_rect.x1 -= RTGUI_FILELIST_MARGIN + file_image->w + 2;

        /* move to next item position */
		item_rect.y1 += (rtgui_theme_get_selected_height() + 1);
		item_rect.y2 += (rtgui_theme_get_selected_height() + 1);

		image_rect.y1 += (rtgui_theme_get_selected_height() + 1);
		image_rect.y2 += (rtgui_theme_get_selected_height() + 1);
	}

	rtgui_dc_end_drawing(dc);
}

void rtgui_filelist_view_update_current(struct rtgui_filelist_view* view, rt_uint16_t old_item)
{
	struct rtgui_dc* dc;
	struct rtgui_file_item* item;
	rtgui_rect_t rect, item_rect, image_rect;

	if (old_item/view->page_items != view->current_item/view->page_items)
	{
		/* it's not a same page, update all */
		rtgui_widget_update(RTGUI_WIDGET(view));
		return;
	}

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(view));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);

	/* get old item rect */
	item_rect = rect;
	item_rect.y1 += 1;
	item_rect.y1 += (old_item % view->page_items) * (1 + rtgui_theme_get_selected_height());
	item_rect.y2 = item_rect.y1 + (1 + rtgui_theme_get_selected_height());

	/* get image rect */
	image_rect.x1 = RTGUI_FILELIST_MARGIN; image_rect.y1 = 0;
	image_rect.x2 = RTGUI_FILELIST_MARGIN + file_image->w; image_rect.y2 = file_image->h;
	rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);

	/* draw old item */
	rtgui_dc_fill_rect(dc, &item_rect);

	item = &(view->items[old_item]);
	if (item->type == RTGUI_FITEM_FILE) /* draw item image */
		rtgui_image_blit(file_image, dc, &image_rect);
	else
		rtgui_image_blit(folder_image, dc, &image_rect);

	item_rect.x1 += RTGUI_FILELIST_MARGIN + file_image->w + 2;
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	/* draw current item */
	item_rect = rect;
	item_rect.y1 += 1;
	item_rect.y1 += (view->current_item % view->page_items) * (1 + rtgui_theme_get_selected_height());
	item_rect.y2 = item_rect.y1 + (1 + rtgui_theme_get_selected_height());

	rtgui_theme_draw_selected(dc, &item_rect);

	/* get image base rect */
	image_rect.x1 = RTGUI_FILELIST_MARGIN; image_rect.y1 = 0;
	image_rect.x2 = RTGUI_FILELIST_MARGIN + file_image->w; image_rect.y2 = file_image->h;
	rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);

	item = &(view->items[view->current_item]);
	if (item->type == RTGUI_FITEM_FILE) /* draw item image */
		rtgui_image_blit(file_image, dc, &image_rect);
	else
		rtgui_image_blit(folder_image, dc, &image_rect);

	item_rect.x1 += RTGUI_FILELIST_MARGIN + file_image->w + 2;
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	rtgui_dc_end_drawing(dc);
}

static void rtgui_filelist_view_onenturn(struct rtgui_filelist_view* view)
{
	if (view->items[view->current_item].type == RTGUI_FITEM_DIR)
	{
		char new_path[64];

		if (strcmp(view->items[view->current_item].name, ".") == 0) return ;
		if (strcmp(view->items[view->current_item].name, "..") == 0)
		{
			char *ptr;
			ptr = strrchr(view->current_directory, PATH_SEPARATOR);

			if (ptr == RT_NULL) return ;
			if (ptr == &(view->current_directory[0]))
			{
				/* it's root directory */
				new_path[0] = PATH_SEPARATOR;
				new_path[1] = '\0';
			}
			else
			{
				strncpy(new_path, view->current_directory, ptr - view->current_directory + 1);
				new_path[ptr - view->current_directory] = '\0';
			}
		}
		else if (view->current_item == 0 &&
#ifdef _WIN32
			(view->current_directory[1] == ':') && (view->current_directory[2] == '\\')
#else
			(view->current_directory[0] == '/') && (view->current_directory[1] == '\0')
#endif
			)
		{
			rtgui_filelist_view_destroy(view);

			return ;
		}
		else
		{
			rtgui_filelist_view_menu_pop(RTGUI_WIDGET(view));
			return ;
		}
		rtgui_filelist_view_set_directory(view, new_path);
	}
}

rt_bool_t rtgui_filelist_view_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_widget *widget;
	struct rtgui_filelist_view* view = RT_NULL;

	widget = RTGUI_WIDGET(object);
	view = RTGUI_FILELIST_VIEW(widget);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		rtgui_filelist_view_ondraw(view);
		return RT_FALSE;

    case RTGUI_EVENT_RESIZE:
        {
			struct rtgui_event_resize* resize;

			resize = (struct rtgui_event_resize*)event;

            /* recalculate page items */
			if (file_image != RT_NULL)
				view->page_items = resize->h  / (1 + rtgui_theme_get_selected_height());
			else
				view->page_items = resize->h / (2 + 14);
        }
        break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		{
			rtgui_rect_t rect;
			struct rtgui_event_mouse* emouse;

			emouse = (struct rtgui_event_mouse*)event;

			/* calculate selected item */

			/* get physical extent information */
			rtgui_widget_get_rect(widget, &rect);
			rtgui_widget_rect_to_device(widget, &rect);

			if (rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK)
			{
				rt_uint16_t index;
				rt_uint16_t current_page;
				rt_uint16_t old_item;

				index = (emouse->y - rect.y1) / (2 + rtgui_theme_get_selected_height());

				/* get current page */
				current_page = view->current_item/view->page_items;
				old_item = view->current_item;

				if (index + current_page * view->page_items < view->items_count)
				{
					/* set selected item */
					view->current_item = index + current_page * view->page_items;
					if (emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
					{
						rtgui_filelist_view_update_current(view, old_item);
					}
					else
					{
						/* up event */
						rtgui_filelist_view_onenturn(view);
					}
				}

				return RT_TRUE;
			}
		}
		break;

    case RTGUI_EVENT_KBD:
        {
            struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
            if (ekbd->type == RTGUI_KEYDOWN)
            {
				rt_uint16_t old_item;

				old_item = view->current_item;
                switch (ekbd->key)
                {
                case RTGUIK_UP:
					if (view->current_item > 0)
						view->current_item --;
					rtgui_filelist_view_update_current(view, old_item);
					return RT_TRUE;

                case RTGUIK_DOWN:
					if (view->current_item < view->items_count - 1)
						view->current_item ++;
					rtgui_filelist_view_update_current(view, old_item);
					return RT_TRUE;

				case RTGUIK_LEFT:
					if (view->current_item - view->page_items >= 0)
						view->current_item -= view->page_items;
					rtgui_filelist_view_update_current(view, old_item);
					return RT_TRUE;

				case RTGUIK_RIGHT:
					if (view->current_item + view->page_items < view->items_count - 1)
						view->current_item += view->page_items;
					rtgui_filelist_view_update_current(view, old_item);
					return RT_TRUE;

				case RTGUIK_RETURN:
					rtgui_filelist_view_onenturn(view);
					return RT_TRUE;

                default:
                    break;
                }
            }
        }
		return RT_FALSE;
	}

    /* use view event handler */
    return rtgui_container_event_handler(object, event);
}

rtgui_filelist_view_t* rtgui_filelist_view_create(const char* directory,
												  const char* pattern,
												  const rtgui_rect_t* rect)
{
	struct rtgui_filelist_view* view = RT_NULL;

	/* create a new view */
	view = (struct rtgui_filelist_view*) rtgui_widget_create(RTGUI_FILELIST_VIEW_TYPE);
	if (view != RT_NULL)
	{
		rtgui_widget_set_rect(RTGUI_WIDGET(view), rect);
		view->items = RT_NULL;
		view->pattern = rt_strdup(pattern);
		view->page_items = rtgui_rect_height(*rect) / (1 + rtgui_theme_get_selected_height());
		rtgui_filelist_view_set_directory(view, directory);
	}

	return view;
}
RTM_EXPORT(rtgui_filelist_view_create);

void rtgui_filelist_view_destroy(rtgui_filelist_view_t* view)
{
    /* destroy view */
	rtgui_widget_destroy(RTGUI_WIDGET(view));
}
RTM_EXPORT(rtgui_filelist_view_destroy);


/* clear all file items */
static void rtgui_filelist_view_clear(rtgui_filelist_view_t* view)
{
	rt_uint32_t index;
    struct rtgui_file_item* item;

	for (index = 0; index < view->items_count; index ++)
	{
		item = &(view->items[index]);

		/* release item name */
		rt_free(item->name);
		item->name = RT_NULL;
	}

	/* release items */
	rtgui_free(view->items);
	view->items = RT_NULL;

	view->items_count = 0;
	view->current_item = 0;
}
RTM_EXPORT(rtgui_filelist_view_clear);

void rtgui_filelist_view_set_directory(rtgui_filelist_view_t* view, const char* directory)
{
    struct rtgui_file_item *item;

    RT_ASSERT(view != RT_NULL);

    /* clear file items firstly */
    rtgui_filelist_view_clear(view);
    if (directory != RT_NULL)
    {
		DIR* dir;
		struct stat s;
		char* fullpath;
		rt_uint32_t index;
		struct dirent* dirent;

		view->items_count = 0;
        dir = opendir(directory);
		if (dir == RT_NULL)  goto __return;

		/* current directory exists, set it */
		if (view->current_directory != RT_NULL) rt_free(view->current_directory);
		view->current_directory = rt_strdup(directory);

		do
		{
			dirent = readdir(dir);
			if (dirent == RT_NULL) break;

			if (strcmp(dirent->d_name, ".") == 0) continue;
			if (strcmp(dirent->d_name, "..") == 0) continue;

			view->items_count ++;
		} while (dirent != RT_NULL);
		closedir(dir);

		view->items_count ++; /* root directory for [x] exit, others for .. */

		view->items = (struct rtgui_file_item*) rtgui_malloc(sizeof(struct rtgui_file_item) * view->items_count);
		if (view->items == RT_NULL) return; /* no memory */

		index = 0;
		if (directory[0] == '/' && directory[1] != '\0')
		{
			item = &(view->items[0]);

			/* add .. directory */
			item->name = rt_strdup("..");
			item->type = RTGUI_FITEM_DIR;
			item->size = 0;

			index ++;
		}
		else
		{
			item = &(view->items[0]);

			/* add .. directory */
#ifdef RTGUI_USING_FONTHZ
			item->name = rt_strdup("ÍË³öÎÄ¼þä¯ÀÀ");
#else
			item->name = rt_strdup("..");
#endif
			item->type = RTGUI_FITEM_DIR;
			item->size = 0;

			index ++;
		}

		/* reopen directory */
		dir = opendir(directory);
		fullpath = rtgui_malloc(256);
		while (index < view->items_count)
		{
			dirent = readdir(dir);
			if (dirent == RT_NULL) break;

			if (strcmp(dirent->d_name, ".") == 0) continue;
			if (strcmp(dirent->d_name, "..") == 0) continue;

			item = &(view->items[index]);
			item->name = rt_strdup(dirent->d_name);

			rt_memset(&s, 0, sizeof(struct stat));

			/* build full path for the file */
			if (directory[strlen(directory) - 1] != PATH_SEPARATOR)
				rt_snprintf(fullpath, 256, "%s%c%s", directory, PATH_SEPARATOR, dirent->d_name);
			else
				rt_snprintf(fullpath, 256, "%s%s", directory, dirent->d_name);

			stat(fullpath, &s);
			if ( s.st_mode & S_IFDIR )
			{
				item->type = RTGUI_FITEM_DIR;
				item->size = 0;
			}
			else
			{
				item->type = RTGUI_FITEM_FILE;
				item->size = s.st_size;
			}

			index ++;
		}
		rtgui_free(fullpath);
		closedir(dir);
    }

	view->current_item = 0;

__return:
    /* update view */
    rtgui_widget_update(RTGUI_WIDGET(view));
}
RTM_EXPORT(rtgui_filelist_view_set_directory);

void rtgui_filelist_view_get_fullpath(rtgui_filelist_view_t* view, char* path, rt_size_t len)
{
	RT_ASSERT(view != RT_NULL);

	if (view->current_directory[strlen(view->current_directory) - 1] != PATH_SEPARATOR)
		rt_snprintf(path, len, "%s%c%s",view->current_directory, PATH_SEPARATOR,
			view->items[view->current_item].name);
	else
		rt_snprintf(path, len, "%s%s",view->current_directory,
			view->items[view->current_item].name);
}
RTM_EXPORT(rtgui_filelist_view_get_fullpath);

#endif
