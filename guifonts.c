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

/* GUI fonts data */
static HFONT hGUIFontL = NULL;
static HFONT hGUIFontS = NULL;
static BOOL bFallbackGUIFonts = FALSE;

void
InitGUIFonts(void)
{
    hGUIFontL = CreateFontW(-14,
                            0,
                            0,
                            0,
                            FW_REGULAR,
                            0,
                            0,
                            0,
                            DEFAULT_CHARSET,
                            OUT_OUTLINE_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            VARIABLE_PITCH,
                            L"Tahoma");
    hGUIFontS = CreateFontW(-12,
                            0,
                            0,
                            0,
                            FW_REGULAR,
                            0,
                            0,
                            0,
                            DEFAULT_CHARSET,
                            OUT_OUTLINE_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            VARIABLE_PITCH,
                            L"Tahoma");
    if (!hGUIFontL || !hGUIFontS)
    {
        if (hGUIFontL)
            DeleteObject(hGUIFontL);

        if (hGUIFontS)
            DeleteObject(hGUIFontS);

        hGUIFontL = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        hGUIFontS = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

        bFallbackGUIFonts = TRUE;
    }
}

void
UninitGUIFonts(void)
{
    if (!bFallbackGUIFonts)
    {
        DeleteObject(hGUIFontL);
        DeleteObject(hGUIFontS);
    }
}

HFONT
GetLargeGUIFont(void)
{
    return hGUIFontL;
}

HFONT
GetSmallGUIFont(void)
{
    return hGUIFontS;
}
