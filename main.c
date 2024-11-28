/* NoSleep - A simple Windows program that prevents your computer from going
 * to sleep automatically, without changing system configurations.
 *
 * Copyright (C) 2024 Thamatip Chitpong <tangaming123456@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "nosleep.h"

/* Controls ID */
enum controlsID
{
    idBtnDisAutSlp = 1,
    idBtnDisScrTo = 2,
    idBtnReset = 3,
    idBtnExit = 4
};

/* Controls HWND */
static HWND hwndWinMain = NULL;
static HWND hwndBtnDisAutSlp = NULL;
static HWND hwndBtnDisScrTo = NULL;
static HWND hwndBtnReset = NULL;
static HWND hwndBtnExit = NULL;
static HWND hwndLabelSt = NULL;

static LRESULT CALLBACK
MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            ResetToDefault();
            PostQuitMessage(0);
            return 0;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case idBtnDisAutSlp:
                {
                    PlayButtonClickSound();
                    DisableAutoSleep();
                    SetLabelText(hwndLabelSt, L"Status : Disable auto sleep");
                    break;
                }

                case idBtnDisScrTo:
                {
                    PlayButtonClickSound();
                    DisableScreenTimeout();
                    SetLabelText(hwndLabelSt, L"Status : Disable auto sleep and keep screen ON");
                    break;
                }

                case idBtnReset:
                {
                    PlayButtonClickSound();
                    ResetToDefault();
                    SetLabelText(hwndLabelSt, L"Status : Default");
                    break;
                }

                case idBtnExit:
                    DestroyWindow(hWnd);
                    break;
            }

            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            /* NOTE: All painting occurs here, between BeginPaint and EndPaint */
            FillRect(hdc, &ps.rcPaint, (HBRUSH)COLOR_WINDOW);

            EndPaint(hWnd, &ps);
            break;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/* WinMain entry point */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static const WCHAR className[] = L"NoSleep";
    static const WCHAR winTitle[] = L"No Sleep";

    /* Single instance */
    HWND hPrevWindow = FindWindowW(className, winTitle);
    if (hPrevWindow)
    {
        ShowWindow(hPrevWindow, SW_SHOW);
        return 0;
    }

    /* Enable visual styles */
    INITCOMMONCONTROLSEX icex;
    ZeroMemory(&icex, sizeof(icex));
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&icex);

    WNDCLASSEXW wc;
    MSG msg;

    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.cbSize = sizeof(wc);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.style = 0;
    wc.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_APPICON));
    wc.hIconSm = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_APPICON));
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszMenuName  = NULL;

    /* Register the window class */
    if (!RegisterClassExW(&wc))
    {
        MessageBoxW(NULL, L"Window Registration Failed", L"Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    /* Window width and height */
    int winWidth = 330;
    int winHeight = 220;

    /* Calculate window start position (screen center) */
    int winPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - (winWidth / 2);
    int winPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - (winHeight / 2);

    /* Create main window */
    hwndWinMain = CreateWindowExW(WS_EX_WINDOWEDGE,
                                  className,
                                  winTitle,
                                  WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // No resize
                                  winPosX,
                                  winPosY,
                                  winWidth,
                                  winHeight,
                                  NULL,
                                  NULL,
                                  hInstance,
                                  NULL);
    if (!hwndWinMain)
    {
        MessageBoxW(NULL, L"Window Creation Failed", L"Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    ShowWindow(hwndWinMain, nShowCmd);
    UpdateWindow(hwndWinMain);

    InitGUIFonts();

    /* "Disable Auto Sleep" button */
    hwndBtnDisAutSlp = CreateButton(hwndWinMain,
                                    L"Disable Auto Sleep",
                                    GetLargeGUIFont(),
                                    10,  // Position X
                                    10,  // Position Y
                                    140, // Width
                                    30,  // Height
                                    idBtnDisAutSlp);

    /* "Keep Screen ON" button */
    hwndBtnDisScrTo = CreateButton(hwndWinMain,
                                   L"Keep Screen ON",
                                   GetLargeGUIFont(),
                                   170, // Position X
                                   10,  // Position Y
                                   140, // Width
                                   30,  // Height
                                   idBtnDisScrTo);

    /* "Reset" button */
    hwndBtnReset = CreateButton(hwndWinMain,
                                L"Reset",
                                GetLargeGUIFont(),
                                10,  // Position X
                                50,  // Position Y
                                300, // Width
                                30,  // Height
                                idBtnReset);

    /* Status text label */
    hwndLabelSt = CreateTextLabel(hwndWinMain,
                                  L"Status : Default",
                                  GetLargeGUIFont(),
                                  15,  // Position X
                                  100, // Position Y
                                  300, // Width
                                  25); // Height

    /* "Exit" button */
    hwndBtnExit = CreateButton(hwndWinMain,
                               L"Exit",
                               GetSmallGUIFont(),
                               210, // Position X
                               150, // Position Y
                               100, // Width
                               25,  // Height
                               idBtnExit);

    /* Run the message loop */
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessage(hwndWinMain, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UninitGUIFonts();

    return 0;
}
