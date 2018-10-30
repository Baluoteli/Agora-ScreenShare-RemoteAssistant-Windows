#pragma once


// CRemoteAssistantDlg dialog
class CAgoraMediaWrapper;
class CAgoraSignalWrapper;
#include "RemoteAssistantTransfer.h"
using namespace AgoraRemoteTransfer;

class CRemoteAssistantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRemoteAssistantDlg)

public:
	CRemoteAssistantDlg(UINT uID, CWnd* pParent = NULL);   // standard constructor
	virtual ~CRemoteAssistantDlg();

	void setRemoteScreenSolution(int nWidth,int nHeight);

// Dialog Data
	enum { IDD = IDD_DIALOG_REMOTEASSISTANT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnPaint();
	void OnClose();

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
	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

protected:
	void initCtrl();
	void initSignalResource();
	void uninitResource();

	void convertResolution();
	void geneRemotePos(CPoint &ptSrc);

private:

	int m_nScreenW;
	int m_nScreenH;
	UINT m_uRemoteID;
	CPen m_penFrame;

	std::string m_strAccount;
	std::string m_strAppId;

	int m_nRemoteScreenX;
	int m_nRemoteScreenY;

	double m_nSpaceW;
	double m_nSpaceH;

	CAgoraMediaWrapper *m_pMediaWrapper;
	CAgoraRemoteTransfer m_AgoraRemoteTransfer;
};
