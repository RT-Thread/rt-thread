#include "ftk.h"

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret button_clicked(void* ctx, void* obj)
{
	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_check_button_create()
{
	return ftk_app_demo_create(_("check_button"), ftk_main);
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
	FtkWidget* group = NULL;
	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	width = width/2 - 10;
	button = ftk_check_button_create(win,0, 10, width, 50);
	ftk_widget_set_text(button, "show");
	ftk_check_button_set_clicked_listener(button, button_clicked, win);

	button = ftk_check_button_create(win, width + 10, 10, width, 50);
	ftk_widget_set_text(button, "hide");
	ftk_check_button_set_clicked_listener(button, button_clicked, win);
	
	group = ftk_radio_group_create(win, 0, 60, 2 * width, 60);
	
	button = ftk_check_button_create_radio(group,0, 10, width, 50);
	ftk_widget_set_text(button, "Male");
	ftk_check_button_set_clicked_listener(button, button_clicked, win);

	button = ftk_check_button_create_radio(group, width + 10, 10, width, 50);
	ftk_widget_set_text(button, "Female");
	ftk_check_button_set_clicked_listener(button, button_clicked, win);
	
	group = ftk_radio_group_create(win, 0, 120, 2 * width, 60);

	button = ftk_check_button_create_radio(group,0, 10, width, 50);
	ftk_widget_set_text(button, "1(图标右)");
	ftk_check_button_set_icon_position(button, 1);
	ftk_check_button_set_clicked_listener(button, button_clicked, win);

	button = ftk_check_button_create_radio(group, width + 10, 10, width, 50);
	ftk_widget_set_text(button, "2(图标右)");
	ftk_check_button_set_icon_position(button, 1);
	ftk_check_button_set_clicked_listener(button, button_clicked, win);
	
	button = ftk_button_create(win, width/2, 3*height/4, width, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "check button demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

