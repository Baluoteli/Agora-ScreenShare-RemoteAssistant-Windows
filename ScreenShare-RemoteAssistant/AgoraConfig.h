#ifndef __AGORACONFIG_H__
#define __AGORACONFIG_H__

#define INI_BASEINFO													"BaseInfo"
#define INI_BASEINFO_APPID									    "AppId"
#define INI_BASEINFO_AppCertEnable							"AppCertEnable"
#define INI_BASEINFO_APPCertificateID							"AppCertificateId"
#define INI_BASEINFO_ChannelName								"ChannelName"
#define INI_BASEINFO_UID											"LoginUID"

class CAgoraConfig :public CIniBase, public CSingleton<CAgoraConfig>
{
public:
	friend CSingleton;
	~CAgoraConfig();

	__DECLARE_INICONFIG_FUN(AppId)
	__DECLARE_INICONFIG_FUN(AppCertEnable)
	__DECLARE_INICONFIG_FUN(AppCertificateId)
	__DECLARE_INICONFIG_FUN(ChannelName)
	__DECLARE_INICONFIG_FUN(LoginUID)

private:
	CAgoraConfig();
	CAgoraConfig(const std::string &path);
	static CSingleton<CAgoraConfig>::CGrabo graboConfig;
};

#endif