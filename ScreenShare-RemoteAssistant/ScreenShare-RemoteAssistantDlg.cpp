
// ScreenShare-RemoteAssistantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenShare-RemoteAssistant.h"
#include "ScreenShare-RemoteAssistantDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "AgoraConfig.h"
#include "AgoraMediaWrapper.h"
#include "AgoraSignalWrapper.h"
#include "AGEngineEventHandler.h"
#include "RemoteAssistantDlg.h"
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScreenShareRemoteAssistantDlg dialog

UINT CScreenShareRemoteAssistantDlg::uSelectUID = 0;

CScreenShareRemoteAssistantDlg::CScreenShareRemoteAssistantDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenShareRemoteAssistantDlg::IDD, pParent),
	m_pAgoraMediaWrapper(nullptr),
	m_pSignalWrapper(nullptr),
	m_pAgoraConfig(nullptr),
	m_hScreenWnd(nullptr),
	m_pScreenShareRemoteDlg(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenShareRemoteAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHANNELNAME, m_editChannelName);
	DDX_Control(pDX, IDC_EDIT_UID, m_editUID);
	DDX_Control(pDX, IDC_BUTTON_JOIN, m_btnJoin);
	DDX_Control(pDX, IDC_BUTTON_LEAVE, m_btnLeave);
	DDX_Control(pDX, IDC_BUTTON_REMOTE_ASSISTANT, m_btnRemoteAssistant);
	DDX_Control(pDX, IDC_LIST_UserList, m_ltMediaUserList);
	DDX_Control(pDX, IDC_LIST_SIGNAL, m_ltSignalMsgInfo);
	DDX_Control(pDX, IDC_CHECK_MEDIA, m_checkMedia);
	DDX_Control(pDX, IDC_CHECK_SIGNAL, m_checkSignal);
}

BEGIN_MESSAGE_MAP(CScreenShareRemoteAssistantDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &CScreenShareRemoteAssistantDlg::OnBnClickedButtonJoin)
	ON_BN_CLICKED(IDC_BUTTON_LEAVE, &CScreenShareRemoteAssistantDlg::OnBnClickedButtonLeave)
	ON_BN_CLICKED(IDC_BUTTON_REMOTE_ASSISTANT, &CScreenShareRemoteAssistantDlg::OnBnClickedButtonRemoteAssistant)
	ON_MESSAGE(WM_MSGID(EID_JOINCHANNEL_SUCCESS), &CScreenShareRemoteAssistantDlg::OnEIDJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_REJOINCHANNEL_SUCCESS), &CScreenShareRemoteAssistantDlg::OnEIDReJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_LEAVE_CHANNEL), CScreenShareRemoteAssistantDlg::OnEIDLeaveChannel)
	ON_MESSAGE(WM_MSGID(EID_FIRST_LOCAL_VIDEO_FRAME), &CScreenShareRemoteAssistantDlg::OnEIDFirstLocalFrame)
	ON_MESSAGE(WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), &CScreenShareRemoteAssistantDlg::OnEIDFirstRemoteFrameDecoded)
	ON_MESSAGE(WM_MSGID(EID_USER_JOINED), &CScreenShareRemoteAssistantDlg::OnEIDUserJoined)
	ON_MESSAGE(WM_MSGID(EID_USER_OFFLINE), &CScreenShareRemoteAssistantDlg::OnEIDUserOffline)
	ON_MESSAGE(WM_MSGID(EID_USER_MUTE_AUDIO), &CScreenShareRemoteAssistantDlg::OnEIDMuteAudio)
	ON_MESSAGE(WM_MSGID(EID_USER_MUTE_VIDEO), &CScreenShareRemoteAssistantDlg::OnEIDMuteVideo)
	ON_MESSAGE(WM_MSGID(EID_REMOTE_VIDEO_STAT), &CScreenShareRemoteAssistantDlg::OnRemoteVideoStat)
	ON_MESSAGE(WM_MSGID(EID_START_RCDSRV), &CScreenShareRemoteAssistantDlg::OnStartRecordingService)
	ON_MESSAGE(WM_MSGID(EID_STOP_RCDSRV), &CScreenShareRemoteAssistantDlg::OnStopRecordingService)
	ON_LBN_DBLCLK(IDC_LIST_UserList, &CScreenShareRemoteAssistantDlg::OnLbnDblclkListUserlist)
	ON_MESSAGE(WM_LoginSuccess, onLoginSuccess)
	ON_MESSAGE(WM_LoginFailed, onLogFailed)
	ON_MESSAGE(WM_LogOut, onLogout)
	ON_MESSAGE(WM_Error, onError)
	ON_MESSAGE(WM_Log, onLog)
	ON_MESSAGE(WM_QueryUserStatusResult, onQueryUserStatusResult)
	ON_MESSAGE(WM_MessageSendSuccess, onMessageSendSuccess)
	ON_MESSAGE(WM_MessageSendError, onMessageSendError)
	ON_MESSAGE(WM_MessageInstantReceive, onMessageInstantReceive)
	ON_MESSAGE(WM_MessageChannelReceive, onMessageChannelReceive)
	ON_MESSAGE(WM_ChannelJoined, onChannelJoined)
	ON_MESSAGE(WM_ChannelJoinedFailed, onChannelJoinFailed)
	ON_MESSAGE(WM_ChannelLeaved, onChannelLeaved)
END_MESSAGE_MAP()


// CScreenShareRemoteAssistantDlg message handlers

BOOL CScreenShareRemoteAssistantDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here	
	std::string strAppId = CAgoraConfig::getInstance()->getAppId();
	if ("" == strAppId) {
		AfxMessageBox(L"AppId is empty, please input .");
		PostQuitMessage(0);
		return FALSE;
	}

	//to do
	char ch = ',';
	UINT ii = ch;
	ch = '.';
	ii = ch;
	ch = '/';
	ii = ch;
#if 0

	time_t ltime;
	time(&ltime);
	int lasttime = ltime;
	Sleep(2000);
	time(&ltime);
	int nexttime = ltime;

	SYSTEMTIME st, st1;
	GetSystemTime(&st);
	Sleep(1223);
	GetSystemTime(&st1);

	CJsonObject object;
	object.Add(CMDTYPE, 1024);
	GetLocalTime(&st);
	char szbuf[MAX_PATH] = { '\0' };
	sprintf_s(szbuf, "%d:%d:%d:%d", st.wHour, st.wMinute, st.wMinute, st.wMilliseconds);
	object.Add("sTimtStamp", szbuf);
	object.AddEmptySubObject("EventParam");
	object["EventParam"].AddEmptySubObject("point");
	object["EventParam"]["point"].Add("xPos", 10);
	object["EventParam"]["point"].Add("yPos", 10);

	std::string str = object.ToString();
	str = object.ToFormattedString();

#endif

	initCtrl();
	initMediaResource();
	initSignalResource();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScreenShareRemoteAssistantDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScreenShareRemoteAssistantDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScreenShareRemoteAssistantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CScreenShareRemoteAssistantDlg::initCtrl()
{
	std::string strChannelName = CAgoraConfig::getInstance()->getChannelName();
	m_editChannelName.SetWindowTextW(CAgoraWrapperUtilc::s2cs(strChannelName));

	std::string strLoginUID = CAgoraConfig::getInstance()->getLoginUID();
	m_uLocalUID = CAgoraWrapperUtilc::str2int(strLoginUID);
	m_editUID.SetWindowTextW(CAgoraWrapperUtilc::s2cs(strLoginUID));

	m_pAgoraConfig = CAgoraConfig::getInstance();
	m_btnRemoteAssistant.EnableWindow(FALSE);

	m_checkMedia.EnableWindow(FALSE);
	m_checkSignal.EnableWindow(FALSE);
}

void CScreenShareRemoteAssistantDlg::initMediaResource()
{
	m_pAgoraMediaWrapper = CAgoraMediaWrapper::getInstance();
	m_pAgoraMediaWrapper->getEngineEventHandle()->SetMsgReceiver(m_hWnd);
}

void CScreenShareRemoteAssistantDlg::initSignalResource()
{
	m_pSignalWrapper = CAgoraSignalWrapper::getInstance();
	m_pSignalWrapper->setCallBackWnd(m_hWnd);
}

void CScreenShareRemoteAssistantDlg::uninitResource()
{

}

void CScreenShareRemoteAssistantDlg::OnBnClickedButtonJoin()
{
	// TODO: Add your control notification handler code here
	m_pAgoraMediaWrapper->EnableSDKVideoCapture(FALSE);
	m_pAgoraMediaWrapper->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	UINT uid = CAgoraWrapperUtilc::str2int(m_pAgoraConfig->getLoginUID());
	//m_pAgoraMediaWrapper->setLocalVideo(m_hWnd,uid);

	m_pAgoraMediaWrapper->enableVideo(TRUE);
	m_pAgoraMediaWrapper->enableAudio(TRUE);

	//m_pAgoraMediaWrapper->muteAllRemoteAudioStreams(TRUE);
	//m_pAgoraMediaWrapper->muteAllRemoteVideoStreams(TRUE);

	m_pAgoraMediaWrapper->setVideoProfile(VIDEO_PROFILE_TYPE::VIDEO_PROFILE_480P_10, FALSE);
	m_pAgoraMediaWrapper->setClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER, NULL);

	m_pAgoraMediaWrapper->getRtcEngine()->startPreview();

	std::string strChannelName = m_pAgoraConfig->getChannelName();
	m_pAgoraMediaWrapper->JoinChannel(NULL, strChannelName.data(), NULL, uid);

	HWND hMarkWnd = ::GetDesktopWindow();
	m_pAgoraMediaWrapper->EnableScreenCapture(hMarkWnd);

	//Signal
	m_pSignalWrapper->setChannelKey("_no_need_token");
	std::string strAccount = CAgoraConfig::getInstance()->getLoginUID();
	m_pSignalWrapper->Login(strAccount);
}

void CScreenShareRemoteAssistantDlg::OnBnClickedButtonLeave()
{
	// TODO: Add your control notification handler code here

	if (m_pAgoraMediaWrapper) {

		m_pAgoraMediaWrapper->leaveChannel();
		m_pAgoraMediaWrapper->getRtcEngine()->stopPreview();
		UINT uid = CAgoraWrapperUtilc::str2int(m_pAgoraConfig->getLoginUID());
		m_pAgoraMediaWrapper->setLocalVideo(NULL, uid);
		m_pAgoraMediaWrapper->EnableScreenCapture(NULL, 15, NULL, FALSE);
	}

	if (m_pSignalWrapper) {

		m_pSignalWrapper->LeaveChannel();
		m_pSignalWrapper->LogOut();
	}
}


void CScreenShareRemoteAssistantDlg::OnBnClickedButtonRemoteAssistant()
{
	// TODO: Add your control notification handler code here

	CString strSelectText;
	int nCurSel = m_ltMediaUserList.GetCurSel();
	m_ltMediaUserList.GetText(nCurSel, strSelectText);
	UINT uRemoteID = CAgoraWrapperUtilc::str2int(CAgoraWrapperUtilc::cs2s(strSelectText));
	if (uRemoteID == uSelectUID)
		AfxMessageBox(L"Already Remote Assisting .please Switch Remote User..");

	if (0 != uRemoteID)
		m_btnRemoteAssistant.EnableWindow(TRUE);

	for (std::map<UINT, BOOL>::iterator it = m_mapRemoteUserStatus.begin(); m_mapRemoteUserStatus.end() != it; it++) {

		if (it->first == uRemoteID) {
			m_pAgoraMediaWrapper->muteRemoteAudioStream(it->first, false);
			m_pAgoraMediaWrapper->muteRemoteVideoStream(it->first, false);
		}
		else {
			UINT uID = it->first;
			m_pAgoraMediaWrapper->muteRemoteAudioStream(uID, true);
			m_pAgoraMediaWrapper->muteRemoteVideoStream(uID, true);
		}
	}

	uSelectUID = uRemoteID;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_JOINCHANNEL_SUCCESS lpData = (LPAGE_JOINCHANNEL_SUCCESS)wParam;
	if (lpData) {

		m_checkMedia.SetCheck(TRUE);
		delete lpData; lpData = nullptr;

	}

	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDReJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDLeaveChannel(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LEAVE_CHANNEL lpData = (LPAGE_LEAVE_CHANNEL)wParam;
	if (lpData) {

		m_checkMedia.SetCheck(FALSE);
		m_ltMediaUserList.ResetContent();
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDFirstLocalFrame(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDFirstRemoteFrameDecoded(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_REMOTE_VIDEO_DECODED lpData = (LPAGE_FIRST_REMOTE_VIDEO_DECODED)wParam;
	if (lpData) {

		if (NULL == m_pScreenShareRemoteDlg) {

			CRemoteAssistantDlg DlgRemoteAssistant(lpData->uid);
			DlgRemoteAssistant.setRemoteScreenSolution(lpData->width, lpData->height);
			m_pScreenShareRemoteDlg = &DlgRemoteAssistant;
			INT_PTR nResponse = DlgRemoteAssistant.DoModal();
			if (IDOK == nResponse) {

			}
			else if (IDCANCEL == nResponse) {
				//Notify MainWnd RemoteAssistant Finished..
				m_btnRemoteAssistant.EnableWindow(FALSE);
				m_pAgoraMediaWrapper->setRemoteVideo(NULL, uSelectUID);
				m_pAgoraMediaWrapper->muteRemoteAudioStream(uSelectUID, true);
				m_pAgoraMediaWrapper->muteRemoteVideoStream(uSelectUID, true);
				uSelectUID = 0;
			}
		}

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDUserJoined(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_JOINED lpData = (LPAGE_USER_JOINED)wParam;
	if (lpData) {

		CString strRemoteID = CAgoraWrapperUtilc::s2cs(CAgoraWrapperUtilc::int2str(lpData->uid));
		if (CB_ERR == m_ltMediaUserList.FindStringExact(0, strRemoteID)) {

			m_ltMediaUserList.AddString(strRemoteID);

			if (m_pAgoraMediaWrapper) {
				m_pAgoraMediaWrapper->muteRemoteVideoStream(lpData->uid, true);
				m_pAgoraMediaWrapper->muteRemoteAudioStream(lpData->uid, true);

				m_mapRemoteUserStatus[lpData->uid] = FALSE;
			}
		}

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDUserOffline(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_OFFLINE lpData = (LPAGE_USER_OFFLINE)wParam;
	if (lpData) {

		CString strRemoteID = CAgoraWrapperUtilc::s2cs(CAgoraWrapperUtilc::int2str(lpData->uid));
		int nIndex = 0;
		if (CB_ERR != (nIndex = m_ltMediaUserList.FindStringExact(0, strRemoteID))) {
			m_ltMediaUserList.DeleteString(nIndex);

			if (m_pScreenShareRemoteDlg && FALSE)
				::PostMessage(m_pScreenShareRemoteDlg->m_hWnd, WM_DESTROY, 0, 0);
		}
	}

	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDMuteVideo(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_MUTE_AUDIO lpData = (LPAGE_USER_MUTE_AUDIO)wParam;
	if (lpData) {

		if (lpData->muted && lpData->uid == uSelectUID) {
			m_btnRemoteAssistant.EnableWindow(TRUE);
		}
	}

	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDMuteAudio(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T(__FUNCTION__));
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDConnectionLost(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T(__FUNCTION__));
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnEIDVideoDeviceChanged(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnRemoteVideoStat(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnStartRecordingService(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnStopRecordingService(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::OnApiCallExecuted(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}


void CScreenShareRemoteAssistantDlg::OnLbnDblclkListUserlist()
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_ltMediaUserList.GetCurSel();
	if (CB_ERR != nCurSel)
		m_btnRemoteAssistant.EnableWindow(TRUE);
	else
		m_btnRemoteAssistant.EnableWindow(FALSE);
}

//////////////////////////////////////////////////////////////////////////
HRESULT CScreenShareRemoteAssistantDlg::onLoginSuccess(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGINSUCCESS lpData = (PAG_SIGNAL_LOGINSUCCESS)wParam;
	if (lpData) {
		m_checkSignal.SetCheck(TRUE);

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onLogout(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGOUT lpData = (PAG_SIGNAL_LOGOUT)wParam;
	if (lpData) {

		m_checkSignal.SetCheck(FALSE);
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onLogFailed(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGINFAILED lpData = (PAG_SIGNAL_LOGINFAILED)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::onError(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOIN lpData = (PAG_SIGNAL_CHANNELJOIN)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

LRESULT CScreenShareRemoteAssistantDlg::onLog(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOG lpData = (PAG_SIGNAL_LOG)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onQueryUserStatusResult(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_QUERYUSERSTATUSRESULT lpData = (PAG_SIGNAL_QUERYUSERSTATUSRESULT)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onMessageSendSuccess(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGESENDSUCCESS lpData = (PAG_SIGNAL_MESSAGESENDSUCCESS)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onMessageSendError(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGESENDERROR lpData = (PAG_SIGNAL_MESSAGESENDERROR)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onMessageInstantReceive(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGEINSTANCERECEIVE lpData = (PAG_SIGNAL_MESSAGEINSTANCERECEIVE)wParam;
	if (lpData) {
		CString strFormat;
		strFormat.Format(L"[%s] : %s", CAgoraWrapperUtilc::s2cs(lpData->msg), CAgoraWrapperUtilc::s2cs(lpData->msg));
		m_ltSignalMsgInfo.AddString(strFormat);

		parseMsg(lpData->msg);

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onMessageChannelReceive(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGECHANNELRECEIVE lpData = (PAG_SIGNAL_MESSAGECHANNELRECEIVE)wParam;
	if (lpData) {

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onChannelJoined(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOIN lpData = (PAG_SIGNAL_CHANNELJOIN)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onChannelJoinFailed(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOINFAILED lpData = (PAG_SIGNAL_CHANNELJOINFAILED)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

HRESULT CScreenShareRemoteAssistantDlg::onChannelLeaved(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELLEAVE lpData = (PAG_SIGNAL_CHANNELLEAVE)wParam;
	if (lpData) {
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}


void CScreenShareRemoteAssistantDlg::parseMsg(const std::string &msg)
{
	CJsonObject jsonObject(msg);

	UINT uCmdType;
	if (jsonObject.Get(CMDTYPE, uCmdType)) {
		int uTimeStamp = 0;
		jsonObject.Get(TIMESTAMP, uTimeStamp);

		SYSTEMTIME st;
		GetSystemTime(&st);
		int lTimeStamp = (st.wHour * 3600 + st.wMinute * 60 + st.wSecond) * 1000 + st.wMilliseconds;
		uTimeStamp = lTimeStamp - uTimeStamp;
		TRACE("Interval : %d ms\n", uTimeStamp);

		static CPoint pt;
		if (eTransfer_Mouse_Move == uCmdType) {
			int nXpos = 0;
			int nYpos = 0;
			if (jsonObject[EVENTPARAM][POSITION].Get("x", nXpos) &&
				jsonObject[EVENTPARAM][POSITION].Get("y", nYpos)) {
				pt.x = nXpos;
				pt.y = nYpos;
			}
		}

		switch (uCmdType) {
		case eTransfer_StartAssistant:{
			notifyStart();
		}
									  break;
		case eTransfer_StopAssistant:
			notifyStop();
			break;
		case eTransfer_Mouse_LBtnDown:{
			notifyLbtnDown(pt);
		}
									  break;
		case eTransfer_Mouse_LBtnUp:{
			notifyLbtnUp(pt);
		}
									break;
		case eTransfer_Mouse_LBtnDClick:{
			notifyLbtnDClick(pt);
		}
										break;
		case eTransfer_Mouse_RBtnDown:{
			notifyRbtnDown(pt);
		}
									  break;
		case eTransfer_Mouse_RBtnUp:{
			notifyRbtnUp(pt);
		}
									break;
		case eTransfer_Mouse_RBtnDClick:{
			notifyRbtnDClick(pt);
		}
										break;
		case eTransfer_Mouse_Move:{
			notifyMove(pt);
		}
								  break;
		case eTransfer_Mouse_Wheel:{
			WPARAM wParam;
			UINT fwkeys;
			int zDelta;
			jsonObject[EVENTPARAM][SCROLDELTA].Get("x", fwkeys);
			jsonObject[EVENTPARAM][SCROLDELTA].Get("y", zDelta);
			wParam = MAKEWPARAM(fwkeys, zDelta);
			jsonObject[EVENTPARAM].Get("wParam", wParam);
			notifyWheel(wParam, pt);
		}
								   break;
		case eTransfer_KeyBoard_KeyDown: {
			int nVkCode = 0;
			jsonObject[EVENTPARAM].Get(VKEYCODE, nVkCode);
			UINT nVkSrcCode = getSrcChar(nVkCode);
			notifyKeyDown(nVkSrcCode);
		}
										 break;
		case eTransfer_KeyBoard_KeyUp: {
			int nVkCode = 0;
			jsonObject[EVENTPARAM].Get(VKEYCODE, nVkCode);
			UINT nVkSrcCode = getSrcChar(nVkCode);
			notifyKeyUp(nVkSrcCode);
		}
									   break;
		case eTransfer_KeyBoard_KeyPress:{
			int nNum;
			WPARAM wParam;
			jsonObject["EventParam"].Get("input", nNum);
			jsonObject["EventParam"].Get("wParam", wParam);
			notifyChar(wParam, (char)nNum);
		}
										 break;
		case eTransfer_KeyBoard_Copy:{
			std::string strMsg;
			jsonObject["EventParam"].Get("copyContent", strMsg);
			notifyCopy(strMsg);
		}
									 break;
		case eTransfer_KeyBoard_Paste:{
			std::string strMsg;
			jsonObject["EventParam"].Get("pasteContent", strMsg);
			notifyPaste(strMsg);
		}
									  break;
		}
	}
}

void CScreenShareRemoteAssistantDlg::notifyLbtnDown(POINT &pt)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	mouse_event(MOUSEEVENTF_LEFTDOWN, pt.x, pt.y, 0, 0);
}

void CScreenShareRemoteAssistantDlg::notifyLbtnUp(POINT &pt)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	mouse_event(MOUSEEVENTF_LEFTUP, pt.x, pt.y, 0, 0);
}

void CScreenShareRemoteAssistantDlg::notifyLbtnDClick(POINT &pt)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, pt.x, pt.y, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, pt.x, pt.y, 0, 0);
}

void CScreenShareRemoteAssistantDlg::notifyRbtnDown(POINT &pt)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	mouse_event(MOUSEEVENTF_RIGHTDOWN, pt.x, pt.y, 0, 0);
}

void CScreenShareRemoteAssistantDlg::notifyRbtnUp(POINT &pt)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	mouse_event(MOUSEEVENTF_RIGHTUP, pt.x, pt.y, 0, 0);
}


void CScreenShareRemoteAssistantDlg::notifyRbtnDClick(POINT &pt)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, pt.x, pt.y, 0, 0);
	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, pt.x, pt.y, 0, 0);
}

void CScreenShareRemoteAssistantDlg::notifyMove(POINT &pt)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;

#if 0
	POSITION	pos = m_listWnd.GetHeadPosition();
	CRect		rcMarkWnd;
	HWND		hMarkWnd = NULL;
	HWND		hFound = NULL;

	while (pos != NULL) {
		hFound = m_listWnd.GetNext(pos);
		::GetWindowRect(hFound, &rcMarkWnd);
		if (rcMarkWnd.PtInRect(rt)) {
			hMarkWnd = hFound;
			break;
		}
	}

	if (hMarkWnd != m_hMarkWnd) {
		m_hMarkWnd = hMarkWnd;
		Invalidate();
	}
#endif
	//::PostMessage(m_hMarkWnd, WM_NCHITTEST, NULL, MAKELPARAM(rt.x, rt.y));
	//::PostMessage(m_hMarkWnd, WM_SETCURSOR, WPARAM(m_hMarkWnd), MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));
	//::PostMessage(m_hMarkWnd, WM_MOUSEMOVE, NULL, MAKELPARAM(rt.x, rt.y));
	//mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, pt.x, pt.y, 0, 0);
	SetCursorPos(pt.x, pt.y);
}

void CScreenShareRemoteAssistantDlg::notifyChar(WPARAM wParam, char ch)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));

	UINT uFlage = DWORD(LOWORD(wParam));
	if (uFlage) {
		UINT uVCode = DWORD(HIWORD(wParam));
		keybd_event(uVCode, 0, 0, 0);
		keybd_event(ch, 0, 0, 0);
		keybd_event(ch, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(uVCode, 0, KEYEVENTF_KEYUP, 0);
	}
	else {
		keybd_event(ch, 0, 0, 0);
		keybd_event(ch, 0, KEYEVENTF_KEYUP, 0);
	}
}

void CScreenShareRemoteAssistantDlg::notifyKeyDown(int nVkCode)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));
	keybd_event(nVkCode, 0, 0, 0);
}

void CScreenShareRemoteAssistantDlg::notifyKeyUp(int nVkCode)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));
	keybd_event(nVkCode, 0, KEYEVENTF_KEYUP, 0);
}

void CScreenShareRemoteAssistantDlg::notifyCopy(const std::string &msg)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
}

void CScreenShareRemoteAssistantDlg::notifyPaste(const std::string &msg)
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
}

void CScreenShareRemoteAssistantDlg::notifyStart()
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	m_listWnd.RemoveAll();
	::EnumWindows(&CScreenShareRemoteAssistantDlg::WndEnumProc, (LPARAM)&m_listWnd);
}

void CScreenShareRemoteAssistantDlg::notifyStop()
{
	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
}

void CScreenShareRemoteAssistantDlg::notifyWheel(WPARAM wParam, POINT &pt)
{
	UINT fwkeys = GET_KEYSTATE_WPARAM(wParam);
	short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

	OutputDebugString(_T(__FUNCTION__));	OutputDebugString(_T("\n"));;
	mouse_event(MOUSEEVENTF_WHEEL, pt.x, pt.y, zDelta, 0);
}

BOOL CALLBACK CScreenShareRemoteAssistantDlg::WndEnumProc(HWND hWnd, LPARAM lParam)
{
	CList<HWND> *lpListctrl = (CList<HWND> *)lParam;

	LONG lStyle = ::GetWindowLong(hWnd, GWL_STYLE);

	if ((lStyle&WS_VISIBLE) != 0 && (lStyle&(WS_POPUP | WS_SYSMENU)) != 0)
		lpListctrl->AddTail(hWnd);

	return TRUE;
}
