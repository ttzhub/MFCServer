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

	CSocket::OnAccept(nErrorCode);
}


void CSever::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnClose(nErrorCode);
}


void CSever::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnReceive(nErrorCode);
}
