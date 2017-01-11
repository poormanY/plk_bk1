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

	//--------- �ܺ� ȯ�� ���� ------------------------------------//
	CString LP_DISPLAY_TEST_PROGRAM;	// ���÷��� �˻� ���α׷�
	CString LP_READY_FOR_TEST;			// �˻� �غ� ���Դϴ�
	CString LP_CHECK_VERSION;			// ������ Ȯ���մϴ�
	CString LP_PUSH_MIDDLE_BUTTON;		// ��� ��ư�� �����ּ���
	CString LP_PUSH_LEFT_BUTTON;		// ���� ��ư�� �����ּ���
	CString LP_PUSH_RIGHT_BUTTON;		// ������ ��ư�� �����ּ���
	CString LP_PUSH_LEFT_RIGHT_BUTTON;	// ����,������ ��ư�� ���ÿ� �����ּ���
	CString LP_CHECK_LED;				// LED�� Ȯ���մϴ�
	//--------- �ܺ� ��� �Լ� ------------------------------------//
	int SET_LANGUAE_PACK(int languageType);
protected:
	//--------- ���� ȯ�� ���� ------------------------------------//

	//--------- ���� ��� �Լ� ------------------------------------//
};


#endif //  !Y_LANGUAGEPACK_H  //
