
// MediaDevice.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMediaDeviceApp:
// �йش����ʵ�֣������ MediaDevice.cpp
//

class CMediaDeviceApp : public CWinApp
{
public:
	CMediaDeviceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMediaDeviceApp theApp;