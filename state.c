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

/* Disable auto sleep (allow auto screen turnoff) */
void DisableAutoSleep(void)
{
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
}

/* Disable auto sleep and disable auto screen turnoff */
void DisableScreenTimeout(void)
{
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
}

/* Reset to default state */
void ResetToDefault(void)
{
    SetThreadExecutionState(ES_CONTINUOUS);
}
