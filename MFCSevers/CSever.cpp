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
	// TODO: �ڴ����ר�ô����/����û���
	m_SeverDlg->AddClient();                                  //��������û�
	CSocket::OnAccept(nErrorCode);
}


void CSever::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_SeverDlg->RemoveClient(this);                   // ɾ�������û�
	CSocket::OnClose(nErrorCode);
}


void CSever::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_SeverDlg->RecvData(this);                           // ��������
	CSocket::OnReceive(nErrorCode);
}
