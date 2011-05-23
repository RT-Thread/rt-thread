#include "ftk.h"

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);
	return RET_OK;
}

static Ret button_start_clicked(void* ctx, void* obj)
{
	ftk_widget_show(ctx, 1);
	ftk_wait_box_start_waiting(ctx);

	return RET_OK;
}

static Ret button_stop_clicked(void* ctx, void* obj)
{
	ftk_wait_box_stop_waiting(ctx);

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_wait_box_create()
{
	return ftk_app_demo_create(_("wait_box"), ftk_main);
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
	FtkWidget* wait_box = NULL;

	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	wait_box = ftk_wait_box_create(win, width/2 - 16, height/4);
	
	button = ftk_button_create(win, 0, height/2, width/3, 50);
	ftk_widget_set_text(button, "start");
	ftk_button_set_clicked_listener(button, button_start_clicked, wait_box);
	
	button = ftk_button_create(win, 2*width/3, height/2, width/3, 50);
	ftk_widget_set_text(button, "stop");
	ftk_button_set_clicked_listener(button, button_stop_clicked, wait_box);

	button = ftk_button_create(win, width/4, 3*height/4, width/2, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "wait_box demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

