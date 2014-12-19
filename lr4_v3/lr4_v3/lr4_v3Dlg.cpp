
// lr4_v3Dlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "lr4_v3.h"
#include "lr4_v3Dlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ���������� ���� Clr4_v3Dlg


IMPLEMENT_DYNAMIC(Clr4_v3Dlg, CDialogEx);

Clr4_v3Dlg::Clr4_v3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Clr4_v3Dlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

Clr4_v3Dlg::~Clr4_v3Dlg()
{
	// ���� ��� ������� ����������� ���� ������������ ������-������ �������������, ����������
	//  ��� ��� ��������� ��������� �� ��� ���������� ���� �������� NULL, ����� �� ����� ��
	//  �������� ����������� ����.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void Clr4_v3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clr4_v3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT5, &Clr4_v3Dlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &Clr4_v3Dlg::OnEnChangeEdit6)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ����������� ��������� Clr4_v3Dlg
HBRUSH Clr4_v3Dlg::OnCtlColor(CDC* pDC,CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr=CDialog::OnCtlColor(pDC,pWnd,nCtlColor);
	CWnd* pStatic=GetDlgItem(IDC_STATIC1);
	ASSERT(pStatic);
	if(pStatic->m_hWnd==pWnd->m_hWnd)
	{
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
	}
	pStatic=GetDlgItem(IDC_STATIC);
	ASSERT(pStatic);
	if(pStatic->m_hWnd==pWnd->m_hWnd)
	{
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
	}
	pStatic=GetDlgItem(IDC_STATIC2);
	ASSERT(pStatic);
	if(pStatic->m_hWnd==pWnd->m_hWnd)
	{
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
	}
		pStatic=GetDlgItem(IDC_STATIC4);
	ASSERT(pStatic);
	if(pStatic->m_hWnd==pWnd->m_hWnd)
	{
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
	}
		pStatic=GetDlgItem(IDC_STATIC5);
	ASSERT(pStatic);
	if(pStatic->m_hWnd==pWnd->m_hWnd)
	{
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
	}
		pStatic=GetDlgItem(IDC_STATIC6);
	ASSERT(pStatic);
	if(pStatic->m_hWnd==pWnd->m_hWnd)
	{
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
	}
	return hbr;
}
BOOL Clr4_v3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void Clr4_v3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void Clr4_v3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR Clr4_v3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ������� ������������� �� ������ ��������� ������ ��� �������� ���������� ������������,
//  ���� ����������� ��-�������� ���������� ���� �� ��� ��������. ���
//  ����������� ��������� �����������, ��� ���� ������-������ ��� ������������,
//  �� ���������������� ��������� ����������, �� ���������� ���� �������� (���� ���
//  �������).

void Clr4_v3Dlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

BOOL Clr4_v3Dlg::CanExit()
{
	// ���� ������ ������-������� ��-�������� �������, �� ����������
	//  ������������� ���������� ��� ����������. ��������
	//  ���������� ���� ����������, �� ������� ��� ���������������� ���������.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void Clr4_v3Dlg::OnEnChangeEdit5()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

//#1015

	// TODO:  �������� ��� �������� ����������
}


void Clr4_v3Dlg::OnEnChangeEdit6()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

//#1015

	// TODO:  �������� ��� �������� ����������
}
