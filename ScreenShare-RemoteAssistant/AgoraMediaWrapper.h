#ifndef __AGORAMEDIAWRAPPER_H__
#define __AGORAMEDIAWRAPPER_H__

class CAGEngineEventHandler;
class CAgoraMediaWrapper :public CSingleton<CAgoraMediaWrapper>
{
public:
	friend CSingleton;
	~CAgoraMediaWrapper();

	const char* getSDKVersion();
	IRtcEngine* getRtcEngine();
	CAGEngineEventHandler* getEngineEventHandle();
	int JoinChannel(const char *channelKey, const char *channelName, const char *info, unsigned int uid);
	int leaveChannel();
	int enableLastmileTest(BOOL bEnable = TRUE);
	int enableVideo(BOOL bEnable = TRUE);
	int enableLocalRender(BOOL bEnable);
	int setLocalVideo(HWND hVideoWnd,UINT uid);
	int setRemoteVideo(HWND hVideoWnd, UINT uid);
	int localVideoPreview(HWND hVideoWnd, BOOL bPreviewOn);
	int enableAudio(BOOL bEnable);
	int setParameters(const char* options);
	int enableAudioVolumeIndication(int interval, int smooth);
	int startAudioRecording(const char* filePath, int quality);
	int stopAudioRecording();
	int startAudioMixing(const char *filePath, int loopback, int replace, int cycle, int playTime);
	int stopAudioMixing();
	int pauseAudioMixing();
	int resumeAudioMixing();
	int adjustAudioMixingVolume(int volume);
	int getAudioMixingDuration();
	int getAudioMixingCurrentPosition();
	int setAudioMixingPosition(int pos);
	int enableEchoTest(BOOL bEnable);
	int muteLocalAudioStream(int muted);
	int muteAllRemoteAudioStreams(int muted);
	int muteRemoteAudioStream(int uid, int muted);
	int switchCamera();
	int setVideoProfile(int profile, int swapWidthAndHeight);
	int muteLocalVideoStream(int muted);
	int muteAllRemoteVideoStreams(int muted);
	int muteRemoteVideoStream(int uid, int muted);
	int setLogFile(const char *filePath);
	int setLogFilter(unsigned int filter);
	int renewChannelKey(const char *channelKey);
	int setChannelProfile(int profile);
	int setClientRole(int role, const char *permissionKey);
	int enableDualStreamMode(int enabled);
	int setEncryptionMode(const char *encryptionMode);
	int setEncryptionSecret(const char *secret);
	int setRemoteVideoStreamType(int uid, int streamType);
	int startRecordingService(const char *recordingKey);
	int stopRecordingService(const char *recordingKey);
	int refreshRecordingServiceStatus();
	int createDataStream(int reliable, int ordered);
	int sendStreamMessage(int streamId, const char *data);
	int setRecordingAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall);
	int setPlaybackAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall);
	int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);
	int adjustRecordingSignalVolume(int volume);
	int adjustPlaybackSignalVolume(int volume);
	int setHighQualityAudioParametersWithFullband(int fullband, int stereo, int fullBitrate);
	int enableInEarMonitoring(int enabled);
	int enableWebSdkInteroperability(int enabled);
	int setVideoQualityParameters(int preferFrameRateOverImageQuality);

	int EnableExtendVideoCapture(BOOL bEnable, IVideoFrameObserver* lpVideoFrameObserver);
	std::string getCallId();
	int rate(const char* callId, int rating, const char* description);
	int complain(const char *callId, const char *desc);

	BOOL EnableScreenCapture(HWND hWnd, int nCapFPS = 15, LPCRECT lpCapRect = NULL, BOOL bEnable = TRUE);
	BOOL IsScreenCaptureEnabled();
	void SetScreenCaptureEnable(BOOL bEnable = TRUE);

	BOOL EnableSDKVideoCapture(BOOL bEnable = TRUE);
	BOOL EnableSDKAudioCapture(BOOL bEnable = TRUE);

protected:

	inline void initMediaEngine(const std::string &appID);
	inline void uninitMediaEngine();

private:
	CAgoraMediaWrapper();
	static CSingleton<CAgoraMediaWrapper>::CGrabo graboMediaWrapper;

	std::string m_sAppId;
	std::string m_sChannelName;
	UINT m_uLoginUID;
	BOOL m_bScreenCapture;

	IRtcEngine* m_lpAgoraEngine;
	CAGEngineEventHandler* m_pAgEventHandle;
};

#endif