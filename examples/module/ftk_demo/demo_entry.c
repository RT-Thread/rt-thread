#include "ftk.h"

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_logd("%s: %s\n", __func__, ftk_widget_get_text(ftk_widget_lookup(ctx, 100)));
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret ftk_digit_only_filter(void* ctx, void* data)
{
	FtkEvent* event = data;
	if(event->type == FTK_EVT_KEY_UP || event->type == FTK_EVT_KEY_DOWN)
	{
		int code = event->u.key.code;
		if(code >= FTK_KEY_0 && code <= FTK_KEY_9)
		{
			return RET_OK;
		}
		else if(code == FTK_KEY_UP 
			|| code == FTK_KEY_DOWN
			|| code == FTK_KEY_LEFT
			|| code == FTK_KEY_RIGHT
			|| code == FTK_KEY_BACKSPACE
			|| code == FTK_KEY_DELETE
			|| code == FTK_KEY_HOME
			|| code == FTK_KEY_END
			|| code == FTK_KEY_TAB)
		{
			return RET_OK;
		}

		return RET_REMOVE;
	}

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_entry_create()
{
	return ftk_app_demo_create(_("entry"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

#define STR_TEXT1 "Single line editor, that means you can input a one line only."
#define STR_TEXT2 "Single line editor, 也就是说你只能输入一行文字."

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
	ftk_widget_set_id(entry, 100);
	ftk_widget_set_text(entry, "1234");
	ftk_widget_set_event_listener(entry, ftk_digit_only_filter, NULL);
	ftk_entry_set_tips(entry, "Please input some digits.");
	entry = ftk_entry_create(win, 10, 80, ftk_widget_width(win) - 20, 30);
	ftk_widget_set_text(entry, STR_TEXT1);
	assert(strcmp(STR_TEXT1, ftk_widget_get_text(entry)) == 0);

	entry = ftk_entry_create(win, 10, 130, ftk_widget_width(win) - 20, 30);
	ftk_widget_set_text(entry, STR_TEXT2);
	assert(strcmp(STR_TEXT2, ftk_widget_get_text(entry)) == 0);
	
	button = ftk_button_create(win, width/4, 3*height/4, width/2, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "entry demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

