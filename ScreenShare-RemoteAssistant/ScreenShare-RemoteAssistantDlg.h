
// ScreenShare-RemoteAssistantDlg.h : header file
//

#pragma once


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

public:
	afx_msg void OnBnClickedButtonJoin();
	afx_msg void OnBnClickedButtonLeave();
	afx_msg void OnBnClickedButtonRemoteAssistant();
};
