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

#ifndef NOSLEEP_H_INCLUDED
#define NOSLEEP_H_INCLUDED

#define _UNICODE
#define UNICODE

#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <commctrl.h>

/* Fix compile error for MinGW32 */
#ifndef ICC_STANDARD_CLASSES
#define ICC_STANDARD_CLASSES 0x00004000
#endif // ICC_STANDARD_CLASSES

#include "resource.h"

/* State functions */
void DisableAutoSleep(void);
void DisableScreenTimeout(void);
void ResetToDefault(void);

/* Controls functions */
HWND CreateButton(HWND hwndParent, LPCWSTR text, HFONT font, int posX, int posY, int width, int height, UINT id);
void PlayButtonClickSound(void);
HWND CreateTextLabel(HWND hwndParent, LPCWSTR text, HFONT font, int posX, int posY, int width, int height);
void SetLabelText(HWND hwndTextLabel, LPCWSTR newText);

/* GUI fonts functions */
void InitGUIFonts(void);
void UninitGUIFonts(void);
HFONT GetLargeGUIFont(void);
HFONT GetSmallGUIFont(void);

#endif // NOSLEEP_H_INCLUDED
