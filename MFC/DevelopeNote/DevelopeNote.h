
// DevelopeNote.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDevelopeNoteApp:
// �� Ŭ������ ������ ���ؼ��� DevelopeNote.cpp�� �����Ͻʽÿ�.
//

class CDevelopeNoteApp : public CWinApp
{
public:
	CDevelopeNoteApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDevelopeNoteApp theApp;