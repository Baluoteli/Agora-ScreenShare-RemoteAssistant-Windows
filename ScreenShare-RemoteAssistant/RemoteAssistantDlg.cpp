// RemoteAssistantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenShare-RemoteAssistant.h"
#include "RemoteAssistantDlg.h"
#include "afxdialogex.h"
#include "AgoraMediaWrapper.h"


// CRemoteAssistantDlg dialog

IMPLEMENT_DYNAMIC(CRemoteAssistantDlg, CDialogEx)

CRemoteAssistantDlg::CRemoteAssistantDlg(UINT uID,CWnd* pParent /*=NULL*/)
	: CDialogEx(CRemoteAssistantDlg::IDD, pParent),
	m_nScreenH(0),
	m_nScreenW(0),
	m_pMediaWrapper(nullptr),
	m_uRemoteID(uID)
{

}

CRemoteAssistantDlg::~CRemoteAssistantDlg()
{
}

void CRemoteAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRemoteAssistantDlg, CDialogEx)
END_MESSAGE_MAP()


// CRemoteAssistantDlg message handlers
BOOL CRemoteAssistantDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_nScreenW = GetSystemMetrics(SM_CXSCREEN);
	m_nScreenH = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(0, 0, m_nScreenW, m_nScreenH);

	m_pMediaWrapper = CAgoraMediaWrapper::getInstance();
	if (m_pMediaWrapper) {
		m_pMediaWrapper->setRemoteVideo(m_hWnd, m_uRemoteID);
	}

	return TRUE;
}

int CRemoteAssistantDlg::PreTranslateMessage(MSG* pMsg)
{

	return CDialogEx::PreTranslateMessage(pMsg);
}