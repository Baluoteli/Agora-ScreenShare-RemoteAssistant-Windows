#pragma once


// CRemoteAssistantDlg dialog
class CAgoraMediaWrapper;
class CAgoraSignalWrapper;
class CRemoteAssistantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRemoteAssistantDlg)

public:
	CRemoteAssistantDlg(UINT uID, CWnd* pParent = NULL);   // standard constructor
	virtual ~CRemoteAssistantDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_REMOTEASSISTANT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnPaint();

	DECLARE_MESSAGE_MAP()

	
	afx_msg HRESULT onLoginSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onLogout(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onLogFailed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onLog(WPARAM wParam, LPARAM lParam);
	
	afx_msg HRESULT onQueryUserStatusResult(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onMessageSendSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onMessageSendError(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onMessageInstantReceive(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onMessageChannelReceive(WPARAM wParam, LPARAM lParam);
	
	afx_msg HRESULT onChannelJoined(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onChannelJoinFailed(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT onChannelLeaved(WPARAM wParam, LPARAM lParam);
	

protected:
	void initCtrl();
	void initSignalResource();
	void uninitResource();

private:

	int m_nScreenW;
	int m_nScreenH;
	UINT m_uRemoteID;
	CPen m_penFrame;

	std::string m_strAccount;
	std::string m_strAppId;

	CAgoraMediaWrapper *m_pMediaWrapper;
	CAgoraSignalWrapper *m_pSignalWrapper;
};
