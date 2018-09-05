#ifndef __SIGNALDEF_H__
#define __SIGNALDEF_H__

namespace AgoraSignleParamDef
{
	enum SingleMsg
	{
		WM_Default = WM_MSGID(EID_SCREENSHARE_CLOSE),
		WM_Reconnecting,
		WM_Reconnected,
		WM_LoginSuccess,
		WM_LogOut,
		WM_LoginFailed,
		WM_ChannelJoined,
		WM_ChannelJoinedFailed,
		WM_ChannelLeaved,
		WM_ChannelUserJoined,
		WM_ChannelUserLeaved,
		WM_ChannelUserList,
		WM_ChannelQueryUserNumResult,
		WM_ChannelQueryUserIsIn,
		WM_ChannelAttrUpdated,
		WM_InviteReceived,
		WM_InviteReceivedByPeer,
		WM_InviteAcceptedByPeer,
		WM_InviteRefusedByPeer,
		WM_InviteFailed,
		WM_InviteEndByPeer,
		WM_InviteEndByMyself,
		WM_InviteMsg,
		WM_MessageSendError,
		WM_MessageSendProgress,
		WM_MessageSendSuccess,
		WM_MessageAppReceived,
		WM_MessageInstantReceive,
		WM_MessageChannelReceive,
		WM_Log,
		WM_InvokeRet,
		WM_Msg,
		WM_UserAttrResult,
		WM_UserAttrAllResult,
		WM_Error,
		WM_QueryUserStatusResult,
		WM_Dbg,
		WM_BCCall_result,

		WM_UNKWOWN = WM_USER + 0xff
	};

	enum eTagMsgtype
	{
		eType_Instance,
		eType_Channel,
	};

	typedef struct InPutParam
	{
		eTagMsgtype type;
		std::string strParam;
	}AG_INPUTPARAM, *PAG_INPUTPARAM, *LPAG_INPUTPARAM;

	typedef struct AGTagNewChannelName
	{
		std::string account;
		std::string channelname;
	}AG_SIGNAL_NEWCHANNELNAME, *PAG_SIGNAL_NEWCHANNELNAME, *LPAG_SIGNAL_NEWCHANNELNAME;

	typedef struct AGTagInviteRemoteAudience
	{
		std::string remoteAccount;
		bool enableVideo;
		bool enableAudio;
		int nTimeOut;
		bool isAccpet;
		bool isValid;
	}AG_INVITE_REMOTEAUDIENCE, *PAG_INVITE_REMOTEAUDIENCE, *LPAG_INVITE_REMOTEAUDEINCE;

	typedef struct AGTagInviteCallBackAccpet
	{
		std::string remoteMediaUid;
		std::string remoteSigAccount;
		bool isAccept;

	}AG_INVITE_CALLBACKACCEPT, *PAG_INVITE_CALLBACKACCEPT, *LPAG_INVITE_CALLBACKACCEPT;

	typedef struct AGTagSetDataTimeBonus
	{
		int nRoundId;
		std::string strDataTime;
		int nBonus;
	}AG_SetDataTimeBonus, *PAG_SetDataTimeBonus, *LPAG_SetDataTimeBonus;

#define 	WM_InviteReceived_ChannelName  (WM_BCCall_result + 1)
#define WM_UpdateInputParam (WM_BCCall_result + 2)
#define WM_NewChannelName (WM_BCCall_result + 3)
#define 	WM_InviteRemoteAudience (WM_BCCall_result + 4)
#define WM_InviteCallBackAccpet (WM_BCCall_result + 5)
#define WM_SetDataTimeBonus (WM_BCCall_result + 6)

	typedef struct AGTagStructReconnecting
	{
		uint32_t nretry;
	}AG_SIGNAL_RECONNECTING, *PAG_SIGNAL_RECONNECTING, *LPAG_SIGNAL_RECONECTING;

	typedef struct AGTagReconnected
	{
		int fd;
	}AG_SIGNAL_RECONNECTED, *PAG_SIGNAL_RECONNECTED, *LPAG_SIGNAL_RECONNECTED;

	typedef struct AGTagLoginSuccess
	{
		uint32_t uid;
		int fd;
	}AG_SIGNAL_LOGINSUCCESS, *PAG_SIGNAL_LOGINSUCCESS, *LPAG_SIGNAL_LOGINSUCCESS;

	typedef struct AGTagLogout
	{
		int ecode;
	}AG_SIGNAL_LOGOUT, *PAG_SIGNAL_LOGOUT, *LPAG_SIGNAL_LOGOUT;

	typedef struct AGTagLoginFailed
	{
		int ecode;
	}AG_SIGNAL_LOGINFAILED, *PAG_SIGNAL_LOGINFAILED, *LPAG_SIGNAL_LOGINFAILED;

	typedef struct AGTagChannelJoin
	{
		std::string channelID;
	}AG_SIGNAL_CHANNELJOIN, *PAG_SIGNAL_CHANNELJOIN, *LPAG_SIGNAL_CHANNELJOIN;

	typedef struct AGTagChannelJoinFailed
	{
		std::string channelID;
		int ecode;
	}AG_SIGNAL_CHANNELJOINFAILED, *PAG_SIGNAL_CHANNELJOINFAILED, *LPAG_SIGNAL_CHANNELJOINFAILED;

	typedef struct AGTagChannelLeave
	{
		std::string channelID;
		int ecode;
	}AG_SIGNAL_CHANNELLEAVE, *PAG_SIGNAL_CHANNELLEAVE, *LPAG_SIGNAL_CHANNELLEAVE;

	typedef struct  AGTagChannelUserJoin
	{
		std::string account;
		uint32_t uid;
	}AG_SIGNAL_CHANNELUSERJOIN, *PAG_SIGNAL_CHANNELUSERJOIN, *LPAG_SIGNAL_CHANNELUSERJOIN;

	typedef struct AGTagChannelUserLeave
	{
		std::string account;
		uint32_t uid;
	}AG_SIGNAL_CHANNELUSERLEAVE, *PAG_SIGNAL_CHANNELUSERLEAVE, *LPAG_SIGNAL_CHANNELUSERLEAVE;

	typedef struct AGTagChannelUserList
	{
		int nUserNum;
		char** ppAccount;
		uint32_t uids;
	}AG_SIGNAL_CHANNELUSERLIST, *PAG_SIGNAL_CHANNELUSERLIST, *LPAG_SIGNAL_CHANNELUSERLIST;

	typedef struct AGTagChannelQueryUserNumResult
	{
		std::string channelID;
		int ecode;
		int num;
	}AG_SIGNAL_CHNNELQUERYUSERNUMRESULT, *PAG_SIGNAL_CHNNELQUERYUSERNUMRESULT, *LPAG_SIGNAL_CHNNELQUERYUSERNUMRESULT;

	typedef struct AGTagChannelQueryUserIsln
	{
		std::string channelID;
		std::string account;
		int isIn;
	}AG_SIGNAL_CHANNELQUERYUSERISIN, *PAG_SIGNAL_CHANNELQUERYUSERISIN, *LPAG_SIGNAL_CHANNELQUERYUSERISIN;

	typedef struct AGTagChannelAttrUpdated
	{
		std::string channelD;
		std::string name;
		std::string value;
		std::string type;
	}AG_SIGNAL_CHANNELATTRUPDATED, *PAG_SIGNAL_CHANNELATTRUPDATED, *LPAG_SIGNAL_CHANNELATTRUPDATED;

	typedef struct AGTagInviteReceived
	{
		std::string channelID;
		std::string account;
		uint32_t uid;
		std::string extra;
	}AG_SIGNAL_INVITERECEIVED, *PAG_SIGNAL_INVITERECEIVED, *LPAG_SIGNAL_INVITERECEIVED;

	typedef struct AGTagInviteReceivedByPeer
	{
		std::string channelID;
		std::string account;
		uint32_t uid;
	}AG_SIGNAL_INVITERECEIVEDBYPEER, *PAG_SIGNAL_INVITERECEIVEDBYPEER, *LPAG_SIGNAL_INVITERECEIVEDBYPEER;

	typedef struct AGTagInviteAcceptedByPeer
	{
		std::string channelID;
		std::string account;
		int uid;
		std::string extra;
	}AG_SIGNAL_INVITEACCEPTEDBYPEER, *PAG_SIGNAL_INVITEACCEPTEDBYPEER, *LPAG_SIGNAL_INVITEACCEPTEDBYPEER;

	typedef struct AGTagInviteRefusedByPeer
	{
		std::string channelID;
		std::string account;
		uint32_t uid;
		std::string extra;
	}AG_SIGNAL_INVITEREFUSEDBYPEER, *PAG_SIGNAL_INVITEREFUSEDBYPEER, *LPAG_SIGNAL_INVITEREFUSEDBYPEER;

	typedef struct AGTagInviteFailed
	{
		std::string channelID;
		std::string account;
		uint32_t uid;
		int ecode;
		std::string extra;
	}AG_SIGNAL_INVITEFAILED, *PAG_SIGNAL_INVITEFAILED, *LPAG_SIGNAL_INVITEFAILED;

	typedef struct AGTagInviteEndByPeer
	{
		std::string channelID;
		std::string account;
		uint32_t uid;
		std::string extra;
	}AG_SIGNAL_INVITEENDBYPEER, *PAG_SIGNAL_INVITEENDBYPEER, *LPAG_SIGNAL_INVITEENDBYPEER;

	typedef struct AGTagInviteEndByMyself
	{
		std::string channelID;
		std::string account;
		uint32_t uid;
	}AG_SIGNAL_INVITEENDBYMYSELF, *PAG_SIGNAL_INVITEENDBYMYSELF, *LPAG_SIGNAL_INVITEENDBYMYSELF;

	typedef struct AGTagInviteMsg
	{
		std::string channelID;
		std::string account;
		uint32_t uid;
		std::string msgType;
		std::string msgData;
		std::string extra;
	}AG_SIGNAL_INVIDEMSG, *PAG_SIGNAL_INVIDEMSG, *LPAG_SIGNAL_INVIDEMSG;

	typedef struct AGTagMessageSendError
	{
		std::string message;
		int ecode;
	}AG_SIGNAL_MESSAGESENDERROR, *PAG_SIGNAL_MESSAGESENDERROR, *LPAG_SIGNAL_MESSAGESENDERROR;

	typedef struct AGTagMessageSendProgress
	{
		std::string account;
		std::string messageID;
		std::string type;
		std::string info;
	}AG_SIGNAL_MESSAGESENDPROGRESS, *PAG_SIGNAL_MESSAGESENDPROGRESS, *LPAG_SIGNAL_MESSAGESENDPROGRESS;

	typedef struct AGTagMessageSendSuccess
	{
		std::string messageID;
	}AG_SIGNAL_MESSAGESENDSUCCESS, *PAG_SIGNAL_MESSAGESENDSUCCESS, *LPAG_SIGNAL_MESSAGESENDSUCCESS;

	typedef struct AGTagMessageInstantReceive
	{
		std::string account;
		uint32_t uid;
		std::string msg;
	}AG_SIGNAL_MESSAGEINSTANCERECEIVE, *PAG_SIGNAL_MESSAGEINSTANCERECEIVE, *LPAG_SIGNAL_MESSAGEINSTANCERECEIVE;

	typedef struct AGTagMessageChannelReceive
	{									
		std::string channelID;
		std::string account;
		uint32_t uid;
		std::string msg;
	}AG_SIGNAL_MESSAGECHANNELRECEIVE, *PAG_SIGNAL_MESSAGECHANNELRECEIVE, *LPAG_SIGNAL_MESSAGECHANNELRECEIVE;

	typedef struct AGTagLog
	{
		std::string txt;
	}AG_SIGNAL_LOG, *PAG_SIGNAL_LOG, *LPAG_SIGNAL_LOG;

	typedef struct AGTagError
	{
		std::string name;
		int ecode;
		std::string desc;
	}AG_SIGNAL_ERROR, *PAG_SIGNAL_ERROR, *LPAG_SIGNAL_ERROR;

	typedef struct AGTagQueryUserStatusResult
	{
		std::string name;
		std::string status;
	}AG_SIGNAL_QUERYUSERSTATUSRESULT, *PAG_SIGNAL_QUERYUSERSTATUSRESULT, *LPAG_SIGNAL_QUERYUSERSTATUSRESULT;

}//AgoraSignleParamDef


#endif