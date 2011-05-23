#include "ftk.h"

static Ret on_prepare_options_menu(void* ctx, FtkWidget* menu_panel)
{
	int i = 0;
	for(i = 0; i < 3; i++)
	{
		char text[32] = {0};
		FtkWidget* item = ftk_menu_item_create(menu_panel);
		ftk_snprintf(text, sizeof(text), "Menu%02d", i);
		ftk_widget_set_text(item, text);
		ftk_widget_show(item, 1);
	}

	return i > 0 ? RET_OK : RET_FAIL;
}
#define IDC_TEST_BUTTON 1000
static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static const char* buttons[] = {"OK", NULL};
static Ret button_unfullscreen_clicked(void* ctx, void* obj)
{
	if(!ftk_window_is_fullscreen(ctx))
	{
		ftk_infomation("Infomation", "Windows is not fullscreen.", buttons);
	}
	else
	{
		ftk_window_set_fullscreen(ctx, 0);
	}

	return RET_OK;
}

static Ret button_fullscreen_clicked(void* ctx, void* obj)
{
	if(ftk_window_is_fullscreen(ctx))
	{
		ftk_infomation("Infomation", "Windows is fullscreen.", buttons);
	}
	else
	{
		ftk_window_set_fullscreen(ctx, 1);
	}

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_fullscreen_create()
{
	return ftk_app_demo_create(_("fullscreen"), ftk_main);
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
	
	win = ftk_app_window_create();
	ftk_window_set_animation_hint(win, "app_main_window");
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	width = width/2 - 10;
	button = ftk_button_create(win, 0, height/4, width, 50);
	ftk_widget_set_text(button, "Fullscreen");
	ftk_button_set_clicked_listener(button, button_fullscreen_clicked, win);

	button = ftk_button_create(win, width + 10, height/4, width, 50);
	ftk_widget_set_text(button, "Unfullscreen");
	ftk_button_set_clicked_listener(button, button_unfullscreen_clicked, win);
	
	button = ftk_button_create(win, width/2, height/2, width, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "fullscreen");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);
	ftk_app_window_set_on_prepare_options_menu(win, on_prepare_options_menu, win);

	FTK_RUN();

	return 0;
}

