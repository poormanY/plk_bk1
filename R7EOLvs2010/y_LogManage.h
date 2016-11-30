#ifndef Y_LOG_MANAGE_H
#define Y_LOG_MANAGE_H

class CLogManage
{
public:
	CLogManage();
	~CLogManage();

	//--------- �ܺ� ȯ�� ���� ------------------------------------//

	//--------- �ܺ� ��� �Լ� ------------------------------------//
	void SetFilePath(CString a_FilePath);
	int WriteLog(CString a_Log);
	int WriteLogTime(CString a_Log);
	int CopyLog(CString a_CopyFilePath);

	int		WriteSetting(CString a_Setting, CString a_Value);
	CString ReadSetting(CString a_Setting);
protected:
	//--------- ���� ȯ�� ���� ------------------------------------//
	CString m_strFilePath;      // ���� ���
	//--------- ���� ��� �Լ� ------------------------------------//
	
};





#endif //  !Y_LOG_MANAGE_H  //