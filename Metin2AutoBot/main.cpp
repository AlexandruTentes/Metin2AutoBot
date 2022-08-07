#include "Global.h"
#include "src/header/WinApiWrapper.h"

using namespace std;
using namespace mt2;

int main()
{
	bool running = true;
	WinApiWrapper& winapi = WinApiWrapper::get_instance();
	Global& global = Global::get_instance();

	while (running)
	{
		int key = waitKey(0);
		cout << winapi.get_mat() << "\n";
		if (winapi.read_screen())
			imshow(global.title, winapi.get_mat());

		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F5))
			winapi.get_focused_window();

		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F4) || key == 27)
			running = false;
	}
}