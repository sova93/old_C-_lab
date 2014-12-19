
// lr4_v3.cpp : ���������� ��������� ������� ��� ����������.
//

#include "stdafx.h"
#include "lr4_v3.h"
#include "lr4_v3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clr4_v3App

BEGIN_MESSAGE_MAP(Clr4_v3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// �������� Clr4_v3App

Clr4_v3App::Clr4_v3App()
{
	// ��������� ���������� ������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ Clr4_v3App

Clr4_v3App theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xCC5CC53A, 0x31DC, 0x450D, { 0xA2, 0x76, 0x92, 0x8A, 0x33, 0x86, 0xA4, 0xB2 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// ������������� Clr4_v3App

BOOL Clr4_v3App::InitInstance()
{
	// InitCommonControlsEx() ��������� ��� Windows XP, ���� ��������
	// ���������� ���������� ComCtl32.dll ������ 6 ��� ����� ������� ������ ��� ���������
	// ������ �����������. � ��������� ������ ����� ��������� ���� ��� �������� ������ ����.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// ������������� ��������� OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ������� ��������� ��������, � ������, ���� ���������� ���� ��������
	// ������������� ������ �������� ��� �����-���� ��� �������� ����������.
	CShellManager *pShellManager = new CShellManager;

	// ��������� ����������� ���������� "������������ Windows" ��� ��������� ��������� ���������� MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ����������� �������������
	// ���� ��� ����������� �� ������������ � ���������� ��������� ������
	// ��������� ������������ �����, ���������� ������� �� ���������
	// ���������� �������� �������������, ������� �� ���������
	// �������� ������ �������, � ������� �������� ���������
	// TODO: ������� �������� ��� ������ �� ���-������ ����������,
	// �������� �� �������� �����������
	SetRegistryKey(_T("��������� ����������, ��������� � ������� ������� ����������"));
	// ������ ��������� ������ ��� ������������� ��� ����������� ��� ������ � ����������� ����������.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���������� ���� �������� � ���������� /Embedding ��� /Automation.
	// ������ ���������� ��� ������� �������������.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// ����������� ������ ������� ����� CoRegisterClassObject().
		COleTemplateServer::RegisterAll();
	}
	// ���������� ���� �������� � ���������� /Register ��� /Unregister. �������
	// ������ �� �������.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// ���������� ���� �������� �������� ��� � ������� ����������� (��������, /Register
	// ��� /Regserver). �������� ������ �������, ������� ���������� �����.
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

	Clr4_v3Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "��"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "������"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "��������������. �� ������� ������� ���������� ����, ������� ������ ���������� ���������� ���������.\n");
		TRACE(traceAppMsg, 0, "��������������. ��� ������������� ��������� ���������� MFC ��� ����������� ���� ���������� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// ������� ��������� ��������, ��������� ����.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��������� ���������� ���� �������, ���������� �������� FALSE, ����� ����� ���� ����� ��
	//  ���������� ������ ������� ���������� ��������� ����������.
	return FALSE;
}

int Clr4_v3App::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
