#pragma once
#include "MFCSeversDlg.h"			// 主对话框头文件

class CMFCSeversDlg;

class CSever : public CSocket
{
public:
	CSever();
	~CSever();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	// 主对话框指针
	CMFCSeversDlg * m_SeverDlg;
};

