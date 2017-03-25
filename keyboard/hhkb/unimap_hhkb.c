/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

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

N.B: Keymap modified by WJY. For original, see git repository / history.
What's different from the original unimap_hhkb.c:
- switched ALT and GUI keys
- RGUI is now RCTL because Fedora 25 doesn't use it, and I miss having a
  control key on that side of the keyboard
- SpaceFn: holding down the spacebar switches to Layer 2
- Layer 2 has arrow keys in HJKL, among other things

To make the hexfile and program the keyboard:
make -f Makefile.hhkb  # should create unimap_hhkb.hex
sudo make dfu
# press reset button on keyboard
# should flash unimap_hhkb.hex to the keyboard

*/
#include "unimap_trans.h"


/*
 * AC_SPC4: implement SpaceFn, meaning tap on the spacebar sends SPACE,
 *          but long hold shifts to Layer 2
 */
#define AC_L1       ACTION_LAYER_MOMENTARY(1)
#define AC_SPC2     ACTION_LAYER_TAP_KEY(2, KC_SPC)


#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    [0] = UNIMAP_HHKB(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSPC,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,          ENT,
    LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,L1,
         LGUI,LALT,               SPC2,                    RALT,RCTL),

    [1] = UNIMAP_HHKB(
    PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,
    CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,UP,  TRNS,     TRNS,
    TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,          PENT,
    TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,     TRNS,TRNS,
         TRNS,TRNS,               TRNS,                    TRNS,TRNS),

    [2] = UNIMAP_HHKB(
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,PGDN,PGUP,END, TRNS,TRNS,TRNS,     TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,LEFT,DOWN,UP,  RGHT,TRNS,TRNS,          TRNS,
    TRNS,     TRNS,TRNS,TRNS,TRNS,HOME,PGDN,PGUP,END, TRNS,TRNS,     TRNS,TRNS,
         TRNS,TRNS,               TRNS,                    TRNS,TRNS),
};
