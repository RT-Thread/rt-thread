#include "ftk.h"

static Ret button_close_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static FtkListItemInfo g_infos[4];
static Ret on_menu_item_clicked(void* ctx, void* data)
{
	FtkListItemInfo* info = data;

	ftk_logd("%s: %s is selected\n", __func__, info->text);

	return RET_OK;
}

static Ret button_normal_clicked(void* ctx, void* obj)
{
	FtkBitmap* icon = ftk_theme_load_image(ftk_default_theme(), "info"FTK_STOCK_IMG_SUFFIX); 
	FtkWidget* thiz = ftk_popup_menu_create(0, 0, 0, 200, icon, "Edit");
	
	size_t i = 0;
	for(i = 0; i < FTK_ARRAY_SIZE(g_infos); i++)
	{
		g_infos[i].type = FTK_LIST_ITEM_NORMAL;
		ftk_popup_menu_add(thiz, g_infos+i);
	}
	ftk_bitmap_unref(icon);
	
	ftk_widget_show_all(thiz, 1);

	return RET_OK;
}

static Ret button_radio_clicked(void* ctx, void* obj)
{
	FtkBitmap* icon = ftk_theme_load_image(ftk_default_theme(), "info"FTK_STOCK_IMG_SUFFIX); 
	FtkWidget* thiz = ftk_popup_menu_create(0, 0, 0, 200, icon, "Edit");
	
	size_t i = 0;
	for(i = 0; i < FTK_ARRAY_SIZE(g_infos); i++)
	{
		g_infos[i].type = FTK_LIST_ITEM_RADIO;
		g_infos[i].state = i == 0;
		ftk_popup_menu_add(thiz, g_infos+i);
	}
	ftk_bitmap_unref(icon);
	
	ftk_widget_show_all(thiz, 1);

	return RET_OK;
}

static Ret button_check_clicked(void* ctx, void* obj)
{
	FtkBitmap* icon = ftk_theme_load_image(ftk_default_theme(), "info"FTK_STOCK_IMG_SUFFIX); 
	FtkWidget* thiz = ftk_popup_menu_create(0, 0, 0, 200, icon, "Edit");
	
	size_t i = 0;
	for(i = 0; i < FTK_ARRAY_SIZE(g_infos); i++)
	{
		g_infos[i].type = FTK_LIST_ITEM_CHECK;
		g_infos[i].state = i%2;
		ftk_popup_menu_add(thiz, g_infos+i);
	}
	ftk_bitmap_unref(icon);

	ftk_widget_show_all(thiz, 1);

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_popup_create()
{
	return ftk_app_demo_create(_("popup"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	FtkWidget* win = NULL;
	FtkWidget* button = NULL;
	
	FTK_INIT(argc, argv);

	g_infos[0].text = "Copy";
	g_infos[1].text = "Paste";
	g_infos[2].text = "Cut";
	g_infos[3].text = "Select All";
	g_infos[0].extra_user_data = on_menu_item_clicked;
	g_infos[1].extra_user_data = on_menu_item_clicked;
	g_infos[2].extra_user_data = on_menu_item_clicked;
	g_infos[3].extra_user_data = on_menu_item_clicked;

	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	button = ftk_button_create(win, 0, height/6, width/3, 50);
	ftk_widget_set_text(button, "Normal");
	ftk_button_set_clicked_listener(button, button_normal_clicked, NULL);

	button = ftk_button_create(win, 2*width/3, height/6, width/3, 50);
	ftk_widget_set_text(button, "Radio");
	ftk_button_set_clicked_listener(button, button_radio_clicked, NULL);

	button = ftk_button_create(win, 0, height/2, width/3, 50);
	ftk_widget_set_text(button, "CheckBox");
	ftk_button_set_clicked_listener(button, button_check_clicked, NULL);
	
	button = ftk_button_create(win, 2*width/3, height/2, width/3, 50);
	ftk_widget_set_text(button, "Quit");
	ftk_button_set_clicked_listener(button, button_close_clicked, win);
	
	ftk_widget_set_text(win, "pupup");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

