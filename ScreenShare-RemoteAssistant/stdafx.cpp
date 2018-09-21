
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
	case '0':nCharConvert = eKeyboardType_Num0; break;
	case '1':nCharConvert = eKeyboardType_Num1; break;
	case 'Z':nCharConvert = eKeyboardType_Z; break;
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
	case eKeyboardType_F5: break;
	case eKeyboardType_F6: break;
	case eKeyboardType_F7: break;
	case eKeyboardType_F8: break;
	case eKeyboardType_F9: break;
	case eKeyboardType_F10:break;
	case eKeyboardType_F11:break;
	case eKeyboardType_F12:break;
	case eKeyboardType_Home:break;
	case eKeyboardType_End:break;
	case eKeyboardType_Insert:break;
	case eKeyboardType_Delete:break;
	case eKeyboardType_Comma:break;
	case eKeyboardType_Num0:nSrcChar = '0'; break;
	case eKeyboardType_Num1:nSrcChar = '1'; break;
	case eKeyboardType_Num2:nSrcChar = '2'; break;
	case eKeyboardType_Num3:nSrcChar = '3'; break;
	case eKeyboardType_Num4:nSrcChar = '4'; break;
	case eKeyboardType_Num5:nSrcChar = '5'; break;
	case eKeyboardType_Num6:nSrcChar = '6'; break;
	case eKeyboardType_Num7:nSrcChar = '7'; break;
	case eKeyboardType_Num8:nSrcChar = '8'; break;
	case eKeyboardType_Num9:nSrcChar = '9'; break;
	case eKeyboardType_Sub:break;
	case eKeyboardType_Equ:break;
	case eKeyboardType_BackSpace:break;
	case eKeyboardType_Tab:break;
	case eKeyboardType_Q:nSrcChar = 'Q'; break;
	case eKeyboardType_W:break;
	case eKeyboardType_E:break;
	case eKeyboardType_R:break;
	case eKeyboardType_T:break;
	case eKeyboardType_Y:break;
	case eKeyboardType_U:break;
	case eKeyboardType_I:break;
	case eKeyboardType_O:break;
	case eKeyboardType_P:break;
	case eKeyboardType_Left_Parentheses:break;
	case eKeyboardType_Right_Parentheses:break;
	case eKeyboardType_Right_Slash:break;
	case eKeyboardType_CapsLock:break;
	case eKeyboardType_A:break;
	case eKeyboardType_S:break;
	case eKeyboardType_D:break;
	case eKeyboardType_F:break;
	case eKeyboardType_G:break;
	case eKeyboardType_H:break;
	case eKeyboardType_J:break;
	case eKeyboardType_K:break;
	case eKeyboardType_L:break;
	case eKeyboardType_colon:break;
	case eKeyboardType_quotation:break;
	case eKeyboardType_Enter:break;
	case eKeyboardType_Left_Shift:break;
	case eKeyboardType_Z:nSrcChar = 'Z'; break;
	case eKeyboardType_X:break;
	case eKeyboardType_C:break;
	case eKeyboardType_V:break;
	case eKeyboardType_B:break;
	case eKeyboardType_N:break;
	case eKeyboardType_M:break;
	case eKeyboardType_Left_brackets:break;
	case eKeyboardType_Right_brackets:break;
	case eKeyboardType_Question:break;
	case eKeyboardType_Right_Shift:break;
	case eKeyboardType_Fn:break;
	case eKeyboardType_Left_Ctrl:break;
	case eKeyboardType_Windows:break;
	case eKeyboardType_Left_Alt:break;
	case eKeyboardType_Space:break;
	case eKeyboardType_Right_Alt:break;
	case eKeyboardType_Right_Ctrl:break;
	case eKeyboardType_PgUp:break;
	case eKeyboardType_Left_Direction:break;
	case eKeyboardType_Top_Direction:break;
	case eKeyboardType_Botton_Direction:break;
	case eKeyboardType_PgDn:break;
	case eKeyboardType_Right_Direction:break;
	default:break;
	}

	return nSrcChar;
}