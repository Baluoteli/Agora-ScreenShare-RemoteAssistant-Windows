#ifndef __AGORASIGNALWRAPPER_H__
#define __AGORASIGNALWRAPPER_H__

class CAGSignalCallBack;
class CAgoraSignalWrapper :public CSingleton<CAgoraSignalWrapper>
{
public:
	friend CSingleton;
	~CAgoraSignalWrapper();

	void setCallBackWnd(HWND wnd);
	IAgoraAPI* getAgoraAPI();

	void setChannelKey(const std::string &channelKey);
	std::string getChannelKey();

	bool Login(const std::string &account);
	bool LogOut();

	bool QueryIsOnline(const std::string &account);
	bool sendInstantMsg(const std::string &account, const std::string &instanmsg);
	bool sendChannelMsg(const std::string &channel, const std::string &ChannelMsg);

	bool JoinChannel(const std::string &channelID);
	bool LeaveChannel();

	std::string getSDKVersion();

protected:

	inline void initSignalEngine();
	inline void uninitSignalEngine();

private:
	CAgoraSignalWrapper();
	static CSingleton<CAgoraSignalWrapper>::CGrabo graboSignalWrapper;

	bool m_bLoginPt;
	bool m_bJoinChannel;

	std::string m_Account;
	std::string m_ChannelName;
	std::string m_AppId;
	std::string m_AppCertificateId;
	std::string m_channelKey;

	IAgoraAPI* m_AgoraAPI;
	HWND m_hCallBack;

	CAGSignalCallBack* m_pSignalCallBack;
};

#endif