#include "header/WinApiWrapper.h"

void mt2::WinApiWrapper::init()
{
    std::cout << "Waiting to detect the game...\n";

    while (hwnd == NULL)
    {
        hwnd = FindWindowA(NULL, global.game_name);
    }

    std::cout << "Found game!\n";
    this->get_screen_mat();
}

BITMAPINFOHEADER mt2::WinApiWrapper::create_bitmap_header(int width, int height)
{
    BITMAPINFOHEADER  bi;

    // create a bitmap
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    return bi;
}

void mt2::WinApiWrapper::get_focused_window()
{
    if (hwnd != NULL)
        return;

    try
    {
        //Get the handler of the focused window
        hwnd = GetForegroundWindow();
        GetWindowTextA(hwnd, global.title, sizeof(global.title));

        this->get_screen_mat();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}

bool mt2::WinApiWrapper::get_screen_mat()
{
    if (hwnd == NULL)
        return false;

    windowDC = GetDC(hwnd);
    compatible_windowDC = CreateCompatibleDC(windowDC);
    SetStretchBltMode(compatible_windowDC, COLORONCOLOR);
    RECT rect;
    GetClientRect(hwnd, &rect);

    while (rect.left == 0 && rect.right == 0)
    {
        GetClientRect(hwnd, &rect);
        Sleep(5);
    }

    screen_width = rect.right;
    screen_height = rect.bottom;
    width = rect.right / scale;
    height = rect.bottom / scale;

    opencv.get_mat().create(height, width, CV_8UC4);

    hb_window = CreateCompatibleBitmap(windowDC, width, height);
    bi = create_bitmap_header(width, height);
    
    SelectObject(compatible_windowDC, hb_window);

    // copy from the window device context to the bitmap device context
    this->read_screen();

    return true;
}

bool mt2::WinApiWrapper::read_screen()
{
    if (hwnd == NULL)
        return false;

    StretchBlt(compatible_windowDC, 0, 0, width, height, windowDC, 0, 0, screen_width, screen_height, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(compatible_windowDC, hb_window, 0, height, opencv.get_mat().data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

    if (FindWindowA(NULL, global.game_name) == NULL)
    {
        std::cout << "Game closed!\n";
        hwnd = NULL;
        opencv.get_mat().release();
        init();
    }

    //Reading the Map
    this->read_screen(opencv.get_map_mat(), width * global.map_x, height * global.map_y, width * global.map_width, height * global.map_height);

    return !opencv.get_mat().empty();
}

bool mt2::WinApiWrapper::read_screen(Mat & mat, int x, int y, int width, int height)
{
    if (hwnd == NULL || opencv.get_mat().empty())
        return false;

    if (mat.size().height == 0)
        mat.create(height, width, CV_8UC4);

    Rect roi(x, y, width, height);
    Mat src_mat = opencv.get_mat();
    mat = src_mat(roi);

    return !mat.empty();
}

void mt2::WinApiWrapper::clear()
{
    DeleteObject(hb_window);
    DeleteDC(compatible_windowDC);
    ReleaseDC(hwnd, windowDC);
}

mt2::WinApiWrapper::~WinApiWrapper()
{
    clear();
}

