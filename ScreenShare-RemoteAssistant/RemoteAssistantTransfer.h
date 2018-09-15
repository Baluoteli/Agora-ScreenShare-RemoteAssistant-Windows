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


	//Remote Transfer Define
#define EVENTPARAM	"param"
#define CMDTYPE			"cmdType"
#define TIMESTAMP		"timestamp"
#define POSITION			"point"
#define VKEYCODE       "keyCode"
#define SCROLDELTA	"scrolDelta"


	class CAgoraRemoteTransfer{

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