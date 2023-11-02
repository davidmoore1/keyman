#include "pch.h"
#include "virtualcharkeys.h"

KMX_BOOL VKeyMayBeVCKey[256] = {
	FALSE,    // L"K_?00",				// &H0
	FALSE,    // L"K_LBUTTON",			// &H1
	FALSE,    // L"K_RBUTTON",			// &H2
	FALSE,    // L"K_CANCEL",		   	// &H3
	FALSE,    // L"K_MBUTTON",			// &H4
	FALSE,    // L"K_?05",				// &H5
	FALSE,    // L"K_?06",				// &H6
	FALSE,    // L"K_?07",				// &H7
	FALSE,    // L"K_BKSP",	    		// &H8
	FALSE,    // L"K_TAB",	    		// &H9
	FALSE,    // L"K_?0A",				// &HA
	FALSE,    // L"K_?0B",				// &HB
	FALSE,    // L"K_KP5",		    	// &HC
	FALSE,    // L"K_ENTER",				// &HD
	FALSE,    // L"K_?0E",				// &HE
	FALSE,    // L"K_?0F",				// &HF
	FALSE,    // L"K_SHIFT",				// &H10
	FALSE,    // L"K_CONTROL",			// &H11
	FALSE,    // L"K_ALT",				// &H12
	FALSE,    // L"K_PAUSE",				// &H13
	FALSE,    // L"K_CAPS",				// &H14
	FALSE,    // L"K_KANJI?15",			// &H15
	FALSE,    // L"K_KANJI?16",			// &H16
	FALSE,    // L"K_KANJI?17",			// &H17
	FALSE,    // L"K_KANJI?18",			// &H18
	FALSE,    // L"K_KANJI?19",			// &H19
	FALSE,    // L"K_?1A",				// &H1A
	FALSE,    // L"K_ESC",				// &H1B
	FALSE,    // L"K_KANJI?1C",			// &H1C
	FALSE,    // L"K_KANJI?1D",			// &H1D
	FALSE,    // L"K_KANJI?1E",			// &H1E
	FALSE,    // L"K_KANJI?1F",			// &H1F
	TRUE,     // L"K_SPACE",				// &H20
	FALSE,    // L"K_PGUP",				// &H21
	FALSE,    // L"K_PGDN",				// &H22
	FALSE,    // L"K_END",				// &H23
	FALSE,    // L"K_HOME",				// &H24
	FALSE,    // L"K_LEFT",				// &H25
	FALSE,    // L"K_UP",				// &H26
	FALSE,    // L"K_RIGHT",				// &H27
	FALSE,    // L"K_DOWN",				// &H28
	FALSE,    // L"K_SEL",				// &H29
	FALSE,    // L"K_PRINT",				// &H2A
	FALSE,    // L"K_EXEC",				// &H2B
	FALSE,    // L"K_PRTSCN",			// &H2C
	FALSE,    // L"K_INS",				// &H2D
	FALSE,    // L"K_DEL",				// &H2E
	FALSE,    // L"K_HELP",				// &H2F
	TRUE,     // L"K_0",					// &H30
	TRUE,     // L"K_1",					// &H31
	TRUE,     // L"K_2",					// &H32
	TRUE,     // L"K_3",					// &H33
	TRUE,     // L"K_4",					// &H34
	TRUE,     // L"K_5",					// &H35
	TRUE,     // L"K_6",					// &H36
	TRUE,     // L"K_7",					// &H37
	TRUE,     // L"K_8",					// &H38
	TRUE,     // L"K_9",					// &H39
	FALSE,    // L"K_?3A",				// &H3A
	FALSE,    // L"K_?3B",				// &H3B
	FALSE,    // L"K_?3C",				// &H3C
	FALSE,    // L"K_?3D",				// &H3D
	FALSE,    // L"K_?3E",				// &H3E
	FALSE,    // L"K_?3F",				// &H3F
	FALSE,    // L"K_?40",				// &H40

	TRUE,     // L"K_A",					// &H41
	TRUE,     // L"K_B",					// &H42
	TRUE,     // L"K_C",					// &H43
	TRUE,     // L"K_D",					// &H44
	TRUE,     // L"K_E",					// &H45
	TRUE,     // L"K_F",					// &H46
	TRUE,     // L"K_G",					// &H47
	TRUE,     // L"K_H",					// &H48
	TRUE,     // L"K_I",					// &H49
	TRUE,     // L"K_J",					// &H4A
	TRUE,     // L"K_K",					// &H4B
	TRUE,     // L"K_L",					// &H4C
	TRUE,     // L"K_M",					// &H4D
	TRUE,     // L"K_N",					// &H4E
	TRUE,     // L"K_O",					// &H4F
	TRUE,     // L"K_P",					// &H50
	TRUE,     // L"K_Q",					// &H51
	TRUE,     // L"K_R",					// &H52
	TRUE,     // L"K_S",					// &H53
	TRUE,     // L"K_T",					// &H54
	TRUE,     // L"K_U",					// &H55
	TRUE,     // L"K_V",					// &H56
	TRUE,     // L"K_W",					// &H57
	TRUE,     // L"K_X",					// &H58
	TRUE,     // L"K_Y",					// &H59
	TRUE,     // L"K_Z",					// &H5A
	FALSE,    // L"K_?5B",				// &H5B
	FALSE,    // L"K_?5C",				// &H5C
	FALSE,    // L"K_?5D",				// &H5D
	FALSE,    // L"K_?5E",				// &H5E
	FALSE,    // L"K_?5F",				// &H5F
	FALSE,    // L"K_NP0",				// &H60
	FALSE,    // L"K_NP1",				// &H61
	FALSE,    // L"K_NP2",				// &H62
	FALSE,    // L"K_NP3",				// &H63
	FALSE,    // L"K_NP4",				// &H64
	FALSE,    // L"K_NP5",				// &H65
	FALSE,    // L"K_NP6",				// &H66
	FALSE,    // L"K_NP7",				// &H67
	FALSE,    // L"K_NP8",				// &H68
	FALSE,    // L"K_NP9",				// &H69
	FALSE,    // L"K_NPSTAR",			// &H6A
	FALSE,    // L"K_NPPLUS",			// &H6B
	FALSE,    // L"K_SEPARATOR",			// &H6C
	FALSE,    // L"K_NPMINUS",			// &H6D
	FALSE,    // L"K_NPDOT",				// &H6E
	FALSE,    // L"K_NPSLASH",			// &H6F
	FALSE,    // L"K_F1",				// &H70
	FALSE,    // L"K_F2",				// &H71
	FALSE,    // L"K_F3",				// &H72
	FALSE,    // L"K_F4",				// &H73
	FALSE,    // L"K_F5",				// &H74
	FALSE,    // L"K_F6",				// &H75
	FALSE,    // L"K_F7",				// &H76
	FALSE,    // L"K_F8",				// &H77
	FALSE,    // L"K_F9",				// &H78
	FALSE,    // L"K_F10",				// &H79
	FALSE,    // L"K_F11",				// &H7A
	FALSE,    // L"K_F12",				// &H7B
	FALSE,    // L"K_F13",				// &H7C
	FALSE,    // L"K_F14",				// &H7D
	FALSE,    // L"K_F15",				// &H7E
	FALSE,    // L"K_F16",				// &H7F
	FALSE,    // L"K_F17",				// &H80
	FALSE,    // L"K_F18",				// &H81
	FALSE,    // L"K_F19",				// &H82
	FALSE,    // L"K_F20",				// &H83
	FALSE,    // L"K_F21",				// &H84
	FALSE,    // L"K_F22",				// &H85
	FALSE,    // L"K_F23",				// &H86
	FALSE,    // L"K_F24",				// &H87

	FALSE,    // L"K_?88",				// &H88
	FALSE,    // L"K_?89",				// &H89
	FALSE,    // L"K_?8A",				// &H8A
	FALSE,    // L"K_?8B",				// &H8B
	FALSE,    // L"K_?8C",				// &H8C
	FALSE,    // L"K_?8D",				// &H8D
	FALSE,    // L"K_?8E",				// &H8E
	FALSE,    // L"K_?8F",				// &H8F

	FALSE,    // L"K_NUMLOCK",			// &H90
	FALSE,    // L"K_SCROLL",			// &H91

	FALSE,    // L"K_?92",				// &H92
	FALSE,    // L"K_?93",				// &H93
	FALSE,    // L"K_?94",				// &H94
	FALSE,    // L"K_?95",				// &H95
	FALSE,    // L"K_?96",				// &H96
	FALSE,    // L"K_?97",				// &H97
	FALSE,    // L"K_?98",				// &H98
	FALSE,    // L"K_?99",				// &H99
	FALSE,    // L"K_?9A",				// &H9A
	FALSE,    // L"K_?9B",				// &H9B
	FALSE,    // L"K_?9C",				// &H9C
	FALSE,    // L"K_?9D",				// &H9D
	FALSE,    // L"K_?9E",				// &H9E
	FALSE,    // L"K_?9F",				// &H9F
	FALSE,    // L"K_?A0",				// &HA0
	FALSE,    // L"K_?A1",				// &HA1
	FALSE,    // L"K_?A2",				// &HA2
	FALSE,    // L"K_?A3",				// &HA3
	FALSE,    // L"K_?A4",				// &HA4
	FALSE,    // L"K_?A5",				// &HA5
	FALSE,    // L"K_?A6",				// &HA6
	FALSE,    // L"K_?A7",				// &HA7
	FALSE,    // L"K_?A8",				// &HA8
	FALSE,    // L"K_?A9",				// &HA9
	FALSE,    // L"K_?AA",				// &HAA
	FALSE,    // L"K_?AB",				// &HAB
	FALSE,    // L"K_?AC",				// &HAC
	FALSE,    // L"K_?AD",				// &HAD
	FALSE,    // L"K_?AE",				// &HAE
	FALSE,    // L"K_?AF",				// &HAF
	FALSE,    // L"K_?B0",				// &HB0
	FALSE,    // L"K_?B1",				// &HB1
	FALSE,    // L"K_?B2",				// &HB2
	FALSE,    // L"K_?B3",				// &HB3
	FALSE,    // L"K_?B4",				// &HB4
	FALSE,    // L"K_?B5",				// &HB5
	FALSE,    // L"K_?B6",				// &HB6
	FALSE,    // L"K_?B7",				// &HB7
	FALSE,    // L"K_?B8",				// &HB8
	FALSE,    // L"K_?B9",				// &HB9

	TRUE,     // L"K_COLON",				// &HBA
	TRUE,     // L"K_EQUAL",				// &HBB
	TRUE,     // L"K_COMMA",				// &HBC
	TRUE,     // L"K_HYPHEN",			// &HBD
	TRUE,     // L"K_PERIOD",			// &HBE
	TRUE,     // L"K_SLASH",				// &HBF
	TRUE,     // L"K_BKQUOTE",			// &HC0

	TRUE,     // L"K_?C1",				// &HC1 -- 103rd key on Brazilian - /?
	FALSE,     // L"K_?C2",				// &HC2 -- 104th key on Brazilian - numpad .
	FALSE,    // L"K_?C3",				// &HC3
	FALSE,    // L"K_?C4",				// &HC4
	FALSE,    // L"K_?C5",				// &HC5
	FALSE,    // L"K_?C6",				// &HC6
	FALSE,    // L"K_?C7",				// &HC7
	FALSE,    // L"K_?C8",				// &HC8
	FALSE,    // L"K_?C9",				// &HC9
	FALSE,    // L"K_?CA",				// &HCA
	FALSE,    // L"K_?CB",				// &HCB
	FALSE,    // L"K_?CC",				// &HCC
	FALSE,    // L"K_?CD",				// &HCD
	FALSE,    // L"K_?CE",				// &HCE
	FALSE,    // L"K_?CF",				// &HCF
	FALSE,    // L"K_?D0",				// &HD0
	FALSE,    // L"K_?D1",				// &HD1
	FALSE,    // L"K_?D2",				// &HD2
	FALSE,    // L"K_?D3",				// &HD3
	FALSE,    // L"K_?D4",				// &HD4
	FALSE,    // L"K_?D5",				// &HD5
	FALSE,    // L"K_?D6",				// &HD6
	FALSE,    // L"K_?D7",				// &HD7
	FALSE,    // L"K_?D8",				// &HD8
	FALSE,    // L"K_?D9",				// &HD9
	FALSE,    // L"K_?DA",				// &HDA

	TRUE,    // L"K_LBRKT",				// &HDB
	TRUE,    // L"K_BKSLASH",			// &HDC
	TRUE,    // L"K_RBRKT",				// &HDD
	TRUE,    // L"K_QUOTE",				// &HDE
	TRUE,    // L"K_oDF",				// &HDF
	TRUE,    // L"K_oE0",				// &HE0
	TRUE,    // L"K_oE1",				// &HE1
	TRUE,    // L"K_oE2",				// &HE2
	TRUE,    // L"K_oE3",				// &HE3
	TRUE,    // L"K_oE4",				// &HE4

	FALSE,    // L"K_?E5",				// &HE5

	TRUE,    // L"K_oE6",				// &HE6

	FALSE,    // L"K_?E7",				// &HE7
	FALSE,    // L"K_?E8",				// &HE8

	TRUE,    // L"K_oE9",				// &HE9
	TRUE,    // L"K_oEA",				// &HEA
	TRUE,    // L"K_oEB",				// &HEB
	TRUE,    // L"K_oEC",				// &HEC
	TRUE,    // L"K_oED",				// &HED
	TRUE,    // L"K_oEE",				// &HEE
	TRUE,    // L"K_oEF",				// &HEF
	TRUE,    // L"K_oF0",				// &HF0
	TRUE,    // L"K_oF1",				// &HF1
	TRUE,    // L"K_oF2",				// &HF2
	TRUE,    // L"K_oF3",				// &HF3
	TRUE,    // L"K_oF4",				// &HF4
	TRUE,    // L"K_oF5",				// &HF5

	FALSE,    // L"K_?F6",				// &HF6
	FALSE,    // L"K_?F7",				// &HF7
	FALSE,    // L"K_?F8",				// &HF8
	FALSE,    // L"K_?F9",				// &HF9
	FALSE,    // L"K_?FA",				// &HFA
	FALSE,    // L"K_?FB",				// &HFB
	FALSE,    // L"K_?FC",				// &HFC
	FALSE,    // L"K_?FD",				// &HFD
	FALSE,    // L"K_?FE",				// &HFE
	FALSE,    // L"K_?FF"				// &HFF
	};
