#include "lets_split.h"
#include "action_layer.h"


extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ARROW 5
#define _INTJ 6
#define _MODS 7
#define _DIVVY 8
#define _ADJUST 16

// IntelliJ Shortcuts
#define FNDFILE LSFT(LCTL(KC_N))
#define REFACTR LCTL(LALT(LSFT(KC_T)))
#define CLOSE LCTL(KC_F4)
#define HIDWINS LCTL(LSFT(KC_F12))
#define RUNTGTS LSFT(LALT(KC_F10))
#define RERUN LCTL(KC_F5)
#define EXECUTE LCTL(LSFT(KC_F10))
#define SYMBOL LSFT(LCTL(LALT(KC_N)))
#define DEBUG LCTL(LSFT(KC_F9))
#define END LCTL(KC_F2)
#define CREATE LALT(KC_INS)
#define FIND LCTL(LSFT(KC_F))
#define GO2TEST LCTL(LSFT(KC_T))
#define GIT LALT(KC_GRV)
#define MOREGIT LCTL(LALT(LSFT(KC_G)))
#define HIERARC LCTL(LALT(KC_H))
#define USAGES LALT(KC_F7)
#define MENU LALT(LSFT(KC_SCLN))
#define BACK LCTL(LALT(KC_LEFT))
#define FORWARD LCTL(LALT(KC_RGHT))
#define PREVMTD LALT(KC_UP)
#define NEXTMTD LALT(KC_DOWN)
#define FONT_DN LSFT(LCTL(LALT(KC_MINS)))
#define FONT_UP LSFT(LCTL(LALT(KC_EQL)))
#define FONTRES LSFT(LCTL(LALT(KC_SCLN)))
#define INFO LCTL(KC_F1)
#define OUTLINE LCTL(KC_F12)
#define PRVCHNG LCTL(LALT(LSFT(KC_UP)))
#define NXTCHNG LCTL(LALT(LSFT(KC_DOWN)))
#define EXT_VAR LCTL(LALT(KC_V))
#define ACEJUMP LCTL(LALT(KC_SCLN))
#define EXPLEFT LCTL(LSFT(KC_LEFT))
#define EXPDOWN LCTL(LSFT(KC_DOWN))
#define EXP_UP LCTL(LSFT(KC_UP))
#define EXPRGHT LCTL(LSFT(KC_RGHT))

// MacOS Navigation Shortcuts
#define ALTBSPC LALT(KC_BSPC)
#define ALTLEFT LALT(KC_LEFT)
#define ALTRGHT LALT(KC_RGHT)
#define GUILEFT LGUI(KC_LEFT)
#define GUIRGHT LGUI(KC_RGHT)
#define ALT_1 LALT(KC_1)
#define ALT_2 LALT(KC_2)
#define ALT_3 LALT(KC_3)
#define ALT_4 LALT(KC_4)
#define ALT_5 LALT(KC_5)
#define ALT_6 LALT(KC_6)
#define ALT_7 LALT(KC_7)
#define ALT_8 LALT(KC_8)
#define ALT_9 LALT(KC_9)
#define ALT_0 LALT(KC_0)
#define CTL_1 LCTL(LALT(KC_1))
#define CTL_2 LCTL(LALT(KC_2))
#define CTL_3 LCTL(LALT(KC_3))
#define CTL_4 LCTL(LALT(KC_4))
#define CTL_5 LCTL(LALT(KC_5))
#define CTL_6 LCTL(LALT(KC_6))
#define CTL_7 LCTL(LALT(KC_7))
#define CTL_8 LCTL(LALT(KC_8))
#define CTL_9 LCTL(LALT(KC_9))
#define CTL_0 LCTL(LALT(KC_0))
#define GUI_1 LGUI(KC_1)
#define GUI_2 LGUI(KC_2)
#define GUI_3 LGUI(KC_3)
#define GUI_4 LGUI(KC_4)
#define GUI_5 LGUI(KC_5)
#define GUI_6 LGUI(KC_6)
#define GUI_7 LGUI(KC_7)
#define GUI_8 LGUI(KC_8)
#define GUI_9 LGUI(KC_9)
#define GUI_0 LGUI(KC_0)

// DIVVY Shortcuts
#define TOPLEFT LGUI(LSFT(LCTL(KC_R)))
#define TOPHALF LGUI(LSFT(LCTL(KC_T)))
#define TOPRGHT LGUI(LSFT(LCTL(KC_Y)))
#define LFTHALF LGUI(LSFT(LCTL(KC_F)))
#define FULLSCR LGUI(LSFT(LCTL(KC_G)))
#define RGTHALF LGUI(LSFT(LCTL(KC_H)))
#define BOTLEFT LGUI(LSFT(LCTL(KC_V)))
#define BOTHALF LGUI(LSFT(LCTL(KC_B)))
#define BOTRGHT LGUI(LSFT(LCTL(KC_N)))

// SmallTalk Shortcuts
#define CALLERS LSFT(KC_F12)
#define CLASS LCTL(LSFT(KC_L))
#define IMPLS LSFT(KC_F11)
#define METHOD LCTL(LSFT(KC_M))
#define NEWVIEW LCTL(LSFT(KC_B))


enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    PW,
    MODS,
    DELMAIL,
    ARCMAIL,
    CALENDR,
    CHROME,
    FIREFOX,
    INTELIJ,
    ITERM,
    MAIL,
    ONENOTE,
    SLACK,
    SPOTIFY,
    TODOIST,
    UNANET,
    VMWARE,
    CLSVIEW
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define ARROW MO(_ARROW)
#define INTJ LT(MO(_INTJ), KC_F4)
#define MODS MO(_MODS)
#define ESCAPE LT(ARROW, KC_ESC)
#define D_DIVVY LT(MO(_DIVVY), KC_D)
#define MODKEYS LT(MODS, KC_DEL)

// @formatter:off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |   Tab   |    Q    |    W    |    E    |    R    |    T    |   |    Y    |    U    |    I    |    O    |    P    |   Bksp  |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |   Esc   |    A    |    S    |    D    |    F    |    G    |   |    H    |    J    |    K    |    L    |    ;    |    "    |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |  Shift  |    Z    |    X    |    C    |    V    |    B    |   |    N    |    M    |    ,    |    .    |    /    |  Enter  |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * | IntelliJ|   Ctrl  |   Alt   |   GUI   |  Lower  |  Space  |   |   Mods  |  Raise  |   Left  |   Down  |    Up   |  Right  |
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */

[_QWERTY] = LAYOUT( \
      KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC, \
      ESCAPE,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,         KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT, \
     KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,         KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,   KC_ENT, \
        INTJ,  KC_LCTL,  KC_LALT,  KC_LGUI,    LOWER,   KC_SPC,      MODKEYS,    RAISE,  KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |    ~    |    !    |    @    |    #    |    $    |    %    |   |     ^   |    &    |    *    |    (    |    )    |   Del   |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |   Del   |         |         |         |         |         |   |         |    _    |    +    |    {    |    }    |    |    |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         |         |         |         |   Play  |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |  Reset  |         |         |         |         |         |   |         |         | PrvTrack| VolumeDn| VolumeUp| NxtTrack|
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
     KC_TILD,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,      KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,   KC_DEL, \
      KC_DEL,  _______,  _______,  _______,  _______,  _______,      _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  KC_MPLY, \
       RESET,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT  \
),

/* Raise
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |    `    |    1    |    2    |    3    |    4    |    5    |   |    6    |    7    |    8    |    9    |    0    |   Del   |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |   Del   |         |         |         |         |         |   |         |    -    |    =    |    [    |    ]    |   \     |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         |         |         |         |  Reset  |
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
      KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,   KC_DEL, \
      KC_DEL,  _______,  _______,  _______,  _______,  _______,      _______,  KC_MINS,   KC_EQL,  KC_LBRC,  KC_RBRC,  KC_BSLS, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,    RESET  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |         |  Reset  |         |   Mail  |         | Todoist |   |  iTerm  |  Unanet | IntelliJ| OneNote |         |   Del   |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |  Slack  |         | Firefox |  Chrome |   |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         | Calendar|  VMWare |         |   |         | Spotify |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         |         |         |         |         |
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
     _______,    RESET,  _______,     MAIL,  _______,  TODOIST,        ITERM,   UNANET,  INTELIJ,  ONENOTE,  _______,   KC_DEL, \
     _______,  _______,    SLACK,  _______,  FIREFOX,   CHROME,      _______,  _______,  _______,  _______,  _______,  _______, \
     _______,  _______,  _______,  CALENDR,   VMWARE,  _______,      _______,  SPOTIFY,  _______,  _______,  _______,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______  \
),

/* Arrow (Hold Escape)
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |         |    F1   |    F2   |    F3   |    F4   |         |   | DelEmail|    Up   | ArcEmail|         |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |    F5   |    F6   |    F7   |    F8   |         |   |   Home  |   Left  |   Down  |  Right  |         |   MENU  |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |    F9   |   F10   |   F11   |   F12   |         |   |   End   |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         |         |         |         |         |
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */

[_ARROW] = LAYOUT( \
     _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,  _______,      _______,  DELMAIL,    KC_UP,  ARCMAIL,  _______,  _______, \
     _______,    KC_F5,    KC_F6,    KC_F7,    KC_F8,  _______,      KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  KC_MENU, \
     _______,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,       KC_END,  _______,  _______,  _______,  _______,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______  \
),

/* IntelliJ (Fn)
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |         |  Close  |         |   End   |  Refctr | Go2 Test|   |         |  Usages |  Prev_M |  Outlin |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |  HidWin |  RunMnu |  Symbol |  DbugIt |  Search |   Git   |   |  Hierar |   Prev  |  Next_M |   Next  |  FntRes |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |  ReRun  |  Run It |  Create | ExtctVar| More Git|   |   File  |   Menu  |  Font-  |  Font+  |   Info  |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         | Exp Left| Exp Down|  Exp Up | ExpRight|
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */

[_INTJ] = LAYOUT( \
     _______,    CLOSE,  _______,      END,  REFACTR,  GO2TEST,      _______,   USAGES,  PREVMTD,  OUTLINE,  _______,       PW, \
     HIDWINS,  RUNTGTS,   SYMBOL,    DEBUG,     FIND,      GIT,      HIERARC,     BACK,  NEXTMTD,  FORWARD,  FONTRES,  _______, \
     _______,    RERUN,  EXECUTE,   CREATE,  EXT_VAR,  MOREGIT,      FNDFILE,     MENU,  FONT_DN,  FONT_UP,     INFO,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  EXPLEFT,  EXPDOWN,   EXP_UP,  EXPRGHT  \
),

/* Mods
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |         |  Alt+1  |  Alt+2  |  Alt+3  |  Alt+4  |  Alt+5  |   |  Alt+6  |  Alt+7  |  Alt+8  |  Alt+9  |  Alt+0  |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |  Ctrl+1 |  Ctrl+2 |  Ctrl+3 |  Ctrl+4 |  Ctrl+5 |   |  Ctrl+6 |  Ctrl+7 |  Ctrl+8 |  Ctrl+9 |  Ctrl+0 |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |  Gui+1  |  Gui+2  |  Gui+3  |  Gui+4  |  Gui+5  |   |  Gui+6  |  Gui+7  |  Gui+8  |  Gui+9  |  Gui+0  |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         |         |         |         |         |
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */
[_MODS] =  LAYOUT( \
     _______,    ALT_1,    ALT_2,    ALT_3,    ALT_4,    ALT_5,        ALT_6,    ALT_7,    ALT_8,    ALT_9,    ALT_0,  _______, \
     _______,    CTL_1,    CTL_2,    CTL_3,    CTL_4,    CTL_5,        CTL_6,    CTL_7,    CTL_8,    CTL_9,    CTL_0,  _______, \
     _______,    GUI_1,    GUI_2,    GUI_3,    GUI_4,    GUI_5,        GUI_6,    GUI_7,    GUI_8,    GUI_9,    GUI_0,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______  \
),

/* Divvy
 * ,-----------------------------------------------------------.   ,-----------------------------------------------------------.
 * |         |         |         |         |         |         |   |         |    <^   |    ^^   |    ^>   |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |    <    |  FulScr |    >    |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |    <v   |    vv   |    v>   |         |         |
 * |---------+---------+---------+---------+---------+---------|   |---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |   |         |         |         |         |         |         |
 * `-----------------------------------------------------------'   `-----------------------------------------------------------'
 */
[_DIVVY] =  LAYOUT( \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  TOPLEFT,  TOPHALF,  TOPRGHT,  _______,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  LFTHALF,  FULLSCR,  RGTHALF,  _______,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  BOTLEFT,  BOTHALF,  BOTRGHT,  _______,  _______, \
     _______,  _______,  _______,  _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______  \
)

};

// @formatter:on

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PW:
            if (record->event.pressed) {
                SEND_STRING("PW_PLACEHOLDER");
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case DELMAIL:
            if (record->event.pressed) {
                SEND_STRING("x#");
            }
            return false;
        case ARCMAIL:
            if (record->event.pressed) {
                SEND_STRING("xE");
            }
            return false;
        case SLACK:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("slack"
                SS_TAP(X_ENTER));
            }
            return false;
        case CALENDR:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("calendar"
                SS_TAP(X_ENTER));
            }
            return false;
        case FIREFOX:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("firefox"
                SS_TAP(X_ENTER));
            }
            return false;
        case MAIL:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("mail"
                SS_TAP(X_ENTER));
            }
            return false;
        case TODOIST:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("todoist-native"
                SS_TAP(X_ENTER));
            }
            return false;
        case CHROME:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("chrome"
                SS_TAP(X_ENTER));
            }
            return false;
        case UNANET:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("unanet"
                SS_TAP(X_ENTER));
            }
            return false;
        case SPOTIFY:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("spotify"
                SS_TAP(X_ENTER));
            }
            return false;
        case ITERM:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("iterm"
                SS_TAP(X_ENTER));
            }
            return false;
        case ONENOTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("onenote"
                SS_TAP(X_ENTER));
            }
            return false;
        case INTELIJ:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("intellij"
                SS_TAP(X_ENTER));
            }
            return false;
        case VMWARE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("vmware"
                SS_TAP(X_ENTER));
            }
            return false;
        case CLSVIEW:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F10));
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_RIGHT));
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_RIGHT));
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_RIGHT));
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_DOWN));
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_DOWN));
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
    }
    return true;
}

/* Layer Name
 * ,-----------------------------------------------------.      ,-----------------------------------------------------.
 * |        |        |        |        |        |        |      |        |        |        |        |        |        |
 * |---------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |      |        |        |        |        |        |        |
 * |---------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |      |        |        |        |        |        |        |
 * |---------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |      |        |        |        |        |        |        |
 * `-----------------------------------------------------'      `-----------------------------------------------------'
 */

/*
[_LAYER] =  LAYOUT( \
    _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______  \
)
*/
