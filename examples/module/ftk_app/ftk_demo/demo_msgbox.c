#include "ftk.h"

static const char* buttons1[] = {"Yes", NULL};
static const char* buttons2[] = {"Yes", "No", NULL};
static const char* buttons3[] = {"Yes", "No", "Cancel", NULL};
static Ret button_warning(void* ctx, void* obj)
{
	int ret = ftk_warning("Warning", "December 31, 2008: patchwork.kernel.org is now available for general use. It is currently only monitoring the Linux Kernel mailing-list, but should be useful to kernel developers in dealing with patches flying across the wire.", buttons1);

	ftk_logd("%s: ret = %d\n", __func__, ret);

	return RET_OK;
}

static Ret button_info(void* ctx, void* obj)
{
	int ret = ftk_infomation("Infomation", "September 19, 2008: mirrors.kernel.org has been flipped over to using our new GeoDNS based bind server (named-geodns). This means that, at the dns query level, our servers will attempt to direct you to the nearest / fastest kernel.org mirror for your request. This means that you no longer have to use mirrors.us.kernel.org or mirrors.eu.kernel.org to generally route you to the right place. This does mean a change to mirrors.kernel.org no longer explicitly pointing at mirrors.us.kernel.org. Additional information on named-geodns will be forth coming, check back here for an addendum soon.", buttons2);

	ftk_logd("%s: ret = %d\n", __func__, ret);
	return RET_OK;
}

static Ret button_question(void* ctx, void* obj)
{
	int ret = ftk_question("Question", "Are you sure to quit?", buttons3);
	ftk_logd("%s: ret = %d\n", __func__, ret);

	return RET_OK;
}

static Ret button_tips(void* ctx, void* obj)
{
	int ret = ftk_tips("The dialog will quit in 3 seconds.");
	ftk_logd("%s: ret = %d\n", __func__, ret);

	return RET_OK;
}

static Ret button_quit(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);
	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_msgbox_create()
{
	return ftk_app_demo_create(_("msgbox"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int y = 0;
	int width = 0;
	int height = 0;
	FtkWidget* win = NULL;
	FtkWidget* button = NULL;

	FTK_INIT(argc, argv);
		
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	y = (height - 240)/2;
	y = y > 0 ? y : 0;

	button = ftk_button_create(win, 0, y, width/2, 50);
	ftk_widget_set_text(button, "question");
	ftk_button_set_clicked_listener(button, button_question, win);
	
	button = ftk_button_create(win, width/2, y, width/2, 50);
	ftk_widget_set_text(button, "warning");
	ftk_button_set_clicked_listener(button, button_warning, win);
	
	button = ftk_button_create(win, 0, y+60, width/2, 50);
	ftk_widget_set_text(button, "info");
	ftk_button_set_clicked_listener(button, button_info, win);

	button = ftk_button_create(win, width/2, y+60, width/2, 50);
	ftk_widget_set_text(button, "tips");
	ftk_button_set_clicked_listener(button, button_tips, win);
	
	button = ftk_button_create(win, width/4, y+120, width/2, 50);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit, win);

	ftk_widget_set_text(win, "message box demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

