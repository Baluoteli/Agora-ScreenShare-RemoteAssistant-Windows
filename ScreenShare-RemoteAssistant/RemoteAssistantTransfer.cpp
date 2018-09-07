#include "stdafx.h"
#include "RemoteAssistantTransfer.h"
using namespace AgoraRemoteTransfer;
#include "AgoraSignalWrapper.h"

CAgoraRemoteTransfer::CAgoraRemoteTransfer():
m_pSignalWrapper(nullptr)
{
	m_pSignalWrapper = CAgoraSignalWrapper::getInstance();
}

CAgoraRemoteTransfer::~CAgoraRemoteTransfer()
{
	m_pSignalWrapper = nullptr;
}

void CAgoraRemoteTransfer::start()
{

}

void CAgoraRemoteTransfer::stop()
{

}

void CAgoraRemoteTransfer::mouse_LBtnDown(POINT pt)
{

}

void CAgoraRemoteTransfer::mouse_LBtnUp(POINT pt)
{

}

void CAgoraRemoteTransfer::mouse_LBtnDClick(POINT pt)
{

}

void CAgoraRemoteTransfer::mouse_RBtnDown(POINT pt)
{

}

void CAgoraRemoteTransfer::mouse_RBtnUp(POINT pt)
{

}

void CAgoraRemoteTransfer::mouse_RBtnDClick(POINT pt)
{

}

void CAgoraRemoteTransfer::keyboard_charnum(int nNum)
{

}

void CAgoraRemoteTransfer::keyboard_copy(const std::string &copycontext)
{

}

void CAgoraRemoteTransfer::keyboard_paste(const std::string &copycontext)
{

}
