#include "stdafx.h"
#include "AgoraSignalWrapper.h"
#include "AgoraConfig.h"
#include "AGSignalCallBack.h"

CSingleton<CAgoraSignalWrapper>::CGrabo CAgoraSignalWrapper::graboSignalWrapper;

CAgoraSignalWrapper::CAgoraSignalWrapper():
m_pSignalCallBack(nullptr)
{
	m_AppId = CAgoraConfig::getInstance()->getAppId();
	m_AppCertificateId = CAgoraConfig::getInstance()->getAppCertificateId();
	initSignalEngine();
}

CAgoraSignalWrapper::~CAgoraSignalWrapper()
{
	LeaveChannel();
	LogOut();
	uninitSignalEngine();
}

void CAgoraSignalWrapper::initSignalEngine()
{
	m_AgoraAPI = getAgoraSDKInstanceWin(m_AppId.data(), m_AppId.size());
}

void CAgoraSignalWrapper::uninitSignalEngine()
{
	m_AgoraAPI->callbackSet(nullptr);
	delete m_pSignalCallBack;
	m_pSignalCallBack = nullptr;
}

void CAgoraSignalWrapper::setCallBackWnd(HWND wnd)
{
	m_pSignalCallBack = new CAGSignalCallBack(wnd);
	m_AgoraAPI->callbackSet(m_pSignalCallBack);
}

IAgoraAPI* CAgoraSignalWrapper::getAgoraAPI()
{
	return m_AgoraAPI;
}

void CAgoraSignalWrapper::setChannelKey(const std::string &channelKey)
{
	m_channelKey = channelKey;
}

std::string CAgoraSignalWrapper::getChannelKey()
{
	return m_channelKey;
}

bool CAgoraSignalWrapper::Login(const std::string &account)
{
	if (m_AgoraAPI){
		m_Account = account;
		int retryCount = 3;
		int retryTime = 30;
		m_AgoraAPI->login2(CAgoraWrapperUtilc::gbk2utf8(m_AppId).data(), CAgoraWrapperUtilc::gbk2utf8(m_AppId).size(), CAgoraWrapperUtilc::gbk2utf8(m_Account).data(), CAgoraWrapperUtilc::gbk2utf8(m_Account).size(), CAgoraWrapperUtilc::gbk2utf8(m_channelKey).data(), CAgoraWrapperUtilc::gbk2utf8(m_channelKey).size(), 0, "", 0, retryTime, retryCount);
		return TRUE;
	}

	return FALSE;
}

bool CAgoraSignalWrapper::LogOut()
{
	if (m_AgoraAPI){
		m_AgoraAPI->logout();
	}

	return FALSE;
}

bool CAgoraSignalWrapper::QueryIsOnline(const std::string &account)
{
	if (m_AgoraAPI){
		m_AgoraAPI->queryUserStatus(CAgoraWrapperUtilc::gbk2utf8(account).data(), CAgoraWrapperUtilc::gbk2utf8(account).size());
		return TRUE;
	}

	return FALSE;
}

bool CAgoraSignalWrapper::sendInstantMsg(const std::string &account, const std::string &instanmsg)
{
	if (m_AgoraAPI){
		std::string msgId = CAgoraWrapperUtilc::int2str(GetTickCount());
		m_AgoraAPI->messageInstantSend(CAgoraWrapperUtilc::gbk2utf8(account).data(), CAgoraWrapperUtilc::gbk2utf8(account).size(), 0, CAgoraWrapperUtilc::gbk2utf8(instanmsg).data(), CAgoraWrapperUtilc::gbk2utf8(instanmsg).size(), CAgoraWrapperUtilc::gbk2utf8(msgId).data(), CAgoraWrapperUtilc::gbk2utf8(msgId).size());
	}

	return FALSE;
}

bool CAgoraSignalWrapper::sendChannelMsg(const std::string &channel, const std::string &ChannelMsg)
{
	if (m_AgoraAPI){
		std::string msgId = "ChannelMsg";
		m_AgoraAPI->messageChannelSend(CAgoraWrapperUtilc::gbk2utf8(channel).data(), CAgoraWrapperUtilc::gbk2utf8(channel).size(), CAgoraWrapperUtilc::gbk2utf8(ChannelMsg).data(), CAgoraWrapperUtilc::gbk2utf8(ChannelMsg).size(), CAgoraWrapperUtilc::gbk2utf8(msgId).data(), CAgoraWrapperUtilc::gbk2utf8(msgId).size());
		return TRUE;
	}

	return FALSE;
}

bool CAgoraSignalWrapper::JoinChannel(const std::string &channelID)
{
	if (m_AgoraAPI){
		m_AgoraAPI->channelJoin(CAgoraWrapperUtilc::gbk2utf8(channelID).data(), CAgoraWrapperUtilc::gbk2utf8(channelID).size());
		m_ChannelName = channelID;
		return TRUE;
	}

	return FALSE;
}

bool CAgoraSignalWrapper::LeaveChannel()
{
	if (m_AgoraAPI){
		m_AgoraAPI->channelLeave(CAgoraWrapperUtilc::gbk2utf8(m_ChannelName).data(), CAgoraWrapperUtilc::gbk2utf8(m_ChannelName).size());
		return TRUE;
	}

	return FALSE;
}

std::string CAgoraSignalWrapper::getSDKVersion()
{
	if (m_AgoraAPI){
		return  std::string("SDKVERSION: ") + CAgoraWrapperUtilc::int2str(m_AgoraAPI->getSdkVersion());
	}

	return "";
}