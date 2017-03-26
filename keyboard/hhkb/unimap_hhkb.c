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
make -f Makefile.unimap  # should create unimap_hhkb.hex
sudo make -f Makefile.unimap dfu
# press reset button on keyboard
# should flash unimap_hhkb.hex to the keyboard

*/
#include "unimap_trans.h"

/* id for user defined functions */
enum function_id {
    LSHIFT_LPAREN,
};

enum macro_id {
    HELLO,
    VOLUP,
    ALT_TAB,
};

/* AC_SPC2: tapping spacebar sends SPACE but long hold shifts to Layer 2 */
/* AC_TAB3: tapping the tab key sends TAB but long hold shifts to Layer 3 */
#define AC_L1      ACTION_LAYER_MOMENTARY(1)
#define AC_SPC2    ACTION_LAYER_TAP_KEY(2, KC_SPC)
#define AC_TAB3    ACTION_LAYER_TAP_KEY(3, KC_TAB)
#define AC_APSW    ACTION_MACRO(ALT_TAB)
#define AC_BACK    ACTION_MODS_KEY(MOD_LALT, KC_LEFT)
#define AC_FRWD    ACTION_MODS_KEY(MOD_LALT, KC_RIGHT)


#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    /* Basic HHKB Macintosh mode QWERTY layer (SW1 OFF, SW2 ON), except
     *   - GUI and ALT keys are switched (SW5 ON)
     *   - RGUI is a control key (no DIP switch equivalent)
     *   - space bar activates layer 2 if it's held down
     * The first modification (GUI and ALT keys switched) can be done by
     * using the virtual DIP switches / boot magic configuration, but why
     * not make burn it in?
     */
    [0] = UNIMAP_HHKB(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV,
    TAB3,Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSPC,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,          ENT,
    LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,L1,
         LGUI,LALT,               SPC2,                    RALT,RCTL),

    /* HHKB function layer that matches what's on the key labels, in case
     * someone wishes to rely on them. No change from Hasu's version.
     */
    [1] = UNIMAP_HHKB(
    PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,
    CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,UP,  TRNS,     TRNS,
    TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,          PENT,
    TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,     TRNS,TRNS,
         TRNS,TRNS,               TRNS,                    TRNS,TRNS),

    /* Custom layer, based on Hasu's layer 2. Note that he holds the slash
     * key down to get into his layer 2, so he is allowed to transmit SPC
     * on the space bar. Since we're using SPACE to get into this layer, it
     * needs to be transparent instead of transmitting SPC. Otherwise we
     * could end up getting stuck in this layer (I think that's what happened)
     *   - arrow keys at HJKL (like vim)
     *   - arrow keys at ASDF (rather than WASD: it's how I used to game)
     *   - HOME, PGUP, PGDN, and END keys positioned around these arrow keys
     */
    [2] = UNIMAP_HHKB(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,
    NO,  HOME,PGDN,PGUP,END ,NO,  HOME,PGDN,PGUP,END, NO,  NO,  NO,       BSPC,
    LCTL,LEFT,DOWN,UP  ,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,            ENT,
    LSFT,     NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, NO,  NO,       RSFT,TRNS,
         LGUI,LALT,               TRNS,                    RALT,RCTL),

    /* Mousing layer, based on Hasu's layer 3. Mouse movement shifted to use
     * the HJKL keys.
     *   - since I get into this by holding down TAB, make that key transparent
     *     else we'll get stuck in this layer
     */
    [3] = UNIMAP_HHKB(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,
    TRNS,NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,       APSW,
    LCTL,NO,  NO,  NO,  NO,  NO,  MS_L,MS_D,MS_U,MS_R,BACK,FRWD,          ENT,
    LSFT,     NO,  NO,  NO,  NO,  NO,  NO,  BTN1,BTN3,BTN2,NO,       RSFT,TRNS,
         TRNS,TRNS,               BTN1,                    TRNS,TRNS),
};


/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case HELLO:
            return (record->event.pressed ?
                    MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
        case VOLUP:
            return (record->event.pressed ?
                    MACRO( D(VOLU), U(VOLU), END ) :
                    MACRO_NONE );
        case ALT_TAB:
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}



/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    dprintf("%d", record->tap.count);
    if (record->tap.interrupted) dprint("i");
    dprint("\n");

    switch (id) {
        case LSHIFT_LPAREN:
            // Shift parentheses example: LShft + tap '('
            // http://stevelosh.com/blog/2012/10/a-modern-space-cadet/#shift-parentheses
            // http://geekhack.org/index.php?topic=41989.msg1304899#msg1304899
            if (record->event.pressed) {
                if (record->tap.count > 0 && !record->tap.interrupted) {
                    if (record->tap.interrupted) {
                        dprint("tap interrupted\n");
                        register_mods(MOD_BIT(KC_LSHIFT));
                    }
                } else {
                    register_mods(MOD_BIT(KC_LSHIFT));
                }
            } else {
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
                    add_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    register_code(KC_9);
                    unregister_code(KC_9);
                    del_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    record->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_LSHIFT));
                }
            }
            break;
    }
}
