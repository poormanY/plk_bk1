#include "stdafx.h"
#include "LanguagePack.h"

CString EOL_LANGUAGE[N_LANGUAGE_INDEX_MAX][L_LANGUAGE_TYPE_MAX] = 
{
	// KOREAN
	// CHINESE
	// ENGLISH
	{ _T("디스플레이 검사 프로그램"), _T("显示器检查程序"), _T("Display Test Program") },
	{ _T("검사 준비\r\n중입니다"), _T("检查准备中"), _T("Ready for Test") },
	{ _T("버전을\r\n확인합니다"), _T("确认版本"), _T("Check Version") },
	{ _T("가운데 버튼을\r\n눌러주세요"), _T("请按中间按钮"), _T("Push the\r\nMiddle button") },
	{ _T("왼쪽 버튼을\r\n눌러주세요"), _T("请按左侧按钮"), _T("Push the\r\nLeft button") },
	{ _T("오른쪽 버튼을\r\n눌러주세요"), _T("请按右侧按钮"), _T("Push the\r\nRight button") },
	{ _T("왼쪽,오른쪽\r\n버튼을 동시에\r\n눌러주세요"), _T("请同时按\r\n左右按钮"), _T("Push the\r\nRight and Left\r\n button at once") },
	{ _T("LED를\r\n확인합니다"), _T("确认 LED"), _T("Check LED") }
};

int CLanguagePack::SET_LANGUAE_PACK(int languageType)
{
	if ( languageType >= L_LANGUAGE_TYPE_MAX )	languageType = L_ENGLISH;

	LP_DISPLAY_TEST_PROGRAM = EOL_LANGUAGE[ N_DISPLAY_TEST_PROGRAM][ languageType ];
	LP_READY_FOR_TEST = EOL_LANGUAGE[ N_READY_FOR_TEST][ languageType ];
	LP_CHECK_VERSION = EOL_LANGUAGE[ N_CHECK_VERSION][ languageType ];
	LP_PUSH_MIDDLE_BUTTON = EOL_LANGUAGE[ N_PUSH_MIDDLE_BUTTON][ languageType ];
	LP_PUSH_LEFT_BUTTON = EOL_LANGUAGE[ N_PUSH_LEFT_BUTTON][ languageType ];
	LP_PUSH_RIGHT_BUTTON = EOL_LANGUAGE[ N_PUSH_RIGHT_BUTTON][ languageType ];
	LP_PUSH_LEFT_RIGHT_BUTTON = EOL_LANGUAGE[ N_PUSH_LEFT_RIGHT_BUTTON][ languageType ];
	LP_CHECK_LED = EOL_LANGUAGE[ N_CHECK_LED][ languageType ];

	return 1;
}


CLanguagePack::CLanguagePack()
{
}
CLanguagePack::~CLanguagePack()
{
}