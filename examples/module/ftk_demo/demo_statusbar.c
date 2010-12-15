#include "ftk.h"
#include <time.h>

#define IDC_TIME_ITEM 2000

static Ret update_time(void* ctx)
{
	char text[10] = {0};
	FtkWidget* item = NULL;
	FtkWidget* panel = NULL;

	time_t now = time(0);
	struct tm* t = localtime(&now);
	panel = ftk_default_status_panel();

	snprintf(text, sizeof(text)-1, "%2d:%2d", t->tm_hour, t->tm_min);

	item = ftk_widget_lookup(panel, IDC_TIME_ITEM);

	ftk_widget_set_text(item, text);

	ftk_logd("%s: %s\n", __func__, text);

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_statusbar_create()
{
	return ftk_app_demo_create(_("status_bar"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	FtkSource* timer = NULL;
	FtkWidget* win = NULL;
	FtkWidget* item = NULL;
	FtkWidget* panel = NULL;
	FTK_INIT(argc, argv);

	/*create a time widget in statusbar.*/
	panel = ftk_default_status_panel();
	item = ftk_status_item_create(panel, -2, 60);
	ftk_widget_set_id(item, IDC_TIME_ITEM);

	ftk_widget_show(item, 1);

	win = ftk_app_window_create();
	ftk_widget_set_text(win, "Hello FTK!");

	ftk_widget_show(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	update_time(NULL);
	timer = ftk_source_timer_create(60000, update_time, NULL);
	ftk_main_loop_add_source(ftk_default_main_loop(), timer);

	FTK_RUN();

	return 0;
}
