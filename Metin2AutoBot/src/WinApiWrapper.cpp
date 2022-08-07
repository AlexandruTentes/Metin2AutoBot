#include "header/WinApiWrapper.h"

void mt2::WinApiWrapper::init()
{

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

        //Get the dimensions of the focused window;
        GetWindowRect(hwnd, &(rect));
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;

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

    screen_x = rect.bottom;
    screen_y = rect.right;
    width = rect.bottom / scale;
    height = rect.right / scale;

    std::cout << rect.left << "--" << rect.right  << "--" << rect.top << "--" << rect.bottom << "\n";

    mat.create(height, width, CV_8UC4);

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

    StretchBlt(compatible_windowDC, 0, 0, width, height, windowDC, 0, 0, screen_x, screen_y, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(compatible_windowDC, hb_window, 0, height, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

    return !mat.empty();
}

Mat mt2::WinApiWrapper::get_mat()
{
    return mat;
}

mt2::WinApiWrapper::~WinApiWrapper()
{
    DeleteObject(hb_window);
    DeleteDC(compatible_windowDC);
    ReleaseDC(hwnd, windowDC);
}

