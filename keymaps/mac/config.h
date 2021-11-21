/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

//#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define USE_SERIAL_PD2

//#define RETRO_TAPPING
//#define PERMISSIVE_HOLD
#define TAPPING_TERM 0
#define TAPPING_TERM_CUSTOM 500
#define RETRO_TAPPING

#ifdef MOUSEKEY_ENABLE
#    undef MOUSEKEY_MAX_SPEED
#    define MOUSEKEY_MAX_SPEED 3

#    undef MOUSEKEY_WHEEL_MAX_SPEED
#    define MOUSEKEY_WHEEL_MAX_SPEED 1
#endif  //MOUSEKEY_ENABLE


