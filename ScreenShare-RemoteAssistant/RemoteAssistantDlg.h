#pragma once


// CRemoteAssistantDlg dialog
class CAgoraMediaWrapper;
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

	DECLARE_MESSAGE_MAP()

private:

	int m_nScreenW;
	int m_nScreenH;
	UINT m_uRemoteID;

	CAgoraMediaWrapper *m_pMediaWrapper;
};
