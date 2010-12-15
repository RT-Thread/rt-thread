#include "ftk.h"

typedef struct _TimerInfo
{
	int times;
	FtkWidget* label;
}TimerInfo;

static Ret timeout(void* ctx)
{
	TimerInfo* info = ctx;
	char buffer[32] = {0};
	if(info->times > 0)
	{
		snprintf(buffer, sizeof(buffer), "Quit after %d seconds", info->times);
		ftk_widget_set_text(info->label, buffer);
		info->times--;

		return RET_OK;
	}
	else
	{
		ftk_widget_unref(ftk_widget_toplevel(info->label));
		ftk_logd("%s: timeout and quit.\n", __func__);
		FTK_FREE(info);
		FTK_QUIT();
		return RET_REMOVE;
	}
}

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	FtkGc gc = {.mask = FTK_GC_BG};
	TimerInfo* info = NULL;

	FTK_INIT(argc, argv);
	info = (TimerInfo*)FTK_ZALLOC(sizeof(TimerInfo));
	info->times = 100;
		
	FtkSource* timer = ftk_source_timer_create(1000, timeout, info);
	FtkWidget* win = ftk_app_window_create();

	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	FtkWidget* label = ftk_label_create(win, 10, 10, width - 20, 20);
	ftk_widget_set_text(label, "arabic bidi demo");
	
	label = ftk_label_create(win, 10, 40, width - 20, 20);
	ftk_widget_set_text(label, "English Text");
	assert(strcmp(ftk_widget_get_text(label), "English Text") == 0);
	
	gc.bg.a = 0xff;
	gc.bg.r = 0xF0;
	gc.bg.g = 0xF0;
	gc.bg.b = 0x80;
	label = ftk_label_create(win, 10, height/2, width - 20, 120);
	ftk_widget_set_gc(label, FTK_WIDGET_INSENSITIVE, &gc);
	ftk_widget_unset_attr(label, FTK_ATTR_TRANSPARENT);
	ftk_widget_set_text(label, "ان منح حياتك للمسيح تعد خطوة ايمان يمكنك القيام بها عن طريق الصلاة");
	
	label = ftk_label_create(win, 50, height/2-30, width, 20);
	info->label = label;
	
	ftk_widget_set_text(win, "label demo");
	ftk_widget_show_all(win, 1);

	ftk_widget_set_attr(win, FTK_ATTR_IGNORE_CLOSE);
	ftk_main_loop_add_source(ftk_default_main_loop(), timer);

	FTK_RUN();

	return 0;
}

