
// R7EOLvs2010.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CR7EOLvs2010App:
// �� Ŭ������ ������ ���ؼ��� R7EOLvs2010.cpp�� �����Ͻʽÿ�.
//

class CR7EOLvs2010App : public CWinApp
{
public:
	CR7EOLvs2010App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CR7EOLvs2010App theApp;