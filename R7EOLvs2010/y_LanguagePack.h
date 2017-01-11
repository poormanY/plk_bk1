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
	N_R7_EOL_PROGRAM = 0,
	N_INPUT_DATA,
	N_VEHICLE_SPEED,
	N_WINKER,
	N_LEFT,
	N_RIGHT,
	N_OUTPUT_DATA,
	N_LANE_DETECT,
	N_LANE_WARNING,
	N_HMW_WARNING,
	N_FCW_WARNING,
	N_PROCESS_COUNT,
	N_FACTORY_LANE,
	N_TESTER,
	N_TEST_TIME,
	N_PRODUCT_NAME,
	N_PASS,
	N_FAIL,
	N_TOTAL,
	N_PASS_RATE,
	N_TEST_INDEX,
	N_TARGET,
	N_CHECK,
	N_RESULT,
	N_LAST_TEST,
	N_TEST_WAITING,
	N_IO_BOARD,
	N_BARCODE1,
	N_BARCODE2,
	N_CASE_BARCODE,
	N_POWER,
	N_CONNECT_FAIL,
	N_COMMUNICATION_FAIL,
	N_TESTING,
	N_SERIAL_NUMBER,
	N_SOFTWARE_VERSION,
	N_MCU_VERSION,
	N_ACCELERATION,
	N_SPEED_PULSE,
	N_CONFIRM_FAIL,
	N_LANE_DETECT_FAIL,
	N_LANE_WARNING_L_FAIL,
	N_LANE_WARNING_R_FAIL,
	N_WINKER_L,
	N_WINKER_R,
	N_EMERGENCY_LAMP,
	N_FCW_WARNING_FAIL,
	N_WARNING_FAIL,
	N_DTC_DELETE_FAIL,
	N_POWER_OFF_FAIL,
	N_CASE_BARCODE_FAIL,
	N_TEST_PASS,
	N_TEST_FAIL,
	N_FAIL_OCCURS,
	N_TEST_END,
	N_CONNECTING,
	N_TEST_PROCESS_START,
	N_POWER_OFF,
	N_CONNECTION_CHECK,
	N_LANE_WARNING_L,
	N_LANE_WARNING_R,
	N_START,
	N_CLOSE,
	N_PAUSE,
	N_LANGUAGE_INDEX_MAX
};

class CLanguagePack
{
public:
	CLanguagePack();
	~CLanguagePack();

	//--------- �ܺ� ȯ�� ���� ------------------------------------//
	CString LP_R7_EOL_PROGRAM;		// R7 EOL �˻� ���α׷�
	CString LP_INPUT_DATA;			// �Է� ������
	CString LP_VEHICLE_SPEED;		// ���� �ӵ�
	CString LP_WINKER;				// ������ ��ȣ
	CString LP_LEFT;				// ��
	CString LP_RIGHT;				// ��
	CString LP_OUTPUT_DATA;			// ��� ������
	CString LP_LANE_DETECT;			// ���� �ν�
	CString LP_LANE_WARNING;		// ���� ��Ż �溸
	CString LP_HMW_WARNING;			// HMW �溸
	CString LP_FCW_WARNING;			// FCW �溸
	CString LP_PROCESS_COUNT;		// ���� ī��Ʈ
	CString LP_FACTORY_LANE;		// ���θ�
	CString LP_TESTER;				// �˻���
	CString	LP_TEST_TIME;			// �˻� �ð�
	CString LP_PRODUCT_NAME;		// ��ǰ��
	CString LP_PASS;				// ��ǰ
	CString LP_FAIL;				// �ҷ�
	CString LP_TOTAL;				// ��ü
	CString LP_PASS_RATE;			// ��ǰ��
	CString LP_TEST_INDEX;			// �˻� �׸�
	CString LP_TARGET;				// ��ǥ��
	CString LP_CHECK;				// ������
	CString LP_RESULT;				// �����
	CString LP_LAST_TEST;			// ��� �������
	CString LP_TEST_WAITING;		// �˻� �����
	CString LP_IO_BOARD;			// IO ����
	CString LP_BARCODE1;			// ���ڵ� ��ĳ��1
	CString LP_BARCODE2;			// ���ڵ� ��ĳ��2
	CString LP_CASE_BARCODE;		// ���̽� ���ڵ�
	CString LP_POWER;				// ����
	CString LP_CONNECT_FAIL;		// ���� ����
	CString LP_COMMUNICATION_FAIL;	// ��� ����
	CString LP_TESTING;				// �˻���
	CString LP_SERIAL_NUMBER;		// �ø��� ��ȣ
	CString LP_SOFTWARE_VERSION;	// ����Ʈ���� ����
	CString LP_MCU_VERSION;			// MCU ����
	CString LP_ACCELERATION;		// ���ӵ���
	CString LP_SPEED_PULSE;			// �ӵ� �޽���
	CString LP_CONFIRM_FAIL;		// Ȯ�� ����
	CString LP_LANE_DETECT_FAIL;	// ���� �ν� ����
	CString LP_LANE_WARNING_L_FAIL;	// ���� ���� �溸 ����
	CString LP_LANE_WARNING_R_FAIL;	// ���� ���� �溸 ����
	CString LP_WINKER_L;			// ���� ���õ� (��)
	CString LP_WINKER_R;			// ���� ���õ� (��)
	CString LP_EMERGENCY_LAMP;		// ��� ������
	CString LP_FCW_WARNING_FAIL;	// ���� �浹 �溸 ����
	CString LP_WARNING_FAIL;		// �溸 ����
	CString LP_DTC_DELETE_FAIL;		// DTC ���� ����
	CString LP_POWER_OFF_FAIL;		// �Ŀ� ���� ����
	CString LP_CASE_BARCODE_FAIL;	// ���̽� ���ڵ� ����
	CString LP_TEST_PASS;			// �˻� ���
	CString LP_TEST_FAIL;			// �˻� ����
	CString LP_FAIL_OCCURS;			// �ҷ� �߻�
	CString LP_TEST_END;			// �˻� ����
	CString LP_CONNECTING;			// ������
	CString LP_TEST_PROCESS_START;	// ��ǰ�� ���� ��Ű�� ���� �� �Ŀ� ���� ��ư�� ��������
	CString LP_POWER_OFF;			// ������ ���� �մϴ�
	CString LP_CONNECTION_CHECK;	// ��ſ��� Ȯ��
	CString LP_LANE_WARNING_L;		// LDWS ���� ���� ��Ż	
	CString LP_LANE_WARNING_R;		// LDWS ���� ���� ��Ż
	CString LP_START;				// ����
	CString LP_CLOSE;				// �ݱ�
	CString LP_PAUSE;				// �ߴ�

	//--------- �ܺ� ��� �Լ� ------------------------------------//
	int SET_LANGUAE_PACK(int languageType);
protected:
	//--------- ���� ȯ�� ���� ------------------------------------//

	//--------- ���� ��� �Լ� ------------------------------------//
};


#endif //  !Y_LANGUAGEPACK_H  //
