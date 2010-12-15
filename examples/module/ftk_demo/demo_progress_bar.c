#include "ftk.h"
#include "ftk_util.h"

static void on_window_destroy(void* user_data)
{
	FtkSource* timer = user_data;

	ftk_source_disable(timer);
	ftk_main_loop_remove_source(ftk_default_main_loop(), timer);

	return;
}

static Ret update_progress(void* ctx)
{
	int percent = 0;
	char text[32] = {0};
	FtkWidget* progress_bar = ctx;

	percent = ftk_progress_bar_get_percent(progress_bar);
	if(percent == 100)
	{
		return RET_REMOVE;
	}
	ftk_progress_bar_set_percent(progress_bar, percent + 10);

	ftk_itoa(text, sizeof(text), ftk_progress_bar_get_percent(progress_bar));
	strcat(text, "%");
	ftk_widget_set_text(progress_bar, text);

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_progress_bar_create()
{
	return ftk_app_demo_create(_("progress_bar"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	FtkWidget* win = NULL;
	FtkWidget* progress_bar = NULL;
	FtkSource* timer = NULL;

	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	width = width - 20;
	progress_bar = ftk_progress_bar_create(win, 10, height/6, width, 20);
	ftk_progress_bar_set_percent(progress_bar, 20);
	timer = ftk_source_timer_create(1000, update_progress, progress_bar);
	ftk_main_loop_add_source(ftk_default_main_loop(), timer);
	ftk_widget_set_user_data(progress_bar, on_window_destroy, timer);

	progress_bar = ftk_progress_bar_create(win, 10, height/3, width, 20);
	ftk_progress_bar_set_percent(progress_bar, 20);
	timer = ftk_source_timer_create(1000, update_progress, progress_bar);
	ftk_main_loop_add_source(ftk_default_main_loop(), timer);
	ftk_widget_set_user_data(progress_bar, on_window_destroy, timer);
	ftk_progress_bar_set_interactive(progress_bar, 1);

	progress_bar = ftk_progress_bar_create(win, 10, height/2, width, 20);
	ftk_progress_bar_set_percent(progress_bar, 20);
	timer = ftk_source_timer_create(1000, update_progress, progress_bar);
	ftk_main_loop_add_source(ftk_default_main_loop(), timer);
	ftk_widget_set_user_data(progress_bar, on_window_destroy, timer);

	ftk_widget_set_text(win, "progress_bar demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

