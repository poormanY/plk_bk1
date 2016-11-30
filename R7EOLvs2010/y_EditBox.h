#ifndef Y_EDIT_BOX_H
#define Y_EDIT_BOX_H

#include "y_wm_user.h"

enum
{
	UPDATE_OFF = 0,
	UPDATE_ON,
};

class CEditBox : public CStatic
{
public:

	CEditBox();
	~CEditBox();

	//--------- �ܺ� ȯ�� ���� ------------------------------------//
	BOOL m_tFontInstalled;  // ��Ʈ ���� ����
	UINT m_nFontFormat;		// ��Ʈ ����
							//--> �¿� ���� : DT_LEFT, DT_CENTER , DT_RIGHT
							//--> ���� ���� : DT_TOP , DT_VCENTER, DT_BOTTOM
	LOGFONT  m_LogFont;		// ��Ʈ ����
	CFont    m_Font;		// ��Ʈ ũ�� �� ������
	COLORREF m_ColorTxt;	// ��Ʈ ��
	COLORREF m_ColorBg;		// ��� ��
	CString  m_strMsg;		// ����
	//--------- �ܺ� ��� �Լ� ------------------------------------//
	void SetTextFormat(UINT a_uFormat);
	void SetTextColor(COLORREF a_Color);
	void SetBgColor(COLORREF a_Color);
	void SetLogFont(LOGFONT *a_pLogFont);
	void SetTextString(CString a_String);

	void SetText(COLORREF a_BgColor, COLORREF a_TextColor, CString a_StrText, BOOL a_UpdateMsg);
	
protected:
	//--------- ���� ȯ�� ���� ------------------------------------//

	//--------- ���� ��� �Լ� ------------------------------------//
	int GetMsgLines();

	//{{AFX_MSG(CTextStatic)
	afx_msg void OnPaint();
    afx_msg LRESULT OnThreadMsgUpdate(WPARAM a_wParam, LPARAM a_lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};





#endif //  !Y_EDIT_BOX_H  //