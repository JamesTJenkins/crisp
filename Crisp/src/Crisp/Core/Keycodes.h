#pragma once

// From SDL_keycode.h
// Skipped uppercase

#define CRISP_UNKNOWN				0x00

#define CRISP_RETURN				0x0D
#define CRISP_ESCAPE				0x1B
#define CRISP_BACKSPACE				0x08
#define CRISP_TAB					0x09
#define CRISP_SPACE					0x20
#define CRISP_EXCLAIM				0x21
#define CRISP_QUOTEDBL				0x22
#define CRISP_HASH					0x23
#define CRISP_DOLLAR				0x24
#define CRISP_PERCENT				0x25
#define CRISP_AMPERSAND				0x26
#define CRISP_QUOTE					0x27
#define CRISP_LEFTPAREN				0x28
#define CRISP_RIGHTPAREN			0x29
#define CRISP_ASTERISK				0x2A
#define CRISP_PLUS					0x2B
#define CRISP_COMMA					0x2C
#define CRISP_MINUS					0x2D
#define CRISP_PERIOD				0x2E
#define CRISP_SLASH					0x2F
#define CRISP_0						0x30
#define CRISP_1						0x31
#define CRISP_2						0x32
#define CRISP_3						0x33
#define CRISP_4						0x34
#define CRISP_5						0x35
#define CRISP_6						0x36
#define CRISP_7						0x37
#define CRISP_8						0x38
#define CRISP_9						0x39
#define CRISP_COLON					0x3A
#define CRISP_SEMICOLON				0x3B
#define CRISP_LESS					0x3C
#define CRISP_EQUALS				0x3D
#define CRISP_GREATER				0x3E
#define CRISP_QUESTION				0x3F
#define CRISP_AT					0x40
#define CRISP_LEFTBRACKET			0x5B
#define CRISP_BACKSLASH				0x5C
#define CRISP_RIGHTBRACKET			0x5D
#define CRISP_CARET					0x5E
#define CRISP_UNDERSCORE			0x5F
#define CRISP_BACKQUOTE				0x60

#define CRISP_A						0x61
#define CRISP_B						0x62
#define CRISP_C						0x63
#define CRISP_D						0x64
#define CRISP_E						0x65
#define CRISP_F						0x66
#define CRISP_G						0x67
#define CRISP_H						0x68
#define CRISP_I						0x69
#define CRISP_J						0x6A
#define CRISP_K						0x6B
#define CRISP_L						0x6C
#define CRISP_M						0x6D
#define CRISP_N						0x6E
#define CRISP_O						0x6F
#define CRISP_P						0x70
#define CRISP_Q						0x71
#define CRISP_R						0x72
#define CRISP_S						0x73
#define CRISP_T						0x74
#define CRISP_U						0x75
#define CRISP_V						0x76
#define CRISP_W						0x77
#define CRISP_X						0x78
#define CRISP_Y						0x79
#define CRISP_Z						0x7A
 
#define CRISP_CAPSLOCK				0x40000039
 
#define CRISP_F1					0x4000003A
#define CRISP_F2					0x4000003B
#define CRISP_F3					0x4000003C
#define CRISP_F4					0x4000003D
#define CRISP_F5					0x4000003E
#define CRISP_F6					0x4000003F
#define CRISP_F7					0x40000040
#define CRISP_F8					0x40000041
#define CRISP_F9					0x40000042
#define CRISP_F10					0x40000043
#define CRISP_F11					0x40000044
#define CRISP_F12					0x40000045
 
#define CRISP_PRINTSCREEN			0x40000046
#define CRISP_SCROLLLOCK			0x40000047
#define CRISP_PAUSE					0x40000048
#define CRISP_INSERT				0x40000049
#define CRISP_HOME					0x4000004A
#define CRISP_PAGEUP				0x4000004B
#define CRISP_DELETE  
#define CRISP_END					0x4000004D
#define CRISP_PAGEDOWN				0x4000004E
#define CRISP_RIGHT					0x4000004F
#define CRISP_LEFT					0x40000050
#define CRISP_DOWN					0x40000051
#define CRISP_UP					0x40000052
 
#define CRISP_NUMLOCKCLEAR			0x40000053
#define CRISP_KEYPAD_DIVIDE			0x40000054
#define CRISP_KEYPAD_MULTIPLY		0x40000055
#define CRISP_KEYPAD_MINUS			0x40000056
#define CRISP_KEYPAD_PLUS			0x40000057
#define CRISP_KEYPAD_ENTER			0x40000058
#define CRISP_KEYPAD_1				0x40000059
#define CRISP_KEYPAD_2				0x4000005A
#define CRISP_KEYPAD_3				0x4000005B
#define CRISP_KEYPAD_4				0x4000005C
#define CRISP_KEYPAD_5				0x4000005D
#define CRISP_KEYPAD_6				0x4000005E
#define CRISP_KEYPAD_7				0x4000005F
#define CRISP_KEYPAD_8				0x40000060
#define CRISP_KEYPAD_9				0x40000061
#define CRISP_KEYPAD_0				0x40000062
#define CRISP_KEYPAD_PERIOD			0x40000063
#define CRISP_APPLICATION			0x40000065
#define CRISP_POWER					0x40000066
#define CRISP_KEYPAD_EQUALS			0x40000067
#define CRISP_F13					0x40000068
#define CRISP_F14					0x40000069
#define CRISP_F15					0x4000006A
#define CRISP_F16					0x4000006B
#define CRISP_F17					0x4000006C
#define CRISP_F18					0x4000006D
#define CRISP_F19					0x4000006E
#define CRISP_F20					0x4000006F
#define CRISP_F21					0x40000070
#define CRISP_F22					0x40000071
#define CRISP_F23					0x40000072
#define CRISP_F24					0x40000073
#define CRISP_EXECUTE				0x40000074
#define CRISP_HELP					0x40000075
#define CRISP_MENU					0x40000076
#define CRISP_SELECT				0x40000077
#define CRISP_STOP					0x40000078
#define CRISP_AGAIN					0x40000079
#define CRISP_UNDO					0x4000007A
#define CRISP_CUT					0x4000007B
#define CRISP_COPY					0x4000007C
#define CRISP_PASTE					0x4000007D
#define CRISP_FIND					0x4000007E
#define CRISP_MUTE					0x4000007F
#define CRISP_VOLUMEUP				0x40000080
#define CRISP_VOLUMEDOWN			0x40000081
#define CRISP_KEYPAD_COMMA			0x40000085
#define CRISP_KEYPAD_EQUALSAS400	0x40000086
 
#define CRISP_ALTERASE				0x40000099
#define CRISP_SYSREQ				0x4000009A
#define CRISP_CANCEL				0x4000009B
#define CRISP_CLEAR					0x4000009C
#define CRISP_PRIOR					0x4000009D
#define CRISP_RETURN2				0x4000009E
#define CRISP_SEPARATOR				0x4000009F
#define CRISP_OUT					0x400000A0
#define CRISP_OPER					0x400000A1
#define CRISP_CLEARAGAIN			0x400000A2
#define CRISP_CRSEL					0x400000A3
#define CRISP_EXSEL					0x400000A4
 
#define CRISP_KEYPAD_00				0x400000B0
#define CRISP_KEYPAD_000			0x400000B1
#define CRISP_THOUSANDSSEPARATOR	0x400000B2
#define CRISP_DECIMALSEPARATOR		0x400000B3
#define CRISP_CURRENCYUNIT			0x400000B4
#define CRISP_CURRENCYSUBUNIT		0x400000B5
#define CRISP_KEYPAD_LEFTPAREN		0x400000B6
#define CRISP_KEYPAD_RIGHTPAREN		0x400000B7
#define CRISP_KEYPAD_LEFTBRACE		0x400000B8
#define CRISP_KEYPAD_RIGHTBRACE		0x400000B9
#define CRISP_KEYPAD_TAB			0x400000BA
#define CRISP_KEYPAD_BACKSPACE		0x400000BB
#define CRISP_KEYPAD_A				0x400000BC
#define CRISP_KEYPAD_B				0x400000BD
#define CRISP_KEYPAD_C				0x400000BE
#define CRISP_KEYPAD_D				0x400000BF
#define CRISP_KEYPAD_E				0x400000C0
#define CRISP_KEYPAD_F				0x400000C1
#define CRISP_KEYPAD_XOR			0x400000C2
#define CRISP_KEYPAD_POWER			0x400000C3
#define CRISP_KEYPAD_PERCENT		0x400000C4
#define CRISP_KEYPAD_LESS			0x400000C5
#define CRISP_KEYPAD_GREATER		0x400000C6
#define CRISP_KEYPAD_AMPERSAND		0x400000C7
#define CRISP_KEYPAD_DBLAMPERSAND	0x400000C8
#define CRISP_KEYPAD_VERTICALBAR	0x400000C9
#define CRISP_KEYPAD_DBLVERTICALBAR	0x400000CA
#define CRISP_KEYPAD_COLON			0x400000CB
#define CRISP_KEYPAD_HASH			0x400000CC
#define CRISP_KEYPAD_SPACE			0x400000CD
#define CRISP_KEYPAD_AT				0x400000CE
#define CRISP_KEYPAD_EXCLAM			0x400000CF
#define CRISP_KEYPAD_MEMSTORE		0x400000D0
#define CRISP_KEYPAD_MEMRECALL		0x400000D1
#define CRISP_KEYPAD_MEMCLEAR		0x400000D2
#define CRISP_KEYPAD_MEMADD			0x400000D3
#define CRISP_KEYPAD_MEMSUBTRACT	0x400000D4
#define CRISP_KEYPAD_MEMMULTIPLY	0x400000D5
#define CRISP_KEYPAD_MEMDIVIDE		0x400000D6
#define CRISP_KEYPAD_PLUSMINUS		0x400000D7
#define CRISP_KEYPAD_CLEAR			0x400000D8
#define CRISP_KEYPAD_CLEARENTRY		0x400000D9
#define CRISP_KEYPAD_BINARY			0x400000DA
#define CRISP_KEYPAD_OCTAL			0x400000DB
#define CRISP_KEYPAD_DECIMAL		0x400000DC
#define CRISP_KEYPAD_HEXADECIMAL	0x400000DD
 
#define CRISP_LCTRL					0x400000E0
#define CRISP_LSHIFT				0x400000E1
#define CRISP_LALT					0x400000E2
#define CRISP_LGUI					0x400000E3
#define CRISP_RCTRL					0x400000E4
#define CRISP_RSHIFT				0x400000E5
#define CRISP_RALT					0x400000E6
#define CRISP_RGUI					0x400000E7

#define CRISP_MODE					0x40000101

#define CRISP_AUDIONEXT				0x40000102
#define CRISP_AUDIOPREV				0x40000103
#define CRISP_AUDIOSTOP				0x40000104
#define CRISP_AUDIOPLAY				0x40000105
#define CRISP_AUDIOMUTE				0x40000106
#define CRISP_MEDIASELECT			0x40000107
#define CRISP_WWW					0x40000108
#define CRISP_MAIL					0x40000109
#define CRISP_CALCULATOR			0x4000010A
#define CRISP_COMPUTER				0x4000010B
#define CRISP_AC_SEARCH				0x4000010C
#define CRISP_AC_HOME				0x4000010D
#define CRISP_AC_BACK				0x4000010E
#define CRISP_AC_FORWARD			0x4000010F
#define CRISP_AC_STOP				0x40000110
#define CRISP_AC_REFRESH			0x40000111
#define CRISP_AC_BOOKMARKS			0x40000112
 
#define CRISP_BRIGHTNESSDOWN		0x40000113
#define CRISP_BRIGHTNESSUP			0x40000114
#define CRISP_DISPLAYSWITCH			0x40000115
#define CRISP_KBDILLUMTOGGLE		0x40000116
#define CRISP_KBDILLUMDOWN			0x40000117
#define CRISP_KBDILLUMUP			0x40000118
#define CRISP_EJECT					0x40000119
#define CRISP_SLEEP					0x4000011A