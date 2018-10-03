#include "stdafx.h"
#include "CSever.h"


CSever::CSever()
{
}


CSever::~CSever()
{
}


void CSever::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnAccept(nErrorCode);
}


void CSever::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnClose(nErrorCode);
}


void CSever::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
}
