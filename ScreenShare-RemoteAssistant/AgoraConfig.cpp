#include "stdafx.h"
#include "AgoraConfig.h"

CSingleton<CAgoraConfig>::CGrabo CAgoraConfig::graboConfig;

CAgoraConfig::CAgoraConfig() :CIniBase("")
{
	std::string path = CAgoraWrapperUtilc::getAbsoluteDir() + "RemoteAssistant.ini";
	pIniInstance_->openFile(path);
}

CAgoraConfig::CAgoraConfig(const std::string &path):
CIniBase("")
{

}

CAgoraConfig::~CAgoraConfig()
{

}

__IMPLEMENT_INICONFIG_FUN(CAgoraConfig, AppId, INI_BASEINFO, INI_BASEINFO_APPID)
__IMPLEMENT_INICONFIG_FUN(CAgoraConfig, AppCertEnable, INI_BASEINFO, INI_BASEINFO_AppCertEnable)
__IMPLEMENT_INICONFIG_FUN(CAgoraConfig, AppCertificateId, INI_BASEINFO, INI_BASEINFO_APPCertificateID)
__IMPLEMENT_INICONFIG_FUN(CAgoraConfig, ChannelName, INI_BASEINFO, INI_BASEINFO_ChannelName)
__IMPLEMENT_INICONFIG_FUN(CAgoraConfig, LoginUID, INI_BASEINFO, INI_BASEINFO_UID)