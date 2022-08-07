#include "Global.h"
#include "src/header/WinApiWrapper.h"
#include "src/header/OpenCVWrapper.h"

using namespace std;
using namespace mt2;

int main()
{
	bool running = true;
	WinApiWrapper& winapi = WinApiWrapper::get_instance();
	OpenCVWrapper& opencv = OpenCVWrapper::get_instance();
	Global& global = Global::get_instance();

	while (running)
	{
		int key = waitKey(1);

		if (winapi.read_screen())
		{
			opencv.update();
			imshow(global.title, opencv.get_mat());
			imshow(global.map_title, opencv.get_color_map_mat());			
		}

		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F5))
			winapi.get_focused_window();

		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F4) || key == 27)
			running = false;
	}

	destroyAllWindows();
}