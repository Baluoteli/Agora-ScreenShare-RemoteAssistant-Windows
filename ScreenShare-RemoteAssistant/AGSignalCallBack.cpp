#include "stdafx.h"
#include "AGSignalCallBack.h"


CAGSignalCallBack::CAGSignalCallBack(HWND wnd) :m_MsgWnd(wnd)
{
}

CAGSignalCallBack::CAGSignalCallBack()
{

}

CAGSignalCallBack::~CAGSignalCallBack()
{
	m_MsgWnd = nullptr;
}

void CAGSignalCallBack::setCallBackWnd(HWND wnd)
{
	m_MsgWnd = wnd;
}

void CAGSignalCallBack::onReconnecting(uint32_t nretry)
{
}

void CAGSignalCallBack::onReconnected(int fd)
{
}

void CAGSignalCallBack::onLoginSuccess(uint32_t uid, int fd)
{
	PAG_SIGNAL_LOGINSUCCESS lpData = new AG_SIGNAL_LOGINSUCCESS;
	lpData->fd = fd;
	lpData->uid = uid;

	postMsg(WM_LoginSuccess, WPARAM(lpData));
}

void CAGSignalCallBack::onLogout(int ecode)
{
	PAG_SIGNAL_LOGOUT lpData = new AG_SIGNAL_LOGOUT;
	lpData->ecode = ecode;

	postMsg(WM_LogOut, WPARAM(lpData), LPARAM(ecode));
}

void CAGSignalCallBack::onLoginFailed(int ecode)
{
	PAG_SIGNAL_LOGINFAILED lpData = new AG_SIGNAL_LOGINFAILED;
	lpData->ecode = ecode;

	postMsg(WM_LoginFailed, WPARAM(lpData), LPARAM(ecode));
}

void CAGSignalCallBack::onChannelJoined(char const * channelID, size_t channelID_size)
{
	PAG_SIGNAL_CHANNELJOIN lpData = new AG_SIGNAL_CHANNELJOIN;
	lpData->channelID = CAgoraWrapperUtilc::utf82gbk(channelID);

	postMsg(WM_ChannelJoined, WPARAM(lpData));
}

void CAGSignalCallBack::onChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode)
{
	PAG_SIGNAL_CHANNELJOINFAILED lpData = new AG_SIGNAL_CHANNELJOINFAILED;
	lpData->channelID = CAgoraWrapperUtilc::utf82gbk(channelID);
	lpData->ecode = ecode;

	postMsg(WM_ChannelJoinedFailed, WPARAM(lpData));
}

void CAGSignalCallBack::onChannelLeaved(char const * channelID, size_t channelID_size, int ecode)
{
	PAG_SIGNAL_CHANNELLEAVE lpData = new AG_SIGNAL_CHANNELLEAVE;
	lpData->channelID = CAgoraWrapperUtilc::utf82gbk(channelID);
	lpData->ecode = ecode;

	postMsg(WM_ChannelLeaved, WPARAM(lpData));
}

void CAGSignalCallBack::onChannelUserJoined(char const * account, size_t account_size, uint32_t uid)
{
}

void CAGSignalCallBack::onChannelUserLeaved(char const * account, size_t account_size, uint32_t uid)
{
}

void CAGSignalCallBack::onChannelUserList(int n, char** accounts, uint32_t* uids)
{
}

void CAGSignalCallBack::onChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num)
{
}

void CAGSignalCallBack::onChannelQueryUserIsIn(char const * channelID, size_t channelID_size, char const * account, size_t account_size, int isIn)
{

}

void CAGSignalCallBack::onChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size)
{
}

void CAGSignalCallBack::onInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void CAGSignalCallBack::onInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
}

void CAGSignalCallBack::onInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void CAGSignalCallBack::onInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void CAGSignalCallBack::onInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode, char const * extra, size_t extra_size)
{
}

void CAGSignalCallBack::onInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
}

void CAGSignalCallBack::onInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
}

void CAGSignalCallBack::onInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size)
{
}

void CAGSignalCallBack::onMessageSendError(char const * messageID, size_t messageID_size, int ecode)
{
	PAG_SIGNAL_MESSAGESENDERROR lpData = new AG_SIGNAL_MESSAGESENDERROR;
	lpData->message = CAgoraWrapperUtilc::utf82gbk(messageID);
	lpData->ecode = ecode;

	postMsg(WM_MessageSendError, WPARAM(lpData));
}

void CAGSignalCallBack::onMessageSendProgress(char const * account, size_t account_size, char const * messageID, size_t messageID_size, char const * type, size_t type_size, char const * info, size_t info_size)
{
}

void CAGSignalCallBack::onMessageSendSuccess(char const * messageID, size_t messageID_size)
{
	PAG_SIGNAL_MESSAGESENDSUCCESS  lpData = new AG_SIGNAL_MESSAGESENDSUCCESS;
	lpData->messageID = CAgoraWrapperUtilc::utf82gbk(messageID);

	postMsg(WM_MessageSendSuccess, WPARAM(lpData));
}

void CAGSignalCallBack::onMessageAppReceived(char const * msg, size_t msg_size)
{
}

void CAGSignalCallBack::onMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	PAG_SIGNAL_MESSAGEINSTANCERECEIVE lpData = new AG_SIGNAL_MESSAGEINSTANCERECEIVE;
	lpData->account = CAgoraWrapperUtilc::utf82gbk(account);
	lpData->uid = uid;
	lpData->msg = CAgoraWrapperUtilc::utf82gbk(msg);

	postMsg(WM_MessageInstantReceive, WPARAM(lpData));
}

void CAGSignalCallBack::onMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	PAG_SIGNAL_MESSAGECHANNELRECEIVE lpData = new AG_SIGNAL_MESSAGECHANNELRECEIVE;
	lpData->account = CAgoraWrapperUtilc::utf82gbk(account);
	lpData->channelID = CAgoraWrapperUtilc::utf82gbk(channelID);
	lpData->uid = uid;
	lpData->msg = CAgoraWrapperUtilc::utf82gbk(msg);

	postMsg(WM_MessageChannelReceive, WPARAM(lpData));
}

void CAGSignalCallBack::onLog(char const * txt, size_t txt_size)
{
	PAG_SIGNAL_LOG lpData = new AG_SIGNAL_LOG;
	lpData->txt = CAgoraWrapperUtilc::utf82gbk(txt);

	postMsg(WM_Log, WPARAM(lpData));
}

void CAGSignalCallBack::onInvokeRet(char const * callID, size_t callID_size, char const * err, size_t err_size, char const * resp, size_t resp_size)
{
}

void CAGSignalCallBack::onMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size)
{
}

void CAGSignalCallBack::onUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size)
{
}

void CAGSignalCallBack::onUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size)
{
}

void CAGSignalCallBack::onError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size)
{
	PAG_SIGNAL_ERROR lpData = new AG_SIGNAL_ERROR;
	lpData->name = CAgoraWrapperUtilc::utf82gbk(name);
	lpData->ecode = ecode;
	lpData->desc = CAgoraWrapperUtilc::utf82gbk(desc);

	postMsg(WM_Error, WPARAM(lpData), NULL);
}

void CAGSignalCallBack::onQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size)
{
	PAG_SIGNAL_QUERYUSERSTATUSRESULT lpData = new AG_SIGNAL_QUERYUSERSTATUSRESULT;
	lpData->name = CAgoraWrapperUtilc::utf82gbk(name);
	lpData->status = CAgoraWrapperUtilc::utf82gbk(status);

	postMsg(WM_QueryUserStatusResult, WPARAM(lpData));
}

void CAGSignalCallBack::onDbg(char const * a, size_t a_size, char const * b, size_t b_size)
{
	int i = 0;
}

void CAGSignalCallBack::onBCCall_result(char const * reason, size_t reason_size, char const * json_ret, size_t json_ret_size, char const * callID, size_t callID_size)
{
}

void CAGSignalCallBack::postMsg(UINT msg, WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/)
{
	::PostMessage(m_MsgWnd, msg, wParam, lParam);
}