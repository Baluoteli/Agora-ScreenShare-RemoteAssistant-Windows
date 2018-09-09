#ifndef __REMOTEASSISTANTTRANSFER_H__
#define __REMOTEASSISTANTTRANSFER_H__

class CAgoraSignalWrapper;
namespace AgoraRemoteTransfer {

	enum RemoteTransferType {
		eTransfer_NULL = 0,
		eTransfer_Mouse_LBtnDown = 0x01,
		eTransfer_Mouse_LBtnUp,
		eTransfer_Mouse_LBtnDClick,
		eTransfer_Mouse_Move,
		eTransfer_Mouse_RBtnDown,
		eTransfer_Mouse_RBtnUp,
		eTransfer_Mouse_RBtnDClick,
		eTransfer_Mouse_Wheel,
		eTransfer_KeyBoard_CharNum,
		eTransfer_KeyBoard_Copy,
		eTransfer_KeyBoard_Paste,
		eTransfer_StartAssistant,
		eTransfer_StopAssistant,

		eTransfer_UNKNOWN = 0xffff,

	};

	//Remote Transfer Define


	class CAgoraRemoteTransfer{

	public:
		CAgoraRemoteTransfer();
		CAgoraRemoteTransfer(const std::string &strUID);
		~CAgoraRemoteTransfer();

		void setRemoteUID(const std::string &strUID);

		void start();
		void stop();
		void mouse_LBtnDown(WPARAM wParam, POINT pt);
		void mouse_LBtnUp(WPARAM wParam,POINT pt);
		void mouse_LBtnDClick(WPARAM wParam,POINT pt);
		void mouse_RBtnDown(WPARAM wParam,POINT pt);
		void mouse_RBtnUp(WPARAM wParam,POINT pt);
		void mouse_RBtnDClick(WPARAM wParam,POINT pt);
		void mouse_Move(WPARAM wParam,POINT pt);
		void mouse_Wheel(WPARAM wParam,POINT pt);
		void keyboard_charnum(WPARAM wParam,int nNum);
		void keyboard_copy(const std::string &copycontext);
		void keyboard_paste(const std::string &pastecontext);

	private:
		
		std::string m_strCommUID;
		CAgoraSignalWrapper* m_pSignalWrapper;
	};
}//AgoraRemoteTransfer

#endif