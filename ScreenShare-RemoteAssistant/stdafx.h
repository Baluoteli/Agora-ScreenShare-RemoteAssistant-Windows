
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars


#include "../MediaSDK/include/IAgoraMediaEngine.h"
#include "../MediaSDK/include/IAgoraRtcEngine2.h"
using namespace agora::media;
using namespace agora::rtc;
#pragma comment(lib,"../MediaSDK/lib/agora_rtc_sdk.lib")

#include "../SignalSDK/include/agora_sig.h"
using namespace  agora_sdk_win;
#pragma comment(lib,"../SignalSDK/lib/agora_sig_sdk.lib")

#pragma warning(disable:4244)
#pragma warning(disable:4800)
#pragma warning(disable:4172)
#pragma warning(disable:4715)
#pragma warning(disable:4114)

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <assert.h>

#include "AgoraUitlc.h"
using namespace AgoraSdkCWrapperUtilc;
#include "AgoraSingletonTemplate.h"

#include "MediaDef.h"
using namespace AgoraMediaParamDef;

#include "SignalDef.h"
using namespace  AgoraSignleParamDef;

#include "./JsonObject/CJsonObject.h"
using namespace neb;

UINT getConvertChar(UINT uSrcChar);
UINT getSrcChar(UINT uConvertChar);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


