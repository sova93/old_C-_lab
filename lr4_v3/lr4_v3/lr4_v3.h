
// lr4_v3.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// Clr4_v3App:
// � ���������� ������� ������ ��. lr4_v3.cpp
//

class Clr4_v3App : public CWinApp
{
public:
	Clr4_v3App();

// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern Clr4_v3App theApp;