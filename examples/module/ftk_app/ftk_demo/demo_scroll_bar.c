#include "ftk.h"

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret scroll_bar_on_scroll(void* ctx, void* scroll_bar)
{
	ftk_logd("%s: value=%d\n", __func__, ftk_scroll_bar_get_value(scroll_bar));

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_scroll_bar_create()
{
	return ftk_app_demo_create(_("scroll_bar"), ftk_main);
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
	FtkWidget* scroll_bar = NULL;

	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	/*v*/
	scroll_bar = ftk_scroll_bar_create(win, width/8, 5, 0, height/2);
	ftk_scroll_bar_set_param(scroll_bar, 0, 120, 120);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);

	scroll_bar = ftk_scroll_bar_create(win, width/4, 5, 0, height/2);
	ftk_scroll_bar_set_param(scroll_bar, 40, 120, 60);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);
	
	scroll_bar = ftk_scroll_bar_create(win, 3*width/8, 5, 0, height/2);
	ftk_scroll_bar_set_param(scroll_bar, 110, 120, 30);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);
	
	scroll_bar = ftk_scroll_bar_create(win, width/2, 5, 0, height/2);
	ftk_scroll_bar_set_param(scroll_bar, 120, 120, 20);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);

	/*h*/
	scroll_bar = ftk_scroll_bar_create(win, 5, height/2 + 10, width - 10, 0);
	ftk_scroll_bar_set_param(scroll_bar, 120, 120, 20);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);
	
	scroll_bar = ftk_scroll_bar_create(win, 5, height/2 + 30, width - 10, 0);
	ftk_scroll_bar_set_param(scroll_bar, 110, 120, 30);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);
	
	scroll_bar = ftk_scroll_bar_create(win, 5, height/2 + 50, width - 10, 0);
	ftk_scroll_bar_set_param(scroll_bar, 40, 120, 60);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);
	
	scroll_bar = ftk_scroll_bar_create(win, 5, height/2 + 80, width - 10, 0);
	ftk_scroll_bar_set_param(scroll_bar, 0, 120, 120);	
	ftk_scroll_bar_set_listener(scroll_bar, scroll_bar_on_scroll, NULL);
	
	button = ftk_button_create(win, 2*width/3, height/4, width/3-5, 50);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "scroll_bar demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

