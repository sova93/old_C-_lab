
// lr4_v3Dlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <string>

class Clr4_v3DlgAutoProxy;


// ���������� ���� Clr4_v3Dlg
class Clr4_v3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Clr4_v3Dlg);
	friend class Clr4_v3DlgAutoProxy;

// ��������
public:
	Clr4_v3Dlg(CWnd* pParent = NULL);	// ����������� �����������
	virtual ~Clr4_v3Dlg();

// ������ ����������� ����
	enum { IDD = IDD_LR4_V3_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV

// ����������
protected:
	Clr4_v3DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;
	BOOL CanExit();
	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
	void UniteResult(char **result, std::vector<char*> &resultsVector);
public:
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedButton1();
	CString surename;
	CString number;
	CString adress;
	CString resOfSearch;
};
