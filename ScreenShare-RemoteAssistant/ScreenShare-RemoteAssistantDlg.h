
// ScreenShare-RemoteAssistantDlg.h : header file
//

#pragma once


class CAgoraConfig;
class CAgoraMediaWrapper;
// CScreenShareRemoteAssistantDlg dialog
class CScreenShareRemoteAssistantDlg : public CDialogEx
{
// Construction
public:
	CScreenShareRemoteAssistantDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCREENSHAREREMOTEASSISTANT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDReJoinChannelSuccess(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDFirstLocalFrame(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDFirstRemoteFrameDecoded(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserJoined(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserOffline(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDConnectionLost(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDVideoDeviceChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRemoteVideoStat(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnStartRecordingService(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStopRecordingService(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnApiCallExecuted(WPARAM wParam, LPARAM lParam);

protected:

	void initCtrl();
	void initMediaResource();
	void initSignalResource();
	void uninitResource();

private:

	CEdit m_editChannelName;
	CEdit m_editUID;
	
	CButton m_btnJoin;
	CButton m_btnLeave;
	CButton m_btnRemoteAssistant;
	CListBox m_ltUserList;

	CAgoraConfig* m_pAgoraConfig;
	CAgoraMediaWrapper* m_pAgoraMediaWrapper;

	HWND m_hScreenWnd;
	std::map<UINT, BOOL> m_mapRemoteUserStatus;

public:
	afx_msg void OnBnClickedButtonJoin();
	afx_msg void OnBnClickedButtonLeave();
	afx_msg void OnBnClickedButtonRemoteAssistant();
};
