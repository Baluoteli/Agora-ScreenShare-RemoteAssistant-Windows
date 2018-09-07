#ifndef __REMOTEASSISTANTTRANSFER_H__
#define __REMOTEASSISTANTTRANSFER_H__

class CAgoraSignalWrapper;
namespace AgoraRemoteTransfer {

	enum RemoteTransferType {
		eTransfer_NULL = 0,
		eTransfer_Mouse_LBtnDown = 0x0001,
		eTransfer_Mouse_LBtnUp = eTransfer_Mouse_LBtnDown * 2,
		eTransfer_Mouse_LBtnDClick = eTransfer_Mouse_LBtnUp * 2,
		eTransfer_Mouse_Move = eTransfer_Mouse_LBtnDClick * 2,
		eTransfer_Mouse_RBtnDown = eTransfer_Mouse_Move * 2,
		eTransfer_Mouse_RBtnUp = eTransfer_Mouse_RBtnDown * 2,
		eTransfer_Mouse_RBtnDClick = eTransfer_Mouse_RBtnUp * 2,
		eTransfer_KeyBoard_CharNum = eTransfer_Mouse_RBtnDClick * 2,
		eTransfer_KeyBoard_Copy = eTransfer_KeyBoard_CharNum * 2,
		eTransfer_KeyBoard_Paste = eTransfer_KeyBoard_Copy * 2,
		eTransfer_StartAssistant = eTransfer_KeyBoard_Paste * 2,
		eTransfer_StopAssistant = eTransfer_StartAssistant * 2,

		eTransfer_UNKNOWN = 0xffff,

	};

	class CAgoraRemoteTransfer{

	public:
		CAgoraRemoteTransfer();
		~CAgoraRemoteTransfer();

		void start();
		void stop();
		void mouse_LBtnDown(POINT pt);
		void mouse_LBtnUp(POINT pt);
		void mouse_LBtnDClick(POINT pt);
		void mouse_RBtnDown(POINT pt);
		void mouse_RBtnUp(POINT pt);
		void mouse_RBtnDClick(POINT pt);
		void keyboard_charnum(int nNum);
		void keyboard_copy(const std::string &copycontext);
		void keyboard_paste(const std::string &copycontext);

	private:
		
		CAgoraSignalWrapper* m_pSignalWrapper;
	};
}//AgoraRemoteTransfer

#endif