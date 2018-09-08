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
		eTransfer_KeyBoard_CharNum,
		eTransfer_KeyBoard_Copy,
		eTransfer_KeyBoard_Paste,
		eTransfer_StartAssistant,
		eTransfer_StopAssistant,

		eTransfer_UNKNOWN = 0xffff,

	};
	
	//keyboard vk code.
	const int const KVK_BACK = VK_BACK;
	const int const KVK_TAB = VK_TAB;
	const int const KVK_RETURN = VK_RETURN;
	const int const KVK_CONTROL = VK_CONTROL;
	const int const KVK_SHIFT = VK_SHIFT;
	const int const KVK_SPACE = VK_SPACE;
	const int const KVK_NUM_0 = 0x30;
	const int const KVK_NUM_9 = 0x39;
	const int const KVK_CHAR_A = 0x41;
	const int const KVK_CHAR_Z = 0x5A;
	const int const KVK_F1 = VK_F1;
	const int const KVK_F12 = VK_F12;

	//Remote Transfer Define


	class CAgoraRemoteTransfer{

	public:
		CAgoraRemoteTransfer();
		CAgoraRemoteTransfer(const std::string &strUID);
		~CAgoraRemoteTransfer();

		void setRemoteUID(const std::string &strUID);

		void start();
		void stop();
		void mouse_LBtnDown(POINT pt);
		void mouse_LBtnUp(POINT pt);
		void mouse_LBtnDClick(POINT pt);
		void mouse_RBtnDown(POINT pt);
		void mouse_RBtnUp(POINT pt);
		void mouse_RBtnDClick(POINT pt);
		void mouse_Move(POINT pt);
		void keyboard_charnum(int nNum);
		void keyboard_copy(const std::string &copycontext);
		void keyboard_paste(const std::string &pastecontext);

	private:
		
		std::string m_strCommUID;
		CAgoraSignalWrapper* m_pSignalWrapper;
	};
}//AgoraRemoteTransfer

#endif