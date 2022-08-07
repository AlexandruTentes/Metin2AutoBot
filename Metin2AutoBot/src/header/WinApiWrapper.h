#pragma once

#include "../../Include.h"
#include "../../Macro.h"
#include "../../Global.h"

#include "OpenCVWrapper.h"

namespace mt2
{
	class WinApiWrapper
	{
	public:
		SINGLETONIZE_INIT(WinApiWrapper)

		void get_focused_window();
		bool get_screen_mat();
		bool read_screen();
		Mat get_mat();

		virtual ~WinApiWrapper();

	private:
		void init();
		BITMAPINFOHEADER create_bitmap_header(int width, int height);

	private:
		HWND hwnd = NULL;
		RECT rect;
		int width = 0, height = 0;
		HDC windowDC, compatible_windowDC;
		HBITMAP hb_window;
		Mat mat;
		int screen_x, screen_y;
		float scale = 1.0;
		BITMAPINFOHEADER bi;

		Global& global = Global::get_instance();
		OpenCVWrapper& opencv = OpenCVWrapper::get_instance();
	};
};