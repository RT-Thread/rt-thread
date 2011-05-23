#include "ftk.h"

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);
	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_ime_create()
{
	return ftk_app_demo_create(_("ime"), ftk_main);
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
	FtkWidget* entry  = NULL;

	FTK_INIT(argc, argv);

	win = ftk_app_window_create();
	ftk_window_set_animation_hint(win, "app_main_window");
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	entry = ftk_entry_create(win, 10, 30, ftk_widget_width(win) - 20, 30);
	ftk_entry_set_text(entry, "Single line editor");
	ftk_input_method_manager_set_current(ftk_default_input_method_manager(), 0);

	entry = ftk_entry_create(win, 10, 80, ftk_widget_width(win) - 20, 30);
	ftk_entry_set_text(entry, "Single line editor, that means you can input a one line only.");
	
	entry = ftk_entry_create(win, 10, 130, ftk_widget_width(win) - 20, 30);
	ftk_entry_set_text(entry, "Single line editor, 也就是说你只能输入一行文字.");
	
	button = ftk_button_create(win, width/4, height/2, width/2, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);
	
	entry = ftk_entry_create(win, 10, height-60, ftk_widget_width(win) - 20, 30);
	ftk_entry_set_text(entry, "Single line editor");

	ftk_widget_set_text(win, "entry demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

