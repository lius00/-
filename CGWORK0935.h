
// CGWORK0935.h : CGWORK0935 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCGWORK0935App:
// �йش����ʵ�֣������ CGWORK0935.cpp
//

class CCGWORK0935App : public CWinAppEx
{
public:
	CCGWORK0935App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPloygon();
};

extern CCGWORK0935App theApp;
