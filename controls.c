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

HWND
CreateButton(HWND hwndParent, LPCWSTR text, HFONT font, int posX, int posY, int width, int height, UINT id)
{
    HWND hWnd = CreateWindowW(L"Button", // Predefined class
                              text,
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                              posX,
                              posY,
                              width,
                              height,
                              hwndParent,
                              (HMENU)(UINT_PTR)id,
                              NULL,
                              NULL);
    if (hWnd)
    {
        SendMessageW(hWnd, WM_SETFONT, (WPARAM)font, (LPARAM)TRUE);
    }

    return hWnd;
}

void
PlayButtonClickSound(void)
{
    PlaySoundW(MAKEINTRESOURCEW(IDW_BTNCLICK), GetModuleHandleW(NULL), SND_RESOURCE | SND_ASYNC);
}

HWND
CreateTextLabel(HWND hwndParent, LPCWSTR text, HFONT font, int posX, int posY, int width, int height)
{
    HWND hWnd = CreateWindowW(L"Static", // Predefined class
                              text,
                              WS_CHILD | WS_VISIBLE | SS_LEFT,
                              posX,
                              posY,
                              width,
                              height,
                              hwndParent,
                              NULL, // No ID
                              NULL,
                              NULL);
    if (hWnd)
    {
        SendMessageW(hWnd, WM_SETFONT, (WPARAM)font, (LPARAM)TRUE);
    }

    return hWnd;
}

void
SetLabelText(HWND hwndTextLabel, LPCWSTR newText)
{
    SendMessageW(hwndTextLabel, WM_SETTEXT, 0, (LPARAM)newText);
}
