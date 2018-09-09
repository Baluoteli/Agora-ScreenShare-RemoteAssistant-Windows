// RemoteAssistantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenShare-RemoteAssistant.h"
#include "RemoteAssistantDlg.h"
#include "afxdialogex.h"
#include "AgoraConfig.h"
#include "AgoraMediaWrapper.h"
#include "AgoraSignalWrapper.h"


// CRemoteAssistantDlg dialog

IMPLEMENT_DYNAMIC(CRemoteAssistantDlg, CDialogEx)

CRemoteAssistantDlg::CRemoteAssistantDlg(UINT uID,CWnd* pParent /*=NULL*/)
	: CDialogEx(CRemoteAssistantDlg::IDD, pParent),
	m_nScreenH(0),
	m_nScreenW(0),
	m_pMediaWrapper(nullptr),
	m_uRemoteID(uID)
{
	m_AgoraRemoteTransfer.setRemoteUID(CAgoraWrapperUtilc::int2str(uID));
}

CRemoteAssistantDlg::~CRemoteAssistantDlg()
{
}

void CRemoteAssistantDlg::setRemoteScreenSolution(int nWidth, int nHeight)
{
	m_nRemoteScreenX = nWidth;
	m_nRemoteScreenY = nHeight;
}

void CRemoteAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRemoteAssistantDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_LoginSuccess,onLoginSuccess)
	ON_MESSAGE(WM_LoginFailed,onLogFailed)
	ON_MESSAGE(WM_LogOut,onLogout)
	ON_MESSAGE(WM_Error,onError)
	ON_MESSAGE(WM_Log,onLog)
	ON_MESSAGE(WM_QueryUserStatusResult,onQueryUserStatusResult)
	ON_MESSAGE(WM_MessageSendSuccess,onMessageSendSuccess)
	ON_MESSAGE(WM_MessageSendError,onMessageSendError)
	ON_MESSAGE(WM_MessageInstantReceive,onMessageInstantReceive)
	ON_MESSAGE(WM_MessageChannelReceive,onMessageChannelReceive)
	ON_MESSAGE(WM_ChannelJoined,onChannelJoined)
	ON_MESSAGE(WM_ChannelJoinedFailed,onChannelJoinFailed)
	ON_MESSAGE(WM_ChannelLeaved,onChannelLeaved)
END_MESSAGE_MAP()


// CRemoteAssistantDlg message handlers
BOOL CRemoteAssistantDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_nScreenW = GetSystemMetrics(SM_CXSCREEN);
	m_nScreenH = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(0, 0, m_nScreenW, m_nScreenH);
	m_penFrame.CreatePen(PS_SOLID, 4, RGB(0x00, 0xA0, 0xE9));
	CRect rt;
	GetClientRect(&rt);
	ClientToScreen(&rt);
	//::SetWindowPos(m_hWnd,HWND_TOPMOST, rt.left, rt.top, rt.Width(), rt.Height(), SWP_SHOWWINDOW);

	m_pMediaWrapper = CAgoraMediaWrapper::getInstance();
	if (m_pMediaWrapper) {
		m_pMediaWrapper->setRemoteVideo(m_hWnd, m_uRemoteID);
	}

	initCtrl();
	initSignalResource();

	return TRUE;
}

void CRemoteAssistantDlg::initCtrl()
{

}

void CRemoteAssistantDlg::initSignalResource()
{
	m_AgoraRemoteTransfer.start();
}

void CRemoteAssistantDlg::uninitResource()
{
}

int CRemoteAssistantDlg::PreTranslateMessage(MSG* pMsg)
{
	//Êó±ê: ×ó¼üµ¥»÷,×ó¼üË«»÷,ÓÒ¼üµ¥»÷,ÓÒ¼üË«»÷,ÍÏ¶¯.
	//¼üÅÌ:Êý×Ö,×ÖÄ¸.
	//¿ì½Ý¼ü:ctrl+c,ctrl+v
	static bool bCtrlKey = false;
	WPARAM wParam;
	if (pMsg->hwnd == m_hWnd && false) {

		switch (pMsg->message)
		{
		case WM_LBUTTONDBLCLK:
		{
			CPoint pt;
			int nXpos = GET_X_LPARAM(pMsg->lParam);
			int nYpos = GET_Y_LPARAM(pMsg->lParam);
			pt.SetPoint(nXpos, nYpos);
			
			m_AgoraRemoteTransfer.mouse_LBtnDClick(wParam,pt);
		}
			break;
		case WM_LBUTTONDOWN:
		{
			CPoint pt;
			int nXpos = GET_X_LPARAM(pMsg->lParam);
			int nYpos = GET_Y_LPARAM(pMsg->lParam);
			pt.SetPoint(nXpos, nYpos);

			m_AgoraRemoteTransfer.mouse_LBtnDown(wParam,pt);
		}
			break;
		case WM_LBUTTONUP:
		{
			CPoint pt;
			int nXpos = GET_X_LPARAM(pMsg->lParam);
			int nYpos = GET_Y_LPARAM(pMsg->lParam);
			pt.SetPoint(nXpos, nYpos);

			m_AgoraRemoteTransfer.mouse_LBtnUp(wParam,pt);
		}
			break;
		case WM_RBUTTONDBLCLK:
		{
			CPoint pt;
			int nXpos = GET_X_LPARAM(pMsg->lParam);
			int nYpos = GET_Y_LPARAM(pMsg->lParam);
			pt.SetPoint(nXpos, nYpos);

			m_AgoraRemoteTransfer.mouse_RBtnDClick(wParam,pt);
		}
			break;
		case WM_RBUTTONUP: 
		{
			CPoint pt;
			int nXpos = GET_X_LPARAM(pMsg->lParam);
			int nYpos = GET_Y_LPARAM(pMsg->lParam);
			pt.SetPoint(nXpos, nYpos);

			m_AgoraRemoteTransfer.mouse_RBtnUp(wParam,pt);
		}
			break;
		case WM_RBUTTONDOWN:
		{
			CPoint pt;
			int nXpos = GET_X_LPARAM(pMsg->lParam);
			int nYpos = GET_Y_LPARAM(pMsg->lParam);
			pt.SetPoint(nXpos, nYpos);

			m_AgoraRemoteTransfer.mouse_RBtnDown(wParam,pt);
		}
			break;
		case WM_MOUSEMOVE:
		{
			CPoint pt;
			int nXpos = GET_X_LPARAM(pMsg->lParam);
			int nYpos = GET_Y_LPARAM(pMsg->lParam);
			pt.SetPoint(nXpos, nYpos);

			m_AgoraRemoteTransfer.mouse_Move(wParam,pt);
		}
			break;
		case WM_CHAR:
		{
// 			char ch = pMsg->wParam;
// 			
// 			if ('C' == ch || 'c' == ch)
// 				m_AgoraRemoteTransfer.keyboard_copy("");
// 			else if ('v' == ch || 'V' == ch)
// 				m_AgoraRemoteTransfer.keyboard_paste("");
// 			else
// 				m_AgoraRemoteTransfer.keyboard_charnum(ch);
// 			bCtrlKey = false;
		}
			break;
		case WM_KEYDOWN:
		{
			UINT nKeyCode = pMsg->wParam;
			if (GetKeyState(VK_CONTROL) & 0x8000)
				if (nKeyCode == _T('C'))
					m_AgoraRemoteTransfer.keyboard_copy("");
				else if (_T('V') == nKeyCode)
					m_AgoraRemoteTransfer.keyboard_paste("");

			if (pMsg->wParam == 'V' && GetAsyncKeyState(VK_CONTROL)) {
				 
				int i = 0;
			}

			switch (pMsg->wParam)
			{
			case VK_F1:
			case VK_F2:
			case VK_F3:
			case VK_F4:
			case VK_F5:
			case VK_F6:
			case VK_F7:
			case VK_F8:
			case VK_F9:
			case VK_F10:
			case VK_F11:
			case VK_F12:
				break;
			case VK_BACK:
			case VK_RETURN:
			case VK_SPACE:
			case VK_TAB:
			case VK_ESCAPE:
			case VK_CONTROL:
			case VK_SHIFT:
				break;
			default:
				break;
			}
		}
			break;
		default:break;
		}
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CRemoteAssistantDlg::OnPaint()
{
	CPaintDC dc(this);
	CDC dcMem;
	CBitmap bmpBuffer;

	CRect rt;
	GetClientRect(&rt);

	dcMem.CreateCompatibleDC(&dc);
	bmpBuffer.CreateCompatibleBitmap(&dc, rt.Width(), rt.Height());

	CBitmap *lpOldBitmap = dcMem.SelectObject(&bmpBuffer);
	CPen* defPen = dcMem.SelectObject(&m_penFrame);
	dcMem.Rectangle(rt);
	::BitBlt(dc, 0, 0, rt.right, rt.bottom, dcMem, 0, 0, SRCCOPY);

	//dc.SelectObject(defPen);
}

void CRemoteAssistantDlg::OnClose()
{
	m_AgoraRemoteTransfer.stop();
	CDialogEx::OnCancel();
}

HRESULT CRemoteAssistantDlg::onLoginSuccess(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGINSUCCESS lpData = (PAG_SIGNAL_LOGINSUCCESS)wParam;
	if (lpData) {

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CRemoteAssistantDlg::onLogout(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGOUT lpData = (PAG_SIGNAL_LOGOUT)wParam;
	if (lpData) {

		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

HRESULT CRemoteAssistantDlg::onLogFailed(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGINFAILED lpData = (PAG_SIGNAL_LOGINFAILED)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CRemoteAssistantDlg::onError(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOIN lpData = (PAG_SIGNAL_CHANNELJOIN)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

LRESULT CRemoteAssistantDlg::onLog(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOG lpData = (PAG_SIGNAL_LOG)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CRemoteAssistantDlg::onQueryUserStatusResult(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_QUERYUSERSTATUSRESULT lpData = (PAG_SIGNAL_QUERYUSERSTATUSRESULT)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CRemoteAssistantDlg::onMessageSendSuccess(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGESENDSUCCESS lpData = (PAG_SIGNAL_MESSAGESENDSUCCESS)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CRemoteAssistantDlg::onMessageSendError(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGESENDERROR lpData = (PAG_SIGNAL_MESSAGESENDERROR)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CRemoteAssistantDlg::onMessageInstantReceive(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGEINSTANCERECEIVE lpData = (PAG_SIGNAL_MESSAGEINSTANCERECEIVE)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

HRESULT CRemoteAssistantDlg::onMessageChannelReceive(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGECHANNELRECEIVE lpData = (PAG_SIGNAL_MESSAGECHANNELRECEIVE)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CRemoteAssistantDlg::onChannelJoined(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOIN lpData = (PAG_SIGNAL_CHANNELJOIN)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

HRESULT CRemoteAssistantDlg::onChannelJoinFailed(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOINFAILED lpData = (PAG_SIGNAL_CHANNELJOINFAILED)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CRemoteAssistantDlg::onChannelLeaved(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELLEAVE lpData = (PAG_SIGNAL_CHANNELLEAVE)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}


void CRemoteAssistantDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	POINT ptRemote;
	ptRemote.x = point.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = point.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	WPARAM wParam = MAKEWPARAM(0, 0);
	m_AgoraRemoteTransfer.mouse_LBtnDClick(wParam,ptRemote);
}

void CRemoteAssistantDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT ptRemote;
	ptRemote.x = point.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = point.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	WPARAM wParam = MAKEWPARAM(0, 0);
	m_AgoraRemoteTransfer.mouse_LBtnDown(wParam,ptRemote);
}

void CRemoteAssistantDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	POINT ptRemote;
	ptRemote.x = point.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = point.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	WPARAM wParam = MAKEWPARAM(0, 0);
	m_AgoraRemoteTransfer.mouse_LBtnUp(wParam,ptRemote);
}

void CRemoteAssistantDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	POINT ptRemote;
	ptRemote.x = point.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = point.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	WPARAM wParam = MAKEWPARAM(0, 0);
	m_AgoraRemoteTransfer.mouse_RBtnDown(wParam,ptRemote);
}

void CRemoteAssistantDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	POINT ptRemote;
	ptRemote.x = point.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = point.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	WPARAM wParam = MAKEWPARAM(0, 0);
	m_AgoraRemoteTransfer.mouse_RBtnUp(wParam,ptRemote);
}

void CRemoteAssistantDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	POINT ptRemote;
	ptRemote.x = point.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = point.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	WPARAM wParam = MAKEWPARAM(0, 0);
	m_AgoraRemoteTransfer.mouse_RBtnDClick(wParam,ptRemote);
}

void CRemoteAssistantDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	POINT ptRemote;
	ptRemote.x = point.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = point.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	WPARAM wParam = MAKEWPARAM(0, 0);
	m_AgoraRemoteTransfer.mouse_Move(wParam,ptRemote);
}

void CRemoteAssistantDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	WPARAM wParam;
	wParam = MAKEWPARAM(nRepCnt, nFlags);

#if 0
	if (('C' == nChar || 'c' == nChar) && ::GetKeyState(VK_CONTROL) & 0x8000) {
		m_AgoraRemoteTransfer.keyboard_copy("");
	}
	else if (('V' == nChar || 'v' == nChar) && ::GetKeyState(VK_CONTROL) & 0x8000) {
		m_AgoraRemoteTransfer.keyboard_paste("");
	}
	else
		m_AgoraRemoteTransfer.keyboard_charnum(wParam,nChar);

#endif

	m_AgoraRemoteTransfer.keyboard_charnum(wParam, nChar);
}

BOOL CRemoteAssistantDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	WPARAM wParam;
	wParam = MAKEWPARAM(nFlags,zDelta);
	POINT ptRemote;
	ptRemote.x = pt.x * 1.0 * m_nRemoteScreenX / m_nScreenW;
	ptRemote.y = pt.y * 1.0 * m_nRemoteScreenY / m_nScreenH;
	m_AgoraRemoteTransfer.mouse_Wheel(wParam, ptRemote);

	return TRUE;
}