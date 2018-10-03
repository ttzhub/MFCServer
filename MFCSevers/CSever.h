#pragma once
#include "MFCSeversDlg.h"			// 

class CMFCSeversDlg;
class CSever : public CSocket
{
public:
	CSever();
	~CSever();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

