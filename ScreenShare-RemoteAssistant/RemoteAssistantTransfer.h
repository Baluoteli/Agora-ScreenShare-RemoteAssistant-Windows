#ifndef __REMOTEASSISTANTTRANSFER_H__
#define __REMOTEASSISTANTTRANSFER_H__

class CAgoraSignalWrapper;
namespace AgoraRemoteTransfer {

	enum RemoteTransferType {
		eTransfer_NULL = 0,
		eTransfer_StartAssistant = 1,
		eTransfer_StopAssistant = 2,
		eTransfer_Mouse_LBtnDown = 100,
		eTransfer_Mouse_LBtnUp = 101,
		eTransfer_Mouse_LBtnDClick = 102,
		eTransfer_Mouse_RBtnDown = 103,
		eTransfer_Mouse_RBtnUp = 104,
		eTransfer_Mouse_RBtnDClick = 105,
		eTransfer_Mouse_Move = 106,
		eTransfer_Mouse_Wheel = 107,
		eTransfer_KeyBoard_KeyPress = 1000,
		eTransfer_KeyBoard_KeyDown = 1001,
		eTransfer_KeyBoard_KeyUp = 1002,
		eTransfer_KeyBoard_Cut = 1003,
		eTransfer_KeyBoard_Copy = 1004,
		eTransfer_KeyBoard_Paste = 1005,
	};

	enum KeyboardTransferType {
		eKeyboardType_NULL = 0,
		eKeyboardType_ESC,
		eKeyboardType_F1,
		eKeyboardType_F2,
		eKeyboardType_F3,
		eKeyboardType_F4,
		eKeyboardType_F5,
		eKeyboardType_F6,
		eKeyboardType_F7,
		eKeyboardType_F8,
		eKeyboardType_F9,
		eKeyboardType_F10,
		eKeyboardType_F11,
		eKeyboardType_F12,
		eKeyboardType_Home,
		eKeyboardType_End,
		eKeyboardType_Insert,
		eKeyboardType_Delete,
		eKeyboardType_Comma,//~,`
		eKeyboardType_Num0,
		eKeyboardType_Num1,
		eKeyboardType_Num2,
		eKeyboardType_Num3,
		eKeyboardType_Num4,
		eKeyboardType_Num5,
		eKeyboardType_Num6,
		eKeyboardType_Num7,
		eKeyboardType_Num8,
		eKeyboardType_Num9,
		eKeyboardType_Sub,//_,-
		eKeyboardType_Equ,//+,=
		eKeyboardType_BackSpace,
		eKeyboardType_Tab,
		eKeyboardType_Q,
		eKeyboardType_W,
		eKeyboardType_E,
		eKeyboardType_R,
		eKeyboardType_T,
		eKeyboardType_Y,
		eKeyboardType_U,
		eKeyboardType_I,
		eKeyboardType_O,
		eKeyboardType_P,
		eKeyboardType_Left_Parentheses,//{,[
		eKeyboardType_Right_Parentheses,//},]
		eKeyboardType_Right_Slash,//\,|
		eKeyboardType_CapsLock,//uppercase and lowercase switch
		eKeyboardType_A,
		eKeyboardType_S,
		eKeyboardType_D,
		eKeyboardType_F,
		eKeyboardType_G,
		eKeyboardType_H,
		eKeyboardType_J,
		eKeyboardType_K,
		eKeyboardType_L,
		eKeyboardType_colon,//;,:
		eKeyboardType_quotation,//',"
		eKeyboardType_Enter,
		eKeyboardType_Left_Shift,
		eKeyboardType_Z,
		eKeyboardType_X,
		eKeyboardType_C,
		eKeyboardType_V,
		eKeyboardType_B,
		eKeyboardType_N,
		eKeyboardType_M,
		eKeyboardType_Left_brackets,//<,,
		eKeyboardType_Right_brackets,//>,.
		eKeyboardType_Question,//?,/
		eKeyboardType_Right_Shift,
		eKeyboardType_Fn,
		eKeyboardType_Left_Ctrl,
		eKeyboardType_Windows,
		eKeyboardType_Left_Alt, 
		eKeyboardType_Space,
		eKeyboardType_Right_Alt,
		eKeyboardType_Right_Ctrl,
		eKeyboardType_PgUp,
		eKeyboardType_Left_Direction,
		eKeyboardType_Top_Direction,
		eKeyboardType_Botton_Direction,
		eKeyboardType_PgDn,
		eKeyboardType_Right_Direction,
	};

	//Remote Transfer Define
#define EVENTPARAM	"param"
#define CMDTYPE			"cmdType"
#define TIMESTAMP		"timestamp"
#define POSITION			"point"
#define VKEYCODE       "keyCode"
#define SCROLDELTA	"scrolDelta"


	class CAgoraRemoteTransfer {

	public:
		CAgoraRemoteTransfer();
		CAgoraRemoteTransfer(const std::string &strUID);
		~CAgoraRemoteTransfer();

		void setRemoteUID(const std::string &strUID);

		void start();
		void stop();
		void mouse_LBtnDown(WPARAM wParam, POINT pt);
		void mouse_LBtnUp(WPARAM wParam, POINT pt);
		void mouse_LBtnDClick(WPARAM wParam, POINT pt);
		void mouse_RBtnDown(WPARAM wParam, POINT pt);
		void mouse_RBtnUp(WPARAM wParam, POINT pt);
		void mouse_RBtnDClick(WPARAM wParam, POINT pt);
		void mouse_Move(WPARAM wParam, POINT pt);
		void mouse_Wheel(WPARAM wParam, POINT pt);
		void keyboard_keyDown(int  nVkCode);
		void keyboard_keyUp(int nVkCode);
		void keyboard_charnum(WPARAM wParam, int nNum);
		void keyboard_copy(const std::string &copycontext);
		void keyboard_paste(const std::string &pastecontext);

	private:

		std::string m_strCommUID;
		CAgoraSignalWrapper* m_pSignalWrapper;
	};
}//AgoraRemoteTransfer

#endif