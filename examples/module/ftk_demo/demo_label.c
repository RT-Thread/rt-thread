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
		ftk_snprintf(buffer, sizeof(buffer), "Quit after %d seconds", info->times);
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

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_label_create()
{
	return ftk_app_demo_create(_("label"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	FtkGc gc = {0};
	TimerInfo* info = NULL;
	FtkSource* timer = NULL;
	FtkWidget* win = NULL;
	FtkWidget* label = NULL;

	gc.mask = FTK_GC_BG;

	FTK_INIT(argc, argv);
	info = (TimerInfo*)FTK_ZALLOC(sizeof(TimerInfo));
	info->times = 5;
		
	timer = ftk_source_timer_create(1000, timeout, info);
	win = ftk_app_window_create();
	ftk_window_set_animation_hint(win, "app_main_window");

	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

#ifdef WIN32	
	label = ftk_label_create(win, 10, 10, width - 20, 20);
	ftk_widget_set_text(label, "中文文本");
#else
#endif
	label = ftk_label_create(win, 10, 40, width - 20, 20);
	ftk_widget_set_text(label, "English Text(center)");
	ftk_label_set_alignment(label, FTK_ALIGN_CENTER);
	assert(strcmp(ftk_widget_get_text(label), "English Text(center)") == 0);
	
	label = ftk_label_create(win, 10, 70, width - 20, 20);
	ftk_widget_set_text(label, "English Text(right)");
	ftk_label_set_alignment(label, FTK_ALIGN_RIGHT);

	gc.bg.a = 0xff;
	gc.bg.r = 0xF0;
	gc.bg.g = 0xF0;
	gc.bg.b = 0x80;
	label = ftk_label_create(win, 10, height/2, width - 20, 120);
	ftk_widget_set_gc(label, FTK_WIDGET_INSENSITIVE, &gc);
	ftk_widget_unset_attr(label, FTK_ATTR_TRANSPARENT);
#ifdef WIN32	
	ftk_widget_set_text(label, "The linux mobile development(with background color)");
#else
	ftk_widget_set_text(label, "中英文混合多行文本显示:the linux mobile development.带有背景颜色。");
#endif
	label = ftk_label_create(win, 50, height/2-30, width, 20);
	info->label = label;
	
	ftk_widget_set_text(win, "label demo");
	ftk_widget_show_all(win, 1);

	ftk_widget_set_attr(win, FTK_ATTR_IGNORE_CLOSE);
	ftk_main_loop_add_source(ftk_default_main_loop(), timer);

	FTK_RUN();

	return 0;
}

