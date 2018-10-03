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
	m_SeverDlg->AddClient();                                  //添加上线用户
	CSocket::OnAccept(nErrorCode);
}


void CSever::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_SeverDlg->RemoveClient(this);                   // 删除下线用户
	CSocket::OnClose(nErrorCode);
}


void CSever::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_SeverDlg->RecvData(this);                           // 接收数据
	CSocket::OnReceive(nErrorCode);
}
