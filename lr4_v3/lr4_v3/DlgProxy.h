
// DlgProxy.h: ���� ���������
//

#pragma once

class Clr4_v3Dlg;


// �������� ������ ������� Clr4_v3DlgAutoProxy

class Clr4_v3DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(Clr4_v3DlgAutoProxy)

	Clr4_v3DlgAutoProxy();           // ���������� �����������, ������������ ��� ������������ ��������

// ��������
public:
	Clr4_v3Dlg* m_pDialog;

// ��������
public:

// ���������������
	public:
	virtual void OnFinalRelease();

// ����������
protected:
	virtual ~Clr4_v3DlgAutoProxy();

	// ��������� ������� ����� ���������

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(Clr4_v3DlgAutoProxy)

	// ������������� ��������� ������� ������������� ����� OLE

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

