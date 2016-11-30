#ifndef Y_SCREWCOUNTERMGT_H
#define Y_SCREWCOUNTERMGT_H

#include "y_JDEFINE.h"

class CScrewMgt
{
public:
	CScrewMgt();
	~CScrewMgt();

	//--------- �ܺ� ȯ�� ���� ------------------------------------//
	bool SetSendMsg(const char *szMeg, int nRepeatNum);
	int m_nScrew_State;

	bool Open(const char *a_pszCom);
    void Close(void);

	bool  AddCount(void);
    bool  DelCount(void);
    void  DelAllCount(void);
    char *GetMsg(void);
    S16   GetCount(void);

    TOF  Thread_Begin(void);
    TOF  Thread_End(void);
	//--------- �ܺ� ��� �Լ� ------------------------------------//

protected:
	//--------- ���� ȯ�� ���� ------------------------------------//
	HANDLE m_hCom;
	bool m_tMsgComplete;
    S16  m_nCount;
    char m_szMsg[256];
	
	//--------- ���� ��� �Լ� ------------------------------------//
	
	
	// Thread for Run
    TOF m_tThreadStop;
	CWinThread * m_pThread;

    friend UINT ThreadScrew(LPVOID pParam);
};





#endif //  !Y_SCREWCOUNTERMGT_H  //