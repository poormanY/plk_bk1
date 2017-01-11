#ifndef Y_LANGUAGEPACK_H
#define Y_LANGUAGEPACK_H

enum _LANGUAGE_TYPE
{
	L_KOREAN = 0,
	L_CHINESE,
	L_ENGLISH,
	L_LANGUAGE_TYPE_MAX
};

enum _LANGUAGE_INDEX
{
	N_DISPLAY_TEST_PROGRAM = 0,
	N_READY_FOR_TEST,
	N_CHECK_VERSION,
	N_PUSH_MIDDLE_BUTTON,
	N_PUSH_LEFT_BUTTON,
	N_PUSH_RIGHT_BUTTON,
	N_PUSH_LEFT_RIGHT_BUTTON,
	N_CHECK_LED,
	N_LANGUAGE_INDEX_MAX
};

class CLanguagePack
{
public:
	CLanguagePack();
	~CLanguagePack();

	//--------- 외부 환경 변수 ------------------------------------//
	CString LP_DISPLAY_TEST_PROGRAM;	// 디스플레이 검사 프로그램
	CString LP_READY_FOR_TEST;			// 검사 준비 중입니다
	CString LP_CHECK_VERSION;			// 버전을 확인합니다
	CString LP_PUSH_MIDDLE_BUTTON;		// 가운데 버튼을 눌러주세요
	CString LP_PUSH_LEFT_BUTTON;		// 왼쪽 버튼을 눌러주세요
	CString LP_PUSH_RIGHT_BUTTON;		// 오른쪽 버튼을 눌러주세요
	CString LP_PUSH_LEFT_RIGHT_BUTTON;	// 왼쪽,오른쪽 버튼을 동시에 눌러주세요
	CString LP_CHECK_LED;				// LED를 확인합니다
	//--------- 외부 사용 함수 ------------------------------------//
	int SET_LANGUAE_PACK(int languageType);
protected:
	//--------- 내부 환경 변수 ------------------------------------//

	//--------- 내부 사용 함수 ------------------------------------//
};


#endif //  !Y_LANGUAGEPACK_H  //
