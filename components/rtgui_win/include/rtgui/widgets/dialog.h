#ifndef __DIALOG_H__
#define __DIALOG_H__

/* 打开对话框中的一些数据 */
struct OpenDlgSt
{
	char* path;		 //查找路径
	char* filename;	 //文件(夹)名称
	rt_uint32_t size;//文件大小/文件夹下的文件个数 
	rt_uint32_t type;//文件类型:文件/文件夹
	char* pattern;   //文件类型;

	rtgui_filelist_view_t* fview;
	rtgui_textbox_t* tbox_path;	//控件指针
	rtgui_textbox_t* tbox_filename;
	rtgui_combo_t*   cbox_pattern;
};


rtgui_win_t* rtgui_win_get_win_by_widget(PVOID wdt);
void OpenFileDialog(PVOID wdt, rtgui_event_t* event);
void NewFileDialog(PVOID wdt, rtgui_event_t *event);
void SaveFileDialog(PVOID wdt, rtgui_event_t *event);

void GoToTopFolder(PVOID wdt, rtgui_event_t *event);
void GoToSubFolder(PVOID wdt, rtgui_event_t *event);




#endif

