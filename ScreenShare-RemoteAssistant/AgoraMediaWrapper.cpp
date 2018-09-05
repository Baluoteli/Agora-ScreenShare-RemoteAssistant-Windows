#include "stdafx.h"
#include "AgoraMediaWrapper.h"
#include "AgoraConfig.h"
#include "AGEngineEventHandler.h"

CSingleton<CAgoraMediaWrapper>::CGrabo CAgoraMediaWrapper::graboMediaWrapper;

CAgoraMediaWrapper::CAgoraMediaWrapper():
m_pAgEventHandle(nullptr),
m_lpAgoraEngine(nullptr),
m_sAppId(""),
m_uLoginUID(0),
m_sChannelName(""),
m_bScreenCapture(FALSE)
{
	m_sAppId = CAgoraConfig::getInstance()->getAppId();
	initMediaEngine(m_sAppId);
}

CAgoraMediaWrapper::~CAgoraMediaWrapper()
{
	uninitMediaEngine();
}

void CAgoraMediaWrapper::initMediaEngine(const std::string &appID)
{
	m_pAgEventHandle = new CAGEngineEventHandler;

	m_lpAgoraEngine = createAgoraRtcEngine();
	if (m_lpAgoraEngine){

		m_pAgEventHandle = new CAGEngineEventHandler;
		assert(m_pAgEventHandle);

		RtcEngineContext ctx;
		ctx.eventHandler = m_pAgEventHandle;
		ctx.appId = m_sAppId.data();
		m_lpAgoraEngine->initialize(ctx);
	}
}

void CAgoraMediaWrapper::uninitMediaEngine()
{
	m_lpAgoraEngine->release();
	m_lpAgoraEngine = nullptr;

	if (m_pAgEventHandle) {

		delete[] m_pAgEventHandle;
		m_pAgEventHandle = nullptr;
	}
}


const char* CAgoraMediaWrapper::getSDKVersion()
{
	int nBuildNumber = 0;
	const char *lpszEngineVer = getAgoraRtcEngineVersion(&nBuildNumber);

	char szbuf[MAX_PATH] = { '\0' };
	sprintf_s(szbuf, "%s %d", lpszEngineVer, nBuildNumber);

	return szbuf;
}

IRtcEngine* CAgoraMediaWrapper::getRtcEngine()
{
	return m_lpAgoraEngine;
}

CAGEngineEventHandler* CAgoraMediaWrapper::getEngineEventHandle()
{
	return m_pAgEventHandle;
}

int CAgoraMediaWrapper::JoinChannel(const char *channelKey, const char *channelName, const char *info, unsigned int uid)
{
	int nRet = 0;

	m_uLoginUID = uid;
	m_sChannelName = channelName;
	LPCSTR lpStreamInfo = "{\"owner\":true,\"width\":640,\"height\":480,\"bitrate\":500}";
	nRet = m_lpAgoraEngine->joinChannel(channelKey, channelName, lpStreamInfo, uid);

	return nRet;
}

int CAgoraMediaWrapper::leaveChannel()
{
	m_lpAgoraEngine->stopPreview();
	int nRet = m_lpAgoraEngine->leaveChannel();

	m_uLoginUID = 0;

	return nRet;
}

int CAgoraMediaWrapper::enableLastmileTest(BOOL bEnable /*= TRUE*/)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->enableLastmileTest();
	else
		nRet = m_lpAgoraEngine->enableLastmileTest();

	return nRet;
}

int CAgoraMediaWrapper::enableVideo(BOOL bEnable /*= TRUE*/)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->enableVideo();
	else
		nRet = m_lpAgoraEngine->disableVideo();

	return nRet;
}

int CAgoraMediaWrapper::enableLocalRender(BOOL bEnable)
{
	int nRet = 0;

	AParameter apm(*m_lpAgoraEngine);

	if (bEnable)
		nRet = apm->setParameters("{\"che.video.local.render\":true}");
	else
		nRet = apm->setParameters("{\"che.video.local.render\":false}");

	return nRet;
}

int CAgoraMediaWrapper::setLocalVideo(HWND hVideoWnd, UINT uid)
{
	VideoCanvas vc;
	vc.renderMode = RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
	vc.uid = uid;
	vc.view = hVideoWnd;

	return m_lpAgoraEngine->setupLocalVideo(vc);
}

int CAgoraMediaWrapper::setRemoteVideo(HWND hVideoWnd, UINT uid)
{
	VideoCanvas vc;
	vc.renderMode = RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
	vc.uid = uid;
	vc.view = hVideoWnd;

	return m_lpAgoraEngine->setupRemoteVideo(vc);
}

int CAgoraMediaWrapper::localVideoPreview(HWND hVideoWnd, BOOL bPreviewOn)
{
	int nRet = 0;

	if (bPreviewOn) {
		VideoCanvas vc;

		vc.uid = 0;
		vc.view = hVideoWnd;
		vc.renderMode = RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;

		m_lpAgoraEngine->setupLocalVideo(vc);
		nRet = m_lpAgoraEngine->startPreview();
	}
	else
		nRet = m_lpAgoraEngine->stopPreview();

	return nRet;
}

int CAgoraMediaWrapper::enableAudio(BOOL bEnable)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->enableAudio();
	else
		nRet = m_lpAgoraEngine->disableAudio();

	return nRet;
}

int CAgoraMediaWrapper::setParameters(const char* options)
{
	int nRet = 0;

	AParameter apm(*m_lpAgoraEngine);

	nRet = apm->setParameters(options);

	return nRet;
}

int CAgoraMediaWrapper::enableAudioVolumeIndication(int interval, int smooth)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.enableAudioVolumeIndication(interval, smooth);

	return nRet;
}

int CAgoraMediaWrapper::startAudioRecording(const char* filePath, int quality)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.startAudioRecording(filePath, (AUDIO_RECORDING_QUALITY_TYPE)quality);

	return nRet;
}

int CAgoraMediaWrapper::stopAudioRecording()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.stopAudioRecording();

	return nRet;
}

int CAgoraMediaWrapper::startAudioMixing(const char *filePath, int loopback, int replace, int cycle, int playTime)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.startAudioMixing(filePath, loopback, replace, cycle);

	return nRet;
}

int CAgoraMediaWrapper::stopAudioMixing()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.stopAudioMixing();

	return nRet;
}

int CAgoraMediaWrapper::pauseAudioMixing()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.pauseAudioMixing();

	return nRet;
}

int CAgoraMediaWrapper::resumeAudioMixing()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.resumeAudioMixing();

	return nRet;
}

int CAgoraMediaWrapper::adjustAudioMixingVolume(int volume)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.adjustAudioMixingVolume(volume);

	return nRet;
}

int CAgoraMediaWrapper::getAudioMixingDuration()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.getAudioMixingDuration();

	return nRet;
}

int CAgoraMediaWrapper::getAudioMixingCurrentPosition()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.getAudioMixingCurrentPosition();

	return nRet;
}

int CAgoraMediaWrapper::setAudioMixingPosition(int pos)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setAudioMixingPosition(pos);

	return nRet;
}

int CAgoraMediaWrapper::enableEchoTest(BOOL bEnable)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->startEchoTest();
	else
		nRet = m_lpAgoraEngine->stopEchoTest();

	return nRet;
}


int CAgoraMediaWrapper::muteLocalAudioStream(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteLocalAudioStream(muted);

	return nRet;
}

int CAgoraMediaWrapper::muteAllRemoteAudioStreams(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteAllRemoteAudioStreams(muted);

	return nRet;
}

int CAgoraMediaWrapper::muteRemoteAudioStream(int uid, int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteRemoteAudioStream(uid, muted);

	return nRet;
}

int CAgoraMediaWrapper::switchCamera()
{
	int nRet = 0;

	return nRet;
}

int CAgoraMediaWrapper::setVideoProfile(int profile, int swapWidthAndHeight)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setVideoProfile((VIDEO_PROFILE_TYPE)profile, swapWidthAndHeight);

	return nRet;
}

int CAgoraMediaWrapper::muteLocalVideoStream(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteLocalVideoStream(muted);

	return nRet;
}

int CAgoraMediaWrapper::muteAllRemoteVideoStreams(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteAllRemoteVideoStreams(muted);

	return nRet;
}

int CAgoraMediaWrapper::muteRemoteVideoStream(int uid, int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteRemoteVideoStream(uid, muted);

	return nRet;
}

int CAgoraMediaWrapper::setLogFile(const char *filePath)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setLogFile(filePath);

	return nRet;
}

int CAgoraMediaWrapper::setLogFilter(unsigned int filter)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setLogFilter(filter);

	return nRet;
}

int CAgoraMediaWrapper::renewChannelKey(const char *channelKey)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->renewChannelKey(channelKey);

	return nRet;
}

int CAgoraMediaWrapper::setChannelProfile(int profile)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setChannelProfile((CHANNEL_PROFILE_TYPE)profile);

	return nRet;
}

int CAgoraMediaWrapper::setClientRole(int role, const char *permissionKey)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setClientRole((CLIENT_ROLE_TYPE)role, permissionKey);

	return nRet;
}

int CAgoraMediaWrapper::enableDualStreamMode(int enabled)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.enableDualStreamMode(enabled);

	return nRet;
}

int CAgoraMediaWrapper::setEncryptionMode(const char *encryptionMode)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setEncryptionMode(encryptionMode);

	return nRet;
}

int CAgoraMediaWrapper::setEncryptionSecret(const char *secret)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setEncryptionSecret(secret);

	return nRet;
}

int CAgoraMediaWrapper::setRemoteVideoStreamType(int uid, int streamType)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setRemoteVideoStreamType(uid, (REMOTE_VIDEO_STREAM_TYPE)streamType);

	return nRet;
}

int CAgoraMediaWrapper::startRecordingService(const char *recordingKey)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.startRecordingService(recordingKey);

	return nRet;
}

int CAgoraMediaWrapper::stopRecordingService(const char *recordingKey)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.stopRecordingService(recordingKey);

	return nRet;
}

int CAgoraMediaWrapper::refreshRecordingServiceStatus()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.refreshRecordingServiceStatus();

	return nRet;
}

int CAgoraMediaWrapper::createDataStream(int reliable, int ordered)
{
	int nRet = 0;

	int nStreamID = 0;
	nRet = m_lpAgoraEngine->createDataStream(&nStreamID, reliable, ordered);

	return nRet;
}

int CAgoraMediaWrapper::sendStreamMessage(int streamId, const char *data)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->sendStreamMessage(streamId, data, strlen(data));

	return nRet;
}

int CAgoraMediaWrapper::setRecordingAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setRecordingAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);

	return nRet;
}

int CAgoraMediaWrapper::setPlaybackAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setPlaybackAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);

	return nRet;
}

int CAgoraMediaWrapper::setMixedAudioFrameParameters(int sampleRate, int samplesPerCall)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setMixedAudioFrameParameters(sampleRate, samplesPerCall);

	return nRet;
}

int CAgoraMediaWrapper::adjustRecordingSignalVolume(int volume)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.adjustRecordingSignalVolume(volume);

	return nRet;
}

int CAgoraMediaWrapper::adjustPlaybackSignalVolume(int volume)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.adjustPlaybackSignalVolume(volume);

	return nRet;
}

int CAgoraMediaWrapper::setHighQualityAudioParametersWithFullband(int fullband, int stereo, int fullBitrate)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setHighQualityAudioParameters(fullband, stereo, fullBitrate);

	return nRet;
}

int CAgoraMediaWrapper::enableInEarMonitoring(int enabled)
{
	int nRet = 0;

	return nRet;
}

int CAgoraMediaWrapper::enableWebSdkInteroperability(int enabled)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.enableWebSdkInteroperability(enabled);

	return nRet;
}

int CAgoraMediaWrapper::setVideoQualityParameters(int preferFrameRateOverImageQuality)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setVideoQualityParameters(preferFrameRateOverImageQuality);

	return nRet;
}

int CAgoraMediaWrapper::EnableExtendVideoCapture(BOOL bEnable, IVideoFrameObserver* lpVideoFrameObserver)
{
	agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_lpAgoraEngine, INTERFACE_ID_TYPE::AGORA_IID_MEDIA_ENGINE);

	int nRet = 0;
	AParameter apm(*m_lpAgoraEngine);

	if (mediaEngine.get() == NULL)
		return FALSE;

	if (bEnable && lpVideoFrameObserver != NULL) {
		//apm->setParameters("{\"che.video.local.camera_index\":1024}");
		nRet = mediaEngine->registerVideoFrameObserver(lpVideoFrameObserver);
	}
	else {
		nRet = mediaEngine->registerVideoFrameObserver(NULL);
		apm->setParameters("{\"che.video.local.camera_index\":0}");
	}

	return nRet;
}

std::string CAgoraMediaWrapper::getCallId()
{
	if (m_lpAgoraEngine) {
		agora::util::AString sCallId;
		m_lpAgoraEngine->getCallId(sCallId);

		return sCallId->data();
	}

	return "";
}

int CAgoraMediaWrapper::rate(const char* callId, int rating, const char* description)
{
	if (m_lpAgoraEngine && false) {

		return m_lpAgoraEngine->rate(callId, rating, description);
	}
}

int CAgoraMediaWrapper::complain(const char *callId, const char *desc)
{
	if (m_lpAgoraEngine && false) {

		return m_lpAgoraEngine->complain(callId, desc);
	}
}

BOOL CAgoraMediaWrapper::EnableScreenCapture(HWND hWnd, int nCapFPS /*= 15*/, LPCRECT lpCapRect /*= NULL*/, BOOL bEnable /*= TRUE*/)
{
	ASSERT(m_lpAgoraEngine != NULL);

	int ret = 0;
	RtcEngineParameters rep(*m_lpAgoraEngine);

	Rect rcCap;

	if (bEnable) {
		if (lpCapRect == NULL)
			ret = rep.startScreenCapture(hWnd, nCapFPS, NULL);
		else {
			rcCap.left = lpCapRect->left;
			rcCap.right = lpCapRect->right;
			rcCap.top = lpCapRect->top;
			rcCap.bottom = lpCapRect->bottom;

			ret = rep.startScreenCapture(hWnd, nCapFPS, &rcCap);
		}
	}
	else
		ret = rep.stopScreenCapture();

	if (ret == 0)
		m_bScreenCapture = bEnable;

	return ret == 0 ? TRUE : FALSE;
}

BOOL CAgoraMediaWrapper::IsScreenCaptureEnabled()
{
	return m_bScreenCapture;
}

void CAgoraMediaWrapper::SetScreenCaptureEnable(BOOL bEnable /*= TRUE*/)
{
	m_bScreenCapture = bEnable;
}

BOOL CAgoraMediaWrapper::EnableSDKVideoCapture(BOOL bEnable /*= TRUE*/)
{
	agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_lpAgoraEngine, agora::rtc::AGORA_IID_MEDIA_ENGINE);

	int nRet = 0;
	AParameter apm(*m_lpAgoraEngine);

	if (mediaEngine.get() == NULL)
		return FALSE;

	if (!bEnable)
		apm->setParameters("{\"che.video.local.camera_index\":1024}");
	else
		apm->setParameters("{\"che.video.local.camera_index\":0}");

	return nRet == 0 ? TRUE : FALSE;
}

BOOL CAgoraMediaWrapper::EnableSDKAudioCapture(BOOL bEnable /*= TRUE*/)
{
	int nRet = 0;
	AParameter apm(*m_lpAgoraEngine);
	if (bEnable)
		nRet = apm->setParameters(R"(["che.audio.external_device":false])");
	else
		nRet = apm->setParameters(R"(["che.audio.external_device":true])");

	return nRet == 0 ? TRUE : FALSE;
}