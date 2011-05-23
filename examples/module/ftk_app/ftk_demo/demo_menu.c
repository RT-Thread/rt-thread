#include "ftk.h"

static void create_app_window(void);
static Ret button_open_clicked(void* ctx, void* obj)
{
	create_app_window();

	return RET_OK;
}

static Ret button_close_clicked(void* ctx, void* obj)
{
	FtkWidget* win = ctx;
	ftk_logd("%s: close window %s\n", __func__, ftk_widget_get_text(win));
	ftk_widget_unref(win);

	return RET_OK;
}


static int g_index = 0;
static void on_window_close(void* user_data)
{
	g_index--;

	ftk_logd("%s: g_index=%d\n", __func__, g_index);
	if(g_index == 0)
	{
		FTK_QUIT();
	}

	return ;
}

static Ret on_prepare_options_menu(void* ctx, FtkWidget* menu_panel)
{
	int i = 0;
	for(i = 0; i < g_index && i < 8; i++)
	{
		char text[32] = {0};
		FtkWidget* item = ftk_menu_item_create(menu_panel);
		ftk_snprintf(text, sizeof(text), "Menu%02d", i);
		ftk_widget_set_text(item, text);
		ftk_widget_show(item, 1);
	}

	return i > 0 ? RET_OK : RET_FAIL;
}

static void create_app_window(void)
{
	int width = 0;
	int height = 0;
	char title[128] = {0};
	FtkWidget* win = ftk_app_window_create();
	FtkWidget* label = NULL;
	FtkWidget* button = NULL;

	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	button = ftk_button_create(win, 0, height/6, width/2-5, 50);
	ftk_widget_set_text(button, "创建窗口");
	ftk_button_set_clicked_listener(button, button_open_clicked, win);

	button = ftk_button_create(win, width/2+5, height/6, width/2-5, 50);
	ftk_widget_set_text(button, "关闭窗口");
	ftk_button_set_clicked_listener(button, button_close_clicked, win);

	label = ftk_label_create(win, 10, height/2, width-20, 60);

	ftk_snprintf(title, sizeof(title), 
		"Press F2 to open menu, Presss F3 close window%02d", g_index++);
	ftk_widget_set_text(label, title);
	
	ftk_snprintf(title, sizeof(title), "window%02d", g_index++);
	ftk_widget_set_text(win, title);
	ftk_widget_show_all(win, 1);
	ftk_widget_set_user_data(win, on_window_close, win);
	
	ftk_app_window_set_on_prepare_options_menu(win, on_prepare_options_menu, win);

	return;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_menu_create()
{
	return ftk_app_demo_create(_("menu"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	FTK_INIT(argc, argv);
	
	create_app_window();

	FTK_RUN();

	return 0;
}

