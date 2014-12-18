
// lr4_v3Dlg.h : файл заголовка
//

#pragma once

class Clr4_v3DlgAutoProxy;


// диалоговое окно Clr4_v3Dlg
class Clr4_v3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Clr4_v3Dlg);
	friend class Clr4_v3DlgAutoProxy;

// Создание
public:
	Clr4_v3Dlg(CWnd* pParent = NULL);	// стандартный конструктор
	virtual ~Clr4_v3Dlg();

// Данные диалогового окна
	enum { IDD = IDD_LR4_V3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	Clr4_v3DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
};
