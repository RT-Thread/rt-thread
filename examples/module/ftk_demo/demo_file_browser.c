#include "ftk.h"
#include "ftk_file_browser.h"

static Ret on_file_selected(void* ctx, int index, const char* path)
{
	ftk_logd("%s: [%d] %s\n", __func__, index, path);

	return RET_OK;
}

#define IDC_TEST_BUTTON 1000
static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret button_browser_clicked(void* ctx, void* obj)
{
	FtkWidget* win = ftk_file_browser_create(FTK_FILE_BROWER_APP);
	ftk_file_browser_set_path(win, "./");
	ftk_file_browser_load(win);

	return RET_OK;
}

static Ret button_single_choose_clicked(void* ctx, void* obj)
{
	FtkWidget* win = ftk_file_browser_create(FTK_FILE_BROWER_SINGLE_CHOOSER);
	ftk_file_browser_set_choosed_handler(win, on_file_selected, NULL);
	ftk_file_browser_set_path(win, "./");
	ftk_file_browser_load(win);

	return RET_OK;
}

static Ret button_multi_choose_clicked(void* ctx, void* obj)
{
	FtkWidget* win = ftk_file_browser_create(FTK_FILE_BROWER_MULTI_CHOOSER);
	ftk_file_browser_set_choosed_handler(win, on_file_selected, NULL);
	ftk_file_browser_set_path(win, "./");
	ftk_file_browser_load(win);


	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_file_browser_create()
{
	return ftk_app_demo_create(_("file_browser"), ftk_main);
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
	
	width = width/2 - 10;
	button = ftk_button_create(win, 0, height/4, width, 50);
	ftk_widget_set_text(button, "Single Choose");
	ftk_button_set_clicked_listener(button, button_single_choose_clicked, win);

	button = ftk_button_create(win, width + 10, height/4, width, 50);
	ftk_widget_set_text(button, "Browser");
	ftk_button_set_clicked_listener(button, button_browser_clicked, win);
	
	button = ftk_button_create(win, 0, height/2, width, 50);
	ftk_widget_set_text(button, "Multi Choose");
	ftk_button_set_clicked_listener(button, button_multi_choose_clicked, win);

	button = ftk_button_create(win, width + 10, height/2, width, 50);
	ftk_widget_set_text(button, "Quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "FileBrowser");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

