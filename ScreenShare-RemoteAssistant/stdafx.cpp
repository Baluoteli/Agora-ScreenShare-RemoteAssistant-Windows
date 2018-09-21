
// stdafx.cpp : source file that includes just the standard includes
// ScreenShare-RemoteAssistant.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "RemoteAssistantTransfer.h"
using namespace AgoraRemoteTransfer;

UINT getConvertChar(UINT uSrcChar)
{
	UINT nCharConvert = eKeyboardType_NULL;
	switch (uSrcChar) {
	case VK_ESCAPE:nCharConvert = eKeyboardType_ESC; break;
	case VK_F1:nCharConvert = eKeyboardType_F1; break;
	case VK_F2:nCharConvert = eKeyboardType_F2; break;
	case VK_F3:nCharConvert = eKeyboardType_F3; break;
	case VK_F4:nCharConvert = eKeyboardType_F4; break;
	case VK_F5:nCharConvert = eKeyboardType_F5; break;
	case VK_F6:nCharConvert = eKeyboardType_F6; break;
	case VK_F7:nCharConvert = eKeyboardType_F7; break;
	case VK_F8:nCharConvert = eKeyboardType_F8; break;
	case VK_F9:nCharConvert = eKeyboardType_F9; break;
	case VK_F10:nCharConvert = eKeyboardType_F10; break;
	case VK_F11:nCharConvert = eKeyboardType_F11; break;
	case VK_F12:nCharConvert = eKeyboardType_F12; break;
	case VK_HOME:nCharConvert = eKeyboardType_Home; break;
	case VK_END:nCharConvert = eKeyboardType_End; break;
	case VK_INSERT:nCharConvert = eKeyboardType_Insert; break;
	case VK_DELETE:nCharConvert = eKeyboardType_Delete; break;
	case VK_OEM_3:nCharConvert = eKeyboardType_Comma; break;
	case '1':nCharConvert = eKeyboardType_Num1; break;
	case '2':nCharConvert = eKeyboardType_Num2; break;
	case '3':nCharConvert = eKeyboardType_Num3; break;
	case '4':nCharConvert = eKeyboardType_Num4; break;
	case '5':nCharConvert = eKeyboardType_Num5; break;
	case '6':nCharConvert = eKeyboardType_Num6; break;
	case '7':nCharConvert = eKeyboardType_Num7; break;
	case '8':nCharConvert = eKeyboardType_Num8; break;
	case '9':nCharConvert = eKeyboardType_Num9; break;
	case '0':nCharConvert = eKeyboardType_Num0; break;
	case VK_OEM_MINUS:nCharConvert = eKeyboardType_Sub; break;
	case VK_OEM_PLUS:nCharConvert = eKeyboardType_Equ; break;
	case VK_BACK:nCharConvert = eKeyboardType_BackSpace; break;
	case VK_TAB:nCharConvert = eKeyboardType_Tab; break;
	case 'Q':nCharConvert = eKeyboardType_Q; break;
	case 'W':nCharConvert = eKeyboardType_W; break;
	case 'E':nCharConvert = eKeyboardType_E; break;
	case 'R':nCharConvert = eKeyboardType_R; break;
	case 'T':nCharConvert = eKeyboardType_T; break;
	case 'Y':nCharConvert = eKeyboardType_Y; break;
	case 'U':nCharConvert = eKeyboardType_U; break;
	case 'I':nCharConvert = eKeyboardType_I; break;
	case 'O':nCharConvert = eKeyboardType_O; break;
	case 'P':nCharConvert = eKeyboardType_P; break;
	case VK_OEM_4:nCharConvert = eKeyboardType_Left_Parentheses; break;
	case VK_OEM_6:nCharConvert = eKeyboardType_Right_Parentheses; break;
	case VK_OEM_5:nCharConvert = eKeyboardType_Right_Slash; break;
	case VK_CAPITAL:nCharConvert = eKeyboardType_CapsLock; break;
	case 'A':nCharConvert = eKeyboardType_A; break;
	case 'S':nCharConvert = eKeyboardType_S; break;
	case 'D':nCharConvert = eKeyboardType_D; break;
	case 'F':nCharConvert = eKeyboardType_F; break;
	case 'G':nCharConvert = eKeyboardType_G; break;
	case 'H':nCharConvert = eKeyboardType_H; break;
	case 'J':nCharConvert = eKeyboardType_J; break;
	case 'K':nCharConvert = eKeyboardType_K; break;
	case 'L':nCharConvert = eKeyboardType_L; break;
	case VK_OEM_1:nCharConvert = eKeyboardType_colon; break;
	case VK_OEM_7:nCharConvert = eKeyboardType_quotation; break;
	case VK_RETURN:nCharConvert = eKeyboardType_Enter; break;
	case VK_LSHIFT:nCharConvert = eKeyboardType_Left_Shift; break;
	case 'Z':nCharConvert = eKeyboardType_Z; break;
	case 'X':nCharConvert = eKeyboardType_X; break;
	case 'C':nCharConvert = eKeyboardType_C; break;
	case 'V':nCharConvert = eKeyboardType_V; break;
	case 'B':nCharConvert = eKeyboardType_B; break;
	case 'N':nCharConvert = eKeyboardType_N; break;
	case 'M':nCharConvert = eKeyboardType_M; break;
	case VK_OEM_COMMA:nCharConvert = eKeyboardType_Left_brackets; break;
	case VK_OEM_PERIOD:nCharConvert = eKeyboardType_Right_brackets; break;
	case VK_OEM_2:nCharConvert = eKeyboardType_Question; break;
	case VK_RSHIFT:nCharConvert = eKeyboardType_Right_Shift; break;
	case VK_LCONTROL:nCharConvert = eKeyboardType_Left_Ctrl; break;
	case VK_LWIN:nCharConvert = eKeyboardType_Windows; break;
	case VK_LMENU:nCharConvert = eKeyboardType_Left_Alt; break;
	case VK_SPACE:nCharConvert = eKeyboardType_Space; break;
	case VK_RMENU:nCharConvert = eKeyboardType_Right_Alt; break;
	case VK_RCONTROL:nCharConvert = eKeyboardType_Right_Ctrl; break;
	case VK_PRIOR:nCharConvert = eKeyboardType_PgUp; break;
	case VK_LEFT:nCharConvert = eKeyboardType_Left_Direction; break;
	case VK_UP:nCharConvert = eKeyboardType_Up_Direction; break;
	case VK_DOWN:nCharConvert = eKeyboardType_Down_Direction; break;
	case VK_RIGHT:nCharConvert = eKeyboardType_Right_Direction; break;
	case VK_NEXT:nCharConvert = eKeyboardType_PgDn; break;
	default:break;
	}

	return nCharConvert;
}

UINT getSrcChar(UINT uConvertChar)
{
	UINT nSrcChar = eKeyboardType_NULL;
	switch (uConvertChar) {
	case eKeyboardType_NULL:break;
	case eKeyboardType_ESC:nSrcChar = VK_ESCAPE; break;
	case eKeyboardType_F1:nSrcChar = VK_F1; break;
	case eKeyboardType_F2:nSrcChar = VK_F2; break;
	case eKeyboardType_F3:nSrcChar = VK_F3; break;
	case eKeyboardType_F4:nSrcChar = VK_F4; break;
	case eKeyboardType_F5: nSrcChar = VK_F5; break;
	case eKeyboardType_F6: nSrcChar = VK_F6; break;
	case eKeyboardType_F7: nSrcChar = VK_F7; break;
	case eKeyboardType_F8: nSrcChar = VK_F8; break;
	case eKeyboardType_F9: nSrcChar = VK_F9; break;
	case eKeyboardType_F10:nSrcChar = VK_F10;break;
	case eKeyboardType_F11:nSrcChar = VK_F11;break;
	case eKeyboardType_F12:nSrcChar = VK_F12; break;
	case eKeyboardType_Home:nSrcChar = VK_HOME;break;
	case eKeyboardType_End:nSrcChar = VK_END;break;
	case eKeyboardType_Insert: nSrcChar = VK_INSERT;break;
	case eKeyboardType_Delete:nSrcChar = VK_DELETE;break;
	case eKeyboardType_Comma:nSrcChar = VK_OEM_3; break;
	case eKeyboardType_Num1:nSrcChar = '1'; break;
	case eKeyboardType_Num2:nSrcChar = '2'; break;
	case eKeyboardType_Num3:nSrcChar = '3'; break;
	case eKeyboardType_Num4:nSrcChar = '4'; break;
	case eKeyboardType_Num5:nSrcChar = '5'; break;
	case eKeyboardType_Num6:nSrcChar = '6'; break;
	case eKeyboardType_Num7:nSrcChar = '7'; break;
	case eKeyboardType_Num8:nSrcChar = '8'; break;
	case eKeyboardType_Num9:nSrcChar = '9'; break;
	case eKeyboardType_Num0:nSrcChar = '0'; break;
	case eKeyboardType_Sub:nSrcChar = VK_OEM_MINUS; break;
	case eKeyboardType_Equ:nSrcChar = VK_OEM_PLUS; break;
	case eKeyboardType_BackSpace:nSrcChar = VK_BACK; break;
	case eKeyboardType_Tab:nSrcChar = VK_TAB; break;
	case eKeyboardType_Q:nSrcChar = 'Q'; break;
	case eKeyboardType_W:nSrcChar = 'W'; break;
	case eKeyboardType_E:nSrcChar = 'E'; break;
	case eKeyboardType_R:nSrcChar = 'R'; break;
	case eKeyboardType_T:nSrcChar = 'T'; break;
	case eKeyboardType_Y:nSrcChar = 'Y'; break;
	case eKeyboardType_U:nSrcChar = 'U'; break;
	case eKeyboardType_I:nSrcChar = 'I'; break;
	case eKeyboardType_O:nSrcChar = 'O'; break;
	case eKeyboardType_P:nSrcChar = 'P'; break;
	case eKeyboardType_Left_Parentheses:nSrcChar = VK_OEM_4;  break;
	case eKeyboardType_Right_Parentheses:nSrcChar = VK_OEM_6; break;
	case eKeyboardType_Right_Slash:nSrcChar = VK_OEM_5; break;
	case eKeyboardType_CapsLock: nSrcChar = VK_CAPITAL; break;
	case eKeyboardType_A:nSrcChar = 'A'; break;
	case eKeyboardType_S:nSrcChar = 'S'; break;
	case eKeyboardType_D:nSrcChar = 'D'; break;
	case eKeyboardType_F:nSrcChar = 'F'; break;
	case eKeyboardType_G:nSrcChar = 'G'; break;
	case eKeyboardType_H:nSrcChar = 'H'; break;
	case eKeyboardType_J:nSrcChar = 'J'; break;
	case eKeyboardType_K:nSrcChar = 'K'; break;
	case eKeyboardType_L:nSrcChar = 'L'; break;
	case eKeyboardType_colon: nSrcChar = VK_OEM_1; break;
	case eKeyboardType_quotation:nSrcChar = VK_OEM_7; break;
	case eKeyboardType_Enter:nSrcChar = VK_RETURN;break;
	case eKeyboardType_Left_Shift:nSrcChar = VK_LSHIFT; break;
	case eKeyboardType_Z:nSrcChar = 'Z'; break;
	case eKeyboardType_X:nSrcChar = 'X'; break;
	case eKeyboardType_C:nSrcChar = 'C'; break;
	case eKeyboardType_V:nSrcChar = 'V'; break;
	case eKeyboardType_B:nSrcChar = 'B'; break;
	case eKeyboardType_N:nSrcChar = 'N'; break;
	case eKeyboardType_M:nSrcChar = 'M'; break;
	case eKeyboardType_Left_brackets:nSrcChar = VK_OEM_COMMA; break;
	case eKeyboardType_Right_brackets:nSrcChar = VK_OEM_PERIOD; break;
	case eKeyboardType_Question:nSrcChar = VK_OEM_2; break;
	case eKeyboardType_Right_Shift:nSrcChar = VK_RSHIFT; break;
	case eKeyboardType_Left_Ctrl:nSrcChar = VK_LCONTROL; break;
	case eKeyboardType_Windows:nSrcChar = VK_LWIN; break;
	case eKeyboardType_Left_Alt:nSrcChar = VK_LMENU; break;
	case eKeyboardType_Space:nSrcChar = VK_SPACE; break;
	case eKeyboardType_Right_Alt:nSrcChar = VK_RMENU; break;
	case eKeyboardType_Right_Ctrl:nSrcChar = VK_RCONTROL; break;
	case eKeyboardType_PgUp:nSrcChar = VK_PRIOR; break;
	case eKeyboardType_Left_Direction:nSrcChar = VK_LEFT; break;
	case eKeyboardType_Up_Direction:nSrcChar = VK_UP; break;
	case eKeyboardType_Down_Direction:nSrcChar = VK_DOWN; break;
	case eKeyboardType_PgDn:nSrcChar = VK_NEXT;break;
	case eKeyboardType_Right_Direction:nSrcChar = VK_RIGHT; break;
	default:break;
	}

	return nSrcChar;
}