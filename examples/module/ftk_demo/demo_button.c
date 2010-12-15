#include "ftk.h"

#define IDC_TEST_BUTTON 1000
static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret button_hide_clicked(void* ctx, void* obj)
{
	ftk_widget_show(ftk_widget_lookup(ctx, IDC_TEST_BUTTON), 0);

	return RET_OK;
}

static Ret button_show_clicked(void* ctx, void* obj)
{
	ftk_widget_show(ftk_widget_lookup(ctx, IDC_TEST_BUTTON), 1);

	return RET_OK;
}

static Ret button_default_clicked(void* ctx, void* obj)
{
	printf("%s: button %s is clicked.\n", __func__, ftk_widget_get_text(obj));

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_button_create()
{
	return ftk_app_demo_create(_("button"), ftk_main);
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
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	width = width/3 - 10;
	button = ftk_button_create(win, 0, 30, width, 50);
	ftk_widget_set_text(button, "show");
	ftk_button_set_clicked_listener(button, button_show_clicked, win);

	button = ftk_button_create(win, width + 10, 30, width, 50);
	ftk_widget_set_text(button, "hide");
	ftk_button_set_clicked_listener(button, button_hide_clicked, win);
	
	button = ftk_button_create(win, 2*(width + 10), 30, width, 50);
	ftk_widget_set_text(button, "按钮测试");
	ftk_widget_set_id(button, IDC_TEST_BUTTON);
	ftk_button_set_clicked_listener(button, button_default_clicked, win);
	
	button = ftk_button_create(win, 0, 130, width, 40);
	ftk_widget_set_text(button, "yes");
	ftk_button_set_clicked_listener(button, button_default_clicked, win);
	
	button = ftk_button_create(win, 2*(width + 10), 130, width, 40);
	ftk_widget_set_text(button, "no");
	ftk_button_set_clicked_listener(button, button_default_clicked, win);
	
	button = ftk_button_create(win, width + 10, height/2, width, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "button demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

