/**
 * ISOENGINE
 * engine.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_ISOENGINE_H__
#define __ISOENGINE_ISOENGINE_H__

#include <stdint.h>
#include <stdlib.h>

typedef enum isoengine_scancode
{
    ISO_SCANCODE_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    ISO_SCANCODE_A = 4,
    ISO_SCANCODE_B = 5,
    ISO_SCANCODE_C = 6,
    ISO_SCANCODE_D = 7,
    ISO_SCANCODE_E = 8,
    ISO_SCANCODE_F = 9,
    ISO_SCANCODE_G = 10,
    ISO_SCANCODE_H = 11,
    ISO_SCANCODE_I = 12,
    ISO_SCANCODE_J = 13,
    ISO_SCANCODE_K = 14,
    ISO_SCANCODE_L = 15,
    ISO_SCANCODE_M = 16,
    ISO_SCANCODE_N = 17,
    ISO_SCANCODE_O = 18,
    ISO_SCANCODE_P = 19,
    ISO_SCANCODE_Q = 20,
    ISO_SCANCODE_R = 21,
    ISO_SCANCODE_S = 22,
    ISO_SCANCODE_T = 23,
    ISO_SCANCODE_U = 24,
    ISO_SCANCODE_V = 25,
    ISO_SCANCODE_W = 26,
    ISO_SCANCODE_X = 27,
    ISO_SCANCODE_Y = 28,
    ISO_SCANCODE_Z = 29,

    ISO_SCANCODE_1 = 30,
    ISO_SCANCODE_2 = 31,
    ISO_SCANCODE_3 = 32,
    ISO_SCANCODE_4 = 33,
    ISO_SCANCODE_5 = 34,
    ISO_SCANCODE_6 = 35,
    ISO_SCANCODE_7 = 36,
    ISO_SCANCODE_8 = 37,
    ISO_SCANCODE_9 = 38,
    ISO_SCANCODE_0 = 39,

    ISO_SCANCODE_RETURN = 40,
    ISO_SCANCODE_ESCAPE = 41,
    ISO_SCANCODE_BACKSPACE = 42,
    ISO_SCANCODE_TAB = 43,
    ISO_SCANCODE_SPACE = 44,

    ISO_SCANCODE_MINUS = 45,
    ISO_SCANCODE_EQUALS = 46,
    ISO_SCANCODE_LEFTBRACKET = 47,
    ISO_SCANCODE_RIGHTBRACKET = 48,
    ISO_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    ISO_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementer, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate ISO_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because ISO
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    ISO_SCANCODE_SEMICOLON = 51,
    ISO_SCANCODE_APOSTROPHE = 52,
    ISO_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    ISO_SCANCODE_COMMA = 54,
    ISO_SCANCODE_PERIOD = 55,
    ISO_SCANCODE_SLASH = 56,

    ISO_SCANCODE_CAPSLOCK = 57,

    ISO_SCANCODE_F1 = 58,
    ISO_SCANCODE_F2 = 59,
    ISO_SCANCODE_F3 = 60,
    ISO_SCANCODE_F4 = 61,
    ISO_SCANCODE_F5 = 62,
    ISO_SCANCODE_F6 = 63,
    ISO_SCANCODE_F7 = 64,
    ISO_SCANCODE_F8 = 65,
    ISO_SCANCODE_F9 = 66,
    ISO_SCANCODE_F10 = 67,
    ISO_SCANCODE_F11 = 68,
    ISO_SCANCODE_F12 = 69,

    ISO_SCANCODE_PRINTSCREEN = 70,
    ISO_SCANCODE_SCROLLLOCK = 71,
    ISO_SCANCODE_PAUSE = 72,
    ISO_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    ISO_SCANCODE_HOME = 74,
    ISO_SCANCODE_PAGEUP = 75,
    ISO_SCANCODE_DELETE = 76,
    ISO_SCANCODE_END = 77,
    ISO_SCANCODE_PAGEDOWN = 78,
    ISO_SCANCODE_RIGHT = 79,
    ISO_SCANCODE_LEFT = 80,
    ISO_SCANCODE_DOWN = 81,
    ISO_SCANCODE_UP = 82,

    ISO_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    ISO_SCANCODE_KP_DIVIDE = 84,
    ISO_SCANCODE_KP_MULTIPLY = 85,
    ISO_SCANCODE_KP_MINUS = 86,
    ISO_SCANCODE_KP_PLUS = 87,
    ISO_SCANCODE_KP_ENTER = 88,
    ISO_SCANCODE_KP_1 = 89,
    ISO_SCANCODE_KP_2 = 90,
    ISO_SCANCODE_KP_3 = 91,
    ISO_SCANCODE_KP_4 = 92,
    ISO_SCANCODE_KP_5 = 93,
    ISO_SCANCODE_KP_6 = 94,
    ISO_SCANCODE_KP_7 = 95,
    ISO_SCANCODE_KP_8 = 96,
    ISO_SCANCODE_KP_9 = 97,
    ISO_SCANCODE_KP_0 = 98,
    ISO_SCANCODE_KP_PERIOD = 99,

    ISO_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Z.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    ISO_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    ISO_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    ISO_SCANCODE_KP_EQUALS = 103,
    ISO_SCANCODE_F13 = 104,
    ISO_SCANCODE_F14 = 105,
    ISO_SCANCODE_F15 = 106,
    ISO_SCANCODE_F16 = 107,
    ISO_SCANCODE_F17 = 108,
    ISO_SCANCODE_F18 = 109,
    ISO_SCANCODE_F19 = 110,
    ISO_SCANCODE_F20 = 111,
    ISO_SCANCODE_F21 = 112,
    ISO_SCANCODE_F22 = 113,
    ISO_SCANCODE_F23 = 114,
    ISO_SCANCODE_F24 = 115,
    ISO_SCANCODE_EXECUTE = 116,
    ISO_SCANCODE_HELP = 117,    /**< AL Integrated Help Center */
    ISO_SCANCODE_MENU = 118,    /**< Menu (show menu) */
    ISO_SCANCODE_SELECT = 119,
    ISO_SCANCODE_STOP = 120,    /**< AC Stop */
    ISO_SCANCODE_AGAIN = 121,   /**< AC Redo/Repeat */
    ISO_SCANCODE_UNDO = 122,    /**< AC Undo */
    ISO_SCANCODE_CUT = 123,     /**< AC Cut */
    ISO_SCANCODE_COPY = 124,    /**< AC Copy */
    ISO_SCANCODE_PASTE = 125,   /**< AC Paste */
    ISO_SCANCODE_FIND = 126,    /**< AC Find */
    ISO_SCANCODE_MUTE = 127,
    ISO_SCANCODE_VOLUMEUP = 128,
    ISO_SCANCODE_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     ISO_SCANCODE_LOCKINGCAPSLOCK = 130,  */
/*     ISO_SCANCODE_LOCKINGNUMLOCK = 131, */
/*     ISO_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    ISO_SCANCODE_KP_COMMA = 133,
    ISO_SCANCODE_KP_EQUALSAS400 = 134,

    ISO_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    ISO_SCANCODE_INTERNATIONAL2 = 136,
    ISO_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    ISO_SCANCODE_INTERNATIONAL4 = 138,
    ISO_SCANCODE_INTERNATIONAL5 = 139,
    ISO_SCANCODE_INTERNATIONAL6 = 140,
    ISO_SCANCODE_INTERNATIONAL7 = 141,
    ISO_SCANCODE_INTERNATIONAL8 = 142,
    ISO_SCANCODE_INTERNATIONAL9 = 143,
    ISO_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    ISO_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    ISO_SCANCODE_LANG3 = 146, /**< Katakana */
    ISO_SCANCODE_LANG4 = 147, /**< Hiragana */
    ISO_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    ISO_SCANCODE_LANG6 = 149, /**< reserved */
    ISO_SCANCODE_LANG7 = 150, /**< reserved */
    ISO_SCANCODE_LANG8 = 151, /**< reserved */
    ISO_SCANCODE_LANG9 = 152, /**< reserved */

    ISO_SCANCODE_ALTERASE = 153,    /**< Erase-Eaze */
    ISO_SCANCODE_SYSREQ = 154,
    ISO_SCANCODE_CANCEL = 155,      /**< AC Cancel */
    ISO_SCANCODE_CLEAR = 156,
    ISO_SCANCODE_PRIOR = 157,
    ISO_SCANCODE_RETURN2 = 158,
    ISO_SCANCODE_SEPARATOR = 159,
    ISO_SCANCODE_OUT = 160,
    ISO_SCANCODE_OPER = 161,
    ISO_SCANCODE_CLEARAGAIN = 162,
    ISO_SCANCODE_CRSEL = 163,
    ISO_SCANCODE_EXSEL = 164,

    ISO_SCANCODE_KP_00 = 176,
    ISO_SCANCODE_KP_000 = 177,
    ISO_SCANCODE_THOUSANDSSEPARATOR = 178,
    ISO_SCANCODE_DECIMALSEPARATOR = 179,
    ISO_SCANCODE_CURRENCYUNIT = 180,
    ISO_SCANCODE_CURRENCYSUBUNIT = 181,
    ISO_SCANCODE_KP_LEFTPAREN = 182,
    ISO_SCANCODE_KP_RIGHTPAREN = 183,
    ISO_SCANCODE_KP_LEFTBRACE = 184,
    ISO_SCANCODE_KP_RIGHTBRACE = 185,
    ISO_SCANCODE_KP_TAB = 186,
    ISO_SCANCODE_KP_BACKSPACE = 187,
    ISO_SCANCODE_KP_A = 188,
    ISO_SCANCODE_KP_B = 189,
    ISO_SCANCODE_KP_C = 190,
    ISO_SCANCODE_KP_D = 191,
    ISO_SCANCODE_KP_E = 192,
    ISO_SCANCODE_KP_F = 193,
    ISO_SCANCODE_KP_XOR = 194,
    ISO_SCANCODE_KP_POWER = 195,
    ISO_SCANCODE_KP_PERCENT = 196,
    ISO_SCANCODE_KP_LESS = 197,
    ISO_SCANCODE_KP_GREATER = 198,
    ISO_SCANCODE_KP_AMPERSAND = 199,
    ISO_SCANCODE_KP_DBLAMPERSAND = 200,
    ISO_SCANCODE_KP_VERTICALBAR = 201,
    ISO_SCANCODE_KP_DBLVERTICALBAR = 202,
    ISO_SCANCODE_KP_COLON = 203,
    ISO_SCANCODE_KP_HASH = 204,
    ISO_SCANCODE_KP_SPACE = 205,
    ISO_SCANCODE_KP_AT = 206,
    ISO_SCANCODE_KP_EXCLAM = 207,
    ISO_SCANCODE_KP_MEMSTORE = 208,
    ISO_SCANCODE_KP_MEMRECALL = 209,
    ISO_SCANCODE_KP_MEMCLEAR = 210,
    ISO_SCANCODE_KP_MEMADD = 211,
    ISO_SCANCODE_KP_MEMSUBTRACT = 212,
    ISO_SCANCODE_KP_MEMMULTIPLY = 213,
    ISO_SCANCODE_KP_MEMDIVIDE = 214,
    ISO_SCANCODE_KP_PLUSMINUS = 215,
    ISO_SCANCODE_KP_CLEAR = 216,
    ISO_SCANCODE_KP_CLEARENTRY = 217,
    ISO_SCANCODE_KP_BINARY = 218,
    ISO_SCANCODE_KP_OCTAL = 219,
    ISO_SCANCODE_KP_DECIMAL = 220,
    ISO_SCANCODE_KP_HEXADECIMAL = 221,

    ISO_SCANCODE_LCTRL = 224,
    ISO_SCANCODE_LSHIFT = 225,
    ISO_SCANCODE_LALT = 226, /**< alt, option */
    ISO_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    ISO_SCANCODE_RCTRL = 228,
    ISO_SCANCODE_RSHIFT = 229,
    ISO_SCANCODE_RALT = 230, /**< alt gr, option */
    ISO_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

    ISO_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special ISO_KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     *
     *  There are way more keys in the spec than we can represent in the
     *  current scancode range, so pick the ones that commonly come up in
     *  real world usage.
     */
    /* @{ */

    ISO_SCANCODE_SLEEP = 258,                   /**< Sleep */
    ISO_SCANCODE_WAKE = 259,                    /**< Wake */

    ISO_SCANCODE_CHANNEL_INCREMENT = 260,       /**< Channel Increment */
    ISO_SCANCODE_CHANNEL_DECREMENT = 261,       /**< Channel Decrement */

    ISO_SCANCODE_MEDIA_PLAY = 262,          /**< Play */
    ISO_SCANCODE_MEDIA_PAUSE = 263,         /**< Pause */
    ISO_SCANCODE_MEDIA_RECORD = 264,        /**< Record */
    ISO_SCANCODE_MEDIA_FAST_FORWARD = 265,  /**< Fast Forward */
    ISO_SCANCODE_MEDIA_REWIND = 266,        /**< Rewind */
    ISO_SCANCODE_MEDIA_NEXT_TRACK = 267,    /**< Next Track */
    ISO_SCANCODE_MEDIA_PREVIOUS_TRACK = 268, /**< Previous Track */
    ISO_SCANCODE_MEDIA_STOP = 269,          /**< Stop */
    ISO_SCANCODE_MEDIA_EJECT = 270,         /**< Eject */
    ISO_SCANCODE_MEDIA_PLAY_PAUSE = 271,    /**< Play / Pause */
    ISO_SCANCODE_MEDIA_SELECT = 272,        /* Media Select */

    ISO_SCANCODE_AC_NEW = 273,              /**< AC New */
    ISO_SCANCODE_AC_OPEN = 274,             /**< AC Open */
    ISO_SCANCODE_AC_CLOSE = 275,            /**< AC Close */
    ISO_SCANCODE_AC_EXIT = 276,             /**< AC Exit */
    ISO_SCANCODE_AC_SAVE = 277,             /**< AC Save */
    ISO_SCANCODE_AC_PRINT = 278,            /**< AC Print */
    ISO_SCANCODE_AC_PROPERTIES = 279,       /**< AC Properties */

    ISO_SCANCODE_AC_SEARCH = 280,           /**< AC Search */
    ISO_SCANCODE_AC_HOME = 281,             /**< AC Home */
    ISO_SCANCODE_AC_BACK = 282,             /**< AC Back */
    ISO_SCANCODE_AC_FORWARD = 283,          /**< AC Forward */
    ISO_SCANCODE_AC_STOP = 284,             /**< AC Stop */
    ISO_SCANCODE_AC_REFRESH = 285,          /**< AC Refresh */
    ISO_SCANCODE_AC_BOOKMARKS = 286,        /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */


    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
    /* @{ */

    ISO_SCANCODE_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    ISO_SCANCODE_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    ISO_SCANCODE_CALL = 289, /**< Used for accepting phone calls. */
    ISO_SCANCODE_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

    ISO_SCANCODE_RESERVED = 400,    /**< 400-500 reserved for dynamic keycodes */

    ISO_SCANCODE_COUNT = 512 /**< not a key, just marks the number of scancodes for array bounds */

} ISO_Scancode;

typedef struct isoengine_3dcoords {
    double x;
    double y;
    double z;
} isoengine_3dcoords;

typedef struct isoengine_2dcoords {
    double x;
    double y;
} isoengine_2dcoords;

/**
 * A function pointer type for a callback that handles key press events in an isometric engine, taking a starting position (startx, starty),
 * output pointers for the resulting end position (endx, endy), and an isoengine_keycode indicating which key was pressed.
 * This callback pattern allows the engine to compute a new position based on the original coordinates and the specific key input,
 * writing the result back through the endx and endy pointers.
 */
typedef isoengine_3dcoords (*isoengine_object3d_keypress_callback_func)(const isoengine_3dcoords *const current_coords, const ISO_Scancode keycode);
typedef isoengine_2dcoords (*isoengine_object2d_keypress_callback_func)(const isoengine_2dcoords *const current_coords, const bool *const keys, double dt);

/**
 * Creates and initializes a new instance of an isometric engine, returning an opaque pointer to the newly created engine object.
 * The caller is responsible for managing the lifetime of the returned object and should release it with the corresponding
 * destroy function when it is no longer needed.
 */
void *isoengine_create();

/**
 * Destroys an isometric engine instance and releases its associated resources.
 * Returns true if the engine was successfully destroyed, or false if the operation failed (e.g., if the provided engine pointer is invalid or NULL).
 */
bool isoengine_destroy(void *engine);

/**
 * isoengine_handle_events processes and dispatches pending events (such as input or system events) for the given isometric engine instance.
 * It returns true if the engine should continue running, or false if a quit/shutdown event was received, signaling the engine loop to terminate.
 */
bool isoengine_handle_events(void *engine);

/**
 * Creates a window for the iso engine with the specified title, dimensions (width and height), and associates it with the given engine instance,
 * returning true on success and false on failure.
 */
bool isoengine_window_create(void *const engine, const char *title, uint16_t width, uint16_t height);

/**
 * Clears and presents the ISO renderer associated with the given isometric engine, effectively drawing a frame. Returns false if the engine or its renderer is null,
 * or if the ISO clear/present operations fail; otherwise returns true.
 */
bool isoengine_render_draw(void *const engine);

uint32_t isoengine_object2d_create(void *engine, const isoengine_2dcoords *const coords);

bool isoengine_object2d_keypress_callback(void *engine, uint32_t objectid, isoengine_object2d_keypress_callback_func callback);

bool isoengine_object2d_texture(void *engine, uint32_t objectid, const char *filepng);

#endif