#include "ftk.h"
#include "ftk_xul.h"

const char* t1 = "<window> </window>";

#define IDC_QUIT 100

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);
	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_xul_create()
{
	return ftk_app_demo_create(_("xul"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	if(argc > 1)
	{
		FtkWidget* win = NULL;
		FtkWidget* quit = NULL;
		FtkXulCallbacks callbacks;
		
		FTK_INIT(argc, argv);
		
		callbacks.translate_text = NULL;
		callbacks.load_image = (FtkXulLoadImage)ftk_icon_cache_load;
		callbacks.ctx = ftk_icon_cache_create(NULL, "testdata");
		win = ftk_xul_load_file(argv[1], &callbacks);
		ftk_icon_cache_destroy(callbacks.ctx);
		FTK_QUIT_WHEN_WIDGET_CLOSE(win);

		quit = ftk_widget_lookup(win, IDC_QUIT);
		ftk_button_set_clicked_listener(quit, button_quit_clicked, win);
		ftk_widget_show_all(win, 1);

		FTK_RUN();
	}
	else
	{
		ftk_logd("Usage: %s xul\n", argv[0]);

		return 0;
	}

	return 0;
}
