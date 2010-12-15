#include "ftk.h"

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_hello_create()
{
	return ftk_app_demo_create(_("hello"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	FtkWidget* win = NULL;

	FTK_INIT(argc, argv);
	win = ftk_app_window_create();
	ftk_widget_set_text(win, "Hello FTK!");
	ftk_widget_show(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

