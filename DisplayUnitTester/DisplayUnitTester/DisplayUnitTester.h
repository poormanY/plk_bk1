
// DisplayUnitTester.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDisplayUnitTesterApp:
// �� Ŭ������ ������ ���ؼ��� DisplayUnitTester.cpp�� �����Ͻʽÿ�.
//

class CDisplayUnitTesterApp : public CWinApp
{
public:
	CDisplayUnitTesterApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDisplayUnitTesterApp theApp;