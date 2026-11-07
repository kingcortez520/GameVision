#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat captureScreen()
{
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HDC screen = GetDC(nullptr);
    HDC memory = CreateCompatibleDC(screen);
    HBITMAP bitmap = CreateCompatibleBitmap(screen, width, height);
    HGDIOBJ old = SelectObject(memory, bitmap);

    BitBlt(memory, 0, 0, width, height, screen, 0, 0, SRCCOPY);

    BITMAPINFO info{};
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biHeight = -height;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;

    cv::Mat frame(height, width, CV_8UC4);
    GetDIBits(memory, bitmap, 0, height, frame.data, &info, DIB_RGB_COLORS);

    SelectObject(memory, old);
    DeleteObject(bitmap);
    DeleteDC(memory);
    ReleaseDC(nullptr, screen);

    cv::Mat output;
    cv::cvtColor(frame, output, cv::COLOR_BGRA2BGR);
    return output;
}

int main()
{
    std::cout << "GameVision started. Press ESC to exit.\n";

    cv::namedWindow("GameVision - Screen Capture", cv::WINDOW_NORMAL);

    while (true)
    {
        cv::Mat frame = captureScreen();

        if (frame.empty())
            continue;

        cv::resize(frame, frame, cv::Size(1280, 720));
        cv::putText(frame, "GameVision | Live Capture",
                    cv::Point(20, 35), cv::FONT_HERSHEY_SIMPLEX,
                    0.8, cv::Scalar(0, 255, 0), 2);

        cv::imshow("GameVision - Screen Capture", frame);

        if (cv::waitKey(1) == 27)
            break;
    }

    cv::destroyAllWindows();
    return 0;
}
